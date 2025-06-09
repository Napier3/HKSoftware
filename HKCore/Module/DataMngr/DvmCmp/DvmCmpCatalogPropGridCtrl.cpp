#include "StdAfx.h"
#include "DvmCmpCatalogPropGridCtrl.h"
#include "..\..\XLanguage\XLanguageResource.h"

//////////////////////////////////////////////////////////////////////////
//CDvmCmpCatalogPropGridCtrl
CDvmCmpCatalogPropGridCtrl::CDvmCmpCatalogPropGridCtrl()
{	
	m_clrLine = RGB(128, 128, 128);
	m_pMsgRcvWnd = NULL;
	m_bIngnoreSetCurrSel = FALSE;
	m_pDvmDeviceMap = NULL;
}

CDvmCmpCatalogPropGridCtrl::~CDvmCmpCatalogPropGridCtrl()
{
	
}

void CDvmCmpCatalogPropGridCtrl::UpdatePropGridCtrl(CExBaseList &listNew, CExBaseList &listDelete) 
{

}

// 
// void CDvmCmpCatalogPropGridCtrl::SetDevice(CDvmDevice *pDvmDevice)
// {
// 	m_pDvmDevice = pDvmDevice;
// 
// 	CDvmCmpPropGridProperty* pRoot = NULL;
// 
// 	pRoot = new CDvmCmpPropGridProperty(m_pDvmDevice->m_strName);
// 
// 	POS pos = m_pDvmDevice->GetHeadPosition();
// 	CDvmLogicDevice *pLdDevice = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pLdDevice = (CDvmLogicDevice *)m_pDvmDevice->GetNext(pos);
// 		AddDvmLdevice(pLdDevice, pRoot);
// 	}
// 	
// 	AddProperty(pRoot);
// 	
// 	AdjustLayout();
// 	Invalidate(FALSE);
// }
// 
// void CDvmCmpCatalogPropGridCtrl::AddDvmLdevice(CDvmLogicDevice  *pDvmLdevice, CDvmCmpPropGridProperty *pParent)
// {
// 	CDvmCmpPropGridProperty* pLdProp = NULL;
// 	CDvmCmpPropGridProperty* pDsProp = NULL;
// 
// 	pLdProp = new CDvmCmpPropGridProperty(pDvmLdevice->m_strName);
// 	pDvmLdevice->m_dwItemData = (DWORD)pLdProp;
// 	pLdProp->SetData((DWORD)pDvmLdevice);
// 
// 	POS pos = pDvmLdevice->GetHeadPosition();
// 	CDvmDataset *pDataset = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pDataset = (CDvmDataset *)pDvmLdevice->GetNext(pos);
// 		pDsProp = new CDvmCmpPropGridProperty(pDataset->m_strName, pDataset->m_strID, _T(""));
// 		pLdProp->AddSubItem(pDsProp);
// 		pDataset->m_dwItemData = (DWORD)pDsProp;
// 		pDsProp->SetData((DWORD)pDataset);
// 		pDsProp->AllowEdit(FALSE);
// 	}
// 
// 	pParent->AddSubItem(pLdProp);
// }


BEGIN_MESSAGE_MAP(CDvmCmpCatalogPropGridCtrl, CMFCPropertyGridCtrl)
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


void CDvmCmpCatalogPropGridCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	OnLButtonDblClkMsg();

	__super::OnLButtonDblClk(nFlags, point);
}

//////////////////////////////////////////////////////////////////////////
//CDvmCmpCatalogStandPropGridCtrl
CDvmCmpCatalogStandPropGridCtrl::CDvmCmpCatalogStandPropGridCtrl()
{
	
}

CDvmCmpCatalogStandPropGridCtrl::~CDvmCmpCatalogStandPropGridCtrl()
{

}

BEGIN_MESSAGE_MAP(CDvmCmpCatalogStandPropGridCtrl, CDvmCmpCatalogPropGridCtrl)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

