// EpGlobalDefine_101.h
//////////////////////////////////////////////////////////////////////

#if !defined(_EPGLOBALDEFINE_101_H__)
#define _EPGLOBALDEFINE_101_H__

#include "..\ProtocolBase\EpFrameGroup.h"

// #define EPCLASSID_FRAME             (EPCLASSID_BASECLASS   + 0X00100000)
// #define EPCLASSID_PARSE_FRAME       (EPCLASSID_BASECLASS   + 0X00300000)
// #define EPCLASSID_PRODUCE_FRAME     (EPCLASSID_BASECLASS   + 0X00500000)
// #define EPCLASSID_FRAMES            (EPCLASSID_EXLISTCLASS + 0X00200000)
// #define EPCLASSID_PROCEDURE         (EPCLASSID_BASECLASS   + 0X00400000)
// #define EPCLASSID_PROCEDURES        (EPCLASSID_EXLISTCLASS + 0X00600000)
// #define EPCLASSID_PROTOCOL          (EPCLASSID_EXLISTCLASS + 0X01000000)

#define EPCLASSID_101_BASE          0X00000100  //规约的D0~D7表示ASDU,D8~D23表示规约的类型

#define EPCLASSID_PROTOCOL_101      (EPCLASSID_PROTOCOL + EPCLASSID_101_BASE)

#define EPCLASSID_101_TFRAME_68_GROUP      (EPCLASSID_101_BASE + 0X00000400)
#define EPCLASSID_101_TFRAME_68            (EPCLASSID_101_BASE + 0X00000800)
#define EPCLASSID_101_TFRAME_68_ASDUBASE   (EPCLASSID_101_BASE + 0X00001000)

#define EPCLASSID_101_FRAME_68_ASDU01      (EPCLASSID_101_BASE + 0X00000001)
#define EPCLASSID_101_FRAME_68_ASDU09      (EPCLASSID_101_BASE + 0X00000009)
#define EPCLASSID_101_FRAME_68_ASDU0D      (EPCLASSID_101_BASE + 0X0000000D)
#define EPCLASSID_101_FRAME_68_ASDU14      (EPCLASSID_101_BASE + 0X00000014)
#define EPCLASSID_101_FRAME_68_ASDU1E      (EPCLASSID_101_BASE + 0X0000001E)
#define EPCLASSID_101_FRAME_68_ASDU24      (EPCLASSID_101_BASE + 0X00000024)
#define EPCLASSID_101_FRAME_68_ASDU2E      (EPCLASSID_101_BASE + 0X0000002E)
#define EPCLASSID_101_FRAME_68_ASDU30      (EPCLASSID_101_BASE + 0X00000030)
#define EPCLASSID_101_FRAME_68_ASDU46      (EPCLASSID_101_BASE + 0X00000046)
#define EPCLASSID_101_FRAME_68_ASDU64      (EPCLASSID_101_BASE + 0X00000064)
#define EPCLASSID_101_FRAME_68_ASDU67      (EPCLASSID_101_BASE + 0X00000067)

#define EPCLASSID_104_TFRAME_68_S          (EPCLASSID_101_BASE + 0X000000F0)
#define EPCLASSID_104_TFRAME_68_U          (EPCLASSID_101_BASE + 0X000000F1)
#define EPCLASSID_101_TFRAME_E5            (EPCLASSID_101_BASE + 0X000000F2)
#define EPCLASSID_101_TFRAME_10            (EPCLASSID_101_BASE + 0X000000F3)
#define EPCLASSID_104_TFRAME_68_I          (EPCLASSID_101_BASE + 0X000000F4)
#define EPCLASSID_TFRAME_EMPTY             (EPCLASSID_101_BASE + 0X000000FF)

