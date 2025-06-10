#pragma once

#include "../tmt_test_paras_head.h"
#include "../tmt_common_def.h"
#include "../SearchBase/tmt_search_base.h"
	
typedef struct tmt_diff_curr_paras :public tmt_SearchBase
{
	int		m_nTestType;	//测试类型，本参数需要在每个派生类中写死：	0-启动电流，1-比率制动，2-速断电流，3-2次谐波制动系数，4-动作时间，5-其他
	int		m_nTestMethod;	//测试模式 0-手动 1-自动
//	float	m_fReso;		//测试精度
// 	float	m_fDiffStart;	//差动搜索始值
// 	float	m_fDiffEnd;		//差动搜索终值
	float	m_fVg1;			//第一组电压常态输出值
	float	m_fVg2;			//第二组电压常态输出值
	float  m_fVg1_fault;  //第一组电压故障态输出值(故障相)
	float  m_fVg2_fault;  //第二组电压故障态输出值(故障相)
	float	m_fIdSetting;	//差动电流定值（测试无用，专供模板）

	//整定值
	BOOL	m_bMinAxis;	//定制整定方式 0-有名值 1-标幺值 平台模板没有，恒为1
	int		m_nInSel;	//基准电流选择 0-高侧二次额定电流 1-设定值 2-各侧二次额定电流	平台模板没有，恒为0 用以计算INOM
// 	float	m_fInom;	//基准电流（其他）5.000A  用以计算INOM 即平台的故障前电流
// 	float	m_fVnom;	//额定电压
// 	float	m_fFnom;	//额定频率
	float	m_fIbase;	//基准电流设定值

	float	m_fIsd;	//差动速断电流定值 1.500In或A		用以计算IBIAS，可无视
	float	m_fIcdqd;//差动动作电流门槛值 0.500In或A	用以计算IBIAS，可无视

	int m_nKneePoints;//拐点个数  //比率制动特性拐点数 1-1个拐点 2-两个拐点	0	用以计算IBIAS，可无视
	float m_fIp1;//比率制动特性拐点1电流
	float m_fIp2;//比率制动特性拐点1电流
	float m_fIp3;//比率制动特性拐点1电流
	float m_fKid0;//启动电流斜率
	float m_fKid1;//基波比率制动特性斜率1
	float m_fKid2;//基波比率制动特性斜率2
	float m_fKid3;//基波比率制动特性斜率3
	
	//启动电流斜率 0.000	用以计算特性曲线中的Id，可无视
	//基波比率制动特性斜率1 0.500	用以计算IBIAS，可无视
	//基波比率制动特性斜率2 0.700	用以计算IBIAS，可无视
	//速断电流斜率 0.000	用以计算特性曲线中的Id，可无视

	//通用参数
    float m_fPreTime;		//准备时间  0.000
	float m_fPreFaultTime;	//故障前时间 1.000
	float m_fFaultTime;		//故障时间 0.500
	float m_fAfterFaultTime;	//故障后持续时间

	int	  m_nKcal;			//各侧平衡系数 0-自动计算 1-手动计算并输入 0	用以计算KPH、KPL、CONNECTFACTOR 即平衡系数设置方式
	float m_fSN;			//变压器额定容量 31.500MVA	用以计算INOM INOMh INOMm INOMl
	float m_fUh;			//高压侧额定电压 110.000kV	用以计算KPH、KPL、INOM、INOMh
	float m_fUm;			//中压侧额定电压 38.5kV	用以计算KPH、KPL、INOM、INOMm
	float m_fUl;			//低压侧额定电压 10.500kV	用以计算KPH、KPL、INOM、INOMl
	float m_fKph;			//高压侧差动平衡系数 1.000	用以计算KPH
	float m_fKpm;			//中压侧差动平衡系数 0.936	用以计算KPH、KPL
	float m_fKpl;			//低压侧差动平衡系数 0.637	用以计算KPL
	int		m_nWindH;		//高压侧绕组接线形式 0-Y 1-△ 0	用以计算KPH、KPL
	int		m_nWindM;		//中压侧绕组接线形式 0-Y 1-△ 0	用以计算KPH、KPL
	int		m_nWindL;		//低压侧绕组接线形式 0-Y 1-△ 1 用以计算KPL
	int		m_nAngleMode;	//校正选择	0-无校正 1-△侧校正 2-Y侧校正  2	用以计算KPH、KPL AngleMode
	int		m_nWindSide;	//测试绕组	0-高-低  1-高-中    2-中-低    2	用以计算KPH、KPL
	int		m_nConnectMode;	//测试绕组之间角差（钟点数）0-11 12点、1点--11点  11 即平台的变压器接线组别
	int		m_nJXFactor;	//平衡系数计算方法	0-不考虑绕组接线型式  1-考虑绕组接线型式 0	用以计算KPH、KPL、CONNECTFACTOR
	//	int		m_nKpCalMode;	//补偿系数Kp计算方法 博电的计算方法是由AngleMode、JXFactor、WindSide、WindH、WindM、WindL决定的，故此值无效 
	//0-根据额定电压 Un 和 CT 变比归算至高压侧 1-根据额定电流 In' 归算至高压侧 2-标么值计算   //   周宏军 20200425  此参数未用到
	float	m_fInh,m_fInm,m_fInl;	//高中低压侧额定电流
	float	m_fCTh,m_fCTm,m_fCTl;	//高中低压侧CT变比
	// 	int		m_nSearchMode;	//搜索方法		0-二分法 1-单步逼近 0 平台模板中没有，应封装时处理
	BOOL	m_bCTStarPoint;	//CT极性0-两侧指向变压器 1-一侧指向变压器  平台模板好像没有，恒为0
	int		m_nIbiasCal;	//制动方程	0-Ir=(|I1-I2|)/K1或Ir=(|I1+I2|)/K1,1-Ir=(|I1|+|I2|*K2)/K1,2-Ir=max(|I1|,,|I2|)
	//,3-Ir=(|Id-|I1|-|I2||)/K1,4-Ir=|I2|,5-Sqrt(K1*I1*I2*Cos(δ)),		1
	float	m_fFactor1;		//K1				2
	float	m_fFactor2;		//K2				1
	int		m_nPhase;		//测试相 0-A,1-B,2-C,3-A,B,C	平台模板没有，恒为3 
	float	m_fVzAmp;			//Uz				57.740V

	//差动参数
	float	m_fIdiff;		//差动电流
	float	m_fIbias;		//制动电流

	// 谐波参数
	int		m_nHarmIndex;	//谐波制动次数选择，0-2值分别对应2次、3次和5次
	float	m_fCoefHarm2;			//二次谐波制动系数
	float	m_fCoefHarm3;			//三次谐波制动系数
	float	m_fCoefHarm5;			//五次谐波制动系数

	//上位机设置单用
	float m_fCTPh;			//高压侧CT一次值 300A	用以计算KPH、KPL、INOM、INOMh
	float m_fCTPm;			//中压侧CT一次值 800A	用以计算KPH、KPL、INOM、INOMm
	float m_fCTPl;			//低压侧CT一次值 2000A	用以计算KPH、KPL、INOM、INOMl
	float m_fCTSh;			//高压侧CT二次值 5A	用以计算KPH、KPL、INOM、INOMh
	float m_fCTSm;			//中压侧CT二次值 5A	用以计算KPH、KPL、INOM、INOMm
	float m_fCTSl;			//低压侧CT二次值 5A	用以计算KPH、KPL、INOM、INOMl

	//开关量
	tmt_BinaryIn  m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryIn  m_binInEx[MAX_ExBINARY_COUNT];
	tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];	
	tmt_BinaryOut m_binOutEx[MAX_ExBINARY_COUNT];
	int	m_nBinLogic;			//0-或 1-与
	int m_nAutoSearch;//是否自动搜索 (0:手动搜索;1:自动搜索)
	
	// 2022.5.12 caoxc
	char m_pszTestName[32];	//项目名称

    //xuzhantao240301
    float m_fPreFaultIp;//故障前电流
    tmt_channel m_uiVOL[2][6];	//(故障前+故障)*最大电压数6
    tmt_channel m_uiCUR[2][6];

    //Xuzhantao Pnv待处理
    int		m_nIdiffCal;	//Ir制动方程  0:Ir=|I1'-I2'|/K, 1:Ir=Max(|I1'|,|I2'|)*K, 2:Ir=|I2'|, 3:Ir=|Id-|I1'|-|I2'||,
                            //          4:Ir=(|I1'|+|I2'|)/K, 5:Ir=|Imax'-∑Ii'|/K, Ii'≠Imax', 6:Ir=√(－|I1'×I2'| * cosθ)
    int     m_nHarmPos;     //谐波施加侧  0：I1侧， 1：I2侧
    int     m_nY0CorrectMode;//保护内部零序修正方式  0：否 1：是
