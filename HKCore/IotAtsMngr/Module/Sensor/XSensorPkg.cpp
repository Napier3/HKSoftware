#include "stdafx.h"
#include "XSensorPkg.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  


CXSensorPkg::CXSensorPkg()
{
	
}

CXSensorPkg::~CXSensorPkg()
{
	if (m_pSensorPkgInfo != NULL)
	{
		delete m_pSensorPkgInfo;
		m_pSensorPkgInfo = NULL;
	}
}