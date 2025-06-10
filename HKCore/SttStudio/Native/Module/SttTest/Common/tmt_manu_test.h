#pragma once

#include "tmt_common_def.h"
#include"../../SttTestBase/SttXmlSerialize.h"

//2021-5-30  lijunqing
#include "tmt_test_paras_head.h"


#define   TMT_MANU_FUNC_TYPE_Common                                0 //手动试验功能类别  0代表一般的手动试验
#define   TMT_MANU_FUNC_TYPE_MUAccuracy                            1 //手动试验功能类别  1代表合并单元精度测试
//#define   TMT_MANU_FUNC_TYPE_MUZeroDrift                           2 //手动试验功能类别  2代表合并单元零漂测试
#define	  TMT_MANU_FUNC_TYPE_MUFirstCycleWave					   2 //手动试验功能类别  2代表合并单元首周波测试
#define   TMT_MANU_FUNC_TYPE_MUTimingAccur                         3 //手动试验功能类别  3代表合并单元对时精度测试
#define   TMT_MANU_FUNC_TYPE_MUPunctAccur                          4 //手动试验功能类别  4代表合并单元守时精度测试



// 手动测试相关参数
typedef struct tmt_manu_gradient
{
    int		nMode;	// 0:始值-终值  1:始值-终值-始值
    float	fStart;
    float	fEnd;
    float	fStep;
    float	fStepTime;
    float	fTrigDelay;
    int		nHarmIndex;	//变化谐波次数 1为基波

    void init()
    {
        nMode = 0;
        fStart = 1;
        fEnd = 10;
        fTrigDelay = 0;
        fStep = 0.5;
        fStepTime = 1;
        nHarmIndex = 1;
    }

    tmt_manu_gradient()
    {
        init();
    }
} tmt_ManuGradient;

typedef struct tmt_mu_paras
{
    int		nAlgorithmType;	// 0:插值法  1:同步法
    int		nPPS_SetType;	// 0:上升沿有效  1:下降沿有效 2:无PPS
    float	fUn;//额定电压-用于零漂计算
    float	fIn;//额定电流-用于零漂计算
    long   nSynTime;//守时精度测试时,开始测试后,先同步该时间后,自动切断同步信号
	//zhouhj 2023.10.13 删除
 //   float   fDelayCompens_NoPPS;//无PPS模式下的延时补偿值
	int   m_nUseSetRpt;//是否使用自定义报告方式,即指定报告次数和每次的时间
	int   m_nMaxTestCount;//最大测试次数
	float  m_fTimeOneCount;//每次的时间


    void init()
    {
        nAlgorithmType = 0;
        nPPS_SetType = 0;
        fUn = 57.74f;
        fIn = 1.0;
        nSynTime = 2;
//        fDelayCompens_NoPPS = 0.0f;
		m_nUseSetRpt = 0;
		m_nMaxTestCount = 10;//
		m_fTimeOneCount = 0.5f;
    }

    tmt_mu_paras()
    {
        init();
    }
} tmt_MuParas;

