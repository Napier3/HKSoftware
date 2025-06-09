// PoDataSet.cpp : 实现文件
//

#include "stdafx.h"
#include "PoMmsDataSet.h"
#include "../../../Module/System/TickCount32.h"

#define _use_GetXmlData_file

// CPoMmsDataSet



CPoMmsDataSet::CPoMmsDataSet()
{
	m_pACSI_NODE = NULL;
	m_pLD_NODE = NULL;
	m_pDataset = NULL;
	m_pRpt = NULL;
	m_pFileDir = NULL;
	m_pDvmDatasetMap = NULL;
	m_pDvmDeviceMap  = NULL;
	m_pDvmDataset    = NULL;

	m_pMmsDatasetMapTool = NULL;
	m_pTempNewDataset = NULL;
	m_bTempNewDataset = TRUE;
}

CPoMmsDataSet::~CPoMmsDataSet()
{
	if (m_bTempNewDataset)
	{
		if (m_pTempNewDataset != NULL)
		{
			delete m_pTempNewDataset;
		}
	}
}

CPoMmsDataSet* CPoMmsDataSet::_NewPoDataset(CMmsDatasetMapTool *pMmsDatasetMapTool)
{
	CPoMmsDataSet *pNew = new CPoMmsDataSet();

	pNew->m_pACSI_NODE = pMmsDatasetMapTool->m_pACSI_NODE;
	pNew->m_pMmsDatasetMapTool = pMmsDatasetMapTool;
	pNew->m_pLD_NODE = NULL;
	pNew->m_pDataset = NULL;
	pNew->m_pRpt = NULL;
	pNew->m_pFileDir = NULL;

	return pNew;
}


void CPoMmsDataSet::OnFinalRelease()
{

}


// CPoMmsDataSet 消息处理程序

CString CPoMmsDataSet::GetName(void)
{
	

	CString strResult;

	ASSERT( m_pDataset != NULL);
	strResult = m_pDataset->DaSetDesc;

	return strResult;
}

void CPoMmsDataSet::SetName(const CString &newVal)
{
	

	// TODO: 在此添加属性处理程序代码
}

CString CPoMmsDataSet::GetID(void)
{
	

	CString strResult;

	ASSERT( m_pDataset != NULL);
	strResult = m_pDataset->DataSetID;

	return strResult;
}

void CPoMmsDataSet::SetID(CString newVal)
{
	

	// TODO: 在此添加属性处理程序代码
}

long CPoMmsDataSet::GetCount(void)
{
	

	ASSERT( m_pDataset != NULL);
	
	return m_pDataset->numData;
}

CPoMmsData* CPoMmsDataSet::GetItem(long nIndex)
{
	

	if (nIndex < 0 || nIndex >m_pDataset->numData)
	{
		return NULL;
	}

	tagDA *pDA = &m_pDataset->DataSet[nIndex];
	CPoMmsData *pPoData = CPoMmsData::_NewPoData(m_pACSI_NODE, m_pLD_NODE, m_pDataset, pDA);

	return pPoData;
}

CPoMmsData* CPoMmsDataSet::FindDataByID(const CString &strDataID)
{
	

	long nIndex = 0;
	tagDA *pDA = NULL;
	tagDA *pFind = NULL;

	for (nIndex=0; nIndex<m_pDataset->numData; nIndex++)
	{
		pDA = &m_pDataset->DataSet[nIndex];

#ifdef _use_mms_string
        if (strDataID == mms_string(&pDA->DAValue.mmsName) )
#else
		if (strcmp(pDA->DAValue.mmsName, strDataID) == 0)
#endif
		{
			pFind = pDA;
			break;
		}
	}

	if (pFind == NULL)
	{
		return NULL;
	}

	CPoMmsData *pPoData = CPoMmsData::_NewPoData(m_pACSI_NODE, m_pLD_NODE, m_pDataset, pFind);

	return pPoData;
}

CPoMmsData* CPoMmsDataSet::FindDataByName(const CString &strName)
{
	

	// TODO: 在此添加调度处理程序代码

	return NULL;
}

void CPoMmsDataSet::FreeTempNewDataset()
{	
	if (m_pTempNewDataset != NULL)
	{
		if (m_bTempNewDataset)
		{
			delete m_pTempNewDataset;
			m_pTempNewDataset = NULL;
		}
	}

	m_bTempNewDataset = TRUE;
}

void CPoMmsDataSet::TempNewDataset()
{
	if (m_pTempNewDataset != NULL)
	{
		if (! m_bTempNewDataset)
		{
			m_bTempNewDataset = TRUE;
			m_pTempNewDataset = new CDvmDataset();
		}
	}
	else
	{
		m_bTempNewDataset = TRUE;
		m_pTempNewDataset = new CDvmDataset();
	}
}

