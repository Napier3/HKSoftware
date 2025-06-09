// PictLens.h: interface for the CPictLens class.
//
//        3--͸��: ����ϵ��־(0--������, 1--ֱ������), �����迹 Z1 (���յ�), 
//				   ����ϵ��־(0--������, 1--ֱ������), �����迹 Z2 (�����), 
//                 ͸���ڽ� Ang (��Z=Z1-Z2���д�����Բ����� Z1,Z2 ���Ž�);
//                 ( ��Z=Z1-Z2 ����͸������ B, �ֱ�Ϊ͸������Բ�ϵ���, 
//                   �д���������Բ�Ľ��㹹��͸������ A,
//                   ���� Ratio = A/B)
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
	//Z=Z1-Z2 ����͸������ B, ͨ��͸���ڽǿɵõ�ֱ��λ��(Բ�ĺͰ뾶)
	struct struct_ZPointSet	m_Z1;		//�����迹 Z1, �迹��ֵ
	struct struct_ZPointSet m_Z2;		//�����迹 Z2, Ĭ��Ϊ (0,0)
	//���� 3 ������m_Ang, m_Width, m_Ratio���Ի���ת��
	float m_Ang;					//͸���ڽ�(10--170��)
	float m_Width;
	float m_Ratio;
	//��ģ��ʹ��
	WCHAR m_Ang_string[MAX_STRING_LENGTH];
	//
	//���������յ�����(ֱ������)
	void my_calcu_Z1(float *Z1_R, float *Z1_X);
	void my_calcu_Z2(float *Z2_R, float *Z2_X);
	//������������Բ�� Z0(ֱ������) �Ͱ뾶 Radius
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
