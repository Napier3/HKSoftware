#include "QSttBinRecordChsGrid.h"

#include "../../../UI/SttTestCntrFrameBase.h"
#include "../../SmartCap/61850Cap/CapDevice/CapDeviceRecord.h"

#include <iomanip>
#include "../SttBinRecordDefine.h"

QSttBinRecordChsGrid::QSttBinRecordChsGrid(QWidget *parent)
:QExBaseListGridBase(parent)
{
	m_pDelegEtype = NULL;
	m_pMeasGear = NULL;
	m_pChAngType = NULL;
	m_bRunning = false;
	
}

QSttBinRecordChsGrid::~QSttBinRecordChsGrid()
{

}

void QSttBinRecordChsGrid::InitGrid()
{
	InitComboBox();
	connect(this, SIGNAL(sig_BinRecordEtype(long, int, int)), this, SLOT(slot_BinRecordMeasGear(long, int, int)));
	InitGridTitle();
	verticalHeader()->setVisible(false);
	SetEditable(TRUE);


	if (m_pChAngType == NULL)
	{
		m_pChAngType = new QExBaseListComBoxDelegBase(this);
	}
	setItemDelegateForColumn(STT_BINRECORD_ID_NTWO, m_pChAngType);

	if (m_pDelegEtype == NULL)
	{
		m_pDelegEtype = new QExBaseListComBoxDelegBase(this);
	}
	setItemDelegateForColumn(STT_BINRECORD_ID_NTHREE, m_pDelegEtype);

	if (m_pMeasGear == NULL)
	{
		m_pMeasGear = new QExBaseListComBoxDelegBase(this);
	}
	setItemDelegateForColumn(STT_BINRECORD_ID_NFOUR, m_pMeasGear);
}

void QSttBinRecordChsGrid::InitGridTitle()
{
	CString astrGridTitle[QSTTTESTITEMGRIDCOL] = { g_sLangTxt_BinRecord_Channel, g_sLangTxt_Name, g_sLangTxt_Native_phaseDifference, g_sLangTxt_BinRecord_RecordType, g_sLangTxt_Native_Gear, g_sLangTxt_BinRecord_ClampRate + "(mV/A)", g_sLangTxt_Native_Threshold + "(V)" };
	int iColType[QSTTTESTITEMGRIDCOL] = { QT_GVET_NOEDIT, QT_GVET_NOEDIT, QT_GVET_COMBOBOX, QT_GVET_COMBOBOX, QT_GVET_COMBOBOX, QT_GVET_NOEDIT, QT_GVET_NOEDIT };
	int iGridWidth[QSTTTESTITEMGRIDCOL] = {80, 150, 90, 120, 115, 120, 110 };
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, QSTTTESTITEMGRIDCOL);
}

void QSttBinRecordChsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow /*= TRUE*/)
{
	ASSERT(pData);

	CCapDeviceRcdCh *pCh = (CCapDeviceRcdCh*)pData;
	CString strClampRate, strSwitchVolt;
	strClampRate.Format(_T("%.2f"), pCh->m_dClampRate);
	strSwitchVolt.Format(_T("%.2f"), pCh->m_fSwitchVolt);

	Show_StaticString(pData, nRow, STT_BINRECORD_ID_NZERO, pData->m_strName);
	Show_String(pData, nRow, STT_BINRECORD_ID_NONE, &pData->m_strName);

	Show_DataType_Val(pCh, nRow, STT_BINRECORD_ID_NTHREE, (CDataType*)m_oBinRcdDataTypes.FindByID(STT_BINRECORD_ID_ETYPEID), &pCh->m_nEType, EndEditCell_ComboBoxChanged);


	if (pCh->m_nEType == STT_BINRECORD_ID_NONE || pCh->m_nEType == STT_BINRECORD_ID_NTWO)
	{
		pCh->m_nChAngType = STT_BINRECORD_ID_NONE;
		Show_DataType_Val(pData, nRow, STT_BINRECORD_ID_NTWO, (CDataType*)m_oBinRcdDataTypes.FindByID(STT_BINRECORD_ID_CHANGTYPEID), &pCh->m_nChAngType);

		const char* pDataTypeID = (pCh->m_nEType == STT_BINRECORD_ID_NONE) ? STT_BINRECORD_ID_VOLTGEARID : STT_BINRECORD_ID_CURGEARID;
		CDataType* pDataType = (CDataType*)m_oBinRcdDataTypes.FindByID(pDataTypeID);
		Show_DataType_Val(pData, nRow, STT_BINRECORD_ID_NFOUR, pDataType, &pCh->m_nMeasGear, EndEditCell_GearComboBoxChanged);
	}
	else
	{
		pCh->m_nChAngType = STT_BINRECORD_ID_NZERO;
		Show_DataType_Val(pData, nRow, STT_BINRECORD_ID_NTWO, (CDataType*)m_oBinRcdDataTypes.FindByID(STT_BINRECORD_ID_CHANGTYPEID), &pCh->m_nChAngType);

		Show_StaticString(pData, nRow, STT_BINRECORD_ID_NFOUR, STT_BINRECORD_ID_SPACE);
	}

	if (pCh->m_nEType == STT_BINRECORD_ID_NTWO)
	{
		Show_String(pData, nRow, STT_BINRECORD_ID_NFIVE, &strClampRate, EndEditCell_ClampRateLineEditChanged);
	}
	else
	{
		Show_StaticString(pData, nRow, STT_BINRECORD_ID_NFIVE, STT_BINRECORD_ID_SPACE);
	}

	if (pCh->m_nEType == STT_BINRECORD_ID_NFOUR)
	{
		Show_Float(pData, nRow, STT_BINRECORD_ID_NSIX, STT_BINRECORD_ID_NTHREE, &pCh->m_fSwitchVolt, STT_BINRECORD_ID_NONE, EndEditCell_GearComboBoxChanged);
	}
	else
	{
		Show_StaticString(pData, nRow, STT_BINRECORD_ID_NSIX, STT_BINRECORD_ID_SPACE);
	}
	nRow++;
}

