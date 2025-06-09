//CapAnalysisConfig.cpp  CCapAnalysisConfig
#include "stdafx.h"
#include "CapAnalysisConfig.h"
#include "../../../API/GlobalConfigApi.h"
#include "../../../API/FileApi.h"

/*
ϵͳ�������ܱȽ϶࣬Ϊ�˽���ϵͳ��CPUռ���ʣ�������صĹ��ܿ���
�����ض�����չʾʱ����ִ����ص�����
*/

BOOL g_bSmartCap_RecordNow = FALSE; 
//zhouhj 2023.9.18 ��ǵ�ǰ�Ƿ����ڽ���,��ֹ���߳�ʱ,����������,��տ��ƿ�
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

	m_bSmv_AD = false;       //�Ƿ����˫AD���ݼ�
	m_bSmv_Power = false;   //�Ƿ���¹������ݼ�
	m_bSmv_Vector = false;  //�Ƿ����ʸ��ͼ���ݼ�
	m_bUseCapRecord = true;  //Ĭ����ʹ��CapRecord�������η����ͼ�����Ĭ�ϵģ����쳣�������Բ�ʹ��CapRecord����ʱ��ô��
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

void CCapAnalysisConfig::Smv_EffecValue()	//��Чֵ
{
	DisableAll();
	EnableRcdCal(1);
	EnableRcdHarmCal(0);
}

void CCapAnalysisConfig::Smv_Wave()	//���η���
{
	DisableAll();
	EnableRcdCal(1);
	EnableRcdHarmCal(0);
}

void CCapAnalysisConfig::Smv_Vector()	  //����
{
	DisableAll();
	m_bSmv_Vector = true;
	EnableRcdCal(1);
	EnableRcdHarmCal(0);
}

void CCapAnalysisConfig::Smv_Sequence()	//�����
{
	DisableAll();
	m_bSmv_Vector = true;
	EnableRcdCal(1);
	EnableRcdHarmCal(0);
}

void CCapAnalysisConfig::Smv_Power()	   //����
{
	DisableAll();
	m_bSmv_Power = 1;
	EnableRcdCal(1);
	EnableRcdHarmCal(0);
}

void CCapAnalysisConfig::Smv_Harm()	//г��
{
	DisableAll();
	EnableRcdCal(1);
	EnableRcdHarmCal(1);
}

void CCapAnalysisConfig::Smv_Polar()	   //����
{
	DisableAll();
	EnableRcdCal(1);
	EnableRcdHarmCal(0);
}

void CCapAnalysisConfig::Smv_PkgError()	  //����ͳ��
{
	DisableAll();
	EnableRcdCal(0);
	EnableRcdHarmCal(0);
	m_bSvAnalysis = true;
	m_bUseCapRecord = false;
}

void CCapAnalysisConfig::Smv_AD()	  //˫AD����
{
	DisableAll();
	m_bSmv_AD = true;
	EnableRcdCal(1);
	EnableRcdHarmCal(0);
}

void CCapAnalysisConfig::Smv_PkgAnalyze()	  //���ķ���
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

void CCapAnalysisConfig::Goose_RT()	//ʵʱֵ
{
	DisableAll();
	EnableRcdCal(0);
	EnableRcdHarmCal(0);
	m_bGsAnalysis = true;
}

void CCapAnalysisConfig::FT3_RT()	//ʵʱֵ
{
	DisableAll();
	EnableRcdCal(1);
	EnableRcdHarmCal(0);
	m_bGsAnalysis = true;
}

void CCapAnalysisConfig::FT3_OriginalMsg()	//ԭʼ����
{
	DisableAll();
	EnableRcdCal(1);
	EnableRcdHarmCal(0);
	m_bGsAnalysis = true;
}

void CCapAnalysisConfig::Goose_TurnList()	  //��λ�б�
{
	DisableAll();
	EnableRcdCal(0);
	EnableRcdHarmCal(0);
	m_bGsAnalysis = true;
}

void CCapAnalysisConfig::Goose_PkgStc()	//����ͳ��
{
	DisableAll();
	EnableRcdCal(0);
	EnableRcdHarmCal(0);
	m_bGsAnalysis = true;
}

void CCapAnalysisConfig::Goose_PkgAnalyze()	//���ķ���
{
	DisableAll();
	EnableRcdCal(0);
	EnableRcdHarmCal(0);
	m_bPkgConsistence = true;//20220607 zhouhj 
	m_bGsAnalysis = true;
}

void CCapAnalysisConfig::Goose_TurnSpy()	   //��λ����
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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�����ļ�(%s)δ���ҵ�."),strFilePath.GetString());
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

