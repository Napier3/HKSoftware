//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DataMngrGlobal.h

#pragma once

#include "../BaseClass/ExBaseList.h"

#define DTMCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define DTMCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define DTMCLASSID_CVALUE       (DTMCLASSID_BASECLASS + 0X00000000)
#define DTMCLASSID_CVALUES       (DTMCLASSID_EXLISTCLASS + 0X00000001)
#define DTMCLASSID_CVALUESMNGR       (DTMCLASSID_EXLISTCLASS + 0X00000002)
#define DTMCLASSID_CTAG       (DTMCLASSID_BASECLASS + 0X00000003)
#define DTMCLASSID_CTAGS       (DTMCLASSID_EXLISTCLASS + 0X00000004)
#define DTMCLASSID_CTAGSMNGR       (DTMCLASSID_EXLISTCLASS + 0X00000005)
#define DTMCLASSID_CSHORTDATA       (DTMCLASSID_BASECLASS + 0X00000006)
#define DTMCLASSID_CSHORTDATAS       (DTMCLASSID_EXLISTCLASS + 0X00000007)
#define DTMCLASSID_CSHORTDATASMNGR       (DTMCLASSID_EXLISTCLASS + 0X00000008)
#define DTMCLASSID_CLONGDATA       (DTMCLASSID_BASECLASS + 0X00000009)
#define DTMCLASSID_CLONGDATAS       (DTMCLASSID_EXLISTCLASS + 0X0000000A)
#define DTMCLASSID_CLONGDATASMNGR       (DTMCLASSID_EXLISTCLASS + 0X0000000B)
#define DTMCLASSID_CDATATYPEVALUE       (DTMCLASSID_BASECLASS + 0X0000000C)
#define DTMCLASSID_CDATATYPE       (DTMCLASSID_EXLISTCLASS + 0X0000000D)
#define DTMCLASSID_CDATATYPES       (DTMCLASSID_EXLISTCLASS + 0X0000000E)
#define DTMCLASSID_CDATAGROUP       (DTMCLASSID_EXLISTCLASS + 0X0000000F)


#define DVMCLASSID_BASECLASS       DTMCLASSID_BASECLASS
#define DVMCLASSID_EXLISTCLASS       DTMCLASSID_EXLISTCLASS

#define DVMCLASSID_CDVMVALUE       (DVMCLASSID_EXLISTCLASS + 0X00000010)
#define DVMCLASSID_CDVMDATA       (DVMCLASSID_EXLISTCLASS + 0X00000011)
#define DVMCLASSID_CDVMDATASET       (DVMCLASSID_EXLISTCLASS + 0X00000012)
#define DVMCLASSID_CDVMLOGICDEVICE       (DVMCLASSID_EXLISTCLASS + 0X00000013)
#define DVMCLASSID_CDVMDEVICE       (DVMCLASSID_EXLISTCLASS + 0X00000014)

//2014-10-20  数据集验证
#define DVMCLASSID_CDSVELEMENT       (DVMCLASSID_EXLISTCLASS + 0X00000015)
#define DVMCLASSID_CDSVSEQUENCE       (DVMCLASSID_EXLISTCLASS + 0X00000016)
#define DVMCLASSID_CDSVCHOICE       (DVMCLASSID_EXLISTCLASS + 0X00000017)
#define DVMCLASSID_CDSVBASE       (DVMCLASSID_EXLISTCLASS + 0X00000018)
#define DVMCLASSID_CDSVELEMATTR       (DVMCLASSID_BASECLASS + 0X00000019)
#define DVMCLASSID_CDSVSCRIPT       (DVMCLASSID_EXLISTCLASS + 0X0000001A)
#define DVMCLASSID_CDSVINDATASET       (DVMCLASSID_EXLISTCLASS + 0X0000001B)
#define DVMCLASSID_CDSVELIMINATES       (DVMCLASSID_EXLISTCLASS + 0X0000001C)
#define DVMCLASSID_CDSVELIMINATE       (DVMCLASSID_EXLISTCLASS + 0X0000001D)

