#pragma once
#include "..\..\..\..\Module\BaseClass\ExBaseList.h"

#define DKSOURCE_TIMER_NUMBER		10000

#define DKSOURCE_PARA_ID_ACOpenSource	_T("ACOpenSource")
#define DKSOURCE_PARA_ID_DCOpenSource	_T("DCOpenSource")
#define DKSOURCE_PARA_ID_Ua 			_T("Ua")
#define DKSOURCE_PARA_ID_Ub				_T("Ub")
#define DKSOURCE_PARA_ID_Uc				_T("Uc")
#define DKSOURCE_PARA_ID_Ia				_T("Ia")
#define DKSOURCE_PARA_ID_Ib				_T("Ib")
#define DKSOURCE_PARA_ID_Ic				_T("Ic")
#define DKSOURCE_PARA_ID_IPa			_T("IPa")
#define DKSOURCE_PARA_ID_IPb			_T("IPb")
#define DKSOURCE_PARA_ID_IPc			_T("IPc")
#define DKSOURCE_PARA_ID_Fa				_T("Fa")
#define DKSOURCE_PARA_ID_Fb				_T("Fb")
#define DKSOURCE_PARA_ID_Fc				_T("Fc")
#define DKSOURCE_PARA_ID_Range			_T("Range")
#define DKSOURCE_PARA_ID_Type			_T("Type")
#define DKSOURCE_PARA_ID_SData			_T("SData")
#define DKSOURCE_PARA_ID_Flag			_T("Flag")
#define DKSOURCE_PARA_ID_EV				_T("EV")
#define DKSOURCE_PARA_ID_ROUND			_T("ROUND")
//#define DKSOURCE_PARA_ID_DCData			_T("DCData")
#define DKSOURCE_PARA_ID_DC_U			_T("DC-U")
#define DKSOURCE_PARA_ID_DC_I			_T("DC-I")
#define DKSOURCE_PARA_ID_F				_T("F")
#define DKSOURCE_PARA_ID_UaRange		_T("UaRange")
#define DKSOURCE_PARA_ID_UbRange		_T("UbRange")
#define DKSOURCE_PARA_ID_UcRange		_T("UcRange")
#define DKSOURCE_PARA_ID_IaRange		_T("IaRange")
#define DKSOURCE_PARA_ID_IbRange		_T("IbRange")
#define DKSOURCE_PARA_ID_IcRange		_T("IcRange")
#define DKSOURCE_PARA_ID_UaPhase		_T("UaPhase")
#define DKSOURCE_PARA_ID_UbPhase		_T("UbPhase")
#define DKSOURCE_PARA_ID_UcPhase		_T("UcPhase")
#define DKSOURCE_PARA_ID_IaPhase		_T("IaPhase")
#define DKSOURCE_PARA_ID_IbPhase		_T("IbPhase")
#define DKSOURCE_PARA_ID_IcPhase		_T("IcPhase")
#define DKSOURCE_PARA_ID_Pa				_T("Pa")
#define DKSOURCE_PARA_ID_Pb				_T("Pb")
#define DKSOURCE_PARA_ID_Pc				_T("Pc")
#define DKSOURCE_PARA_ID_P				_T("P")
#define DKSOURCE_PARA_ID_Qa				_T("Qa")
#define DKSOURCE_PARA_ID_Qb				_T("Qb")
#define DKSOURCE_PARA_ID_Qc				_T("Qc")
#define DKSOURCE_PARA_ID_Q				_T("Q")
#define DKSOURCE_PARA_ID_Sa				_T("Sa")
#define DKSOURCE_PARA_ID_Sb				_T("Sb")
#define DKSOURCE_PARA_ID_Sc				_T("Sc")
#define DKSOURCE_PARA_ID_S				_T("S")
#define DKSOURCE_PARA_ID_CosFaia		_T("CosFaia")
#define DKSOURCE_PARA_ID_CosFaib		_T("CosFaib")
#define DKSOURCE_PARA_ID_CosFaic		_T("CosFaic")
#define DKSOURCE_PARA_ID_CosFai			_T("CosFai")
#define DKSOURCE_PARA_ID_PRINCIPLE		_T("PRINCIPLE")
#define DKSOURCE_PARA_ID_CloseloopEn	_T("CloseloopEn")
#define DKSOURCE_PARA_ID_HarmonicMode	_T("HarmonicMode")
#define DKSOURCE_PARA_ID_DI0			_T("DI0")
#define DKSOURCE_PARA_ID_DI1			_T("DI1")
#define DKSOURCE_PARA_ID_DI2			_T("DI2")
#define DKSOURCE_PARA_ID_DI3			_T("DI3")
//命令对应的idx
//系统信号
#define DKSOURCE_PROCEDURE_SYS_REPORT		31	//系统应答命令
#define DKSOURCE_PROCEDURE_SYS_GETINFO		32	//读取终端型号和版本号
#define DKSOURCE_PROCEDURE_SYS_SETMODE		33	//设置系统模式
#define DKSOURCE_PROCEDURE_SYS_ERROR		34	//发送故障代码
#define DKSOURCE_PROCEDURE_SYS_SETPAGE		35	//设置终端当前显示界面
//交流源表
#define DKSOURCE_PROCEDURE_AC_CLOSE			41	//源关闭命令
#define DKSOURCE_PROCEDURE_AC_OPEN			42	//源打开命令
#define DKSOURCE_PROCEDURE_AC_SETGEAR		43	//设置源档位参数
#define DKSOURCE_PROCEDURE_AC_SETRANGE		44	//设置源幅度参数
#define DKSOURCE_PROCEDURE_AC_SETPHASE		45	//设置源相位参数
#define DKSOURCE_PROCEDURE_AC_SETFREQ		46	//设置源频率
#define DKSOURCE_PROCEDURE_AC_SETPRINCIPLE	47	//设置源接线模式
#define DKSOURCE_PROCEDURE_AC_ENABLELOOP	48	//闭环控制使能
#define DKSOURCE_PROCEDURE_AC_SETHARMONICPARAM	49	//设置谐波参数
#define DKSOURCE_PROCEDURE_AC_SETVERIFICATION	410  //设置电能校验并启动
#define DKSOURCE_PROCEDURE_AC_GETERROR		411 //读电能误差
#define DKSOURCE_PROCEDURE_AC_SETACTIVEPOWER		412 //设置有功功率
#define DKSOURCE_PROCEDURE_AC_SETREACTIVEPOWER		413 //设置无功功率
//交流标准表
#define DKSOURCE_PROCEDURE_AC_GETPARAM		51 //读交流标准表参数
#define DKSOURCE_PROCEDURE_AC_GETSTATE		52 //读系统状态位(读交流标准表参数2)
//直流表
#define DKSOURCE_PROCEDURE_DC_SETMEASUREMENTRANGE			61 //设置直流表量程
#define DKSOURCE_PROCEDURE_DC_GETMEASUREMENTPARAM			62 //读直流表测量参数
#define DKSOURCE_PROCEDURE_DC_SETMEASUREMENTTYPE			63 //设置直流表测量类型
#define DKSOURCE_PROCEDURE_DC_SETMEASUREMENTPARAM2			64 //设置直流表测量参数(适用于双通道)
#define DKSOURCE_PROCEDURE_DC_GETMEASUREMENTPARAM2			65 //读直流表测量参数(适用于双通道)
//直流源
#define DKSOURCE_PROCEDURE_DC_CLOSE			71 //关闭直流源
#define DKSOURCE_PROCEDURE_DC_OPEN			72 //打开直流源
#define DKSOURCE_PROCEDURE_DC_SETGEAR		73 //设置直流源档位参数
#define DKSOURCE_PROCEDURE_DC_SETRANGE		74 //设置直流源幅值
#define DKSOURCE_PROCEDURE_DC_GETPARAM		75 //读直流源参数
//带时间控制的标准源
//遥信控制命令
#define DKSOURCE_PROCEDURE_REMOTE_SETOUTPUTSTATE		101 //设置数字量输出口的状态
#define DKSOURCE_PROCEDURE_REMOTE_SETCONTROL		102 //发送系统控制命令
#define DKSOURCE_PROCEDURE_REMOTE_GETINPUTSTATE		103//读数字量输入输入口的当前状态
#define DKSOURCE_PROCEDURE_REMOTE_GETINPUT		104//读取数字量输入口的事件记录
#define DKSOURCE_PROCEDURE_REMOTE_CLEARINPUT		105 //清空数字输入口的事件记录
#define DKSOURCE_PROCEDURE_REMOTE_SETPULSE		106 //设置脉冲参数
#define DKSOURCE_PROCEDURE_REMOTE_SETTIME 		107	//设置并启动对时
#define DKSOURCE_PROCEDURE_REMOTE_GETTIME		108 //读系统时间

