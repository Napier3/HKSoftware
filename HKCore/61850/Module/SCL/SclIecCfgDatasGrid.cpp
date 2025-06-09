#include "StdAfx.h"
#include "SclIecCfgDatasGrid.h"

//#include "..\XLanguageResourceIec_61850Cfg.h"  //20161014
#include "../../Iec61850Config/XLanguageResourceIec_61850Cfg.h"  //20161014
#include "../XLanguageResourceIec.h"//20161014

//////////////////////////////////////////////////////////////////////////
//CSclIecCfgGridBase
CSclIecCfgGridBase::CSclIecCfgGridBase()
{
	m_nOldSclIecCfgClassID = 0;
	m_nAdjustBeginCol = 1;
}

CSclIecCfgGridBase::~CSclIecCfgGridBase()
{

}

void CSclIecCfgGridBase::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(1);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CSclIecCfgGridBase::ShowDatas(CExBaseList *pDatas)
{
	CExBaseListGrid::ShowDatas(pDatas);

	
}


//////////////////////////////////////////////////////////////////////////
// CSclIecCfgCtrlGrid

BOOL g_bSclIecCfgTitleInit = FALSE;

const int g_nSclIecCfgColsGIn = 17;
CString g_astrSclIecCfgTitleGIn[g_nSclIecCfgColsGIn];// = {_T("00序号"),_T("00选择"),_T("00AppID"),_T("MAC"), _T("00控制块所在IED"), _T("控制块所在AP"),_T("通道数"),_T("总通道数"), _T("控制块所在数据集描述"),
													//			_T("gocbRef"),_T("Dataset"),_T("goID"), _T("confRev"), _T("VLANID"), _T("VLANPRI"),
													//			_T("MinTime"), _T("MaxTime")};
const int g_iSclIecCfgWidthGin[g_nSclIecCfgColsGIn]={50,50,80, 80,80,80, 80, 80,80, 80,80,80, 80, 80, 80, 80, 80};

const int g_nSclIecCfgColsGOut = 15;
CString g_astrSclIecCfgTitleGOut[g_nSclIecCfgColsGOut] = {_T("序号"),_T("选择"),_T("AppID"),_T("MAC"),_T("控制块所在AP"),_T("通道数"), _T("数据集描述"),//中文部分 单独重新赋值   20161014
																_T("gocbRef"),_T("Dataset"),_T("goID"), _T("confRev"), _T("VLANID"), _T("VLANPRI"),//中文部分 单独重新赋值   20161014
																_T("MinTime"), _T("MaxTime")};//中文部分 单独重新赋值   20161014
const int g_iSclIecCfgWidthGOut[g_nSclIecCfgColsGOut]={50,50,80, 80,80,80, 80, 80,80, 80,80,80, 80, 80, 80};

const int g_nSclIecCfgColsSmvIn = 16;
CString g_astrSclIecCfgTitleSmvIn[g_nSclIecCfgColsSmvIn] = {_T("序号"),_T("选择"),_T("AppID"),_T("MAC"),_T("控制块所在IED"), _T("控制块所在AP"), _T("控制块所在数据集描述"),//中文部分 单独重新赋值   20161014
																_T("SmpRate"),_T("DataSet"), _T("引用通道数"), _T("总通道数"), _T("svID"),_T("NofASDU"),_T("confRev"),_T("VLanID"),_T("VLANPRI")};//中文部分 单独重新赋值   20161014
const int g_iSclIecCfgWidthSmvIn[g_nSclIecCfgColsSmvIn]={50,50,80, 80,80,80, 80, 80,80, 80,80,80, 80, 80, 80, 80};

const int g_nSclIecCfgColsSmvOut = 14;
CString g_astrSclIecCfgTitleSmvOut[g_nSclIecCfgColsSmvOut] = {_T("序号"),_T("选择"),_T("AppID"),_T("MAC"),_T("控制块所在AP"), _T("数据集描述"), _T("SmpRate"),_T("DataSet"),//中文部分 单独重新赋值   20161014
																_T("通道数"),_T("svID"),_T("NofASDU"),_T("confRev"),_T("VLanID"),_T("VLANPRI")};//中文部分 单独重新赋值   20161014
const int g_iSclIecCfgWidthSmvOut[g_nSclIecCfgColsSmvOut]={50,50,80, 80,80,80, 80, 80, 80,80,80, 80, 80, 80};

const int g_nSclIecCfgColsEmpty = 1;
const CString g_astrSclIecCfgTitleEmpty[g_nSclIecCfgColsEmpty] = {_T("序号")};
const int g_iSclIecCfgWidthEmpty[g_nSclIecCfgColsEmpty]={60};

void scliec_InitSclIecCfgTitle()
{
	if (g_bSclIecCfgTitleInit)
	{
		return;
	}

	g_bSclIecCfgTitleInit = TRUE;
	long nIndex = 0;
	g_astrSclIecCfgTitleGIn[nIndex++] = g_sLtxt_SICDGSerial;//_T("序号")
	g_astrSclIecCfgTitleGIn[nIndex++] = g_sLtxt_SICDSelect;//_T("选择")
	g_astrSclIecCfgTitleGIn[nIndex++] = _T("AppID");
	g_astrSclIecCfgTitleGIn[nIndex++] = _T("MAC");
	g_astrSclIecCfgTitleGIn[nIndex++] = g_sLtxt_SICDIED;//_T("控制块所在IED")
	g_astrSclIecCfgTitleGIn[nIndex++] = g_sLtxt_SICDAP;//_T("控制块所在AP")
	g_astrSclIecCfgTitleGIn[nIndex++] = g_sLtxt_SICDChaNO;//_T("通道数")
	g_astrSclIecCfgTitleGIn[nIndex++] = g_sLtxt_SICDTotCha;//_T("总通道数")
	g_astrSclIecCfgTitleGIn[nIndex++] = g_sLtxt_SICDDataSet;//_T("控制块所在数据集描述")
	g_astrSclIecCfgTitleGIn[nIndex++] = _T("gocbRef");
	g_astrSclIecCfgTitleGIn[nIndex++] = _T("Dataset");
	g_astrSclIecCfgTitleGIn[nIndex++] = _T("goID");
	g_astrSclIecCfgTitleGIn[nIndex++] = _T("confRev");
	g_astrSclIecCfgTitleGIn[nIndex++] = _T("VLANID");
	g_astrSclIecCfgTitleGIn[nIndex++] = _T("VLANPRI");
	g_astrSclIecCfgTitleGIn[nIndex++] = _T("MinTime");
	g_astrSclIecCfgTitleGIn[nIndex++] = _T("MaxTime");
	
	//g_astrSclIecCfgTitleGIn[nIndex++] = g_sLtxt_Select;//,_T("选择"),_T("AppID"),_T("MAC"), _T("控制块所在IED"), _T("控制块所在AP"),_T("通道数"),_T("总通道数"), _T("控制块所在数据集描述"),
	//	_T("gocbRef"),_T("Dataset"),_T("goID"), _T("confRev"), _T("VLANID"), _T("VLANPRI"),
	//	_T("MinTime"), _T("MaxTime")};

}



