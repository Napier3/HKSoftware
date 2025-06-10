// IecCfgSysParasView.cpp : 实现文件
//

#include "stdafx.h"
#include "Iec61850Config.h"
#include "IecCfgSysParasView.h"


// CIecCfgSysParasView

IMPLEMENT_DYNCREATE(CIecCfgSysParasView, CFormView)

CIecCfgSysParasView::CIecCfgSysParasView()
	: CFormView(CIecCfgSysParasView::IDD)
//	, m_nBCodeLogic(0)
//	, m_nIec1588Type(0)
{
	m_pIecCfgFile = NULL;
	m_pSysParas = NULL;
	m_pFiberParas = NULL;
	m_pPrimRates = NULL;

	int nIndex = 0;

	for (nIndex = 0;nIndex<IECCFG_MAX_LC_FIBER_NUM;nIndex++)
	{
		m_nLC_Fiber[nIndex] = 0;
	}

	for (nIndex = 0;nIndex<IECCFG_MAX_ST_FIBER_NUM;nIndex++)
	{
		m_nST_Fiber[nIndex] = 0;
	}
}

CIecCfgSysParasView::~CIecCfgSysParasView()
{
}

void CIecCfgSysParasView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PKG_SEND_TYPE, m_cmbPkgSendType);
	//	DDX_Control(pDX, IDC_COMBO_SEC_SYN_STATE, m_cmbSecSynState);
	//	DDX_Radio(pDX, IDC_RADIO_POSITIVE, m_nBCodeLogic);
	//	DDX_Radio(pDX, IDC_RADIO_IEC1588_PEER, m_nIec1588Type);
	DDX_Radio(pDX, IDC_RADIO_100M_FIBER1, m_nLC_Fiber[0]);
	DDX_Radio(pDX, IDC_RADIO_100M_FIBER2, m_nLC_Fiber[1]);
	DDX_Radio(pDX, IDC_RADIO_100M_FIBER3, m_nLC_Fiber[2]);
	DDX_Radio(pDX, IDC_RADIO_100M_FIBER4, m_nLC_Fiber[3]);
	DDX_Radio(pDX, IDC_RADIO_BCODE_FIBER1, m_nST_Fiber[0]);
	DDX_Radio(pDX, IDC_RADIO_BCODE_FIBER2, m_nST_Fiber[1]);
	DDX_Radio(pDX, IDC_RADIO_BCODE_FIBER3, m_nST_Fiber[2]);
	DDX_Radio(pDX, IDC_RADIO_BCODE_FIBER4, m_nST_Fiber[3]);
	DDX_Radio(pDX, IDC_RADIO_BCODE_FIBER5, m_nST_Fiber[4]);
	DDX_Radio(pDX, IDC_RADIO_BCODE_FIBER6, m_nST_Fiber[5]);
	DDX_Control(pDX, IDC_EDIT_PRIM_PT_RATE1, m_edtPrimPT[0]);
	DDX_Control(pDX, IDC_EDIT_SECOND_PT_RATE1, m_edtSecPT[0]);
	DDX_Control(pDX, IDC_EDIT_PRIM_CT_RATE1, m_edtPrimCT[0]);
	DDX_Control(pDX, IDC_EDIT_SECOND_CT_RATE1, m_edtSecCT[0]);

	DDX_Control(pDX, IDC_EDIT_PRIM_PT_RATE2, m_edtPrimPT[1]);
	DDX_Control(pDX, IDC_EDIT_SECOND_PT_RATE2, m_edtSecPT[1]);
	DDX_Control(pDX, IDC_EDIT_PRIM_CT_RATE2, m_edtPrimCT[1]);
	DDX_Control(pDX, IDC_EDIT_SECOND_CT_RATE2, m_edtSecCT[1]);

	DDX_Control(pDX, IDC_EDIT_PRIM_PT_RATE3, m_edtPrimPT[2]);
	DDX_Control(pDX, IDC_EDIT_SECOND_PT_RATE3, m_edtSecPT[2]);
	DDX_Control(pDX, IDC_EDIT_PRIM_CT_RATE3, m_edtPrimCT[2]);
	DDX_Control(pDX, IDC_EDIT_SECOND_CT_RATE3, m_edtSecCT[2]);

	DDX_Control(pDX, IDC_EDIT_PRIM_PT_RATE4, m_edtPrimPT[3]);
	DDX_Control(pDX, IDC_EDIT_SECOND_PT_RATE4, m_edtSecPT[3]);
	DDX_Control(pDX, IDC_EDIT_PRIM_CT_RATE4, m_edtPrimCT[3]);
	DDX_Control(pDX, IDC_EDIT_SECOND_CT_RATE4, m_edtSecCT[3]);

	DDX_Control(pDX, IDC_EDIT_PRIM_PT_RATE5, m_edtPrimPT[4]);
	DDX_Control(pDX, IDC_EDIT_SECOND_PT_RATE5, m_edtSecPT[4]);
	DDX_Control(pDX, IDC_EDIT_PRIM_CT_RATE5, m_edtPrimCT[4]);
	DDX_Control(pDX, IDC_EDIT_SECOND_CT_RATE5, m_edtSecCT[4]);

	DDX_Control(pDX, IDC_EDIT_PRIM_PT_RATE6, m_edtPrimPT[5]);
	DDX_Control(pDX, IDC_EDIT_SECOND_PT_RATE6, m_edtSecPT[5]);
	DDX_Control(pDX, IDC_EDIT_PRIM_CT_RATE6, m_edtPrimCT[5]);
	DDX_Control(pDX, IDC_EDIT_SECOND_CT_RATE6, m_edtSecCT[5]);
	DDX_Control(pDX, IDC_COMBO_PARAS_SET_SEL, m_cmbParasSetSel);
}

