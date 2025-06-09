//////////////////////////////////////////////////////////////////////////
//TinyxmlInterface.h
//XML组件的接口定义和扩展文件
#pragma once
#include "..\tinyXml\tinyxml.h"


inline BOOL xml_OpenFile(TiXmlDocument* oDoc, const CString &strFile )
{
	return oDoc->LoadFile(strFile);//读取指定位置的XML源;
}

// MSXML2::IXMLDOMNodePtr tinyxml_FindAttibute(const BSTR &strAttrName, MSXML2::IXMLDOMNamedNodeMapPtr oAttrs);
// MSXML2::IXMLDOMNodePtr tinyxml_FindAttibute(const BSTR &strAttrName, MSXML2::IXMLDOMNodePtr oNode);

//MSXML2 GetAttibuteValues 声明
inline void xml_GetRowAndColumn(TiXmlElement* oElement, CString &strPrivateMSG)
{
	ASSERT(oElement!=NULL);
	strPrivateMSG.Format(_T("行号=%d ,列号=%d") ,oElement->Row(),oElement->Column() );
}

inline BOOL xml_GetAttibuteValue(char* strAttrName, TiXmlElement* oElement, CString &strAttrVal)
{
	ASSERT(oElement!=NULL);
	strAttrVal = oElement->Attribute(strAttrName);
	return (strAttrVal != _T(""));
}

inline BOOL xml_GetAttibuteValue(char* strAttrName, TiXmlElement* oElement, long &nAttrVal)
{
	return (oElement->Attribute(strAttrName ,&nAttrVal ) != NULL);
}
inline BOOL xml_GetAttibuteValue(char* strAttrName, TiXmlElement* oElement, int &nAttrVal)
{
	return (oElement->Attribute(strAttrName ,&nAttrVal ) != NULL);
}
// BOOL xml_GetAttibuteValue(const BSTR &strAttrName, const MSXML2::IXMLDOMElementPtr &oElement, DWORD &dwAttrVal);
// BOOL xml_GetAttibuteValue_Color(const BSTR &strAttrName, const MSXML2::IXMLDOMElementPtr &oElement, COLORREF &crAttrVal);
inline BOOL xml_GetAttibuteValue(char* strAttrName, TiXmlElement* oElement, double &dAttrVal)
{
	return (oElement->Attribute(strAttrName, &dAttrVal) != NULL);
}
inline BOOL xml_GetAttibuteValue(char* strAttrName, TiXmlElement* oElement, short &unAttrVal)
{
	return (oElement->Attribute(strAttrName ,&unAttrVal ) != NULL);
}
inline BOOL xml_GetAttibuteValue(char* strAttrName, TiXmlElement* oElement, float &fAttrVal)
{
	return (oElement->Attribute(strAttrName ,&fAttrVal ) != NULL);
}

inline BOOL xml_GetAttibuteValue(char* strAttrName, TiXmlElement* oElement, DWORD &fAttrVal)
{
	return (oElement->Attribute(strAttrName ,&fAttrVal ) != NULL);
}

inline BOOL xml_GetElementText(char* strAttrName, TiXmlElement* oNode, CString &strAttrVal)
{
	const char *pValue = oNode->GetAttributeText(strAttrName );

	if (pValue)
	{
		strAttrVal = pValue;
		return TRUE;
	}
	return FALSE;
}

inline BOOL xml_GetElementText(char* strAttrName, TiXmlElement* oNode, long &nAttrVal)
{
	const char *pValue = oNode->GetAttributeText(strAttrName );

	if (pValue)
	{
		TIXML_SSCANF( pValue, "%ld", &nAttrVal );
		return TRUE;
	}
	return FALSE;
}

inline BOOL xml_GetElementText(char* strAttrName, TiXmlElement* oNode, int &nAttrVal)
{
	const char *pValue = oNode->GetAttributeText(strAttrName );

	if (pValue)
	{
		TIXML_SSCANF( pValue, "%d", &nAttrVal );
		return TRUE;
	}
	return FALSE;
}