public:
	virtual void init()
	{
		tmt_SearchBase::InitSearch();
		m_nTestType = 0;	//默认测试启动电流
		m_nTestMethod = 1;
// 		m_fDiffStart = 0.700f;
// 		m_fDiffEnd = 1.300f;	
// 		m_fReso = 0.01f;
		m_fVg1=57.74f;
		m_fVg2=57.74f;
		m_fVg1_fault = 57.74;
		m_fVg2_fault = 57.74;
		m_fIdSetting = 1;

		m_nKneePoints = 1;
		m_fIp1 = 1.0f;
		m_fIp2 = 2.5f;
		m_fIp3 = 3.0f;
		m_fKid0 = 0.0f;
		m_fKid1 = 0.7f;
		m_fKid2 = 0.4f;
		m_fKid3 = 0.4f;

		m_bMinAxis = TRUE;
		m_nInSel = 0;
// 		m_fInom = 0.000f;
// 		m_fVnom = 57.74f;
// 		m_fFnom = 50.000f;
		m_fIbase = 5.000f;

		//通用参数
		m_fPreTime = 5.000f;
		m_fPreFaultTime = 1.000;
		m_fFaultTime = 0.500;
		m_nKcal = 0;
		m_fSN = 31.500;
		m_fUh = 110.000;
		m_fUm = 38.5;
		m_fUl = 10.500;	
		m_fKph = 1.000;
		m_fKpm = 0.936f;	
		m_fKpl = 0.637f;
		m_nWindH = 0;
		m_nWindM = 0;
		m_nWindL = 1;
		m_nAngleMode = 0;
		m_nWindSide = 0;
		m_nConnectMode = 11;
		m_nJXFactor = 0;
		m_bCTStarPoint = FALSE;
		m_nIbiasCal = 0;
		m_fFactor1 = 2.000f;
		m_fFactor2 = 1.000f;
		m_nPhase = 0;
// 		m_fDistinguish = 0.010f;
		m_fVzAmp = 57.740f;

		m_fInh = 1.0;
		m_fInm = 1.0;
		m_fInl = 1.0f;

		//差动参数
		m_fIdiff = 0.600f;
		m_fIbias = 1.200f;
		m_fIsd=5;
		m_fIcdqd=0.5;

		// 谐波参数
		m_nHarmIndex = 0;
		m_fCoefHarm2 = 0.15f;
		m_fCoefHarm3 = 0.12f;
		m_fCoefHarm5 = 0.11f;
		m_nAutoSearch = 1;

		//上位机单用
		m_fCTPh = 300;	
		m_fCTPm = 800;
		m_fCTPl = 2000;	
		m_fCTSh = 5.000;
		m_fCTSm = 5.000;
		m_fCTSl = 5.000;

		m_nBinLogic = 0;

		for (int i=0;i<MAX_BINARYIN_COUNT;i++)
		{
			m_binIn[i].init();
			m_binOut[i].init();
		}

        for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			m_binInEx[i].init();
		}

        for(int i = 0; i < g_nBoutExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			m_binOutEx[i].init();
		}

		//2022.5.24 caoxc 初始化项目名称
		memset(m_pszTestName, 0, 32);

        m_fPreFaultIp = 0;
        float fAngle[3]={0,-120,120};
        for(int i=0; i<2; i++)
        {
            for(int j=0; j<6; j++)
            {
                m_uiVOL[i][j].Harm[1].fAmp = 0;
                m_uiVOL[i][j].Harm[1].fAngle = fAngle[j%3];
                m_uiVOL[i][j].Harm[1].fFreq = 50;
            }
            for(int j=0; j<6; j++)
            {
                m_uiCUR[i][j].Harm[1].fAmp = 0;
                m_uiCUR[i][j].Harm[1].fAngle = fAngle[j%3];
                m_uiCUR[i][j].Harm[1].fFreq = 50;
            }
        }
	} 

}tmt_DiffCurrParas;

