//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XScdDrawIed.cpp  CXScdDrawIed


#include "stdafx.h"
#include "XScdDrawLine_Ctrls.h"


CXScdDrawLine_Ctrls::CXScdDrawLine_Ctrls()
{
	//��ʼ������

	//��ʼ����Ա����
	
}

CXScdDrawLine_Ctrls::~CXScdDrawLine_Ctrls()
{
	
}

void CXScdDrawLine_Ctrls::Pick(const CPoint &point, CExBaseList &oList)
{
	CXScdDrawLine_Vert::Pick(point, oList);
}

void CXScdDrawLine_Ctrls::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag)
{
	CXScdDrawLine_Vert::Draw(pDC, fZoomRatio, ptOffset, dwDrawFlag);
}


void CXScdDrawLine_Ctrls::InitLinePos()
{
	ASSERT ((m_pBeginElement != NULL) && (m_pEndElement != NULL) );

	if (m_pBeginElement == NULL || m_pEndElement == NULL)
	{
		return;
	}

	m_ptBegin.x = m_pBeginElement->m_ptTopLeft.x + m_pBeginElement->m_nWidth / 2;
	m_ptEnd.x   = m_pEndElement->m_ptTopLeft.x + m_pEndElement->m_nWidth / 2;
	
	if (m_pBeginElement->m_ptTopLeft.y > m_pEndElement->m_ptTopLeft.y)
	{
		m_ptBegin.y = m_pBeginElement->m_ptTopLeft.y;
		m_ptEnd.y   = m_pEndElement->m_ptTopLeft.y + m_pEndElement->m_nHeight;
	}
	else if( (m_pBeginElement->m_ptTopLeft.y < m_pEndElement->m_ptTopLeft.y))
	{
		m_ptBegin.y = m_pBeginElement->m_ptTopLeft.y + m_pEndElement->m_nHeight;
		m_ptEnd.y   = m_pEndElement->m_ptTopLeft.y;
	}
	else if( (m_pBeginElement->m_ptTopLeft.y==m_pEndElement->m_ptTopLeft.y)||m_pBeginElement->m_ptTopLeft.y>300)//�����ʼ�ͽ�������������ͬ������һ��ˮƽ����������֮��
	{
		m_ptBegin.y = m_pBeginElement->m_ptTopLeft.y + m_pEndElement->m_nHeight;
		m_ptEnd.y   = m_pEndElement->m_ptTopLeft.y + m_pEndElement->m_nHeight;
	}
	else
	{

	}
}


CBaseObject* CXScdDrawLine_Ctrls::Clone()
{
	CXScdDrawLine_Ctrls *p = new CXScdDrawLine_Ctrls();
	Copy(p);
	return p;
}
