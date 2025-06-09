// RtAttrSpyConfigs.cpp: implementation of the CRtAttrSpyConfigs class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtAttrSpyConfigs.h"
#include "../MR1200BaseApp.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
long CRtAttrSpyConfigs::g_nRtAttrSpyConfigsCount = 0;
CRtAttrSpyConfigs* CRtAttrSpyConfigs::g_pRtAttrSpyConfigs = NULL;

CRtAttrSpyConfigs* CRtAttrSpyConfigs::CreategRtAttrSpyConfigs()
{
	g_nRtAttrSpyConfigsCount++;
	
	if (g_nRtAttrSpyConfigsCount == 1)
	{		
		g_pRtAttrSpyConfigs = new CRtAttrSpyConfigs();
	}
	
	return g_pRtAttrSpyConfigs;
}

long CRtAttrSpyConfigs::Release()
{
	g_nRtAttrSpyConfigsCount--;
	
	if (g_nRtAttrSpyConfigsCount == 0)
	{
		delete g_pRtAttrSpyConfigs;
		g_pRtAttrSpyConfigs = NULL;
	}
	return 0;
}

CRtAttrSpyConfigs::CRtAttrSpyConfigs()
{
	InitAttrSpyConfigs();	
	m_nVariableSpyGridMaxColums = 0;
}

CRtAttrSpyConfigs::~CRtAttrSpyConfigs()
{
	
}

CExBaseObject* CRtAttrSpyConfigs::CreateNewChild(long nClassID)
{
	CExBaseObject *pNew = NULL;

	if (nClassID == RTCLASSID_ATTRSPYCONFIG)
	{
		pNew = new CRtAttrSpyConfig();
	}

	return pNew;
}

void CRtAttrSpyConfigs::InitAttrSpyConfigs()
{
	CRtAttrSpyConfig *pNew = NULL;

	//关联	"频率"
	pNew = (CRtAttrSpyConfig *)CreateNewChild(RTCLASSID_ATTRSPYCONFIG);
	if (pNew != NULL)
	{
		strcpy(pNew->m_oAttrFreq.strAttrID, g_pszChannelKeyAttrID[0]);
		strcpy(pNew->m_oAttrFreq.strAttrName, pNew->m_oAttrFreq.strAttrID);//GetLanguageStringByID(gs_strLanguage_AttrName[0])); //ldh modify 2010.06.15
		pNew->m_oAttrFreq.nAttributeID	= 0;
		pNew->m_oAttrFreq.nSpyState = 0;
		pNew->m_oAttrFreq.nAttrType = AttrType_Freq;
		pNew->m_oAttrFreq.pParent = pNew;
		pNew->SetParent(this);
		AddNode(pNew);
	}

	
	//关联"真有效值","相位","基波有效值","基波相位",
	int nIndex = 0;

	for(nIndex = 1; nIndex < 5; nIndex += 2)
	{
		pNew = (CRtAttrSpyConfig *)CreateNewChild(RTCLASSID_ATTRSPYCONFIG);
		
		if (pNew != NULL)
		{
			//有效值
			strcpy(pNew->m_oAttrEffec.strAttrID, g_pszChannelKeyAttrID[nIndex]);
			strcpy(pNew->m_oAttrEffec.strAttrName, pNew->m_oAttrEffec.strAttrID);//GetLanguageStringByID(gs_strLanguage_AttrName[nIndex]));
			pNew->m_oAttrEffec.nAttributeID = nIndex;
			pNew->m_oAttrEffec.nSpyState	= 0;
			pNew->m_oAttrEffec.nAttrType    = AttrType_Effec;
			pNew->m_oAttrEffec.pParent		= pNew;

			//相位
			strcpy(pNew->m_oAttrPhase.strAttrID, g_pszChannelKeyAttrID[nIndex + 1]);
			strcpy(pNew->m_oAttrPhase.strAttrName, pNew->m_oAttrPhase.strAttrID);//GetLanguageStringByID(gs_strLanguage_AttrName[nIndex + 1]));
			pNew->m_oAttrPhase.nAttributeID	= nIndex + 1;
			pNew->m_oAttrPhase.nSpyState		= 0;
			pNew->m_oAttrPhase.nAttrType     = AttrType_Phase;
			pNew->m_oAttrPhase.pParent		= pNew;

			pNew->SetParent(this);
			AddNode(pNew);
		}
	}

	//关联谐波
	for(nIndex = 9; nIndex < 33; nIndex ++)
	{
		pNew = (CRtAttrSpyConfig *)CreateNewChild(RTCLASSID_ATTRSPYCONFIG);

		if (pNew != NULL)
		{
			//有效值
			strcpy(pNew->m_oAttrEffec.strAttrID, g_pszChannelKeyAttrID[nIndex]);
			strcpy(pNew->m_oAttrEffec.strAttrName, pNew->m_oAttrEffec.strAttrID);;//GetLanguageStringByID(gs_strLanguage_AttrName[nIndex]));
			pNew->m_oAttrEffec.nAttributeID = nIndex;
			pNew->m_oAttrEffec.nSpyState	= 0;
			pNew->m_oAttrEffec.nAttrType    = AttrType_Effec;
			pNew->m_oAttrEffec.pParent		= pNew;

			//相位
			strcpy(pNew->m_oAttrPhase.strAttrID, g_pszChannelKeyAttrID[nIndex + 24]);
			strcpy(pNew->m_oAttrPhase.strAttrName, pNew->m_oAttrPhase.strAttrID);//GetLanguageStringByID(gs_strLanguage_AttrName[nIndex + 24]));
			pNew->m_oAttrPhase.nAttributeID	= nIndex + 1;
			pNew->m_oAttrPhase.nSpyState		= 0;
			pNew->m_oAttrPhase.nAttrType     = AttrType_Phase;
			pNew->m_oAttrPhase.pParent		= pNew;

			pNew->SetParent(this);
			AddNode(pNew);
		}
	}
}

