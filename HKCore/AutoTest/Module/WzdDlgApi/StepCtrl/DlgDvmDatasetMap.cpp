// DlgDvmDatasetMap.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgDvmDatasetMap.h"
#include "DvmMapSelDataDlg.h"
#include "../../../../Module/DataMngr/DvmCmp/DvmCmpCatalogPropGridCtrl.h"
#include "../StepDlg/WzdDlg_DvmMap.h"


// CDlgDvmDatasetMap 对话框

IMPLEMENT_DYNAMIC(CDlgDvmDatasetMap, CDialog)

CDlgDvmDatasetMap::CDlgDvmDatasetMap(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDvmDatasetMap::IDD, pParent)
{

}

CDlgDvmDatasetMap::~CDlgDvmDatasetMap()
{
	m_listDvmDsMapStand.RemoveAll();
}

void CDlgDvmDatasetMap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnOK);
}


BEGIN_MESSAGE_MAP(CDlgDvmDatasetMap, CDialog)
	ON_WM_SIZE()
	ON_MESSAGE(WM_DVMCMPGRIDSTAND_POPDEST, OnDvmCmpGridStandPopDest)
	ON_MESSAGE(WM_DVMCMPGRIDDEST_POPSTAND, OnDvmCmpGridDestPopStand)

	ON_COMMAND(ID_DVMMAP_CREATEDATAMAP_STAND, &CDlgDvmDatasetMap::OnCreateDataMap_Stand)
	ON_COMMAND(ID_DVMMAP_CREATEDATAMAP_DEST, &CDlgDvmDatasetMap::OnCreateDataMap_Dest)
	ON_COMMAND(ID_DVMMAP_DELETEDATAMAP_STAND, &CDlgDvmDatasetMap::OnDeleteDataMap_Stand)
	ON_COMMAND(ID_DVMMAP_DELETEDATAMAP_DEST, &CDlgDvmDatasetMap::OnDeleteDataMap_Dest)

	ON_COMMAND(ID_DVMMAP_MODIFYDATAMAP_STAND, &CDlgDvmDatasetMap::OnModifyDataMap_Stand)
	//ON_COMMAND(ID_DVMMAP_MODIFYDATAMAP_DEST, &CDlgDvmDatasetMap::OnModifyDataMap_Dest)
	ON_COMMAND(ID_DVMMAP_CONFIRMDATAMAP_STAND, &CDlgDvmDatasetMap::OnConfirmDataMap_Stand)
	//ON_COMMAND(ID_DVMMAP_CONFIRMDATAMAP_DEST, &CDlgDvmDatasetMap::OnConfirmDataMap_Dest)

	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CDlgDvmDatasetMap::OnBnClickedOk)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CDlgDvmDatasetMap 消息处理程序

