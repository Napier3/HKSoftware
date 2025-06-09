#pragma once

#include "GbXMLKeys.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#include "../../../Module/API/GlobalConfigApi.h"


//////////////////////////////////////////////////////////////////////////
//版本管理
#define GBVERSION_1_0         0X00010000
#define GBVERSION_1_1         0X00010001
#define GBVERSION_1_2         0X00010002    //增加脚本管理文件，脚本库文件有内部改为外部
#define GBVERSION_1_3         0X00010003    //增加使用扩展设备通讯
#define GBVERSION_1_4         0X00010004    //增加使用扩展设备通讯
#define GBVERSION_1_5         0X00010005    //增加MacroTest的重复次数的报告处理方式
#define GBVERSION_1_6         0X00010006    //设备数据模型的修改
#define GBVERSION_1_7         0X00010007    //设备增加时属性：时间定值的单位是否为S判断，主要用于自动处理与时间相关的数据计算，ms自动除以1000
#define GBVERSION_1_8         0X00010008    //模板增加计时变量，记录从开始测试到终止测试的时间长度
#define GBVERSION_1_9         0X00010009    //增加多设备数据模型，用于线路纵联差动
#define GBVERSION_1_10        0X0001000A    //增加报告标签增加属性、处理两个功能
#define GBVERSION_1_11        0X0001000B    //CDataObj:max,min两个值直接使用double类型，不使用CString
#define GBVERSION_1_12        0X0001000C    //设备数据模型：增加规约模板选择、点表选择功能
#define GBVERSION_1_13        0X0001000D    //测试完成，自动保存测试报告到指定位置；安全措施增加一个延时时间；
#define GBVERSION_1_14        0X0001000E    //CItems,m_strType
#define GBVERSION_1_15        0X0001000F    //CCmd : m_nUseConnect

//2015-3-5  李俊庆
//CItems : m_strStxmlFile, m_strWzdMapFile:用于记录实例化时使用的子模板和映射文件
#define GBVERSION_1_16        0X00010010    

//2015-6-10  李俊庆
//CGuideBook : m_nTestControlMode
#define GBVERSION_1_17        0X00010011    

//2015-9-10  李俊庆
//CCmd::m_nZoneIndex  定值区号
#define GBVERSION_1_18        0X00010012    

//2015-9-20  李俊庆
//CDevice  增加 m_nDsvTextWithValue
//CCommCmd 增加  m_nSortSoeByT
#define GBVERSION_1_19        0X00010013  


//CRptBkmk增加m_nFillMode，0=cell；1=col；2=row
#define GBVERSION_1_20        0X00010014    

//CDataObj增加StepSize
#define GBVERSION_1_21        0X00010015    

//CGuideBook增加m_strGbXmlFile，用于更新项目参数
#define GBVERSION_1_22        0X00010016    

//CDvice::m_strSrcDeviceModelFile
#define GBVERSION_1_23        0X00010017    

//CGuideBook增加m_strIecfgFile   记录整装置配置文件
#define GBVERSION_1_24        0X00010018    

//CDevice增加报文显示增加m_nDsvTextWithUtcTime  
#define GBVERSION_1_25        0X00010019    

//CSafety增加m_nManyDeviceTestMode，多测试报告的时候的模式：0只执行一次；1：每个报告执行一次 
#define GBVERSION_1_26        0X0001001A    

//CGuideBook增加CTestGlobalDatasMngr:管理全局数据，装置属性、测试仪器等
#define GBVERSION_1_27        0X0001001B    

//CRptArea增加m_strAreaType
#define GBVERSION_1_28        0X0001001C    

//CRptBkmk增加m_strMgrpCmbnMode   2017-10-12
#define GBVERSION_1_29        0X0001001D    

//增加m_nReportFillUseNoRepeat   2017-11-25
#define GBVERSION_1_30        0X0001001E    

//增加CDvmLogs,CReport增加CDvmLogs对象   2018-03-01
#define GBVERSION_1_31        0X0001001F    

//CCommCmd增加m_nDsvRunAfterResultScript   2018-03-08
#define GBVERSION_1_32        0X00010020    

//CRptData增加m_strPrecision
#define GBVERSION_1_33        0X00010021    

//CCommCmd增加m_nCmdExecModeForMgbrpt
#define GBVERSION_1_34        0X00010022

//CCharacterArea串行化m_pCharBisector，TestLine增加m_nTestLineID
#define GBVERSION_1_35        0X00010023

//CGbTestItemBase 增加m_nMdvTestEach
#define GBVERSION_1_36        0X00010024

//CGbTestItemBase 增加m_nMdvTestEach
#define GBVERSION_1_37        0X00010025

//CGuideBook 增加m_strAuthoritySN
#define GBVERSION_1_38        0X00010026

//2020-3-14  特性曲线的改进  lijq
#define GBVERSION_1_39        0X00010027

//2020-6-2  脚本由LUA改为XVM  lijq
#define GBVERSION_1_40        0X00010028

//2021-3-10 CItems增加属性"ActLogic" 表示该项目分类绑定的逻辑图页面  shaolei
#define GBVERSION_1_41        0X00010029

//2022-2-5 特性曲线增加m_strIndex
//佘夫为CCharacteristic增加m_strIndex，但是没有考虑版本兼容，导致读取之前的模板出问题
#define GBVERSION_1_42        0X00010030

//2022-10-3  lijunqing 通信命令对象增加m_nFillRptDataset
#define GBVERSION_1_43        0X00010031

//2023-3-17  shaolei  项目分类增加重复次数属性：m_nRepeatTimes
#define GBVERSION_1_44        0X00010032

//2023-6-20  shaolei  项目分类，增加rpt-title、title-level属性
#define GBVERSION_1_45        0X00010033

#define _use_device_model_ds   

static const DWORD g_dwGuideBookCurrVersion = GBVERSION_1_45;
inline void Gb_InitGuideBookFileVersion(char *pszPrefix, DWORD &dwVersion)
{
	pszPrefix[0]='E';
	pszPrefix[1]='P';
	pszPrefix[2]='O';
	pszPrefix[3]='T';
	pszPrefix[4]='O';
	pszPrefix[5]='.';
	pszPrefix[6]='G';
	pszPrefix[7]='B';
	pszPrefix[8]=0;
	dwVersion = g_dwGuideBookCurrVersion;
}

inline void Gb_InitGuideBookFileVersion(CBinarySerialBuffer &oBuffer)
{
	Gb_InitGuideBookFileVersion(oBuffer.m_chPrefix, oBuffer.m_dwVersion);
	oBuffer.SetCharSet(CHAR_SET_ASCII);

	oBuffer.AddBinaryVersion(g_pszDataMngrVersionPrefix, g_dwDataMngrCurrVersion, g_dwDataMngrVersionID);
}

