// D:\WorkLiJQ\Source\AutoTest\Module\WzdDlgApi\StepDlg\InputDataDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "InputDataDlg.h"
#include "WzdMainDlg.h"

#define WND_HEIGHT 100
#define WND_WIDTH  600
#define WND_OFFSET 10

#define IDC_USER_INPUT	60000

// InputDataDlg 对话框

IMPLEMENT_DYNAMIC(InputDataDlg, CDialog)

InputDataDlg::InputDataDlg(CWnd* pParent /*=NULL*/)
	: CUIDialog(InputDataDlg::IDD, pParent)
{
	m_nListID = 1000;
	m_nEditID = 2000;
	m_pDatas = new CSttParas();
	m_pMsgs = NULL;
	m_pItem = NULL;
	m_pLastCtrl = NULL;
}

InputDataDlg::~InputDataDlg()
{

}

void InputDataDlg::FitSize(CStatic* pTxt, CRect& rc, const CString& strText)
{
	long nWidth = rc.Width();
	CDC* pDC = pTxt->GetDC();
	pDC->DrawText(strText, rc, DT_WORDBREAK | DT_CALCRECT | DT_EDITCONTROL);
	int nHeight = rc.Height();
	pTxt->SetWindowPos(NULL, 0, 0, nWidth, nHeight, SWP_NOMOVE);
}

void InputDataDlg::InitMsgBox(CExBaseList* pMsgs)
{
	CString strText;
	POS pos = pMsgs->GetHeadPosition();
	while (pos)
	{
		CSttMsg* pMsg = (CSttMsg*)pMsgs->GetNext(pos);
		strText += pMsg->m_strMsg;
		strText += '\n';
	}

	CRect rc;
	GetClientRect(rc);
	
	CRect rcBox(WND_OFFSET, WND_OFFSET, rc.Width() - 2 * WND_OFFSET, 0);
	CStatic* txtBox = new CStatic;
	BOOL bRet = txtBox->Create(strText, WS_CHILD | WS_VISIBLE, rcBox, this);
	txtBox->SetFont(this->GetFont());
	FitSize(txtBox, rcBox, strText);
	m_pLastCtrl = txtBox;
	m_vecStatics.push_back(txtBox);
}

void InputDataDlg::InitListBox(CExBaseList* pDatas)
{
	POS pos = pDatas->GetHeadPosition();
	while (pos)
	{
		CRect rc;
		GetClientRect(rc);
		long nWidth = rc.Width() - 2 * WND_OFFSET;
		long nHeight = rc.Height();

		CDvmData* pData = (CDvmData*)pDatas->GetNext(pos);
		if(pData->m_strDataType == "combobox")
		{
			long nX = WND_OFFSET, nY = WND_OFFSET;
			if(m_pLastCtrl)
			{
				CRect rcClient;
				m_pLastCtrl->GetWindowRect(rcClient);
				ScreenToClient(rcClient);
				nX = rcClient.left;
				nY = rcClient.bottom + WND_OFFSET;
			}

			CRect rcBox(nX, nY, nX + nWidth * 3 / 4, nY + 24);
			CStatic* pTxt = new CStatic;
			pTxt->Create(pData->m_strName, WS_CHILD | WS_VISIBLE, rcBox, this);
			pTxt->SetFont(this->GetFont());
			m_vecStatics.push_back(pTxt);
			FitSize(pTxt, rcBox, pData->m_strName);
			m_pLastCtrl = pTxt;

			if(rcBox.bottom > nHeight)
			{
				SetWindowPos(NULL, 0, 0, WND_WIDTH, rcBox.bottom, SWP_NOMOVE);
			}

			CUIComboBox* pCbb = new CUIComboBox;
			pCbb->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST,
				CRect(nX + nWidth * 3 / 4 + WND_OFFSET, nY, nX + nWidth, nY + 120), this, IDC_USER_INPUT + m_nListID++);
			pCbb->SetFont(this->GetFont());
			pCbb->InitUI(COLOR_LIGHTGRAY, COLOR_LIGHTGREEN);
			m_vecCtrls.push_back(pCbb);
			CDataType* pType = (CDataType*)g_pWzdMainDlg->m_oDataTypes.FindByID(pData->m_strFormat);
			if(pType)
			{
				POS posType = pType->GetHeadPosition();
				while (posType)
				{
					CDataTypeValue* pValue = (CDataTypeValue*)pType->GetNext(posType);
					pCbb->AddString(pValue->m_strName);
				}

				CDataTypeValue* pIndexValue = (CDataTypeValue*)pType->FindByID(pData->m_strValue);

				if (pIndexValue == NULL)
				{
					pIndexValue = (CDataTypeValue*)pType->FindByName(pData->m_strValue);
				}

				long nIndex = pType->FindIndex(pIndexValue);

				if (nIndex == -1)
				{
					nIndex = 0;
				}

				pCbb->SetCurSel(nIndex);
			}
		}
	}
}

