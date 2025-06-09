#include "stdafx.h"
#include "GuideBookMmsModelReplace.h"
#include "..\XLanguageResourceAts.h"


CGuideBookMmsModelReplace::CGuideBookMmsModelReplace()
{
	m_pDestCpus = NULL;
	m_pWndRef = NULL;
	m_pSelCurrGbDataObject = NULL;
	m_pSelDataObjectOpened = NULL;
	m_bReplaceAinDataset = FALSE;
	m_pDestObject = NULL;
}	

CGuideBookMmsModelReplace::~CGuideBookMmsModelReplace()
{
	m_oListDatasetRef.RemoveAll();
}

void CGuideBookMmsModelReplace::AttachXMatchGrid(CXMatchEditGridCtrlBase *pGrid)	
{	
	m_pGridXMatchEdit = pGrid;
	m_pGridXMatchEdit->SetXMatchRefClassID(GBCLASSID_DATAOBJ);
}

void CGuideBookMmsModelReplace::InitReplace()
{
// 	CString strFile;
// 	strFile = _P_GetConfigPath();
// 	strFile += _T("GbDeviceMmsDvmFiles.xml");
// 	m_oFilterMmsDvmFiles.OpenXmlFile(strFile);

	m_pGridXMatchEdit->InitGrid();
	OpenKeyDbFile();
}

void CGuideBookMmsModelReplace::SetEditCpus(CCpus *pDestCpus)
{
	m_pDestCpus = pDestCpus;
	m_oCpusDest.AppendClone(pDestCpus);
}

void CGuideBookMmsModelReplace::OpenKeyDbFile()
{
	m_oKeyDB.OpenKeyDbFile(_T(""), TRUE);
// 	m_oKeyDB.DeleteAll();
// 	CString strFile;
// 	strFile = _P_GetLibraryPath();
// 	strFile += _T("RelayTestKeyDb.xml");
// 	m_oKeyDB.OpenXmlFile(strFile, CKeyDbXmlRWKeys::CXKeyDBKey(), CKeyDbXmlRWKeys::g_pXmlKeys);
// 	m_oKeyDB.InitKeyRefBuffer();

}


void CGuideBookMmsModelReplace::OnGbNodeSelChanged_Src(CExBaseList *pSelNode)
{
	m_pSelDataObjectOpened = pSelNode;
	XMatch();
}

void CGuideBookMmsModelReplace::OnGbNodeSelChanged_Dest(CExBaseList *pSelNode)
{
	m_pSelCurrGbDataObject = pSelNode;
	XMatch();
}
// 
// BOOL CGuideBookMmsModelReplace::PopOpenMmsDvmDlg(CFilterText**ppFilterText)
// {
// 	CString strFilePath, strSoft;
// 	strFilePath = _P_GetLibraryPath();
// 	strSoft = _P_GetSystemSoftName();
// 	strFilePath += _T("*.xml");
// 	CString strFilter = _T("设备数据模型文件(*.xml)|*.xml||");
// 	CString strPostFix = _T("xml");
// 	CFilterText *pFilterText = NULL;
// 	*ppFilterText = NULL;
// 
// 	if (PopupOpenFileDialog(m_pWndRef, strFilePath, strFilter, strPostFix) )
// 	{
// 		pFilterText = m_oFilterMmsDvmFiles.AddText(strFilePath);
// 		m_oFilterMmsDvmFiles.BringToHead(pFilterText);
// 		m_oFilterMmsDvmFiles.SaveXmlFile();
// 		OpenMmsDvmFile(pFilterText->m_strName);
// 		*ppFilterText = pFilterText;
// 
// 		return TRUE;
// 	}
// 	
// 	return FALSE;
// }

BOOL CGuideBookMmsModelReplace::OpenMmsDvmFile(const CString &strMmsDvmFile)
{
	m_strMmsDvmFile = strMmsDvmFile;
	m_oCpusSrc.DeleteAll();
	return m_oCpusSrc.OpenXmlFile(strMmsDvmFile, m_oCpusSrc.GetXmlElementKey(), CGbXMLKeys::g_pGbXMLKeys);
}

