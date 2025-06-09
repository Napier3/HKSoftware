// XrioScript.cpp : 实现文件
//

#include "stdafx.h"
#include "XrioScript.h"


// CXrioScript

CXrioScript::CXrioScript()
{
//	m_strName = _T("Script节点");
}

CXrioScript::~CXrioScript()
{
}

long CXrioScript::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
	xml_GetElementText(pXmlKeys->m_strNameKey, oNode, m_strName);
    xml_GetCDATA(oNode,m_strCDATA);

	return 0;
}

long CXrioScript::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
	xml_SetElementText(pXmlKeys->m_strNameKey, oXMLDoc, oElement, m_strName);
    xml_SetCDATA(oXMLDoc,oElement,m_strCDATA);
	return 0;
}

long CXrioScript::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		
	}

	return 0;
}

BOOL CXrioScript::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXrioScript *p = (CXrioScript*)pObj;

	return TRUE;
}

BOOL CXrioScript::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXrioScript *p = (CXrioScript*)pDest;

	return TRUE;
}

CBaseObject* CXrioScript::Clone()
{
	CXrioScript *p = new CXrioScript();
	Copy(p);
	return p;
}

BOOL CXrioScript::CanPaste(UINT nClassID)
{
    if (nClassID == XRIOCLASSID_Script
	)
	{
		return TRUE;
	}

	return FALSE;
}


void CXrioScript::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
	m_dwItemData = (DWORD)pTreeCtrl->InsertItem(_T("CUSTOM"), 0, 0);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}

BOOL CXrioScript::ReadXRIOFileCustom(const CString& strXRIOFilePath,const long &nXmlRWType)
{
//	if (!IsFileExist(strXRIOFilePath))
//	{
//		return FALSE;
//	}

//	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(nXmlRWType);

//	try
//	{
//		if ( !xml_OpenFile(pRWDoc, strXRIOFilePath) )//调用XMLInterface.h中的全局函数，加载资源，入口返回给oDoc；
//		{
//			delete pRWDoc;
//			return FALSE;
//		}
//	}
//	catch (...)
//	{
//		delete pRWDoc;
//		return FALSE;
//	}

//	CXmlRWNodeBase *pDocRoot = pRWDoc->GetDocNode();

//	pDocRoot = pDocRoot->GetChildNode(CXrioCfgMngrXmlRWKeys::XrioKey());

//	if ((pDocRoot == NULL)||(!pDocRoot->IsValid()))
//{
//		delete pRWDoc;
//		return FALSE;
//	}

//	pDocRoot = pDocRoot->GetChildNode(CXrioCfgMngrXmlRWKeys::CustomKey());

//	if ((pDocRoot == NULL)||(!pDocRoot->IsValid()))
//	{
//		delete pRWDoc;
//		return FALSE;
//	}

//	XmlRead(*pDocRoot, CXrioCfgMngrXmlRWKeys::g_pXmlKeys);

//	delete pRWDoc;
    return TRUE;
//	//return CExBaseObject::OpenXmlFile(strXRIOFilePath, CXrioCfgMngrXmlRWKeys::CustomKey(), CXrioCfgMngrXmlRWKeys::g_pXmlKeys);
}

BOOL CXrioScript::WriteXRIOFileCustom(const CString& strXRIOFilePath)
{
    return TRUE;
//	return CExBaseObject::SaveXmlFile(strXRIOFilePath, CXrioCfgMngrXmlRWKeys::g_pXmlKeys);
}


