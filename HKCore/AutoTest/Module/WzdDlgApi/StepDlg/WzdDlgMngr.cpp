#include "stdafx.h"
#include "WzdDlgMngr.h"

CWzdDlgMngr::CWzdDlgMngr()
{

}

CWzdDlgMngr::~CWzdDlgMngr()
{

}

void CWzdDlgMngr::AddNewChild(CWzdDlgBase* pWzdDlgBase, const CString& strID)
{
	pWzdDlgBase->m_strID = strID;
	CExBaseList::AddNewChild(pWzdDlgBase);
}

CWnd* CWzdDlgMngr::GetActiveWnd()
{
	CWzdDlgBase* pDlg = GetActiveDlg();
	if(pDlg)
	{
		return pDlg;
	}
	return 0;
}

CWzdDlgBase* CWzdDlgMngr::GetActiveDlg()
{
	POS pos = GetHeadPosition();
	while (pos)
	{
		CWzdDlgBase* pDlg = (CWzdDlgBase*)GetNext(pos);
		if (pDlg->IsActived())
		{
			return pDlg;
			break;
		}
	}
	return 0;
}

void CWzdDlgMngr::SetActiveDlg(const CString& strID)
{
	POS pos = GetHeadPosition();
	while (pos)
	{
		CWzdDlgBase* pDlg = (CWzdDlgBase*)GetNext(pos);
		if(pDlg->m_strID == strID)
		{
			pDlg->SetActived(TRUE);
		}
		else
		{
			pDlg->SetActived(FALSE);
		}
	}
}

void CWzdDlgMngr::SetActiveDlg(CWnd* pWnd)
{
	POS pos = GetHeadPosition();
	while (pos)
	{
		CWzdDlgBase* pDlg = (CWzdDlgBase*)GetNext(pos);
		if(pDlg == pWnd)
		{
			pDlg->SetActived(TRUE);
		}
		else
		{
			pDlg->SetActived(FALSE);
		}
	}
}

void CWzdDlgMngr::EnableDlg(const CString& strID)
{
	CWzdDlgBase* pDlg = (CWzdDlgBase*)FindByID(strID);
	if(pDlg)
	{
		pDlg->SetEnabled(TRUE);
	}
}

void CWzdDlgMngr::DisableDlg(const CString& strID)
{
	CWzdDlgBase* pDlg = (CWzdDlgBase*)FindByID(strID);
	if(pDlg)
	{
		pDlg->SetEnabled(FALSE);
	}
}