BOOL CGuideBookMmsModelReplace::XMatch(BOOL bShowMatch)
{
	if (m_pSelDataObjectOpened != NULL && m_pSelCurrGbDataObject != NULL)
	{
		if (m_pSelDataObjectOpened->GetClassID() == GBCLASSID_DATASET
			&& m_pSelCurrGbDataObject->GetClassID() == GBCLASSID_DATASET)
		{
			m_oXMatchTool.Match(&m_oKeyDB, m_pSelDataObjectOpened, m_pSelCurrGbDataObject);

			if (bShowMatch)
			{
				CXMatchList *pList = m_oXMatchTool.GetDstMatchList();
				m_pGridXMatchEdit->ShowMatch(&m_oXMatchTool);
			}

			return (TRUE);
		}
		else
		{
			m_pGridXMatchEdit->SetRowCount(1);
			return (FALSE);
		}
	}
	else
	{
		m_pGridXMatchEdit->SetRowCount(1);
		return (FALSE);
	}
}

void CGuideBookMmsModelReplace::ReplaceDataSet(CThreadProgressInterface *pThreadProgress)
{
	ASSERT (pThreadProgress != NULL);
	m_pThreadProgress = pThreadProgress;
	CWinThread *pThread = ::AfxBeginThread(ReplaceDataSetThread, this);
	pThread->m_bAutoDelete = TRUE;
}

UINT CGuideBookMmsModelReplace::ReplaceDataSetThread(LPVOID pParam)
{
	CGuideBookMmsModelReplace *pMmsModelReplace = (CGuideBookMmsModelReplace*)pParam;
	pMmsModelReplace->ReplaceDataSetThread();
	return 0;
}

BOOL CGuideBookMmsModelReplace::GetReplaceID(CExBaseObject *pSrc, CExBaseObject *pDest, CString &strSrc, CString &strDest)
{
	if (pDest->m_strID == pSrc->m_strID)
	{
		return FALSE;
	}
	else
	{
		strSrc  = pSrc->m_strID;
		strDest = pDest->m_strID;
		return TRUE;
	}


	CExBaseObject *pDatasetSrc = (CExBaseObject*)pSrc->GetParent();
	CExBaseObject *pDatasetDest = (CExBaseObject*)pDest->GetParent();

	if ((pDest->m_strID == pSrc->m_strID) && (pDatasetDest->m_strID == pDatasetSrc->m_strID))
	{
		return FALSE;
	}

	if (pDatasetDest->m_strID == pDatasetSrc->m_strID)
	{
		strSrc  = pSrc->m_strID;
		strDest = pDest->m_strID;
	}
	else
	{
		strSrc.Format(_T("%s$%s"), pDatasetSrc->m_strID, pSrc->m_strID);
		strDest.Format(_T("%s$%s"), pDatasetDest->m_strID, pDest->m_strID);
	}

	return TRUE;
}

