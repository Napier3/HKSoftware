//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IOTPPGlobal.h

#pragma once

#include "../../../../Module/BaseClass/ExBaseList.h"

#define IOTCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define IOTCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define IOTCLASSID_CIOTPPTEMPLATE       (IOTCLASSID_EXLISTCLASS + 0X00000000)
#define IOTCLASSID_CIOTPPPARSES       (IOTCLASSID_EXLISTCLASS + 0X00000001)
#define IOTCLASSID_CIOTPPPRODUCES       (IOTCLASSID_EXLISTCLASS + 0X00000002)
#define IOTCLASSID_CIOTPPPROCEDURES       (IOTCLASSID_EXLISTCLASS + 0X00000003)
#define IOTCLASSID_CIOTPPPARSE       (IOTCLASSID_EXLISTCLASS + 0X00000004)
#define IOTCLASSID_CIOTPPPRODUCE       (IOTCLASSID_EXLISTCLASS + 0X00000005)
#define IOTCLASSID_CIOTPPPROCEDURE       (IOTCLASSID_EXLISTCLASS + 0X00000006)
#define IOTCLASSID_CIOTPPPKGHEAD       (IOTCLASSID_EXLISTCLASS + 0X00000007)
#define IOTCLASSID_CIOTPPDATALIST       (IOTCLASSID_EXLISTCLASS + 0X00000008)
#define IOTCLASSID_CIOTPPINTERFACE       (IOTCLASSID_EXLISTCLASS + 0X00000009)
#define IOTCLASSID_CIOTPPVALUE       (IOTCLASSID_BASECLASS + 0X0000000A)
#define IOTCLASSID_CIOTPPNODE       (IOTCLASSID_EXLISTCLASS + 0X0000000B)
#define IOTCLASSID_CIOTPPACKS       (IOTCLASSID_EXLISTCLASS + 0X0000000C)
#define IOTCLASSID_CIOTPPACK       (IOTCLASSID_EXLISTCLASS + 0X0000000D)
#define IOTCLASSID_CIOTPPTIMERS       (IOTCLASSID_EXLISTCLASS + 0X0000000E)
#define IOTCLASSID_CIOTPPTIMER       (IOTCLASSID_EXLISTCLASS + 0X0000000F)
#define IOTCLASSID_CIOTPPJUMPS       (IOTCLASSID_EXLISTCLASS + 0X00000010)
#define IOTCLASSID_CIOTPPJUMP       (IOTCLASSID_EXLISTCLASS + 0X00000011)

#define PROCEDURE_END_NODE_ID	_T("END")
#define PROCEDURE_START_NODE_ID	_T("START")