inline BOOL xml_GetElementText(char* strAttrName, TiXmlElement* oNode, DWORD &dwAttrVal)
{
	const char *pValue = oNode->GetAttributeText(strAttrName );

	if (pValue)
	{
		TIXML_SSCANF( pValue, "%ld", &dwAttrVal );
		return TRUE;
	}
	return FALSE;
}

//BOOL xml_GetElementText_Color(char* strAttrName, TiXmlElement* oElement, COLORREF &crAttrVal);

inline BOOL xml_GetElementText(char* strAttrName, TiXmlElement* oNode, double &dAttrVal)
{
	const char *pValue = oNode->GetAttributeText(strAttrName );

	if (pValue)
	{
		TIXML_SSCANF( pValue, "%lf", &dAttrVal );
		return TRUE;
	}
	return FALSE;
}

inline BOOL xml_GetElementText(char* strAttrName, TiXmlElement* oNode, short &unAttrVal)
{
	const char *pValue = oNode->GetAttributeText(strAttrName );

	if (pValue)
	{
		TIXML_SSCANF( pValue, "%d", &unAttrVal );
		return TRUE;
	}
	return FALSE;
}

inline BOOL xml_GetElementText(char* strAttrName,TiXmlElement* oNode,float &fAttrVal)
{
	const char *pValue = oNode->GetAttributeText(strAttrName );

	if (pValue)
	{
		TIXML_SSCANF( pValue, "%f", &fAttrVal );
		return TRUE;
	}
	return FALSE;
}

// BOOL xml_GetElementText(char* strAttrName, TiXmlElement* oElement, _variant_t &vValue);
// BOOL xml_GetElementText(char* strAttrName, TiXmlElement* oElement, SYSTEMTIME &tmSys);

// BOOL xml_GetAttibuteValue(const BSTR &strAttrName, const MSXML2::IXMLDOMElementPtr &oElement, _variant_t &vValue);
// BOOL xml_GetAttibuteValue(const BSTR &strAttrName, const MSXML2::IXMLDOMElementPtr &oElement, SYSTEMTIME &tmSys);


// inline BOOL tinyxml_GetCDATA(const MSXML2::IXMLDOMNodePtr &oNode, CString &strText)
// {
// 	MSXML2::IXMLDOMCDATASectionPtr oCDTA =  oNode->GetfirstChild();
// 
// 	if (oCDTA != NULL)
// 	{
// 		strText = (char*)oCDTA->Getxml();
// 		long nLen = strText.GetLength();
// 		strText = strText.Mid(9, nLen-12);
// 	}
// 	else
// 	{
// 		strText = (char*)oNode->Gettext();
// 		strText.Trim();
// 	}
// 	
// 	return TRUE;
// }

//MSXML2 SetAttibuteValue 声明
inline BOOL xml_SetAttributeValue(char* strAttrName, TiXmlElement *oNode, const CString &strAttrVal)
{
	if (!strAttrVal.IsEmpty())
	{
	oNode->SetAttribute(strAttrName ,strAttrVal);
	}
	
	return FALSE;
}
inline BOOL xml_SetAttributeValue(char* strAttrName, TiXmlElement* oNode, long &nAttrVal)
{
	oNode->SetAttribute(strAttrName ,nAttrVal);	
	return FALSE;
}
// BOOL xml_SetAttributeValue(const BSTR &strAttrName, MSXML2::IXMLDOMNodePtr oNode, DWORD &dwAttrVal);
// BOOL xml_SetAttributeValue_Color(const BSTR &strAttrName, MSXML2::IXMLDOMNodePtr oNode, COLORREF &crAttrVal);
inline BOOL xml_SetAttributeValue(char* strAttrName, TiXmlElement* oNode, double &dAttrVal)
{
	oNode->SetAttribute(strAttrName ,dAttrVal);	
	return FALSE;
}
inline BOOL xml_SetAttributeValue(char* strAttrName, TiXmlElement* oNode, short &unAttrVal)
{
	oNode->SetAttribute(strAttrName ,unAttrVal);	
	return FALSE;
}
inline BOOL xml_SetAttributeValue(char* strAttrName, TiXmlElement* oNode, float &fAttrVal)
{
	oNode->SetAttribute(strAttrName ,fAttrVal);	
	return FALSE;
}

