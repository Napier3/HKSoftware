//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDataMngrGlobal.cpp

#include "stdafx.h"
#include "IecCfgDataMngrGlobal.h"
#include "../../../Module/XLanguage/XLanguageResource.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
#include"../../../Module/API/GlobalConfigApi.h"


//#define _USE_Write_CH_FiberIndex_Config_Files

//////////////////////////////////////////////////////////////////////////
//CCfgDataMngrXmlRWKeys

CCfgDataMngrXmlRWKeys* CCfgDataMngrXmlRWKeys::g_pXmlKeys = NULL;
long CCfgDataMngrXmlRWKeys::g_nCFGRef = 0;
CString g_strGsChDtID_goose_in_ch         = _T("goose-in-ch"); //zhouhj 20220428 山东自动测试项目,需要根据被测装置类型切换显示通道映射

long g_nIecCfgSmvOut_60044MaxNum = IecCfg6044COM_OUT_MaxNum;
long g_nIecCfgSmvIn_60044MaxNum = IecCfg6044COM_IN_MaxNum;
long g_nIecCfgSmvOut_91_92MaxNum = IecCfgSmvOut_91_92MaxNum;
long g_nIecCfgGoutMaxNum = IecCfgGoutData_MaxNum;
long g_nIecCfgGinMaxNum = IecCfgGinData_MaxNum;

const CString g_strSmvCurrentRateID[SMV_RATE_MAX_NUM] = {SMV_RATEID_STR_IABC,SMV_RATEID_STR_PIABC,SMV_RATEID_STR_SIABC,SMV_RATEID_STR_TIABC
, SMV_RATEID_STR_IABC5,SMV_RATEID_STR_IABC6};

const CString g_strSmvVolRateID[SMV_RATE_MAX_NUM] = {SMV_RATEID_STR_UABCZ,SMV_RATEID_STR_PUABCZ,SMV_RATEID_STR_SUABCZ,SMV_RATEID_STR_TUABCZ
, SMV_RATEID_STR_UABCZ5,SMV_RATEID_STR_UABCZ6};

CCfgDataMngrXmlRWKeys::CCfgDataMngrXmlRWKeys()
{
	m_strCIecCfgSmvRatesKey = L"smv-rates";
	m_strCIecCfgSmvRateKey = L"smv-rate";
	m_strCIecCfgAnalogChKey = L"ch-analog";
	m_strCIecCfgDataAnalogKey = L"cfg-analog";
	m_strCIecCfgChsAnalogKey = L"chs";
	m_strCIecCfgSystemConfigKey = L"sys-config";
	m_strCArtAmpDigdatasKey = L"dig-datas";
	m_strCArtAmpDigdataKey = L"dig-data";
	m_strSValueKey = L"S";
	m_strQValueKey = L"Q";
	m_strCIecCfg91StateWordMngrKey = L"state-word-mngr";
	m_strCIecCfg91StateWordBitKey = L"bit";
	m_strCIecCfg91StateWordKey = L"state-word";
	m_strCIecCfg91StatusDataSetChKey = L"ch";
	m_strCIecCfgChsGoutKey = L"chs";
	m_strCIecCfgChsGinKey = L"chs";
	m_strCIecCfgChs6044Key = L"chs";
	m_strCIecCfgChs91Key = L"chs";
	m_strCIecCfgChs92Key = L"chs";
	m_strCIecCfgChs92InKey = L"chs";
	m_strCIecCfgChsBaseKey = L"chs";
	m_strCIecCfgDatasMngrKey = L"cfg-datas-mngr";
	m_strCIecCfgDeviceKey = L"cfg-device";
	m_strCIecCfgDatasGoutKey = L"cfg-gouts";
	m_strCIecCfgDatasGinKey = L"cfg-gins";
	m_strCIecCfgDatasAnalogKey = L"cfg-analogs";
	m_strCIecCfgDatasSMVKey = L"cfg-smvs";
	m_strCIecCfgDatasSmvInKey = L"cfg-smvs-in";
	m_strCIecCfgGoutChKey = L"ch-gout";
	m_strCIecCfgDataGoutKey = L"cfg-gout";
	m_strCIecCfgGinChKey = L"ch-gin";
	m_strCIecCfgDataGinKey = L"cfg-gin";
	m_strCIecCfg6044ChKey = L"ch-6044";
	m_strCIecCfg6044CommonChKey = L"ch-6044-common";
	m_strCIecCfg6044CommonChInKey = L"ch-6044-common-in";
	m_strCIecCfgData6044Key = L"cfg-6044";
	m_strCIecCfgData6044CommonKey = L"cfg-6044-common";
	m_strCIecCfgData6044CommonInKey = L"cfg-6044-common-in";
	m_strCIecCfgData2MKey = L"cfg-2m";
	m_strCIecCfgData2MInKey = L"cfg-2m-in";
	m_strCIecCfg91ChKey = L"ch-91";
	m_strCIecCfg91StatusDataSetKey = L"status-data-set";
	m_strCIecCfgData91Key = L"cfg-91";
	m_strCIecCfg92ChKey = L"ch-92";
	m_strCIecCfg92ChQualityKey = L"ch-92-Q";
	m_strCIecCfgData92Key = L"cfg-92";
	m_strCIecCfgData92InKey = L"cfg-92-in";
	m_strCIecCfgDataGooseChBaseKey = L"ch-goose";
	m_strCIecCfgGooseDataBaseKey = L"cfg-goose";
	m_strCIecCfgDataSmvChBaseKey = L"ch-smv";
	m_strCIecCfgSmvDataBaseKey = L"cfg-smv";
	m_strCIecCfgAdvanceExceptionKey = L"exception";
	m_strCIecCfgDatasBaseKey = L"cfg-datas";
	m_strCIecCfgDataChBaseKey = L"ch";
	m_strCIecCfgDataBaseKey = L"cfg-data";
	m_strUseFlagKey = L"use";
	m_strChannelNumKey = L"ch-num";
	m_strFiberIndexKey = L"fiber-index";
	m_strFiber2IndexKey = L"fiber2-index";
	m_strCtrlRefKey = L"ctrl-ref";
	m_strCfgDataViewStateKey = L"view-state";
	m_strIndexKey = L"index";
	m_strAppChIDKey = L"app-ch";
	m_strDevChIDKey = L"dev-ch";
	m_strMapDataIDKey = L"map-id";
	m_strDatasCountKey = L"data-count";
	m_strDatasUseKey = L"use";
	m_strExceptionTypeKey = L"type";
	m_strSerialNumErrKey = L"serial-num-err";
	m_strFrameLossGapKey = L"frm-loss-gap";
	m_strFrameLossPointsKey = L"frm-loss-points";
	m_strSynGapKey = L"syn-gap";
	m_strSynPointsKey = L"syn-points";
	m_strQualityGapKey = L"quality-gap";
	m_strQualityPointsKey = L"quality-points";
	m_strQualityValueKey = L"quality-value";
	m_strSerialJmpGapKey = L"serial-jmp-gap";
	m_strSerialJmpPointsKey = L"serial-jmp-points";
	m_strSerialJmpStepKey = L"serial-jmp-step";
	m_strFaultValGapKey = L"fault-val-gap";
	m_strFaultValPointsKey = L"fault-val-points";
	m_strFaultValRateKey = L"fault-val-rate";
	m_strExceptionFaultIntervalKey = L"fault-interval";
	m_strExceptionFaultCountKey = L"fault-count";
	m_strExceptionFaultValueKey = L"fault-value";
	m_strExceptionBeginIndexKey = L"exception-begin-index";
	m_strExceptionLimitKey = L"exception-limit";
	m_strExceptionCountKey = L"exception-count";
	m_strUNomKey = L"unom";
	m_strINomKey = L"inom";
	m_strFNomKey = L"fnom";
	m_strUNom2Key = L"unom2";
	m_strINom2Key = L"inom2";
	m_strICenterKey = L"icenter";
	m_strSampleRateKey = L"sample-rate";
	m_strAsduNumKey = L"asdu-num";
	m_strNoQualityKey = L"no-quality";
	m_strCoefKey = L"coef";
	m_strUseExceptionKey = L"use-exception";
	m_strDestAddressKey = L"addr-dest";
	m_strSrcAddressKey = L"addr-src";
	m_strAppIDKey = L"app-id";
	m_strPriorityKey = L"priority";
	m_strVIDKey = L"vid";
	m_strVersionKey = L"version";
	m_strGooseIdKey = L"goose-id";
	m_strDataSetKey = L"dataset";
	m_strDataSetDescKey = L"dataset-desc";
	m_strgocbRefKey = L"gocb-ref";
	m_strgocbIEDKey = L"gocb-ied";
	m_strTestKey = L"test";
	m_strT0Key = L"T0";
	m_strT1Key = L"T1";
	m_strT2Key = L"T2";
	m_strT3Key = L"T3";
	m_strTGKey = L"TG";
	m_strTQKey = L"TQ";
	m_strDataTypeKey = L"data-type";
	m_strSVIDKey = L"svid";
	m_strSynKey = L"syn";
	m_strCTBitKey = L"ct-bit";
	m_strPTBitKey = L"pt-bit";
	m_strDelayKey = L"delay";
	m_strUseSampRateKey = L"use-samp-rate";
	m_strUseDataSetKey = L"use-dataset";
	m_strUseSampleTimeKey = L"use-smp-time";
	m_strUseRefreshTimeKey = L"use-refresh-time";
	m_strUseEncruptKey = L"use-encrupt";
	m_strVoltateRateKey = L"v-rate";
	m_strCurrRateKey = L"i-rate";
	m_strValidityKey = L"validity";
	m_strSourceKey = L"source";
	m_strOverflowKey = L"overflow";
	m_strOutOfRangeKey = L"out-of-range";
	m_strBadindexKey = L"bad-index";
	m_strOscillationKey = L"oscillation";
	m_strBreakdownKey = L"breakdown";
	m_strObsoletedataKey = L"obsolete-data";
	m_strIncompatibleKey = L"incompatible";
	m_strInaccurateKey = L"inaccurate";
	m_strOperatorLockKey = L"operatorLock";
	m_strUITypeKey = L"ui-type";
	m_strAddrExternalKey = L"addr-external";
	m_strDescExternalKey = L"desc-external";
	m_strIndexExternalKey = L"index-external";
	m_strQualityKey = L"quality";
	m_strLNNameKey = L"ln-name";
	m_strLDNameKey = L"ld-name";
	m_strStateWordKey = L"state-word";
	m_strUseStateDataSetKey = L"state-data-set";
	m_strDataSetNameKey = L"dataset-name";
	m_strSmprateKey = L"smp-rate";
	m_strValidKey = L"valid";
	m_strObsoleteDataKey = L"obsolete-data";
	m_strFaultKey = L"fault";
	m_strDiscordKey = L"discord";
	m_strLeapSecondKey = L"leap-second";
	m_strReliableClockKey = L"reliable-clock";
	m_strReferenceSourceSynKey = L"ref-src-syn";
	m_strChTypeKey = L"ch-type";
	m_strDelayTimeKey = L"delay-time";
	m_strTransSpeedKey = L"trans-speed";
	m_strINomPhKey = L"inom-ph";
	m_strINomNeutralKey = L"inom-neutral";
	m_strUNomPhKey = L"unom-ph";
	m_strUseMacSrcAddrKey = L"use-mac-src";
	m_strUseMacDestAddrKey = L"use-mac-dest";
	m_strUseAppIDKey = L"use-appid";
	m_strUseGocbRefKey = L"use-gocb-ref";
	m_strUseGooseIDKey = L"use-goose-id";
	m_strEntrustKey = L"entrust";
	m_strSmvTypeKey = L"smv-type";
	m_strEnableSMVKey = L"enable-smv";
	m_strEnableGINKey = L"enable-gin";
	m_strEnableGOUTKey = L"enable-gout";
	m_strValueKey = L"value";
	m_strDataKey = L"data";
	m_strWhichKey = L"which";
	m_strMaxOutKey = L"max-out";
	m_strOffsetKey = L"offset";
	m_strUnitKey = L"unit";
	m_strDigFlagKey = L"dig-flag";
	m_strFiberFlagKey = L"fiber-flag";
	m_strProtocalFlagKey = L"protocal-flag";
	m_strTypeFlagKey = L"type-flag";
	m_strTypeFlagValueKey = L"type-flag-val";
	m_strChannelFlagKey = L"channel-flag";
	m_strDigWhichKey = L"dig-witch";
	m_strDigMaxOutKey = L"dig-max-out";
	m_strDigOffsetKey = L"dig-offset";
	m_strDefaultCfgFileKey = L"default-cfg-file";
	m_strLaIecCfgFileKey = L"last-cfg-file";
	m_strUseDebugKey = L"debug-state";
	m_strAutoSetUIChIndexKey = L"auto-set-ui-ch-index";
	m_strPrimNomKey = L"prim-nom";
	m_strSecNomKey = L"sec-nom";
	m_strOutputKey = L"output";

	m_strPriValueKey = L"prim-value"; //last-cfg-file
	m_strSecValueKey = L"sec-value"; //prim
	m_strAnaValueKey = L"ana-value"; //output

	m_strChecksumKey = L"checksum"; //
	m_strPolarityKey = L"polarity"; //

	m_strSendPortKey = L"send-port"; //
	m_strNdsComKey = L"nds"; //
	m_strLiveTimeKey = L"live-time"; //
	m_strAnalyzeKey = L"analyze"; //
	m_strRateKey = L"rate";
	m_strCodeValueKey = L"code-value";
	m_strMeasCurrCodeValueKey = L"meas-curr-code-value";
	m_strPrimValueKey = L"prim-value";
	m_strAliasNameKey = L"alias-name";

	m_strIcdFileKey = L"icd-file";
	m_strGinChMapFileNameKey = L"gin-ch-mapfile-name";
	m_strDateKey = L"date";
	m_strXscdFileKey = L"xscd-file";

	m_strIecCfgKey=L"ieccfg";
	m_strIecAbstrKey=L"scd-src-file";

	m_strKey_iedStr=L"iedStr";
	 m_strKey_iedExtName=L"iedExtName";
	 m_strKey_nChnRefCount=L"nChnRefCount";
	 m_strKey_ldName_own=L"ldName_own";
	 m_strKey_lnName_own=L"lnName_own";
	m_strKey_scl_datset_own=L"scl_datset_own";
	 m_strKey_apName_own=L"apName_own";

	m_strKey_fcda_map=L"fcda_map";
	m_strKey_fcda_type=L"fcda_type";
	 m_strKey_fcda_lndesc=L"fcda_lndesc";
	 m_strKey_fcda_dodesc=L"fcda_dodesc";
	 m_strKey_fcda_name=L"fcda_name";

	 m_strKey_lnName_own=L"lnName_own";
	 m_strKey_fcda_desc=L"fcda_desc";
	 m_strKey_outIndex=L"outIndex";
	 m_strKey_inLNDesc=L"inLNDesc";
	 m_strKey_inDODesc=L"inDODesc";
	 m_strKey_inDADesc=L"inDADesc";
	 m_strKey_fcda_dodesc=L"fcda_dodesc";
	 m_strKey_inIndex=L"inIndex";
	 m_strKey_inPath=L"inPath";
	 m_strKey_outPath=L"outPath";


      m_strCtrlGsKey=L"CtrlGs";//CSclCtrlGs
	 m_strKey_gocbref=L"gocbref";
	 m_strKey_gocbref_path=L"gocbref_path";
	 m_strKey_scl_gcb_confRev=L"scl_gcb_confRev";
	 m_strKey_scl_gcb_APPID=L"scl_gcb_APPID";
	 m_strKey_scl_gse_APPID=L"scl_gse_APPID";
	 m_strKey_scl_gse_VLANID=L"scl_gse_VLANID";
	 m_strKey_scl_gse_VLANPRI=L"scl_gse_VLANPRI";
	 m_strKey_scl_gse_MinTime=L"scl_gse_MinTime";
	 m_strKey_scl_gse_MaxTime=L"scl_gse_MaxTime";

	 m_strKey_m_nSelect=L"m_nSelect";//CSclCtrlBase
	 m_strKey_ldName=L"ldName";
	 m_strKey_lnName=L"lnName";
	 m_strKey_scl_datset=L"scl_datset";
	 m_strKey_scl_datset_path=L"scl_datset_path";
	 m_strKey_apName=L"apName";
	 m_strKey_scl_dataset_desc=L"scl_dataset_desc";
	 m_strKey_strMac=L"strMac";
	 m_strKey_m_nChnCount=L"scl_m_nChnCount";


	 m_strKey_scl_svcb_smpRate=L"scl_svcb_smpRate";//CSclCtrlSmv
	 m_strKey_scl_svcb_smvID=L"scl_svcb_smvID";
	 m_strKey_scl_svcb_nofASDU=L"scl_nofASDU";
	 m_strKey_scl_svcb_confRev=L"svcb_confRev";
	 m_strKey_scl_smv_APPID=L"scl_smv_APPID";
	 m_strKey_scl_smv_VLANID=L"scl_smv_VLANID";
	 m_strKey_scl_smv_VLANPRI=L"scl_smv_VLANPRI";

	 m_strCSclSvInChKey=L"ch-smvin";//SvIn通道
	 m_strCSclCtrlSvInKey=L"smv-in";//SvIn
	 m_strCSclCtrlsSvInKey=L"smv-ins";//SvIn

	 m_strCSclSvOutChKey=L"ch-svout";//SvOut通道
	 m_strCSclCtrlSvOutKey=L"smv-out";//SvOut
	 m_strCSclCtrlsSvOutKey=L"smv-outs";//SvOut

	 m_strCSclGsInChKey=L"ch-gsin";//GsIn通道
	 m_strCSclCtrlGsInKey=L"gs-in";//GsIn
	 m_strCSclCtrlsGsInKey=L"gs-ins";//GsIn

	 m_strCSclGsOutChKey=L"ch-gsout";//GsOut通道
	 m_strCSclCtrlGsOutKey=L"gs-out";//GsOut
	 m_strCSclCtrlsGsOutKey=L"gs-outs";//GsOut

	  m_strKey_test_men=L"test-men";
	  m_strKey_model_test=L"model-test";
	  m_strKey_vcnln_test=L"vcnln-test";
	  m_strKey_macro_test=L"macro-test";
	  m_strCIecStationKey=L"station";

	  m_strCSclIedKey=L"ied";
	  m_strCSclIedRefKey=L"ied-ref";
	  m_strCSclBayVLevelKey=L"bay-v-level";
	  m_strCSclBayKey=L"Bay";

	  m_strIedTypeKey=L"ied-type";
	   m_strIedTypeLabelKey=L"ied-typeLabel";
	  m_strIedIPKey=L"ip";
	  m_strIedIPSUBNETKey=L"ip-subnet";
	  m_strIedIPGATEWAYKey=L"ip_gateway";
	  m_strIedTypeIDKey=L"ied-type-id";
	  m_strManufacturerKey=L"manufacturer";

	  m_strSmpCntType=  L"smp-cnt-type";
	  m_strSampleDataLen=L"sample-data-len";
	  m_strBlockType=L"block-type";
	  m_strSCP=L"SCP";
	  m_strSCM=L"SCM";
	  m_strSV=L"SV";
	  m_strBaudRate=L"baud-rate";
	  m_strInomProt=L"inom-prot";
	  m_strInomMeas=L"inom-meas";
	  m_strDcVol=L"dc-vol";
	  m_strDcCur=L"dc-cur";
	  m_strDcNeutralVol=L"dc-neutral-vol";
	  m_strDcVolPrim=L"dc-vol-prim";
	  m_strDcCurPrim=L"dc-cur-prim";
	  m_strDcNeutralVolPrim=L"dc-neutral-vol-prim";
	  m_strProtocolIDKey=L"protocol-id";
	  m_strChLenth = L"ch-lenth";

	m_strCIecCfgDatasSMVInputKey = L"cfg-smvInput";
	m_strCIecCfg92DoDescKey = L"Do-desc";
	m_strCIecCfgAccuracyLevelKey = L"accuracy-level";
	m_strCIecCfg92dUValKey = L"dU-Val";
	m_strCIecCfg92ChInKey = L"ch-92In";//ch-92In



	m_strCDataTypeTmpsKey = L"DataTypeTemplates"; //
	m_strCLNodeTypeKey = L"LNodeType"; //
	m_strCDOTypeKey = L"DOType"; //
	m_strCDATypeKey = L"DAType"; //
	m_strCEnumTypeKey = L"EnumType"; //

	m_strCDODetailKey = L"DODetail"; //
	m_strCDADetailKey = L"DADetail"; //
	m_strCBDADetailKey = L"BDADetail"; //
	m_strCEnumValKey = L"EnumVal"; //

	m_strLnClassKey = L"lnClass"; //
	m_strCDCKey = L"cdc";

	m_strObjTypeKey = L"objType"; //
	m_strSAddrKey = L"sAddr"; //
	m_strBTypeKey = L"bType"; //
	m_strValKindKey = L"valKind"; //
	m_strCountKey = L"count"; //
	m_strFCKey = L"fc"; //
	m_strSGroupKey = L"sGroup"; //sGroup

	m_strOrdKey = L"ord"; //

	m_strKey_LDdesc = L"LDdesc";//LDdesc
	m_strKey_ExLDdesc = L"ExLDdesc";//ExLDdesc
	m_strKey_ExIedDesc = L"ExIedDesc";//ExIedDesc

	m_strKey_inputRef_cdc = L"inputRef_cdc";//inputRef_cdc
	m_strKey_inputRef_type = L"inputRef_type";//inputRef_type

	m_strKey_GinPath = L"gin_path";   //gin_path

	m_strCIecCfgFiberParaKey = L"fiber-para";//zhouhj 20210315 单机软件参数设置
	m_strCIecCfgFiberParasKey = L"fiber-paras";
	m_strCIecCfgFiberParasInKey = L"fiber-paras-in";
	m_strCIecCfgPrimRateKey = L"prim-rate";
	m_strCIecCfgPrimRatesKey = L"prim-rates";
	m_strCIecCfgPrimRatesInKey = L"prim-rates-in";
	m_strCIecCfgSysParasKey = L"sys-paras";
	m_strPkg_Send_TypeKey = L"pkg-send-type";
	m_strSec_SynKey = L"sec-syn";
	m_strBcode_LogicKey = L"bcode-logic";
	m_strIec1588_TypeKey = L"iec1588-type";
	m_strPrim_ParasKey = L"prim-paras";
	m_strPrim_OutputKey = L"prim-output";
	m_strPrim_ValueKey = L"prim-value";
	m_strSecond_ValueKey = L"second-value";
	m_strFT3_ProtocolIDKey =L"ft3-protocol-id";
	m_strFT3_CRCTypeKey =L"ft3-crctype";
}

