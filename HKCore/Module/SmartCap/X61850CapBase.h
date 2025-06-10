#pragma once

#ifndef _PSX_IDE_QT_
#include "61850Cap/CapSmDbFile/CapFrameDbFile.h"
#include "../Smdb/SmDbWriteThread.h"
#endif

#include "61850Cap/ProtocolBase/Protocol61850.h"
#include "61850Cap/Record/CapDeviceChRecordMngr.h"

#include "../../Module/DataMngr/DvmDevice.h"
#include "../../61850/Module/CfgDataMngr/IecCfgDevice.h"
#include "../../61850/Module/CfgDataMngr/IecCfgDatasMngr.h"
#include "../../Module/Smdb/XSmMemBufferMngr.h"
#include "XIecDatasetSmartMatch.h"
#include "61850Cap/CapDevice/CapDevice92.h"
#include "61850Cap/CapDevice/CapDevice6044.h"


#define WM_UPDATECAPDEVICE	(WM_USER+1145)
#define WM_UPDATECAPDEVICES	(WM_USER+1146)

#define WM_SHOWIECFGDATAS	    (WM_USER+2020)
#define WM_UPDATETITLE		    (WM_USER+2021)
#define WM_UPDATEDATASET	    (WM_USER+2022)
#define WM_SHOW_DVMDEVICE	(WM_USER+2023)
#define WM_KILL_TIMER_DVM     (WM_USER+2024)


//配置ID 
#define CONFIG_ID_GOOSEACCEPTTEST   "GooseAcceptTest"    //goose接收和解析能力测试
#define CONFIG_ID_TIMEMEASURETEST   "TimeMeasureTest"    //时间测量准确度测试
#define CONFIG_ID_BOUTTIMETEST      "BoutTimeTest"       //硬接点时间测试
#define CONFIG_ID_IEC61850CONFIG   "IEC61850CFG"


#define IEDTEST_CONTROLMODE_AUTOTEST    _T("1")
#define IEDTEST_CONTROLMODE_MANUTEST    _T("0")

#define IEDTEST_TESTTYPE_DELAY          _T("0")
#define IEDTEST_TESTTYPE_SOE            _T("1")
#define IEDTEST_TESTTYPE_STORM          _T("2")

#define IEDTEST_TESTMODE_GSE2BIN        _T("0")
#define IEDTEST_TESTMODE_BOUT2GSE       _T("1")
#define IEDTEST_TESTMODE_GSE2BIN_RESET  _T("2")
#define IEDTEST_TESTMODE_BOUT2GSE_RESET _T("3")

#define MUAccuracy_ErrorType_RatError                0
#define MUAccuracy_ErrorType_AngError                1
#define MUAccuracy_ErrorType_CompError               2
#define MUAccuracy_ErrorType_FreqError               3


static CString g_strListChannelGroupName[12] = {_T("Ua"), _T("Ub"), _T("Uc"), _T("Uap"), _T("Ubp"), _T("Ucp")
,_T("Ia"), _T("Ib"), _T("Ic"), _T("Iap"), _T("Ibp"), _T("Icp")};
static CString g_strListChannelName[12] = {_T("Ua1"), _T("Ub1"), _T("Uc1"), _T("Ua2"), _T("Ub2"), _T("Uc2")
,_T("Ia1"), _T("Ib1"), _T("Ic1"), _T("Ia2"), _T("Ib2"), _T("Ic2")};
static CString g_strListChannelPh[12] = {_T("Ua1Ph"), _T("Ub1Ph"), _T("Uc1Ph"), _T("Ua2Ph"), _T("Ub2Ph"), _T("Uc2Ph")
,_T("Ia1Ph"), _T("Ib1Ph"), _T("Ic1Ph"), _T("Ia2Ph"), _T("Ib2Ph"), _T("Ic2Ph")};
static CString g_strListChannelHarm[12] = {_T("Ua1Harm"), _T("Ub1Harm"), _T("Uc1Harm"), _T("Ua2Harm"), _T("Ub2Harm"), _T("Uc2Harm")
,_T("Ia1Harm"), _T("Ib1Harm"), _T("Ic1Harm"), _T("Ia2Harm"), _T("Ib2Harm"), _T("Ic2Harm")};
static CString g_strListChannelHarmPh[12] = {_T("Ua1HarmPh"), _T("Ub1HarmPh"), _T("Uc1HarmPh"), _T("Ua2HarmPh"), _T("Ub2HarmPh"), _T("Uc2HarmPh")
,_T("Ia1HarmPh"), _T("Ib1HarmPh"), _T("Ic1HarmPh"), _T("Ia2HarmPh"), _T("Ib2HarmPh"), _T("Ic2HarmPh")};

