//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

    /*  ���¼������ƶ�������CXLanguageResourceBase��2024-1-4  shaolei
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
	g_sLangTxt_NotSelDev            = _T("û��ѡ���豸");
	g_sLangID_PrtcProHome             = _T("sPrtcProHome");
	g_sLangTxt_PrtcProHome            = _T("��Լ���������ҳ");
	g_sLangID_DevOpera             = _T("sDevOpera");
	g_sLangTxt_DevOpera            = _T("�豸����");
	g_sLangID_NewAdd             = _T("sNewAdd");
	g_sLangTxt_NewAdd            = _T("����");
	g_sLangID_Connection             = _T("sConnection");
	g_sLangTxt_Connection            = _T("����");
	g_sLangID_DisConnection             = _T("sDisConnection");
	g_sLangTxt_DisConnection            = _T("�Ͽ�����");
	g_sLangID_Uninstall             = _T("sUninstall");
	g_sLangTxt_Uninstall            = _T("ж��");
	g_sLangID_PointTableEdit             = _T("sPointTableEdit");
	g_sLangTxt_PointTableEdit            = _T("���༭");
	g_sLangID_CommuntSet             = _T("sCommuntSet");
	g_sLangTxt_CommuntSet            = _T("ͨѶ����");
	g_sLangID_CommunProcess             = _T("sCommunProcess ");
	g_sLangTxt_CommunProcess             = _T("ͨѶ����");
	g_sLangID_OperationProcess             = _T("sOperationProcess");
	g_sLangTxt_OperationProcess            = _T("���й���");
	g_sLangID_ViewOprthPrcs             = _T("sViewOprthPrcs");
	g_sLangTxt_ViewOprthPrcs            = _T("�鿴���й���");
	g_sLangID_StopProcess             = _T("sStopProcess");
	g_sLangTxt_StopProcess            = _T("��ֹ����");
	g_sLangID_ClearSOE             = _T("sClearSOE");
	g_sLangTxt_ClearSOE            = _T("���SOE");
	g_sLangID_ClearMessage             = _T("sClearMessage");
	g_sLangTxt_ClearMessage            = _T("�������");
	g_sLangID_DebugMode             = _T("sDebugMode");
	g_sLangTxt_DebugMode            = _T("����ģʽ");
	g_sLangID_Report             = _T("sReport");
	g_sLangTxt_Report             = _T("����");
	g_sLangID_StartReport             = _T("sStartReport");
	g_sLangTxt_StartReport            = _T("��������");
	g_sLangID_StopReport             = _T("sStopReport");
	g_sLangTxt_StopReport            = _T("ֹͣ����");
	g_sLangID_DevToolBar             = _T("sDevToolBar");
	g_sLangTxt_DevToolBar            = _T("�豸������");
	g_sLangID_DevToolBarTip             = _T("sDevToolBarTip");
	g_sLangTxt_DevToolBarTip            = _T("��ʾ�������豸������\n�л��豸������");
	g_sLangID_OutputWndTip             = _T("sOutputWndTip");
	g_sLangTxt_OutputWndTip            = _T("��ʾ�������������\n�л��������");
	g_sLangID_MonitorBindError             = _T("sMonitorBindError");
	g_sLangTxt_MonitorBindError            = _T("���Ӱ󶨴���");
	g_sLangID_MonitorMessageInf             = _T("sMonitorMessageInf");
	g_sLangTxt_MonitorMessageInf            = _T("���ӱ�����Ϣ");
	g_sLangID_MonitorMessage             = _T("sMonitorMessage");
	g_sLangTxt_MonitorMessage            = _T("���ӱ���");

	g_sLangID_ClipboardData             = _T("sClipboardData");
	g_sLangTxt_ClipboardData            = _T("���а�����");
	//  g_sLangID_DataList             = _T("sDataList");
	//  g_sLangTxt_DataList            = _T("�����б�");
	g_sLangID_ReadClipboard             = _T("sReadClipboard");
	g_sLangTxt_ReadClipboard            = _T("��ȡ���а�");
	g_sLangID_AddToList             = _T("sAddToList");
	g_sLangTxt_AddToList            = _T("��ӵ��б�");
	g_sLangID_InsertList             = _T("sInsertList");
	g_sLangTxt_InsertList            = _T("���뵽�б�β");
	g_sLangID_ClearList             = _T("sClearList");
	g_sLangTxt_ClearList            = _T("����б�");
	g_sLangID_InsertIndex             = _T("sInsertIndex");
	g_sLangTxt_InsertIndex            = _T("������ʼ������");
	g_sLangID_PointDataPaste             = _T("sPointDataPaste");
	g_sLangTxt_PointDataPaste            = _T("�������ճ��");
	g_sLangID_NewDev             = _T("sNewDev");
	g_sLangTxt_NewDev            = _T("�½��豸");
	g_sLangID_PointListFile             = _T("sPointListFile");
	g_sLangTxt_PointListFile            = _T("����ļ�");
	g_sLangID_ModifyClose             = _T("sModifyClose");
	g_sLangTxt_ModifyClose            = _T("�޸Ĺر�");

	g_sLangID_FormulaType             = _T("sFormulaType");
	g_sLangTxt_FormulaType            = _T("��ʽ����");
	g_sLangID_FormulaEdit             = _T("sFormulaEdit");
	g_sLangTxt_FormulaEdit            = _T("��ʽ�༭");
	g_sLangID_SelType             = _T("sSelType");
	g_sLangTxt_SelType            = _T("ѡ�����");
	g_sLangID_FormulaEditD             = _T("sFormulaEditD");
	g_sLangTxt_FormulaEditD            = _T("��ʽ�༭�Ի���");

	g_sLangID_MonitorPrtcMessage             = _T("sMonitorPrtcMessage");
	g_sLangTxt_MonitorPrtcMessage             = _T("���ӹ�Լ����");
	g_sLangID_MonitorSOE             = _T("sMonitorSOE");
	g_sLangTxt_MonitorSOE             = _T("����SOE");
	g_sLangID_Empty             = _T("sEmpty");
	g_sLangTxt_Empty             = _T("���");
	g_sLangID_CommunMonitor             = _T("sCommunMonitor");
	g_sLangTxt_CommunMonitor             = _T("ͨѶ����");
	g_sLangID_SelCommunProcess             = _T("sSelCommunProcess");
	g_sLangTxt_SelCommunProcess             = _T("ѡ��ͨѶ����");
	g_sLangID_SelProcessSet             = _T("sSelProcessSet");
	g_sLangTxt_SelProcessSet             = _T("ѡ��������ݽӿ�����");

	g_sLangID_Vaule             = _T("sVaule");
	g_sLangTxt_Vaule             = _T("��ֵ");
	g_sLangID_PrtcMonitor             = _T("sPrtcMonitor");
	g_sLangTxt_PrtcMonitor             = _T("��Լ����");
	g_sLangID_CannotAddView             = _T("sCannotAddView");
	g_sLangTxt_CannotAddView             = _T("�޷�����λͼ: %x\n");
	g_sLangID_NewFolder2             = _T("sNewFolder2");
	g_sLangTxt_NewFolder2             = _T("�½��ļ���...");
	g_sLangID_AddMemberFctn             = _T("sAddMemberFctn");
	g_sLangTxt_AddMemberFctn             = _T("��ӳ�Ա����...");
	g_sLangID_RptPathUnExist             = _T("sRptPathUnExist");
	g_sLangTxt_RptPathUnExist             = _T("����·����%s��������");
	g_sLangID_DataPathUnExist             = _T("sDataPathUnExist");
	g_sLangTxt_DataPathUnExist             = _T("���ݼ�·����%s��������");
	g_sLangID_DiffError             = _T("sDiffError");
	g_sLangTxt_DiffError             = _T("��ǰ���̡�%s���������Ĺ��̡�%s�������߲�ͬ����������");
	g_sLangID_SendTestInf             = _T("sSendTestInf");
	g_sLangTxt_SendTestInf             = _T("===============���Ͳ��������Ϣ[%s] WND=��%08x�� MSG=��%08x��");
	g_sLangID_SendSystemMsg             = _T("sSendSystemMsg");
	g_sLangTxt_SendSystemMsg            = _T("����ϵͳ��Ϣ WND=��%08x�� MSG=��%08x��(%d, %d)");
	g_sLangID_ColctnClcltFmla             = _T("sColctnClcltFmla");
	g_sLangTxt_ColctnClcltFmla              = _T("�ɼ����㹫ʽ");
	g_sLangID_SendClcltFmla             = _T("sSendClcltFmla");
	g_sLangTxt_SendClcltFmla             = _T("���ͼ��㹫ʽ");

    /*  ���¼������ƶ�������CXLanguageResourceBase��2024-1-4  shaolei
	g_sLangID_Voltage             = _T("sVoltage");
	g_sLangTxt_Voltage            = _T("��ѹ");
	g_sLangID_Current             = _T("sCurrent");
	g_sLangTxt_Current             = _T("����");
	g_sLangID_ActivePower             = _T("sActivePower");
	g_sLangTxt_ActivePower             = _T("�й�����");
	g_sLangID_ReactivePower             = _T("sReactivePower");
	g_sLangTxt_ReactivePower             = _T("�޹�����");
    g_sLangID_Frequency             = _T("sFrequency");
    g_sLangTxt_Frequency             = _T("Ƶ��");
	g_sLangID_PowerFactor             = _T("sPowerFactor");
	g_sLangTxt_PowerFactor             = _T("��������");
    */

	g_sLangID_Menu_32817             = _T("sMenu_32817");
	g_sLangTxt_Menu_32817             = _T("չ��ȫ���豸");
	g_sLangID_Menu_32818             = _T("sMenu_32818");
	g_sLangTxt_Menu_32818             = _T("�۵�ȫ���豸");
	g_sLangID_Menu_32819             = _T("sMenu_32819");
	g_sLangTxt_Menu_32819             = _T("ˢ�������豸");


	g_sLangID_DeviceDataView             = _T("sDeviceDataView");
	g_sLangTxt_DeviceDataView             = _T("�����豸������ͼ");

}


