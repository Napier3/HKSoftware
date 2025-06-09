
#include "stdafx.h"
#include "XLanguageResourceIec_61850Cfg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView

const CString  CXLanguageResourceIec_61850Cfg::g_strXLangRs_61850CfgFile = _T("Iec61850Cfg"); //20161015

CXLanguageResourceIec_61850Cfg::CXLanguageResourceIec_61850Cfg()
{
	m_pXLangRsExe = &m_oXLangRs_61850Cfg;    //20161015
	m_oXLangRs_61850Cfg.m_strID = g_strXLangRs_61850CfgFile;  //20161015
	m_oXLangRs_61850Cfg.m_strName = g_strXLangRs_61850CfgFile;   //20161015
}

CXLanguageResourceIec_61850Cfg::~CXLanguageResourceIec_61850Cfg()
{
	m_oXLangRs_61850Cfg.RemoveAll();//20161015
}


CXLangItem* CXLanguageResourceIec_61850Cfg::rs_AddString(const CString &strID, CString *pstrString)//20161015
{
	CXLangItem *p = CXLanguage::AddString(strID, pstrString);//20161015

	m_oXLangRs_61850Cfg.AddTail(p); //20161015

	return p;//20161015
}


void CXLanguageResourceIec_61850Cfg::InitLangRsByFile()//20161015
{
	CXLanguageResourceIecBase::InitLangRsByFile();//20161015

	InitLangRsByFileEx(&m_oXLangRs_61850Cfg, g_strXLangRs_61850CfgFile);//20161015
}