//class id定义
#define GBCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00030000)
#define GBCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00030000)

#define GBCLASSID_ITEMBASE			(GBCLASSID_EXLISTCLASS	+  0x00001000)
#define GBCLASSID_ITEMSBASE			(GBCLASSID_EXLISTCLASS	+  0x00003000)

#define GBCLASSID_GUIDEBOOK		(GBCLASSID_ITEMSBASE	+  0x00000000)
#define GBCLASSID_JOBGUIDE			(GBCLASSID_ITEMSBASE	+  0x00000001)
#define GBCLASSID_DEVICE				(GBCLASSID_ITEMSBASE	+  0x00000002)
#define GBCLASSID_SYSPARAS			(GBCLASSID_EXLISTCLASS	+  0x00000003)
#define GBCLASSID_TESTPARAS			(GBCLASSID_EXLISTCLASS	+  0x00000004)
#define GBCLASSID_CPUS					(GBCLASSID_EXLISTCLASS	+  0x00000005)
#define GBCLASSID_CPU					(GBCLASSID_EXLISTCLASS	+  0x00000006)
#define GBCLASSID_ANALOGS			(GBCLASSID_EXLISTCLASS	+  0x00000007)
#define GBCLASSID_ANALOG				(GBCLASSID_BASECLASS		+  0x00000008)
#define GBCLASSID_SETS					(GBCLASSID_EXLISTCLASS	+  0x00000009)
#define GBCLASSID_SET					(GBCLASSID_BASECLASS		+  0x0000000A)
#define GBCLASSID_CTRLWORDS		(GBCLASSID_EXLISTCLASS	+  0x0000000B)
#define GBCLASSID_CTRLWORD			(GBCLASSID_BASECLASS		+  0x0000000C)
#define GBCLASSID_SOFTSWITCHS	(GBCLASSID_EXLISTCLASS	+  0x0000000D)
#define GBCLASSID_SOFTSWITCH		(GBCLASSID_BASECLASS		+  0x0000000E)
#define GBCLASSID_BINARYS			(GBCLASSID_EXLISTCLASS	+  0x0000000F)
#define GBCLASSID_BINARY				(GBCLASSID_BASECLASS		+  0x00000010)
#define GBCLASSID_SOES					(GBCLASSID_EXLISTCLASS	+  0x00000011)
#define GBCLASSID_SOE					(GBCLASSID_BASECLASS		+  0x00000012)
#define GBCLASSID_ITEMS				(GBCLASSID_ITEMSBASE	+  0x00000013)
#define GBCLASSID_SAFETY				(GBCLASSID_ITEMBASE	+  0x00000014)
#define GBCLASSID_MACROTEST		(GBCLASSID_ITEMBASE	+  0x00000015)
#define GBCLASSID_SYSPARAEDIT		(GBCLASSID_ITEMBASE	+  0x00000016)
#define GBCLASSID_COMMCMDS		(GBCLASSID_ITEMBASE	+  0x00000017)
#define GBCLASSID_COMMCMD			(GBCLASSID_ITEMBASE	+  0x00000018)
#define GBCLASSID_MSGS					(GBCLASSID_EXLISTCLASS	+  0x00000019)
#define GBCLASSID_MSG					(GBCLASSID_BASECLASS		+  0x0000001A)
#define GBCLASSID_STANDARD			(GBCLASSID_BASECLASS	+  0x0000001B)
#define GBCLASSID_MACROPARA		(GBCLASSID_EXLISTCLASS	+  0x0000001C)
#define GBCLASSID_REPORTS			(GBCLASSID_EXLISTCLASS	+  0x0000001D)
#define GBCLASSID_REPORT				(GBCLASSID_BASECLASS		+  0x0000001E)
#define GBCLASSID_DEVICES				(GBCLASSID_EXLISTCLASS	+  0x0000001F)
#define GBCLASSID_BINARYINS			(GBCLASSID_EXLISTCLASS	+  0x00000020)
#define GBCLASSID_BINARYOUTS		(GBCLASSID_EXLISTCLASS	+  0x00000021)
#define GBCLASSID_VALPARAS			(GBCLASSID_BASECLASS		+  0x00000022)
#define GBCLASSID_SCRIPTTEXT		(GBCLASSID_BASECLASS		+  0x00000023)

#define GBCLASSID_DEVICE_SYSPARAS                (GBCLASSID_EXLISTCLASS + 0x00000024)
#define GBCLASSID_FAULTPARAS                   (GBCLASSID_EXLISTCLASS + 0x00000026)
#define GBCLASSID_FAULTPARAS_PARA           (GBCLASSID_EXLISTCLASS + 0x00000028)
#define GBCLASSID_CMD				                 (GBCLASSID_EXLISTCLASS + 0x00000029)
#define GBCLASSID_SCRIPT_TEXT_MNGR         (GBCLASSID_EXLISTCLASS + 0x0000002A)
#define GBCLASSID_FAULTPARAS_PARA_USER   (GBCLASSID_BASECLASS + 0x0000002B)

#define GBCLASSID_SCRIPTTEXT_INIT		(GBCLASSID_BASECLASS		+  0x0000002C)
#define GBCLASSID_SCRIPTTEXT_NAME		(GBCLASSID_BASECLASS		+  0x0000002D)
#define GBCLASSID_SCRIPTTEXT_RESULT		(GBCLASSID_BASECLASS		+  0x0000002E)
#define GBCLASSID_DEVICE_TESTPARAS                (GBCLASSID_EXLISTCLASS + 0x0000002F)
#define GBCLASSID_FAULTPARASUSER                   (GBCLASSID_EXLISTCLASS + 0x00000030)
#define GBCLASSID_TESTTYPES                        (GBCLASSID_EXLISTCLASS + 0x00000031)
#define GBCLASSID_TESTTYPE                         (GBCLASSID_BASECLASS + 0x00000032)

