//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SetFileXmlParseGlobal.h

#pragma once

#include "../../../../../Module/BaseClass/ExBaseList.h"

#define MngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define MngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define MNGRCLASSID_CSETFILESXML_DSC       (MngrCLASSID_EXLISTCLASS + 0X00000000)
#define MNGRCLASSID_CSETSFILEXML_HEADER       (MngrCLASSID_BASECLASS + 0X00000001)
#define MNGRCLASSID_CSETSFILEXML_HASHINFO       (MngrCLASSID_EXLISTCLASS + 0X00000002)
#define MNGRCLASSID_CSETSFILEXML_DEVINFO       (MngrCLASSID_EXLISTCLASS + 0X00000003)
#define MNGRCLASSID_CSETSFILEXML_DI       (MngrCLASSID_BASECLASS + 0X00000004)
#define MNGRCLASSID_CSETSFILEXML_HI       (MngrCLASSID_BASECLASS + 0X00000005)
#define MNGRCLASSID_CSETSFILEXML_FILEINFO       (MngrCLASSID_EXLISTCLASS + 0X00000006)
#define MNGRCLASSID_CSETSFILEXML_FI       (MngrCLASSID_BASECLASS + 0X00000007)
#define MNGRCLASSID_CSETSFILEXML_SETTINGS       (MngrCLASSID_EXLISTCLASS + 0X00000008)
#define MNGRCLASSID_CSETSFILEXML_INFOGRP       (MngrCLASSID_EXLISTCLASS + 0X00000009)
#define MNGRCLASSID_CSETSFILEXML_REMARK       (MngrCLASSID_EXLISTCLASS + 0X0000000A)
#define MNGRCLASSID_CSETSFILEXML_SI       (MngrCLASSID_EXLISTCLASS + 0X0000000B)
#define MNGRCLASSID_CSETSFILEXML_VAL       (MngrCLASSID_BASECLASS + 0X0000000C)
#define MNGRCLASSID_CSETSFILEXML_RI       (MngrCLASSID_BASECLASS + 0X0000000D)


//2024-11-15 yuanting 
#define MNGRCLASSID_CSETSFILEXML_UPDATE       (MngrCLASSID_EXLISTCLASS + 0X0000000E)
#define MNGRCLASSID_CSETSFILEXML_UI       (MngrCLASSID_BASECLASS + 0X0000000F)

#define SETTING_DESC_ZONE   _T("定值区号")

#define SETTING_CLASS_PARAMETER   _T("dsParameter")
#define SETTING_CLASS_VTCPARAMETER   _T("dsVtcParameter")
#define SETTING_CLASS_SETTING     _T("dsSetting")
#define SETTING_CLASS_RELAYENA    _T("dsRelayEna")
#define SETTING_CLASS_CTRL        _T("dsCtrl")
#define SETTING_CLASS_MATRIX      _T("dsMatrix")


class CSetFileXmlParseXmlRWKeys : public CXmlRWKeys
{
protected:
	CSetFileXmlParseXmlRWKeys();
	virtual ~CSetFileXmlParseXmlRWKeys();
	static long g_nMngrRef;

public:
	static CSetFileXmlParseXmlRWKeys* g_pXmlKeys;
	static CSetFileXmlParseXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCSetsFileXml_RIKey; //RI
	BSTR m_strCSetsFileXml_ValKey; //Val
	BSTR m_strCSetsFileXml_SIKey; //SI
	BSTR m_strCSetsFileXml_RemarkKey; //Remark
	BSTR m_strCSetsFileXml_InfoGrpKey; //InfoGrp
	BSTR m_strCSetsFileXml_SettingsKey; //Settings
	BSTR m_strCSetsFileXml_FIKey; //FI
	BSTR m_strCSetsFileXml_FileInfoKey; //FileInfo
	BSTR m_strCSetsFileXml_HIKey; //HI
	BSTR m_strCSetsFileXml_DIKey; //DI
	BSTR m_strCSetsFileXml_DevInfoKey; //DevInfo
	BSTR m_strCSetsFileXml_HashInfoKey; //HashInfo
	BSTR m_strCSetsFileXml_HeaderKey; //Header
	BSTR m_strCSetFilesXml_DSCKey; //DSC
	BSTR m_strConfigVersionKey; //configVersion
	BSTR m_strDevTypeKey; //devType
	BSTR m_strDevIdKey; //devId
	BSTR m_strIedNameKey; //iedName
	BSTR m_strUpdateTimeKey; //updateTime
	BSTR m_strItemNumKey; //itemNum
	BSTR m_strDescKey; //desc
	BSTR m_strKey; //
	BSTR m_strClassKey; //class
	BSTR m_strMd5Key; //md5
	BSTR m_strLdKey; //ld
	BSTR m_strInfoGrpNumKey; //infoGrpNum
	BSTR m_strGrpKey; //grp
	BSTR m_strSetGrpNumKey; //setGrpNum
	BSTR m_strRemoteKey; //remote
	BSTR m_strTypeKey; //type
	BSTR m_strUnitKey; //unit
	BSTR m_strMinKey; //min
	BSTR m_strMaxKey; //max
	BSTR m_strStepKey; //step
	BSTR m_strRefKey; //ref
	BSTR m_strupDateKey; //upDate

	//2024-11-15 yuanting
	BSTR m_strUpdateKey; //Update
	BSTR m_strCSetsFileXml_UIKey; //UI