void CXLanguageResourceIec_61850Cfg::RegisterLanguageResource()
{
	CXLanguageResourceIecBase::RegisterLanguageResource();


/*	rs_AddString(g_sLangID_FileTip, &g_sLangTxt_FileTip);*/
	//rs_AddString(g_sLangID_Save,&g_sLangTxt_Save);
	
	rs_AddString(g_sLangID_UseCfg, &g_sLangTxt_UseCfg);
	rs_AddString(g_sLangID_UseCfgTip, &g_sLangTxt_UseCfgTip);
	rs_AddString(g_sLangID_CloseFileTip, &g_sLangTxt_CloseFileTip);

	rs_AddString(g_sLangID_ConfigFile, &g_sLangTxt_ConfigFile);
	rs_AddString(g_sLangID_NewConf, &g_sLangTxt_NewConf);
	rs_AddString(g_sLangID_NewConfTip, &g_sLangTxt_NewConfTip);
	rs_AddString(g_sLangID_ImportConf, &g_sLangTxt_ImportConf);
	rs_AddString(g_sLangID_ImportConfTip, &g_sLangTxt_ImportConfTip);
	rs_AddString(g_sLangID_SaveConf, &g_sLangTxt_SaveConf);
	rs_AddString(g_sLangID_SaveConfTip, &g_sLangTxt_SaveConfTip);
	rs_AddString(g_sLangID_ConfSaveAs, &g_sLangTxt_ConfSaveAs);
	rs_AddString(g_sLangID_ConfSaveAsTip, &g_sLangTxt_ConfSaveAsTip);
	rs_AddString(g_sLangID_SCDFile, &g_sLangTxt_SCDFile);
	rs_AddString(g_sLangID_OpenSCDFile, &g_sLangTxt_OpenSCDFile);
	rs_AddString(g_sLangID_OpenSCDFileTip, &g_sLangTxt_OpenSCDFileTip);
	rs_AddString(g_sLangID_ChooseSCDFile, &g_sLangTxt_ChooseSCDFile);
	rs_AddString(g_sLangID_ChooseSCDFileTip, &g_sLangTxt_ChooseSCDFileTip);
	rs_AddString(g_sLangID_NewDeviceConfig, &g_sLangTxt_NewDeviceConfig);
	rs_AddString(g_sLangID_NewDeviceConfigTip, &g_sLangTxt_NewDeviceConfigTip);

	rs_AddString(g_sLangID_DeviceConfigFileBar, &g_sLangTxt_DeviceConfigFileBar);
	rs_AddString(g_sLangID_DeviceConfigFileBarTip, &g_sLangTxt_DeviceConfigFileBarTip);
	rs_AddString(g_sLangID_ConfigFileBar, &g_sLangTxt_ConfigFileBar);
	rs_AddString(g_sLangID_ConfigFileBarTip, &g_sLangTxt_ConfigFileBarTip);
	rs_AddString(g_sLangID_DeviceConfigBar, &g_sLangTxt_DeviceConfigBar);
	rs_AddString(g_sLangID_DeviceConfigBarTip, &g_sLangTxt_DeviceConfigBarTip);
	rs_AddString(g_sLangID_OnlyReferencedChannel, &g_sLangTxt_OnlyReferencedChannel);
	rs_AddString(g_sLangID_OnlyReferencedChannelTip, &g_sLangTxt_OnlyReferencedChannelTip);
//	rs_AddString(g_sLangID_OutputBarTip, &g_sLangTxt_OutputBarTip);
// 	rs_AddString(g_sLangID_StatusBarTip, &g_sLangTxt_StatusBarTip);
	rs_AddString(g_sLangID_Other, &g_sLangTxt_Other);
// 	rs_AddString(g_sLangID_AboutTip, &g_sLangTxt_AboutTip);
	rs_AddString(g_sLangID_Quit, &g_sLangTxt_Quit);
	rs_AddString(g_sLangID_QuitTip, &g_sLangTxt_QuitTip);

	rs_AddString(g_sLangID_DeviceCfgFileManag, &g_sLangTxt_DeviceCfgFileManag);
	rs_AddString(g_sLangID_DeviceCfg, &g_sLangTxt_DeviceCfg);

	rs_AddString(g_sLid_staMesType, &g_sLtxt_staMesType);    //以下为文本框内容 20161013
	rs_AddString(g_sLid_staSampleRate, &g_sLtxt_staSampleRate);    //以下为文本框内容 20161013
	rs_AddString(g_sLid_staASDU, &g_sLtxt_staASDU);    //以下为文本框内容 20161013
	rs_AddString(g_sLid_cheQuality, &g_sLtxt_cheQuality);    //以下为文本框内容 20161013
	rs_AddString(g_sLid_butSMVRate, &g_sLtxt_butSMVRate);    //以下为文本框内容 20161013

	rs_AddString(g_sLid_radUiselI, &g_sLtxt_radUiselI);    //以下为文本框内容 20161013
	rs_AddString(g_sLid_radIecUiselU, &g_sLtxt_radIecUiselU);    //以下为文本框内容 20161013
	rs_AddString(g_sLid_radIecUiselAll, &g_sLtxt_radIecUiselAll);    //以下为文本框内容 20161013
	rs_AddString(g_sLid_cheUseName, &g_sLtxt_cheUseName);    //以下为文本框内容 20161013
	rs_AddString(g_sLid_butSetABC, &g_sLtxt_butSetABC);    //以下为文本框内容 20161013
	rs_AddString(g_sLid_butSetPABC, &g_sLtxt_butSetPABC);    //以下为文本框内容 20161013
	rs_AddString(g_sLid_butSetSABC, &g_sLtxt_butSetSABC);    //以下为文本框内容 20161013
	rs_AddString(g_sLid_butSetTABC, &g_sLtxt_butSetTABC);    //以下为文本框内容 20161013
	rs_AddString(g_sLid_butSetABC5, &g_sLtxt_butSetABC5);    //以下为文本框内容 zhouhj20210924
	rs_AddString(g_sLid_butSetABC6, &g_sLtxt_butSetABC6);    //以下为文本框内容 zhouhj20210924
	rs_AddString(g_sLid_butSet0, &g_sLtxt_butSet0);    //以下为文本框内容 20161013

	rs_AddString(g_sLid_btnAllSel, &g_sLtxt_btnAllSel);    //以下为文本框内容 20161013
	rs_AddString(g_sLid_btnAddTo, &g_sLtxt_btnAddTo);    //以下为文本框内容 20161013
	rs_AddString(g_sLid_btnOverwrite, &g_sLtxt_btnOverwrite);    //以下为文本框内容 20161013
	rs_AddString(g_sLid_btnCompare, &g_sLtxt_btnCompare);    //以下为文本框内容 20161013
	rs_AddString(g_sLid_btnExport, &g_sLtxt_btnExport);    //以下为文本框内容 20161013
	rs_AddString(g_sLid_btnFilter, &g_sLtxt_btnFilter);    //以下为文本框内容 20161014
	rs_AddString(g_sLid_btnIecBrowse, &g_sLtxt_btnIecBrowse);    //以下为文本框内容 20161014
	rs_AddString(g_sLid_btnOK, &g_sLtxt_btnOK);    //以下为文本框内容 20161014
	rs_AddString(g_sLid_btnIecCancel, &g_sLtxt_btnIecCancel);    //以下为文本框内容 20161014


	rs_AddString(g_sLid_titIecSMVCfg, &g_sLtxt_titIecSMVCfg);    //以下为标题输出内容 20161014
	rs_AddString(g_sLid_titIecGoSubCfg, &g_sLtxt_titIecGoSubCfg);    //以下为标题输出内容 20161014
	rs_AddString(g_sLid_titIecGoPubCfg, &g_sLtxt_titIecGoPubCfg);    //以下为标题输出内容 20161014

	rs_AddString(g_sLid_btnIecAdd, &g_sLtxt_btnIecAdd);    //以下为按键输出内容 20161014
	rs_AddString(g_sLid_btnIecMoveUp, &g_sLtxt_btnIecMoveUp);    //以下为按键输出内容 20161014
	rs_AddString(g_sLid_btnIecMoveDown, &g_sLtxt_btnIecMoveDown);    //以下为按键输出内容 20161014
	rs_AddString(g_sLid_btnIecCope, &g_sLtxt_btnIecCope);    //以下为按键输出内容 20161014
	rs_AddString(g_sLid_btnIecPaste, &g_sLtxt_btnIecPaste);    //以下为按键输出内容 20161014
	rs_AddString(g_sLid_btnIecOutputTo, &g_sLtxt_btnIecOutputTo);    //以下为按键输出内容 20161014
	  //以下为按键输出内容 20161014
	rs_AddString(g_sLid_btnIecUnselectAll, &g_sLtxt_btnIecUnselectAll);    //以下为按键输出内容 20161014
/*	AddString(g_sLangID_DeviceConfigFileBar, &g_sLangTxt_DeviceConfigFileBar);
	AddString(g_sLangID_DeviceConfigFileBar, &g_sLangTxt_DeviceConfigFileBar);
	AddString(g_sLangID_DeviceConfigFileBar, &g_sLangTxt_DeviceConfigFileBar);*/


	//SCL文件历史记录   //20161015
	rs_AddString(g_sLangID_SclRecord, &g_sLangTxt_SclRecord); //20161015
	//SCL文件读取中      //20161015
	rs_AddString(g_sLangID_SclReading, &g_sLangTxt_SclReading);  //20161015
	rs_AddString(g_sLangID_CheckDelHistory, &g_sLangTxt_CheckDelHistory);
	rs_AddString(g_sLangID_ConfigOpenNoDel, &g_sLangTxt_ConfigOpenNoDel);
	rs_AddString(g_sLangID_NoDelContent, &g_sLangTxt_NoDelContent);
	rs_AddString(g_sLangID_NoModifyContent, &g_sLangTxt_NoModifyContent);
	rs_AddString(g_sLangID_NoSaveCloseConfigFile, &g_sLangTxt_NoSaveCloseConfigFile);
	rs_AddString(g_sLangID_NonePowerTestIecPara, &g_sLangTxt_NonePowerTestIecPara);

	rs_AddString(g_sLangID_CreateTestModuleFail, &g_sLangTxt_CreateTestModuleFail);
	rs_AddString(g_sLangID_CreateTesterMngrModuleFail, &g_sLangTxt_CreateTesterMngrModuleFail);
	rs_AddString(g_sLangID_CreateTesterCmmModuleAbn, &g_sLangTxt_CreateTesterCmmModuleAbn);
	rs_AddString(g_sLangID_CreateTesterCmmModuleFail, &g_sLangTxt_CreateTesterCmmModuleFail);
	rs_AddString(g_sLangID_DownloadConfigFileErr, &g_sLangTxt_DownloadConfigFileErr);

	rs_AddString(g_sLangID_AngLiTesterIec61850ConfigFile, &g_sLangTxt_AngLiTesterIec61850ConfigFile);

	
}


