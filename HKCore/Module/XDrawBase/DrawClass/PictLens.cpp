// PictLens.cpp: implementation of the CPictLens class.
//
//        3--͸��: ����ϵ��־(0--������, 1--ֱ������), �����迹 Z1 (���յ�), 
//				   ����ϵ��־(0--������, 1--ֱ������), �����迹 Z2 (�����), 
//                 ͸���ڽ� Ang (��Z=Z1-Z2���д�����Բ����� Z1,Z2 ���Ž�);
//                 ( ��Z=Z1-Z2 ����͸������ B, �ֱ�Ϊ͸������Բ�ϵ���, 
//                   �д���������Բ�Ľ��㹹��͸������ A,
//                   ���� Ratio = A/B)
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PictLens.h"
#include "OnllyCommFunc.h"	//Ӧ�ò㹫������
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPictLens::CPictLens()
{
	swprintf_s(m_ZoneTag_string,_countof(m_ZoneTag_string),_T("%s"),_T("Z1_LE"));
	m_nPictType=Pict_Lens;
	m_Z1.nAxisFlag=0;		//�������־: 0--������; 1--ֱ������
	m_Z1.Mag_R=0.0f;
	m_Z1.Ang_X=0.0f;
	swprintf_s(m_Z1.Mag_R_string,_countof(m_Z1.Mag_R_string),_T("%s"),_T("0.0"));
	swprintf_s(m_Z1.Ang_X_string,_countof(m_Z1.Ang_X_string),_T("%s"),_T("0.0"));
	m_Z2.nAxisFlag=0;		//�������־: 0--������; 1--ֱ������
	m_Z2.Mag_R=0.0f;
	m_Z2.Ang_X=0.0f;
	swprintf_s(m_Z2.Mag_R_string,_countof(m_Z2.Mag_R_string),_T("%s"),_T("0.0"));
	swprintf_s(m_Z2.Ang_X_string,_countof(m_Z2.Ang_X_string),_T("%s"),_T("0.0"));
	m_Ang=0.0f;
	swprintf_s(m_Ang_string,_countof(m_Ang_string),_T("%s"),_T("0.0"));
	m_Width=0.0f;
	m_Ratio=0.0f;
}

CPictLens::~CPictLens()
{

}

//��Բ: ԭ������, ÿ��λ����Ӧ��������
void CPictLens::Draw(CDC *pDC,CPoint originPos,double pixelsPerUnit_x,double pixelsPerUnit_y)
{
	float theR,theX;
	float theR_Left,theX_Left;
	float theR_Right,theX_Right;
	float theRadius;
	int x,y;
	int r_x,r_y;
	CPoint ptStart,ptEnd;

	//������������Բ�� Z0(ֱ������) �Ͱ뾶 Radius
	my_calcu_Z0(&theR_Left,&theX_Left,&theR_Right,&theX_Right,&theRadius);
	//
	//����Բ�������յ�����
	my_calcu_Z1(&theR,&theX);
	ptStart.x=(int)(originPos.x+theR*pixelsPerUnit_x+0.5f);
	ptStart.y=(int)(originPos.y-theX*pixelsPerUnit_y+0.5f);
	my_calcu_Z2(&theR,&theX);
	ptEnd.x=(int)(originPos.x+theR*pixelsPerUnit_x+0.5f);
	ptEnd.y=(int)(originPos.y-theX*pixelsPerUnit_y+0.5f);
	//
	for(int ii=0;ii<2;ii++)
	{
		if(ii==0)
		{
			theR=theR_Left;
			theX=theX_Left;
		}
		else
		{
			theR=theR_Right;
			theX=theX_Right;
		}
		x=(int)(originPos.x+theR*pixelsPerUnit_x+0.5f);
		y=(int)(originPos.y-theX*pixelsPerUnit_y+0.5f);
		r_x=(int)(theRadius*pixelsPerUnit_x+0.5f);
		r_y=(int)(theRadius*pixelsPerUnit_y+0.5f);
		if(ii==0)
		{
			//Z2 -> Z1
			pDC->Arc(CRect(x-r_x,y-r_y,x+r_x,y+r_y),ptEnd,ptStart);
		}
		else
		{
			//Z1 -> Z2
			pDC->Arc(CRect(x-r_x,y-r_y,x+r_x,y+r_y),ptStart,ptEnd);
		}
	}
}

