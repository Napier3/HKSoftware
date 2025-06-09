// XrioCustom.cpp : 实现文件
//

#include "stdafx.h"
#include "XrioCustom.h"
#include "XrioObjectCfg.h"
#include "XrioCustomBlock.h"
#include "XrioCustomParameter.h"

// CXrioCustom

CXrioCustom::CXrioCustom()
{
	m_strName = _T("CUSTOM节点");
}

CXrioCustom::~CXrioCustom()
{
}

long CXrioCustom::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
	xml_GetElementText(pXmlKeys->m_strNameKey, oNode, m_strName);

	return 0;
}

long CXrioCustom::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;
	xml_SetElementText(pXmlKeys->m_strNameKey, oXMLDoc, oElement, m_strName);

	return 0;
}

long CXrioCustom::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CXrioCustom::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXrioCustom *p = (CXrioCustom*)pObj;

	return TRUE;
}

BOOL CXrioCustom::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXrioCustom *p = (CXrioCustom*)pDest;

	return TRUE;
}

CBaseObject* CXrioCustom::Clone()
{
	CXrioCustom *p = new CXrioCustom();
	Copy(p);
	return p;
}

BOOL CXrioCustom::CanPaste(UINT nClassID)
{
	if (nClassID == XRIOCLASSID_CUSTOMBLOCK
	)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CXrioCustom::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCustomBlockKey)
	{
		pNew = new CXrioCustomBlock();
	}

	return pNew;
}

CExBaseObject* CXrioCustom::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == XRIOCLASSID_CUSTOMBLOCK)
	{
		pNew = new CXrioCustomBlock();
	}

	return pNew;
}

void CXrioCustom::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
	m_dwItemData = (DWORD)pTreeCtrl->InsertItem(_T("CUSTOM"), 0, 0);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}

BOOL CXrioCustom::ReadXRIOFileCustom(const CString& strXRIOFilePath,const long &nXmlRWType)
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

	pDocRoot = pDocRoot->GetChildNode(CXrioCfgMngrXmlRWKeys::XrioKey());

	if ((pDocRoot == NULL)||(!pDocRoot->IsValid()))
{
		delete pRWDoc;
		return FALSE;
	}

	pDocRoot = pDocRoot->GetChildNode(CXrioCfgMngrXmlRWKeys::CustomKey());

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

BOOL CXrioCustom::WriteXRIOFileCustom(const CString& strXRIOFilePath)
{
	return CExBaseObject::SaveXmlFile(strXRIOFilePath, CXrioCfgMngrXmlRWKeys::g_pXmlKeys);
}

CExBaseObject *CXrioCustom::FindParaByFullPath(const CString &strMap)
{
	CXrioCustomParameter *pParameter = NULL;
	CExBaseObject *pCurObj = NULL;
	CString strParaID,strMapPath;
	long nIndex = strMap.Find('$');

	if (nIndex == -1)
	{
		strParaID = strMap;
		strMapPath = _T("");
	}
	else
	{
		strParaID = strMap.Left(nIndex);
		strMapPath = strMap.Mid(nIndex+1);
	}

	CExBaseObject *pFind = FindByID(strParaID);

	if (pFind == NULL)
	{
		return NULL;
	}

	if (pFind->GetClassID() == XRIOCLASSID_CUSTOMPARAMETER)
	{
		return pFind;
	}
	else if (pFind->GetClassID() == XRIOCLASSID_CUSTOMBLOCK)
	{
		CXrioCustomBlock *pCurBlock = (CXrioCustomBlock*)pFind;
		return pCurBlock->FindParaByFullPath(strMapPath);
	}
	else
		return NULL;
}

void xrio_GetAllChildParameters(CExBaseList &oParasList,CExBaseList &oParametersListRef)
{
	if ((oParasList.GetClassID() != XRIOCLASSID_CUSTOM)&&(oParasList.GetClassID() != XRIOCLASSID_CUSTOMBLOCK))
	{
		return;
	}

	CExBaseObject *pChildObj = NULL;
	CXrioCustomParameter *pParameter = NULL;
	POS pos = oParasList.GetHeadPosition();
	CString strTmp;

	while(pos)
	{
		pChildObj = oParasList.GetNext(pos);

		if (pChildObj->GetClassID() == XRIOCLASSID_CUSTOMPARAMETER)
		{
			pParameter = (CXrioCustomParameter*)pChildObj;
			strTmp = pParameter->m_strEnabled;
			strTmp.MakeLower();

			if (strTmp != _T("false"))
			{
				oParametersListRef.AddTail(pChildObj);
			}
		}

		xrio_GetAllChildParameters((CExBaseList&)*pChildObj,oParametersListRef);
	}
}


