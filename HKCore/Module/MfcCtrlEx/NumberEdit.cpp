// NumberEdit.cpp : implementation file
//

#include "stdafx.h"

#include "NumberEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNumberEdit
CNumberEdit::CNumberEdit()
{
	m_nFormat          = 0;
	m_bFocus		   = FALSE;
	m_euForamt			= FM_NONE;

	m_bUseMin = FALSE;
	m_bUseMax = FALSE;
	m_nMinValue = 0;
	m_nMaxValue = 0;
	m_fMinValue = 0;
	m_fMaxValue = 0;

}

CNumberEdit::~CNumberEdit()
{
}

BEGIN_MESSAGE_MAP(CNumberEdit, CEdit)
	//{{AFX_MSG_MAP(CNumberEdit)
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	ON_CONTROL_REFLECT(EN_KILLFOCUS, OnKillfocus)
	ON_CONTROL_REFLECT(EN_SETFOCUS, OnSetfocus)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNumberEdit message handlers
// 
// BOOL CNumberEdit::UICreate(CWnd *pParent)
// {
// 	if ( m_pWindow != NULL )
// 	{
//         LOG_WriteLawString("recreate button");
//     }
// 	
//     CRect rect = GetWndPosition();
// 	
//     BOOL status = Create(
//         WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT | WS_BORDER,
//         rect,
//         pParent,
//         GenerateWindowID());
// 	
//     if ( !status )
// 	{
// 		return FALSE;
// 	}
// 	
// 	if (m_euForamt == FM_Password)
// 	{
// 		this->SetPasswordChar('*');
// 	}
// 	
// 	CUIBaseFont *pFont = GetUIBaseFont();
// 	
// 	if (pFont != NULL)
// 	{
// 		SetFont(pFont->m_pFont);
// 	}
// 	
// 	if (m_pWndText != NULL)
// 	{
// 		SetWindowText( m_strText);
// 	}
// 	else
// 	{
// 		SetWindowText(m_strID);
// 	}
// 	ShowWindow(SW_SHOW);
// 	
// 	m_pWindow = this;
// 	
// 	return TRUE;
// }

void CNumberEdit::OnChange() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CEdit::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	GetWindowText(m_strText);
}

void CNumberEdit::OnKillfocus() 
{
	// TODO: Add your control notification handler code here
	m_bFocus = FALSE;
	UpdateUnit();//当单位不为空时,焦点切换时,需要增加对应的单位信息
}

void CNumberEdit::OnSetfocus() 
{
	// TODO: Add your control notification handler code here
	m_bFocus = TRUE;
}

void CNumberEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar == VK_DOWN)
	{
		ArrowDown();
		///InitByMinMaxValue();
	}
	else if (nChar == VK_UP)
	{
		ArrowUp();
		//InitByMinMaxValue();
	}
	else if (nChar == VK_LEFT)
	{
		ArrowLeft();
	}
	else if (nChar == VK_RIGHT)
	{
		ArrowRight();
		//CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
	}
	else
	{
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);

		if (nChar == VK_DELETE)
		{
			InitByMinMaxValue();
		}
	}
}

void CNumberEdit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
// 	if (nChar == VK_DOWN || nChar == VK_UP || nChar == VK_LEFT || nChar == VK_RIGHT)
// 	{
// 	}
// 	else
	{
		CEdit::OnKeyUp(nChar, nRepCnt, nFlags);
	}
}

//////////////////////////////////////////////////////////////////////////
//系统消息处理方法
//long CNumberEdit::OnSystemMessage(UINT nSysMsgID, long &nImpCount, long &nRunCount)
// {
// 	if (m_pSysMsgMaps != NULL)
// 	{
// 		CMessageImp *pSysMsgImp = FindBySysMsgID(nSysMsgID);
// 		
// 		if (pSysMsgImp != NULL)
// 		{
// 			if (pSysMsgImp == m_pSysMsgArrowUp)
// 			{
// 				if (m_bFocus)
// 				{
// 					ArrowUp();
// 				}
// 				
// 			}
// 			else if (pSysMsgImp == m_pSysMsgArrowDown)
// 			{
// 				if (m_bFocus)
// 				{
// 					ArrowDown();
// 				}
// 			}
// 			else if (pSysMsgImp == m_pSysMsgArrowLeft)
// 			{		
// 				if (m_bFocus)
// 				{
// 					ArrowLeft();
// 				}		
// 			}
// 			else if (pSysMsgImp == m_pSysMsgArrowRight)
// 			{
// 				if (m_bFocus)
// 				{
// 					ArrowRight();
// 				}
// 			}
// 			else
// 			{
// 			}
// 		}
// 	}	
// 	return 0;
// }
void CNumberEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(nChar == VK_DOWN||nChar == VK_UP)
	{

	}
	else if ((nChar >= '0' && nChar <= '9') || nChar == '.')
	{
		if (m_euForamt == FM_Integer)
		{
			if (nChar != '.')
			{
				CEdit::OnChar(nChar, nRepCnt, nFlags);
			}
		}
		else
		{
			if (m_euForamt == FM_Float)
			{
				int nIndex = m_strText.FindOneOf(_T("."));
				
				if (nIndex > -1 &&  nChar == '.')
				{				
				}
				else
				{
					CEdit::OnChar(nChar, nRepCnt, nFlags);
				}
			}
			else
			{
				CEdit::OnChar(nChar, nRepCnt, nFlags);
			}

			InitByMinMaxValue();	
		}
	}
	else if (nChar=='-' || nChar=='+')
	{
		int nIndex = m_strText.Find(nChar);

		if (nIndex >= 0)
		{				
		}
		else
		{
			DWORD nSel = GetSel();

			if (nSel == 0)
			{
				CEdit::OnChar(nChar, nRepCnt, nFlags);
			}
		}
	}
	else if(nChar == VK_LEFT || nChar == VK_RIGHT)
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	else if (nChar == VK_BACK)
	{	
		CEdit::OnChar(nChar, nRepCnt, nFlags);
		InitByMinMaxValue();
	}
}

