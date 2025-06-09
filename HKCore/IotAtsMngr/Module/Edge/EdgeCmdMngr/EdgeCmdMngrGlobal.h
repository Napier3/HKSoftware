//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeCmdMngrGlobal.h

#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"

#define MngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define MngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define MNGRCLASSID_CEDGEGROUP       (MngrCLASSID_EXLISTCLASS + 0X00000000)
#define MNGRCLASSID_CEDGEDATA       (MngrCLASSID_EXLISTCLASS + 0X00000001)
#define MNGRCLASSID_CEDGEPARAM       (MngrCLASSID_EXLISTCLASS + 0X00000002)
#define MNGRCLASSID_CEDGEPARAS       (MngrCLASSID_EXLISTCLASS + 0X00000003)
#define MNGRCLASSID_CEDGEDEV       (MngrCLASSID_EXLISTCLASS + 0X00000004)
#define MNGRCLASSID_CEDGECPU       (MngrCLASSID_EXLISTCLASS + 0X00000005)
#define MNGRCLASSID_CEDGEMEM       (MngrCLASSID_EXLISTCLASS + 0X00000006)
#define MNGRCLASSID_CEDGEDISK       (MngrCLASSID_EXLISTCLASS + 0X00000007)
#define MNGRCLASSID_CEDGELINKS       (MngrCLASSID_EXLISTCLASS + 0X00000008)
#define MNGRCLASSID_CEDGELINK       (MngrCLASSID_EXLISTCLASS + 0X00000009)
#define MNGRCLASSID_CEDGEOS       (MngrCLASSID_EXLISTCLASS + 0X0000000A)
#define MNGRCLASSID_CEDGECPULMT       (MngrCLASSID_EXLISTCLASS + 0X0000000B)
#define MNGRCLASSID_CEDGEMEMLMT       (MngrCLASSID_EXLISTCLASS + 0X0000000C)
#define MNGRCLASSID_CEDGEDISKLMT       (MngrCLASSID_EXLISTCLASS + 0X0000000D)
#define MNGRCLASSID_CEDGEFILE       (MngrCLASSID_EXLISTCLASS + 0X0000000E)
#define MNGRCLASSID_CEDGESIGN       (MngrCLASSID_EXLISTCLASS + 0X0000000F)
#define MNGRCLASSID_CEDGELINKSTATE       (MngrCLASSID_EXLISTCLASS + 0X00000010)
#define MNGRCLASSID_CEDGEMEMUSED       (MngrCLASSID_EXLISTCLASS + 0X00000011)
#define MNGRCLASSID_CEDGETEMPERATURE       (MngrCLASSID_EXLISTCLASS + 0X00000012)
#define MNGRCLASSID_CEDGEREPPERIOD       (MngrCLASSID_EXLISTCLASS + 0X00000013)
#define MNGRCLASSID_CEDGEDEVICEINFOS       (MngrCLASSID_EXLISTCLASS + 0X00000014)
#define MNGRCLASSID_CEDGECMD       (MngrCLASSID_EXLISTCLASS + 0X00000015)
#define MNGRCLASSID_CEDGEDATAS       (MngrCLASSID_EXLISTCLASS + 0X00000016)

