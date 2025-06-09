//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawViewThumbnail.cpp  CXScdDrawViewThumbnail


#include "stdafx.h"
#include "XScdDrawViewStationThumbnail.h"
#include "ThumbLayoutTool.h"

CXScdDrawViewStationThumbnail::CXScdDrawViewStationThumbnail()
{
	m_pLineGooseBus = new CXScdDrawLine_GooseBus();
	m_pLineSvBus = new CXScdDrawLine_SvBus();

	m_pLineGooseBus->SetParent(this);
	m_pLineSvBus->SetParent(this);
	//初始化属性

	//初始化成员变量
}

CXScdDrawViewStationThumbnail::~CXScdDrawViewStationThumbnail()
{
	delete m_pLineGooseBus;
	delete m_pLineSvBus;
}

void CXScdDrawViewStationThumbnail::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	m_pLineGooseBus->Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
	m_pLineSvBus->Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);

	CXDrawElements::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);

}


CXDrawElement* CXScdDrawViewStationThumbnail::XCreateChildElement(UINT nClassID)
{
	if (SCLIECCLASSID_IED == nClassID)
	{
		return new CXScdDrawIedThumbnail();
	}

	return NULL;
}

DWORD CXScdDrawViewStationThumbnail::XCreateElement(CExBaseObject *pData, CWnd *pParentWnd)
{
	UINT nClassID = pData->GetClassID();
	//ASSERT (nClassID == CFGCLASSID_CIECCFGDATASMNGR);

	//CreateElements
	InitXScdDrawViewThumbnail((CSclStation*)pData, pParentWnd);

	////CalLayout
	CSize szView(0,0);
	szView = CalLayout(szView);

	////调整位置
	//Layout(CPoint(0, 0));

	return XCREATE_SUCC;
}

void CXScdDrawViewStationThumbnail::CreateCtrlBusLines()
{
	POS pos = GetHeadPosition();
	CXScdDrawIedThumbnail *pIedThumb = NULL;

	while (pos != NULL)
	{
		pIedThumb = (CXScdDrawIedThumbnail *)GetNext(pos);
		pIedThumb->CreateCtrlBusLines();
	}
}

void CXScdDrawViewStationThumbnail::InitXScdDrawViewThumbnail(CSclStation *pSclStation, CWnd *pParentWnd)
{
	POS pos=pSclStation->GetHeadPosition();
	CSclIed *pIed=NULL;
	CExBaseObject *pTemp=NULL;

	m_pIedList_ProtMeas=new CXScdIedGroupThumb();
	m_pIedList_MergIntel=new CXScdIedGroupThumb();
	m_listIedGroup.AddTail(m_pIedList_ProtMeas);
	m_listIedGroup.AddTail(m_pIedList_MergIntel);
	m_oScdDrawLines.DeleteAll();

	CXScdDrawCtrl_ThumbBase::g_bNeedCreateCtrlLines = FALSE;
	CXScdDrawIedThumbnail *pDrawIed_Thumbnail = NULL;

	while (pos!=NULL)
	{
		pTemp = pSclStation->GetNext(pos);
		pIed=(CSclIed*)pTemp;

		if (pIed == pSclStation->GetTail())
		{
			int i =0;
		}

		if (pIed->GetClassID()==CFGCLASSID_CSCLBAY)
		{
			continue;
		}

		pDrawIed_Thumbnail = new CXScdDrawIedThumbnail();
		AddNewChild(pDrawIed_Thumbnail);
		pDrawIed_Thumbnail->m_strName=pIed->m_strName;
		pDrawIed_Thumbnail->m_strID=pIed->m_strID;
		pDrawIed_Thumbnail->SetRefIed(pIed);
		
		//if(pTempIed->m_strIedType==_T("合智一体装置")||pTempIed->m_strIedType==_T("合并单元")||pTempIed->m_strIedType==_T("智能终端"))
		if(pIed->IsIed_RPIT_MU())
		{
			m_pIedList_MergIntel->AddTail(pDrawIed_Thumbnail);
			pDrawIed_Thumbnail->SetSymbel(IEDTHUMBNAILTYPE_MUCTRL);
		}
		//	if (pTempIed->m_strIedType==_T("保护测控装置")||pTempIed->m_strIedType==_T("保护装置")||pTempIed->m_strIedType==_T("测控装置"))
		else /*if (pIed->m_strIedTypeLabel==_T("ProcMeas")
			||pIed->m_strIedTypeLabel==_T("Proc")
			||pIed->m_strIedTypeLabel==_T("Meas"))*/
		{
			m_pIedList_ProtMeas->AddTail(pDrawIed_Thumbnail);
			pDrawIed_Thumbnail->SetSymbel(IEDTHUMBNAILTYPE_PROCMEAS);
		}
		
		pDrawIed_Thumbnail->XCreateCtrl(pIed,pParentWnd);
	}

	pos = GetHeadPosition();

	while (pos != NULL)
	{
		pDrawIed_Thumbnail = (CXScdDrawIedThumbnail *)GetNext(pos);

		if (pDrawIed_Thumbnail == GetTail())
		{
			int i = 0;
		}

		pDrawIed_Thumbnail->CreateCtrlLines();
		pDrawIed_Thumbnail->GetAllLines(m_oScdDrawLines);
	}

	//调整连接线
	InitLinesBeginElement();

	CreateCtrlBusLines();

	CXScdDrawLine_Vert *pXScdDrawLine_Vert=NULL;
}



