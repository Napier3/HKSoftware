//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttTestGridDefineGlobal.h

#pragma once
#include "../../../../../Module/BaseClass/ExBaseList.h"

#define MngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define MngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define MNGRCLASSID_CSTTTESTGRIDDEFINE       (MngrCLASSID_EXLISTCLASS + 0X00000000)
#define MNGRCLASSID_CSTTGDTESTMACRO       (MngrCLASSID_EXLISTCLASS + 0X00000001)
#define MNGRCLASSID_CSTTGDDATAPROCESS       (MngrCLASSID_EXLISTCLASS + 0X00000002)
#define MNGRCLASSID_CSTTGDDATACAL       (MngrCLASSID_BASECLASS + 0X00000003)
#define MNGRCLASSID_CSTTGDGRIDDEFINE       (MngrCLASSID_EXLISTCLASS + 0X00000004)
#define MNGRCLASSID_CSTTGDCOLDEF       (MngrCLASSID_EXLISTCLASS + 0X00000005)
#define MNGRCLASSID_CSTTGDCOLDEF_PARA       (MngrCLASSID_BASECLASS + 0X00000006)
#define MNGRCLASSID_CSTTGDCOLDEF_SCRIPT       (MngrCLASSID_EXLISTCLASS + 0X00000007)
#define MNGRCLASSID_CSTTGDCOLDEF_FUC_MAX       (MngrCLASSID_EXLISTCLASS + 0X00000008)
#define MNGRCLASSID_CSTTGDCOLDEF_FUC_MIN       (MngrCLASSID_EXLISTCLASS + 0X00000009)
#define MNGRCLASSID_CSTTGDCOLDEF_FUC_AVG       (MngrCLASSID_EXLISTCLASS + 0X0000000A)
#define MNGRCLASSID_CSTTGDGRIDINSTS       (MngrCLASSID_EXLISTCLASS + 0X0000000B)
#define MNGRCLASSID_CSTTGDGRIDINST       (MngrCLASSID_EXLISTCLASS + 0X0000000C)
#define MNGRCLASSID_CSTTGDINST_COLS       (MngrCLASSID_EXLISTCLASS + 0X0000000D)
#define MNGRCLASSID_CSTTGDINST_COL       (MngrCLASSID_BASECLASS + 0X0000000E)
#define MNGRCLASSID_CSTTGDCONDITION       (MngrCLASSID_EXLISTCLASS + 0X0000000F)
#define MNGRCLASSID_CSTTGDPARACONDITION       (MngrCLASSID_BASECLASS + 0X00000010)
#define MNGRCLASSID_CSTTGDCOLDEF_TEXTCOMB       (MngrCLASSID_BASECLASS + 0X00000011)

