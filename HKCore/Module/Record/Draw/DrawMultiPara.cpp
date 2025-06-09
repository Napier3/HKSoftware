// DrawMultiPara.cpp: implementation of the CDrawMultiPara class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawMultiPara.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawMultiPara::CDrawMultiPara()
{
	m_pdValue2 = NULL;
	m_strUnit2 = "";
}

CDrawMultiPara::~CDrawMultiPara()
{
	m_pdValue2		= NULL;
	m_pdValue		= NULL;
	m_pCalFuncPara	= NULL;
	m_pfCalFunc		= NULL;
	m_pfPara		= NULL;
}

void CDrawMultiPara::Draw(CDC* pDC)
{

	CFont* pOldFont = pDC->SelectObject(m_pfPara);
	CPen Pen(PS_SOLID,1,m_crForeColor);
	CPen* pOldPen = pDC->SelectObject(&Pen);
	CString strPara,strPara2;
	
	//第一个参数
	if (m_pdValue != NULL)
	{
        strPara.Format("%.3f%s",*m_pdValue,m_strUnit.GetString());
	}
	else
	{
        strPara.Format("#%s", m_strUnit.GetString());
	}

	CSize szPara = pDC->GetTextExtent(strPara);	
	long nTop = m_ptTopLeft.y;//m_rcBorder.top ;
	long nLeft = m_ptTopLeft.x;//m_rcBorder.left;
	long nBom = nTop + szPara.cy;

	pDC->TextOut(nLeft, nTop, strPara);
	nLeft += szPara.cx;
	pDC->MoveTo(nLeft, nBom);
	pDC->LineTo(nLeft + szPara.cy , nTop );

	//第二个参数
	if (m_pdValue2 != NULL)
	{
        strPara2.Format("%.3f%s",*m_pdValue2,m_strUnit2.GetString());
	}
	else
	{
        strPara2.Format("#%s", m_strUnit2.GetString());
	}

	CSize szPara2 = pDC->GetTextExtent(strPara2);
	pDC->TextOut(nLeft + szPara.cy , nTop, strPara2);
	pDC->MoveTo(nLeft, nBom);
	pDC->LineTo(nLeft + szPara.cy + szPara2.cx , nBom);

	pDC->SelectObject(pOldFont);
	pDC->SelectObject(pOldPen);
	pOldPen  = NULL;
	pOldFont = NULL;
	Pen.DeleteObject();
}

void CDrawMultiPara::GetDrawRectSize(long& cx,long& cy)
{
	if (m_pfCalFunc == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("m_pfCalFunc == NULL"));
		return;
	}

	m_pfCalFunc(m_pCalFuncPara);
	CDC* pDC = m_pParentWnd->GetDC();
	CFont* pOldFont = pDC->SelectObject(m_pfPara);
	CString strPara,strPara2;

	//第一个参数
    strPara.Format("%.3f%s",*m_pdValue,m_strUnit.GetString());
	CSize szPara = pDC->GetTextExtent(strPara);	
	cy = szPara.cy + 2;
	cx = szPara.cx;
	
	//第二个参数
    strPara2.Format("%.3f%s",*m_pdValue2,m_strUnit2.GetString());
	CSize szPara2 = pDC->GetTextExtent(strPara2);
	cx += szPara2.cx;
	cx += cy;
	pDC->SelectObject(pOldFont);
	pOldFont = NULL;
	m_pParentWnd->ReleaseDC(pDC);
}

