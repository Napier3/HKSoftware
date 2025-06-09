// EpGlobalDefine_MODBUS.h
//////////////////////////////////////////////////////////////////////

#if !defined(_EPGLOBALDEFINE_MODBUS_H__)
#define _EPGLOBALDEFINE_MODBUS_H__

#include "..\ProtocolBase\EpFrameGroup.h"

#define EPCLASSID_MODBUS_BASE          0X00000100  //规约的D0~D7表示ASDU,D8~D23表示规约的类型

#define EPCLASSID_PROTOCOL_MODBUS      (EPCLASSID_PROTOCOL + EPCLASSID_MODBUS_BASE)

// static const CString g_strEpAsduInfOAddr = _T("o-addr");
// static const CString g_strEpAsduSIQ      = _T("siq");

#endif // !defined(_EPGLOBALDEFINE_MODBUS_H__)
