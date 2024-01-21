#ifndef ESP_NOW_HALF_H
#define ESP_NOW_HALF_H
#include <Arduino.h>
#include "struct_message.h"

void espnowsndr_setup(int id, uint8_t mac_dest[]);
String espnowsndr_loop(struct_message* myDta);
#endif