void CDvmCmpCatalogStandPropGridCtrl::ShowDvmCmpCatalog(CDvmDeviceMap *pDvmDeviceMap)
{
	RemoveAll();

	if (pDvmDeviceMap == NULL)
	{
		return;
	}

	m_pDvmDeviceMap = pDvmDeviceMap;
	m_pDvmDevice = (CDvmDevice*)pDvmDeviceMap->m_pStand;
	CDvmCmpPropGridProperty* pRoot = NULL;
	pRoot = new CDvmCmpPropGridProperty(m_pDvmDevice->m_strName);
	pRoot->SetData((DWORD)pDvmDeviceMap);
	pDvmDeviceMap->m_dwItemData = (DWORD)pRoot;
	POS pos = pDvmDeviceMap->GetHeadPosition();
	CDvmLDeviceMap *pLdDevice = NULL;

	while (pos != NULL)
	{
		pLdDevice = (CDvmLDeviceMap *)pDvmDeviceMap->GetNext(pos);
		AddDvmLdevice(pLdDevice, pRoot);
	}

	AddProperty(pRoot);

	AdjustLayout();
	Invalidate(FALSE);
}

CDvmCmpPropGridProperty* CDvmCmpCatalogStandPropGridCtrl::NewDatasetProp(CDvmDatasetMap *pDatasetMap)
{
	CString strMapPath;
	CDvmCmpPropGridProperty *pDsProp = NULL;
	CString strName;
	strName = pDatasetMap->GetDvmCmpPropGridPropertyName();

	if (pDatasetMap->m_pMap != NULL)
	{
		if (pDatasetMap->m_strLdvice != pDatasetMap->m_strLdviceMap)
		{
			strMapPath.Format(_T("%s_(%s$%s)"),pDatasetMap->m_pMap->m_strName, pDatasetMap->m_strLdviceMap, pDatasetMap->m_pMap->m_strID);
		}
		else
		{
			strMapPath.Format(_T("%s_(%s)"), pDatasetMap->m_pMap->m_strName, pDatasetMap->m_pMap->m_strID);
		}

		pDsProp = new CDvmCmpPropGridProperty(strName, strMapPath, _T(""));
	}
	else
	{
		pDsProp = new CDvmCmpPropGridProperty(strName, _T(""), _T(""));
	}

	pDsProp->SetData((DWORD)pDatasetMap);
	pDatasetMap->m_dwItemData = (DWORD)pDsProp;

// 	CPaintDC dcPaint(this); // device context for painting
// 	CMemDC memDC(dcPaint, this);
// 	CDC* pDC = &memDC.GetDC();
// 
// 	pDsProp->SetTextColor(pDatasetMap->IsAllMaped(), pDC);

	return pDsProp;
}

void CDvmCmpCatalogStandPropGridCtrl::InitDatasetProp(CDvmDatasetMap *pDatasetMap, CDvmCmpPropGridProperty *pDsProp)
{
	CString strMapPath;

	if (pDatasetMap->m_pMap != NULL)
	{
		if (pDatasetMap->m_strLdvice != pDatasetMap->m_strLdviceMap)
		{
			strMapPath.Format(_T("%s$%s"), pDatasetMap->m_strLdviceMap, pDatasetMap->m_pMap->m_strID);
		}
		else
		{
			strMapPath = pDatasetMap->m_pMap->m_strID;
		}
	}

	pDsProp->SetValue(strMapPath);
}

void CDvmCmpCatalogStandPropGridCtrl::AddDvmLdevice(CDvmLDeviceMap  *pDvmLdevice, CDvmCmpPropGridProperty *pParent)
{
	CDvmCmpPropGridProperty* pLdProp = NULL;
	CDvmCmpPropGridProperty* pDsProp = NULL;

	pLdProp = new CDvmCmpPropGridProperty(pDvmLdevice->m_strName);
	pDvmLdevice->m_dwItemData = (DWORD)pLdProp;
	pLdProp->SetData((DWORD)pDvmLdevice);

	POS pos = pDvmLdevice->GetHeadPosition();
	CDvmDatasetMap *pDatasetMap = NULL;
	CString strMapPath;

	while (pos != NULL)
	{
		pDatasetMap = (CDvmDatasetMap *)pDvmLdevice->GetNext(pos);
		pDsProp = NewDatasetProp(pDatasetMap);
		pLdProp->AddSubItem(pDsProp);
		pDatasetMap->m_dwItemData = (DWORD)pDsProp;
		pDsProp->SetData((DWORD)pDatasetMap);
		pDsProp->AllowEdit(FALSE);
	}

	pParent->AddSubItem(pLdProp);
}

