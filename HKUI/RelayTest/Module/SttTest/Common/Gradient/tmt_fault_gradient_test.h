#pragma once

#include "../tmt_gradient_test.h"
//////////////////////////////////////////////////////////////////////////

//整定和结果评估界面 行列
#define FG_EstimateRow		9
#define FG_EstimateCol		5

//FG  FaultGradient  故障递变
//测试返回类型  
enum SttFaultGradientTestMode
{
	FG_TestMode_ActValue = 0,		//动作值
	FG_TestMode_ReturnCoef,			//返回系数
	FG_TestMode_MaxAngle,			//最大灵敏角
	FG_TestMode_Null
};

//故障模式
enum SttFaultGradientFaultMode
{
	FG_FaultMode_A = 0,				//A相短路
	FG_FaultMode_B,					//B相短路
	FG_FaultMode_C,					//A相短路
	FG_FaultMode_ABC,				//ABC相短路
	FG_FaultMode_AB,				//AB相短路
	FG_FaultMode_BC,				//BC相短路
	FG_FaultMode_CA,				//CA相短路
	FG_FaultMode_AB_C,				//AB相短路，C相电流
	FG_FaultMode_BC_A,				//BC相短路，A相电流
	FG_FaultMode_CA_B,				//CA相短路，B相电流
	FG_FaultMode_AB_B,				//AB相短路，B相电流
	FG_FaultMode_BC_C,				//BC相短路，C相电流
	FG_FaultMode_CA_A,				//CA相短路，A相电流
	//FG_FaultMode_CA_A,			//CA相短路，A相电流  错误
	FG_FaultMode_UF,				//U/f
	FG_FaultMode_I2I1,				//I2/I1
	FG_FaultMode_Null
};

//故障模式改变( FaultGradientFaultMode  FG_FM )  变化量值
enum SttFG_FM_Value
{
	FG_FM_Vaule_ShortVM = 0,		//短路电压
	FG_FM_Vaule_ShortVA,			//短路电流
	FG_FM_Vaule_ImpedeAngle,		//阻抗角
	FG_FM_Vaule_ShortImpede,		//短路阻抗
	FG_FM_Vaule_Frequency,			//频率
	FG_FM_Vaule_PlusVM,				//正序电压
	FG_FM_Vaule_MinusVM,			//负序电压
	FG_FM_Vaule_ZeroVM,				//零序电压（3U0）
	//AB相短路，C相电流
	FG_FM_Vaule_Uab_c = 0,			//Uab
	FG_FM_Vaule_Ic_ab,				//Ic
	FG_FM_Vaule_Uab_Ic,				//Φ(Uab-Ic)
	//BC相短路，A相电流
	FG_FM_Vaule_Ubc_a = 0,			//
	FG_FM_Vaule_Ia_bc,				//
	FG_FM_Vaule_Ubc_Ia,				//
	//CA相短路，B相电流
	FG_FM_Vaule_Uca_b = 0,			//
	FG_FM_Vaule_Ib_ca,				//
	FG_FM_Vaule_Uca_Ib,				//
	//AB相短路，B相电流
	FG_FM_Vaule_Uab_b = 0,			//
	FG_FM_Vaule_Ib_ab,				//
	FG_FM_Vaule_Uab_Ib,				//
	//BC相短路，C相电流
	FG_FM_Vaule_Ubc_c= 0,			//
	FG_FM_Vaule_Ic_bc,				//
	FG_FM_Vaule_Ubc_Ic,				//
	//CA相短路，A相电流
	FG_FM_Vaule_Uca_a = 0,			//
	FG_FM_Vaule_Ia_ca,				//
	FG_FM_Vaule_Uca_Ia,				//
	//U/f
	FG_FM_Vaule_VM = 0,				//电压
	FG_FM_Vaule_HZ,				    //频率
	FG_FM_Vaule_I2 = 0,				//I2
	FG_FM_Vaule_Null = 200
};

//电压类型
enum SttFaultGradientTypeVM
{
	FG_Type_VM_Plus = 0,			//正序(U1)
	FG_Type_VM_Minus,				//负序(U2)
	FG_Type_VM_Zero,				//零序(3U0)
	FG_Type_VM_Null
};


