// ShareMemBuffer_CPoint.cpp: implementation of the CShareMemBuffer_CPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ShareMemBuffer_CPoint.h"
#include "../../api/GlobalConfigApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShareMemBuffer_CPoint::CShareMemBuffer_CPoint()
{
	m_nBufferLength = 0;
	m_pBuffer       = NULL;
	m_pBufferX      = NULL;
	m_pBufferY		= NULL;
	m_nCurrUseLength  = 0;
	m_dCoefY	      = 0;
	m_dOffSetY		  = 0;
	m_dCoefX	      = 0;
	m_dOffSetX		  = 0;
	m_pMemServer      = NULL;
}

CShareMemBuffer_CPoint::~CShareMemBuffer_CPoint()
{
	DettachBuffer();

	FreeBuffer();
}

void CShareMemBuffer_CPoint::CreateShareMemBufferCPoint(LPCTSTR pszMapName, long nPointSize)
{
	FreeBuffer();

	m_nBufferLength = nPointSize;
	long nMapSize = nPointSize * (sizeof(CPoint));

	char pszPath[MAX_PATH];
    sprintf(pszPath, "%s%s.mrsm", _P_GetBinPath(), pszMapName);
	m_pMemServer = new CShareMemServerEx(pszPath, pszMapName, nMapSize);

	if (m_pMemServer->IsValid())
	{
		m_pBuffer = (CPoint*)m_pMemServer->GetBuffer();
	}
}

void CShareMemBuffer_CPoint::FreeBuffer()
{
	if (m_pMemServer != NULL)
	{
		delete m_pMemServer;
		m_pMemServer = NULL;
	}

	m_pBuffer = NULL;
	m_nBufferLength = 0;
	m_nCurrUseLength = 0;

	m_dCoefY	      = 0;
	m_dOffSetY		  = 0;
	m_dCoefX	      = 0;
	m_dOffSetX		  = 0;
}
