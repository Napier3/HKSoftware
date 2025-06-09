#pragma once

#include "../tmt_manu_test.h"
#include "../tmt_common_def.h"

typedef struct tmt_fa_paras_set
{
	float m_fRatedVoltage;   		//���ѹ
	float m_fResidualVoltage;   		//��ѹ
	float m_fRatedCurrent;   		//�����
	float m_fFaultCurrent;  		//���ϵ���
	float m_fFailureDuration;		//���ϳ���ʱ��
	float m_fErrorAssessTime;   //�������ʱ��
	float m_fxTime;			 //������ʱ��բʱ��
	float m_fyTime;			//��բ���޹���ȷ��ʱ��
	float m_fzTime;			//ʧѹ��բʱ��
	float m_fxlTime;			//����ģʽ����ʧѹ��ʱ��բʱ��
	float m_fsTime;			//����Ӧ���޹��ϵõ���ʱ��բʱ��
	
	void init()
	{
		m_fRatedVoltage = 100.00f;
		m_fResidualVoltage = 30.00f;
		m_fRatedCurrent = 5.000f;
		m_fFaultCurrent = 5.000f;
		m_fFailureDuration = 0.500f;
		m_fErrorAssessTime = 0.500f;
		m_fxTime = 7.000f;
		m_fyTime = 5.000f;
		m_fzTime = 0.000f;
		m_fxlTime = 50.000f;
		m_fsTime = 57.000f;

		m_nTermPowerVol = 0;		//0-UAB 1-UCB
		m_nTermLoadVol = 1;			//0-UAB 1-UCB

		m_strCloseOutput = "����A";
		m_strOpenOutput = "����B";

		m_strCloseSignal = "����1";
		m_strQuantileSignal = "����2";
	}
	tmt_fa_paras_set()
	{
		init();
	}

	int m_nTermPowerVol;		//0-UAB 1-UCB
	int m_nTermLoadVol;			//0-UAB 1-UCB

	QString m_strCloseOutput;
	QString m_strOpenOutput;

	QString m_strCloseSignal;
	QString m_strQuantileSignal;

 	tmt_BinaryIn    m_binCloseIn[MAX_BINARYIN_COUNT];   //��բ����
 	tmt_BinaryOut   m_binQuantileout[MAX_BINARYOUT_COUNT]; //��λ����

	tmt_BinaryIn    m_binOpenIn[MAX_BINARYIN_COUNT];   //��բ����
	tmt_BinaryOut   m_binFitout[MAX_BINARYOUT_COUNT]; //��λ����

}tmt_FaParasSet;


typedef struct tmt_fa_paras_set_result  : public tmt_ManualResult
{
public:
	virtual void init()
	{
		tmt_ManualResult::init();
	}

	tmt_fa_paras_set_result()
	{
		init();
	}
} tmt_FaParasSetResult;


typedef struct tmt_fa_paras_set_test : public TMT_PARAS_HEAD
{
public:
	tmt_FaParasSetResult    m_oFaParasSetResult;
	tmt_FaParasSet			m_oFaParasSet;


	void init()
	{
		strcpy(m_pszMacroID, STT_MACRO_ID_VolTimeTypeSecTest);
#ifndef NOT_USE_TMT_TEST_PARAS_HEAD
		m_nVersion = 0x00010001;
		m_nTestState = 0;
#endif
		m_oFaParasSet.init();
		m_oFaParasSetResult.init();
	}

	tmt_fa_paras_set_test()
	{
		init();
	}
} tmt_FaParasSetTest;



//���� ����ֵ ���л�
void stt_xml_serialize_base(tmt_FaParasSet *pParas, CSttXmlSerializeBase *pXmlSierialize);
//��բ����
void stt_xml_serialize_binary_closein(tmt_FaParasSet *pParas, CSttXmlSerializeBase *pXmlSierialize);
//��λ����
void stt_xml_serialize_binary_openin(tmt_FaParasSet *pParas, CSttXmlSerializeBase *pXmlSierialize);
//��բ����
void stt_xml_serialize_binary_Fitout(tmt_FaParasSet *pParas, CSttXmlSerializeBase *pXmlSierialize);
//��λ����
void stt_xml_serialize_binary_Quantileout(tmt_FaParasSet *pParas, CSttXmlSerializeBase *pXmlSierialize);
//���ԣ��ļ����� �鿴
void stt_xml_serialize_write_FaultGradientTest();