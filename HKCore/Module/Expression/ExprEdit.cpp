// D:\WorkLIJQ\Source\Module\Expression\ExprEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "ExprEdit.h"


#define XID_EXPREDIT_OPTR_COPY    1451
#define XID_EXPREDIT_OPTR_PASTE   1452

BOOL Expr_IsStringFunc(const CString &strText)
{
	static const CString g_strExprFunc[] = {_T("SIN"), _T("COS"), _T("EXP"), _T("SQRT"), _T("LOG"), _T("TG"), _T("CTG"), _T("ASIN")
			, _T("ACOS"), _T("ATG") 
			, _T("SIND"), _T("COSD"), _T("TGD"), _T("CTGD"), _T("ASIND"), _T("ACOSD"), _T("ATGD") 
			, _T("")};

	CString strTemp = strText;
	strTemp.MakeUpper();
	long nIndex = 0;
	BOOL bFind = FALSE;

	while (g_strExprFunc[nIndex].GetLength() > 0)
	{
		if (g_strExprFunc[nIndex] == strTemp)
		{
			bFind = TRUE;
			break;
		}

		nIndex++;
	}

	return bFind;
}

BOOL Expr_IsCharOptr(TCHAR chChar)
{
	static TCHAR g_ptcharOptr[MAX_PATH] = _T("+-*/(),\0\0\0\0\0\0\0\0"); 
	TCHAR *pChar = g_ptcharOptr;

	while (*pChar != 0)
	{
		if (chChar == *pChar)
		{
			return TRUE;
		}

		pChar++;
	}

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
CExprVariableFind::CExprVariableFind()
{

}

CExprVariableFind::~CExprVariableFind()
{

}

CExBaseObject* CExprVariableFind::FindVariableByID(const CString &strID)
{
	return NULL;
}

CExBaseObject* CExprVariableFind::FindVariableByName(const CString &strName)
{
	return NULL;
}

void CExprVariableFind::OnExprScriptChanged(const CString &strExprScript)
{

}

//////////////////////////////////////////////////////////////////////////
BOOL CExprEdit::g_bIsInProcessing = FALSE;
CString CExprEdit::g_strExprEditCopyString = _T("");

BOOL CExprTextUnit::IsNumber()
{
	return IsStringNumber(m_strUnitScpt);
}

BOOL CExprTextUnit::IsVariable()
{
	if (IsNumber())
	{
		return FALSE;
	}

	if (IsOptr())
	{
		return FALSE;
	}

	if (IsFunc())
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CExprTextUnit::IsOptr()
{
	if (m_strUnitScpt.GetLength() != 1)
	{
		return FALSE;
	}

	return Expr_IsCharOptr(m_strUnitScpt.GetAt(0));
}

BOOL CExprTextUnit::IsFunc()
{
	return Expr_IsStringFunc(m_strUnitScpt);
}

BOOL CExprTextUnit::InsertChar(TCHAR chChar, int nPos)
{
	if (!IsNumber())
	{
		return FALSE;
	}

	m_strUnitScpt.Insert(nPos, chChar);
	m_strUnitText = m_strUnitScpt;

	return TRUE;
}

BOOL CExprTextUnit::AppendChar(TCHAR chChar)
{
	m_strUnitScpt.AppendChar(chChar);
	m_strUnitText = m_strUnitScpt;
	return TRUE;
}

CString CExprTextUnit::GetString()
{
	return m_strUnitText;
// 	if (IsNumber())
// 	{
// 		return m_strUnitText;
// 	}
// 
// 	if (IsFunc())
// 	{
// 		return m_strUnitText;
// 	}
}

void CExprTextUnit::SetTChar(TCHAR chChar)
{
	m_strUnitScpt = chChar;
	m_strUnitText = m_strUnitScpt;
}

void CExprTextUnit::SetString(const CString &strText)
{
	m_strUnitScpt = strText;
	m_strUnitText = strText;
}

CExprTextUnit* CExprTextUnitList::GetExprTextUnit(int nBeginPos, int nEndPos)
{
	CExprTextUnitList oList;
	GetExprTextUnits(nBeginPos, nEndPos, oList);
	CExprTextUnit *pUnit = NULL;

	if (oList.GetCount() == 1)
	{
		pUnit = oList.GetHead();
	}

	oList.RemoveAll();
	return pUnit;
}

int CExprTextUnitList::GetExprTextUnits(int nBeginPos, int nEndPos, CExprTextUnitList &oList)
{
	int nPos1=0, nPos2 = 0;
	POS pos = GetHeadPosition();
	CExprTextUnit *p = NULL;
	int nLen = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nPos2 = nPos1 + p->m_strUnitText.GetLength();

		//if (((nBeginPos <= nPos1 && nPos1 <= nEndPos) || (nBeginPos < nPos2 && nPos2 < nEndPos))
		//	|| ((nPos1 <= nBeginPos && nBeginPos < nPos2) || (nPos1 < nEndPos && nEndPos < nPos2)) )
		if (IsIntersect(nPos1, nPos2, nBeginPos, nEndPos))
		{
			oList.AddTail(p);
		}

		nPos1 = nPos2;
	}

	return oList.GetCount();
}

void CExprTextUnitList::GetExprTextUnitsPos(CExprTextUnitList &oList, int &nBeginPos, int &nEndPos)
{
	if (oList.GetCount() == 0)
	{
		nBeginPos = 0;
		nEndPos = 0;
		return;
	}

	CExprTextUnit *pHead = oList.GetHead();
	CExprTextUnit *pTail = oList.GetTail();
	int nPos11=0, nPos12 = 0;
	int nPos21=0, nPos22 = 0;
	
	GetExprTextUnitPos(pHead, nPos11, nPos12);
	GetExprTextUnitPos(pHead, nPos21, nPos22);

	nBeginPos = min(nPos11, nPos21);
	nEndPos = max(nPos12, nPos22);
}

void CExprTextUnitList::GetExprTextUnitPos(CExprTextUnit *pExprTextUnit, int &nBeginPos, int &nEndPos)
{
	int nPos1=0, nPos2 = 0;
	POS pos = GetHeadPosition();
	CExprTextUnit *p = NULL;
	int nLen = 0;
	BOOL bFind = FALSE;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nPos2 = nPos1 + p->m_strUnitText.GetLength();

		if (p == pExprTextUnit)
		{
			nBeginPos = nPos1;
			nEndPos = nPos2;
			bFind = TRUE;
			break;
		}

		nPos1 = nPos2;
	}
}