#define X61850_CapID_IsZeroDriftTest              _T("IsZeroDriftTest")
#define X61850_CapID_ZeroDrift_Un                 _T("Un")
#define X61850_CapID_ZeroDrift_In                 _T("In")
#define X61850_CapID_IsFirstCWTest                _T("IsFirstCWTest")


//zhouhj 2023.10.13 删除
//#define X61850_CapID_DelayCompens_NoPPS           _T("DelayCompens_NoPPS")


#define STT_MUTEST_DL_ChDelay                  _T("$ChDelay")
#define STT_MUTEST_DL_RealDelay                _T("$RealDelay")
#define STT_MUTEST_DL_MaxDelayError            _T("$MaxDelayError")
#define STT_MUTEST_DL_MinDelayError            _T("$MinDelayError")
#define STT_MUTEST_DL_AverageDelayError        _T("$AverageDelayError")
#define STT_MUTEST_DL_TimeLong                 _T("$TimeLong")
// #define STT_MUTEST_DL_MaxErrorNoPPS            _T("$MaxErrorNoPPS")
// #define STT_MUTEST_DL_MinErrorNoPPS            _T("$MinErrorNoPPS")
// #define STT_MUTEST_DL_AverageErrorNoPPS        _T("$AverageErrorNoPPS")

#define STT_MUTEST_HasUsingTime                 _T("HasUsingTime")
#define STT_MUTEST_MaxErrTime                   _T("MaxErrTime")
#define STT_MUTEST_MinErrTime                   _T("MinErrTime")
#define STT_MUTEST_CurrErrTime                  _T("CurrErrTime")
#define STT_MUTEST_AverageErrTime               _T("AverageErrTime")
#define STT_MUTEST_MUTimeResult               _T("MUTimeResult")

#define STT_SV_MaxTestCount                      5000// zhouhj 2023.10.13 最大测试次数

#define MUErrorRange_VolLevelNum                      6
#define MUErrorRange_CurrLevelNum                     9

#define ADMUErrorRange_VolLevelNum                      4
#define ADMUErrorRange_CurrLevelNum                     4

#define CAP_BEFORE_TEST_DELAY_COUNT            12//测试开始后,不进入结果统计的延时次数
#define CAP_BEFORE_TEST_CALC_COUNT             4//测试开始后,不进入结果统计的角差、比差、复合误差次数


typedef struct _PARAMCALCOMPLEX
{
		float		fFinitAmp;
		float		fFinitPh;		
		float		fFinitFre;  
}_PARAMCALCOMPLEX;

typedef struct _61850_cap_mu_error_range//0:角差  1:比差   2:复合误差
{
	double		m_dStdError[3];//标准误差 
	double		m_nErrorCalType[3];		  //误差判断类别  0:绝对误差;1:相对误差 

	void  Init()
	{
		for (int nIndex = 0;nIndex<3;nIndex++)
		{
			m_dStdError[nIndex] = -1.0f;
			m_nErrorCalType[nIndex] = 0;
		}
	}
}_61850CapMUErrorRange;


typedef struct _61850_cap_mu_error_ranges
{
	_61850CapMUErrorRange		m_oCurrChRange[MUErrorRange_CurrLevelNum];
	_61850CapMUErrorRange		m_oVolChRange[MUErrorRange_VolLevelNum];


 	//2024.5.16 ADMU
	_61850CapMUErrorRange		m_oADMUCurrChRange[ADMUErrorRange_CurrLevelNum];
	_61850CapMUErrorRange		m_oADMUVolChRange[ADMUErrorRange_VolLevelNum];

	void  Init()
	{
		for (int nIndex = 0;nIndex<MUErrorRange_VolLevelNum;nIndex++)
		{
			m_oVolChRange[nIndex].Init();
		}

		for (int nIndex = 0;nIndex<MUErrorRange_CurrLevelNum;nIndex++)
		{
			m_oCurrChRange[nIndex].Init();
		}

		for (int nIndex = 0;nIndex<ADMUErrorRange_CurrLevelNum;nIndex++)
		{
			m_oADMUCurrChRange[nIndex].Init();
		}

		for (int nIndex = 0;nIndex<ADMUErrorRange_VolLevelNum;nIndex++)
		{
			m_oADMUVolChRange[nIndex].Init();
		}

	}

	void InitNormal();//通用的初始化标准,即额定电压、额定电流时的误差判据
	void InitADMUNormal();//ADMU的误差判据

	_61850_cap_mu_error_ranges()
	{
		Init();
	}
}_61850CapMUErrorRanges;


class CX61850CapBase
{
public:

	//double m_dTimeDelayForMU;

	_PARAMCALCOMPLEX m_U_B[6],  m_I_B[6],   m_U_P[6],  m_I_P[6];//分别对应MU测试仪输出模拟量的,6电压、6电流、6电压谐波、6电流谐波的幅值、相位、频率
	double m_oStdSrcDatas_FirstCW[12][800];//首周波的原始数据，开始测试之前从这里初始化首周波
	bool m_bFirstCWDatasChanged;//判断首周波测试参数数据是否改变
	bool m_bIsFT3ADMU;//是否是FT3且是ADMU自动测试

public:
	CX61850CapBase(void);
	virtual ~CX61850CapBase(void);

