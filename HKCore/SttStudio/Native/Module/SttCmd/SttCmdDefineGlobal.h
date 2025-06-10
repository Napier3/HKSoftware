//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttCmdDefineGlobal.h

#pragma once

#include "../../../61850/Module/CfgDataMngr/IecCfgDataMngrGlobal.h"
//#include "../../Module/DataMngr/DataMngrGlobal.h"

//2021-6-13  lijunqing
//模块class id的命名，都用模块的功能概要简写，同时都是大写，MNGR是生成工具缺省的，必须要修改
//因此将“MngrCLASSID”改为“STTCMDCLASSID”。
//#define STTCMDCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
//#define STTCMDCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)
//2023-9-9  lijunqing  (CLASSID_BASECLASS + 0X00010000) >> (CLASSID_BASECLASS + 0X00310000)
#define STTCMDCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00310000)
#define STTCMDCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00310000)

#define STTCMDCLASSID_CSTTCMDBASE       (STTCMDCLASSID_EXLISTCLASS + 0X00000000)
#define STTCMDCLASSID_CSTTPARAS       (STTCMDCLASSID_EXLISTCLASS + 0X00000001)
#define STTCMDCLASSID_CSTTMACRO       (STTCMDCLASSID_EXLISTCLASS + 0X00000002)
#define STTCMDCLASSID_CSTTTESTCMD       (STTCMDCLASSID_EXLISTCLASS + 0X00000003)
#define STTCMDCLASSID_CSTTSYSTEMCMD       (STTCMDCLASSID_EXLISTCLASS + 0X00000004)
#define STTCMDCLASSID_CSTTATSCMD       (STTCMDCLASSID_EXLISTCLASS + 0X00000005)
#define STTCMDCLASSID_CSTTREMOTECMD       (STTCMDCLASSID_EXLISTCLASS + 0X00000006)
#define STTCMDCLASSID_CSTTDEBUGCMD       (STTCMDCLASSID_EXLISTCLASS + 0X00000007)
#define STTCMDCLASSID_CSTTASSISTCMD       (STTCMDCLASSID_EXLISTCLASS + 0X00000008)
#define STTCMDCLASSID_CSTTSYSSTATE       (STTCMDCLASSID_EXLISTCLASS + 0X00000009)
#define STTCMDCLASSID_CSHORTDATAS       (STTCMDCLASSID_EXLISTCLASS + 0X0000000A)
#define STTCMDCLASSID_CSTTRESULTS       (STTCMDCLASSID_EXLISTCLASS + 0X0000000B)
#define STTCMDCLASSID_REPORTS			(STTCMDCLASSID_EXLISTCLASS + 0X0000000C)
#define STTCMDCLASSID_REPORT			(STTCMDCLASSID_EXLISTCLASS + 0X0000000D)
#define STTCMDCLASSID_CSTTRPTMAPDATAS  (STTCMDCLASSID_EXLISTCLASS + 0X0000000E)
#define STTCMDCLASSID_CSTTMSGS       (STTCMDCLASSID_EXLISTCLASS + 0X0000000F)
#define STTCMDCLASSID_CSTTMSG       (STTCMDCLASSID_BASECLASS + 0X00000010)
#define STTCMDCLASSID_CSTTADJUSTCMD       (STTCMDCLASSID_EXLISTCLASS + 0X00000011)
#define STTCMDCLASSID_CSTTIOTDEVICE       (STTCMDCLASSID_BASECLASS + 0X00000012)
#define STTCMDCLASSID_CSTTIOTDEVICES       (STTCMDCLASSID_EXLISTCLASS + 0X00000013)
#define STTCMDCLASSID_CSTTIOTNODE       (STTCMDCLASSID_EXLISTCLASS + 0X00000014)
#define STTCMDCLASSID_CSTTIOTTOPO       (STTCMDCLASSID_EXLISTCLASS + 0X00000015)

#define STTCMDCLASSID_CSTTCHMAPS       (STTCMDCLASSID_EXLISTCLASS + 0X00000016)
#define STTCMDCLASSID_CSTTCHMAP        (STTCMDCLASSID_EXLISTCLASS + 0X00000017)
#define STTCMDCLASSID_CSTTHDCHS        (STTCMDCLASSID_EXLISTCLASS + 0X00000018)
#define STTCMDCLASSID_CSTTHDCH         (STTCMDCLASSID_EXLISTCLASS + 0X00000019)
#define STTCMDCLASSID_CSTTIOTCMD       (STTCMDCLASSID_EXLISTCLASS + 0X0000001A)

