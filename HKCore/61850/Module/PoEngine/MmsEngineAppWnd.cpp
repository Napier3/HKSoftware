// MmsEngineAppWnd.cpp
//

#include "stdafx.h"
#include "MmsEngineAppBase.h"
#include "MmsEngineAppWnd.h"

#include "../MmsGlobal.h"
#include "../MmsWriteXml.h"
#include "../../../Module/API/FileApi.h"
#include "../../../Module/System/TickCount32.h"
#include "PoMmsDevice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMmsEngineAppWnd

CMmsEngineAppWnd::CMmsEngineAppWnd()
{
	m_nCallFuncRetryTimes = 0;
	m_bOperateAllDevReport = 0;
	m_pOnOperAllDevsRpt_Thread = NULL;
	m_pReadAllDeviceRcdDir = NULL;

	m_nStartAllDevsRpt_DeviceIndex = 0;
	m_nStartAllDevsRpt_LDIndex = 0;
	m_pLinkDevice_Thread = NULL;
	m_nOnCloseDevAll_Curr_Index = -1;
	m_nReadDirDevAll_Curr_Index = -1;
	m_nReadDirFailTimes = 0;
}

CMmsEngineAppWnd::~CMmsEngineAppWnd()
{
	
}

void CMmsEngineAppWnd::StartAllDevsRpt_Func()
{
/*
	m_bOperateAllDevReport = TRUE;

	//根据装置数量创建启动报告的结构体
	CDvmDataset *pMstmSlnDevices = &g_theMmsEngineRpcMngr->m_oMstmSlnDevices;
	long nDeviceCount = pMstmSlnDevices->GetCount();

	if (nDeviceCount == 0)
	{
		return;
	}

	PSTRUCT_START_RPT pStartRptParas = new STRUCT_START_RPT[nDeviceCount];
	long nIndex = 0;
	PSTRUCT_START_RPT p = pStartRptParas;
	long nCnlnIndex=0; 
	CDvmValue *pSlnCnln = NULL;
	CDvmData *pMstmSlnDv = NULL;
	pMstmSlnDv = (CDvmData*)pMstmSlnDevices->GetHead();
	long nCnlnCount = pMstmSlnDv->GetCount();

	for (nIndex=0; nIndex<nDeviceCount; nIndex++)
	{
		p->nCnlnIndex = 0;
		p->pFuncParaEx = NULL;
		p->nMstmSlnDvIndex = nIndex;
		p->nCnlnIndex = 0;
		p->strSleDsPath = m_strOperAllRpt_DsName;
		p->strLDType = m_strOperAllRpt_LDName;
		p->pThread = NULL;
		p->pMainFrame = this;
		p->nRetSucc = 0;
		p->nLinkCounts = 0;
		p++;

		pMstmSlnDv = (CDvmData *)pMstmSlnDevices->GetAtIndex(nIndex);

		//找到一个没有启动报告的MMS装置
		for (nCnlnIndex=0; nCnlnIndex<nCnlnCount; nCnlnIndex++)
		{
			pSlnCnln = (CDvmValue*)pMstmSlnDv->GetAtIndex(nCnlnIndex);
			pSlnCnln->m_dwItemData = 0;
		}
	}

	CTickCount32 oTickCount;
	CFuncParamEx *pFuncEx = NULL;
	BOOL bCanEnd = FALSE;
	int nMmsDevIndex = 0;
	long nLinkCounts = 0;

//	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("开始StartAllDevsRpt_Func线程循环"));

	while (TRUE)
	{
		bCanEnd = TRUE;

		for (long nDev = 0; nDev < nDeviceCount;nDev++)
		{
			//每个装置一个启动报告线程，当前装置的启动报告线程还没有结束，等待后进入下一个装置的判断
			if (pStartRptParas[nDev].pThread != NULL)
			{
				bCanEnd = FALSE; //线程还没有结束，不能结束总的线程
				oTickCount.DoEvents(100);
				continue;
			}

			pMstmSlnDv = (CDvmData *)pMstmSlnDevices->GetAtIndex(nDev);

			//找到一个没有启动报告的MMS装置
			for (nCnlnIndex=pStartRptParas[nDev].nCnlnIndex; nCnlnIndex<nCnlnCount; nCnlnIndex++)
			{
				pSlnCnln = (CDvmValue*)pMstmSlnDv->GetAtIndex(nCnlnIndex);
				ASSERT (pSlnCnln != NULL);

				if (pSlnCnln->m_dwItemData == 0xFF00FF00)
				{
					continue;
				}

				nMmsDevIndex = nDev * nCnlnCount + nCnlnIndex;

				if (!theMmsApi->m_oFuncParamEx[nMmsDevIndex].m_bEnaRpt)
				{// 不使能报告
					continue;
				}

				if (!acsi_ctrl_table[nMmsDevIndex].bConnect || (acsi_ctrl_table[nMmsDevIndex].pnet_info == NULL ) )
				{//未连接，表示线程不能结束
					bCanEnd = FALSE;
					continue;
				}

				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(">>Start %s : %s Report"), pMstmSlnDv->m_strID, pSlnCnln->m_strID);
				pFuncEx = &theMmsApi->m_oFuncParamEx[nMmsDevIndex];
				pFuncEx->set_DevIndex(nMmsDevIndex);

				pStartRptParas[nDev].pFuncParaEx = pFuncEx;
				pStartRptParas[nDev].pCnln = pSlnCnln;
				pStartRptParas[nDev].pThread = AfxBeginThread(StartTripInforRpt_Thread, &pStartRptParas[nDev]);
				pStartRptParas[nDev].pThread->m_bAutoDelete = TRUE;
				bCanEnd = FALSE;
				
				break;
			}//end of <for (long nCnlnIndex=pStartRptParas[nDev].nCnlnIndex; nCnlnIndex<nCnlnCount; nCnlnIndex++)>
		}//end of <for (long nDev = 0; nDev < nDeviceCount;nDev++)>

		if (bCanEnd)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("退出StartAllDevsRpt_Func线程循环"));
			CDvmDataset *pDataset = &theMmsApi->m_pMmsEngineRpcMngr->m_oRptStartDataset;
			CDvmData *pData = (CDvmData*)pDataset->GetAtIndex(pDataset->m_nIndex);

			if (pData != NULL)
			{
				this->PostMessage(WM_OPER_ALL_DEVS_REPORT,OPERATE_START_ALL_DEV_REPORT,(LPARAM)pData);
				pDataset->m_nIndex++;
			}
			else
				pDataset->DeleteAll();
			break;
		}

		//延时
		oTickCount.DoEvents(100);
	}

	m_bOperateAllDevReport = FALSE;
	//delete pStartRptParas;

	return;
// 
// 
// 	if (theMmsApi->m_pMmsEngineRpcMngr != NULL)
// 	{
// 		for (long nDevIndex = 0;nDevIndex < MAX_DEVICE;nDevIndex++)
// 		{
// 
// 			if ((theMmsApi->m_oFuncParamEx[nDevIndex].m_bEnaRpt)&&(acsi_ctrl_table[nDevIndex].bConnect))
// 			{
// 				if ((acsi_ctrl_table[nDevIndex].pnet_info) != NULL)
// 				{
// 					pFuncEx = &theMmsApi->m_oFuncParamEx[nDevIndex];
// 					pFuncEx->set_DevIndex(nDevIndex);
// 					StartTripInforRpt(pFuncEx,strSleDsPath,strSelLDName);//zhouhj 对于多装置做特殊处理，固定联机成功去启动报告
// 
// 					//mms_FindByDeviceIndexForStartRpt
// 					//查找一个没有启动报告的装置
// 					//调用InitFuncPara，的模式，启动报告
// 					//sleep（1000），
// 				}
// 
// 			}	
// 		}
// 	}
// 
// 	pFuncEx = NULL;
// 
// 	m_bOperateStartAllDevReport = FALSE;
*/
}

