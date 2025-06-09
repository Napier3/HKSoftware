//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XLanguageResourceBase.cpp  CXLanguageResourceAtsBase


#include "stdafx.h"
#include "XLanguageResourceIec.h"
#include "../../Module/API/GlobalConfigApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CString g_strXLangRsIecBaseFile = _T("RsIecBase"); //2016.10.13 


CXLanguageResourceIecBase::CXLanguageResourceIecBase()
{

}


CXLanguageResourceIecBase::~CXLanguageResourceIecBase()
{

	m_oXLangRsIecBase.RemoveAll(); //2016.10.13 
}

void CXLanguageResourceIecBase::InitLangFileForDebug(const CString &strModule)
{
	m_strXLangFile = _P_GetLanguagePath();
	m_strXLangFile.AppendFormat(_T("%s.xml"), strModule.GetString());
}

CXLangItem* CXLanguageResourceIecBase::rs_AddString(const CString &strID, CString *pstrString) //2016.10.13 
{
	CXLangItem *p = CXLanguage::AddString(strID, pstrString); //2016.10.13 

	m_oXLangRsIecBase.AddTail(p); //2016.10.13 

	return p;//2016.10.13 
}

void CXLanguageResourceIecBase::InitLangRsByFile() //2016.10.13 
{
	//CXLanguageResourceBase::InitLangRsByFile(); //2016.10.13 //dingxy 20240919 �Ż�����Ч�ʣ�RsBase�ļ��ظ���(CXLanguageResourceAtsBase::InitLangRsByFile)
	InitLangRsByFileEx(&m_oXLangRsIecBase, g_strXLangRsIecBaseFile);  //2016.10.13 
}


