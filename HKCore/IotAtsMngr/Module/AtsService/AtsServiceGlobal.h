//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsServiceGlobal.h

#pragma once

#include "../../../Module/DataMngr/DvmDataset.h"

#define ATSVRCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define ATSVRCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define ATSVRCLASSID_CATSSVRRSALLOCPARAS       (ATSVRCLASSID_EXLISTCLASS + 0X00000000)
#define ATSVRCLASSID_CATSSVRRSALLOCDEF       (ATSVRCLASSID_EXLISTCLASS + 0X00000001)
#define ATSVRCLASSID_CATSSVRRSALLOCDEFMNGR       (ATSVRCLASSID_EXLISTCLASS + 0X00000002)
#define ATSVRCLASSID_CATSSVRRSTESTAPP       (ATSVRCLASSID_EXLISTCLASS + 0X00000003)
#define ATSVRCLASSID_CATSSVRTESTRESOURCE       (ATSVRCLASSID_EXLISTCLASS + 0X00000004)
#define ATSVRCLASSID_CATSSVRTESTRESOURCES       (ATSVRCLASSID_EXLISTCLASS + 0X00000005)
#define ATSVRCLASSID_CATSSVRRSTESTAPPREF       (ATSVRCLASSID_BASECLASS + 0X00000006)
#define ATSVRCLASSID_CATSSVRTESTAPPEX       (ATSVRCLASSID_EXLISTCLASS + 0X00000007)
#define ATSVRCLASSID_CATSSVRTESTAPPS       (ATSVRCLASSID_EXLISTCLASS + 0X00000008)
#define ATSVRCLASSID_CATSSVRTESTBENCH       (ATSVRCLASSID_EXLISTCLASS + 0X00000009)
#define ATSVRCLASSID_CATSSVRTESTBENCHS       (ATSVRCLASSID_EXLISTCLASS + 0X0000000A)
#define ATSVRCLASSID_CATSSVRSERVICE       (ATSVRCLASSID_EXLISTCLASS + 0X0000000B)
#define ATSVRCLASSID_CATSSVRDEVICE       (ATSVRCLASSID_EXLISTCLASS + 0X0000000C)
#define ATSVRCLASSID_CATSSVRDEVICES       (ATSVRCLASSID_EXLISTCLASS + 0X0000000D)
#define ATSVRCLASSID_CATSSVRTESTFLOW       (ATSVRCLASSID_EXLISTCLASS + 0X0000000E)
#define ATSVRCLASSID_CATSSVRTESTFLOWS       (ATSVRCLASSID_EXLISTCLASS + 0X0000000F)

