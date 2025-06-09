// Language.h: interface for the CLanguage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LANGUAGE_H__00AE1227_3B8C_463B_B951_F0690B9314B5__INCLUDED_)
#define AFX_LANGUAGE_H__00AE1227_3B8C_463B_B951_F0690B9314B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\BaseClass\TLinkList.h"
#include "..\interface\XML2Interface.h"

#ifdef WIN32
#pragma warning (disable: 4514 4786)
#endif

#ifndef debug_trace
#define debug_trace(STR)  {}
#endif


class CLanguage  
{
private:

	//描述一个语言资源,包括ID和Translation
	class CItem
	{
	public:
		CItem();
		CItem(CItem *pSrc);
		CItem(const CString &strID, const CString &strTranslation);
		virtual ~CItem();

	public:
		CString m_strName;//m_strStringID;
		CString m_strTranslation;
		
		static const BSTR gs_strKeyStringID;
		static const BSTR gs_strKeyTranslation;
		static const BSTR gs_strKeyItem;

	public:
		BOOL ReadXml(const MSXML2::IXMLDOMElementPtr &oItem);
		BOOL WriteXml(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oParent);
	};
public:
	CLanguage();
	virtual ~CLanguage();

//attribute
public:
	CString m_strLanguage;
	static const char* gs_strKeyLanguage;

//operations
public:
	BOOL GetLanguageStringByID(const CString &strID, CString &strLanguageString);
	BOOL GetLanguageStringByID(LPCTSTR strID, CString &strLanguageString);
	CString GetLanguageStringByID(const CString &strID);
	BOOL RegisterString(const CString &strID, const CString &strString);
	BOOL RegisterString(char* strID, char* strString); 

#ifdef _LANGUAGE_DANAMIC
	BOOL ReadXmlEx(MSXML2::IXMLDOMElementPtr &oLanguage);
#else
	BOOL ReadXml(MSXML2::IXMLDOMElementPtr &oLanguage);
#endif
	BOOL ReadXmlFile(const CString &strFilePath);
	
#ifdef _DEBUG_LANGUAGE_MNGR
	void Append(CLanguage *pLanguage);
	BOOL Debug_WriteTempXmlFile(const CString &strFile);
#endif
	
private:
	CTLinkListEx<CItem> m_listChild;	
	
	CItem* FindByID(const CString &strID);
	CItem* FindByID(char* strID);
	BOOL AddString(const CString &strID, const CString &strString);	
};

#endif // !defined(AFX_LANGUAGE_H__00AE1227_3B8C_463B_B951_F0690B9314B5__INCLUDED_)
