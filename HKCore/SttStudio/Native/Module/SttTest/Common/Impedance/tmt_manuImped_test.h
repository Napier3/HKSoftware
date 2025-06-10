#pragma once

#include "../tmt_test_paras_head.h"
#include "../tmt_manu_test.h"
#include"../../../SttTestBase/SttXmlSerialize.h"

// 手动测试相关参数
typedef struct tmt_manuImped_gradient
{
	int		nMode;			// 0:始值-终值  1:始值-终值-始值
	float		fStep;			//变化步长
	float		fTrigDelay;	//触发后延时
	float		fStart;			//变化始值;
	float		fEnd;				//变化终值
	float		fStepTime;	//变化时间

	void init()
	{
		nMode = 0;		
		fTrigDelay = 0;
		fStep = 0.5;
		fStart = 1;
		fEnd = 10;
		fStepTime = 1;
	}

public:
    tmt_manuImped_gradient()
    {
        init();
    }
} tmt_ManuImpedGradient;


typedef struct tmt_manualImped_paras
{
public:
	//参数设置
	int		 m_nCalMode;				// 阻抗类型 Add计算模型：0-定电流 1-定电压 2-固定系统侧阻抗
	double  m_fSCCurrent;				// 短路电流 
	double  m_fSCVoltage;				// 短路电压 
	double	m_fSZSAmp;					// ZS -Amp
	double	m_fSZSAngle;				// ZS -Angle

	int		m_nOffsetsMode;			// 零序补偿系数的模式
	float		m_fAmplitudeOrKr;		// Ko和Z0,Z1： 幅值，Kr,Kx 
	float		m_fPhaseOrKx;				// Ko和Z0,Z1： 相位，Kr,Kx 

	int		m_nFaultType;				// 故障类型(0:A相接地;1:B相接地;2:C相接地;3:AB短路;4:BC短路;5:CA短路;6:AB接地短路;7:BC接地短路;8:CA接地短路;9:三相短路;) 	
	int		m_nImped;					// 阻抗输入选择
	float		m_fZAmp;						// 短路阻抗幅值
	float		m_fZAngle;					// 阻抗角
	float		m_fR;
	float		m_fX;

	int		m_nFirstMode;				// 变量选择1- Z R X 
	int		m_nSecondMode;			// 变量选择2 - 幅值 相位	
	BOOL		m_bAuto;						// 自动递变//20240624 suyang 修改为BOOL类型
	int		m_bMutation;				// 突变量启动
	int		m_bLockChanged;		// lock mark
	float		m_fPrepareTime;			//常态时间(该参数为试验前复归时间,也称作变化前时间,即递变类发生递变前的复归时间,用于搜索阻抗边界,搜索角度等,一般重合闸后加速、距离不用该参数)
	float		m_fPreFaultTime;			//故障前时间(故障前复归时间,每次故障前的故障复归时间)

	tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
	tmt_channel m_uiCUR[MAX_CURRENT_COUNT];

	//开关量
	int		m_nBinLogic;			//0-或 1-与
	tmt_BinaryIn    m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryOut   m_binOut[MAX_BINARYOUT_COUNT];
	tmt_BinaryIn    m_binInEx[MAX_ExBINARY_COUNT];//系统扩展开关量
	tmt_BinaryOut	m_binOutEx[MAX_ExBINARY_COUNT];//系统扩展开关量

	tmt_ManuImpedGradient m_manuImpedGradient;
	tmt_GoosePub m_oGoosePub[MAX_MODULES_GOOSEPUB_COUNT];//GoosePub

	//整定值
	float m_fTimeSet;   //动作整定时间
	float m_fUSet;		//电压整定动作值
	float m_fISet;		//电流整定动作值
	float m_fAngleSet;	//相位整定动作值
	//float m_fHzSet;		//频率整定动作值
	float m_fImpSet;		//阻抗整定动作值
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
	//float m_fHzActVal_AbsErr; 		//频率动作值绝对误差
	//float m_fHzActVal_RelErr; 		//频率动作值相对误差
	//long m_nHzActVal_ErrorLogic; 	//频率动作值误差判断逻辑
	float m_fImpValue_AbsErr;//阻抗动作值绝对误差
	float m_fImpValue_RelErr;//阻抗动作值相对误差
	long m_nImpValue_ErrorLogic; 	//阻抗动作值误差判断逻辑
	float m_fRetCoef_AbsErr; 		//返回系数绝对误差
	float m_fRetCoef_RelErr;		//返回系数相对误差
	long m_nRetCoef_ErrorLogic; 	//返回系数误差判断逻辑

	void init()
	{		
		//阻抗类型
		 m_nCalMode = 0;//  0:阻抗，定电流 1:阻抗，定电压 2:阻抗，固定系统测阻抗 ，默认为0（定电流）
		 m_fSCCurrent = 5.000f;		//短路电流
		 m_fSCVoltage = 10.000f;		//短路电压
		 m_fSZSAmp = 1.000f;	
		 m_fSZSAngle = 90.000f;

		//零序补偿系数
		 m_nOffsetsMode = 0;//零序补偿系数的模式
		 m_fAmplitudeOrKr = 0.000f;
		 m_fPhaseOrKx	=  0.000f;
		
		 m_nFaultType = 0;//故障类型-A相接地	 		 
		 m_nImped = 0;//阻抗输入选择
		 m_fZAmp = 1.000f;			
		 m_fZAngle = 90.000f;	
		 m_fR = 0.000f;	
		 m_fX = 1.000f;	

		 m_nFirstMode = 0;//变量选择1- Z R X 
		 m_nSecondMode = 0;//变量选择2 - 幅值 相位
		 m_bAuto = false;
		 m_bMutation = false;		 
		 m_bLockChanged = false;
		 m_fPrepareTime = 0.000f;		//常态时间
		 m_fPreFaultTime = 0.000f;		//故障前时间
		 float fAngle[3] = {0, -120.0, 120.0};
		 m_manuImpedGradient.init();

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

		 m_fTimeSet = 0;
		 m_fUSet = 0;
		 m_fISet = 0;
		 m_fAngleSet = 0;
		 //m_fHzSet=0;
		 m_fImpSet = 0;
		 m_fRetCoefSet = 0;
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
		 //m_fHzActVal_AbsErr = 0.001f;
		 //m_fHzActVal_RelErr = 0.1f;
		 //m_nHzActVal_ErrorLogic = 0;
		 m_fImpValue_AbsErr = 0.001f;
		 m_fImpValue_RelErr = 0.1f;
		 m_nImpValue_ErrorLogic = 0;
		 m_fRetCoef_AbsErr = 0.001f;
		 m_fRetCoef_RelErr = 0.1f;
		 m_nRetCoef_ErrorLogic = 0;		
	}

	void InitManuImpedGradient(int nType)
	{	
		m_manuImpedGradient.fStep = 0.5;
		m_manuImpedGradient.fStepTime = 1.2;

		if(nType = 0)
		{
			m_manuImpedGradient.fStart = 1;
			m_manuImpedGradient.fEnd = 10;
		}
		else if(nType = 1)
		{
			m_manuImpedGradient.fStart = 50;
			m_manuImpedGradient.fEnd = 20;
		}

	}

	void CopyOwn(tmt_manualImped_paras *pDest)
	{
		pDest->m_fTimeSet = m_fTimeSet;
		pDest->m_fUSet = m_fUSet;
		pDest->m_fISet = m_fISet;
		pDest->m_fAngleSet = m_fAngleSet;
		//pDest->m_fHzSet = m_fHzSet;
		pDest->m_fImpSet = m_fImpSet;
		pDest->m_fRetCoefSet = m_fRetCoefSet;
		pDest->m_fTimeValue_AbsErr = m_fTimeValue_AbsErr;
		pDest->m_fTimeValue_RelErr = m_fTimeValue_RelErr;
		pDest->m_nTimeValue_ErrorLogic = m_nTimeValue_ErrorLogic;
		pDest->m_fUActVal_AbsErr = m_fUActVal_AbsErr;
		pDest->m_fUActVal_RelErr = m_fUActVal_RelErr;
		pDest->m_nUActVal_ErrorLogic = m_nUActVal_ErrorLogic;
		pDest->m_fIActVal_AbsErr = m_fIActVal_AbsErr;
		pDest->m_fIActVal_RelErr = m_fIActVal_RelErr;
		pDest->m_nIActVal_ErrorLogic = m_nIActVal_ErrorLogic;
		//pDest->m_fHzActVal_AbsErr = m_fHzActVal_AbsErr;
		//pDest->m_fHzActVal_RelErr = m_fHzActVal_RelErr;
		//pDest->m_nHzActVal_ErrorLogic = m_nHzActVal_ErrorLogic;
		pDest->m_fAngleActVal_AbsErr = m_fAngleActVal_AbsErr;
		pDest->m_fAngleActVal_RelErr = m_fAngleActVal_RelErr;
		pDest->m_nAngleActVal_ErrorLogic = m_nAngleActVal_ErrorLogic;
		pDest->m_fImpValue_AbsErr = m_fImpValue_AbsErr;
		pDest->m_fImpValue_RelErr = m_fImpValue_RelErr;
		pDest->m_nImpValue_ErrorLogic = m_nImpValue_ErrorLogic;
		pDest->m_fRetCoef_AbsErr = m_fRetCoef_AbsErr;
		pDest->m_fRetCoef_RelErr = m_fRetCoef_RelErr;
		pDest->m_nRetCoef_ErrorLogic = m_nRetCoef_ErrorLogic; 
	}

	void SetFundFreq(float fFreqValue)
	{
		for(int j = 0; j < MAX_VOLTAGE_COUNT; j++)
		{
			m_uiVOL[j].Harm[1].fFreq = fFreqValue;
			m_uiCUR[j].Harm[1].fFreq = fFreqValue;
		}
	}

public:
    tmt_manualImped_paras()
    {
        init();
    }
} tmt_ManualImpedParas;

