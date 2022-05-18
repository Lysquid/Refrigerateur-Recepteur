#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <paquets.h>

RF24 radio(9, 10);
uint8_t address[6] = {80, 0xCE, 0xCC, 0xCE, 0xCC}; // Adresse du pipe

paquetCodebarre_t paquetCodebarre;
paquetInfos_t paquetInfos;
paquetPorte_t paquetPorte;

String liste_gaz[8] = {"NH3", "CO", "NO2", "C3H8", "C4H10", "CH4", "H2", "C2H5OH"};

void setup()
{
  Serial.begin(115200); // Initialiser la communication série

  radio.begin();
  radio.setChannel(80);
  radio.setDataRate(RF24_2MBPS);

  radio.openReadingPipe(0, address); // Ouvrir le Pipe en lecture
  radio.startListening();
  radio.setPALevel(RF24_PA_MAX);
  radio.enableDynamicPayloads();
}

void loop(void)
{
  while (radio.available())
  {

    switch (radio.getDynamicPayloadSize())
    {
    case sizeof(paquetInfos_t):
    {
      radio.read(&paquetInfos, sizeof(paquetInfos));

      // Température 1
      Serial.print("info;1;");
      float temperature = (float)paquetInfos.temperature / 100.0;
      Serial.println(temperature);

      // Humidité
      Serial.print("info;2;");
      float humidite = (float)paquetInfos.humidite / 100.0;
      Serial.println(humidite);

      // Température 2 (capteur humidité)
      Serial.print("info;11;");
      float temperature2 = (float)paquetInfos.temperature2 / 100.0;
      Serial.println(temperature2);

      // Gaz
      for (int i = 0; i < 8; i++)
      {
        Serial.print("info;");
        Serial.print(3 + i);
        Serial.print(";");
        Serial.println(paquetInfos.gaz[i]);
      }
      break;
    }

    // Code barre
    case sizeof(paquetCodebarre_t):
    {

      radio.read(&paquetCodebarre, sizeof(paquetCodebarre));

      Serial.print("codebarre;0;");
      Serial.print(paquetCodebarre.codeBarre1);
      Serial.println(paquetCodebarre.codeBarre2);
      break;
    }

    // Luminosité
    case sizeof(paquetPorte_t):
    {

      radio.read(&paquetPorte, sizeof(paquetPorte));

      Serial.print("porte;0;");
      Serial.println(paquetPorte.porteOuverte);

      break;
    }

    default:

      delay(100);
      break;
    }
  }
}