#pragma once

#include "tmt_common_def.h"
#include"../../SttTestBase/SttXmlSerialize.h"

//////////////////////////////////////////////////////////////////////////
// 递变测试相关参数

enum GRADIENTCHANNEL
{
    IA=0, IB, IC, IAIB, IBIC, ICIA, IAIBIC, IABC,/*0~7*/
    IA1, IB1, IC1, IA1IB1, IB1IC1, IC1IA1, IA1IB1IC1, IA1B1C1,/*8~15*/
    UA, UB, UC, UAUB, UBUC, UCUA, UAUBUC,/*16~22*/
    UA1, UB1, UC1, UA1UB1, UB1UC1, UC1UA1, UA1UB1UC1,/*23~29*/
};

typedef struct tmt_gradient_paras
{
public:
    float	m_fStart;
    float	m_fStop;
    float	m_fStep;
    float	m_fStepTime;
    float	m_fPrepareTime;
    float	m_fPreFaultTime;
    int		m_nTestMode;	//测试类型：0-动作值 1-返回系数 2-最大灵敏角
    int		m_nOutputType;	//输出方式：0-模拟量 1-数字量
    float	m_fVolAux;		// 辅助直流电压（仅模拟）
    float	m_fCurAux;		// 辅助直流电流（仅模拟）
    int		m_nBinLogic;			//0-或 1-与
    GRADIENTCHANNEL       m_nChannel;
    int       m_nType;
    float   m_fU;
    float   m_fI;
    float   m_fAngle0;
    float   m_fFreq;

    tmt_channel m_uiVOL[3][MAX_VOLTAGE_COUNT];	//(测试前+故障前+故障)*最大电压数
    tmt_channel m_uiCUR[3][MAX_CURRENT_COUNT];  
    //开关量

    tmt_BinaryIn  m_binIn[MAX_BINARYIN_COUNT];
    tmt_BinaryOut m_binOut[2][MAX_BINARYOUT_COUNT];	//0-非故障态开出 1-故障态开出

//    float	m_frTimeBinAct[MAX_BINARYIN_COUNT][64];		//每一个开入记录64次变位时间
//    float	m_frFlagBinAct[MAX_BINARYIN_COUNT][64];		//每一个开入记录64次变位时间
//    int		m_nrBinSwitchCount[MAX_BINARYIN_COUNT];

public:
    void init()
    {
        float fAngle[3] = {0, -120.0, 120.0};
        m_nChannel = IA;
        m_nType = 0;
        m_fStart = 0;
        m_fStop = 0;
        m_fStep = 0;
        m_fStepTime = 0;
        m_fPrepareTime = 0;
        m_fPreFaultTime = 0;
        m_nTestMode = 0;
        m_nOutputType = 0;
        m_fVolAux = 0;
        m_fCurAux = 0;
        m_nBinLogic = 0;
        m_fU = 57.74;
        m_fI = 0;
        m_fAngle0 = 0;
        m_fFreq = 50;
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<MAX_VOLTAGE_COUNT; j++)
            {
                m_uiVOL[i][j].Harm[1].fAmp = 57.74;
                m_uiCUR[i][j].Harm[1].fAmp = 0;
                m_uiVOL[i][j].Harm[1].fAngle = m_uiCUR[i][j].Harm[1].fAngle = fAngle[i%3];
            }
        }
//        for (int i=0;i<MAX_BINARYIN_COUNT;i++)
//        {
//            for (int j=0;j<64;j++)
//            {
//                m_frTimeBinAct[i][j] = 0;
//                m_frFlagBinAct[i][j] = 0;
//            }
//            m_nrBinSwitchCount[i] = 0;
//        }
    }

    tmt_gradient_paras()	{}
    virtual ~tmt_gradient_paras(){}
}tmt_GradientParas;

typedef struct tmt_gradient_result
{
public:
    float m_fTripValue;
    float m_fTripValueChl[MAX_BINARYIN_COUNT];
    float m_fReturnValue;
    float m_fReturnCoef;
    int     m_nAct;
    float m_fPhiAngleValue;

    void init()
    {
        m_fTripValue = 0;
        m_fReturnValue = 0;
        m_fReturnCoef = 0;
        m_nAct = 0;
        m_fPhiAngleValue = 0;
        for(int i=0; i<MAX_BINARYIN_COUNT; i++)
        {
            m_fTripValueChl[i] = 0;
        }
    }

    tmt_gradient_result()	{}
    virtual ~tmt_gradient_result(){}

    tmt_StepUI uiResult;
}tmt_GradientResult;

typedef struct tmt_gradient_test
{
public:
    tmt_GradientParas m_oGradientParas;
    tmt_GradientResult m_oResultParas;

    void init()
    {
        m_oGradientParas.init();
        m_oResultParas.init();
    }

    tmt_gradient_test()	{}
    virtual ~tmt_gradient_test(){}


}tmt_GradientTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas

void stt_xml_serialize_write_GradientTest();
void stt_init_paras(tmt_GradientParas *pParas);
void stt_init_results(tmt_GradientParas *pResults);
void stt_xml_serialize(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_GradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize);


