#pragma once

#include "../tmt_test_paras_head.h"
#include "../tmt_common_def.h"
#include "../SearchBase/tmt_search_base.h"
#include "tmt_diff_curr_test.h"
	
typedef struct tmt_elec_railway_diff_paras :public tmt_SearchBase
{
    int		m_nTestType;	//�������ͣ���������Ҫ��ÿ����������д����	0-����������1-�����ƶ���2-�ٶϵ�����3-2��г���ƶ�ϵ����4-����ʱ�䣬5-����
    int		m_nTestMethod;	//����ģʽ 0-�ֶ� 1-�Զ�
    float	m_fVg1;			//��һ���ѹ���ֵ
    float	m_fVg2;			//�ڶ����ѹ���ֵ
    float	m_fIdSetting;	//�������ֵ���������ã�ר��ģ�壩

    //����ֵ
    BOOL	m_bMinAxis;	//����������ʽ 0-����ֵ 1-����ֵ ƽ̨ģ��û�У���Ϊ1
    float	m_fIbase;	//��׼�����趨ֵ

    float	m_fIsd;	//��ٶϵ�����ֵ 1.500In��A		���Լ���IBIAS��������
    float	m_fIcdqd;//����������ż�ֵ 0.500In��A	���Լ���IBIAS��������

    float m_fIp1;//�����ƶ����Թյ�1����
    float m_fIp2;//�����ƶ����Թյ�1����
    float m_fKid1;//���������ƶ�����б��1
    float m_fKid2;//���������ƶ�����б��2
	


    //ͨ�ò���
	float m_fPreTime;		//׼��ʱ��  0.000
    float m_fPreFaultTime;	//����ǰʱ�� 1.000
    float m_fFaultTime;		//����ʱ�� 0.500
    float m_fKpl;			//��ѹ��ƽ��ϵ�� 0.637	���Լ���KPL
    BOOL	m_bCTStarPoint;	//CT����0-����ָ���ѹ�� 1-һ��ָ���ѹ��  ƽ̨ģ�����û�У���Ϊ0
    int		m_nIbiasCal;	//�ƶ�����	0-Ir=(|I1-I2|)/K1��Ir=(|I1+I2|)/K1,1-Ir=(|I1|+|I2|*K2)/K1,2-Ir=max(|I1|,,|I2|)
    //,3-Ir=(|Id-|I1|-|I2||)/K1,4-Ir=|I2|,5-Sqrt(K1*I1*I2*Cos(��)),		1
	int		m_nPhase;		//������ 0-A,1-B,2-C,3-A,B,C	ƽ̨ģ��û�У���Ϊ3 

	int    m_nTranSort;//��ѹ��������ʽ 0-Y/V����ƽ���ѹ��   1-Y/��-11����  2-�����ѹ��   
    int    m_nRWCTconnect;//��ѹ��CT���߷�ʽ    0-���ͽ���   1-Y�ͽ���
	int    m_nKphMode;//ƽ��ϵ�����㷽��   0-������*��ѹ��CT���/��ѹ��CT���    1-��ѹ��CT���/(������*��ѹ��CT���)  

    //�����
    float	m_fIdiff;		//�����
    float	m_fIbias;		//�ƶ�����

    // г������
    int		m_nHarmIndex;	//г���ƶ�����ѡ��0-2ֵ�ֱ��Ӧ2�Ρ�3�κ�5��
    float	m_fCoefHarm2;			//����г���ƶ�ϵ��
    float	m_fCoefHarm3;			//����г���ƶ�ϵ��
    float	m_fCoefHarm5;			//���г���ƶ�ϵ��

    //������
    tmt_BinaryIn  m_binIn[MAX_BINARYIN_COUNT];
    tmt_BinaryIn  m_binInEx[MAX_ExBINARY_COUNT];
	tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];	
    tmt_BinaryOut m_binOutEx[MAX_ExBINARY_COUNT];
    int	m_nBinLogic;			//0-�� 1-��
    int m_nAutoSearch;//�Ƿ��Զ����� (0:�ֶ�����;1:�Զ�����)
	
    char m_pszTestName[32];	//��Ŀ����
