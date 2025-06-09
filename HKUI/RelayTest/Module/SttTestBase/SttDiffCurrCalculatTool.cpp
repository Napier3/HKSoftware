//#include "StdAfx.h"
#include "../../../Module/OSInterface/QT/stdafx.h"
#include "SttDiffCurrCalculatTool.h"
#include "../../../Module/API/MathApi.h"

#define qSqrt sqrt
#define SQRT_3 SQRT3



//Title:比率差动测试逻辑
//Date:5/8/2017
//Ver:1.0
//X.Q.
/*******************Global Varibles*******************************/
/**********************************************************************/
//   以下变量为全局变量
/**********************************************************************/
//m_bStart:测试开始标志
//m_bResultJudge：判据
//m_fTtrip：保护动作时间
//m_bJudge1: 动作判据1
//m_bJudge2：动作判据2
//m_nRunSer：测试序号,初值=1；
//m_nCurrentSerial：测试项目列表序号。从0开始。
//m_fIdiff1：差动值1
//m_fIdiff2：差动值2
//m_fIdiff：差动电流
//m_fKjxh:高压侧接线系数
//m_fKjxl:低压侧接线系数
//m_fKph,m_fKpl分别为高压侧和低压侧平衡系数
//Complex Ia,Ib,Ic,Ia',Ib',Ic'   计算得到的高压侧和低压侧三相电流

/**********************************************************************/
//   以下变量需要从试验参数中获取
/**********************************************************************/

//m_fIdiffStart：差动电流变化始值。大于整定曲线值的1.2倍
//m_bItemSel：测试项目列表选项标记。TRUE：选择，FALSE:非选择
//m_fPrec:精度误差(绝对值)
//m_fIbias:制动电流
//m_nAngleMode:校正方式。0,1,2=无校正,△侧校正,Y侧校正;
//m_nIbiasCal:制动方程。0,1,2,3,4,5=(|I1-I2|)/K1或Ir=(|I1+I2|)/K1,(|I1|+|I2|*K2)/K1,max(|I1|,|I2|),(|Id-|I1|-|I2||)/K1,|I2|,√(K1*I1*I2*Cos(δ))
//m_nWindH:高压侧绕组接线型式,0,1="Y","△"
//m_nWindM:中压侧绕组接线型式,0,1="Y","△"
//m_nWindL:低压侧绕组接线型式,0,1="Y","△"
//m_nWindSide:测试绕组，0,1,2=高低，高中，中低
//m_fFactor1:对应制动方程中的K1
//m_fFactor2:对应制动方程中的K2
//标幺制时,m_fIet1=额定电流;实名制时m_fIet1=1;
//标幺制时,m_fIet2=额定电流;实名制时m_fIet2=1;
//m_nConnectMode:测试绕组之间角差（钟点数）=0-12,"12点","1点","2点","3点","4点","5点","6点","7点","8点","9点","10点","11点"
//m_bConnectFactor,FALSE,TRUE=不考虑绕组接线型式,考虑绕组接线型式;
//m_nPhase:相别,0,1,2分别表示为A,B,C三相
//m_bCTStarPoint,CT极性，FALSE,TRUE分别表示为正极性和负极性
//Sn:变压器额定容量
//Uh,Um,Ul:变压器高、中、低压侧额定电压
//高、中、低压侧CT变比，CTPh/CTSh,CTPm/CTSm,CTPl/CTSl,
//m_bMinAxis=FALSE,TRUE,分别表示：有名值，标幺值
//m_nJXFactor=0,1;分别是不考虑绕组接线型式和考虑绕组接线型式
//m_nKcal=0,1;分别表示平衡系数自动计算和手动设置,手动设置平衡系数时，高中低压侧平衡系数分别为:Kph,Kpm和Kpl;

int nSignMethod2[12]={1,1,-1,-1,1,-1,-1,-1,1,1,-1,1};
int nSignMethod1[12]={1,1,-1,1,1,-1,-1,-1,1,-1,-1,1};
int nMethod1[12]={0,3,1,4,2,5,0,3,1,4,2,5};
int nMethod2[12]={6,5,2,4,1,3,0,5,2,4,1,3};


CSttDiffCurrCalculatTool::CSttDiffCurrCalculatTool(void)
{
	m_fKph_ElecRailway = 1.0f;
}

CSttDiffCurrCalculatTool::~CSttDiffCurrCalculatTool(void)
{
}

void CSttDiffCurrCalculatTool::InitSysParas(float fIOutmax,float fFreq)
{
	m_fIOutmax = fIOutmax;
	m_fFreq = fFreq;
}

//不需要设置的参数,m_float fKjxh,float m_fKjxl,m_fKph,m_fKpm,m_fKpl,m_fIet,
void CSttDiffCurrCalculatTool::InitParas6I(int nInSel,float fIbase,int nSearchMode,bool bMinAxis,int nAngleMode,int nIbiasCal,int nWindH,int nWindM,int nWindL,int nWindSide,
										   float fFactor1,float fFactor2,int nConnectMode,int nPhase,bool bCTStarPoint,int nJXFactor)
{
	m_nInSel = nInSel;
	m_fIbase = fIbase;
	m_nSearchMode = nSearchMode;
	m_bMinAxis = bMinAxis;
	m_nAngleMode = nAngleMode;
	m_nIbiasCal = nIbiasCal;
	m_nWindH = nWindH;
	m_nWindM = nWindM;
	m_nWindL = nWindL;
	m_nWindSide = nWindSide;
	m_fFactor1 = fFactor1;
	m_fFactor2 = fFactor2;
	m_nConnectMode = nConnectMode;
	m_nPhase = nPhase;
	m_bCTStarPoint = bCTStarPoint;
	m_nJXFactor = nJXFactor;
}

//手动计算平衡系数并指定
void CSttDiffCurrCalculatTool::InitParas_SetBalanceFactors(float fKph_Set,float fKpm_Set,float fKpl_Set)
{
	m_nKcal = 1;
	m_fKph_Set = fKph_Set;
	m_fKpm_Set = fKpm_Set;
	m_fKpl_Set = fKpl_Set;
	CalKjx();
	CalKpx();
}

//通过变压器参数,自动计算平衡系数
void CSttDiffCurrCalculatTool::InitParas_AutoCalBalanceFactors(float fSn,float fUh,float fUm,float fUl,float fCTPh,float fCTSh,float fCTPm,float fCTSm,float fCTPl,float fCTSl)
{
	m_nKcal = 0;
	m_fSn= fSn;
	m_fUh= fUh;
	m_fUm = fUm;
	m_fUl= fUl;
	m_fCTPh= fCTPh;
	m_fCTSh = fCTSh;
	m_fCTPm = fCTPm;
	m_fCTSm = fCTSm;
	m_fCTPl= fCTPl;
	m_fCTSl = fCTSl;
	CalKjx();
	CalKpx();
}

void CSttDiffCurrCalculatTool::InitParas5I_ElecRailway(float fIbase,int nSearchMode,bool bMinAxis,int nIbiasCal,float fKpl,
										   int nPhase,bool bCTStarPoint,int nRWCTconnect,int nTranSort,int nKphMode)
{
	m_nInSel = 1;//基准电流选择设定值
	m_fIbase = fIbase;
	m_nSearchMode = nSearchMode;
	m_bMinAxis = bMinAxis;
	m_nAngleMode = 0;//校正方式。0=无校正
	m_nIbiasCal = 0;
	m_fFactor2 = 1;

	if (nIbiasCal == 1)
	{
		m_fFactor1 = 2;
	}
	else
	{
		m_fFactor1 = 1;
	}

	m_nWindH = 0;//绕组接线型式,0="Y"
//	m_nWindH = nRWCTconnect;
	m_nWindM = 0;//绕组接线型式,0="Y"
	m_nWindL = 0;//绕组接线型式,0="Y"
	m_nWindSide = 0;//测试绕组	0-高-低 
	
	m_nConnectMode = 0;//:测试绕组之间角差（钟点数）=0-"12点"
	m_nPhase = nPhase;
	m_bCTStarPoint = bCTStarPoint;
	m_nJXFactor = 0;//平衡系数计算方法	0-不考虑绕组接线型式

	m_nKcal = 1;
	m_fKph_Set =  1.0f;
	m_fKpm_Set = 1.0f;
	m_fKpl_Set = 1.0f;
	m_fKph_ElecRailway = fKpl;

	if ((nTranSort == ElecRailway_TransType_0_YV)||(nTranSort == ElecRailway_TransType_17_YD11_YT)
		||(nTranSort == ElecRailway_TransType_18_ThreeYV2_YT))//zhouhj 20211203 对于Y/V接线平衡变压器、Y/△-11接线 需要进行转角计算
	{
		m_nWindL = 1;//低压侧为△
		m_nAngleMode = 2;//Y侧校正
		m_nConnectMode = 11;//钟点数为11点

		if (nTranSort == ElecRailway_TransType_17_YD11_YT)
		{
			m_fKph_Set = 0.577f;//YD11点,在Y侧转角时,高压侧平衡系数除以根号3
//			m_fKpl_Set = fKpl;
			m_nAngleMode = 0;
			m_bCTStarPoint = (!bCTStarPoint);
		}
	}

	m_nRWCTconnect_ElecRailway = nRWCTconnect;
	m_nTranSort_ElecRailway = nTranSort;
	m_nKphMode_ElecRailway = nKphMode;
	CalKjx();
	CalKpx();
}

void CSttDiffCurrCalculatTool::InitParas3I_BP2()
{
	m_nInSel = 1;//基准电流选择设定值
	m_fIbase = 1.0f;//基准电流设定值
	m_nSearchMode = 0;//0二分法, 实际未用到此参数
	m_bMinAxis = 0;//有名值
	m_nAngleMode = 0;//校正方式。0=无校正
	m_nIbiasCal = 0;//制动方式选择(|I1|+|I2|*K2)/K1
	m_fFactor1 = 1;//对应制动方程中的K1
	m_fFactor2 = 1;//对应制动方程中的K2

	m_nWindH = 0;//绕组接线型式,0="Y"
	m_nWindM = 0;//绕组接线型式,0="Y"
	m_nWindL = 0;//绕组接线型式,0="Y"
	m_nWindSide = 0;//测试绕组	0-高-低 
	
	m_nConnectMode = 0;//:测试绕组之间角差（钟点数）=0-"12点"
	m_nPhase = 0;////:相别,0,1,2分别表示为A,B,C三相
	m_bCTStarPoint = 0;////,CT极性，FALSE,TRUE分别表示为正极性和负极性
	m_nJXFactor = 0;//平衡系数计算方法	0-不考虑绕组接线型式

	m_nKcal = 1;
	m_fKph_Set =  1.0f;
	m_fKpm_Set = 1.0f;
	m_fKpl_Set = 1.0f;

	CalKjx();
	CalKpx();
}

BOOL CSttDiffCurrCalculatTool::CurrentCal3I_BP2(float *fId,float fIr_Id)
{
	float fIr = *fId + fIr_Id;
	float fId_old = *fId;
	CurrentCal(fId,fIr);

	if (fabs(fId_old-*fId)<0.0001)//判断差动电流有没有被修改,如果被修改了,需要进行重新计算
	{
		return TRUE;
	}

	fIr = *fId + fIr_Id;
	fId_old = *fId;
	CurrentCal(fId,fIr);//暂时只做一次修正
	return FALSE;
}

void CSttDiffCurrCalculatTool::CurrentCal_ElecRailway(float *fId,float fIr,float &fIalpha,float &fIbeta)
{
	CurrentCal(fId,fIr);
	float fIfault = 0.0f,fReimbCurr_YD11 = 0.0f;//fReimbCurr_YD11为在Y侧转角补偿电流
	long nPhIndex = 3,nReimbIndex_YD11 = 5;//nReimbIndex_YD11为补偿电流相别

	if (m_nPhase == 0)
	{
		nPhIndex = 3;
		nReimbIndex_YD11 = 5;
	}
	else if (m_nPhase == 1)
	{
		nPhIndex = 4;
		nReimbIndex_YD11 = 3;
	}
	else if (m_nPhase == 2)
	{
		nPhIndex = 5;
		nReimbIndex_YD11 = 4;
	}
	else
	{
		fIalpha = 0;
		fIbeta = 0;
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("当前测试相别(%d)错误,只支持单相故障(A、B、C)"),m_nPhase);
		return;
	}

//	float fKph = m_fKpl_Set;//为后期预留
	
	fIfault = m_arryoCurrent[nPhIndex].famptitude;
	fReimbCurr_YD11 = m_arryoCurrent[nReimbIndex_YD11].famptitude;

	if ((fabs(m_arryoCurrent[nPhIndex].fphase-180)<0.001)||(fabs(m_arryoCurrent[nPhIndex].fphase+180)<0.001))
	{
		fIfault = -fIfault;
	}

	if ((fabs(m_arryoCurrent[nReimbIndex_YD11].fphase-180)<0.001)||(fabs(m_arryoCurrent[nReimbIndex_YD11].fphase+180)<0.001))
	{
		fReimbCurr_YD11 = -fReimbCurr_YD11;
	}

	if (m_nTranSort_ElecRailway == ElecRailway_TransType_0_YV)
	{
		CalTranSort0_YV(fIfault,fIalpha,fIbeta);
	}
	else if (m_nTranSort_ElecRailway == ElecRailway_TransType_1_YD11)
	{
		CalTranSort1_YD11(fIfault,fIalpha,fIbeta);
	}
	else if (m_nTranSort_ElecRailway == ElecRailway_TransType_2_Single)
	{
		CalTranSort2_Single(fIfault,fIalpha,fIbeta);
	}
	else if (m_nTranSort_ElecRailway == ElecRailway_TransType_3_YDD)
	{
		CalTranSort3_YDD(fIfault,fIalpha,fIbeta);
	}
	else if (m_nTranSort_ElecRailway == ElecRailway_TransType_4_Scott1)
	{
		CalTranSort4_Scott1(fIfault,fIalpha,fIbeta);
	}
	else if (m_nTranSort_ElecRailway == ElecRailway_TransType_5_VV1)
	{
		CalTranSort5_VV1(fIfault,fIalpha,fIbeta);
	}
	else if (m_nTranSort_ElecRailway == ElecRailway_TransType_6_VX)
	{
		CalTranSort6_VX(fIfault,fIalpha,fIbeta);
	}
	else if (m_nTranSort_ElecRailway == ElecRailway_TransType_7_YA)
	{
		CalTranSort7_YA(fIfault,fIalpha,fIbeta);
	}
	else if (m_nTranSort_ElecRailway == ElecRailway_TransType_8_ThreeVV)
	{
		CalTranSort8_ThreeVV(fIfault,fIalpha,fIbeta);
	}
	else if (m_nTranSort_ElecRailway == ElecRailway_TransType_9_Scott2)
	{
		CalTranSort9_Scott2(fIfault,fIalpha,fIbeta);
	}
	else if (m_nTranSort_ElecRailway == ElecRailway_TransType_10_Scott3)
	{
		CalTranSort10_Scott3(fIfault,fIalpha,fIbeta);
	}
	else if (m_nTranSort_ElecRailway == ElecRailway_TransType_11_VV2)
	{
		CalTranSort11_VV2(fIfault,fIalpha,fIbeta);
	}
	else if (m_nTranSort_ElecRailway == ElecRailway_TransType_12_Scott4)
	{
		CalTranSort12_Scott4(fIfault,fIalpha,fIbeta);
	}
	else if (m_nTranSort_ElecRailway == ElecRailway_TransType_13_ThreeVV2)
	{
		CalTranSort13_ThreeVV2(fIfault,fIalpha,fIbeta);
	}
	else if (m_nTranSort_ElecRailway == ElecRailway_TransType_14_ThreeVV3)
	{
		CalTranSort14_ThreeVV3(fIfault,fIalpha,fIbeta);
	}
	else if (m_nTranSort_ElecRailway == ElecRailway_TransType_15_ThreeYV2)
	{
		CalTranSort15_ThreeYV2(fIfault,fIalpha,fIbeta);
	}
	else if (m_nTranSort_ElecRailway == ElecRailway_TransType_16_Scott5)
	{
		CalTranSort16_Scott5(fIfault,fIalpha,fIbeta);
	}
	else if (m_nTranSort_ElecRailway == ElecRailway_TransType_17_YD11_YT)
	{
		CalTranSort17_YD11_YT(fIfault,fReimbCurr_YD11,fIalpha,fIbeta);
	}
	else if (m_nTranSort_ElecRailway == ElecRailway_TransType_18_ThreeYV2_YT)
	{
		CalTranSort18_ThreeYV2_YT(fIfault,fReimbCurr_YD11,fIalpha,fIbeta);
	}
}

void CSttDiffCurrCalculatTool::CalTranSort0_YV(float fIfault,float &fIalpha,float &fIbeta)
{
	float fKph = m_fKph_ElecRailway;

	if (m_nPhase == 0)
	{
		fIalpha = (fIfault*fKph)/((0.366*0.366)/1.366 - 1.366);
		fIbeta = (0.366/1.366)*fIalpha;
	}
	else if (m_nPhase == 1)
	{
		fIalpha = (fIfault*fKph)/(1.732);
		fIbeta = -fIalpha;
	}
	else if (m_nPhase == 2)
	{
		fIalpha = (fIfault*fKph)/(1 + 1.366/0.366);
		fIbeta = (0.366/1.366)*fIalpha;
	}
}

void CSttDiffCurrCalculatTool::CalTranSort1_YD11(float fIfault,float &fIalpha,float &fIbeta)
{
	float fKph = m_fKph_ElecRailway;
	float fReimbCurr = 0.0f;
	int nReimbPhase = 0;

	if (m_nPhase == 0)
	{
		fIalpha = -fIfault*fKph;
		fIbeta = 0;
		fReimbCurr = (fIalpha + fIbeta)/fKph;
		nReimbPhase = 2;
	}
	else if (m_nPhase == 1)
	{
		fIbeta = -fIfault*fKph;
		fIalpha = -fIbeta;
		fReimbCurr = -fIalpha/fKph;
		nReimbPhase = 0;
	}
	else if (m_nPhase == 2)
	{
		fIalpha = 0;
		fIbeta = fIfault*fKph - fIalpha;
		fReimbCurr = -fIbeta/fKph;
		nReimbPhase = 1;
	}

	fReimbCurr = -fReimbCurr;//20220905 补偿电流应该与低压侧计算的电流反向(暂时只在此公式中处理,待验证确认)
	m_arryoCurrent[nReimbPhase].famptitude = fabs(fReimbCurr);

	if (fReimbCurr<0)
	{
		m_arryoCurrent[nReimbPhase].fphase = 180.0f;
	}
}

void CSttDiffCurrCalculatTool::CalTranSort17_YD11_YT(float fIfault,float fReimbCurr_YD11,float &fIalpha,float &fIbeta)
{
	float fKph = m_fKph_ElecRailway;

	if (m_nPhase == 0)
	{
		fIalpha = fIfault*fKph;
		fIbeta = 0;
	}
	else if (m_nPhase == 1)
	{
		fIbeta = fIfault*fKph;
		fIalpha = -fIbeta;
	}
	else if (m_nPhase == 2)
	{
		fIalpha = 0;
		fIbeta = -fIfault*fKph + fIalpha;
	}

// 	float fKph = 1/m_fKph_ElecRailway;//取倒数
// 
// 	if (m_nPhase == 0)
// 	{
// 		fIalpha = -fIfault*fKph;
// 		fIbeta = fReimbCurr_YD11*fKph - fIalpha;
// 	}
// 	else if (m_nPhase == 1)
// 	{
// 		fIbeta = -fIfault*fKph;
// 		fIalpha = -fReimbCurr_YD11*fKph;
// 	}
// 	else if (m_nPhase == 2)
// 	{
// 		fIbeta = -fReimbCurr_YD11*fKph;
// 		fIalpha = fIfault*fKph - fIbeta;
// 	}
}

void CSttDiffCurrCalculatTool::CalTranSort2_Single(float fIfault,float &fIalpha,float &fIbeta)
{
	float fKph = m_fKph_ElecRailway;

	if (m_nPhase == 0)
	{
		fIalpha = -fIfault*fKph;
		fIbeta = 0;
	}
	else if (m_nPhase == 1)
	{
		fIalpha = fIfault*fKph;
		fIbeta = 0;
	}
	else if (m_nPhase == 2)
	{
		fIalpha = 0;
		fIbeta = 0;
	}
}

void CSttDiffCurrCalculatTool::CalTranSort3_YDD(float fIfault,float &fIalpha,float &fIbeta)
{
	float fKph = m_fKph_ElecRailway;
	float fReimbCurr = 0.0f;
	int nReimbPhase = 0;

	if (m_nPhase == 0)
	{
		fIalpha = -fIfault*fKph/3;
		fIbeta = -fIalpha;
		fReimbCurr = (fIalpha-2*fIbeta)/fKph;
		nReimbPhase = 2;
	}
	else if (m_nPhase == 1)
	{
		fIalpha = fIfault*fKph/1.5;
		fIbeta = 0.5*fIalpha;
		fReimbCurr = (-2*fIalpha+fIbeta)/fKph;
		nReimbPhase = 0;
	}
	else if (m_nPhase == 2)
	{
		fIalpha = -fIfault*fKph/3;
		fIbeta = 2*fIalpha;
		fReimbCurr = (fIalpha+fIbeta)/fKph;
		nReimbPhase = 1;
	}

	m_arryoCurrent[nReimbPhase].famptitude = fabs(fReimbCurr);

	if (fReimbCurr<0)
	{
		m_arryoCurrent[nReimbPhase].fphase = 180.0f;
	}
}

void CSttDiffCurrCalculatTool::CalTranSort4_Scott1(float fIfault,float &fIalpha,float &fIbeta)
{
	float fKph = m_fKph_ElecRailway;
	float fReimbCurr = 0.0f;
	int nReimbPhase = 0;

	if (m_nPhase == 0)
	{
		fIalpha = -fIfault*fKph/2;
		fIbeta = -fIalpha/1.7320508;
		fReimbCurr = (2*fIalpha)/fKph;
		nReimbPhase = 2;
	}
	else if (m_nPhase == 1)
	{
		fIalpha = 0;
		fIbeta =  -fIfault*fKph/1.7320508;
		fReimbCurr = (-fIalpha+1.7320508*fIbeta)/fKph;
		nReimbPhase = 0;
	}
	else if (m_nPhase == 2)
	{
		fIalpha = fIfault*fKph/2;
		fIbeta = fIalpha/1.7320508;
		fReimbCurr = (-fIalpha-1.7320508*fIbeta)/fKph;
		nReimbPhase = 1;
	}

	m_arryoCurrent[nReimbPhase].famptitude = fabs(fReimbCurr);

	if (fReimbCurr<0)
	{
		m_arryoCurrent[nReimbPhase].fphase = 180.0f;
	}
}

void CSttDiffCurrCalculatTool::CalTranSort5_VV1(float fIfault,float &fIalpha,float &fIbeta)
{
	float fKph = m_fKph_ElecRailway;

	if (m_nPhase == 0)
	{
		fIalpha = -fIfault*fKph;
		fIbeta = 0;
	}
	else if (m_nPhase == 1)
	{
		fIalpha = 0;
		fIbeta =  0;
	}
	else if (m_nPhase == 2)
	{
		fIalpha = 0;
		fIbeta = -fIfault*fKph;
	}
}

void CSttDiffCurrCalculatTool::CalTranSort6_VX(float fIfault,float &fIalpha,float &fIbeta)
{
	float fKph = m_fKph_ElecRailway;

	if (m_nPhase == 0)
	{
		fIalpha = -fIfault*fKph;
		fIbeta = 0;
	}
	else if (m_nPhase == 1)
	{
		fIalpha = 0;
		fIbeta =  -fIfault*fKph;
	}
	else if (m_nPhase == 2)
	{
		fIalpha = 0;
		fIbeta = 0;
	}
}

