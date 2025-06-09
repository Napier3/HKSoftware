#pragma once

#define TREEITEM_TYPE_DEVICE   0X10000000
#define TREEITEM_TYPE_LDEVICE  0X20000000
#define TREEITEM_TYPE_TAGDA    0X30000000
#define TREEITEM_TYPE_FILEDIR  0X40000000
#define TREEITEM_TYPE_LOGLIST  0X50000000
#define TREEITEM_TYPE_NODES    0X60000000

#define DLG_STEP_EntrySel		"EntrySel"
#define DLG_STEP_Main			"Main"
#define DLG_STEP_SenceSel		"SenceSel"
#define DLG_STEP_ConnectTip		"ConnectTip"
#define DLG_STEP_DvmRead		"DvmRead"
#define DLG_STEP_IEDSel			"IDESel"
#define DLG_STEP_DvmMap			"DvmMap"
#define DLG_STEP_ImpSet			"ImpSet"
#define DLG_STEP_IECCfg			"IECCfg"
#define DLG_STEP_Build			"Build"
#define DLG_STEP_Record			"OpenRecord"
#define DLG_STEP_Bluetooth		"OpenBluetooth"

#define DLG_STEP_AutoTest		"AutoTest"


//iSmartTestWzdCfg属性
#define SENCESEL_USERFACTORY	"SenceSel_UserFactory"
#define SENCESEL_FACTORY		"SenceSel_Factory"
#define SENCESEL_SUBSTATION		"SenceSel_Substation"
#define SENCESEL_VOLTLEVEL		"SenceSel_VolLevel"
#define SENCESEL_DEVICETYPE		"SenceSel_DeviceType"
#define SENCESEL_DEVICECOMMOND	"SenceSel_DeviceCommond"
#define SENCESEL_TESTTYPE		"SenceSel_TestType"
#define SENCESEL_SCDCHOOSE		"SenceSel_SCDChoose"
#define SENCESEL_SETFILECHOOSE	"SenceSel_SetFileChoose"
#define SENCESEL_FILEPATH		"SenceSel_FilePath"
#define SENCESEL_ENABLE			"SenceSel_Enable"

#define IECCFG_TRANSFORM		"IECCfg_Transform"
#define IECCFG_LINE				"IECCfg_Line"
#define IECCFG_BUS				"IECCfg_Bus"

//主界面消息
#define WM_MAIN_ENABLE_RETURN	WM_USER + 10995
#define WM_MAIN_ENABLE_PREV		WM_USER + 10996
#define WM_MAIN_ENABLE_NEXT		WM_USER + 10997
#define WM_MAIN_NEWTEST			WM_USER + 10998
#define WM_STEPLIST_CHANGE		WM_USER + 10999
//变电站信息配置变更(WPARAM),定值文件变更(LPARAM)
//变电站:   0-常规     1-智能
//定值文件: 0-未选取   1-选取
#define WM_SENCESEL_CHANGE	WM_USER + 11000 
//根据选项选择标准模型
#define WM_SENCESEL_CFG		WM_USER + 11001
//选择测试类型
#define WM_SENCESEL_TEST	WM_USER + 11002
//根据定值文件刷新定值单核对
#define WM_SENSESEL_FILE	WM_USER + 11003
//选择规约
#define WM_SENCESEL_COMM	WM_USER + 11004
//选择用户
#define WM_USER_CHANGE		WM_USER + 11005

//IED装置刷新
#define WM_OPEN_SCL_FILE		(WM_USER + 13000)
//IED选中并解析一个装置
#define WM_IEDSEL_SELECT	WM_USER + 13001
//IED选中的装置名
#define WM_IEDSEL_TXT		WM_USER + 13002
//传递菜单右键消息
#define WM_DVMMAP_MENU		WM_USER + 15000
//即将进入定值单页面,提前刷新数据
#define WM_DVMMAP_DONEXT	WM_USER	+ 15001
//定值单重新核对
#define WM_IMPSET_UPDATE	WM_USER + 16000
//IECCFG传递映射信息
#define WM_IECCFG_SETTING	WM_USER + 17000
#define WM_IECCFG_RETURN	WM_USER + 17001
#define WM_IECCFG_CLICKED	WM_USER + 17002
#define WM_IECCFG_UPDATEGS	WM_USER + 17003
//刷新信息确认界面
#define WM_CONNECT_UPDATE	WM_USER + 18000

static COLORREF g_crBlue = RGB(162, 217, 247);
static COLORREF g_crLightBlue = RGB(208, 231, 244);