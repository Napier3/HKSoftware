//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbItemsGenRuleDefMngrGlobal.h

#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"

#define GbItemsGenMngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define GbItemsGenMngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define GBITEMSGENMNGRCLASSID_CITEMSGENBASE       (GbItemsGenMngrCLASSID_EXLISTCLASS + 0X00001000)
#define GBITEMSGENMNGRCLASSID_CGENNODEBASE       (GbItemsGenMngrCLASSID_EXLISTCLASS + 0X00003000)

#define GBITEMSGENMNGRCLASSID_CGBITEMSGEN       (GbItemsGenMngrCLASSID_EXLISTCLASS + 0X00000000)
#define GBITEMSGENMNGRCLASSID_CMACROITEMSGEN       (GbItemsGenMngrCLASSID_EXLISTCLASS + 0X00000001)
#define GBITEMSGENMNGRCLASSID_CITEMSGENCLASS       (GBITEMSGENMNGRCLASSID_CITEMSGENBASE + 0X00000002)
#define GBITEMSGENMNGRCLASSID_CITEMSGENINST       (GbItemsGenMngrCLASSID_EXLISTCLASS + 0X00000003)
#define GBITEMSGENMNGRCLASSID_CITEMSGENPARASMAP       (GbItemsGenMngrCLASSID_EXLISTCLASS + 0X00000004)
#define GBITEMSGENMNGRCLASSID_CITEMSGENINTERFACE       (GbItemsGenMngrCLASSID_EXLISTCLASS + 0X00000005)
#define GBITEMSGENMNGRCLASSID_CITEMSGENDATA       (GbItemsGenMngrCLASSID_BASECLASS + 0X00000006)
#define GBITEMSGENMNGRCLASSID_CITEMSGENENABLE       (GbItemsGenMngrCLASSID_EXLISTCLASS + 0X00000007)
#define GBITEMSGENMNGRCLASSID_CPARASGENNODE       (GBITEMSGENMNGRCLASSID_CGENNODEBASE + 0X00000008)
#define GBITEMSGENMNGRCLASSID_CITEMSGENPARADEF       (GbItemsGenMngrCLASSID_EXLISTCLASS + 0X00000009)
#define GBITEMSGENMNGRCLASSID_CITEMSGENPARA       (GbItemsGenMngrCLASSID_BASECLASS + 0X0000000A)
#define GBITEMSGENMNGRCLASSID_CITEMSGENNAMEADD       (GbItemsGenMngrCLASSID_EXLISTCLASS + 0X0000000B)
#define GBITEMSGENMNGRCLASSID_CITEMSGENNAMEITEM       (GbItemsGenMngrCLASSID_BASECLASS + 0X0000000C)
#define GBITEMSGENMNGRCLASSID_CITEMSGENDATAMAP       (GbItemsGenMngrCLASSID_BASECLASS + 0X0000000D)
#define GBITEMSGENMNGRCLASSID_CITEMSGENDEFINE       (GBITEMSGENMNGRCLASSID_CITEMSGENBASE + 0X0000000E)
#define GBITEMSGENMNGRCLASSID_CITEMSGENNODE       (GBITEMSGENMNGRCLASSID_CGENNODEBASE + 0X0000000F)
#define GBITEMSGENMNGRCLASSID_CITEMSGENCHARITEMLINE      (GbItemsGenMngrCLASSID_BASECLASS + 0X00000010)

#define GBITEMSGENMNGRCLASSID_CITEMGENRSLTEXPR   (GbItemsGenMngrCLASSID_EXLISTCLASS		+  0X00000011)
#define GBITEMSGENMNGRCLASSID_CITEMGENCOMMCMD    (GbItemsGenMngrCLASSID_EXLISTCLASS		+  0X00000012)
#define GBITEMSGENMNGRCLASSID_CITEMGENSAFETY     (GbItemsGenMngrCLASSID_EXLISTCLASS		+  0X00000013)
#define GBITEMSGENMNGRCLASSID_CITEMGENSYSPARAEDIT   (GbItemsGenMngrCLASSID_EXLISTCLASS		+  0X00000014)
#define GBITEMSGENMNGRCLASSID_CITEMSGENDATASET       (GbItemsGenMngrCLASSID_BASECLASS + 0X00000015)
#define GBITEMSGENMNGRCLASSID_CMACROSELFDEFGEN       (GbItemsGenMngrCLASSID_EXLISTCLASS + 0X00000016)

