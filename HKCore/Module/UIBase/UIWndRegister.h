//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWndRegister.h  CUIWndRegister

#pragma once

#include "UIBaseGlobal.h"

#include "UIWindowBase.h"


class CUIWndRegister : public CStatic, public CUIWindowBase
{
public:
	CUIWndRegister();
	virtual ~CUIWndRegister();


	static long g_nUIWndRegisterRef;
	static BOOL g_bPopRegister;

//重载函数
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIWNDREGISTER;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIWndRegisterKey();     }
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
	void SetWndText(CString strWndText);
	//virtual CRect GetWndPosition();

//私有成员变量
private:

//私有成员变量访问方法
public:
	void InitRegisterText();

// Generated message map functions
protected:
	//{{AFX_MSG(CUIWndStaticText)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnClicked();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};

