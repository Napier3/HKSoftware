#pragma once

#include "tmt_common_def.h"
#include"../../SttTestBase/SttXmlSerialize.h"
#include "tmt_test_paras_head.h"
//////////////////////////////////////////////////////////////////////////
// 递变测试相关参数
enum GradientChan
{
	U1a = 0,
	U1b,
	U1c,
	Null,
	U1ab=4,
	U1bc,
	U1ca,
	U1abc,
	U2a,
	U2b,
	U2c,
	U2abc,
	I1a,
	I1b,
	I1c,
	I1ab,
	I1bc,
	I1ca,
	I1abc,
	I2a,
	I2b,
	I2c,
	I2abc,
	U_All,
	I_All,
	Udc,
	Uz,
	U2ab,
	U2bc,
	U2ca,
	I2ab,
	I2bc,
	I2ca,
	I1abcAdd=33,
	I2abcAdd,  //a2+b2+c2
	U1abcAdd,
	U2abcAdd,  //va2+vb2+vc2
	FreAll,
	Ia1Ia2Add,//ia+ia2
	Ib1Ib2Add,//ib+ib2
	Ic1Ic2Add,//ic+ic2
	Ia1Ia2Add_Ib1Ib2Add_Ic1Ic2Add,//ia+ia2,ib+ib2,ic+ic2
	Ia1Ia2_Ib1Ib2_Ic1Ic2_Add//ia+ia2+ib+ib2+ic+ic2
};

enum AtsGradientChan
{
	a1=0,
	b1,
	c1,
	a2,
	b2,
	c2,
	ab1,
	bc1,
	ca1,
	ab2,
	bc2,
	ca2,
	abc1,
	abc2,
	abc12
};

enum AtsURampCh //电压递变通道定义
{
	URampCh_Ua=0,
	URampCh_Ub,
	URampCh_Uc,
    URampCh_Ua2,
    URampCh_Ub2,
    URampCh_Uc2,
	URampCh_Uab,
	URampCh_Ubc,
	URampCh_Uca,
    URampCh_Uab2,
    URampCh_Ubc2,
    URampCh_Uca2,
    URampCh_Uabc,
    URampCh_Uabc2,
    URampCh_Uabc12
};

enum AtsIRampCh //电流递变通道定义
{
	IRampCh_Ia=0,
	IRampCh_Ib,
	IRampCh_Ic,
	IRampCh_Ia2,
	IRampCh_Ib2,
	IRampCh_Ic2,
	IRampCh_Iab,
	IRampCh_Ibc,
	IRampCh_Ica,
	IRampCh_Iab2,
	IRampCh_Ibc2,
    IRampCh_Ica2,
    IRampCh_Iabc,
    IRampCh_Iabc2,
    IRampCh_Iabc12
};

enum SequenceGradientVarPhase
{
    VarPhaseV1 = 0,
    VarPhaseV2,
    VarPhaseV0,
    VarPhaseI1,
    VarPhaseI2,
    VarPhaseI0
};

enum ArcRampIndex
{
    Pha_a = 0,
    Phb_b,
    Phc_c,
    Phab_c = 6,
    Phbc_a,
    Phca_b
};

/*********SttGradientTest**********/
#define TMT_GRADIENT_CHANNEL_A    0
#define TMT_GRADIENT_CHANNEL_B    1
#define TMT_GRADIENT_CHANNEL_C    2
#define TMT_GRADIENT_CHANNEL_A2   3
#define TMT_GRADIENT_CHANNEL_B2   4
#define TMT_GRADIENT_CHANNEL_C2   5


#define GradientTest_Base   0   //0-单机模式
#define GradientTest_URamp  1	//1-自动测试电压递变
#define GradientTest_IRamp  2	//2-自动测试电流递变
#define GradientTest_Base_1 3	//3-递变,分组设置<变化前、故障前、故障>

#define TESTSTATE_NONE		0
#define TESTSTATE_SUCCESS	1
#define TESTSTATE_FAIL		2

#define MAX_GRADIENT_COUNT  20


#define Gradient_TestMode_ActValue                              0
#define Gradient_TestMode_ReturnCoef                            1
#define Gradient_TestMode_MaxAngle                              2