	virtual void ExitInstance();
	virtual void CreateCapTrhead();
	virtual BOOL BeginCap(CIecCfgDatasMngr *pIecfgDataMngr,BOOL bClearDevices=TRUE);
	virtual BOOL StopCap();

	virtual void BeginRecord();
	virtual void StopRecord();

	virtual BOOL IsCapExit();
	virtual BOOL CanClose();
	virtual BOOL IsInCapture();
	
	virtual void FreeCapture();
#ifdef _XSmartCap_use_SmDb_
	virtual void InitCapSmDb();
#endif
	virtual void ClearCap(); //2022-5-2  lijunqing  清空Cap相关的内容
	void ClearPara();

	void RecordDevice(CCapDeviceBase *pDevice);
	void RecordDevices();

	//根据pCapDevice初始化DvmDevice数据集
	void InitDvmDevices();
	void InitDvmDevices(CIecCfgDatasMngr *pDatasMngr);
	void InitDvmDevices_BySmvInGin(CIecCfgDatasMngr *pDatasMngr,BOOL bhasMUTestParas);//20220811 zhouhj  根据Iec配置中的SMV接收和GOOSE接收初始化逻辑设备
	void InitDvmDevice(CCapDeviceBase *pCapDevice);
	CDvmLogicDevice* GetLogicalDevice(BOOL bNew);
	CDvmDataset* FindDataset(const CString &strDatasetID);
	CDvmDataset* GetDataset(CDvmLogicDevice *pLDevice, const CString &strID);
	CDvmData* GetMU_TimeAccurRltData();
	BOOL SetName_DvmData(const CString &strDatasetID,const CString &strDataID,const CString &strDataName);//20221212 设置数据集中某个通道描述

	void RecordAllDevice(BOOL bRcdGoose=FALSE);
	void ChangeChRecordState(CCapDeviceChBase *pCh, long nState);
	void RecordDevice_Reset();
	void GetSttCapParas(CDataGroup *pSttParas, BOOL bUseSmv, BOOL bUseGoose,BOOL bUseFT3);  //2022-4-14  lijunqing

	void InitMuErrorRangesBydsCurrErrorRange();//根据当前测试项数据集,初始化误差判断标准
	void InitMuErrorRangesByCurrErrorRange(CDvmData *pCurrMuErrorData);//根据当前测试项数据对象,初始化误差判断标准结构体
	void InitMuErrorRangesByCurrErrorRange(CDvmData *pCurrMuErrorData,const CString &strID,_61850CapMUErrorRange *pCurrChRange);//根据当前测试项数据对象,初始化误差判断标准结构体

	void InitIsFirstCWTestValueByDataset();

	void InitCapDeviceRecordMngr_SmpRate(long nSmpRateValue);
	void InitADMUErrorRangesByCurrErrorRange(CDvmData *pCurrADMUErrorData);//ADMU根据当前测试项数据对象,初始化误差判断标准结构体


	void InitSVDatasetADMUChannel();//admu报文探测谐波模块通道过滤

	virtual void OnCloseMainFrame()
	{//暂时保留
#ifndef _PSX_IDE_QT_
		if (m_pSmDbWriteThread != NULL)
		{
			m_pSmDbWriteThread->Exit();
		}
#endif
	}

	virtual void OnBeginSmDbWrite()
	{
#ifndef _PSX_IDE_QT_
		if (m_pSmDbWriteThread == NULL)
		{
			return;
		}

		m_pSmDbWriteThread->Post_WriteSmDB_Msg();
#endif
	}

	virtual void ReadCapBuffer(CFrameMemBuffer *pBuffer, CXMemBufferBse *pDestBuffer)
	{
#ifndef _PSX_IDE_QT_
		m_pCapFrameDbFileClient->ReadCapBuffer(pBuffer, pDestBuffer);
#endif
	}

	void SetDvmDevice(CDvmDevice *pDevice);
	void AttachDatasets();
	void InitSVDatasetAmpAng_MUTest();//对合并单元测试数据集,增加对应电压电流幅值、相位的关联,

	CXSmMemBufferMngr *m_pFrameMemBufferMngr;
	CCapDeviceMngr m_oCapDeviceAll;  //检测、探测到的全部装置
	CCapDeviceMngr m_oRecordDevice; //录波的装置
	CCapDeviceChRecordMngr m_oCapDeviceChRecordMngr; //抓包波形显示通道管理，以及RecordTest
	CRecordTestCalThread *m_pRecordTestCalThread; 

