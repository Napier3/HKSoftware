// EpGlobalBaseDefine.h
//////////////////////////////////////////////////////////////////////

#if !defined(_EPGLOBALBASEDEFINE_H__)
#define _EPGLOBALBASEDEFINE_H__

#include "..\BaseClass\ExBaseList.h"
#include "..\ProtocolBase\EpCycleMemBufferMngr.h"
#include "..\ProtocolBase\ProtocolGlobalBaseDefine.h"
#include "EpGlobalClassIDBaseDefine.h"

//规约
#define EPCLASSID_FRAMES            (EPPCLASSID_EXLISTCLASS + 0X00200000)
#define EPCLASSID_PROCEDURES        (EPPCLASSID_EXLISTCLASS + 0X00600000)
#define EPCLASSID_FRAME_GROUPS      (EPPCLASSID_EXLISTCLASS + 0X04000000)

#define EPCLASSID_FRAME             (EPPCLASSID_EXLISTCLASS + 0X00100000) //0x0001
#define EPCLASSID_PARSE_FRAME       (EPPCLASSID_EXLISTCLASS + 0X00300000) //0x0011
#define EPCLASSID_PRODUCE_FRAME     (EPPCLASSID_EXLISTCLASS + 0X00500000) //0x0111
#define EPCLASSID_FRAME_ALL         (EPPCLASSID_EXLISTCLASS + 0X00700000) //0x0111
#define EPCLASSID_PROCEDURE         (EPPCLASSID_BASECLASS   + 0X00400000)
#define EPCLASSID_PROTOCOL          (EPPCLASSID_EXLISTCLASS + 0X01000000)
#define EPCLASSID_FRAME_GROUP       (EPPCLASSID_EXLISTCLASS + 0X02000000)

#define EPCLASSID_TAG               (EPPCLASSID_EXLISTCLASS + 0X07000001)
#define EPCLASSID_TAGS              (EPPCLASSID_EXLISTCLASS + 0X07000002)
#define EPCLASSID_BYTEBLOCK         (EPPCLASSID_EXLISTCLASS + 0X07000003)
#define EPCLASSID_DATA     (EPPCLASSID_EXLISTCLASS + 0X07000004)
#define EPCLASSID_BYTEBLOCKS        (EPPCLASSID_EXLISTCLASS + 0X07000005)
#define EPCLASSID_DATASET           (EPPCLASSID_EXLISTCLASS + 0X07000006)
#define EPCLASSID_BBINFOR           (EPPCLASSID_BASECLASS   + 0X07000009)

#define EPCLASSID_NODE				(EPPCLASSID_EXLISTCLASS + 0X07000010)
#define EPCLASSID_NODES				(EPPCLASSID_EXLISTCLASS + 0X07000011)
#define EPCLASSID_TIMER				(EPPCLASSID_EXLISTCLASS + 0X07000010)
#define EPCLASSID_TIMERS				(EPPCLASSID_EXLISTCLASS + 0X07000011)

#define EPCLASSID_ENGINEDATA            (EPPCLASSID_BASECLASS + 0X07000070)


#define EPCLASSID_OWN_MASK          0X0000FFFF


//////////////////////////////////////////////////////////////////////////
//状态常量定义
#define EPFRAME_STATE_CHECK_TRUE    0X00000001
#define EPFRAME_STATE_CHECK_ERROR   0X00000002
#define EPFRAME_STATE_NONE          0X00000004
#define EPFRAME_STATE_SEND          0X00000008

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

inline BOOL EpIsMatchStateNone(PEPBUFFERPOS pBufferPos)
{
	return (pBufferPos->dwState == EP_MATCH_STATE_NONE);
}

inline void Ep_GetCycleMemBuffer(CEpCycleMemBuffer *pBuffer, PEPBUFFERPOS pBufPos)
{
	Ep_InitEpBufferPos(pBufPos);
	pBufPos->dwBufferLen = pBuffer->GetDataLength();
	pBufPos->pBuffer = pBuffer->GetBuffer();
	pBufPos->nIndex = pBuffer->m_nCurrPos;
}

//////////////////////////////////////////////////////////////////////////
//常用函数定义
inline bool Ep_IsClassFrame(UINT nClassID)
{
	return ((nClassID & EPCLASSID_FRAME) == EPCLASSID_FRAME);
}

inline bool Ep_IsClassParseFrame(UINT nClassID)
{
	return ((nClassID & EPCLASSID_PRODUCE_FRAME) == EPCLASSID_PARSE_FRAME);
}

