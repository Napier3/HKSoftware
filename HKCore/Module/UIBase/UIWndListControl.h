//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//UIWndEdit.h  CUIWndEdit

#pragma once

#include "UIBaseGlobal.h"

#include "UIWindowBase.h"


class CUIWndListControl :public CListCtrl, public CUIWindowBase
{
public:
	CUIWndListControl();
	virtual ~CUIWndListControl();


	CString  m_strFormat;
//���غ���
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIWNDEDIT;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIWndEditKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	virtual BOOL UICreate(CWnd *pParent);
	virtual BOOL Destroy();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnEnChange();
};

