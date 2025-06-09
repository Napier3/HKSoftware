// Dlg92DataQuality.cpp : 实现文件
//

#include "stdafx.h"
#include "Dlg92DataQuality.h"

#include "..\..\..\Module\System\TickCount32.h"

BOOL CDlg92DataQuality::m_bHasShowDlg = FALSE;
// CDlg92DataQuality 对话框

CDlg92DataQuality::CDlg92DataQuality(CWnd* pParent /*=NULL*/)
	: CDynDialogEx(pParent)
{
	m_pInitThread = NULL;
	m_dwQuality = 0;
	m_bEditAll = 0;
}

CDlg92DataQuality::~CDlg92DataQuality()
{
}

void CDlg92DataQuality::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);
		
	if (!m_bHasInitDialog)
	{
		return;
	}
	
	DDX_Control(pDX, IECFG_IDC_CMB_VALIDITY, m_cmbValidity);
	DDX_Control(pDX, IECFG_IDC_CMB_OVERFLOW, m_cmbOverflow);
	DDX_Control(pDX, IECFG_IDC_CMB_OUTOFRANGE, m_cmbOutOfRange);
	DDX_Control(pDX, IECFG_IDC_CMB_BADREFRENCE, m_cmbBadReference);
	DDX_Control(pDX, IECFG_IDC_CMB_OCILLATORY, m_cmbOscillatory);
	DDX_Control(pDX, IECFG_IDC_CMB_FAILURE, m_cmbFailure);
	DDX_Control(pDX, IECFG_IDC_CMB_OLDDATA, m_cmbOldData);
	DDX_Control(pDX, IECFG_IDC_CMB_INCONSISTENT, m_cmbInconsistent);
	DDX_Control(pDX, IECFG_IDC_CMB_INACCURATE, m_cmbInaccurate);
	DDX_Control(pDX, IECFG_IDC_CMB_SOURCE, m_cmbSource);
	DDX_Control(pDX, IECFG_IDC_CMB_TEST, m_cmbTest);
	DDX_Control(pDX, IECFG_IDC_CMB_OPB, m_cmbOpb);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IECFG_IDC_EDIT_QUALITY, m_hexQuality);
}


BEGIN_MESSAGE_MAP(CDlg92DataQuality, CDynDialogEx)
	ON_EN_CHANGE(IECFG_IDC_EDIT_QUALITY, &CDlg92DataQuality::OnEnChangeEditquality)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_VALIDITY, &CDlg92DataQuality::OnCbnSelchangeCmbValidity)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_OVERFLOW, &CDlg92DataQuality::OnCbnSelchangeCmbOverflow)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_OUTOFRANGE, &CDlg92DataQuality::OnCbnSelchangeCmbOutofrange)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_BADREFRENCE, &CDlg92DataQuality::OnCbnSelchangeCmbBadrefrence)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_OCILLATORY, &CDlg92DataQuality::OnCbnSelchangeCmbOcillatory)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_FAILURE, &CDlg92DataQuality::OnCbnSelchangeCmbFailure)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_OLDDATA, &CDlg92DataQuality::OnCbnSelchangeCmbOlddata)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_INCONSISTENT, &CDlg92DataQuality::OnCbnSelchangeCmbInconsistent)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_INACCURATE, &CDlg92DataQuality::OnCbnSelchangeCmbInaccurate)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_SOURCE, &CDlg92DataQuality::OnCbnSelchangeCmbSource)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_TEST, &CDlg92DataQuality::OnCbnSelchangeCmbTest)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_OPB, &CDlg92DataQuality::OnCbnSelchangeCmbOpb)
	ON_BN_CLICKED(IECFG_IDC_BUTTON_SET, &CDlg92DataQuality::OnBnClickedButtonSet)
END_MESSAGE_MAP()


// CDlg92DataQuality 消息处理程序