class CSttTestGridDefineXmlRWKeys : public CXmlRWKeys
{
protected:
	CSttTestGridDefineXmlRWKeys();
	virtual ~CSttTestGridDefineXmlRWKeys();
	static long g_nMngrRef;

public:
	static CSttTestGridDefineXmlRWKeys* g_pXmlKeys;
	static CSttTestGridDefineXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCSttGdColDef_TextCombKey; //CSttGdColDef_TextComb
	BSTR m_strCSttGdParaConditionKey; //para-condition
	BSTR m_strCSttGdConditionKey; //condition
	BSTR m_strCSttGdInst_ColKey; //col
	BSTR m_strCSttGdInst_ColsKey; //cols
	BSTR m_strCSttGdGridInstKey; //grid-inst
	BSTR m_strCSttGdGridInstsKey; //grid-insts
	BSTR m_strCSttGdColDef_Fuc_AvgKey; //avg
	BSTR m_strCSttGdColDef_Fuc_MinKey; //min
	BSTR m_strCSttGdColDef_Fuc_MaxKey; //max
	BSTR m_strCSttGdColDef_ScriptKey; //script
	BSTR m_strCSttGdColDef_ParaKey; //para
	BSTR m_strCSttGdColDefKey; //col-def
	BSTR m_strCSttGdGridDefineKey; //grid-define
	BSTR m_strCSttGdDataCalKey; //data-cal
	BSTR m_strCSttGdDataProcessKey; //data-process
	BSTR m_strCSttGdTestMacroKey; //test-macro
	BSTR m_strCSttTestGridDefineKey; //test-grid-define
	BSTR m_strMacro_IdKey; //macro-id
	BSTR m_strExprKey; //expr
	BSTR m_strData_IdKey; //data-id
	BSTR m_strData_TypeKey; //data-type
	BSTR m_strUnitKey; //unit
	BSTR m_strDecimalKey; //decimal
	BSTR m_strMaxKey; //max
	BSTR m_strMinKey; //min
	BSTR m_strEditableKey; //editable
	BSTR m_strWidthKey; //width
	BSTR m_strIdKey; //id
	BSTR m_strLogicKey; //logic
	BSTR m_strValueKey; //value
	BSTR m_strPrev_TextKey; //prev-text
	BSTR m_strAfter_TextKey; //after-text
	BSTR m_strWith_UnitKey; //with-unit

public:
	static BSTR CSttGdColDef_TextCombKey()  {   return g_pXmlKeys->m_strCSttGdColDef_TextCombKey;  }
	static BSTR CSttGdParaConditionKey()  {   return g_pXmlKeys->m_strCSttGdParaConditionKey;  }
	static BSTR CSttGdConditionKey()  {   return g_pXmlKeys->m_strCSttGdConditionKey;  }
	static BSTR CSttGdInst_ColKey()  {   return g_pXmlKeys->m_strCSttGdInst_ColKey;  }
	static BSTR CSttGdInst_ColsKey()  {   return g_pXmlKeys->m_strCSttGdInst_ColsKey;  }
	static BSTR CSttGdGridInstKey()  {   return g_pXmlKeys->m_strCSttGdGridInstKey;  }
	static BSTR CSttGdGridInstsKey()  {   return g_pXmlKeys->m_strCSttGdGridInstsKey;  }
	static BSTR CSttGdColDef_Fuc_AvgKey()  {   return g_pXmlKeys->m_strCSttGdColDef_Fuc_AvgKey;  }
	static BSTR CSttGdColDef_Fuc_MinKey()  {   return g_pXmlKeys->m_strCSttGdColDef_Fuc_MinKey;  }
	static BSTR CSttGdColDef_Fuc_MaxKey()  {   return g_pXmlKeys->m_strCSttGdColDef_Fuc_MaxKey;  }
	static BSTR CSttGdColDef_ScriptKey()  {   return g_pXmlKeys->m_strCSttGdColDef_ScriptKey;  }
	static BSTR CSttGdColDef_ParaKey()  {   return g_pXmlKeys->m_strCSttGdColDef_ParaKey;  }
	static BSTR CSttGdColDefKey()  {   return g_pXmlKeys->m_strCSttGdColDefKey;  }
	static BSTR CSttGdGridDefineKey()  {   return g_pXmlKeys->m_strCSttGdGridDefineKey;  }
	static BSTR CSttGdDataCalKey()  {   return g_pXmlKeys->m_strCSttGdDataCalKey;  }
	static BSTR CSttGdDataProcessKey()  {   return g_pXmlKeys->m_strCSttGdDataProcessKey;  }
	static BSTR CSttGdTestMacroKey()  {   return g_pXmlKeys->m_strCSttGdTestMacroKey;  }
	static BSTR CSttTestGridDefineKey()  {   return g_pXmlKeys->m_strCSttTestGridDefineKey;  }
	static BSTR Macro_IdKey()  {   return g_pXmlKeys->m_strMacro_IdKey;  }
	static BSTR ExprKey()  {   return g_pXmlKeys->m_strExprKey;  }
	static BSTR Data_IdKey()  {   return g_pXmlKeys->m_strData_IdKey;  }
	static BSTR Data_TypeKey()  {   return g_pXmlKeys->m_strData_TypeKey;  }
	static BSTR UnitKey()  {   return g_pXmlKeys->m_strUnitKey;  }
	static BSTR DecimalKey()  {   return g_pXmlKeys->m_strDecimalKey;  }
	static BSTR MaxKey()  {   return g_pXmlKeys->m_strMaxKey;  }
	static BSTR MinKey()  {   return g_pXmlKeys->m_strMinKey;  }
	static BSTR EditableKey()  {   return g_pXmlKeys->m_strEditableKey;  }
	static BSTR WidthKey()  {   return g_pXmlKeys->m_strWidthKey;  }
	static BSTR IdKey()  {   return g_pXmlKeys->m_strIdKey;  }
	static BSTR LogicKey()  {   return g_pXmlKeys->m_strLogicKey;  }
	static BSTR ValueKey()  {   return g_pXmlKeys->m_strValueKey;  }
	static BSTR Prev_TextKey()  {   return g_pXmlKeys->m_strPrev_TextKey;  }
	static BSTR After_TextKey()  {   return g_pXmlKeys->m_strAfter_TextKey;  }
	static BSTR With_UnitKey()  {   return g_pXmlKeys->m_strWith_UnitKey;  }
};



class CSttTestGridDefineConstGlobal
{
private:
	CSttTestGridDefineConstGlobal();
	virtual ~CSttTestGridDefineConstGlobal();

public:
	static CSttTestGridDefineConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CSttTestGridDefineConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
