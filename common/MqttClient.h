//
// Created by lekhacvuong on 3/16/24.
//

#ifndef BSS_SDK_MQTTCLIENT_H
#define BSS_SDK_MQTTCLIENT_H

#include "mqtt.h"
#include "posix_sockets.h"


enum MQTTPublishFlags MQTT_QOS_USE = MQTT_PUBLISH_QOS_0;

#define MQTT_BUFFER_SIZE  (2 * 1024)


#define MQTT_BROKER_ADDRESS         "hub-uat.selex.vn"
#define MQTT_CONNECTING_PORT        "1883"
#define MQTT_SELF_CLIENT_ID         "5"
#define MQTT_USER_NAME              "selex"
#define MQTT_PASSWORD               "selex"


typedef struct ConnectionInfo{
    const char* brokerAddr;
    const char* port;
    const char*clientId;
    const char* userName;
    const char*userPassword;
}ConnectionInfo;

ConnectionInfo g_connectionInfo = {
        .brokerAddr = MQTT_BROKER_ADDRESS,
        .port = MQTT_CONNECTING_PORT,
        .clientId = MQTT_SELF_CLIENT_ID,
        .userName = MQTT_USER_NAME,
        .userPassword = MQTT_PASSWORD,
};

typedef void (*publish_response_callback)(void** state, struct mqtt_response_publish *publish);

typedef struct mqttClient{
    struct mqtt_client m_instance;
    ConnectionInfo m_info;
    uint8_t m_sendBuff[MQTT_BUFFER_SIZE];
    uint8_t m_receiveBuff[MQTT_BUFFER_SIZE];
}mqttClient;

typedef struct mqttClient mqttClient_t;


mqttClient_t* mqttClientCreate(ConnectionInfo _info, publish_response_callback _callback);
int mqttSubscribe(mqttClient_t* _self, const char* _topic);
int mqttUnsubscribe(mqttClient_t* _self, const char* _topic);
int mqttPublish(mqttClient_t* _self, const char* _msg, uint32_t _len, const char* _topic);
int mqttReconnect(mqttClient_t* _self);
int mqttIsError(mqttClient_t* _self);
void mqttProcess(mqttClient_t* _self);




#endif //BSS_SDK_MQTTCLIENT_H

