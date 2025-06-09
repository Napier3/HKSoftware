// PictLens.cpp: implementation of the CPictLens class.
//
//        3--透镜: 坐标系标志(0--极坐标, 1--直角坐标), 正向阻抗 Z1 (弦终点), 
//				   坐标系标志(0--极坐标, 1--直角坐标), 反向阻抗 Z2 (弦起点), 
//                 透镜内角 Ang (弦Z=Z1-Z2的中垂线与圆交点对 Z1,Z2 的张角);
//                 ( 弦Z=Z1-Z2 构成透镜长轴 B, 分别为透镜两个圆上的弦, 
//                   中垂线与两个圆的交点构成透镜短轴 A,
//                   比率 Ratio = A/B)
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PictLens.h"
#include "OnllyCommFunc.h"	//应用层公共函数
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
	m_Z1.nAxisFlag=0;		//坐标轴标志: 0--极坐标; 1--直角坐标
	m_Z1.Mag_R=0.0f;
	m_Z1.Ang_X=0.0f;
	swprintf_s(m_Z1.Mag_R_string,_countof(m_Z1.Mag_R_string),_T("%s"),_T("0.0"));
	swprintf_s(m_Z1.Ang_X_string,_countof(m_Z1.Ang_X_string),_T("%s"),_T("0.0"));
	m_Z2.nAxisFlag=0;		//坐标轴标志: 0--极坐标; 1--直角坐标
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

//画圆: 原点坐标, 每单位长对应的象素数
void CPictLens::Draw(CDC *pDC,CPoint originPos,double pixelsPerUnit_x,double pixelsPerUnit_y)
{
	float theR,theX;
	float theR_Left,theX_Left;
	float theR_Right,theX_Right;
	float theRadius;
	int x,y;
	int r_x,r_y;
	CPoint ptStart,ptEnd;

	//计算左右两个圆心 Z0(直角坐标) 和半径 Radius
	my_calcu_Z0(&theR_Left,&theX_Left,&theR_Right,&theX_Right,&theRadius);
	//
	//计算圆弧起点和终点坐标
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

//计算起点坐标(直角坐标)
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

//计算终点坐标(直角坐标)
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

//计算左右两个圆心 Z0(直角坐标) 和半径 Radius
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
	//Z=Z1-Z2 构成阻抗圆上的一条弦, 通过偏转角计算出直径
	comp_Sub(Z1_Mag,Z1_Ang,Z2_Mag,Z2_Ang,&Z12_Mag,&Z12_Ang);
	AngShift=m_Ang-90.0f;	//偏移角 = 透镜内角 -90
	Z12_Mag/=(float)cos(AngShift*PI/180.0);
	//计算右圆心
	comp_Add(Z2_Mag,Z2_Ang,(Z12_Mag/2.0f),(Z12_Ang-AngShift),&Z0_Mag,&Z0_Ang);
	po_to_xy(Z0_Mag,Z0_Ang,Z0_R_Right,Z0_X_Right);
	//计算左圆心
	comp_Add(Z2_Mag,Z2_Ang,(Z12_Mag/2.0f),(Z12_Ang+AngShift),&Z0_Mag,&Z0_Ang);
	po_to_xy(Z0_Mag,Z0_Ang,Z0_R_Left,Z0_X_Left);
	//半径
	*Radius=Z12_Mag/2.0f;
}

