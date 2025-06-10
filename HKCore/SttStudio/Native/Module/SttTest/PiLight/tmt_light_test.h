#pragma once
#include "../Common/tmt_common_def.h"
#include "../../SttTestBase/SttXmlSerialize.h"
#include "../Common/tmt_test_paras_head.h"

typedef struct tmt_light_para
{
public:
	unsigned int m_nUseBi;//��Դ����ӳ�俪����  1-8:����1-8
	unsigned int m_nDelayType;//��Դ��������ʱ���ϵ 0:������ǰ 1:��Դ��ǰ
	float        m_fDelayTime;//��ǰʱ�� ����
	unsigned int m_nMode;//ģʽѡ�� 0-��Ծ 1-����
	unsigned int m_nTime;//����ʱ�� ms
	unsigned int m_nType;//��Դѡ�� 0-�Ϲ� 1-�׹�
	unsigned int m_nData0;//�Ϲ��ǿ
	unsigned int m_nData1;//�׹��ǿ

	float m_fBaseFre;//����Ƶ��
	tmt_channel m_uiCUR[6];
	int		m_nBinLogic;//0-�� 1-��
	int     m_nBinStop;//�����λ�� 0-��ֹͣʵ��,1-ֹͣʵ��
	tmt_BinaryIn    m_binIn[10];//��Դ����ӳ�俪���� ����
	tmt_BinaryOut   m_binOut[8];
public:
    void init()
    {
		m_nUseBi = 8;//Ĭ�ϵ�8������
		m_nDelayType = 0;
		m_fDelayTime = 0.0f;
		m_nMode = 0;
		m_nTime = 0;
		m_nType = 0;
		m_nData0 = 0;
		m_nData1 = 0;

		m_fBaseFre = 50.0f;
		float fAngle[3] = {0, -120.0, 120.0};
		for(int i=0; i<6; i++)
		{
			m_uiCUR[i].Harm[0].fAmp = 0;
			m_uiCUR[i].Harm[1].fAmp = 0;
			m_uiCUR[i].Harm[1].fAngle = fAngle[i%3];
			m_uiCUR[i].Harm[1].fFreq=50;
		}

		m_nBinLogic = 0;
		m_nBinStop = 0;
		for (int j=0;j<10;j++)
		{
			m_binIn[j].nSelect = 0;
			m_binIn[j].nTrigMode = 0;
		}
		for (int j=0;j<8;j++)
		{
			m_binOut[j].nState = 0;
			m_binOut[j].nMode = 0;
			m_binOut[j].fTimeTrig = 0;
			m_binOut[j].fHoldTime = 0;
		}
    }

	tmt_light_para()	{}
}tmt_LightPara;

typedef struct tmt_light_result
{
public:
	//�������
	float	m_frTestTime;							//ʵ������ʱ��
	float	m_frTimeBinAct[MAX_BINARYIN_COUNT][64];		//ÿһ�������¼64�α�λʱ��
	int		m_nrBinSwitchCount[MAX_BINARYIN_COUNT]; //��λ����
	int		m_nTripFlag; //0,1
	float	m_fTripTime;		//ʵ������ʱ��
	float	m_fActValue;

public:
	void init()
	{
		m_frTestTime = 0;
		m_nTripFlag = 0;
		m_fTripTime = 0;
		m_fActValue = 0;
		for (int i=0;i<MAX_BINARYIN_COUNT;i++)
		{
			for (int j=0;j<64;j++)
			{
				m_frTimeBinAct[i][j] = 0;
			}
			m_nrBinSwitchCount[i] = 0;
		}
	}

	tmt_light_result()
	{
		init();
	}
}tmt_LightResult;

typedef struct tmt_light_test
{
public:
	tmt_LightPara    m_oLightPara;
	tmt_LightResult  m_oLightResult;
	void init()
	{
		m_oLightPara.init();
		m_oLightResult.init();
	}
	tmt_light_test() {}
}tmt_LightTest;

void stt_xml_serialize_write_LightTest();
void stt_init_paras(tmt_LightPara *pPara);
void stt_xml_serialize(tmt_LightPara *pPara, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_LightResult *pResults, CSttXmlSerializeBase *pXmlSierialize);

