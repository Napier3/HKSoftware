//////////////////////////////////////////////////////////////////////////

#ifndef _XML_RW_INTERFACE_H__
#define _XML_RW_INTERFACE_H__

#include "XmlRWBase.h"


inline BOOL xml_OpenFile(CXmlRWDocBase *pDoc, const CString &strFile)
{
	ASSERT(pDoc);
	return pDoc->xml_OpenFile(strFile);
}

inline BOOL xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWElementBase &oElement, __int64 &n64Val)
{
	//CString strAttrVal;
	
	BOOL bRet = oElement.xml_GetAttibuteValue(strAttrName,n64Val);

// 	if (bRet)
// 	{
// 		n64Val = CString_To_i64(strAttrVal);
// 	}
// 	else
// 	{
// 		n64Val = 0;
// 	}
	
	return bRet;
}

inline BOOL xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWElementBase &oElement, CString &strAttrVal)
{
	return oElement.xml_GetAttibuteValue(strAttrName,strAttrVal);
}

inline BOOL xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWElementBase &oElement, wchar_t *strAttrVal)
{
	return oElement.xml_GetAttibuteValue(strAttrName,strAttrVal);
}

inline BOOL xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWElementBase &oElement, long &nAttrVal)
{
	return oElement.xml_GetAttibuteValue(strAttrName,nAttrVal);
}

inline BOOL xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWElementBase &oElement, DWORD &dwAttrVal)
{
	return oElement.xml_GetAttibuteValue(strAttrName,dwAttrVal);
}

inline BOOL xml_GetAttibuteValue_Color(const BSTR strAttrName, CXmlRWElementBase &oElement, COLORREF &crAttrVal)
{
	return oElement.xml_GetAttibuteValue_Color(strAttrName,crAttrVal);
}

inline BOOL xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWElementBase &oElement, double &dAttrVal)
{
	return oElement.xml_GetAttibuteValue(strAttrName,dAttrVal);
}

inline BOOL xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWElementBase &oElement, short &unAttrVal)
{
	return oElement.xml_GetAttibuteValue(strAttrName,unAttrVal);
}

inline BOOL xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWElementBase &oElement, float &fAttrVal)
{
	return oElement.xml_GetAttibuteValue(strAttrName,fAttrVal);
}

#ifndef _PSX_IDE_QT_
inline BOOL xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWElementBase &oElement, _variant_t &vValue)
{
	return oElement.xml_GetAttibuteValue(strAttrName,vValue);
}

inline BOOL xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWElementBase &oElement, SYSTEMTIME &tmSys)
{
	return oElement.xml_GetAttibuteValue(strAttrName,tmSys);
}
#endif

inline BOOL xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, __int64 &n64Val)
{
	//CString strAttrVal;

	BOOL bRet = oNode.xml_GetAttibuteValue(strAttrName,n64Val);

// 	if (bRet)
// 	{
// 		n64Val = CString_To_i64(strAttrVal);
// 	}
// 	else
// 	{
// 		n64Val = 0;
// 	}

	return bRet;
}

inline BOOL xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
{
	return oNode.xml_GetAttibuteValue(strAttrName,strAttrVal);
}

inline BOOL xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, long &nAttrVal)
{
	return oNode.xml_GetAttibuteValue(strAttrName,nAttrVal);
}

inline BOOL xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, DWORD &nAttrVal)
{
	return oNode.xml_GetAttibuteValue(strAttrName,nAttrVal);
}

inline BOOL xml_GetAttibuteValue_Color(const BSTR strAttrName, CXmlRWNodeBase &oNode, DWORD &nAttrVal)
{
	return oNode.xml_GetAttibuteValue_Color(strAttrName,nAttrVal);
}

inline BOOL xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, double &dAttrVal)
{
	return oNode.xml_GetAttibuteValue(strAttrName,dAttrVal);
}

inline BOOL xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, short &unAttrVal)
{
	return oNode.xml_GetAttibuteValue(strAttrName,unAttrVal);
}

inline BOOL xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, float &fAttrVal)
{
	return oNode.xml_GetAttibuteValue(strAttrName,fAttrVal);
}

//yzj 2021-12-13
inline long xml_GetAttibuteType(const BSTR strAttrName, CXmlRWNodeBase &oNode)
{
	return oNode.xml_GetAttibuteType(strAttrName);
}

#ifndef _PSX_IDE_QT_
inline BOOL xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, _variant_t &vValue)
{
	return oNode.xml_GetAttibuteValue(strAttrName,vValue);
}

inline BOOL xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, SYSTEMTIME &tmSys)
{
	return oNode.xml_GetAttibuteValue(strAttrName,tmSys);
}
#endif