#define DVMCLASSID_CDVMDEVICES       (DVMCLASSID_EXLISTCLASS + 0X0000001F)

#define DMPCLASSID_CDVMDATAMAP       (DVMCLASSID_EXLISTCLASS + 0X00000020)
#define DMPCLASSID_CDVMDATASETMAP       (DVMCLASSID_EXLISTCLASS + 0X00000021)
#define DMPCLASSID_CDVMDEVICEMAP       (DVMCLASSID_EXLISTCLASS + 0X00000022)
#define DMPCLASSID_CDVMVALUEMAP       (DVMCLASSID_EXLISTCLASS + 0X00000023)
#define DMPCLASSID_CDVMLDVICEMAP       (DVMCLASSID_EXLISTCLASS + 0X00000024)

#define DMPCLASSID_CDVMMAPTOOL       (DVMCLASSID_EXLISTCLASS + 0X00000025)

#define DTMCLASSID_CDATAMNGRFOLDER      (DVMCLASSID_EXLISTCLASS + 0X00000026)
#define DVMCLASSID_CDSVANYELEMENT       (DVMCLASSID_EXLISTCLASS + 0X00000027)

#define DVMCLASSID_CDVMBRCB            (DVMCLASSID_EXLISTCLASS + 0X00000028)
#define DVMCLASSID_CDVMBRCBVALUE       (DVMCLASSID_EXLISTCLASS + 0X00000029)

#define DVMCLASSID_CDVMLOGCTRL            (DVMCLASSID_EXLISTCLASS + 0X00000029)


#define DVMCLASSID_CRPTCTRL       (DVMCLASSID_BASECLASS + 0X0000002A)
#define DVMCLASSID_CRPTCTRLS       (DVMCLASSID_EXLISTCLASS + 0X0000002B)
#define DVMCLASSID_CLOGCTRL       (DVMCLASSID_BASECLASS + 0X0000002C)
#define DVMCLASSID_CLOGCTRLS       (DVMCLASSID_EXLISTCLASS + 0X0000002D)

#define DVMCLASSID_CDVMLOG       (DVMCLASSID_EXLISTCLASS + 0X0000002E)
#define DVMCLASSID_CDVMLOGS       (DVMCLASSID_EXLISTCLASS + 0X0000002F)
#define DVMCLASSID_CDSVAPPEARFORERR       (DVMCLASSID_EXLISTCLASS + 0X00000030)

//2021-10-9  LIJUNQING
#define DVMCLASSID_CDVMDATASETGROUP       (DVMCLASSID_EXLISTCLASS + 0X00000031)

//2023-0106 zhouhj
#define DTMCLASSID_CDVMVALUES       (DVMCLASSID_EXLISTCLASS + 0X00000032)

//20240621 huangliang 添加Maps
#define DTMCLASSID_CDATAMAPS       (DTMCLASSID_EXLISTCLASS + 0X00000033)
#define DTMCLASSID_CXDATAMAP       (DTMCLASSID_EXLISTCLASS + 0X00000034)

//数据模型之为数据结构体，CDvmValue，CValue都为结构体模式处理
#define DATAMNGR_VERSION_1_0         0X00010000

//Data对象增加时间属性
#define DATAMNGR_VERSION_1_1         0X00010001

//CDsvElemAttr对象增加关联变量属性
#define DATAMNGR_VERSION_1_2         0X00010002

//CDsvScript增加属性：m_nDsvType
#define DATAMNGR_VERSION_1_3         0X00010003

//CDvmData：保存m_nChange属性
#define DATAMNGR_VERSION_1_4         0X00010004

//CDvmData：增加m_strStep
#define DATAMNGR_VERSION_1_5         0X00010005

//CDvmDataset：增加属性的串行化
#define DATAMNGR_VERSION_1_6         0X00010006

