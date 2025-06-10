#pragma once

#include "../tmt_test_paras_head.h"
#include "../tmt_common_def.h"


typedef struct tmt_swing_paras 
{
	//���ϲ���
	float	m_fPowerAngleBegin;	//����ʼֵ
	float	m_fPowerAngleEnd;	//������ֵ
	float	m_fCycle;			//������
	int		m_nSwingCount;		//�𵴴���
	float	m_fRate;			//em/en
	int		m_nTripPoint;		//��բ�����
	int		m_nTripSpeedUp;		//�����źŽӵ�
	int		m_nTripSpeedDown;	//�����źŽӵ�
//	float	m_fFreq;			//Ƶ��
	BOOL	m_bReciprocating;	//�Ƿ�������
	int		m_nAccelerate;		//���ٻ���� 0-���� 1-����
	BOOL	m_bDzdt;			//�迹�Ƿ�仯
	float	m_fDzdt;			//dz/dt

	BOOL	m_bTransFault;		//�Ƿ�ת���Թ���
	int		m_nFaultType;		//��������
	float	m_fImpedance;		//��·�迹
	float	m_fSCurrent;		//��·����
	float	m_fFaultTime;		//���Ϸ���ʱ��
	int		m_nK0CalMode;		//���򲹳�ϵ�����㷽ʽ
	float	m_fK0Amp;			//|���򲹳�����ϵ��Ko|��Re(Ko) m_fRMRL
	float	m_fK0Angle;			//������λ����ϵ��Phi(Ko)��Im(Ko) m_fXMXL

	//ͨ�ò���
	float	m_fPreFaultTime;	//��ǰʱ��
	int		m_nCTPoint;			//CT������ 0 ָ��ĸ�ߣ�1ָ����·
	float	m_fImpSys;			//ϵͳ���迹
	float	m_fImpSysPh;		//PHI(zs)
	float	m_fImpTf;			//��ѹ���迹
	float	m_fImpTfPh;			//PHI
	float	m_fImpTs;			//�������̬�迹
	float	m_fActTimeSet;		//����ʱ�䶨ֵ

	//������
// 	tmt_BinaryIn  m_binIn[MAX_BINARYIN_COUNT];
// 	tmt_BinaryIn  m_binInEx[MAX_ExBINARY_COUNT];
	tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];	//0-�ǹ���̬���� 1-����̬����
    tmt_BinaryOut m_binOutEx[MAX_ExBINARY_COUNT];//0-�ǹ���̬���� 1-����̬����

    //GoosePub
    tmt_GoosePub m_oGoosePub[MAX_MODULES_GOOSEPUB_COUNT];
public:
	virtual void init()
	{
		m_fPowerAngleBegin = 0;
		m_fPowerAngleEnd = 200;
		m_fCycle = 3;
		m_nSwingCount = 5;
		m_fRate = 1.25f;
		m_nTripPoint = 0;
		m_nTripSpeedUp = 2;
		m_nTripSpeedDown = 3;
		m_bReciprocating=0;
		m_nAccelerate=1;
		m_bDzdt=0;
		m_fDzdt = 4.4452f;
//		m_fFreq = 50;

		m_bTransFault=0;
		m_nFaultType = 0;
		m_fImpedance = 1.0f;
		m_fSCurrent = 5.0f;
		m_fFaultTime = 0.5f;
		m_nK0CalMode = 0;
		m_fK0Amp = 0;
		m_fK0Angle =0;

		m_fPreFaultTime = 0;
		m_nCTPoint = 1;
		m_fImpSys = 25;
		m_fImpSysPh = 90;
		m_fImpTf = 15;
		m_fImpTfPh = 78;
		m_fImpTs = 1;
		m_fActTimeSet = 1;

		for (int i=0;i<MAX_BINARYIN_COUNT;i++)
		{
//			m_binIn[i].init();
			m_binOut[i].init();
		}

        for(int i = 0; i < g_nBoutExCount && i < MAX_ExBINARY_COUNT; i++)
		{
//			m_binInEx[i].init();
			m_binOutEx[i].init();
		}

        for(int nIndex=0;nIndex<MAX_MODULES_GOOSEPUB_COUNT;nIndex++)
            m_oGoosePub[nIndex].init();
	} 

}tmt_SwingParas;

typedef struct tmt_swing_results
{
	float m_fTripTime;
	float m_fSpeedUp;
	float m_fSpeedDown;
	long m_nAct;

public:
	virtual void init()
	{
		m_fTripTime = 0.0f;
		m_fSpeedUp = 0.0f;
		m_fSpeedDown = 0.0f;
		m_nAct = 0;
	} 

}tmt_SwingResults;


typedef struct tmt_swing_test : public TMT_PARAS_HEAD
{
public:
	tmt_SwingParas      m_oSwingParas ;
	tmt_SwingResults   m_oSwingResults;


	void init()
	{
		init_head(); //20210918 zhouhj
		strcpy(m_pszMacroID, STT_MACRO_ID_PsuSwing);
		m_nVersion = 0x00010001;
		m_nTestState = 0;

		m_oSwingParas.init();
		m_oSwingResults.init();
	}

	tmt_swing_test()	{init();}
	virtual void clear_result(){	m_oSwingResults.init();	}
	virtual ~tmt_swing_test(){}
}tmt_SwingTest;

void stt_init_paras(tmt_SwingParas *pParas);
void stt_init_results(tmt_SwingResults *pResults);

void stt_xml_serialize(tmt_SwingParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_SwingResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_SwingTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
