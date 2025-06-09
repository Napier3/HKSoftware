// RtGenShortDrawConfigs.cpp: implementation of the CRtGenShortDrawConfigs class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mr1200.h"
#include "RtGenShortDrawConfigs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

long CRtGenShortDrawConfigs::g_nRtGenShortDrawConfigsCount = 0;
CRtGenShortDrawConfigs* CRtGenShortDrawConfigs::g_pRtGenShortDrawConfigs = NULL;

CRtGenShortDrawConfigs* CRtGenShortDrawConfigs::CreateRtGenShortDrawConfigs()
{
	g_nRtGenShortDrawConfigsCount++;
	
	if (g_nRtGenShortDrawConfigsCount == 1)
	{		
		g_pRtGenShortDrawConfigs = new CRtGenShortDrawConfigs();
	}
	
	return g_pRtGenShortDrawConfigs;
}

long CRtGenShortDrawConfigs::Release()
{
	g_nRtGenShortDrawConfigsCount--;
	
	if (g_nRtGenShortDrawConfigsCount == 0)
	{
		delete g_pRtGenShortDrawConfigs;
		g_pRtGenShortDrawConfigs = NULL;
	}
	return 0;
}

CRtGenShortDrawConfigs::CRtGenShortDrawConfigs()
{

}

CRtGenShortDrawConfigs::~CRtGenShortDrawConfigs()
{

}

CExBaseObject* CRtGenShortDrawConfigs::CreateNewChild(long nClassID)
{
	CExBaseObject *pNew = NULL;
	
	if (nClassID == RTCLASSID_GENSHORTDRAWCONFIG)
	{
		pNew = new CRtGenShortDrawConfig();
	}
	
	return pNew;
}

void CRtGenShortDrawConfigs::InitDrawConfigs(CUIDraws *pDraws)
{
	CRtGenShortDrawConfig *pNew = NULL;
	CUIDraw *pDraw = NULL;
	void *pos = pDraws->GetHeadPosition();

	while (pos != NULL)
	{
		pDraw = (CUIDraw *)pDraws->GetNext(pos);

		if (pDraw != NULL)
		{
			pNew = (CRtGenShortDrawConfig *)CreateNewChild(RTCLASSID_GENSHORTDRAWCONFIG);
			
			if (pNew != NULL)
			{
				pNew->m_nDrawState = pDraw->m_nShow;
				pNew->m_strName  = pDraw->m_strName;
				pNew->
			}
		}
	}
}

