#include "StdAfx.h"
#include "SclVisualDatasGrid.h"

//#include "..\XLanguageResourceIec_61850Cfg.h"  //20161014
#include "..\..\61850/Iec61850Config/XLanguageResourceIec_61850Cfg.h"  //20161014
#include "..\..\61850\Module\XLanguageResourceIec.h"//20161014

#include "..\..\SclFileTest\SclVisualCtrlChsView.h"

//////////////////////////////////////////////////////////////////////////
//CSclVisualGridBase
CSclVisualGridBase::CSclVisualGridBase()
{
	m_nOldSclIecCfgClassID = 0;
	m_nAdjustBeginCol = 1;
}

CSclVisualGridBase::~CSclVisualGridBase()
{

}

void CSclVisualGridBase::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(1);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CSclVisualGridBase::ShowDatas(CExBaseList *pDatas)
{
	CExBaseListGrid::ShowDatas(pDatas);	
}

long CSclVisualGridBase::GetDatasCount()
{
	ASSERT (m_pDatas != NULL);

	if (m_pDatas == NULL)
	{
		return 0;
	}
	else if (m_pDatas->GetClassID() == DVMCLASSID_CDVMDEVICE)
	{
		CExBaseList *pLogicDevice = NULL;
		long nCount = 0;
		POS pos = ((CExBaseList*)m_pDatas)->GetHeadPosition();

		while (pos != NULL)
		{
			pLogicDevice = (CExBaseList*)((CExBaseList*)m_pDatas)->GetNext(pos);
			nCount += pLogicDevice->GetCount();
		}

		return nCount;
	}
	else if (m_pDatas->GetClassID() == DVMCLASSID_CDVMLOGICDEVICE)
	{
		CExBaseList *pDvmDevice = (CExBaseList*)m_pDatas->GetParent();
		CExBaseList *pLogicDevice = NULL;
		POS pos = pDvmDevice->GetHeadPosition();
		long nCount = 0;

		while ((pos != NULL)&&(nCount == 0))
		{
			pLogicDevice = (CExBaseList *)pDvmDevice->GetNext(pos);
			CExBaseList *pDataSet = (CExBaseList*)(((CExBaseList*)pLogicDevice)->GetHead());

			if (pDataSet != NULL)
			{
				nCount = pDataSet->GetCount();
			}
		}

		return nCount;
	}
	else if (m_pDatas->GetClassID() == SCLIECCLASSID_CTRL_SMV_OUT)
	{
		CSclVisualCtrlChnGrid *pSclVisualCtrlChnGrid = (CSclVisualCtrlChnGrid*)this;
		if (pSclVisualCtrlChnGrid->m_nCtrlType == 22)
		{
			CSclCtrlSmvOut *pSclCtrlSmvOut = (CSclCtrlSmvOut*)m_pDatas;
			CSclChSmvOut *pSclChSmvOut = NULL;
			POS posCh = pSclCtrlSmvOut->GetHeadPosition();
			long nCount = 0;

			while(posCh != NULL)
			{
				pSclChSmvOut = (CSclChSmvOut *)pSclCtrlSmvOut->GetNext(posCh);
				nCount += pSclChSmvOut->m_oChInRefs.GetCount();
			}

			return nCount;
		} 
		else
		{
			return m_pDatas->GetCount();
		}
	}
	else if (m_pDatas->GetClassID() == SCLIECCLASSID_CTRL_GS_OUT)
	{
		CSclVisualCtrlChnGrid *pSclVisualCtrlChnGrid = (CSclVisualCtrlChnGrid*)this;
		if (pSclVisualCtrlChnGrid->m_nCtrlType == 22)
		{
			CSclCtrlGsOut *pSclCtrlGsOut = (CSclCtrlGsOut*)m_pDatas;
			CSclChGsOut *pSclChGsOut = NULL;
			POS posCh = pSclCtrlGsOut->GetHeadPosition();
			long nCount = 0;

			while(posCh != NULL)
			{
				pSclChGsOut = (CSclChGsOut *)pSclCtrlGsOut->GetNext(posCh);
				nCount += pSclChGsOut->m_oChInRefs.GetCount();
			}

			return nCount;
		} 
		else
		{
			return m_pDatas->GetCount();
		}
	}
	else
	{
		return m_pDatas->GetCount();
	}
}

//////////////////////////////////////////////////////////////////////////
// CSclVisualCtrlGrid

BOOL g_bSclIecCfgTitleInit = FALSE;

const int g_nSclIecCfgColsGIn = 16;
CString g_astrSclIecCfgTitleGIn[g_nSclIecCfgColsGIn] = {_T("序号"),_T("AppID"),_T("MAC"), _T("控制块所在IED"), _T("控制块所在AP"),_T("通道数"),_T("总通道数"), _T("控制块所在数据集描述"),
																_T("gocbRef"),_T("Dataset"),_T("goID"), _T("confRev"), _T("VLANID"), _T("VLANPRI"),
																_T("MinTime"), _T("MaxTime")};
const int g_iSclIecCfgWidthGin[g_nSclIecCfgColsGIn]={50,80, 80,80,80, 80, 80,80, 80,80,80, 80, 80, 80, 80, 80};

const int g_nSclIecCfgColsGOut = 14;
CString g_astrSclIecCfgTitleGOut[g_nSclIecCfgColsGOut] = {_T("序号"),_T("AppID"),_T("MAC"),_T("控制块所在AP"),_T("通道数"), _T("数据集描述"),//中文部分 单独重新赋值   20161014
																_T("gocbRef"),_T("Dataset"),_T("goID"), _T("confRev"), _T("VLANID"), _T("VLANPRI"),//中文部分 单独重新赋值   20161014
																_T("MinTime"), _T("MaxTime")};//中文部分 单独重新赋值   20161014
const int g_iSclIecCfgWidthGOut[g_nSclIecCfgColsGOut]={50,80, 80,80,80, 80, 80,80, 80,80,80, 80, 80, 80};

const int g_nSclIecCfgColsSmvIn = 15;
CString g_astrSclIecCfgTitleSmvIn[g_nSclIecCfgColsSmvIn] = {_T("序号"),_T("AppID"),_T("MAC"),_T("控制块所在IED"), _T("控制块所在AP"), _T("控制块所在数据集描述"),//中文部分 单独重新赋值   20161014
																_T("SmpRate"),_T("DataSet"), _T("引用通道数"), _T("总通道数"), _T("svID"),_T("NofASDU"),_T("confRev"),_T("VLanID"),_T("VLANPRI")};//中文部分 单独重新赋值   20161014