CCfgDataMngrXmlRWKeys::~CCfgDataMngrXmlRWKeys()
{
}

CCfgDataMngrXmlRWKeys* CCfgDataMngrXmlRWKeys::Create()
{
	g_nCFGRef++;

	if (g_nCFGRef == 1)
	{
		g_pXmlKeys = new CCfgDataMngrXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CCfgDataMngrXmlRWKeys::Release()
{
	g_nCFGRef--;

	if (g_nCFGRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CCfgDataMngrConstGlobal

long CCfgDataMngrConstGlobal::g_nGlobalRef = 0;
CCfgDataMngrConstGlobal* CCfgDataMngrConstGlobal::g_pGlobal = NULL;


CCfgDataMngrConstGlobal::CCfgDataMngrConstGlobal()
{

	//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()
	InitGlobal();
}

CCfgDataMngrConstGlobal::~CCfgDataMngrConstGlobal()
{
}

CCfgDataMngrConstGlobal* CCfgDataMngrConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CCfgDataMngrConstGlobal();
	}

	return g_pGlobal;
}

void CCfgDataMngrConstGlobal::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

// #define _WRITE_DATATYPE_XLANGFILE

void CCfgDataMngrConstGlobal::InitGlobal()
{
	CString strPath;

	//数据类型文件加载
	strPath = _P_GetConfigPath();
	strPath += CFG_IECCFG_DATATYPES_FILE;
	BOOL bRet = m_oIecRtdDataTypes.Open(strPath, CDataMngrXmlRWKeys::g_pXmlKeys);

	if (bRet)
	{
		ValidAddDataTypes();//验证新添加的数据类型是否存在,如果不存在,则添加对应的数据类型
	}
	else
	{
		Init_Smv92ChDataType();  //_T("Smv92ChDataType");
		Init_Smv91ChDataType();  //_T("Smv91ChDataType");
		Init_Smv6044ChDataType();  //_T("Smv6044ChDataType");
		Init_SmvCommon6044ChDataType();//_T("SmvCommon6044ChDataType");
		Init_SmvCommon6044DCChDataType();//_T("SmvCommon6044DCChDataType");
		Init_SmvCommon6044ChInDataType();//_T("SmvCommon6044ChInDataType");
		// 	void Init_SmvChDataType_Val_Vol();  //_T("Vol");
		// 	void Init_SmvChDataType_Val_Curr();  //_T("Curr");
		// 	void Init_SmvChDataType_Val_CurrProt();  //_T("Curr");
		// 	void Init_SmvChDataType_Val_CurrMeasure();  //_T("CurrMeasure");
		// 	void Init_SmvChDataType_Val_UTCTime();  //_T("UTCTime");

		Init_SmvChAngType();  //iecfg_SmvChAngType
		Init_SmvAppChDataType();  //_T("SmvAppChDataType");
		Init_SmvAppChDataType_U();  //_T("SmvAppChDataType_U");
		Init_SmvAppChDataType_I();  //_T("SmvAppChDataType_I");
		Init_SmvAppChDataType_T();  //_T("SmvAppChDataType_T");

		Init_SmvInAppChAccLevelDataType_U();
		Init_SmvInAppChAccLevelDataType_I();

		Init_SclCtrlAppDataType_Goose();  //_T("SclCtrlAppDataType_Goose");
		Init_SmvAppChDataType_DCU();
		Init_SmvAppChDataType_DCI();
//		Init_SmvAppChDataType_NeutralU();
		Init_SmvAppChDataType_StateValue();
		Init_SmvAppChDataType_Other();

		Init_SmvAppChDataType_6U();  //_T("SmvAppChDataType_6U");
		Init_SmvAppChDataType_6I();  //_T("SmvAppChDataType_6I");

		Init_SmvChByteLenDataType();
		Init_BlockInx_2MDataType();
		Init_PkgType_2MDataType();

		// 	void Init_BOutChDataType();  //_T("BOutChDataType");
		// 	void Init_Cfg6044Speed();  //_T("Cfg6044Speed");
		Init_GooseChDataType();  //_T("GooseChDataType");
		Init_GoutAppChDataType();  //_T("GoutAppChDataType");
		Init_GinAppChDataType();  //_T("GinAppChDataType");

		Init_AppPortDataType_Fiber(MAX_FIBER_PORT_NUM);  //_T("AppFiberPort");
		Init_AppPortDataType_SmpByteNum();
		Init_AppPortDataType_SmpCntType();
		Init_AppSynDataType_Fiber();  //_T("AppSynMode");
		Init_AppTestSetDataType();  //_T("g_strAppTestSetDataType");

		Init_Quality_DataTypes(); 
		Init_goose_ch_DataTypes();

		Init_STFiberDataType();
		Init_LCFiberDataType();
		Init_TesterSubPubDataType();

		Init_STFiberInDataType();

		m_oIecRtdDataTypes.SaveXmlFile(strPath, CDataMngrXmlRWKeys::g_pXmlKeys);
	}

//	m_oIecRtdDataTypes.SaveXmlFile(strPath, CDataMngrXmlRWKeys::g_pXmlKeys);

#ifdef _WRITE_DATATYPE_XLANGFILE
	xlang_WriteResourceFile(&m_oIecRtdDataTypes, _T("Iec61850CfgDataType.xml"), CDataMngrXmlRWKeys::g_pXmlKeys);
#else
// 	CXLanguage oXLanguage;
// 	oXLanguage.xlang_Buid(&m_oIecRtdDataTypes);
// 
// 	xlang_TranslateByResourceFile(&m_oIecRtdDataTypes, _T("Iec61850CfgDataType.xml"), TRUE);
	//20161212  lijq
#ifndef NOT_USE_XLANGUAGE
	xlang_TranslateByResourceFileEx(&m_oIecRtdDataTypes, _T("Iec61850CfgDataType.xml"));
#endif
#endif

}
//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()
//	m_oFuncParaDataTypes.AddNew(g_pstrVariableType_CString, g_pstrVariableType_CString);

//定义全局常量，例如  static CString g_pstrVariableType_CString;

CDataTypes* CCfgDataMngrConstGlobal::GetIecRtdDataTypes()
{
	ASSERT (g_pGlobal != NULL);
	return &g_pGlobal->m_oIecRtdDataTypes;
}

CDataType* CCfgDataMngrConstGlobal::FindIecRtdDataType(const  CString &strDataTypeID)
{
	ASSERT (g_pGlobal != NULL);
	CDataType *pDataType = NULL;
	
	pDataType = (CDataType*)g_pGlobal->m_oIecRtdDataTypes.FindByID(strDataTypeID);
//	ASSERT(pDataType != NULL);

	if (pDataType == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("datatype \"%s\"is not in file\"%s\""), strDataTypeID.GetString(), CFG_IECCFG_DATATYPES_FILE.GetString());
	}

	return pDataType;
}


BOOL CCfgDataMngrConstGlobal::IsViewOnlyUsedInChs()
{
	ASSERT (g_pGlobal != NULL);

	if (g_pGlobal == NULL)
	{
		return FALSE;
	}

	return (g_pGlobal->m_nViewOnlyUsedInChs == 1);
}

BOOL CCfgDataMngrConstGlobal::SetViewOnlyUsedInChs(long nViewOnlyUsedInChs)
{
	ASSERT (g_pGlobal != NULL);

	if (g_pGlobal == NULL)
	{
		return FALSE;
	}

	g_pGlobal->m_nViewOnlyUsedInChs = nViewOnlyUsedInChs;

	return IsViewOnlyUsedInChs();
}

void CCfgDataMngrConstGlobal::UpdataAppPortDataType_FiberNum(long nFiberNum)
{
	if (g_pGlobal == NULL)
	{
		return;
	}

	CDataType *pDataType = (CDataType*)g_pGlobal->m_oIecRtdDataTypes.FindByID(_T("AppFiberPort"));

	if (pDataType == NULL)
	{
		g_pGlobal->Init_AppPortDataType_Fiber(nFiberNum);
		return;
	}

	if (nFiberNum<pDataType->GetCount())
	{
		while(nFiberNum<pDataType->GetCount())
		{
			pDataType->DeleteTail();
		}
	} 
	else
	{
		CString strFiberIndex,strFiberName,strFiberID;
		for (int nIndex = pDataType->GetCount();nIndex<nFiberNum;nIndex++)
		{
			strFiberIndex.Format(_T("%d"),nIndex);
			strFiberName.Format(_T("光口%d"),(nIndex+1));
			strFiberID.Format(_T("Fiber%s"),strFiberIndex.GetString());
			pDataType->AddNewValue(strFiberName, strFiberID, strFiberIndex);
		}
	}
}

void CCfgDataMngrConstGlobal::UpdataAppPortDataType_FT3Num(long nFT3Num)
{
	if (g_pGlobal == NULL)
	{
		return;
	}

	CDataType *pDataType = (CDataType*)g_pGlobal->m_oIecRtdDataTypes.FindByID(_T("AppFt3Port"));

	if (pDataType == NULL)
	{
		g_pGlobal->Init_AppPortDataType_Ft3(TRUE);
		//return;
	}

	if (nFT3Num<pDataType->GetCount())
	{
		while(nFT3Num<pDataType->GetCount())
		{
			pDataType->DeleteTail();
		}
	} 
	else
	{
		CString strFiberIndex,strFiberName,strFiberID;
		for (int nIndex = pDataType->GetCount();nIndex<nFT3Num;nIndex++)
		{
			strFiberIndex.Format(_T("%d"),nIndex);
			strFiberName.Format(_T("FT3_%d口"),(nIndex+1));
			strFiberID.Format(_T("Ft3_%s"),strFiberIndex.GetString());
			pDataType->AddNewValue(strFiberName, strFiberID, strFiberIndex);
		}
	}
}

void CCfgDataMngrConstGlobal::UpdataAppPortDataType_FT3InNum(long nFT3InNum)
{
	if (g_pGlobal == NULL)
	{
		return;
	}

	CDataType *pDataType = (CDataType*)g_pGlobal->m_oIecRtdDataTypes.FindByID(_T("AppFt3InPort"));

	if (pDataType == NULL)
	{
		g_pGlobal->Init_AppPortDataType_Ft3In(TRUE);
		//return;
	}

	if (nFT3InNum<pDataType->GetCount())
	{
		while(nFT3InNum<pDataType->GetCount())
		{
			pDataType->DeleteTail();
		}
	} 
	else
	{
		CString strFiberIndex,strFiberName,strFiberID;
		for (int nIndex = pDataType->GetCount();nIndex<nFT3InNum;nIndex++)
		{
			strFiberIndex.Format(_T("%d"),nIndex);
			strFiberName.Format(_T("FT3接收_%d口"),(nIndex+1));
			strFiberID.Format(_T("Ft3In_%s"),strFiberIndex.GetString());
			pDataType->AddNewValue(strFiberName, strFiberID, strFiberIndex);
		}
	}
}
void CCfgDataMngrConstGlobal::Update_GinAppChDataType()
{
	g_pGlobal->Init_GinAppChDataType();
}

long CCfgDataMngrConstGlobal::GetAppPortFT3Num_ST()
{
	if (g_pGlobal == NULL)
	{
		return 0;
	}

	CDataType *pDataType = (CDataType*)g_pGlobal->m_oIecRtdDataTypes.FindByID(_T("AppFt3Port"));

	if (pDataType == NULL)
	{
		return 0;
	}

	return pDataType->GetCount();
}

long CCfgDataMngrConstGlobal::GetAppPortFT3InNum_ST()
{
	if (g_pGlobal == NULL)
	{
		return 0;
	}

	CDataType *pDataType = (CDataType*)g_pGlobal->m_oIecRtdDataTypes.FindByID(_T("AppFt3InPort"));

	if (pDataType == NULL)
	{
		return 0;
	}

	return pDataType->GetCount();
}

long CCfgDataMngrConstGlobal::GetAppPortFiberNum_LC()
{
	if (g_pGlobal == NULL)
	{
		return 0;
	}

	CDataType *pDataType = (CDataType*)g_pGlobal->m_oIecRtdDataTypes.FindByID(_T("AppFiberPort"));

	if (pDataType == NULL)
	{
		return 0;
	}

	return pDataType->GetCount();
}

void CCfgDataMngrConstGlobal::UpdataDataType_BinExNum(long nBinExNum)
{
	if (g_pGlobal == NULL)
	{
		return;
	}

	CDataType *pDataType = (CDataType*)g_pGlobal->m_oIecRtdDataTypes.FindByID(iecfg_GinAppChDataType);

	if (pDataType == NULL)
	{
		pDataType = g_pGlobal->m_oIecRtdDataTypes.AddNew2(_T("开入量"), iecfg_GinAppChDataType);
	}

	if (pDataType->GetCount()<9)
	{
		pDataType->DeleteAll();
		pDataType->AddNewValue(_T("无"), _T("none"), _T("0"));
		pDataType->AddNewValue(_T("开入A"), _T("bin1"), _T("1"));
		pDataType->AddNewValue(_T("开入B"), _T("bin2"), _T("2"));
		pDataType->AddNewValue(_T("开入C"), _T("bin3"), _T("3"));
		pDataType->AddNewValue(_T("开入D"), _T("bin4"), _T("4"));
		pDataType->AddNewValue(_T("开入E"), _T("bin5"), _T("5"));
		pDataType->AddNewValue(_T("开入F"), _T("bin6"), _T("6"));
		pDataType->AddNewValue(_T("开入G"), _T("bin7"), _T("7"));
		pDataType->AddNewValue(_T("开入H"), _T("bin8"), _T("8"));
	}

	if (nBinExNum<(pDataType->GetCount()-9))
	{
		while(nBinExNum<(pDataType->GetCount()-9))
		{
			pDataType->DeleteTail();
		}
	} 
	else
	{
		CString strIndex,strName,strID;

		for (int nIndex = pDataType->GetCount() - 9;nIndex<nBinExNum;nIndex++)
		{
			strIndex.Format(_T("%d"),nIndex+9);
			strName.Format(_T("开入扩展%d"),(nIndex+1));
			strID.Format(_T("binex%d"),(nIndex+1));
			pDataType->AddNewValue(strName, strID, strIndex);
		}
	}
}

void CCfgDataMngrConstGlobal::UpdataDataType_BoutExNum(long nBoutExNum)
{
	if (g_pGlobal == NULL)
	{
		return;
	}

	CDataType *pDataType = (CDataType*)g_pGlobal->m_oIecRtdDataTypes.FindByID(g_strGsChDtID_goose_out_ch_single);

	if (pDataType == NULL)
	{
		pDataType = g_pGlobal->m_oIecRtdDataTypes.AddNew2(_T("开出量-单点"), g_strGsChDtID_goose_out_ch_single);
	}

	if (pDataType->GetCount()<9)
	{
		pDataType->DeleteAll();
		pDataType->AddNewValue(_T("---"), _T("v0"), _T("0"));
		int nIndex = 0;
		CString strName,strID,strIndex;

		for (nIndex=1;nIndex<=8;nIndex++)
		{
			strName.Format(_T("开出%d"),nIndex);
			strID.Format(_T("bout%d"),nIndex);
			strIndex.Format(_T("%d"),(nIndex+1));
			pDataType->AddNewValue(strName, strID,strIndex);
		}
	}

	if (nBoutExNum<(pDataType->GetCount()-9))
	{
		while(nBoutExNum<(pDataType->GetCount()-9))
		{
			pDataType->DeleteTail();
		}
	} 
	else
	{
		CString strIndex,strName,strID;

		for (int nIndex = pDataType->GetCount() - 9;nIndex<nBoutExNum;nIndex++)
		{
			strIndex.Format(_T("%d"),nIndex+10);
			strName.Format(_T("扩展开出%d"),(nIndex+1));
			strID.Format(_T("boutex%d"),(nIndex+1));
			pDataType->AddNewValue(strName, strID, strIndex);
		}
	}


	pDataType = (CDataType*)g_pGlobal->m_oIecRtdDataTypes.FindByID(g_strGsChDtID_goose_out_ch_double);

	if (pDataType == NULL)
	{
		pDataType = g_pGlobal->m_oIecRtdDataTypes.AddNew2(_T("开出量-双点"), g_strGsChDtID_goose_out_ch_double);
	}

	if (pDataType->GetCount()<9)
	{
		pDataType->DeleteAll();
		pDataType->AddNewValue(_T("---"), _T("v01"), _T("1"));//zhouhj 20210924单机软件默认不需要进行通道映射
		int nIndex = 0;
		CString strName,strID,strIndex;

		for (nIndex=1;nIndex<=8;nIndex++)
		{
			strName.Format(_T("开出%d"),nIndex);
			strID.Format(_T("bout%d"),nIndex);
			strIndex.Format(_T("%d"),(nIndex+3));
			pDataType->AddNewValue(strName, strID,strIndex);
		}
	}

	if (nBoutExNum<(pDataType->GetCount()-9))
	{
		while(nBoutExNum<(pDataType->GetCount()-9))
		{
			pDataType->DeleteTail();
		}
	} 
	else
	{
		CString strIndex,strName,strID;

		for (int nIndex = pDataType->GetCount() - 9;nIndex<nBoutExNum;nIndex++)
		{
			strIndex.Format(_T("%d"),nIndex+12);
			strName.Format(_T("扩展开出%d"),(nIndex+1));
			strID.Format(_T("boutex%d"),(nIndex+1));
			pDataType->AddNewValue(strName, strID, strIndex);
		}
	}
}

void CCfgDataMngrConstGlobal::Init_Smv92ChDataType()  //_T("Smv92ChDataType")
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("Smv92ChDataType"), _T("Smv92ChDataType"));
	pDataType->AddNewValue(_T("电流"), _T("Curr"), _T("0"));
	pDataType->AddNewValue(_T("电压"), _T("Vol"), _T("1"));
	pDataType->AddNewValue(_T("时间"), _T("UTCTime"), _T("2"));
}

