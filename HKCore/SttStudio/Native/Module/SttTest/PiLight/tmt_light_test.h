#pragma once
#include "../Common/tmt_common_def.h"
#include "../../SttTestBase/SttXmlSerialize.h"
#include "../Common/tmt_test_paras_head.h"

typedef struct tmt_light_para
{
public:
	unsigned int m_nUseBi;//光源启动映射开关量  1-8:开关1-8
	unsigned int m_nDelayType;//光源与电流输出时间关系 0:电流超前 1:光源超前
	float        m_fDelayTime;//超前时间 毫秒
	unsigned int m_nMode;//模式选择 0-阶跃 1-脉冲
	unsigned int m_nTime;//脉冲时间 ms
	unsigned int m_nType;//光源选择 0-紫光 1-白光
	unsigned int m_nData0;//紫光光强
	unsigned int m_nData1;//白光光强

	float m_fBaseFre;//基波频率
	tmt_channel m_uiCUR[6];
	int		m_nBinLogic;//0-或 1-与
	int     m_nBinStop;//开入变位后 0-不停止实验,1-停止实验
	tmt_BinaryIn    m_binIn[10];//光源启动映射开关量 禁用
	tmt_BinaryOut   m_binOut[8];
public:
    void init()
    {
		m_nUseBi = 8;//默认第8个开入
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
	//结果参数
	float	m_frTestTime;							//实际试验时间
	float	m_frTimeBinAct[MAX_BINARYIN_COUNT][64];		//每一个开入记录64次变位时间
	int		m_nrBinSwitchCount[MAX_BINARYIN_COUNT]; //变位次数
	int		m_nTripFlag; //0,1
	float	m_fTripTime;		//实际试验时间
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

