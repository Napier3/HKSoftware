#pragma once

#include "../tmt_test_paras_head.h"
#include "../tmt_common_def.h"
#include "../SearchBase/tmt_search_base.h"
	
typedef struct tmt_diff_curr_paras :public tmt_SearchBase
{
	int		m_nTestType;	//�������ͣ���������Ҫ��ÿ����������д����	0-����������1-�����ƶ���2-�ٶϵ�����3-2��г���ƶ�ϵ����4-����ʱ�䣬5-����
	int		m_nTestMethod;	//����ģʽ 0-�ֶ� 1-�Զ�
//	float	m_fReso;		//���Ծ���
// 	float	m_fDiffStart;	//�����ʼֵ
// 	float	m_fDiffEnd;		//�������ֵ
	float	m_fVg1;			//��һ���ѹ��̬���ֵ
	float	m_fVg2;			//�ڶ����ѹ��̬���ֵ
	float  m_fVg1_fault;  //��һ���ѹ����̬���ֵ(������)
	float  m_fVg2_fault;  //�ڶ����ѹ����̬���ֵ(������)
	float	m_fIdSetting;	//�������ֵ���������ã�ר��ģ�壩

	//����ֵ
	BOOL	m_bMinAxis;	//����������ʽ 0-����ֵ 1-����ֵ ƽ̨ģ��û�У���Ϊ1
	int		m_nInSel;	//��׼����ѡ�� 0-�߲���ζ���� 1-�趨ֵ 2-������ζ����	ƽ̨ģ��û�У���Ϊ0 ���Լ���INOM
// 	float	m_fInom;	//��׼������������5.000A  ���Լ���INOM ��ƽ̨�Ĺ���ǰ����
// 	float	m_fVnom;	//���ѹ
// 	float	m_fFnom;	//�Ƶ��
	float	m_fIbase;	//��׼�����趨ֵ

	float	m_fIsd;	//��ٶϵ�����ֵ 1.500In��A		���Լ���IBIAS��������
	float	m_fIcdqd;//����������ż�ֵ 0.500In��A	���Լ���IBIAS��������

	int m_nKneePoints;//�յ����  //�����ƶ����Թյ��� 1-1���յ� 2-�����յ�	0	���Լ���IBIAS��������
	float m_fIp1;//�����ƶ����Թյ�1����
	float m_fIp2;//�����ƶ����Թյ�1����
	float m_fIp3;//�����ƶ����Թյ�1����
	float m_fKid0;//��������б��
	float m_fKid1;//���������ƶ�����б��1
	float m_fKid2;//���������ƶ�����б��2
	float m_fKid3;//���������ƶ�����б��3
	
	//��������б�� 0.000	���Լ������������е�Id��������
	//���������ƶ�����б��1 0.500	���Լ���IBIAS��������
	//���������ƶ�����б��2 0.700	���Լ���IBIAS��������
	//�ٶϵ���б�� 0.000	���Լ������������е�Id��������

	//ͨ�ò���
    float m_fPreTime;		//׼��ʱ��  0.000
	float m_fPreFaultTime;	//����ǰʱ�� 1.000
	float m_fFaultTime;		//����ʱ�� 0.500
	float m_fAfterFaultTime;	//���Ϻ����ʱ��

	int	  m_nKcal;			//����ƽ��ϵ�� 0-�Զ����� 1-�ֶ����㲢���� 0	���Լ���KPH��KPL��CONNECTFACTOR ��ƽ��ϵ�����÷�ʽ
	float m_fSN;			//��ѹ������� 31.500MVA	���Լ���INOM INOMh INOMm INOMl
	float m_fUh;			//��ѹ����ѹ 110.000kV	���Լ���KPH��KPL��INOM��INOMh
	float m_fUm;			//��ѹ����ѹ 38.5kV	���Լ���KPH��KPL��INOM��INOMm
	float m_fUl;			//��ѹ����ѹ 10.500kV	���Լ���KPH��KPL��INOM��INOMl
	float m_fKph;			//��ѹ��ƽ��ϵ�� 1.000	���Լ���KPH
	float m_fKpm;			//��ѹ��ƽ��ϵ�� 0.936	���Լ���KPH��KPL
	float m_fKpl;			//��ѹ��ƽ��ϵ�� 0.637	���Լ���KPL
	int		m_nWindH;		//��ѹ�����������ʽ 0-Y 1-�� 0	���Լ���KPH��KPL
	int		m_nWindM;		//��ѹ�����������ʽ 0-Y 1-�� 0	���Լ���KPH��KPL
	int		m_nWindL;		//��ѹ�����������ʽ 0-Y 1-�� 1 ���Լ���KPL
	int		m_nAngleMode;	//У��ѡ��	0-��У�� 1-����У�� 2-Y��У��  2	���Լ���KPH��KPL AngleMode
	int		m_nWindSide;	//��������	0-��-��  1-��-��    2-��-��    2	���Լ���KPH��KPL
	int		m_nConnectMode;	//��������֮��ǲ�ӵ�����0-11 12�㡢1��--11��  11 ��ƽ̨�ı�ѹ���������
	int		m_nJXFactor;	//ƽ��ϵ�����㷽��	0-���������������ʽ  1-�������������ʽ 0	���Լ���KPH��KPL��CONNECTFACTOR
	//	int		m_nKpCalMode;	//����ϵ��Kp���㷽�� ����ļ��㷽������AngleMode��JXFactor��WindSide��WindH��WindM��WindL�����ģ��ʴ�ֵ��Ч 
	//0-���ݶ��ѹ Un �� CT ��ȹ�������ѹ�� 1-���ݶ���� In' ��������ѹ�� 2-��ôֵ����   //   �ܺ�� 20200425  �˲���δ�õ�
	float	m_fInh,m_fInm,m_fInl;	//���е�ѹ������
	float	m_fCTh,m_fCTm,m_fCTl;	//���е�ѹ��CT���
	// 	int		m_nSearchMode;	//��������		0-���ַ� 1-�����ƽ� 0 ƽ̨ģ����û�У�Ӧ��װʱ����
	BOOL	m_bCTStarPoint;	//CT����0-����ָ���ѹ�� 1-һ��ָ���ѹ��  ƽ̨ģ�����û�У���Ϊ0
	int		m_nIbiasCal;	//�ƶ�����	0-Ir=(|I1-I2|)/K1��Ir=(|I1+I2|)/K1,1-Ir=(|I1|+|I2|*K2)/K1,2-Ir=max(|I1|,,|I2|)
	//,3-Ir=(|Id-|I1|-|I2||)/K1,4-Ir=|I2|,5-Sqrt(K1*I1*I2*Cos(��)),		1
	float	m_fFactor1;		//K1				2
	float	m_fFactor2;		//K2				1
	int		m_nPhase;		//������ 0-A,1-B,2-C,3-A,B,C	ƽ̨ģ��û�У���Ϊ3 
	float	m_fVzAmp;			//Uz				57.740V

	//�����
	float	m_fIdiff;		//�����
	float	m_fIbias;		//�ƶ�����

	// г������
	int		m_nHarmIndex;	//г���ƶ�����ѡ��0-2ֵ�ֱ��Ӧ2�Ρ�3�κ�5��
	float	m_fCoefHarm2;			//����г���ƶ�ϵ��
	float	m_fCoefHarm3;			//����г���ƶ�ϵ��
	float	m_fCoefHarm5;			//���г���ƶ�ϵ��

	//��λ�����õ���
	float m_fCTPh;			//��ѹ��CTһ��ֵ 300A	���Լ���KPH��KPL��INOM��INOMh
	float m_fCTPm;			//��ѹ��CTһ��ֵ 800A	���Լ���KPH��KPL��INOM��INOMm
	float m_fCTPl;			//��ѹ��CTһ��ֵ 2000A	���Լ���KPH��KPL��INOM��INOMl
	float m_fCTSh;			//��ѹ��CT����ֵ 5A	���Լ���KPH��KPL��INOM��INOMh
	float m_fCTSm;			//��ѹ��CT����ֵ 5A	���Լ���KPH��KPL��INOM��INOMm
	float m_fCTSl;			//��ѹ��CT����ֵ 5A	���Լ���KPH��KPL��INOM��INOMl

	//������
	tmt_BinaryIn  m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryIn  m_binInEx[MAX_ExBINARY_COUNT];
	tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];	
	tmt_BinaryOut m_binOutEx[MAX_ExBINARY_COUNT];
	int	m_nBinLogic;			//0-�� 1-��
	int m_nAutoSearch;//�Ƿ��Զ����� (0:�ֶ�����;1:�Զ�����)
	
	// 2022.5.12 caoxc
	char m_pszTestName[32];	//��Ŀ����

    //xuzhantao240301
    float m_fPreFaultIp;//����ǰ����
    tmt_channel m_uiVOL[2][6];	//(����ǰ+����)*����ѹ��6
    tmt_channel m_uiCUR[2][6];

    //Xuzhantao Pnv������
    int		m_nIdiffCal;	//Ir�ƶ�����  0:Ir=|I1'-I2'|/K, 1:Ir=Max(|I1'|,|I2'|)*K, 2:Ir=|I2'|, 3:Ir=|Id-|I1'|-|I2'||,
                            //          4:Ir=(|I1'|+|I2'|)/K, 5:Ir=|Imax'-��Ii'|/K, Ii'��Imax', 6:Ir=��(��|I1'��I2'| * cos��)
    int     m_nHarmPos;     //г��ʩ�Ӳ�  0��I1�࣬ 1��I2��
    int     m_nY0CorrectMode;//�����ڲ�����������ʽ  0���� 1����
