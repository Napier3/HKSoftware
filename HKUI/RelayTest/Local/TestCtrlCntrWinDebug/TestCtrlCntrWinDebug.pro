#-------------------------------------------------
#
# Project created by QtCreator 2024-07-09T09:04:00
#
#-------------------------------------------------

QT       += core gui widgets axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestCtrlCntrWin
TEMPLATE = app


INCLUDEPATH += ../../../Module/BaseClass
INCLUDEPATH += ../../../Module/OSInterface
INCLUDEPATH += ../../../Module/OSInterface/QT
INCLUDEPATH += ../../../61850/mmslite/inc
INCLUDEPATH += $(QTDIR)/include/QWT
INCLUDEPATH += $(QTDIR)/include/QtCore
INCLUDEPATH += $(QTDIR)/include/QtNetwork
INCLUDEPATH += $(QTDIR)/include/QtGui
INCLUDEPATH += $(QTDIR)/include/QtXml
INCLUDEPATH += $(QTDIR)/include/QtWebKit
INCLUDEPATH += $(QTDIR)/include
INCLUDEPATH += $(QTDIR)/include/ActiveQt
INCLUDEPATH += $(QTDIR)/mkspecs/default
#INCLUDEPATH += ./GeneratedFiles

DEFINES += UNICODE QT_DLL QT_WEBKIT_LIB QWT_DLL QT_XML_LIB QT_GUI_LIB QT_NETWORK_LIB QT_CORE_LIB
DEFINES += QT_HAVE_MMX QT_HAVE_3DNOW QT_HAVE_SSE QT_HAVE_MMXEXT QT_HAVE_SSE2
DEFINES += QT_THREAD_SUPPORT XML_USE_PUGIXML _PSX_IDE_QT_ _PSX_QT_WINDOWS_
DEFINES += CHECK_HEARTBEAT_TIMEOUT_MODE _PSX_QT_NO_USE_MIN_MAX_ USE_AXIS_CONFIG
DEFINES += STT_CMD_PARAS_HAS_GUIDEBOOK JSON_USE_ _PSX_QT_SRCFILE_GBK_
DEFINES += _not_use_CTCtrlCntrConfig Not_USE_IECCFGFILES _CRT_SECURE_NO_WARNINGS
#DEFINES += _USE_IN_AT02D_MODE_  use_CSmartCapCtrl
DEFINES +=  _no_use_RecordCompare_ XDrawMngr_NO_MemBufferDC
DEFINES += _STT_NOT_IN_TEST_SERVER_ MMS_LITE ETHERNET MVL_UCA _CONSOLE MOSI LEAN_T
DEFINES += SMPVAL_SUPPORT NOT_USE_ASSIST _NOT_USE_SttTestCntrThread_
DEFINES += _XSmartCap_use_SttRcdSocket_ _DVMDATASET_USE_ADDR_
#DEFINES  += CLIENT_TEST_ENGINE_IN_LOCAL
DEFINES  += WIN32_LEAN_AND_MEAN
DEFINES  += _USE_IN_IED_QT5
DEFINES  += SttXcmdCh_AxAtsLib
#DEFINES  += SttXcmdCh_SttClientSocket

include(../../../61850/61850_T.pri)
include(../../../AutoTest/Module/AutoTest_T.pri)
include(../../../IotAtsMngr/Module/IotAtsMngr_T.pri)
include(../../../Module/Module_T.pri)
include(../../../Protocol/Module/Protocol_T.pri)
include(../../../IotProtoServer/Module/IotProtoServer_T.pri)


#include(../../Module/Test_UI.pri)
include(../../Module/TestUI/TestUI_Module.pri)
include(../../Module/UI/IEC61850Config/Test_IEC61850Config.pri)
include(../../Module/UI/SCL/Test_SCL.pri)
include(../../Module/UI/Module/CharLibWidget/CharLib.pri)
#include(../../Module/UI/VoltageTimeTypeSectorMode/Test_VoltageTimeTypeSectorMode.pri)

include(../../Module/UI/Manual/Test_Manual.pri)
include(../../Module/UI/State/Test_State.pri)

include(../../Module/SttStudio_Module_T.pri)


SOURCES += main.cpp\
    ../TestCtrlCntrWin/SttTestCntrApplication.cpp \
    ../TestCtrlCntrWin/SttTestCntrFrameWin.cpp \
    SttMacroParaEditFactoryDebug.cpp \
    ../TestCtrlCntrWin/SttTestCntrApplicationAx.cpp


HEADERS  +=  \
    ../TestCtrlCntrWin/SttTestCntrApplication.h \
    ../TestCtrlCntrWin/SttTestCntrFrameWin.h \
    SttMacroParaEditFactoryDebug.h \
    ../TestCtrlCntrWin/SttTestCntrApplicationAx.h




FORMS    += \

#$(QTDIR)\lib\qtmaind.lib $(QTDIR)\lib\QtWebKitd4.lib $(QTDIR)\lib\QtXmld4.lib $(QTDIR)\lib\QtGuid4.lib $(QTDIR)\lib\QtNetworkd4.lib $(QTDIR)\lib\QtCored4.lib $(QTDIR)\lib\qwtd.lib QAxContainerd.lib
LIBS += -L$(QTDIR)\lib
INCLUDEPATH += ../../Module/AtsLib
LIBS += -L../../Module/AtsLib #-lAtsLib

CONFIG(debug, debug|release) {
    LIBS += -lqwtd
    LIBS += -lAtsLibd
}
CONFIG(release, debug|release) {
    LIBS += -lqwt
    LIBS += -lAtsLib
}


DESTDIR = "../../../PONOVO\PowerTest\Stt56\Bin"

win32
{
    DEFINES += _WIN32 _CRT_SECURE_NO_WARNINGS _SCL_SECURE_NO_WARNINGS
#    LIBS += -Ldll -lws2_32
#    LIBS += -lWs2_32
#    LIBS += -lAdvapi32

}

win32: QMAKE_CXXFLAGS_RELEASE -= -Zc:strictStrings
win32: QMAKE_CFLAGS_RELEASE -= -Zc:strictStrings
win32: QMAKE_CFLAGS -= -Zc:strictStrings
win32: QMAKE_CXXFLAGS -= -Zc:strictStrings

