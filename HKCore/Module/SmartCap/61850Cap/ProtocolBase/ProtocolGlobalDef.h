#pragma once

#include "../../../../Module/BaseClass/ExBaseList.h"
//#include "../../../../Module/MemBuffer/CycleMemBuffer.h"
#include "../../../../Module/MemBuffer/XMemBufferBse.h"

#define STPROTOCOLCLASSID_BASECLASS        (CLASSID_BASECLASS+0x04000000)
#define STPROTOCOLCLASSID_LISTCLASS        (CLASSID_LISTCLASS+0x04000000)

#define STPROTCOLCLASSID_OWN_MASK          0X0000FFFF


#define STPROTOCOLCLASSID_BBINFOR           (STPROTOCOLCLASSID_BASECLASS + 0X00000000)
#define STPROTOCOLCLASSID_BYTEBLOCK         (STPROTOCOLCLASSID_LISTCLASS + 0X00000001)
#define STPROTOCOLCLASSID_BYTEBLOCKS        (STPROTOCOLCLASSID_LISTCLASS + 0X00000002)
#define STPROTOCOLCLASSID_FRAMEDETAIL       (STPROTOCOLCLASSID_LISTCLASS + 0X00000003)
#define STPROTOCOLCLASSID_FRAME             (STPROTOCOLCLASSID_LISTCLASS + 0X00000100)
#define STPROTOCOLCLASSID_FRAMELIST         (STPROTOCOLCLASSID_LISTCLASS + 0X00000200)

#define STPROTOCOLCLASSID_PROTOCOL          (STPROTOCOLCLASSID_LISTCLASS + 0X00001000)

#define STPROTOCOLCLASSID_FRAME91             (STPROTOCOLCLASSID_FRAME + 0X00000001)
#define STPROTOCOLCLASSID_FRAME92             (STPROTOCOLCLASSID_FRAME + 0X00000002)
#define STPROTOCOLCLASSID_FRAMEGS             (STPROTOCOLCLASSID_FRAME + 0X00000003)
#define STPROTOCOLCLASSID_FRAME6044           (STPROTOCOLCLASSID_FRAME + 0X00000004)

#define STCAPPARSE_DATA_MAX_COUNT   255

#define STCAPPARSE_CONSISTENCY_COUNT   12

typedef struct epTime64Ex
{
	WORD wYear;
	WORD wMonth;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
	WORD wMicrosecond;
}EPTIME64EX, *PEPTIME64EX;


inline BOOL Ep_IsProtocolClassID(UINT nClassID)
{
	return ((nClassID & STPROTOCOLCLASSID_PROTOCOL) == STPROTOCOLCLASSID_PROTOCOL);
}


typedef struct ep92ParseData_ASDU
{
	char SVID[64];
	long smpCnt;
	long confRev;
	long smpSynch;

}EP92PARSEDATA_ASDU, *PEP92PARSEDATA_ASDU;

/*
<data name="����λ"/>1
<data name="�汾��"/>1
<data name="PDU����"/>1
<data name="ͨ����"/>1
<data name="VLANID"/>1
<data name="VLAN ���ȼ�"/>1
<data name="ͬ��״̬"/>1
<data name="������"/>1
<data name="ASDU��Ŀ"/>1
<data name="Ŀ��MAC��ַ"/>1
<data name="SVID/LD Name"/>1
*/

typedef struct ep92ParseData
{
	long APDULen;
	long Num_ASDU;
	long SequenceOfASDU;
	long nChCount;
	//long nFirstPacket;
	long nTestMode;
	long VlanID;
	long VlanPr;

	BYTE Time[8];
	EP92PARSEDATA_ASDU Asdu[8];
}EP92PARSEDATA, *PEP92PARSEDATA;


typedef struct epGooseChData
{
	WORD wChType;
	long dwValue;
}EPGOOSECHDATA, *PEPGOOSECHDATA;