CString CXLanguageResourceIec_61850Cfg::g_sLangID_UseCfg                  = _T("sUseCfg");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_UseCfg                 = _T("使用配置");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_UseCfgTip                  = _T("sUseCfgTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_UseCfgTip                 = _T("使用配置");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_CloseFileTip                  = _T("sCloseFileTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_CloseFileTip                 = _T("关闭文件");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_ConfigFile                  = _T("sConfigFile");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfigFile                 = _T("配置文件");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_NewConf                  = _T("sNewConfig");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_NewConf                 = _T("新配置");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_NewConfTip                  = _T("sNewConfigTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_NewConfTip                 = _T("创建新文档");


CString CXLanguageResourceIec_61850Cfg::g_sLangID_ImportConf                  = _T("sImportConfig");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_ImportConf                 = _T("导入配置");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_ImportConfTip                  = _T("sImportConfigTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_ImportConfTip                 = _T("导入其它厂家配置文件");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_SaveConf                  = _T("sSaveConf");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_SaveConf                 = _T("保存配置");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_SaveConfTip                  = _T("sSaveConfTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_SaveConfTip                 = _T("保存活动文档");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_ConfSaveAs                  = _T("sConfSaveAs");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfSaveAs                 = _T("配置另存为");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_ConfSaveAsTip                  = _T("sConfSaveAsTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfSaveAsTip                 = _T("用新名称保存活动文档");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_SCDFile                  = _T("sSCDFile");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_SCDFile                 = _T("SCD文件");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_OpenSCDFile                  = _T("sOpenSCDFile");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_OpenSCDFile                 = _T("打开SCD文件");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_OpenSCDFileTip                  = _T("sOpenSCDFileTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_OpenSCDFileTip                 = _T("打开存在的SCL文件");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_ChooseSCDFile                  = _T("sChooseSCDFile");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_ChooseSCDFile                 = _T("选择SCD文件");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_ChooseSCDFileTip                  = _T("sChooseSCDFileTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_ChooseSCDFileTip                 = _T("打开SCL历史文件");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_NewDeviceConfig                  = _T("sNewDeviceConfig");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_NewDeviceConfig                 = _T("新设备配置");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_NewDeviceConfigTip                  = _T("sNewDeviceConfigTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_NewDeviceConfigTip                 = _T("创建新设备配置文档");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_DeviceConfigFileBar                  = _T("sDeviceConfigFileBar");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_DeviceConfigFileBar                 = _T("设备配置文件栏");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_DeviceConfigFileBarTip                  = _T("sDeviceConfigFileBarTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_DeviceConfigFileBarTip                 = _T("显示或隐藏设备配置文件管理栏");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_ConfigFileBar                  = _T("sConfigFileBar");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfigFileBar                 = _T("配置文件栏");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_ConfigFileBarTip                  = _T("sConfigFileBarTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfigFileBarTip                 = _T("显示或隐藏配置文件栏");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_DeviceConfigBar                  = _T("sDeviceConfigBar");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_DeviceConfigBar                 = _T("设备配置栏");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_DeviceConfigBarTip                  = _T("sDeviceConfigBarTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_DeviceConfigBarTip                 = _T("显示或隐藏设备配置栏");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_OnlyReferencedChannel                  = _T("sOnlyReferencedChannel");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_OnlyReferencedChannel                 = _T("只显示引用通道");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_OnlyReferencedChannelTip                  = _T("sOnlyReferencedChannelTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_OnlyReferencedChannelTip                 = _T("只显示引用的通道");

// CString CXLanguageResourceIec_61850Cfg::g_sLangID_OutputBarTip                  = _T("sOutputBarTip");
// CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_OutputBarTip                 = _T("显示或隐藏输出栏");

// CString CXLanguageResourceIec_61850Cfg::g_sLangID_StatusBarTip                  = _T("sStatusBarTip");
// CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_StatusBarTip                 = _T("显示或隐藏状态栏");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_Other                  = _T("sOther");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_Other                 = _T("其它");

// CString CXLanguageResourceIec_61850Cfg::g_sLangID_AboutTip                  = _T("sAboutTip");
// CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_AboutTip                 = _T("显示程序信息、版本号和版权");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_Quit                  = _T("sQuit");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_Quit                 = _T("退出");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_QuitTip                  = _T("sQuitTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_QuitTip                 = _T("退出应用程序；提示保存文档");


CString CXLanguageResourceIec_61850Cfg::g_sLangID_DeviceCfgFileManag                  = _T("sDeviceCfgFileManag");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_DeviceCfgFileManag                 = _T("设备配置文件管理");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_DeviceCfg                  = _T("sDeviceCfg");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_DeviceCfg                 = _T("设备配置");

CString CXLanguageResourceIec_61850Cfg::g_sLid_staMesType                = _T("sstaMesType"); // 以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_staMesType               = _T("报文种类");      //以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_staSampleRate                = _T("sstaSampleRate"); // 以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_staSampleRate               = _T("采样率");      //以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_staASDU                = _T("sstaASDU"); // 以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_staASDU               = _T("ASDU");      //以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_cheQuality                = _T("scheQuality"); // 以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_cheQuality               = _T("不含品质位");      //以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_butSMVRate                = _T("sbutSMVRate"); // 以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_butSMVRate               = _T("比例因子");      //以下为文本框内容 20161013

CString CXLanguageResourceIec_61850Cfg::g_sLid_radUiselI                = _T("sradUiselI"); // 以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_radUiselI               = _T("电流映射");      //以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_radIecUiselU                = _T("sradIecUiselU"); // 以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_radIecUiselU               = _T("电压映射");      //以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_radIecUiselAll                = _T("sradIecUiselAll"); // 以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_radIecUiselAll               = _T("全部");      //以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_cheUseName                = _T("scheUseName"); // 以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_cheUseName               = _T("根据名称智能匹配");      //以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_butSetABC                = _T("sbutSetABC"); // 以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_butSetABC               = _T("配置为abc1");      //以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_butSetPABC                = _T("sbutSetPABC"); // 以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_butSetPABC               = _T("配置为abc2");      //以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_butSetSABC                = _T("sbutSetSABC"); // 以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_butSetSABC               = _T("配置为abc3");      //以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_butSetTABC                = _T("sbutSetTABC"); // 以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_butSetTABC               = _T("配置为abc4");      //以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_butSetABC5                = _T("sbutSetABC5"); // 以下为文本框内容 zhouhj20210924
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_butSetABC5               = _T("配置为abc5");      //以下为文本框内容 zhouhj20210924
CString CXLanguageResourceIec_61850Cfg::g_sLid_butSetABC6                = _T("sbutSetABC6"); // 以下为文本框内容 zhouhj20210924
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_butSetABC6               = _T("配置为abc6");      //以下为文本框内容 zhouhj20210924
CString CXLanguageResourceIec_61850Cfg::g_sLid_butSet0                = _T("sbutSet0"); // 以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_butSet0               = _T("配置为0");      //以下为文本框内容 20161013

CString CXLanguageResourceIec_61850Cfg::g_sLid_btnAllSel                = _T("sbtnAllSel"); // 以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnAllSel               = _T("全部");      //以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_btnAddTo                = _T("sbtnAddTo"); // 以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnAddTo               = _T("添加至＞＞");      //以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_btnOverwrite                = _T("sbtnOverwrite"); // 以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnOverwrite               = _T("覆盖配置＞＞");      //以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_btnCompare                = _T("sbtnCompare"); // 以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnCompare               = _T("对比配置＞＞");      //以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_btnExport                = _T("sbtnExport"); // 以下为文本框内容 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnExport               = _T("导出遥信向导");      //以下为文本框内容 20161013

CString CXLanguageResourceIec_61850Cfg::g_sLid_btnFilter                = _T("sbtnFilter"); // 以下为文本框内容 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnFilter               = _T("过滤");      //以下为文本框内容 20161014

CString CXLanguageResourceIec_61850Cfg::g_sLid_btnIecBrowse                = _T("sbtnIecBrowse"); // 以下为文本框内容 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnIecBrowse               = _T("浏览...");      //以下为文本框内容 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLid_btnOK                = _T("sbtnOK"); // 以下为文本框内容 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnOK               = _T("确定");      //以下为文本框内容 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLid_btnIecCancel                = _T("sbtnIecCancel"); // 以下为文本框内容 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnIecCancel               = _T("取消");      //以下为文本框内容 20161014


CString CXLanguageResourceIec_61850Cfg::g_sLid_titIecSMVCfg                = _T("stitIecSMVCfg"); // 以下为标题内容 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_titIecSMVCfg               = _T("SMV配置");      //以下为标题内容 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLid_titIecGoSubCfg                = _T("stitIecGoSubCfg"); // 以下为标题内容 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_titIecGoSubCfg               = _T("GOOSE订阅配置");      //以下为标题内容 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLid_titIecGoPubCfg                = _T("stitIecGoPubCfg"); // 以下为标题内容 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_titIecGoPubCfg               = _T("GOOSE发布配置");      //以下为标题内容 20161014

CString CXLanguageResourceIec_61850Cfg::g_sLid_btnIecAdd                = _T("sbtnIecAdd"); // 以下为按键内容 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnIecAdd               = _T("添加");      //以下为按键内容 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLid_btnIecMoveUp                = _T("sbtnIecMoveUp"); // 以下为按键内容 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnIecMoveUp               = _T("上移");      //以下为按键内容 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLid_btnIecMoveDown                = _T("sbtnIecMoveDown"); // 以下为按键内容 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnIecMoveDown               = _T("下移");      //以下为按键内容 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLid_btnIecCope                = _T("sbtnIecCope"); // 以下为按键内容 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnIecCope               = _T("拷贝");      //以下为按键内容 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLid_btnIecPaste                = _T("sbtnIecPaste"); // 以下为按键内容 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnIecPaste               = _T("粘贴");      //以下为按键内容 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLid_btnIecOutputTo                = _T("sbtnIecOutputTo"); // 以下为按键内容 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnIecOutputTo               = _T("输出至");      //以下为按键内容 20161014
      //以下为按键内容 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLid_btnIecUnselectAll                = _T("sbtnIecUnselectAll"); // 以下为按键内容 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnIecUnselectAll               = _T("全不选");      //以下为按键内容 20161014
//SCL文件历史记录 //20161015
CString CXLanguageResourceIec_61850Cfg::g_sLangID_SclRecord                = _T("sSclRecord");  //20161015
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_SclRecord               = _T("SCL文件历史记录"); //20161015  
//SCL文件读取中   //20161015
CString CXLanguageResourceIec_61850Cfg::g_sLangID_SclReading                = _T("sSclReading");  //20161015
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_SclReading               = _T("SCL文件读取中，请稍后......");   //20161015
CString CXLanguageResourceIec_61850Cfg::g_sLangID_CheckDelHistory                = _T("sCheckDelHistory");  //20161015
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_CheckDelHistory               = _T("你确实要删除历史记录：\r\n\r\n%s");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_ConfigOpenNoDel                = _T("sConfigOpenNoDel");  //20161015
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfigOpenNoDel               =_T("配置文件【%s】已经打开，不能删除!");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_NoDelContent                = _T("sNoDelContent");  //20161015
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_NoDelContent               =_T("目录【%s】包含已经打开的文件,不能删除！");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_NoModifyContent                  = _T("sNoModifyContent");  //20161015
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_NoModifyContent              = _T("目录【%s】包含已经打开的文件，不能修改名称！");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_NoSaveCloseConfigFile                = _T("sNoSaveCloseConfigFile");  //20161015
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_NoSaveCloseConfigFile               =_T("配置文件\r\n%s\r\n已经改变，不保存直接关闭吗？");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_NonePowerTestIecPara                = _T("sNonePowerTestIecPara");  //20161015
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_NonePowerTestIecPara                =_T("未配置PowerTest IEC参数！");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_CreateTesterMngrModuleFail                = _T("sCreateTesterMngrModuleFail");  
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_CreateTesterMngrModuleFail                =_T("创建测试仪管理组件失败");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_CreateTestModuleFail                = _T("sCreateTestModuleFail");  
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_CreateTestModuleFail                  =_T("创建测试组件失败");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_CreateTesterCmmModuleAbn                = _T("sCreateTesterCmmModuleAbn");  
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_CreateTesterCmmModuleAbn                 =_T("创建测试仪通讯组件出现异常");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_CreateTesterCmmModuleFail                = _T("sCreateTesterCmmModuleFail");  
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_CreateTesterCmmModuleFail                =_T("创建测试仪通讯组件失败");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_DownloadConfigFileErr                = _T("sDownloadConfigFileErr");  
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_DownloadConfigFileErr                =_T("下载配置文件错误，错误号：0X%08X");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_AngLiTesterIec61850ConfigFile                = _T("sAngLiTesterIec61850ConfigFile");  
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_AngLiTesterIec61850ConfigFile                 =_T("昂立测试仪IEC61850配置文件(*.f66)|*.f66||");