CExprTextUnit* CExprTextUnitList::FindPrevExprTextUnit(CExprTextUnit *pExprTextUnit)
{
	POS pos = Find(pExprTextUnit);

	if (pos == NULL)
	{
		return NULL;
	}

	GetPrev(pos);

	if (pos == NULL)
	{
		return NULL;
	}

	return GetAt(pos);
}

CExprTextUnit* CExprTextUnitList::FindNextExprTextUnit(CExprTextUnit *pExprTextUnit)
{
	POS pos = Find(pExprTextUnit);

	if (pos == NULL)
	{
		return NULL;
	}

	GetNext(pos);

	if (pos == NULL)
	{
		return NULL;
	}

	return GetAt(pos);
}

CExprTextUnit* CExprTextUnitList::NewTextUnit(TCHAR chChar)
{
	CExprTextUnit *pNew = new CExprTextUnit(chChar);
	AddTail(pNew);
	return pNew;
}

BOOL CExprTextUnitList::IsIntersect(int nBegin, int nEnd, int nBeginRef, int nEndRef)
{//
	if (nBeginRef == nEndRef)
	{
		if (nBegin <= nBeginRef && nBeginRef < nEnd)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	if (nBegin <nBeginRef && nEnd <= nBeginRef)
	{
		return FALSE;
	}

	if (nEndRef <=nBegin && nEndRef < nEnd)
	{
		return FALSE;
	}

	

	return TRUE;
}

void CExprTextUnitList::InitStringUnit(CExprTextUnit *pUnit)
{
	if (pUnit->IsVariable())
	{
		ASSERT (m_pExprVariableFind != NULL);

		if (m_pExprVariableFind != NULL)
		{
			CExBaseObject *pFind = (CExBaseObject*)m_pExprVariableFind->FindVariableByID(pUnit->m_strUnitScpt);

			if (pFind != NULL)
			{
				pUnit->m_strUnitText = pFind->m_strName;
			}
		}
	}
}

CExprTextUnit* CExprTextUnitList::NewTextUnit(const CString &strText)
{
	CExprTextUnit *pNew = new CExprTextUnit(strText);
	AddTail(pNew);

	if (pNew->IsVariable())
	{
		ASSERT (m_pExprVariableFind != NULL);

		if (m_pExprVariableFind != NULL)
		{
			CExBaseObject *pFind = (CExBaseObject*)m_pExprVariableFind->FindVariableByID(strText);

			if (pFind != NULL)
			{
				pNew->m_strUnitText = pFind->m_strName;
			}
		}
	}

	return pNew;
}

void CExprTextUnitList::SetExprScript(const CString &strExprScript)
{
	DeleteAll();
	long nCurr = 0;
	long nPrev = 0;
	long nLen = strExprScript.GetLength();
	CString strTemp;

	while (nCurr<nLen)
	{
		TCHAR chChar = strExprScript.GetAt(nCurr);

		if (Expr_IsCharOptr(chChar))
		{
			if (nCurr == nPrev)
			{
				NewTextUnit(chChar);
			}
			else
			{
				strTemp = strExprScript.Mid(nPrev, nCurr-nPrev);
				NewTextUnit(strTemp);
				NewTextUnit(chChar);
			}

			nCurr++;
			nPrev = nCurr;
		}
		else
		{
			nCurr++;
		}
	}

	if (nCurr > nPrev)
	{
		strTemp = strExprScript.Mid(nPrev, nCurr-nPrev);
		NewTextUnit(strTemp);
	}
}

void CExprTextUnitList::GetExprScript(CString &strExprScript) const 
{
	POS pos = GetHeadPosition();
	CExprTextUnit *pUnit = NULL;
	strExprScript.Empty();

	while (pos != NULL)
	{
		pUnit = GetNext(pos);
		strExprScript += pUnit->m_strUnitScpt;
	}
}

CString CExprTextUnitList::GetExprScript()
{
	CString strText;
	GetExprScript(strText);
	return strText;
}

void CExprTextUnitList::GetExprScriptText(CString &strExprScript) const
{
	POS pos = GetHeadPosition();
	CExprTextUnit *pUnit = NULL;
	strExprScript.Empty();

	while (pos != NULL)
	{
		pUnit = GetNext(pos);
		strExprScript += pUnit->m_strUnitText;
	}
}

CString CExprTextUnitList::GetExprScriptText()
{
	CString strText;
	GetExprScriptText(strText);
	return strText;
}
// 
// void CExprTextUnitList::InsertText(int nBeginPos, int nEndPos, const CString &strText)
// {
// 	CExprTextUnitList oList;
// 	GetExprTextUnits(nBeginPos, nEndPos, oList);
// 	int iBegiPos2, nEndPos2;
// 	GetExprTextUnitsPos(oList, iBegiPos2, nEndPos2);
// 
// 	if (nBeginPos != iBegiPos2 || nEndPos2 != nEndPos)
// 	{
// 
// 	}
// }
// 
// BOOL CExprTextUnitList::CanInsertText(int nBeginPos, int nEndPos, const CString &strText)
// {
// 	return FALSE;
// }
// 
// BOOL CExprTextUnitList::CanInsertChar(int nPos)
// {
// 	return TRUE;
// }

// BOOL CExprTextUnitList::CanDelete(CExprTextUnitList &oList)
// {
// 	return FALSE;
// }
// 
// BOOL CExprTextUnitList::Delete(CExprTextUnitList &oList)
// {
// 	return FALSE;
// }
// 
// BOOL CExprTextUnitList::CanDelete(CExprTextUnit &pTextUnit)
// {
// 	return FALSE;
// }

BOOL CExprTextUnitList::DeleteExprTextUnit(CExprTextUnit *pTextUnit)
{
	POS pos = Find(pTextUnit);

	if (pos != NULL)
	{
		DeleteAt(pos);
		return TRUE;
	}

	return FALSE;
}


//////////////////////////////////////////////////////////////////////////

// CExprEdit

IMPLEMENT_DYNAMIC(CExprEdit, CEdit)

//{{AFX_MSG_MAP(CExprEdit)
BEGIN_MESSAGE_MAP(CExprEdit, CEdit)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_CONTROL_REFLECT(EN_SETFOCUS, &CExprEdit::OnSetFocusR)
	ON_MESSAGE(WM_CUT, &CExprEdit::OnCut)
	ON_MESSAGE(WM_CLEAR, &CExprEdit::OnClear)
	ON_MESSAGE(WM_PASTE, &CExprEdit::OnPaste)
	ON_MESSAGE(WM_SETTEXT, &CExprEdit::OnSetText)
	ON_MESSAGE(WM_GETTEXT, &CExprEdit::OnGetText)
	ON_MESSAGE(WM_GETTEXTLENGTH, &CExprEdit::OnGetTextLength)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(XID_EXPREDIT_OPTR_COPY, &CExprEdit::OnCopy)
	ON_COMMAND(XID_EXPREDIT_OPTR_PASTE, &CExprEdit::OnPaste)
END_MESSAGE_MAP()
//}}AFX_MSG_MAP

CExprEdit::CExprEdit()
{
	
}

CExprEdit::~CExprEdit()
{
}

///////////////////////////////////
// Replace standard CWnd operations

void CExprEdit::SetExprScript(const CString &strScriptText)
{
	m_oExprTextUnitList.DeleteAll();
	m_strExprScript = strScriptText;
	m_oExprTextUnitList.SetExprScript(strScriptText);
	SetWindowText(m_oExprTextUnitList.GetExprScriptText());
}

void CExprEdit::SetWindowText(LPCTSTR lpszString)
{
	CEdit::SetWindowText(lpszString);
}

int CExprEdit::GetWindowText(_Out_z_cap_post_count_(nMaxCount, return + 1) LPTSTR lpszStringBuf, _In_ int nMaxCount) const
{
	return 0;
}

void CExprEdit::GetWindowText(CString& strString) const
{
	if (g_bIsInProcessing)
	{
		strString = m_strExprScript;
	}
	else
	{
		m_oExprTextUnitList.GetExprScript(strString);
	}
}

void CExprEdit::InsertFunc(const CString &strFunc)
{
	int nBegin, nEnd;
	CEdit::GetSel(nBegin, nEnd);

	InsertText(strFunc);
	nBegin += strFunc.GetLength();
	CEdit::SetSel(nBegin, nBegin);

	InsertText(_T("("));
	InsertText(_T(")"));
}

void CExprEdit::InsertText(const CString &strText)
{
	int nBegin, nEnd;
	CEdit::GetSel(nBegin, nEnd);

	//如果有选中的部分，则不处理
	if (nBegin != nEnd)
	{
		CExprTextUnit *pExptrUnit = m_oExprTextUnitList.GetExprTextUnit(nBegin, nEnd);

		if (pExptrUnit != NULL)
		{
			pExptrUnit->m_strUnitScpt = strText;
			pExptrUnit->m_strUnitText = strText;
			m_oExprTextUnitList.InitStringUnit(pExptrUnit);
			DoUpdate(nBegin+strText.GetLength()+1);
		}

		return;
	}

	long nLen = strText.GetLength();

	if (nLen == 0)
	{
		return;
	}

	//只有一个字符，调用OnCharPrintchar
	if (nLen == 1)
	{
		TCHAR chChar = strText.GetAt(0);
		OnCharPrintchar(chChar, 0, 0);
		return;
	}

	CExprTextUnit *pCurr = m_oExprTextUnitList.GetExprTextUnit(nBegin, nBegin);
	
	if (pCurr == NULL)
	{//1,,pCurr==NULL
		CExprTextUnit *pPrev = m_oExprTextUnitList.FindPrevExprTextUnit(pCurr);

		//1-1,pCurr==NULL：Prev==NULL
		if (pPrev == NULL)
		{
			CExprTextUnit *pExptrUnit = new CExprTextUnit(strText);
			m_oExprTextUnitList.AddTail(pExptrUnit);
			m_oExprTextUnitList.InitStringUnit(pExptrUnit);
			DoUpdate(nBegin);
		}
		else
		{//1-1,pCurr==NULL：Prev!=NULL
			if (pPrev->IsOptr() || pPrev->IsFunc())
			{//1-1-1,pCurr==NULL：Prev!=NULL：pPrev为Optr或者Func
				CExprTextUnit *pExptrUnit = new CExprTextUnit(strText);
				m_oExprTextUnitList.AddTail(pExptrUnit);
				m_oExprTextUnitList.InitStringUnit(pExptrUnit);
				DoUpdate(nBegin);
			}
			else
			{//1-1-2,pCurr==NULL：Prev!=NULL：pPrev不为Optr或者Func
				
			}
		}
	}
	else
	{//1-2,pCurr!=NULL
		int nUnitBegin, nUnitEnd;
		m_oExprTextUnitList.GetExprTextUnitPos(pCurr, nUnitBegin, nUnitEnd);

		if (nBegin < nUnitBegin && nBegin <= nEnd)
		{//1-2,pCurr!=NULL：当前位置在中间，不处理
			return;
		}
		else
		{//1-2,pCurr!=NULL：当前位置不在中间
			CExprTextUnit *pPrev = m_oExprTextUnitList.FindPrevExprTextUnit(pCurr);

			if (pPrev == NULL)
			{//1-2-1,pCurr!=NULL：当前位置不在中间：pPrev == NULL头部
				if (pCurr->IsOptr() || pCurr->IsFunc())
				{//1-2-1,pCurr!=NULL：当前位置不在中间：头部：当前为Optr
					CExprTextUnit *pExptrUnit = new CExprTextUnit(strText);
					m_oExprTextUnitList.AddHead(pExptrUnit);
					m_oExprTextUnitList.InitStringUnit(pExptrUnit);
					DoUpdate(nBegin);
				}
				else
				{//

				}
			}
			else
			{//1-2-2,pCurr!=NULL：当前位置不在中间：pPrev!=NULL两个Unit中间
				if (pPrev->IsOptr() && pCurr->IsOptr())
				{
					CExprTextUnit *pExptrUnit = new CExprTextUnit(strText);
					POS pos = m_oExprTextUnitList.Find(pPrev);
					m_oExprTextUnitList.InsertAfter(pos, pExptrUnit);
					m_oExprTextUnitList.InitStringUnit(pExptrUnit);
					DoUpdate(nBegin);
				}
			}
		}
	}
}

///////////////////////////////////
// Handlers

int CExprEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;

	CWnd::SetWindowText(_T(""));
	return 0;
}

void CExprEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case VK_END:
		{
			CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
			// Calc last group bounds
			//int nGroupStart, nGroupEnd;
			//CString strText = m_oExprTextUnitList.GetExprScriptText();
			//int nLen = strText.GetLength();
			//CEdit::SetSel(nLen, nLen);
			return;
		}
	case VK_HOME:
		{
			CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
			//CEdit::SetSel(0, 0);
			return;
		}
	case VK_UP:
	case VK_LEFT:
		{
			CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
			return;
		}

	case VK_DOWN:
	case VK_RIGHT:
		{
			CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
			return;
		}

	case VK_BACK:
		{
			// Special processing
			OnCharBackspace(nChar, nRepCnt, nFlags);
			return;
		}
	case VK_DELETE:
		{
			if (::GetKeyState(VK_SHIFT)&0x80)
			{
				break;
			}
			// Special processing
			OnCharDelete(nChar, nRepCnt, nFlags);
			return;
		}

	case VK_INSERT:
		{
			if ((::GetKeyState(VK_CONTROL)&0x80) ||(::GetKeyState(VK_SHIFT)&0x80))
			{
				break;
			}
			
			break;
		}
	}

	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CExprEdit::OnLButtonUp(UINT nFlags, CPoint point)
{
	int nStart, nEnd;
	CEdit::GetSel(nStart, nEnd);

	CExprTextUnitList oExprTextUnitList;
	m_oExprTextUnitList.GetExprTextUnits(nStart, nEnd, oExprTextUnitList);
	BOOL bSetSel = FALSE;

	if (oExprTextUnitList.GetCount() == 1)
	{
		CExprTextUnit *pExprTextUnit = oExprTextUnitList.GetHead();

		if (pExprTextUnit->IsOptr())
		{
			nStart = nEnd;
			//CEdit::SetSel(nEnd, nEnd);
		}
		else
		{
			m_oExprTextUnitList.GetExprTextUnitPos(pExprTextUnit, nStart, nEnd);
			//CEdit::SetSel(nStart, nEnd);
		}
	}
	else
	{
		nStart = nEnd;
		//CEdit::SetSel(nEnd, nEnd);
	}

	oExprTextUnitList.RemoveAll();

	CEdit::OnLButtonUp(nFlags, point);
	CEdit::SetSel(nStart, nEnd);
}

void CExprEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	TCHAR chChar = (TCHAR) nChar;
	if (_istprint(chChar) && !(::GetKeyState(VK_CONTROL)&0x80))
	{
		OnCharPrintchar(nChar, nRepCnt, nFlags);
		return;
	}
	else if ((nChar == VK_DELETE || nChar == VK_BACK))
	{
		return;
	}

// 	int nBeginOld, nEndOld;
// 	CEdit::GetSel(nBeginOld, nEndOld);
// 
// 	CEdit::OnChar(nChar, nRepCnt, nFlags);
}

//////////////////////////////
// Char routines

BOOL CExprEdit::IsCharOptr(TCHAR chChar)
{
	static TCHAR g_ptcharOptr[MAX_PATH] = _T("+-*/(),\0\0\0\0\0\0\0\0"); 
	ASSERT(_istprint(chChar) != FALSE);
	TCHAR *pChar = g_ptcharOptr;

	while (*pChar != 0)
	{
		if (chChar == *pChar)
		{
			return TRUE;
		}

		pChar++;
	}

	return FALSE;
}

BOOL CExprEdit::IsCharDigit(TCHAR chChar)
{
	if ( '0' <= chChar && chChar <= '9')
	{
		return TRUE;
	}

	if (chChar == '.')
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CExprEdit::CheckChar(TCHAR chChar, int nPos) // returns TRUE if the symbol is valid
{
	if (IsCharOptr(chChar))
	{
		return TRUE;
	}

	if ( IsCharDigit(chChar))
	{
		return TRUE;
	}

// 	if ( 'A' <= chChar && chChar <= 'Z')
// 	{
// 		return TRUE;
// 	}
// 
// 	if ( 'a' <= chChar && chChar <= 'z')
// 	{
// 		return TRUE;
// 	}

	return FALSE;
}

void CExprEdit::OnCharPrintchar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	TCHAR chChar = (TCHAR) nChar;
	ASSERT(_istprint(chChar) != FALSE);

	int nStartPos, nEndPos;
	CEdit::GetSel(nStartPos, nEndPos);

	ASSERT(nStartPos>=0);
	ASSERT(nEndPos>=0);
	ASSERT(nEndPos>=nStartPos);

	//如果有选中的部分，不能插入
	if (nEndPos != nStartPos)
	{
		CExprTextUnit *pExptrUnit = m_oExprTextUnitList.GetExprTextUnit(nStartPos, nEndPos);

		if (pExptrUnit != NULL)
		{
			pExptrUnit->m_strUnitScpt = chChar;
			pExptrUnit->m_strUnitText = chChar;
			DoUpdate(nStartPos+1);
		}

		return;
	}

	//只能处理数字和运算符号的输入
	if (IsCharDigit(chChar) || IsCharOptr(chChar))
	{

	}
	else
	{
		return;
	}

// 	if (!m_oExprTextUnitList.CanInsertChar(nEndPos))
// 	{
// 		return;
// 	}

	//获取当前位置的TextUnit，当前位置是指光标位置之后的TextUnit
	CExprTextUnit *pExptrUnit = m_oExprTextUnitList.GetExprTextUnit(nEndPos, nEndPos);

	//////////////////////////////////////////////////////////////////////////
	//1,如果没有找到，表示为空或者光标位于末尾
	if (pExptrUnit == NULL)
	{
		CExprTextUnit *pTail = m_oExprTextUnitList.GetTail();

		//1-1,为空
		if (pTail == NULL)
		{
			pExptrUnit = new CExprTextUnit(chChar);
			m_oExprTextUnitList.AddTail(pExptrUnit);
			DoUpdate(nEndPos+1);
			return;
		}
		else
		{//1-2
			//1-2-1不为空
			if (IsCharDigit(chChar))
			{
				if (pTail->IsVariable())
				{//1-2-1-1当前输入的是数字，最后一个是变量，不能处理
					return;
				}

				if (pTail->IsOptr() || pTail->IsFunc())
				{//1-2-1-3函数或者运算符号，创建数字对象
					pExptrUnit = new CExprTextUnit(chChar);
					m_oExprTextUnitList.AddTail(pExptrUnit);
					DoUpdate(nEndPos+1);
					return;
				}

				if (pTail->IsNumber())
				{//1-2-1-2数字，则添加到字符串的末尾
					pTail->AppendChar(chChar);
					DoUpdate(nEndPos+1);
					return;
				}

				return;
			}
			else if (IsCharOptr(chChar))
			{//1-2-2
				pExptrUnit = new CExprTextUnit(chChar);
				m_oExprTextUnitList.AddTail(pExptrUnit);
				DoUpdate(nEndPos+1);
			}
		}

		//其他的各种情况，不处理
		return;
	}

	//////////////////////////////////////////////////////////////////////////
	//2,当前位置有对象
	int nUnitBegin, nUnitEnd;
	m_oExprTextUnitList.GetExprTextUnitPos(pExptrUnit, nUnitBegin, nUnitEnd);

	//2-1:当前位置有对象：光标位置位于当前对象的中间
	if (nUnitBegin < nEndPos && nEndPos <= nEndPos)
	{
		if (pExptrUnit->IsNumber() && IsCharDigit(chChar))
		{//2-1-1:当前位置有对象：光标位置位于当前对象的中间：当前位置为数字并且当前字符为数字
			nUnitBegin = nEndPos - nUnitBegin;
			pExptrUnit->InsertChar(chChar, nUnitBegin);
			DoUpdate(nEndPos+1);
		}

		return;
	}

	//2-2 :当前位置有对象：当前光标不位于当前对象的中间
	//2-2-1  当前位置有对象：当前光标不位于当前对象的中间：当前字符为Optr
	if (IsCharOptr(chChar))
	{
		CExprTextUnit *pPrev = m_oExprTextUnitList.FindPrevExprTextUnit(pExptrUnit);

		if (pPrev == NULL)
		{//2-2-1-1 当前位置有对象：当前光标不位于当前对象的中间：当前字符为Optr：之前没有对象，插入到头部
			pExptrUnit = new CExprTextUnit(chChar);
			m_oExprTextUnitList.AddHead(pExptrUnit);
			DoUpdate(nEndPos+1);
		}
		else
		{//2-2-1-2 当前位置有对象：当前光标不位于当前对象的中间：当前字符为Optr：之前有对象，插入到中间位置
			POS pos = m_oExprTextUnitList.Find(pPrev);
			ASSERT (pos != NULL);
			pExptrUnit = new CExprTextUnit(chChar);
			m_oExprTextUnitList.InsertAfter(pos, pExptrUnit);
			DoUpdate(nEndPos+1);
		}

		return;
	}

	//2-2-2 :当前位置有对象：当前光标不位于当前对象的中间：当前字符为数字
	if (IsCharDigit(chChar))
	{
		CExprTextUnit *pPrev = m_oExprTextUnitList.FindPrevExprTextUnit(pExptrUnit);

		if (pPrev == NULL)
		{//2-2-2-1：当前位置有对象：当前光标不位于当前对象的中间：当前字符为数字 ： 位于头部
			if (pExptrUnit->IsOptr())
			{//2-2-2-1-2：当前位置有对象：当前光标不位于当前对象的中间：当前字符为数字 ： 位于头部：当前位置为运算符号
				pExptrUnit = new CExprTextUnit(chChar);
				m_oExprTextUnitList.AddHead(pExptrUnit);
				DoUpdate(nEndPos+1);
			}
			else if (pExptrUnit->IsNumber())
			{//2-2-2-1-1：当前位置有对象：当前光标不位于当前对象的中间：当前字符为数字 ： 位于头部：当前位置为数字
				pExptrUnit->m_strUnitScpt = chChar + pExptrUnit->m_strUnitScpt;
				pExptrUnit->m_strUnitText = pExptrUnit->m_strUnitScpt;
				DoUpdate(nEndPos+1);
			}
			else
			{//2-2-2-1-2：当前位置有对象：当前光标不位于当前对象的中间：当前字符为数字 ： 位于头部：当前位置为其他情况，不处理

			}

			return;
		}
		else
		{//2-2-2-2：当前位置有对象：当前光标不位于当前对象的中间：当前字符为数字 ： 位于中间
			if (pPrev->IsOptr() || pPrev->IsFunc())
			{//2-2-2-2-1：当前位置有对象：当前光标不位于当前对象的中间：当前字符为数字 ： 位于中间：pPrev为运算符号或者函数
				if (pExptrUnit->IsNumber())
				{///2-2-2-2-1-1：当前位置有对象：当前光标不位于当前对象的中间：当前字符为数字 ： 位于中间：pPrev为运算符号或者函数：当前位置为数字
					pExptrUnit->m_strUnitScpt = chChar + pExptrUnit->m_strUnitScpt;
					pExptrUnit->m_strUnitText = pExptrUnit->m_strUnitScpt;
					DoUpdate(nEndPos+1);
				}
				else if (pExptrUnit->IsOptr() || pExptrUnit->IsFunc())
				{///2-2-2-2-1-1：当前位置有对象：当前光标不位于当前对象的中间：当前字符为数字 ： 位于中间：pPrev为运算符号或者函数：当前位置为函数、运算符
					POS pos = m_oExprTextUnitList.Find(pPrev);
					ASSERT (pos != NULL);
					pExptrUnit = new CExprTextUnit(chChar);
					m_oExprTextUnitList.InsertAfter(pos, pExptrUnit);
					DoUpdate(nEndPos+1);
				}
				else
				{///2-2-2-2-1-1：当前位置有对象：当前光标不位于当前对象的中间：当前字符为数字 ： 位于中间：pPrev为运算符号或者函数：其他情况不处理

				}
			}
			else
			{//2-2-2-2-1：当前位置有对象：当前光标不位于当前对象的中间：当前字符为数字 ： 位于中间：pPrev为其他情况不处理
				if (pPrev->IsNumber())
				{
					pPrev->m_strUnitScpt = pPrev->m_strUnitScpt + chChar;
					pPrev->m_strUnitText = pPrev->m_strUnitScpt;
					DoUpdate(nEndPos+1);
				}
			}
			return;
		}
	}
	
}