BOOL CPoMmsDataSet::GetXmlDataEx_LD_DATASET_INFO()
{
	if (m_pDataset != NULL)
	{
		TempNewDataset();
		mms_GetDvmDataset(m_pDataset, m_pTempNewDataset);

		m_pTempNewDataset->m_strName = m_pDataset->DataSetID;
		m_pTempNewDataset->m_strID = m_pDataset->DataSetID;

		return TRUE;
	}

	return FALSE;
}

BOOL CPoMmsDataSet::GetXmlDataEx_DvmDataset()
{
	if (m_pDvmDataset == NULL)
	{
		return FALSE;
	}

	POS pos = m_pDvmDataset->GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)m_pDvmDataset->GetNext(pos);
		GetXmlDataEx_DvmData(pData);
	}

	FreeTempNewDataset();
	m_pTempNewDataset = m_pDvmDataset;
	m_bTempNewDataset = FALSE;

	return TRUE;
}

BOOL po_GetXmlDataEx_DvmData(CDvmData *pData, ACSI_NODE *pDevice)
{
	if (pData->m_strID == ATTRID_NUMOFSG)
	{
		if (g_bMmsEngineDebugMode)
		{
			pData->m_strValue = _T("8");
		}
		else
		{
			pData->m_strValue.Format(_T("%d"), pDevice->nSGNum);
		}
	}
	else if (pData->m_strID == ATTRID_ACTSG)
	{
		pData->m_strValue.Format(_T("%d"), pDevice->nRunSGIndex);
	}
	else if (pData->m_strID == ATTRID_TMTOTAL)
	{
		pData->m_strValue.Format(_T("%d"), pDevice->tmTotal);
	}
	else if (pData->m_strID == ATTRID_TMEXEC)
	{
		pData->m_strValue.Format(_T("%d"), pDevice->tmExec);
	}
	else if (pData->m_strID == ATTRID_TimeStartExec)
	{
		pData->m_strValue.Format(_T("%d-%d-%d %d:%d:%d %d"), pDevice->tmStartExc.wYear, pDevice->tmStartExc.wMonth, pDevice->tmStartExc.wDay, pDevice->tmStartExc.wHour
			, pDevice->tmStartExc.wMinute, pDevice->tmStartExc.wSecond, pDevice->tmStartExc.wMilliseconds);
	}
	else if (pData->m_strID == ATTRID_TMSEL)
	{
		pData->m_strValue.Format(_T("%d"), pDevice->tmSel);
	}
	else if (pData->m_strID == ATTRID_ERRINFO)
	{
		//theApp.GetErrorString(pData->m_strValue);
	}
	else if (pData->m_strID == ATTRID_RECORD_PATH)
	{
//		PXMMS_FILE_SYS_OBJ pFileDir = &pDevice->FileDir;
		if (mms_str_is_null(&pDevice->RcdFilePath))
		{
			pData->m_strValue = _T("");
		} 
		else
		{
            pData->m_strValue.Format(_T("\"%s\""), mms_string(&pDevice->RcdFilePath));
		}
	}
	else if (pData->m_strID ==  ATTRID_InfoEXEC)//  _T("InfoEXEC")
	{
		pData->m_strValue = pDevice->InfoExec;
	}
	else if (pData->m_strID ==  ATTRID_InfoSEL)//  _T("InfoSEL")
	{
		pData->m_strValue = pDevice->InfoSel;
	}
	else if (pData->m_strID ==  ATTRID_TimeGapEnaWrite)//  _T("TimeGapEnaWrite")
	{
		pData->m_strValue.Format(_T("%d"), g_nEnaWriteWait);
	}
	else if (pData->m_strID ==  ATTRID_TimeGapSelExec)//  _T("TimeGapSelExec")
	{
		pData->m_strValue.Format(_T("%d"), g_nEnaWriteWaitAfterSel);
	}
	else if (pData->m_strID ==  ATTRID_LogMmsMsg)//  _T("LogMmsMsg")
	{
		pData->m_strValue.Format(_T("%d"), mms_log_error_infor);
	}
	else if (pData->m_strID ==  ATTRID_EnaReadBeforeWrite)//  _T("LogMmsMsg")
	{
		pData->m_strValue.Format(_T("%d"), mms_ena_read_before_write);
	}
	else if (pData->m_strID ==  ATTRID_TEnaReadBeforeWrite)//  _T("LogMmsMsg")
	{
		pData->m_strValue.Format(_T("%d"), mms_ena_read_before_write_t);
	}
	else if (pData->m_strID ==  ATTRID_InfoSetSE)
	{
		pData->m_strValue = pDevice->InfoSetSE;
	}
	else if (pData->m_strID ==  ATTRID_InfoSetSG)
	{
		pData->m_strValue = pDevice->InfoSetSG;
	}
	else if (pData->m_strID ==  ATTRID_tmSetSE)
	{
		pData->m_strValue.Format(_T("%d"), pDevice->tmSetSE);
	}
	else if (pData->m_strID ==  ATTRID_tmSetSG)
	{
		pData->m_strValue.Format(_T("%d"), pDevice->tmSetSG);
	}
	else if (pData->m_strID ==  ATTRID_InfoWriteData)//  _T("InfoWriteData")
	{
		pData->m_strValue = pDevice->InfoWriteData;
	}
	else if (pData->m_strID ==  ATTRID_TestLinkState)
	{
		pData->m_strValue.Format(_T("%d"), pDevice->bTestLinkState);
	}
	else if (pData->m_strID ==  ATTRID_LogCount)
	{
		pData->m_strValue.Format(_T("%d"), pDevice->LogTotalNum);
	}
	else if (pData->m_strID ==  ATTRID_CurDirFileNum)
	{
		pData->m_strValue.Format(_T("%d"), pDevice->nRecordFileTotalNum);
	}
	else if (pData->m_strID == ATTRID_DVM_NAME_IS_STD)
	{
		pData->m_strValue.Format(_T("%d"), g_nDvmNameIsStd);
	}
	else if (pData->m_strID == ATTRID_COMM_Error_Code)
	{
		pData->m_strValue.Format(_T("%d"), g_nCurErrorCode);
	}
	else if (pData->m_strID == ATTRID_COMM_Error_Class)
	{
		pData->m_strValue.Format(_T("%d"), g_nCurErrorClass);
	}
	else if (pData->m_strID == ATTRID_COMM_Error_InforRpt)
	{
		pData->m_strValue.Format(_T("%d"), g_nCurErrorInforRpt);
	}

	return TRUE;
}

