//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttTestCtrlFrameCfgMngrGlobal.h

#pragma once

#include "../../../../../Module/BaseClass/ExBaseList.h"

#define MngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define MngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define MNGRCLASSID_CSTTFRAMECONFIG       (MngrCLASSID_EXLISTCLASS + 0X00000000)
#define MNGRCLASSID_CSTTFRAME_FONT       (MngrCLASSID_BASECLASS + 0X00000001)
#define MNGRCLASSID_CSTTFRAME_MENUS       (MngrCLASSID_EXLISTCLASS + 0X00000002)
#define MNGRCLASSID_CSTTFRAME_MENU       (MngrCLASSID_EXLISTCLASS + 0X00000003)
#define MNGRCLASSID_CSTTFRAME_ITEM       (MngrCLASSID_BASECLASS + 0X00000004)
#define MNGRCLASSID_CSTTFRAME_TOOLBAR       (MngrCLASSID_EXLISTCLASS + 0X00000005)
#define MNGRCLASSID_CSTTFRAME_PANAL       (MngrCLASSID_EXLISTCLASS + 0X00000006)
#define MNGRCLASSID_CSTTFRAME_BUTTON       (MngrCLASSID_BASECLASS + 0X00000007)
#define MNGRCLASSID_CSTTFRAME_DATA       (MngrCLASSID_BASECLASS + 0X00000008)
#define MNGRCLASSID_CSTTFRAME_GBTREE       (MngrCLASSID_EXLISTCLASS + 0X00000009)
#define MNGRCLASSID_CSTTFRAME_SIZE       (MngrCLASSID_BASECLASS + 0X0000000A)
#define MNGRCLASSID_CSTTFRAME_MACROPARAVIEW       (MngrCLASSID_EXLISTCLASS + 0X0000000B)
#define MNGRCLASSID_CSTTFRAME_REPORTVIEW       (MngrCLASSID_EXLISTCLASS + 0X0000000C)
#define MNGRCLASSID_CSTTFRAME_RIGHTPANES       (MngrCLASSID_EXLISTCLASS + 0X0000000D)
#define MNGRCLASSID_CSTTFRAME_STATUSBAR       (MngrCLASSID_EXLISTCLASS + 0X0000000E)
#define MNGRCLASSID_CSTTFRAME_RESULTBAR       (MngrCLASSID_EXLISTCLASS + 0X0000000F)

#define MNGRCLASSID_CSTTFRAME_GLOBALDATAS       (MngrCLASSID_EXLISTCLASS + 0X00000001A)
#define MNGRCLASSID_CSTTFRAME_GLOBALDATA       (MngrCLASSID_BASECLASS + 0X00000001B)



class CSttTestCtrlFrameCfgMngrXmlRWKeys : public CXmlRWKeys
{
protected:
	CSttTestCtrlFrameCfgMngrXmlRWKeys();
	virtual ~CSttTestCtrlFrameCfgMngrXmlRWKeys();
	static long g_nMngrRef;

public:
	static CSttTestCtrlFrameCfgMngrXmlRWKeys* g_pXmlKeys;
	static CSttTestCtrlFrameCfgMngrXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCSttFrame_StatusBarKey; //status-bar
	BSTR m_strCSttFrame_ResultBarKey; //result-bar
	BSTR m_strCSttFrame_RightPanesKey; //right-panes
	BSTR m_strCSttFrame_ReportViewKey; //report-view
	BSTR m_strCSttFrame_MacroParaViewKey; //macro-para-view
	BSTR m_strCSttFrame_SizeKey; //size
	BSTR m_strCSttFrame_GbTreeKey; //gb-tree
	BSTR m_strCSttFrame_DataKey; //data
	BSTR m_strCSttFrame_ButtonKey; //button
	BSTR m_strCSttFrame_PanalKey; //panal
	BSTR m_strCSttFrame_ToolBarKey; //tool-bar
	BSTR m_strCSttFrame_ItemKey; //item
	BSTR m_strCSttFrame_MenuKey; //menu
	BSTR m_strCSttFrame_MenusKey; //menus
	BSTR m_strCSttFrame_FontKey; //font
	BSTR m_strCSttFrameConfigKey; //frame-config
	BSTR m_strWidthKey; //width
	BSTR m_strHeightKey; //height
	BSTR m_strBoldKey; //bold
	BSTR m_strUseKey; //use
	BSTR m_strIcon_PosKey; //icon-pos
	BSTR m_strTypeKey; //type
	BSTR m_strIconKey; //icon
	BSTR m_strEnableStateKey; //enable-state
	BSTR m_strLogDebugInforKey; //log-debug-infor
	BSTR m_strFrameBtnGapKey; //frame-btn-gap
	BSTR m_strSelMacroShow;//sel-macro-show