int CExprEdit::GetSelExprTextUnits(CExprTextUnitList &oList)
{
	oList.RemoveAll();

	int nStartPos, nEndPos;
	CEdit::GetSel(nStartPos, nEndPos);
	m_oExprTextUnitList.GetExprTextUnits(nStartPos, nEndPos, oList);

	long nCount = oList.GetCount();
	oList.RemoveAll();

	return nCount;
}

void CExprEdit::OnCharBackspace(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	g_bIsInProcessing = TRUE;
	//获取当前位置，获取前一位置的数据
	int nStartPos, nEndPos;
	CEdit::GetSel(nStartPos, nEndPos);
	ASSERT(nStartPos>=0);
	ASSERT(nEndPos>=0);
	ASSERT(nEndPos>=nStartPos);

	if (nStartPos == 0 && nEndPos == 0)
	{
		g_bIsInProcessing = FALSE;
		return;
	}

	CExprTextUnitList oList;
	m_oExprTextUnitList.GetExprTextUnits(nStartPos, nEndPos, oList);

	if (oList.GetCount() == 0)
	{
		CString strText = m_oExprTextUnitList.GetExprScriptText();
		if (nStartPos == nEndPos && nStartPos == strText.GetLength())
		{
			CExprTextUnit *p = m_oExprTextUnitList.GetTail();
			m_oExprTextUnitList.DeleteExprTextUnit(p);
			g_bIsInProcessing = FALSE;
			DoUpdate(nStartPos);
		}

		g_bIsInProcessing = FALSE;
		return;
	}

	if (nStartPos == nEndPos)
	{
		CExprTextUnit *p = oList.GetHead();
		CExprTextUnit *pPrev = m_oExprTextUnitList.FindPrevExprTextUnit(p);

		if (pPrev != NULL)
		{
			m_oExprTextUnitList.GetExprTextUnitPos(pPrev, nStartPos, nEndPos);
			m_oExprTextUnitList.DeleteExprTextUnit(pPrev);
			oList.RemoveAll();
			g_bIsInProcessing = FALSE;

			DoUpdate(nStartPos);
		}
	}
	else
	{
		POS pos = oList.GetHeadPosition();
		CExprTextUnit *p = NULL;

		while (pos != NULL)
		{
			p = oList.GetNext(pos);
			m_oExprTextUnitList.DeleteExprTextUnit(p);
		}

		oList.RemoveAll();
		g_bIsInProcessing = FALSE;

		DoUpdate(nStartPos);
	}

}