public:
    virtual void init()
    {
        tmt_SearchBase::InitSearch();
        m_nTestType = 0;	//Ĭ�ϲ�����������
        m_nTestMethod = 1;
		m_fVg1=57.74f;
		m_fVg2=57.74f;
        m_fIdSetting = 1;

        m_fIp1 = 1.0f;
        m_fIp2 = 2.5f;
        m_fKid1 = 0.7f;
        m_fKid2 = 0.4f;

        m_bMinAxis = TRUE;
        m_fIbase = 5.000f;

        //ͨ�ò���
		m_fPreTime = 1.000;
        m_fPreFaultTime = 1.000;
		m_fFaultTime = 0.500;	
        m_fKpl = 0.637f;

        m_bCTStarPoint = FALSE;
        m_nIbiasCal = 0;
        m_nPhase = 0;

        m_nTranSort = 0;
        m_nRWCTconnect = 0;
        m_nKphMode = 0;

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
		
        memset(m_pszTestName, 0, 32);
	} 

    void CopyOwnDiffParas(tmt_DiffCurrParas *pDiffCurrParas)
    {
        tmt_SearchBase::CopyOwnSearchBase(pDiffCurrParas);

        pDiffCurrParas->m_nTestType = m_nTestType;	//Ĭ�ϲ�����������
        pDiffCurrParas->m_nTestMethod = m_nTestMethod;
		pDiffCurrParas->m_fVg1=m_fVg1;
		pDiffCurrParas->m_fVg2=m_fVg2;
		pDiffCurrParas->m_fIdSetting =m_fIdSetting;

        pDiffCurrParas->m_nKneePoints = 2;
        pDiffCurrParas->m_fIp1 = m_fIp1;
        pDiffCurrParas->m_fIp2 = m_fIp2;
        pDiffCurrParas->m_fIp3 = 3.0f;
        pDiffCurrParas->m_fKid0 = 0.0f;
        pDiffCurrParas->m_fKid1 = m_fKid1;
        pDiffCurrParas->m_fKid2 = m_fKid2;
        pDiffCurrParas->m_fKid3 = 0.4f;

        pDiffCurrParas->m_bMinAxis = m_bMinAxis;
        pDiffCurrParas->m_nInSel = 1;//��׼����ѡ���趨ֵ
        pDiffCurrParas->m_fIbase = m_fIbase;

        //ͨ�ò���
        pDiffCurrParas->m_fPreFaultTime = m_fPreFaultTime;
        pDiffCurrParas->m_fFaultTime = m_fFaultTime;
		pDiffCurrParas->m_nKcal = 1;	
        pDiffCurrParas->m_fKpl = m_fKpl;
        pDiffCurrParas->m_nConnectMode = 0;
        pDiffCurrParas->m_nJXFactor = 0;
        pDiffCurrParas->m_bCTStarPoint = m_bCTStarPoint;
        pDiffCurrParas->m_nIbiasCal = m_nIbiasCal;

        pDiffCurrParas->m_fFactor2 = 1;

		if (m_nIbiasCal == 1)
        {
            pDiffCurrParas->m_fFactor1 = 2;
        }
        else
        {
            pDiffCurrParas->m_fFactor1 = 1;
        }

        pDiffCurrParas->m_fFactor2 = 1.000f;
        pDiffCurrParas->m_nPhase = m_nPhase;

        //�����
        pDiffCurrParas->m_fIdiff = m_fIdiff;
        pDiffCurrParas->m_fIbias = m_fIbias;
		pDiffCurrParas->m_fIsd=m_fIsd;
		pDiffCurrParas->m_fIcdqd=m_fIcdqd;

        // г������
        pDiffCurrParas->m_nHarmIndex = m_nHarmIndex;
        pDiffCurrParas->m_fCoefHarm2 = m_fCoefHarm2;
        pDiffCurrParas->m_fCoefHarm3 = m_fCoefHarm3;
        pDiffCurrParas->m_fCoefHarm5 = m_fCoefHarm5;
        pDiffCurrParas->m_nAutoSearch = m_nAutoSearch;


        pDiffCurrParas->m_nBinLogic = m_nBinLogic;

		for (int i=0;i<MAX_BINARYIN_COUNT;i++)
        {
            pDiffCurrParas->m_binIn[i] = m_binIn[i];
            pDiffCurrParas->m_binOut[i] = m_binOut[i];
        }

        for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
        {
            pDiffCurrParas->m_binInEx[i] = m_binInEx[i];
        }

        for(int i = 0; i < g_nBoutExCount && i < MAX_ExBINARY_COUNT; i++)
        {
            pDiffCurrParas->m_binOutEx[i] = m_binOutEx[i];
        }
    }

}tmt_ElecRailwayDiffParas;

