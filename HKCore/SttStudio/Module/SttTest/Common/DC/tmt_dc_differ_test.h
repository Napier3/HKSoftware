#pragma once

#include "../tmt_test_paras_head.h"
#include "../tmt_common_def.h"
#include "../SearchBase/tmt_search_base.h"

#define DCDIFF_INSEL 1       //��׼����ѡ�� 0-�߲���ζ���� 1-�趨ֵ 2-������ζ����
#define DCDIFF_MINAXIS 1     //����������ʽ 0-����ֵ 1-����ֵ
#define DCDIFF_ANGLEMODE 2   //У��ѡ��	0-��У�� 1-����У�� 2-Y��У��
#define DCDIFF_WINDH 0       //��ѹ�����������ʽ 0-Y 1-�� 0
#define DCDIFF_WINDM 0       //��ѹ�����������ʽ 0-Y 1-��
#define DCDIFF_WINDL 0       //��ѹ�����������ʽ 0-Y 1-��
#define DCDIFF_WINDSIDE 0    //��������	0-��-��  1-��-��    2-��-��
#define DCDIFF_CONNECTMODE 0 //��������֮��ǲ�ӵ�����0-11 12�㡢1��--11��
#define DCDIFF_PHASE 3       //������ 0-A,1-B,2-C,3-A,B,C
#define DCDIFF_CTSTARPOINT 0 //CT����0-����ָ���ѹ�� 1-һ��ָ���ѹ��
#define DCDIFF_JXFACTOR 0    //ƽ��ϵ�����㷽��	0-���������������ʽ  1-�������������ʽ

typedef struct tmt_dc_differ_cur_paras : public tmt_SearchBase
{
	int		m_nTestType;	//�������ͣ�0-����������1-�����ƶ���2-����ʱ�䣬3-����
	//����ֵ
	float m_fIStart;//��������
	int m_nKneePoints;//�յ����
	float m_fIp1;     //�յ�1����
	float m_fIp2;     //�յ�2����
	float m_fKRation1; //�����ƶ�ϵ��1
	float m_fKRation2; //�����ƶ�ϵ��2
	float m_fActTime; //����ʱ��
	float m_fKid0;//��������б��

	//ͨ�ò���
	float m_fBeforeTime; //�仯ǰʱ��
	float m_fPreFaultTime;//����ǰʱ��
	float m_fMarginTime;//����ʱ��ԣ��
	float m_fK1;        //ƽ��ϵ��1
	float m_fK2;        //ƽ��ϵ��2
	int m_nCurChannel1; //����1ͨ��
	int m_nCurChannel2; //����2ͨ��
	int m_nSearchMode; //����ģʽ 0,���ַ� 1����������
	int m_nDiffCal;     //�����
	int m_nIbiasCal;    //�ƶ�����
	float m_fFactor1;   //K1
	float m_fFactor2;   //K2
	
	//������
	tmt_BinaryIn  m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryIn  m_binInEx[MAX_ExBINARY_COUNT];
	tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];	
	tmt_BinaryOut m_binOutEx[MAX_ExBINARY_COUNT];
	int	m_nBinLogic;			//0-�� 1-��

	//�������
	char m_pszTestName[EXPR_MAX_COUNT];	//��Ŀ����
	float	m_fIbias;		//�ƶ�����
	float   m_fIdiff;       //�����

public:
	virtual void init()
	{
		m_nTestType = 0;
		m_fIStart = 5.000f;
		m_nKneePoints = 1;
		m_fIp1 = 1.0f;
		m_fIp2 = 2.5f;
		m_fKRation1 = 0.15f;
		m_fKRation2 = 0.12f;
		m_fActTime = 0.0f;

		m_fBeforeTime = 2.000f;
		m_fPreFaultTime = 2.000f;
		m_fMarginTime = 0.2f;
		m_fK1 = 1.000f;
		m_fK2 = 1.000f;
		m_nCurChannel1 = 0;
		m_nCurChannel2 = 0;
		m_nSearchMode = 0;
		m_nDiffCal = 0;
		m_nIbiasCal = 0;
		m_fFactor1 = 2.000f;
		m_fFactor2 = 1.000f;
		m_fKid0 = 0.200f;

		m_fIbias = 1.200f;
		m_fIdiff = 0.600f;

		for (int i = 0; i < MAX_ExBINARY_COUNT; i++)
		{
			m_binIn[i].init();
			m_binOut[i].init();
		}

		for (int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			m_binInEx[i].init();
		}

		for (int i = 0; i < g_nBoutExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			m_binOutEx[i].init();
		}

		memset(m_pszTestName, 0, EXPR_MAX_COUNT);
	}
}tmt_DcDifferCurParas;