void CXLanguageResourceIecBase::RegisterLanguageResource()
{
	CXLanguageResourceBase::RegisterLanguageResource();
	/*rs_AddString(g_sLangID_Home, &g_sLangTxt_Home);*/
	rs_AddString(g_sLid_SICDGSerial, &g_sLtxt_SICDGSerial);    //����Ϊ���������� 20161014
	rs_AddString(g_sLid_SICDSelect, &g_sLtxt_SICDSelect);    //����Ϊ���������� 20161014
	rs_AddString(g_sLid_SICDIED, &g_sLtxt_SICDIED);    //����Ϊ���������� 20161014
	rs_AddString(g_sLid_SICDAP, &g_sLtxt_SICDAP);    //����Ϊ���������� 20161014
	rs_AddString(g_sLid_SICDChaNO, &g_sLtxt_SICDChaNO);    //����Ϊ���������� 20161014
	rs_AddString(g_sLid_SICDTotCha, &g_sLtxt_SICDTotCha);    //����Ϊ���������� 20161014
	rs_AddString(g_sLid_SICDDataSet, &g_sLtxt_SICDDataSet);    //����Ϊ���������� 20161014
	rs_AddString(g_sLid_SICDDataSetDes, &g_sLtxt_SICDDataSetDes);    //����Ϊ���������� 20161014
	rs_AddString(g_sLid_SICDRefChaNO, &g_sLtxt_SICDRefChaNO);    //����Ϊ���������� 20161014
	rs_AddString(g_sLid_SICDDesMAC, &g_sLtxt_SICDDesMAC);    //����Ϊ���������� 20161014
	rs_AddString(g_sLid_SourceMAC, &g_sLtxt_SourceMAC);    //����Ϊ���������� 20161014
	rs_AddString(g_sLid_OutputSel, &g_sLtxt_OutputSel);    //����Ϊ���������� 20161014
	rs_AddString(g_sLid_VersionNumber, &g_sLtxt_VersionNumber);    //����Ϊ���������� 20161014
	rs_AddString(g_sLid_SampleDelay, &g_sLtxt_SampleDelay);    //����Ϊ���������� 20161014
	rs_AddString(g_sLid_SynMode, &g_sLtxt_SynMode);    //����Ϊ���������� 20161014

	rs_AddString(g_sLid_Description, &g_sLtxt_Description);    //����Ϊ���������� 20161014
	rs_AddString(g_sLid_TestMark, &g_sLtxt_TestMark);    //����Ϊ���������� 20161014
	rs_AddString(g_sLid_ShortTransTime, &g_sLtxt_ShortTransTime);    //����Ϊ���������� 20161014
	rs_AddString(g_sLid_StaRetransT, &g_sLtxt_StaRetransT);    //����Ϊ���������� 20161014
	rs_AddString(g_sLid_Interval, &g_sLtxt_Interval);    //����Ϊ���������� 20161014
	rs_AddString(g_sLid_TimeQualty, &g_sLtxt_TimeQualty);    //����Ϊ���������� 20161014
	rs_AddString(g_sLid_TimeAllowToLive, &g_sLtxt_TimeAllowToLive);    //����Ϊ���������� 20161014
	rs_AddString(g_sLid_InputSel, &g_sLtxt_InputSel);    //����Ϊ���������� 20161014
	rs_AddString(g_sLid_AnaGoCBGooseIDAppID, &g_sLtxt_AnaGoCBGooseIDAppID);    //����Ϊ���������� 20161014

	rs_AddString(g_sLid_SMVChannel, &g_sLtxt_SMVChannel);    //����Ϊ���������� 20161015
	rs_AddString(g_sLid_ChannelType, &g_sLtxt_ChannelType);    //����Ϊ���������� 20161015
	rs_AddString(g_sLid_TestDeviceChannel, &g_sLtxt_TestDeviceChannel);    //����Ϊ���������� 20161015
	rs_AddString(g_sLid_Quality, &g_sLtxt_Quality);    //����Ϊ���������� 20161015
	rs_AddString(g_sLid_InputName, &g_sLtxt_InputName);    //����Ϊ���������� 20161015
	rs_AddString(g_sLid_InputPath, &g_sLtxt_InputPath);    //����Ϊ���������� 20161015

	rs_AddString(g_sLid_InitialValue, &g_sLtxt_InitialValue);    //����Ϊ���������� 20161015
	rs_AddString(g_sLid_InputMap, &g_sLtxt_InputMap);    //����Ϊ���������� 20161015

	rs_AddString(g_sLid_LNDescrip, &g_sLtxt_LNDescrip);    //����Ϊ���������� 20161015
	rs_AddString(g_sLid_DOIDescrip, &g_sLtxt_DOIDescrip);    //����Ϊ���������� 20161015
	rs_AddString(g_sLid_DAIDescrip, &g_sLtxt_DAIDescrip);    //����Ϊ���������� 20161015
	rs_AddString(g_sLid_Address, &g_sLtxt_Address);    //����Ϊ���������� 20161015

	rs_AddString(g_sLid_Map, &g_sLtxt_Map);    //����Ϊ���������� 20161015
	rs_AddString(g_sLid_InterLNDes, &g_sLtxt_InterLNDes);    //����Ϊ���������� 20161015
	rs_AddString(g_sLid_ExterLNDes, &g_sLtxt_ExterLNDes);    //����Ϊ���������� 20161015
	rs_AddString(g_sLid_InterDODes, &g_sLtxt_InterDODes);    //����Ϊ���������� 20161015
	rs_AddString(g_sLid_ExterDODes, &g_sLtxt_ExterDODes);    //����Ϊ���������� 20161015
	rs_AddString(g_sLid_InterDUDes, &g_sLtxt_InterDUDes);    //����Ϊ���������� 20161015
	rs_AddString(g_sLid_ExterDUDes, &g_sLtxt_ExterDUDes);    //����Ϊ���������� 20161015
	rs_AddString(g_sLid_InterNO, &g_sLtxt_InterNO);    //����Ϊ���������� 20161015
	rs_AddString(g_sLid_ExterNO, &g_sLtxt_ExterNO);    //����Ϊ���������� 20161015
	rs_AddString(g_sLid_InterPath, &g_sLtxt_InterPath);    //����Ϊ���������� 20161015
	rs_AddString(g_sLid_ExterPath, &g_sLtxt_ExterPath);    //����Ϊ���������� 20161015

	rs_AddString(g_sLid_DUDes, &g_sLtxt_DUDes);    //����Ϊ���������� 20161015  
	rs_AddString(g_sLangID_IEC61850Config, &g_sLangTxt_IEC61850Config);
	rs_AddString(g_sLangID_TesterIEC61850Config, &g_sLangTxt_TesterIEC61850Config);
	rs_AddString(g_sLangID_MsgMonitorWnd, &g_sLangTxt_MsgMonitorWnd);
	rs_AddString(g_sLangID_WaveMonitorWnd, &g_sLangTxt_WaveMonitorWnd);
	rs_AddString(g_sLangID_NoneConfigFile, &g_sLangTxt_NoneConfigFile);
	rs_AddString(g_sLangID_NoneSclFile, &g_sLangTxt_NoneSclFile);
	rs_AddString(g_sLangID_SclFile, &g_sLangTxt_SclFile);
	rs_AddString(g_sLangID_SclStateTool, &g_sLangTxt_SclStateTool);

	rs_AddString(g_sLangID_TesterLinkSucc, &g_sLangTxt_TesterLinkSucc);
	rs_AddString(g_sLangID_LinkFail, &g_sLangTxt_LinkFail);
	rs_AddString(g_sLangID_RecevElectricalTestEndMsg, &g_sLangTxt_RecevElectricalTestEndMsg);
	rs_AddString(g_sLangID_DownloadParaFail, &g_sLangTxt_DownloadParaFail);
	rs_AddString(g_sLangID_TesterInterfNoIed61850ConfigFunc, &g_sLangTxt_TesterInterfNoIed61850ConfigFunc);
	rs_AddString(g_sLangID_TesterTestFuncOvertime, &g_sLangTxt_TesterTestFuncOvertime);
	rs_AddString(g_sLangID_Channel, &g_sLangTxt_Channel);
	rs_AddString(g_sLangID_DefaultConfigFileNone, &g_sLangTxt_DefaultConfigFileNone);

	rs_AddString(g_sLangID_GooseoutGroup, &g_sLangTxt_GooseoutGroup);
	rs_AddString(g_sLangID_PortConflict, &g_sLangTxt_PortConflict);
	rs_AddString(g_sLangID_GooseinGroup, &g_sLangTxt_GooseinGroup);
	rs_AddString(g_sLangID_SameOpening, &g_sLangTxt_SameOpening);

	rs_AddString(g_sLangID_TesterConfigFile, &g_sLangTxt_TesterConfigFile);
	rs_AddString(g_sLangID_Iec61850Config, &g_sLangTxt_Iec61850Config);
	rs_AddString(g_sLangID_ErrFileFormat, &g_sLangTxt_ErrFileFormat);
	rs_AddString(g_sLangID_DiffSvmConfig, &g_sLangTxt_DiffSvmConfig);
	rs_AddString(g_sLangID_NoMatchData, &g_sLangTxt_NoMatchData);
	rs_AddString(g_sLangID_NoSelData, &g_sLangTxt_NoSelData);
	rs_AddString(g_sLangID_NoExisDataIndex, &g_sLangTxt_NoExisDataIndex);

	rs_AddString(g_sLangID_AppBin, &g_sLangTxt_AppBin);
	rs_AddString(g_sLangID_BindMac, &g_sLangTxt_BindMac);
	rs_AddString(g_sLangID_BindAppID, &g_sLangTxt_BindAppID);
	rs_AddString(g_sLangID_BindChannel, &g_sLangTxt_BindChannel);
	rs_AddString(g_sLangID_OptrBindAppBinInfo, &g_sLangTxt_OptrBindAppBinInfo);
    rs_AddString(g_sLangID_Channel2, &g_sLangTxt_Channel2);
	rs_AddString(g_sLangID_Iec_Relay, &g_sLangTxt_Iec_Relay);
	rs_AddString(g_sLangID_Iec_Measure, &g_sLangTxt_Iec_Measure);
	rs_AddString(g_sLangID_Iec_Current, &g_sLangTxt_Iec_Current);
	rs_AddString(g_sLangID_Iec_Voltage, &g_sLangTxt_Iec_Voltage);
	rs_AddString(g_sLangID_Iec_Gnd, &g_sLangTxt_Iec_Gnd);
	rs_AddString(g_sLangID_Iec_ZeroSeq, &g_sLangTxt_Iec_ZeroSeq);
	rs_AddString(g_sLangID_Iec_RatedDelay, &g_sLangTxt_Iec_RatedDelay);
}

