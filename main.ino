#include <DHT.h>  
#include <DHT_U.h>

const int SENSOR = 10;
DHT dht(SENSOR, DHT11); 

const int MAX_N_LEDs = 9;
const int LED1 = 1;
const int LED_FEUCHTIGKEIT = 0;

const int LED_GRUN = 11;
const int LED_GELB = 12;
const int LED_ROT  = LED_BUILTIN;

void setup(){
  //Serial.begin(9600);
  dht.begin();     
  for(int i = 0; i<=13; i++){
    if (i != SENSOR)
      pinMode(i, OUTPUT);
  }
}

void AktuatorLED(int nummer, int feuchtigkeit_status){
  digitalWrite(LED_FEUCHTIGKEIT, feuchtigkeit_status);
  
  int leds_anstellen = nummer % 10;
  for(int i = 0; i<MAX_N_LEDs; i++){
    digitalWrite(LED1 + i, LOW);
    if (i < leds_anstellen){
      digitalWrite(LED1 + i, HIGH);
    }
  }
  int zehner = nummer/10;
  
  digitalWrite(LED_ROT, LOW);
  digitalWrite(LED_GELB, LOW);
  digitalWrite(LED_GRUN, LOW); 
    if ((!feuchtigkeit_status && 3 == zehner) 
      || (feuchtigkeit_status && 4 == zehner)){
      digitalWrite(LED_GRUN, HIGH); 
      digitalWrite(LED_ROT, HIGH);
    }
    if ((!feuchtigkeit_status && 2 == zehner) 
      || (feuchtigkeit_status && 5 == zehner)){
      digitalWrite(LED_GRUN, HIGH); 
    }
    if ((!feuchtigkeit_status && 1 == zehner) 
      || (feuchtigkeit_status && 6 == zehner)){
      digitalWrite(LED_GRUN, HIGH); 
      digitalWrite(LED_GELB, HIGH);
    }
    if ((!feuchtigkeit_status && 0 == zehner) 
      || (feuchtigkeit_status && 7 == zehner)){
      digitalWrite(LED_GELB, HIGH);
    }
    if (feuchtigkeit_status && 8 == zehner){
      digitalWrite(LED_GELB, HIGH);
      digitalWrite(LED_ROT, HIGH); 
    }
    if ((!feuchtigkeit_status && 4 == zehner) 
      || (feuchtigkeit_status && 9 == zehner)){
      digitalWrite(LED_ROT, HIGH);
    }
    
  /*Serial.print(feuchtigkeit_status);
  Serial.print("    Zehner: "); 
  Serial.print(zehner);
  Serial.print(" Leds anstellen: ");
  Serial.println(leds_anstellen);*/
}

int temperatur;
int luftfeuchte;

void loop(){
  delay(2000);
  temperatur = dht.readTemperature(); 
  AktuatorLED(temperatur, LOW);
  delay(2000);
  luftfeuchte = dht.readHumidity();  
  AktuatorLED(luftfeuchte, HIGH);
  /*Serial.print("  Temperatur: "); 
  Serial.print(temperatur);
  Serial.print(" Luftfeuchte: ");
  Serial.println( luftfeuchte );*/
}
