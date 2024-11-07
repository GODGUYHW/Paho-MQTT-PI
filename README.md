Change this in main.c to your mqtt.

#define ADDRESS     "broker.emqx.io:1883"  // Replace with your broker's address

#define CLIENTID    "RaspberryPiClient"

#define TOPIC       "pi/test1"

#define PAYLOAD     "Hello MQTT!"

and then use this command 

gcc -c mqtt_lib.c -o mqtt_lib.o -lpaho-mqtt3c

ar rcs libmqtt_lib.a mqtt_lib.o

to compile mqtt_lib.c into Library (libmqtt_lib.a)

then use this command gcc main.c -L. -lmqtt_lib -lpaho-mqtt3c -o mqtt_program

to compile main.c and link with libmqtt_lib.a

run ./mqtt_program
