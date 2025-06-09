//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIBaseGlobal.h

#pragma once

#include "ExBaseList.h"
#include "..\BaseClass\DIB.h"
#include "..\EpotoInterface\EpotoInterface.h"

#define UICLASSID_BASECLASS         (CLASSID_BASECLASS      + 0X00C10000)
#define UICLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS    + 0X00C10000)
#define UICLASSID_WNDBASECLASS      (UICLASSID_EXLISTCLASS  + 0X00020000)
#define UICLASSID_WNDLISTCLASS      (UICLASSID_WNDBASECLASS + 0X00040000)

#define UICLASSID_CUIWINDOWTEXT       (UICLASSID_BASECLASS + 0X00000000)
#define UICLASSID_CUIWINDOWBASE       (UICLASSID_EXLISTCLASS + 0X00000001)
#define UICLASSID_CUIBASEFONT         (UICLASSID_BASECLASS + 0X00000002)
#define UICLASSID_CUIBASERULAR        (UICLASSID_BASECLASS + 0X00000003)
#define UICLASSID_CUIBASEAXIS         (UICLASSID_EXLISTCLASS + 0X00000004)
#define UICLASSID_CUIBASEAXISES       (UICLASSID_EXLISTCLASS + 0X00000005)
#define UICLASSID_CUIEVENT            (UICLASSID_BASECLASS + 0X00000006)
#define UICLASSID_CUIEVENTS           (UICLASSID_EXLISTCLASS + 0X00000007)
#define UICLASSID_CUIBASEITEM           (UICLASSID_EXLISTCLASS + 0X00000008)
#define UICLASSID_CUIBASEITEMS           (UICLASSID_EXLISTCLASS + 0X00000009)

#define UICLASSID_CUIWNDBITMAP        (UICLASSID_WNDBASECLASS + 0X00000008)
#define UICLASSID_CUIWNDBUTTON        (UICLASSID_WNDBASECLASS + 0X00000009)
#define UICLASSID_CUIWNDCHECKBOX      (UICLASSID_WNDBASECLASS + 0X0000000A)
#define UICLASSID_CUIWNDCOMBOBOX      (UICLASSID_WNDBASECLASS + 0X0000000B)
#define UICLASSID_CUIWNDDATETIMECTRL  (UICLASSID_WNDBASECLASS + 0X0000000C)
#define UICLASSID_CUIWNDEDIT          (UICLASSID_WNDBASECLASS + 0X0000000D)
#define UICLASSID_CUIWNDRECT          (UICLASSID_WNDBASECLASS + 0X0000000E)
#define UICLASSID_CUIWNDSTATICTEXT    (UICLASSID_WNDBASECLASS + 0X0000000F)
#define UICLASSID_CUIWNDTIME          (UICLASSID_WNDBASECLASS + 0X00000010)
#define UICLASSID_CUIWNDLISTCTRL          (UICLASSID_WNDBASECLASS + 0X00000011)
#define UICLASSID_CUIWNDLISTBOX          (UICLASSID_WNDBASECLASS + 0X00000012)

#define UICLASSID_CUIWINDOWLIST       (UICLASSID_WNDLISTCLASS + 0X00000011)
#define UICLASSID_CUIWNDLAYER         (UICLASSID_WNDLISTCLASS + 0X00000012)
#define UICLASSID_CUIWNDPAGE          (UICLASSID_WNDLISTCLASS + 0X00000013)
#define UICLASSID_CUIWNDMAIN          (UICLASSID_WNDLISTCLASS + 0X00000014)
#define UICLASSID_CUIWNDPAGEDEF       (UICLASSID_BASECLASS    + 0X00000015)
#define UICLASSID_CUIWNDPAGESDEF   (UICLASSID_EXLISTCLASS  + 0X00000016)
#define UICLASSID_CUIWNDFILEMNGR       (UICLASSID_WNDBASECLASS + 0X00000017)
#define UICLASSID_CUIBASEFILETYPES       (UICLASSID_EXLISTCLASS + 0X00000018)
#define UICLASSID_CUIBASEFILETYPE       (UICLASSID_EXLISTCLASS + 0X00000019)
#define UICLASSID_CUIBASEFILETYPEPOSTFIX       (UICLASSID_BASECLASS + 0X00000020)
#define UICLASSID_CUIWNDREGISTER        (UICLASSID_WNDBASECLASS + 0X00000021)

