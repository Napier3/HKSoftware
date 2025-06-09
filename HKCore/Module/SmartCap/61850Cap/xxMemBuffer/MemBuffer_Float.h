// MemBuffer_Float.h: interface for the CMemBuffer_Float class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_MEMBUFFER_FLOAT_H__)
#define _MEMBUFFER_FLOAT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\..\..\Module\BaseClass\ExBaseList.h"
#include "MemBufferDef.h"

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
	long CopyBuffer(long lLen, long lGap , BOOL bOffsetBuffer, long &lPos1Begin , long &lPos1End, long &lPos2Begin, long &lPos2End);
	long CopyBuffer(CMemBuffer_Float *pBuffer, long &lCopyBeginPos, long lGap = 1);
	long CopyBuffer(float *pBuffer, long lLen, long lGap = 1);
	long CopyBufferByPos(float *pBuffer, long lBeginPos, long lEndPos, long lGap = 1);
	long AddValue(float *pValue);
	long AddValue(float fValue);
	
	//�������
	void AppendBuffer(CMemBuffer_Float *pBuffer);
	void AppendBuffer(float *pBuffer, long lLen);
	void AttachBuffer(float *pBuffer, long lLen);
	void DettachBuffer();

	//������ز����Ļ�ȡ
	virtual long GetDataLength();
	virtual long GetDataFillBeginPosition();
	virtual long GetBufferLength();
	virtual void OffsetDataFillBeginPosition(long nLen);
	float* GetBuffer();
	
	//��ȡFillBeginPos��ǰһ����������
	double GetCurrValue();
protected:
	long m_nBufferLength;	
	long m_nDataFillBeginPos;
	long m_nDataLength;
	float *m_pBuffer;

};


#endif // !defined(_MEMBUFFER_FLOAT_H__)
