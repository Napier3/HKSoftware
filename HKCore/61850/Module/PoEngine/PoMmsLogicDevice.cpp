// PoLogicDevice.cpp : 实现????
//

#include "stdafx.h"
#include "PoMmsLogicDevice.h"


// CPoMmsLogicDevice
CPoMmsLogicDevice::CPoMmsLogicDevice()
{
	m_pACSI_NODE = NULL;  //设备的指针
	m_pLD_NODE = NULL;      //逻辑设备的指针，类似于传统的CPU
	m_pTagDA = NULL;
	m_dw_tagDA_Type = -1;    
}

CPoMmsLogicDevice::~CPoMmsLogicDevice()
{
}


void CPoMmsLogicDevice::OnFinalRelease()
{

}

// CPoMmsLogicDevice 消息处理程序

CString CPoMmsLogicDevice::GetName(void)
{
	

	CString strResult;

	if (m_pLD_NODE != NULL)
	{
		strResult = m_pLD_NODE->LDDesc;
	}

	return strResult;
}

void CPoMmsLogicDevice::SetName(const CString &newVal)
{
	

	// TODO: 在此添加属性处理程序代码
}

CString CPoMmsLogicDevice::GetID(void)
{
	

	CString strResult;

	if (m_pLD_NODE != NULL)
	{
		strResult = m_pLD_NODE->LDName;
	}

	return strResult;
}

void CPoMmsLogicDevice::SetID(const CString &newVal)
{
	

	// TODO: 在此添加属性处理程序代码
}

long CPoMmsLogicDevice::GetCount(void)
{
	

	ASSERT (m_pLD_NODE != NULL);

	return m_pLD_NODE->numDaSet;
}

CPoMmsDataSet* CPoMmsLogicDevice::GetItem(long nIndex)
{
	

	ASSERT (m_pLD_NODE != NULL);

	if (nIndex < 0 || nIndex >= m_pLD_NODE->numDaSet)
	{
		return NULL;
	}

	CPoMmsDataSet *pPoDataset = NULL;
	LD_DATASET_INFO *pDataset = &m_pLD_NODE->DataInfo[nIndex];

	pPoDataset = CPoMmsDataSet::_NewPoDataset(m_pACSI_NODE, m_pLD_NODE, pDataset);

	return pPoDataset;
}

CPoMmsDataSet* CPoMmsLogicDevice::FindDataSet(const CString &strDataSetPath)
{
	

	LD_DATASET_INFO *pDataset = NULL;
	pDataset = mms_FindDataset(m_pLD_NODE, strDataSetPath);

	if (pDataset == NULL)
	{
		return NULL;
	}

	CPoMmsDataSet *pPoDataset = CPoMmsDataSet::_NewPoDataset(m_pACSI_NODE, m_pLD_NODE, pDataset);

	return pPoDataset;
}

CPoMmsData* CPoMmsLogicDevice::FindData(const CString &strPath)
{
	

	tagDA *pDA = NULL;
	LD_DATASET_INFO *pDataset = NULL;
	pDA = mms_FindData(m_pLD_NODE, &pDataset, strPath);

	if (pDA == NULL)
	{
		return NULL;
	}

	CPoMmsData *pPoData = CPoMmsData::_NewPoData(m_pACSI_NODE, m_pLD_NODE, pDataset, pDA);

	return pPoData;
}

CString CPoMmsLogicDevice::GetXmlData(void)
{
	

	CString strResult;
	mms_GetXml(m_pLD_NODE, strResult);

	return strResult;
}

long CPoMmsLogicDevice::SetXmlData(const CString &strXmlData)
{
	

	mms_SetXml(m_pLD_NODE, strXmlData);

	return 0;
}