// IMPLEMENT_DYNCREATE(CSclIecCfgCtrlGrid, CGridCtrl)

CSclIecCfgCtrlGrid::CSclIecCfgCtrlGrid()
{
	m_pMsgRcvWnd = NULL;
	m_nAdjustBeginCol = 2;
}

CSclIecCfgCtrlGrid::~CSclIecCfgCtrlGrid()
{
}

// 
// BEGIN_MESSAGE_MAP(CSclIecCfgCtrlGrid, CGridCtrl)
// END_MESSAGE_MAP()

void CSclIecCfgCtrlGrid::InitGridTitle()
{
	scliec_InitSclIecCfgTitle();//   20161013
	g_astrSclIecCfgTitleGOut[0]=g_astrSclIecCfgTitleGIn[0];  //   20161014
	g_astrSclIecCfgTitleGOut[1]=g_astrSclIecCfgTitleGIn[1];  //   20161014
	g_astrSclIecCfgTitleGOut[4]=g_astrSclIecCfgTitleGIn[5];   //   20161014
	g_astrSclIecCfgTitleGOut[5]=g_astrSclIecCfgTitleGIn[6];    //   20161014
	g_astrSclIecCfgTitleGOut[6]=g_sLtxt_SICDDataSetDes;   //   20161014

	g_astrSclIecCfgTitleSmvIn[0]=g_astrSclIecCfgTitleGIn[0];  //   20161014
	g_astrSclIecCfgTitleSmvIn[1]=g_astrSclIecCfgTitleGIn[1];  //   20161014
	g_astrSclIecCfgTitleSmvIn[4]=g_astrSclIecCfgTitleGIn[4];  //   20161014
	g_astrSclIecCfgTitleSmvIn[5]=g_astrSclIecCfgTitleGIn[5];  //   20161014
	g_astrSclIecCfgTitleSmvIn[6]=g_astrSclIecCfgTitleGIn[8];  //   20161014
	g_astrSclIecCfgTitleSmvIn[9]=g_sLtxt_SICDRefChaNO; //   20161014
	g_astrSclIecCfgTitleSmvIn[10]=g_astrSclIecCfgTitleGIn[7];  //   20161014

	g_astrSclIecCfgTitleSmvOut[0]=g_astrSclIecCfgTitleGIn[0];  //   20161014
	g_astrSclIecCfgTitleSmvOut[1]=g_astrSclIecCfgTitleGIn[1];  //   20161014
	g_astrSclIecCfgTitleSmvOut[4]=g_astrSclIecCfgTitleGIn[5];  //   20161014
	g_astrSclIecCfgTitleSmvOut[5]=g_astrSclIecCfgTitleGOut[6];  //   20161014
	g_astrSclIecCfgTitleSmvOut[8]=g_astrSclIecCfgTitleGIn[6];  //   20161014



	if (m_pDatas == NULL)
	{
		SetColumnCount(1);
		SetRowCount(1);
		return;
	}

	if (m_nOldSclIecCfgClassID == m_pDatas->GetClassID())
	{
		return;
	}

	m_nOldSclIecCfgClassID = m_pDatas->GetClassID();
	long nCols = 1;
	const CString *pstrTitle = NULL;
	const int *pnWidth = NULL;

	switch (m_nOldSclIecCfgClassID)
	{
	case SCLIECCLASSID_CTRLS_SMV_OUT:
		nCols = g_nSclIecCfgColsSmvOut;
		pstrTitle = g_astrSclIecCfgTitleSmvOut;
		pnWidth = g_iSclIecCfgWidthSmvOut;
		break;

	case SCLIECCLASSID_CTRLS_SMV_IN:
		nCols = g_nSclIecCfgColsSmvIn;
		pstrTitle = g_astrSclIecCfgTitleSmvIn;
		pnWidth = g_iSclIecCfgWidthSmvIn;
		break;

	case SCLIECCLASSID_CTRLS_GS_OUT:
		nCols = g_nSclIecCfgColsGOut;
		pstrTitle = g_astrSclIecCfgTitleGOut;
		pnWidth = g_iSclIecCfgWidthGOut;
		break;

	case SCLIECCLASSID_CTRLS_GS_IN:
		nCols = g_nSclIecCfgColsGIn;
		pstrTitle = g_astrSclIecCfgTitleGIn;
		pnWidth = g_iSclIecCfgWidthGin;
		break;

	default:
		nCols = g_nSclIecCfgColsEmpty;
		pstrTitle = g_astrSclIecCfgTitleEmpty;
		pnWidth = g_iSclIecCfgWidthEmpty;
		break;
	}

	SetColumnCount(nCols);

	CExBaseListGrid::InitGridTitle(pstrTitle, pnWidth, nCols);
}

void CSclIecCfgCtrlGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
	//CExBaseListGrid::ShowData(pData, nRow, bInsertRow);

	switch (nClassID)
	{
	case SCLIECCLASSID_CTRL_SMV_OUT:
		ShowData_SMVOutput((CSclCtrlSmvOut*)pData, nRow);
		break;

	case SCLIECCLASSID_CTRL_SMV_IN:
		ShowData_SMVInput((CSclCtrlSmvIn*)pData, nRow);
		break;

	case SCLIECCLASSID_CTRL_GS_OUT:
		ShowData_GooseOutput((CSclCtrlGsOut*)pData, nRow);
		break;

	case SCLIECCLASSID_CTRL_GS_IN:
		ShowData_GooseInput((CSclCtrlGsIn*)pData, nRow);
		break;

	}

	nRow++;
}