typedef struct tmt_gradient_paras
{
public:
	int   m_nChannel;
	int   m_nType;//幅值、相位、频率
	int   m_nChannel2; //add wangtao 20240619 第二变量的通道 ，下同
	int   m_nType2;//第二变量类型
	int   m_nStepCnt;//仅用于SttDevice计数
	int   m_nStepDirection;//仅用于SttDevice
	int   m_nStepHarm;//仅用于SttDevice
	BOOL  m_bManuDc;//用于手动实验选择直流模式
	int	  m_nVarIndexType;//0=电流 1=电压 2=频率

	int   m_nSttTestMode;	//0-单机模式 1-自动测试电压递变 2-自动测试电流递变  3-递变,分组设置
	float m_fG1Current;     //故障电流值1
	float m_fG2Current;     //故障电流值2
	float m_fG1Volt;        //故障电压值1
	float m_fG2Volt;        //故障电压值2
	float m_fDiffIAngle;	//故障前两组角度差
	float m_fHz;			//故障前频率

	float m_fStart;
	float m_fStop;
	float m_fStep;
	float m_fStart2;//第二变量始值
	float m_fStop2;//第二变量终值
	float m_fStep2;//第二变量步长
	float m_fStepTime;
	float m_fPrepareTime;
	float m_fPreFaultTime;
    float m_fMarginTime;
	int	  m_nTestMode;	//测试类型：0-动作值 1-返回系数 2-最大灵敏角
	float m_fVolAux;		// 辅助直流电压（仅模拟）
	float m_fCurAux;		// 辅助直流电流（仅模拟）
	int	  m_nBinLogic;			//0-或 1-与
	float m_fEDU;//额定
	float m_fEDI;//额定
	float m_fEDUaIaAngle;//额定
	float m_fEDFreq;//额定
	int   m_nPhaseGradDir;//相位递变的方向(0:逆时针方向  1:顺时针方向)

	//自动测试用
	tmt_channel m_uiVOL[3][MAX_VOLTAGE_COUNT];	//(测试前+故障前+故障)*最大电压数
	tmt_channel m_uiCUR[3][MAX_CURRENT_COUNT];

	//开关量
	tmt_BinaryIn  m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryIn  m_binInEx[MAX_ExBINARY_COUNT];
	tmt_BinaryOut m_binOut[2][MAX_BINARYOUT_COUNT];	//0-非故障态开出 1-故障态开出
	tmt_BinaryOut m_binOutEx[2][MAX_ExBINARY_COUNT];//0-非故障态开出 1-故障态开出

	//GoosePub
	tmt_GoosePub m_oGoosePub[MAX_MODULES_GOOSEPUB_COUNT];

	int		m_nPhaseSet[2];	// 相序设置 电压电流,用于高级试验,如复压闭锁

	//定值
	float m_fUSet;		//电压整定动作值
	float m_fISet;		//电流整定动作值
	float m_fAngleSet;	//相位整定动作值
	float m_fHzSet;		//频率整定动作值
	float m_fRetCoefSet; //返回系数整定值
	float m_fAngleFSet; //边界角1整定值
	float m_fAngleSSet; //边界角2整定值
	float m_fMaxAngleSet; //最大灵敏角整定值

	//评估
	float m_fUActVal_AbsErr; 		//电压动作值绝对误差
	float m_fUActVal_RelErr; 		//电压动作值相对误差 		
	long m_nUActVal_ErrorLogic; 			//电压动作值误差判断逻辑 	
	float m_fIActVal_AbsErr; 		//电流动作值绝对误差 		
	float m_fIActVal_RelErr; 		//电流动作值相对误差 		
	long m_nIActVal_ErrorLogic; 			//电流动作值误差判断逻辑 	
	float m_fAngleActVal_AbsErr; 	//相位动作值绝对误差 		
	float m_fAngleActVal_RelErr; 	//相位动作值相对误差 		
	long m_nAngleActVal_ErrorLogic; 		//相位动作值误差判断逻辑 	
	float m_fHzActVal_AbsErr; 		//频率动作值绝对误差 		
	float m_fHzActVal_RelErr; 		//频率动作值相对误差 		
	long m_nHzActVal_ErrorLogic; 		//频率动作值误差判断逻辑 	
	float m_fRetCoef_AbsErr; 		//返回系数绝对误差 		
	float m_fRetCoef_RelErr;			//返回系数相对误差 		
	long m_nRetCoef_ErrorLogic; 		//返回系数误差判断逻辑 	
	float m_fMaxAngle_AbsErr; 		//最大灵敏角绝对误差		
	float m_fMaxAngle_RelErr; 		//最大灵敏角相对误差 		
	long m_nMaxAngle_ErrorLogic; 	//最大灵敏角误差判断逻辑	
	float m_fAngleF_AbsErr; 			//边界角1绝对误差			
	float m_fAngleF_RelErr; 			//边界角1相对误差			
	long m_nAngleF_ErrorLogic; 		//边界角1误差判断逻辑 		
	float m_fAngleS_AbsErr; 			//边界角2绝对误差 			
	float m_fAngleS_RelErr; 			//边界角2相对误差 			
	long m_nAngleS_ErrorLogic; 		//边界角2误差判断逻辑		


public:
	void init()
	{
        m_nSttTestMode = GradientTest_Base;
		m_nChannel = 0;
		m_nType = GRADIENT_AMP;
		m_nChannel2 = 0;
		m_nType2 = GRADIENT_AMP;
		m_fStart = 0;
		m_fStop = 0;
		m_fStep = 0;
		m_fStart2 = 0;
		m_fStop2 = 0;
		m_fStep2 = 0;
		m_fStepTime = 0;
		m_fPrepareTime = 0;
		m_fPreFaultTime = 0;
        m_fMarginTime = 0;
		m_nTestMode = Gradient_TestMode_ActValue;
		m_fVolAux = 0;
		m_fCurAux = 0;
		m_nBinLogic = 0;
		//变化前额定
		m_fEDU = 57.74f;
		m_fEDI = 0;
		m_fEDUaIaAngle = 0;
		m_fEDFreq = 50;
		m_nVarIndexType = 0;

		//故障前
		m_fG1Current=0;
		m_fG2Current=0;
		m_fDiffIAngle = 0;
		m_fG1Volt=57.74f;
		m_fG2Volt=57.74f;
		m_fHz=50;
		m_nPhaseGradDir = 0;

		float fAngle[3]={0,-120,120};
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<MAX_VOLTAGE_COUNT; j++)
			{
				m_uiVOL[i][j].Harm[1].fAmp = 0;
				m_uiVOL[i][j].Harm[1].fAngle = fAngle[j%3];
				m_uiVOL[i][j].Harm[1].fFreq = 50;
			}
			for(int j=0; j<MAX_CURRENT_COUNT; j++)
			{
				m_uiCUR[i][j].Harm[1].fAmp = 0;
				m_uiCUR[i][j].Harm[1].fAngle = fAngle[j%3];
				m_uiCUR[i][j].Harm[1].fFreq = 50;
			}
		}

		for (int i=0;i<MAX_BINARYIN_COUNT;i++)
		{
			m_binIn[i].init();
			for(int j=0;j<2;j++)
			{
				m_binOut[j][i].init();
			}
		}

        for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			m_binInEx[i].init();
		}

        for(int i = 0; i < g_nBoutExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			for(int j=0;j<2;j++)
			{
				m_binOutEx[j][i].init();
			}
		}

		m_nPhaseSet[0] = m_nPhaseSet[1] = 0;

		m_fUSet = 0;		
		m_fISet = 0;		
		m_fAngleSet = 30;	
		m_fHzSet = 50;
		m_fRetCoefSet = 0;	
		m_fAngleFSet = 0;	
		m_fAngleSSet = 0;	
		m_fMaxAngleSet = 0;	

		m_fUActVal_AbsErr = 0;
		m_fUActVal_RelErr = 0;
		m_nUActVal_ErrorLogic = 0;
		m_fIActVal_AbsErr = 0;
		m_fIActVal_RelErr = 0;
		m_nIActVal_ErrorLogic = 0;
		m_fAngleActVal_AbsErr = 0;
		m_fAngleActVal_RelErr = 0;
		m_nAngleActVal_ErrorLogic = 0;
		m_fHzActVal_AbsErr = 0;		
		m_fHzActVal_RelErr = 0;		
		m_nHzActVal_ErrorLogic = 0;		
		m_fRetCoef_AbsErr = 0; 		
		m_fRetCoef_RelErr = 0;		
		m_nRetCoef_ErrorLogic = 0;	
		m_fMaxAngle_AbsErr = 0;		
		m_fMaxAngle_RelErr = 0;		
		m_nMaxAngle_ErrorLogic = 0; 	
		m_fAngleF_AbsErr = 0;		
		m_fAngleF_RelErr = 0;		
		m_nAngleF_ErrorLogic = 0;	
		m_fAngleS_AbsErr = 0; 		
		m_fAngleS_RelErr = 0; 		
		m_nAngleS_ErrorLogic = 0; 	
	}

	void CopyOwn(tmt_gradient_paras* pDest,long nVolChNum,long nCurrChNum)
	{
		pDest->m_nSttTestMode = m_nSttTestMode;
		pDest->m_nChannel = m_nChannel;
		pDest->m_nType = m_nType;
		pDest->m_fStart = m_fStart;
		pDest->m_fStop = m_fStop;
		pDest->m_fStep = m_fStep;
		pDest->m_nChannel2 = m_nChannel2;
		pDest->m_nType2 = m_nType2;
		pDest->m_fStart2 = m_fStart2;
		pDest->m_fStop2 = m_fStop2;
		pDest->m_fStep2 = m_fStep2;
		pDest->m_fStepTime = m_fStepTime;
		pDest->m_fPrepareTime = m_fPrepareTime;
		pDest->m_fPreFaultTime = m_fPreFaultTime;
		pDest->m_fMarginTime = m_fMarginTime;
		pDest->m_nTestMode = m_nTestMode;
		pDest->m_nVarIndexType = m_nVarIndexType;
		pDest->m_fVolAux = m_fVolAux;
		pDest->m_fCurAux = m_fCurAux;
		pDest->m_nBinLogic = m_nBinLogic;
		//变化前额定
		pDest->m_fEDU = m_fEDU;
		pDest->m_fEDI = m_fEDI;
		pDest->m_fEDUaIaAngle = m_fEDUaIaAngle;
		pDest->m_fEDFreq = m_fEDFreq;

		//故障前
		pDest->m_fG1Current=m_fG1Current;
		pDest->m_fG2Current=m_fG2Current;
		pDest->m_fDiffIAngle = m_fDiffIAngle;
		pDest->m_fG1Volt=m_fG1Volt;
		pDest->m_fG2Volt=m_fG2Volt;
		pDest->m_fHz=m_fHz;

		for(int i=0; i<3; i++)
		{
			for(int j=0; j<nVolChNum; j++)
			{
				pDest->m_uiVOL[i][j].Harm[1].fAmp = m_uiVOL[i][j].Harm[1].fAmp;
				pDest->m_uiVOL[i][j].Harm[1].fAngle = m_uiVOL[i][j].Harm[1].fAngle;
			}
			for(int j=0; j<nCurrChNum; j++)
			{
				pDest->m_uiCUR[i][j].Harm[1].fAmp = m_uiCUR[i][j].Harm[1].fAmp;
				pDest->m_uiCUR[i][j].Harm[1].fAngle = m_uiCUR[i][j].Harm[1].fAngle;
			}
		}

		for (int i=0;i<MAX_BINARYIN_COUNT;i++)
		{
			pDest->m_binIn[i] = m_binIn[i];

			for(int j=0;j<2;j++)
			{
				pDest->m_binOut[j][i] = m_binOut[j][i];
			}
		}

        for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			pDest->m_binInEx[i] = m_binInEx[i];
		}

        for(int i = 0; i < g_nBoutExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			for(int j=0;j<2;j++)
			{
				pDest->m_binOutEx[j][i] = m_binOutEx[j][i];
			}
		}

		pDest->m_nPhaseSet[0] = m_nPhaseSet[0];
		pDest->m_nPhaseSet[1] = m_nPhaseSet[1];

		pDest->m_fUSet = m_fUSet;		
		pDest->m_fISet = m_fISet;		
		pDest->m_fAngleSet = m_fAngleSet;	
		pDest->m_fHzSet = m_fHzSet;
		pDest->m_fRetCoefSet = m_fRetCoefSet;	
		pDest->m_fAngleFSet = m_fAngleFSet;	
		pDest->m_fAngleSSet = m_fAngleSSet;	
		pDest->m_fMaxAngleSet = m_fMaxAngleSet;	

		pDest->m_fUActVal_AbsErr = m_fUActVal_AbsErr;
		pDest->m_fUActVal_RelErr = m_fUActVal_RelErr;
		pDest->m_nUActVal_ErrorLogic = m_nUActVal_ErrorLogic;
		pDest->m_fIActVal_AbsErr = m_fIActVal_AbsErr;
		pDest->m_fIActVal_RelErr = m_fIActVal_RelErr;
		pDest->m_nIActVal_ErrorLogic = m_nIActVal_ErrorLogic;
		pDest->m_fAngleActVal_AbsErr = m_fAngleActVal_AbsErr;
		pDest->m_fAngleActVal_RelErr = m_fAngleActVal_RelErr;
		pDest->m_nAngleActVal_ErrorLogic = m_nAngleActVal_ErrorLogic; 
		pDest->m_fHzActVal_AbsErr = m_fHzActVal_AbsErr;	
		pDest->m_fHzActVal_RelErr = m_fHzActVal_RelErr;	
		pDest->m_nHzActVal_ErrorLogic = m_nHzActVal_ErrorLogic;
		pDest->m_fRetCoef_AbsErr = m_fRetCoef_AbsErr; 	
		pDest->m_fRetCoef_RelErr = m_fRetCoef_RelErr;	
		pDest->m_nRetCoef_ErrorLogic = m_nRetCoef_ErrorLogic;
		pDest->m_fMaxAngle_AbsErr = m_fMaxAngle_AbsErr;	
		pDest->m_fMaxAngle_RelErr = m_fMaxAngle_RelErr;	
		pDest->m_nMaxAngle_ErrorLogic = m_nMaxAngle_ErrorLogic;
		pDest->m_fAngleF_AbsErr = m_fAngleF_AbsErr;	
		pDest->m_fAngleF_RelErr = m_fAngleF_RelErr;	
		pDest->m_nAngleF_ErrorLogic = m_nAngleF_ErrorLogic;
		pDest->m_fAngleS_AbsErr = m_fAngleS_AbsErr; 	
		pDest->m_fAngleS_RelErr = m_fAngleS_RelErr; 	
		pDest->m_nAngleS_ErrorLogic = m_nAngleS_ErrorLogic; 
	}

	void SetAllFreq(float fFreqValue)//设置变化前、故障前、故障态频率
	{
		m_fEDFreq = fFreqValue;
		m_fHz = fFreqValue;//故障前频率
	}

	tmt_gradient_paras()	{}
}tmt_GradientParas;

