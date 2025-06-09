#pragma once
#include "../../../BaseClass/ExBaseObject.h"

class CCapAnalysisConfig : public CExBaseObject
{
public:
	CCapAnalysisConfig();	
	virtual ~CCapAnalysisConfig();

public:
	bool m_bSmvSyncDelt;   // SV同步差
	bool m_bAnalysisData_DelayTime;  //SV延时
	bool m_bAnalysisData_Complex;  //复合误差
	bool m_bAnalysisData_PhaseDelt;  //角差
	bool m_bMaxTimeDiscrete; //SV离散度
	bool m_bPkgConsistence; //检查报文一致性
	bool m_bGsAnalysis;   // GS同步差
	bool m_bMU_Test;//20220618 zhouhj区分MU测试的相关测试项
	bool m_bChQualitySpy;//通道品质监视
	bool m_bStateValueChangedAnalysis;  //2024.5.29 chenling 状态量变化

	bool m_bSvAnalysis;  //是否执行报文分析：异常分析、一致性分析、延时等等

	bool m_bSmv_AD;       //是否更新双AD数据集
	bool m_bSmv_Power;   //是否更新功率数据集
	bool m_bSmv_Vector;  //是否更新矢量图数据集

	bool m_bUseCapRecord;  //2022-6-19  lijunqing 是否使用录波数据：即CapRecord是否起作用

// 	double m_dCT_PrimaryValue;//A//20220612 增加用于设置未进行IEC配置映射的变比
// 	double m_dCT_SecondValue;//A
// 	double m_dPT_PrimaryValue;//kV
// 	double m_dPT_SecondValue;//V
	long m_nShowPrimaryValue;

	double m_fCT_Rate[6];//zhouhj 20220812 CT变比值 与IEC配置中SV接收变比保持一致
	double m_fPT_Rate[6];//zhouhj 20220812 PT变比值 与IEC配置中SV接收变比保持一致

public:
	void DisableAll();
	void EnableRcdCal(long nEnable=1);
	void EnableRcdHarmCal(long nEnable=1);

	void Smv_EffecValue();	//有效值
	void Smv_Wave();	//波形分析
	void Smv_Vector();	  //向量
	void Smv_Sequence();	//序分量
	void Smv_Power();	   //功率
	void Smv_Harm();	//谐波
	void Smv_Polar();	   //极性
	void Smv_PkgError();	  //报文统计  2022-6-19  改为Error，增强可读性
	void Smv_AD();	  //双AD分析
	void Smv_PkgAnalyze();	  //报文分析
	void Smv_MUAccuracy();  //MU精确度
	void Smv_MUErrorStatistics();  //MU误差统计
	void Smv_ChQualitySpy();//通道品质监视

	void Goose_RT();	//实时值
	void Goose_TurnList();	  //变位列表
	void Goose_PkgStc();	//报文统计
	void Goose_PkgAnalyze();	//报文分析
	void Goose_TurnSpy();	   //变位监视

	void FT3_RT();	//实时值
	void FT3_OriginalMsg();	//原始报文

public:
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()	{      return m_strCapAnalysisCfgKey;	}

	BOOL Open();
	BOOL Save();

private:
	static BSTR m_strCapAnalysisCfgKey;
	static BSTR m_strCT_PrimaryValueKey;
	static BSTR m_strCT_SecondValueKey;
	static BSTR m_strPT_PrimaryValueKey;
	static BSTR m_strPT_SecondValueKey;
	static BSTR m_strShowPrimaryValueKey;


};


extern CCapAnalysisConfig g_oCapAnalysisConfig;
extern BOOL g_bSmartCap_RecordNow; 
extern BOOL g_bIsParsingPkg;

//2022-5-3  lijunqing enable harm cal  functions
extern long g_nEnableCal_Root;//  = 1 ;

extern long g_nEnableCal_Harm02Value;//  = 1 ;
extern long g_nEnableCal_Harm03Value;//  = 1 ;
extern long g_nEnableCal_Harm04Value;//  = 1 ;
extern long g_nEnableCal_Harm05Value;//  = 1 ;
extern long g_nEnableCal_Harm06Value;//  = 1 ;
extern long g_nEnableCal_Harm07Value;//  = 1 ;
extern long g_nEnableCal_Harm08Value;//  = 1 ;
extern long g_nEnableCal_Harm09Value;//  = 1 ;
extern long g_nEnableCal_Harm10Value;//  = 1 ;
extern long g_nEnableCal_Harm11Value;//  = 1 ;
extern long g_nEnableCal_Harm12Value;//  = 1 ;
extern long g_nEnableCal_Harm13Value;//  = 1 ;
extern long g_nEnableCal_Harm14Value;//  = 1 ;
extern long g_nEnableCal_Harm15Value;//  = 1 ;
extern long g_nEnableCal_Harm16Value;//  = 1 ;
extern long g_nEnableCal_Harm17Value;//  = 1 ;
extern long g_nEnableCal_Harm18Value;//  = 1 ;
extern long g_nEnableCal_Harm19Value;//  = 1 ;
extern long g_nEnableCal_Harm20Value;//  = 1 ;
extern long g_nEnableCal_Harm21Value;//  = 1 ;
extern long g_nEnableCal_Harm22Value;//  = 1 ;
extern long g_nEnableCal_Harm23Value;//  = 1 ;
extern long g_nEnableCal_Harm24Value;//  = 1 ;
extern long g_nEnableCal_Harm25Value;//  = 1 ;

