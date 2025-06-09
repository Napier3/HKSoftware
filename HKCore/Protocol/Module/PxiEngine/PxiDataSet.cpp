// PoDataSet.cpp : 实现文件
//

#include "stdafx.h"
#include "../Engine/PpEngineBaseApp.h"
#include "PxiDataSet.h"


// CPxiDataSet
CPxiDataSet::CPxiDataSet()
{
	m_pDataset = NULL;
}

CPxiDataSet::~CPxiDataSet()
{
}


void CPxiDataSet::OnFinalRelease()
{

}

// CPxiDataSet 消息处理程序

CString CPxiDataSet::GetName(void)
{

	CString strResult;

	ASSERT( m_pDataset != NULL);
	strResult = m_pDataset->m_strName;

	return strResult;
}

void CPxiDataSet::SetName(const CString &newVal)
{

	// TODO: 在此添加属性处理程序代码
}

CString CPxiDataSet::GetID(void)
{

	CString strResult;

	ASSERT( m_pDataset != NULL);
	strResult = m_pDataset->m_strID;

	return strResult;
}

void CPxiDataSet::SetID(CString newVal)
{

	// TODO: 在此添加属性处理程序代码
}

long CPxiDataSet::GetCount(void)
{

	ASSERT( m_pDataset != NULL);

	return m_pDataset->GetCount();
}

CPxiData* CPxiDataSet::GetItem(long nIndex)
{

	if (nIndex < 0 || nIndex >m_pDataset->GetCount())
	{
		return NULL;
	}

	CDvmData *pDA = (CDvmData*)m_pDataset->GetAt(nIndex);
	CPxiData *pPoData = CPxiData::_NewPoData(pDA);

	return pPoData;
}

CPxiData* CPxiDataSet::FindDataByID(const CString &strDataID)
{

	long nIndex = 0;
	CDvmData *pDA = NULL;
	CDvmData *pFind = NULL;

	pFind = (CDvmData *)m_pDataset->FindByID(strDataID);

	if (pFind == NULL)
	{
		return NULL;
	}

	CPxiData *pPoData = CPxiData::_NewPoData(pFind);

	return pPoData;
}

CPxiData* CPxiDataSet::FindDataByName(const CString &strName)
{

	// TODO: 在此添加调度处理程序代码

	return NULL;
}

CString CPxiDataSet::GetXmlData(void)
{

	CString strResult;

	if (m_pDataset != NULL)
	{
		m_pDataset->GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strResult);
	}
	else
	{
	
	}

	return strResult;
}

long CPxiDataSet::SetXmlData(const CString &strXmlData)
{

	if (m_pDataset == NULL)
	{
		return 0;
	}

	CDvmDataset oDataset;
    BSTR bstrXmlData;
    bstrXmlData = strXmlData.AllocSysString();
    oDataset.SetXml(bstrXmlData, CDataMngrXmlRWKeys::CDvmDatasetKey(), CDataMngrXmlRWKeys::g_pXmlKeys);
    ::SysFreeString(bstrXmlData);
	
	m_pDataset->InitValue(&oDataset, g_pTheEngineApp->m_pPpEngineConfig->m_nNoChangeWhenSame);

	return 0;
}


CString CPxiDataSet::GetXmlDataEx(void)
{

	CString strResult;

	if (m_pDataset != NULL)
	{
		m_pDataset->GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strResult);
	}
	else
	{
	}

	
	return strResult;
}

void CPxiDataSet::InitByDataset(CDvmDataset *pDataset)
{
    m_pDataset->InitValue(pDataset, g_pTheEngineApp->m_pPpEngineConfig->m_nNoChangeWhenSame);
}
