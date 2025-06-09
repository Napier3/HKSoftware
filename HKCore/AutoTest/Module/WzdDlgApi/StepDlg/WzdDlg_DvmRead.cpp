#include "stdafx.h"
#include "WzdDlg_DvmRead.h"
#include "../MmsApi/MmsApi.h"
#include "../MmsApi/MmsGlobal.h"
#include "../MmsApi/MmsWriteXml.h"
#include "../../../../Module/XLanguage/XLanguageResource.h"
#include "../../../../Module/GpsPcTime/GpsPcTime.h"
#include "../../../../Module/Socket/XPing.h"
#include "MessageDlg.h"

void mms_UpdateDeviceState(long nDeviceIndex)
{

}

void mms_UpdateDeviceState(ACSI_NODE *pDevice)
{

}

void mms_UpdateDatasetState(long nDeviceIndex, long nLDIndex, long nDsIndex)
{

}

void mms_UpdateDatasetState(LD_DATASET_INFO *pLD_INFO)
{

}

ST_RET enter_u_mvl_rpt_CriticSection()
{
	return 0;
}

ST_RET free_u_mvl_rpt_CriticSection()
{
	return 0;
}


IMPLEMENT_DYNAMIC(CWzdDlg_DvmRead, CDialog)

CWzdDlg_DvmRead::CWzdDlg_DvmRead(CWnd* pParent /*=NULL*/)
: CWzdDlgBase(CWzdDlg_DvmRead::IDD, pParent)
{
	m_hBkBr = CreateSolidBrush(RGB(255,255,255));
	m_dwMmsNodeType = -1;
	m_nMmsDeviceIndex = -1;
	m_nMmsLDeviceIndex = -1;
	m_nMmsDsIndex = -1;
	m_pCurrSelDA = NULL;
	m_bIsCurrListHeaderAin = FALSE;
	m_bIsCurrDataSetAin = FALSE;
	m_pProgDlg = NULL;
}

CWzdDlg_DvmRead::~CWzdDlg_DvmRead()
{
}

void CWzdDlg_DvmRead::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_DVM, m_btnDvm);
	DDX_Control(pDX, IDC_STATIC_DVM, m_txtDvm);
	DDX_Control(pDX, IDC_TREE_DVM, m_treeDvm);
	DDX_Control(pDX, IDC_EDIT_IP, m_editIP);
	DDX_Control(pDX, IDC_LIST_DVM, m_gridDvm);
}

void CWzdDlg_DvmRead::OnInitialUpdate()
{
	XUI_InitAdjust();

	InitListHeader();

	const char *pBinPath = _P_GetBinPath();

	sprintf(CLIENT_PATH, "%sclient.log", pBinPath);
	sprintf(LOGCFG_PATH, "%slogcfg.xml", pBinPath);
	sprintf(WMD_PATH, "%svmd.ini", pBinPath);
	sprintf(OSICFG_PATH, "%sosicfg.xml", pBinPath);
	sprintf(SECMANCFG_PATH, "%ssecmancfg.xml", pBinPath);

	ReadMmsEngineConfig();

	mmsi_InitMMSData(0, SD_TRUE);

	m_treeDvm.InitDeviceNodeList(-1);
}

void CWzdDlg_DvmRead::XUI_InitAdjust()
{
	CXUIAdjItem_Area::XUI_SetParentWnd(this);
	XUI_AddWnd(&m_btnDvm, 0, 0, 0, 0);
	XUI_AddWnd(&m_txtDvm, 0, 0, 0, 0);
	XUI_AddWnd(&m_treeDvm, 0, 0, 0, 1);
	XUI_AddWnd(&m_editIP, 0, 0, 0, 0);
	XUI_AddWnd(&m_gridDvm, 0, 0, 1, 1);

	CXUIAdjItem_Area::XUI_OnSize();
}

void CWzdDlg_DvmRead::InitListHeader()
{
	m_gridDvm.InitGrid();
}

void CWzdDlg_DvmRead::UpdateList(BOOL bUpdateHead)
{
	UpdateDsData(bUpdateHead);
}

