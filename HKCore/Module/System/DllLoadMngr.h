// DllLoadMngr.h: interface for the CDllLoadMngr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DllLoadMngr_H__)
#define AFX_DllLoadMngr_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../BaseClass/ExBaseList.h"

class CDllLoadObj : public CExBaseObject  
{
public:
	CDllLoadObj();
	virtual ~CDllLoadObj();
	

	BOOL LoadDLL();
	BOOL LoadDLL(const CString &strDllPath);
	void FreeInstance();

	BOOL HasLoadLib()					{		return (m_hLibInstance != NULL);		}
	HINSTANCE GetLibInstance()	{		return m_hLibInstance;	}

private:
	HINSTANCE m_hLibInstance;
	
};

class CDllLoadMngr : public CExBaseList 
{
public:
	CDllLoadMngr();
	virtual ~CDllLoadMngr();

public:
	CDllLoadObj* AddLib(const CString &strDllPath);
	HINSTANCE FindLib(const CString &strDllPath);

};

#endif // !defined(AFX_DllLoadMngr_H__)
