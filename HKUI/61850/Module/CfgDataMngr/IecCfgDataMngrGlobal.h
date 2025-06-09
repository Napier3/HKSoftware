//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDataMngrGlobal.h

#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"
#include "../../../Module/API/FileApi.h"
#include "../../../Module/DataMngr/DataTypes.h"

static const CString g_strIecCfgFilePostfix       = _T("ixml");
static const CString g_strDeviceIecCfgFilePostfix = _T("iecfg");

#define CFGCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00020000)
#define CFGCLASSID_EXLISTCLASS       (CLASSID_LISTCLASS + 0X00020000)

#define CFGCLASSID_CIECCFGDATABASE       (CFGCLASSID_EXLISTCLASS + 0X00000000)
#define CFGCLASSID_CIECCFGDATACHBASE       (CFGCLASSID_BASECLASS + 0X00000001)
#define CFGCLASSID_CIECCFGDATASBASE       (CFGCLASSID_EXLISTCLASS + 0X00000002)
#define CFGCLASSID_CIECCFGADVANCEEXCEPTION       (CFGCLASSID_BASECLASS + 0X00000003)
#define CFGCLASSID_CIECCFGSMVDATABASE       (CFGCLASSID_EXLISTCLASS + 0X00000004)
#define CFGCLASSID_CIECCFGDATASMVCHBASE       (CFGCLASSID_EXLISTCLASS + 0X00000005)
#define CFGCLASSID_CIECCFGGOOSEDATABASE       (CFGCLASSID_EXLISTCLASS + 0X00000006)
#define CFGCLASSID_CIECCFGDATAGOOSECHBASE       (CFGCLASSID_EXLISTCLASS + 0X00000007)
#define CFGCLASSID_CIECCFG92DATA       (CFGCLASSID_EXLISTCLASS + 0X00000008)
#define CFGCLASSID_CIECCFG92CHQUALITY       (CFGCLASSID_BASECLASS + 0X00000009)
#define CFGCLASSID_CIECCFG92CH       (CFGCLASSID_EXLISTCLASS + 0X0000000A)
#define CFGCLASSID_CIECCFG91DATA       (CFGCLASSID_EXLISTCLASS + 0X0000000B)
#define CFGCLASSID_CIECCFG91STATUSDATASET       (CFGCLASSID_EXLISTCLASS + 0X0000000C)
#define CFGCLASSID_CIECCFG91CH       (CFGCLASSID_EXLISTCLASS + 0X0000000D)
#define CFGCLASSID_CIECCFG6044DATA       (CFGCLASSID_EXLISTCLASS + 0X0000000E)
#define CFGCLASSID_CIECCFG6044CH       (CFGCLASSID_EXLISTCLASS + 0X0000000F)
#define CFGCLASSID_CIECCFGGINDATA       (CFGCLASSID_EXLISTCLASS + 0X00000010)
#define CFGCLASSID_CIECCFGGINCH       (CFGCLASSID_EXLISTCLASS + 0X00000011)
#define CFGCLASSID_CIECCFGGOUTDATA       (CFGCLASSID_EXLISTCLASS + 0X00000012)
#define CFGCLASSID_CIECCFGGOUTCH       (CFGCLASSID_EXLISTCLASS + 0X00000013)
#define CFGCLASSID_CIECCFGDATASSMV       (CFGCLASSID_EXLISTCLASS + 0X00000014)
#define CFGCLASSID_CIECCFGDATASGIN       (CFGCLASSID_EXLISTCLASS + 0X00000015)
#define CFGCLASSID_CIECCFGDATASGOUT       (CFGCLASSID_EXLISTCLASS + 0X00000016)

#define CFGCLASSID_CIECCFGDATASMNGR       (CFGCLASSID_EXLISTCLASS + 0X00000017)
#define CFGCLASSID_CIECCFGCHSBASE       (CFGCLASSID_EXLISTCLASS + 0X00000018)
#define CFGCLASSID_CIECCFGCHS92       (CFGCLASSID_EXLISTCLASS + 0X00000019)
#define CFGCLASSID_CIECCFGCHS91       (CFGCLASSID_EXLISTCLASS + 0X0000001A)
#define CFGCLASSID_CIECCFGCHS6044       (CFGCLASSID_EXLISTCLASS + 0X0000001B)
#define CFGCLASSID_CIECCFGCHSGIN       (CFGCLASSID_EXLISTCLASS + 0X0000001C)
#define CFGCLASSID_CIECCFGCHSGOUT       (CFGCLASSID_EXLISTCLASS + 0X0000001D)
#define CFGCLASSID_CIECCFG91STATUSDATASETCH       (CFGCLASSID_BASECLASS + 0X0000001E)
#define CFGCLASSID_CIECCFG91STATEWORD       (CFGCLASSID_EXLISTCLASS + 0X0000001F)
#define CFGCLASSID_CIECCFG91STATEWORDBIT       (CFGCLASSID_BASECLASS + 0X00000020)
#define CFGCLASSID_CIECCFG91STATEWORDMNGR       (CFGCLASSID_EXLISTCLASS + 0X00000021)
#define CFGCLASSID_CARTAMPDIGDATA       (CFGCLASSID_BASECLASS + 0X00000022)
#define CFGCLASSID_CARTAMPDIGDATAS       (CFGCLASSID_EXLISTCLASS + 0X00000023)
#define CFGCLASSID_CIECCFG_SMV_COMMON      (CFGCLASSID_BASECLASS + 0X00000024)
#define CFGCLASSID_CIECCFGSYSTEMCONFIG       (CFGCLASSID_BASECLASS + 0X00000025)
#define CFGCLASSID_CIECCFGANALOGCH       (CFGCLASSID_EXLISTCLASS + 0X00000026)
#define CFGCLASSID_CIECCFGCHSANALOG       (CFGCLASSID_EXLISTCLASS + 0X00000027)
#define CFGCLASSID_CIECCFGANALOGDATA       (CFGCLASSID_EXLISTCLASS + 0X00000028)
#define CFGCLASSID_CIECCFGDATASANALOG       (CFGCLASSID_EXLISTCLASS + 0X00000029)
#define CFGCLASSID_CIECCFGSMVRATE       (CFGCLASSID_BASECLASS + 0X00000030)
#define CFGCLASSID_CIECCFGSMVRATES       (CFGCLASSID_EXLISTCLASS + 0X0000003A)
#define CFGCLASSID_CIECCFGDEVICE       (CFGCLASSID_EXLISTCLASS + 0X0000003B)

#define CFGCLASSID_CSCLIEDREF       (CFGCLASSID_BASECLASS + 0X0000003C)
#define CFGCLASSID_CSCLBAYVLEVEL       (CFGCLASSID_EXLISTCLASS + 0X0000003D)
#define CFGCLASSID_CSCLBAY       (CFGCLASSID_EXLISTCLASS + 0X0000003E)
#define CFGCLASSID_CIECCFGCHS92IN       (CFGCLASSID_EXLISTCLASS + 0X0000003F)
#define CFGCLASSID_CIECCFG92CHIN       (CFGCLASSID_EXLISTCLASS + 0X00000040)


//DataTypeTemplates
#define DATATYPECLASSID_TEMPLATES       (CFGCLASSID_EXLISTCLASS + 0X00000041)
#define DATATYPECLASSID_LNODETYPE       (CFGCLASSID_EXLISTCLASS + 0X00000042)
#define DATATYPECLASSID_DOTYPE       (CFGCLASSID_EXLISTCLASS + 0X00000043)
#define DATATYPECLASSID_DATYPE       (CFGCLASSID_EXLISTCLASS + 0X00000044)
#define DATATYPECLASSID_ENUMTYPE       (CFGCLASSID_EXLISTCLASS + 0X00000045)

#define DATATYPECLASSID_DODETAIL       (CFGCLASSID_EXLISTCLASS + 0X00000046)
#define DATATYPECLASSID_DADETAIL       (CFGCLASSID_EXLISTCLASS + 0X00000047)
#define DATATYPECLASSID_BDADETAIL       (CFGCLASSID_EXLISTCLASS + 0X00000048)
#define DATATYPECLASSID_ENUMDETAIL       (CFGCLASSID_EXLISTCLASS + 0X00000049)


#define CFGCLASSID_CIECCFGSYSPARAS       (CFGCLASSID_EXLISTCLASS + 0X00000050)//zhouhj 20210315 单机软件参数设置
#define CFGCLASSID_CIECCFGPRIMRATES       (CFGCLASSID_EXLISTCLASS + 0X00000051)
#define CFGCLASSID_CIECCFGPRIMRATESIN     (CFGCLASSID_EXLISTCLASS + 0X00000052)
#define CFGCLASSID_CIECCFGPRIMRATE       (CFGCLASSID_EXLISTCLASS + 0X00000053)
#define CFGCLASSID_CIECCFGFIBERPARAS       (CFGCLASSID_EXLISTCLASS + 0X00000054)
#define CFGCLASSID_CIECCFGFIBERPARA       (CFGCLASSID_EXLISTCLASS + 0X00000055)

#define CFGCLASSID_CIECCFG6044COMMONDATA     (CFGCLASSID_EXLISTCLASS + 0X00000056)//zhouhj 20211009 增加用于公共FT3（柔直）
#define CFGCLASSID_CIECCFG6044COMMONCH       (CFGCLASSID_EXLISTCLASS + 0X00000057)
#define CFGCLASSID_CIECCFG2MDATA             (CFGCLASSID_EXLISTCLASS + 0X00000058)//zhouhj 20220731 增加用于南瑞2M输出
#define CFGCLASSID_CIECCFG2MINDATA           (CFGCLASSID_EXLISTCLASS + 0X00000059)//zhouhj 20220731 增加用于南瑞2M输出

#define CFGCLASSID_CIECCFG6044COMMONINDATA     (CFGCLASSID_EXLISTCLASS + 0X00005A)//zhouhj 20221104 增加用于公共FT3（柔直）接收
#define CFGCLASSID_CIECCFG6044COMMONCHIN       (CFGCLASSID_EXLISTCLASS + 0X00005B)

#define CFGCLASSID_CIECCFGDATASSMVINPUT       (CFGCLASSID_EXLISTCLASS + 0X0000005C)
#define CFGCLASSID_CIECCFG92INPUTDATA       (CFGCLASSID_EXLISTCLASS + 0X0000005D)
#define CFGCLASSID_CIECCFGFIBERPARAIN       (CFGCLASSID_EXLISTCLASS + 0X0000005E)//suyang 20230519 

#define MAX_FIBER_PORT_NUM                  48

