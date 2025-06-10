 #pragma once

#include "../../Module/XLanguage/XLanguageMngr.h"
#include "../Module/XLanguageResourceIec.h"

class CXLanguageResourceIec_61850Cfg: public CXLanguageResourceIecBase
{
	// ����
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

	static CString g_sLid_staMesType;//�ı��� 20161013
	static CString g_sLtxt_staMesType;//�ı��� 20161013
	static CString g_sLid_staSampleRate;//�ı��� 20161013
	static CString g_sLtxt_staSampleRate;//�ı��� 20161013
	static CString g_sLid_staASDU;//�ı��� 20161013
	static CString g_sLtxt_staASDU;//�ı��� 20161013
	static CString g_sLid_cheQuality;//�ı��� 20161013
	static CString g_sLtxt_cheQuality;//�ı��� 20161013
	static CString g_sLid_butSMVRate;//�ı��� 20161013
	static CString g_sLtxt_butSMVRate;//�ı��� 20161013

	static CString g_sLid_radUiselI;//�ı��� 20161013
	static CString g_sLtxt_radUiselI;//�ı��� 20161013
	static CString g_sLid_radIecUiselU;//�ı��� 20161013
	static CString g_sLtxt_radIecUiselU;//�ı��� 20161013
	static CString g_sLid_radIecUiselAll;//�ı��� 20161013
	static CString g_sLtxt_radIecUiselAll;//�ı��� 20161013
	static CString g_sLid_cheUseName;//�ı��� 20161013
	static CString g_sLtxt_cheUseName;//�ı��� 20161013
	static CString g_sLid_butSetABC;//�ı��� 20161013
	static CString g_sLtxt_butSetABC;//�ı��� 20161013
	static CString g_sLid_butSetPABC;//�ı��� 20161013
	static CString g_sLtxt_butSetPABC;//�ı��� 20161013
	static CString g_sLid_butSetSABC;//�ı��� 20161013
	static CString g_sLtxt_butSetSABC;//�ı��� 20161013
	static CString g_sLid_butSetTABC;//�ı��� 20161013
	static CString g_sLtxt_butSetTABC;//�ı��� 20161013
	static CString g_sLid_butSetABC5;//zhouhj20210924
	static CString g_sLtxt_butSetABC5;//zhouhj20210924
	static CString g_sLid_butSetABC6;//zhouhj20210924
	static CString g_sLtxt_butSetABC6;//zhouhj20210924
	static CString g_sLid_butSet0;//�ı��� 20161013
	static CString g_sLtxt_butSet0;//�ı��� 20161013

	static CString g_sLid_btnAllSel;//�ı��� 20161013
	static CString g_sLtxt_btnAllSel;//�ı��� 20161013
	static CString g_sLid_btnAddTo;//�ı��� 20161013
	static CString g_sLtxt_btnAddTo;//�ı��� 20161013
	static CString g_sLid_btnOverwrite;//�ı��� 20161013
	static CString g_sLtxt_btnOverwrite;//�ı��� 20161013
	static CString g_sLid_btnCompare;//�ı��� 20161013
	static CString g_sLtxt_btnCompare;//�ı��� 20161013
	static CString g_sLid_btnExport;//�ı��� 20161013
	static CString g_sLtxt_btnExport;//�ı��� 20161013

	static CString g_sLid_btnFilter;//�ı��� 20161014
	static CString g_sLtxt_btnFilter;//�ı��� 20161014

	static CString g_sLid_btnIecBrowse;//�ı��� 20161014
	static CString g_sLtxt_btnIecBrowse;//�ı��� 20161014
	static CString g_sLid_btnOK;//�ı��� 20161014
	static CString g_sLtxt_btnOK;//�ı��� 20161014
	static CString g_sLid_btnIecCancel;//�ı��� 20161014
	static CString g_sLtxt_btnIecCancel;//�ı��� 20161014


	static CString g_sLid_titIecSMVCfg;//������� 20161014
	static CString g_sLtxt_titIecSMVCfg;//������� 20161014
	static CString g_sLid_titIecGoSubCfg;//������� 20161014
	static CString g_sLtxt_titIecGoSubCfg;//������� 20161014
	static CString g_sLid_titIecGoPubCfg;//������� 20161014
	static CString g_sLtxt_titIecGoPubCfg;//������� 20161014

	static CString g_sLid_btnIecAdd;//������� 20161014
	static CString g_sLtxt_btnIecAdd;//������� 20161014
	static CString g_sLid_btnIecMoveUp;//������� 20161014
	static CString g_sLtxt_btnIecMoveUp;//������� 20161014
	static CString g_sLid_btnIecMoveDown;//������� 20161014
	static CString g_sLtxt_btnIecMoveDown;//������� 20161014
	static CString g_sLid_btnIecCope;//������� 20161014
	static CString g_sLtxt_btnIecCope;//������� 20161014
	static CString g_sLid_btnIecPaste;//������� 20161014
	static CString g_sLtxt_btnIecPaste;//������� 20161014
	static CString g_sLid_btnIecOutputTo;//������� 20161014
	static CString g_sLtxt_btnIecOutputTo;//������� 20161014
	static CString g_sLid_btnIecIncrement;//������� 20161014
	static CString g_sLid_btnIecDescending;//������� 20161014
	static CString g_sLid_btnIecUnselectAll;//������� 20161014
	static CString g_sLtxt_btnIecUnselectAll;//������� 20161014
//SCL�ļ���ʷ��¼      //20161015
	static CString g_sLangID_SclRecord;    //20161015
	static CString g_sLangTxt_SclRecord;    //20161015
	//SCL�ļ���ȡ��         //20161015
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
	static CString g_sLangTxt_CreateTesterMngrModuleFail;//                =_T("���������ǹ������ʧ��");
	static CString g_sLangID_CreateTestModuleFail;//                = _T("sCreateTestModuleFail  ");  
	static CString g_sLangTxt_CreateTestModuleFail;//                  =_T("�����������ʧ��");
	static CString g_sLangID_CreateTesterCmmModuleAbn;//                = _T("sCreateTesterCmmModuleAbn ");  
	static CString g_sLangTxt_CreateTesterCmmModuleAbn ;//                =_T("����������ͨѶ��������쳣");
	static CString g_sLangID_CreateTesterCmmModuleFail;//                = _T("sCreateTesterCmmModuleFail");  
	static CString g_sLangTxt_CreateTesterCmmModuleFail;//                =_T("����������ͨѶ���ʧ��");
	static CString g_sLangID_DownloadConfigFileErr;//                = _T("sDownloadConfigFileErr");  
	static CString g_sLangTxt_DownloadConfigFileErr;//                =_T("���������ļ����󣬴���ţ�0X%08X");
	static CString g_sLangID_AngLiTesterIec61850ConfigFile ;//               = _T("sAngLiTesterIec61850ConfigFile");  
	static CString g_sLangTxt_AngLiTesterIec61850ConfigFile ;//                =_T("����������IEC61850�����ļ�(*.f66)|*.f66||");
	
	

};