//shaolei  20210724  add
//lijunqing 2022-1-14   所有项目的classid 与STTGBXMLCLASSID_CSTTITEMBASE关联
#define STTGBXMLCLASSID_CSTTGUIDEBOOK			(STTCMDCLASSID_EXLISTCLASS + 0X0000001B)
#define STTGBXMLCLASSID_CSTTITEMBASE			(STTCMDCLASSID_EXLISTCLASS + 0X00001000)
#define STTGBXMLCLASSID_CSTTITEMS					(STTGBXMLCLASSID_CSTTITEMBASE + 0X0000001D)
#define STTGBXMLCLASSID_CSTTDEVICE				(STTGBXMLCLASSID_CSTTITEMBASE + 0X0000001E)
#define STTGBXMLCLASSID_CSTTJOBGUIDE			(STTGBXMLCLASSID_CSTTITEMBASE + 0X0000001F)
#define STTGBXMLCLASSID_CSTTRPTDATA				(STTCMDCLASSID_EXLISTCLASS + 0X00000020)
#define STTGBXMLCLASSID_CSTTREPORTMAP			(STTCMDCLASSID_EXLISTCLASS + 0X00000021)
#define STTGBXMLCLASSID_CSTTSYSPARAS			(STTCMDCLASSID_EXLISTCLASS + 0X00000022)
#define STTGBXMLCLASSID_CSTTDATAOBJ				(STTCMDCLASSID_EXLISTCLASS + 0X00000023)
#define STTGBXMLCLASSID_CSTTCOMMCMD			(STTGBXMLCLASSID_CSTTITEMBASE + 0X00000024)
#define STTGBXMLCLASSID_CSTTMACROTEST			(STTGBXMLCLASSID_CSTTITEMBASE + 0X00000025)
#define STTGBXMLCLASSID_CSTTSAFETY				(STTGBXMLCLASSID_CSTTITEMBASE + 0X00000026)
#define STTGBXMLCLASSID_CSTTSYSPARAEDIT		(STTGBXMLCLASSID_CSTTITEMBASE + 0X00000027)

#define STTCMDCLASSID_CSTTSEARCHRESULTS       (STTCMDCLASSID_EXLISTCLASS + 0X00000028)//zhouhj 20210925 增加搜索点结果
#define STTGBXMLCLASSID_CSTTCONTENTS				(STTCMDCLASSID_EXLISTCLASS + 0X00000029)  
#define STTGBXMLCLASSID_CSTTTESTMACROUIPARAS		(STTCMDCLASSID_BASECLASS + 0X0000002A)  
//2022-7-24  lijunqing 
#define STTGBXMLCLASSID_MACROCHARITEMLINEDEF		(STTCMDCLASSID_BASECLASS + 0X0000002B)
#define STTGBXMLCLASSID_CSTTMACROCHARITEMS              (STTGBXMLCLASSID_CSTTITEMBASE + 0x0000002C)

//2022-9-14  lijunqing
#define STTGBXMLCLASSID_CSTTCOMM_DATA			(STTCMDCLASSID_EXLISTCLASS + 0x0000002D)

//2022-12-19  shaolei
#define STTGBXMLCLASSID_CSTTMACROPARA			(STTCMDCLASSID_EXLISTCLASS + 0x0000002E)
#define STTGBXMLCLASSID_CSTTCHARACTERISTIC              (STTCMDCLASSID_EXLISTCLASS + 0x0000002F)

//2023-3-1
#define STTGBXMLCLASSID_CSTTITEMRSLTEXPR            (STTCMDCLASSID_EXLISTCLASS + 0x00000030)
//2023-3-22
#define STTGBXMLCLASSID_CSTTTESTMACROCHARPARAS		(STTCMDCLASSID_BASECLASS + 0X00000031)  

inline bool stt_gb_is_a_itembase(UINT nClassID)
{
	return (STTGBXMLCLASSID_CSTTITEMBASE == (STTGBXMLCLASSID_CSTTITEMBASE & nClassID));
}

inline bool stt_gb_is_a_itembase(CExBaseObject *p)
{
	return stt_gb_is_a_itembase(p->GetClassID());
}

