#ifndef _CRingMemBuf_h__
#define _CRingMemBuf_h__

//#include "../../../Module/CriticalSection/SynCriticalSection.h"
#include "SttRcdBufferRcvMsg.h"

#define DEFAULT_CIRCLEBUF_LEN	20480000
#define DEFAULT_CIRCLEBUF_LEN2	20479988

//ǰ�᣺�����ٶȱ������д���ٶ�

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
	bool m_bIsCreateOwn; //�Ƿ�Ϊ�������Ļ�����
    char *m_pszRealBuffer;
    char *m_pszRingBuf;//[DEFAULT_CIRCLEBUF_LEN];
    long *m_nRingBufLen;  //�������ĳ���

    long *m_nDataLen;  //���������ݵĳ��ȣ�ѭ������֮��m_nDataLen��Զ����m_nRingBufLen
    __int64 m_n64WriteSizeTotal;  //д���ݵ�Ȧ��
    long *m_nWritePos;//����д����ʼλ��

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
	long ReadBuf2(char *pDestBuf,long &nReadPos ,long n64ReadSizeTotal, long nLen);  //��ȡָ�����ȵ����ݣ���������򲻶�ȡ
    long GetReadDataTotalLen(long nWritePos, long nReadPos, long nDataLen, long nBufLen);
    long GetWritePos(){return *m_nWritePos;}
	long GetDataLen(){return *m_nDataLen;}

    //���ϲ�������Ȧ�ı�������
    BOOL ValidateBufErr(BOOL nSetReadPos,long &nReadPos,long n64ReadSizeTotal,long &nHasDataSize);
};


#endif

