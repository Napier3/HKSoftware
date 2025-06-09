//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecfgGenMngrGlobal.h

#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"

#define GenrateCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define GenrateCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define GENRATECLASSID_CIECGENRULEMNGR       (GenrateCLASSID_EXLISTCLASS + 0X00000000)
#define GENRATECLASSID_CIECDEVICERULE       (GenrateCLASSID_EXLISTCLASS + 0X00000001)
#define GENRATECLASSID_CIECGENCFGDATAMNGRRULE       (GenrateCLASSID_EXLISTCLASS + 0X00000002)
#define GENRATECLASSID_CIECGENCFGDATAMNGRRULE_SMV       (GenrateCLASSID_EXLISTCLASS + 0X00000003)
#define GENRATECLASSID_CIECGENCFGDATAMNGRRULE_GIN       (GenrateCLASSID_EXLISTCLASS + 0X00000004)
#define GENRATECLASSID_CIECGENCFGDATAMNGRRULE_GOUT       (GenrateCLASSID_EXLISTCLASS + 0X00000005)
#define GENRATECLASSID_CIECGENRULE_CTRLBLOCK       (GenrateCLASSID_EXLISTCLASS + 0X00000006)
#define GENRATECLASSID_CIECGENCFGKEYS       (GenrateCLASSID_EXLISTCLASS + 0X00000007)
#define GENRATECLASSID_CIECGENCFGKEY       (GenrateCLASSID_EXLISTCLASS + 0X00000008)
#define GENRATECLASSID_CIECGENCFGCHILDKEY       (GenrateCLASSID_BASECLASS + 0X00000009)
#define GENRATECLASSID_CIECGENCFGDATAMNGRRULE_BASE       (GenrateCLASSID_EXLISTCLASS + 0X0000000A)
#define GENRATECLASSID_CIECGENRULE_CTRLCH       (GenrateCLASSID_EXLISTCLASS + 0X0000000B)

class CIecfgGenMngrXmlRWKeys : public CXmlRWKeys
{
protected:
	CIecfgGenMngrXmlRWKeys();
	virtual ~CIecfgGenMngrXmlRWKeys();
	static long g_nGenrateRef;

public:
	static CIecfgGenMngrXmlRWKeys* g_pXmlKeys;
	static CIecfgGenMngrXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCIecGenRule_CtrlChKey; //ch
	BSTR m_strCIecGenCfgDataMngrRule_BaseKey; //
	BSTR m_strCIecGenCfgChildKeyKey; //child-key
	BSTR m_strCIecGenCfgKeyKey; //key
	BSTR m_strCIecGenCfgKeysKey; //keys
	BSTR m_strCIecGenRule_CtrlBlockKey; //ctrl-block
	BSTR m_strCIecGenCfgDataMngrRule_GoutKey; //gout-rule
	BSTR m_strCIecGenCfgDataMngrRule_GinKey; //gin-rule
	BSTR m_strCIecGenCfgDataMngrRule_SMVKey; //smv-rule
	BSTR m_strCIecGenCfgDataMngrRuleKey; //cfg-data-mngr-rule
	BSTR m_strCIecDeviceRuleKey; //cfg-device-rule
	BSTR m_strCIecGenRuleMngrKey; //iecfg-gen-mngr
	BSTR m_strNet_DescKey; //net-desc
	BSTR m_strIecfgKey; //iecfg
	BSTR m_strGin_Ch_File_NameKey; //gin-ch-file-name
	BSTR m_strFiber_IndexKey; //fiber-index
	BSTR m_strMatch_RatioKey; //match-ratio
	BSTR m_strLogicKey; //logic
	BSTR m_strApp_ChKey; //app-ch
	BSTR m_strCh_TypeKey; //ch-type
	BSTR m_strPhsIDKey; //phs

public:
	static BSTR CIecGenRule_CtrlChKey()  {   return g_pXmlKeys->m_strCIecGenRule_CtrlChKey;  }
	static BSTR CIecGenCfgDataMngrRule_BaseKey()  {   return g_pXmlKeys->m_strCIecGenCfgDataMngrRule_BaseKey;  }
	static BSTR CIecGenCfgChildKeyKey()  {   return g_pXmlKeys->m_strCIecGenCfgChildKeyKey;  }
	static BSTR CIecGenCfgKeyKey()  {   return g_pXmlKeys->m_strCIecGenCfgKeyKey;  }
	static BSTR CIecGenCfgKeysKey()  {   return g_pXmlKeys->m_strCIecGenCfgKeysKey;  }
	static BSTR CIecGenRule_CtrlBlockKey()  {   return g_pXmlKeys->m_strCIecGenRule_CtrlBlockKey;  }
	static BSTR CIecGenCfgDataMngrRule_GoutKey()  {   return g_pXmlKeys->m_strCIecGenCfgDataMngrRule_GoutKey;  }
	static BSTR CIecGenCfgDataMngrRule_GinKey()  {   return g_pXmlKeys->m_strCIecGenCfgDataMngrRule_GinKey;  }
	static BSTR CIecGenCfgDataMngrRule_SMVKey()  {   return g_pXmlKeys->m_strCIecGenCfgDataMngrRule_SMVKey;  }
	static BSTR CIecGenCfgDataMngrRuleKey()  {   return g_pXmlKeys->m_strCIecGenCfgDataMngrRuleKey;  }
	static BSTR CIecDeviceRuleKey()  {   return g_pXmlKeys->m_strCIecDeviceRuleKey;  }
	static BSTR CIecGenRuleMngrKey()  {   return g_pXmlKeys->m_strCIecGenRuleMngrKey;  }
	static BSTR Net_DescKey()  {   return g_pXmlKeys->m_strNet_DescKey;  }
	static BSTR IecfgKey()  {   return g_pXmlKeys->m_strIecfgKey;  }
	static BSTR Gin_Ch_File_NameKey()  {   return g_pXmlKeys->m_strGin_Ch_File_NameKey;  }
	static BSTR Fiber_IndexKey()  {   return g_pXmlKeys->m_strFiber_IndexKey;  }
	static BSTR Match_RatioKey()  {   return g_pXmlKeys->m_strMatch_RatioKey;  }
	static BSTR LogicKey()  {   return g_pXmlKeys->m_strLogicKey;  }
	static BSTR App_ChKey()  {   return g_pXmlKeys->m_strApp_ChKey;  }
	static BSTR Ch_TypeKey()  {   return g_pXmlKeys->m_strCh_TypeKey;  }
};



class CIecfgGenMngrConstGlobal
{
private:
	CIecfgGenMngrConstGlobal();
	virtual ~CIecfgGenMngrConstGlobal();

public:
	static CIecfgGenMngrConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CIecfgGenMngrConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