CSize CXScdDrawViewStationThumbnail::CalLayout(CSize &szDraw)
{
	CSize szEntire(0,0);//计算所有的IED的Size
	CSize szIed(0,0);
	POS pos=GetHeadPosition(); 
	CXScdDrawIedThumbnail *pIedThumbnail=NULL;
	CSclIed *pTempIed=NULL;

	while (pos!=NULL)
	{
		pIedThumbnail=(CXScdDrawIedThumbnail*)GetNext(pos);
		szIed=pIedThumbnail->CalLayout(szIed);
	}

	szEntire.cy=max(szEntire.cy,szIed.cy);
	szEntire.cx+=szIed.cx;

	//计算总的Size
	szDraw = Layout(CPoint(0, 0));

	return szDraw;
}

void CXScdDrawViewStationThumbnail::InitLinesBeginElement()
{
	POS pos = m_oScdDrawLines.GetHeadPosition(); 
	CXScdDrawLine_Vert *pLine = NULL;

	while (pos!=NULL)
	{
		pLine = (CXScdDrawLine_Vert *)m_oScdDrawLines.GetNext(pos);
		pLine->m_pBeginElement = QueryByXDrawDataRef(pLine->m_pBeginObj);

		ASSERT(pLine->m_pEndElement != NULL);

		if (pLine->m_pBeginElement != NULL)
		{
			pLine->m_pBeginElement->AddTail(pLine);
		}
	}
}

void CXScdDrawViewStationThumbnail::LayoutLines()
{
	POS pos = m_oScdDrawLines.GetHeadPosition(); 
	CXScdDrawLineBase *pLine = NULL;

	CXDrawElement *pElement=NULL;
	CXScdDrawIedThumbnail *pDrawIedThumbnail=NULL;
	CExBaseObject *pSclCtrls=NULL;
	CXScdDrawCtrl_ThumbBase *pXScdDrawCtrl=NULL;

	while (pos!=NULL)
	{
		pLine = (CXScdDrawLineBase *)m_oScdDrawLines.GetNext(pos);
		pLine->InitLinePos();
	}
}


void CXScdDrawViewStationThumbnail::LayoutBusLines(CXScdDrawLine_Bus *pBus)
{
	CXScdDrawLine_Bus *pLine = NULL;
	POS pos = pBus->GetHeadPosition();

	while (pos !=NULL)
	{
		pLine = (CXScdDrawLine_Bus *)pBus->GetNext(pos);
		pLine->InitLinePos();
		pLine->m_crForeColor = pBus->m_crForeColor;
	}
}


