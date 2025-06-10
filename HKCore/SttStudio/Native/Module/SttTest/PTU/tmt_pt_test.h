#pragma once
#include"../../SttTestBase/SttXmlSerialize.h"
#include "tmt_soe_test.h"
#include "./tmt_common_def.h"


typedef struct tmt_pt_para
{
public:
	unsigned int value;
public:
    void init()
    {
		value=0;
    }

	tmt_pt_para()	{}
	virtual ~tmt_pt_para() {}
}tmt_PtPara;

typedef struct tmt_pt_test
{
public:
	tmt_PtPara    m_oPtPara;

	void init()
	{
		m_oPtPara.init();
	}
	tmt_pt_test() {}
	virtual ~tmt_pt_test() {}
}tmt_PtTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas

void stt_xml_serialize_write_PtTest();
void stt_init_paras(tmt_PtPara *pPara);
void stt_xml_serialize(tmt_PtPara *pPara, CSttXmlSerializeBase *pXmlSierialize);

