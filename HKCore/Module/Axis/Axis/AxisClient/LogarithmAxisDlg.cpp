// LogarithmAxisDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AxisClient.h"
#include "LogarithmAxisDlg.h"
#include "..\..\..\Module\Api\GloblaDrawFunctions.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogarithmAxisDlg dialog


CLogarithmAxisDlg::CLogarithmAxisDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLogarithmAxisDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLogarithmAxisDlg)
	m_bAxisBorder = TRUE;
	m_bAxisCenter = TRUE;
	m_bWorkArea = TRUE;
	m_bXAxisLine = TRUE;
	m_bXHalfScale = TRUE;
	m_bXScaleText = TRUE;
	m_bXTenthScale = TRUE;
	m_bYAxisLine = TRUE;
	m_bYHalfScale = TRUE;
	m_bYScaleText = TRUE;
	m_bYTenthScale = TRUE;
	//}}AFX_DATA_INIT
}

void CLogarithmAxisDlg::InitLogarithmAxis()
{
	if (!CreateLogarithmAxisInterface(&m_ILogarithmAxis))
	{
		MessageBox("create IAxis failed!");
		return;
	}

	m_ILogarithmAxis->SetAxisDrawStyle(LOGARITHMAXISDRAW_ALL);
	
	m_stcFrame.GetWindowRect(&m_rectAxis);
	ScreenToClient(&m_rectAxis);

	m_ILogarithmAxis->SetXAxisGridLineStyle(PS_DOT);
	m_ILogarithmAxis->SetYAxisGridLineStyle(PS_DOT);

	CString strAxisTitle = "对数坐标系";
	BSTR    bstrAxisTitle = strAxisTitle.AllocSysString();
	m_ILogarithmAxis->SetAxisTitle(bstrAxisTitle);

	m_ILogarithmAxis->SetWorkAreaBkColor((long)(RGB(255,255,255)));
	unsigned long ulColor=RGB(83,83,83);
		CString strXAxisNameFont = "文鼎粗行楷简";
	BSTR bstrXAxisNameFont = strXAxisNameFont.AllocSysString();
	m_ILogarithmAxis->SetXAxisNameFont(-12,0,0,0,0,'\0','\0','\0','\0','\x1','\x2','\x1','1',bstrXAxisNameFont);
	m_ILogarithmAxis->SetYAxisNameFont(-12,0,0,0,0,'\0','\0','\0','\0','\x1','\x2','\x1','1',bstrXAxisNameFont);
	CString strXAxisName = "t/S";
	CString strYAxisName = "I/A";
	BSTR    bstrXAxisName = strXAxisName.AllocSysString();
	BSTR    bstrYAxisName = strYAxisName.AllocSysString();
	m_ILogarithmAxis->SetXAxisName(bstrXAxisName);
	m_ILogarithmAxis->SetYAxisName(bstrYAxisName);
	m_ILogarithmAxis->SetAxisCenterColor((long)(RGB(0,0,0)));
	m_ILogarithmAxis->SetAxisDrawStyle(LOGARITHMAXISDRAW_ALL);
	m_ILogarithmAxis->SetXAxisGridLineColor((long)(RGB(240,240,240)));
	m_ILogarithmAxis->SetYAxisGridLineColor((long)(RGB(240,240,240)));
	m_ILogarithmAxis->SetAxisCenterColor((long)(RGB(0,0,0)));

	m_ILogarithmAxis->ResetAxis();
	m_ILogarithmAxis->SetBoder(m_rectAxis.left,m_rectAxis.top,m_rectAxis.right,m_rectAxis.bottom);
	
	m_iCurrTestItem	=0;			//当前测试项目
	m_fMaxTimeVal	=1000;		//坐标的最大时间数值
	m_fMaxCurrVal	=40;		//坐标的最大电流数值
	m_iAxisGridLineType=1;
	InitAxisValue();
}

//初始化各坐标轴的范围
void CLogarithmAxisDlg::InitAxisValue()
{
	m_fAxisValue[0]	= -0.2f;
	m_fAxisValue[1]	= 1.26f;
	m_fAxisValue[2] = -3.0f;
	m_fAxisValue[3] = 3.0f;
	m_ILogarithmAxis->SetMinMaxVal(m_fAxisValue[0],m_fAxisValue[1],m_fAxisValue[2],m_fAxisValue[3],0);
	
}

void CLogarithmAxisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogarithmAxisDlg)
	DDX_Control(pDX, IDC_FRAME, m_stcFrame);
	DDX_Check(pDX, IDC_AXISBORDER, m_bAxisBorder);
	DDX_Check(pDX, IDC_AXISCENTER, m_bAxisCenter);
	DDX_Check(pDX, IDC_WORKAREA, m_bWorkArea);
	DDX_Check(pDX, IDC_XAXISLINE, m_bXAxisLine);
	DDX_Check(pDX, IDC_XHALFSCALE, m_bXHalfScale);
	DDX_Check(pDX, IDC_XSCALETEXT, m_bXScaleText);
	DDX_Check(pDX, IDC_XTENTHSCALE, m_bXTenthScale);
	DDX_Check(pDX, IDC_YAXISLINE, m_bYAxisLine);
	DDX_Check(pDX, IDC_YHALFSCALE, m_bYHalfScale);
	DDX_Check(pDX, IDC_YSCALETEXT, m_bYScaleText);
	DDX_Check(pDX, IDC_YTENTHSCALE, m_bYTenthScale);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogarithmAxisDlg, CDialog)
	//{{AFX_MSG_MAP(CLogarithmAxisDlg)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_WORKAREA, OnWorkarea)
	ON_BN_CLICKED(IDC_AXISCENTER, OnAxiscenter)
	ON_BN_CLICKED(IDC_AXISBORDER, OnAxisborder)
	ON_BN_CLICKED(IDC_XAXISLINE, OnXaxisline)
	ON_BN_CLICKED(IDC_XSCALETEXT, OnXscaletext)
	ON_BN_CLICKED(IDC_XTENTHSCALE, OnXtenthscale)
	ON_BN_CLICKED(IDC_XHALFSCALE, OnXhalfscale)
	ON_BN_CLICKED(IDC_YAXISLINE, OnYaxisline)
	ON_BN_CLICKED(IDC_YSCALETEXT, OnYscaletext)
	ON_BN_CLICKED(IDC_YTENTHSCALE, OnYtenthscale)
	ON_BN_CLICKED(IDC_YHALFSCALE, OnYhalfscale)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogarithmAxisDlg message handlers

void CLogarithmAxisDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if (m_ILogarithmAxis != NULL)
	{
		m_ILogarithmAxis->Release();
	}
	
}

BOOL CLogarithmAxisDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitLogarithmAxis();
//	ResetNormalAxis();
	ResetLogAxisDataDef();
//	OnAxisColorChanged();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLogarithmAxisDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	if (m_ILogarithmAxis != NULL)
	{
		CDC *pDC = GetDC();
		long lDC = (long)pDC;;
		m_ILogarithmAxis->DrawAxis(lDC,1,0,0);
		ReleaseDC(pDC);
	}
	
	// Do not call CDialog::OnPaint() for painting messages
}


void CLogarithmAxisDlg::ResetLogAxisDataDef()			//初始化坐标位置
{	
	double dMinX =m_fAxisValue[0];	//0.01	
	double dMaxX =m_fAxisValue[1];		//1000	//时间
	double dMinY =m_fAxisValue[2];	//0.01
	double dMaxY =m_fAxisValue[3];		//10

	m_stcFrame.GetWindowRect(&m_rectAxis);
	ScreenToClient(&m_rectAxis);
	m_ILogarithmAxis->SetMinMaxVal(dMinX,dMinY,dMaxX,dMaxY,0);
	m_ILogarithmAxis->SetBoder(m_rectAxis.left,m_rectAxis.top,m_rectAxis.right,m_rectAxis.bottom);

}

/*
//坐标轴颜色信息改变
void CLogarithmAxisDlg::OnAxisColorChanged()
{
	if(m_iAxisGridLineType==0)
	{
		m_LogAxis.odDrawPara.lVertLineStyle=PS_SOLID;
//		m_ILogarithmAxis->set
		m_LogAxis.odDrawPara.lHorzLineStyle=PS_SOLID;
	}
	else
	{
		m_LogAxis.odDrawPara.lVertLineStyle=PS_DOT;
		m_LogAxis.odDrawPara.lHorzLineStyle=PS_DOT;
	}
	
	m_ILogarithmAxis->SetWorkAreaBkColor((long)(RGB(255,255,255)));
//	m_LogAxis.odDrawPara.crVert_WorkAreaLine_Color=m_crAxisGrid;
//	m_LogAxis.odDrawPara.crHorz_WorkAreaLine_Color=m_crAxisGrid;
//	m_LogAxis.odDrawPara.crCircleScale=m_crAxisGrid;
//	m_LogAxis.odDrawPara.crBiaslineScale=m_crAxisGrid;
	m_ILogarithmAxis->SetAxisCenterColor((long)m_crAxisCenter);
//	m_LogAxis.odDrawPara.ContinueInit();
}*/

void CLogarithmAxisDlg::ResetNormalAxis()
{
	double dMinX=m_fAxisValue[0];
	double dMaxX=m_fAxisValue[1];
	double dMinY=m_fAxisValue[2];
	double dMaxY=m_fAxisValue[3];
	m_ILogarithmAxis->SetMinMaxVal(dMinX,dMinY,dMaxX,dMaxY,0);

	m_stcFrame.GetWindowRect(&m_rectAxis);
	ScreenToClient(&m_rectAxis);
	m_ILogarithmAxis->SetBoder(m_rectAxis.left,m_rectAxis.top,m_rectAxis.right,m_rectAxis.bottom);

	InitAxisAttr();
}