	CDvmDevice *m_pDvmDevice;
	CProtocol61850 *m_pProtocol61850;
	double m_dTimeFirstValue;
	double m_dTimeMaxValue;
	double m_dTimeMinValue;
	double m_dTimeCurrValue;
	int         m_nFirstDataFlag;
	BOOL m_bIsZeroDriftTest;
	double m_dZeroDrift_Un;
	double m_dZeroDrift_In;
	//zhouhj 2023.10.13 删除,改为自动计算方式
//	double m_dDelayCompens_NoPPS;//无PPS模式下的延时补偿

	CString m_strDatasetMapID_MUTestCB;//20220920 zhouhj SV映射数据集 之前固定为dsSV1,修改为与当前选择的控制块保存一致

protected:
#ifdef _XSmartCap_use_SmDb_
	CSmDbWriteThread *m_pSmDbWriteThread;

	//报文
	CSmDbConfig m_oSmDbConfig; //历史报文索引配置文件
	CCapFrameDbFile *m_pCapFrameDbFileServer;
	CCapFrameDbArea *m_pCapFrameDbFileClient; //2020-06-12  lijunqing
#endif

	//索引表

//lijunqing 2020-6-17  将杨一军写在CProtocol61850的代码移植到此处
//CProtocol61850功能单一，属于规约解析的部分，测试仪配置的代码位于CProtocol61850不合理
protected:
	CIecCfgDevice *m_pIecCfgDevice;

public:
	void UpdateUI_Paras(BOOL bUpdateZeroDriftByUIValue);//更新电压电流参数  20220822 zhouhj 参数1为是否根据电压电流值,更新是否为零漂
	void InitZeroDriftBy6U6I();//根据当前输出电压电流,自动设置为是否为零漂
	void SetIecCfgDevice(CIecCfgDevice *pIecCfgDevice){	m_pIecCfgDevice = pIecCfgDevice;	}
	void AddCapDevice(CIecCfgDataBase *pDatasBase);//2024-2-5 zhouyangyong通过配置文件增加单个设备
	void AddCapDevices(CIecCfgDatasMngr *pDatasMngr);
	void AddCapDevices_BySmvInGin(CIecCfgDatasMngr *pDatasMngr);
	void AddCapDevices(CIecCfgDatasBase *pDatasBase);
	void LoadCapDevices(CIecCfgDevice *pIecCfgDevice);
	CIecCfgDatasMngr* GetDatasMngr(const CString& strIecfgDataID);

	BOOL IsAppIDSame(CIecCfgDataBase *pDataBase);
    void RemoveCapDevices();

	void UpdateCapDevicesRecordSmvChRates();//20220612 根据当前SMV通道的通道类型及当前是否显示一次值,更新对应通道的比率
	void UpdateAfterMUChsSet();//2023.6.25 zhouhj 在合并单元接收通道选择、准确级修改后,或者变比修改后进行更新
	CCapDeviceBase* GetMUTestCapDevice();

public:
	//更新DvmDevice的数据  lijunqing 2020-6-17
	void UpdateDvmDeviceDatas();
	//void UpdateDvmDeviceDatas_RecordTest();
	void UpdateDvmDeviceDatas_Analysis();
	void UpdateDvmDeviceDatas_SvInst(const CString &strSvChID);
	void UpdateDvmDeviceDatas_SvInst(long *pLong, double dCoef, long nBegin, long nEnd, long &nDataIndex, double *pdLong);

	//初始化通道映射关系：波形计算和设备数据模型
	void Init_SV_Channels();
	void Init_GS_Channels();
	//加载配置文件，复位故障计算以及报文分析  lijunqing 2020-6-17
	void ResetRecord();
	BOOL UpdateMUTimeRlt(CDataGroup *pRtSycTime);
	void UpdateFirstCyclePoints();//根据当前输出电压电流，更新首周波输入波形
	void ClearMUTestResults();
	//zhouhj 2023.10.16 计算合并单元对时守时测试结果(无PPS模式)
	void CalMuTimeTestRlt_NoPPS();

protected:
	DWORD m_dwDvmSvChannels[MAX_RTVARIABLES];
	long m_nMaxSvChannelsMap;
	void InitSVDatasetAmpAng_MUTest(CDvmData *pCurrChData,CCapDeviceSmvCh *pDevCh);//对合并单元测试单个通道,增加对应电压电流幅值、相位的关联,
	BOOL GetChAmpAng(const CString &strChID, double *pdAmp,double *pdAng);

	void UpdateDvmDeviceDatas_RecordTest();
	void UpdateDvmDeviceDatas_RecordTest_SV();
	void UpdateDvmDeviceDatas_RecordTest_SV(CRtVariable *pVariable, CDvmData *pData);
	void UpdateDvmDeviceDatas_RecordTest_SV(RTCHANNELATTRVALUE *pAttrValues, CDvmData *pData,BOOL bIs92Datas);
	void UpdateDataValue(CExBaseList *pParent, const CString &strAttrID, double fValue,long nPrecision = 3);
	void UpdateDataValueAng(CExBaseList *pParent, const CString &strAttrID, double fValue);
	void UpdateDataValue(CDvmData *pData, long nHarmIndex, double fValue);
	void UpdateDvmDeviceDatas_RecordTest_THD();