void CSttDiffCurrCalculatTool::CalTranSort7_YA(float fIfault,float &fIalpha,float &fIbeta)
{
	float fKph = m_fKph_ElecRailway;
	float fReimbCurr = 0.0f;
	int nReimbPhase = 0;

	if (m_nPhase == 0)
	{
		fIalpha = (fIfault*fKph)/(2.154-0.577*0.577/2.154);
		fIbeta = 0.577*fIalpha/2.154;
		fReimbCurr = (-1.577*fIalpha-1.577*fIbeta)/fKph;
		nReimbPhase = 2;
	}
	else if (m_nPhase == 1)
	{
		fIalpha = -(fIfault*fKph)/(0.577+2.154);
		fIbeta = -fIalpha;
		fReimbCurr = (2.154*fIalpha-0.577*fIbeta)/fKph;
		nReimbPhase = 0;
	}
	else if (m_nPhase == 2)
	{
		fIalpha = -(fIfault*fKph)/(1.577+2.154*1.577/0.577);
		fIbeta = 2.154*fIalpha/0.577;
		fReimbCurr = (-0.577*fIalpha+2.154*fIbeta)/fKph;
		nReimbPhase = 1;
	}

	m_arryoCurrent[nReimbPhase].famptitude = fabs(fReimbCurr);

	if (fReimbCurr<0)
	{
		m_arryoCurrent[nReimbPhase].fphase = 180.0f;
	}
}

void CSttDiffCurrCalculatTool::CalTranSort8_ThreeVV(float fIfault,float &fIalpha,float &fIbeta)
{
	float fKph = m_fKph_ElecRailway;
	float fReimbCurr = 0.0f;
	int nReimbPhase = 0;

	if (m_nPhase == 0)
	{
		fIalpha = -(fIfault*fKph);
		fIbeta = 0;
		fReimbCurr = (fIalpha+fIbeta)/fKph;
		nReimbPhase = 2;
	}
	else if (m_nPhase == 1)
	{
		fIalpha = fIfault*fKph;
		fIbeta = -fIalpha;
		fReimbCurr = (-fIalpha)/fKph;
		nReimbPhase = 0;
	}
	else if (m_nPhase == 2)
	{
		fIalpha = 0;
		fIbeta = fIfault*fKph;
		fReimbCurr = (-fIbeta)/fKph;
		nReimbPhase = 1;
	}

	m_arryoCurrent[nReimbPhase].famptitude = fabs(fReimbCurr);

	if (fReimbCurr<0)
	{
		m_arryoCurrent[nReimbPhase].fphase = 180.0f;
	}
}

void CSttDiffCurrCalculatTool::CalTranSort9_Scott2(float fIfault,float &fIalpha,float &fIbeta)
{
	float fKph = m_fKph_ElecRailway;
	float fReimbCurr = 0.0f;
	int nReimbPhase = 0;

	if (m_nPhase == 0)
	{
		fIalpha = -(fIfault*fKph)/(2*1.7320508);
		fIbeta = -1.7320508*fIalpha;
		fReimbCurr = (-2*fIbeta)/fKph;
		nReimbPhase = 2;
	}
	else if (m_nPhase == 1)
	{
		fIalpha = (fIfault*fKph)/1.7320508;
		fIbeta = 0;
		fReimbCurr = (-1.7320508*fIalpha+fIbeta)/fKph;
		nReimbPhase = 0;
	}
	else if (m_nPhase == 2)
	{
		fIalpha = -fIfault*fKph/(2*1.7320508);
		fIbeta = 1.7320508*fIalpha;
		fReimbCurr = (1.7320508*fIalpha+fIbeta)/fKph;
		nReimbPhase = 1;
	}

	m_arryoCurrent[nReimbPhase].famptitude = fabs(fReimbCurr);

	if (fReimbCurr<0)
	{
		m_arryoCurrent[nReimbPhase].fphase = 180.0f;
	}
}

void CSttDiffCurrCalculatTool::CalTranSort10_Scott3(float fIfault,float &fIalpha,float &fIbeta)
{
	float fKph = m_fKph_ElecRailway;
	float fReimbCurr = 0.0f;
	int nReimbPhase = 0;

	if (m_nPhase == 0)
	{
		fIalpha = -(fIfault*fKph)/1.7320508;
		fIbeta = 0;
		fReimbCurr = (1.7320508*fIalpha+fIbeta)/fKph;
		nReimbPhase = 2;
	}
	else if (m_nPhase == 1)
	{
		fIbeta = -fIfault*fKph/2;
		fIalpha = -fIbeta/1.7320508;
		fReimbCurr = (-1.7320508*fIalpha+fIbeta)/fKph;
		nReimbPhase = 0;
	}
	else if (m_nPhase == 2)
	{
		fIalpha = fIfault*fKph/(2*1.7320508);
		fIbeta = 1.7320508*fIalpha;
		fReimbCurr = (-2*fIbeta)/fKph;
		nReimbPhase = 1;
	}

	m_arryoCurrent[nReimbPhase].famptitude = fabs(fReimbCurr);

	if (fReimbCurr<0)
	{
		m_arryoCurrent[nReimbPhase].fphase = 180.0f;
	}
}

void CSttDiffCurrCalculatTool::CalTranSort11_VV2(float fIfault,float &fIalpha,float &fIbeta)
{
	float fKph = m_fKph_ElecRailway;

	if (m_nPhase == 0)
	{
		fIalpha = -fIfault*fKph;
		fIbeta = 0;
	}
	else if (m_nPhase == 1)
	{
		fIalpha = 0;
		fIbeta = fIfault*fKph;
	}
	else if (m_nPhase == 2)
	{
		fIalpha = 0;
		fIbeta = 0;
	}
}

void CSttDiffCurrCalculatTool::CalTranSort12_Scott4(float fIfault,float &fIalpha,float &fIbeta)
{
	float fKph = m_fKph_ElecRailway;
	float fReimbCurr = 0.0f;
	int nReimbPhase = 0;

	if (m_nPhase == 0)
	{
		fIalpha = -fIfault*fKph/2;
		fIbeta = fIalpha/1.7320508;
		fReimbCurr = (2*fIalpha)/fKph;
		nReimbPhase = 2;
	}
	else if (m_nPhase == 1)
	{
		fIalpha = 0;
		fIbeta = fIfault*fKph/1.7320508;
		fReimbCurr = (-fIalpha-1.7320508*fIbeta)/fKph;
		nReimbPhase = 0;
	}
	else if (m_nPhase == 2)
	{
		fIalpha = fIfault*fKph/2;
		fIbeta = -fIalpha/1.7320508;
		fReimbCurr = (-fIalpha+1.7320508*fIbeta)/fKph;
		nReimbPhase = 1;
	}

	m_arryoCurrent[nReimbPhase].famptitude = fabs(fReimbCurr);

	if (fReimbCurr<0)
	{
		m_arryoCurrent[nReimbPhase].fphase = 180.0f;
	}
}

void CSttDiffCurrCalculatTool::CalTranSort13_ThreeVV2(float fIfault,float &fIalpha,float &fIbeta)
{
	float fKph1 = m_fKph_ElecRailway;
	float fKph2 = m_fKph_ElecRailway;//20220518 根据客户的应用场景,不需要设置为两个不同的系数,故都采用此方式
	float fReimbCurr = 0.0f;
	int nReimbPhase = 0;

	if (m_nPhase == 0)
	{
		fIalpha = -fIfault*fKph1;
		fIbeta = -(fKph2/fKph1)*fIalpha;
		fReimbCurr = (-fIbeta)/fKph2;
		nReimbPhase = 2;
	}
	else if (m_nPhase == 1)
	{
		fIalpha = fIfault*fKph1;
		fIbeta = 0;
		nReimbPhase = 0;
		fReimbCurr = (-fIalpha)/fKph1;
	}
	else if (m_nPhase == 2)
	{
		fIalpha = 0;
		fIbeta = -fIfault*fKph2;
		nReimbPhase = 1;
		fReimbCurr = fIalpha/fKph1 + fIbeta/fKph2;
	}

	fReimbCurr = -fReimbCurr;//20220905 补偿电流应该与低压侧计算的电流反向(暂时只在此公式中处理,待验证确认)
	m_arryoCurrent[nReimbPhase].famptitude = fabs(fReimbCurr);

	if (fReimbCurr<0)
	{
		m_arryoCurrent[nReimbPhase].fphase = 180.0f;
	}
}

void CSttDiffCurrCalculatTool::CalTranSort14_ThreeVV3(float fIfault,float &fIalpha,float &fIbeta)
{
	float fKph = m_fKph_ElecRailway;
	float fReimbCurr = 0.0f;
	int nReimbPhase = 0;

	if (m_nPhase == 0)
	{
		fIalpha = fIfault*fKph;
		fIbeta = -fIalpha;
		fReimbCurr = (fIbeta)/fKph;
		nReimbPhase = 2;
	}
	else if (m_nPhase == 1)
	{
		fIalpha = -fIfault*fKph;
		fIbeta = 0;
		fReimbCurr = (fIalpha)/fKph;
		nReimbPhase = 0;
	}
	else if (m_nPhase == 2)
	{
		fIalpha = 0;
		fIbeta = fIfault*fKph;
		fReimbCurr = (-fIalpha-fIbeta)/fKph;
		nReimbPhase = 1;
	}

	m_arryoCurrent[nReimbPhase].famptitude = fabs(fReimbCurr);

	if (fReimbCurr<0)
	{
		m_arryoCurrent[nReimbPhase].fphase = 180.0f;
	}
}

void CSttDiffCurrCalculatTool::CalTranSort15_ThreeYV2(float fIfault,float &fIalpha,float &fIbeta)
{
	float fKph = m_fKph_ElecRailway;
	float fReimbCurr = 0.0f;
	int nReimbPhase = 0;

	if (m_nPhase == 0)
	{
		fIbeta = fIfault*fKph/(1.115*1.115/0.299 - 0.299);
		fIalpha = -1.115*fIbeta/0.299;
		fReimbCurr = (-0.816*fIalpha-0.816*fIbeta)/fKph;
		nReimbPhase = 2;
	}
	else if (m_nPhase == 1)
	{
		fIalpha = -fIfault*fKph/1.414;
		fIbeta = -fIalpha;
		fReimbCurr = (1.115*fIalpha-0.299*fIbeta)/fKph;
		nReimbPhase = 0;
	}
	else if (m_nPhase == 2)
	{
		fIbeta = -fIfault*fKph/(0.816*0.299/1.115 + 0.816);
		fIalpha = 0.299*fIbeta/1.115;
		fReimbCurr = (-0.299*fIalpha-1.115*fIbeta)/fKph;
		nReimbPhase = 1;
	}

	m_arryoCurrent[nReimbPhase].famptitude = fabs(fReimbCurr);

	if (fReimbCurr<0)
	{
		m_arryoCurrent[nReimbPhase].fphase = 180.0f;
	}
}

void CSttDiffCurrCalculatTool::CalTranSort18_ThreeYV2_YT(float fIfault, float fReimbCurr_YD11,float &fIalpha,float &fIbeta)
{
	float fKph = 1/m_fKph_ElecRailway;

	if (m_nPhase == 0)
	{
		fIbeta = -(fReimbCurr_YD11/fKph + 0.816*fIfault/(1.115*fKph))/(0.816*0.299/1.115 + 0.816);
		fIalpha = (fIfault/fKph + 0.299*fIbeta)/1.115;
	}
	else if (m_nPhase == 1)
	{
		fIalpha = (1.115*fReimbCurr_YD11 + 0.299*fIfault)/(fKph*(1.115*1.115-0.299*0.299));
		fIbeta = (fIfault/fKph + 0.299*fIalpha)/1.115;
	}
	else if (m_nPhase == 2)
	{
		fIalpha = -(1.115*fIfault + 0.816*fReimbCurr_YD11)/(fKph*(1.115*0.816+0.816*0.299));
		fIbeta = (fReimbCurr_YD11/fKph + 0.299*fIalpha)/1.115;
	}
}

void CSttDiffCurrCalculatTool::CalTranSort16_Scott5(float fIfault,float &fIalpha,float &fIbeta)
{
	float fKph = m_fKph_ElecRailway;

	if (m_nPhase == 0)
	{
		fIalpha = fIfault*fKph/1.154;
		fIbeta = 0;
	}
	else if (m_nPhase == 1)
	{
		fIalpha = 0;
		fIbeta = fIfault*fKph/1.154;
	}
	else if (m_nPhase == 2)
	{
		fIbeta = 0;
		fIalpha = 0;
	}

	Complex oTmp_comp;
	Complex oI1_comp = oTmp_comp.polar(m_arryoCurrent[0].famptitude,m_arryoCurrent[0].fphase);
	Complex oI3_comp = oTmp_comp.polar(m_arryoCurrent[2].famptitude,m_arryoCurrent[2].fphase);
	Complex oI2_comp = (oI1_comp-oI3_comp);
	m_arryoCurrent[0].famptitude = oI2_comp.norm()/1.7320508;
	m_arryoCurrent[0].fphase = oI2_comp.arg();
}

void CSttDiffCurrCalculatTool::Init()
{
	float fAngle[DIFF_CURR_CAL_CHANNEL_MAX] = {0, -120.0, 120.0, 0, -120.0, 120.0};

	for(int nIndex=0;nIndex<DIFF_CURR_CAL_CHANNEL_MAX;nIndex++)
	{
		m_arryoCurrent[nIndex].famptitude = 0;
		m_arryoCurrent[nIndex].fphase = fAngle[nIndex];
		m_arryoCurrent[nIndex].ffre = m_fFreq;

// 		m_harmCurrent[nIndex].famptitude = 0;
// 		m_harmCurrent[nIndex].fphase = 0;
// 		m_harmCurrent[nIndex].ffre = 0;
	}

	m_fIOutmax = 20.0f;
	m_nInSel = 0;
	m_fIbase = 1.0f;
	m_nSearchMode = 0;

	m_fKjxh = 1.0f;
	m_fKjxl = 1.0f;
	m_fKph = 1.0f;
	m_fKpl = 1.0f;
	m_fKpm = 1.0f;

	m_bMinAxis = FALSE;
	m_nAngleMode = 0;
	m_nIbiasCal = 0;
	m_nWindH = 0;
	m_nWindM = 0;
	m_nWindL = 0;
	m_nWindSide = 0;
	m_fFactor1 = 2.0f;
	m_fFactor2 = 1.0f;
	m_fIet = 1.0f;
	m_nConnectMode = 0;
	m_nPhase = APhase;
	m_bCTStarPoint = TRUE;
	m_nKcal = 1;
	m_nJXFactor = 0;
	m_fSn = 31.5f;
	m_fUh = 110.f;
	m_fUm = 38.5f;
	m_fUl = 10.5f;
	m_fCTPh = 300.0f;
	m_fCTSh = 1.0f;
	m_fCTPm = 800.0f;
	m_fCTSm = 1.0f;
	m_fCTPl = 2000.0f;
	m_fCTSl = 1.0f;

	m_fKpm_Set = m_fKpm;
	m_fKph_Set = m_fKph;
	m_fKpl_Set = m_fKpl;
	m_fKph_ElecRailway = 1.0f;
	m_fFreq = 50.0f;
	m_nRWCTconnect_ElecRailway = 0;
	m_nTranSort_ElecRailway = ElecRailway_TransType_0_YV;
	m_nKphMode_ElecRailway = 1;
}

double CSttDiffCurrCalculatTool::CalStdId(double dIr,double dIcdqd,int nKneePoints,double dIp1,double dIp2,double dIp3,
				double dKid0,double dKid1,double dKid2,double dKid3,double dIsd,
				long nComBineFeature,long nZeroSeqElimiType,long nFaultType,long nClock)
{
	if (nComBineFeature == 0)
	{
		return CalStdId(dIr,dIcdqd,nKneePoints,dIp1,dIp2,dIp3,dKid0,dKid1,dKid2,dKid3,dIsd);
	}

	if (nZeroSeqElimiType == 2)// 2-YD辅助CT
	{
		if (nClock%2 == 0)//	Y/Y，D/D 接线方式
		{
			if (nFaultType > ABCPhase)//单相故障需要处理
			{
				return CalStdId(dIr,dIcdqd*2,nKneePoints,dIp1*2,dIp2*2,dIp3*2,dKid0,dKid1,dKid2,dKid3,dIsd);
			} 
			else
			{
				return CalStdId(dIr,dIcdqd,nKneePoints,dIp1,dIp2,dIp3,dKid0,dKid1,dKid2,dKid3,dIsd);
			}
		} 
		else
		{
			if (nFaultType<ABCPhase)//单相故障需要处理
			{
				return CalStdId(dIr,dIcdqd*2,nKneePoints,dIp1*2,dIp2*2,dIp3*2,dKid0,dKid1,dKid2,dKid3,dIsd);
			} 
			else
			{
				return CalStdId(dIr,dIcdqd,nKneePoints,dIp1,dIp2,dIp3,dKid0,dKid1,dKid2,dKid3,dIsd);
			}
		}
	} 
	else
	{
		if (nFaultType<ABCPhase)//单相故障需要处理
		{
			return CalStdId(dIr,dIcdqd*2,nKneePoints,dIp1*2,dIp2*2,dIp3*2,dKid0,dKid1,dKid2,dKid3,dIsd);
		} 
		else
		{
			return CalStdId(dIr,dIcdqd,nKneePoints,dIp1,dIp2,dIp3,dKid0,dKid1,dKid2,dKid3,dIsd);
		}
	}
}

double CSttDiffCurrCalculatTool::CalStdId(double dIr,double dIcdqd,int nKneePoints,double dIp1,double dIp2,double dIp3,
				double dKid0,double dKid1,double dKid2,double dKid3,double dIsd)
{
	if (dIr < 0.0)
	{
		return dIcdqd;
	}

	double dId = dIcdqd + dIr*dKid0;

	if ((nKneePoints<=0)||(dIr<=dIp1))
	{
		return dId;
	}

	switch (nKneePoints)
	{
	case 1:
		{
			dId = dIcdqd + dIp1*dKid0 + (dIr - dIp1)*dKid1;
		}
		break;
	case 2:
		{
			if (dIr <= dIp2)//当前点在第一段,小于拐点2
			{
				//拐点1的Y坐标 + 当前点在第一段的X轴长度 乘 斜率
				dId = dIcdqd + dIp1*dKid0 + (dIr - dIp1)*dKid1;
			}
			else 
			{
				dId = dIcdqd + dIp1*dKid0 + dIp2*dKid1 + (dIr - dIp2)*dKid2;
			}
		}
		break;
	case 3:
		{
			if (dIr <= dIp2)//当前点在第一段,小于拐点2
			{
				//拐点1的Y坐标 + 当前点在第一段的X轴长度 乘 斜率
				dId = dIcdqd + dIp1*dKid0 + (dIr - dIp1)*dKid1;
			}
			else if (dIr <= dIp3)//当前点在第二段,小于拐点3
			{
				//拐点2的Y坐标 + 当前点在第二段的X轴长度 乘 斜率
				dId = dIcdqd + dIp1*dKid0 + dIp2*dKid1 + (dIr - dIp2)*dKid2;
			}
			else //当前点在第三段
			{
				dId = dIcdqd + dIp1*dKid0 + dIp2*dKid1 + dIp3*dKid2 + (dIr - dIp3)*dKid3;
			}
		}
		break;
	default:
		break;
	}

	if (dId < dIsd)
	{
		return dId;
	}
	else
	{
		return dIsd;
	}
}

