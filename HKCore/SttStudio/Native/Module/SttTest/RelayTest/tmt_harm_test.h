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
    int          m_nHarmMode;//harm mode
    int		    m_nBinLogic;			//0-或 1-与
    int		 m_nGradientTpSelect;	// 递变类型选择
    int		 m_nGradientChSelect;	// 递变通道选择
    float      m_fOutPutTime;	// 最长输出时间
    float	    m_fVolAux;		// 辅助直流电压（仅模拟）
    float	    m_fCurAux;		// 辅助直流电流（仅模拟）
    float       m_fBaseFre;
    tmt_BinaryIn     m_binIn[MAX_BINARYIN_COUNT];
    tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];
    tmt_HarmGradient m_oHarmGradient;
    tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
    tmt_channel m_uiCUR[MAX_CURRENT_COUNT];

public:
    void init()
    {
        float fAngle[3] = {0, -120.0, 120.0};
        m_bAuto = false;
		m_fBaseFre=50;
        m_fOutPutTime = 999;
        m_fVolAux = 0;
        m_fCurAux = 0;
        m_nBinLogic = 0;
        m_nGradientChSelect = 0;
        m_nGradientTpSelect = 0;
        m_oHarmGradient.init();
        for(int i=0; i<MAX_VOLTAGE_COUNT; i++)
        {
            m_uiVOL[i].Harm[1].fAmp = 57.74;
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

    tmt_harm_paras()	
	{
		init();
	}
    virtual ~tmt_harm_paras() {}
}tmt_HarmParas;

typedef struct tmt_auto_para
{
	bool m_bAuto;		//是否自动
	int m_nChanel;		//通道选择
	int m_nHarmIndex;	//谐波索引
	float m_fStep;		//变化步长
	float m_fStart;		//变化开始值
	float m_fEnd;		//变化终值
	float m_fTime;		//变化时间
	int m_nHz;			//基波频率

	tmt_auto_para()
	{
		init();
	}

	void init()
	{
		m_bAuto = false;
		m_nChanel = 0;
		m_nHarmIndex = 0;
		m_fStep = 0.5;
		m_fStart = 0;
		m_fEnd = 10;
		m_fTime = 0.5;
		m_nHz = 50;
	}

	tmt_auto_para &operator = (const tmt_auto_para &right)
	{
		m_bAuto = right.m_bAuto;
		m_nChanel = right.m_nChanel;
		m_nHarmIndex = right.m_nHarmIndex;
		m_fStep = right.m_fStep;
		m_fStart = right.m_fStart;
		m_fEnd = right.m_fEnd;
		m_fTime = right.m_fTime;
		m_nHz = right.m_nHz;

		return *this;
	}
}tmt_AutoPara;

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

    tmt_harm_result()	{}
    virtual ~tmt_harm_result() {}
}tmt_HarmResult;

typedef struct tmt_harm_test
{
public:
    tmt_HarmResult  m_oHarmResult;
    tmt_HarmParas    m_oHarmParas;

    void init()
    {
        m_oHarmResult.init();
        m_oHarmParas.init();
    }
    tmt_harm_test() {}
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


