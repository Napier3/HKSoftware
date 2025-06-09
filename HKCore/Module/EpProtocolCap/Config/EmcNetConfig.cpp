//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EmcNetConfig.cpp  CEmcNetConfig


#include "stdafx.h"
#include "EmcNetConfig.h"

CEmcNetConfig::CEmcNetConfig()
{
	//初始化属性
	m_nDir = 0;

	//初始化成员变量
	m_strName = _T("网络配置对象");
}

CEmcNetConfig::~CEmcNetConfig()
{
}

long CEmcNetConfig::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strProtocolKey, oNode, m_strProtocol);
	xml_GetAttibuteValue(pXmlKeys->m_strDirKey, oNode, m_nDir);
	xml_GetAttibuteValue(pXmlKeys->m_strDvmFileKey, oNode, m_strDvmFile);

	return 0;
}

long CEmcNetConfig::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strProtocolKey, oElement, m_strProtocol);
	xml_SetAttributeValue(pXmlKeys->m_strDirKey, oElement, m_nDir);
	xml_SetAttributeValue(pXmlKeys->m_strDvmFileKey, oElement, m_strDvmFile);

	return 0;
}

long CEmcNetConfig::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strProtocol);
		BinarySerializeCalLen(oBinaryBuffer, m_nDir);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strProtocol);
		BinarySerializeRead(oBinaryBuffer, m_nDir);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strProtocol);
		BinarySerializeWrite(oBinaryBuffer, m_nDir);
	}
	return 0;
}

void CEmcNetConfig::InitAfterRead()
{
}

BOOL CEmcNetConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEmcNetConfig *p = (CEmcNetConfig*)pObj;
	
	if(m_strProtocol != p->m_strProtocol)
	{
		return FALSE;
	}
	if(m_nDir != p->m_nDir)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEmcNetConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CEmcNetConfig *p = (CEmcNetConfig*)pDest;
	p->m_strProtocol = m_strProtocol;
	p->m_nDir = m_nDir;
	p->m_strDvmFile = m_strDvmFile;

	return TRUE;
}

CBaseObject* CEmcNetConfig::Clone()
{
	CEmcNetConfig *p = new CEmcNetConfig();
	Copy(p);
	return p;
}

long CEmcNetConfig::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
	pListCtrl->SetItemText(lItemIndex, 3, m_strProtocol);
	pListCtrl->SetItemText(lItemIndex, 4, Ep_GetProtocolDir(m_nDir));
	pListCtrl->SetItemText(lItemIndex, 5, m_strDvmFile);

	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

long CEmcNetConfig::InitListCtrlColumnsFunc(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 40);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 160);
	pListCtrl->InsertColumn(2, _T("ID"));
	pListCtrl->SetColumnWidth(2, 120);
	pListCtrl->InsertColumn(3, _T("规约"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->InsertColumn(4, _T("方向"));
	pListCtrl->SetColumnWidth(4, 80);
	pListCtrl->InsertColumn(5, _T("点表"));
	pListCtrl->SetColumnWidth(5, 100);

	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

