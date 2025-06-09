#pragma once

#include "../Impedance/tmt_impedance_test.h"
#include "../tmt_test_paras_head.h"

#define TMT_DCUNBALANCEE_TESTNAME_LEN	  128

typedef struct tmt_dc_unbalance_paras
{
public:
	long m_nCurrent1Select;		//����1ͨ��ѡ��
	long m_nCurrent2Select;		//����2ͨ��ѡ��
	float m_fRate;				//����
	float m_fPreFaultTime;		//����ǰʱ��
	float m_fMarginTime;        //����ʱ��ԣ��
	float m_fSettingValue;		//����ֵ
	float m_fSettingTime;		//��������ʱ��

	int  m_nBinLogic;//0 1�߼����
	tmt_BinaryIn m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryIn m_binInEx[MAX_ExBINARY_COUNT];

	//������
	tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];
	long m_nOutputSwitchMode;//��ת������ʽ 0-ʱ�䴥�� 1-����������
	float	m_fBoutTimeTrig;	//��תʱ�䣬0Ϊ����ת
	float	m_fBoutHoldTime;	//��ת����ʱ��

public:
	virtual void init()
	{
		m_nCurrent1Select = 0;
		m_nCurrent2Select = 0;
		m_fRate = 1.0f;
		m_fPreFaultTime = 0.0f;
		m_fMarginTime = 0.2f;
		m_fSettingValue = 0.0f;	
		m_fSettingTime = 0.0f;	

		m_nBinLogic = 0;

		for (int i = 0; i < MAX_BINARYIN_COUNT; i++)
		{
			m_binIn[i].init();
			m_binOut[i].init();
		}

		for (int i = 0; i < g_nBinExCount; i++)
		{
			m_binInEx[i].init();
		}

		m_nOutputSwitchMode = 0;
		m_fBoutTimeTrig = 0.0f;
		m_fBoutHoldTime = 0.0f;

	}
	void CopyOwn(tmt_dc_unbalance_paras* pDest)
	{
		pDest->m_nCurrent1Select = m_nCurrent1Select;
		pDest->m_nCurrent2Select = m_nCurrent2Select;
		pDest->m_fRate = m_fRate;
		pDest->m_fPreFaultTime = m_fPreFaultTime;
		pDest->m_fMarginTime = m_fMarginTime;
		pDest->m_fSettingValue = m_fSettingValue;
		pDest->m_fPreFaultTime = m_fPreFaultTime;
		pDest->m_fSettingTime = m_fSettingTime;
		pDest->m_nBinLogic = m_nBinLogic;

		for (int nIndex = 0;nIndex<MAX_BINARYIN_COUNT;nIndex++)
		{
			pDest->m_binIn[nIndex] = m_binIn[nIndex];
			pDest->m_binOut[nIndex] = m_binOut[nIndex];
			pDest->m_binInEx[nIndex] = m_binInEx[nIndex];
		}

		pDest->m_fBoutTimeTrig = m_fBoutTimeTrig;
		pDest->m_fBoutHoldTime = m_fBoutHoldTime;
		pDest->m_nOutputSwitchMode = m_nOutputSwitchMode;
	}

}tmt_DcUnbalanceParas;

typedef struct tmt_dc_unbalance_paras_ex :public tmt_DcUnbalanceParas
{
public:
	char m_pszSetting[PARAS_RSLT_EXPR_LEN];//����ֵ
	char m_pszTSetting[PARAS_RSLT_EXPR_LEN];//��������ʱ��
	char m_pszGroupID[MAX_NAME_LEN];//���ӷ���id

	virtual void init()
	{
		tmt_DcUnbalanceParas::init();
		memset(m_pszSetting,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszTSetting,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszGroupID, 0, MAX_NAME_LEN);
	}

}tmt_DcUnbalanceParasEx;

typedef struct tmt_dc_unbalance_results
{
public:
	float m_fTripTime;   //����ʱ��
	long m_nAct;

public:
	virtual void init()
	{
		m_fTripTime = 0;
		m_nAct = 0;
	}
}tmt_DcUnbalanceResults;

typedef struct tmt_dc_unbalance_test : public TMT_PARAS_HEAD
{
public:
	tmt_DcUnbalanceParasEx m_oDcUnbalanceParas;
	tmt_DcUnbalanceResults m_oDcUnbalanceResults;
	char m_szName[MAX_NAME_LEN];


	tmt_dc_unbalance_test()
	{
		init();
	}

	virtual void init()
	{
		init_head(); 
		strcpy(m_pszMacroID, STT_MACRO_ID_DCUnbalanceTest);
		m_nVersion = 0x00010001;
		m_nSelected = 1;
		m_nTestState = 0;
		memset(m_szName, 0, MAX_NAME_LEN);
		memset(&m_oRsltExprMngr, 0, sizeof(TMT_PARAS_RSLT_EXPR_MNGR));

		m_oDcUnbalanceParas.init();
		m_oDcUnbalanceResults.init();
	}

    virtual void clear_result()
    {
        m_oDcUnbalanceResults.init();
    }
	virtual ~tmt_dc_unbalance_test(){}

}tmt_DcUnbalanceTest;


void stt_init_paras(tmt_DcUnbalanceParas *pParas);
void stt_init_paras_ex(tmt_DcUnbalanceParasEx *pParas);
void stt_init_results(tmt_DcUnbalanceResults *pResults);

void stt_xml_serialize_DcUnbalance(tmt_DcUnbalanceParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_DcUnbalance_ex(tmt_DcUnbalanceParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_DcUnbalanceResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_DcUnbalanceTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_serialize_write_DcUnbalanceTest();

