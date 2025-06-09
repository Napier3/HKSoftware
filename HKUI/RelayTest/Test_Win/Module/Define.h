#ifndef DIFFERDEFINE_H
#define DIFFERDEFINE_H
#include <QMap>
#include <QString>
#include <QPen>
#include <QMetaType>

#include "../../Module/SttTestSysGlobalPara.h"

#define STT_UI_RUN_STATE_Stoped                              0
#define STT_UI_RUN_STATE_StateTested_NotEditable             1
#define STT_UI_RUN_STATE_StateTested_Editable                2

//启动电流 比例制动 二次谐波制动 五次谐波制动 速断电流 动作电流
enum ErrorType {Error_A_JD=0,Error_B_JD,Error_C_JD,Error_AB_DL,Error_BC_DL,Error_CA_DL,\
	Error_AB_JDDL,Error_BC_JDDL,Error_CA_JDDL,Error_ABC_DL,Error_SINGLE_ZK};
enum ChanelType{ChanelUa=1,ChanelUb,ChanelUc,ChanelUz,ChanelIa,ChanelIb,ChanelIc,ChannelI0};
enum PTPhase {Phase_A=1,Phase_B,Phase_C,Phase_AB,Phase_BC,Phase_CA,Phase_ABC};
enum LogLevel {LEVEL_COMMON=0,LEVEL_WARN,LEVEL_INFO,LEVEL_ERROR};
enum TABLETYPE{TYPE_V=0,TYPE_I};
enum PhaseType{Phase_P=0,Phase_N,Phase_Z};
enum MOUDLEType{Moudle_U=0,Moudle_I};
enum ZKType {TYPE_LINE=0,TYPE_CIRCLE,TYPE_EDGE}; //线、圆、棱
enum ErrorVar {Error_U1_1 = 0, Error_U1_2, Error_U1_3, Error_U2_1, Error_U2_2, Error_U2_3};
enum CurrentVar {Current_I1_1 = 0, Current_I1_2, Current_I1_3, Current_I2_1, Current_I2_2, Current_I2_3,
	Current_I3_1, Current_I3_2, Current_I3_3, Current_I4_1, Current_I4_2, Current_I4_3};
enum DifferCurrentVar {ZERO = 0, DifferCurrent_I1_1, DifferCurrent_I1_2, DifferCurrent_I1_3, DifferCurrent_I2_1, DifferCurrent_I2_2, DifferCurrent_I2_3,
DifferCurrent_I3_1, DifferCurrent_I3_2, DifferCurrent_I3_3, DifferCurrent_I4_1, DifferCurrent_I4_2, DifferCurrent_I4_3};
/*
enum TestTypeOfDiffer {TEST_QD=0,TEST_ZD1,TEST_ZD1_2,TEST_ZD2,TEST_ZD2_2,TEST_ZD3,TEST_ZD3_2,\
TEST_ZD4,TEST_ZD4_2,TEST_HARM,TEST_SD,TEST_ACTION,TEST_OTHER};
*/
enum TableMode{Mode_Ana4U3I_4U=0,Mode_Ana4U3I_3I,Mode_Ana4U4I_4U,Mode_Ana4U4I_4I,Mode_Ana6U6I_F3U,Mode_Ana6U6I_F3I,Mode_Ana6U6I_S3U,Mode_Ana6U6I_S3I,\
Mode_Dig4U3I_4U,Mode_Dig4U3I_3I,Mode_Dig4U4I_4U,Mode_Dig4U4I_4I,Mode_Dig6U6I_F3U,Mode_Dig6U6I_F3I,Mode_Dig6U6I_S3U,Mode_Dig6U6I_S3I,};

