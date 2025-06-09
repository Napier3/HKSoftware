 #pragma once

#include "../../Module/XLanguage/XLanguageMngr.h"
#include "../Module/XLanguageResourceIec.h"

class CXLanguageResourceIec_61850Cfg: public CXLanguageResourceIecBase
{
	// 构造
public:
	CXLanguageResourceIec_61850Cfg();
	virtual ~CXLanguageResourceIec_61850Cfg();
	
private:    //20161015
	CXLanguage m_oXLangRs_61850Cfg;   //20161015
	static const CString  g_strXLangRs_61850CfgFile;  //20161015


public:
	CXLangItem* rs_AddString(const CString &strID, CString *pstrString);	 //20161015 
	virtual void InitLangRsByFile();     //20161015

	virtual void RegisterLanguageResource();

public:
	static CString g_sLangID_UseCfg;
	static CString g_sLangTxt_UseCfg;
	static CString g_sLangID_UseCfgTip;
	static CString g_sLangTxt_UseCfgTip;
	static CString g_sLangID_CloseFileTip;
	static CString g_sLangTxt_CloseFileTip;

	static CString g_sLangID_ConfigFile;
	static CString g_sLangTxt_ConfigFile;
	static CString g_sLangID_NewConf;
	static CString g_sLangTxt_NewConf;
	static CString g_sLangID_NewConfTip;
	static CString g_sLangTxt_NewConfTip;
	static CString g_sLangID_ImportConf;
	static CString g_sLangTxt_ImportConf;
	static CString g_sLangID_ImportConfTip;
	static CString g_sLangTxt_ImportConfTip;
	static CString g_sLangID_SaveConf;
	static CString g_sLangTxt_SaveConf;
	static CString g_sLangID_SaveConfTip;
	static CString g_sLangTxt_SaveConfTip;
	static CString g_sLangID_ConfSaveAs;
	static CString g_sLangTxt_ConfSaveAs;
	static CString g_sLangID_ConfSaveAsTip;
	static CString g_sLangTxt_ConfSaveAsTip;
	static CString g_sLangID_SCDFile;
	static CString g_sLangTxt_SCDFile;
	static CString g_sLangID_OpenSCDFile;
	static CString g_sLangTxt_OpenSCDFile;
	static CString g_sLangID_OpenSCDFileTip;
	static CString g_sLangTxt_OpenSCDFileTip;
	static CString g_sLangID_ChooseSCDFile;
	static CString g_sLangTxt_ChooseSCDFile;
	static CString g_sLangID_ChooseSCDFileTip;
	static CString g_sLangTxt_ChooseSCDFileTip;
	static CString g_sLangID_NewDeviceConfig;
	static CString g_sLangTxt_NewDeviceConfig;
	static CString g_sLangID_NewDeviceConfigTip;
	static CString g_sLangTxt_NewDeviceConfigTip;

	static CString g_sLangID_DeviceConfigFileBar;
	static CString g_sLangTxt_DeviceConfigFileBar;
	static CString g_sLangID_DeviceConfigFileBarTip;
	static CString g_sLangTxt_DeviceConfigFileBarTip;
	static CString g_sLangID_ConfigFileBar;
	static CString g_sLangTxt_ConfigFileBar;
	static CString g_sLangID_ConfigFileBarTip;
	static CString g_sLangTxt_ConfigFileBarTip;
	static CString g_sLangID_DeviceConfigBar;
	static CString g_sLangTxt_DeviceConfigBar;
	static CString g_sLangID_DeviceConfigBarTip;
	static CString g_sLangTxt_DeviceConfigBarTip;
	static CString g_sLangID_OnlyReferencedChannel;
	static CString g_sLangTxt_OnlyReferencedChannel;
	static CString g_sLangID_OnlyReferencedChannelTip;
	static CString g_sLangTxt_OnlyReferencedChannelTip;
// 	static CString g_sLangID_OutputBarTip;
// 	static CString g_sLangTxt_OutputBarTip;
// 	static CString g_sLangID_StatusBarTip;
// 	static CString g_sLangTxt_StatusBarTip;

