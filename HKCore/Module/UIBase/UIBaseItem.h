//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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


//���غ���
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

//˽�г�Ա����
protected:
	CUIBaseFont *m_pFont;
	CUIWindowText *m_pText;
	CUIEvents *m_pEvents;
//˽�г�Ա�������ʷ���
public:
	CString GetText(){ return m_pText->m_strText;}
};

