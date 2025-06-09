message("You are running qmake : Record.pri  ")

INCLUDEPATH +=$$PWD

SOURCES += \
     $$PWD/FFT/FFT.cpp \
    $$PWD/Comtrade/ComtradeAnalogData.cpp \
    $$PWD/Comtrade/ComtradeBinaryData.cpp \
    $$PWD/Comtrade/ComtradeDataBase.cpp \
    $$PWD/Comtrade/ComtradeFileGlobal.cpp \
    $$PWD/Comtrade/ComtradeMngr.cpp \
    $$PWD/Comtrade/ComtradeRateData.cpp \
    $$PWD/RtMemBuffer/ComplexMemBuffer_UnsignedShort.cpp \
    $$PWD/RtMemBuffer/MemBuffer.cpp \
    $$PWD/RtMemBuffer/MemBuffer_CPoint.cpp \
    $$PWD/RtMemBuffer/MemBuffer_Double.cpp \
    $$PWD/RtMemBuffer/MemBuffer_Float.cpp \
    $$PWD/RtMemBuffer/MemBuffer_Long.cpp \
    $$PWD/RtMemBuffer/MemBuffer_UnsignedShort.cpp \
    $$PWD/RtMemBuffer/RtMemBufScript.cpp \
    $$PWD/RtScriptBase/RtScriptBase.cpp \
    $$PWD/Algorithm/AlgorithmAPI.cpp \
    $$PWD/RtMemBuffer/RtMemBufferMngr.cpp \
    $$PWD/Draw/DrawGlobalDef.cpp \
    $$PWD/RtMemBuffer/RtMemBufferChannel.cpp \
    $$PWD/RecordGlobalDefine.cpp

HEADERS  += \
     $$PWD/FFT/FFT.h \
     $$PWD/FFT/FFTEx.h \
     $$PWD/FFT/xcomplex.h \
    $$PWD/Comtrade/ComtradeAnalogData.h \
    $$PWD/Comtrade/ComtradeBinaryData.h \
    $$PWD/Comtrade/ComtradeDataBase.h \
    $$PWD/Comtrade/ComtradeFileGlobal.h \
    $$PWD/Comtrade/ComtradeMngr.h \
    $$PWD/Comtrade/ComtradeRateData.h \
    $$PWD/RtMemBuffer/ComplexMemBuffer_UnsignedShort.h \
    $$PWD/RtMemBuffer/MemBuffer.h \
    $$PWD/RtMemBuffer/MemBuffer_CPoint.h \
    $$PWD/RtMemBuffer/MemBuffer_Double.h \
    $$PWD/RtMemBuffer/MemBuffer_Float.h \
    $$PWD/RtMemBuffer/MemBuffer_Long.h \
    $$PWD/RtMemBuffer/MemBuffer_UnsignedShort.h \
    $$PWD/RtMemBuffer/MemBufferDef.h \
    $$PWD/RtMemBuffer/RtMemBufScript.h \
    $$PWD/RtScriptBase/RtScriptBase.h \
    $$PWD/Algorithm/AlgorithmAPI.h \
    $$PWD/RtMemBuffer/RtMemBufferMngr.h \
    $$PWD/Draw/DrawGlobalDef.h \
    $$PWD/RtMemBuffer/RtMemBufferChannel.h \
    $$PWD/RecordGlobalDefine.h
     

