//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PpCfgGlobal.h

#pragma once

#include "../../../Module/DataMngr/DataMngrGlobal.h"

#define PpCfgCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00090000)
#define PpCfgCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00090000)

#define PPCFGCLASSID_CSENSORPPCONFIG       (PpCfgCLASSID_EXLISTCLASS + 0X00000000)
#define PPCFGCLASSID_CSENSORPPDEVICETYPE       (PpCfgCLASSID_EXLISTCLASS + 0X00000001)
#define PPCFGCLASSID_CSENSORPPPRASE       (PpCfgCLASSID_EXLISTCLASS + 0X00000002)
#define PPCFGCLASSID_CSENSORPPPRODUCE       (PpCfgCLASSID_EXLISTCLASS + 0X00000003)

class CPpCfgXmlRWKeys : public CDataMngrXmlRWKeys
{
protected:
	CPpCfgXmlRWKeys();
	virtual ~CPpCfgXmlRWKeys();
	static long g_nPpCfgRef;

public:
	static CPpCfgXmlRWKeys* g_pXmlKeys;
	static CPpCfgXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCSensorPpProduceKey; //pp-produce
	BSTR m_strCSensorPpPraseKey; //pp-prase
	BSTR m_strCSensorPpDeviceTypeKey; //device-type
	BSTR m_strCSensorPpConfigKey; //sensor-pkg-protocol

public:
	static BSTR CSensorPpProduceKey()  {   return g_pXmlKeys->m_strCSensorPpProduceKey;  }
	static BSTR CSensorPpPraseKey()  {   return g_pXmlKeys->m_strCSensorPpPraseKey;  }
	static BSTR CSensorPpDeviceTypeKey()  {   return g_pXmlKeys->m_strCSensorPpDeviceTypeKey;  }
	static BSTR CSensorPpConfigKey()  {   return g_pXmlKeys->m_strCSensorPpConfigKey;  }
};



class CPpCfgConstGlobal
{
private:
	CPpCfgConstGlobal();
	virtual ~CPpCfgConstGlobal();

public:
	static CPpCfgConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CPpCfgConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