inline BOOL xml_SetAttributeValue(char* strAttrName, TiXmlElement* oNode, DWORD &fAttrVal)
{
	oNode->SetAttribute(strAttrName ,fAttrVal);	
	return FALSE;
}
/*BOOL tinyxml_SetCDATA(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, const CString &strText);*/
inline BOOL xml_SetElementText(char* strAttrName, TiXmlElement* oNode, const CString &strAttrVal)
{
	TiXmlElement *pValue = oNode->SetElementChild(strAttrName );

#ifdef UNICODE
	CT2CA pszConvertedAnsiString(strAttrVal); 
	pValue->SetTextChild(pszConvertedAnsiString);
#else
	pValue->SetTextChild(strAttrVal);
#endif

	return FALSE;
}

inline BOOL xml_SetElementText(char* strAttrName, TiXmlElement* oNode, long &nAttrVal)
{
 	TiXmlElement *pValue = oNode->SetElementChild(strAttrName );

	char buf [64];
#if defined(TIXML_SNPRINTF)		
	TIXML_SNPRINTF(buf, sizeof(buf), "%ld", nAttrVal);
#else
	sprintf (buf, "%ld", nAttrVal);
#endif

	pValue->SetTextChild(buf);

 	return FALSE;
}

inline BOOL xml_SetElementText(char* strAttrName, TiXmlElement* oNode, double &dAttrVal)
{
	TiXmlElement *pValue = oNode->SetElementChild(strAttrName );

	char buf [64];
#if defined(TIXML_SNPRINTF)		
	TIXML_SNPRINTF(buf, sizeof(buf), "%lf", dAttrVal);
#else
	sprintf (buf, "%lf", dAttrVal);
#endif

	pValue->SetTextChild(buf);

	return FALSE;
}

inline BOOL xml_SetElementText(char* strAttrName, TiXmlElement* oNode, short &unAttrVal)
{
	TiXmlElement *pValue = oNode->SetElementChild(strAttrName );

	char buf [64];
#if defined(TIXML_SNPRINTF)		
	TIXML_SNPRINTF(buf, sizeof(buf), "%d", unAttrVal);
#else
	sprintf (buf, "%d", unAttrVal);
#endif

	pValue->SetTextChild(buf);

	return FALSE;
}

inline BOOL xml_SetElementText(char* strAttrName, TiXmlElement* oNode, float &fAttrVal)
{
	TiXmlElement *pValue = oNode->SetElementChild(strAttrName );

	char buf [64];
#if defined(TIXML_SNPRINTF)		
	TIXML_SNPRINTF(buf, sizeof(buf), "%f", fAttrVal);
#else
	sprintf (buf, "%f", fAttrVal);
#endif

	pValue->SetTextChild(buf);

	return FALSE;
}

inline BOOL xml_SetElementText(char* strAttrName, TiXmlElement* oNode, DWORD &fAttrVal)
{
	TiXmlElement *pValue = oNode->SetElementChild(strAttrName );

	char buf [64];
#if defined(TIXML_SNPRINTF)		
	TIXML_SNPRINTF(buf, sizeof(buf), "%ld", fAttrVal);
#else
	sprintf (buf, "%ld", fAttrVal);
#endif

	pValue->SetTextChild(buf);

	return FALSE;
}

// BOOL tinyxml_SetElementText(const BSTR &strAttrName, const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oParent, long &nAttrVal);
// BOOL tinyxml_SetElementText(const BSTR &strAttrName, MSXML2::IXMLDOMNodePtr oNode, DWORD &dwAttrVal);
// BOOL tinyxml_SetElementText_Color(const BSTR &strAttrName, const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oParent, COLORREF &crAttrVal);
// BOOL tinyxml_SetElementText(const BSTR &strAttrName, const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oParente, double &dAttrVal);
// BOOL tinyxml_SetElementText(const BSTR &strAttrName, const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oParent, short &unAttrVal);
// BOOL tinyxml_SetElementText(const BSTR &strAttrName, const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oParent, float &fAttrVal);
// BOOL tinyxml_SetElementText(const BSTR &strAttrName, const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oParent, VARIANT &vValue);
// BOOL tinyxml_SetElementText(const BSTR &strAttrName, const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oParent, const SYSTEMTIME &tmSys);

