#ifndef _CTCycleMemBuffer_h__
#define _CTCycleMemBuffer_h__

#include "TMemBuffer.h"

//2022-10-19 李俊庆批注：典型的瞎搞方式，TCycleMemBuffer作为通用模块
//却需要引用SttStudio/Module/SttTest/Common/tmt_rtdata_def.h，这是极端错误的方式
//#include "../../SttStudio/Module/SttTest/Common/tmt_rtdata_def.h"

template <class T>
struct CTCycleMemBufferPos
{
    T *pBuffer;
    long nBufLength;

    long nBuf1BeginPos;
    long nBuf1EndPos;
    long nBuf2BeginPos;
    long nBuf2EndPos;
};

template <class T> 
class CTCycleMemBuffer : public  CTMemBuffer<T>
{

public:
	CTCycleMemBuffer()
	{
		m_nDataFillBeginPos = 0;
		m_nDataLength		= 0;
	}

	virtual ~CTCycleMemBuffer()
	{
	}

	//缓存相关参数的获取
	virtual long GetDataLength()                       {    return m_nDataLength;                                  }
	virtual long GetDataFillBeginPosition()            {    return m_nDataFillBeginPos;                            }
    virtual long GetDataFillEmptyLen()                 {    return CTMemBuffer<T>::m_nMemBuffLen - m_nDataFillBeginPos;          }
	virtual T* GetDataFillBeginBuffer()             {    return CTMemBuffer<T>::m_pxData + m_nDataFillBeginPos;                }
	virtual long GetBufferLength()                     {    return CTMemBuffer<T>::m_nMemBuffLen;                                }
	virtual T* GetBuffer()                          {    return CTMemBuffer<T>::m_pxData;                                      }
	virtual BOOL CanAppendBuffer(long nLen)            {    return (m_nDataFillBeginPos + nLen < CTMemBuffer<T>::m_nMemBuffLen); }

	virtual long AppendBuffer(long nLen, long nGap , BOOL bOffsetBuffer, long &nPos1Begin , long &nPos1End, long &nPos2Begin, long &nPos2End)
	{
		long nLenCopy = nLen / nGap;
		long nOffset = nLen - nLenCopy * nGap;

		if (nOffset > 0)
		{
			nLenCopy++;
		}

		long nEndPos = m_nDataFillBeginPos + nLenCopy; //目标缓冲区期望末位置
		long nLenCopy1 = 0, nLenCopy2 = 0;

		nPos1Begin = -1;
		nPos1End   = -1;
		nPos2Begin = -1;
		nPos2End   = -1;

        if (nEndPos < CTMemBuffer<T>::m_nMemBuffLen)
		{
			nPos1Begin = m_nDataFillBeginPos;
			nPos1End   = nEndPos;

			if (bOffsetBuffer)
			{
				m_nDataFillBeginPos = nEndPos;
			}
		}
		else 
		{
			//第一次拷贝,从m_nDataFillBeginPos到缓冲区末尾
            nLenCopy1 = CTMemBuffer<T>::m_nMemBuffLen - m_nDataFillBeginPos;
			nPos1Begin = m_nDataFillBeginPos;
            nPos1End   = CTMemBuffer<T>::m_nMemBuffLen;

			//第一次拷贝,从缓冲区开始到......
			nLenCopy2 = nLenCopy - nLenCopy1;
			nPos2Begin = 0;
			nPos2End   = nLenCopy2;

			if (bOffsetBuffer)
			{
				m_nDataFillBeginPos = nLenCopy2;
			}

		}

		if (bOffsetBuffer)
		{
			m_nDataLength += nLenCopy;

            if (m_nDataLength >= CTMemBuffer<T>::m_nMemBuffLen)
			{
                m_nDataLength = CTMemBuffer<T>::m_nMemBuffLen;
			}
		}

		return nLenCopy*nGap;
	}

	long AppendBufferByPos(T *pBuffer, long nBeginPos, long nEndPos, long nGap)
	{
		ASSERT (nBeginPos >= 0 && nEndPos >= 0 && nEndPos >= nBeginPos);
		if (!(nBeginPos >= 0 && nEndPos >= 0 && nEndPos >= nBeginPos))
		{
			return 0;
		}

		T *pDest = NULL;
		T *pDestEnd = NULL;
		T *pSrc = NULL;
		T *pSrcEnd = NULL;	

        pDest = CTMemBuffer<T>::m_pxData + nBeginPos;

		if (nGap == 1)
		{
			memcpy(pDest, pBuffer, (nEndPos - nBeginPos)*sizeof(T));
		}
		else
		{
            pDestEnd = CTMemBuffer<T>::m_pxData + nEndPos;
			pSrc = pBuffer;

			while (pDest < pDestEnd)
			{
				*pDest = *pSrc;
				pDest++;
				pSrc += nGap;
			}
		}

		return nGap * (nEndPos - nBeginPos);
	}


