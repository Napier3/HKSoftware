//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIBaseAxis.h  CUIBaseAxis

#pragma once

#include "UIBaseGlobal.h"


#include "UIBaseFont.h"
#include "UIBaseText.h"
#include "UIEvents.h"

class CUIBaseItem : public CExBaseList
{
public:
	CUIBaseItem();
	virtual ~CUIBaseItem();


//重载函数
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIBASEITEM;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIBaseItemKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
protected:
	CUIBaseFont *m_pFont;
	CUIWindowText *m_pText;
	CUIEvents *m_pEvents;
//私有成员变量访问方法
public:
	CString GetText(){ return m_pText->m_strText;}
};