//命令对应的macrotestID
//系统信号
#define DKSOURCE_MACROTEST_SYS_REPORT		""	//系统应答命令
#define DKSOURCE_MACROTEST_SYS_GETINFO		""	//读取终端型号和版本号
#define DKSOURCE_MACROTEST_SYS_SETMODE		""	//设置系统模式
#define DKSOURCE_MACROTEST_SYS_ERROR		""	//发送故障代码
#define DKSOURCE_MACROTEST_SYS_SETPAGE		""	//设置终端当前显示界面
//交流源表                                  
#define DKSOURCE_MACROTEST_AC_CONTROL		"ACControl"	//源控制命令 0关闭 1打开
#define DKSOURCE_MACROTEST_AC_SETGEAR		"ACSetGear"	//设置源档位参数
#define DKSOURCE_MACROTEST_AC_SETRANGE		"ACSetRange"	//设置源幅度参数
#define DKSOURCE_MACROTEST_AC_SETPHASE		"ACSetPhase"	//设置源相位参数
#define DKSOURCE_MACROTEST_AC_SETFREQ		"ACSetFreq"	//设置源频率
#define DKSOURCE_MACROTEST_AC_SETPRINCIPLE	""	//设置源接线模式
#define DKSOURCE_MACROTEST_AC_ENABLELOOP	"ACSetEnableLoop"	//闭环控制使能
#define DKSOURCE_MACROTEST_AC_SETHARMONICPARAM	"ACSetHarmonicParam"	//设置谐波参数
#define DKSOURCE_MACROTEST_AC_SETVERIFICATION	""  //设置电能校验并启动
#define DKSOURCE_MACROTEST_AC_GETERROR		"" //读电能误差
#define DKSOURCE_MACROTEST_AC_SETACTIVEPOWER		"" //设置有功功率
#define DKSOURCE_MACROTEST_AC_SETREACTIVEPOWER		"" //设置无功功率
//交流标准表
#define DKSOURCE_MACROTEST_AC_GETPARAM		"ACGetParam" //读交流标准表参数
#define DKSOURCE_MACROTEST_AC_GETSTATE		"" //读系统状态位(读交流标准表参数2)
//直流表
#define DKSOURCE_MACROTEST_DC_SETMEASUREMENTRANGE			"" //设置直流表量程
#define DKSOURCE_MACROTEST_DC_GETMEASUREMENTPARAM			"" //读直流表测量参数
#define DKSOURCE_MACROTEST_DC_SETMEASUREMENTTYPE			"" //设置直流表测量类型
#define DKSOURCE_MACROTEST_DC_SETMEASUREMENTPARAM2			"" //设置直流表测量参数(适用于双通道)
#define DKSOURCE_MACROTEST_DC_GETMEASUREMENTPARAM2			"" //读直流表测量参数(适用于双通道)
//直流源
#define DKSOURCE_MACROTEST_DC_CONTROL			"DCControl" //直流源控制 0关闭 1打开
#define DKSOURCE_MACROTEST_DC_SETGEAR		"DCSetGear" //设置直流源档位参数
#define DKSOURCE_MACROTEST_DC_SETRANGE		"DCSetRange" //设置直流源幅值
#define DKSOURCE_MACROTEST_DC_GETPARAM		"DCGetParam" //读直流源参数
//带时间控制的标准源
//遥信控制命令
#define DKSOURCE_MACROTEST_REMOTE_SETOUTPUTSTATE		"" //设置数字量输出口的状态
#define DKSOURCE_MACROTEST_REMOTE_SETCONTROL		"" //发送系统控制命令
#define DKSOURCE_MACROTEST_REMOTE_GETINPUTSTATE		""//读数字量输入输入口的当前状态
#define DKSOURCE_MACROTEST_REMOTE_GETINPUT		""//读取数字量输入口的事件记录
#define DKSOURCE_MACROTEST_REMOTE_CLEARINPUT		"" //清空数字输入口的事件记录
#define DKSOURCE_MACROTEST_REMOTE_SETPULSE		"" //设置脉冲参数
#define DKSOURCE_MACROTEST_REMOTE_SETTIME 		""	//设置并启动对时
#define DKSOURCE_MACROTEST_REMOTE_GETTIME		"" //读系统时间

