#pragma once

// #include "GuideBook\SysParas.h"
// #include "GuideBook\Cpus.h"

//typedef LONG (__cdecl *EP_GETEPOTOSTRING)(long nStringID, char *pString, long &nStringLen);

//extern EP_GETEPOTOSTRING 								Pp_GetEpotoString;


typedef CWnd* (__cdecl *EP_GbUICreate) (CExBaseList *pCpus, CExBaseList *pSysParas, CWnd *pParent, HINSTANCE hInstance);
typedef void (__cdecl *EP_GbUIFree) (CWnd *pWnd);
typedef void (__cdecl *EP_GbUIShowParas)(CWnd *pWnd, const CString &strParas);
typedef void (__cdecl *EP_GbUIGetParas)(CWnd *pWnd, CString &strParas);
typedef void (__cdecl *EP_GbUIShow) (CWnd *pWnd, CWnd *pParent);
typedef void (__cdecl *EP_GbUIHide) (CWnd *pWnd);
typedef void (__cdecl *EP_GbUIResultEx) (CWnd *pWnd, CString &strResultsEx);
typedef void (__cdecl *EP_GbUIFaultParaEx) (CWnd *pWnd, CString &strFaultParaEx);

class CGbMacroUILib;

class CGbMacroUI : public CExBaseObject
{
public:
	CGbMacroUI();
	virtual ~CGbMacroUI();

	void GbUICreate (CExBaseList *pCpus, CExBaseList *pSysParas, CWnd *pParent, HINSTANCE hInstance);
	void GbUIFree ();
	void GbUIShowParas( const CString &strParas);
	void GbUIGetParas( CString &strParas);
	void GbUIShow ( CWnd *pParent);
	void GbUIHide ();
	void GbUIResultEx(CString &strResultsEx);
	void GbUIFaultParaEx(CString &strFaultParaEx);

	CWnd* GetWndGbUI()	{	return m_pWndGbMacroUI;	}
	CString m_strDLL;
	CExBaseObject *m_pGuideBook;

protected:
	EP_GbUICreate    m_pGbUICreate;
	EP_GbUIFree      m_pGbUIFree;
	EP_GbUIShowParas m_pGbUIShowParas;
	EP_GbUIGetParas  m_pGbUIGetParas;
	EP_GbUIShow      m_pGbUIShow;
	EP_GbUIHide      m_pGbUIHide;
	EP_GbUIResultEx  m_pGbUIResultEx;
	EP_GbUIFaultParaEx  m_pGbUIFaultParaEx;

	CWnd *m_pWndGbMacroUI;

	friend CGbMacroUILib;
};

class CGbMacroUILib : public CExBaseList
{
public:
	CGbMacroUILib();
	virtual ~CGbMacroUILib();

protected:
	HINSTANCE m_hMacroUILib;

	EP_GbUICreate    m_pGbUICreate;
	EP_GbUIFree      m_pGbUIFree;
	EP_GbUIShowParas m_pGbUIShowParas;
	EP_GbUIGetParas  m_pGbUIGetParas;
	EP_GbUIShow      m_pGbUIShow;
	EP_GbUIHide      m_pGbUIHide;
	EP_GbUIResultEx  m_pGbUIResultEx;
	EP_GbUIFaultParaEx  m_pGbUIFaultParaEx;

public:
	BOOL LoadLib(const CString &strDllFile);
	void ReleaseLib();
	BOOL HasLoadLib();

	CGbMacroUI* CreateGbMacroUI(CExBaseObject *pGuideBook);
	CGbMacroUI* FindByGuideBook(CExBaseObject *pGuideBook);
	void FreeGbMacroUI(CGbMacroUI *pMacroUI);
};

class CGbMacroUILibMngr : public CExBaseList
{
private:
	CGbMacroUILibMngr();
	virtual ~CGbMacroUILibMngr();

	static long g_nGbMacroUILibMngrRef;

public:
	static CGbMacroUILibMngr *g_pGbMacroUILibMngr;
	static CGbMacroUILibMngr* Create();
	static void Release();
	
	static CGbMacroUI* CreateGbMacroUI(const CString &strDllFile, CExBaseObject *pGuideBook);
	static void FreeGbMacroUI(CGbMacroUI *pMacroUI);

protected:
	CGbMacroUI* In_CreateGbMacroUI(const CString &strDllFile, CExBaseObject *pGuideBook);
	void In_FreeGbMacroUI(CGbMacroUI *pMacroUI);
};

