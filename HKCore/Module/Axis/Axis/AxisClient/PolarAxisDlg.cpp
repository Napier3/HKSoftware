// PolarAxisDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AxisClient.h"
#include "PolarAxisDlg.h"
#include "..\..\..\Module\Api\GloblaDrawFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPolarAxisDlg dialog


CPolarAxisDlg::CPolarAxisDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPolarAxisDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPolarAxisDlg)
	m_bAngleUnitLine = TRUE;
	m_bAxisBorder = TRUE;
	m_bAxisCenter = TRUE;
	m_bCircleUnit = TRUE;
	m_bWorkArea = TRUE;
	m_bWorkAreaFrame = TRUE;
	m_bAxisTitle = TRUE;
	m_strAngleLineWidth = _T("");
	m_strCircleLineWidth = _T("");
	m_strTitle = _T("");
	m_strAngleUnit = _T("");
	m_strCircleUnit = _T("");
	//}}AFX_DATA_INIT
	m_IPolarAxis = NULL;
	iCount = 0;
	
}

void CPolarAxisDlg::InitPolarAxis()
{
	if (!CreatePloarAxisInterface(&m_IPolarAxis))
	{
		MessageBox("create IAxis failed!");
		return;
	}

	m_IPolarAxis->SetAxisDrawStyle(POLARAXISDRAW_ALL);
	m_stcPolarFrame.GetWindowRect(&m_rectPolarAxis);
	ScreenToClient(&m_rectPolarAxis);

    m_IPolarAxis->SetMarginGap(45,15,30,15);
//	lfAxisCenter		=InitLogFont (-12*m_lZoomCoefficient,0,0,0,400,'\0','\0','\0','\1','\x1','\x2','\x1','1',"Arial");

	//矢量的名称绘制字体
//	lfVectorName		=InitLogFont (-12*m_lZoomCoefficient,0,0,0,600,'\0','\0','\0','\1','\x1','\x2','\x1','1',"Arial");

//工作区域及坐标轴颜色定义
	m_IPolarAxis->SetAxisBackColor((long)(GetSysColor(COLOR_3DFACE)));
	m_IPolarAxis->SetWorkAreaBkColor((long)(RGB(255,255,255)));
	
//角度刻度线属性定义
	m_IPolarAxis->SetAngleUnitLineColor((long)(GetSysColor(COLOR_3DDKSHADOW)));
	m_IPolarAxis->SetAngleUnitLineWidth(1);
	m_IPolarAxis->SetAngleUnitFontColor((long)(RGB(0,0,0)));

	m_IPolarAxis->SetAngleUnitLineStyle(PS_DOT);
	m_IPolarAxis->SetAngleUnitID(30);
	m_IPolarAxis->SetAngleUnitFont(-12,0,0,0,400,'\0','\0','\0','\1','\x1','\x2','\x1','1',_bstr_t("Arial"));

//坐标中心轴及边框定义
	m_IPolarAxis->SetAxisCenterColor((long)(RGB(0,0,0)));
//	m_crAxisFrame		=RGB(0,0,0);		//坐标边框颜色
	m_IPolarAxis->SetFrameLeftTopColor((long)(RGB(128,128,128)));
	m_IPolarAxis->SetFrameRightBottomColor((long)(RGB(240,240,240)));
	m_IPolarAxis->SetFrameShadow(2);
	m_IPolarAxis->SetAxisCenterLineType(PS_DOT);
	m_IPolarAxis->SetAxisCenterLineWidth(1);

//圆(幅值)刻度线属性定义
	m_IPolarAxis->SetCircleUnitLineStyle(PS_DOT);
	m_IPolarAxis->SetCircleUnitLineColor((long)(GetSysColor(COLOR_3DDKSHADOW)));
	m_IPolarAxis->SetCircleUnitLineWidth(1);
//	m_iCircleGridCounts	=5;
	m_IPolarAxis->SetCircleAxisCounts(5);
	for(int i=0;i<10;i++)
	{
		m_IPolarAxis->SetCircleUnitValue(i,20*sizeof(char));
	}	
	
	m_IPolarAxis->SetAxisTitle(_bstr_t("极坐标系"));
	m_IPolarAxis->SetAxisTitleFontColor((long)(RGB(0,0,0)));
	m_IPolarAxis->SetAxisTitleFont(-14,0,0,0,600,'\0','\0','\0','\0','\x1','\x2','\x1','1',_bstr_t("宋体"));

	m_IPolarAxis->SetBoder(m_rectPolarAxis.left,m_rectPolarAxis.top,m_rectPolarAxis.right,m_rectPolarAxis.bottom);
    m_IPolarAxis->ResetAxis();
}

void CPolarAxisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPolarAxisDlg)
	DDX_Control(pDX, IDC_BTN_ZOOMOUT, m_btnZoomOut);
	DDX_Control(pDX, IDC_BTN_ZOOMIN, m_btnZoomIn);
	DDX_Control(pDX, IDC_BTN_COLOR_ANGLEFONT, m_crAngleFont);
	DDX_Control(pDX, IDC_BTN_FONTANGLELINE, m_fontAngleLine);
	DDX_Control(pDX, IDC_BTN_FONT, m_btnFont);
	DDX_Control(pDX, IDC_BTN_COLOR_CIRCLELINE, m_crCircleLine);
	DDX_Control(pDX, IDC_BTN_COLOR_ANGLELINE, m_crAngleLine);
	DDX_Control(pDX, IDC_COMBO_CIRCLELINE, m_cmbCircleLine);
	DDX_Control(pDX, IDC_COMBO_ANGLELINE, m_cmbAngleLine);
	DDX_Control(pDX, IDC_COMBO_FRAMESHADOW, m_cmbFrameShadow);
	DDX_Control(pDX, IDC_BTN_COLOR_RIGHTBOTTOMFRAME, m_crRightBottomFrame);
	DDX_Control(pDX, IDC_BTN_COLOR_LEFTTOPFRAME, m_crLeftTopFrame);
	DDX_Control(pDX, IDC_BTN_COLOR_AXISBACK, m_crAxisBack);
	DDX_Control(pDX, IDC_BTN_COLOR_AXISTITLE, m_crAxisTitle);
	DDX_Control(pDX, IDC_BTN_COLOR_WORKAREA, m_crWorkArea);
	DDX_Control(pDX, IDC_FRAME, m_stcPolarFrame);
	DDX_Check(pDX, IDC_ANGLEUNITLINE, m_bAngleUnitLine);
	DDX_Check(pDX, IDC_AXISBORDER, m_bAxisBorder);
	DDX_Check(pDX, IDC_AXISCENTER, m_bAxisCenter);
	DDX_Check(pDX, IDC_CIRCLEUNIT, m_bCircleUnit);
	DDX_Check(pDX, IDC_WORKAREA, m_bWorkArea);
	DDX_Check(pDX, IDC_WORKAREAFRAME, m_bWorkAreaFrame);
	DDX_Check(pDX, IDC_AXISTITLE, m_bAxisTitle);
	DDX_Text(pDX, IDC_EDIT_ANGLELINE, m_strAngleLineWidth);
	DDX_Text(pDX, IDC_EDIT_CIRCLELINE, m_strCircleLineWidth);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_strTitle);
	DDX_Text(pDX, IDC_EDIT_ANGLEUNIT, m_strAngleUnit);
	DDX_Text(pDX, IDC_EDIT_CIRCLEUNIT, m_strCircleUnit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPolarAxisDlg, CDialog)
	//{{AFX_MSG_MAP(CPolarAxisDlg)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_WORKAREA, OnWorkarea)
	ON_BN_CLICKED(IDC_WORKAREAFRAME, OnWorkareaframe)
	ON_BN_CLICKED(IDC_AXISCENTER, OnAxiscenter)
	ON_BN_CLICKED(IDC_AXISBORDER, OnAxisborder)
	ON_BN_CLICKED(IDC_ANGLEUNITLINE, OnAngleunitline)
	ON_BN_CLICKED(IDC_CIRCLEUNIT, OnCircleunit)
	ON_BN_CLICKED(IDC_BTN_COLOR_WORKAREA, OnBtnColorWorkarea)
	ON_BN_CLICKED(IDC_AXISTITLE, OnAxistitle)
	ON_BN_CLICKED(IDC_BTN_COLOR_AXISTITLE, OnBtnColorAxistitle)
	ON_BN_CLICKED(IDC_BTN_COLOR_AXISBACK, OnBtnColorAxisback)
	ON_BN_CLICKED(IDC_BTN_COLOR_LEFTTOPFRAME, OnBtnColorLefttopframe)
	ON_BN_CLICKED(IDC_BTN_COLOR_RIGHTBOTTOMFRAME, OnBtnColorRightbottomframe)
	ON_CBN_SELCHANGE(IDC_COMBO_FRAMESHADOW, OnSelchangeComboFrameshadow)
	ON_CBN_SELCHANGE(IDC_COMBO_ANGLELINE, OnSelchangeComboAngleline)
	ON_CBN_SELCHANGE(IDC_COMBO_CIRCLELINE, OnSelchangeComboCircleline)
	ON_BN_CLICKED(IDC_BTN_COLOR_ANGLELINE, OnBtnColorAngleline)
	ON_BN_CLICKED(IDC_BTN_COLOR_CIRCLELINE, OnBtnColorCircleline)
	ON_BN_CLICKED(IDC_BTN_FONT, OnBtnFont)
	ON_BN_CLICKED(IDC_BTN_FONTANGLELINE, OnBtnFontangleline)
	ON_BN_CLICKED(IDC_BTN_COLOR_ANGLEFONT, OnBtnColorAnglefont)
	ON_BN_CLICKED(IDC_BTN_ZOOMIN, OnBtnZoomin)
	ON_BN_CLICKED(IDC_BTN_ZOOMOUT, OnBtnZoomout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPolarAxisDlg message handlers

BOOL CPolarAxisDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitPolarAxis();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPolarAxisDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	if (m_IPolarAxis != NULL)
	{
		CDC *pDC = GetDC();
		long lDC = (long)pDC;
		m_IPolarAxis->DrawAxis(lDC);
		ReleaseDC(pDC);
	}
}

void CPolarAxisDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if (m_IPolarAxis != NULL)
	{
		m_IPolarAxis->Release();
	}
	
}

void CPolarAxisDlg::ChangeDrawStype(BOOL bSet,long nStyle)
{
	if (m_IPolarAxis == NULL)
	{
		return ;
	}
	
	if (bSet)
	{
		m_IPolarAxis->SetAxisDrawStyleBit(nStyle);
	}
	else
	{
		m_IPolarAxis->ClearAxisDrawStyleBit(nStyle);
	}
	CRect rect = m_rectPolarAxis;
	rect.InflateRect(2,2,2,2);
	
	InvalidateRect(rect,true);
	
}


void CPolarAxisDlg::OnWorkarea() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bWorkArea,POLARAXISDRAW_WORKAREA);
	
}

void CPolarAxisDlg::OnWorkareaframe() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bWorkAreaFrame,POLARAXISDRAW_WORKAREAFRAME);
	
}

void CPolarAxisDlg::OnAxiscenter() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bAxisCenter,POLARAXISDRAW_AXISCENTER);
	
}

void CPolarAxisDlg::OnAxisborder() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bAxisBorder,POLARAXISDRAW_AXISBODER);
	
}

void CPolarAxisDlg::OnAngleunitline() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bAngleUnitLine,POLARAXISDRAW_ANGLEUNIT_LINE);
	
}

void CPolarAxisDlg::OnCircleunit() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bCircleUnit,POLARAXISDRAW_CIRCLEUNIT);
	
}

void CPolarAxisDlg::OnAxistitle() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bAxisTitle,POLARAXISDRAW_AXISTITLE);
	
}

void CPolarAxisDlg::OnBtnColorWorkarea() 
{
	SetColor();
}

void CPolarAxisDlg::OnBtnColorAxistitle() 
{
	SetColor();	
}

void CPolarAxisDlg::OnBtnColorAxisback() 
{
	SetColor();
}

void CPolarAxisDlg::OnBtnColorLefttopframe() 
{
	SetColor();	
}

void CPolarAxisDlg::OnBtnColorRightbottomframe() 
{
	SetColor();
}

void CPolarAxisDlg::OnSelchangeComboFrameshadow() 
{
	CString str="";
	m_cmbFrameShadow.GetWindowText(str);
	int iFrameShadow = atoi(str);
	m_IPolarAxis->SetFrameShadow(iFrameShadow);
	CRect rect = m_rectPolarAxis;
	InvalidateRect(rect,true);
	
}

