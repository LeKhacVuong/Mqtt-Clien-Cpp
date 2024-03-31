cmake_minimum_required(VERSION 3.22)
project(mqttClient)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

add_library(mqttClient STATIC
        MqttClient.h
        MqttClient.c)

link_libraries(mqttClient mqttc)