void CDrawMultiPara::Init(UINT nParaID,const CString& strUnit,PRTATTRIBUTECALFUNCPARA pCalFuncPara,CFont* pFont)
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
	case Para_FundValue:             
		{
			m_pfCalFunc = RT_CalFundValue;
			m_pdValue = &(pCalPara->dFundValue);
			m_pdValue2 = &(pCalPara->dFundPhase);
			m_strUnit = strUnit;
			m_strUnit2 = "°";
		}
		break;
	case Para_HarmValue2:        
		{
			m_pfCalFunc = RT_CalHarm02Value;
			m_strUnit = strUnit;
			m_strUnit2 = "°";
			m_pdValue = &(pCalPara->dHarmValue[0]);
			m_pdValue2 = &(pCalPara->dHarmPhase[0]);
		}
		break;
	case Para_HarmValue3:
        {
			m_strUnit = strUnit;
			m_strUnit2 = "°";
			m_pfCalFunc = RT_CalHarm03Value;
			m_pdValue = &(pCalPara->dHarmValue[1]);
			m_pdValue2 = &(pCalPara->dHarmPhase[1]);
		}	
		break;
	case Para_HarmValue4:        
		{
			m_strUnit = strUnit;
			m_strUnit2 = "°";
			m_pfCalFunc = RT_CalHarm04Value;
			m_pdValue = &(pCalPara->dHarmValue[2]);
			m_pdValue2 = &(pCalPara->dHarmPhase[2]);
		}
		break;
	case Para_HarmValue5:       
		{
			m_strUnit = strUnit;
			m_strUnit2 = "°";
			m_pfCalFunc = RT_CalHarm05Value;
			m_pdValue = &(pCalPara->dHarmValue[3]);
			m_pdValue2 = &(pCalPara->dHarmPhase[3]);
		}
		break;
	case Para_HarmValue6:       
		{
			m_strUnit = strUnit;
			m_strUnit2 = "°";
			m_pfCalFunc = RT_CalHarm06Value;
			m_pdValue = &(pCalPara->dHarmValue[4]);
			m_pdValue2 = &(pCalPara->dHarmPhase[4]);
		}
		break;
	case Para_HarmValue7:  			
		{
			m_strUnit = strUnit;
			m_strUnit2 = "°";      
			m_pfCalFunc = RT_CalHarm07Value;
			m_pdValue = &(pCalPara->dHarmValue[5]);
			m_pdValue2 = &(pCalPara->dHarmPhase[5]);
		}
		break;
	case Para_HarmValue8:        
		{
			m_pfCalFunc = RT_CalHarm08Value;
			m_strUnit = strUnit;
			m_strUnit2 = "°";
			m_pdValue = &(pCalPara->dHarmValue[6]);
			m_pdValue2 = &(pCalPara->dHarmPhase[6]);
		}
		break;
	case Para_HarmValue9:        
		{
			m_pfCalFunc = RT_CalHarm09Value;
			m_strUnit = strUnit;
			m_strUnit2 = "°";
			m_pdValue = &(pCalPara->dHarmValue[7]);
			m_pdValue2 = &(pCalPara->dHarmPhase[7]);
		}
		break;
	case Para_HarmValue10:        
		{
			m_pfCalFunc = RT_CalHarm10Value;
			m_strUnit = strUnit;
			m_strUnit2 = "°";
			m_pdValue = &(pCalPara->dHarmValue[8]);
			m_pdValue2 = &(pCalPara->dHarmPhase[8]);
		}
		break;
	case Para_HarmValue11:        
		{
			m_pfCalFunc = RT_CalHarm11Value;
			m_strUnit = strUnit;
			m_strUnit2 = "°";
			m_pdValue = &(pCalPara->dHarmValue[9]);
			m_pdValue2 = &(pCalPara->dHarmPhase[9]);
		}
		break;
	case Para_HarmValue12:        
		{
			m_pfCalFunc = RT_CalHarm12Value;
			m_strUnit = strUnit;
			m_strUnit2 = "°";
			m_pdValue = &(pCalPara->dHarmValue[10]);
			m_pdValue2 = &(pCalPara->dHarmPhase[10]);
		}
		break;
	case Para_HarmValue13:        
		{
			m_pfCalFunc = RT_CalHarm13Value;
			m_strUnit = strUnit;
			m_strUnit2 = "°";
			m_pdValue = &(pCalPara->dHarmValue[11]);
			m_pdValue2 = &(pCalPara->dHarmPhase[11]);
		}
		break;
	case Para_HarmValue14:        
		{
			m_pfCalFunc = RT_CalHarm14Value;
			m_strUnit = strUnit;
			m_strUnit2 = "°";
			m_pdValue = &(pCalPara->dHarmValue[12]);
			m_pdValue2 = &(pCalPara->dHarmPhase[12]);
		}
		break;
	case Para_HarmValue15:        
		{
			m_pfCalFunc = RT_CalHarm15Value;
			m_strUnit = strUnit;
			m_strUnit2 = "°";
			m_pdValue = &(pCalPara->dHarmValue[13]);
			m_pdValue2 = &(pCalPara->dHarmPhase[13]);
		}
		break;
	case Para_HarmValue16:        
		{
			m_pfCalFunc = RT_CalHarm16Value;
			m_strUnit = strUnit;
			m_strUnit2 = "°";
			m_pdValue = &(pCalPara->dHarmValue[14]);
			m_pdValue2 = &(pCalPara->dHarmPhase[14]);
		}
		break;
	case Para_HarmValue17:        
		{
			m_pfCalFunc = RT_CalHarm17Value;
			m_strUnit = strUnit;
			m_strUnit2 = "°";
			m_pdValue = &(pCalPara->dHarmValue[15]);
			m_pdValue2 = &(pCalPara->dHarmPhase[15]);
		}
		break;
	case Para_HarmValue18:        
		{
			m_pfCalFunc = RT_CalHarm18Value;
			m_strUnit = strUnit;
			m_strUnit2 = "°";
			m_pdValue = &(pCalPara->dHarmValue[16]);
			m_pdValue2 = &(pCalPara->dHarmPhase[16]);
		}
		break;
	case Para_HarmValue19:        
		{
			m_pfCalFunc = RT_CalHarm19Value;
			m_strUnit = strUnit;
			m_strUnit2 = "°";
			m_pdValue = &(pCalPara->dHarmValue[17]);
			m_pdValue2 = &(pCalPara->dHarmPhase[17]);
		}
		break;
	case Para_HarmValue20:        
		{
			m_pfCalFunc = RT_CalHarm20Value;
			m_strUnit = strUnit;
			m_strUnit2 = "°";
			m_pdValue = &(pCalPara->dHarmValue[18]);
			m_pdValue2 = &(pCalPara->dHarmPhase[18]);
		}
		break;
	case Para_HarmValue21:        
		{
			m_pfCalFunc = RT_CalHarm21Value;
			m_strUnit = strUnit;
			m_strUnit2 = "°";
			m_pdValue = &(pCalPara->dHarmValue[19]);
			m_pdValue2 = &(pCalPara->dHarmPhase[19]);
		}
		break;
	case Para_HarmValue22:        
		{
			m_pfCalFunc = RT_CalHarm22Value;
			m_strUnit = strUnit;
			m_strUnit2 = "°";
			m_pdValue = &(pCalPara->dHarmValue[20]);
			m_pdValue2 = &(pCalPara->dHarmPhase[20]);
		}
		break;
	case Para_HarmValue23:       
		{
			m_pfCalFunc = RT_CalHarm23Value;
			m_strUnit = strUnit;
			m_strUnit2 = "°";
			m_pdValue = &(pCalPara->dHarmValue[21]);
			m_pdValue2 = &(pCalPara->dHarmPhase[21]);
		}
		break;
	case Para_HarmValue24:        
		{
			m_pfCalFunc = RT_CalHarm24Value;
			m_strUnit = strUnit;
			m_strUnit2 = "°";
			m_pdValue = &(pCalPara->dHarmValue[22]);
			m_pdValue2 = &(pCalPara->dHarmPhase[22]);
		}
		break;
	case Para_HarmValue25:        
		{
			m_pfCalFunc = RT_CalHarm25Value;
			m_strUnit = strUnit;
			m_strUnit2 = "°";
			m_pdValue = &(pCalPara->dHarmValue[23]);
			m_pdValue2 = &(pCalPara->dHarmPhase[23]);
		}
		break;
	default:
		break;
	}
}
