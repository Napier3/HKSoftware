#pragma once

#include "../tmt_test_paras_head.h"
#include "../tmt_common_def.h"

#define  Stt_Syn_Test_Type_VoltageBoder                        0
#define  Stt_Syn_Test_Type_FreqBoder                           1
#define  Stt_Syn_Test_Type_AutoAdj                             2
#define  Stt_Syn_Test_Type_AdjVolCycle                         3
#define  Stt_Syn_Test_Type_AdjFreqCycle                        4
#define  Stt_Syn_Test_Type_LeadAngle                           5


#define  Stt_Syn_Test_Vol_Def_Type_Ua_Ub                       0
#define  Stt_Syn_Test_Vol_Def_Type_Ua_Ubc                      1
#define  Stt_Syn_Test_Vol_Def_Type_Uz_Uabc                     2
#define  Stt_Syn_Test_Vol_Def_Type_Uabc1_Uabc2                 3


#define  Stt_Syn_Test_Ref_Vol_Def_Ua                           0
#define  Stt_Syn_Test_Ref_Vol_Def_Ub                           1
#define  Stt_Syn_Test_Ref_Vol_Def_Uc                           2
#define  Stt_Syn_Test_Ref_Vol_Def_Uab                          3
#define  Stt_Syn_Test_Ref_Vol_Def_Ubc                          4
#define  Stt_Syn_Test_Ref_Vol_Def_Uca                          5

#define  Stt_Syn_Test_TConnMode_Y_Y12                          0
#define  Stt_Syn_Test_TConnMode_Y_D11                          1
#define  Stt_Syn_Test_TConnMode_Y_D1                           2

#define  Stt_Syn_Test_Bout_Type_NO                             0 // ��
#define  Stt_Syn_Test_Bout_Type_Pulse                          1//����
#define  Stt_Syn_Test_Bout_Type_Continue                       2//����

enum WingAngs
{
    WingAng_12,
    WingAng_1,
    WingAng_2,
    WingAng_3,
    WingAng_4,
    WingAng_5,
    WingAng_6,
    WingAng_7,
    WingAng_8,
    WingAng_9,
    WingAng_10,
    WingAng_11,
};