/***********************************************************/
//  根据差动和制动电流计算三相电流
/***********************************************************/
void CSttDiffCurrCalculatTool::CurrentCal(float *fId,float fIr)
{
	float fIa,fIaPh,fIb,fIbPh,fIc,fIcPh,fIap,fIapPh,fIbp,fIbpPh,fIcp,fIcpPh;
	float ftemp,fphe;
	float fTmp = 0;

	switch(m_nIbiasCal)//制动方程
	{
	case 0:  //(|I1-I2|)/K1或Ir=(|I1+I2|)/K1
		{
			fIa=(*fId+m_fFactor1*fIr)*m_fIet/2.0;
			fIap=fIa-*fId*m_fIet;
			fIaPh=0.0;
			fIapPh=180.0;
			if(fIap<0.0)
			{
				fIap=-fIap;
				fIapPh=0.0;
			}
			fIb=fIbPh=0.0f;
			fIc=fIcPh=0.0f;
			fIbp=fIbpPh=0.0f;
			fIcp=fIcpPh=0.0f;
		}
		break;
	case 1:  //(|I1|+|I2|*K2)/K1
		{
			if(m_nPhase<ABCPhase)
			{
				fTmp = fIr*m_fFactor1-*fId;//zhouhj 20211007 当差动电流太大,导致无法找到次差流值时,需要特殊处理

				if ((fTmp<0)&&(fabs(fTmp)>0.0001))
				{
					*fId = fIr*m_fFactor1;
				}

				fIa=(*fId*m_fFactor2+m_fFactor1*fIr)*m_fIet/(1+m_fFactor2);
				if(fIa>=*fId*m_fIet)
					fIap=(fIa-*fId*m_fIet);
				else
					fIap=0.0;
			}
			else
			{
				if((m_fFactor1*fIr)<*fId)
				{
					*fId=m_fFactor1*fIr;
				}
				fIa=(*fId+m_fFactor1*fIr)*m_fIet/2.0;
				fIap=(fIa-*fId*m_fIet)/m_fFactor2;
			}

			fIaPh=0.0;
			fIapPh=180.0;
			fIb=fIbPh=0.0f;
			fIc=fIcPh=0.0f;
			fIbp=fIbpPh=0.0f;
			fIcp=fIcpPh=0.0f;
		}
		break;
	case 2:  //max(|I1|,|I2|)
		{
			if(fIr>*fId)
			{
				fIa=fIr*m_fIet;
				fIap=fIa-*fId*m_fIet;
				fIaPh=0.0;
				fIapPh=180.0;
				fIb=fIbPh=0.0f;
				fIc=fIcPh=0.0f;
				fIbp=fIbpPh=0.0f;
				fIcp=fIcpPh=0.0f;
			}
			else if(fIr<=(*fId)&&(*fId)<2.0*fIr)
			{
				fIa=fIr*m_fIet;
				fIap=*fId*m_fIet-fIr*m_fIet;
				fIaPh=0.0;
				fIapPh=0.0;
				fIb=fIbPh=0.0f;
				fIc=fIcPh=0.0f;
				fIbp=fIbpPh=0.0f;
				fIcp=fIcpPh=0.0f;
			}
			else
			{
				*fId=2.0*fIr;
				fIa=fIr*m_fIet;
				fIap=*fId*m_fIet-fIr*m_fIet;
				fIaPh=0.0;
				fIapPh=0.0;
				fIb=fIbPh=0.0f;
				fIc=fIcPh=0.0f;
				fIbp=fIbpPh=0.0f;
				fIcp=fIcpPh=0.0f;
			}
		}
		break;
	case 3: //(|Id-|I1|-|I2||)/K1
		{
			fIa=*fId*m_fIet+m_fFactor1*fIr*m_fIet/2.0;
			fIap=m_fFactor1*fIr*m_fIet/2.0;
			fIaPh=0.0;
			fIapPh=180.0;
			fIb=fIbPh=0.0f;
			fIc=fIcPh=0.0f;
			fIbp=fIbpPh=0.0f;
			fIcp=fIcpPh=0.0f;
		}
		break;
	case 4: //|I2|
		{
			if(fIr>*fId)
			{
				fIap=fIr*m_fIet;
				fIa=fIr*m_fIet-*fId*m_fIet;
				fIaPh=0.0;
				fIapPh=180.0;
			}
			else
			{
				fIap=fIr*m_fIet;
				fIa=*fId*m_fIet-fIr*m_fIet;
				fIaPh=0.0;
				fIapPh=0.0;
			}
			fIb=fIbPh=0.0f;
			fIc=fIcPh=0.0f;
			fIbp=fIbpPh=0.0f;
			fIcp=fIcpPh=0.0f;
		}
		break;
	case 5: // √(K1*I1*I2*Cos(δ))
		{
			fIa=(qSqrt(*fId*(*fId)+4*fIr*fIr/m_fFactor1)+(*fId))/2.0*m_fIet;
			fIap=(qSqrt(*fId*(*fId)+4*fIr*fIr/m_fFactor1)-(*fId))/2.0*m_fIet;
			fIaPh=0.0;
			fIapPh=180.0;
			fIb=fIbPh=0.0f;
			fIc=fIcPh=0.0f;
			fIbp=fIbpPh=0.0f;
			fIcp=fIcpPh=0.0f;
		}
		break;
	}

	if(m_nPhase<ABCPhase)//单相故障的处理
	{
		int nAngleMode;
		if(m_nAngleMode>0)  //the way to correct
		{
			if(m_nPhase<ABCPhase)
			{
				if(m_nWindH==0)
					nAngleMode=m_nAngleMode;

				if(m_nWindH==1)
				{
					if(m_nAngleMode==1)
						nAngleMode=2;

					if(m_nAngleMode==2)
						nAngleMode=1;
				}

				if(nAngleMode==2)
				{
					switch(GetMethod(m_nConnectMode,nAngleMode))
					{
					case 0:
						{
							fIa=fIa/m_fKph*m_fKjxh;
							fIap=fIap/m_fKpl*m_fKjxl;
							if(GetSign(m_nConnectMode,nAngleMode)<0)
								fIaPh+=180.0;
							if(m_bCTStarPoint)
								fIaPh+=180.0;
						}
						break;
					case 1:
						{
							fIb=fIa/m_fKph*m_fKjxh;
							fIbp=fIap/m_fKpl*m_fKjxl;
							if(GetSign(m_nConnectMode,nAngleMode)<0)
								fIbPh+=180.0;
							if(m_bCTStarPoint)
								fIbPh+=180.0;
						}
						break;
					case 2:
						{
							fIc=fIa/m_fKph*m_fKjxh;
							fIcp=fIap/m_fKpl*m_fKjxl;
							if(GetSign(m_nConnectMode,nAngleMode)<0)
								fIcPh+=180.0;
							if(m_bCTStarPoint)
								fIcPh+=180.0;
						}
						break;
					case 3:
						{
							fIa=fIa/m_fKph*m_fKjxh;
							fIap=fIap/m_fKpl*m_fKjxl;
							if(GetSign(m_nConnectMode,nAngleMode)<0)
								fIaPh+=180.0;
							if(m_bCTStarPoint)
								fIaPh+=180.0;
							if(m_nWindH==1&&m_nWindL==0&&m_nAngleMode==1)
							{
								fIbp=fIap;
								fIbpPh=fIapPh+180.0;
							}
							else
							{
								fIbp=fIa/m_fKpl*m_fKjxl/m_fKjxh;
								if(GetSign(m_nConnectMode,nAngleMode)<0)
									fIbpPh=fIaPh-180;
								else
									fIbpPh=fIaPh;
							}
						}
						break;
					case 4:
						{
							fIb=fIa/m_fKph*m_fKjxh;
							fIbp=fIap/m_fKpl*m_fKjxl;
							fIa=0;
							fIaPh=0;
							if(GetSign(m_nConnectMode,nAngleMode)<0)
								fIbPh+=180.0;
							if(m_bCTStarPoint)
								fIbPh+=180.0;
							if(m_nWindH==1&&m_nWindL==0&&m_nAngleMode==1)
							{
								fIcp=fIbp;
								fIcpPh=fIbpPh+180.0;
							}
							else
							{
								fIcp=fIa/m_fKpl*m_fKjxl;
								fIcpPh=fIaPh;
							}
						}
						break;
					case 5:
						{
							if(GetSign(m_nConnectMode,nAngleMode)<0)
								fIaPh+=180.0;
							if(m_bCTStarPoint)
								fIaPh+=180.0;
							fIa=fIa/m_fKph*m_fKjxh;
							fIap=fIap/m_fKpl*m_fKjxl;
							if(m_nWindH==1&&m_nWindL==0&&m_nAngleMode==1)
							{
								fIcp=fIap;
								fIcpPh=fIapPh+180.0;
							}
							else
							{
								fIcp=fIa/m_fKpl*m_fKjxl/m_fKjxh;
								if(GetSign(m_nConnectMode,nAngleMode)<0)
									fIcpPh=fIaPh-180;
								else
									fIcpPh=fIaPh;
							}
						}
						break;
					}
				}

				if(nAngleMode==1)
				{
					switch(GetMethod(m_nConnectMode,nAngleMode))
					{
					case 0:
						{
							fIa=fIa/m_fKph*m_fKjxh;
							fIap=fIap/m_fKpl*m_fKjxl;
							if(GetSign(m_nConnectMode,nAngleMode)<0)
								fIaPh+=180.0;
							if(m_bCTStarPoint)
								fIaPh+=180.0;
						}
						break;
					case 1:
						{
							fIb=fIa/m_fKph*m_fKjxh;
							fIbp=fIap/m_fKpl*m_fKjxl;
							if(GetSign(m_nConnectMode,nAngleMode)<0)
								fIbPh+=180.0;
							if(m_bCTStarPoint)
								fIbPh+=180.0;
						}
						break;
					case 2:
						{
							fIc=fIa/m_fKph*m_fKjxh;
							fIcp=fIap/m_fKpl*m_fKjxl;
							if(GetSign(m_nConnectMode,nAngleMode)<0)
								fIcPh+=180.0;
							if(m_bCTStarPoint)
								fIcPh+=180.0;
						}
						break;
					case 3:
						{
							fIbPh=fIaPh+180.0;
							fIap=fIap/m_fKpl*m_fKjxl;
							fIa=fIa/m_fKph*m_fKjxh;
							fIb=fIa;
							if(GetSign(m_nConnectMode,nAngleMode)<0)
							{
								fIapPh+=180.0;
							}
							if(m_bCTStarPoint)
								fIapPh+=180.0;
						}
						break;
					case 4:
						{
							fIbPh=fIaPh;
							fIcPh=fIbPh+180.0;
							fIbp=fIap/m_fKpl*m_fKjxl;
							fIcpPh=fIapPh;
							fIb=fIa/m_fKph*m_fKjxh;
							fIc=fIb;
							fIa=0;
							fIaPh=0;
							if(GetSign(m_nConnectMode,nAngleMode)<0)
								fIbpPh+=180.0;
							if(m_bCTStarPoint)
								fIbpPh+=180.0;
						}
						break;
					case 5:
						{
							fIcPh=fIaPh+180.0;
							fIap=fIap/m_fKpl*m_fKjxl;
							fIa=fIa/m_fKph*m_fKjxh;
							fIc=fIa;
							if(GetSign(m_nConnectMode,nAngleMode)<0)
								fIapPh+=180.0;
							if(m_bCTStarPoint)
								fIapPh+=180.0;
						}
						break;
					case 6:
						{
							fIa=fIa/m_fKph*m_fKjxh;
							fIap=fIap/m_fKpl*m_fKjxl;
							fIb=fIa;
							fIbp=fIap;
							if(GetSign(m_nConnectMode,nAngleMode)<0)
								fIaPh+=180.0;
							if(m_bCTStarPoint)
								fIaPh+=180.0;
							fIbPh=fIaPh+180.0;
							fIbpPh=fIapPh+180.0;
						}
						break;
					}
				}
			}
			else
			{
				if(m_bCTStarPoint)
					fIaPh+=180.0;
				fIa=fIa/m_fKph*m_fKjxh;
				fIap=fIap/m_fKpl*m_fKjxl;
				fIapPh-=30.0*m_nConnectMode;  //m_nConnectMode=12,1,2,...11
				fIa/=m_fKjxh;
				fIap/=m_fKjxl;
				fIb=fIa;
				fIc=fIa;
				fIbp=fIap;
				fIcp=fIap;
				fIbPh=fIaPh-120.0;
				fIcPh=fIaPh+120.0;
				fIbpPh=fIapPh-120.0;
				fIcpPh=fIapPh+120.0;
			}
		}
		else  //外转角
		{
			if(m_nPhase<ABCPhase)
			{
				fIa=fIa/m_fKph;
				fIb=fIb/m_fKph;
				fIc=fIc/m_fKph;
				fIap=fIap/m_fKpl;
				fIbp=fIbp/m_fKpl;
				fIcp=fIcp/m_fKpl;
			}
			else
			{
				fIa=fIa/m_fKph;
				fIap=fIap/m_fKpl;
				fIb=fIa;
				fIc=fIa;
				fIbPh=fIaPh-120.0;
				fIcPh=fIaPh+120.0;
				fIbp=fIap;
				fIcp=fIap;
				fIbpPh=fIapPh-120.0;
				fIcpPh=fIapPh+120.0;
			}

			if(m_bCTStarPoint)
			{
				fIapPh+=180.0;
				fIbpPh+=180.0;
				fIcpPh+=180.0;
			}
		}

		if(m_nPhase==BPhase)
		{
			ftemp=fIc;
			fphe=fIcPh;
			fIc=fIb;
			fIcPh=fIbPh;
			fIb=fIa;
			fIbPh=fIaPh;
			fIa=ftemp;
			fIaPh=fphe;

			ftemp=fIcp;
			fphe=fIcpPh;
			fIcp=fIbp;
			fIcpPh=fIbpPh;
			fIbp=fIap;
			fIbpPh=fIapPh;
			fIap=ftemp;
			fIapPh=fphe;
		}

		if(m_nPhase==CPhase)
		{
			ftemp=fIb;
			fphe=fIbPh;
			fIb=fIc;
			fIbPh=fIcPh;
			fIc=fIa;
			fIcPh=fIaPh;
			fIa=ftemp;
			fIaPh=fphe;

			ftemp=fIbp;
			fphe=fIbpPh;
			fIbp=fIcp;
			fIbpPh=fIcpPh;
			fIcp=fIap;
			fIcpPh=fIapPh;
			fIap=ftemp;
			fIapPh=fphe;
		}

	}
	else//三相及相间故障的处理
	{
		bool bSame = FALSE;
		if (m_nWindSide == 0)
			bSame = (m_nWindH == m_nWindL);

		if (m_nWindSide == 1)
			bSame = (m_nWindH == m_nWindM);

		if (m_nWindSide == 2)
			bSame = (m_nWindL == m_nWindM);

		//zhouhj 2023.10.9 此处不可能再为单相故障,无需此判断
		//if (m_nPhase < ABCPhase)	// 单相故障
		//{
		//	if (m_nAngleMode==1)	// △侧转角
		//		CurrentCal_SP_D(fIa,fIaPh,fIb,fIbPh,fIc,fIcPh,fIap,fIapPh,fIbp,fIbpPh,fIcp,fIcpPh,bSame);

		//	if (m_nAngleMode==2)
		//		CurrentCal_SP_Y(fIa,fIaPh,fIb,fIbPh,fIc,fIcPh,fIap,fIapPh,fIbp,fIbpPh,fIcp,fIcpPh,bSame);
		//}

		if (m_nPhase > ABCPhase)	// 相间故障
		{
			if (m_nAngleMode==1)	// △侧转角
				CurrentCal_IP_D(fIa,fIaPh,fIb,fIbPh,fIc,fIcPh,fIap,fIapPh,fIbp,fIbpPh,fIcp,fIcpPh,bSame);

			if (m_nAngleMode==2)
				CurrentCal_IP_Y(fIa,fIaPh,fIb,fIbPh,fIc,fIcPh,fIap,fIapPh,fIbp,fIbpPh,fIcp,fIcpPh,bSame);
		}

		if(m_nPhase == ABCPhase)// 三相故障
		{
			CurrentCal_SP(fIa,fIaPh,fIb,fIbPh,fIc,fIcPh,fIap,fIapPh,fIbp,fIbpPh,fIcp,fIcpPh);
		}

		// 校正平衡系数
		fIa /= m_fKph;
		fIb /= m_fKph;
		fIc /= m_fKph;
		fIap /= m_fKpl;
		fIbp /= m_fKpl;
		fIcp /= m_fKpl;

		// 校正CT正极性//zhouhj 2023.10.9 对应三相短路,此处不需要再转换相位,在对应的函数中已经做了转换处理
		if(m_bCTStarPoint && (m_nPhase != ABCPhase))
		{
			fIapPh = fIap>0.0001 ? fIapPh+180.0 : fIapPh;
			fIbpPh = fIbp>0.0001 ? fIbpPh+180.0 : fIbpPh;
			fIcpPh = fIcp>0.0001 ? fIcpPh+180.0 : fIcpPh;
		}

		if(m_nPhase==BPhase||m_nPhase==BCPhase)
		{
			ftemp =fIc;
			fphe = fIcPh;
			fIc = fIb;
			fIcPh = fIbPh;
			fIb = fIa;
			fIbPh = fIaPh;
			fIa = ftemp;
			fIaPh = fphe;

			ftemp =fIcp;
			fphe = fIcpPh;
			fIcp = fIbp;
			fIcpPh = fIbpPh;
			fIbp = fIap;
			fIbpPh = fIapPh;
			fIap = ftemp;
			fIapPh = fphe;
		}

		if(m_nPhase==CPhase||m_nPhase==CAPhase)
		{
			ftemp =fIb;
			fphe = fIbPh;
			fIb = fIc;
			fIbPh = fIcPh;
			fIc = fIa;
			fIcPh = fIaPh;
			fIa = ftemp;
			fIaPh = fphe;

			ftemp =fIbp;
			fphe = fIbpPh;
			fIbp = fIcp;
			fIbpPh = fIcpPh;
			fIcp = fIap;
			fIcpPh = fIapPh;
			fIap = ftemp;
			fIapPh = fphe;
		}

	}

	if(fIa>m_fIOutmax||fIb>m_fIOutmax||fIc>m_fIOutmax
		||fIap>m_fIOutmax||fIbp>m_fIOutmax||fIcp>m_fIOutmax)
	{
		if(fIa>m_fIOutmax)
			fIa=m_fIOutmax;
		if(fIb>m_fIOutmax)
			fIb=m_fIOutmax;
		if(fIc>m_fIOutmax)
			fIc=m_fIOutmax;
		if(fIap>m_fIOutmax)
			fIap=m_fIOutmax;
		if(fIbp>m_fIOutmax)
			fIbp=m_fIOutmax;
		if(fIcp>m_fIOutmax)
			fIcp=m_fIOutmax;
	}

	m_arryoCurrent[0].famptitude = fIa;
	m_arryoCurrent[0].fphase = fIaPh;
	m_arryoCurrent[0].ffre = m_fFreq;

	m_arryoCurrent[1].famptitude = fIb;
	m_arryoCurrent[1].fphase = fIbPh;
	m_arryoCurrent[1].ffre = m_fFreq;

	m_arryoCurrent[2].famptitude = fIc;
	m_arryoCurrent[2].fphase = fIcPh;
	m_arryoCurrent[2].ffre = m_fFreq;

	m_arryoCurrent[3].famptitude = fIap;
	m_arryoCurrent[3].fphase = fIapPh;
	m_arryoCurrent[3].ffre = m_fFreq;

	m_arryoCurrent[4].famptitude = fIbp;
	m_arryoCurrent[4].fphase = fIbpPh;
	m_arryoCurrent[4].ffre = m_fFreq;

	m_arryoCurrent[5].famptitude = fIcp;
	m_arryoCurrent[5].fphase = fIcpPh;
	m_arryoCurrent[5].ffre = m_fFreq;
}

void CSttDiffCurrCalculatTool::CurrentCal_CbopDiff(double dI1,double dI2)
{
	float fIa = dI1,fIaPh = 0.0f,fIb = 0.0f,fIbPh = 0.0f,fIc = 0.0f,fIcPh = 0.0f;
	float fIap = dI2,fIapPh = 0.0f,fIbp = 0.0f,fIbpPh = 0.0f,fIcp = 0.0f,fIcpPh = 0.0f;
	float ftemp,fphe;
	float fTmp = 0;

	if(m_nPhase<ABCPhase)//单相故障的处理
	{
		int nAngleMode;
		if(m_nAngleMode>0)  //the way to correct
		{
			if(m_nPhase<ABCPhase)
			{
				if(m_nWindH==0)
					nAngleMode=m_nAngleMode;

				if(m_nWindH==1)
				{
					if(m_nAngleMode==1)
						nAngleMode=2;

					if(m_nAngleMode==2)
						nAngleMode=1;
				}

				if(nAngleMode==2)
				{
					switch(GetMethod(m_nConnectMode,nAngleMode))
					{
					case 0:
						{
							fIa=fIa/m_fKph*m_fKjxh;
							fIap=fIap/m_fKpl*m_fKjxl;
							if(GetSign(m_nConnectMode,nAngleMode)<0)
								fIaPh+=180.0;
							if(m_bCTStarPoint)
								fIaPh+=180.0;
						}
						break;
					case 1:
						{
							fIb=fIa/m_fKph*m_fKjxh;
							fIbp=fIap/m_fKpl*m_fKjxl;
							if(GetSign(m_nConnectMode,nAngleMode)<0)
								fIbPh+=180.0;
							if(m_bCTStarPoint)
								fIbPh+=180.0;
						}
						break;
					case 2:
						{
							fIc=fIa/m_fKph*m_fKjxh;
							fIcp=fIap/m_fKpl*m_fKjxl;
							if(GetSign(m_nConnectMode,nAngleMode)<0)
								fIcPh+=180.0;
							if(m_bCTStarPoint)
								fIcPh+=180.0;
						}
						break;
					case 3:
						{
							fIa=fIa/m_fKph*m_fKjxh;
							fIap=fIap/m_fKpl*m_fKjxl;
							if(GetSign(m_nConnectMode,nAngleMode)<0)
								fIaPh+=180.0;
							if(m_bCTStarPoint)
								fIaPh+=180.0;
							if(m_nWindH==1&&m_nWindL==0&&m_nAngleMode==1)
							{
								fIbp=fIap;
								fIbpPh=fIapPh+180.0;
							}
							else
							{
								fIbp=fIa/m_fKpl*m_fKjxl/m_fKjxh;
								if(GetSign(m_nConnectMode,nAngleMode)<0)
									fIbpPh=fIaPh-180;
								else
									fIbpPh=fIaPh;
							}
						}
						break;
					case 4:
						{
							fIb=fIa/m_fKph*m_fKjxh;
							fIbp=fIap/m_fKpl*m_fKjxl;
							fIa=0;
							fIaPh=0;
							if(GetSign(m_nConnectMode,nAngleMode)<0)
								fIbPh+=180.0;
							if(m_bCTStarPoint)
								fIbPh+=180.0;
							if(m_nWindH==1&&m_nWindL==0&&m_nAngleMode==1)
							{
								fIcp=fIbp;
								fIcpPh=fIbpPh+180.0;
							}
							else
							{
								fIcp=fIa/m_fKpl*m_fKjxl;
								fIcpPh=fIaPh;
							}
						}
						break;
					case 5:
						{
							if(GetSign(m_nConnectMode,nAngleMode)<0)
								fIaPh+=180.0;
							if(m_bCTStarPoint)
								fIaPh+=180.0;
							fIa=fIa/m_fKph*m_fKjxh;
							fIap=fIap/m_fKpl*m_fKjxl;
							if(m_nWindH==1&&m_nWindL==0&&m_nAngleMode==1)
							{
								fIcp=fIap;
								fIcpPh=fIapPh+180.0;
							}
							else
							{
								fIcp=fIa/m_fKpl*m_fKjxl/m_fKjxh;
								if(GetSign(m_nConnectMode,nAngleMode)<0)
									fIcpPh=fIaPh-180;
								else
									fIcpPh=fIaPh;
							}
						}
						break;
					}
				}

				if(nAngleMode==1)
				{
					switch(GetMethod(m_nConnectMode,nAngleMode))
					{
					case 0:
						{
							fIa=fIa/m_fKph*m_fKjxh;
							fIap=fIap/m_fKpl*m_fKjxl;
							if(GetSign(m_nConnectMode,nAngleMode)<0)
								fIaPh+=180.0;
							if(m_bCTStarPoint)
								fIaPh+=180.0;
						}
						break;
					case 1:
						{
							fIb=fIa/m_fKph*m_fKjxh;
							fIbp=fIap/m_fKpl*m_fKjxl;
							if(GetSign(m_nConnectMode,nAngleMode)<0)
								fIbPh+=180.0;
							if(m_bCTStarPoint)
								fIbPh+=180.0;
						}
						break;
					case 2:
						{
							fIc=fIa/m_fKph*m_fKjxh;
							fIcp=fIap/m_fKpl*m_fKjxl;
							if(GetSign(m_nConnectMode,nAngleMode)<0)
								fIcPh+=180.0;
							if(m_bCTStarPoint)
								fIcPh+=180.0;
						}
						break;
					case 3:
						{
							fIbPh=fIaPh+180.0;
							fIap=fIap/m_fKpl*m_fKjxl;
							fIa=fIa/m_fKph*m_fKjxh;
							fIb=fIa;
							if(GetSign(m_nConnectMode,nAngleMode)<0)
							{
								fIapPh+=180.0;
							}
							if(m_bCTStarPoint)
								fIapPh+=180.0;
						}
						break;
					case 4:
						{
							fIbPh=fIaPh;
							fIcPh=fIbPh+180.0;
							fIbp=fIap/m_fKpl*m_fKjxl;
							fIcpPh=fIapPh;
							fIb=fIa/m_fKph*m_fKjxh;
							fIc=fIb;
							fIa=0;
							fIaPh=0;
							if(GetSign(m_nConnectMode,nAngleMode)<0)
								fIbpPh+=180.0;
							if(m_bCTStarPoint)
								fIbpPh+=180.0;
						}
						break;
					case 5:
						{
							fIcPh=fIaPh+180.0;
							fIap=fIap/m_fKpl*m_fKjxl;
							fIa=fIa/m_fKph*m_fKjxh;
							fIc=fIa;
							if(GetSign(m_nConnectMode,nAngleMode)<0)
								fIapPh+=180.0;
							if(m_bCTStarPoint)
								fIapPh+=180.0;
						}
						break;
					case 6:
						{
							fIa=fIa/m_fKph*m_fKjxh;
							fIap=fIap/m_fKpl*m_fKjxl;
							fIb=fIa;
							fIbp=fIap;
							if(GetSign(m_nConnectMode,nAngleMode)<0)
								fIaPh+=180.0;
							if(m_bCTStarPoint)
								fIaPh+=180.0;
							fIbPh=fIaPh+180.0;
							fIbpPh=fIapPh+180.0;
						}
						break;
					}
				}
			}
			else
			{
				if(m_bCTStarPoint)
					fIaPh+=180.0;
				fIa=fIa/m_fKph*m_fKjxh;
				fIap=fIap/m_fKpl*m_fKjxl;
				fIapPh-=30.0*m_nConnectMode;  //m_nConnectMode=12,1,2,...11
				fIa/=m_fKjxh;
				fIap/=m_fKjxl;
				fIb=fIa;
				fIc=fIa;
				fIbp=fIap;
				fIcp=fIap;
				fIbPh=fIaPh-120.0;
				fIcPh=fIaPh+120.0;
				fIbpPh=fIapPh-120.0;
				fIcpPh=fIapPh+120.0;
			}
		}
		else  //外转角
		{
			if(m_nPhase<ABCPhase)
			{
				fIa=fIa/m_fKph;
				fIb=fIb/m_fKph;
				fIc=fIc/m_fKph;
				fIap=fIap/m_fKpl;
				fIbp=fIbp/m_fKpl;
				fIcp=fIcp/m_fKpl;
			}
			else
			{
				fIa=fIa/m_fKph;
				fIap=fIap/m_fKpl;
				fIb=fIa;
				fIc=fIa;
				fIbPh=fIaPh-120.0;
				fIcPh=fIaPh+120.0;
				fIbp=fIap;
				fIcp=fIap;
				fIbpPh=fIapPh-120.0;
				fIcpPh=fIapPh+120.0;
			}

			if(m_bCTStarPoint)
			{
				fIapPh+=180.0;
				fIbpPh+=180.0;
				fIcpPh+=180.0;
			}
		}

		if(m_nPhase==BPhase)
		{
			ftemp=fIc;
			fphe=fIcPh;
			fIc=fIb;
			fIcPh=fIbPh;
			fIb=fIa;
			fIbPh=fIaPh;
			fIa=ftemp;
			fIaPh=fphe;

			ftemp=fIcp;
			fphe=fIcpPh;
			fIcp=fIbp;
			fIcpPh=fIbpPh;
			fIbp=fIap;
			fIbpPh=fIapPh;
			fIap=ftemp;
			fIapPh=fphe;
		}

		if(m_nPhase==CPhase)
		{
			ftemp=fIb;
			fphe=fIbPh;
			fIb=fIc;
			fIbPh=fIcPh;
			fIc=fIa;
			fIcPh=fIaPh;
			fIa=ftemp;
			fIaPh=fphe;

			ftemp=fIbp;
			fphe=fIbpPh;
			fIbp=fIcp;
			fIbpPh=fIcpPh;
			fIcp=fIap;
			fIcpPh=fIapPh;
			fIap=ftemp;
			fIapPh=fphe;
		}

	}
	else//三相及相间故障的处理
	{
		bool bSame = FALSE;
		if (m_nWindSide == 0)
			bSame = (m_nWindH == m_nWindL);

		if (m_nWindSide == 1)
			bSame = (m_nWindH == m_nWindM);

		if (m_nWindSide == 2)
			bSame = (m_nWindL == m_nWindM);

		//zhouhj 2023.10.9 此处不可能再为单相故障,无需此判断
		//if (m_nPhase < ABCPhase)	// 单相故障
		//{
		//	if (m_nAngleMode==1)	// △侧转角
		//		CurrentCal_SP_D(fIa,fIaPh,fIb,fIbPh,fIc,fIcPh,fIap,fIapPh,fIbp,fIbpPh,fIcp,fIcpPh,bSame);

		//	if (m_nAngleMode==2)
		//		CurrentCal_SP_Y(fIa,fIaPh,fIb,fIbPh,fIc,fIcPh,fIap,fIapPh,fIbp,fIbpPh,fIcp,fIcpPh,bSame);
		//}

		if (m_nPhase > ABCPhase)	// 相间故障
		{
			if (m_nAngleMode==1)	// △侧转角
				CurrentCal_IP_D(fIa,fIaPh,fIb,fIbPh,fIc,fIcPh,fIap,fIapPh,fIbp,fIbpPh,fIcp,fIcpPh,bSame);

			if (m_nAngleMode==2)
				CurrentCal_IP_Y(fIa,fIaPh,fIb,fIbPh,fIc,fIcPh,fIap,fIapPh,fIbp,fIbpPh,fIcp,fIcpPh,bSame);
		}

		if(m_nPhase == ABCPhase)// 三相故障
		{
			CurrentCal_SP(fIa,fIaPh,fIb,fIbPh,fIc,fIcPh,fIap,fIapPh,fIbp,fIbpPh,fIcp,fIcpPh);
		}

		// 校正平衡系数
		fIa /= m_fKph;
		fIb /= m_fKph;
		fIc /= m_fKph;
		fIap /= m_fKpl;
		fIbp /= m_fKpl;
		fIcp /= m_fKpl;

		// 校正CT正极性//zhouhj 2023.10.9 对应三相短路,此处不需要再转换相位,在对应的函数中已经做了转换处理
		if(m_bCTStarPoint && (m_nPhase != ABCPhase))
		{
			fIapPh = fIap>0.0001 ? fIapPh+180.0 : fIapPh;
			fIbpPh = fIbp>0.0001 ? fIbpPh+180.0 : fIbpPh;
			fIcpPh = fIcp>0.0001 ? fIcpPh+180.0 : fIcpPh;
		}

		if(m_nPhase==BPhase||m_nPhase==BCPhase)
		{
			ftemp =fIc;
			fphe = fIcPh;
			fIc = fIb;
			fIcPh = fIbPh;
			fIb = fIa;
			fIbPh = fIaPh;
			fIa = ftemp;
			fIaPh = fphe;

			ftemp =fIcp;
			fphe = fIcpPh;
			fIcp = fIbp;
			fIcpPh = fIbpPh;
			fIbp = fIap;
			fIbpPh = fIapPh;
			fIap = ftemp;
			fIapPh = fphe;
		}

		if(m_nPhase==CPhase||m_nPhase==CAPhase)
		{
			ftemp =fIb;
			fphe = fIbPh;
			fIb = fIc;
			fIbPh = fIcPh;
			fIc = fIa;
			fIcPh = fIaPh;
			fIa = ftemp;
			fIaPh = fphe;

			ftemp =fIbp;
			fphe = fIbpPh;
			fIbp = fIcp;
			fIbpPh = fIcpPh;
			fIcp = fIap;
			fIcpPh = fIapPh;
			fIap = ftemp;
			fIapPh = fphe;
		}

	}

	if(fIa>m_fIOutmax||fIb>m_fIOutmax||fIc>m_fIOutmax
		||fIap>m_fIOutmax||fIbp>m_fIOutmax||fIcp>m_fIOutmax)
	{
		if(fIa>m_fIOutmax)
			fIa=m_fIOutmax;
		if(fIb>m_fIOutmax)
			fIb=m_fIOutmax;
		if(fIc>m_fIOutmax)
			fIc=m_fIOutmax;
		if(fIap>m_fIOutmax)
			fIap=m_fIOutmax;
		if(fIbp>m_fIOutmax)
			fIbp=m_fIOutmax;
		if(fIcp>m_fIOutmax)
			fIcp=m_fIOutmax;
	}

	m_arryoCurrent[0].famptitude = fIa;
	m_arryoCurrent[0].fphase = fIaPh;
	m_arryoCurrent[0].ffre = m_fFreq;

	m_arryoCurrent[1].famptitude = fIb;
	m_arryoCurrent[1].fphase = fIbPh;
	m_arryoCurrent[1].ffre = m_fFreq;

	m_arryoCurrent[2].famptitude = fIc;
	m_arryoCurrent[2].fphase = fIcPh;
	m_arryoCurrent[2].ffre = m_fFreq;

	m_arryoCurrent[3].famptitude = fIap;
	m_arryoCurrent[3].fphase = fIapPh;
	m_arryoCurrent[3].ffre = m_fFreq;

	m_arryoCurrent[4].famptitude = fIbp;
	m_arryoCurrent[4].fphase = fIbpPh;
	m_arryoCurrent[4].ffre = m_fFreq;

	m_arryoCurrent[5].famptitude = fIcp;
	m_arryoCurrent[5].fphase = fIcpPh;
	m_arryoCurrent[5].ffre = m_fFreq;
}

