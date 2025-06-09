// RtSingleVariable.cpp: implementation of the CRtSingleVariable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtSingleVariable.h"
#include "RtVariables.h"
#include "RecordTest.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// const char *CRtSingleVariable::g_pszKeySingleVariable		= "single-variable";
// const char *CRtSingleVariable::g_pszKeyDCAC					= "dc-ac";
// const char *CRtSingleVariable::g_pszKeyRange				= "range";
// const char *CRtSingleVariable::g_pszKeyPhaseID				= "ph-id";
// const char *CRtSingleVariable::g_pszKeyTranChIndex			= "tran-ch-index";
// const char *CRtSingleVariable::g_pszKeyEndFrequence			= "end-frequence";

CRtSingleVariable::CRtSingleVariable()
{
	m_dRange = 10;
	m_strPhaseID = "A";	
	m_nAttachedTranChannelIndex = 0;

	m_nEndFreqSet = END_FREQ_NONE;

	m_bRangeChanged = FALSE;
	m_pReserved = NULL;

	m_nRangeCoef = 1;
}

CRtSingleVariable::~CRtSingleVariable()
{
}

long CRtSingleVariable::RTUpdateOwnByAutofit(HDINFO &oHDInfo)
{
	CString strTemp;
	long nUITran = 0;
	int nTemp = 0;

	if (!oHDInfo.bDCTran)
	{
		if (IsVariableType_U())
		{
			nUITran = oHDInfo.nVoltageTranindex;
		}
		else if (IsVariableType_I())
		{
			nUITran = oHDInfo.nCurrentTranindex;
		}
		else
		{
		}
		
		//ID
		strTemp.Format(m_strID, nUITran, oHDInfo.nTranChIndex + 1);
		m_strID = strTemp;
		
		//Name
		strTemp.Format(m_strName, nUITran, oHDInfo.nTranChIndex + 1);
		m_strName = strTemp;
		
		//RecordBufferID
		strTemp.Format(m_strRecordBufferID, nUITran, oHDInfo.nTranChIndex + 1);
		m_strRecordBufferID = strTemp;
		
		//SpyBufferID
		strTemp.Format(m_strSpyBufferID, nUITran, oHDInfo.nTranChIndex + 1);
		m_strSpyBufferID = strTemp;
	}
	else
	{
		//ID
		strTemp.Format(m_strID, oHDInfo.nDCUIChIndexInTran);
		m_strID = strTemp;
		
		//Name
		strTemp.Format(m_strName, oHDInfo.nDCUIChIndexInTran);
		m_strName = strTemp;
		
		//RecordBufferID
		strTemp.Format(m_strRecordBufferID, oHDInfo.nDCUIChIndexInTran);
		m_strRecordBufferID = strTemp;
		
		//SpyBufferID
		strTemp.Format(m_strSpyBufferID, oHDInfo.nDCUIChIndexInTran);
		m_strSpyBufferID = strTemp;

	}


	//ACDC
	m_strDCAC = oHDInfo.m_strDCAC;
	
	//Max Range
	SetRange(oHDInfo.m_dRange);
// 	m_dRange = oHDInfo.m_dRange;
// 	AdjustRangeAndUint(m_dRange);

 	//HD Index
	m_nAttachedTranChannelIndex = oHDInfo.nTranFirstChannelHdIndex + oHDInfo.nTranChIndex;

	//TranModel
	m_strTranModel = oHDInfo.strTranModel;

	//Variable-use
	m_nVariableUse = 1;

	if (oHDInfo.nTranAnologChCount == 4)
	{
		nTemp = oHDInfo.nTranChIndex % 4;
	}
	else
	{
		nTemp = oHDInfo.nTranChIndex % 3;
	}

	//相别
	m_strPhaseID = g_pszVariablePhaseID[nTemp];

	//通道颜色
	switch (nTemp)
	{
	case 0:
		m_crColor = RGB(255, 255, 0);
		break;
	case 1:
		m_crColor = RGB(0, 255, 0);
		break;
	case 2:
		m_crColor = RGB(255, 0, 0);
		break;
	case 3:
		m_crColor = RGB(0, 0, 255);
		break;
	default:
		break;
	}

	//改变oHDInfo.nTranIndex = oHDInfo.nVoltageTranindex或oHDInfo.nCurrentTranindex，
	//以此来更新属性、定值、脚本的名称等属性，避免在属性、定值中再判断是电压变换器还是电流变换器
	oHDInfo.nTranIndex = nUITran;
	return 0;
}

CMemBuffer_Float *CRtSingleVariable::GetEffcAttrBuffer()
{
 	CMemBuffer_Float* pFind = NULL;
	CRtDataAttribute *pAttr = NULL;
	
	pAttr = m_pDataAttrs->FindByAttrID(g_pszChannelKeyAttrID[SingleVariableAttrID_EffecValue]);
		
	if (pAttr != NULL)
	{
		if (pAttr->m_pAttrBuffer != NULL)
		{
			pFind = pAttr->m_pAttrBuffer;
		}
	}

	return pFind;
}