//CDvmData：增加m_nIndex的串行化
#define DATAMNGR_VERSION_1_7         0X00010007

//增加 CDvmDatasetGroup
#define DATAMNGR_VERSION_1_8         0X00010008

//CDvmData 增加m_strDefaultValue
#define DATAMNGR_VERSION_1_9         0X00010009

//2024-10-16 zhouyangyong 移植李工处理优化打开慢的代码
#define DATAMNGR_VERSION_FF         0X0001FFFF
#define DATAMNGR_DATATYPE_ALLOCBUFFER 60

extern const DWORD g_dwDataMngrVersionID ;//  = 0X80000001;
extern const DWORD g_dwDataMngrCurrVersion ;//= DATAMNGR_VERSION_1_8;
extern const char* g_pszDataMngrVersionPrefix ;//= "DMVersion";


//数据类型定义  shaolei 2022-1-18
#define DATAMNGR_DATATYPE_LONG     _T("long")
#define DATAMNGR_DATATYPE_INT64     _T("__int64")
#define DATAMNGR_DATATYPE_INT      _T("int")
#define DATAMNGR_DATATYPE_NUMBER   _T("number")   //数值类型，当浮点数处理
#define DATAMNGR_DATATYPE_FLOAT    _T("float")
#define DATAMNGR_DATATYPE_DOUBLE   _T("double")
#define DATAMNGR_DATATYPE_STRING   _T("string")

//是否是基础数据类型。若不是，则认为是datatype文件中配置的数据类型
inline BOOL dsv_IsBaseDataType(const CString &strDataType)
{
	if (strDataType == DATAMNGR_DATATYPE_LONG)
	{
		return TRUE;
	}

	if (strDataType == DATAMNGR_DATATYPE_INT)
	{
		return TRUE;
	}

	if (strDataType == DATAMNGR_DATATYPE_NUMBER)
	{
		return TRUE;
	}

	if (strDataType == DATAMNGR_DATATYPE_STRING)
	{
		return TRUE;
	}

	if (strDataType == DATAMNGR_DATATYPE_FLOAT)
	{
		return TRUE;
	}

	if (strDataType == DATAMNGR_DATATYPE_DOUBLE)
	{
		return TRUE;
	}

	return FALSE;
}

inline void dvm_InitDvmVersion(CBinarySerialBuffer &oBuffer)
{
	char *pszPrefix = oBuffer.m_chPrefix;
	pszPrefix[0]='E';
	pszPrefix[1]='P';
	pszPrefix[2]='O';
	pszPrefix[3]='T';
	pszPrefix[4]='O';
	pszPrefix[5]='.';
	pszPrefix[6]='G';
	pszPrefix[7]='B';
	pszPrefix[8]=0;
	oBuffer.m_dwVersion = g_dwDataMngrCurrVersion;

	oBuffer.SetCharSet(CHAR_SET_ASCII);
}

class CDataMngrXmlRWKeys : public CXmlRWKeys
{
protected:
	CDataMngrXmlRWKeys();
	virtual ~CDataMngrXmlRWKeys();
	static long g_nDTMRef;

public:
	static CDataMngrXmlRWKeys* g_pXmlKeys;
	static CDataMngrXmlRWKeys* Create();
	static void Release();
	static void Release(CDataMngrXmlRWKeys *pDataMngrXmlRWKeys);
	static CDataMngrXmlRWKeys* CreateNew()
	{
		return new CDataMngrXmlRWKeys();
	}

	//lijq 2020-4-15  DataGroup的子对象data，是ShortData，还是DvmData
	long m_nIsGroupUseDvmData;

	//lijunqing 2020-10-23 保存xml文件时，只保存id和value
	long m_nXmlOnlyWrite_Id_Value;
    static void IncXmlOnlyWrite_Id_Value(CDataMngrXmlRWKeys *pXmlKeys=NULL, long nAdd=1);
    static void DecXmlOnlyWrite_Id_Value(CDataMngrXmlRWKeys *pXmlKeys=NULL, long nDec=1);

