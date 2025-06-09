//CapAnalysisConfig.cpp  CCapAnalysisConfig
#include "stdafx.h"
#include "CapAnalysisConfig.h"
#include "../../../API/GlobalConfigApi.h"
#include "../../../API/FileApi.h"

/*
系统分析功能比较多，为了降低系统的CPU占有率，设置相关的功能开关
进行特定功能展示时，才执行相关的运算
*/

BOOL g_bSmartCap_RecordNow = FALSE; 
//zhouhj 2023.9.18 标记当前是否正在解析,防止多线程时,解析过程中,清空控制块
BOOL g_bIsParsingPkg = FALSE;

CCapAnalysisConfig g_oCapAnalysisConfig;

BSTR CCapAnalysisConfig::m_strCapAnalysisCfgKey = L"cap-analys-cfg";
BSTR CCapAnalysisConfig::m_strCT_PrimaryValueKey = L"ct-prim-value";
BSTR CCapAnalysisConfig::m_strCT_SecondValueKey = L"ct-second-value";
BSTR CCapAnalysisConfig::m_strPT_PrimaryValueKey = L"pt-prim-value";
BSTR CCapAnalysisConfig::m_strPT_SecondValueKey = L"pt-second-value";
BSTR CCapAnalysisConfig::m_strShowPrimaryValueKey = L"show-prim-value";


CCapAnalysisConfig::CCapAnalysisConfig()
{
	DisableAll();

// 	m_dCT_PrimaryValue = 1000.0f;
// 	m_dCT_SecondValue = 1.0f;
// 	m_dPT_PrimaryValue = 220.0f;
// 	m_dPT_SecondValue = 100.0f;
	m_nShowPrimaryValue = 1;

	for (int nIndex = 0;nIndex<6;nIndex++)
	{
		m_fCT_Rate[nIndex] = 2500;
		m_fPT_Rate[nIndex] = 2200;
	}
}

CCapAnalysisConfig::~CCapAnalysisConfig()
{
}

void CCapAnalysisConfig::DisableAll()
{
	m_bSmvSyncDelt = false;
	m_bAnalysisData_DelayTime = false;
	m_bAnalysisData_Complex = false;
	m_bAnalysisData_PhaseDelt = false;
	m_bMaxTimeDiscrete = false;
	m_bPkgConsistence = false;
	m_bGsAnalysis = false;

	m_bSvAnalysis = false;
	m_bMU_Test = false;
	m_bChQualitySpy = false;

	m_bSmv_AD = false;       //是否更新双AD数据集
	m_bSmv_Power = false;   //是否更新功率数据集
	m_bSmv_Vector = false;  //是否更新矢量图数据集
	m_bUseCapRecord = true;  //默认是使用CapRecord，做波形分析和计算是默认的，做异常分析可以不使用CapRecord（暂时这么定
	m_bStateValueChangedAnalysis = false;
}

void CCapAnalysisConfig::EnableRcdCal(long nEnable)
{
	g_nEnableCal_Root = nEnable;
}

void CCapAnalysisConfig::EnableRcdHarmCal(long nEnable)
{
	g_nEnableCal_Harm02Value  = nEnable ;
	g_nEnableCal_Harm03Value  = nEnable ;
	g_nEnableCal_Harm04Value  = nEnable ;
	g_nEnableCal_Harm05Value  = nEnable ;
	g_nEnableCal_Harm06Value  = nEnable ;
	g_nEnableCal_Harm07Value  = nEnable ;
	g_nEnableCal_Harm08Value  = nEnable ;
	g_nEnableCal_Harm09Value  = nEnable ;
	g_nEnableCal_Harm10Value  = nEnable ;
	g_nEnableCal_Harm11Value  = nEnable ;
	g_nEnableCal_Harm12Value  = nEnable ;
	g_nEnableCal_Harm13Value  = nEnable ;
	g_nEnableCal_Harm14Value  = nEnable ;
	g_nEnableCal_Harm15Value  = nEnable ;
	g_nEnableCal_Harm16Value  = nEnable ;
	g_nEnableCal_Harm17Value  = nEnable ;
	g_nEnableCal_Harm18Value  = nEnable ;
	g_nEnableCal_Harm19Value  = nEnable ;
	g_nEnableCal_Harm20Value  = nEnable ;
	g_nEnableCal_Harm21Value  = nEnable ;
	g_nEnableCal_Harm22Value  = nEnable ;
	g_nEnableCal_Harm23Value  = nEnable ;
	g_nEnableCal_Harm24Value  = nEnable ;
	g_nEnableCal_Harm25Value  = nEnable ;
}

void CCapAnalysisConfig::Smv_EffecValue()	//有效值
{
	DisableAll();
	EnableRcdCal(1);
	EnableRcdHarmCal(0);
}

void CCapAnalysisConfig::Smv_Wave()	//波形分析
{
	DisableAll();
	EnableRcdCal(1);
	EnableRcdHarmCal(0);
}

void CCapAnalysisConfig::Smv_Vector()	  //向量
{
	DisableAll();
	m_bSmv_Vector = true;
	EnableRcdCal(1);
	EnableRcdHarmCal(0);
}

void CCapAnalysisConfig::Smv_Sequence()	//序分量
{
	DisableAll();
	m_bSmv_Vector = true;
	EnableRcdCal(1);
	EnableRcdHarmCal(0);
}

void CCapAnalysisConfig::Smv_Power()	   //功率
{
	DisableAll();
	m_bSmv_Power = 1;
	EnableRcdCal(1);
	EnableRcdHarmCal(0);
}

