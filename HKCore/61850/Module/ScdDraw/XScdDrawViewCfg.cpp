//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XScdDrawViewIedCfg.cpp  CXScdDrawViewIedCfg


#include "stdafx.h"
#include "XScdDrawViewCfg.h"

extern int  g_nCount_LeftIeds;
extern int  g_nCount_RightIeds;

CXScdDrawViewCfg::CXScdDrawViewCfg()
{
	//��ʼ������

	//��ʼ����Ա����
	m_pMainIed = NULL;
	m_pLeft = NULL;
	m_pRight = NULL;
}

CXScdDrawViewCfg::~CXScdDrawViewCfg()
{
}

DWORD CXScdDrawViewCfg::XCreateElement(CExBaseObject *pData, CWnd *pParentWnd)
{
	UINT nClassID = pData->GetClassID();
	ASSERT (nClassID == CFGCLASSID_CIECCFGDATASMNGR);

	//CreateElements
	InitXScdDrawView((CIecCfgDatasMngr*)pData, pParentWnd);

	if (m_pMainIed == NULL)
	{
		return XCREATE_FAIL;
	}

	//CalLayout
	CSize szView(0,0);
	szView = CalLayout(szView);

	//����λ��
	Layout(CPoint(0, 0));

	return XCREATE_SUCC;
}

void CXScdDrawViewCfg::InitXScdDrawView(CIecCfgDatasMngr *pCfgDatasMngr, CWnd *pParentWnd)
{
	CIecCfgDevice *pIecCfgDevice = (CIecCfgDevice*)pCfgDatasMngr->GetParent();

	if (pIecCfgDevice == NULL)
	{
		return;
	}

	m_pSclIed = pIecCfgDevice->m_pSclIed;
	ASSERT (m_pMainIed == NULL);
	m_pMainIed = new CXScdDrawIedCfg();
	AddNewChild(m_pMainIed);
	m_pMainIed->SetSymbleMainIed(TRUE);//������IED�ı�־

	CSclIed *pSclIed=pIecCfgDevice->m_pSclIed;

	if (pSclIed == NULL)
	{
		return;
	}

	m_pMainIed->m_strName = pSclIed->m_strName;
	m_pMainIed->m_strID   = pSclIed->m_strID;
	m_pMainIed->m_pXDrawDataRef = pIecCfgDevice;
	m_pMainIed->m_strIP=pSclIed->m_strIP;
	m_pMainIed->m_strManufacturer=pSclIed->m_strManufacturer;

	CIecCfgDatasSMV  *pCfgDatasSmv     = pCfgDatasMngr->GetSmvMngr();
	CIecCfgGinDatas  *pIecCfgGinDatas  = pCfgDatasMngr->GetGinMngr();
	CIecCfgGoutDatas *pIecCfgGoutDatas = pCfgDatasMngr->GetGoutMngr();
	
	InitXScdDrawView(pCfgDatasSmv, m_pMainIed, pParentWnd);
	InitXScdDrawView(pIecCfgGoutDatas, m_pMainIed, pParentWnd);
	InitXScdDrawView(pIecCfgGinDatas, m_pMainIed, pParentWnd);


// 	CXScdDrawCtrlBase *pCtrl = (CXScdDrawCtrlBase*)m_pMainIed->GetHead();
// 
// 	if (pCtrl != NULL)
// 	{
// 		pCtrl->SetShowChs(TRUE);
// 	}
}

/*
CIecCfgDatasSMV
	��IED������װ�õ�SvIn�źţ�ʹ��SCL���ݶ���
	�ⲿIED��������ģ��SvOut��ʹ��CIecCfgDatasSMV
*/
void CXScdDrawViewCfg::InitXScdDrawView(CIecCfgDatasSMV *pIecCfgDatasSMV, CXScdDrawIedCfg *pMainIed, CWnd *pParentWnd)
{
	CExBaseList oCfgDatas;
	pIecCfgDatasSMV->GetIecCfgDatas(oCfgDatas);

	CIecCfgDataBase *pIecfgData = NULL;
	CXScdDrawIedCfg *pIedDraw = NULL;
	POS pos = oCfgDatas.GetHeadPosition();
	CXScdDrawCtrlBase *pCtrl_SvOut_Cfg = NULL;
	CXScdDrawCtrlBase *pCtrl_SvIn_Scl = NULL;

	while (pos != NULL)
	{
		pIecfgData = (CIecCfgDataBase *)oCfgDatas.GetNext(pos);
		pIedDraw = (CXScdDrawIedCfg *)FindByName(pIecfgData->m_strIedRefDesc);

		if (pIedDraw == NULL)
		{
			pIedDraw = new CXScdDrawIedCfg();
			AddNewChild(pIedDraw);
		}
		pIedDraw->m_strID=pIecfgData->m_strIedRefDesc;

		pCtrl_SvOut_Cfg = pIedDraw->XCreateCtrl_SvOut_Cfg(pIecfgData, pParentWnd);
		pCtrl_SvIn_Scl = pMainIed->XCreateCtrl_SvIn_Scl(pIecfgData, pParentWnd);
		pCtrl_SvIn_Scl->InitLineBeginElement(pCtrl_SvOut_Cfg);
		pCtrl_SvIn_Scl->AddXScdDrawLineCtrl(pCtrl_SvOut_Cfg, pCtrl_SvIn_Scl, pIecfgData, pIecfgData->m_pSclRef);
		pCtrl_SvIn_Scl->GetAllLines(m_oScdDrawLines);
	}

	oCfgDatas.RemoveAll();
}

