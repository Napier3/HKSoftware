#pragma once

#include "tmt_impedance_test.h"
#include "../tmt_common_def.h"

#define STT_CB_OPERATE_PROC_CTRL_TRIP              0
#define STT_CB_OPERATE_PROC_CTRL_TIME              1
// #define MAX_NAME_LEN  32

typedef struct tmt_cb_operate_paras :public tmt_ImpedanceParas
{
	float	m_fTAfterAccTrig;	//故障后延时
	int		m_nTestProcCtrlMode;	// 试验过程控制方式 0-跳合控制 1-时间控制
	int   m_nRecloseMode;// 重合方式：0-综重（单重+三重） 1-三重 2-不重合
	float   m_fUnom;//额定电压(为兼容老版接口程序增加)
	

	long    m_nTtripCheck;     //动作时间误差判断
	long    m_nTtripDCheck;    //重合闸动作时间误差判断
	long    m_nTtripAccCheck;  //后加速动作时间误差判断

	float   m_fTtripAbsErr;    //动作时间绝对误差
	float   m_fTtripRelErr;    //动作时间相对误差
	float   m_fTSetting;       //动作时间整定值

	float   m_fTtripDAbsErr;     //重合闸动作时间绝对误差
	float   m_fTtripDRelErr;     //重合闸动作时间相对误差
	float   m_fDTSetting;        //重合闸动作时间整定值

	float   m_fTtripAccAbsErr;   //后加速绝对误差
	float   m_fTtripAccRelErr;   //后加速相对误差
	float   m_fAccTSetting;      //后加速整定值

	long   m_nTtripErrorLogic;     //动作时间误差逻辑判断
	long   m_nTtripDErrorLogic;   //重合闸动作时间误差逻辑判断
	long   m_nTtripAccErrorLogic; //后加速动作时间误差逻辑判断

	void CalRX_CB_Angle()//整组
	{
		float fAngle = m_fImpAngle[0] * pi / 180;
		m_fR = m_fImpedance[0] * cos(fAngle);
		m_fX = m_fImpedance[0] * sin(fAngle);
	}


public:
	virtual void init()
	{
		tmt_ImpedanceParas::init();
		m_fUnom = 57.74f;
		m_fTAfterAccTrig = 0.0f;
		m_nTestProcCtrlMode = STT_CB_OPERATE_PROC_CTRL_TRIP;
		m_nRecloseMode = 0;

		m_fTtripAbsErr = 0.04f;    //动作时间绝对误差
		m_fTtripRelErr = 0.04f;    //动作时间相对误差
		m_fTSetting = 0.1f;       //动作时间整定值

		m_fTtripDAbsErr = 0.04f;     //重合闸动作时间绝对误差
		m_fTtripDRelErr = 0.04f;     //重合闸动作时间相对误差
		m_fDTSetting = 1.0f;        //重合闸动作时间整定值

		m_fTtripAccAbsErr = 0.04f;   //后加速绝对误差
	    m_fTtripAccRelErr = 0.04f;   //后加速相对误差
		m_fAccTSetting = 0.04f;      //后加速整定值

		m_nTtripCheck = 1;     //动作时间误差判断
		m_nTtripDCheck = 0;    //重合闸动作时间误差判断
		m_nTtripAccCheck = 0;  //后加速动作时间误差判断

		m_nTtripErrorLogic = 0;     //动作时间误差逻辑判断
		m_nTtripDErrorLogic = 0;   //重合闸动作时间误差逻辑判断
		m_nTtripAccErrorLogic = 0; //后加速动作时间误差逻辑判断
	} 


	tmt_cb_operate_paras &operator = (const tmt_cb_operate_paras &paras)
	{
		m_fSetting[0]   = paras.m_fSetting[0] ;
		m_fSetting[1]  = paras.m_fSetting[1] ;
		m_fRate[0] = paras.m_fRate[0] ;
		m_fRate[1] = paras.m_fRate[1] ;
		m_fImpedance[0] = paras.m_fImpedance[0] ;		//短路阻抗
		m_fImpedance[1] = paras.m_fImpedance[1] ;	
		m_fImpAngle[0] = paras.m_fImpAngle[0] ;			//阻抗角 m_fPhi
		m_fImpAngle[1] = paras.m_fImpAngle[1] ;
		m_fSCCurrent[0]  = paras.m_fSCCurrent[0] ;		//短路电流 原m_fItest  m_fItestdev
		m_fSCCurrent[1] = paras.m_fSCCurrent[1] ;
		m_fSCVoltage[0]  = paras.m_fSCVoltage[0] ;		//短路电压 原m_fVtest  m_fVtestdev
		m_fSCVoltage[1]  = paras.m_fSCVoltage[1] ;
		m_nFaultDir[0] = paras.m_nFaultDir[0] ;				//故障方向 原m_bFaultDirFirst m_bFaultDirSecond
		m_nFaultDir[1] = paras.m_nFaultDir[1] ;
		m_nCTPoint = paras.m_nCTPoint ;			//TA正极性  S1=指向母线,S2=指向线路  m_bCTPoint
		m_nPTPoint  = paras.m_nPTPoint ;			//TV安装位置  S1=母线侧,S2=线路侧  m_bPTPoint
		m_nFaultType[0] = paras.m_nFaultType[0] ;			//故障类型 
		m_nFaultType[1] = paras.m_nFaultType[1] ;
		m_nCalMode = paras.m_nCalMode ;			//计算方式，原m_nTestMode 永远为0
//		m_fPrepareTime = paras.m_fPrepareTime ;		//常态时间
		m_fPreFaultTime = paras.m_fPreFaultTime ;		//故障前时间
		m_fMaxFaultTime = paras.m_fMaxFaultTime;
		m_fMarginTime = paras.m_fMarginTime ;			//故障时间裕度
		m_bImitatePT  = paras.m_bImitatePT ;		//是否模拟PT断线
		m_nImitPTPhase = paras.m_nImitPTPhase ;			//模拟A相
		m_bCBSimulation = paras.m_bCBSimulation ;		//断路器模拟  S1=不模拟,S2=模拟 0
		m_fCBTripTime  = paras.m_fCBTripTime ;		//分闸时间	200ms
		m_fCBCloseTime  = paras.m_fCBCloseTime ;		//合闸时间	100ms
		m_fFaultAngle = paras.m_fFaultAngle ;		//故障角 永远为0
		m_fFaultAng_0 = paras.m_fFaultAng_0 ;
		m_nFaultIncMode = paras.m_nFaultIncMode ;		//故障开始方式 永远为0
		m_nFaultTrigMode = paras.m_nFaultTrigMode ;					//故障触发方式 S1=时间,S2=按键,S3=开入量“H”触发,S4=GPS 0
		m_nFaultProperty = paras.m_nFaultProperty ;		//故障性质，0-瞬时 1-永久 m_bLastFault
		m_bTransFault = paras.m_bTransFault ;		//是否转换性故障 0
		// m_nTransMode = 0;
		m_fTransTime = paras.m_fTransTime ;		//故障转换时间  0.1
		m_fPostFaultTime = paras.m_fPostFaultTime ;		//保护动作后持续时间  2.000f
		//通用参数
		m_nVzDefine = paras.m_nVzDefine ;			//Uz输出定义 S1=0,S2=√3×3Vo,S3=-√3×3Vo,S4=3Vo,S5=-3Vo,S6=抽取电压
		//m_nVzPhDefine = 0;		//Uz参考相定义
		m_nK0CalMode = paras.m_nK0CalMode ;			//零序补偿系数计算方式 1  S1=|K0|,,Phi(K0),S2=RERL,,XEXL,S3=|Z0/Z1|,,Phi(Z0/Z1)
		m_fK0Amp = paras.m_fK0Amp ;				//|Ko|或Re(Ko) m_fRMRL
		m_fK0Angle = paras.m_fK0Angle ;			//Phi(Ko)或Im(Ko) m_fXMXL
		//其他参数
		m_fIfh = paras.m_fIfh ;				//不知道什么电流，永远为0
		m_fPowerAngle = paras.m_fPowerAngle ;		//不知道什么电流的相位，永远为20
		m_fZs = paras.m_fZs ;				//系统阻抗，永远为1.0 系统阻抗不变时有效
		m_fPhis = paras.m_fPhis ;				//系统阻抗角，永远为90  系统阻抗不变时有效
		m_fK0s = paras.m_fK0s ;				//不知道什么系数，永远为0
		m_fK0sPh = paras.m_fK0sPh  ;				//不知道什么系数，永远为0
		m_nRXSelect = paras.m_nRXSelect ;
		m_tGps  = paras.m_tGps;//paras.m_tGps.init();
		m_bIPlusDC  = paras.m_bIPlusDC;
		//m_fTao = 0.1f;
		m_nBinSelect  = paras.m_nBinSelect;

		m_fRecloseTime  = paras.m_fRecloseTime ;
		m_fAfterAcceTime  = paras.m_fAfterAcceTime ;

		m_fUxInput_Mag = paras.m_fUxInput_Mag ;
		m_fUxInput_Ang  = paras.m_fUxInput_Ang ;
		m_fUxHigh  = paras.m_fUxHigh ;
		m_fUxLow  = paras.m_fUxLow ;
		m_fUxInput_Ang  = paras.m_fUxInput_Ang ;
		m_fBoutTimeTrig  = paras.m_fBoutTimeTrig ;
		m_fBoutHoldTime  = paras.m_fBoutHoldTime ;
        /////////////////////////////////////////////////////////////////////////////////
        m_fTAfterAccTrig  = paras.m_fTAfterAccTrig;
        m_nTestProcCtrlMode = paras.m_nTestProcCtrlMode;
		m_nRecloseMode = paras.m_nRecloseMode;
		m_fUnom = paras.m_fUnom;

		m_fTtripAbsErr = paras.m_fTtripAbsErr;    //动作时间绝对误差
		m_fTtripRelErr = paras.m_fTtripRelErr;    //动作时间相对误差
		m_fTSetting = paras.m_fTSetting;       //动作时间整定值

		m_fTtripDAbsErr = paras.m_fTtripDAbsErr;     //重合闸动作时间绝对误差
		m_fTtripDRelErr = paras.m_fTtripDRelErr;     //重合闸动作时间相对误差
		m_fDTSetting = paras.m_fDTSetting;       //重合闸动作时间整定值

		m_fTtripAccAbsErr = paras.m_fTtripAccAbsErr;   //后加速绝对误差
		m_fTtripAccRelErr = paras.m_fTtripAccRelErr;   //后加速相对误差
		m_fAccTSetting = paras.m_fAccTSetting;      //后加速整定值

		m_nTtripCheck = paras.m_nTtripCheck;     //动作时间误差判断
		m_nTtripDCheck = paras.m_nTtripDCheck;     //重合闸动作时间误差判断
		m_nTtripAccCheck = paras.m_nTtripAccCheck;  //后加速动作时间误差判断
 

		m_nTtripErrorLogic = paras.m_nTtripErrorLogic;     //动作时间误差逻辑判断
		m_nTtripDErrorLogic = paras.m_nTtripDErrorLogic;  //重合闸动作时间误差逻辑判断
		m_nTtripAccErrorLogic = paras.m_nTtripAccErrorLogic; //后加速动作时间误差逻辑判断
 		return *this;
 	}

}tmt_CBOperateParas;

