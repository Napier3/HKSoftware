
#if !defined(__DiffCharCal_h__)
#define __DiffCharCal_h__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../XDrawBase/XDrawDataDef.h"

class CDiffCharCal  
{
public:
	CDiffCharCal();
	virtual ~CDiffCharCal();
	
	float	m_fIsd;	//��ٶϵ�����ֵ 1.500In��A		���Լ���IBIAS��������
	float	m_fIcdqd;//����������ż�ֵ 0.500In��A	���Լ���IBIAS��������

	int m_nKneePoints;//�յ����  //�����ƶ����Թյ��� 1-1���յ� 2-�����յ�	0	���Լ���IBIAS��������
	float m_fIp1;//�����ƶ����Թյ�1����
	float m_fIp2;//�����ƶ����Թյ�2����
	float m_fIp3;//�����ƶ����Թյ�3����
	float m_fKid0;//��������б��
	float m_fKid1;//���������ƶ�����б��1
	float m_fKid2;//���������ƶ�����б��2
	float m_fKid3;//���������ƶ�����б��3

	float m_fHarmCoef;//г���ƶ�ϵ��

	float m_fXMax;
	float m_fYMax;

	float m_fAxisMaxCoef;  //����������ֵ����ϵ��
	long m_nSelectSd;//20230206 zhouhj ����ٶ��Ƿ�ѡ
	long m_nMinAxis;	//����������ʽ 0-����ֵ 1-����ֵ
	long m_nInsel;//��׼����ѡ��
	long m_nHarmIndex;////г���ƶ�����ѡ��0-2ֵ�ֱ��Ӧ2�Ρ�3�κ�5��
	float m_fInSet;//��׼����
	long m_nPointNum[5];//��¼ÿ�����ϵĲ��Ե�����
	float m_fErrorBand[5];//��¼����
	BOOL m_bFixYMax;//zhouhj 20230616 Y�����ֵ�Ƿ񰴹̶�ֵ����,��·���ĸ�߲��û���ٶ�,��Ҫ֧��ָ�������ֵ

public:
	CXDrawDatas m_oPoints;

public:
	void Cal();
	void CalHarm();
};

#endif // !defined(__DiffCharCal_h__)