const int g_iSclIecCfgWidthSmvIn[g_nSclIecCfgColsSmvIn]={50,80, 80,80,80, 80, 80,80, 80,80,80, 80, 80, 80, 80};

const int g_nSclIecCfgColsSmvOut = 13;
CString g_astrSclIecCfgTitleSmvOut[g_nSclIecCfgColsSmvOut] = {_T("序号"),_T("AppID"),_T("MAC"),_T("控制块所在AP"), _T("数据集描述"), _T("SmpRate"),_T("DataSet"),//中文部分 单独重新赋值   20161014
																_T("通道数"),_T("svID"),_T("NofASDU"),_T("confRev"),_T("VLanID"),_T("VLANPRI")};//中文部分 单独重新赋值   20161014
const int g_iSclIecCfgWidthSmvOut[g_nSclIecCfgColsSmvOut]={50,80, 80,80,80, 80, 80, 80,80,80, 80, 80, 80};


const int g_nSclIecCfgColsRptCtrl = 12;
CString g_astrSclIecCfgTitleRptCtrl[g_nSclIecCfgColsRptCtrl] = {_T("序号"),_T("名称"),_T("所在LD名"),_T("rptID值"),_T("关联数据集"),_T("配置版本号"),_T("完整性周期"),_T("缓存"),_T("缓存时间"),_T("最大实例化数"),_T("TrgOps值"),_T("OptFields值")};
const int g_iSclIecCfgWidthRptCtrl[g_nSclIecCfgColsRptCtrl]={50,120, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80 };

const int g_nSclIecCfgColsLogCtrl = 10;
CString g_astrSclIecCfgTitleLogCtrl[g_nSclIecCfgColsLogCtrl] = { _T("序号"), _T("名称"), _T("描述"), _T("所在LD名"), _T("关联数据集"), _T("完整性周期"), _T("logName"), _T("日志远方使能"), _T("ReasonCode") ,_T("TrgOps值") };
const int g_iSclIecCfgWidthLogCtrl[g_nSclIecCfgColsLogCtrl]={50,120, 80, 80, 80, 80, 80, 80, 80, 80 };

const int g_nSclIecCfgColsDataSet = 6;
CString g_astrSclIecCfgTitleDataSet[g_nSclIecCfgColsDataSet] = {_T("序号"),_T("LD名称"),_T("LD描述"),_T("DataSet名称"),_T("DataSet描述"),_T("通道数")};//新增20170524
const int g_iSclIecCfgWidthDataSet[g_nSclIecCfgColsDataSet]={50,150, 150, 150, 150,50};

const int g_nSclIecCfgColsEmpty = 1;
const CString g_astrSclIecCfgTitleEmpty[g_nSclIecCfgColsEmpty] = {_T("序号")};
const int g_iSclIecCfgWidthEmpty[g_nSclIecCfgColsEmpty]={60};



// IMPLEMENT_DYNCREATE(CSclVisualCtrlGrid, CGridCtrl)

CSclVisualCtrlGrid::CSclVisualCtrlGrid()
{
	m_nAdjustBeginCol = 2;

	m_nCtrlType  = 0;
	m_pFirstDvmDataset = NULL;
	m_pDataViewOptrInterface2 = NULL;
}

CSclVisualCtrlGrid::~CSclVisualCtrlGrid()
{
}

// 
// BEGIN_MESSAGE_MAP(CSclVisualCtrlGrid, CGridCtrl)
// END_MESSAGE_MAP()


void CSclVisualCtrlGrid::OnDataSelChanged(int nRow, int nCol)
{
	if (m_pDataViewOptrInterface != NULL)
	{
		m_pDataViewOptrInterface->OnDataSelChanged(this, nRow, nCol);
	}

	if (m_pDataViewOptrInterface2 != NULL)
	{
		((CSclVisualCtrlChsView*)m_pDataViewOptrInterface2)->m_nCtrlType = 22;//标记为第二组列表的切换
		((CSclVisualCtrlChsView*)m_pDataViewOptrInterface2)->m_oCSclIecCfgCtrlChnGrid.DeleteNonFixedRows();
		m_pDataViewOptrInterface2->OnDataSelChanged(this, nRow, nCol);
	}
}


void CSclVisualCtrlGrid::InitGridTitle()
{

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

	case DVMCLASSID_CDVMDEVICE:

		if ( m_nCtrlType == 6 )
		{
			nCols = g_nSclIecCfgColsRptCtrl;
			pstrTitle = g_astrSclIecCfgTitleRptCtrl;
			pnWidth = g_iSclIecCfgWidthRptCtrl;
			break;
		} 
		else if ( m_nCtrlType == 7 )
		{
			nCols = g_nSclIecCfgColsLogCtrl;
			pstrTitle = g_astrSclIecCfgTitleLogCtrl;
			pnWidth = g_iSclIecCfgWidthLogCtrl;
			break;
		} 
		else if ( m_nCtrlType == 8 )
		{
			nCols = g_nSclIecCfgColsDataSet;
			pstrTitle = g_astrSclIecCfgTitleDataSet;
			pnWidth = g_iSclIecCfgWidthDataSet;
			break;
		}

	default:
		nCols = g_nSclIecCfgColsEmpty;
		pstrTitle = g_astrSclIecCfgTitleEmpty;
		pnWidth = g_iSclIecCfgWidthEmpty;
		break;
	}

	SetColumnCount(nCols);

	CExBaseListGrid::InitGridTitle(pstrTitle, pnWidth, nCols);
}

void CSclVisualCtrlGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
	//CExBaseListGrid::ShowData(pData, nRow, bInsertRow);

	CDvmDataset *pDvmDataset = NULL;
	CRptCtrl *pRptCtrl = NULL;
	CLogCtrl *pLogCtrl = NULL;

	CExBaseObject *pExBaseObject = NULL;
	POS pos = NULL ,posDetail = NULL;
	CString strName , strDesc;

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

	case DVMCLASSID_CDVMLOGICDEVICE:

		if ( m_nCtrlType == 6 )
		{
			pos = ((CExBaseList*)pData)->GetHeadPosition();

			if ( nRow == 1 )
			{
				m_pFirstDvmDataset = NULL;
			}

			while (pos != NULL)
			{
				pExBaseObject = ((CExBaseList*)pData)->GetNext(pos);
				if ( pExBaseObject->GetClassID() == DVMCLASSID_CRPTCTRLS )
				{
					posDetail = ((CExBaseList*)pExBaseObject)->GetHeadPosition();
					strName = pExBaseObject->m_strName;

					while( posDetail != NULL )
					{
						pRptCtrl = (CRptCtrl *)(((CExBaseList*)pExBaseObject)->GetNext(posDetail));
						ShowData_RptCtrl(pRptCtrl, nRow ,strName );
						nRow++;
					}
				}
			}

			nRow--;
		} 
		else if ( m_nCtrlType == 7 )
		{
			pos = ((CExBaseList*)pData)->GetHeadPosition();

			if ( nRow == 1 )
			{
				m_pFirstDvmDataset = NULL;
			}

			while (pos != NULL)
			{
				pExBaseObject = ((CExBaseList*)pData)->GetNext(pos);
				if ( pExBaseObject->GetClassID() == DVMCLASSID_CLOGCTRLS )
				{
					posDetail = ((CExBaseList*)pExBaseObject)->GetHeadPosition();
					strName = pExBaseObject->m_strName;

					while( posDetail != NULL )
					{
						pLogCtrl = (CLogCtrl *)(((CExBaseList*)pExBaseObject)->GetNext(posDetail));
						ShowData_LogCtrl(pLogCtrl, nRow ,strName );
						nRow++;
					}
				}
			}

			nRow--;
			
		} 
		else if ( m_nCtrlType == 8 )
		{
			strName = pData->m_strName;
			strDesc = pData->m_strID;
			pos = ((CExBaseList*)pData)->GetHeadPosition();

			while (pos != NULL)
			{
				pExBaseObject = ((CExBaseList*)pData)->GetNext(pos);
				if ( pExBaseObject->GetClassID() == DVMCLASSID_CDVMDATASET )
				{
					pDvmDataset = (CDvmDataset*)pExBaseObject;
					ShowData_DataSet(pDvmDataset, nRow ,strName ,strDesc);
					nRow++;
				}
			}

			nRow--;
		}
		
		break;

	case DVMCLASSID_CDVMDATASET:
		ShowData_DataSet((CDvmDataset*)pData, nRow ,_T("/") ,_T("/"));
		break;

	}

	nRow++;
}

void CSclVisualCtrlGrid::UpdateCheck()
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

void CSclVisualCtrlGrid::ShowData_GooseInput(CSclCtrlGsIn *pGsIn,int nRow)
{
	//_T("序号")
	Show_Index(pGsIn, nRow, 0);
	
// 	//_T("选择")
// 	Show_Check(pGsIn, nRow, 1, &pGsIn->m_nSelect);

	//_T("AppID")
	Show_Hex(pGsIn, nRow, 1, &pGsIn->m_dwAppID, 2, FALSE);

	//_T("MAC")
	Show_StaticString(pGsIn, nRow, 2, &pGsIn->m_strMac);

	// _T("控制块所在IED")
	Show_StaticString(pGsIn, nRow, 3, &pGsIn->m_strIedDesc);

	// _T("控制块所在AP")
	Show_StaticString(pGsIn, nRow, 4, &pGsIn->apName);

	//_T("通道数")
	Show_Long(pGsIn, nRow, 5, &pGsIn->m_nChnCount, FALSE);

	//_T("通道数")
	Show_Long(pGsIn, nRow, 6, &pGsIn->m_nChnRefCount, FALSE);

	// _T("控制块所在数据集描述")
	Show_StaticString(pGsIn, nRow, 7, &pGsIn->m_strDataSetDesc);

	//_T("gocbRef")
	Show_StaticString(pGsIn, nRow, 8, &pGsIn->gocbref);

	//_T("Dataset")
	Show_StaticString(pGsIn, nRow, 9, &pGsIn->m_strDataSet);

	//_T("goID")
	Show_StaticString(pGsIn, nRow, 10, &pGsIn->m_strGooseId);
	
	// _T("confRev")
	Show_Long(pGsIn, nRow, 11, &pGsIn->m_dwVersion, FALSE);

	// _T("VLANID")
	Show_DWORD(pGsIn, nRow, 12, &pGsIn->m_dwVLandID, FALSE);

	// _T("VLANPRI")
	Show_Long(pGsIn, nRow, 13, &pGsIn->m_dwVLandPriority, FALSE);

	//_T("MinTime")
	Show_Long(pGsIn, nRow, 14, &pGsIn->scl_gse_MinTime, FALSE);

	// _T("MaxTime")
	Show_Long(pGsIn, nRow, 15, &pGsIn->scl_gse_MaxTime, FALSE);
}

void CSclVisualCtrlGrid::ShowData_GooseOutput(CSclCtrlGsOut *pGsOut,int nRow)
{
	//_T("序号")
	Show_Index(pGsOut, nRow, 0);

// 	//_T("选择")
// 	Show_Check(pGsOut, nRow, 1, &pGsOut->m_nSelect);

	//_T("AppID")
	Show_Hex(pGsOut, nRow, 1, &pGsOut->m_dwAppID, 2, FALSE);

	//_T("MAC")
	Show_StaticString(pGsOut, nRow, 2, &pGsOut->m_strMac);

	// _T("控制块所在AP")
	Show_StaticString(pGsOut, nRow, 3, &pGsOut->apName);

	//_T("通道数")
	Show_Long(pGsOut, nRow,4, &pGsOut->m_nChnCount, FALSE);

	// _T("数据集描述")
	Show_StaticString(pGsOut, nRow,5, &pGsOut->m_strDataSetDesc);

	//_T("gocbRef")
	Show_StaticString(pGsOut, nRow, 6, &pGsOut->gocbref);

	//_T("Dataset")
	Show_StaticString(pGsOut, nRow, 7, &pGsOut->m_strDataSet);

	//_T("goID")
	Show_StaticString(pGsOut, nRow, 8, &pGsOut->m_strGooseId);

	// _T("confRev")
	Show_Long(pGsOut, nRow, 9, &pGsOut->m_dwVersion, FALSE);

	// _T("VLANID")
	Show_DWORD(pGsOut, nRow, 10, &pGsOut->m_dwVLandID, FALSE);

	// _T("VLANPRI")
	Show_Long(pGsOut, nRow, 11, &pGsOut->m_dwVLandPriority, FALSE);

	//_T("MinTime")
	Show_Long(pGsOut, nRow, 12, &pGsOut->scl_gse_MinTime, FALSE);

	// _T("MaxTime")
	Show_Long(pGsOut, nRow, 13, &pGsOut->scl_gse_MaxTime, FALSE);
}

