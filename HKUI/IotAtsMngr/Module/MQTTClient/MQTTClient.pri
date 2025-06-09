INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/Base64.h \
    $$PWD/Clients.h \
    $$PWD/Heap.h \
    $$PWD/LinkedList.h \
    $$PWD/Log.h \
    $$PWD/MQTTAsync.h \
    $$PWD/MQTTAsyncUtils.h \
    $$PWD/MQTTClient.h \
    $$PWD/MQTTClientPersistence.h \
    $$PWD/MQTTExportDeclarations.h \
    $$PWD/MQTTPacket.h \
    $$PWD/MQTTPacketOut.h \
    $$PWD/MQTTPersistence.h \
    $$PWD/MQTTPersistenceDefault.h \
    $$PWD/MQTTProperties.h \
    $$PWD/MQTTProtocol.h \
    $$PWD/MQTTProtocolClient.h \
    $$PWD/MQTTProtocolOut.h \
    $$PWD/MQTTReasonCodes.h \
    $$PWD/MQTTSubscribeOpts.h \
    $$PWD/MQTTTime.h \
    $$PWD/Messages.h \
    $$PWD/OsWrapper.h \
    $$PWD/Proxy.h \
    $$PWD/SHA1.h \
    $$PWD/SSLSocket.h \
    $$PWD/Socket.h \
    $$PWD/SocketBuffer.h \
    $$PWD/StackTrace.h \
    $$PWD/Thread.h \
    $$PWD/Tree.h \
    $$PWD/WebSocket.h \
    $$PWD/mutex_type.h \
    $$PWD/utf-8.h \
    $$PWD/VersionInfo.h

SOURCES += \
    $$PWD/MQTTTime.c \
    $$PWD/MQTTProtocolClient.c \
    $$PWD/Clients.c \
    $$PWD/utf-8.c \
    $$PWD/MQTTPacket.c \
    $$PWD/MQTTPacketOut.c \
    $$PWD/Messages.c \
    $$PWD/Tree.c \
    $$PWD/Socket.c \
    $$PWD/Log.c \
    $$PWD/MQTTPersistence.c \
    $$PWD/Thread.c \
    $$PWD/MQTTProtocolOut.c \
    $$PWD/MQTTPersistenceDefault.c \
    $$PWD/SocketBuffer.c \
    $$PWD/LinkedList.c \
    $$PWD/MQTTProperties.c \
    $$PWD/MQTTReasonCodes.c \
    $$PWD/Base64.c \
    $$PWD/SHA1.c \
    $$PWD/WebSocket.c \
    $$PWD/Proxy.c \
    $$PWD/MQTTClient.c \
    $$PWD/StackTrace.c \
    $$PWD/Heap.c
