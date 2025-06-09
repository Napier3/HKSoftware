//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttSystemConfigGlobal.h

#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"

#define MngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define MngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define MNGRCLASSID_CSTTSYSTEMCONFIG       (MngrCLASSID_EXLISTCLASS + 0X00000000)
#define MNGRCLASSID_CSTTDEVCONFIG       (MngrCLASSID_BASECLASS + 0X00000001)
#define MNGRCLASSID_CSTTMODULEUSE       (MngrCLASSID_EXLISTCLASS + 0X00000002)
#define MNGRCLASSID_CSTTMODULE       (MngrCLASSID_BASECLASS + 0X00000003)

class CSttSystemConfigXmlRWKeys : public CXmlRWKeys
{
protected:
	CSttSystemConfigXmlRWKeys();
	virtual ~CSttSystemConfigXmlRWKeys();
	static long g_nMngrRef;

public:
	static CSttSystemConfigXmlRWKeys* g_pXmlKeys;
	static CSttSystemConfigXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCSttModuleKey; //module
	BSTR m_strCSttModuleUseKey; //module-use
	BSTR m_strCSttDevConfigKey; //dev-config
	BSTR m_strCSttSystemConfigKey; //system-config
	BSTR m_strOpen_Delay_TimeKey; //open-delay-time
	BSTR m_strCompany_NameKey; //company-name
	BSTR m_strInternationalModeKey; //international-mode
	BSTR m_strCur_Sel_ModelKey; //cur-sel-model
	BSTR m_strSel_OfflineKey; //sel-offline
	BSTR m_strSel_SOE_TestKey; //sel-SOE-test
	BSTR m_strSel_Steady_OutputKey; //sel-steady-output
	BSTR m_strSet_PasswordKey; //set-password
	BSTR m_strOverload_DelayKey; //overload-delay
	BSTR m_strDouble_Click_EditKey; //double-click-edit
	BSTR m_strAux_IpKey; //aux-ip
	BSTR m_strLast_Folder_PathKey; //last-folder-path  20230307 zhangyq
	BSTR m_strMulti_Exp_ListKey; //multi-exp-list
	BSTR m_strUse_Scl_ViewKey; //use-scl-view
	BSTR m_strLog_PrintKey; //log_print
	BSTR m_strFt3_Prim_Code_ValueKey ;//ft3-prim-code-value  20240416chenling
	BSTR m_strLock_MapsKey;//Lock_Maps 20240507wangtao
	BSTR m_strSel_Sys_Pata;


public:
	static BSTR CSttModuleKey()  {   return g_pXmlKeys->m_strCSttModuleKey;  }
	static BSTR CSttModuleUseKey()  {   return g_pXmlKeys->m_strCSttModuleUseKey;  }
	static BSTR CSttDevConfigKey()  {   return g_pXmlKeys->m_strCSttDevConfigKey;  }
	static BSTR CSttSystemConfigKey()  {   return g_pXmlKeys->m_strCSttSystemConfigKey;  }
	static BSTR Open_Delay_TimeKey()  {   return g_pXmlKeys->m_strOpen_Delay_TimeKey;  }
	static BSTR Company_NameKey()  {   return g_pXmlKeys->m_strCompany_NameKey;  }
	static BSTR InternationalModeKey()  {   return g_pXmlKeys->m_strInternationalModeKey;  }
	static BSTR Cur_Sel_ModelKey()  {   return g_pXmlKeys->m_strCur_Sel_ModelKey;  }
	static BSTR Sel_OfflineKey()  {   return g_pXmlKeys->m_strSel_OfflineKey;  }
	static BSTR Sel_SOE_TestKey()  {   return g_pXmlKeys->m_strSel_SOE_TestKey;  }
	static BSTR Sel_Steady_OutputKey()  {   return g_pXmlKeys->m_strSel_Steady_OutputKey;  }
	static BSTR Set_PasswordKey()  {   return g_pXmlKeys->m_strSet_PasswordKey;  }
	static BSTR Overload_DelayKey()  {   return g_pXmlKeys->m_strOverload_DelayKey;  }
	static BSTR Double_Click_EditKey()  {   return g_pXmlKeys->m_strDouble_Click_EditKey;  }
	static BSTR Aux_IpKey()  {   return g_pXmlKeys->m_strAux_IpKey;  }
	static BSTR Last_Folder_PathKey()  {return g_pXmlKeys->m_strLast_Folder_PathKey; }
	static BSTR Multi_Exp_ListKey()  {   return g_pXmlKeys->m_strMulti_Exp_ListKey;  }
	static BSTR Use_Scl_ViewKey()  {   return g_pXmlKeys->m_strUse_Scl_ViewKey;  }
	static BSTR Log_PrintKey()  {   return g_pXmlKeys->m_strLog_PrintKey;  }
	static BSTR Ft3_Prim_Code_ValueKey()  {   return g_pXmlKeys->m_strFt3_Prim_Code_ValueKey;  }
	static BSTR Lock_MapsKey()  {   return g_pXmlKeys->m_strLock_MapsKey;  }
	static BSTR Sel_Sys_Pata() {   return g_pXmlKeys->m_strSel_Sys_Pata;  }

};



class CSttSystemConfigConstGlobal
{
private:
	CSttSystemConfigConstGlobal();
	virtual ~CSttSystemConfigConstGlobal();

public:
	static CSttSystemConfigConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CSttSystemConfigConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
