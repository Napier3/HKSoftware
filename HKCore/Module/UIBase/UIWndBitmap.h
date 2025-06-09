//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWndBitmap.h  CUIWndBitmap

#pragma once

#include "UIBaseGlobal.h"

#include "UIWindowBase.h"
#include "UIMemDC.h"
#include "..\BaseClass\BitmapFile.h"

#define _use_bitmap_file

class CUIWndBitmap : public CStatic, public CUIWindowBase
{
public:
	CUIWndBitmap();
	virtual ~CUIWndBitmap();


	CString  m_strNormalBmpFile;
	CString  m_strDisablelBmpFile;
	CString  m_strClickBmpFile;
	CString  m_strActiveBmpFile;

//重载函数
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIWNDBITMAP;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIWndBitmapKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

public:
	virtual BOOL UICreate(CWnd *pParent);
	virtual BOOL Destroy();

//私有成员变量
private:

#ifndef _use_bitmap_file
	CDib		   m_oDibNormal;
	CDib		   m_oDibActive;
	CDib		   m_oDibClick;
	CDib		   m_oDibDisable;
#else
	CBitmapFile		   m_oDibNormal;
	CBitmapFile		   m_oDibActive;
	CBitmapFile		   m_oDibClick;
	CBitmapFile		   m_oDibDisable;
	//CUIMemDC       m_oUIMemDC;
#endif

//私有成员变量访问方法
public:


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUIWndBitmap)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	void LoadUIBitmap();
	//{{AFX_MSG(CUIWndBitmap)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnClicked();
	afx_msg void OnDoubleclicked();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

