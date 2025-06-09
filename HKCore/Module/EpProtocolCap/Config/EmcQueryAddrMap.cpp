//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EmcQueryAddrMap.cpp  CEmcQueryAddrMap


#include "stdafx.h"
#include "EmcQueryAddrMap.h"
#include "MonitorQueryConfig.h"

CEmcQueryAddrMap::CEmcQueryAddrMap()
{
	//初始化属性

	//初始化成员变量
	m_strName = _T("地址映射对象");
}

CEmcQueryAddrMap::~CEmcQueryAddrMap()
{
}

long CEmcQueryAddrMap::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strSrcKey, oNode, m_strSrc);
	xml_GetAttibuteValue(pXmlKeys->m_strDestKey, oNode, m_strDest);

	m_strSrc.Trim();
	m_strDest.Trim();
	return 0;
}

long CEmcQueryAddrMap::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strSrcKey, oElement, m_strSrc);
	xml_SetAttributeValue(pXmlKeys->m_strDestKey, oElement, m_strDest);
	return 0;
}

long CEmcQueryAddrMap::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strSrc);
		BinarySerializeCalLen(oBinaryBuffer, m_strDest);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strSrc);
		BinarySerializeRead(oBinaryBuffer, m_strDest);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strSrc);
		BinarySerializeWrite(oBinaryBuffer, m_strDest);
	}
	return 0;
}

BOOL CEmcQueryAddrMap::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEmcQueryAddrMap *p = (CEmcQueryAddrMap*)pObj;

	if(m_strSrc != p->m_strSrc)
	{
		return FALSE;
	}

	if(m_strDest != p->m_strDest)
	{
		return FALSE;
	}

	return TRUE;
}

CBaseObject* CEmcQueryAddrMap::Clone()
{
	CEmcQueryAddrMap *p = new CEmcQueryAddrMap();
	Copy(p);
	return p;
}

BOOL CEmcQueryAddrMap::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEmcQueryAddrMap *p = (CEmcQueryAddrMap*)pDest;

	p->m_strSrc = m_strSrc;
	p->m_strDest = m_strDest;
	return TRUE;
}

long CEmcQueryAddrMap::InitListCtrlColumnsFunc(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 40);
	pListCtrl->InsertColumn(1, _T("Src"));
	pListCtrl->SetColumnWidth(1, 180);
	pListCtrl->InsertColumn(2, _T("Dest"));
	pListCtrl->SetColumnWidth(2,180);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CEmcQueryAddrMap::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CMonitorQueryConfig *pCapConfig = (CMonitorQueryConfig*)GetAncestor(ECCLASSID_CMONITORQUERYCONFIG);
// 	CEmcSerialsConfig *pEmcSerialsConfig = pCapConfig->m_pEmcSerialsConfig;
	CEmcNetsConfig *pEmcNetsConfig = pCapConfig->m_pEmcNetsConfig;

	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);

	if (m_strSrc == m_strDest)
	{
// 		CEmcSerialConfig *pSerial = (CEmcSerialConfig*)pEmcSerialsConfig->FindByPort(m_strSrc);
// 		if (pSerial == NULL)
// 		{
// 			strTemp = m_strSrc;
// 		}
// 		else
// 		{
// 			strTemp.Format(_T("%s(%s)"), pSerial->m_strName, m_strSrc);
// 		}
// 	
// 		pListCtrl->SetItemText(lItemIndex, 1, strTemp);
// 		pListCtrl->SetItemText(lItemIndex, 2, _T("---"));
// 
	}
// 	else
	{
		CEmcNetConfig *pNet = (CEmcNetConfig*)pEmcNetsConfig->FindByID(m_strSrc);
		if (pNet == NULL)
		{
			strTemp = m_strSrc;
		}
		else
		{
			strTemp.Format(_T("%s(%s)"), pNet->m_strName, m_strSrc);
		}
		pListCtrl->SetItemText(lItemIndex, 1, strTemp);

		pNet = (CEmcNetConfig*)pEmcNetsConfig->FindByID(m_strDest);
		if (pNet == NULL)
		{
			strTemp = m_strDest;
		}
		else
		{
			strTemp.Format(_T("%s(%s)"), pNet->m_strName, m_strDest);
		}
		pListCtrl->SetItemText(lItemIndex, 2, strTemp);
	}

	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

