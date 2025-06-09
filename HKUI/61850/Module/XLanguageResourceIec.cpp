//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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
	CXLanguageResourceBase::InitLangRsByFile(); //2016.10.13 
	InitLangRsByFileEx(&m_oXLangRsIecBase, g_strXLangRsIecBaseFile);  //2016.10.13 
}


void CXLanguageResourceIecBase::RegisterLanguageResource()
{
	CXLanguageResourceBase::RegisterLanguageResource();
	/*rs_AddString(g_sLangID_Home, &g_sLangTxt_Home);*/
	rs_AddString(g_sLid_SICDGSerial, &g_sLtxt_SICDGSerial);    //以下为表格输出内容 20161014
	rs_AddString(g_sLid_SICDSelect, &g_sLtxt_SICDSelect);    //以下为表格输出内容 20161014
	rs_AddString(g_sLid_SICDIED, &g_sLtxt_SICDIED);    //以下为表格输出内容 20161014
	rs_AddString(g_sLid_SICDAP, &g_sLtxt_SICDAP);    //以下为表格输出内容 20161014
	rs_AddString(g_sLid_SICDChaNO, &g_sLtxt_SICDChaNO);    //以下为表格输出内容 20161014
	rs_AddString(g_sLid_SICDTotCha, &g_sLtxt_SICDTotCha);    //以下为表格输出内容 20161014
	rs_AddString(g_sLid_SICDDataSet, &g_sLtxt_SICDDataSet);    //以下为表格输出内容 20161014
	rs_AddString(g_sLid_SICDDataSetDes, &g_sLtxt_SICDDataSetDes);    //以下为表格输出内容 20161014
	rs_AddString(g_sLid_SICDRefChaNO, &g_sLtxt_SICDRefChaNO);    //以下为表格输出内容 20161014
	rs_AddString(g_sLid_SICDDesMAC, &g_sLtxt_SICDDesMAC);    //以下为表格输出内容 20161014
	rs_AddString(g_sLid_SourceMAC, &g_sLtxt_SourceMAC);    //以下为表格输出内容 20161014
	rs_AddString(g_sLid_OutputSel, &g_sLtxt_OutputSel);    //以下为表格输出内容 20161014
	rs_AddString(g_sLid_VersionNumber, &g_sLtxt_VersionNumber);    //以下为表格输出内容 20161014
	rs_AddString(g_sLid_SampleDelay, &g_sLtxt_SampleDelay);    //以下为表格输出内容 20161014
	rs_AddString(g_sLid_SynMode, &g_sLtxt_SynMode);    //以下为表格输出内容 20161014

	rs_AddString(g_sLid_Description, &g_sLtxt_Description);    //以下为表格输出内容 20161014
	rs_AddString(g_sLid_TestMark, &g_sLtxt_TestMark);    //以下为表格输出内容 20161014
	rs_AddString(g_sLid_ShortTransTime, &g_sLtxt_ShortTransTime);    //以下为表格输出内容 20161014
	rs_AddString(g_sLid_StaRetransT, &g_sLtxt_StaRetransT);    //以下为表格输出内容 20161014
	rs_AddString(g_sLid_Interval, &g_sLtxt_Interval);    //以下为表格输出内容 20161014
	rs_AddString(g_sLid_TimeQualty, &g_sLtxt_TimeQualty);    //以下为表格输出内容 20161014
	rs_AddString(g_sLid_TimeAllowToLive, &g_sLtxt_TimeAllowToLive);    //以下为表格输出内容 20161014
	rs_AddString(g_sLid_InputSel, &g_sLtxt_InputSel);    //以下为表格输出内容 20161014
	rs_AddString(g_sLid_AnaGoCBGooseIDAppID, &g_sLtxt_AnaGoCBGooseIDAppID);    //以下为表格输出内容 20161014

	rs_AddString(g_sLid_SMVChannel, &g_sLtxt_SMVChannel);    //以下为表格输出内容 20161015
	rs_AddString(g_sLid_ChannelType, &g_sLtxt_ChannelType);    //以下为表格输出内容 20161015
	rs_AddString(g_sLid_TestDeviceChannel, &g_sLtxt_TestDeviceChannel);    //以下为表格输出内容 20161015
	rs_AddString(g_sLid_Quality, &g_sLtxt_Quality);    //以下为表格输出内容 20161015
	rs_AddString(g_sLid_InputName, &g_sLtxt_InputName);    //以下为表格输出内容 20161015
	rs_AddString(g_sLid_InputPath, &g_sLtxt_InputPath);    //以下为表格输出内容 20161015

	rs_AddString(g_sLid_InitialValue, &g_sLtxt_InitialValue);    //以下为表格输出内容 20161015
	rs_AddString(g_sLid_InputMap, &g_sLtxt_InputMap);    //以下为表格输出内容 20161015

	rs_AddString(g_sLid_LNDescrip, &g_sLtxt_LNDescrip);    //以下为表格输出内容 20161015
	rs_AddString(g_sLid_DOIDescrip, &g_sLtxt_DOIDescrip);    //以下为表格输出内容 20161015
	rs_AddString(g_sLid_DAIDescrip, &g_sLtxt_DAIDescrip);    //以下为表格输出内容 20161015
	rs_AddString(g_sLid_Address, &g_sLtxt_Address);    //以下为表格输出内容 20161015

	rs_AddString(g_sLid_Map, &g_sLtxt_Map);    //以下为表格输出内容 20161015
	rs_AddString(g_sLid_InterLNDes, &g_sLtxt_InterLNDes);    //以下为表格输出内容 20161015
	rs_AddString(g_sLid_ExterLNDes, &g_sLtxt_ExterLNDes);    //以下为表格输出内容 20161015
	rs_AddString(g_sLid_InterDODes, &g_sLtxt_InterDODes);    //以下为表格输出内容 20161015
	rs_AddString(g_sLid_ExterDODes, &g_sLtxt_ExterDODes);    //以下为表格输出内容 20161015
	rs_AddString(g_sLid_InterDUDes, &g_sLtxt_InterDUDes);    //以下为表格输出内容 20161015
	rs_AddString(g_sLid_ExterDUDes, &g_sLtxt_ExterDUDes);    //以下为表格输出内容 20161015
	rs_AddString(g_sLid_InterNO, &g_sLtxt_InterNO);    //以下为表格输出内容 20161015
	rs_AddString(g_sLid_ExterNO, &g_sLtxt_ExterNO);    //以下为表格输出内容 20161015
	rs_AddString(g_sLid_InterPath, &g_sLtxt_InterPath);    //以下为表格输出内容 20161015
	rs_AddString(g_sLid_ExterPath, &g_sLtxt_ExterPath);    //以下为表格输出内容 20161015

	rs_AddString(g_sLid_DUDes, &g_sLtxt_DUDes);    //以下为表格输出内容 20161015  
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

	g_sLid_SICDGSerial                = _T("sSICDGSerial"); // 以下为文本框内容 20161014
	g_sLtxt_SICDGSerial               = _T("序号");      //以下为文本框内容 20161014
	g_sLid_SICDSelect                = _T("sSICDSelect"); // 以下为文本框内容 20161014
	g_sLtxt_SICDSelect               = _T("选择");      //以下为文本框内容 20161014
	g_sLid_SICDIED               = _T("sSICDIED"); // 以下为文本框内容 20161014
	g_sLtxt_SICDIED               = _T("控制块所在IED");      //以下为文本框内容 20161014
	g_sLid_SICDAP               = _T("sSICDAP"); // 以下为文本框内容 20161014
	g_sLtxt_SICDAP               = _T("控制块所在AP");      //以下为文本框内容 20161014
	g_sLid_SICDChaNO               = _T("sSICDChaNO"); // 以下为文本框内容 20161014
	g_sLtxt_SICDChaNO               = _T("通道数");      //以下为文本框内容 20161014
	g_sLid_SICDTotCha               = _T("sSICDTotCha"); // 以下为文本框内容 20161014
	g_sLtxt_SICDTotCha               = _T("总通道数");      //以下为文本框内容 20161014
	g_sLid_SICDDataSet               = _T("sDataSetDesc"); // 以下为文本框内容 20161014
	g_sLtxt_SICDDataSet             = _T("控制块所在数据集描述");      //以下为文本框内容 20161014
	g_sLid_SICDDataSetDes               = _T("sDataSetDes"); // 以下为文本框内容 20161014
	g_sLtxt_SICDDataSetDes             = _T("数据集描述");      //以下为文本框内容 20161014
	g_sLid_SICDRefChaNO               = _T("sSICDRefChaNO"); // 以下为文本框内容 20161014
	g_sLtxt_SICDRefChaNO             = _T("引用通道数");      //以下为文本框内容 20161014
	g_sLid_SICDDesMAC               = _T("sDesMAC"); // 以下为文本框内容 20161014
	g_sLtxt_SICDDesMAC             = _T("目标MAC");      //以下为文本框内容 20161014
	g_sLid_SourceMAC               = _T("sSourceMAC"); // 以下为文本框内容 20161014
	g_sLtxt_SourceMAC             = _T("源MAC");      //以下为文本框内容 20161014
	g_sLid_OutputSel               = _T("sOutputSel"); // 以下为文本框内容 20161014
	g_sLtxt_OutputSel            = _T("输出口选择");      //以下为文本框内容 20161014
	g_sLid_VersionNumber               = _T("sVersionNumber"); // 以下为文本框内容 20161014
	g_sLtxt_VersionNumber             = _T("版本号");      //以下为文本框内容 20161014
	g_sLid_SampleDelay               = _T("sSampleDelay"); // 以下为文本框内容 20161014
	g_sLtxt_SampleDelay             = _T("采样延时");      //以下为文本框内容 20161014
	g_sLid_SynMode               = _T("sSynMode"); // 以下为文本框内容 20161014
	g_sLtxt_SynMode            = _T("同步方式");      //以下为文本框内容 20161014

	g_sLid_Description               = _T("sDescription"); // 以下为文本框内容 20161014
	g_sLtxt_Description            = _T("描述");      //以下为文本框内容 20161014
	g_sLid_TestMark               = _T("sTestMark"); // 以下为文本框内容 20161014
	g_sLtxt_TestMark           = _T("测试标记");      //以下为文本框内容 20161014
	g_sLid_ShortTransTime               = _T("sShortTransTime"); // 以下为文本框内容 20161014
	g_sLtxt_ShortTransTime           = _T("最短传输时间(ms)");      //以下为文本框内容 20161014
	g_sLid_StaRetransT              = _T("sStaRetransT"); // 以下为文本框内容 20161014
	g_sLtxt_StaRetransT            = _T("稳定条件下重传时间(ms)");      //以下为文本框内容 20161014
	g_sLid_Interval               = _T("sInterval"); // 以下为文本框内容 20161014
	g_sLtxt_Interval            = _T("组间延时(ms)");      //以下为文本框内容 20161014
	g_sLid_TimeQualty               = _T("sTimeQualty"); // 以下为文本框内容 20161014
	g_sLtxt_TimeQualty            = _T("时间品质");      //以下为文本框内容 20161014
	g_sLid_TimeAllowToLive               = _T("sTimeAllowToLive"); // 以下为文本框内容 20161014
	g_sLtxt_TimeAllowToLive           = _T("允许生存时间(ms)");      //以下为文本框内容 20161014

	g_sLid_InputSel           = _T("sInputSel"); // 以下为文本框内容 20161014
	g_sLtxt_InputSel           = _T("输入口选择");      //以下为文本框内容 20161014
	g_sLid_AnaGoCBGooseIDAppID           = _T("sAnaGoCBGooseIDAppID"); // 以下为文本框内容 20161014
	g_sLtxt_AnaGoCBGooseIDAppID           = _T("是否解析GoCB,GooseID");      //以下为文本框内容 20161014

	g_sLid_SMVChannel               = _T("sSMVChannel"); // 以下为文本框内容 20161014
	g_sLtxt_SMVChannel           = _T("SMV通道");      //以下为文本框内容 20161014
	g_sLid_ChannelType              = _T("sChannelType"); // 以下为文本框内容 20161014
	g_sLtxt_ChannelType          = _T("通道类型");      //以下为文本框内容 20161014
	g_sLid_TestDeviceChannel               = _T("sTestDeviceChannel"); // 以下为文本框内容 20161014
	g_sLtxt_TestDeviceChannel          = _T("测试仪通道");      //以下为文本框内容 20161014
	g_sLid_Quality               = _T("sQuality"); // 以下为文本框内容 20161014
	g_sLtxt_Quality          = _T("品质");      //以下为文本框内容 20161014
	g_sLid_InputName               = _T("sInputName"); // 以下为文本框内容 20161014
	g_sLtxt_InputName          = _T("输入端-名称");      //以下为文本框内容 20161014
	g_sLid_InputPath               = _T("sInputPath"); // 以下为文本框内容 20161014
	g_sLtxt_InputPath           = _T("输入端-路径");      //以下为文本框内容 20161014

	g_sLid_InitialValue               = _T("sInitialValue"); // 以下为文本框内容 20161015
	g_sLtxt_InitialValue          = _T("初始值");      //以下为文本框内容 20161015
	g_sLid_InputMap               = _T("sInputMap"); // 以下为文本框内容 20161015
	g_sLtxt_InputMap         = _T("开入量映射");      //以下为文本框内容 20161015

	g_sLid_LNDescrip               = _T("sLNDescrip"); // 以下为文本框内容 20161015
	g_sLtxt_LNDescrip        = _T("LN描述");      //以下为文本框内容 20161015
	g_sLid_DOIDescrip               = _T("sDOIDescrip"); // 以下为文本框内容 20161015
	g_sLtxt_DOIDescrip         = _T("DOI描述");      //以下为文本框内容 20161015
	g_sLid_DAIDescrip               = _T("sDAIDescrip"); // 以下为文本框内容 20161015
	g_sLtxt_DAIDescrip         = _T("DAI描述");      //以下为文本框内容 20161015
	g_sLid_Address               = _T("sAddress"); // 以下为文本框内容 20161015
	g_sLtxt_Address         = _T("地址");      //以下为文本框内容 20161015


	g_sLid_Map               = _T("sMap"); // 以下为文本框内容 20161015
	g_sLtxt_Map         = _T("映射");      //以下为文本框内容 20161015
	g_sLid_InterLNDes               = _T("sInterLNDes"); // 以下为文本框内容 20161015
	g_sLtxt_InterLNDes         = _T("内部LN描述");      //以下为文本框内容 20161015
	g_sLid_ExterLNDes               = _T("sExterLNDes"); // 以下为文本框内容 20161015
	g_sLtxt_ExterLNDes         = _T("外部LN描述");      //以下为文本框内容 20161015
	g_sLid_InterDODes               = _T("sInterDODes"); // 以下为文本框内容 20161015
	g_sLtxt_InterDODes         = _T("内部DO描述");      //以下为文本框内容 20161015
	g_sLid_ExterDODes               = _T("sExterDODes"); // 以下为文本框内容 20161015
	g_sLtxt_ExterDODes         = _T("外部DO描述");      //以下为文本框内容 20161015
	g_sLid_InterDUDes               = _T("sInterDUDes"); // 以下为文本框内容 20161015
	g_sLtxt_InterDUDes         = _T("内部DU描述");      //以下为文本框内容 20161015
	g_sLid_ExterDUDes               = _T("sExterDUDes"); // 以下为文本框内容 20161015
	g_sLtxt_ExterDUDes         = _T("外部DU描述");      //以下为文本框内容 20161015
	g_sLid_InterNO               = _T("sInterNO"); // 以下为文本框内容 20161015
	g_sLtxt_InterNO         = _T("内部序号");      //以下为文本框内容 20161015
	g_sLid_ExterNO               = _T("sExterNO"); // 以下为文本框内容 20161015
	g_sLtxt_ExterNO         = _T("外部序号");      //以下为文本框内容 20161015
	g_sLid_InterPath               = _T("sInterPath"); // 以下为文本框内容 20161015
	g_sLtxt_InterPath         = _T("内部路径");      //以下为文本框内容 20161015
	g_sLid_ExterPath               = _T("sExterPath"); // 以下为文本框内容 20161015
	g_sLtxt_ExterPath         = _T("外部路径");      //以下为文本框内容 20161015

	g_sLid_DUDes              = _T("sDUDes"); // 以下为文本框内容 20161015
	g_sLtxt_DUDes         = _T("DU描述");      //以下为文本框内容 20161015  


	g_sLangID_IEC61850Config              = _T("sIEC61850Config"); 
	g_sLangTxt_IEC61850Config             = _T("IEC61850测试仪配置");     

	g_sLangID_TesterIEC61850Config              = _T("sTesterIEC61850Config"); 
	g_sLangTxt_TesterIEC61850Config             = _T("测试仪IEC61850Config");  
	g_sLangID_MsgMonitorWnd              = _T("sMsgMonitorWnd"); 
	g_sLangTxt_MsgMonitorWnd             = _T("报文监视窗口"); 
	g_sLangID_WaveMonitorWnd              = _T("sWaveMonitorWnd"); 
	g_sLangTxt_WaveMonitorWnd             = _T("波形监视窗口");
	g_sLangID_NoneConfigFile              = _T("sNoneConfigFile"); 
	g_sLangTxt_NoneConfigFile            = _T("配置文件【%s】不存在");
	g_sLangID_NoneSclFile             = _T("sNoneSclFile"); 
	g_sLangTxt_NoneSclFile            = _T("没有选择SCL文件");
	g_sLangID_SclFile             = _T("sSclFile"); 
	g_sLangTxt_SclFile            = _T("SCL文件");
	g_sLangID_SclStateTool             = _T("sSclStateTool"); 
	g_sLangTxt_SclStateTool            = _T("SCL状态序列工具");


	g_sLangID_TesterLinkSucc             = _T("sTesterLinkSucc"); 
	g_sLangTxt_TesterLinkSucc            = _T("测试仪联机成功");  
	g_sLangID_LinkFail              = _T("sLinkFail"); 
	g_sLangTxt_LinkFail             = _T("联机失败"); 
	g_sLangID_RecevElectricalTestEndMsg              = _T("sRecevElectricalTestEndMsg"); 
	g_sLangTxt_RecevElectricalTestEndMsg             = _T("收到电气量测试结束消息！");
	g_sLangID_DownloadParaFail              = _T("sDownloadParaFail"); 
	g_sLangTxt_DownloadParaFail           = _T("参数下载失败");
	g_sLangID_TesterInterfNoIed61850ConfigFunc             = _T("sTesterInterfNoIed61850ConfigFunc"); 
	g_sLangTxt_TesterInterfNoIed61850ConfigFunc            = _T("测试仪器底层功能接口不支持下载Iec61850配置测试功能");
	g_sLangID_TesterTestFuncOvertime             = _T("sTesterTestFuncOvertime"); 
	g_sLangTxt_TesterTestFuncOvertime            = _T("测试仪器底层测试功能测试超时");

	g_sLangID_Channel                = _T("sChannel");  
	g_sLangTxt_Channel               =_T("通道%d");
	g_sLangID_DefaultConfigFileNone                = _T("sDefaultConfigFileNone");  
	g_sLangTxt_DefaultConfigFileNone                  =_T("缺省配置文件【%s】不存在");

	g_sLangID_GooseoutGroup                = _T("sGooseoutGroup");  
	g_sLangTxt_GooseoutGroup                  =_T("GOOSEOUT第%d组");
	g_sLangID_PortConflict                = _T("sPortConflict");  
	g_sLangTxt_PortConflict                  =_T("【%s】与【%s】输出光口冲突");
	g_sLangID_GooseinGroup                = _T("sGooseinGroup");  
	g_sLangTxt_GooseinGroup                  =_T("GOOSEIN第%d组");
	g_sLangID_SameOpening                = _T("sSameOpening");  
	g_sLangTxt_SameOpening                  =_T("【%s$%s】与【%s$%s】使用相同的开入【%s】");

	g_sLangID_Iec61850Config                = _T("sIec61850Config");  
	g_sLangTxt_Iec61850Config                  =_T("IEC61850配置");
	g_sLangID_TesterConfigFile                = _T("sTesterConfigFile");  
	g_sLangTxt_TesterConfigFile                  =_T("测试仪配置文件");
	g_sLangID_ErrFileFormat                = _T("sErrFileFormat");  
	g_sLangTxt_ErrFileFormat                  =_T("文件【%s】格式不正确、版本不兼容，是使用PowerTest配置的文件");
	g_sLangID_DiffSvmConfig               = _T("sDiffSvmConfig");  
	g_sLangTxt_DiffSvmConfig                  =_T("添加的SMV配置对象与当前的配置不一致");
	g_sLangID_NoMatchData                = _T("sNoMatchData");  
	g_sLangTxt_NoMatchData                  =_T("数据覆盖失败，配置数据种类不匹配");
	g_sLangID_NoSelData                = _T("sNoSelData");  
	g_sLangTxt_NoSelData                 =_T("数据覆盖失败，配置数据种类没有选中");
	g_sLangID_NoExisDataIndex                = _T("sNoExisDataIndex");  
	g_sLangTxt_NoExisDataIndex                  =_T("数据覆盖失败，配置数据索引%d不存在");

	g_sLangID_AppBin  = _T("sAppBin");
	g_sLangTxt_AppBin  = _T("测试仪开入");
	g_sLangID_BindMac  = _T("sBindMa");
	g_sLangTxt_BindMac  = _T("绑定控制块MAC");
	g_sLangID_BindAppID = _T("sBindAppID");
	g_sLangTxt_BindAppID = _T("绑定控制块APPID");
	g_sLangID_BindChannel = _T("sBindChannel");
	g_sLangTxt_BindChannel = _T("绑定通道");
	g_sLangID_OptrBindAppBinInfo = _T("sOptrBindAppBinInfo");
	g_sLangTxt_OptrBindAppBinInfo = _T("鼠标左键双击绑定选中的控制块通道到测试仪开入，再次双击移去绑定;按delete键删除选中的绑定");

    g_sLangID_Channel2 = _T("sChannel2");
    g_sLangTxt_Channel2 =_T("通道");

	g_sLangID_Iec_Relay = _T("Iec_Relay");
	g_sLangTxt_Iec_Relay = _T("保护");
	g_sLangID_Iec_Measure = _T("Iec_Measure");
	g_sLangTxt_Iec_Measure = _T("测量");
	g_sLangID_Iec_Current = _T("Iec_Current");
	g_sLangTxt_Iec_Current = _T("电流");
	g_sLangID_Iec_Voltage = _T("Iec_Voltage");
	g_sLangTxt_Iec_Voltage = _T("电压");
	g_sLangID_Iec_Gnd = _T("Iec_Gnd");
	g_sLangTxt_Iec_Gnd = _T("相");
	g_sLangID_Iec_ZeroSeq = _T("Iec_ZeroSeq");
	g_sLangTxt_Iec_ZeroSeq = _T("零序");
	g_sLangID_Iec_RatedDelay = _T("Iec_RatedDelay");
	g_sLangTxt_Iec_RatedDelay = _T("额定延时");


}

