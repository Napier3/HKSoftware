// D:\WorkLIJQ\Source\Module\Expression\ExprEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "ExprParse.h"


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

BOOL Expr_IsCharOptr(char chChar)
{
	static char  g_ptcharOptr[MAX_PATH] = _T("+-*/()<>&|=,\0\0\0\0\0\0\0\0"); 
	char *pChar = g_ptcharOptr;

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
// BOOL CExprEdit::g_bIsInProcessing = FALSE;
// CString CExprEdit::g_strExprEditCopyString = _T("");

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

BOOL CExprTextUnit::InsertChar(char chChar, int nPos)
{
	if (!IsNumber())
	{
		return FALSE;
	}

	m_strUnitScpt.Insert(nPos, chChar);
	m_strUnitText = m_strUnitScpt;

	return TRUE;
}

BOOL CExprTextUnit::AppendChar(char chChar)
{
#ifdef _PSX_IDE_QT_
	m_strUnitScpt.push_back(chChar);
#else
	m_strUnitScpt += chChar;
#endif
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

void CExprTextUnit::SetTChar(char chChar)
{
	m_strUnitScpt = CString(&chChar);
	m_strUnitText = m_strUnitScpt;
}

void CExprTextUnit::SetString(const CString &strText)
{
	m_strUnitScpt = strText;
	m_strUnitScpt.Trim();
	m_strUnitText = m_strUnitScpt;
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

CExprTextUnit* CExprTextUnitList::NewTextUnit(char chChar)
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
			CExBaseObject *pFind = (CExBaseObject*)m_pExprVariableFind->FindVariableByID(pNew->m_strUnitScpt);

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