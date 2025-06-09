// DllLoadMngr.cpp: implementation of the CDllLoadMngr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DllLoadMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//
CDllLoadObj::CDllLoadObj()
{
	m_hLibInstance = NULL;
}

CDllLoadObj::~CDllLoadObj()
{
	
}

BOOL CDllLoadObj::LoadDLL()
{
	return LoadDLL(m_strID);
}

BOOL CDllLoadObj::LoadDLL(const CString &strDllPath)
{
	FreeInstance();

	m_hLibInstance = ::LoadLibrary(strDllPath);

	return (m_hLibInstance != NULL);
}

void CDllLoadObj::FreeInstance()
{
	if (m_hLibInstance != NULL)
	{
		FreeLibrary(m_hLibInstance);
		m_hLibInstance = NULL;
	}
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDllLoadMngr::CDllLoadMngr()
{
	
}

CDllLoadMngr::~CDllLoadMngr()
{
	
}

CDllLoadObj* CDllLoadMngr::AddLib(const CString &strDllPath)
{
	CString strPath;
	strPath = strDllPath;
	strPath.MakeLower();

	CDllLoadObj *pFind = (CDllLoadObj*)FindByID(strPath);

	if (pFind == NULL)
	{
		pFind = new CDllLoadObj();
		pFind->m_strID = strPath;
		AddNewChild(pFind);
		pFind->LoadDLL();
	}

	return pFind;
}

HINSTANCE CDllLoadMngr::FindLib(const CString &strDllPath)
{
	CString strPath;
	strPath = strDllPath;
	strPath.MakeLower();

	CDllLoadObj *pFind = (CDllLoadObj*)FindByID(strPath);

	if (pFind == NULL)
	{
		return NULL;
	}
	else
	{
		return pFind->GetLibInstance();
	}
}