void CExprEdit::OnCharDelete(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	g_bIsInProcessing = TRUE;
	int nStartPos, nEndPos;
	CEdit::GetSel(nStartPos, nEndPos);
	ASSERT(nStartPos>=0);
	ASSERT(nEndPos>=0);
	ASSERT(nEndPos>=nStartPos);
	
	CExprTextUnitList oList;
	m_oExprTextUnitList.GetExprTextUnits(nStartPos, nEndPos, oList);

	if (oList.GetCount() == 0)
	{
		g_bIsInProcessing = FALSE;
		return;
	}

	POS pos = oList.GetHeadPosition();
	CExprTextUnit *p = oList.GetHead();
	m_oExprTextUnitList.GetExprTextUnitPos(p, nStartPos, nEndPos);

	while (pos != NULL)
	{
		p = oList.GetNext(pos);
		m_oExprTextUnitList.DeleteExprTextUnit(p);
	}

	oList.RemoveAll();
	g_bIsInProcessing = FALSE;

	DoUpdate(nStartPos);
}

void CExprEdit::GetGroupBounds(int &nBegin, int &nEnd, int nStartPos, BOOL bForward)
{
	nBegin = 0;
	nEnd = 1024;
}

BOOL CExprEdit::DoUpdate(int nPos)
{
	m_strExprScript = m_oExprTextUnitList.GetExprScriptText();
	SetWindowText(m_strExprScript);
	CEdit::SetSel(nPos, nPos);

	m_strExprScript = m_oExprTextUnitList.GetExprScript();

	if (m_oExprTextUnitList.m_pExprVariableFind != NULL)
	{
		m_oExprTextUnitList.m_pExprVariableFind->OnExprScriptChanged(m_strExprScript);
	}

	return TRUE;
}