typedef struct tmt_manual_paras
{
public:
    BOOL    m_bBinStop;//开入停止,接收UpdateParameter时底层更新变量
    BOOL	m_bAging;		//是否老化试验
    BOOL	m_bAuto;
    BOOL	m_bDC;
    BOOL       m_bLockChanged;//lock mark
	BOOL	m_bResultAddBin;
    float       m_fOutPutTime;	// 最长输出时间
    float	    m_fVolAux;		// 辅助直流电压（仅模拟）
    float	    m_fCurAux;		// 辅助直流电流（仅模拟）
//	float       m_fOverloadDelaytime;	//过载延时  单位秒 功能：测试仪在开始输出的设定时间之，检测到过载不切断输出
    tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
    tmt_channel m_uiCUR[MAX_CURRENT_COUNT];
    //开关量
    int		m_nBinLogic;			//0-或 1-与
    tmt_BinaryIn    m_binIn[MAX_BINARYIN_COUNT];
    tmt_BinaryOut   m_binOut[MAX_BINARYOUT_COUNT];
    tmt_BinaryIn    m_binInEx[MAX_ExBINARY_COUNT];//系统扩展开关量
    tmt_BinaryOut	m_binOutEx[MAX_ExBINARY_COUNT];//系统扩展开关量
    int		 m_nGradientTpSelect;	// 递变类型选择
    int		 m_nGradientChSelect;	// 递变通道选择
	int	     m_nVarIndexType;//0=电流 1=电压 2=频率
    tmt_ManuGradient m_manuGradient;

    //GoosePub
    tmt_GoosePub m_oGoosePub[MAX_MODULES_GOOSEPUB_COUNT];
    //Ft3Pub
    tmt_Ft3Pub m_oFt3Pub[MAX_MODULES_FT3PUB_COUNT];
    //2M
    tmt_2MOnePortPub m_o2MOnePortPub[MAX_2M_BLOCKS_COUNT];
    int            m_nFuncType;//功能类别  0-常规手动试验  1-MU精度测试  2-MU零漂测试   3-对时精度测试      4-守时精度测试
    int            m_nSelHarm;//选择叠加谐波
    int            m_nHarmIndex;// 选择叠加谐波的Index  2-2次谐波    3-3次谐波
//	int            m_nUploadRpt_Started;//开始测试时,是否上送报告
    tmt_MuParas    m_oMuParas;//合并单元测试相关参数

	//整定值
	float m_fTimeSet;   //动作整定时间
	float m_fUSet;		//电压整定动作值
	float m_fISet;		//电流整定动作值
	float m_fAngleSet;	//相位整定动作值
	float m_fHzSet;		//频率整定动作值
	float m_fRetCoefSet; //返回系数整定值
	

	//评估
	float m_fTimeValue_AbsErr;      //动作时间值绝对误差
	float m_fTimeValue_RelErr;      //动作时间值相对误差
	long m_nTimeValue_ErrorLogic; 	//动作时间误差判断逻辑 
	float m_fUActVal_AbsErr; 		//电压动作值绝对误差
	float m_fUActVal_RelErr; 		//电压动作值相对误差 		
	long m_nUActVal_ErrorLogic; 	//电压动作值误差判断逻辑 	
	float m_fIActVal_AbsErr; 		//电流动作值绝对误差 		
	float m_fIActVal_RelErr; 		//电流动作值相对误差 		
	long m_nIActVal_ErrorLogic; 	//电流动作值误差判断逻辑 	
	float m_fAngleActVal_AbsErr; 	//相位动作值绝对误差 		
	float m_fAngleActVal_RelErr; 	//相位动作值相对误差 		
	long m_nAngleActVal_ErrorLogic; //相位动作值误差判断逻辑 	
	float m_fHzActVal_AbsErr; 		//频率动作值绝对误差 		
	float m_fHzActVal_RelErr; 		//频率动作值相对误差 		
	long m_nHzActVal_ErrorLogic; 	//频率动作值误差判断逻辑 	
	float m_fRetCoef_AbsErr; 		//返回系数绝对误差 		
	float m_fRetCoef_RelErr;		//返回系数相对误差 		
	long m_nRetCoef_ErrorLogic; 	//返回系数误差判断逻辑 	

public:
    void init()
    {
        m_bBinStop = FALSE;
        float fAngle[3] = {0, -120.0, 120.0};
        m_bAging = false;
        m_bAuto = false;
        m_bDC = false;
        m_bLockChanged = false;
		m_bResultAddBin = FALSE;
        m_fOutPutTime = 0.000001f;
//		m_nUploadRpt_Started = 0;
        m_fVolAux = 0;
        m_fCurAux = 0;
//		m_fOverloadDelaytime = 0;
        m_nBinLogic = 0;
        m_nGradientChSelect = 0;
        m_nGradientTpSelect = 0;
		m_nVarIndexType = 0;
        m_nFuncType = TMT_MANU_FUNC_TYPE_Common;
        m_nSelHarm = 0;
        m_nHarmIndex = 2;
        m_oMuParas.init();
        m_manuGradient.init();

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

        for(int nIndex = 0; nIndex < MAX_MODULES_FT3PUB_COUNT; nIndex++)
        {
            m_oFt3Pub[nIndex].init();
        }

        for(int nIndex = 0; nIndex < MAX_2M_BLOCKS_COUNT; nIndex++)
        {
            m_o2MOnePortPub[nIndex].init();
        }

		m_fTimeSet =0; 
		m_fUSet=0;		
		m_fISet=0;		
		m_fAngleSet=0;	
		m_fHzSet=0;		
		m_fRetCoefSet=0;

		m_fTimeValue_AbsErr = 0.001f;
		m_fTimeValue_RelErr = 0.1f;
		m_nTimeValue_ErrorLogic = 0;
		m_fUActVal_AbsErr = 0.001f;
		m_fUActVal_RelErr = 0.1f;	
		m_nUActVal_ErrorLogic = 0;
		m_fIActVal_AbsErr = 0.001f; 				
		m_fIActVal_RelErr = 0.1f; 		
		m_nIActVal_ErrorLogic = 0; 	
		m_fAngleActVal_AbsErr = 0.001f; 			
		m_fAngleActVal_RelErr = 0.1f; 		
		m_nAngleActVal_ErrorLogic = 0; 
		m_fHzActVal_AbsErr = 0.001f; 		
		m_fHzActVal_RelErr = 0.1f; 		 		
		m_nHzActVal_ErrorLogic = 0; 	
		m_fRetCoef_AbsErr = 0.001f; 			
		m_fRetCoef_RelErr = 0.1f;				
		m_nRetCoef_ErrorLogic = 0; 
    }

    void InitManuGradient(bool bType_U)
    {
        m_manuGradient.fStart = 0;
        m_manuGradient.fStep = 0.5;
        m_manuGradient.fStepTime = 0.5;

        if(bType_U)
        {
            m_manuGradient.fEnd = 10;
        }
        else
        {
            m_manuGradient.fEnd = 5;
        }
    }

    void setDC(bool bDC, bool bUpdateAngleFre = false)
    {
        m_bDC = bDC;
        float fAngle[3] = {0, -120.0, 120.0};

        for(int j = 0; j < MAX_VOLTAGE_COUNT; j++)
        {
            m_uiVOL[j].Harm[1].bDC = bDC;

            if(bUpdateAngleFre)
            {
                if(bDC)
                {
                    m_uiVOL[j].Harm[1].fAngle = 0;
                    m_uiVOL[j].Harm[1].fFreq = 0;
                }
                else
                {
                    m_uiVOL[j].Harm[1].fFreq = 50;
                    m_uiVOL[j].Harm[1].fAngle = fAngle[j % 3];
                }
            }
        }

        for(int j = 0; j < MAX_CURRENT_COUNT; j++)
        {
            m_uiCUR[j].Harm[1].bDC = bDC;

            if(bUpdateAngleFre)
            {
                if(bDC)
                {
                    m_uiCUR[j].Harm[1].fAngle = 0;
                    m_uiCUR[j].Harm[1].fFreq = 0;
                }
                else
                {
                    m_uiCUR[j].Harm[1].fFreq = 50;
                    m_uiCUR[j].Harm[1].fAngle = fAngle[j % 3];
                }
            }
        }
    }
	void CopyOwn(tmt_manual_paras *pDest)
	{

		pDest->m_fTimeSet =m_fTimeSet; 
		pDest->m_fUSet=m_fUSet;		
		pDest->m_fISet=m_fISet;		
		pDest->m_fAngleSet=m_fAngleSet;	
		pDest->m_fHzSet=m_fHzSet;		
		pDest->m_fRetCoefSet=m_fRetCoefSet;

		pDest->m_fTimeValue_AbsErr = m_fTimeValue_AbsErr;
		pDest->m_fTimeValue_RelErr = m_fTimeValue_RelErr;
		pDest->m_nTimeValue_ErrorLogic = m_nTimeValue_ErrorLogic;
		pDest->m_fUActVal_AbsErr = m_fUActVal_AbsErr;
		pDest->m_fUActVal_RelErr = m_fUActVal_RelErr;
		pDest->m_nUActVal_ErrorLogic = m_nUActVal_ErrorLogic;
		pDest->m_fIActVal_AbsErr = m_fIActVal_AbsErr;
		pDest->m_fIActVal_RelErr = m_fIActVal_RelErr;
		pDest->m_nIActVal_ErrorLogic = m_nIActVal_ErrorLogic;
		pDest->m_fHzActVal_AbsErr = m_fHzActVal_AbsErr;	
		pDest->m_fHzActVal_RelErr = m_fHzActVal_RelErr;	
		pDest->m_nHzActVal_ErrorLogic = m_nHzActVal_ErrorLogic;
		pDest->m_fAngleActVal_AbsErr = m_fAngleActVal_AbsErr;
		pDest->m_fAngleActVal_RelErr = m_fAngleActVal_RelErr;
		pDest->m_nAngleActVal_ErrorLogic = m_nAngleActVal_ErrorLogic; 
		pDest->m_fRetCoef_AbsErr = m_fRetCoef_AbsErr; 	
		pDest->m_fRetCoef_RelErr = m_fRetCoef_RelErr;	
		pDest->m_nRetCoef_ErrorLogic = m_nRetCoef_ErrorLogic;

		pDest->m_nVarIndexType = m_nVarIndexType;

	}


    void SetFundFreq(float fFreqValue)
    {
        for(int j = 0; j < MAX_VOLTAGE_COUNT; j++)
        {
            m_uiVOL[j].Harm[1].fFreq = fFreqValue;
            m_uiCUR[j].Harm[1].fFreq = fFreqValue;
        }
    }

    tmt_manual_paras()
    {
        init();
    }

} tmt_ManualParas;