BEGIN_MESSAGE_MAP(CIecCfgSysParasView, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO_PKG_SEND_TYPE, &CIecCfgSysParasView::OnCbnSelchangeComboPkgSendType)
//	ON_CBN_SELCHANGE(IDC_COMBO_SEC_SYN_STATE, &CIecCfgSysParasView::OnCbnSelchangeComboSecSynState)
// 	ON_BN_CLICKED(IDC_RADIO_POSITIVE, &CIecCfgSysParasView::OnBnClickedRadioPositive)
// 	ON_BN_CLICKED(IDC_RADIO_NEGATIVE, &CIecCfgSysParasView::OnBnClickedRadioNegative)
// 	ON_BN_CLICKED(IDC_RADIO_IEC1588_PEER, &CIecCfgSysParasView::OnBnClickedRadioIec1588Peer)
// 	ON_BN_CLICKED(IDC_RADIO_IEC1588_REQ_RES, &CIecCfgSysParasView::OnBnClickedRadioIec1588ReqRes)
	ON_BN_CLICKED(IDC_RADIO_100M_FIBER1, &CIecCfgSysParasView::OnBnClickedRadio100mFiber1)
	ON_BN_CLICKED(IDC_RADIO_1000M_FIBER1, &CIecCfgSysParasView::OnBnClickedRadio1000mFiber1)
	ON_BN_CLICKED(IDC_RADIO_100M_FIBER2, &CIecCfgSysParasView::OnBnClickedRadio100mFiber2)
	ON_BN_CLICKED(IDC_RADIO_1000M_FIBER2, &CIecCfgSysParasView::OnBnClickedRadio1000mFiber2)
	ON_BN_CLICKED(IDC_RADIO_100M_FIBER3, &CIecCfgSysParasView::OnBnClickedRadio100mFiber3)
	ON_BN_CLICKED(IDC_RADIO_1000M_FIBER3, &CIecCfgSysParasView::OnBnClickedRadio1000mFiber3)
	ON_BN_CLICKED(IDC_RADIO_100M_FIBER4, &CIecCfgSysParasView::OnBnClickedRadio100mFiber4)
	ON_BN_CLICKED(IDC_RADIO_1000M_FIBER4, &CIecCfgSysParasView::OnBnClickedRadio1000mFiber4)
	ON_BN_CLICKED(IDC_RADIO_BCODE_FIBER1, &CIecCfgSysParasView::OnBnClickedRadioBcodeFiber1)
	ON_BN_CLICKED(IDC_RADIO_FT3_FIBER1, &CIecCfgSysParasView::OnBnClickedRadioFt3Fiber1)
	ON_BN_CLICKED(IDC_RADIO_BCODE_FIBER2, &CIecCfgSysParasView::OnBnClickedRadioBcodeFiber2)
	ON_BN_CLICKED(IDC_RADIO_FT3_FIBER2, &CIecCfgSysParasView::OnBnClickedRadioFt3Fiber2)
	ON_BN_CLICKED(IDC_RADIO_BCODE_FIBER3, &CIecCfgSysParasView::OnBnClickedRadioBcodeFiber3)
	ON_BN_CLICKED(IDC_RADIO_FT3_FIBER3, &CIecCfgSysParasView::OnBnClickedRadioFt3Fiber3)
	ON_BN_CLICKED(IDC_RADIO_BCODE_FIBER4, &CIecCfgSysParasView::OnBnClickedRadioBcodeFiber4)
	ON_BN_CLICKED(IDC_RADIO_FT3_FIBER4, &CIecCfgSysParasView::OnBnClickedRadioFt3Fiber4)
	ON_BN_CLICKED(IDC_RADIO_BCODE_FIBER5, &CIecCfgSysParasView::OnBnClickedRadioBcodeFiber5)
	ON_BN_CLICKED(IDC_RADIO_FT3_FIBER5, &CIecCfgSysParasView::OnBnClickedRadioFt3Fiber5)
	ON_BN_CLICKED(IDC_RADIO_BCODE_FIBER6, &CIecCfgSysParasView::OnBnClickedRadioBcodeFiber6)
	ON_BN_CLICKED(IDC_RADIO_FT3_FIBER6, &CIecCfgSysParasView::OnBnClickedRadioFt3Fiber6)
	ON_EN_UPDATE(IDC_EDIT_PRIM_PT_RATE1, &CIecCfgSysParasView::OnEnUpdateEditPrimPtRate1)
	ON_EN_UPDATE(IDC_EDIT_SECOND_PT_RATE1, &CIecCfgSysParasView::OnEnUpdateEditSecondPtRate1)
	ON_EN_UPDATE(IDC_EDIT_PRIM_CT_RATE1, &CIecCfgSysParasView::OnEnUpdateEditPrimCtRate1)
	ON_EN_UPDATE(IDC_EDIT_SECOND_CT_RATE1, &CIecCfgSysParasView::OnEnUpdateEditSecondCtRate1)
	ON_EN_UPDATE(IDC_EDIT_PRIM_PT_RATE2, &CIecCfgSysParasView::OnEnUpdateEditPrimPtRate2)
	ON_EN_UPDATE(IDC_EDIT_SECOND_PT_RATE2, &CIecCfgSysParasView::OnEnUpdateEditSecondPtRate2)
	ON_EN_UPDATE(IDC_EDIT_PRIM_CT_RATE2, &CIecCfgSysParasView::OnEnUpdateEditPrimCtRate2)
	ON_EN_UPDATE(IDC_EDIT_SECOND_CT_RATE2, &CIecCfgSysParasView::OnEnUpdateEditSecondCtRate2)

	ON_EN_UPDATE(IDC_EDIT_PRIM_PT_RATE3, &CIecCfgSysParasView::OnEnUpdateEditPrimPtRate3)
	ON_EN_UPDATE(IDC_EDIT_SECOND_PT_RATE3, &CIecCfgSysParasView::OnEnUpdateEditSecondPtRate3)
	ON_EN_UPDATE(IDC_EDIT_PRIM_CT_RATE3, &CIecCfgSysParasView::OnEnUpdateEditPrimCtRate3)
	ON_EN_UPDATE(IDC_EDIT_SECOND_CT_RATE3, &CIecCfgSysParasView::OnEnUpdateEditSecondCtRate3)

	ON_EN_UPDATE(IDC_EDIT_PRIM_PT_RATE4, &CIecCfgSysParasView::OnEnUpdateEditPrimPtRate4)
	ON_EN_UPDATE(IDC_EDIT_SECOND_PT_RATE4, &CIecCfgSysParasView::OnEnUpdateEditSecondPtRate4)
	ON_EN_UPDATE(IDC_EDIT_PRIM_CT_RATE4, &CIecCfgSysParasView::OnEnUpdateEditPrimCtRate4)
	ON_EN_UPDATE(IDC_EDIT_SECOND_CT_RATE4, &CIecCfgSysParasView::OnEnUpdateEditSecondCtRate4)

	ON_EN_UPDATE(IDC_EDIT_PRIM_PT_RATE5, &CIecCfgSysParasView::OnEnUpdateEditPrimPtRate5)
	ON_EN_UPDATE(IDC_EDIT_SECOND_PT_RATE5, &CIecCfgSysParasView::OnEnUpdateEditSecondPtRate5)
	ON_EN_UPDATE(IDC_EDIT_PRIM_CT_RATE5, &CIecCfgSysParasView::OnEnUpdateEditPrimCtRate5)
	ON_EN_UPDATE(IDC_EDIT_SECOND_CT_RATE5, &CIecCfgSysParasView::OnEnUpdateEditSecondCtRate5)

	ON_EN_UPDATE(IDC_EDIT_PRIM_PT_RATE6, &CIecCfgSysParasView::OnEnUpdateEditPrimPtRate6)
	ON_EN_UPDATE(IDC_EDIT_SECOND_PT_RATE6, &CIecCfgSysParasView::OnEnUpdateEditSecondPtRate6)
	ON_EN_UPDATE(IDC_EDIT_PRIM_CT_RATE6, &CIecCfgSysParasView::OnEnUpdateEditPrimCtRate6)
	ON_EN_UPDATE(IDC_EDIT_SECOND_CT_RATE6, &CIecCfgSysParasView::OnEnUpdateEditSecondCtRate6)
	ON_CBN_SELCHANGE(IDC_COMBO_PARAS_SET_SEL, &CIecCfgSysParasView::OnCbnSelchangeComboParasSetSel)