inline bool Ep_IsClassProduceFrame(UINT nClassID)
{
	return ((nClassID & EPCLASSID_PRODUCE_FRAME) == EPCLASSID_PRODUCE_FRAME);
}

inline bool Ep_IsClassProcedure(UINT nClassID)
{
	return ((nClassID & 0xFF000000) == EPCLASSID_PROCEDURE);
}


//////////////////////////////////////////////////////////////////////////
//


#define WM_THREAD_RECEIVE             (WM_USER+100)
#define WM_THREAD_CONNECT             (WM_USER+101)
#define WM_THREAD_DISCONNECT          (WM_USER+102)
#define WM_EXIT_ENGINE_THREAD         (WM_USER+103)
#define WM_DELETE_ALL_RECORD_FRAME    (WM_USER+104)
#define WM_THREAD_RECORD_SEND_PKG     (WM_USER+105)

#define EPEXIT_STATE_NONE         0
#define EPEXIT_STATE_NORMAL       1
#define EPEXIT_STATE_EXITPRUN     2
#define EPEXIT_STATE_DISCONNECT   3
#define EPEXIT_STATE_EXIT         0XFFFFFFFF

//解析过程中的状态定义
#define Ep_PPSERROR                       0X80000000
#define Ep_PPSHAS_NO_PACKAGE     0X00000001
#define Ep_PPSNOT_WHOLE_MATCH  0X00000002
#define Ep_PPSNO_DEFINE_PACKAGE 0X00000004

//解析是否错误
inline BOOL Ep_IsParseError(DWORD dwResult)
{
	return ( (dwResult & Ep_PPSERROR) == Ep_PPSERROR);
}
inline BOOL Ep_ParseError()
{
	return ( Ep_PPSERROR );
}

//是否包含完整的package
inline BOOL Ep_IsParseHasPakage(DWORD dwResult)
{
	return ( (dwResult & Ep_PPSHAS_NO_PACKAGE) == 0);
}

inline DWORD Ep_ParseHasNoPackage()
{
	return (Ep_PPSERROR | Ep_PPSHAS_NO_PACKAGE);
}


//是否完全匹配
inline DWORD Ep_IsParseWholeMatch(DWORD dwResult)
{
	return ( (dwResult & Ep_PPSNOT_WHOLE_MATCH) == 0);
}
inline DWORD Ep_IsParseMatch(DWORD dwResult)
{
	return ( (dwResult & Ep_PPSNOT_WHOLE_MATCH) == 0);
}

inline DWORD Ep_ParseNotWholeMatch()
{
	return (Ep_PPSERROR | Ep_PPSNOT_WHOLE_MATCH);
}

inline DWORD Ep_ParseWholeMatch()
{
	return (0);
}

inline DWORD Ep_ParseMatch()
{
	return (0);
}

//没有定义的报文帧
inline DWORD Ep_IsParseNoDefinePackage(DWORD dwResult)
{
	return ( (dwResult & Ep_PPSNO_DEFINE_PACKAGE) == Ep_PPSNO_DEFINE_PACKAGE);

}

inline DWORD Ep_ParseNoDefinePackage()
{
	return (Ep_PPSERROR | Ep_PPSNO_DEFINE_PACKAGE);
}

//制造过程中的状态定义
#define Ep_PPRFINISH				0X00000000
#define Ep_PPRERROR				0X00000001
#define Ep_PPRNOT_FINISH			0X00000002

//制造是否全部完成
inline BOOL Ep_IsProduceFinish(DWORD dwResult)
{
	return ( (dwResult & Ep_PPRFINISH) == Ep_PPRFINISH);
}

inline DWORD Ep_ProduceFinish()
{
	return ( Ep_PPRFINISH );
}

//制造是否有错
inline BOOL Ep_IsProduceError(DWORD dwResult)
{
	return ( (dwResult & Ep_PPRERROR) == Ep_PPRERROR);
}

inline DWORD Ep_ProduceError()
{
	return ( Ep_PPRERROR );
}

//制造是否完成一部分
inline BOOL Ep_IsProduceNotFinish(DWORD dwResult)
{
	return ( (dwResult & Ep_PPRNOT_FINISH) == Ep_PPRNOT_FINISH);
}

inline DWORD Ep_ProduceNotFinish()
{
	return ( Ep_PPRNOT_FINISH );
}



#endif // !defined(_EPGLOBALBASEDEFINE_H__)
