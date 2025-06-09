// MemBufferDef.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(_MEMBUFFERDEF_H__)
#define _MEMBUFFERDEF_H__

#include "..\..\..\Module\BASECLASS\ExBaseObject.h"

#define MEMCLASSID_BUFFERBASE     (CLASSID_BASECLASS+0X00100000)

#define MEMCLASSID_USHORT         (MEMCLASSID_BUFFERBASE+0X00000001)     
#define MEMCLASSID_COMPLEXUSHORT  (MEMCLASSID_BUFFERBASE+0X00000002)     
#define MEMCLASSID_LONG           (MEMCLASSID_BUFFERBASE+0X00000003)     
#define MEMCLASSID_COMPLEXLONG    (MEMCLASSID_BUFFERBASE+0X00000004)     
#define MEMCLASSID_FLOAT          (MEMCLASSID_BUFFERBASE+0X00000005)     
#define MEMCLASSID_COMPLEXFLOAT   (MEMCLASSID_BUFFERBASE+0X00000006)     
#define MEMCLASSID_DOUBLE         (MEMCLASSID_BUFFERBASE+0X00000007)     
#define MEMCLASSID_COMPLEXDOUBLE  (MEMCLASSID_BUFFERBASE+0X00000008)     
#define MEMCLASSID_CHANNEL        (MEMCLASSID_BUFFERBASE+0X00000009)     
#define MEMCLASSID_MNGR           (MEMCLASSID_BUFFERBASE+0X0000000A)     

//参数计算过滤用
#define RT_FILTER_BUFFER_LEN   81
#define RT_FILTER_DATA_LEN_PREV 40
#define RT_FILTER_DATA_LEN_NEXT 40

extern DWORD g_dwRtFilterDataLenPrev;
extern DWORD g_dwRtFilterDataLenNext;
extern DWORD g_dwRtFilterDataLenLen;

//按照额定频率
#define RTATTRIBUTECAL_MIN_BUFFER_LEN       (6000+RT_FILTER_BUFFER_LEN) //20000
#define RTATTRIBUTECAL_MIN_STARTUP_BUFLEN   (18000)

//25次谐波，RTATTRIBUTECAL_MIN_BUFFER_LEN点对应的过零点次数为250次
//取较大的裕度
#define  MAX_FREQ_ZERO_POS_BUFFER  400
#define  MAX_FREQ_ZERO_POS_COUNT   50

#define MIN_CIRCLRPOINTS 10 //一个周期的最少点数，fdp add 2010.4.15

inline BOOL IsMemClassID(UINT nClassID)
{
	return ( (nClassID & CLASSID_BASECLASS) == CLASSID_BASECLASS);
}

inline BOOL IsMemClass(CBaseObject *pObj)
{
	return ( (pObj->GetClassID() & CLASSID_BASECLASS) == CLASSID_BASECLASS);
}

//用于启动判断的与缓冲区相关的设置
//属性缓冲区为float
//record缓冲区为ushort、float
#define MEMBUFFER_TYPE_ID_NONE           0X00000000
#define MEMBUFFER_TYPE_ID_ATTRBUFFER     0X00010000
#define MEMBUFFER_TYPE_ID_RECORDBUFFER   0X00020000

#define MEMBUFFER_TYPE_ID_RECORD_USHORT  0X00000001
#define MEMBUFFER_TYPE_ID_RECORD_FLOAT   0X00000002

inline UINT CreateMemBufferTypeIDAttr()  
{
	return (MEMBUFFER_TYPE_ID_ATTRBUFFER);
}

inline UINT CreateMemBufferTypeIDRecordUShort()  
{
	return (MEMBUFFER_TYPE_ID_RECORDBUFFER+MEMBUFFER_TYPE_ID_RECORD_USHORT);
}

inline UINT CreateMemBufferTypeIDRecordFloat()  
{
	return (MEMBUFFER_TYPE_ID_RECORDBUFFER+MEMBUFFER_TYPE_ID_RECORD_FLOAT);
}

inline BOOL IsMemBufferTypeAttr(UINT nTypeID)
{
	return (MEMBUFFER_TYPE_ID_ATTRBUFFER == (nTypeID & MEMBUFFER_TYPE_ID_ATTRBUFFER));
}

inline BOOL IsMemByfferTypeRecord(UINT nTypeID)
{
	return (MEMBUFFER_TYPE_ID_RECORDBUFFER == (nTypeID & MEMBUFFER_TYPE_ID_RECORDBUFFER));
}

inline BOOL IsMemByfferTypeRecordUshort(UINT nTypeID)
{
	return ( (MEMBUFFER_TYPE_ID_RECORDBUFFER == (nTypeID & MEMBUFFER_TYPE_ID_RECORDBUFFER))
		&& (MEMBUFFER_TYPE_ID_RECORD_USHORT == (nTypeID & MEMBUFFER_TYPE_ID_RECORD_USHORT)) );
}

inline BOOL IsMemByfferTypeRecordFloat(UINT nTypeID)
{
	return ( (MEMBUFFER_TYPE_ID_RECORDBUFFER == (nTypeID & MEMBUFFER_TYPE_ID_RECORDBUFFER))
		&& (MEMBUFFER_TYPE_ID_RECORD_FLOAT == (nTypeID & MEMBUFFER_TYPE_ID_RECORD_FLOAT)) );
}

class CMemBufferInterface : public CExBaseObject
{
public:
	virtual long GetDataLength() = 0;
	virtual long GetDataFillBeginPosition() = 0;
	virtual long GetBufferLength() = 0;
	virtual void Init() = 0;
	virtual void OffsetDataFillBeginPosition(long nLen) = 0;

	UINT m_nMemBufferTypeID;
};

#define MEMBUFFER_LENGTH_EX 2000


#endif // !defined(_MEMBUFFERDEF_H__)
