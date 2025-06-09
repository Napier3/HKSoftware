// CmsEngineAppWnd.cpp
//

#include "stdafx.h"
#include "DltEngineAppBase.h"
#include "CmsEngineAppWnd.h"

#include "../MmsGlobal.h"
#include "../MmsWriteXml.h"
#include "../../../Module/API/FileApi.h"
#include "../../../Module/System/TickCount32.h"
#include "PoCmsDevice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCmsEngineAppWnd

CCmsEngineAppWnd::CCmsEngineAppWnd()
{
	m_nCallFuncRetryTimes = 0;
}

CCmsEngineAppWnd::~CCmsEngineAppWnd()
{
	
}

void CCmsEngineAppWnd::PostDeviceCommCmdMessage(WPARAM wParam, LPARAM lParam)
{
	CFuncParamEx *pFuncParaEx = (CFuncParamEx*) wParam;
	LONG nFuncID = pFuncParaEx-> get_FuncID();

	ACSI_NODE *pACSI_NODE =theCmsApp->GetAcsiNode(pFuncParaEx->get_DevIndex());
	CPoMmsDevice *pMmsDevice = (CPoMmsDevice*)pACSI_NODE->pRefDevice;

	if (pACSI_NODE->nWriteErrorCount > 0)
	{
		pACSI_NODE->nWriteErrorCount = 0;
		PostDeviceSysMessage(pFuncParaEx->get_DevIndex() ,engineCommError);
		return;
	}
	else
	{
		if (pMmsDevice != NULL)
		{
			pMmsDevice->mms_PostDeviceCommCmdMessage(pACSI_NODE, nFuncID, lParam);
		}
	}
}

void CCmsEngineAppWnd::PostDeviceSysMessage(WPARAM wParam, LPARAM lParam)
{
	int nDeviceIndex = wParam;

	ACSI_NODE *pACSI_NODE =theCmsApp->GetAcsiNode(nDeviceIndex);
	CPoMmsDevice *pMmsDevice = (CPoMmsDevice*)pACSI_NODE->pRefDevice;

	if (pMmsDevice != NULL)
	{
		pMmsDevice->mms_PostDeviceSysMessage(pACSI_NODE, wParam, lParam);
	}
}