void CPolarAxisDlg::OnSelchangeComboAngleline() 
{
	CString str="";
	m_cmbAngleLine.GetWindowText(str);
	if (str == "PS_SOLID") 
	{
		m_IPolarAxis->SetAngleUnitLineStyle(PS_SOLID);
	}
	else if (str == "PS_DOT")
	{
		m_IPolarAxis->SetAngleUnitLineStyle(PS_DOT);
	}
	else if (str == "PS_DASH") 
	{
		m_IPolarAxis->SetAngleUnitLineStyle(PS_DASH);
	}
	else if (str == "PS_DASHDOT") 
	{
		m_IPolarAxis->SetAngleUnitLineStyle(PS_DASHDOT);
	}
	else
	{
		m_IPolarAxis->SetAngleUnitLineStyle(PS_DASHDOTDOT);
	}
	CRect rect = m_rectPolarAxis;
	InvalidateRect(rect,true);
	
}

void CPolarAxisDlg::OnSelchangeComboCircleline() 
{
	CString str="";
	m_cmbCircleLine.GetWindowText(str);
	if (str == "PS_SOLID") 
	{
		m_IPolarAxis->SetCircleUnitLineStyle(PS_SOLID);
	}
	else if (str == "PS_DOT")
	{
		m_IPolarAxis->SetCircleUnitLineStyle(PS_DOT);
	}
	else if (str == "PS_DASH") 
	{
		m_IPolarAxis->SetCircleUnitLineStyle(PS_DASH);
	}
	else if (str == "PS_DASHDOT") 
	{
		m_IPolarAxis->SetCircleUnitLineStyle(PS_DASHDOT);
	}
	else
	{
		m_IPolarAxis->SetCircleUnitLineStyle(PS_DASHDOTDOT);
	}
	CRect rect = m_rectPolarAxis;
	InvalidateRect(rect,true);
	
}

void CPolarAxisDlg::OnBtnColorAngleline() 
{
	SetColor();	
}

void CPolarAxisDlg::OnBtnColorCircleline() 
{
	SetColor();
}

BOOL CPolarAxisDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST) 
	{
		HWND hWnd;
		if(pMsg->wParam==VK_RETURN )
		{
			hWnd =::GetFocus();
		}
		int iID=::GetDlgCtrlID(hWnd);
		if(iID==1053)              //IDC_EDIT_ANGLELINE
		{
			UpdateData(TRUE);
			int iAngleLineWidth = atoi(m_strAngleLineWidth); 
			m_IPolarAxis->SetAngleUnitLineWidth(iAngleLineWidth);
		}
		if(iID==1054)              //IDC_EDIT_CIRCLELINE
		{
			UpdateData(TRUE);
			int iCircleLineWidth = atoi(m_strCircleLineWidth); 
			m_IPolarAxis->SetCircleUnitLineWidth(iCircleLineWidth);
		}
		if(iID==1055)
		{
			UpdateData(TRUE);
			BSTR bstrTitle = m_strTitle.AllocSysString();
			m_IPolarAxis->SetAxisTitle(bstrTitle);			
		}
		if(iID==1057)
		{
			UpdateData(TRUE);
			int iAngleUnit = atoi(m_strAngleUnit);
			m_IPolarAxis->SetAngleUnitID(iAngleUnit);			
		}
		if(iID==1059)
		{
			UpdateData(TRUE);
			int iCircleUnit = atoi(m_strCircleUnit);
			m_IPolarAxis->SetCircleAxisCounts(iCircleUnit);			
		}
		CRect rect = m_rectPolarAxis;
		InvalidateRect(rect,true);
		
	}
	
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CPolarAxisDlg::OnOK() 
{
	
//	CDialog::OnOK();
}