/************************************************************************
<data name="����λ"/>1
<data name="�汾��"/>1
<data name="PDU����"/>1
<data name="ͨ����"/>1
<data name="VLAN_ID"/>1
<data name="VLAN ���ȼ�"/>1
<data name="Ŀ��MAC��ַ"/>1
<data name="���ƿ�����"/>1
<data name="GOOSE ID"/>1
************************************************************************/
typedef struct epGooseParseData
{
	long APDULen;
	long TimeAllowedToLive;
	long stNO;
	long sqNO;
	long ClockFlag;
	long nTestMode;
	long nConfRev;
	long VLAN_ID;
	long VLAN_P;
	long ndsCom;
	double EventTimeSample;
	char   GOID[50];
	char   GORef[50];
	long   nChCnt;                               //GOOSEͨ��������
	char   GODataSet[50];                        //GOOSEDataSet add 20240509 wangtao

	EPGOOSECHDATA chData[STCAPPARSE_DATA_MAX_COUNT];
	long    nDataFlag[STCAPPARSE_DATA_MAX_COUNT];
}EPGOOSEPARSEDATA, *PEPGOOSEPARSEDATA;


typedef struct stCapParseData
{
// 	WORD  wValue;
// 	WORD  wValue2;
	WORD wChType;
	WORD wLength;
    long dwValue;
    long dwValue2;
}EPCAPPARSEDATA, *PEPCAPPARSEDATA;


typedef struct epCapParseDatas
{
	__int64 n64Time;  //���ݶ�Ӧ��ʱ��
	DWORD dwDatas;
	EPCAPPARSEDATA pDatas[STCAPPARSE_DATA_MAX_COUNT];     //�������������������
	int      nFirstPacket;//mym 2020-6-21  �жϵ�ǰ֡�Ƿ��ǵ�һ֡���ݣ��Ƿ����ڱȽϣ�
	int   nParseState; //0=no error  <0 is error

	//2020-06-27 ��ȡ����������
	char destMAC[6];
	char srcMAC[6];
	unsigned short APPID;

	union
	{
		EP92PARSEDATA   oData92; 
		EPGOOSEPARSEDATA   oDataGs; 
		//EPGOOSEPARSEDATA oDataGs; 
	};

}EPCAPPARSEDATAS, *PEPCAPPARSEDATAS;


typedef struct epBufferPos : public XMEMBUFFERBASEPOS//CYCLEMEMBUFFERPOS
{
	long nIndex;        //��ǰʹ�õĻ�����λ��
	long nPrevIndex;        //��ǰʹ�õĻ�����λ��
	long nFrameCurr;    //��ǰ֡ʹ�õĻ���������λ��
	DWORD dwState;      //״̬������ƥ���״̬
	volatile __int64 n64ID;      //��ص�ID������CaptureID
	DWORD nProtocol;      //��Լ����
	DWORD dwPara;
	LPVOID pItemData;
	PEPCAPPARSEDATAS pDatas;     //�������������������
}EPBUFFERPOS, *PEPBUFFERPOS;  


inline void Ep_BackBufferPos(EPBUFFERPOS &oSrc, EPBUFFERPOS &oDest)
{
	oDest.pBuffer = oSrc.pBuffer;
	oDest.nBufLength = oSrc.nBufLength;
	oDest.nIndex = oSrc.nIndex;
	oDest.nFrameCurr = oSrc.nFrameCurr;
	//oDest.dwState = oSrc.dwState;
	oDest.n64ID = oSrc.n64ID;
	oDest.nPrevIndex = oSrc.nPrevIndex;
	oDest.nProtocol = oSrc.nProtocol;
}

inline void Ep_InitBufferPos(EPBUFFERPOS &oBufferPos)
{
	memset(&oBufferPos, 0, sizeof(EPBUFFERPOS));
}

inline void Ep_InitBufferPos(PEPBUFFERPOS pBufferPos)
{
	memset(pBufferPos, 0, sizeof(EPBUFFERPOS));
}

//��û�����ʣ�µĳ���
inline BOOL Ep_IsBufferEnough(PEPBUFFERPOS pBufferPos, long nLen)
{
	return (nLen <= (pBufferPos->nBufLength - pBufferPos->nIndex));
}


