#pragma once

#include "../tmt_common_def.h"
#include "../tmt_state_test.h"

typedef struct tmt_prim_freq_state_para :public tmt_state_para
{
public:
	float	m_frCurrentDc[2];//直流信号源

    void init()
	{
		tmt_state_para::init();
		m_frCurrentDc[0] = 0.0f;
		m_frCurrentDc[1] = 0.0f;
	}

    tmt_prim_freq_state_para()
	{	
		init(); 
	}
}tmt_PrimFreqStatePara;

typedef struct tmt_prim_freq_state_result:public tmt_state_result
{
    void init()
    {
		tmt_state_result::init();
    }

    tmt_prim_freq_state_result()	
	{ 
		init(); 
	}
    virtual ~tmt_prim_freq_state_result(){}
}tmt_PrimFreqStateResult;

typedef struct tmt_prim_freq_state_paras :public tmt_state_paras
{
public:
#ifdef TMT_STATECOUNT_USE_DEF
	tmt_PrimFreqStatePara       m_paraPrimFreqState[STATE_MAX_COUNT];
#else
	tmt_PrimFreqStatePara*       m_paraPrimFreqState;
#endif

	void init(long nStateNumbers)
	{
#ifdef TMT_STATECOUNT_USE_DEF
#else
		if (g_nStateCount > m_nStateCount)
		{
			//2024-9-11 lijunqing 优化
			if (m_paraPrimFreqState != NULL)
			{
				delete []m_paraPrimFreqState;
				m_paraPrimFreqState = NULL;
			}	
		}

		if(m_paraPrimFreqState == NULL)
		{
			//2024-9-11 lijunqing 优化
			m_paraPrimFreqState = new tmt_PrimFreqStatePara[g_nStateCount];
		}

#endif

		for (int i=0;i<nStateNumbers&&i<g_nStateCount;i++)
		{
			m_paraPrimFreqState[i].init();
		}

		m_nStateCount = g_nStateCount;
	}

    tmt_prim_freq_state_paras()
	{
		tmt_state_paras();
	}

	virtual ~tmt_prim_freq_state_paras()
	{

	}
}tmt_PrimFreqStateParas;

typedef struct tmt_prim_freq_state_results: public tmt_state_results
{

#ifdef TMT_STATECOUNT_USE_DEF
	tmt_PrimFreqStateResult  m_resultState[STATE_MAX_COUNT];
#else
	tmt_PrimFreqStateResult*  m_resultState;
#endif

    tmt_prim_freq_state_results()
	{
#ifdef TMT_STATECOUNT_USE_DEF
#else
		m_resultState = NULL;
#endif
		m_nStateCount = 0;
	}
    virtual ~tmt_prim_freq_state_results()
	{
#ifdef TMT_STATECOUNT_USE_DEF
#else
		if (m_resultState != NULL)
		{
            delete[] m_resultState;
			m_resultState = NULL;
		}
#endif
	}
}tmt_PrimFreqStateResults;

typedef struct tmt_prim_freq_state_test : public TMT_PARAS_HEAD
{
public:
    tmt_PrimFreqStateParas       m_oStateParas;
    tmt_PrimFreqStateResults   m_oStateResults;

    void init(long nStateNumbers)
    {
		init_head(); 
		strcpy(m_pszMacroID, STT_MACRO_ID_PrimFreqStateTest);
#ifndef NOT_USE_TMT_TEST_PARAS_HEAD
		m_nVersion = 0x00010001;
		m_nTestState = 0;
#endif
        m_oStateParas.init(nStateNumbers);
        m_oStateResults.init(nStateNumbers);
    }

	tmt_prim_freq_state_test()	{init(0);}
}tmt_PrimFreqStateTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief st t_init_paras
/// \param pParas
///
///
void stt_xml_serialize_write_PrimFreqStateTest();
void stt_xml_serialize(tmt_PrimFreqStateParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_PrimFreqStateResults *pResults,tmt_PrimFreqStateParas *pStateParas,int nStateNums, CSttXmlSerializeBase *pXmlSierialize,int nBinTripRef);
void stt_xml_serialize_ex(tmt_channel *pChannel, const char *pszID, CSttXmlSerializeBase *pXmlSierialize, const char *pszDataTypeID);

void stt_xml_serialize(tmt_PrimFreqStatePara &oStatePara, long nIndex, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_ex(tmt_PrimFreqStatePara &oStatePara, long nIndex, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_ex(tmt_PrimFreqStateParas *pParas, CSttXmlSerializeBase *pXmlSierialize,bool bSel);
void stt_xml_serialize_ex2(tmt_PrimFreqStateParas *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum,long nCurRsNum,bool bSel);

tmt_PrimFreqStatePara* stt_prim_freq_state_paras_insert_after(tmt_PrimFreqStateParas *pParas, tmt_PrimFreqStatePara *pSrc, int nAfter);
tmt_PrimFreqStatePara* stt_prim_freq_state_paras_insert_before(tmt_PrimFreqStateParas *pParas, tmt_PrimFreqStatePara *pSrc, int nBefore);
void stt_prim_freq_state_paras_delete(tmt_PrimFreqStateParas *pParas, int nIndex);
void stt_xml_serialize_act_rcd(tmt_PrimFreqStateResult *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_common(tmt_PrimFreqStateParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_common(tmt_PrimFreqStateResults *pResults, BOOL *bUseErr, CSttXmlSerializeBase *pXmlSierialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_PrimFreqStateTest *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum,long nCurRsNum);

void stt_xml_serialize_binary_in(tmt_PrimFreqStatePara &oStatePara, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_binary_out(tmt_PrimFreqStatePara &oStatePara, CSttXmlSerializeBase *pXmlSierialize);
