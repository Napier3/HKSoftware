#include "stdafx.h"
#include "SttAssistWzd_MuTest.h"
#include "../../UI/SttTestCntrCmdDefine.h" 
#include "../../UI/SttTestCntrFrameBase.h" 
#include "../../RecordTest/UI/SttIecRecordCbWidget.h"
#include "../../RecordTest/UI/SttIecRecordDetectWidget.h"
#include "../../RecordTest/UI/MUTest/SttMUTestIecCbSelWidget.h"
#include "../../SttSystemConfig/SttSystemConfig.h"

#include "../DynEffect/SttAssistShowTips.h"
#include "SttAssistIecCbSelWidget.h"
#include "../DynEffect/SttAssistWndDynEffExecTool.h"

QSttAssistIecCbSelWidget *g_pSttAssistIecCbSelWidget = NULL;


CSttAssistWzd_MuTest::CSttAssistWzd_MuTest()
{
	
}


CSttAssistWzd_MuTest::~CSttAssistWzd_MuTest()
{
#ifdef STT_MUTest_CBSelect_USE_Assist
	if (g_pSttAssistIecCbSelWidget != NULL)
	{
		g_pSttAssistIecCbSelWidget->deleteLater();
		g_pSttAssistIecCbSelWidget = NULL;
	}
#else
	if (g_pSttMUTestIecCbSelWidget != NULL)
	{
		delete g_pSttMUTestIecCbSelWidget;
		g_pSttMUTestIecCbSelWidget = NULL;
	}
#endif
}

void CSttAssistWzd_MuTest::assist_init()
{
	//��ʼ�����ڴ�����̽�⹦��
	g_theTestCntrFrame->InitIecCapTest(false, true);
	g_pSttIecRecordCbWidget->SetMUTestMode(true);
	g_theAssistWndDynEffExecTool->ShowMsgEx("AstSttIecCbGrid", "�ڿ��ƿ�����ѡ������Ŀ��ƿ�", 5000);
}

void CSttAssistWzd_MuTest::assist_wnd_show(const CString &strWndID, CSttAssistWzd_MuTest *pWnd, bool bShow)
{
	
}

void CSttAssistWzd_MuTest::assist_ui_msg(const CString &strUiMsgID, CDataGroup *pDatas)
{
	
}

void CSttAssistWzd_MuTest::assist_data_change(const CString &strWndID, const CString &strDataID, const CString &strValue)
{
	
}

bool CSttAssistWzd_MuTest::assist_event(const CString &strEventID, CExBaseObject *pSttParas)
{
	if (strEventID == STT_CNTR_CMD_StartTest)
	{
		return Event_StartTest(pSttParas);
	}
	else if (strEventID == Event_ID_IecAddCb)
	{
		return Event_IecAddCb(pSttParas);
	}
	else if (strEventID == Event_ID_OnTestStarted)
	{
		return Event_OnTestStarted(pSttParas);
	}
	else if (strEventID == Event_ID_OnTestFinished)
	{
		return Event_OnTestFinished(pSttParas);
	}
	else if (strEventID == Event_ID_IecSelCb)
	{

	}
	
	return true;
}

/*
���û��������ƿ飬��ʾû��̽�⵽���ƿ�
����Ѿ�ѡ��Ψһ�Ŀ��ƿ飬�򷵻�true
���ֻ��һ�����ƿ飬����û��ѡ����ƿ飬�Զ�ѡ��
����ж�����ƿ飬����û��ѡ����ƿ飬�򵯿����ѡ����ƿ�
*/
bool CSttAssistWzd_MuTest::Event_StartTest(CExBaseObject *pSttParas)
{
	if (! g_oSttTestResourceMngr.HasContrlBlockSelected_IecConfig())
	{
// 		QMessageBox msgBox;
// 		CString strTmp;
// 		strTmp = "ѡ����ƿ�";
// 		msgBox.setText(strTmp);
// 		msgBox.exec();

		Event_IecSelCb(NULL);

		return false;
	}
	
	//g_theTestCntrFrame->ast_ExecCmd(Event_ID_IecSelCb, _T("ReportView"));

	return true;
}

