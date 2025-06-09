//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawCtrl_ThumbGsOut.cpp  CXScdDrawCtrl_ThumbGsOut


#include "stdafx.h"
#include "XScdDrawCtrl_ThumbGsOut.h"

CXScdDrawCtrl_ThumbGsOut::CXScdDrawCtrl_ThumbGsOut()
{
	//初始化属性

	//初始化成员变量
	m_strName = _T("GOUT");
}

CXScdDrawCtrl_ThumbGsOut::~CXScdDrawCtrl_ThumbGsOut()
{
	RemoveAll();
}

void CXScdDrawCtrl_ThumbGsOut::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CXScdDrawCtrl_ThumbBase::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
}


void CXScdDrawCtrl_ThumbGsOut::CreateCtrlBusLines()
{
	ASSERT (m_pXDrawDataRef != NULL);

	POS pos = GetHeadPosition();

	if (pos == NULL)
	{
		return;
	}

	CXScdDrawLine_Bus *pLineBus = GetGooseBus();
	m_pLineCtrlBus = new CXScdDrawLine_ToBus();
	m_pLineCtrlBus->m_pBeginObj = m_pXDrawDataRef;
	m_pLineCtrlBus->m_pEndObj   = NULL;
	
	m_pLineCtrlBus->m_pBeginElement = this;
	m_pLineCtrlBus->m_pEndElement = pLineBus;
	pLineBus->AddLine(m_pLineCtrlBus);

	CXScdDrawCtrl_ThumbBase::CreateCtrlBusLines();
}

