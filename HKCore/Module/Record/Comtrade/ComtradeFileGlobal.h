//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ComtradeFileGlobal.h

#pragma once

#include "../../BaseClass/ExBaseList.h"

#define GlobalCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define GlobalCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define GLOBALCLASSID_CRCDCOMTRADEFILE       (GlobalCLASSID_EXLISTCLASS + 0X00000000)
#define GLOBALCLASSID_CCOMTRADEDATABASE       (GlobalCLASSID_EXLISTCLASS + 0X00000001)
#define GLOBALCLASSID_CCOMTRADEANALOGDATA       (GlobalCLASSID_EXLISTCLASS + 0X00000002)
#define GLOBALCLASSID_CCOMTRADEBINARYDATA       (GlobalCLASSID_EXLISTCLASS + 0X00000003)
#define GLOBALCLASSID_CCOMTRADERATEDATA       (GlobalCLASSID_EXLISTCLASS + 0X00000004)

class CComtradeFileXmlRWKeys : public CXmlRWKeys
{
protected:
	CComtradeFileXmlRWKeys();
	virtual ~CComtradeFileXmlRWKeys();
	static long g_nGlobalRef;

public:
	static CComtradeFileXmlRWKeys* g_pXmlKeys;
	static CComtradeFileXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCComtradeRateDataKey; //rateinfor
	BSTR m_strCComtradeBinaryDataKey; //sttInfo
	BSTR m_strCComtradeAnalogDataKey; //ChInfo
	BSTR m_strCComtradeDataBaseKey; //
	BSTR m_strCRcdComtradeFileKey; //Cfg
	BSTR m_strVersionKey; //version
	BSTR m_strAllchsKey; //allchs
	BSTR m_strUIchsKey; //uichs
	BSTR m_strStatechKey; //statech
	BSTR m_strFreqKey; //freq
	BSTR m_strRatesKey; //rates
	BSTR m_strFirstpttmKey; //firstpttm
	BSTR m_strTriptmKey; //triptm
	BSTR m_strDatafiletypeKey; //datafiletype
	BSTR m_strTmmultKey; //tmmult
	BSTR m_strIndexKey; //index
	BSTR m_strCcbmKey; //ccbm
	BSTR m_strUnitKey; //unit
	BSTR m_strCoefaKey; //coefa
	BSTR m_strCoefbKey; //coefb
	BSTR m_strSkewtimeKey; //skewtime
	BSTR m_strMinKey; //min
	BSTR m_strMaxKey; //max
	BSTR m_strPrimaryKey; //primary
	BSTR m_strSecondaryKey; //secondary
	BSTR m_strPsKey; //ps
	BSTR m_strYKey; //y
	BSTR m_strSamprateKey; //samprate
	BSTR m_strEndsampKey; //endsamp

public:
	static BSTR CComtradeRateDataKey()  {   return g_pXmlKeys->m_strCComtradeRateDataKey;  }
	static BSTR CComtradeBinaryDataKey()  {   return g_pXmlKeys->m_strCComtradeBinaryDataKey;  }
	static BSTR CComtradeAnalogDataKey()  {   return g_pXmlKeys->m_strCComtradeAnalogDataKey;  }
	static BSTR CComtradeDataBaseKey()  {   return g_pXmlKeys->m_strCComtradeDataBaseKey;  }
	static BSTR CRcdComtradeFileKey()  {   return g_pXmlKeys->m_strCRcdComtradeFileKey;  }
	static BSTR VersionKey()  {   return g_pXmlKeys->m_strVersionKey;  }
	static BSTR AllchsKey()  {   return g_pXmlKeys->m_strAllchsKey;  }
	static BSTR UIchsKey()  {   return g_pXmlKeys->m_strUIchsKey;  }
	static BSTR StatechKey()  {   return g_pXmlKeys->m_strStatechKey;  }
	static BSTR FreqKey()  {   return g_pXmlKeys->m_strFreqKey;  }
	static BSTR RatesKey()  {   return g_pXmlKeys->m_strRatesKey;  }
	static BSTR FirstpttmKey()  {   return g_pXmlKeys->m_strFirstpttmKey;  }
	static BSTR TriptmKey()  {   return g_pXmlKeys->m_strTriptmKey;  }
	static BSTR DatafiletypeKey()  {   return g_pXmlKeys->m_strDatafiletypeKey;  }
	static BSTR TmmultKey()  {   return g_pXmlKeys->m_strTmmultKey;  }
	static BSTR IndexKey()  {   return g_pXmlKeys->m_strIndexKey;  }
	static BSTR CcbmKey()  {   return g_pXmlKeys->m_strCcbmKey;  }
	static BSTR UnitKey()  {   return g_pXmlKeys->m_strUnitKey;  }
	static BSTR CoefaKey()  {   return g_pXmlKeys->m_strCoefaKey;  }
	static BSTR CoefbKey()  {   return g_pXmlKeys->m_strCoefbKey;  }
	static BSTR SkewtimeKey()  {   return g_pXmlKeys->m_strSkewtimeKey;  }
	static BSTR MinKey()  {   return g_pXmlKeys->m_strMinKey;  }
	static BSTR MaxKey()  {   return g_pXmlKeys->m_strMaxKey;  }
	static BSTR PrimaryKey()  {   return g_pXmlKeys->m_strPrimaryKey;  }
	static BSTR SecondaryKey()  {   return g_pXmlKeys->m_strSecondaryKey;  }
	static BSTR PsKey()  {   return g_pXmlKeys->m_strPsKey;  }
	static BSTR YKey()  {   return g_pXmlKeys->m_strYKey;  }
	static BSTR SamprateKey()  {   return g_pXmlKeys->m_strSamprateKey;  }
	static BSTR EndsampKey()  {   return g_pXmlKeys->m_strEndsampKey;  }
};



class CComtradeFileConstGlobal
{
private:
	CComtradeFileConstGlobal();
	virtual ~CComtradeFileConstGlobal();

public:
	static CComtradeFileConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CComtradeFileConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