	BSTR m_strCSttFrame_GlobalDataKey; //global-data
	BSTR m_strCSttFrame_GlobalDatasKey; //global-datas
	BSTR m_strValueKey; //value
	BSTR m_strData_TypeKey; //data-type
	BSTR m_strMacro_UseKey; //macro-use




public:
	static BSTR CSttFrame_StatusBarKey()  {   return g_pXmlKeys->m_strCSttFrame_StatusBarKey;  }
	static BSTR CSttFrame_ResultBarKey()  {   return g_pXmlKeys->m_strCSttFrame_ResultBarKey;  }
	static BSTR CSttFrame_RightPanesKey()  {   return g_pXmlKeys->m_strCSttFrame_RightPanesKey;  }
	static BSTR CSttFrame_ReportViewKey()  {   return g_pXmlKeys->m_strCSttFrame_ReportViewKey;  }
	static BSTR CSttFrame_MacroParaViewKey()  {   return g_pXmlKeys->m_strCSttFrame_MacroParaViewKey;  }
	static BSTR CSttFrame_SizeKey()  {   return g_pXmlKeys->m_strCSttFrame_SizeKey;  }
	static BSTR CSttFrame_GbTreeKey()  {   return g_pXmlKeys->m_strCSttFrame_GbTreeKey;  }
	static BSTR CSttFrame_DataKey()  {   return g_pXmlKeys->m_strCSttFrame_DataKey;  }
	static BSTR CSttFrame_ButtonKey()  {   return g_pXmlKeys->m_strCSttFrame_ButtonKey;  }
	static BSTR CSttFrame_PanalKey()  {   return g_pXmlKeys->m_strCSttFrame_PanalKey;  }
	static BSTR CSttFrame_ToolBarKey()  {   return g_pXmlKeys->m_strCSttFrame_ToolBarKey;  }
	static BSTR CSttFrame_ItemKey()  {   return g_pXmlKeys->m_strCSttFrame_ItemKey;  }
	static BSTR CSttFrame_MenuKey()  {   return g_pXmlKeys->m_strCSttFrame_MenuKey;  }
	static BSTR CSttFrame_MenusKey()  {   return g_pXmlKeys->m_strCSttFrame_MenusKey;  }
	static BSTR CSttFrame_FontKey()  {   return g_pXmlKeys->m_strCSttFrame_FontKey;  }
	static BSTR CSttFrameConfigKey()  {   return g_pXmlKeys->m_strCSttFrameConfigKey;  }
	static BSTR WidthKey()  {   return g_pXmlKeys->m_strWidthKey;  }
	static BSTR HeightKey()  {   return g_pXmlKeys->m_strHeightKey;  }
	static BSTR BoldKey()  {   return g_pXmlKeys->m_strBoldKey;  }
	static BSTR UseKey()  {   return g_pXmlKeys->m_strUseKey;  }
	static BSTR Icon_PosKey()  {   return g_pXmlKeys->m_strIcon_PosKey;  }
	static BSTR TypeKey()  {   return g_pXmlKeys->m_strTypeKey;  }
	static BSTR IconKey()  {   return g_pXmlKeys->m_strIconKey;  }

	static BSTR CSttFrame_GlobalDataKey()  {   return g_pXmlKeys->m_strCSttFrame_GlobalDataKey;  }
	static BSTR CSttFrame_GlobalDatasKey()  {   return g_pXmlKeys->m_strCSttFrame_GlobalDatasKey;  }
	static BSTR Data_TypeKey()  {   return g_pXmlKeys->m_strData_TypeKey;  }
	static BSTR ValueKey()  {   return g_pXmlKeys->m_strValueKey;  }
	
	static BSTR MacroUseKey()  {   return g_pXmlKeys->m_strMacro_UseKey;  }
};



class CSttTestCtrlFrameCfgMngrConstGlobal
{
private:
	CSttTestCtrlFrameCfgMngrConstGlobal();
	virtual ~CSttTestCtrlFrameCfgMngrConstGlobal();

public:
	static CSttTestCtrlFrameCfgMngrConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CSttTestCtrlFrameCfgMngrConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