bool CSttAssistWzd_MuTest::Event_IecAddCb(CExBaseObject *pSttParas)
{
	//2023.9.14 ����ԭ�е����ַ�ʽ���ƿ�ѡ��,����ʹ���µ�ˢ�µķ�ʽ
#ifdef STT_MUTest_CBSelect_USE_Assist
	if (g_pSttAssistIecCbSelWidget == NULL)
	{
		g_pSttAssistIecCbSelWidget = new QSttAssistIecCbSelWidget();

		if (g_pSttIecRecordDetectWidget != NULL)
		{
			g_pSttMUTestIecCbSelWidget->m_pGridIecCb_CBSel->m_bViewSmv = g_pSttIecRecordDetectWidget->m_pGridIecCb->m_bViewSmv;
			g_pSttMUTestIecCbSelWidget->m_pGridIecCb_CBSel->m_bViewGoose = g_pSttIecRecordDetectWidget->m_pGridIecCb->m_bViewGoose;
			g_pSttMUTestIecCbSelWidget->m_pGridIecCb_CBSel->m_bViewFT3 = g_pSttIecRecordDetectWidget->m_pGridIecCb->m_bViewFT3;
		}

		g_pSttAssistIecCbSelWidget->show();
	}

	g_pSttAssistIecCbSelWidget->ShowAllCapDevice();
#else

	if (g_pSttMUTestIecCbSelWidget == NULL)
	{
		g_pSttMUTestIecCbSelWidget = new QSttMUTestIecCbSelWidget();

		if (g_pSttIecRecordDetectWidget != NULL)
		{
			g_pSttMUTestIecCbSelWidget->m_pGridIecCb_CBSel->m_bViewSmv = g_pSttIecRecordDetectWidget->m_pGridIecCb->m_bViewSmv;
			g_pSttMUTestIecCbSelWidget->m_pGridIecCb_CBSel->m_bViewGoose = g_pSttIecRecordDetectWidget->m_pGridIecCb->m_bViewGoose;
			g_pSttMUTestIecCbSelWidget->m_pGridIecCb_CBSel->m_bViewFT3 = g_pSttIecRecordDetectWidget->m_pGridIecCb->m_bViewFT3;
			g_pSttMUTestIecCbSelWidget->ShowAllCapDevice();//zhouhj 2024.4.9 �����ʾ���ݸ��º�,������ع��ܴ���
		}

		g_pSttMUTestIecCbSelWidget->show();
		g_pSttMUTestIecCbSelWidget->Refresh_MUTest();
	}

#endif

	return true;
}

bool CSttAssistWzd_MuTest::Event_OnTestStarted(CExBaseObject *pSttParas)
{
// 	QMessageBox msgBox;
// 	CString strTmp;
// 	strTmp = "���Կ�ʼ";
// 	msgBox.setText(strTmp);
// 	msgBox.exec();

//	g_theTestCntrFrame->ast_ExecCmd("MenuCmd", _T("ReportView"));
	CSttDevConfig* pSttDevConfig = g_oSttSystemConfig.GetSttDevConfig();

	if (pSttDevConfig->m_nMultiExpList == 1)
	{
		if (g_theTestCntrFrame->IsMultiTestItems())
		{
			if (g_theTestCntrFrame->m_pSttGbTreeView->isHidden())
			{
				g_theTestCntrFrame->SendMenuButtonClick(STT_CNTR_CMD_ItemList);
			}
		}
	}
	return true;
}

bool CSttAssistWzd_MuTest::Event_OnTestFinished(CExBaseObject *pSttParas)
{
// 	QMessageBox msgBox;
// 	CString strTmp;
// 	strTmp = "���Խ���";
// 	msgBox.setText(strTmp);
// 	msgBox.exec();

//	g_theTestCntrFrame->ast_ExecCmd("MenuCmd", _T("ReportView"));
	if (g_theTestCntrFrame->IsMultiTestItems())
	{
		if (!g_theTestCntrFrame->m_pSttGbTreeView->isHidden())
		{
			g_theTestCntrFrame->SendMenuButtonClick(STT_CNTR_CMD_ItemList);
		}
	}
	return true;
}

bool CSttAssistWzd_MuTest::Event_IecSelCb(CExBaseObject *pSttParas)
{
	return true;
}