CString g_sLangID_NotSelDev             ;    //= _T("sNotSelDev");
CString g_sLangTxt_NotSelDev            ;    //= _T("û��ѡ���豸");
CString g_sLangID_PrtcProHome             ;    //= _T("sPrtcProHome");
CString g_sLangTxt_PrtcProHome            ;    //= _T("��Լ���������ҳ");
CString g_sLangID_DevOpera             ;    //= _T("sDevOpera");
CString g_sLangTxt_DevOpera            ;    //= _T("�豸����");
CString g_sLangID_NewAdd             ;    //= _T("sNewAdd");
CString g_sLangTxt_NewAdd            ;    //= _T("����");
CString g_sLangID_Connection             ;    //= _T("sConnection");
CString g_sLangTxt_Connection            ;    //= _T("����");
CString g_sLangID_DisConnection             ;    //= _T("sDisConnection");
CString g_sLangTxt_DisConnection            ;    //= _T("�Ͽ�����");
CString g_sLangID_Uninstall             ;    //= _T("sUninstall");
CString g_sLangTxt_Uninstall            ;    //= _T("ж��");
CString g_sLangID_PointTableEdit             ;    //= _T("sPointTableEdit");
CString g_sLangTxt_PointTableEdit            ;    //= _T("���༭");
CString g_sLangID_CommuntSet             ;    //= _T("sCommuntSet");
CString g_sLangTxt_CommuntSet            ;    //= _T("ͨѶ����");
CString g_sLangID_CommunProcess             ;    //= _T("sCommunProcess ");
CString g_sLangTxt_CommunProcess             ;    //= _T("ͨѶ����");
CString g_sLangID_OperationProcess             ;    //= _T("sOperationProcess");
CString g_sLangTxt_OperationProcess            ;    //= _T("���й���");
CString g_sLangID_ViewOprthPrcs             ;    //= _T("sViewOprthPrcs");
CString g_sLangTxt_ViewOprthPrcs            ;    //= _T("�鿴���й���");
CString g_sLangID_StopProcess             ;    //= _T("sStopProcess");
CString g_sLangTxt_StopProcess            ;    //= _T("��ֹ����");
CString g_sLangID_ClearSOE             ;    //= _T("sClearSOE");
CString g_sLangTxt_ClearSOE            ;    //= _T("���SOE");
CString g_sLangID_ClearMessage             ;    //= _T("sClearMessage");
CString g_sLangTxt_ClearMessage            ;    //= _T("�������");
CString g_sLangID_DebugMode             ;    //= _T("sDebugMode");
CString g_sLangTxt_DebugMode            ;    //= _T("����ģʽ");
CString g_sLangID_Report             ;    //= _T("sReport");
CString g_sLangTxt_Report             ;    //= _T("����");
CString g_sLangID_StartReport             ;    //= _T("sStartReport");
CString g_sLangTxt_StartReport            ;    //= _T("��������");
CString g_sLangID_StopReport             ;    //= _T("sStopReport");
CString g_sLangTxt_StopReport            ;    //= _T("ֹͣ����");
CString g_sLangID_DevToolBar             ;    //= _T("sDevToolBar");
CString g_sLangTxt_DevToolBar            ;    //= _T("�豸������");
CString g_sLangID_DevToolBarTip             ;    //= _T("sDevToolBarTip");
CString g_sLangTxt_DevToolBarTip            ;    //= _T("��ʾ�������豸������\n�л��豸������");
CString g_sLangID_OutputWndTip             ;    //= _T("sOutputWndTip");
CString g_sLangTxt_OutputWndTip            ;    //= _T("��ʾ�������������\n�л��������");
CString g_sLangID_MonitorBindError             ;    //= _T("sMonitorBindError");
CString g_sLangTxt_MonitorBindError            ;    //= _T("���Ӱ󶨴���");
CString g_sLangID_MonitorMessageInf             ;    //= _T("sMonitorMessageInf");
CString g_sLangTxt_MonitorMessageInf            ;    //= _T("���ӱ�����Ϣ");
CString g_sLangID_MonitorMessage             ;    //= _T("sMonitorMessage");
CString g_sLangTxt_MonitorMessage            ;    //= _T("���ӱ���");