typedef struct tmt_manualImped_result:public tmt_ManualResult
{
public:
    tmt_manualImped_result()
    {
        init();
    }
} tmt_ManualImpedResult;

typedef struct tmt_manualImped_test : public TMT_PARAS_HEAD
{
public:
    tmt_ManualImpedParas   m_oManuImpedParas;
    tmt_ManualImpedResult  m_oManuImpedResult;

    void init()
    {
        strcpy(m_pszMacroID, STT_MACRO_ID_ImpedManualTest);
#ifndef NOT_USE_TMT_TEST_PARAS_HEAD
        m_nVersion = 0x00010001;
        m_nTestState = 0;
#endif
        m_oManuImpedResult.init();
        m_oManuImpedParas.init();
    }

    tmt_manualImped_test()
    {
        init();
    }
} tmt_ManualImpedTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void stt_xml_serialize_write_ManuImpedTest();
void stt_init_paras(tmt_ManualImpedParas *pParas);
void stt_init_results(tmt_ManualImpedResult *pResults);
void stt_xml_serialize(tmt_ManualImpedParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_ManualImpedResult *pResults, CSttXmlSerializeBase *pXmlSierialize);
CSttXmlSerializeBase *stt_xml_serialize(tmt_ManualImpedTest *pParas, CSttXmlSerializeBase *pXmlSierialize);

