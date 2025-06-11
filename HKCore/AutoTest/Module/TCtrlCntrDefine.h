#pragma once

#include "../../Module/BaseClass/ExBaseList.h"
#include "../../Module/API/GlobalConfigApi.h"
#include "AutoTestXMLRWKeys.h"
#include "GuideBook/GuideBookDefine.h"
#include "../../Module/API/FileApi.h"

#ifndef _PSX_QT_LINUX_
#include "../../Module/XFileMngrBase/XFileMngr.h"
#endif

extern CString g_strTCtrlCntrWorkspacePath;//				= _T("");
extern CString g_strTCtrlCntrTemplatePath	;//			= _T("");
extern CString g_strTCtrlCntrLibraryPath;//					= _T("");

static const CString g_strTCtrlCntrTaskMngrFile				= _T("TaskMngr.xml");
static const CString g_strTCtrlCntrWorkspaceCfgFile		= _T("Workspace.xml");

static const CString g_strXmlPostfix = _T(".xml");
static const CString g_strBinaryPostfix = _T(".tdp");
static const CString g_strDocPostfix = _T(".doc");
static const CString g_strMapXmlSubPostfix = _T("_map");
static const CString g_strGbBinaryPostfix = _T("tdp");
static const CString g_strGuideBookBinaryPostfix = _T("gbrpt");
static const CString g_strTestTaskFilePostfix = _T("gbtsk");
static const CString g_strGuideBookBinaryPostfix_SdvSpoMgrp = _T("gbmrpt"); //��ͨ��
static const CString g_strGuideBookMdTaskPostfix = _T("gbmtsk"); //��װ��
static const CString g_strGuideBookSdvMppTaskPostfix = _T("gbsdmp"); //��װ�ö��Լ
static const CString g_strGuideBookMdvMgrpTaskPostfix = _T("gbmdmrpt"); //��װ�ö�ͨ��
static const CString g_strTempGuideBookBinaryPostfix = _T("tgbrpt"); //������Ŀ��ʱ�ļ���Ҳ������xml
static const CString g_strDocFilePostfix = _T("doc");
static const CString g_strJsonFilePostfix = _T("json");		//20230901 huangliang
static const CString g_strVisioFilePostfix = _T("vsdx");


void InitTCtrlCntrPath(BOOL bUseAts=FALSE);

inline void GetTCtrlCntrWorkspaceCfgFile(CString &strFile)
{
    strFile.Format(_T("%s%s"), g_strTCtrlCntrWorkspacePath.GetString(),  g_strTCtrlCntrWorkspaceCfgFile.GetString());
}

inline void GetTCtrlCntrTaskMngrCfgFile(CString& strFile)
{
    strFile.Format(_T("%s%s"),  g_strTCtrlCntrLibraryPath.GetString(), g_strTCtrlCntrTaskMngrFile.GetString());
}

inline void GetGuideBookXMLFileName(const CString &strTaskID, const CString &strProjectID, CString &strFile)
{
    strFile.Format(_T("%s%s\\%s%s"),  g_strTCtrlCntrWorkspacePath.GetString(), strTaskID.GetString(), strProjectID.GetString(), g_strGbFilePostfix.GetString());
}

inline void GetGuideBookBinaryFileName(const CString &strTaskID, const CString &strProjectID, CString &strFile)
{
    strFile.Format(_T("%s%s\\%s%s"),  g_strTCtrlCntrWorkspacePath.GetString(), strTaskID.GetString(), strProjectID.GetString(), g_strBinaryPostfix.GetString());
}

inline CString GetGuideBookBinaryFileName(const CString &strGbBiaryFileName)
{
	CString strFile;
    strFile.Format(_T("%s%s"),  g_strTCtrlCntrWorkspacePath.GetString(), strGbBiaryFileName.GetString());
	return strFile;
}

inline CString GetGuideBookGbxmlFileName(const CString &strGbGbxmlFileName)
{
	CString strFile;
	strFile.Format(_T("%s%s"),  g_strTCtrlCntrTemplatePath.GetString(), strGbGbxmlFileName.GetString());
	return strFile;
}

