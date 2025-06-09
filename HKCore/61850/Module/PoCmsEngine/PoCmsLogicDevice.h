
#pragma once

#include "PoCmsDataSet.h"
#include "../PoEngine/PoMmsLogicDevice.h"

class CPoCmsLogicDevice : public CPoMmsLogicDevice
{
public:
	static CPoCmsLogicDevice* _New_CDeviceNode_LD(ACSI_NODE *pACSI_NODE, LD_NODE *pLD_NODE)
	{
		ASSERT (pLD_NODE != NULL && pACSI_NODE != NULL);
		CPoCmsLogicDevice *pLDevice = new CPoCmsLogicDevice();
		pLDevice->m_pACSI_NODE = pACSI_NODE;  //设备的指针
		pLDevice->m_pLD_NODE = pLD_NODE;      //逻辑设备的指针，类似于传统的CPU
		return pLDevice;
	}

public:
	CPoCmsLogicDevice();
	virtual ~CPoCmsLogicDevice();

	virtual CPoMmsDataSet* GetItem(long nIndex);
	virtual CPoMmsDataSet* FindDataSet(const CString &strDataSetPath);
};