void CMmsEngineAppWnd::StopAllDevsRpt_Func()
{
/*
	m_bOperateAllDevReport = TRUE;

	//根据装置数量创建启动报告的结构体
	CDvmDataset *pMstmSlnDevices = &g_theMmsEngineRpcMngr->m_oMstmSlnDevices;
	long nDeviceCount = pMstmSlnDevices->GetCount();

	if (nDeviceCount == 0)
	{
		return;
	}

	PSTRUCT_START_RPT pStartRptParas = new STRUCT_START_RPT[nDeviceCount];
	long nIndex = 0;
	PSTRUCT_START_RPT p = pStartRptParas;
	long nCnlnIndex=0; 
	CDvmValue *pSlnCnln = NULL;
	CDvmData *pMstmSlnDv = NULL;
	pMstmSlnDv = (CDvmData*)pMstmSlnDevices->GetHead();
	long nCnlnCount = pMstmSlnDv->GetCount();

	for (nIndex=0; nIndex<nDeviceCount; nIndex++)
	{
		p->nCnlnIndex = 0;
		p->pFuncParaEx = NULL;
		p->nMstmSlnDvIndex = nIndex;
		p->nCnlnIndex = 0;
		p->strSleDsPath = m_strOperAllRpt_DsName;
		p->strLDType = m_strOperAllRpt_LDName;
		p->pThread = NULL;
		p->pMainFrame = this;
		p->nRetSucc = 0;
		p->nLinkCounts = 0;
		p++;

		pMstmSlnDv = (CDvmData *)pMstmSlnDevices->GetAtIndex(nIndex);

		//找到一个没有启动报告的MMS装置
		for (nCnlnIndex=0; nCnlnIndex<nCnlnCount; nCnlnIndex++)
		{
			pSlnCnln = (CDvmValue*)pMstmSlnDv->GetAtIndex(nCnlnIndex);
			pSlnCnln->m_dwItemData = 0;
		}
	}

	CTickCount32 oTickCount;
	CFuncParamEx *pFuncEx = NULL;
	BOOL bCanEnd = FALSE;
	int nMmsDevIndex = 0;
	long nLinkCounts = 0;

	while (TRUE)
	{
		bCanEnd = TRUE;

		for (long nDev = 0; nDev < nDeviceCount;nDev++)
		{
			//每个装置一个启动报告线程，当前装置的启动报告线程还没有结束，等待后进入下一个装置的判断
			if (pStartRptParas[nDev].pThread != NULL)
			{
				bCanEnd = FALSE; //线程还没有结束，不能结束总的线程
				oTickCount.DoEvents(100);
				continue;
			}

			pMstmSlnDv = (CDvmData *)pMstmSlnDevices->GetAtIndex(nDev);

			//找到一个没有启动报告的MMS装置
			for (nCnlnIndex=pStartRptParas[nDev].nCnlnIndex; nCnlnIndex<nCnlnCount; nCnlnIndex++)
			{
				pSlnCnln = (CDvmValue*)pMstmSlnDv->GetAtIndex(nCnlnIndex);
				ASSERT (pSlnCnln != NULL);

				if (pSlnCnln->m_dwItemData == 0xFF00FF00)
				{
					continue;
				}

				nMmsDevIndex = nDev * nCnlnCount + nCnlnIndex;

				if (!theMmsApi->m_oFuncParamEx[nMmsDevIndex].m_bEnaRpt)
				{// 不停止报告
					continue;
				}

				if (!acsi_ctrl_table[nMmsDevIndex].bConnect || (acsi_ctrl_table[nMmsDevIndex].pnet_info == NULL ) )
				{//未连接，默认报告未启动，无需关闭
					continue;
				}

				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(">>Stop %s : %s Report"), pMstmSlnDv->m_strID, pSlnCnln->m_strID);
				pFuncEx = &theMmsApi->m_oFuncParamEx[nMmsDevIndex];
				pFuncEx->set_DevIndex(nMmsDevIndex);

				pStartRptParas[nDev].pFuncParaEx = pFuncEx;
				pStartRptParas[nDev].pCnln = pSlnCnln;
				pStartRptParas[nDev].pThread = AfxBeginThread(StopTripInforRpt_Thread, &pStartRptParas[nDev]);
				pStartRptParas[nDev].pThread->m_bAutoDelete = TRUE;
				bCanEnd = FALSE;

				break;
			}//end of <for (long nCnlnIndex=pStartRptParas[nDev].nCnlnIndex; nCnlnIndex<nCnlnCount; nCnlnIndex++)>
		}//end of <for (long nDev = 0; nDev < nDeviceCount;nDev++)>

		if (bCanEnd)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("退出StopAllDevsRpt_Func线程循环"));
			break;
		}

		//延时
		oTickCount.DoEvents(100);
	}

	m_bOperateAllDevReport = FALSE;

	return;
*/
}

UINT CMmsEngineAppWnd::LinkDevAll_OneDevice_Thread(LPVOID pParam)
{
/*
	PSTRUCT_START_RPT pStartRptPara = (PSTRUCT_START_RPT)pParam;

	//zhouhj 对于多装置做特殊处理，固定联机成功去启动报告
	CFuncParamEx *pFuncParaEx = pStartRptPara->pFuncParaEx;
	long nDevIndex = pFuncParaEx->get_DevIndex();

	pFuncParaEx->set_LDvIndex(nDevIndex);
	pFuncParaEx->set_FuncID(FuncID_Link);

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE ,_T("开始连接第%d台装置"),nDevIndex);

	ST_RET nRet = SD_FAILURE;
	nRet = theMmsApi->MMS_LinkDev(pFuncParaEx);

// 	if (theMmsApi->m_pMmsEngineRpcMngr != NULL)
// 	{
// 		theMmsApi->m_pMmsEngineRpcMngr->OnAloneOperCmdFinish((WPARAM)pFuncParaEx, nRet);
// 	}

	pStartRptPara->pThread = NULL;

	if (pStartRptPara->nRetSucc == SD_SUCCESS)
	{
		pStartRptPara->pCnln->m_dwReserved = 0xFF00FF00;
		pStartRptPara->nCnlnIndex++;
	}
	else
	{
		pStartRptPara->pCnln->m_dwItemData = 0;
		pStartRptPara->nLinkCounts++;

		if (pStartRptPara->nLinkCounts >= 10)
		{
			pStartRptPara->pCnln->m_dwItemData = 0xFF00FF00;
			pStartRptPara->nLinkCounts = 0;
		}
	}
*/
	return 0;
}

UINT CMmsEngineAppWnd::StartTripInforRpt_Thread(LPVOID pParam)
{
/*
	PSTRUCT_START_RPT pStartRptPara = (PSTRUCT_START_RPT)pParam;

	//zhouhj 对于多装置做特殊处理，固定联机成功去启动报告
	pStartRptPara->nRetSucc = pStartRptPara->pMainFrame->StartTripInforRpt(pStartRptPara->pFuncParaEx
		,pStartRptPara->strSleDsPath,pStartRptPara->strLDType);
	pStartRptPara->pThread = NULL;

	if (pStartRptPara->nRetSucc == SD_SUCCESS)
	{
		pStartRptPara->pCnln->m_dwItemData = 0xFF00FF00;
		pStartRptPara->nCnlnIndex++;
	}
	else
	{
		pStartRptPara->pCnln->m_dwItemData = 0;
		pStartRptPara->nLinkCounts++;

		if (pStartRptPara->nLinkCounts >= 10)
		{
			pStartRptPara->pCnln->m_dwItemData = 0xFF00FF00;
			pStartRptPara->nLinkCounts = 0;
		}
	}
*/
	return 0;
}

