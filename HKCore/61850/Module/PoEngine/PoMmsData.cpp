// PoData.cpp : ʵ����??
//

#include "stdafx.h"
#include "PoMmsData.h"


// CPoMmsData
CPoMmsData::CPoMmsData()
{
	m_pShortData = NULL;
	m_pACSI_NODE = NULL;
	m_pLD_NODE = NULL;
	m_pDataset = NULL;
	m_pDA = NULL;
}

CPoMmsData::~CPoMmsData()
{
}


void CPoMmsData::OnFinalRelease()
{

}

// CPoMmsData ��Ϣ�������

CString CPoMmsData::GetName(void)
{
	

	CString strResult;

	ASSERT (m_pDA != NULL);
	
	return strResult;
}

void CPoMmsData::SetName(const CString &newVal)
{
	

	// TODO: �ڴ�������Դ���������
}

CString CPoMmsData::GetID(void)
{
	

	CString strResult;

	ASSERT (m_pDA != NULL);
#ifdef _use_mms_string
	strResult = mms_string(&m_pDA->DAValue.mmsName);
#else
	strResult = m_pDA->DAValue.mmsName;
#endif

	return strResult;
}

void CPoMmsData::SetID(CString newVal)
{
	

	// TODO: �ڴ�������Դ���������
}

CString CPoMmsData::GetDataType(void)
{
	

	CString strResult;

	ASSERT (m_pDA != NULL);
	strResult = m_pDA->DataType;

	return strResult;
}

void CPoMmsData::SetDataType(const CString &newVal)
{
	

	// TODO: �ڴ�������Դ���������
}

CString CPoMmsData::GetValue(void)
{
	

	CString strResult;

	if (m_pShortData != NULL)
	{
		strResult = m_pShortData->m_strValue;
	}
	else
	{
		if (m_pDA != NULL)
		{
			strResult = mms_GetDAValue(m_pDA);
		}
	}

	return strResult;
}

void CPoMmsData::SetValue(const CString &newVal)
{
	

	// TODO: �ڴ�������Դ���������
}

CString CPoMmsData::GetUnit(void)
{
	

	CString strResult;

	ASSERT (m_pDA != NULL);
	//strResult = m_pDA->DAUnite.

	return strResult;
}

void CPoMmsData::SetUnit(const CString &newVal)
{
	

	// TODO: �ڴ�������Դ���������
}

CString CPoMmsData::GetMinValue(void)
{
	

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������

	return strResult;
}

void CPoMmsData::SetMinValue(const CString &newVal)
{
	

	// TODO: �ڴ�������Դ���������
}

CString CPoMmsData::GetMaxValue(void)
{
	

	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������

	return strResult;
}

void CPoMmsData::SetMaxValue(const CString &newVal)
{
	

	// TODO: �ڴ�������Դ���������
}

long CPoMmsData::GetCount(void)
{
	

	// TODO: �ڴ���ӵ��ȴ���������

	return 0;
}

CPoMmsValue* CPoMmsData::GetItem(long nIndex)
{
	

	// TODO: �ڴ���ӵ��ȴ���������

	return NULL;
}


long CPoMmsData::RegisterDataChangedWndMsg(ULONG hWnd, ULONG nWMsgID)
{
	

	// TODO: �ڴ���ӵ��ȴ���������

	return 0;
}

long CPoMmsData::UnRegisterDataChangedWndMsg()
{
	

	// TODO: �ڴ���ӵ��ȴ���������

	return 0;
}
