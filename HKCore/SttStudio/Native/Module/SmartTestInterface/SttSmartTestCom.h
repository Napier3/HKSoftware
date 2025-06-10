#pragma once

#include "XSmartTestEventInterface.h"
#include "../../../AutoTest/Module/XSmartTestClient.h"
#include "../SttCmd/GuideBook/SttGuideBook.h"
#include "..\..\..\Module\Office\msword9.h"

//2021-7-27   lijunqing ��  CDynDialogEx  ��Ϊ CWnd���򻯻��������
//2021-8-3  lijunqing �ܵĽӿ�CXSttSmartTestXInterface���������
class CSttSmartTestCom : public CXSttSmartTestXInterface, public CWnd
{
	DECLARE_DYNCREATE(CSttSmartTestCom)

public:
	static CSttSmartTestCom * CreateSmartTest()
	{
		CSttSmartTestCom *pSttSmartTestCom = new CSttSmartTestCom();
		pSttSmartTestCom->CreateWnd();
		pSttSmartTestCom->ShowWindow(SW_HIDE);
		return pSttSmartTestCom;
	}

public:
    CSttSmartTestCom();
    virtual ~CSttSmartTestCom();

	CXSmartTestClient *m_pXSmartTestClient;
	CDataGroup *m_pDevices;   //��¼����װ��  shaolei  20210.8.02
	
	void CreateWnd();
	void InitSmartTestCom();
	void ExitSmartTestCom();