class CCfgDataMngrXmlRWKeys : public CDataMngrXmlRWKeys
{
protected:
	CCfgDataMngrXmlRWKeys();
	virtual ~CCfgDataMngrXmlRWKeys();
	static long g_nCFGRef;

public:
	static CCfgDataMngrXmlRWKeys* g_pXmlKeys;
	static CCfgDataMngrXmlRWKeys* Create();
	static void Release();


public:
	BSTR m_strCIecCfgSmvRatesKey; //smv-rates
	BSTR m_strCIecCfgSmvRateKey; //smv-rate
	BSTR m_strCIecCfgAnalogChKey; //analog-ch
	BSTR m_strCIecCfgChsAnalogKey; //analog-ch
	BSTR m_strCIecCfgDataAnalogKey; //cfg-analog
	BSTR m_strCIecCfgSystemConfigKey; //sys-config
	BSTR m_strCArtAmpDigdatasKey; //dig-datas
	BSTR m_strCArtAmpDigdataKey; //dig-data
	BSTR m_strSValueKey; //state-word-mngr
	BSTR m_strQValueKey; //bit
	BSTR m_strCIecCfg91StateWordMngrKey; //state-word-mngr
	BSTR m_strCIecCfg91StateWordBitKey; //bit
	BSTR m_strCIecCfg91StateWordKey; //state-word
	BSTR m_strCIecCfg91StatusDataSetChKey; //ch
	BSTR m_strCIecCfgChsGoutKey; //chs
	BSTR m_strCIecCfgChsGinKey; //chs
	BSTR m_strCIecCfgChs6044Key; //chs
	BSTR m_strCIecCfgChs91Key; //chs
	BSTR m_strCIecCfgChs92Key; //chs
	BSTR m_strCIecCfgChs92InKey; //chs
	BSTR m_strCIecCfgChsBaseKey; //chs
	BSTR m_strCIecCfgDatasMngrKey; //cfg-datas-mngr
	BSTR m_strCIecCfgDeviceKey; //cfg-device
	BSTR m_strCIecCfgDatasGoutKey; //cfg-gouts
	BSTR m_strCIecCfgDatasGinKey; //cfg-gins
	BSTR m_strCIecCfgDatasAnalogKey; //cfg-analogs
	BSTR m_strCIecCfgDatasSMVKey; //cfg-smvs
	BSTR m_strCIecCfgDatasSmvInKey; //cfg-smvs-in
	BSTR m_strCIecCfgGoutChKey; //ch-gout
	BSTR m_strCIecCfgDataGoutKey; //cfg-gout
	BSTR m_strCIecCfgGinChKey; //ch-gin
	BSTR m_strCIecCfgDataGinKey; //cfg-gin
	BSTR m_strCIecCfg6044ChKey; //ch-6044
	BSTR m_strCIecCfg6044CommonChKey; //ch-6044-common
	BSTR m_strCIecCfg6044CommonChInKey; //ch-6044-common-in
	BSTR m_strCIecCfgData6044Key; //cfg-6044
	BSTR m_strCIecCfgData6044CommonKey; //cfg-6044-common
	BSTR m_strCIecCfgData6044CommonInKey; //cfg-6044-common-in
	BSTR m_strCIecCfgData2MKey; //cfg-2m
	BSTR m_strCIecCfgData2MInKey; //cfg-2m-in

	BSTR m_strCIecCfg91ChKey; //ch-91
	BSTR m_strCIecCfg91StatusDataSetKey; //cfg-91-status-data
	BSTR m_strCIecCfgData91Key; //cfg-91
	BSTR m_strCIecCfg92ChKey; //ch-92
	BSTR m_strCIecCfg92ChQualityKey; //ch-92-Q
	BSTR m_strCIecCfgData92Key; //cfg-92
	BSTR m_strCIecCfgData92InKey; //cfg-92-in
	BSTR m_strCIecCfgDataGooseChBaseKey; //ch-goose
	BSTR m_strCIecCfgGooseDataBaseKey; //cfg-goose
	BSTR m_strCIecCfgDataSmvChBaseKey; //ch-smv
	BSTR m_strCIecCfgSmvDataBaseKey; //cfg-smv
	BSTR m_strCIecCfgAdvanceExceptionKey; //exception
	BSTR m_strCIecCfgDatasBaseKey; //cfg-datas
	BSTR m_strCIecCfgDataChBaseKey; //ch
	BSTR m_strCIecCfgDataBaseKey; //cfg-data
	BSTR m_strUseFlagKey; //use
	BSTR m_strChannelNumKey; //ch-num
	BSTR m_strFiberIndexKey; //fiber-ref
	BSTR m_strFiber2IndexKey; //
	BSTR m_strCtrlRefKey; //ctrl-index
	BSTR m_strCfgDataViewStateKey; //ctrl-index
	BSTR m_strIndexKey; //index
	BSTR m_strAppChIDKey; //app-ch
	BSTR m_strDevChIDKey; //dev-ch  //zhouhj 增加用于PNI302
	BSTR m_strMapDataIDKey; //map-id
	BSTR m_strDatasCountKey; //data-count
	BSTR m_strDatasUseKey; //use
	BSTR m_strExceptionTypeKey; //type
	BSTR m_strSerialNumErrKey; //serial-num-err
	BSTR m_strFrameLossGapKey; //frm-loss-gap
	BSTR m_strFrameLossPointsKey; //frm-loss-points
	BSTR m_strSynGapKey; //syn-gap
	BSTR m_strSynPointsKey; //syn-points
	BSTR m_strQualityGapKey; //quality-gap
	BSTR m_strQualityPointsKey; //quality-points
	BSTR m_strQualityValueKey; //quality-points
	BSTR m_strSerialJmpGapKey; //serial-jmp-gap
	BSTR m_strSerialJmpPointsKey; //serial-jmp-points
	BSTR m_strSerialJmpStepKey; //serial-jmp-step
	BSTR m_strFaultValGapKey; //fault-val-gap
	BSTR m_strFaultValPointsKey; //fault-val-points
	BSTR m_strFaultValRateKey; //fault-val-rate
	BSTR m_strExceptionFaultIntervalKey; //exception-begin-index
	BSTR m_strExceptionFaultCountKey; //exception-limit
	BSTR m_strExceptionFaultValueKey; //exception-count
	BSTR m_strExceptionBeginIndexKey; //exception-begin-index
	BSTR m_strExceptionLimitKey; //exception-limit
	BSTR m_strExceptionCountKey; //exception-count
	BSTR m_strUNomKey; //unom
	BSTR m_strINomKey; //inom
	BSTR m_strUNom2Key; //unom2
	BSTR m_strINom2Key; //inom2
	BSTR m_strFNomKey; //fnom
	BSTR m_strICenterKey; //icenter
	BSTR m_strSampleRateKey; //sample-rate
	BSTR m_strAsduNumKey; //asdu-num
	BSTR m_strNoQualityKey; //no-quality
	BSTR m_strCoefKey; //coef
	BSTR m_strUseExceptionKey; //coef
	BSTR m_strDestAddressKey; //addr-dest
	BSTR m_strSrcAddressKey; //addr-src
	BSTR m_strAppIDKey; //app-id
	BSTR m_strPriorityKey; //priority
	BSTR m_strVIDKey; //vid
	BSTR m_strVersionKey; //version
	BSTR m_strGooseIdKey; //goose-id
	BSTR m_strDataSetKey; //dataset
	BSTR m_strDataSetDescKey; //dataset-desc
	BSTR m_strgocbRefKey; //gocb-ref
	BSTR m_strgocbIEDKey; //gocb-ied
	BSTR m_strTestKey; //test
	BSTR m_strT0Key; //T0
	BSTR m_strT1Key; //T1
	BSTR m_strT2Key; //T2
	BSTR m_strT3Key; //T3
	BSTR m_strTGKey; //TGroup
	BSTR m_strTQKey; //TQuality
	BSTR m_strDataTypeKey; //data-type
	BSTR m_strSVIDKey; //svid
	BSTR m_strSynKey; //syn
	BSTR m_strCTBitKey; //ct-bit
	BSTR m_strPTBitKey; //pt-bit
	BSTR m_strDelayKey; //delay
	BSTR m_strUseSampRateKey; //use-samp-rate
	BSTR m_strUseDataSetKey; //use-dataset
	BSTR m_strUseSampleTimeKey; //use-smp-time
	BSTR m_strUseRefreshTimeKey; //use-refresh-time
	BSTR m_strUseEncruptKey; //use-encrupt
	BSTR m_strVoltateRateKey; //v-rate
	BSTR m_strCurrRateKey; //i-rate
	BSTR m_strValidityKey; //validity
	BSTR m_strSourceKey; //source
	BSTR m_strOverflowKey; //overflow
	BSTR m_strOutOfRangeKey; //overrange
	BSTR m_strBadindexKey; //bad-index
	BSTR m_strOscillationKey; //oscillation
	BSTR m_strBreakdownKey; //breakdown
	BSTR m_strObsoletedataKey; //obsolete-data
	BSTR m_strIncompatibleKey; //incompatible
	BSTR m_strInaccurateKey; //inaccurate
	BSTR m_strOperatorLockKey; //operatorLock
	BSTR m_strUITypeKey; //ui-type
	BSTR m_strAddrExternalKey; //addr-external
	BSTR m_strDescExternalKey; //desc-external
	BSTR m_strIndexExternalKey; //index-external
	BSTR m_strQualityKey; //quality
	BSTR m_strLNNameKey; //ln-name
	BSTR m_strLDNameKey; //ld-name
	BSTR m_strStateWordKey; //state-word
	BSTR m_strUseStateDataSetKey; //use-state-data-set
	BSTR m_strDataSetNameKey; //dataset-name
	BSTR m_strSmprateKey; //smp-rate
	BSTR m_strValidKey; //valid
	BSTR m_strObsoleteDataKey; //obsolete-data
	BSTR m_strFaultKey; //fault
	BSTR m_strDiscordKey; //discord
	BSTR m_strLeapSecondKey; //leap-second
	BSTR m_strReliableClockKey; //reliable-clock
	BSTR m_strReferenceSourceSynKey; //ref-src-syn
	BSTR m_strChTypeKey; //ch-type
	BSTR m_strDelayTimeKey; //delay-time
	BSTR m_strTransSpeedKey; //trans-speed
	BSTR m_strINomPhKey; //inom-ph
	BSTR m_strINomNeutralKey; //inom-neutral
	BSTR m_strUNomPhKey; //unom-ph
	BSTR m_strUseMacSrcAddrKey; //use-mac-src
	BSTR m_strUseMacDestAddrKey; //use-mac-dest
	BSTR m_strUseAppIDKey; //use-appid
	BSTR m_strUseGocbRefKey; //use-gocb-ref
	BSTR m_strUseGooseIDKey; //use-goose-id
	BSTR m_strEntrustKey; //entrust
	BSTR m_strSmvTypeKey; //smv-type
	BSTR m_strEnableSMVKey; //enable-smv
	BSTR m_strEnableGINKey; //enable-gin
	BSTR m_strEnableGOUTKey; //enable-gout
	BSTR m_strValueKey; //value
	BSTR m_strDataKey; //data
	BSTR m_strWhichKey; //which
	BSTR m_strMaxOutKey; //max-out
	BSTR m_strOffsetKey; //offset
	BSTR m_strUnitKey; //Unit
	BSTR m_strDigFlagKey; //dig-flag
	BSTR m_strFiberFlagKey; //fiiber-flag
	BSTR m_strProtocalFlagKey; //protocal-flag
	BSTR m_strTypeFlagKey; //type-flag
	BSTR m_strTypeFlagValueKey; //type-flag-val
	BSTR m_strChannelFlagKey; //channel-flag
	BSTR m_strDigWhichKey; //dig-witch
	BSTR m_strDigMaxOutKey; //dig-max-out
	BSTR m_strDigOffsetKey; //dig-offset
	BSTR m_strDefaultCfgFileKey; //default-cfg-file
	BSTR m_strLaIecCfgFileKey; //last-cfg-file
	BSTR m_strUseDebugKey; //last-cfg-file
	BSTR m_strAutoSetUIChIndexKey; //
	BSTR m_strPrimNomKey; //prim
	BSTR m_strSecNomKey; //prim
	BSTR m_strOutputKey; //output

	BSTR m_strPriValueKey; //last-cfg-file
	BSTR m_strSecValueKey; //prim
	BSTR m_strAnaValueKey; //output
	BSTR m_strChecksumKey; //prim
	BSTR m_strPolarityKey; //output

