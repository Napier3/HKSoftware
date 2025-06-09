// DescartesAxisDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AxisClient.h"
#include "DescartesAxisDlg.h"
#include "..\..\..\Module\Api\GloblaDrawFunctions.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDescartesAxisDlg dialog


CDescartesAxisDlg::CDescartesAxisDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDescartesAxisDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDescartesAxisDlg)
	m_bDrawFrame = TRUE;
	m_bAxisTitle = TRUE;
	m_bXAxisTitle = TRUE;
	m_bYAxisTitle = TRUE;
	m_bXAxisTenth = TRUE;
	m_bXAxisScaleText = TRUE;
	m_bYAxisTenth = TRUE;
	m_bAxisCenter = TRUE;
	m_bXAxisHalfUnitScale = TRUE;
	m_bYAxisHalfUnitScale = TRUE;
	m_bYAxisScaleText = TRUE;
	m_strAxisTitle = _T("");
	m_strXAxisName = _T("");
	m_strYAxisName = _T("");
	m_strXAxisWidth = _T("");
	m_strYAxisWidth = _T("");
	m_strXHalfScaleLen = _T("");
	m_strXTenthScaleLen = _T("");
	m_strXUnitScaleLen = _T("");
	m_strYHalfScaleLen = _T("");
	m_strYTenthScaleLen = _T("");
	m_strYUnitScaleLen = _T("");
	m_strCenterLineWidth = _T("");
	//}}AFX_DATA_INIT
	m_IDescartesAxis = NULL;

}

void CDescartesAxisDlg::InitAxis()
{
	if (!CreateDescartesAxisInterface(&m_IDescartesAxis))
	{
		MessageBox("create IAxis failed!");
		return;
	}
	m_IDescartesAxis->SetAxisDrawStyle(DESCARTESAXISDRAW_ALL);

	m_IDescartesAxis->SetXAxisName(_bstr_t("t/S"));
	m_IDescartesAxis->SetYAxisName(_bstr_t("Ia /A"));
	
	m_stcFrame.GetWindowRect(&m_rectDescartesAxis);
	ScreenToClient(&m_rectDescartesAxis);
	
	m_IDescartesAxis->SetYAxisGridLineStyle(PS_DOT);
	m_IDescartesAxis->SetXAxisGridLineStyle(PS_DOT);

	//坐标轴的范围
	m_IDescartesAxis->SetMinMaxVal(-5,-5,5,5,0);
	//坐标轴的颜色设置
	COLORREF crXAxisGridLineColor = RGB(128,128,0);
	COLORREF crAxisCenterColor = RGB(0,0,0);
	long lXAxisGridLineColor = (long)crXAxisGridLineColor;
	long lAxisCenterColor = (long)crAxisCenterColor;
	m_IDescartesAxis->SetXAxisGridLineColor(lXAxisGridLineColor);
	m_IDescartesAxis->SetAxisCenterColor(lAxisCenterColor);
	
	//坐标轴的名称的字体
	CString strNameFont = "宋体";
	BSTR bstrNameFont = strNameFont.AllocSysString();
	m_IDescartesAxis->SetXAxisNameFont(-12,0,0,0,400,'\0','\0','\0','\0','\x1','\x2','\x1','1',bstrNameFont);
	m_IDescartesAxis->SetYAxisNameFont(-12,0,0,0,400,'\0','\0','\0','\0','\x1','\x2','\x1','1',bstrNameFont);
	CString strAxisTitle = "笛卡尔坐标系";
	BSTR bstrAxisTitle = strAxisTitle.AllocSysString();
	m_IDescartesAxis->SetAxisTitle(bstrAxisTitle);

	m_IDescartesAxis->SetXAxisMaxUnitCount(20);
	m_IDescartesAxis->SetYAxisMaxUnitCount(20);

	m_IDescartesAxis->SetBoder(m_rectDescartesAxis.left,m_rectDescartesAxis.top,m_rectDescartesAxis.right,m_rectDescartesAxis.bottom);


	
}

void CDescartesAxisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDescartesAxisDlg)
	DDX_Control(pDX, IDC_BTN_ZOOMOUT, m_btnZoomOut);
	DDX_Control(pDX, IDC_BTN_ZOOMIN, m_btnZoomIn);
	DDX_Control(pDX, IDC_COMBO_DESCENTERLINESTYLE, m_cmbCenterLineStyle);
	DDX_Control(pDX, IDC_BTN_COLOR_CENTERLINE, m_crCenterLine);
	DDX_Control(pDX, IDC_BTN_COLOR_DESXUNITSCALESHADOW, m_crXUnitScaleShadow);
	DDX_Control(pDX, IDC_BTN_COLOR_DESXUNITSCALE, m_crXUnitScale);
	DDX_Control(pDX, IDC_BTN_COLOR_DESYTENTH, m_crYScaleTenth);
	DDX_Control(pDX, IDC_BTN_COLOR_DESXTENTH, m_crXScaleTenth);
	DDX_Control(pDX, IDC_COMBO_DESYGIRDSTYLE, m_cmbYGridStyle);
	DDX_Control(pDX, IDC_COMBO_DESXGRIDSTYLE, m_cmbXGridStyle);
	DDX_Control(pDX, IDC_BTN_COLOR_DESYGRID, m_crYGrid);
	DDX_Control(pDX, IDC_BTN_COLOR_DESXGRID, m_crXGrid);
	DDX_Control(pDX, IDC_BTN_COLOR_DESYSCALEFONT, m_crYScaleFont);
	DDX_Control(pDX, IDC_BTN_COLOR_DESXSCALEFONT, m_crXScaleFont);
	DDX_Control(pDX, IDC_BTN_COLOR_DESYAXISNAME, m_crYAxisName);
	DDX_Control(pDX, IDC_BTN_COLOR_DESXAXISNAME, m_crXAxisName);
	DDX_Control(pDX, IDC_BTN_FONT_DESYSCALE, m_lfYScale);
	DDX_Control(pDX, IDC_BTN_FONT_DESXSCALE, m_lfXScale);
	DDX_Control(pDX, IDC_BTN_FONT_DESYAXISNAME, m_lfXAxisName);
	DDX_Control(pDX, IDC_BTN_FONT_DESXAXISNAME, m_lfYAxisName);
	DDX_Control(pDX, IDC_BTN_COLOR_DESYUNITSCALESHADOW, m_crYUnitScaleShadow);
	DDX_Control(pDX, IDC_BTN_COLOR_DESYUNITSCALE, m_crYUnitScale);
	DDX_Control(pDX, IDC_COMBO_DESFRAMESHADOW, m_cmbFrameShadow);
	DDX_Control(pDX, IDC_BTN_COLOR_DESFRAMERIGHTBOTTOM, m_crRightBottomFrame);
	DDX_Control(pDX, IDC_BTN_COLOR_DESFRAMELEFTTOP, m_crLeftTopFrame);
	DDX_Control(pDX, IDC_COMBO_DESBORDERSHADOW, m_cmbBorderShadow);
	DDX_Control(pDX, IDC_BTN_COLOR_DESRIGHTBOTTOMBORDER, m_crRightBottomBorder);
	DDX_Control(pDX, IDC_BTN_COLOR_DESLEFTTOPBORDER, m_crLeftTopBorder);
	DDX_Control(pDX, IDC_BTN_COLOR_DESAXISBACK, m_crAxisBack);
	DDX_Control(pDX, IDC_BTN_FONT_DESAXISTITLE, m_fontDesAxisTitle);
	DDX_Control(pDX, IDC_BTN_COLOR_DESAXISTITLE, m_crAxisTitle);
	DDX_Control(pDX, IDC_BTN_COLORWORKAREA, m_crWorkArea);
	DDX_Control(pDX, IDC_FRAME, m_stcFrame);
	DDX_Check(pDX, IDC_DRAWBORDER, m_bDrawFrame);
	DDX_Check(pDX, IDC_AXISTITLE, m_bAxisTitle);
	DDX_Check(pDX, IDC_XAXISTITLE, m_bXAxisTitle);
	DDX_Check(pDX, IDC_YAXISTITLE, m_bYAxisTitle);
	DDX_Check(pDX, IDC_XAXISTENITH, m_bXAxisTenth);
	DDX_Check(pDX, IDC_XAXISSCALETEXT, m_bXAxisScaleText);
	DDX_Check(pDX, IDC_YAXISTENITH, m_bYAxisTenth);
	DDX_Check(pDX, IDC_AXISCENTER, m_bAxisCenter);
	DDX_Check(pDX, IDC_XAXISHALFUNITSCALE, m_bXAxisHalfUnitScale);
	DDX_Check(pDX, IDC_YAXISHALFUNITSCALE, m_bYAxisHalfUnitScale);
	DDX_Check(pDX, IDC_YAXISSCALETEXT, m_bYAxisScaleText);
	DDX_Text(pDX, IDC_EDIT_AXISTITLE, m_strAxisTitle);
	DDX_Text(pDX, IDC_EDIT_DESXAXISNAME, m_strXAxisName);
	DDX_Text(pDX, IDC_EDIT_DESYAXISNAME, m_strYAxisName);
	DDX_Text(pDX, IDC_EDIT_DESXAXISWIDTH, m_strXAxisWidth);
	DDX_Text(pDX, IDC_EDIT_DESYAXISWIDTH, m_strYAxisWidth);
	DDX_Text(pDX, IDC_EDIT_DESXHALFSCALELEN, m_strXHalfScaleLen);
	DDX_Text(pDX, IDC_EDIT_DESXTENTHSCALELEN, m_strXTenthScaleLen);
	DDX_Text(pDX, IDC_EDIT_DESXUNITSCALELEN, m_strXUnitScaleLen);
	DDX_Text(pDX, IDC_EDIT_DESYHALFSCALELEN, m_strYHalfScaleLen);
	DDX_Text(pDX, IDC_EDIT_DESYTENTHSCALELEN, m_strYTenthScaleLen);
	DDX_Text(pDX, IDC_EDIT_DESYUNITSCALELEN, m_strYUnitScaleLen);
	DDX_Text(pDX, IDC_EDIT_DESCENTERLINEWIDTH, m_strCenterLineWidth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDescartesAxisDlg, CDialog)
	//{{AFX_MSG_MAP(CDescartesAxisDlg)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_DRAWBORDER, OnDrawborder)
	ON_BN_CLICKED(IDC_AXISTITLE, OnAxistitle)
	ON_BN_CLICKED(IDC_XAXISTITLE, OnXaxistitle)
	ON_BN_CLICKED(IDC_YAXISTITLE, OnYaxistitle)
	ON_BN_CLICKED(IDC_XAXISTENITH, OnXaxistenith)
	ON_BN_CLICKED(IDC_XAXISSCALETEXT, OnXaxisscaletext)
	ON_BN_CLICKED(IDC_YAXISTENITH, OnYaxistenith)
	ON_BN_CLICKED(IDC_AXISCENTER, OnAxiscenter)
	ON_BN_CLICKED(IDC_XAXISHALFUNITSCALE, OnXaxishalfunitscale)
	ON_BN_CLICKED(IDC_YAXISHALFUNITSCALE, OnYaxishalfunitscale)
	ON_BN_CLICKED(IDC_YAXISSCALETEXT, OnYaxisscaletext)
	ON_BN_CLICKED(IDC_BTN_COLORWORKAREA, OnBtnColorworkarea)
	ON_BN_CLICKED(IDC_BTN_COLOR_DESAXISTITLE, OnBtnColorDesaxistitle)
	ON_BN_CLICKED(IDC_BTN_FONT_DESAXISTITLE, OnBtnFontDesaxistitle)
	ON_BN_CLICKED(IDC_BTN_COLOR_DESAXISBACK, OnBtnColorDesaxisback)
	ON_BN_CLICKED(IDC_BTN_COLOR_DESLEFTTOPBORDER, OnBtnColorDeslefttopborder)
	ON_BN_CLICKED(IDC_BTN_COLOR_DESRIGHTBOTTOMBORDER, OnBtnColorDesrightbottomborder)
	ON_BN_CLICKED(IDC_BTN_COLOR_DESFRAMELEFTTOP, OnBtnColorDesframelefttop)
	ON_BN_CLICKED(IDC_BTN_COLOR_DESFRAMERIGHTBOTTOM, OnBtnColorDesframerightbottom)
	ON_BN_CLICKED(IDC_BTN_COLOR_DESYUNITSCALE, OnBtnColorDesyunitscale)
	ON_BN_CLICKED(IDC_BTN_COLOR_DESYUNITSCALESHADOW, OnBtnColorDesyunitscaleshadow)
	ON_BN_CLICKED(IDC_BTN_FONT_DESYAXISNAME, OnBtnFontDesyaxisname)
	ON_BN_CLICKED(IDC_BTN_FONT_DESXAXISNAME, OnBtnFontDesxaxisname)
	ON_BN_CLICKED(IDC_BTN_FONT_DESYSCALE, OnBtnFontDesyscale)
	ON_BN_CLICKED(IDC_BTN_FONT_DESXSCALE, OnBtnFontDesxscale)
	ON_BN_CLICKED(IDC_BTN_COLOR_DESYAXISNAME, OnBtnColorDesyaxisname)
	ON_BN_CLICKED(IDC_BTN_COLOR_DESXAXISNAME, OnBtnColorDesxaxisname)
	ON_BN_CLICKED(IDC_BTN_COLOR_DESYSCALEFONT, OnBtnColorDesyscalefont)
	ON_BN_CLICKED(IDC_BTN_COLOR_DESXSCALEFONT, OnBtnColorDesxscalefont)
	ON_BN_CLICKED(IDC_BTN_COLOR_DESYGRID, OnBtnColorDesygrid)
	ON_BN_CLICKED(IDC_BTN_COLOR_DESXGRID, OnBtnColorDesxgrid)
	ON_BN_CLICKED(IDC_BTN_COLOR_DESYTENTH, OnBtnColorDesytenth)
	ON_BN_CLICKED(IDC_BTN_COLOR_DESXTENTH, OnBtnColorDesxtenth)
	ON_CBN_SELCHANGE(IDC_COMBO_DESBORDERSHADOW, OnSelchangeComboDesbordershadow)
	ON_CBN_SELCHANGE(IDC_COMBO_DESFRAMESHADOW, OnSelchangeComboDesframeshadow)
	ON_CBN_SELCHANGE(IDC_COMBO_DESYGIRDSTYLE, OnSelchangeComboDesygirdstyle)
	ON_CBN_SELCHANGE(IDC_COMBO_DESXGRIDSTYLE, OnSelchangeComboDesxgridstyle)
	ON_BN_CLICKED(IDC_BTN_COLOR_DESXUNITSCALE, OnBtnColorDesxunitscale)
	ON_BN_CLICKED(IDC_BTN_COLOR_DESXUNITSCALESHADOW, OnBtnColorDesxunitscaleshadow)
	ON_CBN_SELCHANGE(IDC_COMBO_DESCENTERLINESTYLE, OnSelchangeComboDescenterlinestyle)
	ON_BN_CLICKED(IDC_BTN_COLOR_CENTERLINE, OnBtnColorCenterline)
	ON_BN_CLICKED(IDC_BTN_ZOOMIN, OnBtnZoomin)
	ON_BN_CLICKED(IDC_BTN_ZOOMOUT, OnBtnZoomout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDescartesAxisDlg message handlers

BOOL CDescartesAxisDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitAxis();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDescartesAxisDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if (m_IDescartesAxis != NULL)
	{
		m_IDescartesAxis->Release();
	}
}

void CDescartesAxisDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	if (m_IDescartesAxis != NULL)
	{

		CDC *pDC = GetDC();
		long lDC = (long)pDC;;
		m_IDescartesAxis->DrawAxis(lDC,1,0,0);
		ReleaseDC(pDC);
	}

	// Do not call CDialog::OnPaint() for painting messages
}

void CDescartesAxisDlg::ChangeDrawStype(BOOL bSet,long nStyle)
{
	if (m_IDescartesAxis == NULL)
	{
		return ;
	}

	if (bSet)
	{
		m_IDescartesAxis->SetAxisDrawStyleBit(nStyle);
	}
	else
	{
		m_IDescartesAxis->ClearAxisDrawStyleBit(nStyle);
	}
	CRect rect = m_rectDescartesAxis;
	rect.InflateRect(2,2,2,2);

	InvalidateRect(rect,true);
	
}

void CDescartesAxisDlg::OnDrawborder() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bDrawFrame,DESCARTESAXISDRAW_AXISBODER);
}

void CDescartesAxisDlg::OnAxistitle() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bAxisTitle,DESCARTESAXISDRAW_AXISTITLE);
}

void CDescartesAxisDlg::OnXaxistitle() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bXAxisTitle,DESCARTESAXISDRAW_XAXIS_NAME);
}

