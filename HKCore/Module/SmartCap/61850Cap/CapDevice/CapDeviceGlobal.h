//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDeviceGlobal.h

#pragma once

#include "../../Module/BaseClass/ExBaseList.h"

#define CPDCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00040000)
#define CPDCLASSID_EXLISTCLASS     (CLASSID_LISTCLASS + 0X00040000)

#define CPDCLASSID_DEVICE91       (CPDCLASSID_EXLISTCLASS + 0X00000001)
#define CPDCLASSID_DEVICE92       (CPDCLASSID_EXLISTCLASS + 0X00000002)
#define CPDCLASSID_DEVICE6044     (CPDCLASSID_EXLISTCLASS + 0X00000003)
#define CPDCLASSID_DEVICEGOOSE    (CPDCLASSID_EXLISTCLASS + 0X00000004)
#define CPDCLASSID_SMVCH          (CPDCLASSID_EXLISTCLASS + 0X00000005)
#define CPDCLASSID_GOOSECH        (CPDCLASSID_EXLISTCLASS + 0X00000006)
#define CPDCLASSID_DEVICERECORD   (CPDCLASSID_EXLISTCLASS + 0X00000007)
#define CPDCLASSID_RCDCH          (CPDCLASSID_EXLISTCLASS + 0X00000008)

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
#define CAP_RECORD_POINTS_GS  4000
#define  CAP_FFT_CAL_POINTS  1200
#define STT_CAP_SMV_SYN_RCD_MAX_COUNT  100

#define PROTOCOL_61850_TYPE_92      1
#define PROTOCOL_61850_TYPE_GOOSEOUT   2
#define PROTOCOL_61850_TYPE_60448   3
#define PROTOCOL_61850_TYPE_91      4
#define PROTOCOL_61850_TYPE_GOOSEIN   5
#define PROTOCOL_61850_TYPE_ANALOG  6
#define PROTOCOL_61850_TYPE_BINARY  7
#define PROTOCOL_61850_TYPE_NONE    0XFF
#define PROTOCOL_61850_TYPE_GOOSE   0x1F

#define MATCH_STATE_NONE			0		//未匹配
#define MATCH_STATE_SUCCESS			1		//匹配成功
#define MATCH_STATE_SURPLUS			2		//多余
#define MATCH_STATE_MISS			3		//缺少


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

#define WM_ADDCAPDEVICE				(WM_USER+1144)
#define WM_UPDATECAPDEVICE		(WM_USER+1145)
//2022-5-31  lijunqing
#define WM_UPDATE_GOOSE_SPY		(WM_USER+1146)
