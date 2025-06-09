// XLanguageTextWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "XLangWndAdjust.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
// CXLangWndAdjBase
void CXLangWndAdjBase::InitCXLangWndAdj(CXLanguageWndInterface *pWnd)
{
	m_pXLangWndRef = NULL;
	m_pXLangWnd = pWnd;
	m_pXLangWnd->CalXLangWndAdj(m_rcOrigin, m_nWidthCal);
}

void CXLangWndAdjBase::InitCXLangWndAdj(CWnd *pWnd)
{
	m_pXLangWnd = NULL;
	m_pXLangWndRef = pWnd;
	xlang_CalXLangWndAdj(m_pXLangWndRef, m_rcOrigin, m_nWidthCal);
}

CXLangWndAdjBase::CXLangWndAdjBase()
{
	m_pXLangWndRef = NULL;
	m_pXLangWnd = NULL;
	m_nWidthCal = 0;
	m_nWidthOrigin = 0;
	ZeroMemory(&m_rcOrigin, sizeof(m_rcOrigin));
}

CXLangWndAdjBase::~CXLangWndAdjBase()
{
}

//调整单个控件对象
long CXLangWndAdjBase::Adjust(CWnd *pParent, long nOffset, CSize &szMax)
{
	CRect rc = m_rcOrigin;
	pParent->ScreenToClient(&rc);
	rc.OffsetRect(nOffset, 0);
	
	if (rc.Width() <= m_nWidthCal)
	{
		rc.right = rc.left + m_nWidthCal;
	}

	if (m_pXLangWnd != NULL)
	{
		m_pXLangWnd->MoveWindow(rc);
	}
	else if (m_pXLangWndRef != NULL)
	{
		m_pXLangWndRef->MoveWindow(rc);
		m_pXLangWndRef->Invalidate(FALSE);
	}
	else
	{
		ASSERT (FALSE);
	}

	szMax.cx = max(szMax.cx, rc.right);
	szMax.cy = max(szMax.cx, rc.bottom);

	return 0;
}

//计算调整窗口
 long CXLangWndAdjBase::AdjustCal()
 {
	 m_nWidthOrigin = m_rcOrigin.Width();
	return 0;
 }

//////////////////////////////////////////////////////////////////////////
//CXLangWndAdjBaseList
CXLangWndAdjBaseList::CXLangWndAdjBaseList()
{
	m_nWidthOrigin = 0;
	m_rcOrigin.left = 0;
	m_rcOrigin.right = 0;
	m_rcOrigin.top = 0;
	m_rcOrigin.bottom = 0;
}

CXLangWndAdjBaseList::~CXLangWndAdjBaseList()
{

}


CXLangWndAdjBase* CXLangWndAdjBaseList::AddNewChild(CXLangWndAdjBase *pNew)
{
	AddTail(pNew);
	pNew->SetParent(this);
	return pNew;
}

//遍历集合中每个CXLangWndAdjBase对象，调整位置
//集合中的对象可能是CXLangWndAdjBase、Col、Frame等
//返回调整的偏移量
long CXLangWndAdjBaseList::Adjust(CWnd *pParent, long nOffset, CSize &szMax)
{
	POS pos = GetHeadPosition();
	CXLangWndAdjBase *pWnd = NULL;

	while (pos != NULL)
	{
		pWnd = (CXLangWndAdjBase*)GetNext(pos);
		pWnd->Adjust(pParent, nOffset, szMax);
	}

	if (m_nWidthCal > m_nWidthOrigin)
	{
		nOffset += m_nWidthCal - m_nWidthOrigin;
	}

	return nOffset;
}

long CXLangWndAdjBaseList::Width()
{
	return m_nWidthOrigin;
}

long CXLangWndAdjBaseList::CalWidth()
{
	return m_nWidthCal;
}