typedef struct tmt_mu_time_result//20220806 zhouhj 增加用于合并单元对时、守时精度测试返回报告
{
public:
    float m_fHasUsingTime;//已使用实际时间长度,同步时长/守时时长(单位:s)
    float m_fCurrErrTime;//当前误差时间(单位:μs)
    float m_fMaxErrTime;//最大误差时间(单位:μs)
    float m_fMinErrTime;//最小误差时间(单位:μs)
    float m_fAverageErrTime;//平均误差时间(单位:μs)
    long  m_nTimeTestResult;//MU时间精度测试结果,判断是否合格

    void init()
    {
        m_fHasUsingTime = 0.00f;
        m_fCurrErrTime = 0.00f;
        m_fMaxErrTime = 0.00f;
        m_fMinErrTime = 0.00f;
        m_fAverageErrTime = 0.00f;
        m_nTimeTestResult = 0;
    }

    void CopyOwn(tmt_mu_time_result *pDest)
    {
        pDest->m_fHasUsingTime = m_fHasUsingTime;
        pDest->m_fCurrErrTime = m_fCurrErrTime;
        pDest->m_fMaxErrTime = m_fMaxErrTime;
        pDest->m_fMinErrTime = m_fMinErrTime;
        pDest->m_fAverageErrTime = m_fAverageErrTime;
        pDest->m_nTimeTestResult = m_nTimeTestResult;
    }

    tmt_mu_time_result()
    {
        init();
    }
} tmt_MuTimeResult;

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
    int		m_nrBinSwitchCount[MAX_BINARYIN_COUNT]; //变位次数
    float	m_frTimeBinExAct[MAX_ExBINARY_COUNT][64];		//每一个开入记录64次变位时间
    int		m_nrBinExSwitchCount[MAX_ExBINARY_COUNT]; //变位次数
    int		m_nTripFlag; //0,1
    float	m_fTripTime;		//实际试验时间
    float	m_fActValue;
    float	m_fReturnValue;
    float   m_fReturnCoef;
    float   m_fReturnTime;

    tmt_MuTimeResult m_oMuTimeRlt;//20220806 zhouhj 增加用于合并单元对时、守时精度测试返回报告

