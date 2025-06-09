//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XLanguageResourceBase.cpp  CXLanguageResourceAtsBase


#include "stdafx.h"
#include "XLanguageResourcePp_PpEngine.h"
#include "../../Module/API/GlobalConfigApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CString  g_strXLangRsPp_PpEngineFile = _T("PpEngine");

CXLanguageResourcePp_PpEngine::CXLanguageResourcePp_PpEngine()
{
	m_pXLangRsExe = &m_oXLangRsPp_PpEngine;
	m_oXLangRsPp_PpEngine.m_strName = g_strXLangRsPp_PpEngineFile;
	m_oXLangRsPp_PpEngine.m_strID = g_strXLangRsPp_PpEngineFile;
}


CXLanguageResourcePp_PpEngine::~CXLanguageResourcePp_PpEngine()
{
	m_oXLangRsPp_PpEngine.RemoveAll();
}

void CXLanguageResourcePp_PpEngine::InitLangFileForDebug(const CString &strModule)
{
	m_strXLangFile = _P_GetLanguagePath();
    m_strXLangFile.AppendFormat(_T("%s.xml"), strModule.GetString());
}

CXLangItem* CXLanguageResourcePp_PpEngine::rs_AddString(const CString &strID, CString *pstrString)
{
	CXLangItem *p = CXLanguage::AddString(strID, pstrString);

	m_oXLangRsPp_PpEngine.AddTail(p);

	return p;
}

void CXLanguageResourcePp_PpEngine::InitLangRsByFile()
{
	CXLanguageResourcePpBase::InitLangRsByFile();

	InitLangRsByFileEx(&m_oXLangRsPp_PpEngine, g_strXLangRsPp_PpEngineFile);
}