void CCfgDataMngrConstGlobal::Init_SmvChAngType(BOOL bFindRepeat)  //_T("SmvChAngTypeI")
{
// 	if (bFindRepeat && (m_oIecRtdDataTypes.FindByID(_T("SmvChAngType")) != NULL))
// 	{
// 		return;
// 	}
	//dingxiaoya 20240103 按测试要求改为Ia1 Ua1等
	if (bFindRepeat && (m_oIecRtdDataTypes.FindByID(_T("SmvChAngTypeI")) != NULL) 
		&& (m_oIecRtdDataTypes.FindByID(_T("SmvChAngTypeU")) != NULL))
	{
		return;
	}

	/*CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("SmvChAngType"), _T("SmvChAngType"));*/
	CDataType *pDataTypeI = m_oIecRtdDataTypes.AddNew2(_T("SmvChAngTypeI"), _T("SmvChAngTypeI"));
	CDataType *pDataTypeU = m_oIecRtdDataTypes.AddNew2(_T("SmvChAngTypeU"), _T("SmvChAngTypeU"));
	CString strID,strNameI,strNameU;
	long nIndex = 0;

	for (int nGroupIndex = 1;nGroupIndex<=6;nGroupIndex++)
	{
		/*strName = _T("A相");*/
		strNameI = _T("Ia");
		strNameI.AppendFormat(_T("%ld"),nGroupIndex);
		strNameU = _T("Ua");
		strNameU.AppendFormat(_T("%ld"),nGroupIndex);
		strID.Format(_T("AngA%ld"),nGroupIndex);
		pDataTypeI->AddNewValue(strNameI, strID, nIndex);
		pDataTypeU->AddNewValue(strNameU, strID, nIndex);
		nIndex++;

		/*strName = _T("B相");*/
		strNameI = _T("Ib");
		strNameI.AppendFormat(_T("%ld"),nGroupIndex);
		strNameU = _T("Ub");
		strNameU.AppendFormat(_T("%ld"),nGroupIndex);
		strID.Format(_T("AngB%ld"),nGroupIndex);
		pDataTypeI->AddNewValue(strNameI, strID, nIndex);
		pDataTypeU->AddNewValue(strNameU, strID, nIndex);
		nIndex++;

		/*strName = _T("C相");*/
		strNameI = _T("Ic");
		strNameI.AppendFormat(_T("%ld"),nGroupIndex);
		strNameU = _T("Uc");
		strNameU.AppendFormat(_T("%ld"),nGroupIndex);
		strID.Format(_T("AngC%ld"),nGroupIndex);
		pDataTypeI->AddNewValue(strNameI, strID, nIndex);
		pDataTypeU->AddNewValue(strNameU, strID, nIndex);
		nIndex++;

		/*strName = _T("零序");*/
		strNameI = _T("I0");
		strNameI.AppendFormat(_T("%ld"),nGroupIndex);
		strNameU = _T("U0");
		strNameU.AppendFormat(_T("%ld"),nGroupIndex);
		strID.Format(_T("Ang0%ld"),nGroupIndex);
		pDataTypeI->AddNewValue(strNameI, strID, nIndex);
		pDataTypeU->AddNewValue(strNameU, strID, nIndex);
		nIndex++;
	}
}

