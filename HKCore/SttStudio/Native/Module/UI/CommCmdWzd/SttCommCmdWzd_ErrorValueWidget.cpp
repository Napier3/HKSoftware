#include "SttCommCmdWzd_ErrorValueWidget.h"
#include "ui_SttCommCmdWzd_ErrorValueWidget.h"
#include "../../../../Module/BaseClass/QT/ExBaseListComboBox.h"
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
#include "../../../../Module/API/MathApi.h"
#include <QHeaderView>

#include "../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"


extern CGbSmartGenWzd *g_theGbSmartGenWzd;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
QSttCommCmdWzd_ErrorValueGrid_StateTest::QSttCommCmdWzd_ErrorValueGrid_StateTest(QWidget* pparent):QExBaseListGridBase(pparent)
{

}

QSttCommCmdWzd_ErrorValueGrid_StateTest::~QSttCommCmdWzd_ErrorValueGrid_StateTest()
{

}

void QSttCommCmdWzd_ErrorValueGrid_StateTest::InitGrid()
{
 	QExBaseListGridBase::InitGrid();
	m_pSelect = new QExBaseListCheckBoxDelegate(this);
	setItemDelegateForColumn(0,m_pSelect);
}

void QSttCommCmdWzd_ErrorValueGrid_StateTest::InitGridTitle()
{
	CString astrGridTitle[5] = {/*"选择"*/g_sLangTxt_Select, /*"名称"*/g_sLangTxt_Name, /*"相对误差(%)"*/g_sLangTxt_StateEstimate_RelError+"(%)", /*"绝对误差(s)"*/g_sLangTxt_StateEstimate_AbsError+"(%)", ""};
	int iGridWidth[5]={40, 200, 90, 90, 10};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 5);
}

void QSttCommCmdWzd_ErrorValueGrid_StateTest::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	DisConnectAll_SigSlot();
	m_pCurrData = NULL;

	if (pDatas == NULL)
	{
		SetRowCount(0);
		return;
	}

	m_pDatas = pDatas;
	CDataGroup *pRsltEvalute = NULL;	
	POS pos = pDatas->GetHeadPosition();
	int nRowIndex = 0;//zhouhj Qt中不包括标题行
	long nCalRows = GetDatasCount();//zhouhj Qt中不包括标题行
	SetRowCount(nCalRows, bResetScrollBars);

	while (pos != NULL)
	{
		pRsltEvalute = (CDataGroup *)pDatas->GetNext(pos);
		ShowData(pRsltEvalute, nRowIndex, FALSE);
	}

	SetRowCount(nRowIndex, bResetScrollBars);
	AfterShowDatas(1, bResetScrollBars);
}

void QSttCommCmdWzd_ErrorValueGrid_StateTest::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDataGroup *pRsltEvalute = (CDataGroup *)pData;
	CString strName = /*_T("动作时间")*/g_sLangTxt_Gradient_ActionTime;
	CString strIndex;
	strIndex.Format(_T("%d"), nRow + 1);
	strName += strIndex;
	CDvmData *pDvmData = (CDvmData *)pRsltEvalute->FindByID(_T("UseError"));
	pDvmData->m_nChange = CString_To_long(pDvmData->m_strValue);

	Show_Check(pDvmData, nRow, 0, &pDvmData->m_nChange, EndEditCell_Select); 
	Show_StaticString(pDvmData, nRow, 1, &strName);

	float dValue = 0;
	pDvmData = (CDvmData *)pRsltEvalute->FindByID(_T("ActT_RelErr"));
	dValue = CString_To_double(pDvmData->m_strValue);
	Show_Float(pDvmData, nRow, 2, 3, &dValue, TRUE, EndEditCell_RelError);

	pDvmData = (CDvmData *)pRsltEvalute->FindByID(_T("ActT_AbsErr"));
	Show_String(pDvmData, nRow, 3, &pDvmData->m_strValue);

	nRow++;
}

void QSttCommCmdWzd_ErrorValueGrid_StateTest::EndEditCell_Select(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);

	CDvmData *pData = (CDvmData *)pVCellData->pObj;
	pData->m_strValue.Format(_T("%d"), pData->m_nChange);
}

