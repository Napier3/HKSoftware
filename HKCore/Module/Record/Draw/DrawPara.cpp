// DrawPara.cpp: implementation of the CDrawPara class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawPara.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawPara::CDrawPara()
{
	m_nParaID		= 0;
	m_pdValue		= NULL;
	m_pCalFuncPara	= NULL;
	m_pfCalFunc		= NULL;
	m_pfPara		= NULL;
	m_strUnit	    = "";
}

CDrawPara::~CDrawPara()
{
	m_nParaID		= 0;
	m_pdValue		= NULL;
	m_pCalFuncPara	= NULL;
	m_pfCalFunc		= NULL;
	m_pfPara		= NULL;
}

void CDrawPara::CalValue()
{
	if(m_pfCalFunc == NULL || m_pCalFuncPara == NULL)
		return;
	
	m_pfCalFunc(m_pCalFuncPara);
}

void CDrawPara::GetDrawRectSize(long& cx,long& cy)
{
	m_pfCalFunc(m_pCalFuncPara);
	CDC* pDC = m_pParentWnd->GetDC();
	CFont* pOldFont = pDC->SelectObject(m_pfPara);
	CString str ;
    str.Format("%.3f%s",*m_pdValue,m_strUnit.GetString());
	CSize szPara = pDC->GetTextExtent(str);
	pDC->SelectObject(pOldFont);
	pOldFont = NULL;
	m_pParentWnd->ReleaseDC(pDC);
	cy = szPara.cy;
	cx = szPara.cx;
}

void CDrawPara::Draw(CDC* pDC)
{
	CFont* pOldFont = pDC->SelectObject(m_pfPara);
	int nMode = pDC->SetBkMode(TRANSPARENT);
	CString str ;
	CRect rect = GetBorder();//m_rcBorder;
    str.Format("%.1f%s",*m_pdValue,m_strUnit.GetString());
	pDC->DrawText(str,rect,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	pDC->SelectObject(pOldFont);
	pDC->SetBkMode(nMode);
	pOldFont = NULL;
}

void CDrawPara::Init(UINT nParaID,const CString& strUnit,PRTATTRIBUTECALFUNCPARA pCalFuncPara,CFont* pFont)
{
	if(pCalFuncPara == NULL)
		return;

	if(pCalFuncPara->pRtChAttrVal == NULL)
		return;

	m_pfPara = pFont;
	m_pCalFuncPara = pCalFuncPara;
	m_nParaID = nParaID;
	PRTCHANNELATTRVALUE pCalPara = pCalFuncPara->pRtChAttrVal;
	
	switch(m_nParaID)
	{
	case Para_FreqValue:             
		{
			m_pfCalFunc = RT_CalFrequency;//计算频率的函数
			m_pdValue = &(pCalPara->dFrequency);
			m_strUnit = "Hz";
		}
		break;
	case Para_EffecValue:             
		{
			m_pfCalFunc = RT_CalEffecValue;
			m_pdValue = &(pCalPara->dEffecValue);
			m_strUnit = strUnit;
		}
		break;
	case Para_EffecPhase:             
		{
			m_pfCalFunc = RT_CalEffecValue;
			m_pdValue = &(pCalPara->dEffecPhase);
			m_strUnit = "°";
		}
		break;
	case Para_PeakValue:             
		{
			m_pfCalFunc = RT_CalPeakValue;
			m_strUnit = strUnit;
			m_pdValue = &(pCalPara->dPeakValue);
		}
		break;
	case Para_VellayValue:           
		{
			m_pfCalFunc = RT_CalVellayValue;
			m_strUnit = strUnit;
			m_pdValue = &(pCalPara->dVellayValue);
		}
		break;
	case Para_InstValue:              
		{
			m_pfCalFunc = RT_CalInstValue;
			m_strUnit = strUnit;
			m_pdValue = &(pCalPara->dInstValue);
		}
		break;
	case Para_AverageValue:        
		{
			m_pfCalFunc = RT_CalAverageValue;
			m_pdValue = &(pCalPara->dAverageValue);
			m_strUnit = strUnit;
		}
		break;
	case Para_Impedance:             
		{
			m_pfCalFunc = RT_CalImpedance    ;//计算阻抗的函数
			m_pdValue = &(pCalPara->dImpedance);
			m_strUnit = "Ω";
		}
		break;
	case Para_ActivePower:            
		{
			m_pfCalFunc = RT_CalActivePower;
			m_strUnit = "W";
			m_pdValue = &(pCalPara->dActivePower);
		}
		break;
	case Para_ReactivePower:            
		{
			m_pfCalFunc = RT_CalReactivePower;
			m_strUnit = "W";
			m_pdValue = &(pCalPara->dReactivePower);
		}
		break;
	case Para_ApparentPower:
		{
			m_pfCalFunc = RT_CalApparentPower;
			m_strUnit = "W";
			m_pdValue = &(pCalPara->dApparentPower);
		}
		break;
	case Para_PositiveSequence:
		{
			m_pfCalFunc = RT_CalPositiveSequence;
			m_strUnit = strUnit;
			m_pdValue = &(pCalPara->dPositiveSequence);
		}
		break;
	case Para_NegativeSequence:
		{
			m_pfCalFunc = RT_CalNegativeSequence;
			m_strUnit = strUnit;
			m_pdValue = &(pCalPara->dNegativeSequence);
		}
		break;
	case Para_ZeroSequence:
		{
			m_pfCalFunc = RT_CalZeroSequence;
			m_strUnit = strUnit;
			m_pdValue = &(pCalPara->dZeroSequence);
		}
		break;
	default:
		break;
	}
}
