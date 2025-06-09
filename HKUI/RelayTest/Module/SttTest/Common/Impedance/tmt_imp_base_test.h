#pragma once

#include "../tmt_state_test.h"

#define STT_CB_OPERATE_PROC_CTRL_TRIP              0
#define STT_CB_OPERATE_PROC_CTRL_TIME              1
// #define MAX_NAME_LEN  32

typedef struct tmt_imp_base_paras
{
public:
	tmt_StateParas *m_pStateParas;

	float	m_fImpBaseFaultTime;		//������ʱ�� s
	float 	m_fImpBaseTripTime;		//�����բʱ�� s
	float	m_fImpBaseTransTime; //ת��ʱ�� s
	BOOL 	m_bImpBaseIsPermanent;        //�Ƿ����ù���    1�� ����  0 �� ˲ʱ����
	BOOL	m_bImpBaseTransFault;//�Ƿ���ת������  1�� ��    0 �� ����
	float	m_fImpBaseReclosingTime;		//�غ�բ��ֵ s
	float 	m_fImpBaseStopTime;			//ֹ̬ͣ����ʱ�� s
	BOOL    m_bSearchNext;//0-����������1-�к���������Ҫ��ֹͣ���


	void init(tmt_StateParas *pStateParas)
	{
		m_fImpBaseFaultTime = 5.0f;		//������ʱ�� s
		m_fImpBaseTripTime = 5.0f;		//�����բʱ�� s
		m_fImpBaseTransTime = 5.0; //ת��ʱ�� s
		m_bImpBaseIsPermanent = TRUE;        //�Ƿ����ù���    1�� ����  0 �� ˲ʱ����
		m_bImpBaseTransFault = TRUE;//�Ƿ���ת������  1�� ��    0 �� ����
		m_fImpBaseReclosingTime = 5.0f;		//�غ�բ��ֵ s
		m_fImpBaseStopTime = 0.1f;			//ֹ̬ͣ����ʱ�� s
		m_bSearchNext = FALSE;

		m_pStateParas = pStateParas;
		if(m_pStateParas==NULL)
			return;

		m_pStateParas->m_nStateNumbers = 8;
		m_pStateParas->m_nRepeatNumbers = 0;
		m_pStateParas->m_nBinTripRef = 1;
		m_pStateParas->m_nPlusDC = 0;
		m_pStateParas->m_fTao = 0;
		m_pStateParas->m_bSequence = true;
		for (int i=0;i<m_pStateParas->m_nStateNumbers;i++)
		{
			m_pStateParas->m_paraState[i].init();
		}
	}


	tmt_imp_base_paras()
	{

	}
	virtual ~tmt_imp_base_paras(){}

}tmt_ImpBaseParas;


// typedef struct tmt_imp_base_test  : public TMT_PARAS_HEAD
// {
// public:
// 	tmt_ImpBaseParas       m_oCBOperateParas;
// 	tmt_ImpBaseResults   m_oCBOperateResults;
// 
// 	void init()
// 	{
// 		m_nVersion = 0x00010001;
// 		m_nTestState = 0;
// 		m_nSelected = 1;
// 
// 		m_oCBOperateParas.init();
// 		m_oCBOperateResults.init();
// 	}
// 
// 
// 
// 	tmt_imp_base_test()	{init();}
// 	virtual ~tmt_imp_base_test(){}
// 
// }tmt_ImpBaseTest;

void stt_init_paras(tmt_ImpBaseParas *pParas);

void stt_xml_serialize(tmt_ImpBaseParas *pParas, CSttXmlSerializeBase *pXmlSierialize);