CString g_sLangID_ClipboardData             ;    //= _T("sClipboardData");
CString g_sLangTxt_ClipboardData            ;    //= _T("���а�����");
// CString g_sLangID_DataList             ;    //= _T("sDataList");
// CString g_sLangTxt_DataList            ;    //= _T("�����б�");
CString g_sLangID_ReadClipboard             ;    //= _T("sReadClipboard");
CString g_sLangTxt_ReadClipboard            ;    //= _T("��ȡ���а�");
CString g_sLangID_AddToList             ;    //= _T("sAddToList");
CString g_sLangTxt_AddToList            ;    //= _T("��ӵ��б�");
CString g_sLangID_InsertList             ;    //= _T("sInsertList");
CString g_sLangTxt_InsertList            ;    //= _T("���뵽�б�β");
CString g_sLangID_ClearList             ;    //= _T("sClearList");
CString g_sLangTxt_ClearList            ;    //= _T("����б�");
CString g_sLangID_InsertIndex             ;    //= _T("sInsertIndex");
CString g_sLangTxt_InsertIndex            ;    //= _T("������ʼ������");
CString g_sLangID_PointDataPaste             ;    //= _T("sPointDataPaste");
CString g_sLangTxt_PointDataPaste            ;    //= _T("�������ճ��");
CString g_sLangID_NewDev             ;    //= _T("sNewDev");
CString g_sLangTxt_NewDev            ;    //= _T("�½��豸");
CString g_sLangID_PointListFile             ;    //= _T("sPointListFile");
CString g_sLangTxt_PointListFile            ;    //= _T("����ļ�");
CString g_sLangID_ModifyClose             ;    //= _T("sModifyClose");
CString g_sLangTxt_ModifyClose            ;    //= _T("�޸Ĺر�");