//////下发参数 
typedef struct tmt_fault_gradient_paras
{

public:
	float m_fStart;								//变化始值
	float m_fStop;  							//变化终值
	float m_fStep;							    //变化步长
	float m_fFaultTime;							//故障时间
	int	  m_nTestMode;							//返回类型
	///////////////
	int	  m_nFaultMode;							//故障模式    m_nChannel
	int	  m_nChangeValue;						//变化量	  m_nType
	int	  m_nVarIndexType;						//0=电压 1=电流 2=阻抗角 3=短路阻抗 4=频率 5=返回系数 6=最大灵敏角 
	float m_fShortVm;							//短路电压
	int   m_nShortVmType;						//短路电压
	float m_fShortVa;							//短路电流
	float m_fAngle;								//阻抗角
	///////////
	float m_fPrepareTime;						//变化前时间
	float m_fPreFaultTime;						//故障前时间
	float m_fPreFaultEDU;						//故障前电压
	float m_fPreFaultEDI;						//故障前电流
	float m_fEDUaIaAngle;						//故障前相角
	//////////
	int	  m_nBinLogic;							//逻辑或与   0-或 1-与
	tmt_BinaryIn  m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryOut m_binOut[2][MAX_BINARYOUT_COUNT];	//0-非故障态开出 1-故障态开出

	//////////////////////////////////////
	//GoosePub
	tmt_GoosePub m_oGoosePub[MAX_MODULES_GOOSEPUB_COUNT];

	//定值
	float m_fUSet;								//电压整定动作值
	float m_fISet;								//电流整定动作值
	float m_fImpAngleSet;						//阻抗角整定动作值
	float m_fShortZImp;							//短路阻抗整定动作值
	float m_fHzSet;								//频率整定动作值
	float m_fAngleFSet;							//边界角1整定值
	float m_fAngleSSet;							//边界角2整定值
	float m_fMaxAngleSet;						//最大灵敏角整定值
	float m_fRetCoefSet;						//返回系数整定值

	//评估
	float m_fUActVal_AbsErr; 					//电压动作值绝对误差
	float m_fUActVal_RelErr; 					//电压动作值相对误差 		
	long m_nUActVal_ErrorLogic; 				//电压动作值误差判断逻辑 	
	float m_fIActVal_AbsErr; 					//电流动作值绝对误差 		
	float m_fIActVal_RelErr; 					//电流动作值相对误差 		
	long m_nIActVal_ErrorLogic; 				//电流动作值误差判断逻辑 	
	float m_fImpAngleActVal_AbsErr; 				//阻抗角动作值绝对误差 		
	float m_fImpAngleActVal_RelErr; 				//阻抗角动作值相对误差 		
	long m_nImpAngleActVal_ErrorLogic; 			//阻抗角动作值误差判断逻辑 	
	float m_fShortZImpActVal_AbsErr; 				//短路阻抗动作值绝对误差 		
	float m_fShortZImpActVal_RelErr; 				//短路阻抗动作值相对误差 		
	long m_nShortZImpActVal_ErrorLogic; 			//短路阻抗动作值误差判断逻辑 	
	float m_fHzActVal_AbsErr; 					//频率动作值绝对误差 		
	float m_fHzActVal_RelErr; 					//频率动作值相对误差 		
	long m_nHzActVal_ErrorLogic; 				//频率动作值误差判断逻辑 	
	float m_fAngleF_AbsErr; 					//边界角1绝对误差			
	float m_fAngleF_RelErr; 					//边界角1相对误差			
	long m_nAngleF_ErrorLogic; 					//边界角1误差判断逻辑 		
	float m_fAngleS_AbsErr; 					//边界角2绝对误差 			
	float m_fAngleS_RelErr; 					//边界角2相对误差 			
	long m_nAngleS_ErrorLogic; 					//边界角2误差判断逻辑
	float m_fMaxAngle_AbsErr; 					//最大灵敏角绝对误差		
	float m_fMaxAngle_RelErr; 					//最大灵敏角相对误差 		
	long m_nMaxAngle_ErrorLogic; 				//最大灵敏角误差判断逻辑
	float m_fRetCoef_AbsErr; 					//返回系数绝对误差 		
	float m_fRetCoef_RelErr;					//返回系数相对误差 		
	long m_nRetCoef_ErrorLogic; 				//返回系数误差判断逻辑 	
	
	
	/////////////////////////

	void init()
	{
		m_fStart = 0;
		m_fStop = 0;
		m_fStep = 0;
		m_fFaultTime = 0;
		m_nTestMode = FG_TestMode_ActValue;

		m_nFaultMode = FG_FaultMode_A;
		m_nChangeValue = FG_FM_Vaule_ShortVM;
		m_nVarIndexType = 0;
		m_fShortVm = 0;
		m_nShortVmType = FG_Type_VM_Plus;
		m_fShortVa = 0;
		m_fAngle = 0;

		m_fPrepareTime = 0;
		m_fPreFaultTime = 0;
		m_fPreFaultEDU = 0;
		m_fPreFaultEDI = 0;
		m_fEDUaIaAngle = 0;

		m_nBinLogic = 0;
		for (int i=0;i<MAX_BINARYIN_COUNT;i++)
		{
			m_binIn[i].init();
			for(int j=0;j<2;j++)
			{
				m_binOut[j][i].init();
			}
		}	
		m_fUSet = 0;		
		m_fISet = 0;		
		m_fImpAngleSet = 30;
		m_fHzSet = 50;
		m_fShortZImp = 0;
		m_fRetCoefSet = 0;	
		m_fMaxAngleSet = 0;	

		m_fUActVal_AbsErr = 0;
		m_fUActVal_RelErr = 0;
		m_nUActVal_ErrorLogic = 0;
		m_fIActVal_AbsErr = 0;
		m_fIActVal_RelErr = 0;
		m_nIActVal_ErrorLogic = 0;
		m_fImpAngleActVal_AbsErr = 0;
		m_fImpAngleActVal_RelErr = 0;
		m_nImpAngleActVal_ErrorLogic = 0;
		m_fShortZImpActVal_AbsErr = 0;
		m_fShortZImpActVal_RelErr = 0;
		m_nShortZImpActVal_ErrorLogic = 0;
		m_fHzActVal_AbsErr = 0;		
		m_fHzActVal_RelErr = 0;		
		m_nHzActVal_ErrorLogic = 0;
		m_fAngleF_AbsErr = 0;
		m_fAngleF_RelErr = 0;
		m_nAngleF_ErrorLogic = 0;
		m_fAngleS_AbsErr = 0;
		m_fAngleS_RelErr = 0;
		m_nAngleS_ErrorLogic = 0;
		m_fMaxAngle_AbsErr = 0;		
		m_fMaxAngle_RelErr = 0;		
		m_nMaxAngle_ErrorLogic = 0; 	
		m_fRetCoef_AbsErr = 0;
		m_fRetCoef_RelErr = 0;
		m_nRetCoef_ErrorLogic = 0;
	}

	tmt_fault_gradient_paras()	{}
}tmt_faultGradientParas;



