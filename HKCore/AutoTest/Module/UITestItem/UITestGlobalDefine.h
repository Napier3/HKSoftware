#pragma once

class CTestControlWnd;

//主窗口
#define SYSEDIT_WIN_TOP    0
#define SYSEDIT_WIN_LEFT   0
#define SYSEDIT_WIN_RIGHT  557
#define SYSEDIT_WIN_BOTTOM 422

//Tab控件
#define SYSEDIT_Tab_TOP    8
#define SYSEDIT_Tab_LEFT   8
#define SYSEDIT_Tab_RIGHT  545
#define SYSEDIT_Tab_BOTTOM 353

//Grid控件
#define SYSEDIT_Grid_TOP    35
#define SYSEDIT_Grid_LEFT   13
#define SYSEDIT_Grid_RIGHT  538
#define SYSEDIT_Grid_BOTTOM 347

//下一步按钮
#define SYSEDIT_BTN_NEXT_TOP    358
#define SYSEDIT_BTN_NEXT_LEFT   226
#define SYSEDIT_BTN_NEXT_RIGHT  300
#define SYSEDIT_BTN_NEXT_BOTTOM 382

//导入按钮
#define SYSEDIT_BTN_IMPORT_TOP    358
#define SYSEDIT_BTN_IMPORT_LEFT   406
#define SYSEDIT_BTN_IMPORT_RIGHT  462
#define SYSEDIT_BTN_IMPORT_BOTTOM 382

//导出按钮
#define SYSEDIT_BTN_EXPORT_TOP    358
#define SYSEDIT_BTN_EXPORT_LEFT   482
#define SYSEDIT_BTN_EXPORT_RIGHT  539
#define SYSEDIT_BTN_EXPORT_BOTTOM 382

#define IDC_SYSEDIT_BTN_OK 10000
#define IDC_SYSEDIT_BTN_IMPORT 10001
#define IDC_SYSEDIT_BTN_EXPORT 10002
#define IDC_SYSEDIT_RELAYSETGRID 10003
#define IDC_SYSEDIT_TAB_PARASEL_0 10004

// static const CString g_strUI_BtnCaptionImport = _T("导入");
// static const CString g_strUI_BtnCaptionExport = _T("导出");
// static const CString g_strUISysPara = _T("系统参数");
// static const CString g_strUITestPara = _T("测试参数");


#define _UITEST_USE_DIALOGEX

// #ifndef _UITEST_USE_DIALOGEX
extern UINT UI_GetSysParaEditDialogID();
extern UINT UI_GetSafetyDialogID();
extern UINT UI_GetCommCmdDialogID();
extern UINT UI_GetCommCmdAttrDialogID();
// #endif
