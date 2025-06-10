#pragma once

#include "../tmt_common_def.h"
#include "../tmt_manu_test.h"
#include"../../../SttTestBase/SttXmlSerialize.h"

//2021-5-30  lijunqing
#include "../tmt_test_paras_head.h"

typedef struct tmt_binary_manual_paras
{
public:
	BOOL    m_bBinStop;//开入停止,接收UpdateParameter时底层更新变量
    //开关量
    int		m_nBinLogic;			//0-或 1-与
    tmt_BinaryIn    m_binIn[MAX_BINARYIN_COUNT];
    tmt_BinaryOut   m_binOut[MAX_BINARYOUT_COUNT];
    tmt_BinaryIn    m_binInEx[MAX_ExBINARY_COUNT];//系统扩展开关量
    tmt_BinaryOut	m_binOutEx[MAX_ExBINARY_COUNT];//系统扩展开关量

    //GoosePub
    tmt_GoosePub m_oGoosePub[MAX_MODULES_GOOSEPUB_COUNT];

public:
    void init()
	{
		m_bBinStop = FALSE;
		m_nBinLogic = 0;
        for(int j = 0; j < MAX_BINARYIN_COUNT; j++)
        {
            m_binIn[j].nSelect = 0;
            m_binIn[j].nTrigMode = 0;
#ifndef _PSX_QT_LINUX_

            if(j < g_nBinCount)
            {
                m_binIn[j].nSelect = 1;
            }

#endif
        }

        for(int j = 0; j < MAX_BINARYOUT_COUNT; j++)
        {
            m_binOut[j].nState = 0;
            m_binOut[j].nMode = 0;
            m_binOut[j].fTimeTrig = 0;
            m_binOut[j].fHoldTime = 0;
        }

        for(int j = 0; j < g_nBinExCount && j < MAX_ExBINARY_COUNT; j++)
        {
            m_binInEx[j].nSelect = 0;//默认扩增开入不选中
            m_binInEx[j].nTrigMode = 0;
        }

        for(int j = 0; j < g_nBoutExCount && j < MAX_ExBINARY_COUNT; j++)
        {
            m_binOutEx[j].nState = 0;//默认扩增开出全断开
            m_binOutEx[j].nMode = 0;
            m_binOutEx[j].fTimeTrig = 0;
            m_binOutEx[j].fHoldTime = 0;
        }

        for(int nIndex = 0; nIndex < MAX_MODULES_GOOSEPUB_COUNT; nIndex++)
        {
            m_oGoosePub[nIndex].init();
        }
    }

	tmt_binary_manual_paras()
    {
        init();
    }

} tmt_BinaryManualParas;

typedef struct tmt_binary_manual_test : public TMT_PARAS_HEAD
{
public:
	tmt_BinaryManualParas   m_oManuParas;

    void init()
    {
		strcpy(m_pszMacroID, STT_MACRO_ID_BinaryManuTest);
#ifndef NOT_USE_TMT_TEST_PARAS_HEAD
        m_nVersion = 0x00010001;
        m_nTestState = 0;
#endif
        m_oManuParas.init();
    }

	tmt_binary_manual_test()
    {
        init();
    }
} tmt_BinaryManualTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas

void stt_xml_serialize_write_BinaryManuTest();
void stt_xml_serialize(tmt_BinaryManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_BinaryManual(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize);

