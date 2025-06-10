#pragma once

#include "../tmt_common_def.h"
#include "../tmt_state_test.h"
#include"../../../SttTestBase/SttXmlSerialize.h"
#include <math.h>

#define STT_FaultProperty_Transient                  0           
#define STT_FaultProperty_Permanent                  1   



#define MAX_NAME_LEN  32
typedef struct tmt_impedance_paras
{
public:
	virtual void init()
	{
		m_fSetting[0] = 2.85f;
		m_fSetting[1] = 0.5f;
		m_fRate[0] = 1.0f;
		m_fRate[1] = 1.0f;
		m_fImpedance[0] = 2.85f;		//短路阻抗
		m_fImpedance[1] = 0.5;	
		m_fImpAngle[0] = 90;			//阻抗角 m_fPhi
		m_fImpAngle[1] = 90;
		m_fSCCurrent[0] = 5.000f;		//短路电流 原m_fItest  m_fItestdev
		m_fSCCurrent[1] = 5.000f;
		m_fSCVoltage[0] = 50.000f;		//短路电压 原m_fVtest  m_fVtestdev
		m_fSCVoltage[1] = 0.000f;
		m_nFaultDir[0] = 1;				//故障方向 原m_bFaultDirFirst m_bFaultDirSecond
		m_nFaultDir[1] = 1;
		m_nCTPoint = 1;			//TA正极性  S1=指向母线,S2=指向线路  m_bCTPoint
		m_nPTPoint = 0;			//TV安装位置  S1=母线侧,S2=线路侧  m_bPTPoint
		m_nFaultType[0] = 0;			//故障类型 
		m_nFaultType[1] = 0;
		m_nCalMode = 0;			//计算方式，原m_nTestMode 永远为0
		m_fPrepareTime = 5.000;		//常态时间
		m_fPreFaultTime = 2.000f;		//故障前时间
		m_fMaxFaultTime = 0.200f;			//故障时间
		m_fMarginTime = 0.2f;//
		m_bImitatePT = FALSE;		//是否模拟PT断线
		m_nImitPTPhase = STT_PT_IMIT_PHASE_A;			//模拟A相
		m_bCBSimulation = 0;		//断路器模拟  S1=不模拟,S2=模拟 0
		m_fCBTripTime = 0.200f;		//分闸时间	200ms
		m_fCBCloseTime = 0.100f;		//合闸时间	100ms
		m_fFaultAngle = 0;		//故障角 永远为0
		m_fFaultAng_0 = 0;
		m_nFaultIncMode = 0;		//故障开始方式 永远为0
		m_nFaultTrigMode = 0;					//故障触发方式 S1=时间,S2=按键,S3=开入量“H”触发,S4=GPS 0
		m_nFaultProperty = STT_FaultProperty_Transient;		//故障性质，0-瞬时 1-永久 m_bLastFault
		m_bTransFault = 0;		//是否转换性故障 0
// 		m_nTransMode = 0;
 		m_fTransTime = 0.1f;		//故障转换时间  0.1
		m_fPostFaultTime = 2.000f;		//保护动作后持续时间  2.000f
		//通用参数
		m_nVzDefine = 0;			//Uz输出定义 S1=0,S2=√3×3Vo,S3=-√3×3Vo,S4=3Vo,S5=-3Vo,S6=抽取电压
//		m_nVzPhDefine = 0;		//Uz参考相定义
		m_nK0CalMode = 1;			//零序补偿系数计算方式 1  S1=|K0|,,Phi(K0),S2=RERL,,XEXL,S3=|Z0/Z1|,,Phi(Z0/Z1)
		m_fK0Amp = 0.670f;				//|Ko|或Re(Ko) m_fRMRL
		m_fK0Angle = 0.670f;			//Phi(Ko)或Im(Ko) m_fXMXL
		//其他参数
		m_fIfh = 0;				//不知道什么电流，永远为0
		m_fPowerAngle = 20;		//不知道什么电流的相位，永远为20
		m_fZs = 1.0;				//系统阻抗，永远为1.0 系统阻抗不变时有效
		m_fPhis = 90.0f;				//系统阻抗角，永远为90  系统阻抗不变时有效
		m_fK0s = 0;				//不知道什么系数，永远为0
		m_fK0sPh = 0;				//不知道什么系数，永远为0
		m_nRXSelect = 0;
		m_tGps.init();
		m_bIPlusDC = 0;
//		m_fTao = 0.1f;
		m_nBinSelect = 0;

		m_fRecloseTime = 0.7f;
		m_fAfterAcceTime = 0.5f;

		m_nVzPhDefine = 0;
		m_fUxInput_Mag = 0.0f;
		m_fUxInput_Ang = 0.0f;
		m_fUxHigh = 40.0f;
		m_fUxLow = 0.0f;
		m_fUxInput_Ang = 0.0f;
		m_fBoutTimeTrig = 0.0f;
		m_fBoutHoldTime = 0.0f;
		m_nOutputSwitchMode = 0;

		for (int nIndex = 0;  nIndex  <  MAX_BINARYIN_COUNT;  nIndex++)
		{
			m_nDInputState[nIndex] = STT_IMPEDANCE_BIN_STATE_SINGLE;
			m_nStateBOut[nIndex] = 0;
		}
	}

	void CopyOwn(tmt_impedance_paras* pDest)
	{
		for (int nIndex = 0;nIndex<2;nIndex++)
		{
			pDest->m_fSetting[nIndex] = m_fSetting[nIndex];
			pDest->m_fRate[nIndex] = m_fRate[nIndex];
			pDest->m_fImpedance[nIndex] = m_fImpedance[nIndex];
			pDest->m_fImpAngle[nIndex] = m_fImpAngle[nIndex];
			pDest->m_fSCCurrent[nIndex] = m_fSCCurrent[nIndex];
			pDest->m_fSCVoltage[nIndex] = m_fSCVoltage[nIndex];
			pDest->m_nFaultType[nIndex] = m_nFaultType[nIndex];
			pDest->m_nFaultDir[nIndex] = m_nFaultDir[nIndex];
		}

		pDest->m_nCTPoint = m_nCTPoint;
		pDest->m_nPTPoint = m_nPTPoint;
		pDest->m_nCalMode = m_nCalMode;
		pDest->m_fPrepareTime = m_fPrepareTime;
		pDest->m_fPreFaultTime = m_fPreFaultTime;
		pDest->m_fMaxFaultTime = m_fMaxFaultTime;
		pDest->m_fMarginTime = m_fMarginTime;
		pDest->m_bImitatePT = m_bImitatePT;
		pDest->m_nImitPTPhase = m_nImitPTPhase;

		pDest->m_bCBSimulation = m_bCBSimulation;
		pDest->m_fCBTripTime = m_fCBTripTime;
		pDest->m_fCBCloseTime = m_fCBCloseTime;
		pDest->m_nFaultIncMode = m_nFaultIncMode;
		pDest->m_fFaultAngle = m_fFaultAngle;
		pDest->m_fFaultAng_0 = m_fFaultAng_0;
		pDest->m_nFaultTrigMode = m_nFaultTrigMode;
		pDest->m_nFaultProperty = m_nFaultProperty;
		pDest->m_bTransFault = m_bTransFault;
		pDest->m_fTransTime = m_fTransTime;
		pDest->m_fPostFaultTime = m_fPostFaultTime;
		pDest->m_nVzDefine = m_nVzDefine;
		pDest->m_nVzPhDefine = m_nVzPhDefine;
		pDest->m_nK0CalMode = m_nK0CalMode;
		pDest->m_fK0Amp = m_fK0Amp;
		pDest->m_fK0Angle = m_fK0Angle;

		pDest->m_fIfh = m_fIfh;
		pDest->m_fPowerAngle = m_fPowerAngle;
		pDest->m_fZs = m_fZs;
		pDest->m_fPhis = m_fPhis;
		pDest->m_fK0s = m_fK0s;
		pDest->m_fK0sPh = m_fK0sPh;
		pDest->m_nRXSelect = m_nRXSelect;
		pDest->m_fUxInput_Mag = m_fUxInput_Mag;
		pDest->m_fUxInput_Ang = m_fUxInput_Ang;
		pDest->m_fUxHigh = m_fUxHigh;
		pDest->m_fUxLow = m_fUxLow;
		pDest->m_nOutputSwitchMode = m_nOutputSwitchMode;
		pDest->m_fBoutTimeTrig = m_fBoutTimeTrig;

		pDest->m_fBoutHoldTime = m_fBoutHoldTime;
		pDest->m_fRecloseTime = m_fRecloseTime;
		pDest->m_fAfterAcceTime = m_fAfterAcceTime;
		pDest->m_tGps = m_tGps;
		pDest->m_bIPlusDC = m_bIPlusDC;
		pDest->m_nBinSelect = m_nBinSelect;
		pDest->m_nOutputSwitchMode = m_nOutputSwitchMode;

		for (int nIndex = 0;nIndex<MAX_BINARYIN_COUNT;nIndex++)
		{
			pDest->m_nDInputState[nIndex] = m_nDInputState[nIndex];
			pDest->m_nStateBOut[nIndex] = m_nStateBOut[nIndex];
		}
	}

	int GetSttTrigMode()
	{
		int nSttTrigMode = TMT_MDSTATE_TIMETRIGGER;

		switch (m_nFaultTrigMode)
		{
		case 0:		// 时间
			nSttTrigMode = TMT_MDSTATE_TIMETRIGGER; 
			break;
		case 1:		// 按键
			nSttTrigMode = TMT_MDSTATE_MEARSURETRIGGER; 
			break;
		case 2:		// 开入接点
			nSttTrigMode = TMT_MDSTATE_BINTRIGGER; 
			break;
		case 3:		// GPS
			nSttTrigMode = TMT_MDSTATE_GPSBTRIGGER; 
			break;
		default:
			break;
		}

		return nSttTrigMode;
	}

	tmt_impedance_paras()	{	}
	virtual ~tmt_impedance_paras(){}

public:
	float m_fSetting[2];//阻抗定值//过流定值
	float m_fRate[2];// 阻抗系数/过流系数【通过阻抗定值及系数计算阻抗值】
	float m_fImpedance[2];		//短路阻抗幅值(第一次故障阻抗、第二次故障阻抗)	m_fZ m_fZdev
	float m_fImpAngle[2];		//阻抗角(第一次故障阻抗、第二次故障阻抗) m_fPhi

	double m_fSCCurrent[2];		//短路电流 原m_fItest  m_fItestdev
	double m_fSCVoltage[2];		//短路电压 原m_fVtest  m_fVtestdev
	int	  m_nFaultType[2];		//故障类型(0:A相接地;1:B相接地;2:C相接地;3:AB短路;4:BC短路;5:CA短路;6:AB接地短路;7:BC接地短路;8:CA接地短路;9:三相短路;10:单相阻抗) 
	int   m_nFaultDir[2];		//故障方向 原m_bFaultDirFirst m_bFaultDirSecond(0:反方向;1:正方向;)
	int   m_nCTPoint;			//TA正极性  S1=指向母线,S2=指向线路  m_bCTPoint(0:指向母线;1:指向线路;)
	int   m_nPTPoint;			//TV安装位置  S1=母线侧,S2=线路侧  m_bPTPoint(0:母线侧;1:线路侧;)
	int   m_nCalMode;			//计算方式，原Dis=0 Overcurrent=3 Search可选(????该参数有点疑问,阻抗类该值为0,过流类该值为3)(Add计算模型：0-电流不变 1-电压不变 2-系统阻抗不变)
	//工频变化量距离根据故障方向而不同，为4（正方向）或5（反方向）
	float m_fPrepareTime;		//常态时间(该参数为试验前复归时间,也称作变化前时间,即递变类发生递变前的复归时间,用于搜索阻抗边界,搜索角度等,一般重合闸后加速、距离不用该参数)
	float m_fPreFaultTime;		//故障前时间(故障前复归时间,每次故障前的故障复归时间)
	float m_fMaxFaultTime;			//故障时间
	float m_fMarginTime;//故障时间裕度
	BOOL	m_bImitatePT;		//是否模拟PT断线
	int		m_nImitPTPhase;		//PT断线模拟相  A B C AB BC CA ABC
	BOOL  m_bCBSimulation;		//断路器模拟  S1=不模拟,S2=模拟 0(0:不模拟,1:模拟)
	float m_fCBTripTime;		//分闸时间	200ms（模拟断路器时的分闸时间）
	float m_fCBCloseTime;		//合闸时间	100ms（模拟断路器时的合闸时间）
	int   m_nFaultIncMode;		//合闸角选择 0-随机 1-定值
	float m_fFaultAngle;		//合闸角 永远为0
	float m_fFaultAng_0;		//合闸角的起始值(根据第1次故障的故障类型计算)
	int   m_nFaultTrigMode;		//故障触发方式 S1=时间,S2=按键,S3=开入量“H”触发,S4=GPS 0(0:时间触发,1:按键触发,2:开入接点翻转触发,3:GPS触发)
	BOOL  m_nFaultProperty;		//故障性质，0-瞬时 1-永久 m_bLastFault
	BOOL  m_bTransFault;		//是否转换性故障 (0:不是转换性故障,1:是转换性故障)
//	int   m_nTransMode;			//故障转换模式。1代表开入量启动故障转换；2代表重合启动转换
	float m_fTransTime;			//故障转换时间  0.1
	float m_fPostFaultTime;		//保护动作后持续时间  2.000f
	//通用参数
	int   m_nVzDefine;			//Uz输出定义 S1=0,S2=√3×3Vo,S3=-√3×3Vo,S4=3Vo,S5=-3Vo,S6=抽取电压
	//0:+3U0,1:-3U0,2:+√3×3Vo,3:-√3×3Vo,4:检同期A,5:检同期B,6:检同期C,7:检同期AB,8:检同期BC,9:检同期CA,10:检线无压母有压,11:检线有压母无压,12:检线无压母无压,13:检线有压母有压,14:无输出
	int	  m_nVzPhDefine;		//Uz参考相定义  S1=Va相位,S2=Vb相位,S3=Vc相位,S4=Vab相位,S5=Vbc相位,S6=Vca相位
	int   m_nK0CalMode;			//零序补偿系数计算方式 3  S1=|K0|,,Phi(K0),S2=RERL,,XEXL,S3=|Z0/Z1|,,Phi(Z0/Z1)
	float m_fK0Amp;				//|Ko|或Re(Ko) m_fRMRL
	float m_fK0Angle;			//Phi(Ko)或Im(Ko) m_fXMXL
	//其他参数
	float m_fIfh;				//负荷电流，除Search外为0
	float m_fPowerAngle;		//负荷功角，除Search外为20
	float m_fZs;				//不知道什么阻抗，永远为1.0(系统阻抗幅值)
	float m_fPhis;				//不知道什么阻抗的相位，永远为90（系统阻抗相位）
	float m_fK0s;				//不知道什么系数，永远为0
	float m_fK0sPh;				//不知道什么系数，永远为0
	int	  m_nRXSelect;			//阻抗表示方式 0-Z-Phi 1-RX  模板中没有，恒为0(阻抗表达方式) zhouhj说 底层用不到这个变量，恒为0；mym 2021-8-5

/////////////////////////////////////////后续提取增加///////////////////////////////////////////////////////////////////////////////
	float m_fUxInput_Mag;	//同期电压(检同期方式有效)
	float m_fUxInput_Ang;
	float	m_fUxHigh;			//有压测试值
	float	m_fUxLow;			//无压测试值
	long m_nOutputSwitchMode;//翻转触发方式 0-时间触发 1-开入量触发
	float	m_fBoutTimeTrig;	//反转时间，0为不翻转
	float	m_fBoutHoldTime;	//翻转保持时间

	float  m_fRecloseTime;    //重合闸时间
	float  m_fAfterAcceTime;    //后加速时间
	tmt_time	    m_tGps;
	long m_bIPlusDC;//是否叠加非周期分量
//	float m_fTao;//衰减时间常数

	long m_nDInputState[MAX_BINARYIN_COUNT];//开入量状态  0:单跳;1：三跳;2：重合
	long m_nStateBOut[MAX_BINARYIN_COUNT];//用二进制标识各个开出状态
	long m_nBinSelect;//开入量选择第几组   0-ABCD 1-EFGH 0

	//2021-9-7  lijunqing
	double m_fR, m_fX;  //阻抗平面的阻抗值，用于绘图

	void CalRX()
	{
		float fAngle = m_fImpAngle[0] * pi / 180;
		m_fR = m_fSetting[0] * cos(fAngle);
		m_fX = m_fSetting[0] * sin(fAngle);
	}
}tmt_ImpedanceParas;