///////////////////////////////////////////////返回结果
//返回参数-最大灵敏角
typedef struct tmt_fault_gradient_max_angle_result
{
public:
	float m_fAngleF;					//边界角1
	float m_fAngleS;					//边界角2
	float m_fMaxAngle;					//最大灵敏角
	int  m_nAngleF_StepIndex;			//首端边界角的递变步数,从0开始计数,0为始值
	long m_nAngleS_StepIndex;			//末端边界角的递变步数,从0开始计数,0为始值
	int   m_nActF;						//1-动作 0-没动作
	int   m_nActS;						//1-动作 0-没动作

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

	tmt_fault_gradient_max_angle_result(){}
}tmt_FaultGradientMaxAngleResult;


typedef struct tmt_fault_gradient_result
{
public:

	float m_fTripValue;							//动作值
	float m_fTripTime;							//动作时间
	float m_fTripValueChl[MAX_BINARYIN_COUNT];	//动作值，默认是0
	float m_fTripValueExChl[MAX_ExBINARY_COUNT];//0-非故障态开出 1-故障态开出
	float m_fReturnValue;
	float m_fReturnCoef;						//返回值/动作值
	int   m_nAct;								//1-动作 0-没动作
	float m_fPhiAngleValue;
	tmt_FaultGradientMaxAngleResult m_oMaxAngle;

	//评估
	float m_fTripUErrVal;						//电压动作值误差
	float m_fTripIErrVal;						//电流动作值误差
	float m_fTripHzErrVal;						//频率动作值误差
	float m_fImpAngleErrVal;					//阻抗角动作值误差
	float m_fShortZImp;							//短路阻抗动作值误差
	float m_fAngleF;							//边界角1
	float m_fAngleS;							//边界角2
	float m_fMaxAngleErrVal;					//最大灵敏角误差
	float m_fRetCoefErrVal;						//返回系数误差

	void init()
	{
		m_fAngleF = 0;
		m_fAngleS = 0;
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
		m_fImpAngleErrVal = 0;
		m_fRetCoefErrVal = 0;
		m_fMaxAngleErrVal = 0;

		for(int i=0; i<MAX_BINARYIN_COUNT; i++)
		{
			m_fTripValueChl[i] = 0;
		}

		for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			m_fTripValueExChl[i] = 0;
		}
	}

	tmt_fault_gradient_result()	{}
}tmt_faultGradientResult;


typedef struct tmt_fault_gradient_test : public TMT_PARAS_HEAD
{
public:
	tmt_faultGradientParas m_oFaultGradientParas;
	tmt_faultGradientResult m_oFaultResult;

	void init()
	{
		init_head(); 
		strcpy(m_pszMacroID,STT_MACRO_ID_FaultGradientTest);
		m_nSelected = 1;
		m_nVersion = 0x00010001;
		m_nTestState = 0;

		m_oFaultGradientParas.init();
		m_oFaultResult.init();
	}

	tmt_fault_gradient_test(){init();}
}tmt_faultGradientTest;



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void stt_xml_serialize(tmt_faultGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_faultGradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize);
//界面 基础值 序列化
void stt_xml_serialize_base(tmt_faultGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
//开入量 逻辑或与
void stt_xml_serialize_binary_AndOr(tmt_faultGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
//开入量 
void stt_xml_serialize_binary_in(tmt_faultGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
//常态开出 故障开出
void stt_xml_serialize_binary_out(tmt_faultGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
//整定值 
void stt_xml_serialize_FaultGradientSetting(tmt_faultGradientParas *pParas,CSttXmlSerializeBase *pXmlSierialize);
//评估 误差值 
void stt_xml_serialize_FaultGradientError(tmt_faultGradientParas *pParas,CSttXmlSerializeBase *pXmlSierialize);

//测试，文件生成 查看
void stt_xml_serialize_write_FaultGradientTest();