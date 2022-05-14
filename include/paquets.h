
#ifndef PAQUETS_H
#define PAQUETS_H

typedef struct paquetInfos_t
{
  short temperature;
  unsigned short humidite;
  short temperature2;
  unsigned short gaz[8];
} paquetInfos_t;

typedef struct paquetPorte_t
{
  bool porteOuverte;
} paquetPorte_t;

typedef struct paquetCodebarre_t
{
  unsigned long codeBarre1;
  unsigned long codeBarre2;
} paquetCodebarre_t;

#endif