void CCfgDataMngrConstGlobal::Init_Smv91ChDataType()  //_T("Smv91ChDataType")
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("Smv91ChDataType"), _T("Smv91ChDataType"));
	pDataType->AddNewValue(_T("电压"), _T("Vol"), _T("0"));
	pDataType->AddNewValue(_T("电流(保护)"), _T("Curr"), _T("1"));
	pDataType->AddNewValue(_T("电流(测量)"), _T("CurrMeasure"), _T("2"));

}

void CCfgDataMngrConstGlobal::Init_Smv6044ChDataType()  //_T("Smv6044ChDataType")
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("Smv6044ChDataType"), _T("Smv6044ChDataType"));
	pDataType->AddNewValue(_T("电压"), _T("Vol"), _T("0"));
	pDataType->AddNewValue(_T("电流(保护)"), _T("Curr"), _T("1"));
	pDataType->AddNewValue(_T("电流(测量)"), _T("CurrMeasure"), _T("2"));
	pDataType->AddNewValue(_T("时间"), _T("UTCUTCTime"), _T("3"));
}

void CCfgDataMngrConstGlobal::Init_SmvCommon6044ChDataType(BOOL bValid)  //_T("SmvCommon6044ChDataType")
{
	CDataType *pDataType = NULL;

	if (bValid)
	{
		pDataType = (CDataType*)m_oIecRtdDataTypes.FindByID(_T("SmvCommon6044ChDataType"));

		if (pDataType != NULL)
		{
			//判断当前的数量是否与最新的一致,如果不一致,则删除重新添加
			if (pDataType->GetCount() == 4)
			{
				return;
			}

			pDataType->DeleteAll();
		}
	}

	if (pDataType == NULL)
	{
		pDataType = m_oIecRtdDataTypes.AddNew2(_T("SmvCommon6044ChDataType"), _T("SmvCommon6044ChDataType"));
	}
	
// 	pDataType->AddNewValue(_T("直流电流"),iecfg_SmvChDataType_Val_DCCur , _T("0"));
// 	pDataType->AddNewValue(_T("直流电压"), iecfg_SmvChDataType_Val_DCVol, _T("1"));
//	pDataType->AddNewValue(_T("中性母线电压"), iecfg_SmvChDataType_Val_NeutralU, _T("2"));
	pDataType->AddNewValue(_T("交流电压"), iecfg_SmvChDataType_Val_Vol, _T("0"));
	pDataType->AddNewValue(_T("交流电流(保护)"), iecfg_SmvChDataType_Val_Curr, _T("1"));
	pDataType->AddNewValue(_T("交流电流(测量)"), iecfg_SmvChDataType_Val_CurrMeasure, _T("2"));
	pDataType->AddNewValue(_T("状态值"), iecfg_SmvChDataType_Val_StateValue, _T("3"));
	pDataType->AddNewValue(_T("其它"), iecfg_SmvChDataType_Val_Other, _T("4"));
}

void CCfgDataMngrConstGlobal::Init_SmvCommon6044DCChDataType(BOOL bValid)  //_T("SmvCommon6044DCChDataType")
{
	CDataType *pDataType = NULL;

	if (bValid)
	{
		pDataType = (CDataType*)m_oIecRtdDataTypes.FindByID(_T("SmvCommon6044DCChDataType"));

		if (pDataType != NULL)
		{
			//判断当前的数量是否与最新的一致,如果不一致,则删除重新添加
			if (pDataType->GetCount() == 7)
			{
				return;
			}

			pDataType->DeleteAll();
		}
	}

	if (pDataType == NULL)
	{
		pDataType = m_oIecRtdDataTypes.AddNew2(_T("SmvCommon6044DCChDataType"), _T("SmvCommon6044DCChDataType"));
	}

	pDataType->AddNewValue(_T("直流电流"),iecfg_SmvChDataType_Val_DCCur , _T("0"));
	pDataType->AddNewValue(_T("直流电压"), iecfg_SmvChDataType_Val_DCVol, _T("1"));
	//	pDataType->AddNewValue(_T("中性母线电压"), iecfg_SmvChDataType_Val_NeutralU, _T("2"));
	pDataType->AddNewValue(_T("状态值"), iecfg_SmvChDataType_Val_StateValue, _T("2"));
	pDataType->AddNewValue(_T("其它"), iecfg_SmvChDataType_Val_Other, _T("3"));
	pDataType->AddNewValue(_T("交流电压"), iecfg_SmvChDataType_Val_6Vol, _T("4"));
	pDataType->AddNewValue(_T("交流电流(保护)"), iecfg_SmvChDataType_Val_6CurrProt, _T("5"));
	pDataType->AddNewValue(_T("交流电流(测量)"), iecfg_SmvChDataType_Val_6CurrMeasure, _T("6"));
}

void CCfgDataMngrConstGlobal::Init_SmvCommon6044ChInDataType(BOOL bFindRepeat)  //_T("SmvCommon6044ChInDataType")
{
	CDataType *pDataType = (CDataType*)m_oIecRtdDataTypes.FindByID(_T("SmvCommon6044ChInDataType"));
	if (bFindRepeat && (pDataType!= NULL))
	{
		//判断当前的数量是否与最新的一致,如果不一致,则删除重新添加
		if (pDataType->GetCount() == 5)
		{
			return;
		}

		pDataType->DeleteAll();
	}

	if (pDataType == NULL)
	{
		pDataType = m_oIecRtdDataTypes.AddNew2(_T("SmvCommon6044ChInDataType"), _T("SmvCommon6044ChInDataType"));
	}

// 	pDataType->AddNewValue(_T("状态值"), iecfg_SmvChDataType_Val_StateValue, _T("0"));
// 	pDataType->AddNewValue(_T("其它"), iecfg_SmvChDataType_Val_Other, _T("1"));

	pDataType->AddNewValue(_T("交流电压"), iecfg_SmvChDataType_Val_Vol, _T("0"));
	pDataType->AddNewValue(_T("交流电流(保护)"), iecfg_SmvChDataType_Val_Curr, _T("1"));
	pDataType->AddNewValue(_T("交流电流(测量)"), iecfg_SmvChDataType_Val_CurrMeasure, _T("2"));
	pDataType->AddNewValue(_T("状态值"), iecfg_SmvChDataType_Val_StateValue, _T("3"));
	pDataType->AddNewValue(_T("其它"), iecfg_SmvChDataType_Val_Other, _T("4"));
}

// 
// void CCfgDataMngrConstGlobal::Init_SmvChDataType_Val_Vol()  //_T("Vol")
// {
// 
// }
// 
// void CCfgDataMngrConstGlobal::Init_SmvChDataType_Val_Curr()  //_T("Curr")
// {
// 
// }
// 
// void CCfgDataMngrConstGlobal::Init_SmvChDataType_Val_CurrProt()  //_T("Curr")
// {
// 
// }
// 
// void CCfgDataMngrConstGlobal::Init_SmvChDataType_Val_CurrMeasure()  //_T("CurrMeasure")
// {
// 
// }
// 
// void CCfgDataMngrConstGlobal::Init_SmvChDataType_Val_UTCTime()  //_T("UTCTime")
// {
// 
// }