END_MESSAGE_MAP()


// CIecCfgSysParasView 诊断

#ifdef _DEBUG
void CIecCfgSysParasView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CIecCfgSysParasView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CIecCfgSysParasView 消息处理程序

BOOL CIecCfgSysParasView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CIecCfgSysParasView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
}

void CIecCfgSysParasView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// TODO: 在此添加专用代码和/或调用基类
	CIecCfgFile *pFile = (CIecCfgFile*)lHint;
	m_pIecCfgFile = pFile;

	if (m_pIecCfgFile != NULL)
	{
		InitUI();
		UpdateData(FALSE);
	}
}

void CIecCfgSysParasView::InitUI()
{
	for (int nIndex = 0;nIndex<IECCFG_MAX_PT_CT_NUM;nIndex++)
	{
		m_edtPrimPT[nIndex].SetEnumFormatFloat();
		m_edtSecPT[nIndex].SetEnumFormatFloat();
		m_edtPrimCT[nIndex].SetEnumFormatFloat();
		m_edtSecCT[nIndex].SetEnumFormatFloat();

		m_edtPrimPT[nIndex].InitFormat(_T("kV"),_T("%f %s"));
		m_edtSecPT[nIndex].InitFormat(_T("V"),_T("%f %s"));
		m_edtPrimCT[nIndex].InitFormat(_T("A"),_T("%f %s"));
		m_edtSecCT[nIndex].InitFormat(_T("A"),_T("%f %s"));

		m_edtPrimPT[nIndex].SetMinMax(1.0,10000.0);
		m_edtSecPT[nIndex].SetMinMax(1.0,10000.0);
		m_edtPrimCT[nIndex].SetMinMax(1.0,10000.0);
		m_edtSecCT[nIndex].SetMinMax(1.0,10000.0);
	}

	m_cmbPkgSendType.Clear();
	m_cmbPkgSendType.AddString(_T("停止后保持发送"));
	m_cmbPkgSendType.AddString(_T("停止后终止发送"));
	m_cmbPkgSendType.SetCurSel(0);

	m_cmbParasSetSel.Clear();
	m_cmbParasSetSel.AddString(_T("二次值"));
	m_cmbParasSetSel.AddString(_T("一次值"));
	m_cmbParasSetSel.SetCurSel(0);

// 	m_cmbSecSynState.Clear();
// 	m_cmbSecSynState.AddString(_T("开启秒同步"));
// 	m_cmbSecSynState.AddString(_T("关闭秒同步"));

	if (m_pIecCfgFile != NULL)
	{
		ASSERT(m_pIecCfgFile->m_pIecCfgDatasMngr);
		m_pSysParas = m_pIecCfgFile->m_pIecCfgDatasMngr->GetSysParasMngr();
		m_cmbPkgSendType.SetCurSel(m_pSysParas->m_nPkgSendType);
		m_cmbParasSetSel.SetCurSel(m_pSysParas->m_nPrimParas);

// 		if (m_pSysParas->m_nSecSyn == _IECCFG_SYSPARAS_SEC_SYN_Enable_)
// 		{
// 			m_cmbSecSynState.SetCurSel(0);
// 		}
// 		else
// 		{
// 			m_cmbSecSynState.SetCurSel(1);
// 		}
		
// 		if (m_pSysParas->m_nBCodeLogic == _IECCFG_SYSPARAS_B_CODE_LOGIC_Positive_)
// 		{
// 			m_nBCodeLogic = 0;
// 		}
// 		else
// 		{
// 			m_nBCodeLogic = 1;
// 		}

//		m_nIec1588Type = m_pSysParas->m_nIec1588Type;
		int nIndex = 0;
		CString strID;
		CIecCfgFiberPara *pFiberPara = NULL;
		m_pFiberParas = m_pSysParas->GetFiberParas();

		for (nIndex = 0;nIndex<IECCFG_MAX_LC_FIBER_NUM;nIndex++)
		{
			strID.Format(_T("LC%d"),nIndex+1);
			pFiberPara = (CIecCfgFiberPara*)m_pFiberParas->FindByID(strID);

			if (pFiberPara == NULL)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("光口(%s)对应参数数据未找到"),strID.GetString());
			}
			else
			{
				m_nLC_Fiber[nIndex] = pFiberPara->m_ntype;
			}
		}

		for (nIndex = 0;nIndex<IECCFG_MAX_ST_FIBER_NUM;nIndex++)
		{
			strID.Format(_T("ST%d"),nIndex+1);
			pFiberPara = (CIecCfgFiberPara*)m_pFiberParas->FindByID(strID);

			if (pFiberPara == NULL)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("光口(%s)对应参数数据未找到"),strID.GetString());
			}
			else
			{
				m_nST_Fiber[nIndex] = pFiberPara->m_ntype;
			}
		}

		m_pPrimRates = m_pSysParas->GetPrimRates();
		CIecCfgPrimRate *pPrimRate = NULL;

		for (nIndex = 0;nIndex<IECCFG_MAX_PT_CT_NUM;nIndex++)
		{
			strID.Format(_T("U%d-abc"),nIndex+1);
			pPrimRate = (CIecCfgPrimRate *)m_pPrimRates->FindByID(strID);

			if (pPrimRate == NULL)
			{
				pPrimRate = new CIecCfgPrimRate;
				pPrimRate->m_strName = strID;
				pPrimRate->m_strID = strID;
				m_pPrimRates->AddNewChild(pPrimRate);
			}

			m_edtPrimPT[nIndex].SetValue(pPrimRate->m_fPrimValue);
			m_edtSecPT[nIndex].SetValue(pPrimRate->m_fSecondValue);

			strID.Format(_T("I%d-abc"),nIndex+1);
			pPrimRate = (CIecCfgPrimRate *)m_pPrimRates->FindByID(strID);

			if (pPrimRate == NULL)
			{
				pPrimRate = new CIecCfgPrimRate;
				pPrimRate->m_strName = strID;
				pPrimRate->m_strID = strID;
				m_pPrimRates->AddNewChild(pPrimRate);
			}

			m_edtPrimCT[nIndex].SetValue(pPrimRate->m_fPrimValue);
			m_edtSecCT[nIndex].SetValue(pPrimRate->m_fSecondValue);
		}
	}
}

