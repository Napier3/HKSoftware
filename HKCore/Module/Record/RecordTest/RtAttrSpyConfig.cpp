// RtAttrSpyConfig.cpp: implementation of the CRtAttrSpyConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtAttrSpyConfig.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRtAttrSpyConfig::CRtAttrSpyConfig()
{
	m_nSpyState	= 0;
	memset(&m_oAttrFreq, 0, sizeof(RTATTRSPY));
	memset(&m_oAttrEffec, 0, sizeof(RTATTRSPY));
	memset(&m_oAttrPhase, 0, sizeof(RTATTRSPY));
}

CRtAttrSpyConfig::~CRtAttrSpyConfig()
{

}

BOOL CRtAttrSpyConfig::IsAttrHarm()
{
	BOOL bTrue = FALSE;
	CString strEffecAttrName = m_oAttrEffec.strAttrID;
	CString strEffecPhaseName = m_oAttrPhase.strAttrID;

	if ((_stricmp(strEffecAttrName.Left(4).GetString(), "Harm") == 0) || (_stricmp(strEffecPhaseName.Left(4).GetString(), "Harm") == 0))
	{
		bTrue = TRUE;
	}

	return bTrue;
}

BOOL CRtAttrSpyConfig::IsAttrFrequency()
{
	BOOL bTrue = FALSE;
	
	if (_stricmp(m_oAttrFreq.strAttrID, g_pszChannelKeyAttrID[0]) == 0) 
	{
		bTrue = TRUE;
	}
	
	return bTrue;
}

BOOL CRtAttrSpyConfig::IsAttrSpyEffec(CString strAttrID)
{
	BOOL bTrue = FALSE;
	CString str;
	str = strAttrID.Right(5);

	if (_stricmp(str.GetString(), "Value") == 0)
	{
		bTrue = TRUE;
	}

	return bTrue;
}

BOOL CRtAttrSpyConfig::IsAttrSpyPhase(CString strAttrID)
{
	BOOL bTrue = FALSE;
	CString str;
	str = strAttrID.Right(5);
	
	if (_stricmp(str.GetString(), "Phase") == 0)
	{
		bTrue = TRUE;
	}
	
	return bTrue;
}