void CSclIecCfgCtrlGrid::UpdateCheck()
{
	POS pos = m_pDatas->GetHeadPosition();
	CSclCtrlBase *pSclCtrl = NULL;
	GV_ITEM Item;
	long nRow = 1;

	while (pos != NULL)
	{
		pSclCtrl = (CSclCtrlBase *)m_pDatas->GetNext(pos);
		InitDataCellItem(Item, pSclCtrl, nRow, 1, RGB(0, 0, 0));
		Item.mask = GVIF_VALUE;
		Item.szText.Format(_T("%d"), pSclCtrl->m_nSelect);
		Item.dwValue = pSclCtrl->m_nSelect;
		SetItem(&Item);
		nRow++;
	}

	Invalidate(FALSE);
}

void CSclIecCfgCtrlGrid::ShowData_GooseInput(CSclCtrlGsIn *pGsIn,int nRow)
{
	//_T("序号")
	Show_Index(pGsIn, nRow, 0);
	
	//_T("选择")
	Show_Check(pGsIn, nRow, 1, &pGsIn->m_nSelect,EndEditCell_CheckChanged);

	//_T("AppID")
	Show_Hex(pGsIn, nRow, 2, &pGsIn->m_dwAppID, 2, FALSE);

	//_T("MAC")
	Show_StaticString(pGsIn, nRow, 3, &pGsIn->m_strMac);

	// _T("控制块所在IED")
	Show_StaticString(pGsIn, nRow, 4, &pGsIn->m_strIedDesc);

	// _T("控制块所在AP")
	Show_StaticString(pGsIn, nRow, 5, &pGsIn->apName);

	//_T("通道数")
	Show_Long(pGsIn, nRow, 6, &pGsIn->m_nChnCount, FALSE);

	//_T("通道数")
	Show_Long(pGsIn, nRow, 7, &pGsIn->m_nChnRefCount, FALSE);

	// _T("控制块所在数据集描述")
	Show_StaticString(pGsIn, nRow, 8, &pGsIn->m_strDataSetDesc);

	//_T("gocbRef")
	Show_StaticString(pGsIn, nRow, 9, &pGsIn->gocbref);

	//_T("Dataset")
	Show_StaticString(pGsIn, nRow, 10, &pGsIn->m_strDataSet);

	//_T("goID")
	Show_StaticString(pGsIn, nRow, 11, &pGsIn->m_strGooseId);
	
	// _T("confRev")
	Show_Long(pGsIn, nRow, 12, &pGsIn->m_dwVersion, FALSE);

	// _T("VLANID")
	Show_DWORD(pGsIn, nRow, 13, &pGsIn->m_dwVLandID, FALSE);

	// _T("VLANPRI")
	Show_Long(pGsIn, nRow, 14, &pGsIn->m_dwVLandPriority, FALSE);

	//_T("MinTime")
	Show_Long(pGsIn, nRow, 15, &pGsIn->scl_gse_MinTime, FALSE);

	// _T("MaxTime")
	Show_Long(pGsIn, nRow, 16, &pGsIn->scl_gse_MaxTime, FALSE);
}

void CSclIecCfgCtrlGrid::ShowData_GooseOutput(CSclCtrlGsOut *pGsOut,int nRow)
{
	//_T("序号")
	Show_Index(pGsOut, nRow, 0);

	//_T("选择")
	Show_Check(pGsOut, nRow, 1, &pGsOut->m_nSelect,EndEditCell_CheckChanged);

	//_T("AppID")
	Show_Hex(pGsOut, nRow, 2, &pGsOut->m_dwAppID, 2, FALSE);

	//_T("MAC")
	Show_StaticString(pGsOut, nRow, 3, &pGsOut->m_strMac);

	// _T("控制块所在AP")
	Show_StaticString(pGsOut, nRow, 4, &pGsOut->apName);

	//_T("通道数")
	Show_Long(pGsOut, nRow,5, &pGsOut->m_nChnCount, FALSE);

	// _T("数据集描述")
	Show_StaticString(pGsOut, nRow,6, &pGsOut->m_strDataSetDesc);

	//_T("gocbRef")
	Show_StaticString(pGsOut, nRow, 7, &pGsOut->gocbref);

	//_T("Dataset")
	Show_StaticString(pGsOut, nRow, 8, &pGsOut->m_strDataSet);

	//_T("goID")
	Show_StaticString(pGsOut, nRow, 9, &pGsOut->m_strGooseId);

	// _T("confRev")
	Show_Long(pGsOut, nRow, 10, &pGsOut->m_dwVersion, FALSE);

	// _T("VLANID")
	Show_DWORD(pGsOut, nRow, 11, &pGsOut->m_dwVLandID, FALSE);

	// _T("VLANPRI")
	Show_Long(pGsOut, nRow, 12, &pGsOut->m_dwVLandPriority, FALSE);

	//_T("MinTime")
	Show_Long(pGsOut, nRow, 13, &pGsOut->scl_gse_MinTime, FALSE);

	// _T("MaxTime")
	Show_Long(pGsOut, nRow, 14, &pGsOut->scl_gse_MaxTime, FALSE);
}

void CSclIecCfgCtrlGrid::ShowData_SMVInput(CSclCtrlSmvIn *pSmvIn,int nRow)
{
	//_T("序号")
	Show_Index(pSmvIn, nRow, 0);

	//_T("选择")
	Show_Check(pSmvIn, nRow, 1, &pSmvIn->m_nSelect,EndEditCell_CheckChanged);

	//_T("AppID")
	Show_Hex(pSmvIn, nRow, 2, &pSmvIn->m_dwAppID, 2, FALSE);

	//_T("MAC")
	Show_StaticString(pSmvIn, nRow, 3, &pSmvIn->m_strMac);

	//_T("控制块所在IED")
	Show_StaticString(pSmvIn, nRow, 4, &pSmvIn->iedStr);

	// _T("控制块所在AP")
	Show_StaticString(pSmvIn, nRow, 5, &pSmvIn->apName);

	// _T("控制块所在数据集描述")
	Show_StaticString(pSmvIn, nRow, 6, &pSmvIn->m_strDataSetDesc);

	//_T("SmpRate")
	Show_Long(pSmvIn, nRow, 7, &pSmvIn->scl_svcb_smpRate);

	//_T("DataSet")
	Show_StaticString(pSmvIn, nRow, 8, &pSmvIn->m_strDataSet);

	// _T("条目数")
	Show_Long(pSmvIn, nRow, 9, &pSmvIn->m_nChnCount, FALSE);

	// _T("条目数")
	Show_Long(pSmvIn, nRow, 10, &pSmvIn->m_nChnRefCount, FALSE);

	//_T("svID")
	Show_StaticString(pSmvIn, nRow, 11, &pSmvIn->m_strSVID);

	//_T("NofASDU")
	Show_Long(pSmvIn, nRow, 12, &pSmvIn->scl_svcb_nofASDU, FALSE);

	//_T("confRev")
	Show_Long(pSmvIn, nRow, 13, &pSmvIn->scl_svcb_confRev, FALSE);

	//_T("VLanID")
	Show_DWORD(pSmvIn, nRow, 14, &pSmvIn->scl_smv_VLANID, FALSE);

	//_T("VLANPRI")
	Show_DWORD(pSmvIn, nRow, 15, &pSmvIn->scl_smv_VLANPRI, FALSE);

}

