// MemBufferDef.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(_MEMBUFFERDEF_H__)
#define _MEMBUFFERDEF_H__

//#include "../../../Module/BASECLASS/ExBaseObject.h"
#include "../../../Module/BaseClass/ExBaseObject.h"
//../../BaseClass/ExBaseObject.h
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
// #define RT_FILTER_DATA_LEN_PREV 40
// #define RT_FILTER_DATA_LEN_NEXT 40

extern DWORD g_dwRtFilterDataLenPrev;
extern DWORD g_dwRtFilterDataLenNext;
extern DWORD g_dwRtFilterDataLenLen;

//按照额定频率
// extern long USE_RT_FILTER_BUFFER_LEN;//   81
// extern long RT_FILTER_DATA_LEN_PREV;// 40
// extern long RT_FILTER_DATA_LEN_NEXT;// 40
// extern long RTATTRIBUTECAL_MIN_BUFFER_LEN;

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
	CMemBufferInterface()
	{
		m_nMemBufferTypeID = 0;

		memset(m_dwFreqZeroPosition, 0, MAX_FREQ_ZERO_POS_BUFFER*sizeof(DWORD));
		m_nFreqZeroPosCount = 0;

		//缓存中已经放入的数据数量，可以大于缓存长度的大小 fdp add 2010.4.15
		m_n64BeginPos = 0;
		m_n64EndPos = 0;

		m_nBufferLength = 0;	
		m_nDataFillBeginPos = 0;
		m_nDataLength = 0;
		m_nChIndex = 0;
		m_nHdIndex = 0;
	}

	virtual ~CMemBufferInterface()
	{

	}

public:
	virtual void Init() 
	{
		m_nDataFillBeginPos = 0;
		m_nDataLength		= 0;
	}

	virtual unsigned short* GetBuffer()		{	return NULL;	}
	virtual float* GetBuffer_float()		{	return NULL;	}
	virtual long* GetBuffer_long()		{	return NULL;	}
	virtual void FreeBuffer() = 0;
	virtual void SetBufferLength(long lBufferLen) = 0;
	virtual long CopyBuffer(CMemBufferInterface *pBuffer, long &lCopyBeginPos, long lGap) = 0;

	long CalCopyBuffer(long lLen, long lGap , BOOL bOffsetBuffer, long &lPos1Begin , long &lPos1End, long &lPos2Begin, long &lPos2End)
	{
		long lLenCopy = lLen / lGap;
		long nOffset = lLen - lLenCopy * lGap;

		if (nOffset > 0)
		{
			lLenCopy++;
		}

		long lEndPos = m_nDataFillBeginPos + lLenCopy; //目标缓冲区期望末位置
		long lLenCopy1 = 0, lLenCopy2 = 0;

		lPos1Begin = -1;
		lPos1End   = -1;
		lPos2Begin = -1;
		lPos2End   = -1;

		if (lEndPos < m_nBufferLength)
		{
			lPos1Begin = m_nDataFillBeginPos;
			lPos1End   = lEndPos;

			if (bOffsetBuffer)
			{
				m_nDataFillBeginPos = lEndPos;
			}
		}
		else 
		{
			//第一次拷贝,从m_nDataFillBeginPos到缓冲区末尾
			lLenCopy1 = m_nBufferLength - m_nDataFillBeginPos;
			lPos1Begin = m_nDataFillBeginPos;
			lPos1End   = m_nBufferLength;

			//第一次拷贝,从缓冲区开始到......
			lLenCopy2 = lLenCopy - lLenCopy1;
			lPos2Begin = 0;
			lPos2End   = lLenCopy2;

			if (bOffsetBuffer)
			{
				m_nDataFillBeginPos = lLenCopy2;
			}

		}

		if (bOffsetBuffer)
		{
			m_nDataLength += lLenCopy;

			if (m_nDataLength >= m_nBufferLength)
			{
				m_nDataLength = m_nBufferLength;
			}
		}

		return lLenCopy*lGap;
	}


	virtual void OffsetDataFillBeginPosition(long nLen)
	{
		m_nDataFillBeginPos += nLen;
		m_nDataLength += nLen;

		if (m_nDataFillBeginPos >= m_nBufferLength)
		{
			m_nDataFillBeginPos -= m_nBufferLength;
		}

		if (m_nDataLength >= m_nBufferLength)
		{
			m_nDataLength = m_nBufferLength;
		}

	}

	BOOL CanAppendBuffer(long nLen)            {    return (m_nDataFillBeginPos + nLen < m_nBufferLength); }