//使能模式：与、或、非
#define GB_ITEMS_GEN_ENABLE_AND  _T("and")
#define GB_ITEMS_GEN_ENABLE_OR   _T("or")
#define GB_ITEMS_GEN_ENABLE_NOT  _T("not")

//模板生成实例的模板，是class还是define
#define GB_ITEMS_GEN_INST_CLASS_CLASS   _T("SttItemsGenClass")
#define GB_ITEMS_GEN_INST_CLASS_DEFINE  _T("SttItemsGenDefine")

//项目生成节点类的类型
//class模式下的节点类型
#define GB_ITEMS_GEN_NODETYPE_SEQUENCE    _T("sequence")
#define GB_ITEMS_GEN_NODETYPE_CHOICE      _T("choice")

//define模式下的节点类型，该模式下，节点类型对应于项目类型
#define GB_ITEMS_GEN_NODETYPE_COMMCMD     _T("commoncmd")
#define GB_ITEMS_GEN_NODETYPE_ITEMS       _T("items")
#define GB_ITEMS_GEN_NODETYPE_MACROTEST   _T("macrotest")
#define GB_ITEMS_GEN_NODETYPE_NONE        _T("none")   //none，表示该项目生成节点，不生成测试项目，仅表示模板结构
#define GB_ITEMS_GEN_NODETYPE_SAFETY      _T("safety")
#define GB_ITEMS_GEN_NODETYPE_SYSPARAEDIT _T("sysparaedit")

class CGbItemsGenRuleDefMngrXmlRWKeys : public CXmlRWKeys
{
protected:
	CGbItemsGenRuleDefMngrXmlRWKeys();
	virtual ~CGbItemsGenRuleDefMngrXmlRWKeys();
	static long g_nGbItemsGenMngrRef;

public:
	static CGbItemsGenRuleDefMngrXmlRWKeys* g_pXmlKeys;
	static CGbItemsGenRuleDefMngrXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCItemsGenNodeKey; //items-gen-node
	BSTR m_strCItemsGenDefineKey; //items-gen-define
	BSTR m_strCItemsGenDataMapKey; //data-map
	BSTR m_strCItemsGenDatasetKey; //dataset
	BSTR m_strCItemsGenNameItemKey; //name-item
	BSTR m_strCItemsGenNameAddKey; //name-add
	BSTR m_strCItemsGenParaKey; //para
	BSTR m_strCItemsGenParaDefKey; //paras-def
	BSTR m_strCParasGenNodeKey; //paras-gen-node
	BSTR m_strCItemsGenEnableKey; //enable
	BSTR m_strCItemsGenDataKey; //data
	BSTR m_strCItemsGenInterfaceKey; //interface
	BSTR m_strCItemsGenParasMapKey; //paras-map
	BSTR m_strCItemsGenInstKey; //items-gen-inst
	BSTR m_strCItemsGenClassKey; //items-gen-class
	BSTR m_strCMacroItemsGenKey; //macro-items-gen
	BSTR m_strCMacroSelfDefGenKey; //macro-selfdef-gen
	BSTR m_strCGbItemsGenKey; //gb-items-gen
	BSTR m_strMacro_IdKey; //macro-id
	BSTR m_strNew_ItemsKey; //new-items
	BSTR m_strClassKey; //class
	BSTR m_strData_TypeKey; //data-type
	BSTR m_strValueKey; //value
	BSTR m_strModeKey; //mode
	BSTR m_strTypeKey; //type
	BSTR m_strFormatKey; //format
	BSTR m_strTextKey; //text
	BSTR m_strText_HeadKey; //text-head
	BSTR m_strText_TailKey; //text-tail
	BSTR m_strId_DataKey; //id-data
	BSTR m_strId_MapKey; //id-map
	BSTR m_strKeepExprKey; //keepexpr
	BSTR m_strName_HeadKey; //name-head
	BSTR m_strName_TailKey; //id-tail
	BSTR m_strID_HeadKey; //id-head
	BSTR m_strID_TailKey; //id-tail