void CSclVisualCtrlGrid::ShowData_SMVInput(CSclCtrlSmvIn *pSmvIn,int nRow)
{
	//_T("序号")
	Show_Index(pSmvIn, nRow, 0);

// 	//_T("选择")
// 	Show_Check(pSmvIn, nRow, 1, &pSmvIn->m_nSelect);

	//_T("AppID")
	Show_Hex(pSmvIn, nRow, 1, &pSmvIn->m_dwAppID, 2, FALSE);

	//_T("MAC")
	Show_StaticString(pSmvIn, nRow, 2, &pSmvIn->m_strMac);

	//_T("控制块所在IED")
	Show_StaticString(pSmvIn, nRow, 3, &pSmvIn->iedStr);

	// _T("控制块所在AP")
	Show_StaticString(pSmvIn, nRow, 4, &pSmvIn->apName);

	// _T("控制块所在数据集描述")
	Show_StaticString(pSmvIn, nRow, 5, &pSmvIn->m_strDataSetDesc);

	//_T("SmpRate")
	Show_Long(pSmvIn, nRow, 6, &pSmvIn->scl_svcb_smpRate);

	//_T("DataSet")
	Show_StaticString(pSmvIn, nRow, 7, &pSmvIn->m_strDataSet);

	// _T("条目数")
	Show_Long(pSmvIn, nRow, 8, &pSmvIn->m_nChnCount, FALSE);

	// _T("条目数")
	Show_Long(pSmvIn, nRow, 9, &pSmvIn->m_nChnRefCount, FALSE);

	//_T("svID")
	Show_StaticString(pSmvIn, nRow, 10, &pSmvIn->m_strSVID);

	//_T("NofASDU")
	Show_Long(pSmvIn, nRow, 11, &pSmvIn->scl_svcb_nofASDU, FALSE);

	//_T("confRev")
	Show_Long(pSmvIn, nRow, 12, &pSmvIn->scl_svcb_confRev, FALSE);

	//_T("VLanID")
	Show_DWORD(pSmvIn, nRow, 13, &pSmvIn->scl_smv_VLANID, FALSE);

	//_T("VLANPRI")
	Show_DWORD(pSmvIn, nRow, 14, &pSmvIn->scl_smv_VLANPRI, FALSE);

}

void CSclVisualCtrlGrid::ShowData_SMVOutput(CSclCtrlSmvOut *pSmvOut,int nRow)
{
	//_T("序号")
	Show_Index(pSmvOut, nRow, 0);

// 	//_T("选择")
// 	Show_Check(pSmvOut, nRow, 1, &pSmvOut->m_nSelect);

	//_T("AppID")
	Show_Hex(pSmvOut, nRow, 1, &pSmvOut->m_dwAppID, 2, FALSE);

	//_T("MAC")
	Show_StaticString(pSmvOut, nRow, 2, &pSmvOut->m_strMac);

	//_T("控制块所在AP")
	Show_StaticString(pSmvOut, nRow, 3, &pSmvOut->apName);

	// _T("数据集描述")
	Show_StaticString(pSmvOut, nRow, 4, &pSmvOut->m_strDataSetDesc);

	// _T("SmpRate")
	Show_Long(pSmvOut, nRow, 5, &pSmvOut->scl_svcb_smpRate);

	//_T("DataSet")
	Show_StaticString(pSmvOut, nRow, 6, &pSmvOut->m_strDataSet);

	//_T("条目数")
	Show_Long(pSmvOut, nRow, 7, &pSmvOut->m_nChnCount, FALSE);

	//_T("svID")
	Show_StaticString(pSmvOut, nRow, 8, &pSmvOut->m_strSVID);

	//_T("confRev")
	Show_Long(pSmvOut, nRow, 9, &pSmvOut->scl_svcb_nofASDU, FALSE);

	//_T("NofASDU")
	Show_Long(pSmvOut, nRow, 10, &pSmvOut->scl_svcb_confRev, FALSE);

	//_T("VLanID")
	Show_DWORD(pSmvOut, nRow, 11, &pSmvOut->scl_smv_VLANID, FALSE);

	//_T("VLANPRI")
	Show_DWORD(pSmvOut, nRow, 12, &pSmvOut->scl_smv_VLANPRI, FALSE);
}

void CSclVisualCtrlGrid::ShowData_RptCtrl(CRptCtrl *pRptCtrl,int nRow ,CString strName)
{
	CDvmLogicDevice *pLogicDvm = (CDvmLogicDevice *)pRptCtrl->GetAncestor(DVMCLASSID_CDVMLOGICDEVICE);
	CDvmDataset *pDvmDataset = NULL;

	POS pos = NULL;
	CString strTmp;
	pos = pLogicDvm->GetHeadPosition();
	while( pos != NULL )
	{
		pDvmDataset = (CDvmDataset *)pLogicDvm->GetNext(pos);
		strTmp = pDvmDataset->m_strID.Right(pRptCtrl->m_strDatSet.GetLength());

		if (strTmp == pRptCtrl->m_strDatSet)
		{
			break;
		}
	}

	if ( nRow == 1)
	{
		m_pFirstDvmDataset = pDvmDataset;
	} 

	CString strValue;
	//_T("序号")
	Show_Index(pDvmDataset, nRow, 0);

	//_T("名称")
	Show_StaticString(pDvmDataset, nRow, 1, &pRptCtrl->m_strName);

	//_T("所在LD名")
	Show_StaticString(pDvmDataset, nRow, 2, &strName);

	//_T("rptID值")
	Show_StaticString(pDvmDataset, nRow, 3, &pRptCtrl->m_strID);

	//_T("关联数据集")
	Show_StaticString(pDvmDataset, nRow, 4, &pRptCtrl->m_strDatSet);

	//_T("配置版本号")
	Show_Long(pDvmDataset, nRow, 5, &pRptCtrl->m_nConfRev, FALSE);

	//_T("完整性周期")
	Show_Long(pDvmDataset, nRow, 6, &pRptCtrl->m_nIntgPd, FALSE);

	//_T("缓存")
	if (pRptCtrl->m_nBuffered)
	{
		strValue = "是";
	} 
	else
	{
		strValue = "否";
	}
	Show_StaticString(pDvmDataset, nRow, 7, &strValue);

	//_T("缓存时间")
	Show_Long(pDvmDataset, nRow, 8, &pRptCtrl->m_nBufTime, FALSE);

	//_T("最大实例化数")
	Show_Long(pDvmDataset, nRow, 9, &pRptCtrl->m_nRptEnabled, FALSE);

	//_T("TrgOps值")
	Show_Long(pDvmDataset, nRow, 10, &pRptCtrl->m_nTrgOps, FALSE);

	//_T("OptFields值")
	Show_Long(pDvmDataset, nRow, 11, &pRptCtrl->m_nOptFields, FALSE);

}