void QSttBinRecordChsGrid::InitComboBox()
{
	m_oBinRcdDataTypes.DeleteAll();   
	//记录类型
	CDataType *pEType = m_oBinRcdDataTypes.AddNew2(STT_BINRECORD_ID_ETYPE, STT_BINRECORD_ID_ETYPEID);
	pEType->AddNewValue(g_sLangTxt_BinRecord_Invalid, STT_BINRECORD_ID_INVALID, STT_BINRECORD_ID_STRZERO);
	pEType->AddNewValue(g_sLangTxt_Iec_Voltage, STT_BINRECORD_ID_VOL, STT_BINRECORD_ID_STRONE);
	pEType->AddNewValue(g_sLangTxt_Iec_Current, STT_BINRECORD_ID_CUR, STT_BINRECORD_ID_STRTWO);
	pEType->AddNewValue(g_sLangTxt_BinRecord_BinPassive, STT_BINRECORD_ID_BINPASSIVE, STT_BINRECORD_ID_STRTHREE);
	pEType->AddNewValue(g_sLangTxt_BinRecord_BinActive, STT_BINRECORD_ID_BINACTIVE, STT_BINRECORD_ID_STRFOUR);

	//记录类型 - 电压
	CDataType *VoltGear = m_oBinRcdDataTypes.AddNew2(STT_BINRECORD_ID_VOLTGEAR, STT_BINRECORD_ID_VOLTGEARID);
	VoltGear->AddNewValue(STT_BINRECORD_ID_STRSIXHUNDREDV, STT_BINRECORD_ID_VOLONE, STT_BINRECORD_ID_STRZERO);
	VoltGear->AddNewValue(STT_BINRECORD_ID_STRONETHOUSANDV, STT_BINRECORD_ID_VOLTWO, STT_BINRECORD_ID_STRONE);
	VoltGear->AddNewValue(STT_BINRECORD_ID_STRTENV, STT_BINRECORD_ID_VOLTHREE, STT_BINRECORD_ID_STRTWO);
	VoltGear->AddNewValue(STT_BINRECORD_ID_STRONEV, STT_BINRECORD_ID_VOLFOUR, STT_BINRECORD_ID_STRTHREE);
	VoltGear->AddNewValue(STT_BINRECORD_ID_STRZERODOTONEV, STT_BINRECORD_ID_VORFIVE, STT_BINRECORD_ID_STRFOUR);

	//记录类型 - 电流
	CDataType *CurGear = m_oBinRcdDataTypes.AddNew2(STT_BINRECORD_ID_CURGEAR, STT_BINRECORD_ID_CURGEARID);
	CurGear->AddNewValue(STT_BINRECORD_ID_STRSIXHUNDREDA, STT_BINRECORD_ID_CURONE, STT_BINRECORD_ID_STRZERO);
	CurGear->AddNewValue(STT_BINRECORD_ID_STRONETHOUSANDA, STT_BINRECORD_ID_CURTWO, STT_BINRECORD_ID_STRONE);
	CurGear->AddNewValue(STT_BINRECORD_ID_STRTENA, STT_BINRECORD_ID_CURTHREE, STT_BINRECORD_ID_STRTWO);
	CurGear->AddNewValue(STT_BINRECORD_ID_STRONEA, STT_BINRECORD_ID_CURFOUR, STT_BINRECORD_ID_STRTHREE);
	CurGear->AddNewValue(STT_BINRECORD_ID_STRZERODOTONEA, STT_BINRECORD_ID_CURFIVE, STT_BINRECORD_ID_STRFOUR);

	//相别
	CDataType *ChAngType = m_oBinRcdDataTypes.AddNew2(STT_BINRECORD_ID_CHANGTYPE, STT_BINRECORD_ID_CHANGTYPEID);
	ChAngType->AddNewValue(STT_BINRECORD_ID_SPACE, STT_BINRECORD_ID_CHANGONE, STT_BINRECORD_ID_STRZERO);
	ChAngType->AddNewValue(STT_BINRECORD_ID_STRA, STT_BINRECORD_ID_CHANGTWO, STT_BINRECORD_ID_STRONE);
	ChAngType->AddNewValue(STT_BINRECORD_ID_STRB, STT_BINRECORD_ID_CHANGTHREE, STT_BINRECORD_ID_STRTWO);
	ChAngType->AddNewValue(STT_BINRECORD_ID_STRC, STT_BINRECORD_ID_CHANGFOUR, STT_BINRECORD_ID_STRTHREE);
	ChAngType->AddNewValue(g_sLangTxt_Iec_ZeroSeq, STT_BINRECORD_ID_CHANGFIVE, STT_BINRECORD_ID_STRFOUR);
}

void QSttBinRecordChsGrid::EndEditCell_ComboBoxChanged(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	QSttBinRecordChsGrid *pOwnGrid = (QSttBinRecordChsGrid*)pGrid;

	if (pVCellData->pnValue != NULL)
	{
		long pnValue = *pVCellData->pnValue;
		emit pOwnGrid->sig_BinRecordEtype(pnValue, nRow, nCol);
	}
}


void QSttBinRecordChsGrid::EndEditCell_GearComboBoxChanged(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	QSttBinRecordChsGrid *pOwnGrid = (QSttBinRecordChsGrid*)pGrid;
	
	if (pVCellData->pnValue != NULL)
	{
		QTableWidgetItem* item = pOwnGrid->item(nRow, STT_BINRECORD_ID_NSIX);
		pOwnGrid->JudgCurOrVol(nRow);
		CCapDeviceRcdCh *pCh = (CCapDeviceRcdCh *)pOwnGrid->m_pDatas->GetAtIndex(nRow);
		float fValue;
		CString text;
		if (nCol == STT_BINRECORD_ID_NSIX)
		{
			text = item->text();
			int pos1 = text.Find(STT_BINRECORD_ID_SPACE);
			if (pos1 == STT_BINRECORD_ID_NZERO)
			{
				return;
			}
			else
			{
				fValue = CString_To_double(text);
				pCh->m_fSwitchVolt = fValue;
			}
		}
	}
}