typedef struct tmt_gradient_max_angle_result
{
public:
	float m_fAngleF;	//边界角1
	float m_fAngleS;	//边界角2
	float m_fMaxAngle; //最大灵敏角
	int  m_nAngleF_StepIndex;//首端边界角的递变步数,从0开始计数,0为始值
	long m_nAngleS_StepIndex;//末端边界角的递变步数,从0开始计数,0为始值
	int   m_nActF;		//1-动作 0-没动作
	int   m_nActS;		//1-动作 0-没动作

	void init()
	{
		m_fAngleF = 0;
		m_fAngleS = 0;
		m_fMaxAngle = 0;
		m_nAngleF_StepIndex = 0;
		m_nAngleS_StepIndex = 0;
		m_nActF = 0;
		m_nActS = 0;
	}

	tmt_gradient_max_angle_result(){}
}tmt_GradientMaxAngleResult;

typedef struct tmt_gradient_result
{
public:
	float m_fTripValue;	//动作值
	float m_fTripTime;//动作时间 zhouhj 20211125 用于记录动作时间
	float m_fTripValueChl[MAX_BINARYIN_COUNT];//动作值，默认是0
	float m_fTripValueExChl[MAX_ExBINARY_COUNT];//0-非故障态开出 1-故障态开出
	float m_fReturnValue;
	float m_fReturnCoef;//返回值/动作值
	int   m_nAct;		//1-动作 0-没动作
	float m_fPhiAngleValue;
	tmt_GradientMaxAngleResult m_oMaxAngle;

	//评估
	float m_fTripUErrVal;		 //电压动作值误差
	float m_fTripIErrVal;		 //电流动作值误差
	float m_fTripHzErrVal;		 //频率动作值误差
	float m_fTripAngleErrVal;	 //相位动作值误差
	float m_fRetCoefErrVal;      //返回系数误差
	float m_fMaxAngleErrVal;     //最大灵敏角误差
	float m_fAngleFErrVal;		 //边界角1误差
	float m_fAngleSErrVal;		 //边界角2误差

	void init()
	{
		m_fTripValue = 0;
		m_fTripTime = 0;
		m_fReturnValue = 0;
		m_fReturnCoef = 0;
		m_nAct = 0;
		m_fPhiAngleValue = 0;
		m_oMaxAngle.init();

		m_fTripUErrVal = 0;
		m_fTripIErrVal = 0;
		m_fTripHzErrVal = 0;
		m_fTripAngleErrVal = 0;
		m_fRetCoefErrVal = 0;
		m_fMaxAngleErrVal = 0;
		m_fAngleFErrVal = 0;
		m_fAngleSErrVal = 0;
		
		for(int i=0; i<MAX_BINARYIN_COUNT; i++)
		{
			m_fTripValueChl[i] = 0;
		}

        for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			m_fTripValueExChl[i] = 0;
		}
	}

	tmt_gradient_result()	{}
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
}tmt_GradientTest;

