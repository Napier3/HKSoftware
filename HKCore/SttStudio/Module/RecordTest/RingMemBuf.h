#ifndef _CRingMemBuf_h__
#define _CRingMemBuf_h__

//#include "../../../Module/CriticalSection/SynCriticalSection.h"
#include "SttRcdBufferRcvMsg.h"

#define DEFAULT_CIRCLEBUF_LEN	20480000
#define DEFAULT_CIRCLEBUF_LEN2	20479988

//前提：读的速度必须大于写的速度

class CRingMemBuf : public CSttRcdBufferRcvMsg
{
public:
	CRingMemBuf();
    virtual ~CRingMemBuf();

//2022-6-30  lijunqing  CSttRcdBufferRcvMsg
public:
	virtual void OnRcdBufRcv(BYTE *pBuffer, long nLen)
	{
		WriteBuf((char*)pBuffer, nLen);
	}
	virtual long OnRcdRcvClosed()
	{
		return 0;
	}

protected:
	bool m_bIsCreateOwn; //是否为自身创建的缓冲区
    char *m_pszRealBuffer;
    char *m_pszRingBuf;//[DEFAULT_CIRCLEBUF_LEN];
    long *m_nRingBufLen;  //缓冲区的长度

    long *m_nDataLen;  //缓冲区数据的长度，循环覆盖之后，m_nDataLen永远等于m_nRingBufLen
    __int64 m_n64WriteSizeTotal;  //写数据的圈数
    long *m_nWritePos;//数据写的起始位置

public:
	void Free();
	void Reset();
	void Create(long nLen=0);
    void Attatch(char *pBuffer, long nBufferLen, bool bInitBuffer=true);
	char* GetBuffer()	{	return m_pszRingBuf;	}
	long GetRingBufLen() {	return *m_nRingBufLen;	}

    void Init(bool bInitBuffer=true);
	BOOL WriteBuf(char *pSrcBuf,long nLen);
    long ReadBuf(char *pDestBuf,long &nReadPos, long n64ReadSizeTotal, long nLen);
	long ReadBuf2(char *pDestBuf,long &nReadPos ,long n64ReadSizeTotal, long nLen);  //读取指定长度的数据，如果不足则不读取
    long GetReadDataTotalLen(long nWritePos, long nReadPos, long nDataLen, long nBufLen);
    long GetWritePos(){return *m_nWritePos;}
	long GetDataLen(){return *m_nDataLen;}

    //作废并丢弃套圈的报文数据
    BOOL ValidateBufErr(BOOL nSetReadPos,long &nReadPos,long n64ReadSizeTotal,long &nHasDataSize);
};


#endif

