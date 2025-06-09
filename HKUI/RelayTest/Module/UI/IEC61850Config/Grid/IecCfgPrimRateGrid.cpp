#include "IecCfgPrimRateGrid.h"
#include "../../Module/CommonMethod/commonMethod.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgPrimRate.h"
#include "../../../../../Module/API/MathApi.h"
#include "../../SttStyleSheetGlobalDefine.h"
#include "../../Module/XLangResource_Native.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include <QApplication>

CIecCfgPrimRateGrid::CIecCfgPrimRateGrid(long nGridType,QWidget *parent)
	: QExBaseListGridBase(parent)
{
	m_nGridType = nGridType;
	m_dMaxValue = 10000.f;
	m_dMinValue = 1;
	
	m_bRunning = FALSE;
	installEventFilter(this);
}

CIecCfgPrimRateGrid::~CIecCfgPrimRateGrid()
{

}

void CIecCfgPrimRateGrid::InitGrid()
{
	InitGridTitle();
#ifdef _PSX_QT_LINUX_
	SetDefaultRowHeight(50);
#endif
	//	AutoAdjColWidth();
	setStyleSheet(STT_StyleSheet_QTableWidgetItem_Enabled);

	connect(this,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(slot_doubleClicked(int,int)),Qt::UniqueConnection);
}

void CIecCfgPrimRateGrid::InitGridTitle()
{
	CString strType,strPrimDesc,strSecondDesc;
	//strType = _T("类型");

	if (m_nGridType == IECCFG_PRIMRATE_GRIDTYPE_PT)
	{
		strPrimDesc = _T("PT一次值(kV)");
		xlang_GetLangStrByFile(strPrimDesc,"IEC_PTOnce");
		strSecondDesc = _T("PT二次值(V)");
		xlang_GetLangStrByFile(strSecondDesc,"IEC_PTSecond");
	}
	else
	{
		strPrimDesc = _T("CT一次值(A)");
		xlang_GetLangStrByFile(strPrimDesc,"IEC_CTOnce");
		strSecondDesc = _T("CT二次值(A)");
		xlang_GetLangStrByFile(strSecondDesc,"IEC_CTSecond");
	}


	CString astrGridTitle[IECCFGPRIMRATE_GRID_COLS] = {g_sLangTxt_Native_Type,strPrimDesc,strSecondDesc};
	int iGridWidth[IECCFGPRIMRATE_GRID_COLS]={80, 145,145};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, IECCFGPRIMRATE_GRID_COLS);
}

void CIecCfgPrimRateGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != CFGCLASSID_CIECCFGPRIMRATE)
	{
		return;
	}

	CIecCfgPrimRate *pIecCfgPrimRate = (CIecCfgPrimRate*)pData;
	CString strType;

	if (m_nGridType == IECCFG_PRIMRATE_GRIDTYPE_PT)
	{
		strType.Format(_T("Uabc%ld"),nRow+1);
	} 
	else
	{
		strType.Format(_T("Iabc%ld"),nRow+1);
	}

	Show_StaticString(pData,nRow,0,&/*pIecCfgPrimRate->m_strName*/strType);
	Show_Double(pData,nRow,1,3,&pIecCfgPrimRate->m_fPrimValue,TRUE,EndEditCell_PrimrateDouble);
	Show_Double(pData,nRow,2,3,&pIecCfgPrimRate->m_fSecondValue,TRUE,EndEditCell_PrimrateDouble);
	nRow++;
}

CDataType* CIecCfgPrimRateGrid::FindDataType(const CString &strDataType)
{
	CDataType *pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(strDataType);

	return pDataType;
}

void CIecCfgPrimRateGrid::slot_doubleClicked( int nRow,int nCol )
{
	GridDoubleClicked_ShowKeyBoard(nRow,nCol);
	
}

