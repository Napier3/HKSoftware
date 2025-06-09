//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWndPageRef.h  CUIWndPageRef

#pragma once

#include "UIBaseGlobal.h"

#include "UIWndPage.h"

class CUIWndPageDef : public CExBaseObject
{
public:
	CUIWndPageDef();
	virtual ~CUIWndPageDef();

	CString m_strPageFile;

//重载函数
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIWNDPAGEDEF;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIWndPageDefKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:
	CUIWndPage *m_pPage;

//私有成员变量访问方法
public:
	CUIWndPage* GetPage();

};

