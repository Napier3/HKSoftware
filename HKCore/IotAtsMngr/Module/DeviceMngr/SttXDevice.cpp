//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttXDevice.cpp  CSttXDevice


#include "stdafx.h"
#include "SttXDevice.h"
#include "../Module/SttGlobalDef.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttXDevice::CSttXDevice()
{
	//初始化属性
	m_nSelect = 0;
	m_strDataType = XPARA_ID_device;

	//初始化成员变量
}

CSttXDevice::~CSttXDevice()
{
}

BOOL CSttXDevice::CopyOwn(CBaseObject* pDest)
{
	CDataGroup::CopyOwn(pDest);

	CSttXDevice *p = (CSttXDevice*)pDest;

	p->m_nSelect = m_nSelect;
	p->m_strSN = m_strSN;
	p->m_strModel = m_strModel;
	p->m_strType = m_strType;
	p->m_strCategoryID = m_strCategoryID;

	return TRUE;
}

CString CSttXDevice::GetSN()
{
	CString strValue;
	GetDataValue(STTX_DEVICE_ATTRID_SN, strValue);
	return strValue;
}

CString CSttXDevice::GetModel()
{
	CString strValue;
	GetDataValue(STTX_DEVICE_ATTRID_Model, strValue);
	return strValue;
}

CString CSttXDevice::GetType()
{
	CString strValue;
	GetDataValue(STTX_DEVICE_ATTRID_Type, strValue);
	return strValue;
}

CString CSttXDevice::GetCategoryID()
{
	CString strValue;
	GetDataValue(STTX_DEVICE_ATTRID_CategoryID, strValue);
	return strValue;
}


void CSttXDevice::SetSN(const CString &strValue)
{
	m_strSN = strValue;
	m_strName = strValue;
	m_strID = strValue;

	SetDataValue(STTX_DEVICE_ATTRID_SN, strValue, TRUE);
}

void CSttXDevice::SetModel(const CString &strValue)
{
	m_strModel = strValue;
	SetDataValue(STTX_DEVICE_ATTRID_Model, strValue, TRUE);
}

void CSttXDevice::SetType(const CString &strValue)
{
	m_strType = strValue;
	SetDataValue(STTX_DEVICE_ATTRID_Type, strValue, TRUE);
}

void CSttXDevice::SetCategoryID(const CString &strValue)
{
	m_strCategoryID = strValue;
	SetDataValue(STTX_DEVICE_ATTRID_CategoryID, strValue, TRUE);
}

void CSttXDevice::InitDevice()
{
	m_strSN = GetSN();
	m_strType = GetType();
	m_strModel = GetModel();
	m_strCategoryID = GetCategoryID();
	m_strID = m_strSN;  //ID等于SN
	m_strName = m_strSN;
}