	void UpdateDvmDeviceDatas_RecordTest_SV_Power();
	void UpdateDvmDeviceDatas_RecordTest_SV_Power(CDvmDataset *pDataset_Power);
	void UpdateDvmDeviceDatas_RecordTest_SV_Power(CDvmData *pPower);
	void UpdateDvmDeviceDatas_RecordTest_SV_Power_CH(CDvmValue *pCh, double &dP, double &dQ, double &dW, double &dCoef);
	void UpdateDvmDeviceDatas_RecordTest_SV_CH_Attr(CDvmValue *pCh, double &dMag, double &dAng, double &dFreq);

	void UpdateDvmDeviceDatas_RecordTest_SV_AD();//20220610 //根据之前计算的通道幅值、相位、频率,计算双AD相关数值
	void UpdateDvmDeviceDatas_RecordTest_SV_AD(CDvmDataset *pDataset_AD);
	void UpdateDvmDeviceDatas_RecordTest_SV_AD(CDvmData *pData_AD);
	
	void UpdateDvmDeviceDatas_RecordTest_SV_Vector();
	void UpdateDvmDeviceDatas_RecordTest_SV_Vector(CDvmDataset *pDataset);
	void UpdateDvmDeviceDatas_RecordTest_SV_Vector(CDvmData *pVector);

	void ResetRecord_RecordTest();
	void ResetRecord_Analysis();
	void ClearDatasetsMap();//在删除LdDevice的同时,清除数据集的关联指针
	double GetCurrChAngValue(long *pnChType,long *pnChAngType,int nChIndex);
	

public:
	//一次性定义各种相关的数据集，数据集ID常量定义在CapDeviceChBase.h
	CDvmDataset *m_pDataset_MUTestCB;//合并单元测试,指定控制块
	CDvmDataset *m_pDataset_Discrete;//SMV离散度;mym 20202-6-19
	CDvmDataset *m_pDataset_THD;
	CDvmDataset *m_pDataset_SVErr;//采样值报文异常模拟;mym 20202-6-19
	CDvmDataset *m_pDataset_GSErr;//GOOSE报文异常模拟;mym 20202-6-19
	CDvmDataset *m_pDataset_SV_PkgAnalyze;//SV一致性;mym 20202-6-19
	CDvmDataset *m_pDataset_GS_PkgAnalyze;//GS一致性;mym 20202-6-19
	CDvmDataset *m_pDataset_SVInst;       //SV瞬时值
	CDvmDataset *m_pDataset_SVDelay;       //SV延时
	CDvmDataset *m_pDataset_Report;       //REport
	CDvmDataset *m_pDataset_SVSyncDelt;       //SV同步差
	CDvmDataset *m_pDataset_GSSyncDelt;       //GS同步差
	CDvmDataset *m_pDataset_LinkState;       //链接状态
	CDvmDataset *m_pDataset_RcdStep6U6I ;       //302精度测试
	CDvmDataset *m_pDataset_RcdStepResponse ;       //302精度测试响应时间结果
	CDvmDataset *m_pDataset_IEDTest ;       //智能终端测试
	CDvmDataset *m_pDataset_Gin1;    //GOOSE订阅数据集，智能终端测试，默认只有一个GOOSE订阅控制块
	CDvmDataset *m_pDataset_Time;    //时间特性数据集；mym add 2020-11-07
	CDvmDataset *m_pDataset_MUTimeRlt;    //时间特性测试结果数据集,时间特性数据集中包括下发参数,此处增加单独测试结果数据集
	CDvmDataset *m_pDataset_CurrErrorRange; //当前测试项误差范围
	CDvmDataset *m_pDataset_ErrorRanges; //全部百分比的误差范围
	CDvmDataset *m_pDataset_SV_His;//历史数据
	CDvmDataset *m_pDataset_StateValueChangedRlt;//开出变位结果
	CDvmDataset *m_pDataset_TestFunSelect;//测试功能选择
	


protected:

	char  m_destIn[100];
	unsigned char m_destOut[50];
	//SOE  lijunqing 2020-6-20
	CExBaseCycleArray m_oSoeCycleArray;
	CExBaseCycleArray m_oBinCycleArray;

	void DvmFindDataset(const CString &strDatasetID, CDvmDataset **ppDataset);

	void UpdateDvmDeviceDatas_LinkState();

	void UpdateDvmDeviceDatas_PkgAnalyz_SV(CCapDeviceBase *pCapDevice);
	void UpdateDvmDeviceDatas_PkgAnalyz_SV_Single(CCapDeviceBase *pCapDevice,   long nSvIndex);
	void UpdateDvmDeviceDatas_PkgAnalyz_SV();

