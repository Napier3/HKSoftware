#pragma once

#include "../tmt_test_paras_head.h"
#include "../tmt_common_def.h"
#include "../SearchBase/tmt_search_base.h"

#define FAULTLOCATION_HIGH_IN  0
#define FAULTLOCATION_HIGH_OUT  1
#define FAULTLOCATION_LOW_IN  2
#define FAULTLOCATION_LOW_OUT  3

typedef struct tmt_diff_cbop_paras
{
	int	    m_nFaultType;		//故障类型
	int     m_nErrorType;       //误差类型
	int	    m_nFaultLocation;	//故障点位置
	float	m_fCurrent;			//电流(A)
	float	m_fFreq;			//频率(Hz)

    float	m_fVg1;			//第一组电压输出值
    float	m_fVg2;			//第二组电压输出值

	//系统参数
    int  m_nKcal;               //是否设置平衡系数
    float	m_fSN;              //变压器额定容量
	float	m_fKph;				//变压器高压侧平衡系数
	float	m_fUh;				//变压器高压侧额定电压
    float	m_fInh;             //变压器高压侧额定电流
    float	m_fCTh;             //变压器高压侧CT变比
    float	m_fKpm;				//变压器中压侧平衡系数
    float	m_fUm;				//变压器中压侧额定电压
    float	m_fInm;             //变压器中压侧额定电流
    float	m_fCTm;             //变压器中压侧CT变比
    float	m_fKpl;				//变压器低压侧平衡系数
    float	m_fUl;				//变压器低压侧额定电压
    float	m_fInl;             //变压器低压侧额定电流
    float	m_fCTl;             //变压器低压侧CT变比

    float   m_fAbsErrSum;       //绝对误差(S) +
    float   m_fAbsErrReduce;    //绝对误差(S) -
    float	m_fRelErr;	        //相对误差

	//通用参数
	float   m_fPrepareTime;         //准备时间
	float   m_fPreFaultTime;	    //故障前时间
    float   m_fFaultTime;		    //故障时间
	float   m_fFaultTimeMargin;     //故障时间裕度
    float   m_fActionHoldTime;      //动作后保持时间
    int		m_nWindH;		//高压侧绕组接线形式 0-Y 1-△ 0	用以计算KPH、KPL
    int		m_nWindM;		//中压侧绕组接线形式 0-Y 1-△ 0	用以计算KPH、KPL
    int		m_nWindL;		//低压侧绕组接线形式 0-Y 1-△ 1 用以计算KPL
    int		m_nAngleMode;	//校正选择	0-无校正 1-△侧校正 2-Y侧校正  2	用以计算KPH、KPL AngleMode
    int		m_nWindSide;	//测试绕组	0-高-低  1-高-中    2-中-低    2	用以计算KPH、KPL
    int	    m_nAroundClockNumHM;	//高-中绕组钟点数//
	int	    m_nAroundClockNumHL;	//高-低绕组钟点数
	int	    m_nBalanceTerms;		//平衡系数计算
	BOOL	m_bCTStarPoint;		    //CT极性0-两侧指向变压器 1-一侧指向变压器  平台模板好像没有，恒为0
    int	    m_nIbiasCal;	        //制动方程 0-Ir=(|I1-I2|)/K1或Ir=(|I1+I2|)/K1,1-Ir=(|I1|+|I2|*K2)/K1,2-Ir=max(|I1|s,|I2|)
    //,3-Ir=(|Id-|I1|-|I2||)/K1,4-Ir=|I2|,5-Sqrt(K1*I1*I2*Cos(δ))
	float	m_fFactor1;				//K1
	float	m_fFactor2;				//K2
    int	    m_nComBineFeature;		//组合特性
    int	    m_nEarthing;			//接地
	BOOL    m_bCBSimulation;		//断路器模拟  S1=不模拟,S2=模拟 0(0:不模拟,1:模拟)
	float   m_fCBTripTime;			//分闸时间
	float   m_fCBCloseTime;			//合闸时间
	int	    m_nCoordinate;			//坐标
    int		m_nInSel;	//基准电流选择 0-高侧二次额定电流 1-设定值 2-各侧二次额定电流	平台模板没有，恒为0 用以计算INOM
    float	m_fIbase;	//基准电流设定值

	//开关量设置
    int  m_nBinLogic; //0 1逻辑与或
    int  m_binIn[MAX_BINARYIN_COUNT];
    int  m_binOut[2][MAX_BINARYOUT_COUNT];

public:
	virtual void init()
	{
        //tmt_SearchBase::InitSearch();

		m_nFaultType = 0;		//故障类型
		m_nFaultLocation = 0;	//故障点位置 0-高压侧（区内）1-高压侧（区外）2-低压侧（区内）3-低压侧（区外）
		m_nErrorType = 0;      //误差类型
		m_fCurrent = 5.000f;			//电流(A)
		m_fFreq = 50.000f;			//频率(Hz)
        m_fVg1=57.74f;
        m_fVg2=57.74f;

		//系统参数
		m_fKph = 1.000f;				//变压器高压侧平衡系数
		m_fUh = 110.000f;				//变压器高压侧额定电压
        m_fInh = 10.000f;               //变压器高压侧额定电流
        m_fCTl  = 300.000f;             //变压器高压侧CT变比
		m_fKpm = 0.936f;				//变压器中压侧平衡系数
		m_fUm = 38.500f;				//变压器中压侧额定电压
        m_fInm = 7.000f;                //变压器中压侧额定电流
        m_fCTm  = 800.000f;             //变压器中压侧CT变比
		m_fKpl = 0.637f;				//变压器低压侧平衡系数
		m_fUl = 10.500f;				//变压器低压侧额定电压
        m_fCTl  = 5.000f;               //变压器低压侧额定电流
        m_fCTl  = 800.000f;             //变压器中压侧CT变比
        m_fSN = 31.500f;                //变压器额定容量

		m_fAbsErrSum   = 0.002f;		//绝对误差(S) +
		m_fAbsErrReduce= 0.001f;		//绝对误差(S) -
		m_fRelErr      = 0.02f;	        //相对误差

		//通用参数
		m_fPrepareTime  = 0.000f;        //准备时间
		m_fPreFaultTime =0.500f;	     //故障前时间
        m_fFaultTime =0.500f;
		m_fFaultTimeMargin = 0.500f;     //故障时间裕度
		m_fActionHoldTime = 0.500f;      //动作后保持时间	 
        m_nWindH = 0;
        m_nWindM = 0;
        m_nWindL = 1;
        m_nAngleMode = 0;
        m_nWindSide = 0;
		m_nAroundClockNumHM = 1;	     //高-中绕组钟点数
		m_nAroundClockNumHL = 1;	     //高-低绕组钟点数
		m_nBalanceTerms = 1;		     //平衡系数计算
		m_bCTStarPoint = 1;				 //CT极性
		m_nIbiasCal = 1;				 //制动方程 0-Ir=(|I1-I2|)/K1或Ir=(|I1+I2|)/K1,1-Ir=(|I1|+|I2|*K2)/K1,2-Ir=max(|I1|,,|I2|)
		m_fFactor1 = 2;					 //K1
		m_fFactor2 = 1;					 //K2
		m_nComBineFeature = 1;			 //组合特性
		m_nEarthing = 1;				 //接地
		m_bCBSimulation = 0;			 //断路器模拟  S1=不模拟,S2=模拟 0(0:不模拟,1:模拟)
		m_fCBTripTime  = 100.000f;		 //分闸时间
		m_fCBCloseTime = 100.000f;		 //合闸时间
		m_nCoordinate  = 0;				 //坐标
        m_nInSel = 0;
        m_fIbase = 5.000f;

		//开关量设置
		m_nBinLogic = 0; //0 - 或 1 - 与

		for(int i = 0;i < MAX_BINARYOUT_COUNT; i++)
		{
			m_binIn[i] = 0;
			for (int j = 0;j < 2; j++)
			{
				m_binOut[i][j] = 0;
			}
		}
	}

}tmt_DiffCBOpParas;