void QSttBinRecordChsGrid::EndEditCell_ClampRateLineEditChanged(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	QSttBinRecordChsGrid *pOwnGrid = (QSttBinRecordChsGrid*)pGrid;

	if (pVCellData->pnValue != NULL)
	{
		QTableWidgetItem* item = pOwnGrid->item(nRow, STT_BINRECORD_ID_NFIVE);
		CCapDeviceRcdCh *pCh = (CCapDeviceRcdCh *)pOwnGrid->m_pDatas->GetAtIndex(nRow);
		float fValue;
		CString text;

		if (nCol == STT_BINRECORD_ID_NFIVE)
		{
			text = item->text();
			int pos1 = text.Find(STT_BINRECORD_ID_SPACE);
			if (pos1 == STT_BINRECORD_ID_NZERO)
			{
				return;
			}
			else
			{
				fValue = CString_To_double(text);
				pCh->m_dClampRate = fValue;
			}
			if (fValue <= STT_BINRECORD_ID_ONEHUNDRED && fValue > STT_BINRECORD_ID_NZERO)
			{
				pOwnGrid->ComputeGearValue(fValue, nRow, nCol);
				pCh->m_nMeasGear = STT_BINRECORD_ID_NFOUR;
				pOwnGrid->JudgCurOrVol(nRow);
			}
			else if (fValue <= STT_BINRECORD_ID_ONETHOUSAND && fValue != STT_BINRECORD_ID_NZERO)
			{
				pOwnGrid->ComputeGearValue(fValue, nRow, nCol);
				pCh->m_nMeasGear = STT_BINRECORD_ID_NTHREE;
				pOwnGrid->JudgCurOrVol(nRow);
			}
			else if (fValue <= STT_BINRECORD_ID_TENTHOUSAND && fValue != STT_BINRECORD_ID_NZERO)
			{
				pOwnGrid->ComputeGearValue(fValue, nRow, nCol);
				pCh->m_nMeasGear = STT_BINRECORD_ID_NTWO;
				pOwnGrid->JudgCurOrVol(nRow);
			}
			else if (fValue <= STT_BINRECORD_ID_HUNDREDTHOUSAND && fValue != STT_BINRECORD_ID_NZERO)
			{
				pOwnGrid->ComputeGearValue(fValue, nRow, nCol);
				pCh->m_nMeasGear = STT_BINRECORD_ID_NONE;
				pOwnGrid->JudgCurOrVol(nRow);
			}
			else if (fValue <= STT_BINRECORD_ID_SIXHUNDREDTHOUSAND && fValue != STT_BINRECORD_ID_NZERO)
			{
				pOwnGrid->ComputeGearValue(fValue, nRow, nCol);
				pCh->m_nMeasGear = STT_BINRECORD_ID_NZERO;
				pOwnGrid->JudgCurOrVol(nRow);
			}
			else
			{
				CString strText;
				fValue = setLimit(STT_BINRECORD_ID_NZERO, STT_BINRECORD_ID_SIXHUNDREDTHOUSAND, fValue);
				strText.Format(_T("%.2f"), fValue);
				pOwnGrid->Show_String(pCh, nRow, STT_BINRECORD_ID_NFIVE, &strText, EndEditCell_ClampRateLineEditChanged);
			}
		}
	}
}

void QSttBinRecordChsGrid::JudgCurOrVol(int nRow)
{
	CCapDeviceRcdCh *pCh = (CCapDeviceRcdCh *)m_pDatas->GetAtIndex(nRow);
	if (pCh->m_nEType == STT_BINRECORD_ID_NONE)    //1-电压
	{
		Show_DataType_Val(pCh, nRow, STT_BINRECORD_ID_NFOUR, (CDataType*)m_oBinRcdDataTypes.FindByID(STT_BINRECORD_ID_VOLTGEARID), &pCh->m_nMeasGear, EndEditCell_GearComboBoxChanged);
	}
	else if (pCh->m_nEType == STT_BINRECORD_ID_NTWO)//2-电流
	{
		Show_DataType_Val(pCh, nRow, STT_BINRECORD_ID_NFOUR, (CDataType*)m_oBinRcdDataTypes.FindByID(STT_BINRECORD_ID_CURGEARID), &pCh->m_nMeasGear, EndEditCell_GearComboBoxChanged);
	}
}

