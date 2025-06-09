//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TestTasksMngrGenerateGlobal.h

#pragma once

#include "..\..\..\..\Module\BaseClass\ExBaseList.h"
#include "..\..\..\..\Module\BaseClass\ThreadProgressInterface.h"

#define TTMGCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define TTMGCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define TTMGCLASSID_CTTMGSTATION       (TTMGCLASSID_BASECLASS + 0X00000000)
#define TTMGCLASSID_CTTMGSTATIONS       (TTMGCLASSID_EXLISTCLASS + 0X00000001)
#define TTMGCLASSID_CTTMGFACTORY       (TTMGCLASSID_BASECLASS + 0X00000002)
#define TTMGCLASSID_CTTMGFACTORYS       (TTMGCLASSID_EXLISTCLASS + 0X00000003)
#define TTMGCLASSID_CTTMGBATCH       (TTMGCLASSID_EXLISTCLASS + 0X00000004)
#define TTMGCLASSID_CTESTTASKSMNGRGENERATE       (TTMGCLASSID_EXLISTCLASS + 0X00000005)
#define TTMGCLASSID_CTTMGREPORT       (TTMGCLASSID_BASECLASS + 0X00000006)
#define TTMGCLASSID_CTTMGREPORTS       (TTMGCLASSID_EXLISTCLASS + 0X00000007)
#define TTMGCLASSID_CTTMGREPORTSMNGR       (TTMGCLASSID_EXLISTCLASS + 0X00000008)
#define TTMGCLASSID_CTTMGBATCHS       (TTMGCLASSID_EXLISTCLASS + 0X00000009)
#define TTMGCLASSID_CTTMGBATCHREPORT       (TTMGCLASSID_BASECLASS + 0X0000000A)

