#pragma once
#include "WzdDlgBase.h"

class CWzdDlgMngr : public CExBaseList
{
public:
	CWzdDlgMngr();
	virtual ~CWzdDlgMngr();

public:
	virtual void AddNewChild(CWzdDlgBase* pWzdDlgBase, const CString& strID);
	virtual CWnd* GetActiveWnd();
	virtual CWzdDlgBase* GetActiveDlg();
	virtual void SetActiveDlg(const CString& strID);
	virtual void SetActiveDlg(CWnd* pWnd);
	virtual void EnableDlg(const CString& strID);
	virtual void DisableDlg(const CString& strID);
};