LRESULT CCmsEngineAppWnd::OnMmsCmdFinish_View(WPARAM wParam,LPARAM lParam)
{
	CFuncParamEx *pFuncParaEx = (CFuncParamEx*) wParam;
	CString strMsg;
	BOOL bIsClientCmd = pFuncParaEx->is_ClientCmd();
	LONG nFuncID = pFuncParaEx-> get_FuncID();
	ACSI_NODE *pDevice =theCmsApp->GetAcsiNode(pFuncParaEx->get_DevIndex());

	switch(nFuncID)
	{
	case FuncID_Link:
		if (lParam==SD_SUCCESS)
		{
			strMsg.Format(_T("��װ��%d�����ɹ�."),pFuncParaEx->get_DevIndex());
		}
		else
		{
			strMsg.Format(_T("��װ��%d����ʧ�ܡ�Error��."),pFuncParaEx->get_DevIndex());
		}

		mms_UpdateDeviceState(pDevice);

		break;

	case FuncID_UnLink:
		if (lParam==SD_SUCCESS)
		{
			strMsg.Format(_T("��װ��%d�Ͽ����ӳɹ�."),pFuncParaEx->get_DevIndex());
		}
		else
		{
			strMsg.Format(_T("��װ��%d�Ͽ�����ʧ�ܡ�Error��."),pFuncParaEx->get_DevIndex());
		}

		pDevice->bConnect = FALSE;
		mms_UpdateDeviceState(pDevice);

		break;

	case FuncID_Read:
	case FuncID_Read_SET:
		if (lParam==SD_SUCCESS)
		{
			strMsg.Format(_T("��ȡװ��%d���ݼ��ɹ�."),pFuncParaEx->get_DevIndex());
		}
		else
		{
			strMsg.Format(_T("��ȡװ��%d���ݼ�ʧ�ܡ�Error��."),pFuncParaEx->get_DevIndex());
		}

		//		ResetWriteFailErrorCode();//�ڶ�ȡ���ݲ����󣬽�дʧ�ܵ�ԭ����ֵ����Ϊ-1 ��Ϊԭ����ֵ����Ϊ0���˴�����Ϊ-1Ϊ����ֵ
		break;

	case FuncID_ReadDir:
		if (lParam==SD_SUCCESS)
		{
			PXMMS_FILE_SYS_OBJ pFileDir = &pDevice->FileDir;

			if (pFileDir->readfailed == 1)
			{
				strMsg.Format(_T("��ȡװ��%d¼���ļ�Ŀ¼ʧ��."),pFuncParaEx->get_DevIndex());
			}
			else
			{
				//strMsg.Format(_T("��ȡװ��%d¼���ļ�Ŀ¼�ɹ�."),pFuncParaEx->get_DevIndex());
			}
		}
		else
		{
			strMsg.Format(_T("��ȡװ��%d¼���ļ�Ŀ¼ʧ��."),pFuncParaEx->get_DevIndex());
		}
		break;
	case FuncID_ReadRPC:

		if (lParam==SD_SUCCESS)
		{
			strMsg.Format(_T("��ȡװ��%dԶ�̵���RPC�����ɹ�."),pFuncParaEx->get_DevIndex());
		}
		else
		{
			strMsg.Format(_T("��ȡװ��%dԶ�̵���RPC����ʧ��."),pFuncParaEx->get_DevIndex());
		}

		break;
	case FuncID_RpcCall:

		if (lParam==SD_SUCCESS)
		{
			strMsg.Format(_T("��ȡװ��%dԶ�̵���RpcCall�ɹ�."),pFuncParaEx->get_DevIndex());
		}
		else
		{
			strMsg.Format(_T("��ȡװ��%dԶ�̵���RpcCallʧ��."),pFuncParaEx->get_DevIndex());
		}

		break;
	case FuncID_ReadFile:
		if (lParam==SD_SUCCESS)
		{
			strMsg.Format(_T("��ȡװ��%d¼���ļ��ɹ�."),pFuncParaEx->get_DevIndex());
		}
		else
		{
			strMsg.Format(_T("��ȡװ��%d¼���ļ�ʧ��."),pFuncParaEx->get_DevIndex());
		}
		break;

	case FuncID_Write:
		if (lParam!=SD_SUCCESS)
		{
			//theMmsApi->OutputPrintMsg(g_sLangTxt_WriteDataFail);//"д����ʧ�ܡ�Error��.");
		}
		else
		{
			//theMmsApi->OutputPrintMsg(g_sLangTxt_WriteDataSucc);//"д���ݳɹ�.");
		}
		break;
	case FuncID_StartRpt:
		if (lParam!=SD_SUCCESS)
		{
			//theMmsApi->OutputPrintMsg(g_sLangTxt_StartRptFail);//"��������ʧ�ܡ�Error��.");
		}
		else
		{
			//theMmsApi->OutputPrintMsg(g_sLangTxt_StartRptSucc);//"��������ɹ�.");
		}

		theCmsApp->SetReportRet(pFuncParaEx,lParam==SD_SUCCESS, TRUE);
		break;
	case FuncID_StopRpt:
		if (lParam!=SD_SUCCESS)
		{
			//theMmsApi->OutputPrintMsg(g_sLangTxt_StopRptFail);//"ֹͣ����ʧ�ܡ�Error��.");
		}
		else
		{
			//theMmsApi->OutputPrintMsg(g_sLangTxt_StopRptSucc);//"ֹͣ����ɹ�.");
		}

		theCmsApp->SetReportRet(pFuncParaEx,lParam==SD_SUCCESS, FALSE);
		break;
	case FuncID_GetSGNum:
		if (lParam!=SD_SUCCESS)
		{
			//theMmsApi->OutputPrintMsg(g_sLangTxt_ReadZoneFail);//"��ȡ��ǰ��ֵ��������ʧ��.");
		}
		else
		{
			ST_INT nSGNum = pFuncParaEx->get_SGNum();
			ST_INT nSGID = pFuncParaEx->get_SGID();

			CString strText = "";
			strText.Format(_T("��%d����ֵ������%d;��ǰ��������%d;"), pFuncParaEx->get_DevIndex(), nSGNum, nSGID);

			if (pFuncParaEx->IsConnectDevice())//  �ܺ��  20200421  �����Ƿ��Զ�����ģʽ�£����Զ����豸
			{//�Զ�����ģʽ�£�ö���豸���߼��豸�ɹ��������ö���豸����������

				if (pDevice->nHasDeviceModel == 1)
				{//����Ѿ������豸����ģ�ͣ�����Ҫ�ٶ�ȡ
				}
				else
				{
					int nDeviceIndex = pFuncParaEx->get_DevIndex();
					int nLDIndex  = pFuncParaEx->get_LDvIndex();
					int nDSIndex = pFuncParaEx->get_DSID();

					if(pDevice->LD[0].mms_data_node != NULL)
					{
						theCmsApp->InitReadDevice(nDeviceIndex,FALSE);
					}
					// 					else
					// 					{
					// 						theCmsApp->InitReadDeviceFuncParas(nDeviceIndex, TRUE,FALSE);
					// 					}

					theCmsApp->InitCallReportFlagDefault(nDeviceIndex);

					if (nDSIndex>= 0)
					{
						theCmsApp->InitCallReportFuncParas(nDeviceIndex, nLDIndex, nDSIndex,TRUE, FALSE);
					}
				}
			}
		}
		break;
	case FuncID_SetSGNum:
		if (lParam!=SD_SUCCESS)
		{
			strMsg.Format(_T("��%d�����õ�ǰ��ֵ��������%dʧ�ܡ�Error��"),pFuncParaEx->get_DevIndex(), pFuncParaEx->get_SGID());
		}
		else
		{
			strMsg.Format(_T("���õ�ǰ���ж�ֵ��Ϊ%d"), pFuncParaEx->get_SGID());
		}
		break;
	case FuncID_EnumLD:
		if (lParam==SD_SUCCESS)
		{
			int nDeviceIndex = pFuncParaEx->get_DevIndex();
			// ��ʼ��װ����
			strMsg = _T("ö��װ��Ŀ¼�ɹ�.");//"ö��װ��Ŀ¼�ɹ�.");
		}
		else
		{
			strMsg = _T("ö��װ��Ŀ¼ʧ�ܡ�Error��.");//"ö��װ��Ŀ¼ʧ�ܡ�Error��.");
		}
		break;
	case FuncID_TestProc:
		if (lParam==SD_SUCCESS)
		{
			//theCmsApp->OutputPrintMsg("������������.");
		}
		else
		{
			strMsg = _T("�������ӶϿ�.");//"�������ӶϿ�.");
			pDevice->bConnect = FALSE;
		}

		break;
	case FuncID_SetSENum:
		if (lParam==SD_SUCCESS)
		{
			strMsg.Format(_T("�л��༭��ֵ��%d�ɹ�"), pFuncParaEx->get_SEID());
		}
		else
		{
			strMsg.Format(_T("�л��༭��ֵ��%dʧ�ܡ�Error��"), pFuncParaEx->get_SEID());
		}


		break;
	case FuncID_CnfSetSE:
		if (lParam==SD_SUCCESS)
		{
			strMsg.Format(_T("�̻���ֵ��%d��ֵ�ɹ�"), pFuncParaEx->get_SEID());
		}
		else
		{
			strMsg.Format(_T("�̻���ֵ��%d��ֵʧ�ܡ�Error��"), pFuncParaEx->get_SEID());
		}

		break;
	case FuncID_CtrlWrite:
	case FuncID_CtrlWriteOne:
		if (lParam==SD_SUCCESS)
		{
			strMsg = _T("����д�ɹ�");
			//			ResetWriteFailErrorCode();
		}
		else
		{
			strMsg = _T("����дʧ�ܡ�Error��");
		}


		break;

	case FuncID_Reset:
		if (lParam==SD_SUCCESS)
		{
			strMsg = _T("װ�ø���ɹ�");
		}
		else
		{
			strMsg = _T("װ�ø���ʧ�ܡ�Error��");
		}

		break;

	case FuncID_UploadFile:
		if (lParam==SD_SUCCESS)
		{
			strMsg = _T("ʹ��UPLOAD�����ϴ��ļ��ɹ�");
		}
		else
		{
			strMsg = _T("UPLOAD�ϴ��ļ�ʧ�ܡ�Error��");
		}

		break;

	case FuncID_ReadDevice:
		if (lParam==SD_SUCCESS)
		{
			strMsg = _T("��ȡװ�óɹ�");
		}
		else
		{
			strMsg = _T("��ȡװ��ʧ�ܡ�Error��");
		}

		break;
	default:
		break;
	}

	return 0;
}