void CCfgDataMngrConstGlobal::Init_SmvAppChDataType()  //_T("SmvAppChDataType")
{
	CString strConfigPath;
	strConfigPath = _P_GetConfigPath();
	strConfigPath += _T("smv-app-ch.xml");

	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("SmvAppChDataType"), _T("SmvAppChDataType"));

	if (IsFileExist(strConfigPath))
	{
		pDataType->OpenXmlFile(strConfigPath,CDataMngrXmlRWKeys::g_pXmlKeys);
		return;
	}

	pDataType->AddNewValue(_T("0"), _T("zero"), _T("0"));
	pDataType->AddNewValue(_T("Ua1"), _T("Ua1"), _T("1"));
	pDataType->AddNewValue(_T("Ub1"), _T("Ub1"), _T("2"));
	pDataType->AddNewValue(_T("Uc1"), _T("Uc1"), _T("3"));
	pDataType->AddNewValue(_T("3U0"), _T("U01"), _T("4"));
	pDataType->AddNewValue(_T("Ua2"), _T("Ua2"), _T("5"));
	pDataType->AddNewValue(_T("Ub2"), _T("Ub2"), _T("6"));
	pDataType->AddNewValue(_T("Uc2"), _T("Uc2"), _T("7"));
	pDataType->AddNewValue(_T("3U02"), _T("U02"), _T("8"));
	pDataType->AddNewValue(_T("Uz"), _T("Uz1"), _T("9"));
	pDataType->AddNewValue(_T("Ia1"), _T("Ia1"), _T("10"));
	pDataType->AddNewValue(_T("Ib1"), _T("Ib1"), _T("11"));
	pDataType->AddNewValue(_T("Ic1"), _T("Ic1"), _T("12"));
	pDataType->AddNewValue(_T("3I0"), _T("I01"), _T("13"));
	pDataType->AddNewValue(_T("Ia2"), _T("Ia2"), _T("14"));
	pDataType->AddNewValue(_T("Ib2"), _T("Ib2"), _T("15"));
	pDataType->AddNewValue(_T("Ic2"), _T("Ic2"), _T("16"));
	pDataType->AddNewValue(_T("3I02"), _T("I02"), _T("17"));
	pDataType->AddNewValue(_T("采样延时"), _T("t-delay"), _T("18"));
	pDataType->AddNewValue(_T("Ua3"), _T("Ua3"), _T("19"));
	pDataType->AddNewValue(_T("Ub3"), _T("Ub3"), _T("20"));
	pDataType->AddNewValue(_T("Uc3"), _T("Uc3"), _T("21"));
	pDataType->AddNewValue(_T("3U03"), _T("U03"), _T("22"));
	pDataType->AddNewValue(_T("Ua4"), _T("Ua4"), _T("23"));
	pDataType->AddNewValue(_T("Ub4"), _T("Ub4"), _T("24"));
	pDataType->AddNewValue(_T("Uc4"), _T("Uc4"), _T("25"));
	pDataType->AddNewValue(_T("3U04"), _T("U04"), _T("26"));
	pDataType->AddNewValue(_T("Ia3"), _T("Ia3"), _T("27"));
	pDataType->AddNewValue(_T("Ib3"), _T("Ib3"), _T("28"));
	pDataType->AddNewValue(_T("Ic3"), _T("Ic3"), _T("29"));
	pDataType->AddNewValue(_T("3I03"), _T("I03"), _T("30"));
	pDataType->AddNewValue(_T("Ia4"), _T("Ia4"), _T("31"));
	pDataType->AddNewValue(_T("Ib4"), _T("Ib4"), _T("32"));
	pDataType->AddNewValue(_T("Ic4"), _T("Ic4"), _T("33"));
	pDataType->AddNewValue(_T("3I04"), _T("I04"), _T("34"));
// 	pDataType->AddNewValue(_T("Uz2"), _T("Uz2"), _T("35"));//zhouhj 20210727  模块化测试仪只支持单个Uz,避免查找出错
// 	pDataType->AddNewValue(_T("Uz3"), _T("Uz3"), _T("36"));
// 	pDataType->AddNewValue(_T("Uz4"), _T("Uz4"), _T("37"));
	pDataType->AddNewValue(_T("Uab"), _T("Uab"), _T("38"));
	pDataType->AddNewValue(_T("Ubc"), _T("Ubc"), _T("39"));
	pDataType->AddNewValue(_T("Uca"), _T("Uca"), _T("40"));

	pDataType->AddNewValue(_T("Ua5"), _T("Ua5"), _T("41"));
	pDataType->AddNewValue(_T("Ub5"), _T("Ub5"), _T("42"));
	pDataType->AddNewValue(_T("Uc5"), _T("Uc5"), _T("43"));
	pDataType->AddNewValue(_T("3U05"), _T("U05"), _T("44"));
	pDataType->AddNewValue(_T("Ua6"), _T("Ua6"), _T("45"));
	pDataType->AddNewValue(_T("Ub6"), _T("Ub6"), _T("46"));
	pDataType->AddNewValue(_T("Uc6"), _T("Uc6"), _T("47"));
	pDataType->AddNewValue(_T("3U06"), _T("U06"), _T("48"));
	pDataType->AddNewValue(_T("Ia5"), _T("Ia5"), _T("49"));
	pDataType->AddNewValue(_T("Ib5"), _T("Ib5"), _T("50"));
	pDataType->AddNewValue(_T("Ic5"), _T("Ic5"), _T("51"));
	pDataType->AddNewValue(_T("3I05"), _T("I05"), _T("52"));
	pDataType->AddNewValue(_T("Ia6"), _T("Ia6"), _T("53"));
	pDataType->AddNewValue(_T("Ib6"), _T("Ib6"), _T("54"));
	pDataType->AddNewValue(_T("Ic6"), _T("Ic6"), _T("55"));
	pDataType->AddNewValue(_T("3I06"), _T("I06"), _T("56"));

#ifdef _USE_Write_CH_FiberIndex_Config_Files
	pDataType->SaveXmlFile(strConfigPath,CDataMngrXmlRWKeys::g_pXmlKeys);
#endif
}

void CCfgDataMngrConstGlobal::Init_SmvAppChDataType_U()  //_T("SmvAppChDataType_U")
{
	CString strConfigPath;
	strConfigPath = _P_GetConfigPath();
	strConfigPath += _T("smv-app-u-ch.xml");

	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("SmvAppChDataType_U"), _T("SmvAppChDataType_U"));

	if (IsFileExist(strConfigPath))
	{
		pDataType->OpenXmlFile(strConfigPath,CDataMngrXmlRWKeys::g_pXmlKeys);
		return;
	}

	pDataType->AddNewValue(_T("0"), _T("zero"), _T("0"));
	pDataType->AddNewValue(_T("Ua1"), _T("Ua1"), _T("1"));
	pDataType->AddNewValue(_T("Ub1"), _T("Ub1"), _T("2"));
	pDataType->AddNewValue(_T("Uc1"), _T("Uc1"), _T("3"));
	pDataType->AddNewValue(_T("3U0"), _T("U01"), _T("4"));
//	pDataType->AddNewValue(_T("Uz"), _T("Uz1"), _T("5"));
// 	pDataType->AddNewValue(_T("Uab"), _T("Uab"), _T("6"));  //zhouhj 20211021 无效通道映射,去除
// 	pDataType->AddNewValue(_T("Ubc"), _T("Ubc"), _T("7"));
// 	pDataType->AddNewValue(_T("Uca"), _T("Uca"), _T("8"));
	pDataType->AddNewValue(_T("Ua2"), _T("Ua2"), _T("9"));
	pDataType->AddNewValue(_T("Ub2"), _T("Ub2"), _T("10"));
	pDataType->AddNewValue(_T("Uc2"), _T("Uc2"), _T("11"));
	pDataType->AddNewValue(_T("3U02"), _T("U02"), _T("12"));
//	pDataType->AddNewValue(_T("Uz2"), _T("Uz2"), _T("13"));
	pDataType->AddNewValue(_T("Ua3"), _T("Ua3"), _T("14"));
	pDataType->AddNewValue(_T("Ub3"), _T("Ub3"), _T("15"));
	pDataType->AddNewValue(_T("Uc3"), _T("Uc3"), _T("16"));
	pDataType->AddNewValue(_T("3U03"), _T("U03"), _T("17"));
//	pDataType->AddNewValue(_T("Uz3"), _T("Uz3"), _T("18"));
	pDataType->AddNewValue(_T("Ua4"), _T("Ua4"), _T("19"));
	pDataType->AddNewValue(_T("Ub4"), _T("Ub4"), _T("20"));
	pDataType->AddNewValue(_T("Uc4"), _T("Uc4"), _T("21"));
	pDataType->AddNewValue(_T("3U04"), _T("U04"), _T("22"));
//	pDataType->AddNewValue(_T("Uz4"), _T("Uz4"), _T("23"));

	pDataType->AddNewValue(_T("Ua5"), _T("Ua5"), _T("24"));
	pDataType->AddNewValue(_T("Ub5"), _T("Ub5"), _T("25"));
	pDataType->AddNewValue(_T("Uc5"), _T("Uc5"), _T("26"));
	pDataType->AddNewValue(_T("3U05"), _T("U05"), _T("27"));
//	pDataType->AddNewValue(_T("Uz5"), _T("Uz5"), _T("28"));
	pDataType->AddNewValue(_T("Ua6"), _T("Ua6"), _T("29"));
	pDataType->AddNewValue(_T("Ub6"), _T("Ub6"), _T("30"));
	pDataType->AddNewValue(_T("Uc6"), _T("Uc6"), _T("31"));
	pDataType->AddNewValue(_T("3U06"), _T("U06"), _T("32"));
//	pDataType->AddNewValue(_T("Uz6"), _T("Uz6"), _T("33"));

#ifdef _USE_Write_CH_FiberIndex_Config_Files
	pDataType->SaveXmlFile(strConfigPath,CDataMngrXmlRWKeys::g_pXmlKeys);
#endif
}

void CCfgDataMngrConstGlobal::Init_SmvInAppChAccLevelDataType_U()  //iecfg_SmvInAppChAccLevelDataType_U
{
	CString strConfigPath;
	strConfigPath = _P_GetConfigPath();
	strConfigPath += _T("smv-acclevel-u-ch.xml");

	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(iecfg_SmvInAppChAccLevelDataType_U, iecfg_SmvInAppChAccLevelDataType_U);

	if (IsFileExist(strConfigPath))
	{
		pDataType->OpenXmlFile(strConfigPath,CDataMngrXmlRWKeys::g_pXmlKeys);
		return;
	}

	pDataType->AddNewValue(_T("保护级(3P)"), _T("Prot3P"), _T("0"));
	pDataType->AddNewValue(_T("保护级(6P)"), _T("Prot6P"), _T("1"));
	pDataType->AddNewValue(_T("测量级(0.1)"), _T("Meas0_1"), _T("2"));
	pDataType->AddNewValue(_T("测量级(0.2)"), _T("Meas0_2"), _T("3"));
	pDataType->AddNewValue(_T("测量级(0.5)"), _T("Meas0_5"), _T("4"));
	pDataType->AddNewValue(_T("测量级(1)"), _T("Meas1"), _T("5"));


#ifdef _USE_Write_CH_FiberIndex_Config_Files
	pDataType->SaveXmlFile(strConfigPath,CDataMngrXmlRWKeys::g_pXmlKeys);
#endif
}

void CCfgDataMngrConstGlobal::Init_SmvInAppChAccLevelDataType_I()  //iecfg_SmvInAppChAccLevelDataType_I
{
	CString strConfigPath;
	strConfigPath = _P_GetConfigPath();
	strConfigPath += _T("smv-acclevel-i-ch.xml");

	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(iecfg_SmvInAppChAccLevelDataType_I, iecfg_SmvInAppChAccLevelDataType_I);

	if (IsFileExist(strConfigPath))
	{
		pDataType->OpenXmlFile(strConfigPath,CDataMngrXmlRWKeys::g_pXmlKeys);
		return;
	}

	pDataType->AddNewValue(_T("保护级(5P30)"), _T("Prot5P30"), _T("0"));
	pDataType->AddNewValue(_T("保护级(5P)"), _T("Prot5P"), _T("1"));
	pDataType->AddNewValue(_T("保护级(10P)"), _T("Prot10P"), _T("2"));
	pDataType->AddNewValue(_T("测量级(0.1)"), _T("Meas0_1"), _T("3"));
	pDataType->AddNewValue(_T("测量级(0.2S)"), _T("Meas0_2S"), _T("4"));
	pDataType->AddNewValue(_T("测量级(0.2)"), _T("Meas0_2"), _T("5"));
	pDataType->AddNewValue(_T("测量级(0.5S)"), _T("Meas0_5S"), _T("6"));
	pDataType->AddNewValue(_T("测量级(0.5)"), _T("Meas0_5"), _T("7"));
	pDataType->AddNewValue(_T("测量级(1)"), _T("Meas1"), _T("8"));


#ifdef _USE_Write_CH_FiberIndex_Config_Files
	pDataType->SaveXmlFile(strConfigPath,CDataMngrXmlRWKeys::g_pXmlKeys);
#endif
}