	BSTR m_strFileKey; //file
public:
	static BSTR CSetsFileXml_RIKey()  {   return g_pXmlKeys->m_strCSetsFileXml_RIKey;  }
	static BSTR CSetsFileXml_ValKey()  {   return g_pXmlKeys->m_strCSetsFileXml_ValKey;  }
	static BSTR CSetsFileXml_SIKey()  {   return g_pXmlKeys->m_strCSetsFileXml_SIKey;  }
	static BSTR CSetsFileXml_RemarkKey()  {   return g_pXmlKeys->m_strCSetsFileXml_RemarkKey;  }
	static BSTR CSetsFileXml_InfoGrpKey()  {   return g_pXmlKeys->m_strCSetsFileXml_InfoGrpKey;  }
	static BSTR CSetsFileXml_SettingsKey()  {   return g_pXmlKeys->m_strCSetsFileXml_SettingsKey;  }
	static BSTR CSetsFileXml_FIKey()  {   return g_pXmlKeys->m_strCSetsFileXml_FIKey;  }
	static BSTR CSetsFileXml_FileInfoKey()  {   return g_pXmlKeys->m_strCSetsFileXml_FileInfoKey;  }
	static BSTR CSetsFileXml_HIKey()  {   return g_pXmlKeys->m_strCSetsFileXml_HIKey;  }
	static BSTR CSetsFileXml_DIKey()  {   return g_pXmlKeys->m_strCSetsFileXml_DIKey;  }
	static BSTR CSetsFileXml_DevInfoKey()  {   return g_pXmlKeys->m_strCSetsFileXml_DevInfoKey;  }
	static BSTR CSetsFileXml_HashInfoKey()  {   return g_pXmlKeys->m_strCSetsFileXml_HashInfoKey;  }
	static BSTR CSetsFileXml_HeaderKey()  {   return g_pXmlKeys->m_strCSetsFileXml_HeaderKey;  }
	static BSTR CSetFilesXml_DSCKey()  {   return g_pXmlKeys->m_strCSetFilesXml_DSCKey;  }
	static BSTR ConfigVersionKey()  {   return g_pXmlKeys->m_strConfigVersionKey;  }
	static BSTR DevTypeKey()  {   return g_pXmlKeys->m_strDevTypeKey;  }
	static BSTR DevIdKey()  {   return g_pXmlKeys->m_strDevIdKey;  }
	static BSTR IedNameKey()  {   return g_pXmlKeys->m_strIedNameKey;  }
	static BSTR UpdateTimeKey()  {   return g_pXmlKeys->m_strUpdateTimeKey;  }
	static BSTR ItemNumKey()  {   return g_pXmlKeys->m_strItemNumKey;  }
	static BSTR DescKey()  {   return g_pXmlKeys->m_strDescKey;  }
	static BSTR Key()  {   return g_pXmlKeys->m_strKey;  }
	static BSTR ClassKey()  {   return g_pXmlKeys->m_strClassKey;  }
	static BSTR Md5Key()  {   return g_pXmlKeys->m_strMd5Key;  }
	static BSTR LdKey()  {   return g_pXmlKeys->m_strLdKey;  }
	static BSTR InfoGrpNumKey()  {   return g_pXmlKeys->m_strInfoGrpNumKey;  }
	static BSTR GrpKey()  {   return g_pXmlKeys->m_strGrpKey;  }
	static BSTR SetGrpNumKey()  {   return g_pXmlKeys->m_strSetGrpNumKey;  }
	static BSTR RemoteKey()  {   return g_pXmlKeys->m_strRemoteKey;  }
	static BSTR TypeKey()  {   return g_pXmlKeys->m_strTypeKey;  }
	static BSTR UnitKey()  {   return g_pXmlKeys->m_strUnitKey;  }
	static BSTR MinKey()  {   return g_pXmlKeys->m_strMinKey;  }
	static BSTR MaxKey()  {   return g_pXmlKeys->m_strMaxKey;  }
	static BSTR StepKey()  {   return g_pXmlKeys->m_strStepKey;  }
	static BSTR RefKey()  {   return g_pXmlKeys->m_strRefKey;  }

	//2024-12-11 yuanting 缺少一个Remark中的属性 upDate
	static BSTR UpdateKey()  {   return g_pXmlKeys->m_strupDateKey;  }

	////2024-11-15 yuanting
	static BSTR CSetsFileXml_UpdateKey()  {   return g_pXmlKeys->m_strUpdateKey;  }
	static BSTR CSetsFileXml_UIKey()  {   return g_pXmlKeys->m_strCSetsFileXml_UIKey;  }

};



class CSetFileXmlParseConstGlobal
{
private:
	CSetFileXmlParseConstGlobal();
	virtual ~CSetFileXmlParseConstGlobal();

public:
	static CSetFileXmlParseConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CSetFileXmlParseConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};

CString RemoveOffsetChars(const CString& strInput);  //去除空格、制表符、换行、回车
void Char_to_WChart(char *pSrc, wchar_t **ppDest);//char转换为wchar。仅适用于不含中文
char* removeSpacesNewlinesTabs(char* str);
void RemoveTrailingCRLF(CString &strText); //去掉最末尾的\r\n

#define XST_PARAID_DsFile   _T("DsFile")
#define XST_PARAID_SetsFile   _T("SetsFile")
#define XST_PARAID_SetsFileUp   _T("SetsFileUp")
#define XST_PARAID_SetsFileDown   _T("SetsFileDown")
#define XST_PARAID_Path   _T("Path")
#define XST_PARAID_Grp   _T("Grp")
#define XST_PARAID_DeviceSN  _T("DeviceSN")
#define XST_PARAID_DvmFile   _T("DvmFile")
//2024-12-16 yuanting
#define XST_PARAID_DeviceModel   _T("DeviceModel")
#define XST_PARAID_EditMode   _T("EditMode")