void CSclVisualCtrlGrid::ShowData_LogCtrl(CLogCtrl *pLogCtrl,int nRow ,CString strName)
{
	CDvmLogicDevice *pLogicDvm = (CDvmLogicDevice *)pLogCtrl->GetAncestor(DVMCLASSID_CDVMLOGICDEVICE);
	CDvmDataset *pDvmDataset = NULL;

	POS pos = NULL;
	CString strTmp;
	pos = pLogicDvm->GetHeadPosition();
	while( pos != NULL )
	{
		pDvmDataset = (CDvmDataset *)pLogicDvm->GetNext(pos);
		strTmp = pDvmDataset->m_strID.Right(pLogCtrl->m_strDatSet.GetLength());

		if (strTmp == pLogCtrl->m_strDatSet)
		{
			break;
		}
	}

	if ( nRow == 1)
	{
		m_pFirstDvmDataset = pDvmDataset;
	} 

	CString strValue;
	//_T("序号")
	Show_Index(pDvmDataset, nRow, 0);

	//_T("名称")
	Show_StaticString(pDvmDataset, nRow, 1, &pLogCtrl->m_strID);

	//_T("描述")
	Show_StaticString(pDvmDataset, nRow, 2, &pLogCtrl->m_strName);

	//_T("所在LD名")
	Show_StaticString(pDvmDataset, nRow, 3, &strName);

	//_T("关联数据集")
	Show_StaticString(pDvmDataset, nRow, 4, &pLogCtrl->m_strDatSet);

	//_T("完整性周期")
	Show_Long(pDvmDataset, nRow, 5, &pLogCtrl->m_nIntgPd, FALSE);

	//_T("logName")
	Show_StaticString(pDvmDataset, nRow, 6, &pLogCtrl->m_strLogName);

	if (pLogCtrl->m_nLogEna)
	{
		strValue = "true";
	} 
	else
	{
		strValue = "false";
	}
    //_T("日志远方使能")
	Show_StaticString(pDvmDataset, nRow, 7, &strValue);

	if (pLogCtrl->m_nReasonCode)
	{
		strValue = "true";
	} 
	else
	{
		strValue = "false";
	}
	//_T("ReasonCode")
	Show_StaticString(pDvmDataset, nRow, 8, &strValue);


	//_T("TrgOps值")
	Show_Long(pDvmDataset, nRow, 9, &pLogCtrl->m_nTrgOps, FALSE);

}


void CSclVisualCtrlGrid::ShowData_DataSet(CDvmDataset *pDvmDataset,int nRow ,CString strName ,CString strDesc)
{
	//_T("序号")
	Show_Index(pDvmDataset, nRow, 0);

	//_T("LD名称")
	Show_StaticString(pDvmDataset, nRow, 1, &strDesc);

	//_T("LD描述")
	Show_StaticString(pDvmDataset, nRow, 2, &strName);

	//_T("DataSet名称")
	Show_StaticString(pDvmDataset, nRow, 3, &pDvmDataset->m_strID);

	//_T("DataSet描述")
	Show_StaticString(pDvmDataset, nRow, 4, &pDvmDataset->m_strName);

	long nNumber = pDvmDataset->GetCount();
	//_T("通道数")
	Show_Long(pDvmDataset, nRow, 5, &nNumber ,FALSE);

}


//////////////////////////////////////////////////////////////////////////
// CSclVisualCtrlChnGrid

const int g_nSclIecCfgColsGOutChn = 6;
CString g_astrSclIecCfgTitleGOutChn[g_nSclIecCfgColsGOutChn];// = {
//	CXLanguageResourceIecBase::g_sLtxt_SICDGSerial,CXLanguageResourceIecBase::g_sLtxt_LNDescrip,CXLanguageResourceIecBase::g_sLtxt_DOIDescrip,CXLanguageResourceIecBase::g_sLtxt_DAIDescrip,
//	CXLanguageResourceIecBase::g_sLtxt_Type,CXLanguageResourceIecBase::g_sLtxt_Address//
//	_T("序号"),_T("LN描述"),_T("DOI描述"),_T("DAI描述"),_T("类型"),_T("地址")
//};
const int g_iSclIecCfgWidthGOutChn[g_nSclIecCfgColsGOutChn]={50,50, 80,80,80,80};

const int g_nSclIecCfgColsGInChn = 12;
CString g_astrSclIecCfgTitleGInChn[g_nSclIecCfgColsGInChn];// = {
//	CXLanguageResourceIecBase::g_sLtxt_SICDGSerial,CXLanguageResourceIecBase::g_sLtxt_Map,CXLanguageResourceIecBase::g_sLtxt_Type,CXLanguageResourceIecBase::g_sLtxt_InterLNDes,CXLanguageResourceIecBase::g_sLtxt_ExterLNDes,
//	CXLanguageResourceIecBase::g_sLtxt_InterDODes,CXLanguageResourceIecBase::g_sLtxt_ExterDODes,CXLanguageResourceIecBase::g_sLtxt_InterDUDes,CXLanguageResourceIecBase::g_sLtxt_ExterDUDes,CXLanguageResourceIecBase::g_sLtxt_InterNO,
//	CXLanguageResourceIecBase::g_sLtxt_ExterNO,CXLanguageResourceIecBase::g_sLtxt_InterPath,CXLanguageResourceIecBase::g_sLtxt_ExterPath//
//	_T("序号"),_T("映射"), _T("类型"), _T("内部LN描述"),_T("外部LN描述"), _T("内部DO描述"),
//	_T("外部DO描述"), _T("内部DU描述"), _T("外部DU描述"), _T("内部序号"),_T("外部序号"),_T("内部路径"),  _T("外部路径")
//};
const int g_iSclIecCfgWidthGinChn[g_nSclIecCfgColsGInChn]={50, 80,80,80,80, 80,80,80,80, 80,80,80};

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
//	CXLanguageResourceIecBase::g_sLtxt_ExterDODes,CXLanguageResourceIecBase::g_sLtxt_InterDUDes,CXLanguageResourceIecBase::g_sLtxt_ExterDUDes,CXLanguageResourceIecBase::g_sLtxt_InterNO,CXLanguageResourceIecBase::g_sLtxt_ExterNO,
//	CXLanguageResourceIecBase::g_sLtxt_InterPath,CXLanguageResourceIecBase::g_sLtxt_ExterPath//
	_T("序号"),_T("内部LN描述"),_T("外部LN描述"), _T("内部DO描述"),
	_T("外部DO描述"), _T("内部DU描述"), _T("外部DU描述"), _T("内部序号"),_T("外部序号"),_T("内部路径"),  _T("外部路径")
};
const int g_iSclIecCfgWidthSmvInChn[g_nSclIecCfgColsSmvInChn]={50,50, 80,80,80,80,50, 80,80,80,80};

