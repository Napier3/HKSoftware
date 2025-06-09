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
			strMsg.Format(_T("和装置%d联机成功."),pFuncParaEx->get_DevIndex());
		}
		else
		{
			strMsg.Format(_T("和装置%d联机失败【Error】."),pFuncParaEx->get_DevIndex());
		}

		mms_UpdateDeviceState(pDevice);

		break;

	case FuncID_UnLink:
		if (lParam==SD_SUCCESS)
		{
			strMsg.Format(_T("和装置%d断开连接成功."),pFuncParaEx->get_DevIndex());
		}
		else
		{
			strMsg.Format(_T("和装置%d断开连接失败【Error】."),pFuncParaEx->get_DevIndex());
		}

		pDevice->bConnect = FALSE;
		mms_UpdateDeviceState(pDevice);

		break;

	case FuncID_Read:
	case FuncID_Read_SET:
		if (lParam==SD_SUCCESS)
		{
			strMsg.Format(_T("读取装置%d数据集成功."),pFuncParaEx->get_DevIndex());
		}
		else
		{
			strMsg.Format(_T("读取装置%d数据集失败【Error】."),pFuncParaEx->get_DevIndex());
		}

		//		ResetWriteFailErrorCode();//在读取数据操作后，将写失败的原因码值复归为-1 因为原因码值可能为0，此处设置为-1为复归值
		break;

	case FuncID_ReadDir:
		if (lParam==SD_SUCCESS)
		{
			PXMMS_FILE_SYS_OBJ pFileDir = &pDevice->FileDir;

			if (pFileDir->readfailed == 1)
			{
				strMsg.Format(_T("读取装置%d录波文件目录失败."),pFuncParaEx->get_DevIndex());
			}
			else
			{
				//strMsg.Format(_T("读取装置%d录波文件目录成功."),pFuncParaEx->get_DevIndex());
			}
		}
		else
		{
			strMsg.Format(_T("读取装置%d录波文件目录失败."),pFuncParaEx->get_DevIndex());
		}
		break;
	case FuncID_ReadRPC:

		if (lParam==SD_SUCCESS)
		{
			strMsg.Format(_T("读取装置%d远程调用RPC方法成功."),pFuncParaEx->get_DevIndex());
		}
		else
		{
			strMsg.Format(_T("读取装置%d远程调用RPC方法失败."),pFuncParaEx->get_DevIndex());
		}

		break;
	case FuncID_RpcCall:

		if (lParam==SD_SUCCESS)
		{
			strMsg.Format(_T("读取装置%d远程调用RpcCall成功."),pFuncParaEx->get_DevIndex());
		}
		else
		{
			strMsg.Format(_T("读取装置%d远程调用RpcCall失败."),pFuncParaEx->get_DevIndex());
		}

		break;
	case FuncID_ReadFile:
		if (lParam==SD_SUCCESS)
		{
			strMsg.Format(_T("读取装置%d录波文件成功."),pFuncParaEx->get_DevIndex());
		}
		else
		{
			strMsg.Format(_T("读取装置%d录波文件失败."),pFuncParaEx->get_DevIndex());
		}
		break;

	case FuncID_Write:
		if (lParam!=SD_SUCCESS)
		{
			//theMmsApi->OutputPrintMsg(g_sLangTxt_WriteDataFail);//"写数据失败【Error】.");
		}
		else
		{
			//theMmsApi->OutputPrintMsg(g_sLangTxt_WriteDataSucc);//"写数据成功.");
		}
		break;
	case FuncID_StartRpt:
		if (lParam!=SD_SUCCESS)
		{
			//theMmsApi->OutputPrintMsg(g_sLangTxt_StartRptFail);//"启动报告失败【Error】.");
		}
		else
		{
			//theMmsApi->OutputPrintMsg(g_sLangTxt_StartRptSucc);//"启动报告成功.");
		}

		theCmsApp->SetReportRet(pFuncParaEx,lParam==SD_SUCCESS, TRUE);
		break;
	case FuncID_StopRpt:
		if (lParam!=SD_SUCCESS)
		{
			//theMmsApi->OutputPrintMsg(g_sLangTxt_StopRptFail);//"停止报告失败【Error】.");
		}
		else
		{
			//theMmsApi->OutputPrintMsg(g_sLangTxt_StopRptSucc);//"停止报告成功.");
		}

		theCmsApp->SetReportRet(pFuncParaEx,lParam==SD_SUCCESS, FALSE);
		break;
	case FuncID_GetSGNum:
		if (lParam!=SD_SUCCESS)
		{
			//theMmsApi->OutputPrintMsg(g_sLangTxt_ReadZoneFail);//"获取当前定值运行区号失败.");
		}
		else
		{
			ST_INT nSGNum = pFuncParaEx->get_SGNum();
			ST_INT nSGID = pFuncParaEx->get_SGID();

			CString strText = "";
			strText.Format(_T("【%d】定值区数：%d;当前运行区：%d;"), pFuncParaEx->get_DevIndex(), nSGNum, nSGID);

			if (pFuncParaEx->IsConnectDevice())//  周宏军  20200421  无论是否自动测试模式下，都自动读设备
			{//自动测试模式下，枚举设备的逻辑设备成功，则继续枚举设备的其他参数

				if (pDevice->nHasDeviceModel == 1)
				{//如果已经有了设备数据模型，则不需要再读取
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
			strMsg.Format(_T("【%d】设置当前定值运行区号%d失败【Error】"),pFuncParaEx->get_DevIndex(), pFuncParaEx->get_SGID());
		}
		else
		{
			strMsg.Format(_T("设置当前运行定值区为%d"), pFuncParaEx->get_SGID());
		}
		break;
	case FuncID_EnumLD:
		if (lParam==SD_SUCCESS)
		{
			int nDeviceIndex = pFuncParaEx->get_DevIndex();
			// 初始化装置树
			strMsg = _T("枚举装置目录成功.");//"枚举装置目录成功.");
		}
		else
		{
			strMsg = _T("枚举装置目录失败【Error】.");//"枚举装置目录失败【Error】.");
		}
		break;
	case FuncID_TestProc:
		if (lParam==SD_SUCCESS)
		{
			//theCmsApp->OutputPrintMsg("网络连接正常.");
		}
		else
		{
			strMsg = _T("网络连接断开.");//"网络连接断开.");
			pDevice->bConnect = FALSE;
		}

		break;
	case FuncID_SetSENum:
		if (lParam==SD_SUCCESS)
		{
			strMsg.Format(_T("切换编辑定值区%d成功"), pFuncParaEx->get_SEID());
		}
		else
		{
			strMsg.Format(_T("切换编辑定值区%d失败【Error】"), pFuncParaEx->get_SEID());
		}


		break;
	case FuncID_CnfSetSE:
		if (lParam==SD_SUCCESS)
		{
			strMsg.Format(_T("固化定值区%d定值成功"), pFuncParaEx->get_SEID());
		}
		else
		{
			strMsg.Format(_T("固化定值区%d定值失败【Error】"), pFuncParaEx->get_SEID());
		}

		break;
	case FuncID_CtrlWrite:
	case FuncID_CtrlWriteOne:
		if (lParam==SD_SUCCESS)
		{
			strMsg = _T("控制写成功");
			//			ResetWriteFailErrorCode();
		}
		else
		{
			strMsg = _T("控制写失败【Error】");
		}


		break;

	case FuncID_Reset:
		if (lParam==SD_SUCCESS)
		{
			strMsg = _T("装置复归成功");
		}
		else
		{
			strMsg = _T("装置复归失败【Error】");
		}

		break;

	case FuncID_UploadFile:
		if (lParam==SD_SUCCESS)
		{
			strMsg = _T("使用UPLOAD命令上传文件成功");
		}
		else
		{
			strMsg = _T("UPLOAD上传文件失败【Error】");
		}

		break;

	case FuncID_ReadDevice:
		if (lParam==SD_SUCCESS)
		{
			strMsg = _T("读取装置成功");
		}
		else
		{
			strMsg = _T("读取装置失败【Error】");
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

	//theMmsApi->OutputPrintMsg(g_sLangTxt_AllCommandExecuted/*_T("自动测试模式，命令全部执行完毕!!")*/);

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
				//通讯命令状态，发送通讯命令消息
				if (pFuncParaEx->IsConnectDevice())
				{
					pFuncParaEx->SetsConnectDevice(FALSE);
					CLogPrint::LogString(XLOGLEVEL_TRACE,g_sLangTxt_SendSuccMsg /*_T("+++++++++++发送连接设备成功消息+++++++++++")*/);
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
		{//联机状态，发送系统消息
			pFuncParaEx->SetsConnectDevice(FALSE);
			CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_SendSuccMsg/*_T("+++++++++++发送连接设备成功消息+++++++++++")*/);
			PostDeviceSysMessage(pFuncParaEx->get_DevIndex(), engineConnectDeviceSuccessful);
		}
		else
		{//通讯命令状态，发送通讯命令消息
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
		{//全命令完成
			//2022-11-26  lijunqing 传入当前的功能ID，不是next的功能id
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

