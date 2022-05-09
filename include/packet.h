
#ifndef __PACKET_H__
#define __PACKET_H__

typedef struct payload_t
{
  short temperature;
  bool luminosite;
  unsigned short humidite;
  short temperature2;
  unsigned short gaz[8];
  char codeBarre;
} payload_t;

#endif
