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
  Serial.println("\n");
  Serial.println("Debut setup");

  radio.begin();
  radio.setChannel(80);
  radio.setDataRate(RF24_2MBPS);

  radio.openReadingPipe(0, address); // Ouvrir le Pipe en lecture
  radio.startListening();
  radio.setPALevel(RF24_PA_MAX);
  radio.enableDynamicPayloads();

  Serial.println("Fin setup");
}

void loop(void)
{
  while (radio.available())
  {
    Serial.println();

    switch (radio.getDynamicPayloadSize())
    {
    case sizeof(paquetInfos_t):
    {
      Serial.println("Réception d'un paquet infos");
      radio.read(&paquetInfos, sizeof(paquetInfos));

      // Température 1
      Serial.print("Température 1:  ");
      float temperature = (float)paquetInfos.temperature / 100.0;
      Serial.print(temperature);
      Serial.println(" °C ");

      // Humidité
      Serial.print("Humidité : ");
      float humidite = (float)paquetInfos.humidite / 100.0;
      Serial.print(humidite);
      Serial.println(" % ");

      // Température 2 (capteur humidité)
      Serial.print("Température 2 : ");
      float temperature2 = (float)paquetInfos.temperature2 / 100.0;
      Serial.print(temperature2);
      Serial.println(" °C ");

      // Gaz
      Serial.println("Gaz : ");
      for (int i = 0; i < 8; i++)
      {
        Serial.print(liste_gaz[i]);
        Serial.print(" : ");
        Serial.print(paquetInfos.gaz[i]);
        Serial.println(" ppm ");
      }
      break;
    }

    // Code barre
    case sizeof(paquetCodebarre_t):
    {

      Serial.println("Réception d'un paquet code barre");
      radio.read(&paquetCodebarre, sizeof(paquetCodebarre));

      Serial.print("Code barre : ");
      Serial.print(paquetCodebarre.codeBarre1);
      Serial.println(paquetCodebarre.codeBarre2);
    }

    // Luminosité
    case sizeof(paquetPorte_t):
    {

      Serial.println("Réception d'un paquet porte");
      radio.read(&paquetPorte, sizeof(paquetPorte));

      Serial.print("Porte ");
      if (paquetPorte.porteOuverte)
      {
        Serial.println("ouverte");
      }
      else
      {
        Serial.println("fermée");
      }
    }

    default:

      // Serial.println("Test");
      // Serial.println(radio.getPayloadSize());
      // Serial.println(radio.getDynamicPayloadSize());
      // Serial.println(sizeof(paquetInfos_t));
      // Serial.println(sizeof(paquetCodebarre_t));
      // Serial.println(sizeof(paquetPorte_t));

      delay(1000);
      break;
    }
  }
}