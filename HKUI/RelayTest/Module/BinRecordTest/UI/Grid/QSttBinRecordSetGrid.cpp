#include "QSttBinRecordSetGrid.h"
#include "../../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceRecord.h"
#include "../SttBinRecordDefine.h"

#include "../../../XLangResource_Native.h"
QSttBinRecordSetGrid::QSttBinRecordSetGrid(QWidget *parent /*= NULL*/) 
:QExBaseListGridBase(parent)
{

}

QSttBinRecordSetGrid::~QSttBinRecordSetGrid()
{

}

void QSttBinRecordSetGrid::InitGrid()
{
	InitGridTitle();
	verticalHeader()->setVisible(false);
	SetEditable(TRUE);
	connect(this, SIGNAL(cellClicked(int, int)), this, SLOT(slot_BinRecordSetGrid(int, int)));
	connect(this, SIGNAL(cellClicked(int, int)), this, SLOT(slot_CellChanged(int, int)));
}

void QSttBinRecordSetGrid::InitGridTitle()
{
	CString astrGridTitle[QSTTBINRECORDSETGRIDCOL] = { g_sLtxt_SICDGSerial, /*_T("插件名称")*/g_sLangTxt_BinRecord_PlugName, g_sLangTxt_channelname, /*_T("记录类型")*/g_sLangTxt_BinRecord_RecordType, g_sLangTxt_Native_phaseDifference, /*_T("一次侧")*/g_sLangTxt_BinRecord_PrimValue, /*_T("二次侧")*/g_sLangTxt_BinRecord_SecondValue };
	int iColType[QSTTBINRECORDSETGRIDCOL] = { QT_GVET_NOEDIT, QT_GVET_NOEDIT, QT_GVET_NOEDIT, QT_GVET_NOEDIT, QT_GVET_NOEDIT, QT_GVET_NOEDIT, QT_GVET_NOEDIT };
	int iGridWidth[QSTTBINRECORDSETGRIDCOL] = { 50, 80 ,80 , 120, 50, 100, 100 };
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, QSTTBINRECORDSETGRIDCOL);
}

void QSttBinRecordSetGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow /*= TRUE*/)
{

	ASSERT(pData);
	CDvmData *pDvmData, *pnEType, *pnChAngType, *pModuleName, *pClampRate, *pThresholds, *pPrimValue,*pSecondValue;
	CDataGroup *pDataGroup = (CDataGroup *)pData;
	if (pDataGroup->m_strValue == STT_BINRECORD_ID_STRZERO)
	{
		return;
	}
	CString strValue, strClampRate, strSwitchVolt, strEType, strChAngType, strPrim, strSecond;
	long nEType, nChAngType, nModule, nThresholds, nPrimValue, nSecondValue;
	float fpClampRate;
		
	pnEType = (CDvmData *)pDataGroup->FindByID(STT_BINRECORD_ID_RECORDTYPE);
	pnChAngType = (CDvmData *)pDataGroup->FindByID(STT_BINRECORD_ID_CHANGTYPE);
	pModuleName = (CDvmData *)pDataGroup->FindByID(STT_BINRECORD_ID_MODULE);
	pClampRate = (CDvmData *)pDataGroup->FindByID(STT_BINRECORD_ID_CLAMPRATE);
	pThresholds = (CDvmData *)pDataGroup->FindByID(STT_BINRECORD_ID_THRESHOLDS);
	pPrimValue = (CDvmData *)pDataGroup->FindByID(STT_BINRECORD_ID_PRIMVALUE);
	pSecondValue = (CDvmData *)pDataGroup->FindByID(STT_BINRECORD_ID_SECONDVALUE);
	if (pnEType != NULL)
	{
		nEType = CString_To_long(pnEType->m_strValue);
		if (nEType == STT_BINRECORD_ID_NZERO)
		{
			return;
		}
	}
	if (pnChAngType != NULL)
	{
		nChAngType = CString_To_long(pnChAngType->m_strValue);
	}
	if (pClampRate != NULL)
	{
		fpClampRate = CString_To_long(pClampRate->m_strValue);
	}
	if (pThresholds != NULL)
	{
		nThresholds = CString_To_long(pThresholds->m_strValue);
	}
	if (pPrimValue != NULL)
	{
		nPrimValue = CString_To_long(pPrimValue->m_strValue);
	}
	if (pSecondValue != NULL)
	{
		nSecondValue = CString_To_long(pSecondValue->m_strValue);
	}

	switch (nEType)
	{
	case STT_BINRECORD_ID_NZERO:
		strEType = /*_T("无效")*/g_sLangTxt_BinRecord_Invalid;
		break;
	case STT_BINRECORD_ID_NONE:
		strEType = /*_T("电压")*/g_sLangTxt_Iec_Voltage;
		break;
	case STT_BINRECORD_ID_NTWO:
		strEType = /*_T("电流")*/g_sLangTxt_Iec_Current;
		break;
	case STT_BINRECORD_ID_NTHREE:
		strEType = /*_T("开关量(无源)")*/g_sLangTxt_BinRecord_BinPassive;
		break;
	case STT_BINRECORD_ID_NFOUR:
		strEType = /*_T("开关量(有源)")*/g_sLangTxt_BinRecord_BinActive;
		break;
	default:
		break;
	}


	switch (nChAngType)
	{
	case STT_BINRECORD_ID_NZERO:
		strChAngType = STT_BINRECORD_ID_SPACE;
		break;
	case STT_BINRECORD_ID_NONE:
		strChAngType = STT_BINRECORD_ID_STRA;
		break;
	case STT_BINRECORD_ID_NTWO:
		strChAngType = STT_BINRECORD_ID_STRB;
		break;
	case STT_BINRECORD_ID_NTHREE:
		strChAngType = STT_BINRECORD_ID_STRC;
		break;
	case STT_BINRECORD_ID_NFOUR:
		strChAngType = g_sLangTxt_Iec_ZeroSeq;
		break;
	default:
		break;
	}

	strValue.Format(_T("%d"), nRow + STT_BINRECORD_ID_NONE);
	strClampRate.Format(_T("%d"), fpClampRate);
	strSwitchVolt.Format(_T("%d"), nThresholds);
	strPrim.Format(_T("%d"), nPrimValue);
	strSecond.Format(_T("%d"), nSecondValue);
	
	Show_StaticString(pDataGroup, nRow, STT_BINRECORD_ID_NZERO, strValue);
	Show_StaticString(pDataGroup, nRow, STT_BINRECORD_ID_NONE, pModuleName->m_strName);
	Show_StaticString(pDataGroup, nRow, STT_BINRECORD_ID_NTWO, pDataGroup->m_strName);
	Show_StaticString(pDataGroup, nRow, STT_BINRECORD_ID_NTHREE, strEType);
	Show_StaticString(pDataGroup, nRow, STT_BINRECORD_ID_NFOUR, strChAngType);

	if (nEType == STT_BINRECORD_ID_NONE || nEType == STT_BINRECORD_ID_NTWO)
	{
		Show_String(pDataGroup, nRow, STT_BINRECORD_ID_NFIVE, &strPrim);
		Show_String(pDataGroup, nRow, STT_BINRECORD_ID_NSIX, &strSecond);
	}
	else
	{
        Show_StaticString(pDataGroup, nRow, STT_BINRECORD_ID_NFIVE, CString(STT_BINRECORD_ID_SPACE));
        Show_StaticString(pDataGroup, nRow, STT_BINRECORD_ID_NSIX, CString(STT_BINRECORD_ID_SPACE));
	}
	nRow++;
}

void QSttBinRecordSetGrid::slot_BinRecordSetGrid(int nRow,int nCol)
{
	emit sig_BinSetGridRowValue(nRow);
}

void QSttBinRecordSetGrid::slot_CellChanged(int nRow, int nCol)
{

}

