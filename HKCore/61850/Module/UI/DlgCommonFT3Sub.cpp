#include "stdafx.h"
#include "DlgCommonFT3Sub.h"

#include "..\..\..\Module\System\TickCount32.h"
#include "..\..\..\Module\MemBuffer\EquationBuffer.h"

// CDlgCommonFT3Sub 对话框

CDlgCommonFT3Sub::CDlgCommonFT3Sub(CWnd* pParent /*=NULL*/)
	: CDlgCommonFT3Pub(pParent)
{
	m_pCfg6044CommonCh = NULL;
}

CDlgCommonFT3Sub::~CDlgCommonFT3Sub()
{
}

void CDlgCommonFT3Sub::DoDataExchange(CDataExchange* pDX)
{
	CDlgCommonFT3Pub::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlgCommonFT3Sub, CDynDialogEx)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_BIT0, &CDlgCommonFT3Sub::OnCbnSelchangeComboxBit0)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_BIT1, &CDlgCommonFT3Sub::OnCbnSelchangeComboxBit1)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_BIT2, &CDlgCommonFT3Sub::OnCbnSelchangeComboxBit2)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_BIT3, &CDlgCommonFT3Sub::OnCbnSelchangeComboxBit3)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_BIT4, &CDlgCommonFT3Sub::OnCbnSelchangeComboxBit4)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_BIT5, &CDlgCommonFT3Sub::OnCbnSelchangeComboxBit5)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_BIT6, &CDlgCommonFT3Sub::OnCbnSelchangeComboxBit6)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_BIT7, &CDlgCommonFT3Sub::OnCbnSelchangeComboxBit7)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_BIT8, &CDlgCommonFT3Sub::OnCbnSelchangeComboxBit8)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_BIT9, &CDlgCommonFT3Sub::OnCbnSelchangeComboxBit9)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_BIT10, &CDlgCommonFT3Sub::OnCbnSelchangeComboxBit10)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_BIT11, &CDlgCommonFT3Sub::OnCbnSelchangeComboxBit11)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_BIT12, &CDlgCommonFT3Sub::OnCbnSelchangeComboxBit12)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_BIT13, &CDlgCommonFT3Sub::OnCbnSelchangeComboxBit13)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_BIT14, &CDlgCommonFT3Sub::OnCbnSelchangeComboxBit14)
	ON_CBN_SELCHANGE(IECFG_IDC_CMB_BIT15, &CDlgCommonFT3Sub::OnCbnSelchangeComboxBit15)
END_MESSAGE_MAP()


// CDlgCommonFT3Sub 消息处理程序

void CDlgCommonFT3Sub::InitDialog()
{
	CTickCount32 oTick32;
	CDataType *pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(iecfg_GinAppChDataType);

	for (int nIndex = 0;nIndex<IECCFG_COMMON_FT3_BIT_NUM;nIndex++)
	{
		m_cmbBitValue[nIndex].ShowDataType(pDataType);
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("InitDialog=%d"), oTick32.GetTickCountLong());
	m_btnOK.EnableWindow(TRUE);
	m_btnCancel.EnableWindow(TRUE);
}


