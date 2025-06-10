#include "tmt_common_def.h"
#include "../../SttTestBase/SttXmlSerialize.h"
#include "tmt_test_paras_head.h"
#include "Abnormal/tmt_abnormal_test.h"

typedef struct tmt_short_time_over_para
{
public:
	int m_nInflictCount; //施加次数
	float m_fOnceInflictTime; //单次施加时间
	float m_fIntervalTime; //相邻施加间隔时间
	tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT]; //电压通道
	tmt_channel m_uiCUR[MAX_CURRENT_COUNT];//电流通道

public:
	void init()
	{
		m_nInflictCount = 1;
		m_fOnceInflictTime = 0;
		m_fIntervalTime = 0;

		float fAngle[3] = {0, -120.0, 120.0};
		for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
		{
			m_uiVOL[i].Harm[0].fAmp = 0;
			m_uiCUR[i].Harm[0].fAmp = 0;
			m_uiVOL[i].Harm[1].fAmp = 0;
			m_uiCUR[i].Harm[1].fAmp = 0;

			for(int harm = 0; harm < MAX_HARM_COUNT; harm++)
			{
				m_uiVOL[i].Harm[harm].init();
				m_uiCUR[i].Harm[harm].init();
			}

			m_uiVOL[i].Harm[1].fAngle = m_uiCUR[i].Harm[1].fAngle = fAngle[i % 3];
			m_uiVOL[i].Harm[1].fFreq = m_uiCUR[i].Harm[1].fFreq = 50;
		}
	}



	void CopyOwn(tmt_short_time_over_para *pDest)
	{

		pDest->m_nInflictCount = m_nInflictCount; 
		pDest->m_fOnceInflictTime = m_fOnceInflictTime;		
		pDest->m_fIntervalTime = m_fIntervalTime;		
	}

	tmt_short_time_over_para()
	{
		init();
	}

}tmt_ShortTimeOver_Para;

typedef struct tmt_short_time_over_paras
{
public:
	int m_nStateNumbers;

	tmt_ShortTimeOver_Para* m_pParaShortTimeOver;

	void init(long nStateNumbers)
	{
		if(m_pParaShortTimeOver == NULL)
		{
			m_pParaShortTimeOver = new tmt_ShortTimeOver_Para[g_nStateCount];
		}

		for (int i=0;i<nStateNumbers&&i<g_nStateCount;i++)
		{
			m_pParaShortTimeOver[i].init();
		}
	}

	tmt_short_time_over_paras(){
		m_pParaShortTimeOver = NULL;
	}

	virtual ~tmt_short_time_over_paras()
	{
		if (m_pParaShortTimeOver != NULL)
		{
			delete[] m_pParaShortTimeOver;
			m_pParaShortTimeOver = NULL;
		}
	}


}tmt_ShortTimeOver_Paras;

typedef struct tmt_short_time_over_results
{
public:
	/*tmt_ManualParas		m_oManuParas;
	tmt_ManualResult		m_oManuResult;*/

	void init()
	{

	}

}tmt_ShortTimeOver_Results;

typedef struct tmt_short_time_over_test : public TMT_PARAS_HEAD
{
public:
	tmt_short_time_over_paras   m_oShortTimeOverParas;
	tmt_short_time_over_results m_oShortTimeOverResults;

	void init(long nStateNumbers)
	{
		init_head(); 
		strcpy(m_pszMacroID, STT_MACRO_ID_ShortTimeOverTest);
#ifndef NOT_USE_TMT_TEST_PARAS_HEAD
		m_nVersion = 0x00010001;
		m_nTestState = 0;
#endif
		m_oShortTimeOverParas.init(nStateNumbers);
		m_oShortTimeOverParas.init(nStateNumbers);
	}

	tmt_short_time_over_test()
	{
		init(0);
	}

}tmt_ShortTimeOver_Test;


void stt_xml_serialize_write_ShortTimeOverTest();
void stt_init_paras(tmt_ShortTimeOver_Paras *pParas);
void stt_init_results(tmt_ShortTimeOver_Results *pResults);

void stt_xml_serialize(tmt_ShortTimeOver_Paras *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_ShortTimeOver_Results *pResults, CSttXmlSerializeBase *pXmlSierialize);
BOOL stt_xml_serialize(tmt_ShortTimeOver_Paras &oShortTimeOverPara, long nIndex, CSttXmlSerializeBase *pXmlSierialize,int nHarmCount = MAX_HARM_COUNT);

//void stt_xml_serialize(tmt_Channel *pChannel, const char *pszID, CSttXmlSerializeBase *pXmlSierialize,int nHarmCount = MAX_HARM_COUNT);
//CSttXmlSerializeBase *stt_xml_serialize(tmt_ShortTimeOver_Test *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum, long nCurRsNum);
void stt_xml_serialize(tmt_Channel *pChannel, const char *pszID, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_ex(tmt_ShortTimeOver_Para *pParas, CSttXmlSerializeBase *pXmlSierialize, long nIndex, long nVolRsNum, long nCurRsNum);
void stt_xml_serialize_ex2(tmt_ShortTimeOver_Paras *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum, long nCurRsNum);