public:
	virtual void init()
	{
		tmt_SearchBase::InitSearch();
		m_nTestType = 0;	//Ĭ�ϲ�����������
		m_nTestMethod = 1;
// 		m_fDiffStart = 0.700f;
// 		m_fDiffEnd = 1.300f;	
// 		m_fReso = 0.01f;
		m_fVg1=57.74f;
		m_fVg2=57.74f;
		m_fVg1_fault = 57.74;
		m_fVg2_fault = 57.74;
		m_fIdSetting = 1;

		m_nKneePoints = 1;
		m_fIp1 = 1.0f;
		m_fIp2 = 2.5f;
		m_fIp3 = 3.0f;
		m_fKid0 = 0.0f;
		m_fKid1 = 0.7f;
		m_fKid2 = 0.4f;
		m_fKid3 = 0.4f;

		m_bMinAxis = TRUE;
		m_nInSel = 0;
// 		m_fInom = 0.000f;
// 		m_fVnom = 57.74f;
// 		m_fFnom = 50.000f;
		m_fIbase = 5.000f;

		//ͨ�ò���
		m_fPreTime = 5.000f;
		m_fPreFaultTime = 1.000;
		m_fFaultTime = 0.500;
		m_nKcal = 0;
		m_fSN = 31.500;
		m_fUh = 110.000;
		m_fUm = 38.5;
		m_fUl = 10.500;	
		m_fKph = 1.000;
		m_fKpm = 0.936f;	
		m_fKpl = 0.637f;
		m_nWindH = 0;
		m_nWindM = 0;
		m_nWindL = 1;
		m_nAngleMode = 0;
		m_nWindSide = 0;
		m_nConnectMode = 11;
		m_nJXFactor = 0;
		m_bCTStarPoint = FALSE;
		m_nIbiasCal = 0;
		m_fFactor1 = 2.000f;
		m_fFactor2 = 1.000f;
		m_nPhase = 0;
// 		m_fDistinguish = 0.010f;
		m_fVzAmp = 57.740f;

		m_fInh = 1.0;
		m_fInm = 1.0;
		m_fInl = 1.0f;

		//�����
		m_fIdiff = 0.600f;
		m_fIbias = 1.200f;
		m_fIsd=5;
		m_fIcdqd=0.5;

		// г������
		m_nHarmIndex = 0;
		m_fCoefHarm2 = 0.15f;
		m_fCoefHarm3 = 0.12f;
		m_fCoefHarm5 = 0.11f;
		m_nAutoSearch = 1;

		//��λ������
		m_fCTPh = 300;	
		m_fCTPm = 800;
		m_fCTPl = 2000;	
		m_fCTSh = 5.000;
		m_fCTSm = 5.000;
		m_fCTSl = 5.000;

		m_nBinLogic = 0;

		for (int i=0;i<MAX_BINARYIN_COUNT;i++)
		{
			m_binIn[i].init();
			m_binOut[i].init();
		}

        for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			m_binInEx[i].init();
		}

        for(int i = 0; i < g_nBoutExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			m_binOutEx[i].init();
		}

		//2022.5.24 caoxc ��ʼ����Ŀ����
		memset(m_pszTestName, 0, 32);

        m_fPreFaultIp = 0;
        float fAngle[3]={0,-120,120};
        for(int i=0; i<2; i++)
        {
            for(int j=0; j<6; j++)
            {
                m_uiVOL[i][j].Harm[1].fAmp = 0;
                m_uiVOL[i][j].Harm[1].fAngle = fAngle[j%3];
                m_uiVOL[i][j].Harm[1].fFreq = 50;
            }
            for(int j=0; j<6; j++)
            {
                m_uiCUR[i][j].Harm[1].fAmp = 0;
                m_uiCUR[i][j].Harm[1].fAngle = fAngle[j%3];
                m_uiCUR[i][j].Harm[1].fFreq = 50;
            }
        }
	} 

}tmt_DiffCurrParas;