inline BOOL UI_IsUIWndListClassID(UINT nClassID)
{
	return ((nClassID & UICLASSID_WNDLISTCLASS) == UICLASSID_WNDLISTCLASS);
}
inline BOOL UI_IsUIWndClassID(UINT nClassID)
{
	if (UI_IsUIWndListClassID(nClassID))
	{
		return FALSE;
	}

	return ((nClassID & UICLASSID_WNDBASECLASS) == UICLASSID_WNDBASECLASS);
}
inline BOOL UI_IsUIWndClass(CExBaseObject *pObj)
{
	ASSERT (pObj != NULL);
	return UI_IsUIWndClassID(pObj->GetClassID());
}
inline BOOL UI_IsUIWndListClassID(CExBaseObject *pObj)
{
	ASSERT (pObj != NULL);
	return UI_IsUIWndListClassID(pObj->GetClassID());
}

class CUIBaseXmlRWKeys : public CDataMngrXmlRWKeys
{
protected:
	CUIBaseXmlRWKeys();
	virtual ~CUIBaseXmlRWKeys();
	static long g_nUIRef;

public:
	static CUIBaseXmlRWKeys* g_pXmlKeys;
	static CUIBaseXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCUIWndRegisterKey; //register
	BSTR m_strCUIBaseFileTypePostfixKey; //file-type-file
	BSTR m_strCUIBaseFileTypeKey; //file-type
	BSTR m_strCUIBaseFileTypesKey; //file-types
	BSTR m_strCUIWndFileMngrKey; //file-mngr
	BSTR m_strCUIWndPagesDefKey; //page-ref-mngr
	BSTR m_strCUIWndPageDefKey; //page-ref
	BSTR m_strCUIWndMainKey; //main
	BSTR m_strCUIWndPageKey; //page
	BSTR m_strCUIWndLayerKey; //layer
	BSTR m_strCUIWindowListKey; //
	BSTR m_strCUIWndTimeKey; //timewnd
	BSTR m_strCUIWndStaticTextKey; //text
	BSTR m_strCUIWndRectKey; //rect
	BSTR m_strCUIWndEditKey; //edit
	BSTR m_strCUIWndListCtrlKey; //listctrl
	BSTR m_strCUIWndDateTimeCtrlKey; //datetime
	BSTR m_strCUIWndComboBoxKey; //combobox
	BSTR m_strCUIWndCheckBoxKey; //checkbox
	BSTR m_strCUIWndButtonKey; //button
	BSTR m_strCUIWndBitmapKey; //bitmap
	BSTR m_strCUIWndListBoxKey; //listbox
	BSTR m_strCUIEventsKey; //
	BSTR m_strCUIEventKey; //
	BSTR m_strCUIBaseAxisesKey; //axis
	BSTR m_strCUIBaseAxisKey; //axis
	BSTR m_strCUIBaseItemKey; //item
	BSTR m_strCUIBaseItemsKey; //items
	BSTR m_strCUIBaseRularKey; //ruler
	BSTR m_strCUIBaseFontKey; //font
	BSTR m_strCUIWindowBaseKey; //
	BSTR m_strCUIWindowTextKey; //wtxt
	BSTR m_strForeColorKey; //fore-color
	BSTR m_strBackColorKey; //back-color
	BSTR m_strDisableColorKey; //disable-color
	BSTR m_strHighLightColorKey; //high-light-color
	BSTR m_strTextKey; //text
	BSTR m_strTabOrderKey; //tab
	BSTR m_strTopKey; //top
	BSTR m_strLeftKey; //left
	BSTR m_strWidthKey; //width
	BSTR m_strHeightKey; //height
	BSTR m_strAccelMsgKey; //accel-msg
	BSTR m_strShowKey; //show
	BSTR m_strEnableKey; //enable
	BSTR m_strSysTimerIDKey; //sys-timer-id
	BSTR m_strSysOptrIDKey; //sys-optr-id
	BSTR m_strBkColorKey; //bk-color
	BSTR m_strFrmTopLeftColorKey; //frm-tl-color
	BSTR m_strFrmRightBottomColorKey; //frm-rb-color
	BSTR m_strFrmSizeKey; //frm-size
	BSTR m_strSizeKey; //size
	BSTR m_strItalicKey; //italic
	BSTR m_strBoldKey; //bold
	BSTR m_strColorKey; //color
	BSTR m_strEscapementKey; //escapement
	BSTR m_strScaleColorKey; //scale-color
	BSTR m_strScaleShadowColorKey; //scale-shadow-color
	BSTR m_strTenthScaleColorKey; //tenth-scale-color
	BSTR m_strBorderColorKey; //border-color
	BSTR m_strTextColorKey; //TextColor
	BSTR m_strDrawBorderKey; //draw-border
	BSTR m_strDrawHalfScaleKey; //draw-half-scale
	BSTR m_strDrawTenthScaleKey; //draw-tenth-scale
	BSTR m_strRangeMinKey; //range-min
	BSTR m_strRangeMaxKey; //range-max
	BSTR m_strScaleTypeKey; //scale-type
	BSTR m_strScaleMinPixelKey; //scale-min-pixel
	BSTR m_strUseHalfScaleKey; //use-half-scale
	BSTR m_strUseTenthScaleKey; //use-tenth-scale
	BSTR m_strBkColorFromKey; //back-color-from
	BSTR m_strBkColorToKey; //back-color-to
	BSTR m_strGridColorKey; //grid-color
	BSTR m_strCenterColorKey; //center-color
	BSTR m_strAxisColorKey; //axis-color
	BSTR m_strFrameColorKey; //frame-color
	BSTR m_strLockHorVerScaleKey; //lock-hor-ver-scale
	BSTR m_strWndStateKey; //wnd-state
	BSTR m_strSysMsgKey; //sys-msg
	BSTR m_strScriptKey; //script
	BSTR m_strNormalBmpFileKey; //normal-bmp-file
	BSTR m_strDisablelBmpFileKey; //disable-bmp-file
	BSTR m_strClickBmpFileKey; //click-bmp-file
	BSTR m_strActiveBmpFileKey; //active-bmp-file
	BSTR m_strCurrIndexKey; //curr-index
	BSTR m_strSortKey; //sort
	BSTR m_strSourceKey; //source
	BSTR m_strFormartKey; //formart
	BSTR m_strUseCurTimeKey; //use-cur-time
	BSTR m_strYearKey; //year
	BSTR m_strDayKey; //day
	BSTR m_strHourKey; //hour
	BSTR m_strMinuteKey; //minute
	BSTR m_strSecondKey; //second
	BSTR m_strFormatKey; //format
	BSTR m_strPenColorKey; //pen-color
	BSTR m_strPenStypeKey; //pen-stype
	BSTR m_strPenWidthKey; //pen-width
	BSTR m_strBrushColorKey; //brush-color
	BSTR m_strShowChildrenKey; //show-children
	BSTR m_strBringToTopKey; //bring-to-top
	BSTR m_strBkBmpFileKey; //bk-bmp-file
	BSTR m_strBorderKey; //border
	BSTR m_strTabSysMsgKey; //tab-sys-msg
	BSTR m_strStartPageKey; //title
	BSTR m_strUseFrameKey; //use-frame
	BSTR m_strPageFileKey; //PageFileKey
	BSTR m_strBkActiveColorKey;//bk-active-color
	BSTR m_strBkDisableColorKey;//bk-disable-color
	BSTR m_strTreeViewWidthRateKey; //tree-view-width-rate
	BSTR m_strTreeViewWidthMaxKey; //tree-view-width-max
	BSTR m_strRootPathKey; //root-path
	BSTR m_strOnlySearchMainTypeFileKey; //only-search-main
	BSTR m_strExeKey; //exe
	BSTR m_strRootNameKey; //name_root
	BSTR m_strRunModeKey; //run-mode
	BSTR m_strTransparentKey; //run-mode
	BSTR m_strTransMaskColorKey; //run-mode


public:
	static BSTR CUIWndRegisterKey()  {   return g_pXmlKeys->m_strCUIWndRegisterKey;  }
	static BSTR CUIBaseFileTypePostfixKey()  {   return g_pXmlKeys->m_strCUIBaseFileTypePostfixKey;  }
	static BSTR CUIBaseFileTypeKey()  {   return g_pXmlKeys->m_strCUIBaseFileTypeKey;  }
	static BSTR CUIBaseFileTypesKey()  {   return g_pXmlKeys->m_strCUIBaseFileTypesKey;  }
	static BSTR CUIWndFileMngrKey()  {   return g_pXmlKeys->m_strCUIWndFileMngrKey;  }
	static BSTR CUIWndPagesDefKey()  {   return g_pXmlKeys->m_strCUIWndPagesDefKey;  }
	static BSTR CUIWndPageDefKey()  {   return g_pXmlKeys->m_strCUIWndPageDefKey;  }
	static BSTR CUIWndMainKey()  {   return g_pXmlKeys->m_strCUIWndMainKey;  }
	static BSTR CUIWndPageKey()  {   return g_pXmlKeys->m_strCUIWndPageKey;  }
	static BSTR CUIWndLayerKey()  {   return g_pXmlKeys->m_strCUIWndLayerKey;  }
	static BSTR CUIWindowListKey()  {   return g_pXmlKeys->m_strCUIWindowListKey;  }
	static BSTR CUIWndTimeKey()  {   return g_pXmlKeys->m_strCUIWndTimeKey;  }
	static BSTR CUIWndStaticTextKey()  {   return g_pXmlKeys->m_strCUIWndStaticTextKey;  }
	static BSTR CUIWndRectKey()  {   return g_pXmlKeys->m_strCUIWndRectKey;  }
	static BSTR CUIWndEditKey()  {   return g_pXmlKeys->m_strCUIWndEditKey;  }
	static BSTR CUIWndListBoxKey()  {   return g_pXmlKeys->m_strCUIWndListBoxKey;  }
	static BSTR CUIWndListCtrlKey()  {   return g_pXmlKeys->m_strCUIWndListCtrlKey;  }
	static BSTR CUIWndDateTimeCtrlKey()  {   return g_pXmlKeys->m_strCUIWndDateTimeCtrlKey;  }
	static BSTR CUIWndComboBoxKey()  {   return g_pXmlKeys->m_strCUIWndComboBoxKey;  }
	static BSTR CUIWndCheckBoxKey()  {   return g_pXmlKeys->m_strCUIWndCheckBoxKey;  }
	static BSTR CUIWndButtonKey()  {   return g_pXmlKeys->m_strCUIWndButtonKey;  }
	static BSTR CUIWndBitmapKey()  {   return g_pXmlKeys->m_strCUIWndBitmapKey;  }
	static BSTR CUIEventsKey()  {   return g_pXmlKeys->m_strCUIEventsKey;  }
	static BSTR CUIEventKey()  {   return g_pXmlKeys->m_strCUIEventKey;  }
	static BSTR CUIBaseItemKey()  {   return g_pXmlKeys->m_strCUIBaseItemKey;  }
	static BSTR CUIBaseItemsKey()  {   return g_pXmlKeys->m_strCUIBaseItemsKey;  }
	static BSTR CUIBaseAxisesKey()  {   return g_pXmlKeys->m_strCUIBaseAxisesKey;  }
	static BSTR CUIBaseAxisKey()  {   return g_pXmlKeys->m_strCUIBaseAxisKey;  }
	static BSTR CUIBaseRularKey()  {   return g_pXmlKeys->m_strCUIBaseRularKey;  }
	static BSTR CUIBaseFontKey()  {   return g_pXmlKeys->m_strCUIBaseFontKey;  }
	static BSTR CUIWindowBaseKey()  {   return g_pXmlKeys->m_strCUIWindowBaseKey;  }
	static BSTR CUIWindowTextKey()  {   return g_pXmlKeys->m_strCUIWindowTextKey;  }
	static BSTR ForeColorKey()  {   return g_pXmlKeys->m_strForeColorKey;  }
	static BSTR BackColorKey()  {   return g_pXmlKeys->m_strBackColorKey;  }
	static BSTR DisableColorKey()  {   return g_pXmlKeys->m_strDisableColorKey;  }
	static BSTR HighLightColorKey()  {   return g_pXmlKeys->m_strHighLightColorKey;  }
	static BSTR TextKey()  {   return g_pXmlKeys->m_strTextKey;  }
	static BSTR TabOrderKey()  {   return g_pXmlKeys->m_strTabOrderKey;  }
	static BSTR TopKey()  {   return g_pXmlKeys->m_strTopKey;  }
	static BSTR LeftKey()  {   return g_pXmlKeys->m_strLeftKey;  }
	static BSTR WidthKey()  {   return g_pXmlKeys->m_strWidthKey;  }
	static BSTR HeightKey()  {   return g_pXmlKeys->m_strHeightKey;  }
	static BSTR AccelMsgKey()  {   return g_pXmlKeys->m_strAccelMsgKey;  }
	static BSTR ShowKey()  {   return g_pXmlKeys->m_strShowKey;  }
	static BSTR EnableKey()  {   return g_pXmlKeys->m_strEnableKey;  }
	static BSTR SysTimerIDKey()  {   return g_pXmlKeys->m_strSysTimerIDKey;  }
	static BSTR SysOptrIDKey()  {   return g_pXmlKeys->m_strSysOptrIDKey;  }
	static BSTR BkColorKey()  {   return g_pXmlKeys->m_strBkColorKey;  }
	static BSTR FrmTopLeftColorKey()  {   return g_pXmlKeys->m_strFrmTopLeftColorKey;  }
	static BSTR FrmRightBottomColorKey()  {   return g_pXmlKeys->m_strFrmRightBottomColorKey;  }
	static BSTR FrmSizeKey()  {   return g_pXmlKeys->m_strFrmSizeKey;  }
	static BSTR SizeKey()  {   return g_pXmlKeys->m_strSizeKey;  }
	static BSTR ItalicKey()  {   return g_pXmlKeys->m_strItalicKey;  }
	static BSTR BoldKey()  {   return g_pXmlKeys->m_strBoldKey;  }
	static BSTR ColorKey()  {   return g_pXmlKeys->m_strColorKey;  }
	static BSTR EscapementKey()  {   return g_pXmlKeys->m_strEscapementKey;  }
	static BSTR ScaleColorKey()  {   return g_pXmlKeys->m_strScaleColorKey;  }
	static BSTR ScaleShadowColorKey()  {   return g_pXmlKeys->m_strScaleShadowColorKey;  }
	static BSTR TenthScaleColorKey()  {   return g_pXmlKeys->m_strTenthScaleColorKey;  }
	static BSTR BorderColorKey()  {   return g_pXmlKeys->m_strBorderColorKey;  }
	static BSTR TextColorKey()  {   return g_pXmlKeys->m_strTextColorKey;  }
	static BSTR DrawBorderKey()  {   return g_pXmlKeys->m_strDrawBorderKey;  }
	static BSTR DrawHalfScaleKey()  {   return g_pXmlKeys->m_strDrawHalfScaleKey;  }
	static BSTR DrawTenthScaleKey()  {   return g_pXmlKeys->m_strDrawTenthScaleKey;  }
	static BSTR RangeMinKey()  {   return g_pXmlKeys->m_strRangeMinKey;  }
	static BSTR RangeMaxKey()  {   return g_pXmlKeys->m_strRangeMaxKey;  }
	static BSTR ScaleTypeKey()  {   return g_pXmlKeys->m_strScaleTypeKey;  }
	static BSTR ScaleMinPixelKey()  {   return g_pXmlKeys->m_strScaleMinPixelKey;  }
	static BSTR UseHalfScaleKey()  {   return g_pXmlKeys->m_strUseHalfScaleKey;  }
	static BSTR UseTenthScaleKey()  {   return g_pXmlKeys->m_strUseTenthScaleKey;  }
	static BSTR BkColorFromKey()  {   return g_pXmlKeys->m_strBkColorFromKey;  }
	static BSTR BkColorToKey()  {   return g_pXmlKeys->m_strBkColorToKey;  }
	static BSTR GridColorKey()  {   return g_pXmlKeys->m_strGridColorKey;  }
	static BSTR CenterColorKey()  {   return g_pXmlKeys->m_strCenterColorKey;  }
	static BSTR AxisColorKey()  {   return g_pXmlKeys->m_strAxisColorKey;  }
	static BSTR FrameColorKey()  {   return g_pXmlKeys->m_strFrameColorKey;  }
	static BSTR LockHorVerScaleKey()  {   return g_pXmlKeys->m_strLockHorVerScaleKey;  }
	static BSTR WndStateKey()  {   return g_pXmlKeys->m_strWndStateKey;  }
	static BSTR SysMsgKey()  {   return g_pXmlKeys->m_strSysMsgKey;  }
	static BSTR ScriptKey()  {   return g_pXmlKeys->m_strScriptKey;  }
	static BSTR NormalBmpFileKey()  {   return g_pXmlKeys->m_strNormalBmpFileKey;  }
	static BSTR DisablelBmpFileKey()  {   return g_pXmlKeys->m_strDisablelBmpFileKey;  }
	static BSTR ClickBmpFileKey()  {   return g_pXmlKeys->m_strClickBmpFileKey;  }
	static BSTR ActiveBmpFileKey()  {   return g_pXmlKeys->m_strActiveBmpFileKey;  }
	static BSTR CurrIndexKey()  {   return g_pXmlKeys->m_strCurrIndexKey;  }
	static BSTR SortKey()  {   return g_pXmlKeys->m_strSortKey;  }
	static BSTR SourceKey()  {   return g_pXmlKeys->m_strSourceKey;  }
	static BSTR FormartKey()  {   return g_pXmlKeys->m_strFormartKey;  }
	static BSTR UseCurTimeKey()  {   return g_pXmlKeys->m_strUseCurTimeKey;  }
	static BSTR YearKey()  {   return g_pXmlKeys->m_strYearKey;  }
	static BSTR DayKey()  {   return g_pXmlKeys->m_strDayKey;  }
	static BSTR HourKey()  {   return g_pXmlKeys->m_strHourKey;  }
	static BSTR MinuteKey()  {   return g_pXmlKeys->m_strMinuteKey;  }
	static BSTR SecondKey()  {   return g_pXmlKeys->m_strSecondKey;  }
	static BSTR FormatKey()  {   return g_pXmlKeys->m_strFormatKey;  }
	static BSTR PenColorKey()  {   return g_pXmlKeys->m_strPenColorKey;  }
	static BSTR PenStypeKey()  {   return g_pXmlKeys->m_strPenStypeKey;  }
	static BSTR PenWidthKey()  {   return g_pXmlKeys->m_strPenWidthKey;  }
	static BSTR BrushColorKey()  {   return g_pXmlKeys->m_strBrushColorKey;  }
	static BSTR ShowChildrenKey()  {   return g_pXmlKeys->m_strShowChildrenKey;  }
	static BSTR BringToTopKey()  {   return g_pXmlKeys->m_strBringToTopKey;  }
	static BSTR BkBmpFileKey()  {   return g_pXmlKeys->m_strBkBmpFileKey;  }
	static BSTR BorderKey()  {   return g_pXmlKeys->m_strBorderKey;  }
	static BSTR TabSysMsgKey()  {   return g_pXmlKeys->m_strTabSysMsgKey;  }
	static BSTR StartPageKey()  {   return g_pXmlKeys->m_strStartPageKey;  }
	static BSTR UseFrameKey()  {   return g_pXmlKeys->m_strUseFrameKey;  }
	static BSTR PageFileKey()  {   return g_pXmlKeys->m_strPageFileKey;  }
	static BSTR TreeViewWidthRateKey()  {   return g_pXmlKeys->m_strTreeViewWidthRateKey;  }
	static BSTR TreeViewWidthMaxKey()  {   return g_pXmlKeys->m_strTreeViewWidthMaxKey;  }
	static BSTR BkActiveColorKey()  {   return g_pXmlKeys->m_strBkActiveColorKey;  }
	static BSTR BkDisableColorKey() { return g_pXmlKeys->m_strBkDisableColorKey; }
	static BSTR TransMaskColorKey() { return g_pXmlKeys->m_strTransMaskColorKey; }
	static BSTR TansparentKey() { return g_pXmlKeys->m_strTransparentKey; }
};



class CUIBaseConstGlobal
{
private:
	CUIBaseConstGlobal();
	virtual ~CUIBaseConstGlobal();

public:
	static CUIBaseConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CUIBaseConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};


//////////////////////////////////////////////////////////////////////////
#define WM_EXITINSTANCE							(WM_USER + 1038)

#define POOLTYPE_DIALOG   1
#define POOLTYPE_CHILD    2

UINT UI_GetWndListPoolID(DWORD dwMode);