	//shaolei 2023-4-20  判断对象是否相等时，只判断id和value
	long m_nIsEqualOwn_Id_Value;
	static void IncIsEqualOwn_Id_Value(CDataMngrXmlRWKeys *pXmlKeys=NULL, long nAdd=1);
	static void DecIsEqualOwn_Id_Value(CDataMngrXmlRWKeys *pXmlKeys=NULL, long nDec=1);

	//lijunqing 2023-2-28  lijunqing 只读取主属性，针对data，不读取min、max、unit、step、time、change等
	long m_nXmlOnlyRead_MainAttr;
	static void IncXmlOnlyRead_MainAttr(CDataMngrXmlRWKeys *pXmlKeys=NULL, long nAdd=1);
	static void DecXmlOnlyRead_MainAttr(CDataMngrXmlRWKeys *pXmlKeys=NULL, long nDec=1);

public:
	BSTR m_strCDsvAppearForErrKey; //appear-for-err
	BSTR m_strCDvmLogControlKey; //log-ctrl
	BSTR m_strCDsvEliminateKey; //eliminate
	BSTR m_strCDsvInDatasetKey; //dataset
	BSTR m_strCDsvScriptKey; //script
	BSTR m_strCDsvElemAttrKey; //attr
	BSTR m_strCDsvChoiceKey; //choice
	BSTR m_strCDsvSequenceKey; //sequence
	BSTR m_strCDsvElementKey; //element
	BSTR m_strCDsvAnyElementKey; //any-element
	BSTR m_strCDvmDeviceKey; //device
	BSTR m_strCDvmDevicesKey; //devices
	BSTR m_strCDvmLogicDeviceKey; //ldevice
	BSTR m_strCDvmLogicDeviceMapKey; //ldevice
	BSTR m_strCDvmDatasetKey; //dataset
	BSTR m_strCDvmDatasetGroupKey; //dataset-group
	BSTR m_strCDvmDataKey; //data

	BSTR m_strCRptCtrlKey;//RptCtrl
	BSTR m_strCRptCtrlsKey;//RptCtrls

	BSTR m_strCLogCtrlKey;//LogCtrl
	BSTR m_strCLogCtrlsKey;//LogCtrls
	BSTR m_strCDvmLogKey;//Log
	BSTR m_strCDvmLogsKey;//Logs

	BSTR m_strCDatSetKey;//DatSet
	BSTR m_strCIntgPdKey;//IntgPd
	BSTR m_strCRptIDKey;//RptID
	BSTR m_strConfRevKey;//ConfRev
	BSTR m_strCBufferedKey;//Buffered
	BSTR m_strCBufTimeKey;//BufTime
	BSTR m_strCTrgOpsKey;//TrgOps
	BSTR m_strCOptFieldsKey;//OptFields
	BSTR m_strCRptEnabledKey;//RptEnabled


	BSTR m_strCLogNameKey;//LogName
	BSTR m_strCLogEnaKey;//LogEna
	BSTR m_strCReasonCodeKey;//ReasonCode