LRESULT CExprEdit::OnCut(WPARAM, LPARAM)
{
	return 0;
}

LRESULT CExprEdit::OnClear(WPARAM, LPARAM)
{
	return 0;
}

LRESULT CExprEdit::OnPaste(WPARAM, LPARAM)
{
	return FALSE;
}

///////////////////////////////////
// Replace standard CWnd operations

LRESULT CExprEdit::OnSetText(WPARAM, LPARAM lParam)
{
	return Default();
// 	static BOOL bSetTextProcessing = FALSE;
// 
// 	if (bSetTextProcessing || m_bPasteProcessing)
// 	{
// 		return Default();
// 	}
// 
// 	bSetTextProcessing = TRUE;
// 	m_strExprText = (LPCTSTR)lParam;
// 	bSetTextProcessing = FALSE;
// 
// 	return FALSE;
}

LRESULT CExprEdit::OnGetText(WPARAM wParam, LPARAM lParam)
{
	int nMaxCount = (int)wParam;
	if (nMaxCount == 0)
	{
		return 0;       // nothing copied
	}

	LPTSTR lpszDestBuf = (LPTSTR)lParam;

	if (lpszDestBuf == NULL)
	{
		return 0;       // nothing copied
	}

	// Copy text
	int nCount = min(nMaxCount, m_strExprScript.GetLength());
	LPCTSTR lpcszTmp = m_strExprScript;
	CopyMemory(lpszDestBuf, lpcszTmp, nCount * sizeof(TCHAR));

	// Add terminating null character if possible
	if (nMaxCount > nCount)
	{
		lpszDestBuf[nCount] = _T('\0');
	}

	return(nCount * sizeof(TCHAR));
}