	BSTR m_strSendPortKey; //
	BSTR m_strNdsComKey; //
	BSTR m_strLiveTimeKey; //
	BSTR m_strAnalyzeKey; //
	BSTR m_strRateKey; //rate
	BSTR m_strCodeValueKey;//code-value
	BSTR m_strMeasCurrCodeValueKey;//meas-curr-code-value
	BSTR m_strPrimValueKey;//prim-value
	BSTR m_strAliasNameKey;//alias-name

	BSTR m_strIcdFileKey;   
	BSTR m_strGinChMapFileNameKey;//   "gin-ch-mapfile-name"  20220516 GOOSE订阅通道映射文件名称,山东自动测试需要每个ixml对应一个开入通道映射增加
	BSTR m_strDateKey;//"date"
	BSTR m_strXscdFileKey;

	//SCL 
	BSTR m_strIecCfgKey;
	BSTR m_strIecAbstrKey;

	BSTR m_strKey_iedStr;//CsclCtrlGsIn
	BSTR m_strKey_iedExtName;
	BSTR m_strKey_nChnRefCount;
	BSTR m_strKey_ldName_own;
	BSTR m_strKey_lnName_own;
	BSTR m_strKey_scl_datset_own;
	BSTR m_strKey_apName_own;

	BSTR m_strKey_fcda_map;//CSclChGsIn 
	BSTR m_strKey_fcda_type;
	BSTR m_strKey_fcda_lndesc;
	BSTR m_strKey_fcda_dodesc;
	BSTR m_strKey_fcda_desc;

	BSTR m_strKey_outIndex;
	BSTR m_strKey_inLNDesc;
	BSTR m_strKey_inDODesc;
	BSTR m_strKey_inDADesc;
	BSTR m_strKey_inIndex;
	BSTR m_strKey_inPath;
	BSTR m_strKey_outPath;

	BSTR m_strKey_inputRef_cdc;//inputRef_cdc
	BSTR m_strKey_inputRef_type;//inputRef_type

	BSTR m_strKey_fcda_name;//CSclChGsOut用


	BSTR m_strCtrlGsKey;//CsclCtrlGs
	BSTR m_strKey_gocbref;
	BSTR m_strKey_gocbref_path;
	BSTR m_strKey_scl_gcb_confRev;
	BSTR m_strKey_scl_gcb_APPID;
	BSTR m_strKey_scl_gse_APPID;
	BSTR m_strKey_scl_gse_VLANID;
	BSTR m_strKey_scl_gse_VLANPRI;
	BSTR m_strKey_scl_gse_MinTime;
	BSTR m_strKey_scl_gse_MaxTime;

	BSTR m_strKey_m_nSelect;//CsclCtrlBase
	BSTR m_strKey_ldName;

	BSTR m_strKey_LDdesc;//LDdesc
	BSTR m_strKey_ExLDdesc;//ExLDdesc
	BSTR m_strKey_ExIedDesc;//ExIedDesc

	BSTR m_strKey_lnName;
	BSTR m_strKey_scl_datset;
	BSTR m_strKey_scl_datset_path;
	BSTR m_strKey_apName;
	BSTR m_strKey_scl_dataset_desc;
	BSTR m_strKey_strMac;
	BSTR m_strKey_m_nChnCount;


	BSTR m_strKey_scl_svcb_smpRate;//CSclCtrlSmv
	BSTR m_strKey_scl_svcb_smvID;
	BSTR m_strKey_scl_svcb_nofASDU;
	BSTR m_strKey_scl_svcb_confRev;
	BSTR m_strKey_scl_smv_APPID;
	BSTR m_strKey_scl_smv_VLANID;
	BSTR m_strKey_scl_smv_VLANPRI;

	BSTR m_strCSclSvInChKey;//SvIn通道
	BSTR m_strCSclCtrlSvInKey;//SvIn
	BSTR m_strCSclCtrlsSvInKey;//SvIn

	BSTR m_strCSclSvOutChKey;//SvOut通道
	BSTR m_strCSclCtrlSvOutKey;//SvOut
	BSTR m_strCSclCtrlsSvOutKey;//SvOut

	BSTR m_strCSclGsInChKey;//GsIn通道
	BSTR m_strCSclCtrlGsInKey;//GsIn
	BSTR m_strCSclCtrlsGsInKey;//GsIn

	BSTR m_strCSclGsOutChKey;//GsOut通道
	BSTR m_strCSclCtrlGsOutKey;//GsOut
	BSTR m_strCSclCtrlsGsOutKey;//GsOut

	BSTR m_strKey_test_men;
	BSTR m_strKey_model_test;
	BSTR m_strKey_vcnln_test;
	BSTR m_strKey_macro_test;

	BSTR m_strCIecStationKey;
	BSTR m_strCSclIedKey;
	BSTR m_strCSclIedRefKey;
	BSTR m_strCSclBayVLevelKey;
	BSTR m_strCSclBayKey;

	BSTR m_strIedTypeKey;
	BSTR m_strIedTypeLabelKey;
	BSTR m_strIedTypeIDKey;
	BSTR m_strIedIPKey;
	BSTR m_strIedIPSUBNETKey;
	BSTR m_strIedIPGATEWAYKey;
	BSTR m_strManufacturerKey;

	BSTR m_strSmpCntType;  //smp-cnt-type
	BSTR m_strSampleDataLen;//sample-data-len
	BSTR m_strBlockType;//block-type
	BSTR m_strSCP;//SCP
	BSTR m_strSCM;//SCM
	BSTR m_strSV;//SV
	BSTR m_strBaudRate;//baud-rate
	BSTR m_strInomProt;//inom-prot
	BSTR m_strInomMeas;//inom-meas
	BSTR m_strDcVol;//dc-vol
	BSTR m_strDcCur;//dc-cur
	BSTR m_strDcNeutralVol;//dc-neutral-vol
	BSTR m_strDcVolPrim;//dc-vol-prim
	BSTR m_strDcCurPrim;//dc-cur-prim
	BSTR m_strDcNeutralVolPrim;//dc-neutral-vol-prim
	BSTR m_strProtocolIDKey;//protocol-id
	BSTR m_strChLenth;//ch-lenth

	BSTR m_strCIecCfgDatasSMVInputKey;//cfg-smvInput
	BSTR m_strCIecCfg92DoDescKey; //Do-desc
	BSTR m_strCIecCfgAccuracyLevelKey; //accuracy-level
	BSTR m_strCIecCfg92dUValKey; //dU-Val
	BSTR m_strCIecCfg92ChInKey;// ch-92In

	BSTR m_strCDataTypeTmpsKey; //DataTypeTemplates
	BSTR m_strCLNodeTypeKey; //LNodeType
	BSTR m_strCDOTypeKey; //DOType
	BSTR m_strCDATypeKey; //DAType
	BSTR m_strCEnumTypeKey; //EnumType

	BSTR m_strCDODetailKey; //DODetail
	BSTR m_strCDADetailKey; //DADetail
	BSTR m_strCBDADetailKey; //BDADetail
	BSTR m_strCEnumValKey; //EnumVal

	BSTR m_strLnClassKey; //lnClass
	BSTR m_strCDCKey; //cdc

	BSTR m_strObjTypeKey; //objType
	BSTR m_strSAddrKey; //sAddr
	BSTR m_strBTypeKey; //bType
	BSTR m_strValKindKey; //valKind
	BSTR m_strCountKey; //count
	BSTR m_strFCKey; //fc
	BSTR m_strSGroupKey; //sGroup

	BSTR m_strOrdKey; //ord

	BSTR m_strKey_GinPath;  //gin_path

	BSTR m_strCIecCfgFiberParaKey; //fiber-para   zhouhj 20210315
	BSTR m_strCIecCfgFiberParasKey; //fiber-paras
	BSTR m_strCIecCfgFiberParasInKey; //fiber-paras-in suyang 20230519
	BSTR m_strCIecCfgPrimRateKey; //prim-rate
	BSTR m_strCIecCfgPrimRatesKey; //prim-rates
	BSTR m_strCIecCfgPrimRatesInKey; //prim-rates-in
	BSTR m_strCIecCfgSysParasKey; //sys-paras
	BSTR m_strPkg_Send_TypeKey; //pkg-send-type
	BSTR m_strSec_SynKey; //sec-syn
	BSTR m_strBcode_LogicKey; //bcode-logic
	BSTR m_strIec1588_TypeKey; //iec1588-type
	BSTR m_strPrim_ParasKey; //prim-paras
	BSTR m_strPrim_OutputKey; //prim-output
	BSTR m_strPrim_ValueKey; //prim-value
	BSTR m_strSecond_ValueKey; //second-value

	BSTR m_strFT3_ProtocolIDKey;//ft3-protocol-id suyang 20240712
	BSTR m_strFT3_CRCTypeKey;