const int g_nSclIecCfgColsSmvOutChnRef = 12;
CString g_astrSclIecCfgTitleSmvOutChnRef[g_nSclIecCfgColsSmvOutChnRef] = {
	_T("序号"),_T("输出端LN描述"),_T("输出端DOI描述"),_T("输出端DU描述"),_T("输出端序号"), _T("输出端地址"), _T("接收端IED名称"), _T("接收端序号"), _T("接收端LN描述"), _T("接收端DO描述"), _T("接收端DU描述") , _T("接收端内部路径")
};
const int g_iSclIecCfgWidthSmvOutChnRef[g_nSclIecCfgColsSmvOutChnRef]={60, 60, 80, 80, 80, 80, 80, 80, 80, 80, 80 ,80};


const int g_nSclIecCfgColsGsOutChnRef = 13;
CString g_astrSclIecCfgTitleGsOutChnRef[g_nSclIecCfgColsGsOutChnRef] = {
	_T("序号"), _T("类型"), _T("输出端LN描述"),_T("输出端DOI描述"),_T("输出端DU描述"),_T("输出端序号"), _T("输出端地址"), _T("接收端IED名称"), _T("接收端序号"), _T("接收端LN描述"), _T("接收端DO描述"), _T("接收端DU描述") , _T("接收端内部路径")
};
const int g_iSclIecCfgWidthGsOutChnRef[g_nSclIecCfgColsGsOutChnRef]={60, 60, 60, 80, 80, 80, 80, 80, 80, 80, 80, 80 ,80};


const int g_nSclIecCfgColsDataSetChn = 11;
CString g_astrSclIecCfgTitleDataSetChn[g_nSclIecCfgColsDataSetChn] = {
	_T("序号"),_T("数据集描述"), _T("数据通道路径"),
	_T("数据通道描述"), _T("DataType"), _T("值路径"), _T("ValueType"),
	_T("单位"),_T("最小值"),_T("最大值"),_T("步长")
};
const int g_iSclIecCfgWidthDataSetChn[g_nSclIecCfgColsDataSetChn]={50 , 80 ,80 ,80 ,80 ,50 , 80 ,80 ,80 ,80 ,80};



CSclVisualCtrlChnGrid::CSclVisualCtrlChnGrid()
{
	m_nOldSclIecCfgClassID = 0;
	m_nCtrlType = 0;
}

CSclVisualCtrlChnGrid::~CSclVisualCtrlChnGrid()
{
}

