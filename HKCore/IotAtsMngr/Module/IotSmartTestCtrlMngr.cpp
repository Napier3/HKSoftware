#include "stdafx.h"
#include "IotSmartTestCtrlMngr.h"


CIotSmartTestCtrlMngr::CIotSmartTestCtrlMngr()
{
	
}

CIotSmartTestCtrlMngr::~CIotSmartTestCtrlMngr()
{
	
}

/************************
�Զ��������⣺
"����̨SN/XML/AtsCmd/+";
"����̨SN/����װ��SN/XML/AtsCmd/FinishInputData";
"����̨SN/����װ��SN/XML/AtsState/InputData/Reply"
**************************/
void CIotSmartTestCtrlMngr::OnMqttMsgRecieve(const CString &strTopic,char *pBuf,long nLen)
{
	//��������
	CStringTokenizer oToken;
	oToken.Init(strTopic, '/');

	long nPathCnt = oToken.GetStringsCount();
	CString strTestID = oToken.GetToken(0);
	CString strCmd = oToken.GetToken(nPathCnt-1);

	CIotSmartTestCtrl *pSmartTestCtrl = (CIotSmartTestCtrl *)FindByID(strTestID);

	if (strCmd == STT_CMD_TYPE_ATS_CreateTest)
	{//��������
		if (pSmartTestCtrl != NULL)
		{
			delete pSmartTestCtrl;
		}

		pSmartTestCtrl = new CIotSmartTestCtrl;
		pSmartTestCtrl->m_strID = strTestID;
		AddNewChild(pSmartTestCtrl);
	}
	else if (pSmartTestCtrl == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnMqttMsgRecieve:����[%s]��pSmartTestCtrl == NULL��"),strTopic);
		return;
	}

	pSmartTestCtrl->OnMqttMsgRecieve(oToken,pBuf,nLen);
}