void CDlg92DataQuality::InitDialog()
{
	CTickCount32 oTick32;

	m_cmbValidity.ShowDataType(      CCfgDataMngrConstGlobal::FindIecRtdDataType(_T("validity")));
	m_cmbOverflow.ShowDataType(      CCfgDataMngrConstGlobal::FindIecRtdDataType(_T("overflow")));
	m_cmbOutOfRange.ShowDataType(    CCfgDataMngrConstGlobal::FindIecRtdDataType(_T("outofrange")));
	m_cmbBadReference.ShowDataType(  CCfgDataMngrConstGlobal::FindIecRtdDataType(_T("badreference")));
	m_cmbOscillatory.ShowDataType(   CCfgDataMngrConstGlobal::FindIecRtdDataType(_T("oscillatory")));
	m_cmbFailure.ShowDataType(       CCfgDataMngrConstGlobal::FindIecRtdDataType(_T("failure")));
	m_cmbOldData.ShowDataType(       CCfgDataMngrConstGlobal::FindIecRtdDataType(_T("olddata")));
	m_cmbInconsistent.ShowDataType(  CCfgDataMngrConstGlobal::FindIecRtdDataType(_T("inconsistent")));
	m_cmbInaccurate.ShowDataType(    CCfgDataMngrConstGlobal::FindIecRtdDataType(_T("inaccurate")));
	m_cmbSource.ShowDataType(        CCfgDataMngrConstGlobal::FindIecRtdDataType(_T("source")));
	m_cmbTest.ShowDataType(          CCfgDataMngrConstGlobal::FindIecRtdDataType(_T("test")));
	m_cmbOpb.ShowDataType(           CCfgDataMngrConstGlobal::FindIecRtdDataType(_T("OPB")));

	ShowQuality();

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("InitDialog=%d"), oTick32.GetTickCountLong());
	m_btnOK.EnableWindow(TRUE);
	m_btnCancel.EnableWindow(TRUE);
}

void CDlg92DataQuality::ShowQuality()
{
	CIecCfg92ChQuality oQuality;
	oQuality.SetQuality(m_dwQuality);

	m_cmbValidity.SetSelByIndex(oQuality.m_nValidity);
	m_cmbOverflow.SetSelByIndex(oQuality.m_nOverflow);
	m_cmbOutOfRange.SetSelByIndex(oQuality.m_nOutOfRange);
	m_cmbBadReference.SetSelByIndex(oQuality.m_nBadReference);
	m_cmbOscillatory.SetSelByIndex(oQuality.m_nOscillation);
	m_cmbFailure.SetSelByIndex(oQuality.m_nFailure);
	m_cmbOldData.SetSelByIndex(oQuality.m_nOldData);
	m_cmbInconsistent.SetSelByIndex(oQuality.m_nInconsistent);
	m_cmbInaccurate.SetSelByIndex(oQuality.m_nInaccurate);
	m_cmbSource.SetSelByIndex(oQuality.m_nSource);
	m_cmbTest.SetSelByIndex(oQuality.m_nTest);
	m_cmbOpb.SetSelByIndex(oQuality.m_nOPB);
}

void CDlg92DataQuality::SaveQuality()
{
	CIecCfg92ChQuality oQuality;

	oQuality.m_nValidity = m_cmbValidity.GetSelectIndex2();
	oQuality.m_nOverflow = m_cmbOverflow.GetSelectIndex2();
	oQuality.m_nOutOfRange = m_cmbOutOfRange.GetSelectIndex2();
	oQuality.m_nBadReference = m_cmbBadReference.GetSelectIndex2();
	oQuality.m_nOscillation = m_cmbOscillatory.GetSelectIndex2();
	oQuality.m_nFailure = m_cmbFailure.GetSelectIndex2();
	oQuality.m_nOldData = m_cmbOldData.GetSelectIndex2();
	oQuality.m_nInconsistent = m_cmbInconsistent.GetSelectIndex2();
	oQuality.m_nInaccurate = m_cmbInaccurate.GetSelectIndex2();
	oQuality.m_nSource = m_cmbSource.GetSelectIndex2();
	oQuality.m_nTest = m_cmbTest.GetSelectIndex2();
	oQuality.m_nOPB = m_cmbOpb.GetSelectIndex2();

	m_dwQuality = oQuality.GetQuality();
}

UINT CDlg92DataQuality::InitDialogThread(LPVOID lpPara)
{
	CDlg92DataQuality *pDlg = (CDlg92DataQuality*)lpPara;
	pDlg->InitDialog();
	pDlg->m_pInitThread = NULL;
	return 0;
}