LRESULT CCmsEngineAppWnd::OnMmsCmdAllFinish_AutoTest(LONG nFuncID, WPARAM wParam,LPARAM lParam)
{
	CFuncParamEx *pFuncParaEx = (CFuncParamEx*) wParam;
	BOOL bIsClientCmd = pFuncParaEx->is_ClientCmd();
	//LONG nFuncID = pFuncParaEx-> get_FuncID();

	//theMmsApi->OutputPrintMsg(g_sLangTxt_AllCommandExecuted/*_T("�Զ�����ģʽ������ȫ��ִ�����!!")*/);

	if (FuncID_Link== nFuncID || FuncID_UnLink == nFuncID)// || FuncID_EnumLD == wParam)
	{
		ACSI_NODE *pDevice =theCmsApp->GetAcsiNode(pFuncParaEx->get_DevIndex());

		if (pDevice->bTestLinkState)
		{
			pFuncParaEx->SetsConnectDevice(FALSE);
			PostDeviceCommCmdMessage((WPARAM)pFuncParaEx, engineCommFinish);
		}
		else
		{
			if (bIsClientCmd)
			{
				//ͨѶ����״̬������ͨѶ������Ϣ
				if (pFuncParaEx->IsConnectDevice())
				{
					pFuncParaEx->SetsConnectDevice(FALSE);
					CLogPrint::LogString(XLOGLEVEL_TRACE,g_sLangTxt_SendSuccMsg /*_T("+++++++++++���������豸�ɹ���Ϣ+++++++++++")*/);
					PostDeviceSysMessage(pFuncParaEx->get_DevIndex(), engineConnectDeviceSuccessful);
				}
				else
				{
					PostDeviceCommCmdMessage((WPARAM)pFuncParaEx, engineCommFinish);
				}
			}
		}
	}
	else if (FuncID_EnumLD == nFuncID)
	{
	}
	else
	{
		if (pFuncParaEx->IsConnectDevice())
		{//����״̬������ϵͳ��Ϣ
			pFuncParaEx->SetsConnectDevice(FALSE);
			CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_SendSuccMsg/*_T("+++++++++++���������豸�ɹ���Ϣ+++++++++++")*/);
			PostDeviceSysMessage(pFuncParaEx->get_DevIndex(), engineConnectDeviceSuccessful);
		}
		else
		{//ͨѶ����״̬������ͨѶ������Ϣ
			PostDeviceCommCmdMessage((WPARAM)pFuncParaEx, engineCommFinish);
		}
	}

	return 0;
}