void CSclIecCfgCtrlGrid::ShowData_SMVOutput(CSclCtrlSmvOut *pSmvOut,int nRow)
{
	//_T("序号")
	Show_Index(pSmvOut, nRow, 0);

	//_T("选择")
	Show_Check(pSmvOut, nRow, 1, &pSmvOut->m_nSelect,EndEditCell_CheckChanged);

	//_T("AppID")
	Show_Hex(pSmvOut, nRow, 2, &pSmvOut->m_dwAppID, 2, FALSE);

	//_T("MAC")
	Show_StaticString(pSmvOut, nRow, 3, &pSmvOut->m_strMac);

	//_T("控制块所在AP")
	Show_StaticString(pSmvOut, nRow, 4, &pSmvOut->apName);

	// _T("数据集描述")
	Show_StaticString(pSmvOut, nRow, 5, &pSmvOut->m_strDataSetDesc);

	// _T("SmpRate")
	Show_Long(pSmvOut, nRow, 6, &pSmvOut->scl_svcb_smpRate);

	//_T("DataSet")
	Show_StaticString(pSmvOut, nRow, 7, &pSmvOut->m_strDataSet);

	//_T("条目数")
	Show_Long(pSmvOut, nRow, 8, &pSmvOut->m_nChnCount, FALSE);

	//_T("svID")
	Show_StaticString(pSmvOut, nRow, 9, &pSmvOut->m_strSVID);

	//_T("confRev")
	Show_Long(pSmvOut, nRow, 10, &pSmvOut->scl_svcb_nofASDU, FALSE);

	//_T("NofASDU")
	Show_Long(pSmvOut, nRow, 11, &pSmvOut->scl_svcb_confRev, FALSE);

	//_T("VLanID")
	Show_DWORD(pSmvOut, nRow, 12, &pSmvOut->scl_smv_VLANID, FALSE);

	//_T("VLANPRI")
	Show_DWORD(pSmvOut, nRow, 13, &pSmvOut->scl_smv_VLANPRI, FALSE);
}