	BSTR m_strCDvmBrcbKey; //brcb
	BSTR m_strCDvmValueKey; //value
	BSTR m_strCDataGroupKey; //group
	BSTR m_strCDataTypesKey; //data-types
	BSTR m_strCDataTypeKey; //data-type
	BSTR m_strCDataTypeValueKey; //value
	BSTR m_strCLongDatasMngrKey; //data-mngr
	BSTR m_strCLongDatasKey; //datas
	BSTR m_strCLongDataKey; //data
	BSTR m_strCShortDatasMngrKey; //datas-mngr
	BSTR m_strCShortDatasKey; //datas
	BSTR m_strCShortDataKey; //data
	BSTR m_strFolderKey; //folder
	BSTR m_strCTagsMngrKey; //tags-mngr
	BSTR m_strCTagsKey; //tags
	BSTR m_strCTagKey; //tag
	BSTR m_strCValuesMngrKey; //values-mngr
	BSTR m_strCValuesKey; //values
	BSTR m_strCValueKey; //value
	BSTR m_strValueKey; //value
	BSTR m_strDefaultValueKey2; //default-value
	BSTR m_strDataTypeKey; //data-type
	BSTR m_strWriteModeKey; //write-mode
	BSTR m_strDataTypeIDKey; //data-type
	BSTR m_strUnitKey; //unit
	BSTR m_strFormatKey; //format
	BSTR m_strRemarkKey; //remark
	BSTR m_strDefaultValueKey; //def-val
	BSTR m_strReservedKey; //reserved
	BSTR m_strValueNameKey; //val-name
	BSTR m_strScriptKey; //script
	BSTR m_strMessageKey; //msg
	BSTR m_strTypeKey; //type
	BSTR m_strShowKey; //show
	BSTR m_strEnableKey; //enable
	BSTR m_strReserved2Key; //reserved2
	BSTR m_strIndexKey; //index
	BSTR m_strMinKey; //min
	BSTR m_strMaxKey; //max
	BSTR m_strChangeKey;  //change
	BSTR m_strStepKey;  //step
	BSTR m_strTextKey; //text
	BSTR m_strModeKey; //mode
	BSTR m_strOptionKey; //option
	BSTR m_strUnboundKey; //unbound
	BSTR m_strTimeKey; //unbound
	BSTR m_strOptrKey; //optr
	BSTR m_strValue2Key; //optr
	BSTR m_strMinOccKey; //minocc
	BSTR m_strMaxOccKey; //maxocc
	BSTR m_strInDatasetKey; //in-dataset
	BSTR m_strVariableKey; //variable
	BSTR m_strExprRcvKey;
	BSTR m_strExprSendKey;

	BSTR m_strCDvmDeviceMapKey; //device-map
	BSTR m_strCDvmLDeviceMapKey; //ldevice-map
	BSTR m_strCDvmDatasetMapKey; //dataset-map
	BSTR m_strCDvmDataMapKey; //data-map
	BSTR m_strMapNameKey; //map-name
	BSTR m_strMapIDKey; //map-id
	BSTR m_strCDvmValueMapKey; //value-map

	BSTR m_strDescKey;//desc
	BSTR m_strCmpWithIDKey; //cmp-with-id
	BSTR m_strDvmCmdDataNameFullKey; //cmp-name-full
	BSTR m_strDvmCmpToolConfigKey;
	BSTR m_strReportModeKey; //report-mode

	//2023.11.15 lichao PNS331 新增	
#ifdef _DVMDATASET_USE_ADDR_
	BSTR m_strAddrKey;
#endif

	//20240621 huangliang
	BSTR m_strCXDataMapKey; //datamap
	BSTR m_strCDataMapsKey; //datamaps
	BSTR m_strMap_IdKey;	//map_id


public:

	//2023.11.15 lichao PNS331 新增
#ifdef _DVMDATASET_USE_ADDR_
	static BSTR AddrKey()  {   return g_pXmlKeys->m_strAddrKey;  }
#endif

