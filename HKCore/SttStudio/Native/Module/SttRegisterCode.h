
#pragma once

#ifdef _PSX_IDE_QT_
#include "../../Module/OSInterface/OSInterface.h"
#endif

CString stt_GetMachineRegCode();
__uint64 stt_GetMachineCode_U64();

//stt_GetMachineCode_U64:   Low 32 bit
unsigned long stt_GetMachineCode_U32();


/*
m_strMachineCode = stt_GetMachineCode();
unsigned __int64 n64Code = stt_GetMachineCode_U64();
unsigned n32Code = stt_GetMachineCode_U32();

*/

