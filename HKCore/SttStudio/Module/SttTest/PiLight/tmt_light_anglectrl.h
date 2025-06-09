#pragma once
#include "../Common/tmt_common_def.h"
#include "../../SttTestBase/SttXmlSerialize.h"
#include "../Common/tmt_test_paras_head.h"

typedef struct tmt_lightangle_para
{
public:
	unsigned int m_nWaitTime;//等待电机超时时间
	unsigned int m_nMode;//0-转动 1-清零
	unsigned int m_nAngle;//光源旋转角度
	unsigned int m_nDirection;//0-正转 1-反转
public:
    void init()
    {
		m_nWaitTime = 5;
		m_nMode = 0;
		m_nAngle = 0;
		m_nDirection = 0;
    }

	tmt_lightangle_para()	{}
}tmt_LightAnglePara;

typedef struct tmt_lightangle_test
{
public:
	tmt_LightAnglePara    m_oLightAnglePara;

	void init()
	{
		m_oLightAnglePara.init();
	}
	tmt_lightangle_test() {}
}tmt_LightAngleTest;

typedef struct tmt_light_getangle_result
{
public:
	unsigned int m_nTotalCode;//总码值
	unsigned int m_nRingCnt;//圈数
	unsigned int m_nRingValue;//单圈值
	unsigned int m_nAngle;//编码器角度值已经放大100倍
	unsigned int m_nReserve;//备用
public:
	void init()
	{
		m_nTotalCode = 0;
		m_nRingCnt = 0;
		m_nRingValue = 0;
		m_nAngle = 0;
		m_nReserve = 0;
	}

	tmt_light_getangle_result()	{}
}tmt_LightGetAngleResult;

typedef struct tmt_light_getangle
{
public:
	tmt_LightGetAngleResult    m_oLightGetAngleResult;

	void init()
	{
		m_oLightGetAngleResult.init();
	}
	tmt_light_getangle() {}
}tmt_LightGetAngle;

extern tmt_LightGetAngle g_oLightGetAngle;

void stt_xml_serialize_write_LightAngleTest();
void stt_xml_serialize_write_LightGetAngle();
void stt_init_paras(tmt_LightAnglePara *pPara);
void stt_xml_serialize(tmt_LightAnglePara *pPara, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_LightGetAngleResult *pResult, CSttXmlSerializeBase *pXmlSierialize);

