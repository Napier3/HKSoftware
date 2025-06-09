//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MmsEngineConfigGlobal.h

#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"

#define MSCFGCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define MSCFGCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define MSCFGCLASSID_CMMSENGINECONFIG       (MSCFGCLASSID_EXLISTCLASS + 0X00000000)
#define MSCFGCLASSID_CMMSENGINEDATASETS       (MSCFGCLASSID_BASECLASS + 0X00000001)
#define MSCFGCLASSID_CMMSENGINEDSCFG       (MSCFGCLASSID_BASECLASS + 0X00000002)
#define MSCFGCLASSID_CMMSENGINELOCALIPS      (MSCFGCLASSID_BASECLASS + 0X00000003)
#define MSCFGCLASSID_CMMSENGINEIPCFG       (MSCFGCLASSID_BASECLASS + 0X00000004)

class CMmsEngineConfigXmlRWKeys : public CXmlRWKeys
{
protected:
	CMmsEngineConfigXmlRWKeys();
	virtual ~CMmsEngineConfigXmlRWKeys();
	static long g_nMSCFGRef;

public:
	static CMmsEngineConfigXmlRWKeys* g_pXmlKeys;
	static CMmsEngineConfigXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCMmsEngineDsCfgKey; //ds

	BSTR m_strCMmsDatasetsKey; //datasets
	BSTR m_strCMmslocalipsKey; //localips
	BSTR m_strCMmsIPCfgKey; //ip

	BSTR m_strCMmsEngineConfigKey; //mms-engine-config
	BSTR m_strKeyKey; //Key
	BSTR m_strReadKey; //read
	BSTR m_strMmsKeyConfigKey;//mms-key-config
	BSTR m_str_TrgOps_Key;
	BSTR m_str_OptFlds_Key;
	BSTR m_strCanWriteActiveSGKey;
	BSTR m_strWriteCtrlCheckModeKey;
	BSTR m_strWriteDataAfterWaitKey;
	BSTR m_strWriteDataAfterWaitAfterSelKey;
	BSTR m_str_OptFlds_BR_Key;
	BSTR m_str_OptFlds_RP_Key;
	BSTR m_str_TrgOps_UI_Key;
	BSTR m_strMmsReadUseReportKey;
	BSTR m_strMmsResetOnlyClearReportKey;
	BSTR m_strDebugModeKey;
	BSTR m_strUseDsDoutKey;
	BSTR m_strAutoGenModelDatasKey;
	BSTR m_strEnumLDAfterReadXmlKey;
	BSTR m_strMmsEnumLogCtrKey;
	BSTR m_strExitAppForExceptionKey;
	BSTR m_strUseDvmMapFileKey;
	BSTR m_strSwitchSGWaitKey;
	BSTR m_strMaxReportCountKey;
	BSTR m_strMultDevModelKey;
	BSTR m_strExportModelAutoKey;

	BSTR m_strDevNumKey;//dev-num
	BSTR m_strMultiDevModelKey;//multi-dev-model
	BSTR m_strAutoSetIpKey;//auto-set-ip
	BSTR m_strConnNumKey;//conn-num
	BSTR m_strDevCheckKey;//dev-check
	BSTR m_strUseEntryIDUpdateKey;//use-entryid-update
	BSTR m_strIntgPdKey;//IntgPd


public:
	static BSTR CMmsEngineDsCfgKey()  {   return g_pXmlKeys->m_strCMmsEngineDsCfgKey;  }

	static BSTR CMmsDatasetsKey()  {   return g_pXmlKeys->m_strCMmsDatasetsKey;  }
	static BSTR CMmslocalipsKey()  {   return g_pXmlKeys->m_strCMmslocalipsKey;  }
	static BSTR CMmsIPCfgKey()  {   return g_pXmlKeys->m_strCMmsIPCfgKey;  }

	static BSTR CMmsEngineConfigKey()  {   return g_pXmlKeys->m_strCMmsEngineConfigKey;  }
	static BSTR KeyKey()  {   return g_pXmlKeys->m_strKeyKey;  }
	static BSTR ReadKey()  {   return g_pXmlKeys->m_strReadKey;  }
};



class CMmsEngineConfigConstGlobal
{
private:
	CMmsEngineConfigConstGlobal();
	virtual ~CMmsEngineConfigConstGlobal();

public:
	static CMmsEngineConfigConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CMmsEngineConfigConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
