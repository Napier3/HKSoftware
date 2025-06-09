// PictLens.h: interface for the CPictLens class.
//
//        3--透镜: 坐标系标志(0--极坐标, 1--直角坐标), 正向阻抗 Z1 (弦终点), 
//				   坐标系标志(0--极坐标, 1--直角坐标), 反向阻抗 Z2 (弦起点), 
//                 透镜内角 Ang (弦Z=Z1-Z2的中垂线与圆交点对 Z1,Z2 的张角);
//                 ( 弦Z=Z1-Z2 构成透镜长轴 B, 分别为透镜两个圆上的弦, 
//                   中垂线与两个圆的交点构成透镜短轴 A,
//                   比率 Ratio = A/B)
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PICTLENS_H__691AAB9A_736B_49F6_9EDE_0B8A074F45C4__INCLUDED_)
#define AFX_PICTLENS_H__691AAB9A_736B_49F6_9EDE_0B8A074F45C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Pict.h"

class CPictLens : public CPict  
{
public:
	//Z=Z1-Z2 构成透镜长轴 B, 通过透镜内角可得到直径位置(圆心和半径)
	struct struct_ZPointSet	m_Z1;		//正向阻抗 Z1, 阻抗定值
	struct struct_ZPointSet m_Z2;		//反向阻抗 Z2, 默认为 (0,0)
	//以下 3 个参数m_Ang, m_Width, m_Ratio可以互相转换
	float m_Ang;					//透镜内角(10--170度)
	float m_Width;
	float m_Ratio;
	//供模板使用
	WCHAR m_Ang_string[MAX_STRING_LENGTH];
	//
	//计算起点和终点坐标(直角坐标)
	void my_calcu_Z1(float *Z1_R, float *Z1_X);
	void my_calcu_Z2(float *Z2_R, float *Z2_X);
	//计算左右两个圆心 Z0(直角坐标) 和半径 Radius
	void my_calcu_Z0(float *Z0_R_Left, float *Z0_X_Left,
					float *Z0_R_Right, float *Z0_X_Right,	
					float *Radius);

public:
	CPictLens();
	virtual ~CPictLens();

public:
	virtual void Draw(CDC *pDC,CPoint originPos,double pixelsPerUnit_x,double pixelsPerUnit_y);
	virtual void Serialize(CArchive& ar);
	virtual void Serialize_Model(CArchive& ar);
};

#endif // !defined(AFX_PICTLENS_H__691AAB9A_736B_49F6_9EDE_0B8A074F45C4__INCLUDED_)