void CXLanguageResourcePp_PpEngine::RegisterLanguageResource()
{
	CXLanguageResourcePpBase::RegisterLanguageResource();

	rs_AddString(g_sLangID_NotSelDev, &g_sLangTxt_NotSelDev);
	rs_AddString(g_sLangID_PrtcProHome, &g_sLangTxt_PrtcProHome);
	rs_AddString(g_sLangID_DevOpera, &g_sLangTxt_DevOpera);
	rs_AddString(g_sLangID_NewAdd, &g_sLangTxt_NewAdd);
	rs_AddString(g_sLangID_Connection, &g_sLangTxt_Connection);
	rs_AddString(g_sLangID_DisConnection, &g_sLangTxt_DisConnection);
	rs_AddString(g_sLangID_Uninstall, &g_sLangTxt_Uninstall);
	rs_AddString(g_sLangID_PointTableEdit, &g_sLangTxt_PointTableEdit);
	rs_AddString(g_sLangID_CommuntSet, &g_sLangTxt_CommuntSet);
	rs_AddString(g_sLangID_CommunProcess, &g_sLangTxt_CommunProcess);
	rs_AddString(g_sLangID_OperationProcess, &g_sLangTxt_OperationProcess);
	rs_AddString(g_sLangID_ViewOprthPrcs, &g_sLangTxt_ViewOprthPrcs);
	rs_AddString(g_sLangID_StopProcess, &g_sLangTxt_StopProcess);
	rs_AddString(g_sLangID_ClearSOE, &g_sLangTxt_ClearSOE);
	rs_AddString(g_sLangID_ClearMessage, &g_sLangTxt_ClearMessage);
	rs_AddString(g_sLangID_DebugMode, &g_sLangTxt_DebugMode);
	rs_AddString(g_sLangID_Report, &g_sLangTxt_Report);
	rs_AddString(g_sLangID_StartReport, &g_sLangTxt_StartReport);
	rs_AddString(g_sLangID_StopReport, &g_sLangTxt_StopReport);
	rs_AddString(g_sLangID_DevToolBar, &g_sLangTxt_DevToolBar);
	rs_AddString(g_sLangID_DevToolBarTip, &g_sLangTxt_DevToolBarTip);
	rs_AddString(g_sLangID_OutputWndTip, &g_sLangTxt_OutputWndTip);
	rs_AddString(g_sLangID_MonitorBindError, &g_sLangTxt_MonitorBindError);
	rs_AddString(g_sLangID_MonitorMessageInf, &g_sLangTxt_MonitorMessageInf);
	rs_AddString(g_sLangID_MonitorMessage, &g_sLangTxt_MonitorMessage);

	rs_AddString(g_sLangID_ClipboardData, &g_sLangTxt_ClipboardData);
// 	rs_AddString(g_sLangID_DataList, &g_sLangTxt_DataList);
	rs_AddString(g_sLangID_ReadClipboard, &g_sLangTxt_ReadClipboard);
	rs_AddString(g_sLangID_AddToList, &g_sLangTxt_AddToList);
	rs_AddString(g_sLangID_InsertList, &g_sLangTxt_InsertList);
	rs_AddString(g_sLangID_ClearList, &g_sLangTxt_ClearList);
	rs_AddString(g_sLangID_InsertIndex, &g_sLangTxt_InsertIndex);
	rs_AddString(g_sLangID_PointDataPaste, &g_sLangTxt_PointDataPaste);
	rs_AddString(g_sLangID_NewDev, &g_sLangTxt_NewDev);
	rs_AddString(g_sLangID_PointListFile, &g_sLangTxt_PointListFile);
	rs_AddString(g_sLangID_ModifyClose, &g_sLangTxt_ModifyClose);

	rs_AddString(g_sLangID_FormulaType, &g_sLangTxt_FormulaType);
	rs_AddString(g_sLangID_FormulaEdit, &g_sLangTxt_FormulaEdit);
	rs_AddString(g_sLangID_SelType, &g_sLangTxt_SelType);

	rs_AddString(g_sLangID_FormulaEditD, &g_sLangTxt_FormulaEditD);

	rs_AddString(g_sLangID_MonitorPrtcMessage, &g_sLangTxt_MonitorPrtcMessage);
	rs_AddString(g_sLangID_MonitorSOE, &g_sLangTxt_MonitorSOE);
	rs_AddString(g_sLangID_Empty, &g_sLangTxt_Empty);
	rs_AddString(g_sLangID_CommunMonitor, &g_sLangTxt_CommunMonitor);
	rs_AddString(g_sLangID_SelCommunProcess, &g_sLangTxt_SelCommunProcess);
	rs_AddString(g_sLangID_SelProcessSet, &g_sLangTxt_SelProcessSet);
	rs_AddString(g_sLangID_Vaule, &g_sLangTxt_Vaule);
	rs_AddString(g_sLangID_PrtcMonitor, &g_sLangTxt_PrtcMonitor);

	rs_AddString(g_sLangID_CannotAddView, &g_sLangTxt_CannotAddView);
	rs_AddString(g_sLangID_NewFolder2, &g_sLangTxt_NewFolder2);
	rs_AddString(g_sLangID_AddMemberFctn, &g_sLangTxt_AddMemberFctn);

	rs_AddString(g_sLangID_RptPathUnExist, &g_sLangTxt_RptPathUnExist);
	rs_AddString(g_sLangID_DataPathUnExist, &g_sLangTxt_DataPathUnExist);
	rs_AddString(g_sLangID_DiffError, &g_sLangTxt_DiffError);
	rs_AddString(g_sLangID_SendTestInf, &g_sLangTxt_SendTestInf);
	rs_AddString(g_sLangID_SendSystemMsg, &g_sLangTxt_SendSystemMsg);
	rs_AddString(g_sLangID_ColctnClcltFmla, &g_sLangTxt_ColctnClcltFmla);
	rs_AddString(g_sLangID_SendClcltFmla, &g_sLangTxt_SendClcltFmla);

    /*  以下几个，移动到基类CXLanguageResourceBase。2024-1-4  shaolei
	rs_AddString(g_sLangID_Voltage, &g_sLangTxt_Voltage);
	rs_AddString(g_sLangID_Current, &g_sLangTxt_Current);
	rs_AddString(g_sLangID_ActivePower, &g_sLangTxt_ActivePower);
	rs_AddString(g_sLangID_ReactivePower, &g_sLangTxt_ReactivePower);
    rs_AddString(g_sLangID_Frequency, &g_sLangTxt_Frequency);
	rs_AddString(g_sLangID_PowerFactor, &g_sLangTxt_PowerFactor);
    */

	rs_AddString(g_sLangID_Menu_32817, &g_sLangTxt_Menu_32817);
	rs_AddString(g_sLangID_Menu_32818, &g_sLangTxt_Menu_32818);
	rs_AddString(g_sLangID_Menu_32819, &g_sLangTxt_Menu_32819);


	rs_AddString(g_sLangID_DeviceDataView, &g_sLangTxt_DeviceDataView);
}

