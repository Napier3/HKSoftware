
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

	rs_AddString(g_sLid_staMesType, &g_sLtxt_staMesType);    //����Ϊ�ı������� 20161013
	rs_AddString(g_sLid_staSampleRate, &g_sLtxt_staSampleRate);    //����Ϊ�ı������� 20161013
	rs_AddString(g_sLid_staASDU, &g_sLtxt_staASDU);    //����Ϊ�ı������� 20161013
	rs_AddString(g_sLid_cheQuality, &g_sLtxt_cheQuality);    //����Ϊ�ı������� 20161013
	rs_AddString(g_sLid_butSMVRate, &g_sLtxt_butSMVRate);    //����Ϊ�ı������� 20161013

	rs_AddString(g_sLid_radUiselI, &g_sLtxt_radUiselI);    //����Ϊ�ı������� 20161013
	rs_AddString(g_sLid_radIecUiselU, &g_sLtxt_radIecUiselU);    //����Ϊ�ı������� 20161013
	rs_AddString(g_sLid_radIecUiselAll, &g_sLtxt_radIecUiselAll);    //����Ϊ�ı������� 20161013
	rs_AddString(g_sLid_cheUseName, &g_sLtxt_cheUseName);    //����Ϊ�ı������� 20161013
	rs_AddString(g_sLid_butSetABC, &g_sLtxt_butSetABC);    //����Ϊ�ı������� 20161013
	rs_AddString(g_sLid_butSetPABC, &g_sLtxt_butSetPABC);    //����Ϊ�ı������� 20161013
	rs_AddString(g_sLid_butSetSABC, &g_sLtxt_butSetSABC);    //����Ϊ�ı������� 20161013
	rs_AddString(g_sLid_butSetTABC, &g_sLtxt_butSetTABC);    //����Ϊ�ı������� 20161013
	rs_AddString(g_sLid_butSetABC5, &g_sLtxt_butSetABC5);    //����Ϊ�ı������� zhouhj20210924
	rs_AddString(g_sLid_butSetABC6, &g_sLtxt_butSetABC6);    //����Ϊ�ı������� zhouhj20210924
	rs_AddString(g_sLid_butSet0, &g_sLtxt_butSet0);    //����Ϊ�ı������� 20161013

	rs_AddString(g_sLid_btnAllSel, &g_sLtxt_btnAllSel);    //����Ϊ�ı������� 20161013
	rs_AddString(g_sLid_btnAddTo, &g_sLtxt_btnAddTo);    //����Ϊ�ı������� 20161013
	rs_AddString(g_sLid_btnOverwrite, &g_sLtxt_btnOverwrite);    //����Ϊ�ı������� 20161013
	rs_AddString(g_sLid_btnCompare, &g_sLtxt_btnCompare);    //����Ϊ�ı������� 20161013
	rs_AddString(g_sLid_btnExport, &g_sLtxt_btnExport);    //����Ϊ�ı������� 20161013
	rs_AddString(g_sLid_btnFilter, &g_sLtxt_btnFilter);    //����Ϊ�ı������� 20161014
	rs_AddString(g_sLid_btnIecBrowse, &g_sLtxt_btnIecBrowse);    //����Ϊ�ı������� 20161014
	rs_AddString(g_sLid_btnOK, &g_sLtxt_btnOK);    //����Ϊ�ı������� 20161014
	rs_AddString(g_sLid_btnIecCancel, &g_sLtxt_btnIecCancel);    //����Ϊ�ı������� 20161014


	rs_AddString(g_sLid_titIecSMVCfg, &g_sLtxt_titIecSMVCfg);    //����Ϊ����������� 20161014
	rs_AddString(g_sLid_titIecGoSubCfg, &g_sLtxt_titIecGoSubCfg);    //����Ϊ����������� 20161014
	rs_AddString(g_sLid_titIecGoPubCfg, &g_sLtxt_titIecGoPubCfg);    //����Ϊ����������� 20161014

	rs_AddString(g_sLid_btnIecAdd, &g_sLtxt_btnIecAdd);    //����Ϊ����������� 20161014
	rs_AddString(g_sLid_btnIecMoveUp, &g_sLtxt_btnIecMoveUp);    //����Ϊ����������� 20161014
	rs_AddString(g_sLid_btnIecMoveDown, &g_sLtxt_btnIecMoveDown);    //����Ϊ����������� 20161014
	rs_AddString(g_sLid_btnIecCope, &g_sLtxt_btnIecCope);    //����Ϊ����������� 20161014
	rs_AddString(g_sLid_btnIecPaste, &g_sLtxt_btnIecPaste);    //����Ϊ����������� 20161014
	rs_AddString(g_sLid_btnIecOutputTo, &g_sLtxt_btnIecOutputTo);    //����Ϊ����������� 20161014
	  //����Ϊ����������� 20161014
	rs_AddString(g_sLid_btnIecUnselectAll, &g_sLtxt_btnIecUnselectAll);    //����Ϊ����������� 20161014