void CSttDiffCurrCalculatTool::CalIrId_CbopDiff(double dFaultCurrent,long nFaultLocation,double &dIr,double &dId)
{
	double dI1 = 0.0f,dI2 = 0.0f;

	switch (nFaultLocation)
	{
	case 0://0-高压侧（区内）
		{
			dI1 = dFaultCurrent;
			dI2 = dFaultCurrent;
		}
		break;
	case 1://1-高压侧（区外）
		{
			dI1 = dFaultCurrent;
			dI2 = -dFaultCurrent;
		}
		break;
	case 2://2-低压侧（区内）
		{
			dI1 = dFaultCurrent;
			dI2 = dFaultCurrent;
		}
		break;
	case 3://3-低压侧（区外）
		{
			dI1 = dFaultCurrent;
			dI2 = -dFaultCurrent;
		}
		break;
	default:
		break;
	}

	dId = fabs(dI1 + dI2);
	switch(m_nIbiasCal)//制动方程
	{
	case 0:  //(|I1-I2|)/K1或Ir=(|I1+I2|)/K1
		{
			dIr = (fabs(dI1) + fabs(dI2)) /m_fFactor1;
		}
		break;
	case 1:  //(|I1|+|I2|*K2)/K1
		{
			dIr = (fabs(dI1) + fabs(dI2)*m_fFactor2) /m_fFactor1;
		}
		break;
	case 2:  //max(|I1|,|I2|)
		{
			dIr = max(fabs(dI1), fabs(dI2));
		}
		break;
	case 3: //(|Id-|I1|-|I2||)/K1
		{
			dIr = (dId - fabs(dI1) - fabs(dI2)) /m_fFactor1;
		}
		break;
	case 4: //|I2|
		{
			dIr = fabs(dI2);
		}
		break;
	case 5: // √(K1*I1*I2*Cos(δ)) 
		{
			dIr = qSqrt(m_fFactor1 * fabs(dI1 * dI2));
		}
		break;
	}
    return;
}

void CSttDiffCurrCalculatTool::CurrentCal_CbopDiff(double dFaultCurrent,long nFaultLocation,long nEarthing)
{
	dFaultCurrent *= m_fIet;//换算为实际故障电流安培值
	double dI1 = 0.0f,dI2 = 0.0f;

	switch (nFaultLocation)
	{
	case 0://0-高压侧（区内）
		{
			dI1 = dFaultCurrent;
			dI2 = dFaultCurrent;
			dI1 /= m_fKph;
			dI2 /= m_fKpl;
		}
		break;
	case 1://1-高压侧（区外）
		{
			dI1 = dFaultCurrent;
			dI2 = -dFaultCurrent;
			dI1 /= m_fKph;
			dI2 /= m_fKpl;
		}
		break;
	case 2://2-低压侧（区内）
		{
			dI1 = dFaultCurrent;
			dI2 = dFaultCurrent;
			dI1 /= m_fKph;
			dI2 /= m_fKpl;
		}
		break;
	case 3://3-低压侧（区外）
		{
			dI1 = dFaultCurrent;
			dI2 = -dFaultCurrent;
			dI1 /= m_fKph;
			dI2 /= m_fKpl;
		}
		break;
	default:
		break;
	}

	//中性点接地模式,还采用之前的模式，三相故障或者相间故障还跟之前保持一致,相间故障默认没有零序电流,三相故障默认三相正序
	if (nEarthing || (m_nPhase == ABCPhase))
	{
		return CurrentCal_CbopDiff(dI1,dI2);
	}

	//以下为中性点不接地模式,即需要进行零序补偿

	double dIa = 0.0f,dIaPh = 0.0f,dIb = 0.0f,dIbPh = 0.0f,dIc = 0.0f,dIcPh = 0.0f;
	double dIap = 0.0f,dIapPh = 0.0f,dIbp = 0.0f,dIbpPh = 0.0f,dIcp = 0.0f,dIcpPh = 0.0f;

	switch(m_nAngleMode)
	{
	case 1://△侧校正
		{
			CurrentCal_ByI1I2_DTrans(dI1,dI2,dIa,dIaPh,dIb,dIbPh,dIc,dIcPh,dIap,dIapPh,dIbp,dIbpPh,dIcp,dIcpPh);
		}
		break;
	case 2://Y侧校正
		{
			CurrentCal_ByI1I2_YTrans(dI1,dI2,dIa,dIaPh,dIb,dIbPh,dIc,dIcPh,dIap,dIapPh,dIbp,dIbpPh,dIcp,dIcpPh);
		}
		break;
	default://无校准
		{
			switch(m_nPhase)
			{
			case APhase:
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1/2;
					dIbPh = 180.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = dI2;
					dIapPh = 180.0f;
					dIbp = dI2/2;
					dIbpPh = 0.0f;
					dIcp = dI2/2; 
					dIcpPh = 0.0f;
				}
				break;
			case BPhase:
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = dI2/2;
					dIapPh = 0.0f;
					dIbp = dI2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 0.0f;
				}
				break;
			case CPhase:
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1/2; 
					dIbPh = 180.0f;
					dIc = dI1;
					dIcPh = 0.0f;

					dIap = dI2/2;
					dIapPh = 0.0f;
					dIbp = dI2/2; 
					dIbpPh = 0.0f;
					dIcp = dI2;
					dIcpPh = 180.0f;
				}
				break;
			case ABPhase:
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1;
					dIbPh = 180.0f;
					dIc = 0.0f; 
					dIcPh = 0.0f;
					dIap = dI2;
					dIapPh = 180.0f;
					dIbp = dI2;
					dIbpPh = 0.0f;
					dIcp = 0.0f; 
					dIcpPh = 0.0f;
				}
				break;
			case BCPhase:
				{
					dIa = 0.0f;
					dIaPh = 0.0f;
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1; 
					dIcPh = 180.0f;
					dIap = 0.0f;
					dIapPh = 0.0f;
					dIbp = dI2;
					dIbpPh = 180.0f;
					dIcp = dI2; 
					dIcpPh = 0.0f;
				}
				break;
			case CAPhase:
				{
					dIa = dI1;
					dIaPh = 180.0f;
					dIb = 0.0f;
					dIbPh = 0.0f;
					dIc = dI1; 
					dIcPh = 0.0f;
					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = 0.0f;
					dIbpPh = 0.0f;
					dIcp = dI2; 
					dIcpPh = 180.0f;
				}
				break;
			default:
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1/2;
					dIbPh = 180.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = dI2;
					dIapPh = 180.0f;
					dIbp = dI2/2;
					dIbpPh = 0.0f;
					dIcp = dI2/2; 
					dIcpPh = 0.0f;
				}
				break;
			}
		}
		break;
	}

	if(dIa>m_fIOutmax)
		dIa=m_fIOutmax;
	if(dIb>m_fIOutmax)
		dIb=m_fIOutmax;
	if(dIc>m_fIOutmax)
		dIc=m_fIOutmax;
	if(dIap>m_fIOutmax)
		dIap=m_fIOutmax;
	if(dIbp>m_fIOutmax)
		dIbp=m_fIOutmax;
	if(dIcp>m_fIOutmax)
		dIcp=m_fIOutmax;

	m_arryoCurrent[0].famptitude = dIa;
	m_arryoCurrent[0].fphase = dIaPh;
	m_arryoCurrent[0].ffre = m_fFreq;

	m_arryoCurrent[1].famptitude = dIb;
	m_arryoCurrent[1].fphase = dIbPh;
	m_arryoCurrent[1].ffre = m_fFreq;

	m_arryoCurrent[2].famptitude = dIc;
	m_arryoCurrent[2].fphase = dIcPh;
	m_arryoCurrent[2].ffre = m_fFreq;

	m_arryoCurrent[3].famptitude = dIap;
	m_arryoCurrent[3].fphase = dIapPh;
	m_arryoCurrent[3].ffre = m_fFreq;

	m_arryoCurrent[4].famptitude = dIbp;
	m_arryoCurrent[4].fphase = dIbpPh;
	m_arryoCurrent[4].ffre = m_fFreq;

	m_arryoCurrent[5].famptitude = dIcp;
	m_arryoCurrent[5].fphase = dIcpPh;
	m_arryoCurrent[5].ffre = m_fFreq;

    //如果电流值为负则需逆转相位
    for(int nIndex=0; nIndex<6; nIndex++)
    {
        if(m_arryoCurrent[nIndex].famptitude<0)
        {
            m_arryoCurrent[nIndex].fphase += 180.0f;
            m_arryoCurrent[nIndex].famptitude = -m_arryoCurrent[nIndex].famptitude;
        }
        if(m_arryoCurrent[nIndex].fphase > 180)
        {
            m_arryoCurrent[nIndex].fphase -= 360.0f;
        }
    }
}

bool CSttDiffCurrCalculatTool::GetI1I2_ByIdIr(float *fId,float fIr,double &dI1,double &dI2)
{
	float fIa,fIaPh,fIap,fIapPh;
	float fTmp = 0;

	switch(m_nIbiasCal)//制动方程
	{
	case 0:  //(|I1-I2|)/K1或Ir=(|I1+I2|)/K1
		{
			fIa=(*fId+m_fFactor1*fIr)*m_fIet/2.0;
			fIap=fIa-*fId*m_fIet;
			fIaPh=0.0;
			fIapPh=180.0;
			if(fIap<0.0)
			{
				fIap=-fIap;
				fIapPh=0.0;
			}
		}
		break;
	case 1:  //(|I1|+|I2|*K2)/K1
		{
			if(m_nPhase<ABCPhase)
			{
				fTmp = fIr*m_fFactor1-*fId;//zhouhj 20211007 当差动电流太大,导致无法找到次差流值时,需要特殊处理

				if ((fTmp<0)&&(fabs(fTmp)>0.0001))
				{
					*fId = fIr*m_fFactor1;
				}

				fIa=(*fId*m_fFactor2+m_fFactor1*fIr)*m_fIet/(1+m_fFactor2);
				if(fIa>=*fId*m_fIet)
					fIap=(fIa-*fId*m_fIet);
				else
					fIap=0.0;
			}
			else
			{
				if((m_fFactor1*fIr)<*fId)
				{
					*fId=m_fFactor1*fIr;
				}
				fIa=(*fId+m_fFactor1*fIr)*m_fIet/2.0;
				fIap=(fIa-*fId*m_fIet)/m_fFactor2;
			}

			fIaPh=0.0;
			fIapPh=180.0;
		}
		break;
	case 2:  //max(|I1|,|I2|)
		{
			if(fIr>*fId)
			{
				fIa=fIr*m_fIet;
				fIap=fIa-*fId*m_fIet;
				fIaPh=0.0;
				fIapPh=180.0;
			}
			else if(fIr<=(*fId)&&(*fId)<2.0*fIr)
			{
				fIa=fIr*m_fIet;
				fIap=*fId*m_fIet-fIr*m_fIet;
				fIaPh=0.0;
				fIapPh=0.0;
			}
			else
			{
				*fId=2.0*fIr;
				fIa=fIr*m_fIet;
				fIap=*fId*m_fIet-fIr*m_fIet;
				fIaPh=0.0;
				fIapPh=0.0;
			}
		}
		break;
	case 3: //(|Id-|I1|-|I2||)/K1
		{
			fIa=*fId*m_fIet+m_fFactor1*fIr*m_fIet/2.0;
			fIap=m_fFactor1*fIr*m_fIet/2.0;
			fIaPh=0.0;
			fIapPh=180.0;
		}
		break;
	case 4: //|I2|
		{
			if(fIr>*fId)
			{
				fIap=fIr*m_fIet;
				fIa=fIr*m_fIet-*fId*m_fIet;
				fIaPh=0.0;
				fIapPh=180.0;
			}
			else
			{
				fIap=fIr*m_fIet;
				fIa=*fId*m_fIet-fIr*m_fIet;
				fIaPh=0.0;
				fIapPh=0.0;
			}
		}
		break;
	case 5: // √(K1*I1*I2*Cos(δ))
		{
			fIa=(qSqrt(*fId*(*fId)+4*fIr*fIr/m_fFactor1)+(*fId))/2.0*m_fIet;
			fIap=(qSqrt(*fId*(*fId)+4*fIr*fIr/m_fFactor1)-(*fId))/2.0*m_fIet;
			fIaPh=0.0;
			fIapPh=180.0;
		}
		break;
	}

	dI1=fIa/*/m_fKph*/;
	dI2=fIap/*/m_fKpl*/;
	return true;
}

long CSttDiffCurrCalculatTool::GetTransAngleClockValue()
{
	long nValue = TransAngleClock_YY12;
	if (m_nWindH == 0)//高压侧为Y
	{
		switch(m_nConnectMode)
		{
		case 1: 
			{
				nValue = TransAngleClock_YD1;
			}
			break;
		case 2: 
			{
				nValue = TransAngleClock_YY2;
			}
			break;
		case 3: 
			{
				nValue = TransAngleClock_YD3;
			}
			break;
		case 4: 
			{
				nValue = TransAngleClock_YY4;
			}
			break;
		case 5: 
			{
				nValue = TransAngleClock_YD5;
			}
			break;
		case 6: 
			{
				nValue = TransAngleClock_YY6;
			}
			break;
		case 7: 
			{
				nValue = TransAngleClock_YD7;
			}
			break;
		case 8: 
			{
				nValue = TransAngleClock_YY8;
			}
			break;
		case 9: 
			{
				nValue = TransAngleClock_YD9;
			}
			break;
		case 10: 
			{
				nValue = TransAngleClock_YY10;
			}
			break;
		case 11: 
			{
				nValue = TransAngleClock_YD11;
			}
			break;
		default: 
			{
				nValue = TransAngleClock_YY12;
			}
			break;
		}
	}
	else//否则低压侧为Y
	{
		switch(m_nConnectMode)
		{
		case 1: 
			{
				nValue = TransAngleClock_DY1;
			}
			break;
		case 2: 
			{
				nValue = TransAngleClock_DD2;
			}
			break;
		case 3: 
			{
				nValue = TransAngleClock_DY3;
			}
			break;
		case 4: 
			{
				nValue = TransAngleClock_DD4;
			}
			break;
		case 5: 
			{
				nValue = TransAngleClock_DY5;
			}
			break;
		case 6: 
			{
				nValue = TransAngleClock_DD6;
			}
			break;
		case 7: 
			{
				nValue = TransAngleClock_DY7;
			}
			break;
		case 8: 
			{
				nValue = TransAngleClock_DD8;
			}
			break;
		case 9: 
			{
				nValue = TransAngleClock_DY9;
			}
			break;
		case 10: 
			{
				nValue = TransAngleClock_DD10;
			}
			break;
		case 11: 
			{
				nValue = TransAngleClock_DY11;
			}
			break;
		default: 
			{
				nValue = TransAngleClock_DD12;
			}
			break;
		}
	}

	return nValue;
}

void  CSttDiffCurrCalculatTool::CurrentCal(float *fId,float fIr,long nEarthing)
{
	//中性点接地模式,还采用之前的模式，三相故障或者相间故障还跟之前保持一致,相间故障默认没有零序电流,三相故障默认三相正序
	if (nEarthing || (m_nPhase == ABCPhase))
	{
		return CurrentCal(fId,fIr);
	}

	//以下为中性点不接地模式,即需要进行零序补偿
	double dI1 = 0.0f,dI2 = 0.0f;
	GetI1I2_ByIdIr(fId,fIr,dI1,dI2);//根据差动电流和制动电流计算高压侧及低压侧电流

	//从I1\I2折算为实际电压电流
	dI1 /= m_fKph;
	dI2 /= m_fKpl;

	double dIa = 0.0f,dIaPh = 0.0f,dIb = 0.0f,dIbPh = 0.0f,dIc = 0.0f,dIcPh = 0.0f;
	double dIap = 0.0f,dIapPh = 0.0f,dIbp = 0.0f,dIbpPh = 0.0f,dIcp = 0.0f,dIcpPh = 0.0f;

	switch(m_nAngleMode)
	{
	case 1://△侧校正
		{
			CurrentCal_ByI1I2_DTrans(dI1,dI2,dIa,dIaPh,dIb,dIbPh,dIc,dIcPh,dIap,dIapPh,dIbp,dIbpPh,dIcp,dIcpPh);
		}
		break;
	case 2://Y侧校正
		{
			CurrentCal_ByI1I2_YTrans(dI1,dI2,dIa,dIaPh,dIb,dIbPh,dIc,dIcPh,dIap,dIapPh,dIbp,dIbpPh,dIcp,dIcpPh);
		}
		break;
	default://无校准
		{
			switch(m_nPhase)
			{
			case APhase:
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1/2;
					dIbPh = 180.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = dI2;
					dIapPh = 180.0f;
					dIbp = dI2/2;
					dIbpPh = 0.0f;
					dIcp = dI2/2; 
					dIcpPh = 0.0f;
				}
				break;
			case BPhase:
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = dI2/2;
					dIapPh = 0.0f;
					dIbp = dI2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 0.0f;
				}
				break;
			case CPhase:
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1/2; 
					dIbPh = 180.0f;
					dIc = dI1;
					dIcPh = 0.0f;

					dIap = dI2/2;
					dIapPh = 0.0f;
					dIbp = dI2/2; 
					dIbpPh = 0.0f;
					dIcp = dI2;
					dIcpPh = 180.0f;
				}
				break;
			case ABPhase:
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1;
					dIbPh = 180.0f;
					dIc = 0.0f; 
					dIcPh = 0.0f;
					dIap = dI2;
					dIapPh = 180.0f;
					dIbp = dI2;
					dIbpPh = 0.0f;
					dIcp = 0.0f; 
					dIcpPh = 0.0f;
				}
				break;
			case BCPhase:
				{
					dIa = 0.0f;
					dIaPh = 0.0f;
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1; 
					dIcPh = 180.0f;
					dIap = 0.0f;
					dIapPh = 0.0f;
					dIbp = dI2;
					dIbpPh = 180.0f;
					dIcp = dI2; 
					dIcpPh = 0.0f;
				}
				break;
			case CAPhase:
				{
					dIa = dI1;
					dIaPh = 180.0f;
					dIb = 0.0f;
					dIbPh = 0.0f;
					dIc = dI1; 
					dIcPh = 0.0f;
					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = 0.0f;
					dIbpPh = 0.0f;
					dIcp = dI2; 
					dIcpPh = 180.0f;
				}
				break;
			default:
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1/2;
					dIbPh = 180.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = dI2;
					dIapPh = 180.0f;
					dIbp = dI2/2;
					dIbpPh = 0.0f;
					dIcp = dI2/2; 
					dIcpPh = 0.0f;
				}
				break;
			}
		}
		break;
	}

	if(dIa>m_fIOutmax)
		dIa=m_fIOutmax;
	if(dIb>m_fIOutmax)
		dIb=m_fIOutmax;
	if(dIc>m_fIOutmax)
		dIc=m_fIOutmax;
	if(dIap>m_fIOutmax)
		dIap=m_fIOutmax;
	if(dIbp>m_fIOutmax)
		dIbp=m_fIOutmax;
	if(dIcp>m_fIOutmax)
		dIcp=m_fIOutmax;

	m_arryoCurrent[0].famptitude = dIa;
	m_arryoCurrent[0].fphase = dIaPh;
	m_arryoCurrent[0].ffre = m_fFreq;

	m_arryoCurrent[1].famptitude = dIb;
	m_arryoCurrent[1].fphase = dIbPh;
	m_arryoCurrent[1].ffre = m_fFreq;

	m_arryoCurrent[2].famptitude = dIc;
	m_arryoCurrent[2].fphase = dIcPh;
	m_arryoCurrent[2].ffre = m_fFreq;

	m_arryoCurrent[3].famptitude = dIap;
	m_arryoCurrent[3].fphase = dIapPh;
	m_arryoCurrent[3].ffre = m_fFreq;

	m_arryoCurrent[4].famptitude = dIbp;
	m_arryoCurrent[4].fphase = dIbpPh;
	m_arryoCurrent[4].ffre = m_fFreq;

	m_arryoCurrent[5].famptitude = dIcp;
	m_arryoCurrent[5].fphase = dIcpPh;
	m_arryoCurrent[5].ffre = m_fFreq;

    //如果电流值为负则需逆转相位
    for(int nIndex=0; nIndex<6; nIndex++)
    {
        if(m_arryoCurrent[nIndex].famptitude<0)
        {
            m_arryoCurrent[nIndex].fphase += 180.0f;
            m_arryoCurrent[nIndex].famptitude = -m_arryoCurrent[nIndex].famptitude;
        }
        if(m_arryoCurrent[nIndex].fphase > 180)
        {
            m_arryoCurrent[nIndex].fphase -= 360.0f;
        }
    }
}