void CDescartesAxisDlg::OnYaxistitle() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bYAxisTitle,DESCARTESAXISDRAW_YAXIS_NAME);
}

void CDescartesAxisDlg::OnXaxistenith() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bXAxisTenth,DESCARTESAXISDRAW_XAXIS_HALFSCCALE);	
}

void CDescartesAxisDlg::OnXaxisscaletext() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bXAxisScaleText,DESCARTESAXISDRAW_XAXIS_SCALETEXT);
	
}

void CDescartesAxisDlg::OnYaxistenith() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bYAxisTenth,DESCARTESAXISDRAW_YAXIS_HALFSCCALE);
	
}

void CDescartesAxisDlg::OnAxiscenter() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bAxisCenter,DESCARTESAXISDRAW_AXISCENTER);
	
}

void CDescartesAxisDlg::OnXaxishalfunitscale() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bXAxisHalfUnitScale,DESCARTESAXISDRAW_XAXIS_TENTHSCALE);
	
}

void CDescartesAxisDlg::OnYaxishalfunitscale() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bYAxisHalfUnitScale,DESCARTESAXISDRAW_YAXIS_TENTHSCALE);
	
}

void CDescartesAxisDlg::OnYaxisscaletext() 
{
	UpdateData(TRUE);
	ChangeDrawStype(m_bYAxisScaleText,DESCARTESAXISDRAW_YAXIS_SCALETEXT);
	
}

