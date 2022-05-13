
#ifndef __PACKET_H__
#define __PACKET_H__

typedef struct payloadInfos_t
{
  short temperature;
  unsigned short humidite;
  short temperature2;
  unsigned short gaz[8];
} payloadInfos_t;

#endif
