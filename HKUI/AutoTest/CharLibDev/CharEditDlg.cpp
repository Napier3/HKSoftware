// CharEditDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CharLibDev.h"
#include "CharEditDlg.h"
#include "XLanguageResourceAts_CharLibDev.h"
#include "..\..\Module\Axis\AxisInterface.h"

// CCharEditDlg 对话框

IMPLEMENT_DYNAMIC(CCharEditDlg, CDialog)

CCharEditDlg::CCharEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCharEditDlg::IDD, pParent)
	, m_strName(_T(""))
	, m_strID(_T(""))
	, m_nAxis(0)
	, m_nSearchLineMode(0)
{
	m_pCharTemp = NULL;
	m_pCurrFolder = NULL;
}

CCharEditDlg::~CCharEditDlg()
{
}

void CCharEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_ID, m_strID);
	DDX_Radio(pDX, IDC_RADIO_DECARTES, m_nAxis);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Radio(pDX, IDC_RADIO_SL_PLUMB, m_nSearchLineMode);
	DDX_Control(pDX, IDC_EDIT_XMIN, m_edtXMin);
	DDX_Control(pDX, IDC_EDIT_XMAX, m_edtXMax);
	DDX_Control(pDX, IDC_EDIT_YMIN, m_edtYMin);
	DDX_Control(pDX, IDC_EDIT_YMAX, m_edtYMax);
	DDX_Text(pDX, IDC_EDIT_XMIN, m_strXMin);
	DDX_Text(pDX, IDC_EDIT_XMAX, m_strXMax);
	DDX_Text(pDX, IDC_EDIT_YMIN, m_strYMin);
	DDX_Text(pDX, IDC_EDIT_YMAX, m_strYMax);

	DDX_Control(pDX, IDC_STATIC_CHARNAME, m_wndCharName);
	DDX_Control(pDX, IDC_STATIC_CHARMARKING, m_wndCharMarking);
	DDX_Control(pDX, IDC_STATIC_CHARCOORDIN, m_xFrameCharSystem);
	DDX_Control(pDX, IDC_STATIC_CHARSEARMODE, m_xFrameSearchLineMode);
	DDX_Control(pDX, IDC_RADIO_DECARTES, m_btnDecSystem);
	DDX_Control(pDX, IDC_RADIO_POLOR, m_btnPolarSystem);
	DDX_Control(pDX, IDC_RADIO_LOG, m_btnLogSystem);
	DDX_Control(pDX, IDC_RADIO_SL_PLUMB, m_btnVertical);
	DDX_Control(pDX, IDC_RADIO_SL_VERT, m_btnVerticalLine);
	DDX_Control(pDX, IDC_RADIO_SL_HORZ, m_btnHorizontalLine);
	DDX_Control(pDX, IDCANCEL, m_btnCharCancel);
	DDX_Control(pDX, IDC_EDIT_NAME, m_edtCharName);
	DDX_Control(pDX, IDC_EDIT_ID, m_edtCharMarking);
}


BEGIN_MESSAGE_MAP(CCharEditDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIO_DECARTES, &CCharEditDlg::OnBnClickedRadioDecartes)
	ON_BN_CLICKED(IDC_RADIO_POLOR, &CCharEditDlg::OnBnClickedRadioPolor)
	ON_BN_CLICKED(IDC_RADIO_LOG, &CCharEditDlg::OnBnClickedRadioLog)
	ON_EN_CHANGE(IDC_EDIT_NAME, &CCharEditDlg::OnEnChangeEditName)
	ON_EN_CHANGE(IDC_EDIT_ID, &CCharEditDlg::OnEnChangeEditId)
END_MESSAGE_MAP()


// CCharEditDlg 消息处理程序
void CCharEditDlg::InitImageList()
{
	m_CharLibViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_CLASS_VIEW_24 : IDB_CLASS_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_CharLibViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_CharLibViewImages.Add(&bmp, RGB(255, 0, 0));
}

void CCharEditDlg::xlang_InitAndAdjust()
{
	if (xlang_IsCurrXLanguageChinese())
	{
		return;
	}

	m_wndCharName.SetLanguageID(g_sLangID_Name);
	m_wndCharMarking.SetLanguageID(g_sLangID_Marking);
	m_xFrameCharSystem.SetLanguageID(g_sLangID_CoordinateSystem);
	m_xFrameSearchLineMode.SetLanguageID(g_sLangID_SearchLineMode);
	m_btnDecSystem.SetLanguageID(g_sLangID_DecSystem);
	m_btnPolarSystem.SetLanguageID(g_sLangID_PolarSystem);
	m_btnLogSystem.SetLanguageID(g_sLangID_LogSystem);
	m_btnVertical.SetLanguageID(g_sLangID_Vertical);
	m_btnVerticalLine.SetLanguageID(g_sLangID_VerticalLine);
	m_btnHorizontalLine.SetLanguageID(g_sLangID_HorizontalLine);
	m_btnOK.SetLanguageID(g_sLangID_OK);
	m_btnCharCancel.SetLanguageID(g_sLangID_Cancel);

	CXLangWndAdjMngr oWndAdjMngr; 
	oWndAdjMngr.FreeAdjMngr();                      
	CXLangWndAdjFrame *pXAdjFrame = NULL; 


	oWndAdjMngr.RegisterCols(); 
	oWndAdjMngr.RegisterCol();
	oWndAdjMngr.RegisterXWnd(&m_wndCharName);
	oWndAdjMngr.RegisterXWnd(&m_wndCharMarking);
	oWndAdjMngr.RegisterCol();
	oWndAdjMngr.RegisterWnd(&m_edtCharName);
	oWndAdjMngr.RegisterWnd(&m_edtCharMarking);
	

	oWndAdjMngr.RegisterCol();                      
	pXAdjFrame = oWndAdjMngr.RegisterXFrame(&m_xFrameCharSystem);  
	pXAdjFrame->RegisterCol();  
	pXAdjFrame->RegisterXWnd(&m_btnDecSystem);   
	pXAdjFrame->RegisterXWnd(&m_btnPolarSystem);  
	pXAdjFrame->RegisterXWnd(&m_btnLogSystem);  
    oWndAdjMngr.Adjust(this, TRUE);
	oWndAdjMngr.RegisterCol();                      
	pXAdjFrame = oWndAdjMngr.RegisterXFrame(&m_xFrameCharSystem);  
	pXAdjFrame->RegisterCol();  
	pXAdjFrame->RegisterXWnd(&m_btnVertical);   
	pXAdjFrame->RegisterXWnd(&m_btnVerticalLine);  
	pXAdjFrame->RegisterXWnd(&m_btnHorizontalLine);  
	oWndAdjMngr.Adjust(this, TRUE);
	xlang_InitByLgugStr(g_sLangID_CharCurve, this);
}


