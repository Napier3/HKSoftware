#pragma once
#include "tmt_common_def.h"
#include"../../SttTestBase/SttXmlSerialize.h"
#include "tmt_manu_test.h"

typedef tmt_ManuGradient tmt_HarmGradient;
typedef struct tmt_harm_paras
{
public:
    BOOL    m_bLock;
    BOOL	m_bAuto;
    int     m_nHarmMode;		//harm mode
    int		m_nGradientTpSelect;//递变类型选择
    int		m_nGradientChSelect;//递变通道选择
    float   m_fOutPutTime;		//最长输出时间
    float	m_fVolAux;			//辅助直流电压（仅模拟）
    float	m_fCurAux;			//辅助直流电流（仅模拟）
    float   m_fBaseFre;

	tmt_BinaryConfig m_oBinaryConfig;
    tmt_HarmGradient m_oHarmGradient;
    tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
    tmt_channel m_uiCUR[MAX_CURRENT_COUNT];

public:
    void init()
    {
        float fAngle[3] = {0, -120.0, 120.0};
		m_bLock = false;
        m_bAuto = false;
		m_fBaseFre=50;
        m_fOutPutTime = 999;
        m_fVolAux = 0;
        m_fCurAux = 0;
        m_nGradientChSelect = 0;
        m_nGradientTpSelect = 0;
        m_oHarmGradient.init();
		m_oBinaryConfig.init();

        for(int i=0; i<MAX_VOLTAGE_COUNT; i++)
        {
			m_uiVOL[i].Harm[1].fAmp = 0;
            m_uiCUR[i].Harm[1].fAmp = 0;
            m_uiVOL[i].Harm[1].fAngle = m_uiCUR[i].Harm[1].fAngle = fAngle[i%3];
			m_uiVOL[i].Harm[0].fAmp = m_uiCUR[i].Harm[0].fAmp=0;
            for(int j=2; j<32; j++)
            {
                m_uiVOL[i].Harm[j].fAngle = m_uiCUR[i].Harm[j].fAngle = fAngle[i%3];
                m_uiVOL[i].Harm[j].fAmp = m_uiCUR[i].Harm[j].fAmp = 0;
            }
        }
    }

	void setBaseAmp(float fAmp)
	{
		for(int i=0; i<MAX_VOLTAGE_COUNT; i++)
		{
			m_uiVOL[i].Harm[1].fAmp = fAmp;
		}
	}

	void setBaseFree(float fFre)
	{
		int i=0;
		int j=1;

		m_fBaseFre = fFre;
		for(i=0; i<MAX_VOLTAGE_COUNT; i++)
		{
			for (j=1; j<MAX_HARM_COUNT; j++)
			{
				m_uiVOL[i].Harm[j].fFreq = fFre * j;
			}	
		}
		for(i=0; i<MAX_CURRENT_COUNT; i++)
		{
			for (j=1; j<MAX_HARM_COUNT; j++)
			{
				m_uiCUR[i].Harm[j].fFreq = fFre * j;
			}	
		}
	}
	void InitHarmGradient(bool bType_U)
	{
		m_oHarmGradient.fStart = 0;
		m_oHarmGradient.fStep = 0.5;
		m_oHarmGradient.fStepTime = 0.5;

		if (bType_U)
		{
			m_oHarmGradient.fEnd = 10;
		}
		else
		{
			m_oHarmGradient.fEnd = 5;
		}
	}

    tmt_harm_paras()	
	{
		init();
	}
    virtual ~tmt_harm_paras() {}
}tmt_HarmParas;

typedef struct tmt_harm_result
{
public:
    int		m_nTripFlag;
    float	m_fTripTime;
    float	m_fActValue;

public:
    void init()
    {
        m_nTripFlag = 0;
        m_fTripTime = 0;
        m_fActValue = 0;
    }

    tmt_harm_result()	
	{	
		init();	
	}
    virtual ~tmt_harm_result() {}
}tmt_HarmResult;

typedef struct tmt_harm_test
{
public:
    tmt_HarmResult  m_oHarmResult;
    tmt_HarmParas   m_oHarmParas;

    void init()
    {
        m_oHarmResult.init();
        m_oHarmParas.init();
    }

    tmt_harm_test() 
	{	
		init();	
	}
    virtual ~tmt_harm_test() {}
}tmt_HarmTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas

void stt_xml_serialize_write_HarmTest();
void stt_init_paras(tmt_HarmParas *pParas);
void stt_init_results(tmt_HarmResult *pResults);
void stt_xml_serialize(tmt_HarmParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_HarmResult *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_ex(tmt_HarmParas *pParas, CSttXmlSerializeBase *pXmlSierialize, bool bSel);