UINT CMmsEngineAppWnd::StopTripInforRpt_Thread(LPVOID pParam)
{
/*
	PSTRUCT_START_RPT pStartRptPara = (PSTRUCT_START_RPT)pParam;

	pStartRptPara->nRetSucc = pStartRptPara->pMainFrame->StopTripInforRpt(pStartRptPara->pFuncParaEx
		,pStartRptPara->strSleDsPath,pStartRptPara->strLDType);
	pStartRptPara->pThread = NULL;

	if (pStartRptPara->nRetSucc == SD_SUCCESS)
	{
		pStartRptPara->pCnln->m_dwItemData = 0xFF00FF00;
		pStartRptPara->nCnlnIndex++;
	}
	else
	{
		pStartRptPara->pCnln->m_dwItemData = 0;
		pStartRptPara->nLinkCounts++;

		if (pStartRptPara->nLinkCounts >= 10)
		{
			pStartRptPara->pCnln->m_dwItemData = 0xFF00FF00;
			pStartRptPara->nLinkCounts = 0;
		}
	}
*/
	return 0;
}

UINT CMmsEngineAppWnd::OnStartAllDevsRpt_Thread(LPVOID pParam)
{
/*
	CMmsEngineAppWnd *pMainFrame = (CMmsEngineAppWnd*)pParam;
	pMainFrame->StartAllDevsRpt_Func();
	pMainFrame->m_pOnOperAllDevsRpt_Thread = NULL;
*/
	return 0;
}

UINT CMmsEngineAppWnd::OnStopAllDevsRpt_Thread(LPVOID pParam)
{
/*
	CMmsEngineAppWnd *pMainFrame = (CMmsEngineAppWnd*)pParam;
	pMainFrame->StopAllDevsRpt_Func();
	pMainFrame->m_pOnOperAllDevsRpt_Thread = NULL;
*/
	return 0;
}

LRESULT CMmsEngineAppWnd::OnOperAllDevsRpt(WPARAM wParam,LPARAM lParam)//参数2传递CDvmData 其m_strID传递对应数据集名称，LD默认固定为PROT
{
/*
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("收到WM_OPER_ALL_DEVS_REPORT消息"));

	if (m_pOnOperAllDevsRpt_Thread != NULL)
	{
		return 0;
	}

	if (lParam != NULL)
	{
		m_strOperAllRpt_LDName = _T("PROT");
		CDvmData *pData = (CDvmData*)lParam;
		m_strOperAllRpt_DsName = pData->m_strID;
		m_strOperAllRpt_DsName.MakeUpper();
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("启动OnStartAllDevsRpt_Thread线程"));

	if (wParam == OPERATE_START_ALL_DEV_REPORT)
	{
		m_pOnOperAllDevsRpt_Thread = AfxBeginThread(OnStartAllDevsRpt_Thread, (LPVOID)this);
	} 
	else if (wParam == OPERATE_STOP_ALL_DEV_REPORT)
	{
		m_pOnOperAllDevsRpt_Thread = AfxBeginThread(OnStopAllDevsRpt_Thread, (LPVOID)this);
	}
*/
	return 0;
}

//2020-12-22  lijunqing  外部调用配置接口，配置IP
void CMmsEngineAppWnd::OnLinkDev(long nDeviceIndex, BOOL bIsConfig)
{
/*	CLinkSetDlg LinkDlg;
	LinkDlg.m_nDeviceIndex = nDeviceIndex;
	LinkDlg.m_bIsConfig = bIsConfig;

	if (theMmsApi->m_oFuncParamEx[nDeviceIndex].m_hThread_Proc_Data == NULL)
	{
		theMmsApi->CreateDataProcThread(&theMmsApi->m_oFuncParamEx[nDeviceIndex]);
	}

	if (LinkDlg.DoModal() == IDOK)
	{
		m_wndNodeView.UpdateDeviceIP_Desc(LinkDlg.m_nDeviceIndex);
	}
*/
}

/*void CMmsEngineAppWnd::OnLinkDevAll()
{

	if (! Encrypt_CanUse_MmsEngine())
	{
		return;
	}

	long nDeviceCount = theMmsApi->HasDevice();
	nDeviceCount--;

	if (nDeviceCount<0)
	{
		nDeviceCount = 0;
	}

	ACSI_NODE *pDevice = NULL;

	if (theMmsApi->m_pMmsEngineRpcMngr != NULL)
	{
		theMmsApi->m_pMmsEngineRpcMngr->ConnectAllDevice();
//		theMmsApi->m_pMmsEngineRpcMngr->m_nCurrConnectDeviceIndex = 0;
	}
	else
	{
		for (long nIndex = 0;nIndex<nDeviceCount;nIndex++)
		{
			pDevice = &pACSINode[nIndex];

			if (!pDevice->bConnect)
			{
				theMmsApi->InitDeviceNodeList(nIndex);
				theMmsApi->InitLinkDeviceFuncPara_AutoTest(nIndex, TRUE);
				theMmsApi->CallFirstFunc(nIndex);
			}
			//else if (theMmsApi->m_pMmsEngineRpcMngr != NULL)
			//{
			//	theMmsApi->m_pMmsEngineRpcMngr->m_nCurrConnectDeviceIndex++;
			//}
		}
	}
}
*/

UINT CMmsEngineAppWnd::LinkDevAll_Thread(LPVOID pParam)
{
/*
	CMmsEngineAppWnd *pMainFrame = (CMmsEngineAppWnd*)pParam;
	pMainFrame->LinkDevAll_ThreadFunc();
	pMainFrame->m_pLinkDevice_Thread = NULL;
*/
	return 0;
}

