#pragma once

#include "../tmt_gradient_test.h"
#include "../tmt_test_paras_head.h"

#define ULOCK_FAULT_TYPE_LOW_VOLTAGE                   0 
#define ULOCK_FAULT_TYPE_NEG_SEQ_VOL                   1 
#define ULOCK_FAULT_TYPE_LOW_CURRENT_A                 2 
#define ULOCK_FAULT_TYPE_LOW_CURRENT_B                 3 
#define ULOCK_FAULT_TYPE_LOW_CURRENT_C                 4 


typedef struct tmt_ulock_overcurrent_paras :public tmt_GradientParas
{
public:
	int		m_nULockFaultType;	//��ѹ������������
	float	m_fSCVoltage;
	float	m_fSCCurrent;
	float	m_fImpAngle;

	//����Ϊ�������ʹ�ò���
	float m_fVzd;//�͵�ѹ��ֵ
	float m_fV2zd;
	float m_fIzd;
	float m_fT1;
	float m_fPhimax;//���������
	float m_fPhiSize;//��������С
	long m_nIPoint;//��������
	long m_nUSetMode;//�͵�ѹ����  0-���ѹ 1-�ߵ�ѹ VSetMode

	
public:
	virtual void init()
	{
		tmt_GradientParas::init();
		m_nSttTestMode = GradientTest_URamp;
		m_fStart = 4.9f;
		m_fStop = 5.1f;
		m_fStep = 0.1f;
		m_fStepTime = 0.1f;
		m_nULockFaultType = 0;
		m_nTestMode = Gradient_TestMode_ActValue;

		m_fSCVoltage = 0.0f;
		m_fSCCurrent = 0.0f;
		m_fImpAngle = 0.0f;

		m_fVzd = 50.0f;
		m_fV2zd = 10.0f;
		m_fIzd = 3.0f;
		m_fT1 = 1.0f;
		m_fPhimax = -30.0f;
		m_fPhiSize = 180.0f;
		m_nIPoint = 0;
		m_nUSetMode = 0;
	} 

}tmt_ULockOverCurrentParas;


typedef struct tmt_ulock_overcurrent_paras_ex :public tmt_ULockOverCurrentParas
{
public:
	char	m_pszSCVoltage[PARAS_RSLT_EXPR_LEN];
	char	m_pszSCCurrent[PARAS_RSLT_EXPR_LEN];
	char	m_pszImpAngle[PARAS_RSLT_EXPR_LEN];
	char	m_pszStart[PARAS_RSLT_EXPR_LEN];
	char	m_pszStop[PARAS_RSLT_EXPR_LEN];
	char	m_pszStepTime[PARAS_RSLT_EXPR_LEN];

	virtual void init()
	{
		tmt_ULockOverCurrentParas::init();
		memset(m_pszSCVoltage,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszSCCurrent,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszImpAngle,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszStart,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszStop,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszStepTime,0,PARAS_RSLT_EXPR_LEN);
	} 
}tmt_ULockOverCurrentParasEx;

typedef struct tmt_ulock_overcurrent_results :public tmt_GradientResult
{

public:
	virtual void init()
	{
		tmt_GradientResult::init();
	} 

}tmt_ULockOverCurrentResults;

typedef struct tmt_ulock_overcurrent_test : public TMT_PARAS_HEAD
{
public:
	tmt_ULockOverCurrentParasEx       m_oTmtParas;
	tmt_ULockOverCurrentResults   m_oTmtResults;

	void init()
	{
		init_head(); //20210918 zhouhj
		strcpy(m_pszMacroID, STT_MACRO_ID_ULockOverCurrent);
		m_nVersion = 0x00010001;
		m_nTestState = 0;

		m_oTmtParas.init();
		m_oTmtResults.init();
	}

	tmt_ulock_overcurrent_test()	{init();}
	virtual void clear_result(){	m_oTmtResults.init();	}
	virtual ~tmt_ulock_overcurrent_test(){}
}tmt_ULockOverCurrentTest;

void stt_init_paras(tmt_ULockOverCurrentParas *pParas);
void stt_init_paras_ex(tmt_ULockOverCurrentParasEx *pParas);
void stt_init_results(tmt_ULockOverCurrentResults *pResults);

void stt_xml_serialize(tmt_ULockOverCurrentParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_ex(tmt_ULockOverCurrentParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_ULockOverCurrentResults *pResults, CSttXmlSerializeBase *pXmlSierialize);


CSttXmlSerializeBase* stt_xml_serialize(tmt_ULockOverCurrentTest *pTests, CSttXmlSerializeBase *pXmlSerialize);