/*
CIecCfgGinDatas��GOOSE����
	��IED������װ�õĿ����źţ�ʹ��CIecCfgGinDatas����������ǵĿ���󶨹�ϵ
	�ⲿIED����
*/
void CXScdDrawViewCfg::InitXScdDrawView(CIecCfgGinDatas *pIecCfgGinDatas, CXScdDrawIedCfg *pMainIed, CWnd *pParentWnd)
{
	CExBaseList oCfgDatas;
	pIecCfgGinDatas->GetIecCfgDatas(oCfgDatas);

	CIecCfgDataBase *pIecfgData = NULL;
	CXScdDrawIedCfg *pIedDraw = NULL;
	POS pos = oCfgDatas.GetHeadPosition();

	CXScdDrawCtrlBase *pCtrl_GsOut_Cfg = NULL;
	CXScdDrawCtrlBase *pCtrl_GsIn_Scl = NULL;

	while (pos != NULL)
	{
		pIecfgData = (CIecCfgDataBase *)oCfgDatas.GetNext(pos);
		pIedDraw = (CXScdDrawIedCfg *)FindByName(pIecfgData->m_strIedRefDesc);

		if (pIedDraw == NULL)
		{
			pIedDraw = new CXScdDrawIedCfg();
			AddNewChild(pIedDraw);
		}

		//��������ǵĿ���󶨣�GOOSE����
		pIedDraw->m_strID=pIecfgData->m_strIedRefDesc;
		//pMainIed->XCreateCtrl_GsIn_Cfg(pIecfgData, pParentWnd);

	
         //	pMainIed->XCreateCtrl_GsIn_Scl(pIecfgData, pParentWnd);
	 

	}

	oCfgDatas.RemoveAll();
}

/*
CIecCfgGoutDatas��GOOSE����
	�ⲿIED����������ģ�⣬��������ǿ�����ʹ��CIecCfgGoutDatas
	��IED������װ�õ����붨�壬ʹ��SCL����
*/
void CXScdDrawViewCfg::InitXScdDrawView(CIecCfgGoutDatas *pIecCfgGoutDatas, CXScdDrawIedCfg *pMainIed, CWnd *pParentWnd)
{
	CExBaseList oCfgDatas;
	pIecCfgGoutDatas->GetIecCfgDatas(oCfgDatas);

	CIecCfgDataBase *pIecfgData = NULL;
	CXScdDrawIedCfg *pIedDraw = NULL;
	POS pos = oCfgDatas.GetHeadPosition();

	while (pos != NULL)
	{
		pIecfgData = (CIecCfgDataBase *)oCfgDatas.GetNext(pos);
		pIedDraw = (CXScdDrawIedCfg *)FindByName(pIecfgData->m_strIedRefDesc);

		if (pIedDraw == NULL)
		{
			pIedDraw = new CXScdDrawIedCfg();
			AddNewChild(pIedDraw);
		}

		//�ⲿIED����������ģ�⣬��������ǿ�����ʹ��CIecCfgGoutDatas
	//	pIedDraw->XCreateCtrl_GsOut_Cfg(pIecfgData, pParentWnd);

		//��IED������װ�õ����붨�壬ʹ��SCL����
	//	pMainIed->XCreateCtrl_GsIn_Scl(pIecfgData, pParentWnd);

/////////////////////////////////////////////////////////////////////////////////////////////////////cgl
		//��������ǵĿ���󶨣�GOOSE����
		pIedDraw->m_strID=pIecfgData->m_strIedRefDesc;
		//pMainIed->XCreateCtrl_GsIn_Cfg(pIecfgData, pParentWnd);

		CXScdDrawCtrlBase *pCtrl_GsOut_Cfg = NULL;
		CXScdDrawCtrlBase *pCtrl_GsIn_Scl = NULL;

		pCtrl_GsOut_Cfg = pIedDraw->XCreateCtrl_GsOut_Cfg(pIecfgData, pParentWnd);
		pCtrl_GsIn_Scl = pMainIed->XCreateCtrl_GsIn_Scl(pIecfgData, pParentWnd);
		pCtrl_GsIn_Scl->InitLineBeginElement(pCtrl_GsOut_Cfg);
		pCtrl_GsIn_Scl->AddXScdDrawLineCtrl(pCtrl_GsOut_Cfg, pCtrl_GsIn_Scl, pIecfgData, pIecfgData->m_pSclRef);
		pCtrl_GsIn_Scl->GetAllLines(m_oScdDrawLines);
	}

	oCfgDatas.RemoveAll();
}