void CMmsEngineAppWnd::LinkDevAll_ThreadFunc()
{
/*
	//根据装置数量创建启动报告的结构体
	CDvmDataset *pMstmSlnDevices = &g_theMmsEngineRpcMngr->m_oMstmSlnDevices;
	long nDeviceCount = pMstmSlnDevices->GetCount();

	if (nDeviceCount == 0)
	{
		return;
	}

	PSTRUCT_START_RPT pStartRptParas = new STRUCT_START_RPT[nDeviceCount];
	long nIndex = 0;
	PSTRUCT_START_RPT p = pStartRptParas;
	long nCnlnIndex=0; 
	CDvmValue *pSlnCnln = NULL;
	CDvmData *pMstmSlnDv = NULL;
	pMstmSlnDv = (CDvmData*)pMstmSlnDevices->GetHead();
	long nCnlnCount = pMstmSlnDv->GetCount();

	for (nIndex=0; nIndex<nDeviceCount; nIndex++)
	{
		p->nCnlnIndex = 0;
		p->pFuncParaEx = NULL;
		p->nMstmSlnDvIndex = nIndex;
		p->nCnlnIndex = 0;
		p->pThread = NULL;
		p->pMainFrame = this;
		p->nRetSucc = 0;
		p->nLinkCounts = 0;
		p++;

		pMstmSlnDv = (CDvmData *)pMstmSlnDevices->GetAtIndex(nIndex);
		pMstmSlnDv->m_dwReserved = 0;

		for (nCnlnIndex=0; nCnlnIndex<nCnlnCount; nCnlnIndex++)
		{
			pSlnCnln = (CDvmValue*)pMstmSlnDv->GetAtIndex(nCnlnIndex);
			pSlnCnln->m_dwItemData = 0;
		}
	}

	CTickCount32 oTickCount;
	CFuncParamEx *pFuncEx = NULL;
	BOOL bCanEnd = FALSE;
	int nMmsDevIndex = 0;
	long nLinkCounts = 0;

	while (TRUE)
	{
		bCanEnd = TRUE;

		for (long nDev = 0; nDev < nDeviceCount;nDev++)
		{
			//每个装置一个启动报告线程，当前装置的启动报告线程还没有结束，等待后进入下一个装置的判断
			if (pStartRptParas[nDev].pThread != NULL)
			{
				bCanEnd = FALSE; //线程还没有结束，不能结束总的线程
				oTickCount.DoEvents(100);
				continue;
			}

			pMstmSlnDv = (CDvmData *)pMstmSlnDevices->GetAtIndex(nDev);

			if (pMstmSlnDv->m_dwReserved == 0)
			{
				//ping
				ST_ULONG nLocalIP = 0;
				nLocalIP =  inet_addr(pMstmSlnDv->m_strValue);
				ST_INT ping_ret = ping(nLocalIP);  

				if (ping_ret == 0)
				{
					pMstmSlnDv->m_dwReserved = 0x0000FFFF;
					continue;
				}
				else
				{
					pMstmSlnDv->m_dwReserved = 0xFFFF0000;
				}
			}
			else if (pMstmSlnDv->m_dwReserved == 0x0000FFFF)
			{//如果ping不通，则不再联机
				continue;
			}

			//找到一个没有连接的MMS装置
			for (nCnlnIndex=pStartRptParas[nDev].nCnlnIndex; nCnlnIndex<nCnlnCount; nCnlnIndex++)
			{
				pSlnCnln = (CDvmValue*)pMstmSlnDv->GetAtIndex(nCnlnIndex);
				ASSERT (pSlnCnln != NULL);

				if (pSlnCnln->m_dwReserved == 0xFF00FF00)
				{
					continue;
				}

				nMmsDevIndex = nDev * nCnlnCount + nCnlnIndex;

				if (!acsi_ctrl_table[nMmsDevIndex].bConnect || (acsi_ctrl_table[nMmsDevIndex].pnet_info == NULL ) )
				{//未连接，表示线程不能结束
					bCanEnd = FALSE;
					continue;
				}

				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(">>Link %s : %s"), pMstmSlnDv->m_strID, pSlnCnln->m_strID);
				pFuncEx = &theMmsApi->m_oFuncParamEx[nMmsDevIndex];
				pFuncEx->set_DevIndex(nMmsDevIndex);

				pStartRptParas[nDev].pFuncParaEx = pFuncEx;
				pStartRptParas[nDev].pCnln = pSlnCnln;
				pStartRptParas[nDev].pThread = AfxBeginThread(LinkDevAll_OneDevice_Thread, &pStartRptParas[nDev]);
				pStartRptParas[nDev].pThread->m_bAutoDelete = TRUE;
				bCanEnd = FALSE;

				break;
			}//end of <for (long nCnlnIndex=pStartRptParas[nDev].nCnlnIndex; nCnlnIndex<nCnlnCount; nCnlnIndex++)>
		}//end of <for (long nDev = 0; nDev < nDeviceCount;nDev++)>

		if (bCanEnd)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("退出LinkAllDevice_Func线程循环"));
			break;
		}

		//延时
		oTickCount.DoEvents(100);
	}
*/
	return;
}

void CMmsEngineAppWnd::OnCloseDevAll_CloseCurr()
{
/*
	long nDeviceCount = theMmsApi->HasDevice();

	while (TRUE)
	{
		if (pACSINode[m_nOnCloseDevAll_Curr_Index].bConnect)
		{
			theMmsApi->InitUnLinkDeviceFuncPara(m_nOnCloseDevAll_Curr_Index, FALSE, TRUE);
			theMmsApi->CallFirstFunc(m_nOnCloseDevAll_Curr_Index);
			break;
		}

		m_nOnCloseDevAll_Curr_Index++;

		if (m_nOnCloseDevAll_Curr_Index >= nDeviceCount)
		{
			break;
		}
	}

	if (m_nOnCloseDevAll_Curr_Index >= nDeviceCount)
	{
		m_nOnCloseDevAll_Curr_Index = -1;
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("断开全部链接操作完成"));
	}
*/
}

void CMmsEngineAppWnd::OnCloseDevAll_CloseNext()
{
/*
	if (m_nOnCloseDevAll_Curr_Index == -1)
	{
		return;
	}

	m_nOnCloseDevAll_Curr_Index++;

	long nDeviceCount = theMmsApi->HasDevice();

	if (m_nOnCloseDevAll_Curr_Index >= nDeviceCount)
	{
		m_nOnCloseDevAll_Curr_Index = -1;
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("断开全部链接操作完成"));
		return;
	}

	OnCloseDevAll_CloseCurr();
*/
}

void CMmsEngineAppWnd::OnReadDirDevAll_DirCurr()
{

}

void CMmsEngineAppWnd::OnReadDirDevAll_DirNext()
{
	m_nReadDirDevAll_Curr_Index++;

}

/*
void CMmsEngineAppWnd::OnCloseDevAll()
{
	long nDeviceCount = theMmsApi->HasDevice();

	if (nDeviceCount>0)
	{
		nDeviceCount--;
	}

	for (long nDevIndex = 0;nDevIndex<nDeviceCount;nDevIndex++)
	{
		if (pACSINode[nDevIndex].bConnect)
		{
			theMmsApi->InitUnLinkDeviceFuncPara(nDevIndex, FALSE, TRUE);
			theMmsApi->CallFirstFunc(nDevIndex);
		}

		Sleep(100);
	}
}
*/

LRESULT CMmsEngineAppWnd::OnDisConnAllDev(WPARAM wParam,LPARAM lParam)
{
/*
	long nDeviceCount = theMmsApi->HasDevice();

	if (nDeviceCount>0)
	{
		nDeviceCount--;
	}

	CTickCount32 oTick;

	for (long nDevIndex = 0;nDevIndex<nDeviceCount;nDevIndex++)
	{
		if (pACSINode[nDevIndex].bConnect)
		{
			theMmsApi->InitUnLinkDeviceFuncPara(nDevIndex, FALSE, TRUE);
			theMmsApi->CallFirstFunc(nDevIndex);
		}

		oTick.DoEvents(100);
	}
*/
	return 0;
}

void CMmsEngineAppWnd::Create_ReadAllDeviceRcdDir_Thread()
{
/*
	if (m_pReadAllDeviceRcdDir != NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("正在读全部装置的录波文件目录"));
		return;
	}

	m_pReadAllDeviceRcdDir = AfxBeginThread(ReadAllDeviceRcdDir_Thread, (LPVOID)this);
	m_pReadAllDeviceRcdDir->m_bAutoDelete = TRUE;
*/
}

UINT CMmsEngineAppWnd::ReadAllDeviceRcdDir_Thread(LPVOID pParam)
{
/*
	CMmsEngineAppWnd *pMainFrame = (CMmsEngineAppWnd*)pParam;
	pMainFrame->ReadAllDeviceRcdDir_Thread_Func();
*/
	return 0;
}

