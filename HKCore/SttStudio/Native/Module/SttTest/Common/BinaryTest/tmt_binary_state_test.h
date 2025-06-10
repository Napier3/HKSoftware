#pragma once
#include"../tmt_state_test.h"

typedef struct tmt_binary_state_result
{
public://试验结果
    long    m_nCurLoopIndx;//当前状态号
    long    m_nCurStateIndx;//当前状态号
    long    m_nBinAct;
    int		m_nrBinSwitchCount[MAX_BINARYIN_COUNT];
    int     m_nBinFirstChgState[MAX_BINARYIN_COUNT];//第一次变位时的开入状态值(0:断开;1:闭合)
    float	m_frTimeBinAct[MAX_BINARYIN_COUNT][64];		//每一个开入记录64次变位时间

    int		m_nrBinExSwitchCount[MAX_ExBINARY_COUNT];
    int     m_nBinExFirstChgState[MAX_ExBINARY_COUNT];//变位时的开入状态值(0:断开;1:闭合)
    float	m_frTimeBinExAct[MAX_ExBINARY_COUNT][64];		//每一个开入记录64次变位时间
    void init()
    {
        m_nCurLoopIndx = 0;
        m_nCurStateIndx = 0;
        m_nBinAct = 0;

        for(int i = 0; i < MAX_BINARYIN_COUNT; i++)
        {
            for(int j = 0; j < 64; j++)
            {
                m_frTimeBinAct[i][j] = 0;
            }

            m_nBinFirstChgState[i] = 0;
            m_nrBinSwitchCount[i] = 0;
        }

        for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
        {
            for(int j = 0; j < 64; j++)
            {
                m_frTimeBinExAct[i][j] = 0;
            }

            m_nBinExFirstChgState[i] = 0;
            m_nrBinExSwitchCount[i] = 0;
        }
    }

    tmt_binary_state_result()
    {
        init();
    }
    virtual ~tmt_binary_state_result() {}
} tmt_BinaryStateResult;

typedef struct tmt_binary_state_results
{
public:
    long m_nrBinSwitchTotalCount[MAX_BINARYIN_COUNT];
    long m_nresultCount;
    tmt_BinaryStateResult  *m_resultState;

    void init()
    {
        m_nresultCount = 0;

        if(m_resultState == NULL)
        {
            m_resultState = new tmt_BinaryStateResult[100];
        }

        for(int i = 0; i < 100; i++)
        {
            m_resultState[i].init();
        }
    }

    tmt_binary_state_results()
    {
        m_resultState = NULL;
    }
    virtual ~tmt_binary_state_results()
    {
        if(m_resultState != NULL)
        {
            delete[] m_resultState;
            m_resultState = NULL;
        }
    }
} tmt_BinaryStateResults;

typedef struct tmt_binary_state_test : public TMT_PARAS_HEAD
{
public:
	tmt_StateParas       m_oStateParas;
    tmt_BinaryStateResults   m_oStateResults;

    void init(long nStateNumbers)
    {
        init_head();
        strcpy(m_pszMacroID, STT_MACRO_ID_BinaryStateTest);
#ifndef NOT_USE_TMT_TEST_PARAS_HEAD
        m_nVersion = 0x00010001;
        m_nTestState = 0;
#endif
        m_oStateParas.init(nStateNumbers);
        m_oStateResults.init();
    }

    tmt_binary_state_test()
    {
        init(0);
    }
} tmt_BinaryStateTest;

extern long g_nBinaryStateTestMode;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_BinaryState(tmt_StatePara &oStatePara, long nIndex, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_BinaryStates(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_BinaryStateResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_BinaryState_act_rcd(tmt_BinaryStateResult *pResult, CSttXmlSerializeBase *pXmlSierialize);

