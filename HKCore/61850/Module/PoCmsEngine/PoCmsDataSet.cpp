// PoCmsDataSet.cpp : 实现文件
//

#include "stdafx.h"
#include "PoCmsDataSet.h"
#include "../../../Module/System/TickCount32.h"
#include "../dlt860/DLT860Engine.h"

#ifndef USE_Old_EngineSystemDefine
#define _use_GetXmlData_file
#endif

// CPoCmsDataSet
CPoCmsDataSet::CPoCmsDataSet()
{
	
}

CPoCmsDataSet::~CPoCmsDataSet()
{
}

CPoCmsDataSet* CPoCmsDataSet::_NewPoCmsDataSet(CMmsDatasetMapTool *pMmsDatasetMapTool)
{
	CPoCmsDataSet *pNew = new CPoCmsDataSet();

	pNew->m_pACSI_NODE = pMmsDatasetMapTool->m_pACSI_NODE;
	pNew->m_pMmsDatasetMapTool = pMmsDatasetMapTool;
	pNew->m_pLD_NODE = NULL;
	pNew->m_pDataset = NULL;
	pNew->m_pRpt = NULL;
	pNew->m_pFileDir = NULL;

	return pNew;
}

BOOL po_cms_GetXmlDataEx_DvmData(CDvmData *pData, ACSI_NODE *pDevice)
{
	if (pData->m_strID ==  ATTRID_TimeGapEnaWrite)//  _T("TimeGapEnaWrite")
	{
		pData->m_strValue.Format(_T("%d"), g_o61850ClientConfig.m_nEnaWriteWait);
	}
	else if (pData->m_strID ==  ATTRID_TimeGapSelExec)//  _T("TimeGapSelExec")
	{
		pData->m_strValue.Format(_T("%d"),g_o61850ClientConfig.m_nEnaWriteWaitAfterSel);
	}
	else if (pData->m_strID == ATTRID_ENA_WRITE_CTRL_TYPE_)
	{
		pData->m_strValue.Format(_T("%ld"), g_o61850ClientConfig.GetCtrlType());
	}
	else if (pData->m_strID == ATTRID_READ_AIN_USE_REPORT_)
	{
		pData->m_strValue.Format(_T("%d"),g_o61850ClientConfig.m_nReadAinUseReport);
	}
	else
	{
			po_GetXmlDataEx_DvmData(pData, pDevice);
	}

	return TRUE;
}

BOOL CPoCmsDataSet::GetXmlDataEx_DvmData(CDvmData *pData)
{
	return po_cms_GetXmlDataEx_DvmData(pData, m_pACSI_NODE);
}

BOOL CPoCmsDataSet::SetXmlData_Data(CDvmData *pData)
{
	if (pData->m_strID ==  ATTRID_TimeGapEnaWrite)//  _T("TimeGapEnaWrite")
	{
		g_o61850ClientConfig.m_nEnaWriteWait = CString_To_long(pData->m_strValue);
	}
	else if (pData->m_strID ==  ATTRID_TimeGapSelExec)//  _T("TimeGapSelExec")
	{
		g_o61850ClientConfig.m_nEnaWriteWaitAfterSel = CString_To_long(pData->m_strValue);
	}
	else if (pData->m_strID ==  ATTRID_TestLinkState)//  _T("LogMmsMsg")
	{
		m_pACSI_NODE->bTestLinkState = CString_To_long(pData->m_strValue);
	}
	else if (pData->m_strID == ATTRID_DVM_NAME_IS_STD)
	{
		g_nDvmNameIsStd = CString_To_long(pData->m_strValue);
	}
	else if (pData->m_strID == ATTRID_ENA_WRITE_CTRL_TYPE_)
	{
		CRemoteDevs *pRemoteDevs = g_o61850ClientConfig.GetRemoteDevs();
		pRemoteDevs->m_nWriteCtrlType = CString_To_long(pData->m_strValue);
	}
	else if (pData->m_strID == ATTRID_READ_AIN_USE_REPORT_)
	{
		g_o61850ClientConfig.m_nReadAinUseReport = CString_To_long(pData->m_strValue);
	}

	return 0;
}