CSize CXScdDrawViewStationThumbnail::Layout(CPoint &ptTopLeft)
{
	CSize szMergIntel, szProcMeas;
	m_pIedList_ProtMeas->GetSize(szProcMeas,GETSIZE_MODE_XADD_YMAX);
	m_pIedList_MergIntel->GetSize(szMergIntel,GETSIZE_MODE_XADD_YMAX);

	ptTopLeft.x=XSCDDRAW_ELEMENT_MARGIN;
	ptTopLeft.y=XSCDDRAW_ELEMENT_MARGIN;

	//保护、测控
	szProcMeas=m_pIedList_ProtMeas->Layout(ptTopLeft);

	//合并单元、智能终端
	ptTopLeft.y += szProcMeas.cy + XSCDDRAW_THUMBNAIL_GAP_IED_Y;
	szMergIntel = m_pIedList_MergIntel->Layout(ptTopLeft);
	m_nHeight = ptTopLeft.y;

	m_nWidth  = max(szProcMeas.cx, szMergIntel.cx) + XSCDDRAW_THUMBNAIL_GAP_IED_X*2;
	m_nHeight +=szMergIntel.cy + XSCDDRAW_ELEMENT_MARGIN;

	//调整位置
	long nOffset = szMergIntel.cx - szProcMeas.cx;

	if (nOffset > 0)
	{
		ptTopLeft.x=XSCDDRAW_ELEMENT_MARGIN + (nOffset) / 2;
		ptTopLeft.y=XSCDDRAW_ELEMENT_MARGIN;
		m_pIedList_ProtMeas->Layout(ptTopLeft);
	}
	else
	{
		ptTopLeft.y = XSCDDRAW_ELEMENT_MARGIN + szProcMeas.cy + XSCDDRAW_THUMBNAIL_GAP_IED_Y;
		ptTopLeft.x=XSCDDRAW_ELEMENT_MARGIN - nOffset / 2;
		m_pIedList_MergIntel->Layout(ptTopLeft);
	}

	m_pLineGooseBus->m_ptBegin.x=XSCDDRAW_ELEMENT_MARGIN;
	m_pLineGooseBus->m_ptBegin.y=m_pIedList_ProtMeas->m_ptTopLeft.y+m_pIedList_ProtMeas->m_nHeight+(m_pIedList_MergIntel->m_ptTopLeft.y-m_pIedList_ProtMeas->m_ptTopLeft.y-m_pIedList_ProtMeas->m_nHeight)/3;
	m_pLineGooseBus->m_ptEnd.x= m_nWidth - XSCDDRAW_ELEMENT_MARGIN;//m_pLineGooseBus->m_ptBegin.x+max(m_pIedList_ProtMeas->m_nWidth,m_pIedList_MergIntel->m_nWidth);
	m_pLineGooseBus->m_ptEnd.y=  m_pLineGooseBus->m_ptBegin.y;	 
	m_pLineGooseBus->m_ptTopLeft = m_pLineGooseBus->m_ptBegin;

	m_pLineSvBus->m_ptBegin.x=XSCDDRAW_ELEMENT_MARGIN;
	m_pLineSvBus->m_ptBegin.y=m_pIedList_ProtMeas->m_ptTopLeft.y+m_pIedList_ProtMeas->m_nHeight+(m_pIedList_MergIntel->m_ptTopLeft.y-m_pIedList_ProtMeas->m_ptTopLeft.y-m_pIedList_ProtMeas->m_nHeight)*2/3;
	m_pLineSvBus->m_ptEnd.x= m_nWidth - XSCDDRAW_ELEMENT_MARGIN;//m_pLineSvBus->m_ptBegin.x+max(m_pIedList_ProtMeas->m_nWidth,m_pIedList_MergIntel->m_nWidth);
	m_pLineSvBus->m_ptEnd.y=m_pLineSvBus->m_ptBegin.y;
	m_pLineSvBus->m_ptTopLeft = m_pLineSvBus->m_ptBegin;

	LayoutLines();
	LayoutBusLines(m_pLineSvBus);
	LayoutBusLines(m_pLineGooseBus);

	return CSize(m_nWidth, m_nHeight);
}