//��������Ҫ�����Զ���������
/***************************
���ģ�
	����̨SN/XML/AtsCmd/CreateTest
������
	����̨SN/XML/AtsState/CreateTest/Reply
	����̨SN/XML/AtsState/EVENT/TestCreated

���ģ�
	����̨SN/XML/AtsCmd/StartTest
������
	����̨SN/XML/AtsState/StartTest/Reply
	����̨SN/XML/AtsState/EVENT/TestStarted

���ģ�
	����̨SN/XML/AtsCmd/StopTest
������
	����̨SN/XML/AtsState/StopTest/Reply
	����̨SN/XML/AtsState/EVENT/TestStoped

���ģ�
	����̨SN/XML/AtsCmd/TestItem
������
	����̨SN/XML/AtsState/TestItem/Reply

���ģ�
	����̨SN/XML/AtsCmd/TestFrom
������
	����̨SN/XML/AtsState/TestFrom/Reply

���ģ�
	����̨SN/XML/AtsCmd/TestAllFailedItems
������
	����̨SN/XML/AtsState/TestAllFailedItems/Reply

���ģ�
	����̨SN/XML/AtsCmd/SetItemState
������
	����̨SN/XML/AtsState/SetItemState/Reply

���ģ�
	����̨SN/XML/AtsCmd/CreateDevice
������
	����̨SN/XML/AtsState/CreateDevice/Reply

���ģ�
	����̨SN/XML/AtsCmd/ConfigDevice
������
	����̨SN/XML/AtsState/ConfigDevice/Reply

���ģ�
	����̨SN/XML/AtsCmd/ConnectDevice
������
	����̨SN/XML/AtsState/ConnectDevice/Reply
	����̨SN/XML/AtsState/EVENT/EngineEvent/�¼�ID

���ģ�
	����̨SN/XML/AtsCmd/CloseDevice
������
	����̨SN/XML/AtsState/CloseDevice/Reply
	����̨SN/XML/AtsState/EVENT/EngineEvent/DeviceClosed

���ģ�
	����̨SN/XML/AtsCmd/ConfigEngine
������
	����̨SN/XML/AtsState/ConfigEngine/Reply

���ģ�
	����̨SN/XML/AtsCmd/GetDataset
������
	����̨SN/XML/AtsState/GetDataset/Reply

���ģ�
	����̨SN/XML/AtsCmd/SetDataset
������
	����̨SN/XML/AtsState/SetDataset/Reply

���ģ�
	����̨SN/XML/AtsCmd/RunProcedure
������
	����̨SN/XML/AtsState/RunProcedure/Reply
	����̨SN/XML/AtsState/EVENT/EngineEvent/�¼�ID

���ģ�
	����̨SN/XML/AtsCmd/QueryAtsFile
������
	����̨SN/XML/AtsState/QueryAtsFile/Reply

������
	����̨SN/����װ��SN/XML/AtsCmd/InputData
���ģ�
	����̨SN/����װ��SN/XML/AtsState/InputData/Reply

���ģ�
	����̨SN/����װ��SN/XML/AtsCmd/FinishInputData
������
	����̨SN/����װ��SN/XML/AtsState/FinishInputData/Reply

���ģ�
	����̨SN/XML/AtsCmd/ExportReport
������
	����̨SN/XML/AtsState/ExportReport/Reply
	����̨SN/XML/AtsState/EVENT/ExportBegin|ExportFinish

���ģ�
	����̨SN/XML/AtsCmd/QueryItems
������
	����̨SN/XML/AtsState/QueryItems/Reply

���ģ�
	����̨SN/XML/AtsCmd/SetItemsReport
������
	����̨SN/XML/AtsState/SetItemsReport/Reply

���ģ�
	����̨SN/XML/AtsCmd/ConfigTest
������
	����̨SN/XML/AtsState/ConfigTest/Reply

�����¼���
	����̨SN/����װ��SN/XML/AtsState/EVENT/ItemStateChanged
	����̨SN/����װ��SN/XML/AtsState/EVENT/Report
	����̨SN/XML/AtsState/EVENT/TestFinished
	����̨SN/XML/AtsState/EVENT/TestProcess
	����̨SN/XML/AtsState/EVENT/EngineEvent/�¼�ID
	����̨SN/XML/AtsState/EVENT/TestAppEvent/�¼�ID
***************************/
BOOL CIotSmartTestCtrlMngr::SubcribeMqttAtsTopic(int nQos)
{
	/*************************************
	�趩���Զ��������⣺
	����̨SN/XML/AtsCmd/CreateTest
	����̨SN/XML/AtsCmd/StartTest
	����̨SN/XML/AtsCmd/StopTest
	����̨SN/XML/AtsCmd/TestItem
	����̨SN/XML/AtsCmd/TestFrom
	����̨SN/XML/AtsCmd/TestAllFailedItems
	����̨SN/XML/AtsCmd/SetItemState
	����̨SN/XML/AtsCmd/CreateDevice
	����̨SN/XML/AtsCmd/ConfigDevice
	����̨SN/XML/AtsCmd/ConnectDevice
	����̨SN/XML/AtsCmd/CloseDevice
	����̨SN/XML/AtsCmd/ConfigEngine
	����̨SN/XML/AtsCmd/GetDataset
	����̨SN/XML/AtsCmd/SetDataset
	����̨SN/XML/AtsCmd/RunProcedure
	����̨SN/XML/AtsCmd/QueryAtsFile
	����̨SN/XML/AtsCmd/ExportReport
	����̨SN/XML/AtsCmd/QueryItems
	����̨SN/XML/AtsCmd/SetItemsReport
	����̨SN/XML/AtsCmd/ConfigTest

	����̨SN/����װ��SN/XML/AtsCmd/FinishInputData
	����̨SN/����װ��SN/XML/AtsState/InputData/Reply
	*********************************/

	CSttMqttClientTool::SubscribeTopic(_T("+/+/AtsCmd/+"),nQos);
	CSttMqttClientTool::SubscribeTopic(_T("+/+/+/AtsCmd/FinishInputData"),nQos);
	CSttMqttClientTool::SubscribeTopic(_T("+/+/+/AtsState/InputData/Reply"),nQos);

	return TRUE;
}

