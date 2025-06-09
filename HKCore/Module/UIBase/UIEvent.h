//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIEvent.h  CUIEvent

#pragma once

#include "UIBaseGlobal.h"

#define WNDSTATE_NONE      0x00000000
#define WNDSTATE_FOCUS     0x00000001
#define WNDSTATE_ENABLE    0x00000002
#define WNDSTATE_VISIBLE   0x00000004
#define WNDSTATE_ANAY      0x00000007


static const CString g_strEventID_OnArrowUp = _T("on-arrow-up");
static const CString g_strEventID_OnArrowDown = _T("on-arrow-down");
static const CString g_strEventID_OnArrowLeft = _T("on-arrow-left");
static const CString g_strEventID_OnArrowRight = _T("on-arrow-right");
static const CString g_strEventID_OnSetFoucus = _T("on-set-foucus");
static const CString g_strEventID_OnKillFoucus = _T("on-kill-foucus");
static const CString g_strEventID_OnEditChanged = _T("on-edit-changed");
static const CString g_strEventID_OnSelChanged = _T("on-sel-changed");
static const CString g_strEventID_OnDropDown = _T("on-dropdown");
static const CString g_strEventID_OnClick = _T("on-clk");
static const CString g_strEventID_OnDbClick = _T("on-dbclick");
static const CString g_strEventID_OnShow = _T("on-show");
static const CString g_strEventID_OnHide = _T("on-hide");
static const CString g_strEventID_OnCheck = _T("on-check");
static const CString g_strEventID_OnPreLoad = _T("on-pre-load");
static const CString g_strEventID_OnLoad = _T("on-load");
static const CString g_strEventID_OnUnload = _T("on-unload");
static const CString g_strEventID_OnPreCreate = _T("on-pre-create");
static const CString g_strEventID_OnCreate = _T("on-create");

inline BOOL UIWndState_IsAny(long nWndState)
{
	return (nWndState == WNDSTATE_ANAY);
}

inline BOOL UIWndState_IsEnable(long nWndState)
{
	return ((nWndState & WNDSTATE_ANAY) == WNDSTATE_ENABLE);
}

inline BOOL UIWndState_IsVisible(long nWndState)
{
	return ((nWndState & WNDSTATE_ANAY) == WNDSTATE_VISIBLE);
}

inline BOOL UIWndState_IsFocus(long nWndState)
{
	return ((nWndState & WNDSTATE_ANAY) == WNDSTATE_FOCUS);
}

static const CString g_pszKeyWndStateAny     = _T("any");
static const CString g_pszKeyWndStateFocus   = _T("focus");
static const CString g_pszKeyWndStateEnable  = _T("enable");
static const CString g_pszKeyWndStateVisible = _T("visible");


class CUIEvent : public CExBaseObject
{
public:
	CUIEvent();
	virtual ~CUIEvent();


	CString  m_strWndState;
	long  m_nSysMsg;
	CString  m_strScript;

public:
	void Run();
	CBaseObject* GetParentPage();

//重载函数
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIEVENT;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIEventKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:
	
//私有成员变量访问方法
public:
	CExBaseObject *GetParentWnd();
};