void CSclIecCfgCtrlGrid::EndEditCell_CheckChanged(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
 {
	 PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	 ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	 CSclIecCfgCtrlGrid *pOwnGrid = (CSclIecCfgCtrlGrid*)pGrid;
	 *(pVCellData->pnValue) = pCell->dwValue;

 	 if ((pOwnGrid->m_pMsgRcvWnd != NULL)&&(pVCellData->pObj != NULL))
 	 {
		 CSclCtrlBase *pSclCtrlBase = (CSclCtrlBase*)pVCellData->pObj;

		 if (pSclCtrlBase->m_nSelect)
		 {
			 if (pSclCtrlBase->GetClassID() == SCLIECCLASSID_CTRL_GS_OUT)
			 {
				 pSclCtrlBase->m_dwItemData = 0;//用于测试仪Goose订阅
			 }
			 else  if (pSclCtrlBase->GetClassID() == SCLIECCLASSID_CTRL_GS_IN)
			 {
				 pSclCtrlBase->m_dwItemData = 1;//用于测试仪Goose发布
			 }
		 }

 		 pOwnGrid->m_pMsgRcvWnd->PostMessage(WM_SCLIECCFGCTRL_SELECTED, (WPARAM)pVCellData->pObj, (LPARAM)NULL);
 	 }
 }

// 
// void CSclIecCfgCtrlGrid::InitGrid(int nimportfiletype,const CLIENTIEDPTR& showiedPtr)
// {
// 	m_nRowCurSel = 0;
// 	DWORD Ptraddr = 0;
// 	switch (nimportfiletype)
// 	{
// 	case 2:
// 		ShowGooseInput(showiedPtr->list_gooseinput);
// 		break;
// 	case 0:
// 		ShowGooseOutput(showiedPtr->list_gooseoutput);
// 		break;
// 	case 3:
// 		ShowSMVInput(showiedPtr->list_smvinput);
// 		break;
// 	case 1:
// 		ShowSMVOutput(showiedPtr->list_smvoutput);
// 		break;
// 	default:
// 		DeleteAllItems();
// 		break;
// 	}
// 
// 	AutoSize(FALSE, TRUE);
// 
// 	if (GetRowCount() > 1)
// 	{
// 		m_nRowCurSel = 1;
// 		Ptraddr = GetItemData(m_nRowCurSel, 0);
// 		m_nType = nimportfiletype;
// 
// 		SelectRow(m_nRowCurSel);
// 		::SendMessage(GetParent()->GetSafeHwnd(),WM_USERUPDATECHN,Ptraddr,nimportfiletype);
// 	}
// 	else
// 	{
// 		m_nRowCurSel = 0;
// 	}
// }
// 
// void CSclIecCfgCtrlGrid::ShowGooseInput(CScdDataList& listGooseIn)
// {
// 	PGOOSEIN giptitr=NULL,giptitrT=NULL;
// 
// 	// 检查各个逻辑设备间是否有相同的控制块输出
// 	if (listGooseIn.GetCount() > 1)//size() > 1)
// 	{
// 		//giptitrB = listGooseIn.begin();
// 		//giptitrE = listGooseIn.end();
// 		long nIndex=0;
// 
// 		while(TRUE)//for (giptitr = giptitrB; giptitr != giptitrE; giptitr++)
// 		{
// 			giptitr = (PGOOSEIN)listGooseIn.GetAtIndex(nIndex);
// 			if (giptitr == NULL)
// 			{
// 				break;
// 			}
// 
// 			//giptitrT = giptitr;
// 			//advance(giptitrT,1);
// 			long nIndex2 = nIndex+1;
// 			while (TRUE)//for (;giptitrT != giptitrE;)
// 			{
// 				giptitrT = (PGOOSEIN)listGooseIn.GetAtIndex(nIndex2);
// 
// 				if (giptitrT == NULL)
// 				{
// 					break;
// 				}
// 
// 				// 相同则删除此ldevice内的goosein,添加到giptitrT
// 				if (giptitrT->strAppID == giptitr->strAppID && 
// 					giptitrT->strMac == giptitr->strMac &&
// 					giptitrT->nChnCount == giptitr->nChnCount &&
// 					giptitrT->strgocbRef == giptitr->strgocbRef &&
// 					giptitrT->strDataSet == giptitr->strDataSet && 
// 					giptitrT->strgoID == giptitr->strgoID)
// 				{
// 					//giptitr->list_gseinputchn.insert(giptitr->list_gseinputchn.end(),
// 					//	giptitrT->list_gseinputchn.begin(),giptitrT->list_gseinputchn.end());
// 					giptitr->Append(*giptitrT);
// 
// 					listGooseIn.DeleteAtIndex(nIndex2);//giptitrT = listGooseIn.erase(giptitrT);
// 				}
// 				else
// 				{
// 					nIndex2++;
// 				}
// 			}
// 
// 		}
// 
// 	}
// 
// 
// 	// 统计个数
// 	int nSize = listGooseIn.GetCount();//.size();
// 
// 
// 	// 创建列表
// 	CreateGrid(nSize+1,g_nSclIecCfgColsGIn,1);
// 	SetGridHead(g_astrSclIecCfgTitleGIn,g_nSclIecCfgColsGIn);
// 
// 	// 设置数据
// 	int nCount = 1;
// 	//giptitrB = listGooseIn.begin();
// 	//giptitrE = listGooseIn.end();
// 
// 	TPOS pos = listGooseIn.GetHeadPosition();
// 
// 	// 在此范围内查找,判断MAC,gocbRef,DataSet,goID
// 	while (pos != NULL)//for (giptitr = giptitrB; giptitr != giptitrE; giptitr++)
// 	{
// 		giptitr = (PGOOSEIN)listGooseIn.GetNext(pos);
// 		giptitr->bSelect = FALSE;
// 
// 		// 检测是否有选中项（以APPID为键值）
// 		ShowData_GooseInput(giptitr,nCount++);
// 	}
// }
// 
// 
// void CSclIecCfgCtrlGrid::ShowGooseOutput(CScdDataList& listGooseOut)
// {
// 	PGOOSEOUT goptitr=NULL,goptitrB=NULL,goptitrE=NULL;
// 	int nSize = listGooseOut.GetCount();//.size();
// 	//goptitr = listGooseOut.begin();
// 	//goptitrE = listGooseOut.end();
// 
// 	// 创建列表
// 	CreateGrid(nSize+1,g_nSclIecCfgColsGOut,1);
// 	SetGridHead(g_astrSclIecCfgTitleGOut,g_nSclIecCfgColsGOut);
// 
// 	nSize = 1;
// 	TPOS pos = listGooseOut.GetHeadPosition();
// 
// 	while (pos != NULL)//for (;goptitr != goptitrE; goptitr++)
// 	{
// 		goptitr = (PGOOSEOUT)listGooseOut.GetNext(pos);
// 		goptitr->bSelect = FALSE;
// 		ShowData_GooseOutput(goptitr,nSize++);
// 	}
// }
// 
// void CSclIecCfgCtrlGrid::ShowSMVInput(CScdDataList& listSMVIn)
// {
// 	PSMVIN smviptitr=NULL,smviptitrT=NULL;
// 
// 	CString str;
// 	// 检查各个逻辑设备间是否有相同的控制块输出
// 	if (listSMVIn.GetCount() > 1)//size() > 1)
// 	{
// 		//smviptitrB = listSMVIn.begin();
// 		//smviptitrE = listSMVIn.begin();
// 		long nIndex = 0;
// 
// 
// 		while (TRUE)//for (smviptitr = smviptitrB; smviptitr != smviptitrE; smviptitr++)
// 		{
// 			smviptitr = (PSMVIN)listSMVIn.GetAtIndex(nIndex);
// 
// 			if (smviptitr == NULL)
// 			{
// 				break;
// 			}
// 
// 			//smviptitrT = smviptitr;
// 			//advance(smviptitrT,1);
// 			long nIndex2 = nIndex + 1;
// 			while (TRUE)//for (; smviptitrT != smviptitrE;)
// 			{
// 				smviptitrT = (PSMVIN)listSMVIn.GetAtIndex(nIndex2);
// 
// 				if (smviptitrT == NULL)
// 				{
// 					break;
// 				}
// 
// 				// 相同则删除此ldevice内的goosein,添加到giptitrT
// 				if (smviptitrT->strAppID == smviptitr->strAppID && 
// 					smviptitrT->strMac == smviptitr->strMac &&
// 					smviptitrT->nChnCount == smviptitr->nChnCount &&
// 					smviptitrT->strsmvID == smviptitr->strsmvID)
// 				{
// 
// 					//smviptitr->list_smvinputchn.insert(smviptitr->list_smvinputchn.end(),
// 					//	smviptitrT->list_smvinputchn.begin(),smviptitrT->list_smvinputchn.end());
// 					smviptitr->Append(*smviptitrT);
// 
// 					listSMVIn.DeleteAtIndex(nIndex2);//smviptitrT = listSMVIn.erase(smviptitrT);
// 				}else
// 				{
// 					nIndex2++;//smviptitrT++;
// 				}
// 			}
// 
// 		}
// 	}
// 
// 
// 	int nSize = listSMVIn.GetCount();//.size();
// 
// 
// 	// 创建列表
// 	CreateGrid(nSize+1,g_nSclIecCfgColsSmvIn,1);
// 	SetGridHead(g_astrSclIecCfgTitleSmvIn,g_nSclIecCfgColsSmvIn);
// 
// 	// 设置数据
// 	int nCount = 1;
// 
// 	//smviptitrB = listSMVIn.begin();
// 	//smviptitrE = listSMVIn.end();
// 	TPOS pos = listSMVIn.GetHeadPosition();
// 
// 	while (pos != NULL)//for (smviptitr = smviptitrB; smviptitr != smviptitrE; smviptitr++)
// 	{
// 		smviptitr = (PSMVIN)listSMVIn.GetNext(pos);
// 		smviptitr->bSelect = FALSE;
// 		ShowData_SMVInput(smviptitr,nCount++);
// 	}
// 
// }
// 
// void CSclIecCfgCtrlGrid::ShowSMVOutput(CScdDataList& listSMVOut)
// {
// 	PSMVOUT smvoptitr=NULL,smvoptitrB=NULL,smvoptitrE=NULL;
// 	int nSize = listSMVOut.GetCount();//size();
// 
// 	// 创建列表
// 	int nCount = 1;
// 	CreateGrid(nSize+1,g_nSclIecCfgColsSmvOut,1);
// 	SetGridHead(g_astrSclIecCfgTitleSmvOut,g_nSclIecCfgColsSmvOut);
// 
// 	// 设置数据
// 	//smvoptitrB = listSMVOut.begin();
// 	//smvoptitrE = listSMVOut.end();
// 	TPOS pos = listSMVOut.GetHeadPosition();
// 
// 	while (pos != NULL)//for (smvoptitr = smvoptitrB; smvoptitr != smvoptitrE; smvoptitr++)
// 	{
// 		smvoptitr = (PSMVOUT)listSMVOut.GetNext(pos);
// 		smvoptitr->bSelect = FALSE;
// 		ShowData_SMVOutput(smvoptitr,nCount);
// 		nCount++;
// 	}
// }

// 
// void CSclIecCfgCtrlGrid::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
// {
// 	// TODO: Add your message handler code here and/or call default
// 
// 	CGridCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
// 
// 
// 	if ((nChar == VK_DOWN || nChar == VK_UP) && m_nRowCurSel != m_idCurrentCell.row)
// 	{
// 
// 		m_nRowCurSel = m_idCurrentCell.row;
// 		DWORD Ptraddr = GetItemData(m_nRowCurSel, 0);
// 		::SendMessage(GetParent()->GetSafeHwnd(),WM_USERUPDATECHN,Ptraddr,m_nType);
// 
// 	}
// }
// 
// void CSclIecCfgCtrlGrid::OnLButtonUp(UINT nFlags, CPoint point)
// {
// 	if (st_IsInLoadScdXmlFile())
// 	{
// 		return;
// 	}
// 
// 	int nType = -1;
// 	BOOL bOldCheck;
// 	CGridCell* pCell = GetCell(m_LeftClickDownCell.row, m_LeftClickDownCell.col);
// 	if (pCell)
// 	{
// 		if (pCell->nDataType == GVET_CHECKBOX)
// 		{
// 			nType = 1;
// 			bOldCheck = pCell->dwValue;
// 		}
// 	}
// 
// 	CGridCtrl::OnLButtonUp(nFlags,point);
// 
// 	if (pCell && m_nRowCurSel > 0)
// 	{
// 		BOOL bUpdataChn = FALSE;
// 		if (m_nRowCurSel != m_LeftClickDownCell.row )
// 		{
// 			bUpdataChn = TRUE;
// 		}
// 
// 		if (bUpdataChn == TRUE || nType == 1)
// 		{
// 			m_nRowCurSel = m_LeftClickDownCell.row;
// 			if (m_nRowCurSel > 0)
// 			{
// 
// 				// 更新通道数据
// 				DWORD dwPtrAddr = pCell->lParam;
// 				if (nType == 1)
// 				{
// 					BOOL bCheck = pCell->dwValue;
// 
// 					if (bCheck != bOldCheck)
// 					{
// 						SetIEDCtrlCheck(bCheck,dwPtrAddr);
// 					}
// 				}
// 
// 				if (bUpdataChn == TRUE)
// 				{
// 					::SendMessage(GetParent()->GetSafeHwnd(),WM_USERUPDATECHN,dwPtrAddr,m_nType);
// 				}
// 			}	
// 		}
// 	}
// }
// 
// 
// void CSclIecCfgCtrlGrid::SetIEDCtrlCheck(BOOL bCheck,DWORD dwPtrAddr)
// {
// 
// 	switch (m_nType)
// 	{
// 	case 2:
// 		{
// 			GOOSEINPtr gseinputptr = (GOOSEINPtr)dwPtrAddr;
// 			(gseinputptr)->bSelect = bCheck;
// 		}
// 		break;
// 	case 0:
// 		{
// 			GOOSEOUTPtr gseoutputPtr = (GOOSEOUTPtr)dwPtrAddr;
// 			(gseoutputPtr)->bSelect = bCheck;
// 
// 		}
// 		break;
// 	case 3:
// 		{
// 			SMVINPtr smvinputPtr= (SMVINPtr)dwPtrAddr;
// 			(smvinputPtr)->bSelect = bCheck;
// 		}
// 		break;
// 	case  1:
// 		{
// 			SMVOUTPtr smvoutputPtr = (SMVOUTPtr)dwPtrAddr;
// 			(smvoutputPtr)->bSelect = bCheck;
// 		}
// 		break;
// 	}
// 
// 
// }


//////////////////////////////////////////////////////////////////////////
// CCSclIecCfgCtrlChnGrid

const int g_nSclIecCfgColsGOutChn = 6;
CString g_astrSclIecCfgTitleGOutChn[g_nSclIecCfgColsGOutChn];// = {
//	g_sLtxt_SICDGSerial,g_sLtxt_LNDescrip,g_sLtxt_DOIDescrip,g_sLtxt_DAIDescrip,
//	CXLanguageResourceIecBase::g_sLtxt_Type,g_sLtxt_Address//
//	_T("序号"),_T("LN描述"),_T("DOI描述"),_T("DAI描述"),_T("类型"),_T("地址")
//};
const int g_iSclIecCfgWidthGOutChn[g_nSclIecCfgColsGOutChn]={50,50, 80,80,80,80};

const int g_nSclIecCfgColsGInChn = 13;
CString g_astrSclIecCfgTitleGInChn[g_nSclIecCfgColsGInChn];// = {
//	g_sLtxt_SICDGSerial,g_sLtxt_Map,g_sLtxt_Type,g_sLtxt_InterLNDes,CXLanguageResourceIecBase::g_sLtxt_ExterLNDes,
//	CXLanguageResourceIecBase::g_sLtxt_InterDODes,CXLanguageResourceIecBase::g_sLtxt_ExterDODes,CXLanguageResourceIecBase::g_sLtxt_InterDUDes,CXLanguageResourceIecBase::g_sLtxt_ExterDUDes,CXLanguageResourceIecBase::g_sLtxt_InterNO,
//	CXLanguageResourceIecBase::g_sLtxt_ExterNO,CXLanguageResourceIecBase::g_sLtxt_InterPath,CXLanguageResourceIecBase::g_sLtxt_ExterPath//
//	_T("序号"),_T("映射"), _T("类型"), _T("内部LN描述"),_T("外部LN描述"), _T("内部DO描述"),
//	_T("外部DO描述"), _T("内部DU描述"), _T("外部DU描述"), _T("内部序号"),_T("外部序号"),_T("内部路径"),  _T("外部路径")
//};
const int g_iSclIecCfgWidthGinChn[g_nSclIecCfgColsGInChn]={50,50, 80,80,80,80, 80,80,80,80, 80,80,80};

const int g_nSclIecCfgColsSmvOutChn = 5;
CString g_astrSclIecCfgTitleSmvOutChn[g_nSclIecCfgColsSmvOutChn] = {
//	CXLanguageResourceIecBase::g_sLtxt_SICDGSerial,CXLanguageResourceIecBase::g_sLtxt_LNDescrip,CXLanguageResourceIecBase::g_sLtxt_DOIDescrip,CXLanguageResourceIecBase::g_sLtxt_DUDes,
//	CXLanguageResourceIecBase::g_sLtxt_Address//
	_T("序号"),_T("LN描述"),_T("DOI描述"),_T("DU描述"), _T("地址")
};
const int g_iSclIecCfgWidthSmvOutChn[g_nSclIecCfgColsSmvOutChn]={60, 60, 80, 80, 80};

const int g_nSclIecCfgColsSmvInChn = 11;
CString g_astrSclIecCfgTitleSmvInChn[g_nSclIecCfgColsSmvInChn] = {
//	CXLanguageResourceIecBase::g_sLtxt_SICDGSerial,CXLanguageResourceIecBase::g_sLtxt_InterLNDes,CXLanguageResourceIecBase::g_sLtxt_ExterLNDes,CXLanguageResourceIecBase::g_sLtxt_InterDODes,
//	CXLanguageResourceIecBase::g_sLtxt_ExterDODes,CXLanguageResourceIecBase::g_sLtxt_InterDUDes,g_sLtxt_ExterDUDes,g_sLtxt_InterNO,g_sLtxt_ExterNO,
//	g_sLtxt_InterPath,g_sLtxt_ExterPath//
	_T("序号"),_T("内部LN描述"),_T("外部LN描述"), _T("内部DO描述"),
	_T("外部DO描述"), _T("内部DU描述"), _T("外部DU描述"), _T("内部序号"),_T("外部序号"),_T("内部路径"),  _T("外部路径")
};
const int g_iSclIecCfgWidthSmvInChn[g_nSclIecCfgColsSmvInChn]={50,50, 80,80,80,80,50, 80,80,80,80};



CCSclIecCfgCtrlChnGrid::CCSclIecCfgCtrlChnGrid()
{
	m_nOldSclIecCfgClassID = 0;
}

CCSclIecCfgCtrlChnGrid::~CCSclIecCfgCtrlChnGrid()
{
}

void CCSclIecCfgCtrlChnGrid::InitGridTitle()
{
	g_astrSclIecCfgTitleGOutChn[0]=g_sLtxt_SICDGSerial;//20161015
	g_astrSclIecCfgTitleGOutChn[1]=g_sLtxt_LNDescrip;//20161015
	g_astrSclIecCfgTitleGOutChn[2]=g_sLtxt_DOIDescrip;//20161015
	g_astrSclIecCfgTitleGOutChn[3]=g_sLtxt_DAIDescrip;//20161015
	g_astrSclIecCfgTitleGOutChn[4]=g_sLangID_Type;//20161015
	g_astrSclIecCfgTitleGOutChn[5]=g_sLtxt_Address;//20161015
	g_astrSclIecCfgTitleGInChn[0]=g_sLtxt_SICDGSerial;//20161015
	g_astrSclIecCfgTitleGInChn[1]=g_sLtxt_Map;//20161015
	g_astrSclIecCfgTitleGInChn[2]=g_sLangID_Type;//20161015
	g_astrSclIecCfgTitleGInChn[3]=g_sLtxt_InterLNDes;//20161015
	g_astrSclIecCfgTitleGInChn[4]=g_sLtxt_ExterLNDes;//20161015
	g_astrSclIecCfgTitleGInChn[5]=g_sLtxt_InterDODes;//20161015
	g_astrSclIecCfgTitleGInChn[6]=g_sLtxt_ExterDODes;//20161015
	g_astrSclIecCfgTitleGInChn[7]=g_sLtxt_InterDUDes;//20161015
	g_astrSclIecCfgTitleGInChn[8]=g_sLtxt_ExterDUDes;//20161015
	g_astrSclIecCfgTitleGInChn[9]=g_sLtxt_InterNO;//20161015
	g_astrSclIecCfgTitleGInChn[10]=g_sLtxt_ExterNO;//20161015
	g_astrSclIecCfgTitleGInChn[11]=g_sLtxt_InterPath;//20161015
	g_astrSclIecCfgTitleGInChn[12]=g_sLtxt_ExterPath;//20161015
	if (m_pDatas == NULL)
	{
		SetColumnCount(1);
		SetRowCount(1);
		return;
	}

	if (m_nOldSclIecCfgClassID == m_pDatas->GetClassID())
	{
		return;
	}

	m_nOldSclIecCfgClassID = m_pDatas->GetClassID();
	long nCols = 1;
	const CString *pstrTitle = NULL;
	const int *pnWidth = NULL;

	switch (m_nOldSclIecCfgClassID)
	{
	case SCLIECCLASSID_CTRL_SMV_OUT:
		nCols = g_nSclIecCfgColsSmvOutChn;
		pstrTitle = g_astrSclIecCfgTitleSmvOutChn;
		pnWidth = g_iSclIecCfgWidthSmvOutChn;
		break;

	case SCLIECCLASSID_CTRL_SMV_IN:
		nCols = g_nSclIecCfgColsSmvInChn;
		pstrTitle = g_astrSclIecCfgTitleSmvInChn;
		pnWidth = g_iSclIecCfgWidthSmvInChn;
		break;

	case SCLIECCLASSID_CTRL_GS_OUT:
		nCols = g_nSclIecCfgColsGOutChn;
		pstrTitle = g_astrSclIecCfgTitleGOutChn;
		pnWidth = g_iSclIecCfgWidthGOutChn;
		break;

	case SCLIECCLASSID_CTRL_GS_IN:
		nCols = g_nSclIecCfgColsGInChn;
		pstrTitle = g_astrSclIecCfgTitleGInChn;
		pnWidth = g_iSclIecCfgWidthGinChn;
		break;

	default:
		nCols = g_nSclIecCfgColsEmpty;
		pstrTitle = g_astrSclIecCfgTitleEmpty;
		pnWidth = g_iSclIecCfgWidthEmpty;
		break;
	}

	SetColumnCount(nCols);

	CExBaseListGrid::InitGridTitle(pstrTitle, pnWidth, nCols);
}

void CCSclIecCfgCtrlChnGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	switch (nClassID)
	{
	case SCLIECCLASSID_CH_SMV_OUT:
		ShowData_SMVOutputChn((CSclChSmvOut*)pData, nRow);
		break;

	case SCLIECCLASSID_CH_SMV_IN:
		ShowData_SMVInputChn((CSclChSmvIn*)pData, nRow);
		break;

	case SCLIECCLASSID_CH_GS_OUT:
		ShowData_GooseOutputChn((CSclChGsOut*)pData, nRow);
		break;

	case SCLIECCLASSID_CH_GS_IN:
		ShowData_GooseInputChn((CSclChGsIn*)pData, nRow);
		break;

	}

	nRow++;
}



