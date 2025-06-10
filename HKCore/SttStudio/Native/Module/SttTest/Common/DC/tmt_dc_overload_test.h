#pragma once

#include "../tmt_test_paras_head.h"
#include "../tmt_common_def.h"


#define DC_OVERLOAD_TESTNAME_LEN	64

typedef struct tmt_dc_overload_paras 
{
	float m_fNormaltime;//��̬ʱ��
	float m_fFaultMarginTime;//����ʱ��ԣ��
	float m_fPreFaultVol;//����ǰ��ѹ
	float m_fPreFaultCur;//����ǰ����


	float m_fTime;//�ȹ�����ʱ�䳣��
	float m_fBaseCur;//�ȹ����ɻ�������
	float m_fBaseActionSet;//�ȹ����ɶ�����ֵ
	long m_nFaultCurChannel;//���Ϲ����ɵ���ͨ��
	double m_fFaultCur;//���Ϲ����ɵ���
	double m_fFaultSettingTime;//���϶���ʱ�䶨ֵ


	float m_fStartCur;//�����仯ʼֵ
	float m_fEndCur;//�����仯��ֵ
	float m_fStepCur;//�����仯����


	//������
	tmt_BinaryIn  m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryIn  m_binInEx[MAX_ExBINARY_COUNT];
	tmt_BinaryOut m_binOut[2][MAX_BINARYOUT_COUNT];	//0-�ǹ���̬���� 1-����̬����
	tmt_BinaryOut m_binOutEx[2][MAX_ExBINARY_COUNT];//0-�ǹ���̬���� 1-����̬����
	int		m_nBinLogic;			//0-�� 1-��
	
	char m_pszTestName[DC_OVERLOAD_TESTNAME_LEN];

public:
	virtual void init()
	{
		m_fNormaltime = 5.0f;
		m_fFaultMarginTime = 0.20f;
		m_fPreFaultVol = 0;
		m_fPreFaultCur = 0;
		m_fTime = 1.00f;
		m_fBaseCur =1.00f;
		m_fBaseActionSet =1.00f ;
		m_nFaultCurChannel=DC_CURRENT_COMMON_FAULT_TYPE_I1_1;
		m_fFaultCur = 0;
		m_fFaultSettingTime = 0;
		m_fStartCur = 3.00f;
		m_fEndCur = 20.00f;
		m_fStepCur = 1.00f;

		m_nBinLogic = 0;

		for (int i=0;i<MAX_BINARYIN_COUNT;i++)
		{
			m_binIn[i].init();
			for(int j=0;j<2;j++)
			{
				m_binOut[j][i].init();
			}
		}

		for (int i=0;i<g_nBinExCount;i++)
		{
			m_binInEx[i].init();			
		}

		for (int i=0;i<g_nBoutExCount;i++)
		{
			for(int j=0;j<2;j++)
			{
				m_binOutEx[j][i].init();
			}
		}

		memset(m_pszTestName, 0, DC_OVERLOAD_TESTNAME_LEN);
	} 
}tmt_DC_OverLoadParas;


typedef struct tmt_dc_overload_paras_ex :public tmt_DC_OverLoadParas
{
public:
	char m_pszTimeCoef[PARAS_RSLT_EXPR_LEN];//�ȹ�����ʱ�䳣��
	char m_pszCur[PARAS_RSLT_EXPR_LEN];//�ȹ����ɻ�������
	char m_pszActionSet[PARAS_RSLT_EXPR_LEN];//�ȹ����ɶ�����ֵ

	virtual void init()
	{
		tmt_DC_OverLoadParas::init();
		memset(m_pszActionSet,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszTimeCoef,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszCur,0,PARAS_RSLT_EXPR_LEN);

	} 
}tmt_DC_OverLoadParasEx;

typedef struct tmt_dc_overload_results
{
	float m_fTripTime;
	long m_nAct;

public:
	virtual void init()
	{
		m_fTripTime = 0.0f;
		m_nAct = 0;
	} 

}tmt_DC_OverLoadTestResults;

typedef struct tmt_dc_overload_test : public TMT_PARAS_HEAD
{
public:
	tmt_DC_OverLoadParasEx   m_oOverLoadParas ;
	tmt_DC_OverLoadTestResults m_oOverLoadTestResults;
	double m_fTsetCal;

	virtual void init()
	{
		init_head(); 
		strcpy(m_pszMacroID, STT_MACRO_ID_DCOverLoadTest);
		m_nVersion = 0x00010001;
		m_nTestState = 0;
		m_fTsetCal = 0.0f;
		m_oOverLoadParas.init();
		m_oOverLoadTestResults.init();
	}

	tmt_dc_overload_test()	{init();}
	virtual ~tmt_dc_overload_test(){}
}tmt_DC_OverLoadTest;


void stt_init_paras(tmt_DC_OverLoadParas *pParas);
void stt_init_paras_ex(tmt_DC_OverLoadParasEx *pParas);
void stt_init_results(tmt_DC_OverLoadTestResults *pResults);

void stt_xml_serialize(tmt_DC_OverLoadParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_ex(tmt_DC_OverLoadParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_DC_OverLoadTestResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_DC_OverLoadTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
