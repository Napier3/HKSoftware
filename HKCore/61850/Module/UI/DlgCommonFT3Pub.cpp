// Dlg92DataQuality.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgCommonFT3Pub.h"

#include "..\..\..\Module\System\TickCount32.h"

BOOL CDlgCommonFT3Pub::m_bHasShowDlg = FALSE;

// CDlgCommonFT3Pub 对话框

CDlgCommonFT3Pub::CDlgCommonFT3Pub(CWnd* pParent /*=NULL*/)
	: CDynDialogEx(pParent)
{
	m_dwValue = 0;
}

CDlgCommonFT3Pub::~CDlgCommonFT3Pub()
{
}

void CDlgCommonFT3Pub::DoDataExchange(CDataExchange* pDX)
{
	CDynDialogEx::DoDataExchange(pDX);
		
	if (!m_bHasInitDialog)
	{
		return;
	}
	
	for (int nIndex = 0;nIndex<IECCFG_COMMON_FT3_BIT_NUM;nIndex++)
	{
		DDX_Control(pDX, IECFG_IDC_CMB_BIT0_TITLE + nIndex, m_stcBitValue[nIndex]);
		DDX_Control(pDX, IECFG_IDC_CMB_BIT0 + nIndex, m_cmbBitValue[nIndex]);
	}

	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CDlgCommonFT3Pub, CDynDialogEx)
END_MESSAGE_MAP()


// CDlgCommonFT3Pub 消息处理程序

void CDlgCommonFT3Pub::InitDialog()
{
	CTickCount32 oTick32;
	CDataType *pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(g_strGsChDtID_goose_out_ch_single_def_value);

	for (int nIndex = 0;nIndex<IECCFG_COMMON_FT3_BIT_NUM;nIndex++)
	{
		m_cmbBitValue[nIndex].ShowDataType(pDataType);
	}

	ShowQuality();

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("InitDialog=%d"), oTick32.GetTickCountLong());
	m_btnOK.EnableWindow(TRUE);
	m_btnCancel.EnableWindow(TRUE);
}

void CDlgCommonFT3Pub::ShowQuality()
{
	for (int nIndex = 0;nIndex<IECCFG_COMMON_FT3_BIT_NUM;nIndex++)
	{
		m_cmbBitValue[nIndex].SetSelByIndex((m_dwValue>>nIndex)%2);
	}
}

void CDlgCommonFT3Pub::SaveQuality()
{
	m_dwValue = 0;

	for (int nIndex = 0;nIndex<IECCFG_COMMON_FT3_BIT_NUM;nIndex++)
	{
		m_dwValue += (m_cmbBitValue[nIndex].GetSelectIndex2()<<nIndex);
	}
}

void CDlgCommonFT3Pub::CreateControls()
{
	CString strText;
	long nGapLenth = 28,nGapIndex = 0;

	for (int nIndex = 0;nIndex<IECCFG_COMMON_FT3_BIT_NUM ;nIndex++)
	{
		strText.Format(_T("Bit[%d]"),nIndex);
		nGapIndex = nIndex%8;

		if (nIndex/8 == 0)
		{
			CreateStatic(m_stcBitValue[nIndex], strText,  CRect(10,12 + nGapLenth*nGapIndex, 42,32 + nGapLenth*nGapIndex),
				IECFG_IDC_CMB_BIT0_TITLE+nIndex, this,EXSTYLE_STATIC, STYLE_STATIC_RIGHT);
			CreateComboBox_DropList(m_cmbBitValue[nIndex],    CRect(57,12 + nGapLenth*nGapIndex, 155,122 + nGapLenth*nGapIndex), IECFG_IDC_CMB_BIT0+nIndex, this);
		} 
		else
		{
			CreateStatic(m_stcBitValue[nIndex], strText,  CRect(165,12 + nGapLenth*nGapIndex, 197,32 + nGapLenth*nGapIndex), 
				IECFG_IDC_CMB_BIT0_TITLE+nIndex, this,EXSTYLE_STATIC, STYLE_STATIC_RIGHT);
			CreateComboBox_DropList(m_cmbBitValue[nIndex],     CRect(212,12 + nGapLenth*nGapIndex, 310,122 + nGapLenth*nGapIndex), IECFG_IDC_CMB_BIT0+nIndex, this);
		}

		m_stcBitValue[nIndex].SetFont(g_pGlobalFont11);
		m_cmbBitValue[nIndex].SetFont(g_pGlobalFont11);
	}

	CreateButton(m_btnOK, _T("确定"),     CRect(83,240,155,261), IDOK, this);
	CreateButton(m_btnCancel, _T("取消"), CRect(165,240,237,261), IDCANCEL, this);

	m_btnOK.SetFont(g_pGlobalFont11);
	m_btnCancel.SetFont(g_pGlobalFont11);
}


BOOL CDlgCommonFT3Pub::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();

	CreateControls();
	InitDialog();
	MoveWindow(CRect( 0, 0, 330, 300), TRUE);
	CenterWindow();
	SetWindowText(_T("FT3发布参数设置"));

	m_bHasInitDialog = TRUE;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgCommonFT3Pub::OnOK()
{
	UpdateData(TRUE);
	
	SaveQuality();
	CDynDialogEx::OnOK();
}

void CDlgCommonFT3Pub::OnCancel()
{
	CDynDialogEx::OnCancel();
}

void CDlgCommonFT3Pub::ShowHexQuality()
{
	if (!m_bHasInitDialog)
	{
		return;
	}

	SaveQuality();
}