void CWzdDlg_DvmRead::UpdateFileDir(long nMmsDeviceIndex)
{
// 	if (m_dwMmsNodeType == -1)
// 	{
// 		return;
// 	}
// 
// 	if (m_dwMmsNodeType != TREEITEM_TYPE_FILEDIR)
// 	{
// 		return;
// 	}
// 
// 	if (nMmsDeviceIndex != m_nMmsDeviceIndex)
// 	{
// 		return;
// 	}
// 
// 	if (!m_ListCtrl.DeleteAllItems())
// 		return;
// 
// 	InitListHeaderFileDir();
// 	m_dwMmsNodeType = TREEITEM_TYPE_FILEDIR;
// 
// 	ACSI_NODE *pDevice = &pACSINode[m_nMmsDeviceIndex];
// 	XMMS_FILE_SYS_OBJ *pFileDir = &pDevice->FileDir;
// 	XMMS_FILE_SYS_OBJ *pSubFileDir = NULL;
// 
// 	if (pFileDir->subFiles.numOfData == 0)
// 		return;
// 
// 	long nCount = 0;
// 	long nIndex = 0;
// 	CString strText;
// 	struct tm *pdate;
// 
// 	char *pszFileDirPath = NULL;
// 
// 	if (!m_strFileDirPath.IsEmpty())
// 		pFileDir = find_dir_by_path(mms_string(&pFileDir->filedir.filename),m_strFileDirPath,pFileDir);
// 	else
// 		m_strFileDirPath = mms_string(&pFileDir->filedir.filename) ;
// 
// 	if (pFileDir == NULL)// 如果未检索到，则显示根目录下内容
// 	{
// 		// 		m_strFileDirPath = "";
// 		// 		return;
// 		pFileDir = &pDevice->FileDir;
// 		m_strFileDirPath = mms_string(&pFileDir->filedir.filename);
// 	}
// 
// 
// 	nCount = pFileDir->subFiles.numOfData;
// 
// 	m_ListCtrl.InsertItem(0, "0");
// 	m_ListCtrl.SetItemText(0, 1, "上一级目录");
// 	m_ListCtrl.SetItemText(0, 2, "..");
// 
// 	if (pFileDir->parent == NULL)
// 	{
// 		m_ListCtrl.SetItemData(0, (DWORD)pFileDir);
// 	}
// 	else
// 		m_ListCtrl.SetItemData(0, (DWORD)pFileDir->parent);
// 
// 	for (nIndex=1; nIndex<=nCount; nIndex++)
// 	{
// 		pSubFileDir = (PXMMS_FILE_SYS_OBJ)(*(pFileDir->subFiles.Datas + (nIndex-1)));//->dir[nIndex];
// 		strText.Format(_T("%d"), nIndex);
// 		m_ListCtrl.InsertItem(nIndex, strText);
// 		strText = mms_string(&pSubFileDir->filedir.filename);
// 		//		strText = strPath + strText;
// 		//		strcpy(mms_string(&pSubFileDir->name) ,strText);
// 		m_ListCtrl.SetItemText(nIndex, 1, strText);
// 		m_ListCtrl.SetItemText(nIndex, 2, m_strFileDirPath);
// 
// 		pdate = localtime(&pSubFileDir->filedir.mtime);
// 		strText.Format("%04d/%02d/%02d %02d:%02d:%02d",
// 			pdate->tm_year+1900,
// 			pdate->tm_mon+1,
// 			pdate->tm_mday,
// 			pdate->tm_hour,
// 			pdate->tm_min,
// 			pdate->tm_sec
// 			);
// 		m_ListCtrl.SetItemText(nIndex, 3, strText);
// 
// 		if (pSubFileDir->filedir.fsize < 1024)
// 		{
// 			strText.Format(_T("%d B"), pSubFileDir->filedir.fsize);
// 		}
// 		else if (pSubFileDir->filedir.fsize < 1048576)
// 		{
// 			strText.Format(_T("%.2f KB"), pSubFileDir->filedir.fsize / 1024.0);
// 		}
// 		else
// 		{
// 			strText.Format(_T("%.2f MB"), pSubFileDir->filedir.fsize / 1048576.0);
// 		}
// 
// 		m_ListCtrl.SetItemText(nIndex, 4, strText);
// 		m_ListCtrl.SetItemData(nIndex, (DWORD)pSubFileDir);
// 		//zhow:20180107 解决选择行后软件死掉的现象，选择行后，会默认将此认为是 tagDA *pDA
// 	}
// 
// 	m_strFileDirPath = "";
}

void CWzdDlg_DvmRead::UpdateJournal()
{
	m_dwMmsNodeType = TREEITEM_TYPE_LOGLIST;
	m_gridDvm.m_nType = CDvmReadGrid::Journal;
	m_gridDvm.InitGrid();

	ACSI_NODE *pDevice = &pACSINode[m_nMmsDeviceIndex];
	LD_NODE *pLdevice = &pDevice->LD[m_nMmsLDeviceIndex];
	MMS_ADDR_VECTOR *pJournalDatas = &pLdevice->JournalDatas;
	LD_JOURNAL_DATA *pJournalData = NULL;
	int nIndex = 0,nIndex1,nEntryNum = 0;
	CString strEntryID,strTmp,strEntryTime;
	tagEVENTTIME tmEvent;

	for (nIndex=0;nIndex<pJournalDatas->numOfData;nIndex++)
	{
		nEntryNum++;
		pJournalData = (LD_JOURNAL_DATA *)pJournalDatas->Datas[nIndex];
		strEntryID = "";

		for (int nLenth = 0;nLenth<8;nLenth++)
		{
			strTmp.Format("%02X ",(ST_UCHAR)pJournalData->EntryID[nLenth]);
			strEntryID += strTmp;
		}

		convert_btod_to_timet(pJournalData->occur_time, tmEvent);
		strEntryTime.Format("%d-%d-%d %d:%d:%d.%d",tmEvent.year, tmEvent.month, tmEvent.day, tmEvent.hour
			, tmEvent.minute, tmEvent.second, tmEvent.ms);

		CExBaseList oList;
		for (nIndex1 = 0;nIndex1<pJournalData->numData;nIndex1++)
		{
			tagDA* pTempData = &pJournalData->DAValue[nIndex1];
			CTagDAObject* pObj = new CTagDAObject;
			pObj->m_pData = pTempData;
			pObj->m_nEntryNum = nEntryNum;
			pObj->m_strEntryID = strEntryID;
			pObj->m_strLogEntryName = mms_string(&pJournalData->LogCtrl);
			pObj->m_strEntryTime = strEntryTime;
			oList.AddNewChild(pObj);
		}

		m_gridDvm.ShowDatas(&oList);
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "当前日志总数目为 %d ;", nEntryNum);
}

BOOL CWzdDlg_DvmRead::InitCurrDsAin()
{
	LD_NODE *pLD_NODE = &pACSINode[m_nMmsDeviceIndex].LD[m_nMmsLDeviceIndex];
	LD_DATASET_INFO *pDs = &pLD_NODE->DataInfo[m_nMmsDsIndex];
	CString strDataSetName;
	strDataSetName = pDs->DataSetID;
	strDataSetName.MakeLower();

	if (strDataSetName.Find(_T("ain")) >= 0)
	{
		m_bIsCurrDataSetAin = TRUE;
	}
	else
	{
		m_bIsCurrDataSetAin = FALSE;
	}

	return m_bIsCurrDataSetAin;
}