	BSTR m_strCIecCfg92Version;//9-2 报文类型 xueyangfan 20241029

public:
	static BSTR CIecCfgDeviceKey()  {   return g_pXmlKeys->m_strCIecCfgDeviceKey;  }
	static BSTR CIecCfgSmvRatesKey()  {   return g_pXmlKeys->m_strCIecCfgSmvRatesKey;  }
	static BSTR CIecCfgSmvRateKey()  {   return g_pXmlKeys->m_strCIecCfgSmvRateKey;  }
	static BSTR CIecCfgAnalogChKey()  {   return g_pXmlKeys->m_strCIecCfgAnalogChKey;  }
	static BSTR CIecCfgChsAnalogKey()  {   return g_pXmlKeys->m_strCIecCfgChsAnalogKey;  }
	static BSTR CIecCfgDataAnalogKey()  {   return g_pXmlKeys->m_strCIecCfgDataAnalogKey;  }
	static BSTR CIecCfgSystemConfigKey()  {   return g_pXmlKeys->m_strCIecCfgSystemConfigKey;  }
	static BSTR CArtAmpDigdatasKey()  {   return g_pXmlKeys->m_strCArtAmpDigdatasKey;  }
	static BSTR CArtAmpDigdataKey()  {   return g_pXmlKeys->m_strCArtAmpDigdataKey;  }
	static BSTR CIecCfg91StateWordMngrKey()  {   return g_pXmlKeys->m_strCIecCfg91StateWordMngrKey;  }
	static BSTR CIecCfg91StateWordBitKey()  {   return g_pXmlKeys->m_strCIecCfg91StateWordBitKey;  }
	static BSTR CIecCfg91StateWordKey()  {   return g_pXmlKeys->m_strCIecCfg91StateWordKey;  }
	static BSTR CIecCfg91StatusDataSetChKey()  {   return g_pXmlKeys->m_strCIecCfg91StatusDataSetChKey;  }
	static BSTR CIecCfgChsGoutKey()  {   return g_pXmlKeys->m_strCIecCfgChsGoutKey;  }
	static BSTR CIecCfgChsGinKey()  {   return g_pXmlKeys->m_strCIecCfgChsGinKey;  }
	static BSTR CIecCfgChs6044Key()  {   return g_pXmlKeys->m_strCIecCfgChs6044Key;  }
	static BSTR CIecCfgChs91Key()  {   return g_pXmlKeys->m_strCIecCfgChs91Key;  }
	static BSTR CIecCfgChs92Key()  {   return g_pXmlKeys->m_strCIecCfgChs92Key;  }
	static BSTR CIecCfgChs92InKey()  {   return g_pXmlKeys->m_strCIecCfgChs92InKey;  }
	static BSTR CIecCfgChsBaseKey()  {   return g_pXmlKeys->m_strCIecCfgChsBaseKey;  }
	static BSTR CIecCfgDatasMngrKey()  {   return g_pXmlKeys->m_strCIecCfgDatasMngrKey;  }
	static BSTR CIecCfgDatasGoutKey()  {   return g_pXmlKeys->m_strCIecCfgDatasGoutKey;  }
	static BSTR CIecCfgDatasAnalogKey()  {   return g_pXmlKeys->m_strCIecCfgDatasAnalogKey;  }
	static BSTR CIecCfgDatasGinKey()  {   return g_pXmlKeys->m_strCIecCfgDatasGinKey;  }
	static BSTR CIecCfgDatasSMVKey()  {   return g_pXmlKeys->m_strCIecCfgDatasSMVKey;  }
	static BSTR CIecCfgDatasSmvInKey()  {   return g_pXmlKeys->m_strCIecCfgDatasSmvInKey;  }
	static BSTR CIecCfgGoutChKey()  {   return g_pXmlKeys->m_strCIecCfgGoutChKey;  }
	static BSTR CIecCfgDataGoutKey()  {   return g_pXmlKeys->m_strCIecCfgDataGoutKey;  }
	static BSTR CIecCfgGinChKey()  {   return g_pXmlKeys->m_strCIecCfgGinChKey;  }
	static BSTR CIecCfgDataGinKey()  {   return g_pXmlKeys->m_strCIecCfgDataGinKey;  }
	static BSTR CIecCfg6044ChKey()  {   return g_pXmlKeys->m_strCIecCfg6044ChKey;  }
	static BSTR CIecCfg6044CommonChKey()  {   return g_pXmlKeys->m_strCIecCfg6044CommonChKey;  }
	static BSTR CIecCfg6044CommonChInKey()  {   return g_pXmlKeys->m_strCIecCfg6044CommonChInKey;  }
	static BSTR CIecCfgData6044Key()  {   return g_pXmlKeys->m_strCIecCfgData6044Key;  }
	static BSTR CIecCfgData6044CommonKey()  {   return g_pXmlKeys->m_strCIecCfgData6044CommonKey;  }
	static BSTR CIecCfgData6044CommonInKey()  {   return g_pXmlKeys->m_strCIecCfgData6044CommonInKey;  }
	static BSTR CIecCfgData2MKey()  {   return g_pXmlKeys->m_strCIecCfgData2MKey;  }
	static BSTR CIecCfgData2MInKey()  {   return g_pXmlKeys->m_strCIecCfgData2MInKey;  }
	static BSTR CIecCfg91ChKey()  {   return g_pXmlKeys->m_strCIecCfg91ChKey;  }
	static BSTR CIecCfg91StatusDataSetKey()  {   return g_pXmlKeys->m_strCIecCfg91StatusDataSetKey;  }
	static BSTR CIecCfgData91Key()  {   return g_pXmlKeys->m_strCIecCfgData91Key;  }
	static BSTR CIecCfg92ChKey()  {   return g_pXmlKeys->m_strCIecCfg92ChKey;  }
	static BSTR CIecCfg92ChQualityKey()  {   return g_pXmlKeys->m_strCIecCfg92ChQualityKey;  }
	static BSTR CIecCfgData92Key()  {   return g_pXmlKeys->m_strCIecCfgData92Key;  }
	static BSTR CIecCfgData92InKey()  {   return g_pXmlKeys->m_strCIecCfgData92InKey;  }
	static BSTR CIecCfgDataGooseChBaseKey()  {   return g_pXmlKeys->m_strCIecCfgDataGooseChBaseKey;  }
	static BSTR CIecCfgGooseDataBaseKey()  {   return g_pXmlKeys->m_strCIecCfgGooseDataBaseKey;  }
	static BSTR CIecCfgDataSmvChBaseKey()  {   return g_pXmlKeys->m_strCIecCfgDataSmvChBaseKey;  }
	static BSTR CIecCfgSmvDataBaseKey()  {   return g_pXmlKeys->m_strCIecCfgSmvDataBaseKey;  }
	static BSTR CIecCfgAdvanceExceptionKey()  {   return g_pXmlKeys->m_strCIecCfgAdvanceExceptionKey;  }
	static BSTR CIecCfgDatasBaseKey()  {   return g_pXmlKeys->m_strCIecCfgDatasBaseKey;  }
	static BSTR CIecCfgDataChBaseKey()  {   return g_pXmlKeys->m_strCIecCfgDataChBaseKey;  }
	static BSTR CIecCfgDataBaseKey()  {   return g_pXmlKeys->m_strCIecCfgDataBaseKey;  }
	static BSTR UseFlagKey()  {   return g_pXmlKeys->m_strUseFlagKey;  }
	static BSTR ChannelNumKey()  {   return g_pXmlKeys->m_strChannelNumKey;  }
	static BSTR FiberIndexKey()  {   return g_pXmlKeys->m_strFiberIndexKey;  }
	static BSTR Fiber2IndexKey()  {   return g_pXmlKeys->m_strFiber2IndexKey;  }
	static BSTR IndexKey()  {   return g_pXmlKeys->m_strIndexKey;  }
	static BSTR AppChIDKey()  {   return g_pXmlKeys->m_strAppChIDKey;  }
	static BSTR DevChIDKey()  {   return g_pXmlKeys->m_strDevChIDKey;  }
	static BSTR MapDataIDKey()  {   return g_pXmlKeys->m_strMapDataIDKey;  }
	static BSTR DatasCountKey()  {   return g_pXmlKeys->m_strDatasCountKey;  }
	static BSTR DatasUseKey()  {   return g_pXmlKeys->m_strDatasUseKey;  }
	static BSTR ExceptionTypeKey()  {   return g_pXmlKeys->m_strExceptionTypeKey;  }
	static BSTR SerialNumErrKey()  {   return g_pXmlKeys->m_strSerialNumErrKey;  }
	static BSTR FrameLossGapKey()  {   return g_pXmlKeys->m_strFrameLossGapKey;  }
	static BSTR FrameLossPointsKey()  {   return g_pXmlKeys->m_strFrameLossPointsKey;  }
	static BSTR SynGapKey()  {   return g_pXmlKeys->m_strSynGapKey;  }
	static BSTR SynPointsKey()  {   return g_pXmlKeys->m_strSynPointsKey;  }
	static BSTR QualityGapKey()  {   return g_pXmlKeys->m_strQualityGapKey;  }
	static BSTR QualityPointsKey()  {   return g_pXmlKeys->m_strQualityPointsKey;  }
	static BSTR SerialJmpGapKey()  {   return g_pXmlKeys->m_strSerialJmpGapKey;  }
	static BSTR SerialJmpPointsKey()  {   return g_pXmlKeys->m_strSerialJmpPointsKey;  }
	static BSTR SerialJmpStepKey()  {   return g_pXmlKeys->m_strSerialJmpStepKey;  }
	static BSTR FaultValGapKey()  {   return g_pXmlKeys->m_strFaultValGapKey;  }
	static BSTR FaultValPointsKey()  {   return g_pXmlKeys->m_strFaultValPointsKey;  }
	static BSTR FaultValRateKey()  {   return g_pXmlKeys->m_strFaultValRateKey;  }
	static BSTR ExceptionBeginIndexKey()  {   return g_pXmlKeys->m_strExceptionBeginIndexKey;  }
	static BSTR ExceptionLimitKey()  {   return g_pXmlKeys->m_strExceptionLimitKey;  }
	static BSTR ExceptionCountKey()  {   return g_pXmlKeys->m_strExceptionCountKey;  }
	static BSTR UNomKey()  {   return g_pXmlKeys->m_strUNomKey;  }
	static BSTR INomKey()  {   return g_pXmlKeys->m_strINomKey;  }
	static BSTR UNom2Key()  {   return g_pXmlKeys->m_strUNom2Key;  }
	static BSTR INom2Key()  {   return g_pXmlKeys->m_strINom2Key;  }
	static BSTR FNomKey()  {   return g_pXmlKeys->m_strFNomKey;  }
	static BSTR ICenterKey()  {   return g_pXmlKeys->m_strICenterKey;  }
	static BSTR SampleRateKey()  {   return g_pXmlKeys->m_strSampleRateKey;  }
	static BSTR AsduNumKey()  {   return g_pXmlKeys->m_strAsduNumKey;  }
	static BSTR NoQualityKey()  {   return g_pXmlKeys->m_strNoQualityKey;  }
	static BSTR CoefKey()  {   return g_pXmlKeys->m_strCoefKey;  }
	static BSTR DestAddressKey()  {   return g_pXmlKeys->m_strDestAddressKey;  }
	static BSTR SrcAddressKey()  {   return g_pXmlKeys->m_strSrcAddressKey;  }
	static BSTR AppIDKey()  {   return g_pXmlKeys->m_strAppIDKey;  }
	static BSTR PriorityKey()  {   return g_pXmlKeys->m_strPriorityKey;  }
	static BSTR VIDKey()  {   return g_pXmlKeys->m_strVIDKey;  }
	static BSTR VersionKey()  {   return g_pXmlKeys->m_strVersionKey;  }
	static BSTR GooseIdKey()  {   return g_pXmlKeys->m_strGooseIdKey;  }
	static BSTR DataSetKey()  {   return g_pXmlKeys->m_strDataSetKey;  }
	static BSTR DataSetDescKey()  {   return g_pXmlKeys->m_strDataSetDescKey;  }
	static BSTR gocbRefKey()  {   return g_pXmlKeys->m_strgocbRefKey;  }
	static BSTR gocbIEDKey()  {   return g_pXmlKeys->m_strgocbIEDKey;  }
	static BSTR TestKey()  {   return g_pXmlKeys->m_strTestKey;  }
	static BSTR T0Key()  {   return g_pXmlKeys->m_strT0Key;  }
	static BSTR T1Key()  {   return g_pXmlKeys->m_strT1Key;  }
	static BSTR T2Key()  {   return g_pXmlKeys->m_strT2Key;  }
	static BSTR T3Key()  {   return g_pXmlKeys->m_strT3Key;  }
	static BSTR TGKey()  {   return g_pXmlKeys->m_strTGKey;  }
	static BSTR TQKey()  {   return g_pXmlKeys->m_strTQKey;  }
	static BSTR DataTypeKey()  {   return g_pXmlKeys->m_strDataTypeKey;  }
	static BSTR SVIDKey()  {   return g_pXmlKeys->m_strSVIDKey;  }
	static BSTR SynKey()  {   return g_pXmlKeys->m_strSynKey;  }
	static BSTR CTBitKey()  {   return g_pXmlKeys->m_strCTBitKey;  }
	static BSTR PTBitKey()  {   return g_pXmlKeys->m_strPTBitKey;  }
	static BSTR DelayKey()  {   return g_pXmlKeys->m_strDelayKey;  }
	static BSTR UseSampRateKey()  {   return g_pXmlKeys->m_strUseSampRateKey;  }
	static BSTR UseDataSetKey()  {   return g_pXmlKeys->m_strUseDataSetKey;  }
	static BSTR UseSampleTimeKey()  {   return g_pXmlKeys->m_strUseSampleTimeKey;  }
	static BSTR UseRefreshTimeKey()  {   return g_pXmlKeys->m_strUseRefreshTimeKey;  }
	static BSTR UseEncruptKey()  {   return g_pXmlKeys->m_strUseEncruptKey;  }
	static BSTR VoltateRateKey()  {   return g_pXmlKeys->m_strVoltateRateKey;  }
	static BSTR CurrRateKey()  {   return g_pXmlKeys->m_strCurrRateKey;  }
	static BSTR ValidityKey()  {   return g_pXmlKeys->m_strValidityKey;  }
	static BSTR SourceKey()  {   return g_pXmlKeys->m_strSourceKey;  }
	static BSTR OverflowKey()  {   return g_pXmlKeys->m_strOverflowKey;  }
	static BSTR OverrangeKey()  {   return g_pXmlKeys->m_strOutOfRangeKey;  }
	static BSTR BadindexKey()  {   return g_pXmlKeys->m_strBadindexKey;  }
	static BSTR OscillationKey()  {   return g_pXmlKeys->m_strOscillationKey;  }
	static BSTR BreakdownKey()  {   return g_pXmlKeys->m_strBreakdownKey;  }
	static BSTR ObsoletedataKey()  {   return g_pXmlKeys->m_strObsoletedataKey;  }
	static BSTR IncompatibleKey()  {   return g_pXmlKeys->m_strIncompatibleKey;  }
	static BSTR InaccurateKey()  {   return g_pXmlKeys->m_strInaccurateKey;  }
	static BSTR OperatorLockKey()  {   return g_pXmlKeys->m_strOperatorLockKey;  }
	static BSTR UITypeKey()  {   return g_pXmlKeys->m_strUITypeKey;  }
	static BSTR AddrExternalKey()  {   return g_pXmlKeys->m_strAddrExternalKey;  }
	static BSTR DescExternalKey()  {   return g_pXmlKeys->m_strDescExternalKey;  }
	static BSTR QualityKey()  {   return g_pXmlKeys->m_strQualityKey;  }
	static BSTR LNNameKey()  {   return g_pXmlKeys->m_strLNNameKey;  }
	static BSTR LDNameKey()  {   return g_pXmlKeys->m_strLDNameKey;  }
	static BSTR StateWordKey()  {   return g_pXmlKeys->m_strStateWordKey;  }
	static BSTR UseStateDataSetKey()  {   return g_pXmlKeys->m_strUseStateDataSetKey;  }
	static BSTR DataSetNameKey()  {   return g_pXmlKeys->m_strDataSetNameKey;  }
	static BSTR SmprateKey()  {   return g_pXmlKeys->m_strSmprateKey;  }
	static BSTR ValidKey()  {   return g_pXmlKeys->m_strValidKey;  }
	static BSTR ObsoleteDataKey()  {   return g_pXmlKeys->m_strObsoleteDataKey;  }
	static BSTR FaultKey()  {   return g_pXmlKeys->m_strFaultKey;  }
	static BSTR DiscordKey()  {   return g_pXmlKeys->m_strDiscordKey;  }
	static BSTR LeapSecondKey()  {   return g_pXmlKeys->m_strLeapSecondKey;  }
	static BSTR ReliableClockKey()  {   return g_pXmlKeys->m_strReliableClockKey;  }
	static BSTR ReferenceSourceSynKey()  {   return g_pXmlKeys->m_strReferenceSourceSynKey;  }
	static BSTR ChTypeKey()  {   return g_pXmlKeys->m_strChTypeKey;  }
	static BSTR DelayTimeKey()  {   return g_pXmlKeys->m_strDelayTimeKey;  }
	static BSTR TransSpeedKey()  {   return g_pXmlKeys->m_strTransSpeedKey;  }
	static BSTR INomPhKey()  {   return g_pXmlKeys->m_strINomPhKey;  }
	static BSTR INomNeutralKey()  {   return g_pXmlKeys->m_strINomNeutralKey;  }
	static BSTR UNomPhKey()  {   return g_pXmlKeys->m_strUNomPhKey;  }
	static BSTR UseMacSrcAddrKey()  {   return g_pXmlKeys->m_strUseMacSrcAddrKey;  }
	static BSTR UseMacDestAddrKey()  {   return g_pXmlKeys->m_strUseMacDestAddrKey;  }
	static BSTR UseAppIDKey()  {   return g_pXmlKeys->m_strUseAppIDKey;  }
	static BSTR UseGocbRefKey()  {   return g_pXmlKeys->m_strUseGocbRefKey;  }
	static BSTR UseGooseIDKey()  {   return g_pXmlKeys->m_strUseGooseIDKey;  }
	static BSTR EntrustKey()  {   return g_pXmlKeys->m_strEntrustKey;  }
	static BSTR SmvTypeKey()  {   return g_pXmlKeys->m_strSmvTypeKey;  }
	static BSTR EnableSMVKey()  {   return g_pXmlKeys->m_strEnableSMVKey;  }
	static BSTR EnableGINKey()  {   return g_pXmlKeys->m_strEnableGINKey;  }
	static BSTR EnableGOUTKey()  {   return g_pXmlKeys->m_strEnableGOUTKey;  }
	static BSTR ValueKey()  {   return g_pXmlKeys->m_strValueKey;  }
	static BSTR WhichKey()  {   return g_pXmlKeys->m_strWhichKey;  }
	static BSTR MaxOutKey()  {   return g_pXmlKeys->m_strMaxOutKey;  }
	static BSTR OffsetKey()  {   return g_pXmlKeys->m_strOffsetKey;  }
	static BSTR UnitKey()  {   return g_pXmlKeys->m_strUnitKey;  }
	static BSTR DigFlagKey()  {   return g_pXmlKeys->m_strDigFlagKey;  }
	static BSTR FiberFlagKey()  {   return g_pXmlKeys->m_strFiberFlagKey;  }
	static BSTR ProtocalFlagKey()  {   return g_pXmlKeys->m_strProtocalFlagKey;  }
	static BSTR TypeFlagKey()  {   return g_pXmlKeys->m_strTypeFlagKey;  }
	static BSTR TypeFlagValueKey()  {   return g_pXmlKeys->m_strTypeFlagValueKey;  }
	static BSTR ChannelFlagKey()  {   return g_pXmlKeys->m_strChannelFlagKey;  }
	static BSTR DigWhichKey()  {   return g_pXmlKeys->m_strDigWhichKey;  }
	static BSTR DigMaxOutKey()  {   return g_pXmlKeys->m_strDigMaxOutKey;  }
	static BSTR DigOffsetKey()  {   return g_pXmlKeys->m_strDigOffsetKey;  }
	static BSTR DefaultCfgFileKey()  {   return g_pXmlKeys->m_strDefaultCfgFileKey;  }
	static BSTR LaIecCfgFileKey()  {   return g_pXmlKeys->m_strLaIecCfgFileKey;  }
	static BSTR SendPortKey()  {   return g_pXmlKeys->m_strSendPortKey;  }
	static BSTR NdsComKey()  {   return g_pXmlKeys->m_strNdsComKey;  }
	static BSTR LiveTimeKey()  {   return g_pXmlKeys->m_strLiveTimeKey;  }
	static BSTR AnalyzeKey()  {   return g_pXmlKeys->m_strAnalyzeKey;  }
	static BSTR RateKey()  {   return g_pXmlKeys->m_strRateKey;  }
	static BSTR CodeValueKey ()  {   return g_pXmlKeys->m_strCodeValueKey;  }
	static BSTR MeasCurrCodeValueKey ()  {   return g_pXmlKeys->m_strMeasCurrCodeValueKey;  }
	static BSTR PrimValueKey ()  {   return g_pXmlKeys->m_strPrimValueKey;  }
	static BSTR AliasNameKey ()  {   return g_pXmlKeys->m_strAliasNameKey;  }