void CPolarAxisDlg::SetFont()
{
	LOGFONT lf;
	lf = InitLogFont (-14,0,0,0,600,'\0','\0','\0','\0','\x1','\x2','\x1','1',"宋体");	
	LOGFONT lfont;
	lfont = InitLogFont (-14,0,0,0,600,'\0','\0','\0','\0','\x1','\x2','\x1','1',"宋体");	
	long lfHeight;
	long lfWidth;
	long lfEscapement;
	long lfOrientation;
	long lfWeight;
	long lfItalic;
	long lfUnderline;
	long lfStrikeOut;
	long lfCharSet;
	long lfOutPrecision;
	long lfClipPrecision;
	long lfQuality;
	long lfPitchAndFamily;
	CString lfFaceName = "";
	
	CDC *pDC = GetDC();
	CFontDialog dlgFont(&lfont,0,pDC,this);
	if (dlgFont.DoModal() == IDOK) 
	{
		dlgFont.GetCurrentFont(&lf);
		lfont = lf;
		lfHeight = lf.lfHeight;
		lfWidth = lf.lfWidth;
		lfEscapement = lf.lfEscapement;
		lfOrientation = lf.lfOrientation;
		lfWeight = lf.lfWeight;
		lfItalic = lf.lfItalic;
		lfUnderline = lf.lfUnderline;
		lfStrikeOut = lf.lfStrikeOut;
		lfCharSet = lf.lfCharSet;
		lfOutPrecision = lf.lfOutPrecision;
		lfClipPrecision = lf.lfClipPrecision;
		lfQuality = lf.lfQuality;
		lfPitchAndFamily = lf.lfPitchAndFamily;
		lfFaceName = lf.lfFaceName;

		HWND hWnd;
		hWnd =::GetFocus();
		int iID=::GetDlgCtrlID(hWnd);
		if(iID==1056)  
		{
			m_IPolarAxis->SetAxisTitleFont(lfHeight,lfWidth,lfEscapement,lfOrientation
				,lfWeight,lfItalic,lfUnderline,lfStrikeOut,lfCharSet,lfOutPrecision
				,lfClipPrecision,lfQuality,lfPitchAndFamily,(_bstr_t)lfFaceName);
		}
		if (iID==1058)
		{
			m_IPolarAxis->SetAngleUnitFont(lfHeight,lfWidth,lfEscapement,lfOrientation
				,lfWeight,lfItalic,lfUnderline,lfStrikeOut,lfCharSet,lfOutPrecision
				,lfClipPrecision,lfQuality,lfPitchAndFamily,(_bstr_t)lfFaceName);
		}
		CRect rect = m_rectPolarAxis;
		InvalidateRect(rect,true);
		
	}

}

void CPolarAxisDlg::SetColor()
{
	COLORREF crColor = RGB(255,255,255);
	CColorDialog od(crColor,0,this);	
	if (od.DoModal()==IDOK)
	{
		COLORREF cr1=od.GetColor();
		HWND hWnd;
		hWnd =::GetFocus();
		int iID=::GetDlgCtrlID(hWnd);
		if(iID==1032) 
		{
			m_IPolarAxis->SetCircleUnitLineColor((long)cr1);
		}
		if(iID==1031) 
		{
			m_IPolarAxis->SetAngleUnitLineColor((long)cr1);
		}
		if(iID==1026) 
		{
			m_IPolarAxis->SetWorkAreaBkColor((long)cr1);
		}
		if(iID==1027) 
		{
			m_IPolarAxis->SetAxisTitleFontColor((long)cr1);
		}
		if(iID==1028) 
		{
			m_IPolarAxis->SetAxisBackColor((long)cr1);
		}
		if(iID==1029) 
		{
			m_IPolarAxis->SetFrameLeftTopColor((long)cr1);
		}
		if(iID==1030) 
		{
			m_IPolarAxis->SetFrameRightBottomColor((long)cr1);
		}
		if(iID==1062) 
		{
			m_IPolarAxis->SetAngleUnitFontColor((long)cr1);
		}
		CRect rect = m_rectPolarAxis;
		InvalidateRect(rect,true);
		
	}
}

void CPolarAxisDlg::OnBtnFont() 
{
	SetFont();
}

void CPolarAxisDlg::OnBtnFontangleline() 
{
	SetFont();	
}

void CPolarAxisDlg::OnBtnColorAnglefont() 
{
	SetColor();	
}

void CPolarAxisDlg::OnBtnZoomin() 
{
	iCount++;
	if(iCount<=2)
	{
		m_IPolarAxis->ZoomIn(0.5);
		CRect rect = m_rectPolarAxis;
		InvalidateRect(rect,true);
	}
	else
		return;
	
}

void CPolarAxisDlg::OnBtnZoomout() 
{
	m_IPolarAxis->ZoomOut(2);
	CRect rect = m_rectPolarAxis;
	InvalidateRect(rect,true);
	
}
