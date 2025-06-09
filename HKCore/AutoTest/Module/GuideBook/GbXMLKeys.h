#pragma once

#include "../../../Module/BaseClass/ExBaseObject.h"
#include "../../../Module/DataMngr/DataMngrGlobal.h"
#include "../Characteristic/CharacteristicGlobal.h"
#include "../../../Module/DataMngr/Values.h"
#include "../../../Module/DataMngr/ShortDatas.h"
#include "../../../Module/DataMngr/DataTypes.h" //yyj 20200523
#include "../AutoTestGlobalDefine.h"
/*
	在适当的地方(比如ExitInstance)调用CGbXMLKeys::Release()
*/

#ifdef ScriptText_NoGb
class CGbXMLKeys : public CDataMngrXmlRWKeys
#else
class CGbXMLKeys : /*public CDataMngrXmlRWKeys,*/ public CCharacteristicXmlRWKeys
#endif

{
protected:
	CGbXMLKeys();
	virtual ~CGbXMLKeys();

	static long g_nGbXmlKeysRef;

public:
	static CGbXMLKeys* g_pGbXMLKeys;
	static CGbXMLKeys* CreatetGbXMLkeys();
	static void Release();

public:
	BSTR m_strTestDefineKey;
	BSTR m_strCMacroCharItemLineDefKey;
	BSTR m_strCMacroCharItemsKey;
	BSTR m_strCAinExpandMngrKey; //ain-expand
	BSTR m_strCAinExpandKey; //ain-expand
	BSTR m_strAbsKey; //abs
	BSTR m_strRealKey; //real
	BSTR m_strRsltKey; //rslt
	BSTR m_strShowWordRptKey;

	BSTR m_strCommCmdConfigKey;
	BSTR m_strMacroFileKey;
	BSTR m_strTestTypeFileKey;

	//name和id Key已在基类中定义
	BSTR m_strGuideBookKey;
	BSTR m_strDeviceIDKey;
	BSTR m_strDevByKey;
	BSTR m_strVersionKey;
	BSTR m_strCommCmdConfigFileKey;
	BSTR m_strPpTemplateFileKey;
	BSTR m_strScriptMngrFileKey;
	BSTR m_strPpEngineProgIDKey;
	BSTR m_strDvmFileKey;
	BSTR m_strStandNameFileKey;
	BSTR m_strDeviceModelFileKey;
	BSTR m_strTestControlModeKey;
	BSTR m_strExpandConfigFileKey;
	BSTR m_strIecfgFileKey;
	BSTR m_strReadOnlyKey;
	BSTR m_strSaveRptToDBKey;
	BSTR m_strAuthoritySNKey;
	BSTR m_strAuthorityCopKey;
	BSTR m_strScriptTypeKey;

	BSTR m_strJobGuideKey;
	BSTR m_strItemsKey;
	BSTR m_strMdvTestEachKey;

	//items Attributes
	BSTR m_strTypeKey;
	BSTR m_strCmdRwKey;
	BSTR m_strRepeatTimes;
	BSTR m_strReportFillUseNoRepeatKey;
	BSTR m_strTkIDKey;
	BSTR m_strIndexKey;
	BSTR m_strShowKey;
	BSTR m_strEnableKey;
	BSTR m_strStateKey; //2020-12-09  lijunqing
	BSTR m_strCharacteristicIDKey;
	BSTR m_strStxmlFileKey;
	BSTR m_strWzdMapFileKey;
	BSTR m_strSortSoeByTKey;
	BSTR m_strDsvRunAfterResultScriptKey;
	BSTR m_strCmdExecModeForMgbrptKey;
	BSTR m_strFillRptDatasetKey;
	BSTR m_strActLogicKey;

	//shaolei 2023-6-20
	BSTR m_strRptTitleKey;   //rpt-title
	BSTR m_strTitleLevelKey; //title-level

	//Result Expression Script
	BSTR m_strRsltExprKey;
	BSTR m_strRsltExprScriptKey;
	BSTR m_strRsltExprScriptMngrKey;

	BSTR m_strStandIDKey; //输出的标准值
	BSTR m_strStandCalExprKey; //输出的标准值
	BSTR m_strDvmDataIDKey;    //数据ID
	BSTR m_strDvmDataCalExprKey;   //数据计算公式
	BSTR m_strDvmDataAbsErrIDKey;
	BSTR m_strDvmDataRelErrIDKey;
	BSTR m_strVarAbsErrKey;   //绝对误差限
	BSTR m_strVarRelErrKey;   //相对误差限
	BSTR m_strRsltVarAbsErrKey;  
	BSTR m_strRsltVarRelErrKey;  
	BSTR m_strAbsErrCalExprKey;
	BSTR m_strRelErrCalExprKey;


	//safety Attributes	 有些和items Attributes 重复
	BSTR m_strSafetyKey;
	BSTR m_strExecTypeKey;
	BSTR m_strBatchItemKey;
	BSTR m_strSoundFileKey;
	BSTR m_strManyDeviceTestModeKey;

	BSTR m_strStandardKey;
	BSTR m_strMsgKey;
	BSTR m_strDatasKey;
	BSTR m_strTableKey;
	BSTR m_strScriptKey;
	BSTR m_strScriptResultKey;
	BSTR m_strScriptInitKey;
	BSTR m_strScriptNameKey;
	BSTR m_strScriptMngrKey;
	BSTR m_strScriptIsRefKey;
	BSTR m_strDllCallKey;
	BSTR m_strFuncNameKey;
	BSTR m_strParaTypeKey;
	BSTR m_strResultFileKey;

	//reports
	BSTR m_strReportsKey;
	BSTR m_strReportKey;

	BSTR m_strBeginTimeKey;
	BSTR m_strEndTimeKey;
	BSTR m_strReportValueElementKey;
	BSTR m_strReportValAttrKey;
	BSTR m_strBkmkDataAttrIDKey;
	BSTR m_strBkmkProcessKey;
	BSTR m_strBkmkFillModeKey;
	BSTR m_strMgrpCmbnModeKey;
	
	//device Attributes
	BSTR m_strDeviceKey;
	BSTR m_strFactoryKey;
	BSTR m_strDeviceTypeKey;		//设备型号
	BSTR m_strStandNameKey;	
	BSTR m_strIsTimeSetsUnit_ms_Key;
	BSTR m_strSrcDeviceModelFileKey;
	BSTR m_strDsvTextWithValueKey;
	BSTR m_strDsvTextWithUtcTimeKey;

	//cpus
	BSTR m_strCpusKey;
	BSTR m_strCpuKey;
	BSTR m_strDeviceModelKey;
	BSTR m_strLDeviceKey;
	BSTR m_strDataSetKey;
	BSTR m_strDataSetGroupKey;
	BSTR m_strLogKey;
	BSTR m_strLogsKey;
	BSTR m_strLogCtrlKey;
	BSTR m_strLogCtrlsKey;
	BSTR m_strTestGlobalDatasMngrKey;

	//analogs
	BSTR m_strAnalogsKey;
	BSTR m_strAnalogKey;
	BSTR m_strUnitKey;

	//sets
	BSTR m_strSetsKey;
	BSTR m_strSetKey;
	BSTR m_strDataTypeKey;
	BSTR m_strMinValKey;
	BSTR m_strMaxValKey;
	BSTR m_strRWAttrKey;
	BSTR m_strDataIndexKey;

	//ctrl-words
	BSTR m_strCtrlWordsKey;
	//soft-switchs
	BSTR m_strSoftSwitchsKey;
	//binary-ins
	BSTR m_strBinaryInsKey;
	BSTR m_strBinaryKey;
	//binary-outs
	BSTR m_strBinaryOutsKey;
	//soes
	BSTR m_strSoesKey;
	BSTR m_strSoeKey;
	BSTR m_strTimeKey;

	//Sys-paras
	BSTR m_strSysParasKey;
	BSTR m_strDataKey;
	BSTR m_strFormatKey;
	BSTR m_strRemarkKey;
	BSTR m_strSelectKey;
	BSTR m_strTestParaEditModeKey;
	BSTR m_strProjectIDKey;

	//test-paras
	BSTR m_strTestParasKey;

	//macrotest
	BSTR m_strMacroTestKey;
	//para
	BSTR m_strParaKey;
	BSTR m_strMacroIDKey;
	BSTR m_strTestModeKey;
	BSTR m_strParaDatasKey;

	//faultPara
	BSTR m_strFaultParaKey;
	BSTR m_strFaultParaUserKey;
	BSTR m_strParaSysVarKey;
	BSTR m_strSysVarTypeKey;
	BSTR m_strSysVarPathKey;
	BSTR m_strFaultParaTableParaKey;
	BSTR m_strFaultParaTableParaUserKey;

	//commcmd
	BSTR m_strCommCmdKey;
	BSTR m_strCpuIDKey;
	BSTR m_strDataSetPathKey;
	//cmd
	BSTR m_strCmdKey;
	BSTR m_strDelayBeforeCmdKey;
	BSTR m_strDelayAfterCmdKey;
	BSTR m_strCalModeKey;
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

	//sysparaedit
	BSTR m_strSysParaEditKey;
	BSTR m_strParasKey;
	BSTR m_strSysParaEditGroupKey;
	BSTR m_strSysParaEditGroupsKey;

	BSTR m_strValueKey;
	BSTR m_strDefaultValueKey;

	//report map
	BSTR m_strPrecisionKey;//BSTR m_strSelectKey;
	BSTR m_strBkmkKey;
	BSTR m_strAreaKey;
	BSTR m_strReportMapKey;
	BSTR m_strMapRepeatKey;
	BSTR m_strAreaTypeKey;   //区域标签的类型

	BSTR m_strCGbDataSetTypeKey; //data-set-type
	BSTR m_strCGbDataSetTypesKey; //data-set-type
	BSTR m_strDsParameterKey; //dsParameter
	BSTR m_strDsSettingKey; //dsSetting
	BSTR m_strDsEnaKey; //dsEna
	BSTR m_strDsAinKey; //dsAin
	BSTR m_strDsDinKey; //dsDin
	BSTR m_strDsRecKey; //dsRec
	BSTR m_strDsTripInfoKey; //dsTripInfo
	BSTR m_strDsAlarmKey; //dsAlarm
	BSTR m_strDsWarningKey; //dsWarning
	BSTR m_strDsSoeKey; //dsSoe
	BSTR m_strDsSVKey; //dsSV
	BSTR m_strDsGOOSEKey; //dsGOOSE
	BSTR m_strCanWriteKey; //can-write

	BSTR m_strGbtDataInterfacesKey;
	BSTR m_strGbtDataInterfaceKey;
	BSTR m_strGbtDataKey;
	BSTR m_strGbtDatasKey;
	BSTR m_strGbtDataScriptKey;
	BSTR m_strGbtDataKeyKey;
	BSTR m_strGbtDataScptOptrAndKey;
	BSTR m_strGbtDataScptOptrOrKey;
	BSTR m_strGbtDataScptOptrNotKey;
	BSTR m_strGbtDataScptFuncMustHaveKey;
	BSTR m_strGbtDataScptFuncMustNotHaveKey;

	//character
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

	//2019-3-17  自动测试过程，与模板生成过程集成到一起
	BSTR m_strCGbWzdAutoTemplateKey; //template
	BSTR m_strCGbWzdAutoConfigKey; //gb-wzd-auto
	BSTR m_strDvm_FileKey; //dvm-file
	BSTR m_strGbxml_FileKey; //gbxml-file
	BSTR m_strRel_PathKey; //rel-path
	BSTR m_strBin_OffsetKey; //bin-offset
	BSTR m_strBout_OffsetKey; //bout-offset
	BSTR m_strDateKey; //date
	BSTR m_strCnt_BinKey; //cnt-bin
	BSTR m_strCnt_BoutKey; //cnt-bout
	BSTR m_strAutoKey;  //Auto
	BSTR m_strDICountKey;  //DICount
	BSTR m_strDOCountKey;  //DOCount
	BSTR m_strEnaCountKey; //EnaCount
	BSTR m_strBmkDITestKey; //Bmk_DITest;
	BSTR m_strBmkDOTestKey; //Bmk_DOTest;

	BSTR m_strItemMngrKey;  //itemmngr
	BSTR m_strwzdAutoItemsKey; //items
	BSTR m_strItemTypeKey;   //itemtype
	BSTR m_strwzdAutoSafetyKey;   //safety

	BSTR m_strItemParaMngrKey;   //itemparamngr
	BSTR m_strItemParaKey;       //itempara

	//2020-5-24
	BSTR m_strCSysGbRptUIKey; //sys-rpt-ui
	BSTR m_strCSysRptTableKey; //table
	BSTR m_strCSysRptTrKey; //tr
	BSTR m_strCSysRptTdKey; //td
	BSTR m_strCSysRptTextKey; //text
	BSTR m_strTextKey; //text
	BSTR m_strAlignKey; //align
	BSTR m_strFont_SizeKey; //font-size
	BSTR m_strFont_NameKey; //font-name
	BSTR m_strRowspanKey; //rowspan
	BSTR m_strBorderKey; //border
	BSTR m_strWidthKey; //width
	BSTR m_strHeightKey; //height
	BSTR m_strBgColorKey; //bgcolor
	BSTR m_strCellPaddingKey; //cellpadding

	//2021-11-17  lijunqing
	BSTR m_strGbDevSaveStruDescFileKey;
	BSTR m_strGbDevSaveStruDescDsvKey;


	//shaolei 2022-01-05 
	BSTR m_strTestMacroUiParasKey;  //test-macro-ui-paras
	//shaolei 2023-3-22 
	BSTR m_strTestMacroCharParasKey;  //test-macro-char-paras

	//lijunqing 2022-9-24
	BSTR m_strCItemRsltExprRunKey;  //rslt-expr

	//lijunqing 2022-5-6
	BSTR m_strHdResReqestKey;  //HdResReq

	//shaolei 2023-3-19 保存模板时，是否保存测试项目的报告（reports节点）
	//该标记的设计之初，是用来标记是否保存整个reports节点
	//但实际应用发现，应当保留初始报告（ID = _Init_ 的report节点）
	//原因在于，我不保存reports节点，打开的gbxml后再次保存，则dscxml中也没有初始报告了
	long m_nSaveItemRpts;
	static void IncXml_SaveItemRpts(CGbXMLKeys *pXmlKeys=NULL, long nAdd=1);
	static void DecXml_SaveItemRpts(CGbXMLKeys *pXmlKeys=NULL, long nDec=1);
public:
	CDataMngrXmlRWKeys *m_pReportValueKeys;
	
	static BSTR TestDefineKey()  {   return g_pGbXMLKeys->m_strTestDefineKey;  }

	static BSTR CGbDataSetTypeKey()  {   return g_pGbXMLKeys->m_strCGbDataSetTypeKey;  }
	static BSTR CGbDataSetTypesKey()  {   return g_pGbXMLKeys->m_strCGbDataSetTypesKey;  }
	static BSTR DsParameterKey()  {   return g_pGbXMLKeys->m_strDsParameterKey;  }
	static BSTR DsSettingKey()  {   return g_pGbXMLKeys->m_strDsSettingKey;  }
	static BSTR DsEnaKey()  {   return g_pGbXMLKeys->m_strDsEnaKey;  }
	static BSTR DsAinKey()  {   return g_pGbXMLKeys->m_strDsAinKey;  }
	static BSTR DsDinKey()  {   return g_pGbXMLKeys->m_strDsDinKey;  }
	static BSTR DsRecKey()  {   return g_pGbXMLKeys->m_strDsRecKey;  }
	static BSTR DsTripInfoKey()  {   return g_pGbXMLKeys->m_strDsTripInfoKey;  }
	static BSTR DsAlarmKey()  {   return g_pGbXMLKeys->m_strDsAlarmKey;  }
	static BSTR DsWarningKey()  {   return g_pGbXMLKeys->m_strDsWarningKey;  }
	static BSTR DsSoeKey()  {   return g_pGbXMLKeys->m_strDsSoeKey;  }
	static BSTR DsSVKey()  {   return g_pGbXMLKeys->m_strDsSVKey;  }
	static BSTR DsGOOSEKey()  {   return g_pGbXMLKeys->m_strDsGOOSEKey;  }
	static BSTR CanWriteKey()  {   return g_pGbXMLKeys->m_strCanWriteKey;  }

	static BSTR CAinExpandMngrKey()  {   return g_pGbXMLKeys->m_strCAinExpandMngrKey;  }
	static BSTR CAinExpandKey()  {   return g_pGbXMLKeys->m_strCAinExpandKey;  }
	static BSTR AbsKey()  {   return g_pGbXMLKeys->m_strAbsKey;  }
	static BSTR RealKey()  {   return g_pGbXMLKeys->m_strRealKey;  }
	static BSTR RsltKey()  {   return g_pGbXMLKeys->m_strRsltKey;  }

	static BSTR AreaTypeKey()  {   return g_pGbXMLKeys->m_strAreaTypeKey;  }

	//2019-3-17  自动测试过程，与模板生成过程集成到一起
	static BSTR CGbWzdAutoTemplateKey()  {   return g_pGbXMLKeys->m_strCGbWzdAutoTemplateKey;  }
	static BSTR CGbWzdAutoConfigKey()  {   return g_pGbXMLKeys->m_strCGbWzdAutoConfigKey;  }
	static BSTR Dvm_FileKey()  {   return g_pGbXMLKeys->m_strDvm_FileKey;  }
	static BSTR Gbxml_FileKey()  {   return g_pGbXMLKeys->m_strGbxml_FileKey;  }
	static BSTR Rel_PathKey()  {   return g_pGbXMLKeys->m_strRel_PathKey;  }
	static BSTR Bin_OffsetKey()  {   return g_pGbXMLKeys->m_strBin_OffsetKey;  }
	static BSTR Bout_OffsetKey()  {   return g_pGbXMLKeys->m_strBout_OffsetKey;  }
	static BSTR VersionKey()  {   return g_pGbXMLKeys->m_strVersionKey;  }
	static BSTR DateKey()  {   return g_pGbXMLKeys->m_strDateKey;  }
	static BSTR Cnt_BinKey()  {   return g_pGbXMLKeys->m_strCnt_BinKey;  }
	static BSTR Cnt_BoutKey()  {   return g_pGbXMLKeys->m_strCnt_BoutKey;  }
	static BSTR AutoKey()	{	return g_pGbXMLKeys->m_strAutoKey;	}
	static BSTR DICountKey()	{	return g_pGbXMLKeys->m_strDICountKey;	}
	static BSTR DOCountKey()	{	return g_pGbXMLKeys->m_strDOCountKey;	}
	static BSTR EnaCountKey()	{	return g_pGbXMLKeys->m_strEnaCountKey;	}
	static BSTR BmkDITestKey()	{	return g_pGbXMLKeys->m_strBmkDITestKey;		}
	static BSTR BmkDOTestKey()	{	return g_pGbXMLKeys->m_strBmkDOTestKey;		}

	static BSTR ItemMngrKey()	{	return g_pGbXMLKeys->m_strItemMngrKey;	}
	static BSTR WzdAutoItemsKey()		{	return g_pGbXMLKeys->m_strwzdAutoItemsKey;	}
	static BSTR ItemTypeKey()	{	return g_pGbXMLKeys->m_strItemTypeKey;	}
	static BSTR WzdAutoSafetyKey()	{	return g_pGbXMLKeys->m_strwzdAutoSafetyKey;	}
	
	static BSTR ItemParaMngrKey()	{	return g_pGbXMLKeys->m_strItemParaMngrKey;	}
	static BSTR ItemParaKey()		{	return g_pGbXMLKeys->m_strItemParaKey;	}

	static BSTR CSysGbRptUIKey()  {   return g_pGbXMLKeys->m_strCSysGbRptUIKey;  }
	static BSTR CSysRptTableKey()  {   return g_pGbXMLKeys->m_strCSysRptTableKey;  }
	static BSTR CSysRptTrKey()  {   return g_pGbXMLKeys->m_strCSysRptTrKey;  }
	static BSTR CSysRptTdKey()  {   return g_pGbXMLKeys->m_strCSysRptTdKey;  }
	static BSTR CSysRptTextKey()  {   return g_pGbXMLKeys->m_strCSysRptTextKey;  }
	static BSTR TextKey()  {   return g_pGbXMLKeys->m_strTextKey;  }
	static BSTR AlignKey()  {   return g_pGbXMLKeys->m_strAlignKey;  }
	static BSTR Font_SizeKey()  {   return g_pGbXMLKeys->m_strFont_SizeKey;  }
	static BSTR Font_NameKey()  {   return g_pGbXMLKeys->m_strFont_NameKey;  }
	static BSTR BkmkKey()  {   return g_pGbXMLKeys->m_strBkmkKey;  }
	static BSTR RowspanKey()  {   return g_pGbXMLKeys->m_strRowspanKey;  }
	static BSTR BorderKey()  {   return g_pGbXMLKeys->m_strBorderKey;  }
	static BSTR WidthKey()  {   return g_pGbXMLKeys->m_strWidthKey;  }
	static BSTR HeightKey()  {   return g_pGbXMLKeys->m_strHeightKey;  }
	static BSTR BgColorKey()  {   return g_pGbXMLKeys->m_strBgColorKey;  }
	static BSTR CellPaddingKey()  {   return g_pGbXMLKeys->m_strCellPaddingKey;  }

private:
	void InitReportValueXMLRWKeys();
};