void CCSclIecCfgCtrlChnGrid::ShowData_GooseInputChn(CSclChGsIn *pChn,int nRow)
{
	//_T("序号")
	Show_Index(pChn, nRow, 0);

	//_T("映射")
	Show_StaticString(pChn, nRow, 1, &pChn->fcda_map);

	// _T("类型")
	Show_StaticString(pChn, nRow, 2, &pChn->fcda_type);

	// _T("内部LN描述")
	Show_StaticString(pChn, nRow, 3, &pChn->inLNDesc);

	//_T("外部LN描述")
	Show_StaticString(pChn, nRow, 4, &pChn->fcda_lndesc);

	// _T("内部DO描述")
	Show_StaticString(pChn, nRow, 5, &pChn->inDODesc);

	//_T("外部DO描述")
	Show_StaticString(pChn, nRow, 6, &pChn->fcda_dodesc);
	
	// _T("内部DU描述")
	Show_StaticString(pChn, nRow, 7, &pChn->inDADesc);
	
	// _T("外部DU描述")
	Show_StaticString(pChn, nRow, 8, &pChn->fcda_desc);
	
	// _T("内部序号")
	Show_Long(pChn, nRow, 9, &pChn->inIndex, FALSE);
	
	//_T("外部序号")
	Show_Long(pChn, nRow, 10, &pChn->outIndex, FALSE);

	//_T("内部路径")
	Show_StaticString(pChn, nRow, 11, &pChn->inPath);

	// _T("外部路径")
	Show_StaticString(pChn, nRow, 12, &pChn->fcda_name);
}

