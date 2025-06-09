// PoData.cpp : 实现文件
//

#include "stdafx.h"
#include "../Engine/PpEngineBaseApp.h"
#include "PxiData.h"


// CPxiData
CPxiData::CPxiData()
{

}

CPxiData::~CPxiData()
{
}

CString CPxiData::GetName(void)
{

	CString strResult;

	ASSERT (m_pDA != NULL);

	return strResult;
}

void CPxiData::SetName(const CString &newVal)
{

	// TODO: 在此添加属性处理程序代码
}

CString CPxiData::GetID(void)
{

	CString strResult;

	ASSERT (m_pDA != NULL);
	strResult = m_pDA->m_strID;

	return strResult;
}

void CPxiData::SetID(CString newVal)
{

	// TODO: 在此添加属性处理程序代码
}

CString CPxiData::GetDataType(void)
{

	CString strResult;

	ASSERT (m_pDA != NULL);
	strResult = m_pDA->m_strDataType;

	return strResult;
}

void CPxiData::SetDataType(const CString &newVal)
{

	// TODO: 在此添加属性处理程序代码
}

CString CPxiData::GetValue(void)
{

	CString strResult;

	if (m_pDA != NULL)
	{
		strResult = m_pDA->m_strValue;
	}

	return strResult;
}

void CPxiData::SetValue(const CString &newVal)
{

	// TODO: 在此添加属性处理程序代码
}

CString CPxiData::GetUnit(void)
{

	CString strResult;

	ASSERT (m_pDA != NULL);
	if (m_pDA != NULL)
	{
		strResult = m_pDA->m_strUnit;
	}

	return strResult;
}

void CPxiData::SetUnit(const CString &newVal)
{

	// TODO: 在此添加属性处理程序代码
}

CString CPxiData::GetMinValue(void)
{

	CString strResult;

	if (m_pDA != NULL)
	{
		strResult = m_pDA->m_strMin;
	}

	return strResult;
}

void CPxiData::SetMinValue(const CString &newVal)
{

	// TODO: 在此添加属性处理程序代码
}

CString CPxiData::GetMaxValue(void)
{

	CString strResult;

	if (m_pDA != NULL)
	{
		strResult = m_pDA->m_strMax;
	}

	return strResult;
}

void CPxiData::SetMaxValue(const CString &newVal)
{

	// TODO: 在此添加属性处理程序代码
}

long CPxiData::GetCount(void)
{

	if (m_pDA != NULL)
	{
		return m_pDA->GetCount();
	}

	return 0;
}

CPxiValue* CPxiData::GetItem(long nIndex)
{

	// TODO: 在此添加调度处理程序代码

	return NULL;
}


long CPxiData::RegisterDataChangedWndMsg(ULONG hWnd, ULONG nWMsgID)
{

	// TODO: 在此添加调度处理程序代码

	return 0;
}

long CPxiData::UnRegisterDataChangedWndMsg()
{

	// TODO: 在此添加调度处理程序代码

	return 0;
}