typedef struct tmt_cb_operate_results :public tmt_ImpedanceResults
{
public:
	long m_nActAcc;
public:
	virtual void init()
	{
		tmt_ImpedanceResults::init();
		m_nActAcc = 0;
		
	} 

	tmt_cb_operate_results &operator = (const tmt_cb_operate_results &paras)
	{
		m_fRealTestTime =  paras.m_fRealTestTime;			//实际试验时间
		m_nTripNumbers =  paras.m_nTripNumbers;			//跳闸(重合)总次数, 最多允许记录跳闸 4 次
		m_fImp = paras.m_fImp;
		m_fImpAngle = paras.m_fImpAngle;
		m_fOverCurrent = paras.m_fOverCurrent;
		m_fFaultCurrent =  paras.m_fFaultCurrent;
		m_fFaultVol =	paras.m_fFaultVol;

		for (int i = 0; i < MAX_BINARYIN_COUNT; i++)
		{
			for (int j = 0; j < 2;j++)
			{
				m_fBinTripTime[i][j] = paras.m_fBinTripTime[i][j];
			}
		}
		
		for (int i = 0; i < 8; i++)
		{
			m_fFirstTripTime[i] = paras.m_fFirstTripTime[i];//float	m_fBinTripTime[MAX_BINARYIN_COUNT][2];//开入接点每次动作(跳闸,重合)时间
		}

		m_fRecloseTime = paras.m_fRecloseTime;
		m_fSecondTripTime = paras.m_fSecondTripTime;

		for (int i = 0; i < 4; i++)
		{
			m_fRecordTime[i] = paras.m_fRecordTime[i];
		}

		for (int i = 0; i < 8; i++)
		{
			m_fReturnTime[i] = paras.m_fReturnTime[i];
		}
		m_fTripTime = paras.m_fTripTime;

		for (int i = 0; i < MAX_BINARYIN_COUNT; i++)
		{
			m_nActID[i] = paras.m_nActID[i];//将原来m_nActA、B、C等统一为数组
		}

		m_nActA =  paras.m_nActA;
		m_nActB = paras.m_nActB;
		m_nActC = paras.m_nActC;
		m_nActD = paras.m_nActD;
		m_nActAcc = paras.m_nActAcc;

		return *this;
	}


}tmt_CBOperateResults;

