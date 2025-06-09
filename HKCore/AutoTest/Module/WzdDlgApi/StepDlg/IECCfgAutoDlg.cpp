#include "stdafx.h"
#include "IECCfgAutoDlg.h"
#include "../WzdDlgDef.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgDatasMngr.h"

#define IECAUTOBTN_FIRST 30001
#define BTN_HEIGHT  32
#define BTN_SPACE	10

void CIECAutoBtn::LButtonUp(UINT nFlags, CPoint point)
{
	CWzdDlgNormalBtn::LButtonUp(nFlags, point);
	CString strText;
	GetWindowText(strText);
	::SendMessage(GetParent()->m_hWnd, WM_IECCFG_CLICKED, (LPARAM)m_pData, (LPARAM)strText.GetString());
}

void CIECAutoBtn::SetCurrentType(long nType)
{
	CString strImg = _P_GetResourcePath();
	strImg += "iSmartTestWzd/";
	m_nType = nType;
	switch(nType)
	{
	case CURRENT:
	case CURRENTSAVE:
		LoadImage(strImg + "btn_select_n.png", strImg + "btn_select_y.png", strImg + "btn_select_h.png", strImg + "btn_d.png");
		break;
	case SAVE:
		LoadImage(strImg + "btn_auto_n.png", strImg + "btn_auto_y.png", strImg + "btn_auto_h.png", strImg + "btn_d.png");
		break;
// 	case CURRENTSAVE:
// 		LoadImage(strImg + "btn_aselect_n.png", strImg + "btn_aselect_y.png", strImg + "btn_aselect_h.png", strImg + "btn_d.png");
// 		break;
	default:
		LoadImage(strImg + "btn_n.png", strImg + "btn_y.png", strImg + "btn_h.png", strImg + "btn_d.png");
		m_nType = NORMAL;
		break;
	}
}

IMPLEMENT_DYNAMIC(CSmvIecfgDataMngrSelDlg, CDialog)
BEGIN_MESSAGE_MAP(CSmvIecfgDataMngrSelDlg, CDialog)
	ON_MESSAGE(WM_IECCFG_CLICKED, &CSmvIecfgDataMngrSelDlg::OnClickBtn)
	ON_WM_PAINT()
END_MESSAGE_MAP()

CSmvIecfgDataMngrSelDlg::CSmvIecfgDataMngrSelDlg(CWnd* pParent /*=NULL*/)
: CDialog(CSmvIecfgDataMngrSelDlg::IDD, pParent)
{
	CIECCfgAutoLine oLine;
	m_oBtnsGrid.m_vecLines.push_back(oLine);
	m_pFont = NULL;
	m_pList = NULL;
	m_bBtnsHasShow = FALSE;
}

CSmvIecfgDataMngrSelDlg::~CSmvIecfgDataMngrSelDlg()
{
	
};

void CSmvIecfgDataMngrSelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CSmvIecfgDataMngrSelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	//AutoShowBtns();
	return TRUE;
}

void CSmvIecfgDataMngrSelDlg::UpdateBbns()
{
	if (m_bBtnsHasShow)
	{
		return;
	}

	//2022-4-17 lijunqing 如果数据不改变，不做更新
	m_bBtnsHasShow = TRUE;
	AutoShowBtns();
}

void CSmvIecfgDataMngrSelDlg::AttachDatas(CExBaseList* pList)
{
	m_pList = pList;
}

BOOL CSmvIecfgDataMngrSelDlg::AddToLine(CExBaseObject* pObj, long nIndex)
{
	long nWidth = m_nMaxWidth - 4 * BTN_SPACE;
	long nExistedWidth = 0;
	for (int i = 0; i < m_oBtnsGrid.m_vecLines[nIndex].m_vecElements.size(); i++)
	{
		nExistedWidth += nWidth / 3 + BTN_SPACE;
	}

	if(nExistedWidth + nWidth / 3 + BTN_SPACE > m_nMaxWidth)
	{
		return FALSE;
	}

	m_oBtnsGrid.m_vecLines[nIndex].m_vecElements.push_back(pObj);

	return TRUE;
}

void CSmvIecfgDataMngrSelDlg::AddButton(CExBaseObject* pObj)
{
	//不支持空名按钮的创建
	if(!pObj->m_strName.GetLength())
	{
		return;
	}

	BOOL bRes = FALSE;
	long nLines = m_oBtnsGrid.m_vecLines.size();
	for (int i = 0; i < nLines; i++)
	{
		bRes = AddToLine(pObj, i);	
		if(bRes)
		{
			break;
		}
	}

	if(!bRes)
	{	
		CIECCfgAutoLine oLine;
		m_oBtnsGrid.m_vecLines.push_back(oLine);
		AddToLine(pObj, nLines);
	}
}