void CLogarithmAxisDlg::InitAxisAttr()
{
	CRect rectWork;
	long *left = 0;
	long *top = 0;
	long *right = 0;
	long *bottom = 0;
	m_ILogarithmAxis->GetWorkArea(left,top,right,bottom);
	rectWork = CRect(*left,*top,*right,*bottom);
	float fYValue=0,fXValue=0;
	float fYMaxValue=0,fYMinValue=0,fXMaxValue=0,fXMinValue=0;
	CPoint pointCenter=CPoint(0,0);
	double *dMinX=0,*dMinY=0,*dMaxX=0,*dMaxY=0;
	m_ILogarithmAxis->GetMinMaxVal(dMinX,dMinY,dMaxX,dMaxY,0);
	fYMaxValue=(*dMaxY);
	fYMinValue=(*dMinY);
	
	int iHeight=rectWork.Height();
	float fValYOneGap=iHeight/(fYMaxValue-fYMinValue);///Y轴实际坐标与实际值的比率
	///////////////////////////////////////////////
	fXMaxValue=(*dMaxX);
	fXMinValue=(*dMinX);
	int iWidth=rectWork.Width();
	float fValXOneGap=iWidth/(fXMaxValue-fXMinValue);//X轴实际坐标与实际值的比率
	/////坐标原点在屏幕上的位置
	float f=rectWork.left + (0-fXMinValue)*fValXOneGap;
	pointCenter.x=FloatValToInt(f);
	f=rectWork.bottom -(0-fYMinValue)*fValYOneGap;
	pointCenter.y=FloatValToInt(f);
	/////// 
	m_ILogarithmAxis->SetXAxisMinSawGapWidth(fValXOneGap);
	m_ILogarithmAxis->SetYAxisMinSawGapHeight(fValYOneGap);
//	m_LogAxis.odDisplayPara.m_ptCenterLogInDv=pointCenter;
}

int CLogarithmAxisDlg::FloatValToInt(double f,BOOL bCaryy)
{
	int iVal = 0;
	char pszBuff[40];
	int nFlag = 1;
	sprintf(pszBuff,"%f",f);
	if (pszBuff[0] == '-')
	{
		nFlag = -1;
	}
	char *pTemp = pszBuff;
	while (*pTemp != 0)
	{
		if (*pTemp == '.')
			break;
		pTemp++;
	}
	if(*pTemp != '.')
		return atoi(pszBuff);
	*pTemp = 0;
	pTemp++;
	iVal = atoi(pszBuff);
	if(*pTemp >= '5' && bCaryy )
	{
		iVal += nFlag;
	}
	return iVal;
}

void CLogarithmAxisDlg::ChangeDrawStype(BOOL bSet,long nStyle)
{
	if (m_ILogarithmAxis == NULL)
	{
		return ;
	}
	
	if (bSet)
	{
		m_ILogarithmAxis->SetAxisDrawStyleBit(nStyle);
	}
	else
	{
		m_ILogarithmAxis->ClearAxisDrawStyleBit(nStyle);
	}
	CRect rect = m_rectAxis;
	rect.InflateRect(2,2,2,2);
	
	InvalidateRect(rect,true);
	
}

void CLogarithmAxisDlg::OnWorkarea() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bWorkArea,LOGARITHMAXISDRAW_WORKAREA);
	
}

void CLogarithmAxisDlg::OnAxiscenter() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bAxisCenter,LOGARITHMAXISDRAW_AXISCENTER);
	
}

void CLogarithmAxisDlg::OnAxisborder() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bAxisBorder,LOGARITHMAXISDRAW_AXISBODER);
	
}

void CLogarithmAxisDlg::OnXaxisline() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bXAxisLine,LOGARITHMAXISDRAW_XAXIS_LINE);
	
}

void CLogarithmAxisDlg::OnXscaletext() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bXScaleText,LOGARITHMAXISDRAW_XAXIS_SCALETEXT);
	
}

void CLogarithmAxisDlg::OnXtenthscale() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bXTenthScale,LOGARITHMAXISDRAW_XAXIS_TENTHSCALE);
	
}

void CLogarithmAxisDlg::OnXhalfscale() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bXHalfScale,LOGARITHMAXISDRAW_XAXIS_HALFSCCALE);
	
}

void CLogarithmAxisDlg::OnYaxisline() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bYAxisLine,LOGARITHMAXISDRAW_YAXIS_LINE);
	
}

void CLogarithmAxisDlg::OnYscaletext() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bYScaleText,LOGARITHMAXISDRAW_YAXIS_SCALETEXT);
	
}

void CLogarithmAxisDlg::OnYtenthscale() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bYTenthScale,LOGARITHMAXISDRAW_YAXIS_TENTHSCALE);
	
}

void CLogarithmAxisDlg::OnYhalfscale() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bYHalfScale,LOGARITHMAXISDRAW_YAXIS_HALFSCCALE);
	
}