BOOL CDlgDvmDatasetMap::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_gridStand.Create(WS_VISIBLE | WS_CHILD | WS_BORDER, CRect(0,0,0,0), this, ID_DVMCMP_GRID_STAND);
	m_gridStand.EnableHeaderCtrl(TRUE, _T("源数据（九统一标准模型）"), _T("目标数据（装置实际数据）"));
	m_gridStand.MarkModifiedProperties();
	m_gridStand.SetVSDotNetLook();
	m_gridStand.SetFont(g_pGlobalFont11);

	m_gridDest.Create(WS_VISIBLE | WS_CHILD | WS_BORDER, CRect(0,0,0,0), this, ID_DVMCMP_GRID_DEST);
	m_gridDest.EnableHeaderCtrl(TRUE, _T("目标数据（装置实际模型）"), _T("源数据（九统一标准模型）"));
	m_gridDest.MarkModifiedProperties();
	m_gridDest.SetVSDotNetLook();
	m_gridDest.SetFont(g_pGlobalFont11);

	m_gridStand.AttachDvmCmpBasePropGridCtrlRef(&m_gridDest);
	m_gridDest.AttachDvmCmpBasePropGridCtrlRef(&m_gridStand);

	COLORREF clrBackground, clrText, clrGroupBackground, clrGroupText, clrDescriptionBackground, clrDescriptionText, clrLine;
	m_gridStand.GetCustomColors(clrBackground, clrText, clrGroupBackground, clrGroupText, clrDescriptionBackground, clrDescriptionText, clrLine);
	m_gridStand.SetCustomColors(clrBackground, clrText, g_crLightBlue, clrGroupText, clrDescriptionBackground, clrDescriptionText, RGB(208, 231, 244));

	m_gridDest.GetCustomColors(clrBackground, clrText, clrGroupBackground, clrGroupText, clrDescriptionBackground, clrDescriptionText, clrLine);
	m_gridDest.SetCustomColors(clrBackground, clrText, g_crLightBlue, clrGroupText, clrDescriptionBackground, clrDescriptionText, RGB(208, 231, 244));

	CRect rcClient;
	GetClientRect(&rcClient);
	int cx = rcClient.Width();
	int cy = rcClient.Height();
	AdjustGrids(cx, cy);

	if (m_pDvmCmpObj != NULL)
	{
		m_gridStand.ShowDatasetMap(m_pDvmCmpObj);
		m_gridDest.ShowDatasetMap(m_pDvmCmpObj);
		g_DvmMapDlg->GetDvmCmpTool()->m_oDvmDeviceMap.FindDvmMapObj_ByStand(DMPCLASSID_CDVMDATASETMAP, m_pDvmCmpObj->m_pStand, m_listDvmDsMapStand);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CDlgDvmDatasetMap::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}

#define  DVMCMP_CNLN_AREA_WIDTH   4

void CDlgDvmDatasetMap::AdjustGrids(long cx, long cy)
{
	if (! ::IsWindow(m_gridStand.m_hWnd))
	{
		return;
	}

//  	CRect rcStand(5, 5, cx - 5, cy-38);
//  	CRect rcDest(rcStand.right + 5, 5, cx-5, cy-38);
//  
//  	m_gridStand.MoveWindow(rcStand);
 	//m_gridDest.MoveWindow(rcDest);

	CRect rc[2];
	rc[0] = CRect(0, 0, 200-DVMCMP_CNLN_AREA_WIDTH/2, 100);
	rc[1] = CRect(200+DVMCMP_CNLN_AREA_WIDTH/2, 0, 400, 100);

	if (cx > 400)
	{
		rc[0].right = (cx - DVMCMP_CNLN_AREA_WIDTH) / 2;
		rc[1].left = rc[0].right + DVMCMP_CNLN_AREA_WIDTH;
		rc[1].right = cx;
	}

	if (cy > 100)
	{
		rc[0].bottom = cy-38;
		rc[1].bottom = cy-38;
	}

	rc[0].DeflateRect(2,2,2,2);
	rc[1].DeflateRect(2,2,2,2);
	m_gridStand.MoveWindow(rc[0]);
	m_gridDest.MoveWindow(rc[1]);
}

void CDlgDvmDatasetMap::DeleteMap(CDvmMapObject *pMap)
{
	if (pMap == NULL)
	{
		return;
	}

// 	if (pMap->m_pMap != NULL)
// 	{
// 		m_gridDest.DeleteMap(pMap->m_pMap);
// 	}

	m_gridStand.DeleteMap(pMap);
}

void CDlgDvmDatasetMap::DeleteMap(CExBaseObject *pStand, CExBaseObject *pDest)
{
	CDvmMapObject *pDvmMap = dvmmap_GetMpObject(pStand);

	if (pDvmMap != NULL)
	{
		//m_gridDest.DeleteMap(pDvmMap->m_pMap);
		m_gridStand.DeleteMap(pDvmMap->m_pStand);
	}

	pDvmMap = dvmmap_GetMpObject(pDest);

	if (pDvmMap != NULL)
	{
		//m_gridDest.DeleteMap(pDvmMap->m_pMap);
		m_gridStand.DeleteMap(pDvmMap->m_pStand);
	}
}


