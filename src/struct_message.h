#ifndef _STRUCT_MESSAGE_H
#define _STRUCT_MESSAGE_H

typedef struct struct_pairing {       // new structure for pairing
  uint8_t msgType;
  uint8_t id;
  uint8_t macAddr[6];
  uint8_t channel;
} struct_pairing;

typedef struct struct_message {
  uint8_t msgType;
  uint8_t id;

  float temp;
  float hum;

  unsigned int readingId;
  
  float _0x10;
  float _0x11;
  float _0x12;

  float _0x30;
  float _0x31;

  float _0x40;
  float _0x41;
  float _0x42;
  float _0x43;
  float _0x44;

  float _0x60;
  float _0x61;
  float _0x62;
  float _0x63;
  float _0x64;
  float _0x65;
  float _0x66;
  float _0x67;
  float _0x68;
  
  float _0x80;
  float _0x81;

  float _0x90;
  float _0x91;
  
  int error_code;
  int signal_streng;
  int battery;
  
  String lat;
  String lng;

  String sorfware_version;
  int sf_version;

} struct_message;

#endif