// PoLogicDevice.cpp : 实现文件
//

#include "stdafx.h"
#include "../Engine/PpEngineBaseApp.h"
#include "PxiLogicDevice.h"


// CPxiLogicDevice

CPxiLogicDevice::CPxiLogicDevice()
{
	
}

CPxiLogicDevice::~CPxiLogicDevice()
{
}


void CPxiLogicDevice::OnFinalRelease()
{

}

// CPxiLogicDevice 消息处理程序

CString CPxiLogicDevice::GetName(void)
{
	CString strResult;

	if (m_pLD_NODE != NULL)
	{
		strResult = m_pLD_NODE->m_strName;
	}

	return strResult;
}

void CPxiLogicDevice::SetName(const CString &newVal)
{

	// TODO: 在此添加属性处理程序代码
}

CString CPxiLogicDevice::GetID(void)
{

	CString strResult;

	if (m_pLD_NODE != NULL)
	{
		strResult = m_pLD_NODE->m_strID;
	}

	return strResult;
}

void CPxiLogicDevice::SetID(const CString &newVal)
{

}

long CPxiLogicDevice::GetCount(void)
{
	ASSERT (m_pLD_NODE != NULL);

	return m_pLD_NODE->GetCount();
}

CPxiDataSet* CPxiLogicDevice::GetItem(long nIndex)
{

	ASSERT (m_pLD_NODE != NULL);

	if (nIndex < 0 || nIndex >= m_pLD_NODE->GetCount())
	{
		return NULL;
	}

	CPxiDataSet *pPoDataset = NULL;
	CDvmDataset *pDataset = (CDvmDataset*)m_pLD_NODE->GetAt(nIndex);

	pPoDataset = CPxiDataSet::_NewPoDataset(pDataset);

	return pPoDataset;
}

CPxiDataSet* CPxiLogicDevice::FindDataSet(const CString &strDataSetPath)
{
	CDvmDataset *pDataset = NULL;
	pDataset = (CDvmDataset*)m_pLD_NODE->FindByID(strDataSetPath);

	if (pDataset == NULL)
	{
		return NULL;
	}

	CPxiDataSet *pPoDataset = CPxiDataSet::_NewPoDataset(pDataset);

	return pPoDataset;
}

CPxiData* CPxiLogicDevice::FindData(const CString &strPath)
{

	CDvmData *pDA = NULL;
	CDvmDataset *pDataset = NULL;
	pDA = (CDvmData*)m_pLD_NODE->SelectData(strPath);

	if (pDA == NULL)
	{
		return NULL;
	}

	CPxiData *pPoData = CPxiData::_NewPoData(pDA);

	return pPoData;
}

CString CPxiLogicDevice::GetXmlData(void)
{

	CString strResult;

	if (m_pLD_NODE != NULL)
	{
		m_pLD_NODE->GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strResult);
	}

	return strResult;
}

long CPxiLogicDevice::SetXmlData(const CString &strXmlData)
{

	//mms_SetXml(m_pLD_NODE, strXmlData);

	return 0;
}
