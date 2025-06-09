//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PpCfgDevice.cpp  CPpCfgDevice


#include "stdafx.h"
#include "PpCfgDevice.h"
#include "PpCfgDevices.h"

CPpCfgDevice::CPpCfgDevice()
{
	//初始化属性

	//初始化成员变量
	m_pEngineDataRef = NULL;
	m_pDeviceCmmConfig = NULL;
}

CPpCfgDevice::~CPpCfgDevice()
{
	m_listCmmCfg.RemoveAll();
}

long CPpCfgDevice::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);
	CClassProcotolProjectXmlRWKeys *pXmlKeys = (CClassProcotolProjectXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTemplateFileKey, oNode, m_strTemplateFile);
	xml_GetAttibuteValue(pXmlKeys->m_strDdvmFileKey, oNode, m_strDdvmFile);
	return 0;
}

long CPpCfgDevice::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CClassProcotolProjectXmlRWKeys *pXmlKeys = (CClassProcotolProjectXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTemplateFileKey, oElement, m_strTemplateFile);
	xml_SetAttributeValue(pXmlKeys->m_strDdvmFileKey, oElement, m_strDdvmFile);
	return 0;
}

long CPpCfgDevice::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseList::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strTemplateFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strDdvmFile);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strTemplateFile);
		BinarySerializeRead(oBinaryBuffer, m_strDdvmFile);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strTemplateFile);
		BinarySerializeWrite(oBinaryBuffer, m_strDdvmFile);
	}
	return 0;
}

void CPpCfgDevice::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;
	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DMCLASSID_DEVICECMMCONFIG)
		{
			m_pDeviceCmmConfig = (CDeviceCmmConfig*)p;
		}

	}

	if (m_pDeviceCmmConfig == NULL)
	{
		m_pDeviceCmmConfig = (CDeviceCmmConfig*)AddNewChild(new CDeviceCmmConfig());
	}

}

BOOL CPpCfgDevice::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CPpCfgDevice *p = (CPpCfgDevice*)pObj;

	if(m_strTemplateFile != p->m_strTemplateFile)
	{
		return FALSE;
	}

	if(m_strDdvmFile != p->m_strDdvmFile)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPpCfgDevice::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPpCfgDevice *p = (CPpCfgDevice*)pDest;

	p->m_strTemplateFile = m_strTemplateFile;
	p->m_strDdvmFile = m_strDdvmFile;
	return TRUE;
}

CBaseObject* CPpCfgDevice::Clone()
{
	CPpCfgDevice *p = new CPpCfgDevice();
	Copy(p);
	return p;
}

long CPpCfgDevice::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("Index"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 200);
	pListCtrl->InsertColumn(2, _T("TemplateFile"));
	pListCtrl->SetColumnWidth(2, 120);
	pListCtrl->InsertColumn(3, _T("DdvmFile"));
	pListCtrl->SetColumnWidth(3, 200);

	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPpCfgDevice::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strTemplateFile);
	pListCtrl->SetItemText(lItemIndex, 3, m_strDdvmFile);

	pListCtrl->SetItemData(lItemIndex, (DWORD)this);

	return 1;
}

BOOL CPpCfgDevice::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPpCfgDevice::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CClassProcotolProjectXmlRWKeys *pXmlKeys = (CClassProcotolProjectXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCmmConfigKey)
	{
		pNew = new CDeviceCmmConfig();
	}

	return pNew;
}

CExBaseObject* CPpCfgDevice::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == DMCLASSID_DEVICECMMCONFIG)
	{
		pNew = new CDeviceCmmConfig();
	}

	return pNew;
}

void CPpCfgDevice::AddDeviceCmmConfig(CDeviceCmmConfig *pCmmConfig)
{
	if (m_pDeviceCmmConfig == NULL)
	{
		m_pDeviceCmmConfig = (CDeviceCmmConfig*)pCmmConfig->Clone();
		AddNewChild(m_pDeviceCmmConfig);
	}
	else
	{
		m_pDeviceCmmConfig->InitBy(pCmmConfig);
	}

	m_listCmmCfg.RemoveAll();
	m_pDeviceCmmConfig->SelectCmmCfgChannel(m_listCmmCfg);
}

void CPpCfgDevice::SelectCmmCfgChannel(CExBaseList &listCmmCfgChannel)
{
	//更新自身通讯通道
	m_listCmmCfg.RemoveAll();
	m_pDeviceCmmConfig->SelectCmmCfgChannel(m_listCmmCfg);

	//初始化总的通讯通道信息表格
	POS pos = m_listCmmCfg.GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)m_listCmmCfg.GetNext(pos);

		if (listCmmCfgChannel.FindByClassID(p->GetClassID()) == NULL)
		{
			listCmmCfgChannel.AddTail(p);
		}
	}
}

