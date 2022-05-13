
#ifndef __PACKET_H__
#define __PACKET_H__

typedef struct paquetInfos_t
{
  short temperature;
  unsigned short humidite;
  short temperature2;
  unsigned short gaz[8];
} paquetInfos_t;

#endif
