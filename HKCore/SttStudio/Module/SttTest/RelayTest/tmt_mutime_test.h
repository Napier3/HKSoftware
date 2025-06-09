#ifndef TMT_MUTIME_TEST_H
#define TMT_MUTIME_TEST_H

#include "../../SttTestBase/SttXmlSerialize.h"
#include "../../SttDevice/RelayTest/drv_define.h"

typedef struct tmt_mutime_para
{
public:
	int     m_nOutputTime;

	void init()
	{

	}

	tmt_mutime_para(){}
	virtual ~tmt_mutime_para(){}
}tmt_MUTIMEPara;

typedef struct tmt_mutime_test
{
public:
	tmt_MUTIMEPara       m_oMUTIMEPara;

	void init()
	{		
		m_oMUTIMEPara.init();
	}

	tmt_mutime_test()	{}
	virtual ~tmt_mutime_test(){}
}tmt_MUTIMETest;

void stt_xml_serialize_write_MUTimeTest();
void stt_xml_serialize(tmt_MUTIMEPara *pParas, CSttXmlSerializeBase *pXmlSierialize);

#endif // TMT_TIMEMEASURE_TEST_H

