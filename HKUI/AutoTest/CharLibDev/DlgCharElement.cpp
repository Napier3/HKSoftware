// DlgCharElement.cpp : 实现文件
//

#include "stdafx.h"
#include "CharLibDev.h"
#include "DlgCharElement.h"
#include "XLanguageResourceAts_CharLibDev.h"

// CDlgCharElement 对话框

IMPLEMENT_DYNAMIC(CDlgCharElement, CDialog)

CDlgCharElement::CDlgCharElement(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCharElement::IDD, pParent)
	, m_strErrLength(_T(""))
	, m_nTestPoints(1)
{
	m_pElementDlgCurr = NULL;
	m_pCharElementSrcSel = NULL;
	m_pCharElementEdit = NULL;
	m_pPrevCharElement = NULL;
}

CDlgCharElement::~CDlgCharElement()
{
}

void CDlgCharElement::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_ELEMENTTYPE, m_cmbElementType);
	DDX_Control(pDX, IDC_FRAME_ELEMENT, m_wndFrmElement);
	DDX_Text(pDX, IDC_EDIT_ERROR_LEN, m_strErrLength);
	DDX_Text(pDX, IDC_EDIT_TESTPOINTS, m_nTestPoints);

	DDX_Control(pDX, IDC_STATIC_ALTYPE, m_wndEdgeElementType);
	DDX_Control(pDX, IDC_STATIC_ERRORLENGTH, m_wndErrorBandLength);
	DDX_Control(pDX, IDC_STATIC_EDGETESTPOINT, m_wndEdgTestPoints);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_EDIT_ERROR_LEN, m_edtErrorBandLength);
	DDX_Control(pDX, IDC_EDIT_TESTPOINTS, m_edtEdgTestPoints);
	DDV_MinMaxLong(pDX, m_nTestPoints, 1, 200);
}


BEGIN_MESSAGE_MAP(CDlgCharElement, CDialog)
	ON_CBN_SELCHANGE(IDC_CMB_ELEMENTTYPE, &CDlgCharElement::OnCbnSelchangeCmbElementtype)
END_MESSAGE_MAP()


// CDlgCharElement 消息处理程序

void CDlgCharElement::OnCbnSelchangeCmbElementtype()
{
	CString strID;
	CCharElement *pCharSrc = (CCharElement*)m_cmbElementType.GetCurrSelObject();
	ASSERT (pCharSrc != NULL);

	if (pCharSrc == NULL)
	{
		return;
	}

// 	if (m_pCharElementEdit != NULL)
// 	{
// 		if (pCharSrc->m_strID == m_pCharElementEdit->m_strID)
// 		{
// 			m_pCharElementEdit->Copy(pCharSrc);
// 		}
// 	}

	ShowElementDlg(pCharSrc->m_strID);
	m_pCharElementSrcSel = pCharSrc;

	if (m_pElementDlgCurr != NULL)
	{
		m_pElementDlgCurr->ShowCharElement(pCharSrc);
	}
}

void CDlgCharElement::xlang_InitAndAdjust()
{
	if (xlang_IsCurrXLanguageChinese())
	{
		return;
	}

	m_wndEdgeElementType.SetLanguageID(g_sLangID_EdgeElementType);
    m_wndErrorBandLength.SetLanguageID(g_sLangID_ErrorBandLength);
    m_wndEdgTestPoints.SetLanguageID(g_sLangID_EdgTestPoints);
    m_btnOK.SetLanguageID(g_sLangID_OK);
	m_btnCancel.SetLanguageID(g_sLangID_Cancel);

	CXLangWndAdjMngr oWndAdjMngr;         
	oWndAdjMngr.RegisterCols(); 
	oWndAdjMngr.RegisterCol(); 
	oWndAdjMngr.RegisterXWnd(&m_wndEdgeElementType);
	oWndAdjMngr.RegisterXWnd(&m_wndErrorBandLength);
	oWndAdjMngr.RegisterXWnd(&m_wndEdgTestPoints);
	oWndAdjMngr.RegisterCol(); 
	oWndAdjMngr.RegisterWnd(&m_cmbElementType);
	oWndAdjMngr.RegisterWnd(&m_edtErrorBandLength);
	oWndAdjMngr.RegisterWnd(&m_edtEdgTestPoints);
	oWndAdjMngr.Adjust(this, TRUE);

	xlang_InitByLgugStr(g_sLangID_CharCurveEdge, this);
}