//计算集合对象下每个CXLangWndAdjBase的调整属性，得到集合对象的调整属性
//调整属性：原始宽度m_nWidthOrigin、计算宽度m_nWidthCal
long CXLangWndAdjBaseList::AdjustCal()
{
	POS pos = GetHeadPosition();
	CXLangWndAdjBase *pWnd = NULL;

	while (pos != NULL)
	{
		pWnd = (CXLangWndAdjBase*)GetNext(pos);
		pWnd->AdjustCal();
		m_nWidthOrigin = max(m_nWidthOrigin, pWnd->Width());
		m_nWidthCal = max(m_nWidthCal, pWnd->CalWidth());
		//m_rcOrigin.left = min(m_rcOrigin.left, pWnd->m_rcOrigin.left);
	}

	//m_rcOrigin.right = m_rcOrigin.left + m_nWidthCal;

	return GetOffset();
}

long CXLangWndAdjBaseList::GetOffset()
{
	if (m_nWidthCal > m_nWidthOrigin)
	{
		return m_nWidthCal - m_nWidthOrigin;
	}
	else
	{
		return 0;
	}
}

//////////////////////////////////////////////////////////////////////////
//CXLangWndAdjCol
CXLangWndAdjCol::CXLangWndAdjCol()
{
	m_nWidthOrigin = 0;
	m_nWidthCal = 0;
}

CXLangWndAdjCol::~CXLangWndAdjCol()
{

}

CXLangWndAdjBase* CXLangWndAdjCol::RegisterWnd(CXLanguageWndInterface *pXLandWnd)
{
	CXLangWndAdjBase *pNew = new CXLangWndAdjBase();
	pNew->InitCXLangWndAdj(pXLandWnd);
	AddNewChild(pNew);

	return pNew;
}

CXLangWndAdjBase* CXLangWndAdjCol::RegisterWnd(CWnd *pXLandWnd)
{
	CXLangWndAdjBase *pNew = new CXLangWndAdjBase();
	pNew->InitCXLangWndAdj(pXLandWnd);
	AddNewChild(pNew);

	return pNew;
}

CXLangWndAdjFrame* CXLangWndAdjCol::RegisterFrame(CXLanguageWndInterface *pXLandWnd)
{
	CXLangWndAdjFrame *pNew = new CXLangWndAdjFrame();
	pNew->InitCXLangWndAdj(pXLandWnd);
	AddNewChild(pNew);

	return pNew;
}

CXLangWndAdjFrame* CXLangWndAdjCol::RegisterFrame(CWnd *pXLandWnd)
{
	CXLangWndAdjFrame *pNew = new CXLangWndAdjFrame();
	pNew->InitCXLangWndAdj(pXLandWnd);
	AddNewChild(pNew);

	return pNew;
}

long CXLangWndAdjCol::Adjust(CWnd *pParent, long nOffset, CSize &szMax)
{
	return CXLangWndAdjBaseList::Adjust(pParent, nOffset, szMax);
// 	POS pos = GetHeadPosition();
// 	CXLangWndAdjBase *pWnd = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pWnd = (CXLangWndAdjBase*)GetNext(pos);
// 		pWnd->Adjust(pParent, nOffset, szMax);
// 	}
// 
// 	if (m_nWidthCal > m_nWidthOrigin)
// 	{
// 		nOffset += m_nWidthCal - m_nWidthOrigin;
// 	}
// 
// 	return nOffset;
}


//////////////////////////////////////////////////////////////////////////
//CXLangWndAdjCols
CXLangWndAdjCols::CXLangWndAdjCols()
{
	m_pCurrCol = NULL;
}

CXLangWndAdjCols::~CXLangWndAdjCols()
{

}

CXLangWndAdjCol* CXLangWndAdjCols::RegisterCol()
{
	CXLangWndAdjCol *pNew = new CXLangWndAdjCol();
	AddNewChild(pNew);

	m_pCurrCol = pNew;

	return pNew;
}

CXLangWndAdjBase* CXLangWndAdjCols::RegisterXWnd(CXLanguageWndInterface *pXLandWnd)
{
	ASSERT (m_pCurrCol != NULL);

	if (m_pCurrCol != NULL)
	{
		return m_pCurrCol->RegisterWnd(pXLandWnd);
	}
	else
	{
		return NULL;
	}
}

