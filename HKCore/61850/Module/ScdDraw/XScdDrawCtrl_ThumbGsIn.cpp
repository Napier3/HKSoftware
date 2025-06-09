//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawCtrl_ThumbGsIn.cpp  CXScdDrawCtrl_ThumbGsIn


#include "stdafx.h"
#include "XScdDrawCtrl_ThumbGsIn.h"
#include "XScdDrawLine_Ctrls.h"

CXScdDrawCtrl_ThumbGsIn::CXScdDrawCtrl_ThumbGsIn()
{
	//初始化属性

	//初始化成员变量
	m_strName = _T("GIN");
}

CXScdDrawCtrl_ThumbGsIn::~CXScdDrawCtrl_ThumbGsIn()
{
}

void CXScdDrawCtrl_ThumbGsIn::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CXScdDrawCtrl_ThumbBase::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
}


void CXScdDrawCtrl_ThumbGsIn::CreateCtrlLines()
{
	ASSERT (m_pXDrawDataRef != NULL);

	CSclCtrlsGsIn  *pSclCtrlsGsIn  = (CSclCtrlsGsIn*)m_pXDrawDataRef;
	CSclCtrlGsIn   *pSclCtrlGsIn   = NULL;
	CSclCtrlsGsOut *pSclCtrlsGsOut = NULL;
	CSclCtrlGsOut  *pSclCtrlGsOut  = NULL;

	CSclIed *pSclIedByCtrlsGsIn=(CSclIed *)pSclCtrlsGsIn->GetParent();//
	//CXScdDrawIedThumbnail *pScdDrawIedThumbnail =pSclCtrlsGsIn->GetParent();
	//if(pSclIedByCtrlsGsIn->m_strID!=_T("PB5011A"))
	//{
	//	return;
	//}

	CSclStation *pSclStation = (CSclStation*)m_pXDrawDataRef->GetAncestor(SCLIECCLASSID_STATION);
	ASSERT (pSclStation != NULL);

	if (pSclStation == NULL)
	{
		return;
	}

	POS pos = pSclCtrlsGsIn->GetHeadPosition();
	CXScdDrawLine_Ctrls *pLine = NULL;

	while (pos != NULL)
	{
		pSclCtrlGsIn = (CSclCtrlGsIn *)pSclCtrlsGsOut->GetNext(pos);
		pSclCtrlGsOut = pSclStation->FindCrl_GooseOutput(pSclCtrlGsIn->m_strGooseId);

		if (pSclCtrlGsOut == NULL)
		{
			continue;
		}

		pSclCtrlsGsOut = (CSclCtrlsGsOut *)pSclCtrlGsOut->GetParent();
		CSclIed *pSclIedByCtrlsGsOut=(CSclIed *)pSclCtrlsGsOut->GetParent();

// 		if(pSclIedByCtrlsGsIn->m_strIedTypeLabel==pSclIedByCtrlsGsOut->m_strIedTypeLabel)
// 		{
// 			continue;
// 		}

		pLine = (CXScdDrawLine_Ctrls*)FindLineByBeginRef(pSclCtrlsGsOut);

		if (pLine == NULL)
		{
			pLine = new CXScdDrawLine_Ctrls();
			pLine->m_pBeginObj = pSclCtrlsGsOut;
			pLine->m_pEndObj   = m_pXDrawDataRef;
			pLine->m_pEndElement = this;
		
			AddNewChild(pLine);
		}
	}
}


void CXScdDrawCtrl_ThumbGsIn::CreateCtrlBusLines()
{
	ASSERT (m_pXDrawDataRef != NULL);

	POS pos = GetHeadPosition();

	if (pos == NULL)
	{
		return;
	}

	CXScdDrawLine_Bus *pLineBus = GetGooseBus();
	m_pLineCtrlBus = new CXScdDrawLine_ToBus();
	m_pLineCtrlBus->m_pBeginObj = NULL;
	m_pLineCtrlBus->m_pEndObj   = m_pXDrawDataRef;
	
	m_pLineCtrlBus->m_pBeginElement = pLineBus;
	m_pLineCtrlBus->m_pEndElement   = this;
	pLineBus->AddLine(m_pLineCtrlBus);
	
	CXScdDrawCtrl_ThumbBase::CreateCtrlBusLines();
}