static long g_nCXLanguageResourcePp_PpEngine_InitLangTxt = 0;

void CXLanguageResourcePp_PpEngine::InitLangTxt()
{
	CXLanguageResourcePpBase::InitLangTxt();

    if (g_nCXLanguageResourcePp_PpEngine_InitLangTxt > 0)
    {
        return;
    }

    g_nCXLanguageResourcePp_PpEngine_InitLangTxt = 1;

	g_sLangID_NotSelDev             = _T("sNotSelDev");
	g_sLangTxt_NotSelDev            = _T("没有选择设备");
	g_sLangID_PrtcProHome             = _T("sPrtcProHome");
	g_sLangTxt_PrtcProHome            = _T("规约引擎操作主页");
	g_sLangID_DevOpera             = _T("sDevOpera");
	g_sLangTxt_DevOpera            = _T("设备操作");
	g_sLangID_NewAdd             = _T("sNewAdd");
	g_sLangTxt_NewAdd            = _T("新增");
	g_sLangID_Connection             = _T("sConnection");
	g_sLangTxt_Connection            = _T("连接");
	g_sLangID_DisConnection             = _T("sDisConnection");
	g_sLangTxt_DisConnection            = _T("断开连接");
	g_sLangID_Uninstall             = _T("sUninstall");
	g_sLangTxt_Uninstall            = _T("卸载");
	g_sLangID_PointTableEdit             = _T("sPointTableEdit");
	g_sLangTxt_PointTableEdit            = _T("点表编辑");
	g_sLangID_CommuntSet             = _T("sCommuntSet");
	g_sLangTxt_CommuntSet            = _T("通讯设置");
	g_sLangID_CommunProcess             = _T("sCommunProcess ");
	g_sLangTxt_CommunProcess             = _T("通讯过程");
	g_sLangID_OperationProcess             = _T("sOperationProcess");
	g_sLangTxt_OperationProcess            = _T("运行过程");
	g_sLangID_ViewOprthPrcs             = _T("sViewOprthPrcs");
	g_sLangTxt_ViewOprthPrcs            = _T("查看运行过程");
	g_sLangID_StopProcess             = _T("sStopProcess");
	g_sLangTxt_StopProcess            = _T("终止过程");
	g_sLangID_ClearSOE             = _T("sClearSOE");
	g_sLangTxt_ClearSOE            = _T("清空SOE");
	g_sLangID_ClearMessage             = _T("sClearMessage");
	g_sLangTxt_ClearMessage            = _T("清除报文");
	g_sLangID_DebugMode             = _T("sDebugMode");
	g_sLangTxt_DebugMode            = _T("调试模式");
	g_sLangID_Report             = _T("sReport");
	g_sLangTxt_Report             = _T("报告");
	g_sLangID_StartReport             = _T("sStartReport");
	g_sLangTxt_StartReport            = _T("启动报告");
	g_sLangID_StopReport             = _T("sStopReport");
	g_sLangTxt_StopReport            = _T("停止报告");
	g_sLangID_DevToolBar             = _T("sDevToolBar");
	g_sLangTxt_DevToolBar            = _T("设备工具栏");
	g_sLangID_DevToolBarTip             = _T("sDevToolBarTip");
	g_sLangTxt_DevToolBarTip            = _T("显示或隐藏设备工具栏\n切换设备工具栏");
	g_sLangID_OutputWndTip             = _T("sOutputWndTip");
	g_sLangTxt_OutputWndTip            = _T("显示或隐藏输出窗口\n切换输出窗口");
	g_sLangID_MonitorBindError             = _T("sMonitorBindError");
	g_sLangTxt_MonitorBindError            = _T("监视绑定错误");
	g_sLangID_MonitorMessageInf             = _T("sMonitorMessageInf");
	g_sLangTxt_MonitorMessageInf            = _T("监视报文信息");
	g_sLangID_MonitorMessage             = _T("sMonitorMessage");
	g_sLangTxt_MonitorMessage            = _T("监视报文");

	g_sLangID_ClipboardData             = _T("sClipboardData");
	g_sLangTxt_ClipboardData            = _T("剪切板数据");
	//  g_sLangID_DataList             = _T("sDataList");
	//  g_sLangTxt_DataList            = _T("数据列表");
	g_sLangID_ReadClipboard             = _T("sReadClipboard");
	g_sLangTxt_ReadClipboard            = _T("读取剪切板");
	g_sLangID_AddToList             = _T("sAddToList");
	g_sLangTxt_AddToList            = _T("添加到列表");
	g_sLangID_InsertList             = _T("sInsertList");
	g_sLangTxt_InsertList            = _T("插入到列表尾");
	g_sLangID_ClearList             = _T("sClearList");
	g_sLangTxt_ClearList            = _T("清空列表");
	g_sLangID_InsertIndex             = _T("sInsertIndex");
	g_sLangTxt_InsertIndex            = _T("插入起始索引号");
	g_sLangID_PointDataPaste             = _T("sPointDataPaste");
	g_sLangTxt_PointDataPaste            = _T("点表数据粘贴");
	g_sLangID_NewDev             = _T("sNewDev");
	g_sLangTxt_NewDev            = _T("新建设备");
	g_sLangID_PointListFile             = _T("sPointListFile");
	g_sLangTxt_PointListFile            = _T("点表文件");
	g_sLangID_ModifyClose             = _T("sModifyClose");
	g_sLangTxt_ModifyClose            = _T("修改关闭");

	g_sLangID_FormulaType             = _T("sFormulaType");
	g_sLangTxt_FormulaType            = _T("公式种类");
	g_sLangID_FormulaEdit             = _T("sFormulaEdit");
	g_sLangTxt_FormulaEdit            = _T("公式编辑");
	g_sLangID_SelType             = _T("sSelType");
	g_sLangTxt_SelType            = _T("选择分类");
	g_sLangID_FormulaEditD             = _T("sFormulaEditD");
	g_sLangTxt_FormulaEditD            = _T("公式编辑对话框");

	g_sLangID_MonitorPrtcMessage             = _T("sMonitorPrtcMessage");
	g_sLangTxt_MonitorPrtcMessage             = _T("监视规约报文");
	g_sLangID_MonitorSOE             = _T("sMonitorSOE");
	g_sLangTxt_MonitorSOE             = _T("监视SOE");
	g_sLangID_Empty             = _T("sEmpty");
	g_sLangTxt_Empty             = _T("清空");
	g_sLangID_CommunMonitor             = _T("sCommunMonitor");
	g_sLangTxt_CommunMonitor             = _T("通讯监视");
	g_sLangID_SelCommunProcess             = _T("sSelCommunProcess");
	g_sLangTxt_SelCommunProcess             = _T("选择通讯过程");
	g_sLangID_SelProcessSet             = _T("sSelProcessSet");
	g_sLangTxt_SelProcessSet             = _T("选择过程数据接口设置");

	g_sLangID_Vaule             = _T("sVaule");
	g_sLangTxt_Vaule             = _T("数值");
	g_sLangID_PrtcMonitor             = _T("sPrtcMonitor");
	g_sLangTxt_PrtcMonitor             = _T("规约监视");
	g_sLangID_CannotAddView             = _T("sCannotAddView");
	g_sLangTxt_CannotAddView             = _T("无法加载位图: %x\n");
	g_sLangID_NewFolder2             = _T("sNewFolder2");
	g_sLangTxt_NewFolder2             = _T("新建文件夹...");
	g_sLangID_AddMemberFctn             = _T("sAddMemberFctn");
	g_sLangTxt_AddMemberFctn             = _T("添加成员函数...");
	g_sLangID_RptPathUnExist             = _T("sRptPathUnExist");
	g_sLangTxt_RptPathUnExist             = _T("报告路径“%s”不存在");
	g_sLangID_DataPathUnExist             = _T("sDataPathUnExist");
	g_sLangTxt_DataPathUnExist             = _T("数据集路径“%s”不存在");
	g_sLangID_DiffError             = _T("sDiffError");
	g_sLangTxt_DiffError             = _T("当前过程【%s】；结束的过程【%s】，两者不同，发生错误");
	g_sLangID_SendTestInf             = _T("sSendTestInf");
	g_sLangTxt_SendTestInf             = _T("===============发送测试完成消息[%s] WND=【%08x】 MSG=【%08x】");
	g_sLangID_SendSystemMsg             = _T("sSendSystemMsg");
	g_sLangTxt_SendSystemMsg            = _T("发送系统消息 WND=【%08x】 MSG=【%08x】(%d, %d)");
	g_sLangID_ColctnClcltFmla             = _T("sColctnClcltFmla");
	g_sLangTxt_ColctnClcltFmla              = _T("采集计算公式");
	g_sLangID_SendClcltFmla             = _T("sSendClcltFmla");
	g_sLangTxt_SendClcltFmla             = _T("发送计算公式");

    /*  以下几个，移动到基类CXLanguageResourceBase。2024-1-4  shaolei
	g_sLangID_Voltage             = _T("sVoltage");
	g_sLangTxt_Voltage            = _T("电压");
	g_sLangID_Current             = _T("sCurrent");
	g_sLangTxt_Current             = _T("电流");
	g_sLangID_ActivePower             = _T("sActivePower");
	g_sLangTxt_ActivePower             = _T("有功功率");
	g_sLangID_ReactivePower             = _T("sReactivePower");
	g_sLangTxt_ReactivePower             = _T("无功功率");
    g_sLangID_Frequency             = _T("sFrequency");
    g_sLangTxt_Frequency             = _T("频率");
	g_sLangID_PowerFactor             = _T("sPowerFactor");
	g_sLangTxt_PowerFactor             = _T("功率因数");
    */

	g_sLangID_Menu_32817             = _T("sMenu_32817");
	g_sLangTxt_Menu_32817             = _T("展开全部设备");
	g_sLangID_Menu_32818             = _T("sMenu_32818");
	g_sLangTxt_Menu_32818             = _T("折叠全部设备");
	g_sLangID_Menu_32819             = _T("sMenu_32819");
	g_sLangTxt_Menu_32819             = _T("刷新所有设备");


	g_sLangID_DeviceDataView             = _T("sDeviceDataView");
	g_sLangTxt_DeviceDataView             = _T("引擎设备数据视图");

}


