#ifndef ENERINNO_ESP_NOW_SENDER_H
#define ENERINNO_ESP_NOW_SENDER_H

#include "struct_message.h"

void setup_esp_now_sender(int id);
void datasend_esp_now_sender(struct_message* myDta);

#endif