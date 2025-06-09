#pragma once

#include "../tmt_gradient_test.h"
#include "tmt_sequence_manu_test.h"
//////////////////////////////////////////////////////////////////////////

typedef struct tmt_sequence_gradient_test
{
public:
	tmt_GradientParas m_oSequenceGradientParas;
	tmt_GradientResult m_oSequenceResultParas;

	void init()
	{
		m_oSequenceGradientParas.init();
		m_oSequenceResultParas.init();
	}

	tmt_sequence_gradient_test()	{}
}tmt_SequenceGradientTest;

typedef struct tmt_sequence_gradient_test_ex : public TMT_PARAS_HEAD
{
public:
	tmt_GradientParasEx m_oSequenceGradientParasEx;
	tmt_GradientResult m_oSequenceResultParas;

	void init()
	{
		init_head(); 
		strcpy(m_pszMacroID,STT_MACRO_ID_SequenceGradientTest);
		m_nSelected = 1;
		m_nVersion = 0x00010001;
		m_nTestState = 0;

		m_oSequenceGradientParasEx.init();
		m_oSequenceResultParas.init();
	}

	tmt_sequence_gradient_test_ex(){	init();}
}tmt_SequenceGradientTestEx;

typedef struct tmt_sequence_gradient_pnv_test : public TMT_PARAS_HEAD
{
public:
    tmt_GradientParas m_oSequenceGradientParas;
    tmt_GradientResult m_oSequenceResultParas;

    void init()
    {
        init_head();
        strcpy(m_pszMacroID,STT_MACRO_ID_PnvSCActValue);
        m_nSelected = 1;
        m_nVersion = 0x00010001;
        m_nTestState = 0;
        m_oSequenceGradientParas.init();
        m_oSequenceResultParas.init();
    }

    tmt_sequence_gradient_pnv_test()	{}
}tmt_SequenceGradientPnvTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas
///
#ifndef _STT_NOT_IN_TEST_SERVER_
void stt_xml_serialize_Sequence(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize,
                                tmt_channel *puiVOL1, tmt_channel *puiVOL2, tmt_channel *puiVOL3,
                                tmt_channel *puiCUR1, tmt_channel *puiCUR2, tmt_channel *puiCUR3);
#endif

void stt_xml_serialize_sequence_base(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_sequence_ex(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_Sequence(tmt_GradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_SequenceGradientTestEx *pParas, CSttXmlSerializeBase *pXmlSerialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_SequenceGradientPnvTest *pParas, CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_sequence_serialize(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_sequence_serialize(tmt_GradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_sequence_pnv_serialize(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_sequence_pnv_serialize(tmt_GradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_write_SequenceGradientTest();
