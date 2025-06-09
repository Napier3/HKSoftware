// XObjectRefBase.cpp: implementation of the CXObjectRefBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XObjectRefBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CXObjectRefBase
CXObjectRefBase::CXObjectRefBase()
{
	m_nObjectRefCount = 0;
}

CXObjectRefBase::~CXObjectRefBase()
{

}

void CXObjectRefBase::AddRef()
{
	m_nObjectRefCount++;
}

void CXObjectRefBase::Release()
{
	m_nObjectRefCount--;
	
	if (m_nObjectRefCount == 0)
	{
		delete this;
	}
}

long CXObjectRefBase::GetRefCount()
{
	return m_nObjectRefCount;
}

//////////////////////////////////////////////////////////////////////////
//
CXObjectRefDriver::CXObjectRefDriver()
{
	m_lpXObject = NULL;
	m_bAutoRelease = TRUE;
	m_pFuncCreate = NULL;
}

CXObjectRefDriver::CXObjectRefDriver(P_FUNC_CREATE_XOBJECT *pFuncCreate)
{
	m_lpXObject = NULL;
	m_bAutoRelease = TRUE;
	m_pFuncCreate = pFuncCreate;
}

CXObjectRefDriver::CXObjectRefDriver(CXObjectRefBase* lpXObjec, BOOL bAutoRelease)
{
	m_lpXObject = lpXObjec;
	m_bAutoRelease = bAutoRelease;
	m_pFuncCreate = NULL;
}

CXObjectRefDriver::CXObjectRefDriver(const CXObjectRefDriver& oXobjRefSrc)
{
	ASSERT(this != &oXobjRefSrc);   // constructing from self?

	m_lpXObject = oXobjRefSrc.m_lpXObject;
	m_pFuncCreate = oXobjRefSrc.m_pFuncCreate;

	if (m_lpXObject != NULL)
		m_lpXObject->AddRef();

	m_bAutoRelease = TRUE;
}

void CXObjectRefDriver::AttachXObject(CXObjectRefBase* lpXObject, BOOL bAutoRelease)
{
	ReleaseXObject();  // detach previous
	m_lpXObject = lpXObject;
	m_bAutoRelease = bAutoRelease;
}

CXObjectRefBase* CXObjectRefDriver::DetachXObject()
{
	CXObjectRefBase* lpXObject = m_lpXObject;
	m_lpXObject = NULL;    // detach without Release
	return lpXObject;
}

// detach and get ownership of m_lpXObject
void CXObjectRefDriver::ReleaseXObject()
{
	if (m_lpXObject != NULL)
	{
		if (m_bAutoRelease)
			m_lpXObject->Release();

		m_lpXObject = NULL;
	}
}

// special operators
const CXObjectRefDriver& CXObjectRefDriver::operator=(const CXObjectRefDriver& oXobjRefSrc)
{
	if (this != &oXobjRefSrc)
	{
		CXObjectRefBase* lpTemp = m_lpXObject;
		m_lpXObject = oXobjRefSrc.m_lpXObject;

		if (m_lpXObject != NULL)
			m_lpXObject->AddRef();

		if (lpTemp != NULL && m_bAutoRelease)
			lpTemp->Release();

		m_bAutoRelease = TRUE;
	}

	return *this;
}

CXObjectRefDriver::~CXObjectRefDriver()
{
	ReleaseXObject();
}

CXObjectRefBase* CXObjectRefDriver::New()
{
	if (m_pFuncCreate == NULL)
	{
		ASSERT (FALSE);
		return NULL;
	}

	m_lpXObject = m_pFuncCreate();
	m_lpXObject->AddRef();

	return m_lpXObject;
}

void CXObjectRefDriver::AddRef()
{
	if (m_lpXObject != NULL)
	{
		m_lpXObject->AddRef();
	}
}

void CXObjectRefDriver::Release()
{
	if (m_lpXObject != NULL)
	{
		m_lpXObject->Release();
		m_lpXObject = NULL;
	}
}

//2022-10-19 lijunqing
CXObjectRefDriver* CXObjectRefDriver::Clone()
{
	CXObjectRefDriver *pNew = new CXObjectRefDriver();
	*pNew = *this;
	return pNew;
}

