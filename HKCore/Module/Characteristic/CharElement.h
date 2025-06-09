//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElement.h  CCharElement

#pragma once

#include "CharacteristicGlobal.h"


#include "CharTestLineDefine.h"

class CCharElement : public CExBaseList
{
public:
	CCharElement();
	virtual ~CCharElement();


	CString  m_strDir;
//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENT;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	virtual long InsertToListCtrl(CListCtrl *pListCtrl,long lItemIndex);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
	virtual CString ReturnXml();
//私有成员变量
private:

//私有成员变量访问方法
public:
};