void CWzdDlg_DvmRead::UpdateDsData(BOOL bUpdateHead)
{
	m_pCurrSelDA = NULL;
	ASSERT (pACSINode!=NULL);

	int nDvIndex = m_nMmsDeviceIndex;
	int nLDIndex = m_nMmsLDeviceIndex;
	int nDsIndex = m_nMmsDsIndex;

	if (nDvIndex < 0 || nDvIndex >= numDevice)
		return;

	if (nLDIndex < 0 || nLDIndex >= MAX_LD_VMD)
		return;

	LD_NODE *pLD = &pACSINode[nDvIndex].LD[nLDIndex];

	if (nDsIndex >= pLD->numDaSet)
	{
		//ASSERT(FALSE);
		return ;
	}

	LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex]; 

	// 	if (!pLD_INFO->bHasEnum)
	// 		return;

	InitCurrDsAin();

	if (bUpdateHead)
	{
		if (m_bIsCurrDataSetAin)
		{
			m_gridDvm.m_nType = CDvmReadGrid::Ain;
		}
		else
		{
			m_gridDvm.m_nType = CDvmReadGrid::Normal;
		}
	}
	else
	{
		if (m_bIsCurrDataSetAin)
		{
			if (!m_bIsCurrListHeaderAin)
			{
				m_gridDvm.m_nType = CDvmReadGrid::Ain;
			}
		}
		else
		{
			if (m_bIsCurrListHeaderAin)
			{
				m_gridDvm.m_nType = CDvmReadGrid::Normal;
			}
		}
	}

	m_gridDvm.InitGrid();

	CExBaseList oList;

	tagDA* pDA = NULL;
	for (int i=0; i<pLD_INFO->numData; i++)
	{
		pDA = &pLD_INFO->DataSet[i];
		if (pDA)
		{
			CTagDAObject* pObj = new CTagDAObject;
			pObj->m_pData = pDA;
			oList.AddNewChild(pObj);
		}
	}

	m_gridDvm.ShowDatas(&oList);
}

// 
// void CWzdDlg_DvmRead::UpdateListItemText(int nRow, tagDA* pDA)
// {
// 	CString strText = "";
// 	strText.Format("%d",nRow+1);
// 	m_ListCtrl.SetItemText(nRow,0, strText);
// 
// 	CString str;// = mms_GetDADesc(pDA);
// 	strText = mms_GetDADesc(pDA);//mms_UTF8ToUnicode(str, str.GetLength());
// 
// 	if (strText.IsEmpty())//zhouhj20180607 当描述为空时，自动替换为路径
// 	{
// 		strText = mms_string(&pDA->DAValue.mmsName);
// 		mms_str_copy(&pDA->DADescri.mmsName,&pDA->DAValue.mmsName);
// 	}
// 
// 	m_ListCtrl.SetItemText(nRow,1,strText);
// 
// #ifdef _use_mms_string
// 	strText = mms_string(&pDA->DAValue.mmsName);
// #else
// 	strText = pDA->DAValue.mmsName;
// #endif
// 	m_ListCtrl.SetItemText(nRow,2,strText);
// 
// 	if (m_bIsCurrDataSetAin)
// 	{
// 		long nCount = pDA->nSubDANum;
// 		long nIndex = 0;
// #ifdef _use_mms_string
// 		long nPos = mms_str_length(&pDA->DAValue.mmsName) + 1;
// #else
// 		long nPos = strlen(pDA->DAValue.mmsName) + 1;
// #endif
// 
// 		if (nCount == 0)
// 		{
// #ifdef _use_mms_string
// 			long nCol = GetSubDACol(mms_string(&pDA->DAValue.mmsName), nPos);
// #else
// 			long nCol = GetSubDACol(pDA->DAValue.mmsName, nPos);
// #endif
// 
// 			if (nCol == -1)
// 			{
// 				nCol = 3;
// 			}
// 			strText = mms_GetValue(&pDA->DAValue, pDA->DataType);
// 			m_ListCtrl.SetItemText(nRow, nCol, strText);
// 		}
// 		else
// 		{
// 			for (nIndex=0; nIndex<nCount; nIndex++)
// 			{
// 				ShowAinText(nRow, &pDA->pSubDA[nIndex], nPos);
// 			}
// 		}
// 	}
// 	else
// 	{
// 		strText = pDA->DataType;
// 		m_ListCtrl.SetItemText(nRow,3,strText);
// 
// 		strText = mms_GetDAValue(pDA);
// 		m_ListCtrl.SetItemText(nRow,4,strText);
// 
// 		strText.Empty();
// 
// #ifdef tagDA_use_UNIT_MIN_MAX_STEP
// 		if (mms_str_length(&pDA->StepSize.mmsName) > 0)
// 		{
// 			CString strDataType = "";
// 
// 			if (mms_GetValueDataType(pDA,strDataType))
// 			{
// 				strText = mms_GetValueByDataType(&pDA->StepSize.Value ,strDataType);
// 			}
// 			//			strText.Format("%f",pDA->StepSize.Value.f);
// 		}
// 		else
// 			mms_GetDAStepSizeValue(pDA, strText);
// #endif
// 
// 		m_ListCtrl.SetItemText(nRow,5,strText);
// 
// 		strText = mms_GetDAUnit(pDA);
// 		m_ListCtrl.SetItemText(nRow,6,strText);
// 
// 		if (pDA->bModify)
// 		{
// 			strText = _T("X");
// 		}
// 		else
// 		{
// 			strText = _T("");
// 		}
// 
// 		m_ListCtrl.SetItemText(nRow,7,strText);
// 	}
// 
// #ifdef tagDA_use_UNIT_MIN_MAX_STEP
// 	if (mms_str_length(&pDA->MinVal.mmsName)>0)
// 	{
// 		CString strDataType = "";
// 
// 		if (mms_GetValueDataType(pDA,strDataType))
// 		{
// 			strText = mms_GetValueByDataType(&pDA->MinVal.Value ,strDataType);
// 		}
// 	}
// 	else
// 		strText = mms_GetMinValue(pDA);
// 
// 	m_ListCtrl.SetItemText(nRow, 8, strText);
// #endif
// 
// #ifdef tagDA_use_UNIT_MIN_MAX_STEP
// 	if (mms_str_length(&pDA->MaxVal.mmsName)>0)
// 	{
// 		CString strDataType = "";
// 
// 		if (mms_GetValueDataType(pDA,strDataType))
// 		{
// 			strText = mms_GetValueByDataType(&pDA->MaxVal.Value ,strDataType);
// 		}
// 	}
// 	else
// 		strText = mms_GetMaxValue(pDA);
// 
// 	m_ListCtrl.SetItemText(nRow, 9, strText);
// #endif
// 
// 	m_ListCtrl.SetItemData(nRow, (DWORD)pDA);
// }

