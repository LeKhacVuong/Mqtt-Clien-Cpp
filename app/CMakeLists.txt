cmake_minimum_required(VERSION 3.22)
project(MqttClient)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

add_executable(mqttApp MqttApp.cpp)

target_link_libraries(mqttApp mqttClient)