void CDescartesAxisDlg::OnOK() 
{
	
	//	CDialog::OnOK();
}

void CDescartesAxisDlg::OnBtnColorworkarea() 
{
	CColorDialog od(m_crWorkArea.crColor,0,this);	
	if (od.DoModal()==IDOK)
	{
		COLORREF cr1=od.GetColor();
		if (m_crWorkArea.crColor!=cr1)
		{
			m_IDescartesAxis->SetWorkAreaBkColor((long)cr1);
			CRect rect = m_rectDescartesAxis;
			InvalidateRect(rect,true);

		}
	}	// TODO: Add your control notification handler code here
	
}

BOOL CDescartesAxisDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST) 
	{
		HWND hWnd;
		if(pMsg->wParam==VK_RETURN )
		{
			hWnd =::GetFocus();
		}
		int iID=::GetDlgCtrlID(hWnd);
		if(iID==1067)              //IDC_EDIT_ANGLELINE
		{
			UpdateData(TRUE);
			BSTR bstrAxisTitle = m_strAxisTitle.AllocSysString(); 
			m_IDescartesAxis->SetAxisTitle(bstrAxisTitle);
		}
		if(iID==1085)              //IDC_EDIT_CIRCLELINE
		{
			UpdateData(TRUE);
			BSTR bstrYAxisTitle = m_strYAxisName.AllocSysString(); 
			m_IDescartesAxis->SetYAxisName(bstrYAxisTitle);
		}
		if(iID==1086)
		{
			UpdateData(TRUE);
			BSTR bstrXAxisTitle = m_strXAxisName.AllocSysString(); 
			m_IDescartesAxis->SetXAxisName(bstrXAxisTitle);			
		}

		if(iID==1099)
		{
			UpdateData(TRUE);
			int iYAxisWidth = atoi(m_strYAxisWidth);
			m_IDescartesAxis->SetYAxisAreaWidth(iYAxisWidth);
			m_IDescartesAxis->SetBoder(m_rectDescartesAxis.left,m_rectDescartesAxis.top,m_rectDescartesAxis.right,m_rectDescartesAxis.bottom);
		}
		if(iID==1100)
		{
			UpdateData(TRUE);
			int iXAxisWidth = atoi(m_strXAxisWidth);
			m_IDescartesAxis->SetXAxisAreaHeight(iXAxisWidth);
			m_IDescartesAxis->SetBoder(m_rectDescartesAxis.left,m_rectDescartesAxis.top,m_rectDescartesAxis.right,m_rectDescartesAxis.bottom);
		}
		if(iID==1104)              
		{
			UpdateData(TRUE);
			int iXUnitScaleLen = atoi(m_strXUnitScaleLen); 
			m_IDescartesAxis->SetXAxisUnitScaleLineLen(iXUnitScaleLen);
		}
		if(iID==1106)
		{
			UpdateData(TRUE);
			int iXHalfScaleLen = atoi(m_strXHalfScaleLen); 
			m_IDescartesAxis->SetXAxisHalfScaleLineLen(iXHalfScaleLen);			
		}
		
		if(iID==1108)
		{
			UpdateData(TRUE);
			int iXTenthScaleLen = atoi(m_strXTenthScaleLen);
			m_IDescartesAxis->SetXAxisTenthScaleLineLen(iXTenthScaleLen);			
		}
		if(iID==1103)
		{
			UpdateData(TRUE);
			int iYUnitScaleLen = atoi(m_strYUnitScaleLen);
			m_IDescartesAxis->SetYAxisUnitScaleLineLen(iYUnitScaleLen);			
		}	
		if(iID==1105)
		{
			UpdateData(TRUE);
			int iYHalfScaleLen = atoi(m_strYHalfScaleLen); 
			m_IDescartesAxis->SetYAxisHalfScaleLineLen(iYHalfScaleLen);			
		}
		if(iID==1107)
		{
			UpdateData(TRUE);
			int iYTenthScaleLen = atoi(m_strYTenthScaleLen);
			m_IDescartesAxis->SetYAxisTenthScaleLineLen(iYTenthScaleLen);			
		}
		if(iID==1110)
		{
			UpdateData(TRUE);
			int iCenterLineWidth = atoi(m_strCenterLineWidth);
			m_IDescartesAxis->SetAxisCenterLineWidth(iCenterLineWidth);			
		}

		CRect rect = m_rectDescartesAxis;
		InvalidateRect(rect,true);
		
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CDescartesAxisDlg::SetFont()
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
		if(iID==1070)  
		{
			m_IDescartesAxis->SetAxisTitleFont(lfHeight,lfWidth,lfEscapement,lfOrientation
				,lfWeight,lfItalic,lfUnderline,lfStrikeOut,lfCharSet,lfOutPrecision
				,lfClipPrecision,lfQuality,lfPitchAndFamily,(_bstr_t)lfFaceName);
		}
		if (iID==1081)
		{
			m_IDescartesAxis->SetYAxisNameFont(lfHeight,lfWidth,lfEscapement,lfOrientation
				,lfWeight,lfItalic,lfUnderline,lfStrikeOut,lfCharSet,lfOutPrecision
				,lfClipPrecision,lfQuality,lfPitchAndFamily,(_bstr_t)lfFaceName);
		}
		if (iID==1082)
		{
			m_IDescartesAxis->SetXAxisNameFont(lfHeight,lfWidth,lfEscapement,lfOrientation
				,lfWeight,lfItalic,lfUnderline,lfStrikeOut,lfCharSet,lfOutPrecision
				,lfClipPrecision,lfQuality,lfPitchAndFamily,(_bstr_t)lfFaceName);
		}
		if (iID==1083)
		{
			m_IDescartesAxis->SetYAxisScaleFont(lfHeight,lfWidth,lfEscapement,lfOrientation
				,lfWeight,lfItalic,lfUnderline,lfStrikeOut,lfCharSet,lfOutPrecision
				,lfClipPrecision,lfQuality,lfPitchAndFamily,(_bstr_t)lfFaceName);
		}
		if (iID==1084)
		{
			m_IDescartesAxis->SetXAxisScaleFont(lfHeight,lfWidth,lfEscapement,lfOrientation
				,lfWeight,lfItalic,lfUnderline,lfStrikeOut,lfCharSet,lfOutPrecision
				,lfClipPrecision,lfQuality,lfPitchAndFamily,(_bstr_t)lfFaceName);
		}
		CRect rect = m_rectDescartesAxis;
		InvalidateRect(rect,true);
		
	}

}