UINT CGuideBookMmsModelReplace::ReplaceDataSetThread()
{
	CXMatchList *pList = m_oXMatchTool.GetDstMatchList();
	POS pos = pList->GetHeadPosition();
	CXMatchObject *pXMatch = NULL;
	CExBaseObject *pMatchRef = NULL;
	long nIndex = 1;
	long nCount = pList->GetCount();

	if (m_bInsertNoMatch)
	{
		m_pThreadProgress->SetMaxRange(nCount+1);
	}
	else
	{
		m_pThreadProgress->SetMaxRange(nCount);
	}

	CString strDestID, strSrcID;

	while (pos != NULL)
	{
		pXMatch = (CXMatchObject *)pList->GetNext(pos);
		pMatchRef = pXMatch->GetMatchRef();

		if (pMatchRef != NULL)
		{
			pXMatch->m_pRefObject->m_strName = pMatchRef->m_strName;
			m_pDestObject = pMatchRef;

			//如果ID不一致，则替换ID
			//2014-11-14   lijunqing
			//if (pXMatch->m_pRefObject->m_strID != pMatchRef->m_strID)
			if (GetReplaceID(pXMatch->m_pRefObject, pMatchRef, strSrcID, strDestID))
			{
				CString strMsg;
				//strMsg.Format(_T("【第%d个 共%d个】ID替换：【%s】==>>【%s】"), nIndex, nCount, pXMatch->m_pRefObject->m_strID, pMatchRef->m_strID);
				strMsg.Format(/*_T("【第%d个 共%d个】ID替换：【%s】==>>【%s】")*/g_sLangTxt_IdReplace, nIndex, nCount, strSrcID, strDestID);
				m_pThreadProgress->ShowMsg(strMsg);
				//CDevice *pDevice = (CDevice*)m_pDestCpus->GetParent();
				//CGbItemVariableIDReplace oReplace;
				//oReplace.Replace((CExBaseList*)pDevice, pXMatch->m_pRefObject->m_strID, pMatchRef->m_strID);
				
				//2014-11-14   lijunqing
				//RelpaceID(pXMatch->m_pRefObject->m_strID, pMatchRef->m_strID);
				RelpaceID(strSrcID, strDestID);
			
				//如果是遥测，则替换相关的误差计算量
				if (m_bReplaceAinDataset)
				{
					CExBaseList *pDataset = (CExBaseList*)pXMatch->m_pRefObject->GetParent();
					CExBaseObject *pFind = NULL;
						
					pFind = pDataset->FindByID(g_strAinExand_Abs+pXMatch->m_pRefObject->m_strID);
					if (pFind != NULL)
					{
						pFind->m_strName = g_strAinExand_Abs + pMatchRef->m_strName;
						m_pDestObject = pFind;
						RelpaceID(g_strAinExand_Abs+pXMatch->m_pRefObject->m_strID, g_strAinExand_Abs+pMatchRef->m_strID);
						pFind->m_strID = g_strAinExand_Abs+pMatchRef->m_strID;
					}

					pFind = pDataset->FindByID(g_strAinExand_Rel+pXMatch->m_pRefObject->m_strID);
					if (pFind != NULL)
					{
						pFind->m_strName = g_strAinExand_Rel + pMatchRef->m_strName;
						m_pDestObject = pFind;
						RelpaceID(g_strAinExand_Rel+pXMatch->m_pRefObject->m_strID, g_strAinExand_Rel+pMatchRef->m_strID);
						pFind->m_strID = g_strAinExand_Rel+pMatchRef->m_strID;
					}

					pFind = pDataset->FindByID(g_strAinExand_Rst+pXMatch->m_pRefObject->m_strID);
					if (pFind != NULL)
					{
						pFind->m_strName = g_strAinExand_Rst + pMatchRef->m_strName;
						m_pDestObject = pFind;
						RelpaceID(g_strAinExand_Rst+pXMatch->m_pRefObject->m_strID, g_strAinExand_Rst+pMatchRef->m_strID);
						pFind->m_strID = g_strAinExand_Rst+pMatchRef->m_strID;
					}
				}

				pXMatch->m_pRefObject->m_strID = pMatchRef->m_strID;
				m_pThreadProgress->StepIt();
			}
			else
			{
				m_pThreadProgress->StepIt();
			}
		}
		else
		{
			m_pThreadProgress->StepIt();
		}

		nIndex++;
	}

	m_pDestObject = NULL;

	AfterReplace();

	if (!m_bInsertNoMatch)
	{
		m_pThreadProgress->ShowMsg(/*_T("名称替换完成")*/g_sLangTxt_NameReplaceCompleted);
		m_pThreadProgress->Finish();
		return 0;
	}

	m_pThreadProgress->ShowMsg(/*_T("添加没有匹配成功的对象")*/g_sLangTxt_AddObjMatchUnsucc);
	pos = m_pSelDataObjectOpened->GetHeadPosition();
	CExBaseObject *pSrcData = NULL;

	while (pos != NULL)
	{
		pSrcData = m_pSelDataObjectOpened->GetNext(pos);

		if (m_pSelCurrGbDataObject->FindByName(pSrcData->m_strName) == NULL)
		{
			CExBaseObject *pNew = (CExBaseObject*)pSrcData->Clone();
			m_pSelCurrGbDataObject->AddNewChild(pNew);
		}
	}

	m_pThreadProgress->StepIt();
	m_pThreadProgress->ShowMsg(/*_T("替换完成.......")*/g_sLangTxt_ReplaceCompleted2);
	m_pThreadProgress->Finish();


	return 0;
}

void CGuideBookMmsModelReplace::RelpaceID(const CString &strSrcID, const CString &strDestID)
{
	CDevice *pDevice = (CDevice*)m_pDestCpus->GetParent();
	//CGbItemVariableIDReplace oReplace;
	m_oGbItemVariableIDReplace.SetDestObject(m_pDestObject);
	m_oGbItemVariableIDReplace.Replace((CExBaseList*)pDevice, strSrcID, strDestID);
}

BOOL CGuideBookMmsModelReplace::MatchOrder()
{
	CXMatchList *pList = m_oXMatchTool.GetDstMatchList();
	POS pos = pList->GetHeadPosition();
	CXMatchObject *pXMatch = NULL;
	CExBaseObject *pMatchRef = NULL;
	POS posSel = m_pSelDataObjectOpened->GetHeadPosition();
	CExBaseObject *pData = NULL;

	while (pos != NULL && posSel != NULL)
	{
		pData = m_pSelDataObjectOpened->GetNext(posSel);
		pXMatch = (CXMatchObject *)pList->GetNext(pos);
		pXMatch->SetMacthRefObj(pData);
	}

	m_pGridXMatchEdit->ShowMatch(&m_oXMatchTool);

	return TRUE;
}

