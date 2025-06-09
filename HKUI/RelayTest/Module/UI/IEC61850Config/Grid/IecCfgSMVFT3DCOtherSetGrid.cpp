#include "IecCfgSMVFT3DCOtherSetGrid.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgSmvRate.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../Module/CommonMethod/commonMethod.h"
#include "../../SttTestCntrFrameBase.h"
#include "../../../XLangResource_Native.h"
#include "../../../SttSystemConfig/SttSystemConfig.h"
#include <QApplication>

CIecCfgSMVFT3DCOtherSetGrid::CIecCfgSMVFT3DCOtherSetGrid(QWidget* pparent, long nValueType):QExBaseListGridBase(pparent)
{
	m_nCodeValueGridType = nValueType;
	m_bRunning = false;
	installEventFilter(this);
}

CIecCfgSMVFT3DCOtherSetGrid::~CIecCfgSMVFT3DCOtherSetGrid()
{

}

void CIecCfgSMVFT3DCOtherSetGrid::InitGrid()
{
	InitGridTitle();
#ifdef _PSX_QT_LINUX_
	SetDefaultRowHeight(50);
#endif

	//	AutoAdjColWidth();
	SetEditable(TRUE);

	connect(this,SIGNAL(cellClicked(int,int)),this,SLOT(slot_doubleClicked(int,int)),Qt::UniqueConnection);
}

void CIecCfgSMVFT3DCOtherSetGrid::InitGridTitle()
{
	CString strName,strScaleFactor,strIECPrimtRatedType;
	xlang_GetLangStrByFile(strName,"sName");
	//xlang_GetLangStrByFile(strScaleFactor,"IEC_ScaleFactor");

	if(m_nCodeValueGridType == IECCFGSMV_DCFT3_DCVOL_GRID || m_nCodeValueGridType == IECCFGSMV_DCFT3_ACVOL_GRID
		|| m_nCodeValueGridType == IECCFGSMV_FT3_VOL_GRID)
	{ 
		if (g_oSttSystemConfig.GetFt3PrimCodeValue()) //chenling20240416 ADMU FT3码值
		{
			strIECPrimtRatedType = _T("二次额定电压(V)");
		}
		else
		{
		xlang_GetLangStrByFile(strIECPrimtRatedType,"IEC_PrimtRatedVol"); 
	}
	}
	else
	{
		if (g_oSttSystemConfig.GetFt3PrimCodeValue()) 
		{
			strIECPrimtRatedType = _T("二次额定电流(A)");
		}
	else
	{
		xlang_GetLangStrByFile(strIECPrimtRatedType,"IEC_PrimtRatedCur");
	}
	}

	CString astrGridTitle[IECCFGSMVFT3DCOTHERSET_GRID_COLS] = {strName,/*"码值"*/g_sLangTxt_Native_codesValue,strIECPrimtRatedType};
	int iGridWidth[IECCFGSMVFT3DCOTHERSET_GRID_COLS]={150, 150, 150};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, IECCFGSMVFT3DCOTHERSET_GRID_COLS);
}

void CIecCfgSMVFT3DCOtherSetGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != CFGCLASSID_CIECCFGSMVRATE)
	{
		return;
	}

	CIecCfgSmvRate *pIecCfgSmvRate = (CIecCfgSmvRate*)pData;
	CString strTempValue;
	strTempValue = pIecCfgSmvRate->m_strAliasName;

	if(m_nCodeValueGridType == IECCFGSMV_DCFT3_DCVOL_GRID)
	{
		if(pIecCfgSmvRate->IsDcFT3VolChsGroup() == FALSE)
	{
		return;
	}
	}
	if(m_nCodeValueGridType == IECCFGSMV_DCFT3_DCCUR_GRID)
	{
		if(pIecCfgSmvRate->IsDcFT3CurChsGroup() == FALSE)
	{
		return;
	}
	}
	if(m_nCodeValueGridType == IECCFGSMV_DCFT3_ACVOL_GRID)
	{
		if(pIecCfgSmvRate->IsAcFT3VolChsGroup() == FALSE)
	{
		return;
	}
	}
	if(m_nCodeValueGridType == IECCFGSMV_DCFT3_ACCUR_GRID)
	{
		if(pIecCfgSmvRate->IsAcFT3CurChsGroup() == FALSE)
	{
		return;
	}
	}
	if(m_nCodeValueGridType == IECCFGSMV_FT3_VOL_GRID)
	{
		if(pIecCfgSmvRate->IsVolChsGroup() == FALSE)
		{
			return;
		}
		else
		{
			strTempValue = pIecCfgSmvRate->m_strName;
		}
		
	}
	if(m_nCodeValueGridType == IECCFGSMV_FT3_CUR_GRID)
	{
		if(pIecCfgSmvRate->IsVolChsGroup() == TRUE)
		{
			return;
		}
		else
		{
			strTempValue = pIecCfgSmvRate->m_strName;
		}
	}

	Show_StaticString(pData,nRow,0,strTempValue);
	Show_Long(pData,nRow,1,&pIecCfgSmvRate->m_nCodeValue, TRUE,_T(""),EndEditCell_CodeValue);
	
	if ((g_oSttSystemConfig.GetFt3PrimCodeValue()) && (strTempValue.Find("U")!= -1))
	{
		pIecCfgSmvRate->m_fPrimValue = pIecCfgSmvRate->m_fPrimValue * 1000;
	}
		
	Show_Float(pData,nRow,2,3,&pIecCfgSmvRate->m_fPrimValue,1,EndEditCell_PrimValue);

	nRow++;
}


