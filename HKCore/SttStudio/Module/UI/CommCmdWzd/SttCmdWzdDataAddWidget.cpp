#include "SttCmdWzdDataAddWidget.h"
#include "ui_SttCmdWzdDataAddWidget.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../../SttGlobalDef.h"
#include "../SttTestCntrFrameBase.h"
#include "SettingZoneComboBox.h"

#include "../../../../Module/BaseClass/QT/ExBaseListComboBox.h"

#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"

#include "../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"


extern CGbSmartGenWzd *g_theGbSmartGenWzd;

extern QFont *g_pSttGlobalFont;  //2022-9-16  lijunqing

void QSttCmdWzdDataAddWidget::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{
	CDvmData *pData = (CDvmData*)m_pEditGrid->GetData(nRow, 1);
	EnableInsertBtn(pData);
	//ui->m_btnInsertData->setEnabled(pData != NULL);
}

BOOL QSttCmdWzdDataAddWidget::OnEditCellLBDblClk(QTableWidget *pGridCtrl, int nRow, int nCol, UINT nChar)
{
	CDvmData *pData = (CDvmData*)m_pEditGrid->GetData(nRow, 1);
	emit sig_CmdWzd_AddData(pData);
	return TRUE;
}

QSttCmdWzdDataAddWidget::QSttCmdWzdDataAddWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSttCmdWzdDataAddWidget)
{
    ui->setupUi(this);

	xlang_SetLangStrToWidget_Txt(ui->m_btnInsertData,g_sLangTxt_Native_InsData,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->m_btnClose,g_sLangTxt_Close,XLang_Ctrls_QPushButton);

	setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
	m_pEditGrid = new CSttCmdWzdDsShowGrid(this);
	m_pEditGrid->setSelectionMode(QAbstractItemView::MultiSelection);
	m_pEditGrid->InitGrid();
	m_pEditGrid->AttachDataViewOptrInterface(this);
	ui->verticalLayout->insertWidget(0, m_pEditGrid);

	ui->m_btnInsertData->setEnabled(false);
	m_pCommCmdRef = NULL;

	UI_SetFont();
}

QSttCmdWzdDataAddWidget::~QSttCmdWzdDataAddWidget()
{
    delete ui;
}


void QSttCmdWzdDataAddWidget::UI_SetFont()
{
	ui->m_btnInsertData->setFont(*g_pSttGlobalFont);
 	ui->m_btnClose->setFont(*g_pSttGlobalFont);
}

void QSttCmdWzdDataAddWidget::EnableInsertBtn(CExBaseObject *pData)
{
	CSttCommCmdData *pSttCmdData = m_pCommCmdRef->GetCommCmdData(TRUE);
	CValue *pValue = (CValue*)pSttCmdData->FindByID(pData->m_strID);

	if (pValue != NULL)
	{
		ui->m_btnInsertData->setEnabled(false);
		return;
	}

	ui->m_btnInsertData->setEnabled(true);
}

void QSttCmdWzdDataAddWidget::ShowDataset(CDvmDataset *pDataset)
{
	m_pEditGrid->ShowDatas(pDataset);
}

void QSttCmdWzdDataAddWidget::on_m_btnInsertData_clicked()
{
 	CDvmData *pData = (CDvmData*)m_pEditGrid->GetCurrSelData(1);
 	emit sig_CmdWzd_AddData(pData);
// 	CExBaseList oList;
// 	m_pEditGrid->GetCurrSelDatas(oList, 1);
// 
// 	POS pos = oList.GetHeadPosition();
// 
// 	while (pos != NULL)
// 	{
// 		CDvmData *pData = (CDvmData*)oList.GetNext(pos);
// 
// 		emit sig_CmdWzd_AddData(pData);
// 	}
// 
// 	oList.RemoveAll();
}

void QSttCmdWzdDataAddWidget::on_m_btnClose_clicked()
{
	close();
}