	virtual long AppendBuffer(T *pBuffer, long nLen, long nGap = 1)
	{
		long nPos1Begin = -1;
		long nPos1End = -1;
		long nPos2Begin = -1;
		long nPos2End = -1;

		long nLenCopy = AppendBuffer(nLen, nGap, FALSE, nPos1Begin, nPos1End, nPos2Begin, nPos2End);

		if (nPos1Begin >= 0)
		{
			AppendBufferByPos(pBuffer, nPos1Begin, nPos1End, nGap);
		}

		if (nPos2Begin >= 0)
		{
			AppendBufferByPos(pBuffer+nPos1End-nPos1Begin, nPos2Begin, nPos2End, nGap);
		}

		nLenCopy = AppendBuffer(nLen, nGap, TRUE, nPos1Begin, nPos1End, nPos2Begin, nPos2End);

		return nLenCopy;
	}

	virtual long GetBufferPos(long nBeginPos, long nLen, long &nPos1Begin , long &nPos1End, long &nPos2Begin, long &nPos2End)
	{
        if (nBeginPos >= CTMemBuffer<T>::m_nMemBuffLen)
		{//如果缓冲区
            nBeginPos -= CTMemBuffer<T>::m_nMemBuffLen;
		}

		nPos1Begin = -1;
		nPos1End   = -1;
		nPos2Begin = -1;
		nPos2End   = -1;

		if (nLen <= 0)
		{
            if (m_nDataLength ==CTMemBuffer<T>::m_nMemBuffLen)
			{
				if(m_nDataFillBeginPos > nBeginPos)
				{
					nPos1Begin = nBeginPos;
					nPos1End = m_nDataFillBeginPos;
				}
				else if (m_nDataFillBeginPos < nBeginPos)
				{
					nPos1Begin = nBeginPos;
                    nPos1End = CTMemBuffer<T>::m_nMemBuffLen;
					nPos2Begin = 0;
					nPos2End = m_nDataFillBeginPos;
				}
			}
			else
			{
				if (nBeginPos < m_nDataFillBeginPos)
				{
					nPos1Begin = nBeginPos;
					nPos1End = m_nDataFillBeginPos;
				}
				else
				{
					nPos1Begin = -1;
					nPos1End = 0;
				}
			}
		}
		else
		{
            if (m_nDataLength == CTMemBuffer<T>::m_nMemBuffLen)
			{
				nPos1Begin = nBeginPos;
				nPos1End = nBeginPos + nLen;

				if(m_nDataFillBeginPos > nBeginPos)
				{
					if (nPos1End >= m_nDataFillBeginPos)
					{
						nPos1End = m_nDataFillBeginPos;
					}
					else
					{
					}
				}
				else
				{
                    if (nPos1End >= CTMemBuffer<T>::m_nMemBuffLen)
					{
                        nPos1End = CTMemBuffer<T>::m_nMemBuffLen;
						nPos2Begin = 0;
						nPos2End = nLen - nPos1End + nPos1Begin;

						if (nPos2End >= m_nDataFillBeginPos)
						{
							nPos2End = m_nDataFillBeginPos;
						}
						else
						{
						}
					}
					else
					{
					}
				}
			}
			else 
			{
				if (nBeginPos < m_nDataFillBeginPos)
				{
					nPos1Begin = nBeginPos;
					nPos1End = nBeginPos + nLen;

					if (nPos1End >= m_nDataFillBeginPos)
					{
						nPos1End = m_nDataFillBeginPos;
					}
					else
					{
					}
				}
				else
				{
					nPos1Begin = -1;
					nPos1End = 0;
				}
			}		
		}

		return 0;
	}

    virtual long GetBufferPos(long nBeginPos, long nLen, CTCycleMemBufferPos<T> &oBufPos)
    {
        GetBufferPos(nBeginPos, nLen, oBufPos.nBuf1BeginPos, oBufPos.nBuf1EndPos, oBufPos.nBuf2BeginPos, oBufPos.nBuf2EndPos);
        oBufPos.nBufLength = oBufPos.nBuf1EndPos - oBufPos.nBuf1BeginPos + 1;
        oBufPos.pBuffer = CTMemBuffer<T>::m_pxData;

        if (oBufPos.nBuf2BeginPos >= 0)
        {
            oBufPos.nBufLength += oBufPos.nBuf2EndPos - oBufPos.nBuf2BeginPos;
        }

        return oBufPos.nBufLength;
    }