//////////////////////////////////////////////////////////////////////////
//101全局函数
/*
DIR = D7		传输方向位 =0：表示报文是主站向子站传输  =1：表示报文是子站向主站传输。
PRM = D6		启动报文位 =0：从动站,报文为确认报文或响应报文  =1：启动站，报文为发送或请求报文
FCB/ACD =  D5	
	FCB			帧计数位：     启动站向从动站传输,启动站向从动站传输新一轮的发送/确认、请求/响应服务时，将前一轮FCB取相反值
	ACD			帧计数有效位 ：启动站向从动站传输 =0：表示FCB变化无效  =1：表示FCB变化有效
FCV/DFC = D4	 
	FCV			要求访问位 ：主站做从动站时ACD位无实际意义，ACD=0。
				子站做从动站时ACD=0：表示子站无1级用户数据;	ACD=1：表示子站有1级用户数据，希望向主站传输
	DCF			数据流控制位：从动站向启动站传输   =0：表示子站可以继续接收数据   =1：表示子站数据区满，无法接收新数据
功能码 = D3-D0
*/
inline void Ep101_CalControl(BYTE byteDIR, BYTE bytePRM, BYTE byteFCB_ACD, BYTE byteFCV_DFC, BYTE byteFuncCode, BYTE *byteControl)
{
	*byteControl = ( (byteDIR & 0x01) << 7) + ( (bytePRM & 0x01) << 6) + ( (byteFCB_ACD & 0x01) << 5)
		+ ( (byteFCV_DFC & 0x01) << 4) + (byteFCV_DFC & 0x0F);
}

inline void Ep101_CalControl(BYTE byteControl, BYTE *byteDIR, BYTE *bytePRM, BYTE *byteFCB_ACD, BYTE *byteFCV_DFC, BYTE *byteFuncCode)
{
	*byteDIR = (byteControl >> 7) & 0x01;
	*bytePRM = (byteControl >> 6) & 0x01;
	*byteFCB_ACD = (byteControl >> 5) & 0x01;
	*byteFCV_DFC = (byteControl >> 4) & 0x01;
	*byteFuncCode = byteControl & 0x0F;
}


inline long Ep101_GetNormalizationValue(const BYTE *byASDU, float &fValue, float fMinValue, float fMaxValue)
{
	WORD wValue;
	BYTE byLow = *byASDU;
	BYTE byHigh = *(byASDU + 1);
	wValue = MAKEWORD(byLow, byHigh);
	fValue = 0.0f;

	if ((wValue & 0x8000) != 0)
	{
		// 负数			
		wValue -= 1;
		wValue = ~wValue;			
		wValue &= 0x7FFF;
		fValue = (fMaxValue + fMinValue)/2.0f - ((fMaxValue - fMinValue)/2.0f) * ((float)wValue/32767.0f);
	}
	else
	{
		fValue = (fMaxValue + fMinValue)/2.0f + ((fMaxValue - fMinValue)/2.0f) * ((float)wValue/32767.0f);
	}

	return 2;
}

inline long Ep101_GetNormalizationValue(const BYTE *byASDU, float &fValue)
{
	WORD wValue;
	BYTE byLow = *byASDU;
	BYTE byHigh = *(byASDU + 1);
	wValue = MAKEWORD(byLow, byHigh);
	fValue = 0.0f;

	if ((wValue & 0x8000) != 0)
	{		// 负数
		wValue -= 1;
		wValue = ~wValue;			
		wValue &= 0x7FFF;
	}

	fValue = wValue;

	return 2;
}

inline long Ep101_GetIEEE754Value(const BYTE *byASDU, float &fValue)
{
// 	unsigned char tmp_char[4];
// 	tmp_char[0]=byASDU[0];
// 	tmp_char[1]=byASDU[1];
// 	tmp_char[2]=byASDU[2];
// 	tmp_char[3]=byASDU[3];
// 	fValue = *((float *)tmp_char);
	fValue = *( (float*) byASDU);
	return 4;
}

inline long Ep101_GetODDRValue(const BYTE *byASDU, long nAddrLen, long &nODDR)
{
	if (nAddrLen == 1)
	{// 1字节
		nODDR = *byASDU;
	}
	else if (nAddrLen == 2)
	{// 2字节
		BYTE byLow = *byASDU;
		BYTE byHigh = *(byASDU+1);
		nODDR = MAKEWORD(byLow, byHigh);
	}
	else
	{// 3字节
		nODDR = ((*(byASDU+2)) << 16) +  ((*(byASDU+1)) << 8) + *byASDU;
		BYTE byLow = *byASDU;
		BYTE byMiddle = *(byASDU+1);
		BYTE byHigh = *(byASDU+2);
		nODDR = MAKELONG(MAKEWORD(byLow, byMiddle), MAKEWORD(byHigh, 0x00));
	}

	return nAddrLen;
}