LRESULT CExprEdit::OnGetTextLength(WPARAM, LPARAM)
{
	return (LRESULT) m_strExprScript.GetLength();
}

void CExprEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CEdit::OnLButtonDown(nFlags, point);
}

void CExprEdit::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CEdit::OnLButtonDblClk(nFlags, point);
}

void CExprEdit::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu menu;		
	menu.CreatePopupMenu();

	// 添加菜单项
#ifdef NOT_USE_XLANGUAGE
	menu.AppendMenu(MF_STRING,XID_EXPREDIT_OPTR_COPY,_T("拷贝"));
	menu.AppendMenu(MF_STRING,XID_EXPREDIT_OPTR_PASTE,_T("粘贴"));
#else
	menu.AppendMenu(MF_STRING,XID_EXPREDIT_OPTR_COPY,/*_T("拷贝")*/g_sLangTxt_Copy);
	menu.AppendMenu(MF_STRING,XID_EXPREDIT_OPTR_PASTE,/*_T("粘贴")*/g_sLangTxt_Paste);
#endif

	//确定弹出式菜单的位置
	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,pWnd);			

	//资源回收
	HMENU hmenu=menu.Detach();	
	menu.DestroyMenu();	
}

void CExprEdit::OnSetFocusR()
{
	//CEdit::SetSel(0, -1);
}


void CExprEdit::OnCopy()
{
	g_strExprEditCopyString = m_oExprTextUnitList.GetExprScript();
}

void CExprEdit::OnPaste()
{
	m_oExprTextUnitList.SetExprScript(g_strExprEditCopyString);
	DoUpdate(0);
}


