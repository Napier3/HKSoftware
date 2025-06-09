//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XScdDrawIed.cpp  CXScdDrawIed


#include "stdafx.h"
#include "XScdDrawIedCfg.h"

CXScdDrawIedBase::CXScdDrawIedBase()
{
	//��ʼ������

	//��ʼ����Ա����
}

CXScdDrawIedBase::~CXScdDrawIedBase()
{
}

void CXScdDrawIedBase::AttachViewWindow(CXDrawBaseInterface_ViewWindow *pViewWindow)
{
	POS pos = GetHeadPosition();
	CXScdDrawCtrlBase *pCtrlBase = NULL;

	while (pos != NULL)
	{
		pCtrlBase = (CXScdDrawCtrlBase *)GetNext(pos);
		pCtrlBase->AttachViewWindow(pViewWindow);
	}
}


void CXScdDrawIedBase::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	//���Ʊ߿�

	CFont font;//����IED���ֺ�ID��������ʽ
	CFont *pFont;
	font.CreateFont(12,0,0,0,FW_MEDIUM,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_SWISS,"����");
	pFont=pDC->SelectObject(&font);
	pDC->SetTextColor(RGB(0,0,0));
	pDC->SetBkColor(RGB(150,200,156));

	CRect rc_IedName(m_ptTopLeft.x, m_ptTopLeft.y, m_ptTopLeft.x+m_nWidth/3, m_ptTopLeft.y+30);//����IED�����ֺ�ID�ı�������
	CRect rc_IedID(m_ptTopLeft.x+m_nWidth/3-2,m_ptTopLeft.y, (m_ptTopLeft.x+m_nWidth), m_ptTopLeft.y+30);
	rc_IedName.DeflateRect(1,1,1,1);
	rc_IedID.DeflateRect(1,1,1,1);


	CPen pen(PS_SOLID, 1, RGB(0, 0, 255));//����IED�� ���ֺ�ID �ı���ɫ
	CPen *pOldPen = pDC->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(RGB(150,200,156));
	CBrush *pOldBrush = pDC->SelectObject(&brush);
	pDC->Rectangle(rc_IedName);
	pDC->Rectangle(rc_IedID);
	CString strName, strID;
	
	if (m_pXDrawDataRef != NULL)
	{
		strName = m_pXDrawDataRef->m_strName;
		strID = m_pXDrawDataRef->m_strID;
	}
	else
	{
		strName = m_strName;
		strID = m_strID;
	}

	if (strlen(strID)<m_nWidth/3)//���¶��� ����IED�����ֺ����� �����򣬱ȱ���ɫ��΢ƫ�£�������
	{
		CRect rc_IedName_Text(m_ptTopLeft.x, m_ptTopLeft.y+8, m_ptTopLeft.x+m_nWidth/3, m_ptTopLeft.y+30);
		pDC->DrawText(strID,strlen(strID),rc_IedName_Text,DT_CENTER);//����IED�����ֺ�����
	}
	else
	{
		CRect rc_IedName_Text(m_ptTopLeft.x, m_ptTopLeft.y+2, m_ptTopLeft.x+m_nWidth/3, m_ptTopLeft.y+30);
		pDC->DrawText(strID,strlen(strID),rc_IedName_Text,DT_EDITCONTROL|DT_WORDBREAK|DT_CENTER);
	}

	if(strlen(strName)<m_nWidth*2/3)
	{
		CRect rc_IedID_Text(m_ptTopLeft.x+m_nWidth/3, m_ptTopLeft.y+8, m_ptTopLeft.x+m_nWidth, m_ptTopLeft.y+30);
		pDC->DrawText(strName,strlen(strName),rc_IedID_Text,DT_CENTER);
	}
	else
	{
		CRect rc_IedID_Text(m_ptTopLeft.x+m_nWidth/3, m_ptTopLeft.y+2, m_ptTopLeft.x+m_nWidth, m_ptTopLeft.y+30);
		pDC->DrawText(strName,strlen(strName),rc_IedID_Text,DT_EDITCONTROL|DT_WORDBREAK|DT_CENTER);
	}

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
	font.DeleteObject();

	CRect rc_Ied(m_ptTopLeft.x, m_ptTopLeft.y+28, (m_ptTopLeft.x+m_nWidth), m_ptTopLeft.y+m_nHeight);
	rc_Ied.DeflateRect(1,1,1,1);
	CPen pen1(PS_SOLID, 1, RGB(0, 0, 255));//���¶���IED���ĵĻ��ʺͻ�ˢ
	CPen *pOldPen1 = pDC->SelectObject(&pen1);
	CBrush brush1;
	brush1.CreateSolidBrush(RGB(192,192,192));
	CBrush *pOldBrush1 = pDC->SelectObject(&brush1);
	pDC->Rectangle(rc_Ied);
	pDC->SelectObject(pOldPen1);
	pDC->SelectObject(pOldBrush1);

	CXDrawElements::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
}

void CXScdDrawIedBase::GetAllLines(CXDrawElements &oScdLines)
{
	CXScdDrawCtrlBase *pCtrl = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pCtrl = (CXScdDrawCtrlBase *)GetNext(pos);
		pCtrl->GetAllLines(oScdLines);
	}
}

void CXScdDrawIedBase::CreateCtrlLines()
{
	POS pos = GetHeadPosition();
	CXScdDrawCtrlBase *pCtrl = NULL;

	while (pos != NULL)
	{
		pCtrl = (CXScdDrawCtrlBase *)GetNext(pos);
		pCtrl->CreateCtrlLines();
	}
}

void CXScdDrawIedBase::OnOnlyShowUsedChsChanged(CXScdDrawLines *pLines)
{
	POS pos = GetHeadPosition();
	CXScdDrawCtrlBase *pCtrl = NULL;

	while (pos != NULL)
	{
		pCtrl = (CXScdDrawCtrlBase *)GetNext(pos);
		pCtrl->OnOnlyShowUsedChsChanged(pLines);
	}
}

void CXScdDrawIedBase::RemoveErrorLines()
{
	POS pos = GetHeadPosition();
	CXScdDrawCtrlBase *pCtrl = NULL;

	while (pos != NULL)
	{
		pCtrl = (CXScdDrawCtrlBase *)GetNext(pos);
		pCtrl->RemoveErrorLines();
	}
}
