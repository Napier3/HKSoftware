#include "StdAfx.h"
#include "XPkgFullRcvJdgTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//
CXPkgFullRcvJdg_101::CXPkgFullRcvJdg_101()
{
	m_strName = _T("101");
	m_strID = m_strName;
}

CXPkgFullRcvJdg_101::~CXPkgFullRcvJdg_101()
{

}

long CXPkgFullRcvJdg_101::XPkgFullRcvJdg(BYTE *pBuffer, long nBufLen, long &nPkgLen)
{
	ASSERT (nBufLen > 0);

	if (pBuffer[0] == 0x10)
	{
		nPkgLen = 6;

		if (nBufLen >= 6 && pBuffer[5] == 0x16)
		{
			return 6;
		}
	}

	if (pBuffer[0] == 0x68 )
	{
		nPkgLen = pBuffer[1]+6;

		if (nBufLen > 4 && pBuffer[3] == 0x68)
		{
			if (nPkgLen <= nBufLen)
			{
				return nPkgLen;
			}
		}
	}

	return 0;
}


//////////////////////////////////////////////////////////////////////////
//
CXPkgFullRcvJdg_103::CXPkgFullRcvJdg_103()
{
	m_strName = _T("103");
	m_strID = m_strName;
}

CXPkgFullRcvJdg_103::~CXPkgFullRcvJdg_103()
{

}

long CXPkgFullRcvJdg_103::XPkgFullRcvJdg(BYTE *pBuffer, long nBufLen, long &nPkgLen)
{
	return FALSE;
}


//////////////////////////////////////////////////////////////////////////
//
CXPkgFullRcvJdg_104::CXPkgFullRcvJdg_104()
{
	m_strName = _T("104");
	m_strID = m_strName;
}

CXPkgFullRcvJdg_104::~CXPkgFullRcvJdg_104()
{

}

long CXPkgFullRcvJdg_104::XPkgFullRcvJdg(BYTE *pBuffer, long nBufLen, long &nPkgLen)
{
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
//

CXPkgFullRcvJdgTool *CXPkgFullRcvJdgTool::g_pXPkgFullRcvJdgTool = NULL;
long CXPkgFullRcvJdgTool::g_nXPkgFullRcvJdgToolRef = 0;


CXPkgFullRcvJdgTool::CXPkgFullRcvJdgTool()
{
	CXPkgFullRcvJdgInterface *pFind = NULL;

	pFind = new CXPkgFullRcvJdg_101();
	AddNewChild(pFind);

	pFind = new CXPkgFullRcvJdg_103();
	AddNewChild(pFind);

	pFind = new CXPkgFullRcvJdg_104();
	AddNewChild(pFind);
}

CXPkgFullRcvJdgTool::~CXPkgFullRcvJdgTool()
{
}

CXPkgFullRcvJdgTool* CXPkgFullRcvJdgTool::Create()
{
	g_nXPkgFullRcvJdgToolRef++;

	if (g_nXPkgFullRcvJdgToolRef == 1)
	{
		g_pXPkgFullRcvJdgTool = new CXPkgFullRcvJdgTool();
	}

	return g_pXPkgFullRcvJdgTool;
}

void CXPkgFullRcvJdgTool::Release()
{
	g_nXPkgFullRcvJdgToolRef--;

	if (g_nXPkgFullRcvJdgToolRef == 0)
	{
		delete g_pXPkgFullRcvJdgTool;
		g_pXPkgFullRcvJdgTool = NULL;
	}
}

CXPkgFullRcvJdgInterface* CXPkgFullRcvJdgTool::CreateXPkgFullRcvJdg(const CString &strID)
{
	CXPkgFullRcvJdgInterface *pFind = NULL;

	pFind = (CXPkgFullRcvJdgInterface *)g_pXPkgFullRcvJdgTool->FindByID(strID);

	return pFind;
}
