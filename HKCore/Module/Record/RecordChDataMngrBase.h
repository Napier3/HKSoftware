//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapDeviceChRecordMngr.h  CRecordChDataMngrBase

#pragma once

#include "RecordChDataInterface.h"
#include "RtMemBuffer/MemBuffer.h"
#include "MR1200BaseApp.h"
#include "RecordTest/RecordTestCalThread.h"
#include "Draw/ViewAnalyse.h"

#define RCDCHDATA_ANALOG       (0X00A10000 + 0X00000001)
#define RCDCHDATA_BINARY       (0X00A10000 + 0X00000002)

#define RECORD_WAVE_DRAW_CHS_PER_PAGE  10


//ץ��ͨ��¼�����ݶ������ڼ�¼�ͱ��沨������
//m_pRecfChΪ̽��ͨ����������
class CRecordChDataBase : public CRecordChDataInterface
{
public:
	CRecordChDataBase();
	virtual ~CRecordChDataBase();

	virtual CMemBufferInterface* GetRecordBuffer()	{	return m_pMemBuffer;	}
	COLORREF m_crColor;
	CExBaseObject *m_pExternChRef; //ͨ����������
	CExBaseObject *m_pRcdCalVarRef; //���μ���ͨ������

	CString m_strHdID;   //Ӳ��ͨ��ID������װ��ID
	CString m_strChID;   //ͨ��ID
public:
	virtual void SetBufferLen(long nLen);
	virtual double GetRange()	{	return 1;	}
	virtual UINT GetClassID()	{		ASSERT (m_pExternChRef != NULL);		return m_pExternChRef->GetClassID();	}
	virtual void CalMinMax(){};

	CString GetName();

	void SetPosition(long nPos, long nDataCount)	{		m_pMemBuffer->SetPosition(nPos, nDataCount);	}
	void SetHdIndex(long nIndex)	{	m_pMemBuffer->m_nHdIndex = nIndex;	}
	long GetHdIndex()	{	return m_pMemBuffer->m_nHdIndex;	}
	void SetChIndex(long nIndex)	{	m_pMemBuffer->m_nChIndex = nIndex;	}
	long GetChIndex()	{	return m_pMemBuffer->m_nChIndex;	}

protected:
	CMemBufferInterface *m_pMemBuffer;
};

class CRecordChDataAnalog : public CRecordChDataBase
{
public:
	CRecordChDataAnalog();
	virtual ~CRecordChDataAnalog();

	virtual UINT GetClassID() {    return RCDCHDATA_ANALOG;   }

public:
	virtual void AddRcdData(WORD wValue);
	virtual void AddRcdData(long nValue);
	virtual void AddRcdData(float fValue)	;
	virtual void AddRcdData(double dValue);
	virtual void AddRcdData(long wValue, long nPos)	;

	virtual void AddRcdData(WORD wValue, long nPos)	;
	virtual void AddRcdData(float fValue, long nPos);
	virtual void AddRcdData(double dValue, long nPos);


public:
	virtual double GetRange();
	virtual double GetChRateVal();
	virtual double* GetChRate();
	virtual UINT GetChType();
	virtual void CalMinMax();

	void SetMemBuffer_Long();
	void SetMemBuffer_Float();

protected:
	double m_fMinValue;
	double m_fMaxValue;
	double m_fChRate;

	CMemBuffer_Long *m_pBufferLong;
	CMemBuffer_Float *m_pBufferFloat;

	virtual void CalMinMax_Long();
	virtual void CalMinMax_Float();

};

class CRecordChDataBinary : public CRecordChDataBase
{
public:
	CRecordChDataBinary();
	virtual ~CRecordChDataBinary();

	virtual UINT GetClassID() {    return RCDCHDATA_BINARY;   }

public:
	virtual void AddRcdData(WORD wValue)	{		m_oBufferUShort.AddValue(wValue);	}
	virtual void AddRcdData(long nValue)		{		m_oBufferUShort.AddValue(nValue);	}
	virtual void AddRcdData(float fValue)			{	}
	virtual void AddRcdData(double dValue)		{	}
	virtual void AddRcdData(long wValue, long nPos)		{		m_oBufferUShort.SetValue(wValue, nPos);	}

