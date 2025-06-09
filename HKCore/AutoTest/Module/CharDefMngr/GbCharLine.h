//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbCharLine.h  CGbCharLine

#pragma once

#include "GbCharDefMngrGlobal.h"



class CGbCharLine : public CExBaseObject
{
public:
	CGbCharLine();
	virtual ~CGbCharLine();


	CString  m_strXb;
	CString  m_strYb;
	CString  m_strAngle;
	CString  m_strDir;
//重载函数
public:
	virtual UINT GetClassID() {    return CHRCLASSID_CGBCHARLINE;   }
	virtual BSTR GetXmlElementKey()  {      return CGbCharDefMngrXmlRWKeys::CGbCharLineKey();     }
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

