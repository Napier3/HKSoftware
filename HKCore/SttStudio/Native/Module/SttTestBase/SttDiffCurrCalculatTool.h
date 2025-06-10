#pragma once
#include "SttComplexp.h"


#define DIFF_CURR_CAL_CHANNEL_NUM_3I                       3//
#define DIFF_CURR_CAL_CHANNEL_MAX                          6

#define ElecRailway_TransType_0_YV                         0
#define ElecRailway_TransType_1_YD11                       1//无转角
#define ElecRailway_TransType_2_Single                     2
#define ElecRailway_TransType_3_YDD                        3
#define ElecRailway_TransType_4_Scott1                     4
#define ElecRailway_TransType_5_VV1                        5
#define ElecRailway_TransType_6_VX                         6
#define ElecRailway_TransType_7_YA                         7
#define ElecRailway_TransType_8_ThreeVV                    8
#define ElecRailway_TransType_9_Scott2                     9
#define ElecRailway_TransType_10_Scott3                    10
#define ElecRailway_TransType_11_VV2                       11
#define ElecRailway_TransType_12_Scott4                    12
#define ElecRailway_TransType_13_ThreeVV2                  13
#define ElecRailway_TransType_14_ThreeVV3                  14
#define ElecRailway_TransType_15_ThreeYV2                  15//无转角
#define ElecRailway_TransType_16_Scott5                    16
#define ElecRailway_TransType_17_YD11_YT                   17//在Y侧进行转角
#define ElecRailway_TransType_18_ThreeYV2_YT               18//在Y侧进行转角




typedef struct
{
	float famptitude;//fuzhi
	float fphase;
	float ffre;
}ChannelUI_Diff;


class CSttDiffCurrCalculatTool
{
public:
	CSttDiffCurrCalculatTool(void);
	virtual ~CSttDiffCurrCalculatTool(void);
	//对全部参数进行统一初始化
	void Init();

	//初始化系统参数,测试仪最大输出的电流值、输出的基波频率
    void InitSysParas(float fIOutmax = 100.0f, float fFreq = 50.0f);
	//初始化全部差动故障计算参数(除去平衡系数以外)
	void InitParas6I(int nInSel,float fIbase,int nSearchMode,bool bMinAxis,int nAngleMode,int nIbiasCal,int nWindH,int nWindM,int nWindL,int nWindSide,
		float fFactor1,float fFactor2,int nConnectMode,int nPhase,bool bCTStarPoint,int nJXFactor);//初始化全部成员参数
	//手动计算平衡系数并指定
	void InitParas_SetBalanceFactors(float fKph_Set,float fKpm_Set,float fKpl_Set);
	//通过变压器参数,自动计算平衡系数
	void InitParas_AutoCalBalanceFactors(float fSn,float fUh,float fUm,float fUl,float fCTPh,float fCTSh,float fCTPm,float fCTSm,float fCTPl,float fCTSl);

	void InitParas5I_ElecRailway(float fIbase,int nSearchMode,bool bMinAxis,int nIbiasCal,float fKpl,
		int nPhase,bool bCTStarPoint,int nRWCTconnect,int nTranSort,int nKphMode);//初始化电铁牵引变
	void CurrentCal_ElecRailway(float *fId,float fIr,float &fIalpha,float &fIbeta);//计算出牵引变的参数值

	void InitParas3I_BP2();//zhouhj 20211211  初始化BP2复式比率差动参数
	BOOL CurrentCal3I_BP2(float *fId,float fIr_Id);//三相输出的BP2复式比率差动计算

	 void  CurrentCal(float *fId,float fIr);
	ChannelUI_Diff* GetChannelCurrents(){return m_arryoCurrent;}

	void GetKps(float& fKph,float& fKpm,float& fKpl){ fKph = m_fKph; fKpm = m_fKpm; fKpl = m_fKpl;} //yyj 20211029 
	void GetKjx(float& fKjxh,float& fKjxl){ fKjxh = m_fKjxh; fKjxl = m_fKjxl; } //yyj 20211029
	void GetIet(float& fIet){ fIet = m_fIet; } //yyj 20211029