typedef struct tmt_impedance_results
{
public:
	virtual void init()
	{
		m_fRealTestTime=0.0f;		//实际试验时间
		m_nTripNumbers=0;			//跳闸(重合)总次数, 最多允许记录跳闸 4 次
		m_fImp = m_fImpAngle = 0;
		m_fOverCurrent = m_fFaultVol = m_fFaultCurrent = 0;
		m_fRecloseTime = m_fSecondTripTime = m_fTripTime = 0;

		for (int nIndex = 0;nIndex<MAX_BINARYIN_COUNT;nIndex++)
		{
			m_nActID[nIndex] = 0;
		}

		for(int i=0;i<2;i++)
		{
			for(int j=0;j<MAX_BINARYIN_COUNT;j++)
				m_fBinTripTime[j][i] = -1000.0f;
		}

		for(int i=0;i<4;i++)
		{
			m_fFirstTripTime[i] = m_fFirstTripTime[i+4] = 0;
			m_fRecordTime[i] = 0;
			m_fReturnTime[i] = m_fReturnTime[i+4] = 0;
		}

		m_nActA = m_nActB = m_nActC = 0;
		m_nActAcc = 0;
	}

	tmt_impedance_results()	
	{
//		init();
	}

	virtual ~tmt_impedance_results(){}

	void SetRecloseTime(float fValue)
	{
		if (fValue<=0)
		{
			return;
		}

		m_fRecloseTime = fValue;
	}

	void SetFault1TripTime(long nTripIndex,long nInputMapState,float fValue,bool bHasMapReclose)
	{
		if (fValue<=0)
		{
			return;
		}

		if (nInputMapState == STT_IMPEDANCE_BIN_STATE_THREE)
		{
			m_fFirstTripTime[0] = fValue;
			m_fFirstTripTime[1] = fValue;
			m_fFirstTripTime[2] = fValue;
		}
		else if (nInputMapState == STT_IMPEDANCE_BIN_STATE_SINGLE)
		{
			m_fFirstTripTime[nTripIndex-bHasMapReclose] = fValue;
		}
	}

	void SetFaultTripTime(float *pfTripTime, long nTripIndex,long nInputMapState,float fValue,bool bHasMapReclose)
	{
		if (fValue<=0)
		{
			return;
		}

		if (nInputMapState == STT_IMPEDANCE_BIN_STATE_THREE)
		{
			pfTripTime[0] = fValue;
			pfTripTime[1] = fValue;
			pfTripTime[2] = fValue;
		}
		else if (nInputMapState == STT_IMPEDANCE_BIN_STATE_SINGLE)
		{
			pfTripTime[nTripIndex-bHasMapReclose] = fValue;
		}
	}

	void SetFault2TripTime(long nTripIndex,long nInputMapState,float fValue)
	{
		if (nInputMapState == STT_IMPEDANCE_BIN_STATE_RECLOCE)
			return;

		if (fValue>=m_fSecondTripTime)
		{
			m_fSecondTripTime = fValue;
		}
	}

	float GetFirstTripTime()
	{
		float fValue = 0.0f;

		for (int nIndex = 0;nIndex<3;nIndex++)
		{
			if (fValue<m_fFirstTripTime[nIndex])
			{
				fValue = m_fFirstTripTime[nIndex];
			}
		}

		return fValue;
	}

	void CopyOwn(tmt_impedance_results* pDest)
	{
		pDest->m_fRealTestTime = m_fRealTestTime;
		pDest->m_nTripNumbers = m_nTripNumbers;
		pDest->m_fImp = m_fImp;
		pDest->m_fImpAngle = m_fImpAngle;
		pDest->m_fOverCurrent = m_fOverCurrent;
		pDest->m_fFaultCurrent = m_fFaultCurrent;
		pDest->m_fFaultVol = m_fFaultVol;
		pDest->m_fRecloseTime = m_fRecloseTime;
		pDest->m_fSecondTripTime = m_fSecondTripTime;
		pDest->m_fTripTime = m_fTripTime;

		pDest->m_nActA = m_nActA;
		pDest->m_nActB = m_nActB;
		pDest->m_nActC = m_nActC;
		pDest->m_nActD = m_nActD;
		pDest->m_nActAcc = m_nActAcc;

		for (int nIndex = 0;nIndex<MAX_BINARYIN_COUNT;nIndex++)
		{
			pDest->m_fBinTripTime[nIndex][0] = m_fBinTripTime[nIndex][0];
			pDest->m_fBinTripTime[nIndex][1] = m_fBinTripTime[nIndex][1];
			pDest->m_nActID[nIndex] = m_nActID[nIndex];
		}

		pDest->m_fTripTime = m_fTripTime;
	}

public:
	float m_fRealTestTime;			//实际试验时间
	int   m_nTripNumbers;			//跳闸(重合)总次数, 最多允许记录跳闸 4 次
	float m_fImp,m_fImpAngle;
	float m_fOverCurrent;
	float m_fFaultCurrent,m_fFaultVol;	//故障电流、电压
	float	m_fBinTripTime[MAX_BINARYIN_COUNT][2];//开入接点每次动作(跳闸,重合)时间
	float		m_fFirstTripTime[8];
	float		m_fRecloseTime;
	float		m_fSecondTripTime;
	float		m_fRecordTime[4];
	float		m_fReturnTime[8];
	float		m_fTripTime;
	int		m_nActID[MAX_BINARYIN_COUNT];//将原来m_nActA、B、C等统一为数组

	long m_nActA,m_nActB,m_nActC,m_nActD;
	long m_nActAcc;

}tmt_ImpedanceResults;

//参数2代表是否使用ImpBase作为基类,只有重合闸后加速不是采用ImpBase作为基类,重合闸后加速使用状态序列作为基类
void stt_xml_serialize_impedance_paras(tmt_ImpedanceParas *pParas, CSttXmlSerializeBase *pXmlSierialize,BOOL bImpBase);
void stt_xml_serialize_impedance_results(tmt_ImpedanceResults *pResults, CSttXmlSerializeBase *pXmlSierialize);