void CDlgDvmDatasetMap::OnCreateDataMap_Stand()
{
	CDvmMap_SelDataDlg dlg;

	//CExBaseList *pListMap = m_gridDest.GetDvmDsMapStand();
	CExBaseList *pListMap = &m_listDvmDsMapStand;
	POS pos = pListMap->GetHeadPosition();
	CDvmDatasetMap *pDsMap = NULL;

	while (pos != NULL)
	{
		pDsMap = (CDvmDatasetMap *)pListMap->GetNext(pos);
		dlg.AddDataset((CDvmDataset*)pDsMap->m_pMap);
	}

	dlg.m_pSelMapObject = m_gridStand.GetSelMapObject();
	dlg.m_pDvmMapSrcObject = dlg.m_pSelMapObject->m_pStand;
	dlg.m_pSelDvmObject = NULL;
	//dlg.m_pSelDvmObject    = m_gridDest.GetSelDvmObject();

	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	ASSERT (dlg.m_pSelDvmObject != NULL);


	if (dlg.m_pSelDvmObject == NULL)
	{
		return;
	}


	long nStandIndex = 0;
	long nDestIndex = 0;
	long nStandGap = dlg.m_nGapStand;
	long nDestGap  = dlg.m_nGapDest;
	long nCount = dlg.m_nMatchCount;

	//如果是Data，则映射Data
	if (dlg.m_pSelDvmObject->GetClassID() == DVMCLASSID_CDVMDATA&&((CExBaseList *)dlg.m_pSelDvmObject)->GetHead() != NULL)
	{
		long Number;
		Number = dlg.m_cmbNumber.GetNumber();
		CDvmDataset *pStandDataset = (CDvmDataset*)dlg.m_pSelMapObject;
		CDvmDataset *pDestDataset = (CDvmDataset*)dlg.m_pSelDvmObject;

		CExBaseList * pStandDatasetParent = (CExBaseList *)pStandDataset->GetParent();		//20231027 luozibing 选为父节点时 批量映射
		CExBaseList * pDestDatasetParent = (CExBaseList *)pDestDataset->GetParent();
		long nIndex = pStandDatasetParent->FindIndexByID(pStandDataset->m_strID);
		long index = pDestDatasetParent->FindIndexByID(pDestDataset->m_strID);

		nStandIndex = 0;
		nDestIndex = 0;
		nCount += nIndex;

		for(nIndex; nIndex<nCount; nIndex++)
		{
			pStandDataset = (CDvmDataset *)pStandDatasetParent->GetAtIndex(nIndex);
			pDestDataset = (CDvmDataset *)pDestDatasetParent->GetAtIndex(index);
			if(pDestDataset == NULL ||pStandDataset == NULL)
			{
				break;
			}
			CDvmMapObject *StandpMap = dvmmap_GetMpObject(pStandDataset);//20231107 luozibing 存在映射时删除
			if (StandpMap->m_pMap != NULL)
			{
				dvmmap_SetDvmMapModifiedFlag(StandpMap);
				m_gridDest.DeleteMap(StandpMap->m_pMap);
				m_gridStand.DeleteMap(StandpMap->m_pStand);
				m_pDvmCmpObj->m_nCmpErrCount++;
			}
			m_pDvmCmpObj->m_nCmpErrCount--;
			SetDataMap(pStandDataset,pDestDataset,pStandDataset->GetCount(),nStandGap,nDestGap,nStandIndex,nDestIndex);
			index++;
		}
	}
	else
	{
		CExBaseList *pDestParent;
		CExBaseList *pStandParent = (CExBaseList*)dlg.m_pDvmMapSrcObject->GetParent();
		pDestParent = (CExBaseList*)dlg.m_pSelDvmObject->GetParent();
		if(((CExBaseList *)dlg.m_pSelDvmObject)->GetCount() == 0)		//20231103 luozibing 没有子节点
		{
			pDestParent = (CExBaseList*)dlg.m_pSelDvmObject;
			if(dlg.m_pDvmMapSrcObject->GetClassID() == DVMCLASSID_CDVMDATA && ((CExBaseList *)dlg.m_pDvmMapSrcObject)->GetHead() == NULL)
			{
				pStandParent = (CExBaseList*)dlg.m_pDvmMapSrcObject;
			}
		}

		nStandIndex = pStandParent->FindIndex(dlg.m_pDvmMapSrcObject);
		nDestIndex = pDestParent->FindIndex(dlg.m_pSelDvmObject);

		BOOL ExistData = FALSE;						//20231030 luozibing 当第一次向该组添加数据时 记录创建
		POS pos = pStandParent->GetHeadPosition();
		while(pos != NULL)
		{
			CDvmValue * tmp = (CDvmValue*)pStandParent->GetNext(pos);
			CDvmValueMap *tmpmap = (CDvmValueMap *)tmp->m_pDvmMapObj;
			if(tmpmap->m_strMapName != _T(""))
			{
				ExistData = TRUE;
			}
		}
		if(!ExistData)
		{	
			m_pDvmCmpObj->m_nCmpErrCount--;
		}
		SetDataMap(pStandParent,pDestParent,nCount,nStandGap,nDestGap,nStandIndex,nDestIndex);
	}
	//刷新视图更新显示映射比例
	UpdateDvmCmpPropGridProperty();
	m_gridStand.Invalidate(FALSE);
	m_gridDest.Invalidate(FALSE);

	CDvmMapObject *pDvmMapObj = m_gridStand.GetSelMapObject();
	dvmmap_SetDvmMapModifiedFlag(pDvmMapObj);
}

