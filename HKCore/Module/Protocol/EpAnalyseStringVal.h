//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpAnalyseStringVal.h  CEpAnalyseStringVal

#pragma once

#include "EpAnalyseStringGlobal.h"



class CEpAnalyseStringVal : public CExBaseObject
{
public:
	CEpAnalyseStringVal();
	virtual ~CEpAnalyseStringVal();


	CString  m_strValue;
	CString  m_strValue2;
//重载函数
public:
	virtual UINT GetClassID() {    return EPASCLASSID_CEPANALYSESTRINGVAL;   }
	virtual BSTR GetXmlElementKey()  {      return CEpAnalyseStringXmlRWKeys::CEpAnalyseStringValKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);

//私有成员变量
private:

//私有成员变量访问方法
public:
	BOOL IsValueIn(const CString &strValue);
};