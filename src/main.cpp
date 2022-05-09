#include <Arduino.h>
#include  <SPI.h>
#include  <RF24.h>
#include "packet.h"

RF24 radio(9,10); 
uint8_t address[6] = {80,0xCE,0xCC,0xCE,0xCC};   // Adresse du pipe
payload_t rcv_val;
long diff;
long time;

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
      Serial.print("Température : ");
      Serial.println(rcv_val.temperature);
      Serial.print("Luminosité : ");
      Serial.println(rcv_val.luminosite);
      Serial.print("Humidité : ");
      Serial.println(rcv_val.humidite);
      Serial.print("Température2 : ");
      Serial.println(rcv_val.temperature2);
      Serial.print("Gaz : ");
      Serial.println(rcv_val.gaz[0]);
      Serial.print("Code barre : ");
      Serial.println(rcv_val.codeBarre);
      
            
      }
}