typedef struct tmt_diff_curr_results
{
	float	m_fIdiffActValue;	//���������ֵ
	float	m_fIdiffSettingValue;	// ��ǰ�����Ĳ����ֵ
	float	m_fIbiasValue;	//�ƶ�����
	float	m_fIrCoef;		//�ƶ�ϵ��
	BOOL	m_bLastPoint;	//�Ƿ����һ��������
	int		m_nZDRatioIndex;	//�����ƶ����1 1-2 2 2-2 3 3-2 ֵ��1 2 3 4 5 6 7 8
	int		m_rltBin[MAX_BINARYIN_COUNT];	//����״̬

	float	m_fTripTime;		//����ʱ��: ��ֵ��Ч
	int		m_nActFlag;			//������־

	float	m_fI1Ie;
	float	m_fI1;
	float	m_fI2Ie;
	float	m_fI2;
	float	m_fIRbase[6];
	float	m_fIharm[6];

	//��λ����
	float   m_fRateKid; //�����ƶ�ϵ��

public:
	virtual void init()
	{
		m_fIdiffActValue = 0;	//�����
		m_fIdiffSettingValue = 0;
		m_fIbiasValue = 0;	//�ƶ�����
		m_fIrCoef = 0;		//�ƶ�ϵ��
		m_bLastPoint = 0;	//�Ƿ����һ��������
		m_nZDRatioIndex = 0;	//�����ƶ����1 1-2 2 2-2 3 3-2 ֵ��1 2 3 4 5 6 7 8
		memset(m_rltBin, 0, MAX_BINARYIN_COUNT*sizeof(int));
		m_fTripTime = 0;			//����ʱ��: ��ֵ��Ч
		m_nActFlag = 0;

		m_fI1 = 0;
		m_fI2 = 0;
		m_fI1Ie = 0;
		m_fI2Ie = 0;

		m_fRateKid = 0;

		for (int i=0;i<6;i++)
		{
			m_fIRbase[0] = m_fIharm[0] = 0;
		}
	} 

}tmt_DiffCurrResults;