//��û�����ʣ�µĳ���
inline long Ep_BufferLeave(PEPBUFFERPOS pBufferPos)
{
	return pBufferPos->nBufLength - pBufferPos->nIndex;
}

//��û�������ǰ��λ��
inline BYTE* Ep_GetBufferCurr(PEPBUFFERPOS pBufferPos)
{
	return pBufferPos->pBuffer + pBufferPos->nIndex;
}

//���֡��ʼ�Ļ�����
inline BYTE* Ep_GetFrameBufferBegin(PEPBUFFERPOS pBufferPos)
{
	return pBufferPos->pBuffer + pBufferPos->nIndex - pBufferPos->nFrameCurr;
}

//���֡�ĵ�ǰλ��
inline long Ep_GetFramePos(PEPBUFFERPOS pBufferPos)
{
	return pBufferPos->nFrameCurr;
}

//��ǰֵ��λ��
inline long Ep_GetValuePos(PEPBUFFERPOS pBufferPos)
{
	return pBufferPos->nPrevIndex;
}

//ƫ�ƻ�����λ��,������һ��֡�Ĳ���
inline long Ep_OffsetBufferCurr(PEPBUFFERPOS pBufferPos, long nOffset)
{
	pBufferPos->nPrevIndex = pBufferPos->nIndex;
	pBufferPos->nIndex += nOffset;
	pBufferPos->nFrameCurr += nOffset;
	return pBufferPos->nIndex;
}

inline BOOL Ep_NoInBuffer(PEPBUFFERPOS pBufferPos)
{
	return (0 > pBufferPos->nIndex || pBufferPos->nIndex >= pBufferPos->nBufLength);
}

inline BOOL Ep_NoInBuffer(PEPBUFFERPOS pBufferPos, BYTE *p)
{
	return ((pBufferPos->pBuffer > p) || (p >= pBufferPos->pBuffer + pBufferPos->nBufLength));
}

inline BOOL Ep_InBuffer(PEPBUFFERPOS pBufferPos)
{
	return (0 <= pBufferPos->nIndex && pBufferPos->nIndex < pBufferPos->nBufLength);
}

inline BOOL Ep_InBuffer(PEPBUFFERPOS pBufferPos, BYTE *p)
{
	return ((pBufferPos->pBuffer <= p) && (p < pBufferPos->pBuffer + pBufferPos->nBufLength));
}

//��ʼ����,��λ֡������������ʼ��λ��
inline void Ep_BeginParseFrame(PEPBUFFERPOS pBufferPos)
{
	pBufferPos->nFrameCurr = 0;
}

inline long Ep_GetParseFrameBuffer(PEPBUFFERPOS pBufferPos, BYTE **ppBuffer, long *pnLen)
{
	*pnLen = pBufferPos->nFrameCurr;
	*ppBuffer = pBufferPos->pBuffer + pBufferPos->nIndex - pBufferPos->nFrameCurr;
	return *pnLen;
}

inline BYTE Ep_BufferGetByte(PEPBUFFERPOS pBufferPos)
{
	return *Ep_GetBufferCurr(pBufferPos);
}

inline BYTE Ep_BufferReadByte(PEPBUFFERPOS pBufferPos)
{
	BYTE val = *Ep_GetBufferCurr(pBufferPos);
	Ep_OffsetBufferCurr(pBufferPos, 1);
	return val;
}

inline WORD Ep_BufferGetWord(PEPBUFFERPOS pBufferPos)
{
	return *((WORD*)Ep_GetBufferCurr(pBufferPos));
}

inline WORD Ep_BufferReadWord(PEPBUFFERPOS pBufferPos)
{
	WORD val = *((WORD*)Ep_GetBufferCurr(pBufferPos));
	Ep_OffsetBufferCurr(pBufferPos, 2);
	return val;
}