// enum para_type
// {
// 	va1_type = 0,
// 	vb1_type = 1,
// 	vc1_type = 2,
// 	null_type = 3,
// 	vab1_type = 4,
// 	vbc1_type = 5,
// 	vca1_type = 6,
// 	vabc1_type = 7,
// 	va2_type = 8,
// 	vb2_type = 9,
// 	vc2_type = 10,
// 	vabc2_type = 11,
// 	ia1_type = 12,
// 	ib1_type = 13,
// 	ic1_type = 14,
// 	iab1_type = 15,
// 	ibc1_type = 16,
// 	ica1_type = 17,
// 	iabc1_type = 18,
// 	ia2_type = 19,
// 	ib2_type = 20,
// 	ic2_type = 21,
// 	iabc2_type = 22,
// 	vall_type= 23,
// 	iall_type = 24,
// 	vdc_type = 25,
// 	vz_type=26,
// 	vab2_type = 27,
// 	vbc2_type = 28,
// 	vca2_type = 29,
// 	iab2_type = 30,
// 	ibc2_type = 31,
// 	ica2_type = 32,
// 	iabcAdd_type = 33,
// 	ia2b2c2Add_type =34,				 //a2+b2+c2
// 	vabcAdd_type= 35,
// 	va2b2c2Add_type = 36,				 //va2+vb2+vc2
// 	freAll_type = 37,
// 	iaia2Add_type = 38,					 //ia+ia2
// 	ibib2Add_type = 39,					 //ib+ib2
// 	icic2Add_type = 40,					 //ic+ic2
// 	iaia2Add_ibib2Add_icic2Add_type = 41,//ia+ia2,ib+ib2,ic+ic2
// 	iaia2ibib2icic2Add_type = 42		 //ia+ia2+ib+ib2+ic+ic2
// };

enum Value_TypeMarkDisp {MarkDispType_Int = 0, MarkDispType_UnInt,MarkDispType_Float};
enum AppType{App_PTU=0,App_RelayTest=1};

enum changed_type
{
	amplitude_type = 0,
	phasor_type = 1,
	fre_type = 2
};

enum plugin_type{
	P_Analog = 0,
	P_Digit,
	P_LowSignal,
	P_Common,
	P_Harm
};

Q_DECLARE_METATYPE(para_type);
Q_DECLARE_METATYPE(LogLevel); 
Q_DECLARE_METATYPE(ErrorType); 
Q_DECLARE_METATYPE(TABLETYPE);
Q_DECLARE_METATYPE(MOUDLEType);
Q_DECLARE_METATYPE(ErrorVar);
Q_DECLARE_METATYPE(CurrentVar);

#define TESTTYPE_ANA		0
#define TESTTYPE_DGT		1
#define TESTTYPE_LOW		2
#define TESTTYPE_MIX_ANADGT	3
#define TESTTYPE_MIX_ANALOW	4
#define TESTTYPE_MIX_DGTLOW	5
#define TESTTYPE_MIX_ALL	6

#define CIRCLECOUNT 2000
#define CHANLEPOINT 4000
#define RADIO 1.4
#define HARMNUMBER 31   //32
#define MAXHARMCOUNT 51  //32

#define MAXHZ 3000
#define pi 3.14159265357979823846
#define G3 1.7320508
#define G2 1.4142135623731
#define FRADIO 1.1

#define EPSINON 0.00000001

#define Postfix_StateTest		"sttxml"
#define Postfix_ManualTest		"mntxml"
#define Postfix_HarmTest		"hrmxml"
#define Postfix_SoeTest			"soexml"
#define Postfix_SystemParas		"sysxml"
#define Postfix_GradientTest	"grtxml"
#define Postfix_CBOperateTest	"cbtxml"
#define Postfix_DistanceTest	"dttxml"
#define Postfix_ZeroSequenceTest "zstxml"
#define Postfix_Reclose			"rctxml"
#define Postfix_OverCurrentTest  "octxml"
#define Postfix_DifferTest		"dftxml"


struct LineInfor
{
	QString m_UIType;
	float m_RealValue;
	float m_XW;
	bool m_bShowOrHide;
	QPen m_Color;
	float m_ChangeFactor;
};

struct ShortCalcuPara
{
	int nRadio;
	bool bZPhi;
	bool bRX;
	bool bPrimaryPara;
	int nFaultType;
	float fZ;
	float fR;
	float fX;
	float fPhi;

	float fImax;
	float fVmax;
	float fKr;
	float fKx;
	float fDLI;
	float fDLV;
	float fZSZL;
	int nCalMode;
	int nCalType;
	float fVnom;