//CString g_sLangID_Home                 = _T("sHome");
//CString g_sLangTxt_Home                = _T("主页(H)");

CString g_sLid_SICDGSerial                ; //= _T("sSICDGSerial"); // 以下为文本框内容 20161014
CString g_sLtxt_SICDGSerial               ; //= _T("序号");      //以下为文本框内容 20161014
CString g_sLid_SICDSelect                ; //= _T("sSICDSelect"); // 以下为文本框内容 20161014
CString g_sLtxt_SICDSelect               ; //= _T("选择");      //以下为文本框内容 20161014
CString g_sLid_SICDIED               ; //= _T("sSICDIED"); // 以下为文本框内容 20161014
CString g_sLtxt_SICDIED               ; //= _T("控制块所在IED");      //以下为文本框内容 20161014
CString g_sLid_SICDAP               ; //= _T("sSICDAP"); // 以下为文本框内容 20161014
CString g_sLtxt_SICDAP               ; //= _T("控制块所在AP");      //以下为文本框内容 20161014
CString g_sLid_SICDChaNO               ; //= _T("sSICDChaNO"); // 以下为文本框内容 20161014
CString g_sLtxt_SICDChaNO               ; //= _T("通道数");      //以下为文本框内容 20161014
CString g_sLid_SICDTotCha               ; //= _T("sSICDTotCha"); // 以下为文本框内容 20161014
CString g_sLtxt_SICDTotCha               ; //= _T("总通道数");      //以下为文本框内容 20161014
CString g_sLid_SICDDataSet               ; //= _T("sDataSetDesc"); // 以下为文本框内容 20161014
CString g_sLtxt_SICDDataSet             ; //= _T("控制块所在数据集描述");      //以下为文本框内容 20161014
CString g_sLid_SICDDataSetDes               ; //= _T("sDataSetDes"); // 以下为文本框内容 20161014
CString g_sLtxt_SICDDataSetDes             ; //= _T("数据集描述");      //以下为文本框内容 20161014
CString g_sLid_SICDRefChaNO               ; //= _T("sSICDRefChaNO"); // 以下为文本框内容 20161014
CString g_sLtxt_SICDRefChaNO             ; //= _T("引用通道数");      //以下为文本框内容 20161014
CString g_sLid_SICDDesMAC               ; //= _T("sDesMAC"); // 以下为文本框内容 20161014
CString g_sLtxt_SICDDesMAC             ; //= _T("目标MAC");      //以下为文本框内容 20161014
CString g_sLid_SourceMAC               ; //= _T("sSourceMAC"); // 以下为文本框内容 20161014
CString g_sLtxt_SourceMAC             ; //= _T("源MAC");      //以下为文本框内容 20161014
CString g_sLid_OutputSel               ; //= _T("sOutputSel"); // 以下为文本框内容 20161014
CString g_sLtxt_OutputSel            ; //= _T("输出口选择");      //以下为文本框内容 20161014
CString g_sLid_VersionNumber               ; //= _T("sVersionNumber"); // 以下为文本框内容 20161014
CString g_sLtxt_VersionNumber             ; //= _T("版本号");      //以下为文本框内容 20161014
CString g_sLid_SampleDelay               ; //= _T("sSampleDelay"); // 以下为文本框内容 20161014
CString g_sLtxt_SampleDelay             ; //= _T("采样延时");      //以下为文本框内容 20161014
CString g_sLid_SynMode               ; //= _T("sSynMode"); // 以下为文本框内容 20161014
CString g_sLtxt_SynMode            ; //= _T("同步方式");      //以下为文本框内容 20161014