// void CWzdDlg_DvmRead::SetListItemText(int nRow, tagDA* pDA)
// {
// 	m_ListCtrl.InsertItem(nRow,_T(""));
// 	UpdateListItemText(nRow, pDA);
// }

XMMS_FILE_SYS_OBJ* CWzdDlg_DvmRead::find_dir_by_path(const CString &strObjParentPath,const CString &strSearchPath, XMMS_FILE_SYS_OBJ *pFileDir)
{
	XMMS_FILE_SYS_OBJ *pFind = NULL;
	XMMS_FILE_SYS_OBJ *pSubFileDir = NULL;
	int nIndex = 0;
	CString strNewObjPath;

	for(nIndex = 0;nIndex<pFileDir->subFiles.numOfData;nIndex++)
	{
		pSubFileDir = (XMMS_FILE_SYS_OBJ *)*(pFileDir->subFiles.Datas + nIndex);

		if (pSubFileDir->nType == 1)
		{
			strNewObjPath.Format("%s%s",strObjParentPath,mms_string(&pSubFileDir->filedir.filename));
			strNewObjPath.Replace("//","/");
			if (strNewObjPath == strSearchPath)
			{
				pFind = pSubFileDir;
			}
			else if (strSearchPath.Left(strNewObjPath.GetLength()) == strNewObjPath)
			{
				pFind = find_dir_by_path(strNewObjPath,strSearchPath,pSubFileDir);
			}

			if (pFind != NULL)
			{
				break;
			}
		}
	}

	return pFind;
}

// void CWzdDlg_DvmRead::InitStopReportFuncParas(ST_INT nDeviceIndex, BOOL bFreeFuncParas)
// {
// 	if (pACSINode == NULL)
// 	{
// 		return;
// 	}
// 
// 	if (nDeviceIndex<0)
// 		return;
// 
// 	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
// 
// 	if (pDevice == NULL)
// 	{
// 		return;
// 	}
// 
// // 	if (m_pMainWnd !=NULL)
// // 		pDevice->hRptMsgWnd = (unsigned long)GetParent()->m_hWnd;
// 
// 	pDevice->nRptMsg = WM_MMS_REPORT;
// 
// 	long nLDIndex = 0;
// 	long nLDCount = pDevice->numLD;
// 
// 	if (bFreeFuncParas)
// 	{
// 		m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
// 	}
// 
// 	for (nLDIndex=0; nLDIndex<nLDCount; nLDIndex++)
// 	{
// 		LD_NODE *pLD = &(pACSINode[nDeviceIndex].LD[nLDIndex]);
// 		for (int i=0; i<pLD->numDaSet; i++)
// 		{
// 			// 2013-4-8  如果是定值无需停止
// 			if (!CheckCurSelIsSetting(nDeviceIndex,nLDIndex,i))
// 				InitStopReportFuncParas(nDeviceIndex, nLDIndex, i);
// 		}
// 	}
// }

BOOL CWzdDlg_DvmRead::DoNext()
{
	//InitStopReportFuncParas(0, TRUE);

	CString strFile = _P_GetLibraryPath();
	strFile += "iSmartTestWzdTempDvmFile.xml";
	mms_XmlWrite(strFile, &pACSINode[0]);
	GetParentWnd()->SendMessage(WM_IEDSEL_SELECT, 0, (LPARAM)strFile.GetString());
	return TRUE;
}

ST_VOID CWzdDlg_DvmRead::mmsi_RecvRptData()
{

}