class CEdgeCmdMngrXmlRWKeys : public CXmlRWKeys
{
protected:
	CEdgeCmdMngrXmlRWKeys();
	virtual ~CEdgeCmdMngrXmlRWKeys();
	static long g_nMngrRef;

public:
	static CEdgeCmdMngrXmlRWKeys* g_pXmlKeys;
	static CEdgeCmdMngrXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCEdgeDatasKey; //datas
	BSTR m_strCEdgeCmdKey; //edgecmd
	BSTR m_strCEdgeDeviceInfosKey; //deviceInfos
	BSTR m_strCEdgeRepPeriodKey; //repPeriod
	BSTR m_strCEdgeTemperatureKey; //temperature
	BSTR m_strCEdgeMemUsedKey; //memUsed
	BSTR m_strCEdgeLinkStateKey; //linkState
	BSTR m_strCEdgeSignKey; //sign
	BSTR m_strCEdgeFileKey; //file
	BSTR m_strCEdgeDiskLmtKey; //disklmt
	BSTR m_strCEdgeMemLmtKey; //memlmt
	BSTR m_strCEdgeCpuLmtKey; //cpulmt
	BSTR m_strCEdgeOSKey; //os
	BSTR m_strCEdgeLinkKey; //link
	BSTR m_strCEdgeLinksKey; //links
	BSTR m_strCEdgeDiskKey; //disk
	BSTR m_strCEdgeMemKey; //mem
	BSTR m_strCEdgeCpuKey; //cpu
	BSTR m_strCEdgeDevKey; //dev
	BSTR m_strCEdgeParasKey; //paras
	BSTR m_strCEdgeParamKey; //param
	BSTR m_strCEdgeDataKey; //data
	BSTR m_strCEdgeGroupKey; //group
	BSTR m_strDataTypeKey; //data-type
	BSTR m_strValueKey; //value

public:
	static BSTR CEdgeDatasKey()  {   return g_pXmlKeys->m_strCEdgeDatasKey;  }
	static BSTR CEdgeCmdKey()  {   return g_pXmlKeys->m_strCEdgeCmdKey;  }
	static BSTR CEdgeDeviceInfosKey()  {   return g_pXmlKeys->m_strCEdgeDeviceInfosKey;  }
	static BSTR CEdgeRepPeriodKey()  {   return g_pXmlKeys->m_strCEdgeRepPeriodKey;  }
	static BSTR CEdgeTemperatureKey()  {   return g_pXmlKeys->m_strCEdgeTemperatureKey;  }
	static BSTR CEdgeMemUsedKey()  {   return g_pXmlKeys->m_strCEdgeMemUsedKey;  }
	static BSTR CEdgeLinkStateKey()  {   return g_pXmlKeys->m_strCEdgeLinkStateKey;  }
	static BSTR CEdgeSignKey()  {   return g_pXmlKeys->m_strCEdgeSignKey;  }
	static BSTR CEdgeFileKey()  {   return g_pXmlKeys->m_strCEdgeFileKey;  }
	static BSTR CEdgeDiskLmtKey()  {   return g_pXmlKeys->m_strCEdgeDiskLmtKey;  }
	static BSTR CEdgeMemLmtKey()  {   return g_pXmlKeys->m_strCEdgeMemLmtKey;  }
	static BSTR CEdgeCpuLmtKey()  {   return g_pXmlKeys->m_strCEdgeCpuLmtKey;  }
	static BSTR CEdgeOSKey()  {   return g_pXmlKeys->m_strCEdgeOSKey;  }
	static BSTR CEdgeLinkKey()  {   return g_pXmlKeys->m_strCEdgeLinkKey;  }
	static BSTR CEdgeLinksKey()  {   return g_pXmlKeys->m_strCEdgeLinksKey;  }
	static BSTR CEdgeDiskKey()  {   return g_pXmlKeys->m_strCEdgeDiskKey;  }
	static BSTR CEdgeMemKey()  {   return g_pXmlKeys->m_strCEdgeMemKey;  }
	static BSTR CEdgeCpuKey()  {   return g_pXmlKeys->m_strCEdgeCpuKey;  }
	static BSTR CEdgeDevKey()  {   return g_pXmlKeys->m_strCEdgeDevKey;  }
	static BSTR CEdgeParasKey()  {   return g_pXmlKeys->m_strCEdgeParasKey;  }
	static BSTR CEdgeParamKey()  {   return g_pXmlKeys->m_strCEdgeParamKey;  }
	static BSTR CEdgeDataKey()  {   return g_pXmlKeys->m_strCEdgeDataKey;  }
	static BSTR CEdgeGroupKey()  {   return g_pXmlKeys->m_strCEdgeGroupKey;  }
	static BSTR DataTypeKey()  {   return g_pXmlKeys->m_strDataTypeKey;  }
	static BSTR ValueKey()  {   return g_pXmlKeys->m_strValueKey;  }
};



class CEdgeCmdMngrConstGlobal
{
private:
	CEdgeCmdMngrConstGlobal();
	virtual ~CEdgeCmdMngrConstGlobal();

public:
	static CEdgeCmdMngrConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CEdgeCmdMngrConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
