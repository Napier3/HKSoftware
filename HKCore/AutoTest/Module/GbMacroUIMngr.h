#pragma once

#include "GuideBook\SysParas.h"
#include "GuideBook\Cpus.h"

class CGbUIWndInterface
{
public:
	virtual BOOL GbUICreate (CExBaseList *pCpus, CExBaseList *pSysParas, CWnd *pParent, HINSTANCE hInstance) = 0;
	virtual BOOL GbUIFree () = 0;
	virtual BOOL GbUIShowParas(const CString &strParas) = 0;
	virtual BOOL GbUIGetParas(CString &strParas) = 0;
	virtual BOOL GbUIShow () = 0;
	virtual BOOL GbUIHide () = 0;
	virtual BOOL GbUIResultEx (CString &strResultEx) = 0;
	virtual BOOL GbUIFaultParaEx (CString &strFaultParaEx) = 0;

};

class CWndGbMacroUI : public CExBaseObject
{
public:
	CWndGbMacroUI();
	virtual ~CWndGbMacroUI();

	CWnd *m_pWndGbMacroUI;

};

class CWndGbMacroUIList : public CExBaseList
{
private:
	CWndGbMacroUIList();
	virtual ~CWndGbMacroUIList();

	static long g_nGbMacroUILibMngrRef;

public:
	static CWndGbMacroUIList *g_pGbMacroUILibMngr;
	static CWndGbMacroUIList* Create();
	static void Release();
	
	static CWndGbMacroUI* CreateGbMacroUI(CWnd *pWnd);
	static void FreeGbMacroUI(CWnd *pMacroUI);
	static CWndGbMacroUI* FindUIWnd(CWnd *pWnd);

protected:
	CWndGbMacroUI* In_CreateGbMacroUI(CWnd *pWnd);
	void In_FreeGbMacroUI(CWnd *pMacroUI);
	CWndGbMacroUI* In_FindUIWnd(CWnd *pWnd);
};