BOOL CGuideBookMmsModelReplace::MatchFrom(CExBaseObject *pCurrFrom, CExBaseObject *pRefFrom)
{
	CXMatchList *pList = m_oXMatchTool.GetDstMatchList();
	POS pos = pList->Find(pCurrFrom);
	POS posSel = m_pSelDataObjectOpened->Find(pRefFrom);
	CExBaseObject *pData = NULL;
	CXMatchObject *pXMatch = NULL;

	if (pos == NULL || posSel == NULL)
	{
		return FALSE;
	}

	while (pos != NULL && posSel != NULL)
	{
		pData = m_pSelDataObjectOpened->GetNext(posSel);
		pXMatch = (CXMatchObject *)pList->GetNext(pos);
		pXMatch->SetMacthRefObj(pData);
	}

	m_pGridXMatchEdit->ShowMatch(&m_oXMatchTool);

	return TRUE;
}

void CGuideBookMmsModelReplace::InitXMatchConfig(CXMatchConfig *pXMatchConfig)
{
	CXMatchDatasetRefs *pCXMatchDatasetRefs = pXMatchConfig->m_pXMatchDatasetRefs;
	CXMatchDatarefs *pCXMatchDatarefs =pXMatchConfig->m_pXMatchDatarefs;

	ASSERT (pCXMatchDatasetRefs != NULL);
	ASSERT (pCXMatchDatarefs != NULL);

	pXMatchConfig->m_strSrcDatasetPath = m_pSelCurrGbDataObject->GetIDPathEx(GBCLASSID_CPUS, FALSE);

	//数据集
	pCXMatchDatasetRefs->m_strMmsDvmFile = m_strMmsDvmFile;
	InitXMatchConfigDataset(pXMatchConfig);

	//匹配的数据对象
	CXMatchList *pDestList = m_oXMatchTool.GetDstMatchList();
	POS pos = pDestList->GetHeadPosition();
	CXMatchObject *pXMatchObj = NULL;
	CExBaseObject *pMatchRef = NULL;

	while (pos != NULL)
	{
		pXMatchObj = (CXMatchObject *)pDestList->GetNext(pos);

		if (pXMatchObj->GetMatchRefCount() == 1)
		{
			pMatchRef = pXMatchObj->GetMatchRef();
			pCXMatchDatarefs->AddNewDataRef(pXMatchObj->m_pRefObject->GetIDPathEx(GBCLASSID_CPUS, FALSE)
				, pMatchRef->GetIDPathEx(GBCLASSID_CPUS, FALSE));
		}
	}

}

void CGuideBookMmsModelReplace::InitXMatchConfigDataset(CXMatchConfig *pXMatchConfig)
{
	CXMatchDatasetRefs *pCXMatchDatasetRefs = pXMatchConfig->m_pXMatchDatasetRefs;
	CXMatchDatarefs *pCXMatchDatarefs =pXMatchConfig->m_pXMatchDatarefs;

	ASSERT (pCXMatchDatasetRefs != NULL);
	ASSERT (pCXMatchDatarefs != NULL);

	//数据集
	pCXMatchDatasetRefs->AddNewDataset(m_pSelDataObjectOpened->GetIDPathEx(GBCLASSID_CPUS, FALSE));
}


BOOL CGuideBookMmsModelReplace::XMatchConfigSave()
{
	CString strPath;
	strPath = wzd_GetXMatchFilePath();

#ifdef GB_USE_XFILEMNGRBASE
	CXFileMngr oFileMngrBase;
	oFileMngrBase.SearchFiles(g_strGbXMatchFileName, g_strGbXMatchFilePostFix, strPath);

	CDlgXFileMngr dlg(0, g_strGbXMatchFilePostFix, g_strGbXMatchFileName, &oFileMngrBase, SAVE_FILE_MODE, m_pWndRef);
#else
	CFileMngrBase oFileMngrBase;

	oFileMngrBase.SetRootPath(strPath);
	oFileMngrBase.m_strName.Format(_T("%s管理"), g_strGbXMatchFileName);
	oFileMngrBase.m_strID = strPath;
	oFileMngrBase.Traverse(strPath, g_strGbXMatchFilePostFix, TRUE);

	CDlgFileMngr dlg(0, g_strGbXMatchFilePostFix, g_strGbXMatchFileName, &oFileMngrBase, SAVE_FILE_MODE, m_pWndRef);
#endif


	if(dlg.DoModal() == IDOK)
	{
		m_strXMatchFile = dlg.GetFileName();
		CXMatchConfig oXMatchConfig;
		oXMatchConfig.InitAfterRead();
		InitXMatchConfig(&oXMatchConfig);
		oXMatchConfig.SaveXmlFile(m_strXMatchFile, CKeyDbXmlRWKeys::g_pXmlKeys);
		return TRUE;
	}

	return FALSE;
}

