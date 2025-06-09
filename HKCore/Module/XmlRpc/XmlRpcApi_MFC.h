#ifndef _XmlRpcApi_MFC_H__
#define _XmlRpcApi_MFC_H__

#include"XmlRpcServerMethod.h"
#include"XmlRpcValue.h"
#include"XmlRpcServer.h"
#include "../DataMngr/DvmDataset.h"

using namespace XmlRpc;

inline void XmlRpcValue_To_String(XmlRpcValue &oValue, char**ppString)
{
	std::string* pstring = oValue.get_string();
	*ppString = (char*)pstring->data();
}

inline void XmlRpcValue_To_String(XmlRpcValue &oValue, CString &strValue)
{
	char *pBuffer = NULL;
	XmlRpcValue_To_String(oValue, &pBuffer);
	strValue = pBuffer;
}


inline void XmlRpcValue_To_Buffer(XmlRpcValue &oValue, char **ppBuffer, long &nLen)
{
	XmlRpcValue::BinaryData &oData = oValue;
	*ppBuffer= &oData[0];
	nLen = oData.size();
}

inline void String_To_XmlRpcValue(const CString &strValue, XmlRpcValue &oValue)
{
	//yyj
#ifndef _PSX_IDE_QT_
	oValue = strValue;
#else
	char* pstrValue;
	long nLen = 0;
	CString_to_char(strValue, pstrValue, nLen);
	oValue = pstrValue;
#endif

	return;

// 	long nLen = String_Char_Count(strValue);
// 	oValue = "";
// 	std::string* pstring = oValue.get_string();
// 	pstring->resize(nLen+5);
// 	char *pBuffer = (char*)pstring->data();
// 
// 	CString_to_char(strValue, pBuffer);
}

inline void Buffer_To_XmlRpcValue(char *pBuffer, long nLen, XmlRpcValue &oValue)
{
	oValue.SetBinaryData(pBuffer, nLen);
}

inline void CDvmDataset_to_XmlRpcValue(CDvmDataset &oDataset, XmlRpcValue &oValue)
{
	CBinarySerialBuffer oBuffer;
	long nLen = 0;
	char *pBuffer = NULL;
	oDataset.SerializeWrite(oBuffer);
	oBuffer.GetBuffer(&pBuffer, &nLen);
	Buffer_To_XmlRpcValue(pBuffer, nLen, oValue);
}

inline void XmlRpcValue_to_CDvmDataset(XmlRpcValue &oValue, CDvmDataset &oDataset)
{
	char *pRptBuffer = NULL;
	long nLen = 0;

	XmlRpcValue_To_Buffer(oValue, &pRptBuffer, nLen);
	oDataset.SerializeRead(pRptBuffer, nLen);
}

inline void String_to_ExBaseObject(const CString &strResXML,CExBaseObject &oResult,CXmlRWKeys *pXmlRWKeys)
{
// 	char *pStrXml = (LPSTR)(LPCTSTR)strResXML;
// 	long nLenXml = strResXML.GetLength();
//	oResult.SetXml_UTF8(pStrXml,nLenXml,pXmlRWKeys);
	BSTR bstrXml = strResXML.AllocSysString();  
	oResult.SetXml(bstrXml,pXmlRWKeys);
	::SysFreeString(bstrXml); // ”√ÕÍ Õ∑≈
}

inline void ExBaseObject_to_XmlRpcValue(CExBaseObject &oResult,XmlRpcValue &oValue,CXmlRWKeys *pXmlRWKeys)
{
	CString strXML;
	oResult.GetXml(pXmlRWKeys,strXML);
	String_To_XmlRpcValue(strXML,oValue);
}

inline void XmlRpcValue_to_ExBaseObject(XmlRpcValue &oValue,CExBaseObject &oResult,CXmlRWKeys *pXmlRWKeys)
{
	CString strResXML;
	XmlRpcValue_To_String(oValue,strResXML);

	String_to_ExBaseObject(strResXML,oResult,pXmlRWKeys);
}

#endif // _XmlRpcApi_MFC_H__
