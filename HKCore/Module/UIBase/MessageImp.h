//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MessageImp.h  CMessageImp

#pragma once

#include "UIBaseGlobal.h"

#define WNDSTATE_NONE      0x00000000
#define WNDSTATE_FOCUS     0x00000001
#define WNDSTATE_ENABLE    0x00000002
#define WNDSTATE_VISIBLE   0x00000004
#define WNDSTATE_ANAY      0x00000007

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


class CMessageImp : public CExBaseObject
{
public:
	CMessageImp();
	virtual ~CMessageImp();


	CString  m_strWndState;
	long  m_nSysMsg;
	CString  m_strScript;

public:
	void Run(BOOL bShowMessage=FALSE);
	CBaseObject* GetParentPage();

//重载函数
public:
	virtual UINT GetClassID() {    return UICLASSID_CMESSAGEIMP;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CMessageImpKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
};

