//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbCharLines.h  CGbCharLines

#pragma once

#include "GbCharDefMngrGlobal.h"



class CGbCharLines : public CExBaseObject
{
public:
	CGbCharLines();
	virtual ~CGbCharLines();


	CString  m_strXb;
	CString  m_strYb;
	CString  m_strXe;
	CString  m_strYe;
	CString  m_strDir;
//重载函数
public:
	virtual UINT GetClassID() {    return CHRCLASSID_CGBCHARLINES;   }
	virtual BSTR GetXmlElementKey()  {      return CGbCharDefMngrXmlRWKeys::CGbCharLinesKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
};