#ifndef CLIENT_TEST_ENGINE_IN_LOCAL
class CSttCmdDefineXmlRWKeys : public CCfgDataMngrXmlRWKeys
#else
class CSttCmdDefineXmlRWKeys : public CDataMngrXmlRWKeys
#endif
{
protected:
	CSttCmdDefineXmlRWKeys();
	virtual ~CSttCmdDefineXmlRWKeys();
	static long g_nMngrRef;

	BOOL m_bOnlyGetItem;
	long m_nGuideBookUseItemKey;  //2022-3-24  lijunqing

public:
	static CSttCmdDefineXmlRWKeys* g_pXmlKeys;
	static CSttCmdDefineXmlRWKeys* Create();
	static void Release();
	
	static BOOL IsOnlyGetItem()	{	return g_pXmlKeys->m_bOnlyGetItem;	}
	static void SetOnlyGetItem(BOOL b)	{	g_pXmlKeys->m_bOnlyGetItem = b;	}

	//2022-3-24  lijunqing
	static void stt_Inc_GuideBookUseItemKey(CSttCmdDefineXmlRWKeys *pXmlKeys);
	static void stt_Dec_GuideBookUseItemKey(CSttCmdDefineXmlRWKeys *pXmlKeys);
	static long stt_Is_GuideBookUseItemKey(CSttCmdDefineXmlRWKeys *pXmlKeys);

public:
	BSTR m_strCSttIotTopoKey; //topo
	BSTR m_strCSttIotNodeKey; //node
	BSTR m_strCSttIotDevicesKey; //devices
	BSTR m_strCSttIotDeviceKey; //device
	BSTR m_strCSttMsgKey; //msg
	BSTR m_strCSttMsgsKey; //msgs
	BSTR m_strCSttRptMapDatasKey; //rpt-map-datas
	BSTR m_strCSttReportsKey;//reports
	BSTR m_strCSttReportKey;//report
	BSTR m_strCSttSysStateKey; //sys-state
	BSTR m_strCSttAssistCmdKey; //assist-cmd
	BSTR m_strCSttDebugCmdKey; //dbg-cmd
	BSTR m_strCSttRemoteCmdKey; //remote-cmd
	BSTR m_strCSttAtsCmdKey; //ats-cmd
	BSTR m_strCSttSystemCmdKey; //sys-cmd
	BSTR m_strCSttAdjustCmdKey; //adj-cmd
	BSTR m_strCSttTestCmdKey; //test-cmd
	BSTR m_strCSttIotCmdKey; //iot-cmd
	BSTR m_strCSttMacroKey; //macro
	BSTR m_strCSttParasKey; //paras
	BSTR m_strCSttResultsKey; //results
	BSTR m_strCSttSearchResultsKey; //search-results  //zhouhj 20210925 增加搜索点结果
	BSTR m_strCSttCmdBaseKey; //SttCmdBase
	BSTR m_strCSttCmdDataKey; //SttCmdData
	BSTR m_strTestorKey; //testor
	BSTR m_strMater_HostKey; //mater-host
	BSTR m_strRetTypeKey; //ret-type
	BSTR m_strRetCmdKey; //ret-type

	BSTR m_strVersionKey; //version
	BSTR m_strTypeKey; //type
	BSTR m_strRemarkKey; //remark

	BSTR m_strBeginTimeKey;
	BSTR m_strEndTimeKey;

	BSTR m_strMidKey; //mid
	BSTR m_strTimeKey; //time
	BSTR m_strLevelKey; //level
	BSTR m_strContentKey; //content
	BSTR m_strDevCodeKey; //devCode
	BSTR m_strDevTypeKey; //devType
	BSTR m_strSNKey; //SN
	BSTR m_strCatKey; //cat
	BSTR m_strParentKey; //parent
	BSTR m_strStateKey; //state

	BSTR m_strCSttHdChKey; //hd-ch
	BSTR m_strCSttHdChsKey; //hd-chs
	BSTR m_strCSttChMapKey; //ch-map
	BSTR m_strCSttChMapsKey; //ch-maps
	BSTR m_strAliasKey; //alias
	BSTR m_strRsIndexKey; //rs-index zhouhj 增加用于标识软件资源编号

	//shaolei  20210724
	BSTR m_strCSttSysParaEditKey; //sysparaedit
	BSTR m_strCSttSafetyKey; //safety
	BSTR m_strCSttMacroTestKey; //macrotest
	BSTR m_strCSttCommCmdKey; //commcmd
	BSTR m_strCSttDataObjKey; //data
	BSTR m_strCSttSysParasKey; //sys-paras
	BSTR m_strCSttReportMapKey; //rpt-map
	BSTR m_strCSttRptDataKey; //data
	BSTR m_strCSttJobGuideKey; //job-guide
	BSTR m_strCSttDeviceKey; //device
	BSTR m_strCSttItemsKey; //items
	BSTR m_strCSttItemBaseKey; //item-base
	BSTR m_strCSttGuideBookKey; //guidebook
	BSTR m_strTestMacroFileIDKey; //macro-file
	BSTR m_strTestTypeFileKey; //test-type-file
	BSTR m_strDeviceIdKey; //device-id
	BSTR m_strDevByKey; //dev-by
	//BSTR m_strVersionKey; //version
	BSTR m_strCommCmdConfigFileKey; //comm-cmd-config
	BSTR m_strPpTemplateFileKey; //PpTemplateFile
	BSTR m_strScriptMngrFileKey; //script-library
	BSTR m_strPpEngineProgIDKey; //PpEngineProgID
	BSTR m_strDvmFileKey; //dvm-file
	BSTR m_strStandNameFileKey; //stand-file
	BSTR m_strDeviceModelFileKey; //device-model-file
	BSTR m_strTestControlModeKey; //test-control-mode
	BSTR m_strExpandConfigFileKey; //expand-config-file
	BSTR m_strIecfgFileKey; //iecfg-file
	BSTR m_strReadOnlyKey; //read-only
	BSTR m_strSaveRptToDBKey; //save-rpt-to-db
	BSTR m_strAuthoritySNKey; //authority-sn
	BSTR m_strAuthorityCopKey; //authority-cop
	BSTR m_strScriptTypeKey; //script-type
	BSTR m_strTkidKey; //tkid
	BSTR m_strShowKey; //show
	BSTR m_strEnableKey; //enable
	BSTR m_strExectypeKey; //exectype
	BSTR m_strBatchItemKey; //batch-item
	BSTR m_strMdvTestEachKey; //mdv-test-each
	//BSTR m_strStateKey; //state
	BSTR m_strSelectKey; //select
	//BSTR m_strTypeKey; //type
	BSTR m_strCharacteristicIDKey; //characteristic-id
	BSTR m_strStxmlFileKey; //stxml
	BSTR m_strWzdMapFileKey; //wzd-map
	BSTR m_strActLogicKey; //act-logic
	BSTR m_strFactoryKey; //factory
	BSTR m_strDeviceTypeKey; //type
	BSTR m_strIsTimeSetsUnit_ms_Key; //is-time-sets-unit-s
	BSTR m_strDsvTextWithValueKey; //dsv-text-with-value
	BSTR m_strDsvTextWithUtcTimeKey; //dsv-text-with-utctime
	BSTR m_strSrcDeviceModelFileKey; //src-device-model-file
	BSTR m_strPrecisionKey; //precision
	BSTR m_strDataTypeKey; //data-type
	BSTR m_strRWAttrKey; //rw-attr
	BSTR m_strUnitKey; //unit
	BSTR m_strValueKey; //value
	BSTR m_strDefaultValueKey; //default-value
	BSTR m_strMinValKey; //min
	BSTR m_strMaxValKey; //max
	BSTR m_strStepKey; //step
	BSTR m_strDataIndexKey; //data-index
	BSTR m_strCmdRwKey; //rw-optr
	BSTR m_strSortSoeByTKey; //sort-soe
	BSTR m_strDsvRunAfterResultScriptKey; //dsv-run-after-rst
	BSTR m_strCmdExecModeForMgrptKey; //mgbrpt-cmd-mode
	BSTR m_strFillRptDatasetKey;  //fill-dataset
	BSTR m_strRepeatTimesKey; //repeat-timers
	BSTR m_strCalModeKey; //cal-mode
	BSTR m_strReportFillUseNoRepeatKey; //rpt-fill-no-repeat
	BSTR m_strSoundFileKey; //sound-file
	BSTR m_strManyDeviceTestModeKey; //many-rpt-test-mode
	BSTR m_strMacroIDKey; //macroid
	BSTR m_strContentsKey; //contents
	BSTR m_strTestMacroUiParasKey;  //test-macro-ui-paras
	BSTR m_strTestMacroCharParasKey;  //test-macro-char-paras
	BSTR m_strCSttMacroCharItemsKey;  //macro-char-items
	BSTR m_strTestModeKey;   //testmode
	BSTR m_strParaKey;   //para
	BSTR m_strCSttCharacteristicKey; //characteristic

	BSTR m_strAutoCloseKey; //auto-close
	BSTR m_strAxisKey; //axis
	BSTR m_strTestLineModeKey; //test-line-mode
	BSTR m_strXMinKey; //xmin
	BSTR m_strXMaxKey; //xmax
	BSTR m_strYMinKey; //ymin
	BSTR m_strYMaxKey; //ymax

	//2022-7-24  lijunqing
	BSTR m_strCMacroCharItemLineDefKey;
	BSTR  m_strAxisModeKey;   //Axis mode:x-y; r-angle
	BSTR  m_strParaIdXbKey;
	BSTR  m_strParaIdYbKey;
	BSTR  m_strParaIdXeKey;
	BSTR  m_strParaIdYeKey;
	BSTR  m_strParaIdXsetKey;
	BSTR  m_strParaIdYsetKey;
	BSTR  m_strParaIdXactKey;
	BSTR  m_strParaIdYactKey;
	BSTR  m_strParaIdFlagActKey;

	BSTR  m_strParaIdSearchXbKey;
	BSTR  m_strParaIdSearchYbKey;
	BSTR  m_strParaIdSearchActbKey;
	BSTR  m_strParaIdSearchXeKey;
	BSTR  m_strParaIdSearchYeKey;
	BSTR  m_strParaIdSearchActeKey;
	BSTR  m_strParaIdSearchXcKey;
	BSTR  m_strParaIdSearchYcKey;


	//cmd-data
	BSTR m_strCSttCommCmdDataKey;
	BSTR m_strDataSetPathKey;
	BSTR m_strDelayBeforeCmdKey;
	BSTR m_strDelayAfterCmdKey;
	//BSTR m_strCalModeKey;
	BSTR m_strDelayBeforeTryKey;
	BSTR m_strMaxRetryTimesKey;
	BSTR m_strRetryTimesKey;
	BSTR m_strTimeLongKey;
	BSTR m_strTimeGapKey;
	BSTR m_strTimeIgnoreKey;
	BSTR m_strUseCurrSetDataKey;
	BSTR m_strUseDeviceExKey;
	BSTR m_strBeginModeKey;
	BSTR m_strUseConnectKey;
	BSTR m_strZoneIndexKey;

	BSTR m_strCSttItemRsltExprKey;

#ifdef CLIENT_TEST_ENGINE_IN_LOCAL
	BSTR m_strCoefKey; //coef
#endif

	//shaolei 2023-6-20
	BSTR m_strRptTitleKey;   //rpt-title
	BSTR m_strTitleLevelKey; //title-level

public:
	static BSTR CSttCommCmdDataKey()  {   return g_pXmlKeys->m_strCSttCommCmdDataKey;  }

	static BSTR CSttIotTopoKey()  {   return g_pXmlKeys->m_strCSttIotTopoKey;  }
	static BSTR CSttIotNodeKey()  {   return g_pXmlKeys->m_strCSttIotNodeKey;  }
	static BSTR CSttIotDevicesKey()  {   return g_pXmlKeys->m_strCSttIotDevicesKey;  }
	static BSTR CSttIotDeviceKey()  {   return g_pXmlKeys->m_strCSttIotDeviceKey;  }
	static BSTR CSttMsgKey()  {   return g_pXmlKeys->m_strCSttMsgKey;  }
	static BSTR CSttMsgsKey()  {   return g_pXmlKeys->m_strCSttMsgsKey;  }
	static BSTR CSttRptMapDatasKey()  {   return g_pXmlKeys->m_strCSttRptMapDatasKey;  }
	static BSTR CSttSysStateKey()  {   return g_pXmlKeys->m_strCSttSysStateKey;  }
	static BSTR CSttAssistCmdKey()  {   return g_pXmlKeys->m_strCSttAssistCmdKey;  }
	static BSTR CSttDebugCmdKey()  {   return g_pXmlKeys->m_strCSttDebugCmdKey;  }
	static BSTR CSttRemoteCmdKey()  {   return g_pXmlKeys->m_strCSttRemoteCmdKey;  }
	static BSTR CSttAtsCmdKey()  {   return g_pXmlKeys->m_strCSttAtsCmdKey;  }
	static BSTR CSttSystemCmdKey()  {   return g_pXmlKeys->m_strCSttSystemCmdKey;  }
	static BSTR CSttAdjustCmdKey()  {   return g_pXmlKeys->m_strCSttAdjustCmdKey;  }
	static BSTR CSttTestCmdKey()  {   return g_pXmlKeys->m_strCSttTestCmdKey;  }
	static BSTR CSttIotCmdKey()  {   return g_pXmlKeys->m_strCSttIotCmdKey;  }
	static BSTR CSttMacroKey()  {   return g_pXmlKeys->m_strCSttMacroKey;  }
	static BSTR CSttParasKey()  {   return g_pXmlKeys->m_strCSttParasKey;  }
	static BSTR CSttResultsKey()  {   return g_pXmlKeys->m_strCSttResultsKey;  }
	static BSTR CSttSearchResultsKey()  {   return g_pXmlKeys->m_strCSttSearchResultsKey;  }
	static BSTR CSttCmdBaseKey()  {   return g_pXmlKeys->m_strCSttCmdBaseKey;  }
	static BSTR CSttCmdDataKey()  {   return g_pXmlKeys->m_strCSttCmdDataKey;  }
	static BSTR TestorKey()  {   return g_pXmlKeys->m_strTestorKey;  }
	static BSTR Mater_HostKey()  {   return g_pXmlKeys->m_strMater_HostKey;  }

	static BSTR VersionKey()  {   return g_pXmlKeys->m_strVersionKey;  }
	static BSTR TypeKey()  {   return g_pXmlKeys->m_strTypeKey;  }
	static BSTR RemarkKey()  {   return g_pXmlKeys->m_strRemarkKey;  }
	static BSTR MidKey()  {   return g_pXmlKeys->m_strMidKey;  }
	static BSTR TimeKey()  {   return g_pXmlKeys->m_strTimeKey;  }
	static BSTR LevelKey()  {   return g_pXmlKeys->m_strLevelKey;  }
	static BSTR ContentKey()  {   return g_pXmlKeys->m_strContentKey;  }
	static BSTR DevCodeKey()  {   return g_pXmlKeys->m_strDevCodeKey;  }
	static BSTR DevTypeKey()  {   return g_pXmlKeys->m_strDevTypeKey;  }
	static BSTR SNKey()  {   return g_pXmlKeys->m_strSNKey;  }
	static BSTR CatKey()  {   return g_pXmlKeys->m_strCatKey;  }
	static BSTR ParentKey()  {   return g_pXmlKeys->m_strParentKey;  }
	static BSTR StateKey()  {   return g_pXmlKeys->m_strStateKey;  }

	static BSTR CSttHdChKey()  {   return g_pXmlKeys->m_strCSttHdChKey;  }
	static BSTR CSttHdChsKey()  {   return g_pXmlKeys->m_strCSttHdChsKey;  }
	static BSTR CSttChMapKey()  {   return g_pXmlKeys->m_strCSttChMapKey;  }
	static BSTR CSttChMapsKey()  {   return g_pXmlKeys->m_strCSttChMapsKey;  }
	static BSTR AliasKey()  {   return g_pXmlKeys->m_strAliasKey;  }
	static BSTR RsIndexKey()  {   return g_pXmlKeys->m_strRsIndexKey;  }

	//shaolei 20210724 
	static BSTR CSttSysParaEditKey()  {   return g_pXmlKeys->m_strCSttSysParaEditKey;  }
	static BSTR CSttSafetyKey()  {   return g_pXmlKeys->m_strCSttSafetyKey;  }
	static BSTR CSttMacroTestKey()  {   return g_pXmlKeys->m_strCSttMacroTestKey;  }
	static BSTR CSttCommCmdKey()  {   return g_pXmlKeys->m_strCSttCommCmdKey;  }
	static BSTR CSttDataObjKey()  {   return g_pXmlKeys->m_strCSttDataObjKey;  }
	static BSTR CSttSysParasKey()  {   return g_pXmlKeys->m_strCSttSysParasKey;  }
	static BSTR CSttReportMapKey()  {   return g_pXmlKeys->m_strCSttReportMapKey;  }
	static BSTR CSttRptDataKey()  {   return g_pXmlKeys->m_strCSttRptDataKey;  }
	static BSTR CSttJobGuideKey()  {   return g_pXmlKeys->m_strCSttJobGuideKey;  }
	static BSTR CSttDeviceKey()  {   return g_pXmlKeys->m_strCSttDeviceKey;  }
	static BSTR CSttItemsKey()  {   return g_pXmlKeys->m_strCSttItemsKey;  }
	static BSTR CSttItemBaseKey()  {   return g_pXmlKeys->m_strCSttItemBaseKey;  }
	static BSTR CSttGuideBookKey()  {   return g_pXmlKeys->m_strCSttGuideBookKey;  }
	static BSTR TestMacroFileIDKey()  {   return g_pXmlKeys->m_strTestMacroFileIDKey;  }
	static BSTR TestTypeFileKey()  {   return g_pXmlKeys->m_strTestTypeFileKey;  }
	static BSTR DeviceIdKey()  {   return g_pXmlKeys->m_strDeviceIdKey;  }
	static BSTR DevByKey()  {   return g_pXmlKeys->m_strDevByKey;  }
	//static BSTR VersionKey()  {   return g_pXmlKeys->m_strVersionKey;  }
	static BSTR CommCmdConfigFileKey()  {   return g_pXmlKeys->m_strCommCmdConfigFileKey;  }
	static BSTR PpTemplateFileKey()  {   return g_pXmlKeys->m_strPpTemplateFileKey;  }
	static BSTR ScriptMngrFileKey()  {   return g_pXmlKeys->m_strScriptMngrFileKey;  }
	static BSTR PpEngineProgIDKey()  {   return g_pXmlKeys->m_strPpEngineProgIDKey;  }
	static BSTR DvmFileKey()  {   return g_pXmlKeys->m_strDvmFileKey;  }
	static BSTR StandNameFileKey()  {   return g_pXmlKeys->m_strStandNameFileKey;  }
	static BSTR DeviceModelFileKey()  {   return g_pXmlKeys->m_strDeviceModelFileKey;  }
	static BSTR TestControlModeKey()  {   return g_pXmlKeys->m_strTestControlModeKey;  }
	static BSTR ExpandConfigFileKey()  {   return g_pXmlKeys->m_strExpandConfigFileKey;  }
	static BSTR IecfgFileKey()  {   return g_pXmlKeys->m_strIecfgFileKey;  }
	static BSTR ReadOnlyKey()  {   return g_pXmlKeys->m_strReadOnlyKey;  }
	static BSTR SaveRptToDBKey()  {   return g_pXmlKeys->m_strSaveRptToDBKey;  }
	static BSTR AuthoritySNKey()  {   return g_pXmlKeys->m_strAuthoritySNKey;  }
	static BSTR AuthorityCopKey()  {   return g_pXmlKeys->m_strAuthorityCopKey;  }
	static BSTR ScriptTypeKey()  {   return g_pXmlKeys->m_strScriptTypeKey;  }
	static BSTR TkidKey()  {   return g_pXmlKeys->m_strTkidKey;  }
	static BSTR ShowKey()  {   return g_pXmlKeys->m_strShowKey;  }
	static BSTR EnableKey()  {   return g_pXmlKeys->m_strEnableKey;  }
	static BSTR ExectypeKey()  {   return g_pXmlKeys->m_strExectypeKey;  }
	static BSTR BatchItemKey()  {   return g_pXmlKeys->m_strBatchItemKey;  }
	static BSTR MdvTestEachKey()  {   return g_pXmlKeys->m_strMdvTestEachKey;  }
	//static BSTR StateKey()  {   return g_pXmlKeys->m_strStateKey;  }
	static BSTR SelectKey()  {   return g_pXmlKeys->m_strSelectKey;  }
	//static BSTR TypeKey()  {   return g_pXmlKeys->m_strTypeKey;  }
	static BSTR CharacteristicIDKey()  {   return g_pXmlKeys->m_strCharacteristicIDKey;  }
	static BSTR StxmlFileKey()  {   return g_pXmlKeys->m_strStxmlFileKey;  }
	static BSTR WzdMapFileKey()  {   return g_pXmlKeys->m_strWzdMapFileKey;  }
	static BSTR ActLogicKey()  {   return g_pXmlKeys->m_strActLogicKey;  }
	static BSTR FactoryKey()  {   return g_pXmlKeys->m_strFactoryKey;  }
	static BSTR DeviceTypeKey()  {   return g_pXmlKeys->m_strDeviceTypeKey;  }
	static BSTR IsTimeSetsUnit_ms_Key()  {   return g_pXmlKeys->m_strIsTimeSetsUnit_ms_Key;  }
	static BSTR DsvTextWithValueKey()  {   return g_pXmlKeys->m_strDsvTextWithValueKey;  }
	static BSTR DsvTextWithUtcTimeKey()  {   return g_pXmlKeys->m_strDsvTextWithUtcTimeKey;  }
	static BSTR SrcDeviceModelFileKey()  {   return g_pXmlKeys->m_strSrcDeviceModelFileKey;  }
	static BSTR PrecisionKey()  {   return g_pXmlKeys->m_strPrecisionKey;  }
	static BSTR DataTypeKey()  {   return g_pXmlKeys->m_strDataTypeKey;  }
	static BSTR RWAttrKey()  {   return g_pXmlKeys->m_strRWAttrKey;  }
	static BSTR UnitKey()  {   return g_pXmlKeys->m_strUnitKey;  }
	static BSTR ValueKey()  {   return g_pXmlKeys->m_strValueKey;  }
	static BSTR DefaultValueKey()  {   return g_pXmlKeys->m_strDefaultValueKey;  }
	static BSTR MinValKey()  {   return g_pXmlKeys->m_strMinValKey;  }
	static BSTR MaxValKey()  {   return g_pXmlKeys->m_strMaxValKey;  }
	static BSTR StepKey()  {   return g_pXmlKeys->m_strStepKey;  }
	static BSTR DataIndexKey()  {   return g_pXmlKeys->m_strDataIndexKey;  }
	static BSTR CmdRwKey()  {   return g_pXmlKeys->m_strCmdRwKey;  }
	static BSTR SortSoeByTKey()  {   return g_pXmlKeys->m_strSortSoeByTKey;  }
	static BSTR DsvRunAfterResultScriptKey()  {   return g_pXmlKeys->m_strDsvRunAfterResultScriptKey;  }
	static BSTR CmdExecModeForMgrptKey()  {   return g_pXmlKeys->m_strCmdExecModeForMgrptKey;  }
	static BSTR FillRptDatasetKey()  {   return g_pXmlKeys->m_strFillRptDatasetKey;  }
	static BSTR RepeatTimesKey()  {   return g_pXmlKeys->m_strRepeatTimesKey;  }
	static BSTR CalModeKey()  {   return g_pXmlKeys->m_strCalModeKey;  }
	static BSTR ReportFillUseNoRepeatKey()  {   return g_pXmlKeys->m_strReportFillUseNoRepeatKey;  }
	static BSTR SoundFileKey()  {   return g_pXmlKeys->m_strSoundFileKey;  }
	static BSTR ManyDeviceTestModeKey()  {   return g_pXmlKeys->m_strManyDeviceTestModeKey;  }
	static BSTR CSttContentsKey()  {   return g_pXmlKeys->m_strContentsKey;  }
	static BSTR CSttMacroCharItemsKey()  {   return g_pXmlKeys->m_strCSttMacroCharItemsKey;  }
	static BSTR CSttCharacteristicKey()  {   return g_pXmlKeys->m_strCSttCharacteristicKey;  }
	static BSTR CSttItemRsltExprKey()	{	return g_pXmlKeys->m_strCSttItemRsltExprKey;	}
};


