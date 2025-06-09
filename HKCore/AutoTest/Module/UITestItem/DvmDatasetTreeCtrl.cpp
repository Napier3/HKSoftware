// DvmDatasetTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "DvmDatasetTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDvmDatasetTreeCtrl

IMPLEMENT_DYNAMIC(CDvmDatasetTreeCtrl, CTreeCtrl)

CDvmDatasetTreeCtrl::CDvmDatasetTreeCtrl()
{
	m_bShowTestPara = FALSE;
}

CDvmDatasetTreeCtrl::~CDvmDatasetTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CDvmDatasetTreeCtrl, CTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CDvmDatasetTreeCtrl::OnTvnSelchanged)
END_MESSAGE_MAP()



// CDvmDatasetTreeCtrl 消息处理程序



void CDvmDatasetTreeCtrl::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	CExBaseObject *pSel = (CExBaseObject *)pNMTreeView->itemNew.lParam;

	if (pSel == NULL)
	{
		return;
	}

	UINT nClassID = pSel->GetClassID();

	if (nClassID == GBCLASSID_DATASET || GBCLASSID_DEVICE_SYSPARAS == nClassID
		|| nClassID == GBCLASSID_DATASETGROUP)
	{
		CDataSet *pDataset = (CDataSet*)pSel;
		m_pDatasetListCtrl->DeleteAllItems();
		pDataset->InsertChildToListCtrl(m_pDatasetListCtrl, 0);
	}
	else if (nClassID == DVMCLASSID_CDVMDATASET)
	{
		CDvmDataset *pDataset = (CDvmDataset*)pSel;
		m_pDatasetListCtrl->DeleteAllItems();
		pDataset->InsertChildToListCtrl(m_pDatasetListCtrl, 0);
	}

	*pResult = 0;
}

//2021-10-14  lijunqing
void CDvmDatasetTreeCtrl::ShowDataset(CDataSet *pDataset, HTREEITEM hParent)
{
	pDataset->InsertOwnTreeCtrl(this, hParent);
	HTREEITEM hCurr = (HTREEITEM)pDataset->m_dwItemData;

	if (pDataset->GetClassID() == GBCLASSID_DATASET)
	{
		return;
	}

	POS pos = pDataset->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pDataset->GetNext(pos);

		if (p->GetClassID() == GBCLASSID_DATASETGROUP)
		{
			ShowDataset((CDataSet*)p, hCurr);
		}
	}
}

void CDvmDatasetTreeCtrl::ShowDevice(CDevice *pDevice, CDvmDataset *pDsGlobalDatas)
{
	if (pDevice == NULL)
	{
		return;
	}

	CExBaseList oListCpus;
	pDevice->GetCpusList(oListCpus);
	CCpus *pCpus = NULL;
	CDataSet *pDataset = NULL;
	POS posDataset = NULL;
	CCpu *pCpu = NULL;

	HTREEITEM hRoot = InsertItem(g_sLangTxt_GlobalData, 0, 0, TVI_ROOT);
	SetItemData(hRoot, (DWORD)pDsGlobalDatas);

	pDataset = pDevice->GetTestParas();
	pDataset->InsertOwnTreeCtrl(this, TVI_ROOT);

	CGuideBook *pGuideBook = (CGuideBook*)pDevice->GetParent();
	CDvmDataset *pTemp = pGuideBook->GetTestApp(FALSE);

	if (pTemp != NULL)
	{
		pTemp->InsertOwnTreeCtrl(this, TVI_ROOT);
	}

	CDvmDataset *pTestAppDef = pGuideBook->GetTestAppDefine(FALSE);

	if (pTestAppDef != NULL)
	{
		pTestAppDef->InsertOwnTreeCtrl(this, TVI_ROOT);
	}

	if (oListCpus.GetCount() == 0)
	{
		return;
	}

	HTREEITEM hItemCpus = NULL, hItemDataset=NULL;

	POS posCpus = oListCpus.GetHeadPosition();

	while (posCpus != NULL)
	{
		pCpus = (CCpus *)oListCpus.GetNext(posCpus);
		CString strTemp;
		strTemp.Format(_T("%s[%s]"), pCpus->m_strName, pCpus->m_strID);
		hItemCpus = InsertItem(strTemp, 0, 0, TVI_ROOT);
		POS posCpu = pCpus->GetHeadPosition();

		while (posCpu != NULL)
		{
			pCpu = (CCpu*)pCpus->GetNext(posCpu);
			pCpu->InsertOwnTreeCtrl(this, hItemCpus);
			posDataset = pCpu->GetHeadPosition();

			while (posDataset != NULL)
			{
				pDataset = (CDataSet *)pCpu->GetNext(posDataset);
				ShowDataset(pDataset, (HTREEITEM)pCpu->m_dwItemData);
			}

			Expand((HTREEITEM)pCpu->m_dwItemData, TVE_EXPAND);
		}

		Expand(hItemCpus, TVE_EXPAND);
	}
	
	Select(hRoot, TVGN_CARET);
	oListCpus.RemoveAll();
}