void CDescartesAxisDlg::SetColor()
{
	COLORREF crColor = RGB(255,255,255);
	CColorDialog od(crColor,0,this);	
	if (od.DoModal()==IDOK)
	{
		COLORREF cr1=od.GetColor();
		HWND hWnd;
		hWnd =::GetFocus();
		int iID=::GetDlgCtrlID(hWnd);
		if(iID==1069) 
		{
			m_IDescartesAxis->SetAxisTitleFontColor((long)cr1);
		}
		if(iID==1071) 
		{
			m_IDescartesAxis->SetAxisBackColor((long)cr1);
		}
		if(iID==1072) 
		{
			m_IDescartesAxis->SetWorkAreaBorderLeftTopColor((long)cr1);
		}
		if(iID==1073) 
		{
			m_IDescartesAxis->SetWorkAreaBorderRightBottomColor((long)cr1);
		}
		if(iID==1076) 
		{
			m_IDescartesAxis->SetFrameLeftTopColor((long)cr1);
		}
		if(iID==1077) 
		{
			m_IDescartesAxis->SetFrameRightBottomColor((long)cr1);
		}
		if(iID==1079) 
		{
			m_IDescartesAxis->SetYUnitScaleColor((long)cr1);
		}
		if(iID==1080) 
		{
			m_IDescartesAxis->SetYUnitScaleShadowColor((long)cr1);
		}
		if(iID==1087) 
		{
			m_IDescartesAxis->SetYAxisNameFontColor((long)cr1);
		}
		if(iID==1088) 
		{
			m_IDescartesAxis->SetXAxisNameFontColor((long)cr1);
		}
		if(iID==1089) 
		{
			m_IDescartesAxis->SetYAxisScaleFontColor((long)cr1);
		}
		if(iID==1090) 
		{
			m_IDescartesAxis->SetXAxisScaleFontColor((long)cr1);
		}
		if(iID==1091) 
		{
			m_IDescartesAxis->SetYAxisGridLineColor((long)cr1);
		}
		if(iID==1092) 
		{
			m_IDescartesAxis->SetXAxisGridLineColor((long)cr1);
		}
		if(iID==1093) 
		{
			m_IDescartesAxis->SetYAxisTenthScaleColor((long)cr1);
		}
		if(iID==1094) 
		{
			m_IDescartesAxis->SetXAxisTenthScaleColor((long)cr1);
		}
		if(iID==1101) 
		{
			m_IDescartesAxis->SetXUnitScaleColor((long)cr1);
		}
		if(iID==1102) 
		{
			m_IDescartesAxis->SetXUnitScaleShadowColor((long)cr1);
		}
		if(iID==1109) 
		{
			m_IDescartesAxis->SetAxisCenterColor((long)cr1);
		}
		CRect rect = m_rectDescartesAxis;
		InvalidateRect(rect,true);
		
	}
}