void CDvmCmpCatalogStandPropGridCtrl::OnChangeSelection(CMFCPropertyGridProperty* pNewSel, CMFCPropertyGridProperty* pOldSel)
{
	if (m_bIngnoreSetCurrSel)
	{
		return;
	}

	if (pNewSel == NULL)
	{
		return;
	}

	CExBaseObject *pSelObj = (CExBaseObject*)pNewSel->GetData();

	if (pSelObj == NULL)
	{
		return;
	}

	if (pSelObj->GetClassID() != DMPCLASSID_CDVMDATASETMAP)
	{
		return;
	}

	if (m_pDvmCmpBasePropGridCtrlRef == NULL)
	{
		return;
	}

	CDvmDatasetMap *pDatasetMap = (CDvmDatasetMap*)pSelObj;

	if (pDatasetMap->m_pMap == NULL)
	{
		return;
	}

	CDvmCmpPropGridProperty *pProp = (CDvmCmpPropGridProperty*)pDatasetMap->m_pMap->m_dwItemData;

	if (pProp == NULL)
	{
		return;
	}

	m_pDvmCmpBasePropGridCtrlRef->m_bIngnoreSetCurrSel = TRUE;
	m_pDvmCmpBasePropGridCtrlRef->EnsurePropVisible(pProp, TRUE);
	m_pDvmCmpBasePropGridCtrlRef->SetCurSel(pProp);
	m_pDvmCmpBasePropGridCtrlRef->m_bIngnoreSetCurrSel = FALSE;
}


void CDvmCmpCatalogStandPropGridCtrl::OnLButtonDblClkMsg()
{
	CExBaseObject *pSelObj = GetSelectData();

	if (pSelObj == NULL)
	{
		return;
	}

	if (pSelObj->GetClassID() != DMPCLASSID_CDVMDATASETMAP)
	{
		return;
	}

	CWnd *pParent = GetParent();
	pParent->PostMessage(WM_OPEN_DVMCMP_DATASET, (WPARAM)pSelObj, (LPARAM)pSelObj);
}

void CDvmCmpCatalogStandPropGridCtrl::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CExBaseObject *pSelObj = GetSelectData();

	if (pSelObj == NULL)
	{
		return;
	}

	if (pSelObj->GetClassID() != DMPCLASSID_CDVMDATASETMAP)
	{
		return;
	}

	CDvmDatasetMap *pDatasetMap = (CDvmDatasetMap*)pSelObj;

	CMenu menu;		
	menu.CreatePopupMenu();

	menu.AppendMenu(MF_STRING,ID_DVMMAP_CREATEDATAMAP_STAND,g_sLangTxt_CreatDataMap2/*_T("创建数据集映射")*/);

	if (pDatasetMap->m_pMap != NULL)
	{
		menu.AppendMenu(MF_STRING,ID_DVMMAP_DELETEDATAMAP_STAND,g_sLangTxt_DeleteDataMap2/*_T("删除数据集映射")*/);
	}

	CWnd *pOwer = pWnd->GetParent();
	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,pOwer);	
}

void CDvmCmpCatalogStandPropGridCtrl::DeleteMap()
{
	CDvmDatasetMap *pDataSetMap = (CDvmDatasetMap*)GetSelectData(DMPCLASSID_CDVMDATASETMAP);

	if (pDataSetMap == NULL)
	{
		return;
	}

	if (pDataSetMap->m_pMap != NULL)
	{
		//是否考虑删除属性CDvmCmpPropGridProperty *pPropMap?
		//待确认

		//CDvmCmpPropGridProperty *pPropMap = (CDvmCmpPropGridProperty*)pDataSetMap->m_pMap->m_dwItemData;
		CDvmCmpPropGridProperty *pPropMap = (CDvmCmpPropGridProperty*)pDataSetMap->m_dwItemData;
		pPropMap->SetValue(_T(""));

		CString strName;
		strName.Format(_T("%s_(%s)"), pDataSetMap->m_pStand->m_strName, pDataSetMap->m_pStand->m_strID);

		CString strID = pDataSetMap->m_pStand->m_strID;
		long nCount = 0;

		//对于定值、压板、设备参数数据集，分子为匹配映射的数据个数，分母为目标数据集中数据个数
		if (strID.Find(_T("Setting")) >= 0 || strID.Find(_T("Ena")) >= 0 || strID.Find(_T("Parameter")) >= 0)
		{
			CDvmDataset *pMap = (CDvmDataset *)pDataSetMap->m_pMap;
			nCount = pMap->GetCount();
		}
		else
		{
			nCount = pDataSetMap->GetCount();
		}

		strName.AppendFormat(_T("------------------0/%d"), nCount);
		pPropMap->SetName(strName);
	}

	DeleteMap(pDataSetMap);
}