void CDlg92DataQuality::CreateControls()
{
	CreateStatic(m_stcValidity,  _T("Validity(有效)[bit0-bit1]"),  CRect(10,12, 142,32), IECFG_IDC_CMB_VALIDITY_TITLE, this,EXSTYLE_STATIC, STYLE_STATIC_RIGHT);
	CreateStatic(m_stcOutOfRange,  _T("OutOfrange(超值域)[bit3]"), CRect(10,40, 142,60), IECFG_IDC_CMB_OUTOFRANGE_TITLE, this,EXSTYLE_STATIC, STYLE_STATIC_RIGHT);
	CreateStatic(m_stcOscillatory,  _T("Oscillatory(抖动)[bit5]"), CRect(10,68, 142,88), IECFG_IDC_CMB_OCILLATORY_TITLE, this,EXSTYLE_STATIC, STYLE_STATIC_RIGHT);
	CreateStatic(m_stcOldData,  _T("OldData(旧数据)[bit7]"),       CRect(10,96, 142,116), IECFG_IDC_CMB_OLDDATA_TITLE, this,EXSTYLE_STATIC, STYLE_STATIC_RIGHT);
	CreateStatic(m_stcInaccurate,  _T("Inaccurate(不精确)[bit9]"), CRect(10,124,142,144), IECFG_IDC_CMB_INACCURATE_TITLE, this,EXSTYLE_STATIC, STYLE_STATIC_RIGHT);
	CreateStatic(m_stcTest,  _T("Test(测试)[bit11]"),              CRect(10,152,142,172), IECFG_IDC_CMB_TEST_TITLE, this,EXSTYLE_STATIC, STYLE_STATIC_RIGHT);

	CreateStatic(m_stcOverflow,  _T("Overflow(溢出)[bit2]"),             CRect(265,12 ,415,32), IECFG_IDC_CMB_OVERFLOW_TITLE, this,EXSTYLE_STATIC, STYLE_STATIC_RIGHT);
	CreateStatic(m_stcBadReference,  _T("BadReference(坏基准值)[bit4]"), CRect(265,40 ,415,60), IECFG_IDC_CMB_BADREFRENCE_TITLE, this,EXSTYLE_STATIC, STYLE_STATIC_RIGHT);
	CreateStatic(m_stcFailure,  _T("Failure(故障)[bit6]"),               CRect(265,68, 415,88), IECFG_IDC_CMB_FAILURE_TITLE, this,EXSTYLE_STATIC, STYLE_STATIC_RIGHT);
	CreateStatic(m_stcInconsistent,  _T("Inconsistent(不一致)[bit8]"),   CRect(265,96, 415,116), IECFG_IDC_CMB_INCONSISTENT_TITLE, this,EXSTYLE_STATIC, STYLE_STATIC_RIGHT);
	CreateStatic(m_stcSource,  _T("Source(源)[bit10]"),                  CRect(265,124,415,144), IECFG_IDC_CMB_SOURCE_TITLE, this,EXSTYLE_STATIC, STYLE_STATIC_RIGHT);
	CreateStatic(m_stcOpb,  _T("Opb(操作员闭锁)[bit12]"),                CRect(265,152,415,172), IECFG_IDC_CMB_OPB_TITLE, this,EXSTYLE_STATIC, STYLE_STATIC_RIGHT);

	CreateComboBox_DropList(m_cmbValidity,    CRect(157,12, 255,122), IECFG_IDC_CMB_VALIDITY, this);
	CreateComboBox_DropList(m_cmbOutOfRange,  CRect(157,40, 255,152), IECFG_IDC_CMB_OUTOFRANGE, this);
	CreateComboBox_DropList(m_cmbOscillatory, CRect(157,68, 255,178), IECFG_IDC_CMB_OCILLATORY, this);
	CreateComboBox_DropList(m_cmbOldData,     CRect(157,96, 255,206), IECFG_IDC_CMB_OLDDATA, this);
	CreateComboBox_DropList(m_cmbInaccurate,  CRect(157,124,255,234), IECFG_IDC_CMB_INACCURATE, this);
	CreateComboBox_DropList(m_cmbTest,        CRect(157,152,255,262), IECFG_IDC_CMB_TEST, this);

	CreateComboBox_DropList(m_cmbOverflow,     CRect(427,12, 525,122), IECFG_IDC_CMB_OVERFLOW, this);
	CreateComboBox_DropList(m_cmbBadReference, CRect(427,40, 525,152), IECFG_IDC_CMB_BADREFRENCE, this);
	CreateComboBox_DropList(m_cmbFailure,      CRect(427,68, 525,178), IECFG_IDC_CMB_FAILURE, this);
	CreateComboBox_DropList(m_cmbInconsistent, CRect(427,96, 525,206), IECFG_IDC_CMB_INCONSISTENT, this);
	CreateComboBox_DropList(m_cmbSource,       CRect(427,124,525,234), IECFG_IDC_CMB_SOURCE, this);
	CreateComboBox_DropList(m_cmbOpb,          CRect(427,152,525,262), IECFG_IDC_CMB_OPB, this);

	CreateButton(m_btnOK, _T("确定"),     CRect(370,185,442,206), IDOK, this);
	CreateButton(m_btnCancel, _T("取消"), CRect(452,185,524,206), IDCANCEL, this);
	CreateButton(m_btnSet, _T("直接设置"), CRect(255,185,327,206), IECFG_IDC_BUTTON_SET, this);
	CreateCheckBox(m_btnCheckAll, _T("修改全部通道"), CRect(10,185,105,206), IECFG_IDC_BUTTON_SET, this);
	CreateEdit(m_hexQuality, CRect(166,185,251,206), IECFG_IDC_EDIT_QUALITY, this, EXSTYLE_EDIT, STYLE_EDIT);

	m_cmbValidity.SetFont(g_pGlobalFont11);
	m_cmbOverflow.SetFont(g_pGlobalFont11);
	m_cmbOutOfRange.SetFont(g_pGlobalFont11);
	m_cmbBadReference.SetFont(g_pGlobalFont11);
	m_cmbOscillatory.SetFont(g_pGlobalFont11);
	m_cmbFailure.SetFont(g_pGlobalFont11);
	m_cmbOldData.SetFont(g_pGlobalFont11);
	m_cmbInconsistent.SetFont(g_pGlobalFont11);
	m_cmbInaccurate.SetFont(g_pGlobalFont11);
	m_cmbSource.SetFont(g_pGlobalFont11);
	m_cmbTest.SetFont(g_pGlobalFont11);
	m_cmbOpb.SetFont(g_pGlobalFont11);

	m_stcValidity.SetFont(g_pGlobalFont11);
	m_stcOverflow.SetFont(g_pGlobalFont11);
	m_stcOutOfRange.SetFont(g_pGlobalFont11);
	m_stcBadReference.SetFont(g_pGlobalFont11);
	m_stcOscillatory.SetFont(g_pGlobalFont11);
	m_stcFailure.SetFont(g_pGlobalFont11);
	m_stcOldData.SetFont(g_pGlobalFont11);
	m_stcInconsistent.SetFont(g_pGlobalFont11);
	m_stcInaccurate.SetFont(g_pGlobalFont11);
	m_stcSource.SetFont(g_pGlobalFont11);
	m_stcTest.SetFont(g_pGlobalFont11);
	m_stcOpb.SetFont(g_pGlobalFont11);

	m_btnOK.SetFont(g_pGlobalFont11);
	m_btnCancel.SetFont(g_pGlobalFont11);
	m_btnCheckAll.SetFont(g_pGlobalFont11);
	m_btnSet.SetFont(g_pGlobalFont11);
	m_hexQuality.SetFont(g_pGlobalFont11);

}


