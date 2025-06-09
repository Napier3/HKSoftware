#pragma once

#include "../tmt_gradient_test.h"
#include "tmt_linevolt_manu_test.h"
#include "../tmt_common_def.h"
#include"../../../SttTestBase/SttXmlSerialize.h"
#include "../tmt_test_paras_head.h"


typedef struct tmt_linevolgradient_paras :public tmt_gradient_paras
{
	tmt_linevolgradient_paras(){}
}tmt_LineVolGradientParas;

typedef struct tmt_LineVolgradient_result : public tmt_gradient_result
{
	tmt_LineVolgradient_result()	{}
}tmt_LineVolGradientResult;

typedef struct tmt_linevolgradient_paras_ex : public tmt_linevolgradient_paras
{
public:
	TestDataCondition sCondition; //结果判据

public:
	void init()
	{
		m_nSttTestMode = GradientTest_Base;

		tmt_linevolgradient_paras::init();
	}

	tmt_linevolgradient_paras_ex()	{}
}tmt_LineVolGradientParasEx;

typedef struct tmt_linevolgradient_test_ex :public TMT_PARAS_HEAD
{
public:
	tmt_LineVolGradientParasEx m_oLineVolGradientParasEx;
	tmt_LineVolGradientResult m_oLineVolGradientResultParas;
	void init()
	{
		init_head();
		strcpy(m_pszMacroID, STT_MACRO_ID_LineVolGradientTest);
		m_nSelected = 1;
		m_nVersion = 0x00010001;
		m_nTestState = 0;

		m_oLineVolGradientParasEx.init();
		m_oLineVolGradientResultParas.init();

	}
	tmt_linevolgradient_test_ex(){init();};

}tmt_LineVolGradientTestEx;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas

#ifndef _STT_NOT_IN_TEST_SERVER_
void stt_xml_serialize_linevolt(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize,
                                tmt_channel *puiVOL1, tmt_channel *puiVOL2, tmt_channel *puiVOL3,
                                tmt_channel *puiCUR1, tmt_channel *puiCUR2, tmt_channel *puiCUR3);
#endif
void stt_xml_serialize_write_LineVolGradientTest();
void stt_xml_serialize_Chs_linevolt(tmt_LineVolGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_base_LineVol(tmt_LineVolGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_LineVol(tmt_LineVolGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);//测试参数
void stt_xml_serialize_LineVol(tmt_LineVolGradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize);//结果参数
void stt_xml_serialize_LineVol_ex(tmt_LineVolGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
CSttXmlSerializeBase* stt_xml_serialize_LineVol(tmt_linevolgradient_test_ex *pParas, CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_serializeLineVolGradientSetting(tmt_GradientParas *pParas,CSttXmlSerializeBase *pXmlSierialize);