void QSttCommCmdWzd_ErrorValueGrid_StateTest::EndEditCell_RelError(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);
	float fValue =  math_GetValueFromString(pCell->text());

	if (fabs(fValue-*(pVCellData->pfValue) ) > 0.00001)
	{
		*(pVCellData->pfValue) = fValue;
		long nPrecision = (pCell->dwValue >> 16) & 0xFFFF;
		ASSERT(nPrecision == 3);

		if (nPrecision > 0 )
		{
			CString strFormat, strTmp;
			strFormat.Format(_T("%%.%df"), nPrecision);
			strTmp.Format(strFormat.GetString(), *(pVCellData->pfValue));
			pCell->setText(strTmp);

			CDvmData *pData = (CDvmData*)pVCellData->pObj;
			pData->m_strValue.Format(_T("%.4f"), fValue);
		}	
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
QSttCommCmdWzd_ErrorValueWidget::QSttCommCmdWzd_ErrorValueWidget(QFont font, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSttCommCmdWzd_ErrorValueWidget)
{
    ui->setupUi(this);
	InitLanguage();
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	InitUI();
	UI_SetFont(font);
}

void QSttCommCmdWzd_ErrorValueWidget::InitLanguage()
{	
//	ui->tableWidget->clearHorizontalHeaderLabels();
	QStringList labels; 
	labels << g_sLangTxt_Native_ErrName << g_sLangTxt_Native_ErrValue << g_sLangTxt_Native_modifyto; 
	ui->tableWidget->setHorizontalHeaderLabels(labels);
}

QSttCommCmdWzd_ErrorValueWidget::~QSttCommCmdWzd_ErrorValueWidget()
{
    delete ui;
}

void QSttCommCmdWzd_ErrorValueWidget::UI_SetFont(QFont font)
{

}

void QSttCommCmdWzd_ErrorValueWidget::InitUI()
{
	QHeaderView* pHeadTop = ui->tableWidget->horizontalHeader();
#ifndef _PSX_QT_LINUX_
	pHeadTop->setClickable(false);
	pHeadTop->setMovable(false);
#endif
	QHeaderView* pHeadLeft = ui->tableWidget->verticalHeader();

	ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
	ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");

	m_pGridStateTest = new QSttCommCmdWzd_ErrorValueGrid_StateTest(this);
	m_pGridStateTest->InitGrid();
	m_pGridStateTest->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_pGridStateTest->hide();

	ui->verticalLayout->insertWidget(0,m_pGridStateTest);
}

void QSttCommCmdWzd_ErrorValueWidget::ShowDatas(CDataGroup* pDataGroup)
{
	if (m_strTestMacroID == STT_CMD_ATS_MACRO_ID_StateTest)
	{
		ui->tableWidget->hide();
		m_pGridStateTest->show();
		m_pGridStateTest->ShowDatas(pDataGroup);
		return;
	}

	m_pGridStateTest->hide();
	ui->tableWidget->show();

	long nIndex = 0;
	ui->tableWidget->setRowCount(pDataGroup->GetCount());
	POS pos = pDataGroup->GetHeadPosition();
	while (pos)
	{
		CDvmData* pData = (CDvmData*)pDataGroup->GetNext(pos);
		QTableWidgetItem* pItem = new QTableWidgetItem;
		pItem->setText(pData->m_strName);
		pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
		ui->tableWidget->setItem(nIndex, 0, pItem);

		pItem = new QTableWidgetItem;
		pItem->setText(pData->m_strValue);
		pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
		ui->tableWidget->setItem(nIndex, 1, pItem);

		pItem = new QTableWidgetItem;
		pItem->setText(pData->m_strValue);
		ui->tableWidget->setItem(nIndex, 2, pItem);

		nIndex++;
	}
}

void QSttCommCmdWzd_ErrorValueWidget::FinishEditDatas(CDataGroup* pDataGroup)
{
	if (m_strTestMacroID == STT_CMD_ATS_MACRO_ID_StateTest)
	{
		//已经在表格编辑的回调函数中处理了
		return;
	}

	long nIndex = 0;
	POS pos = pDataGroup->GetHeadPosition();
	while (pos)
	{
		CDvmData* pData = (CDvmData*)pDataGroup->GetNext(pos);
		QTableWidgetItem* pItem = ui->tableWidget->item(nIndex, 2);
		pData->m_strValue = pItem->text();
		nIndex++;
	}
}

void QSttCommCmdWzd_ErrorValueWidget::resizeEvent(QResizeEvent *event)
{
	QRect rc = geometry();
	long nWidth = rc.width() / 5;
	ui->tableWidget->setColumnWidth(0, nWidth * 2.5);
	ui->tableWidget->setColumnWidth(1, nWidth);
	ui->tableWidget->setColumnWidth(2, nWidth);
}