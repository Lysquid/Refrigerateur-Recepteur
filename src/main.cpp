#include <Arduino.h>
#include  <SPI.h>
#include  <RF24.h>
#include "packet.h"


RF24 radio(9,10); 
uint8_t address[6] = {80,0xCE,0xCC,0xCE,0xCC};   // Adresse du pipe
payload_t rcv_val;
long diff;
long time;
float val_temperature1;
float val_temperature2;
float val_humidite;
String liste_gaz[8] = {"NH3","CO","NO2","C3H8","C4H10","CH4","H2","C2H5OH"};

void setup() {
  Serial.begin(115200);    // Initialiser la communication série 
  Serial.println (F("Starting my first test")) ;
  
  radio.begin();
  radio.setChannel(80);
  radio.setDataRate(RF24_2MBPS);

  radio.openReadingPipe(0,address); // Ouvrir le Pipe en lecture
  radio.startListening();
  radio.setPALevel(RF24_PA_MAX);
  radio.enableDynamicPayloads();
  

}

void loop(void) {
    unsigned long wait = micros();
    boolean timeout = false;     
    while (radio.available()) 
      {
      radio.read(&rcv_val, sizeof(rcv_val));
      Serial.println(F("received value : "));

      //Température 1
      Serial.print("Température 1: ");      
      val_temperature1 = (float) rcv_val.temperature/100.0;
      Serial.println(val_temperature1);

      //Luminosité
      Serial.print("Luminosité : ");
      if (rcv_val.luminosite) {
        Serial.println("Clair");
      } else {
          Serial.println("Sombre");
      }

      //Humidité 
      Serial.print("Humidité : ");
      val_humidite = (float) rcv_val.humidite/100.0;
      Serial.println(val_humidite);

      //Température 2 (capteur humidité)
      Serial.print("Température 2: ");      
      val_temperature1 = (float) rcv_val.temperature2/100.0;
      Serial.println(val_temperature2);
      
      //Gaz
      Serial.print("Gaz : ");
      for (int i = 0; i < 8; i++)
      {
          Serial.println(liste_gaz[i]);
          Serial.print(" : ");
          Serial.print(rcv_val.gaz[i]);
      }
      
      //Code barre
      Serial.print("Code barre : ");
      Serial.println(rcv_val.codeBarre);
      
            
      }
}