CString g_sLangID_NotSelDev             ;    //= _T("sNotSelDev");
CString g_sLangTxt_NotSelDev            ;    //= _T("没有选择设备");
CString g_sLangID_PrtcProHome             ;    //= _T("sPrtcProHome");
CString g_sLangTxt_PrtcProHome            ;    //= _T("规约引擎操作主页");
CString g_sLangID_DevOpera             ;    //= _T("sDevOpera");
CString g_sLangTxt_DevOpera            ;    //= _T("设备操作");
CString g_sLangID_NewAdd             ;    //= _T("sNewAdd");
CString g_sLangTxt_NewAdd            ;    //= _T("新增");
CString g_sLangID_Connection             ;    //= _T("sConnection");
CString g_sLangTxt_Connection            ;    //= _T("连接");
CString g_sLangID_DisConnection             ;    //= _T("sDisConnection");
CString g_sLangTxt_DisConnection            ;    //= _T("断开连接");
CString g_sLangID_Uninstall             ;    //= _T("sUninstall");
CString g_sLangTxt_Uninstall            ;    //= _T("卸载");
CString g_sLangID_PointTableEdit             ;    //= _T("sPointTableEdit");
CString g_sLangTxt_PointTableEdit            ;    //= _T("点表编辑");
CString g_sLangID_CommuntSet             ;    //= _T("sCommuntSet");
CString g_sLangTxt_CommuntSet            ;    //= _T("通讯设置");
CString g_sLangID_CommunProcess             ;    //= _T("sCommunProcess ");
CString g_sLangTxt_CommunProcess             ;    //= _T("通讯过程");
CString g_sLangID_OperationProcess             ;    //= _T("sOperationProcess");
CString g_sLangTxt_OperationProcess            ;    //= _T("运行过程");
CString g_sLangID_ViewOprthPrcs             ;    //= _T("sViewOprthPrcs");
CString g_sLangTxt_ViewOprthPrcs            ;    //= _T("查看运行过程");
CString g_sLangID_StopProcess             ;    //= _T("sStopProcess");
CString g_sLangTxt_StopProcess            ;    //= _T("终止过程");
CString g_sLangID_ClearSOE             ;    //= _T("sClearSOE");
CString g_sLangTxt_ClearSOE            ;    //= _T("清空SOE");
CString g_sLangID_ClearMessage             ;    //= _T("sClearMessage");
CString g_sLangTxt_ClearMessage            ;    //= _T("清除报文");
CString g_sLangID_DebugMode             ;    //= _T("sDebugMode");
CString g_sLangTxt_DebugMode            ;    //= _T("调试模式");
CString g_sLangID_Report             ;    //= _T("sReport");
CString g_sLangTxt_Report             ;    //= _T("报告");
CString g_sLangID_StartReport             ;    //= _T("sStartReport");
CString g_sLangTxt_StartReport            ;    //= _T("启动报告");
CString g_sLangID_StopReport             ;    //= _T("sStopReport");
CString g_sLangTxt_StopReport            ;    //= _T("停止报告");
CString g_sLangID_DevToolBar             ;    //= _T("sDevToolBar");
CString g_sLangTxt_DevToolBar            ;    //= _T("设备工具栏");
CString g_sLangID_DevToolBarTip             ;    //= _T("sDevToolBarTip");
CString g_sLangTxt_DevToolBarTip            ;    //= _T("显示或隐藏设备工具栏\n切换设备工具栏");
CString g_sLangID_OutputWndTip             ;    //= _T("sOutputWndTip");
CString g_sLangTxt_OutputWndTip            ;    //= _T("显示或隐藏输出窗口\n切换输出窗口");
CString g_sLangID_MonitorBindError             ;    //= _T("sMonitorBindError");
CString g_sLangTxt_MonitorBindError            ;    //= _T("监视绑定错误");
CString g_sLangID_MonitorMessageInf             ;    //= _T("sMonitorMessageInf");
CString g_sLangTxt_MonitorMessageInf            ;    //= _T("监视报文信息");
CString g_sLangID_MonitorMessage             ;    //= _T("sMonitorMessage");
CString g_sLangTxt_MonitorMessage            ;    //= _T("监视报文");