CString g_sLangID_FormulaType             ;    //= _T("sFormulaType");
CString g_sLangTxt_FormulaType            ;    //= _T("��ʽ����");
CString g_sLangID_FormulaEdit             ;    //= _T("sFormulaEdit");
CString g_sLangTxt_FormulaEdit            ;    //= _T("��ʽ�༭");
CString g_sLangID_SelType             ;    //= _T("sSelType");
CString g_sLangTxt_SelType            ;    //= _T("ѡ�����");
CString g_sLangID_FormulaEditD             ;    //= _T("sFormulaEditD");
CString g_sLangTxt_FormulaEditD            ;    //= _T("��ʽ�༭�Ի���");

CString g_sLangID_MonitorPrtcMessage             ;    //= _T("sMonitorPrtcMessage");
CString g_sLangTxt_MonitorPrtcMessage             ;    //= _T("���ӹ�Լ����");
CString g_sLangID_MonitorSOE             ;    //= _T("sMonitorSOE");
CString g_sLangTxt_MonitorSOE             ;    //= _T("����SOE");
CString g_sLangID_Empty             ;    //= _T("sEmpty");
CString g_sLangTxt_Empty             ;    //= _T("���");
CString g_sLangID_CommunMonitor             ;    //= _T("sCommunMonitor");
CString g_sLangTxt_CommunMonitor             ;    //= _T("ͨѶ����");
CString g_sLangID_SelCommunProcess             ;    //= _T("sSelCommunProcess");
CString g_sLangTxt_SelCommunProcess             ;    //= _T("ѡ��ͨѶ����");
CString g_sLangID_SelProcessSet             ;    //= _T("sSelProcessSet");
CString g_sLangTxt_SelProcessSet             ;    //= _T("ѡ��������ݽӿ�����");