typedef struct tmt_elec_railway_diff_results :public tmt_DiffCurrResults
{
public:
    tmt_elec_railway_diff_results()
    {
    }
    virtual ~tmt_elec_railway_diff_results()
    {
    }

    float	m_fIalphaIe;
    float	m_fIalpha;
    float   m_fIbetaIe;
    float   m_fIbeta;

    virtual void init()
    {
        tmt_DiffCurrResults::init();
        m_fIalphaIe = 0;
        m_fIalpha = 0;
        m_fIbetaIe = 0;
        m_fIbeta = 0;
    }
}tmt_ElecRailwayDiffResults;


typedef struct tmt_elec_railway_diff_thr_test : public TMT_PARAS_HEAD // �������������
{
public:
    tmt_ElecRailwayDiffParas      m_oDiffCurrParas ;
    tmt_ElecRailwayDiffResults   m_oDiffCurrResults;
    int m_nThrType;		//0-����������1-������������

    virtual void init()
    {
        init_head(); //20210918 zhouhj
        strcpy(m_pszMacroID, STT_MACRO_ID_ElecRailwayDiffTest);
        m_nVersion = 0x00010001;
        m_nTestState = 0;

        m_oDiffCurrParas.init();
        m_oDiffCurrResults.init();
        m_nThrType = 0;
    }

	tmt_elec_railway_diff_thr_test()	{init();}
	virtual void clear_result(){	m_oDiffCurrResults.init();	}
	virtual ~tmt_elec_railway_diff_thr_test(){}
}tmt_ElecRailwayDiffThrTest;

typedef struct tmt_elec_railway_diff_rate_test : public tmt_ElecRailwayDiffThrTest // ������ƶ�
{
public:
    int m_nRateType;		//0-������б�ʣ�1��2-�����ƶ�ϵ��һ��3��4-�����ƶ�ϵ������5��6-�����ƶ�ϵ������7��8-�����ƶ�ϵ���ģ�
    virtual void init()
    {
        tmt_ElecRailwayDiffThrTest::init();
        m_nRateType = 0;
        strcpy(m_pszMacroID, STT_MACRO_ID_ElecRailwayDiffRateTest);
    }

	tmt_elec_railway_diff_rate_test()	{init();}
	virtual ~tmt_elec_railway_diff_rate_test(){}
}tmt_ElecRailwayDiffRateTest;

typedef struct tmt_elec_railway_diff_quick_test : public tmt_ElecRailwayDiffThrTest // ��ٶ�
{
public:
    virtual void init()
    {
        tmt_ElecRailwayDiffThrTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_ElecRailwayDiffQuickTest);
    }

	tmt_elec_railway_diff_quick_test()	{init();}
	virtual ~tmt_elec_railway_diff_quick_test(){}
}tmt_ElecRailwayDiffQuickTest;

typedef struct tmt_elec_railway_diff_harm_test : public tmt_ElecRailwayDiffThrTest // г���ƶ�
{
public:
    virtual void init()
    {
        tmt_ElecRailwayDiffThrTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_ElecRailwayDiffHarmTest);
    }

	tmt_elec_railway_diff_harm_test()	{init();}
	virtual ~tmt_elec_railway_diff_harm_test(){}
}tmt_ElecRailwayDiffHarmTest;

typedef struct tmt_elec_railway_diff_act_time_test : public tmt_ElecRailwayDiffThrTest // �����ʱ��
{
public:
    virtual void init()
    {
        tmt_ElecRailwayDiffThrTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_ElecRailwayDiffTimeTest);
    }

	tmt_elec_railway_diff_act_time_test()	{init();}
	virtual ~tmt_elec_railway_diff_act_time_test(){}
}tmt_ElecRailwayDiffActTimeTest;


void stt_init_paras(tmt_ElecRailwayDiffParas *pParas);

void stt_xml_serialize_diff_search_results(tmt_ElecRailwayDiffParas *pParas, tmt_ElecRailwayDiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_thr(tmt_ElecRailwayDiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_thr_elec_railway(tmt_ElecRailwayDiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_rate(tmt_ElecRailwayDiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_rate_elec_railway(tmt_ElecRailwayDiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_quick(tmt_ElecRailwayDiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_quick_elec_railway(tmt_ElecRailwayDiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_harm(tmt_ElecRailwayDiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_harm_elec_railway(tmt_ElecRailwayDiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_acttime(tmt_ElecRailwayDiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_acttime_elec_railway(tmt_ElecRailwayDiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_ElecRailwayDiffThrTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_serialize(tmt_ElecRailwayDiffThrTest *pTests, CSttXmlSerializeBase *pXmlSerialize,BOOL bResultOnly);

void stt_xml_serialize_write_ElecRailwayDiffTest();