	static BOOL IsPhaseA(int nPhase){return (nPhase == APhase);}
	static BOOL IsPhaseB(int nPhase){return (nPhase == BPhase);}
	static BOOL IsPhaseC(int nPhase){return (nPhase == CPhase);}
	static BOOL IsPhaseABC(int nPhase){return (nPhase == ABCPhase);}
	static BOOL IsPhaseAB(int nPhase){return (nPhase == ABPhase);}
	static BOOL IsPhaseBC(int nPhase){return (nPhase == BCPhase);}
	static BOOL IsPhaseCA(int nPhase){return (nPhase == CAPhase);}


protected:
	int   GetMethod(int nClock,int nAngleMode);
	 int   GetSign(int nClock,int nAngleMode);

	 void  CalKjx();

	 void  CalKpx();
	 bool CurrentCal_SP(float &fIa,float &fIaPh,float &fIb,float &fIbPh,float &fIc,float &fIcPh
		 ,float &fIap,float &fIapPh,float &fIbp,float &fIbpPh,float &fIcp,float &fIcpPh);	// Added by ZM 20180504		单相故障计算(已废止)
	 bool CurrentCal_SP_D(float &fIa,float &fIaPh,float &fIb,float &fIbPh,float &fIc,float &fIcPh
		 ,float &fIap,float &fIapPh,float &fIbp,float &fIbpPh,float &fIcp,float &fIcpPh, bool bSame);	// Added by ZM 20180816		单相故障△侧校正（角侧转角）
	 bool CurrentCal_SP_Y(float &fIa,float &fIaPh,float &fIb,float &fIbPh,float &fIc,float &fIcPh
		 ,float &fIap,float &fIapPh,float &fIbp,float &fIbpPh,float &fIcp,float &fIcpPh, bool bSame);	// Added by ZM 20180816		单相故障Y侧校正（星侧转角）
	 bool CurrentCal_IP_D(float &fIa,float &fIaPh,float &fIb,float &fIbPh,float &fIc,float &fIcPh
		 ,float &fIap,float &fIapPh,float &fIbp,float &fIbpPh,float &fIcp,float &fIcpPh, bool bSame);	// Added by ZM 20180504		相间故障△侧校正（角侧转角）
	 bool CurrentCal_IP_Y(float &fIa,float &fIaPh,float &fIb,float &fIbPh,float &fIc,float &fIcPh
		 ,float &fIap,float &fIapPh,float &fIbp,float &fIbpPh,float &fIcp,float &fIcpPh, bool bSame);	// Added by ZM 20180504		相间故障Y侧校正（星侧转角）


	 enum TestPhasor_type {
		 APhase = 0,
		 BPhase = 1,
		 CPhase = 2,
		 ABCPhase = 3,
		 ABPhase = 4,
		 BCPhase = 5,
		 CAPhase = 6
	 };