	bool bFaultDir;
	bool bCTPoint;
	float fIfh;			//负荷电流
	float fPowerAngle;  //负荷功角

	ShortCalcuPara()
	{
		nRadio = 0;
		bZPhi = true;;
		bRX = false;
		bPrimaryPara = false;
		nFaultType = 0;
		fZ = 1;
		fR = 0;
		fX  = 1;
		fPhi = 90;

		fImax = 5000;
		fVmax = 5000000;
		fKr=0.67;
		fKx=0;
		fDLI = 5;
		fDLV = 0;
		fZSZL=0;
		nCalMode=0;
		nCalType=0;
		fVnom=57.74;

		bFaultDir=1;
		bCTPoint=1;
		fIfh=0;
		fPowerAngle=0;
	}

	ShortCalcuPara &operator = (const ShortCalcuPara &right)
	{
		nRadio = right.nRadio;
		bZPhi = right.bZPhi;
		bRX = right.bRX;
		bPrimaryPara = right.bPrimaryPara;
		nFaultType = right.nFaultType;
		fZ = right.fZ;
		fR = right.fR;
		fX  = right.fX;
		fPhi = right.fPhi;

		fImax = right.fImax;
		fVmax = right.fVmax;
		fKr=right.fKr;
		fKx=right.fKx;
		fDLI = right.fDLI;
		fDLV = right.fDLV;
		fZSZL= right.fZSZL;
		nCalMode=right.nCalMode;
		nCalType=right.nCalType;
		fVnom=right.fVnom;

		bFaultDir=right.bFaultDir;
		bCTPoint=right.bCTPoint;
		fIfh=right.fIfh;
		fPowerAngle=right.fPowerAngle;
		return *this;
	}
};

struct GPSDATA
{
	int nSecond;
	int nNanoSec;					
	GPSDATA()
	{
		nSecond  = 0;
		nNanoSec = 0;
	}

	GPSDATA &operator = (const GPSDATA &right)
	{
		if (this == &right)
		{
			return *this;
		}
		nSecond = right.nSecond;
		nNanoSec = right.nNanoSec;

		return *this;
	}
};

struct HarmSwitchPara
{
	int KA;
	int KB;
	int KC;
	int KD;
	int KE;
	int KF;
	int KG;
	int KH;
	int KI;
	int KJ;

	int Logic;
	int Out1;
	int Out2;
	int Out3;
	int Out4;
	int Out5;
	int Out6;
	int Out7;
	int Out8;

	HarmSwitchPara()
	{
		KA = 0;
		KB = 0;
		KC = 0;
		KD = 0;
		KE = 0;
		KF = 0;
		KG = 0;
		KH = 0;
		KI = 0;
		KJ = 0;
		Logic = 0;
		Out1 = 1;
		Out2 = 1;
		Out3 = 1;
		Out4 = 1;
		Out5 = 1;
		Out6 = 1;
		Out7 = 1;
		Out8 = 1;	
	}

	HarmSwitchPara &operator = (const HarmSwitchPara &right)
	{
		KA = right.KA;
		KB = right.KB;
		KC = right.KC;
		KD = right.KD;
		KE = right.KE;
		KF = right.KF;
		KG = right.KG;
		KH = right.KH;
		KI = right.KI;
		KJ = right.KJ;
		Logic = right.Logic;
		Out1 = right.Out1;
		Out2 = right.Out2;
		Out3 = right.Out3;
		Out4 = right.Out4;
		Out5 = right.Out5;
		Out6 = right.Out6;
		Out7 = right.Out7;
		Out8 = right.Out8;
		return *this;
	}
};

struct SwitchPara
{
	int KA;
	bool bKA;
	int KB;
	bool bKB;
	int KC;
	bool bKC;
	int KCHZ;
	int K1;
	int K2;
	int K3;
	int K4;
	int K5;
	int K6;
	int K7;
	int K8;
	int OutMode;
	float TurnTime;
	float HoldTime;

