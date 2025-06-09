//SfuncPageBase.h  CSfuncPageBase

#pragma once

class CSfuncPageBase : public CExBaseObject
{
public:
	CSfuncPageBase();
	virtual ~CSfuncPageBase();

	CString  m_strType;
//重载函数
public:
	virtual UINT GetClassID() {    return SFNCLASSID_CSFUNCPAGEBASE;   }
	virtual BSTR GetXmlElementKey()  {      return CScriptFuncXmlRWKeys::CSfuncPageBaseKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);

//私有成员变量
private:

//私有成员变量访问方法
public:
};