//�����������(ֱ������)
void CPictLens::my_calcu_Z1(float *Z1_R, float *Z1_X)
{
	if(m_Z1.nAxisFlag==Axis_Polar)
	{
		float theMag,theAng;

		theMag=m_Z1.Mag_R;
		theAng=m_Z1.Ang_X;
		po_to_xy(theMag,theAng,Z1_R,Z1_X);
	}
	else
	{
		*Z1_R=m_Z1.Mag_R;
		*Z1_X=m_Z1.Ang_X;
	}
}

//�����յ�����(ֱ������)
void CPictLens::my_calcu_Z2(float *Z2_R, float *Z2_X)
{
	if(m_Z2.nAxisFlag==Axis_Polar)
	{
		float theMag,theAng;

		theMag=m_Z2.Mag_R;
		theAng=m_Z2.Ang_X;
		po_to_xy(theMag,theAng,Z2_R,Z2_X);
	}
	else
	{
		*Z2_R=m_Z2.Mag_R;
		*Z2_X=m_Z2.Ang_X;
	}
}

//������������Բ�� Z0(ֱ������) �Ͱ뾶 Radius
void CPictLens::my_calcu_Z0(float *Z0_R_Left, float *Z0_X_Left,
							float *Z0_R_Right, float *Z0_X_Right,	
							float *Radius)
{
	float Z1_Mag,Z1_Ang;
	float Z2_Mag,Z2_Ang;
	float Z12_Mag,Z12_Ang;
	float Z0_Mag,Z0_Ang;
	float AngShift;

	if(m_Z1.nAxisFlag==Axis_Polar)
	{
		Z1_Mag=m_Z1.Mag_R;
		Z1_Ang=m_Z1.Ang_X;
	}
	else
	{
		xy_to_po(m_Z1.Mag_R,m_Z1.Ang_X,&Z1_Mag,&Z1_Ang);
	}
	if(m_Z2.nAxisFlag==Axis_Polar)
	{
		Z2_Mag=m_Z2.Mag_R;
		Z2_Ang=m_Z2.Ang_X;
	}
	else
	{
		xy_to_po(m_Z2.Mag_R,m_Z2.Ang_X,&Z2_Mag,&Z2_Ang);
	}
	//Z=Z1-Z2 �����迹Բ�ϵ�һ����, ͨ��ƫת�Ǽ����ֱ��
	comp_Sub(Z1_Mag,Z1_Ang,Z2_Mag,Z2_Ang,&Z12_Mag,&Z12_Ang);
	AngShift=m_Ang-90.0f;	//ƫ�ƽ� = ͸���ڽ� -90
	Z12_Mag/=(float)cos(AngShift*PI/180.0);
	//������Բ��
	comp_Add(Z2_Mag,Z2_Ang,(Z12_Mag/2.0f),(Z12_Ang-AngShift),&Z0_Mag,&Z0_Ang);
	po_to_xy(Z0_Mag,Z0_Ang,Z0_R_Right,Z0_X_Right);
	//������Բ��
	comp_Add(Z2_Mag,Z2_Ang,(Z12_Mag/2.0f),(Z12_Ang+AngShift),&Z0_Mag,&Z0_Ang);
	po_to_xy(Z0_Mag,Z0_Ang,Z0_R_Left,Z0_X_Left);
	//�뾶
	*Radius=Z12_Mag/2.0f;
}