	SwitchPara()
	{
		KA = 0;
		KB = 1;
		KC = 2;
		KCHZ = 3;
		K1 = 0;
		K2 = 0;
		K3 = 0;
		K4 = 0;
		K5 = 0;
		K6 = 0;
		K7 = 0;
		K8 = 0;
		OutMode = 0;
		TurnTime = 0.1;
		HoldTime = 0.2;

		bKA = false;
		bKB = false;
		bKC = false;
	}

	SwitchPara &operator = (const SwitchPara &right)
	{
		KA = right.KA;
		KB = right.KB;
		KC = right.KC;
		KCHZ = right.KCHZ;
		K1 = right.K1;
		K2 = right.K2;
		K3 = right.K3;
		K4 = right.K4;
		K5 = right.K5;
		K6 = right.K6;
		K7 = right.K7;
		K8 = right.K8;
		OutMode = right.OutMode;
		TurnTime = right.TurnTime;
		HoldTime = right.HoldTime;

		bKA = right.bKA;
		bKB = right.bKB;
		bKC = right.bKC;

		return *this;
	}
};

struct TestInfo
{
	QString strName;
	bool bSelected;
	int index; //因为可重复的 所以从1-N
	QString strResult;
	int iStatus;  //0:未测试 1 已测试并成功 2已测试但是失败
	TestInfo()
	{
		iStatus = 0;
		bSelected = false;
	}

	TestInfo &operator = (const TestInfo &right)
	{
		iStatus = right.iStatus;
		strName = right.strName;
		bSelected = right.bSelected;
		strResult = right.strResult;
		index = right.index;

		return *this;
	}
};

Q_DECLARE_METATYPE(SwitchPara);
Q_DECLARE_METATYPE(GPSDATA);

Q_DECLARE_METATYPE(ShortCalcuPara);

//短路计算
typedef enum tag_FaultType          // 故障类型
{
	PHASE_A_GROUNDING       = 0,    // A相接地
	PHASE_B_GROUNDING       = 1,    // B相接地
	PHASE_C_GROUNDING       = 2,    // C相接地
	PHASE_AB_SHORT_CIRCUIT  = 3,    // AB短路
	PHASE_BC_SHORT_CIRCUIT  = 4,    // BC短路
	PHASE_CA_SHORT_CIRCUIT  = 5,    // CA短路
	PHASE_AB_GROUND_SHORT   = 6,    // AB接地短路
	PHASE_BC_GROUND_SHORT   = 7,    // BC接地短路
	PHASE_CA_GROUND_SHORT   = 8,    // CA接地短路
	PHASE_ABC_SHORT_CIRCUIT = 9,    // ABC三相短路
	SINGLE_PHASE_FAULT      = 10    // 单相系统
}FaultType;

typedef enum tag_ImpedanceMode    // 阻抗参数形式
{
	Z_PHI_MODE = 0,   // Z, Phi 形式
	R_X_MODE   = 1,   // R, X 形式
}ImpedanceMode;

typedef struct tag_ValuePair
{
	union
	{
		double Z;
		double R;
		double Kr;
		double Amp;
	};
	union
	{
		double Phi;
		double X;
		double Kx;
	};
} ValuePair;

typedef struct tag_ImpedanceInfo
{
	ImpedanceMode mode;      // 阻抗参数形式
	ValuePair Z_Phi;         // Z, Phi 形式
	ValuePair R_X;           // R, X 形式
}ImpedanceInfo;

typedef enum tag_ShortcutComputationalModel
{
	KEEP_CURRENT_CONST     = 0,     // 电流不变
	KEEP_VOLTAGE_CONST     = 1,     // 电压不变
	KEEP_IMPEDANCE_CONST   = 2      // 系统阻抗不变
}ShortcutComputationalModel;

typedef struct tag_ShortcutComputationalInfo
{
	ShortcutComputationalModel mode;      // 计算模型类型
	double Current;      // 保持不变的电流值
	double Voltage;      // 保持不变的电压值
	double Impedance;      // 保持不变的|ZS/ZL|值
}ShortcutComputationalInfo;

