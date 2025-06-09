#include "stdafx.h"
#include "GuideBookMmsModelsReplace.h"
#include "..\..\Module\GuideBook\GbItemVariableIDReplaceEx.h"
#include "..\XLanguageResourceAts.h"

CGuideBookMmsModelsReplace::CGuideBookMmsModelsReplace()
{
	m_nCommCmdCount = 0;
}	

CGuideBookMmsModelsReplace::~CGuideBookMmsModelsReplace()
{
	m_oListDatasetRef,RemoveAll();
	m_oListDatasOpened.RemoveAll();
}

BOOL CGuideBookMmsModelsReplace::AddDataset(CExBaseList *pDataset)
{
	if (m_oListDatasetRef.Find(pDataset) != NULL)
	{
		return FALSE;
	}

	m_oListDatasetRef.AddTail(pDataset);
	m_oListDatasOpened.Append(pDataset);
	return TRUE;
}

BOOL CGuideBookMmsModelsReplace::RemoveDataset(CExBaseList *pDataset)
{
	m_oListDatasetRef.Remove(pDataset);
	InitListDatasetRef();

	return TRUE;
}


BOOL CGuideBookMmsModelsReplace::XMatch(BOOL bShowMatch)
{
	if (m_pSelDataObjectOpened != NULL && m_pSelCurrGbDataObject != NULL)
	{
		if (m_pSelDataObjectOpened->GetClassID() == GBCLASSID_DATASET
			&& m_pSelCurrGbDataObject->GetClassID() == GBCLASSID_DATASET)
		{
			m_oXMatchTool.Match(&m_oKeyDB, &m_oListDatasOpened, m_pSelCurrGbDataObject);

			CXMatchList *pList = m_oXMatchTool.GetDstMatchList();
			m_pGridXMatchEdit->SetShowID(TRUE);
			m_pGridXMatchEdit->ShowMatch(&m_oXMatchTool);
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

void CGuideBookMmsModelsReplace::XMatchRead(CXMatchConfig *pConfig)
{
	m_oXMatchTool.MatchReadSingle(pConfig->m_pXMatchDatarefs, &m_oListDatasOpened, m_pSelCurrGbDataObject, GBCLASSID_CPUS);
	CXMatchList *pList = m_oXMatchTool.GetDstMatchList();
	m_pGridXMatchEdit->ShowMatch(&m_oXMatchTool);
}

void CGuideBookMmsModelsReplace::ReplaceDataSet(CThreadProgressInterface *pThreadProgress)
{
	CExBaseList *pDatasetDest = (CExBaseList*)m_pSelCurrGbDataObject->GetParent();
	pDatasetDest->Remove(m_pSelCurrGbDataObject);
	pDatasetDest->AppendCloneEx(m_oListDatasetRef, TRUE);
	m_oListTemp.AddTail(m_pSelCurrGbDataObject);
	
	//替换逻辑设备ID
	CDevice *pDevice = (CDevice*)m_pDestCpus->GetParent();
	CCpu *pCpuOld = (CCpu*)m_pSelCurrGbDataObject->GetAncestor(GBCLASSID_CPU);
	CExBaseObject *p = m_oListDatasetRef.GetHead();
	ASSERT( p != NULL );
	CCpu *pCpuNew = (CCpu*)p->GetAncestor(GBCLASSID_CPU);

	if (pCpuNew->m_strID != pCpuOld->m_strID)
	{
		//CGbItemVariableIDReplace oReplace;
		m_oGbItemVariableIDReplace.Replace((CExBaseList*)pDevice, pCpuOld->m_strID, pCpuNew->m_strID);
		pCpuOld->m_strID = pCpuNew->m_strID;
		pCpuOld->m_strName = pCpuNew->m_strName;
	}

	CGuideBookMmsModelReplace::ReplaceDataSet(pThreadProgress);

}

void CGuideBookMmsModelsReplace::RelpaceID(const CString &strSrcID, const CString &strDestID)
{
	m_nCommCmdCount++;
	CGuideBookMmsModelReplace::RelpaceID(strSrcID, strDestID);
	return;

//	CDevice *pDevice = (CDevice*)m_pDestCpus->GetParent();
//	CGbItemVariableIDReplaceEx oReplace;
//	oReplace.CGbItemVariableIDReplace::Replace((CExBaseList*)pDevice, strSrcID, strDestID);
}

void CGuideBookMmsModelsReplace::AfterReplace()
{
	if (m_pThreadProgress != NULL)
	{
		m_pThreadProgress->SetMaxRange(m_nCommCmdCount);
	}

	CDevice *pDevice = (CDevice*)m_pDestCpus->GetParent();

	SplitCommCmd((CExBaseList*)pDevice);
}

void CGuideBookMmsModelsReplace::SplitCommCmd(CExBaseList *pList)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == GBCLASSID_COMMCMD)
		{
			SplitCommCmd((CCommCmd*)p);
		}
		else if (nClassID == GBCLASSID_ITEMS)
		{
			SplitCommCmd((CExBaseList*)p);
		}
	}
}