class CAtsServiceXmlRWKeys : public CDataMngrXmlRWKeys
{
protected:
	CAtsServiceXmlRWKeys();
	virtual ~CAtsServiceXmlRWKeys();
	static long g_nATSVRRef;

public:
	static CAtsServiceXmlRWKeys* g_pXmlKeys;
	static CAtsServiceXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCAtsSvrTestFlowsKey; //TestFlows
	BSTR m_strCAtsSvrTestFlowKey; //TestFlow
	BSTR m_strCAtsSvrDevicesKey; //Devices
	BSTR m_strCAtsSvrDeviceKey; //Device
	BSTR m_strCAtsSvrServiceKey; //AtsService
	BSTR m_strCAtsSvrTestBenchsKey; //Benchs
	BSTR m_strCAtsSvrTestBenchKey; //Bench
	BSTR m_strCAtsSvrTestAppsKey; //TestApps
	BSTR m_strCAtsSvrTestAppExKey; //TestAppEx
	BSTR m_strCAtsSvrRsTestAppRefKey; //TestAppRef
	BSTR m_strCAtsSvrTestResourcesKey; //TestResources
	BSTR m_strCAtsSvrTestResourceKey; //TestResource
	BSTR m_strCAtsSvrRsTestAppKey; //TestApp
	BSTR m_strCAtsSvrRsAllocDefMngrKey; //RsAllocDefMngr
	BSTR m_strCAtsSvrRsAllocDefKey; //RsAllocDef
	BSTR m_strCAtsSvrRsAllocParasKey; //RsAllocParas
	BSTR m_strDeviceTypeKey; //DeviceType
	BSTR m_strDeviceSNKey; //DeviceSN
	BSTR m_strMacroIDKey; //MacroID
	BSTR m_strBenchSNKey; //BenchSN
	BSTR m_strTypeKey; //type
	BSTR m_strSelfStartKey; //SelfStart
	BSTR m_strSnKey; //sn
	BSTR m_strAttrsKey; //Attrs
	BSTR m_strSvrModeKey; //SvrMode
	BSTR m_strIsServiceMngrKey; //SvrMode
	BSTR m_strUseTemplateSvrKey;  //use-template-svr
	BSTR m_strSmartTestSvrKey;    //SmartTestSvr

public:
	static BSTR CAtsSvrTestFlowsKey()  {   return g_pXmlKeys->m_strCAtsSvrTestFlowsKey;  }
	static BSTR CAtsSvrTestFlowKey()  {   return g_pXmlKeys->m_strCAtsSvrTestFlowKey;  }
	static BSTR CAtsSvrDevicesKey()  {   return g_pXmlKeys->m_strCAtsSvrDevicesKey;  }
	static BSTR CAtsSvrDeviceKey()  {   return g_pXmlKeys->m_strCAtsSvrDeviceKey;  }
	static BSTR CAtsSvrServiceKey()  {   return g_pXmlKeys->m_strCAtsSvrServiceKey;  }
	static BSTR CAtsSvrTestBenchsKey()  {   return g_pXmlKeys->m_strCAtsSvrTestBenchsKey;  }
	static BSTR CAtsSvrTestBenchKey()  {   return g_pXmlKeys->m_strCAtsSvrTestBenchKey;  }
	static BSTR CAtsSvrTestAppsKey()  {   return g_pXmlKeys->m_strCAtsSvrTestAppsKey;  }
	static BSTR CAtsSvrTestAppExKey()  {   return g_pXmlKeys->m_strCAtsSvrTestAppExKey;  }
	static BSTR CAtsSvrRsTestAppRefKey()  {   return g_pXmlKeys->m_strCAtsSvrRsTestAppRefKey;  }
	static BSTR CAtsSvrTestResourcesKey()  {   return g_pXmlKeys->m_strCAtsSvrTestResourcesKey;  }
	static BSTR CAtsSvrTestResourceKey()  {   return g_pXmlKeys->m_strCAtsSvrTestResourceKey;  }
	static BSTR CAtsSvrRsTestAppKey()  {   return g_pXmlKeys->m_strCAtsSvrRsTestAppKey;  }
	static BSTR CAtsSvrRsAllocDefMngrKey()  {   return g_pXmlKeys->m_strCAtsSvrRsAllocDefMngrKey;  }
	static BSTR CAtsSvrRsAllocDefKey()  {   return g_pXmlKeys->m_strCAtsSvrRsAllocDefKey;  }
	static BSTR CAtsSvrRsAllocParasKey()  {   return g_pXmlKeys->m_strCAtsSvrRsAllocParasKey;  }
	static BSTR DeviceTypeKey()  {   return g_pXmlKeys->m_strDeviceTypeKey;  }
	static BSTR DeviceSNKey()  {   return g_pXmlKeys->m_strDeviceSNKey;  }
	static BSTR MacroIDKey()  {   return g_pXmlKeys->m_strMacroIDKey;  }
	static BSTR BenchSNKey()  {   return g_pXmlKeys->m_strBenchSNKey;  }
	static BSTR TypeKey()  {   return g_pXmlKeys->m_strTypeKey;  }
	static BSTR SelfStartKey()  {   return g_pXmlKeys->m_strSelfStartKey;  }
	static BSTR AttrsKey()  {   return g_pXmlKeys->m_strAttrsKey;  }
	static BSTR SnKey()  {   return g_pXmlKeys->m_strSnKey;  }
	static BSTR SvrModeKey()  {   return g_pXmlKeys->m_strSvrModeKey;  }
};



class CAtsServiceConstGlobal
{
private:
	CAtsServiceConstGlobal();
	virtual ~CAtsServiceConstGlobal();

public:
	static CAtsServiceConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CAtsServiceConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};

#define Ats_Svr_Service_Config_File   _T("SmartTestService.xml")