inline WORD Ep_BufferGetWord2(PEPBUFFERPOS pBufferPos)
{
	BYTE *p = Ep_GetBufferCurr(pBufferPos);
	WORD val = *(p);
	val = val << 8;
	val += *(p + 1);
	return val;
}

inline WORD Ep_BufferGetWord(BYTE *pBufferPos)//2023.8.12
{
	WORD val = *(pBufferPos);
	val = val << 8;
	val += *(pBufferPos + 1);
	return val;
}

inline WORD Ep_BufferReadWord2(PEPBUFFERPOS pBufferPos)
{
	WORD val = Ep_BufferGetWord2(pBufferPos);
	Ep_OffsetBufferCurr(pBufferPos, 2);
	return val;
}


inline DWORD Ep_BufferGetDWord(PEPBUFFERPOS pBufferPos)
{
	return *((DWORD*)Ep_GetBufferCurr(pBufferPos));
}

inline DWORD Ep_BufferReadDWord(PEPBUFFERPOS pBufferPos)
{
	DWORD val = *((DWORD*)Ep_GetBufferCurr(pBufferPos));
	Ep_OffsetBufferCurr(pBufferPos, 4);
	return val;
}

inline DWORD Ep_BufferGetDWord2(PEPBUFFERPOS pBufferPos)
{
	BYTE *p = Ep_GetBufferCurr(pBufferPos);
	DWORD val = *(p);
	val = val << 8;
	val += *(p + 1);
	val = val << 8;
	val += *(p + 2);
	val = val << 8;
	val += *(p + 3);
	return val;
}

inline DWORD Ep_BufferGetDWord(BYTE *pBuffValue)//2023.8.12 zhouhj
{
	DWORD val = *(pBuffValue);
	val = val << 8;
	val += *(pBuffValue + 1);
	val = val << 8;
	val += *(pBuffValue + 2);
	val = val << 8;
	val += *(pBuffValue + 3);
	return val;
}

inline DWORD Ep_BufferReadDWord2(PEPBUFFERPOS pBufferPos)
{
	DWORD val = Ep_BufferGetDWord2(pBufferPos);
	Ep_OffsetBufferCurr(pBufferPos, 4);
	return val;
}

inline DWORD Ep_BufferGetDWord(PEPBUFFERPOS pBufferPos, long nLen)
{
	if (nLen > 4 || nLen < 0)
	{
		nLen = 4;
	}

	BYTE *pCurr = Ep_GetBufferCurr(pBufferPos) + nLen - 1;
	BYTE *pEnd = Ep_GetBufferCurr(pBufferPos);
	DWORD val = 0;

	while (pCurr >= pEnd)
	{
		val = val << 8;
		val += *pCurr;
		pCurr--;
	}

	return val;
}

inline DWORD Ep_BufferReadDWord(PEPBUFFERPOS pBufferPos, long nLen)
{
	DWORD val = Ep_BufferGetDWord(pBufferPos, nLen);
	Ep_OffsetBufferCurr(pBufferPos, nLen);
	return val;
}

inline DWORD Ep_BufferGetDWord2(PEPBUFFERPOS pBufferPos, long nLen)
{
	if (nLen > 4 || nLen < 0)
	{
		nLen = 4;
	}

	BYTE *pCurr = Ep_GetBufferCurr(pBufferPos);
	BYTE *pEnd = pCurr + nLen;
	DWORD val = 0;

	while (pCurr < pEnd)
	{
		val = val << 8;
		val += *pCurr;
		pCurr++;
	}

	return val;
}

inline DWORD Ep_BufferReadDWord2(PEPBUFFERPOS pBufferPos, long nLen)
{
	DWORD val = Ep_BufferGetDWord2(pBufferPos, nLen);
	Ep_OffsetBufferCurr(pBufferPos, nLen);
	return val;
}