typedef struct tmt_syn_paras 
{
public:
	//������Ŀ���: ��ö��Tmt_Enum_Syn_TestType
	int m_nTestType;	//
	//ϵͳ���ѹ Vs
	float m_fVs_Mag;	//��ֵ, �Ƕ�, Ƶ��
//	float m_fVs_Ang;
	float m_fVs_Fre;
	//�������ѹ Vg
	float m_fVg_Std;//��������ѹ
	float m_fVg_Mag;	//��ֵ, �Ƕ�, Ƶ��
//	float m_fVg_Ang;
	float m_fVg_Fre;

	int m_nVolDefType;//��ѹ����
	int m_nRefVolType;//�ο���ѹ����
	int m_nTransConnMode;//��ѹ�����߷�ʽ
    int m_nWindAngs;//:��������֮��ǲ�ӵ�����=0-12,"12��","1��","2��","3��","4��","5��","6��","7��","8��","9��","10��","11��"
    float m_fPhaseDiff;//������λ��
	int m_nBoutType;//����4����

	//���Ʋ���
	float m_fVs_AngShift;	//ϵͳ��Ӧת��
	float m_fResetTime;	//ͬ��װ�ø���ʱ��
	float m_fSureTime;		//������ȷ��ʱ��

	float m_fDvStep;//�������ѹ�仯����
	float m_fDfStep;//������Ƶ�ʱ仯����

	//�Զ�����������Ч
	float m_fdVg_dt;		//��ѹ����: ������
	float m_fdFg_dt;		//Ƶ�ʻ���: ������

	float m_fMaxSynTime;//���ͬ��ʱ��
	float m_fBoutKeepTime;//����4����ʱ��

	//����ֵ
	float m_fLAngle;
	float m_fLTime;
	float m_fdVzd;
	float m_fdFzd;
	float m_fUt;//��ѹ����
	float m_fFt;//��Ƶ����


	//������
    int m_binIn_Syn;//ͬ���ź�
    int m_binIn_IncV;//��ѹ�ź�
    int m_binIn_IncF;//��Ƶ�ź�
    int m_binIn_DecV;//��ѹ�ź�
    int m_binIn_DecF;//��Ƶ�ź�

    int m_binOut[8]; //��ֵ 0-�Ͽ� 1-�պ�


    //SttDevice������
    tmt_channel m_uiVOL[6];
    float m_fDrvStepV;
    float m_fDrvStepF;
    float m_fVoltMax;
    float m_fVoltMin;
    float m_fFreMax;
    float m_fFreMin;

public:
	virtual void init()
	{
		m_fLAngle = 0.5f;
		m_fLTime = 0.1f;
		m_fdVzd = 2.0f;
		m_fdFzd = 0.2f;
		m_fUt = 6.0f;
		m_fFt = 8.0f;

		m_nTestType = Stt_Syn_Test_Type_VoltageBoder;
		m_fVs_Mag=100.0f;
		m_fVg_Std = 100.0f;
//		m_fVs_Ang=0.0f;
		m_fVs_Fre=50.0f;
		//�������ѹ Vg
		m_fVg_Mag=90.0f;
//		m_fVg_Ang=0.0f;
		m_fVg_Fre=49.9f;

		m_nVolDefType = Stt_Syn_Test_Vol_Def_Type_Ua_Ub;
		m_nRefVolType = Stt_Syn_Test_Ref_Vol_Def_Ua;
		m_nTransConnMode = Stt_Syn_Test_TConnMode_Y_Y12;
		m_nBoutType = Stt_Syn_Test_Bout_Type_NO;
		m_fMaxSynTime = 400.0f;
		m_fBoutKeepTime = 10.0f;
		m_fDvStep = 0.2f;
		m_fDfStep = 0.02f;

		//���Ʋ���
		m_fVs_AngShift=0.0f;	//ϵͳ��Ӧת��
		m_fResetTime=2.0f;		//ͬ��װ�ø���ʱ��
		m_fSureTime=0.01f;		//������ȷ��ʱ��
		//�Զ�����������Ч
		m_fdVg_dt=0.1f;		//��ѹ����: ������, V/s
		m_fdFg_dt=0.1f;		//Ƶ�ʻ���: ������, Hz/s

        m_binIn_Syn = 0;//ͬ���ź�,����A
        m_binIn_IncV = 4;//��ѹ�ź�,����E
        m_binIn_IncF = 5;//��Ƶ�ź�,����F
        m_binIn_DecV = 6;//��ѹ�ź�,����G
        m_binIn_DecF = 7;//��Ƶ�ź�,����H

        for (int i=0;i<8;i++)
		{
            m_binOut[i] = 0;
		}

        for(int i=0; i<6; i++)
        {
            m_uiVOL[i].Harm[0].fAmp = 0;
            m_uiVOL[i].Harm[1].fAmp = 0;

            m_uiVOL[i].Harm[1].fAngle = 0;
            m_uiVOL[i].Harm[1].fFreq = 0;

            for (int nRampIndex = 0;nRampIndex < 3;nRampIndex++)
            {
                m_uiVOL[i].Ramp[nRampIndex].init();
            }
        }

        m_fDrvStepV = m_fDrvStepF = 0;
        m_fVoltMax = 0;
        m_fVoltMin = 0;
        m_fFreMax = 0;
        m_fFreMin = 0;
        m_nWindAngs = WingAng_12;
        m_fPhaseDiff = 0.0;
    }

}tmt_SynParas;

typedef struct tmt_syn_paras_ex :public tmt_SynParas
{
public:
	char m_pszVg_Mag[PARAS_RSLT_EXPR_LEN];//�������ѹ
	char m_pszVg_Freq[PARAS_RSLT_EXPR_LEN];//������Ƶ��
	char m_pszDvStep[PARAS_RSLT_EXPR_LEN];//�������ѹ�仯����
	char m_pszDfStep[PARAS_RSLT_EXPR_LEN];//������Ƶ�ʱ仯����
	char m_pszdVg_dt[PARAS_RSLT_EXPR_LEN];//DvDt
	char m_pszdFg_dt[PARAS_RSLT_EXPR_LEN];//DvDt

	virtual void init()
	{
		tmt_SynParas::init();
		memset(m_pszVg_Mag,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszVg_Freq,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszDvStep,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszDfStep,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszdVg_dt,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszdFg_dt,0,PARAS_RSLT_EXPR_LEN);
	} 
}tmt_SynParasEx;