inline BOOL xml_SetAttributeValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, __int64 n64Val)
{
	CString strAttrVal;
	strAttrVal.Format(_T("%lld"), n64Val);
	return oNode.xml_SetAttributeValue(strAttrName,strAttrVal);
}

inline BOOL xml_SetAttributeValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, const CString &strAttrVal)
{
	return oNode.xml_SetAttributeValue(strAttrName,strAttrVal);
}

inline BOOL xml_SetAttributeValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, const wchar_t *strAttrVal)
{
	return oNode.xml_SetAttributeValue(strAttrName,strAttrVal);
}

inline BOOL xml_SetAttributeValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, const char *strAttrVal)
{
	wchar_t *pwszVal = NULL;
	str_char_to_wchar(&pwszVal, strAttrVal);
	BOOL bRet = oNode.xml_SetAttributeValue(strAttrName,pwszVal);
	delete pwszVal;

	return bRet;
}

inline BOOL xml_SetAttributeValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, long &nAttrVal)
{
	return oNode.xml_SetAttributeValue(strAttrName,nAttrVal);
}

inline BOOL xml_SetAttributeValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, DWORD &dwAttrVal)
{
	return oNode.xml_SetAttributeValue(strAttrName,dwAttrVal);
}

inline BOOL xml_SetAttributeValue_Color(const BSTR strAttrName, CXmlRWNodeBase &oNode, COLORREF &crAttrVal)
{
	return oNode.xml_SetAttributeValue_Color(strAttrName,crAttrVal);
}

inline BOOL xml_SetAttributeValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, double &dAttrVal)
{
	return oNode.xml_SetAttributeValue(strAttrName,dAttrVal);
}

inline BOOL xml_SetAttributeValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, short &unAttrVal)
{
	return oNode.xml_SetAttributeValue(strAttrName,unAttrVal);
}

inline BOOL xml_SetAttributeValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, float &fAttrVal)
{
	return oNode.xml_SetAttributeValue(strAttrName,fAttrVal);
}

#ifndef _PSX_IDE_QT_
inline BOOL xml_SetAttributeValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, VARIANT &vValue)
{
	return oNode.xml_SetAttributeValue(strAttrName,vValue);
}