void CIecCfgPrimRateGrid::GridDoubleClicked_ShowKeyBoard(int nRow,int nCol)
{
	if (nCol <= 0)
	{
		return;
	}

	QGV_ITEM *pItem = GetCell(nRow,nCol);

	if (pItem == NULL)
	{
		return;
	}

	QString strValue = pItem->text();
	GetWidgetBoard_DigitData(4,strValue,pItem, parentWidget()->parentWidget());

// 	double dValue = strValue.toDouble();
// 
// 	if (dValue<1)
// 	{
// 		dValue = 1.0f;
// 	}
// 
// 	if (dValue>10000)
// 	{
// 		dValue = 10000;
// 	}
// 
// 	strValue = QString::number(dValue, 'f', 3);
// 	pItem->setText(strValue);

}

bool CIecCfgPrimRateGrid::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent *pMouseEvent = (QMouseEvent *)event;
		m_bRunning = TRUE;
		mouseDoubleClickEvent((QMouseEvent *)pMouseEvent);
		m_bRunning = FALSE;
		return  true;
	}

	return QExBaseListGridBase::eventFilter(obj,event);

}

void CIecCfgPrimRateGrid::mousePressEvent(QMouseEvent * event)
{
	if (m_bRunning)
	{
		QExBaseListGridBase::mousePressEvent(event);
		return;
	}

	QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick,event->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
	QApplication::postEvent(this,pEvent);
	QExBaseListGridBase::mousePressEvent(event);

}

void CIecCfgPrimRateGrid::EndEditCell_PrimrateDouble (int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	CIecCfgPrimRateGrid *pOwnPrimRateGrid = (CIecCfgPrimRateGrid*)pGrid;
	PEXBASECELLDATA pVCellData = (EXBASECELLDATA*)pCell->lParam;
	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pnValue != NULL);
	ASSERT (pVCellData->nVt == VCD_LONG);
	ASSERT (pVCellData->pObj != NULL);
// 	CString strTmp = pCell->text();
// 	double dCurrValue = CString_To_double(strTmp);
// 
// 	if (dCurrValue<pOwnPrimRateGrid->m_dMinValue)
// 	{
// 		pCell->setText(QString::number(pOwnPrimRateGrid->m_dMinValue, 'f', 3));
// 	}
// 	else if (dCurrValue>pOwnPrimRateGrid->m_dMaxValue)
// 	{
// 		pCell->setText(QString::number(pOwnPrimRateGrid->m_dMaxValue, 'f', 3));
// 	}

	double dValue =  math_GetValueFromString(pCell->text());
	CString strTmp;

	if (fabs(dValue-*(pVCellData->pdValue)) > 0.00001)
	{
		*(pVCellData->pdValue) = dValue;

		if (dValue<pOwnPrimRateGrid->m_dMinValue)
		{
			dValue = pOwnPrimRateGrid->m_dMinValue;
	}
		else if (dValue>pOwnPrimRateGrid->m_dMaxValue)
	{
			dValue = pOwnPrimRateGrid->m_dMaxValue;
		}

		strTmp.Format(_T("%.03lf"), dValue);
		*(pVCellData->pdValue) = CString_To_double(strTmp);
		pCell->setText(strTmp);

		((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
	}

//	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pVellData->pObj;

// 	long nChNum = CString_To_long(strTmp);
// 	long nNewChNUm = 1;
// 
// 	if ((pIecCfgData->GetClassID() == CFGCLASSID_CIECCFGGOUTDATA)||(pIecCfgData->GetClassID() == CFGCLASSID_CIECCFGGINDATA))
// 	{
// 		nNewChNUm = iecfg_ValidateChsMiMax_GOOSE(nChNum);
// 	}
// 	else
// 	{
// 		nNewChNUm = iecfg_ValidateChsMiMax(nChNum);
// 	}
// 
// 	if (nChNum != nNewChNUm)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("通道数%d超出范围， 调整到%d"), nChNum, nNewChNUm);
// 	}
// 
// 	if (nNewChNUm == pIecCfgData->m_nChannelNum)
// 	{
// 		strTmp.Format(_T("%d"), pIecCfgData->m_nChannelNum);
// 		pCell->setText(strTmp);
// 		return;
// 	}
// 
// 	//在此对通道数量进行有效性验证
// 	pIecCfgData->m_nChannelNum = nNewChNUm;
// 	strTmp.Format(_T("%d"), nNewChNUm);
// 	pCell->setText(strTmp);
// 
// 	pIecCfgData->SetChannelNum(nNewChNUm);
}

