//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpAnalyseMngr.h  CEpAnalyseMngr

#pragma once

#include "EpAnalyseStringGlobal.h"


#include "EpAnalyseString.h"

class CEpAnalyseMngr : public CExBaseList
{
public:
	CEpAnalyseMngr();
	virtual ~CEpAnalyseMngr();


//重载函数
public:
	virtual UINT GetClassID() {    return EPASCLASSID_CEPANALYSEMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CEpAnalyseStringXmlRWKeys::CEpAnalyseMngrKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

//私有成员变量
private:

//私有成员变量访问方法
public:
};