void CCfgDataMngrConstGlobal::Init_SmvAppChDataType_I()  //_T("SmvAppChDataType_I")
{
	CString strConfigPath;
	strConfigPath = _P_GetConfigPath();
	strConfigPath += _T("smv-app-i-ch.xml");

	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("SmvAppChDataType_I"), _T("SmvAppChDataType_I"));

	if (IsFileExist(strConfigPath))
	{
		pDataType->OpenXmlFile(strConfigPath,CDataMngrXmlRWKeys::g_pXmlKeys);
		return;
	}

	pDataType->AddNewValue(_T("0"), _T("zero"), _T("0"));
	pDataType->AddNewValue(_T("Ia1"), _T("Ia1"), _T("1"));
	pDataType->AddNewValue(_T("Ib1"), _T("Ib1"), _T("2"));
	pDataType->AddNewValue(_T("Ic1"), _T("Ic1"), _T("3"));
	pDataType->AddNewValue(_T("3I0"), _T("I01"), _T("4"));
	pDataType->AddNewValue(_T("Ia2"), _T("Ia2"), _T("5"));
	pDataType->AddNewValue(_T("Ib2"), _T("Ib2"), _T("6"));
	pDataType->AddNewValue(_T("Ic2"), _T("Ic2"), _T("7"));
	pDataType->AddNewValue(_T("3I02"), _T("I02"), _T("8"));
	pDataType->AddNewValue(_T("Ia3"), _T("Ia3"), _T("9"));
	pDataType->AddNewValue(_T("Ib3"), _T("Ib3"), _T("10"));
	pDataType->AddNewValue(_T("Ic3"), _T("Ic3"), _T("11"));
	pDataType->AddNewValue(_T("3I03"), _T("I03"), _T("12"));
	pDataType->AddNewValue(_T("Ia4"), _T("Ia4"), _T("13"));
	pDataType->AddNewValue(_T("Ib4"), _T("Ib4"), _T("14"));
	pDataType->AddNewValue(_T("Ic4"), _T("Ic4"), _T("15"));
	pDataType->AddNewValue(_T("3I04"), _T("I04"), _T("16"));

	pDataType->AddNewValue(_T("Ia5"), _T("Ia5"), _T("17"));
	pDataType->AddNewValue(_T("Ib5"), _T("Ib5"), _T("18"));
	pDataType->AddNewValue(_T("Ic5"), _T("Ic5"), _T("19"));
	pDataType->AddNewValue(_T("3I05"), _T("I05"), _T("20"));
	pDataType->AddNewValue(_T("Ia6"), _T("Ia6"), _T("21"));
	pDataType->AddNewValue(_T("Ib6"), _T("Ib6"), _T("22"));
	pDataType->AddNewValue(_T("Ic6"), _T("Ic6"), _T("23"));
	pDataType->AddNewValue(_T("3I06"), _T("I06"), _T("24"));

#ifdef _USE_Write_CH_FiberIndex_Config_Files
	pDataType->SaveXmlFile(strConfigPath,CDataMngrXmlRWKeys::g_pXmlKeys);
#endif
}

void CCfgDataMngrConstGlobal::Init_SmvAppChDataType_6U()  //_T("SmvAppChDataType_6U")
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("SmvAppChDataType_6U"), _T("SmvAppChDataType_6U"));
	pDataType->AddNewValue(_T("0"), _T("zero"), _T("0"));
	pDataType->AddNewValue(_T("Ua1"), _T("Ua1"), _T("1"));
	pDataType->AddNewValue(_T("Ub1"), _T("Ub1"), _T("2"));
	pDataType->AddNewValue(_T("Uc1"), _T("Uc1"), _T("3"));
//	pDataType->AddNewValue(_T("3U0"), _T("U01"), _T("4"));
	//	pDataType->AddNewValue(_T("Uz"), _T("Uz1"), _T("5"));
	// 	pDataType->AddNewValue(_T("Uab"), _T("Uab"), _T("6"));  //zhouhj 20211021 无效通道映射,去除
	// 	pDataType->AddNewValue(_T("Ubc"), _T("Ubc"), _T("7"));
	// 	pDataType->AddNewValue(_T("Uca"), _T("Uca"), _T("8"));
	pDataType->AddNewValue(_T("Ua2"), _T("Ua2"), _T("9"));
	pDataType->AddNewValue(_T("Ub2"), _T("Ub2"), _T("10"));
	pDataType->AddNewValue(_T("Uc2"), _T("Uc2"), _T("11"));
//	pDataType->AddNewValue(_T("3U02"), _T("U02"), _T("12"));
	//	pDataType->AddNewValue(_T("Uz2"), _T("Uz2"), _T("13"));
}

void CCfgDataMngrConstGlobal::Init_SmvAppChDataType_6I()  //_T("SmvAppChDataType_6I")
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("SmvAppChDataType_6I"), _T("SmvAppChDataType_6I"));
	pDataType->AddNewValue(_T("0"), _T("zero"), _T("0"));
	pDataType->AddNewValue(_T("Ia1"), _T("Ia1"), _T("1"));
	pDataType->AddNewValue(_T("Ib1"), _T("Ib1"), _T("2"));
	pDataType->AddNewValue(_T("Ic1"), _T("Ic1"), _T("3"));
//	pDataType->AddNewValue(_T("3I0"), _T("I01"), _T("4"));
	pDataType->AddNewValue(_T("Ia2"), _T("Ia2"), _T("5"));
	pDataType->AddNewValue(_T("Ib2"), _T("Ib2"), _T("6"));
	pDataType->AddNewValue(_T("Ic2"), _T("Ic2"), _T("7"));
//	pDataType->AddNewValue(_T("3I02"), _T("I02"), _T("8"));
}


void CCfgDataMngrConstGlobal::Init_SclCtrlAppDataType_Goose()  //_T("SclCtrlAppDataType_Goose")
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("SclCtrlAppDataType_Goose"), _T("SclCtrlAppDataType_Goose"));

	pDataType->AddNewValue(_T("测试仪GOOSE订阅"), _T("GooseSub"), _T("0"));
	pDataType->AddNewValue(_T("测试仪GOOSE发布"), _T("GoosePub"), _T("1"));
}

void CCfgDataMngrConstGlobal::Init_SmvAppChDataType_DCU(BOOL bValid)  //_T("NeutralU")
{
	CDataType *pDataType = NULL;

	if (bValid)
	{
		pDataType = (CDataType*)m_oIecRtdDataTypes.FindByID(iecfg_SmvAppChDataType_DCU);

		if (pDataType != NULL)
		{
			//判断当前的数量是否与最新的一致,如果不一致,则删除重新添加
			if (pDataType->GetCount() == 7)
			{
				return;
			}

			pDataType->DeleteAll();
		}
	}
	if (pDataType == NULL)
	{
		pDataType = m_oIecRtdDataTypes.AddNew2(iecfg_SmvAppChDataType_DCU, iecfg_SmvAppChDataType_DCU);
	}

	pDataType->AddNewValue(_T("0"), _T("zero"), _T("0"));
	//2023.10.7 zhouhj 修改了对应ID
	pDataType->AddNewValue(_T("U1-1"), _T("U1-1"), _T("1"));
	pDataType->AddNewValue(_T("U1-2"), _T("U1-2"), _T("2"));
	pDataType->AddNewValue(_T("U1-3"), _T("U1-3"), _T("3"));
	pDataType->AddNewValue(_T("U2-1"), _T("U2-1"), _T("4"));
	pDataType->AddNewValue(_T("U2-2"), _T("U2-2"), _T("5"));
	pDataType->AddNewValue(_T("U2-3"), _T("U2-3"), _T("6"));

// 	pDataType->AddNewValue(_T("UdL1"), _T("UdL1"), _T("1"));
// 	pDataType->AddNewValue(_T("UdL2"), _T("UdL2"), _T("2"));
// 	pDataType->AddNewValue(_T("UdL3"), _T("UdL3"), _T("3"));
}

void CCfgDataMngrConstGlobal::Init_SmvAppChDataType_DCI(BOOL bValid)  //_T("NeutralU")
{
	CDataType *pDataType = NULL;

	if (bValid)
	{
		pDataType = (CDataType*)m_oIecRtdDataTypes.FindByID(iecfg_SmvAppChDataType_DCI);

		if (pDataType != NULL)
		{
			//判断最新规则ID是否能查找到,如果查找失败,则删除重新添加
			if (pDataType->FindByID(_T("I1-1")) != NULL)
			{
				return;
			}

			pDataType->DeleteAll();
		}
	}
	
	if (pDataType == NULL)
	{
		pDataType = m_oIecRtdDataTypes.AddNew2(iecfg_SmvAppChDataType_DCI, iecfg_SmvAppChDataType_DCI);
	}
	//2023.10.7 zhouhj 修改了对应ID
	pDataType->AddNewValue(_T("0"), _T("zero"), _T("0"));
	pDataType->AddNewValue(_T("I1-1"), _T("I1-1"), _T("1"));
	pDataType->AddNewValue(_T("I1-2"), _T("I1-2"), _T("2"));
	pDataType->AddNewValue(_T("I1-3"), _T("I1-3"), _T("3"));

	pDataType->AddNewValue(_T("I2-1"), _T("I2-1"), _T("4"));
	pDataType->AddNewValue(_T("I2-2"), _T("I2-2"), _T("5"));
	pDataType->AddNewValue(_T("I2-3"), _T("I2-3"), _T("6"));

	pDataType->AddNewValue(_T("I3-1"), _T("I3-1"), _T("7"));
	pDataType->AddNewValue(_T("I3-2"), _T("I3-2"), _T("8"));
	pDataType->AddNewValue(_T("I3-3"), _T("I3-3"), _T("9"));

	pDataType->AddNewValue(_T("I4-1"), _T("I4-1"), _T("10"));
	pDataType->AddNewValue(_T("I4-2"), _T("I4-2"), _T("11"));
	pDataType->AddNewValue(_T("I4-3"), _T("I4-3"), _T("12"));
// 	pDataType->AddNewValue(_T("IdH1"), _T("IdH1"), _T("1"));
// 	pDataType->AddNewValue(_T("IdN1"), _T("IdN1"), _T("2"));
// 	pDataType->AddNewValue(_T("IdL1"), _T("IdL1"), _T("3"));
// 	pDataType->AddNewValue(_T("IdE1"), _T("IdE1"), _T("4"));
// 	pDataType->AddNewValue(_T("IdH2"), _T("IdH2"), _T("5"));
// 	pDataType->AddNewValue(_T("IdN2"), _T("IdN2"), _T("6"));
// 	pDataType->AddNewValue(_T("IdL2"), _T("IdL2"), _T("7"));
// 	pDataType->AddNewValue(_T("IdE2"), _T("IdE2"), _T("8"));
// 	pDataType->AddNewValue(_T("IdH3"), _T("IdH3"), _T("9"));
// 	pDataType->AddNewValue(_T("IdN3"), _T("IdN3"), _T("10"));
// 	pDataType->AddNewValue(_T("IdL3"), _T("IdL3"), _T("11"));
// 	pDataType->AddNewValue(_T("IdE3"), _T("IdE3"), _T("12"));
}

void CCfgDataMngrConstGlobal::Init_SmvAppChDataType_NeutralU()  //_T("NeutralU")
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(iecfg_SmvAppChDataType_NeutralU, iecfg_SmvAppChDataType_NeutralU);
	pDataType->AddNewValue(_T("0"), _T("zero"), _T("0"));
	pDataType->AddNewValue(_T("UdN1"), _T("UdN1"), _T("1"));
	pDataType->AddNewValue(_T("UdN2"), _T("UdN2"), _T("2"));
	pDataType->AddNewValue(_T("UdN3"), _T("UdN3"), _T("3"));
}

void CCfgDataMngrConstGlobal::Init_SmvAppChDataType_T()  //_T("SmvAppChDataType_T")
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(iecfg_SmvAppChDataType_T, iecfg_SmvAppChDataType_T);
	pDataType->AddNewValue(_T("0"), _T("zero"), _T("0"));
	pDataType->AddNewValue(_T("采样延时"), g_strAppChID_TDelay, _T("1"));
}

void CCfgDataMngrConstGlobal::Init_SmvAppChDataType_StateValue()  //_T("SmvChStateValue")
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(iecfg_SmvAppChDataType_StateValue, iecfg_SmvAppChDataType_StateValue);
	pDataType->AddNewValue(_T("单点"), g_strGooseChType_Single, _T("0"));
	pDataType->AddNewValue(_T("双点"), g_strGooseChType_Double, _T("1"));
}

void CCfgDataMngrConstGlobal::Init_SmvAppChDataType_Other()  //_T("Other")
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(iecfg_SmvAppChDataType_Other, iecfg_SmvAppChDataType_Other);
	pDataType->AddNewValue(_T("采样计数器"), g_strAppChID_SmpCnt, _T("0"));
	pDataType->AddNewValue(_T("采样延时"), g_strAppChID_TDelay, _T("1"));
	pDataType->AddNewValue(_T("其它"), _T("Other"), _T("2"));
}

// 
// void CCfgDataMngrConstGlobal::Init_BOutChDataType()  //_T("BOutChDataType")
// {
// 
// }
// 
// void CCfgDataMngrConstGlobal::Init_Cfg6044Speed()  //_T("Cfg6044Speed")
// {
// 
// }

void CCfgDataMngrConstGlobal::Init_GooseChDataType()  //_T("GooseChDataType")
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("开关量类型"), _T("GooseChDataType"));
	pDataType->AddNewValue(_T("单点"), _T("BOOLEAN"), _T("0"));
	pDataType->AddNewValue(_T("双点"), _T("Dbpos"), _T("1"));
	pDataType->AddNewValue(_T("时间"), _T("Timestamp"), _T("2"));
	pDataType->AddNewValue(_T("品质"), _T("Quality"), _T("3"));
	pDataType->AddNewValue(_T("浮点"), _T("FLOAT32"), _T("4"));
	pDataType->AddNewValue(_T("字符串"), _T("VisString64"), _T("5"));
	pDataType->AddNewValue(_T("结构"), _T("Struct"), _T("6"));
	pDataType->AddNewValue(_T("INT32"), _T("INT32"), _T("7"));
	pDataType->AddNewValue(_T("INT32U"), _T("INT32U"), _T("8"));
}