	//character
	BSTR m_strCCharacteristicKey;
	BSTR m_strCMacroCharItemLineDefKey;
	BSTR m_strCMacroCharItemsKey;
	BSTR  m_strAxisModeKey;   //Axis mode:x-y; r-angle
	BSTR  m_strParaIdXbKey;
	BSTR  m_strParaIdYbKey;
	BSTR  m_strParaIdXeKey;
	BSTR  m_strParaIdYeKey;
	BSTR  m_strParaIdXsetKey;
	BSTR  m_strParaIdYsetKey;
	BSTR  m_strParaIdXactKey;
	BSTR  m_strParaIdYactKey;
	BSTR  m_strParaIdFlagActKey;

	BSTR  m_strParaIdSearchXbKey;
	BSTR  m_strParaIdSearchYbKey;
	BSTR  m_strParaIdSearchActbKey;
	BSTR  m_strParaIdSearchXeKey;
	BSTR  m_strParaIdSearchYeKey;
	BSTR  m_strParaIdSearchActeKey;
	BSTR  m_strParaIdSearchXcKey;
	BSTR  m_strParaIdSearchYcKey;

	BSTR  m_strCItemRsltExprKey;
	//BSTR  m_strCItemValueRsltKey;
	BSTR  m_strEngineProgIDKey;
	BSTR  m_strCItemsGenCommCmdKey;
	BSTR  m_strCItemsGenSafetyKey;
	BSTR  m_strCItemsGenSysParaEditKey;
	BSTR  m_strCmdIDKey;
	BSTR  m_strRwOptrKey;
	BSTR  m_strRptFillDsKey;

public:
	static BSTR CItemsGenNodeKey()  {   return g_pXmlKeys->m_strCItemsGenNodeKey;  }
	static BSTR CItemsGenDefineKey()  {   return g_pXmlKeys->m_strCItemsGenDefineKey;  }
	static BSTR CItemsGenDataMapKey()  {   return g_pXmlKeys->m_strCItemsGenDataMapKey;  }
	static BSTR CItemsGenDatasetKey()  {   return g_pXmlKeys->m_strCItemsGenDatasetKey;  }
	static BSTR CItemsGenNameItemKey()  {   return g_pXmlKeys->m_strCItemsGenNameItemKey;  }
	static BSTR CItemsGenNameAddKey()  {   return g_pXmlKeys->m_strCItemsGenNameAddKey;  }
	static BSTR CItemsGenParaKey()  {   return g_pXmlKeys->m_strCItemsGenParaKey;  }
	static BSTR CItemsGenParaDefKey()  {   return g_pXmlKeys->m_strCItemsGenParaDefKey;  }
	static BSTR CParasGenNodeKey()  {   return g_pXmlKeys->m_strCParasGenNodeKey;  }
	static BSTR CItemsGenEnableKey()  {   return g_pXmlKeys->m_strCItemsGenEnableKey;  }
	static BSTR CItemsGenDataKey()  {   return g_pXmlKeys->m_strCItemsGenDataKey;  }
	static BSTR CItemsGenInterfaceKey()  {   return g_pXmlKeys->m_strCItemsGenInterfaceKey;  }
	static BSTR CItemsGenParasMapKey()  {   return g_pXmlKeys->m_strCItemsGenParasMapKey;  }
	static BSTR CItemsGenInstKey()  {   return g_pXmlKeys->m_strCItemsGenInstKey;  }
	static BSTR CItemsGenClassKey()  {   return g_pXmlKeys->m_strCItemsGenClassKey;  }
	static BSTR CMacroItemsGenKey()  {   return g_pXmlKeys->m_strCMacroItemsGenKey;  }
	static BSTR CMacroSelfDefGenKey()  {   return g_pXmlKeys->m_strCMacroSelfDefGenKey;  }
	static BSTR CGbItemsGenKey()  {   return g_pXmlKeys->m_strCGbItemsGenKey;  }
	static BSTR Macro_IdKey()  {   return g_pXmlKeys->m_strMacro_IdKey;  }
	static BSTR New_ItemsKey()  {   return g_pXmlKeys->m_strNew_ItemsKey;  }
	static BSTR ClassKey()  {   return g_pXmlKeys->m_strClassKey;  }
	static BSTR Data_TypeKey()  {   return g_pXmlKeys->m_strData_TypeKey;  }
	static BSTR ValueKey()  {   return g_pXmlKeys->m_strValueKey;  }
	static BSTR ModeKey()  {   return g_pXmlKeys->m_strModeKey;  }
	static BSTR TypeKey()  {   return g_pXmlKeys->m_strTypeKey;  }
	static BSTR FormatKey()  {   return g_pXmlKeys->m_strFormatKey;  }
	static BSTR TextKey()  {   return g_pXmlKeys->m_strTextKey;  }
	static BSTR Text_HeadKey()  {   return g_pXmlKeys->m_strText_HeadKey;  }
	static BSTR Text_TailKey()  {   return g_pXmlKeys->m_strText_TailKey;  }
	static BSTR Id_DataKey()  {   return g_pXmlKeys->m_strId_DataKey;  }
	static BSTR Id_MapKey()  {   return g_pXmlKeys->m_strId_MapKey;  }
	static BSTR Name_HeadKey()  {   return g_pXmlKeys->m_strName_HeadKey;  }
	static BSTR Name_TailKey()  {   return g_pXmlKeys->m_strName_TailKey;  }
	static BSTR ID_HeadKey()  {   return g_pXmlKeys->m_strID_HeadKey;  }
	static BSTR ID_TailKey()  {   return g_pXmlKeys->m_strID_TailKey;  }
	static BSTR CItemsGenCharItemLineKey()  {   return g_pXmlKeys->m_strCMacroCharItemLineDefKey;  }
	static BSTR CItemRsltExprKey()  {   return g_pXmlKeys->m_strCItemRsltExprKey;  }
	//static BSTR CItemValueRsltKey()  {   return g_pXmlKeys->m_strCItemValueRsltKey;  }
	static BSTR EngineProgIDKey()  {   return g_pXmlKeys->m_strEngineProgIDKey;  }
	static BSTR CItemsGenCommCmdKey()  {   return g_pXmlKeys->m_strCItemsGenCommCmdKey;  }
	static BSTR CItemsGenSafetyKey()  {   return g_pXmlKeys->m_strCItemsGenSafetyKey;  }
	static BSTR CItemsGenSysParaEditKey()  {   return g_pXmlKeys->m_strCItemsGenSysParaEditKey;  }
	static BSTR CmdIDKey()  {   return g_pXmlKeys->m_strCmdIDKey;  }
	static BSTR RwOptrKey()  {   return g_pXmlKeys->m_strRwOptrKey;  }
	static BSTR RptFillDsKey()  {   return g_pXmlKeys->m_strRptFillDsKey;  }
};

class CGbItemsGenRuleDefMngrConstGlobal
{
private:
	CGbItemsGenRuleDefMngrConstGlobal();
	virtual ~CGbItemsGenRuleDefMngrConstGlobal();

public:
	static CGbItemsGenRuleDefMngrConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CGbItemsGenRuleDefMngrConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
