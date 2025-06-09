#include "stdafx.h"
#include "PxPkgBase.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif 

CPxPkgBase::CPxPkgBase()
{
	m_n64Time = 0;
	m_pBuffer = NULL;

	GetLocalTime(&m_tmPkg);
	m_nPkgState = PX_PKG_STATE_NOT_PROCESSED;
}

CPxPkgBase::~CPxPkgBase()
{

}