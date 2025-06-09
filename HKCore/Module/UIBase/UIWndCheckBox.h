//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//UIWndCheckBox.h  CUIWndCheckBox

#pragma once

#include "UIBaseGlobal.h"

#include "UIWindowBase.h"


class CUIWndCheckBox :public CButton, public CUIWindowBase
{
public:
	CUIWndCheckBox();
	virtual ~CUIWndCheckBox();


//���غ���
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIWNDCHECKBOX;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIWndCheckBoxKey();     }
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
	afx_msg void OnBnClicked();
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
};

