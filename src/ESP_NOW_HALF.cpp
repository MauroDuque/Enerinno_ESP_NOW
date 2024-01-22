#include <Arduino.h>
#include <esp_now.h>
#include <EEPROM.h>
#include "struct_message.h"

int BOARD_ID = 99; // Sensor 1 Temperature water outlet ID 7 || Temperature water inlet ID 6
bool last_status = false;

uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// Create a struct_message called myData
struct_message myData;

// Create peer interface
esp_now_peer_info_t peerInfo;

enum MessageType {PAIRING, DATA,};
unsigned int readingId = 0; 

bool status_OnDataSent() {
  return last_status;
}

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  last_status = ESP_NOW_SEND_SUCCESS;
}

void espnowsndr_setup(int id, uint8_t mac_dest[]) {
  memcpy(broadcastAddress, mac_dest, 6);
  
  Serial.print("MAC Destine: ");
  for (int i = 0; i < 6; i++) {
    Serial.print(broadcastAddress[i], HEX);
    if (i < 5) {
      Serial.print(":");
    }
  }
  Serial.println();


  BOARD_ID = id;

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

String espnowsndr_loop(struct_message* myDta) {
    myData.msgType = DATA;
    myData.id = BOARD_ID;
    myData.temp = myDta->temp;
    myData.hum = myDta->hum;

    myData._0x10 = myDta->_0x10;
    myData._0x11 = myDta->_0x11;
    myData._0x12 = myDta->_0x12;

    myData._0x30 = myDta->_0x30;
    myData._0x31 = myDta->_0x31;

    myData._0x40 = myDta->_0x40;
    myData._0x41 = myDta->_0x41;
    myData._0x43 = myDta->_0x42;
    myData._0x43 = myDta->_0x43;
    myData._0x44 = myDta->_0x44;

    myData._0x60 = myDta->_0x60;
    myData._0x61 = myDta->_0x61;
    myData._0x62 = myDta->_0x62;
    myData._0x63 = myDta->_0x63;
    myData._0x64 = myDta->_0x64;
    myData._0x65 = myDta->_0x65;
    myData._0x66 = myDta->_0x66;
    myData._0x67 = myDta->_0x67;

    myData._0x80 = myDta->_0x80;
    myData._0x81 = myDta->_0x81;

    myData._0x90 = myDta->_0x90;
    myData._0x91 = myDta->_0x91;

    myData.error_code = myDta->error_code;
    myData.signal_streng = myDta->signal_streng;
    myData.battery = myDta->battery;

    myData.lat = myDta->lat;
    myData.lng = myDta->lng;

    myData.sorfware_version = myDta->sorfware_version;
    myData.sf_version = myDta->sf_version;

    myData.readingId = readingId++;

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  
  if (result == ESP_OK) {
    return "Sent with success";
  } else if (result == ESP_ERR_ESPNOW_NOT_INIT) {
    return "ESP-NOW not initialized";
  } else if (result == ESP_ERR_ESPNOW_ARG) {
    return "Invalid argument";
  } else if (result == ESP_ERR_ESPNOW_INTERNAL) {
    return "Internal error occurred";
  } else if (result == ESP_ERR_ESPNOW_NO_MEM) {
    return "Memory allocation failed";
  } else if (result == ESP_ERR_ESPNOW_NOT_FOUND) {
    return "Peer not found";
  } else if (result == ESP_ERR_ESPNOW_FULL) {
    return "Internal buffer is full";
  // } else if (result == ESP_ERR_ESPNOW_NOT_SUPPORT) {
  //   return "ESP-NOW not supported";
  // } else if (result == ESP_ERR_ESPNOW_ABORT) {
  //   return "Sending operation aborted";
  // } else if (result == ESP_ERR_ESPNOW_RST) {
  //   return "ESP-NOW reset";
  } else {
    return "Unknown error";
  }
}