CString g_sLid_Description               ; //= _T("sDescription"); // 以下为文本框内容 20161014
CString g_sLtxt_Description            ; //= _T("描述");      //以下为文本框内容 20161014
CString g_sLid_TestMark               ; //= _T("sTestMark"); // 以下为文本框内容 20161014
CString g_sLtxt_TestMark           ; //= _T("测试标记");      //以下为文本框内容 20161014
CString g_sLid_ShortTransTime               ; //= _T("sShortTransTime"); // 以下为文本框内容 20161014
CString g_sLtxt_ShortTransTime           ; //= _T("最短传输时间(ms)");      //以下为文本框内容 20161014
CString g_sLid_StaRetransT              ; //= _T("sStaRetransT"); // 以下为文本框内容 20161014
CString g_sLtxt_StaRetransT            ; //= _T("稳定条件下重传时间(ms)");      //以下为文本框内容 20161014
CString g_sLid_Interval               ; //= _T("sInterval"); // 以下为文本框内容 20161014
CString g_sLtxt_Interval            ; //= _T("组间延时(ms)");      //以下为文本框内容 20161014
CString g_sLid_TimeQualty               ; //= _T("sTimeQualty"); // 以下为文本框内容 20161014
CString g_sLtxt_TimeQualty            ; //= _T("时间品质");      //以下为文本框内容 20161014
CString g_sLid_TimeAllowToLive               ; //= _T("sTimeAllowToLive"); // 以下为文本框内容 20161014
CString g_sLtxt_TimeAllowToLive           ; //= _T("允许生存时间(ms)");      //以下为文本框内容 20161014

