/*
 * Prueba del DHT22
 */

#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);//coloca la direccion de 


//VARIABLES 
#define DHTPIN 2 
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22     // DHT 22  (AM2302), AM2321
int retardo = 1000;   // retardo entre lecturas 
DHT dht(DHTPIN, DHTTYPE);
char array1[]="    EPET Nro 7     "; // cargar en unerray
char array2[]="Secadero de Madera ";
char array3[]=" Controlado por:   ";
char array4[]="    Arduino        ";

char cadenaSP[20];
char cadenaME[20];
char cadenaVE[20];

int hum_set=40;
int temp_set=50;
int kp_set=1000;
int lec_pot_temp;
int lec_pot_hum;
int lec_pot_kp;

int rele_humedad= 9;
int rele_temperatura= 11;

void setup() {
  Serial.begin(9600);
  Serial.println("Prueba del DHT22!");
  dht.begin();
  
  pinMode (rele_humedad,OUTPUT);    //indicamos en que ping estan los reles
  pinMode (rele_temperatura,OUTPUT); 
  
  digitalWrite(rele_humedad,HIGH); //inicializamos los reles apagados
  digitalWrite(rele_temperatura,HIGH);
  
lcd.init();        //inicializa el lcd
lcd.backlight();   // ilumina el fondo

pantalla(0,0,array1);
pantalla(0,1,array2);
pantalla(0,2,array3);
pantalla(0,3,array4);

delay(2000);
lcd.clear();
  
}



void loop() {

int lec_pot_hum=analogRead(A2);
int lec_pot_temp=analogRead(A1);
int lec_pot_kp=analogRead(A0);

 temp_set=map(lec_pot_temp,0,1023,20,50);
 hum_set=map(lec_pot_hum,0,1023,15,100);
 kp_set=map(lec_pot_kp,0,1023,100,5000);

  
  lcd.clear();
  
  float h = dht.readHumidity();     // Lee Humedad
  float t = dht.readTemperature(); // Lee Temperatura
  
  if (isnan(h) || isnan(t) ) {
    Serial.println("Falla en la lectura del sensor DHT !");
    return;
  }
int Temp=t;
int Hum=h;

 sprintf(array2,"S.P Hum%3d Temp%3d*C",hum_set,temp_set);
 sprintf(array3,"Med Hum%3d Temp%3d*C",Hum,Temp);
 sprintf(array4,"Ventana Tiem :%3d",kp_set);
  lcd.clear();
  pantalla(0,0,array1); 
  pantalla(0,1,array2);
  pantalla(0,2,array3);
  pantalla(0,3,array4);
delay(retardo);


  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print("%");
   Serial.print("     Temperatura: ");
  Serial.print(t);
  Serial.println(" *C ");
 
 
 
 if(Temp<=temp_set){
  
    digitalWrite(rele_temperatura,LOW); //PRENDEMOS RELE
  delay(kp_set);

  }else{
     digitalWrite(rele_temperatura,HIGH);
   
    }

 
 
 
 if(Hum>=hum_set){
  
    digitalWrite(rele_humedad,LOW); //PRENDEMOS RELE

  }else{
     digitalWrite(rele_humedad,HIGH);
    }





}

int pantalla(int columna,int fila,char texto[]){

  lcd.setCursor(columna,fila);
  for (int c=0;c<=19;c++){
  lcd.print(texto[c]);
  }
}