#define GBCLASSID_SYSPARAEDITGROUP                        (GBCLASSID_EXLISTCLASS + 0x00000033)
#define GBCLASSID_SYSPARAEDITGROUPS                         (GBCLASSID_EXLISTCLASS + 0x00000034)
#define GBCLASSID_DLLCALL                         (GBCLASSID_BASECLASS + 0x00000035)
#define GBCLASSID_REPORTSBACK                         (GBCLASSID_BASECLASS + 0x00000036)
#define GBCLASSID_DATASET                         (GBCLASSID_EXLISTCLASS + 0x00000037)
#define GBCLASSID_DATAOBJ                         (GBCLASSID_EXLISTCLASS + 0x00000038)
#define GBCLASSID_DATAVALUE                         (GBCLASSID_BASECLASS + 0x00000039)
#define GBCLASSID_GBDATASETTYPES                         (GBCLASSID_EXLISTCLASS + 0x0000003A)
#define GBCLASSID_GBDATASETTYPE                         (GBCLASSID_BASECLASS + 0x0000003B)
#define GBCLASSID_ZONECHARACERISTICS                         (GBCLASSID_EXLISTCLASS + 0x0000003C)
#define GBCLASSID_ZONECHARACERISTIC                         (GBCLASSID_EXLISTCLASS + 0x0000003D)
#define GBCLASSID_DATAOBJ_VALUE                         (GBCLASSID_EXLISTCLASS + 0x0000003E)

#define RPTCLASSID_RPTBKMK			(GBCLASSID_BASECLASS   + 0x00000041)
#define RPTCLASSID_RPTAREA			(GBCLASSID_EXLISTCLASS + 0x00000042)
#define RPTCLASSID_RPTDATA			(GBCLASSID_EXLISTCLASS + 0x00000043)
#define RPTCLASSID_RPTREPORTMAP		(GBCLASSID_EXLISTCLASS + 0x00000044)
#define RPTCLASSID_RPTITEM		(GBCLASSID_EXLISTCLASS + 0x00000045)
#define RPTCLASSID_RPTMAPREPEAT		(GBCLASSID_EXLISTCLASS + 0x00000046)

#define GBCLASSID_CAINEXPAND       (GBCLASSID_BASECLASS + 0x00000047)
#define GBCLASSID_CAINEXPANDMNGR       (GBCLASSID_EXLISTCLASS + 0x00000048)

#define GBCLASSID_GBTDATAINTERFACES                         (GBCLASSID_EXLISTCLASS + 0x00000050)
#define GBCLASSID_GBTDATAINTERFACE                         (GBCLASSID_EXLISTCLASS + 0x00000051)
#define GBCLASSID_GBTDATA                         (GBCLASSID_BASECLASS + 0x00000052)
#define GBCLASSID_GBTDATASCRIPT                         (GBCLASSID_EXLISTCLASS + 0x00000053)
#define GBCLASSID_GBTDATAS                         (GBCLASSID_EXLISTCLASS + 0x00000054)
#define GBCLASSID_GBTDATAKEY                         (GBCLASSID_BASECLASS + 0x00000055)
#define GBCLASSID_GBTDATASCPTOPTR                         (GBCLASSID_EXLISTCLASS + 0x00000056)
#define GBCLASSID_GBTDATASCPTFUNC                         (GBCLASSID_EXLISTCLASS + 0x00000057)
#define GBCLASSID_GBTDATASCPTOPTR_AND                         (GBCLASSID_EXLISTCLASS + 0x00000058)
#define GBCLASSID_GBTDATASCPTOPTR_OR                         (GBCLASSID_EXLISTCLASS + 0x00000059)
#define GBCLASSID_GBTDATASCPTOPTR_NOT                         (GBCLASSID_EXLISTCLASS + 0x0000005A)
#define GBCLASSID_GBTDATASCPTFUNC_MUSTHAVE                         (GBCLASSID_EXLISTCLASS + 0x0000005B)
#define GBCLASSID_GBTDATASCPTFUNC_MUSTNOTHAVE                      (GBCLASSID_EXLISTCLASS + 0x0000005C)

#define GBCLASSID_MACROCHARITEMS                         (GBCLASSID_ITEMBASE + 0x0000005D)
#define GBCLASSID_MACROCHARITEMLINEDEF                      (GBCLASSID_BASECLASS + 0x0000005E)
#define GBCLASSID_ITEMSRSLTEXPR                     (GBCLASSID_BASECLASS + 0x0000005F)
#define GBCLASSID_ITEMSRSLTEXPRSCRIPT                      (GBCLASSID_EXLISTCLASS + 0x00000060)
#define GBCLASSID_ITEMSRSLTEXPRSCRIPTMNGR                      (GBCLASSID_EXLISTCLASS + 0x00000061)
#define GBCLASSID_TESTGLOBALDATASMNGR                      (GBCLASSID_EXLISTCLASS + 0x00000062)

//2018-3-4  LIJQ  日志部分的功能
#define GBCLASSID_GBLOGCTRL                       (GBCLASSID_BASECLASS    + 0x00000063)
#define GBCLASSID_GBLOGCTRLS                      (GBCLASSID_EXLISTCLASS + 0x00000064)

//2019-3-17  自动测试过程，与模板生成过程集成到一起
#define MNGRCLASSID_CGBWZDAUTOCONFIG       (GBCLASSID_EXLISTCLASS + 0x00000065)
#define MNGRCLASSID_CGBWZDAUTOTEMPLATE       (GBCLASSID_EXLISTCLASS + 0x00000066)

//2021-10-9  lijunqing
#define GBCLASSID_DATASETGROUP                         (GBCLASSID_EXLISTCLASS + 0x00000067)

//LIJUNQING  2022-9-24
#define GBCLASSID_ITEMRSLTEXPRRUN   (GBCLASSID_EXLISTCLASS		+  0x00000068)

#define GBCLASSID_TESTCONTROL                      (GBCLASSID_EXLISTCLASS + 0x00000F00)


#define GBCLASSID_TESTITEMMNGR                      (GBCLASSID_EXLISTCLASS + 0x00000F01)
#define GBCLASSID_GBWZDAUTOITEMS                     (GBCLASSID_EXLISTCLASS + 0x00000F02)
#define GBCLASSID_GBWZDAUTOSAFETY                   (GBCLASSID_EXLISTCLASS + 0x00000F03)
#define GBCLASSID_TESTITEMPARAMNGR                      (GBCLASSID_EXLISTCLASS + 0x00000F04)
#define GBCLASSID_GBWZDAUTOITEMPARA                 (GBCLASSID_EXLISTCLASS + 0x00000F05)


//shaolei 2022-0-10-05
#define GBCLASSID_TESTMACROUIPARAS		(GBCLASSID_BASECLASS		+  0x00000069)
//shaolei 2023-3-22
#define GBCLASSID_TESTMACROCHARPARAS		(GBCLASSID_BASECLASS		+  0x0000006A)


//LIJUNQING  2022-9-24
#define GBCLASSID_HDRESREQUEST   (GBCLASSID_ITEMBASE		+  0x0000006B)

#define TOTALTEST        0x00000001
#define PARTTEST         0x00000002
#define CHECKTEST        0x00000004