typedef struct tmt_diff_curr_results
{
	float	m_fIdiffActValue;	//差动电流动作值
	float	m_fIdiffSettingValue;	// 当前搜索的差动电流值
	float	m_fIbiasValue;	//制动电流
	float	m_fIrCoef;		//制动系数
	BOOL	m_bLastPoint;	//是否最后一个搜索点
	int		m_nZDRatioIndex;	//比例制动序号1 1-2 2 2-2 3 3-2 值：1 2 3 4 5 6 7 8
	int		m_rltBin[MAX_BINARYIN_COUNT];	//开入状态

	float	m_fTripTime;		//动作时间: 负值无效
	int		m_nActFlag;			//动作标志

	float	m_fI1Ie;
	float	m_fI1;
	float	m_fI2Ie;
	float	m_fI2;
	float	m_fIRbase[6];
	float	m_fIharm[6];

	//上位机用
	float   m_fRateKid; //比率制动系数

public:
	virtual void init()
	{
		m_fIdiffActValue = 0;	//差动电流
		m_fIdiffSettingValue = 0;
		m_fIbiasValue = 0;	//制动电流
		m_fIrCoef = 0;		//制动系数
		m_bLastPoint = 0;	//是否最后一个搜索点
		m_nZDRatioIndex = 0;	//比例制动序号1 1-2 2 2-2 3 3-2 值：1 2 3 4 5 6 7 8
		memset(m_rltBin, 0, MAX_BINARYIN_COUNT*sizeof(int));
		m_fTripTime = 0;			//动作时间: 负值无效
		m_nActFlag = 0;

		m_fI1 = 0;
		m_fI2 = 0;
		m_fI1Ie = 0;
		m_fI2Ie = 0;

		m_fRateKid = 0;

		for (int i=0;i<6;i++)
		{
			m_fIRbase[0] = m_fIharm[0] = 0;
		}
	} 

}tmt_DiffCurrResults;


