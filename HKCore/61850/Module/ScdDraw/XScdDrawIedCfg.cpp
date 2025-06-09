//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XScdDrawIed.cpp  CXScdDrawIed


#include "stdafx.h"
#include "XScdDrawIedCfg.h"

int  g_nCount_LeftIeds=0;
int  g_nCount_RightIeds=0;

CXScdDrawIedCfg::CXScdDrawIedCfg()
{
	//初始化属性
    m_Symble_MainIed=0;
	//初始化成员变量
	m_strIP="";
	m_strManufacturer="";
}

CXScdDrawIedCfg::~CXScdDrawIedCfg()
{
}



CXScdDrawCtrlBase* CXScdDrawIedCfg::XCreateCtrl_SvIn_Cfg(CIecCfgDataBase *pIecfgData, CWnd *pParentWnd)
{
	CXScdDrawCtrl_CfgSvIn *pNew = new CXScdDrawCtrl_CfgSvIn();
	AddNewChild(pNew);
	pNew->XCreateElement(pIecfgData, pParentWnd);

	return pNew;
}

CXScdDrawCtrlBase* CXScdDrawIedCfg::XCreateCtrl_SvOut_Cfg(CIecCfgDataBase *pIecfgData, CWnd *pParentWnd)
{
	CXScdDrawCtrl_CfgSvOut *pNew = new CXScdDrawCtrl_CfgSvOut();
	AddNewChild(pNew);
	pNew->XCreateElement(pIecfgData, pParentWnd);

	return pNew;
}

CXScdDrawCtrlBase* CXScdDrawIedCfg::XCreateCtrl_GsIn_Cfg(CIecCfgDataBase *pIecfgData, CWnd *pParentWnd)
{
	CXScdDrawCtrl_CfgGsIn *pNew = new CXScdDrawCtrl_CfgGsIn();
	AddNewChild(pNew);

	//对应IEC61850配置的GOOSE发布，查找相应的保护GOOSEIN部分
	pNew->XCreateElement(pIecfgData, pParentWnd);

	return pNew;
}

CXScdDrawCtrlBase* CXScdDrawIedCfg::XCreateCtrl_GsOut_Cfg(CIecCfgDataBase *pIecfgData, CWnd *pParentWnd)
{
	CXScdDrawCtrl_CfgGsOut *pNew = new CXScdDrawCtrl_CfgGsOut();
	AddNewChild(pNew);
	pNew->XCreateElement(pIecfgData, pParentWnd);

	return pNew;
}


CXScdDrawCtrlBase* CXScdDrawIedCfg::XCreateCtrl_SvIn_Scl(CIecCfgDataBase *pIecfgData, CWnd *pParentWnd)
{
	CXScdDrawCtrl_SclSvIn *pNew = new CXScdDrawCtrl_SclSvIn();
	AddNewChild(pNew);
	pNew->XCreateElement(pIecfgData, pParentWnd);

	return pNew;
}

CXScdDrawCtrlBase* CXScdDrawIedCfg::XCreateCtrl_SvOut_Scl(CIecCfgDataBase *pIecfgData, CWnd *pParentWnd)
{
	CXScdDrawCtrl_CfgSvOut *pNew = new CXScdDrawCtrl_CfgSvOut();
	AddNewChild(pNew);
	pNew->XCreateElement(pIecfgData, pParentWnd);

	return pNew;
}

CXScdDrawCtrlBase* CXScdDrawIedCfg::XCreateCtrl_GsIn_Scl(CIecCfgDataBase *pIecfgData, CWnd *pParentWnd)
{
	CXScdDrawCtrl_SclGsIn *pNew = new CXScdDrawCtrl_SclGsIn();
	AddNewChild(pNew);

	pNew->XCreateElement(pIecfgData, pParentWnd);

	return pNew;
}

CXScdDrawCtrlBase* CXScdDrawIedCfg::XCreateCtrl_GsOut_Scl(CIecCfgDataBase *pIecfgData, CWnd *pParentWnd)
{
	CXScdDrawCtrl_CfgGsOut *pNew = new CXScdDrawCtrl_CfgGsOut();
	AddNewChild(pNew);
	pNew->XCreateElement(pIecfgData, pParentWnd);

	return pNew;
}