	static CString g_sLangID_Other;
	static CString g_sLangTxt_Other;
// 	static CString g_sLangID_AboutTip;
// 	static CString g_sLangTxt_AboutTip;
	static CString g_sLangID_Quit;
	static CString g_sLangTxt_Quit;
	static CString g_sLangID_QuitTip;
	static CString g_sLangTxt_QuitTip;

	static CString g_sLangID_DeviceCfgFileManag;
	static CString g_sLangTxt_DeviceCfgFileManag;
	static CString g_sLangID_DeviceCfg;
	static CString g_sLangTxt_DeviceCfg;

	static CString g_sLid_staMesType;//文本框 20161013
	static CString g_sLtxt_staMesType;//文本框 20161013
	static CString g_sLid_staSampleRate;//文本框 20161013
	static CString g_sLtxt_staSampleRate;//文本框 20161013
	static CString g_sLid_staASDU;//文本框 20161013
	static CString g_sLtxt_staASDU;//文本框 20161013
	static CString g_sLid_cheQuality;//文本框 20161013
	static CString g_sLtxt_cheQuality;//文本框 20161013
	static CString g_sLid_butSMVRate;//文本框 20161013
	static CString g_sLtxt_butSMVRate;//文本框 20161013

	static CString g_sLid_radUiselI;//文本框 20161013
	static CString g_sLtxt_radUiselI;//文本框 20161013
	static CString g_sLid_radIecUiselU;//文本框 20161013
	static CString g_sLtxt_radIecUiselU;//文本框 20161013
	static CString g_sLid_radIecUiselAll;//文本框 20161013
	static CString g_sLtxt_radIecUiselAll;//文本框 20161013
	static CString g_sLid_cheUseName;//文本框 20161013
	static CString g_sLtxt_cheUseName;//文本框 20161013
	static CString g_sLid_butSetABC;//文本框 20161013
	static CString g_sLtxt_butSetABC;//文本框 20161013
	static CString g_sLid_butSetPABC;//文本框 20161013
	static CString g_sLtxt_butSetPABC;//文本框 20161013
	static CString g_sLid_butSetSABC;//文本框 20161013
	static CString g_sLtxt_butSetSABC;//文本框 20161013
	static CString g_sLid_butSetTABC;//文本框 20161013
	static CString g_sLtxt_butSetTABC;//文本框 20161013
	static CString g_sLid_butSetABC5;//zhouhj20210924
	static CString g_sLtxt_butSetABC5;//zhouhj20210924
	static CString g_sLid_butSetABC6;//zhouhj20210924
	static CString g_sLtxt_butSetABC6;//zhouhj20210924
	static CString g_sLid_butSet0;//文本框 20161013
	static CString g_sLtxt_butSet0;//文本框 20161013

	static CString g_sLid_btnAllSel;//文本框 20161013
	static CString g_sLtxt_btnAllSel;//文本框 20161013
	static CString g_sLid_btnAddTo;//文本框 20161013
	static CString g_sLtxt_btnAddTo;//文本框 20161013
	static CString g_sLid_btnOverwrite;//文本框 20161013
	static CString g_sLtxt_btnOverwrite;//文本框 20161013
	static CString g_sLid_btnCompare;//文本框 20161013
	static CString g_sLtxt_btnCompare;//文本框 20161013
	static CString g_sLid_btnExport;//文本框 20161013
	static CString g_sLtxt_btnExport;//文本框 20161013

	static CString g_sLid_btnFilter;//文本框 20161014
	static CString g_sLtxt_btnFilter;//文本框 20161014

	static CString g_sLid_btnIecBrowse;//文本框 20161014
	static CString g_sLtxt_btnIecBrowse;//文本框 20161014
	static CString g_sLid_btnOK;//文本框 20161014
	static CString g_sLtxt_btnOK;//文本框 20161014
	static CString g_sLid_btnIecCancel;//文本框 20161014
	static CString g_sLtxt_btnIecCancel;//文本框 20161014


	static CString g_sLid_titIecSMVCfg;//标题输出 20161014
	static CString g_sLtxt_titIecSMVCfg;//标题输出 20161014
	static CString g_sLid_titIecGoSubCfg;//标题输出 20161014
	static CString g_sLtxt_titIecGoSubCfg;//标题输出 20161014
	static CString g_sLid_titIecGoPubCfg;//标题输出 20161014
	static CString g_sLtxt_titIecGoPubCfg;//标题输出 20161014

