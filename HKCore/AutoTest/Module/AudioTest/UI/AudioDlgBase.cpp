// ParaDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "AudioDlgBase.h"
// CParaDialo
#include "../../../AudioTest/AudioTestDlg.h"
CAudioDlgBase::CAudioDlgBase(int nID,CWnd* pParent)
		: CDialog(nID, pParent)
{
	m_nScollMin = 0;
	m_nScollMax = 0;
	m_nPageStep = 3;
	m_nCurrentPagePos = 0;
	m_strResult = "";
	m_pListCtrl = NULL;
}

CAudioDlgBase::~CAudioDlgBase()
{
}

BOOL CAudioDlgBase::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN)
	{
		return TRUE; 
	}
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE) 
	{
		return TRUE; 
	}
	return CDialog::PreTranslateMessage(pMsg);
}

int CAudioDlgBase::GetCurrentSelectRow()
{
	POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition();
	return m_pListCtrl->GetNextSelectedItem(pos);
}
// CParaDialog 消息处理程序

void CAudioDlgBase::SetResult(CString& strResult)
{
	m_strResult = strResult;
}

CString CAudioDlgBase::GetResult()
{
	if(m_strResult == "")
	{
		return GetCurrentResult();
	}
	return m_strResult;
}

CString CAudioDlgBase::GetCurrentResult()
{
	POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition();
	long nIndex = m_pListCtrl->GetNextSelectedItem(pos);
	m_strResult =  m_pListCtrl->GetItemText(nIndex, 1);
	return m_strResult;
}

void CAudioDlgBase::SetListCtrl(CListCtrl*	pListCtrl)
{
	m_pListCtrl = pListCtrl;
}

CListCtrl* CAudioDlgBase::GetListCtrl()
{
	return m_pListCtrl;
}

void CAudioDlgBase::SetListData(CDvmData* pData)
{
	if(pData == NULL || m_pListCtrl == NULL)
	{
		return;
	}
	for (int i = 0; i < pData->GetCount(); i++)
	{
		CDvmValue* pValue = (CDvmValue*)pData->GetAt(i);
		CString strIndex;
		strIndex.Format(_T("%d"),i+1);
		m_pListCtrl->InsertItem(i,strIndex);
		m_pListCtrl->SetItemText(i,1,pValue->m_strName);
	}

	m_pListCtrl->GetScrollRange(SB_VERT,&m_nScollMin,&m_nScollMax);
	//m_pListCtrl->SetItemState(0, LVIS_DROPHILITED | LVIS_SELECTED, LVIS_DROPHILITED | LVIS_SELECTED);
	m_pListCtrl->SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
	//m_pListCtrl->SetFocus();
}

void CAudioDlgBase::SetBackPage()
{
	m_nCurrentPagePos = m_pListCtrl->GetScrollPos(SB_VERT);
	if(m_nCurrentPagePos <= m_nScollMin)
	{
		m_nCurrentPagePos = m_nScollMin;
	}
	else
	{
		m_nCurrentPagePos -= m_nPageStep;
		if(m_nCurrentPagePos <= m_nScollMin)
		{
			m_nCurrentPagePos = m_nScollMin;
		}
	}
	CSize size(0,-42);
	m_pListCtrl->Scroll(size);
	m_pListCtrl->SetScrollPos(SB_VERT, m_nCurrentPagePos);
}

void CAudioDlgBase::SetNextPage()
{
	m_nCurrentPagePos = m_pListCtrl->GetScrollPos(SB_VERT);
	if(m_nCurrentPagePos >= m_nScollMax)
	{
		m_nCurrentPagePos = m_nScollMax;
	}
	else
	{
		m_nCurrentPagePos += m_nPageStep;
		if(m_nCurrentPagePos >= m_nScollMax)
		{
			m_nCurrentPagePos = m_nScollMax;
		}
	}
	CSize size(0,42);
	m_pListCtrl->Scroll(size);
	m_pListCtrl->SetScrollPos(SB_VERT, m_nCurrentPagePos);
}

void CAudioDlgBase::SetListSelectRow(int nRow,int nLastRow)
{
	int nRowCount = m_pListCtrl->GetItemCount();
	//m_pListCtrl->SetItemState(nRow,  LVIS_DROPHILITED | LVIS_SELECTED, LVIS_DROPHILITED | LVIS_SELECTED);
	m_pListCtrl->SetItemState(nRow,  LVIS_SELECTED, LVIS_SELECTED);
	//m_pListCtrl->SetFocus();
	//m_pListCtrl->SetSelectionMark(nRow);

	UINT nState = m_pListCtrl->GetItemState(nRow,LVIF_STATE);   
	nState &=! nState;
	if(nLastRow == -1)
	{
		for(int i = 0;i < nRowCount;i++)
		{
			if(i != nRow)
			{
				m_pListCtrl->SetItemState(i,nState,LVIF_STATE);
			}
		}	
	}
	else
	{
		m_pListCtrl->SetItemState(nLastRow,nState,LVIF_STATE);
	}
}

//模拟 鼠标单击事件
void CAudioDlgBase::SetRowHightLight(int nRow,int nLastRow)
{
	// 备份光标初始位置
	/*CPoint initPos;
	GetCursorPos(&initPos);

	m_nListStateFlag = 1;

	CRect itemRect;
	m_pListCtrl->GetItemRect(nRow, itemRect, LVIR_BOUNDS);
	CRect ctrlRect;
	m_pListCtrl->GetWindowRect(ctrlRect);

	// 转换成相对父对话框的
	itemRect.left += ctrlRect.left;
	itemRect.top += ctrlRect.top;

	SetCursorPos(itemRect.left + 2, itemRect.top + 2); 
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0); 
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0); 

	// 恢复光标初始位置
	SetCursorPos(initPos.x, initPos.y);*/

}

void CAudioDlgBase::FindSelectAnswer(CString strResult)
{
	int nRowCount = m_pListCtrl->GetItemCount();
	int nLastSelRow = GetCurrentSelectRow();
	for (int i = 0;i < nRowCount;i++)
	{
		CString strRow = m_pListCtrl->GetItemText(i,1);
		if(strRow == strResult)
		{
			SetListSelectRow(i,nLastSelRow);
			return;
		}
	}
	//模板的 模糊查询
	for (int n = 0;n < nRowCount;n++)
	{
		CString strRow = m_pListCtrl->GetItemText(n,1);
		if(strRow.Find(strResult) >= 0)
		{
			SetListSelectRow(n,nLastSelRow);
			return;
		}
	}
}