static long g_nCXLanguageResourceIecBase_InitLangTxt = 0;

void CXLanguageResourceIecBase::InitLangTxt()
{
	CXLanguageResourceBase::InitLangTxt();

	if (g_nCXLanguageResourceIecBase_InitLangTxt > 0)
	{
		return;
	}

	g_nCXLanguageResourceIecBase_InitLangTxt = 1;

	g_sLid_SICDGSerial                = _T("sSICDGSerial"); // ����Ϊ�ı������� 20161014
	g_sLtxt_SICDGSerial               = _T("���");      //����Ϊ�ı������� 20161014
	g_sLid_SICDSelect                = _T("sSICDSelect"); // ����Ϊ�ı������� 20161014
	g_sLtxt_SICDSelect               = _T("ѡ��");      //����Ϊ�ı������� 20161014
	g_sLid_SICDIED               = _T("sSICDIED"); // ����Ϊ�ı������� 20161014
	g_sLtxt_SICDIED               = _T("���ƿ�����IED");      //����Ϊ�ı������� 20161014
	g_sLid_SICDAP               = _T("sSICDAP"); // ����Ϊ�ı������� 20161014
	g_sLtxt_SICDAP               = _T("���ƿ�����AP");      //����Ϊ�ı������� 20161014
	g_sLid_SICDChaNO               = _T("sSICDChaNO"); // ����Ϊ�ı������� 20161014
	g_sLtxt_SICDChaNO               = _T("ͨ����");      //����Ϊ�ı������� 20161014
	g_sLid_SICDTotCha               = _T("sSICDTotCha"); // ����Ϊ�ı������� 20161014
	g_sLtxt_SICDTotCha               = _T("��ͨ����");      //����Ϊ�ı������� 20161014
	g_sLid_SICDDataSet               = _T("sDataSetDesc"); // ����Ϊ�ı������� 20161014
	g_sLtxt_SICDDataSet             = _T("���ƿ��������ݼ�����");      //����Ϊ�ı������� 20161014
	g_sLid_SICDDataSetDes               = _T("sDataSetDes"); // ����Ϊ�ı������� 20161014
	g_sLtxt_SICDDataSetDes             = _T("���ݼ�����");      //����Ϊ�ı������� 20161014
	g_sLid_SICDRefChaNO               = _T("sSICDRefChaNO"); // ����Ϊ�ı������� 20161014
	g_sLtxt_SICDRefChaNO             = _T("����ͨ����");      //����Ϊ�ı������� 20161014
	g_sLid_SICDDesMAC               = _T("sDesMAC"); // ����Ϊ�ı������� 20161014
	g_sLtxt_SICDDesMAC             = _T("Ŀ��MAC");      //����Ϊ�ı������� 20161014
	g_sLid_SourceMAC               = _T("sSourceMAC"); // ����Ϊ�ı������� 20161014
	g_sLtxt_SourceMAC             = _T("ԴMAC");      //����Ϊ�ı������� 20161014
	g_sLid_OutputSel               = _T("sOutputSel"); // ����Ϊ�ı������� 20161014
	g_sLtxt_OutputSel            = _T("�����ѡ��");      //����Ϊ�ı������� 20161014
	g_sLid_VersionNumber               = _T("sVersionNumber"); // ����Ϊ�ı������� 20161014
	g_sLtxt_VersionNumber             = _T("�汾��");      //����Ϊ�ı������� 20161014
	g_sLid_SampleDelay               = _T("sSampleDelay"); // ����Ϊ�ı������� 20161014
	g_sLtxt_SampleDelay             = _T("������ʱ");      //����Ϊ�ı������� 20161014
	g_sLid_SynMode               = _T("sSynMode"); // ����Ϊ�ı������� 20161014
	g_sLtxt_SynMode            = _T("ͬ����ʽ");      //����Ϊ�ı������� 20161014

	g_sLid_Description               = _T("sDescription"); // ����Ϊ�ı������� 20161014
	g_sLtxt_Description            = _T("����");      //����Ϊ�ı������� 20161014
	g_sLid_TestMark               = _T("sTestMark"); // ����Ϊ�ı������� 20161014
	g_sLtxt_TestMark           = _T("���Ա��");      //����Ϊ�ı������� 20161014
	g_sLid_ShortTransTime               = _T("sShortTransTime"); // ����Ϊ�ı������� 20161014
	g_sLtxt_ShortTransTime           = _T("��̴���ʱ��(ms)");      //����Ϊ�ı������� 20161014
	g_sLid_StaRetransT              = _T("sStaRetransT"); // ����Ϊ�ı������� 20161014
	g_sLtxt_StaRetransT            = _T("�ȶ��������ش�ʱ��(ms)");      //����Ϊ�ı������� 20161014
	g_sLid_Interval               = _T("sInterval"); // ����Ϊ�ı������� 20161014
	g_sLtxt_Interval            = _T("�����ʱ(ms)");      //����Ϊ�ı������� 20161014
	g_sLid_TimeQualty               = _T("sTimeQualty"); // ����Ϊ�ı������� 20161014
	g_sLtxt_TimeQualty            = _T("ʱ��Ʒ��");      //����Ϊ�ı������� 20161014
	g_sLid_TimeAllowToLive               = _T("sTimeAllowToLive"); // ����Ϊ�ı������� 20161014
	g_sLtxt_TimeAllowToLive           = _T("��������ʱ��(ms)");      //����Ϊ�ı������� 20161014

	g_sLid_InputSel           = _T("sInputSel"); // ����Ϊ�ı������� 20161014
	g_sLtxt_InputSel           = _T("�����ѡ��");      //����Ϊ�ı������� 20161014
	g_sLid_AnaGoCBGooseIDAppID           = _T("sAnaGoCBGooseIDAppID"); // ����Ϊ�ı������� 20161014
	g_sLtxt_AnaGoCBGooseIDAppID           = _T("�Ƿ����GoCB,GooseID");      //����Ϊ�ı������� 20161014

	g_sLid_SMVChannel               = _T("sSMVChannel"); // ����Ϊ�ı������� 20161014
	g_sLtxt_SMVChannel           = _T("SMVͨ��");      //����Ϊ�ı������� 20161014
	g_sLid_ChannelType              = _T("sChannelType"); // ����Ϊ�ı������� 20161014
	g_sLtxt_ChannelType          = _T("ͨ������");      //����Ϊ�ı������� 20161014
	g_sLid_TestDeviceChannel               = _T("sTestDeviceChannel"); // ����Ϊ�ı������� 20161014
	g_sLtxt_TestDeviceChannel          = _T("������ͨ��");      //����Ϊ�ı������� 20161014
	g_sLid_Quality               = _T("sQuality"); // ����Ϊ�ı������� 20161014
	g_sLtxt_Quality          = _T("Ʒ��");      //����Ϊ�ı������� 20161014
	g_sLid_InputName               = _T("sInputName"); // ����Ϊ�ı������� 20161014
	g_sLtxt_InputName          = _T("�����-����");      //����Ϊ�ı������� 20161014
	g_sLid_InputPath               = _T("sInputPath"); // ����Ϊ�ı������� 20161014
	g_sLtxt_InputPath           = _T("�����-·��");      //����Ϊ�ı������� 20161014

	g_sLid_InitialValue               = _T("sInitialValue"); // ����Ϊ�ı������� 20161015
	g_sLtxt_InitialValue          = _T("��ʼֵ");      //����Ϊ�ı������� 20161015
	g_sLid_InputMap               = _T("sInputMap"); // ����Ϊ�ı������� 20161015
	g_sLtxt_InputMap         = _T("������ӳ��");      //����Ϊ�ı������� 20161015

	g_sLid_LNDescrip               = _T("sLNDescrip"); // ����Ϊ�ı������� 20161015
	g_sLtxt_LNDescrip        = _T("LN����");      //����Ϊ�ı������� 20161015
	g_sLid_DOIDescrip               = _T("sDOIDescrip"); // ����Ϊ�ı������� 20161015
	g_sLtxt_DOIDescrip         = _T("DOI����");      //����Ϊ�ı������� 20161015
	g_sLid_DAIDescrip               = _T("sDAIDescrip"); // ����Ϊ�ı������� 20161015
	g_sLtxt_DAIDescrip         = _T("DAI����");      //����Ϊ�ı������� 20161015
	g_sLid_Address               = _T("sAddress"); // ����Ϊ�ı������� 20161015
	g_sLtxt_Address         = _T("��ַ");      //����Ϊ�ı������� 20161015


	g_sLid_Map               = _T("sMap"); // ����Ϊ�ı������� 20161015
	g_sLtxt_Map         = _T("ӳ��");      //����Ϊ�ı������� 20161015
	g_sLid_InterLNDes               = _T("sInterLNDes"); // ����Ϊ�ı������� 20161015
	g_sLtxt_InterLNDes         = _T("�ڲ�LN����");      //����Ϊ�ı������� 20161015
	g_sLid_ExterLNDes               = _T("sExterLNDes"); // ����Ϊ�ı������� 20161015
	g_sLtxt_ExterLNDes         = _T("�ⲿLN����");      //����Ϊ�ı������� 20161015
	g_sLid_InterDODes               = _T("sInterDODes"); // ����Ϊ�ı������� 20161015
	g_sLtxt_InterDODes         = _T("�ڲ�DO����");      //����Ϊ�ı������� 20161015
	g_sLid_ExterDODes               = _T("sExterDODes"); // ����Ϊ�ı������� 20161015
	g_sLtxt_ExterDODes         = _T("�ⲿDO����");      //����Ϊ�ı������� 20161015
	g_sLid_InterDUDes               = _T("sInterDUDes"); // ����Ϊ�ı������� 20161015
	g_sLtxt_InterDUDes         = _T("�ڲ�DU����");      //����Ϊ�ı������� 20161015
	g_sLid_ExterDUDes               = _T("sExterDUDes"); // ����Ϊ�ı������� 20161015
	g_sLtxt_ExterDUDes         = _T("�ⲿDU����");      //����Ϊ�ı������� 20161015
	g_sLid_InterNO               = _T("sInterNO"); // ����Ϊ�ı������� 20161015
	g_sLtxt_InterNO         = _T("�ڲ����");      //����Ϊ�ı������� 20161015
	g_sLid_ExterNO               = _T("sExterNO"); // ����Ϊ�ı������� 20161015
	g_sLtxt_ExterNO         = _T("�ⲿ���");      //����Ϊ�ı������� 20161015
	g_sLid_InterPath               = _T("sInterPath"); // ����Ϊ�ı������� 20161015
	g_sLtxt_InterPath         = _T("�ڲ�·��");      //����Ϊ�ı������� 20161015
	g_sLid_ExterPath               = _T("sExterPath"); // ����Ϊ�ı������� 20161015
	g_sLtxt_ExterPath         = _T("�ⲿ·��");      //����Ϊ�ı������� 20161015

	g_sLid_DUDes              = _T("sDUDes"); // ����Ϊ�ı������� 20161015
	g_sLtxt_DUDes         = _T("DU����");      //����Ϊ�ı������� 20161015  


	g_sLangID_IEC61850Config              = _T("sIEC61850Config"); 
	g_sLangTxt_IEC61850Config             = _T("IEC61850����������");     

	g_sLangID_TesterIEC61850Config              = _T("sTesterIEC61850Config"); 
	g_sLangTxt_TesterIEC61850Config             = _T("������IEC61850Config");  
	g_sLangID_MsgMonitorWnd              = _T("sMsgMonitorWnd"); 
	g_sLangTxt_MsgMonitorWnd             = _T("���ļ��Ӵ���"); 
	g_sLangID_WaveMonitorWnd              = _T("sWaveMonitorWnd"); 
	g_sLangTxt_WaveMonitorWnd             = _T("���μ��Ӵ���");
	g_sLangID_NoneConfigFile              = _T("sNoneConfigFile"); 
	g_sLangTxt_NoneConfigFile            = _T("�����ļ���%s��������");
	g_sLangID_NoneSclFile             = _T("sNoneSclFile"); 
	g_sLangTxt_NoneSclFile            = _T("û��ѡ��SCL�ļ�");
	g_sLangID_SclFile             = _T("sSclFile"); 
	g_sLangTxt_SclFile            = _T("SCL�ļ�");
	g_sLangID_SclStateTool             = _T("sSclStateTool"); 
	g_sLangTxt_SclStateTool            = _T("SCL״̬���й���");


	g_sLangID_TesterLinkSucc             = _T("sTesterLinkSucc"); 
	g_sLangTxt_TesterLinkSucc            = _T("�����������ɹ�");  
	g_sLangID_LinkFail              = _T("sLinkFail"); 
	g_sLangTxt_LinkFail             = _T("����ʧ��"); 
	g_sLangID_RecevElectricalTestEndMsg              = _T("sRecevElectricalTestEndMsg"); 
	g_sLangTxt_RecevElectricalTestEndMsg             = _T("�յ����������Խ�����Ϣ��");
	g_sLangID_DownloadParaFail              = _T("sDownloadParaFail"); 
	g_sLangTxt_DownloadParaFail           = _T("��������ʧ��");
	g_sLangID_TesterInterfNoIed61850ConfigFunc             = _T("sTesterInterfNoIed61850ConfigFunc"); 
	g_sLangTxt_TesterInterfNoIed61850ConfigFunc            = _T("���������ײ㹦�ܽӿڲ�֧������Iec61850���ò��Թ���");
	g_sLangID_TesterTestFuncOvertime             = _T("sTesterTestFuncOvertime"); 
	g_sLangTxt_TesterTestFuncOvertime            = _T("���������ײ���Թ��ܲ��Գ�ʱ");

	g_sLangID_Channel                = _T("sChannel");  
	g_sLangTxt_Channel               =_T("ͨ��%d");
	g_sLangID_DefaultConfigFileNone                = _T("sDefaultConfigFileNone");  
	g_sLangTxt_DefaultConfigFileNone                  =_T("ȱʡ�����ļ���%s��������");

	g_sLangID_GooseoutGroup                = _T("sGooseoutGroup");  
	g_sLangTxt_GooseoutGroup                  =_T("GOOSEOUT��%d��");
	g_sLangID_PortConflict                = _T("sPortConflict");  
	g_sLangTxt_PortConflict                  =_T("��%s���롾%s�������ڳ�ͻ");
	g_sLangID_GooseinGroup                = _T("sGooseinGroup");  
	g_sLangTxt_GooseinGroup                  =_T("GOOSEIN��%d��");
	g_sLangID_SameOpening                = _T("sSameOpening");  
	g_sLangTxt_SameOpening                  =_T("��%s$%s���롾%s$%s��ʹ����ͬ�Ŀ��롾%s��");

	g_sLangID_Iec61850Config                = _T("sIec61850Config");  
	g_sLangTxt_Iec61850Config                  =_T("IEC61850����");
	g_sLangID_TesterConfigFile                = _T("sTesterConfigFile");  
	g_sLangTxt_TesterConfigFile                  =_T("�����������ļ�");
	g_sLangID_ErrFileFormat                = _T("sErrFileFormat");  
	g_sLangTxt_ErrFileFormat                  =_T("�ļ���%s����ʽ����ȷ���汾�����ݣ���ʹ��PowerTest���õ��ļ�");
	g_sLangID_DiffSvmConfig               = _T("sDiffSvmConfig");  
	g_sLangTxt_DiffSvmConfig                  =_T("��ӵ�SMV���ö����뵱ǰ�����ò�һ��");
	g_sLangID_NoMatchData                = _T("sNoMatchData");  
	g_sLangTxt_NoMatchData                  =_T("���ݸ���ʧ�ܣ������������಻ƥ��");
	g_sLangID_NoSelData                = _T("sNoSelData");  
	g_sLangTxt_NoSelData                 =_T("���ݸ���ʧ�ܣ�������������û��ѡ��");
	g_sLangID_NoExisDataIndex                = _T("sNoExisDataIndex");  
	g_sLangTxt_NoExisDataIndex                  =_T("���ݸ���ʧ�ܣ�������������%d������");

	g_sLangID_AppBin  = _T("sAppBin");
	g_sLangTxt_AppBin  = _T("�����ǿ���");
	g_sLangID_BindMac  = _T("sBindMa");
	g_sLangTxt_BindMac  = _T("�󶨿��ƿ�MAC");
	g_sLangID_BindAppID = _T("sBindAppID");
	g_sLangTxt_BindAppID = _T("�󶨿��ƿ�APPID");
	g_sLangID_BindChannel = _T("sBindChannel");
	g_sLangTxt_BindChannel = _T("��ͨ��");
	g_sLangID_OptrBindAppBinInfo = _T("sOptrBindAppBinInfo");
	g_sLangTxt_OptrBindAppBinInfo = _T("������˫����ѡ�еĿ��ƿ�ͨ���������ǿ��룬�ٴ�˫����ȥ��;��delete��ɾ��ѡ�еİ�");

    g_sLangID_Channel2 = _T("sChannel2");
    g_sLangTxt_Channel2 =_T("ͨ��");

	g_sLangID_Iec_Relay = _T("Iec_Relay");
	g_sLangTxt_Iec_Relay = _T("����");
	g_sLangID_Iec_Measure = _T("Iec_Measure");
	g_sLangTxt_Iec_Measure = _T("����");
	g_sLangID_Iec_Current = _T("Iec_Current");
	g_sLangTxt_Iec_Current = _T("����");
	g_sLangID_Iec_Voltage = _T("Iec_Voltage");
	g_sLangTxt_Iec_Voltage = _T("��ѹ");
	g_sLangID_Iec_Gnd = _T("Iec_Gnd");
	g_sLangTxt_Iec_Gnd = _T("��");
	g_sLangID_Iec_ZeroSeq = _T("Iec_ZeroSeq");
	g_sLangTxt_Iec_ZeroSeq = _T("����");
	g_sLangID_Iec_RatedDelay = _T("Iec_RatedDelay");
	g_sLangTxt_Iec_RatedDelay = _T("���ʱ");


}

