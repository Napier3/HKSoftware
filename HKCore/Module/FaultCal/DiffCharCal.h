
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
	
	float	m_fIsd;	//差动速断电流定值 1.500In或A		用以计算IBIAS，可无视
	float	m_fIcdqd;//差动动作电流门槛值 0.500In或A	用以计算IBIAS，可无视

	int m_nKneePoints;//拐点个数  //比率制动特性拐点数 1-1个拐点 2-两个拐点	0	用以计算IBIAS，可无视
	float m_fIp1;//比率制动特性拐点1电流
	float m_fIp2;//比率制动特性拐点2电流
	float m_fIp3;//比率制动特性拐点3电流
	float m_fKid0;//启动电流斜率
	float m_fKid1;//基波比率制动特性斜率1
	float m_fKid2;//基波比率制动特性斜率2
	float m_fKid3;//基波比率制动特性斜率3

	float m_fHarmCoef;//谐波制动系数

	float m_fXMax;
	float m_fYMax;

	float m_fAxisMaxCoef;  //坐标轴的最大值比例系数
	long m_nSelectSd;//20230206 zhouhj 标记速断是否勾选
	long m_nMinAxis;	//定制整定方式 0-有名值 1-标幺值
	long m_nInsel;//基准电流选择
	long m_nHarmIndex;////谐波制动次数选择，0-2值分别对应2次、3次和5次
	float m_fInSet;//基准电流
	long m_nPointNum[5];//记录每条线上的测试点数量
	float m_fErrorBand[5];//记录误差带
	BOOL m_bFixYMax;//zhouhj 20230616 Y轴最大值是否按固定值设置,线路差动和母线差动因没有速断,需要支持指定该最大值

public:
	CXDrawDatas m_oPoints;

public:
	void Cal();
	void CalHarm();
};

#endif // !defined(__DiffCharCal_h__)
