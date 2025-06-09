#include "SttIecCbGrid.h"
#include "../../UI/Module/CommonCtrl_QT/QIecWidgetDelegate.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../XLangResource_Native.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDevice6044.h"


#define CAPDEVICEGRID_COLS			6

#define CAPDEVICEGRID_INDEX			0
#define CAPDEVICEGRID_SELECT		0
#define CAPDEVICEGRID_TYPE			1
#define CAPDEVICEGRID_APPID			2
#define CAPDEVICEGRID_NAME		3
#define CAPDEVICEGRID_FIBER		4
#define CAPDEVICEGRID_CHCOUNT		5
//#define CAPDEVICEGRID_SRCMAC		3
//#define CAPDEVICEGRID_CTRLBLOCK	5
#define CAPDEVICEGRID_DESTMAC		2

CSttIecCbGrid::CSttIecCbGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_bViewSmv = TRUE;
	m_bViewGoose = TRUE;
	m_bViewFT3 = FALSE;
	m_pAllSelCBs = NULL;
	m_nIecCbShowType = STT_IECCBGRID_SHOW_TYPE_61850;
}

CSttIecCbGrid::~CSttIecCbGrid()
{
	if (m_pAllSelCBs != NULL)
	{
		m_pAllSelCBs->RemoveAll();
		delete m_pAllSelCBs;
		m_pAllSelCBs = NULL;
	}
}

void CSttIecCbGrid::InitGrid()
{
	if (m_bViewFT3)
	{
		if (m_nIecCbShowType != STT_IECCBGRID_SHOW_TYPE_60044)
		{
			m_nIecCbShowType = STT_IECCBGRID_SHOW_TYPE_60044;
		}
	}
	else if (m_nIecCbShowType != STT_IECCBGRID_SHOW_TYPE_61850)
	{
		m_nIecCbShowType = STT_IECCBGRID_SHOW_TYPE_61850;
	}

 	QExBaseListGridBase::InitGrid();
	QExBaseListCheckBoxDelegate *pCtrlBlockSelectDelegate = new QExBaseListCheckBoxDelegate(this);
	setItemDelegateForColumn(0,pCtrlBlockSelectDelegate);
// 	QIecNumberEditDelegate *pAppIDDelegate = new QIecNumberEditDelegate(QIecLineEdit::HEX_TEXT,this);
// 	setItemDelegateForColumn(CAPDEVICEGRID_APPID,pAppIDDelegate);

}

void CSttIecCbGrid::InitGridTitle()
{
	if (m_nIecCbShowType == STT_IECCBGRID_SHOW_TYPE_60044)
	{
		InitGridTitle_60044();
	} 
	else
	{
		InitGridTitle_61850();
	}
}

void CSttIecCbGrid::InitGridTitle_61850()
{
	CString astrGridTitle[6];
	//	= {"选择", "类型","APPID",_T("描述"),"光口","通道数"};
	xlang_GetLangStrByFile(astrGridTitle[0],_T("sSelect"));
	xlang_GetLangStrByFile(astrGridTitle[1],_T("sType"));
	astrGridTitle[2] = "APPID";
//	xlang_GetLangStrByFile(astrGridTitle[2],_T("Native_APPID"));
	xlang_GetLangStrByFile(astrGridTitle[3],_T("State_Description"));
	xlang_GetLangStrByFile(astrGridTitle[4],_T("IEC_FI"));
	xlang_GetLangStrByFile(astrGridTitle[5],_T("IEC_ChannelNumber"));
	//= {"选择", "类型","APPID",_T("描述"),"光口","通道数"};
#ifdef _PSX_QT_LINUX_
	int iGridWidth[6]={60, 80, 100, 450, 100, 120};
#else
	int iGridWidth[6]={60, 80, 100, 300, 100, 120};
#endif
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 6);
}