public:
    virtual void init()
    {
        m_nindex = 0;
        m_nsecondtime = 0;
        m_nnsecondtime = 0;
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
        m_fReturnCoef = 0;
        m_fReturnTime = 0;
        m_oMuTimeRlt.init();

        for(int i = 0; i < MAX_BINARYIN_COUNT; i++)
        {
            for(int j = 0; j < 64; j++)
            {
                m_frTimeBinAct[i][j] = 0;
            }

            m_nrBinSwitchCount[i] = 0;
        }

        for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
        {
            for(int j = 0; j < 64; j++)
            {
                m_frTimeBinExAct[i][j] = 0;
            }

            m_nrBinExSwitchCount[i] = 0;
        }
    }

    void CopyOwn(tmt_manual_result *pDest)
    {
        pDest->m_nindex = m_nindex;
        pDest->m_nsecondtime = m_nsecondtime;
        pDest->m_nnsecondtime = m_nnsecondtime;
        pDest->m_noactivetype = m_noactivetype;
        pDest->m_nBinstate = m_nBinstate;
        pDest->m_nBinAllState = m_nBinAllState;
        pDest->m_nOverLoad = m_nOverLoad;
        pDest->m_fuavalue = m_fuavalue;
        pDest->m_fubvalue = m_fubvalue;
        pDest->m_fucvalue = m_fucvalue;
        pDest->m_fuzvalue = m_fuzvalue;
        pDest->m_frTestTime = m_frTestTime;
        pDest->m_nTripFlag = m_nTripFlag;
        pDest->m_fTripTime = m_fTripTime;
        pDest->m_fActValue = m_fActValue;
        pDest->m_fReturnValue = m_fReturnValue;
        pDest->m_fReturnTime = m_fReturnTime;
        pDest->m_fReturnCoef = m_fReturnCoef;
        pDest->m_oMuTimeRlt.CopyOwn(&pDest->m_oMuTimeRlt);

        for(int i = 0; i < MAX_BINARYIN_COUNT; i++)
        {
            for(int j = 0; j < 64; j++)
            {
                pDest->m_frTimeBinAct[i][j] = m_frTimeBinAct[i][j];
            }

            pDest->m_nrBinSwitchCount[i] = m_nrBinSwitchCount[i];
        }

        for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
        {
            for(int j = 0; j < 64; j++)
            {
                pDest->m_frTimeBinExAct[i][j] = m_frTimeBinExAct[i][j];
            }

            pDest->m_nrBinExSwitchCount[i] = m_nrBinExSwitchCount[i];
        }
    }

    tmt_manual_result()
    {
        init();
    }
} tmt_ManualResult;