void CPictLens::Serialize(CArchive& ar)
{
	//当前版本号
	CString strVersion=_T("1.00");		//版本号
	CString strText;
	
	//执行基类的串行化
	CPict::Serialize(ar);
	//
	if (ar.IsStoring())
	{
		//保存: 根据版本号不同
		strText=strVersion;
		ar<<strText;
		if(strVersion==_T("1.00"))
		{
			//透镜: 正向阻抗 Z1
			strText.Format(_T("%d"),m_Z1.nAxisFlag);
			ar<<strText;
			strText.Format(_T("%f"),m_Z1.Mag_R);
			ar<<strText;
			strText.Format(_T("%f"),m_Z1.Ang_X);
			ar<<strText;
			//透镜: 反向阻抗 Z2
			strText.Format(_T("%d"),m_Z2.nAxisFlag);
			ar<<strText;
			strText.Format(_T("%f"),m_Z2.Mag_R);
			ar<<strText;
			strText.Format(_T("%f"),m_Z2.Ang_X);
			ar<<strText;
			//透镜内角
			strText.Format(_T("%f"),m_Ang);
			ar<<strText;
			//透镜宽度
			strText.Format(_T("%f"),m_Width);
			ar<<strText;
			//轴比率
			strText.Format(_T("%f"),m_Ratio);
			ar<<strText;
		}
	}
	else
	{
		//读取: 根据版本号不同
		ar>>strText;
		strVersion=strText;
		if(strVersion==_T("1.00"))
		{
			//透镜: 正向阻抗 Z1
			ar>>strText;
			m_Z1.nAxisFlag=(int)StringToData(strText);
			ar>>strText;
			m_Z1.Mag_R=StringToData(strText);
			ar>>strText;
			m_Z1.Ang_X=StringToData(strText);
			//透镜: 反向阻抗 Z2
			ar>>strText;
			m_Z2.nAxisFlag=(int)StringToData(strText);
			ar>>strText;
			m_Z2.Mag_R=StringToData(strText);
			ar>>strText;
			m_Z2.Ang_X=StringToData(strText);
			//透镜内角
			ar>>strText;
			m_Ang=StringToData(strText);
			//透镜宽度
			ar>>strText;
			m_Width=StringToData(strText);
			//轴比率
			ar>>strText;
			m_Ratio=StringToData(strText);
		}
	}
}

void CPictLens::Serialize_Model(CArchive& ar)
{
	//当前版本号
	CString strVersion=_T("1.00");		//版本号
	CString strText;
	
	if (ar.IsStoring())
	{
		//保存: 根据版本号不同
		strText=strVersion;
		ar<<strText;
		if(strVersion==_T("1.00"))
		{
			//透镜: 正向阻抗 Z1 的模板(计算公式)
			strText.Format(_T("%d"),m_Z1.nAxisFlag);
			ar<<strText;
			strText.Format(_T("%s"),m_Z1.Mag_R_string);
			ar<<strText;
			strText.Format(_T("%s"),m_Z1.Ang_X_string);
			ar<<strText;
			//透镜: 反向阻抗 Z2 的模板(计算公式)
			strText.Format(_T("%d"),m_Z2.nAxisFlag);
			ar<<strText;
			strText.Format(_T("%s"),m_Z2.Mag_R_string);
			ar<<strText;
			strText.Format(_T("%s"),m_Z2.Ang_X_string);
			ar<<strText;
			//透镜内角: 计算公式
			strText.Format(_T("%s"),m_Ang_string);
			ar<<strText;
		}
	}
	else
	{
		//读取: 根据版本号不同
		ar>>strText;
		strVersion=strText;
		if(strVersion==_T("1.00"))
		{
			//透镜: 正向阻抗 Z1 的模板(计算公式)
			ar>>strText;
			m_Z1.nAxisFlag=(int)StringToData(strText);
			ar>>strText;
			swprintf_s(m_Z1.Mag_R_string,_countof(m_Z1.Mag_R_string),_T("%s"),strText);
			ar>>strText;
			swprintf_s(m_Z1.Ang_X_string,_countof(m_Z1.Ang_X_string),_T("%s"),strText);
			//透镜: 反向阻抗 Z2 的模板(计算公式)
			ar>>strText;
			m_Z2.nAxisFlag=(int)StringToData(strText);
			ar>>strText;
			swprintf_s(m_Z2.Mag_R_string,_countof(m_Z2.Mag_R_string),_T("%s"),strText);
			ar>>strText;
			swprintf_s(m_Z2.Ang_X_string,_countof(m_Z2.Ang_X_string),_T("%s"),strText);
			//透镜内角: 计算公式
			ar>>strText;
			swprintf_s(m_Ang_string,_countof(m_Ang_string),_T("%s"),strText);
		}
	}
}