	static BSTR CIecCfgKey()  {   return g_pXmlKeys->m_strIecCfgKey;  }
	static BSTR CIecAbstrKey()  {   return g_pXmlKeys->m_strIecAbstrKey;  }
	static BSTR CSclCtrlGsKey(){ return g_pXmlKeys->m_strCtrlGsKey;}

	static BSTR CSclSvInChKey()  {   return g_pXmlKeys->m_strCSclSvInChKey;  }
	static BSTR CSclCtrlSvInKey()  {   return g_pXmlKeys->m_strCSclCtrlSvInKey;  }
	static BSTR CSclCtrlsSvInKey()  {   return g_pXmlKeys->m_strCSclCtrlsSvInKey;  }

	static BSTR CSclSvOutChKey()  {   return g_pXmlKeys->m_strCSclSvOutChKey;  }
	static BSTR CSclCtrlSvOutKey()  {   return g_pXmlKeys->m_strCSclCtrlSvOutKey;  }
	static BSTR CSclCtrlsSvOutKey()  {   return g_pXmlKeys->m_strCSclCtrlsSvOutKey;  }

	static BSTR CSclGsInChKey()  {   return g_pXmlKeys->m_strCSclGsInChKey;  }
	static BSTR CSclCtrlGsInKey()  {   return g_pXmlKeys->m_strCSclCtrlGsInKey;  }
	static BSTR CSclCtrlsGsInKey()  {   return g_pXmlKeys->m_strCSclCtrlsGsInKey;  }

	static BSTR CSclGsOutChKey()  {   return g_pXmlKeys->m_strCSclGsOutChKey;  }
	static BSTR CSclCtrlGsOutKey()  {   return g_pXmlKeys->m_strCSclCtrlGsOutKey;  }
	static BSTR CSclCtrlsGsOutKey()  {   return g_pXmlKeys->m_strCSclCtrlsGsOutKey;  }

	static BSTR CSclStationKey()  {   return g_pXmlKeys->m_strCIecStationKey;  }
	static BSTR CSclIedKey()  {   return g_pXmlKeys->m_strCSclIedKey;  }
	static BSTR CSclIedRefKey()  {   return g_pXmlKeys->m_strCSclIedRefKey;  }
	static BSTR CSclBayVLevelKey()  {   return g_pXmlKeys->m_strCSclBayVLevelKey;  }
	static BSTR CSclBayKey()  {   return g_pXmlKeys->m_strCSclBayKey;  }

	static BSTR CIecCfgDatasSMVInputKey()  {   return g_pXmlKeys->m_strCIecCfgDatasSMVInputKey;  }
	static BSTR CIecCfg92DoDescKey()  {   return g_pXmlKeys->m_strCIecCfg92DoDescKey;  }
	static BSTR CIecCfgAccuracyLevelKey()  {   return g_pXmlKeys->m_strCIecCfgAccuracyLevelKey;  }
	static BSTR CIecCfg92dUValKey()  {   return g_pXmlKeys->m_strCIecCfg92dUValKey;  }
	static BSTR CIecCfg92ChInKey()  {   return g_pXmlKeys->m_strCIecCfg92ChInKey;  }


	static BSTR CIecCfgFiberParaKey()  {   return g_pXmlKeys->m_strCIecCfgFiberParaKey;  }//zhouhj20210315
	static BSTR CIecCfgFiberParasKey()  {   return g_pXmlKeys->m_strCIecCfgFiberParasKey;  }
	static BSTR CIecCfgFiberParasInKey()  {   return g_pXmlKeys->m_strCIecCfgFiberParasInKey;  }//suyang20230519

