// EpGlobalDefine_MODBUS.h
//////////////////////////////////////////////////////////////////////

#if !defined(_EPGLOBALDEFINE_MODBUS_H__)
#define _EPGLOBALDEFINE_MODBUS_H__

#include "..\ProtocolBase\EpFrameGroup.h"

#define EPCLASSID_MODBUS_BASE          0X00000100  //��Լ��D0~D7��ʾASDU,D8~D23��ʾ��Լ������

#define EPCLASSID_PROTOCOL_MODBUS      (EPCLASSID_PROTOCOL + EPCLASSID_MODBUS_BASE)

// static const CString g_strEpAsduInfOAddr = _T("o-addr");
// static const CString g_strEpAsduSIQ      = _T("siq");

#endif // !defined(_EPGLOBALDEFINE_MODBUS_H__)
