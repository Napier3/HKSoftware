//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DocFile.cpp  CDocFile


#include "stdafx.h"
#include "DocFile.h"

extern 	long g_nDocmp_DebugGroup;

CDocFile::CDocFile()
{
	//初始化属性

	//初始化成员变量
}

CDocFile::~CDocFile()
{
}

long CDocFile::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDocCmpXmlRWKeys *pXmlKeys = (CDocCmpXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	return 0;
}

long CDocFile::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDocCmpXmlRWKeys *pXmlKeys = (CDocCmpXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	return 0;
}

void CDocFile::InitAfterRead()
{
}

BOOL CDocFile::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CDocFile *p = (CDocFile*)pObj;

	if(m_strID != p->m_strID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDocFile::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDocFile *p = (CDocFile*)pDest;

	p->m_strID = m_strID;
	return TRUE;
}

CBaseObject* CDocFile::Clone()
{
	CDocFile *p = new CDocFile();
	Copy(p);
	return p;
}

//WriteXml
long CDocFile::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	if (! CDocCmpXmlRWKeys::IsSaveCmpMode())
	{
		return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
	}

	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID;


	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == DOCMPCLASSID_CDOCTEXT)
		{
			if ( ((CDocText*)pObj)->m_strCmp_Id.GetLength() == 0)
			{
				continue;
			}
		}
		else if (nClassID == DOCMPCLASSID_CDOCTABLE)
		{
			if ( ((CDocTable*)pObj)->m_strCmp_Id.GetLength() == 0)
			{
				continue;
			}
		}

		pObj->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
	}

	return 0;
}


CExBaseObject* CDocFile::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDocCmpXmlRWKeys *pXmlKeys = (CDocCmpXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDocTextKey)
	{
		pNew = new CDocText();
	}
	else if (strClassID == pXmlKeys->m_strCDocTableKey)
	{
		pNew = new CDocTable();
	}

	return pNew;
}

CExBaseObject* CDocFile::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DOCMPCLASSID_CDOCTEXT)
	{
		pNew = new CDocText();
	}
	else if (nClassID == DOCMPCLASSID_CDOCTABLE)
	{
		pNew = new CDocTable();
	}

	return pNew;
}

void CDocFile::Group(CDataGroup *pConfig)
{
	m_oDocGroupRoot.SetConfig(pConfig);
	doccmp_Group(this, pConfig, &m_oDocGroupRoot);
	m_oDocGroupRoot.AddHead(GetHead());

	if (g_nDocmp_DebugGroup != 1)
	{
		return;
	}

	CString strFile;
	strFile = m_strID + _T("g");

	m_oDocGroupRoot.SaveXmlFile(strFile, CDocCmpXmlRWKeys::g_pXmlKeys);
}

void CDocFile::GroupNone(CDataGroup *pConfig)
{
	doccmp_Group(this, pConfig, &m_oDocGroupRoot);

	CString strFile;
	strFile = m_strID + _T("g");

	m_oDocGroupRoot.SaveXmlFile(strFile, CDocCmpXmlRWKeys::g_pXmlKeys);
}

void CDocFile::Cmp(CDocFile *pSrcFile)
{
	m_oDocGroupRoot.Cmp(&pSrcFile->m_oDocGroupRoot);
	pSrcFile->m_oDocGroupRoot.SetCmpError();
}

void CDocFile::OpenDocDataFile(const CString &strFile)
{
	CString strPostfix;
	strPostfix = ParseFilePostfix(strFile);
	strPostfix.MakeLower();
	m_strID = strFile;

	if (strPostfix == _T("xml"))
	{
		OpenXmlFile(strFile, CDocCmpXmlRWKeys::g_pXmlKeys, _PUGI_XML_TYPE_);
	}
	else
	{
		OpenXmlFile(strFile, CDocCmpXmlRWKeys::g_pXmlKeys, _JSON_TYPE_);
	}
	
}

void CDocFile::InitTableTxtCmpID()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p=NULL, *pPrev = NULL;
	UINT nClassID;

	if (pos != NULL)
	{
		pPrev = GetNext(pos);
	}

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == DOCMPCLASSID_CDOCTABLE)
		{
			if (pPrev->GetClassID() == DOCMPCLASSID_CDOCTEXT)
			{
				((CDocTable*)p)->m_strTxt_Cmp_Id = ((CDocText*)pPrev)->m_strCmp_Id;
			}
		}

		pPrev = p;
	}
}