#define ITEM_CNT  5



typedef struct tmt_cb_operate_test  : public TMT_PARAS_HEAD
{
public:
	tmt_CBOperateParas       m_oCBOperateParas;
	tmt_CBOperateResults   m_oCBOperateResults;
	char m_szName[MAX_NAME_LEN];
	
	float m_fR;
	float m_fX;

	void init()
	{
		init_head(); //2021-9-13  lijunqing
		strcpy(m_pszMacroID, STT_MACRO_ID_PsuCBOperate);
		strcpy(m_szName, "Z = 1.900Ω, A-E, 瞬时");
		m_nVersion = 0x00010001;
		m_nTestState = 0;
		m_nSelected = 1;
		m_fR = 0.0f;
		m_fX = 0.0f;

		m_oCBOperateParas.init();
		m_oCBOperateResults.init();
		
	}


	tmt_cb_operate_test &operator = (const tmt_cb_operate_test &paras)
	{
		m_oCBOperateParas = paras.m_oCBOperateParas ;
		m_oCBOperateResults = paras.m_oCBOperateResults ;
		m_fR = paras.m_fR;
		m_fX = paras.m_fX;
		m_nSelected = paras.m_nSelected;

		for (int i = 0; i < MAX_NAME_LEN;i++)
			m_szName[i] = paras.m_szName[i];

		return *this;
	}

	tmt_cb_operate_test()	{init();}
	virtual void clear_result(){	m_oCBOperateResults.init();	}
	virtual ~tmt_cb_operate_test(){}

}tmt_CBOperateTest;

void stt_init_paras(tmt_CBOperateParas *pParas);
void stt_init_results(tmt_CBOperateResults *pResults);

void stt_xml_serialize(tmt_CBOperateParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_CBOperateResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_CBOperateTest *pTests, CSttXmlSerializeBase *pXmlSerialize, long nVolRsNum, long nCurRsNum);