void CCfgDataMngrConstGlobal::Init_STFiberDataType()  //_T("STFiberDataType")
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("ST光口类型"), _T("STFiberDataType"));
	pDataType->AddNewValue(_T("B码"), _T("BCode"), _T("0"));
	pDataType->AddNewValue(_T("FT3"), _T("FT3"), _T("1"));
	
}

void CCfgDataMngrConstGlobal::Init_STFiberInDataType()  //_T("STFiberInDataType")
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("ST接收光口类型"), _T("STFiberInDataType"));
	pDataType->AddNewValue(_T("B码"), _T("BCode"), _T("0"));
	pDataType->AddNewValue(_T("FT3"), _T("FT3"), _T("1"));
	pDataType->AddNewValue(_T("PPS"), _T("PPS"), _T("2"));
	
}
void CCfgDataMngrConstGlobal::Init_LCFiberDataType()  //_T("STFiberDataType")
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("LC光口类型"), _T("LCFiberDataType"));
	pDataType->AddNewValue(_T("百兆口"), _T("Port100M"), _T("0"));
	pDataType->AddNewValue(_T("千兆口"), _T("Port1000M"), _T("1"));
}

void CCfgDataMngrConstGlobal::Init_TesterSubPubDataType()  //_T("TesterSubPubDataType")
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("测试仪订阅发布类型"), _T("TesterSubPubDataType"));
	pDataType->AddNewValue(_T("测试仪订阅"), _T("TesterSub"), _T("0"));
	pDataType->AddNewValue(_T("测试仪发布"), _T("TesterPub"), _T("1"));
}

void CCfgDataMngrConstGlobal::Init_GoutAppChDataType()  //_T("GoutAppChDataType")
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("GoutAppChDataType"), _T("GoutAppChDataType"));
	pDataType->AddNewValue(_T("TRUE"), _T("TRUE"), _T("0"));
	pDataType->AddNewValue(_T("FALSE"), _T("FALSE"), _T("1"));
	pDataType->AddNewValue(_T("0"), _T("v0"), _T("2"));
	pDataType->AddNewValue(_T("0.0"), _T("v0_0"), _T("3"));
	pDataType->AddNewValue(_T("[01]"), _T("v01"), _T("4"));
	pDataType->AddNewValue(_T("[10]"), _T("v10"), _T("5"));
	pDataType->AddNewValue(_T("[1000000000000]"), _T("v_2_13"), _T("6"));
	pDataType->AddNewValue(_T("[1000]"), _T("v100"), _T("7"));
	pDataType->AddNewValue(_T("Out1"), _T("Out1"), _T("8"));
	pDataType->AddNewValue(_T("Out2"), _T("Out2"), _T("9"));
	pDataType->AddNewValue(_T("Out3"), _T("Out3"), _T("10"));
	pDataType->AddNewValue(_T("Out4"), _T("Out4"), _T("11"));
	pDataType->AddNewValue(_T("Out5"), _T("Out5"), _T("12"));
	pDataType->AddNewValue(_T("Out6"), _T("Out6"), _T("13"));
	pDataType->AddNewValue(_T("Out7"), _T("Out7"), _T("14"));
	pDataType->AddNewValue(_T("Out8"), _T("Out8"), _T("15"));
	pDataType->AddNewValue(_T("Out1_DPPOS"), _T("Out1_DPPOS"), _T("16"));
	pDataType->AddNewValue(_T("Out2_DPPOS"), _T("Out2_DPPOS"), _T("17"));
	pDataType->AddNewValue(_T("Out3_DPPOS"), _T("Out3_DPPOS"), _T("18"));
	pDataType->AddNewValue(_T("Out4_DPPOS"), _T("Out4_DPPOS"), _T("19"));
	pDataType->AddNewValue(_T("Out5_DPPOS"), _T("Out5_DPPOS"), _T("20"));
	pDataType->AddNewValue(_T("Out6_DPPOS"), _T("Out6_DPPOS"), _T("21"));
	pDataType->AddNewValue(_T("Out7_DPPOS"), _T("Out7_DPPOS"), _T("22"));
	pDataType->AddNewValue(_T("Out8_DPPOS"), _T("Out8_DPPOS"), _T("23"));
	pDataType->AddNewValue(_T("UTCTime"), _T("UTCTime"), _T("24"));
}

void CCfgDataMngrConstGlobal::Init_GinAppChDataType()  //_T("GinAppChDataType")
{
	CString strConfigPath;
	strConfigPath = _P_GetConfigPath();
	strConfigPath += g_strGsChDtID_goose_in_ch;
	strConfigPath += _T(".xml");
	CDataType *pDataType = (CDataType*)m_oIecRtdDataTypes.FindByID(iecfg_GinAppChDataType);

	if (pDataType == NULL)
	{
		pDataType = m_oIecRtdDataTypes.AddNew2(_T("开入量"), iecfg_GinAppChDataType);//_T("GinAppChDataType"));
	}
	else
	{
		pDataType->DeleteAll();
	}

	if (IsFileExist(strConfigPath))
	{
		pDataType->OpenXmlFile(strConfigPath,CDataMngrXmlRWKeys::g_pXmlKeys);
	}
	else
	{
		pDataType->AddNewValue(_T("无"), _T("none"), _T("0"));
		pDataType->AddNewValue(_T("开入A"), _T("bin1"), _T("1"));
		pDataType->AddNewValue(_T("开入B"), _T("bin2"), _T("2"));
		pDataType->AddNewValue(_T("开入C"), _T("bin3"), _T("3"));
		pDataType->AddNewValue(_T("开入D"), _T("bin4"), _T("4"));
		pDataType->AddNewValue(_T("开入E"), _T("bin5"), _T("5"));
		pDataType->AddNewValue(_T("开入F"), _T("bin6"), _T("6"));
		pDataType->AddNewValue(_T("开入G"), _T("bin7"), _T("7"));
		pDataType->AddNewValue(_T("开入H"), _T("bin8"), _T("8"));

		CString strBin,strID,strIndex;

		for (int i=0;i<64;i++)
		{
			strBin.Format(_T("开入扩展%d"), i+1);
			strID.Format(_T("binex%d"), i+1);
			strIndex.Format(_T("%d"), i+9);//周宏军 20200526  防止与正常开入的重复
			pDataType->AddNewValue(strBin, strID, strIndex);
		}

#ifdef _USE_Write_CH_FiberIndex_Config_Files
		pDataType->SaveXmlFile(strConfigPath,CDataMngrXmlRWKeys::g_pXmlKeys);
#endif
	}
}


void CCfgDataMngrConstGlobal::Init_AppPortDataType_Fiber(long nFiberNum)  //_T("AppFiberPort")
{
	CString strFiberConfigPath;
	strFiberConfigPath = _P_GetConfigPath();
	strFiberConfigPath += _T("IecFiberTypeCfg.xml");
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("测试仪光口选择"), _T("AppFiberPort"));

	if (IsFileExist(strFiberConfigPath))
	{
		pDataType->OpenXmlFile(strFiberConfigPath,CDataMngrXmlRWKeys::g_pXmlKeys);
		return;
	}

	CString strFiberName,strFiberID,strFiberIndex;//周宏军 20200311 将光口数量扩展到48

	for (int nIndex = 0;nIndex<nFiberNum;nIndex++)
	{
		strFiberIndex.Format(_T("%d"),nIndex);
        strFiberName.Format(_T("光口%d"),(nIndex+1));
		strFiberID.Format(_T("Fiber%s"),strFiberIndex.GetString());
		pDataType->AddNewValue(strFiberName, strFiberID, strFiberIndex);
	}

#ifdef _USE_Write_CH_FiberIndex_Config_Files
	pDataType->SaveXmlFile(strFiberConfigPath,CDataMngrXmlRWKeys::g_pXmlKeys);
#endif

// 	pDataType->AddNewValue(_T("光口1"), _T("Fiber1"), _T("0"));
// 	pDataType->AddNewValue(_T("光口2"), _T("Fiber2"), _T("1"));
// 	pDataType->AddNewValue(_T("光口3"), _T("Fiber3"), _T("2"));
// 	pDataType->AddNewValue(_T("光口4"), _T("Fiber4"), _T("3"));
// 	pDataType->AddNewValue(_T("光口5"), _T("Fiber5"), _T("4"));
// 	pDataType->AddNewValue(_T("光口6"), _T("Fiber6"), _T("5"));
// 	pDataType->AddNewValue(_T("光口7"), _T("Fiber7"), _T("6"));
// 	pDataType->AddNewValue(_T("光口8"), _T("Fiber8"), _T("7"));
}


void CCfgDataMngrConstGlobal::Init_AppPortDataType_Ft3(BOOL bFindRepeat)
{
	CDataType *pDataType = NULL;

	if (bFindRepeat)
	{
		pDataType = (CDataType*)m_oIecRtdDataTypes.FindByID(g_strAppPortDataType_Ft3);

		if (pDataType != NULL)
		{
			return;
		}
	}

	if (pDataType == NULL)
	{
		pDataType = m_oIecRtdDataTypes.AddNew2(_T("FT3口选择"), g_strAppPortDataType_Ft3);
	}

	pDataType->AddNewValue(_T("FT3_1口"), _T("Ft3_1"), _T("0"));
	pDataType->AddNewValue(_T("FT3_2口"), _T("Ft3_2"), _T("1"));
	pDataType->AddNewValue(_T("FT3_3口"), _T("Ft3_3"), _T("2"));
	pDataType->AddNewValue(_T("FT3_4口"), _T("Ft3_4"), _T("3"));
}

void CCfgDataMngrConstGlobal::Init_AppPortDataType_Ft3In(BOOL bFindRepeat)
{
	CDataType *pDataType = NULL;

	if (bFindRepeat)
	{
		pDataType = (CDataType*)m_oIecRtdDataTypes.FindByID(g_strAppPortDataType_Ft3In);

		if (pDataType != NULL)
		{
			return;
		}
	}

	if (pDataType == NULL)
	{
		pDataType = m_oIecRtdDataTypes.AddNew2(_T("FT3接收口选择"), g_strAppPortDataType_Ft3In);
	}
	pDataType->AddNewValue(_T("FT3接收_1口"), _T("Ft3In_1"), _T("0"));
	pDataType->AddNewValue(_T("FT3接收_2口"), _T("Ft3In_2"), _T("1"));
}

void CCfgDataMngrConstGlobal::Init_AppPortDataType_SmpByteNum()  //_T("SmpByteNum")
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("采样位宽"), _T("SmpByteNum"));
	pDataType->AddNewValue(_T("1字节"), _T("ByteNum_1"), _T("1"));
	pDataType->AddNewValue(_T("2字节"), _T("ByteNum_2"), _T("2"));
	pDataType->AddNewValue(_T("3字节"), _T("ByteNum_3"), _T("3"));
	pDataType->AddNewValue(_T("4字节"), _T("ByteNum_4"), _T("4"));
}

void CCfgDataMngrConstGlobal::Init_AppPortDataType_SmpCntType()  //_T("SmpCntType")
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("采样方式"), _T("SmpCntType"));
	pDataType->AddNewValue(_T("采样计数器(2字节0~SampCount)"), _T("SmpCnt"), _T("0"));
	pDataType->AddNewValue(_T("帧循环计数器(1字节0~255)"), _T("FrameLoop255"), _T("1"));
	pDataType->AddNewValue(_T("帧循环计数器(2字节0~65536)"), _T("FrameLoop65536"), _T("2"));
}

void CCfgDataMngrConstGlobal::Init_SmvChByteLenDataType()  //_T("SmvChByteLen")
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("字节长度"), _T("SmvChByteLen"));
	pDataType->AddNewValue(_T("1"), _T("ByteLen1"), _T("1"));
	pDataType->AddNewValue(_T("2"), _T("ByteLen2"), _T("2"));
	pDataType->AddNewValue(_T("3"), _T("ByteLen3"), _T("3"));
	pDataType->AddNewValue(_T("4"), _T("ByteLen4"), _T("4"));
}

void CCfgDataMngrConstGlobal::Init_BlockInx_2MDataType()  //_T("BlockInx_2M")
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("控制块Inx"), _T("BlockInx_2M"));
	CString strName,strID;

	for (int nIndex = 0;nIndex<22;nIndex++)
	{
		strName.Format(_T("%d"),nIndex);
		strID.Format(_T("BlockInx%d"),nIndex);
		pDataType->AddNewValue(strName, strID, nIndex);
	}
}

void CCfgDataMngrConstGlobal::Init_PkgType_2MDataType()  //_T("PkgType_2M")
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("报文类别"), _T("PkgType_2M"));
	pDataType->AddNewValue(_T("数据报文"), _T("DataPkg_2M"), _T("0"));
	pDataType->AddNewValue(_T("命令报文"), _T("CmdPkg_2M"), _T("1"));
}


void CCfgDataMngrConstGlobal::Init_AppSynDataType_Fiber()  //_T("AppSynMode")
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("同步方式"), _T("AppSynMode"));
	pDataType->AddNewValue(_T("未同步"), _T("Syn1"), _T("0"));
	pDataType->AddNewValue(_T("本地同步(Local)"), _T("Syn2"), _T("1"));
	pDataType->AddNewValue(_T("全站同步(Global)"), _T("Syn3"), _T("2"));
}

