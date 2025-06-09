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

	//����װ������������������Ľṹ��
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

		//�ҵ�һ��û�����������MMSװ��
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

//	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("��ʼStartAllDevsRpt_Func�߳�ѭ��"));

	while (TRUE)
	{
		bCanEnd = TRUE;

		for (long nDev = 0; nDev < nDeviceCount;nDev++)
		{
			//ÿ��װ��һ�����������̣߳���ǰװ�õ����������̻߳�û�н������ȴ��������һ��װ�õ��ж�
			if (pStartRptParas[nDev].pThread != NULL)
			{
				bCanEnd = FALSE; //�̻߳�û�н��������ܽ����ܵ��߳�
				oTickCount.DoEvents(100);
				continue;
			}

			pMstmSlnDv = (CDvmData *)pMstmSlnDevices->GetAtIndex(nDev);

			//�ҵ�һ��û�����������MMSװ��
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
				{// ��ʹ�ܱ���
					continue;
				}

				if (!acsi_ctrl_table[nMmsDevIndex].bConnect || (acsi_ctrl_table[nMmsDevIndex].pnet_info == NULL ) )
				{//δ���ӣ���ʾ�̲߳��ܽ���
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
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�˳�StartAllDevsRpt_Func�߳�ѭ��"));
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

		//��ʱ
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
// 					StartTripInforRpt(pFuncEx,strSleDsPath,strSelLDName);//zhouhj ���ڶ�װ�������⴦���̶������ɹ�ȥ��������
// 
// 					//mms_FindByDeviceIndexForStartRpt
// 					//����һ��û�����������װ��
// 					//����InitFuncPara����ģʽ����������
// 					//sleep��1000����
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

	//����װ������������������Ľṹ��
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

		//�ҵ�һ��û�����������MMSװ��
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
			//ÿ��װ��һ�����������̣߳���ǰװ�õ����������̻߳�û�н������ȴ��������һ��װ�õ��ж�
			if (pStartRptParas[nDev].pThread != NULL)
			{
				bCanEnd = FALSE; //�̻߳�û�н��������ܽ����ܵ��߳�
				oTickCount.DoEvents(100);
				continue;
			}

			pMstmSlnDv = (CDvmData *)pMstmSlnDevices->GetAtIndex(nDev);

			//�ҵ�һ��û�����������MMSװ��
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
				{// ��ֹͣ����
					continue;
				}

				if (!acsi_ctrl_table[nMmsDevIndex].bConnect || (acsi_ctrl_table[nMmsDevIndex].pnet_info == NULL ) )
				{//δ���ӣ�Ĭ�ϱ���δ����������ر�
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
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�˳�StopAllDevsRpt_Func�߳�ѭ��"));
			break;
		}

		//��ʱ
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

	//zhouhj ���ڶ�װ�������⴦���̶������ɹ�ȥ��������
	CFuncParamEx *pFuncParaEx = pStartRptPara->pFuncParaEx;
	long nDevIndex = pFuncParaEx->get_DevIndex();

	pFuncParaEx->set_LDvIndex(nDevIndex);
	pFuncParaEx->set_FuncID(FuncID_Link);

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE ,_T("��ʼ���ӵ�%d̨װ��"),nDevIndex);

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

	//zhouhj ���ڶ�װ�������⴦���̶������ɹ�ȥ��������
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

LRESULT CMmsEngineAppWnd::OnOperAllDevsRpt(WPARAM wParam,LPARAM lParam)//����2����CDvmData ��m_strID���ݶ�Ӧ���ݼ����ƣ�LDĬ�Ϲ̶�ΪPROT
{
/*
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�յ�WM_OPER_ALL_DEVS_REPORT��Ϣ"));

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

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("����OnStartAllDevsRpt_Thread�߳�"));

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

//2020-12-22  lijunqing  �ⲿ�������ýӿڣ�����IP
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
	//����װ������������������Ľṹ��
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
			//ÿ��װ��һ�����������̣߳���ǰװ�õ����������̻߳�û�н������ȴ��������һ��װ�õ��ж�
			if (pStartRptParas[nDev].pThread != NULL)
			{
				bCanEnd = FALSE; //�̻߳�û�н��������ܽ����ܵ��߳�
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
			{//���ping��ͨ����������
				continue;
			}

			//�ҵ�һ��û�����ӵ�MMSװ��
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
				{//δ���ӣ���ʾ�̲߳��ܽ���
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
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�˳�LinkAllDevice_Func�߳�ѭ��"));
			break;
		}

		//��ʱ
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
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("�Ͽ�ȫ�����Ӳ������"));
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
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("�Ͽ�ȫ�����Ӳ������"));
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
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("���ڶ�ȫ��װ�õ�¼���ļ�Ŀ¼"));
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
	strOutPutMsg.Format(_T("�ܼ�%ld̨װ��,��ʼ��ȡ��װ��¼��Ŀ¼;"),nDeviceCount);
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
		{//���ڶ�ͬһ��װ�õ�¼���ļ�Ŀ¼
			bCanEnd = FALSE;

			if (oTick.GetTickCountLong(FALSE) >= 10000)
			{//��ʱ��10�룬�����
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("��װ��%d¼��Ŀ¼��ʱ����ʼ����һ��"), nCurrReadIndex);
				nReadRcdAllDev[nCurrReadIndex] = 1;
			}
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("���ڶ�װ��%d¼��Ŀ¼"), nCurrReadIndex);
				Sleep(100);//zhouhj20190610 ��ֹͣʱ�����̣������̶�ȡ¼��Ŀ¼�ĵȴ�ʱ�� ֮ǰΪ1000
				continue;
			}
		}
		else
		{
			if (nCurrReadIndex != -1)
			{
				nReadRcdAllDev[nCurrReadIndex] = 1;
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("��װ��%d¼��Ŀ¼����"), nCurrReadIndex);
			}
		}

		for (nIndex=0; nIndex<nDeviceCount; nIndex++)
		{
			if (!pACSINode[nIndex].bConnect)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("װ��%dû�����ӳɹ�"), nIndex);
				continue;
			}

			if (theMmsApi->m_oFuncParamEx[nIndex].m_bExitFunc)
			{//��û���˳�ͨѶ��������ȴ�
				bCanEnd = FALSE;
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("װ��%dû���˳�ͨѶ�������ȴ�"), nIndex);
				continue;
			}

			if (nReadRcdAllDev[nIndex] == 1)
			{//���
				continue;
			}

			bCanEnd = FALSE;
			m_nReadDirDevAll_Curr_Index = nIndex;
			nCurrReadIndex = nIndex;
			oTick.Enter();

			theMmsApi->InitGetFileDir(nCurrReadIndex, _T("/COMTRADE/"),TRUE);
			theMmsApi->CallFirstFunc(nCurrReadIndex);

			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("��ʼ��װ��%d¼��Ŀ¼"), nCurrReadIndex);
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
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("��ȫ��װ�õ�¼���ļ�Ŀ¼���"));
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

//	CLogPrint::LogFormatString(XLOGLEVEL_TRACE ,_T("��ʼ������%d̨װ��,�߼��豸 %s,���ݼ�%s �ı���"),nDevIndex,strLDType,strSleDsPath);

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

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE ,_T("��ʼ������%d̨װ��,�߼��豸 %s,���ݼ�%s �ı���"),nDevIndex,strLDType,strSleDsPath);

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

	//	CLogPrint::LogFormatString(XLOGLEVEL_TRACE ,_T("��ʼ������%d̨װ��,�߼��豸 %s,���ݼ�%s �ı���"),nDevIndex,strLDType,strSleDsPath);

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

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE ,_T("��ʼֹͣ��%d̨װ��,�߼��豸 %s,���ݼ�%s �ı���"),nDevIndex,strLDType,strSleDsPath);

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
	//strMsg.Format(g_sLangTxt_SendCommMsg/*_T("����ͨѶ��Ϣ��wParam=%d  lParam=%d")*/, nFuncID, lParam);
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
	//strMsg.Format(g_sLangTxt_SendSySMsg/*_T("����ϵͳ��Ϣ��wParam=%d  lParam=%d")*/, wParam, lParam);
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

			strMsg.Format(_T("��װ��%d�����ɹ�."),pFuncParaEx->get_DevIndex());
			//theMmsApi->OutputPrintMsg(strMsg/*g_sLangTxt_ConnectSucc*/);//"��װ�������ɹ�.");
		}
		else
		{
			strMsg.Format(_T("��װ��%d����ʧ�ܡ�Error��."),pFuncParaEx->get_DevIndex());
			//theMmsApi->OutputPrintMsg(strMsg/*g_sLangTxt_ConnectFail*/);//"��װ������ʧ�ܡ�Error��.");
		}

		mms_UpdateDeviceState(pDevice);

		break;

	case FuncID_UnLink:
		if (lParam==SD_SUCCESS)
		{
			strMsg.Format(_T("��װ��%d�Ͽ����ӳɹ�."),pFuncParaEx->get_DevIndex());
			//theMmsApi->OutputPrintMsg(strMsg/*g_sLangTxt_DisConnectSucc*/);//"��װ�öϿ����ӳɹ�.");
		}
		else
		{
			strMsg.Format(_T("��װ��%d�Ͽ�����ʧ�ܡ�Error��."),pFuncParaEx->get_DevIndex());
			//theMmsApi->OutputPrintMsg(strMsg/*g_sLangTxt_DisConnectFail*/);//"��װ�öϿ�����ʧ�ܡ�Error��.");
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
			//strMsg.Format(_T("��ȡװ��%d���ݼ�ʧ�ܡ�Error��."),pFuncParaEx->get_DevIndex());
			//theMmsApi->OutputPrintMsg(strMsg/*g_sLangTxt_RdDatasetFail*/);//"�����ݼ�ʧ�ܡ�Error��.");
		}

		ResetWriteFailErrorCode();//�ڶ�ȡ���ݲ����󣬽�дʧ�ܵ�ԭ����ֵ����Ϊ-1 ��Ϊԭ����ֵ����Ϊ0���˴�����Ϊ-1Ϊ����ֵ
		break;

	case FuncID_ReadDir:
		if (lParam==SD_SUCCESS)
		{
			PXMMS_FILE_SYS_OBJ pFileDir = &pDevice->FileDir;

			if (pFileDir->readfailed == 1)
			{
				m_nReadDirFailTimes++;
				//strMsg.Format(_T("��ȡװ��%d¼���ļ�Ŀ¼ʧ��."),pFuncParaEx->get_DevIndex());
				//theMmsApi->OutputPrintMsg(strMsg/*g_sLangTxt_ReadRecorDirFail*/);//"��¼���ļ�Ŀ¼ʧ��.");
				//OnReadDirDevAll_DirCurr();
			}
			else
			{
				//strMsg.Format(_T("��ȡװ��%d¼���ļ�Ŀ¼�ɹ�."),pFuncParaEx->get_DevIndex());
				//theMmsApi->OutputPrintMsg(strMsg/*g_sLangTxt_ReadRecordDirSucc*/);//"��¼���ļ�Ŀ¼�ɹ�.");
				//OnReadDirDevAll_DirNext();
			}

			OnReadDirDevAll_DirNext();
		}
		else
		{
			m_nReadDirFailTimes++;
			//strMsg.Format(_T("��ȡװ��%d¼���ļ�Ŀ¼ʧ��."),pFuncParaEx->get_DevIndex());
			//theMmsApi->OutputPrintMsg(strMsg/*g_sLangTxt_ReadRecorDirFail*/);//"��¼���ļ�Ŀ¼ʧ��.");
			//OnReadDirDevAll_DirCurr();
			OnReadDirDevAll_DirNext();
		}
		break;
	case FuncID_ReadFile:
		if (lParam==SD_SUCCESS)
		{
			//strMsg.Format(_T("��ȡװ��%d¼���ļ��ɹ�."),pFuncParaEx->get_DevIndex());
			//theMmsApi->OutputPrintMsg(strMsg);
		}
		else
		{
			//strMsg.Format(_T("��ȡװ��%d¼���ļ�ʧ��."),pFuncParaEx->get_DevIndex());
			//theMmsApi->OutputPrintMsg(strMsg);
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

		theMmsApi->SetReportRet(pFuncParaEx,lParam==SD_SUCCESS, TRUE);
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

		theMmsApi->SetReportRet(pFuncParaEx,lParam==SD_SUCCESS, FALSE);
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

			if (/*theMmsApi->IsAutoTestMode() &&*/ pFuncParaEx->IsConnectDevice())//  �ܺ��  20200421  �����Ƿ��Զ�����ģʽ�£����Զ����豸
			{//�Զ�����ģʽ�£�ö���豸���߼��豸�ɹ��������ö���豸����������

				if (pDevice->nHasDeviceModel == 1)
				{//����Ѿ������豸����ģ�ͣ�����Ҫ�ٶ�ȡ
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
			//strMsg.Format(g_sLangTxt_SetFixedValueRegionFail/*_T("��%d�����õ�ǰ��ֵ��������%dʧ�ܡ�Error��")*/,pFuncParaEx->get_DevIndex(), pFuncParaEx->get_SGID());
			//theMmsApi->OutputPrintMsg(strMsg);
		}
		else
		{
			//strMsg.Format(g_sLangTxt_SetFixedValueRegion/*_T("���õ�ǰ���ж�ֵ��Ϊ%d")*/, pFuncParaEx->get_SGID());
			//theMmsApi->OutputPrintMsg(strMsg);
		}
		break;
	case FuncID_EnumLD:
		if (lParam==SD_SUCCESS)
		{
			int nDeviceIndex = pFuncParaEx->get_DevIndex();
			// ��ʼ��װ����
			//theMmsApi->OutputPrintMsg(g_sLangTxt_ReadDeviceDirSucc);//"ö��װ��Ŀ¼�ɹ�.");
		}
		else
		{
			//theMmsApi->OutputPrintMsg(g_sLangTxt_ReadDeviceDirFail);//"ö��װ��Ŀ¼ʧ�ܡ�Error��.");
		}
		break;
	case FuncID_TestProc:
		if (lParam==SD_SUCCESS)
		{
			////theMmsApi->OutputPrintMsg("������������.");
		}
		else
		{
			//theMmsApi->OutputPrintMsg(g_sLangTxt_NetDisConnect);//"�������ӶϿ�.");
			theMmsApi->OnUnlink(pFuncParaEx);
		}

		break;
	case FuncID_SetSENum:
		if (lParam==SD_SUCCESS)
		{
			//strMsg.Format(g_sLangID_EditFixedValueRegionSucc/*_T("�л��༭��ֵ��%d�ɹ�")*/, pFuncParaEx->get_SEID());
		}
		else
		{
			//strMsg.Format(g_sLangID_EditFixedValueRegionFail/*_T("�л��༭��ֵ��%dʧ�ܡ�Error��")*/, pFuncParaEx->get_SEID());
		}

		//theMmsApi->OutputPrintMsg(strMsg);

		break;
	case FuncID_CnfSetSE:
		if (lParam==SD_SUCCESS)
		{
			//strMsg.Format(g_sLangID_SolidFixedValueRegionSucc/*_T("�̻���ֵ��%d��ֵ�ɹ�")*/, pFuncParaEx->get_SEID());
		}
		else
		{
			//strMsg.Format(g_sLangID_SolidFixedValueRegionFail/*_T("�̻���ֵ��%d��ֵʧ�ܡ�Error��")*/, pFuncParaEx->get_SEID());
		}

		//theMmsApi->OutputPrintMsg(strMsg);

		break;
	case FuncID_CtrlWrite:
	case FuncID_CtrlWriteOne:
		if (lParam==SD_SUCCESS)
		{
			//strMsg = g_sLangTxt_CtrlWriteSucc/*_T("����д�ɹ�")*/;
			ResetWriteFailErrorCode();
		}
		else
		{
			//strMsg = g_sLangTxt_CtrlWriteFail/*_T("����дʧ�ܡ�Error��")*/;
		}

		//theMmsApi->OutputPrintMsg(strMsg);

		break;

	case FuncID_Reset:
		if (lParam==SD_SUCCESS)
		{
			//strMsg = g_sLangTxt_DeviceReturnSucc/*_T("װ�ø���ɹ�")*/;
		}
		else
		{
			//strMsg = g_sLangTxt_DeviceReturnFail/*_T("װ�ø���ʧ�ܡ�Error��")*/;
		}

		//theMmsApi->OutputPrintMsg(strMsg);
		break;

	case FuncID_UploadFile:
		if (lParam==SD_SUCCESS)
		{
			//strMsg = _T("ʹ��UPLOAD�����ϴ��ļ��ɹ�");
		}
		else
		{
			//strMsg = _T("UPLOAD�ϴ��ļ�ʧ�ܡ�Error��");
		}

		//theMmsApi->OutputPrintMsg(strMsg);
		break;
	case FuncID_ReadDevice:
		if (lParam==SD_SUCCESS)
		{
			//strMsg = _T("��ȡװ�óɹ�");
		}
		else
		{
			//strMsg = _T("��ȡװ��ʧ�ܡ�Error��");
		}

		//theMmsApi->OutputPrintMsg(strMsg);
		break;
	case FuncID_DvmEnum:
		if (lParam==SD_SUCCESS)
		{
			//strMsg = _T("ö��Dvmģ�ͳɹ�");
		}
		else
		{
			//strMsg = _T("ö��Dvmģ��ʧ�ܡ�Error��");
		}

		//theMmsApi->OutputPrintMsg(strMsg);
		break;
	}

	return 0;
}

void CMmsEngineAppWnd::ResetWriteFailErrorCode()
{
	g_nCurErrorCode = -1;//�ڿ���д�ɹ��󣬴˴�����Ϊ-1Ϊ����ֵ
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