	void UpdateDvmDeviceDatas_PkgAnalyz_GS_Single(CCapDeviceBase *pCapDevice, long nGsIndex);
	void UpdateDvmDeviceDatas_PkgAnalyz_GS();

	void UpdateDvmDeviceDatas_Analysis_SVDelayErr();
	void UpdateDvmDeviceDatas_Analysis_SVDelayErr_Dvm(	long &nLinkCount,long &nHasCalCount);
	void UpdateDvmDeviceDatas_Analysis_SVDelayErr_Rcd(long nChCount);
	void UpdateDvmDeviceDatas_Analysis_SVSync();
	void UpdateDvmDeviceDatas_Analysis_GSSync();
	void UpdateDvmDeviceDatas_Analysis_MagPhaseFreq();

	void UpdateDvmDeviceDatas_Analysis_ComplexError();
	void Get_Value_B_P(const CString &strChnelTypeXML, const CString &strA_B_CType,
		_PARAMCALCOMPLEX &d_B, _PARAMCALCOMPLEX &d_P, double &d_Coef);
	BOOL Get_Value_B_P(long *pnChType,long *pnChAngType,int nChIndex
		, _PARAMCALCOMPLEX &d_B, _PARAMCALCOMPLEX &d_P, double &d_Coef);

	void UpdateDvmDeviceDatas_Analysis_Discrete();
	void UpdateDvmDeviceDatas_PkgError_92();
	void UpdateDvmDeviceDatas_PkgError_GS();
	void UpdateDvmDeviceDatas_PkgError_92(CCapDeviceBase *pCapDevice, long nSvIndex, EP_ANALYSIS_RESULT &oAnalysisResults);
	void UpdateDvmDeviceDatas_PkgError_GS(CCapDeviceBase *pCapDevice, long nSvIndex, EP_ANALYSIS_RESULT &oAnalysisResults);
	void Analysis_Add_Atrri_Error(CCapDeviceBase *pCapDevice,  CDvmData * pDataParent,   int  nGsOr92 , int nGsIndex,   int nInde);
	long FindGinMapByIndex(long nIndex);
	void GetGooseTime(double &dTime1, double &dTime2, long nMap);
	void UpdateDvmDeviceDatas_Analysis_GS_ChangeBit();// mym 2020-11-02 add ;
	void UpdateDvmDeviceDatas_Analysis_NoPps();

	CDvmData* Analysis_Add_Data(CDvmDataset *pDataset, const CString &strID);
	void Analysis_Add_Data(CDvmDataset *pDataset, const CString &strID, BYTE byteValue);
	void Analysis_Add_Data(CDvmDataset *pDataset, const CString &strID, long nValue);
	void Analysis_Add_Data(CDvmDataset *pDataset, const CString &strID, int nValue);
	void Analysis_Add_Data(CDvmDataset *pDataset, const CString &strID, double fValue);
	void Analysis_Add_Data(CDvmDataset *pDataset, const CString &strID, const CString &strValue);
	void Analysis_Add_Value(CDvmData *pData, const CString &strID, long nValue);
	void Analysis_Add_Value(CDvmData *pData, const CString &strID, CString strValue);
	CDvmValue* Analysis_Add_Value(CDvmData *pData, const CString &strID, double fValue,long nPrecision);

	void Analysis_Add_SVDelayValue(const CString &strSVCstcID, CCapDevice92 *pDevice92);//20220820 zhouhj 
	void Analysis_Add_SVDelayValue(const CString &strSVCstcID, CCapDevice6044 *pDevice6044);

	void Analysis_Add_SVHis(const CString &strSV_ID,const CString &strHisDataID,double dCurrValue,long nCurrTestCount);

	void UpdateDvmDeviceDatas_SOE();
	void UpdateDvmDeviceDatas_SOE(long nBegin, long nEnd);
	void UpdateDvmDeviceDatas_BIN();
	void UpdateDvmDeviceDatas_BIN(long nBegin, long nEnd);

	CString Get6u6iValue(CString strDstID,  int nCnt);	
	void  UpdateComplexErrorValue(double * pValue,   int nChnelCnt);
	void  GetU_IChnel(CString strName[],  CString strA_B_CType[], int& nChnelCnt);
	void  GetU_IParamValue(_PARAMCALCOMPLEX *pU_B,  _PARAMCALCOMPLEX *pI_B,  _PARAMCALCOMPLEX *pU_P, _PARAMCALCOMPLEX *pI_P);
	void  UpdateDvmDeviceDatas_Analysis_PhaseDelta();
	void UpdatePhaseDeltaValue(double * pValue,  double * pAngleValue,int nChnelCnt);
//	void UpdatePhaseValue(double * pValue,  int nChnelCnt);//20220823 zhouhj 删除统一采用UpdateValue_MUTest
	void UpdateValue_MUTest(double * pValue,  int nChnelCnt,CString strID);
	void  UpdateDvmDeviceDatas_Analysis_Response();
	void  GetOutputPhase(const CString &strU_IType, const CString &strA_B_CType, double & dPhase);
    void UpdateTestModeValue(double * pValue,  int nChnelCnt);
	void UpdateDCValue(double * pValue,  int nChnelCnt);
	void UpdateVlaue_HarmBase(CString strID);

