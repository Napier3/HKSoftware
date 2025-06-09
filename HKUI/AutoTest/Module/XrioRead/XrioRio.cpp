// XrioRio.cpp : 实现文件
//

#include "stdafx.h"
#include "XrioRio.h"
#include "XrioObjectCfg.h"

// CXrioRio

CXrioRio::CXrioRio()
{
    m_strName = _T("RIO节点");
    m_strType = _T("");
    m_strBlockType = _T("");
    m_strDescription = _T("");
}

CXrioRio::~CXrioRio()
{
}

long CXrioRio::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
    xml_GetAttibuteValue(pXmlKeys->m_strBlockTypeKey, oNode, m_strBlockType);
    xml_GetElementText(pXmlKeys->m_strNameKey, oNode, m_strName);
    xml_GetElementText(pXmlKeys->m_strDescriptionKey, oNode, m_strDescription);

	return 0;
}

long CXrioRio::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
    xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
    xml_SetAttributeValue(pXmlKeys->m_strBlockTypeKey, oElement, m_strBlockType);
	xml_SetElementText(pXmlKeys->m_strNameKey, oXMLDoc, oElement, m_strName);
    xml_SetElementText(pXmlKeys->m_strDescriptionKey, oXMLDoc, oElement, m_strDescription);

	return 0;
}

long CXrioRio::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
        BinarySerializeCalLen(oBinaryBuffer, m_strType);
        BinarySerializeCalLen(oBinaryBuffer, m_strBlockType);
        BinarySerializeCalLen(oBinaryBuffer, m_strDescription);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
        BinarySerializeRead(oBinaryBuffer, m_strType);
        BinarySerializeRead(oBinaryBuffer, m_strBlockType);
        BinarySerializeRead(oBinaryBuffer, m_strDescription);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
        BinarySerializeWrite(oBinaryBuffer, m_strType);
        BinarySerializeWrite(oBinaryBuffer, m_strBlockType);
        BinarySerializeWrite(oBinaryBuffer, m_strDescription);
	}

	return 0;
}

BOOL CXrioRio::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXrioRio *p = (CXrioRio*)pObj;

        if(m_strType != p->m_strType)
        {
            return FALSE;
        }
        if(m_strBlockType != p->m_strBlockType)
        {
            return FALSE;
        }
        if(m_strDescription != p->m_strDescription)
        {
            return FALSE;
        }

	return TRUE;
}

BOOL CXrioRio::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXrioRio *p = (CXrioRio*)pDest;

   p->m_strType = m_strType;
   p->m_strBlockType = m_strBlockType;
   p->m_strDescription = m_strDescription;

	return TRUE;
}

CBaseObject* CXrioRio::Clone()
{
	CXrioRio *p = new CXrioRio();
	Copy(p);
	return p;
}

BOOL CXrioRio::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_DEVICE ||
            nClassID == XRIOCLASSID_RIO ||
            nClassID == XRIOCLASSID_CBCONFIGURATION  ||
            nClassID == XRIOCLASSID_DISTANCE  ||
            nClassID == XRIOCLASSID_DIFFERENTIAL  ||
            nClassID == XRIOCLASSID_OVERCURRENT
	)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CXrioRio::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

    if (strClassID == pXmlKeys->m_strRioDeviceKey)
	{
        pNew = new CRioDevice();
	}
    if (strClassID == pXmlKeys->m_strRioCBKey)
    {
        pNew = new CRioCBConfig();
    }
    if (strClassID == pXmlKeys->m_strDistanceKey)
    {
        pNew = new CRioDistance();
    }
    if (strClassID == pXmlKeys->m_strDifferentialKey)
    {
        pNew = new CRioDifferential();
    }
    if (strClassID == pXmlKeys->m_strOverCurrentKey)
    {
        pNew = new CRioOverCurrent();
    }

	return pNew;
}

CExBaseObject* CXrioRio::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

    if (nClassID == XRIOCLASSID_DEVICE)
	{
        pNew = new CRioDevice();
	}
    if (nClassID == XRIOCLASSID_CBCONFIGURATION)
    {
        pNew = new CRioCBConfig();
    }
    if (nClassID == XRIOCLASSID_DISTANCE)
    {
        pNew = new CRioDistance();
    }
    if (nClassID == XRIOCLASSID_DIFFERENTIAL)
    {
        pNew = new CRioDifferential();
    }
	if (nClassID == XRIOCLASSID_DIFFERENTIAL)
	{
		pNew = new CRioOverCurrent();
	}

	return pNew;
}

void CXrioRio::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
	m_dwItemData = (DWORD)pTreeCtrl->InsertItem(_T("RIO"), 0, 0);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}

BOOL CXrioRio::ReadXRIOFileRio(const CString& strXRIOFilePath,const long &nXmlRWType)
{
	if (!IsFileExist(strXRIOFilePath))
	{
		return FALSE;
	}

	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(nXmlRWType);

	try
	{
		if ( !xml_OpenFile(pRWDoc, strXRIOFilePath) )//调用XMLInterface.h中的全局函数，加载资源，入口返回给oDoc；
		{
			delete pRWDoc;
			return FALSE;
		}
	}
	catch (...)
	{
		delete pRWDoc;
		return FALSE;
	}

	CXmlRWNodeBase *pDocRoot = pRWDoc->GetDocNode();

    pDocRoot = pDocRoot->GetChildNode(CXrioCfgMngrXmlRWKeys::RioKey());

	if ((pDocRoot == NULL)||(!pDocRoot->IsValid()))
    {
		delete pRWDoc;
		return FALSE;
	}

    pDocRoot = pDocRoot->GetChildNode(CXrioCfgMngrXmlRWKeys::DeviceKey());

	if ((pDocRoot == NULL)||(!pDocRoot->IsValid()))
	{
		delete pRWDoc;
		return FALSE;
	}

	XmlRead(*pDocRoot, CXrioCfgMngrXmlRWKeys::g_pXmlKeys);

	delete pRWDoc;
	return TRUE;
	//return CExBaseObject::OpenXmlFile(strXRIOFilePath, CXrioCfgMngrXmlRWKeys::CustomKey(), CXrioCfgMngrXmlRWKeys::g_pXmlKeys);
}

BOOL CXrioRio::WriteXRIOFileRio(const CString& strXRIOFilePath)
{
	return CExBaseObject::SaveXmlFile(strXRIOFilePath, CXrioCfgMngrXmlRWKeys::g_pXmlKeys);
}


