
#pragma once

#include "PoMmsValue.h"
// CPoMmsData 命令目标

class CPoMmsData
{
public:
	ACSI_NODE *m_pACSI_NODE;  //设备的指针
	LD_NODE *m_pLD_NODE;      //逻辑设备的指针
	LD_DATASET_INFO *m_pDataset;
	tagDA *m_pDA;
	CShortData *m_pShortData;

	static CPoMmsData* _NewPoData(ACSI_NODE *pACSI_NODE, LD_NODE *pLD_NODE, LD_DATASET_INFO *pDataset, tagDA *pDA)
	{
		CPoMmsData *pNew = new CPoMmsData();
		pNew->m_pACSI_NODE = pACSI_NODE;
		pNew->m_pLD_NODE = pLD_NODE;
		pNew->m_pDataset = pDataset;
		pNew->m_pDA = pDA;
		return pNew;
	}

	static CPoMmsData* _NewPoData(CShortData *pData)
	{
		CPoMmsData *pNew = new CPoMmsData();
		pNew->m_pShortData = pData;
		return pNew;
	}

public:
	CPoMmsData();
	virtual ~CPoMmsData();

	virtual void OnFinalRelease();

public:
	CString GetName(void);
	void SetName(const CString &newVal);
	CString GetID(void);
	void SetID(CString newVal);
	CString GetDataType(void);
	void SetDataType(const CString &newVal);
	CString GetValue(void);
	void SetValue(const CString &newVal);
	CString GetUnit(void);
	void SetUnit(const CString &newVal);
	CString GetMinValue(void);
	void SetMinValue(const CString &newVal);
	CString GetMaxValue(void);
	void SetMaxValue(const CString &newVal);
	long GetCount(void);
    CPoMmsValue* GetItem(long nIndex);
	long RegisterDataChangedWndMsg(ULONG hWnd, ULONG nWMsgID);
	long UnRegisterDataChangedWndMsg();
};


