#pragma once

#include "tmt_common_def.h"
#include"../../SttTestBase/SttXmlSerialize.h"

// 手动测试相关参数
typedef struct tmt_manu_gradient
{
    int		nMode;	// 0:始值-终值  1:始值-终值-始值
    float	fStart;
    float	fEnd;
    float	fStep;
    float	fStepTime;
    float	fTrigDelay;
    int		nHarmIndex;

    void init()
    {
        nMode = 0;
        fStart=0;
        fEnd=0;
        fTrigDelay=0;
        fStep=0;
        fStepTime=0;
        nHarmIndex=0;
    }

    tmt_manu_gradient(){}
    virtual ~tmt_manu_gradient(){}
}tmt_ManuGradient;

typedef struct tmt_manual_paras
{
public:
    BOOL	m_bAging;		//是否老化试验
    BOOL	m_bAuto;
    BOOL	m_bDC;
    bool       m_bLockChanged;//lock mark
    float       m_fOutPutTime;	// 最长输出时间
    float	    m_fVolAux;		// 辅助直流电压（仅模拟）
    float	    m_fCurAux;		// 辅助直流电流（仅模拟）
    float       m_fOverloadDelaytime;	//过载延时  单位秒 功能：测试仪在开始输出的设定时间之，检测到过载不切断输出
    tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
    tmt_channel m_uiCUR[MAX_CURRENT_COUNT];
    //开关量
    int		m_nBinLogic;			//0-或 1-与
    tmt_BinaryIn     m_binIn[MAX_BINARYIN_COUNT];
    tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];
    int		 m_nGradientTpSelect;	// 递变类型选择
    int		 m_nGradientChSelect;	// 递变通道选择
    tmt_ManuGradient m_manuGradient;

public:
    void init()
    {
        float fAngle[3] = {0, -120.0, 120.0};
        m_bAging = false;
        m_bAuto = false;
        m_bDC = false;
        m_bLockChanged = false;
        m_fOutPutTime = 999;
        m_fVolAux = 0;
        m_fCurAux = 0;       
        m_fOverloadDelaytime = 10;
        m_nBinLogic = 0;                   
        m_nGradientChSelect = 0;
        m_nGradientTpSelect = 0;                
        m_manuGradient.init();
        for(int i=0; i<MAX_VOLTAGE_COUNT; i++)
        {
            m_uiVOL[i].Harm[1].fAmp = 57.74;
            m_uiCUR[i].Harm[1].fAmp = 0;
             m_uiVOL[i].Harm[1].fAngle = m_uiCUR[i].Harm[1].fAngle = fAngle[i%3];
        }
    }

    tmt_manual_paras()	{}
    virtual ~tmt_manual_paras() {}
}tmt_ManualParas;

typedef struct tmt_manual_result
{
public:
    unsigned  int m_nindex;		//序号
    unsigned   int m_nsecondtime;		// 时间组成 秒
    unsigned   int m_nnsecondtime;	// 时间组成 纳秒
    unsigned   int m_noactivetype;	// 类型
    unsigned   int m_nBinstate;		// 开入量
    unsigned   int m_nBinAllState;   // 开入量所有状态值
    unsigned   int m_nOverLoad;		// 过载后停止
    float        m_fuavalue;		// 电压实际输出值，用于计算大电压校正系数
    float        m_fubvalue;
    float        m_fucvalue;
    float        m_fuzvalue;

    //结果参数
    float	m_frTestTime;							//实际试验时间
    float	m_frTimeBinAct[MAX_BINARYIN_COUNT][64];		//每一个开入记录64次变位时间
    int		m_nrBinSwitchCount[MAX_BINARYIN_COUNT];
    int		m_nTripFlag;
    float	m_fTripTime;
    float	m_fActValue;
    float	m_fReturnValue;
    float   m_fReturnTime;

public:
    void init()
    {
        m_nindex = 0;
        m_nsecondtime = 0;
        m_nsecondtime = 0;
        m_noactivetype = 0;
        m_nBinstate = 0;
        m_nBinAllState = 0;
        m_nOverLoad = 0;
        m_fuavalue = 0;
        m_fubvalue = 0;
        m_fucvalue = 0;
        m_fuzvalue = 0;
        m_frTestTime = 0;
        m_nTripFlag = 0;
        m_fTripTime = 0;
        m_fActValue = 0;
        m_fReturnValue = 0;
        m_fReturnTime = 0;

        for (int i=0;i<MAX_BINARYIN_COUNT;i++)
        {
            for (int j=0;j<64;j++)
            {
                m_frTimeBinAct[i][j] = 0;
 //            m_frFlagBinAct[i][j] = 0;
            }
            m_nrBinSwitchCount[i] = 0;
        }
    }

    tmt_manual_result()	{}
    virtual ~tmt_manual_result() {}
}tmt_ManualResult;

typedef struct tmt_manual_test
{
public:
    tmt_ManualResult m_oManuResult;
    tmt_ManualParas   m_oManuParas;

    void init()
    {
        m_oManuResult.init();
        m_oManuParas.init();
    }
    tmt_manual_test() {}
    virtual ~tmt_manual_test() {}
}tmt_ManualTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas

void stt_xml_serialize_write_ManuTest();
void stt_init_paras(tmt_ManualParas *pParas);
void stt_init_results(tmt_ManualParas *pResults);
void stt_xml_serialize(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_ManualResult *pResults, CSttXmlSerializeBase *pXmlSierialize);


