//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//UIWndButton.h  CUIWndButton

#pragma once

#include "UIBaseGlobal.h"

#include "UIWindowBase.h"


class CUIWndButton :public CButton, public CUIWindowBase
{
public:
	CUIWndButton();
	virtual ~CUIWndButton();

	COLORREF  m_crBkActiveColor;
	COLORREF  m_crBkDisableColor;
//���غ���
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIWNDBUTTON;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIWndButtonKey();     }
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


public:
	virtual BOOL UICreate(CWnd *pParent);
	virtual BOOL Destroy();

//˽�г�Ա����
private:

	CPen m_crFontPen;
	CPen m_crFrmPen;
	CBrush m_crFillBkBrush;

//˽�г�Ա�������ʷ���
public:
	afx_msg void OnBnClicked();
//	afx_msg void OnPaint();
	afx_msg void OnBnDoubleclicked();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	
	DECLARE_MESSAGE_MAP()
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
};