	static BSTR CIecCfgPrimRateKey()  {   return g_pXmlKeys->m_strCIecCfgPrimRateKey;  }
	static BSTR CIecCfgPrimRatesKey()  {   return g_pXmlKeys->m_strCIecCfgPrimRatesKey;  }
	static BSTR CIecCfgPrimRatesInKey()  {   return g_pXmlKeys->m_strCIecCfgPrimRatesInKey;  }
	static BSTR CIecCfgSysParasKey()  {   return g_pXmlKeys->m_strCIecCfgSysParasKey;  }
	static BSTR Pkg_Send_TypeKey()  {   return g_pXmlKeys->m_strPkg_Send_TypeKey;  }
	static BSTR Sec_SynKey()  {   return g_pXmlKeys->m_strSec_SynKey;  }
	static BSTR Bcode_LogicKey()  {   return g_pXmlKeys->m_strBcode_LogicKey;  }
	static BSTR Iec1588_TypeKey()  {   return g_pXmlKeys->m_strIec1588_TypeKey;  }
	static BSTR Prim_ParasKey()  {   return g_pXmlKeys->m_strPrim_ParasKey;  }
	static BSTR Prim_OutputKey()  {   return g_pXmlKeys->m_strPrim_OutputKey;  }
	static BSTR Prim_ValueKey()  {   return g_pXmlKeys->m_strPrim_ValueKey;  }
	static BSTR Second_ValueKey()  {   return g_pXmlKeys->m_strSecond_ValueKey;  }


public:
	static BSTR CDataTypeTmpsKey()  {   return g_pXmlKeys->m_strCDataTypeTmpsKey;  }
	static BSTR CLNodeTypeKey()  {   return g_pXmlKeys->m_strCLNodeTypeKey;  }
	static BSTR CDOTypeKey()  {   return g_pXmlKeys->m_strCDOTypeKey;  }
	static BSTR CDATypeKey()  {   return g_pXmlKeys->m_strCDATypeKey;  }
	static BSTR CEnumTypeKey()  {   return g_pXmlKeys->m_strCEnumTypeKey;  }

	static BSTR CDODetailKey()  {   return g_pXmlKeys->m_strCDODetailKey;  }
	static BSTR CDADetailKey()  {   return g_pXmlKeys->m_strCDADetailKey;  }
	static BSTR CBDADetailKey()  {   return g_pXmlKeys->m_strCBDADetailKey;  }
	static BSTR CEnumValKey()  {   return g_pXmlKeys->m_strCEnumValKey;  }

};



class CCfgDataMngrConstGlobal
{
private:
	CCfgDataMngrConstGlobal();
	virtual ~CCfgDataMngrConstGlobal();

public:
	static CCfgDataMngrConstGlobal* Create();
	static void Release();

	static CDataTypes* GetIecRtdDataTypes();
	static CDataType* FindIecRtdDataType(const  CString &strDataTypeID);

	static BOOL IsViewOnlyUsedInChs();
	static BOOL SetViewOnlyUsedInChs(long nViewOnlyUsedInChs);
	static void UpdataAppPortDataType_FiberNum(long nFiberNum);//zhouhj 20211201 更新全局唯一对象中的光口数量
	static void UpdataDataType_BinExNum(long nBinExNum);//zhouhj 20211201 更新全局唯一对象中扩展开入数量
	static void UpdataDataType_BoutExNum(long nBoutExNum);//zhouhj 20211201 更新全局唯一对象中扩展开出数量
	static void Update_GinAppChDataType();//zhouhj 20220428 重新更新Gin通道映射的内容
	static long GetAppPortFiberNum_LC();//2023.7.20 zhouhj 获取LC光口的数量

	static long GetAppPortFT3Num_ST();//2023.11.29 suyang  获取ST口的数量
	static void UpdataAppPortDataType_FT3Num(long nFT3Num);//2023.11.29 suyang 更新全局唯一对象中的FT3数量
	static long GetAppPortFT3InNum_ST();//2023.11.29 suyang  获取ST接收口的数量
	static void UpdataAppPortDataType_FT3InNum(long nFT3InNum);//2023.11.29 suyang 更新全局唯一对象中的FT3接收数量
private:
	static long g_nGlobalRef;
	static CCfgDataMngrConstGlobal *g_pGlobal;

	void InitGlobal();
	CDataTypes m_oIecRtdDataTypes;
	long m_nViewOnlyUsedInChs;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()
	void ValidAddDataTypes();//验证新添加的DataTypes是否存在,如果不存在则创建保存

	void Init_Smv92ChDataType();  //_T("Smv92ChDataType");
	void Init_Smv91ChDataType();  //_T("Smv91ChDataType");
	void Init_Smv6044ChDataType();  //_T("Smv6044ChDataType");
	void Init_SmvCommon6044ChDataType(BOOL bValid = FALSE);  //_T("SmvCommon6044ChDataType");
	void Init_SmvCommon6044DCChDataType(BOOL bValid = FALSE);  //_T("SmvCommon6044DCChDataType");
	void Init_SmvCommon6044ChInDataType(BOOL bFindRepeat = FALSE);  //_T("SmvCommon6044ChInDataType");
// 	void Init_SmvChDataType_Val_Vol();  //_T("Vol");
// 	void Init_SmvChDataType_Val_Curr();  //_T("Curr");
// 	void Init_SmvChDataType_Val_CurrProt();  //_T("Curr");
// 	void Init_SmvChDataType_Val_CurrMeasure();  //_T("CurrMeasure");
// 	void Init_SmvChDataType_Val_UTCTime();  //_T("UTCTime");

	void Init_SmvChAngType(BOOL bFindRepeat = FALSE);    //_T("SmvChAngType")
	void Init_SmvAppChDataType();  //_T("SmvAppChDataType");
	void Init_SmvAppChDataType_U();  //_T("SmvAppChDataType_U");
	void Init_SmvAppChDataType_I();  //_T("SmvAppChDataType_I");
	void Init_SmvAppChDataType_T();  //_T("SmvAppChDataType_T");

	void Init_SmvInAppChAccLevelDataType_U();  //iecfg_SmvInAppChAccLevelDataType_U
	void Init_SmvInAppChAccLevelDataType_I();  //iecfg_SmvInAppChAccLevelDataType_I

	void Init_SclCtrlAppDataType_Goose();  //_T("SclCtrlAppDataType_Goose");
	void Init_SmvAppChDataType_DCU(BOOL bValid = FALSE);
	void Init_SmvAppChDataType_DCI(BOOL bValid = FALSE);
	void Init_SmvAppChDataType_NeutralU();
	void Init_SmvAppChDataType_StateValue();  //_T("SmvAppChDataType_T");
	void Init_SmvAppChDataType_Other();  //_T("Other");

	void Init_SmvAppChDataType_6U();  //_T("SmvAppChDataType_6U");
	void Init_SmvAppChDataType_6I();  //_T("SmvAppChDataType_6I");

	void Init_SmvChByteLenDataType();  //_T("SmvChByteLen");
	void Init_BlockInx_2MDataType();  //_T("BlockInx_2M");
	void Init_PkgType_2MDataType();  //_T("PkgType_2M");

// 	void Init_BOutChDataType();  //_T("BOutChDataType");
// 	void Init_Cfg6044Speed();  //_T("Cfg6044Speed");
	void Init_GooseChDataType();  //_T("GooseChDataType");
	void Init_GoutAppChDataType();  //_T("GoutAppChDataType");
	void Init_GinAppChDataType();  //_T("GinAppChDataType");

	void Init_STFiberDataType();  //_T("STFiberDataType");
	void Init_LCFiberDataType();  //_T("LCFiberDataType");
	void Init_TesterSubPubDataType();  //_T("TesterSubPubDataType");
	void Init_STFiberInDataType();  //_T("STFiberInDataType");

	void Init_AppPortDataType_Fiber(long nFiberNum = MAX_FIBER_PORT_NUM);  //_T("AppFiberPort");
	void Init_AppPortDataType_SmpByteNum();  //_T("SmpByteNum");zhouhj 增加用于采样位宽设置
	void Init_AppPortDataType_SmpCntType();  //_T("SmpCntType");zhouhj 增加用于采样方式设置(采样计数器的使用方式)
	void Init_AppPortDataType_Ft3(BOOL bFindRepeat = FALSE);  //_T("AppFt3Port");
	void Init_AppPortDataType_Ft3In(BOOL bFindRepeat = FALSE);  //_T("AppFt3InPort");

	void Init_AppSynDataType_Fiber();  //_T("AppSynMode");
	void Init_AppTestSetDataType(BOOL bFindRepeat = FALSE);  //_T("AppTestSet");

	void Init_Quality_DataTypes(); 
	void Init_goose_ch_DataTypes(); 
public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};

#define PROTOCOL_61850_TYPE_92      1
#define PROTOCOL_61850_TYPE_GOOSEOUT   2
#define PROTOCOL_61850_TYPE_6044   3
#define PROTOCOL_61850_TYPE_91      4
#define PROTOCOL_61850_TYPE_GOOSEIN   5
#define PROTOCOL_61850_TYPE_ANALOG  6
#define PROTOCOL_61850_TYPE_NONE    0XFF
#define PROTOCOL_61850_TYPE_GOOSE   0x1F


inline BOOL iecfg_IsTypeGoose(UINT nType)
{
	return ( (nType == PROTOCOL_61850_TYPE_GOOSEOUT) 
		|| (nType == PROTOCOL_61850_TYPE_GOOSEIN)
		|| (nType == PROTOCOL_61850_TYPE_GOOSE));
}

//shaolei 20220421
inline BOOL iecfg_IsTypeAnalog(UINT nType)
{
    return ( (nType == PROTOCOL_61850_TYPE_92)
        || (nType == PROTOCOL_61850_TYPE_6044)
        || (nType == PROTOCOL_61850_TYPE_91)
        ||(nType == PROTOCOL_61850_TYPE_ANALOG));
}

inline CString iecfg_Get61850ProtocolType(UINT nType)
{
	switch (nType)
	{
	case PROTOCOL_61850_TYPE_91:
		return _T("9-1");

	case PROTOCOL_61850_TYPE_92:
		return _T("9-2");

	case PROTOCOL_61850_TYPE_GOOSEIN:
		return _T("GOOSEIN");

	case PROTOCOL_61850_TYPE_GOOSEOUT:
		return _T("GOOSEOUT");

	case PROTOCOL_61850_TYPE_6044:
		return _T("IEC60044-8(FT3)");

	case PROTOCOL_61850_TYPE_ANALOG:
		return _T("Analog");

	case PROTOCOL_61850_TYPE_GOOSE:
		return _T("GOOSE");

	}

	return _T("------");
}

#define CFG_CAP_FILE_CFGDATASMNGR   _T("IecCfgCapConfig.xml")
#define CFG_CAP_FILE_CFGDATA        _T("IecCfgCapCfgData.xml")
static const CString CFG_IECCFG_DATATYPES_FILE =  _T("IecCfgDataTypes.xml");

CString iecfg_GetCfgCapFileCfgDatasMngr();
CString iecfg_GetCfgCapFileCfgData();


//////////////////////////////////////////////////////////////////////////
#define CFGDATAID_FIBER    0X0001
#define CFGDATAID_APPID    0X0002
#define CFGDATAID_SRCMAC   0X0003
#define CFGDATAID_DESTMAC  0X0004

#define CFGDATAID_INOM2   0X0005
#define CFGDATAID_UNOM2   0X0006

#define CFGDATAID_CHCECKSUM   0X0007
#define CFGDATAID_POLARITY   0X0008

