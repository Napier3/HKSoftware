//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttIecGsBinaryDrawView.cpp  CSttIecGsBinaryDrawView


#include "stdafx.h"
#include "SttIecGsBinaryDrawView.h"
#include "../../../../Module/API/GloblaDrawFunctions.h"
#include "SttIecGsBinaryDraw.h"

//////////////////////////////////////////////////////////////////////////
//CSttIecGsBinarysDraw
CSttIecGsBinaryDrawView::CSttIecGsBinaryDrawView()
{
	//��ʼ������
	m_pDatas = NULL;

	//��ʼ����Ա����
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

	//����λ��
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