void CDescartesAxisDlg::OnBtnColorDesaxistitle() 
{
	SetColor();
	
}

void CDescartesAxisDlg::OnBtnFontDesaxistitle() 
{
	SetFont();
	
}

void CDescartesAxisDlg::OnBtnColorDesaxisback() 
{
	SetColor();
	
}

void CDescartesAxisDlg::OnBtnColorDeslefttopborder() 
{
	SetColor();
	
}

void CDescartesAxisDlg::OnBtnColorDesrightbottomborder() 
{
	SetColor();
	
}

void CDescartesAxisDlg::OnBtnColorDesframelefttop() 
{
	SetColor();
	
}

void CDescartesAxisDlg::OnBtnColorDesframerightbottom() 
{
	SetColor();
	
}

void CDescartesAxisDlg::OnBtnColorDesyunitscale() 
{
	SetColor();
	
}

void CDescartesAxisDlg::OnBtnColorDesyunitscaleshadow() 
{
	SetColor();
	
}

void CDescartesAxisDlg::OnBtnFontDesyaxisname() 
{
	SetFont();
	
}

void CDescartesAxisDlg::OnBtnFontDesxaxisname() 
{
	SetFont();
	
}

void CDescartesAxisDlg::OnBtnFontDesyscale() 
{
	SetFont();
	
}

void CDescartesAxisDlg::OnBtnFontDesxscale() 
{
	SetFont();
	
}

void CDescartesAxisDlg::OnBtnColorDesyaxisname() 
{
	SetColor();
	
}

void CDescartesAxisDlg::OnBtnColorDesxaxisname() 
{
	SetColor();
	
}

void CDescartesAxisDlg::OnBtnColorDesyscalefont() 
{
	SetColor();
}

void CDescartesAxisDlg::OnBtnColorDesxscalefont() 
{
	SetColor();
	
}

void CDescartesAxisDlg::OnBtnColorDesygrid() 
{
	SetColor();
	
}

void CDescartesAxisDlg::OnBtnColorDesxgrid() 
{
	SetColor();
	
}

void CDescartesAxisDlg::OnBtnColorDesytenth() 
{
	SetColor();
	
}

void CDescartesAxisDlg::OnBtnColorDesxtenth() 
{
	SetColor();
	
}