CXLangWndAdjBase* CXLangWndAdjCols::RegisterWnd(CXLanguageWndInterface *pXLandWnd)
{
	ASSERT (m_pCurrCol != NULL);

	if (m_pCurrCol != NULL)
	{
		return m_pCurrCol->RegisterWnd(pXLandWnd);
	}
	else
	{
		return NULL;
	}
}

CXLangWndAdjBase* CXLangWndAdjCols::RegisterWnd(CWnd *pXLandWnd)
{
	ASSERT (m_pCurrCol != NULL);

	if (m_pCurrCol != NULL)
	{
		return m_pCurrCol->RegisterWnd(pXLandWnd);
	}
	else
	{
		return NULL;
	}
}

CXLangWndAdjFrame* CXLangWndAdjCols::RegisterFrame(CXLanguageWndInterface *pXLandWnd)
{
	ASSERT (m_pCurrCol != NULL);

	if (m_pCurrCol != NULL)
	{
		return m_pCurrCol->RegisterFrame(pXLandWnd);
	}
	else
	{
		return NULL;
	}
}

CXLangWndAdjFrame* CXLangWndAdjCols::RegisterFrame(CWnd *pXLandWnd)
{
	ASSERT (m_pCurrCol != NULL);

	if (m_pCurrCol != NULL)
	{
		return m_pCurrCol->RegisterFrame(pXLandWnd);
	}
	else
	{
		return NULL;
	}
}