void CIecCfgSMVFT3DCOtherSetGrid::EndEditCell_CodeValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)//设置一次性额定电压最大最小值
{
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pString != NULL);

	long nValue =  math_GetValueFromString(pCell->text());

	if (nValue > 0 && nValue<= 999999)
	{
		*(pVCellData->pnValue) = nValue;
	}

	CString strTmp;
	strTmp.Format(_T("%d"), *(pVCellData->pnValue));								
	pCell->setText(strTmp);

	((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
}

void CIecCfgSMVFT3DCOtherSetGrid::EndEditCell_PrimValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)//cl20230906比列因子不能设置0
{
	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVCellData != NULL);
	ASSERT (pVCellData->pString != NULL);

	float fValue =  math_GetValueFromString(pCell->text());

	float fMaxValue ;
	CString strText = pGrid->item(nRow, nCol-2)->text();

	if ((g_oSttSystemConfig.GetFt3PrimCodeValue()) && (strText.Find("U")!= -1))
	{
		fMaxValue = 99999000;
	}
	else
	{
		fMaxValue = 99999;
	}

	if (fValue>0 && fValue <= fMaxValue)
	{
		*(pVCellData->pfValue) = fValue;
	}
	/*else
	{
		*(pVCellData->pfValue) = m_fv;
	}

	m_fv = fValue;*/

	CString strTmp;
	strTmp.Format(_T("%.3f"), *(pVCellData->pfValue));								
	pCell->setText(strTmp);

	((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
}

void CIecCfgSMVFT3DCOtherSetGrid::slot_doubleClicked( int nRow,int nCol )
{
// 	QTableWidgetItem *pItem = this->item(nRow,nCol);
	QGV_ITEM *pItem = GetCell(nRow,nCol);

	if (pItem == NULL)
	{
		return;
	}

	if (nCol != 1)
	{
		return;
	}

	QString strValue = pItem->text();
	
	GetWidgetBoard_DigitData(4, strValue,pItem, g_theTestCntrFrame);
// 	pItem->setText(strValue);

	/*
	WidgetKeyboard dlg(this);
	dlg.m_InputString = pItem->text();
	dlg.showToEdit();
	if (dlg.exec() == QDialog::Accepted)
	{
		pItem->setText(dlg.m_InputString);
	}
	*/
}



bool CIecCfgSMVFT3DCOtherSetGrid::eventFilter(QObject *obj, QEvent *event)
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

void CIecCfgSMVFT3DCOtherSetGrid::mousePressEvent(QMouseEvent * event)
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CIecCfgProtMaesCurrCodeSetGrid::CIecCfgProtMaesCurrCodeSetGrid(QWidget* pparent):CIecCfgSMVFT3DCOtherSetGrid(pparent,IECCFGSMV_FT3_CUR_PROT_MEAS_GRID)
{
}

CIecCfgProtMaesCurrCodeSetGrid::~CIecCfgProtMaesCurrCodeSetGrid()
{

}

void CIecCfgProtMaesCurrCodeSetGrid::InitGridTitle()
{
	CString strName,strProtCodeValue,strMeasCodeValue,strIECPrimtRatedType;
	xlang_GetLangStrByFile(strName,"sName");
	strProtCodeValue = /*"保护码值"*/g_sLangTxt_Native_Protection_CodeValue;
	strMeasCodeValue = /*"测量码值"*/g_sLangTxt_Native_Measure_CodeValue;

	//20240416chenling FT3订阅码值设置 ADMU
	if (g_oSttSystemConfig.GetFt3PrimCodeValue())
	{	
		strIECPrimtRatedType = /*_T("二次额定电流(A)")*/g_sLangTxt_Native_SecondaryCur;
	}
	else
	{
		xlang_GetLangStrByFile(strIECPrimtRatedType,"IEC_PrimtRatedCur");
	}

	CString astrGridTitle[IECCFGPROTMEASCURRCODE_GRID_COLS] = {strName,strProtCodeValue,strMeasCodeValue,strIECPrimtRatedType};
	int iGridWidth[IECCFGPROTMEASCURRCODE_GRID_COLS]={110, 120,120, 100};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, IECCFGPROTMEASCURRCODE_GRID_COLS);
}

void CIecCfgProtMaesCurrCodeSetGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != CFGCLASSID_CIECCFGSMVRATE)
	{
		return;
	}

	CIecCfgSmvRate *pIecCfgSmvRate = (CIecCfgSmvRate*)pData;

	if(pIecCfgSmvRate->IsVolChsGroup())
	{
		return;
	}

	Show_StaticString(pData,nRow,0,pIecCfgSmvRate->m_strName);
	Show_Long(pData,nRow,1,&pIecCfgSmvRate->m_nCodeValue, TRUE,_T(""),EndEditCell_CodeValue);
	Show_Long(pData,nRow,2,&pIecCfgSmvRate->m_nMeasCurrCodeValue, TRUE,_T(""),EndEditCell_CodeValue);
	Show_Float(pData,nRow,3,3,&pIecCfgSmvRate->m_fPrimValue,1,EndEditCell_PrimValue);
	nRow++;
}

void CIecCfgProtMaesCurrCodeSetGrid::slot_doubleClicked( int nRow,int nCol )
{
	QGV_ITEM *pItem = GetCell(nRow,nCol);

	if (pItem == NULL)
	{
		return;
	}

	if (nCol != 1)
	{
		return;
	}

	QString strValue = pItem->text();
	GetWidgetBoard_DigitData(4, strValue,pItem, g_theTestCntrFrame);
}


