//
// Created by lekhacvuong on 3/31/24.
//

#include "MqttClient.h"
#include "ctime"

mqttClient_t * g_mqttClient;

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}


void MqttCallback(void** state, struct mqtt_response_publish *publish){

}


int i = MQTT_BUFFER_SIZE;

int main(){

    while(!g_mqttClient){
        g_mqttClient = mqttClientCreate(g_connectionInfo, MqttCallback);
        mqttReconnect(g_mqttClient);
        delay(1000);
    }

    while (true){

    }

}