void CDvmCmpCatalogStandPropGridCtrl::DeleteMap(CDvmDatasetMap *pDatasetMap)
{
	CExBaseList *pParent = (CExBaseList*)pDatasetMap->GetParent();

	CMFCPropertyGridProperty *pProp = (CMFCPropertyGridProperty*)pDatasetMap->m_dwItemData;
	CExBaseList oList;
	m_pDvmDeviceMap->FindDvmMapObj_ByStand(DMPCLASSID_CDVMDATASETMAP, pDatasetMap->m_pStand, oList);

	if (oList.GetCount() > 1)
	{
		CDvmCmpPropGridProperty *pPropLd = (CDvmCmpPropGridProperty*)pProp->GetParent();
		pPropLd->RemoveSubItem(pProp);
		pParent->Delete(pDatasetMap);
		AdjustLayout();
		Invalidate(FALSE);
	}
	else
	{
		pDatasetMap->ClearDatasetMap();
		pDatasetMap->m_pMap = NULL;
		pProp->SetValue(_T(""));
		Invalidate(FALSE);
		pDatasetMap->DeleteAll();
		pDatasetMap->m_strMapID.Empty();
		pDatasetMap->m_strMapName.Empty();
	}

	oList.RemoveAll();
}


CDvmDatasetMap* CDvmCmpCatalogStandPropGridCtrl::AddDatasetMap(CDvmDataset *pDestDataset, BOOL bNewStandDataset)
{
	CDvmDatasetMap *pDatasetMap = (CDvmDatasetMap*)GetSelectData(DMPCLASSID_CDVMDATASETMAP);

	if (pDatasetMap == NULL)
	{
		return NULL;
	}

	CDvmLDeviceMap *pLdeviceMap = (CDvmLDeviceMap*)pDatasetMap->GetParent();
	CDvmDatasetMap *pAdd = pLdeviceMap->AddDvmMap(pDatasetMap, pDestDataset, bNewStandDataset);
	CMFCPropertyGridProperty *pProp = NULL;

	if (pDatasetMap == pAdd)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("选择的数据集与当前的映射一致！"));
		pProp = (CMFCPropertyGridProperty*)pDatasetMap->m_dwItemData;
	}
	else
	{
		CDvmCmpPropGridProperty* pDsProp = NULL;
		CDvmCmpPropGridProperty* pLdProp = (CDvmCmpPropGridProperty*)pLdeviceMap->m_dwItemData;
		pDsProp = NewDatasetProp(pAdd);
		pLdProp->AddSubItem(pDsProp);
		pAdd->m_dwItemData = (DWORD)pDsProp;
		pDsProp->SetData((DWORD)pAdd);
		pDsProp->AllowEdit(FALSE);
		pProp = pDsProp;
		SetCurSel(pProp);
		AdjustLayout();
	}

	CExBaseObject *pMapParent = (CExBaseObject*)pDestDataset->GetParent();
	CString strLdPath;
	pAdd->m_strMapName = pDestDataset->m_strName;
	pAdd->m_strMapID   = pDestDataset->m_strID;
	pAdd->m_strLdviceMap = pMapParent->m_strID;

	if (pMapParent->m_strID != pAdd->m_strLdvice)
	{
		//strLdPath.Format(_T("%s$%s"), pMapParent->m_strID, pDestDataset->m_strID);
		strLdPath.Format(_T("%s_(%s$%s)"),pDestDataset->m_strName, pMapParent->m_strID, pDestDataset->m_strID);
	}
	else
	{
		strLdPath = pDestDataset->m_strID;
	}

	pProp->SetValue(strLdPath);

	//映射数据集ID
// 	pProp = (CMFCPropertyGridProperty*)pDestDataset->m_dwItemData;
// 	pProp->SetValue(pAdd->m_strID);

	Invalidate(FALSE);

	return pAdd;
}