void CDlgDvmDatasetMap::OnCreateDataMap_Dest()
{
	CDvmMap_SelDataDlg dlg;

	CDvmDataset *pDvmDataset = m_gridStand.GetDvmDatasetStand();
	dlg.AddDataset(pDvmDataset);

	dlg.m_pSelMapObject = m_gridDest.GetSelMapObject();
	dlg.m_pDvmMapSrcObject = m_gridDest.GetSelectData();
	dlg.m_pSelDvmObject    = m_gridStand.GetSelDvmObject();

	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	ASSERT (dlg.m_pSelDvmObject != NULL);
	long nCount = dlg.m_nMatchCount;
	CDvmDataMap *pDvmDataMap = NULL;
	long nStandIndex = 0;
	long nDestIndex = 0;
	long nStandGap = dlg.m_nGapStand;
	long nDestGap  = dlg.m_nGapDest;

	//如果是Data，则映射Data
	if (dlg.m_pSelDvmObject->GetClassID() == DVMCLASSID_CDVMDATA)
	{
		CDvmData *pStandDataset = (CDvmData*)dlg.m_pSelDvmObject;
		CDvmDataset *pDestDataset = (CDvmDataset*)dlg.m_pDvmMapSrcObject;		

		nStandIndex = 0;
		nDestIndex = 0;

		CExBaseList * pStandDatasetParent = (CExBaseList *)pStandDataset->GetParent();		//20231027 luozibing 选为父节点时 批量映射
		CExBaseList * pDestDatasetParent = (CExBaseList *)pDestDataset->GetParent();
		long nIndex = pStandDatasetParent->FindIndexByID(pStandDataset->m_strID);
		long index = pDestDatasetParent->FindIndexByID(pDestDataset->m_strID);
		nCount += index;
		
		for(index; index<nCount; index++)
		{
			pDestDataset = (CDvmDataset *)pDestDatasetParent->GetAtIndex(index);
			pStandDataset = (CDvmData *)pStandDatasetParent->GetAtIndex(nIndex);
			if(pDestDataset == NULL ||pStandDataset == NULL)
			{
				break;
			}
			CDvmMapObject *DestpMap = dvmmap_GetMpObject(pDestDataset);//20231107 luozibing 存在映射时删除
			if(DestpMap != NULL)
			{
				if (DestpMap->m_pMap != NULL)
				{
					dvmmap_SetDvmMapModifiedFlag(DestpMap);
					m_gridDest.DeleteMap(DestpMap->m_pMap);
					m_gridStand.DeleteMap(DestpMap->m_pStand);
					m_pDvmCmpObj->m_nCmpErrCount++;
				}
			}
			SetDataMap(pStandDataset,pDestDataset,pDestDataset->GetCount(),nStandGap,nDestGap,nStandIndex,nDestIndex);
			++nIndex;
			m_pDvmCmpObj->m_nCmpErrCount--;
		}
	}
	else
	{
		CExBaseList *pStandParent = (CExBaseList*)dlg.m_pSelDvmObject->GetParent();
		CExBaseList *pDestParent = (CExBaseList*)dlg.m_pDvmMapSrcObject->GetParent();
		if(((CExBaseList *)dlg.m_pSelDvmObject)->GetCount() == 0)//20231103 luozibing 没有子节点
		{
			pDestParent = (CExBaseList*)dlg.m_pDvmMapSrcObject;
		}

		nStandIndex = pStandParent->FindIndex(dlg.m_pSelDvmObject);
		nDestIndex = pDestParent->FindIndex(dlg.m_pDvmMapSrcObject);

		BOOL ExistData = FALSE;						//20231030 luozibing 当第一次向该组添加数据时 记录创建
		POS pos = pStandParent->GetHeadPosition();
		while(pos != NULL)
		{
			CDvmValue * tmp = (CDvmValue*)pStandParent->GetNext(pos);
			CDvmValueMap *tmpmap = (CDvmValueMap *)tmp->m_pDvmMapObj;
			if(tmpmap->m_strMapName != _T(""))
			{
				ExistData = TRUE;
			}
		}
		if(!ExistData)
		{	
			m_pDvmCmpObj->m_nCmpErrCount--;
		}

		SetDataMap(pStandParent,pDestParent,nCount,nStandGap,nDestGap,nStandIndex,nDestIndex);
	}

	CDvmMapObject *pDvmMapObj = m_gridDest.GetSelMapObject();
	dvmmap_SetDvmMapModifiedFlag(pDvmMapObj);
	//刷新视图更新显示映射比例
	UpdateDvmCmpPropGridProperty();

	m_gridStand.Invalidate(FALSE);
	m_gridDest.Invalidate(FALSE);

}
void CDlgDvmDatasetMap::SetDataMap(CExBaseList *pStandParent,CExBaseList *pDestParent,long nCount,long nStandGap,long nDestGap,long nStandIndex,long nDestIndex)
{
	CDvmValue *pStand = NULL;
	CDvmValue *pDest  = NULL;
	CDvmDataMap *pParenMap = NULL;
	CDvmValueMap *pDvmMap = NULL;
	BOOL NoChild = FALSE;
	if(pDestParent->GetHead() == NULL && pStandParent->GetHead() != NULL)	//20231103 luozibing 判断当前Dest是否有子节点
	{
		NoChild = TRUE;
	}
	if(!NoChild)
	{
		//20231027 huangliang 对父级进行更新匹配
		pParenMap = (CDvmDataMap *)dvmmap_GetMpObject(pStandParent);
		//	DeleteMap(pStandParent, pDestParent);
		//	g_DvmMapDlg->GetDvmCmpTool()->UpdateDvmDataMap(pParenMap, (CDvmData*)pDestParent);

		((CDvmData *)pDestParent)->m_dwReserved = 1;				//20231027 luozibing 解决新建一个映射，其他为空的也显示映射
		((CDvmData *)pDestParent)->m_pDvmMapObj = pParenMap;
		pParenMap->SetMap0(pDestParent);
		pParenMap->StringCmp();

		m_gridDest.UpdateMap(pDestParent);
	}
	for (long nIndex=0; nIndex<nCount; nIndex++)
	{
		pStand = (CDvmValue*)pStandParent->GetAtIndex(nStandIndex+nIndex*nStandGap);
		pDest  = (CDvmValue*)pDestParent->GetAtIndex(nDestIndex+nIndex*nDestGap);
		if(NoChild)
		{
			CExBaseList *pDestPParent = (CExBaseList *)pDestParent->GetParent();
			long DestIndex = pDestPParent->FindIndex(pDestParent);
			pDest = (CDvmValue*)pDestPParent->GetAtIndex(DestIndex+nIndex);
			if (pDest == NULL || pStand == NULL)
			{
				break;
			}
			CDvmValueMap * pDestMap = (CDvmValueMap *)dvmmap_GetMpObject(pDest);
			if(pDestMap != NULL)
			{
				if(pDestMap->m_pStand != NULL)								//20231107 luozibing 如已经匹配则解除映射重新映射
				{
					dvmmap_SetDvmMapModifiedFlag(pDestMap);
					m_gridDest.DeleteMap(pDestMap);
					m_gridStand.DeleteMap(pDestMap->m_pStand);
				}
			}
			pDvmMap = (CDvmValueMap *)dvmmap_GetMpObject(pStand);
			if(pDvmMap->m_pMap != NULL)								//20231107 luozibing 如已经匹配则解除映射重新映射
			{
				dvmmap_SetDvmMapModifiedFlag(pDvmMap);
				m_gridDest.DeleteMap(pDvmMap->m_pMap);
				m_gridStand.DeleteMap(pDvmMap);
			}
			((CDvmData *)pDest)->m_dwReserved = 1;
			((CDvmData *)pDest)->m_pDvmMapObj = pDvmMap;
			pDvmMap->SetMap0(pDest);
			pStand->m_dwReserved = 1;
		}
		else
		{
			if (pDest == NULL || pStand == NULL)
			{
				break;
			}
			pDvmMap = (CDvmValueMap *)dvmmap_GetMpObject(pStand);
			DeleteMap(pStand, pDest);
			g_DvmMapDlg->GetDvmCmpTool()->UpdateDvmValueMap(pDvmMap, pDest);
		}

		m_gridStand.UpdateMap(pStand);
		m_gridDest.UpdateMap(pDest);
	}
}
void CDlgDvmDatasetMap::OnDeleteDataMap_Stand()
{
	CDvmMapObject *pMap = m_gridStand.GetSelMapObject();

	if (pMap == NULL)
	{
		return;
	}
	CDvmData * pDestParent= (CDvmData *)pMap->m_pMap->GetParent();
	dvmmap_SetDvmMapModifiedFlag(pMap);
	m_gridDest.DeleteMap(pMap->m_pMap);
	m_gridStand.DeleteMap(pMap);

	if(pMap->GetClassID() == DMPCLASSID_CDVMDATAMAP)		//20231030 luozibing 直接删除父节点时 记录删除	
	{
		m_pDvmCmpObj->m_nCmpErrCount++;
	}
	else													//当前删除节点为最后一个节点 删除父节点信息并记录删除
	{
		BOOL ExistData = FALSE;
		CDvmDataMap *pStandParent = (CDvmDataMap *)pMap->GetParent();
		POS pos = pStandParent->GetHeadPosition();
		while(pos != NULL)
		{
			CDvmValueMap * tmp = (CDvmValueMap*)pStandParent->GetNext(pos);
			if(tmp->m_pMap != NULL)
			{
				ExistData = TRUE;
			}
		}
		if(!ExistData)
		{
			m_gridDest.DeleteMap(pDestParent);
			m_gridStand.DeleteMap(pStandParent);
			m_pDvmCmpObj->m_nCmpErrCount++;
		}
	}

	//刷新视图更新显示映射比例
	UpdateDvmCmpPropGridProperty();

	m_gridDest.Invalidate(FALSE);
	m_gridStand.Invalidate(FALSE);

	// 	CDvmDatasetMap *pDataSetMap = (CDvmDatasetMap*)m_wndCatalogStand.GetSelectData(DMPCLASSID_CDVMDATASETMAP);
	// 
	// 	if (pDataSetMap == NULL)
	// 	{
	// 		return;
	// 	}
	// 
	// 	theApp.CloseDatasetCmpTemplate(pDataSetMap);
	// 	m_wndCatalogStand.DeleteMap();
}