long CRtAttrSpyConfigs::GetCurrSpyAttrCount()
{
	CRtAttrSpyConfig *pSpyConfig = NULL;
	long nCount = GetCount();
	long nSpyCount = 0;

	for(long nIndex = 0; nIndex < nCount; nIndex++)
	{
		pSpyConfig = (CRtAttrSpyConfig *)GetAt(nIndex);

		if (pSpyConfig->IsAttrFrequency())
		{
			if (pSpyConfig->m_oAttrFreq.nSpyState == 1)
			{
				nSpyCount++;
			}
		}
		else
		{
			if (pSpyConfig->m_oAttrEffec.nSpyState == 1)
			{
				nSpyCount++;
			}
			else
			{
			}
						
			if (pSpyConfig->m_oAttrPhase.nSpyState == 1)
			{
				nSpyCount++;
			}
			else
			{
			}

		}
	}

	return nSpyCount;
}


BOOL CRtAttrSpyConfigs::CanChangeAttrSpyCount()
{
	BOOL bTrue = FALSE;
	long nSpyCount = GetCurrSpyAttrCount();

	if (nSpyCount < m_nVariableSpyGridMaxColums)
	{
		bTrue = TRUE;
	}

	return bTrue;
}

BOOL CRtAttrSpyConfigs::CanAddHarmAttrSpy()
{
	BOOL bTrue = FALSE;
	
	long nHarmSpyCount = 0;
	CRtAttrSpyConfig *pConfig = NULL;
	POS pos  = GetHeadPosition();

	while (pos != NULL)
	{
		pConfig = (CRtAttrSpyConfig *)GetNext(pos);
		ASSERT(pConfig != NULL);

		if (pConfig->IsAttrHarm() && (pConfig->m_nSpyState == 1))
		{
			nHarmSpyCount++;
		}
	}

	
	long nVariableCount = g_pCurrRecordTest->m_pVariables->GetCount();

	if (nHarmSpyCount < Max_Harm_CalCount * nVariableCount)
	{
		bTrue = TRUE;
	}

	return bTrue;
}

CRtAttrSpyConfig *CRtAttrSpyConfigs::FindByAttrID(CString strAttrID)
{
	CRtAttrSpyConfig *pFind = NULL;
	CRtAttrSpyConfig *pConfig = NULL;
	POS pos  = GetHeadPosition();

	while (pos != NULL)
	{
		pConfig = (CRtAttrSpyConfig *)GetNext(pos);
		ASSERT(pConfig != NULL);

		if (strAttrID == pConfig->m_oAttrFreq.strAttrID 
			|| strAttrID == pConfig->m_oAttrEffec.strAttrID
			|| strAttrID == pConfig->m_oAttrPhase.strAttrID)
		{
			pFind = pConfig;
			break;
		}
	}

	return pFind;
}

