CDvmDatasetMap* CDvmCmpCatalogStandPropGridCtrl::AddDatasetMap(CDvmDataset *pStandDataset, CDvmDataset *pDestDataset)
{
	CExBaseList oList;
	m_pDvmDeviceMap->FindDvmMapObj_ByStand(DMPCLASSID_CDVMDATASETMAP, pStandDataset, oList);
	CDvmDatasetMap *pDatasetMap = NULL;
	CDvmLDeviceMap *pLdviceMap = NULL;

	if (oList.GetCount() == 0)
	{
		return NULL;
	}

	pDatasetMap = (CDvmDatasetMap*)oList.GetHead();
	pLdviceMap = (CDvmLDeviceMap *)pDatasetMap->GetParent();
	CDvmCmpPropGridProperty *pDstasetMapProp = NULL;

	if (oList.GetCount() == 1)
	{
		if (pDatasetMap->m_pMap != NULL)
		{
			pDatasetMap = NULL;
		}
	}
	else
	{
		pDatasetMap = (CDvmDatasetMap*)pLdviceMap->FindDvmMapObj(pStandDataset, pDestDataset);

		if (pDatasetMap != NULL)
		{
			return pDatasetMap;
		}
	}

	//存在映射关系
	if (pDatasetMap == NULL)
	{
		pDatasetMap = pLdviceMap->AddDvmMap(pStandDataset, pDestDataset);
		CMFCPropertyGridProperty *pLdProp = (CMFCPropertyGridProperty*)pLdviceMap->m_dwItemData;
		pDstasetMapProp = NewDatasetProp(pDatasetMap);
		pLdProp->AddSubItem(pDstasetMapProp);
		SetCurSel(pDstasetMapProp);
		AdjustLayout();
		Invalidate(FALSE);
	}
	else
	{//不存在映射关系
		pDatasetMap->SetDataset_Map(pDestDataset);
		pDstasetMapProp = (CDvmCmpPropGridProperty *)pDatasetMap->m_dwItemData;
		InitDatasetProp(pDatasetMap, pDstasetMapProp);
	}

	oList.RemoveAll();

	return pDatasetMap;
}

//////////////////////////////////////////////////////////////////////////
//CDvmCmpCatalogMapPropGridCtrl
CDvmCmpCatalogMapPropGridCtrl::CDvmCmpCatalogMapPropGridCtrl()
{
	m_pDvmDeviceMap = NULL;
}

CDvmCmpCatalogMapPropGridCtrl::~CDvmCmpCatalogMapPropGridCtrl()
{

}


BEGIN_MESSAGE_MAP(CDvmCmpCatalogMapPropGridCtrl, CDvmCmpCatalogPropGridCtrl)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

void CDvmCmpCatalogMapPropGridCtrl::ShowDvmCmpCatalog(CDvmDeviceMap *pDvmDeviceMap)
{
	RemoveAll();
	m_pDvmDeviceMap = pDvmDeviceMap;
	m_pDvmDevice = (CDvmDevice*)pDvmDeviceMap->m_pMap;
	CDvmCmpPropGridProperty* pRoot = NULL;
	pRoot = new CDvmCmpPropGridProperty(m_pDvmDevice->m_strName);
	pRoot->SetData((DWORD)pDvmDeviceMap);
	m_pDvmDevice->m_dwItemData = (DWORD)pRoot;
	POS pos = m_pDvmDevice->GetHeadPosition();
	CDvmLogicDevice *pLdDevice = NULL;

	while (pos != NULL)
	{
		pLdDevice = (CDvmLogicDevice *)pDvmDeviceMap->GetNext(pos);
		AddDvmLdevice(pLdDevice, pRoot);
	}

	AddProperty(pRoot);

	AdjustLayout();
	Invalidate(FALSE);
}

