//LIBS
#include <ArduinoJson.h>

//Entradas
const int termistor = A1;
const int turbPin = A0;
const int phPin = A2;

//Saidas
const int led = 12;

//Variaveis
float tc, vO, r2, logR2, t, c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07, r1 = 10000;    
int  turbidez, ph;
float temperatura;


void setup() {
  Serial.begin(115200);
  pinMode(termistor, INPUT);
  pinMode(turbPin, INPUT);
  pinMode(phPin, INPUT);
  pinMode(led, OUTPUT);
}



void loop() {
   
    temperatura = readTemp(termistor);
    turbidez = analogRead(turbPin);
    ph = analogRead(phPin);
    ph = ph * 2;
  
    /*Serial.print("Temperatura: ");
    Serial.println(temperatura);
    Serial.print("Turbidez: ");
    Serial.println(turbidez);
    Serial.print("PH: ");
    Serial.println(ph);*/
    boolean status;
    char dado;
    if(Serial.available() > 0){
    
        dado = Serial.read();

        if(dado == 'A'){
            digitalWrite(led, HIGH); 
            status = true;
            delay(3000);  
        }
    } 
    
    StaticJsonDocument<100> json;
    json["Temperatura"] = temperatura;
    json["Turbidez"] = turbidez;
    json["PH"] = ph;
    //json["Status"]= status;
    serializeJson(json, Serial);
    
    Serial.println();
    
    delay(30000);
  
}

float readTemp(int termistor) {
  vO = analogRead(termistor);
  r2 = r1 * (1023.0 / (float)vO - 1.0);
  logR2 = log(r2);
  t = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
  tc = t - 273.15;

  return tc;
}