//自动测试模式下，联机之后，枚举设备的逻辑设备，在枚举逻辑设备成功之后，在枚举逻辑设备的其他参数
void CWzdDlg_DvmRead::InitLinkDeviceFuncPara(ST_INT nDeviceIndex, BOOL bOnlyLink)
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	CFuncParam *pParam = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, 0, FuncID_Link, dsType_NULL, /*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
	pParam->set_ServerCmd();

	if (bOnlyLink)
	{
		return;
	}
	else
	{
		m_oFuncParamEx[nDeviceIndex].SetsConnectDevice(TRUE);
	}

	pDevice->nSetRunSGIndexState = 1;

	if (!pDevice->bCanReConnect)
	{
		set_OnlyReadValue(SD_FALSE);
		InitEnumLDFuncPara(nDeviceIndex, FALSE);
	}
}

void CWzdDlg_DvmRead::InitEnumLDFuncPara(ST_INT nDeviceIndex, BOOL bFreeFuncParas)
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	set_OnlyReadValue(SD_FALSE);

	if (bFreeFuncParas)
	{
		m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	}

	if (pDevice->nHasDeviceModel != 1)
	{
		m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, 0,  FuncID_EnumLD,   dsType_NULL, /*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
	}
	else
	{
		if (g_bMmsEnumLDAfterReadXml)
		{
			m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, 0,  FuncID_EnumLD,   dsType_NULL, /*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
		}
	}

	m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, -1, FuncID_GetSGNum, dsType_NULL, /*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
}

BOOL CWzdDlg_DvmRead::CallFirstFunc(long nDeviceIndex)
{
	CFuncParamEx *pFuncParaEx = &m_oFuncParamEx[nDeviceIndex];
	pFuncParaEx->m_posCurrFuncPara = pFuncParaEx->GetHeadPosition();
	long nCount = m_oFuncParamEx[nDeviceIndex].GetCount();

	if (pFuncParaEx->m_posCurrFuncPara != NULL)
	{
		StartProgress();

		if (m_pProgDlg != NULL)
		{
			m_pProgDlg->SetMaxRange(nCount);
		}
	}

	return CallCurrFunc(nDeviceIndex);
}

BOOL CWzdDlg_DvmRead::CallNextFunc(long nDeviceIndex)
{
	CFuncParamEx *pFuncParaEx = &m_oFuncParamEx[nDeviceIndex];

	if (pFuncParaEx->m_posCurrFuncPara == NULL)
	{
		mmsi_FunctionCall(nDeviceIndex,FuncID_TestProc);
		return FALSE;
	}

	pFuncParaEx->GetNext(pFuncParaEx->m_posCurrFuncPara);
	return CallCurrFunc(nDeviceIndex);
}

void CWzdDlg_DvmRead::ValidateCurrFunc(long nDeviceIndex)
{
	CFuncParamEx *pFuncParaEx = &m_oFuncParamEx[nDeviceIndex];

	if (pFuncParaEx->m_posCurrFuncPara == NULL)
	{
		return;
	}

	CFuncParam *pParam = (CFuncParam*)m_oFuncParamEx[nDeviceIndex].GetAt(pFuncParaEx->m_posCurrFuncPara);

	if (pParam->get_FuncID() == FuncID_GetSGNum || pParam->get_FuncID() == FuncID_SetSGNum)
	{
		ValidateCurrFunc_ReadZone(pParam);
	}
}

void CWzdDlg_DvmRead::ValidateCurrFunc_ReadZone(CFuncParam *pParam)
{
	ST_INT nDvIndex = pParam->get_DevIndex();
	ST_INT nLdIndex = pParam->get_LDvIndex();

	if (nLdIndex != -1)
	{//验证当前的数据集是不是保护
		ACSI_NODE *pDevice = &pACSINode[nDvIndex];
		ASSERT(pDevice != NULL);
		LD_NODE   *pLD = &(pDevice->LD[nLdIndex]);

		if (pLD != NULL)
		{
			if (mms_IsSettingsDS(pLD->LDName))
			{
				return;
			}
		}
	}

	nLdIndex = mms_FindLDeviceIndex(nDvIndex, "prot");//zhowTest20180111

	if (nLdIndex == -1)
	{
		nLdIndex = mms_FindLDeviceIndex(nDvIndex, "pqld");//zhowTest20180111
	}

	if (nLdIndex == -1)
	{
		nLdIndex =  mms_FindLDeviceIndex(nDvIndex, "rcd");
	}

	if (nDvIndex == -1)
	{
		pParam->set_DevIndex(pParam->get_DevIndex());
	}

	if (nLdIndex == -1)
	{
		ACSI_NODE *pDevice = &pACSINode[nDvIndex];

		if (pDevice != NULL)
		{
			ST_INT nIndex = 0;

			for (nIndex=0; nIndex<pDevice->numLD; nIndex++)
			{
				//if (strstr(pDevice->LD[nIndex].LDName,"PROT") || strstr(pDevice->LD[nIndex].LDName,"BRcd"))
				if (mms_IsSettingsDS(pDevice->LD[nIndex].LDName))
				{
					nLdIndex = nIndex;
					break;
				}
			}
		}
	}

	pParam->set_LDvIndex(nLdIndex);
}

BOOL CWzdDlg_DvmRead::CallCurrFunc(long nDeviceIndex)
{
	CFuncParamEx *pFuncParaEx = &m_oFuncParamEx[nDeviceIndex];

	if (pFuncParaEx->m_posCurrFuncPara == NULL)
	{
		mmsi_FunctionCall(nDeviceIndex,FuncID_TestProc);
		return FALSE;
	}

	CFuncParam *pParam = (CFuncParam*)m_oFuncParamEx[nDeviceIndex].GetAt(pFuncParaEx->m_posCurrFuncPara);

	ValidateCurrFunc(nDeviceIndex);
	m_oFuncParamEx[nDeviceIndex].InitPara(pParam);//memcpy(&m_FuncParam, pParam, sizeof(m_FuncParam));

	mmsi_FunctionCall(nDeviceIndex,pParam->get_FuncID());
	m_oFuncParamEx[nDeviceIndex].BeginExecDataProc(0);

	if (m_pProgDlg == NULL)
	{
		return TRUE;
	}

	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	LD_NODE *pLD_NODE = &pDevice->LD[m_oFuncParamEx[nDeviceIndex].get_LDvIndex()];
	ST_INT nFuncID = m_oFuncParamEx[nDeviceIndex].get_FuncID();
	ST_INT nDsDaType = m_oFuncParamEx[nDeviceIndex].get_DSID();

	long nIndex = m_oFuncParamEx[nDeviceIndex].FindIndex(pFuncParaEx->m_posCurrFuncPara)+1;
	long nCount = m_oFuncParamEx[nDeviceIndex].GetCount();
	CString strFuncID , strDsDaType;

	if (g_bMultDevModel)
	{
		return TRUE;
	}

	// 2013-3-4  增加校验 && nFuncID < FUNCID_MAX_COUNT
	if (nFuncID != FuncID_UnKnow && nFuncID != FuncID_TestProc && nFuncID < FUNCID_MAX_COUNT)
	{
		strFuncID = g_strFuncIDame[nFuncID];
	}

	// 2013-3-4  增加校验  
	if (nDsDaType != dsType_NULL && nDsDaType < MAX_DASET_NUM)
	{
		LD_DATASET_INFO *pLD_INFO = &pLD_NODE->DataInfo[nDsDaType];
		strDsDaType = pLD_INFO->DataSetID;
	}

	CString strTitle;

	if (nFuncID != FuncID_Link)
	{
		if (nFuncID == FuncID_ReadFile)
		{
			strTitle.Format(_T("第%d步 共%d步 ： %s"), nIndex, nCount, CString(m_oFuncParamEx[nDeviceIndex].get_FileName()) );
		}
		else
		{
			strTitle.Format(_T("第%d步 共%d步 ： 设备%d - 逻辑设备%d - %s - %s")
				, nIndex, nCount,
				nDeviceIndex + 1, m_oFuncParamEx[nDeviceIndex].get_LDvIndex() + 1, strFuncID, strDsDaType);
		}
	}
	else
	{
		strTitle.Format(_T("联机：%s"), mms_string(&pDevice->IpAddr));
	}

	m_pProgDlg->StepIt();
	m_pProgDlg->SetTitle(strTitle);
	m_pProgDlg->ShowMsg(strTitle);

	return TRUE;
}

void CWzdDlg_DvmRead::StartProgress()
{		
	if (g_bMultDevModel)
	{
		return;
	}

	if (m_pProgDlg == NULL)
	{
		m_pProgDlg = new CMmsProgressDlg;
		m_pProgDlg->CreateThreadDlg(this, _T("MMS通讯处理中，请稍候............"));
	}

	m_pProgDlg->StartProgress();

	m_pProgressInterface = m_pProgDlg;
	GetParentWnd()->SendMessage(WM_MAIN_ENABLE_NEXT, 0, 0);
	GetParentWnd()->SendMessage(WM_MAIN_ENABLE_PREV, 0, 0);
}

void CWzdDlg_DvmRead::StopProgress(long nDeviceIndex)
{
	if (m_pProgDlg->GetSafeHwnd())
	{
		m_pProgDlg->ShowWindow(SW_HIDE);
	}

	m_oFuncParamEx[nDeviceIndex].m_posCurrFuncPara = NULL;
	GetParentWnd()->SendMessage(WM_MAIN_ENABLE_NEXT, 0, 1);
	GetParentWnd()->SendMessage(WM_MAIN_ENABLE_PREV, 0, 1);
}

void CWzdDlg_DvmRead::ReadMmsEngineConfig()
{
	CString strTemp;
	strTemp = mms_CONFIG_PATH();
	CGpsPcTimeTickCount oTick32;

	m_oMMS_STACK_CFG.OpenXmlFile(strTemp, CMMS_STACK_CFGXmlRWKeys::g_pXmlKeys);
	long nTmLong = oTick32.GetTickCountLong(FALSE);
	strTemp += _T("e");
	m_oMMS_STACK_CFG.SaveXmlFile(strTemp, CMMS_STACK_CFGXmlRWKeys::g_pXmlKeys);
	CMMS_STACK_CFGXmlRWKeys::Release();
	nTmLong = oTick32.GetTickCountLong(TRUE);

	m_oMmsEngineConfig.ReadMmsEngineConfig();

	nTmLong = oTick32.GetTickCountLong(TRUE);
	g_bMmsEngineDebugMode = m_oMmsEngineConfig.m_nDebugMode;
	g_bMmsEnumLDAfterReadXml = m_oMmsEngineConfig.m_nEnumLDAfterReadXml;
	m_bEnumLN = m_oMmsEngineConfig.m_nMmsEnumLogCtrl;
	m_bEmnuRpt = m_oMmsEngineConfig.m_nEnumRpt;
	g_nExitAppForException = m_oMmsEngineConfig.m_nExitAppForException;
	g_bUseDvmMapFile = m_oMmsEngineConfig.m_nUseDvmMapFile;
	g_bMultDevModel = m_oMmsEngineConfig.m_bMultDevModel;
	g_bExportModelAuto = m_oMmsEngineConfig.m_nExportModelAuto;
	g_bUseDsDout = m_oMmsEngineConfig.m_nUseDsDout;
	g_bAutoGenModelDatas = m_oMmsEngineConfig.m_nAutoGenModelDatas;
}

BOOL CWzdDlg_DvmRead::IsFuncsAllFinish(long nDeviceIndex)
{
	CFuncParamEx *pFuncParaEx = &m_oFuncParamEx[nDeviceIndex];

	if (pFuncParaEx->m_posCurrFuncPara == NULL)
	{
		StopProgress(nDeviceIndex);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CWzdDlg_DvmRead::SendMessage_TestFuncFinished(WPARAM wParam,LPARAM lParam)
{
	CFuncParamEx *pFuncParaEx = (CFuncParamEx*)wParam;

	if (pFuncParaEx->m_bHasPostMsg)
	{
		return FALSE;
	}

	pFuncParaEx->m_bHasPostMsg = TRUE;
	SendMessage(WM_Notify_Msg,(WPARAM )pFuncParaEx,lParam); 
	return TRUE;
}

long CWzdDlg_DvmRead::MMS_DataOpeProc(CFuncParamEx *pFuncParaEx)
{
	long nRet = CMmsApi::MMS_DataOpeProc(pFuncParaEx);

	if (nRet == -1)
	{
		return nRet;
	}

	ST_INT nFuncID = pFuncParaEx->get_FuncID();

	if (nFuncID != FuncID_TestProc)
	{
		SendMessage_TestFuncFinished((WPARAM)pFuncParaEx,nRet);
		//		pFuncParaEx->MySendMessage();//参数1在函数中未使用，实际无效
	}

	return nRet;
}

LRESULT CWzdDlg_DvmRead::OnMmsCmdFinish(WPARAM wParam,LPARAM lParam)
{
	CFuncParamEx *pFuncParaEx = (CFuncParamEx*) wParam;
	CString strMsg;
	BOOL bIsClientCmd = pFuncParaEx->is_ClientCmd();
	LONG nFuncID = pFuncParaEx-> get_FuncID();

	OnMmsCmdFinish_View(wParam, lParam);

	if (lParam==SD_SUCCESS)
	{
		if (nFuncID == FuncID_TestProc)
		{
			return 0;
		}

		ACSI_NODE *pDevice = get_DevACSI_NODEPtr(pFuncParaEx);
		CallNextFunc(pFuncParaEx->get_DevIndex());

		if ( IsFuncsAllFinish(pFuncParaEx->get_DevIndex()) )
		{
			//非自动测试模式不处理
			if (pFuncParaEx->IsConnectDevice())
			{
				pFuncParaEx->SetsConnectDevice(FALSE);//20220608 zhouhj  在联机完后读取定值区,则添加读取模型命令,并将联机模式去除
			}

			if (nFuncID == FuncID_Read)
			{
				//所有命令完成，发送消息，进行相关处理
			}
			else if (FuncID_EnumLD == nFuncID || nFuncID == FuncID_GetSGNum || nFuncID == FuncID_ReadDevice) //增加了读设备的命令  周宏军 20200422
			{
				pFuncParaEx->SetsConnectDevice(FALSE);
			}
		}
	}
	else
	{
		OnMmsCmdFinish_Error(wParam, lParam);
	}

	return 0;
}

void CWzdDlg_DvmRead::ResetWriteFailErrorCode()
{
	g_nCurErrorCode = -1;//在控制写成功后，此处设置为-1为复归值
	g_nCurErrorClass = -1;
	g_nCurErrorInforRpt = -1;
}

void CWzdDlg_DvmRead::InitReadDevice(ST_INT nDeviceIndex, BOOL bFreeFuncParas) 
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];

	if (bFreeFuncParas)
	{
		m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	}

	m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, -1 ,FuncID_ReadDevice, -1,/* m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
}

void CWzdDlg_DvmRead::InitReadFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDataType)
{
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	CFuncParam *pFuncPara = NULL;
	pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_Read, nDataType, /*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
}

void CWzdDlg_DvmRead::InitWriteFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_CHAR *strDataType)
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	LD_NODE *pLD_NODE = &pDevice->LD[nLDIndex];
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

	ST_INT nIndex = 0;
	LD_DATASET_INFO			*pDataInfo = pLD_NODE->DataInfo;

	for (nIndex=0; nIndex<pLD_NODE->numDaSet; nIndex++)
	{
		if (strstr(pDataInfo[nIndex].DataSetID, strDataType) != NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("InitCtrlWriteFuncParas(%d, %d, %s)"), nDeviceIndex, nLDIndex, CString(pDataInfo[nIndex].DataSetID));
			CFuncParam *pFuncPara = NULL;
			pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_Write, nIndex, /*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
		}
	}
}

BOOL CWzdDlg_DvmRead::CheckCurSelIsSetting(int nDeviceIndex, int nLDIndex, int nDsIndex)
{
	LD_NODE *pLD = &(pACSINode[nDeviceIndex].LD[nLDIndex]);

	if (nDsIndex<0 || nDsIndex >= MAX_DASET_NUM)
		return FALSE;

	CStringA strText(pLD->LDName);

	LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
	CStringA str(pLD_INFO->DataSetID);

	if (str.Find("Setting")!=-1)
	{
		return TRUE;
	}

	return FALSE;
}

void CWzdDlg_DvmRead::InitCallReportFlagDefault(ST_INT nDeviceIndex)
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	long nLDIndex = 0;
	long nLdCount = pDevice->numLD;

	for (nLDIndex=0; nLDIndex<nLdCount; nLDIndex++)
	{
		LD_NODE *pLD = &(pACSINode[nDeviceIndex].LD[nLDIndex]);

		for (int i=0; i<pLD->numDaSet; i++)
		{
			// 2013-4-8  注意定值无相应的报告
			if (!CheckCurSelIsSetting(nDeviceIndex,nLDIndex,i))
				mms_SetReportFlag(nDeviceIndex, nLDIndex, i, TRUE);
		}
	}
}

void CWzdDlg_DvmRead::InitReadDeviceFuncParas(ST_INT nDeviceIndex, BOOL bReadAll, BOOL bFreeFuncParas)
{
	set_OnlyReadValue(SD_FALSE);
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	long nLDIndex = 0;
	long nLdCount = pDevice->numLD;

	if (bFreeFuncParas)
	{
		m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	}

	for (nLDIndex=0; nLDIndex<nLdCount; nLDIndex++)
	{
		LD_NODE *pLD = &pACSINode[nDeviceIndex].LD[nLDIndex];
		for (int i=0;i<pLD->numDaSet;i++)
		{
			if (bReadAll)
			{
				m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_Read, i, /*m_pMainWnd->m_hWnd, */WM_Notify_Msg);

			}
			else
			{
				if (m_oMmsEngineConfig.IsDatasetUse(pLD->DataInfo[i].DataSetID))
				{
					m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_Read, i, /*m_pMainWnd->m_hWnd,*/ WM_Notify_Msg);
				}
			}
		}
	}
}
void CWzdDlg_DvmRead::OnUnlink(CFuncParamEx *pFuncParaEx)
{
	if (g_bMmsEngineDebugMode)
	{
		return;
	}

	ACSI_NODE *pDevice = get_DevACSI_NODEPtr(pFuncParaEx);

	if (pDevice->bTestLinkState)
	{
		return;
	}

	if (pDevice != NULL)
	{
		pDevice->bConnect = FALSE;
	}
}