CString g_sLid_InputSel           ; //= _T("sInputSel"); // 以下为文本框内容 20161014
CString g_sLtxt_InputSel           ; //= _T("输入口选择");      //以下为文本框内容 20161014
CString g_sLid_AnaGoCBGooseIDAppID           ; //= _T("sAnaGoCBGooseIDAppID"); // 以下为文本框内容 20161014
CString g_sLtxt_AnaGoCBGooseIDAppID           ; //= _T("是否解析GoCB,GooseID");      //以下为文本框内容 20161014

CString g_sLid_SMVChannel               ; //= _T("sSMVChannel"); // 以下为文本框内容 20161014
CString g_sLtxt_SMVChannel           ; //= _T("SMV通道");      //以下为文本框内容 20161014
CString g_sLid_ChannelType              ; //= _T("sChannelType"); // 以下为文本框内容 20161014
CString g_sLtxt_ChannelType          ; //= _T("通道类型");      //以下为文本框内容 20161014
CString g_sLid_TestDeviceChannel               ; //= _T("sTestDeviceChannel"); // 以下为文本框内容 20161014
CString g_sLtxt_TestDeviceChannel          ; //= _T("测试仪通道");      //以下为文本框内容 20161014
CString g_sLid_Quality               ; //= _T("sQuality"); // 以下为文本框内容 20161014
CString g_sLtxt_Quality          ; //= _T("品质");      //以下为文本框内容 20161014
CString g_sLid_InputName               ; //= _T("sInputName"); // 以下为文本框内容 20161014
CString g_sLtxt_InputName          ; //= _T("输入端-名称");      //以下为文本框内容 20161014
CString g_sLid_InputPath               ; //= _T("sInputPath"); // 以下为文本框内容 20161014
CString g_sLtxt_InputPath           ; //= _T("输入端-路径");      //以下为文本框内容 20161014

