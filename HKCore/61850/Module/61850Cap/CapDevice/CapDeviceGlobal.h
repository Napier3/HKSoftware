//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDeviceGlobal.h

#pragma once

#include "..\..\..\..\Module\BaseClass\ExBaseList.h"

#define CPDCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00040000)
#define CPDCLASSID_EXLISTCLASS     (CLASSID_LISTCLASS + 0X00040000)

#define CPDCLASSID_DEVICE91       (CPDCLASSID_EXLISTCLASS + 0X00000001)
#define CPDCLASSID_DEVICE92       (CPDCLASSID_EXLISTCLASS + 0X00000002)
#define CPDCLASSID_DEVICE6044     (CPDCLASSID_EXLISTCLASS + 0X00000003)
#define CPDCLASSID_DEVICEGOOSE    (CPDCLASSID_EXLISTCLASS + 0X00000004)
#define CPDCLASSID_SMVCH          (CPDCLASSID_EXLISTCLASS + 0X00000005)
#define CPDCLASSID_GOOSECH        (CPDCLASSID_EXLISTCLASS + 0X00000006)

inline CString st_GetMacString(BYTE *pMac)
{
	CString strMac;
	strMac.Format(_T("%.2X-%.2X-%.2X-%.2X-%.2X-%.2X"), pMac[0], pMac[1], pMac[2], pMac[3], pMac[4], pMac[5]);
	return strMac;
}


#define WM_CAPDEVICECH_SELCHANGED  (WM_USER + 1630)
#define WM_CAPDEVICECH_DATACHANGED (WM_USER + 1631)

//监视一分钟  4000*60
#define CAP_RECORD_POINTS   240000

#define PROTOCOL_61850_TYPE_92      1
#define PROTOCOL_61850_TYPE_GOOSEOUT   2
#define PROTOCOL_61850_TYPE_60448   3
#define PROTOCOL_61850_TYPE_91      4
#define PROTOCOL_61850_TYPE_GOOSEIN   5
#define PROTOCOL_61850_TYPE_ANALOG  6
#define PROTOCOL_61850_TYPE_NONE    0XFF
#define PROTOCOL_61850_TYPE_GOOSE   0x1F


inline BOOL ep_IsTypeGoose(UINT nType)
{
	return ( (nType == PROTOCOL_61850_TYPE_GOOSEOUT) 
		|| (nType == PROTOCOL_61850_TYPE_GOOSEIN)
		|| (nType == PROTOCOL_61850_TYPE_GOOSE));
}

inline CString ep_Get61850ProtocolType(UINT nType)
{
	switch (nType)
	{
	case PROTOCOL_61850_TYPE_91:
		return _T("9-1");

	case PROTOCOL_61850_TYPE_92:
		return _T("9-2");

	case PROTOCOL_61850_TYPE_GOOSEIN:
		return _T("GOOSEIN");

	case PROTOCOL_61850_TYPE_GOOSEOUT:
		return _T("GOOSEOUT");

	case PROTOCOL_61850_TYPE_60448:
		return _T("IEC60044-8(FT3)");

	case PROTOCOL_61850_TYPE_ANALOG:
		return _T("Analog");

	case PROTOCOL_61850_TYPE_GOOSE:
		return _T("GOOSE");

	}

	return _T("------");
}
