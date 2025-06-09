//TMemBuffer.h
//2002年07月12日		李俊庆
//////////////////////////////////////////////////////////////////
#ifndef _CTMemBuffer_h__
#define _CTMemBuffer_h__

template <class T> 
class CTMemBuffer
{
public:
	long   m_nMemBuffMax;
	long   m_nMemBuffLen;
	T*     m_pxData;
	CString m_strBufferID;   //缓冲区的标示，整个系统中，此标示唯一

public:
	CTMemBuffer()
	{
		InitMemBuffer();
	}

	virtual ~CTMemBuffer()
	{
		FreeMemBuffer();
	}

	void	InitMemBuffer()
	{
		m_nMemBuffMax = 0;
		m_nMemBuffLen = 0;
		m_pxData = NULL;
	}

	void	FreeMemBuffer()
	{
		m_nMemBuffLen = 0;

		if (m_pxData != NULL)
		{
			delete m_pxData;
			m_pxData = NULL;
		}
	}

	BOOL	AllocMemBuffer(long	nMemBufferLen)
	{
		if (nMemBufferLen > m_nMemBuffMax)
		{
			FreeMemBuffer();

			m_pxData=new T[nMemBufferLen];
			m_nMemBuffMax = nMemBufferLen;
			m_nMemBuffLen = nMemBufferLen;
		}
		else
		{
			m_nMemBuffLen = nMemBufferLen;
		}

		return TRUE;
	}

	void	SetMemBufVal(long iIndex,T xVal)
	{
                m_pxData[iIndex]=xVal;
	}

	T	GetMemBufVal(long iIndex)
	{
		return m_pxData[iIndex];
	}

	T* GetBuffer()         {  return m_pxData;           }

};




#define		MEMBUFFER_MAX_ONEBUFFER		8000
#define		MEMBUFFER_MAX_BUFARRAY		15
#define		MEMBUFFER_MAX_BUFFER		120000

template <class T> 
class CTMemBufferEx
{
public:
	long		m_nMemBuffNum;
	long		m_nLastMemBuffIndex;
	T*     m_pxData[MEMBUFFER_MAX_BUFARRAY];
	CString m_strBufferID;   //缓冲区的标示，整个系统中，此标示唯一

public:
	CTMemBufferEx()
	{
		InitMemBuffer();
	}

	virtual ~CTMemBufferEx()
	{
		FreeMemBuffer();
	}

	void	InitMemBuffer()
	{
		for(long i=0;i<MEMBUFFER_MAX_BUFARRAY;i++)
			m_pxData[i]=NULL;
		m_nMemBuffNum		=0;
		m_nLastMemBuffIndex	=0;
	}

	void	FreeMemBuffer()
	{
		for(long i=0;i<MEMBUFFER_MAX_BUFARRAY;i++)
		{
			if(m_pxData[i])
			{
				delete m_pxData[i];
				m_pxData[i]=NULL;
			}
		}

		m_nMemBuffNum		=0;
		m_nLastMemBuffIndex	=0;
	}

	BOOL	AllocMemBuffer(long	lMemBufferLen)
	{
		if(lMemBufferLen>MEMBUFFER_MAX_BUFFER)
			return FALSE;

		FreeMemBuffer();

		long iBuffNum=lMemBufferLen / MEMBUFFER_MAX_ONEBUFFER;
		long iLastBuff=lMemBufferLen - iBuffNum * MEMBUFFER_MAX_ONEBUFFER;

		m_nMemBuffNum=iBuffNum;
		m_nLastMemBuffIndex=iLastBuff;

		for(long i=0;i<iBuffNum;i++)
			m_pxData[i]=new T[MEMBUFFER_MAX_ONEBUFFER];
		if(iLastBuff>0)
                        m_pxData[iBuffNum]=new T[iLastBuff];
		return TRUE;
	}

	void	SetMemBufVal(long iIndex,T fVal)
	{
		long iBufIndex=iIndex / MEMBUFFER_MAX_ONEBUFFER;
		long iDIndex=iIndex % MEMBUFFER_MAX_ONEBUFFER;
		m_pxData[iBufIndex][iDIndex]=fVal;
	}

	T	GetMemBufVal(long iIndex)
	{
		long iBufIndex=iIndex / MEMBUFFER_MAX_ONEBUFFER;
		long iDIndex=iIndex % MEMBUFFER_MAX_ONEBUFFER;
		return m_pxData[iBufIndex][iDIndex];
	}
};


typedef CTMemBuffer<float> CXMemBuffer_float;//zhouhj 20210820  与Record中重名,将CMemBuffer_float改为CXMemBuffer_float
typedef CTMemBuffer<float> CXMemBuffer_Float;
typedef CTMemBuffer<double> CXMemBuffer_double;
typedef CTMemBuffer<char> CXMemBuffer_char;
typedef CTMemBuffer<long> CXMemBuffer_long;
typedef CTMemBuffer<BYTE> CXMemBuffer_BYTE;
typedef CTMemBuffer<unsigned short> CXMemBuffer_UShort;


#endif //_CTMemBuffer_h__
