//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//FilterText.h  CFilterText

#pragma once

#include "GlobalDataMngrGlobal.h"



class CFilterText : public CExBaseObject
{
public:
	CFilterText();
	virtual ~CFilterText();


//重载函数
public:
	virtual UINT GetClassID() {    return TFLTCLASSID_CFILTERTEXT;   }
	virtual BSTR GetXmlElementKey()  {      return CGlobalDataMngrXmlRWKeys::CFilterTextKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CExBaseObject* pObj);
	virtual BOOL CopyOwn(CExBaseObject* pDest);
	virtual CExBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
};