LRESULT CCmsEngineAppWnd::OnMmsCmdFinish_Error(WPARAM wParam,LPARAM lParam)
{
	if (g_bMmsEngineDebugMode)
	{
		return 0;
	}

	CFuncParamEx *pFuncParaEx = (CFuncParamEx*) wParam;
	LONG nFuncID = pFuncParaEx-> get_FuncID();

	if (!theCmsApp->IsFuncsAllFinish(pFuncParaEx->get_DevIndex()))
	{
		if (nFuncID == FuncID_TestProc)
		{
			PostDeviceSysMessage(pFuncParaEx->get_DevIndex() ,engineConnectDeviceFailed);
		}	
		else
		{
			ACSI_NODE *pACSI_NODE =theCmsApp->GetAcsiNode(pFuncParaEx->get_DevIndex());

			if (!pACSI_NODE->bTestLinkState)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Error CMD Exec:CMD=%d DV=%d  LD=%d  DS=%d"), pFuncParaEx->get_FuncID()
					, pFuncParaEx->get_DevIndex(), pFuncParaEx->get_LDvIndex(), pFuncParaEx->get_DSID());
				pFuncParaEx->set_FuncID(FuncID_TestProc);
				theCmsApp->ProgDlg_StopProgress(pFuncParaEx->get_DevIndex());	
				PostDeviceSysMessage(pFuncParaEx->get_DevIndex() ,engineCommError);

				pFuncParaEx->SetsConnectDevice(FALSE);
			}
			else
			{
				PostDeviceCommCmdMessage((WPARAM)pFuncParaEx, engineCommFinish);
				pFuncParaEx->set_FuncID(FuncID_TestProc);
			}

			theCmsApp->ProgDlg_StopProgress(pFuncParaEx->get_DevIndex());
		}
	}
	else
	{
		pFuncParaEx->set_FuncID(FuncID_TestProc);
	}

	return 0;
}

LRESULT CCmsEngineAppWnd::OnMmsCmdFinish(WPARAM wParam,LPARAM lParam)
{
	CFuncParamEx *pFuncParaEx = (CFuncParamEx*) wParam;
	CString strMsg;
	BOOL bIsClientCmd = pFuncParaEx->is_ClientCmd();
	LONG nFuncID = pFuncParaEx->get_FuncID();

	OnMmsCmdFinish_View(wParam, lParam);

	if (lParam==SD_SUCCESS)
	{
		if (nFuncID == FuncID_TestProc)
		{
			return 0;
		}

		ACSI_NODE *pDevice =theCmsApp->GetAcsiNode(pFuncParaEx->get_DevIndex());
		theCmsApp->CallNextFunc(pFuncParaEx->get_DevIndex());

		if ( theCmsApp->IsFuncsAllFinish(pFuncParaEx->get_DevIndex()) )
		{//ȫ�������
			//2022-11-26  lijunqing ���뵱ǰ�Ĺ���ID������next�Ĺ���id
			OnMmsCmdAllFinish_AutoTest(nFuncID, wParam, lParam);
		}
	}
	else
	{
		OnMmsCmdFinish_Error(wParam, lParam);
	}

	return 0;
}

LRESULT CCmsEngineAppWnd::SaveAllMmsDevicesRcdFiles(WPARAM wParam,LPARAM lParam)
{
	return 0;
}

LRESULT CCmsEngineAppWnd::OnMmsReport(WPARAM wParam,LPARAM lParam)
{
	return 0;
}

LRESULT CCmsEngineAppWnd::OnReset(WPARAM wParam,LPARAM lParam)
{
	return 0;
}

LRESULT CCmsEngineAppWnd::OnConnectAllDevice(WPARAM wParam,LPARAM lParam)
{
	return 0;
}