void CSmvIecfgDataMngrSelDlg::AutoShowBtns()
{
	if (m_pList && m_pList->GetCount())
	{
		//获取窗口宽度
		if(!m_pParentWnd)
		{
			return;
		}

		if(!m_pFont)
		{
			m_pFont = m_pParentWnd->GetFont();
		}

		CRect rc;
		m_pParentWnd->GetClientRect(rc);
		m_nMaxWidth = rc.Width();
		m_nMaxHeight = rc.Height();

		//确认行长度与按钮数目的关系
		POS pos = m_pList->GetHeadPosition();
		while (pos)
		{
			CIecCfgDatasMngr* pDatasMngr = (CIecCfgDatasMngr*)m_pList->GetNext(pos);
			AddButton(pDatasMngr);
		}

		unsigned int uID = IECAUTOBTN_FIRST;
		long nTop = BTN_SPACE;
		for (int i = 0; i < m_oBtnsGrid.m_vecLines.size(); i++)
		{
			long nLeft = BTN_SPACE;
			long nWidth = m_nMaxWidth - 4 * BTN_SPACE;
			for(int n = 0; n < m_oBtnsGrid.m_vecLines[i].m_vecElements.size(); n++)
			{
				CExBaseObject* pObj = m_oBtnsGrid.m_vecLines[i].m_vecElements[n];
				CIECAutoBtn* pBtn = new CIECAutoBtn;
				pBtn->Create(pObj->m_strName, WS_CHILD | WS_VISIBLE, CRect(nLeft, nTop, nLeft + nWidth / 3, nTop + BTN_HEIGHT), this, uID);
				pBtn->SetFont(m_pFont);
				pBtn->m_pData = pObj;
				m_vecBtns.push_back(pBtn);
				nLeft += nWidth / 3 + BTN_SPACE;
				uID++;
			}
			nTop += BTN_HEIGHT + BTN_SPACE;
		}

		MoveWindow(rc);
	}
}

//20230620 huangliang 界面变化后，按钮位置大小需要跟随变化
void CSmvIecfgDataMngrSelDlg::XUI_InitAdjust()
{
	if(!m_pParentWnd)
	{
		return;
	}

	CRect rc;
	m_pParentWnd->GetClientRect(rc);
	m_nMaxWidth = rc.Width();
	m_nMaxHeight = rc.Height();

	long nLeft = BTN_SPACE;
	long nTop = BTN_SPACE;
	long nWidth = m_nMaxWidth - 4 * BTN_SPACE;
	for (int i = 0; i < m_vecBtns.size(); i++)
	{
		nLeft = (i%3)*(nWidth / 3 + BTN_SPACE) + BTN_SPACE;
		nTop = (i/3)*(BTN_HEIGHT + BTN_SPACE) + BTN_SPACE;

		CRect rcBtn(nLeft, nTop, nLeft + nWidth / 3, nTop + BTN_HEIGHT);
		m_vecBtns[i]->MoveWindow(rcBtn);
	}
}

BOOL CSmvIecfgDataMngrSelDlg::Exit()
{
	ShowWindow(SW_HIDE);
	return TRUE;
// 	for(int i = 0; i < m_vecBtns.size(); i++)
// 	{
// 		delete m_vecBtns[i];
// 	}
// 	m_vecBtns.clear();
// 	m_oBtnsGrid.m_vecLines.clear();
// 	return CDialog::DestroyWindow();
}

BOOL CSmvIecfgDataMngrSelDlg::Create(CWnd* pParentWnd)
{
	m_pParentWnd = pParentWnd;
	return CDialog::Create(IDD, pParentWnd);

// 	BOOL bRes = Exit();
// 	if(!bRes)
// 	{
// 		m_pParentWnd = pParentWnd;
// 		return CDialog::Create(IDD, pParentWnd);
// 	}
// 	else
// 	{
// 		return FALSE;
// 	}
}

HRESULT CSmvIecfgDataMngrSelDlg::OnClickBtn(WPARAM wParam, LPARAM lParam)
{
	ClearBtnTypes();
	CString strText = (char*)lParam;
	for (int i = 0; i < m_vecBtns.size(); i++)
	{
		if(m_vecBtns[i]->m_pData->m_strName == strText)
		{
			if(m_vecBtns[i]->m_nType == CIECAutoBtn::NORMAL)
			{
				m_vecBtns[i]->SetCurrentType(CIECAutoBtn::CURRENT);
			}
			else if(m_vecBtns[i]->m_nType == CIECAutoBtn::SAVE)
			{
				m_vecBtns[i]->SetCurrentType(CIECAutoBtn::CURRENTSAVE);
			}
			break;
		}
	}
	m_pParentWnd->SendMessage(WM_IECCFG_CLICKED, wParam, lParam);
	return Exit();
}

void CSmvIecfgDataMngrSelDlg::OnPaint()
{
	CRect rect;
	CPaintDC dc(this);
	GetClientRect(rect);
	dc.FillSolidRect(rect, g_crLightBlue);  //设置为绿色背景
	CDialog::OnPaint();
}

void CSmvIecfgDataMngrSelDlg::ClearBtnTypes()
{
	for (int i = 0; i < m_vecBtns.size(); i++)
	{
		if(m_vecBtns[i]->m_nType == CIECAutoBtn::CURRENT)
		{
			m_vecBtns[i]->SetCurrentType(CIECAutoBtn::NORMAL);
		}
		else if (m_vecBtns[i]->m_nType == CIECAutoBtn::CURRENTSAVE)
		{
			m_vecBtns[i]->SetCurrentType(CIECAutoBtn::SAVE);
		}
	}
}

void CSmvIecfgDataMngrSelDlg::SetBtnType(CString strName, long nType)
{
	ClearBtnTypes();
	for (int i = 0; i < m_vecBtns.size(); i++)
	{
		if(m_vecBtns[i]->m_pData->m_strName == strName)
		{
			m_vecBtns[i]->SetCurrentType(nType);
			break;
		}
	}
}