//CString g_sLangID_Home                 = _T("sHome");
//CString g_sLangTxt_Home                = _T("��ҳ(H)");

CString g_sLid_SICDGSerial                ; //= _T("sSICDGSerial"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_SICDGSerial               ; //= _T("���");      //����Ϊ�ı������� 20161014
CString g_sLid_SICDSelect                ; //= _T("sSICDSelect"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_SICDSelect               ; //= _T("ѡ��");      //����Ϊ�ı������� 20161014
CString g_sLid_SICDIED               ; //= _T("sSICDIED"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_SICDIED               ; //= _T("���ƿ�����IED");      //����Ϊ�ı������� 20161014
CString g_sLid_SICDAP               ; //= _T("sSICDAP"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_SICDAP               ; //= _T("���ƿ�����AP");      //����Ϊ�ı������� 20161014
CString g_sLid_SICDChaNO               ; //= _T("sSICDChaNO"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_SICDChaNO               ; //= _T("ͨ����");      //����Ϊ�ı������� 20161014
CString g_sLid_SICDTotCha               ; //= _T("sSICDTotCha"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_SICDTotCha               ; //= _T("��ͨ����");      //����Ϊ�ı������� 20161014
CString g_sLid_SICDDataSet               ; //= _T("sDataSetDesc"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_SICDDataSet             ; //= _T("���ƿ��������ݼ�����");      //����Ϊ�ı������� 20161014
CString g_sLid_SICDDataSetDes               ; //= _T("sDataSetDes"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_SICDDataSetDes             ; //= _T("���ݼ�����");      //����Ϊ�ı������� 20161014
CString g_sLid_SICDRefChaNO               ; //= _T("sSICDRefChaNO"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_SICDRefChaNO             ; //= _T("����ͨ����");      //����Ϊ�ı������� 20161014
CString g_sLid_SICDDesMAC               ; //= _T("sDesMAC"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_SICDDesMAC             ; //= _T("Ŀ��MAC");      //����Ϊ�ı������� 20161014
CString g_sLid_SourceMAC               ; //= _T("sSourceMAC"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_SourceMAC             ; //= _T("ԴMAC");      //����Ϊ�ı������� 20161014
CString g_sLid_OutputSel               ; //= _T("sOutputSel"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_OutputSel            ; //= _T("�����ѡ��");      //����Ϊ�ı������� 20161014
CString g_sLid_VersionNumber               ; //= _T("sVersionNumber"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_VersionNumber             ; //= _T("�汾��");      //����Ϊ�ı������� 20161014
CString g_sLid_SampleDelay               ; //= _T("sSampleDelay"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_SampleDelay             ; //= _T("������ʱ");      //����Ϊ�ı������� 20161014
CString g_sLid_SynMode               ; //= _T("sSynMode"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_SynMode            ; //= _T("ͬ����ʽ");      //����Ϊ�ı������� 20161014