inline BOOL xml_SetAttributeValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, const SYSTEMTIME &tmSys)
{
	return oNode.xml_SetAttributeValue(strAttrName,tmSys);
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline BOOL xml_SetAttributeValue(const BSTR strAttrName, CXmlRWElementBase &oElement, __int64 n64Val)
{
// 	CString strAttrVal;
// 	strAttrVal.Format(_T("%lld"), n64Val);
	return oElement.xml_SetAttributeValue(strAttrName,n64Val);
}

inline BOOL xml_SetAttributeValue(const BSTR strAttrName, CXmlRWElementBase &oElement, const CString &strAttrVal)
{
	return oElement.xml_SetAttributeValue(strAttrName,strAttrVal);
}

inline BOOL xml_SetAttributeValue(const BSTR strAttrName, CXmlRWElementBase &oElement, const wchar_t *strAttrVal)
{
	return oElement.xml_SetAttributeValue(strAttrName,strAttrVal);
}


inline BOOL xml_SetAttributeValue(const BSTR strAttrName, CXmlRWElementBase &oElement, const char *strAttrVal)
{
	//ASCII编码格式下，char * 是中文时，转成wchar*会乱码，此处改为CString，shaolei，20200423
// 	wchar_t *pwszVal = NULL;
// 	str_char_to_wchar(&pwszVal, strAttrVal);
	CString strVal(strAttrVal);
	BOOL bRet = oElement.xml_SetAttributeValue(strAttrName,strVal/*pwszVal*/);
//	delete pwszVal;

	return bRet;
}

inline BOOL xml_SetAttributeValue(const BSTR strAttrName, CXmlRWElementBase &oElement, long &nAttrVal)
{
	return oElement.xml_SetAttributeValue(strAttrName,nAttrVal);
}

inline BOOL xml_SetAttributeValue(const BSTR strAttrName, CXmlRWElementBase &oElement, DWORD &dwAttrVal)
{
	return oElement.xml_SetAttributeValue(strAttrName,dwAttrVal);
}

inline BOOL xml_SetAttributeValue_Color(const BSTR strAttrName, CXmlRWElementBase &oElement, COLORREF &crAttrVal)
{
	return oElement.xml_SetAttributeValue_Color(strAttrName,crAttrVal);
}

inline BOOL xml_SetAttributeValue(const BSTR strAttrName, CXmlRWElementBase &oElement, double &dAttrVal)
{
	return oElement.xml_SetAttributeValue(strAttrName,dAttrVal);
}

inline BOOL xml_SetAttributeValue(const BSTR strAttrName,CXmlRWElementBase &oElement, short &unAttrVal)
{
	return oElement.xml_SetAttributeValue(strAttrName,unAttrVal);
}

inline BOOL xml_SetAttributeValue(const BSTR strAttrName, CXmlRWElementBase &oElement, float &fAttrVal)
{
	return oElement.xml_SetAttributeValue(strAttrName,fAttrVal);
}

#ifndef _PSX_IDE_QT_
inline BOOL xml_SetAttributeValue(const BSTR strAttrName,CXmlRWElementBase &oElement, VARIANT &vValue)
{
	return oElement.xml_SetAttributeValue(strAttrName,vValue);
}

inline BOOL xml_SetAttributeValue(const BSTR strAttrName, CXmlRWElementBase &oElement, const SYSTEMTIME &tmSys)
{
	return oElement.xml_SetAttributeValue(strAttrName,tmSys);
}
#endif

//////////////////////////////////////////////////////////////////////////
//
inline BOOL xml_GetElementText(const BSTR strAttrName, CXmlRWElementBase &oElement, CString &strAttrVal)
{
	return oElement.xml_GetElementText(strAttrName,strAttrVal);
}

inline BOOL xml_GetElementText(const BSTR strAttrName, CXmlRWElementBase &oElement, long &nAttrVal)
{
	return oElement.xml_GetElementText(strAttrName,nAttrVal);
}

inline BOOL xml_GetElementText(const BSTR strAttrName, CXmlRWElementBase &oElement, DWORD &dwAttrVal)
{
	return oElement.xml_GetElementText(strAttrName,dwAttrVal);
}

inline BOOL xml_GetElementText_Color(const BSTR strAttrName, CXmlRWElementBase &oElement, COLORREF &crAttrVal)
{
	return oElement.xml_GetElementText_Color(strAttrName,crAttrVal);
}

inline BOOL xml_GetElementText(const BSTR strAttrName, CXmlRWElementBase &oElement, double &dAttrVal)
{
	return oElement.xml_GetElementText(strAttrName,dAttrVal);
}

inline BOOL xml_GetElementText(const BSTR strAttrName, CXmlRWElementBase &oElement, short &unAttrVal)
{
	return oElement.xml_GetElementText(strAttrName,unAttrVal);
}

inline BOOL xml_GetElementText(const BSTR strAttrName, CXmlRWElementBase &oElement, float &fAttrVal)
{
	return oElement.xml_GetElementText(strAttrName,fAttrVal);
}

#ifndef _PSX_IDE_QT_
inline BOOL xml_GetElementText(const BSTR strAttrName, CXmlRWElementBase &oElement, _variant_t &vValue)
{
	return oElement.xml_GetElementText(strAttrName,vValue);
}

inline BOOL xml_GetElementText(const BSTR strAttrName, CXmlRWElementBase &oElement, SYSTEMTIME &tmSys)
{
	return oElement.xml_GetElementText(strAttrName,tmSys);
}
#endif


inline BOOL xml_GetElementText(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
{
	return oNode.xml_GetElementText(strAttrName,strAttrVal);
}

inline BOOL xml_GetElementText(const BSTR strAttrName, CXmlRWNodeBase &oNode, long &nAttrVal)
{
	return oNode.xml_GetElementText(strAttrName,nAttrVal);
}
inline BOOL xml_GetElementText(const BSTR strAttrName, CXmlRWNodeBase &oNode, DWORD &nAttrVal)
{
	return oNode.xml_GetElementText(strAttrName,nAttrVal);
}

inline BOOL xml_GetElement_Color(const BSTR strAttrName, CXmlRWNodeBase &oNode, DWORD &nAttrVal)
{
	return oNode.xml_GetElement_Color(strAttrName,nAttrVal);
}
inline BOOL xml_GetElementText(const BSTR strAttrName, CXmlRWNodeBase &oNode, double &dAttrVal)
{
	return oNode.xml_GetElementText(strAttrName,dAttrVal);
}

inline BOOL xml_GetElementText(const BSTR strAttrName, CXmlRWNodeBase &oNode, short &unAttrVal)
{
	return oNode.xml_GetElementText(strAttrName,unAttrVal);
}

inline BOOL xml_GetElementText(const BSTR strAttrName, CXmlRWNodeBase &oNode, float &fAttrVal)
{
	return oNode.xml_GetElementText(strAttrName,fAttrVal);
}

#ifndef _PSX_IDE_QT_
inline BOOL xml_GetElementText(const BSTR strAttrName, CXmlRWNodeBase &oNode, _variant_t &vValue)
{
	return oNode.xml_GetElementText(strAttrName,vValue);
}

inline BOOL xml_GetElementText(const BSTR strAttrName, CXmlRWNodeBase &oNode, SYSTEMTIME &tmSys)
{
	return oNode.xml_GetElementText(strAttrName,tmSys);
}
#endif

inline BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, const CString &strAttrVal)
{
	return oParent.xml_SetElementText(strAttrName,&oXMLDoc,strAttrVal);
}

inline BOOL xml_SetElementOwnText(const BSTR strAttrName, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, const CString &strAttrVal)
{
    return oParent.xml_SetElementOwnText(strAttrName,&oXMLDoc,strAttrVal);
}

inline BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, long &nAttrVal)
{
	return oParent.xml_SetElementText(strAttrName,&oXMLDoc,nAttrVal);
}