void CCapAnalysisConfig::Smv_Harm()	//谐波
{
	DisableAll();
	EnableRcdCal(1);
	EnableRcdHarmCal(1);
}

void CCapAnalysisConfig::Smv_Polar()	   //极性
{
	DisableAll();
	EnableRcdCal(1);
	EnableRcdHarmCal(0);
}

void CCapAnalysisConfig::Smv_PkgError()	  //报文统计
{
	DisableAll();
	EnableRcdCal(0);
	EnableRcdHarmCal(0);
	m_bSvAnalysis = true;
	m_bUseCapRecord = false;
}

void CCapAnalysisConfig::Smv_AD()	  //双AD分析
{
	DisableAll();
	m_bSmv_AD = true;
	EnableRcdCal(1);
	EnableRcdHarmCal(0);
}

void CCapAnalysisConfig::Smv_PkgAnalyze()	  //报文分析
{
	DisableAll();
	EnableRcdCal(0);
	EnableRcdHarmCal(0);
	m_bPkgConsistence = true;
	m_bSvAnalysis = true;
}

void CCapAnalysisConfig::Smv_MUAccuracy()
{
	DisableAll();
	EnableRcdCal(1);
	EnableRcdHarmCal(0);
	m_bMU_Test = true;
	m_bAnalysisData_PhaseDelt = true;
	m_bAnalysisData_Complex = true;
	m_bAnalysisData_DelayTime = false;
//	m_bSvAnalysis = true;
}

void CCapAnalysisConfig::Smv_MUErrorStatistics()
{
	DisableAll();
	EnableRcdCal(1);
	EnableRcdHarmCal(0);
	m_bMU_Test = true;
	m_bAnalysisData_PhaseDelt = true;
	m_bAnalysisData_Complex = true;
	m_bAnalysisData_DelayTime = false;
//	m_bSvAnalysis = true;
}

void CCapAnalysisConfig::Smv_ChQualitySpy()
{
	DisableAll();
	EnableRcdCal(1);
	EnableRcdHarmCal(0);
	m_bChQualitySpy = true;
}

void CCapAnalysisConfig::Goose_RT()	//实时值
{
	DisableAll();
	EnableRcdCal(0);
	EnableRcdHarmCal(0);
	m_bGsAnalysis = true;
}

void CCapAnalysisConfig::FT3_RT()	//实时值
{
	DisableAll();
	EnableRcdCal(1);
	EnableRcdHarmCal(0);
	m_bGsAnalysis = true;
}

void CCapAnalysisConfig::FT3_OriginalMsg()	//原始报文
{
	DisableAll();
	EnableRcdCal(1);
	EnableRcdHarmCal(0);
	m_bGsAnalysis = true;
}

void CCapAnalysisConfig::Goose_TurnList()	  //变位列表
{
	DisableAll();
	EnableRcdCal(0);
	EnableRcdHarmCal(0);
	m_bGsAnalysis = true;
}

void CCapAnalysisConfig::Goose_PkgStc()	//报文统计
{
	DisableAll();
	EnableRcdCal(0);
	EnableRcdHarmCal(0);
	m_bGsAnalysis = true;
}

void CCapAnalysisConfig::Goose_PkgAnalyze()	//报文分析
{
	DisableAll();
	EnableRcdCal(0);
	EnableRcdHarmCal(0);
	m_bPkgConsistence = true;//20220607 zhouhj 
	m_bGsAnalysis = true;
}

void CCapAnalysisConfig::Goose_TurnSpy()	   //变位监视
{
	DisableAll();
	EnableRcdCal(0);
	EnableRcdHarmCal(0);
	m_bGsAnalysis = true;
}

long CCapAnalysisConfig::XmlReadOwn(CXmlRWNodeBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
// 	xml_GetElementText(m_strCT_PrimaryValueKey, oElement, m_dCT_PrimaryValue);
// 	xml_GetElementText(m_strCT_SecondValueKey, oElement, m_dCT_SecondValue);
// 	xml_GetElementText(m_strPT_PrimaryValueKey, oElement, m_dPT_PrimaryValue);
// 	xml_GetElementText(m_strPT_SecondValueKey, oElement, m_dPT_SecondValue);
	xml_GetElementText(m_strShowPrimaryValueKey, oElement, m_nShowPrimaryValue);
	return 0;
}

long CCapAnalysisConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
// 	xml_SetElementText(m_strCT_PrimaryValueKey, oXMLDoc, oElement, m_dCT_PrimaryValue);
// 	xml_SetElementText(m_strCT_SecondValueKey, oXMLDoc, oElement, m_dCT_SecondValue);
// 	xml_SetElementText(m_strPT_PrimaryValueKey, oXMLDoc, oElement, m_dPT_PrimaryValue);
// 	xml_SetElementText(m_strPT_SecondValueKey, oXMLDoc, oElement, m_dPT_SecondValue);
	xml_SetElementText(m_strShowPrimaryValueKey, oXMLDoc, oElement, m_nShowPrimaryValue);
	return 0;
}

BOOL CCapAnalysisConfig::Open()
{
	CString strFilePath;
	strFilePath = _P_GetConfigPath();
	strFilePath += _T("SttCapAnalisysCfg.xml");

	if (! IsFileExist(strFilePath))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("配置文件(%s)未查找到."),strFilePath.GetString());
		return FALSE;
	}

	return OpenXmlFile(strFilePath, m_strCapAnalysisCfgKey, NULL);
}

BOOL CCapAnalysisConfig::Save()
{
	CString strFilePath;
	strFilePath = _P_GetConfigPath();
	strFilePath += _T("SttCapAnalisysCfg.xml");
	return SaveXmlFile(strFilePath, NULL);
}

