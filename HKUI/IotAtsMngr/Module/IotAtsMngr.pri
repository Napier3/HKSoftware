INCLUDEPATH +=$$PWD

#for windows
include(MQTTClient/MQTTClient.pri)

SOURCES +=  \
    $$PWD/SttMqttClientEngineConfig.cpp \
    $$PWD/SttMqttClient.cpp \
    $$PWD/SttMqttTopicParser.cpp \
    $$PWD/DeviceMngr/SttXDevice.cpp \
    $$PWD/DeviceMngr/SttXDeviceMngr.cpp



HEADERS += \
    $$PWD/MqttCmmInterface.h \
    $$PWD/SttMqttClientEngineConfig.h \
    $$PWD/SttMqttClient.h \
    $$PWD/SttMqttTopicParser.h \
    $$PWD/DeviceMngr/SttXDevice.h \
    $$PWD/DeviceMngr/SttXDeviceMngr.h
    