void CIecCfgSysParasView::OnCbnSelchangeComboPkgSendType()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pSysParas != NULL)
	{
		if (m_pSysParas->m_nPkgSendType != m_cmbPkgSendType.GetCurSel())
		{
			m_pSysParas->m_nPkgSendType = m_cmbPkgSendType.GetCurSel();
			iecfg_SetModified(m_pSysParas);
		}
	}
}

// void CIecCfgSysParasView::OnCbnSelchangeComboSecSynState()
// {
// 	// TODO: 在此添加控件通知处理程序代码
// 	if (m_pSysParas != NULL)
// 	{
// 		if (m_cmbSecSynState.GetCurSel() == 0)
// 		{
// 			m_pSysParas->m_nSecSyn = _IECCFG_SYSPARAS_SEC_SYN_Enable_;
// 		} 
// 		else
// 		{
// 			m_pSysParas->m_nSecSyn = _IECCFG_SYSPARAS_SEC_SYN_DisEnable_;
// 		}
// 	}
// }
// 
// void CIecCfgSysParasView::OnBnClickedRadioPositive()
// {
// 	// TODO: 在此添加控件通知处理程序代码
// 	if (m_pSysParas != NULL)
// 	{
// 		if (m_pSysParas->m_nBCodeLogic != _IECCFG_SYSPARAS_B_CODE_LOGIC_Positive_)
// 		{
// 			m_pSysParas->m_nBCodeLogic = _IECCFG_SYSPARAS_B_CODE_LOGIC_Positive_;
// 			iecfg_SetModified(m_pSysParas);
// 		}
// 	}
// }
// 
// void CIecCfgSysParasView::OnBnClickedRadioNegative()
// {
// 	// TODO: 在此添加控件通知处理程序代码
// 	if (m_pSysParas != NULL)
// 	{
// 		if (m_pSysParas->m_nBCodeLogic != _IECCFG_SYSPARAS_B_CODE_LOGIC_Negative_)
// 		{
// 			m_pSysParas->m_nBCodeLogic = _IECCFG_SYSPARAS_B_CODE_LOGIC_Negative_;
// 			iecfg_SetModified(m_pSysParas);
// 		}
// 	}
// }

