#ifndef _TxRingPtrBuffer_H_
#define _TxRingPtrBuffer_H_

template <class T>
class CTxRingPtrBuffer
{
private:
	 unsigned long *m_pxData;

	long m_nBuffMaxLen;  //分配的缓冲区最大个数
	long m_nDataCount;    //当前存放的数据个数
	long m_nReadPos;      //默认使用的读位置
	long m_nWritePos;     //写入数据的位置

public:
	CTxRingPtrBuffer()
	{
		InitBuffer();
	}

	virtual ~CTxRingPtrBuffer()
	{
		FreeBuffer();
	}


public:
	void	InitBuffer()
	{
		m_pxData = NULL;
		m_nBuffMaxLen = 0;
		m_nDataCount = 0;
		m_nReadPos = 0;
		m_nWritePos = 0;
	}

	void	FreeBuffer()
	{
		if (m_pxData != NULL)
		{
			delete m_pxData;
			m_pxData = NULL;
		}

		Clear();
	}

	void	AllocBuffer(long	nBuffMaxLen)
	{
		if (m_pxData == NULL)
		{
			m_pxData=new unsigned long [nBuffMaxLen];
			memset(m_pxData, 0, m_nBuffMaxLen*sizeof(unsigned long));
			m_nBuffMaxLen = nBuffMaxLen;
		}

		if (nBuffMaxLen > m_nBuffMaxLen)
		{
			FreeBuffer();
			unsigned long *pTemp = m_pxData;
			m_pxData=new unsigned long [nBuffMaxLen];
			memcpy(m_pxData, pTemp, m_nBuffMaxLen*sizeof(unsigned long));
			m_nBuffMaxLen = nBuffMaxLen;
			delete pTemp;
		}
	}

	long GetDataCount()
	{
		return m_nDataCount;
	}

	long GetDataCountCanRead(long nReadPos)
	{
		if (nReadPos <= m_nWritePos)
		{
			return m_nWritePos - nReadPos;
		}
		else
		{
			return m_nBuffMaxLen - nReadPos + m_nWritePos;
		}
	}

	long GetDataCountCanRead()
	{
		return GetDataCountCanRead(m_nReadPos);
	}

	long GetWritePos()
	{
		return m_nWritePos;
	}

	T* Read(long &nReadPos)
	{
		if (nReadPos == m_nWritePos)
		{
			return NULL;
		}
		else
		{
			T *pRet = (T*)m_pxData[nReadPos];
			nReadPos++;

			if (nReadPos >= m_nBuffMaxLen)
			{
				nReadPos = 0;
			}

			if (m_nDataCount>0)//zhouhj 2024.1.23 读完之后,将数据数量减少
			{
				m_nDataCount--;
			}

			return pRet;
		}
	}

	T* Read()
	{
		return Read(m_nReadPos);
	}

	void Add(T *p)
	{
		m_pxData[m_nWritePos] = (unsigned long)p;
		m_nWritePos++;

		if (m_nDataCount <= m_nBuffMaxLen)
		{
			m_nDataCount++;
		}

		if (m_nWritePos >= m_nBuffMaxLen)
		{
			m_nWritePos = 0;
		}
	}

	BOOL CanRead()
	{
		return GetDataCountCanRead() > 0;
	}

	void Clear()
	{
//		m_nBuffMaxLen = 0;//20220627 zhouhj 清除当前循环缓存记录的读写位置,数据长度恢复为0,缓存大小不变
		m_nDataCount = 0;
		m_nReadPos = 0;
		m_nWritePos = 0;
	}

};

#endif//!_TxRingPtrBuffer_H_