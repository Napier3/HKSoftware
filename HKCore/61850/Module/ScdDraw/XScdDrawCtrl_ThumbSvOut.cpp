//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XScdDrawCtrl_ThumbSvOut.cpp  CXScdDrawCtrl_ThumbSvOut


#include "stdafx.h"
#include "XScdDrawCtrl_ThumbSvOut.h"

CXScdDrawCtrl_ThumbSvOut::CXScdDrawCtrl_ThumbSvOut()
{
	//��ʼ������

	//��ʼ����Ա����
	m_strName = _T("SVOUT");
}

CXScdDrawCtrl_ThumbSvOut::~CXScdDrawCtrl_ThumbSvOut()
{
	RemoveAll();
}

void CXScdDrawCtrl_ThumbSvOut::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CXScdDrawCtrl_ThumbBase::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
}



void CXScdDrawCtrl_ThumbSvOut::CreateCtrlBusLines()
{
	ASSERT (m_pXDrawDataRef != NULL);

	POS pos = GetHeadPosition();

	if (pos == NULL)
	{
		return;
	}

	CXScdDrawLine_Bus *pLineBus = GetSvBus();
	m_pLineCtrlBus = new CXScdDrawLine_ToBus();
	m_pLineCtrlBus->m_pBeginObj = m_pXDrawDataRef;
	m_pLineCtrlBus->m_pEndObj   = NULL;

	m_pLineCtrlBus->m_pBeginElement = this;
	m_pLineCtrlBus->m_pEndElement = pLineBus;
	pLineBus->AddLine(m_pLineCtrlBus);

	CXScdDrawCtrl_ThumbBase::CreateCtrlBusLines();
}

