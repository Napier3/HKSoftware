#include "stdafx.h"
#include "TestControlSdvMpp.h"
#include "TestControlWnd.h"
#include "../TCtrlCntrWorkSpace.h"
#include "TCtrlCntrBaseApp.h"
#include "../GuideBook\Script/GbScript_GlobalDefine.h"
#include "..\..\..\Module\KeyDb\XMatchToolBase.h"
#include <math.h>

#include "../XRecorderDlg.h"
#include "..\..\..\Module\EpotoInterface\EpotoInterface.h"
#include "..\..\..\Module\DataMngr\DatasetValid\DsvViewResultDialog.h"

#include "../XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CTestControlSdvMpp
CTestControlSdvMpp::CTestControlSdvMpp()
{
	m_pCurrTestControl = NULL;
}

CTestControlSdvMpp::~CTestControlSdvMpp()
{
	
}

long CTestControlSdvMpp::TestItemCommCmdEx(CCommCmd* pItem)
{
	CTestControl *pTestCtrol = GetTestControl(pItem);
	ASSERT (pTestCtrol != NULL);

	if (pTestCtrol == this)
	{
		return CTestControl::TestItemCommCmdEx(pItem);
	}
	else
	{
		return pTestCtrol->TestItemCommCmdEx(pItem);
	}
}

BOOL CTestControlSdvMpp::ProcessAfterCommCmdFinish(CCommCmd *pCommCmd)
{
	return FALSE;
}

BOOL CTestControlSdvMpp::IsMutexWriteCmd(CCommCmd* pItem)
{
	CGbCommCmdMms *pGbCmd = pItem->GetGbCommCmd();

	if (pGbCmd->m_strGbRwOptr != g_strDeviceModelOptr_Write)
	{
		return FALSE;
	}

	if (pGbCmd->m_strGbDataID == g_strDataSetID[DSID_dsEna])
	{
		return TRUE;
	}

	if (pGbCmd->m_strGbDataID == g_strDataSetID[DSID_dsParameter])
	{
		return TRUE;
	}

	if (pGbCmd->m_strGbDataID == g_strDataSetID[DSID_dsSetting])
	{
		return TRUE;
	}

	if (pGbCmd->m_strGbDataID == g_strDataSetID[DSID_dsDout])
	{
		return TRUE;
	}

	return FALSE;
}

void CTestControlSdvMpp::AddReportToChildren(CCommCmd* pItem)
{
	POS pos = GetHeadPosition();
	CTestControl *pTestControl = NULL;
	CReport *pReport = pItem->GetReport(-1);
	CCommCmd *pDestItem = NULL;
	CDataSet *pDataset = GetDataset(pItem);
	CDataSet *pDestDataset = NULL;
	CReports *pReports = NULL;

	while (pos != NULL)
	{
		pTestControl = (CTestControl *)GetNext(pos);
		pDestItem = (CCommCmd*)GetItem(pTestControl->m_pGuideBook, pItem);
	
		ASSERT (pDestItem != NULL);	

		//pReports = pDestItem->GetReports();
		//pReports->AddNewChild((CExBaseObject *)pReport->Clone());
		CReport *pDestReport = pDestItem->GetReport(-1);
		pDestReport->m_pValues->DeleteAll();
		pReport->m_pValues->CopyChildren(pDestReport->m_pValues);

		pDestDataset = pTestControl->GetDataset(pDestItem);

		if (pDestDataset != NULL)
		{
			pDestDataset->InitValueByDataset(pDataset);
		}

		pTestControl->ProcessFinishCommCmdAfter(pDestItem, pReport);
		pTestControl->m_oTCtrlMsgRcv.OnCurrItemStateChanged(pDestItem);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_TestCpntCopy/*_T("        [%s]:[%s]�������(���Ʊ���)")*/, pTestControl->GetGbBinaryFileName(), pDestItem->m_strName);
	}
}