	//shaolei 20210927
	//�������������ڼ�¼�ⲿϵͳ�ϴ��ı����ļ���ԭʼ��¼�ļ���ȫ·��
	//�����Զ����Խ������ȵ�������ı��棬����кϲ�����Ҫ���ļ������м�¼
	//�ϲ���������ռ�¼���ļ���
	CString m_strDocFile;
	CString m_strDocFileEx;

public:
	//���º���������0��ʾ�ɹ������ط���ֵ��ʾʧ��
    virtual long Ats_CreateTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_StartTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_StopTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_CloseTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_TestItem(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_TestFrom(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_TestAllFailedItems(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	//GetItemReport�����������Ա����豸Ϊ��λ���鿴ѡ��װ�õ�ĳ����Ŀ�ı���
    virtual long Ats_GetItemReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	//GetReportFile�����������Ա����豸Ϊ��λ����ȡѡ��װ�õı����ļ�
    virtual long Ats_GetReportFile(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
    virtual long Ats_GetSystemState(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	//FinishInputData����װ��ʱ��ÿ��װ�õ���һ��
    virtual long Ats_FinishInputData(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	//SetItemState�����������Ա����豸Ϊ��λ���趨ѡ��װ�õ�ĳ����Ŀ��״̬
    virtual long Ats_SetItemState(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	//InputData����װ��ʱ��ÿ��װ�õ���һ��
	virtual long Ats_InputData(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	//�Բ���̨Ϊ��λ���������б����豸�Ĳ��Ա���
	virtual long Ats_ExportReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	//SetItemsReport�����������Ա����豸Ϊ��λ������ѡ��װ�õ�ĳ����Ŀ�ı���
	virtual long Ats_SetItemsReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	//QueryItems�����������Ա����豸Ϊ��λ����ѯѡ��װ�õ�ĳ��������Ŀ
	virtual long Ats_QueryItems(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);

	virtual long Ats_ConfigTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	virtual long Ats_QueryTestParas(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	virtual long Ats_SetTestParas(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol);
	virtual long Ats_GenerateItems(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Ats_GenerateMacroTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Ats_SetItemPara(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Ats_ManualTrigger(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Ats_SaveTemplate(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Ats_SaveTest(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Ats_OpenTemplate(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Ats_OpenGbrptFile(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Ats_AdjustMainWnd(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Ats_UpdateItem(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Ats_AdjustReport(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual CString Ats_QueryItem(CXObjectRefDriver &oAtsCmdDrv, CSttProtocolInterface *pSttProtocol) {	return _T("");	}

	//shaolei 20210927
	virtual long Process_Cmd_Ats_Event_UploadFinish(CSttCmdBase* pSttCmdBase);

	virtual long Process_Cmd_SysState_ItemStateChanged(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Process_Cmd_SysState_TestFinished(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Process_Cmd_SysState_TestStarted(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol)  {	return 0;	}
	virtual long Process_Cmd_SysState_TestStoped(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Process_Cmd_SysState_OnReport(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}
	virtual long Process_Cmd_SysState_ExportReport(CXObjectRefDriver &oSysStateDrv, CSttProtocolInterface *pSttProtocol) {	return 0;	}

public:
	virtual long OnItemStateChanged(const CString& strDeviceID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString& strItemID, const CString& strState, long nSelect);
	virtual long OnTestFinished(const CString& strDeviceID, long nDeviceIndex, long nReportIndex);
	virtual long OnTestStoped(const CString& strDeviceID, long nDeviceIndex, long nReportIndex);
	virtual long OnExportRptEvent(const CString& strDeviceID, const CString &strEventID, long nDeviceIndex, long nReportIndex);
	virtual long OnTestAppEvent(const CString& strDeviceID, const CString& strEvent);
	virtual long OnEngineEvent(const CString& strDeviceID, long nDeviceIndex, const CString& strEvent);
	virtual long OnTestCreated(const CString& strDeviceID);
	virtual long OnOpenGbrptFileFailed(const CString& strDeviceID);
	virtual long OnTestProcess(const CString& strDeviceID, const CString& strTestID, long nTotalItems, long nCurrItem, long nTotalTime, long nRemainTime, const CString& strDeviceState);
	virtual long OnTestProcess(CExBaseList* pSttParas) {	return 0;	}
	virtual long OnReTestFinished(CExBaseList* pSttParas)  {	return 0;	}
	virtual long OnTestStarted(const CString& strDeviceID, long nDeviceIndex, long nReportIndex);
	virtual long OnUploadRptFile(const CString& strDeviceID, const CString &strFiles){	return 0;	}

	virtual long OnInputData(const CString& strDatas, const CString& strMsgs){	return 0;	}
	virtual long OnInputData(CExBaseList *pSttParas, CExBaseList *pSttMsgs){	return 0;	} //lijunqing 2022-6-27  ֱ�Ӵ������ݶ��󣬷��㴦�����ת��ΪXML����JSON�Ȳ�ͬ�ĸ�ʽ
	virtual long On_Ats_CreateTest(const CString &strGbrptFile)	{	return 0;	}  //shaolei 20220707  CreateTest��REPLY������gbrptfile��ȫ·��
	virtual long On_Ats_AdjustMainWnd(LONG nMainWnd)	{	return 0;	}  //shaolei 20220718  AdjustMainWnd��REPLY������SmartTest��MainWnd
public:
	virtual long ReturnSysState_REPLY(CSttProtocolInterface *pSttProtocol, CSttCmmOptrInterface *pCmmOptrInterface, long nCmdExecStatus, CSttCmdData *pRetData, char *pszEventID);
	virtual long ReturnSysState_EVENT(CSttProtocolInterface *pSttProtocol, CSttCmmOptrInterface *pCmmOptrInterface, CSttCmdData *pRetData, char *pszEventID);

	//2021-8-6  lijunqing
	virtual long ReturnSysState_REPORT(CSttProtocolInterface *pSttProtocol, CSttCmmOptrInterface *pCmmOptrInterface, CSttCmdData *pRetData);

	CDataGroup* GetReportFiles(const CString &strDeviceID);
	//��word��صĲ��� �ȷ�����ߣ�������Ҫ��װ
	MSWord::_Application m_WordApp;
	MSWord::_Application GetWordApp(BOOL bShow=FALSE);
	//ĿǰCWordRptEdit��ص��࣬������CGuideBookģ��
	BOOL wordOptr_ActiveWindow(MSWord::_Application	&oWordApp, const CString &strTitle);
	CString CombineWordFile(const CString &strFile1, const CString &strFile2, BOOL bToPdf = FALSE);
	//BOOL UploadAllRptFiles(CDataGroup* pFiles);
private:
	void word_close_doc(MSWord::_Document &oDoc, MSWord::_Document &oDoc2);
	BOOL word_insert_doc_bkmk(MSWord::_Document &oDoc, MSWord::_Document &oDoc2, const CString &strFile1, const CString &strFile2);
	BOOL word_insert_doc_tail(MSWord::_Document &oDoc, MSWord::_Document &oDoc2, const CString &strFile1, const CString &strFile2);

public:
	BOOL DownLoadAllFiles(CSttAtsCmd *pAtsCmd);
	BOOL DownLoadFiles_Devices(CDataGroup *pDevices);  //����ģ���ļ��͹�Լģ��
	BOOL DownLoadFiles_TestApps(CDataGroup *pTestApps);  //���ز����������ļ�
};
