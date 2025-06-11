//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttIecGsBinaryDrawView.cpp  CSttIecGsBinaryDrawView


#include "stdafx.h"
#include "SttIecGsBinaryDrawView.h"
#include "../../../../Module/API/GloblaDrawFunctions.h"
#include "SttIecGsBinaryDraw.h"

//////////////////////////////////////////////////////////////////////////
//CSttIecGsBinarysDraw
CSttIecGsBinaryDrawView::CSttIecGsBinaryDrawView()
{
	//初始化属性
	m_pDatas = NULL;

	//初始化成员变量
}

CSttIecGsBinaryDrawView::~CSttIecGsBinaryDrawView()
{
}


DWORD CSttIecGsBinaryDrawView::XCreateElement(long nCount, EPCAPPARSEDATAS *pDatas, CWnd *pParentWnd)
{
	DeleteAll();
	m_bIsBinaryOut = FALSE;
	m_bUseBinaryOutOptr = FALSE;
	CSttIecGsBinarysDraw *pNew = new CSttIecGsBinarysDraw();
	m_pBinarysDraw = pNew;
	pNew->CreateBinarysDraw(nCount, pDatas, pParentWnd);

	AddNewChild(m_pBinarysDraw);

	//CalLayout
	CSize szView(0,0);
	szView = CalLayout(szView);

	//调整位置
    CPoint oPoint(0,0);
    Layout(oPoint);

	return XCREATE_SUCC;
}

void CSttIecGsBinaryDrawView::OnSize(long cx, long cy)
{
	m_nWidth = cx;
	m_nHeight = cy;
    CPoint oPoint(0,0);
    Layout(oPoint);
}