CString g_sLid_Description               ; //= _T("sDescription"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_Description            ; //= _T("����");      //����Ϊ�ı������� 20161014
CString g_sLid_TestMark               ; //= _T("sTestMark"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_TestMark           ; //= _T("���Ա��");      //����Ϊ�ı������� 20161014
CString g_sLid_ShortTransTime               ; //= _T("sShortTransTime"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_ShortTransTime           ; //= _T("��̴���ʱ��(ms)");      //����Ϊ�ı������� 20161014
CString g_sLid_StaRetransT              ; //= _T("sStaRetransT"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_StaRetransT            ; //= _T("�ȶ��������ش�ʱ��(ms)");      //����Ϊ�ı������� 20161014
CString g_sLid_Interval               ; //= _T("sInterval"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_Interval            ; //= _T("�����ʱ(ms)");      //����Ϊ�ı������� 20161014
CString g_sLid_TimeQualty               ; //= _T("sTimeQualty"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_TimeQualty            ; //= _T("ʱ��Ʒ��");      //����Ϊ�ı������� 20161014
CString g_sLid_TimeAllowToLive               ; //= _T("sTimeAllowToLive"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_TimeAllowToLive           ; //= _T("��������ʱ��(ms)");      //����Ϊ�ı������� 20161014

CString g_sLid_InputSel           ; //= _T("sInputSel"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_InputSel           ; //= _T("�����ѡ��");      //����Ϊ�ı������� 20161014
CString g_sLid_AnaGoCBGooseIDAppID           ; //= _T("sAnaGoCBGooseIDAppID"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_AnaGoCBGooseIDAppID           ; //= _T("�Ƿ����GoCB,GooseID");      //����Ϊ�ı������� 20161014