void InputDataDlg::InitEditBox(CExBaseList* pDatas)
{
	POS pos = pDatas->GetHeadPosition();
	while (pos)
	{
		CRect rc;
		GetClientRect(rc);
		long nWidth = rc.Width() - 2 * WND_OFFSET;
		long nHeight = rc.Height();

		CDvmData* pData = (CDvmData*)pDatas->GetNext(pos);	
		if(pData->m_strDataType == "string" || pData->m_strDataType == "")
		{
			long nX = WND_OFFSET, nY = WND_OFFSET;
			if(m_pLastCtrl)
			{
				CRect rcClient;
				m_pLastCtrl->GetWindowRect(rcClient);
				ScreenToClient(rcClient);
				nX = rcClient.left;
				nY = rcClient.bottom + WND_OFFSET;
			}

			CRect rcBox(nX, nY, nX + nWidth * 3 / 4, nY + 24);
			CStatic* pTxt = new CStatic;
			pTxt->Create(pData->m_strName, WS_CHILD | WS_VISIBLE, rcBox, this);
			pTxt->SetFont(this->GetFont());
			m_vecStatics.push_back(pTxt);
			FitSize(pTxt, rcBox, pData->m_strName);
			m_pLastCtrl = pTxt;

			if(rcBox.bottom > nHeight)
			{
				SetWindowPos(NULL, 0, 0, WND_WIDTH, rcBox.bottom, SWP_NOMOVE);
			}

			CUIEdit* pEdit = new CUIEdit;
			pEdit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER,
				CRect(nX + nWidth * 3 / 4 + WND_OFFSET, nY, nX + nWidth, nY + 24), this,  + m_nEditID++);
			m_vecCtrls.push_back(pEdit);
			pEdit->SetFont(this->GetFont());
			pEdit->InitUI(COLOR_LIGHTGRAY);
			pEdit->SetWindowText(pData->m_strValue);
		}
	}
}

void InputDataDlg::KillTimer()
{
	CDialog::KillTimer(1);
}

void InputDataDlg::StartTimer()
{
	SetTimer(1, 3000, NULL);
}