BOOL CDlgCommonFT3Sub::OnInitDialog()
{
	CDynDialogEx::OnInitDialog();

	CreateControls();
	InitDialog();
	MoveWindow(CRect( 0, 0, 330, 300), TRUE);
	CenterWindow();
	SetWindowText(_T("FT3发布参数设置"));
	InitChMapCombox();

	m_bHasInitDialog = TRUE;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgCommonFT3Sub::InitChMapCombox()
{
	if (m_pCfg6044CommonCh == NULL)
	{
		return;
	}

	CEquationBuffer oEquationBuffer(m_pCfg6044CommonCh->m_strDevChID);
	CString strMapID,astrMap[IECCFG_COMMON_FT3_BIT_NUM];

	for (int nIndex = 0;nIndex<IECCFG_COMMON_FT3_BIT_NUM;nIndex++)
	{
		strMapID.Format(_T("bit%d"),nIndex);
		oEquationBuffer.ParseString(strMapID,astrMap[nIndex]);

		if (astrMap[nIndex].IsEmpty())
		{
			m_cmbBitValue[nIndex].SetCurSel(0);
			m_nBitSelIndex[nIndex] = 0;
		} 
		else
		{
			m_cmbBitValue[nIndex].SetCurrSelByID(astrMap[nIndex]);
			m_nBitSelIndex[nIndex] = m_cmbBitValue[nIndex].GetCurSel();
		}
	}
}

void CDlgCommonFT3Sub::SaveChMapCombox()
{
	if (m_pCfg6044CommonCh == NULL)
	{
		return;
	}

//	CEquationBuffer oEquationBuffer(m_pCfg6044CommonCh->m_strDevChID);
	CString strMapString,strSelectID;
	strMapString = _T("");

	for (int nIndex = 0;nIndex<IECCFG_COMMON_FT3_BIT_NUM;nIndex++)
	{
		strSelectID = m_cmbBitValue[nIndex].GetSelectID();

		if (strSelectID != _T("none"))
		{
			strMapString.AppendFormat(_T("bit%d=%s;"),nIndex,strSelectID.GetString());
		} 
	}

	if (strMapString.IsEmpty())
	{
		strMapString = _T("none");
	}

	m_pCfg6044CommonCh->m_strDevChID = strMapString;
}

void CDlgCommonFT3Sub::OnOK()
{
	UpdateData(TRUE);
	SaveChMapCombox();
	CDynDialogEx::OnOK();
}


void CDlgCommonFT3Sub::OnCancel()
{
	CDynDialogEx::OnCancel();
}

void CDlgCommonFT3Sub::OnCbnSelchangeComboxBit0()
{
	OnCbnSelchangeComboxBit(0);
}

void CDlgCommonFT3Sub::OnCbnSelchangeComboxBit1()
{
	OnCbnSelchangeComboxBit(1);
}

void CDlgCommonFT3Sub::OnCbnSelchangeComboxBit2()
{
	OnCbnSelchangeComboxBit(2);
}
void CDlgCommonFT3Sub::OnCbnSelchangeComboxBit3()
{
	OnCbnSelchangeComboxBit(3);
}

void CDlgCommonFT3Sub::OnCbnSelchangeComboxBit4()
{
	OnCbnSelchangeComboxBit(4);
}
void CDlgCommonFT3Sub::OnCbnSelchangeComboxBit5()
{
	OnCbnSelchangeComboxBit(5);
}
void CDlgCommonFT3Sub::OnCbnSelchangeComboxBit6()
{
	OnCbnSelchangeComboxBit(6);
}
void CDlgCommonFT3Sub::OnCbnSelchangeComboxBit7()
{
	OnCbnSelchangeComboxBit(7);
}
void CDlgCommonFT3Sub::OnCbnSelchangeComboxBit8()
{
	OnCbnSelchangeComboxBit(8);
}
void CDlgCommonFT3Sub::OnCbnSelchangeComboxBit9()
{
	OnCbnSelchangeComboxBit(9);
}
void CDlgCommonFT3Sub::OnCbnSelchangeComboxBit10()
{
	OnCbnSelchangeComboxBit(10);
}

void CDlgCommonFT3Sub::OnCbnSelchangeComboxBit11()
{
	OnCbnSelchangeComboxBit(11);
}
void CDlgCommonFT3Sub::OnCbnSelchangeComboxBit12()
{
	OnCbnSelchangeComboxBit(12);
}
void CDlgCommonFT3Sub::OnCbnSelchangeComboxBit13()
{
	OnCbnSelchangeComboxBit(13);
}
void CDlgCommonFT3Sub::OnCbnSelchangeComboxBit14()
{
	OnCbnSelchangeComboxBit(14);
}
void CDlgCommonFT3Sub::OnCbnSelchangeComboxBit15()
{
	OnCbnSelchangeComboxBit(15);
}
void CDlgCommonFT3Sub::OnCbnSelchangeComboxBit(int nIndex)
{
	CString strCurSelID;
	strCurSelID = m_cmbBitValue[nIndex].GetSelectID();
	if ((strCurSelID != _T("none")) && IsBinMapRepeat(nIndex))
	{
		m_cmbBitValue[nIndex].SetCurSel(m_nBitSelIndex[nIndex]);
	}
	else
	{
		m_nBitSelIndex[nIndex] = m_cmbBitValue[nIndex].GetCurSel();
	}
}

BOOL CDlgCommonFT3Sub::IsBinMapRepeat(int nBitIndex)
{
	CString strCurSelID,strCurSelName;
	strCurSelID = m_cmbBitValue[nBitIndex].GetSelectID();
	strCurSelName = m_cmbBitValue[nBitIndex].GetSelectName();

	for (int nIndex = 0;nIndex<IECCFG_COMMON_FT3_BIT_NUM;nIndex++)
	{
		if ((nIndex != nBitIndex)&&(strCurSelID == m_cmbBitValue[nIndex].GetSelectID()))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("%s在本通道已映射,不能重复映射."),strCurSelName.GetString());
			return TRUE;
		}
	}

	ASSERT(m_pCfg6044CommonCh);
	CExBaseList *pParent = (CExBaseList*)m_pCfg6044CommonCh->GetParent();

	if (pParent != NULL)
	{
		strCurSelID += _T(";");
		CIecCfg6044CommonCh *pCurCfgCh = NULL;
		POS pos = pParent->GetHeadPosition();

		while(pos)
		{
			pCurCfgCh = (CIecCfg6044CommonCh *)pParent->GetNext(pos);

			if ((pCurCfgCh != m_pCfg6044CommonCh)&&(pCurCfgCh->m_strDevChID.Find(strCurSelID) != -1))
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("%s在%s已映射,不能重复映射."),strCurSelName.GetString()
					,pCurCfgCh->m_strName.GetString());
				return TRUE;
			}
		}
	}

	return FALSE;
}
