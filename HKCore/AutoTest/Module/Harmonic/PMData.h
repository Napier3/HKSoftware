//PMData.h

#if !defined PMDATA_H_
#define PMDATA_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CHData.h"
#include "../TestControl.h"

#define PNUM_CH 16//11

struct stPMOutData
{
	double fFreq;	//Ƶ��
	double fAnlg[PNUM_CH];	//��ֵ
	double fPhase[PNUM_CH];//��λ

	unsigned char nFD[PNUM_CH];	//��λ���Զ�����=0��1~n��������ʼ�ĵ�λ

	unsigned char nU4Mode;	//U4ģʽ���仯���Ӱ�쵽���ͨ��ת��

	//����ʱ�ĸ��������
	double fFPoint;	//Ƶ������
	double fALP[PNUM_CH];	//��Ư����
};

struct stPMAdjData
{
};

class CPMData
{
// Construction
public:
	CPMData();
	~CPMData();

public:

	static CTestControl* m_pTestControl;

	////////////////////////	���	/////////////////////////
	CCHData	m_PMData[PNUM_CH];

	unsigned char nU4Mode;	//U4ģʽ���仯���Ӱ�쵽���ͨ��ת��
	
	//����ʱ�ĸ��������
	double fFPoint;	//Ƶ������
	
	
	//�����
	stPMOutData	m_stPMOutData;
	stPMOutData	m_stPMOutDataOld;

	BOOL	m_bVarChanged;

	void InitOutData();
	BOOL IsOutDataChanged();
	void UpdateOutDataOld();
	
	//�´����������������
	unsigned char m_nAutoSetFD[PNUM_CH];
	unsigned char m_nFDSet[PNUM_CH];
	double m_fFDMax[PNUM_CH];
	
	void CheckFDChg();

	////////////////////////	����	/////////////////////////
	unsigned int m_iSampleMode;

	////////////////////////	����	/////////////////////////
public:
	double m_fTmp[5];
	unsigned char m_nCurTmpZone[5];


	/////////////////////////////////////////////////////
public:
	//���
//	CCHData	m_PMData[PNUM_CH];

	double m_fFreqMax;				//Ƶ�����ֵ
	double m_fFreqMin;				//Ƶ����Сֵ
	double m_fPhaseMax;				//��λ���ֵ
	double m_fPhaseMin;				//��λ��Сֵ

	unsigned char m_nHarmMax;		//г���������ֵ

	long  m_lCmpstF;  //Ƶ���������� = 41841;
	
	//������������
//	unsigned int m_iSampleMode;     //ֱ��������ʽ
	unsigned int m_iSampleMode2;     //ֱ�������ֵ�
	unsigned int m_iU4Mode;    //����������
	unsigned int m_iInputStatus;    //����
	unsigned int m_iAlarmStatus;    //����
	unsigned int m_iOutStatus;      //����
	unsigned int m_iDSPState;
	
	//�¶Ȳ����������й�
	unsigned char m_nRom[6][9];    //�¶ȴ�����ID��5�� 
//	double	m_fTmp[5];    //5���¶ȴ����������¶�ֵ
	
	//����������
	unsigned char m_nState_S[4];   //������״̬
	double m_ftime_S[5];  //��������תʱ�̺����ʱ��

	/////////////////////////////////////////////////////
public:
	void InitData();
	unsigned char m_nVarChanged;

	//�ж�������ݱ仯
	unsigned char IsOutDataChanged2();
	
	//��������
	void UpdateOutDataOld2();
	
	//����������Ĵ���
	//��λ�仯
	void UpdateFDChg();
};

#endif