BOOL CDlg92DataQuality::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();

	CreateControls();
	InitDialog();
	m_hexQuality.Init(2);
	m_hexQuality.SetValue(m_dwQuality);
	//m_pInitThread = AfxBeginThread(InitDialogThread, this);
	//m_pInitThread->m_bAutoDelete = TRUE;

	MoveWindow(CRect( 0, 0, 552, 256), TRUE);
	CenterWindow();
	SetWindowText(_T("品质参数设置"));

	m_bHasInitDialog = TRUE;

	WORD wValue = m_dwQuality;
	m_hexQuality.SetValue(wValue);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlg92DataQuality::OnOK()
{
	UpdateData(TRUE);
	
	SaveQuality();
	m_bEditAll = m_btnCheckAll.GetCheck();

	CDynDialogEx::OnOK();
}

void CDlg92DataQuality::OnCancel()
{
	if (m_pInitThread != NULL)
	{
		return;
	}

	CDynDialogEx::OnCancel();
}

void CDlg92DataQuality::OnEnChangeEditquality()
{
	
}

void CDlg92DataQuality::OnCbnSelchangeCmbValidity()
{
	ShowHexQuality();
}

void CDlg92DataQuality::OnCbnSelchangeCmbOverflow()
{
	ShowHexQuality();
}

void CDlg92DataQuality::OnCbnSelchangeCmbOutofrange()
{
	ShowHexQuality();
}

void CDlg92DataQuality::OnCbnSelchangeCmbBadrefrence()
{
	ShowHexQuality();
}

void CDlg92DataQuality::OnCbnSelchangeCmbOcillatory()
{
	ShowHexQuality();
}

void CDlg92DataQuality::OnCbnSelchangeCmbFailure()
{
	ShowHexQuality();
}

void CDlg92DataQuality::OnCbnSelchangeCmbOlddata()
{
	ShowHexQuality();
}

void CDlg92DataQuality::OnCbnSelchangeCmbInconsistent()
{
	ShowHexQuality();
}

void CDlg92DataQuality::OnCbnSelchangeCmbInaccurate()
{
	ShowHexQuality();
}

void CDlg92DataQuality::OnCbnSelchangeCmbSource()
{
	ShowHexQuality();
}

void CDlg92DataQuality::OnCbnSelchangeCmbTest()
{
	ShowHexQuality();
}

void CDlg92DataQuality::OnCbnSelchangeCmbOpb()
{
	ShowHexQuality();
}

void CDlg92DataQuality::ShowHexQuality()
{
	if (!m_bHasInitDialog)
	{
		return;
	}

	SaveQuality();
	WORD wValue = m_dwQuality;
	m_hexQuality.SetValue(wValue);
}


void CDlg92DataQuality::OnBnClickedButtonSet()
{
	WORD wValue = 0;
	m_hexQuality.GetValue(wValue);
	m_dwQuality = wValue;
	ShowQuality();
}
