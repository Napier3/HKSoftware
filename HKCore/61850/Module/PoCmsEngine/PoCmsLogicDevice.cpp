// PoLogicDevice.cpp :
//

#include "stdafx.h"
#include "PoCmsLogicDevice.h"


// CPoCmsLogicDevice
CPoCmsLogicDevice::CPoCmsLogicDevice()
{

}

CPoCmsLogicDevice::~CPoCmsLogicDevice()
{
}


CPoMmsDataSet* CPoCmsLogicDevice::GetItem(long nIndex)
{
	ASSERT (m_pLD_NODE != NULL);

	if (nIndex < 0 || nIndex >= m_pLD_NODE->numDaSet)
	{
		return NULL;
	}

	CPoCmsDataSet *pPoDataset = NULL;
	LD_DATASET_INFO *pDataset = &m_pLD_NODE->DataInfo[nIndex];

	pPoDataset = CPoCmsDataSet::_NewPoCmsDataSet(m_pACSI_NODE, m_pLD_NODE, pDataset);

	return pPoDataset;
}

CPoMmsDataSet* CPoCmsLogicDevice::FindDataSet(const CString &strDataSetPath)
{
	LD_DATASET_INFO *pDataset = NULL;
	pDataset = mms_FindDataset(m_pLD_NODE, strDataSetPath);

	if (pDataset == NULL)
	{
		return NULL;
	}

	CPoCmsDataSet *pPoDataset = CPoCmsDataSet::_NewPoCmsDataSet(m_pACSI_NODE, m_pLD_NODE, pDataset);

	return pPoDataset;
}