void CDvmCmpCatalogMapPropGridCtrl::AddDvmLdevice(CDvmLogicDevice  *pDvmLdevice, CDvmCmpPropGridProperty *pParent)
{
	CDvmCmpPropGridProperty* pLdProp = NULL;
	CDvmCmpPropGridProperty* pDsProp = NULL;

	pLdProp = new CDvmCmpPropGridProperty(pDvmLdevice->m_strName);
	pDvmLdevice->m_dwItemData = (DWORD)pLdProp;
	pLdProp->SetData((DWORD)pDvmLdevice);

	POS pos = pDvmLdevice->GetHeadPosition();
	CDvmDataset *pDataset = NULL;
	CDvmDatasetMap *pDsMap = NULL;

	while (pos != NULL)
	{
		pDataset = (CDvmDataset *)pDvmLdevice->GetNext(pos);
		pDsMap = (CDvmDatasetMap*)m_pDvmDeviceMap->FindDvmMapObj_ByMap(DMPCLASSID_CDVMDATASETMAP, pDataset);

		if (pDsMap == NULL)
		{
			pDsProp = new CDvmCmpPropGridProperty(pDataset->m_strName, _T(""), _T(""));
		}
		else
		{
			pDsProp = new CDvmCmpPropGridProperty(pDataset->m_strName, pDsMap->m_pStand->m_strID, _T(""));
		}

		pLdProp->AddSubItem(pDsProp);
		pDataset->m_dwItemData = (DWORD)pDsProp;
		pDsProp->SetData((DWORD)pDataset);
		pDsProp->AllowEdit(FALSE);
		InitDsProperty(pDsMap, pDataset);
	}

	pParent->AddSubItem(pLdProp);
}
// 
// void CDvmCmpCatalogMapPropGridCtrl::AddDvmLdevice(CDvmLDeviceMap  *pDvmLdevice, CDvmCmpPropGridProperty *pParent)
// {
// 	CDvmCmpPropGridProperty* pLdProp = NULL;
// 	CDvmCmpPropGridProperty* pDsProp = NULL;
// 
// 	pLdProp = new CDvmCmpPropGridProperty(pDvmLdevice->m_strName);
// 	pDvmLdevice->m_dwItemData = (DWORD)pLdProp;
// 	pLdProp->SetData((DWORD)pDvmLdevice);
// 
// 	POS pos = pDvmLdevice->GetHeadPosition();
// 	CDvmDatasetMap *pDatasetMap = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pDatasetMap = (CDvmDatasetMap *)pDvmLdevice->GetNext(pos);
// 
// 		if (pDatasetMap->m_pMap != NULL)
// 		{
// 			pDsProp = new CDvmCmpPropGridProperty(pDatasetMap->m_pStand->m_strName, pDatasetMap->m_pMap->m_strID, _T(""));
// 		}
// 		else
// 		{
// 			pDsProp = new CDvmCmpPropGridProperty(pDatasetMap->m_pStand->m_strName, _T(""), _T(""));
// 		}
// 
// 		pLdProp->AddSubItem(pDsProp);
// 		pDatasetMap->m_dwItemData = (DWORD)pDsProp;
// 		pDsProp->SetData((DWORD)pDatasetMap);
// 		pDsProp->AllowEdit(FALSE);
// 	}
// 
// 	pParent->AddSubItem(pLdProp);
// }

void CDvmCmpCatalogMapPropGridCtrl::OnChangeSelection(CMFCPropertyGridProperty* pNewSel, CMFCPropertyGridProperty* pOldSel)
{
	if (pNewSel == NULL)
	{
		return;
	}

	if (m_bIngnoreSetCurrSel)
	{
		return;
	}

	CExBaseObject *pSelObj = (CExBaseObject*)pNewSel->GetData();

	if (pSelObj == NULL)
	{
		return;
	}

	if (pSelObj->GetClassID() != DVMCLASSID_CDVMDATASET)
	{
		return;
	}

	if (m_pDvmCmpBasePropGridCtrlRef == NULL)
	{
		return;
	}

	CDvmCmpCatalogStandPropGridCtrl *pStandProp = (CDvmCmpCatalogStandPropGridCtrl*)m_pDvmCmpBasePropGridCtrlRef;
	CDvmDataset *pDataset = (CDvmDataset*)pSelObj;
	CDvmDeviceMap *pDvmDeviceMap = m_pDvmDeviceMap;
	CExBaseList oList;
	pDvmDeviceMap->FindDvmMapObj_ByMap(DMPCLASSID_CDVMDATASETMAP, pDataset, oList);

	if (oList.GetCount() == 0)
	{
		return;
	}

	CDvmDatasetMap *pDatasetMap = (CDvmDatasetMap*)oList.GetHead();
	CDvmCmpPropGridProperty *pProp = (CDvmCmpPropGridProperty*)pDatasetMap->m_dwItemData;
	oList.RemoveAll();

	if (pProp == NULL)
	{
		return;
	}

	m_pDvmCmpBasePropGridCtrlRef->m_bIngnoreSetCurrSel = TRUE;
	m_pDvmCmpBasePropGridCtrlRef->EnsurePropVisible(pProp, TRUE);
	m_pDvmCmpBasePropGridCtrlRef->SetCurSel(pProp);
	m_pDvmCmpBasePropGridCtrlRef->m_bIngnoreSetCurrSel = FALSE;

}

void CDvmCmpCatalogMapPropGridCtrl::OnLButtonDblClkMsg()
{

}