CString g_sLid_InitialValue               ; //= _T("sInitialValue"); // 以下为文本框内容 20161015
CString g_sLtxt_InitialValue          ; //= _T("初始值");      //以下为文本框内容 20161015
CString g_sLid_InputMap               ; //= _T("sInputMap"); // 以下为文本框内容 20161015
CString g_sLtxt_InputMap         ; //= _T("开入量映射");      //以下为文本框内容 20161015

CString g_sLid_LNDescrip               ; //= _T("sLNDescrip"); // 以下为文本框内容 20161015
CString g_sLtxt_LNDescrip        ; //= _T("LN描述");      //以下为文本框内容 20161015
CString g_sLid_DOIDescrip               ; //= _T("sDOIDescrip"); // 以下为文本框内容 20161015
CString g_sLtxt_DOIDescrip         ; //= _T("DOI描述");      //以下为文本框内容 20161015
CString g_sLid_DAIDescrip               ; //= _T("sDAIDescrip"); // 以下为文本框内容 20161015
CString g_sLtxt_DAIDescrip         ; //= _T("DAI描述");      //以下为文本框内容 20161015
CString g_sLid_Address               ; //= _T("sAddress"); // 以下为文本框内容 20161015
CString g_sLtxt_Address         ; //= _T("地址");      //以下为文本框内容 20161015


