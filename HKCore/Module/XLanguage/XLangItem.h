//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XLangItem.h  CXLangItem

#pragma once

#include "XLanguageGlobal.h"



class CXLangItem : public CExBaseObject
{
public:
	CXLangItem();
	virtual ~CXLangItem();

	CString  m_strSrcText;
	CString  m_strTranslation;
	CString  *m_pstrResourceRef;
//重载函数
public:
	virtual UINT GetClassID() {    return LGUGCLASSID_CLANGITEM;   }
	virtual BSTR GetXmlElementKey()  {      return CXLanguageXmlRWKeys::CXLangItemKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
};