// 
// void CXScdDrawViewCfg::InitXScdDrawView(CExBaseList *pCfgDatas)
// {
// 	POS pos = pCfgDatas->GetHeadPosition();
// 	CIecCfgDataBase *pIecfgData = NULL;
// 	CXScdDrawIedCfg *pIedDraw = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pIecfgData = (CIecCfgDataBase *)pCfgDatas->GetNext(pos);
// 		pIedDraw = (CXScdDrawIedCfg *)FindByName(pIecfgData->m_strCtrlRef);
// 
// 		if (pIedDraw == NULL)
// 		{
// 			pIedDraw = new CXScdDrawIedCfg();
// 			AddNewChild(pIedDraw);
// 		}
// 
// 		pIedDraw->XCreateCtrl(pIecfgData);
// 	}
// }

void CXScdDrawViewCfg::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	if (m_pMainIed == NULL)
	{
		return;
	}

	CXScdDrawViewBase::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
}

// void CXScdDrawViewCfg::Pick(const CPoint &point, CExBaseList &oList)
// {
// 	
// }

CSize CXScdDrawViewCfg::Layout(CPoint &ptTopLeft)
{
	CSize szLeft, szRight, szIed;
	m_pLeft->GetSize(szLeft, GETSIZE_MODE_XMAX_YADD);
	m_pRight->GetSize(szRight, GETSIZE_MODE_XMAX_YADD);
	m_pMainIed->GetSize(szIed, GETSIZE_MODE_XMAX_YADD);


	ptTopLeft.x = XSCDDRAW_VIEW_GAP;
	ptTopLeft.y = XSCDDRAW_VIEW_GAP;

	g_nCount_LeftIeds=m_pLeft->GetCount();
	g_nCount_RightIeds=m_pRight->GetCount();

	szLeft = m_pLeft->Layout(ptTopLeft);



	ptTopLeft.x += XSCDDRAW_VIEW_IED_GAP_HOR + szLeft.cx;
	
	//ptTopLeft.y+=300;//cgl
	szIed = m_pMainIed->Layout(ptTopLeft);

	ptTopLeft.x += szIed.cx + XSCDDRAW_VIEW_IED_GAP_HOR;
	szRight = m_pRight->Layout(ptTopLeft);

	m_nWidth = XSCDDRAW_VIEW_GAP * 2 + szLeft.cx + XSCDDRAW_VIEW_IED_GAP_HOR*2 + szIed.cx + szRight.cx;
	m_nHeight = max(szLeft.cy, szRight.cy);
	m_nHeight = max(m_nHeight, szIed.cy);

	return CSize(m_nWidth, m_nHeight);
}

CSize CXScdDrawViewCfg::CalLayout(CSize &szDraw)
{
	CSize szMain, szOther;
	szMain = m_pMainIed->CalLayout(szMain);	//����m_pMainIed��Size
	szOther = CalLayoutOtherIed();	//��������Ied��Size
	
	//������Ied�ֳ����н��м���
	szOther.cy /= 2;
	szOther = CalLayoutOtherIed(szOther);

	//�����ܵ�Size
	szDraw = Layout(CPoint(0, 0));

	return szDraw;
}

CSize CXScdDrawViewCfg::CalLayoutOtherIed()
{
	CSize szOther(0, 0), szIed(0, 0);
	POS pos = GetHeadPosition();
	CXScdDrawIedCfg *pIedDraw = NULL;

	while (pos != NULL)
	{
		pIedDraw = (CXScdDrawIedCfg *)GetNext(pos);

		if (pIedDraw == m_pMainIed)
		{
			continue;
		}

		szIed = pIedDraw->CalLayout(szIed);
		szOther.cx = max(szOther.cx, szIed.cx);
		szOther.cy += szIed.cy;
	}

	return szOther;
}

CSize CXScdDrawViewCfg::CalLayoutOtherIed(CSize szSplit)
{
	CSize szOther(0, 0), szIed(0, 0);
	POS pos = GetHeadPosition();
	CXScdDrawIedCfg *pIedDraw = NULL;
	m_pLeft = new CXScdIedGroup();
	m_pRight = new CXScdIedGroup();
	m_listIedGroup.AddTail(m_pLeft);
	m_listIedGroup.AddTail(m_pRight);

	while (pos != NULL)
	{
		pIedDraw = (CXScdDrawIedCfg *)GetNext(pos);

		if (pIedDraw == m_pMainIed)
		{
			continue;
		}

		m_pLeft->AddTail(pIedDraw);
		//pIedDraw->GetSize(szIed, GETSIZE_MODE_XMAX_YADD);
		szOther.cx = max(szOther.cx, pIedDraw->m_nWidth);
		szOther.cy += pIedDraw->m_nHeight;

		if (szOther.cy >= szSplit.cy)
		{
			break;
		}
	}

	while (pos != NULL)
	{
		pIedDraw = (CXScdDrawIedCfg *)GetNext(pos);
		m_pRight->AddTail(pIedDraw);
	}

	return szOther;
}

