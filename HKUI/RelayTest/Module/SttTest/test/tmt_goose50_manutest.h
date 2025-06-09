#pragma once

#include "../common/tmt_common_def.h"
#include"../../SttTestBase/SttXmlSerialize.h"

//2021-5-30  lijunqing
#include "../common/tmt_test_paras_head.h"


typedef struct tmt_goose50_paras
{
public:
    //GoosePub
    tmt_GoosePub m_oGoosePub[50];

public:
    void init()
    {
        for(int nIndex = 0; nIndex < 50; nIndex++)
        {
            m_oGoosePub[nIndex].init();
        }
    }

    tmt_goose50_paras()
    {
        init();
    }

} tmt_Goose50Paras;

typedef struct tmt_goose50_manutest : public TMT_PARAS_HEAD
{
public:
    tmt_Goose50Paras   m_oGoose50Paras;

    void init()
    {
        strcpy(m_pszMacroID, STT_MACRO_ID_ManualTest);
#ifndef NOT_USE_TMT_TEST_PARAS_HEAD
        m_nVersion = 0x00010001;
        m_nTestState = 0;
#endif
        m_oGoose50Paras.init();
    }

    tmt_goose50_manutest()
    {
        init();
    }
} tmt_Goose50ManuTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas

void stt_init_paras(tmt_Goose50Paras *pParas);
void stt_xml_serialize(tmt_Goose50Paras *pParas, CSttXmlSerializeBase *pXmlSierialize);
