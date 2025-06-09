#-------------------------------------------------
#
# Project created by QtCreator 2022-01-09T11:03:48
#
#-------------------------------------------------

QT       += core gui widgets network

DEFINES += UNICODE QT_DLL QT_WEBKIT_LIB QWT_DLL QT_XML_LIB QT_GUI_LIB QT_NETWORK_LIB QT_CORE_LIB
DEFINES += QT_HAVE_MMX QT_HAVE_3DNOW QT_HAVE_SSE QT_HAVE_MMXEXT QT_HAVE_SSE2 not_use_FreqCalFix50Hz
DEFINES += QT_THREAD_SUPPORT XML_USE_PUGIXML _PSX_IDE_QT_ _PSX_QT_WINDOWS_
DEFINES += CHECK_HEARTBEAT_TIMEOUT_MODE _PSX_QT_NO_USE_MIN_MAX_ USE_AXIS_CONFIG
DEFINES += STT_CMD_PARAS_HAS_GUIDEBOOK JSON_USE_ _PSX_QT_SRCFILE_GBK_
DEFINES += _not_use_CTCtrlCntrConfig Not_USE_IECCFGFILES _CRT_SECURE_NO_WARNINGS
DEFINES += _USE_IN_AT02D_MODE_ _no_use_RecordCompare_ XDrawMngr_NO_MemBufferDC
DEFINES += _STT_NOT_IN_TEST_SERVER_ MMS_LITE ETHERNET MVL_UCA _CONSOLE MOSI LEAN_T
DEFINES += SMPVAL_SUPPORT NOT_USE_ASSIST _NOT_USE_SttTestCntrThread_
DEFINES += _XSmartCap_use_SttRcdSocket_ _DVMDATASET_USE_ADDR_
#DEFINES  += CLIENT_TEST_ENGINE_IN_LOCAL
DEFINES  += WIN32_LEAN_AND_MEAN
DEFINES  += _USE_IN_IED_QT5
#DEFINES  += QT_USE_WEBKIT
#DEFINES  += QT_USE_WEBENGINE
DEFINES  += _USE_IN_IED_QT5  use_CSmartCapCtrl
DEFINES  += SttXcmdCh_AxAtsLib
#DEFINES  += SttXcmdCh_SttClientSocket
DEFINES  += _USE_SoftKeyBoard_
#DEFINES  += NOT_USE_XLANGUAGE


INCLUDEPATH += ../../../61850/mmslite/inc
INCLUDEPATH += ../../../Module/BaseClass
INCLUDEPATH += ../../../Module/OSInterface
INCLUDEPATH += ../../../Module/OSInterface/QT
INCLUDEPATH += $(QTDIR)/include/QtCore
INCLUDEPATH += $(QTDIR)/include/QtNetwork
INCLUDEPATH += $(QTDIR)/include/QtGui
INCLUDEPATH += $(QTDIR)/include/QtXml
INCLUDEPATH += $(QTDIR)/include/QtWebKit
INCLUDEPATH += $(QTDIR)/include
INCLUDEPATH += $(QTDIR)/include/ActiveQt
INCLUDEPATH += $(QTDIR)/mkspecs/default


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestCtrlCntrLinuxD
TEMPLATE = app
DESTDIR = "../../../PONOVO/PowerTest/Stt/Bin"

include(../../../61850/61850_T.pri)
include(../../../AutoTest/Module/AutoTest_T.pri)
include(../../../IotAtsMngr/Module/IotAtsMngr_T.pri)
include(../../../Module/Module_T.pri)
include(../../../Module/Record/Record_T.pri)
include(../../../Module/SmartCap/SmartCap_T.pri)

include(../../../Protocol/Module/Protocol_T.pri)
include(../../../IotProtoServer/Module/IotProtoServer_T.pri)
include(../../Module/Test_UI_330.pri)
include(../../Module/SttStudio_Module_T.pri)


SOURCES += main.cpp\
    SttTestCntrFrameLinux.cpp \
    SttTestCntrApplication.cpp \
    SttMacroParaEditFactoryEng.cpp \
    SttTestCntrApplicationAx.cpp

HEADERS  += \
    SttTestCntrFrameLinux.h \
    SttTestCntrApplication.h \
    SttMacroParaEditFactoryEng.h \
    SttTestCntrApplicationAx.h

FORMS +=

RESOURCES += \
    TestCtrlCntrLinuxD.qrc

#AtsLib
INCLUDEPATH += ../../Module/AtsLib
LIBS += -L../../Module/AtsLib -lAtsLib