void CTestControlSdvMpp::ExcuteCommCmdOnDelayAfterFinish(CCommCmd* pItem)
{
	CGuideBook *pGuideBook = (CGuideBook *)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();

	ASSERT (m_pCurrTestControl == pTestControl);

	if (pTestControl == this)
	{
		CTestControl::ExcuteCommCmdOnDelayAfterFinish(pItem);
	}
	else
	{
		m_pCurrTestControl->CTestControl::ExcuteCommCmdOnDelayAfterFinish(pItem);
	}

	BOOL bTestFinish = FALSE;
	//������޸Ķ�ֵ���޸�ѹ�塢�޸�װ�ò������л���ֵ����ң�ء���λ���޸���ѹ��(����)��RriteDout
	//��ֻ����ף��ͼ��ͨѶ����ӱ���ʹ������������ͬ������
	if (IsMutexWriteCmd(pItem))
	{
		bTestFinish = TRUE;
		AddReportToChildren(pItem);
	}

	//���һ��
	if (m_pCurrTestControl == GetTail())
	{
		bTestFinish = TRUE;
	}

	if (bTestFinish)
	{
		m_pTCtrlWnd->m_pTestControl = this;
		CGbItemBase *pMainItem = (CGbItemBase*)GetItem(m_pGuideBook, pItem);

		if (pMainItem->m_bIsSubItem)
		{
			if (m_pCurrSubTestItem == NULL)
			{
				TestNextItem();
			}
			else
			{
				TestNextSubItem(m_pCurrSubTestItem);
			}
		}
		else
		{
			TestNextItem();
		}
	}
	else
	{
		if (m_pCurrTestControl == this)
		{
			pTestControl = (CTestControl *)GetHead();
		}
		else
		{
			long nIndex = FindIndex(m_pCurrTestControl) + 1;
			pTestControl = (CTestControl*)GetAt(nIndex);
		}

		m_pCurrTestControl = pTestControl;
		m_pTCtrlWnd->m_pTestControl = m_pCurrTestControl;

		if (g_nLog_TestControl_Msg == 1)
		{
			CString strPath1 = Gb_GetItemPath(pItem);//pItem->GetIDPathEx(GBCLASSID_GUIDEBOOK, FALSE);
			pItem = (CCommCmd*)GetItem(pTestControl->m_pGuideBook, pItem);
			CString strPath2 = Gb_GetItemPath(pItem);//pItem->GetIDPathEx(GBCLASSID_GUIDEBOOK, FALSE);
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_SngDevMulPrtc/*_T("��װ�ö��Լ-·��1��%s")*/, strPath1);
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_SngDevMulPrtc2/*_T("��װ�ö��Լ-·��2��%s")*/, strPath2);
		}
		else
		{
			pItem = (CCommCmd*)GetItem(pTestControl->m_pGuideBook, pItem);
		}
	
		//����������Ŀ״̬�ı���Ϣ
		pItem->SetState(TEST_STATE_TESTING);
		pTestControl->m_oTCtrlMsgRcv.OnCurrItemStateChanged(pItem);
		pTestControl->TestItemCommCmdEx(pItem);
	}
}

void CTestControlSdvMpp::CreatePpEngineDevice(CProtocolEngineInterface* &pEngine, CPpDeviceRef *pDevieceRef)
{
	CTestControl::CreatePpEngineDevice(pEngine, pDevieceRef);
}


CPpDeviceRef* CTestControlSdvMpp::FindPpDeviceRef(WPARAM wParam)
{
	return (CPpDeviceRef*)m_oDeviceRefs.GetHead();
}


CProtocolDeviceInterface* CTestControlSdvMpp::FindPpDevice(WPARAM wParam)
{
	CPpDeviceRef *p = (CPpDeviceRef*)m_oDeviceRefs.GetHead();
	CProtocolDeviceInterface* oPpDevice = NULL;

	if (p != NULL)
	{
		oPpDevice = p->m_oPpDevice;
	}

	return oPpDevice;
}

long CTestControlSdvMpp::GetDelayBeforeCmd(CCommCmd* pItem)
{
	CGuideBook *pGuideBook = (CGuideBook *)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();

	ASSERT (m_pCurrTestControl == pTestControl);

	//�����Զ����ͨѶ�������ͨѶǰ��ʱ
	if (pTestControl == this)
	{
// 		CCmd *pCmd = pItem->GetCmd();
// 		return pCmd->GetDelayBeforeCmd();
		return CTestControl::GetDelayBeforeCmd(pItem);
	}
	else
	{
		//�Ӷ����ͨѶ���������ͨѶǰ��ʱ
		return 0;
		//m_pCurrTestControl->CTestControl::ExcuteCommCmdOnDelayAfterFinish(pItem);
	}

}

long CTestControlSdvMpp::GetDelayAfterCmd(CCommCmd* pItem)
{
	CGuideBook *pGuideBook = (CGuideBook *)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	CTestControl *pTestControl = (CTestControl*)pGuideBook->GetParent();
	CTestControl *pTail = (CTestControl*)GetTail();

	ASSERT (m_pCurrTestControl == pTestControl);

	//�����Զ����ͨѶ�������ͨѶ����ʱ
	if (pTestControl == pTail)
	{
		return CTestControl::GetDelayAfterCmd(pItem);
	}
	else
	{
		if (IsMutexWriteCmd(pItem))
		{
			return CTestControl::GetDelayAfterCmd(pItem);
		}
		else
		{
			//�Ӷ����ͨѶ���������ͨѶ����ʱ
			return 0;
		}
	}
}