typedef struct tmt_diff_cbop_results
{
    float	m_fTripTime;		//动作时间
    int		m_nActFlag;			//动作标志
public:
	virtual void init()
	{
        m_fTripTime = 0.0f;
        m_nActFlag = 0;
    }
}tmt_DiffCBOpResults;


typedef struct tmt_diff_cbop_Test  : public TMT_PARAS_HEAD
{
public:
	tmt_DiffCBOpParas       m_oDiffProtectionParas;
	tmt_DiffCBOpResults     m_oDiffProtectionResults;

    virtual void init()
    {
        init_head();
        strcpy(m_pszMacroID, STT_MACRO_ID_DiffCBOp);
        m_nVersion = 0x00010001;
        m_nTestState = 0;

        m_oDiffProtectionParas.init();
        m_oDiffProtectionResults.init();
    }

    tmt_diff_cbop_Test()	{init();}
    virtual void clear_result(){	m_oDiffProtectionResults.init();	}
    virtual ~tmt_diff_cbop_Test(){}


}tmt_DiffCBOpTest;

void stt_init_paras(tmt_DiffCBOpParas *pParas);
void stt_init_results(tmt_DiffCBOpResults *pResults);

void stt_xml_serialize(tmt_DiffCBOpParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_write_DiffCBOp();
void stt_xml_serialize(tmt_DiffCBOpResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_diff_cbop_Test *pTests, CSttXmlSerializeBase *pXmlSerialize);
