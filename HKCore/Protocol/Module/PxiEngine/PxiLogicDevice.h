
#pragma once
#include "PxiDataSet.h"

// CPxiLogicDevice 

class CPxiLogicDevice
{
public:
	CDvmLogicDevice *m_pLD_NODE;

	static CPxiLogicDevice* _New_CDeviceNode_LD(CDvmLogicDevice *pLogicDevice)
	{
		ASSERT (pLogicDevice != NULL);
		CPxiLogicDevice *pLDevice = new CPxiLogicDevice();
		pLDevice->m_pLD_NODE = pLogicDevice;  //设备的指针
		return pLDevice;
	}

public:
	CPxiLogicDevice();
	virtual ~CPxiLogicDevice();

	virtual void OnFinalRelease();

	CString GetName(void);
	void SetName(const CString &newVal);
	CString GetID(void);
	void SetID(const CString &newVal);
	long GetCount(void);
	CPxiDataSet* GetItem(long nIndex);
	CPxiDataSet* FindDataSet(const CString &strDataSetPath);
	CPxiData* FindData(const CString &strPath);
	CString GetXmlData(void);
	long SetXmlData(const CString &strXmlData);
};