/*	AddString(g_sLangID_DeviceConfigFileBar, &g_sLangTxt_DeviceConfigFileBar);
	AddString(g_sLangID_DeviceConfigFileBar, &g_sLangTxt_DeviceConfigFileBar);
	AddString(g_sLangID_DeviceConfigFileBar, &g_sLangTxt_DeviceConfigFileBar);*/


	//SCL�ļ���ʷ��¼   //20161015
	rs_AddString(g_sLangID_SclRecord, &g_sLangTxt_SclRecord); //20161015
	//SCL�ļ���ȡ��      //20161015
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
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_UseCfg                 = _T("ʹ������");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_UseCfgTip                  = _T("sUseCfgTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_UseCfgTip                 = _T("ʹ������");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_CloseFileTip                  = _T("sCloseFileTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_CloseFileTip                 = _T("�ر��ļ�");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_ConfigFile                  = _T("sConfigFile");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfigFile                 = _T("�����ļ�");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_NewConf                  = _T("sNewConfig");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_NewConf                 = _T("������");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_NewConfTip                  = _T("sNewConfigTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_NewConfTip                 = _T("�������ĵ�");


CString CXLanguageResourceIec_61850Cfg::g_sLangID_ImportConf                  = _T("sImportConfig");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_ImportConf                 = _T("��������");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_ImportConfTip                  = _T("sImportConfigTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_ImportConfTip                 = _T("�����������������ļ�");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_SaveConf                  = _T("sSaveConf");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_SaveConf                 = _T("��������");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_SaveConfTip                  = _T("sSaveConfTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_SaveConfTip                 = _T("�����ĵ�");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_ConfSaveAs                  = _T("sConfSaveAs");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfSaveAs                 = _T("�������Ϊ");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_ConfSaveAsTip                  = _T("sConfSaveAsTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfSaveAsTip                 = _T("�������Ʊ����ĵ�");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_SCDFile                  = _T("sSCDFile");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_SCDFile                 = _T("SCD�ļ�");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_OpenSCDFile                  = _T("sOpenSCDFile");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_OpenSCDFile                 = _T("��SCD�ļ�");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_OpenSCDFileTip                  = _T("sOpenSCDFileTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_OpenSCDFileTip                 = _T("�򿪴��ڵ�SCL�ļ�");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_ChooseSCDFile                  = _T("sChooseSCDFile");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_ChooseSCDFile                 = _T("ѡ��SCD�ļ�");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_ChooseSCDFileTip                  = _T("sChooseSCDFileTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_ChooseSCDFileTip                 = _T("��SCL��ʷ�ļ�");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_NewDeviceConfig                  = _T("sNewDeviceConfig");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_NewDeviceConfig                 = _T("���豸����");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_NewDeviceConfigTip                  = _T("sNewDeviceConfigTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_NewDeviceConfigTip                 = _T("�������豸�����ĵ�");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_DeviceConfigFileBar                  = _T("sDeviceConfigFileBar");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_DeviceConfigFileBar                 = _T("�豸�����ļ���");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_DeviceConfigFileBarTip                  = _T("sDeviceConfigFileBarTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_DeviceConfigFileBarTip                 = _T("��ʾ�������豸�����ļ�������");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_ConfigFileBar                  = _T("sConfigFileBar");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfigFileBar                 = _T("�����ļ���");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_ConfigFileBarTip                  = _T("sConfigFileBarTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfigFileBarTip                 = _T("��ʾ�����������ļ���");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_DeviceConfigBar                  = _T("sDeviceConfigBar");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_DeviceConfigBar                 = _T("�豸������");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_DeviceConfigBarTip                  = _T("sDeviceConfigBarTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_DeviceConfigBarTip                 = _T("��ʾ�������豸������");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_OnlyReferencedChannel                  = _T("sOnlyReferencedChannel");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_OnlyReferencedChannel                 = _T("ֻ��ʾ����ͨ��");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_OnlyReferencedChannelTip                  = _T("sOnlyReferencedChannelTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_OnlyReferencedChannelTip                 = _T("ֻ��ʾ���õ�ͨ��");

// CString CXLanguageResourceIec_61850Cfg::g_sLangID_OutputBarTip                  = _T("sOutputBarTip");
// CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_OutputBarTip                 = _T("��ʾ�����������");

// CString CXLanguageResourceIec_61850Cfg::g_sLangID_StatusBarTip                  = _T("sStatusBarTip");
// CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_StatusBarTip                 = _T("��ʾ������״̬��");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_Other                  = _T("sOther");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_Other                 = _T("����");

// CString CXLanguageResourceIec_61850Cfg::g_sLangID_AboutTip                  = _T("sAboutTip");
// CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_AboutTip                 = _T("��ʾ������Ϣ���汾�źͰ�Ȩ");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_Quit                  = _T("sQuit");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_Quit                 = _T("�˳�");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_QuitTip                  = _T("sQuitTip");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_QuitTip                 = _T("�˳�Ӧ�ó�����ʾ�����ĵ�");


CString CXLanguageResourceIec_61850Cfg::g_sLangID_DeviceCfgFileManag                  = _T("sDeviceCfgFileManag");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_DeviceCfgFileManag                 = _T("�豸�����ļ�����");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_DeviceCfg                  = _T("sDeviceCfg");
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_DeviceCfg                 = _T("�豸����");

CString CXLanguageResourceIec_61850Cfg::g_sLid_staMesType                = _T("sstaMesType"); // ����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_staMesType               = _T("��������");      //����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_staSampleRate                = _T("sstaSampleRate"); // ����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_staSampleRate               = _T("������");      //����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_staASDU                = _T("sstaASDU"); // ����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_staASDU               = _T("ASDU");      //����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_cheQuality                = _T("scheQuality"); // ����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_cheQuality               = _T("����Ʒ��λ");      //����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_butSMVRate                = _T("sbutSMVRate"); // ����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_butSMVRate               = _T("��������");      //����Ϊ�ı������� 20161013

CString CXLanguageResourceIec_61850Cfg::g_sLid_radUiselI                = _T("sradUiselI"); // ����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_radUiselI               = _T("����ӳ��");      //����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_radIecUiselU                = _T("sradIecUiselU"); // ����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_radIecUiselU               = _T("��ѹӳ��");      //����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_radIecUiselAll                = _T("sradIecUiselAll"); // ����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_radIecUiselAll               = _T("ȫ��");      //����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_cheUseName                = _T("scheUseName"); // ����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_cheUseName               = _T("������������ƥ��");      //����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_butSetABC                = _T("sbutSetABC"); // ����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_butSetABC               = _T("����Ϊabc1");      //����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_butSetPABC                = _T("sbutSetPABC"); // ����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_butSetPABC               = _T("����Ϊabc2");      //����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_butSetSABC                = _T("sbutSetSABC"); // ����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_butSetSABC               = _T("����Ϊabc3");      //����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_butSetTABC                = _T("sbutSetTABC"); // ����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_butSetTABC               = _T("����Ϊabc4");      //����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_butSetABC5                = _T("sbutSetABC5"); // ����Ϊ�ı������� zhouhj20210924
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_butSetABC5               = _T("����Ϊabc5");      //����Ϊ�ı������� zhouhj20210924
CString CXLanguageResourceIec_61850Cfg::g_sLid_butSetABC6                = _T("sbutSetABC6"); // ����Ϊ�ı������� zhouhj20210924
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_butSetABC6               = _T("����Ϊabc6");      //����Ϊ�ı������� zhouhj20210924
CString CXLanguageResourceIec_61850Cfg::g_sLid_butSet0                = _T("sbutSet0"); // ����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_butSet0               = _T("����Ϊ0");      //����Ϊ�ı������� 20161013

CString CXLanguageResourceIec_61850Cfg::g_sLid_btnAllSel                = _T("sbtnAllSel"); // ����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnAllSel               = _T("ȫ��");      //����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_btnAddTo                = _T("sbtnAddTo"); // ����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnAddTo               = _T("���������");      //����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_btnOverwrite                = _T("sbtnOverwrite"); // ����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnOverwrite               = _T("�������ã���");      //����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_btnCompare                = _T("sbtnCompare"); // ����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnCompare               = _T("�Ա����ã���");      //����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLid_btnExport                = _T("sbtnExport"); // ����Ϊ�ı������� 20161013
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnExport               = _T("����ң����");      //����Ϊ�ı������� 20161013

CString CXLanguageResourceIec_61850Cfg::g_sLid_btnFilter                = _T("sbtnFilter"); // ����Ϊ�ı������� 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnFilter               = _T("����");      //����Ϊ�ı������� 20161014

CString CXLanguageResourceIec_61850Cfg::g_sLid_btnIecBrowse                = _T("sbtnIecBrowse"); // ����Ϊ�ı������� 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnIecBrowse               = _T("���...");      //����Ϊ�ı������� 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLid_btnOK                = _T("sbtnOK"); // ����Ϊ�ı������� 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnOK               = _T("ȷ��");      //����Ϊ�ı������� 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLid_btnIecCancel                = _T("sbtnIecCancel"); // ����Ϊ�ı������� 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnIecCancel               = _T("ȡ��");      //����Ϊ�ı������� 20161014


CString CXLanguageResourceIec_61850Cfg::g_sLid_titIecSMVCfg                = _T("stitIecSMVCfg"); // ����Ϊ�������� 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_titIecSMVCfg               = _T("SMV����");      //����Ϊ�������� 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLid_titIecGoSubCfg                = _T("stitIecGoSubCfg"); // ����Ϊ�������� 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_titIecGoSubCfg               = _T("GOOSE��������");      //����Ϊ�������� 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLid_titIecGoPubCfg                = _T("stitIecGoPubCfg"); // ����Ϊ�������� 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_titIecGoPubCfg               = _T("GOOSE��������");      //����Ϊ�������� 20161014

CString CXLanguageResourceIec_61850Cfg::g_sLid_btnIecAdd                = _T("sbtnIecAdd"); // ����Ϊ�������� 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnIecAdd               = _T("���");      //����Ϊ�������� 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLid_btnIecMoveUp                = _T("sbtnIecMoveUp"); // ����Ϊ�������� 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnIecMoveUp               = _T("����");      //����Ϊ�������� 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLid_btnIecMoveDown                = _T("sbtnIecMoveDown"); // ����Ϊ�������� 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnIecMoveDown               = _T("����");      //����Ϊ�������� 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLid_btnIecCope                = _T("sbtnIecCope"); // ����Ϊ�������� 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnIecCope               = _T("����");      //����Ϊ�������� 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLid_btnIecPaste                = _T("sbtnIecPaste"); // ����Ϊ�������� 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnIecPaste               = _T("ճ��");      //����Ϊ�������� 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLid_btnIecOutputTo                = _T("sbtnIecOutputTo"); // ����Ϊ�������� 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnIecOutputTo               = _T("�����");      //����Ϊ�������� 20161014
      //����Ϊ�������� 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLid_btnIecUnselectAll                = _T("sbtnIecUnselectAll"); // ����Ϊ�������� 20161014
CString CXLanguageResourceIec_61850Cfg::g_sLtxt_btnIecUnselectAll               = _T("ȫ��ѡ");      //����Ϊ�������� 20161014
//SCL�ļ���ʷ��¼ //20161015
CString CXLanguageResourceIec_61850Cfg::g_sLangID_SclRecord                = _T("sSclRecord");  //20161015
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_SclRecord               = _T("SCL�ļ���ʷ��¼"); //20161015  
//SCL�ļ���ȡ��   //20161015
CString CXLanguageResourceIec_61850Cfg::g_sLangID_SclReading                = _T("sSclReading");  //20161015
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_SclReading               = _T("SCL�ļ���ȡ�У����Ժ�......");   //20161015
CString CXLanguageResourceIec_61850Cfg::g_sLangID_CheckDelHistory                = _T("sCheckDelHistory");  //20161015
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_CheckDelHistory               = _T("��ȷʵҪɾ����ʷ��¼��\r\n\r\n%s");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_ConfigOpenNoDel                = _T("sConfigOpenNoDel");  //20161015
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfigOpenNoDel               =_T("�����ļ���%s���Ѿ��򿪣�����ɾ��!");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_NoDelContent                = _T("sNoDelContent");  //20161015
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_NoDelContent               =_T("Ŀ¼��%s�������Ѿ��򿪵��ļ�,����ɾ����");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_NoModifyContent                  = _T("sNoModifyContent");  //20161015
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_NoModifyContent              = _T("Ŀ¼��%s�������Ѿ��򿪵��ļ��������޸����ƣ�");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_NoSaveCloseConfigFile                = _T("sNoSaveCloseConfigFile");  //20161015
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_NoSaveCloseConfigFile               =_T("�����ļ�\r\n%s\r\n�Ѿ��ı䣬������ֱ�ӹر���");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_NonePowerTestIecPara                = _T("sNonePowerTestIecPara");  //20161015
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_NonePowerTestIecPara                =_T("δ����PowerTest IEC������");

CString CXLanguageResourceIec_61850Cfg::g_sLangID_CreateTesterMngrModuleFail                = _T("sCreateTesterMngrModuleFail");  
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_CreateTesterMngrModuleFail                =_T("���������ǹ������ʧ��");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_CreateTestModuleFail                = _T("sCreateTestModuleFail");  
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_CreateTestModuleFail                  =_T("�����������ʧ��");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_CreateTesterCmmModuleAbn                = _T("sCreateTesterCmmModuleAbn");  
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_CreateTesterCmmModuleAbn                 =_T("����������ͨѶ��������쳣");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_CreateTesterCmmModuleFail                = _T("sCreateTesterCmmModuleFail");  
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_CreateTesterCmmModuleFail                =_T("����������ͨѶ���ʧ��");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_DownloadConfigFileErr                = _T("sDownloadConfigFileErr");  
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_DownloadConfigFileErr                =_T("���������ļ����󣬴���ţ�0X%08X");
CString CXLanguageResourceIec_61850Cfg::g_sLangID_AngLiTesterIec61850ConfigFile                = _T("sAngLiTesterIec61850ConfigFile");  
CString CXLanguageResourceIec_61850Cfg::g_sLangTxt_AngLiTesterIec61850ConfigFile                 =_T("����������IEC61850�����ļ�(*.f66)|*.f66||");