CString g_sLangID_ClipboardData             ;    //= _T("sClipboardData");
CString g_sLangTxt_ClipboardData            ;    //= _T("剪切板数据");
// CString g_sLangID_DataList             ;    //= _T("sDataList");
// CString g_sLangTxt_DataList            ;    //= _T("数据列表");
CString g_sLangID_ReadClipboard             ;    //= _T("sReadClipboard");
CString g_sLangTxt_ReadClipboard            ;    //= _T("读取剪切板");
CString g_sLangID_AddToList             ;    //= _T("sAddToList");
CString g_sLangTxt_AddToList            ;    //= _T("添加到列表");
CString g_sLangID_InsertList             ;    //= _T("sInsertList");
CString g_sLangTxt_InsertList            ;    //= _T("插入到列表尾");
CString g_sLangID_ClearList             ;    //= _T("sClearList");
CString g_sLangTxt_ClearList            ;    //= _T("清空列表");
CString g_sLangID_InsertIndex             ;    //= _T("sInsertIndex");
CString g_sLangTxt_InsertIndex            ;    //= _T("插入起始索引号");
CString g_sLangID_PointDataPaste             ;    //= _T("sPointDataPaste");
CString g_sLangTxt_PointDataPaste            ;    //= _T("点表数据粘贴");
CString g_sLangID_NewDev             ;    //= _T("sNewDev");
CString g_sLangTxt_NewDev            ;    //= _T("新建设备");
CString g_sLangID_PointListFile             ;    //= _T("sPointListFile");
CString g_sLangTxt_PointListFile            ;    //= _T("点表文件");
CString g_sLangID_ModifyClose             ;    //= _T("sModifyClose");
CString g_sLangTxt_ModifyClose            ;    //= _T("修改关闭");