inline CString GetGuideBookDocRptFileName(const CString &strGbDocRptFileName)
{
	CString strFile;
	strFile.Format(_T("%s%s"),  g_strTCtrlCntrWorkspacePath.GetString(), strGbDocRptFileName.GetString());
	return strFile;
}

inline void GetReportFileName(const CString &strTaskID, const CString &strProjectID, CString &strFile)
{
    strFile.Format(_T("%s%s\\%s%s"),  g_strTCtrlCntrWorkspacePath.GetString(), strTaskID.GetString(), strProjectID.GetString(), g_strDocPostfix.GetString());
}

inline BOOL ATS_IsTestTaskFile(const CString &strFile)
{
	CString strTemp = ParseFilePostfix(strFile);
	strTemp.MakeLower();

	return (strTemp == g_strTestTaskFilePostfix);
}

inline BOOL ATS_IsTestFile_SdvSpoMgrp(const CString &strFile)
{
	CString strTemp = ParseFilePostfix(strFile);
	strTemp.MakeLower();

	return (strTemp == g_strGuideBookBinaryPostfix_SdvSpoMgrp);
}

inline BOOL ATS_IsTestTaskFile_MdvSpo(const CString &strFile)
{
	CString strTemp = ParseFilePostfix(strFile);
	strTemp.MakeLower();

	return (strTemp == g_strGuideBookMdTaskPostfix);
}

inline BOOL ATS_IsTestTaskFile_SdvMpo(const CString &strFile)
{
	CString strTemp = ParseFilePostfix(strFile);
	strTemp.MakeLower();

	return (strTemp == g_strGuideBookSdvMppTaskPostfix);
}

inline BOOL ATS_IsTestTaskFile_MdvMgrp(const CString &strFile)
{
	CString strTemp = ParseFilePostfix(strFile);
	strTemp.MakeLower();

	return (strTemp == g_strGuideBookMdvMgrpTaskPostfix);
}

inline BOOL ATS_IsGuideBookReportFile(const CString &strFile)
{
	CString strTemp = ParseFilePostfix(strFile);
	strTemp.MakeLower();

	return (strTemp == g_strGuideBookBinaryPostfix);
}

inline BOOL ATS_IsGuideBookFile(const CString &strFile)
{
	CString strTemp = ParseFilePostfix(strFile);
	strTemp.MakeLower();

	return (strTemp == g_strGbFileFilter);
}

#ifndef _PSX_QT_LINUX_
void ATS_InitSysReportFileMngr(CXFileMngr *pXFileMngr, const CString &strWorkSpacePath);
void ATS_InitSysReportFileMngr(CXFileMngr *pXFileMngr, const CString &strWorkSpacePath, const CString &strPostfix);
#endif

//������������Ϣ��ͨ���ӿ�ָ�����ײ���Թ��ܲ���
#define	WM_ELECTRIC_TEST	(WM_USER+1000)

//ͨѶ�������Ϣ��ͨ���ӿ�ָ����ͨѶ����
// #define	WM_COMM_COMMAND		(WM_USER+1001)

//��ȫ��ʩ��ϵͳ�����޸���Ϣ
#define	WM_SAFETY_TEST_FINISHED	(WM_USER+1002)

//ϵͳ�����޸���Ϣ
#define WM_SYSPARAEDIT_TEST_FINISHED	(WM_USER+1003)

//�ֶ�����
#define WM_MANUAL_TEST   (WM_USER+1004)

//������Ŀ�����Խڵ�
//���Ե�ǰ��Ŀ
#define WM_TESTPOINT  (WM_USER+1005)
#define WM_TESTPOINT_MD_ONE  (WM_USER+1012)