BOOL CCharEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitImageList();

	SetWindowText(m_strTitle);
	ASSERT (m_pCharTemp != NULL);
	m_strAxis = m_pCharTemp->m_strAxis;
	m_strTestLineMode = m_pCharTemp->m_strTestLineMode;

	m_nAxis = axis_GetAxisIndex(m_strAxis);
	m_nSearchLineMode = char_GetTestLineModeIndex(m_strTestLineMode);

	m_strName = m_pCharTemp->m_strName;
	m_strID   = m_pCharTemp->m_strID;
	m_strXMin = m_pCharTemp->m_strXMin;
	m_strXMax = m_pCharTemp->m_strXMax;
	m_strYMin = m_pCharTemp->m_strYMin;
	m_strYMax = m_pCharTemp->m_strYMax;

	UpdateData(FALSE);

// 	if (m_pCurrFolder != NULL)
// 	{
// 		//m_treeFolder.SelectItem((HTREEITEM)m_pCurrFolder->m_dwItemData);
// 		m_treeFolder.EnableWindow(FALSE);
// 	}

	EnableOKButton();
	EnableMinMax();

	xlang_InitAndAdjust();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CCharEditDlg::OnBnClickedRadioDecartes()
{
	EnableOKButton();
	EnableMinMax();
}

void CCharEditDlg::OnBnClickedRadioPolor()
{
	EnableOKButton();
	EnableMinMax();
}

void CCharEditDlg::OnBnClickedRadioLog()
{
	EnableOKButton();
	EnableMinMax();
}

void CCharEditDlg::OnOK()
{
	UpdateData(TRUE);

	m_strAxis = axis_GetAxisID(m_nAxis);
	m_strTestLineMode = char_GetTestLineModeID(m_nSearchLineMode);

	ASSERT (m_pCurrFolder != NULL);
	CString strMsg;
	
	CExBaseObject *pFind = m_pCurrFolder->FindCharTempByName(m_strName);

	if (pFind != NULL)
	{
		if (pFind != m_pCharTemp)
		{
			strMsg.Format(g_sLangTxt_ExistNameCurve/*_T("存在名称为“%s”的曲线")*/, m_strName);
			MessageBox(strMsg, g_sLangTxt_Message1/*_T("提示")*/, MB_OK | MB_ICONERROR);
			return;
		}
	}

	pFind = m_pCurrFolder->FindCharTempByName(m_strName);

	if (pFind != NULL)
	{
		if (pFind != m_pCharTemp)
		{
			strMsg.Format(g_sLangTxt_ExistNameCurve/*_T("存在名称为“%s”的曲线")*/, m_strName);
			MessageBox(strMsg, g_sLangTxt_Message1/*_T("提示")*/, MB_OK | MB_ICONERROR);
			return;
		}
	}

	CDialog::OnOK();
}

void CCharEditDlg::EnableMinMax()
{
	switch (m_nAxis)
	{
	case AXIS_TYPE_INDEX_CARTES:
		m_edtXMin.EnableWindow(TRUE);
		m_edtXMax.EnableWindow(TRUE);
		m_edtYMin.EnableWindow(TRUE);
		m_edtYMax.EnableWindow(TRUE);
		break;

	case AXIS_TYPE_INDEX_POLAR:
		m_edtXMin.EnableWindow(FALSE);
		m_edtXMax.EnableWindow(FALSE);
		m_edtYMin.EnableWindow(FALSE);
		m_edtYMax.EnableWindow(FALSE);
		break;

	case AXIS_TYPE_INDEX_LOGARITHM:
		m_edtXMin.EnableWindow(TRUE);
		m_edtXMax.EnableWindow(TRUE);
		m_edtYMin.EnableWindow(TRUE);
		m_edtYMax.EnableWindow(TRUE);
		break;

	}
}

void CCharEditDlg::EnableOKButton()
{
	UpdateData(TRUE);

// 	if (m_pCurrFolder == NULL)
// 	{
// 		m_btnOK.EnableWindow(FALSE);
// 		return;
// 	}

	if (m_strName.GetLength() == 0)
	{
		m_btnOK.EnableWindow(FALSE);
		return;
	}

	if (m_strID.GetLength() == 0)
	{
		m_btnOK.EnableWindow(FALSE);
		return;
	}

	m_btnOK.EnableWindow(TRUE);
}
void CCharEditDlg::OnEnChangeEditName()
{
	EnableOKButton();
}

void CCharEditDlg::OnEnChangeEditId()
{
	EnableOKButton();
}
