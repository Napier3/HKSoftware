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


//iSmartTestWzdCfg����
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

//��������Ϣ
#define WM_MAIN_ENABLE_RETURN	WM_USER + 10995
#define WM_MAIN_ENABLE_PREV		WM_USER + 10996
#define WM_MAIN_ENABLE_NEXT		WM_USER + 10997
#define WM_MAIN_NEWTEST			WM_USER + 10998
#define WM_STEPLIST_CHANGE		WM_USER + 10999
//���վ��Ϣ���ñ��(WPARAM),��ֵ�ļ����(LPARAM)
//���վ:   0-����     1-����
//��ֵ�ļ�: 0-δѡȡ   1-ѡȡ
#define WM_SENCESEL_CHANGE	WM_USER + 11000 
//����ѡ��ѡ���׼ģ��
#define WM_SENCESEL_CFG		WM_USER + 11001
//ѡ���������
#define WM_SENCESEL_TEST	WM_USER + 11002
//���ݶ�ֵ�ļ�ˢ�¶�ֵ���˶�
#define WM_SENSESEL_FILE	WM_USER + 11003
//ѡ���Լ
#define WM_SENCESEL_COMM	WM_USER + 11004
//ѡ���û�
#define WM_USER_CHANGE		WM_USER + 11005

//IEDװ��ˢ��
#define WM_OPEN_SCL_FILE		(WM_USER + 13000)
//IEDѡ�в�����һ��װ��
#define WM_IEDSEL_SELECT	WM_USER + 13001
//IEDѡ�е�װ����
#define WM_IEDSEL_TXT		WM_USER + 13002
//���ݲ˵��Ҽ���Ϣ
#define WM_DVMMAP_MENU		WM_USER + 15000
//�������붨ֵ��ҳ��,��ǰˢ������
#define WM_DVMMAP_DONEXT	WM_USER	+ 15001
//��ֵ�����º˶�
#define WM_IMPSET_UPDATE	WM_USER + 16000
//IECCFG����ӳ����Ϣ
#define WM_IECCFG_SETTING	WM_USER + 17000
#define WM_IECCFG_RETURN	WM_USER + 17001
#define WM_IECCFG_CLICKED	WM_USER + 17002
#define WM_IECCFG_UPDATEGS	WM_USER + 17003
//ˢ����Ϣȷ�Ͻ���
#define WM_CONNECT_UPDATE	WM_USER + 18000

static COLORREF g_crBlue = RGB(162, 217, 247);
static COLORREF g_crLightBlue = RGB(208, 231, 244);