//�ӵ�ǰ��Ŀ��ʼ����
#define WM_TESTBELOW ( WM_USER+1006)
//�鿴����
#define WM_SHOWREPORT     (WM_USER+1007)
//�޸Ĳ���
#define WM_ITEM_PARA_EDIT     (WM_USER+1008)
//�޸Ĳ���
#define WM_SHOWRECORD     (WM_USER+1009)

//ͨѶ�����ֶ��޸���Ϣ
#define WM_COMMCMD_TEST_FINISHED	(WM_USER+1009)
#define  WM_VIEW_DEVICESETS         (WM_USER+1010)
#define  WM_EXPAND_ALL_CHILDREN     (WM_USER+1011)
//�鿴��������
#define WM_SHOWCHARDRAW     (WM_USER+1013)

//������Ŀ����
#define  WM_UPDATE_GBITEMOBJ     (WM_USER+1014)

//ʱ�Ӵ�����Ϣ��2017-5-13
#define  WM_TIMER_TRIGGER     (WM_USER+1015)

//����ȫ�����ϸ���Ŀ  lijq2019-1-18
#define  WM_TEST_ALL_INLEGIBLE_ITEMS     (WM_USER+1016)

//������Ŀ����������ģ�壺�򿪲���ģ��༭������б༭   LIJQ 2020-02-02
#define  WM_UPDATE_PARA_TO_GBDEV     (WM_USER+1017)

//shaolei �ⲿϵͳ�������¼����Ϣ  ���͸���ȫ��ʩ�Ի����ϵͳ�����༭�Ի���   20220611
#define WM_FINISH_INPUTDATA	(WM_USER + 1018)

//shaolei ���Թ����У���̬������Ŀ��������Ŀ��  2023-8-15
#define WM_INSERT_ITEMS	(WM_USER + 1019)

#define CLASSID_WORKSPACE					(CLASSID_EXLISTCLASS + 0x00000001)
#define CLASSID_TESTTASK					(CLASSID_EXLISTCLASS + 0x00000002)
#define CLASSID_TESTPROJECT					(CLASSID_BASECLASS + 0x00000003)
#define CLASSID_ERRTESTITEMREF				(CLASSID_BASECLASS + 0x00000004)
#define CLASSID_PPDEVICEREF					(CLASSID_BASECLASS + 0x00000005)
#define CLASSID_PPDEVICEREFS				(CLASSID_EXLISTCLASS + 0x00000006)
#define CLASSID_TESTWZDDEFINE				(CLASSID_BASECLASS + 0x00000007)
#define CLASSID_TESTWZDDEFINES				(CLASSID_EXLISTCLASS + 0x00000008)
#define CLASSID_STATIONTESTMAINCONFIG				(CLASSID_BASECLASS + 0x00000009)
#define CLASSID_TESTTASKS					(CLASSID_EXLISTCLASS + 0x0000000A)

#define CLASSID_TESTTASKMNGRS					(CLASSID_EXLISTCLASS + 0x0000000B)
#define CLASSID_TESTTASKMNGRSGROUP					(CLASSID_EXLISTCLASS + 0x0000000C)
#define CLASSID_TESTTASKMNGRSDB					(CLASSID_EXLISTCLASS + 0x0000000D)

//����CTestProject�ĸ���״̬���� 
static const CString g_strTestArchiving = _T("Archiving");
static const CString g_strTestFinished = _T("Finished");
static const CString g_strTestStop = _T("Stop");
static const CString g_strTesting	= _T("Testing");
static const CString g_strNormal = _T("Normal");


//������ĵ���������� ��CPAautoTestDoc::OnNewDocument()���޸ģ���������
//#define ATS_DOC_NAME _T("ATS")

//˫��CTaskMngrTreeCtrl�ϵĽڵ�ʱ�������µĿ����Ϣ
#define WM_CREATE_NEW_PROJECT_FRAME					(WM_USER+1101)
#define WM_CREATE_NEW_MPROJECT_FRAME				(WM_USER+1098)
#define WM_CREATE_NEW_MDTASK_FRAME					(WM_USER+1099)
#define WM_CREATE_NEW_SDVMPPTASK_FRAME				(WM_USER+1100)

