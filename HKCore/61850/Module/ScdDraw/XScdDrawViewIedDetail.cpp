//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawViewIed2Detail.cpp  CXScdDrawViewIedDetail


#include "stdafx.h"
#include "XScdDrawViewIedDetail.h"
#include "ThumbLayoutTool.h"

CXScdDrawViewIedDetail::CXScdDrawViewIedDetail()
{
// 	m_pIedList_MergIntel = NULL;
// 	m_pIedList_ProtMeas = NULL;
}

CXScdDrawViewIedDetail::~CXScdDrawViewIedDetail()
{
}

void CXScdDrawViewIedDetail::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CXScdDrawViewBase::Draw(pDC,fZoomRatio,ptOffset, dwDrawFlag);
}

void CXScdDrawViewIedDetail::Pick(const CPoint &point, CExBaseList &oList)
{
	CXScdDrawViewBase::Pick(point, oList);
}

CXDrawElement* CXScdDrawViewIedDetail::XCreateChildElement(UINT nClassID)
{
// 	if (SCLIECCLASSID_IED == nClassID)
// 	{
// 		return new CXScdDrawIedDetail();
// 	}

	return NULL;
}

DWORD CXScdDrawViewIedDetail::XCreateElement(CExBaseObject *pData, CWnd *pParentWnd)
{
	UINT nClassID = pData->GetClassID();
	
	if (XSCDDRAW_LINE_CTRL == nClassID)
	{
		InitXScdDrawViewIedDetail((CXScdDrawLine_Ctrls*)pData, pParentWnd);
	}

	////CalLayout
	CSize szView(0,0);
	szView = CalLayout(szView);

	////调整位置
	Layout(CPoint(0, 0));

	return XCREATE_SUCC;
}


CSize CXScdDrawViewIedDetail::CalLayout(CSize &szDraw)
{
	CSize szEntire(0,0);//计算所有的IED的Size
	CSize szIed(0,0);
	POS pos=GetHeadPosition(); 
	CXScdDrawIedSclDetail *pIedDetail=NULL;
	CSclIed *pTempIed=NULL;

	while (pos!=NULL)
	{
		pIedDetail=(CXScdDrawIedSclDetail*)GetNext(pos);
		szIed=pIedDetail->CalLayout(szIed);
	}

	szEntire.cy=max(szEntire.cy,szIed.cy);
	szEntire.cx+=szIed.cx;

	return szDraw;
}


void CXScdDrawViewIedDetail::LayoutLines()
{
	POS pos = m_oScdDrawLines.GetHeadPosition(); 
	CXScdDrawLineBase *pLine = NULL;

	while (pos!=NULL)
	{
		pLine = (CXScdDrawLineBase *)m_oScdDrawLines.GetNext(pos);
		pLine->InitLinePos();
	}
}


CSize CXScdDrawViewIedDetail::Layout(CPoint &ptTopLeft)
{
	ptTopLeft.x=XSCDDRAW_ELEMENT_MARGIN;
	ptTopLeft.y=XSCDDRAW_ELEMENT_MARGIN;

	CXScdDrawIedSclDetail *pLeft = (CXScdDrawIedSclDetail*)GetHead();
	CXScdDrawIedSclDetail *pRight = (CXScdDrawIedSclDetail*)GetTail();

	ptTopLeft.x = XSCDDRAW_VIEW_GAP;
	ptTopLeft.y = XSCDDRAW_VIEW_GAP;
	CSize szLeft = pLeft->Layout(ptTopLeft);

	ptTopLeft.x += XSCDDRAW_VIEW_IED_GAP_HOR_EX + szLeft.cx;

	CSize szRight = pRight->Layout(ptTopLeft);

	m_nWidth = XSCDDRAW_VIEW_GAP * 3 + szLeft.cx + XSCDDRAW_VIEW_IED_GAP_HOR_EX + szRight.cx;
	m_nHeight = max(szLeft.cy, szRight.cy);
	m_nHeight += XSCDDRAW_VIEW_GAP * 2;

	LayoutLines();

	return CSize(m_nWidth, m_nHeight);
}

void CXScdDrawViewIedDetail::InitXScdDrawViewIedDetail(CXScdDrawLine_Ctrls *pLineCtrls, CWnd *pParentWnd)
{
	CXScdDrawIedSclDetail *pDrawIedBegin = new CXScdDrawIedSclDetail();
	CXScdDrawIedSclDetail *pDrawIedEnd = new CXScdDrawIedSclDetail();

	CSclIed *pIedBegin = (CSclIed*)pLineCtrls->m_pBeginObj->GetAncestor(SCLIECCLASSID_IED);
	CSclIed *pIedEnd   = (CSclIed*)pLineCtrls->m_pEndObj->GetAncestor(SCLIECCLASSID_IED);

	AddNewChild(pDrawIedBegin);
	AddNewChild(pDrawIedEnd);

	pDrawIedBegin->XCreateElement(pLineCtrls->m_pBeginObj, pParentWnd);
	pDrawIedEnd->XCreateElement(pLineCtrls->m_pEndObj, pParentWnd);

	pDrawIedBegin->CreateCtrlLines();
	pDrawIedEnd->CreateCtrlLines();
	pDrawIedBegin->GetAllLines(m_oScdDrawLines);
	pDrawIedEnd->GetAllLines(m_oScdDrawLines);

	//调整连接线
	InitLinesBeginElement();
	m_oScdDrawLines.RemoveErrorLines();
	pDrawIedBegin->RemoveErrorLines();
	pDrawIedEnd->RemoveErrorLines();

	pDrawIedBegin->OnOnlyShowUsedChsChanged(&m_oScdDrawLines);
	pDrawIedEnd->OnOnlyShowUsedChsChanged(&m_oScdDrawLines);
}

void CXScdDrawViewIedDetail::OnOnlyShowUsedChsChanged()
{

}

void CXScdDrawViewIedDetail::InitLinesBeginElement()
{
	POS pos = m_oScdDrawLines.GetHeadPosition(); 
	CXScdDrawLineBase *pLine = NULL;
	CExBaseObject *pCtrl = NULL;

	while (pos!=NULL)
	{
		pLine = (CXScdDrawLineBase *)m_oScdDrawLines.GetNext(pos);
		pCtrl = (CExBaseObject*)pLine->m_pBeginObj->GetParent();
		pLine->m_pBeginElement = QueryByXDrawDataRef(pCtrl);
	}
}