void CMmsEngineAppWnd::ReadAllDeviceRcdDir_Thread_Func()
{
/*
	theMmsApi->ExitAllFunc();

	Sleep(1000);

	long nReadRcdAllDev[MAX_DEVICE];
	ZeroMemory(nReadRcdAllDev, sizeof(long)*MAX_DEVICE);
	long nDeviceCount = theMmsApi->HasDevice();
	CString strOutPutMsg;
	strOutPutMsg.Format(_T("总计%ld台装置,开始读取各装置录波目录;"),nDeviceCount);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, strOutPutMsg);

	if (nDeviceCount>0)
	{
		nDeviceCount--;

		if (nDeviceCount> MAX_DEVICE)
		{
			nDeviceCount = MAX_DEVICE;
		}
	}

	long nIndex = 0;
	BOOL bCanEnd = FALSE;
	CTickCount32 oTick;
	long nCurrReadIndex = -1;
	m_nReadDirDevAll_Curr_Index = 0;

	while (TRUE)
	{
		bCanEnd = TRUE;

		if (nCurrReadIndex == m_nReadDirDevAll_Curr_Index)
		{//还在读同一个装置的录波文件目录
			bCanEnd = FALSE;

			if (oTick.GetTickCountLong(FALSE) >= 10000)
			{//超时了10秒，则结束
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("读装置%d录波目录超时，开始读下一个"), nCurrReadIndex);
				nReadRcdAllDev[nCurrReadIndex] = 1;
			}
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("正在读装置%d录波目录"), nCurrReadIndex);
				Sleep(100);//zhouhj20190610 将停止时间缩短，以缩短读取录波目录的等待时间 之前为1000
				continue;
			}
		}
		else
		{
			if (nCurrReadIndex != -1)
			{
				nReadRcdAllDev[nCurrReadIndex] = 1;
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("读装置%d录波目录结束"), nCurrReadIndex);
			}
		}

		for (nIndex=0; nIndex<nDeviceCount; nIndex++)
		{
			if (!pACSINode[nIndex].bConnect)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("装置%d没有连接成功"), nIndex);
				continue;
			}

			if (theMmsApi->m_oFuncParamEx[nIndex].m_bExitFunc)
			{//还没有退出通讯操作，则等待
				bCanEnd = FALSE;
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("装置%d没有退出通讯操作，等待"), nIndex);
				continue;
			}

			if (nReadRcdAllDev[nIndex] == 1)
			{//完成
				continue;
			}

			bCanEnd = FALSE;
			m_nReadDirDevAll_Curr_Index = nIndex;
			nCurrReadIndex = nIndex;
			oTick.Enter();

			theMmsApi->InitGetFileDir(nCurrReadIndex, _T("/COMTRADE/"),TRUE);
			theMmsApi->CallFirstFunc(nCurrReadIndex);

			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("开始读装置%d录波目录"), nCurrReadIndex);
			break;
		}

		if (bCanEnd)
		{
			break;
		}
	}

	m_pReadAllDeviceRcdDir = NULL;
	PostMessage(WM_SAVE_ALL_DEVICES_RCD_FILES ,NULL,NULL);
//	theMmsApi->SaveAllMmsDevicesRcdFiles();
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("读全部装置的录波文件目录完成"));
*/
}

LRESULT CMmsEngineAppWnd::OnReadRcdAllDev(WPARAM wParam,LPARAM lParam)
{
/*
	long nUseLastRcdFiles = wParam;

	if (nUseLastRcdFiles == 1)
	{
		if (theMmsApi->ReadAllMmsDevicesRcdFilesFromFile())
		{
			return 0;
		}
	}

	Create_ReadAllDeviceRcdDir_Thread();
*/	
	return 0;
}


/*
void CMmsEngineAppWnd::OnResetDev()
{
	CPpMmsEngineView *pView = (CPpMmsEngineView *)theMmsApi->m_pEngineView;
	ASSERT (pView != NULL);
	ACSI_NODE *pDevice = theMmsApi->GetCurrSelDevice();
	
	if (pDevice == NULL)
	{
		return;
	}

	enter_u_mvl_rpt_CriticSection();
	pDevice->nReportBeginIndex = pDevice->nCurrReportIndex;
	free_u_mvl_rpt_CriticSection();

	if (!g_bResetOnlyClearReport)
	{
		theMmsApi->ResetDevice(pView->m_nMmsDeviceIndex,  0);
		theMmsApi->CallFirstFunc(pView->m_nMmsDeviceIndex);
	}

	theMmsApi->m_pMainWnd->PostMessage(WM_PROCEDURE_RESET, pView->m_nMmsDeviceIndex, pView->m_nMmsDeviceIndex);
}
*/

BOOL CMmsEngineAppWnd::StartTripInforRpt(CFuncParamEx *pFuncParaEx,const CString &strSleDsPath,const CString &strLDType)
{
/*
	long nDevIndex = pFuncParaEx->get_DevIndex();
// 	pFuncParaEx->m_nConnDevIndex = theMmsApi->m_oFuncParamEx[nDevIndex].m_nConnDevIndex;
// 	pFuncParaEx->m_bEnaRpt = theMmsApi->m_oFuncParamEx[nDevIndex].m_bEnaRpt;
	ACSI_NODE *pACSI = &pACSINode[nDevIndex];
	long nLDIndex = 0;
	long nDataSetIndex = 0;
	CString strLDName,strDataSetName;
	LD_NODE *pLD_NODE = NULL;

//	CLogPrint::LogFormatString(XLOGLEVEL_TRACE ,_T("开始启动第%d台装置,逻辑设备 %s,数据集%s 的报告"),nDevIndex,strLDType,strSleDsPath);

	for (nLDIndex = 0;nLDIndex<pACSI->numLD;nLDIndex++)
	{
		pLD_NODE = &pACSI->LD[nLDIndex];
		strLDName.Format("%s",pLD_NODE->LDName);
		strLDName.MakeUpper();

		if (strLDName.Find(strLDType) != -1)
		{
			break;
		}
	}

	if (nLDIndex == pACSI->numLD)
	{
		return SD_SUCCESS;
	}
	
	LD_DATASET_INFO *pDs = NULL;

	for (nDataSetIndex = 0;nDataSetIndex<pLD_NODE->numDaSet;nDataSetIndex++)
	{
		pDs = &pLD_NODE->DataInfo[nDataSetIndex];
		strDataSetName.Format("%s",pDs->DataSetID);
		strDataSetName.MakeUpper();

		if (strDataSetName.Find(strSleDsPath) != -1)
		{
			break;
		}
	}

	if (nDataSetIndex == pLD_NODE->numDaSet)
	{
		return SD_SUCCESS;
	}

	pFuncParaEx->set_RptGI(TRUE);
	pFuncParaEx->set_LDvIndex(nLDIndex);
	pFuncParaEx->set_DSID(nDataSetIndex);
	pFuncParaEx->set_BrcbIndex(pFuncParaEx->m_nConnDevIndex);
	pFuncParaEx->set_FuncID(FuncID_StartRpt);

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE ,_T("开始启动第%d台装置,逻辑设备 %s,数据集%s 的报告"),nDevIndex,strLDType,strSleDsPath);

	ST_RET nRet = SD_FAILURE;
	nRet = theMmsApi->MMS_StartDevRpt(pFuncParaEx);
	pFuncParaEx->set_FuncID(FuncID_TestProc);

	if (theMmsApi->m_pMmsEngineRpcMngr != NULL)
	{
		theMmsApi->m_pMmsEngineRpcMngr->OnAloneOperCmdFinish((WPARAM)pFuncParaEx, nRet);
	}

	return nRet;
*/
	return 0;
}

