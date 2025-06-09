#ifndef TMT_IED_TEST_H
#define TMT_IED_TEST_H
#include "../../SttTestBase/SttXmlSerialize.h"
#include "../../SttDevice/RelayTest/drv_define.h"
#include "tmt_common_def.h"

#define MAX_IO_SIZE 40  //8+32

//0-延时测试 1-SOE测试 2-风暴测试 3-复归
#define  DelayMode  0
#define  SOEMode    1
#define  RepeatMode 2

typedef struct tmt_ied_para
{
public:		
	tmt_BinaryOut    m_binOut[256];

	void init()
	{
		for(int i=0;i<256;i++)
		{
			m_binOut[i].init();
		}
	}

	tmt_ied_para(){}
	virtual ~tmt_ied_para(){}
}tmt_IEDPara;

typedef struct tmt_ied_paras
{
public:
	int              m_nFaultPreTime;//故障前时间
	int              m_nOutputTime;//状态间隔时间 毫秒
	int              m_nBoKeepTime;//开出保持时间 毫秒
	int              m_nDataMode;//加量方式 0-gse2bin,1-bo2gse 2-gse2bin复归 3-bo2gse复归
	int              m_nTestType;//实验类型 0-延时测试 1-SOE测试 2-风暴测试
	int              m_nRepeatCount;//风暴重复次数
	int              m_nStateCount;

	tmt_IEDPara      m_otmt_IEDPara[256];

	void init()
	{
		m_nOutputTime=1000;
		m_nBoKeepTime=0;
		m_nDataMode=0;
		m_nTestType=0;
		m_nRepeatCount=0;
		m_nStateCount=256;
		for(int i=0;i<m_nStateCount;i++)
		{
			m_otmt_IEDPara[i].init();
		}
	}

	tmt_ied_paras(){}
	virtual ~tmt_ied_paras(){}
}tmt_IEDParas;

typedef struct tmt_ied_test
{
public:
	tmt_IEDParas       m_oIEDParas;

	void init()
	{		
		m_oIEDParas.init();
	}

	tmt_ied_test()	{}
	virtual ~tmt_ied_test(){}
}tmt_IEDTest;

void stt_xml_serialize_write_IEDTest();
void stt_xml_serialize(tmt_IEDParas *oParas, CSttXmlSerializeBase *pXmlSierialize);

#endif // TMT_TIMEMEASURE_TEST_H