LRESULT CWzdDlg_DvmRead::OnMmsNodeSelChanged(WPARAM wParam,LPARAM lParam)
{
	DWORD dwMmsNodeType = m_dwMmsNodeType;
	m_dwMmsNodeType = -1;
	m_nMmsDeviceIndex = -1;
	m_nMmsLDeviceIndex = -1;

	mms_GetFromDWORD(wParam, m_dwMmsNodeType, m_nMmsDeviceIndex, m_nMmsLDeviceIndex, m_nMmsDsIndex);

	if (m_dwMmsNodeType == TREEITEM_TYPE_TAGDA)
	{
		UpdateList(dwMmsNodeType != m_dwMmsNodeType);
	}
	else if (m_dwMmsNodeType == TREEITEM_TYPE_FILEDIR)
	{
		m_strFileDirPath = "";
		UpdateFileDir(m_nMmsDeviceIndex);
	}
	else if (m_dwMmsNodeType == TREEITEM_TYPE_LOGLIST)
	{
		UpdateJournal();
	}

	return 0;
}

LRESULT CWzdDlg_DvmRead::OnMmsCmdFinish_View(WPARAM wParam,LPARAM lParam)
{
	CFuncParamEx *pFuncParaEx = (CFuncParamEx*) wParam;
	CString strMsg;
	BOOL bIsClientCmd = pFuncParaEx->is_ClientCmd();
	LONG nFuncID = pFuncParaEx-> get_FuncID();
	ACSI_NODE *pDevice = &pACSINode[pFuncParaEx->get_DevIndex()];
	//ACSI_NODE *pDevice = theApp.get_DevACSI_NODEPtr(pFuncParaEx);

	switch(nFuncID)
	{
	case FuncID_Link:
		if (lParam==SD_SUCCESS)
		{
			acsi_ctrl_table[pFuncParaEx->get_DevIndex()].bShow = TRUE;
			acsi_ctrl_table[pFuncParaEx->get_DevIndex()].bConnect = TRUE;
		}
		mms_UpdateDeviceState(pDevice);
		break;

	case FuncID_UnLink:
		OnUnlink(pFuncParaEx);
		mms_UpdateDeviceState(pDevice);
		break;
	case FuncID_Read:
	case FuncID_Read_SET:
		ResetWriteFailErrorCode();//在读取数据操作后，将写失败的原因码值复归为-1 因为原因码值可能为0，此处设置为-1为复归值
		break;
	case FuncID_ReadDir:
		break;
	case FuncID_ReadFile:
		break;
	case FuncID_Write:
		break;
	case FuncID_StartRpt:
		break;
	case FuncID_StopRpt:
		break;
	case FuncID_GetSGNum:
		if (lParam == SD_SUCCESS)
		{
			ST_INT nSGNum = pFuncParaEx->get_SGNum();
			ST_INT nSGID = pFuncParaEx->get_SGID();

			CString strText = "";
			if (/*theApp.IsAutoTestMode() &&*/ pFuncParaEx->IsConnectDevice())//  周宏军  20200421  无论是否自动测试模式下，都自动读设备
			{//自动测试模式下，枚举设备的逻辑设备成功，则继续枚举设备的其他参数

				if (pDevice->nHasDeviceModel == 1)
				{//如果已经有了设备数据模型，则不需要再读取
					//theApp.SetsConnectDevice(FALSE);
					//PostDeviceSysMessage(engineConnectDeviceSuccessful, engineConnectDeviceSuccessful);
				}
				else
				{
					int nDeviceIndex = pFuncParaEx->get_DevIndex();
					int nLDIndex  = pFuncParaEx->get_LDvIndex();
					int nDSIndex = pFuncParaEx->get_DSID();

					if(pACSINode[nDeviceIndex].LD[0].mms_data_node != NULL)
					{
						InitReadDevice(nDeviceIndex,FALSE);
					}
					else
					{
						InitReadDeviceFuncParas(nDeviceIndex, TRUE,FALSE);
					}

					InitCallReportFlagDefault(nDeviceIndex);

					if (nDSIndex>= 0)
					{
						//InitCallReportFuncParas(nDeviceIndex, nLDIndex, nDSIndex,TRUE, FALSE);
					}
				}
			}
		}
		break;
	case FuncID_SetSGNum:
		break;
	case FuncID_EnumLD:
		if (lParam==SD_SUCCESS)
		{
			int nDeviceIndex = pFuncParaEx->get_DevIndex();
			m_treeDvm.InitDeviceNodeList(nDeviceIndex);
		}
		break;
	case FuncID_TestProc:
		break;
	case FuncID_SetSENum:
		break;
	case FuncID_CnfSetSE:
		break;
	case FuncID_CtrlWrite:
	case FuncID_CtrlWriteOne:
		if (lParam==SD_SUCCESS)
		{
			ResetWriteFailErrorCode();
		}
		break;
	case FuncID_Reset:
		break;
	case FuncID_UploadFile:
		break;
	case FuncID_ReadDevice:
		break;
	case FuncID_DvmEnum:
		break;
	}

	return 0;
}