void CSttDiffCurrCalculatTool::CurrentCal_ByI1I2_DTrans(double dI1,double dI2,double &dIa,double &dIaPh,double &dIb,double &dIbPh,double &dIc,double &dIcPh,
							  double &dIap,double &dIapPh,double &dIbp,double &dIbpPh,double &dIcp,double &dIcpPh)
{
	switch(m_nPhase)//故障相别
	{
	case APhase: 
		{
			switch(GetTransAngleClockValue())//转角方式及钟点数
			{
			case TransAngleClock_YD1: 
			case TransAngleClock_DY1: 
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1/2;
					dIbPh = 180.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = 1.5f*dI2/SQRT3;
					dIapPh = 180.0f;
					dIbp = 1.5f*dI2/SQRT3;
					dIbpPh = 0.0f;
					dIcp = 0.0f; 
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YY2: 
			case TransAngleClock_DD2:
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1/2;
					dIbPh = 180.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = dI2/2;
					dIapPh = 180.0f;
					dIbp = dI2;
					dIbpPh = 0.0f;
					dIcp = dI2/2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YD3: 
			case TransAngleClock_DY3: 
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1/2;
					dIbPh = 180.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = 0.0f; 
					dIapPh = 0.0f;
					dIbp = 1.5f*dI2/SQRT3;
					dIbpPh = 0.0f;
					dIcp = 1.5f*dI2/SQRT3;
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YY4: 
			case TransAngleClock_DD4: 
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1/2;
					dIbPh = 180.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = dI2/2;
					dIapPh = 0.0f;
					dIbp = dI2/2;
					dIbpPh = 0.0f;
					dIcp = dI2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YD5:
			case TransAngleClock_DY5: 
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1/2;
					dIbPh = 180.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = 1.5f*dI2/SQRT3;
					dIapPh = 0.0f;
					dIbp = 0.0f; 
					dIbpPh = 180.0f;
					dIcp = 1.5f*dI2/SQRT3;
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YY6: 
			case TransAngleClock_DD6:
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1/2;
					dIbPh = 180.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YD7: 
			case TransAngleClock_DY7: 
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1/2;
					dIbPh = 180.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = 1.5f*dI2/SQRT3;
					dIapPh = 0.0f;
					dIbp = 1.5f*dI2/SQRT3;
					dIbpPh = 180.0f;
					dIcp = 0.0f; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YY8: 
			case TransAngleClock_DD8: 
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1/2;
					dIbPh = 180.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = dI2/2;
					dIapPh = 0.0f;
					dIbp = dI2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YD9: 
			case TransAngleClock_DY9: 
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1/2;
					dIbPh = 180.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = 0.0f; 
					dIapPh = 0.0f;
					dIbp = 1.5f*dI2/SQRT3;
					dIbpPh = 180.0f;
					dIcp = 1.5f*dI2/SQRT3;
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YY10: 
			case TransAngleClock_DD10: 
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1/2;
					dIbPh = 180.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = dI2/2;
					dIapPh = 180.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2; 
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YD11: 
			case TransAngleClock_DY11:
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1/2;
					dIbPh = 180.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = 1.5f*dI2/SQRT3;
					dIapPh = 180.0f;
					dIbp = 0.0f; 
					dIbpPh = 0.0f;
					dIcp = 1.5f*dI2/SQRT3;
					dIcpPh = 0.0f;
				}
				break;
			default: 
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1/2;
					dIbPh = 180.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = dI2;
					dIapPh = 180.0f;
					dIbp = dI2/2;
					dIbpPh = 0.0f;
					dIcp = dI2/2; 
					dIcpPh = 0.0f;
				}
				break;
			}
		}
		break;
	case BPhase: 
		{
			switch(GetTransAngleClockValue())//转角方式及钟点数
			{
			case TransAngleClock_YD1: 
			case TransAngleClock_DY1: 
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = 0.0f; 
					dIapPh = 0.0f;
					dIbp = 1.5f*dI2/SQRT3;
					dIbpPh = 180.0f;
					dIcp = 1.5f*dI2/SQRT3;
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YY2: 
			case TransAngleClock_DD2:
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = dI2/2;
					dIapPh = 180.0f;
					dIbp = dI2/2; 
					dIbpPh = 180.0f;
					dIcp = dI2;
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YD3: 
			case TransAngleClock_DY3: 
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = 1.5f*dI2/SQRT3;
					dIapPh = 180.0f;
					dIbp = 0.0f; 
					dIbpPh = 0.0f;
					dIcp = 1.5f*dI2/SQRT3;
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YY4: 
			case TransAngleClock_DD4: 
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = dI2; 
					dIapPh = 180.0f;
					dIbp = dI2/2;
					dIbpPh = 0.0f;
					dIcp = dI2/2;
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YD5:
			case TransAngleClock_DY5: 
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = 1.5f*dI2/SQRT3;
					dIapPh = 180.0f;
					dIbp = 1.5f*dI2/SQRT3;
					dIbpPh = 0.0f;
					dIcp = 0.0f; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YY6: 
			case TransAngleClock_DD6:
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = dI2/2;
					dIapPh = 180.0f;
					dIbp = dI2;
					dIbpPh = 0.0f;
					dIcp = dI2/2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YD7: 
			case TransAngleClock_DY7: 
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = 0.0f; 
					dIapPh = 180.0f;
					dIbp = 1.5f*dI2/SQRT3;
					dIbpPh = 0.0f;
					dIcp = 1.5f*dI2/SQRT3;
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YY8: 
			case TransAngleClock_DD8: 
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = dI2/2;
					dIapPh = 0.0f;
					dIbp = dI2/2; 
					dIbpPh = 0.0f;
					dIcp = dI2;
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YD9: 
			case TransAngleClock_DY9: 
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = 1.5f*dI2/SQRT3;
					dIapPh = 0.0f;
					dIbp = 0.0f; 
					dIbpPh = 0.0f;
					dIcp = 1.5f*dI2/SQRT3;
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YY10: 
			case TransAngleClock_DD10: 
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = dI2; 
					dIapPh = 0.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2/2;
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YD11: 
			case TransAngleClock_DY11:
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = 1.5f*dI2/SQRT3;
					dIapPh = 0.0f;
					dIbp = 1.5f*dI2/SQRT3;
					dIbpPh = 180.0f;
					dIcp = 0.0f; 
					dIcpPh = 0.0f;
				}
				break;
			default: 
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = dI2/2;
					dIapPh = 0.0f;
					dIbp = dI2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 0.0f;
				}
				break;
			}
		}
		break;
	case CPhase: 
		{
			switch(GetTransAngleClockValue())//转角方式及钟点数
			{
			case TransAngleClock_YD1: 
			case TransAngleClock_DY1: 
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1/2; 
					dIbPh = 180.0f;
					dIc = dI1;
					dIcPh = 0.0f;

					dIap = 1.5f*dI2/SQRT3;
					dIapPh = 0.0f;
					dIbp = 0.0f; 
					dIbpPh = 0.0f;
					dIcp = 1.5f*dI2/SQRT3;
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YY2: 
			case TransAngleClock_DD2:
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1/2; 
					dIbPh = 180.0f;
					dIc = dI1;
					dIcPh = 0.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YD3: 
			case TransAngleClock_DY3: 
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1/2; 
					dIbPh = 180.0f;
					dIc = dI1;
					dIcPh = 0.0f;

					dIap = 1.5f*dI2/SQRT3;
					dIapPh = 0.0f;
					dIbp = 1.5f*dI2/SQRT3;
					dIbpPh = 180.0f;
					dIcp = 0.0f; 
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YY4: 
			case TransAngleClock_DD4: 
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1/2; 
					dIbPh = 180.0f;
					dIc = dI1;
					dIcPh = 0.0f;

					dIap = dI2/2;
					dIapPh = 0.0f;
					dIbp = dI2; 
					dIbpPh = 180.0f;
					dIcp = dI2/2;
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YD5:
			case TransAngleClock_DY5: 
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1/2; 
					dIbPh = 180.0f;
					dIc = dI1;
					dIcPh = 0.0f;

					dIap = 0.0f; 
					dIapPh = 180.0f;
					dIbp = 1.5f*dI2/SQRT3;
					dIbpPh = 180.0f;
					dIcp = 1.5f*dI2/SQRT3;
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YY6: 
			case TransAngleClock_DD6:
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1/2; 
					dIbPh = 180.0f;
					dIc = dI1;
					dIcPh = 0.0f;

					dIap = dI2/2; 
					dIapPh = 180.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2;
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YD7: 
			case TransAngleClock_DY7: 
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1/2; 
					dIbPh = 180.0f;
					dIc = dI1;
					dIcPh = 0.0f;

					dIap = 1.5f*dI2/SQRT3;
					dIapPh = 180.0f;
					dIbp = 0.0f; 
					dIbpPh = 180.0f;
					dIcp = 1.5f*dI2/SQRT3;
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YY8: 
			case TransAngleClock_DD8: 
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1/2; 
					dIbPh = 180.0f;
					dIc = dI1;
					dIcPh = 0.0f;

					dIap = dI2;
					dIapPh = 180.0f;
					dIbp = dI2/2;
					dIbpPh = 0.0f;
					dIcp = dI2/2; 
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YD9: 
			case TransAngleClock_DY9: 
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1/2; 
					dIbPh = 180.0f;
					dIc = dI1;
					dIcPh = 0.0f;

					dIap = 1.5f*dI2/SQRT3;
					dIapPh = 180.0f;
					dIbp = 1.5f*dI2/SQRT3;
					dIbpPh = 0.0f;
					dIcp = 0.0f; 
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YY10: 
			case TransAngleClock_DD10: 
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1/2; 
					dIbPh = 180.0f;
					dIc = dI1;
					dIcPh = 0.0f;

					dIap = dI2/2;
					dIapPh = 180.0f;
					dIbp = dI2; 
					dIbpPh = 0.0f;
					dIcp = dI2/2;
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YD11: 
			case TransAngleClock_DY11:
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1/2; 
					dIbPh = 180.0f;
					dIc = dI1;
					dIcPh = 0.0f;

					dIap = 0.0f; 
					dIapPh = 0.0f;
					dIbp = 1.5f*dI2/SQRT3;
					dIbpPh = 0.0f;
					dIcp = 1.5f*dI2/SQRT3;
					dIcpPh = 180.0f;
				}
				break;
			default: 
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1/2; 
					dIbPh = 180.0f;
					dIc = dI1;
					dIcPh = 0.0f;

					dIap = dI2/2;
					dIapPh = 0.0f;
					dIbp = dI2/2; 
					dIbpPh = 0.0f;
					dIcp = dI2;
					dIcpPh = 180.0f;
				}
				break;
			}
		}
		break;

	case ABPhase: 
		{
			switch(GetTransAngleClockValue())//转角方式及钟点数
			{
			case TransAngleClock_YD1: 
			case TransAngleClock_DY1: 
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1;
					dIbPh = 180.0f;
					dIc = 0.0f; 
					dIcPh = 0.0f;
					dIap = dI2/SQRT3;
					dIapPh = 180.0f;
					dIbp = 2.0f*dI2/SQRT3;
					dIbpPh = 0.0f;
					dIcp = dI2/SQRT3; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YY2: 
			case TransAngleClock_DD2:
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1;
					dIbPh = 180.0f;
					dIc = 0.0f; 
					dIcPh = 0.0f;
					dIap = 0;
					dIapPh = 0.0f;
					dIbp = dI2;
					dIbpPh = 0.0f;
					dIcp = dI2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YD3: 
			case TransAngleClock_DY3: 
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1;
					dIbPh = 180.0f;
					dIc = 0.0f; 
					dIcPh = 0.0f;
					dIap = dI2/SQRT3; 
					dIapPh = 0.0f;
					dIbp = dI2/SQRT3;
					dIbpPh = 0.0f;
					dIcp = 2.0f*dI2/SQRT3;
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YY4: 
			case TransAngleClock_DD4: 
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1;
					dIbPh = 180.0f;
					dIc = 0.0f; 
					dIcPh = 0.0f;
					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = 0.0f;
					dIbpPh = 0.0f;
					dIcp = dI2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YD5:
			case TransAngleClock_DY5: 
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1;
					dIbPh = 180.0f;
					dIc = 0.0f; 
					dIcPh = 0.0f;
					dIap = 2.0f*dI2/SQRT3;
					dIapPh = 0.0f;
					dIbp = dI2/SQRT3; 
					dIbpPh = 180.0f;
					dIcp = dI2/SQRT3;
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YY6: 
			case TransAngleClock_DD6:
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1;
					dIbPh = 180.0f;
					dIc = 0.0f; 
					dIcPh = 0.0f;
					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2;
					dIbpPh = 180.0f;
					dIcp = 0.0f; 
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YD7: 
			case TransAngleClock_DY7: 
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1;
					dIbPh = 180.0f;
					dIc = 0.0f; 
					dIcPh = 0.0f;
					dIap = dI2/SQRT3;
					dIapPh = 0.0f;
					dIbp = 2.0f*dI2/SQRT3;
					dIbpPh = 180.0f;
					dIcp = dI2/SQRT3; 
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YY8: 
			case TransAngleClock_DD8: 
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1;
					dIbPh = 180.0f;
					dIc = 0.0f; 
					dIcPh = 0.0f;
					dIap = 0.0;
					dIapPh = 0.0f;
					dIbp = dI2;
					dIbpPh = 180.0f;
					dIcp = dI2; 
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YD9: 
			case TransAngleClock_DY9: 
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1;
					dIbPh = 180.0f;
					dIc = 0.0f; 
					dIcPh = 0.0f;
					dIap = dI2/SQRT3; 
					dIapPh = 180.0f;
					dIbp = dI2/SQRT3;
					dIbpPh = 180.0f;
					dIcp = 2.0f*dI2/SQRT3;
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YY10: 
			case TransAngleClock_DD10: 
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1;
					dIbPh = 180.0f;
					dIc = 0.0f; 
					dIcPh = 0.0f;
					dIap = dI2;
					dIapPh = 180.0f;
					dIbp = 0.0f;
					dIbpPh = 0.0f;
					dIcp = dI2; 
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YD11: 
			case TransAngleClock_DY11:
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1;
					dIbPh = 180.0f;
					dIc = 0.0f; 
					dIcPh = 0.0f;
					dIap = 2.0f*dI2/SQRT3;
					dIapPh = 180.0f;
					dIbp = dI2/SQRT3; 
					dIbpPh = 0.0f;
					dIcp = dI2/SQRT3;
					dIcpPh = 0.0f;
				}
				break;
			default: 
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1;
					dIbPh = 180.0f;
					dIc = 0.0f; 
					dIcPh = 0.0f;
					dIap = dI2;
					dIapPh = 180.0f;
					dIbp = dI2;
					dIbpPh = 0.0f;
					dIcp = 0.0f; 
					dIcpPh = 0.0f;
				}
				break;
			}
		}
		break;
	case BCPhase: 
		{
			switch(GetTransAngleClockValue())//转角方式及钟点数
			{
			case TransAngleClock_YD1: 
			case TransAngleClock_DY1: 
				{
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1;
					dIcPh = 180.0f;
					dIa = 0.0f; 
					dIaPh = 0.0f;
					dIbp = dI2/SQRT3;
					dIbpPh = 180.0f;
					dIcp = 2.0f*dI2/SQRT3;
					dIcpPh = 0.0f;
					dIap = dI2/SQRT3; 
					dIapPh = 180.0f;
				}
				break;
			case TransAngleClock_YY2: 
			case TransAngleClock_DD2:
				{
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1;
					dIcPh = 180.0f;
					dIa = 0.0f; 
					dIaPh = 0.0f;
					dIbp = 0;
					dIbpPh = 0.0f;
					dIcp = dI2;
					dIcpPh = 0.0f;
					dIap = dI2; 
					dIapPh = 180.0f;
				}
				break;
			case TransAngleClock_YD3: 
			case TransAngleClock_DY3: 
				{
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1;
					dIcPh = 180.0f;
					dIa = 0.0f; 
					dIaPh = 0.0f;
					dIbp = dI2/SQRT3; 
					dIbpPh = 0.0f;
					dIcp = dI2/SQRT3;
					dIcpPh = 0.0f;
					dIap = 2.0f*dI2/SQRT3;
					dIapPh = 180.0f;
				}
				break;
			case TransAngleClock_YY4: 
			case TransAngleClock_DD4: 
				{
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1;
					dIcPh = 180.0f;
					dIa = 0.0f; 
					dIaPh = 0.0f;
					dIbp = dI2;
					dIbpPh = 0.0f;
					dIcp = 0.0f;
					dIcpPh = 0.0f;
					dIap = dI2; 
					dIapPh = 180.0f;
				}
				break;
			case TransAngleClock_YD5:
			case TransAngleClock_DY5: 
				{
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1;
					dIcPh = 180.0f;
					dIa = 0.0f; 
					dIaPh = 0.0f;
					dIbp = 2.0f*dI2/SQRT3;
					dIbpPh = 0.0f;
					dIcp = dI2/SQRT3; 
					dIcpPh = 180.0f;
					dIap = dI2/SQRT3;
					dIapPh = 180.0f;
				}
				break;
			case TransAngleClock_YY6: 
			case TransAngleClock_DD6:
				{
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1;
					dIcPh = 180.0f;
					dIa = 0.0f; 
					dIaPh = 0.0f;
					dIbp = dI2;
					dIbpPh = 0.0f;
					dIcp = dI2;
					dIcpPh = 180.0f;
					dIap = 0.0f; 
					dIapPh = 0.0f;
				}
				break;
			case TransAngleClock_YD7: 
			case TransAngleClock_DY7: 
				{
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1;
					dIcPh = 180.0f;
					dIa = 0.0f; 
					dIaPh = 0.0f;
					dIbp = dI2/SQRT3;
					dIbpPh = 0.0f;
					dIcp = 2.0f*dI2/SQRT3;
					dIcpPh = 180.0f;
					dIap = dI2/SQRT3; 
					dIapPh = 0.0f;
				}
				break;
			case TransAngleClock_YY8: 
			case TransAngleClock_DD8: 
				{
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1;
					dIcPh = 180.0f;
					dIa = 0.0f; 
					dIaPh = 0.0f;
					dIbp = 0.0;
					dIbpPh = 0.0f;
					dIcp = dI2;
					dIcpPh = 180.0f;
					dIap = dI2; 
					dIapPh = 0.0f;
				}
				break;
			case TransAngleClock_YD9: 
			case TransAngleClock_DY9: 
				{
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1;
					dIcPh = 180.0f;
					dIa = 0.0f; 
					dIaPh = 0.0f;
					dIbp = dI2/SQRT3; 
					dIbpPh = 180.0f;
					dIcp = dI2/SQRT3;
					dIcpPh = 180.0f;
					dIap = 2.0f*dI2/SQRT3;
					dIapPh = 0.0f;
				}
				break;
			case TransAngleClock_YY10: 
			case TransAngleClock_DD10: 
				{
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1;
					dIcPh = 180.0f;
					dIa = 0.0f; 
					dIaPh = 0.0f;
					dIbp = dI2;
					dIbpPh = 180.0f;
					dIcp = 0.0f;
					dIcpPh = 0.0f;
					dIap = dI2; 
					dIapPh = 0.0f;
				}
				break;
			case TransAngleClock_YD11: 
			case TransAngleClock_DY11:
				{
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1;
					dIcPh = 180.0f;
					dIa = 0.0f; 
					dIaPh = 0.0f;
					dIbp = 2.0f*dI2/SQRT3;
					dIbpPh = 180.0f;
					dIcp = dI2/SQRT3; 
					dIcpPh = 0.0f;
					dIap = dI2/SQRT3;
					dIapPh = 0.0f;
				}
				break;
			default: 
				{
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1;
					dIcPh = 180.0f;
					dIa = 0.0f; 
					dIaPh = 0.0f;
					dIbp = dI2;
					dIbpPh = 180.0f;
					dIcp = dI2;
					dIcpPh = 0.0f;
					dIap = 0.0f; 
					dIapPh = 0.0f;
				}
				break;
			}
		}
		break;
	case CAPhase: 
		{
			switch(GetTransAngleClockValue())//转角方式及钟点数
			{
				case TransAngleClock_YD1: 
				case TransAngleClock_DY1: 
				{
					dIc = dI1;
					dIcPh = 0.0f;
					dIa = dI1;
					dIaPh = 180.0f;
					dIb = 0.0f; 
					dIbPh = 0.0f;
					dIcp = dI2/SQRT3;
					dIcpPh = 180.0f;
					dIap = 2.0f*dI2/SQRT3;
					dIapPh = 0.0f;
					dIbp = dI2/SQRT3; 
					dIbpPh = 180.0f;
				}
				break;
				case TransAngleClock_YY2: 
				case TransAngleClock_DD2:
				{
					dIc = dI1;
					dIcPh = 0.0f;
					dIa = dI1;
					dIaPh = 180.0f;
					dIb = 0.0f; 
					dIbPh = 0.0f;
					dIcp = 0;
					dIcpPh = 0.0f;
					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2; 
					dIbpPh = 180.0f;
				}
				break;
				case TransAngleClock_YD3: 
				case TransAngleClock_DY3: 
				{
					dIc = dI1;
					dIcPh = 0.0f;
					dIa = dI1;
					dIaPh = 180.0f;
					dIb = 0.0f; 
					dIbPh = 0.0f;
					dIcp = dI2/SQRT3; 
					dIcpPh = 0.0f;
					dIap = dI2/SQRT3;
					dIapPh = 0.0f;
					dIbp = 2.0f*dI2/SQRT3;
					dIbpPh = 180.0f;
				}
				break;
				case TransAngleClock_YY4: 
				case TransAngleClock_DD4: 
				{
					dIc = dI1;
					dIcPh = 0.0f;
					dIa = dI1;
					dIaPh = 180.0f;
					dIb = 0.0f; 
					dIbPh = 0.0f;
					dIcp = dI2;
					dIcpPh = 0.0f;
					dIap = 0.0f;
					dIapPh = 0.0f;
					dIbp = dI2; 
					dIbpPh = 180.0f;
				}
				break;
				case TransAngleClock_YD5:
				case TransAngleClock_DY5: 
				{
					dIc = dI1;
					dIcPh = 0.0f;
					dIa = dI1;
					dIaPh = 180.0f;
					dIb = 0.0f; 
					dIbPh = 0.0f;
					dIcp = 2.0f*dI2/SQRT3;
					dIcpPh = 0.0f;
					dIap = dI2/SQRT3; 
					dIapPh = 180.0f;
					dIbp = dI2/SQRT3;
					dIbpPh = 180.0f;
				}
				break;
				case TransAngleClock_YY6: 
				case TransAngleClock_DD6:
				{
					dIc = dI1;
					dIcPh = 0.0f;
					dIa = dI1;
					dIaPh = 180.0f;
					dIb = 0.0f; 
					dIbPh = 0.0f;
					dIcp = dI2;
					dIcpPh = 0.0f;
					dIap = dI2;
					dIapPh = 180.0f;
					dIbp = 0.0f; 
					dIbpPh = 0.0f;
				}
				break;
				case TransAngleClock_YD7: 
				case TransAngleClock_DY7: 
				{
					dIc = dI1;
					dIcPh = 0.0f;
					dIa = dI1;
					dIaPh = 180.0f;
					dIb = 0.0f; 
					dIbPh = 0.0f;
					dIcp = dI2/SQRT3;
					dIcpPh = 0.0f;
					dIap = 2.0f*dI2/SQRT3;
					dIapPh = 180.0f;
					dIbp = dI2/SQRT3; 
					dIbpPh = 0.0f;
				}
				break;
				case TransAngleClock_YY8: 
				case TransAngleClock_DD8: 
				{
					dIc = dI1;
					dIcPh = 0.0f;
					dIa = dI1;
					dIaPh = 180.0f;
					dIb = 0.0f; 
					dIbPh = 0.0f;
					dIcp = 0.0;
					dIcpPh = 0.0f;
					dIap = dI2;
					dIapPh = 180.0f;
					dIbp = dI2; 
					dIbpPh = 0.0f;
				}
				break;
				case TransAngleClock_YD9: 
				case TransAngleClock_DY9: 
				{
					dIc = dI1;
					dIcPh = 0.0f;
					dIa = dI1;
					dIaPh = 180.0f;
					dIb = 0.0f; 
					dIbPh = 0.0f;
					dIcp = dI2/SQRT3; 
					dIcpPh = 180.0f;
					dIap = dI2/SQRT3;
					dIapPh = 180.0f;
					dIbp = 2.0f*dI2/SQRT3;
					dIbpPh = 0.0f;
				}
				break;
				case TransAngleClock_YY10: 
				case TransAngleClock_DD10: 
				{
					dIc = dI1;
					dIcPh = 0.0f;
					dIa = dI1;
					dIaPh = 180.0f;
					dIb = 0.0f; 
					dIbPh = 0.0f;
					dIcp = dI2;
					dIcpPh = 180.0f;
					dIap = 0.0f;
					dIapPh = 0.0f;
					dIbp = dI2; 
					dIbpPh = 0.0f;
				}
				break;
				case TransAngleClock_YD11: 
				case TransAngleClock_DY11:
				{
					dIc = dI1;
					dIcPh = 0.0f;
					dIa = dI1;
					dIaPh = 180.0f;
					dIb = 0.0f; 
					dIbPh = 0.0f;
					dIcp = 2.0f*dI2/SQRT3;
					dIcpPh = 180.0f;
					dIap = dI2/SQRT3; 
					dIapPh = 0.0f;
					dIbp = dI2/SQRT3;
					dIbpPh = 0.0f;
				}
				break;
			default: 
			{
				dIc = dI1;
				dIcPh = 0.0f;
				dIa = dI1;
				dIaPh = 180.0f;
				dIb = 0.0f; 
				dIbPh = 0.0f;
				dIcp = dI2;
				dIcpPh = 180.0f;
				dIap = dI2;
				dIapPh = 0.0f;
				dIbp = 0.0f; 
				dIbpPh = 0.0f;
			}
			break;
			}
		}
		break;
	default:
		break;
			
	}
}