	 enum BaseCurrentSelect {
		 HighSideSecondaryCurrent = 0,
		 SettingValue = 1,
		 AllSideCurrent = 2
	 };


private:
	void CalTranSort0_YV(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort1_YD11(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort2_Single(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort3_YDD(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort4_Scott1(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort5_VV1(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort6_VX(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort7_YA(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort8_ThreeVV(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort9_Scott2(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort10_Scott3(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort11_VV2(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort12_Scott4(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort13_ThreeVV2(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort14_ThreeVV3(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort15_ThreeYV2(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort16_Scott5(float fIfault,float &fIalpha,float &fIbeta);
	void CalTranSort17_YD11_YT(float fIfault,float fReimbCurr_YD11,float &fIalpha,float &fIbeta);
	void CalTranSort18_ThreeYV2_YT(float fIfault,float fReimbCurr_YD11,float &fIalpha,float &fIbeta);



	ChannelUI_Diff m_arryoCurrent[DIFF_CURR_CAL_CHANNEL_MAX];
//	ChannelUI_Diff m_harmCurrent[DIFF_CURR_CAL_CHANNEL_MAX];

	 float m_fIOutmax;//单相最大输出电流值(对于数字化保护,该值可以很大;对于模拟输出,需要对该值做限制)

	 int	m_nInSel;	//基准电流选择 0-高侧二次额定电流 1-设定值 2-设侧二次额定电流	平台模板没有，恒为0 用以计算INOM
	 float	m_fIbase;	//基准电流设定值
	int m_nSearchMode; //0二分法,1单步逼近
//	float m_fResultId;//给界面的差动电流
//	bool m_bResultJudge;//判据
//	float m_fTtrip;//保护动作时间
//	bool m_bJudge1;// 动作判据1
//	bool m_bJudge2;//动作判据2
//	int m_nRunSer;//测试序号,初值=1；
//	int m_nCurrentSerial;//测试项目列表序号。从0开始。
// 	float m_fIdiff1;//差动值1
// 	float m_fIdiff2;//差动值2
//	float m_fIdiff;//差动电流
	float m_fKjxh;//高压侧接线系数
	float m_fKjxl;//低压侧接线系数
	float m_fKph;
	float m_fKpl;//分别为高压侧和低压侧平衡系数
	float m_fKpm;


	bool m_bMinAxis;//=FALSE,TRUE,分别表示：有名值，标幺值
	int m_nAngleMode;//校正方式。0,1,2=无校正,△侧校正,Y侧校正;
	int m_nIbiasCal;//制动方程。0,1,2,3,4,5=(|I1-I2|)/K1或Ir=(|I1+I2|)/K1,(|I1|+|I2|*K2)/K1,max(|I1|,|I2|),(|Id-|I1|-|I2||)/K1,|I2|,√(K1*I1*I2*Cos(δ))
	int m_nWindH;//高压侧绕组接线型式,0,1="Y","△"
	int m_nWindM;//中压侧绕组接线型式,0,1="Y","△"
	int m_nWindL;//:低压侧绕组接线型式,0,1="Y","△"
	int m_nWindSide;//测试绕组，0,1,2=高低，高中，中低
	float m_fFactor1;//对应制动方程中的K1
	float m_fFactor2;//对应制动方程中的K2
	float m_fIet;//基准电流,当定值整定为有名值时,该值固定为1,当为标幺值时,该值需要进行折算
	int m_nConnectMode;//:测试绕组之间角差（钟点数）=0-12,"12点","1点","2点","3点","4点","5点","6点","7点","8点","9点","10点","11点"
	//    bool m_bConnectFactor;//FALSE,TRUE=不考虑绕组接线型式,考虑绕组接线型式;
	int m_nPhase;//:相别,0,1,2分别表示为A,B,C三相 ,3位ABC三相
	bool m_bCTStarPoint;//,CT极性，FALSE,TRUE分别表示为正极性和负极性
	int m_nKcal;//=0,1分别表示平衡系数自动计算和手动设置,手动设置平衡系数时，高中低压侧平衡系数分别为:Kph,Kpm和Kpl;
	int m_nJXFactor;//=0,1;分别是不考虑绕组接线型式和考虑绕组接线型
	float m_fSn;//变压器额定容量
	float m_fUh;//变压器高压侧额定电压
	float m_fUm;
	float m_fUl;
	//CT变比=CTPh/CTSh
	float m_fCTPh;
	float m_fCTSh;
	float m_fCTPm;
	float m_fCTSm;
	float m_fCTPl;
	float m_fCTSl;

	float m_fKpm_Set;// 手动计算用此系数
	float m_fKph_Set;
	float m_fKpl_Set;
// 	float m_fIbias1;
// 	float m_fIbias2;
	float m_fFreq;//当前频率

	int m_nRWCTconnect_ElecRailway;//地铁牵引变参数 高压侧CT接线方式
	int m_nTranSort_ElecRailway;//地铁牵引变参数   变压器接线形式
	int m_nKphMode_ElecRailway;//地铁牵引变参数    平衡系数计算方式
	float m_fKph_ElecRailway;//地铁牵引变中系数
};