// void CIecCfgSysParasView::OnBnClickedRadioIec1588Peer()
// {
// 	// TODO: 在此添加控件通知处理程序代码
// 	if (m_pSysParas != NULL)
// 	{
// 		if (m_pSysParas->m_nIec1588Type != _IECCFG_SYSPARAS_IEC1588_TYPE_PeerDelay_)
// 		{
// 			m_pSysParas->m_nIec1588Type = _IECCFG_SYSPARAS_IEC1588_TYPE_PeerDelay_;
// 			iecfg_SetModified(m_pSysParas);
// 		}
// 	}
// }
// 
// void CIecCfgSysParasView::OnBnClickedRadioIec1588ReqRes()
// {
// 	// TODO: 在此添加控件通知处理程序代码
// 	if (m_pSysParas != NULL)
// 	{
// 		if (m_pSysParas->m_nIec1588Type != _IECCFG_SYSPARAS_IEC1588_TYPE_RequestResponse_)
// 		{
// 			m_pSysParas->m_nIec1588Type = _IECCFG_SYSPARAS_IEC1588_TYPE_RequestResponse_;
// 			iecfg_SetModified(m_pSysParas);
// 		}
// 	}
// }

void CIecCfgSysParasView::SetFiberValue(const CString &strID,const long &nValue)
{
	if (m_pFiberParas != NULL)
	{
		CIecCfgFiberPara *pFiberPara = (CIecCfgFiberPara*)m_pFiberParas->FindByID(strID);

		if (pFiberPara == NULL)
		{
			pFiberPara = new CIecCfgFiberPara;
			pFiberPara->m_strName = strID;
			pFiberPara->m_strID = pFiberPara->m_strName;
			m_pFiberParas->AddNewChild(pFiberPara);
		}

		if (pFiberPara->m_ntype != nValue)
		{
			pFiberPara->m_ntype = nValue;
			iecfg_SetModified(m_pFiberParas);
		}
	}
}

void CIecCfgSysParasView::OnBnClickedRadio100mFiber1()
{
	// TODO: 在此添加控件通知处理程序代码
	SetFiberValue(_T("LC1"),_IECCFG_SYSPARAS_LC_PORT_TYPE_100M_);
}

void CIecCfgSysParasView::OnBnClickedRadio1000mFiber1()
{
	// TODO: 在此添加控件通知处理程序代码
	SetFiberValue(_T("LC1"),_IECCFG_SYSPARAS_LC_PORT_TYPE_1000M_);
}

void CIecCfgSysParasView::OnBnClickedRadio100mFiber2()
{
	// TODO: 在此添加控件通知处理程序代码
	SetFiberValue(_T("LC2"),_IECCFG_SYSPARAS_LC_PORT_TYPE_100M_);

}

void CIecCfgSysParasView::OnBnClickedRadio1000mFiber2()
{
	// TODO: 在此添加控件通知处理程序代码
	SetFiberValue(_T("LC2"),_IECCFG_SYSPARAS_LC_PORT_TYPE_1000M_);
}

