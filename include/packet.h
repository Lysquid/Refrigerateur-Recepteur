
#ifndef __PACKET_H__
#define __PACKET_H__

typedef struct payload_t
{
  short temperature;
  boolean luminosite;
  unsigned short humidite;
  short temperature2;
  unsigned short gaz[8];
  unsigned long codeBarre1;
  unsigned long codeBarre2;
} payload_t;

#endif