	static BSTR CDsvAppearForErrKey()  {   return g_pXmlKeys->m_strCDsvAppearForErrKey;  }
	static BSTR CDvmLogControlKey()  {   return g_pXmlKeys->m_strCDvmLogControlKey;  }
	static BSTR CDsvEliminateKey()  {   return g_pXmlKeys->m_strCDsvEliminateKey;  }
	static BSTR CDsvInDatasetKey()  {   return g_pXmlKeys->m_strCDsvInDatasetKey;  }
	static BSTR CDsvScriptKey()  {   return g_pXmlKeys->m_strCDsvScriptKey;  }
	static BSTR CDsvElemAttrKey()  {   return g_pXmlKeys->m_strCDsvElemAttrKey;  }
	static BSTR CDsvChoiceKey()  {   return g_pXmlKeys->m_strCDsvChoiceKey;  }
	static BSTR CDsvSequenceKey()  {   return g_pXmlKeys->m_strCDsvSequenceKey;  }
	static BSTR CDsvElementKey()  {   return g_pXmlKeys->m_strCDsvElementKey;  }
	static BSTR CDsvAnyElementKey()  {   return g_pXmlKeys->m_strCDsvAnyElementKey;  }
	static BSTR CDvmDevicesKey()  {   return g_pXmlKeys->m_strCDvmDevicesKey;  }
	static BSTR CDvmDeviceKey()  {   return g_pXmlKeys->m_strCDvmDeviceKey;  }
	static BSTR CDvmLogicDeviceKey()  {   return g_pXmlKeys->m_strCDvmLogicDeviceKey;  }
	static BSTR CDvmDatasetKey()  {   return g_pXmlKeys->m_strCDvmDatasetKey;  }
	static BSTR CDvmDatasetGroupKey()  {   return g_pXmlKeys->m_strCDvmDatasetGroupKey;  }
	static BSTR CDvmDataKey()  {   return g_pXmlKeys->m_strCDvmDataKey;  }

	static BSTR CRptCtrlKey()  {   return g_pXmlKeys->m_strCRptCtrlKey;  }
	static BSTR CRptCtrlsKey()  {   return g_pXmlKeys->m_strCRptCtrlsKey;  }

	static BSTR CLogCtrlKey()  {   return g_pXmlKeys->m_strCLogCtrlKey;  }
	static BSTR CLogCtrlsKey()  {   return g_pXmlKeys->m_strCLogCtrlsKey;  }
	static BSTR CDvmLogKey()  {   return g_pXmlKeys->m_strCDvmLogKey;  }
	static BSTR CDvmLogsKey()  {   return g_pXmlKeys->m_strCDvmLogsKey;  }