void InputDataDlg::InitDlg(CExBaseList* pDatas, CExBaseList* pMsgs, CExBaseList *pItem)
{
	m_pDatas->AppendCloneEx2(*pDatas);
	m_pMsgs = pMsgs;
	m_pItem = pItem;

	//SetWindowPos(NULL, 0, 0, WND_WIDTH, WND_HEIGHT, SWP_NOMOVE | SWP_SHOWWINDOW);

	InitUI(COLOR_LIGHTGREEN, COLOR_DEEPBLUE);
	if(m_pItem)
	{
		SetWindowTitle(m_pItem->m_strName);	
	}
	else
	{
		SetWindowTitle("");
	}

	m_btnOK.InitUI("normal下一步.png", "hover下一步.png");

	CRect rcClient;
	if (m_pMsgs && m_pMsgs->GetCount())
	{
		InitMsgBox(m_pMsgs);
		CRect rcMsg;
		m_pLastCtrl->GetClientRect(rcMsg);
		
		GetClientRect(rcClient);
		SetWindowPos(NULL, 0, 0, WND_WIDTH, rcClient.Height() + rcMsg.Height(), SWP_NOMOVE);
	}

	if (m_pDatas && m_pDatas->GetCount())
	{
		InitListBox(m_pDatas);
		InitEditBox(m_pDatas);
	}

	CRect rcOK;
	m_btnOK.GetWindowRect(rcOK);
	GetClientRect(rcClient);
	SetWindowPos(NULL, 0, 0, WND_WIDTH, rcClient.Height() + rcOK.Height() + WND_HEIGHT, SWP_NOMOVE);

	GetClientRect(rcClient);
	ScreenToClient(rcOK);
	m_btnOK.SetWindowPos(NULL, rcOK.left, rcClient.bottom - rcOK.Height() - 10, 0, 0, SWP_NOSIZE);

	for (int i = 0; i < m_vecCtrls.size(); i++)
	{
		MoveChildWindow(m_vecCtrls[i]);
	}

	for (int i = 0; i < m_vecStatics.size(); i++)
	{
		MoveChildWindow(m_vecStatics[i]);
	}

	Invalidate();

	if (m_pItem == NULL && g_pWzdMainDlg->m_pAutoTest->GetPerConfirm())
	{
		SetTimer(1, 3000, NULL);
		return;
	}

	if (m_pItem && m_pItem->m_strID.Find(ID_CONSTANT_ITEM_PREFIX_CONFIRM) >= 0)
	{
		//固定的ID，不需要起定时器，必须人工确认
		return;
	}

	if (g_pWzdMainDlg->m_pAutoTest->GetPerConfirm())
	{
		SetTimer(1, 3000, NULL);
	}

}

void InputDataDlg::DoOK()
{
	POS pos = m_pDatas->GetHeadPosition();
	long nIndex = 0;
	while (pos)
	{
		CDvmData* pData = (CDvmData*)m_pDatas->GetNext(pos);
		if(pData->m_strDataType == "combobox")
		{
			CUIComboBox* pCbb = (CUIComboBox*)m_vecCtrls[nIndex];
			long nSel = pCbb->GetCurSel();

			CDataType* pType = (CDataType*)g_pWzdMainDlg->m_oDataTypes.FindByID(pData->m_strFormat);
			CDataTypeValue* pValue = (CDataTypeValue*)pType->GetAt(nSel);
			pData->m_strValue = pValue->m_strName;
		}

		nIndex++;
	}

	nIndex = 0;
	pos = m_pDatas->GetHeadPosition();
	while (pos)
	{
		CDvmData* pData = (CDvmData*)m_pDatas->GetNext(pos);
		if(pData->m_strDataType == "string" || pData->m_strDataType == "")
		{
			CEdit* pEdit = (CEdit*)m_vecCtrls[nIndex];
			CString strText;
			pEdit->GetWindowText(strText);
			pData->m_strValue = strText;
		}

		nIndex++;
	}

	g_pWzdMainDlg->FinishInputData(m_pDatas);

	OnOK();
 	DestroyWindow();
 	delete this;
	g_pWzdMainDlg->m_pAutoTest->ClearInputDlg();
}

void InputDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnOK);
}

BEGIN_MESSAGE_MAP(InputDataDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDOK, &InputDataDlg::OnBnClickedOk)
END_MESSAGE_MAP()

void InputDataDlg::OnPaint()
{
	CRect rc;
	GetClientRect(rc);
	rc.top += 20;
	rc.bottom -= 50;
	rc.left += 5;
	rc.right -= 5;

	CPaintDC dc(this);
	dc.FillSolidRect(rc, RGB(255, 255, 255));
}

void InputDataDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == 1)
	{
		CDialog::KillTimer(nIDEvent);
		DoOK();
	}
}

void InputDataDlg::OnBnClickedOk()
{
	CDialog::KillTimer(1);
	DoOK();
}