void CSclVisualCtrlChnGrid::InitGridTitle()
{
	g_astrSclIecCfgTitleGOutChn[0]=CXLanguageResourceIecBase::g_sLtxt_SICDGSerial;//20161015
	g_astrSclIecCfgTitleGOutChn[1]=CXLanguageResourceIecBase::g_sLtxt_LNDescrip;//20161015
	g_astrSclIecCfgTitleGOutChn[2]=CXLanguageResourceIecBase::g_sLtxt_DOIDescrip;//20161015
	g_astrSclIecCfgTitleGOutChn[3]=CXLanguageResourceIecBase::g_sLtxt_DAIDescrip;//20161015
	g_astrSclIecCfgTitleGOutChn[4]=_T("类型");//20161015
	g_astrSclIecCfgTitleGOutChn[5]=CXLanguageResourceIecBase::g_sLtxt_Address;//20161015
	g_astrSclIecCfgTitleGInChn[0]=CXLanguageResourceIecBase::g_sLtxt_SICDGSerial;//20161015
//	g_astrSclIecCfgTitleGInChn[1]=CXLanguageResourceIecBase::g_sLtxt_Map;//20161015
	g_astrSclIecCfgTitleGInChn[1]=_T("类型");//20161015
	g_astrSclIecCfgTitleGInChn[2]=CXLanguageResourceIecBase::g_sLtxt_InterLNDes;//20161015
	g_astrSclIecCfgTitleGInChn[3]=CXLanguageResourceIecBase::g_sLtxt_ExterLNDes;//20161015
	g_astrSclIecCfgTitleGInChn[4]=CXLanguageResourceIecBase::g_sLtxt_InterDODes;//20161015
	g_astrSclIecCfgTitleGInChn[5]=CXLanguageResourceIecBase::g_sLtxt_ExterDODes;//20161015
	g_astrSclIecCfgTitleGInChn[6]=CXLanguageResourceIecBase::g_sLtxt_InterDUDes;//20161015
	g_astrSclIecCfgTitleGInChn[7]=CXLanguageResourceIecBase::g_sLtxt_ExterDUDes;//20161015
	g_astrSclIecCfgTitleGInChn[8]=CXLanguageResourceIecBase::g_sLtxt_InterNO;//20161015
	g_astrSclIecCfgTitleGInChn[9]=CXLanguageResourceIecBase::g_sLtxt_ExterNO;//20161015
	g_astrSclIecCfgTitleGInChn[10]=CXLanguageResourceIecBase::g_sLtxt_InterPath;//20161015
	g_astrSclIecCfgTitleGInChn[11]=CXLanguageResourceIecBase::g_sLtxt_ExterPath;//20161015
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
		if (m_nCtrlType == 22)
		{
			nCols = g_nSclIecCfgColsSmvOutChnRef;
			pstrTitle = g_astrSclIecCfgTitleSmvOutChnRef;
			pnWidth = g_iSclIecCfgWidthSmvOutChnRef;
			break;
		} 
		else
		{
			nCols = g_nSclIecCfgColsSmvOutChn;
			pstrTitle = g_astrSclIecCfgTitleSmvOutChn;
			pnWidth = g_iSclIecCfgWidthSmvOutChn;
			break;
		}

	case SCLIECCLASSID_CTRL_SMV_IN:
		nCols = g_nSclIecCfgColsSmvInChn;
		pstrTitle = g_astrSclIecCfgTitleSmvInChn;
		pnWidth = g_iSclIecCfgWidthSmvInChn;
		break;

	case SCLIECCLASSID_CTRL_GS_OUT:
		if (m_nCtrlType == 22)
		{
			nCols = g_nSclIecCfgColsGsOutChnRef;
			pstrTitle = g_astrSclIecCfgTitleGsOutChnRef;
			pnWidth = g_iSclIecCfgWidthGsOutChnRef;
			break;
		}
		else
		{
			nCols = g_nSclIecCfgColsGOutChn;
			pstrTitle = g_astrSclIecCfgTitleGOutChn;
			pnWidth = g_iSclIecCfgWidthGOutChn;
			break;
		}

	case SCLIECCLASSID_CTRL_GS_IN:
		nCols = g_nSclIecCfgColsGInChn;
		pstrTitle = g_astrSclIecCfgTitleGInChn;
		pnWidth = g_iSclIecCfgWidthGinChn;
		break;

	case DVMCLASSID_CDVMDATASET:
		nCols = g_nSclIecCfgColsDataSetChn;
		pstrTitle = g_astrSclIecCfgTitleDataSetChn;
		pnWidth = g_iSclIecCfgWidthDataSetChn;
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

void CSclVisualCtrlChnGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
	POS pos = NULL;
	CDvmDataset *pDvmDataSet = NULL;
	CSclChSmvIn *pSclChSmvIn = NULL;
	CSclChGsIn *pSclChGsIn = NULL;

	switch (nClassID)
	{
	case SCLIECCLASSID_CH_SMV_OUT:
		if (m_nCtrlType == 22)
		{
			pos = (((CSclChSmvOut*)pData)->m_oChInRefs).GetHeadPosition();

			while (pos != NULL)
			{
				pSclChSmvIn = (CSclChSmvIn*)(((CSclChSmvOut*)pData)->m_oChInRefs).GetNext(pos);
				ShowData_SMVOutputChnRef((CSclChSmvOut*)pData, pSclChSmvIn ,nRow);
				nRow++;
			}

			long nRowRef = (((CSclChSmvOut*)pData)->m_oChInRefs).GetCount();
			if (nRowRef > 1)
			{
				Merge((nRow-nRowRef) ,1, (nRow-1) , 1);
				Merge((nRow-nRowRef) ,2, (nRow-1) , 2);
				Merge((nRow-nRowRef) ,3, (nRow-1) , 3);
				Merge((nRow-nRowRef) ,4, (nRow-1) , 4);
				Merge((nRow-nRowRef) ,5, (nRow-1) , 5);
			}

			nRow--;
		} 
		else
		{
			ShowData_SMVOutputChn((CSclChSmvOut*)pData, nRow);
		}
		break;

	case SCLIECCLASSID_CH_SMV_IN:
		ShowData_SMVInputChn((CSclChSmvIn*)pData, nRow);
		break;

	case SCLIECCLASSID_CH_GS_OUT:
		if (m_nCtrlType == 22)
		{
			pos = (((CSclChGsOut*)pData)->m_oChInRefs).GetHeadPosition();

			while (pos != NULL)
			{
				pSclChGsIn = (CSclChGsIn*)(((CSclChGsOut*)pData)->m_oChInRefs).GetNext(pos);
				ShowData_GooseOutputChnRef((CSclChGsOut*)pData, pSclChGsIn ,nRow);
				nRow++;
			}

			long nRowRef = (((CSclChGsOut*)pData)->m_oChInRefs).GetCount();
			if (nRowRef > 1)
			{
				Merge((nRow-nRowRef) ,1, (nRow-1) , 1);
				Merge((nRow-nRowRef) ,2, (nRow-1) , 2);
				Merge((nRow-nRowRef) ,3, (nRow-1) , 3);
				Merge((nRow-nRowRef) ,4, (nRow-1) , 4);
				Merge((nRow-nRowRef) ,5, (nRow-1) , 5);
				Merge((nRow-nRowRef) ,6, (nRow-1) , 6);
			}

			nRow--;
		} 
		else
		{
			ShowData_GooseOutputChn((CSclChGsOut*)pData, nRow);
		}
		break;

	case SCLIECCLASSID_CH_GS_IN:
		ShowData_GooseInputChn((CSclChGsIn*)pData, nRow);
		break;

	case DVMCLASSID_CDVMDATA:
		pDvmDataSet = (CDvmDataset *)pData->GetAncestor(DVMCLASSID_CDVMDATASET);
		ShowData_DataSetChn((CDvmData*)pData, nRow ,pDvmDataSet->m_strName);
		break;

	}

	nRow++;
}



void CSclVisualCtrlChnGrid::ShowData_GooseInputChn(CSclChGsIn *pChn,int nRow)
{
	//_T("序号")
	Show_Index(pChn, nRow, 0);

// 	//_T("映射")
// 	Show_StaticString(pChn, nRow, 1, &pChn->fcda_map);

	// _T("类型")
	Show_StaticString(pChn, nRow, 1, &pChn->fcda_type);

	// _T("内部LN描述")
	Show_StaticString(pChn, nRow, 2, &pChn->inLNDesc);

	//_T("外部LN描述")
	Show_StaticString(pChn, nRow, 3, &pChn->fcda_lndesc);

	// _T("内部DO描述")
	Show_StaticString(pChn, nRow, 4, &pChn->inDODesc);

	//_T("外部DO描述")
	Show_StaticString(pChn, nRow, 5, &pChn->fcda_dodesc);
	
	// _T("内部DU描述")
	Show_StaticString(pChn, nRow, 6, &pChn->inDADesc);
	
	// _T("外部DU描述")
	Show_StaticString(pChn, nRow, 7, &pChn->fcda_desc);
	
	// _T("内部序号")
	Show_Long(pChn, nRow, 8, &pChn->inIndex, FALSE);
	
	//_T("外部序号")
	Show_Long(pChn, nRow, 9, &pChn->outIndex, FALSE);

	//_T("内部路径")
	Show_StaticString(pChn, nRow, 10, &pChn->inPath);

	// _T("外部路径")
	Show_StaticString(pChn, nRow, 11, &pChn->fcda_name);
}

void CSclVisualCtrlChnGrid::ShowData_GooseOutputChn(CSclChGsOut *pChn,int nRow)
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