CString g_sLangID_FormulaType             ;    //= _T("sFormulaType");
CString g_sLangTxt_FormulaType            ;    //= _T("公式种类");
CString g_sLangID_FormulaEdit             ;    //= _T("sFormulaEdit");
CString g_sLangTxt_FormulaEdit            ;    //= _T("公式编辑");
CString g_sLangID_SelType             ;    //= _T("sSelType");
CString g_sLangTxt_SelType            ;    //= _T("选择分类");
CString g_sLangID_FormulaEditD             ;    //= _T("sFormulaEditD");
CString g_sLangTxt_FormulaEditD            ;    //= _T("公式编辑对话框");

CString g_sLangID_MonitorPrtcMessage             ;    //= _T("sMonitorPrtcMessage");
CString g_sLangTxt_MonitorPrtcMessage             ;    //= _T("监视规约报文");
CString g_sLangID_MonitorSOE             ;    //= _T("sMonitorSOE");
CString g_sLangTxt_MonitorSOE             ;    //= _T("监视SOE");
CString g_sLangID_Empty             ;    //= _T("sEmpty");
CString g_sLangTxt_Empty             ;    //= _T("清空");
CString g_sLangID_CommunMonitor             ;    //= _T("sCommunMonitor");
CString g_sLangTxt_CommunMonitor             ;    //= _T("通讯监视");
CString g_sLangID_SelCommunProcess             ;    //= _T("sSelCommunProcess");
CString g_sLangTxt_SelCommunProcess             ;    //= _T("选择通讯过程");
CString g_sLangID_SelProcessSet             ;    //= _T("sSelProcessSet");
CString g_sLangTxt_SelProcessSet             ;    //= _T("选择过程数据接口设置");