//数据类型定义
static const CString iecfg_Smv92ChDataType     = _T("Smv92ChDataType");
static const CString iecfg_Smv91ChDataType     = _T("Smv91ChDataType");
static const CString iecfg_Smv6044ChDataType     = _T("Smv6044ChDataType");
//zhouhj 20211011 增加用于CommonFT3  2023.10.10 改为用于通用FT3
static const CString iecfg_SmvCommon6044ChDataType     = _T("SmvCommon6044ChDataType");
//zhouhj 20231010 增加用于单独的柔直FT3
static const CString iecfg_SmvCommon6044DCChDataType     = _T("SmvCommon6044DCChDataType");
static const CString iecfg_SmvCommon6044ChInDataType     = _T("SmvCommon6044ChInDataType");
static const CString iecfg_SmvChDataType_Val_Vol = _T("Vol");
static const CString iecfg_SmvChDataType_Val_Curr = _T("Curr");
static const CString iecfg_SmvChDataType_Val_CurrProt = _T("Curr");
static const CString iecfg_SmvChDataType_Val_CurrMeasure = _T("CurrMeasure");
static const CString iecfg_SmvChDataType_Val_DCVol = _T("DCVol");//zhouhj 20211012 直流电压
static const CString iecfg_SmvChDataType_Val_DCCur = _T("DCCur");//zhouhj 20211012 直流电流
static const CString iecfg_SmvChDataType_Val_NeutralU = _T("NeutralU");//zhouhj 20211012 中性母线电压
static const CString iecfg_SmvChDataType_Val_UTCTime = _T("UTCTime");

static const CString iecfg_SmvChDataType_Val_6Vol = _T("6Vol");
static const CString iecfg_SmvChDataType_Val_6CurrProt = _T("6Curr");
static const CString iecfg_SmvChDataType_Val_6CurrMeasure = _T("6CurrMeasure");

static const CString iecfg_SmvChDataType_Val_StateValue = _T("StateValue");//zhouhj 20211012 增加用于状态值
static const CString iecfg_SmvChDataType_Val_Other = _T("Other");//zhouhj 20211012 增加用于其它

static const CString iecfg_SmvAppChDataType    = _T("SmvAppChDataType");
static const CString iecfg_SmvAppChDataType_U    = _T("SmvAppChDataType_U");
static const CString iecfg_SmvAppChDataType_I    = _T("SmvAppChDataType_I");
static const CString iecfg_SmvAppChDataType_T    = _T("SmvAppChDataType_T");

static const CString iecfg_SmvChAngType     = _T("SmvChAngType");//20221210 zhouhj  通道相位类别
static const CString iecfg_SmvChAngTypeU     = _T("SmvChAngTypeU");//20240103 dingxiaoya  通道相位类别(电压)
static const CString iecfg_SmvChAngTypeI     = _T("SmvChAngTypeI");//20240103 dingxiaoya  通道相位类别(电流)


static const CString iecfg_SmvInAppChAccLevelDataType_U    = _T("SmvInAppChAccLevelDataType_U");
static const CString iecfg_SmvInAppChAccLevelDataType_I    = _T("SmvInAppChAccLevelDataType_I");

static const CString iecfg_SmvAppChDataType_DCU    = _T("SmvAppChDataType_DCU");//zhouhj 20211012  直流电压
static const CString iecfg_SmvAppChDataType_DCI    = _T("SmvAppChDataType_DCI");//zhouhj 20211012   直流电流
static const CString iecfg_SmvAppChDataType_NeutralU    = _T("SmvAppChDataType_NeutralU");//zhouhj 20211012  直流中性点母线电压
static const CString iecfg_SmvAppChDataType_StateValue    = _T("SmvAppChDataType_StateValue");//zhouhj 20211012 增加用于状态值
static const CString iecfg_SmvAppChDataType_Other    = _T("SmvAppChDataType_Other");//zhouhj 20211012 增加用于Other
static const CString iecfg_SmvAppChDataType_6U    = _T("SmvAppChDataType_6U");//zhouhj 20211109柔直FT3采用直流+交流9U9I
static const CString iecfg_SmvAppChDataType_6I    = _T("SmvAppChDataType_6I");//zhouhj 20211109柔直FT3采用直流+交流9U9I

static const CString iecfg_SmvChByteLen    = _T("SmvChByteLen");//zhouhj 20211011 增加用于CommonFT3中的单个通道的字节长度

static const CString iecfg_SclCtrlAppDataType_Smv    = _T("SclCtrlAppDataType_Smv");//zhouhj 20211027 增加用于选择Smv发布、订阅
static const CString iecfg_SclCtrlAppDataType_Goose    = _T("SclCtrlAppDataType_Goose");//zhouhj 20211027 增加用于选择Goose发布、订阅

static const CString iecfg_BlockInx_2M    = _T("BlockInx_2M");//zhouhj 20220805 增加用于2M控制块的Inx
static const CString iecfg_PkgType_2M    = _T("PkgType_2M");//zhouhj 20220805 增加用于2M控制块的Inx

static const CString iecfg_BOutChDataType      = _T("BOutChDataType");
static const CString iecfg_Cfg6044Speed       = _T("Cfg6044Speed");
static const CString iecfg_GooseChDataType      = _T("GooseChDataType");
static const CString iecfg_GoutAppChDataType   = _T("GoutAppChDataType");
static const CString iecfg_GinAppChDataType    = _T("GinAppChDataType");

static const CString g_strAppPortDataType_Fiber = _T("AppFiberPort");
static const CString g_strAppPortDataType_Ft3   = _T("AppFt3Port");
static const CString g_strAppPortDataType_Ft3In   = _T("AppFt3InPort");//2023-11-29 suyang 增加FT3接收光口
static const CString g_strSynModeDataType_Fiber = _T("AppSynMode");
static const CString g_strAppTestSetDataType = _T("AppTestSet");//20220902 zhouhj  检修设置
static const CString g_strAppPortDataType_SmpByteNum = _T("SmpByteNum");//zhouhj 20211011 增加用于公共FT3的采样位宽
static const CString g_strAppPortDataType_SmpCntType = _T("SmpCntType");//zhouhj 20211011 增加用于采样方式

static const CString iecfg_ST_FiberDataType      = _T("STFiberDataType");//20220731 zhouhj 增加用于光口设置
static const CString iecfg_LC_FiberDataType      = _T("LCFiberDataType");
static const CString iecfg_ST_FiberInDataType      = _T("STFiberInDataType");//20230519 suyang 增加用于接收光口设置

static const CString iecfg_TesterSubPubDataType      = _T("TesterSubPubDataType");//20220731 zhouhj 增加用于光口设置

static const CString g_strAppChID_TRUE = _T("TRUE");
static const CString g_strAppChID_FALSE = _T("FALSE");
static const CString g_strAppChID_None = _T("none");
static const CString g_strAppChID_Zero = _T("zero");
static const CString g_strAppChID_UTCTime = _T("UTCTime");

static const CString g_strChTypeDT_Voltage = _T("voltage");
static const CString g_strChTypeDT_prot = _T("prot");
static const CString g_strChTypeDT_measure = _T("measure");

static const CString g_strGsChDtID_goose_ch_type       = _T("goose-ch-type");
extern CString g_strGsChDtID_goose_in_ch; //zhouhj 20220428 山东自动测试项目,需要根据被测装置类型切换显示通道映射
static const CString g_strGsChDtID_goose_out_ch_single = _T("goose-out-ch-single");
static const CString g_strGsChDtID_goose_out_ch_double = _T("goose-out-ch-double");

static const CString g_strGsChDtID_goose_out_ch_single_def_value = _T("goose-out-ch-single-def-value");
static const CString g_strGsChDtID_goose_out_ch_double_def_value = _T("goose-out-ch-double-def-value");

static const CString g_strGooseChType_Single       = _T("BOOLEAN");
static const CString g_strGooseChType_Double       = _T("Dbpos");
static const CString g_strGooseChType_Time         = _T("Timestamp");
static const CString g_strGooseChType_Quality      = _T("Quality");
static const CString g_strGooseChType_Float        = _T("FLOAT32");
static const CString g_strGooseChType_String       = _T("VisString64");
static const CString g_strGooseChType_Struct       = _T("Struct");
static const CString g_strGooseChType_Integer       = _T("INT32");
static const CString g_strGooseChType_UInteger       = _T("INT32U");

static const CString g_strAppChID_TDelay = _T("t-delay");
static const CString g_strAppChID_SmpCnt = _T("SmpCnt");

#define  DT_GooseChType_Single   0x01
#define  DT_rGooseChType_Double  0x02
#define  DT_rGooseChType_Time    0x03
#define  DT_rGooseChType_Quality 0x84
#define  DT_rGooseChType_Integer 0x85
#define  DT_rGooseChType_Float   0x87
#define  DT_rGooseChType_String  0x8a
#define  DT_rGooseChType_Struct  0x8b

//////////////////////////////////////////////////////////////////////////
//
inline void iecfg_ValidateMiMax(long &Value, long Min, long Max)
{
	if (Value < Min)
	{
		Value = Min;
	}

	if (Value > Max)
	{
		Value = Max;
	}
}


inline void iecfg_ValidateMiMax(double &Value, double Min, double Max)
{
	if (Value < Min)
	{
		Value = Min;
	}

	if (Value > Max)
	{
		Value = Max;
	}
}


inline void iecfg_ValidateMiMax(float &Value, float Min, float Max)
{
	if (Value < Min)
	{
		Value = Min;
	}

	if (Value > Max)
	{
		Value = Max;
	}
}


inline void iecfg_ValidateMiMax(DWORD &Value, DWORD Min, DWORD Max)
{
	if (Value < Min)
	{
		Value = Min;
	}

	if (Value > Max)
	{
		Value = Max;
	}
}

inline BOOL iecfg_IsValidateMiMax(long &Value, long Min, long Max)
{
	return ((Min <= Value) && (Value <= Max));
}


inline BOOL iecfg_IsValidateMiMax(double &Value, double Min, double Max)
{
	return ((Min <= Value) && (Value <= Max));
}

inline BOOL iecfg_IsValidateMiMax(float &Value, float Min, float Max)
{
	return ((Min <= Value) && (Value <= Max));
}

inline BOOL iecfg_IsValidateMiMax(DWORD &Value, DWORD Min, DWORD Max)
{
	return ((Min <= Value) && (Value <= Max));
}

inline long iecfg_ValidateChsMiMax(long nSmvChs)
{
	if (nSmvChs < 1)
	{
		return 1;
	}

	if (nSmvChs > 100)		//程序中不做限制，解析后VM中再做限制
	{
		return 100;
	}

	return nSmvChs;
}

inline BOOL iecfg_IsCurrSmvChType(const CString &strChType)
{
	if (strChType == iecfg_SmvChDataType_Val_Curr)
	{
		return TRUE;
	}

	if (strChType == iecfg_SmvChDataType_Val_CurrProt)
	{
		return TRUE;
	}

	if (strChType == iecfg_SmvChDataType_Val_CurrMeasure)
	{
		return TRUE;
	}

	return FALSE;
}

inline BOOL iecfg_IsVolSmvChType(const CString &strChType)
{
	if (strChType == iecfg_SmvChDataType_Val_Vol)
	{
		return TRUE;
	}

	return FALSE;
}


inline BOOL iecfg_Is6CurrSmvChType(const CString &strChType)
{
	if (strChType == iecfg_SmvChDataType_Val_6CurrProt)
	{
		return TRUE;
	}

	if (strChType == iecfg_SmvChDataType_Val_6CurrMeasure)
	{
		return TRUE;
	}

	return FALSE;
}

inline BOOL iecfg_Is6VolSmvChType(const CString &strChType)
{
	if (strChType == iecfg_SmvChDataType_Val_6Vol)
	{
		return TRUE;
	}

	return FALSE;
}

inline BOOL iecfg_IsDCVolSmvChType(const CString &strChType)//zhouhj 20211012 直流电压
{
	if (strChType == iecfg_SmvChDataType_Val_DCVol)
	{
		return TRUE;
	}

	return FALSE;
}