typedef struct tmt_manual_test : public TMT_PARAS_HEAD
{
public:
    tmt_ManualParas   m_oManuParas;
    tmt_ManualResult m_oManuResult;

    void init()
    {
        strcpy(m_pszMacroID, STT_MACRO_ID_ManualTest);
#ifndef NOT_USE_TMT_TEST_PARAS_HEAD
        m_nVersion = 0x00010001;
        m_nTestState = 0;
#endif
        m_oManuResult.init();
        m_oManuParas.init();
    }

    tmt_manual_test()
    {
        init();
    }
} tmt_ManualTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas

void stt_xml_serialize_write_ManuTest();
void stt_init_paras(tmt_ManualParas *pParas);
void stt_init_results(tmt_ManualResult *pResults);
void stt_xml_serialize(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum, long nCurRsNum);
void stt_xml_serialize(tmt_ManualResult *pResults, CSttXmlSerializeBase *pXmlSierialize, BOOL bBinStatus = FALSE);
void stt_xml_serialize_dc(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
//void stt_xml_serialize_Aging(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
//void stt_xml_serialize_Lock(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
//void stt_xml_serialize_Auto(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize);  zhouhj 20210830 串行化已支持BOOL,无需调用此函数

void stt_xml_serialize_12u12i_pnv(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase *stt_xml_serialize(tmt_ManualTest *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum, long nCurRsNum);

