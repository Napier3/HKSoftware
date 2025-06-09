//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EmcSerialsConfig.cpp  CEmcSerialsConfig


#include "stdafx.h"
#include "EmcSerialsConfig.h"

CEmcSerialsConfig::CEmcSerialsConfig()
{
	//初始化属性
	m_strName = _T("串口端口管理");
	m_strID = _T("EmcSerialsConfig");

	//初始化成员变量
}

CEmcSerialsConfig::~CEmcSerialsConfig()
{
}

long CEmcSerialsConfig::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strProtocolKey, oNode, m_strProtocol);
	return 0;
}

long CEmcSerialsConfig::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strProtocolKey, oElement, m_strProtocol);
	return 0;
}

long CEmcSerialsConfig::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strProtocol);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strProtocol);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strProtocol);
	}
	return 0;
}

void CEmcSerialsConfig::InitAfterRead()
{
}

BOOL CEmcSerialsConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEmcSerialsConfig *p = (CEmcSerialsConfig*)pObj;

	if(m_strProtocol != p->m_strProtocol)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEmcSerialsConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEmcSerialsConfig *p = (CEmcSerialsConfig*)pDest;

	p->m_strProtocol = m_strProtocol;
	return TRUE;
}

CBaseObject* CEmcSerialsConfig::Clone()
{
	CEmcSerialsConfig *p = new CEmcSerialsConfig();
	Copy(p);
	return p;
}

BOOL CEmcSerialsConfig::CanPaste(UINT nClassID)
{
	if (nClassID == EMCCLASSID_CEMCSERIALCONFIG)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEmcSerialsConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEmcSerialConfigKey)
	{
		pNew = new CEmcSerialConfig();
	}

	return pNew;
}

CExBaseObject* CEmcSerialsConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EMCCLASSID_CEMCSERIALCONFIG)
	{
		pNew = new CEmcSerialConfig();
	}

	return pNew;
}
long CEmcSerialsConfig::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strProtocol);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

long CEmcSerialsConfig::InitListCtrlColumnsFunc(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 40);
	pListCtrl->InsertColumn(1, _T("Protocol"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

CEmcSerialConfig* CEmcSerialsConfig::FindByPort(const CString &strPort)
{
	return FindByPort(CString_To_long(strPort));
}

CEmcSerialConfig* CEmcSerialsConfig::FindByPort(UINT nPort)
{
	CEmcSerialConfig *pFind = NULL;
	CEmcSerialConfig *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CEmcSerialConfig *)GetNext(pos);

		if (p->m_nPort == nPort)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