public:
	UINT m_nMemBufferTypeID;
	UINT m_nChIndex;
	UINT m_nHdIndex;
	CString m_strBufferID;   //缓冲区的标示，整个系统中，此标示唯一

	DWORD m_dwFreqZeroPosition[MAX_FREQ_ZERO_POS_BUFFER];
	UINT  m_nFreqZeroPosCount;

	//缓存中已经放入的数据数量，可以大于缓存长度的大小 fdp add 2010.4.15
	__int64 m_n64BeginPos;
	__int64 m_n64EndPos;

protected:
	long m_nBufferLength;	
	long m_nDataFillBeginPos;
	long m_nDataLength;

public:
	long GetDataLength()                       {    return m_nDataLength;                      }
	long GetDataFillBeginPosition()            {    return m_nDataFillBeginPos;                }
	long GetBufferLength()                     {    return m_nBufferLength;                    }

	void SetPosition(long nPos, long nDataCount)
	{
		m_nDataFillBeginPos = nPos;
		m_nDataLength = nDataCount;
	}

};

inline BOOL is_mem_buffer_ushort(CMemBufferInterface *pBuffer)
{
	return (MEMCLASSID_USHORT == pBuffer->GetClassID());
}


inline BOOL is_mem_buffer_long(CMemBufferInterface *pBuffer)
{
	return (MEMCLASSID_LONG == pBuffer->GetClassID());
}


#define MEMBUFFER_LENGTH_EX 2000

typedef struct rt_mem_buffer_data_pos
{
	long nDataLength;    //pnBuffer、pfBuffer的数据总长度
	long nBufferLength;  //pnBuffer、pfBuffer的缓冲区长度

	long nBuffer1Pos;
	long nBuffer2Pos;
	long nBuffer1Len;
	long nBuffer2Len;
}*PRT_MEM_BUFFER_DATA_POS, RT_MEM_BUFFER_DATA_POS;

inline long rt_get_points_prev(PRT_MEM_BUFFER_DATA_POS pDataPos, long nPos)
{
	if (pDataPos->nBuffer1Len <= 0)
	{//第一段区域无数据
		return 0;
	}

	if ((pDataPos->nBuffer1Pos <= nPos) && (nPos < pDataPos->nBuffer1Len + pDataPos->nBuffer1Pos))
	{//在第一段区域之内
		return nPos - pDataPos->nBuffer1Pos - 1;
	}

	if (pDataPos->nBuffer2Len <= 0)
	{//第二段区域无数据
		return 0;
	}

	if ((pDataPos->nBuffer2Pos <= nPos) && (nPos < pDataPos->nBuffer2Len + pDataPos->nBuffer2Pos))
	{//在第二段区域之内
		return pDataPos->nBuffer1Len + (nPos - pDataPos->nBuffer2Pos) - 1;
	}

	return 0;//不在第二段区域之内
}


inline long rt_get_points_next(PRT_MEM_BUFFER_DATA_POS pDataPos, long nPos)
{
	long nRet = 0;
	if (pDataPos->nBuffer2Len > 0)
	{//第二段区域有数据
		if ((pDataPos->nBuffer2Pos <= nPos) && (nPos < pDataPos->nBuffer2Len + pDataPos->nBuffer2Pos))
		{//在第二段区域之内
			nRet = pDataPos->nBuffer2Len - (nPos - pDataPos->nBuffer2Pos);
			nRet--;
		}
		else
		{
			if ((pDataPos->nBuffer1Pos <= nPos) && (nPos < pDataPos->nBuffer1Len + pDataPos->nBuffer1Pos))
			{//在第一段区域之内
				nRet = pDataPos->nBuffer1Len - (nPos - pDataPos->nBuffer1Pos);
				nRet += pDataPos->nBuffer2Len;
				nRet--;
			}
			else
			{
				nRet = 0;
			}
		}
	}
	else
	{
		if ((pDataPos->nBuffer1Pos <= nPos) && (nPos < pDataPos->nBuffer1Len + pDataPos->nBuffer1Pos))
		{//在第一段区域之内
			nRet = pDataPos->nBuffer1Len - (nPos - pDataPos->nBuffer1Pos);
			nRet--;
		}
		else
		{
			nRet = 0;
		}
	}

	return nRet;
}


#endif // !defined(_MEMBUFFERDEF_H__)