CString g_sLangID_Vaule             ;    //= _T("sVaule");
CString g_sLangTxt_Vaule             ;    //= _T("��ֵ");
CString g_sLangID_PrtcMonitor             ;    //= _T("sPrtcMonitor");
CString g_sLangTxt_PrtcMonitor             ;    //= _T("��Լ����");
CString g_sLangID_CannotAddView             ;    //= _T("sCannotAddView");
CString g_sLangTxt_CannotAddView             ;    //= _T("�޷�����λͼ: %x\n");
CString g_sLangID_NewFolder2             ;    //= _T("sNewFolder2");
CString g_sLangTxt_NewFolder2             ;    //= _T("�½��ļ���...");
CString g_sLangID_AddMemberFctn             ;    //= _T("sAddMemberFctn");
CString g_sLangTxt_AddMemberFctn             ;    //= _T("��ӳ�Ա����...");
CString g_sLangID_RptPathUnExist             ;    //= _T("sRptPathUnExist");
CString g_sLangTxt_RptPathUnExist             ;    //= _T("����·����%s��������");
CString g_sLangID_DataPathUnExist             ;    //= _T("sDataPathUnExist");
CString g_sLangTxt_DataPathUnExist             ;    //= _T("���ݼ�·����%s��������");
CString g_sLangID_DiffError             ;    //= _T("sDiffError");
CString g_sLangTxt_DiffError             ;    //= _T("��ǰ���̡�%s���������Ĺ��̡�%s�������߲�ͬ����������");
CString g_sLangID_SendTestInf             ;    //= _T("sSendTestInf");
CString g_sLangTxt_SendTestInf             ;    //= _T(";    //=;    //=;    //=;    //=;    //=;    //=;    //=;    //=;    //=;    //=;    //=;    //=;    //=;    //=;    //=���Ͳ��������Ϣ[%s] WND;    //=��%08x�� MSG;    //=��%08x��");
CString g_sLangID_SendSystemMsg             ;    //= _T("sSendSystemMsg");
CString g_sLangTxt_SendSystemMsg            ;    //= _T("����ϵͳ��Ϣ WND;    //=��%08x�� MSG;    //=��%08x��(%d, %d)");
CString g_sLangID_ColctnClcltFmla             ;    //= _T("sColctnClcltFmla");
CString g_sLangTxt_ColctnClcltFmla              ;    //= _T("�ɼ����㹫ʽ");
CString g_sLangID_SendClcltFmla             ;    //= _T("sSendClcltFmla");
CString g_sLangTxt_SendClcltFmla             ;    //= _T("���ͼ��㹫ʽ");

/*  ���¼������ƶ�������CXLanguageResourceBase��2024-1-4  shaolei
CString g_sLangID_Voltage             ;    //= _T("sVoltage");
CString g_sLangTxt_Voltage            ;    //= _T("��ѹ");
CString g_sLangID_Current             ;    //= _T("sCurrent");
CString g_sLangTxt_Current             ;    //= _T("����");
CString g_sLangID_ActivePower             ;    //= _T("sActivePower");
CString g_sLangTxt_ActivePower             ;    //= _T("�й�����");
CString g_sLangID_ReactivePower             ;    //= _T("sReactivePower");
CString g_sLangTxt_ReactivePower             ;    //= _T("�޹�����");
CString g_sLangID_Frequency             ;    //= _T("sFrequency");
CString g_sLangTxt_Frequency             ;    //= _T("Ƶ��");
CString g_sLangID_PowerFactor             ;    //= _T("sPowerFactor");
CString g_sLangTxt_PowerFactor             ;    //= _T("��������");
*/

CString g_sLangID_Menu_32817             ;    //= _T("sMenu_32817");
CString g_sLangTxt_Menu_32817             ;    //= _T("չ��ȫ���豸");
CString g_sLangID_Menu_32818             ;    //= _T("sMenu_32818");
CString g_sLangTxt_Menu_32818             ;    //= _T("�۵�ȫ���豸");
CString g_sLangID_Menu_32819             ;    //= _T("sMenu_32819");
CString g_sLangTxt_Menu_32819             ;    //= _T("ˢ�������豸");


CString g_sLangID_DeviceDataView             ;    //= _T("sDeviceDataView");
CString g_sLangTxt_DeviceDataView             ;    //= _T("�����豸������ͼ");
