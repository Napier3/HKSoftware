// Language.cpp: implementation of the CLanguage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Language.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const BSTR CLanguage::CItem::gs_strKeyStringID     = L"string";
const BSTR CLanguage::CItem::gs_strKeyTranslation  = L"translation";
const BSTR CLanguage::CItem::gs_strKeyItem         = L"item";

CLanguage::CItem::CItem()
{
}

CLanguage::CItem::CItem(CItem *pSrc)
{
	ASSERT (this != pSrc);

	m_strName = pSrc->m_strName;
	m_strTranslation = pSrc->m_strTranslation;	
}

CLanguage::CItem::CItem(const CString &strID, const CString &strTranslation)
{
	m_strName = strID;
	m_strTranslation = strTranslation;
}

CLanguage::CItem::~CItem()
{
}

BOOL CLanguage::CItem::ReadXml(const MSXML2::IXMLDOMElementPtr &oItem)
{
	return TRUE;
}

BOOL CLanguage::CItem::WriteXml(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oParent)
{
	MSXML2::IXMLDOMElementPtr oItem;

	oItem = oXMLDoc->createElement(_bstr_t(gs_strKeyItem));
	oItem->setAttribute(_bstr_t(gs_strKeyStringID), _bstr_t(m_strName));
	oItem->setAttribute(_bstr_t(gs_strKeyTranslation), _bstr_t(m_strTranslation));
	oParent->appendChild(oItem);
	
	return TRUE;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const char* CLanguage::gs_strKeyLanguage    = "language";

CLanguage::CLanguage()
{

}

CLanguage::~CLanguage()
{
	m_listChild.DeleteAll();
}

BOOL CLanguage::GetLanguageStringByID(const CString &strID, CString &strLanguageString)
{
	strLanguageString = GetLanguageStringByID(strID);

	return TRUE;
}

BOOL CLanguage::GetLanguageStringByID(LPCTSTR strID, CString &strLanguageString)
{
	strLanguageString = GetLanguageStringByID(strID);
	return TRUE;
}

CString CLanguage::GetLanguageStringByID(const CString &strID)
{
	CItem *pItem = NULL;
	pItem = FindByID(strID);
//	ASSERT(pItem != NULL);
	
	if (pItem == NULL)
	{
		return L"#err#";
	}
	else
	{
		return pItem->m_strTranslation;
	}
}

BOOL CLanguage::RegisterString(const CString &strID, const CString &strString)
{
	CItem *pItem = NULL;
	pItem = FindByID(strID);

	if (pItem != NULL && pItem->m_strTranslation == strString)
	{
		//ASSERT(FALSE);
		//在此输出错误信息
		return FALSE;
	}

	//lijq: 2009-9-14
/*
	pItem = new CItem(strID, strString);
	m_listChild.AddNode(pItem);
*/
	AddString(strID, strString);
	
	return TRUE;
}

BOOL CLanguage::RegisterString(char* strID, char* strString)
{
	return RegisterString(CString(strID), CString(strString));
}

/*
 *	因为语言资源文件保存了整个系统的语言文字，
 *  为了节约空间，只加载当前程序需要的语言文字资源
 */
#ifndef _LANGUAGE_DANAMIC
BOOL CLanguage::ReadXml(MSXML2::IXMLDOMElementPtr &oLanguage)
{
	MSXML2::IXMLDOMNodeListPtr oItems = NULL;
	oItems = oLanguage->GetchildNodes();
	long nCount = oItems->Getlength();
	long nIndex = 0;
	MSXML2::IXMLDOMNodePtr oItem = NULL;
	CItem *pItem = NULL;
	CString strID;
	MSXML2::IXMLDOMNodePtr oAttr;
	CString strTag;
	strTag = (char*)oLanguage->GettagName();
	strTag = (char*)oLanguage->GetnodeName();
	
	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		oItem = oItems->Getitem(nIndex);
		strTag = (char*)oItem->GetnodeName();

		oAttr = xml_FindAttibute(_bstr_t(CItem::gs_strKeyStringID), oItem);
		
		if (oAttr != NULL)
		{
			pItem = FindByID((char*)(_bstr_t(oAttr->nodeTypedValue)));

			if (pItem != NULL)
			{
				oAttr = xml_FindAttibute(CItem::gs_strKeyTranslation, oItem);

				if (oAttr != NULL)
				{
					pItem->m_strTranslation = (char*)(_bstr_t(oAttr->nodeTypedValue));
				}
			}
		}
	}
	
	return TRUE;
}
#endif