typedef enum tag_ZeroSeqCompensateCoefMode    // 零序补偿系数的计算方法
{
	ZERO_SEQ_COMP_KL    = 0,      // KL
	ZERO_SEQ_COMP_KR_KX = 1,      // Kr,Kx
	ZERO_SEQ_COMP_Z0_Z1 = 2       // Z0,Z1
}ZeroSeqCompensateCoefMode;

typedef struct tag_ZeroSeqCompensateCoefInfo
{
	ZeroSeqCompensateCoefMode mode;   // 计算模型类型
	ValuePair KL;                     // KL
	ValuePair Kr_Kx;                  // Kr,Kx
	ValuePair Z0_Z1;                  // Z0,Z1
}ZeroSeqCompensateCoefInfo;

typedef struct tag_ShortcutCalcInfo
{
	FaultType                  Mode;
	ImpedanceInfo              Impedance;
	bool                       FaultIsPositiveDirection;
	bool                       CTIsBusDirection;
	ShortcutComputationalInfo  ShortcutCompute;
	ZeroSeqCompensateCoefInfo  ZeroSeqCompensateCoef;  // 零序补偿系数
	double                     LoadCurrent;            // 负荷电流
	double                     LoadAngle;              // 负荷功角
} ShortcutCalcInfo;

//功率、序分量、线电压计算
typedef struct tag_PowerValue
{
	double FactorA;
	double FactorB;
	double FactorC;
	double PA;
	double PB;
	double PC;
	double PSum;
	double QA;
	double QB;
	double QC;
	double QSum;
	double SA;
	double SB;
	double SC;
	double SSum;
} PowerValue;

typedef struct tag_SeqValue
{
	double amp;
	double phase;
} SeqValue;

//测试结果项
typedef enum tag_ResultType
{
	RESULTTYPE_NONE			= 0,
	RESULTTYPE_START		= 1,    //开始测试
	RESULTTYPE_STOP			= 2,	//停止测试
	RESULTTYPE_FINISH		= 3,    //结束测试
	RESULTTYPE_PARACHG		= 4,	//参数变化
	RESULTTYPE_BINCHG		= 5,    //开入变位
	RESULTTYPE_GRADIENTRET  = 6,    //递变返回
	RESULTTYPE_BOUTCHG		= 7,    //开出变位
	RESULTTYPE_GRADIENTEND  = 8     //递变结束
}ResultType;

typedef struct tmt_result_item
{
	ResultType nType;			//结果类型：1开始测试；2停止测试；3参数变化(状态切换)；4开入变位；5递变返回；6开出变位；7递变结束
	unsigned int nSec;			//产生结果的时间秒值
	unsigned int nNanoSec;		//产生结果的时间纳秒值
	unsigned int nInput;		//产生结果时开入量的值            			
	unsigned int currentIndex;	//当前状态索引号
	
	unsigned int nExInput1;
	unsigned int nExInput2;

	tmt_result_item()
	{
		nType = RESULTTYPE_NONE;
		nSec = 0;
		nNanoSec = 0;
		nInput = 0;
		currentIndex = 0;
		nExInput1 = nExInput2 = 0;
	}

}tmt_ResultItem;

typedef struct tmt_act_info
{
	QString strSwitchName;
	float fActTime;
	float fActValue;
	QStringList aStrActValue;
	int nBinIndex;     //对应动作的开入 1-开入A，2-开入B ，3-开入C， 4-开入D, 5-开入E，6-开入F ，7-开入G， 8-开入H

	tmt_act_info()
	{
		fActTime = 0;
		fActValue = 0;
		nBinIndex = 0;
		aStrActValue.clear();
	}
}tmt_ActInfo;

typedef struct tmt_testresult_data
{
	QList<tmt_ActInfo> ActInfoList;
	bool bMark;  //计算返回值和返回时间的标记点
	float fReturnValue;
	float fReturnTime;
	long nCurrStepIndex;

	tmt_testresult_data()
	{
		ActInfoList.clear();
		bMark = false;
		fReturnValue = 0;
		fReturnTime = 0;
		nCurrStepIndex = 0;
	}
}tmt_TestResultData;
#endif