//void CXScdDrawIedCfg::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
//{
//	//绘制边框
//	//CRect rc(m_ptTopLeft.x, m_ptTopLeft.y, m_ptTopLeft.x+m_nWidth, m_ptTopLeft.y+m_nHeight);
//	//rc.DeflateRect(1,1,1,1);
//	//CPen pen(PS_SOLID, 1, RGB(0, 0, 255));
//	//CPen *pOldPen = pDC->SelectObject(&pen);
//	//CBrush brush;
//	//brush.CreateSolidBrush(RGB(192,192,192));
//	//CBrush *pOldBrush = pDC->SelectObject(&brush);
//	//pDC->Rectangle(rc);
//	//pDC->SelectObject(pOldPen);
//	//pDC->SelectObject(pOldBrush);
//
//
//	CFont font;//定义IED名字和ID的字体样式
//	CFont *pFont;
//	font.CreateFont(12,0,0,0,FW_MEDIUM,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_SWISS,"宋体");
//	pFont=pDC->SelectObject(&font);
//	pDC->SetTextColor(RGB(0,0,0));
//	pDC->SetBkColor(RGB(150,200,156));
//
//	if (m_Symble_MainIed==0)
//	{
//		CRect rc_IedID(m_ptTopLeft.x, m_ptTopLeft.y, m_ptTopLeft.x+m_nWidth, m_ptTopLeft.y+30);//定义IED的名字和ID的背景区域
//		rc_IedID.DeflateRect(1,1,1,1);
//		CPen pen(PS_SOLID, 1, RGB(0, 0, 255));//绘制IED的 名字和ID 的背景色
//		CPen *pOldPen = pDC->SelectObject(&pen);
//		CBrush brush;
//		brush.CreateSolidBrush(RGB(150,200,156));
//		CBrush *pOldBrush = pDC->SelectObject(&brush);
//		pDC->Rectangle(rc_IedID);
//
//		CRect rc_IedID_Text(m_ptTopLeft.x, m_ptTopLeft.y+8, m_ptTopLeft.x+m_nWidth, m_ptTopLeft.y+30);
//		pDC->DrawText(m_strID,strlen(m_strID),rc_IedID_Text,DT_CENTER);
//
//		pDC->SelectObject(pOldPen);
//		pDC->SelectObject(pOldBrush);
//		font.DeleteObject();
//
//	}
//	else
//	{
//
//		CRect rc_IedName(m_ptTopLeft.x, m_ptTopLeft.y, m_ptTopLeft.x+m_nWidth/3, m_ptTopLeft.y+30);//定义IED的名字和ID的背景区域
//		CRect rc_IedID(m_ptTopLeft.x+m_nWidth/3-2,m_ptTopLeft.y, (m_ptTopLeft.x+m_nWidth*5/9), m_ptTopLeft.y+30);
//		CRect rc_IedIP(m_ptTopLeft.x+m_nWidth*5/9-2,m_ptTopLeft.y, (m_ptTopLeft.x+m_nWidth*7/9), m_ptTopLeft.y+30);
//		CRect rc_IedManufature(m_ptTopLeft.x+m_nWidth*7/9-2,m_ptTopLeft.y, (m_ptTopLeft.x+m_nWidth), m_ptTopLeft.y+30);
//		rc_IedName.DeflateRect(1,1,1,1);
//		rc_IedID.DeflateRect(1,1,1,1);
//       	rc_IedIP.DeflateRect(1,1,1,1);
//		rc_IedManufature.DeflateRect(1,1,1,1);
//
//		CPen pen(PS_SOLID, 1, RGB(0, 0, 255));//绘制IED的 名字和ID 的背景色
//		CPen *pOldPen = pDC->SelectObject(&pen);
//		CBrush brush;
//		brush.CreateSolidBrush(RGB(150,200,156));
//		CBrush *pOldBrush = pDC->SelectObject(&brush);
//		pDC->Rectangle(rc_IedName);
//		pDC->Rectangle(rc_IedID);
//		pDC->Rectangle(rc_IedIP);
//		pDC->Rectangle(rc_IedManufature);
//
//
//		//if (strlen(m_strName)<m_nWidth/3)//重新定义 输入IED的名字和字体 的区域，比背景色稍微偏下，区别换行
//		//{
//			CRect rc_IedName_Text(m_ptTopLeft.x, m_ptTopLeft.y+8, m_ptTopLeft.x+m_nWidth/3, m_ptTopLeft.y+30);
//			pDC->DrawText(m_strName,strlen(m_strName),rc_IedName_Text,DT_CENTER);//输入IED的名字和字体
//	/*	}*/
//	/*	else
//		{
//			CRect rc_IedName_Text(m_ptTopLeft.x, m_ptTopLeft.y+2, m_ptTopLeft.x+m_nWidth/3, m_ptTopLeft.y+30);
//			pDC->DrawText(m_strName,strlen(m_strName),rc_IedName_Text,DT_EDITCONTROL|DT_WORDBREAK|DT_CENTER);
//		}*/
//
//
//		//if(strlen(m_strID)<m_nWidth*2/3)
//		//{
//			CRect rc_IedID_Text(m_ptTopLeft.x+m_nWidth/3, m_ptTopLeft.y+8, m_ptTopLeft.x+m_nWidth*5/9, m_ptTopLeft.y+30);
//			pDC->DrawText(m_strID,strlen(m_strID),rc_IedID_Text,DT_CENTER);
//		//}
//		//else
//		//{
//		//	CRect rc_IedID_Text(m_ptTopLeft.x+m_nWidth/3, m_ptTopLeft.y+2, m_ptTopLeft.x+m_nWidth, m_ptTopLeft.y+30);
//		//	pDC->DrawText(m_strID,strlen(m_strID),rc_IedID_Text,DT_EDITCONTROL|DT_WORDBREAK|DT_CENTER);
//		//}
//
//			CRect rc_IedIP_Text(m_ptTopLeft.x+m_nWidth*5/9, m_ptTopLeft.y+8, m_ptTopLeft.x+m_nWidth*7/9, m_ptTopLeft.y+30);
//			pDC->DrawText(m_strIP,strlen(m_strIP),rc_IedIP_Text,DT_CENTER);
//
//			CRect rc_IedManufature_Text(m_ptTopLeft.x+m_nWidth*7/9, m_ptTopLeft.y+8, m_ptTopLeft.x+m_nWidth, m_ptTopLeft.y+30);
//			if (m_strManufacturer=="")
//			{
//				CString strTrmp=_T("厂家不详");
//				pDC->DrawText(strTrmp,strlen(strTrmp),rc_IedManufature_Text,DT_CENTER);
//			}
//			pDC->DrawText(m_strManufacturer,strlen(m_strManufacturer),rc_IedManufature_Text,DT_CENTER);
//
//		pDC->SelectObject(pOldPen);
//		pDC->SelectObject(pOldBrush);
//		font.DeleteObject();
//
//	}
//
//	
//
//
//
//	CRect rc_Ied(m_ptTopLeft.x, m_ptTopLeft.y+28, (m_ptTopLeft.x+m_nWidth), m_ptTopLeft.y+m_nHeight);
//	rc_Ied.DeflateRect(1,1,1,1);
//	CPen pen1(PS_SOLID, 1, RGB(0, 0, 255));//重新定义IED正文的画笔和画刷
//	CPen *pOldPen1 = pDC->SelectObject(&pen1);
//	CBrush brush1;
//	brush1.CreateSolidBrush(RGB(192,192,192));
//	CBrush *pOldBrush1 = pDC->SelectObject(&brush1);
//	pDC->Rectangle(rc_Ied);
//	pDC->SelectObject(pOldPen1);
//	pDC->SelectObject(pOldBrush1);
//
//	CXDrawElements::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
//}

