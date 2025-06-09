// MemBuffer_Double.h: interface for the CMemBuffer_Double class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_MEMBUFFER_DOUBLE_H__)
#define _MEMBUFFER_DOUBLE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "RtMemBufScript.h"
#include "MemBufferDef.h"

class CMemBuffer_Double    : public CExBaseObject
{
public:	
	CMemBuffer_Double();
	virtual ~CMemBuffer_Double();
	CString m_strBufferID;   //�������ı�ʾ������ϵͳ�У��˱�ʾΨһ

	virtual UINT GetClassID()    {    return MEMCLASSID_DOUBLE;     }
public:
	virtual BOOL ExecScript(long nPos1Begin, long nPos1End, long nPos2Begin, long nPos2End)  {    return TRUE;     }

public:
	//��ʼ��
	void Init();
	void SetBufferLength(long lBufferLen);
	void SetDataFillBeginPos(long nDataFillBeginPos){m_nDataFillBeginPos = nDataFillBeginPos;}

	//�ڴ��ͷ�
	void FreeBuffer();

	//�ڴ濽��
	long CopyBuffer(long lLen, long lGap , BOOL bOffsetBuffer, long &lPos1Begin , long &lPos1End, long &lPos2Begin, long &lPos2End);
	long CopyBuffer(CMemBuffer_Double *pBuffer, long &lCopyBeginPos, long lGap = 1);
	long CopyBuffer(double *pBuffer, long lLen, long lGap = 1);
	long CopyBufferByPos(double *pBuffer, long lBeginPos, long lEndPos, long lGap = 1);

	//�������
	void AppendBuffer(CMemBuffer_Double *pBuffer);
	void AppendBuffer(double *pBuffer, long lLen);

	//������ز����Ļ�ȡ
	long GetDataLength();
	long GetDataFillBeginPosition();
	long GetBufferLength();
	double* GetBuffer();
	void SetDataLength(long nDataLength){m_nDataLength = nDataLength;/*WriteLogTxt();*/}


	void WriteLogTxt();
	
protected:
	long m_nBufferLength;//���泤��	
	long m_nDataFillBeginPos;//������俪ʼλ��,ʹ��CopyBuffer��ȡ���̶���������ʱ��Ҫ�����λ���һ�Σ�����ȡ��Ӧ��λ��
	long m_nDataLength;//ʵ�����ݵ㳤��
	double *m_pBuffer;
};

//���ϻ���������Դ����������
#define  COMPLEX_MEMBUFFER_SRCBUF_MAXCOUNT  32
class CComplexMemBuffer_Double : public CMemBuffer_Double
{
public:
	CComplexMemBuffer_Double();
	virtual ~CComplexMemBuffer_Double();
	
	virtual UINT GetClassID()    {    return MEMCLASSID_COMPLEXDOUBLE;     }
public:
	virtual BOOL ExecScript(long nPos1Begin, long nPos1End, long nPos2Begin, long nPos2End);
	void SetSrcMemBufferCount(long nnSrcMemBufCount)                  {   m_nSrcMemBufferCount = nnSrcMemBufCount;   }
	void SetSrcBuffer(long nIndex, CMemBuffer_Double *pBuffer) {   m_pSrcBuffer[nIndex] = pBuffer;              }
	
public:
	long  m_nSrcMemBufferCount;
	CMemBuffer_Double *m_pSrcBuffer[COMPLEX_MEMBUFFER_SRCBUF_MAXCOUNT];
	
//	CRtMemBufScript *m_pScript;

/*
#ifdef _debug_complex_channel
	void CreateScript();
#endif
*/
};

#endif // !defined(_MEMBUFFER_DOUBLE_H__)
