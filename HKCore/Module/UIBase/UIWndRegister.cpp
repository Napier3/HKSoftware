//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWndRegister.cpp  CUIWndRegister


#include "stdafx.h"
#include "UIWndRegister.h"
#include "UIWndLayer.h"

long CUIWndRegister::g_nUIWndRegisterRef = 0;
BOOL CUIWndRegister::g_bPopRegister = FALSE;

#define _not_use_safety_

CUIWndRegister::CUIWndRegister()
{
	g_nUIWndRegisterRef++;
	
#ifndef _not_use_safety_
	//启动加密狗
	CSafenet_hasp::Create(0);

	if (CSafenet_hasp::hasp_has_catalog())
	{
		//hasp_ViewEntitlementInfor(FETUREID_GBDEV);
	}
#endif
}

CUIWndRegister::~CUIWndRegister()
{
	g_nUIWndRegisterRef--;
#ifndef _not_use_safety_
	CSafenet_hasp::Release();
#endif
}

long CUIWndRegister::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlReadOwn(oNode, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CUIWndRegister::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CUIWndRegister::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CUIWindowBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CUIWndRegister::InitAfterRead()
{
	CUIWindowBase::InitAfterRead();
}

BOOL CUIWndRegister::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CUIWindowBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CUIWndRegister *p = (CUIWndRegister*)pObj;

	return TRUE;
}

BOOL CUIWndRegister::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIWindowBase::CopyOwn(pDest);

	CUIWndRegister *p = (CUIWndRegister*)pDest;

	return TRUE;
}

CBaseObject* CUIWndRegister::Clone()
{
	CUIWndRegister *p = new CUIWndRegister();
	Copy(p);
	return p;
}

BOOL CUIWndRegister::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CUIWndRegister::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	pNew = CUIWindowBase::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);


	return pNew;
}

CExBaseObject* CUIWndRegister::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	pNew = CUIWindowBase::CreateNewChild(nClassID);

	return pNew;
}


BOOL CUIWndRegister::UICreate(CWnd *pParent)
{
	if (m_pWindow != NULL)
	{
		LOG_WriteLawString("recreate BitMap");
	}

	CRect rect = GetWndPosition();
	BOOL bState = FALSE;	

	BOOL status = Create(
		NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT | SS_NOTIFY ,
		rect,
		pParent,
		GenerateWindowID());

	if ( !status )
	{
		return FALSE;
	}

	CUIBaseFont *pFont = GetUIBaseFont();

	if (pFont != NULL)
	{
		SetFont(pFont->GetFont());
	}

	m_pWindow = this;

	InitRegisterText();

	return TRUE;
}

void CUIWndRegister::InitRegisterText()
{
	CString strText;

// 	if (Encrypt_IsEncrypt())
// 	{
// 		strText = Encrypt_GetUserMsg();
// 	}
// 	else
// 	{
// 		strText = _T("你使用的系统没有授权，点击“我”进行注册！");
// 	}
#ifndef _not_use_safety_
	strText += hasp_get_ownership(TRUE);
#endif
	strText += _T("    ");
// 	strText += hasp_get_develop(TRUE);
// 	strText += _T("    ");
// 	strText += hasp_get_user_cop(TRUE);

	SetWndText(strText);
}

BOOL CUIWndRegister::Destroy()
{
	if (m_pWindow != NULL)
	{
		DestroyWindow();
		m_pWindow = NULL;
	}

	return TRUE;
}



BEGIN_MESSAGE_MAP(CUIWndRegister, CStatic)
	//{{AFX_MSG_MAP(CUIWndStaticText)
	ON_WM_CTLCOLOR_REFLECT()
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

HBRUSH CUIWndRegister::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	HBRUSH hbr=(HBRUSH)GetStockObject(HOLLOW_BRUSH);
	pDC->SetBkMode(TRANSPARENT);

	if (m_pFont != NULL)
	{
		pDC->SetTextColor(m_pFont->m_crColor);
	}
	else
	{
		pDC->SetTextColor(RGB(255, 0, 0));
	}

	return hbr;
}

void CUIWndRegister::OnClicked() 
{
	if (g_bPopRegister)
	{
		return;
	}

// 	if (Encrypt_IsEncrypt())
// 	{
// 		return;
// 	}
// 
// 	g_bPopRegister = TRUE;
// 	CString strExe;
// 	 strExe = Encrypt_GetEncryptRegister();
// 	 
// 	 SHELLEXECUTEINFO ShExecInfo = {0};
// 	 ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
// 	 ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
// 	 ShExecInfo.hwnd = NULL;
// 	 ShExecInfo.lpVerb = NULL;
// 	 ShExecInfo.lpFile = strExe;
// 	 ShExecInfo.lpParameters = _T("");
// 	 ShExecInfo.lpDirectory = NULL;
// 	 ShExecInfo.nShow = SW_SHOW;
// 	 ShExecInfo.hInstApp = NULL;
// 	 ShellExecuteEx(&ShExecInfo);
// 	 WaitForSingleObject(ShExecInfo.hProcess,INFINITE);
// 
// 	Encrypt_ReloadEncryptFile();
// 	InitRegisterText();
	g_bPopRegister = 0;
}

void CUIWndRegister::SetWndText(CString strWndText)
{
	CUIWindowBase::SetWndText(strWndText);

	if (m_pWindow == NULL)
	{
		return;
	}

	CWnd *pParentWnd = (CWnd*)m_pWindow->GetParent();

	if (pParentWnd != NULL)
	{
		if (::IsWindow(pParentWnd->m_hWnd))
		{
			pParentWnd->InvalidateRect(GetWndPosition(), TRUE);
		}
	}
}
// 
// CRect CUIWndRegister::GetWndPosition()
// {
// 	CUIWndLayer *pLayer = (CUIWndLayer*)CExBaseObject::GetParent();
// 
// 	CRect rcLayer = pLayer->GetWndPosition();
// 	CRect rcWnd = CRect(m_nLeft, m_nTop, m_nLeft+GetWndWidth(), m_nTop + GetWndHeight());
// 	rcWnd.left += rcLayer.left;
// 	rcWnd.top  += rcLayer.top;
// 
// 	return rcWnd;
// }