class CSttCmdDefineConstGlobal
{
private:
	CSttCmdDefineConstGlobal();
	virtual ~CSttCmdDefineConstGlobal();

public:
	static CSttCmdDefineConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CSttCmdDefineConstGlobal *g_pGlobal;



private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};

class CTestDataTypeMngrConstGlobal
{
private:
	CTestDataTypeMngrConstGlobal();
	virtual ~CTestDataTypeMngrConstGlobal();

public:
	static CTestDataTypeMngrConstGlobal* Create();
	static void Release();

	static CDataTypes* GetTestDataTypes();
	static CDataType* FindTestDataType(const  CString &strDataTypeID);

	static CTestDataTypeMngrConstGlobal *g_pDataTypeGlobal;

private:
	static long g_nDataTypeGlobal;
	void InitGlobal();
	CDataTypes m_oTestDataTypes;

private:
	//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

	//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

	void Init_FaultTrigModeDataType();  //_T("FaultTrigMode");故障触发方式
	void Init_K0ModeModeDataType();  //_T("Init_K0ModeMode");零序补偿系数计算方式
	void Init_PTPositionDataType();  //_T("PTPosition");PT安装位置
	void Init_CTPosDataType();  //_T("CTPos");CT极性正方向
	void Init_CBSimulationDataType(); //_T("CBSimulation");是否模拟断路器延时
	void Init_IPlusDCDataType();  //_T("IPlusDC");是否叠加非周期分量
	void Init_FaultAngModeDataType();  //_T("FaultAngMode");合闸角方式
	void Init_UxModeDataType();  //_T("UxMode");Ux输出方式
	void Init_CalcuMode();//计算方式
	void Init_TestProcess();//试验过程
	void Init_RecloseMode();//重合方式
	void Init_USetMode();//0相电压 1线电压
	void Init_IPoint();//0指向变压器 1指向母线 (ipoint) 
	void Init_InterMethod();//插值法 0拉格朗日插值法 1线性插值法
	void Init_UzOutputDataType(); //mym add 2021-8-3
	void Init_UzCKDataType(); //mym add 2021-8-3
	void Init_K0CalModeDataType();//mym add 2021-8-3
	void Init_RXSelect();//阻抗参考方式 mym add 2021-8-3
	void Init_InputChannel();//开入量触发通道
	void Init_FaultType();//故障相选择
	void Init_FaultUType();//zyq 20230529 故障电压类型
	void Init_DifferMarkType();	//yyj add 2021-08-25 差动定值整定方式
	void Init_BasicCurrSelect();//yyj add 2021-08-25 差动基准电流选择
	void Init_ZDPointNum();		//yyj add 2021-08-25 差动比率制动特性拐点数
	void Init_DiffHarmIndex();
	void Init_FaultDirection();//故障方向 20230530 zyq
	void Init_FaultDirection2();//转换故障方向 20230530 zyq
	void Init_FaultPermanent();//转换故障方向 20230530 zyq
	void Init_IFaultTrans();  //_T("_FaultTrans");是否转换性故障
	void Init_FaultVolDef();

	void Init_Uariable();//gyp 20230602 电压变化量
	void Init_Iariable();//gyp 20230602 电流输出相
	void Init_nFaultType();//故障类型选择
	void Init_SearchMode();//zyq 20230607 搜索方式
	void Init_TranSort();//变压器接线形式
	void Init_CTPoint();//CT极性
	void Init_IrEquation();//制动方程
	void Init_SettingMode();//定值整定方式
	void Init_HarmIndex();//谐波次数
	void Init_FaultPhase();//故障相
	void Init_Conclusion();//结论
	void Init_FaultChannel();//故障通道

public:
	//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

	//定义全局常量，例如  static CString g_pstrVariableType_CString;

};

//空节点
#define  STTITEMS_NODETYPE_NONE       (_T("none"))
//一个基于子模板或者是智能生成的一个分类的节点
#define  STTITEMS_NODETYPE_ROOTNODE   (_T("rootnode"))
//模板智能生成和编辑部分，可以在此项目分类下面插入智能生成的模板模块
#define  STTITEMS_NODETYPE_ITEMS   (_T("items"))

//数据集相关定义
#define DSID_ALL_DVM     0XFF

static BOOL g_bStt_InitCommCmdToAllDevice = TRUE;
