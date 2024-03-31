cmake_minimum_required(VERSION 3.22)
project(MqttProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

include_directories(libs/MQTT-C/include
                    libs/tiny-json
                    common
                    app)

add_subdirectory(libs/MQTT-C)
add_subdirectory(libs/tiny-json)
add_subdirectory(common)
add_subdirectory(app)