void QSttBinRecordSetGrid::MoveUp()
{
	CExBaseObject *pSel = (CExBaseObject*)GetCurrSelData(STT_BINRECORD_ID_NZERO);

	long nRow = GetDataRow(pSel);

	if (nRow < STT_BINRECORD_ID_NONE)
	{
		return;
	}
	emit sig_BinSetGridRowValue(nRow - STT_BINRECORD_ID_NONE);
	CExBaseObject *p1 = GetData(nRow - STT_BINRECORD_ID_NONE, STT_BINRECORD_ID_NZERO);
	CExBaseObject *p2 = GetData(nRow, STT_BINRECORD_ID_NZERO);
	DisConnectAll_SigSlot();
	m_pDatas->ChangePosition(p1, p2);
	ChangeRowPosition(nRow - STT_BINRECORD_ID_NONE, nRow);
	SelectRow(nRow);
	ConnectAll_SigSlot();
	SetModifiedFlag(m_pDatas);
}

void QSttBinRecordSetGrid::MoveDown()
{
	CExBaseObject *pSel = (CExBaseObject*)GetCurrSelData(STT_BINRECORD_ID_NONE);

	long nRow = GetDataRow(pSel);

	if (nRow >= GetRowCount() - STT_BINRECORD_ID_NONE)
	{
		return;
	}
	emit sig_BinSetGridRowValue(nRow + STT_BINRECORD_ID_NONE);
	CExBaseObject *p1 = GetData(nRow + STT_BINRECORD_ID_NONE, STT_BINRECORD_ID_NZERO);
	CExBaseObject *p2 = GetData(nRow, STT_BINRECORD_ID_NZERO);
	DisConnectAll_SigSlot();
	m_pDatas->ChangePosition(p1, p2);
	ChangeRowPosition(nRow, nRow + STT_BINRECORD_ID_NONE);
	SelectRow(nRow + STT_BINRECORD_ID_NTWO);
	ConnectAll_SigSlot();
	SetModifiedFlag(m_pDatas);

}

void QSttBinRecordSetGrid::MoveToTop()
{
	CExBaseObject *pSel = (CExBaseObject*)GetCurrSelData(STT_BINRECORD_ID_NZERO);

	long nRow = GetDataRow(pSel);

	if (nRow < STT_BINRECORD_ID_NONE)
	{
		return;
	}
	CExBaseObject *pTop = GetData(STT_BINRECORD_ID_NZERO, STT_BINRECORD_ID_NZERO);
	CExBaseObject *pCurr = GetData(nRow, STT_BINRECORD_ID_NZERO);
	emit sig_BinSetGridRowValue(STT_BINRECORD_ID_NZERO);
	DisConnectAll_SigSlot();
	m_pDatas->BringToHead(pCurr);
	ChangeRowPosition(STT_BINRECORD_ID_NZERO, nRow);
	SelectRow(1);
	ConnectAll_SigSlot();
	SetModifiedFlag(m_pDatas);
}

void QSttBinRecordSetGrid::MoveToBottom()
{
	CExBaseObject *pSel = (CExBaseObject*)GetCurrSelData(STT_BINRECORD_ID_NZERO);
	if (pSel == NULL)
	{
		return;
	}
	long nRow = GetDataRow(pSel);

	if (nRow < STT_BINRECORD_ID_NZERO)
	{
		return;
	}

	CExBaseObject *pBottom = GetData(GetRowCount() - STT_BINRECORD_ID_NONE, STT_BINRECORD_ID_NZERO);
	CExBaseObject *pCurr = GetData(nRow, STT_BINRECORD_ID_NZERO);
	emit sig_BinSetGridRowValue(GetRowCount() - STT_BINRECORD_ID_NONE);
	if (pCurr == pBottom)
	{
		return;
	}
	DisConnectAll_SigSlot();
	m_pDatas->BringToTail(pCurr);
	ChangeRowPosition(GetRowCount() - STT_BINRECORD_ID_NONE, nRow);
	SelectRow(GetRowCount());
	ConnectAll_SigSlot();
	SetModifiedFlag(m_pDatas);
}

void QSttBinRecordSetGrid::InitData()
{
	m_pDatas->SortByID();

	ShowDatas(m_pDatas);

}