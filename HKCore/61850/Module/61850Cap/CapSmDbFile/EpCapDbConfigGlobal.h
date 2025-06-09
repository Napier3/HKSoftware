//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapDbConfigGlobal.h

#pragma once

#include "ExBaseList.h"

#define MngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define MngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define MNGRCLASSID_CEPCAPDBCONFIG       (MngrCLASSID_EXLISTCLASS + 0X00000000)
#define MNGRCLASSID_CEPCAPDBFILECFG       (MngrCLASSID_BASECLASS + 0X00000001)
#define MNGRCLASSID_CEPCAPDBFILEAREA       (MngrCLASSID_BASECLASS + 0X00000002)

class CEpCapDbConfigXmlRWKeys : public CXmlRWKeys
{
protected:
	CEpCapDbConfigXmlRWKeys();
	virtual ~CEpCapDbConfigXmlRWKeys();
	static long g_nMngrRef;

public:
	static CEpCapDbConfigXmlRWKeys* g_pXmlKeys;
	static CEpCapDbConfigXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCEpCapDbFileAreaKey; //db-area
	BSTR m_strCEpCapDbFileCfgKey; //sm-db-file
	BSTR m_strCEpCapDbConfigKey; //ep-cap-db-config
	BSTR m_strSizeKey; //size
	BSTR m_strViewKey; //view
	BSTR m_strFileKey; //file
	BSTR m_strBeginPosKey; //view

public:
	static BSTR CEpCapDbFileAreaKey()  {   return g_pXmlKeys->m_strCEpCapDbFileAreaKey;  }
	static BSTR CEpCapDbFileCfgKey()  {   return g_pXmlKeys->m_strCEpCapDbFileCfgKey;  }
	static BSTR CEpCapDbConfigKey()  {   return g_pXmlKeys->m_strCEpCapDbConfigKey;  }
	static BSTR SizeKey()  {   return g_pXmlKeys->m_strSizeKey;  }
	static BSTR ViewKey()  {   return g_pXmlKeys->m_strViewKey;  }
	static BSTR FileKey()  {   return g_pXmlKeys->m_strFileKey;  }
	static BSTR BeginPosKey()  {   return g_pXmlKeys->m_strBeginPosKey;  }
};



class CEpCapDbConfigConstGlobal
{
private:
	CEpCapDbConfigConstGlobal();
	virtual ~CEpCapDbConfigConstGlobal();

public:
	static CEpCapDbConfigConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CEpCapDbConfigConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