CString g_sLid_SMVChannel               ; //= _T("sSMVChannel"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_SMVChannel           ; //= _T("SMVͨ��");      //����Ϊ�ı������� 20161014
CString g_sLid_ChannelType              ; //= _T("sChannelType"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_ChannelType          ; //= _T("ͨ������");      //����Ϊ�ı������� 20161014
CString g_sLid_TestDeviceChannel               ; //= _T("sTestDeviceChannel"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_TestDeviceChannel          ; //= _T("������ͨ��");      //����Ϊ�ı������� 20161014
CString g_sLid_Quality               ; //= _T("sQuality"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_Quality          ; //= _T("Ʒ��");      //����Ϊ�ı������� 20161014
CString g_sLid_InputName               ; //= _T("sInputName"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_InputName          ; //= _T("�����-����");      //����Ϊ�ı������� 20161014
CString g_sLid_InputPath               ; //= _T("sInputPath"); // ����Ϊ�ı������� 20161014
CString g_sLtxt_InputPath           ; //= _T("�����-·��");      //����Ϊ�ı������� 20161014

CString g_sLid_InitialValue               ; //= _T("sInitialValue"); // ����Ϊ�ı������� 20161015
CString g_sLtxt_InitialValue          ; //= _T("��ʼֵ");      //����Ϊ�ı������� 20161015
CString g_sLid_InputMap               ; //= _T("sInputMap"); // ����Ϊ�ı������� 20161015
CString g_sLtxt_InputMap         ; //= _T("������ӳ��");      //����Ϊ�ı������� 20161015