void CIecCfgSysParasView::OnBnClickedRadio100mFiber3()
{
	// TODO: 在此添加控件通知处理程序代码
	SetFiberValue(_T("LC3"),_IECCFG_SYSPARAS_LC_PORT_TYPE_100M_);
}

void CIecCfgSysParasView::OnBnClickedRadio1000mFiber3()
{
	// TODO: 在此添加控件通知处理程序代码
	SetFiberValue(_T("LC3"),_IECCFG_SYSPARAS_LC_PORT_TYPE_1000M_);
}

void CIecCfgSysParasView::OnBnClickedRadio100mFiber4()
{
	// TODO: 在此添加控件通知处理程序代码
	SetFiberValue(_T("LC4"),_IECCFG_SYSPARAS_LC_PORT_TYPE_100M_);
}

void CIecCfgSysParasView::OnBnClickedRadio1000mFiber4()
{
	// TODO: 在此添加控件通知处理程序代码
	SetFiberValue(_T("LC4"),_IECCFG_SYSPARAS_LC_PORT_TYPE_1000M_);
}

void CIecCfgSysParasView::OnBnClickedRadioBcodeFiber1()
{
	// TODO: 在此添加控件通知处理程序代码
	SetFiberValue(_T("ST1"),_IECCFG_SYSPARAS_ST_PORT_TYPE_BCode_);
}

void CIecCfgSysParasView::OnBnClickedRadioFt3Fiber1()
{
	// TODO: 在此添加控件通知处理程序代码
	SetFiberValue(_T("ST1"),_IECCFG_SYSPARAS_ST_PORT_TYPE_FT3_);
}

void CIecCfgSysParasView::OnBnClickedRadioBcodeFiber2()
{
	// TODO: 在此添加控件通知处理程序代码
	SetFiberValue(_T("ST2"),_IECCFG_SYSPARAS_ST_PORT_TYPE_BCode_);
}

void CIecCfgSysParasView::OnBnClickedRadioFt3Fiber2()
{
	// TODO: 在此添加控件通知处理程序代码
	SetFiberValue(_T("ST2"),_IECCFG_SYSPARAS_ST_PORT_TYPE_FT3_);
}

void CIecCfgSysParasView::OnBnClickedRadioBcodeFiber3()
{
	// TODO: 在此添加控件通知处理程序代码
	SetFiberValue(_T("ST3"),_IECCFG_SYSPARAS_ST_PORT_TYPE_BCode_);
}

void CIecCfgSysParasView::OnBnClickedRadioFt3Fiber3()
{
	// TODO: 在此添加控件通知处理程序代码
	SetFiberValue(_T("ST3"),_IECCFG_SYSPARAS_ST_PORT_TYPE_FT3_);
}

void CIecCfgSysParasView::OnBnClickedRadioBcodeFiber4()
{
	// TODO: 在此添加控件通知处理程序代码
	SetFiberValue(_T("ST4"),_IECCFG_SYSPARAS_ST_PORT_TYPE_BCode_);
}

void CIecCfgSysParasView::OnBnClickedRadioFt3Fiber4()
{
	// TODO: 在此添加控件通知处理程序代码
	SetFiberValue(_T("ST4"),_IECCFG_SYSPARAS_ST_PORT_TYPE_FT3_);
}

void CIecCfgSysParasView::OnBnClickedRadioBcodeFiber5()
{
	// TODO: 在此添加控件通知处理程序代码
	SetFiberValue(_T("ST5"),_IECCFG_SYSPARAS_ST_PORT_TYPE_BCode_);
}

void CIecCfgSysParasView::OnBnClickedRadioFt3Fiber5()
{
	// TODO: 在此添加控件通知处理程序代码
	SetFiberValue(_T("ST5"),_IECCFG_SYSPARAS_ST_PORT_TYPE_FT3_);
}

void CIecCfgSysParasView::OnBnClickedRadioBcodeFiber6()
{
	// TODO: 在此添加控件通知处理程序代码
	SetFiberValue(_T("ST6"),_IECCFG_SYSPARAS_ST_PORT_TYPE_BCode_);
}

void CIecCfgSysParasView::OnBnClickedRadioFt3Fiber6()
{
	// TODO: 在此添加控件通知处理程序代码
	SetFiberValue(_T("ST6"),_IECCFG_SYSPARAS_ST_PORT_TYPE_FT3_);
}