struct TestDataCondition
{
	bool bXD;
	float fXD;		//相对
	bool bJD;
	float fJD;		//绝对
	bool bCoeff;	//系数
	float fCoeff;  
	bool bLogicOr;	//逻辑或:1 or,0 and,相对误差，绝对误差时使用

	TestDataCondition()
	{
		bXD = false;
		fXD = 5;
		bJD = false;
		fJD = -1;
		bCoeff = false;
		fCoeff = -1;
		bLogicOr = true;
	}

	TestDataCondition &operator = (const TestDataCondition &right)
	{
		bXD = right.bXD;
		fXD = right.fXD;
		bJD = right.bJD;
		fJD = right.fJD;
		bCoeff = right.bCoeff;
		fCoeff = right.fCoeff;
		bLogicOr = right.bLogicOr;

		return *this;
	}
};

typedef struct tmt_gradient_paras_ex : public tmt_gradient_paras
{
public:
	TestDataCondition sCondition; //结果判据

public:
	void init()
	{
        m_nSttTestMode = GradientTest_Base;

		tmt_gradient_paras::init();
	}

	tmt_gradient_paras_ex()	{}
}tmt_GradientParasEx;

typedef struct tmt_gradient_test_ex : public TMT_PARAS_HEAD
{
public:
	tmt_GradientParasEx m_oGradientParasEx;
	tmt_GradientResult m_oResultParas;

	void init()
	{
		init_head(); 
		strcpy(m_pszMacroID,STT_MACRO_ID_GradientTest);
		m_nSelected = 1;
		m_nVersion = 0x00010001;
		m_nTestState = 0;

		m_oGradientParasEx.init();
		m_oResultParas.init();
	}

	tmt_gradient_test_ex(){	init();}
}tmt_GradientTestEx;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas

void stt_xml_serialize_write_GradientTest();
void stt_init_paras(tmt_GradientParas *pParas);
void stt_init_results(tmt_GradientParas *pResults);
void stt_xml_serialize(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_GradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_AtsRamp(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_binary_out(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_base(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_ex(tmt_GradientParas *pPara, CSttXmlSerializeBase *pXmlSierialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_GradientTestEx *pParas, CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_serialize_common(tmt_GradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