	virtual void AddRcdData(WORD wValue, long nPos)	{	}
	virtual void AddRcdData(float fValue, long nPos)		{	}
	virtual void AddRcdData(double dValue, long nPos)	{	}

protected:
	CMemBuffer_Long m_oBufferUShort;
};


/*
¼������ת��Ϊ��ͼ�Ĺ��̣�
1����ʼ��ͨ�����ݹ����������   InitRecordChDataMngr
2����ʼ��¼��ͨ�����ݶ���   InitRecordChDatas
3������¼��ͨ�����ݶ��󣬴���RecordTest�ļ������   InitRecordTest
4��������ʾҳ�棬��ʼ����ǰ��ͼҲ�Ļ�ͼ���ݶ���CViewAnalyse
5�����¼�����ݵ���RecordChDatas
6�����в��β������㡢��ͼ
*/

class CRecordChDataMngrBase : public CExBaseList
{
public:
	CRecordChDataMngrBase();
	virtual ~CRecordChDataMngrBase();

	//��ʼ��ͨ�����ݹ����������
	void InitRecordChDataMngr();
	void ExitRecordChDataMngr();

public:
	//2����ʼ��¼��ͨ�����ݶ���   InitRecordChDatas
	virtual void InitRecordChDatas() = 0;

	//��ʼ¼��֮ǰ����ʼ��¼������
	//3������¼��ͨ�����ݶ��󣬴���RecordTest�ļ������   InitRecordTest
	virtual void InitRecordTest();
	virtual long CreateVariables();   //�������β��������õı���
	virtual void InitRecordDrawObjcontrol();  //��ʼ����ͼ���Ʋ���
	virtual void InitRecordTest_Attrs();  //��ʼ�����μ������Բ���

	virtual void GetCurrDeviceAllRcdVariables();

	//���һ��ͨ������¼ͨ������
	CRecordChDataBase* FindByExternCh(CExBaseObject *pCh);

	//5�����¼�����ݵ���RecordChDatas
	virtual void FillRcdChDataBuffers()	 = 0;

public:
	virtual void Record(CExBaseList *pListExternCh);
	virtual long GetHdIndex(CExBaseList *pListExternCh);
	virtual CRecordChDataBase* AddRecordCh(CExBaseObject *pCh);
	virtual CRecordChDataBase* RemoveRecord(CExBaseObject *pCh);
	virtual void AdjustRecordChRange();
	virtual void Release();
	virtual BOOL IsExternCh_Analog(CExBaseObject *pExternCh);
	virtual BOOL IsExternCh_Binary(CExBaseObject *pExternCh);
	virtual void AttachToExternCh(CExBaseObject *pExternCh, CRecordChDataBase *pRcdChData);

	//����
	virtual CRecordChDataAnalog* NewRcdChDataAnalog();
	virtual CRecordChDataBinary* NewRcdChDataBinary();
	virtual void SetBufferLen(long nLen);

protected:
	CExBaseList m_listRemove;
	long m_nCurrRcdChIndex;
	BOOL m_bInitTimeAxis;

public:
	CRecordTest *m_pRecordTest;  
	CExBaseList  *m_pVariableMngr;
	CViewAnalyse *m_pViewAnalyse;

	void SetViewAnalyse(CViewAnalyse *p);
	LRESULT OnVariableAddRemoved(WPARAM wParam, LPARAM lParam);
	void CalIndex_NextPage();
	void CalIndex_PrevPage();

	CExBaseList m_listRcdVariable;	//��ǰCapDevice��¼��ͨ���������ڶ��豸������ʾ
	long m_nChCountPerPage;
	void UpdateDrawVariablesRange();
	void SetDrawVariablesRange();
	void InitVariablesRangeByRcdChData();

protected:
	CRtSingleVariable* InitAnalogVariable(CRecordChDataAnalog *pAnalog, long &nIndex);
	CRtBinaryVariable* InitBinaryVariable(CRecordChDataBinary *pBinary, long& nIndex);
	BOOL IsChRecordCreated(CRecordChDataBase *pChRecord);
	virtual void InitVariablePhaseID(CRtSingleVariable *pVariable);
};