#define DKSOURCE_UNLOCK					0
#define DKSOURCE_LOCK_REPORT			1
#define DKSOURCE_LOCK_USER				2

//idx - 命令码 转换函数
inline CString DKSource_Idx_To_Code(long nIdx)
{
	switch(nIdx)
	{
	case DKSOURCE_PROCEDURE_SYS_REPORT: return _T("4B");
	case DKSOURCE_PROCEDURE_SYS_GETINFO: return _T("4C");
	case DKSOURCE_PROCEDURE_SYS_SETMODE: return _T("44");
	case DKSOURCE_PROCEDURE_SYS_ERROR: return _T("52");
	case DKSOURCE_PROCEDURE_SYS_SETPAGE: return _T("4A");
	case DKSOURCE_PROCEDURE_AC_CLOSE: return _T("4F");
	case DKSOURCE_PROCEDURE_AC_OPEN: return _T("54");
	case DKSOURCE_PROCEDURE_AC_SETGEAR: return _T("31");
	case DKSOURCE_PROCEDURE_AC_SETRANGE: return _T("32");
	case DKSOURCE_PROCEDURE_AC_SETPHASE: return _T("33");
	case DKSOURCE_PROCEDURE_AC_SETFREQ: return _T("34");
	case DKSOURCE_PROCEDURE_AC_SETPRINCIPLE: return _T("35");
	case DKSOURCE_PROCEDURE_AC_ENABLELOOP: return _T("36");
	case DKSOURCE_PROCEDURE_AC_SETVERIFICATION: return _T("37");
	case DKSOURCE_PROCEDURE_AC_SETACTIVEPOWER: return _T("50");
	case DKSOURCE_PROCEDURE_AC_SETREACTIVEPOWER: return _T("51");
	case DKSOURCE_PROCEDURE_AC_SETHARMONICPARAM: return _T("58");
	case DKSOURCE_PROCEDURE_AC_GETPARAM: return _T("4D");
	case DKSOURCE_PROCEDURE_AC_GETSTATE: return _T("4E");
	case DKSOURCE_PROCEDURE_AC_GETERROR: return _T("45");
	case DKSOURCE_PROCEDURE_DC_SETMEASUREMENTRANGE: return _T("61");
	case DKSOURCE_PROCEDURE_DC_GETMEASUREMENTPARAM: return _T("62");
	case DKSOURCE_PROCEDURE_DC_SETMEASUREMENTTYPE: return _T("63");
	case DKSOURCE_PROCEDURE_DC_SETMEASUREMENTPARAM2: return _T("64");
	case DKSOURCE_PROCEDURE_DC_GETMEASUREMENTPARAM2: return _T("65");
	case DKSOURCE_PROCEDURE_DC_SETGEAR: return _T("66");
	case DKSOURCE_PROCEDURE_DC_CLOSE: return _T("68");
	case DKSOURCE_PROCEDURE_DC_OPEN: return _T("67");
	case DKSOURCE_PROCEDURE_DC_SETRANGE: return _T("69");
	case DKSOURCE_PROCEDURE_DC_GETPARAM: return _T("79");
	case DKSOURCE_PROCEDURE_REMOTE_SETOUTPUTSTATE: return _T("90");
	case DKSOURCE_PROCEDURE_REMOTE_SETCONTROL: return _T("91");
	case DKSOURCE_PROCEDURE_REMOTE_GETINPUTSTATE: return _T("92");
	case DKSOURCE_PROCEDURE_REMOTE_GETINPUT: return _T("93");
	case DKSOURCE_PROCEDURE_REMOTE_CLEARINPUT: return _T("94");
	case DKSOURCE_PROCEDURE_REMOTE_SETPULSE: return _T("95");
	case DKSOURCE_PROCEDURE_REMOTE_SETTIME: return _T("96");
	case DKSOURCE_PROCEDURE_REMOTE_GETTIME: return _T("97");
	default:
		break;
	}
	return _T("");
}

