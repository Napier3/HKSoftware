#include "StdAfx.h"
#include "X61850CapBase.h"
#include "../../Api/MathApi.h"

#include "61850Cap/CapDevice/CapDevice91.h"
#include "61850Cap/CapDevice/CapDevice6044.h"
#include "61850Cap/CapDevice/CapDeviceGoose.h"
#include "61850Cap/SttRcdComtradeFileWrite.h"
#include "../API/GlobalConfigApi.h"

#include "../../61850/Module/AT02DTool/AT02D_Tool.h"
#include "XSttRcdInitChDvmData.h"
#include "../../61850/Module/CfgDataMngr/IecCfg92ChIn.h"
#include <math.h>
//#define  TESTFLAG  //南瑞客户演示使用
// #define PT 2200  //20220812 zhouhj 删除此宏定义,改为成员变量方式
// #define CT 2500


//2020-06-21  lijunqing  设备数据模型访问互斥对象，避免程序崩溃
CAutoCriticSection g_oCapDvmAutoCriticSection;
_61850CapMUErrorRanges g_oMuErrorRanges;//合并单元测试角差、比差、复合误差的合格判据
_61850CapMUErrorRanges g_oADMUErrorRanges;//admu自动测试角差、比差的合格判据

int g_nUseCustomMUTestRpt = 0;//是否自定义测试报告,即设置测试报告使用的测试次数,自定义每次测试的间隔时间
int g_nMURptTestCount = 10;//采自定义测试次数时,合并单元测试几次生成报告
float g_fMUTestTimeEach = 0.5;//每次测试用时(s)
long g_nMuTimeTest_UseNoPPS = 0;
long g_nIsFirstCWTest = 0;

// CString g_strListHarmAmp[30] = {_T("Ua1"), _T("Ub1"), _T("Uc1"), _T("Ua2"), _T("Ub2")};
// CString g_strListHarmAng[30];

#ifndef _PSX_IDE_QT_
CSmDbConfig *g_pCapSmDbConfig = NULL;
#endif

CDvmValue* dvm_FindAddByID(CDvmData *pCurrData,const CString &strID,double dValue)
{
	if (pCurrData == NULL)
	{
		return NULL;
	}

	CDvmValue *pFindValue = (CDvmValue*)pCurrData->FindByID(strID);

	if (pFindValue == NULL)
	{
		pFindValue = new CDvmValue;
		pCurrData->AddNewChild(pFindValue);
		pFindValue->m_strID = strID;
		pFindValue->m_strName = strID;
		pFindValue->m_strValue.Format(_T("%.3lf"),dValue);// = strDefaultValue;
	}

	return pFindValue;
}

CDvmValue* dvm_FindAddByID(CDvmValue *pCurrValue,const CString &strID,const CString &strDefaultValue)
{
	if (pCurrValue == NULL)
	{
		return NULL;
	}

	CDvmValue *pFindValue = (CDvmValue*)pCurrValue->FindByID(strID);

	if (pFindValue == NULL)
	{
		pFindValue = new CDvmValue;
		pCurrValue->AddNewChild(pFindValue);
		pFindValue->m_strID = strID;
		pFindValue->m_strName = strID;
		pFindValue->m_strValue = strDefaultValue;
	}

	return pFindValue;
}

//////////////////////////////////////////////////_61850CapMUErrorRanges////////////////////////////////////////////////////////////////////////////////////////////////////////////
void _61850CapMUErrorRanges::InitNormal()//通用的初始化标准,即额定电压、额定电流时的误差判据
{
	//电流通道初始化
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Prot5P30].m_dStdError[MUAccuracy_ErrorType_RatError] = 0.01f;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Prot5P30].m_dStdError[MUAccuracy_ErrorType_AngError] = 60.0f;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Prot5P30].m_dStdError[MUAccuracy_ErrorType_CompError] = 0.05f;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Prot5P30].m_nErrorCalType[MUAccuracy_ErrorType_RatError] = 1;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Prot5P30].m_nErrorCalType[MUAccuracy_ErrorType_AngError] = 0;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Prot5P30].m_nErrorCalType[MUAccuracy_ErrorType_CompError] = 1;

	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Prot5P].m_dStdError[MUAccuracy_ErrorType_RatError] = 0.01f;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Prot5P].m_dStdError[MUAccuracy_ErrorType_AngError] = 60.0f;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Prot5P].m_dStdError[MUAccuracy_ErrorType_CompError] = 0.05f;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Prot5P].m_nErrorCalType[MUAccuracy_ErrorType_RatError] = 1;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Prot5P].m_nErrorCalType[MUAccuracy_ErrorType_AngError] = 0;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Prot5P].m_nErrorCalType[MUAccuracy_ErrorType_CompError] = 1;

	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Prot10P].m_dStdError[MUAccuracy_ErrorType_RatError] = 0.03f;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Prot10P].m_dStdError[MUAccuracy_ErrorType_AngError] = 120.0f;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Prot10P].m_dStdError[MUAccuracy_ErrorType_CompError] = 0.1f;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Prot10P].m_nErrorCalType[MUAccuracy_ErrorType_RatError] = 1;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Prot10P].m_nErrorCalType[MUAccuracy_ErrorType_AngError] = 0;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Prot10P].m_nErrorCalType[MUAccuracy_ErrorType_CompError] = 1;

	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_1].m_dStdError[MUAccuracy_ErrorType_RatError] = 0.001f;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_1].m_dStdError[MUAccuracy_ErrorType_AngError] = 5.0f;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_1].m_dStdError[MUAccuracy_ErrorType_CompError] = -1.0f;//代表不做误差判断
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_1].m_nErrorCalType[MUAccuracy_ErrorType_RatError] = 1;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_1].m_nErrorCalType[MUAccuracy_ErrorType_AngError] = 0;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_1].m_nErrorCalType[MUAccuracy_ErrorType_CompError] = 1;

	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_2S].m_dStdError[MUAccuracy_ErrorType_RatError] = 0.002f;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_2S].m_dStdError[MUAccuracy_ErrorType_AngError] = 10.0f;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_2S].m_dStdError[MUAccuracy_ErrorType_CompError] = -1.0f;//代表不做误差判断
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_2S].m_nErrorCalType[MUAccuracy_ErrorType_RatError] = 1;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_2S].m_nErrorCalType[MUAccuracy_ErrorType_AngError] = 0;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_2S].m_nErrorCalType[MUAccuracy_ErrorType_CompError] = 1;

	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_2].m_dStdError[MUAccuracy_ErrorType_RatError] = 0.002f;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_2].m_dStdError[MUAccuracy_ErrorType_AngError] = 10.0f;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_2].m_dStdError[MUAccuracy_ErrorType_CompError] = -1.0f;//代表不做误差判断
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_2].m_nErrorCalType[MUAccuracy_ErrorType_RatError] = 1;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_2].m_nErrorCalType[MUAccuracy_ErrorType_AngError] = 0;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_2].m_nErrorCalType[MUAccuracy_ErrorType_CompError] = 1;

	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_5S].m_dStdError[MUAccuracy_ErrorType_RatError] = 0.005f;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_5S].m_dStdError[MUAccuracy_ErrorType_AngError] = 30.0f;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_5S].m_dStdError[MUAccuracy_ErrorType_CompError] = -1.0f;//代表不做误差判断
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_5S].m_nErrorCalType[MUAccuracy_ErrorType_RatError] = 1;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_5S].m_nErrorCalType[MUAccuracy_ErrorType_AngError] = 0;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_5S].m_nErrorCalType[MUAccuracy_ErrorType_CompError] = 1;

	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_5].m_dStdError[MUAccuracy_ErrorType_RatError] = 0.005f;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_5].m_dStdError[MUAccuracy_ErrorType_AngError] = 30.0f;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_5].m_dStdError[MUAccuracy_ErrorType_CompError] = -1.0f;//代表不做误差判断
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_5].m_nErrorCalType[MUAccuracy_ErrorType_RatError] = 1;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_5].m_nErrorCalType[MUAccuracy_ErrorType_AngError] = 0;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_5].m_nErrorCalType[MUAccuracy_ErrorType_CompError] = 1;

	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas1].m_dStdError[MUAccuracy_ErrorType_RatError] = 0.01f;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas1].m_dStdError[MUAccuracy_ErrorType_AngError] = 60.0f;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas1].m_dStdError[MUAccuracy_ErrorType_CompError] = -1.0f;//代表不做误差判断
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas1].m_nErrorCalType[MUAccuracy_ErrorType_RatError] = 1;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas1].m_nErrorCalType[MUAccuracy_ErrorType_AngError] = 0;
	m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas1].m_nErrorCalType[MUAccuracy_ErrorType_CompError] = 1;


	//电压通道初始化
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Prot3P].m_dStdError[MUAccuracy_ErrorType_RatError] = 0.03f;
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Prot3P].m_dStdError[MUAccuracy_ErrorType_AngError] = 120.0f;
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Prot3P].m_dStdError[MUAccuracy_ErrorType_CompError] = -1.0f;//代表不做误差判断
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Prot3P].m_nErrorCalType[MUAccuracy_ErrorType_RatError] = 1;
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Prot3P].m_nErrorCalType[MUAccuracy_ErrorType_AngError] = 0;
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Prot3P].m_nErrorCalType[MUAccuracy_ErrorType_CompError] = 1;

	m_oVolChRange[IECCFG_VOLCH_AccLevel_Prot6P].m_dStdError[MUAccuracy_ErrorType_RatError] = 0.06f;
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Prot6P].m_dStdError[MUAccuracy_ErrorType_AngError] = 240.0f;
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Prot6P].m_dStdError[MUAccuracy_ErrorType_CompError] = -1.0f;//代表不做误差判断
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Prot6P].m_nErrorCalType[MUAccuracy_ErrorType_RatError] = 1;
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Prot6P].m_nErrorCalType[MUAccuracy_ErrorType_AngError] = 0;
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Prot6P].m_nErrorCalType[MUAccuracy_ErrorType_CompError] = 1;

	m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas0_1].m_dStdError[MUAccuracy_ErrorType_RatError] = 0.001f;
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas0_1].m_dStdError[MUAccuracy_ErrorType_AngError] = 5.0f;
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas0_1].m_dStdError[MUAccuracy_ErrorType_CompError] = -1.0f;//代表不做误差判断
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas0_1].m_nErrorCalType[MUAccuracy_ErrorType_RatError] = 1;
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas0_1].m_nErrorCalType[MUAccuracy_ErrorType_AngError] = 0;
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas0_1].m_nErrorCalType[MUAccuracy_ErrorType_CompError] = 1;

	m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas0_2].m_dStdError[MUAccuracy_ErrorType_RatError] = 0.002f;
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas0_2].m_dStdError[MUAccuracy_ErrorType_AngError] = 10.0f;
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas0_2].m_dStdError[MUAccuracy_ErrorType_CompError] = -1.0f;//代表不做误差判断
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas0_2].m_nErrorCalType[MUAccuracy_ErrorType_RatError] = 1;
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas0_2].m_nErrorCalType[MUAccuracy_ErrorType_AngError] = 0;
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas0_2].m_nErrorCalType[MUAccuracy_ErrorType_CompError] = 1;

	m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas0_5].m_dStdError[MUAccuracy_ErrorType_RatError] = 0.005f;
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas0_5].m_dStdError[MUAccuracy_ErrorType_AngError] = 20.0f;
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas0_5].m_dStdError[MUAccuracy_ErrorType_CompError] = -1.0f;//代表不做误差判断
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas0_5].m_nErrorCalType[MUAccuracy_ErrorType_RatError] = 1;
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas0_5].m_nErrorCalType[MUAccuracy_ErrorType_AngError] = 0;
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas0_5].m_nErrorCalType[MUAccuracy_ErrorType_CompError] = 1;

	m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas1].m_dStdError[MUAccuracy_ErrorType_RatError] = 0.01f;
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas1].m_dStdError[MUAccuracy_ErrorType_AngError] = 40.0f;
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas1].m_dStdError[MUAccuracy_ErrorType_CompError] = -1.0f;//代表不做误差判断
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas1].m_nErrorCalType[MUAccuracy_ErrorType_RatError] = 1;
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas1].m_nErrorCalType[MUAccuracy_ErrorType_AngError] = 0;
	m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas1].m_nErrorCalType[MUAccuracy_ErrorType_CompError] = 1;
}


void _61850CapMUErrorRanges::InitADMUNormal()
{
	//电流通道初始化
	//ADMU
	m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Meas0_5S].m_dStdError[MUAccuracy_ErrorType_RatError] = 0.005f;
	m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Meas0_5S].m_dStdError[MUAccuracy_ErrorType_AngError] = 30.0f;
	m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Meas0_5S].m_dStdError[MUAccuracy_ErrorType_CompError] = -1.0f;
	m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Meas0_5S].m_nErrorCalType[MUAccuracy_ErrorType_RatError] = 1;
	m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Meas0_5S].m_nErrorCalType[MUAccuracy_ErrorType_AngError] = 0;
	m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Meas0_5S].m_nErrorCalType[MUAccuracy_ErrorType_CompError] = 1;

	m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Meas1S].m_dStdError[MUAccuracy_ErrorType_RatError] = 0.01f;
	m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Meas1S].m_dStdError[MUAccuracy_ErrorType_AngError] = 60.0f;
	m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Meas1S].m_dStdError[MUAccuracy_ErrorType_CompError] = -1.0f;
	m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Meas1S].m_nErrorCalType[MUAccuracy_ErrorType_RatError] = 1;
	m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Meas1S].m_nErrorCalType[MUAccuracy_ErrorType_AngError] = 0;
	m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Meas1S].m_nErrorCalType[MUAccuracy_ErrorType_CompError] = 1;

	m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Prot5P10].m_dStdError[MUAccuracy_ErrorType_RatError] = 0.005f;
	m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Prot5P10].m_dStdError[MUAccuracy_ErrorType_AngError] = 30.0f;
	m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Prot5P10].m_dStdError[MUAccuracy_ErrorType_CompError] = -1.0f;
	m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Prot5P10].m_nErrorCalType[MUAccuracy_ErrorType_RatError] = 1;
	m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Prot5P10].m_nErrorCalType[MUAccuracy_ErrorType_AngError] = 0;
	m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Prot5P10].m_nErrorCalType[MUAccuracy_ErrorType_CompError] = 1;


	m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Prot5P30].m_dStdError[MUAccuracy_ErrorType_RatError] = 0.01f;
	m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Prot5P30].m_dStdError[MUAccuracy_ErrorType_AngError] = 60.0f;
	m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Prot5P30].m_dStdError[MUAccuracy_ErrorType_CompError] = -1.0f;
	m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Prot5P30].m_nErrorCalType[MUAccuracy_ErrorType_RatError] = 1;
	m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Prot5P30].m_nErrorCalType[MUAccuracy_ErrorType_AngError] = 0;
	m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Prot5P30].m_nErrorCalType[MUAccuracy_ErrorType_CompError] = 1;


	m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_Meas0_5].m_dStdError[MUAccuracy_ErrorType_RatError] = -0.01f;
	m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_Meas0_5].m_dStdError[MUAccuracy_ErrorType_AngError] = -1.0f;
	m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_Meas0_5].m_dStdError[MUAccuracy_ErrorType_CompError] = -1.0f;
	m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_Meas0_5].m_nErrorCalType[MUAccuracy_ErrorType_RatError] = 1;
	m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_Meas0_5].m_nErrorCalType[MUAccuracy_ErrorType_AngError] = 0;
	m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_Meas0_5].m_nErrorCalType[MUAccuracy_ErrorType_CompError] = 1;

	m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_Meas1].m_dStdError[MUAccuracy_ErrorType_RatError] = -0.01f;
	m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_Meas1].m_dStdError[MUAccuracy_ErrorType_AngError] = -1.0f;
	m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_Meas1].m_dStdError[MUAccuracy_ErrorType_CompError] = -1.0f;
	m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_Meas1].m_nErrorCalType[MUAccuracy_ErrorType_RatError] = 1;
	m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_Meas1].m_nErrorCalType[MUAccuracy_ErrorType_AngError] = 0;
	m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_Meas1].m_nErrorCalType[MUAccuracy_ErrorType_CompError] = 1;

	m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_PhaseProt3P].m_dStdError[MUAccuracy_ErrorType_RatError] = 0.005f;
	m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_PhaseProt3P].m_dStdError[MUAccuracy_ErrorType_AngError] = 30.0f;
	m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_PhaseProt3P].m_dStdError[MUAccuracy_ErrorType_CompError] = 0.05f;
	m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_PhaseProt3P].m_nErrorCalType[MUAccuracy_ErrorType_RatError] = -1.0f;
	m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_PhaseProt3P].m_nErrorCalType[MUAccuracy_ErrorType_AngError] = 0;
	m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_PhaseProt3P].m_nErrorCalType[MUAccuracy_ErrorType_CompError] = 1;


	m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_ZeroSeqProt3P].m_dStdError[MUAccuracy_ErrorType_RatError] = 0.01f;
	m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_ZeroSeqProt3P].m_dStdError[MUAccuracy_ErrorType_AngError] = 60.0f;
	m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_ZeroSeqProt3P].m_dStdError[MUAccuracy_ErrorType_CompError] = -1.0f;
	m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_ZeroSeqProt3P].m_nErrorCalType[MUAccuracy_ErrorType_RatError] = 1;
	m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_ZeroSeqProt3P].m_nErrorCalType[MUAccuracy_ErrorType_AngError] = 0;
	m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_ZeroSeqProt3P].m_nErrorCalType[MUAccuracy_ErrorType_CompError] = 1;
}
//////////////////////////////////////////////////CX61850CapBase////////////////////////////////////////////////////////////////////////////////////////////////////////////

CX61850CapBase::CX61850CapBase(void)
{
	m_pProtocol61850 = NULL;
	m_bIsZeroDriftTest = FALSE;
	m_dZeroDrift_Un = 57.74f;
	m_dZeroDrift_In = 1.0f;
//	m_dDelayCompens_NoPPS = 0.0f;
	g_oMuErrorRanges.InitNormal();

	m_strDatasetMapID_MUTestCB = CAP_DATASET_MAP_ID_dsSV1;

#ifdef _XSmartCap_use_SmDb_
	m_pSmDbWriteThread = NULL;
	m_pCapFrameDbFileServer = NULL;
	m_pCapFrameDbFileClient = NULL;
#endif

	m_pFrameMemBufferMngr = NULL;

	m_pIecCfgDevice = NULL;
	m_pRecordTestCalThread = NULL;
	m_pDvmDevice = NULL;
	m_pDataset_MUTestCB  = NULL ;
	m_pDataset_Discrete  = NULL ;
	m_pDataset_THD  = NULL ;
	m_pDataset_SVErr  = NULL ;
	m_pDataset_GSErr = NULL;
	m_pDataset_SV_PkgAnalyze = NULL;
	m_pDataset_SV_His = NULL;
	m_pDataset_GS_PkgAnalyze = NULL;
	m_pDataset_RcdStepResponse = NULL;
	m_pDataset_RcdStep6U6I = NULL;
	m_pDataset_Gin1 = NULL;
	m_pDataset_IEDTest = NULL;
	m_pDataset_Time = NULL;
	m_pDataset_MUTimeRlt = NULL;
	m_pDataset_CurrErrorRange = NULL;
	m_pDataset_ErrorRanges = NULL;
	m_pDataset_StateValueChangedRlt = NULL;
	m_pDataset_TestFunSelect = NULL;

	::memset(m_dwDvmSvChannels, 0x0, sizeof(DWORD) * MAX_RTVARIABLES);

	g_pSmartCapSoeCycleArray = &m_oSoeCycleArray;
	g_pSmartCapBinCycleArray = &m_oBinCycleArray;
	::memset(m_destIn, 0x0, 100);
	::memset(m_destOut, 0x0, 50);

	m_pUpdateDvmDatasThread = NULL;
	m_nHasUpdateSVDelayData = 0;

	m_dTimeMaxValue  = 0;
	m_dTimeMinValue  = 0;
	m_dTimeCurrValue  = 0;
	m_dTimeFirstValue = 0;
	m_nFirstDataFlag = 0;

	::memset(m_oStdSrcDatas_FirstCW, 0x0, sizeof(m_oStdSrcDatas_FirstCW));
	m_bFirstCWDatasChanged = false;
	m_bIsFT3ADMU = false;
}

CX61850CapBase::~CX61850CapBase(void)
{
	m_oRecordDevice.RemoveAll();
}


void CX61850CapBase::CreateCapTrhead()
{

}

void CX61850CapBase::ChangeChRecordState(CCapDeviceChBase *pCh, long nState)
{
	m_oCapDeviceChRecordMngr.ChangeChRecordState(pCh, nState);
}

void CX61850CapBase::RecordDevice_Reset()
{
	m_oRecordDevice.RemoveAll();
	m_oCapDeviceChRecordMngr.RemoveAll();
}

//2022-4-14  lijunqing
void CX61850CapBase::GetSttCapParas(CDataGroup *pSttParas, BOOL bUseSmv, BOOL bUseGoose,BOOL bUseFT3)
{
	m_oCapDeviceAll.GetSttCapParas(pSttParas, bUseSmv, bUseGoose,bUseFT3);
}

#ifdef _XSmartCap_use_SmDb_
void CX61850CapBase::InitCapSmDb()
{
	ASSERT (m_pCapFrameDbFileServer != NULL && m_pCapFrameDbFileClient != NULL);

	if (m_pCapFrameDbFileServer == NULL || m_pCapFrameDbFileClient == NULL)
	{
		return;
	}

	CString strFile = EpCap_GetCapDbConfigFile();
	m_oSmDbConfig.OpenXmlFile(strFile, CSmDbConfigXmlRWKeys::g_pXmlKeys);
	g_pCapSmDbConfig = &m_oSmDbConfig; //历史报文索引配置全局变量赋值

	m_pCapFrameDbFileServer->CreateCapFrameDbServer();
	CCapFrameDbFile::CreateCapFrameArea(*m_pCapFrameDbFileClient);
}
#endif

//2022-5-2  lijunqing  清空Cap相关的内容
void CX61850CapBase::ClearCap()
{
	::memset(m_dwDvmSvChannels, 0x0, sizeof(DWORD) * MAX_RTVARIABLES);

	//检测、探测到的全部装置
	m_oCapDeviceAll.ClearCap();

	 //录波的装置
	m_oRecordDevice.RemoveAll();

	//抓包波形显示通道管理，以及RecordTest
	m_oCapDeviceChRecordMngr.ClearCap();

	//设备数据模型
	m_pDvmDevice->DeleteAll();
	ClearDatasetsMap();//20220813 zhouhj 删除时,清空关联指针
	MUTimeTestRlt_AddDataset();
}


void CX61850CapBase::ClearPara()
{
	::memset(m_dwDvmSvChannels, 0x0, sizeof(DWORD) * MAX_RTVARIABLES);

	m_oCapDeviceAll.ClearPara();
}


BOOL CX61850CapBase::BeginCap(CIecCfgDatasMngr *pIecfgDataMngr,BOOL bClearDevices)
{
	ASSERT (FALSE);
	return TRUE;
}

BOOL CX61850CapBase::StopCap()
{
	return TRUE;
}

void CX61850CapBase::BeginRecord()
{
	m_oCapDeviceChRecordMngr.InitRecordTest();
	g_bSmartCap_RecordNow = TRUE;
}

void CX61850CapBase::StopRecord()
{
	g_bSmartCap_RecordNow = FALSE;
}

BOOL CX61850CapBase::IsCapExit()
{
	ASSERT (FALSE);

	return TRUE;
}


BOOL CX61850CapBase::CanClose()
{
	if (!IsCapExit())
	{
		return FALSE;
	}

#ifndef _PSX_IDE_QT_
	if (m_pSmDbWriteThread != NULL)
	{
		if (!m_pSmDbWriteThread->WaitForExit())
		{
			return FALSE;
		}
	}
#endif

	return TRUE;
}


BOOL CX61850CapBase::IsInCapture()
{
	ASSERT (FALSE);
	return FALSE;
}


void CX61850CapBase::FreeCapture()
{

}

void CX61850CapBase::ExitInstance()
{
	FreeCapture();

	if (m_pProtocol61850 != NULL)
	{
		delete m_pProtocol61850;
		m_pProtocol61850 = NULL;
	}

#ifdef _XSmartCap_use_SmDb_
	if (m_pCapFrameDbFileServer != NULL)
	{
		delete m_pCapFrameDbFileServer;
		m_pCapFrameDbFileServer = NULL;
	}

	if (m_pCapFrameDbFileClient != NULL)
	{
		delete m_pCapFrameDbFileClient;
		m_pCapFrameDbFileClient = NULL;
	}
#endif
}

void CX61850CapBase::RecordDevice(CCapDeviceBase *pDevice)
{
	if (pDevice->m_bSelect == 0)
	{//如果没有选择，则不处理
		return;
	}

	if (m_oRecordDevice.Find(pDevice) != NULL)
	{
		return;
	}

	m_oRecordDevice.AddTail(pDevice);
	m_oCapDeviceChRecordMngr.RecordDevice(pDevice);
}

void CX61850CapBase::RecordDevices()
{
	POS pos = m_oCapDeviceAll.GetHeadPosition();
	CCapDeviceBase *pDevice = NULL;

	while (pos != NULL)
	{
		pDevice = (CCapDeviceBase *)m_oCapDeviceAll.GetNext(pos);
		RecordDevice(pDevice);
	}
}

void CX61850CapBase::InitDvmDevice(CCapDeviceBase *pCapDevice)
{
	if (m_pDvmDevice == NULL)
	{
		return;
	}

	CDvmDataset *pRefDataset = pCapDevice->GetDvmDataset();

	if (pRefDataset != NULL)
	{//如果已经关联，则返回
		if (pRefDataset->GetCount() == 0)
		{
			pCapDevice->CreateDvmDataset(pRefDataset);
		}

		return;
	}

	CDvmLogicDevice *pLDevice = GetLogicalDevice(TRUE);
	CDvmDataset *pDataset = GetDataset(pLDevice, pCapDevice->m_strID);
	
	if (pDataset->GetCount() > 0)
	{//已经创建数据集
		pCapDevice->SetDvmDataset(pDataset);
		return;
	}

/*
	if (pDataset->GetCount() == pCapDevice->GetCount())
	{//2022-5-7  lijunqing  去掉通道不相等的判断  可能会有问题
		//即：实际的通道与配置的通道不一致
		return;
	}
*/

	pCapDevice->CreateDvmDataset(pDataset);
}

void CX61850CapBase::InitDvmDevices()
{
	CCapDeviceBase *pCapDevice = NULL;
	POS pos = m_oCapDeviceAll.GetHeadPosition();

	while (pos != NULL)
	{
		pCapDevice = (CCapDeviceBase *)m_oCapDeviceAll.GetNext(pos);
		InitDvmDevice(pCapDevice);
	}

	IecAnalysis_AddDatasets();
}

void CX61850CapBase::InitDvmDevices(CIecCfgDatasMngr *pDatasMngr)
{
	if (m_pDvmDevice == NULL)
	{
		return;
	}

	CDvmLogicDevice *pLDevice = GetLogicalDevice(TRUE);
	iec_GenDeviceModel(pDatasMngr, pLDevice, TRUE);
}

void CX61850CapBase::InitDvmDevices_BySmvInGin(CIecCfgDatasMngr *pDatasMngr,BOOL bhasMUTestParas)
{
	if (m_pDvmDevice == NULL)
	{
		return;
	}

	CDvmLogicDevice *pLDevice = GetLogicalDevice(TRUE);
	iec_GenDeviceModel_BySmvInGin(pDatasMngr, pLDevice, TRUE,bhasMUTestParas);
}

CDvmDataset* CX61850CapBase::GetDataset(CDvmLogicDevice *pLDevice, const CString &strID)
{
	CDvmDataset *pFind = (CDvmDataset*)pLDevice->FindByID(strID);

	if (pFind == NULL)
	{
		pFind = new CDvmDataset();
		pLDevice->AddNewChild(pFind);
		pFind->m_strID = strID;
		pFind->m_strName = strID;
	}

	return pFind;
}

CDvmDataset* CX61850CapBase::FindDataset(const CString &strDatasetID)
{
	if (m_pDvmDevice == NULL)
	{
		return NULL;
	}

	CDvmLogicDevice *pFind = NULL;
	pFind = (CDvmLogicDevice*)m_pDvmDevice->FindByClassID(DVMCLASSID_CDVMLOGICDEVICE);

	if (pFind == NULL)
	{
		return NULL;
	}

	return (CDvmDataset*)pFind->FindByID(strDatasetID);
}

CDvmData* CX61850CapBase::GetMU_TimeAccurRltData()
{
	if (m_pDataset_SVDelay == NULL)
	{
		return NULL;
	}

	CString strSVX_Data;

	if (m_strDatasetMapID_MUTestCB.GetLength()>2)
	{
		strSVX_Data = m_strDatasetMapID_MUTestCB.Mid(2);
	} 
	else
	{
		strSVX_Data = _T("SV1");
	}

	CDvmData *pDelayData = (CDvmData*)m_pDataset_SVDelay->FindByID(strSVX_Data/*_T("SV1")*/);
	return pDelayData;
}

BOOL CX61850CapBase::SetName_DvmData(const CString &strDatasetID,const CString &strDataID,const CString &strDataName)
{
	CDvmLogicDevice *pLD = GetLogicalDevice(FALSE);

	if (pLD == NULL)
	{
		return FALSE;
	}

	CDvmDataset *pDataset = (CDvmDataset*)pLD->FindByID(strDatasetID);

	if (pDataset == NULL)
	{
		return FALSE;
	}

	CDvmData *pData = (CDvmData*)pDataset->FindByID(strDataID);

	if (pData == NULL)
	{
		return FALSE;
	}

	pData->m_strName = strDataName;
	return TRUE;
}

CDvmLogicDevice* CX61850CapBase::GetLogicalDevice(BOOL bNew)
{
	CDvmLogicDevice *pFind = NULL;
	pFind = (CDvmLogicDevice*)m_pDvmDevice->FindByClassID(DVMCLASSID_CDVMLOGICDEVICE);

	if (pFind == NULL)
	{
		if (bNew)
		{
			pFind = new CDvmLogicDevice();
			m_pDvmDevice->AddNewChild(pFind);
			pFind->m_strID = _T("IecRcd");
			pFind->m_strName = pFind->m_strID;
		}
	}

	return pFind;
}

void CX61850CapBase::RecordAllDevice(BOOL bRcdGoose)
{
	POS pos = m_oCapDeviceAll.GetHeadPosition();
	CCapDeviceBase *pCapDevice = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pCapDevice = (CCapDeviceBase *)m_oCapDeviceAll.GetNext(pos);
		nClassID = pCapDevice->GetClassID();

		if (nClassID == CPDCLASSID_DEVICEGOOSE)
		{
			if (bRcdGoose)
			{
				RecordDevice(pCapDevice);
			}

			//pCapDevice->SetCapSelect(TRUE);
		}
		else
		{
			RecordDevice(pCapDevice);
		}
	}
}

BOOL CX61850CapBase::IsAppIDSame(CIecCfgDataBase *pDataBase)
{
	CCapDeviceBase *pCapDevice = NULL;

	DWORD dwCfgAppID = 0;
	UINT nClassID = pDataBase->GetClassID();

	if (nClassID == CFGCLASSID_CIECCFGGOUTDATA)
	{
		dwCfgAppID = ((CIecCfgGooseDataBase*)pDataBase)->m_dwAppID;
	}
	else if(nClassID == CFGCLASSID_CIECCFG92DATA)
	{
		dwCfgAppID = ((CIecCfg92Data*)pDataBase)->m_dwAppID;
	}
	else if(nClassID == CFGCLASSID_CIECCFG91DATA)
	{
		dwCfgAppID = ((CIecCfg91Data*)pDataBase)->m_dwAppID;
	}

	POS pos = m_oCapDeviceAll.GetHeadPosition();

	while (pos)
	{
		pCapDevice = (CCapDeviceBase*)m_oCapDeviceAll.GetNext(pos);
		if (pCapDevice->m_dwAppID == dwCfgAppID)
		{
			return TRUE;
		}
	}

	return FALSE;
}

void CX61850CapBase::RemoveCapDevices()
{	
	m_oCapDeviceAll.DeleteAll();	

	if (m_pDvmDevice != NULL)
	{
		m_pDvmDevice->DeleteAll();
		ClearDatasetsMap();//20220813 zhouhj 删除时,清空关联指针
		MUTimeTestRlt_AddDataset();
	}
}

CCapDeviceBase* CX61850CapBase::GetMUTestCapDevice()
{
	CCapDeviceBase *pSelCapDevice = (CCapDeviceBase*)m_oCapDeviceAll.FindByID(m_strDatasetMapID_MUTestCB);
	return pSelCapDevice;
}

void CX61850CapBase::UpdateCapDevicesRecordSmvChRates()
{
	if (m_oCapDeviceChRecordMngr.m_pRecordTest == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("m_oCapDeviceChRecordMngr.m_pRecordTest == NULL."));
		return;
	}

	BOOL bSmartCap_RecordNow = g_bSmartCap_RecordNow;//更新前记录是否录波状态

	if (g_bSmartCap_RecordNow)//如果正在录波,则停止录波
	{
		g_bSmartCap_RecordNow = FALSE;
	}
	
	CCapDeviceBase *pCapDevice92 = NULL;
	POS pos_dev = m_oCapDeviceAll.GetHeadPosition();
	CCapDeviceBase *pCapDeviceBase = NULL;
	CCapDeviceSmvCh *pSmvCh = NULL;
	POS pos_ch = NULL;
	CRecordTest *pRecordTest = m_oCapDeviceChRecordMngr.m_pRecordTest;
	long nChIndex = 0;

	while (pos_dev != NULL)
	{
		pCapDeviceBase = (CCapDeviceBase*)m_oCapDeviceAll.GetNext(pos_dev);

		if ((pCapDeviceBase->GetClassID() == CPDCLASSID_DEVICE92)&&(pCapDeviceBase->m_bSelect))
		{
			pos_ch = pCapDeviceBase->GetHeadPosition();

			while (pos_ch != NULL)
			{
				pSmvCh = (CCapDeviceSmvCh *)pCapDeviceBase->GetNext(pos_ch);
				pSmvCh->InitAfterSetChType();
				nChIndex = pRecordTest->m_pVariables->GetChIndexByID(pSmvCh->m_strID);

				if (nChIndex >= 0)
				{
					pRecordTest->g_pCoefValue[nChIndex] = pSmvCh->m_fChRate;
					pRecordTest->m_pVariables->InitCalFuncPara(nChIndex);
				}
				else
				{
					CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("当前CCapDevice92设备的通道(%s)对应的录波通道未查找成功."),pSmvCh->m_strID.GetString());
				}
			}

			pCapDeviceBase->SetDeviceChMaps();
		}
	}

	g_bSmartCap_RecordNow = bSmartCap_RecordNow;
}

void CX61850CapBase::UpdateAfterMUChsSet()
{
	BOOL bSmartCap_RecordNow = g_bSmartCap_RecordNow;//更新前记录是否录波状态

	if (g_bSmartCap_RecordNow)//如果正在录波,则停止录波
	{
		g_bSmartCap_RecordNow = FALSE;
	}

	//更新通道描述\准确级
	if (m_pDataset_MUTestCB != NULL)
	{
		CDvmData *pCurrChData = NULL;
		POS pos = m_pDataset_MUTestCB->GetHeadPosition();
		CCapDeviceBase *pCapDeviceBase = (CCapDeviceBase*)m_oCapDeviceAll.FindByID(m_strDatasetMapID_MUTestCB);

		if (pCapDeviceBase != NULL)
		{
			CIecCfgDataBase *pIecCfgData = pCapDeviceBase->GetIecCfgData();

			if (pIecCfgData != NULL)
			{
				CIecCfgChsBase *pCfgChs = pIecCfgData->m_pCfgChs;
				CCapDeviceSmvCh *pDevCh = NULL;
				CIecCfgDataChBase *pIecCfgDataCh = NULL;
				long nIndex = 0;

				while(pos)
				{
					pCurrChData = (CDvmData *)m_pDataset_MUTestCB->GetNext(pos);
					pIecCfgDataCh = (CIecCfgDataChBase*)pCfgChs->FindByID(pCurrChData->m_strID);

					pDevCh = (CCapDeviceSmvCh*)pCapDeviceBase->FindByID(pCurrChData->m_strID);

					if ((pDevCh != NULL)&&(pIecCfgDataCh != NULL))
					{
						pDevCh->m_strName = pIecCfgDataCh->m_strName;
						pDevCh->m_nSelect = pIecCfgDataCh->m_nUseFlag;
						pCurrChData->m_strName = pIecCfgDataCh->m_strName;
						pCurrChData->m_nChange = pDevCh->m_nSelect;

						if (pIecCfgDataCh->GetClassID() == CFGCLASSID_CIECCFG92CHIN)
						{
							CIecCfg92ChIn *pCfg92ChIn = (CIecCfg92ChIn*)pIecCfgDataCh;
							pDevCh->m_nAccurLevel = pCfg92ChIn->m_nAccuratyLevel;
							pCurrChData->m_nIndex = pDevCh->m_nAccurLevel;
						}
					}

					nIndex++;
				}
			}
		}
	}

	//更新CT、PT变比
	if (m_oCapDeviceChRecordMngr.m_pRecordTest != NULL)
	{
		CCapDeviceBase *pCapDevice92 = NULL;
		POS pos_dev = m_oCapDeviceAll.GetHeadPosition();
		CCapDeviceBase *pCapDeviceBase = NULL;
		CCapDeviceSmvCh *pSmvCh = NULL;
		POS pos_ch = NULL;
		CRecordTest *pRecordTest = m_oCapDeviceChRecordMngr.m_pRecordTest;
		long nChIndex = 0;

		while (pos_dev != NULL)
		{
			pCapDeviceBase = (CCapDeviceBase*)m_oCapDeviceAll.GetNext(pos_dev);

			if ((pCapDeviceBase->GetClassID() == CPDCLASSID_DEVICE92)&&(pCapDeviceBase->m_bSelect))
			{
				pos_ch = pCapDeviceBase->GetHeadPosition();

				while (pos_ch != NULL)
				{
					pSmvCh = (CCapDeviceSmvCh *)pCapDeviceBase->GetNext(pos_ch);
					pSmvCh->InitAfterSetChType();
					nChIndex = pRecordTest->m_pVariables->GetChIndexByID(pSmvCh->m_strID);

					if (nChIndex >= 0)
					{
						pRecordTest->g_pCoefValue[nChIndex] = pSmvCh->m_fChRate;
						pRecordTest->m_pVariables->InitCalFuncPara(nChIndex);
					}
					else
					{
						CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("当前CCapDevice92设备的通道(%s)对应的录波通道未查找成功."),pSmvCh->m_strID.GetString());
					}
				}
			}
		}
	}

	g_bSmartCap_RecordNow = bSmartCap_RecordNow;
}

void CX61850CapBase::AddCapDevice(CIecCfgDataBase *pDataBase)
{
	CCapDeviceBase *pDevice = NULL;
	UINT nClassID = 0;

 	if (pDataBase->m_nUseFlag == 0)//20220601 生成数据集时,只关联勾选控制块,此处需保持一致
 	{
 		return;
 	}

	nClassID = pDataBase->GetClassID();

	if ((nClassID == CFGCLASSID_CIECCFG92DATA)||(nClassID == CFGCLASSID_CIECCFG92INPUTDATA))
	{
		pDevice = new CCapDevice92;
		pDevice->m_nType = PROTOCOL_61850_TYPE_92;
	}

	m_oCapDeviceAll.AddNewChild(pDevice);
	pDevice->SetChannelNum(pDataBase->m_nChannelNum);
	pDevice->AttachIecCfgData(pDataBase);
}

void CX61850CapBase::AddCapDevices(CIecCfgDatasBase *pDatasBase)
{
	CIecCfgDataBase *pDataBase = NULL;
	CCapDeviceBase *pDevice = NULL;
	UINT nClassID = 0;

	POS pos = pDatasBase->GetHeadPosition();
	while (pos)
	{
		pDevice = NULL;
		pDataBase = (CIecCfgDataBase*)pDatasBase->GetNext(pos);

		if (!pDatasBase->IsCfgData(pDataBase))
		{
			continue;
		}

		if (IsAppIDSame(pDataBase))
		{
			continue;
		}

		if (pDataBase->m_nUseFlag == 0)//20220601 生成数据集时,只关联勾选控制块,此处需保持一致
		{
			continue;
		}

		nClassID = pDataBase->GetClassID();

		if ((nClassID == CFGCLASSID_CIECCFG92DATA)||(nClassID == CFGCLASSID_CIECCFG92INPUTDATA))
		{
			pDevice = new CCapDevice92;
			pDevice->m_nType = PROTOCOL_61850_TYPE_92;
		}
		else if(nClassID == CFGCLASSID_CIECCFG91DATA)
		{
			pDevice = new CCapDevice91;
			pDevice->m_nType = PROTOCOL_61850_TYPE_91;
		}
		else if((nClassID == CFGCLASSID_CIECCFG6044COMMONDATA)||(nClassID == CFGCLASSID_CIECCFG6044COMMONINDATA))
		{
			pDevice = new CCapDevice6044;
			pDevice->m_nType = PROTOCOL_61850_TYPE_6044;
		}
		else if ((nClassID == CFGCLASSID_CIECCFGGOUTDATA)||(nClassID == CFGCLASSID_CIECCFGGINDATA))
		{
			pDevice = new CCapDeviceGoose;
			pDevice->m_nType = PROTOCOL_61850_TYPE_GOOSE;
		}

		if(pDevice == NULL)
		{
			continue;
		}

		m_oCapDeviceAll.AddNewChild(pDevice);
		pDevice->SetChannelNum(pDataBase->m_nChannelNum);
		pDevice->AttachIecCfgData(pDataBase);
	}
}

void CX61850CapBase::AddCapDevices(CIecCfgDatasMngr *pDatasMngr)		//更新配置
{
	ASSERT(pDatasMngr != NULL);
	if (pDatasMngr == NULL)
	{
		return;
	}

	CIecCfgDatasSMV *pSmvMngr = (CIecCfgDatasSMV*)pDatasMngr->GetSmvMngr();
	//	CIecCfgGinDatas *pGinMngr = (CIecCfgGinDatas*)pDatasMngr->GetGinMngr();
	CIecCfgGoutDatas *pGoutMngr = (CIecCfgGoutDatas*)pDatasMngr->GetGoutMngr();

	AddCapDevices(pSmvMngr);
	//	AddCapDevices(pGinMngr);
	AddCapDevices(pGoutMngr);
}

void CX61850CapBase::AddCapDevices_BySmvInGin(CIecCfgDatasMngr *pDatasMngr)		//更新配置
{
	ASSERT(pDatasMngr != NULL);
	if (pDatasMngr == NULL)
	{
		return;
	}

	CIecCfgDatasSmvIn *pSmvInMngr = (CIecCfgDatasSmvIn*)pDatasMngr->GetSmvInMngr();
	CIecCfgGinDatas *pGinMngr = (CIecCfgGinDatas*)pDatasMngr->GetGinMngr();

	AddCapDevices(pSmvInMngr);
	AddCapDevices(pGinMngr);
}

void CX61850CapBase::LoadCapDevices(CIecCfgDevice *pIecCfgDevice)		//更新设备
{
	ASSERT(pIecCfgDevice != NULL);
	if (pIecCfgDevice == NULL)
	{
		return;
	}

	RemoveCapDevices();

	m_pIecCfgDevice = pIecCfgDevice;
	CIecCfgDatasMngr *pDatasMngr = NULL;

	POS pos = pIecCfgDevice->GetHeadPosition();
	while (pos)
	{
		pDatasMngr = (CIecCfgDatasMngr*)pIecCfgDevice->GetNext(pos);
		AddCapDevices(pDatasMngr);
	}
#ifndef _USE_NO_GUI_
	g_theCapDeviceMngrMsgRcvWnd->XPostMessage(WM_UPDATECAPDEVICES, (WPARAM)&m_oCapDeviceAll, (LPARAM)&m_oCapDeviceAll);
#endif
}

CIecCfgDatasMngr* CX61850CapBase::GetDatasMngr(const CString& strIecfgDataID)
{
	return (CIecCfgDatasMngr*)m_pIecCfgDevice->FindByID(strIecfgDataID);
}

void CX61850CapBase::SetDvmDevice(CDvmDevice *pDevice)
{
	m_pDvmDevice = pDevice;
	ASSERT (m_pDvmDevice != NULL);

	if (m_pDvmDevice == NULL)
	{
		return;
	}

	AttachDatasets();
}

void CX61850CapBase::AttachDatasets()
{
	POS pos = m_oCapDeviceAll.GetHeadPosition();
	CCapDeviceBase *pDevice = NULL;

	while (pos != NULL)
	{
		pDevice = (CCapDeviceBase *)m_oCapDeviceAll.GetNext(pos);

		if (((pDevice->GetClassID() == CPDCLASSID_DEVICE92)||(pDevice->GetClassID() == CPDCLASSID_DEVICE6044))
			&&(pDevice->m_bSelect))
		{
			m_strDatasetMapID_MUTestCB = pDevice->m_strID;
			break;
		}
	}

	DvmFindDataset(m_strDatasetMapID_MUTestCB/*CAP_DATASET_MAP_ID_dsSV1*/, &m_pDataset_MUTestCB);// 2020-8-17 mym 放开 
	DvmFindDataset(CAP_DATASET_MAP_ID_DISCRETE, &m_pDataset_Discrete);
	DvmFindDataset(CAP_DATASET_MAP_ID_SVERR, &m_pDataset_SVErr);
	DvmFindDataset(CAP_DATASET_MAP_ID_GSERR, &m_pDataset_GSErr);
	DvmFindDataset(CAP_DATASET_MAP_ID_SVCSTC, &m_pDataset_SV_PkgAnalyze);
	DvmFindDataset(CAP_DATASET_MAP_ID_SVHis, &m_pDataset_SV_His);
	DvmFindDataset(CAP_DATASET_MAP_ID_GOCSTC, &m_pDataset_GS_PkgAnalyze);
	DvmFindDataset(CAP_DATASET_MAP_ID_THD, &m_pDataset_THD);
	DvmFindDataset(CAP_DATASET_MAP_ID_SVINST, &m_pDataset_SVInst);
	DvmFindDataset(CAP_DATASET_MAP_ID_SVDELAY, &m_pDataset_SVDelay);

	//2020-06-26  添加报告数据集
	DvmFindDataset(CAP_DATASET_MAP_ID_Report, &m_pDataset_Report);

	// mym add 20202-6-29 SV同步差；
	DvmFindDataset(CAP_DATASET_MAP_ID_SVSYN, &m_pDataset_SVSyncDelt);

	// mym add 20202-6-29 GOOSE同步差；
	DvmFindDataset(CAP_DATASET_MAP_ID_GSSYN, &m_pDataset_GSSyncDelt);

	//lijunqing 2020-07-25  控制块的连接状态
	DvmFindDataset(CAP_DATASET_MAP_ID_LinkState, &m_pDataset_LinkState);

	DvmFindDataset(CAP_DATASET_MAP_ID_RcdStep6U6I, &m_pDataset_RcdStep6U6I);

	DvmFindDataset(CAP_DATASET_MAP_ID_RcdStepResponse, &m_pDataset_RcdStepResponse);
	DvmFindDataset(CAP_DATASET_MAP_ID_IEDTest, &m_pDataset_IEDTest);
	DvmFindDataset(CAP_DATASET_MAP_ID_GIN1, &m_pDataset_Gin1);
	DvmFindDataset(CAP_DATASET_MAP_ID_MUTime, &m_pDataset_Time);
	DvmFindDataset(CAP_DATASET_MAP_ID_dsMUTimeRlt, &m_pDataset_MUTimeRlt);
	DvmFindDataset(CAP_DATASET_MAP_ID_dsCurrErrorRange, &m_pDataset_CurrErrorRange);
	DvmFindDataset(CAP_DATASET_MAP_ID_dsErrorRanges, &m_pDataset_ErrorRanges);
	DvmFindDataset(CAP_DATASET_MAP_ID_dsStateValueChangedRlt, &m_pDataset_StateValueChangedRlt);
	DvmFindDataset(CAP_DATASET_MAP_ID_TestFunSelect, &m_pDataset_TestFunSelect);


	//GetU_IParamValue(m_U_B,  m_I_B,   m_U_P,  m_I_P);
}

void CX61850CapBase::DvmFindDataset(const CString &strDatasetID, CDvmDataset **ppDataset)
{
	*ppDataset = m_pDvmDevice->FindDataset(strDatasetID);

	if (*ppDataset == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("DvmFile Error, Dataset [%s] not exist"), strDatasetID.GetString());
	}
}


//更新DvmDevice的数据  lijunqing 2020-6-17
void CX61850CapBase::UpdateDvmDeviceDatas()
{
#ifndef _PSX_QT_LINUX_
	//数据访问的互斥  2020-06-21  lijunqing
	CAutoSimpleLock Lock(g_oCapDvmAutoCriticSection);
#endif

	UpdateDvmDeviceDatas_RecordTest();
	UpdateDvmDeviceDatas_Analysis();

	UpdateDvmDeviceDatas_SOE();
	UpdateDvmDeviceDatas_BIN();
}


void CX61850CapBase::UpdateDvmDeviceDatas_Analysis()
{
	//2020-07-25  lijunqing  链接状态
	UpdateDvmDeviceDatas_LinkState();

	//离散度检验；
	UpdateDvmDeviceDatas_Analysis_Discrete();

	//SMV 9-2异常模拟检验
	if (g_oCapAnalysisConfig.m_bSvAnalysis || g_oCapAnalysisConfig.m_bMU_Test)
	{
		UpdateDvmDeviceDatas_PkgError_92(); 
	}

	// GOOSE异常模拟检验；
	if (g_oCapAnalysisConfig.m_bGsAnalysis)
	{
		UpdateDvmDeviceDatas_PkgError_GS();
	}

	//SV一致性检查 mym 
	if (g_oCapAnalysisConfig.m_bPkgConsistence)
	{
		UpdateDvmDeviceDatas_PkgAnalyz_SV();
	}

	//GOOSE一致性检查 mym 
	if (g_oCapAnalysisConfig.m_bPkgConsistence)
	{
		UpdateDvmDeviceDatas_PkgAnalyz_GS();
	}

	//SV延时；
	if (g_oCapAnalysisConfig.m_bAnalysisData_DelayTime)
	{
		UpdateDvmDeviceDatas_Analysis_SVDelayErr();
	}

	if (g_oCapAnalysisConfig.m_bSmvSyncDelt)
	{
		// SV同步差 
		UpdateDvmDeviceDatas_Analysis_SVSync();

		// GOOSE同步差 
		UpdateDvmDeviceDatas_Analysis_GSSync();
	}

	//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	// 下面的函数是MU测试仪中用的函数； 
	if (g_oCapAnalysisConfig.m_bMU_Test)
	{
		//计算精确度，更新相位和角差；2020-9-17 add mym 
		UpdateDvmDeviceDatas_Analysis_PhaseDelta();

		if (!g_oCapAnalysisConfig.m_bAnalysisData_DelayTime)//20220820 在不分析采样延时时,进行角差计算时,已经计算采样延时,此处可直接更新采样延时
		{
			long nLinkCount = 0;
			long nHasCalCount = 0;
			UpdateDvmDeviceDatas_Analysis_SVDelayErr_Dvm(nLinkCount, nHasCalCount);
		}

		// 计算出复合误差；mym 2020-9-8
		UpdateDvmDeviceDatas_Analysis_ComplexError();

		// 计算精度测试更新后面的角差，比差，频差等； mym
//		UpdateDvmDeviceDatas_Analysis_MagPhaseFreq();  zhouhj 20220825 为保证角差、复合误差等测试次数与比差一致,只在计算完角差后更新比差

		//计算精度测试更新报文响应时间、响应时间误差、通道延时
		UpdateDvmDeviceDatas_Analysis_Response();

		UpdateDvmDeviceDatas_Analysis_GS_ChangeBit(); //GOOSE 延时 SOE 试验 mym 2020-11-07

		UpdateDvmDeviceDatas_Analysis_NoPps();   // 无PPS时候 从合并单元中找出零点的时间 作差 存储；
	}
	
	if(g_oCapAnalysisConfig.m_bStateValueChangedAnalysis)
	{
		UpdateStateValueChangedRltDatas();
	}
}

/*
<data name="0X4001" id="SV1"/>
....................
<data name="0X1B01" id="Goose1"/>
..............
*/
void CX61850CapBase::UpdateDvmDeviceDatas_LinkState()
{
	if (m_pDataset_LinkState == NULL)
	{
		return;
	}

	POS pos = m_oCapDeviceAll.GetHeadPosition();
	CCapDeviceBase *pCapDevice = NULL;
	long nGSIndex = 1, nSvIndex = 1;
	CString strID, strValue;

	while (pos != NULL)
	{
		pCapDevice = (CCapDeviceBase*)m_oCapDeviceAll.GetNext(pos);

		if ((pCapDevice->GetClassID() == CPDCLASSID_DEVICE92)||
			pCapDevice->GetClassID() == CPDCLASSID_DEVICE6044)
		{
			strID.Format(_T("SV%d"), nSvIndex);
			nSvIndex++;
		}
		else if (pCapDevice->GetClassID() == CPDCLASSID_DEVICEGOOSE)
		{
			strID.Format(_T("Goose%d"), nGSIndex);
			nGSIndex++;
		}
		else
		{
			continue;
		}

		strValue.Format(_T("%d"), pCapDevice->m_bLinkState);
		Analysis_Add_Data(m_pDataset_LinkState,   strID,  strValue);
	}
}

void CX61850CapBase::UpdateDvmDeviceDatas_SvInst(const CString &strSvChID)
{
	CCapDeviceChRecord *pRcdCh = (CCapDeviceChRecord*)m_oCapDeviceChRecordMngr.FindByID(strSvChID);

	if (pRcdCh == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("++++++++++CX61850CapBase::UpdateDvmDeviceDatas_SvInst：pRcdCh==NULL；ChannelIdD==%s"), strSvChID.GetString());
		return;
	}

	if (pRcdCh->m_pRecfCh == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("++++++++++CX61850CapBase::UpdateDvmDeviceDatas_SvInst：pRcdCh->m_pRecfCh==NULL；ChannelIdD==%s"), strSvChID.GetString());
		return;
	}

	if (pRcdCh->m_pRecfCh->GetClassID() != CPDCLASSID_SMVCH)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("++++++++++CX61850CapBase::UpdateDvmDeviceDatas_SvInst：nClassID!=CPDCLASSID_SMVCH；ChannelIdD==%s"), strSvChID.GetString());
		return;
	}

	CMemBuffer_Long *pBufLong = pRcdCh->GetRecordBuffer();
	CCapDeviceSmvCh *pChSmv = ((CCapDeviceSmvCh*)pRcdCh->m_pRecfCh);
	double dCoef = pChSmv->m_fChRate;

	long nCurrIndex = pBufLong->GetDataFillBeginPosition();
	long nBufLen = pBufLong->GetBufferLength();
	long nDataLen = pBufLong->GetDataLength();
	long nCount = 80;
	long *pLongData = pBufLong->GetBuffer_long();
	long nDataIndex = 0;
	double pdLong[80];

	if (nDataLen > 80)
	{
		if (nCurrIndex < 80)
		{
			UpdateDvmDeviceDatas_SvInst(pLongData, dCoef, nDataLen - 80 + nDataIndex, nDataLen, nDataIndex, pdLong);
			UpdateDvmDeviceDatas_SvInst(pLongData, dCoef, 0, nCurrIndex, nDataIndex, pdLong);
		}
		else
		{
			UpdateDvmDeviceDatas_SvInst(pLongData, dCoef, nCurrIndex - 80, nCurrIndex, nDataIndex, pdLong);
		}
	}
	else
	{
		UpdateDvmDeviceDatas_SvInst(pLongData, dCoef, 0, nCurrIndex, nDataIndex, pdLong);
	}

	CString strComtradeFile;
	SYSTEMTIME tmSys;
	::GetLocalTime(&tmSys);

    strComtradeFile.Format(_T("SvInst_%s_%02d%02d.dat"), strSvChID.GetString(), tmSys.wMinute, tmSys.wSecond);
	pChSmv->WriteRcdFile_Comtrade(pdLong, 80, strComtradeFile);

	Analysis_Add_Data(m_pDataset_SVInst,   _T("SvInst_Rcd_file"),  strComtradeFile);
}

void CX61850CapBase::UpdateDvmDeviceDatas_SvInst(long *pLong, double dCoef, long nBegin, long nEnd, long &nDataIndex, double *pdLong)
{
	if (m_pDataset_SVInst == NULL)
	{
		return;
	}

	long nIndex = 0;
	double dValue = 0;
	CDvmData *pData = NULL;

	for (nIndex=nBegin; nIndex<nEnd; nIndex++)
	{
		pData = (CDvmData *)m_pDataset_SVInst->GetAtIndex(nDataIndex);

		if (pData == NULL)
		{
			pData = new CDvmData();
			pData->m_strName.Format(_T("InsValue%d"), nDataIndex+1);
			pData->m_strID = pData->m_strName;
			m_pDataset_SVInst->AddNewChild(pData);
		}

		dValue = dCoef * pLong[nIndex];
		pdLong[nDataIndex] = dValue;
		nDataIndex++;
		pData->m_strValue.Format(_T("%f"), dValue);
	}
}


//SV离散度 送出去；mym 20202-6-19
void CX61850CapBase::UpdateDvmDeviceDatas_Analysis_Discrete()
{
	if (m_pDataset_Discrete  ==  NULL)
	{
		return;
	}

	if (!g_oCapAnalysisConfig.m_bMaxTimeDiscrete)
	{
		return;
	}

	CString strID;
	long nIndex  =  0;
	CDvmData *pData = NULL;

	POS pos = m_oCapDeviceAll.GetHeadPosition();
	CCapDeviceBase *pCapDevice = NULL;
	long nGSIndex = 0;

	BYTE byFlagGSCstc[12] = {0};
	while (pos != NULL)
	{
		pCapDevice = (CCapDeviceBase*)m_oCapDeviceAll.GetNext(pos);

		if (pCapDevice->GetClassID() == CPDCLASSID_DEVICE92)
		{			
			strID.Format(_T("SV%d"),  nIndex + 1);
			pData = (CDvmData*)m_pDataset_Discrete->FindByID(strID);

			if (pData == NULL)
			{
				pData = m_pDataset_Discrete->AddNew2(strID, strID,  _T("us"),  _T("float"),  _T(""),  _T(""));
			}

			pData->m_strValue.Format(_T("%.3f"),  (double)(pCapDevice->m_dMaxTimeDiscrete/1000.0));//除以1000转成us
			pData->m_strUnit = "us";
			nIndex++;
		}
		else if (pCapDevice->GetClassID() == CPDCLASSID_DEVICE6044)
		{
			nIndex++;
		}
	}
}

/*
<dataset name="采集报文异常模拟" id="dsSVErr" data-type="" write-mode="0" index="0">
<data name="失步" id="LoseSyn" data-type="int" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
............
<data name="APPID1" id="SV1" data-type="int" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step="">
<value name="失步" id="SV1$LoseSyn" data-type="int" value=""/>
*/

//往CDvData中添加数据值，用于控制块自身分析结果赋值：<value name="失步" id="SV1$LoseSyn" data-type="int" value=""/>
void CX61850CapBase::Analysis_Add_Value(CDvmData *pData, const CString &strID, long nValue)
{
	CDvmValue *pValue = NULL;
	if (pData == NULL)
		return;
	pValue = (CDvmValue*)pData->FindByID(strID);

	if (pValue == NULL)
	{
		pValue = new CDvmValue();
		pData->AddNewChild(pValue);
		pValue->m_strName = strID;
		pValue->m_strID = strID;
	}

	pValue->m_strValue.Format(_T("%d"), nValue);
}

CDvmData* CX61850CapBase::Analysis_Add_Data(CDvmDataset *pDataset, const CString &strID)
{
	CDvmData *pData = NULL;
	pData = (CDvmData*)pDataset->FindByID(strID);

	if (pData == NULL)
	{
		pData = new CDvmData();
		pData->m_strName = strID;
		pData->m_strID = strID;
		pDataset->AddNewChild(pData);
	}

	return pData;
}

//往CDvDataset中添加数据，用于总的分析结果赋值：<data name="失步" id="LoseSyn" data-type="int" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step=""/>
void CX61850CapBase::Analysis_Add_Data(CDvmDataset *pDataset,  const CString &strID,  long nValue)
{
	if (pDataset == NULL)
		return;

	CDvmData *pData = Analysis_Add_Data(pDataset, strID);
	pData->m_strValue.Format(_T("%d"), nValue);
}

void CX61850CapBase::Analysis_Add_Data(CDvmDataset *pDataset,  const CString &strID,  int nValue)
{
	if (pDataset == NULL)
		return;

	CDvmData *pData = Analysis_Add_Data(pDataset, strID);
	pData->m_strValue.Format(_T("%d"), nValue);
}

void CX61850CapBase::Analysis_Add_Data(CDvmDataset *pDataset, const CString &strID, double fValue)
{
	if (pDataset == NULL)
		return;

	CDvmData *pData = Analysis_Add_Data(pDataset, strID);
	float fTemp  = (float)fValue;
	pData->m_strValue.Format(_T("%0.8lf"), fTemp);
	//pData->m_strValue.Format(_T("%f"), fValue);
}

void CX61850CapBase::Analysis_Add_Data(CDvmDataset *pDataset, const CString &strID, const CString &strValue)
{
	if (pDataset == NULL)
		return;

	CDvmData *pData = Analysis_Add_Data(pDataset, strID);
	pData->m_strValue = strValue;
}

void CX61850CapBase::Analysis_Add_Data(CDvmDataset *pDataset,  const CString &strID, BYTE byteValue)
{
	if (pDataset == NULL)
		return;

	CDvmData *pData = Analysis_Add_Data(pDataset, strID);
	pData->m_strValue.Format(_T("%d"), byteValue);
}


//SV-92 控制块分析结果赋值 mym 20202-6-19
void CX61850CapBase::UpdateDvmDeviceDatas_PkgError_92(CCapDeviceBase *pCapDevice, long nSvIndex, EP_ANALYSIS_RESULT &oAnalysisResults)
{
	if (m_pDataset_SVErr == NULL)
	{
		return;
	}

	if (pCapDevice == NULL)
		return;
	CString strSvID;
	strSvID.Format(_T("SV%d"),   nSvIndex);
	CDvmData *pDataSV    =    (CDvmData *)m_pDataset_SVErr->FindByID(strSvID);

	if (pDataSV == NULL)
	{
		pDataSV   =  new CDvmData();
		pDataSV->m_strName   =  strSvID;
		pDataSV->m_strID   =  strSvID;
		m_pDataset_SVErr->AddNewChild(pDataSV);
	}

	//  把几个ASDU的异常加起来，存在第一里，判断总的；
	int  nErrorType[PROTOCOL_61850ANALYSIS_ERROR_TYPE_NUM];
	::memset(nErrorType,  0x0,  sizeof (int)  * PROTOCOL_61850ANALYSIS_ERROR_TYPE_NUM);
	for (int i  = 0;  i <  PROTOCOL_61850ANALYSIS_ERROR_TYPE_NUM;   i++)
	{
		for (int j = 0;  j < pCapDevice->m_oAnalysisResults.rslt_92.nAsduCnt;  j++)
		{
			oAnalysisResults.rslt_92.nErrorType[j][i]    =  pCapDevice->m_oAnalysisResults.rslt_92.nErrorType[j][i];

			if (j == 0)
			{
				nErrorType[i]  = pCapDevice->m_oAnalysisResults.rslt_92.nErrorType[j][i];
			}
		}
	}

//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("离散度(%lf)."),pCapDevice->m_oAnalysisResults.dDeltTime);
	//上面同样把几个ASDU的值加起来算总的写进去；
	CDvmValue *pCurrValue = NULL;
	Analysis_Add_Value(pDataSV,  strSvID  +  _T("$PkgTotalNum"),  pCapDevice->m_oAnalysisResults.nPkgNum);
	pCurrValue = Analysis_Add_Value(pDataSV,  strSvID  +  _T("$MaxTimeDiscrete"),  (double)(pCapDevice->m_dMaxTimeDiscrete/1000.0f),3);
	Analysis_Add_Value_MaxValueRlt(pCurrValue,10.0f);//zhouhj 2024.4.29 增加对离散度计算的结果判断
	Analysis_Add_Value(pDataSV,  strSvID  +  _T("$LoseSyn"),  nErrorType[Cap_Smv92Error_LoseSyn]);
//	Analysis_Add_Value(pDataSV,  strSvID  +  _T("$LoseSyn"),  nErrorType[0]);
	Analysis_Add_Value(pDataSV,  strSvID  +  _T("$Loss"), nErrorType[Cap_Smv92Error_Loss]);
	Analysis_Add_Value(pDataSV,  strSvID  +  _T("$Repeat"),  nErrorType[Cap_Smv92Error_Repeat]);
	Analysis_Add_Value(pDataSV,  strSvID  +  _T("$NumErr"),  nErrorType[Cap_Smv92Error_NumErr]);
	Analysis_Add_Value(pDataSV,  strSvID  +  _T("$LengthParaErr"),  nErrorType[Cap_Smv92Error_LengthParaErr]);
	Analysis_Add_Value(pDataSV,  strSvID  +  _T("$APDUCodeErr"),  nErrorType[Cap_Smv92Error_APDUCodeErr]);
	Analysis_Add_Value(pDataSV,  strSvID  +  _T("$ASDUCodeErr"),  nErrorType[Cap_Smv92Error_ASDUCodeErr]);
	Analysis_Add_Value(pDataSV,  strSvID  +  _T("$TimeOut"),  nErrorType[Cap_Smv92Error_TimeOut]);
	Analysis_Add_Value(pDataSV,  strSvID  +  _T("$Shake"),  nErrorType[Cap_Smv92Error_Shake]);
	Analysis_Add_Value(pDataSV,  strSvID  +  _T("$CommLoss"),  nErrorType[Cap_Smv92Error_CommLoss]);
	Analysis_Add_Value(pDataSV,  strSvID  +  _T("$CommRecover"), nErrorType[Cap_Smv92Error_CommRecover]);
	Analysis_Add_Value(pDataSV,  strSvID  +  _T("$QualityErr"),  nErrorType[Cap_Smv92Error_QualityErr]);
	Analysis_Add_Value(pDataSV,  strSvID  +  _T("$SVInvalid"), nErrorType[Cap_Smv92Error_SVInvalid]);
	Analysis_Add_Value(pDataSV,  strSvID  +  _T("$TestStatus"), nErrorType[Cap_Smv92Error_TestStatus]);
	Analysis_Add_Value(pDataSV,  strSvID  +  _T("$DelayChanged"),  nErrorType[Cap_Smv92Error_DelayChanged]);
	Analysis_Add_Value(pDataSV,  strSvID  +  _T("$ASDUNumChanged"),  nErrorType[Cap_Smv92Error_ASDUNumChanged]);
	Analysis_Add_Value(pDataSV,  strSvID  +  _T("$ADIncstc"),  nErrorType[Cap_Smv92Error_ADIncstc]);
	Analysis_Add_Value(pDataSV,  strSvID  +  _T("$IllegalData"),  nErrorType[Cap_Smv92Error_IllegalData]);
}

CDvmValue* CX61850CapBase::Analysis_Add_Value(CDvmData *pData, const CString &strID, double fValue,long nPrecision)
{
	CDvmValue *pValue = NULL;

	if (pData == NULL)
		return NULL;

	pValue = (CDvmValue*)pData->FindByID(strID);

	if (pValue == NULL)
	{
		pValue = new CDvmValue();
		pData->AddNewChild(pValue);
		pValue->m_strName = strID;
		pValue->m_strID = strID;
	}

	if (nPrecision == -1)
	{
		pValue->m_strValue.Format(_T("%.3lf"), fValue);
	} 
	else
	{
		CString strTmp;
		strTmp.Format(_T("%%.%ldlf"),nPrecision);
		pValue->m_strValue.Format(strTmp.GetString(), fValue);
	}

	return pValue;
	//zhouhj 2024.4.29 在该功能的处理上,不应该在通用的接口函数中,增加个性化的处理功能
//	Analysis_Add_Value_MaxValueRlt(pValue);
}

//cl20231010离散度误差
void CX61850CapBase::Analysis_Add_Value_MaxValueRlt(CDvmValue *pDvmValue,double dStdMaxErrorValue)    
{
	if (pDvmValue == NULL)
	{
		return;
}

	CString strTmpID;
	double dMaxValue;

	//最大值
	strTmpID = pDvmValue->m_strID + STT_RcdInit_DL_MaxValue;
	dMaxValue = CString_To_double(pDvmValue->m_strValue);
	CDvmValue *pMaxValue = dvm_FindAddByID(pDvmValue,strTmpID,pDvmValue->m_strValue);
	pMaxValue->m_strValue = pDvmValue->m_strValue;

	//测试结果
	strTmpID = pDvmValue->m_strID + STT_RcdInit_DL_Result;
	CDvmValue *pResultValue = dvm_FindAddByID(pDvmValue,strTmpID,_T("1"));

	//测试描述
	strTmpID = pDvmValue->m_strID + STT_RcdInit_DL_RltDesc;
	CDvmValue *pRltDescValue = dvm_FindAddByID(pDvmValue,strTmpID,_T("合格"));
	
	if (fabs(dMaxValue)>dStdMaxErrorValue)
	{
		pResultValue->m_strValue = _T("0");
		pRltDescValue->m_strValue = _T("不合格");
	}
	else
	{
		pResultValue->m_strValue = _T("1");
		pRltDescValue->m_strValue = _T("合格");
	}
}


//SV-92总的分析结果赋值 mym 20202-6-19
void CX61850CapBase::UpdateDvmDeviceDatas_PkgError_92()
{
	if (m_pDataset_SVErr == NULL)
	{
		return;
	}

	EP_ANALYSIS_RESULT oAnalysisResults;
	ZeroMemory(&oAnalysisResults, sizeof(oAnalysisResults));

	POS pos = m_oCapDeviceAll.GetHeadPosition();
	CCapDeviceBase *p= NULL;
	long nSvIndex = 1;
	int nErrorType[PROTOCOL_61850ANALYSIS_ERROR_TYPE_NUM] = {0};
	long nPkgTotalNum = 0;
    double dMaxTimeDiscrete = 0.0f;

	while (pos != NULL)
	{
		p = (CCapDeviceBase*)m_oCapDeviceAll.GetNext(pos);

		if (p->GetClassID() == CPDCLASSID_DEVICE92)
		{
			UpdateDvmDeviceDatas_PkgError_92(p, nSvIndex, oAnalysisResults);
			nPkgTotalNum += p->m_oAnalysisResults.nPkgNum;

			for (int i =  0;  i <  PROTOCOL_61850ANALYSIS_ERROR_TYPE_NUM;  i++)
			{
				for (int  j  = 0; j  < 8; j++)
				{
					if (oAnalysisResults.rslt_92.nErrorType[j][i]  > 0)
						nErrorType[i]  = 1;
				}
			}

			if (p->m_dMaxTimeDiscrete > dMaxTimeDiscrete)
			{
				dMaxTimeDiscrete = p->m_dMaxTimeDiscrete;
			}

			nSvIndex++;
		}
		else if (p->GetClassID() == CPDCLASSID_DEVICE6044)
		{
			nSvIndex++;
		}

	}

	dMaxTimeDiscrete /= 1000.0f;
	Analysis_Add_Data(m_pDataset_SVErr,   _T("PkgTotalNum"),  nPkgTotalNum);
	Analysis_Add_Data(m_pDataset_SVErr,   _T("MaxTimeDiscrete"),  dMaxTimeDiscrete);
	Analysis_Add_Data(m_pDataset_SVErr,   _T("LoseSyn"),  nErrorType[Cap_Smv92Error_LoseSyn]);
	Analysis_Add_Data(m_pDataset_SVErr,   _T("Loss"), nErrorType[Cap_Smv92Error_Loss]);
	Analysis_Add_Data(m_pDataset_SVErr,   _T("Repeat"),  nErrorType[Cap_Smv92Error_Repeat]);
	Analysis_Add_Data(m_pDataset_SVErr,   _T("NumErr"),  nErrorType[Cap_Smv92Error_NumErr]);
	Analysis_Add_Data(m_pDataset_SVErr,   _T("LengthParaErr"),  nErrorType[Cap_Smv92Error_LengthParaErr]);
	Analysis_Add_Data(m_pDataset_SVErr,   _T("APDUCodeErr"),  nErrorType[Cap_Smv92Error_APDUCodeErr]);
	Analysis_Add_Data(m_pDataset_SVErr,   _T("ASDUCodeErr"),  nErrorType[Cap_Smv92Error_ASDUCodeErr]);
	Analysis_Add_Data(m_pDataset_SVErr,   _T("TimeOut"),  nErrorType[Cap_Smv92Error_TimeOut]);
	Analysis_Add_Data(m_pDataset_SVErr,   _T("Shake"),  nErrorType[Cap_Smv92Error_Shake]);
	Analysis_Add_Data(m_pDataset_SVErr,   _T("CommLoss"),  nErrorType[Cap_Smv92Error_CommLoss]);
	Analysis_Add_Data(m_pDataset_SVErr,   _T("CommRecover"), nErrorType[Cap_Smv92Error_CommRecover]);
	Analysis_Add_Data(m_pDataset_SVErr,   _T("QualityErr"),  nErrorType[Cap_Smv92Error_QualityErr]);
	Analysis_Add_Data(m_pDataset_SVErr,   _T("SVInvalid"), nErrorType[Cap_Smv92Error_SVInvalid]);
	Analysis_Add_Data(m_pDataset_SVErr,   _T("TestStatus"), nErrorType[Cap_Smv92Error_TestStatus]);
	Analysis_Add_Data(m_pDataset_SVErr,   _T("DelayChanged"),  nErrorType[Cap_Smv92Error_DelayChanged]);
	Analysis_Add_Data(m_pDataset_SVErr,   _T("ASDUNumChanged"),  nErrorType[Cap_Smv92Error_ASDUNumChanged]);
	Analysis_Add_Data(m_pDataset_SVErr,   _T("ADIncstc"),  nErrorType[Cap_Smv92Error_ADIncstc]);
	Analysis_Add_Data(m_pDataset_SVErr,   _T("IllegalData"),  nErrorType[Cap_Smv92Error_IllegalData]);
}


//GS 控制块分析结果赋值 mym 20202-6-19
void CX61850CapBase::UpdateDvmDeviceDatas_PkgError_GS(CCapDeviceBase *pCapDevice,   long nGsIndex,   EP_ANALYSIS_RESULT &oAnalysisResults)
{
	if (m_pDataset_GSErr == NULL)
	{
		return;
	}

	if (pCapDevice == NULL)
		return;
	CString strGSID;
	strGSID.Format(_T("Goose%d"),   nGsIndex);
	CDvmData * pDataGS   =    (CDvmData *)m_pDataset_GSErr->FindByID(strGSID);

	if ((pDataGS == NULL)&&(pCapDevice->m_strID.GetLength()>2))
		//20220607 zhouhj 对应的报文异常统计data对象ID与对应的数据集DvmDataset对应的ID一致,只是前面少了ds字符,故在此处做处理,由于GOOSE之前定义的数据集包含Gout、Gin,实际并不是Goose%d
	{
		strGSID = pCapDevice->m_strID.Mid(2);
		pDataGS   =    (CDvmData *)m_pDataset_GSErr->FindByID(strGSID);
	}

	if (pDataGS == NULL)
	{
		pDataGS   =  new CDvmData();
		pDataGS->m_strName   =  strGSID;
		pDataGS->m_strID   =  strGSID;
		m_pDataset_GSErr->AddNewChild(pDataGS);
	}
	int  nErrorType[PROTOCOL_61850ANALYSIS_ERROR_TYPE_NUM] = {0};
	//::memset(nErrorType,  0x0,  sizeof (int)  * 20);
	for (int i = 0; i < PROTOCOL_61850ANALYSIS_ERROR_TYPE_NUM; i++)
	{
		oAnalysisResults.rslt_gs.nErrorType[i]    =  pCapDevice->m_oAnalysisResults.rslt_gs.nErrorType[i];
		//nErrorType[i]  += pCapDevice->m_oAnalysisResults.rslt_gs.nErrorType[i];
		nErrorType[i]  =  pCapDevice->m_oAnalysisResults.rslt_gs.nErrorType[i];
	}


	Analysis_Add_Value(pDataGS,  strGSID  +  _T("$PkgTotalNum"),  pCapDevice->m_oAnalysisResults.nPkgNum);
	Analysis_Add_Value(pDataGS,  strGSID  +  _T("$DummyBit"),  nErrorType[Cap_GsError_DummyBit]);
	Analysis_Add_Value(pDataGS,  strGSID  +  _T("$SQNumLoss"), nErrorType[Cap_GsError_SQNumLoss]);
	Analysis_Add_Value(pDataGS,  strGSID  +  _T("$SQNumInitError"),  nErrorType[Cap_GsError_SQNumInitError]);
	Analysis_Add_Value(pDataGS,  strGSID  +  _T("$SQNumDisorder"),  nErrorType[Cap_GsError_SQNumDisorder]);
	Analysis_Add_Value(pDataGS,  strGSID  +  _T("$SQNumRepeat"),  nErrorType[Cap_GsError_SQNumRepeat]);
	Analysis_Add_Value(pDataGS,  strGSID  +  _T("$STNumLoss"),  nErrorType[Cap_GsError_STNumLoss]);
	Analysis_Add_Value(pDataGS,  strGSID  +  _T("$DevRestart"),  nErrorType[Cap_GsError_DevRestart]);
	Analysis_Add_Value(pDataGS,  strGSID  +  _T("$STNumDisorder"),  nErrorType[Cap_GsError_STNumDisorder]);
	Analysis_Add_Value(pDataGS,  strGSID  +  _T("$APDUCodeErr"),  nErrorType[Cap_GsError_APDUCodeErr]);
	Analysis_Add_Value(pDataGS,  strGSID  +  _T("$ASDUCodeErr"),  nErrorType[Cap_GsError_ASDUCodeErr]);
	Analysis_Add_Value(pDataGS,  strGSID  +  _T("$LengthParaErr"), nErrorType[Cap_GsError_LengthParaErr]);
	Analysis_Add_Value(pDataGS,  strGSID  +  _T("$TimeOut"),  nErrorType[Cap_GsError_TimeOut]);
	Analysis_Add_Value(pDataGS,  strGSID  +  _T("$CommLoss"), nErrorType[Cap_GsError_CommLoss]);
	Analysis_Add_Value(pDataGS,  strGSID  +  _T("$CommRecover"), nErrorType[Cap_GsError_CommRecover]);
	Analysis_Add_Value(pDataGS,  strGSID  +  _T("$LivingTimeInvalid"),  nErrorType[Cap_GsError_LivingTimeInvalid]);
	Analysis_Add_Value(pDataGS,  strGSID  +  _T("$ClockFault"),  nErrorType[Cap_GsError_ClockFault]);
	Analysis_Add_Value(pDataGS,  strGSID  +  _T("$ClockNotSyn"),  nErrorType[Cap_GsError_ClockNotSyn]);
	Analysis_Add_Value(pDataGS,  strGSID  +  _T("$Illegal"),  nErrorType[Cap_GsError_Illegal]);

	// mym 2020-11-2这里可以考虑把检修位放置到
}

long CX61850CapBase::FindGinMapByIndex(long nIndex)
{
	if (m_pDataset_Gin1 == NULL)
		return -1;

	CDvmData *pData = (CDvmData *)m_pDataset_Gin1->GetAtIndex(nIndex);

	if (pData == NULL)
		return -1;

	CString strID;
    strID.Format(_T("%s$map"), pData->m_strID.GetString());

	CDvmValue *pMap = (CDvmValue *)pData->FindByID(strID);

	if(pMap == NULL)
		return -1;

	CString strValue = pMap->m_strValue;
	long nPos = strValue.Find(_T("bin"));

	if(nPos < 0)
		return -1;

	nPos = strValue.Find(_T("binex"));
	CString strReturn;
	long nRet = 0;

	if (nPos >= 0)
	{
		strReturn = strValue.Mid(nPos + 5);
		strReturn = strReturn.Left(strReturn.GetLength() - 1);
		nRet = CString_To_long(strReturn);
		nRet += 8;
	}
	else
	{
		nPos =  strValue.Find(_T("bin"));
		strReturn = strValue.Mid(nPos + 3);
		strReturn = strReturn.Left(strReturn.GetLength() - 1);
		nRet = CString_To_long(strReturn);
	}

	return nRet;
}

void CX61850CapBase::GetGooseTime(double &dTime1, double &dTime2, long nMap)
{
	CDvmData *pGinMap = (CDvmData *)m_pDataset_IEDTest->FindByID(_T("Gin"));
	CDvmData *pTestType = (CDvmData *)m_pDataset_IEDTest->FindByID(_T("TestProject")); //测试类型 0-延时测试；1-SOE测试；2-风暴测试
	CString strTestType = pTestType->m_strValue;
	CDvmData *pTestMode = (CDvmData *)m_pDataset_IEDTest->FindByID(_T("TestMode"));   //测试模式 0-gse2bin; 1-bout2gse；2-gse2bin复归；3-bout2gse复归
	CString strTestMode = pTestMode->m_strValue;
	CDvmValue *pValueTime = NULL;

	if (strTestType == IEDTEST_TESTTYPE_DELAY)
	{
		if (strTestMode == IEDTEST_TESTMODE_BOUT2GSE)
		{
			CDvmValue *pValue = (CDvmValue *)pGinMap->GetAtIndex(nMap - 1);
			pValueTime  = (CDvmValue *)pValue->FindByID(_T("Time1"));
			pValueTime->m_strValue.Format(_T("%11.9f"), dTime1);
		}
	}
	else if (strTestType == IEDTEST_TESTTYPE_SOE)
	{
		if (strTestMode == IEDTEST_TESTMODE_BOUT2GSE)
		{
			CDvmValue *pValue = (CDvmValue *)pGinMap->GetAtIndex(nMap - 1);
			pValueTime  = (CDvmValue *)pValue->FindByID(_T("Time1"));
			pValueTime->m_strValue.Format(_T("%11.9f"), dTime1);

			pValueTime  = (CDvmValue *)pValue->FindByID(_T("Time2"));
			pValueTime->m_strValue.Format(_T("%11.9f"), dTime2);
		}
	}
}

//GOOSE 延时、SOE 变位后时间塞到那里去 mym 20202-11-02
void CX61850CapBase::UpdateDvmDeviceDatas_Analysis_GS_ChangeBit()
{
	POS pos = m_oCapDeviceAll.GetHeadPosition();
	CCapDeviceBase *pCapDevice = NULL;
	long nSvIndex = 1;
	int     nErrorType[PROTOCOL_61850ANALYSIS_ERROR_TYPE_NUM]  =  {0};     

	while (pos != NULL)
	{
		pCapDevice  = (CCapDeviceBase*)m_oCapDeviceAll.GetNext(pos);

		if (pCapDevice->GetClassID() == CPDCLASSID_DEVICEGOOSE)
		{	

			for (int nChIndex = 0;  nChIndex  <  GSCHANNEL_CNT; nChIndex++)
			{
				if (pCapDevice->m_oAnalysisResults.nChangeBit[nChIndex]==1)
				{
					long nMap = 0;
					if (pCapDevice->m_oAnalysisResults.nChnnelType[nChIndex]==0x83)
					{
						//获取索引得到是哪个通道变位；
						 nMap = FindGinMapByIndex(nChIndex/2);		//录波是bool、时间通道交替的，从数据集获取映射时，只取bool通道
					}
					else if (pCapDevice->m_oAnalysisResults.nChnnelType[nChIndex]==0x84)
					{
						//获取索引得到是哪个通道变位；
						nMap = FindGinMapByIndex(nChIndex);		//录波是bool、时间通道交替的，从数据集获取映射时，只取bool通道
					} 
			
					if (nMap  > 0)
					{
						GetGooseTime(pCapDevice->m_dTime1[nChIndex], pCapDevice->m_dTime2[nChIndex],  nMap);
						pCapDevice->m_oAnalysisResults.nChangeBit[nChIndex] = 0;
					}
				}
			}

		}
	}
}


//NOPPS时候计算最大值，最小值，当前值；mym 2020-11-07;
void CX61850CapBase::UpdateDvmDeviceDatas_Analysis_NoPps()
{
	if (m_pDataset_Time == NULL)
	{
		return;
	}

	POS pos = m_oCapDeviceAll.GetHeadPosition();
	CCapDeviceBase *pCapDevice = NULL;
	long nSvIndex = 1;
	int     nErrorType[PROTOCOL_61850ANALYSIS_ERROR_TYPE_NUM]  =  {0};     
	CCapDevice92 *pDevice92 = NULL;
	int nFindFlag = 0;
	while (pos != NULL)
	{
		pCapDevice  = (CCapDeviceBase*)m_oCapDeviceAll.GetNext(pos);

		pDevice92  =  (CCapDevice92 *)pCapDevice;
        if (pDevice92==NULL)
			break;

		if (pCapDevice->GetClassID() == CPDCLASSID_DEVICE92)
		{	
		//	pDevice92->m_fZeroDelta;
			nFindFlag = 1;
			break;
		}
	}
	if (nFindFlag==0)
		return;

	if (pDevice92==NULL)
		return;
	if (pDevice92->m_fZeroDelta > 500 && m_nFirstDataFlag==0)
	{
		m_dTimeFirstValue =  pDevice92->m_fZeroDelta;
		m_nFirstDataFlag = 1;
	}

   double dDeltValue =  pDevice92->m_fZeroDelta - m_dTimeFirstValue;
    dDeltValue = fabs(dDeltValue);

	if (m_dTimeMaxValue < dDeltValue)
		m_dTimeMaxValue  = dDeltValue;

	if (m_dTimeMinValue > dDeltValue)
		m_dTimeMinValue  = dDeltValue;

	m_dTimeCurrValue  =  dDeltValue;

	CDvmData *pRslt = (CDvmData *)m_pDataset_Time->FindByID(_T("TestRslt"));

	//POS pos = pRslt->GetHeadPosition();
	CDvmValue *pMax = (CDvmValue *)pRslt->FindByID(_T("MaxRslt"));
	CDvmValue *pMin = (CDvmValue *)pRslt->FindByID(_T("MinRslt"));
	CDvmValue *pCurr = (CDvmValue *)pRslt->FindByID(_T("CurrRslt"));

	if (pMax==NULL||pMin==NULL||pCurr==NULL)
		return;

	double dMax, dMin,  dCurr;

	pMax->m_strValue.Format(_T("%f"), m_dTimeMaxValue);
	pMin->m_strValue.Format(_T("%f"), m_dTimeMinValue);
	pCurr->m_strValue.Format(_T("%f"), m_dTimeCurrValue);
}

//GS 总的分析结果赋值 mym 20202-6-19
void CX61850CapBase::UpdateDvmDeviceDatas_PkgError_GS()
{
	if (m_pDataset_GSErr == NULL)
	{
		return;
	}

	EP_ANALYSIS_RESULT oAnalysisResults;
	ZeroMemory(&oAnalysisResults, sizeof(oAnalysisResults));

	POS pos = m_oCapDeviceAll.GetHeadPosition();
	CCapDeviceBase *p= NULL;
	long nGsIndex = 1;
	int     nErrorType[PROTOCOL_61850ANALYSIS_ERROR_TYPE_NUM]  =  {0};     
	int nPkgTotalNum = 0;

	while (pos != NULL)
	{
		p = (CCapDeviceBase*)m_oCapDeviceAll.GetNext(pos);

		if (p->GetClassID() == CPDCLASSID_DEVICEGOOSE)
		{	
			UpdateDvmDeviceDatas_PkgError_GS(p, nGsIndex, oAnalysisResults);
			nPkgTotalNum += p->m_oAnalysisResults.nPkgNum;

			for (int i = 0; i < 20; i++)
			{
				if (oAnalysisResults.rslt_gs.nErrorType[i]  > 0)
					nErrorType[i] = 1;//oAnalysisResults.rslt_gs.nErrorType[i];
			}
			nGsIndex++;
		}
	}


	Analysis_Add_Data(m_pDataset_GSErr,      _T("PkgTotalNum"),  nPkgTotalNum);
	Analysis_Add_Data(m_pDataset_GSErr,      _T("DummyBit"),  nErrorType[Cap_GsError_DummyBit]);
	Analysis_Add_Data(m_pDataset_GSErr,      _T("SQNumLoss"),   nErrorType[Cap_GsError_SQNumLoss]);
	Analysis_Add_Data(m_pDataset_GSErr,      _T("SQNumInitError"),    nErrorType[Cap_GsError_SQNumInitError]);
	Analysis_Add_Data(m_pDataset_GSErr,      _T("SQNumDisorder"),    nErrorType[Cap_GsError_SQNumDisorder]);
	Analysis_Add_Data(m_pDataset_GSErr,      _T("SQNumRepeat"),    nErrorType[Cap_GsError_SQNumRepeat]);
	Analysis_Add_Data(m_pDataset_GSErr,      _T("STNumLoss"),    nErrorType[Cap_GsError_STNumLoss]);
	Analysis_Add_Data(m_pDataset_GSErr,      _T("DevRestart"),    nErrorType[Cap_GsError_DevRestart]);
	Analysis_Add_Data(m_pDataset_GSErr,      _T("STNumDisorder"),    nErrorType[Cap_GsError_STNumDisorder]);
	Analysis_Add_Data(m_pDataset_GSErr,      _T("APDUCodeErr"),    nErrorType[Cap_GsError_APDUCodeErr]);
	Analysis_Add_Data(m_pDataset_GSErr,      _T("ASDUCodeErr"),    nErrorType[Cap_GsError_ASDUCodeErr]);
	Analysis_Add_Data(m_pDataset_GSErr,      _T("LengthParaErr"),   nErrorType[Cap_GsError_LengthParaErr]);
	Analysis_Add_Data(m_pDataset_GSErr,      _T("TimeOut"),    nErrorType[Cap_GsError_TimeOut]);
	Analysis_Add_Data(m_pDataset_GSErr,      _T("CommLoss"),   nErrorType[Cap_GsError_CommLoss]);
	Analysis_Add_Data(m_pDataset_GSErr,      _T("CommRecover"),   nErrorType[Cap_GsError_CommRecover]);
	Analysis_Add_Data(m_pDataset_GSErr,      _T("LivingTimeInvalid"),    nErrorType[Cap_GsError_LivingTimeInvalid]);
	Analysis_Add_Data(m_pDataset_GSErr,      _T("ClockFault"),    nErrorType[Cap_GsError_ClockFault]);
	Analysis_Add_Data(m_pDataset_GSErr,      _T("ClockNotSyn"),    nErrorType[Cap_GsError_ClockNotSyn]);
	Analysis_Add_Data(m_pDataset_GSErr,      _T("Illegal"),    nErrorType[Cap_GsError_Illegal]);
}

/*
<value name="检修位" id="SV1$TestPos" data-type="STRUCT" value="">
	<value name="标准值" id="SV1$TestPos$stand" data-type="string" value=""/>
	<value name="实际值" id="SV1$TestPos$actual" data-type="string" value=""/>
	<value name="判断结果" id="SV1$TestPos$rslt" data-type="int" value=""/>
</value>
*/
void IecAnalysis_Update_SV_PkgAnalyze_rslt_cal(CDvmValue *pValue)
{
	CString strStand = pValue->GetAttrByID_MmsAttr(_T("$stand"));
	CString strActual = pValue->GetAttrByID_MmsAttr(_T("$actual"));

	if (strStand == strActual)
	{//标准值和实际值相等，则合格，否则不合格
		pValue->SetValue_Mms(_T("$rslt"), _T("1"));
	}
	else
	{
		pValue->SetValue_Mms(_T("$rslt"), _T("0"));
	}
}

void IecAnalysis_Update_SV_PkgAnalyze_val(CDvmData *pSvData, char *pszValueID, unsigned long nValue)
{
	CString strValueID = pszValueID;
	strValueID = _T("$") + strValueID;
	CDvmValue *pValue = (CDvmValue *)pSvData->FindByID_MmsAttr(strValueID);

	if (pValue == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("[%s] not exist in [%s]"), strValueID.GetString(), pSvData->m_strID.GetString());
		return;
	}

	pValue->SetValue_Mms(_T("$actual"), nValue);
	IecAnalysis_Update_SV_PkgAnalyze_rslt_cal(pValue);
}


void IecAnalysis_Update_SV_PkgAnalyze_val(CDvmData *pSvData, char *pszValueID, long nValue)
{
	CString strValueID = pszValueID;
	strValueID = _T("$") + strValueID;
	CDvmValue *pValue = (CDvmValue *)pSvData->FindByID_MmsAttr(strValueID);

	if (pValue == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("[%s] not exist in [%s]"), strValueID.GetString(), pSvData->m_strID.GetString());
		return;
	}

	pValue->SetValue_Mms(_T("$actual"), nValue);
	IecAnalysis_Update_SV_PkgAnalyze_rslt_cal(pValue);
}

void IecAnalysis_Update_SV_PkgAnalyze_val(CDvmData *pSvData, char *pszValueID, const CString &strValue)
{
	CString strValueID = pszValueID;
	strValueID = _T("$") + strValueID;
	CDvmValue *pValue = (CDvmValue *)pSvData->FindByID_MmsAttr(strValueID);

	if (pValue == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("[%s] not exist in [%s]"), strValueID.GetString(), pSvData->m_strID.GetString());
		return;
	}

	pValue->SetValue_Mms(_T("$actual"), strValue);
	IecAnalysis_Update_SV_PkgAnalyze_rslt_cal(pValue);
}

/*
0<data name="检修位"/>
1<data name="版本号"/>1
2<data name="PDU长度"/>
3<data name="通道数"/>1
4<data name="VLANID"/>
5<data name="VLAN 优先级"/>
6<data name="同步状态"/>1
7<data name="采样率"/>`1
8<data name="ASDU数目"/>1
9<data name="目标MAC地址"/>1
10<data name="SVID/LD Name"/> 1
11<data name="APPID1"/> 1
*/
//SV一致性检查 mym 20202-6-19
void CX61850CapBase::UpdateDvmDeviceDatas_PkgAnalyz_SV()
{
	if (m_pDataset_SV_PkgAnalyze == NULL)
	{
		return;
	}

	POS pos = m_oCapDeviceAll.GetHeadPosition();
	CCapDeviceBase *pCapDevice = NULL;
	long nSvIndex = 0;

	BYTE byFlagSVCstc[12] = {0};
	while (pos != NULL)
	{
		pCapDevice = (CCapDeviceBase*)m_oCapDeviceAll.GetNext(pos);

		if (pCapDevice->GetClassID() == CPDCLASSID_DEVICE92)
		{
			for (int i  = 0; i < 12;  i++)
			{ 
				if (pCapDevice->m_dwFlagSVCstc[i]  > 0)
					byFlagSVCstc[i] = 1;
			}

			UpdateDvmDeviceDatas_PkgAnalyz_SV_Single(pCapDevice,  nSvIndex);
			nSvIndex++;
		}
		else if (pCapDevice->GetClassID() == CPDCLASSID_DEVICE6044)
		{
			nSvIndex++;
		}
	}


	//这里是总的检查；
	//所有的不一致都填到第一个控制块里，然后再显示；

	//任何控制块有问题，总的里写错误，值为1就是错误；


	nSvIndex  =  0;
	Analysis_Add_Data(m_pDataset_SV_PkgAnalyze,   _T("Test"),  byFlagSVCstc[0]);
	Analysis_Add_Data(m_pDataset_SV_PkgAnalyze,   _T("DevVersion"), byFlagSVCstc[1]);
	Analysis_Add_Data(m_pDataset_SV_PkgAnalyze,   _T("PDUlength"),  byFlagSVCstc[2]);
	Analysis_Add_Data(m_pDataset_SV_PkgAnalyze,   _T("Channel"),  byFlagSVCstc[3]);
	Analysis_Add_Data(m_pDataset_SV_PkgAnalyze,   _T("VLAN_ID"),  byFlagSVCstc[4]);
	Analysis_Add_Data(m_pDataset_SV_PkgAnalyze,   _T("VLANPriority"),  byFlagSVCstc[5]);
	Analysis_Add_Data(m_pDataset_SV_PkgAnalyze,   _T("SynState"),  byFlagSVCstc[6]);
	Analysis_Add_Data(m_pDataset_SV_PkgAnalyze,   _T("SampRate"),  byFlagSVCstc[7]);
	Analysis_Add_Data(m_pDataset_SV_PkgAnalyze,   _T("ASDUNumber"),  byFlagSVCstc[8]);
	Analysis_Add_Data(m_pDataset_SV_PkgAnalyze,   _T("DstMAC"),  byFlagSVCstc[9]);
	Analysis_Add_Data(m_pDataset_SV_PkgAnalyze,   _T("SVID"),  byFlagSVCstc[10]);
}
/*
int HexStringToByte(char *in, unsigned char *out) 
{
int len = (int)strlen(in);
char *str = (char *)malloc(len);
memset(str, 0, len);
memcpy(str, in, len);
for (int i = 0; i < len; i+=2) {
//小写转大写
if(str[i] >= 'a' && str[i] <= 'f') str[i] = str[i] & ~0x20;
if(str[i+1] >= 'a' && str[i] <= 'f') str[i+1] = str[i+1] & ~0x20;
//处理第前4位
if(str[i] >= 'A' && str[i] <= 'F')
out[i/2] = (str[i]-'A'+10)<<4;
else
out[i/2] = (str[i] & ~0x30)<<4;
//处理后4位, 并组合起来
if(str[i+1] >= 'A' && str[i+1] <= 'F')
out[i/2] |= (str[i+1]-'A'+10);
else
out[i/2] |= (str[i+1] & ~0x30);
}
free(str);
return 0;
}
*/

//16进制字符串 转成16进制值，方便比较；
int HexStringToByte(char s[],  unsigned char bits[]) 
{	
	int i,n = 0;	for(i = 0; s[i]; i += 2)
	{		
		if(s[i] >= 'A' && s[i] <= 'F')		
			bits[n] = s[i] - 'A' + 10;		
		else bits[n] = s[i] - '0';		
		if(s[i + 1] >= 'A' && s[i + 1] <= 'F')	
			bits[n] = (bits[n] << 4) | (s[i + 1] - 'A' + 10);	
		else 
			bits[n] = (bits[n] << 4) | (s[i + 1] - '0');	
		++n;	
	}	
	return n;
}

//SMV  控制块一致性结果分析结果 mym 20202-6-19
void CX61850CapBase::UpdateDvmDeviceDatas_PkgAnalyz_SV_Single(CCapDeviceBase *pCapDevice,   long nSvIndex)
{
	if (m_pDataset_SV_PkgAnalyze == NULL)
	{
		return;
	}

	if (pCapDevice == NULL)
		return;

	CDvmDataset *pDataset = pCapDevice->GetDvmDataset();

	if (pDataset == NULL)
	{
		return;
	}

	CString strSVCstcID = pDataset->m_strID.Mid(2);;

	strSVCstcID.Format(_T("SV%d"),   nSvIndex + 1);
	CDvmData * pSvData   =    (CDvmData *)m_pDataset_SV_PkgAnalyze->FindByID(strSVCstcID);

	if (pSvData == NULL)
	{
		pSvData   =  new CDvmData();
		pSvData->m_strName   =  strSVCstcID;
		pSvData->m_strID   =  strSVCstcID;
		XSttRcdInitSv_PkgAnalyze(pSvData, strSVCstcID);
		m_pDataset_SV_PkgAnalyze->AddNewChild(pSvData);
	}


	EPCAPPARSEDATAS oPrevDatas = pCapDevice->m_oPrevDatas;
	CIecCfgDataBase* pIecCfgDataBase = pCapDevice->GetIecCfgData();

	IecAnalysis_Update_SV_PkgAnalyze_val(pSvData, IEC_PkgAnalyze_ID_DevVersion, oPrevDatas.oData92.Asdu[0].confRev);
	IecAnalysis_Update_SV_PkgAnalyze_val(pSvData, IEC_PkgAnalyze_ID_PDUlength, oPrevDatas.oData92.APDULen);

	IecAnalysis_Update_SV_PkgAnalyze_val(pSvData, IEC_PkgAnalyze_ID_Channel,  oPrevDatas.oData92.nChCount/*/8*/);//20220614 zhouhj 已在赋值位置统一处理除以8的问题
	IecAnalysis_Update_SV_PkgAnalyze_val(pSvData, IEC_PkgAnalyze_ID_VLAN_ID,  oPrevDatas.oData92.VlanID);
	IecAnalysis_Update_SV_PkgAnalyze_val(pSvData, IEC_PkgAnalyze_ID_VLANPriority, oPrevDatas.oData92.VlanPr);
	IecAnalysis_Update_SV_PkgAnalyze_val(pSvData, IEC_PkgAnalyze_ID_SynState, oPrevDatas.oData92.Asdu[0].smpSynch);
	
	IecAnalysis_Update_SV_PkgAnalyze_val(pSvData, IEC_PkgAnalyze_ID_ASDUNumber, oPrevDatas.oData92.Num_ASDU);
	IecAnalysis_Update_SV_PkgAnalyze_val(pSvData, IEC_PkgAnalyze_ID_SVID, oPrevDatas.oData92.Asdu[0].SVID);
	IecAnalysis_Update_SV_PkgAnalyze_val(pSvData, IEC_PkgAnalyze_ID_SampRate, (long)pCapDevice->m_oAnalysisResults.rslt_92.nSmpCountMaxValue);


// 	if((pIecCfgDataBase != NULL)&&(pIecCfgDataBase->GetClassID() == CFGCLASSID_CIECCFG92DATA))
// 	{
// 		CIecCfg92Data *pIecCfg92Data = (CIecCfg92Data*)pIecCfgDataBase;
// 		IecAnalysis_Update_SV_PkgAnalyze_val(pSvData, IEC_PkgAnalyze_ID_SampRate, pIecCfg92Data->m_nSampleRate);
// 	}

	CString strMac;
	strMac.Format(_T("%02X-%02X-%02X-%02X-%02X-%02X"), (unsigned char)oPrevDatas.destMAC[0], (unsigned char)oPrevDatas.destMAC[1], (unsigned char)oPrevDatas.destMAC[2]
		, (unsigned char)oPrevDatas.destMAC[3], (unsigned char)oPrevDatas.destMAC[4], (unsigned char)oPrevDatas.destMAC[5]);

	IecAnalysis_Update_SV_PkgAnalyze_val(pSvData, IEC_PkgAnalyze_ID_DstMAC, strMac);
// 
// 
// 	Analysis_Add_Value(pDataGS,   strSVCstcID  +  _T("$TestPos"),  pCapDevice->m_dwFlagSVCstc[0]);
// 	Analysis_Add_Atrri_Error(pCapDevice,  pDataGS, 2,  nSvIndex,  0);
// 
// 	Analysis_Add_Value(pDataGS,   strSVCstcID  +  _T("$DevVersion"),  pCapDevice->m_dwFlagSVCstc[1]);
// 	Analysis_Add_Atrri_Error(pCapDevice,  pDataGS, 2,  nSvIndex,  1);
// 
// 	Analysis_Add_Value(pDataGS,   strSVCstcID  +  _T("$PDUlength"),   pCapDevice->m_dwFlagSVCstc[2]);
// 	Analysis_Add_Atrri_Error(pCapDevice,  pDataGS, 2,  nSvIndex,  2);
// 
// 	Analysis_Add_Value(pDataGS,   strSVCstcID  +  _T("$Channel"),   pCapDevice->m_dwFlagSVCstc[3]);
// 	Analysis_Add_Atrri_Error(pCapDevice,  pDataGS, 2,  nSvIndex,  3);
// 
// 	Analysis_Add_Value(pDataGS,   strSVCstcID  +  _T("$VLAN_ID"),   pCapDevice->m_dwFlagSVCstc[4]);
// 	Analysis_Add_Atrri_Error(pCapDevice,  pDataGS, 2,  nSvIndex,  4);
// 
// 	Analysis_Add_Value(pDataGS,   strSVCstcID  +  _T("$VLANPriority"),   pCapDevice->m_dwFlagSVCstc[5]);
// 	Analysis_Add_Atrri_Error(pCapDevice,  pDataGS, 2,  nSvIndex,  5);
// 
// 	Analysis_Add_Value(pDataGS,   strSVCstcID  +  _T("$SynState"),   pCapDevice->m_dwFlagSVCstc[6]);
// 	Analysis_Add_Atrri_Error(pCapDevice,  pDataGS, 2,  nSvIndex,  6);
// 
// 	Analysis_Add_Value(pDataGS,   strSVCstcID  +  _T("$SampRate"),   pCapDevice->m_dwFlagSVCstc[7]);
// 	Analysis_Add_Atrri_Error(pCapDevice,  pDataGS, 2,  nSvIndex,  7);
// 
// 	Analysis_Add_Value(pDataGS,   strSVCstcID  +  _T("$ASDUNumber"),   pCapDevice->m_dwFlagSVCstc[8]);
// 	Analysis_Add_Atrri_Error(pCapDevice,  pDataGS, 2,  nSvIndex,  8);
// 
// 	Analysis_Add_Value(pDataGS,   strSVCstcID  +   _T("$DstMAC"),   pCapDevice->m_dwFlagSVCstc[9]);
// 	Analysis_Add_Atrri_Error(pCapDevice,  pDataGS,  2,  nSvIndex,  9);
// 
// 	Analysis_Add_Value(pDataGS,   strSVCstcID  +   _T("$SVID"),   pCapDevice->m_dwFlagSVCstc[10]);
// 	Analysis_Add_Atrri_Error(pCapDevice,  pDataGS, 2,  nSvIndex,  10);

}

//GS一致性检查 mym 20202-6-19
void CX61850CapBase::UpdateDvmDeviceDatas_PkgAnalyz_GS()
{
	POS pos = m_oCapDeviceAll.GetHeadPosition();
	CCapDeviceBase *pCapDevice = NULL;
	long nGSIndex = 0;

	BYTE byFlagGSCstc[12] = {0};
	while (pos != NULL)
	{
		pCapDevice = (CCapDeviceBase*)m_oCapDeviceAll.GetNext(pos);

		if (pCapDevice->GetClassID() == CPDCLASSID_DEVICEGOOSE)
		{			
			for (int i  = 0; i < 12;  i++)
			{ 
				if (pCapDevice->m_dwFlagGSCstc[i]  > 0  )
					byFlagGSCstc[i] = 1;
			}
			UpdateDvmDeviceDatas_PkgAnalyz_GS_Single(pCapDevice,  nGSIndex);
			nGSIndex++;
		}
	}


	//这里是总的检查；
	//所有的不一致都填到第一个控制块里，然后再显示；

	//for (int i  = 0;  i < 30; i++)
	//{
	//for (int j  = 0; j < 12;  j++)
	//{ 
	//if (m_byFlagGSCstc[i][j]==1)
	//	byFlagGSCstc[j] = 1;
	//}
	//}
	nGSIndex  =  0;
	Analysis_Add_Data(m_pDataset_GS_PkgAnalyze,   _T("Test"),  byFlagGSCstc[0]);
	Analysis_Add_Data(m_pDataset_GS_PkgAnalyze,   _T("DevVersion"), byFlagGSCstc[1]);
	Analysis_Add_Data(m_pDataset_GS_PkgAnalyze,   _T("PDUlength"),  byFlagGSCstc[2]);
	Analysis_Add_Data(m_pDataset_GS_PkgAnalyze,   _T("Channel"),  byFlagGSCstc[3]);
	Analysis_Add_Data(m_pDataset_GS_PkgAnalyze,   _T("VLAN_ID"),  byFlagGSCstc[4]);
	Analysis_Add_Data(m_pDataset_GS_PkgAnalyze,   _T("VLANPriority"),  byFlagGSCstc[5]);
	Analysis_Add_Data(m_pDataset_GS_PkgAnalyze,   _T("DstMAC"),  byFlagGSCstc[6]);
	Analysis_Add_Data(m_pDataset_GS_PkgAnalyze,   _T("ContrlRef"),  byFlagGSCstc[7]);
	Analysis_Add_Data(m_pDataset_GS_PkgAnalyze,   _T("GOOSEID"),  byFlagGSCstc[8]);
	Analysis_Add_Data(m_pDataset_GS_PkgAnalyze,   _T("DataSet"),  byFlagGSCstc[9]);
}

/*
0<data name="检修位"/>
1<data name="版本号"/>
2<data name="PDU长度"/>
3<data name="通道数"/>
4<data name="VLAN_ID"/>
5<data name="VLAN 优先级"/>
6<data name="目标MAC地址"/>
7<data name="控制块索引"/>
8<data name="GOOSE ID"/>
*/

// 写入单个GOOSE的异常；
void CX61850CapBase::UpdateDvmDeviceDatas_PkgAnalyz_GS_Single(CCapDeviceBase *pCapDevice,  long nGsIndex)
{
	if (m_pDataset_GS_PkgAnalyze == NULL)
	{
		return;
	}

	if (pCapDevice == NULL)
		return;

	CString strGSCstcID;
	strGSCstcID.Format(_T("Goose%d"),   nGsIndex + 1);
	CDvmData * pDataGS   =    (CDvmData *)m_pDataset_GS_PkgAnalyze->FindByID(strGSCstcID);

	if ((pDataGS == NULL)&&(pCapDevice->m_strID.GetLength()>2))
		//20220607 zhouhj 对应的报文异常统计data对象ID与对应的数据集DvmDataset对应的ID一致,只是前面少了ds字符,故在此处做处理,由于GOOSE之前定义的数据集包含Gout、Gin,实际并不是Goose%d
	{
		strGSCstcID = pCapDevice->m_strID.Mid(2);
		pDataGS   =    (CDvmData *)m_pDataset_GS_PkgAnalyze->FindByID(strGSCstcID);
	}

	if (pDataGS == NULL)
	{
		pDataGS   =  new CDvmData();
		pDataGS->m_strName   =  strGSCstcID;
		pDataGS->m_strID   =  strGSCstcID;
		m_pDataset_GS_PkgAnalyze->AddNewChild(pDataGS);
	}

	EPCAPPARSEDATAS oPrevDatas = pCapDevice->m_oPrevDatas;

	IecAnalysis_Update_SV_PkgAnalyze_val(pDataGS, IEC_PkgAnalyze_ID_Test, oPrevDatas.oDataGs.nTestMode);
	IecAnalysis_Update_SV_PkgAnalyze_val(pDataGS, IEC_PkgAnalyze_ID_DevVersion, oPrevDatas.oDataGs.nConfRev);
	IecAnalysis_Update_SV_PkgAnalyze_val(pDataGS, IEC_PkgAnalyze_ID_PDUlength, oPrevDatas.oDataGs.APDULen);

	IecAnalysis_Update_SV_PkgAnalyze_val(pDataGS, IEC_PkgAnalyze_ID_Channel,  oPrevDatas.oDataGs.nChCnt/*/8*/);//20220614 GOOSE通道长度飞固定
	IecAnalysis_Update_SV_PkgAnalyze_val(pDataGS, IEC_PkgAnalyze_ID_VLAN_ID, oPrevDatas.oDataGs.VLAN_ID);
	IecAnalysis_Update_SV_PkgAnalyze_val(pDataGS, IEC_PkgAnalyze_ID_VLANPriority, oPrevDatas.oDataGs.VLAN_P);
	IecAnalysis_Update_SV_PkgAnalyze_val(pDataGS, IEC_PkgAnalyze_ID_GOOSEID, CString(oPrevDatas.oDataGs.GOID) );
	IecAnalysis_Update_SV_PkgAnalyze_val(pDataGS, IEC_PkgAnalyze_ID_ContrlRef, CString(oPrevDatas.oDataGs.GORef) );

	CString strMac;
	strMac.Format(_T("%02X-%02X-%02X-%02X-%02X-%02X"), (unsigned char)oPrevDatas.destMAC[0], (unsigned char)oPrevDatas.destMAC[1], (unsigned char)oPrevDatas.destMAC[2]
	, (unsigned char)oPrevDatas.destMAC[3], (unsigned char)oPrevDatas.destMAC[4], (unsigned char)oPrevDatas.destMAC[5]);

	IecAnalysis_Update_SV_PkgAnalyze_val(pDataGS, IEC_PkgAnalyze_ID_DstMAC, strMac);
    IecAnalysis_Update_SV_PkgAnalyze_val(pDataGS, IEC_PkgAnalyze_ID_DataSet, CString(oPrevDatas.oDataGs.GODataSet));//wangtao add 20240509 报文探测增加DataSet比对 ，下同

}



// 添加GOOSE属性那几个小项；mym 2020-6-23
void CX61850CapBase::Analysis_Add_Atrri_Error(CCapDeviceBase *pCapDevice,  CDvmData * pDataParent,   int  nGsOr92 , int nGsIndex,   int nIndex)
{
	CString strItem[11];
	CString strGScstcID;
	if (pCapDevice == NULL)
		return;
	CDvmData * pDataGS   =  NULL;

	CIecCfgGinData* pCfgGSData = NULL;
	CIecCfg92Data* pCfgData92  = NULL;

	CString strDataValue;
	CString strCIecCfgValue;
	if (nGsOr92==1)
	{//GS
		pCfgGSData = (CIecCfgGinData*)pCapDevice->GetIecCfgData();

		if ( pCfgGSData==NULL)
			return;

		if (nIndex==0)
		{
			strDataValue.Format("%d",  pCapDevice->m_oPrevDatas.oDataGs.nTestMode);
			strCIecCfgValue.Format("%d",  pCfgGSData->m_bTest);
		}
		else if (nIndex==1)
		{
			strDataValue.Format("%d",  pCapDevice->m_oPrevDatas.oDataGs.nConfRev);
			strCIecCfgValue.Format("%d",  pCfgGSData->m_dwVersion);
		}  
		else if (nIndex==2)
		{
			strDataValue.Format("%d",  pCapDevice->m_oPrevDatas.oDataGs.APDULen);
			strCIecCfgValue.Format("%d", pCapDevice->m_oPrevDatas.oDataGs.APDULen);
		} 
		else if (nIndex==3)
		{
			strDataValue.Format("%d",  pCapDevice->m_oPrevDatas.oDataGs.nChCnt);
			strCIecCfgValue.Format("%d",  pCfgGSData->m_nChannelNum);
		}  
		else if (nIndex==4)
		{
			strDataValue.Format("%d",  pCapDevice->m_oPrevDatas.oDataGs.VLAN_ID);
			strCIecCfgValue.Format("%d",  pCfgGSData->m_dwVLandID);
		}   
		else if (nIndex==5)
		{
			strDataValue.Format("%d",  pCapDevice->m_oPrevDatas.oDataGs.VLAN_P);
			strCIecCfgValue.Format("%d",  pCfgGSData->m_dwVLandPriority);
		} 
		else if (nIndex==6)
		{
// 			char destOut[20] = {0};
// 			ByteToHexStr(	(unsigned char*) pCapDevice->m_oPrevDatas.destMAC, destOut, 6);
// 			destOut[12] = '\0';
			strDataValue = GetMacStringFromByte((unsigned char *)pCapDevice->m_oPrevDatas.destMAC);
// 			strDataValue.Insert(2, '-');			
// 			strDataValue.Insert(5, '-');	
// 			strDataValue.Insert(8, '-');	
// 			strDataValue.Insert(11, '-');	
// 			strDataValue.Insert(14, '-');	

			strCIecCfgValue =  pCfgGSData->m_strDestAddress;
		}
		else if (nIndex==7)
		{
			strDataValue =  pCapDevice->m_oPrevDatas.oDataGs.GORef;
			strCIecCfgValue  =  pCfgGSData->m_strgocbRef;
		} 
		else if (nIndex==8)
		{
			strDataValue = pCapDevice->m_oPrevDatas.oDataGs.GOID;
			strCIecCfgValue =  pCfgGSData->m_strGooseId;
		}
		else if (nIndex==9)
		{
			strDataValue = pCapDevice->m_oPrevDatas.oDataGs.GODataSet;
			strCIecCfgValue =  pCfgGSData->m_strDataSet;
		}

		strItem[0] = "$Test";
		strItem[1] = "$DevVersion";
		strItem[2] = "$PDUlength";
		strItem[3] = "$Channel";
		strItem[4] = "$VLAN_ID";
		strItem[5] = "$VLANPriority";
		strItem[6] = "$DstMAC";
		strItem[7] = "$ContrlRef";
		strItem[8] = "$GOOSEID";
		strItem[9] = "$DataSet";

		strGScstcID.Format(_T("Goose%d"),   nGsIndex + 1);
		pDataGS   =  (CDvmData *)pDataParent->FindByID(strGScstcID + strItem[nIndex] );
	}
	else if (nGsOr92==2)
	{//SV
		pCfgData92  = (CIecCfg92Data*)pCapDevice->GetIecCfgData();

		if(pCfgData92 == NULL)
			return;

		if (nIndex==0)
		{
			strDataValue.Format("%d",  pCapDevice->m_oPrevDatas.oData92.nTestMode);
			strCIecCfgValue.Format("%d",  pCapDevice->m_oPrevDatas.oData92.nTestMode);
		}
		else if (nIndex==1)
		{
			strDataValue.Format("%d",  pCapDevice->m_oPrevDatas.oData92.Asdu[0].confRev);
			strCIecCfgValue.Format("%d",  pCfgData92->m_dwVersion);
		}  
		else if (nIndex==2)
		{
			strDataValue.Format("%d",  pCapDevice->m_oPrevDatas.oData92.APDULen);
			strCIecCfgValue.Format("%d",  pCapDevice->m_oPrevDatas.oData92.APDULen);
		} 
		else if (nIndex==3)
		{
			strDataValue.Format("%d",  pCapDevice->m_oPrevDatas.oData92.nChCount/*/8*/);//20220614 zhouhj 已在赋值位置统一处理除以8的问题
			strCIecCfgValue.Format("%d",  pCfgData92->m_nChannelNum);
		}  
		else if (nIndex==4)
		{
			strDataValue.Format("%d",  pCfgData92->m_nPriority);
			strCIecCfgValue.Format("%d",  pCfgData92->m_nPriority);
		}   
		else if (nIndex==5)
		{
			strDataValue.Format("%d",  pCfgData92->m_nPriority);
			strCIecCfgValue.Format("%d",  pCfgData92->m_nPriority);
		} 
		else if (nIndex==6)
		{
			strDataValue.Format("%d",  pCapDevice->m_oPrevDatas.oData92.Asdu[0].smpSynch);
			strCIecCfgValue.Format("%d",  pCfgData92->m_nSyn);
		}
		else if (nIndex==7)
		{
			strDataValue.Format("%d",   pCfgData92->m_nSampleRate);
			strCIecCfgValue.Format("%d",  pCfgData92->m_nSampleRate);
		} 
		else if (nIndex==8)
		{
			strDataValue.Format("%d",  pCapDevice->m_oPrevDatas.oData92.Num_ASDU);
			strCIecCfgValue.Format("%d",  pCfgData92->m_nAsduNum);
		}
		else if (nIndex==9)
		{
// 			char destOut[20] = {0};
// 			ByteToHexStr((unsigned char*)pCapDevice->m_oPrevDatas.destMAC, destOut, 6);
// 			destOut[12] = '\0';
			strDataValue = GetMacStringFromByte((unsigned char *)pCapDevice->m_oPrevDatas.destMAC);	

// 			strDataValue.Insert(2, '-');			
// 			strDataValue.Insert(5, '-');	
// 			strDataValue.Insert(8, '-');	
// 			strDataValue.Insert(11, '-');	
// 			strDataValue.Insert(14, '-');	

			strCIecCfgValue  =  pCfgData92->m_strDestAddress;
		} 
		else if (nIndex==10)
		{
			strDataValue = pCapDevice->m_oPrevDatas.oData92.Asdu[0].SVID;
			strCIecCfgValue =  pCfgData92->m_strSVID;
		}

		strItem[0] = "$TestPos";
		strItem[1] = "$DevVersion";
		strItem[2] = "$PDUlength";
		strItem[3] = "$Channel";
		strItem[4] = "$VLAN_ID";
		strItem[5] = "$VLANPriority";
		strItem[6] = "$SynState";
		strItem[7] = "$SampRate";
		strItem[8] = "$ASDUNumber";
		strItem[9] = "$DstMAC";
		strItem[10] = "$SVID";
		strGScstcID.Format(_T("SV%d"),   nGsIndex + 1);
		pDataGS   =  (CDvmData *)pDataParent->FindByID(strGScstcID + strItem[nIndex] );
	}

	if (pDataGS == NULL)
	{
		pDataGS   =  new CDvmData();
		pDataGS->m_strName   =  strGScstcID;
		pDataGS->m_strID   =  strGScstcID;
		pDataParent->AddNewChild(pDataGS);
	}

	Analysis_Add_Value(pDataGS,   strGScstcID  + strItem[nIndex] +  _T("$stand"),  strCIecCfgValue);
	Analysis_Add_Value(pDataGS,   strGScstcID  + strItem[nIndex] + _T("$actual"),  strDataValue);

	if (nGsOr92==1)
	{
		CString str;

		str.Format(" %d 帧",  pCapDevice->m_dwFlagGSCstc[nIndex]);// = "相同";

		Analysis_Add_Value(pDataGS,   strGScstcID  + strItem[nIndex]  + _T("$rslt"),    str);//pCapDevice->m_byFlagGSCstc[nIndex]);
	}
	else if (nGsOr92==2)
	{
		CString str;


		str.Format(" %d 帧",  pCapDevice->m_dwFlagSVCstc[nIndex]);// = "相同";

		Analysis_Add_Value(pDataGS,   strGScstcID  + strItem[nIndex]  + _T("$rslt"),    str);
	}
}


//加载配置文件，复位故障计算以及报文分析  lijunqing 2020-6-17
void CX61850CapBase::ResetRecord()
{
}

void CX61850CapBase::ResetRecord_RecordTest()
{
}

void CX61850CapBase::ResetRecord_Analysis()
{
	m_nHasUpdateSVDelayData = 0;
}


void CX61850CapBase::UpdateDvmDeviceDatas_RecordTest()
{
	UpdateDvmDeviceDatas_RecordTest_SV();
	UpdateDvmDeviceDatas_RecordTest_SV_Power();
	UpdateDvmDeviceDatas_RecordTest_SV_Vector();
	UpdateDvmDeviceDatas_RecordTest_SV_AD();//根据之前计算的通道幅值、相位、频率,计算双AD相关数值
	UpdateDvmDeviceDatas_RecordTest_THD();

	//for debug  可以在此处添加更新功率的数据集的代码
}

void CX61850CapBase::UpdateDvmDeviceDatas_RecordTest_SV()
{
	if (g_oCapAnalysisConfig.m_bSvAnalysis || g_oCapAnalysisConfig.m_bPkgConsistence)//20220618 zhouhj 报文统计时不进行计算
	{
		return;
	}

	CDvmData *pData = NULL;
//	CRtVariable *pVariable = NULL;
	long nIndex = 0;
	DWORD *pdwVariablesAddr = m_oCapDeviceChRecordMngr.m_pRecordTest->m_pVariables->GetVariablesAddr();
	m_nMaxSvChannelsMap = 0;

// 	pVariable = (CRtVariable*) (*pdwVariablesAddr);
// 
// 	if (pVariable != NULL)
// 	{
// 		if (pVariable->m_oCurrValue.dFundPhase > 0.1)
// 		{
// 			int i = 0;
// 		}
// 	}

	BOOL bIsFT3Mode = m_oCapDeviceAll.IsFT3Rcd();

	STTVARIABLESRTVALUES oSttVarValues;
	g_oStttVariablesRtValueBuffer.GetLast(oSttVarValues);
	long nVarIndex = 0;

	for (nIndex=0; nIndex<MAX_RTVARIABLES; nIndex++)
	{
// 		if (pdwVariablesAddr[nIndex] != 0 &&  m_dwDvmSvChannels[nIndex] != 0)
// 		{
// 			UpdateDvmDeviceDatas_RecordTest_SV( (CRtVariable*)pdwVariablesAddr[nIndex], (CDvmData*)m_dwDvmSvChannels[nIndex]);
// 		}

		if (nVarIndex >= oSttVarValues.nCount)
		{
			break;
		}

		if (pdwVariablesAddr[nIndex] != 0)
		{
			if (m_dwDvmSvChannels[nIndex] != 0)
		{
				UpdateDvmDeviceDatas_RecordTest_SV(&oSttVarValues.oRtValues[nVarIndex], (CDvmData*)m_dwDvmSvChannels[nIndex]
				,!bIsFT3Mode);
			}

			nVarIndex++;
		}
	}
}

void CX61850CapBase::UpdateDvmDeviceDatas_RecordTest_SV_AD()
{
	if (!g_oCapAnalysisConfig.m_bSmv_AD)
	{
		return;
	}

	if (m_pDvmDevice == NULL)
	{
		return;
	}

	CDvmLogicDevice *pLDevice = (CDvmLogicDevice*)m_pDvmDevice->FindByClassID(DVMCLASSID_CDVMLOGICDEVICE);

	if (pLDevice == NULL)
	{
		return;
	}

	POS pos = pLDevice->GetHeadPosition();
	CString strDatasetID, strIndex;
	CString strPowerID;
	strPowerID = _T("$");
	strPowerID +=CAP_DATASET_MAP_ID_AD;
	CDvmDataset *pDataset = NULL;

	while (pos != NULL)
	{
		CDvmDataset *pDataset = (CDvmDataset *)pLDevice->GetNext(pos);
		long nPos = pDataset->m_strID.Find(strPowerID);

		if (nPos < 0)
		{
			continue;
		}

		UpdateDvmDeviceDatas_RecordTest_SV_AD(pDataset);
	}
}

void CX61850CapBase::UpdateDataValue(CExBaseList *pParent, const CString &strAttrID, double fValue,long nPrecision)
{
	if (pParent == NULL)
		return;

	CString strID = pParent->m_strID + strAttrID;
	CDvmValue *pValue = (CDvmValue*)pParent->FindByID(strID);

	if (pValue == NULL)
	{
		return;
	}

	CString strFormat;
	strFormat.Format(_T("%%.%ldlf"), nPrecision);
	pValue->m_strValue.Format(strFormat.GetString(),fValue);
}

void CX61850CapBase::UpdateDataValueAng(CExBaseList *pParent, const CString &strAttrID, double fValue)
{
	if (pParent == NULL)
		return;

	CString strID = pParent->m_strID + strAttrID;
	CDvmValue *pValue = (CDvmValue*)pParent->FindByID(strID);

	if (pValue == NULL)
	{
		return;
	}

	pValue->m_strValue.Format(_T("%.2f"), fValue);
}

void CX61850CapBase::UpdateDataValue(CDvmData *pData, long nHarmIndex, double fValue)
{
	if (pData == NULL)
		return;

	CString strID;
    strID.Format(_T("%s$h%d"), pData->m_strID.GetString(), nHarmIndex);
	CDvmValue *pValue = (CDvmValue*)pData->FindByID(strID);

	if (pValue == NULL)
	{
		return;
	}

	pValue->m_strValue.Format(_T("%.3f"), fValue);
}

void CX61850CapBase::UpdateDvmDeviceDatas_RecordTest_SV(CRtVariable *pVariable, CDvmData *pData)
{
	if (pVariable == NULL || pData == NULL)
	{
		return;
	}

	RTCHANNELATTRVALUE *pAttrValues = &pVariable->m_oCurrValue;
	UpdateDvmDeviceDatas_RecordTest_SV(pAttrValues, pData,TRUE);
}

void CX61850CapBase::UpdateDvmDeviceDatas_RecordTest_SV(RTCHANNELATTRVALUE *pAttrValues, CDvmData *pData,BOOL bIs92Datas)
{
	if (!g_oCapAnalysisConfig.m_bAnalysisData_PhaseDelt)//20220817 zhouhj 做角差计算时,相位值会单独更新,此处不再赋值,防止重复赋值
	{
		if (bIs92Datas)//zhouhj 2023.11.20 9-2报文时,使用有效相位,FT3报文时,使用基波相位
		{
			UpdateDataValueAng(pData, _T("$ang"),  pAttrValues->dEffecPhase);
		}
		else
		{
			UpdateDataValueAng(pData, _T("$ang"),  pAttrValues->dFundPhase);
		}

		UpdateDataValue(pData, _T("$freq"),  pAttrValues->dFrequency);
	}

	if (fabs(pAttrValues->dFrequency)<0.0001)//20220624 zhouhj 频率为0时,默认为直流,平均值为直流值
	{
		UpdateDataValue(pData, _T("$mag"), pAttrValues->dAverageValue);
		UpdateDataValue(pData, _T("$Base"), 0.0f);
		UpdateDataValue(pData, _T("$avg"), pAttrValues->dAverageValue);
		UpdateDataValue(pData, _T("$DC"), pAttrValues->dAverageValue);
	}
	else//频率不为0时,默认不含直流
	{
		UpdateDataValue(pData, _T("$mag"), pAttrValues->dEffecValue,6);// 合并单元测试时,为保证比差计算精度,此处保留到6位
		UpdateDataValue(pData, _T("$Base"), pAttrValues->dFundValue);
		UpdateDataValue(pData, _T("$avg"), pAttrValues->dAverageValue);
		UpdateDataValue(pData, _T("$DC"), 0.0f);
	}

	//UpdateDataValue(pData, _T("$ang"),  pAttrValues->dFundPhase);

//	long nHarmIndex  = 2;
	for (long nHarmIndex  =  2;  nHarmIndex  <= g_nXSttRcdInitChDvmData_Harm;  nHarmIndex++)//20220611 zhouhj 谐波次数从20次,改为到22次
	{
		UpdateDataValue(pData,  nHarmIndex /* +  2*/,  pAttrValues->dHarmValue[nHarmIndex-2]);
	}

	//mym add 2020-8-17 这里可以添加比差，角差，频差，关键是要获得那个数据集dsRcdStep6U6I中的值；
}

void CX61850CapBase::UpdateDvmDeviceDatas_RecordTest_THD()
{
	if (m_pDataset_THD == NULL)
	{
		return;
	}

	if (g_oCapAnalysisConfig.m_bSvAnalysis || g_oCapAnalysisConfig.m_bPkgConsistence)//20220618 zhouhj 报文统计时不进行畸变率计算
	{
		return;
	}

	CDvmData *pData = NULL;
	CRtVariable *pVariable = NULL;
	long nIndex = 0;
	DWORD *pdwVariablesAddr = m_oCapDeviceChRecordMngr.m_pRecordTest->m_pVariables->GetVariablesAddr();
	m_nMaxSvChannelsMap = 0;

	for (nIndex=0; nIndex<MAX_RTVARIABLES; nIndex++)
	{
		pVariable = (CRtVariable*) (*pdwVariablesAddr);

		if (pdwVariablesAddr[nIndex] == 0 ||  m_dwDvmSvChannels[nIndex] == 0)
		{
			continue;
		}

		pVariable = (CRtVariable *)pdwVariablesAddr[nIndex];
		Analysis_Add_Data(m_pDataset_THD, pVariable->m_strID + _T("_THD"), pVariable->m_oCurrValue.dTHD);
	}
}

void CX61850CapBase::ClearDatasetsMap()
{
	m_pDataset_MUTestCB = NULL;
	m_pDataset_Discrete = NULL;
	m_pDataset_THD = NULL;
	m_pDataset_SVErr = NULL;
	m_pDataset_GSErr = NULL;
	m_pDataset_SV_PkgAnalyze = NULL;
	m_pDataset_SV_His = NULL;
	m_pDataset_GS_PkgAnalyze = NULL;
	m_pDataset_SVInst = NULL;
	m_pDataset_SVDelay = NULL;
	m_pDataset_Report = NULL;
	m_pDataset_SVSyncDelt = NULL;
	m_pDataset_GSSyncDelt = NULL;
	m_pDataset_LinkState = NULL;
	m_pDataset_RcdStep6U6I = NULL;
	m_pDataset_RcdStepResponse = NULL;
	m_pDataset_IEDTest = NULL;
	m_pDataset_Gin1 = NULL;
	m_pDataset_Time = NULL;
	m_pDataset_CurrErrorRange = NULL;
	m_pDataset_ErrorRanges = NULL;
	m_pDataset_StateValueChangedRlt = NULL;
	m_pDataset_TestFunSelect = NULL;
}

void CX61850CapBase::ClearMUTestResults()
{
	if (m_pDataset_MUTestCB == NULL)
	{
		return;
	}

	CDvmData *pDvmData = NULL;	
	POS pos = m_pDataset_MUTestCB->GetHeadPosition();

	if (pos != NULL)
	{
		m_pDataset_MUTestCB->GetNext(pos);
	}

	CDvmValue *pCurrValue = NULL,*pChildValue = NULL;

	while (pos != NULL)
	{
		pDvmData = (CDvmData*)m_pDataset_MUTestCB->GetNext(pos);

		POS pos_value = pDvmData->GetHeadPosition();

		while(pos_value)
		{
			pCurrValue = (CDvmValue *)pDvmData->GetNext(pos_value);

			POS pos_child_value = pCurrValue->GetHeadPosition();

			while(pos_child_value)
			{
				pChildValue = (CDvmValue *)pCurrValue->GetNext(pos_child_value);
				pChildValue->m_strValue = _T("");
			}
		}
	}

	if (m_pDataset_MUTimeRlt != NULL)
	{
		pos = m_pDataset_MUTimeRlt->GetHeadPosition();

		while (pos != NULL)
		{
			pDvmData = (CDvmData *)m_pDataset_MUTimeRlt->GetNext(pos);
			pDvmData->m_strValue = _T("0");
		}
	}

	if ((m_strDatasetMapID_MUTestCB.GetLength()<= 2)||(m_pDataset_SVDelay == NULL))
	{
		return;
	}

	CString strSVCBName;
	strSVCBName = m_strDatasetMapID_MUTestCB.Mid(2);
	CDvmData *pDelayData = (CDvmData*)m_pDataset_SVDelay->FindByID(strSVCBName);
	g_oSVDelayTickCount.Enter();

	if (pDelayData != NULL)
	{
		pos = pDelayData->GetHeadPosition();

		while (pos != NULL)
		{
			pCurrValue = (CDvmValue *)pDelayData->GetNext(pos);
			pCurrValue->m_strValue = _T("");
		}
	}


	////chenling 2024.6.4 选择控制块复归
	//CCapDeviceBase *pSelCapDevice = (CCapDeviceBase*)m_oCapDeviceAll.FindByID(m_strDatasetMapID_MUTestCB);
	//if (pSelCapDevice != NULL)
	//{
	//	pSelCapDevice->Reset();
	//}
}

void CX61850CapBase::CalMuTimeTestRlt_NoPPS()
{
	if (!g_nMuTimeTest_UseNoPPS)
	{
		return;
	}

	if ((m_pDataset_MUTimeRlt == NULL)||(m_pDataset_SV_His == NULL)
		||(m_pDataset_SVDelay == NULL))
	{
		return;
	}

	CDvmData *pHasUsingTime = (CDvmData*)m_pDataset_MUTimeRlt->FindByID(STT_MUTEST_HasUsingTime);
	CDvmData *pMaxErrTime = (CDvmData*)m_pDataset_MUTimeRlt->FindByID(STT_MUTEST_MaxErrTime);
	CDvmData *pMinErrTime = (CDvmData*)m_pDataset_MUTimeRlt->FindByID(STT_MUTEST_MinErrTime);
	CDvmData *pCurrErrTime = (CDvmData*)m_pDataset_MUTimeRlt->FindByID(STT_MUTEST_CurrErrTime);
	CDvmData *pAverageErrTime = (CDvmData*)m_pDataset_MUTimeRlt->FindByID(STT_MUTEST_AverageErrTime);
	CDvmData *pMUTimeResult = (CDvmData*)m_pDataset_MUTimeRlt->FindByID(STT_MUTEST_MUTimeResult);

	if((pHasUsingTime == NULL)||(pMaxErrTime == NULL)||(pMinErrTime == NULL)
		||(pCurrErrTime == NULL)||(pAverageErrTime == NULL)||(pMUTimeResult == NULL))
		return;

	CString strSVX_Data;
	strSVX_Data = _T("SV1");

	if (m_strDatasetMapID_MUTestCB.GetLength()>2)
	{
		strSVX_Data = m_strDatasetMapID_MUTestCB.Mid(2);
	} 

	CDvmData *pDelayData = (CDvmData*)m_pDataset_SVDelay->FindByID(strSVX_Data);
	CDvmData *pHisData = (CDvmData*)m_pDataset_SV_His->FindByID(strSVX_Data);

	if ((pDelayData == NULL)||(pHisData == NULL))
	{
		return;
	}

	CString strPath;
	strPath = strSVX_Data;
	strPath += STT_RcdInit_DL_TestCount;
	long nTestCount = -1;
	CDvmValue *pTestCountValue = (CDvmValue*)pDelayData->FindByID(strPath);

	if (pTestCountValue == NULL)
	{
		return;
	}

	nTestCount = CString_To_long(pTestCountValue->m_strValue);
	strPath = strSVX_Data;
	strPath += STT_MUTEST_DL_RealDelay;
	CDvmValue *pRealDelayValue = (CDvmValue*)pHisData->FindByID(strPath);

	if (pRealDelayValue == NULL)
	{
		return;
	}

	strPath += _T("$TestCount");
	CDvmValue *pCurrValue = NULL;
	double dMaxErrorValue = 0.0f,dMinErrorValue = 0.0f,dCurrErrorValue = 0.0f,dAverageErrorValue = 0.0f;
	double dCompenTime = 0.0f,dTotalValue = 0.0f,TmpTime1 = 0.0f,TmpTime2 = 0.0f;//补偿时间
	POS pos = pRealDelayValue->GetHeadPosition();
	long nTestIndex = 0,nValidTestIndex = 0;
	BOOL bHasGetCompenTime = FALSE;

	while(pos && (nTestIndex<nTestCount))
	{
		pCurrValue = (CDvmValue *)pRealDelayValue->GetNext(pos);

		if (pCurrValue->m_strID.Find(strPath) < 0)
		{
			continue;
		}

		nTestIndex++;
		TmpTime2 = CString_To_double(pCurrValue->m_strValue);

		if (!bHasGetCompenTime)
		{
			if (fabs(TmpTime2 - TmpTime1) < 1.0f)
			{
				dCompenTime = TmpTime2;
				bHasGetCompenTime = TRUE;
			}
			else
			{
				TmpTime1 = TmpTime2;

				if (nTestIndex >20)
				{
					CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("测试次数超过20次,还未找到补偿时间值(%ld)."),TmpTime2);
				}
				continue;
			}
		}

		nValidTestIndex++;
		dCurrErrorValue = TmpTime2 - dCompenTime;

		if (nValidTestIndex == 1)
		{
			dMinErrorValue = dCurrErrorValue;
			dMaxErrorValue = dCurrErrorValue;
			dAverageErrorValue = dCurrErrorValue;
			dTotalValue = dCurrErrorValue;
		}
		else
		{
			dTotalValue += dCurrErrorValue;

			if (fabs(dCurrErrorValue) < fabs(dMinErrorValue))
			{
				dMinErrorValue = dCurrErrorValue;
			}

			if (fabs(dCurrErrorValue) > fabs(dMaxErrorValue))
			{
				dMaxErrorValue = dCurrErrorValue;
			}

			dAverageErrorValue = dTotalValue/nValidTestIndex;
		}
	}

	double dUseTime = nTestIndex*g_fMUTestTimeEach;
	pHasUsingTime->m_strValue.Format(_T("%lf"),dUseTime);
	pCurrErrTime->m_strValue.Format(_T("%lf"),dCurrErrorValue);
	pMaxErrTime->m_strValue.Format(_T("%lf"),dMaxErrorValue);
	pMinErrTime->m_strValue.Format(_T("%lf"),dMinErrorValue);
	pAverageErrTime->m_strValue.Format(_T("%lf"),dAverageErrorValue);
//	pAverageErrTime->m_strValue.Format(_T("%lf"),dAverageErrorValue);

//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("[CalMuTimeTestRlt_NoPPS]dMaxErrorValue=%lf;dMinErrorValue=%lf;"),
//		dMaxErrorValue,dMinErrorValue);

	if ((fabs(dMaxErrorValue)<4)&&(fabs(dMinErrorValue)<4))
	{
		pMUTimeResult->m_strValue = _T("1");
	} 
	else
	{
		pMUTimeResult->m_strValue = _T("0");
	}
}

void CX61850CapBase::UpdateDvmDeviceDatas_RecordTest_SV_Power()
{
	if (!g_oCapAnalysisConfig.m_bSmv_Power)
	{
		return;
	}

	if (m_pDvmDevice == NULL)
	{
		return;
	}

	CDvmLogicDevice *pLDevice = (CDvmLogicDevice*)m_pDvmDevice->FindByClassID(DVMCLASSID_CDVMLOGICDEVICE);

	if (pLDevice == NULL)
	{
		return;
	}

	POS pos = pLDevice->GetHeadPosition();
	CString strDatasetID, strIndex;
	CString strPowerID;
	strPowerID = _T("$");
	strPowerID +=CAP_DATASET_MAP_ID_Power;
	CDvmDataset *pDataset = NULL;
	
	while (pos != NULL)
	{
		CDvmDataset *pDataset = (CDvmDataset *)pLDevice->GetNext(pos);
		long nPos = pDataset->m_strID.Find(strPowerID);

		if (nPos < 0)
		{
			continue;
		}

		UpdateDvmDeviceDatas_RecordTest_SV_Power(pDataset);
	}
}


/*
<dataset name="0X4012_功率" id="dsSV1$Power" data-type="" write-mode="0" index="0">
	<data name="功率1" id="P1" data-type="struct" value="">
		<value name="A相功率" id="P1$A" data-type="int" value="">
			<value name="电压" id="P1$A$U" data-type="string" value="电压A相1">
				<value name="有效值" id="P1$A$U$mag" data-type="float" value="57.735"/>
				<value name="相位" id="P1$A$U$ang" data-type="float" value="0"/>
			</value>
			<value name="电流" id="P1$A$I" data-type="string" value="保护电流A相1">
				<value name="有效值" id="P1$A$I$mag" data-type="float" value="5.001"/>
				<value name="相位" id="P1$A$I$ang" data-type="float" value="0"/>
			</value>
			<value name="有功" id="P1$A$P" data-type="float" value="0"/>
			<value name="无功" id="P1$A$Q" data-type="float" value="0"/>
			<value name="视在功率" id="P1$A$S" data-type="float" value="0"/>
			<value name="功率因子" id="P1$A$coef" data-type="float" value="0"/>
		</value>
		<value name="B相功率" id="P1$B" data-type="int" value="">
			........................
		</value>
		<value name="C相功率" id="P1$C" data-type="int" value="">
			........................
		</value>
		<value name="三相功率" id="P1$ABC" data-type="int" value="">
		<value name="有功" id="P1$ABC$P" data-type="float" value="0"/>
		<value name="无功" id="P1$ABC$Q" data-type="float" value="0"/>
		<value name="视在功率" id="P1$ABC$S" data-type="float" value="0"/>
		<value name="功率因子" id="P1$ABC$coef" data-type="float" value="0"/>
		</value>
	</data>
</dataset>
*/
void CX61850CapBase::UpdateDvmDeviceDatas_RecordTest_SV_Power(CDvmDataset *pDataset_Power)
{
	POS pos = pDataset_Power->GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)pDataset_Power->GetNext(pos);
		UpdateDvmDeviceDatas_RecordTest_SV_Power(pData);
	}
}

void CX61850CapBase::UpdateDvmDeviceDatas_RecordTest_SV_AD(CDvmDataset *pDataset_AD)
{
	POS pos = pDataset_AD->GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)pDataset_AD->GetNext(pos);
		UpdateDvmDeviceDatas_RecordTest_SV_AD(pData);
	}
}

void CX61850CapBase::UpdateDvmDeviceDatas_RecordTest_SV_Power(CDvmData *pPower)
{
	CDvmValue *pA = NULL, *pB=NULL, *pC = NULL;
	pA = (CDvmValue *)pPower->FindByID_MmsAttr(_T("$A"));
	pB = (CDvmValue *)pPower->FindByID_MmsAttr(_T("$B"));
	pC = (CDvmValue *)pPower->FindByID_MmsAttr(_T("$C"));

	double dP_A, dQ_A, dW_A, dCoef_A;
	double dP_B, dQ_B, dW_B, dCoef_B;
	double dP_C, dQ_C, dW_C, dCoef_C;
	double dP, dQ, dW, dCoef;

	UpdateDvmDeviceDatas_RecordTest_SV_Power_CH(pA, dP_A, dQ_A, dW_A, dCoef_A);
	UpdateDvmDeviceDatas_RecordTest_SV_Power_CH(pB, dP_B, dQ_B, dW_B, dCoef_B);
	UpdateDvmDeviceDatas_RecordTest_SV_Power_CH(pC, dP_C, dQ_C, dW_C, dCoef_C);

	CDvmValue *pP = (CDvmValue*)pPower->FindByID_MmsAttr(_T("$P"));
	CDvmValue *pQ = (CDvmValue*)pPower->FindByID_MmsAttr(_T("$Q"));
	CDvmValue *pW = (CDvmValue*)pPower->FindByID_MmsAttr(_T("$S"));
	CDvmValue *pCoef = (CDvmValue*)pPower->FindByID_MmsAttr(_T("$coef"));

	dP = dP_A + dP_B + dP_C;
	dQ = dQ_A + dQ_B + dQ_C;
	dW = dW_A + dW_B + dW_C;
	dCoef = dP / dW;
	pP->m_strValue.Format(_T("%.3f"), dP);
	pQ->m_strValue.Format(_T("%.3f"), dQ);
	pW->m_strValue.Format(_T("%.3f"), dW);
	pCoef->m_strValue.Format(_T("%.3f"), dCoef);
}

void CX61850CapBase::UpdateDvmDeviceDatas_RecordTest_SV_AD(CDvmData *pDataAD)
{
	CDvmValue *pCh1 = NULL, *pCh2=NULL, *pDiffValue_mag = NULL, *pDiffValue_magAbs = NULL, *pDiffValue_ang = NULL, *pDiffValue_angAbs = NULL;
	pCh1 = (CDvmValue *)pDataAD->FindByID_MmsAttr(_T("$Ch1"));
	pCh2 = (CDvmValue *)pDataAD->FindByID_MmsAttr(_T("$Ch2"));
	pDiffValue_mag = (CDvmValue *)pDataAD->FindByID_MmsAttr(_T("$dmag"));
	pDiffValue_magAbs = (CDvmValue *)pDataAD->FindByID_MmsAttr(_T("$dmag_abs"));
	pDiffValue_ang = (CDvmValue *)pDataAD->FindByID_MmsAttr(_T("$dang"));
	pDiffValue_angAbs = (CDvmValue *)pDataAD->FindByID_MmsAttr(_T("$dang_abs"));


	double dCh1_mag = 0.0f, dCh1_ang = 0.0f, dCh1_fre = 0.0f;
	double dCh2_mag = 0.0f, dCh2_ang = 0.0f, dCh2_fre = 0.0f;
	double dDiffValue_mag,dDiffValue_magAbs,dDiffValue_ang,dDiffValue_angAbs;

	UpdateDvmDeviceDatas_RecordTest_SV_CH_Attr(pCh1, dCh1_mag,dCh1_ang,dCh1_fre);
	UpdateDvmDeviceDatas_RecordTest_SV_CH_Attr(pCh2, dCh2_mag,dCh2_ang,dCh2_fre);

	dDiffValue_mag = dCh1_mag - dCh2_mag;
	dDiffValue_magAbs = fabs(dDiffValue_mag);
	dDiffValue_ang = dCh1_ang - dCh2_ang;
	dDiffValue_angAbs = fabs(dDiffValue_ang);

	if (pDiffValue_mag != NULL)
	{
		pDiffValue_mag->m_strValue.Format(_T("%.3lf"), dDiffValue_mag);
	}

	if (pDiffValue_magAbs != NULL)
	{
		pDiffValue_magAbs->m_strValue.Format(_T("%.3lf"), dDiffValue_magAbs);
	}

	if (pDiffValue_ang != NULL)
	{
		pDiffValue_ang->m_strValue.Format(_T("%.3lf"), dDiffValue_ang);
	}

	if (pDiffValue_angAbs != NULL)
	{
		pDiffValue_angAbs->m_strValue.Format(_T("%.3lf"), dDiffValue_angAbs);
	}
}

/*
暂时不做数据指针的有效性检查
*/
void CX61850CapBase::UpdateDvmDeviceDatas_RecordTest_SV_Power_CH(CDvmValue *pCh, double &dP, double &dQ, double &dW, double &dCoef)
{
	CDvmValue *pU = NULL, *pI=NULL;
	pU = (CDvmValue*)pCh->FindByID_MmsAttr(_T("$U"));
	pI = (CDvmValue*)pCh->FindByID_MmsAttr(_T("$I"));
	CDvmValue *pP = (CDvmValue*)pCh->FindByID_MmsAttr(_T("$P"));
	CDvmValue *pQ = (CDvmValue*)pCh->FindByID_MmsAttr(_T("$Q"));
	CDvmValue *pW = (CDvmValue*)pCh->FindByID_MmsAttr(_T("$S"));
	CDvmValue *pCoef = (CDvmValue*)pCh->FindByID_MmsAttr(_T("$coef"));

	double dU_mag = 0, dU_ang = 0, dI_mag = 0, dI_ang = 0, dFreq=0;
	UpdateDvmDeviceDatas_RecordTest_SV_CH_Attr(pU, dU_mag, dU_ang, dFreq);
	UpdateDvmDeviceDatas_RecordTest_SV_CH_Attr(pI, dI_mag, dI_ang, dFreq);

	double dAngDelta = /*fabs*/(dU_ang - dI_ang) * _PI_D_180;

	dP  = dU_mag * dI_mag * cos (dAngDelta);
	dQ = dU_mag * dI_mag * sin (dAngDelta);
	dP = fabs(dP);
//	dQ = /*fabs*/(dQ);
	dW = dU_mag * dI_mag;

	if (dW > 0)
	{
		dCoef = dP / dW;
	}
	else
	{
		dCoef = 1;
	}

	pP->m_strValue.Format(_T("%.3f"), dP);
	pQ->m_strValue.Format(_T("%.3f"), dQ);
	pW->m_strValue.Format(_T("%.3f"), dW);
	pCoef->m_strValue.Format(_T("%.3f"), dCoef);
}

void CX61850CapBase::UpdateDvmDeviceDatas_RecordTest_SV_CH_Attr(CDvmValue *pCh, double &dMag, double &dAng, double &dFreq)
{
	CDvmValue *pMag = (CDvmValue*)pCh->FindByID_MmsAttr(_T("$mag"));
	CDvmValue *pAng = (CDvmValue*)pCh->FindByID_MmsAttr(_T("$ang"));
	
	if ((pMag == NULL)||(pAng == NULL))
	{
		return;
	}

	pMag->m_strValue = ((CDvmValue*)pMag->m_dwItemData)->m_strValue;
	pAng->m_strValue = ((CDvmValue*)pAng->m_dwItemData)->m_strValue;
	dMag = CString_To_double(pMag->m_strValue);
	dAng = CString_To_double(pAng->m_strValue);
}

void CX61850CapBase::UpdateDvmDeviceDatas_RecordTest_SV_Vector()
{
	if (!g_oCapAnalysisConfig.m_bSmv_Vector)
	{
		return;
	}

	if (m_pDvmDevice == NULL)
	{
		return;
	}

	CDvmLogicDevice *pLDevice = (CDvmLogicDevice*)m_pDvmDevice->FindByClassID(DVMCLASSID_CDVMLOGICDEVICE);

	if (pLDevice == NULL)
	{
		return;
	}

	POS pos = pLDevice->GetHeadPosition();
	CString strDatasetID, strIndex;
	CString strPowerID;
	strPowerID = _T("$");
	strPowerID +=CAP_DATASET_MAP_ID_Vector;
	CDvmDataset *pDataset = NULL;

	while (pos != NULL)
	{
		CDvmDataset *pDataset = (CDvmDataset *)pLDevice->GetNext(pos);
		long nPos = pDataset->m_strID.Find(strPowerID);

		if (nPos < 0)
		{
			continue;
		}

		UpdateDvmDeviceDatas_RecordTest_SV_Vector(pDataset);
	}
}

void CX61850CapBase::UpdateDvmDeviceDatas_RecordTest_SV_Vector(CDvmDataset *pDataset)
{
	POS pos = pDataset->GetHeadPosition();
	CDvmData *pVector = NULL;

	while (pos != NULL)
	{
		pVector = (CDvmData *)pDataset->GetNext(pos);
		UpdateDvmDeviceDatas_RecordTest_SV_Vector(pVector);
	}
}


/*
<data name="Vector1" id="Vector1" data-type="U" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step="">
	<value name="A" id="Vector1$A" data-type="" value="A相电压-电压A相1">
		<value name="幅值" id="SV2_U1_Ua2$mag" data-type="FLOAT" value="0.00"/>
		<value name="相位" id="SV2_U1_Ua2$ang" data-type="FLOAT" value="0.00"/>
		<value name="频率" id="SV2_U1_Ua2$freq" data-type="FLOAT" value="50.00"/>
	</value>
	<value name="B" id="Vector1$B" data-type="" value="B相电压-电压B相1">
		<value name="幅值" id="SV2_U3_Ub2$mag" data-type="FLOAT" value="0.00"/>
		<value name="相位" id="SV2_U3_Ub2$ang" data-type="FLOAT" value="0.00"/>
		<value name="频率" id="SV2_U3_Ub2$freq" data-type="FLOAT" value="50.00"/>
	</value>
	<value name="C" id="Vector1$C" data-type="" value="C相电压-电压C相1">
		<value name="幅值" id="SV2_U5_Uc2$mag" data-type="FLOAT" value="0.00"/>
		<value name="相位" id="SV2_U5_Uc2$ang" data-type="FLOAT" value="0.00"/>
		<value name="频率" id="SV2_U5_Uc2$freq" data-type="FLOAT" value="50.00"/>
	</value>
	<value name="Positive" id="Vector1$Positive" data-type="" value="Positive">
		<value name="$mag" id="Vector1$Positive$mag" data-type="float" value=""/>
		<value name="$ang" id="Vector1$Positive$ang" data-type="float" value=""/>
	</value>
	<value name="Negative" id="Vector1$Negative" data-type="" value="Negative">
		<value name="$mag" id="Vector1$Negative$mag" data-type="float" value=""/>
		<value name="$ang" id="Vector1$Negative$ang" data-type="float" value=""/>
	</value>
	<value name="Zero" id="Vector1$Zero" data-type="" value="Zero">
		<value name="$mag" id="Vector1$Zero$mag" data-type="float" value=""/>
		<value name="$ang" id="Vector1$Zero$ang" data-type="float" value=""/>
	</value>
</data>
*/

//#define USE_Old_SequenceCal_

# ifndef USE_Old_SequenceCal_
#include "../BaseClass/ComplexNumber.h"
#endif

void CX61850CapBase::UpdateDvmDeviceDatas_RecordTest_SV_Vector(CDvmData *pVector)
{
	CDvmValue *pA = (CDvmValue*)pVector->FindByID_MmsAttr(_T("$A"));
	CDvmValue *pB = (CDvmValue*)pVector->FindByID_MmsAttr(_T("$B"));
	CDvmValue *pC = (CDvmValue*)pVector->FindByID_MmsAttr(_T("$C"));

	CDvmValue *pPositive = (CDvmValue*)pVector->FindByID_MmsAttr(_T("$Positive"));
	CDvmValue *pNegative = (CDvmValue*)pVector->FindByID_MmsAttr(_T("$Negative"));
	CDvmValue *pZero = (CDvmValue*)pVector->FindByID_MmsAttr(_T("$Zero"));

	double dMag_A=0, dAng_A=0, dMag_B=0, dAng_B=0, dMag_C=0, dAng_C=0, dFreq=0;

	UpdateDvmDeviceDatas_RecordTest_SV_CH_Attr(pA, dMag_A, dAng_A, dFreq);
	UpdateDvmDeviceDatas_RecordTest_SV_CH_Attr(pB, dMag_B, dAng_B, dFreq);
	UpdateDvmDeviceDatas_RecordTest_SV_CH_Attr(pC, dMag_C, dAng_C, dFreq);

	double dMag_Positive=0, dAng_Positive=0, dMag_Negative=0, dAng_Negative=0, dMag_Zero=0, dAng_Zero=0;
#ifdef USE_Old_SequenceCal_

	dAng_A *= PI_RADIAN_PER_DEG;
	dAng_B *= PI_RADIAN_PER_DEG;
	dAng_C *= PI_RADIAN_PER_DEG;
	
	double dReal1 = dMag_A * cos(dAng_A);
	double dIm1   = dMag_A * sin(dAng_A);
	double dReal2 = dMag_B * cos(dAng_B);
	double dIm2   = dMag_B * sin(dAng_B);
	double dReal3 = dMag_C * cos(dAng_C);
	double dIm3   = dMag_C * sin(dAng_C);

	//PositiveSequence
	double dReal = dReal1 - 0.5 * (dReal2 + dReal3) - 0.8660254 * (dIm2 -dIm3);
	double dIm   = dIm1   - 0.5 * (dIm2   + dIm3  ) + 0.8660254 * (dReal2 - dReal3);
	dMag_Positive = (sqrt(dReal * dReal + dIm * dIm)) / 3;
	dAng_Positive = atan2(dReal, dIm) * PI_DEG_PER_RADIAN;

	//NegativeSequence
	dReal = dReal1 - 0.5 * (dReal2 + dReal3) + 0.8660254 * (dIm2 -dIm3);
	dIm   = dIm1   - 0.5 * (dIm2   + dIm3  ) - 0.8660254 * (dReal2 - dReal3);
	dMag_Negative = (sqrt(dReal * dReal + dIm * dIm)) / 3;
	dAng_Negative = atan2(dReal, dIm) * PI_DEG_PER_RADIAN;

	//ZeroSequence
	dReal = dReal1 + dReal2 + dReal3;
	dIm   = dIm1   + dIm2	+ dIm3;
	dMag_Zero = (sqrt(dReal * dReal + dIm * dIm)) / 3;
	dAng_Zero = atan2(dReal, dIm) * PI_DEG_PER_RADIAN;
#else
	CComplexNumber oComA(dMag_A,dAng_A,COMPLEX_MODE_DEGREE);
	CComplexNumber oComB(dMag_B,dAng_B + 120,COMPLEX_MODE_DEGREE);
	CComplexNumber oComC(dMag_C,dAng_C - 120,COMPLEX_MODE_DEGREE);
	CComplexNumber oTempCom = oComA;
	oTempCom += oComB;
	oTempCom += oComC;
	oTempCom.GetValueAngle(dMag_Positive, dAng_Positive, COMPLEX_MODE_DEGREE);
	dMag_Positive /= 3;
	oComB.SetValueAngle(dMag_B,dAng_B - 120,COMPLEX_MODE_DEGREE);
	oComC.SetValueAngle(dMag_C,dAng_C + 120,COMPLEX_MODE_DEGREE);
	oTempCom = oComA;
	oTempCom += oComB;
	oTempCom += oComC;
	oTempCom.GetValueAngle(dMag_Negative, dAng_Negative, COMPLEX_MODE_DEGREE);
	dMag_Negative /= 3;
	oComB.SetValueAngle(dMag_B,dAng_B,COMPLEX_MODE_DEGREE);
	oComC.SetValueAngle(dMag_C,dAng_C,COMPLEX_MODE_DEGREE);
	oTempCom = oComA;
	oTempCom += oComB;
	oTempCom += oComC;
	oTempCom.GetValueAngle(dMag_Zero, dAng_Zero, COMPLEX_MODE_DEGREE);
	dMag_Zero /= 3;
#endif

	UpdateDataValue(pPositive, _T("$mag"), dMag_Positive);
	UpdateDataValueAng(pPositive, _T("$ang"), dAng_Positive);
	UpdateDataValue(pNegative, _T("$mag"), dMag_Negative);
	UpdateDataValueAng(pNegative, _T("$ang"), dAng_Negative);
	UpdateDataValue(pZero, _T("$mag"), dMag_Zero);
	UpdateDataValueAng(pZero, _T("$ang"), dAng_Zero);
}

//在函数：CSmartCapCtrl::LoadIecCfgFile(const CString &strIecCfgFile)
//调用  Init_SV_Channels
void CX61850CapBase::Init_SV_Channels()
{
	if (m_pDvmDevice==NULL)
		return;

	POS posLdevice = m_pDvmDevice->GetHeadPosition();
	POS posDataset = NULL;
	CDvmLogicDevice *pLdevice = NULL;
	CDvmDataset *pDataset = NULL;
	CExBaseList listAll;

	while (posLdevice != NULL)
	{
		pLdevice = (CDvmLogicDevice *)m_pDvmDevice->GetNext(posLdevice);
		posDataset = pLdevice->GetHeadPosition();

		while (posDataset != NULL)
		{
			pDataset = (CDvmDataset *)pLdevice->GetNext(posDataset);

			if (Is_SvDataset(pDataset))
			{
				listAll.Append(pDataset);
			}
		}
	}

	CExBaseObject *pData = NULL;
	long nIndex = 0;
	DWORD *pdwVariablesAddr = m_oCapDeviceChRecordMngr.m_pRecordTest->m_pVariables->GetVariablesAddr();
	CRtVariable *pVariable = NULL;
	m_nMaxSvChannelsMap = 0;

	for (nIndex=0; nIndex<MAX_RTVARIABLES; nIndex++)
	{
		pVariable = (CRtVariable*) (*pdwVariablesAddr);

		if (*pdwVariablesAddr == 0)
		{
			break;
		}

		m_nMaxSvChannelsMap++;
		pData = listAll.FindByID(pVariable->m_strID);

		if (pData == NULL)
		{
			m_dwDvmSvChannels[nIndex] = 0;
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s 对应的模型数据对象不存在"), pVariable->m_strID.GetString());
		}
		else
		{
			m_dwDvmSvChannels[nIndex] = (DWORD)pData;

			if (pVariable->m_strName != pData->m_strName)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s ：配置文件【%s】和模型文件【%s】 名称不一致")
                    , pVariable->m_strID.GetString(), pVariable->m_strName.GetString(), pData->m_strName.GetString());
			}
		}

		pdwVariablesAddr++;
	}

	listAll.RemoveAll();
}

void CX61850CapBase::Init_GS_Channels()
{
	if (m_pDvmDevice==NULL)
		return;

	POS posLdevice = m_pDvmDevice->GetHeadPosition();
	POS posDataset = NULL;
	CDvmLogicDevice *pLdevice = NULL;
	CDvmDataset *pDataset = NULL;
	CExBaseList listDvmAll;

	while (posLdevice != NULL)
	{
		pLdevice = (CDvmLogicDevice *)m_pDvmDevice->GetNext(posLdevice);
		posDataset = pLdevice->GetHeadPosition();

		while (posDataset != NULL)
		{
			pDataset = (CDvmDataset *)pLdevice->GetNext(posDataset);

			if (Is_GsDataset(pDataset))
			{
				listDvmAll.Append(pDataset);
			}
		}
	}

	POS posDevice = m_oCapDeviceAll.GetHeadPosition();
	CCapDeviceBase *pCapDevice = NULL;
	POS posCh = NULL;
	CCapDeviceChBase *pCh = NULL;

	while (posDevice != NULL)
	{
		pCapDevice = (CCapDeviceBase *)m_oCapDeviceAll.GetNext(posDevice);

		if (pCapDevice->GetClassID() != CPDCLASSID_DEVICEGOOSE)
		{
			continue;
		}

		posCh = pCapDevice->GetHeadPosition();

		while (posCh != NULL)
		{
			pCh = (CCapDeviceChBase *)pCapDevice->GetNext(posCh);
			pCh->m_pRefDvmData = listDvmAll.FindByID(pCh->m_strID);

			if (pCh->m_pRefDvmData == NULL)
			{
                CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("GOOSE【%s】【%s】没有匹配的设备数据模型对象"), pCh->m_strID.GetString(), pCh->m_strName.GetString());
			}
		}
	}

	listDvmAll.RemoveAll();
}

// 可以添加字符串的 mym 2020-6-23
void CX61850CapBase::Analysis_Add_Value(CDvmData *pData, const CString &strID, CString strValue)
{
	CDvmValue *pValue = NULL;

	if (pData == NULL)
		return;
	pValue = (CDvmValue*)pData->FindByID(strID);

	if (pValue == NULL)
	{
		pValue = new CDvmValue();
		pData->AddNewChild(pValue);
		pValue->m_strName = strID;
		pValue->m_strID = strID;
	}

	pValue->m_strValue = strValue;
}

void CX61850CapBase::WriteRecordDataFile()
{
	CRtVariables *pVariables = m_oCapDeviceChRecordMngr.m_pRecordTest->m_pVariables;
	DWORD *pVariableAddr = pVariables->GetVariablesAddr()	;
	CRtVariable *pVariable = NULL;
	DWORD *p = pVariableAddr;
	CMemBufferInterface *pRef = NULL;

	//查找第一个有效通道
	while (*p != 0)
	{
		pVariable = (CRtVariable *)(*p);
		p++;

		if ((pVariable->CanCal()))
		{
			pRef = pVariable->GetChannelBuffer();
			break;
		}
	}

	long nCurrIndex = pRef->GetDataFillBeginPosition();
	long nDataLen = pRef->GetDataLength();
	long nBufLen = pRef->GetBufferLength();
	CString strFile;
	strFile = _P_GetBinPath();
	SYSTEMTIME tm;
	::GetLocalTime(&tm);

	strFile.AppendFormat(_T("%02d%02d%02d.txt"), tm.wHour, tm.wMinute, tm.wSecond);
	CFile oFile;

	if (! oFile.Open(strFile, CFile::modeCreate | CFile::modeWrite))
	{
		return;
	}

	if (nDataLen == nBufLen)
	{
		WriteRecordDataFile(pVariableAddr, nBufLen - nCurrIndex, nBufLen, oFile);
		WriteRecordDataFile(pVariableAddr, 0, nCurrIndex, oFile);
	}
	else
	{
		WriteRecordDataFile(pVariableAddr, 0, nCurrIndex, oFile);
	}

	oFile.Close();
}

void CX61850CapBase::WriteRecordDataFile(DWORD *pdwAddrs, long nBegin, long nEnd, CFile &oFile)
{
#ifndef _PSX_IDE_QT_
	DWORD *p = pdwAddrs;
	CMemBufferInterface *pRef = NULL;
	CRtVariable *pVariable = NULL;
	long nIndex = 0;
	long *pLong = NULL;
	CString strText;

	for (nIndex=nBegin; nIndex<nEnd; nIndex++)
	{
		p = pdwAddrs;

		while (*p != 0)
		{
			pVariable = (CRtVariable *)(*p);
			p++;

			if (!pVariable->CanCal())
			{
				continue;
			}

			pLong = pVariable->GetChannelBuffer()->GetBuffer_long();
			strText.Format(_T("%d\t"), pLong[nIndex]);
			oFile.Write(strText, strText.GetLength());
		}

		oFile.Write(_T("\r\n"), 2);
	}
#endif
}

void CX61850CapBase::UpdateDvmDeviceDatas_Analysis_SVDelayErr_Dvm(	long &nLinkCount,long &nHasCalCount)
{
	POS pos = m_oCapDeviceAll.GetHeadPosition();
	CCapDeviceBase *pCapDevice = NULL;
	long nSvIndex = 0;
	CString strSVCstcID;

	while (pos != NULL)
	{
		pCapDevice = (CCapDeviceBase*)m_oCapDeviceAll.GetNext(pos);

		if (pCapDevice->GetClassID() == CPDCLASSID_DEVICE92)
		{
			CCapDevice92 *pDevice92 = (CCapDevice92 *)pCapDevice;

			if (pDevice92->m_bLinkState)
			{
				nLinkCount++;
			}

			if (pDevice92->TimeDelayCalFinish())
			{
				nHasCalCount++;
			}

			strSVCstcID.Format(_T("SV%d"),   nSvIndex + 1);
			CDvmData * pDataSV   =    (CDvmData *)m_pDataset_SVDelay->FindByID(strSVCstcID);

			if (pDataSV != NULL)
			{
				Analysis_Add_SVDelayValue(strSVCstcID,  pDevice92);
				Analysis_Add_Data(m_pDataset_SVDelay,   strSVCstcID+_T("_Rcd_file"),  pDevice92->m_strComtradeFile);
			}

			nSvIndex++;
		}
		else if (pCapDevice->GetClassID() == CPDCLASSID_DEVICE6044)
		{
			CCapDevice6044 *pDevice6044 = (CCapDevice6044 *)pCapDevice;

			if (pDevice6044->m_bLinkState)
			{
				nLinkCount++;
			}

			if (pDevice6044->TimeDelayCalFinish())
			{
				nHasCalCount++;
			}

			strSVCstcID.Format(_T("SV%d"),   nSvIndex + 1);
			CDvmData * pDataSV   =    (CDvmData *)m_pDataset_SVDelay->FindByID(strSVCstcID);

			if (pDataSV != NULL)
			{
				Analysis_Add_SVDelayValue(strSVCstcID,  pDevice6044);
//				Analysis_Add_Data(m_pDataset_SVDelay,   strSVCstcID+_T("_Rcd_file"),  pDevice6044->m_strComtradeFile);
			}

			nSvIndex++;
		}
	}
}

void CX61850CapBase::Analysis_Add_SVHis(const CString &strSV_ID,const CString &strHisDataID,double dCurrValue,
										long nCurrTestCount)
{
	if (m_pDataset_SV_His == NULL)
	{
		return;
	}

	//暂定最大测试次数
	if (nCurrTestCount>STT_SV_MaxTestCount)
	{
		return;
	}

	CString strPath;
	strPath = strSV_ID;
	long nIndex = strSV_ID.ReverseFind('$');

	if (nIndex >=0)
	{
		strPath = strSV_ID.Mid(nIndex+1);
	}

	CDvmData *pData = (CDvmData*)m_pDataset_SV_His->FindByID(strPath);

	if (pData == NULL)
	{
		return;
	}

	strPath += strHisDataID;

	CDvmValue *pHisValueParent = (CDvmValue*)pData->FindByID(strPath);

	if (pHisValueParent == NULL)
	{
		return;
	}

	strPath.AppendFormat(_T("$TestCount%ld"),nCurrTestCount);
	CDvmValue *pHisCurValue = (CDvmValue*)pHisValueParent->FindByID(strPath);

	if (pHisCurValue == NULL)
	{
		pHisCurValue = new CDvmValue;
		pHisCurValue->m_strName = strPath;
		pHisCurValue->m_strID = strPath;
		pHisValueParent->AddNewChild(pHisCurValue);
	}

	pHisCurValue->m_strValue.Format(_T("%lf"),dCurrValue);
}

void CX61850CapBase::Analysis_Add_SVDelayValue(const CString &strID, CCapDevice92 *pDevice92)
{
	if (m_pDataset_SVDelay == NULL)
	{
		return;
	}

	if (!pDevice92->m_bLinkState)
	{
		return;
	}

	if (/*(pDevice92->m_dwTimeDelay == 0)&&*/(/*fabs*/(pDevice92->m_fZeroDelta)<0.001))//延时一定为一个正数值
	{
		return;
	}

	CDvmData *pData = Analysis_Add_Data(m_pDataset_SVDelay, strID);

	if (pData == NULL)
	{
		return;
	}

	CString strTmpID;
	strTmpID = strID + STT_MUTEST_DL_ChDelay;//.Format("%s$ChDelay",strID.GetString());
	Analysis_Add_Value(pData,strTmpID,pDevice92->m_dwTimeDelay);
	strTmpID = strID + STT_MUTEST_DL_RealDelay;//.Format("%s$RealDelay",strID.GetString());
	Analysis_Add_Value(pData,strTmpID,pDevice92->m_fZeroDelta,3);
	//添加测试次数
	strTmpID = strID + STT_RcdInit_DL_TestCount;
	CDvmValue *pTestCountValue = (CDvmValue*)pData->FindByID(strTmpID);

	if (pTestCountValue == NULL)
	{
		pTestCountValue = pData->AddValue(strTmpID,_T("0"));
	}

	double dCurrDelayError = pDevice92->m_fZeroDelta - pDevice92->m_dwTimeDelay;
	long nTestCount = CString_To_long(pTestCountValue->m_strValue);
	//添加最大延时
	strTmpID = strID + STT_MUTEST_DL_MaxDelayError;
	CDvmValue *pMaxDelayValue = dvm_FindAddByID(pData,strTmpID,dCurrDelayError);//  (CDvmValue*)pData->FindByID(strTmpID)
	double dMaxDelayError = CString_To_double(pMaxDelayValue->m_strValue);

	if (fabs(dCurrDelayError)>fabs(dMaxDelayError))
	{
		dMaxDelayError = dCurrDelayError;
		pMaxDelayValue->m_strValue.Format(_T("%.3lf"), dCurrDelayError);
	}

	//添加最小延时
	strTmpID = strID + STT_MUTEST_DL_MinDelayError;
	CDvmValue *pMinDelayErrorValue = dvm_FindAddByID(pData,strTmpID,dCurrDelayError);//(CDvmValue*)pData->FindByID(strTmpID);
	double dMinDelayError = CString_To_double(pMinDelayErrorValue->m_strValue);

	if (fabs(dCurrDelayError)<fabs(dMinDelayError))
	{
		dMinDelayError = dCurrDelayError;
		pMinDelayErrorValue->m_strValue.Format(_T("%.3lf"), dCurrDelayError);
	}

	//添加平均延时
	strTmpID = strID + STT_MUTEST_DL_AverageDelayError;
	CDvmValue *pAverageDelayErrorValue = dvm_FindAddByID(pData,strTmpID,dCurrDelayError);//(CDvmValue*)pData->FindByID(strTmpID);
	double dAverageDelayError = CString_To_double(pAverageDelayErrorValue->m_strValue);

	if (nTestCount>CAP_BEFORE_TEST_DELAY_COUNT)//舍去前4次的测试结果,不进入综合统计,防止刚施加量时,误差较大
	{
		dAverageDelayError = (dAverageDelayError*(nTestCount-CAP_BEFORE_TEST_DELAY_COUNT) + dCurrDelayError)
			/(nTestCount - CAP_BEFORE_TEST_DELAY_COUNT +1);
		Analysis_Add_SVHis(strID,STT_MUTEST_DL_RealDelay,dCurrDelayError,nTestCount - CAP_BEFORE_TEST_DELAY_COUNT);
	}

	pAverageDelayErrorValue->m_strValue.Format(_T("%.3lf"), dAverageDelayError);

// 	//添加无PPS最大延时
// 	strTmpID = strID + STT_MUTEST_DL_MaxErrorNoPPS;
// 	double dCurrValueNoPPS = dCurrDelayError-m_dDelayCompens_NoPPS;
// 	CDvmValue *pMaxValueNoPPS = dvm_FindAddByID(pData,strTmpID,dCurrValueNoPPS);//  (CDvmValue*)pData->FindByID(strTmpID)
// 	double dMaxErrorNoPPS = CString_To_double(pMaxValueNoPPS->m_strValue);
// 
// 	if (fabs(dCurrValueNoPPS)>fabs(dMaxErrorNoPPS))
// 	{
// 		pMaxValueNoPPS->m_strValue.Format(_T("%.3lf"), dCurrValueNoPPS);
// 	}
// 
// 	//添加无PPS最小延时
// 	strTmpID = strID + STT_MUTEST_DL_MinErrorNoPPS;
// 	CDvmValue *pMinErrorValueNoPPS = dvm_FindAddByID(pData,strTmpID,dCurrValueNoPPS);//(CDvmValue*)pData->FindByID(strTmpID);
// 	double dMinErrorNoPPS = CString_To_double(pMinErrorValueNoPPS->m_strValue);
// 
// 	if (fabs(dCurrValueNoPPS)<fabs(dMinErrorNoPPS))
// 	{
// 		pMinErrorValueNoPPS->m_strValue.Format(_T("%.3lf"), dCurrValueNoPPS);
// 	}
// 
// 	//添加无PPS平均延时
// 	strTmpID = strID + STT_MUTEST_DL_AverageErrorNoPPS;
// 	CDvmValue *pAverageErrorValueNoPPS = dvm_FindAddByID(pData,strTmpID,dCurrValueNoPPS);//(CDvmValue*)pData->FindByID(strTmpID);
// 	double dAverageErrorNoPPS = CString_To_double(pAverageErrorValueNoPPS->m_strValue);
// 
// 	if (nTestCount>CAP_BEFORE_TEST_DELAY_COUNT)//舍去前4次的测试结果,不进入综合统计,防止刚施加量时,误差较大
// 	{
// 		dAverageErrorNoPPS = (dAverageErrorNoPPS*(nTestCount-CAP_BEFORE_TEST_DELAY_COUNT) + dCurrValueNoPPS)/(nTestCount - CAP_BEFORE_TEST_DELAY_COUNT +1);
// 	}
// 
// 	pAverageErrorValueNoPPS->m_strValue.Format(_T("%.3lf"), dAverageErrorNoPPS);
 	strTmpID = strID + STT_RcdInit_DL_Result;

	if (nTestCount <= CAP_BEFORE_TEST_DELAY_COUNT)//前4次的结果不计入结果
	{
		pMaxDelayValue->m_strValue.Format(_T("%.03lf"),dCurrDelayError);
		pMinDelayErrorValue->m_strValue = pMaxDelayValue->m_strValue;
		pAverageDelayErrorValue->m_strValue = pMaxDelayValue->m_strValue;

// 		pMaxValueNoPPS->m_strValue.Format(_T("%.03lf"),dCurrValueNoPPS);
// 		pMinErrorValueNoPPS->m_strValue = pMaxValueNoPPS->m_strValue;
// 		pAverageErrorValueNoPPS->m_strValue = pMaxValueNoPPS->m_strValue;
	}

	nTestCount++;
	pTestCountValue->m_strValue.Format(_T("%ld"),nTestCount);

	if ((nTestCount > CAP_BEFORE_TEST_DELAY_COUNT)&&
		((fabs(dMinDelayError/*-pDevice92->m_dwTimeDelay*/)>4)||(fabs(dMaxDelayError/*-pDevice92->m_dwTimeDelay*/)>4)))
		//20230303 zhouhj 已经是减去额定延时之后的值
	{
		Analysis_Add_Value(pData,strTmpID,0);
	} 
	else
	{
		Analysis_Add_Value(pData,strTmpID,1);
	}

// 
// 	strTmpID = strID + STT_MUTEST_$DelayError;//.Format("%s$DelayError",strID.GetString());
// 	double dErrorValue = pDevice92->m_fZeroDelta - pDevice92->m_dwTimeDelay;
// 	Analysis_Add_Value(pData,strTmpID,dErrorValue,3);
// 	strTmpID = strID + STT_MUTEST_$MaxError;//.Format("%s$MaxError",strID.GetString());
// 	CDvmValue *pCurrValue = (CDvmValue*)pData->FindByID(strTmpID);
// 	double dOldValue = 0.0f;
// 
// 	if (pCurrValue != NULL)
// 	{
// 		dOldValue = CString_To_double(pCurrValue->m_strValue);
// 
// 		if ((dOldValue<dErrorValue)||(pCurrValue->m_strValue.IsEmpty()))
// 		{
// 			pCurrValue->m_strValue.Format(_T("%.03lf"),dErrorValue);
// 		}
// 	}
// 
// 	strTmpID = strID + STT_MUTEST_$MinError;//.Format("%s$MinError",strID.GetString());
// 	pCurrValue = (CDvmValue*)pData->FindByID(strTmpID);
// 
// 	if (pCurrValue != NULL)
// 	{
// 		dOldValue = CString_To_double(pCurrValue->m_strValue);
// 
// 		if ((dOldValue>dErrorValue)||(pCurrValue->m_strValue.IsEmpty()))
// 		{
// 			pCurrValue->m_strValue.Format(_T("%.03lf"),dErrorValue);
// 		}
// 	}

	strTmpID = strID + STT_MUTEST_DL_TimeLong;//.Format("%s$TimeLong",strID.GetString());
	CDvmValue *pCurrValue = (CDvmValue*)pData->FindByID(strTmpID);

	if (pCurrValue != NULL)
	{
		 double dOldValue = g_oSVDelayTickCount.GetTickCountLong(FALSE);
		 dOldValue /= 1000;
		pCurrValue->m_strValue.Format(_T("%.03lf"),dOldValue);
	}
}

void CX61850CapBase::Analysis_Add_SVDelayValue(const CString &strID, CCapDevice6044 *pDevice6044)
{
	if (m_pDataset_SVDelay == NULL)
	{
		return;
	}

	if (!pDevice6044->m_bLinkState)
	{
		return;
	}

	CDvmData *pData = Analysis_Add_Data(m_pDataset_SVDelay, strID);

	if (pData == NULL)
	{
		return;
	}

	CString strTmpID;
	strTmpID = strID + STT_MUTEST_DL_ChDelay;//.Format("%s$ChDelay",strID.GetString());
	Analysis_Add_Value(pData,strTmpID,pDevice6044->m_dwTimeDelay);
}

void CX61850CapBase::UpdateDvmDeviceDatas_Analysis_SVDelayErr_Rcd(long nRcdChCount)
{
	CSttRcdComtradeFileWrite oSttRcdWrite;
	oSttRcdWrite.InitComtradeFileWrite(nRcdChCount, STT_CAP_SMV_SYN_RCD_MAX_COUNT);

	POS pos = m_oCapDeviceAll.GetHeadPosition();
	CCapDeviceBase *pCapDevice = NULL;
	long nSvIndex = 0;
	CString strSVCstcID;

	while (pos != NULL)
	{
		pCapDevice = (CCapDeviceBase*)m_oCapDeviceAll.GetNext(pos);

		if (pCapDevice->GetClassID() != CPDCLASSID_DEVICE92)
		{
			continue;
		}

		CCapDevice92 *pDevice92 = (CCapDevice92 *)pCapDevice;

		if ((!pDevice92->m_bLinkState) ||  (!pDevice92->TimeDelayCalFinish()))
		{
			continue;
		}

		oSttRcdWrite.SetChannelData(nSvIndex, pDevice92->m_dSttCapRcdData, pDevice92->m_strSvSynChID, pDevice92->m_dSvSynChCoef);

		nSvIndex++;
	}

	CDvmData * pDataSV   =    (CDvmData *)m_pDataset_SVDelay->FindByID(strSVCstcID);

	SYSTEMTIME tmSys;
	::GetLocalTime(&tmSys);
	CString strComtradeFile;

	if (g_oCapAnalysisConfig.m_bSmvSyncDelt)
	{
		strComtradeFile.Format(_T("SVDelayTime_%02d%02d.dat"), tmSys.wMinute, tmSys.wSecond);
	}
	else
	{
		strComtradeFile.Format(_T("SVSyn_%02d%02d.dat"), tmSys.wMinute, tmSys.wSecond);
	}

	oSttRcdWrite.WritComtradeFile(strComtradeFile);
	Analysis_Add_Data(m_pDataset_SVDelay,   _T("SV_Rcd_file"),  strComtradeFile);
}

long g_max_UpdateSVDelayData_count  = 2;

// SV延时显示；mym 2020-6-26 add
void CX61850CapBase::UpdateDvmDeviceDatas_Analysis_SVDelayErr()
{
	if (! g_oCapAnalysisConfig.m_bAnalysisData_DelayTime)
	{//不需要分析通道延时
		return;
	}

	if (m_nHasUpdateSVDelayData >= g_max_UpdateSVDelayData_count)
	{//已经全部分析完毕
		return;
	}

	long nLinkCount = 0;
	long nHasCalCount = 0;

	UpdateDvmDeviceDatas_Analysis_SVDelayErr_Dvm(nLinkCount, nHasCalCount);

	if (nHasCalCount == 0)
	{
		return;
	}

	UpdateDvmDeviceDatas_Analysis_SVDelayErr_Rcd(nHasCalCount);

	//最多3秒中，多输出几次波形
	if (nLinkCount == nHasCalCount)
	{
		m_nHasUpdateSVDelayData = g_max_UpdateSVDelayData_count + 1;
	}
	else
	{
		m_nHasUpdateSVDelayData++;
	}
}

void CX61850CapBase::UpdateDvmDeviceDatas_SOE()
{
	long nBegin1, nEnd1, nBegin2, nEnd2;
	g_pSmartCapSoeCycleArray->GetReadIndexRange(nBegin1, nEnd1, nBegin2,  nEnd2);

	if (nEnd1 < 0)
	{
		return;
	}

	UpdateDvmDeviceDatas_SOE(nBegin1, nEnd1);

	if (nEnd2 >= 0)
	{
		UpdateDvmDeviceDatas_SOE(nBegin2, nEnd2);
	}
}

void CX61850CapBase::UpdateDvmDeviceDatas_SOE(long nBegin, long nEnd)
{
	long nIndex = 0;
	CExBaseObject *pData = NULL;
	CExBaseObject *pNew = NULL;

	for (nIndex=nBegin; nIndex<=nEnd; nIndex++)
	{
		pData = g_pSmartCapSoeCycleArray->GetExBaseObject(nIndex);
		pNew = (CExBaseObject *)pData->Clone();
		m_pDataset_Report->AddNewChild(pNew);
	}

	g_pSmartCapSoeCycleArray->SetCurrReadIndex(nIndex);
}

void CX61850CapBase::UpdateDvmDeviceDatas_BIN()
{
	long nBegin1, nEnd1, nBegin2, nEnd2;
	g_pSmartCapBinCycleArray->GetReadIndexRange(nBegin1, nEnd1, nBegin2,  nEnd2);

	if (nEnd1 < 0)
	{
		return;
	}

	UpdateDvmDeviceDatas_BIN(nBegin1, nEnd1);

	if (nEnd2 >= 0)
	{
		UpdateDvmDeviceDatas_BIN(nBegin2, nEnd2);
	}
}

void CX61850CapBase::UpdateDvmDeviceDatas_BIN(long nBegin, long nEnd)
{
	long nIndex = 0;
	CExBaseObject *pData = NULL;
	CExBaseObject *pNew = NULL;

	for (nIndex=nBegin; nIndex<=nEnd; nIndex++)
	{
		pData = g_pSmartCapBinCycleArray->GetExBaseObject(nIndex);
		pNew = (CExBaseObject *)pData->Clone();
		m_pDataset_Report->AddNewChild(pNew);
	}

	g_pSmartCapBinCycleArray->SetCurrReadIndex(nIndex);
}

// SV同步差 2020-6-29 mayangming add 
void CX61850CapBase::UpdateDvmDeviceDatas_Analysis_SVSync()
{
	if (! g_oCapAnalysisConfig.m_bSmvSyncDelt)
	{
		return;
	}

	//如果不是同步性测试，是不需要进行同步性测试计算的
	CExBaseList listDvice;
	m_oCapDeviceAll.SelectDevicesByLink(listDvice, CPDCLASSID_DEVICE92, TRUE);

	if (listDvice.GetCount() <= 1)
	{
		listDvice.RemoveAll();
		return;
	}

	POS pos = listDvice .GetHeadPosition();//m_oCapDeviceAll.GetHeadPosition();
	CCapDevice92 *pCapDevice = NULL;
	BOOL bCanCal = TRUE;
	double dTimeDelay[30] = {0};
	CString strTimeDelay[30];
	long nSvIndex = 0, nSvCount = 0;
	CString strSVCstcID;
	CDvmData * pDataGS = NULL;

	while (pos != NULL)
	{
		pCapDevice = (CCapDevice92*)listDvice.GetNext(pos);

		if (pCapDevice->TimeDelayCalFinish())
		{
			dTimeDelay[nSvCount] = pCapDevice->m_dTimeDelay;
			strTimeDelay[nSvCount] = pCapDevice->m_strTimeDelay;
			nSvCount++;
		}
		else
		{
			bCanCal = FALSE;
			break;
		}
	}




	if (!bCanCal)
	{
		listDvice.RemoveAll();
		return;
	}
	//nSvCount = 3;


	for (nSvIndex = 1;  nSvIndex < nSvCount;  nSvIndex++)
	{
		strSVCstcID.Format(_T("SV%d_SV1"), nSvIndex+1);
		pDataGS    =    (CDvmData *)m_pDataset_SVSyncDelt->FindByID(strSVCstcID);

		if (pDataGS == NULL)
		{
			pDataGS = new CDvmData();
			pDataGS->m_strName = strSVCstcID;
			pDataGS->m_strID = strSVCstcID;
			m_pDataset_SVSyncDelt->AddNewChild(pDataGS);
		}

		//mym modify 2020-7-14
		//pDataGS->m_strValue.Format(_T("%f"),  dTimeDelay[nSvIndex]  -  dTimeDelay[nSvIndex - 1]);
		pDataGS->m_strValue.Format(_T("%f"), dTimeDelay[nSvIndex ]  -  dTimeDelay[0]);
	}

	// mym 2020-12-08为了算出SV同步，把单个的SV延时算出来；
	/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
	for (nSvIndex = 0;  nSvIndex < nSvCount;  nSvIndex++)
	{
		strSVCstcID.Format(_T("SV%d"),  nSvIndex + 1);
		pDataGS    =    (CDvmData *)m_pDataset_SVSyncDelt->FindByID(strSVCstcID);

		if (pDataGS == NULL)
		{
			pDataGS = new CDvmData();
			pDataGS->m_strName = strSVCstcID;
			pDataGS->m_strID = strSVCstcID;
			m_pDataset_SVSyncDelt->AddNewChild(pDataGS);
		}

		pDataGS->m_strValue  =  strTimeDelay[nSvIndex ];
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	listDvice.RemoveAll();
}

void SetErrorStatisValues_ADMU(CDvmValue *pDvmValue,float fActualValue,double fCurrValue,long nErrorType,long nAccurLevel,const CString &strChDataType)
{
	if (pDvmValue == NULL)
	{
		return;
	}

	CString strTmpID;
	pDvmValue->m_strValue.Format(_T("%.6lf"), fCurrValue);
	double dMaxValue = fCurrValue;

	//添加测试次数
	strTmpID = pDvmValue->m_strID + STT_RcdInit_DL_TestCount;
	CDvmValue *pTestCountValue = dvm_FindAddByID(pDvmValue,strTmpID,_T("0"));
	long nTestCount = CString_To_long(pTestCountValue->m_strValue);

	//添加最大值
	strTmpID = pDvmValue->m_strID + STT_RcdInit_DL_MaxValue;
	CDvmValue *pMaxValue = dvm_FindAddByID(pDvmValue,strTmpID,pDvmValue->m_strValue);
	dMaxValue = CString_To_double(pMaxValue->m_strValue);

	if(pDvmValue->m_strID.Find(STT_RcdInit_DL_RatError) >= 0)
	{ 
		strTmpID = pDvmValue->m_strID + STT_RcdInit_DL_MaxMagValue;
	}
	else if (pDvmValue->m_strID.Find(STT_RcdInit_DL_AngError) >= 0)
	{
		strTmpID = pDvmValue->m_strID + STT_RcdInit_DL_MaxAngValue;
	}
	else if (pDvmValue->m_strID.Find(STT_RcdInit_DL_CompError) >= 0)
	{
		strTmpID = pDvmValue->m_strID + STT_RcdInit_DL_MaxAngValue;
	}

	//添加最大实测值
	CDvmValue *pMaxActualValue = dvm_FindAddByID(pDvmValue,strTmpID,pDvmValue->m_strValue);
	double dMaxActualValue = CString_To_double(pMaxActualValue->m_strValue);

	if (nTestCount > CAP_BEFORE_TEST_CALC_COUNT )
	{
		if (fabs(fCurrValue) >= fabs(dMaxValue))
		{
			dMaxValue = fCurrValue;
			pMaxValue->m_strValue.Format(_T("%lf"),fCurrValue);//误差值


		if (nErrorType == MUAccuracy_ErrorType_AngError || nErrorType == MUAccuracy_ErrorType_RatError)
			{
                                if (nErrorType == MUAccuracy_ErrorType_AngError)
				{
					double dTemp = fCurrValue/60;
					MakeAngleTo180(dTemp);
                                        dMaxActualValue = fActualValue - dTemp;
					MakeAngleTo360(dMaxActualValue);
				}
				if (nErrorType == MUAccuracy_ErrorType_RatError)
				{
					dMaxActualValue = (fCurrValue/100+1)*fActualValue;


					//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("%d, %f,%f,%f"),nTestCount,dMaxActualValue,fActualValue,fCurrValue);

				}
				pMaxActualValue->m_strValue.Format(_T("%lf"),dMaxActualValue);
			}
		}
	}

	if (nErrorType == MUAccuracy_ErrorType_CompError )
	{
		if (nTestCount > CAP_BEFORE_TEST_CALC_COUNT)
		{
			if (fabs(fActualValue) >= fabs(dMaxActualValue))
			{
				dMaxActualValue = fActualValue;
				pMaxActualValue->m_strValue.Format(_T("%lf"),fActualValue);
			}
		}
	}
	
	nTestCount++;
	pTestCountValue->m_strValue.Format(_T("%ld"),nTestCount);
	double dMaxErrorValue = dMaxValue;

	//添加测试结果
	strTmpID = pDvmValue->m_strID + STT_RcdInit_DL_Result;
	CDvmValue *pResultValue = dvm_FindAddByID(pDvmValue,strTmpID,_T("1"));
	strTmpID = pDvmValue->m_strID + STT_RcdInit_DL_StdErrorValue;
	CDvmValue *pStdErrorValue = dvm_FindAddByID(pDvmValue,strTmpID,_T("100"));
	strTmpID = pDvmValue->m_strID + STT_RcdInit_DL_RltDesc;
	CDvmValue *pRltDescValue = dvm_FindAddByID(pDvmValue,strTmpID,_T("合格"));

	double dStdErrorValue = 0;

	if ((strChDataType == "Curr")||(strChDataType == "电流"))
	{
		dStdErrorValue = cap_ADMUccuracy_GetCurrChStdErrorValue(nAccurLevel,nErrorType);
	}
	else if ((strChDataType == "Vol")||(strChDataType == "电压"))
	{
		dStdErrorValue = cap_ADMUccuracy_GetVolChStdErrorValue(nAccurLevel,nErrorType);
	}

	pStdErrorValue->m_strValue.Format(_T("%.02lf"),dStdErrorValue);

	if (dStdErrorValue<-0.5f)//当标准值小于0时,对测试结果不做判断
	{
		pResultValue->m_strValue = _T("2");
		pRltDescValue->m_strValue = _T("---");
	}
	else if (fabs(dMaxErrorValue) > fabs(dStdErrorValue))
	{
		pResultValue->m_strValue = _T("0");
		pRltDescValue->m_strValue = _T("不合格");
	}
	else if (fabs(dMaxErrorValue) <= fabs(dStdErrorValue))
	{
		pResultValue->m_strValue = _T("1");
		pRltDescValue->m_strValue = _T("合格");
	}

	//误差限值
	double dErrorLimitValue = dStdErrorValue;
	strTmpID = pDvmValue->m_strID + STT_RcdInit_DL_ErrorLimit;
	CDvmValue *pErrorLimitValue = dvm_FindAddByID(pDvmValue,strTmpID,pDvmValue->m_strValue);
	if (dErrorLimitValue == -1)
	{
		pErrorLimitValue->m_strValue = _T("---");
	}
	else
	{
		pErrorLimitValue->m_strValue.Format(_T("%lf"),dErrorLimitValue);
	}
}

void SetErrorStatisValues_MU(CDvmValue *pDvmValue,double fCurrValue,long nErrorType,long nAccurLevel,const CString &strChDataType)
{
	if (pDvmValue == NULL)
	{
		return;
	}

// 	if (((fCurrValue>7198)||(fCurrValue<-7198))&&(nErrorType == MUAccuracy_ErrorType_AngError))
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("当前数据(%s),当前值(%lf),误差类型(%d),准确级(%d),通道类型(%s)."),pDvmValue->m_strID.GetString(),fCurrValue,
// 			nErrorType,nAccurLevel,strChDataType.GetString());
// 	}

	pDvmValue->m_strValue.Format(_T("%.6lf"), fCurrValue);
	CString strTmpID;
	double dMaxValue = fCurrValue,dMinValue = fCurrValue,dAverageValue = fCurrValue;

	//添加测试次数
	strTmpID = pDvmValue->m_strID + STT_RcdInit_DL_TestCount;
	CDvmValue *pTestCountValue = dvm_FindAddByID(pDvmValue,strTmpID,_T("0"));// (CDvmValue*)pDvmValue->FindByID(strTmpID);
	long nTestCount = CString_To_long(pTestCountValue->m_strValue);

	//添加最大值
	strTmpID = pDvmValue->m_strID + STT_RcdInit_DL_MaxValue;
	CDvmValue *pMaxValue = dvm_FindAddByID(pDvmValue,strTmpID,pDvmValue->m_strValue);//(CDvmValue*)pDvmValue->FindByID(strTmpID);
	dMaxValue = CString_To_double(pMaxValue->m_strValue);

	if (fCurrValue>dMaxValue)
	{
		dMaxValue = fCurrValue;
		pMaxValue->m_strValue.Format(_T("%lf"),fCurrValue);
	}

	//添加最小值
	strTmpID = pDvmValue->m_strID + STT_RcdInit_DL_MinValue;
	CDvmValue *pMinValue = dvm_FindAddByID(pDvmValue,strTmpID,pDvmValue->m_strValue);//(CDvmValue*)pDvmValue->FindByID(strTmpID);
	dMinValue = CString_To_double(pMinValue->m_strValue);

	if (fCurrValue<dMinValue)
	{
		dMinValue = fCurrValue;
		pMinValue->m_strValue.Format(_T("%lf"),fCurrValue);
	}

	//添加平均值
	strTmpID = pDvmValue->m_strID + STT_RcdInit_DL_AverageValue;
	CDvmValue *pAverageValue = dvm_FindAddByID(pDvmValue,strTmpID,pDvmValue->m_strValue);//(CDvmValue*)pDvmValue->FindByID(strTmpID);
	dAverageValue = CString_To_double(pAverageValue->m_strValue);

	if (nTestCount>CAP_BEFORE_TEST_CALC_COUNT)//舍去前4次的测试结果,不进入综合统计,防止刚施加量时,误差较大
	{
		//目前未记录每次的历史数据,超出最大次数后,采用前几次的平均值和最后一次的值,再取平均的方式
		if (g_nUseCustomMUTestRpt && ((nTestCount-CAP_BEFORE_TEST_CALC_COUNT)>g_nMURptTestCount))
		{
			dAverageValue = (dAverageValue*(g_nMURptTestCount-1) + fCurrValue)/(g_nMURptTestCount);
			pAverageValue->m_strValue.Format(_T("%lf"),dAverageValue);
		}
		else
		{
			dAverageValue = (dAverageValue*(nTestCount-CAP_BEFORE_TEST_CALC_COUNT) + fCurrValue)/(nTestCount-CAP_BEFORE_TEST_CALC_COUNT+1);
			pAverageValue->m_strValue.Format(_T("%lf"),dAverageValue);
		}
	}

	if (nTestCount <= CAP_BEFORE_TEST_CALC_COUNT)//前4次的结果不计入结果
	{
		pMaxValue->m_strValue.Format(_T("%lf"),fCurrValue);
		pMinValue->m_strValue = pMaxValue->m_strValue;
		pAverageValue->m_strValue = pMaxValue->m_strValue;
	}

	nTestCount++;
	pTestCountValue->m_strValue.Format(_T("%ld"),nTestCount);
	double dMaxErrorValue = dMaxValue;

	if (fabs(dMinValue)>fabs(dMaxValue))
	{
		dMaxErrorValue = fabs(dMinValue);
	}

	//添加测试结果
	strTmpID = pDvmValue->m_strID + STT_RcdInit_DL_Result;
	CDvmValue *pResultValue = dvm_FindAddByID(pDvmValue,strTmpID,_T("1"));//(CDvmValue*)pDvmValue->FindByID(strTmpID);
	strTmpID = pDvmValue->m_strID + STT_RcdInit_DL_StdErrorValue;
	CDvmValue *pStdErrorValue = dvm_FindAddByID(pDvmValue,strTmpID,_T("100"));
	strTmpID = pDvmValue->m_strID + STT_RcdInit_DL_RltDesc;
	CDvmValue *pRltDescValue = dvm_FindAddByID(pDvmValue,strTmpID,_T("合格"));

	if ((nErrorType == MUAccuracy_ErrorType_RatError) || (nErrorType == MUAccuracy_ErrorType_CompError))
	{
		dMaxErrorValue /= 100;
	}

	double dStdErrorValue = 100.0;

	if ((strChDataType == "Curr")||(strChDataType == "电流"))
	{
		dStdErrorValue = cap_MUAccuracy_GetCurrChStdErrorValue(nAccurLevel,nErrorType);
	}
	else if ((strChDataType == "Vol")||(strChDataType == "电压"))
	{	
		dStdErrorValue = cap_MUAccuracy_GetVolChStdErrorValue(nAccurLevel,nErrorType);
	}

	pStdErrorValue->m_strValue.Format(_T("%.02lf"),dStdErrorValue);

	if (dStdErrorValue<-0.5f)//当标准值小于0时,对测试结果不做判断
	{
		pResultValue->m_strValue = _T("2");
		pRltDescValue->m_strValue = _T("---");
	}
	else if (dMaxErrorValue > dStdErrorValue)
	{
		pResultValue->m_strValue = _T("0");
		pRltDescValue->m_strValue = _T("不合格");
	}
	else
	{
		pResultValue->m_strValue = _T("1");
		pRltDescValue->m_strValue = _T("合格");
	}
}

void CX61850CapBase::UpdateDvmDeviceDatas_Analysis_HarmBase(CDvmValue *pDvmValue,double fActualValue,double fOutputValue,double fErrorValue)
{
	if (pDvmValue == NULL)
	{
		return;
	}


	CString strTmpID;
	//添加测试次数
	strTmpID = pDvmValue->m_strID + _T("$TestCount");
	CDvmValue *pTestCountValue = dvm_FindAddByID(pDvmValue,strTmpID,_T("0"));
	long nTestCount = CString_To_long(pTestCountValue->m_strValue);

	
	//基波实测值
	strTmpID = pDvmValue->m_strID + _T("$ActualValue");
	CDvmValue *pMaxActualValue = dvm_FindAddByID(pDvmValue,strTmpID,pDvmValue->m_strValue);
	double dMaxActualValue = CString_To_double(pMaxActualValue->m_strValue);


	strTmpID = pDvmValue->m_strID + _T("$ErrorValue");
	CDvmValue *pErrorValue = dvm_FindAddByID(pDvmValue,strTmpID,pDvmValue->m_strValue);
	double dErrorValue = CString_To_double(pErrorValue->m_strValue);

	if (nTestCount>CAP_BEFORE_TEST_CALC_COUNT)
	{
		if (fabs(fActualValue) >= fabs(dMaxActualValue))
		{
			dMaxActualValue = fActualValue;
			pMaxActualValue->m_strValue.Format(_T("%.3f"),fActualValue);

			if (fOutputValue !=0)
			{
			dErrorValue = fabs(1 - fActualValue/fOutputValue) * 100; 
			pErrorValue->m_strValue.Format(_T("%.3f"),dErrorValue);
		}
			else
			{
				dErrorValue = 0; 
				pErrorValue->m_strValue = _T("0");
			}
// 			if (fActualValue > 100)
// 			{
// 				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("%f"),fActualValue);
// 			}

		}
	}
	
	
	//输出值
	strTmpID = pDvmValue->m_strID + _T("$OutPutValue");
	CDvmValue *pOutPutValue = dvm_FindAddByID(pDvmValue,strTmpID,pDvmValue->m_strValue);
	pOutPutValue->m_strValue.Format(_T("%.3f"),fOutputValue);
	strTmpID = pDvmValue->m_strID + _T("$ErrorValue");


	nTestCount++;
	pTestCountValue->m_strValue.Format(_T("%ld"),nTestCount);

	strTmpID = pDvmValue->m_strID + _T("$RltDesc");
	CDvmValue *pRltDescValue = dvm_FindAddByID(pDvmValue,strTmpID,_T("合格"));

	//误差限值
	strTmpID = pDvmValue->m_strID + _T("$ErrorLimit");
	CDvmValue *pErrorLimitValue = dvm_FindAddByID(pDvmValue,strTmpID,pDvmValue->m_strValue);
	float fLimitValue = 0.05/*= CString_To_double(pErrorLimitValue->m_strValue)*/;
	QMap<CString, float>::iterator i;
	for (i = m_pHarmBaseLimitVlaueData.begin(); i != m_pHarmBaseLimitVlaueData.end(); ++i)
	{
		if(strTmpID == i.key())
		{
			fLimitValue = i.value();
			pErrorLimitValue->m_strValue.Format(_T("%.3f"),fLimitValue);
		}
	}
	
	if (fabs(dErrorValue) > fabs(fLimitValue))
	{
		pRltDescValue->m_strValue = _T("不合格");
	}
	else
	{
		pRltDescValue->m_strValue = _T("合格");
	}
}

void CX61850CapBase::InitHarmBaseErrorLimit(BOOL bInit)
{
	if (!bInit)
	{
		return;
	}
	if (m_pDataset_MUTestCB == NULL)
	{
		return;
	}
	CDvmData *pDstData = NULL;
	CDvmValue *pDvmValue = NULL,*pChildValue = NULL;
	POS pos = m_pDataset_MUTestCB->GetHeadPosition();

	float fLimitVlaue = 0;
	while (pos != NULL)
	{
		pDstData  =  (CDvmData *)m_pDataset_MUTestCB->GetNext(pos);
		POS posIn = pDstData->GetHeadPosition();
		while(posIn != NULL)
		{
			pDvmValue  =  (CDvmValue *)pDstData->GetNext(posIn);
			if (pDvmValue->m_strID.Find("$Base") > 0)
			{
				POS pos_child_value = pDvmValue->GetHeadPosition();
				while(pos_child_value)
				{
					pChildValue = (CDvmValue *)pDvmValue->GetNext(pos_child_value);
					if (pChildValue->m_strID.Find(_T("$ErrorLimit"))>0)
					{
						if (((pDstData->m_strDataType == _T("Curr")) || (pDstData->m_strDataType == _T("电流"))) && (pDstData->m_strID.Find(_T("Ia2"))) == -1)
						{
							fLimitVlaue = 1;
						}
						else if (((pDstData->m_strDataType == _T("Curr")) || (pDstData->m_strDataType == _T("电流"))) && (pDstData->m_strID.Find(_T("Ia2"))) != -1)
						{
							fLimitVlaue = 2;
						}
						else if (((pDstData->m_strDataType == _T("Vol")) || (pDstData->m_strDataType == _T("电压")))&& (pDstData->m_strID.Find(_T("Ua2"))) == -1)
						{
							fLimitVlaue = 1;
						}
						else if (((pDstData->m_strDataType == _T("Vol")) || (pDstData->m_strDataType == _T("电压")))&& (pDstData->m_strID.Find(_T("Ua2"))) != -1)
						{
							fLimitVlaue = 2;
						}
						
						m_pHarmBaseLimitVlaueData[pChildValue->m_strID] = fLimitVlaue;
					}
				}
			}
		}
	}
}

void CX61850CapBase::UpdateDvmDeviceDatas_Analysis_MagPhaseFreq()
{
	if (m_pDataset_MUTestCB == NULL)
	{
		return;
	}
// 
// 	CCapDevice92 *pCapDevice = (CCapDevice92*)m_oCapDeviceAll.FindByID(m_strDatasetMapID_MUTestCB/*CAP_DATASET_MAP_ID_dsSV1*/);
// 
// 	if (pCapDevice == NULL)
// 	{
// 		return;
// 	}
// 
// 	if (!pCapDevice->ComplexCalFinish())
// 	{
// 		return;
// 	}

	BOOL bRet = TRUE;
	POS pos = NULL;
	CString strSrcID;
	CString strID;
	CString strValue, strFreq, strUnit;
	int nIndex = 0;

	pos = m_pDataset_MUTestCB->GetHeadPosition();
	CDvmData *pDstData = NULL;
	CDvmValue *pDvmValue = NULL;
	float fCompError[200] = {0};//存储一个周波80个点的瞬时值；

	//获取频率，获取一次就可以了，记住，后面使用；
	strFreq = Get6u6iValue("Fre", 3);

	while (pos != NULL)
	{
		pDstData  =  (CDvmData *)m_pDataset_MUTestCB->GetNext(pos);

		int nIndex = pDstData->m_strID.ReverseFind('_');
		int nLength = pDstData->m_strID.GetLength();
		if (nIndex  > 0)
			strID =  pDstData->m_strID.Right(nLength - nIndex -1);
		else 
			strID =  pDstData->m_strID.Right(3);

		strUnit = pDstData->m_strUnit;

		//这个value就是我下载下去的诸如 57.74V,1,2A 幅值；
		strValue = Get6u6iValue(strID, 3);

		float fMag = 0, fFreq = 0, fPhase = 0, fTemp = 0;
		double fOutputValue = 0.0f ,fErrorValue = 0.0f,fBaseValue = 0.0f;

		//获取最下一级的VALUE；
		POS posIn = pDstData->GetHeadPosition();
		while(posIn != NULL)
		{
			pDvmValue  =  (CDvmValue *)pDstData->GetNext(posIn);

			//先记住 频率 幅值 相位 ,获取后后面再相减；
			if(pDvmValue->m_strID.Find("$mag") > 0)//幅值
			{
				if (g_oCapAnalysisConfig.m_nShowPrimaryValue)//界面显示一次值时,此处需要转换
				{
					if (strUnit=="V")
					{
						fMag = CString_To_double(pDvmValue->m_strValue)/g_oCapAnalysisConfig.m_fPT_Rate[0]/*PT*/;//(110 * 1000/100);//除以变比  
					}
					if (strUnit=="A")
					{
						fMag = CString_To_double(pDvmValue->m_strValue)/g_oCapAnalysisConfig.m_fCT_Rate[0]/*CT*/;//(1000/1.0);//除以变比
					}
				}
				else//界面显示幅值已为2次值 此处不需要再转换 zhouhj 20220813
				{
					fMag = CString_To_double(pDvmValue->m_strValue);
				}	
				//pDvmValue->m_strValue.Format(_T("%.6f"), fMag);
			}
			else if(pDvmValue->m_strID.Find("$freq") > 0)//频率
			{
				fFreq = CString_To_double(pDvmValue->m_strValue);
			}
			else if(pDvmValue->m_strID.Find("$ang") > 0)//相位
			{				
				fPhase = CString_To_double(pDvmValue->m_strValue);
			}
			//else if (pDvmValue->m_strID.Find("$Base") > 0) //基波
			//{
			//	fBaseValue = CString_To_double(pDvmValue->m_strValue);
			//	CDvmData *pBaseDvmData = NULL;
			//	if (((pDstData->m_strDataType == _T("Curr")) || (pDstData->m_strDataType == _T("电流"))) && (pDstData->m_strID.Find(_T("Ia2"))) == -1)
			//	{
			//		pBaseDvmData = (CDvmData*)m_pDataset_RcdStep6U6I->FindByID(_T("INom"));
			//	}
			//	else if (((pDstData->m_strDataType == _T("Curr")) || (pDstData->m_strDataType == _T("电流"))) && (pDstData->m_strID.Find(_T("Ia2"))) != -1)
			//	{
			//		pBaseDvmData = (CDvmData*)m_pDataset_RcdStep6U6I->FindByID(_T("I0"));
			//	}
			//	else if (((pDstData->m_strDataType == _T("Vol")) || (pDstData->m_strDataType == _T("电压")))&& (pDstData->m_strID.Find(_T("Ua2"))) == -1)
			//	{
			//		pBaseDvmData = (CDvmData*)m_pDataset_RcdStep6U6I->FindByID(_T("VNom"));
			//	}
			//	else if (((pDstData->m_strDataType == _T("Vol")) || (pDstData->m_strDataType == _T("电压")))&& (pDstData->m_strID.Find(_T("Ua2"))) != -1)
			//	{
			//		pBaseDvmData = (CDvmData*)m_pDataset_RcdStep6U6I->FindByID(_T("U0"));
			//	}
			//	if (pBaseDvmData)
			//	{
			//		fOutputValue = CString_To_double(pBaseDvmData->m_strValue);
			//		fErrorValue = (fabs(1 - fBaseValue/fOutputValue) * 100); 
			//	}	

			//	UpdateDvmDeviceDatas_Analysis_HarmBase(pDvmValue,fBaseValue,fOutputValue,fErrorValue);
			//}
			else if(pDvmValue->m_strID.Find(STT_RcdInit_DL_RatError) > 0)//比差
			{
				double fValue = 0.0f;

				if (m_bIsZeroDriftTest)
				{
					if (strUnit=="V")
					{
						fValue = 20*log10((double)(m_dZeroDrift_Un/fMag));
					}
					else
					{
						fValue = 20*log10((double)(m_dZeroDrift_In/fMag));
					}
				} 
				else
				{
					if (m_bIsFT3ADMU)
					{
						float fOutVlaue = CString_To_double(strValue);
						fValue = (fMag-fOutVlaue)/fOutVlaue * 100;
					}
					else
					{
					fValue = (fabs(1  -   fMag/CString_To_double(strValue))  *  100);                       //fMag -  atof(strValue) ;
				}
				}
				if (m_bIsFT3ADMU)
				{
					SetErrorStatisValues_ADMU(pDvmValue,CString_To_double(strValue),fValue,MUAccuracy_ErrorType_RatError ,pDstData->m_nIndex,pDstData->m_strDataType);
				}
				else
				{
				SetErrorStatisValues_MU(pDvmValue,fValue,MUAccuracy_ErrorType_RatError ,pDstData->m_nIndex,pDstData->m_strDataType);		
			}
			}
			else if(pDvmValue->m_strID.Find(STT_RcdInit_DL_AngError/*"$AngError"*/) > 0)//角差
			{
// 				strID += _T("Ph");  //20220818 zhouhj 在角差及复合误差根据同步法  已在整秒时计算
// 				strValue = Get6u6iValue(strID, 5);
// 
// 				int nHardWareDelay = 0;
// 				//fPhase = fPhase  + nHardWareDelay  *  360.0  *  fFreq/1000000.0  + 90;
// 				float fValue = fabs(fPhase  -  CString_To_double(strValue)) ;	//减去标准值；
// 				pDvmValue->m_strValue .Format(_T("%.6f"),  fValue);
			}
			else if(pDvmValue->m_strID.Find("$FreqError") > 0)//频差
			{
				double fValue = fFreq  -  CString_To_double(strFreq);	
				SetErrorStatisValues_MU(pDvmValue,fValue,MUAccuracy_ErrorType_FreqError ,pDstData->m_nIndex,pDstData->m_strDataType);
				//pDvmValue->m_strValue.Format(_T("%.6f"),  fValue);
			}
			else if(pDvmValue->m_strID.Find(STT_RcdInit_DL_CompError/*"$CompError"*/) > 0)//复合误差
			{

			}
		}
	}

//	int adf  = 0;
}

BOOL CX61850CapBase::GetMUTimeDataRelAngle(__int64 nFirstRcdPointTime,__int64 nCurrAnalogZeroTime,long nNsCompTime,int nCurrTimeDataCh
										   ,double dFreq,double &dMUTimeDataRelAngle,double &dFirstPointCalAngle)
{
	long nChIndex = nCurrTimeDataCh&0xFF;

	if (nChIndex<= 0)//关联软件资源通道号为1-48
	{
		return FALSE;
	}

	if (nChIndex > 6)//目前只支持前6个通道
	{
		return FALSE;
	}

	if ((nCurrTimeDataCh&0x100)>0)//满足条件为电流通道
	{
		dMUTimeDataRelAngle = m_I_B[nChIndex - 1].fFinitPh;
	} 
	else//否则为电压通道
	{
		dMUTimeDataRelAngle = m_U_B[nChIndex - 1].fFinitPh;
	}

	long uTimeGap = -nNsCompTime;

	if (nFirstRcdPointTime<nCurrAnalogZeroTime)
	{
		uTimeGap -= GetTimeGap_EpcapBufferItem(nCurrAnalogZeroTime,nFirstRcdPointTime,FALSE) ;
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("第一个点时间小于模拟量通道过零点时间."));
	}
	else
	{
		uTimeGap += GetTimeGap_EpcapBufferItem(nFirstRcdPointTime,nCurrAnalogZeroTime,FALSE);
	}
	
	double dSGapValue = uTimeGap/1000000000.0f;

// 	if (nFirstRcdPointTime<nCurrAnalogZeroTime)
// 	{
// 		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("第一个点时间小于模拟量通道过零点时间."));
// 	}
	dFirstPointCalAngle = dSGapValue*dFreq*360.0f;// 间隔时间*360/每周波时间 == 间隔角度差(默认过零点角度为0)
// 	CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("uTimeGap=%ld,dSGapValue=%lf,dFirstPointCalAngle=%lf"),
// 		uTimeGap,dSGapValue,dFirstPointCalAngle);
	MakeAngleTo360(dFirstPointCalAngle);
	return TRUE;
}

double CX61850CapBase::GetCurrChAngValue(long *pnChType,long *pnChAngType,int nChIndex)
{
	if ((nChIndex<0)||(nChIndex>=STCAPPARSE_DATA_MAX_COUNT))
	{
		return 0.0f;
	}

	long nAngIndex = pnChAngType[nChIndex];

	//只有6个通道,对应0~2,4~6
	if ((nAngIndex<0)||(nAngIndex>6)||(nAngIndex == 3))
	{
		return 0.0f;
	}

	if (nAngIndex>2)
	{
		nAngIndex--;
	}

	if (pnChType[nChIndex] == CAPDEVICE_CHTYPE_U)
	{
		return m_U_B[nAngIndex].fFinitPh;
	}
	else if (pnChType[nChIndex] == CAPDEVICE_CHTYPE_I)
	{
		return m_I_B[nAngIndex].fFinitPh;
	}

	return 0.0f;
}

BOOL CX61850CapBase::Get_Value_B_P(long *pnChType,long *pnChAngType,int nChIndex
									  , _PARAMCALCOMPLEX &d_B, _PARAMCALCOMPLEX &d_P, double &d_Coef)
{
	if ((nChIndex<0)||(nChIndex>=STCAPPARSE_DATA_MAX_COUNT))
	{
		return FALSE;
	}

	long nAngIndex = pnChAngType[nChIndex];

	//只有6个通道,对应0~2,4~6
	if ((nAngIndex<0)||(nAngIndex>6)||(nAngIndex == 3))
	{
		return 0.0f;
	}

	if (nAngIndex>2)
	{
		nAngIndex--;
	}

// 	if (g_oCapAnalysisConfig.m_nShowPrimaryValue)//如果显示一次值,则此处需要设置一次、二次变比
// 	{
// 		d_Coef = g_oCapAnalysisConfig.m_fPT_Rate[0]/*PT*/;//(110000/100);//除以变比 mym
// 	} 
// 	else
	{
		d_Coef = 1.0f;
	}

	if (pnChType[nChIndex] == CAPDEVICE_CHTYPE_U)
	{
		d_B.fFinitAmp = m_U_B[nAngIndex].fFinitAmp;
		d_B.fFinitPh = m_U_B[nAngIndex].fFinitPh;
		d_B.fFinitFre = m_U_B[nAngIndex].fFinitFre;
		d_P.fFinitAmp = m_U_P[nAngIndex].fFinitAmp;
		d_P.fFinitPh = m_U_P[nAngIndex].fFinitPh;
		d_P.fFinitFre = m_U_P[nAngIndex].fFinitFre;
		return TRUE;
	}
	else if (pnChType[nChIndex] == CAPDEVICE_CHTYPE_I)
	{
		d_B.fFinitAmp = m_I_B[nAngIndex].fFinitAmp;
		d_B.fFinitPh = m_I_B[nAngIndex].fFinitPh;
		d_B.fFinitFre = m_I_B[nAngIndex].fFinitFre;

		d_P.fFinitAmp = m_I_P[nAngIndex].fFinitAmp;
		d_P.fFinitPh = m_I_P[nAngIndex].fFinitPh;
		d_P.fFinitFre = m_I_P[nAngIndex].fFinitFre;
		return TRUE;
	}

	return FALSE;
}

void CX61850CapBase::CalCompErrValue(CCapDevice6044 *pDevice6044,double dCompRelAng)
{
	if (pDevice6044->m_strID != m_strDatasetMapID_MUTestCB)
	{
		return;
	}

	double dCompDeltaValue[256] = {0};//复合误差值
	double fcomplexAmpstand = 0,    fcomplexAmp = 0,   fsum = 0;
	int nChCount = pDevice6044->GetCount();
	_PARAMCALCOMPLEX d_B;
	_PARAMCALCOMPLEX d_P;
	double d_Coef;
	//总共有多少个通道,去掉第一个延时通道剩下的；
	//这里从第二通道算起；可能会丢失一个通道；
	for (int nChnelIndex   =  0;   nChnelIndex  <  nChCount ;  nChnelIndex++)//20220614 zhouhj 已在赋值位置统一处理除以8的问题
	{
		//每个通道取80个点；
		fsum = 0;
		Get_Value_B_P(pDevice6044->m_nChType,pDevice6044->m_nChAngType,nChnelIndex, d_B, d_P, d_Coef);
		double dUI_P = sqrt(d_B.fFinitAmp*d_B.fFinitAmp + d_P.fFinitAmp*d_P.fFinitAmp);
		fsum = cap_Cal_Analysis_ComplexError_RelAng(pDevice6044->m_dVariable_FftPhaseDeltPoint[nChnelIndex],  
			dCompRelAng, pDevice6044->m_nSmpRate,d_B, d_P, d_Coef );
		dCompDeltaValue[nChnelIndex] =   100*fsum/dUI_P ;/// CAP_COMP_CNT;//除以80点数；
	}

	UpdateComplexErrorValue(dCompDeltaValue,  nChCount);
}

//计算角差并填充；2020-9-17  mym add
//zhouhj 2024.4.2 FT3报文的复合误差计算功能,也放到此函数中计算,与角差计算采用同样的数据源
void  CX61850CapBase::UpdateDvmDeviceDatas_Analysis_PhaseDelta()
{
	CString strRet;
	if (m_pDataset_RcdStep6U6I == NULL)
		return ;
	CDvmData *pSrcData = NULL;

	//_PARAMCALCOMPLEX m_U_B[6],  m_I_B[6],   m_U_P[6],  m_I_P[6];

	CString strChnelTypeXML[256];
	CString strA_B_CType[256];
	int  nChnelCntXML  = 0;
//	GetU_IParamValue(m_U_B,  m_I_B,   m_U_P,  m_I_P);//20220822 zhouhj 删除此函数,只在更新参数时调用
	GetU_IChnel(strChnelTypeXML, strA_B_CType, nChnelCntXML);		//获取电压、电流通道及其数量用于后面的计算；

	if (nChnelCntXML==0)
		return;

	int nFinished = 0;
	double dChsAngValue[256] = {0};//通道相位值
	double dChsFreqValue[256] = {0};
	double dAngDeltaValue[256] = {0};//角差值
//	double dDCValue[256] = {0};  //在常规计算时,已计算直流分量此处无需重复计算  20220817 zhouhj
	double dChsPhase[256] = {0};

	int    nChnelCnt = 0;
	POS pos = m_oCapDeviceAll.GetHeadPosition();
	CCapDeviceBase *pCapDevice = NULL;
	double dTemp = 0.0f;

	while (pos != NULL)
	{
		pCapDevice = (CCapDeviceBase*)m_oCapDeviceAll.GetNext(pos);

		if (pCapDevice->GetClassID() == CPDCLASSID_DEVICE92)
		{
			CCapDevice92 *pDevice92  =  (CCapDevice92 *)pCapDevice;

			if (pDevice92->m_nFFTStatePhaseDelt ==CAPDEV_SMV_FFTStatePhaseDelt_Init)
				continue/*return*/;//20220817  zhouhj  return改为continue

			if (pDevice92->m_nChnelCnt  > 0)
			{
				if (pDevice92->m_nFFTStatePhaseDelt == CAPDEV_SMV_FFTStatePhaseDelt_Finished)
				{		
					int   nChnelIndex    =  0;	

					//总共有多少个通道,去掉第一个延时通道剩下的；这里从第二通道算起；可能会丢失一个通道；
					for (nChnelIndex   =  0;   nChnelIndex  <  pDevice92->m_nChnelCnt/*/8*/  - 1;  nChnelIndex++)//20220614 zhouhj 已在赋值位置统一处理除以8的问题
					{
						double fPhase = 0;
					
						GetOutputPhase(strChnelTypeXML[nChnelIndex],  strA_B_CType[nChnelIndex],  fPhase);

						dChsAngValue[nChnelIndex]  =  pDevice92->m_fPhaseForPhase[nChnelIndex] ;	
						dChsFreqValue[nChnelIndex]  =  pDevice92->m_fChs_Freq[nChnelIndex] ;	
						dTemp  = fPhase - pDevice92->m_fPhaseForPhaseDelta[nChnelIndex];
						MakeAngleTo180(dTemp);

						dAngDeltaValue[nChnelIndex]  = (dTemp )  *  60;	//乘以60转化成分

						if (nChnelIndex==1)//取第二个通道计算响应时间和响应时间误差；
						{
						   //pDevice92->m_fResponseTime =  pDevice92->m_fZeroDelta + pDevice92->m_dwTimeDelayForRes ;//以前是这样的，后来MYM 陈罗飞要改成下面这样的  2020-11-05 
							pDevice92->m_fResponseTime =  pDevice92->m_fZeroDelta ;//+ pDevice92->m_dwTimeDelayForRes ;//pDevice92->m_dwTimeDelayForRes + fabs(dTemp)/4.5 * 250;// (fabs(fPhase - dCompValue[nChnelIndex] )+ ((pDevice92->m_dwTimeDelayForRes )/250) * 4.5  ) /4.5 * 250  ;//-   pDevice92->m_fZeroDelta;

							//pDevice92->m_fResponseTime =  (fPhase - dCompValue[nChnelIndex]  + ((pDevice92->m_dwTimeDelayForRes )/250) * 4.5  ) /4.5 * 250  ;//-   pDevice92->m_fZeroDelta;
							pDevice92->m_fResponseError =  pDevice92->m_fResponseTime -  pDevice92->m_dwTimeDelayForRes ;
						}
					}

					pDevice92->m_nFFTStatePhaseDelt    = CAPDEV_SMV_FFTStatePhaseDelt_Init;  //==2就表示不算了；
					pDevice92->m_nFFTIndexPhaseDelt    = 0;
					nFinished = 1;
					nChnelCnt  =  pDevice92->m_nChnelCnt;
				}
			}
		}
		else if (pCapDevice->GetClassID() == CPDCLASSID_DEVICE6044)
		{
			CCapDevice6044 *pDevice6044  =  (CCapDevice6044 *)pCapDevice;

			if (pDevice6044->m_nFFTStatePhaseDelt ==CAPDEV_SMV_FFTStatePhaseDelt_Init)
				continue;

			if ((pDevice6044->GetCount() > 0)&&
				(pDevice6044->m_nFFTStatePhaseDelt == CAPDEV_SMV_FFTStatePhaseDelt_Finished))
			{
				double dMUTimeDataRelAngle = 0.0f;//上送时间数据通道参数设置相位值
				double dFirstPointCalAngle = 0.0f;//首点计算相位:即以过零点通道的绝对时刻为基准,结合频率,推算首点时刻的相位
				double dDelayCalAngle = pDevice6044->m_dwTimeDelay*360.0f/20000.0f;

				if (GetMUTimeDataRelAngle(pDevice6044->m_nFirstRcdPointTime,pDevice6044->m_nCurrAnalogZeroTime,pDevice6044->GetPkgHeadTimeNs()
					,pDevice6044->m_nCurrTimeDataCh,50.0f,
					dMUTimeDataRelAngle,dFirstPointCalAngle))
				{
					int nChnelIndex = 0;	
					nChnelCnt = pDevice6044->GetCount();
					double dCurrChPhase = 0;//当前通道相位值
					double dCompRelAngle = dDelayCalAngle - dFirstPointCalAngle + dMUTimeDataRelAngle + 360*50/pDevice6044->m_nSmpRate;;

					for (nChnelIndex = 0;nChnelIndex < nChnelCnt;  nChnelIndex++)
					{
						dCurrChPhase = GetCurrChAngValue(pDevice6044->m_nChType,pDevice6044->m_nChAngType,nChnelIndex);
						dChsPhase[nChnelIndex] = dCurrChPhase;

//当前通道的第一个点的实际相位值 - 过零点通道时刻过后到当前第一个点的时刻的相对相位 + 过零点通道的参数设置相位 + 延时补偿相位
//当前通道的第一个点的实际相位值 - 过零点通道时刻过后到当前第一个点的时刻的相对相位 == 当前通道在参考通道过零点时刻的相位
 						dChsAngValue[nChnelIndex]  =  pDevice6044->m_fPhaseForPhaseDelta[nChnelIndex] 
						 - dFirstPointCalAngle + dMUTimeDataRelAngle + dDelayCalAngle;	
						 MakeAngleTo360(dChsAngValue[nChnelIndex]);//显示的测量相位值
 						dChsFreqValue[nChnelIndex]  =  pDevice6044->m_fChs_Freq[nChnelIndex] ;	
 						dTemp  = dCurrChPhase - dChsAngValue[nChnelIndex];
 						MakeAngleTo180(dTemp);
 						dAngDeltaValue[nChnelIndex]  = (dTemp )  *  60;	//乘以60转化成分
					}

					CalCompErrValue(pDevice6044,dCompRelAngle);
					pDevice6044->m_nFFTStatePhaseDelt    = CAPDEV_SMV_FFTStatePhaseDelt_Init;  //==2就表示不算了；
					pDevice6044->m_nFFTIndexPhaseDelt    = 0;
					nFinished = 1;
				}
				else//如果获取的时间数据相位有问题,则忽略
				{
					pDevice6044->m_nFFTStatePhaseDelt    = CAPDEV_SMV_FFTStatePhaseDelt_Init;  //==2就表示不算了；
					pDevice6044->m_nFFTIndexPhaseDelt    = 0;
				}
			}
		}
	}

	if (nFinished==1)
	{
		//更新角差
		UpdatePhaseDeltaValue(dAngDeltaValue,dChsPhase, nChnelCnt);

		UpdateDvmDeviceDatas_Analysis_MagPhaseFreq();

		//更新相位值；
//		UpdatePhaseValue(dChsAngValue,  nChnelCnt);
		UpdateValue_MUTest(dChsAngValue,  nChnelCnt,"$ang");

		//更新频率值
		UpdateValue_MUTest(dChsFreqValue,  nChnelCnt,"$freq");


	       //更新基波值；
		UpdateVlaue_HarmBase("$Base");


		//更新直流分量值；2020-12-09
//		UpdateDCValue(dDCValue,  nChnelCnt);  //zhouhj 20220817  合并单元测试不需要测量直流分量,去除
	}
}

void  CX61850CapBase::GetOutputPhase(const CString &strU_IType, const CString &strA_B_CType, double & dPhase)
{	
	if (strU_IType=="V" || strU_IType=="v")//表示电压
	{
		if (strA_B_CType=="a")
			dPhase   = 	m_U_B[0].fFinitPh;
		if (strA_B_CType=="b")
			dPhase   = 	m_U_B[1].fFinitPh;
		if (strA_B_CType=="c")
			dPhase   = 	m_U_B[2].fFinitPh;
	}
	else if (strU_IType=="A" || strU_IType=="a")//表示电流
	{
		if (strA_B_CType=="a")
			dPhase   = 	m_I_B[0].fFinitPh;
		if (strA_B_CType=="b")
			dPhase   = 	m_I_B[1].fFinitPh;
		if (strA_B_CType=="c")
			dPhase   = 	m_I_B[2].fFinitPh;
	}
}

//计算角差并填充；2020-9-17  mym add
void  CX61850CapBase::UpdateDvmDeviceDatas_Analysis_Response()
{
	if (m_pDataset_RcdStepResponse == NULL)
		return;

	CDvmData *pSrcData = NULL;

	int    nChnelCnt = 0;
	POS pos = m_oCapDeviceAll.GetHeadPosition();
	CCapDeviceBase *pCapDevice = NULL;
	double dResponseTime;
	double dTimeError;
	double dTimeDelay;

	CCapDevice92 *pDevice92 = NULL;

	while (pos != NULL)
	{
		pCapDevice = (CCapDeviceBase*)m_oCapDeviceAll.GetNext(pos);
		if (pCapDevice->GetClassID() == CPDCLASSID_DEVICE92)
		{
			//取第一个SV控制块
			pDevice92  =  (CCapDevice92 *)pCapDevice;	
			break;
		}
	}

	if (pDevice92==NULL)
		return;
	dResponseTime = pDevice92->m_fResponseTime;
	dTimeError = pDevice92->m_fResponseError;
	dTimeDelay = pDevice92->m_dwTimeDelayForRes;

	CDvmData *pSv1 = (CDvmData *)m_pDataset_RcdStepResponse->GetHead();

	if (pSv1 == NULL)
		return;

	CDvmValue *pValue = NULL;
	pos = pSv1->GetHeadPosition();

	while (pos != NULL)
	{
		pValue = (CDvmValue *)pSv1->GetNext(pos);

		if (pValue->m_strID.Find(_T("MsgResponseTm")) >= 0)
		{
			pValue->m_strValue.Format(_T("%.3f"), dResponseTime);
		}
		else if (pValue->m_strID.Find(_T("ResponseTmError")) >= 0)
		{
			pValue->m_strValue.Format(_T("%.3f"), dTimeError);
		}
		else  if (pValue->m_strID.Find(_T("StdChDelay")) >= 0)
		{
			pValue->m_strValue.Format(_T("%.3f"), dTimeDelay);
		}
	}
}

//从dsRcdStep6U6I数据集中根据外面传入的ID 获取value
// mym add 2020-8-17
CString  CX61850CapBase::Get6u6iValue(CString strDstID, int nCnt)
{
	CString strRet;

	if (m_pDataset_RcdStep6U6I == NULL)
	{
		return strRet;
	}

	POS pos = NULL;
	CString strSrcID;
	CString strID;
	pos = m_pDataset_RcdStep6U6I->GetHeadPosition();
	CDvmData *pSrcData = NULL;
	while (pos != NULL)
	{
		pSrcData  =  (CDvmData *)m_pDataset_RcdStep6U6I->GetNext(pos);
		strSrcID  =  pSrcData->m_strID;
		strID = strSrcID.Left(nCnt);

		if (strDstID==strID)
		{
			strRet = pSrcData->m_strValue;
			break;
		}
	}

	return strRet;
}

void CX61850CapBase::Get_Value_B_P(const CString &strChnelTypeXML, const CString &strA_B_CType,
								   _PARAMCALCOMPLEX &d_B, _PARAMCALCOMPLEX &d_P, double &d_Coef)
{
	if (strChnelTypeXML=="V" || strChnelTypeXML=="v")//表示电压
	{
		if (strA_B_CType=="a")
		{
			d_B = m_U_B[0];
			d_P = m_U_P[0];
		}
		else if (strA_B_CType=="b")
		{
			d_B = m_U_B[1];
			d_P = m_U_P[1];
		}
		else if (strA_B_CType=="c")
		{
			d_B = m_U_B[2];
			d_P = m_U_P[2];
		}

		if (g_oCapAnalysisConfig.m_nShowPrimaryValue)//如果显示一次值,则此处需要设置一次、二次变比
		{
			d_Coef = g_oCapAnalysisConfig.m_fPT_Rate[0]/*PT*/;//(110000/100);//除以变比 mym
		} 
		else
		{
			d_Coef = 1.0f;
		}
	}
	else if (strChnelTypeXML=="A" || strChnelTypeXML=="a")//表示电流
	{

		if (strA_B_CType=="a")
		{
			d_B = m_I_B[0];
			d_P = m_I_P[0];
		}
		else if (strA_B_CType=="b")
		{
			d_B = m_I_B[1];
			d_P = m_I_P[1];
		}
		else if (strA_B_CType=="c")
		{
			d_B = m_I_B[2];
			d_P = m_I_P[2];
		}

		if (g_oCapAnalysisConfig.m_nShowPrimaryValue)//如果显示一次值,则此处需要设置一次、二次变比
		{
			d_Coef  = g_oCapAnalysisConfig.m_fCT_Rate[0]/*CT*/;//(1000/1);//除以变比  mym
		} 
		else
		{
			d_Coef = 1.0f;
		}
	}

}

double  cap_Cal_Analysis_ComplexError(double *pDatas, double dHardDelay, _PARAMCALCOMPLEX &d_B, _PARAMCALCOMPLEX &d_P, double &d_Coef)
{
	double fcomplexAmpstand = 0;

	double dFreCoef_PI = 2 * PI / 4000;
	double dCoef_Point = 0;
	//double dHardDelay = 1000;//1308
	double dTCoef_P = dHardDelay *  2 * PI* d_P.fFinitFre / 1000000.0;// / 360;
	double dTCoef_B = dHardDelay *  2 * PI* d_B.fFinitFre / 1000000.0;// / 360;

	double fsum = 0, ft = 0;
	double dValue = 0;
	double dAngleB, dAngleP;


	for(int nPoint  =  0;  nPoint  <  CAP_COMP_CNT + 0;  nPoint++)
	{
		dCoef_Point = dFreCoef_PI * nPoint;

		dAngleB = dCoef_Point * d_B.fFinitFre - dTCoef_B  + d_B.fFinitPh *_PI_D_180;
		dAngleP = dCoef_Point * d_P.fFinitFre - dTCoef_P  + d_P.fFinitPh *_PI_D_180;

		fcomplexAmpstand = 
			d_B.fFinitAmp * 1.414 * sin(dAngleB);
//		+ d_P.fFinitAmp * 1.414 * sin(dAngleP);

// 		fcomplexAmpstand = m_U_B[0].fFinitAmp *  1.414  *  sin(2  *  PI  *  m_U_B[0].fFinitFre  *  nPoint/4000  -  m_fHardWareDelay  * 2  *  PI  *  m_U_P[0].fFinitFre / 1000000.0 / 360 + m_U_B[0].fFinitPh)
// 			+m_U_P[0].fFinitAmp  *  1.414  * sin(2 * PI * m_U_P[0].fFinitFre * nPoint/4000  -  m_fHardWareDelay  *  2  *  PI  *  m_U_P[0].fFinitFre/1000000.0/360  +  m_U_P[0].fFinitPh);
		dValue = pDatas[nPoint] / d_Coef;
		ft = dValue  - fcomplexAmpstand;
		ft = ft * ft;
		//ft = sqrt(abs(ft));  //sqrt(abs(ft));
		fsum += ft;
// 		if (fsum==0)
// 		{
// 			int adf = 0;
// 		}
	}

	fsum /= 80;///sqrt(ft);  //sqrt(abs(ft));
	return sqrt(fsum);
}

double  cap_Cal_Analysis_ComplexError_RelAng(double *pDatas, double dRelAng, long nSmpRate,
											 _PARAMCALCOMPLEX &d_B, _PARAMCALCOMPLEX &d_P, double &d_Coef)
{
	double fcomplexAmpstand = 0;
	double dFreCoef_PI = 2 * PI / nSmpRate;
	double dCoef_Point = 0;
	double dTCoef_B = dRelAng*_PI_D_180;
	double dTCoef_P = dRelAng*_PI_D_180*d_P.fFinitFre/50.0f;
	double fsum = 0, ft = 0;
	double dValue = 0;
	double dAngleB, dAngleP;
	long nSingleCirclePoints = nSmpRate/50;

	if (nSingleCirclePoints>1000)//最大支持单周波1000个点
	{
		nSingleCirclePoints = 1000;
	}

	for(int nPoint  =  0;  nPoint  <  nSingleCirclePoints;  nPoint++)
	{
		dCoef_Point = dFreCoef_PI * nPoint;

		dAngleB = dCoef_Point * d_B.fFinitFre - dTCoef_B  + d_B.fFinitPh *_PI_D_180;
		dAngleP = dCoef_Point * d_P.fFinitFre - dTCoef_P  + d_P.fFinitPh *_PI_D_180;

		fcomplexAmpstand = 
			d_B.fFinitAmp * 1.414 * sin(dAngleB);
		dValue = pDatas[nPoint] / d_Coef;
		ft = dValue  - fcomplexAmpstand;
		ft = ft * ft;
		fsum += ft;
	}

	fsum /= nSingleCirclePoints;///sqrt(ft);  //sqrt(abs(ft));
	return sqrt(fsum);
}

void CX61850CapBase::UpdateUI_Paras(BOOL bUpdateZeroDriftByUIValue)
{
	for (int nIndex = 0;nIndex<6;nIndex++)
	{
		m_U_B[nIndex].fFinitAmp = 0.0f;
		m_U_B[nIndex].fFinitPh = 0.0f;
		m_U_B[nIndex].fFinitFre = 50.0f;

		m_I_B[nIndex].fFinitAmp = 0.0f;
		m_I_B[nIndex].fFinitPh = 0.0f;
		m_I_B[nIndex].fFinitFre = 50.0f;

		m_U_P[nIndex].fFinitAmp = 0.0f;
		m_U_P[nIndex].fFinitPh = 0.0f;
		m_U_P[nIndex].fFinitFre = 50.0f;

		m_I_P[nIndex].fFinitAmp = 0.0f;
		m_I_P[nIndex].fFinitPh = 0.0f;
		m_I_P[nIndex].fFinitFre = 50.0f;
	}

	m_bIsZeroDriftTest = FALSE;
	m_dZeroDrift_Un = 57.74f;
	m_dZeroDrift_In = 1.0f;
//	m_dDelayCompens_NoPPS = 0.0f;
	GetU_IParamValue(m_U_B,  m_I_B,   m_U_P,  m_I_P);
  	UpdateFirstCyclePoints();//更新首周波参数
	m_bFirstCWDatasChanged = true;

	if (bUpdateZeroDriftByUIValue)
	{
		InitZeroDriftBy6U6I();//更新零漂参数,根据当前实际输出电压电流
	}

	InitSVDatasetAmpAng_MUTest();
}

void CX61850CapBase::InitZeroDriftBy6U6I()
{
	BOOL bZeroDriftTest = TRUE;

	for (int nIndex = 0;nIndex<6;nIndex++)
	{
		if (fabs(m_U_B[nIndex].fFinitAmp)>0.0001)//任意一相电压或电流大于0,则为非零漂
		{
			bZeroDriftTest = FALSE;
			break;
		}

		if (fabs(m_I_B[nIndex].fFinitAmp)>0.0001)
		{
			bZeroDriftTest = FALSE;
			break;
		}
	}

	m_bIsZeroDriftTest = bZeroDriftTest;
//	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("当前零漂状态值(%d)."),(int)m_bIsZeroDriftTest);
}

//根据当前输入电压电流，更新首周波输入波形(6U6I)
void CX61850CapBase::UpdateFirstCyclePoints()
{
	for (int nCh = 0; nCh < 6; nCh++)
	{
		for (int i = 0; i < 800; i++)
		{
			m_oStdSrcDatas_FirstCW[nCh][i] = m_U_B[nCh].fFinitAmp*sin(double(i*PI/200) 
				+ m_U_B[nCh].fFinitPh*PI/180);
			m_oStdSrcDatas_FirstCW[nCh +6][i] = m_I_B[nCh].fFinitAmp*sin(double(i*PI/200) 
				+ m_I_B[nCh].fFinitPh*PI/180);
		}

	}

	//原始数据根据通道类型取
// 	CCapDeviceBase *pCapDevice = NULL;
// 	pCapDevice = GetMUTestCapDevice();
// 
// 	if (pCapDevice == NULL)
// 	{
// 		return;
// 	}
// 
// 	if (pCapDevice->GetClassID() != CPDCLASSID_DEVICE92)
// 	{
// 		return;
// 	}
// 
// 	CCapDevice92 *pDevice92 = (CCapDevice92*)pCapDevice;
// 	CCapDeviceSmvCh *pSmvCh = NULL;
// 	POS pos = pDevice92->GetHeadPosition();
// 	long nIndex = 0;
// 
// 	while(pos)
// 	{
// 		pSmvCh = (CCapDeviceSmvCh *)pDevice92->GetNext(pos);
// 		long nChAngType = pSmvCh->m_nChAngType;
// 		if (pSmvCh->m_nChType == CAPDEVICE_CHTYPE_U)
// 		{
// 			if (nChAngType < 2)
// 			{
// 				memcpy(pDevice92->m_dPointYs[nIndex][0], m_oStdSrcDatas_FirstCW[nChAngType],sizeof(m_oStdSrcDatas_FirstCW[nChAngType]));
// 			}	
// 		}
// 		if (pSmvCh->m_nChType == CAPDEVICE_CHTYPE_I)
// 		{
// 			if(nChAngType < 2)
// 			{
// 				memcpy(pDevice92->m_dPointYs[nIndex][0], m_oStdSrcDatas_FirstCW[nChAngType +6],sizeof(m_oStdSrcDatas_FirstCW[nChAngType+6]));
// 			}		
// 		}
// 		nIndex++;
// 	}
}

void CX61850CapBase::InitSVDatasetAmpAng_MUTest()
{
	if (m_pDataset_MUTestCB == NULL)
	{
		return;
	}

	CDvmData *pCurrChData = NULL;
	POS pos = m_pDataset_MUTestCB->GetHeadPosition();
	CCapDeviceBase *pCapDeviceBase = (CCapDeviceBase*)m_oCapDeviceAll.FindByID(m_strDatasetMapID_MUTestCB);
	CCapDeviceSmvCh *pDevCh = NULL;
	long nIndex = 0;

	while(pos)
	{
		pCurrChData = (CDvmData *)m_pDataset_MUTestCB->GetNext(pos);
		pDevCh = NULL;

		if (pCapDeviceBase != NULL)
		{
			pDevCh = (CCapDeviceSmvCh*)pCapDeviceBase->FindByID(pCurrChData->m_strID);
		}

		InitSVDatasetAmpAng_MUTest(pCurrChData,pDevCh);
		nIndex++;
	}
}

void CX61850CapBase::InitSVDatasetAmpAng_MUTest(CDvmData *pCurrChData,CCapDeviceSmvCh *pDevCh)
{
	ASSERT(pCurrChData);
	long nIndex = pCurrChData->m_strID.ReverseFind('_');

	if (nIndex<=0)
	{
		return;
	}

	CString strChID;
	double dAmpValue = 0.0f,dAngValue = 0.0f;
	strChID = pCurrChData->m_strID.Mid(nIndex+1);

	if (GetChAmpAng(strChID,&dAmpValue,&dAngValue))
	{
		if (!m_bIsZeroDriftTest)//非零漂测试项时设置为当前输出值
		{
			pCurrChData->m_strValue.Format(_T("%lf"),dAmpValue);
		}
		else if ((pCurrChData->m_strDataType == _T("Curr"))||(pCurrChData->m_strDataType == _T("电流")))//零漂测试时,设置为当前额定电流、额定电压
		{
			pCurrChData->m_strValue.Format(_T("%lf"),m_dZeroDrift_In);
		}
		else if ((pCurrChData->m_strDataType == _T("Vol"))||(pCurrChData->m_strDataType == _T("电压")))
		{
			pCurrChData->m_strValue.Format(_T("%lf"),m_dZeroDrift_Un);
		}

		pCurrChData->m_strFormat.Format(_T("%lf"),dAngValue);
	}

	if (pDevCh != NULL)
	{
		pCurrChData->m_nIndex = pDevCh->m_nAccurLevel;
		pCurrChData->m_nChange = pDevCh->m_nSelect;
//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("[%s--->%ld]"),pCurrChData->m_strName.GetString(),pDevCh->m_nSelect);
	}
}

BOOL CX61850CapBase::GetChAmpAng(const CString &strChID, double *pdAmp,double *pdAng)
{
	BOOL bRet = FALSE;
	int nIndex = 0,n6U6I_ChIndex = 0;
	_PARAMCALCOMPLEX *pParaComplex = NULL;

	for (nIndex = 0;nIndex<12;nIndex++)
	{
		if (g_strListChannelName[nIndex] == strChID)
		{
			if (nIndex>=6)
			{
				n6U6I_ChIndex = nIndex-6;
				pParaComplex = &m_I_B[n6U6I_ChIndex];
			} 
			else
			{
				n6U6I_ChIndex = nIndex;
				pParaComplex = &m_U_B[nIndex];
			}
		
			if (pdAmp != NULL)
			{
				*pdAmp = pParaComplex->fFinitAmp;
			}
			
			if (pdAng != NULL)
			{
				*pdAng = pParaComplex->fFinitPh;
			}
			
			bRet = TRUE;
			break;
		}
	}

	return bRet;
}

//计算出复合误差并填充；2020-9-8  mym add
void  CX61850CapBase::UpdateDvmDeviceDatas_Analysis_ComplexError()
{
//	static long g_nAnalysis_ComplexError_Flag = 0;

	CString strRet;
	if (m_pDataset_RcdStep6U6I == NULL)
		return ;
	CDvmData *pSrcData = NULL;

// 	_PARAMCALCOMPLEX m_U_B[6],  m_I_B[6],   m_U_P[6],  m_I_P[6];
// 	GetU_IParamValue(m_U_B,  m_I_B,   m_U_P,  m_I_P);

//	GetU_IParamValue(m_U_B,  m_I_B,   m_U_P,  m_I_P);//20220822 zhouhj 删除此函数,只在更新参数时调用
	CString strChnelTypeXML[256];
	CString strA_B_CType[256];
	int  nChnelCntXML  = 0;

	GetU_IChnel(strChnelTypeXML, strA_B_CType, nChnelCntXML);		//获取电压、电流通道及其数量用于后面的计算；

	if (nChnelCntXML==0)
		return;

	double dCompValue[256] = {0};
	int    nChnelCnt = 0;
	POS pos = m_oCapDeviceAll.GetHeadPosition();
	CCapDeviceBase *pCapDevice = NULL;

	while (pos != NULL)
	{
		pCapDevice = (CCapDeviceBase*)m_oCapDeviceAll.GetNext(pos);

		if (pCapDevice->GetClassID() == CPDCLASSID_DEVICE92)
		{
			double fcomplexAmpstand = 0,    fcomplexAmp = 0,   fsum = 0;
			//float fHardWareDelay = 1308.0;
			int   nChnelIndex    =  0;

			CCapDevice92 *pDevice92  =  (CCapDevice92 *)pCapDevice;
			nChnelCnt  = pDevice92->m_nChnelCnt ;
			if (pDevice92->m_nFFTStateComp == 0)
				continue;/*return;*///20220920 zhouhj 配合处理dsSV1改为动态方式

			if (pDevice92->m_nFFTStateComp == 2)//	if (pDevice92->m_nFFTIndexComp  >  CAP_COMP_CNT + 8)
			{				
				/*
				if (g_nAnalysis_ComplexError_Flag == 10)
				{
				CString strComplexCH;

				for (nChnelIndex   =  0;   nChnelIndex  <  nChnelCnt/8 - 1 ;  nChnelIndex++)
				{
				if (nChnelIndex==0||nChnelIndex==15)
				{
				strComplexCH.Format(_T("C_%02d_"), nChnelIndex);
				cap_WriteRcdFile_Txt(pDevice92->m_dVariable_FftPoint[nChnelIndex], 80, strComplexCH);
				}
				}
				}
				else
				{
				g_nAnalysis_ComplexError_Flag++;
				}
				*/
				
				//这里可以计算了；

				//总共有多少个通道,去掉第一个延时通道剩下的；
				//这里从第二通道算起；可能会丢失一个通道；
				for (nChnelIndex   =  0;   nChnelIndex  <  nChnelCnt/*/8*/ - 1 ;  nChnelIndex++)//20220614 zhouhj 已在赋值位置统一处理除以8的问题
				{
					//每个通道取80个点；
					fsum = 0;
					_PARAMCALCOMPLEX d_B;
					_PARAMCALCOMPLEX d_P;
					double d_Coef;
					Get_Value_B_P(strChnelTypeXML[nChnelIndex], strA_B_CType[nChnelIndex], d_B, d_P, d_Coef);
					double dUI_P = sqrt(d_B.fFinitAmp*d_B.fFinitAmp + d_P.fFinitAmp*d_P.fFinitAmp);
					fsum = cap_Cal_Analysis_ComplexError(pDevice92->m_dVariable_FftPoint[nChnelIndex],  (double)pDevice92->m_dwTimeDelayForRes, d_B, d_P, d_Coef );
					dCompValue[nChnelIndex] =   100*fsum/dUI_P ;/// CAP_COMP_CNT;//除以80点数；

// 					if (nChnelIndex == 0)
// 					{
// 						CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("第一个通道,d_B.fFinitAmp=%f,d_B.fFinitFre=%f,d_P.fFinitAmp=%f,d_P.fFinitFre=%f,d_Coef=%lf,dCompValue=%lf"),
// 							d_B.fFinitAmp,d_B.fFinitFre,d_P.fFinitAmp,d_P.fFinitFre,d_Coef,dCompValue[nChnelIndex]);
// 					}

					/*
					for(int nPoint  =  7;  nPoint  <  CAP_COMP_CNT + 7;  nPoint++)
					{
					//计算出标准值；
					if (strChnelTypeXML[nChnelIndex]=="V" || strChnelTypeXML[nChnelIndex]=="v")//表示电压
					{
					if (strA_B_CType[nChnelIndex]=="a")
					{
					fcomplexAmpstand = m_U_B[0].fFinitAmp *  1.414  *  sin(2  *  PI  *  m_U_B[0].fFinitFre  *  nPoint/4000  -  m_fHardWareDelay  * 2  *  PI  *  m_U_P[0].fFinitFre / 1000000.0 / 360 + m_U_B[0].fFinitPh)
					+m_U_P[0].fFinitAmp  *  1.414  * sin(2 * PI * m_U_P[0].fFinitFre * nPoint/4000  -  m_fHardWareDelay  *  2  *  PI  *  m_U_P[0].fFinitFre/1000000.0/360  +  m_U_P[0].fFinitPh);
					}			
					}					
					*/
				}

				pDevice92->m_nFFTStateComp   = 0;  //==2就表示不算了；
				pDevice92->m_nFFTIndexComp   = 0;

				if (pDevice92->m_strID == m_strDatasetMapID_MUTestCB/*CAP_DATASET_MAP_ID_dsSV1*/)
				{
	//更新复合误差的字段值,把计算出来的复合误差填到那个字段里；
					UpdateComplexErrorValue(dCompValue,  nChnelCnt);//20220813 从函数最底部，挪到此处,当前只对第一个控制块计算复合误差
				}
			}
		}
	}
}

//获取基波电压电流、谐波电压电流；2020-9-8  add mym 
void  CX61850CapBase::GetU_IParamValue(_PARAMCALCOMPLEX *pU_B,  _PARAMCALCOMPLEX *pI_B,  _PARAMCALCOMPLEX *pU_P, _PARAMCALCOMPLEX *pI_P)
{
	if (m_pDataset_RcdStep6U6I == NULL)
		return;

	CString strSrcID;
	CString strID;
	POS pos = m_pDataset_RcdStep6U6I->GetHeadPosition();
	double dFreqValue = 50.000f;
	CDvmData *pSrcData = (CDvmData*)m_pDataset_RcdStep6U6I->FindByID(_T("Freq"));

	if (pSrcData != NULL)
	{
		dFreqValue = CString_To_double(pSrcData->m_strValue);
	}

	//这里可以获取XML文件中的值；
	while (pos != NULL)
	{
		pSrcData  =  (CDvmData *)m_pDataset_RcdStep6U6I->GetNext(pos);
		strSrcID  =  pSrcData->m_strID;
		//	strID = strSrcID.Left(nCnt);
		if (strSrcID== "Freq")
		{
			continue;
		}
		else if (strSrcID == X61850_CapID_IsZeroDriftTest)
		{
			m_bIsZeroDriftTest = CString_To_long(pSrcData->m_strValue);
			continue;
		}
		else if (strSrcID == X61850_CapID_ZeroDrift_Un)
		{
			m_dZeroDrift_Un = CString_To_double(pSrcData->m_strValue);
			continue;
		}
		else if (strSrcID == X61850_CapID_ZeroDrift_In)
		{
			m_dZeroDrift_In = CString_To_double(pSrcData->m_strValue);
			continue;
		}
//  		else if (strSrcID == X61850_CapID_DelayCompens_NoPPS)
//  		{
//  //			m_dDelayCompens_NoPPS = CString_To_double(pSrcData->m_strValue);
//  			continue;
//  		}		
		////////////////////////////////////////////////////////////////////////////////////////////////
		for(int i = 0;  i < 12;  i++)
		{
			if (g_strListChannelName[i]==strSrcID)
			{
				if (i < 6)//基波电压幅值
				{
					(pU_B + i)->fFinitAmp =  CString_To_double(pSrcData->m_strValue);
					(pU_B + i)->fFinitFre =  dFreqValue;
					break;
				}
				else if (i  >= 6)//基波电流幅值
				{
					(pI_B + i  -  6)->fFinitAmp =  CString_To_double(pSrcData->m_strValue);
					(pI_B + i  -  6)->fFinitFre =  dFreqValue;
					break;
				}		   
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////
		for(int i = 0;  i < 12;  i++)
		{
			if (g_strListChannelPh[i]==strSrcID)
			{
				if (i < 6)//基波电压相位
				{
					(pU_B + i)->fFinitPh    =  CString_To_double(pSrcData->m_strValue);
					(pU_B + i)->fFinitFre   =  dFreqValue;
					break;
				}
				else if (i  >= 6)//基波电流相位
				{
					(pI_B + i  -  6)->fFinitPh   =  CString_To_double(pSrcData->m_strValue);
					(pI_B + i  -  6)->fFinitFre  =  dFreqValue;
					break;
				}		   
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////
		for(int i = 0;  i < 12;  i++)
		{
			if (g_strListChannelHarm[i]==strSrcID)
			{
				if (i < 6)//谐波电压幅值
				{
					(pU_P + i)->fFinitAmp  =  CString_To_double(pSrcData->m_strValue);
					(pU_P + i)->fFinitFre    =  dFreqValue;
					break;
				}
				else if (i  >= 6)//谐波电流幅值
				{
					(pI_P + i  - 6)->fFinitAmp =  CString_To_double(pSrcData->m_strValue);
					(pI_P + i  - 6)->fFinitFre    =  dFreqValue;
					break;
				}		   
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////////////
		for(int i = 0;  i < 12;  i++)
		{
			if (g_strListChannelHarmPh[i]==strSrcID)
			{
				if (i < 6)//谐波电压相位
				{
					(pU_P + i)->fFinitPh =  CString_To_double(pSrcData->m_strValue);
					(pU_P + i)->fFinitFre =  dFreqValue;
					break;
				}
				else if (i  >= 6)//谐波电流相位
				{
					(pI_P + i - 6)->fFinitPh =  CString_To_double(pSrcData->m_strValue);
					(pI_P + i - 6)->fFinitFre =  dFreqValue;
					break;
				}		   
			}
		}
	}
}

//获取具体电流、电压通道的数量和类型；2020-9-8 mym add 
void CX61850CapBase::GetU_IChnel(CString strName[],  CString strA_B_CType[], int & nChnelCnt)
{
	nChnelCnt = 0;

	if (m_pDataset_MUTestCB==NULL)
		return;

	CDvmData *pDstData = NULL;
	int nChIndex = 0,nIndexABC = 0;; 
	POS pos = m_pDataset_MUTestCB->GetHeadPosition();;

	while (pos != NULL)
	{
		pDstData  =  (CDvmData *)m_pDataset_MUTestCB->GetNext(pos);
		nIndexABC = 0;

		for (nChIndex = 0; nChIndex < 12; nChIndex++)
		{
			if  (pDstData->m_strID.Find(g_strListChannelName[nChIndex])  > 0)
			{
				nIndexABC = nChIndex%3;
				break;
			}
		}
		
		if  (pDstData->m_strUnit=="A"||pDstData->m_strUnit=="a" ||
			pDstData->m_strUnit=="v"||pDstData->m_strUnit=="V")
		{
			strName[nChnelCnt] = pDstData->m_strUnit;
			if (nIndexABC==0)					
				strA_B_CType[nChnelCnt] = "a";
			else if (nIndexABC==1)					
				strA_B_CType[nChnelCnt] = "b";
			else if (nIndexABC==2)					
				strA_B_CType[nChnelCnt] = "c";

			nChnelCnt++;
		}
	}
}

// 更新复合误差的值 2020-9-8 mayangming add 
void CX61850CapBase::UpdateComplexErrorValue(double * pValue,  int nChnelCnt)
{
	if (m_pDataset_MUTestCB == NULL)
		return;

	double dCompValue[256] = {0};
	if (nChnelCnt  > 256)
		nChnelCnt = 256;
	for (int i = 0; i < nChnelCnt;  i++)
		dCompValue[i]  = *(pValue + i);

	POS pos = m_pDataset_MUTestCB->GetHeadPosition();
	
	int nIndex = 0;

	CDvmData *pDstData = NULL;
	CDvmValue * pDvmValue = NULL;

	int nChnelIndex = 0;
	while (pos != NULL)
	{
		//当通道数量够了后直接跳出来；
		if (nChnelIndex  > nChnelCnt)
			break;

		pDstData  =  (CDvmData *)m_pDataset_MUTestCB->GetNext(pos);

		if (pDstData->m_strID.Find(_T("DelayTRtg")) != -1)//20220813 zhouhj 过滤掉延时通道
		{
			continue;
		}

		float fMag = 0 ,fPhase = 0;
		POS posIn = pDstData->GetHeadPosition();
		while(posIn != NULL)
		{
			pDvmValue  =  (CDvmValue *)pDstData->GetNext(posIn);
			if(pDvmValue->m_strID.Find("$mag") > 0)
			{
				fMag = CString_To_double(pDvmValue->m_strValue);
			}
			else if(pDvmValue->m_strID.Find("$ang") > 0)
			{
				fPhase = CString_To_double(pDvmValue->m_strValue);
			}

			//复合误差
			if(pDvmValue->m_strID.Find(STT_RcdInit_DL_CompError/*"$CompError"*/) > 0)
			{
				if (m_bIsFT3ADMU)
				{
					CString strTmpID = pDvmValue->m_strID + STT_RcdInit_DL_MaxMagValue;
					double dMaxActualValue = fMag;
					CDvmValue *pMaxActualValue = dvm_FindAddByID(pDvmValue,strTmpID,pDvmValue->m_strValue);
					dMaxActualValue = CString_To_double(pMaxActualValue->m_strValue);
					if (fMag > dMaxActualValue)
					{
						dMaxActualValue = fMag;
						pMaxActualValue->m_strValue.Format(_T("%lf"),fMag);
					}

					SetErrorStatisValues_ADMU(pDvmValue,fPhase,dCompValue[nChnelIndex],MUAccuracy_ErrorType_CompError ,pDstData->m_nIndex,pDstData->m_strDataType);
				}
				else
				{
				SetErrorStatisValues_MU(pDvmValue,dCompValue[nChnelIndex],MUAccuracy_ErrorType_CompError ,pDstData->m_nIndex,pDstData->m_strDataType);
				}
				//pDvmValue->m_strValue.Format(_T("%.6f"),   dCompValue[nChnelIndex]);
			}
		}
		nChnelIndex++;
	}
}


// 更新复合误差的值 2020-11-2 mym add 
void CX61850CapBase::UpdateTestModeValue(double * pValue,  int nChnelCnt)
{
	if (m_pDataset_MUTestCB == NULL)
		return;

	double dCompValue[256] = {0};
	if (nChnelCnt  > 256)
		nChnelCnt = 256;
	for (int i = 0; i < nChnelCnt;  i++)
		dCompValue[i]  = *(pValue + i);

	POS pos = m_pDataset_MUTestCB->GetHeadPosition();

	int nIndex = 0;

	CDvmData *pDstData = NULL;
	CDvmValue * pDvmValue = NULL;

	int nChnelIndex = 0;
	while (pos != NULL)
	{
		//当通道数量够了后直接跳出来；
		if (nChnelIndex  > nChnelCnt)
			break;

		pDstData  =  (CDvmData *)m_pDataset_MUTestCB->GetNext(pos);

		POS posIn = pDstData->GetHeadPosition();
		while(posIn != NULL)
		{
			pDvmValue  =  (CDvmValue *)pDstData->GetNext(posIn);

			if(pDvmValue->m_strID.Find("$TestValue") > 0)
				pDvmValue->m_strValue.Format(_T("%.6f"),   dCompValue[nChnelIndex]);
		}
		nChnelIndex++;
	}
}

// 添加直流分量的值 2020-12-09 mayangming add 
void CX61850CapBase::UpdateDCValue(double * pValue,  int nChnelCnt)
{
	if (m_pDataset_MUTestCB == NULL)
		return;

	double dCompValue[256] = {0};
	if (nChnelCnt  > 256)
		nChnelCnt = 256;
	for (int i = 0; i < nChnelCnt;  i++)
		dCompValue[i]  = *(pValue + i);

	POS pos = m_pDataset_MUTestCB->GetHeadPosition();

	int nIndex = 0;

	CDvmData *pDstData = NULL;
	CDvmValue * pDvmValue = NULL;

	int nChnelIndex = 0;
	while (pos != NULL)
	{
		//当通道数量够了后直接跳出来；
		if (nChnelIndex  > nChnelCnt)
			break;

		pDstData  =  (CDvmData *)m_pDataset_MUTestCB->GetNext(pos);

		POS posIn = pDstData->GetHeadPosition();
		while(posIn != NULL)
		{
			pDvmValue  =  (CDvmValue *)pDstData->GetNext(posIn);

			//相位更新；
			if(pDvmValue->m_strID.Find("$DC") > 0)
				pDvmValue->m_strValue.Format(_T("%.6f"),   dCompValue[nChnelIndex]);
		}
		nChnelIndex++;
	}
}

BOOL CX61850CapBase::UpdateMUTimeRlt(CDataGroup *pRtSycTime)
{
	CDvmData *pPpsIndexData = (CDvmData*)pRtSycTime->FindByID("PPSIndex");
	CDvmData *pPpsValueData = (CDvmData*)pRtSycTime->FindByID("PPSValue");

	if ((pPpsIndexData == NULL)||(pPpsValueData == NULL) || m_pDataset_MUTimeRlt == NULL)
	{
		return FALSE;
	}

	CDvmData *pHasUsingTime = (CDvmData*)m_pDataset_MUTimeRlt->FindByID(STT_MUTEST_HasUsingTime);
	CDvmData *pMaxErrTime = (CDvmData*)m_pDataset_MUTimeRlt->FindByID(STT_MUTEST_MaxErrTime);
	CDvmData *pMinErrTime = (CDvmData*)m_pDataset_MUTimeRlt->FindByID(STT_MUTEST_MinErrTime);
	CDvmData *pCurrErrTime = (CDvmData*)m_pDataset_MUTimeRlt->FindByID(STT_MUTEST_CurrErrTime);
	CDvmData *pAverageErrTime = (CDvmData*)m_pDataset_MUTimeRlt->FindByID(STT_MUTEST_AverageErrTime);
	CDvmData *pMUTimeResult = (CDvmData*)m_pDataset_MUTimeRlt->FindByID(STT_MUTEST_MUTimeResult);

	if((pHasUsingTime == NULL)||(pMaxErrTime == NULL)||(pMinErrTime == NULL)
		||(pCurrErrTime == NULL)||(pAverageErrTime == NULL)||(pMUTimeResult == NULL))
		return FALSE;

	long nPpsIndex = CString_To_long(pPpsIndexData->m_strValue);
	double dHasUsingTime = nPpsIndex + 1;
	double dCurrErrTime = CString_To_double(pPpsValueData->m_strValue)/1000;
	pCurrErrTime->m_strValue.Format(_T("%.03lf"),dCurrErrTime);
	CString strTempValue,strCurrErrorValue;
	pHasUsingTime->m_strValue.Format("%.03lf",dHasUsingTime);

	if ((nPpsIndex<=0)||(pMaxErrTime->m_strValue == _T("0")))
	{
		pMaxErrTime->m_strValue = pCurrErrTime->m_strValue;
		pMinErrTime->m_strValue = pCurrErrTime->m_strValue;
		pAverageErrTime->m_strValue = pCurrErrTime->m_strValue;
	} 
	else
	{
		double dMaxValue = CString_To_double(pMaxErrTime->m_strValue);

		if (fabs(dMaxValue)<fabs(dCurrErrTime))
		{
			pMaxErrTime->m_strValue = pCurrErrTime->m_strValue;
		}

		double dMinValue = CString_To_double(pMinErrTime->m_strValue);

		if (fabs(dMinValue)>fabs(dCurrErrTime))
		{
			pMinErrTime->m_strValue = pCurrErrTime->m_strValue;
		}

		double dAverageValue = (CString_To_double(pAverageErrTime->m_strValue)*nPpsIndex + dCurrErrTime)/(nPpsIndex+1);
		pAverageErrTime->m_strValue.Format(_T("%.03lf"),dAverageValue);
//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("[UpdateMUTimeRlt]dMaxValue=%lf;dMinValue=%lf;"),dMaxValue,dMinValue);
	}

	return TRUE;
}


// 更新角差的值 2020-9-17 mayangming add 
// void CX61850CapBase::UpdatePhaseValue(double * pValue,  int nChnelCnt)
// {
// 	if (m_pDataset_MUTestCB == NULL)
// 		return;
// 
// 	double dCompValue[256] = {0};
// 	if (nChnelCnt  > 256)
// 		nChnelCnt = 256;
// 	for (int i = 0; i < nChnelCnt;  i++)
// 		dCompValue[i]  = *(pValue + i);
// 
// 	POS pos = m_pDataset_MUTestCB->GetHeadPosition();
// 
// 	int nIndex = 0;
// 
// 	CDvmData *pDstData = NULL;
// 	CDvmValue * pDvmValue = NULL;
// 
// 	int nChnelIndex = 0;
// 
// 	while (pos != NULL)
// 	{
// 		//当通道数量够了后直接跳出来；
// 		if (nChnelIndex  > nChnelCnt)
// 			break;
// 
// 		pDstData  =  (CDvmData *)m_pDataset_MUTestCB->GetNext(pos);
// 
// 		if (pDstData->m_strID.Find("DelayTRtg") != -1)//20220817 zhouhj 传入的pValue中不包含延时通道
// 		{
// 			continue;
// 		}
// 
// 		POS posIn = pDstData->GetHeadPosition();
// 		while(posIn != NULL)
// 		{
// 			pDvmValue  =  (CDvmValue *)pDstData->GetNext(posIn);
// 
// 			//相位更新；
// 			if(pDvmValue->m_strID.Find("$ang") > 0)
// 				pDvmValue->m_strValue.Format(_T("%.6f"),   dCompValue[nChnelIndex]);
// 		}
// 
// 		nChnelIndex++;
// 	}
// }

void CX61850CapBase::UpdateValue_MUTest(double * pValue,  int nChnelCnt,CString strID)
{
	if (m_pDataset_MUTestCB == NULL)
		return;

	double dCompValue[256] = {0};
	if (nChnelCnt  > 256)
		nChnelCnt = 256;
	for (int i = 0; i < nChnelCnt;  i++)
		dCompValue[i]  = *(pValue + i);

	POS pos = m_pDataset_MUTestCB->GetHeadPosition();

	int nIndex = 0;

	CDvmData *pDstData = NULL;
	CDvmValue * pDvmValue = NULL;

	int nChnelIndex = 0;

	while (pos != NULL)
	{
		//当通道数量够了后直接跳出来；
		if (nChnelIndex  > nChnelCnt)
			break;

		pDstData  =  (CDvmData *)m_pDataset_MUTestCB->GetNext(pos);

		if (pDstData->m_strID.Find("DelayTRtg") != -1)//20220817 zhouhj 传入的pValue中不包含延时通道
		{
			continue;
		}

		POS posIn = pDstData->GetHeadPosition();
		while(posIn != NULL)
		{
			pDvmValue  =  (CDvmValue *)pDstData->GetNext(posIn);

			//相位更新；
			if(pDvmValue->m_strID.Find(strID) > 0)
				pDvmValue->m_strValue.Format(_T("%.06f"),   dCompValue[nChnelIndex]);
		}

		nChnelIndex++;
	}
}

void CX61850CapBase::UpdateVlaue_HarmBase(CString strID)
{
	if (m_pDataset_MUTestCB == NULL)
		return;
	POS pos = m_pDataset_MUTestCB->GetHeadPosition();

	CDvmData *pDstData = NULL;
	CDvmValue * pDvmValue = NULL;


	while (pos != NULL)
	{

		pDstData  =  (CDvmData *)m_pDataset_MUTestCB->GetNext(pos);

		if (pDstData->m_strID.Find("DelayTRtg") != -1)
		{
			continue;
		}

		double fOutputValue = 0.0 ,fErrorValue = 0.0,fBaseValue = 0.0;

		POS posIn = pDstData->GetHeadPosition();
		while(posIn != NULL)
		{
			pDvmValue  =  (CDvmValue *)pDstData->GetNext(posIn);

			if(pDvmValue->m_strID.Find(strID) > 0)
			{
				fBaseValue = CString_To_double(pDvmValue->m_strValue);
				CDvmData *pBaseDvmData = NULL;
				if (((pDstData->m_strDataType == _T("Curr")) || (pDstData->m_strDataType == _T("电流"))) && (pDstData->m_strID.Find(_T("Ia2"))) == -1)
				{
					pBaseDvmData = (CDvmData*)m_pDataset_RcdStep6U6I->FindByID(_T("INom"));
				}
				else if (((pDstData->m_strDataType == _T("Curr")) || (pDstData->m_strDataType == _T("电流"))) && (pDstData->m_strID.Find(_T("Ia2"))) != -1)
				{
					pBaseDvmData = (CDvmData*)m_pDataset_RcdStep6U6I->FindByID(_T("I0"));
				}
				else if (((pDstData->m_strDataType == _T("Vol")) || (pDstData->m_strDataType == _T("电压")))&& (pDstData->m_strID.Find(_T("Ua2"))) == -1)
				{
					pBaseDvmData = (CDvmData*)m_pDataset_RcdStep6U6I->FindByID(_T("VNom"));
				}
				else if (((pDstData->m_strDataType == _T("Vol")) || (pDstData->m_strDataType == _T("电压")))&& (pDstData->m_strID.Find(_T("Ua2"))) != -1)
				{
					pBaseDvmData = (CDvmData*)m_pDataset_RcdStep6U6I->FindByID(_T("U0"));
				}
				if (pBaseDvmData)
				{
					fOutputValue = CString_To_double(pBaseDvmData->m_strValue);
				}	

				UpdateDvmDeviceDatas_Analysis_HarmBase(pDvmValue,fBaseValue,fOutputValue,fErrorValue);
			}
				
		}
	}
	//ClearPara();
}



// 更新角差的值 2020-9-17 mayangming add 
void CX61850CapBase::UpdatePhaseDeltaValue(double * pValue,double * pAngleValue, int nChnelCnt)
{
	if (m_pDataset_MUTestCB == NULL)
		return;

	double dCompValue[256] = {0};
	double dAngleValue[256] = {0};

	if (nChnelCnt  > 256)
		nChnelCnt = 256;
	for (int i = 0; i < nChnelCnt;  i++)
	{
		dCompValue[i]  = *(pValue + i);
		dAngleValue[i]  = *(pAngleValue + i);
	}

	POS pos = m_pDataset_MUTestCB->GetHeadPosition();

	int nIndex = 0;

	CDvmData *pDstData = NULL;
	CDvmValue * pDvmValue = NULL;

	int nChnelIndex = 0;
	while (pos != NULL)
	{
		//当通道数量够了后直接跳出来；
		if (nChnelIndex  > nChnelCnt)
			break;

		pDstData  =  (CDvmData *)m_pDataset_MUTestCB->GetNext(pos);

		if (pDstData->m_strID.Find("DelayTRtg") != -1)//20220817 zhouhj 传入的pValue中不包含延时通道
		{
			continue;
		}

		float fPhase = 0;

		POS posIn = pDstData->GetHeadPosition();
		while(posIn != NULL)
		{
			pDvmValue  =  (CDvmValue *)pDstData->GetNext(posIn);

			if(pDvmValue->m_strID.Find("$ang") > 0)
			{
				fPhase = CString_To_double(pDvmValue->m_strValue);
			}
			//更新角差；
			if(pDvmValue->m_strID.Find(STT_RcdInit_DL_AngError/*"$AngError"*/) > 0)
			{
				if (m_bIsFT3ADMU)
				{	
					SetErrorStatisValues_ADMU(pDvmValue,dAngleValue[nChnelIndex],dCompValue[nChnelIndex],MUAccuracy_ErrorType_AngError ,pDstData->m_nIndex,pDstData->m_strDataType);
				}
				else
				{
				SetErrorStatisValues_MU(pDvmValue,dCompValue[nChnelIndex],MUAccuracy_ErrorType_AngError ,pDstData->m_nIndex,pDstData->m_strDataType);
				}

				//pDvmValue->m_strValue.Format(_T("%.6f"),   dCompValue[nChnelIndex]);
			}
			else  if(pDvmValue->m_strID.Find("$h13") > 0)//abs (m_fPhase) / 4.5 * 250.0
				pDvmValue->m_strValue.Format(_T("%.6f"),  dCompValue[nChnelIndex]/1.08 /*/ 4.5 * 250*/);			
		}
		nChnelIndex++;
	}
}

// GS同步差 2020-6-29 mayangming add 
void CX61850CapBase::UpdateDvmDeviceDatas_Analysis_GSSync()
{
	if (! g_oCapAnalysisConfig.m_bGsAnalysis)
	{
		return;
	}

	if (m_pDataset_GSSyncDelt == NULL)
	{
		return;
	}

	POS pos = m_oCapDeviceAll.GetHeadPosition();
	CCapDeviceBase *pCapDevice = NULL;
	long nGsIndex = 0;
	CDvmData * pDataGS   = NULL;

	CString strSVCstcID;
	while (pos != NULL)
	{
		pCapDevice = (CCapDeviceBase*)m_oCapDeviceAll.GetNext(pos);
		if (pCapDevice->GetClassID() == CPDCLASSID_DEVICEGOOSE)
		{
			CCapDeviceGoose *pDeviceGoose  =  (CCapDeviceGoose *)pCapDevice;

			if (nGsIndex==0)
			{
				strSVCstcID  = _T("GOOSE2_GOOSE1");
				pDataGS    =    (CDvmData *)m_pDataset_GSSyncDelt->FindByID(strSVCstcID);
				if (pDataGS != NULL)				
					Analysis_Add_Data(m_pDataset_GSSyncDelt,   strSVCstcID,  pDeviceGoose->m_dGOOSESyn);				
			}
			else if (nGsIndex==1)
			{
				strSVCstcID  = _T("GOOSE3_GOOSE1");
				pDataGS    =    (CDvmData *)m_pDataset_GSSyncDelt->FindByID(strSVCstcID);
				if (pDataGS != NULL)				
					Analysis_Add_Data(m_pDataset_GSSyncDelt,   strSVCstcID,  pDeviceGoose->m_dGOOSESyn);				
			}
			nGsIndex++;
		}
	}

	return;

	// 1 :变位后得第一帧 ST+1,SQNO 清零；这时候的时标；
	//2：两帧的情况；

	//测试仪，at02同步，整秒测试仪变位，你抓变位后的
	//第一帧报文 把时间给自动测试

	//goose同步性，两个光口，发两个控制块，同时变位置，
	//你把变位后第一帧的两个控制块的时间给自动测试

	int nGsCnt = 0;
	nGsCnt  = nGsIndex;
	nGsIndex = 0;
	pos = m_oCapDeviceAll.GetHeadPosition();
	pDataGS    = NULL;
	while (pos != NULL)
	{
		pCapDevice = (CCapDeviceBase*)m_oCapDeviceAll.GetNext(pos);

		if (pCapDevice->GetClassID() == CPDCLASSID_DEVICEGOOSE)
		{
			strSVCstcID  = _T("GOOSE2_GOOSE1");

			pDataGS    =    (CDvmData *)m_pDataset_GSSyncDelt->FindByID(strSVCstcID);

			if (pDataGS != NULL)
			{
				//Analysis_Add_Data(m_pDataset_GSSyncDelt,   strSVCstcID,  dPhase[1] - dPhase[0]);
			}

			strSVCstcID  = _T("GOOSE3_GOOSE1");
			pDataGS    =    (CDvmData *)m_pDataset_GSSyncDelt->FindByID(strSVCstcID);
			if (pDataGS != NULL)
			{
				//Analysis_Add_Data(m_pDataset_GSSyncDelt,   strSVCstcID,  dPhase[2] - dPhase[0]);
			}
			nGsIndex++;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
void CX61850CapBase::IecAnalysis_AddDatasets()
{
	CDvmLogicDevice *pLDevice = GetLogicalDevice(TRUE);
	IecAnalysis_AddDatasets(pLDevice);
	MUTimeTestRlt_AddDataset();
	MUCurrErrorRange_AddDataset();
	MUErrorRanges_AddDataset();
	StateValueChangedRlt_AddDataset();
	TestFunSelect_AddDataset();
}

CDvmDataset* CX61850CapBase::AddDataset_dsRcdStep6U6I()
{
	CDvmLogicDevice *pLogicDevice = GetLogicalDevice(TRUE);
	CDvmDataset *pDsRcdStep6U6I = (CDvmDataset*)pLogicDevice->FindByID(CAP_DATASET_MAP_ID_RcdStep6U6I);
	CString strValue;

	if (pDsRcdStep6U6I != NULL)
	{
		CDvmData *pIsFirstCWTest = (CDvmData*)pDsRcdStep6U6I->FindByID(X61850_CapID_IsFirstCWTest);

		if (pIsFirstCWTest == NULL)
		{
			strValue.Format(_T("%ld"),g_nIsFirstCWTest);
			pDsRcdStep6U6I->AddNewData(X61850_CapID_IsFirstCWTest,X61850_CapID_IsFirstCWTest,
				"long",strValue);
		}

		return pDsRcdStep6U6I;
	}

	pDsRcdStep6U6I = new CDvmDataset();
	pDsRcdStep6U6I->m_strID = CAP_DATASET_MAP_ID_RcdStep6U6I;
	pLogicDevice->AddNewChild(pDsRcdStep6U6I);

	CString strPath;
	strPath = _P_GetConfigPath();
	strPath.AppendFormat("%s.xml",CAP_DATASET_MAP_ID_RcdStep6U6I);

	if (!IsFileExist(strPath))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("缺少配置文件(%s)."),strPath.GetString());
		return pDsRcdStep6U6I;
	}	
	
	pDsRcdStep6U6I->OpenXmlFile(strPath,CDataMngrXmlRWKeys::g_pXmlKeys);
	CDvmData *pIsFirstCWTest = (CDvmData*)pDsRcdStep6U6I->FindByID(X61850_CapID_IsFirstCWTest);

	if (pIsFirstCWTest == NULL)
	{
		strValue.Format(_T("%ld"),g_nIsFirstCWTest);
		pDsRcdStep6U6I->AddNewData(X61850_CapID_IsFirstCWTest,X61850_CapID_IsFirstCWTest,
			"long",strValue);
	}

	return pDsRcdStep6U6I;

}

void CX61850CapBase::IecAnalysis_AddDatasets(CDvmLogicDevice *pLogicDevice)
{
	POS pos = pLogicDevice->GetHeadPosition();
	CDvmDataset *pDataset = NULL;

	while (pos != NULL)
	{
		pDataset = (CDvmDataset *)pLogicDevice->GetNext(pos);

		if (Is_SvDataSetID(pDataset->m_strID))
		{
			IecAnalysis_AddDataset_SV(pLogicDevice, pDataset);
		}
		else if (Is_GsDataSetID(pDataset->m_strID))
		{
			IecAnalysis_AddDataset_GS(pLogicDevice, pDataset);
		}
	}
}

void CX61850CapBase::IecAnalysis_UpdateSvDatasetsPowerVector()
{
	CDvmLogicDevice *pLogicDevice = GetLogicalDevice(FALSE);

	if (pLogicDevice == NULL)
	{
		return;
	}

	CDvmDataset *pDataset = NULL;
	POS pos = pLogicDevice->GetHeadPosition();

	while (pos != NULL)
	{
		pDataset = (CDvmDataset *)pLogicDevice->GetNext(pos);

		if (Is_SvDataSetID(pDataset->m_strID))
		{
			CXIecDatasetSmartMatch oIecDatasetMatch;
			oIecDatasetMatch.AttachKeyDB(m_pKeyDB);
			oIecDatasetMatch.IecDatasetSmartMatch(pDataset);
			IecAnalysis_AddDataset_SV_Power(pLogicDevice, pDataset, oIecDatasetMatch,TRUE);
			IecAnalysis_AddDataset_SV_Vector(pLogicDevice, pDataset, oIecDatasetMatch,TRUE);
		}
	}
}

void CX61850CapBase::IecAnalysis_AddDataset_SV(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsSv)
{
	CXIecDatasetSmartMatch oIecDatasetMatch;
	oIecDatasetMatch.AttachKeyDB(m_pKeyDB);
	oIecDatasetMatch.IecDatasetSmartMatch(pDsSv);

	CString strFile = _P_GetLibraryPath();
	strFile = strFile + pDsSv->m_strID + _T(".xml");
	oIecDatasetMatch.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

	IecAnalysis_AddDataset_SV_Power(pLogicDevice, pDsSv, oIecDatasetMatch);
	IecAnalysis_AddDataset_SV_Vector(pLogicDevice, pDsSv, oIecDatasetMatch);
	IecAnalysis_AddDataset_SV_AD(pLogicDevice, pDsSv);

	//2022-5-25  lijunqing 报文分析：一致性
	IecAnalysis_AddDataset_SV_PkgAnalyze(pLogicDevice, pDsSv);

	//2022-5-28  lijunqing 异常分析
	IecAnalysis_AddDataset_SV_PkgError(pLogicDevice, pDsSv);

	//20220820 zhouhj 添加SV延时
	IecAnalysis_AddDataset_SV_Delay(pLogicDevice, pDsSv);

	IecAnalysis_AddDataset_SV_His(pLogicDevice, pDsSv);
}

/*
<dataset name="0X4012_功率" id="dsSV1$Power" data-type="" write-mode="0" index="0">
	<data name="功率1" id="P1" data-type="struct" value="">
		<value name="A相功率" id="P1$A" data-type="int" value="">
			<value name="电压" id="P1$A$U" data-type="string" value="电压A相1">
				<value name="有效值" id="P1$A$U$mag" data-type="float" value="57.735"/>
				<value name="相位" id="P1$A$U$ang" data-type="float" value="0"/>
			</value>
			<value name="电流" id="P1$A$I" data-type="string" value="保护电流A相1">
				<value name="有效值" id="P1$A$I$mag" data-type="float" value="5.001"/>
				<value name="相位" id="P1$A$I$ang" data-type="float" value="0"/>
			</value>
			<value name="有功" id="P1$A$P" data-type="float" value="0"/>
			<value name="无功" id="P1$A$Q" data-type="float" value="0"/>
			<value name="视在功率" id="P1$A$S" data-type="float" value="0"/>
			<value name="功率因子" id="P1$A$coef" data-type="float" value="0"/>
		</value>
		<value name="B相功率" id="P1$B" data-type="int" value="">
			........................
		</value>
		<value name="C相功率" id="P1$C" data-type="int" value="">
			........................
		</value>
		<value name="三相功率" id="P1$ABC" data-type="int" value="">
		<value name="有功" id="P1$ABC$P" data-type="float" value="0"/>
		<value name="无功" id="P1$ABC$Q" data-type="float" value="0"/>
		<value name="视在功率" id="P1$ABC$S" data-type="float" value="0"/>
		<value name="功率因子" id="P1$ABC$coef" data-type="float" value="0"/>
		</value>
	</data>
</dataset>
*/
void CX61850CapBase::IecAnalysis_AddDataset_SV_Power(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsSv, 
													 CXIecDatasetSmartMatch &oIecDatasetMatch,BOOL bUpdateDatas)
{
	CString strID;
	strID.Format(_T("%s$%s"), pDsSv->m_strID.GetString(), CAP_DATASET_MAP_ID_Power);

	CDvmDataset *pDsPower = (CDvmDataset*)pLogicDevice->FindByID(strID);

	if (pDsPower == NULL)
	{
		pDsPower = new CDvmDataset();
		pLogicDevice->AddNewChild(pDsPower);
	}
	else if (!bUpdateDatas)
	{
		return;
	}

	pDsPower->DeleteAll();
	pDsPower->m_strID = strID;
	pDsPower->m_strName = pDsSv->m_strName;
	pDsPower->m_strName.AppendFormat(_T("$%s"), CAP_DATASET_MAP_ID_Power);
	long nIndex = 1;

	CDataGroup *pGroup_UI_ABC_List = oIecDatasetMatch.Group_UI_ABC_List();
	CXIecDs_Group_UI_ABC *pUI_ABC = NULL;
	POS pos = pGroup_UI_ABC_List->GetHeadPosition();
	CDvmData *pDataPower = NULL;

	while (pos != NULL)
	{
		pUI_ABC = (CXIecDs_Group_UI_ABC *)pGroup_UI_ABC_List->GetNext(pos);
		pDataPower = new CDvmData();
		pDataPower->m_strID.Format(_T("P%d"), nIndex);
		pDsPower->AddNewChild(pDataPower);
		IecAnalysis_AddDataset_SV_Power_P(pDataPower, pUI_ABC);
		nIndex++;
	}
}

void CX61850CapBase::IecAnalysis_AddDataset_SV_Power_P(CDvmData *pDataPower, CXIecDs_Group_UI_ABC *pUI_ABC)
{
	IecAnalysis_AddDataset_SV_Power_P_Ch(pDataPower, pUI_ABC->m_pUI_A, _T("A"));
	IecAnalysis_AddDataset_SV_Power_P_Ch(pDataPower, pUI_ABC->m_pUI_B, _T("B"));
	IecAnalysis_AddDataset_SV_Power_P_Ch(pDataPower, pUI_ABC->m_pUI_C, _T("C"));

	pDataPower->AddValue(_T("P"), pDataPower->m_strID + _T("$P"), _T("float"), _T("0"));   //有功
	pDataPower->AddValue(_T("Q"), pDataPower->m_strID + _T("$Q"), _T("float"), _T("0")); //无功
	pDataPower->AddValue(_T("S"), pDataPower->m_strID + _T("$S"), _T("float"), _T("0"));  //视在功率
	pDataPower->AddValue(_T("coef"), pDataPower->m_strID + _T("$coef"), _T("float"), _T("0"));  //功率因子
}

/*
<value name="A相功率" id="P1$A" data-type="int" value="">
	<value name="电压" id="P1$A$U" data-type="string" value="电压A相1">
		<value name="有效值" id="P1$A$U$mag" data-type="float" value="57.735"/>
		<value name="相位" id="P1$A$U$ang" data-type="float" value="0"/>
	</value>
	<value name="电流" id="P1$A$I" data-type="string" value="保护电流A相1">
		<value name="有效值" id="P1$A$I$mag" data-type="float" value="5.001"/>
		<value name="相位" id="P1$A$I$ang" data-type="float" value="0"/>
	</value>
	<value name="有功" id="P1$A$P" data-type="float" value="0"/>
	<value name="无功" id="P1$A$Q" data-type="float" value="0"/>
	<value name="视在功率" id="P1$A$S" data-type="float" value="0"/>
	<value name="功率因子" id="P1$A$coef" data-type="float" value="0"/>
</value>
*/
void CX61850CapBase::IecAnalysis_AddDataset_SV_Power_P_Ch(CDvmData *pDataPower, CXIecDs_Group_UI *pUI, const CString &strIdPh)
{
	CString strID;
	CDvmValue *pVal = NULL;
	CDvmData *pData = NULL;

	//<value name="A相功率" id="P1$A" data-type="int" value="">
	pVal = new CDvmValue();
	pVal->m_strID.Format(_T("%s$%s"), pDataPower->m_strID.GetString(), strIdPh.GetString());
	pVal->m_strName = strIdPh;
	pDataPower->AddNewChild(pVal);
	
	//U
	pData = iec_match_get_dvmdata(pUI->m_pU);
	IecAnalysis_AddDataset_SV_X_NewCh(pData, pVal, _T("U"));

	//I
	pData = iec_match_get_dvmdata(pUI->m_pI);
	IecAnalysis_AddDataset_SV_X_NewCh(pData, pVal, _T("I"));

	pVal->AddValue(_T("P"), pVal->m_strID + _T("$P"), _T("float"), _T("0"));
	pVal->AddValue(_T("Q"), pVal->m_strID + _T("$Q"), _T("float"), _T("0"));
	pVal->AddValue(_T("S"), pVal->m_strID + _T("$S"), _T("float"), _T("0"));
	pVal->AddValue(_T("coef"), pVal->m_strID + _T("$coef"), _T("float"), _T("0"));
}

void CX61850CapBase::IecAnalysis_AddDataset_SV_Vector(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsSv
													  , CXIecDatasetSmartMatch &oIecDatasetMatch,BOOL bUpdateDatas)
{
	CString strID;
	strID.Format(_T("%s$%s"), pDsSv->m_strID.GetString(), CAP_DATASET_MAP_ID_Vector);

	CDvmDataset *pDsVector = (CDvmDataset*)pLogicDevice->FindByID(strID);

	if (pDsVector == NULL)
	{
		pDsVector = new CDvmDataset();
		pLogicDevice->AddNewChild(pDsVector);
	}
	else if (!bUpdateDatas)
	{
		return;
	}

	pDsVector->DeleteAll();
	pDsVector->m_strID = strID;
	pDsVector->m_strName = pDsSv->m_strName; 
	pDsVector->m_strName.AppendFormat(_T("$%s"), CAP_DATASET_MAP_ID_Vector);

	//电压
	IecAnalysis_AddDataset_SV_Vector_ABC_X_List(pLogicDevice, pDsVector, oIecDatasetMatch.Group_ABC_U_List(), _T("U"));

	//电流
	IecAnalysis_AddDataset_SV_Vector_ABC_X_List(pLogicDevice, pDsVector, oIecDatasetMatch.Group_ABC_I_List(), _T("I"));
}

void CX61850CapBase::IecAnalysis_AddDataset_SV_Vector_ABC_X_List(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsVector, CDataGroup *pGroup_ABC_U_List, const CString &strType)
{
	CXIecDs_Group_ABC *p = NULL;
	POS pos = pGroup_ABC_U_List->GetHeadPosition();

	while (pos != NULL)
	{
		p = (CXIecDs_Group_ABC *)pGroup_ABC_U_List->GetNext(pos);
		IecAnalysis_AddDataset_SV_Vector_ABC_X(pLogicDevice, pDsVector, p, strType);
	}
}

void CX61850CapBase::IecAnalysis_AddDataset_SV_Vector_ABC_X(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsVector
															, CXIecDs_Group_ABC *pABC_X, const CString &strType)
{
	long nIndex = pDsVector->GetCount() + 1;
	CDvmData *pVector = new CDvmData();
	pVector->m_strID.Format(_T("%s%d"), CAP_DATASET_MAP_ID_Vector, nIndex);
	pVector->m_strName = pVector->m_strID;
	pVector->m_strDataType = strType;
	pVector->m_strValue.Format(_T("%d"), pABC_X->m_nRelationIndex);
	pDsVector->AddNewChild(pVector);
	CDvmData *pCh = NULL;

	//A
	pCh = iec_match_get_dvmdata(pABC_X->m_pA);
	IecAnalysis_AddDataset_SV_X_NewCh(pCh, pVector, _T("A"));

	//B
	pCh = iec_match_get_dvmdata(pABC_X->m_pB);
	IecAnalysis_AddDataset_SV_X_NewCh(pCh, pVector, _T("B"));

	//C
	pCh = iec_match_get_dvmdata(pABC_X->m_pC);
	IecAnalysis_AddDataset_SV_X_NewCh(pCh, pVector, _T("C"));

	//Positive sequence Negative sequence Zero sequence
	IecAnalysis_AddDataset_SV_X_NewCh(pVector, _T("Positive"));
	IecAnalysis_AddDataset_SV_X_NewCh(pVector, _T("Negative"));
	IecAnalysis_AddDataset_SV_X_NewCh(pVector, _T("Zero"));
// 	pVector->AddValue(_T("Positive"), pVector->m_strID + _T("$Positive"), _T("float"), _T("0"));
// 	pVector->AddValue(_T("Negative"), pVector->m_strID + _T("$Negative"), _T("float"), _T("0"));
// 	pVector->AddValue(_T("Zero"), pVector->m_strID + _T("$Zero"), _T("float"), _T("0"));
}

void CX61850CapBase::IecAnalysis_AddDataset_SV_AD(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsSv)
{
	POS pos = pDsSv->GetHeadPosition();
	CDvmData *pData1 = NULL;
	CDvmData *pData2 = NULL;
	CString strID;
	strID.Format(_T("%s$%s"), pDsSv->m_strID.GetString(), CAP_DATASET_MAP_ID_AD);

	CDvmDataset *pDsAD = (CDvmDataset*)pLogicDevice->FindByID(strID);

	if (pDsAD != NULL)
	{
		return;
	}

	pDsAD = new CDvmDataset();
	pDsAD->m_strID = strID;
	pDsAD->m_strName = pDsSv->m_strName;
	pDsAD->m_strName.AppendFormat(_T("$%s"),CAP_DATASET_MAP_ID_AD);
	pLogicDevice->AddNewChild(pDsAD);
	long nIndex = 1;

	while (pos != NULL)
	{
		pData1 = (CDvmData *)pDsSv->GetNext(pos);

		if (pData1->m_dwReserved == 1)
		{
			continue;
		}

		pData2 = IecAnalysis_AddDataset_SV_AD_Find(pDsSv, pData1);

		if (pData2 == NULL)
		{
			continue;
		}

		IecAnalysis_AddDataset_SV_AD_Add(pDsAD, pData1, pData2, nIndex);
		nIndex++;
	}
}

CDvmData* CX61850CapBase::IecAnalysis_AddDataset_SV_AD_Find(CDvmDataset *pDsSv, CDvmData *pData1)
{
	POS pos = pDsSv->GetHeadPosition();
	CDvmData *pData2 = NULL;
	CDvmData *pDataFind = NULL;

	while (pos != NULL)
	{
		pData2 = (CDvmData *)pDsSv->GetNext(pos);

		if (pData1 == pData2)
		{
			continue;
		}

		if (pData2->m_dwReserved == 1)
		{
			continue;
		}

		long nLen1 = pData2->m_strName.GetLength();
		long nLen2 = pData1->m_strName.GetLength();

		if (nLen1 != nLen2)
		{
			continue;
		}

		//默认只有最后一个字符不一样，例如：第一组保护电流A相-保护电流A相1 + 第一组保护电流A相-保护电流A相2
		CString strName1, strName2;
		strName1 = pData1->m_strName.Left(nLen1 -1);
		strName2 = pData2->m_strName.Left(nLen2 - 1);

		if (strName1 == strName2)
		{
			pDataFind = pData2;
			pData1->m_dwReserved = 1;
			pData2->m_dwReserved = 1;
			break;
		}
	}

	return pDataFind;
}

/*
<data name="第一组保护电流A相-保护电流A相" id="AD1" value="">
	<value name="ch1" id="AD1$ch1" data-type="struct" value="第一组保护电流A相-保护电流A相1">
		<value name="幅值" id="SV1_I2_Ia1$mag" data-type="FLOAT" value="0.00"/>
		<value name="相位" id="SV1_I2_Ia1$ang" data-type="FLOAT" value="0.00"/>
		<value name="频率" id="SV1_I2_Ia1$freq" data-type="FLOAT" value="50.00"/>
	</value>
	<value name="ch2" id="AD1$ch2" data-type="struct" value="第一组保护电流A相-保护电流A相2">
		<value name="幅值" id="SV1_I2_Ia1$mag" data-type="FLOAT" value="0.00"/>
		<value name="相位" id="SV1_I2_Ia1$ang" data-type="FLOAT" value="0.00"/>
		<value name="频率" id="SV1_I2_Ia1$freq" data-type="FLOAT" value="50.00"/>
	</value>
	<value name="幅值差AD1-AD2" id="AD1$dmag" data-type="FLOAT" value="0.00"/>
	<value name="幅值差|AD1-AD2|" id="AD1$dmag_abs" data-type="FLOAT" value="0.00"/>
	<value name="相位差AD1-AD2" id="AD1$dang" data-type="FLOAT" value="0"/>
	<value name="相位差|AD1-AD2|" id="AD1$dang_abs" data-type="FLOAT" value="0"/>
</data>
*/
void CX61850CapBase::IecAnalysis_AddDataset_SV_AD_Add(CDvmDataset *pDsAD, CDvmData *pData1, CDvmData *pData2, long nIndex)
{
	CDvmData *pDataAD = new CDvmData();
	pDataAD->m_strName = pData1->m_strName;
	pDataAD->m_strID.Format(_T("%s%d"), CAP_DATASET_MAP_ID_AD, nIndex);
	pDsAD->AddNewChild(pDataAD);
	
	IecAnalysis_AddDataset_SV_X_NewCh(pData1, pDataAD, 1);
	IecAnalysis_AddDataset_SV_X_NewCh(pData2, pDataAD, 2);
	
	IecAnalysis_AddDataset_SV_AD_NewVal(pDataAD, _T("幅值差AD1-AD2"), CAP_DATASET_MAP_ID_AD_DMAG);
	IecAnalysis_AddDataset_SV_AD_NewVal(pDataAD, _T("幅值差|AD1-AD2|"), CAP_DATASET_MAP_ID_AD_DMAG_ABS);
	IecAnalysis_AddDataset_SV_AD_NewVal(pDataAD, _T("相位差AD1-AD2"), CAP_DATASET_MAP_ID_AD_DANG);
	IecAnalysis_AddDataset_SV_AD_NewVal(pDataAD, _T("相位差|AD1-AD2|"), CAP_DATASET_MAP_ID_AD_DANG_ABS);
}

void CX61850CapBase::IecAnalysis_AddDataset_SV_AD_NewVal(CDvmData *pDataAD, const CString &strName, const CString &strID)
{
	CDvmValue *pVal = new CDvmValue();
	pVal->m_strName = strName;
	pVal->m_strID.Format(_T("%s$%s"), pDataAD->m_strID.GetString(), strID.GetString());
	pVal->m_strDataType = _T("FLOAT");
	pDataAD->AddNewChild(pVal);
}

CDvmValue* CX61850CapBase::IecAnalysis_AddDataset_SV_X_NewCh(CDvmData *pSrcData, CExBaseList *pParent, long nIndex)
{
	CString strID;
	strID.Format(_T("Ch%d"), nIndex);
	
	return IecAnalysis_AddDataset_SV_X_NewCh(pSrcData, pParent, strID);
// 	CDvmValue *pCh = new CDvmValue();
// 	pCh->m_strName.Format(_T("Ch%d"), nIndex);
// 	pCh->m_strID.Format(_T("%s$Ch%d"), pParent->m_strID, nIndex);
// 	pCh->m_strValue = pSrcData->m_strName;
// 	pParent->AddNewChild(pCh);
// 
// 	IecAnalysis_AddDataset_SV_X_NewCh_Attr(pSrcData, pCh, _T("$mag"));
// 	IecAnalysis_AddDataset_SV_X_NewCh_Attr(pSrcData, pCh, _T("$ang"));
// 	IecAnalysis_AddDataset_SV_X_NewCh_Attr(pSrcData, pCh, _T("$freq"));
// 
// 	return pCh;
}

CDvmValue* CX61850CapBase::IecAnalysis_AddDataset_SV_X_NewCh(CDvmData *pSrcData, CExBaseList *pParent, const CString &strID)
{
	CDvmValue *pCh = new CDvmValue();
	pCh->m_strName = strID;
	pCh->m_strID = pParent->m_strID + _T("$") + strID;
	CExBaseList *pSrcDataParent = (CExBaseList *)pSrcData->GetParent();

	if (pSrcDataParent != NULL)
	{
		long nIndex = pSrcDataParent->FindIndex(pSrcData);
// 		CString strChDesc;
// 		strChDesc = _T("通道");
		pCh->m_strValue = pSrcData->m_strName;
		pCh->m_strValue.AppendFormat(_T("[通道%ld]"),nIndex+1);
	} 
	else
	{
		pCh->m_strValue = pSrcData->m_strName;
	}

	pParent->AddNewChild(pCh);

	IecAnalysis_AddDataset_SV_X_NewCh_Attr(pSrcData, pCh, _T("$mag"));
	IecAnalysis_AddDataset_SV_X_NewCh_Attr(pSrcData, pCh, _T("$ang"));
	IecAnalysis_AddDataset_SV_X_NewCh_Attr(pSrcData, pCh, _T("$freq"));

	return pCh;
}

CDvmValue* CX61850CapBase::IecAnalysis_AddDataset_SV_X_NewCh(CExBaseList *pParent, const CString &strID)
{
	CDvmValue *pCh = new CDvmValue();
	pCh->m_strName = strID;
	pCh->m_strID = pParent->m_strID + _T("$") + strID;
	pCh->m_strValue = strID;
	pParent->AddNewChild(pCh);

	IecAnalysis_AddDataset_SV_X_NewCh_Attr(pCh, _T("$mag"));
	IecAnalysis_AddDataset_SV_X_NewCh_Attr(pCh, _T("$ang"));

	return pCh;
}

void CX61850CapBase::IecAnalysis_AddDataset_SV_X_NewCh_Attr(CDvmData *pSrcData, CDvmValue *pCh, const CString &strAttrID)
{
	CDvmValue *pAttr  = NULL;
	pAttr = pSrcData->FindValueByID(strAttrID);

	if (pAttr == NULL)
	{
		return;
	}

	CDvmValue *pNew = (CDvmValue*)pAttr->Clone();
	pNew->m_dwItemData = (DWORD)pAttr; //指向属性对象，方便计算的时候取值

	pCh->AddNewChild(pNew);
}

void CX61850CapBase::IecAnalysis_AddDataset_SV_X_NewCh_Attr(CDvmValue *pCh, const CString &strAttrID)
{
	CDvmValue *pNew  = new CDvmValue();
	pNew->m_strID = pCh->m_strID + strAttrID;
	pNew->m_strName = strAttrID;
	pNew->m_strDataType = _T("float");

	pCh->AddNewChild(pNew);
}

//2022-5-25  lijunqing
void CX61850CapBase::IecAnalysis_AddDataset_SV_PkgAnalyze(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsSv)
{
	CDvmData *pSvData = NULL;
	IecAnalysis_AddDataset_Ctrl_ForData(pLogicDevice, pDsSv, &m_pDataset_SV_PkgAnalyze, &pSvData
		, CAP_DATASET_MAP_ID_SVCSTC, _T("SttRcdSv_PkgAnalyze.xml"));

// 	CString strID = CAP_DATASET_MAP_ID_SVCSTC;
// 
// 	m_pDataset_SVCstcErr = (CDvmDataset*)pLogicDevice->FindByID(strID);
// 
// 	if (m_pDataset_SVCstcErr == NULL)
// 	{
// 		m_pDataset_SVCstcErr = new CDvmDataset();
// 		m_pDataset_SVCstcErr->m_strID = strID;
// 		m_pDataset_SVCstcErr->m_strName = strID;
// 		pLogicDevice->AddNewChild(m_pDataset_SVCstcErr);
// 	}
// 
// 	strID = pDsSv->m_strID.Mid(2);  //dsSV1 == >> SV1
// 	CDvmData *pSvData = (CDvmData *)m_pDataset_SVCstcErr->FindByID(strID);
// 
// 	if (pSvData == NULL)
// 	{
// 		pSvData = new CDvmData();
// 		m_pDataset_SVCstcErr->AddNewChild(pSvData);
// 	}
// 
// 	XSttRcdInitSv_PkgAnalyze(pSvData, strID);

	CCapDeviceBase *pCapDevice = m_oCapDeviceAll.FindCapDevice(pDsSv);

	if (pCapDevice == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("没有找到数据集对应的设备对象") + pDsSv->m_strID);
		return;
	}

	if (pCapDevice->GetIecCfgData() == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("设备对象没有关联的测试仪配置：") + pDsSv->m_strID);
		return;
	}

	if (pCapDevice->GetClassID() == CPDCLASSID_DEVICE92)
	{
		IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg(pSvData, pCapDevice->GetIecCfgData());
	}
}

void CX61850CapBase::IecAnalysis_AddDataset_SV_His(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsSv)
{
	CDvmDataset *pDsRet = (CDvmDataset*)pLogicDevice->FindByID(CAP_DATASET_MAP_ID_SVHis);

	if (pDsRet == NULL)
	{
		pDsRet = new CDvmDataset();
		pDsRet->m_strID = CAP_DATASET_MAP_ID_SVHis;
		pDsRet->m_strName = CAP_DATASET_MAP_ID_SVHis;
		pLogicDevice->AddNewChild(pDsRet);
	}

	CString strDataID;
	strDataID = pDsSv->m_strID.Mid(2);  //dsSV1 == >> SV1
	CDvmData *pDataRet = (CDvmData *)pDsRet->FindByID(strDataID);

	if (pDataRet == NULL)
	{
		pDataRet = new CDvmData();
		pDataRet->m_strName = strDataID;
		pDataRet->m_strID = strDataID;
		pDsRet->AddNewChild(pDataRet);
	}

	CString strValueID;
	strValueID = strDataID + STT_MUTEST_DL_RealDelay;
	CDvmValue *pCurrValue = (CDvmValue*)pDataRet->FindByID(strValueID);

	if (pCurrValue == NULL)
	{
		pCurrValue = new CDvmValue;
		pCurrValue->m_strName = _T("实测延时(μs)");
		pCurrValue->m_strID = strValueID;
		pDataRet->AddNewChild(pCurrValue);
	}
}

void CX61850CapBase::IecAnalysis_AddDataset_SV_Delay(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsSv)
{
	CDvmData *pSvData = NULL;
	IecAnalysis_AddDataset_Ctrl_ForData(pLogicDevice, pDsSv, &m_pDataset_SVDelay, &pSvData
		, CAP_DATASET_MAP_ID_SVDELAY, _T("SttRcdSv_SVDelay.xml"));

// 	CString strID;
// 	strID.Format(_T("%s$%s"), pDsSv->m_strID.GetString(), CAP_DATASET_MAP_ID_Power);
// 
// 	CDvmDataset *pDsPower = (CDvmDataset*)pLogicDevice->FindByID(strID);
// 
// 	if (pDsPower != NULL)
// 	{
// 		return;
// 	}
// 
// 	pDsPower = new CDvmDataset();
// 	pDsPower->m_strID = strID;
// 	pDsPower->m_strName.Format(_T("%s$%s"), pDsSv->m_strName.GetString(), CAP_DATASET_MAP_ID_Power);
// 	pLogicDevice->AddNewChild(pDsPower);
}

void IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(CDvmData *pSvData, char *pszValueID, unsigned long nValue)
{
	CString strValueID = pszValueID;
	strValueID = _T("$") + strValueID;
	CDvmValue *pValue = (CDvmValue *)pSvData->FindByID_MmsAttr(strValueID);

	if (pValue == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("[%s] not exist in [%s]"), strValueID.GetString(), pSvData->m_strID.GetString());
		return;
	}

	pValue->SetValue_Mms(_T("$stand"), nValue);
}


void IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(CDvmData *pSvData, char *pszValueID, long nValue)
{
	CString strValueID = pszValueID;
	strValueID = _T("$") + strValueID;
	CDvmValue *pValue = (CDvmValue *)pSvData->FindByID_MmsAttr(strValueID);

	if (pValue == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("[%s] not exist in [%s]"), strValueID.GetString(), pSvData->m_strID.GetString());
		return;
	}

	pValue->SetValue_Mms(_T("$stand"), nValue);
}


void IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(CDvmData *pSvData, char *pszValueID, const CString &strValue)
{
	CString strValueID = pszValueID;
	strValueID = _T("$") + strValueID;
	CDvmValue *pValue = (CDvmValue *)pSvData->FindByID_MmsAttr(strValueID);

	if (pValue == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("[%s] not exist in [%s]"), strValueID.GetString(), pSvData->m_strID.GetString());
		return;
	}

	pValue->SetValue_Mms(_T("$stand"), strValue);
}


//SV报文一致性测试：初始化IEC配置的数据
void CX61850CapBase::IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg(CDvmData *pSvData, CIecCfgDataBase *pIecCfgData)
{
// 	//2022-5-26  lijunqing
// #define IEC_PkgAnalyze_ID_TestPos			"TestPos"
// #define IEC_PkgAnalyze_ID_DevVersion		"DevVersion"
// #define IEC_PkgAnalyze_ID_PDUlength		"PDUlength"
// #define IEC_PkgAnalyze_ID_Channel			"Channel"
// #define IEC_PkgAnalyze_ID_VLAN_ID			"VLAN_ID"
// #define IEC_PkgAnalyze_ID_VLANPriority		"VLANPriority"
// #define IEC_PkgAnalyze_ID_SynState			"SynState"
// #define IEC_PkgAnalyze_ID_SampRate		"SampRate"
// #define IEC_PkgAnalyze_ID_ASDUNumber	"ASDUNumber"
// #define IEC_PkgAnalyze_ID_DstMAC			"DstMAC"
// #define IEC_PkgAnalyze_ID_SVID				"SVID"

	CIecCfg92Data *pCfgData92 = (CIecCfg92Data*)pIecCfgData;
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pSvData, IEC_PkgAnalyze_ID_DevVersion, pCfgData92->m_dwVersion);
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pSvData, IEC_PkgAnalyze_ID_Channel, pCfgData92->m_nChannelNum);
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pSvData, IEC_PkgAnalyze_ID_VLANPriority, pCfgData92->m_nPriority);
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pSvData, IEC_PkgAnalyze_ID_SynState, pCfgData92->m_nSyn);
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pSvData, IEC_PkgAnalyze_ID_SampRate, pCfgData92->m_nSampleRate);
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pSvData, IEC_PkgAnalyze_ID_ASDUNumber, pCfgData92->m_nAsduNum);
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pSvData, IEC_PkgAnalyze_ID_SVID, pCfgData92->m_strSVID);
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pSvData, IEC_PkgAnalyze_ID_DstMAC, pCfgData92->m_strDestAddress);
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pSvData, IEC_PkgAnalyze_ID_VLAN_ID, pCfgData92->m_dwVID);
}


//////////////////////////////////////////////////////////////////////////
//
//2022-5-28  lijunqing  分析功能，控制块作为数据集的data对象，记录具体分析功能
void CX61850CapBase::IecAnalysis_AddDataset_Ctrl_ForData(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsSv
														 , CDvmDataset **ppDsRet, CDvmData **ppDataRet
														, const CString &strDataSetID, const CString &strAnalyzeCfgFile)
{
	CString strID = strDataSetID;
	CDvmDataset *pDsRet = (CDvmDataset*)pLogicDevice->FindByID(strID);

	if (pDsRet == NULL)
	{
		pDsRet = new CDvmDataset();
		pDsRet->m_strID = strID;
		pDsRet->m_strName = strID;
		pLogicDevice->AddNewChild(pDsRet);
	}

	*ppDsRet = pDsRet;
	strID = pDsSv->m_strID.Mid(2);  //dsSV1 == >> SV1
	CDvmData *pDataRet = (CDvmData *)pDsRet->FindByID(strID);

	if (pDataRet == NULL)
	{
		pDataRet = new CDvmData();
		pDsRet->AddNewChild(pDataRet);
	}

	*ppDataRet = pDataRet;
	XSttRcdInitSv_FromCfgFile(pDataRet, strID, strAnalyzeCfgFile);
}

//////////////////////////////////////////////////////////////////////////
//
//2022-5-28  lijunqing 异常分析
void CX61850CapBase::IecAnalysis_AddDataset_SV_PkgError(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsSv)
{
	CDvmData *pSvData = NULL;
	IecAnalysis_AddDataset_Ctrl_ForData(pLogicDevice, pDsSv, &m_pDataset_SVErr, &pSvData
		, CAP_DATASET_MAP_ID_SVERR, _T("SttRcdSv_SVPkgError.xml"));
}

///////////////////////////////////////////////////////////////////////////
//
void CX61850CapBase::IecAnalysis_AddDataset_GS(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsGoose)
{
	IecAnalysis_AddDataset_GS_PkgAnalyze(pLogicDevice, pDsGoose);
	IecAnalysis_AddDataset_GS_PkgError(pLogicDevice, pDsGoose);
}

void CX61850CapBase::IecAnalysis_AddDataset_GS_PkgAnalyze(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsGoose)
{
	CDvmData *pGsData = NULL;
	IecAnalysis_AddDataset_Ctrl_ForData(pLogicDevice, pDsGoose, &m_pDataset_GS_PkgAnalyze, &pGsData
		, CAP_DATASET_MAP_ID_GOCSTC, _T("SttRcdGs_PkgAnalyze.xml"));

	CCapDeviceBase *pCapDevice = m_oCapDeviceAll.FindCapDevice(pDsGoose);

	if (pCapDevice == NULL)
	{
// 		CString strTmpFileName;
// 		strTmpFileName = _P_GetLibraryPath();
// 		QDateTime tmData = QDateTime::currentDateTime();
// 		CString strFileName = tmData.toString("yyyy_MM_dd_hh_mm_ss"); 
// 		strTmpFileName += strFileName;
// 		strTmpFileName += ".xml";
// 		pDsGoose->SaveXmlFile(strTmpFileName,CDataMngrXmlRWKeys::g_pXmlKeys);
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("没有找到数据集对应的设备对象") + pDsGoose->m_strID);
		return;
	}

	if (pCapDevice->GetIecCfgData() == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("设备对象没有关联的测试仪配置：") + pDsGoose->m_strID);
		return;
	}

	IecAnalysis_AddDataset_GS_PkgAnalyze_Iecfg_Gout(pGsData, pCapDevice->GetIecCfgData());
}

void CX61850CapBase::IecAnalysis_AddDataset_GS_PkgAnalyze_Iecfg_Gout(CDvmData *pGsData, CIecCfgDataBase *pIecCfgData)
{
/*
	Analysis_Add_Data(m_pDataset_GSCstcErr,   _T("Test"),  byFlagGSCstc[0]);
	Analysis_Add_Data(m_pDataset_GSCstcErr,   _T("DevVersion"), byFlagGSCstc[1]);
	Analysis_Add_Data(m_pDataset_GSCstcErr,   _T("PDUlength"),  byFlagGSCstc[2]);
	Analysis_Add_Data(m_pDataset_GSCstcErr,   _T("Channel"),  byFlagGSCstc[3]);
	Analysis_Add_Data(m_pDataset_GSCstcErr,   _T("VLAN_ID"),  byFlagGSCstc[4]);
	Analysis_Add_Data(m_pDataset_GSCstcErr,   _T("VLANPriority"),  byFlagGSCstc[5]);
	Analysis_Add_Data(m_pDataset_GSCstcErr,   _T("DstMAC"),  byFlagGSCstc[6]);
	Analysis_Add_Data(m_pDataset_GSCstcErr,   _T("ContrlRef"),  byFlagGSCstc[7]);
	Analysis_Add_Data(m_pDataset_GSCstcErr,   _T("GOOSEID"),  byFlagGSCstc[8]);
*/

	CIecCfgGinData *pCfgDataGin = (CIecCfgGinData*)pIecCfgData;
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pGsData, IEC_PkgAnalyze_ID_Test, pCfgDataGin->m_bTest);
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pGsData, IEC_PkgAnalyze_ID_DevVersion, pCfgDataGin->m_dwVersion);
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pGsData, IEC_PkgAnalyze_ID_Channel, pCfgDataGin->m_nChannelNum);
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pGsData, IEC_PkgAnalyze_ID_VLANPriority, pCfgDataGin->m_dwVLandPriority);
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pGsData, IEC_PkgAnalyze_ID_SynState, pCfgDataGin->m_nSyn);
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pGsData, IEC_PkgAnalyze_ID_ContrlRef, pCfgDataGin->m_strgocbRef);
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pGsData, IEC_PkgAnalyze_ID_GOOSEID, pCfgDataGin->m_strGooseId);
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pGsData, IEC_PkgAnalyze_ID_DstMAC, pCfgDataGin->m_strDestAddress);
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pGsData, IEC_PkgAnalyze_ID_VLAN_ID, pCfgDataGin->m_dwVLandID);
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pGsData, IEC_PkgAnalyze_ID_DataSet, pCfgDataGin->m_strDataSet);
	

}

void CX61850CapBase::IecAnalysis_AddDataset_GS_PkgAnalyze_Iecfg_Gin(CDvmData *pGsData, CIecCfgDataBase *pIecCfgData)
{
/*
	Analysis_Add_Data(m_pDataset_GSCstcErr,   _T("Test"),  byFlagGSCstc[0]);
	Analysis_Add_Data(m_pDataset_GSCstcErr,   _T("DevVersion"), byFlagGSCstc[1]);
	Analysis_Add_Data(m_pDataset_GSCstcErr,   _T("PDUlength"),  byFlagGSCstc[2]);
	Analysis_Add_Data(m_pDataset_GSCstcErr,   _T("Channel"),  byFlagGSCstc[3]);
	Analysis_Add_Data(m_pDataset_GSCstcErr,   _T("VLAN_ID"),  byFlagGSCstc[4]);
	Analysis_Add_Data(m_pDataset_GSCstcErr,   _T("VLANPriority"),  byFlagGSCstc[5]);
	Analysis_Add_Data(m_pDataset_GSCstcErr,   _T("DstMAC"),  byFlagGSCstc[6]);
	Analysis_Add_Data(m_pDataset_GSCstcErr,   _T("ContrlRef"),  byFlagGSCstc[7]);
	Analysis_Add_Data(m_pDataset_GSCstcErr,   _T("GOOSEID"),  byFlagGSCstc[8]);
*/

	CIecCfgGinData *pCfgDataGin = (CIecCfgGinData*)pIecCfgData;
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pGsData, IEC_PkgAnalyze_ID_Test, pCfgDataGin->m_bTest);
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pGsData, IEC_PkgAnalyze_ID_DevVersion, pCfgDataGin->m_dwVersion);
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pGsData, IEC_PkgAnalyze_ID_Channel, pCfgDataGin->m_nChannelNum);
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pGsData, IEC_PkgAnalyze_ID_VLANPriority, pCfgDataGin->m_dwVLandPriority);
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pGsData, IEC_PkgAnalyze_ID_SynState, pCfgDataGin->m_nSyn);
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pGsData, IEC_PkgAnalyze_ID_ContrlRef, pCfgDataGin->m_strgocbRef);
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pGsData, IEC_PkgAnalyze_ID_GOOSEID, pCfgDataGin->m_strGooseId);
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pGsData, IEC_PkgAnalyze_ID_DstMAC, pCfgDataGin->m_strDestAddress);
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pGsData, IEC_PkgAnalyze_ID_VLAN_ID, pCfgDataGin->m_dwVLandID);
	IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg_val(pGsData, IEC_PkgAnalyze_ID_DataSet, pCfgDataGin->m_strDataSet);

}


/*
<data name="0X0C01" id="Goose1" data-type="int" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step="">
	<value name="虚变位" id="DummyBit" data-type="int" value=""/>
	<value name="sqNum丢失" id="SQNumLoss" data-type="int" value=""/>
	<value name="sqNum初值错误" id="SQNumInitError" data-type="int" value=""/>
	<value name="sqNum错序" id="SQNumDisorder" data-type="int" value=""/>
	<value name="sqNum重复" id="SQNumRepeat" data-type="int" value=""/>
	<value name="stNum丢失" id="STNumLoss" data-type="int" value=""/>
	<value name="装置重启" id="DevRestart" data-type="int" value=""/>
	<value name="stNum错序" id="STNumDisorder" data-type="int" value=""/>
	<value name="APDU编码错" id="APDUCodeErr" data-type="int" value=""/>
	<value name="ASDU编码错" id="ASDUCodeErr" data-type="int" value=""/>
	<value name="长度参数错" id="LengthParaErr" data-type="int" value=""/>
	<value name="超时" id="TimeOut" data-type="int" value=""/>
	<value name="通信中断" id="CommLoss" data-type="int" value=""/>
	<value name="通讯恢复" id="CommRecover" data-type="int" value=""/>
	<value name="存活时间无效" id="LivingTimeInvalid" data-type="int" value=""/>
	<value name="时钟故障" id="ClockFault" data-type="int" value=""/>
	<value name="时钟未同步" id="ClockNotSyn" data-type="int" value=""/>
	<value name="非法GOOSE的次数和状态" id="Illegal" data-type="int" value=""/>
</data>
*/
void CX61850CapBase::IecAnalysis_AddDataset_GS_PkgError(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsGs)
{
	CDvmData *pGsData = NULL;
	IecAnalysis_AddDataset_Ctrl_ForData(pLogicDevice, pDsGs, &m_pDataset_GSErr, &pGsData
		, CAP_DATASET_MAP_ID_GSERR, _T("SttRcdGs_GSPkgError.xml"));
}

void CX61850CapBase::MUTimeTestRlt_AddDataset()
{
	CDvmLogicDevice *pLogicDevice = GetLogicalDevice(TRUE);

	CDvmDataset *pDataset = (CDvmDataset*)pLogicDevice->FindByID(CAP_DATASET_MAP_ID_dsMUTimeRlt);

	if (pDataset != NULL)
	{
		return;
	}

	pDataset = new CDvmDataset();
	pDataset->m_strName = CAP_DATASET_MAP_ID_dsMUTimeRlt;
	pDataset->m_strID = CAP_DATASET_MAP_ID_dsMUTimeRlt;
	pLogicDevice->AddNewChild(pDataset);
	CDvmData *pData = pDataset->AddNewData(_T("已测试时长"),STT_MUTEST_HasUsingTime,_T("long"),_T("0"));
	pData->m_nChange = 1;
	pData = pDataset->AddNewData(_T("最大误差时间"),STT_MUTEST_MaxErrTime,_T("float"),_T("0"));
	pData->m_nChange = 1;
	pData = pDataset->AddNewData(_T("最小误差时间"),STT_MUTEST_MinErrTime,_T("float"),_T("0"));
	pData->m_nChange = 1;
	pData = pDataset->AddNewData(_T("当前误差"),STT_MUTEST_CurrErrTime,_T("float"),_T("0"));
	pData->m_nChange = 1;
	pData = pDataset->AddNewData(_T("平均误差时间"),STT_MUTEST_AverageErrTime,_T("float"),_T("0"));
	pData->m_nChange = 1;
	pData = pDataset->AddNewData(_T("时间精度测试结果"),STT_MUTEST_MUTimeResult,_T("long"),_T("0"));
	pData->m_nChange = 1;
	m_pDataset_MUTimeRlt = pDataset;
}

void CX61850CapBase::MUErrorRanges_AddDataset()
{
	CDvmLogicDevice *pLogicDevice = GetLogicalDevice(TRUE);

	CDvmDataset *pDataset = (CDvmDataset*)pLogicDevice->FindByID(CAP_DATASET_MAP_ID_dsErrorRanges);

	if (pDataset != NULL)
	{
		return;
	}

	pDataset = new CDvmDataset();
	pDataset->m_strName = CAP_DATASET_MAP_ID_dsErrorRanges;
	pDataset->m_strID = CAP_DATASET_MAP_ID_dsErrorRanges;
	pLogicDevice->AddNewChild(pDataset);
	CString strFilePath;
	strFilePath = _P_GetConfigPath();
	strFilePath += _T("dsMUErrorRagnes.xml");

	if (IsFileExist(strFilePath))
	{
		pDataset->OpenXmlFile(strFilePath, CDataMngrXmlRWKeys::g_pXmlKeys);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("合并单元误差范围设置配置文件(%s)不存在."),strFilePath.GetString());
	}

	m_pDataset_ErrorRanges = pDataset;
}

void CX61850CapBase::MUCurrErrorRange_AddDataset()
{
	CDvmLogicDevice *pLogicDevice = GetLogicalDevice(TRUE);

	CDvmDataset *pDataset = (CDvmDataset*)pLogicDevice->FindByID(CAP_DATASET_MAP_ID_dsCurrErrorRange);

	if (pDataset != NULL)
	{
		return;
	}

	pDataset = new CDvmDataset();
	pDataset->m_strName = CAP_DATASET_MAP_ID_dsCurrErrorRange;
	pDataset->m_strID = CAP_DATASET_MAP_ID_dsCurrErrorRange;
	pLogicDevice->AddNewChild(pDataset);
	pDataset->AddNewData(_T("当前测试百分比"),_T("CurrTestRate"),_T("float"),_T("0.05"));
	pDataset->AddNewData(_T("额定电压"),_T("Unom"),_T("float"),_T("57.74"));
	pDataset->AddNewData(_T("额定电流"),_T("Inom"),_T("float"),_T("1"));
	MUCurrErrorRange_AddData(pDataset,_T("电压-保护级(3P)"),_T("Vol_Prot3P"));
	MUCurrErrorRange_AddData(pDataset,_T("电压-保护级(6P)"),_T("Vol_Prot6P"));
	MUCurrErrorRange_AddData(pDataset,_T("电压-测量级(0.1)"),_T("Vol_Meas0_1"));
	MUCurrErrorRange_AddData(pDataset,_T("电压-测量级(0.2)"),_T("Vol_Meas0_2"));
	MUCurrErrorRange_AddData(pDataset,_T("电压-测量级(0.5)"),_T("Vol_Meas0_5"));
	MUCurrErrorRange_AddData(pDataset,_T("电压-测量级(1)"),_T("Vol_Meas1"));
	MUCurrErrorRange_AddData(pDataset,_T("电流-保护级(5P30)"),_T("Curr_Prot5P30"));
	MUCurrErrorRange_AddData(pDataset,_T("电流-保护级(5P"),_T("Curr_Prot5P"));
	MUCurrErrorRange_AddData(pDataset,_T("电流-保护级(10P)"),_T("Curr_Prot10P"));
	MUCurrErrorRange_AddData(pDataset,_T("电流-测量级(0.1)"),_T("Curr_Meas0_1"));
	MUCurrErrorRange_AddData(pDataset,_T("电流-测量级(0.2S)"),_T("Curr_Meas0_2S"));
	MUCurrErrorRange_AddData(pDataset,_T("电流-测量级(0.2)"),_T("Curr_Meas0_2"));
	MUCurrErrorRange_AddData(pDataset,_T("电流-测量级(0.5S)"),_T("Curr_Meas0_5S"));
	MUCurrErrorRange_AddData(pDataset,_T("电流-测量级(0.5)"),_T("Curr_Meas0_5"));
	MUCurrErrorRange_AddData(pDataset,_T("电流-测量级(1)"),_T("Curr_Meas1"));

	//ADMU
	MUCurrErrorRange_AddData(pDataset,_T("电流-测量级(1S)"),_T("Curr_Meas1S"));
	MUCurrErrorRange_AddData(pDataset,_T("电流-保护级(5P10)"),_T("Curr_Prot5P10"));
	MUCurrErrorRange_AddData(pDataset,_T("电压-零序保护级(3P)"),_T("Vol_Prot3P_Z"));

	m_pDataset_CurrErrorRange = pDataset;
}


void CX61850CapBase::StateValueChangedRlt_AddDataset()
{
	CDvmLogicDevice *pLogicDevice = GetLogicalDevice(TRUE);
	CDvmDataset *pDataset = (CDvmDataset*)pLogicDevice->FindByID(CAP_DATASET_MAP_ID_dsStateValueChangedRlt);

	if (pDataset != NULL)
	{
		return;
	}
	pDataset = new CDvmDataset();
	pDataset->m_strName = CAP_DATASET_MAP_ID_dsStateValueChangedRlt;
	pDataset->m_strID = CAP_DATASET_MAP_ID_dsStateValueChangedRlt;
	pLogicDevice->AddNewChild(pDataset);
	CDvmData *pData = pDataset->AddNewData(_T("开出变位次数"),_T("BoutValueChangedCount"),_T("long"),_T(""));
	pData->m_nChange = 1;
	pData = pDataset->AddNewData(_T("开入变位次数"),_T("StateValueChangedCount"),_T("long"),_T(""));
	pData->m_nChange = 1;
	pData = pDataset->AddNewData(_T("结论"),_T("StateValueChangedResult"),_T("string"),_T(""));
	pData->m_nChange = 1;
	m_pDataset_StateValueChangedRlt = pDataset;
}

void CX61850CapBase::UpdateStateValueChangedRltDatas() //更新开出变位次数、结论
{	
	CDvmData *pBoutValueChangedCountData = (CDvmData *)m_pDataset_StateValueChangedRlt->FindByID(_T("BoutValueChangedCount"));
	CDvmData *pStateValueChangedCountData = (CDvmData *)m_pDataset_StateValueChangedRlt->FindByID(_T("StateValueChangedCount"));
	CDvmData *pStateValueChangedResultData = (CDvmData *)m_pDataset_StateValueChangedRlt->FindByID(_T("StateValueChangedResult"));
	
	CCapDeviceBase *pSelCapDevice = (CCapDeviceBase*)m_oCapDeviceAll.FindByID(m_strDatasetMapID_MUTestCB);
	long nBoutCount = 0;
	if (pSelCapDevice->GetClassID() == CPDCLASSID_DEVICE6044)
		 {
		CCapDevice6044 *pDevice6044 = (CCapDevice6044 *)pSelCapDevice;
			if (pStateValueChangedCountData)
			{	
				pStateValueChangedCountData->m_strValue.Format(_T("%d"),pDevice6044->m_nStateValueChangedCount);
			}
		if (pBoutValueChangedCountData)
		{
			nBoutCount = CString_To_long(pBoutValueChangedCountData->m_strValue);
		}

			if(pStateValueChangedResultData)
			{
			if (pDevice6044->m_nStateValueChangedCount == nBoutCount)
				{
					pStateValueChangedResultData->m_strValue = _T("合格");
				}
				else
				{
					pStateValueChangedResultData->m_strValue = _T("不合格");
				}
			}
		 }
}

void CX61850CapBase::TestFunSelect_AddDataset()
{
	CDvmLogicDevice *pLogicDevice = GetLogicalDevice(TRUE);

	CDvmDataset *pDataset = (CDvmDataset*)pLogicDevice->FindByID(CAP_DATASET_MAP_ID_TestFunSelect);

	if (pDataset != NULL)
	{
		return;
	}

	pDataset = new CDvmDataset();
	pDataset->m_strName = _T("测试功能选择");
	pDataset->m_strID = CAP_DATASET_MAP_ID_TestFunSelect;
	pLogicDevice->AddNewChild(pDataset);
	pDataset->AddNewData(_T("测试功能"),_T("TestFunction"),_T("long"),_T("0"));

	m_pDataset_TestFunSelect = pDataset;
}

void CX61850CapBase::InitIsFunSelectValueByDataset()
{
	if (m_pDataset_TestFunSelect == NULL)
	{
		return;
	}

	long nValue = 0;

	CDvmData *pDvmData = (CDvmData*)m_pDataset_TestFunSelect->FindByID(_T("TestFunction"));

	if (pDvmData != NULL)
	{
		nValue = CString_To_long(pDvmData->m_strValue);
	}

	if (nValue == 0)
	{
		g_oCapAnalysisConfig.m_bStateValueChangedAnalysis = true;	
		//chenling 2024.6.4 选择控制块复归
		CCapDeviceBase *pSelCapDevice = (CCapDeviceBase*)m_oCapDeviceAll.FindByID(m_strDatasetMapID_MUTestCB);
		if (pSelCapDevice != NULL)
		{
			pSelCapDevice->Reset();
		}
	}
	else
	{
		g_oCapAnalysisConfig.m_bStateValueChangedAnalysis = false;
	}
}

void CX61850CapBase::InitMuErrorRangesBydsCurrErrorRange()
{
	if ((m_pDataset_CurrErrorRange == NULL)||(m_pDataset_ErrorRanges == NULL))
	{
		return;
	}

	double dCurrTestRate = 1.0f,dCurrErrorRangeDiff = 10.0f;
	XSttRcdInitDouble_FromDataset(m_pDataset_CurrErrorRange,_T("CurrTestRate"),dCurrTestRate);
	XSttRcdInitDouble_FromDataset(m_pDataset_CurrErrorRange,_T("Unom"),m_dZeroDrift_Un);
	XSttRcdInitDouble_FromDataset(m_pDataset_CurrErrorRange,_T("Inom"),m_dZeroDrift_In);
// 	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("更新合并单元计算误差,当前测试比率(%lf),额定电压(%lf),额定电流(%lf)."),
// 		dCurrTestRate,m_dZeroDrift_Un,m_dZeroDrift_In);
	CDvmData *pCurrMuErrorData = NULL,*pMuErrorData_Find = NULL;
	double dTestRate_Tmp = 1.0f;
	POS pos = m_pDataset_ErrorRanges->GetHeadPosition();

	while(pos)
	{
		pCurrMuErrorData = (CDvmData*)m_pDataset_ErrorRanges->GetNext(pos);
		dTestRate_Tmp = CString_To_double(pCurrMuErrorData->m_strValue);

		if (fabs(dCurrTestRate - dTestRate_Tmp) < dCurrErrorRangeDiff)
		{
			dCurrErrorRangeDiff = fabs(dCurrTestRate - dTestRate_Tmp);
			pMuErrorData_Find = pCurrMuErrorData;//遍历真个误差data,找到最接近的误差值
		}
	}

	if (pMuErrorData_Find != NULL)
	{
		if (m_bIsFT3ADMU)
		{
			InitADMUErrorRangesByCurrErrorRange(pMuErrorData_Find);
		}
		else
		{
		InitMuErrorRangesByCurrErrorRange(pMuErrorData_Find);
	}
	}
}

void CX61850CapBase::InitIsFirstCWTestValueByDataset()
{
	if (m_pDataset_RcdStep6U6I == NULL)
	{
		return;
	}

	CDvmData *pIsFirstCWTest = (CDvmData*)m_pDataset_RcdStep6U6I->FindByID(X61850_CapID_IsFirstCWTest);

	if (pIsFirstCWTest != NULL)
	{
		g_nIsFirstCWTest = CString_To_long(pIsFirstCWTest->m_strValue);
	}
}

void CX61850CapBase::InitCapDeviceRecordMngr_SmpRate(long nSmpRateValue)
{
	CRecordTest *pRecordTest = m_oCapDeviceChRecordMngr.m_pRecordTest;

	if (pRecordTest == NULL)
	{
		return;
	}

	pRecordTest->g_nSampleRate = nSmpRateValue;
}

void CX61850CapBase::InitADMUErrorRangesByCurrErrorRange(CDvmData *pCurrADMUErrorData)
{
	if (pCurrADMUErrorData == NULL)
	{
		return;
	}


	InitMuErrorRangesByCurrErrorRange(pCurrADMUErrorData,_T("Vol_Meas0_5"),&g_oADMUErrorRanges.m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_Meas0_5]);
	InitMuErrorRangesByCurrErrorRange(pCurrADMUErrorData,_T("Vol_Meas1"),&g_oADMUErrorRanges.m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_Meas1]);
	InitMuErrorRangesByCurrErrorRange(pCurrADMUErrorData,_T("Vol_Prot3P"),&g_oADMUErrorRanges.m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_PhaseProt3P]);
	InitMuErrorRangesByCurrErrorRange(pCurrADMUErrorData,_T("Vol_Prot3P_Z"),&g_oADMUErrorRanges.m_oADMUVolChRange[ADMU_IECCFG_VOLCH_AccLevel_ZeroSeqProt3P]);

	InitMuErrorRangesByCurrErrorRange(pCurrADMUErrorData,_T("Curr_Meas0_5S"),&g_oADMUErrorRanges.m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Meas0_5S]);
	InitMuErrorRangesByCurrErrorRange(pCurrADMUErrorData,_T("Curr_Meas1S"),&g_oADMUErrorRanges.m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Meas1S]);
	InitMuErrorRangesByCurrErrorRange(pCurrADMUErrorData,_T("Curr_Prot5P10"),&g_oADMUErrorRanges.m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Prot5P10]);
	InitMuErrorRangesByCurrErrorRange(pCurrADMUErrorData,_T("Curr_Prot5P30"),&g_oADMUErrorRanges.m_oADMUCurrChRange[ADMU_IECCFG_CURRCH_AccLevel_Prot5P30]);
}

void CX61850CapBase::InitMuErrorRangesByCurrErrorRange(CDvmData *pCurrMuErrorData)
{	
	InitMuErrorRangesByCurrErrorRange(pCurrMuErrorData,_T("Vol_Prot3P"),&g_oMuErrorRanges.m_oVolChRange[IECCFG_VOLCH_AccLevel_Prot3P]);
	InitMuErrorRangesByCurrErrorRange(pCurrMuErrorData,_T("Vol_Prot6P"),&g_oMuErrorRanges.m_oVolChRange[IECCFG_VOLCH_AccLevel_Prot6P]);
	InitMuErrorRangesByCurrErrorRange(pCurrMuErrorData,_T("Vol_Meas0_1"),&g_oMuErrorRanges.m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas0_1]);
	InitMuErrorRangesByCurrErrorRange(pCurrMuErrorData,_T("Vol_Meas0_2"),&g_oMuErrorRanges.m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas0_2]);
	InitMuErrorRangesByCurrErrorRange(pCurrMuErrorData,_T("Vol_Meas0_5"),&g_oMuErrorRanges.m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas0_5]);
	InitMuErrorRangesByCurrErrorRange(pCurrMuErrorData,_T("Vol_Meas1"),&g_oMuErrorRanges.m_oVolChRange[IECCFG_VOLCH_AccLevel_Meas1]);

	InitMuErrorRangesByCurrErrorRange(pCurrMuErrorData,_T("Curr_Prot5P30"),&g_oMuErrorRanges.m_oCurrChRange[IECCFG_CURRCH_AccLevel_Prot5P30]);
	InitMuErrorRangesByCurrErrorRange(pCurrMuErrorData,_T("Curr_Prot5P"),&g_oMuErrorRanges.m_oCurrChRange[IECCFG_CURRCH_AccLevel_Prot5P]);
	InitMuErrorRangesByCurrErrorRange(pCurrMuErrorData,_T("Curr_Prot10P"),&g_oMuErrorRanges.m_oCurrChRange[IECCFG_CURRCH_AccLevel_Prot10P]);
	InitMuErrorRangesByCurrErrorRange(pCurrMuErrorData,_T("Curr_Meas0_1"),&g_oMuErrorRanges.m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_1]);
	InitMuErrorRangesByCurrErrorRange(pCurrMuErrorData,_T("Curr_Meas0_2S"),&g_oMuErrorRanges.m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_2S]);
	InitMuErrorRangesByCurrErrorRange(pCurrMuErrorData,_T("Curr_Meas0_2"),&g_oMuErrorRanges.m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_2]);
	InitMuErrorRangesByCurrErrorRange(pCurrMuErrorData,_T("Curr_Meas0_5S"),&g_oMuErrorRanges.m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_5S]);
	InitMuErrorRangesByCurrErrorRange(pCurrMuErrorData,_T("Curr_Meas0_5"),&g_oMuErrorRanges.m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas0_5]);
	InitMuErrorRangesByCurrErrorRange(pCurrMuErrorData,_T("Curr_Meas1"),&g_oMuErrorRanges.m_oCurrChRange[IECCFG_CURRCH_AccLevel_Meas1]);	
}

void CX61850CapBase::InitMuErrorRangesByCurrErrorRange(CDvmData *pCurrMuErrorData,const CString &strID,_61850CapMUErrorRange *pCurrChRange)
{
	if (pCurrMuErrorData == NULL)
	{
		return;
	}

	CString strValueID;
	strValueID.Format(_T("%s$%s"),pCurrMuErrorData->m_strID.GetString(),strID.GetString());
	CDvmValue *pCurrValue = (CDvmValue*)pCurrMuErrorData->FindByID(strValueID);

	if (pCurrValue == NULL)
	{
		return;
	}

	CString strChildValueID;
	strChildValueID.Format(_T("%s$StdRateError"),strValueID.GetString());
	XSttRcdInitDouble_FromValue(pCurrValue,strChildValueID,pCurrChRange->m_dStdError[0]);
	strChildValueID.Format(_T("%s$StdAngError"),strValueID.GetString());
	XSttRcdInitDouble_FromValue(pCurrValue,strChildValueID,pCurrChRange->m_dStdError[1]);
	strChildValueID.Format(_T("%s$StdCompError"),strValueID.GetString());
	XSttRcdInitDouble_FromValue(pCurrValue,strChildValueID,pCurrChRange->m_dStdError[2]);

	strChildValueID.Format(_T("%s$RateErrorCalType"),strValueID.GetString());
	XSttRcdInitDouble_FromValue(pCurrValue,strChildValueID,pCurrChRange->m_nErrorCalType[0]);
	strChildValueID.Format(_T("%s$AngErrorCalType"),strValueID.GetString());
	XSttRcdInitDouble_FromValue(pCurrValue,strChildValueID,pCurrChRange->m_nErrorCalType[1]);
	strChildValueID.Format(_T("%s$CompErrorCalType"),strValueID.GetString());
	XSttRcdInitDouble_FromValue(pCurrValue,strChildValueID,pCurrChRange->m_nErrorCalType[2]);
}

CDvmData* CX61850CapBase::MUCurrErrorRange_AddData(CDvmDataset *pDsErrorRange,const CString &strDataName,const CString &strDataID)
{
	CDvmData *pErrorRangeData = pDsErrorRange->AddNewData(strDataName,strDataID,_T("float"),_T("0"));
	CString strID;
	//比差误差
	strID.Format(_T("%s$StdRateError"),strDataID.GetString());
	pErrorRangeData->AddValue2(strID,_T("0"),_T("float"));
	strID.Format(_T("%s$RateErrorCalType"),strDataID.GetString());
	pErrorRangeData->AddValue2(strID,_T("0"),_T("long"));

	//角差误差
	strID.Format(_T("%s$StdAngError"),strDataID.GetString());
	pErrorRangeData->AddValue2(strID,_T("0"),_T("float"));
	strID.Format(_T("%s$AngErrorCalType"),strDataID.GetString());
	pErrorRangeData->AddValue2(strID,_T("0"),_T("long"));

	//复合误差
	strID.Format(_T("%s$StdCompError"),strDataID.GetString());
	pErrorRangeData->AddValue2(strID,_T("0"),_T("float"));
	strID.Format(_T("%s$CompErrorCalType"),strDataID.GetString());
	pErrorRangeData->AddValue2(strID,_T("0"),_T("long"));
	return pErrorRangeData;
}

//////////////////////////////////////////////////////////////////////////
double cap_MUAccuracy_GetVolChStdErrorValue(long nAccurLevel,long nErrorType)
{
	double dErrorValue = 100.0f;

	if ((nAccurLevel>=0)&&(nErrorType>=0)
		&&(nAccurLevel<MUErrorRange_VolLevelNum)&&(nErrorType<3))
	{
		dErrorValue = g_oMuErrorRanges.m_oVolChRange[nAccurLevel].m_dStdError[nErrorType];
	}

/*	if (nAccurLevel == IECCFG_VOLCH_AccLevel_Prot3P)
	{
		if (nErrorType == MUAccuracy_ErrorType_RatError)
		{
			dErrorValue = 0.03f;
		}
		else if (nErrorType == MUAccuracy_ErrorType_AngError)
		{
			dErrorValue = 120;
		}
	}
	else if (nAccurLevel == IECCFG_VOLCH_AccLevel_Prot6P)
	{
		if (nErrorType == MUAccuracy_ErrorType_RatError)
		{
			dErrorValue = 0.06f;
		}
		else if (nErrorType == MUAccuracy_ErrorType_AngError)
		{
			dErrorValue = 240;
		}
	}
	else if (nAccurLevel == IECCFG_VOLCH_AccLevel_Meas0_1)
	{
		if (nErrorType == MUAccuracy_ErrorType_RatError)
		{
			dErrorValue = 0.001f;
		}
		else if (nErrorType == MUAccuracy_ErrorType_AngError)
		{
			dErrorValue = 5;
		}
	}
	else if (nAccurLevel == IECCFG_VOLCH_AccLevel_Meas0_2)
	{
		if (nErrorType == MUAccuracy_ErrorType_RatError)
		{
			dErrorValue = 0.002f;
		}
		else if (nErrorType == MUAccuracy_ErrorType_AngError)
		{
			dErrorValue = 10;
		}
	}
	else if (nAccurLevel == IECCFG_VOLCH_AccLevel_Meas0_5)
	{
		if (nErrorType == MUAccuracy_ErrorType_RatError)
		{
			dErrorValue = 0.005f;
		}
		else if (nErrorType == MUAccuracy_ErrorType_AngError)
		{
			dErrorValue = 20;
		}
	}
	else if (nAccurLevel == IECCFG_VOLCH_AccLevel_Meas1)
	{
		if (nErrorType == MUAccuracy_ErrorType_RatError)
		{
			dErrorValue = 0.01f;
		}
		else if (nErrorType == MUAccuracy_ErrorType_AngError)
		{
			dErrorValue = 40;
		}
	}*/

	return dErrorValue;
}

double cap_MUAccuracy_GetCurrChStdErrorValue(long nAccurLevel,long nErrorType)
{
	double dErrorValue = 100.0f;

	if ((nAccurLevel>=0)&&(nErrorType>=0)
		&&(nAccurLevel<MUErrorRange_CurrLevelNum)&&(nErrorType<3))
	{
		dErrorValue = g_oMuErrorRanges.m_oCurrChRange[nAccurLevel].m_dStdError[nErrorType];
	}
/*
	if (nAccurLevel == IECCFG_CURRCH_AccLevel_Prot5P30)
	{
		if (nErrorType == MUAccuracy_ErrorType_RatError)
		{
			dErrorValue = 0.01f;
		}
		else if (nErrorType == MUAccuracy_ErrorType_AngError)
		{
			dErrorValue = 60;
		}
		else if (nErrorType == MUAccuracy_ErrorType_CompError)
		{
			dErrorValue = 0.05f;
		}
	}
	else if (nAccurLevel == IECCFG_CURRCH_AccLevel_Prot5P)
	{
		if (nErrorType == MUAccuracy_ErrorType_RatError)
		{
			dErrorValue = 0.01f;
		}
		else if (nErrorType == MUAccuracy_ErrorType_AngError)
		{
			dErrorValue = 60;
		}
		else if (nErrorType == MUAccuracy_ErrorType_CompError)
		{
			dErrorValue = 0.05f;
		}
	}
	else if (nAccurLevel == IECCFG_CURRCH_AccLevel_Prot10P)
	{
		if (nErrorType == MUAccuracy_ErrorType_RatError)
		{
			dErrorValue = 0.03f;
		}
		else if (nErrorType == MUAccuracy_ErrorType_AngError)
		{
			dErrorValue = 120;
		}
		else if (nErrorType == MUAccuracy_ErrorType_CompError)
		{
			dErrorValue = 0.1f;
		}
	}
	else if (nAccurLevel == IECCFG_CURRCH_AccLevel_Meas0_1)
	{
		if (nErrorType == MUAccuracy_ErrorType_RatError)
		{
			dErrorValue = 0.001f;
		}
		else if (nErrorType == MUAccuracy_ErrorType_AngError)
		{
			dErrorValue = 5;
		}
	}
	else if (nAccurLevel == IECCFG_CURRCH_AccLevel_Meas0_2S)
	{
		if (nErrorType == MUAccuracy_ErrorType_RatError)
		{
			dErrorValue = 0.002f;
		}
		else if (nErrorType == MUAccuracy_ErrorType_AngError)
		{
			dErrorValue = 10;
		}
	}
	else if (nAccurLevel == IECCFG_CURRCH_AccLevel_Meas0_2)
	{
		if (nErrorType == MUAccuracy_ErrorType_RatError)
		{
			dErrorValue = 0.002f;
		}
		else if (nErrorType == MUAccuracy_ErrorType_AngError)
		{
			dErrorValue = 10;
		}
	}
	else if (nAccurLevel == IECCFG_CURRCH_AccLevel_Meas0_5S)
	{
		if (nErrorType == MUAccuracy_ErrorType_RatError)
		{
			dErrorValue = 0.005f;
		}
		else if (nErrorType == MUAccuracy_ErrorType_AngError)
		{
			dErrorValue = 30;
		}
	}
	else if (nAccurLevel == IECCFG_CURRCH_AccLevel_Meas0_5)
	{
		if (nErrorType == MUAccuracy_ErrorType_RatError)
		{
			dErrorValue = 0.005f;
		}
		else if (nErrorType == MUAccuracy_ErrorType_AngError)
		{
			dErrorValue = 30;
		}
	}
	else if (nAccurLevel == IECCFG_CURRCH_AccLevel_Meas1)
	{
		if (nErrorType == MUAccuracy_ErrorType_RatError)
		{
			dErrorValue = 0.01f;
		}
		else if (nErrorType == MUAccuracy_ErrorType_AngError)
		{
			dErrorValue = 60;
		}
	}
*/
	return dErrorValue;
}


double cap_ADMUccuracy_GetVolChStdErrorValue(long nAccurLevel,long nErrorType)
{
	double dErrorValue = 100.0f;

	if ((nAccurLevel>=0)&&(nErrorType>=0)
		&&(nAccurLevel<ADMUErrorRange_VolLevelNum)&&(nErrorType<3))
	{
		dErrorValue = g_oADMUErrorRanges.m_oADMUVolChRange[nAccurLevel].m_dStdError[nErrorType];
	}
	return dErrorValue;
}

double cap_ADMUccuracy_GetCurrChStdErrorValue(long nAccurLevel,long nErrorType)
{
	double dErrorValue = 100.0f;

	if ((nAccurLevel>=0)&&(nErrorType>=0)
		&&(nAccurLevel<ADMUErrorRange_CurrLevelNum)&&(nErrorType<3))
	{
		dErrorValue = g_oADMUErrorRanges.m_oADMUCurrChRange[nAccurLevel].m_dStdError[nErrorType];
	}
	return dErrorValue;
}


//////////////////////////////////////////////////////////////////////////

void CX61850CapBase::CreateUpdateDvmDeviceDatasThread()
{
    //for debug......
    return;
	if (m_pUpdateDvmDatasThread != NULL)
	{
		return;
	}

#ifdef _PSX_IDE_QT_
	m_pUpdateDvmDatasThread = new CWinThread(UpdateDvmDeviceDatasThread, this);
	m_pUpdateDvmDatasThread->ResumeThread();
#else
	m_pUpdateDvmDatasThread = AfxBeginThread(UpdateDvmDeviceDatasThread, this);
	m_pUpdateDvmDatasThread->m_bAutoDelete = TRUE;
#endif

}

void CX61850CapBase::InitSVDatasetADMUChannel()
{
	if (m_pDataset_MUTestCB == NULL)
	{
		return;
	}

	CDvmData *pCurrChData = NULL ;
	CCapDeviceSmvCh *pDevCh = NULL;
	POS pos = m_pDataset_MUTestCB->GetHeadPosition();
	CCapDeviceBase *pCapDeviceBase = (CCapDeviceBase*)m_oCapDeviceAll.FindByID(m_strDatasetMapID_MUTestCB);
	while(pos)
	{
		pCurrChData = (CDvmData *)m_pDataset_MUTestCB->GetNext(pos);
		long nIndex = pCurrChData->m_strID.ReverseFind('_');
		if (nIndex <= 0)
		{
			return;
		}

		if (pCapDeviceBase != NULL)
		{
			pDevCh = (CCapDeviceSmvCh*)pCapDeviceBase->FindByID(pCurrChData->m_strID);
			if (pDevCh != NULL)
			{
				pCurrChData->m_nIndex = pDevCh->m_nAccurLevel;
				pCurrChData->m_nChange = pDevCh->m_nSelect;
			}
		}
	}
}


UINT UpdateDvmDeviceDatasThread(LPVOID pParam)
{
	CX61850CapBase *pThis = (CX61850CapBase*)pParam;
	CTickCount32 oTick32;

	while (TRUE)
	{
		pThis->UpdateDvmDeviceDatas();
		Sleep(200);
	}

	return 0;
}