void CDvmCmpCatalogMapPropGridCtrl::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CExBaseObject *pSelObj = GetSelectData();

	if (pSelObj == NULL)
	{
		return;
	}
	
	if (pSelObj->GetClassID() != DVMCLASSID_CDVMDATASET)
	{
		return;
	}

	CDvmCmpCatalogStandPropGridCtrl *pStandProp = (CDvmCmpCatalogStandPropGridCtrl*)m_pDvmCmpBasePropGridCtrlRef;
	CDvmDataset *pDataset = (CDvmDataset*)pSelObj;
	CExBaseList oList;
	CMenu menu;		
	menu.CreatePopupMenu();

	m_pDvmDeviceMap->FindDvmMapObj_ByMap(DMPCLASSID_CDVMDATASETMAP, pDataset, oList);
	menu.AppendMenu(MF_STRING,ID_DVMMAP_CREATEDATAMAP_DEST,g_sLangTxt_CreatDataMap2/*_T("创建数据集映射")*/);
	
	if (oList.GetCount() > 0)
	{
		menu.AppendMenu(MF_STRING,ID_DVMMAP_DELETEDATAMAP_DEST,g_sLangTxt_DeleteDataMap2/*_T("删除数据集映射")*/);
	}

	CWnd *pOwer = pWnd->GetParent();
	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,pOwer);	
	oList.RemoveAll();
}

CDvmDatasetMap* CDvmCmpCatalogMapPropGridCtrl::GetCurrDatasetMap()
{
	CDvmDataset *pDataSet = (CDvmDataset*)GetSelectData(DVMCLASSID_CDVMDATASET);

	if (pDataSet == NULL)
	{
		return NULL;
	}

	CExBaseList oList;
	m_pDvmDeviceMap->FindDvmMapObj_ByMap(DMPCLASSID_CDVMDATASETMAP, pDataSet, oList);

	//Stand:删除全部的与此数据集相关的MAP
	if (oList.GetCount() == 0)
	{
		return NULL;
	}

	CDvmDatasetMap *pDatasetMap = (CDvmDatasetMap*)oList.GetHead();
	oList.RemoveAll();

	return pDatasetMap;
}

void CDvmCmpCatalogMapPropGridCtrl::DeleteMap()
{
	CDvmDataset *pDataSet = (CDvmDataset*)GetSelectData(DVMCLASSID_CDVMDATASET);

	if (pDataSet == NULL)
	{
		return;
	}

	CMFCPropertyGridProperty *pProp = (CMFCPropertyGridProperty*)pDataSet->m_dwItemData;
	CDvmDatasetMap *pDatasetMap = GetCurrDatasetMap();

	if (pDatasetMap == NULL)
	{
		return;
	}

	((CDvmCmpCatalogStandPropGridCtrl*)m_pDvmCmpBasePropGridCtrlRef)->DeleteMap(pDatasetMap);
	pProp->SetValue(_T(""));
}

void CDvmCmpCatalogMapPropGridCtrl::InitDsProperty(CDvmDatasetMap *pDatasetMap, CDvmDataset *pDvmDataset)
{
	CString strMapPath;
	CDvmCmpPropGridProperty *pProp = (CDvmCmpPropGridProperty*)pDvmDataset->m_dwItemData;

	if (pDatasetMap == NULL || pProp == NULL)
	{
		return;
	}

	if (pDatasetMap->m_pStand != NULL)
	{
		if (pDatasetMap->m_strLdvice != pDatasetMap->m_strLdviceMap)
		{
			strMapPath.Format(_T("%s$%s"), pDatasetMap->m_strLdvice, pDatasetMap->m_pStand->m_strID);
		}
		else
		{
			strMapPath = pDatasetMap->m_pStand->m_strID;
		}
	}

	pProp->SetValue(strMapPath);
}

CDvmDatasetMap* CDvmCmpCatalogMapPropGridCtrl::AddDatasetMap(CDvmDataset *pStandDataset)
{
	CDvmDataset *pDestDataset = (CDvmDataset *)GetSelectData(DVMCLASSID_CDVMDATASET);

	if (pDestDataset == NULL)
	{
		return NULL;
	}

	CDvmDatasetMap *pDatasetMap = ((CDvmCmpCatalogStandPropGridCtrl*)m_pDvmCmpBasePropGridCtrlRef)->AddDatasetMap(pStandDataset, pDestDataset);
	InitDsProperty(pDatasetMap, pDestDataset);

	return pDatasetMap;
}
