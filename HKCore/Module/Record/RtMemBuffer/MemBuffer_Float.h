// MemBuffer_Float.h: interface for the CMemBuffer_Float class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_MEMBUFFER_FLOAT_H__)
#define _MEMBUFFER_FLOAT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../RtScriptBase/RtScriptBase.h"
#include "MemBufferDef.h"
#include "RtMemBufScript.h"

class CMemBuffer_Float    : public CMemBufferInterface
{
public:	
	CMemBuffer_Float();
	virtual ~CMemBuffer_Float();
	CString m_strBufferID;   //�������ı�ʾ������ϵͳ�У��˱�ʾΨһ
	double  *m_pdValue;

	virtual UINT GetClassID()    {    return MEMCLASSID_FLOAT;     }
	
	DWORD m_dwFreqZeroPosition[MAX_FREQ_ZERO_POS_BUFFER];
	UINT  m_nFreqZeroPosCount;
	
	virtual long CopyBuffer(CMemBufferInterface *pBuffer, long &lCopyBeginPos, long lGap);
public:
	void BuildComplexBufferScript();
	virtual BOOL ExecScript(long nPos1Begin, long nPos1End, long nPos2Begin, long nPos2End)  {  return TRUE;  }

public:
	//��ʼ��
	virtual void Init();
	void SetBufferLength(long lBufferLen);
	void SetDataLength(long lDataLength)		{	m_nDataLength = lDataLength; }
	void SetFillBeginPos(long lFillBeginPos)	{	m_nDataFillBeginPos = lFillBeginPos;}

	//�ڴ��ͷ�
	void FreeBuffer();

	//�ڴ濽��
	//long CopyBuffer(long lLen, long lGap , BOOL bOffsetBuffer, long &lPos1Begin , long &lPos1End, long &lPos2Begin, long &lPos2End);
	long CopyBuffer(CMemBuffer_Float *pBuffer, long &lCopyBeginPos, long lGap = 1);
	long CopyBuffer(float *pBuffer, long lLen, long lGap = 1);
	long CopyBufferByPos(float *pBuffer, long lBeginPos, long lEndPos, long lGap = 1);
	long AddValue(float *pValue);
	long AddValue(float fValue);

	void SetValue(long nIndex, float fValue)
	{
		ASSERT (0 <= nIndex && nIndex < m_nBufferLength);
		m_pdValue[nIndex] = fValue;
	}
	
	//�������
	void AppendBuffer(CMemBuffer_Float *pBuffer);
	void AppendBuffer(float *pBuffer, long lLen);
	void AttachBuffer(float *pBuffer, long lLen);
	void DettachBuffer();

	//������ز����Ļ�ȡ
	virtual void OffsetDataFillBeginPosition(long nLen);
	virtual float* GetBuffer_float();
	
	//��ȡFillBeginPos��ǰһ����������
	double GetCurrValue();
protected:
	float *m_pBuffer;

};

//���ϻ���������Դ����������
#define  COMPLEX_MEMBUFFER_SRCBUF_MAXCOUNT  32
class CComplexMemBuffer_Float : public CMemBuffer_Float
{
public:
	CComplexMemBuffer_Float();
	virtual ~CComplexMemBuffer_Float();
	
	virtual UINT GetClassID()    {    return MEMCLASSID_COMPLEXFLOAT;     }
public:
	virtual BOOL ExecScript(long nPos1Begin, long nPos1End, long nPos2Begin, long nPos2End);
	void SetSrcMemBufferCount(long nnSrcMemBufCount)                  {   m_nSrcMemBufferCount = nnSrcMemBufCount;   }
	void SetSrcBuffer(long nIndex, CMemBuffer_Float *pBuffer) {   m_pSrcBuffer[nIndex] = pBuffer;              }
	
public:
	long  m_nSrcMemBufferCount;
	CMemBuffer_Float *m_pSrcBuffer[COMPLEX_MEMBUFFER_SRCBUF_MAXCOUNT];
	
	CRtComplexBufUShortFloatScript *m_pScript;

};

#endif // !defined(_MEMBUFFER_FLOAT_H__)