typedef struct tmt_diff_curr_thr_test : public TMT_PARAS_HEAD // �������������
{
public:
	tmt_DiffCurrParas      m_oDiffCurrParas ;
	tmt_DiffCurrResults   m_oDiffCurrResults;
	int m_nThrType;		//0-����������1-������������

	virtual void init()
	{
		init_head(); //20210918 zhouhj
		strcpy(m_pszMacroID, STT_MACRO_ID_PsuDiffTCurrTest);
		m_nVersion = 0x00010001;
		m_nTestState = 0;

		m_oDiffCurrParas.init();
		m_oDiffCurrResults.init();
		m_nThrType = 0;
	}

	tmt_diff_curr_thr_test()	{init();}
	virtual void clear_result(){	m_oDiffCurrResults.init();	}
	virtual ~tmt_diff_curr_thr_test(){}
}tmt_DiffCurrThrTest;

typedef struct tmt_diff_curr_rate_test : public tmt_DiffCurrThrTest // ������ƶ�
{
public:
	int m_nRateType;		//0-������б�ʣ�1��2-�����ƶ�ϵ��һ��3��4-�����ƶ�ϵ������5��6-�����ƶ�ϵ������7��8-�����ƶ�ϵ���ģ�
	virtual void init()
	{
		tmt_DiffCurrThrTest::init();
		m_nRateType = 0;
		strcpy(m_pszMacroID, STT_MACRO_ID_PsuDiffRateTest);
	}

	tmt_diff_curr_rate_test()	{init();}
	virtual ~tmt_diff_curr_rate_test(){}
}tmt_DiffCurrRateTest;