CString g_sLangID_Vaule             ;    //= _T("sVaule");
CString g_sLangTxt_Vaule             ;    //= _T("数值");
CString g_sLangID_PrtcMonitor             ;    //= _T("sPrtcMonitor");
CString g_sLangTxt_PrtcMonitor             ;    //= _T("规约监视");
CString g_sLangID_CannotAddView             ;    //= _T("sCannotAddView");
CString g_sLangTxt_CannotAddView             ;    //= _T("无法加载位图: %x\n");
CString g_sLangID_NewFolder2             ;    //= _T("sNewFolder2");
CString g_sLangTxt_NewFolder2             ;    //= _T("新建文件夹...");
CString g_sLangID_AddMemberFctn             ;    //= _T("sAddMemberFctn");
CString g_sLangTxt_AddMemberFctn             ;    //= _T("添加成员函数...");
CString g_sLangID_RptPathUnExist             ;    //= _T("sRptPathUnExist");
CString g_sLangTxt_RptPathUnExist             ;    //= _T("报告路径“%s”不存在");
CString g_sLangID_DataPathUnExist             ;    //= _T("sDataPathUnExist");
CString g_sLangTxt_DataPathUnExist             ;    //= _T("数据集路径“%s”不存在");
CString g_sLangID_DiffError             ;    //= _T("sDiffError");
CString g_sLangTxt_DiffError             ;    //= _T("当前过程【%s】；结束的过程【%s】，两者不同，发生错误");
CString g_sLangID_SendTestInf             ;    //= _T("sSendTestInf");
CString g_sLangTxt_SendTestInf             ;    //= _T(";    //=;    //=;    //=;    //=;    //=;    //=;    //=;    //=;    //=;    //=;    //=;    //=;    //=;    //=;    //=发送测试完成消息[%s] WND;    //=【%08x】 MSG;    //=【%08x】");
CString g_sLangID_SendSystemMsg             ;    //= _T("sSendSystemMsg");
CString g_sLangTxt_SendSystemMsg            ;    //= _T("发送系统消息 WND;    //=【%08x】 MSG;    //=【%08x】(%d, %d)");
CString g_sLangID_ColctnClcltFmla             ;    //= _T("sColctnClcltFmla");
CString g_sLangTxt_ColctnClcltFmla              ;    //= _T("采集计算公式");
CString g_sLangID_SendClcltFmla             ;    //= _T("sSendClcltFmla");
CString g_sLangTxt_SendClcltFmla             ;    //= _T("发送计算公式");

