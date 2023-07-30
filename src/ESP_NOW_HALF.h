#ifndef ESPNOWSNDR_H
#define ESPNOWSNDR_H

#include "struct_message.h"

void espnowsndr_setup(int id, uint8_t mac_dest[]);
void espnowsndr_loop(struct_message* myDta);
#endif