CString g_sLid_Map               ; //= _T("sMap"); // 以下为文本框内容 20161015
CString g_sLtxt_Map         ; //= _T("映射");      //以下为文本框内容 20161015
CString g_sLid_InterLNDes               ; //= _T("sInterLNDes"); // 以下为文本框内容 20161015
CString g_sLtxt_InterLNDes         ; //= _T("内部LN描述");      //以下为文本框内容 20161015
CString g_sLid_ExterLNDes               ; //= _T("sExterLNDes"); // 以下为文本框内容 20161015
CString g_sLtxt_ExterLNDes         ; //= _T("外部LN描述");      //以下为文本框内容 20161015
CString g_sLid_InterDODes               ; //= _T("sInterDODes"); // 以下为文本框内容 20161015
CString g_sLtxt_InterDODes         ; //= _T("内部DO描述");      //以下为文本框内容 20161015
CString g_sLid_ExterDODes               ; //= _T("sExterDODes"); // 以下为文本框内容 20161015
CString g_sLtxt_ExterDODes         ; //= _T("外部DO描述");      //以下为文本框内容 20161015
CString g_sLid_InterDUDes               ; //= _T("sInterDUDes"); // 以下为文本框内容 20161015
CString g_sLtxt_InterDUDes         ; //= _T("内部DU描述");      //以下为文本框内容 20161015
CString g_sLid_ExterDUDes               ; //= _T("sExterDUDes"); // 以下为文本框内容 20161015
CString g_sLtxt_ExterDUDes         ; //= _T("外部DU描述");      //以下为文本框内容 20161015
CString g_sLid_InterNO               ; //= _T("sInterNO"); // 以下为文本框内容 20161015
CString g_sLtxt_InterNO         ; //= _T("内部序号");      //以下为文本框内容 20161015
CString g_sLid_ExterNO               ; //= _T("sExterNO"); // 以下为文本框内容 20161015
CString g_sLtxt_ExterNO         ; //= _T("外部序号");      //以下为文本框内容 20161015
CString g_sLid_InterPath               ; //= _T("sInterPath"); // 以下为文本框内容 20161015
CString g_sLtxt_InterPath         ; //= _T("内部路径");      //以下为文本框内容 20161015
CString g_sLid_ExterPath               ; //= _T("sExterPath"); // 以下为文本框内容 20161015
CString g_sLtxt_ExterPath         ; //= _T("外部路径");      //以下为文本框内容 20161015

