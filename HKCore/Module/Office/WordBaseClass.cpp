// WordBaseClass.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WordBaseClass.h"
#include "..\API\FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
CWordDocBase::CWordDocBase(MSWord::_Application &oWordApp)
{
	m_WordApp = oWordApp;
}

CWordDocBase::CWordDocBase()
{
	m_WordApp = NULL;
}

CWordDocBase::~CWordDocBase()
{
	m_WordApp = NULL;
}

long CWordDocBase::New(const CString &strTemplateFile, const CString &strWordFile, BOOL bAdjust)
{
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant vTemplate(strTemplateFile);			
	COleVariant vRptFile(strWordFile);			
	BOOL bWordCreate = TRUE;

	ASSERT (m_WordApp != NULL);

	if (  m_WordApp == NULL)
	{
		return 0;
	}

	MSWord::Documents docs;

	try
	{
		//如果打开了报告文档，则保存并关闭文档
		docs =   m_WordApp.GetDocuments();

		//打开报告文档
		if (!Open(strWordFile, bAdjust))
		{
			try
			{
				//如果打开失败，则打开测试模板，并且填写试验报告
				AddNewReport(strTemplateFile);
				SaveAs(strWordFile);
			}
			catch (...)
			{
			}
		}

		if (bAdjust)
		{
			AdjustWordWindow();
		}
	}
	catch(...)
	{
	}

	return TRUE;
}

long CWordDocBase::New(const CString &strWordFile, BOOL bAdjust)
{
	return New(_T(""), strWordFile, bAdjust);
}

BOOL CWordDocBase::Open(const CString  &strWordFile, BOOL bAdjust)
{
	//CFileFind find;

	//if (!find.FindFile(strWordFile))
	if (!IsFileExist(strWordFile))
	{
		return FALSE;
	}

	if ( m_WordApp == NULL)
	{
		return FALSE;
	}

	MSWord::Documents docs = NULL;
	docs =  m_WordApp.GetDocuments();

	if (docs == NULL)
	{
		return FALSE;
	}

	COleVariant vRptFile(strWordFile);			
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	BOOL bTrue = TRUE;
	try
	{
		//打开试验报告文件
		m_oDoc = docs.Open(&vRptFile,covOptional,covFalse,covTrue,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covTrue);
	}
	catch (...)
	{
		bTrue = FALSE;
	}

	if (bAdjust)
	{
		AdjustWordWindow();
	}

	return bTrue;
}

long CWordDocBase::Save()
{
	if( m_WordApp == NULL)
		return FALSE;

	if(m_oDoc == NULL)
		return FALSE;

	m_oDoc.Save();

	return TRUE;
}

long CWordDocBase::SaveAs(const CString  &strWordFile)
{
	if( m_WordApp == NULL || m_oDoc == NULL)
		return FALSE;

	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant vRptFile(strWordFile);
	m_oDoc.SaveAs(vRptFile,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional);

	return TRUE;
}

long CWordDocBase::Close(long nSave)
{
	if( m_WordApp == NULL || m_oDoc == NULL)
	{
		return TRUE;
	}

	CloseWordDocWindow();

	return TRUE;
}

BOOL CWordDocBase::AddNewReport(const CString &strTemplateFile)
{
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant FileFormat((long)0);
	COleVariant Password(_T(""));
	COleVariant WritePassword(_T(""));

	CString strWordRptFile;
	COleVariant TmplFile(strTemplateFile);

	//CFileFind find;
	//if (!find.FindFile(strTemplateFile))
	//{
	//	//return FALSE;
	//}

	BOOL bTrue = TRUE;
	MSWord::Documents docs =  m_WordApp.GetDocuments();

	try
	{
		m_oDoc = docs.Add(&TmplFile,&covFalse,&FileFormat,&covTrue);
	}
	catch (...)
	{
		bTrue = FALSE;
	}

	return bTrue;
}


BOOL CWordDocBase::CloseWordDocWindow()
{
	COleVariant covTrue((long)TRUE);
	COleVariant covFalse((long)FALSE);
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	try
	{
		if (m_oDoc != NULL)
		{
			m_oDoc.Close(covFalse,covOptional,covOptional);
			m_oDoc = NULL;
		}
	}
	catch (...) 
	{
		TRACE("CloseWordDocWindow:Error");
	}

	return TRUE;
}