void CCfgDataMngrConstGlobal::ValidAddDataTypes()
{
	Init_AppTestSetDataType(TRUE);
	Init_SmvCommon6044ChInDataType(TRUE);
	Init_SmvChAngType(TRUE);
	Init_SmvCommon6044ChDataType(TRUE);
	Init_SmvCommon6044DCChDataType(TRUE);
	Init_SmvAppChDataType_DCI(TRUE);
	Init_SmvAppChDataType_DCU(TRUE);
	Init_AppPortDataType_Ft3(TRUE);  
	Init_AppPortDataType_Ft3In(TRUE);
}

void CCfgDataMngrConstGlobal::Init_AppTestSetDataType(BOOL bFindRepeat)  //_T("AppTestSet")
{
	if (bFindRepeat && (m_oIecRtdDataTypes.FindByID(_T("AppTestSet")) != NULL))
	{
		return;
	}

	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("检修状态设置"), _T("AppTestSet"));
	pDataType->AddNewValue(_T("FALSE"), _T("TestSet1"), _T("0"));
	pDataType->AddNewValue(_T("TRUE"), _T("TestSet2"), _T("1"));
	pDataType->AddNewValue(_T("不解析"), _T("TestSet3"), _T("2"));
}

void CCfgDataMngrConstGlobal::Init_Quality_DataTypes()
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("validity"), _T("validity"));
	pDataType->AddNewValue(_T("00:good(好)"), _T("good"), _T("0"));
	pDataType->AddNewValue(_T("01:invalid(无效)"), _T("invalid"), _T("1"));
	pDataType->AddNewValue(_T("10:reserved(保留)"), _T("reserved"), _T("2"));
	pDataType->AddNewValue(_T("11:questionable(可疑)"), _T("questionable"), _T("3"));

	pDataType = m_oIecRtdDataTypes.AddNew2(_T("overflow"), _T("overflow"));
	pDataType->AddNewValue(_T("0:无溢出"), _T("nooverflow"), _T("0"));
	pDataType->AddNewValue(_T("1:溢出"), _T("overflow"), _T("1"));

	pDataType = m_oIecRtdDataTypes.AddNew2(_T("outofrange"), _T("outofrange"));
	pDataType->AddNewValue(_T("0:正常"), _T("normal"), _T("0"));
	pDataType->AddNewValue(_T("1:超值域"), _T("outofrange"), _T("1"));

	pDataType = m_oIecRtdDataTypes.AddNew2(_T("badreference"), _T("badreference"));
	pDataType->AddNewValue(_T("0:正常"), _T("normal"), _T("0"));
	pDataType->AddNewValue(_T("1:坏基准值"), _T("badreference"), _T("1"));

	pDataType = m_oIecRtdDataTypes.AddNew2(_T("oscillatory"), _T("oscillatory"));
	pDataType->AddNewValue(_T("0:无抖动"), _T("normal"), _T("0"));
	pDataType->AddNewValue(_T("1:有抖动"), _T("Oscillatory"), _T("1"));

	pDataType = m_oIecRtdDataTypes.AddNew2(_T("failure"), _T("failure"));
	pDataType->AddNewValue(_T("0:无故障"), _T("nofailure"), _T("0"));
	pDataType->AddNewValue(_T("1:有故障"), _T("failure"), _T("1"));

	pDataType = m_oIecRtdDataTypes.AddNew2(_T("olddata"), _T("olddata"));
	pDataType->AddNewValue(_T("0:无超时"), _T("normal"), _T("0"));
	pDataType->AddNewValue(_T("1:数据超时"), _T("overtime"), _T("1"));

	pDataType = m_oIecRtdDataTypes.AddNew2(_T("inconsistent"), _T("inconsistent"));
	pDataType->AddNewValue(_T("0:一致"), _T("normal"), _T("0"));
	pDataType->AddNewValue(_T("1:不一致"), _T("inconsistent"), _T("1"));

	pDataType = m_oIecRtdDataTypes.AddNew2(_T("inaccurate"), _T("inaccurate"));
	pDataType->AddNewValue(_T("0:精确"), _T("normal"), _T("0"));
	pDataType->AddNewValue(_T("1:不精确"), _T("Inaccurate"), _T("1"));

	pDataType = m_oIecRtdDataTypes.AddNew2(_T("source"), _T("source"));
	pDataType->AddNewValue(_T("0:process(过程)"), _T("process"), _T("0"));
	pDataType->AddNewValue(_T("1:substituted(被取代)"), _T("substituted"), _T("1"));

	pDataType = m_oIecRtdDataTypes.AddNew2(_T("test"), _T("test"));
	pDataType->AddNewValue(_T("0:运行"), _T("run"), _T("0"));
	pDataType->AddNewValue(_T("1:测试"), _T("test"), _T("1"));

	pDataType = m_oIecRtdDataTypes.AddNew2(_T("OPB"), _T("OPB"));
	pDataType->AddNewValue(_T("0:不闭锁"), _T("lock"), _T("0"));
	pDataType->AddNewValue(_T("1:闭锁"), _T("nolock"), _T("1"));
}

void CCfgDataMngrConstGlobal::Init_goose_ch_DataTypes()
{
	CDataType *pDataType = NULL;

	CString strConfigPath;
	strConfigPath = _P_GetConfigPath();
	strConfigPath += _T("goose-out-ch-single.xml");
//	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("测试仪光口选择"), _T("AppFiberPort"));
	pDataType = m_oIecRtdDataTypes.AddNew2(_T("开出量-单点"), g_strGsChDtID_goose_out_ch_single);

	if (IsFileExist(strConfigPath))
	{
		pDataType->OpenXmlFile(strConfigPath,CDataMngrXmlRWKeys::g_pXmlKeys);
	}
	else
	{
		pDataType->AddNewValue(_T("---"), _T("v0"), _T("0"));//zhouhj 20210924单机软件默认不需要进行通道映射
//		pDataType->AddNewValue(_T("1"), _T("v1"), _T("1"));

		int nIndex = 0;
		CString strName,strID,strIndex;

		for (nIndex=1;nIndex<=8;nIndex++)
		{
			strName.Format(_T("开出%d"),nIndex);
			strID.Format(_T("bout%d"),nIndex);
			strIndex.Format(_T("%d"),(nIndex+1));
			pDataType->AddNewValue(strName, strID,strIndex);
		}

		for (nIndex=1;nIndex<=32;nIndex++)
		{
			strName.Format(_T("扩展开出%d"),nIndex);
			strID.Format(_T("boutex%d"),nIndex);
			strIndex.Format(_T("%d"),(nIndex+9));
			pDataType->AddNewValue(strName, strID,strIndex);
		}

#ifdef _USE_Write_CH_FiberIndex_Config_Files
		pDataType->SaveXmlFile(strConfigPath,CDataMngrXmlRWKeys::g_pXmlKeys);
#endif
	}

	
// 	pDataType->AddNewValue(_T("开出1"), _T("bout1"), _T("2"));
// 	pDataType->AddNewValue(_T("开出2"), _T("bout2"), _T("3"));
// 	pDataType->AddNewValue(_T("开出3"), _T("bout3"), _T("4"));
// 	pDataType->AddNewValue(_T("开出4"), _T("bout4"), _T("5"));
// 	pDataType->AddNewValue(_T("开出5"), _T("bout5"), _T("6"));
// 	pDataType->AddNewValue(_T("开出6"), _T("bout6"), _T("7"));
// 	pDataType->AddNewValue(_T("开出7"), _T("bout7"), _T("8"));
// 	pDataType->AddNewValue(_T("开出8"), _T("bout8"), _T("9"));

	strConfigPath = _P_GetConfigPath();
	strConfigPath += _T("goose-out-ch-double.xml");
	pDataType = m_oIecRtdDataTypes.AddNew2(_T("开出量-双点"), g_strGsChDtID_goose_out_ch_double);

	if (IsFileExist(strConfigPath))
	{
		pDataType->OpenXmlFile(strConfigPath,CDataMngrXmlRWKeys::g_pXmlKeys);
	}
	else
	{
//		pDataType->AddNewValue(_T("00"), _T("v00"), _T("0"));
		pDataType->AddNewValue(_T("---"), _T("v01"), _T("1"));//zhouhj 20210924单机软件默认不需要进行通道映射
// 		pDataType->AddNewValue(_T("10"), _T("v10"), _T("2"));
// 		pDataType->AddNewValue(_T("11"), _T("v11"), _T("3"));

		int nIndex = 0;
		CString strName,strID,strIndex;

		for (nIndex=1;nIndex<=8;nIndex++)
		{
			strName.Format(_T("开出%d"),nIndex);
			strID.Format(_T("bout%d"),nIndex);
			strIndex.Format(_T("%d"),(nIndex+3));
			pDataType->AddNewValue(strName, strID,strIndex);
		}

		for (nIndex=1;nIndex<=32;nIndex++)
		{
			strName.Format(_T("扩展开出%d"),nIndex);
			strID.Format(_T("boutex%d"),nIndex);
			strIndex.Format(_T("%d"),(nIndex+11));
			pDataType->AddNewValue(strName, strID,strIndex);
		}

#ifdef _USE_Write_CH_FiberIndex_Config_Files
		pDataType->SaveXmlFile(strConfigPath,CDataMngrXmlRWKeys::g_pXmlKeys);
#endif
	}
	

// 	pDataType->AddNewValue(_T("开出1"), _T("bout1"), _T("4"));
// 	pDataType->AddNewValue(_T("开出2"), _T("bout2"), _T("5"));
// 	pDataType->AddNewValue(_T("开出3"), _T("bout3"), _T("6"));
// 	pDataType->AddNewValue(_T("开出4"), _T("bout4"), _T("7"));
// 	pDataType->AddNewValue(_T("开出5"), _T("bout5"), _T("9"));
// 	pDataType->AddNewValue(_T("开出6"), _T("bout6"), _T("10"));
// 	pDataType->AddNewValue(_T("开出7"), _T("bout7"), _T("11"));
// 	pDataType->AddNewValue(_T("开出8"), _T("bout8"), _T("12"));

	pDataType = m_oIecRtdDataTypes.AddNew2(_T("开出量-单点-缺省值"), g_strGsChDtID_goose_out_ch_single_def_value);
	pDataType->AddNewValue(_T("FALSE"), _T("FALSE"), _T("0"));
	pDataType->AddNewValue(_T("TRUE"), _T("TRUE"), _T("1"));

	pDataType = m_oIecRtdDataTypes.AddNew2(_T("开出量-双点-缺省值"), g_strGsChDtID_goose_out_ch_double_def_value);
	pDataType->AddNewValue(_T("[00]"), _T("[00]"), _T("0"));
	pDataType->AddNewValue(_T("[01]"), _T("[01]"), _T("1"));
	pDataType->AddNewValue(_T("[10]"), _T("[10]"), _T("2"));
	pDataType->AddNewValue(_T("[11]"), _T("[11]"), _T("3"));
}

//////////////////////////////////////////////////////////////////////////
CString iecfg_GetCfgCapFileCfgDatasMngr()
{
	CString strFile;
	strFile = _P_GetBinPath();
	strFile += CFG_CAP_FILE_CFGDATASMNGR;
	return strFile;
}

CString iecfg_GetCfgCapFileCfgData()
{
	CString strFile;
	strFile = _P_GetBinPath();
	strFile += CFG_CAP_FILE_CFGDATA;
	return strFile;
}



long iecfg_GetBinIndex(const char *pszBin)
{
	const char *pTemp = pszBin;

	while (*pTemp != 0)
	{
		if (isalpha(*pTemp))
		{
			pTemp++;
		}
		else
		{
			break;
		}
	}

	long nValue = 0;

	while ('0'<=*pTemp && *pTemp <= '9')
	{
		nValue = nValue * 10 + (*pTemp - '0');
		pTemp++;
	}

	return nValue;
}

void iecfg_AppendBinID(long nIndex, CString &strBinID)
{
	strBinID.AppendFormat(_T("bin%d"), nIndex);
}

void iecfg_GetBinID(DWORD dwValue, CString &strBinID)
{
	long nIndex = 0;

	if (dwValue == 0)
	{
		strBinID = g_strAppChID_None;
		return;
	}

	strBinID.Empty();
	DWORD dwTemp = 1;
	for (nIndex=0; nIndex<8; nIndex++)
	{
		if ((dwTemp & dwValue) > 0)
		{
			strBinID.AppendFormat(_T("bin%d;"), nIndex+1);
		}

		dwTemp <<= 1;
	}
}

long iecfg_GetBinChangeIndex(DWORD dwOld, DWORD dwCurr)
{
	DWORD dw = dwOld ^ dwCurr;

	DWORD dwTemp = 1;
	long nIndex = 0;
	long nIndexFind = -1;

	for (nIndex=0; nIndex<8; nIndex++)
	{
		if ((dw & 0x01) > 0)
		{
			nIndexFind = nIndex+1;
			break;
		}

		dw >>= 1;
	}

	return nIndexFind;
}

CString iecfg_GetBinID(long nIndex)
{
	CString strBinID;
	strBinID.Format(_T("bin%d"), nIndex);
	return strBinID;
}

