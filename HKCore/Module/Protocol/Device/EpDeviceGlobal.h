//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpDeviceGlobal.h

#pragma once

#include "ExBaseList.h"
#include "..\EpGlobalClassIDBaseDefine.h"

#define EPDCLASSID_CEPDEVICE       (EPDCLASSID_EXLISTCLASS + 0X00000000)
#define EPDCLASSID_CEPDEVICENODE       (EPDCLASSID_EXLISTCLASS + 0X00000001)
#define EPDCLASSID_CEPDEVICEDATA       (EPDCLASSID_BASECLASS + 0X00000002)
#define EPDCLASSID_CEPTAG            (EPDCLASSID_BASECLASS + 0X00000003)
#define EPDCLASSID_CEPTAGS            (EPDCLASSID_EXLISTCLASS + 0X00000004)

class CEpDeviceXmlRWKeys : public CXmlRWKeys
{
protected:
	CEpDeviceXmlRWKeys();
	virtual ~CEpDeviceXmlRWKeys();
	static long g_nEPDRef;

public:
	static CEpDeviceXmlRWKeys* g_pXmlKeys;
	static CEpDeviceXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCEpDeviceDataKey; //data
	BSTR m_strCEpDeviceNodeKey; //node
	BSTR m_strCEpDeviceKey; //device
	BSTR m_strUsedKey; //use

public:
	static BSTR CEpDeviceDataKey()  {   return g_pXmlKeys->m_strCEpDeviceDataKey;  }
	static BSTR CEpDeviceNodeKey()  {   return g_pXmlKeys->m_strCEpDeviceNodeKey;  }
	static BSTR CEpDeviceKey()  {   return g_pXmlKeys->m_strCEpDeviceKey;  }
	static BSTR UsedKey()  {   return g_pXmlKeys->m_strUsedKey;  }
};



class CEpDeviceConstGlobal
{
private:
	CEpDeviceConstGlobal();
	virtual ~CEpDeviceConstGlobal();

public:
	static CEpDeviceConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CEpDeviceConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