	long GetDataLength(long nBeginPos)
	{
		if (nBeginPos < 0)
		{
			return m_nDataLength;
		}

        if (nBeginPos >= CTMemBuffer<T>::m_nMemBuffLen)
		{
            nBeginPos -= CTMemBuffer<T>::m_nMemBuffLen;
		}

		long nLen = 0;

        if (m_nDataLength == CTMemBuffer<T>::m_nMemBuffLen)
		{
			if(m_nDataFillBeginPos >= nBeginPos)
			{
				nLen = m_nDataFillBeginPos - nBeginPos;
			}
			else
			{
                nLen = m_nDataFillBeginPos + CTMemBuffer<T>::m_nMemBuffLen - nBeginPos;
			}
		}
		else 
		{
			if(m_nDataFillBeginPos >= nBeginPos)
			{
				nLen = m_nDataFillBeginPos - nBeginPos;
			}
			else
			{
				nLen = 0;
			}
		}

		return nLen;
	}

    virtual BOOL GetBuffer(T *pDestBuffer, long nBeginPos, long nLen)//参数1传入存取的首地址，参数2开始取数据的首地址，参数3取数据的长度
    {
        CTCycleMemBufferPos<T> oBufPos;
        long nDataLen = GetDataLength(nBeginPos);

        GetBufferPos(nBeginPos, nDataLen, oBufPos);

        if (nDataLen < nLen)//如果当前取数据的长度大于首地址到结束位置的长度，则读取数据失败
        {
            return FALSE;
        }

        if (oBufPos.nBuf1EndPos - oBufPos.nBuf1BeginPos + 1 >= nLen)
        {
            memcpy(pDestBuffer, CTMemBuffer<T>::m_pxData+oBufPos.nBuf1BeginPos, nLen*sizeof(T));
        }
        else
        {
            long nLen1 = oBufPos.nBuf1EndPos - oBufPos.nBuf1BeginPos+1;
            ASSERT (nLen1 > 0);

            memcpy(pDestBuffer, CTMemBuffer<T>::m_pxData+oBufPos.nBuf1BeginPos, nLen1*sizeof(T));
            memcpy(pDestBuffer+nLen1, CTMemBuffer<T>::m_pxData, (nLen - nLen1)*sizeof(T));
        }

        return TRUE;
    }

	virtual void ResetOffsetDataFillBeginPosition()  {    m_nDataFillBeginPos = 0;    m_nDataLength = 0;    }
	virtual void ResetOffsetDataFillBeginPosition(long nDataFillBeginPos, long nDataLength)
	{
		m_nDataFillBeginPos = nDataFillBeginPos;
		m_nDataLength = nDataLength;
	}

	virtual BOOL GetLastMemVal(T &oVal)
	{
        if ((m_nDataLength == 0) || (CTMemBuffer<T>::m_nMemBuffLen == 0))
		{
			return FALSE;
		}

		long nIndex = m_nDataFillBeginPos - 1;
		if (nIndex < 0)
		{
            nIndex += CTMemBuffer<T>::m_nMemBuffLen;
		}

        oVal = CTMemBuffer<T>::GetMemBufVal(nIndex);
		return TRUE;
	}

protected:
	long m_nDataFillBeginPos;//数据填充的开始位置
	long m_nDataLength;//数据长度
};

//2022-10-19 李俊庆批注：典型的瞎搞方式，TCycleMemBuffer作为通用模块
//却需要引用SttStudio/Module/SttTest/Common/tmt_rtdata_def.h，这是极端错误的方式
//此处定义的，都是通用的数据对象，rtdata为特定应用的对象
//typedef CTCycleMemBuffer<tmt_RtDataCh> CCycleMemBuffer_rtdata;//yyj add 2021-08-25

typedef CTCycleMemBuffer<float> CCycleMemBuffer_float;
typedef CTCycleMemBuffer<double> CCycleMemBuffer_double;
typedef CTCycleMemBuffer<char> CCycleMemBuffer_char;
typedef CTCycleMemBuffer<long> CCycleMemBuffer_long;
typedef CTCycleMemBuffer<BYTE> CCycleMemBuffer_BYTE;
typedef CTCycleMemBuffer<unsigned short> CCycleMemBuffer_UShort;


#endif //_CTMemBuffer_h__