class CTestTasksMngrGenerateXmlRWKeys : public CXmlRWKeys
{
protected:
	CTestTasksMngrGenerateXmlRWKeys();
	virtual ~CTestTasksMngrGenerateXmlRWKeys();
	static long g_nTTMGRef;

public:
	static CTestTasksMngrGenerateXmlRWKeys* g_pXmlKeys;
	static CTestTasksMngrGenerateXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCTtmgBatchReportKey; //report
	BSTR m_strCTtmgBatchsKey; //batchs
	BSTR m_strCTtmgReportsMngrKey; //rtps-mngr
	BSTR m_strCTtmgReportsKey; //rpts
	BSTR m_strCTtmgReportKey; //rpt
	BSTR m_strCTestTasksMngrGenerateKey; //rpt-generator
	BSTR m_strCTtmgBatchKey; //batch
	BSTR m_strCTtmgFactorysKey; //factorys
	BSTR m_strCTtmgFactoryKey; //factory
	BSTR m_strCTtmgStationsKey; //stations
	BSTR m_strCTtmgStationKey; //station
	BSTR m_strCodeKey; //code
	BSTR m_strOwnDefKey; //own-def
	BSTR m_strHdVerKey; //hd-ver
	BSTR m_strStationKey; //station
	BSTR m_strFactoryKey; //factory
	BSTR m_strNumKey; //num
	BSTR m_strWordBeginNOKey; //word-no-begin
	BSTR m_strProduceNOKey; //produce-no
	BSTR m_strErrorsKey; //errors
	BSTR m_strProduceDateKey; //produce-date
	BSTR m_strFlowNOKey; //flow-no
	BSTR m_strFolderKey; //folder
	BSTR m_strCurrGenIndexKey; //curr-gen-index
	BSTR m_strHasWriteExcelKey; //has-write-excel
	BSTR m_strHandTestNumKey; //hand-test
	BSTR m_strTestBeginTimeKey; //test-begin-time
	BSTR m_strGbxml1Key; //gbxml1
	BSTR m_strGbxml2Key; //gbxml2
	BSTR m_strGbxml3Key; //gbxml3
	BSTR m_strPathKey; //path
	BSTR m_strDeviceAttrKey; //device-attr
	BSTR m_strSrcRptKey; //src-rpt
	BSTR m_strDestRptKey; //dest-rpt
	BSTR m_strErrorTypeKey; //err-type
	BSTR m_strHasGeneratedKey; //has-gen

public:
	static BSTR CTtmgBatchReportKey()  {   return g_pXmlKeys->m_strCTtmgBatchReportKey;  }
	static BSTR CTtmgBatchsKey()  {   return g_pXmlKeys->m_strCTtmgBatchsKey;  }
	static BSTR CTtmgReportsMngrKey()  {   return g_pXmlKeys->m_strCTtmgReportsMngrKey;  }
	static BSTR CTtmgReportsKey()  {   return g_pXmlKeys->m_strCTtmgReportsKey;  }
	static BSTR CTtmgReportKey()  {   return g_pXmlKeys->m_strCTtmgReportKey;  }
	static BSTR CTestTasksMngrGenerateKey()  {   return g_pXmlKeys->m_strCTestTasksMngrGenerateKey;  }
	static BSTR CTtmgBatchKey()  {   return g_pXmlKeys->m_strCTtmgBatchKey;  }
	static BSTR CTtmgFactorysKey()  {   return g_pXmlKeys->m_strCTtmgFactorysKey;  }
	static BSTR CTtmgFactoryKey()  {   return g_pXmlKeys->m_strCTtmgFactoryKey;  }
	static BSTR CTtmgStationsKey()  {   return g_pXmlKeys->m_strCTtmgStationsKey;  }
	static BSTR CTtmgStationKey()  {   return g_pXmlKeys->m_strCTtmgStationKey;  }
	static BSTR CodeKey()  {   return g_pXmlKeys->m_strCodeKey;  }
	static BSTR OwnDefKey()  {   return g_pXmlKeys->m_strOwnDefKey;  }
	static BSTR HdVerKey()  {   return g_pXmlKeys->m_strHdVerKey;  }
	static BSTR StationKey()  {   return g_pXmlKeys->m_strStationKey;  }
	static BSTR FactoryKey()  {   return g_pXmlKeys->m_strFactoryKey;  }
	static BSTR NumKey()  {   return g_pXmlKeys->m_strNumKey;  }
	static BSTR WordBeginNOKey()  {   return g_pXmlKeys->m_strWordBeginNOKey;  }
	static BSTR ProduceNOKey()  {   return g_pXmlKeys->m_strProduceNOKey;  }
	static BSTR ErrorsKey()  {   return g_pXmlKeys->m_strErrorsKey;  }
	static BSTR ProduceDateKey()  {   return g_pXmlKeys->m_strProduceDateKey;  }
	static BSTR FlowNOKey()  {   return g_pXmlKeys->m_strFlowNOKey;  }
	static BSTR FolderKey()  {   return g_pXmlKeys->m_strFolderKey;  }
	static BSTR CurrGenIndexKey()  {   return g_pXmlKeys->m_strCurrGenIndexKey;  }
	static BSTR HasWriteExcelKey()  {   return g_pXmlKeys->m_strHasWriteExcelKey;  }
	static BSTR HandTestNumKey()  {   return g_pXmlKeys->m_strHandTestNumKey;  }
	static BSTR TestBeginTimeKey()  {   return g_pXmlKeys->m_strTestBeginTimeKey;  }
	static BSTR Gbxml1Key()  {   return g_pXmlKeys->m_strGbxml1Key;  }
	static BSTR Gbxml2Key()  {   return g_pXmlKeys->m_strGbxml2Key;  }
	static BSTR Gbxml3Key()  {   return g_pXmlKeys->m_strGbxml3Key;  }
	static BSTR PathKey()  {   return g_pXmlKeys->m_strPathKey;  }
	static BSTR DeviceAttrKey()  {   return g_pXmlKeys->m_strDeviceAttrKey;  }
	static BSTR SrcRptKey()  {   return g_pXmlKeys->m_strSrcRptKey;  }
	static BSTR DestRptKey()  {   return g_pXmlKeys->m_strDestRptKey;  }
	static BSTR ErrorTypeKey()  {   return g_pXmlKeys->m_strErrorTypeKey;  }
	static BSTR HasGeneratedKey()  {   return g_pXmlKeys->m_strHasGeneratedKey;  }
};



class CTestTasksMngrGenerateConstGlobal
{
private:
	CTestTasksMngrGenerateConstGlobal();
	virtual ~CTestTasksMngrGenerateConstGlobal();

public:
	static CTestTasksMngrGenerateConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CTestTasksMngrGenerateConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};

CString TTMG_GetConfigRootPath();
CString TTMG_GetRptGenRootPath();