BOOL CPoMmsDataSet::GetXmlDataEx_DvmData(CDvmData *pData)
{
	return po_GetXmlDataEx_DvmData(pData, m_pACSI_NODE);
}

BOOL CPoMmsDataSet::GetXmlDataEx_Rpt()
{
	if (m_pRpt == NULL || m_pACSI_NODE == NULL)
	{
		return FALSE;
	}

	if (m_strReadSoeDsPath.GetLength() == 0)
	{
		g_nMmsDvmReports_Format_Type = 0;
	}
	else
	{
		g_nMmsDvmReports_Format_Type = 1;
	}

	CTickCount32 oTick32;
	TempNewDataset();

	enter_u_mvl_rpt_CriticSection();
	ASSERT ((m_pRpt != NULL) && (m_pACSI_NODE != NULL));
	mms_GetDvmDatasetReports(m_pACSI_NODE,m_pTempNewDataset, m_pDvmDeviceMap);

	if (m_strReadSoeDsPath.GetLength() == 0)
	{
		m_pACSI_NODE->nReportBeginIndex = m_pACSI_NODE->nCurrReportIndex;// m_pACSI_NODE->nReportEndIndex;
	}

	free_u_mvl_rpt_CriticSection();
	long nTotalCount = m_pTempNewDataset->GetCount();

	//报告去走之后，定位到上次取走报告的位置
	if (m_strReadSoeDsPath.GetLength() > 0)
// 	{
// 		m_pACSI_NODE->nReportBeginIndex = m_pACSI_NODE->nCurrReportIndex;// m_pACSI_NODE->nReportEndIndex;
// 	}
// 	else
	{
		POS pos = m_pTempNewDataset->GetHeadPosition();
		CDvmData *pData = NULL;
		POS posCurr = NULL;

		while (pos != NULL)
		{
			posCurr = pos;
			pData = (CDvmData*)m_pTempNewDataset->GetNext(pos);

			if (pData->m_strFormat.Find(m_strReadSoeDsPath) < 0)
			{
				m_pTempNewDataset->Delete(pData);
			}
		}
	}

	return TRUE;
}

BOOL CPoMmsDataSet::GetXmlDataEx_FileDir()
{
	if (m_pFileDir == NULL)
	{
		return FALSE;
	}

	TempNewDataset();
	mms_GetFileDir(&m_pACSI_NODE->FileDir,m_pTempNewDataset);

	return TRUE;
}

CString CPoMmsDataSet::GetXmlData(void)
{
	if (GetXmlDataEx_LD_DATASET_INFO())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("GetXmlDataEx_LD_DATASET_INFO成功."));
	}
	else if (GetXmlDataEx_DvmDataset())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("GetXmlDataEx_DvmDataset成功."));
	}
	else if (GetXmlDataEx_Rpt())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("GetXmlDataEx_Rpt成功."));
	}
	else if(GetXmlDataEx_FileDir())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("GetXmlDataEx_FileDir成功."));
	}

	return _T("");
}