CString g_sLid_LNDescrip               ; //= _T("sLNDescrip"); // ����Ϊ�ı������� 20161015
CString g_sLtxt_LNDescrip        ; //= _T("LN����");      //����Ϊ�ı������� 20161015
CString g_sLid_DOIDescrip               ; //= _T("sDOIDescrip"); // ����Ϊ�ı������� 20161015
CString g_sLtxt_DOIDescrip         ; //= _T("DOI����");      //����Ϊ�ı������� 20161015
CString g_sLid_DAIDescrip               ; //= _T("sDAIDescrip"); // ����Ϊ�ı������� 20161015
CString g_sLtxt_DAIDescrip         ; //= _T("DAI����");      //����Ϊ�ı������� 20161015
CString g_sLid_Address               ; //= _T("sAddress"); // ����Ϊ�ı������� 20161015
CString g_sLtxt_Address         ; //= _T("��ַ");      //����Ϊ�ı������� 20161015


CString g_sLid_Map               ; //= _T("sMap"); // ����Ϊ�ı������� 20161015
CString g_sLtxt_Map         ; //= _T("ӳ��");      //����Ϊ�ı������� 20161015
CString g_sLid_InterLNDes               ; //= _T("sInterLNDes"); // ����Ϊ�ı������� 20161015
CString g_sLtxt_InterLNDes         ; //= _T("�ڲ�LN����");      //����Ϊ�ı������� 20161015
CString g_sLid_ExterLNDes               ; //= _T("sExterLNDes"); // ����Ϊ�ı������� 20161015
CString g_sLtxt_ExterLNDes         ; //= _T("�ⲿLN����");      //����Ϊ�ı������� 20161015
CString g_sLid_InterDODes               ; //= _T("sInterDODes"); // ����Ϊ�ı������� 20161015
CString g_sLtxt_InterDODes         ; //= _T("�ڲ�DO����");      //����Ϊ�ı������� 20161015
CString g_sLid_ExterDODes               ; //= _T("sExterDODes"); // ����Ϊ�ı������� 20161015
CString g_sLtxt_ExterDODes         ; //= _T("�ⲿDO����");      //����Ϊ�ı������� 20161015
CString g_sLid_InterDUDes               ; //= _T("sInterDUDes"); // ����Ϊ�ı������� 20161015
CString g_sLtxt_InterDUDes         ; //= _T("�ڲ�DU����");      //����Ϊ�ı������� 20161015
CString g_sLid_ExterDUDes               ; //= _T("sExterDUDes"); // ����Ϊ�ı������� 20161015
CString g_sLtxt_ExterDUDes         ; //= _T("�ⲿDU����");      //����Ϊ�ı������� 20161015
CString g_sLid_InterNO               ; //= _T("sInterNO"); // ����Ϊ�ı������� 20161015
CString g_sLtxt_InterNO         ; //= _T("�ڲ����");      //����Ϊ�ı������� 20161015
CString g_sLid_ExterNO               ; //= _T("sExterNO"); // ����Ϊ�ı������� 20161015
CString g_sLtxt_ExterNO         ; //= _T("�ⲿ���");      //����Ϊ�ı������� 20161015
CString g_sLid_InterPath               ; //= _T("sInterPath"); // ����Ϊ�ı������� 20161015
CString g_sLtxt_InterPath         ; //= _T("�ڲ�·��");      //����Ϊ�ı������� 20161015
CString g_sLid_ExterPath               ; //= _T("sExterPath"); // ����Ϊ�ı������� 20161015
CString g_sLtxt_ExterPath         ; //= _T("�ⲿ·��");      //����Ϊ�ı������� 20161015

CString g_sLid_DUDes              ; //= _T("sDUDes"); // ����Ϊ�ı������� 20161015
CString g_sLtxt_DUDes         ; //= _T("DU����");      //����Ϊ�ı������� 20161015  


CString g_sLangID_IEC61850Config              ; //= _T("sIEC61850Config"); 
CString g_sLangTxt_IEC61850Config             ; //= _T("IEC61850����������");     

CString g_sLangID_TesterIEC61850Config              ; //= _T("sTesterIEC61850Config"); 
CString g_sLangTxt_TesterIEC61850Config             ; //= _T("������IEC61850Config");  
CString g_sLangID_MsgMonitorWnd              ; //= _T("sMsgMonitorWnd"); 
CString g_sLangTxt_MsgMonitorWnd             ; //= _T("���ļ��Ӵ���"); 
CString g_sLangID_WaveMonitorWnd              ; //= _T("sWaveMonitorWnd"); 
CString g_sLangTxt_WaveMonitorWnd             ; //= _T("���μ��Ӵ���");
CString g_sLangID_NoneConfigFile              ; //= _T("sNoneConfigFile"); 
CString g_sLangTxt_NoneConfigFile            ; //= _T("�����ļ���%s��������");
CString g_sLangID_NoneSclFile             ; //= _T("sNoneSclFile"); 
CString g_sLangTxt_NoneSclFile            ; //= _T("û��ѡ��SCL�ļ�");
CString g_sLangID_SclFile             ; //= _T("sSclFile"); 
CString g_sLangTxt_SclFile            ; //= _T("SCL�ļ�");
CString g_sLangID_SclStateTool             ; //= _T("sSclStateTool"); 
CString g_sLangTxt_SclStateTool            ; //= _T("SCL״̬���й���");