BOOL CMmsEngineAppWnd::StopTripInforRpt(CFuncParamEx *pFuncParaEx,const CString &strSleDsPath,const CString &strLDType)
{
/*
	long nDevIndex = pFuncParaEx->get_DevIndex();
	ACSI_NODE *pACSI = &pACSINode[nDevIndex];
	long nLDIndex = 0;
	long nDataSetIndex = 0;
	CString strLDName,strDataSetName;
	LD_NODE *pLD_NODE = NULL;

	//	CLogPrint::LogFormatString(XLOGLEVEL_TRACE ,_T("开始启动第%d台装置,逻辑设备 %s,数据集%s 的报告"),nDevIndex,strLDType,strSleDsPath);

	for (nLDIndex = 0;nLDIndex<pACSI->numLD;nLDIndex++)
	{
		pLD_NODE = &pACSI->LD[nLDIndex];
		strLDName.Format("%s",pLD_NODE->LDName);
		strLDName.MakeUpper();

		if (strLDName.Find(strLDType) != -1)
		{
			break;
		}
	}

	if (nLDIndex == pACSI->numLD)
	{
		return SD_SUCCESS;
	}

	LD_DATASET_INFO *pDs = NULL;

	for (nDataSetIndex = 0;nDataSetIndex<pLD_NODE->numDaSet;nDataSetIndex++)
	{
		pDs = &pLD_NODE->DataInfo[nDataSetIndex];
		strDataSetName.Format("%s",pDs->DataSetID);
		strDataSetName.MakeUpper();

		if (strDataSetName.Find(strSleDsPath) != -1)
		{
			break;
		}
	}

	if (nDataSetIndex == pLD_NODE->numDaSet)
	{
		return SD_SUCCESS;
	}

	pFuncParaEx->set_RptGI(TRUE);
	pFuncParaEx->set_LDvIndex(nLDIndex);
	pFuncParaEx->set_DSID(nDataSetIndex);
	pFuncParaEx->set_BrcbIndex(pFuncParaEx->m_nConnDevIndex);
	pFuncParaEx->set_FuncID(FuncID_StopRpt);

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE ,_T("开始停止第%d台装置,逻辑设备 %s,数据集%s 的报告"),nDevIndex,strLDType,strSleDsPath);

	ST_RET nRet = SD_FAILURE;
	nRet = theMmsApi->MMS_StopDevRpt(pFuncParaEx);

	if (theMmsApi->m_pMmsEngineRpcMngr != NULL)
	{
		theMmsApi->m_pMmsEngineRpcMngr->OnAloneOperCmdFinish((WPARAM)pFuncParaEx, nRet);
	}

	return nRet;
*/
	return 0;
}

void CMmsEngineAppWnd::PostDeviceCommCmdMessage(WPARAM wParam, LPARAM lParam)
{
	CFuncParamEx *pFuncParaEx = (CFuncParamEx*) wParam;
	LONG nFuncID = pFuncParaEx-> get_FuncID();

	ACSI_NODE *pACSI_NODE = &pACSINode[pFuncParaEx->get_DevIndex()];
	CPoMmsDevice *pMmsDevice = (CPoMmsDevice*)pACSI_NODE->pRefDevice;

	if (pACSI_NODE->nWriteErrorCount > 0)
	{
		pACSI_NODE->nWriteErrorCount = 0;
		//PostDeviceSysMessage(pFuncParaEx->get_DevIndex() ,engineCommError);
		pMmsDevice->mms_PostDeviceCommCmdMessage(pACSI_NODE, nFuncID, lParam);
		return;
	}
	else
	{
		if (pMmsDevice != NULL)
		{
			pMmsDevice->mms_PostDeviceCommCmdMessage(pACSI_NODE, nFuncID, lParam);
		}
	}

	//CString strMsg;
	//strMsg.Format(g_sLangTxt_SendCommMsg/*_T("发送通讯消息：wParam=%d  lParam=%d")*/, nFuncID, lParam);
	//theMmsApi->OutputPrintMsg(strMsg);
}

void CMmsEngineAppWnd::PostDeviceSysMessage(WPARAM wParam, LPARAM lParam)
{
	int nDeviceIndex = wParam;

	ACSI_NODE *pACSI_NODE = &pACSINode[nDeviceIndex];
	CPoMmsDevice *pMmsDevice = (CPoMmsDevice*)pACSI_NODE->pRefDevice;

	if (pMmsDevice != NULL)
	{
		pMmsDevice->mms_PostDeviceSysMessage(pACSI_NODE, wParam, lParam);
	}

	//CString strMsg;
	//strMsg.Format(g_sLangTxt_SendSySMsg/*_T("发送系统消息：wParam=%d  lParam=%d")*/, wParam, lParam);
	//theMmsApi->OutputPrintMsg(strMsg);
}

void CMmsEngineAppWnd::PostDeviceEventMessage(WPARAM wParam, LPARAM lParam)
{
	CFuncParamEx *pFuncParaEx = (CFuncParamEx*) wParam;

	ACSI_NODE *pACSI_NODE = &pACSINode[pFuncParaEx->get_DevIndex()];
	CPoMmsDevice *pMmsDevice = (CPoMmsDevice*)pACSI_NODE->pRefDevice;

	if (pMmsDevice != NULL)
	{
		pMmsDevice->mms_PostDeviceEventMessage(pACSI_NODE, lParam, lParam);
	}
}