void CSttDiffCurrCalculatTool::CurrentCal_ByI1I2_YTrans(double dI1,double dI2,double &dIa,double &dIaPh,double &dIb,double &dIbPh,double &dIc,double &dIcPh,
							  double &dIap,double &dIapPh,double &dIbp,double &dIbpPh,double &dIcp,double &dIcpPh)
{
	switch(m_nPhase)//故障相别
	{
	case APhase: 
		{
			switch(GetTransAngleClockValue())//转角方式及钟点数
			{
			case TransAngleClock_YD1: 
			case TransAngleClock_DY1: 
				{
					dIa = 1.5f*dI1/SQRT3;
					dIaPh = 180.0f;
					dIb = 0.0f; 
					dIbPh = 0.0f;
					dIc = 1.5f*dI1/SQRT3;
					dIcPh = 0.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YY2: 
			case TransAngleClock_DD2:
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1/2;
					dIbPh = 180.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;

					dIap = dI2/2;
					dIapPh = 180.0f;
					dIbp = dI2;
					dIbpPh = 0.0f;
					dIcp = dI2/2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YD3: 
			case TransAngleClock_DY3: 
				{
					dIa = 1.5f*dI1/SQRT3;
					dIaPh = 0.0f;
					dIb = 0.0f; 
					dIbPh = 0.0f;
					dIc = 1.5f*dI1/SQRT3;
					dIcPh = 180.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YY4: 
			case TransAngleClock_DD4: 
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1/2;
					dIbPh = 180.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;

					dIap = dI2/2;
					dIapPh = 0.0f;
					dIbp = dI2/2;
					dIbpPh = 0.0f;
					dIcp = dI2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YD5:
			case TransAngleClock_DY5: 
				{
					dIa = 1.5f*dI1/SQRT3;
					dIaPh = 0.0f;
					dIb = 1.5f*dI1/SQRT3;
					dIbPh = 180.0f;
					dIc = 0.0f; 
					dIcPh = 180.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YY6: 
			case TransAngleClock_DD6:
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1/2;
					dIbPh = 180.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YD7: 
			case TransAngleClock_DY7: 
				{
					dIa = 1.5f*dI1/SQRT3;
					dIaPh = 0.0f;
					dIb = 0.0f; 
					dIbPh = 180.0f;
					dIc = 1.5f*dI1/SQRT3;
					dIcPh = 180.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YY8: 
			case TransAngleClock_DD8: 
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1/2;
					dIbPh = 180.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;

					dIap = dI2/2;
					dIapPh = 0.0f;
					dIbp = dI2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YD9: 
			case TransAngleClock_DY9: 
				{
					dIa = 1.5f*dI1/SQRT3;
					dIaPh = 180.0f;
					dIb = 0.0f; 
					dIbPh = 0.0f;
					dIc = 1.5f*dI1/SQRT3;
					dIcPh = 0.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YY10: 
			case TransAngleClock_DD10: 
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1/2;
					dIbPh = 180.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;

					dIap = dI2/2;
					dIapPh = 180.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2; 
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YD11: 
			case TransAngleClock_DY11:
				{
					dIa = 1.5f*dI1/SQRT3;
					dIaPh = 180.0f;
					dIb = 1.5f*dI1/SQRT3;
					dIbPh = 0.0f;
					dIc = 0.0f; 
					dIcPh = 0.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 180.0f;
				}
				break;
			default: 
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1/2;
					dIbPh = 180.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;

					dIap = dI2;
					dIapPh = 180.0f;
					dIbp = dI2/2;
					dIbpPh = 0.0f;
					dIcp = dI2/2; 
					dIcpPh = 0.0f;
				}
				break;
			}
		}
		break;
	case BPhase: 
		{
			switch(GetTransAngleClockValue())//转角方式及钟点数
			{
			case TransAngleClock_YD1: 
			case TransAngleClock_DY1: 
				{
					dIa = 1.5f*dI1/SQRT3;
					dIaPh = 0.0f;
					dIb = 1.5f*dI1/SQRT3;
					dIbPh = 180.0f;
					dIc = 0.0f; 
					dIcPh = 0.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YY2: 
			case TransAngleClock_DD2:
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;

					dIap = dI2/2;
					dIapPh = 180.0f;
					dIbp = dI2/2; 
					dIbpPh = 180.0f;
					dIcp = dI2;
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YD3: 
			case TransAngleClock_DY3: 
				{
					dIa = 1.5f*dI1/SQRT3;
					dIaPh = 180.0f;
					dIb = 1.5f*dI1/SQRT3;
					dIbPh = 0.0f;
					dIc = 0.0f; 
					dIcPh = 0.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YY4: 
			case TransAngleClock_DD4: 
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;

					dIap = dI2; 
					dIapPh = 180.0f;
					dIbp = dI2/2;
					dIbpPh = 0.0f;
					dIcp = dI2/2;
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YD5:
			case TransAngleClock_DY5: 
				{
					dIa = 0.0f; 
					dIaPh = 180.0f;
					dIb = 1.5f*dI1/SQRT3;
					dIbPh = 0.0f;
					dIc = 1.5f*dI1/SQRT3;
					dIcPh = 180.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YY6: 
			case TransAngleClock_DD6:
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = dI2/2;
					dIapPh = 180.0f;
					dIbp = dI2;
					dIbpPh = 0.0f;
					dIcp = dI2/2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YD7: 
			case TransAngleClock_DY7: 
				{
					dIa = 1.5f*dI1/SQRT3;
					dIaPh = 180.0f;
					dIb = 1.5f*dI1/SQRT3;
					dIbPh = 0.0f;
					dIc = 0.0f; 
					dIcPh = 180.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YY8: 
			case TransAngleClock_DD8: 
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;
					dIap = dI2/2;
					dIapPh = 0.0f;
					dIbp = dI2/2; 
					dIbpPh = 0.0f;
					dIcp = dI2;
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YD9: 
			case TransAngleClock_DY9: 
				{
					dIa = 1.5f*dI1/SQRT3;
					dIaPh = 0.0f;
					dIb = 1.5f*dI1/SQRT3;
					dIbPh = 180.0f;
					dIc = 0.0f; 
					dIcPh = 0.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YY10: 
			case TransAngleClock_DD10: 
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;

					dIap = dI2; 
					dIapPh = 0.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2/2;
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YD11: 
			case TransAngleClock_DY11:
				{
					dIa = 0.0f; 
					dIaPh = 0.0f;
					dIb = 1.5f*dI1/SQRT3;
					dIbPh = 180.0f;
					dIc = 1.5f*dI1/SQRT3;
					dIcPh = 0.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 180.0f;
				}
				break;
			default: 
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1/2; 
					dIcPh = 180.0f;

					dIap = dI2/2;
					dIapPh = 0.0f;
					dIbp = dI2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 0.0f;
				}
				break;
			}
		}
		break;
	case CPhase: 
		{
			switch(GetTransAngleClockValue())//转角方式及钟点数
			{
			case TransAngleClock_YD1: 
			case TransAngleClock_DY1: 
				{
					dIa = 0.0f; 
					dIaPh = 0.0f;
					dIb = 1.5f*dI1/SQRT3;
					dIbPh = 0.0f;
					dIc = 1.5f*dI1/SQRT3;
					dIcPh = 180.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YY2: 
			case TransAngleClock_DD2:
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1/2; 
					dIbPh = 180.0f;
					dIc = dI1;
					dIcPh = 0.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YD3: 
			case TransAngleClock_DY3: 
				{
					dIa = 0.0f; 
					dIaPh = 0.0f;
					dIb = 1.5f*dI1/SQRT3;
					dIbPh = 180.0f;
					dIc = 1.5f*dI1/SQRT3;
					dIcPh = 0.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YY4: 
			case TransAngleClock_DD4: 
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1/2; 
					dIbPh = 180.0f;
					dIc = dI1;
					dIcPh = 0.0f;

					dIap = dI2/2;
					dIapPh = 0.0f;
					dIbp = dI2; 
					dIbpPh = 180.0f;
					dIcp = dI2/2;
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YD5:
			case TransAngleClock_DY5: 
				{
					dIa = 1.5f*dI1/SQRT3;
					dIaPh = 180.0f;
					dIb = 0.0f; 
					dIbPh = 180.0f;
					dIc = 1.5f*dI1/SQRT3;
					dIcPh = 0.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YY6: 
			case TransAngleClock_DD6:
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1/2; 
					dIbPh = 180.0f;
					dIc = dI1;
					dIcPh = 0.0f;

					dIap = dI2/2; 
					dIapPh = 180.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2;
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YD7: 
			case TransAngleClock_DY7: 
				{
					dIa = 0.0f; 
					dIaPh = 180.0f;
					dIb = 1.5f*dI1/SQRT3;
					dIbPh = 180.0f;
					dIc = 1.5f*dI1/SQRT3;
					dIcPh = 0.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YY8: 
			case TransAngleClock_DD8: 
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1/2; 
					dIbPh = 180.0f;
					dIc = dI1;
					dIcPh = 0.0f;

					dIap = dI2;
					dIapPh = 180.0f;
					dIbp = dI2/2;
					dIbpPh = 0.0f;
					dIcp = dI2/2; 
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YD9: 
			case TransAngleClock_DY9: 
				{
					dIa = 0.0f; 
					dIaPh = 0.0f;
					dIb = 1.5f*dI1/SQRT3;
					dIbPh = 0.0f;
					dIc = 1.5f*dI1/SQRT3;
					dIcPh = 180.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YY10: 
			case TransAngleClock_DD10: 
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1/2; 
					dIbPh = 180.0f;
					dIc = dI1;
					dIcPh = 0.0f;

					dIap = dI2/2;
					dIapPh = 180.0f;
					dIbp = dI2; 
					dIbpPh = 0.0f;
					dIcp = dI2/2;
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YD11: 
			case TransAngleClock_DY11:
				{
					dIa = 1.5f*dI1/SQRT3;
					dIaPh = 0.0f;
					dIb = 0.0f; 
					dIbPh = 0.0f;
					dIc = 1.5f*dI1/SQRT3;
					dIcPh = 180.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2/2;
					dIbpPh = 180.0f;
					dIcp = dI2/2; 
					dIcpPh = 180.0f;
				}
				break;
			default: 
				{
					dIa = dI1/2;
					dIaPh = 180.0f;
					dIb = dI1/2; 
					dIbPh = 180.0f;
					dIc = dI1;
					dIcPh = 0.0f;

					dIap = dI2/2;
					dIapPh = 0.0f;
					dIbp = dI2/2; 
					dIbpPh = 0.0f;
					dIcp = dI2;
					dIcpPh = 180.0f;
				}
				break;
			}
		}
		break;
	case ABPhase: 
		{
			switch(GetTransAngleClockValue())//转角方式及钟点数
			{
			case TransAngleClock_YD1: 
			case TransAngleClock_DY1: 
				{
					dIa = 2.0f*dI1/SQRT3;
					dIaPh = 180.0f;
					dIb = dI1/SQRT3; 
					dIbPh = 0.0f;
					dIc = dI1/SQRT3;
					dIcPh = 0.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2;
					dIbpPh = 180.0f;
					dIcp = 0.0f; 
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YY2: 
			case TransAngleClock_DD2:
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1;
					dIbPh = 180.0f;
					dIc = 0.0f; 
					dIcPh = 0.0f;

					dIap = 0.0f;
					dIapPh = 0.0f;
					dIbp = dI2;
					dIbpPh = 0.0f;
					dIcp = dI2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YD3: 
			case TransAngleClock_DY3: 
				{
					dIa = 2.0f*dI1/SQRT3;
					dIaPh = 0.0f;
					dIb = dI1/SQRT3; 
					dIbPh = 180.0f;
					dIc = dI1/SQRT3;
					dIcPh = 180.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2;
					dIbpPh = 180.0f;
					dIcp = 0.0f; 
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YY4: 
			case TransAngleClock_DD4: 
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1;
					dIbPh = 180.0f;
					dIc = 0.0f; 
					dIcPh = 0.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = 0.0f;
					dIbpPh = 0.0f;
					dIcp = dI2; 
					dIcpPh = 180.0f;
				}
				break;
			case TransAngleClock_YD5:
			case TransAngleClock_DY5: 
				{
					dIa = dI1/SQRT3;
					dIaPh = 0.0f;
					dIb = 2.0f*dI1/SQRT3; 
					dIbPh = 180.0f;
					dIc = dI1/SQRT3;
					dIcPh = 0.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2;
					dIbpPh = 180.0f;
					dIcp = 0.0f; 
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YY6: 
			case TransAngleClock_DD6:
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1;
					dIbPh = 180.0f;
					dIc = 0.0f; 
					dIcPh = 0.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2;
					dIbpPh = 180.0f;
					dIcp = 0.0f; 
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YD7: 
			case TransAngleClock_DY7: 
				{
					dIa = 2.0f*dI1/SQRT3;
					dIaPh = 0.0f;
					dIb = dI1/SQRT3; 
					dIbPh = 180.0f;
					dIc = dI1/SQRT3;
					dIcPh = 180.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2;
					dIbpPh = 180.0f;
					dIcp = 0.0f; 
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YY8: 
			case TransAngleClock_DD8: 
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1;
					dIbPh = 180.0f;
					dIc = 0.0f; 
					dIcPh = 0.0f;

					dIap = 0.0f;
					dIapPh = 0.0f;
					dIbp = dI2;
					dIbpPh = 180.0f;
					dIcp = dI2; 
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YD9: 
			case TransAngleClock_DY9: 
				{
					dIa = 2.0f*dI1/SQRT3;
					dIaPh = 180.0f;
					dIb = dI1/SQRT3; 
					dIbPh = 0.0f;
					dIc = dI1/SQRT3;
					dIcPh = 0.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2;
					dIbpPh = 180.0f;
					dIcp = 0.0f; 
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YY10: 
			case TransAngleClock_DD10: 
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1;
					dIbPh = 180.0f;
					dIc = 0.0f; 
					dIcPh = 0.0f;

					dIap = dI2;
					dIapPh = 180.0f;
					dIbp = 0.0f;
					dIbpPh = 0.0f;
					dIcp = dI2; 
					dIcpPh = 0.0f;
				}
				break;
			case TransAngleClock_YD11: 
			case TransAngleClock_DY11:
				{
					dIa = dI1/SQRT3;
					dIaPh = 180.0f;
					dIb = 2.0f*dI1/SQRT3; 
					dIbPh = 0.0f;
					dIc = dI1/SQRT3;
					dIcPh = 180.0f;

					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2;
					dIbpPh = 180.0f;
					dIcp = 0.0f; 
					dIcpPh = 0.0f;
				}
				break;
			default: 
				{
					dIa = dI1;
					dIaPh = 0.0f;
					dIb = dI1;
					dIbPh = 180.0f;
					dIc = 0.0f; 
					dIcPh = 0.0f;

					dIap = dI2;
					dIapPh = 180.0f;
					dIbp = dI2;
					dIbpPh = 0.0f;
					dIcp = 0.0f; 
					dIcpPh = 0.0f;
				}
				break;
			}
		}
		break;
	case BCPhase: 
		{
			switch(GetTransAngleClockValue())//转角方式及钟点数
			{
			case TransAngleClock_YD1: 
			case TransAngleClock_DY1: 
				{
					dIb = 2.0f*dI1/SQRT3;
					dIbPh = 180.0f;
					dIc = dI1/SQRT3; 
					dIcPh = 0.0f;
					dIa = dI1/SQRT3;
					dIaPh = 0.0f;

					dIbp = dI2;
					dIbpPh = 0.0f;
					dIcp = dI2;
					dIcpPh = 180.0f;
					dIap = 0.0f; 
					dIapPh = 0.0f;
				}
				break;
			case TransAngleClock_YY2: 
			case TransAngleClock_DD2:
				{
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1;
					dIcPh = 180.0f;
					dIa = 0.0f; 
					dIaPh = 0.0f;

					dIbp = 0.0f;
					dIbpPh = 0.0f;
					dIcp = dI2;
					dIcpPh = 0.0f;
					dIap = dI2; 
					dIapPh = 180.0f;
				}
				break;
			case TransAngleClock_YD3: 
			case TransAngleClock_DY3: 
				{
					dIb = 2.0f*dI1/SQRT3;
					dIbPh = 0.0f;
					dIc = dI1/SQRT3; 
					dIcPh = 180.0f;
					dIa = dI1/SQRT3;
					dIaPh = 180.0f;

					dIbp = dI2;
					dIbpPh = 0.0f;
					dIcp = dI2;
					dIcpPh = 180.0f;
					dIap = 0.0f; 
					dIapPh = 0.0f;
				}
				break;
			case TransAngleClock_YY4: 
			case TransAngleClock_DD4: 
				{
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1;
					dIcPh = 180.0f;
					dIa = 0.0f; 
					dIaPh = 0.0f;

					dIbp = dI2;
					dIbpPh = 0.0f;
					dIcp = 0.0f;
					dIcpPh = 0.0f;
					dIap = dI2; 
					dIapPh = 180.0f;
				}
				break;
			case TransAngleClock_YD5:
			case TransAngleClock_DY5: 
				{
					dIb = dI1/SQRT3;
					dIbPh = 0.0f;
					dIc = 2.0f*dI1/SQRT3; 
					dIcPh = 180.0f;
					dIa = dI1/SQRT3;
					dIaPh = 0.0f;

					dIbp = dI2;
					dIbpPh = 0.0f;
					dIcp = dI2;
					dIcpPh = 180.0f;
					dIap = 0.0f; 
					dIapPh = 0.0f;
				}
				break;
			case TransAngleClock_YY6: 
			case TransAngleClock_DD6:
				{
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1;
					dIcPh = 180.0f;
					dIa = 0.0f; 
					dIaPh = 0.0f;

					dIbp = dI2;
					dIbpPh = 0.0f;
					dIcp = dI2;
					dIcpPh = 180.0f;
					dIap = 0.0f; 
					dIapPh = 0.0f;
				}
				break;
			case TransAngleClock_YD7: 
			case TransAngleClock_DY7: 
				{
					dIb = 2.0f*dI1/SQRT3;
					dIbPh = 0.0f;
					dIc = dI1/SQRT3; 
					dIcPh = 180.0f;
					dIa = dI1/SQRT3;
					dIaPh = 180.0f;

					dIbp = dI2;
					dIbpPh = 0.0f;
					dIcp = dI2;
					dIcpPh = 180.0f;
					dIap = 0.0f; 
					dIapPh = 0.0f;
				}
				break;
			case TransAngleClock_YY8: 
			case TransAngleClock_DD8: 
				{
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1;
					dIcPh = 180.0f;
					dIa = 0.0f; 
					dIaPh = 0.0f;

					dIbp = 0.0f;
					dIbpPh = 0.0f;
					dIcp = dI2;
					dIcpPh = 180.0f;
					dIap = dI2; 
					dIapPh = 0.0f;
				}
				break;
			case TransAngleClock_YD9: 
			case TransAngleClock_DY9: 
				{
					dIb = 2.0f*dI1/SQRT3;
					dIbPh = 180.0f;
					dIc = dI1/SQRT3; 
					dIcPh = 0.0f;
					dIa = dI1/SQRT3;
					dIaPh = 0.0f;

					dIbp = dI2;
					dIbpPh = 0.0f;
					dIcp = dI2;
					dIcpPh = 180.0f;
					dIap = 0.0f; 
					dIapPh = 0.0f;
				}
				break;
			case TransAngleClock_YY10: 
			case TransAngleClock_DD10: 
				{
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1;
					dIcPh = 180.0f;
					dIa = 0.0f; 
					dIaPh = 0.0f;

					dIbp = dI2;
					dIbpPh = 180.0f;
					dIcp = 0.0f;
					dIcpPh = 0.0f;
					dIap = dI2; 
					dIapPh = 0.0f;
				}
				break;
			case TransAngleClock_YD11: 
			case TransAngleClock_DY11:
				{
					dIb = dI1/SQRT3;
					dIbPh = 180.0f;
					dIc = 2.0f*dI1/SQRT3; 
					dIcPh = 0.0f;
					dIa = dI1/SQRT3;
					dIaPh = 180.0f;

					dIbp = dI2;
					dIbpPh = 0.0f;
					dIcp = dI2;
					dIcpPh = 180.0f;
					dIap = 0.0f; 
					dIapPh = 0.0f;
				}
				break;
			default: 
				{
					dIb = dI1;
					dIbPh = 0.0f;
					dIc = dI1;
					dIcPh = 180.0f;
					dIa = 0.0f; 
					dIaPh = 0.0f;

					dIbp = dI2;
					dIbpPh = 180.0f;
					dIcp = dI2;
					dIcpPh = 0.0f;
					dIap = 0.0f; 
					dIapPh = 0.0f;
				}
				break;
			}
		}
		break;
	case CAPhase: 
		{
			switch(GetTransAngleClockValue())//转角方式及钟点数
			{
			case TransAngleClock_YD1: 
			case TransAngleClock_DY1: 
				{
					dIc = 2.0f*dI1/SQRT3;
					dIcPh = 180.0f;
					dIa = dI1/SQRT3; 
					dIaPh = 0.0f;
					dIb = dI1/SQRT3;
					dIbPh = 0.0f;

					dIcp = dI2;
					dIcpPh = 0.0f;
					dIap = dI2;
					dIapPh = 180.0f;
					dIbp = 0.0f; 
					dIbpPh = 0.0f;
				}
				break;
			case TransAngleClock_YY2: 
			case TransAngleClock_DD2:
				{
					dIc = dI1;
					dIcPh = 0.0f;
					dIa = dI1;
					dIaPh = 180.0f;
					dIb = 0.0f; 
					dIbPh = 0.0f;

					dIcp = 0.0f;
					dIcpPh = 0.0f;
					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = dI2; 
					dIbpPh = 180.0f;
				}
				break;
			case TransAngleClock_YD3: 
			case TransAngleClock_DY3: 
				{
					dIc = 2.0f*dI1/SQRT3;
					dIcPh = 0.0f;
					dIa = dI1/SQRT3; 
					dIaPh = 180.0f;
					dIb = dI1/SQRT3;
					dIbPh = 180.0f;

					dIcp = dI2;
					dIcpPh = 0.0f;
					dIap = dI2;
					dIapPh = 180.0f;
					dIbp = 0.0f; 
					dIbpPh = 0.0f;
				}
				break;
			case TransAngleClock_YY4: 
			case TransAngleClock_DD4: 
				{
					dIc = dI1;
					dIcPh = 0.0f;
					dIa = dI1;
					dIaPh = 180.0f;
					dIb = 0.0f; 
					dIbPh = 0.0f;

					dIcp = dI2;
					dIcpPh = 0.0f;
					dIap = 0.0f;
					dIapPh = 0.0f;
					dIbp = dI2; 
					dIbpPh = 180.0f;
				}
				break;
			case TransAngleClock_YD5:
			case TransAngleClock_DY5: 
				{
					dIc = dI1/SQRT3;
					dIcPh = 0.0f;
					dIa = 2.0f*dI1/SQRT3; 
					dIaPh = 180.0f;
					dIb = dI1/SQRT3;
					dIbPh = 0.0f;

					dIcp = dI2;
					dIcpPh = 0.0f;
					dIap = dI2;
					dIapPh = 180.0f;
					dIbp = 0.0f; 
					dIbpPh = 0.0f;
				}
				break;
			case TransAngleClock_YY6: 
			case TransAngleClock_DD6:
				{
					dIc = dI1;
					dIcPh = 0.0f;
					dIa = dI1;
					dIaPh = 180.0f;
					dIb = 0.0f; 
					dIbPh = 0.0f;

					dIcp = dI2;
					dIcpPh = 0.0f;
					dIap = dI2;
					dIapPh = 180.0f;
					dIbp = 0.0f; 
					dIbpPh = 0.0f;
				}
				break;
			case TransAngleClock_YD7: 
			case TransAngleClock_DY7: 
				{
					dIc = 2.0f*dI1/SQRT3;
					dIcPh = 0.0f;
					dIa = dI1/SQRT3; 
					dIaPh = 180.0f;
					dIb = dI1/SQRT3;
					dIbPh = 180.0f;

					dIcp = dI2;
					dIcpPh = 0.0f;
					dIap = dI2;
					dIapPh = 180.0f;
					dIbp = 0.0f; 
					dIbpPh = 0.0f;
				}
				break;
			case TransAngleClock_YY8: 
			case TransAngleClock_DD8: 
				{
					dIc = dI1;
					dIcPh = 0.0f;
					dIa = dI1;
					dIaPh = 180.0f;
					dIb = 0.0f; 
					dIbPh = 0.0f;

					dIcp = 0.0f;
					dIcpPh = 0.0f;
					dIap = dI2;
					dIapPh = 180.0f;
					dIbp = dI2; 
					dIbpPh = 0.0f;
				}
				break;
			case TransAngleClock_YD9: 
			case TransAngleClock_DY9: 
				{
					dIc = 2.0f*dI1/SQRT3;
					dIcPh = 180.0f;
					dIa = dI1/SQRT3; 
					dIaPh = 0.0f;
					dIb = dI1/SQRT3;
					dIbPh = 0.0f;

					dIcp = dI2;
					dIcpPh = 0.0f;
					dIap = dI2;
					dIapPh = 180.0f;
					dIbp = 0.0f; 
					dIbpPh = 0.0f;
				}
				break;
			case TransAngleClock_YY10: 
			case TransAngleClock_DD10: 
				{
					dIc = dI1;
					dIcPh = 0.0f;
					dIa = dI1;
					dIaPh = 180.0f;
					dIb = 0.0f; 
					dIbPh = 0.0f;

					dIcp = dI2;
					dIcpPh = 180.0f;
					dIap = 0.0f;
					dIapPh = 0.0f;
					dIbp = dI2; 
					dIbpPh = 0.0f;
				}
				break;
			case TransAngleClock_YD11: 
			case TransAngleClock_DY11:
				{
					dIc = dI1/SQRT3;
					dIcPh = 180.0f;
					dIa = 2.0f*dI1/SQRT3; 
					dIaPh = 0.0f;
					dIb = dI1/SQRT3;
					dIbPh = 180.0f;

					dIcp = dI2;
					dIcpPh = 0.0f;
					dIap = dI2;
					dIapPh = 180.0f;
					dIbp = 0.0f; 
					dIbpPh = 0.0f;
				}
				break;
				default: 
				{
					dIc = dI1;
					dIcPh = 0.0f;
					dIa = dI1;
					dIaPh = 180.0f;
					dIb = 0.0f; 
					dIbPh = 0.0f;

					dIcp = dI2;
					dIcpPh = 180.0f;
					dIap = dI2;
					dIapPh = 0.0f;
					dIbp = 0.0f; 
					dIbpPh = 0.0f;
				}
				break;
			}
		}
		break;
	default:
		break;
	}
}

/***********************************************************/
//  计算转角
/***********************************************************/

int CSttDiffCurrCalculatTool::GetMethod(int nClock,int nAngleMode)
{	
	if(nAngleMode<1)
		return 0;

	if(nAngleMode==1)
		return nMethod2[nClock];

	if(nAngleMode==2)
		return nMethod1[nClock];

	return 0;
}

int CSttDiffCurrCalculatTool::GetSign(int nClock,int nAngleMode)
{
	if(nAngleMode<1)
		return 1;

	if(nAngleMode==1)
		return nSignMethod1[nClock];

	if(nAngleMode==2)
		return nSignMethod2[nClock];

	return 1;
}

/***********************************************************/
//  计算接线系数
/***********************************************************/

void CSttDiffCurrCalculatTool::CalKjx()
{
	if(m_nJXFactor==1)
	{
		m_fKjxl=1.0;
		m_fKjxh=1.0;
	}
	else
	{
		switch(m_nAngleMode)
		{
		case 0:
			{
				m_fKjxl=1.0;
				m_fKjxh=1.0;
			}
			break;
		case 1:
			switch(m_nWindSide)
			{
			case 0:
				{
					if(m_nWindH==0)
						m_fKjxh=1.0;

					if(m_nWindH==1)
						m_fKjxh=SQRT_3;

					if(m_nWindL==0)
						m_fKjxl=1.0;

					if(m_nWindL==1)
						m_fKjxl=SQRT_3;
				}
				break;
			case 1:
				{
					if(m_nWindH==0)
						m_fKjxh=1.0;

					if(m_nWindH==1)
						m_fKjxh=SQRT_3;

					if(m_nWindM==0)
						m_fKjxl=1.0;

					if(m_nWindM==1)
						m_fKjxl=SQRT_3;
				}
				break;
			case 2:
				{
					if(m_nWindM==0)
						m_fKjxh=1.0;
					if(m_nWindM==1)
						m_fKjxh=SQRT_3;

					if(m_nWindL==0)
						m_fKjxl=1.0;
					if(m_nWindL==1)
						m_fKjxl=SQRT_3;
				}
				break;
			}
			break;
		case 2:
			switch(m_nWindSide)
			{
			case 0:
				{
					if(m_nWindH==0)
						m_fKjxh=SQRT_3;

					if(m_nWindH==1)
						m_fKjxh=1;

					if(m_nWindL==0)
						m_fKjxl=SQRT_3;

					if(m_nWindL==1)
						m_fKjxl=1.0;
				}
				break;
			case 1:
				{
					if(m_nWindH==0)
						m_fKjxh=SQRT_3;

					if(m_nWindH==1)
						m_fKjxh=1;

					if(m_nWindM==0)
						m_fKjxl=SQRT_3;
					if(m_nWindM==1)
						m_fKjxl=1.0;
				}
				break;
			case 2:
				{
					if(m_nWindM==0)
						m_fKjxh=SQRT_3;

					if(m_nWindM==1)
						m_fKjxh=1.0;

					if(m_nWindL==0)
						m_fKjxl=SQRT_3;

					if(m_nWindL==1)
						m_fKjxl=1.0;
				}
				break;
			}
			break;
		}
	}

	float fIet=1.0000;
	if(m_bMinAxis)//标幺值
	{
		if(m_nInSel == HighSideSecondaryCurrent || m_nInSel == AllSideCurrent)//yyj 待确定 20211031
		{
			//基准电流选择
			fIet=m_fSn*1000/(SQRT_3*m_fUh*(m_fCTPh/m_fCTSh));
		}
		else
		{
			fIet = m_fIbase;
		}
	}

	m_fIet = fIet;
}

bool CSttDiffCurrCalculatTool::CurrentCal_SP_D(float &fIa,float &fIaPh,float &fIb,float &fIbPh,float &fIc,float &fIcPh
										  ,float &fIap,float &fIapPh,float &fIbp,float &fIbpPh,float &fIcp,float &fIcpPh, bool bSame)
{
	int nClock = 0;
	float fI1=fIa, fI2=fIap;
	fIa = fI1;
	fIaPh = 0;
	fIb = fIc = fI1/2;
	fIbPh = fIcPh = 180;

	if (!bSame)
	{
		float fI2Coef = (float)(1.5*fI2/SQRT_3);
		nClock = 2*(m_nConnectMode/2)+1;

		switch (nClock)
		{
		case 11:
			{
				fIap = fI2Coef;
				fIapPh = 180;
				fIbp = 0;
				fIbpPh = 0;
				fIcp = fI2Coef;
				fIcpPh = 0;
			}
			break;
		case 1:
			{
				fIap = fI2Coef;
				fIapPh = 180;
				fIbp = fI2Coef;
				fIbpPh = 0;
				fIcp = 0;
				fIcpPh = 0;
			}
			break;
		case 3:
			{
				fIap = 0;
				fIapPh = 0;
				fIbp = fI2Coef;
				fIbpPh = 0;
				fIcp = fI2Coef;
				fIcpPh = 180;
			}
			break;
		case 5:
			{
				fIap = fI2Coef;
				fIapPh = 0;
				fIbp = 0;
				fIbpPh = 0;
				fIcp = fI2Coef;
				fIcpPh = 180;
			}
			break;
		case 7:
			{
				fIap = fI2Coef;
				fIapPh = 0;
				fIbp = fI2Coef;
				fIbpPh = 180;
				fIcp = 0;
				fIcpPh = 0;
			}
			break;
		case 9:
			{
				fIap = 0;
				fIapPh = 0;
				fIbp = fI2Coef;
				fIbpPh = 180;
				fIcp = fI2Coef;
				fIcpPh = 0;
			}
			break;
		}
	}
	else
	{
		float fI2Coef = fI2/2;
		nClock = 2*(m_nConnectMode/2);

		switch (nClock)
		{
		case 0:
			{
				fIap = fI2;
				fIapPh = 180;
				fIbp = fI2Coef;
				fIbpPh = 0;
				fIcp = fI2Coef;
				fIcpPh = 0;
			}
			break;
		case 2:
			{
				fIap = fI2Coef;
				fIapPh = 180;
				fIbp = fI2;
				fIbpPh = 0;
				fIcp = fI2Coef;
				fIcpPh = 180;
			}
			break;
		case 4:
			{
				fIap = fI2Coef;
				fIapPh = 0;
				fIbp = fI2Coef;
				fIbpPh = 0;
				fIcp = fI2;
				fIcpPh = 180;
			}
			break;
		case 6:
			{
				fIap = fI2;
				fIapPh = 0;
				fIbp = fI2Coef;
				fIbpPh = 180;
				fIcp = fI2Coef;
				fIcpPh = 180;
			}
			break;
		case 8:
			{
				fIap = fI2Coef;
				fIapPh = 0;
				fIbp = fI2;
				fIbpPh = 180;
				fIcp = fI2Coef;
				fIcpPh = 0;
			}
			break;
		case 10:
			{
				fIap = fI2Coef;
				fIapPh = 180;
				fIbp = fI2Coef;
				fIbpPh = 180;
				fIcp = fI2;
				fIcpPh = 0;
			}
			break;
		}
	}

	return true;
}

bool CSttDiffCurrCalculatTool::CurrentCal_SP_Y(float &fIa,float &fIaPh,float &fIb,float &fIbPh,float &fIc,float &fIcPh
										  ,float &fIap,float &fIapPh,float &fIbp,float &fIbpPh,float &fIcp,float &fIcpPh, bool bSame)
{
	int nClock = 0;
	float fI1=fIa, fI2=fIap;

	if (!bSame)
	{
		fIap = fI2;
		fIapPh = 0;
		fIbp = fI2;
		fIbpPh = 180;
		fIcp = fI2;
		fIcpPh = 180;
		float fI1Coef = (float)(1.5*fI1/SQRT_3);
		nClock = 2*(m_nConnectMode/2)+1;

		switch (nClock)
		{
		case 11:
			{
				fIa = fI1Coef;
				fIaPh = 180;
				fIb = fI1Coef;
				fIbPh = 0;
				fIc = 0;
				fIcPh = 0;
			}
			break;
		case 1:
			{
				fIa = fI1Coef;
				fIaPh = 180;
				fIb = 0;
				fIbPh = 0;
				fIc = fI1Coef;
				fIcPh = 0;
			}
			break;
		case 3:
			{
				fIa = fI1Coef;
				fIaPh = 0;
				fIb = 0;
				fIbPh = 0;
				fIc = fI1Coef;
				fIcPh = 180;
			}
			break;
		case 5:
			{
				fIa = fI1Coef;
				fIaPh = 0;
				fIb = fI1Coef;
				fIbPh = 180;
				fIc = 0;
				fIcPh = 0;
			}
			break;
		case 7:
			{
				fIa = fI1Coef;
				fIaPh = 0;
				fIb = 0;
				fIbPh = 0;
				fIc = fI1Coef;
				fIcPh = 180;
			}
			break;
		case 9:
			{
				fIa = fI1Coef;
				fIaPh = 180;
				fIb = 0;
				fIbPh = 0;
				fIc = fI1Coef;
				fIcPh = 0;
			}
			break;
		}
	}
	else
	{
		fIa = fI1;
		fIaPh = 0;
		fIb = fI1/2;
		fIbPh = 180;
		fIc = fI1/2;
		fIcPh = 180;
		float fI2Coef = fI2/2;
		nClock = 2*(m_nConnectMode/2);

		switch (nClock)
		{
		case 0:
			{
				fIap = fI2;
				fIapPh = 180;
				fIbp = fI2Coef;
				fIbpPh = 0;
				fIcp = fI2Coef;
				fIcpPh = 0;
			}
			break;
		case 2:
			{
				fIap = fI2Coef;
				fIapPh = 180;
				fIbp = fI2;
				fIbpPh = 0;
				fIcp = fI2Coef;
				fIcpPh = 180;
			}
			break;
		case 4:
			{
				fIap = fI2Coef;
				fIapPh = 0;
				fIbp = fI2Coef;
				fIbpPh = 0;
				fIcp = fI2;
				fIcpPh = 180;
			}
			break;
		case 6:
			{
				fIap = fI2;
				fIapPh = 0;
				fIbp = fI2Coef;
				fIbpPh = 180;
				fIcp = fI2Coef;
				fIcpPh = 180;
			}
			break;
		case 8:
			{
				fIap = fI2Coef;
				fIapPh = 0;
				fIbp = fI2;
				fIbpPh = 180;
				fIcp = fI2Coef;
				fIcpPh = 0;
			}
			break;
		case 10:
			{
				fIap = fI2Coef;
				fIapPh = 180;
				fIbp = fI2Coef;
				fIbpPh = 180;
				fIcp = fI2;
				fIcpPh = 0;
			}
			break;
		}
	}

	return true;
}

bool CSttDiffCurrCalculatTool::CurrentCal_IP_D(float &fIa,float &fIaPh,float &fIb,float &fIbPh,float &fIc,float &fIcPh
										  ,float &fIap,float &fIapPh,float &fIbp,float &fIbpPh,float &fIcp,float &fIcpPh, bool bSame)
{
	fIaPh = 0;
	fIb = fIa;
	fIbPh = 180;
	fIc = fIcPh = 0;
	float  fI2 = fIap;

	int nClock = 0;
	if (!bSame)
	{
		nClock = 2*(m_nConnectMode/2)+1;
		float fI2Coef = fI2/SQRT_3;

		switch (nClock)
		{
		case 11:
			{
				fIap = fI2Coef*2;
				fIapPh = 180;
				fIbp = fI2Coef;
				fIbpPh = 0;
				fIcp = fI2Coef;
				fIcpPh = 0;
			}
			break;
		case 1:
			{
				fIap = fI2Coef;
				fIapPh = 180;
				fIbp = fI2Coef*2;
				fIbpPh = 0;
				fIcp = fI2Coef;
				fIcpPh = 180;
			}
			break;
		case 3:
			{
				fIap = fI2Coef;
				fIapPh = 0;
				fIbp = fI2Coef;
				fIbpPh = 0;
				fIcp = fI2Coef*2;
				fIcpPh = 180;
			}
			break;
		case 5:
			{
				fIap = fI2Coef*2;
				fIapPh = 0;
				fIbp = fI2Coef;
				fIbpPh = 180;
				fIcp = fI2Coef;
				fIcpPh = 180;
			}
			break;
		case 7:
			{
				fIap = fI2Coef;
				fIapPh = 0;
				fIbp = fI2Coef*2;
				fIbpPh = 180;
				fIcp = fI2Coef;
				fIcpPh = 0;
			}
			break;
		case 9:
			{
				fIap = fI2Coef;
				fIapPh = 180;
				fIbp = fI2Coef;
				fIbpPh = 180;
				fIcp = fI2Coef*2;
				fIcpPh = 0;
			}
			break;
		}
	}
	else
	{
		nClock = 2*(m_nConnectMode/2);

		switch (nClock)
		{
		case 0:
			{
				fIap = fI2;
				fIapPh = 180;
				fIbp = fI2;
				fIbpPh = 0;
				fIcp = 0;
				fIcpPh = 0;
			}
			break;
		case 2:
			{
				fIap = 0;
				fIapPh = 0;
				fIbp = fI2;
				fIbpPh = 0;
				fIcp = fI2;
				fIcpPh = 180;
			}
			break;
		case 4:
			{
				fIbp = fI2;
				fIbpPh = 0;
				fIcp = 0;
				fIcpPh = 0;
				fIap = fI2;
				fIapPh = 180;
			}
			break;
		case 6:
			{
				fIap = fI2;
				fIapPh = 0;
				fIbp = fI2;
				fIbpPh = 180;
				fIcp = 0;
				fIcpPh = 0;
			}
			break;
		case 8:
			{
				fIap = 0;
				fIapPh = 0;
				fIbp = fI2;
				fIbpPh = 180;
				fIcp = fI2;
				fIcpPh = 0;
			}
			break;
		case 10:
			{
				fIbp = fI2;
				fIbpPh = 180;
				fIcp = 0;
				fIcpPh = 0;
				fIap = fI2;
				fIapPh = 0;
			}
			break;
		}
	}

	return true;
}

bool CSttDiffCurrCalculatTool::CurrentCal_IP_Y(float &fIa,float &fIaPh,float &fIb,float &fIbPh,float &fIc,float &fIcPh
										  ,float &fIap,float &fIapPh,float &fIbp,float &fIbpPh,float &fIcp,float &fIcpPh, bool bSame)
{
	float  fI1=fIa, fI2=fIap;
	int nClock = 0;

	if (!bSame)
	{
		fIap = fI2;
		fIapPh = 0;
		fIbp = fI2;
		fIbpPh = 180;
		fIcp = 0;
		fIcpPh = 0;
		nClock = 2*(m_nConnectMode/2)+1;
		float fI1Coef = fI1/SQRT_3;

		switch (nClock)
		{
		case 11:
			{
				fIa = fI1Coef;
				fIaPh = 180;
				fIb = fI1Coef*2;
				fIbPh = 0;
				fIc = fI1Coef;
				fIcPh = 180;
			}
			break;
		case 1:
			{
				fIa = fI1Coef*2;
				fIaPh = 180;
				fIb = fI1Coef;
				fIbPh = 0;
				fIc = fI1Coef;
				fIcPh = 0;
			}
			break;
		case 3:
			{
				fIa = fI1Coef*2;
				fIaPh = 0;
				fIb = fI1Coef;
				fIbPh = 180;
				fIc = fI1Coef;
				fIcPh = 180;
			}
			break;
		case 5:
			{
				fIa = fI1Coef;
				fIaPh = 0;
				fIb = fI1Coef*2;
				fIbPh = 180;
				fIc = fI1Coef;
				fIcPh = 0;
			}
			break;
		case 7:
			{
				fIa = fI1Coef*2;
				fIaPh = 0;
				fIb = fI1Coef;
				fIbPh = 180;
				fIc = fI1Coef;
				fIcPh = 180;
			}
			break;
		case 9:
			{
				fIa = fI1Coef*2;
				fIaPh = 180;
				fIb = fI1Coef;
				fIbPh = 0;
				fIc = fI1Coef;
				fIcPh = 0;
			}
			break;
		}
	}
	else
	{
		fIa = fI1;
		fIaPh = 0;
		fIb = fI1;
		fIbPh = 180;
		fIc = 0;
		fIcPh = 0;
		nClock = 2*(m_nConnectMode/2);

		switch (nClock)
		{
		case 0:
			{
				fIap = fI2;
				fIapPh = 180;
				fIbp = fI2;
				fIbpPh = 0;
				fIcp = 0;
				fIcpPh = 0;
			}
			break;
		case 2:
			{
				fIap = 0;
				fIapPh = 0;
				fIbp = fI2;
				fIbpPh = 0;
				fIcp = fI2;
				fIcpPh = 180;
			}
			break;
		case 4:
			{
				fIbp = fI2;
				fIbpPh = 0;
				fIcp = 0;
				fIcpPh = 0;
				fIap = fI2;
				fIapPh = 180;
			}
			break;
		case 6:
			{
				fIap = fI2;
				fIapPh = 0;
				fIbp = fI2;
				fIbpPh = 180;
				fIcp = 0;
				fIcpPh = 0;
			}
			break;
		case 8:
			{
				fIap = 0;
				fIapPh = 0;
				fIbp = fI2;
				fIbpPh = 180;
				fIcp = fI2;
				fIcpPh = 0;
			}
			break;
		case 10:
			{
				fIbp = fI2;
				fIbpPh = 180;
				fIcp = 0;
				fIcpPh = 0;
				fIap = fI2;
				fIapPh = 0;
			}
			break;
		}
	}

	return true;
}

bool CSttDiffCurrCalculatTool::CurrentCal_SP(float &fIa,float &fIaPh,float &fIb,float &fIbPh,float &fIc,float &fIcPh
										,float &fIap,float &fIapPh,float &fIbp,float &fIbpPh,float &fIcp,float &fIcpPh)	// Added by ZM 20180504		单相故障计算
{
	// 预留补偿电流  Added by ZM 20180814
	// 	float fIos = fIa;	//fIa/m_fKpl*m_fKjxl;
	// 	float fIosPh = (fIaPh > 180) ? (fIaPh-180) : (fIaPh+180);

	int nAngleMode;
	if(m_nAngleMode>0)   //m_nAngleMode=1:D侧转角；m_nAngleMode=2:Y侧转角；
	{
		if(m_nPhase!=ABCPhase)
		{
			if(m_nWindH<1)nAngleMode=m_nAngleMode;
			else
			{
				if(m_nAngleMode==1)nAngleMode=2;
				else nAngleMode=1;
			}
			if(nAngleMode==2)
			{
				switch(GetMethod(m_nConnectMode,nAngleMode))
				{
				case 0:
					{
						fIa=fIa/*/m_fKph*/*m_fKjxh;
						fIap=fIap/*/m_fKpl*/*m_fKjxl;
						if(GetSign(m_nConnectMode,nAngleMode)<0)
							fIaPh+=180.0;
						if(m_bCTStarPoint)
							fIaPh+=180.0;
					}
					break;
				case 1:
					{
						fIb=fIa/*/m_fKph*/*m_fKjxh;
						fIbp=fIap/*/m_fKpl*/*m_fKjxl;
						if(GetSign(m_nConnectMode,nAngleMode)<0)
							fIbPh+=180.0;
						if(m_bCTStarPoint)
							fIbPh+=180.0;
					}
					break;
				case 2:
					{
						fIc=fIa/*/m_fKph*/*m_fKjxh;
						fIcp=fIap/*/m_fKpl*/*m_fKjxl;
						if(GetSign(m_nConnectMode,nAngleMode)<0)
							fIcPh+=180.0;
						if(m_bCTStarPoint)
							fIcPh+=180.0;
					}
					break;
				case 3:
					//						fIbp=fIa/m_fKpl*m_fKjxl;
					//						fIbpPh=fIaPh;
					{
						fIa=fIa/*/m_fKph*/*m_fKjxh;
						fIap=fIap/*/m_fKpl*/*m_fKjxl;
						if(GetSign(m_nConnectMode,nAngleMode)<0)
							fIaPh+=180.0;
						if(m_bCTStarPoint)
							fIaPh+=180.0;
						if(m_nWindH==1&&m_nWindL==0&&m_nAngleMode==1)
						{
							fIbp=fIap;
							fIbpPh=fIapPh+180.0;
						}
						else
						{
							//							fIbp=fIa/m_fKpl*m_fKjxl;  2013-3-15
							fIbp=fIa/*/m_fKpl*/*m_fKjxl/m_fKjxh;
							//							fIbpPh=fIaPh; 2013-3-15
							if(GetSign(m_nConnectMode,nAngleMode)<0)
								fIbpPh=fIaPh-180;
							else
								fIbpPh=fIaPh;
						}
					}
					break;
				case 4:
					//						fIcp=fIa/m_fKpl*m_fKjxl;
					//						fIcpPh=fIaPh;
					{
						fIb=fIa/*/m_fKph*/*m_fKjxh;
						fIbp=fIap/*/m_fKpl*/*m_fKjxl;
						fIa=0;
						fIaPh=0;
						if(GetSign(m_nConnectMode,nAngleMode)<0)
							fIbPh+=180.0;
						if(m_bCTStarPoint)
							fIbPh+=180.0;
						if(m_nWindH==1&&m_nWindL==0&&m_nAngleMode==1)
						{
							fIcp=fIbp;
							fIcpPh=fIbpPh+180.0;
						}
						else
						{
							fIcp=fIa/*/m_fKpl*/*m_fKjxl;
							fIcpPh=fIaPh;
						}
					}
					break;
				case 5:
					//						fIcp=fIa/m_fKpl*m_fKjxl;
					//						fIcpPh=fIaPh;
					{
						if(GetSign(m_nConnectMode,nAngleMode)<0)
							fIaPh+=180.0;
						if(m_bCTStarPoint)
							fIaPh+=180.0;
						fIa=fIa/*/m_fKph*/*m_fKjxh;
						fIap=fIap/*/m_fKpl*/*m_fKjxl;
						if(m_nWindH==1&&m_nWindL==0&&m_nAngleMode==1)
						{
							fIcp=fIap;
							fIcpPh=fIapPh+180.0;
						}
						else
						{
							//							fIcp=fIa/m_fKpl*m_fKjxl; 2013-3-15
							fIcp=fIa/*/m_fKpl*/*m_fKjxl/m_fKjxh;
							//							fIcpPh=fIaPh;  2013-3-15
							if(GetSign(m_nConnectMode,nAngleMode)<0)
								fIcpPh=fIaPh-180;
							else
								fIcpPh=fIaPh;
						}
					}
					break;
				}
			}
			else if(nAngleMode==1)
			{
				switch(GetMethod(m_nConnectMode,nAngleMode))
				{
				case 0:
					{
						fIa=fIa/*/m_fKph*/*m_fKjxh;
						fIap=fIap/*/m_fKpl*/*m_fKjxl;
						if(GetSign(m_nConnectMode,nAngleMode)<0)
							fIaPh+=180.0;
						if(m_bCTStarPoint)
							fIaPh+=180.0;
					}
					break;
				case 1:
					{
						fIb=fIa/*/m_fKph*/*m_fKjxh;
						fIbp=fIap/*/m_fKpl*/*m_fKjxl;
						if(GetSign(m_nConnectMode,nAngleMode)<0)
							fIbPh+=180.0;
						if(m_bCTStarPoint)
							fIbPh+=180.0;
					}
					break;
				case 2:
					{
						fIc=fIa/*/m_fKph*/*m_fKjxh;
						fIcp=fIap/*/m_fKpl*/*m_fKjxl;
						if(GetSign(m_nConnectMode,nAngleMode)<0)
							fIcPh+=180.0;
						if(m_bCTStarPoint)
							fIcPh+=180.0;
					}
					break;
				case 3:
					{
						fIbPh=fIaPh+180.0;
						fIap=fIap/*/m_fKpl*/*m_fKjxl;
						fIa=fIa/*/m_fKph*/*m_fKjxh;
						fIb=fIa;
						if(GetSign(m_nConnectMode,nAngleMode)<0)
							fIapPh+=180.0;
						if(m_bCTStarPoint)
							fIapPh+=180.0;
					}
					break;
				case 4:
					{
						fIbPh=fIaPh;
						fIcPh=fIbPh+180.0;
						fIbp=fIap/*/m_fKpl*/*m_fKjxl;
						fIcpPh=fIapPh;
						fIb=fIa/*/m_fKph*/*m_fKjxh;
						fIc=fIb;
						fIa=0;
						fIaPh=0;
						if(GetSign(m_nConnectMode,nAngleMode)<0)
							fIbpPh+=180.0;
						if(m_bCTStarPoint)
							fIbpPh+=180.0;
					}
					break;
				case 5:
					{
						fIcPh=fIaPh+180.0;
						fIap=fIap/*/m_fKpl*/*m_fKjxl;
						fIa=fIa/*/m_fKph*/*m_fKjxh;
						fIc=fIa;
						if(GetSign(m_nConnectMode,nAngleMode)<0)
							fIapPh+=180.0;
						if(m_bCTStarPoint)
							fIapPh+=180.0;
					}
					break;
				case 6:
					{
						fIa=fIa/*/m_fKph*/*m_fKjxh;
						fIap=fIap/*/m_fKpl*/*m_fKjxl;
						fIb=fIa;
						fIbp=fIap;
						if(GetSign(m_nConnectMode,nAngleMode)<0)
							fIaPh+=180.0;
						if(m_bCTStarPoint)
							fIaPh+=180.0;
						fIbPh=fIaPh+180.0;
						fIbpPh=fIapPh+180.0;
					}
					break;
				}
			}
		}
		else
		{
			if(m_bCTStarPoint)
				fIaPh+=180.0;
			fIa=fIa/*/m_fKph*/*m_fKjxh;
			fIap=fIap/*/m_fKpl*/*m_fKjxl;
			fIapPh-=30.0*m_nConnectMode;  //m_nConnectMode=12,1,2,...11
			fIa/=m_fKjxh;
			fIap/=m_fKjxl;
			//			if(m_nWindH<1)fIa/=sqrt(3.0);
			//			if(m_nWindL<1)fIap/=sqrt(3.0);
			fIb=fIa;
			fIc=fIa;
			fIbp=fIap;
			fIcp=fIap;
			fIbPh=fIaPh-120.0;
			fIcPh=fIaPh+120.0;
			fIbpPh=fIapPh-120.0;
			fIcpPh=fIapPh+120.0;
		}
	}
	else  //外转角
	{
		if(m_nPhase!=ABCPhase)
		{
			fIa=fIa/*/m_fKph*/;
			fIb=fIb/*/m_fKph*/;
			fIc=fIc/*/m_fKph*/;
			fIap=fIap/*/m_fKpl*/;
			fIbp=fIbp/*/m_fKpl*/;
			fIcp=fIcp/*/m_fKpl*/;
			if(m_bCTStarPoint)
			{
				fIapPh+=180.0;
				fIbpPh+=180.0;
				fIcpPh+=180.0;
			}
		}
		else
		{
			fIa=fIa/*/m_fKph*/;
			fIap=fIap/*/m_fKpl*/;
			fIb=fIa;
			fIc=fIa;
			fIbPh=fIaPh-120.0;
			fIcPh=fIaPh+120.0;
			fIbp=fIap;
			fIcp=fIap;
			fIbpPh=fIapPh-120.0;
			fIcpPh=fIapPh+120.0;
			if(m_bCTStarPoint)
			{
				fIapPh+=180.0;
				fIbpPh+=180.0;
				fIcpPh+=180.0;
			}
		}
	}

	// 为单相故障增加对侧补偿电流  Added by ZM 20180814
	// 	int nModeH,nModeL;		// 0-Y 1-△
	// 	if (m_nWindSide == 0)  // 高低
	// 	{
	// 		nModeH = m_nWindH;
	// 		nModeL = m_nWindL;
	// 	}
	// 	else if (m_nWindSide == 1)	// 高中
	// 	{
	// 		nModeH = m_nWindH;
	// 		nModeL = m_nWindM;
	// 	}
	// 	else	// 中低
	// 	{
	// 		nModeH = m_nWindM;
	// 		nModeL = m_nWindL;
	// 	}

	// 永远在Y侧补偿
	// 	if (nModeH==1 && nModeL==0)	// △—Y
	// 	{
	// 			fIbp = fIos/m_fKpl*m_fKjxl;
	// 			fIbpPh = fIosPh;
	// 	}
	// 	else if (nModeH==0 && nModeL==1)	// Y—△
	// 	{
	//fIc = fIos/m_fKph*m_fKjxh;
	//fIcPh = fIosPh;
	// 	}

	return true;
}

void CSttDiffCurrCalculatTool::CalKpx()
{
	//CT变比  根号3/qSqrt(3)=SQRT_3
	float Um_CT=m_fUm*(m_fCTPm/m_fCTSm);
	float Uh_CT=m_fUh*(m_fCTPh/m_fCTSh);
	float Ul_CT=m_fUl*(m_fCTPl/m_fCTSl);

	if(m_nKcal==0)//自动计算平衡系数
	{
		if(m_nJXFactor==0)//不考虑绕组接线型式
		{
			switch(m_nAngleMode)//校正方式
			{
			case 0://无校正
				{
					switch(m_nWindSide)//测试绕组
					{
					case 0://高低
						{
							if(m_nWindH==0)//高压侧绕组接线型式,"Y"
							{
								if(m_nWindL==0)
								{
									m_fKph=1;
									m_fKpl=Ul_CT/Uh_CT;
								}
								if(m_nWindL==1)
								{
									m_fKph=1;
									m_fKpl=SQRT_3*Ul_CT/Uh_CT;
								}
							}
							if(m_nWindH==1)//高压侧绕组接线型式,"△"
							{
								if(m_nWindL==0)
								{
									m_fKph=1;
									m_fKpl=Ul_CT/(Uh_CT*SQRT_3);
								}
								if(m_nWindL==1)
								{
									m_fKph=1;
									m_fKpl=Ul_CT/Uh_CT;
								}
							}
						}
						break;
					case 1://高中
						{
							if(m_nWindH==0)
							{
								if(m_nWindM==0)
								{
									m_fKph=1;
									m_fKpl=Um_CT/Uh_CT;
								}
								if(m_nWindM==1)
								{
									m_fKph=1;
									m_fKpl=SQRT_3*Um_CT/Uh_CT;
								}
							}
							if(m_nWindH==1)
							{
								if(m_nWindM==0)
								{
									m_fKph=1;
									m_fKpl=Um_CT/(Uh_CT*SQRT_3);
								}
								if(m_nWindM==1)
								{
									m_fKph=1;
									m_fKpl=Um_CT/Uh_CT;
								}
							}
						}
						break;
					case 2://中低
						{
							if(m_nWindH==0)
							{
								if(m_nWindM==0)
								{
									if(m_nWindL==0)
									{
										m_fKph=Um_CT/Uh_CT;
										m_fKpl=Ul_CT/Uh_CT;
									}
									if(m_nWindL==1)
									{
										m_fKph=Um_CT/Uh_CT;
										m_fKpl=SQRT_3*Ul_CT/Uh_CT;
									}
								}
								if(m_nWindM==1)
								{
									if(m_nWindL==0)
									{
										m_fKph=SQRT_3*Um_CT/Uh_CT;
										m_fKpl=Ul_CT/Uh_CT;
									}
									if(m_nWindL==1)
									{
										m_fKph=SQRT_3*Um_CT/Uh_CT;
										m_fKpl=SQRT_3*Ul_CT/Uh_CT;
									}
								}
							}
							if(m_nWindH==1)
							{
								if(m_nWindM==0)
								{
									if(m_nWindL==0)
									{
										m_fKph=Um_CT/(Uh_CT*SQRT_3);
										m_fKpl=Ul_CT/(Uh_CT*SQRT_3);
									}
									if(m_nWindL==1)
									{
										m_fKph=Um_CT/(Uh_CT*SQRT_3);
										m_fKpl=Ul_CT/Uh_CT;
									}
								}
								if(m_nWindM==1)
								{
									if(m_nWindL==0)
									{
										m_fKph=Um_CT/Uh_CT;
										m_fKpl=Ul_CT/(Uh_CT*SQRT_3);
									}
									if(m_nWindL==1)
									{
										m_fKph=Um_CT/Uh_CT;
										m_fKpl=Ul_CT/Uh_CT;
									}
								}
							}
						}
						break;
					}
				}
				break;
			case 1://△侧校正
				{
					switch(m_nWindSide)
					{
					case 0:
						{
							m_fKph=1;
							m_fKpl=Ul_CT/Uh_CT;
						}
						break;
					case 1:
						{
							m_fKph=1;
							m_fKpl=Um_CT/Uh_CT;
						}
						break;
					case 2:
						{
							m_fKph=Um_CT/Uh_CT;
							m_fKpl=Ul_CT/Uh_CT;
						}
						break;
					}
				}
				break;
			case 2://Y侧校正
				{
					switch(m_nWindSide)
					{
					case 0:
						{
							m_fKph=1;
							m_fKpl=Ul_CT/Uh_CT;
						}
						break;
					case 1:
						{
							m_fKph=1;
							m_fKpl=Um_CT/Uh_CT;
						}
						break;
					case 2:
						{
							m_fKph=Um_CT/Uh_CT;
							m_fKpl=Ul_CT/Uh_CT;
						}
						break;
					}
				}
				break;
			}
		}

		if(m_nJXFactor==1)//考虑绕组接线型
		{
			switch(m_nAngleMode)
			{
			case 0:
				{
					switch(m_nWindSide)
					{
					case 0:
						{
							if(m_nWindH==0)
							{
								if(m_nWindL==0)
								{
									m_fKph=1;
									m_fKpl=Ul_CT/Uh_CT;
								}
								if(m_nWindL==1)
								{
									m_fKph=1;
									m_fKpl=SQRT_3*Ul_CT/Uh_CT;
								}
							}
							if(m_nWindH==1)
							{
								if(m_nWindL==0)
								{
									m_fKph=1;
									m_fKpl=Ul_CT/(Uh_CT*SQRT_3);
								}
								if(m_nWindL==1)
								{
									m_fKph=1;
									m_fKpl=Ul_CT/Uh_CT;
								}
							}
						}
						break;
					case 1:
						{
							if(m_nWindH==0)
							{
								if(m_nWindM==0)
								{
									m_fKph=1;
									m_fKpl=Um_CT/Uh_CT;
								}
								if(m_nWindM==1)
								{
									m_fKph=1;
									m_fKpl=SQRT_3*Um_CT/Uh_CT;
								}
							}
							if(m_nWindH==1)
							{
								if(m_nWindM==0)
								{
									m_fKph=1;
									m_fKpl=Um_CT/(Uh_CT*SQRT_3);
								}
								if(m_nWindM==1)
								{
									m_fKph=1;
									m_fKpl=Um_CT/Uh_CT;
								}
							}
						}
						break;
					case 2:
						{
							if(m_nWindH==0)
							{
								if(m_nWindM==0)
								{
									if(m_nWindL==0)
									{
										m_fKph=Um_CT/Uh_CT;
										m_fKpl=Ul_CT/Uh_CT;
									}
									if(m_nWindL==1)
									{
										m_fKph=Um_CT/Uh_CT;
										m_fKpl=SQRT_3*Ul_CT/Uh_CT;
									}
								}
								if(m_nWindM==1)
								{
									if(m_nWindL==0)
									{
										m_fKph=SQRT_3*Um_CT/Uh_CT;
										m_fKpl=Ul_CT/Uh_CT;
									}
									if(m_nWindL==1)
									{
										m_fKph=SQRT_3*Um_CT/Uh_CT;
										m_fKpl=SQRT_3*Ul_CT/Uh_CT;
									}
								}
							}
							if(m_nWindH==1)
							{
								if(m_nWindM==0)
								{
									if(m_nWindL==0)
									{
										m_fKph=Um_CT/(Uh_CT*SQRT_3);
										m_fKpl=Ul_CT/(Uh_CT*SQRT_3);
									}
									if(m_nWindL==1)
									{
										m_fKph=Um_CT/(Uh_CT*SQRT_3);
										m_fKpl=Ul_CT/Uh_CT;
									}
								}
								if(m_nWindM==1)
								{
									if(m_nWindL==0)
									{
										m_fKph=Um_CT/Uh_CT;
										m_fKpl=Ul_CT/(Uh_CT*SQRT_3);
									}
									if(m_nWindL==1)
									{
										m_fKph=Um_CT/Uh_CT;
										m_fKpl=Ul_CT/Uh_CT;
									}
								}
							}
						}
						break;
					}
				}
				break;
			case 1:
				{
					switch(m_nWindSide)
					{
					case 0:
						{
							m_fKph=SQRT_3;
							m_fKpl=SQRT_3*Ul_CT/Uh_CT;
						}
						break;
					case 1:
						{
							m_fKph=SQRT_3;
							m_fKpl=SQRT_3*Um_CT/Uh_CT;
						}
						break;
					case 2:
						{
							m_fKph=SQRT_3*Um_CT/Uh_CT;
							m_fKpl=SQRT_3*Ul_CT/Uh_CT;
						}
						break;
					}
				}
				break;
			case 2:
				{
					switch(m_nWindSide)
					{
					case 0:
						{
							m_fKph=SQRT_3;
							m_fKpl=SQRT_3*Ul_CT/Uh_CT;
						}
						break;
					case 1:
						{
							m_fKph=SQRT_3;
							m_fKpl=SQRT_3*Um_CT/Uh_CT;
						}
						break;
					case 2:
						{
							m_fKph=SQRT_3*Um_CT/Uh_CT;
							m_fKpl=SQRT_3*Ul_CT/Uh_CT;
						}
						break;
					}
				}
				break;
			}
		}
	}

	if(m_nKcal==1)//手动设置平衡系数
	{
		switch(m_nWindSide)//测试绕组
		{
		case 0://高低
			{
				m_fKph=m_fKph_Set;
				m_fKpl=m_fKpl_Set;
			}
			break;
		case 1://高中
			{
				m_fKph=m_fKph_Set;
				m_fKpl=m_fKpm_Set;
			}
			break;
		case 2://中低
			{
				m_fKph=m_fKpm_Set;
				m_fKpl=m_fKpl_Set;
			}
			break;
		}
	}

	//	m_fKph=((m_nKcal<1)*(((m_nAngleMode>0)*(m_nJXFactor<1)*1+(m_nAngleMode>0)*(m_nJXFactor>0)*SQRT_3)+(m_nAngleMode<1)*1)+(m_nKcal>0)*m_nKph)*(m_nWindSide<2);
	//	m_fKph+=((m_nKcal<1)*(((Um*(CTPm/CTSm))/(Uh*(CTPh/CTSh))*((m_nAngleMode>0)*(m_nJXFactor<1)*1+(m_nAngleMode>0)*(m_nJXFactor>0)*SQRT_3))+(m_nAngleMode<1)*(((SQRT_3*(m_nWindH<1)+1*(m_nWindH>0))/(Uh*(CTPh/CTSh)))/((SQRT_3*(m_nWindM<1)+1*(m_nWindM>0))/(Um*(CTPm/CTSm)))))+(m_nKcal>0)*m_nKpm)*(m_nWindSide>1);

	//	m_fKpl=((m_nKcal<1)*(((Ul*(CTPl/CTSl))/(Uh*(CTPh/CTSh))*((m_nAngleMode>0)*(m_nJXFactor<1)*1+(m_nAngleMode>0)*(m_nJXFactor>0)*SQRT_3))+(m_nAngleMode<1)*(((SQRT_3*(m_nWindH<1)+1*(m_nWindH>0))/(Uh*(CTPh/CTSh)))/((SQRT_3*(m_nWindL<1)+1*(m_nWindL>0))/(Ul*(CTPl/CTSl)))))+(m_nKcal>0)*m_nKpl)*(m_nWindSide<1);
	//	m_fKpl+=((m_nKcal<1)*(((Ul*(CTPl/CTSl))/(Uh*(CTPh/CTSh))*((m_nAngleMode>0)*(m_nJXFactor<1)*1+(m_nAngleMode>0)*(m_nJXFactor>0)*SQRT_3))+(m_nAngleMode<1)*(((SQRT_3*(m_nWindH<1)+1*(m_nWindH>0))/(Uh*(CTPh/CTSh)))/((SQRT_3*(m_nWindL<1)+1*(m_nWindL>0))/(Ul*(CTPl/CTSl)))))+(m_nKcal>0)*m_nKpl)*(m_nWindSide>1);
	//	m_fKpl+=((m_nKcal<1)*(((Um*(CTPm/CTSm))/(Uh*(CTPh/CTSh))*((m_nAngleMode>0)*(m_nJXFactor<1)*1+(m_nAngleMode>0)*(m_nJXFactor>0)*SQRT_3))+(m_nAngleMode<1)*(((SQRT_3*(m_nWindH<1)+1*(m_nWindH>0))/(Uh*(CTPh/CTSh)))/((SQRT_3*(m_nWindM<1)+1*(m_nWindM>0))/(Um*(CTPm/CTSm)))))+(m_nKcal>0)*m_nKpm)*(m_nWindSide>0)*(m_nWindSide<2);

}





