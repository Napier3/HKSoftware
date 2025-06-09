//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgToolGlobal.h

#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"

#define IFTCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define IFTCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define IFTCLASSID_CIECCFGFILE       (IFTCLASSID_BASECLASS + 0X00000000)
#define IFTCLASSID_CIECCFGFILES       (IFTCLASSID_EXLISTCLASS + 0X00000001)
#define IFTCLASSID_CSCLFILE       (IFTCLASSID_BASECLASS + 0X00000002)
#define IFTCLASSID_CSCLFILES       (IFTCLASSID_EXLISTCLASS + 0X00000003)
#define IFTCLASSID_CIECCFGTOOL       (IFTCLASSID_EXLISTCLASS + 0X00000004)
#define IFTCLASSID_CIECCFGFILE_DEVICE       (IFTCLASSID_EXLISTCLASS + 0X00000005)

class CIecCfgToolXmlRWKeys : public CXmlRWKeys
{
protected:
	CIecCfgToolXmlRWKeys();
	virtual ~CIecCfgToolXmlRWKeys();
	static long g_nIFTRef;

public:
	static CIecCfgToolXmlRWKeys* g_pXmlKeys;
	static CIecCfgToolXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCIecCfgToolKey; //iecfg-tool
	BSTR m_strCSclFilesKey; //scl-files
	BSTR m_strCSclFileKey; //scl-file
	BSTR m_strCIecCfgFilesKey; //iecfg-files
	BSTR m_strCIecCfgFileKey; //iecfg-file
	BSTR m_strCIecCfgFileDeviceKey; //iecfg-file-device

	BSTR m_strUseDebugKey; 
	BSTR m_strAutoSetUIChIndexKey; //
	BSTR m_strIecCfgDownDllFileKey; //
	BSTR m_strViewOnlyUsedInChsKey; //view-only-used-inch
	BSTR m_strViewChsPathKey; //"view-chs-path"

	BSTR m_strTscdNameKey; //tscd-name
	BSTR m_strAT02D_UseHarmKey; //"use-harm"    周宏军  20200615 用于生成模型时是否增加谐波
	BSTR m_strAT02D_VerifyVolCurChannelKey; //"verify-volcur" 周宏军 20201128  AT02D生成配置文件时，校验必须都包含电压电流通道，但对于PNI302的配置文件，可能只包含电压通道，此时不需要此校验功能
	BSTR m_strLinkGoutKey; //"link-gout"    周宏军  20200615 关联Gout虚端子
	BSTR m_strAutoOpenLastKey; //"auto-open-last"    周宏军  20200914 是否自动打开上次打开过的配置文件

public:
	static BSTR CIecCfgToolKey()  {   return g_pXmlKeys->m_strCIecCfgToolKey;  }
	static BSTR CSclFilesKey()  {   return g_pXmlKeys->m_strCSclFilesKey;  }
	static BSTR CSclFileKey()  {   return g_pXmlKeys->m_strCSclFileKey;  }
	static BSTR CIecCfgFilesKey()  {   return g_pXmlKeys->m_strCIecCfgFilesKey;  }
	static BSTR CIecCfgFileKey()  {   return g_pXmlKeys->m_strCIecCfgFileKey;  }
	static BSTR CIecCfgFileDeviceKey()  {   return g_pXmlKeys->m_strCIecCfgFileDeviceKey;  }
};



class CIecCfgToolConstGlobal
{
private:
	CIecCfgToolConstGlobal();
	virtual ~CIecCfgToolConstGlobal();

public:
	static CIecCfgToolConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CIecCfgToolConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
