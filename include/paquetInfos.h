
#ifndef PAQUET_INFOS_H
#define PAQUET_INFOS_H

typedef struct paquetInfos_t
{
  short temperature;
  unsigned short humidite;
  short temperature2;
  unsigned short gaz[8];
} paquetInfos_t;

#endif
