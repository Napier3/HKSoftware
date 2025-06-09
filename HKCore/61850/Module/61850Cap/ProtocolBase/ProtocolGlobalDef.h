#pragma once

#include "..\..\..\..\Module\BaseClass\ExBaseList.h"
//#include "..\..\..\..\Module\MemBuffer\CycleMemBuffer.h"
#include "..\..\..\..\Module\MemBuffer\XMemBufferBse.h"

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

typedef struct stCapParseData
{
// 	WORD  wValue;
// 	WORD  wValue2;
	WORD wChType;
	WORD wLength;
	long dwValue;
	long dwValue2;
}EPCAPPARSEDATA, *PEPCAPPARSEDATA;

#define STCAPPARSE_DATA_MAX_COUNT 255
typedef struct epCapParseDatas
{
	DWORD dwDatas;
	EPCAPPARSEDATA pDatas[STCAPPARSE_DATA_MAX_COUNT];     //解析出来到的相关数据
}EPCAPPARSEDATAS, *PEPCAPPARSEDATAS;


typedef struct epBufferPos : public XMEMBUFFERBASEPOS//CYCLEMEMBUFFERPOS
{
	long nIndex;        //当前使用的缓冲区位置
	long nPrevIndex;        //当前使用的缓冲区位置
	long nFrameCurr;    //当前帧使用的缓冲区索引位置
	DWORD dwState;      //状态，例如匹配的状态
	volatile __int64 n64ID;      //相关的ID，例如CaptureID
	DWORD nProtocol;      //规约类型
	DWORD dwPara;
	LPVOID pItemData;
	PEPCAPPARSEDATAS pDatas;     //解析出来到的相关数据
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

//获得缓冲区剩下的长度
inline BOOL Ep_IsBufferEnough(PEPBUFFERPOS pBufferPos, long nLen)
{
	return (nLen <= (pBufferPos->nBufLength - pBufferPos->nIndex));
}


//获得缓冲区剩下的长度
inline long Ep_BufferLeave(PEPBUFFERPOS pBufferPos)
{
	return pBufferPos->nBufLength - pBufferPos->nIndex;
}

//获得缓冲区当前的位置
inline BYTE* Ep_GetBufferCurr(PEPBUFFERPOS pBufferPos)
{
	return pBufferPos->pBuffer + pBufferPos->nIndex;
}

//获得帧开始的缓冲区
inline BYTE* Ep_GetFrameBufferBegin(PEPBUFFERPOS pBufferPos)
{
	return pBufferPos->pBuffer + pBufferPos->nIndex - pBufferPos->nFrameCurr;
}

//获得帧的当前位置
inline long Ep_GetFramePos(PEPBUFFERPOS pBufferPos)
{
	return pBufferPos->nFrameCurr;
}

//当前值的位置
inline long Ep_GetValuePos(PEPBUFFERPOS pBufferPos)
{
	return pBufferPos->nPrevIndex;
}

//偏移缓冲区位置,继续下一个帧的操作
inline long Ep_OffsetBufferCurr(PEPBUFFERPOS pBufferPos, long nOffset)
{
	pBufferPos->nPrevIndex = pBufferPos->nIndex;
	pBufferPos->nIndex += nOffset;
	pBufferPos->nFrameCurr += nOffset;
	return pBufferPos->nIndex;
}

//开始解析,置位帧操作缓冲区起始的位置
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

inline DWORD Ep_BufferReadDWord2(PEPBUFFERPOS pBufferPos)
{
	DWORD val = Ep_BufferGetDWord2(pBufferPos);
	Ep_OffsetBufferCurr(pBufferPos, 4);
	return val;
}

inline DWORD Ep_BufferGetDWord(PEPBUFFERPOS pBufferPos, long nLen)
{
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

inline char* Ep_BufferReadString(PEPBUFFERPOS pBufferPos, long nLen, char *pString)
{
	ASSERT (pString != NULL);
	ASSERT (nLen > 0);
	memcpy(pString, Ep_GetBufferCurr(pBufferPos), nLen);
	*(pString + nLen) = '\0';
	Ep_OffsetBufferCurr(pBufferPos, nLen);
	return pString;
}


#define EP_MATCH_STATE_MATCH        0X00000000  //匹配成功
#define EP_MATCH_STATE_NO_MATCH     0X00000001  //匹配不成功，但是是一帧完整的数据
#define EP_MATCH_STATE_NONE         0X00000002  //没有匹配的数据帧
#define EP_MATCH_STATE_BUFF_NOTFULL 0X00000004  //缓冲区不完整

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

//还没有被解析
#define EBS_NOPARSED      0x00000000
//全部解析完毕
#define EBS_BEPARSED      0x00000001 
//部分被解析
#define EBS_SOMEPARSED    0x00000002  
//解析错误
#define EBS_PARSEDERROR   0x00000004 

#define EBS_HASWRITE      0x00010000



#define WM_CAP_MONITOR  (WM_USER+1012)
#define WM_CAP_MONITORS  (WM_USER+1013)