inline long DKSource_Str_To_Idx(const CString& strTestMacroID, long nParamNum = 0)
{
	if(strTestMacroID == DKSOURCE_MACROTEST_AC_CONTROL)
	{
		if (nParamNum == 0)
		{
			return DKSOURCE_PROCEDURE_AC_CLOSE;
		}
		else
		{
			return DKSOURCE_PROCEDURE_AC_OPEN;
		}
	}
	else if (strTestMacroID == DKSOURCE_MACROTEST_AC_SETGEAR)
	{		 
		return DKSOURCE_PROCEDURE_AC_SETGEAR;
	}
	else if (strTestMacroID == DKSOURCE_MACROTEST_AC_SETRANGE)
	{
		return DKSOURCE_PROCEDURE_AC_SETRANGE;
	}
	else if (strTestMacroID == DKSOURCE_MACROTEST_AC_SETPHASE)
	{
		return DKSOURCE_PROCEDURE_AC_SETPHASE;
	}
	else if (strTestMacroID == DKSOURCE_MACROTEST_AC_SETFREQ)
	{
		return DKSOURCE_PROCEDURE_AC_SETFREQ;
	}
	else if (strTestMacroID == DKSOURCE_MACROTEST_AC_ENABLELOOP)
	{
		return DKSOURCE_PROCEDURE_AC_ENABLELOOP;
	}
	else if (strTestMacroID == DKSOURCE_MACROTEST_AC_SETHARMONICPARAM)
	{
		return DKSOURCE_PROCEDURE_AC_SETHARMONICPARAM;
	}
	else if (strTestMacroID == DKSOURCE_MACROTEST_AC_GETPARAM)
	{
		return DKSOURCE_PROCEDURE_AC_GETPARAM;
	}
	else if (strTestMacroID == DKSOURCE_MACROTEST_DC_CONTROL)
	{
		if (nParamNum == 0)
		{
			return DKSOURCE_PROCEDURE_DC_CLOSE;
		}
		else
		{
			return DKSOURCE_PROCEDURE_DC_OPEN;
		}
	}
	else if (strTestMacroID == DKSOURCE_MACROTEST_DC_SETGEAR)
	{
		return DKSOURCE_PROCEDURE_DC_SETGEAR;
	}
	else if (strTestMacroID == DKSOURCE_MACROTEST_DC_SETRANGE)
	{
		return DKSOURCE_PROCEDURE_DC_SETRANGE;
	}
	else if (strTestMacroID == DKSOURCE_MACROTEST_DC_GETPARAM)
	{
		return DKSOURCE_PROCEDURE_DC_GETPARAM;
	}

	return 0;
}