//�¼�����ӿ�
long CIotSmartTestCtrlMngr::TES_OnItemStateChanged(LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex
												, LONG nItemIndex, LPCTSTR strItemID, LPCTSTR strState)
{
	CIotSmartTestCtrl *pSmartTestCtrl = (CIotSmartTestCtrl *)FindByID(strTestID);
	if (pSmartTestCtrl == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("TES_OnItemStateChanged:[%s]��pSmartTestCtrl == NULL��"),strTestID);
		return 1;
	}

	return pSmartTestCtrl->TES_OnItemStateChanged(nDeviceIndex, nReportIndex
													, nItemIndex,strItemID, strState);
}

long CIotSmartTestCtrlMngr::TES_OnTestFinished(LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex)
{
	CIotSmartTestCtrl *pSmartTestCtrl = (CIotSmartTestCtrl *)FindByID(strTestID);
	if (pSmartTestCtrl == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("TES_OnTestFinished:[%s]��pSmartTestCtrl == NULL��"),strTestID);
		return 1;
	}

	return pSmartTestCtrl->TES_OnTestFinished(nDeviceIndex, nReportIndex);
}

long CIotSmartTestCtrlMngr::TES_OnTestStoped(LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex)
{
	CIotSmartTestCtrl *pSmartTestCtrl = (CIotSmartTestCtrl *)FindByID(strTestID);
	if (pSmartTestCtrl == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("TES_OnTestStoped:[%s]��pSmartTestCtrl == NULL��"),strTestID);
		return 1;
	}

	return pSmartTestCtrl->TES_OnTestStoped(nDeviceIndex, nReportIndex);
}

long CIotSmartTestCtrlMngr::TES_OnExportRptFinished(LPCTSTR strTestID, LONG nDeviceIndex, LONG nReportIndex)
{
	CIotSmartTestCtrl *pSmartTestCtrl = (CIotSmartTestCtrl *)FindByID(strTestID);
	if (pSmartTestCtrl == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("TES_OnExportRptFinished:[%s]��pSmartTestCtrl == NULL��"),strTestID);
		return 1;
	}

	return pSmartTestCtrl->TES_OnExportRptFinished(nDeviceIndex, nReportIndex);
}

long CIotSmartTestCtrlMngr::TES_OnTestAppEvent(LPCTSTR strTestID, LPCTSTR strEvent)
{
	CIotSmartTestCtrl *pSmartTestCtrl = (CIotSmartTestCtrl *)FindByID(strTestID);
	if (pSmartTestCtrl == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("TES_OnTestAppEvent:[%s]��pSmartTestCtrl == NULL��"),strTestID);
		return 1;
	}

	return pSmartTestCtrl->TES_OnTestAppEvent(strEvent);
}

long CIotSmartTestCtrlMngr::TES_OnEngineEvent(LPCTSTR strTestID, LONG nDeviceIndex, LPCTSTR strEvent)
{
	CIotSmartTestCtrl *pSmartTestCtrl = (CIotSmartTestCtrl *)FindByID(strTestID);
	if (pSmartTestCtrl == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("TES_OnEngineEvent:[%s]��pSmartTestCtrl == NULL��"),strTestID);
		return 1;
	}

	return pSmartTestCtrl->TES_OnEngineEvent(nDeviceIndex,strEvent);
}

long CIotSmartTestCtrlMngr::TES_OnTestCreated(LPCTSTR strTestID)
{
	CIotSmartTestCtrl *pSmartTestCtrl = (CIotSmartTestCtrl *)FindByID(strTestID);
	if (pSmartTestCtrl == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("TES_OnTestCreated:[%s]��pSmartTestCtrl == NULL��"),strTestID);
		return 1;
	}

	return pSmartTestCtrl->TES_OnTestCreated();
}

long CIotSmartTestCtrlMngr::TES_OnOpenGbrptFileFailed(LPCTSTR strTestID)
{
	CIotSmartTestCtrl *pSmartTestCtrl = (CIotSmartTestCtrl *)FindByID(strTestID);
	if (pSmartTestCtrl == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("TES_OnOpenGbrptFileFailed:[%s]��pSmartTestCtrl == NULL��"),strTestID);
		return 1;
	}

	return pSmartTestCtrl->TES_OnOpenGbrptFileFailed();
}
