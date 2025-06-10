#ifndef TMT_TIMEMEASURE_TEST_H
#define TMT_TIMEMEASURE_TEST_H
#include "../Common/tmt_state_test.h"
#include "../../SttTestBase/SttXmlSerialize.h"

typedef struct tmt_timemeasure_para
{
public:
	int     m_nTrigType;//0--时间触发  4--GPS/B码触发
	int     m_nOutputTime;//时间触发时代表 状态输出时长   B码触发时代表<实验开始>后多久触发	
	tmt_BinaryOut     m_binOut[MAX_BINARYOUT_COUNT];

	void init()
	{
		m_nTrigType=0;		
		m_nOutputTime=5000;
		for (int j=0;j<MAX_BINARYOUT_COUNT;j++)
		{
			m_binOut[j].init();
		}
	}

	tmt_timemeasure_para(){}
	virtual ~tmt_timemeasure_para(){}
}tmt_TimeMeasurePara;

typedef struct tmt_timemeasure_paras
{
public:
	int		m_nStateCount;
	tmt_timemeasure_para    m_oTimeMeasurePara[20];

	void init()
	{
		m_nStateCount = 5;
		for(int i=0;i<20;i++)
		{
			m_oTimeMeasurePara[i].init();
		}
	}

	tmt_timemeasure_paras(){}
	virtual ~tmt_timemeasure_paras(){}
}tmt_TimeMeasureParas;

typedef struct tmt_timemeasure_test
{
public:
	tmt_TimeMeasureParas       m_oTimeMeasureParas;

	void init()
	{		
		m_oTimeMeasureParas.init();
	}

	tmt_timemeasure_test()	{}
	virtual ~tmt_timemeasure_test(){}
}tmt_TimeMeasureTest;

void stt_xml_serialize_write_TimeMeasureTest();
void stt_xml_serialize(tmt_TimeMeasurePara &oPara, long nIndex, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_TimeMeasureParas *pParas, CSttXmlSerializeBase *pXmlSierialize);

#endif // TMT_TIMEMEASURE_TEST_H