typedef struct tmt_dc_differ_results
{
	float	m_fIdiffActValue;	//���������ֵ
	float	m_fIdiffSettingValue;	// ��ǰ�����Ĳ����ֵ
	float	m_fIbiasValue;	//�ƶ�����
	float	m_fIrCoef;		//�ƶ�ϵ��
	float   m_fRateKid; //�����ƶ�ϵ��
	float	m_fTripTime;		//����ʱ��: ��ֵ��Ч
	int		m_nActFlag;			//������־
	float	m_fI1Ie;
	float	m_fI1;
	float	m_fI2Ie;
	float	m_fI2;

public:
	virtual void init()
	{
		m_fIdiffActValue = 0;
		m_fIdiffSettingValue = 0;
		m_fIbiasValue = 0;
		m_fIrCoef = 0;
		m_fRateKid = 0;
		m_nActFlag = 0;
		m_fI1Ie = 0;
		m_fI1 = 0;
		m_fI2Ie = 0;
		m_fI2 = 0;
	}
}tmt_DcDifferCurResults;

typedef struct tmt_dc_differ_cur_test : public TMT_PARAS_HEAD
{
public:
	tmt_DcDifferCurParas m_oDcDifferCurParas;
	tmt_DcDifferCurResults m_oDcDifferCurResults;
	int m_nThrType;		//0-����������1-������������

	virtual void init()
	{
		init_head();
		strcpy(m_pszMacroID, STT_MACRO_ID_DCDifferCurrTest);
		m_nTestState = 0;
		m_oDcDifferCurParas.init();
		m_oDcDifferCurResults.init();
		m_nThrType = 0;
	}

	tmt_dc_differ_cur_test(){init();}
	virtual void clear_result(){m_oDcDifferCurResults.init();}
	virtual ~tmt_dc_differ_cur_test(){}
}tmt_DcDifferCurTest;

typedef struct tmt_dc_differ_cur_rate_test : public tmt_DcDifferCurTest //�����ƶ�ϵ��
{
public:
	int m_nRateType; //0-�����ƶ�ϵ��1 1-�����ƶ�ϵ��2
	virtual void init()
	{
		tmt_DcDifferCurTest::init();
		m_nRateType = 0;
		strcpy(m_pszMacroID, STT_MACRO_ID_DCDifferRateTest);
	}

	tmt_dc_differ_cur_rate_test(){init();}
	virtual ~tmt_dc_differ_cur_rate_test(){}
}tmt_DcDifferCurRateTest;

typedef struct tmt_dc_differ_cur_acttime_test : public tmt_DcDifferCurTest
{
public:
	virtual void init()
	{
		tmt_DcDifferCurTest::init();
		strcpy(m_pszMacroID, STT_MACRO_ID_DCDifferTimeTest);
	}
	tmt_dc_differ_cur_acttime_test(){init();}
	virtual ~tmt_dc_differ_cur_acttime_test(){}
}tmt_DcDifferActTimeTest;

void stt_init_paras(tmt_DcDifferCurParas *pParas);
void stt_init_results(tmt_DcDifferCurResults *pResults);

void stt_xml_serialize_diff_search_results(tmt_DcDifferCurParas *pParas, tmt_DcDifferCurResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_thr(tmt_DcDifferCurParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_thr(tmt_DcDifferCurResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_rate(tmt_DcDifferCurParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_rate(tmt_DcDifferCurResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_acttime(tmt_DcDifferCurParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_acttime(tmt_DcDifferCurResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_DcDifferCurTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_serialize(tmt_DcDifferCurTest *pTests, CSttXmlSerializeBase *pXmlSerialize, BOOL bResultOnly);
void stt_xml_serialize_write_DCDifferTest();