void CNumberEdit::ArrowUp()
{
	int nStart, nEnd;
	GetSel(nStart,nEnd);
	CString strText =  m_strText;
	int nLength = strText.GetLength();
	TCHAR chCurr = 0;
	
	switch(m_euForamt)
	{
	case FM_Float:
		{	
			if (nStart>=nLength)
			{
				chCurr = '0';
			}
			else
			{
				chCurr = strText.GetAt(nStart);
				
				if (chCurr == '.')
				{
					chCurr = '0';
				}
				else
				{
					chCurr++;
				}
				
				if (chCurr > '9')
				{
					chCurr = '.';
				}
			}
			
			strText.Format(_T("%c"),chCurr);
			UpdateText(strText , nStart ,nStart);
		}
		break;
	case FM_Integer:
		{									
			if (nStart>=nLength) 
			{
				chCurr = '0';
			}
			else
			{
				chCurr = strText.GetAt(nStart);
				chCurr++;

				if (chCurr>'9')
				{
					chCurr = '0';
				}
			}
					
			strText.Format(_T("%c"),chCurr);
			UpdateText(strText , nStart ,nStart);
		}
		break;
	}

	InitByMinMaxValue();
}

void CNumberEdit::ArrowDown()
{
	int nStart, nEnd;
	GetSel(nStart,nEnd);
	CString strText =  m_strText;
	int nLength = strText.GetLength();	
	TCHAR chCurr = 0;
	
	switch(m_euForamt)
	{
	case FM_Float:
		{
			int nIndex = strText.FindOneOf(_T("."));	
			int nTempValue = 0;	

			if (nStart>=nLength) 
			{
			}
			else
			{
				chCurr = strText.GetAt(nStart);

				if (chCurr == '.')
				{
					chCurr = '9';
				}
				else
				{
					chCurr--;
				}
				
				if (chCurr < '0')
				{
					chCurr = '.';
				}		
			}
			
			strText.Format(_T("%c"),chCurr);
			UpdateText(strText , nStart ,nStart);
		}
		break;
	case FM_Integer:
		{		
			if (nStart>=nLength) 
			{
				chCurr = '0';
			}
			else
			{
				chCurr = strText.GetAt(nStart);
				chCurr--;

				if (chCurr<'0')
				{
					chCurr = '9';
				}
			}
			
			strText.Format(_T("%c"),chCurr);
			UpdateText(strText , nStart ,nStart);
		}
		break;
	}

	InitByMinMaxValue();
}

void CNumberEdit::UpdateText(CString &strText, int nStart, int nEnd)
{
	SetSel(nStart, nEnd+1);
	ReplaceSel(strText);
	SetFocus();
	SetSel(nStart, nEnd);
}

void CNumberEdit::ArrowLeft()
{
	int nStart, nEnd;
	GetSel(nStart,nEnd);

	if (nStart>0)
	{
		nStart--;
	}

	SetFocus();
	SetSel(nStart, nStart);
}

void CNumberEdit::ArrowRight()
{
	int nStart, nEnd;
	GetSel(nStart,nEnd);
	int nLength =  m_strText.GetLength();
	
	if (nStart<nLength)
	{
		nStart++;
	}
	
	SetFocus();
	SetSel(nStart, nStart);
}

void CNumberEdit::InitByMinMaxValue()
{
	if (m_euForamt == FM_Float)
	{
		InitByMinMaxValueFloat();
	}
	else if (m_euForamt == FM_Integer)
	{
		InitByMinMaxValueLong();
	}
}

void CNumberEdit::InitByMinMaxValueLong()
{
	if (m_bUseMin)
	{
		long nValue = CString_To_long(m_strText);
		if (nValue < m_nMinValue)
		{
			SetValue(m_nMinValue);
		}
	}

	if (m_bUseMax)
	{
		long nValue = CString_To_long(m_strText);
		if (nValue > m_nMaxValue)
		{
			SetValue(m_nMaxValue);
		}
	}
}

void CNumberEdit::InitByMinMaxValueFloat()
{
	if (m_bUseMin)
	{
		double dValue = CString_To_double(m_strText);
		if (dValue < m_fMinValue)
		{
			SetValue(m_fMinValue);
		}
	}

	if (m_bUseMax)
	{
		double dValue = CString_To_double(m_strText);
		if (dValue > m_fMaxValue)
		{
			SetValue(m_fMaxValue);
		}
	}
}

void CNumberEdit::UpdateUnit()
{
	if ((!m_strUnit.IsEmpty())&&(!m_strFormat.IsEmpty()))
	{
		CString strValue;

		if (m_euForamt == FM_Integer)
		{
			long nValue = 0;
			GetValue(nValue);
			SetValue(nValue);
		} 
		else if (m_euForamt == FM_Float)
		{
			float fValue = 0;
			GetValue(fValue);
			SetValue(fValue);
		}


	}
}