	static BSTR CDvmBrcbKey()  {   return g_pXmlKeys->m_strCDvmBrcbKey;  }
	static BSTR CDvmValueKey()  {   return g_pXmlKeys->m_strCDvmValueKey;  }
	static BSTR CDataGroupKey()  {   return g_pXmlKeys->m_strCDataGroupKey;  }
	static BSTR CDataTypesKey()  {   return g_pXmlKeys->m_strCDataTypesKey;  }
	static BSTR CDataTypeKey()  {   return g_pXmlKeys->m_strCDataTypeKey;  }
	static BSTR CDataTypeValueKey()  {   return g_pXmlKeys->m_strCDataTypeValueKey;  }
	static BSTR CLongDatasMngrKey()  {   return g_pXmlKeys->m_strCLongDatasMngrKey;  }
	static BSTR CLongDatasKey()  {   return g_pXmlKeys->m_strCLongDatasKey;  }
	static BSTR CLongDataKey()  {   return g_pXmlKeys->m_strCLongDataKey;  }
	static BSTR CShortDatasMngrKey()  {   return g_pXmlKeys->m_strCShortDatasMngrKey;  }
	static BSTR CShortDatasKey()  {   return g_pXmlKeys->m_strCShortDatasKey;  }
	static BSTR CShortDataKey()  {   return g_pXmlKeys->m_strCShortDataKey;  }
	static BSTR CDataMngrFolderKey()  {   return g_pXmlKeys->m_strFolderKey;  }
	static BSTR CTagsMngrKey()  {   return g_pXmlKeys->m_strCTagsMngrKey;  }
	static BSTR CTagsKey()  {   return g_pXmlKeys->m_strCTagsKey;  }
	static BSTR CTagKey()  {   return g_pXmlKeys->m_strCTagKey;  }
	static BSTR CValuesMngrKey()  {   return g_pXmlKeys->m_strCValuesMngrKey;  }
	static BSTR CValuesKey()  {   return g_pXmlKeys->m_strCValuesKey;  }
	static BSTR CValueKey()  {   return g_pXmlKeys->m_strCValueKey;  }
	static BSTR ValueKey()  {   return g_pXmlKeys->m_strValueKey;  }
	static BSTR DataTypeKey()  {   return g_pXmlKeys->m_strDataTypeKey;  }
	static BSTR DataTypeIDKey()  {   return g_pXmlKeys->m_strDataTypeIDKey;  }
	static BSTR UnitKey()  {   return g_pXmlKeys->m_strUnitKey;  }
	static BSTR FormatKey()  {   return g_pXmlKeys->m_strFormatKey;  }
	static BSTR ExprRcvKey()  {   return g_pXmlKeys->m_strExprRcvKey;  }
	static BSTR ExprSendKey()  {   return g_pXmlKeys->m_strExprSendKey;  }
	static BSTR RemarkKey()  {   return g_pXmlKeys->m_strRemarkKey;  }
	static BSTR DefaultValueKey()  {   return g_pXmlKeys->m_strDefaultValueKey;  }
	static BSTR ReservedKey()  {   return g_pXmlKeys->m_strReservedKey;  }
	static BSTR ValueNameKey()  {   return g_pXmlKeys->m_strValueNameKey;  }
	static BSTR ScriptKey()  {   return g_pXmlKeys->m_strScriptKey;  }
	static BSTR MessageKey()  {   return g_pXmlKeys->m_strMessageKey;  }
	static BSTR TypeKey()  {   return g_pXmlKeys->m_strTypeKey;  }
	static BSTR ShowKey()  {   return g_pXmlKeys->m_strShowKey;  }
	static BSTR EnableKey()  {   return g_pXmlKeys->m_strEnableKey;  }
	static BSTR Reserved2Key()  {   return g_pXmlKeys->m_strReserved2Key;  }
	static BSTR IndexKey()  {   return g_pXmlKeys->m_strIndexKey;  }
	static BSTR MinKey()  {   return g_pXmlKeys->m_strMinKey;  }
	static BSTR MaxKey()  {   return g_pXmlKeys->m_strMaxKey;  }
	static BSTR ChangeKey()  {   return g_pXmlKeys->m_strChangeKey;  }
	static BSTR StepKey()  {   return g_pXmlKeys->m_strStepKey;  }
	static BSTR TextKey()  {   return g_pXmlKeys->m_strTextKey;  }
	static BSTR ModeKey()  {   return g_pXmlKeys->m_strModeKey;  }
	static BSTR OptionKey()  {   return g_pXmlKeys->m_strOptionKey;  }
	static BSTR UnboundKey()  {   return g_pXmlKeys->m_strUnboundKey;  }
	static BSTR TimeKey()  {   return g_pXmlKeys->m_strTimeKey;  }
	static BSTR OptKrey()  {   return g_pXmlKeys->m_strOptrKey;  }
	static BSTR Value2Krey()  {   return g_pXmlKeys->m_strValue2Key;  }
	static BSTR MinOccKey()  {   return g_pXmlKeys->m_strMinOccKey;  }
	static BSTR MaxOccKey()  {   return g_pXmlKeys->m_strMaxOccKey;  }
	static BSTR InDatasetKey()  {   return g_pXmlKeys->m_strInDatasetKey;  }

	static BSTR CDvmDeviceMapKey()  {   return g_pXmlKeys->m_strCDvmDeviceMapKey;  }
	static BSTR CDvmLDeviceMapKey()  {   return g_pXmlKeys->m_strCDvmLDeviceMapKey;  }
	static BSTR CDvmDatasetMapKey()  {   return g_pXmlKeys->m_strCDvmDatasetMapKey;  }
	static BSTR CDvmDataMapKey()  {   return g_pXmlKeys->m_strCDvmDataMapKey;  }
	static BSTR CDvmValueMapKey()  {   return g_pXmlKeys->m_strCDvmValueMapKey;  }
	static BSTR MapNameKey()  {   return g_pXmlKeys->m_strMapNameKey;  }
	static BSTR MapIDKey()  {   return g_pXmlKeys->m_strMapIDKey;  }
	static BSTR ReportModeKey()  {   return g_pXmlKeys->m_strReportModeKey;  }
	
