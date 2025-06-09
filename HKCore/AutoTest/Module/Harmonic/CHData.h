//CHData.h
#if !defined CHDATA_H_
#define CHDATA_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct stCHData
{
	//��������
	double m_fAnlg;					//��ֵ
	double m_fFreq;					//Ƶ��
	double m_fPhase;				//��λ
	
	unsigned char m_nDC;			//ֱ����1��������0��
	
	//��ֵ�ֵ�
	unsigned char m_nAutoSetFD;		//�Զ�������1����̶���λ��0��
	unsigned char m_nFD;			//��λ
	unsigned char m_nFDNum;			//��λ����
	double m_fFDMax[8];				//��λ��ֵ���ֵ������󵵿�ʼ�����һλΪ��
	
	//��������
	double m_fCmpstLP;				//�����Ư�����ڵ������......
	double m_fCmpst[8][3];			//������Ư����ֵ����λ��������	//v1.03-070313
	double m_fCmpstT[15][8][3];     //��ͬ�¶��µ���Ư����ֵ����λ��������	//v1.03-070313
	//��ֻ�����ڽ������ͨ����
	double m_fCmpstH[50][8][2];		//��ͬг���µķ�ֵ����λ��������	//v1.03-070313

	//г������
	double m_fAnlgH[50];			//г����ֵ
	double m_fPhaseH[50];			//г����λ
};

class CCHData	//��ͨ���������
{
// Construction
public:
	CCHData();
	~CCHData();

	/////////////////////////////////////////////////////
public:
	stCHData m_stCHData;
	stCHData m_stCHDataOld;

	/////////////////////////////////////////////////////
public:
	//������ʼ��
	void InitOutData();

	//�ж�������ݱ仯
	unsigned char IsOutDataChanged();

	//��������
	void UpdateOutDataOld();

	//����������Ĵ���
	//��λ�仯
	void UpdateFDChg();
};

#endif