void CSttIecCbGrid::InitGridTitle_60044()
{
	CString astrGridTitle[6];
	//	= {"选择", "类型","APPID",_T("描述"),"光口","通道数"};
	xlang_GetLangStrByFile(astrGridTitle[0],_T("sSelect"));
	xlang_GetLangStrByFile(astrGridTitle[1],_T("sType"));
	astrGridTitle[2] = /*"采样率"*/g_sLangTxt_Native_SamplingFrequency;
	astrGridTitle[3] = /*"波特率"*/g_sLangTxt_Native_BaudRate;
	xlang_GetLangStrByFile(astrGridTitle[4],_T("IEC_FI"));
	astrGridTitle[5] = /*"报文长度"*/g_sLangTxt_Native_MsgLength;
	int iGridWidth[6]={60, 150, 150, 150, 150, 150};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 6);
}

void CSttIecCbGrid::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	BOOL bGridChanged = FALSE;

	if (m_bViewFT3)
	{
		if (m_nIecCbShowType != STT_IECCBGRID_SHOW_TYPE_60044)
		{
			bGridChanged = TRUE;
			m_nIecCbShowType = STT_IECCBGRID_SHOW_TYPE_60044;
		}
	}
	else if (m_nIecCbShowType != STT_IECCBGRID_SHOW_TYPE_61850)
	{
		bGridChanged = TRUE;
		m_nIecCbShowType = STT_IECCBGRID_SHOW_TYPE_61850;
	}

	if (bGridChanged)
	{
		InitGridTitle();
	}

	QExBaseListGridBase::ShowDatas(pDatas, bResetScrollBars);
}

void CSttIecCbGrid::ShowData_61850(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CCapDeviceBase *pCapDevice = (CCapDeviceBase*)pData;

	CString strDesc,strTextTmp;
	strDesc = pCapDevice->GetCtrlDesc();
	Show_Check(pData, nRow, CAPDEVICEGRID_SELECT, &pCapDevice->m_bSelect,EndEditCell_SelectCB);
    Show_61850Type(pData, nRow, CAPDEVICEGRID_TYPE, pCapDevice->m_nType);
	strTextTmp.Format(_T("0X%04X"),pCapDevice->m_dwAppID);
	Show_StaticString(pData, nRow, CAPDEVICEGRID_APPID,strTextTmp);
	Show_StaticString(pData, nRow, CAPDEVICEGRID_NAME, strDesc);
	Show_Fiber(pData, nRow, CAPDEVICEGRID_FIBER, pCapDevice->m_nFiberIndex);

	long nCount = pCapDevice->GetCount();

	if (nCount == 0)
	{
		Show_StaticString(pData, nRow, CAPDEVICEGRID_CHCOUNT, /*_T("未录波")*/g_sLangTxt_Gradient_Unrecorded); //lcq
	}
	else
	{
		Show_Long(pData, nRow, CAPDEVICEGRID_CHCOUNT, &nCount,FALSE);
	}
	ShowColorRow(this, pCapDevice->m_nMatchState, nRow, CAPDEVICEGRID_COLS);

	nRow++;
}

void CSttIecCbGrid::ShowData_60044(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CCapDeviceBase *pCapDevice = (CCapDeviceBase*)pData;

	if (pCapDevice->GetClassID() != CPDCLASSID_DEVICE6044)
	{
		return;
	}

	CCapDevice6044 *pDevice6044 = (CCapDevice6044*)pCapDevice;

	CString /*strDesc,*/strTextTmp;
//	strDesc = pCapDevice->GetCtrlDesc();
	Show_Check(pData, nRow, CAPDEVICEGRID_SELECT, &pCapDevice->m_bSelect,EndEditCell_SelectCB);
	Show_61850Type(pData, nRow, CAPDEVICEGRID_TYPE, pCapDevice->m_nType);
	strTextTmp.Format(_T("%ld Hz"),pDevice6044->m_nSmpRate);
	Show_StaticString(pData, nRow, 2,strTextTmp);
	strTextTmp.Format(_T("%.01lf Mbps"),pDevice6044->m_dBaudRate);
	Show_StaticString(pData, nRow, 3, strTextTmp);
	Show_Fiber(pData, nRow, CAPDEVICEGRID_FIBER, pCapDevice->m_nFiberIndex);

	strTextTmp.Format(_T("%ld"),pDevice6044->m_nPkgLenth);
	Show_StaticString(pData, nRow, 5, strTextTmp);
	ShowColorRow(this, pCapDevice->m_nMatchState, nRow, CAPDEVICEGRID_COLS);

	nRow++;
}

void CSttIecCbGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CCapDeviceBase *pCapDevice = (CCapDeviceBase*)pData;

	if (pCapDevice->m_nType == PROTOCOL_61850_TYPE_GOOSE)
	{
		if (!m_bViewGoose)
		{
			return;
		}
	}
	else if (pCapDevice->m_nType == PROTOCOL_61850_TYPE_92)
	{
		if (!m_bViewSmv)
		{
			return;
		}
	}
	else if (pCapDevice->m_nType == PROTOCOL_61850_TYPE_6044)
	{
		if (!m_bViewFT3)
		{
			return;
		}
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("未知的报文类型(%u)."),pCapDevice->m_nType);
		return;
	}

	if (bInsertRow)
	{
		insertRow(nRow);
	}

	if (m_nIecCbShowType == STT_IECCBGRID_SHOW_TYPE_60044)
	{
		ShowData_60044(pData,nRow,bInsertRow);
	} 
	else
	{
		ShowData_61850(pData,nRow,bInsertRow);
	}
}

void CSttIecCbGrid::Show_Mac(CExBaseObject *pStData, const int& nRow, const int& nCol, BYTE *pMac)
{
	CString strMac;
	strMac.Format(_T("%.2X-%.2X-%.2X-%.2X-%.2X-%.2X"), pMac[0], pMac[1], pMac[2], pMac[3], pMac[4], pMac[5]);
	Show_StaticString(pStData, nRow, nCol, strMac);
}

void CSttIecCbGrid::Show_61850Type(CExBaseObject *pStData, const int& nRow, const int& nCol, UINT nType)
{
	CString strType = ep_Get61850ProtocolType(nType);
	Show_StaticString(pStData, nRow, nCol, strType);
}

void CSttIecCbGrid::Show_Fiber(CExBaseObject *pStData, const int& nRow, const int& nCol, UINT nFiberIndex)
{
    //CString strFiber;
    //QString str = QString("光口%1").arg(nFiberIndex+1);//dingxy 20240511 更改报文探测光口乱码问题
    QString strFiber = g_sLangTxt_IEC_FI + QString("%1").arg(nFiberIndex+1);//2024-7-26 wuxinyi 更改报文探测光口乱码问题
    //strFiber = str;
	//strFiber.Format(/*_T("光口%d")*/g_sLangTxt_Gradient_POpticalPort.GetString(),nFiberIndex+1); //lcq
	Show_StaticString(pStData, nRow, nCol, strFiber);
}

void CSttIecCbGrid::UpdateDatas()
{
	if (m_pDatas == NULL)
	{
		return;
	}

	DisConnectAll_SigSlot();
	CExBaseObject *pObj = NULL;	
	POS pos = m_pDatas->GetHeadPosition();
	int nRowIndex = 0;

	while (pos != NULL)
	{
		pObj = m_pDatas->GetNext(pos);
		ShowData(pObj, nRowIndex, FALSE);
	}

	ConnectAll_SigSlot();
}

void CSttIecCbGrid::AddCapDevice(CExBaseObject *pCapDevice)
{
	if (pCapDevice == NULL)
	{
		SetRowCount(1);
	}
	else
	{
		CExBaseList *pDatas = (CExBaseList *)pCapDevice->GetParent();
		m_pDatas = pDatas;

		int nRow = GetRowCount();
        DisConnectAll_SigSlot();
		ShowData(pCapDevice, nRow, TRUE);
		ConnectAll_SigSlot();
	}
}

void CSttIecCbGrid::UpdateCapDevice(CExBaseObject *pCapDevice)
{
	if (pCapDevice == NULL)
	{
		return;
	}

	CExBaseList *pDatas = (CExBaseList *)pCapDevice->GetParent();

	if (pDatas == NULL)
	{
		return;
	}

	int nIndex = pDatas->FindIndex(pCapDevice);
	DisConnectAll_SigSlot();
	ShowData(pCapDevice, nIndex, FALSE);
	ConnectAll_SigSlot();
}