inline DWORD Ep_BufferReadFloat2(PEPBUFFERPOS pBufferPos, long nLen)//20220615 zhouhj GOOSEͨ���и���5���ֽڳ���,ʵ��ȡ��4���ֽڵĽ��
{
	int nOffset = 0;

	if (nLen>4)
	{
		nOffset = (nLen-4);
	}

	if (nLen > 4 || nLen < 0)
	{
		nLen = 4;
	}

	BYTE *pCurr = Ep_GetBufferCurr(pBufferPos) + nOffset;
	BYTE *pEnd = pCurr + nLen;
	DWORD val = 0;

	while (pCurr < pEnd)
	{
		val = val << 8;
		val += *pCurr;
		pCurr++;
	}

	Ep_OffsetBufferCurr(pBufferPos, nLen+nOffset);
	return val;
}

inline float Ep_BufferGetFloat(PEPBUFFERPOS pBufferPos)
{
	return *((float*)Ep_GetBufferCurr(pBufferPos));
}

inline float Ep_BufferReadFloat(PEPBUFFERPOS pBufferPos)
{
	float val = *((float*)Ep_GetBufferCurr(pBufferPos));
	Ep_OffsetBufferCurr(pBufferPos, 4);
	return val;
}

inline double Ep_BufferReadTime_8(PEPBUFFERPOS pBufferPos)
{
        UINT nsec = Ep_BufferReadDWord2(pBufferPos, 4);
        UINT nusec = Ep_BufferReadDWord2(pBufferPos, 4);
	double dTime = nsec + 1E-6*nusec;
	return dTime;
}

inline char* Ep_BufferReadString(PEPBUFFERPOS pBufferPos, long nLen, char *pString)
{
	if (pString == NULL)
	{
		return NULL;
	}

	if (nLen < 0 || nLen >= 100)
	{
		return NULL;
	}

	memcpy(pString, Ep_GetBufferCurr(pBufferPos), nLen);
	*(pString + nLen) = '\0';
	Ep_OffsetBufferCurr(pBufferPos, nLen);
	return pString;
}


#define EP_MATCH_STATE_MATCH        0X00000000  //ƥ��ɹ�
#define EP_MATCH_STATE_NO_MATCH     0X00000001  //ƥ�䲻�ɹ���������һ֡����������
#define EP_MATCH_STATE_NONE         0X00000002  //û��ƥ�������֡
#define EP_MATCH_STATE_BUFF_NOTFULL 0X00000004  //������������

inline void Ep_SetMatchStateNotFull(PEPBUFFERPOS pBufferPos)
{
	pBufferPos->dwState = EP_MATCH_STATE_BUFF_NOTFULL;
}

inline void Ep_SetMatchStateMatch(PEPBUFFERPOS pBufferPos)
{
	pBufferPos->dwState = EP_MATCH_STATE_MATCH;
}

inline void Ep_SetMatchStateNoMatch(PEPBUFFERPOS pBufferPos)
{
	pBufferPos->dwState = EP_MATCH_STATE_NO_MATCH;
}

inline void Ep_SetMatchStateNone(PEPBUFFERPOS pBufferPos)
{
	pBufferPos->dwState = EP_MATCH_STATE_NONE;
}

inline BOOL Ep_IsMatchStateNotFull(PEPBUFFERPOS pBufferPos)
{
	return (pBufferPos->dwState == EP_MATCH_STATE_BUFF_NOTFULL);
}

inline BOOL Ep_IsMatchStateMatch(PEPBUFFERPOS pBufferPos)
{
	return (pBufferPos->dwState == EP_MATCH_STATE_MATCH);
}

inline BOOL Ep_IsMatchStateNoMatch(PEPBUFFERPOS pBufferPos)
{
	return (pBufferPos->dwState == EP_MATCH_STATE_NO_MATCH);
}

inline BOOL Ep_IsMatchStateNone(PEPBUFFERPOS pBufferPos)
{
	return (pBufferPos->dwState == EP_MATCH_STATE_NONE);
}


#define WM_CAP_MONITOR  (WM_USER+1012)
#define WM_CAP_MONITORS  (WM_USER+1013)

//2022-6-13  lijunqing
#define WM_WRITE_XSMARTCAP_FILE  (WM_USER+1014)