void CDlgDvmDatasetMap::OnDeleteDataMap_Dest()
{
	CExBaseObject *pDvmObj = m_gridDest.GetSelDvmObject();
	if (pDvmObj == NULL)
	{
		return;
	}

	CDvmMapObject *pMap = dvmmap_GetMpObject(pDvmObj);
	if (pMap == NULL)
	{
		return;
	}

	dvmmap_SetDvmMapModifiedFlag(pMap);
	m_gridDest.DeleteMap(pDvmObj);
	m_gridStand.DeleteMap(pMap);
	
	if(pMap->GetClassID() == DMPCLASSID_CDVMDATAMAP)
	{
		m_pDvmCmpObj->m_nCmpErrCount++;
	}
	else
	{
		BOOL ExistData = FALSE;
		CDvmData *pDvmObjParent;
		if(((CDvmData *)pDvmObj)->GetHead() != NULL)//20231103 luozibing Dest组中存在映射则不计数，不存在映射则计数并删除父节点
		{
			 pDvmObjParent = (CDvmData *)pDvmObj->GetParent();
			POS pos = pDvmObjParent->GetHeadPosition();
			while(pos != NULL)
			{
				CDvmValue * tmp = (CDvmValue *)pDvmObjParent->GetNext(pos);
				if(tmp->m_pDvmMapObj != NULL)
					ExistData = TRUE;
			}
		}
		else
		{
			CDvmData *pStand = (CDvmData *)pMap->m_pStand->GetParent();
			POS  pos = pStand->GetHeadPosition();				//20231107 luozibing stand组中存在映射则不计数
			while(pos!=NULL)
			{
				CDvmValue  *pStandValue  =  (CDvmValue*)pStand->GetNext(pos);
				CDvmValueMap * pStandMap = (CDvmValueMap *)dvmmap_GetMpObject(pStandValue);
				if(pStandMap->m_pMap != NULL)
				{
					ExistData = TRUE;
				}
			}
		}
		if(!ExistData)
		{
			if(pDvmObj->GetClassID()==DVMCLASSID_CDVMVALUE)
			{
				m_gridDest.DeleteMap((CExBaseObject *)pDvmObj->GetParent());
				m_gridStand.DeleteMap((CDvmDataMap*)pMap->GetParent());
			}
			m_pDvmCmpObj->m_nCmpErrCount++;
		}
	}
	
	//刷新视图更新显示映射比例
	UpdateDvmCmpPropGridProperty();

	m_gridDest.Invalidate(FALSE);
	m_gridStand.Invalidate(FALSE);

	// 	CDvmDataset *pDataSet = (CDvmDataset*)m_wndCatalogMap.GetSelectData(DVMCLASSID_CDVMDATASET);
	// 
	// 	if (pDataSet == NULL)
	// 	{
	// 		return;
	// 	}
	// 
	// 	CDvmDatasetMap *pDatasetMap = m_wndCatalogMap.GetCurrDatasetMap();
	// 	theApp.CloseDatasetCmpTemplate(pDatasetMap);
	// 	m_wndCatalogMap.DeleteMap();
}