void CPictLens::Serialize(CArchive& ar)
{
	//��ǰ�汾��
	CString strVersion=_T("1.00");		//�汾��
	CString strText;
	
	//ִ�л���Ĵ��л�
	CPict::Serialize(ar);
	//
	if (ar.IsStoring())
	{
		//����: ���ݰ汾�Ų�ͬ
		strText=strVersion;
		ar<<strText;
		if(strVersion==_T("1.00"))
		{
			//͸��: �����迹 Z1
			strText.Format(_T("%d"),m_Z1.nAxisFlag);
			ar<<strText;
			strText.Format(_T("%f"),m_Z1.Mag_R);
			ar<<strText;
			strText.Format(_T("%f"),m_Z1.Ang_X);
			ar<<strText;
			//͸��: �����迹 Z2
			strText.Format(_T("%d"),m_Z2.nAxisFlag);
			ar<<strText;
			strText.Format(_T("%f"),m_Z2.Mag_R);
			ar<<strText;
			strText.Format(_T("%f"),m_Z2.Ang_X);
			ar<<strText;
			//͸���ڽ�
			strText.Format(_T("%f"),m_Ang);
			ar<<strText;
			//͸�����
			strText.Format(_T("%f"),m_Width);
			ar<<strText;
			//�����
			strText.Format(_T("%f"),m_Ratio);
			ar<<strText;
		}
	}
	else
	{
		//��ȡ: ���ݰ汾�Ų�ͬ
		ar>>strText;
		strVersion=strText;
		if(strVersion==_T("1.00"))
		{
			//͸��: �����迹 Z1
			ar>>strText;
			m_Z1.nAxisFlag=(int)StringToData(strText);
			ar>>strText;
			m_Z1.Mag_R=StringToData(strText);
			ar>>strText;
			m_Z1.Ang_X=StringToData(strText);
			//͸��: �����迹 Z2
			ar>>strText;
			m_Z2.nAxisFlag=(int)StringToData(strText);
			ar>>strText;
			m_Z2.Mag_R=StringToData(strText);
			ar>>strText;
			m_Z2.Ang_X=StringToData(strText);
			//͸���ڽ�
			ar>>strText;
			m_Ang=StringToData(strText);
			//͸�����
			ar>>strText;
			m_Width=StringToData(strText);
			//�����
			ar>>strText;
			m_Ratio=StringToData(strText);
		}
	}
}

void CPictLens::Serialize_Model(CArchive& ar)
{
	//��ǰ�汾��
	CString strVersion=_T("1.00");		//�汾��
	CString strText;
	
	if (ar.IsStoring())
	{
		//����: ���ݰ汾�Ų�ͬ
		strText=strVersion;
		ar<<strText;
		if(strVersion==_T("1.00"))
		{
			//͸��: �����迹 Z1 ��ģ��(���㹫ʽ)
			strText.Format(_T("%d"),m_Z1.nAxisFlag);
			ar<<strText;
			strText.Format(_T("%s"),m_Z1.Mag_R_string);
			ar<<strText;
			strText.Format(_T("%s"),m_Z1.Ang_X_string);
			ar<<strText;
			//͸��: �����迹 Z2 ��ģ��(���㹫ʽ)
			strText.Format(_T("%d"),m_Z2.nAxisFlag);
			ar<<strText;
			strText.Format(_T("%s"),m_Z2.Mag_R_string);
			ar<<strText;
			strText.Format(_T("%s"),m_Z2.Ang_X_string);
			ar<<strText;
			//͸���ڽ�: ���㹫ʽ
			strText.Format(_T("%s"),m_Ang_string);
			ar<<strText;
		}
	}
	else
	{
		//��ȡ: ���ݰ汾�Ų�ͬ
		ar>>strText;
		strVersion=strText;
		if(strVersion==_T("1.00"))
		{
			//͸��: �����迹 Z1 ��ģ��(���㹫ʽ)
			ar>>strText;
			m_Z1.nAxisFlag=(int)StringToData(strText);
			ar>>strText;
			swprintf_s(m_Z1.Mag_R_string,_countof(m_Z1.Mag_R_string),_T("%s"),strText);
			ar>>strText;
			swprintf_s(m_Z1.Ang_X_string,_countof(m_Z1.Ang_X_string),_T("%s"),strText);
			//͸��: �����迹 Z2 ��ģ��(���㹫ʽ)
			ar>>strText;
			m_Z2.nAxisFlag=(int)StringToData(strText);
			ar>>strText;
			swprintf_s(m_Z2.Mag_R_string,_countof(m_Z2.Mag_R_string),_T("%s"),strText);
			ar>>strText;
			swprintf_s(m_Z2.Ang_X_string,_countof(m_Z2.Ang_X_string),_T("%s"),strText);
			//͸���ڽ�: ���㹫ʽ
			ar>>strText;
			swprintf_s(m_Ang_string,_countof(m_Ang_string),_T("%s"),strText);
		}
	}
}