inline BOOL iecfg_IsDCCurSmvChType(const CString &strChType)//zhouhj 20211012 直流电流
{
	if (strChType == iecfg_SmvChDataType_Val_DCCur)
	{
		return TRUE;
	}

	return FALSE;
}

inline BOOL iecfg_IsNeutralUSmvChType(const CString &strChType)//zhouhj 20211012 中性母线电压
{
	if (strChType == iecfg_SmvChDataType_Val_NeutralU)
	{
		return TRUE;
	}

	return FALSE;
}

inline BOOL iecfg_IsUTCTimeSmvChType(const CString &strChType)
{
	if (strChType == iecfg_SmvChDataType_Val_UTCTime)
	{
		return TRUE;
	}

	return FALSE;
}

inline BOOL iecfg_IsStateValueChType(const CString &strChType)//zhouhj 20211012 增加用于CommonFT3 状态值
{
	if (strChType == iecfg_SmvChDataType_Val_StateValue)
	{
		return TRUE;
	}

	return FALSE;
}

inline BOOL iecfg_IsOtherChType(const CString &strChType)//zhouhj 20211012 增加用于CommonFT3 其它
{
	if (strChType == iecfg_SmvChDataType_Val_Other)
	{
		return TRUE;
	}

	return FALSE;
}

#define WM_IECCFGDATA_CHANGED      (WM_USER+1746)
#define WM_IECCFGDATA_CHANGED_MIX  (WM_USER+1747)//zhouhj 20211028 增加用于混合控制块更新各视图
#define WM_GIN_CH_APPID_CHANGED      (WM_USER +1448)

//相别编号
#define UI_CH_INDEX_NONE   -1
#define UI_CH_INDEX_A      0
#define UI_CH_INDEX_B      1
#define UI_CH_INDEX_C      2
#define UI_CH_INDEX_0      3
#define UI_CH_INDEX_Z      4
#define UI_CH_INDEX_AB     5
#define UI_CH_INDEX_BC     6
#define UI_CH_INDEX_CA     7


#define _IECCFG_SYSPARAS_PKG_SEND_TYPE_EndKeepSend_                             0//zhouhj 20210316增加用于单机软件系统参数设置
#define _IECCFG_SYSPARAS_PKG_SEND_TYPE_EndStopSend_                             1

#define _IECCFG_SYSPARAS_SEC_SYN_DisEnable_                                     0
#define _IECCFG_SYSPARAS_SEC_SYN_Enable_                                        1

#define _IECCFG_SYSPARAS_B_CODE_LOGIC_Negative_                                 0
#define _IECCFG_SYSPARAS_B_CODE_LOGIC_Positive_                                 1

#define _IECCFG_SYSPARAS_IEC1588_TYPE_PeerDelay_                                0    //对等延时
#define _IECCFG_SYSPARAS_IEC1588_TYPE_RequestResponse_                          1    //请求响应


#define _IECCFG_SYSPARAS_LC_PORT_TYPE_100M_                                     0    //100M
#define _IECCFG_SYSPARAS_LC_PORT_TYPE_1000M_                                    1    //1000M


#define _IECCFG_SYSPARAS_ST_PORT_TYPE_BCode_                                    0 
#define _IECCFG_SYSPARAS_ST_PORT_TYPE_FT3_                                      1


#define IECCFG_MAX_PT_CT_NUM                                   6
#define IECCFG_MAX_LC_FIBER_NUM                                4
#define IECCFG_MAX_ST_FIBER_NUM                                6

#define IEC_CFG_DEVICE_USE_TYPE_NORMAL                          0    // zhouhj 20220211 IecCfgDevice文件的使用方式,以及界面表格等的显示方式
#define IEC_CFG_DEVICE_USE_TYPE_AT02D                           1
#define IEC_CFG_DEVICE_USE_TYPE_ISmartTest                      2

#define IECCFG_VOLCH_AccLevel_Prot3P                                         0
#define IECCFG_VOLCH_AccLevel_Prot6P                                         1
#define IECCFG_VOLCH_AccLevel_Meas0_1                                        2
#define IECCFG_VOLCH_AccLevel_Meas0_2                                        3
#define IECCFG_VOLCH_AccLevel_Meas0_5                                        4
#define IECCFG_VOLCH_AccLevel_Meas1                                          5

#define IECCFG_CURRCH_AccLevel_Prot5P30                                      0
#define IECCFG_CURRCH_AccLevel_Prot5P                                        1
#define IECCFG_CURRCH_AccLevel_Prot10P                                       2
#define IECCFG_CURRCH_AccLevel_Meas0_1                                       3
#define IECCFG_CURRCH_AccLevel_Meas0_2S                                      4
#define IECCFG_CURRCH_AccLevel_Meas0_2                                       5
#define IECCFG_CURRCH_AccLevel_Meas0_5S                                      6
#define IECCFG_CURRCH_AccLevel_Meas0_5                                       7
#define IECCFG_CURRCH_AccLevel_Meas1                                         8

#define IECCFG_FORMAT_61850_92          0
#define IECCFG_FORMAT_60044_8           1
#define IECCFG_FORMAT_60044_8DC         2 //柔直FT3

//ADMU
#define ADMU_IECCFG_VOLCH_AccLevel_Meas0_5                                        0 //测量级0.5
#define ADMU_IECCFG_VOLCH_AccLevel_Meas1                                         1//测量级1
#define ADMU_IECCFG_VOLCH_AccLevel_PhaseProt3P                                     2//相保护级3P
#define ADMU_IECCFG_VOLCH_AccLevel_ZeroSeqProt3P                                   3//零序保护级3P

#define ADMU_IECCFG_CURRCH_AccLevel_Meas0_5S                                       0//测量级0.5S
#define ADMU_IECCFG_CURRCH_AccLevel_Meas1S                                         1//测量级1S
#define ADMU_IECCFG_CURRCH_AccLevel_Prot5P10                                      2//保护级5P10
#define ADMU_IECCFG_CURRCH_AccLevel_Prot5P30                                      3//保护级5P30


#define SMV_RATEID_STR_UABCZ   (_T("Uabcz"))
#define SMV_RATEID_STR_IABC    (_T("Iabc"))
#define SMV_RATEID_STR_UABCZ2  (_T("U2-abcz"))
#define SMV_RATEID_STR_IABC2   (_T("I2-abc"))
#define SMV_RATEID_STR_UABCZ3  (_T("U3-abcz"))
#define SMV_RATEID_STR_IABC3   (_T("I3-abc"))
#define SMV_RATEID_STR_UABCZ4  (_T("U4-abcz"))
#define SMV_RATEID_STR_IABC4   (_T("I4-abc"))
#define SMV_RATEID_STR_UABCZ5  (_T("U5-abcz"))
#define SMV_RATEID_STR_IABC5   (_T("I5-abc"))
#define SMV_RATEID_STR_UABCZ6  (_T("U6-abcz"))
#define SMV_RATEID_STR_IABC6   (_T("I6-abc"))

#define SMV_RATEID_STR_PUABCZ  (_T("Up-abcz"))
#define SMV_RATEID_STR_PIABC   (_T("Ip-abc"))
#define SMV_RATEID_STR_SUABCZ  (_T("Us-abcz"))
#define SMV_RATEID_STR_SIABC   (_T("Is-abc"))
#define SMV_RATEID_STR_TUABCZ  (_T("Ut-abcz"))
#define SMV_RATEID_STR_TIABC   (_T("It-abc"))

//zhouhj 2023.12.27 增加用于直流通道
#define SMV_RATEID_STR_U1_123   (_T("U1-123"))
#define SMV_RATEID_STR_I1_123    (_T("I1-123"))
#define SMV_RATEID_STR_U2_123   (_T("U2-123"))
#define SMV_RATEID_STR_I2_123    (_T("I2-123"))
#define SMV_RATEID_STR_U3_123   (_T("U3-123"))
#define SMV_RATEID_STR_I3_123    (_T("I3-123"))
#define SMV_RATEID_STR_U4_123   (_T("U4-123"))
#define SMV_RATEID_STR_I4_123    (_T("I4-123"))


#define SMV_RATEID_UINT_UABCZ   0
#define SMV_RATEID_UINT_IABC    1
#define SMV_RATEID_UINT_UABCZ2  2
#define SMV_RATEID_UINT_IABC2   3
#define SMV_RATEID_UINT_UABCZ3  4
#define SMV_RATEID_UINT_IABC3   5
#define SMV_RATEID_UINT_UABCZ4  6
#define SMV_RATEID_UINT_IABC4   7
#define SMV_RATEID_UINT_UABCZ5  8
#define SMV_RATEID_UINT_IABC5   9
#define SMV_RATEID_UINT_UABCZ6  10
#define SMV_RATEID_UINT_IABC6   11

#define SMV_RATE_MAX_NUM        6 //zhouhj 2023.12.27 采样值比例系数最大组数

#define IecCfgSmvOut_91_92MaxNum        8
#define IecCfgGoutData_MaxNum           16//表示单个插件时的光口最大数量
#define IecCfgGinData_MaxNum            16//add wangtao 20240509 并将所有使用固定值的地方改成全局变量
#define IecCfgAddMax                    1.2//根据光口数改变最大总控制块数量的系数
#define IecCfg6044COM_IN_MaxNum         12
#define IecCfg6044COM_OUT_MaxNum         12

long iecfg_GetBinIndex(const char *pszBin);
void iecfg_GetBinID(DWORD dwValue, CString &strBinID);
void iecfg_AppendBinID(long nIndex, CString &strBinID);
long iecfg_GetBinChangeIndex(DWORD dwOld, DWORD dwCurr);
CString iecfg_GetBinID(long nIndex);

//zhouhj 2023.10.27 将原来的固定值改为全局变量方式
extern long g_nIecCfgSmvOut_60044MaxNum;
extern long g_nIecCfgSmvIn_60044MaxNum;
extern long g_nIecCfgSmvOut_91_92MaxNum;
extern long g_nIecCfgGoutMaxNum;
extern long g_nIecCfgGinMaxNum;

extern const CString g_strSmvCurrentRateID[SMV_RATE_MAX_NUM];
extern const CString g_strSmvVolRateID[SMV_RATE_MAX_NUM];

//2023-4-17  lijunqing
inline BOOL iecfg_IsDatas(UINT nClassID)
{
	if (nClassID == CFGCLASSID_CIECCFGDATASGIN)
	{
		return TRUE;
	}
	else if (nClassID == CFGCLASSID_CIECCFGDATASSMV)
	{
		return TRUE;
	}
	else if (nClassID == CFGCLASSID_CIECCFGDATASGOUT)
	{
		return TRUE;
	}
	else if (nClassID == CFGCLASSID_CIECCFGDATASSMVINPUT)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

inline BOOL iecfg_IsData(UINT nClassID)
{
	if (nClassID == CFGCLASSID_CIECCFG2MINDATA
		|| nClassID ==CFGCLASSID_CIECCFG92INPUTDATA
		|| nClassID == CFGCLASSID_CIECCFG92INPUTDATA
		|| nClassID == CFGCLASSID_CIECCFGGOUTDATA
		|| nClassID == CFGCLASSID_CIECCFG91DATA
		|| nClassID == CFGCLASSID_CIECCFG92DATA
		|| nClassID == CFGCLASSID_CIECCFG6044DATA
		|| nClassID == CFGCLASSID_CIECCFG2MDATA
		|| nClassID == CFGCLASSID_CIECCFG6044COMMONDATA
		|| nClassID == CFGCLASSID_CIECCFGGINDATA)
	{
		return TRUE;
	}
	
	return FALSE;
}


