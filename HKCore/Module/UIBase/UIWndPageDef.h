//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

//���غ���
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

//˽�г�Ա����
private:
	CUIWndPage *m_pPage;

//˽�г�Ա�������ʷ���
public:
	CUIWndPage* GetPage();

};