void CDescartesAxisDlg::OnSelchangeComboDesbordershadow() 
{
	CString str="";
	m_cmbBorderShadow.GetWindowText(str);
	int iBorderShadow = atoi(str);
	m_IDescartesAxis->SetWorkAreaBorderShadow(iBorderShadow);
	CRect rect = m_rectDescartesAxis;
	InvalidateRect(rect,true);
	
	
}

void CDescartesAxisDlg::OnSelchangeComboDesframeshadow() 
{
	CString str="";
	m_cmbFrameShadow.GetWindowText(str);
	int iFrameShadow = atoi(str);
	m_IDescartesAxis->SetFrameShadow(iFrameShadow);
	CRect rect = m_rectDescartesAxis;
	InvalidateRect(rect,true);
	
}

void CDescartesAxisDlg::OnSelchangeComboDesygirdstyle() 
{
	CString str="";
	m_cmbYGridStyle.GetWindowText(str);
	if (str == "PS_SOLID") 
	{
		m_IDescartesAxis->SetYAxisGridLineStyle(PS_SOLID);
	}
	else if (str == "PS_DOT")
	{
		m_IDescartesAxis->SetYAxisGridLineStyle(PS_DOT);
	}
	else if (str == "PS_DASH") 
	{
		m_IDescartesAxis->SetYAxisGridLineStyle(PS_DASH);
	}
	else if (str == "PS_DASHDOT") 
	{
		m_IDescartesAxis->SetYAxisGridLineStyle(PS_DASHDOT);
	}
	else
	{
		m_IDescartesAxis->SetYAxisGridLineStyle(PS_DASHDOTDOT);
	}
	CRect rect = m_rectDescartesAxis;
	InvalidateRect(rect,true);
	
	
	
}

void CDescartesAxisDlg::OnSelchangeComboDesxgridstyle() 
{
	CString str="";
	m_cmbXGridStyle.GetWindowText(str);
	if (str == "PS_SOLID") 
	{
		m_IDescartesAxis->SetXAxisGridLineStyle(PS_SOLID);
	}
	else if (str == "PS_DOT")
	{
		m_IDescartesAxis->SetXAxisGridLineStyle(PS_DOT);
	}
	else if (str == "PS_DASH") 
	{
		m_IDescartesAxis->SetXAxisGridLineStyle(PS_DASH);
	}
	else if (str == "PS_DASHDOT") 
	{
		m_IDescartesAxis->SetXAxisGridLineStyle(PS_DASHDOT);
	}
	else
	{
		m_IDescartesAxis->SetXAxisGridLineStyle(PS_DASHDOTDOT);
	}
	CRect rect = m_rectDescartesAxis;
	InvalidateRect(rect,true);
	
}

void CDescartesAxisDlg::OnBtnColorDesxunitscale() 
{
	SetColor();
	
}

void CDescartesAxisDlg::OnBtnColorDesxunitscaleshadow() 
{
	SetColor();
	
}

void CDescartesAxisDlg::OnSelchangeComboDescenterlinestyle() 
{
	CString str="";
	m_cmbCenterLineStyle.GetWindowText(str);
	if (str == "PS_SOLID") 
	{
		m_IDescartesAxis->SetAxisCenterLineType(PS_SOLID);
	}
	else if (str == "PS_DOT")
	{
		m_IDescartesAxis->SetAxisCenterLineType(PS_DOT);
	}
	else if (str == "PS_DASH") 
	{
		m_IDescartesAxis->SetAxisCenterLineType(PS_DASH);
	}
	else if (str == "PS_DASHDOT") 
	{
		m_IDescartesAxis->SetAxisCenterLineType(PS_DASHDOT);
	}
	else
	{
		m_IDescartesAxis->SetAxisCenterLineType(PS_DASHDOTDOT);
	}
	CRect rect = m_rectDescartesAxis;
	InvalidateRect(rect,true);
	
}

void CDescartesAxisDlg::OnBtnColorCenterline() 
{
	SetColor();
	
}

void CDescartesAxisDlg::OnBtnZoomin() 
{
	m_IDescartesAxis->ZoomIn1(2);
	CRect rect = m_rectDescartesAxis;
	InvalidateRect(rect,true);
	
}

void CDescartesAxisDlg::OnBtnZoomout() 
{
	m_IDescartesAxis->ZoomOut(2);
	CRect rect = m_rectDescartesAxis;
	InvalidateRect(rect,true);
	
}
