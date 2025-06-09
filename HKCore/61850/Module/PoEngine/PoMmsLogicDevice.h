
#pragma once

#include "PoMmsDataSet.h"
// CPoMmsLogicDevice 命令目标

class CPoMmsLogicDevice
{
public:
	ACSI_NODE *m_pACSI_NODE;  //设备的指针
	LD_NODE *m_pLD_NODE;      //逻辑设备的指针，类似于传统的CPU
	//	DWORD m_dwNodeType;       //节点的类型
	//数据的种类
	tagDA *m_pTagDA;
	DWORD m_dw_tagDA_Type;    

	static CPoMmsLogicDevice* _New_CDeviceNode_LD(ACSI_NODE *pACSI_NODE, LD_NODE *pLD_NODE)
	{
		ASSERT (pLD_NODE != NULL && pACSI_NODE != NULL);
		CPoMmsLogicDevice *pLDevice = new CPoMmsLogicDevice();
		pLDevice->m_pACSI_NODE = pACSI_NODE;  //设备的指针
		pLDevice->m_pLD_NODE = pLD_NODE;      //逻辑设备的指针，类似于传统的CPU
		return pLDevice;
	}

public:
	CPoMmsLogicDevice();
	virtual ~CPoMmsLogicDevice();

	virtual void OnFinalRelease();

public:
	virtual CPoMmsDataSet* GetItem(long nIndex);
	virtual CPoMmsDataSet* FindDataSet(const CString &strDataSetPath);

	CString GetName(void);
	void SetName(const CString &newVal);
	CString GetID(void);
	void SetID(const CString &newVal);
	long GetCount(void);
	CPoMmsData* FindData(const CString &strPath);
	CString GetXmlData(void);
	long SetXmlData(const CString &strXmlData);
};