void CDlgDvmDatasetMap::OnModifyDataMap_Stand()
{
	OnCreateDataMap_Stand();
	OnConfirmDataMap_Stand();
}

// void CDlgDvmDatasetMap::OnModifyDataMap_Dest()
// {
// 	OnCreateDataMap_Dest();
// 	OnConfirmDataMap_Dest();
// }

void CDlgDvmDatasetMap::OnConfirmDataMap_Stand()
{
	CDvmMapObject *pMap = m_gridStand.GetSelMapObject();

	if (pMap == NULL)
	{
		return;
	}

	dvmmap_SetDvmMapModifiedFlag(pMap);
// 	m_gridDest.ConfirmMap(pMap->m_pMap);
// 	m_gridStand.ConfirmMap(pMap);
}

// void CDlgDvmDatasetMap::OnConfirmDataMap_Dest()
// {
// 	CExBaseObject *pDvmObj = m_gridDest.GetSelDvmObject();
// 
// 	if (pDvmObj == NULL)
// 	{
// 		return;
// 	}
// 
// 	CDvmMapObject *pMap = dvmmap_GetMpObject(pDvmObj);
// 
// 	if (pMap == NULL)
// 	{
// 		return;
// 	}
// 
// 	dvmmap_SetDvmMapModifiedFlag(pMap);
// // 	m_gridDest.ConfirmMap(pDvmObj);
// // 	m_gridStand.ConfirmMap(pMap);
// }