void CWordDocBase::AdjustWordWindow()
{
	CWnd *pWnd = NULL;

	//获取Word文档的窗口
	try
	{
		if (m_oDoc != NULL)
		{
			CString strName = m_oDoc.GetName();
			CString strWordName =  m_WordApp.GetName();
			CString strWordCaption =  m_WordApp.GetCaption();
			MSWord::Window docWnd = m_oDoc.GetActiveWindow();
		
			if (docWnd != NULL)
			{
				CString strWndCaption = docWnd.GetCaption();
				CString strWndTitle;
				strWndTitle.Format(_T("%s - %s"),strWndCaption,strWordCaption);
				pWnd=CWnd::FindWindow(NULL,strWndTitle);
			}
		}
	}
	catch(...)
	{
	}

	if (pWnd == NULL)
	{
		if (::IsWindow(m_hWordWnd))
		{
			pWnd = CWnd::FromHandle(m_hWordWnd);
		}
	}

	if (pWnd != NULL)
	{
		CRect rectWin;
		pWnd->GetWindowRect(rectWin);
		::SetParent(pWnd->GetSafeHwnd(),m_pParentWnd->GetSafeHwnd());

		if (TRUE/*pApp->GetCntrConfig()->m_nHideAllCmdbars == 1*/)
		{
			if (FALSE/*CanUnLockReport()*/)
			{
			}
			else
			{
				//注释掉下面一行，可以在word中输入
				pWnd->ModifyStyle(0,WS_CHILD);
			}
			pWnd->ModifyStyle(WS_BORDER | WS_DLGFRAME | WS_EX_WINDOWEDGE,0);
			pWnd->ModifyStyle(WS_SIZEBOX,0);
			pWnd->SetMenu(NULL);

			// need to adjust the client edge style as max/restore happens
			DWORD dwStyle = ::GetWindowLong(m_pParentWnd->GetSafeHwnd(), GWL_EXSTYLE);
			DWORD dwNewStyle = dwStyle;
			dwNewStyle |= WS_EX_CLIENTEDGE;

			if (dwStyle != dwNewStyle)
			{
				// SetWindowPos will not move invalid bits
				::RedrawWindow(m_pParentWnd->GetSafeHwnd(), NULL, NULL,
					RDW_INVALIDATE | RDW_ALLCHILDREN);

				// remove/add WS_EX_CLIENTEDGE to MDI client area
				::SetWindowLong(m_pParentWnd->GetSafeHwnd(), GWL_EXSTYLE, dwNewStyle);
				::SetWindowPos(m_pParentWnd->GetSafeHwnd(), NULL, 0, 0, 0, 0,
					SWP_FRAMECHANGED | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE |
					SWP_NOZORDER | SWP_NOCOPYBITS);
				pWnd->ShowWindow(SW_SHOWMAXIMIZED);

				// return new client area
				::GetClientRect(m_pParentWnd->GetSafeHwnd(), &rectWin);
				pWnd->MoveWindow(rectWin);
				pWnd->SetFocus();
				m_hWordWnd = pWnd->m_hWnd;
			}

			::GetClientRect(m_pParentWnd->GetSafeHwnd(), &rectWin);
			pWnd->MoveWindow(rectWin);
			pWnd->SetFocus();
			pWnd->ShowWindow(SW_SHOWMAXIMIZED);			
		}
		else
		{
			pWnd->ModifyStyle(WS_SYSMENU,0);
			pWnd->ModifyStyle(WS_SIZEBOX,0);
			::GetClientRect(m_pParentWnd->GetSafeHwnd(), &rectWin);
			pWnd->MoveWindow(rectWin);
			pWnd->SetFocus();
		}

		m_hWordWnd = pWnd->m_hWnd;
	}
	else
	{
	}
}


//////////////////////////////////////////////////////////////////////////
//CWordAppBase

CWordAppBase::CWordAppBase(MSWord::_Application &oWordApp)
{
	m_WordApp = oWordApp;
	m_bIsAppRef = TRUE;
}

CWordAppBase::CWordAppBase()
{
	m_WordApp = NULL;
	m_bIsAppRef = FALSE;
}

CWordAppBase::~CWordAppBase()
{
	
}
	
MSWord::_Application CWordAppBase::GetWordApp(BOOL bVisible)
{
	if (m_WordApp != NULL)
	{
		return m_WordApp;
	}

	m_bIsAppRef = FALSE;
	COleVariant covTrue((long)TRUE),covFalse((long)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	try
	{
		if (!m_WordApp.CreateDispatch(_T("Word.Application")))
		{
			return  NULL;
		}

		m_WordApp.SetVisible(bVisible);
	}
	catch (...)
	{
	}

	return m_WordApp;
}

BOOL CWordAppBase::CloseWordApplication()
{
	if (m_bIsAppRef)
	{
		m_WordApp = NULL;
		return TRUE;
	}

	COleVariant covTrue((long)TRUE);
	COleVariant covFalse((long)FALSE);
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	try
	{
		MSWord::Documents oDocs = m_WordApp.GetDocuments();

		if (oDocs.GetCount() > 0)
		{
			return FALSE;
		}
	}
	catch (...)
	{

	}

	try
	{
		if(m_WordApp)
		{
			m_WordApp.Quit(covFalse, covOptional, covOptional);
			m_WordApp = NULL;
		}
	}
	catch (...) 
	{
	}

	m_WordApp = NULL;

	return TRUE;
}

CWordDocBase* CWordAppBase::CreateWordDocBase()
{
	CWordDocBase *pNew = new CWordDocBase(m_WordApp);
	return pNew;
}