LRESULT CWzdDlg_DvmRead::OnMmsCmdFinish_Error(WPARAM wParam,LPARAM lParam)
{
	if (g_bMmsEngineDebugMode)
	{
		return 0;
	}

	CFuncParamEx *pFuncParaEx = (CFuncParamEx*) wParam;
	LONG nFuncID = pFuncParaEx-> get_FuncID();

	if (!IsFuncsAllFinish(pFuncParaEx->get_DevIndex()))
	{
		ACSI_NODE *pACSI_NODE = &pACSINode[pFuncParaEx->get_DevIndex()];

		if (!pACSI_NODE->bTestLinkState)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Error CMD Exec:CMD=%d DV=%d  LD=%d  DS=%d"), pFuncParaEx->get_FuncID()
				, pFuncParaEx->get_DevIndex(), pFuncParaEx->get_LDvIndex(), pFuncParaEx->get_DSID());
			mmsi_FunctionCall(pFuncParaEx->get_DevIndex(),FuncID_TestProc);
			StopProgress(pFuncParaEx->get_DevIndex());	
			pFuncParaEx->SetsConnectDevice(FALSE);
		}
		else
		{
			mmsi_FunctionCall(pFuncParaEx->get_DevIndex(), FuncID_TestProc);
		}

		StopProgress(pFuncParaEx->get_DevIndex());
	}
	else
	{
		mmsi_FunctionCall(pFuncParaEx->get_DevIndex(), FuncID_TestProc);
	}

	return 0;
}