LRESULT CMmsEngineAppWnd::OnMmsCmdFinish_View(WPARAM wParam,LPARAM lParam)
{
	CFuncParamEx *pFuncParaEx = (CFuncParamEx*) wParam;
	CString strMsg;
	BOOL bIsClientCmd = pFuncParaEx->is_ClientCmd();
	LONG nFuncID = pFuncParaEx-> get_FuncID();
	ACSI_NODE *pDevice = &pACSINode[pFuncParaEx->get_DevIndex()];
	//ACSI_NODE *pDevice = theMmsApi->get_DevACSI_NODEPtr(pFuncParaEx);

	switch(nFuncID)
	{
	case FuncID_Link:
		if (lParam==SD_SUCCESS)
		{
			acsi_ctrl_table[pFuncParaEx->get_DevIndex()].bShow = TRUE;
			acsi_ctrl_table[pFuncParaEx->get_DevIndex()].bConnect = TRUE;

			strMsg.Format(_T("和装置%d联机成功."),pFuncParaEx->get_DevIndex());
			//theMmsApi->OutputPrintMsg(strMsg/*g_sLangTxt_ConnectSucc*/);//"和装置联机成功.");
		}
		else
		{
			strMsg.Format(_T("和装置%d联机失败【Error】."),pFuncParaEx->get_DevIndex());
			//theMmsApi->OutputPrintMsg(strMsg/*g_sLangTxt_ConnectFail*/);//"和装置联机失败【Error】.");
		}

		mms_UpdateDeviceState(pDevice);

		break;

	case FuncID_UnLink:
		if (lParam==SD_SUCCESS)
		{
			strMsg.Format(_T("和装置%d断开连接成功."),pFuncParaEx->get_DevIndex());
			//theMmsApi->OutputPrintMsg(strMsg/*g_sLangTxt_DisConnectSucc*/);//"和装置断开连接成功.");
		}
		else
		{
			strMsg.Format(_T("和装置%d断开连接失败【Error】."),pFuncParaEx->get_DevIndex());
			//theMmsApi->OutputPrintMsg(strMsg/*g_sLangTxt_DisConnectFail*/);//"和装置断开连接失败【Error】.");
		}

		theMmsApi->OnUnlink(pFuncParaEx);
		mms_UpdateDeviceState(pDevice);
//		OnCloseDevAll_CloseNext();

		break;

	case FuncID_Read:
	case FuncID_Read_SET:
		if (lParam==SD_SUCCESS)
		{
		}
		else
		{
			//strMsg.Format(_T("读取装置%d数据集失败【Error】."),pFuncParaEx->get_DevIndex());
			//theMmsApi->OutputPrintMsg(strMsg/*g_sLangTxt_RdDatasetFail*/);//"读数据集失败【Error】.");
		}

		ResetWriteFailErrorCode();//在读取数据操作后，将写失败的原因码值复归为-1 因为原因码值可能为0，此处设置为-1为复归值
		break;

	case FuncID_ReadDir:
		if (lParam==SD_SUCCESS)
		{
			PXMMS_FILE_SYS_OBJ pFileDir = &pDevice->FileDir;

			if (pFileDir->readfailed == 1)
			{
				m_nReadDirFailTimes++;
				//strMsg.Format(_T("读取装置%d录波文件目录失败."),pFuncParaEx->get_DevIndex());
				//theMmsApi->OutputPrintMsg(strMsg/*g_sLangTxt_ReadRecorDirFail*/);//"读录波文件目录失败.");
				//OnReadDirDevAll_DirCurr();
			}
			else
			{
				//strMsg.Format(_T("读取装置%d录波文件目录成功."),pFuncParaEx->get_DevIndex());
				//theMmsApi->OutputPrintMsg(strMsg/*g_sLangTxt_ReadRecordDirSucc*/);//"读录波文件目录成功.");
				//OnReadDirDevAll_DirNext();
			}

			OnReadDirDevAll_DirNext();
		}
		else
		{
			m_nReadDirFailTimes++;
			//strMsg.Format(_T("读取装置%d录波文件目录失败."),pFuncParaEx->get_DevIndex());
			//theMmsApi->OutputPrintMsg(strMsg/*g_sLangTxt_ReadRecorDirFail*/);//"读录波文件目录失败.");
			//OnReadDirDevAll_DirCurr();
			OnReadDirDevAll_DirNext();
		}
		break;
	case FuncID_ReadFile:
		if (lParam==SD_SUCCESS)
		{
			//strMsg.Format(_T("读取装置%d录波文件成功."),pFuncParaEx->get_DevIndex());
			//theMmsApi->OutputPrintMsg(strMsg);
		}
		else
		{
			//strMsg.Format(_T("读取装置%d录波文件失败."),pFuncParaEx->get_DevIndex());
			//theMmsApi->OutputPrintMsg(strMsg);
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

		theMmsApi->SetReportRet(pFuncParaEx,lParam==SD_SUCCESS, TRUE);
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

		theMmsApi->SetReportRet(pFuncParaEx,lParam==SD_SUCCESS, FALSE);
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

			if (/*theMmsApi->IsAutoTestMode() &&*/ pFuncParaEx->IsConnectDevice())//  周宏军  20200421  无论是否自动测试模式下，都自动读设备
			{//自动测试模式下，枚举设备的逻辑设备成功，则继续枚举设备的其他参数

				if (pDevice->nHasDeviceModel == 1)
				{//如果已经有了设备数据模型，则不需要再读取
					//theMmsApi->SetsConnectDevice(FALSE);
					//PostDeviceSysMessage(engineConnectDeviceSuccessful, engineConnectDeviceSuccessful);
				}
				else
				{
					int nDeviceIndex = pFuncParaEx->get_DevIndex();
					int nLDIndex  = pFuncParaEx->get_LDvIndex();
					int nDSIndex = pFuncParaEx->get_DSID();

					if(pACSINode[nDeviceIndex].LD[0].mms_data_node != NULL)
					{
						theMmsApi->InitReadDevice(nDeviceIndex,FALSE);
					}
					else
					{
						theMmsApi->InitReadDeviceFuncParas(nDeviceIndex, TRUE,FALSE);
					}

					theMmsApi->InitCallReportFlagDefault(nDeviceIndex);

					if (nDSIndex>= 0)
					{
					theMmsApi->InitCallReportFuncParas(nDeviceIndex, nLDIndex, nDSIndex,TRUE, FALSE);
					}
				}
				//return 0;
			}
		}
		break;
	case FuncID_SetSGNum:
		if (lParam!=SD_SUCCESS)
		{
			//strMsg.Format(g_sLangTxt_SetFixedValueRegionFail/*_T("【%d】设置当前定值运行区号%d失败【Error】")*/,pFuncParaEx->get_DevIndex(), pFuncParaEx->get_SGID());
			//theMmsApi->OutputPrintMsg(strMsg);
		}
		else
		{
			//strMsg.Format(g_sLangTxt_SetFixedValueRegion/*_T("设置当前运行定值区为%d")*/, pFuncParaEx->get_SGID());
			//theMmsApi->OutputPrintMsg(strMsg);
		}
		break;
	case FuncID_EnumLD:
		if (lParam==SD_SUCCESS)
		{
			int nDeviceIndex = pFuncParaEx->get_DevIndex();
			// 初始化装置树
			//theMmsApi->OutputPrintMsg(g_sLangTxt_ReadDeviceDirSucc);//"枚举装置目录成功.");
		}
		else
		{
			//theMmsApi->OutputPrintMsg(g_sLangTxt_ReadDeviceDirFail);//"枚举装置目录失败【Error】.");
		}
		break;
	case FuncID_TestProc:
		if (lParam==SD_SUCCESS)
		{
			////theMmsApi->OutputPrintMsg("网络连接正常.");
		}
		else
		{
			//theMmsApi->OutputPrintMsg(g_sLangTxt_NetDisConnect);//"网络连接断开.");
			theMmsApi->OnUnlink(pFuncParaEx);
		}

		break;
	case FuncID_SetSENum:
		if (lParam==SD_SUCCESS)
		{
			//strMsg.Format(g_sLangID_EditFixedValueRegionSucc/*_T("切换编辑定值区%d成功")*/, pFuncParaEx->get_SEID());
		}
		else
		{
			//strMsg.Format(g_sLangID_EditFixedValueRegionFail/*_T("切换编辑定值区%d失败【Error】")*/, pFuncParaEx->get_SEID());
		}

		//theMmsApi->OutputPrintMsg(strMsg);

		break;
	case FuncID_CnfSetSE:
		if (lParam==SD_SUCCESS)
		{
			//strMsg.Format(g_sLangID_SolidFixedValueRegionSucc/*_T("固化定值区%d定值成功")*/, pFuncParaEx->get_SEID());
		}
		else
		{
			//strMsg.Format(g_sLangID_SolidFixedValueRegionFail/*_T("固化定值区%d定值失败【Error】")*/, pFuncParaEx->get_SEID());
		}

		//theMmsApi->OutputPrintMsg(strMsg);

		break;
	case FuncID_CtrlWrite:
	case FuncID_CtrlWriteOne:
		if (lParam==SD_SUCCESS)
		{
			//strMsg = g_sLangTxt_CtrlWriteSucc/*_T("控制写成功")*/;
			ResetWriteFailErrorCode();
		}
		else
		{
			//strMsg = g_sLangTxt_CtrlWriteFail/*_T("控制写失败【Error】")*/;
		}

		//theMmsApi->OutputPrintMsg(strMsg);

		break;

	case FuncID_Reset:
		if (lParam==SD_SUCCESS)
		{
			//strMsg = g_sLangTxt_DeviceReturnSucc/*_T("装置复归成功")*/;
		}
		else
		{
			//strMsg = g_sLangTxt_DeviceReturnFail/*_T("装置复归失败【Error】")*/;
		}

		//theMmsApi->OutputPrintMsg(strMsg);
		break;

	case FuncID_UploadFile:
		if (lParam==SD_SUCCESS)
		{
			//strMsg = _T("使用UPLOAD命令上传文件成功");
		}
		else
		{
			//strMsg = _T("UPLOAD上传文件失败【Error】");
		}

		//theMmsApi->OutputPrintMsg(strMsg);
		break;
	case FuncID_ReadDevice:
		if (lParam==SD_SUCCESS)
		{
			//strMsg = _T("读取装置成功");
		}
		else
		{
			//strMsg = _T("读取装置失败【Error】");
		}

		//theMmsApi->OutputPrintMsg(strMsg);
		break;
	case FuncID_DvmEnum:
		if (lParam==SD_SUCCESS)
		{
			//strMsg = _T("枚举Dvm模型成功");
		}
		else
		{
			//strMsg = _T("枚举Dvm模型失败【Error】");
		}

		//theMmsApi->OutputPrintMsg(strMsg);
		break;
	}

	return 0;
}

