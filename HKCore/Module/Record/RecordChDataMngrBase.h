//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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


//抓包通道录波数据对象，用于记录和保存波形数据
//m_pRecfCh为探测通道对象引用
class CRecordChDataBase : public CRecordChDataInterface
{
public:
	CRecordChDataBase();
	virtual ~CRecordChDataBase();

	virtual CMemBufferInterface* GetRecordBuffer()	{	return m_pMemBuffer;	}
	COLORREF m_crColor;
	CExBaseObject *m_pExternChRef; //通道对象引用
	CExBaseObject *m_pRcdCalVarRef; //波形计算通道引用

	CString m_strHdID;   //硬件通道ID或者是装置ID
	CString m_strChID;   //通道ID
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
录波数据转换为绘图的过程：
1、初始化通道数据管理对象自身   InitRecordChDataMngr
2、初始化录波通道数据对象   InitRecordChDatas
3、根据录波通道数据对象，创建RecordTest的计算对象   InitRecordTest
4、根据显示页面，初始化当前绘图也的绘图数据对象：CViewAnalyse
5、填充录波数据到：RecordChDatas
6、进行波形参数计算、绘图
*/

class CRecordChDataMngrBase : public CExBaseList
{
public:
	CRecordChDataMngrBase();
	virtual ~CRecordChDataMngrBase();

	//初始化通道数据管理对象自身
	void InitRecordChDataMngr();
	void ExitRecordChDataMngr();

public:
	//2、初始化录波通道数据对象   InitRecordChDatas
	virtual void InitRecordChDatas() = 0;

	//开始录波之前，初始化录波处理
	//3、根据录波通道数据对象，创建RecordTest的计算对象   InitRecordTest
	virtual void InitRecordTest();
	virtual long CreateVariables();   //创建波形参数计算用的变量
	virtual void InitRecordDrawObjcontrol();  //初始化绘图控制参数
	virtual void InitRecordTest_Attrs();  //初始化波形计算属性参数

	virtual void GetCurrDeviceAllRcdVariables();

	//添加一个通道，记录通道波形
	CRecordChDataBase* FindByExternCh(CExBaseObject *pCh);

	//5、填充录波数据到：RecordChDatas
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

	//创建
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

	CExBaseList m_listRcdVariable;	//当前CapDevice的录波通道，适用于多设备单独显示
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
