//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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
//重载函数
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

//私有成员变量
private:

	CPen m_crFontPen;
	CPen m_crFrmPen;
	CBrush m_crFillBkBrush;

//私有成员变量访问方法
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

