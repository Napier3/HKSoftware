//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EmcSerialConfig.cpp  CEmcSerialConfig


#include "stdafx.h"
#include "EmcSerialConfig.h"

CEmcSerialConfig::CEmcSerialConfig()
{
	//初始化属性
	m_nPort = 0;
	m_nBaudRate = 0;
	m_nByteSize = 0;
	m_nStopBits = 0;
	m_nParity = 0;
	m_nDir = 0;

	//初始化成员变量
	m_strName = _T("串口监视对象");
}

CEmcSerialConfig::~CEmcSerialConfig()
{
}

long CEmcSerialConfig::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strPortKey, oNode, m_nPort);
	xml_GetAttibuteValue(pXmlKeys->m_strBaudRateKey, oNode, m_nBaudRate);
	xml_GetAttibuteValue(pXmlKeys->m_strByteSizeKey, oNode, m_nByteSize);
	xml_GetAttibuteValue(pXmlKeys->m_strStopBitsKey, oNode, m_nStopBits);
	xml_GetAttibuteValue(pXmlKeys->m_strParityKey, oNode, m_nParity);
	xml_GetAttibuteValue(pXmlKeys->m_strProtocolKey, oNode, m_strProtocol);
	xml_GetAttibuteValue(pXmlKeys->m_strDirKey, oNode, m_nDir);

//	m_strProtocol = _T("101");
	return 0;
}

long CEmcSerialConfig::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMonitorCapConfigXmlRWKeys *pXmlKeys = (CMonitorCapConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strPortKey, oElement, m_nPort);
	xml_SetAttributeValue(pXmlKeys->m_strBaudRateKey, oElement, m_nBaudRate);
	xml_SetAttributeValue(pXmlKeys->m_strByteSizeKey, oElement, m_nByteSize);
	xml_SetAttributeValue(pXmlKeys->m_strStopBitsKey, oElement, m_nStopBits);
	xml_SetAttributeValue(pXmlKeys->m_strParityKey, oElement, m_nParity);
	xml_SetAttributeValue(pXmlKeys->m_strProtocolKey, oElement, m_strProtocol);
	xml_SetAttributeValue(pXmlKeys->m_strDirKey, oElement, m_nDir);
	return 0;
}

long CEmcSerialConfig::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_nPort);
		BinarySerializeCalLen(oBinaryBuffer, m_nBaudRate);
		BinarySerializeCalLen(oBinaryBuffer, m_nByteSize);
		BinarySerializeCalLen(oBinaryBuffer, m_nStopBits);
		BinarySerializeCalLen(oBinaryBuffer, m_nParity);
		BinarySerializeCalLen(oBinaryBuffer, m_strProtocol);
		BinarySerializeCalLen(oBinaryBuffer, m_nDir);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_nPort);
		BinarySerializeRead(oBinaryBuffer, m_nBaudRate);
		BinarySerializeRead(oBinaryBuffer, m_nByteSize);
		BinarySerializeRead(oBinaryBuffer, m_nStopBits);
		BinarySerializeRead(oBinaryBuffer, m_nParity);
		BinarySerializeRead(oBinaryBuffer, m_strProtocol);
		BinarySerializeRead(oBinaryBuffer, m_nDir);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_nPort);
		BinarySerializeWrite(oBinaryBuffer, m_nBaudRate);
		BinarySerializeWrite(oBinaryBuffer, m_nByteSize);
		BinarySerializeWrite(oBinaryBuffer, m_nStopBits);
		BinarySerializeWrite(oBinaryBuffer, m_nParity);
		BinarySerializeWrite(oBinaryBuffer, m_strProtocol);
		BinarySerializeWrite(oBinaryBuffer, m_nDir);
	}
	return 0;
}

void CEmcSerialConfig::InitAfterRead()
{
}

BOOL CEmcSerialConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEmcSerialConfig *p = (CEmcSerialConfig*)pObj;

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_nPort != p->m_nPort)
	{
		return FALSE;
	}

	if(m_nBaudRate != p->m_nBaudRate)
	{
		return FALSE;
	}

	if(m_nByteSize != p->m_nByteSize)
	{
		return FALSE;
	}

	if(m_nStopBits != p->m_nStopBits)
	{
		return FALSE;
	}

	if(m_nParity != p->m_nParity)
	{
		return FALSE;
	}

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

BOOL CEmcSerialConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEmcSerialConfig *p = (CEmcSerialConfig*)pDest;

	p->m_strName = m_strName;
	p->m_nPort = m_nPort;
	p->m_nBaudRate = m_nBaudRate;
	p->m_nByteSize = m_nByteSize;
	p->m_nStopBits = m_nStopBits;
	p->m_nParity = m_nParity;
	p->m_strProtocol = m_strProtocol;
	p->m_nDir = m_nDir;

	return TRUE;
}

CBaseObject* CEmcSerialConfig::Clone()
{
	CEmcSerialConfig *p = new CEmcSerialConfig();
	Copy(p);
	return p;
}

long CEmcSerialConfig::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	strTemp.Format(_T("%d"), m_nPort);
	pListCtrl->SetItemText(lItemIndex, 2, strTemp);
	strTemp.Format(_T("%d"), m_nBaudRate);
	pListCtrl->SetItemText(lItemIndex, 3, strTemp);
	strTemp.Format(_T("%d"), m_nByteSize);
	pListCtrl->SetItemText(lItemIndex, 4, strTemp);
	strTemp.Format(_T("%d"), m_nStopBits);
	pListCtrl->SetItemText(lItemIndex, 5, strTemp);
	strTemp.Format(_T("%d"), m_nParity);
	pListCtrl->SetItemText(lItemIndex, 6, strTemp);
	pListCtrl->SetItemText(lItemIndex, 7, m_strProtocol);
	pListCtrl->SetItemText(lItemIndex, 8, Ep_GetProtocolDir(m_nDir));
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);

	return 0;
}

long CEmcSerialConfig::InitListCtrlColumnsFunc(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 40);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 160);
	pListCtrl->InsertColumn(2, _T("Port"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("BaudRate"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->InsertColumn(4, _T("ByteSize"));
	pListCtrl->SetColumnWidth(4, 80);
	pListCtrl->InsertColumn(5, _T("StopBits"));
	pListCtrl->SetColumnWidth(5, 80);
	pListCtrl->InsertColumn(6, _T("Parity"));
	pListCtrl->SetColumnWidth(6, 80);
	pListCtrl->InsertColumn(7, _T("Protocol"));
	pListCtrl->SetColumnWidth(7, 80);
	pListCtrl->InsertColumn(8, _T("Dir"));
	pListCtrl->SetColumnWidth(8, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

