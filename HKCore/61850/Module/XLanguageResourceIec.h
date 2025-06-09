//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XLanguageResourceBase.h  CXLanguageResourceBase

#pragma once


#include "../../Module/XLanguage/XLanguageResource.h"


class CXLanguageResourceIecBase : public CXLanguageResourceBase
{
public:
	CXLanguageResourceIecBase();
	virtual ~CXLanguageResourceIecBase();
	
	void InitLangFileForDebug(const CString &strModule);


private:
	CXLanguage m_oXLangRsIecBase;  //2016.10.13

public:
	CXLangItem* rs_AddString(const CString &strID, CString *pstrString);	//2016.10.13 
	virtual void InitLangRsByFile();   //2016.10.13 



public:
	virtual void RegisterLanguageResource();
	virtual void InitLangTxt();

};

	extern CString g_strXLangRsIecBaseFile; //2016.10.13
	extern CString g_sLid_SICDGSerial;//������ 20161014
	extern CString g_sLtxt_SICDGSerial;//������ 20161014
	extern CString g_sLid_SICDSelect;//������ 20161014
	extern CString g_sLtxt_SICDSelect;//������ 20161014
	extern CString g_sLid_SICDIED;//������ 20161014
	extern CString g_sLtxt_SICDIED;//������ 20161014
	extern CString g_sLid_SICDAP;//������ 20161014
	extern CString g_sLtxt_SICDAP;//������ 20161014
	extern CString g_sLid_SICDChaNO;//������ 20161014
	extern CString g_sLtxt_SICDChaNO;//������ 20161014
	extern CString g_sLid_SICDTotCha;//������ 20161014
	extern CString g_sLtxt_SICDTotCha;//������ 20161014
	extern CString g_sLid_SICDDataSet;//������ 20161014
	extern CString g_sLtxt_SICDDataSet;//������ 20161014
	extern CString g_sLid_SICDDataSetDes;//������ 20161014
	extern CString g_sLtxt_SICDDataSetDes;//������ 20161014
	extern CString g_sLid_SICDRefChaNO;//������ 20161014
	extern CString g_sLtxt_SICDRefChaNO;//������ 20161014

	extern CString g_sLid_SICDDesMAC;//������ 20161014
	extern CString g_sLtxt_SICDDesMAC;//������ 20161014
	extern CString g_sLid_SourceMAC;//������ 20161014
	extern CString g_sLtxt_SourceMAC;//������ 20161014
	extern CString g_sLid_OutputSel;//������ 20161014
	extern CString g_sLtxt_OutputSel;//������ 20161014
	extern CString g_sLid_VersionNumber;//������ 20161014
	extern CString g_sLtxt_VersionNumber;//������ 20161014
	extern CString g_sLid_SampleDelay;//������ 20161014
	extern CString g_sLtxt_SampleDelay;//������ 20161014
	extern CString g_sLid_SynMode;//������ 20161014
	extern CString g_sLtxt_SynMode;//������ 20161014

	extern CString g_sLid_Description;//������ 20161014
	extern CString g_sLtxt_Description;//������ 20161014
	extern CString g_sLid_TestMark;//������ 20161014
	extern CString g_sLtxt_TestMark;//������ 20161014
	extern CString g_sLid_ShortTransTime;//������ 20161014
	extern CString g_sLtxt_ShortTransTime;//������ 20161014
	extern CString g_sLid_StaRetransT;//������ 20161014
	extern CString g_sLtxt_StaRetransT;//������ 20161014
	extern CString g_sLid_Interval;//������ 20161014
	extern CString g_sLtxt_Interval;//������ 20161014
	extern CString g_sLid_TimeQualty;//������ 20161014
	extern CString g_sLtxt_TimeQualty;//������ 20161014
	extern CString g_sLid_TimeAllowToLive;//������ 20161014
	extern CString g_sLtxt_TimeAllowToLive;//������ 20161014
	extern CString g_sLid_InputSel;//������ 20161014
	extern CString g_sLtxt_InputSel;//������ 20161014
	extern CString g_sLid_AnaGoCBGooseIDAppID;//������ 20161014
	extern CString g_sLtxt_AnaGoCBGooseIDAppID;//������ 20161014

	extern CString g_sLid_SMVChannel;//������ 20161015
	extern CString g_sLtxt_SMVChannel;//������ 20161015
	extern CString g_sLid_ChannelType;//������ 20161015
	extern CString g_sLtxt_ChannelType;//������ 20161015
	extern CString g_sLid_TestDeviceChannel;//������ 20161015
	extern CString g_sLtxt_TestDeviceChannel;//������ 20161015
	extern CString g_sLid_Quality;//������ 20161015
	extern CString g_sLtxt_Quality;//������ 20161015
	extern CString g_sLid_InputName;//������ 20161015
	extern CString g_sLtxt_InputName;//������ 20161015
	extern CString g_sLid_InputPath;//������ 20161015
	extern CString g_sLtxt_InputPath;//������ 20161015

	extern CString g_sLid_InitialValue;//������ 20161015
	extern CString g_sLtxt_InitialValue;//������ 20161015
	extern CString g_sLid_InputMap;//������ 20161015
	extern CString g_sLtxt_InputMap;//������ 20161015

	extern CString g_sLid_LNDescrip;//������ 20161015
	extern CString g_sLtxt_LNDescrip;//������ 20161015
	extern CString g_sLid_DOIDescrip;//������ 20161015
	extern CString g_sLtxt_DOIDescrip;//������ 20161015
	extern CString g_sLid_DAIDescrip;//������ 20161015
	extern CString g_sLtxt_DAIDescrip;//������ 20161015
	extern CString g_sLid_Address;//������ 20161015
	extern CString g_sLtxt_Address;//������ 20161015


	extern CString g_sLid_Map;//������ 20161015
	extern CString g_sLtxt_Map;//������ 20161015
	extern CString g_sLid_InterLNDes;//������ 20161015
	extern CString g_sLtxt_InterLNDes;//������ 20161015
	extern CString g_sLid_ExterLNDes;//������ 20161015
	extern CString g_sLtxt_ExterLNDes;//������ 20161015
	extern CString g_sLid_InterDODes;//������ 20161015
	extern CString g_sLtxt_InterDODes;//������ 20161015
	extern CString g_sLid_ExterDODes;//������ 20161015
	extern CString g_sLtxt_ExterDODes;//������ 20161015
	extern CString g_sLid_InterDUDes;//������ 20161015
	extern CString g_sLtxt_InterDUDes;//������ 20161015
	extern CString g_sLid_ExterDUDes;//������ 20161015
	extern CString g_sLtxt_ExterDUDes;//������ 20161015
	extern CString g_sLid_InterNO;//������ 20161015
	extern CString g_sLtxt_InterNO;//������ 20161015
	extern CString g_sLid_ExterNO;//������ 20161015
	extern CString g_sLtxt_ExterNO;//������ 20161015
	extern CString g_sLid_InterPath;//������ 20161015
	extern CString g_sLtxt_InterPath;//������ 20161015
	extern CString g_sLid_ExterPath;//������ 20161015
	extern CString g_sLtxt_ExterPath;//������ 20161015

	extern CString g_sLid_DUDes;//������ 20161015
	extern CString g_sLtxt_DUDes;//������ 20161015  
	extern CString g_sLangID_IEC61850Config;
	extern CString g_sLangTxt_IEC61850Config;
	extern CString g_sLangID_TesterIEC61850Config;
	extern CString g_sLangTxt_TesterIEC61850Config;
	extern CString g_sLangID_MsgMonitorWnd;
	extern CString g_sLangTxt_MsgMonitorWnd;
	extern CString g_sLangID_WaveMonitorWnd;
	extern CString g_sLangTxt_WaveMonitorWnd;
	extern CString g_sLangID_NoneConfigFile;
	extern CString g_sLangTxt_NoneConfigFile;
	extern CString g_sLangID_NoneSclFile;
	extern CString g_sLangTxt_NoneSclFile;
	extern CString g_sLangID_SclFile;
	extern CString g_sLangTxt_SclFile;
	extern CString g_sLangID_SclStateTool;
	extern CString g_sLangTxt_SclStateTool;

	extern CString g_sLangID_TesterLinkSucc;
	extern CString g_sLangTxt_TesterLinkSucc;
	extern CString g_sLangID_LinkFail;
	extern CString g_sLangTxt_LinkFail;
	extern CString g_sLangID_RecevElectricalTestEndMsg;
	extern CString g_sLangTxt_RecevElectricalTestEndMsg;
	extern CString g_sLangID_DownloadParaFail;
	extern CString g_sLangTxt_DownloadParaFail;
	extern CString g_sLangID_TesterInterfNoIed61850ConfigFunc;
	extern CString g_sLangTxt_TesterInterfNoIed61850ConfigFunc;
	extern CString g_sLangID_TesterTestFuncOvertime;
	extern CString g_sLangTxt_TesterTestFuncOvertime;

	extern CString g_sLangID_Channel;               
	extern CString g_sLangTxt_Channel;
	extern CString g_sLangID_DefaultConfigFileNone;               
	extern CString g_sLangTxt_DefaultConfigFileNone;

	extern CString g_sLangID_GooseoutGroup;               
	extern CString g_sLangTxt_GooseoutGroup; 
	extern CString g_sLangID_PortConflict;               
	extern CString g_sLangTxt_PortConflict; 
	extern CString g_sLangID_GooseinGroup;               
	extern CString g_sLangTxt_GooseinGroup; 
	extern CString g_sLangID_SameOpening;               
	extern CString g_sLangTxt_SameOpening;

	extern CString g_sLangID_TesterConfigFile;               
	extern CString g_sLangTxt_TesterConfigFile;  
	extern CString g_sLangID_Iec61850Config;               
	extern CString g_sLangTxt_Iec61850Config; 
	extern CString g_sLangID_ErrFileFormat;               
	extern CString g_sLangTxt_ErrFileFormat; 
	extern CString g_sLangID_DiffSvmConfig;               
	extern CString g_sLangTxt_DiffSvmConfig;

	extern CString g_sLangID_NoMatchData;               
	extern CString g_sLangTxt_NoMatchData;
	extern CString g_sLangID_NoSelData;               
	extern CString g_sLangTxt_NoSelData;
	extern CString g_sLangID_NoExisDataIndex;               
	extern CString g_sLangTxt_NoExisDataIndex;

	extern CString g_sLangID_AppBin;  //_T("sAppBin");
	extern CString g_sLangTxt_AppBin;  //_T("�����ǿ���");
	extern CString g_sLangID_BindMac;  //_T("sBindMa");
	extern CString g_sLangTxt_BindMac;  //_T("�󶨿��ƿ�MAC");
	extern CString g_sLangID_BindAppID;  //_T("sBindAppID");
	extern CString g_sLangTxt_BindAppID;  //_T("�󶨿��ƿ�APPID");
	extern CString g_sLangID_BindChannel;  //_T("sBindChannel");
	extern CString g_sLangTxt_BindChannel;  //_T("��ͨ��");
	extern CString g_sLangID_OptrBindAppBinInfo;  //_T("sBindChannel");
	extern CString g_sLangTxt_OptrBindAppBinInfo;  //_T("��ͨ��");
 extern CString g_sLangID_Channel2;               // = _T("sChannel2");  2024-7-26 wuinyi
    extern CString g_sLangTxt_Channel2 ;             // =_T("??");

	//2024-9-4 wuxinyi 
	extern CString g_sLangID_Iec_Relay;		//= _T("Iec_Relay");
	extern CString g_sLangTxt_Iec_Relay;		//= _T("??");
	extern CString g_sLangID_Iec_Measure;		//= _T("Iec_Measure");
	extern CString g_sLangTxt_Iec_Measure;		//= _T("??");
	extern CString g_sLangID_Iec_Current;		//= _T("Iec_Current");
	extern CString g_sLangTxt_Iec_Current;		//= _T("??");
	extern CString g_sLangID_Iec_Voltage;		//= _T("Iec_Voltage");
	extern CString g_sLangTxt_Iec_Voltage;		//= _T("??");
	extern CString g_sLangID_Iec_Gnd;			// = _T("Iec_Gnd");
	extern CString g_sLangTxt_Iec_Gnd;			// = _T("?");
	extern CString g_sLangID_Iec_ZeroSeq;		// = _T("Iec_ZeroSeq");
	extern CString g_sLangTxt_Iec_ZeroSeq;		// = _T("??");
	extern CString g_sLangID_Iec_RatedDelay;	// = _T("Iec_RatedDelay");
	extern CString g_sLangTxt_Iec_RatedDelay;	// = _T("????");