//�޸�CMainFrame�ı�����������Ϣ
#define WM_SET_MAINFRAME_TITLE			(WM_USER+1102)

//�����µĲ��Թ��� ����Ӧ��word�ĵ���Guidebook��ӳ���ļ� ��Ϣ
#define WM_CREATE_NEW_TEST_PROJECT	(WM_USER+1103)

//��TaskMngrTree��ص���Ϣ
#define WM_NEW_TEST_TASK						(WM_USER + 1104)
#define WM_NEW_TEST_PROJECT				(WM_USER + 1105)
#define WM_DELETE_TEST_TASK				(WM_USER + 1106)
#define WM_DELETE_TEST_PROJECT		(WM_USER + 1107)
#define WM_FILE_TEST_TASK						(WM_USER + 1108)
#define WM_FILE_TEST_PROJECT				(WM_USER + 1109)
#define WM_OPEN_TEST_PROJECT				(WM_USER + 1110)
#define WM_CLOSE_TEST_PROJECT			(WM_USER + 1111)
// #define WM_ENGINE_SYSTEM_MSG           (WM_USER + 1112)
#define WM_TEST_BEGIN                        (WM_USER + 1113)
#define WM_TEST_STOP                         (WM_USER + 1114)
#define WM_TEST_SHOW_ITEM_REPORT                         (WM_USER + 1115)

#ifdef _use_test_task
CString GetTestTaskPath(CExBaseObject* pTestTask);
CString GetTestProjectTempFilePath(CExBaseObject* pTestProject);
CString GetTestProjectTempFileName(CExBaseObject* pTestProject,CExBaseObject* pItem);
#endif

BOOL ats_GetMdTestFile(CString &strMdTestFile, CWnd *pParent);
BOOL ats_GetSdvMppTestFile(CString &strSdvMppTestFile, CWnd *pParent);
void ats_GetMdTestFileFilter(CString &strFilter);
void ats_GetSdvMppTestFileFilter(CString &strFilter);
void ats_GetMdvMgrpTestFileFilter(CString &strFilter);

CString _P_GetProjectID();
#ifndef _PSX_QT_LINUX_
void ats_SetCocumentTitle(const CString &strText, CDocument *pDoc, BOOL bMain=FALSE, long nDeviceIndex=-1);
CString ats_GetCocumentTitle(const CString &strText);
#endif


//����ʱ�Ӷ���
#define TM_TESTTASK_PROJECT_FINISHED  1736
#define TM_TESTTASK_PROJECT_CREATENEW 1737
#define TM_TESTTASK_PROJECT_TEST      1738
#define TM_TESTTIME_LONG_SHOW         1739
#define UPDATE_TIMER_LONG  1

//��������
DWORD ATS_GetTkIDIndex(CComboBox *pComboBox);
DWORD ATS_GetTkIDIndex(CComboBox *pComboBox, CString &strTestType);
DWORD ATS_GetTkIDIndex(const CString &strTestType, CDataTypes *pDataTypes);



//������ͨģʽ����װ�á�������
#define TESTCONTROLMODE_NORMAL    0

//��װ�á�����Լ������౨��
#define TESTCONTROLMODE_MGBRPT    1

//��װ�á�����Լ���౨�棨ÿ��װ��һ�ݱ��棩
#define TESTCONTROLMODE_MDGBRPT   2

//��װ�á����Լ��ÿ�ֹ�Լһ�ֱ��棩
#define TESTCONTROLMODE_SDVMPP    3

//��װ�á�ÿ��װ�ö��飨�౨�棩
#define TESTCONTROLMODE_MDVMGRP    4


//
BOOL ATS_ValidateSystemPath(CString &strFile, const CString &strSysPath, const CString &strSysID);
BOOL ATS_ValidateSystemPath(CString &strFile, const CString &strSysPath);
long ATS_GetSrcDeviceModelFiles(const CString &strSrcDeviceModelFile, CStringArray &astrFiles);