LRESULT CDlgDvmDatasetMap::OnDvmCmpGridStandPopDest(WPARAM wParam, LPARAM lParam)
{
	m_wParam = wParam;
	m_lParam = lParam;

	return 0;
}

LRESULT CDlgDvmDatasetMap::OnDvmCmpGridDestPopStand(WPARAM wParam, LPARAM lParam)
{
	m_wParam = wParam;
	m_lParam = lParam;

	return 0;
}
void CDlgDvmDatasetMap::OnClose()
{
	CDialog::OnClose();
}

void CDlgDvmDatasetMap::OnBnClickedOk()
{
	CString strMapFile;
	//pDvmDeviceMap = &theApp.GetDvmCmpTool()->m_oDvmDeviceMap;
	strMapFile = g_DvmMapDlg->GetDvmCmpTool()->SaveDvmCmpMapFile();
	OnOK();
}

void CDlgDvmDatasetMap::UpdateDvmCmpPropGridProperty()
{
	CDvmDatasetMap *pDatasetMap = (CDvmDatasetMap *)m_pDvmCmpObj;
	CDvmCmpPropGridProperty *pDsProp = (CDvmCmpPropGridProperty *)m_pDvmCmpObj->m_dwItemData;

	if (pDsProp != NULL)
	{
		pDsProp->SetNameEx(pDatasetMap);
	}

	CDvmLDeviceMap *pLDeviceMap = (CDvmLDeviceMap *)pDatasetMap->GetParent();
	POS pos = pLDeviceMap->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmDatasetMap *pSetMap = (CDvmDatasetMap *)pLDeviceMap->GetNext(pos);
		pDsProp = (CDvmCmpPropGridProperty *)pSetMap->m_dwItemData;

		if (pDsProp != NULL)
		{
			pDsProp->SetNameEx(pSetMap);
		}
	}
}
BOOL CDlgDvmDatasetMap::PreTranslateMessage(MSG* pMsg) 
{
	CScrollBar* tmp = m_gridStand.GetScrollBarCtrl(SB_VERT);		//20231020 luozibing 点击m_gridDest页面时隐藏m_gridStand滚动条
	//if(pMsg->message == 0x0246)
	{
		if(pMsg->hwnd == m_gridDest.m_hWnd)
		{
			tmp->ShowScrollBar(FALSE);
		}
		else if(pMsg->hwnd == m_gridStand.m_hWnd)
		{
			tmp->ShowScrollBar(TRUE);
		}
	}
	
    return CDialog::PreTranslateMessage(pMsg);
}
