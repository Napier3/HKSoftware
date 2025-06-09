#pragma once
#include"../../SttTestBase/SttXmlSerialize.h"
#include "../Common/tmt_common_def.h"

#define MAX_PARACOUNT_BINARY 8

#define SOETYPE_NULL 0
#define SOETYPE_GPS  1


typedef struct tmt_soestate
{
public:
	unsigned int val;            //开出值             0：断开            1：闭合
	unsigned int time;            //持续时间毫秒值
public:
	void init()
	{
		val=0;
		time=1;
	}

	tmt_soestate()	{	init();	}
}tmt_SoeState;

typedef struct tmt_soebinary_out
{
public:
	unsigned int isValid;            //该通道是否有效            1；有效            0：无效
	unsigned int cnt;                  //循环次数
	tmt_SoeState otmt_SoeState[3];

public:
	void init()
	{
		isValid=0;
		cnt=1;
		for(int i=0;i<3;i++)
		{
			otmt_SoeState[i].init();
		}
	}

	tmt_soebinary_out()	{	init();	}
}tmt_SoeBinaryOut;

typedef struct tmt_soe_paras
{
public:
	unsigned int m_nMode;            //0:立即实验      1:GPS触发实验开始
	tmt_time	 m_tGps;            //GPS time
	unsigned int m_nHoldTime;   //持续时间

	tmt_SoeBinaryOut m_binOut[MAX_PARACOUNT_BINARY];
public:
    void init()
    {
		m_nMode=0;
		m_nHoldTime=0;
		m_tGps.init();

		for(int i=0;i<MAX_PARACOUNT_BINARY;i++)
		{
			m_binOut[i].init();
		}
    }

	tmt_soe_paras()	{}
}tmt_SoeParas;

typedef struct tmt_soe_result
{
public:
    int		m_nTripFlag;
    float	m_fTripTime;
    float	m_fActValue;

public:
    void init()
    {
        m_nTripFlag = 0;
        m_fTripTime = 0;
        m_fActValue = 0;
    }

	tmt_soe_result()	{}
}tmt_SoeResult;

typedef struct tmt_soe_test
{
public:
	tmt_SoeResult   m_oSoeResult;
	tmt_SoeParas    m_oSoeParas;

    void init()
    {
		m_oSoeResult.init();
		m_oSoeParas.init();
    }
	tmt_soe_test() {}
}tmt_SoeTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas

void stt_xml_serialize_write_SoeTest();
void stt_init_paras(tmt_SoeParas *pParas);
void stt_init_results(tmt_SoeResult *pResults);
void stt_xml_serialize(tmt_SoeParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_SoeResult *pResults, CSttXmlSerializeBase *pXmlSierialize);


