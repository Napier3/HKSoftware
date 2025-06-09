
#pragma once

#include "PxiValue.h"
// CPxiData 

class CPxiData
{
public:
	CDvmData *m_pDA;

	static CPxiData* _NewPoData(CDvmData *pDA)
	{
		CPxiData *pNew = new CPxiData();
		pNew->m_pDA = pDA;
		return pNew;
	}

public:
	CPxiData();
	virtual ~CPxiData();

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
    CPxiValue* GetItem(long nIndex);
	long RegisterDataChangedWndMsg(ULONG hWnd, ULONG nWMsgID);
	long UnRegisterDataChangedWndMsg();
};