void CCSclIecCfgCtrlChnGrid::ShowData_GooseOutputChn(CSclChGsOut *pChn,int nRow)
{
	// 序号
	Show_Index(pChn, nRow, 0);

	// LN描述
	Show_StaticString(pChn, nRow, 1, &pChn->fcda_lndesc);

	// DOI描述
	Show_StaticString(pChn, nRow, 2, &pChn->fcda_dodesc);

	// DAI描述
	Show_StaticString(pChn, nRow, 3, &pChn->fcda_desc);

	// 类型
	Show_StaticString(pChn, nRow, 4, &pChn->fcda_type);

	// 地址
	Show_StaticString(pChn, nRow, 5, &pChn->fcda_name);
}

void CCSclIecCfgCtrlChnGrid::ShowData_SMVInputChn(CSclChSmvIn *pChn,int nRow)
{
	//_T("序号")
	Show_Index(pChn, nRow, 0);

	// _T("内部LN描述")
	Show_StaticString(pChn, nRow, 1, &pChn->inLNDesc);

	//_T("外部LN描述")
	Show_StaticString(pChn, nRow, 2, &pChn->fcda_lndesc);

	// _T("内部DO描述")
	Show_StaticString(pChn, nRow, 3, &pChn->inDODesc);

	//_T("外部DO描述")
	Show_StaticString(pChn, nRow, 4, &pChn->fcda_dodesc);

	// _T("内部DU描述")
	Show_StaticString(pChn, nRow, 5, &pChn->inDADesc);

	// _T("外部DU描述")
	Show_StaticString(pChn, nRow, 6, &pChn->fcda_desc);

	// _T("内部序号")
	Show_Long(pChn, nRow, 7, &pChn->inIndex, FALSE);

	//_T("外部序号")
	Show_Long(pChn, nRow, 8, &pChn->outIndex, FALSE);

	//_T("内部路径")
	Show_StaticString(pChn, nRow, 9, &pChn->inPath);

	// _T("外部路径")
	Show_StaticString(pChn, nRow, 10, &pChn->fcda_name);
}

void CCSclIecCfgCtrlChnGrid::ShowData_SMVOutputChn(CSclChSmvOut *pChn,int nRow)
{
	// 序号
	Show_Index(pChn, nRow, 0);

	// LN描述
	Show_StaticString(pChn, nRow, 1, &pChn->fcda_lndesc);

	// DOI描述
	Show_StaticString(pChn, nRow, 2, &pChn->fcda_dodesc);

	// DU描述
	Show_StaticString(pChn, nRow, 3, &pChn->fcda_desc);

	// 地址
	Show_StaticString(pChn, nRow, 4, &pChn->fcda_name);
}