inline CString DKSource_Idx_To_Str(long nIdx)
{
	if(nIdx == DKSOURCE_PROCEDURE_AC_CLOSE
		|| nIdx == DKSOURCE_PROCEDURE_AC_OPEN)
	{
		return DKSOURCE_MACROTEST_AC_CONTROL;
	}
	else if (nIdx == DKSOURCE_PROCEDURE_AC_SETGEAR)
	{		 
		return DKSOURCE_MACROTEST_AC_SETGEAR;
	}
	else if (nIdx == DKSOURCE_PROCEDURE_AC_SETRANGE)
	{
		return DKSOURCE_MACROTEST_AC_SETRANGE;
	}
	else if (nIdx == DKSOURCE_PROCEDURE_AC_SETPHASE)
	{
		return DKSOURCE_MACROTEST_AC_SETPHASE;
	}
	else if (nIdx == DKSOURCE_PROCEDURE_AC_SETFREQ)
	{
		return DKSOURCE_MACROTEST_AC_SETFREQ;
	}
	else if (nIdx == DKSOURCE_PROCEDURE_AC_ENABLELOOP)
	{
		return DKSOURCE_MACROTEST_AC_ENABLELOOP;
	}
	else if (nIdx == DKSOURCE_PROCEDURE_AC_SETHARMONICPARAM)
	{
		return DKSOURCE_MACROTEST_AC_SETHARMONICPARAM;
	}
	else if (nIdx == DKSOURCE_PROCEDURE_AC_GETPARAM)
	{
		return DKSOURCE_MACROTEST_AC_GETPARAM;
	}
	else if (nIdx == DKSOURCE_PROCEDURE_DC_OPEN
		|| nIdx == DKSOURCE_PROCEDURE_DC_CLOSE)
	{
		return DKSOURCE_MACROTEST_DC_CONTROL;
	}
	else if (nIdx == DKSOURCE_PROCEDURE_DC_SETGEAR)
	{
		return DKSOURCE_MACROTEST_DC_SETGEAR;
	}
	else if (nIdx == DKSOURCE_PROCEDURE_DC_SETRANGE)
	{
		return DKSOURCE_MACROTEST_DC_SETRANGE;
	}
	else if (nIdx == DKSOURCE_PROCEDURE_DC_GETPARAM)
	{
		return DKSOURCE_MACROTEST_DC_GETPARAM;
	}
}