void CGuideBookMmsModelsReplace::SplitCommCmd(CCommCmd *pCommCmd)
{
	if (m_pThreadProgress != NULL)
	{
		CString strMsg;
		m_pThreadProgress->StepIt();
		strMsg.Format(/*_T("处理通讯命令：%s")*/g_sLangTxt_DealCommCmd , pCommCmd->GetNamePathEx(GBCLASSID_DEVICE, FALSE));
		m_pThreadProgress->ShowMsg(strMsg);
	}

	CDevice *pDevice = (CDevice*)pCommCmd->GetAncestor(GBCLASSID_DEVICE);

	if (pDevice != NULL)
	{
		CGbCommCmdSplit oSplit;
		oSplit.AttatchCpus(&m_oCpusDest);
		oSplit.InitCommCmdItemDatasetPath(pDevice, pCommCmd);
	}
}

void CGuideBookMmsModelsReplace::InitXMatchConfigDataset(CXMatchConfig *pXMatchConfig)
{
	CXMatchDatasetRefs *pCXMatchDatasetRefs = pXMatchConfig->m_pXMatchDatasetRefs;
	CXMatchDatarefs *pCXMatchDatarefs =pXMatchConfig->m_pXMatchDatarefs;

	ASSERT (pCXMatchDatasetRefs != NULL);
	ASSERT (pCXMatchDatarefs != NULL);

	//数据集
	POS pos = m_oListDatasetRef.GetHeadPosition();
	CExBaseObject *pDatset = NULL;

	while (pos != NULL)
	{
		pDatset = (CExBaseObject *)m_oListDatasetRef.GetNext(pos);
		pCXMatchDatasetRefs->AddNewDataset(pDatset->GetIDPathEx(GBCLASSID_CPUS, FALSE));
	}
}

void CGuideBookMmsModelsReplace::InitListDatasetRef()
{
	m_oListDatasOpened.RemoveAll();

	POS pos = m_oListDatasetRef.GetHeadPosition();
	CExBaseList *pDataset = NULL;

	while (pos != NULL)
	{
		pDataset = (CExBaseList*)m_oListDatasetRef.GetNext(pos);
		m_oListDatasOpened.Append(pDataset);
	}
}



BOOL CGuideBookMmsModelsReplace::MatchFrom(CExBaseObject *pCurrFrom, CExBaseObject *pRefFrom)
{
	CXMatchList *pList = m_oXMatchTool.GetDstMatchList();
	POS pos = pList->Find(pCurrFrom);
	CExBaseList *pRefFromList = (CExBaseList*)pRefFrom->GetParent();
	POS posSel = pRefFromList->Find(pRefFrom);
	CExBaseObject *pData = NULL;
	CXMatchObject *pXMatch = NULL;

	if (pos == NULL || posSel == NULL)
	{
		return FALSE;
	}

	while (pos != NULL && posSel != NULL)
	{
		pData = pRefFromList->GetNext(posSel);
		pXMatch = (CXMatchObject *)pList->GetNext(pos);
		pXMatch->SetMacthRefObj(pData);
	}

	m_pGridXMatchEdit->ShowMatch(&m_oXMatchTool);
	return TRUE;
}