typedef struct tmt_syn_results
{
	float m_fVolBordValue; //��ѹ�߽�ֵ
	float m_fFreqBordValue; //Ƶ�ʱ߽�ֵ
	float m_fVolDelt;//ѹ��
	float m_fFreqDelt;//Ƶ��
	float m_fLeaderAngle; //��ǰ��
	float m_fLeaderTime; //��ǰʱ��
	float m_fUAdjWidth;//��ѹ����
	float m_fUAdjTime; //��ѹ����
	float m_fFAdjWidth; //��Ƶ����
	float m_fFAdjTime; //��Ƶ����
	long m_nAct;

public:
	virtual void init()
	{
		m_fVolBordValue = 0.0f;
		m_fFreqBordValue = 0.0f;

		m_fVolDelt = 0.0f;
		m_fFreqDelt = 0.0f;

		m_fLeaderAngle = 0.0f;
		m_fLeaderTime = 0.0f;

		m_fUAdjWidth = 0.0f;
		m_fUAdjTime = 0.0f;
		m_fFAdjWidth = 0.0f;
		m_fFAdjTime = 0.0f;
		m_nAct = 0;
	} 

}tmt_SynResults;


typedef struct tmt_syn_act_vol_test : public TMT_PARAS_HEAD
{
public:
	tmt_SynParasEx      m_oSynParas ;
	tmt_SynResults   m_oSynResults;


	void init()
	{
		init_head(); //20210918 zhouhj
		strcpy(m_pszMacroID, STT_MACRO_ID_SynActVoltageTest);
		m_nVersion = 0x00010001;
		m_nTestState = 0;

		m_oSynParas.init();
		m_oSynResults.init();
	}

	tmt_syn_act_vol_test()	{init();}
	virtual void clear_result(){	m_oSynResults.init();	}
	virtual ~tmt_syn_act_vol_test(){}
}tmt_SynActVolTest;

typedef struct tmt_syn_act_freq_test : public tmt_SynActVolTest
{
public:
	virtual void init()
	{
		tmt_SynActVolTest::init();
		strcpy(m_pszMacroID, STT_MACRO_ID_SynActFreqTest);
	}

	tmt_syn_act_freq_test(){	init();}
	virtual ~tmt_syn_act_freq_test(){}
}tmt_SynActFreqTest;

typedef struct tmt_syn_lead_ang_test : public tmt_SynActVolTest
{
public:
	virtual void init()
	{
		tmt_SynActVolTest::init();
		strcpy(m_pszMacroID, STT_MACRO_ID_SynLeadAngTest);
	}

	tmt_syn_lead_ang_test(){	init();}
	virtual ~tmt_syn_lead_ang_test(){}
}tmt_SynLeadAngTest;

typedef struct tmt_syn_auto_adj_test : public tmt_SynActVolTest
{
public:
	virtual void init()
	{
		tmt_SynActVolTest::init();
		strcpy(m_pszMacroID, STT_MACRO_ID_SynAutoAdjTest);
	}

	tmt_syn_auto_adj_test(){	init();}
	virtual ~tmt_syn_auto_adj_test(){}
}tmt_SynAutoAdjTest;

typedef struct tmt_syn_adj_vol_test : public tmt_SynActVolTest
{
public:
	virtual void init()
	{
		tmt_SynActVolTest::init();
		strcpy(m_pszMacroID, STT_MACRO_ID_SynAdjVolTest);
	}

	tmt_syn_adj_vol_test(){	init();}
	virtual ~tmt_syn_adj_vol_test(){}
}tmt_SynAdjVolTest;

typedef struct tmt_syn_adj_freq_test : public tmt_SynActVolTest
{
public:
	virtual void init()
	{
		tmt_SynActVolTest::init();
		strcpy(m_pszMacroID, STT_MACRO_ID_SynAdjFreqTest);
	}

	tmt_syn_adj_freq_test(){	init();}
	virtual ~tmt_syn_adj_freq_test(){}
}tmt_SynAdjFreqTest;


void stt_init_paras(tmt_SynParas *pParas);
void stt_init_results(tmt_SynResults *pResults);

void stt_xml_serialize_ActVol(tmt_SynParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_ActVolEx(tmt_SynParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_ActVol(tmt_SynResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_ActFreq(tmt_SynParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_ActFreqEx(tmt_SynParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_ActFreq(tmt_SynResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_LeadAng(tmt_SynParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_LeadAngEx(tmt_SynParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_LeadAng(tmt_SynResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_AutoAdj(tmt_SynParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_AutoAdjEx(tmt_SynParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_AutoAdj(tmt_SynResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_AdjVolCycle(tmt_SynParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_AdjVolCycleEx(tmt_SynParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_AdjVolCycle(tmt_SynResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_AdjFreqCycle(tmt_SynParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_AdjFreqCycleEx(tmt_SynParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_AdjFreqCycle(tmt_SynResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_SynActVolTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
