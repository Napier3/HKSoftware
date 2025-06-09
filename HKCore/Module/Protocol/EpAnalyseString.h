//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpAnalyseString.h  CEpAnalyseString

#pragma once

#include "EpAnalyseStringGlobal.h"


#include "EpAnalyseStringVal.h"

class CEpAnalyseString : public CExBaseList
{
public:
	CEpAnalyseString();
	virtual ~CEpAnalyseString();


	CString  m_strString;
//重载函数
public:
	virtual UINT GetClassID() {    return EPASCLASSID_CEPANALYSESTRING;   }
	virtual BSTR GetXmlElementKey()  {      return CEpAnalyseStringXmlRWKeys::CEpAnalyseStringKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:
	CEpAnalyseStringVal* FindByValue(const CString &strValue);
};