void CXScdDrawIedCfg::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	//绘制边框

	CFont font;//定义IED名字和ID的字体样式
	CFont *pFont;
	font.CreateFont(12,0,0,0,FW_MEDIUM,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_SWISS,"宋体");
	pFont=pDC->SelectObject(&font);
	pDC->SetTextColor(RGB(0,0,0));
	pDC->SetBkColor(RGB(150,200,156));

	CRect rc_IedName(m_ptTopLeft.x, m_ptTopLeft.y, m_ptTopLeft.x+m_nWidth/3, m_ptTopLeft.y+30);//定义IED的名字和ID的背景区域
	CRect rc_IedID(m_ptTopLeft.x+m_nWidth/3-2,m_ptTopLeft.y, (m_ptTopLeft.x+m_nWidth), m_ptTopLeft.y+30);
	rc_IedName.DeflateRect(1,1,1,1);
	rc_IedID.DeflateRect(1,1,1,1);


	CPen pen(PS_SOLID, 1, RGB(0, 0, 255));//绘制IED的 名字和ID 的背景色
	CPen *pOldPen = pDC->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(RGB(150,200,156));
	CBrush *pOldBrush = pDC->SelectObject(&brush);
	pDC->Rectangle(rc_IedName);
	pDC->Rectangle(rc_IedID);


	if (strlen(m_strName)<m_nWidth/3)//重新定义 输入IED的名字和字体 的区域，比背景色稍微偏下，区别换行
	{
		CRect rc_IedName_Text(m_ptTopLeft.x, m_ptTopLeft.y+8, m_ptTopLeft.x+m_nWidth/3, m_ptTopLeft.y+30);
		pDC->DrawText(m_strName,strlen(m_strName),rc_IedName_Text,DT_CENTER);//输入IED的名字和字体
	}
	else
	{
		CRect rc_IedName_Text(m_ptTopLeft.x, m_ptTopLeft.y+2, m_ptTopLeft.x+m_nWidth/3, m_ptTopLeft.y+30);
		pDC->DrawText(m_strName,strlen(m_strName),rc_IedName_Text,DT_EDITCONTROL|DT_WORDBREAK|DT_CENTER);
	}


	if(strlen(m_strID)<m_nWidth*2/3)
	{
		CRect rc_IedID_Text(m_ptTopLeft.x+m_nWidth/3, m_ptTopLeft.y+8, m_ptTopLeft.x+m_nWidth, m_ptTopLeft.y+30);
		pDC->DrawText(m_strID,strlen(m_strID),rc_IedID_Text,DT_CENTER);
	}
	else
	{
		CRect rc_IedID_Text(m_ptTopLeft.x+m_nWidth/3, m_ptTopLeft.y+2, m_ptTopLeft.x+m_nWidth, m_ptTopLeft.y+30);
		pDC->DrawText(m_strID,strlen(m_strID),rc_IedID_Text,DT_EDITCONTROL|DT_WORDBREAK|DT_CENTER);
	}

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	font.DeleteObject();

	CRect rc_Ied(m_ptTopLeft.x, m_ptTopLeft.y+28, (m_ptTopLeft.x+m_nWidth), m_ptTopLeft.y+m_nHeight);
	rc_Ied.DeflateRect(1,1,1,1);
	CPen pen1(PS_SOLID, 1, RGB(0, 0, 255));//重新定义IED正文的画笔和画刷
	CPen *pOldPen1 = pDC->SelectObject(&pen1);
	CBrush brush1;
	brush1.CreateSolidBrush(RGB(192,192,192));
	CBrush *pOldBrush1 = pDC->SelectObject(&brush1);
	pDC->Rectangle(rc_Ied);
	pDC->SelectObject(pOldPen1);
	pDC->SelectObject(pOldBrush1);

	CXDrawElements::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
}