	static CString g_sLid_btnIecAdd;//按键输出 20161014
	static CString g_sLtxt_btnIecAdd;//按键输出 20161014
	static CString g_sLid_btnIecMoveUp;//按键输出 20161014
	static CString g_sLtxt_btnIecMoveUp;//按键输出 20161014
	static CString g_sLid_btnIecMoveDown;//按键输出 20161014
	static CString g_sLtxt_btnIecMoveDown;//按键输出 20161014
	static CString g_sLid_btnIecCope;//按键输出 20161014
	static CString g_sLtxt_btnIecCope;//按键输出 20161014
	static CString g_sLid_btnIecPaste;//按键输出 20161014
	static CString g_sLtxt_btnIecPaste;//按键输出 20161014
	static CString g_sLid_btnIecOutputTo;//按键输出 20161014
	static CString g_sLtxt_btnIecOutputTo;//按键输出 20161014
	static CString g_sLid_btnIecIncrement;//按键输出 20161014
	static CString g_sLid_btnIecDescending;//按键输出 20161014
	static CString g_sLid_btnIecUnselectAll;//按键输出 20161014
	static CString g_sLtxt_btnIecUnselectAll;//按键输出 20161014
//SCL文件历史记录      //20161015
	static CString g_sLangID_SclRecord;    //20161015
	static CString g_sLangTxt_SclRecord;    //20161015
	//SCL文件读取中         //20161015
	static CString g_sLangID_SclReading;     //20161015
	static CString g_sLangTxt_SclReading;     //20161015

/*	static CString g_sLangID_FileTipppp;
	static CString g_sLangTxt_FileTipppp;*/
	static CString g_sLangID_CheckDelHistory;     
	static CString g_sLangTxt_CheckDelHistory;
	static CString g_sLangID_ConfigOpenNoDel;     
	static CString g_sLangTxt_ConfigOpenNoDel;
	static CString g_sLangID_NoDelContent;     
	static CString g_sLangTxt_NoDelContent; 
	static CString g_sLangID_NoModifyContent;     
	static CString g_sLangTxt_NoModifyContent; 
	static CString g_sLangID_NoSaveCloseConfigFile;     
	static CString g_sLangTxt_NoSaveCloseConfigFile;  
	static CString g_sLangID_NonePowerTestIecPara;     
	static CString g_sLangTxt_NonePowerTestIecPara; 

	static CString g_sLangID_CreateTesterMngrModuleFail;//                = _T("sCreateTesterMngrModuleFail");  
	static CString g_sLangTxt_CreateTesterMngrModuleFail;//                =_T("创建测试仪管理组件失败");
	static CString g_sLangID_CreateTestModuleFail;//                = _T("sCreateTestModuleFail  ");  
	static CString g_sLangTxt_CreateTestModuleFail;//                  =_T("创建测试组件失败");
	static CString g_sLangID_CreateTesterCmmModuleAbn;//                = _T("sCreateTesterCmmModuleAbn ");  
	static CString g_sLangTxt_CreateTesterCmmModuleAbn ;//                =_T("创建测试仪通讯组件出现异常");
	static CString g_sLangID_CreateTesterCmmModuleFail;//                = _T("sCreateTesterCmmModuleFail");  
	static CString g_sLangTxt_CreateTesterCmmModuleFail;//                =_T("创建测试仪通讯组件失败");
	static CString g_sLangID_DownloadConfigFileErr;//                = _T("sDownloadConfigFileErr");  
	static CString g_sLangTxt_DownloadConfigFileErr;//                =_T("下载配置文件错误，错误号：0X%08X");
	static CString g_sLangID_AngLiTesterIec61850ConfigFile ;//               = _T("sAngLiTesterIec61850ConfigFile");  
	static CString g_sLangTxt_AngLiTesterIec61850ConfigFile ;//                =_T("昂立测试仪IEC61850配置文件(*.f66)|*.f66||");
	
	

};