void CMmsEngineAppWnd::ResetWriteFailErrorCode()
{
	g_nCurErrorCode = -1;//在控制写成功后，此处设置为-1为复归值
	g_nCurErrorClass = -1;
	g_nCurErrorInforRpt = -1;
}


void CMmsEngineAppWnd::OnMmsCmdAllFinish_FuncID_XLink(CFuncParamEx *pFuncParaEx)
{
	ACSI_NODE *pDevice = &pACSINode[pFuncParaEx->get_DevIndex()];
	BOOL bIsClientCmd = pFuncParaEx->is_ClientCmd();

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

LRESULT CMmsEngineAppWnd::OnMmsCmdAllFinish_AutoTest(LONG nFuncID, WPARAM wParam,LPARAM lParam)
{
	CFuncParamEx *pFuncParaEx = (CFuncParamEx*) wParam;
	BOOL bIsClientCmd = pFuncParaEx->is_ClientCmd();

	if ( ! theMmsApi->IsFuncsAllFinish(pFuncParaEx->get_DevIndex()) )
	{
// 		if (FuncID_Link== nFuncID || FuncID_UnLink == nFuncID)// || FuncID_EnumLD == wParam)
// 		{
// 			OnMmsCmdAllFinish_FuncID_XLink(pFuncParaEx);
// 			return 0;
// 		}
		return 0;
	}

	if (FuncID_Link== nFuncID || FuncID_UnLink == nFuncID)// || FuncID_EnumLD == wParam)
	{
		OnMmsCmdAllFinish_FuncID_XLink(pFuncParaEx);
	}
	else if (FuncID_ReadDevice == nFuncID)
	{
		pFuncParaEx->SetsConnectDevice(FALSE);
		PostDeviceCommCmdMessage((WPARAM)pFuncParaEx, engineCommFinish);
		PostDeviceEventMessage((WPARAM)pFuncParaEx, engineDvmEnumFinish);
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

LRESULT CMmsEngineAppWnd::OnMmsCmdFinish_Error(WPARAM wParam,LPARAM lParam)
{
	if (g_bMmsEngineDebugMode)
	{
		return 0;
	}

	CFuncParamEx *pFuncParaEx = (CFuncParamEx*) wParam;
	LONG nFuncID = pFuncParaEx-> get_FuncID();

	if (!theMmsApi->IsFuncsAllFinish(pFuncParaEx->get_DevIndex()))
	{
		if (nFuncID == FuncID_TestProc)
		{
			PostDeviceSysMessage(pFuncParaEx->get_DevIndex() ,engineConnectDeviceFailed);
		}	
		else
		{
			ACSI_NODE *pACSI_NODE = &pACSINode[pFuncParaEx->get_DevIndex()];

			if (!pACSI_NODE->bTestLinkState)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Error CMD Exec:CMD=%d DV=%d  LD=%d  DS=%d"), pFuncParaEx->get_FuncID()
					, pFuncParaEx->get_DevIndex(), pFuncParaEx->get_LDvIndex(), pFuncParaEx->get_DSID());
				m_nCallFuncRetryTimes = 0;
				theMmsApi->OnCallFuncError(pFuncParaEx->get_DevIndex());
				theMmsApi->ProgDlg_StopProgress(pFuncParaEx->get_DevIndex());	
				PostDeviceCommCmdMessage((WPARAM)pFuncParaEx, engineCommError);
				//PostDeviceSysMessage(pFuncParaEx->get_DevIndex() ,engineCommError);

				pFuncParaEx->SetsConnectDevice(FALSE);
			}
			else
			{
				PostDeviceCommCmdMessage((WPARAM)pFuncParaEx, engineCommFinish);
				theMmsApi->OnCallFuncError(pFuncParaEx->get_DevIndex());
			}

			theMmsApi->ProgDlg_StopProgress(pFuncParaEx->get_DevIndex());
		}
	}
	else
	{
		theMmsApi->OnCallFuncError(pFuncParaEx->get_DevIndex());
	}

	return 0;
}

LRESULT CMmsEngineAppWnd::OnMmsCmdFinish(WPARAM wParam,LPARAM lParam)
{
	CFuncParamEx *pFuncParaEx = (CFuncParamEx*) wParam;
	CString strMsg;
	BOOL bIsClientCmd = pFuncParaEx->is_ClientCmd();
	LONG nFuncID = pFuncParaEx-> get_FuncID();

	OnMmsCmdFinish_View(wParam, lParam);

	if (lParam==SD_SUCCESS)
	{
		m_nCallFuncRetryTimes = 0;

		if (nFuncID == FuncID_TestProc)
		{
			return 0;
		}

		ACSI_NODE *pDevice = theMmsApi->get_DevACSI_NODEPtr(pFuncParaEx);

			theMmsApi->CallNextFunc(pFuncParaEx->get_DevIndex());
			OnMmsCmdAllFinish_AutoTest(nFuncID, wParam, lParam);				
	}
	else
	{
		OnMmsCmdFinish_Error(wParam, lParam);
	}

	return 0;
}

LRESULT CMmsEngineAppWnd::SaveAllMmsDevicesRcdFiles(WPARAM wParam,LPARAM lParam)
{
	return 0;
}

LRESULT CMmsEngineAppWnd::OnMmsReport(WPARAM wParam,LPARAM lParam)
{
	//wParam = nAcsi + (numDsVar << 16);//
	//lParam = ((unsigned short)pACSINode[nAcsi].nCurrReportIndex) + (((unsigned short)nCurrRptIndex) << 16);
	int nAcsi = wParam & 0x0000FFFF;
	ACSI_NODE *pACSI_NODE = &pACSINode[nAcsi];
	CPoMmsDevice *pMmsDevice = (CPoMmsDevice*)pACSI_NODE->pRefDevice;

	if (pMmsDevice != NULL)
	{
		pMmsDevice->mms_PostMmsReportMessage(pACSI_NODE, wParam, lParam);
	}

	return 0;
}

LRESULT CMmsEngineAppWnd::OnReset(WPARAM wParam,LPARAM lParam)
{
	return 0;
}

LRESULT CMmsEngineAppWnd::OnConnectAllDevice(WPARAM wParam,LPARAM lParam)
{
	return 0;
}