/*  以下几个，移动到基类CXLanguageResourceBase。2024-1-4  shaolei
CString g_sLangID_Voltage             ;    //= _T("sVoltage");
CString g_sLangTxt_Voltage            ;    //= _T("电压");
CString g_sLangID_Current             ;    //= _T("sCurrent");
CString g_sLangTxt_Current             ;    //= _T("电流");
CString g_sLangID_ActivePower             ;    //= _T("sActivePower");
CString g_sLangTxt_ActivePower             ;    //= _T("有功功率");
CString g_sLangID_ReactivePower             ;    //= _T("sReactivePower");
CString g_sLangTxt_ReactivePower             ;    //= _T("无功功率");
CString g_sLangID_Frequency             ;    //= _T("sFrequency");
CString g_sLangTxt_Frequency             ;    //= _T("频率");
CString g_sLangID_PowerFactor             ;    //= _T("sPowerFactor");
CString g_sLangTxt_PowerFactor             ;    //= _T("功率因数");
*/

CString g_sLangID_Menu_32817             ;    //= _T("sMenu_32817");
CString g_sLangTxt_Menu_32817             ;    //= _T("展开全部设备");
CString g_sLangID_Menu_32818             ;    //= _T("sMenu_32818");
CString g_sLangTxt_Menu_32818             ;    //= _T("折叠全部设备");
CString g_sLangID_Menu_32819             ;    //= _T("sMenu_32819");
CString g_sLangTxt_Menu_32819             ;    //= _T("刷新所有设备");


CString g_sLangID_DeviceDataView             ;    //= _T("sDeviceDataView");
CString g_sLangTxt_DeviceDataView             ;    //= _T("引擎设备数据视图");