	//cl20231010 离散度
    void Analysis_Add_Value_MaxValueRlt(CDvmValue *pDvmValue,double dStdMaxErrorValue);

	void CalCompErrValue(CCapDevice6044 *pDevice6044,double dCompRelAng);
//////////////////////////////////////////////////////////////////////////
//lijunqing 2020-6-23
public:
	void WriteRecordDataFile();

protected:
	void WriteRecordDataFile(DWORD *pdwAddrs, long nBegin, long nEnd, CFile &oFile);
	BOOL GetMUTimeDataRelAngle(__int64 nFirstRcdPointTime,__int64 nCurrAnalogZeroTime,long nNsCompTime,int nCurrTimeDataCh,
		double dFreq,double &dMUTimeDataRelAngle,double &dFirstPointCalAngle);


//2020-07-18  lijunqing  将数据集更新的功能做成一个单独的线程，避免主框架消息被堵住
public:
	void CreateUpdateDvmDeviceDatasThread();

	CTickCount32 g_oSVDelayTickCount;
protected:
	CWinThread *m_pUpdateDvmDatasThread;

	long m_nHasUpdateSVDelayData;

//2022-5  lijunqing
//创建IEC分析相关的数据集
public:
	CXKeyDB *m_pKeyDB;
	void IecAnalysis_AddDatasets();
	CDvmDataset* AddDataset_dsRcdStep6U6I();//20220811 添加dsRcdStep6U6I数据集,如果存在则不添加
	//MUTimeTest测试结果数据集
	void MUTimeTestRlt_AddDataset();
	void MUErrorRanges_AddDataset();//全部测试百分比误差范围设置
	void MUCurrErrorRange_AddDataset();//当前测试项误差范围设置
	
	void StateValueChangedRlt_AddDataset();//开出变位
	void UpdateStateValueChangedRltDatas();//更新开出变位次数、结论	
	void TestFunSelect_AddDataset();//测试功能选择
	void InitIsFunSelectValueByDataset();
	void UpdateDvmDeviceDatas_Analysis_HarmBase(CDvmValue *pDvmValue,double fActualValue,double fOutputValue,double fErrorValue);//chenling 2024.6.11谐波基波的误差
	QMap<CString, float> m_pHarmBaseLimitVlaueData; //存放谐波基波的误差限值
	void InitHarmBaseErrorLimit(BOOL bInit);

	void IecAnalysis_UpdateSvDatasetsPowerVector();//更新采样值数据集中的功率和矢量数据集内容
private:
	void IecAnalysis_AddDatasets(CDvmLogicDevice *pLogicDevice);

	//////////////////////////////////////////////////////////////////////////
	CDvmData* MUCurrErrorRange_AddData(CDvmDataset *pDsErrorRange,const CString &strDataName,const CString &strDataID);
	//SV
	void IecAnalysis_AddDataset_SV(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsSv);
	
	void IecAnalysis_AddDataset_SV_Power(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsSv,
		CXIecDatasetSmartMatch &oIecDatasetMatch,BOOL bUpdateDatas = FALSE);
	void IecAnalysis_AddDataset_SV_Power_P(CDvmData *pDataPower, CXIecDs_Group_UI_ABC *pUI_ABC);
	void IecAnalysis_AddDataset_SV_Power_P_Ch(CDvmData *pDataPower, CXIecDs_Group_UI *pUI, const CString &strIdPh);

	void IecAnalysis_AddDataset_SV_Vector(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsSv,
		CXIecDatasetSmartMatch &oIecDatasetMatch ,BOOL bUpdateDatas = FALSE);//最后一个参数判断是否更新数据集中的数据值
	void IecAnalysis_AddDataset_SV_Vector_ABC_X_List(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsVector, CDataGroup *pGroup_ABC_U_List, const CString &strType);
	void IecAnalysis_AddDataset_SV_Vector_ABC_X(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsVector, CXIecDs_Group_ABC *pABC_X, const CString &strType);