CString g_sLid_DUDes              ; //= _T("sDUDes"); // 以下为文本框内容 20161015
CString g_sLtxt_DUDes         ; //= _T("DU描述");      //以下为文本框内容 20161015  


CString g_sLangID_IEC61850Config              ; //= _T("sIEC61850Config"); 
CString g_sLangTxt_IEC61850Config             ; //= _T("IEC61850测试仪配置");     

CString g_sLangID_TesterIEC61850Config              ; //= _T("sTesterIEC61850Config"); 
CString g_sLangTxt_TesterIEC61850Config             ; //= _T("测试仪IEC61850Config");  
CString g_sLangID_MsgMonitorWnd              ; //= _T("sMsgMonitorWnd"); 
CString g_sLangTxt_MsgMonitorWnd             ; //= _T("报文监视窗口"); 
CString g_sLangID_WaveMonitorWnd              ; //= _T("sWaveMonitorWnd"); 
CString g_sLangTxt_WaveMonitorWnd             ; //= _T("波形监视窗口");
CString g_sLangID_NoneConfigFile              ; //= _T("sNoneConfigFile"); 
CString g_sLangTxt_NoneConfigFile            ; //= _T("配置文件【%s】不存在");
CString g_sLangID_NoneSclFile             ; //= _T("sNoneSclFile"); 
CString g_sLangTxt_NoneSclFile            ; //= _T("没有选择SCL文件");
CString g_sLangID_SclFile             ; //= _T("sSclFile"); 
CString g_sLangTxt_SclFile            ; //= _T("SCL文件");
CString g_sLangID_SclStateTool             ; //= _T("sSclStateTool"); 
CString g_sLangTxt_SclStateTool            ; //= _T("SCL状态序列工具");


CString g_sLangID_TesterLinkSucc             ; //= _T("sTesterLinkSucc"); 
CString g_sLangTxt_TesterLinkSucc            ; //= _T("测试仪联机成功");  
CString g_sLangID_LinkFail              ; //= _T("sLinkFail"); 
CString g_sLangTxt_LinkFail             ; //= _T("联机失败"); 
CString g_sLangID_RecevElectricalTestEndMsg              ; //= _T("sRecevElectricalTestEndMsg"); 
CString g_sLangTxt_RecevElectricalTestEndMsg             ; //= _T("收到电气量测试结束消息！");
CString g_sLangID_DownloadParaFail              ; //= _T("sDownloadParaFail"); 
CString g_sLangTxt_DownloadParaFail           ; //= _T("参数下载失败");
CString g_sLangID_TesterInterfNoIed61850ConfigFunc             ; //= _T("sTesterInterfNoIed61850ConfigFunc"); 
CString g_sLangTxt_TesterInterfNoIed61850ConfigFunc            ; //= _T("测试仪器底层功能接口不支持下载Iec61850配置测试功能");
CString g_sLangID_TesterTestFuncOvertime             ; //= _T("sTesterTestFuncOvertime"); 
CString g_sLangTxt_TesterTestFuncOvertime            ; //= _T("测试仪器底层测试功能测试超时");