BOOL CPoMmsDataSet::SetXmlData_LD_DATASET_INFO(const CString &strXmlData)
{
	//存在映射关系
	if (m_pMmsDatasetMapTool != NULL)//zhouhj 20190917 如存在映射关系，按映射关系设置修改值
	{
		CDvmDataset oDataset;
        BSTR bstrXmlData = strXmlData.AllocSysString();
        oDataset.SetXml(bstrXmlData, CDataMngrXmlRWKeys::CDvmDatasetKey(), CDataMngrXmlRWKeys::g_pXmlKeys);
        ::SysFreeString(bstrXmlData);

		//映射关系
		m_pMmsDatasetMapTool->SetAcsiNodeByDataset(&oDataset);

		return TRUE;
	}

	if (m_pDataset != NULL)
	{
		CDvmDataset oDataset;
        BSTR bstrXmlData = strXmlData.AllocSysString();
        oDataset.SetXml(bstrXmlData, CDataMngrXmlRWKeys::CDvmDatasetKey(), CDataMngrXmlRWKeys::g_pXmlKeys);
        ::SysFreeString(bstrXmlData);
		mms_SetByDvmDataset(&oDataset, m_pDataset);

		return TRUE;
	}

	return FALSE;
}

BOOL CPoMmsDataSet::SetXmlData_DvmDataset(const CString &strXmlData)
{
	if (m_pDvmDataset == NULL)
	{
		return FALSE;
	}

	CDvmDataset oDataset;
    BSTR bstrXmlData = strXmlData.AllocSysString();
    oDataset.SetXml(bstrXmlData, CDataMngrXmlRWKeys::CDvmDatasetKey(), CDataMngrXmlRWKeys::g_pXmlKeys);
    ::SysFreeString(bstrXmlData);
	POS pos = oDataset.GetHeadPosition();
	CDvmData *pData = NULL;
	CDvmData *pFind = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)oDataset.GetNext(pos);
		pFind = (CDvmData *)m_pDvmDataset->FindByID(pData->m_strID);

		if (pFind != NULL)
		{
			pFind->m_strValue = pData->m_strValue;
			SetXmlData_Data(pFind);
		}
	}

	return TRUE;
}

BOOL CPoMmsDataSet::SetXmlData_Data(CDvmData *pData)
{
	if (pData->m_strID ==  ATTRID_RECORD_PATH)//  _T("RECORD_PATH")
	{
		PXMMS_FILE_SYS_OBJ pFileDir = &m_pACSI_NODE->FileDir;
		CString strPath = pData->m_strValue;
		strPath.Replace(_T("\""), _T(""));
		CString_to_char(strPath, mms_string(&pFileDir->filedir.filename)/*pFileDir->PathName*/);
	}
	else if (pData->m_strID ==  ATTRID_TimeGapEnaWrite)//  _T("TimeGapEnaWrite")
	{
		g_nEnaWriteWait = CString_To_long(pData->m_strValue);
	}
	else if (pData->m_strID ==  ATTRID_TimeGapSelExec)//  _T("TimeGapSelExec")
	{
		g_nEnaWriteWaitAfterSel = CString_To_long(pData->m_strValue);
	}
	else if (pData->m_strID ==  ATTRID_LogMmsMsg)//  _T("LogMmsMsg")
	{
		mms_log_error_infor = CString_To_long(pData->m_strValue);
	}
	else if (pData->m_strID ==  ATTRID_EnaReadBeforeWrite)//  _T("LogMmsMsg")
	{
		mms_ena_read_before_write = CString_To_long(pData->m_strValue);
	}
	else if (pData->m_strID ==  ATTRID_TEnaReadBeforeWrite)//  _T("LogMmsMsg")
	{
		mms_ena_read_before_write_t = CString_To_long(pData->m_strValue);
	}
	else if (pData->m_strID ==  ATTRID_TestLinkState)//  _T("LogMmsMsg")
	{
		m_pACSI_NODE->bTestLinkState = CString_To_long(pData->m_strValue);
	}
	else if (pData->m_strID == ATTRID_DVM_NAME_IS_STD)
	{
		g_nDvmNameIsStd = CString_To_long(pData->m_strValue);
	}

	return 0;
}

long CPoMmsDataSet::SetXmlData(const CString &strXmlData)
{
	

	//本地设备数据模型数据
	if (SetXmlData_LD_DATASET_INFO(strXmlData))
	{
		return 0;
	}

	//装置属性数据
	if (SetXmlData_DvmDataset(strXmlData))
	{
		return 0;
	}
	
	return 0;
}


CString CPoMmsDataSet::GetXmlDataEx(void)
{
	return GetXmlData();
}


void CPoMmsDataSet::InitByDataset(CDvmDataset *pDataset)
{
	mms_SetByDvmDataset(pDataset, m_pDataset);
}