class CIOTPPXmlRWKeys : public CXmlRWKeys
{
protected:
	CIOTPPXmlRWKeys();
	virtual ~CIOTPPXmlRWKeys();
	static long g_nIOTRef;

public:
	static CIOTPPXmlRWKeys* g_pXmlKeys;
	static CIOTPPXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCIotPpJumpKey; //jump
	BSTR m_strCIotPpJumpsKey; //jumps
	BSTR m_strCIotPpTimerKey; //timer
	BSTR m_strCIotPpTimersKey; //timers
	BSTR m_strCIotPpAckKey; //ack
	BSTR m_strCIotPpAcksKey; //acks
	BSTR m_strCIotPpNodeKey; //node
	BSTR m_strCIotPpValueKey; //value
	BSTR m_strCIotPpInterfaceKey; //interface
	BSTR m_strCIotPpDataListKey; //data-list
	BSTR m_strCIotPpPkgHeadKey; //pkg-head
	BSTR m_strCIotPpProcedureKey; //procedure
	BSTR m_strCIotPpProduceKey; //pp-produce
	BSTR m_strCIotPpParseKey; //pp-parse
	BSTR m_strCIotPpProceduresKey; //procedures
	BSTR m_strCIotPpProducesKey; //pp-produces
	BSTR m_strCIotPpParsesKey; //pp-parses
	BSTR m_strCIotPpTemplateKey; //iot-pp-template
	BSTR m_strDvm_FileKey; //dvm-file
	BSTR m_strDs_OptrKey; //ds-optr
	BSTR m_strDsKey; //ds
	BSTR m_strData_TypeKey; //data-type
	BSTR m_strValueKey; //value
	BSTR m_strPkg_IdKey; //pkg-id
	BSTR m_strTypeKey; //type
	BSTR m_strJump_ToKey; //jump-to
	BSTR m_strTimeKey; //time

public:
	static BSTR CIotPpJumpKey()  {   return g_pXmlKeys->m_strCIotPpJumpKey;  }
	static BSTR CIotPpJumpsKey()  {   return g_pXmlKeys->m_strCIotPpJumpsKey;  }
	static BSTR CIotPpTimerKey()  {   return g_pXmlKeys->m_strCIotPpTimerKey;  }
	static BSTR CIotPpTimersKey()  {   return g_pXmlKeys->m_strCIotPpTimersKey;  }
	static BSTR CIotPpAckKey()  {   return g_pXmlKeys->m_strCIotPpAckKey;  }
	static BSTR CIotPpAcksKey()  {   return g_pXmlKeys->m_strCIotPpAcksKey;  }
	static BSTR CIotPpNodeKey()  {   return g_pXmlKeys->m_strCIotPpNodeKey;  }
	static BSTR CIotPpValueKey()  {   return g_pXmlKeys->m_strCIotPpValueKey;  }
	static BSTR CIotPpInterfaceKey()  {   return g_pXmlKeys->m_strCIotPpInterfaceKey;  }
	static BSTR CIotPpDataListKey()  {   return g_pXmlKeys->m_strCIotPpDataListKey;  }
	static BSTR CIotPpPkgHeadKey()  {   return g_pXmlKeys->m_strCIotPpPkgHeadKey;  }
	static BSTR CIotPpProcedureKey()  {   return g_pXmlKeys->m_strCIotPpProcedureKey;  }
	static BSTR CIotPpProduceKey()  {   return g_pXmlKeys->m_strCIotPpProduceKey;  }
	static BSTR CIotPpParseKey()  {   return g_pXmlKeys->m_strCIotPpParseKey;  }
	static BSTR CIotPpProceduresKey()  {   return g_pXmlKeys->m_strCIotPpProceduresKey;  }
	static BSTR CIotPpProducesKey()  {   return g_pXmlKeys->m_strCIotPpProducesKey;  }
	static BSTR CIotPpParsesKey()  {   return g_pXmlKeys->m_strCIotPpParsesKey;  }
	static BSTR CIotPpTemplateKey()  {   return g_pXmlKeys->m_strCIotPpTemplateKey;  }
	static BSTR Dvm_FileKey()  {   return g_pXmlKeys->m_strDvm_FileKey;  }
	static BSTR Ds_OptrKey()  {   return g_pXmlKeys->m_strDs_OptrKey;  }
	static BSTR DsKey()  {   return g_pXmlKeys->m_strDsKey;  }
	static BSTR Data_TypeKey()  {   return g_pXmlKeys->m_strData_TypeKey;  }
	static BSTR ValueKey()  {   return g_pXmlKeys->m_strValueKey;  }
	static BSTR Pkg_IdKey()  {   return g_pXmlKeys->m_strPkg_IdKey;  }
	static BSTR TypeKey()  {   return g_pXmlKeys->m_strTypeKey;  }
	static BSTR Jump_ToKey()  {   return g_pXmlKeys->m_strJump_ToKey;  }
	static BSTR TimeKey()  {   return g_pXmlKeys->m_strTimeKey;  }
};



class CIOTPPConstGlobal
{
private:
	CIOTPPConstGlobal();
	virtual ~CIOTPPConstGlobal();

public:
	static CIOTPPConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CIOTPPConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