void CXScdDrawIedCfg::DrawLines(CDC *pDC, double fZoomRatio,const CPoint &ptOffset)
{
}


CSize CXScdDrawIedCfg::CalLayout(CSize &szDraw)
{
	POS pos = GetHeadPosition();
	CXDrawElement *p = NULL;
	CSize szElement, szIed(0, 0);

	while (pos != NULL)
	{
		p = (CXDrawElement *)GetNext(pos);
		szElement = p->CalLayout(szElement);
		szIed.cx = max(szIed.cx, szElement.cx);
		szIed.cy += szElement.cy;
	}

	if (szIed.cx == 0)
	{
		szIed.cx = XSCDDRAW_IED_WIDTH_MIN;
	}

	if (szIed.cy == 0)
	{
		szIed.cy = XSCDDRAW_IED_TITLE_HEIGHT;
	}

	//标题：
	szIed.cx += XSCDDRAW_IED_BORDER_GAP*2;
	szIed.cy += XSCDDRAW_IED_TITLE_HEIGHT;

	m_nWidth = szIed.cx;
	m_nHeight = szIed.cy;

	szDraw = szIed;
	return szDraw;
}

CSize CXScdDrawIedCfg::Layout(CPoint &ptTopLeft)
{
	POS pos = GetHeadPosition();
	CXScdDrawCtrlBase *pCtrlBase = NULL;
	CPoint pt,ptMainIed;
	CSize szCtrl;
	m_ptTopLeft = ptTopLeft;
	pt.x = ptTopLeft.x + XSCDDRAW_IED_BORDER_GAP;
	pt.y = ptTopLeft.y + XSCDDRAW_IED_BORDER_GAP + XSCDDRAW_IED_TITLE_HEIGHT;
	m_nHeight = XSCDDRAW_IED_TITLE_HEIGHT + XSCDDRAW_IED_BORDER_GAP;
	m_nWidth = 0;
	ptMainIed=pt;

	int nCountLeftIeds=g_nCount_LeftIeds;
	int nCountRightIeds=g_nCount_RightIeds;

	if(m_Symble_MainIed==0)
	{
		while (pos != NULL)
		{
			pCtrlBase = (CXScdDrawCtrlBase *)GetNext(pos);
			szCtrl = pCtrlBase->Layout(pt);
			pt.y += szCtrl.cy + XSCDDRAW_CTRL_GAP_UNMAINIED;
			m_nHeight += szCtrl.cy + XSCDDRAW_CTRL_GAP_UNMAINIED;
			m_nWidth = max(m_nWidth, szCtrl.cx);
		}
	}
	else //测试主IED
	{
		while(pos!=NULL&&nCountLeftIeds)
		{
			pCtrlBase = (CXScdDrawCtrlBase *)GetNext(pos);
			szCtrl = pCtrlBase->Layout(pt);
			pt.y += szCtrl.cy + XSCDDRAW_CTRL_GAP;
			m_nHeight += szCtrl.cy + XSCDDRAW_CTRL_GAP;
			m_nWidth = max(m_nWidth, szCtrl.cx);
			nCountLeftIeds--;
		}
		ptMainIed.x+=m_nWidth+30;
		m_nWidth+=30;
		long m_nWidth_Right=0;
		long m_nHeight_Right=XSCDDRAW_IED_TITLE_HEIGHT + XSCDDRAW_IED_BORDER_GAP;

		while(pos!=NULL)
		{
			pCtrlBase = (CXScdDrawCtrlBase *)GetNext(pos);
			szCtrl = pCtrlBase->Layout(ptMainIed);
			ptMainIed.y += szCtrl.cy + XSCDDRAW_CTRL_GAP;
			m_nHeight_Right += szCtrl.cy + XSCDDRAW_CTRL_GAP;
			m_nWidth_Right = max(m_nWidth_Right, szCtrl.cx);
		}
		m_nWidth+=m_nWidth_Right;
		m_nHeight=max(m_nHeight,m_nHeight_Right);
	}

	if (m_nWidth == 0)
	{
		m_nWidth = XSCDDRAW_IED_WIDTH_MIN;
	}

	if (m_nHeight == 0)
	{
		m_nHeight = XSCDDRAW_IED_TITLE_HEIGHT;
	}

	m_nWidth  += XSCDDRAW_IED_BORDER_GAP * 2;
// 	m_nHeight =  pt.y + XSCDDRAW_IED_BORDER_GAP;

	CSize sz(m_nWidth, m_nHeight);
	return sz;
}