//遍历Col下的每个CXLangWndAdjBaseList对象，调整位置
long CXLangWndAdjCols::Adjust(CWnd *pParent, CSize &szMax)
{
	POS pos = GetHeadPosition();
	CXLangWndAdjBaseList *pCol = NULL;
	long nOffset = 0;

	//计算调整的偏移量
	while (pos != NULL)
	{
		pCol = (CXLangWndAdjBaseList*)GetNext(pos);
		nOffset += pCol->AdjustCal();
	}

	//从最后一个开始调整，目的是为了调整后界面能够更新
	pos = GetTailPosition();

	while (pos != NULL)
	{
		pCol = (CXLangWndAdjBaseList*)GetPrev(pos);
		nOffset -= pCol->GetOffset();
		pCol->Adjust(pParent, nOffset, szMax);
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//CXLangWndAdjFrame
CXLangWndAdjFrame::CXLangWndAdjFrame()
{

}

CXLangWndAdjFrame::~CXLangWndAdjFrame()
{

}

//Frame对象的调整，Frame对象的子对象为Col对象
long CXLangWndAdjFrame::AdjustCal()
{
	//计算Frame下Col的大小
	POS pos = GetHeadPosition();
	CXLangWndAdjBase *pWnd = NULL;
	long nOffset = 0;

	while (pos != NULL)
	{
		pWnd = (CXLangWndAdjBase*)GetNext(pos);
		nOffset += pWnd->AdjustCal();
	}

	//此行代码可以为m_nWidthOrigin = m_rcOrigin.Width();
	m_nWidthOrigin = m_rcOrigin.Width();
	m_nWidthCal = max(m_nWidthCal, m_nWidthOrigin + nOffset);

	return GetOffset();
}

long CXLangWndAdjFrame::Adjust(CWnd *pParent, long nOffset, CSize &szMax)
{
	//先调整框架窗口
	CXLangWndAdjBase::Adjust(pParent, nOffset, szMax);

	CXLangWndAdjBaseList *pCol = NULL;
	POS pos = GetHeadPosition();
	while (pos != NULL)
	{
		pCol = (CXLangWndAdjBaseList*)GetNext(pos);
		nOffset += pCol->GetOffset();
	}

	//调整各列
	pos = GetTailPosition();

	while (pos != NULL)
	{
		pCol = (CXLangWndAdjBaseList*)GetPrev(pos);
		nOffset -= pCol->GetOffset();
		pCol->Adjust(pParent, nOffset, szMax);
	}

	return 0;
}


CXLangWndAdjBase* CXLangWndAdjFrame::RegisterXCol(CXLanguageWndInterface *pXLandWnd)
{
	RegisterCol();
	return m_pCurrCol->RegisterWnd(pXLandWnd);
}

CXLangWndAdjBase* CXLangWndAdjFrame::RegisterColWnd(CWnd *pXLandWnd)
{
	RegisterCol();
	return m_pCurrCol->RegisterWnd(pXLandWnd);
}


//////////////////////////////////////////////////////////////////////////
//CXLangWndAdjCols
CXLangWndAdjMngr::CXLangWndAdjMngr()
{
	//m_pCurrCol = NULL;
	m_pCurrCols = NULL;
}

CXLangWndAdjMngr::~CXLangWndAdjMngr()
{

}

void CXLangWndAdjMngr::FreeAdjMngr()
{
	DeleteAll();
	m_pCurrCols = NULL;
	//m_pCurrCol = NULL;
}

CXLangWndAdjCols* CXLangWndAdjMngr::RegisterCols()
{
	m_pCurrCols = new CXLangWndAdjCols();
	AddNewChild(m_pCurrCols);

	return m_pCurrCols;
}

// CXLangWndAdjBase* CXLangWndAdjMngr::RegisterXCols(CXLanguageWndInterface *pXLandWnd)
// {
// 	CXLangWndAdjCols *pCols = RegisterCols();
// 	pCols->InitCXLangWndAdj(pXLandWnd);
// 
// 	return pCols;
// }
// 
// CXLangWndAdjBase* CXLangWndAdjMngr::RegisterCols(CWnd *pXLandWnd)
// {
// 	CXLangWndAdjCols *pCols = RegisterCols();
// 	pCols->InitCXLangWndAdj(pXLandWnd);
// 
// 	return pCols;
// }

CXLangWndAdjCol* CXLangWndAdjMngr::RegisterCol()
{
	ASSERT (m_pCurrCols != NULL);

	return m_pCurrCols->RegisterCol();
}

CXLangWndAdjBase* CXLangWndAdjMngr::RegisterXCol(CXLanguageWndInterface *pXLandWnd)
{
	m_pCurrCols->RegisterCol();
	return m_pCurrCols->RegisterWnd(pXLandWnd);
}

CXLangWndAdjBase* CXLangWndAdjMngr::RegisterCol(CWnd *pXLandWnd)
{
	m_pCurrCols->RegisterCol();
	return m_pCurrCols->RegisterWnd(pXLandWnd);
}

CXLangWndAdjBase* CXLangWndAdjMngr::RegisterXWnd(CXLanguageWndInterface *pXLandWnd)
{
	ASSERT (m_pCurrCols != NULL);

	return m_pCurrCols->RegisterWnd(pXLandWnd);
}

CXLangWndAdjBase* CXLangWndAdjMngr::RegisterWnd(CWnd *pXLandWnd)
{
	ASSERT (m_pCurrCols != NULL);

	return m_pCurrCols->RegisterWnd(pXLandWnd);
}

CXLangWndAdjFrame* CXLangWndAdjMngr::RegisterXFrame(CXLanguageWndInterface *pXLandWnd)
{
	ASSERT (m_pCurrCols != NULL);

	return m_pCurrCols->RegisterFrame(pXLandWnd);
}

CXLangWndAdjFrame* CXLangWndAdjMngr::RegisterFrame(CWnd *pXLandWnd)
{
	ASSERT (m_pCurrCols != NULL);

	return m_pCurrCols->RegisterFrame(pXLandWnd);
}

void CXLangWndAdjMngr::Adjust(CWnd *pParent, BOOL bDialog)
{
	POS pos = GetHeadPosition();
	CXLangWndAdjCols *pCols = NULL;
	CSize szMax(0, 0);

	while (pos != NULL)
	{
		pCols = (CXLangWndAdjCols *)GetNext(pos);
		pCols->Adjust(pParent, szMax);
	}

	//pParent->Invalidate(FALSE);

	if (bDialog)
	{
		CRect rcClient;
		pParent->GetClientRect(rcClient);

		if (rcClient.Width() < szMax.cx)
		{
			CRect rcDlg;
			pParent->GetWindowRect(rcDlg);

			rcDlg.right += szMax.cx - rcClient.Width();
			rcDlg.right += 5;
			pParent->MoveWindow(rcDlg);
		}

	}
}

