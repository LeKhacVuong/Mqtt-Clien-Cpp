//
// Created by lekhacvuong on 3/30/24.
//

#include <malloc.h>
#include "MqttClient.h"

mqttClient_t* mqttClientCreate(ConnectionInfo _info, publish_response_callback _callback){
    mqttClient_t* mqttClient = malloc(sizeof (mqttClient_t));
    if(!mqttClient){
        return NULL;
    }

    int sockfd = open_nb_socket(_info.brokerAddr, _info.port);
    if(sockfd < 0){
        printf("Failed to open socket\n");
        return NULL;
    }

    mqtt_init(&mqttClient->m_instance, sockfd, mqttClient->m_sendBuff, MQTT_BUFFER_SIZE,
              mqttClient->m_receiveBuff, MQTT_BUFFER_SIZE, _callback);

    mqtt_connect(&mqttClient->m_instance, _info.clientId, NULL, NULL, 0,
                 _info.userName, _info.userPassword, MQTT_CONNECT_CLEAN_SESSION, 400);

    if (mqttClient->m_instance.error != MQTT_OK) {
        printf("Connect to MQTT Broker failed with ERROR code %s", mqtt_error_str(mqttClient->m_instance.error));
        return NULL;
    }

    mqttClient->m_info = _info;

    return mqttClient;
}

int mqttSubscribe(mqttClient_t* _self, const char* _topic){

    mqtt_subscribe(&_self->m_instance, _topic, MQTT_QOS_USE);

    if (_self->m_instance.error != MQTT_OK) {
        printf("subscribe to topic failed with ERROR code %s", mqtt_error_str(_self->m_instance.error));
        return -1;
    }
    return 1;
}

int mqttUnsubscribe(mqttClient_t* _self, const char* _topic){

    mqtt_unsubscribe(&_self->m_instance, _topic);

    if (_self->m_instance.error != MQTT_OK) {
        printf("subscribe to topic failed with ERROR code %s", mqtt_error_str(_self->m_instance.error));
        return -1;
    }
    return 1;
}


int mqttPublish(mqttClient_t* _self, const char* _msg, uint32_t _len, const char* _topic){

    mqtt_publish(&_self->m_instance,  _topic, _msg, _len, MQTT_QOS_USE);

    if (_self->m_instance.error != MQTT_OK) {
        printf("Publish msg to topic failed with ERROR code %s", mqtt_error_str(_self->m_instance.error));
        return -1;
    }
    return 1;

}

int mqttReconnect(mqttClient_t* _self){
    mqtt_reconnect(&_self->m_instance);

    if (_self->m_instance.error != MQTT_OK) {
        printf("Reconnect to Broker failed with ERROR code %s", mqtt_error_str(_self->m_instance.error));
        return -1;
    }
    return 1;
}

int mqttIsError(mqttClient_t* _self){
    return _self->m_instance.error != MQTT_OK;
}

void mqttProcess(mqttClient_t* _self){
    mqtt_sync(&_self->m_instance);
}