//lijq: 2009-9-14
/*
 *	加载全部的语言文字资源
*/
#ifdef _LANGUAGE_DANAMIC
BOOL CLanguage::ReadXmlEx(MSXML2::IXMLDOMElementPtr &oLanguage)
{
	MSXML2::IXMLDOMNodeListPtr oItems = NULL;
	oItems = oLanguage->GetchildNodes();
	long nCount = oItems->Getlength();
	long nIndex = 0;
	MSXML2::IXMLDOMNodePtr oItem = NULL;
	CItem *pItem = NULL;
	MSXML2::IXMLDOMNodePtr oAttr;
	CString strTag;
	CString strID, strTranslation;
	strTag = (char*)oLanguage->GettagName();
	strTag = (char*)oLanguage->GetnodeName();
	
	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		oItem = oItems->Getitem(nIndex);
		strTag = (char*)oItem->GetnodeName();

		oAttr = xml_FindAttibute(CItem::gs_strKeyStringID, oItem);
		
		if (oAttr != NULL)
		{
			strID = (char*)(_bstr_t(oAttr->nodeTypedValue));
			pItem = FindByID(strID);
			oAttr = xml_FindAttibute(CItem::gs_strKeyTranslation, oItem);

			if (pItem != NULL)
			{
				if (oAttr != NULL)
				{
					pItem->m_strTranslation = (char*)(_bstr_t(oAttr->nodeTypedValue));
				}
			}
			else
			{
					strTranslation = (char*)(_bstr_t(oAttr->nodeTypedValue));
					AddString(strID, strTranslation);
			}
		}
	}
	
	return TRUE;
}
#endif

BOOL CLanguage::ReadXmlFile(const CString &strFilePath)
{
	MSXML2::IXMLDOMDocumentPtr oDoc = NULL;
	HRESULT hr = oDoc.CreateInstance(__uuidof(MSXML2::DOMDocument));

	if(!SUCCEEDED(hr)) 
	{ 
		return FALSE;
	} 
	
	MSXML2::IXMLDOMElementPtr oLanguage = NULL;
	BSTR bstrFile = strFilePath.AllocSysString();
	BOOL bTrue = oDoc->load(bstrFile);
	::SysFreeString(bstrFile);

	if (!bTrue)
	{
		TRACE("\nRead language file failed......\n");
	}
	
	oLanguage = oDoc->selectSingleNode(_bstr_t(gs_strKeyLanguage));

	if (oLanguage == NULL)
	{
		return FALSE;
	}

#ifndef _LANGUAGE_DANAMIC
	ReadXml(oLanguage);
#else
	ReadXmlEx(oLanguage);
#endif

	return TRUE;
}

#ifdef _DEBUG_LANGUAGE_MNGR
void CLanguage::Append(CLanguage *pLanguage)
{
	POS pos = pLanguage->m_listChild.GetHeadPosition();
	CItem *pItem = NULL;
	CItem *pNew = NULL;

	while (pos != NULL)
	{
		pItem = pLanguage->m_listChild.GetNext(pos);

		if (FindByID(pItem->m_strName) == NULL)
		{
			pNew = new CItem(pItem);
			m_listChild.AddNode(pNew);
		}
		else
		{
		}
	}
}

BOOL CLanguage::Debug_WriteTempXmlFile(const CString &strFile)
{
	MSXML2::IXMLDOMDocumentPtr oDoc; 
	MSXML2::IXMLDOMElementPtr oRoot;

	try
	{
		//创建DOMDocument对象
		HRESULT hr = oDoc.CreateInstance(__uuidof(MSXML2::DOMDocument));
		
		if(!SUCCEEDED(hr)) 
		{ 
			return FALSE;
		} 
		
		//根节点的名称为language
		oDoc->raw_createElement((_bstr_t)(char*)gs_strKeyLanguage, &oRoot);
		oDoc->raw_appendChild(oRoot, NULL);
		
		POS pos = m_listChild.GetHeadPosition();
		CItem *pItem = NULL;
		
		while (pos != NULL)
		{
			pItem = m_listChild.GetNext(pos);
			pItem->WriteXml(oDoc, oRoot);
		}
		
		BSTR bstrFile = strFile.AllocSysString();
		oDoc->save(bstrFile);
		::SysFreeString(bstrFile);
	}
	catch (...)
	{
		return FALSE;
	}
	
	return TRUE;
}
#endif

CLanguage::CItem* CLanguage::FindByID(const CString &strID)
{
	CItem *pItem = m_listChild.FindByName(strID);
	return pItem;
}

CLanguage::CItem* CLanguage::FindByID(char* strID)
{
	CItem *pItem = m_listChild.FindByName((CString)strID);
	return pItem;
}

//lijq: 2009-9-14
BOOL CLanguage::AddString(const CString &strID, const CString &strString)
{
	CItem *pItem = NULL;
	
	pItem = new CItem(strID, strString);
	m_listChild.AddNode(pItem);
	
	return TRUE;
}
