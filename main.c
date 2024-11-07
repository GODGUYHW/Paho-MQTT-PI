#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTTClient.h"
#define ADDRESS     "broker.emqx.io:1883"  // Replace with your broker's address
#define CLIENTID    "RaspberryPiClient"
#define TOPIC       "pi/test1"
#define PAYLOAD     "Hello MQTT!"

// main.c
#include <stdio.h>
#include "mqtt_lib.h"

int main() {
    //MQTT broker
    mqtt_connect(ADDRESS, CLIENTID);

    // Subscribe to a topic
    mqtt_subscribe(TOPIC);


    mqtt_publish(TOPIC, PAYLOAD);


    printf("Press Enter to exit...\n");
    getchar();

    mqtt_disconnect();

    return 0;
}