BOOL CGuideBookMmsModelReplace::XMatchConfigOpen(CXMatchConfig &oXMatchConfig)
{
	CString strPath;
	strPath = wzd_GetXMatchFilePath();

#ifdef GB_USE_XFILEMNGRBASE
	CXFileMngr oFileMngrBase;
	oFileMngrBase.SearchFiles(g_strGbXMatchFileName, g_strGbXMatchFilePostFix, strPath);

	CDlgXFileMngr dlg(0, g_strGbXMatchFilePostFix, g_strGbXMatchFileName, &oFileMngrBase, OPEN_FILE_MODE, m_pWndRef);
#else
	CFileMngrBase oFileMngrBase;
	oFileMngrBase.SetRootPath(strPath);
	oFileMngrBase.m_strName.Format(_T("%s管理"), g_strGbXMatchFileName);
	oFileMngrBase.m_strID = strPath;
	oFileMngrBase.Traverse(strPath, g_strGbXMatchFilePostFix, TRUE);

	CDlgFileMngr dlg(0, g_strGbXMatchFilePostFix, g_strGbXMatchFileName, &oFileMngrBase, OPEN_FILE_MODE, m_pWndRef);
#endif


	if(dlg.DoModal() == IDOK)
	{
		m_strXMatchFile = dlg.GetFileName();
		oXMatchConfig.OpenXmlFile(m_strXMatchFile, CKeyDbXmlRWKeys::CXMatchConfigKey(), CKeyDbXmlRWKeys::g_pXmlKeys);

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CGuideBookMmsModelReplace::InitDestCpus()
{
	m_oListTemp.Append(m_pDestCpus);
	m_pDestCpus->RemoveAll();
	m_pDestCpus->AppendEx(m_oCpusDest);
	m_oCpusDest.RemoveAll();
}

void CGuideBookMmsModelReplace::XMatchByConfig(CXMatchConfig *pConfig)
{
	CDataSet *pDataset = NULL;
	CDataSet *pDatasetTemp = NULL;

	//获取当前设备数据模型的数据集
	pDataset = m_oCpusDest.SelectDataset(pConfig->m_strSrcDatasetPath, _T("$"));

	if (pDataset == NULL)
	{
		return;
	}

	//获取目标数据集
	CXMatchDatasetRefs *pXMatchDatasetRefs = pConfig->m_pXMatchDatasetRefs;
	POS pos = pXMatchDatasetRefs->GetHeadPosition();
	CXMatchDatasetRef *pDatasetRef = NULL;
	
	if (!OpenMmsDvmFile(pXMatchDatasetRefs->m_strMmsDvmFile))
	{
		return;
	}

	m_oListDatasetRef.RemoveAll();

	while (pos != NULL)
	{
		pDatasetRef = (CXMatchDatasetRef *)pXMatchDatasetRefs->GetNext(pos);
		pDatasetTemp = m_oCpusSrc.SelectDataset(pDatasetRef->m_strID, _T("$"));

		if (pDatasetTemp != NULL)
		{
			m_oListDatasetRef.AddTail(pDatasetTemp);
		}
	}

	if (m_oListDatasetRef.GetCount() == 0)
	{
		return;
	}

	InitListDatasetRef();

	//根据文件信息初始化XMatch
	m_pSelCurrGbDataObject = pDataset;
	m_pSelDataObjectOpened = (CExBaseList *)m_oListDatasetRef.GetHead();
	XMatch(FALSE);
	
	XMatchRead(pConfig);
}


void CGuideBookMmsModelReplace::XMatchRead(CXMatchConfig *pConfig)
{
	m_oXMatchTool.MatchReadSingle(pConfig->m_pXMatchDatarefs, m_pSelDataObjectOpened, m_pSelCurrGbDataObject, GBCLASSID_CPUS);
	CXMatchList *pList = m_oXMatchTool.GetDstMatchList();
	m_pGridXMatchEdit->ShowMatch(&m_oXMatchTool);
}