CString g_sLangID_Channel                ; //= _T("sChannel");  
CString g_sLangTxt_Channel               ; //=_T("通道%d");
CString g_sLangID_DefaultConfigFileNone                ; //= _T("sDefaultConfigFileNone");  
CString g_sLangTxt_DefaultConfigFileNone                  ; //=_T("缺省配置文件【%s】不存在");

CString g_sLangID_GooseoutGroup                ; //= _T("sGooseoutGroup");  
CString g_sLangTxt_GooseoutGroup                  ; //=_T("GOOSEOUT第%d组");
CString g_sLangID_PortConflict                ; //= _T("sPortConflict");  
CString g_sLangTxt_PortConflict                  ; //=_T("【%s】与【%s】输出光口冲突");
CString g_sLangID_GooseinGroup                ; //= _T("sGooseinGroup");  
CString g_sLangTxt_GooseinGroup                  ; //=_T("GOOSEIN第%d组");
CString g_sLangID_SameOpening                ; //= _T("sSameOpening");  
CString g_sLangTxt_SameOpening                  ; //=_T("【%s$%s】与【%s$%s】使用相同的开入【%s】");

CString g_sLangID_Iec61850Config                ; //= _T("sIec61850Config");  
CString g_sLangTxt_Iec61850Config                  ; //=_T("IEC61850配置");
CString g_sLangID_TesterConfigFile                ; //= _T("sTesterConfigFile");  
CString g_sLangTxt_TesterConfigFile                  ; //=_T("测试仪配置文件");
CString g_sLangID_ErrFileFormat                ; //= _T("sErrFileFormat");  
CString g_sLangTxt_ErrFileFormat                  ; //=_T("文件【%s】格式不正确、版本不兼容，是使用PowerTest配置的文件");
CString g_sLangID_DiffSvmConfig               ; //= _T("sDiffSvmConfig");  
CString g_sLangTxt_DiffSvmConfig                  ; //=_T("添加的SMV配置对象与当前的配置不一致");
CString g_sLangID_NoMatchData                ; //= _T("sNoMatchData");  
CString g_sLangTxt_NoMatchData                  ; //=_T("数据覆盖失败，配置数据种类不匹配");
CString g_sLangID_NoSelData                ; //= _T("sNoSelData");  
CString g_sLangTxt_NoSelData                 ; //=_T("数据覆盖失败，配置数据种类没有选中");
CString g_sLangID_NoExisDataIndex                ; //= _T("sNoExisDataIndex");  
CString g_sLangTxt_NoExisDataIndex                  ; //=_T("数据覆盖失败，配置数据索引%d不存在");

CString g_sLangID_AppBin  ; //= _T("sAppBin");
CString g_sLangTxt_AppBin  ; //= _T("测试仪开入");
CString g_sLangID_BindMac  ; //= _T("sBindMa");
CString g_sLangTxt_BindMac  ; //= _T("绑定控制块MAC");
CString g_sLangID_BindAppID ; //= _T("sBindAppID");
CString g_sLangTxt_BindAppID ; //= _T("绑定控制块APPID");
CString g_sLangID_BindChannel ; //= _T("sBindChannel");
CString g_sLangTxt_BindChannel ; //= _T("绑定通道");
CString g_sLangID_OptrBindAppBinInfo ; //= _T("sOptrBindAppBinInfo");
CString g_sLangTxt_OptrBindAppBinInfo ; //= _T("鼠标左键双击绑定选中的控制块通道到测试仪开入，再次双击移去绑定;按delete键删除选中的绑定");


CString g_sLangID_Channel2;               // = _T("sChannel2");  2024-7-26 wuinyi
CString g_sLangTxt_Channel2 ;             // =_T("通道");


CString g_sLangID_Iec_Relay;		//= _T("Iec_Relay");
CString g_sLangTxt_Iec_Relay;		//= _T("保护");
CString g_sLangID_Iec_Measure;		//= _T("Iec_Measure");
CString g_sLangTxt_Iec_Measure;		//= _T("测量");
CString g_sLangID_Iec_Current;		//= _T("Iec_Current");
CString g_sLangTxt_Iec_Current;		//= _T("电流");
CString g_sLangID_Iec_Voltage;		//= _T("Iec_Voltage");
CString g_sLangTxt_Iec_Voltage;		//= _T("电压");
CString g_sLangID_Iec_Gnd;			// = _T("Iec_Gnd");
CString g_sLangTxt_Iec_Gnd;			// = _T("相");
CString g_sLangID_Iec_ZeroSeq;		// = _T("Iec_ZeroSeq");
CString g_sLangTxt_Iec_ZeroSeq;		// = _T("零序");
CString g_sLangID_Iec_RatedDelay;	// = _T("Iec_RatedDelay");
CString g_sLangTxt_Iec_RatedDelay;	// = _T("额定延时");

							   
							  