	//20240621 huangliang
	static BSTR CXDataMapKey()  {   return g_pXmlKeys->m_strCXDataMapKey;  }
	static BSTR CDataMapsKey()  {   return g_pXmlKeys->m_strCDataMapsKey;  }
	static BSTR MapIdKey()  {   return g_pXmlKeys->m_strMap_IdKey;  }

};



class CDataMngrConstGlobal
{
private:
	CDataMngrConstGlobal();
	virtual ~CDataMngrConstGlobal();

public:
	static CDataMngrConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CDataMngrConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};



static const CString g_strDataAttrID_Name = _T("name");
static const CString g_strDataAttrID_DataType = _T("data-type");
static const CString g_strDataAttrID_Enable = _T("enable");
static const CString g_strDataAttrID_Show = _T("show");
static const CString g_strDataAttrID_Unit= _T("unit");
static const CString g_strDataAttrID_Value = _T("value");

static const CString g_strDvmDataMapFilePostfix = _T("mapxml");

#ifndef _PSX_IDE_QT_
BOOL dvm_PopOpenDvmDlg(CString &strFile, CWnd *pParentWnd, const CString &strCaption);
#endif

BOOL dsv_IsElement(UINT nClassID);
BOOL dsv_IsElement(CExBaseObject *p);

BOOL dvm_IsValueEqual(const CString &strValue1, const CString &strValue2);
#ifndef _PSX_QT_LINUX_
BOOL dvm_IsValueEqual(BSTR strValue1, BSTR strValue2);
#endif

//lijunqing 2021-8-11  增加这两个全局函数，访问的时候方便
void dvm_IncGroupUseDvmData(CDataMngrXmlRWKeys *pXmlKeys=NULL);
void dvm_DecGroupUseDvmData(CDataMngrXmlRWKeys *pXmlKeys=NULL);

//2022-10-04  lijuniqng
/*
对于嵌套的value对象，在转为JSON格式的时候，需要做处理，如下：
"data": {
	"name": "通道2",    "id": "SV1_I1_Ia1",    "data-type": "Curr",
	"value": "1.000000",    "unit": "A",    "format": "0.000000",  [value属性改为val]
	"index": "0",    "time": "0",    "change": "1",
	"value": [
	{
		"name": "幅值",   "id": "SV1_I1_Ia1$mag",        "data-type": "FLOAT",
		"value": "0.00"  [value属性改为val]
	},
	{
		"name": "比差",   "id": "SV1_I1_Ia1$RatError",     "data-type": "FLOAT",
		"value": "0.00",  [value属性改为val]
		"value": [
		{
			"name": "标准值",  "id": "SV1_I1_Ia1$RatError$StdValue",
			"data-type": "FLOAT",            "value": "100.1234"  [value属性改为val]
}, 
*/
long dvm_get_json_ascii(CDataMngrXmlRWKeys *pXmlKeys, CExBaseObject *pDvmObj, char **ppszBuffer, long nOffset, bool bOnlyId_Value);
long dvm_get_json_utf8(CDataMngrXmlRWKeys *pXmlKeys, CExBaseObject *pDvmObj, char **ppszBuffer, long nOffset, bool bOnlyId_Value);

//lijunqing 2024-9-10
BOOL dvm_OpenBinaryFile(CExBaseObject *pDvmObj, const CString &strFile, bool bOnlyRead_MainAttr);
BOOL dvm_SaveBinaryFile(CExBaseObject *pDvmObj, const CString &strFile, bool bOnlyRead_MainAttr);