CString g_sLangID_TesterLinkSucc             ; //= _T("sTesterLinkSucc"); 
CString g_sLangTxt_TesterLinkSucc            ; //= _T("�����������ɹ�");  
CString g_sLangID_LinkFail              ; //= _T("sLinkFail"); 
CString g_sLangTxt_LinkFail             ; //= _T("����ʧ��"); 
CString g_sLangID_RecevElectricalTestEndMsg              ; //= _T("sRecevElectricalTestEndMsg"); 
CString g_sLangTxt_RecevElectricalTestEndMsg             ; //= _T("�յ����������Խ�����Ϣ��");
CString g_sLangID_DownloadParaFail              ; //= _T("sDownloadParaFail"); 
CString g_sLangTxt_DownloadParaFail           ; //= _T("��������ʧ��");
CString g_sLangID_TesterInterfNoIed61850ConfigFunc             ; //= _T("sTesterInterfNoIed61850ConfigFunc"); 
CString g_sLangTxt_TesterInterfNoIed61850ConfigFunc            ; //= _T("���������ײ㹦�ܽӿڲ�֧������Iec61850���ò��Թ���");
CString g_sLangID_TesterTestFuncOvertime             ; //= _T("sTesterTestFuncOvertime"); 
CString g_sLangTxt_TesterTestFuncOvertime            ; //= _T("���������ײ���Թ��ܲ��Գ�ʱ");

CString g_sLangID_Channel                ; //= _T("sChannel");  
CString g_sLangTxt_Channel               ; //=_T("ͨ��%d");
CString g_sLangID_DefaultConfigFileNone                ; //= _T("sDefaultConfigFileNone");  
CString g_sLangTxt_DefaultConfigFileNone                  ; //=_T("ȱʡ�����ļ���%s��������");

CString g_sLangID_GooseoutGroup                ; //= _T("sGooseoutGroup");  
CString g_sLangTxt_GooseoutGroup                  ; //=_T("GOOSEOUT��%d��");
CString g_sLangID_PortConflict                ; //= _T("sPortConflict");  
CString g_sLangTxt_PortConflict                  ; //=_T("��%s���롾%s�������ڳ�ͻ");
CString g_sLangID_GooseinGroup                ; //= _T("sGooseinGroup");  
CString g_sLangTxt_GooseinGroup                  ; //=_T("GOOSEIN��%d��");
CString g_sLangID_SameOpening                ; //= _T("sSameOpening");  
CString g_sLangTxt_SameOpening                  ; //=_T("��%s$%s���롾%s$%s��ʹ����ͬ�Ŀ��롾%s��");

CString g_sLangID_Iec61850Config                ; //= _T("sIec61850Config");  
CString g_sLangTxt_Iec61850Config                  ; //=_T("IEC61850����");
CString g_sLangID_TesterConfigFile                ; //= _T("sTesterConfigFile");  
CString g_sLangTxt_TesterConfigFile                  ; //=_T("�����������ļ�");
CString g_sLangID_ErrFileFormat                ; //= _T("sErrFileFormat");  
CString g_sLangTxt_ErrFileFormat                  ; //=_T("�ļ���%s����ʽ����ȷ���汾�����ݣ���ʹ��PowerTest���õ��ļ�");
CString g_sLangID_DiffSvmConfig               ; //= _T("sDiffSvmConfig");  
CString g_sLangTxt_DiffSvmConfig                  ; //=_T("��ӵ�SMV���ö����뵱ǰ�����ò�һ��");
CString g_sLangID_NoMatchData                ; //= _T("sNoMatchData");  
CString g_sLangTxt_NoMatchData                  ; //=_T("���ݸ���ʧ�ܣ������������಻ƥ��");
CString g_sLangID_NoSelData                ; //= _T("sNoSelData");  
CString g_sLangTxt_NoSelData                 ; //=_T("���ݸ���ʧ�ܣ�������������û��ѡ��");
CString g_sLangID_NoExisDataIndex                ; //= _T("sNoExisDataIndex");  
CString g_sLangTxt_NoExisDataIndex                  ; //=_T("���ݸ���ʧ�ܣ�������������%d������");

CString g_sLangID_AppBin  ; //= _T("sAppBin");
CString g_sLangTxt_AppBin  ; //= _T("�����ǿ���");
CString g_sLangID_BindMac  ; //= _T("sBindMa");
CString g_sLangTxt_BindMac  ; //= _T("�󶨿��ƿ�MAC");
CString g_sLangID_BindAppID ; //= _T("sBindAppID");
CString g_sLangTxt_BindAppID ; //= _T("�󶨿��ƿ�APPID");
CString g_sLangID_BindChannel ; //= _T("sBindChannel");
CString g_sLangTxt_BindChannel ; //= _T("��ͨ��");
CString g_sLangID_OptrBindAppBinInfo ; //= _T("sOptrBindAppBinInfo");
CString g_sLangTxt_OptrBindAppBinInfo ; //= _T("������˫����ѡ�еĿ��ƿ�ͨ���������ǿ��룬�ٴ�˫����ȥ��;��delete��ɾ��ѡ�еİ�");


CString g_sLangID_Channel2;               // = _T("sChannel2");  2024-7-26 wuinyi
CString g_sLangTxt_Channel2 ;             // =_T("ͨ��");


CString g_sLangID_Iec_Relay;		//= _T("Iec_Relay");
CString g_sLangTxt_Iec_Relay;		//= _T("����");
CString g_sLangID_Iec_Measure;		//= _T("Iec_Measure");
CString g_sLangTxt_Iec_Measure;		//= _T("����");
CString g_sLangID_Iec_Current;		//= _T("Iec_Current");
CString g_sLangTxt_Iec_Current;		//= _T("����");
CString g_sLangID_Iec_Voltage;		//= _T("Iec_Voltage");
CString g_sLangTxt_Iec_Voltage;		//= _T("��ѹ");
CString g_sLangID_Iec_Gnd;			// = _T("Iec_Gnd");
CString g_sLangTxt_Iec_Gnd;			// = _T("��");
CString g_sLangID_Iec_ZeroSeq;		// = _T("Iec_ZeroSeq");
CString g_sLangTxt_Iec_ZeroSeq;		// = _T("����");
CString g_sLangID_Iec_RatedDelay;	// = _T("Iec_RatedDelay");
CString g_sLangTxt_Iec_RatedDelay;	// = _T("���ʱ");

							   
							  