// inline BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWNodeBase oNode, DWORD &dwAttrVal)
// {
// 	return oNode.xml_SetElementText(strAttrName,dwAttrVal);
// }

inline BOOL xml_SetElementText_Color(const BSTR strAttrName, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, COLORREF &crAttrVal)
{
	return oParent.xml_SetElementText_Color(strAttrName,&oXMLDoc,crAttrVal);
}

inline BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, double &dAttrVal)
{
	return oParent.xml_SetElementText(strAttrName,&oXMLDoc,dAttrVal);
}

inline BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, short &unAttrVal)
{
	return oParent.xml_SetElementText(strAttrName,&oXMLDoc,unAttrVal);
}

inline BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, float &fAttrVal)
{
	return oParent.xml_SetElementText(strAttrName,&oXMLDoc,fAttrVal);
}

#ifndef _PSX_IDE_QT_
inline BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, VARIANT &vValue)
{
	return oParent.xml_SetElementText(strAttrName,&oXMLDoc,vValue);
}

inline BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oParent, const SYSTEMTIME &tmSys)
{
	return oParent.xml_SetElementText(strAttrName,&oXMLDoc,tmSys);
}
#endif

inline BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase &oXMLDoc, CXmlRWNodeBase &oParent, const CString &strAttrVal)
{
	return oParent.xml_SetElementText(strAttrName,&oXMLDoc,strAttrVal);
}

inline BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase &oXMLDoc, CXmlRWNodeBase &oParent, long &nAttrVal)
{
	return oParent.xml_SetElementText(strAttrName,&oXMLDoc,nAttrVal);
}

// inline BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWNodeBase oNode, DWORD &dwAttrVal)
// {
// 	return oNode.xml_SetElementText(strAttrName,dwAttrVal);
// }

inline BOOL xml_SetElementText_Color(const BSTR strAttrName, CXmlRWDocBase &oXMLDoc, CXmlRWNodeBase &oParent, COLORREF &crAttrVal)
{
	return oParent.xml_SetElementText_Color(strAttrName,&oXMLDoc,crAttrVal);
}

inline BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase &oXMLDoc, CXmlRWNodeBase &oParent, double &dAttrVal)
{
	return oParent.xml_SetElementText(strAttrName,&oXMLDoc,dAttrVal);
}

inline BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase &oXMLDoc, CXmlRWNodeBase &oParent, short &unAttrVal)
{
	return oParent.xml_SetElementText(strAttrName,&oXMLDoc,unAttrVal);
}

inline BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase &oXMLDoc, CXmlRWNodeBase &oParent, float &fAttrVal)
{
	return oParent.xml_SetElementText(strAttrName,&oXMLDoc,fAttrVal);
}

#ifndef _PSX_IDE_QT_
inline BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase &oXMLDoc, CXmlRWNodeBase &oParent, VARIANT &vValue)
{
	return oParent.xml_SetElementText(strAttrName,&oXMLDoc,vValue);
}

inline BOOL xml_SetElementText(const BSTR strAttrName, CXmlRWDocBase &oXMLDoc, CXmlRWNodeBase &oParent, const SYSTEMTIME &tmSys)
{
	return oParent.xml_SetElementText(strAttrName,&oXMLDoc,tmSys);
}
#endif

inline BOOL xml_GetCDATA(CXmlRWElementBase &oElement, CString &strText,const BSTR strAttrName = NULL)
{
	return oElement.xml_GetCDATA(strText,strAttrName);
}

inline BOOL xml_SetCDATA(CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oElement, const CString &strText,const BSTR strAttrName = NULL)
{
	return oElement.xml_SetCDATA(oXMLDoc,strText,strAttrName);
}


inline BOOL xml_GetCDATA(CXmlRWNodeBase &oElement, CString &strText,const BSTR strAttrName = NULL)
{
	return oElement.xml_GetCDATA(strText,strAttrName);
}

inline BOOL xml_SetCDATA(CXmlRWDocBase &oXMLDoc,CXmlRWNodeBase &oElement, const CString &strText,const BSTR strAttrName = NULL)
{
	return oElement.xml_SetCDATA(oXMLDoc,strText,strAttrName);
}

#endif