typedef struct tmt_diff_curr_quick_test : public tmt_DiffCurrThrTest // ��ٶ�
{
public:
	virtual void init()
	{
		tmt_DiffCurrThrTest::init();
		strcpy(m_pszMacroID, STT_MACRO_ID_PsuDiffQuickTest);
	}

	tmt_diff_curr_quick_test()	{init();}
	virtual ~tmt_diff_curr_quick_test(){}
}tmt_DiffCurrQuickTest;

typedef struct tmt_diff_curr_harm_test : public tmt_DiffCurrThrTest // г���ƶ�
{
public:
	virtual void init()
	{
		tmt_DiffCurrThrTest::init();
		strcpy(m_pszMacroID, STT_MACRO_ID_PsuDiffHarmTest);
	}

	tmt_diff_curr_harm_test()	{init();}
	virtual ~tmt_diff_curr_harm_test(){}
}tmt_DiffCurrHarmTest;

typedef struct tmt_diff_act_time_test : public tmt_DiffCurrThrTest // �����ʱ��
{
public:
	virtual void init()
	{
		tmt_DiffCurrThrTest::init();
		strcpy(m_pszMacroID, STT_MACRO_ID_PsuDiffTimeTest);
	}

	tmt_diff_act_time_test()	{init();}
	virtual ~tmt_diff_act_time_test(){}
}tmt_DiffActTimeTest;

//Xuzhantao20240227
typedef struct tmt_diff_6i_rate_pnv_test : public tmt_DiffCurrThrTest // �(6I)-�����ƶ�����(PNV)
{
public:
    virtual void init()
    {
        init_head(); //20210918 zhouhj
        tmt_DiffCurrThrTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_Diff6IRateRestrainSearchTest);

    }
    tmt_diff_6i_rate_pnv_test()	{init();}
    virtual ~tmt_diff_6i_rate_pnv_test(){}
}tmt_Diff6IRatePnvTest;

//Xuzhantao20240401
typedef struct tmt_diff_6i_harm_pnv_test : public tmt_DiffCurrHarmTest // �(6I)-г���ƶ�����(PNV)
{
public:
    virtual void init()
    {
        init_head(); //20210918 zhouhj
        tmt_DiffCurrHarmTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_Diff6IHarmRestrainSearchTest);

    }
    tmt_diff_6i_harm_pnv_test()	{init();}
    virtual ~tmt_diff_6i_harm_pnv_test(){}
}tmt_Diff6IHarmPnvTest;

void stt_init_paras(tmt_DiffCurrParas *pParas);
void stt_init_results(tmt_DiffCurrResults *pResults);

void stt_xml_serialize_diff_search_results(tmt_DiffCurrParas *pParas, tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_thr(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_thr(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_rate(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_rate(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_quick(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_quick(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_harm(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_harm(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_acttime(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_acttime(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_6i_rate_pnv(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_6i_rate_pnv(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_6i_harm_pnv(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_6i_harm_pnv(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_DiffCurrThrTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_serialize(tmt_DiffCurrThrTest *pTests, CSttXmlSerializeBase *pXmlSerialize,BOOL bResultOnly);
