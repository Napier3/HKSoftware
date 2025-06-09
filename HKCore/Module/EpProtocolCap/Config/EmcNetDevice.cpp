//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EmcNetDevice.cpp  CEmcNetDevice


#include "stdafx.h"
#include "EmcNetDevice.h"

CEmcNetDevice::CEmcNetDevice()
{
	//初始化属性
	m_nUDP = 1;
	m_nTCP = 0;
	m_nNetCardIndex = 0;
	m_nCapAllIP = 1;

	//初始化成员变量
	m_strName = _T("网卡监视对象");
}

CEmcNetDevice::~CEmcNetDevice()
{
}

long CEmcNetDevice::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strProtocolKey, oNode, m_strProtocol);
	xml_GetAttibuteValue(pXmlKeys->m_strUDPKey, oNode, m_nUDP);
	xml_GetAttibuteValue(pXmlKeys->m_strTCPKey, oNode, m_nTCP);
	xml_GetAttibuteValue(pXmlKeys->m_strOtherKey, oNode, m_nOther);

	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_nNetCardIndex);
	 
	return 0;
}

long CEmcNetDevice::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strProtocolKey, oElement, m_strProtocol);
	xml_SetAttributeValue(pXmlKeys->m_strUDPKey, oElement, m_nUDP);
	xml_SetAttributeValue(pXmlKeys->m_strTCPKey, oElement, m_nTCP);
	xml_SetAttributeValue(pXmlKeys->m_strOtherKey, oElement, m_nOther);

	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_nNetCardIndex);

	return 0;
}

long CEmcNetDevice::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strProtocol);
		BinarySerializeCalLen(oBinaryBuffer, m_nUDP);
		BinarySerializeCalLen(oBinaryBuffer, m_nTCP);
		BinarySerializeCalLen(oBinaryBuffer, m_nNetCardIndex);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strProtocol);
		BinarySerializeRead(oBinaryBuffer, m_nUDP);
		BinarySerializeRead(oBinaryBuffer, m_nTCP);
		BinarySerializeRead(oBinaryBuffer, m_nNetCardIndex);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strProtocol);
		BinarySerializeWrite(oBinaryBuffer, m_nUDP);
		BinarySerializeWrite(oBinaryBuffer, m_nTCP);
		BinarySerializeWrite(oBinaryBuffer, m_nNetCardIndex);
	}
	return 0;
}

void CEmcNetDevice::InitAfterRead()
{
}

BOOL CEmcNetDevice::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEmcNetDevice *p = (CEmcNetDevice*)pObj;

	if(m_strProtocol != p->m_strProtocol)
	{
		return FALSE;
	}

	if(m_nUDP != p->m_nUDP)
	{
		return FALSE;
	}

	if(m_nTCP != p->m_nTCP)
	{
		return FALSE;
	}

	if(m_nNetCardIndex != p->m_nNetCardIndex)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEmcNetDevice::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CEmcNetDevice *p = (CEmcNetDevice*)pDest;

	p->m_strProtocol = m_strProtocol;
	p->m_nUDP = m_nUDP;
	p->m_nTCP = m_nTCP;
	p->m_nOther = m_nOther;
	p->m_nNetCardIndex = m_nNetCardIndex;

	return TRUE;
}

CBaseObject* CEmcNetDevice::Clone()
{
	CEmcNetDevice *p = new CEmcNetDevice();
	Copy(p);
	return p;
}

long CEmcNetDevice::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);

	strTemp.Format(_T("%d"), m_nNetCardIndex);
	pListCtrl->SetItemText(lItemIndex, 2, strTemp);
	pListCtrl->SetItemText(lItemIndex, 3, m_strProtocol);
	strTemp.Format(_T("%d"), m_nUDP);
	pListCtrl->SetItemText(lItemIndex, 4, strTemp);
	strTemp.Format(_T("%d"), m_nTCP);
	pListCtrl->SetItemText(lItemIndex, 5, strTemp);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

long CEmcNetDevice::InitListCtrlColumnsFunc(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 40);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 100);
	pListCtrl->InsertColumn(2, _T("ID"));
	pListCtrl->SetColumnWidth(2, 70);
	pListCtrl->InsertColumn(3, _T("Protocol"));
	pListCtrl->SetColumnWidth(3, 70);
	pListCtrl->InsertColumn(4, _T("UDP"));
	pListCtrl->SetColumnWidth(4, 70);
	pListCtrl->InsertColumn(5, _T("TCP"));
	pListCtrl->SetColumnWidth(5, 70);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