void CSttIecCbGrid::SelectRecordDevice(CExBaseObject *pStData, BOOL bSel)
{
	long nRowIndex = GetDataRow(pStData, 1);
	QColor crBkClr(255, 255, 255), crFgClr(0,0,0);

	if (nRowIndex <= 0)
	{
		return;
	}

	if (bSel)
	{
		crBkClr.setRgb(255, 255, 0);
		crFgClr.setRgb(255, 0, 0);
	}

	QTableWidgetItem *pItem = NULL;

	for (long nCol = 1; nCol<CAPDEVICEGRID_COLS; nCol++)
	{
		pItem = item(nRowIndex, nCol);

		if (pItem == NULL)
		{
			break;
		}

		pItem->setBackgroundColor(crBkClr);
		pItem->setTextColor(crFgClr);
	}
}

//该UpdateData函数，改到基类了 shaolei 20220902
// BOOL CSttIecCbGrid::UpdateData(CExBaseObject *pData)
// {
// 	int nRow = GetDataRow(pData);
// 
// 	if (nRow != -1)
// 	{
// 		ShowData(pData, nRow, FALSE);
// 	}
// 
// 	return TRUE;
// }

void CSttIecCbGrid::UpdateCapDeviceLinkState()
{
	CCapDeviceBase *pCapDevice = NULL;
	long nRow = 1;
	long nRows = rowCount();

	for (nRow=1; nRow< nRows; nRow++)
	{
		pCapDevice = (CCapDeviceBase*)GetData(nRow, 1);

		if (pCapDevice == NULL)
		{
			break;
		}

		if (pCapDevice->m_bLinkState)
		{
			SetItemBkColour(nRow, 0, 255, 255, 255);
		}
		else
		{
			SetItemBkColour(nRow, 0, 255, 0, 0);
		}
	}
}

CExBaseObject* CSttIecCbGrid::GetCurrSelData_BySelect()
{
	CExBaseObject *pSel = NULL;
	POS pos = m_pDatas->GetHeadPosition();

	while (pos != NULL)
	{
		CCapDeviceBase *pCapDevice = (CCapDeviceBase *)m_pDatas->GetNext(pos);

		if (pCapDevice->m_bSelect)
		{
			pSel = pCapDevice;
			break;
		}
	}

	return pSel;
}

CExBaseList* CSttIecCbGrid::GetAllSelectedCbs()
{
	if (m_pAllSelCBs == NULL)
	{
		m_pAllSelCBs = new CExBaseList;
	}

	m_pAllSelCBs->RemoveAll();
	POS pos = m_pDatas->GetHeadPosition();

	while (pos != NULL)
	{
		CCapDeviceBase *pCapDevice = (CCapDeviceBase *)m_pDatas->GetNext(pos);

		if (pCapDevice->m_bSelect)
		{
			m_pAllSelCBs->AddTail(pCapDevice);
		}
	}

	return m_pAllSelCBs;
}

void CSttIecCbGrid::EndEditCell_SelectCB (int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	CSttIecCbGrid *pOwnGrid = (CSttIecCbGrid*)pGrid;
	CCapDeviceBase *pCapDevice = (CCapDeviceBase *)pVCellData->pObj;

	pOwnGrid->m_pDataViewOptrInterface->OnDataSelChanged(pOwnGrid, nRow, nCol);
}

void ShowColorRow(QExBaseListGridBase* pGridCtrl, int nMatchState, int nRow, int nCols)
{
	if(pGridCtrl == NULL)
	{
		return;
	}

	QColor crMatchColor(0,0,0);

	switch (nMatchState)
	{
	case MATCH_STATE_NONE:
		crMatchColor.setRgb(0,0,0);
		break;
	case MATCH_STATE_SUCCESS:
		crMatchColor.setRgb(0,0,255);
		break;
	case MATCH_STATE_SURPLUS:
		crMatchColor.setRgb(255,0,0);
		break;
	case MATCH_STATE_MISS:
		crMatchColor.setRgb(128,128,128);
		break;
	}

	for (int iCol=0;iCol<nCols;iCol++)
	{
		pGridCtrl->SetItemFgColour(nRow, iCol, crMatchColor);
	}
}