inline void Ep101_InitRange(WORD &wVal, WORD wMax, WORD wMin)
{
	if (wVal > wMax)
	{
		wVal = wMax;
	}

	if (wVal < wMin)
	{
		wVal = wMin;
	}
}

inline long Ep101_GetCP56Time2aValue(const BYTE *byASDU, EPTIME64 &tm)
{
	tm.tm[0] = *byASDU;
	tm.tm[1] = *(byASDU+1);
//	DWORD dwMillTime = ( (*(byASDU+1)) << 8) + *byASDU;
//	tm.wMilliseconds = (WORD)(dwMillTime%1000);
//	tm.wSecond = (WORD)(dwMillTime/1000);
//	Ep101_InitRange(tm.wSecond, 59, 0);

	tm.tm[2] = *(byASDU+2) & 0x3F;
//	BYTE byte1 = *(byASDU+2);
//	tm.wMinute = byte1 & 0x3F;
//	Ep101_InitRange(tm.wMinute, 59, 0);

	tm.tm[3] = *(byASDU+3) & 0x1F;
//	BYTE byte2 =*(byASDU+3);
//	tm.wHour = byte2 & 0x1F;
//	Ep101_InitRange(tm.wHour, 23, 0);

	tm.tm[4] = *(byASDU+4) & 0x1F;
//	BYTE byte3 = *(byASDU+4);
//	tm.wDayOfWeek = (byte3 & 0xE0) >> 5;
//	tm.wDayOfMonth = byte3 & 0x1F;
//	Ep101_InitRange(tm.wDayOfWeek, 7, 0);
//	Ep101_InitRange(tm.wDayOfMonth, 31, 0);

	tm.tm[5] = *(byASDU+5) & 0x0F;
//	BYTE byte4 = *(byASDU+5);
//	tm.wMonth = byte4 & 0x0F;
//	Ep101_InitRange(tm.wDayOfMonth, 12, 0);

	BYTE byte5 = *(byASDU+6);
	WORD wYear = byte5 & 0x7F;
	Ep101_InitRange(wYear, 99, 0);
	//tm.wYear += 2000;
	*(WORD*)(&tm.tm[6]) = wYear + 2000;

	return 7;
}

inline void Ep101_GetVSQValue(BYTE byValue, long &nSQ, long &nNum)
{
	// 解析VSQ
	nSQ = (byValue & 0x80) >> 7;
	nNum = byValue & 0x7F;
}

inline void Ep101_GetSIQValue(BYTE byValue, long &nSPI, long &nBL, long &nSB, long &nNT, long &nIV)
{
	nSPI = (byValue & 0x01);
	nBL = (byValue & 0x10) >> 4;
	nSB = (byValue & 0x20) >> 5;
	nNT = (byValue & 0x40) >> 6;
	nIV = (byValue & 0x80) >> 7;
}

inline void Ep101_GetQDSValue(BYTE byValue, long &nOV, long &nBL, long &nSB, long &nNT, long &nIV)
{
	nOV = (byValue & 0x01);
	nBL = (byValue & 0x10) >> 4;
	nSB = (byValue & 0x20) >> 5;
	nNT = (byValue & 0x40) >> 6;
	nIV = (byValue & 0x80) >> 7;
}

inline void Ep101_GetQOSValue(BYTE byValue, long &nQL, long &nSE)
{
	nSE = (byValue & 0x80) >> 7;
	nQL = byValue & 0x7F;
}


inline void Ep101_GetQOCValue(BYTE byValue, long &nQU, long &nSE)
{
	nQU = (byValue & 0x7C) >> 2;
	nSE = (byValue & 0x80) >> 7;
}

inline void Ep101_GetDCOValue(BYTE byValue, long &nDCS, long &nQU, long &nSE)
{
	nDCS = byValue & 0x03;

	Ep101_GetQOCValue(byValue, nQU, nSE);
}

inline void Ep101_GetRCOValue(BYTE byValue, long &nRCS, long &nQU, long &nSE)
{
	nRCS = byValue & 0x03;
	Ep101_GetQOCValue(byValue, nQU, nSE);
}


//////////////////////////////////////////////////////////////////////////
//

#endif // !defined(_EPGLOBALDEFINE_101_H__)
