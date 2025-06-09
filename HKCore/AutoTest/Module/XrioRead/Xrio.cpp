// XrioCustom.cpp : 实现文件
//

#include "stdafx.h"
#include "Xrio.h"


// CXrio

CXrio::CXrio()
{
	m_strName = _T("XRIO节点");
}

CXrio::~CXrio()
{
}

long CXrio::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{

	return 0;
}

long CXrio::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	return 0;
}

long CXrio::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

BOOL CXrio::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXrio *p = (CXrio*)pObj;

	return TRUE;
}

BOOL CXrio::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXrio *p = (CXrio*)pDest;

	return TRUE;
}

CBaseObject* CXrio::Clone()
{
	CXrio *p = new CXrio();
	Copy(p);
	return p;
}

BOOL CXrio::CanPaste(UINT nClassID)
{
	if (nClassID == XRIOCLASSID_CUSTOM
	)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CXrio::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXrioCfgMngrXmlRWKeys *pXmlKeys = (CXrioCfgMngrXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCustomKey)
	{
		pNew = new CXrioCustom();
	}

	return pNew;
}

CExBaseObject* CXrio::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == XRIOCLASSID_CUSTOM)
	{
		pNew = new CXrioCustom();
	}

	return pNew;
}

void CXrio::InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam)
{
	m_dwItemData = (DWORD)pTreeCtrl->InsertItem(_T("XRIO"), 0, 0);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);
}

BOOL CXrio::ReadXRIOFile(const CString& strXRIOFilePath)
{
	return CExBaseObject::OpenXmlFile(strXRIOFilePath, CXrioCfgMngrXmlRWKeys::XrioKey(), CXrioCfgMngrXmlRWKeys::g_pXmlKeys);
}

BOOL CXrio::WriteXRIOFile(const CString& strXRIOFilePath)
{
	return CExBaseObject::SaveXmlFile(strXRIOFilePath, CXrioCfgMngrXmlRWKeys::g_pXmlKeys);
}

CXrioCustom* CXrio::GetXrioCustom()
{
	CExBaseObject *pChildObj = NULL;
	CXrioCustom *pXrioCustom = NULL;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pChildObj = GetNext(pos);

		if (pChildObj->GetClassID() == XRIOCLASSID_CUSTOM)
		{
			pXrioCustom = (CXrioCustom*)pChildObj;
			break;
		}
	}

	return pXrioCustom;
}