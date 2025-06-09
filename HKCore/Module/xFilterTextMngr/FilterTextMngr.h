//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//FilterTextMngr.h  CFilterTextMngr

#pragma once

#include "GlobalDataMngrGlobal.h"


#include "FilterText.h"

class CFilterTextMngr : public CExBaseList
{
public:
	CFilterTextMngr();
	virtual ~CFilterTextMngr();


//重载函数
public:
	virtual UINT GetClassID() {    return TFLTCLASSID_CFILTERTEXTMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CGlobalDataMngrXmlRWKeys::CFilterTextMngrKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CExBaseObject* pObj);
	virtual BOOL CopyOwn(CExBaseObject* pDest);
	virtual CExBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:
	CString m_strFile;

//私有成员变量访问方法
public:
	virtual BOOL OpenXmlFile(const CString &strFile);
	virtual BOOL SaveXmlFile();
	
	CFilterText* AddText(const CString &strText);
};

