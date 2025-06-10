#pragma once
#include"../../../SttTestBase/SttXmlSerialize.h"


typedef struct tmt_pt_para
{
public:
	unsigned int m_nPT1;//第一路PT
	unsigned int m_nPT2;//第二路PT
public:
    void init()
    {
		m_nPT1=0;
		m_nPT2=0;
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