void CIecCfgSysParasView::SetPrimRateValue(int nGroupIndex,int nVoltCurType,int nPrimSecondType,float fValue)
{
	if (m_pPrimRates != NULL)
	{
		CString strID = _T("");

		if (nVoltCurType == IECCFG_SYSPARAS_VIEW_VOLT_TYPE)
		{
			strID.Format(_T("U%d-abc"),nGroupIndex+1);
		} 
		else if (nVoltCurType == IECCFG_SYSPARAS_VIEW_CURR_TYPE)
		{
			strID.Format(_T("I%d-abc"),nGroupIndex+1);
		}

		if (strID.IsEmpty())
		{
			return;
		}

		CIecCfgPrimRate *pPrimRate = (CIecCfgPrimRate*)m_pPrimRates->FindByID(strID);

		if (pPrimRate == NULL)
		{
			pPrimRate = new CIecCfgPrimRate;
			pPrimRate->m_strName = strID;
			pPrimRate->m_strID = pPrimRate->m_strName;
			m_pPrimRates->AddNewChild(pPrimRate);
		}

		BOOL bModify = FALSE;

		if (nPrimSecondType == IECCFG_SYSPARAS_VIEW_PRIM_TYPE)
		{
			if (abs(pPrimRate->m_fPrimValue - fValue)>0.0001)
			{
				pPrimRate->m_fPrimValue = fValue;
				bModify = TRUE;
			}
		}
		else if (nPrimSecondType == IECCFG_SYSPARAS_VIEW_SECOND_TYPE)
		{
			if (abs(pPrimRate->m_fSecondValue - fValue)>0.0001)
			{
				pPrimRate->m_fSecondValue = fValue;
				bModify = TRUE;
			}
		}

		if (bModify)
		{
			iecfg_SetModified(m_pPrimRates);
		}
	}
}

void CIecCfgSysParasView::OnEnUpdateEditPrimPtRate1()
{
	float fValue = 0;
	m_edtPrimPT[0].GetValue(fValue);
	SetPrimRateValue(0,IECCFG_SYSPARAS_VIEW_VOLT_TYPE,IECCFG_SYSPARAS_VIEW_PRIM_TYPE,fValue);
}

void CIecCfgSysParasView::OnEnUpdateEditSecondPtRate1()
{
	float fValue = 0;
	m_edtSecPT[0].GetValue(fValue);
	SetPrimRateValue(0,IECCFG_SYSPARAS_VIEW_VOLT_TYPE,IECCFG_SYSPARAS_VIEW_SECOND_TYPE,fValue);
}


void CIecCfgSysParasView::OnEnUpdateEditPrimCtRate1()
{
	float fValue = 0;
	m_edtPrimCT[0].GetValue(fValue);
	SetPrimRateValue(0,IECCFG_SYSPARAS_VIEW_CURR_TYPE,IECCFG_SYSPARAS_VIEW_PRIM_TYPE,fValue);
}

void CIecCfgSysParasView::OnEnUpdateEditSecondCtRate1()
{
	float fValue = 0;
	m_edtSecCT[0].GetValue(fValue);
	SetPrimRateValue(0,IECCFG_SYSPARAS_VIEW_CURR_TYPE,IECCFG_SYSPARAS_VIEW_SECOND_TYPE,fValue);
}

void CIecCfgSysParasView::OnEnUpdateEditPrimPtRate2()
{
	float fValue = 0;
	m_edtPrimPT[1].GetValue(fValue);
	SetPrimRateValue(1,IECCFG_SYSPARAS_VIEW_VOLT_TYPE,IECCFG_SYSPARAS_VIEW_PRIM_TYPE,fValue);
}

void CIecCfgSysParasView::OnEnUpdateEditSecondPtRate2()
{
	float fValue = 0;
	m_edtSecPT[1].GetValue(fValue);
	SetPrimRateValue(1,IECCFG_SYSPARAS_VIEW_VOLT_TYPE,IECCFG_SYSPARAS_VIEW_SECOND_TYPE,fValue);
}

void CIecCfgSysParasView::OnEnUpdateEditPrimCtRate2()
{
	float fValue = 0;
	m_edtPrimCT[1].GetValue(fValue);
	SetPrimRateValue(1,IECCFG_SYSPARAS_VIEW_CURR_TYPE,IECCFG_SYSPARAS_VIEW_PRIM_TYPE,fValue);
}

void CIecCfgSysParasView::OnEnUpdateEditSecondCtRate2()
{
	float fValue = 0;
	m_edtSecCT[1].GetValue(fValue);
	SetPrimRateValue(1,IECCFG_SYSPARAS_VIEW_CURR_TYPE,IECCFG_SYSPARAS_VIEW_SECOND_TYPE,fValue);
}


void CIecCfgSysParasView::OnEnUpdateEditPrimPtRate3()
{
	float fValue = 0;
	m_edtPrimPT[2].GetValue(fValue);
	SetPrimRateValue(2,IECCFG_SYSPARAS_VIEW_VOLT_TYPE,IECCFG_SYSPARAS_VIEW_PRIM_TYPE,fValue);
}

void CIecCfgSysParasView::OnEnUpdateEditSecondPtRate3()
{
	float fValue = 0;
	m_edtSecPT[2].GetValue(fValue);
	SetPrimRateValue(2,IECCFG_SYSPARAS_VIEW_VOLT_TYPE,IECCFG_SYSPARAS_VIEW_SECOND_TYPE,fValue);
}

void CIecCfgSysParasView::OnEnUpdateEditPrimCtRate3()
{
	float fValue = 0;
	m_edtPrimCT[2].GetValue(fValue);
	SetPrimRateValue(2,IECCFG_SYSPARAS_VIEW_CURR_TYPE,IECCFG_SYSPARAS_VIEW_PRIM_TYPE,fValue);
}