BOOL CDlgCharElement::OnInitDialog()
{
	CDialog::OnInitDialog();

	CCharacterArea *pCharAreaSrc = CCharacteristicLib::GetGlobalCharAreaSrc();
	m_cmbElementType.SetAddEmptyString(FALSE);
	m_cmbElementType.ShowBaseList(pCharAreaSrc);

	m_wndFrmElement.GetWindowRect(&m_rcCharElemDlg);
	ScreenToClient(&m_rcCharElemDlg);

	//显示当前编辑的对象
	if (m_pCharElementEdit != NULL)
	{
		m_cmbElementType.SetCurrSelByID(m_pCharElementEdit->m_strID);
		m_pCharElementSrcSel = (CCharElement*)pCharAreaSrc->FindByID(m_pCharElementEdit->m_strID);
		ASSERT (m_pCharElementSrcSel != NULL);
		m_pCharElementEdit->Copy(m_pCharElementSrcSel);
	}
	else
	{
		m_cmbElementType.SetCurrSelByID(CHAR_ELEMENT_ID_LINED);
		m_pCharElementSrcSel = (CCharElement *)pCharAreaSrc->GetHead();

		if (m_pPrevCharElement != NULL)
		{
			CString strX, strY;
			m_pPrevCharElement->GetEndPoint(strX, strY);
			m_pCharElementSrcSel->SetBeginPoint(strX, strY);
		}
	}

	m_strErrLength = m_pCharElementSrcSel->m_strErrLength;
	m_nTestPoints = *m_pCharElementSrcSel->GetTestPointsRef();

	UpdateData(FALSE);

	OnCbnSelchangeCmbElementtype();

	xlang_InitAndAdjust();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgCharElement::ShowElementDlg(const CString &strClassID)
{
	CCharElmentBaseDlg *pDlg;
	pDlg = m_oCharElementMngrDlg.FindByID(strClassID);

	if (pDlg == NULL) 
	{
		pDlg =CreateCharElementDlg(strClassID);

		if (m_pElementDlgCurr != NULL)
		{
			m_pElementDlgCurr->Hide();
		}

		if (pDlg != NULL)
		{
			m_pElementDlgCurr = pDlg;	
			m_oCharElementMngrDlg.AddTail(pDlg);
			m_pElementDlgCurr->CreateDlg(this);
		}
		else
		{
			m_pElementDlgCurr = pDlg;
		}
	}
	else
	{
		if (m_pElementDlgCurr == NULL)
		{
			m_pElementDlgCurr = pDlg;
		}
		else
		{
			if (m_pElementDlgCurr != pDlg)
			{
				m_pElementDlgCurr->Hide();
				m_pElementDlgCurr = pDlg;
			}
			else 
				return;
		}
	}

// 	ASSERT (m_pElementDlgCurr != NULL);

	if (m_pElementDlgCurr != NULL)
	{
		m_pElementDlgCurr->SetWindowPos(m_rcCharElemDlg);
	}
}

CCharElmentBaseDlg* CDlgCharElement::CreateCharElementDlg(const CString &strClassID)
{
	CCharElmentBaseDlg* pDlgBase;

	if (strClassID == CHAR_ELEMENT_ID_LINED)
	{
		pDlgBase = new CCharElementLinedDlg();
	}
	else if (strClassID == CHAR_ELEMENT_ID_MHO)
	{
		pDlgBase = new CCharElementMhoDlg();
	}
	else if (strClassID == CHAR_ELEMENT_ID_LINER)
	{
		pDlgBase = new CCharElementLinerDlg();
	}
	else if (strClassID == CHAR_ELEMENT_ID_LINE)
	{
		pDlgBase = new CCharElementLineDlg();
	}
	else if (strClassID == CHAR_ELEMENT_ID_ARC)
	{
		pDlgBase = new CCharElementArcDlg();
	}
	else if (strClassID == CHAR_ELEMENT_ID_ARCP)
	{
		pDlgBase = new CCharElementArcpDlg();
	}
// 	else			if (strClassID == _T("arc"))
// 	{
// 		pDlgBase = new CCharElementArcDlg();
// 	}
// 	else 				if (strClassID == _T("arcp"))
// 	{
// 		pDlgBase = new CCharElementArcpDlg();
// 	}
// 	else					if (strClassID == _T("mho"))
// 	{
// 		pDlgBase = new CCharElementMhoDlg();
// 	}
	else if (strClassID == CHAR_ELEMENT_ID_LENS)
	{
		pDlgBase = new CCharElementLensDlg();
	}
// 	else							if (strClassID == _T("lined"))
// 	{
// 		pDlgBase = new CCharElementLinedDlg();
// 	}
// 	else								if (strClassID == _T("arcd"))
// 	{
// 		pDlgBase = new CCharElementArcdDlg();
// 	}
	else if (strClassID == CHAR_ELEMENT_ID_I2T)
	{
		pDlgBase = new CCharElementInvI2TDlg();
	}
	else if (strClassID == CHAR_ELEMENT_ID_IAC)
	{
		pDlgBase = new CCharElementInvIACDlg();
	}
	else if (strClassID == CHAR_ELEMENT_ID_IEC)
	{
		pDlgBase = new CCharElementInvIECDlg();
	}
	else if (strClassID == CHAR_ELEMENT_ID_IEEE)
	{
		pDlgBase = new CCharElementInvIEEEDlg();
	}
	else if(strClassID == CHAR_ELEMENT_ID_INVOWNDEF)
	{
		pDlgBase = new CCharElementInvOwnDefDlg();
	}
	else 
	{
		MessageBox(g_sLangTxt_ElementDevelop/*_T("元素开发中.....")*/, g_sLangTxt_Message1/*_T("提示")*/, MB_OK | MB_ICONWARNING);
		pDlgBase = NULL;
	}

	return pDlgBase;
}


void CDlgCharElement::OnOK()
{
	UpdateData(TRUE);

	if (m_pElementDlgCurr == NULL)
	{
		MessageBox(g_sLangTxt_ElementDevelop/*_T("元素开发中.....")*/, g_sLangTxt_Message1/*_T("提示")*/, MB_OK | MB_ICONWARNING);
		return;
	}

	m_pCharElementSrcSel->m_strErrLength = m_strErrLength;

	m_pElementDlgCurr->GetData();

	if (m_pElementDlgCurr->IsEnable())
	{
		ASSERT(m_pCharElementSrcSel!=NULL);
		if(m_pCharElementEdit != NULL) //双击某项弹出的修改框
		{
			m_pCharElementSrcSel->Copy(m_pCharElementEdit);
			theApp.m_oCharacteristicLib.SaveCharLibFile(_T("")); //需要实时改变
			//char_dev_SetModifiedFlag(&theApp.m_oCharacteristicLib, TRUE);
		}
		else //新建框
		{

		}

		CDialog::OnOK();
	}

}