typedef struct tmt_diff_curr_thr_test : public TMT_PARAS_HEAD // 差动启动电流测试
{
public:
	tmt_DiffCurrParas      m_oDiffCurrParas ;
	tmt_DiffCurrResults   m_oDiffCurrResults;
	int m_nThrType;		//0-启动电流；1-动作特性曲线

	virtual void init()
	{
		init_head(); //20210918 zhouhj
		strcpy(m_pszMacroID, STT_MACRO_ID_PsuDiffTCurrTest);
		m_nVersion = 0x00010001;
		m_nTestState = 0;

		m_oDiffCurrParas.init();
		m_oDiffCurrResults.init();
		m_nThrType = 0;
	}

	tmt_diff_curr_thr_test()	{init();}
	virtual void clear_result(){	m_oDiffCurrResults.init();	}
	virtual ~tmt_diff_curr_thr_test(){}
}tmt_DiffCurrThrTest;

typedef struct tmt_diff_curr_rate_test : public tmt_DiffCurrThrTest // 差动比率制动
{
public:
	int m_nRateType;		//0-启动段斜率；1、2-比率制动系数一；3、4-比率制动系数二；5、6-比率制动系数三；7、8-比率制动系数四；
	virtual void init()
	{
		tmt_DiffCurrThrTest::init();
		m_nRateType = 0;
		strcpy(m_pszMacroID, STT_MACRO_ID_PsuDiffRateTest);
	}

	tmt_diff_curr_rate_test()	{init();}
	virtual ~tmt_diff_curr_rate_test(){}
}tmt_DiffCurrRateTest;

