// mqtt_lib.h
#ifndef MQTT_LIB_H
#define MQTT_LIB_H

#include "MQTTClient.h"


void mqtt_connect(const char *address, const char *clientID);
void mqtt_disconnect();

void mqtt_subscribe(const char *topic);
void mqtt_publish(const char *topic, const char *payload);

#endif // MQTT_LIB_H