void CSclVisualCtrlChnGrid::ShowData_GooseOutputChnRef(CSclChGsOut *pChn, CSclChGsIn *pSclChGsIn ,int nRow)
{
	CSclIed *pSclIed = (CSclIed*)pSclChGsIn->GetAncestor(SCLIECCLASSID_IED);
	CString strIedName;
	strIedName.Format("name = \"%s\" , desc = \"%s\" ",pSclIed->m_strID ,pSclIed->m_strName);
	long nIndex = pSclChGsIn->outIndex + 1;

	// 序号
	Show_Index(pChn, nRow, 0);

	// 类型
	Show_String(pChn, nRow, 1, &pChn->fcda_type);

	// 输出端LN描述
	Show_String(pChn, nRow, 2, &pChn->fcda_lndesc);

	// 输出端DOI描述
	Show_String(pChn, nRow, 3, &pChn->fcda_dodesc);

	// 输出端DU描述
	Show_StaticString(pChn, nRow, 4, &pChn->fcda_desc);

	// 输出端序号
	Show_Long(pChn, nRow, 5, &nIndex ,FALSE);

	// 输出端地址
	Show_StaticString(pChn, nRow, 6, &pChn->fcda_name);

	// 接收端IED名称
	Show_StaticString(pChn, nRow, 7, &strIedName);

	// 接收端序号
	Show_Long(pChn, nRow, 8, &pSclChGsIn->inIndex ,FALSE);

	// 接收端LN描述
	Show_StaticString(pChn, nRow, 9, &pSclChGsIn->inLNDesc);

	// 接收端DO描述
	Show_StaticString(pChn, nRow, 10, &pSclChGsIn->inDODesc);

	// 接收端DU描述
	Show_StaticString(pChn, nRow, 11, &pSclChGsIn->inDADesc);

	// 接收端内部路径
	Show_StaticString(pChn, nRow, 12, &pSclChGsIn->inPath);
}

void CSclVisualCtrlChnGrid::ShowData_SMVInputChn(CSclChSmvIn *pChn,int nRow)
{
	long nIndex = 0;
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
	nIndex = pChn->outIndex+1;
	Show_Long(pChn, nRow, 8, &nIndex, FALSE);

	//_T("内部路径")
	Show_StaticString(pChn, nRow, 9, &pChn->inPath);

	// _T("外部路径")
	Show_StaticString(pChn, nRow, 10, &pChn->fcda_name);
}

void CSclVisualCtrlChnGrid::ShowData_SMVOutputChn(CSclChSmvOut *pChn,int nRow)
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

void CSclVisualCtrlChnGrid::ShowData_SMVOutputChnRef(CSclChSmvOut *pChn ,CSclChSmvIn *pSclChSmvIn, int nRow)
{
	CSclIed *pSclIed = (CSclIed*)pSclChSmvIn->GetAncestor(SCLIECCLASSID_IED);
	CString strIedName;
	strIedName.Format("name = \"%s\" , desc = \"%s\" ",pSclIed->m_strID ,pSclIed->m_strName);
	long nIndex = pSclChSmvIn->outIndex + 1;
	
	// 序号
	Show_Index(pChn, nRow, 0);

	// 输出端LN描述
	Show_String(pChn, nRow, 1, &pChn->fcda_lndesc);

	// 输出端DOI描述
	Show_String(pChn, nRow, 2, &pChn->fcda_dodesc);

	// 输出端DU描述
	Show_StaticString(pChn, nRow, 3, &pChn->fcda_desc);

	// 输出端序号
	Show_Long(pChn, nRow, 4, &nIndex ,FALSE);

	// 输出端地址
	Show_StaticString(pChn, nRow, 5, &pChn->fcda_name);

	// 接收端IED名称
	Show_StaticString(pChn, nRow, 6, &strIedName);

	// 接收端序号
	Show_Long(pChn, nRow, 7, &pSclChSmvIn->inIndex ,FALSE);

	// 接收端LN描述
	Show_StaticString(pChn, nRow, 8, &pSclChSmvIn->inLNDesc);

	// 接收端DO描述
	Show_StaticString(pChn, nRow, 9, &pSclChSmvIn->inDODesc);

	// 接收端DU描述
	Show_StaticString(pChn, nRow, 10, &pSclChSmvIn->inDADesc);

	// 接收端内部路径
	Show_StaticString(pChn, nRow, 11, &pSclChSmvIn->inPath);
}


void CSclVisualCtrlChnGrid::ShowData_DataSetChn(CDvmData *pChn,int nRow ,CString strName)
{
	// 序号
	Show_Index(pChn, nRow, 0);

	// 数据集描述
	Show_String(pChn, nRow, 1, &strName);

	// 数据通道路径
	Show_String(pChn, nRow, 2, &pChn->m_strID);

	// 数据通道描述
	if (pChn->m_strName.IsEmpty())
	{
		Show_StaticString(pChn, nRow, 3, _T("/"));
	} 
	else
	{
		Show_String(pChn, nRow, 3, &pChn->m_strName);
	}
	
	// DataType
	Show_String(pChn, nRow, 4, &pChn->m_strDataType);

	CDvmValue *pDvmValue = (CDvmValue *)((CDvmData*)pChn)->GetHead();

	if (pDvmValue == NULL)
	{
		// 值路径
		Show_StaticString(pChn, nRow, 5, _T("/"));

		// ValueType
		Show_StaticString(pChn, nRow, 6, _T("/"));

	} 
	else
	{
		// 值路径
		Show_String(pChn, nRow, 5, &pDvmValue->m_strName);

		// ValueType
		Show_String(pChn, nRow, 6, &pDvmValue->m_strDataType);

	}

	// 单位
	if (pChn->m_strUnit == "")
	{
		Show_StaticString(pChn, nRow, 7, _T("/"));
	} 
	else
	{
		Show_StaticString(pChn, nRow, 7, &pChn->m_strUnit);		
	}
	
	// 最小值
	if (pChn->m_strMin == "")
	{
		Show_StaticString(pChn, nRow, 8, _T("/"));
	} 
	else
	{
		Show_StaticString(pChn, nRow, 8, &pChn->m_strMin);		
	}

	// 最大值
	if (pChn->m_strMax.IsEmpty())
	{
		Show_StaticString(pChn, nRow, 9,  _T("/"));		
	} 
	else
	{
		Show_StaticString(pChn, nRow, 9, &pChn->m_strMax);
	}
	
	// 步长
	if (pChn->m_strStep.IsEmpty())
	{
		Show_StaticString(pChn, nRow, 10,  _T("/"));
	} 
	else
	{
		Show_StaticString(pChn, nRow, 10, &pChn->m_strStep);	
	}
	
}