void CRtSingleVariable::AdjustRangeAndUint(double &dRange)
{	
	if (m_pDataAttrs == NULL)
	{
		return;
	}

	CRtDataAttribute *pAttr = NULL;
	//改变有效值单位
	pAttr = (CRtDataAttribute *)m_pDataAttrs->FindByAttrID(g_pszChannelKeyAttrID[SingleVariableAttrID_EffecValue]);
	if (pAttr != NULL)
	{
		pAttr->ChangeToUnit();
	}

	//基波有效值单位
	pAttr = (CRtDataAttribute *)m_pDataAttrs->FindByAttrID(g_pszChannelKeyAttrID[SingleVariableAttrID_FundValue]);

	if (pAttr != NULL)
	{
		pAttr->ChangeToUnit();
	}

	//峰值、谷值、瞬时值、均值、各次谐波有效值
	for (int nIndex = SingleVariableAttrID_PeakValue; nIndex <= SingleVariableAttrID_Harm25Value; nIndex++)
	{
		pAttr = (CRtDataAttribute *)m_pDataAttrs->FindByAttrID(g_pszChannelKeyAttrID[nIndex]);
		
		if (pAttr != NULL)
		{
			pAttr->ChangeToUnit();
		}
	}
	
	if (dRange < 1)
	{
		pAttr = (CRtDataAttribute *)m_pDataAttrs->FindByAttrID(g_pszChannelKeyAttrID[SingleVariableAttrID_EffecValue]);
		char ch = pAttr->m_strUnit.GetAt(0);

		//if (_stricmp(pAttr->m_strUnit.Left(1), "m") != 0)
		if (ch != 'm' && ch != 'M')
		{			
			//改变有效值单位
			pAttr->ChangeToMilliUnit();
		
			//基波有效值单位
			pAttr = (CRtDataAttribute *)m_pDataAttrs->FindByAttrID(g_pszChannelKeyAttrID[SingleVariableAttrID_FundValue]);
			
			if (pAttr != NULL)
			{
					pAttr->ChangeToMilliUnit();
			}
		
			//峰值、谷值、瞬时值、均值、各次谐波有效值
			for (int nIndex = SingleVariableAttrID_PeakValue; nIndex <= SingleVariableAttrID_Harm25Value; nIndex++)
			{
				pAttr = (CRtDataAttribute *)m_pDataAttrs->FindByAttrID(g_pszChannelKeyAttrID[nIndex]);
				
				if (pAttr != NULL)
				{
						pAttr->ChangeToMilliUnit();
					}
				}
				}
			}
		else
		{
	// 		//改变有效值单位
	// 		pAttr->ChangeToUnit();
	// 		
	// 		//基波有效值单位
	// 		pAttr = (CRtDataAttribute *)m_pDataAttrs->FindByAttrID(g_pszChannelKeyAttrID[SingleVariableAttrID_FundValue]);
	// 		
	// 		if (pAttr != NULL)
	// 		{
	// 			pAttr->ChangeToUnit();
	// 		}
	// 		
	// 		//峰值、谷值、瞬时值、均值、各次谐波有效值
	// 		for (int nIndex = SingleVariableAttrID_PeakValue; nIndex <= SingleVariableAttrID_Harm25Value; nIndex++)
	// 		{
	// 			pAttr = (CRtDataAttribute *)m_pDataAttrs->FindByAttrID(g_pszChannelKeyAttrID[nIndex]);
	// 			
	// 			if (pAttr != NULL)
	// 			{
	// 				pAttr->ChangeToUnit();
	// 			}
	// 		}
		}
}

CString CRtSingleVariable::GetUnitString()
{
	CString strUnit = "";
	ASSERT(m_pDataAttrs != NULL);	
	CRtDataAttribute *pData = m_pDataAttrs->FindByAttrID(g_pszChannelKeyAttrID[SingleVariableAttrID_EffecValue]);

	if(pData != NULL)
	{
		strUnit = pData->m_strUnit;
	}

	return strUnit;
}

void CRtSingleVariable::CreateStaticAttrs(const CString &strName)
{
	if (m_pDataAttrs != NULL)
	{
		m_pDataAttrs->DeleteAll();
	}
	else
	{
		m_pDataAttrs = new CRtDataAttributes();
		AddNewChild(m_pDataAttrs);
	}

	CRtDataAttribute* pAttr = NULL;
	m_pDataAttrs->m_nStaticAttrs = 5;
	CString strID;

	for(long i = 0; i< MAX_CHANNEL_ATTRID_KEYS; i++)//2017-11-25修改
	{
		CreateAttrByID(strID, strName, i);
	}
}

CRtDataAttribute* CRtSingleVariable::CreateAttrByID(const CString& strID,const CString& strVarName, long nIndex)
{
	CRtDataAttribute* pAttr = new CRtDataAttribute();
	pAttr->m_strID = strID;
	pAttr->SetUse(0);
	pAttr->SetSpyState(0);
    pAttr->m_strName.Format("%s%s",strVarName.GetString(),strID.GetString());

	pAttr->m_strID = g_pszChannelKeyAttrID[nIndex];

#ifdef RCD_CMP_USE_EffecValue
	if (nIndex == SingleVariableAttrID_EffecValue  
		|| nIndex == SingleVariableAttrID_DeltaEffecValue)
#else
	if (nIndex == SingleVariableAttrID_Frequancy 
		|| nIndex == SingleVariableAttrID_FundValue 
		|| nIndex == SingleVariableAttrID_DeltaFundValue
		)
#endif
	{
		pAttr->SetUse(1);
	}

	m_pDataAttrs->SetAttr(pAttr, nIndex);
	m_pDataAttrs->AddNewChild(pAttr);

	return pAttr;
}

CString CRtSingleVariable::CmbVariableID()
{
	CString strVarID;

	if (m_strUnit.Find(_T("V")) >= 0)
	{
		strVarID = _T("U");
	}
	else
	{
		strVarID = _T("I");
	}

	CString strPhase = m_strPhaseID;
	strPhase.MakeLower();
	strVarID += strPhase;
	
	return strVarID;
}