BEGIN_MESSAGE_MAP(CWzdDlg_DvmRead, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	//ON_BN_CLICKED(IDC_BUTTON_LINK, &CLinkSetDlg::OnBnClickedButtonLink)
	ON_MESSAGE(WM_MMS_NODE_SELCHANGED, &CWzdDlg_DvmRead::OnMmsNodeSelChanged)
	ON_MESSAGE(WM_Notify_Msg, &CWzdDlg_DvmRead::OnMmsCmdFinish)
	ON_BN_CLICKED(IDC_BTN_DVM, &CWzdDlg_DvmRead::OnBnClickedBtnDvm)
END_MESSAGE_MAP()

void CWzdDlg_DvmRead::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	XUI_OnSize(cx, cy);
}

void CWzdDlg_DvmRead::OnBnClickedBtnDvm()
{
	if(!theMmsApi)
	{
		theMmsApi = this;
	}

 	CString strIP;
 	m_editIP.GetWindowText(strIP);

	//判断IP是否完整
	BOOL bRes = xping(strIP);
	if(!bRes)
	{
		MessageDlg::MessageBox("错误", "无法连接指定IP,请确认后重试!", MessageDlg::ERRYES);
		return;
	}

	long nDeviceIndex = 0;
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	device_node_table[nDeviceIndex].IP1 = inet_addr(strIP);
	sock_info_table[nDeviceIndex].ip_addr = device_node_table[nDeviceIndex].IP1;
	mms_str_set(&pDevice->IpAddr, strIP);

	CreateDataProcThread(&theMmsApi->m_oFuncParamEx[nDeviceIndex]);

	if (pDevice->numLD > 0)
	{
		InitLinkDeviceFuncPara(nDeviceIndex, TRUE);
	}
	else
	{
		InitLinkDeviceFuncPara(nDeviceIndex, FALSE);
	}

	CallFirstFunc(nDeviceIndex);
}
