#ifndef TMT_IED_TEST_H
#define TMT_IED_TEST_H
#include "tmt_state_test.h"
#include "../../SttTestBase/SttXmlSerialize.h"
#include "../../SttDevice/RelayTest/drv_define.h"

typedef struct tmt_ied_para
{
public:
	int     m_nOutputTime;
	tmt_BinaryOut     m_binOut[256];

	void init()
	{
		m_nOutputTime=5000;
		for (int j=0;j<256;j++)
		{
			m_binOut[j].init();
		}
	}

	tmt_ied_para(){}
	virtual ~tmt_ied_para(){}
}tmt_IEDPara;

typedef struct tmt_ied_paras
{
public:
	int		         m_nStateCount;
	int              m_nDataMode;//加量方式 0-gse2bin,1-bin2gse
	int              m_nTestType;//实验类型 0-延时测试 1-SOE测试 2-风暴测试
	tmt_ied_para    m_oIEDPara[256];

	void init()
	{
		m_nStateCount = 5;
		m_nDataMode=0;
		m_nTestType=0;
		for(int i=0;i<8;i++)
		{
			m_oIEDPara[i].init();
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
void stt_xml_serialize(tmt_IEDPara &oPara, long nIndex, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_IEDParas *pParas, CSttXmlSerializeBase *pXmlSierialize);

#endif // TMT_TIMEMEASURE_TEST_H

