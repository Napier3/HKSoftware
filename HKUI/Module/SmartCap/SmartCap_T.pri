message("You are running qmake : Record.pri  ")

#INCLUDEPATH +=$$PWD

SOURCES += \
$$PWD/61850Cap/CapDevice/CapAnalysisConfig.cpp \
$$PWD/61850Cap/CapDevice/CapDevice6044.cpp \
$$PWD/61850Cap/CapDevice/CapDevice91.cpp \
$$PWD/61850Cap/CapDevice/CapDevice92.cpp \
$$PWD/61850Cap/CapDevice/CapDeviceBase.cpp \
$$PWD/61850Cap/CapDevice/CapDeviceChBase.cpp \
$$PWD/61850Cap/CapDevice/CapDeviceGoose.cpp \
$$PWD/61850Cap/CapDevice/CapDeviceGooseCh.cpp \
$$PWD/61850Cap/CapDevice/CapDeviceMngr.cpp \
$$PWD/61850Cap/CapDevice/CapDeviceSmvBase.cpp \
$$PWD/61850Cap/CapDevice/CapDeviceSmvCh.cpp \
$$PWD/61850Cap/CapGlobalDef.cpp \
$$PWD/61850Cap/CapThreadBase.cpp \
$$PWD/61850Cap/ProtocolBase/6044Frame.cpp \
$$PWD/61850Cap/ProtocolBase/61850FrameBase.cpp \
$$PWD/61850Cap/ProtocolBase/61850ParseFrameList.cpp \
$$PWD/61850Cap/ProtocolBase/91Frame.cpp \
$$PWD/61850Cap/ProtocolBase/92Frame.cpp \
$$PWD/61850Cap/ProtocolBase/BbInffor.cpp \
$$PWD/61850Cap/ProtocolBase/ByteBlock.cpp \
$$PWD/61850Cap/ProtocolBase/FrameBase.cpp \
$$PWD/61850Cap/ProtocolBase/FrameBaseList.cpp \
$$PWD/61850Cap/ProtocolBase/FrameDetail.cpp \
$$PWD/61850Cap/ProtocolBase/FrameMemBuffer.cpp \
$$PWD/61850Cap/ProtocolBase/GooseFrame.cpp \
$$PWD/61850Cap/ProtocolBase/Protocol61850.cpp \
$$PWD/61850Cap/ProtocolBase/Protocol61850Analysis.cpp \
$$PWD/61850Cap/ProtocolBase/ProtocolBase.cpp \
$$PWD/61850Cap/ProtocolBase/SmvFrameBase.cpp \
$$PWD/61850Cap/ProtocolBase/Stt/SttFrameMemBufferMngr.cpp \
$$PWD/61850Cap/ProtocolBase/Stt/SttRcdMemBufferMngr.cpp \
$$PWD/61850Cap/Record/CapDeviceChRecordMngr.cpp \
$$PWD/61850Cap/Record/CapViewAnalyse.cpp \
$$PWD/61850Cap/SttCapThread.cpp \
$$PWD/61850Cap/SttRcdComtradeFileWrite.cpp \
$$PWD/SmartCapCtrl.cpp \
$$PWD/X61850CapBase.cpp \
$$PWD/XIecDatasetSmartMatch.cpp \
$$PWD/XSmartCapFileWrite.cpp \
$$PWD/XSmartCapInterface.cpp \
$$PWD/XSmartCapMngr.cpp \
$$PWD/XSttCap_61850.cpp \
$$PWD/XSttIecfgDataEdit.cpp \
$$PWD/XSttRcdInitChDvmData.cpp \
    $$PWD/61850Cap/CapDevice/CapDeviceRcdCh.cpp \
    $$PWD/61850Cap/CapDevice/CapDeviceRecord.cpp \
    $$PWD/61850Cap/ProtocolBase/BinRcdFrame.cpp \
    $$PWD/61850Cap/SttRecordToComtradeTool.cpp

 

HEADERS  += \
$$PWD/61850Cap/CapDevice/CapAnalysisConfig.h \
$$PWD/61850Cap/CapDevice/CapDevice6044.h \
$$PWD/61850Cap/CapDevice/CapDevice91.h \
$$PWD/61850Cap/CapDevice/CapDevice92.h \
$$PWD/61850Cap/CapDevice/CapDeviceBase.h \
$$PWD/61850Cap/CapDevice/CapDeviceChBase.h \
$$PWD/61850Cap/CapDevice/CapDeviceGlobal.h \
$$PWD/61850Cap/CapDevice/CapDeviceGoose.h \
$$PWD/61850Cap/CapDevice/CapDeviceGooseCh.h \
$$PWD/61850Cap/CapDevice/CapDeviceMngr.h \
$$PWD/61850Cap/CapDevice/CapDeviceSmvBase.h \
$$PWD/61850Cap/CapDevice/CapDeviceSmvCh.h \
$$PWD/61850Cap/CapGlobalDef.h \
$$PWD/61850Cap/CapThreadBase.h \
$$PWD/61850Cap/ProtocolBase/6044Frame.h \
$$PWD/61850Cap/ProtocolBase/61850FrameBase.h \
$$PWD/61850Cap/ProtocolBase/61850ParseFrameList.h \
$$PWD/61850Cap/ProtocolBase/91Frame.h \
$$PWD/61850Cap/ProtocolBase/92Frame.h \
$$PWD/61850Cap/ProtocolBase/BbInffor.h \
$$PWD/61850Cap/ProtocolBase/ByteBlock.h \
$$PWD/61850Cap/ProtocolBase/FrameBase.h \
$$PWD/61850Cap/ProtocolBase/FrameBaseList.h \
$$PWD/61850Cap/ProtocolBase/FrameDetail.h \
$$PWD/61850Cap/ProtocolBase/FrameMemBuffer.h \
$$PWD/61850Cap/ProtocolBase/GooseFrame.h \
$$PWD/61850Cap/ProtocolBase/Protocol61850.h \
$$PWD/61850Cap/ProtocolBase/Protocol61850Analysis.h \
$$PWD/61850Cap/ProtocolBase/ProtocolBase.h \
$$PWD/61850Cap/ProtocolBase/ProtocolGlobalDef.h \
$$PWD/61850Cap/ProtocolBase/SmvFrameBase.h \
$$PWD/61850Cap/ProtocolBase/Stt/SttFrameMemBufferMngr.h \
$$PWD/61850Cap/ProtocolBase/Stt/SttRcdMemBufferMngr.h \
$$PWD/61850Cap/Record/CapDeviceChRecordMngr.h \
$$PWD/61850Cap/Record/CapViewAnalyse.h \
$$PWD/61850Cap/SttCapThread.h \
$$PWD/61850Cap/SttRcdComtradeFileWrite.h \
$$PWD/SmartCapCtrl.h \
$$PWD/X61850CapBase.h \
$$PWD/XIecDatasetSmartMatch.h \
$$PWD/XSmartCapFileWrite.h \
$$PWD/XSmartCapInterface.h \
$$PWD/XSmartCapMngr.h \
$$PWD/XSttCap_61850.h \
$$PWD/XSttIecfgDataEdit.h \
$$PWD/XSttRcdInitChDvmData.h \ 
    $$PWD/61850Cap/CapDevice/CapDeviceRcdCh.h \
    $$PWD/61850Cap/CapDevice/CapDeviceRecord.h \
    $$PWD/61850Cap/ProtocolBase/BinRcdFrame.h \
    $$PWD/61850Cap/SttRecordToComtradeTool.h

     