typedef struct tmt_diff_curr_quick_test : public tmt_DiffCurrThrTest // 差动速断
{
public:
	virtual void init()
	{
		tmt_DiffCurrThrTest::init();
		strcpy(m_pszMacroID, STT_MACRO_ID_PsuDiffQuickTest);
	}

	tmt_diff_curr_quick_test()	{init();}
	virtual ~tmt_diff_curr_quick_test(){}
}tmt_DiffCurrQuickTest;

typedef struct tmt_diff_curr_harm_test : public tmt_DiffCurrThrTest // 谐波制动
{
public:
	virtual void init()
	{
		tmt_DiffCurrThrTest::init();
		strcpy(m_pszMacroID, STT_MACRO_ID_PsuDiffHarmTest);
	}

	tmt_diff_curr_harm_test()	{init();}
	virtual ~tmt_diff_curr_harm_test(){}
}tmt_DiffCurrHarmTest;

typedef struct tmt_diff_act_time_test : public tmt_DiffCurrThrTest // 差动动作时间
{
public:
	virtual void init()
	{
		tmt_DiffCurrThrTest::init();
		strcpy(m_pszMacroID, STT_MACRO_ID_PsuDiffTimeTest);
	}

	tmt_diff_act_time_test()	{init();}
	virtual ~tmt_diff_act_time_test(){}
}tmt_DiffActTimeTest;

//Xuzhantao20240227
typedef struct tmt_diff_6i_rate_pnv_test : public tmt_DiffCurrThrTest // 差动(6I)-比例制动搜索(PNV)
{
public:
    virtual void init()
    {
        init_head(); //20210918 zhouhj
        tmt_DiffCurrThrTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_Diff6IRateRestrainSearchTest);

    }
    tmt_diff_6i_rate_pnv_test()	{init();}
    virtual ~tmt_diff_6i_rate_pnv_test(){}
}tmt_Diff6IRatePnvTest;

//Xuzhantao20240401
typedef struct tmt_diff_6i_harm_pnv_test : public tmt_DiffCurrHarmTest // 差动(6I)-谐波制动搜索(PNV)
{
public:
    virtual void init()
    {
        init_head(); //20210918 zhouhj
        tmt_DiffCurrHarmTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_Diff6IHarmRestrainSearchTest);

    }
    tmt_diff_6i_harm_pnv_test()	{init();}
    virtual ~tmt_diff_6i_harm_pnv_test(){}
}tmt_Diff6IHarmPnvTest;

void stt_init_paras(tmt_DiffCurrParas *pParas);
void stt_init_results(tmt_DiffCurrResults *pResults);

void stt_xml_serialize_diff_search_results(tmt_DiffCurrParas *pParas, tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_thr(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_thr(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_rate(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_rate(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_quick(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_quick(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_harm(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_harm(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_acttime(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_acttime(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_6i_rate_pnv(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_6i_rate_pnv(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_6i_harm_pnv(tmt_DiffCurrParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_6i_harm_pnv(tmt_DiffCurrResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_DiffCurrThrTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_serialize(tmt_DiffCurrThrTest *pTests, CSttXmlSerializeBase *pXmlSerialize,BOOL bResultOnly);
