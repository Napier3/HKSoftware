#pragma once

#include "../tmt_test_paras_head.h"
#include "../tmt_common_def.h"


#define VF_INVERSE_GRADMODE_ChangeVol                                                    0
#define VF_INVERSE_GRADMODE_ChangeFreq                                                   1




typedef struct tmt_volfreq_inverse_time_paras 
{
	//ͨ�ò���
	float m_fPreFaultTime;//����ǰʱ��
	long m_nGradMode;//�仯��ʽ 0-Ƶ�ʲ���,����ѹ  1-��ѹ����,��Ƶ��
	float m_fSettingFaultTime;//��������ʱ��
	float m_fFaultTimeMargin;//����ʱ��ԣ�� 20230419 zhouhj ��������330ģ�������ļ����������߲�������

	//�������
	float m_fKuf;//U*/F*
// 	float m_fStdVol;//���ѹ
// 	float m_fStdFreq;//�Ƶ��

	//������
	tmt_BinaryIn  m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryOut m_binOut[2][MAX_BINARYOUT_COUNT];	//0-�ǹ���̬���� 1-����̬����
	int		m_nBinLogic;			//0-�� 1-��

public:
	virtual void init()
	{
		m_fPreFaultTime = 5.0f;
		m_nGradMode = VF_INVERSE_GRADMODE_ChangeVol;
		m_fSettingFaultTime = 5.0f;
		m_fFaultTimeMargin = 0.0f;

		m_fKuf = 1.1f;
// 		m_fStdVol = 57.74f;
// 		m_fStdFreq = 50.0f;

		m_nBinLogic = 0;

		for (int i=0;i<MAX_BINARYIN_COUNT;i++)
		{
			m_binIn[i].init();
			for(int j=0;j<2;j++)
			{
				m_binOut[j][i].init();
			}
		}
	} 

}tmt_VFInverseTimeParas;

typedef struct tmt_volfreq_inverse_time_results
{
	float m_fTripTime;
	long m_nAct;

public:
	virtual void init()
	{
		m_fTripTime = 0.0f;
		m_nAct = 0;
	} 

}tmt_VFInverseTimeResults;


typedef struct tmt_volfreq_inverse_time_test : public TMT_PARAS_HEAD
{
public:
	tmt_VFInverseTimeParas      m_oVolInverseParas;
	tmt_VFInverseTimeResults   m_oVolInverseResults;

	void init()
	{	
		init_head(); //2021-9-13  lijunqing

		strcpy(m_pszMacroID, STT_MACRO_ID_VFInverseTime);
		m_nVersion = 0x00010001;
		m_nTestState = 0;

		m_oVolInverseParas.init();
		m_oVolInverseResults.init();
	}

	tmt_volfreq_inverse_time_test()	{init();}
	virtual void clear_result(){	m_oVolInverseResults.init();	}
	virtual ~tmt_volfreq_inverse_time_test(){}
}tmt_VFInverseTimeTest;

void stt_init_paras(tmt_VFInverseTimeParas *pParas);
void stt_init_results(tmt_VFInverseTimeResults *pResults);

void stt_xml_serialize(tmt_VFInverseTimeParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_VFInverseTimeResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_VFInverseTimeTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