void QSttBinRecordChsGrid::slot_BinRecordMeasGear(long nValue, int nRow, int nCol)
{
	CCapDeviceRcdCh *pCh = (CCapDeviceRcdCh *)m_pDatas->GetAtIndex(nRow);
	pCh->m_nChAngType = STT_BINRECORD_ID_NONE;
	if (pCh->m_nEType == STT_BINRECORD_ID_NONE)
	{
		Show_DataType_Val(pCh, nRow, STT_BINRECORD_ID_NTWO, (CDataType*)m_oBinRcdDataTypes.FindByID(STT_BINRECORD_ID_CHANGTYPEID), &pCh->m_nChAngType);
		Show_DataType_Val(pCh, nRow, STT_BINRECORD_ID_NFOUR, (CDataType*)m_oBinRcdDataTypes.FindByID(STT_BINRECORD_ID_VOLTGEARID), &pCh->m_nMeasGear, EndEditCell_GearComboBoxChanged);
	}
	else if (pCh->m_nEType == STT_BINRECORD_ID_NTWO)
	{

		Show_DataType_Val(pCh, nRow, STT_BINRECORD_ID_NTWO, (CDataType*)m_oBinRcdDataTypes.FindByID(STT_BINRECORD_ID_CHANGTYPEID), &pCh->m_nChAngType);
		Show_DataType_Val(pCh, nRow, STT_BINRECORD_ID_NFOUR, (CDataType*)m_oBinRcdDataTypes.FindByID(STT_BINRECORD_ID_CURGEARID), &pCh->m_nMeasGear, EndEditCell_GearComboBoxChanged);
	}
	else
	{
		pCh->m_nChAngType = STT_BINRECORD_ID_NZERO;
		Show_DataType_Val(pCh, nRow, STT_BINRECORD_ID_NTWO, (CDataType*)m_oBinRcdDataTypes.FindByID(STT_BINRECORD_ID_CHANGTYPEID), &pCh->m_nChAngType);
		Show_StaticString(pCh, nRow, STT_BINRECORD_ID_NFOUR, STT_BINRECORD_ID_SPACE);
	}

	CString strTest;
	strTest.Format(_T("%.2f"), pCh->m_dClampRate);
	if (pCh->m_nEType == STT_BINRECORD_ID_NTWO)
	{
		Show_String(pCh, nRow, STT_BINRECORD_ID_NFIVE, &strTest, EndEditCell_ClampRateLineEditChanged);
	}
	else
	{
		Show_StaticString(pCh, nRow, STT_BINRECORD_ID_NFIVE, STT_BINRECORD_ID_SPACE);
	}

	if (pCh->m_nEType == STT_BINRECORD_ID_NFOUR)
	{
		Show_Float(pCh, nRow, STT_BINRECORD_ID_NSIX, STT_BINRECORD_ID_NTHREE, &pCh->m_fSwitchVolt);
	}
	else
	{
		Show_StaticString(pCh, nRow, STT_BINRECORD_ID_NSIX, STT_BINRECORD_ID_SPACE);
	}

}

