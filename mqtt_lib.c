// mqtt_lib.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mqtt_lib.h"

#define QOS 0
#define TIMEOUT 10000L

static MQTTClient client;
static MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;


int messageArrived(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
    printf("Message arrived on topic: %s\n", topicName);
    printf("Message: %.*s\n", message->payloadlen, (char*)message->payload);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}


void mqtt_connect(const char *address, const char *clientID) {
    MQTTClient_create(&client, address, clientID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    if (MQTTClient_connect(client, &conn_opts) != MQTTCLIENT_SUCCESS) {
        fprintf(stderr, "Failed to connect to broker.\n");
        exit(EXIT_FAILURE);
    }
    MQTTClient_setCallbacks(client, NULL, NULL, messageArrived, NULL);
}


void mqtt_disconnect() {
    MQTTClient_disconnect(client, TIMEOUT);
    MQTTClient_destroy(&client);
}


void mqtt_subscribe(const char *topic) {
    int rc = MQTTClient_subscribe(client, topic, QOS);
    if (rc != MQTTCLIENT_SUCCESS) {
        fprintf(stderr, "Failed to subscribe to topic %s, return code %d\n", topic, rc);
    } else {
        printf("Subscribed to topic %s\n", topic);
    }
}


void mqtt_publish(const char *topic, const char *payload) {
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    pubmsg.payload = (void *)payload;
    pubmsg.payloadlen = strlen(payload);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;

    if (MQTTClient_publishMessage(client, topic, &pubmsg, NULL) != MQTTCLIENT_SUCCESS) {
        fprintf(stderr, "Failed to publish message.\n");
    } else {
        printf("Message published: %s\n", payload);
    }
}