inline CString DKSource_URange_To_DCStr(long nRange)
{
	switch(nRange)
	{
	case 0: return _T("1000V");
	case 1: return _T("600V");
	case 2: return _T("300V");
	case 3: return _T("150V");
	case 4: return _T("75V");
	case 5: return _T("30V");
	case 6: return _T("15V");
	case 7: return _T("7.5V");
	case 8: return _T("3V");
	case 9: return _T("1.5V");
	case 10: return _T("1V");
	case 11: return _T("500mV");
	case 12: return _T("200mV");
	case 13: return _T("100mV");
	case 14: return _T("75mV");
	break;
	}
	return _T("0");
}

inline CString DKSource_IRange_To_DCStr(long nRange)
{
	switch(nRange)
	{
	case 0: return _T("50A");
	case 1: return _T("25A");
	case 2: return _T("5A");
	case 3: return _T("1A");
	case 4: return _T("500mA");
	case 5: return _T("200mA");
	case 6: return _T("100mA");
	case 7: return _T("50mA");
	case 8: return _T("20mA");
	case 9: return _T("10mA");
	case 10: return _T("1mA");
	case 11: return _T("500uA");
	case 12: return _T("100uA");
	case 13: return _T("10uA");
	default: break;
	}
	return _T("0");
}

inline CString DKSource_URange_To_ACStr(long nRange)
{
	switch(nRange)
	{
	case 0: return _T("600V");
	case 1: return _T("300V");
	case 2: return _T("150V");
	case 3: return _T("75V");
	case 4: return _T("30V");
	case 5: return _T("15V");
	case 6: return _T("7V");
	case 7: return _T("3V");
	default: break;
	}
	return _T("0");
}

inline CString DKSource_IRange_To_ACStr(long nRange)
{
	switch(nRange)
	{
	case 0: return _T("50A");
	case 1: return _T("25A");
	case 2: return _T("5A");
	case 3: return _T("1A");
	case 4: return _T("500mA");
	case 5: return _T("200mA");
	case 6: return _T("50mA");
	case 7: return _T("20mA");
	default: break;
	}
	return _T("0");
}

class CHarmonic : public CExBaseList
{
public:
	long m_nHarmonic;
	float m_fAmplitude;
	float m_fAngle;

public:
	CHarmonic()
	{
		m_nHarmonic = 0;
		m_fAmplitude = 0;
		m_fAngle = 0;
	}
	virtual ~CHarmonic(){}
};

//所选要获取的全变量
struct tagDKSource
{
	float m_fUa;
	float m_fUb;
	float m_fUc;
	float m_fIa;
	float m_fIb;
	float m_fIc;
	float m_fIPa;
	float m_fIPb;
	float m_fIPc;
	float m_fFa;
	float m_fFb;
	float m_fFc;
	long m_nType; //Flag,Channel
	long m_nCount;
	long m_nRange;
	float m_fSData;
	long m_nEnable; //CloseLoop
	long m_nMode; //Principle,HarmonicMode,Node
	long m_nPage;
	float m_fMPC;
	float m_fMQC;
	float m_fSPC;
	float m_fSQC;
	long m_nMDIV;
	long m_nMROU;
	float m_fPower;
	long m_nD0; //MinX
	long m_nD1;
	long m_nD2;
	long m_nD3;
	CExBaseList* m_pHarmonic;

	tagDKSource()
	{
		m_fUa = 0;
		m_fUb = 0;
		m_fUc = 0;
		m_fIa = 0;
		m_fIb = 0;
		m_fIc = 0;
		m_fIPa = 0;
		m_fIPb = 0;
		m_fIPc = 0;
		m_fFa = 0;
		m_fFb = 0;
		m_fFc = 0;
		m_nCount = 0;
		m_nType = 0;
		m_nRange = 0;
		m_fSData = 0;
		m_nMode = 0;
		m_nPage = 0;
		m_fPower = 0;
		m_nD0 = 0;
		m_nD1 = 0;
		m_nD2 = 0;
		m_nD3 = 0;
		m_pHarmonic = 0;
	}

	~tagDKSource()
	{
		delete m_pHarmonic;
		m_pHarmonic = NULL;
	}
};