void QSttBinRecordChsGrid::ComputeGearValue(float fValue, int nRow, int nCol)
{
	if (nCol == STT_BINRECORD_ID_NFIVE)
	{
	float fInitFirstGear, fInitSecondGear, fInitThreeGear, fInitFourGear, fInitFiveGear;
	fInitFirstGear = STT_BINRECORD_ID_FSIXHUNDRED;
	fInitSecondGear = STT_BINRECORD_ID_FONETHOUSAND;
	fInitThreeGear = STT_BINRECORD_ID_FTEN;
	fInitFourGear = STT_BINRECORD_ID_FONE;
	fInitFiveGear = STT_BINRECORD_ID_FZERODOTONE;

	float fCurValue = fValue / STT_BINRECORD_ID_ONETHOUSAND;

	float fOneGear, fTwoGear, fThreeGear, fFourGear, fFiveGear;
			fOneGear = fInitFirstGear / fCurValue;
	fTwoGear = fInitSecondGear / fCurValue;
	fThreeGear = fInitThreeGear / fCurValue;
	fFourGear = fInitFourGear / fCurValue;
	fFiveGear = fInitFiveGear / fCurValue;

	CString strOne = FormatFloat(fOneGear);
	CString strTwo = FormatFloat(fTwoGear);
	CString strThree = FormatFloat(fThreeGear);
	CString strFour = FormatFloat(fFourGear);
	CString strFive = FormatFloat(fFiveGear);

	CCapDeviceRcdCh *pCh = (CCapDeviceRcdCh *)m_pDatas->GetAtIndex(nRow);
	if (pCh->m_nEType == STT_BINRECORD_ID_NONE)
	{
		CDataType *VoltGear = (CDataType*)m_oBinRcdDataTypes.FindByID(STT_BINRECORD_ID_VOLTGEARID);   //电压
		CDataType *VoltGear1 = (CDataType*)VoltGear->FindByID(STT_BINRECORD_ID_VOLONE);
		CDataType *VoltGear2 = (CDataType*)VoltGear->FindByID(STT_BINRECORD_ID_VOLTWO);
		CDataType *VoltGear3 = (CDataType*)VoltGear->FindByID(STT_BINRECORD_ID_VOLTHREE);
		CDataType *VoltGear4 = (CDataType*)VoltGear->FindByID(STT_BINRECORD_ID_VOLFOUR);
		CDataType *VoltGear5 = (CDataType*)VoltGear->FindByID(STT_BINRECORD_ID_VORFIVE);
	}
	else if (pCh->m_nEType == STT_BINRECORD_ID_NTWO)
	{
		CDataType *CurGear = (CDataType*)m_oBinRcdDataTypes.FindByID(STT_BINRECORD_ID_CURGEARID);   //电流
		CDataType *CurGear1 = (CDataType*)CurGear->FindByID(STT_BINRECORD_ID_CURONE);
		CDataType *CurGear2 = (CDataType*)CurGear->FindByID(STT_BINRECORD_ID_CURTWO);
		CDataType *CurGear3 = (CDataType*)CurGear->FindByID(STT_BINRECORD_ID_CURTHREE);
		CDataType *CurGear4 = (CDataType*)CurGear->FindByID(STT_BINRECORD_ID_CURFOUR);
		CDataType *CurGear5 = (CDataType*)CurGear->FindByID(STT_BINRECORD_ID_CURFIVE);
		CurGear1->m_strName = strOne + STT_BINRECORD_ID_STRA;
		CurGear2->m_strName = strTwo + STT_BINRECORD_ID_STRA;
		CurGear3->m_strName = strThree + STT_BINRECORD_ID_STRA;
		CurGear4->m_strName = strFour + STT_BINRECORD_ID_STRA;
		CurGear5->m_strName = strFive + STT_BINRECORD_ID_STRA;
	}
	}
}

CString QSttBinRecordChsGrid::FormatFloat(float fValue)
{
	CString strResult;
	if (fValue < STT_BINRECORD_ID_FONE)
	{
		strResult.Format("%.3f", fValue);    //小于1 取三位小数
	}
	else
	{
		strResult.Format("%d", (int)fValue); 
	}
	return strResult;
}

bool QSttBinRecordChsGrid::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent *pMouseEvent = (QMouseEvent *)event;
		m_bRunning = TRUE;
		mouseDoubleClickEvent((QMouseEvent *)pMouseEvent);
		m_bRunning = FALSE;
		return  true;
	}

	return QExBaseListGridBase::eventFilter(obj, event);

}

void QSttBinRecordChsGrid::mousePressEvent(QMouseEvent * event)
{
	if (m_bRunning)
	{
		QExBaseListGridBase::mousePressEvent(event);
		return;
	}

	QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick, event->pos(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
	QApplication::postEvent(this, pEvent);
	QExBaseListGridBase::mousePressEvent(event);

}