	void IecAnalysis_AddDataset_SV_AD(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsSv);
	CDvmData* IecAnalysis_AddDataset_SV_AD_Find(CDvmDataset *pDsSv, CDvmData *pData1);
	void IecAnalysis_AddDataset_SV_AD_Add(CDvmDataset *pDsAD, CDvmData *pData1, CDvmData *pData2, long nIndex);
	void IecAnalysis_AddDataset_SV_AD_NewVal(CDvmData *pDataAD, const CString &strName, const CString &strID);
	CDvmValue* IecAnalysis_AddDataset_SV_X_NewCh(CDvmData *pSrcData, CExBaseList *pParent, long nIndex);
	CDvmValue* IecAnalysis_AddDataset_SV_X_NewCh(CDvmData *pSrcData, CExBaseList *pParent, const CString &strID);
	CDvmValue* IecAnalysis_AddDataset_SV_X_NewCh(CExBaseList *pParent, const CString &strID);
	void IecAnalysis_AddDataset_SV_X_NewCh_Attr(CDvmData *pSrcData, CDvmValue *pCh, const CString &strAttrID);
	void IecAnalysis_AddDataset_SV_X_NewCh_Attr(CDvmValue *pCh, const CString &strAttrID);

	//2022-5-28  lijunqing  分析功能，控制块作为数据集的data对象，记录具体分析功能
	void IecAnalysis_AddDataset_Ctrl_ForData(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsSv
		, CDvmDataset **ppDsRet, CDvmData **ppDataRet
		, const CString &strDataSetID, const CString &strAnalyzeCfgFile);

	//2022-5-25  lijunqing
	void IecAnalysis_AddDataset_SV_PkgAnalyze(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsSv);
	void IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg(CDvmData *pSvData, CIecCfgDataBase *pIecCfgData);
	//zhouhj 2023.10.13
	void IecAnalysis_AddDataset_SV_His(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsSv);

	//20220820 zhouhj  SV延时
	void IecAnalysis_AddDataset_SV_Delay(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsSv);

	//2022-5-28  lijunqing  报文异常分析
	void IecAnalysis_AddDataset_SV_PkgError(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsSv);

	//////////////////////////////////////////////////////////////////////////
	//GOOSE
	void IecAnalysis_AddDataset_GS(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsGoose);
	void IecAnalysis_AddDataset_GS_PkgAnalyze(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsGoose);
	void IecAnalysis_AddDataset_GS_PkgAnalyze_Iecfg_Gin(CDvmData *pGsData, CIecCfgDataBase *pIecCfgData);
	void IecAnalysis_AddDataset_GS_PkgAnalyze_Iecfg_Gout(CDvmData *pGsData, CIecCfgDataBase *pIecCfgData);
	void IecAnalysis_AddDataset_GS_PkgError(CDvmLogicDevice *pLogicDevice, CDvmDataset *pGsData);

};

//2020-06-21  lijunqing  设备数据模型访问互斥对象，避免程序崩溃
extern CAutoCriticSection g_oCapDvmAutoCriticSection;
extern CString g_strListChannelGroupName[12];
extern CString g_strListChannelName[12];
extern CString g_strListChannelPh[12];
extern CString g_strListChannelHarm[12];
extern CString g_strListChannelHarmPh[12];
extern _61850CapMUErrorRanges g_oMuErrorRanges;//合并单元测试角差、比差、复合误差的合格判据
extern int g_nUseCustomMUTestRpt;//是否自定义测试报告,即设置测试报告使用的测试次数,自定义每次测试的间隔时间
extern int g_nMURptTestCount;//采自定义测试次数时,合并单元测试几次生成报告
extern float g_fMUTestTimeEach;//每次测试用时(s)
extern long g_nMuTimeTest_UseNoPPS;//合并单元对时守时测试时,采用无PPS模式
extern long g_nIsFirstCWTest;//标记当前是否为首周波测试模式,首周波测试开始测试后,需要记录前两个周波的数据
extern _61850CapMUErrorRanges g_oADMUErrorRanges;//admu自动测试角差、比差的合格判据
// extern CString g_strListHarmAmp[30];
/*extern CString g_strListHarmAng[30];*/
double cap_Cal_Analysis_ComplexError(double *pDatas, double dHardDelay, _PARAMCALCOMPLEX &d_B, _PARAMCALCOMPLEX &d_P, double &d_Coef);
double cap_Cal_Analysis_ComplexError_RelAng(double *pDatas, double dRelAng,  long nSmpRate,
											_PARAMCALCOMPLEX &d_B, _PARAMCALCOMPLEX &d_P, double &d_Coef);
double cap_MUAccuracy_GetVolChStdErrorValue(long nAccurLevel,long nErrorType);
double cap_MUAccuracy_GetCurrChStdErrorValue(long nAccurLevel,long nErrorType);

// 2024.5.16 chenling ADMU的误差限值
double cap_ADMUccuracy_GetVolChStdErrorValue(long nAccurLevel,long nErrorType);
double cap_ADMUccuracy_GetCurrChStdErrorValue(long nAccurLevel,long nErrorType);


static UINT UpdateDvmDeviceDatasThread(LPVOID pParam);