inline BOOL Gb_IsGbItemClassID(UINT nClassID)
{
	if (nClassID == GBCLASSID_SAFETY || nClassID == GBCLASSID_MACROTEST
		|| nClassID == GBCLASSID_COMMCMD || nClassID == GBCLASSID_SYSPARAEDIT
		|| nClassID == GBCLASSID_MACROCHARITEMS || nClassID == GBCLASSID_HDRESREQUEST)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

inline BOOL Gb_IsItemBaseClassID(UINT nClassID)
{
	return ( (nClassID & GBCLASSID_ITEMBASE) == GBCLASSID_ITEMBASE);
}


inline BOOL Gb_IsItemsBaseClassID(UINT nClassID)
{
	UINT nTemp = nClassID & GBCLASSID_ITEMSBASE;

	return ( nTemp == GBCLASSID_ITEMSBASE);
}

inline BOOL Gb_IsItemNeedExportRpt(UINT nClassID)
{
	if (nClassID == GBCLASSID_ITEMSRSLTEXPRSCRIPTMNGR || nClassID == CHARCLASSID_CCHARACTERISTICS || nClassID == GBCLASSID_DEVICE_SYSPARAS
		|| nClassID == GBCLASSID_SCRIPTTEXT
		|| nClassID == GBCLASSID_SCRIPT_TEXT_MNGR || nClassID == GBCLASSID_CPUS
		|| nClassID == GBCLASSID_CMD || nClassID == DVMCLASSID_CDSVSCRIPT
		|| nClassID == DTMCLASSID_CSHORTDATAS || nClassID == GBCLASSID_STANDARD || nClassID == GBCLASSID_DLLCALL || nClassID == GBCLASSID_MSG
		|| nClassID == GBCLASSID_MACROPARA || nClassID == DTMCLASSID_CVALUES
		|| nClassID == GBCLASSID_SCRIPTTEXT_INIT || nClassID == GBCLASSID_SCRIPTTEXT_NAME
		|| nClassID == GBCLASSID_SCRIPTTEXT_RESULT || nClassID == GBCLASSID_ITEMSRSLTEXPRSCRIPT
		|| nClassID == GBCLASSID_MACROCHARITEMLINEDEF || nClassID == GBCLASSID_MACROPARA || nClassID == CHARCLASSID_CCHARACTERISTIC)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

//////////////////////////////////////////////////////////////////////////
//相关常量定义
enum GbFileOptrState
{
	GbFileNotExist = 0,
	GbFileVersionHigh = 1,
	GbFileWriteError = 2,
	GbFileReadError = 3
};

enum GbSysParaType
{
	GbSysParaTypeSets = 0,
	GbSysParaTypeSoftSwitch = 1,
	GbSysParaTypeCtrlWord = 2,
	GbSysParaTypeDevicePara = 3,
	GbSysParaTypeSysPara = 4
};

enum GbSafetyType
{
	GbSafetyTypeHint = 0,
	GbSafetyTypeSafety = 1,
	GbSafetyTypeFlow = 2,
	GbSafetyTypeHdChk =3,
	GbSafetyTypeCnln = 4
};

enum GbJumpMode
{
	GbJumpNone = 0,
	GbJumpToItem = 1,
	GbJumpToExit = 2,
	GbJumpHint = 3,
	GbJumpItemsStateChanged = 4
};

enum GbFilterOptr
{
	GbFilterOptrEqual = 0,
	GbFilterOptrLessThan = 1,
	GbFilterOptrMoreThan = 2,
	GbFilterOptrLessThanEqual = 3,
	GbFilterOptrMoreThanEqual = 4,
	GbFilterOptrAnd = 5,
	GbFilterOptrNotEqual = 6
};

enum GbFilterAttrType
{
	GbFilterAttrIndex = 0,
	GbFilterAttrShow = 1,
	GbFilterAttrEnable = 2,
	GbFilterAttrSelect = 3,
	GbFilterAttrState = 4,
	GbFilterAttrTkid = 5
};

enum GbMacroTestType
{
	GbMacroTestTypeAnalog = 0,
	GbMacroTestTypeBinaryIn = 1,
	GbMacroTestTypeBinaryOut = 2,
	GbMacroTestTypeMacro = 3
};

enum GbMacroTestMode
{
	GbMacroTestModeAutoTest = 0,
	GbMacroTestModeHandWithFault = 1,
	GbMacroTestModeHand = 2,
	GbMacroTestModeOffline = 3
};

enum GbManyDeviceItemTestMode
{
	GbMdItemTestMode_OneTime=0,
	GbMdItemTestMode_ManyTime=1
};

//////////////////////////////////////////////////////////////////////////
//结果判断和结果描述的关键字
static const CString g_strDataResultJudgePrevKey			= _T("err_"); //2019-1-6:增加每个数据是否合格的判断
static const CString g_strTestResultJudgeKey			= _T("RsltJdg");
static const CString g_strTestResultDescriptKey		= _T("RsltDsc");
static const CString g_strTestResultJudgeNameKey			= _T("结果判断");
static const CString g_strTestResultDescriptNameKey		= _T("结果描述");
static const CString g_pszTripValueKey_Trip           = _T("Trip");
static const CString g_pszTripTimeKey_Trip           = _T("Ttrip");
static const CString g_pszTripTimeKey_Trip2           = _T("TTrip");
static const CString g_pszTripTimeKey_Act            = _T("Act");
static const CString g_pszTripTimeDesc_Trip          = _T("动作");
static const CString g_pszTripTimeDesc_NoTrip        = _T("未动作");
static const CString g_pszTripID_Angle               = _T("Angle");

static const CString g_strTestResultAbsErrorKey			= _T("AbsError");
static const CString g_strTestResultRelErrorKey			= _T("RelError");
static const CString g_strTestResultRsltEx1Key			= _T("RsltEx1");
static const CString g_strTestResultRsltEx2Key			= _T("RsltEx2");
static const CString g_strTestResultRsltEx3Key			= _T("RsltEx3");
static const CString g_strTestResultRsltEx4Key			= _T("RsltEx4");

//shaolei 20211020  每个测试项目，都有各自的测试时间，需要填写到报告中
static const CString g_strTestResultTimeKey		= _T("RsltTime");
static const CString g_strTestResultTimeNameKey		= _T("报告时间");

//shaolei 2023-3-22 每个智能生成的测试项目，报告增加固定的四个结果
static const CString g_strTestResultAbsRsltCal1Key			= _T("AbsRsltCal1");
static const CString g_strTestResultAbsRsltCal2Key			= _T("AbsRsltCal2");
static const CString g_strTestResultRelRsltCal1Key			= _T("RelRsltCal1");
static const CString g_strTestResultRelRsltCal2Key			= _T("RelRsltCal2");

//报告调整时，刨除Error相关的报告数据：误差限、误差计算结果、误差判断逻辑
inline BOOL Gb_IsErrKeyID(const CString &strID)
{
	if (strID.Find(_T("Error")) >= 0)
	{
		return TRUE;
	}

	if (strID.Find(_T("Err")) >= 0)
	{
		return TRUE;
	}

	return FALSE;
}

inline BOOL Gb_IsTripKeyID(const CString &strID, BOOL &bIsAngle)
{
	bIsAngle = (strID.Find(g_pszTripID_Angle) > 0);

	if (strID.Left(5) == g_pszTripTimeKey_Trip)
	{
		return TRUE;
	}

	if (strID.Left(5) == g_pszTripTimeKey_Trip2)
	{
		return TRUE;
	}

	if (strID.Left(4) == g_pszTripValueKey_Trip)
	{
		return TRUE;
	}

	CString strTripKey;
	strTripKey = _T("$") + g_pszTripTimeKey_Trip;

	if (strID.Find(strTripKey) > 0)
	{
		return TRUE;
	}

	strTripKey = _T("$") + g_pszTripTimeKey_Trip2;

	if (strID.Find(strTripKey) > 0)
	{
		return TRUE;
	}

	strTripKey = _T("$") + g_pszTripValueKey_Trip;

	if (strID.Find(strTripKey) > 0)
	{
		return TRUE;
	}

	return FALSE;
}

inline CString Gb_GetActKeyIDByTripKeyID(const CString &strID, const CString &strKey)
{
	CString strActID;

	if (strID.Left(strKey.GetLength()) == strKey)
	{
		strActID = g_pszTripTimeKey_Act;
		strActID += strID.Mid(strKey.GetLength());
	}
	else
	{
		CString strTripKey;
		long nPos = 0;

		strTripKey = _T("$") + strKey;
		nPos = strID.Find(strTripKey);

		if (nPos > 0)
		{
			strActID = strID.Left(nPos);
                        strActID.AppendFormat(_T("$%s"), g_pszTripTimeKey_Act.GetString());
			strActID += strID.Mid(nPos + strTripKey.GetLength());
		}
	}

	return strActID;
}

inline CString Gb_GetActKeyIDByTripKeyID(const CString &strID)
{
	CString strActID = Gb_GetActKeyIDByTripKeyID(strID, g_pszTripTimeKey_Trip);

	if (strActID.GetLength() > 0)
	{
		return strActID;
	}

	strActID = Gb_GetActKeyIDByTripKeyID(strID, g_pszTripValueKey_Trip);

	if (strActID.GetLength() > 0)
	{
		return strActID;
	}	

	strActID = Gb_GetActKeyIDByTripKeyID(strID, g_pszTripTimeKey_Trip2);

	if (strActID.GetLength() > 0)
	{
		return strActID;
	}

	return strActID;
}

//结果判断描述：合格、不合格的文本
extern CString g_strResultDescValueCorrect;			//= "合格";
extern CString g_strResultDescValueIncorrect;		//= "不合格";

//////////////////////////////////////////////////////////////////////////
//Macrotest sys-var 类型定义
static const CString g_strSets    =  _T("Sets");
static const CString g_strSysParas    =  _T("sysparas");
static const CString g_strMTResults    =  _T("results");
static const CString g_strMTFaultParas    = _T("fault-paras");
static const CString g_strSafetyDatas     = _T("SafetyDatas");

//CComcmd Type 类型定义
static const CString g_strReset		=_T("reset");
static const CString g_strwSysPara  = _T("sys-para");
static const CString g_strwTestPara  = _T("test-para");

static const CString g_strDeviceModelOptr_Write = _T("write");
static const CString g_strDeviceModelOptr_Read = _T("read");
static const CString g_strDeviceModelOptr_Register = _T("register");
static const CString g_strDeviceModelOptr_None = _T("none");

static const CString g_strGbCommCmdDataType_Value = _T("value");
static const CString g_strGbCommCmdDataType_Struct = _T("struct");

static const CString g_strDeviceModel_Sets = _T("sets");
static const CString g_strDeviceModel_Analogs = _T("analog");
static const CString g_strDeviceModel_SoftSwitchs = _T("softswitch");
static const CString g_strDeviceModel_BinaryOuts = _T("binaryout");
static const CString g_strDeviceModel_SysPara = _T("sys-para");
static const CString g_strDeviceModel_TestPara = _T("test-para");

static const CString g_strAnalogType_Analog = _T("analog");
static const CString g_strAnalogType_Error   = _T("error");

//shaolei 2023-8-15。测试过程中，需要动态往模板树中添加的项目。使用后注意RemoveAll
extern CExBaseList g_oListItemsInsertToTree;  //

//数据集相关定义
#define DSID_ALL_DVM     0XFF

#define DSID_dsParameter    0x0000
#define DSID_dsSetting    0x0001
#define DSID_dsEna    0x0002
#define DSID_dsAin    0x0003
#define DSID_dsDin    0x0004
#define DSID_dsRec    0x0005
#define DSID_dsTripInfo    0x0006
#define DSID_dsAlarm    0x0007
#define DSID_dsWarning    0x0008
#define DSID_dsSoe    0x0009
#define DSID_dsSV    0x000A
#define DSID_dsGOOSE    0x000B
#define DSID_dsDout    0x000C
#define DSID_dsAll    0x000D
#define DSID_dsOwnDef    0x000E
#define DSID_dsNone    0x000F
#define DSID_dsReport    0x0010
#define DSID_dsLog    0x0011
#define DSID_dsFile    0x0012
#define DSID_dsMatrix    0x0013
#define DSID_dsMaxCount    40

extern const CString g_strDataSetID[DSID_dsMaxCount];
extern const CString g_strDataSetIDKey[DSID_dsMaxCount];
extern const CString g_strDataSetName[DSID_dsMaxCount];

const CString& Gb_GetDataSetName(const CString &strIDKey);
const CString& Gb_GetDataSetID(const CString &strID);
const CString& Gb_GetDataSetKey(const CString &strID);
long Gb_GetDataSetKey(const CString &strID, CStringArray &astrKeys);
BOOL Gb_IsDataSetIDError(const CString &strID);


void Gb_AddResultJudgeKey(CValues *pValues,long nResult=0);
void Gb_AddResultJudgeKey(CShortDatas  *pDatas,long nResult=0);
void Gb_GetItemBaseObjects(CExBaseList *pSrcList, CExBaseList *pDestList);

//2023-8-15  等待项目全部插入项目树
void Gb_WaitItemsInsertTree();

//////////////////////////////////////////////////////////////////////////
//作业指导书相关文件定义
static const CString g_strGbFileFilter = _T("gbxml");
static const CString g_strGbFilePostfix = _T(".gbxml");
static const CString g_strGbFilePostfixDes = _T("测试模板文件");

static const CString g_strIecfgFileFilter = _T("iecfg");
static const CString g_strIecfgFilePostfix = _T(".iecfg");
static const CString g_strIecfgFilePostfixDes = _T("装置测试仪IEC61850配置文件");

static const CString g_strTGbFileFilter = _T("stxml");
static const CString g_strTGbFilePostfix = _T(".stxml");
static const CString g_strTGbFilePostfixDes = _T("测试子模板文件");

static const CString g_strGbDocFileFilter = _T("doc");
static const CString g_strGbDocFilePostfix = _T(".doc");
static const CString g_strGbDocFilePostfixDes = _T("报告模板文件");

//2021-1-14  shaolei  模板结构描述文件
static const CString g_strGbStruDscFileFilter = _T("dscxml");
static const CString g_strGbStruDscFilePostfix = _T(".dscxml");
static const CString g_strGbStruDscFilePostfixDes = _T("模板结构描述文件");

//2021-3-12  shaolei Visio文件 逻辑图
static const CString g_strGbVisioFileFilter = _T("vsdx");
static const CString g_strGbVisioFilePostfix = _T(".vsdx");
static const CString g_strGbVisioFilePostfixDes = _T("逻辑图文件");

//2020-6-2  LUA to XVM
static const CString GBSCRIPT_TYPE_LUA  = _T("LUA");
static const CString GBSCRIPT_TYPE_XVM  = _T("XVM");
#define  GBSCRIPT_TYPE_ID_LUA  0
#define  GBSCRIPT_TYPE_ID_XVM  1

static const CString GBSCRIPT_XVM_TASM_EXE = _T("gbtse");
static const CString g_strGbTemplateExeFileFilter = _T("gbexe");

// static const CString g_strReportTeplateFilter = _T("mpxml");
// static const CString g_strReportTemplatePostfix = _T(".mpxml");
// static const CString g_strReportTemplatePostfixDes = _T("模板映射文件");
inline CString Gb_GetGuideBookFileType(const CString &strFile)
{
	CString strFileType;
	long nPos = strFile.ReverseFind('.');
	strFileType = strFile.Mid(nPos+1);

	strFileType.MakeLower();

	return strFileType;
}

inline BOOL Gb_ValidateGuideBookFileType(const CString &strFileType)
{
	if (strFileType == g_strGbFileFilter)
	{
		return TRUE;
	}

	if (strFileType == g_strTGbFileFilter)
	{
		return TRUE;
	}

	return FALSE;
}

inline BOOL Gb_CheckGuideBookFileType(const CString &strFileType)
{
	if (strFileType == g_strGbFileFilter)
	{
		return TRUE;
	}

	if (strFileType == g_strTGbFileFilter)
	{
		return TRUE;
	}

	return FALSE;
}

inline void Gb_ValidateGuideBookFileType(CString &strFileType)
{
	if (Gb_CheckGuideBookFileType(strFileType))
	{
		return;
	}

	strFileType = g_strGbFileFilter;
}

inline CString Gb_GetGuideBookFileDes(const CString &strFileType)
{
	//lijunqing 2020-09008
	if (strFileType == g_strGbFileFilter || strFileType == g_strGbTemplateExeFileFilter)
	{
#ifndef NOT_USE_XLANGUAGE
		return g_sLangTxt_TestTemplateFile/*g_strGbFilePostfixDes*/;
#else
		return _T("测试模板文件");
#endif
	}

	if (strFileType == g_strTGbFileFilter)
	{
#ifndef NOT_USE_XLANGUAGE
		return g_sLangTxt_TestSubTemplateFile/*g_strTGbFilePostfixDes*/;
#else
		return _T("测试子模板文件");
#endif
	}

	if (strFileType == g_strGbDocFileFilter)
	{
#ifndef NOT_USE_XLANGUAGE
		return g_sLangTxt_ReportTemplateFile/*g_strGbDocFilePostfixDes*/;
#else
		return _T("报告模板文件");
#endif
	}

	return _T("");
}

CString Gb_GetOpenGuideBookFile(const CString &strGbFileType, CWnd *pParent);

//////////////////////////////////////////////////////////////////////////
//报告计算方式
static const CString g_strCalMode_None = _T("none");
static const CString g_strCalMode_Last = _T("last");
static const CString g_strCalMode_Average = _T("average");
static const CString g_strCalMode_Max = _T("max");
static const CString g_strCalMode_Min = _T("min");
static const CString g_strCalMode_ErrorMax = _T("maxerror");
static const CString g_strCalMode_StdError = _T("stderror");
static const CString g_strCalMode_OverWrite = _T("overwrite");

static const CString g_strCalMode_ErrorValueID = _T("AbsError");

#define TEST_CALMODE_NONE       0
#define TEST_CALMODE_LAST       1
#define TEST_CALMODE_AVERAGE    2
#define TEST_CALMODE_MAX        3
#define TEST_CALMODE_MIN        4
#define TEST_CALMODE_ERRORMAX   5
#define TEST_CALMODE_STDERROR   6
#define TEST_CALMODE_OVERWRITE  7

inline LONG Gb_GetReportCalMode(const CString &strMode)
{
	if (strMode == g_strCalMode_Average)
	{
		return TEST_CALMODE_AVERAGE;
	}
	else if (strMode == g_strCalMode_Max)
	{
		return TEST_CALMODE_MAX;
	}
	else if (strMode == g_strCalMode_Min)
	{
		return TEST_CALMODE_MIN;
	}
	else if (strMode == g_strCalMode_None)
	{
		return TEST_CALMODE_NONE;
	}
	else if (strMode == g_strCalMode_Last)
	{
		return TEST_CALMODE_LAST;
	}
	else if (strMode == g_strCalMode_ErrorMax)
	{
		return TEST_CALMODE_ERRORMAX;
	}
	else if (strMode == g_strCalMode_StdError)
	{
		return TEST_CALMODE_STDERROR;
	}
	else if (strMode == g_strCalMode_OverWrite)
	{
		return TEST_CALMODE_OVERWRITE;
	}

	return TEST_CALMODE_NONE;
}

inline const CString Gb_GetReportCalModeText(const CString &strMode)
{
	if (strMode == g_strCalMode_Average)
	{
#ifndef NOT_USE_XLANGUAGE
		return /*_T("平均值")*/g_sLangTxt_Average;
#else
		return _T("平均值");
#endif
	}
	else if (strMode == g_strCalMode_Max)
	{
#ifndef NOT_USE_XLANGUAGE
		return /*_T("最大值")*/g_sLangTxt_MaxValue;
#else
		return _T("最大值");
#endif
	}
	else if (strMode == g_strCalMode_Min)
	{
#ifndef NOT_USE_XLANGUAGE
		return /*_T("最小值")*/g_sLangTxt_MinValue;
#else
		return _T("最小值");
#endif
	}
	else if (strMode == g_strCalMode_None)
	{
#ifndef NOT_USE_XLANGUAGE
		return /*_T("无")*/g_sLangTxt_None;
#else
		return _T("无");
#endif
	}
	else if (strMode == g_strCalMode_Last)
	{
#ifndef NOT_USE_XLANGUAGE
		return /*_T("最后一个")*/g_sLangTxt_LastOne;
#else
		return _T("最后一个");
#endif
	}
	else if (strMode == g_strCalMode_ErrorMax)
	{
#ifndef NOT_USE_XLANGUAGE
		return /*_T("误差最大值")*/g_sLangTxt_ErrorMax;
#else
		return _T("误差最大值");
#endif
	}
	else if (strMode == g_strCalMode_StdError)
	{
#ifndef NOT_USE_XLANGUAGE
		return /*_T("标准差")*/g_sLangTxt_Standdeviation;
#else
		return _T("标准差");
#endif
	}
	else if (strMode == g_strCalMode_OverWrite)
	{
#ifndef NOT_USE_XLANGUAGE
		return /*_T("覆盖")*/g_sLangTxt_OverWrite;
#else
		return _T("覆盖");
#endif
	}
#ifndef NOT_USE_XLANGUAGE
	return  /*_T("无")*/g_sLangTxt_None;
#else
	return  _T("无");
#endif
}

inline void  Gb_GetWavePath(CString &strPath)
{
	strPath = _P_GetResourcePath();
	strPath += _T("wav\\");
}

static BOOL g_bInitCommCmdToAllDevice = TRUE;


//全局数据定义
static const CString g_strGbGlobalDatasID            = _T("GlobalDatas");
static const CString g_strGbDevForAuthority            = _T("Develop");

static const CString g_strGbGlobalData_TestBeginTime = _T("TestBeginTime");
static const CString g_strGbGlobalData_TestEndTime   = _T("TestEndTime");
static const CString g_strGbGlobalData_TestType      = _T("TestType");
static const CString g_strGbGlobalData_Tester        = _T("Tester");
static const CString g_strGbGlobalData_GuideBookFile = _T("GuideBookFile");
static const CString g_strGbGlobalData_DvmFile       = _T("DeviceFile");
static const CString g_strGbGlobalData_Protocol      = _T("Protocol");
static const CString g_strGbGlobalData_ProjectName   = _T("ProjectName");
static const CString g_strGbGlobalData_TaskName      = _T("TaskName");
static const CString g_strGbGlobalData_User          = _T("User");
static const CString g_strGbGlobalData_UserCop       = _T("UserCop");
static const CString g_strGbGlobalData_ReportSN       = _T("ReportSN");
static const CString g_strGbGlobalData_TestError       = _T("TestError");
static const CString g_strGbGlobalData_DeviceIndex       = _T("index_device");
static const CString g_strGbGlobalData_KeySN       = _T("KeySN");
static const CString g_strGbGlobalData_AuthoritySN       = _T("AuthoritySN");
static const CString g_strGbGlobalData_DevKey       = _T("DevKey");
static const CString g_strGbGlobalData_DvmNameIsStd       = _T("dvm_name_is_std");
static const CString g_strGbGlobalData_VmProgID       = _T("VmProgID");

//shaolei 20211018
static const CString g_strGbGlobalData_MainInspection    = _T("MainInspection");   //测试人员：主检
static const CString g_strGbGlobalData_Proofreader       = _T("Proofreader");    //测试人员：校对
static const CString g_strGbGlobalData_Checker           = _T("Checker");         //测试人员：校对
static const CString g_strGbGlobalData_InspectionBases   = _T("InspectionBases");   //检验依据或标准
//2019-10-30  定义修改定值的时候，是否判断最大最小值
static const CString g_strGbGlobalData_WSetsUseMinMax       = _T("WSetsUseMinMax");
//2021-11-12 shaolei
static const CString g_strGbExportDatasDefID            = _T("ExportDatasDef");  //GuideBook下导出数据的数据集定义
//2023-2-8  lijunqing 定值赋值给参数时，时间定值的比例系数
#define GbGlobalData_Time_Setting_Coef      _T("Time_Setting_Coef")


#define DSID_COMMCMDMCONFIG  _T("CommCmdManyConfig")
#define DSID_DEVICEATTR             _T("DeviceAttr")
#define DSID_TESTAPP                   _T("TestApp")
#define DSID_TESTAPP_DEF            _T("TestAppDef")
#define DSID_CommConfig_Serial     _T("CommConfig_Serial")
#define DSID_CommConfig_Mms      _T("CommConfig_Mms")
#define DSID_CommConfig_Net      _T("CommConfig_Net")
#define DATAID_DEVICEID              _T("DeviceID")
#define DATAID_LDEVICEID              _T("LdeviceID")
#define DSID_COMMCMDMCONFIG_AUTOSET  _T("CommCmdManyConfigAutoSet")
#define DSID_REPORT_SN_GEN  _T("Report_SN_Gen")
#define DSID_TASK_REPORT_SN_GEN  _T("Task_SN_Gen")

//2021-8-2  lijunqing 
#define DATAID_DEVICESN              _T("DeviceSN")
//2023-10-13  shaolei
#define DATAID_SAMPLESN              _T("SampleSN")
#define DATAID_TASKSN                _T("TaskSN")

//20180904  多份报告模板的定义
#define DSID_EXTEND_RPT_TEMPLATE_DEF         _T("ExtendRptDef")

//2023-5-6  lijunqing  适应充电桩自动测试系统，硬件资源的申请
#define ID_HD_RES         _T("hd_res")
//2023-10-23 shaolei   南瑞windows软件，要求填写到报告中的“技术要求”、“报告数据保留小数位数”可编辑
#define ID_ITEMS_TEC        _T("items-tec")
//2023-11-14 shaolei   南瑞windows软件，导出word报告时，遥测结果参数的ID要反向映射
#define ID_AIN_DATA_MAP_CFG       _T("AinDataMapCfg")
#define ID_AIN_RATIOS       _T("AinRatios")
//2023-12-6
#define ID_PARA_DevMeas    _T("DevMeas")  //装置采样信息，是一次值还是二次值。1|2
#define ID_PARA_PtPrimary    _T("PtPrimary")  //PT一次值
#define ID_PARA_PtSecondary    _T("PtSecondary")  //PT二次值
#define ID_PARA_CtPrimary    _T("CtPrimary")   //CT一次值
#define ID_PARA_CtSecondary    _T("CtSecondary")   //CT二次值

#define GB_FILE_DLG_HISTORY_FILE      _T("GbFileDlgHistory.xml")
#define GB_FILE_DLG_HISTORY_FILE_GBT  _T("GbtFileDlgHistory.xml")

//2020-5-19  lijq
#ifndef _PSX_QT_LINUX_
#define GB_USE_XFILEMNGRBASE
#endif


void Gb_SetGbModifiedFlag(CExBaseObject *pGbObj, BOOL bFlag = TRUE);
BOOL Gb_GetGbModifiedFlag(CExBaseObject *pGbObj);
//////////////////////////////////////////////////////////////////////////
//
extern CExBaseList *g_pListRetry;
extern CExBaseList *g_pListRepeat;
extern CExBaseList *g_pListTimeLong;

void Gb_GbDevGlobalDefine_Init();
BOOL Gb_GetDeviceSysparasTime(CExBaseObject *pGbObj, CExBaseList *pTimeList);


#define AtsRpcTestDef_bin_offset   _T("bin-offset")
#define AtsRpcTestDef_bout_offset   _T("bout-offset")
#define AtsRpcTestDef_udc_power    _T("udc-power")
#define AtsRpcTestDef_TestAppGroup _T("TestAppGroup")

static const CString g_strBinaryParaID_Boutputs = _T("Boutputs");
static const CString g_strBinaryParaID_BinputsResult = _T("BinputsResult");

static const CString g_strBinaryRsltID_BinputsResult = _T("BinputsResult");
static const CString g_strBinaryRsltID_BinRslt = _T("BinRslt");
static const CString g_strBinaryRsltID_SwitchGroup = _T("SwitchGroup");
static const CString g_strBinartRsltID_RefuseBinary = _T("RefuseBinary");  //拒动的开关量  shaolei2018.12.27
static const CString g_strBinartRsltID_UnWantedBinary = _T("UnWantedBinary");  //误动的开关量  shaolei2018.12.27
static const CString g_strBinartRsltName_RefuseBinary = _T("拒动开关量节点");
static const CString g_strBinartRsltName_UnWantedBinary = _T("误动开关量节点");
static const CString g_strBinaryRsltID_SwitchGroupAll = _T("SwitchGroupAll");
static const CString g_strBinaryRsltID_CheckGroup = _T("CheckGroup");

#define XRECORD_DRAW_PARA_WIDTH    _T("width")
#define XRECORD_DRAW_PARA_HEIGHT   _T("height")

//2019-1-28  是否为导出xml格式的报告
extern BOOL g_bGbExportXmlReportFile;
//2021-1-14  是否保存模板结构描述文件
extern BOOL g_bGbSaveGbStruDscFile; 
//2023-4-10  保存dscxml时，是否保存项目状态。
extern BOOL g_bGbSaveItemState_WhenSavedscxml;

//2019-3-18
#define GB_ScriptLibrary_Default_File _T("GbScriptLibrary.xml")

#define WM_SAVE_GUIDEBOOK_FILE  (WM_USER + 1425)

//2019-10-31  通讯命令测试不合格的处理模式
#define SkipModeWhenWSetsError_Item            _T("item")
#define SkipModeWhenWSetsError_ParentItems  _T("parent-items")
#define SkipModeWhenWSetsError_Stxml           _T("stxml")

#define ID_SkipModeWhenWSetsError_None            0
#define ID_SkipModeWhenWSetsError_Item            1
#define ID_SkipModeWhenWSetsError_ParentItems  2
#define ID_SkipModeWhenWSetsError_Stxml           3

inline long Get_ID_SkipModeWhenWSetsErro(const CString &strMode)
{
	if (SkipModeWhenWSetsError_Item == strMode)
	{
		return ID_SkipModeWhenWSetsError_Item;
	}

	if (SkipModeWhenWSetsError_ParentItems == strMode)
	{
		return ID_SkipModeWhenWSetsError_ParentItems;
	}

	if (SkipModeWhenWSetsError_Stxml == strMode)
	{
		return ID_SkipModeWhenWSetsError_Stxml;
	}

	return ID_SkipModeWhenWSetsError_None;
}

inline CString Get_Name_SkipModeWhenWSetsErro(long nMode)
{
	if (ID_SkipModeWhenWSetsError_Item == nMode)
	{
		return SkipModeWhenWSetsError_Item;
	}

	if (ID_SkipModeWhenWSetsError_ParentItems == nMode)
	{
		return SkipModeWhenWSetsError_ParentItems;
	}

	if (ID_SkipModeWhenWSetsError_Stxml == nMode)
	{
		return SkipModeWhenWSetsError_Stxml;
	}

	return _T("");
}

//2020-12-05  lijunqing  离线自动测试模式：测试过程自动执行，测试结果通过导入
//此模式下：测试过程不执行电气量测试结果判断脚本和通信命令测试结果判断脚本
//导入报告数据时，执行通信命令测试结果判断脚本
static const CString g_strAtsOfflineTestMode = _T("offline_test");

//2021-2-23  lijunqing  解决测试模板编辑和自动测试都使用了获取测试项目临时文件路径的功能
class CTestControlBaseInterface : public CExBaseList
{
public:
	CTestControlBaseInterface(){}
	virtual ~CTestControlBaseInterface()	{}

public:
	virtual CString GetItemTempPath() = 0;


};


//2022-3-28  lijunqing from Items.h
#define GBID_BeforeTest_ (_T("_BeforeTest_"))
#define GBID_AfterTest_  (_T("_AfterTest_") )

#define GBID_ItemPrefix_BeforeTest (_T("_BFT_"))
#define GBID_ItemPrefix_AfterTest  (_T("_AFT_"))

//空节点
#define  GBITEMS_NODETYPE_NONE       (_T("none"))
//一个基于子模板或者是智能生成的一个分类的节点
#define  GBITEMS_NODETYPE_ROOTNODE   (_T("rootnode"))
//模板智能生成和编辑部分，可以在此项目分类下面插入智能生成的模板模块
#define  GBITEMS_NODETYPE_ITEMS   (_T("items"))

//2026-6-18  lijunqing 为了资源申请部分项目的方便，测试完毕，立即从容器去掉当前项目
#define SYS_PARAID_CanRemoveItemTesteFinished   _T("remove_item_test_finished")

