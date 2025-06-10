// IecCfgViewMainBase.cpp : 实现文件
//

#include "stdafx.h"
#include "Iec61850Config.h"
#include "IecCfgViewMainBase.h"


// CIecCfgViewMainBase

IMPLEMENT_DYNCREATE(CIecCfgViewMainBase, CView)

CIecCfgViewMainBase::CIecCfgViewMainBase()
{
	m_bAdjust = FALSE;
}

CIecCfgViewMainBase::~CIecCfgViewMainBase()
{
}

BEGIN_MESSAGE_MAP(CIecCfgViewMainBase, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CIecCfgViewMainBase 绘图

void CIecCfgViewMainBase::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}


// CIecCfgViewMainBase 诊断

#ifdef _DEBUG
void CIecCfgViewMainBase::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CIecCfgViewMainBase::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CIecCfgViewMainBase 消息处理程序

int CIecCfgViewMainBase::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect(&rect);

	//获得窗口的创建信息指针
	CCreateContext *pContext = (CCreateContext*) lpCreateStruct->lpCreateParams;

	//产生二次静态切分
	m_wndSplitter.CreateStatic(this, 2, 1);

	CreateViews(rect, pContext);

	return 0;
}

void CIecCfgViewMainBase::CreateViews(const CRect &rect, CCreateContext *pContext)
{

}


void CIecCfgViewMainBase::SwitchView()
{
	CRect rect;
	GetClientRect(&rect);
	int cx = rect.Width();
	int cy = rect.Height();
	m_wndSplitter.MoveWindow(-2,-2,cx,cy+3);

	if (!m_bAdjust)
	{
		m_wndSplitter.SetRowInfo(0, cy / 4, 0);
		m_wndSplitter.SetRowInfo(1, cy * 3 / 4, 0);
	}
	else
	{
		int cyCur,cyCur2, cyMin;

		m_wndSplitter.GetRowInfo(0, cyCur, cyMin);

		if (cyCur < 100)
		{
			cyCur = cy / 2;
		}

		cyCur2 = cy - cyCur;

		if (cyCur2 < 0)
		{
			cyCur2 = cy / 2;
			cyCur = cy / 2;
		}

		m_wndSplitter.SetRowInfo(0, cyCur, 0);
		m_wndSplitter.SetRowInfo(1, cyCur2, 0);
	}

	m_wndSplitter.RecalcLayout();
	m_bAdjust = TRUE;
}

void CIecCfgViewMainBase::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if (!::IsWindow(m_wndSplitter.m_hWnd))
	{
		return;
	}

	SwitchView();
}

void CIecCfgViewMainBase::PostNcDestroy()
{

	CView::PostNcDestroy();
}

void CIecCfgViewMainBase::OnDestroy()
{
	
	CView::OnDestroy();
}
