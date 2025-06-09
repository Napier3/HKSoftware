//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ClassProcotolProjectGlobal.h

#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"

#include "../Engine/DeviceModel/DeviceModelXmlKeys.h"


#define POCLASSID_BASECLASS         (CLASSID_BASECLASS    + 0X01110000)
#define POCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X01110000)

#define POCLASSID_CPPPROJECTCONFIG       (POCLASSID_EXLISTCLASS + 0X00000000)
#define POCLASSID_CPPCFGDEVICES       (POCLASSID_EXLISTCLASS + 0X00000001)
#define POCLASSID_CPPCFGOPTRSMNGR       (POCLASSID_EXLISTCLASS + 0X00000002)
#define POCLASSID_CPPCFGDEVICE       (POCLASSID_EXLISTCLASS + 0X00000003)
#define POCLASSID_CPPCFGOPTRS       (POCLASSID_EXLISTCLASS + 0X00000004)
#define POCLASSID_CPPCFGOPTR       (POCLASSID_EXLISTCLASS + 0X00000005)
#define POCLASSID_CPPCFGOPTRBATCHVAR       (POCLASSID_BASECLASS + 0X00000006)
#define POCLASSID_CPPCFGOPTRBATCH       (POCLASSID_EXLISTCLASS + 0X00000007)
#define POCLASSID_CPPCFGOPTRDEVICE       (POCLASSID_EXLISTCLASS + 0X00000008)

class CClassProcotolProjectXmlRWKeys : public CDeviceModelXmlKeys //CXmlRWKeys
{
protected:
	CClassProcotolProjectXmlRWKeys();
	virtual ~CClassProcotolProjectXmlRWKeys();
	static long g_nPPRef;

public:
	static CClassProcotolProjectXmlRWKeys* g_pXmlKeys;
	static CClassProcotolProjectXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCPpCfgOptrDeviceKey; //device-optr
	BSTR m_strCPpCfgOptrBatchKey; //batch-config
	BSTR m_strCPpCfgOptrBatchVarKey; //batch-var
	BSTR m_strCPpCfgOptrKey; //optr
	BSTR m_strCPpCfgOptrsKey; //optrs
	BSTR m_strCPpCfgDeviceKey; //device
	BSTR m_strCPpCfgOptrsMngrKey; //optrs-mngr
	BSTR m_strCPpCfgDevicesKey; //devices
	BSTR m_strCPpProjectConfigKey; //protocol-project
	BSTR m_strTemplateFileKey; //template-file
	BSTR m_strDdvmFileKey; //ddvm-file
	BSTR m_strTDelayKey; //t-delay
	BSTR m_strRunProcedureKey; //run-procedure
	BSTR m_strPachageIDKey; //run-procedure
	BSTR m_strIsRunningKey; //is-running
	BSTR m_strProcedureKey;    //procedure
	BSTR m_strStepValKey; //step-val
	BSTR m_strStepCountKey; //step-count

public:
	static BSTR CPpCfgOptrDeviceKey()  {   return g_pXmlKeys->m_strCPpCfgOptrDeviceKey;  }
	static BSTR CPpCfgOptrBatchKey()  {   return g_pXmlKeys->m_strCPpCfgOptrBatchKey;  }
	static BSTR CPpCfgOptrBatchVarKey()  {   return g_pXmlKeys->m_strCPpCfgOptrBatchVarKey;  }
	static BSTR CPpCfgOptrKey()  {   return g_pXmlKeys->m_strCPpCfgOptrKey;  }
	static BSTR CPpCfgOptrsKey()  {   return g_pXmlKeys->m_strCPpCfgOptrsKey;  }
	static BSTR CPpCfgDeviceKey()  {   return g_pXmlKeys->m_strCPpCfgDeviceKey;  }
	static BSTR CPpCfgOptrsMngrKey()  {   return g_pXmlKeys->m_strCPpCfgOptrsMngrKey;  }
	static BSTR CPpCfgDevicesKey()  {   return g_pXmlKeys->m_strCPpCfgDevicesKey;  }
	static BSTR CPpProjectConfigKey()  {   return g_pXmlKeys->m_strCPpProjectConfigKey;  }
	static BSTR TemplateFileKey()  {   return g_pXmlKeys->m_strTemplateFileKey;  }
	static BSTR DdvmFileKey()  {   return g_pXmlKeys->m_strDdvmFileKey;  }
	static BSTR TDelayKey()  {   return g_pXmlKeys->m_strTDelayKey;  }
	static BSTR RunProcedureKey()  {   return g_pXmlKeys->m_strRunProcedureKey;  }
	static BSTR PachageIDKey()  {   return g_pXmlKeys->m_strPachageIDKey;  }
	static BSTR ProcedureKey()  {   return g_pXmlKeys->m_strProcedureKey;  }
	static BSTR StepValKey()  {   return g_pXmlKeys->m_strStepValKey;  }
	static BSTR StepCountKey()  {   return g_pXmlKeys->m_strStepCountKey;  }
};



class CClassProcotolProjectConstGlobal
{
private:
	CClassProcotolProjectConstGlobal();
	virtual ~CClassProcotolProjectConstGlobal();

public:
	static CClassProcotolProjectConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CClassProcotolProjectConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};

//规约工程文件
static const CString g_strPopFileFilter = _T("popxml");
static const CString g_strPopFilePostfix = _T("popxml");
static const CString g_strPopFilePostfixDes = _T("规约工程文件");
static const CString g_strPodFileFilter = _T("podxml");
static const CString g_strPodFilePostfix = _T("podxml");
static const CString g_strPodFilePostfixDes = _T("规约工程文件");

CString Pp_GetPopCfgDeviceName(const CString &strPpTemplateFile, const CString &strDeviceFile, CExBaseList *pParent, BOOL bWithPostfix=TRUE);

