//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIBaseGlobal.cpp

#include "stdafx.h"
#include "UIBaseGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CUIBaseXmlRWKeys

CUIBaseXmlRWKeys* CUIBaseXmlRWKeys::g_pXmlKeys = NULL;
long CUIBaseXmlRWKeys::g_nUIRef = 0;


CUIBaseXmlRWKeys::CUIBaseXmlRWKeys()
{
	m_strCUIWndRegisterKey = L"register";
	m_strCUIBaseFileTypePostfixKey = L"file-postfix";
	m_strCUIBaseFileTypeKey = L"file-type";
	m_strCUIBaseFileTypesKey = L"file-types";
	m_strCUIWndFileMngrKey = L"file-mngr";
	m_strCUIWndPagesDefKey = L"pages";
	m_strCUIWndPageDefKey = L"page";
	m_strCUIWndMainKey = L"main";
	m_strCUIWndPageKey = L"page";
	m_strCUIWndLayerKey = L"layer";
	m_strCUIWindowListKey = L"";
	m_strCUIWndTimeKey = L"timewnd";
	m_strCUIWndStaticTextKey = L"text";
	m_strCUIWndRectKey = L"rect";
	m_strCUIWndEditKey = L"edit";
	m_strCUIWndDateTimeCtrlKey = L"datetime";
	m_strCUIWndComboBoxKey = L"combobox";
	m_strCUIWndListBoxKey = L"listbox";
	m_strCUIWndCheckBoxKey = L"checkbox";
	m_strCUIWndButtonKey = L"button";
	m_strCUIWndBitmapKey = L"bitmap";
	m_strCUIWndListCtrlKey = L"listctrl";
	m_strCUIEventsKey = L"events";
	m_strCUIEventKey = L"";
	m_strCUIBaseAxisesKey = L"axis";
	m_strCUIBaseAxisKey = L"axis";
	m_strCUIBaseItemsKey = L"items";
	m_strCUIBaseItemKey = L"item";
	m_strCUIBaseRularKey = L"ruler";
	m_strCUIBaseFontKey = L"font";
	m_strCUIWindowBaseKey = L"";
	m_strCUIWindowTextKey = L"wnd-text";
	m_strForeColorKey = L"fore-color";
	m_strBackColorKey = L"back-color";
	m_strDisableColorKey = L"disable-color";
	m_strHighLightColorKey = L"high-light-color";
	m_strTextKey = L"text";
	m_strTabOrderKey = L"tab";
	m_strTopKey = L"top";
	m_strLeftKey = L"left";
	m_strWidthKey = L"width";
	m_strHeightKey = L"height";
	m_strAccelMsgKey = L"accel-msg";
	m_strShowKey = L"show";
	m_strEnableKey = L"enable";
	m_strSysTimerIDKey = L"sys-timer-id";
	m_strSysOptrIDKey = L"sys-optr-id";
	m_strBkColorKey = L"bk-color";
	m_strFrmTopLeftColorKey = L"frm-tl-color";
	m_strFrmRightBottomColorKey = L"frm-rb-color";
	m_strFrmSizeKey = L"frm-size";
	m_strSizeKey = L"size";
	m_strItalicKey = L"italic";
	m_strBoldKey = L"bold";
	m_strColorKey = L"color";
	m_strEscapementKey = L"escapement";
	m_strScaleColorKey = L"scale-color";
	m_strScaleShadowColorKey = L"scale-shadow-color";
	m_strTenthScaleColorKey = L"tenth-scale-color";
	m_strBorderColorKey = L"border-color";
	m_strTextColorKey = L"TextColor";
	m_strDrawBorderKey = L"draw-border";
	m_strDrawHalfScaleKey = L"draw-half-scale";
	m_strDrawTenthScaleKey = L"draw-tenth-scale";
	m_strRangeMinKey = L"range-min";
	m_strRangeMaxKey = L"range-max";
	m_strScaleTypeKey = L"scale-type";
	m_strScaleMinPixelKey = L"scale-min-pixel";
	m_strUseHalfScaleKey = L"use-half-scale";
	m_strUseTenthScaleKey = L"use-tenth-scale";
	m_strBkColorFromKey = L"back-color-from";
	m_strBkColorToKey = L"back-color-to";
	m_strGridColorKey = L"grid-color";
	m_strCenterColorKey = L"center-color";
	m_strAxisColorKey = L"axis-color";
	m_strFrameColorKey = L"frame-color";
	m_strLockHorVerScaleKey = L"lock-hor-ver-scale";
	m_strWndStateKey = L"wnd-state";
	m_strSysMsgKey = L"sys-msg";
	m_strScriptKey = L"script";
	m_strNormalBmpFileKey = L"normal-file";
	m_strDisablelBmpFileKey = L"disable-file";
	m_strClickBmpFileKey = L"click-file";
	m_strActiveBmpFileKey = L"active-file";
	m_strCurrIndexKey = L"curr-index";
	m_strSortKey = L"sort";
	m_strSourceKey = L"source";
	m_strFormartKey = L"formart";
	m_strUseCurTimeKey = L"use-cur-time";
	m_strYearKey = L"year";
	m_strDayKey = L"day";
	m_strHourKey = L"hour";
	m_strMinuteKey = L"minute";
	m_strSecondKey = L"second";
	m_strFormatKey = L"format";
	m_strPenColorKey = L"pen-color";
	m_strPenStypeKey = L"pen-stype";
	m_strPenWidthKey = L"pen-width";
	m_strBrushColorKey = L"brush-color";
	m_strShowChildrenKey = L"show-children";
	m_strBringToTopKey = L"bring-to-top";
	m_strBkBmpFileKey = L"bk-bmp-file";
	m_strBorderKey = L"border";
	m_strTabSysMsgKey = L"tab-sys-msg";
	m_strStartPageKey = L"start-page";
	m_strUseFrameKey = L"use-frame";
	m_strPageFileKey = L"page-file";
	m_strBkActiveColorKey = L"bk-active-color";
	m_strBkDisableColorKey = L"bk-disable-color";
	m_strTreeViewWidthRateKey = L"tree-view-width-rate";
	m_strTreeViewWidthMaxKey = L"tree-view-width-max";
	m_strRootPathKey = L"root-path";
	m_strOnlySearchMainTypeFileKey = L"only-search-main";

	m_strExeKey = L"exe";
	m_strRootNameKey = L"name_root";
	m_strRunModeKey = L"run-mode";

	m_strTransparentKey = L"transparent";
	m_strTransMaskColorKey = L"mask-color";

}

CUIBaseXmlRWKeys::~CUIBaseXmlRWKeys()
{
}

CUIBaseXmlRWKeys* CUIBaseXmlRWKeys::Create()
{
	g_nUIRef++;

	if (g_nUIRef == 1)
	{
		g_pXmlKeys = new CUIBaseXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CUIBaseXmlRWKeys::Release()
{
	g_nUIRef--;

	if (g_nUIRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CUIBaseConstGlobal

long CUIBaseConstGlobal::g_nGlobalRef = 0;
CUIBaseConstGlobal* CUIBaseConstGlobal::g_pGlobal = NULL;


CUIBaseConstGlobal::CUIBaseConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CUIBaseConstGlobal::~CUIBaseConstGlobal()
{
}

CUIBaseConstGlobal* CUIBaseConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CUIBaseConstGlobal();
	}

	return g_pGlobal;
}

void CUIBaseConstGlobal::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()
//	m_oFuncParaDataTypes.AddNew(g_pstrVariableType_CString, g_pstrVariableType_CString);

//定义全局常量，例如  static CString g_pstrVariableType_CString;