void CIecCfgSysParasView::OnEnUpdateEditSecondCtRate3()
{
	float fValue = 0;
	m_edtSecCT[2].GetValue(fValue);
	SetPrimRateValue(2,IECCFG_SYSPARAS_VIEW_CURR_TYPE,IECCFG_SYSPARAS_VIEW_SECOND_TYPE,fValue);
}


void CIecCfgSysParasView::OnEnUpdateEditPrimPtRate4()
{
	float fValue = 0;
	m_edtPrimPT[3].GetValue(fValue);
	SetPrimRateValue(3,IECCFG_SYSPARAS_VIEW_VOLT_TYPE,IECCFG_SYSPARAS_VIEW_PRIM_TYPE,fValue);
}

void CIecCfgSysParasView::OnEnUpdateEditSecondPtRate4()
{
	float fValue = 0;
	m_edtSecPT[3].GetValue(fValue);
	SetPrimRateValue(3,IECCFG_SYSPARAS_VIEW_VOLT_TYPE,IECCFG_SYSPARAS_VIEW_SECOND_TYPE,fValue);
}

void CIecCfgSysParasView::OnEnUpdateEditPrimCtRate4()
{
	float fValue = 0;
	m_edtPrimCT[3].GetValue(fValue);
	SetPrimRateValue(3,IECCFG_SYSPARAS_VIEW_CURR_TYPE,IECCFG_SYSPARAS_VIEW_PRIM_TYPE,fValue);
}

void CIecCfgSysParasView::OnEnUpdateEditSecondCtRate4()
{
	float fValue = 0;
	m_edtSecCT[3].GetValue(fValue);
	SetPrimRateValue(3,IECCFG_SYSPARAS_VIEW_CURR_TYPE,IECCFG_SYSPARAS_VIEW_SECOND_TYPE,fValue);
}


void CIecCfgSysParasView::OnEnUpdateEditPrimPtRate5()
{
	float fValue = 0;
	m_edtPrimPT[4].GetValue(fValue);
	SetPrimRateValue(4,IECCFG_SYSPARAS_VIEW_VOLT_TYPE,IECCFG_SYSPARAS_VIEW_PRIM_TYPE,fValue);
}

void CIecCfgSysParasView::OnEnUpdateEditSecondPtRate5()
{
	float fValue = 0;
	m_edtSecPT[4].GetValue(fValue);
	SetPrimRateValue(4,IECCFG_SYSPARAS_VIEW_VOLT_TYPE,IECCFG_SYSPARAS_VIEW_SECOND_TYPE,fValue);
}

void CIecCfgSysParasView::OnEnUpdateEditPrimCtRate5()
{
	float fValue = 0;
	m_edtPrimCT[4].GetValue(fValue);
	SetPrimRateValue(4,IECCFG_SYSPARAS_VIEW_CURR_TYPE,IECCFG_SYSPARAS_VIEW_PRIM_TYPE,fValue);
}

void CIecCfgSysParasView::OnEnUpdateEditSecondCtRate5()
{
	float fValue = 0;
	m_edtSecCT[4].GetValue(fValue);
	SetPrimRateValue(4,IECCFG_SYSPARAS_VIEW_CURR_TYPE,IECCFG_SYSPARAS_VIEW_SECOND_TYPE,fValue);
}


void CIecCfgSysParasView::OnEnUpdateEditPrimPtRate6()
{
	float fValue = 0;
	m_edtPrimPT[5].GetValue(fValue);
	SetPrimRateValue(5,IECCFG_SYSPARAS_VIEW_VOLT_TYPE,IECCFG_SYSPARAS_VIEW_PRIM_TYPE,fValue);
}

void CIecCfgSysParasView::OnEnUpdateEditSecondPtRate6()
{
	float fValue = 0;
	m_edtSecPT[5].GetValue(fValue);
	SetPrimRateValue(5,IECCFG_SYSPARAS_VIEW_VOLT_TYPE,IECCFG_SYSPARAS_VIEW_SECOND_TYPE,fValue);
}

void CIecCfgSysParasView::OnEnUpdateEditPrimCtRate6()
{
	float fValue = 0;
	m_edtPrimCT[5].GetValue(fValue);
	SetPrimRateValue(5,IECCFG_SYSPARAS_VIEW_CURR_TYPE,IECCFG_SYSPARAS_VIEW_PRIM_TYPE,fValue);
}

void CIecCfgSysParasView::OnEnUpdateEditSecondCtRate6()
{
	float fValue = 0;
	m_edtSecCT[5].GetValue(fValue);
	SetPrimRateValue(5,IECCFG_SYSPARAS_VIEW_CURR_TYPE,IECCFG_SYSPARAS_VIEW_SECOND_TYPE,fValue);
}
void CIecCfgSysParasView::OnCbnSelchangeComboParasSetSel()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pSysParas != NULL)
	{
		if (m_pSysParas->m_nPrimParas != m_cmbParasSetSel.GetCurSel())
		{
			m_pSysParas->m_nPrimParas = m_cmbParasSetSel.GetCurSel();
			iecfg_SetModified(m_pSysParas);
		}
	}
}
