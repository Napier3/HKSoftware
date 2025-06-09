#include "QRecloseResultAssessDlg.h"
#include <QHeaderView>
#include "../../Module/SttGlobalDef.h"
#include <QTableWidget>
#include <QVBoxLayout>
#include <QTableView>
#include <QCheckBox>
#include <QComboBox>
#include <QSpinBox>
#include "../../UI/Module/CommonMethod/commonMethod.h"
#include "../../UI/SttTestCntrFrameBase.h"
#include "../../HtmlReport/SttXHtmlRptGenFactoryBase.h"
#include "SttMultiMacroRecloseAccParasDefine.h"

//#ifdef _PSX_QT_WINDOWS_
#include <QApplication>
#include <QDesktopWidget>
#include <QRect>
//#endif
QRecloseResultAssessDlg::QRecloseResultAssessDlg(CDataGroup *m_oRecloseAccDataGroup,QWidget *parent) : QDialog(parent)
{

	m_pRecloseResultAssessDataGroup = m_oRecloseAccDataGroup;
	InitUI();
	InitFont();
	InitConnections();
}

QRecloseResultAssessDlg::~QRecloseResultAssessDlg()
{

}

void QRecloseResultAssessDlg::InitUI()
{
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
	m_pResultTableWidget = new QTableWidget(/*3*/1, 5, this);

	QDesktopWidget* desktopWidget = QApplication::desktop();
	QRect rect = desktopWidget->screenGeometry();
	if (rect.height() == 1400)
	{
		m_pResultTableWidget->setMinimumSize(800, /*200*/150);
	}
	else
	{
		m_pResultTableWidget->setMinimumSize(700, /*150*/100); // 设置固定大小
	}
//#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
//    m_pResultTableWidget->horizontalHeader()->setSectionsClickable(false);
//    m_pResultTableWidget->horizontalHeader()->setSectionsMovable(false);
//#else
//    m_pResultTableWidget->horizontalHeader()->setClickable(false);
//	m_pResultTableWidget->horizontalHeader()->setMovable(false);
//#endif

	QStringList headers;
	headers << /*"名称"*/g_sLangTxt_Name << /*"误差类型"*/g_sLangTxt_StateEstimate_ErrorType <</* "相对误差(%)"*/g_sLangTxt_StateEstimate_RelError_Percent << /*"绝对误差"*/g_sLangTxt_StateEstimate_AbsError << g_sLangTxt_StateEstimate_AbsError_Neg;
	m_pResultTableWidget->setHorizontalHeaderLabels(headers);
	m_pResultTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background: skyblue;}"); // 设置表头背景色
	m_pResultTableWidget->setStyleSheet("selection-background-color: grey;selection-color: black");
	m_pResultTableWidget->verticalHeader()->setVisible(false);
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
	m_pResultTableWidget->horizontalHeader()->setSectionsClickable(false);
#else
	m_pResultTableWidget->horizontalHeader()->setClickable(false);
#endif

	//m_pResultTableWidget->resizeColumnsToContents(); // 根据内容调整列宽
	//m_pResultTableWidget->setColumnWidth(0, 200);
	//for (int col = 1; col < 4; ++col) 
	//{
	//	m_pResultTableWidget->setColumnWidth(col, 120); 
	//}
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
	m_pResultTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#else
	m_pResultTableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
#endif
	m_pResultTableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); 

	
//#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
//    m_pResultTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed); // 设置固定列宽
//    m_pResultTableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed); // 设置固定行高
//#else
//    m_pResultTableWidget->horizontalHeader()->setResizeMode(QHeaderView::Fixed); // 设置固定列宽
//	m_pResultTableWidget->verticalHeader()->setResizeMode(QHeaderView::Fixed); // 设置固定行高
//#endif

	//m_pLabActionTime = new QLabel(CString("跳闸")/*"动作时间(s)"*/+ g_sLangTxt_Native_ActionTime);
	//m_pResultTableWidget->setCellWidget(0, 0, m_pLabActionTime);

	m_pLabTripTime = new QLabel(/*"重合闸动作时间(s)"*/g_sLangTxt_Native_RecloseTime + "(s)");
	m_pResultTableWidget->setCellWidget(/*1*/0, 0, m_pLabTripTime);

	//m_pLabAccTime = new QLabel(/*"后加速动作时间(s)"*/g_sLangTxt_Native_PostAccTime + "(s)");
	//m_pResultTableWidget->setCellWidget(2, 0, m_pLabAccTime);

	//m_pLabActionTime->setAlignment(Qt::AlignCenter);
	//m_pLabTripTime->setAlignment(Qt::AlignCenter);
	//m_pLabAccTime->setAlignment(Qt::AlignCenter);

	//m_pCmbActionTime = new QComboBox();
    m_pCmbTtripTime = new CExBaseListComboBox(this);
	//m_pCmbAccTime = new QComboBox();

    CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_ERRTYPE);
    m_pCmbTtripTime->ShowBaseList(pDataType);
	//m_pCmbAccTime->addItems(headers1);
	//m_pResultTableWidget->setCellWidget(0, 1, m_pCmbActionTime);
	m_pResultTableWidget->setCellWidget(0, 1, m_pCmbTtripTime);
	//m_pResultTableWidget->setCellWidget(2, 1, m_pCmbAccTime);
	m_pResultTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pMainLayout = new QVBoxLayout(this);
	m_pMainLayout->addWidget(m_pResultTableWidget);
	m_pButtonLayout = new QHBoxLayout();
	m_pBtnOK = new QPushButton(/*"确定"*/g_sLangTxt_OK, this);
	m_pBtnCancel = new QPushButton(/*"取消"*/g_sLangTxt_Cancel, this);
	m_pButtonLayout->addWidget(m_pBtnOK);
	m_pButtonLayout->addWidget(m_pBtnCancel);
	m_pButtonLayout->setAlignment(Qt::AlignCenter);
	m_pMainLayout->addLayout(m_pButtonLayout);

	m_pResultTableWidget->viewport()->installEventFilter(this);
	setLayout(m_pMainLayout);
	UpdataResultAssess();

	long nValue = m_pCmbTtripTime->currentIndex();
	slot_CmbTtripTimeCurrentIndex(nValue);
}

void QRecloseResultAssessDlg::InitFont()
{
	//m_pCmbActionTime->setFont(*g_pSttGlobalFont);
	m_pCmbTtripTime->setFont(*g_pSttGlobalFont);
	//m_pCmbAccTime->setFont(*g_pSttGlobalFont);
	m_pResultTableWidget->setFont(*g_pSttGlobalFont);
	m_pResultTableWidget->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pBtnOK->setFont(*g_pSttGlobalFont);
	m_pBtnCancel->setFont(*g_pSttGlobalFont);
	//m_pLabActionTime->setFont(*g_pSttGlobalFont);
	m_pLabTripTime->setFont(*g_pSttGlobalFont);
	//m_pLabAccTime->setFont(*g_pSttGlobalFont);
}

void QRecloseResultAssessDlg::slot_btnOK_Clicked()
{
//	long nActionTime = m_pCmbActionTime->currentIndex();

//	long nAccTime = m_pCmbAccTime->currentIndex();

//	long nTtripRelErr = m_pResultTableWidget->item(0, 2)->text().toFloat();
//	float fTtripAbsErr = m_pResultTableWidget->item(0, 3)->text().toFloat();
//	float fTtripAbsErrMinus = m_pResultTableWidget->item(0, 4)->text().toFloat();

	long nTtripDRelErr = m_pResultTableWidget->item(/*1*/0, 2)->text().toFloat();
	float fTtripDAbsErr = m_pResultTableWidget->item(/*1*/0, 3)->text().toFloat();
	float fTtripDAbsErrMinus = m_pResultTableWidget->item(/*1*/0, 4)->text().toFloat();

//	long nTtripAccRelErr = m_pResultTableWidget->item(2, 2)->text().toFloat();
//	float fTtripAccAbsErr = m_pResultTableWidget->item(2, 3)->text().toFloat();
//	float fTtripAccAbsErrMinus = m_pResultTableWidget->item(2, 4)->text().toFloat();

	CDvmData *pData = NULL;
	/*pData = (CDvmData *)m_pRecloseResultAssessDataGroup->FindByID("Ttrip_RelErr");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nTtripRelErr);
		m_pItem1 = new QTableWidgetItem(QString::number(nTtripRelErr));
		m_pItem1->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(0, 2, m_pItem1);
	}


	pData = (CDvmData *)m_pRecloseResultAssessDataGroup->FindByID("Ttrip_AbsErr");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(fTtripAbsErr, 'f', 2);
		m_pItem2 = new QTableWidgetItem(QString::number(fTtripAbsErr, 'f', 2));
		m_pItem2->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(0, 3, m_pItem2);
	}

	pData = (CDvmData *)m_pRecloseResultAssessDataGroup->FindByID("Ttrip_AbsErrMinus");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(fTtripAbsErrMinus, 'f', 2);
		m_pItem10 = new QTableWidgetItem(QString::number(fTtripAbsErrMinus, 'f', 2));
		m_pItem10->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(0, 4, m_pItem10);
	}*/


	pData = (CDvmData *)m_pRecloseResultAssessDataGroup->FindByID("TtripD_RelErr");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nTtripDRelErr);
		m_pItem4 = new QTableWidgetItem(QString::number(nTtripDRelErr));
		m_pItem4->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(/*1*/0, 2, m_pItem4);
	}

	pData = (CDvmData *)m_pRecloseResultAssessDataGroup->FindByID("TtripD_AbsErr");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(fTtripDAbsErr, 'f', 2);
		m_pItem5 = new QTableWidgetItem(QString::number(fTtripDAbsErr, 'f', 2));
		m_pItem5->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(/*1*/0, 3, m_pItem5);
	}

	pData = (CDvmData *)m_pRecloseResultAssessDataGroup->FindByID("TtripD_AbsErrMinus");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(fTtripDAbsErrMinus, 'f', 2);
		m_pItem11 = new QTableWidgetItem(QString::number(fTtripDAbsErrMinus, 'f', 2));
		m_pItem11->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(/*1*/0, 4, m_pItem11);
	}

	/*pData = (CDvmData *)m_pRecloseResultAssessDataGroup->FindByID("TtripAcc_RelErr");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nTtripAccRelErr);
		m_pItem7 = new QTableWidgetItem(QString::number(nTtripAccRelErr));
		m_pItem7->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(2, 2, m_pItem7);
	}

	pData = (CDvmData *)m_pRecloseResultAssessDataGroup->FindByID("TtripAcc_AbsErr");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(fTtripAccAbsErr, 'f', 2);
		m_pItem8 = new QTableWidgetItem(QString::number(fTtripAccAbsErr, 'f', 2));
		m_pItem8->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(2, 3, m_pItem8);
	}

	pData = (CDvmData *)m_pRecloseResultAssessDataGroup->FindByID("TtripAcc_AbsErrMinus");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(fTtripAccAbsErrMinus, 'f', 2);
		m_pItem12 = new QTableWidgetItem(QString::number(fTtripAccAbsErrMinus, 'f', 2));
		m_pItem12->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(2, 4, m_pItem12);
	}

	pData = (CDvmData *)m_pRecloseResultAssessDataGroup->FindByID("Ttrip_ErrorLogic");
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nActionTime);
		m_pCmbActionTime->setCurrentIndex(nActionTime);
	}*/

	pData = (CDvmData *)m_pRecloseResultAssessDataGroup->FindByID("TtripD_ErrorLogic");
	if (pData != NULL)
	{        
        CDataTypeValue *pValue = (CDataTypeValue*)m_pCmbTtripTime->GetCurrSelObject();
        if(pValue != NULL)
            pData->m_strValue = pValue->m_strIndex;
	}

	//pData = (CDvmData *)m_pRecloseResultAssessDataGroup->FindByID("TtripAcc_ErrorLogic");
	//if (pData != NULL)
	//{
	//	pData->m_strValue = QString::number(nAccTime);
	//	m_pCmbAccTime->setCurrentIndex(nAccTime);
	//}

	accept();
}

void QRecloseResultAssessDlg::InitConnections()
{
	connect(m_pBtnOK,SIGNAL(clicked()),this,SLOT(slot_btnOK_Clicked()));
	connect(m_pBtnCancel,SIGNAL(clicked()),this,SLOT(slot_btnCancel_Clicked()));
	connect(m_pCmbTtripTime, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CmbTtripTimeCurrentIndex(int)));
	connect(m_pResultTableWidget,SIGNAL(cellChanged(int, int)),this,SLOT(slot_cellClicked(int, int)));
}
void QRecloseResultAssessDlg::slot_btnCancel_Clicked()
{
	reject();
}

void QRecloseResultAssessDlg::UpdataResultAssess()
{
	CDvmData *pData = NULL;
	long nValue;
	float fValue;

	/*pData = (CDvmData *)m_pRecloseResultAssessDataGroup->FindByID("Ttrip_RelErr");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pItem1 = new QTableWidgetItem(QString::number(nValue));
		m_pItem1->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(0, 2, m_pItem1);
	}


	pData = (CDvmData *)m_pRecloseResultAssessDataGroup->FindByID("Ttrip_AbsErr");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		m_pItem2 = new QTableWidgetItem(QString::number(fValue, 'f', 2));
		m_pItem2->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(0, 3, m_pItem2);
	}

	pData = (CDvmData *)m_pRecloseResultAssessDataGroup->FindByID("Ttrip_AbsErrMinus");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		m_pItem10 = new QTableWidgetItem(QString::number(fValue, 'f', 2));
		m_pItem10->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(0, 4, m_pItem10);
	}*/

	pData = (CDvmData *)m_pRecloseResultAssessDataGroup->FindByID("TtripD_RelErr");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pItem4 = new QTableWidgetItem(QString::number(nValue));
		m_pItem4->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(/*1*/0, 2, m_pItem4);
	}

	pData = (CDvmData *)m_pRecloseResultAssessDataGroup->FindByID("TtripD_AbsErr");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		m_pItem5 = new QTableWidgetItem(QString::number(fValue, 'f', 2));
		m_pItem5->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(/*1*/0, 3, m_pItem5);
	}

	pData = (CDvmData *)m_pRecloseResultAssessDataGroup->FindByID("TtripD_AbsErrMinus");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		m_pItem11 = new QTableWidgetItem(QString::number(fValue, 'f', 2));
		m_pItem11->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(/*1*/0, 4, m_pItem11);
	}
	
	/*pData = (CDvmData *)m_pRecloseResultAssessDataGroup->FindByID("TtripAcc_RelErr");
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pItem7 = new QTableWidgetItem(QString::number(nValue));
		m_pItem7->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(2, 2, m_pItem7);
	}

	pData = (CDvmData *)m_pRecloseResultAssessDataGroup->FindByID("TtripAcc_AbsErr");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		m_pItem8 = new QTableWidgetItem(QString::number(fValue, 'f', 2));
		m_pItem8->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(2, 3, m_pItem8);
	}

	pData = (CDvmData *)m_pRecloseResultAssessDataGroup->FindByID("TtripAcc_AbsErrMinus");
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		m_pItem12 = new QTableWidgetItem(QString::number(fValue, 'f', 2));
		m_pItem12->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(2, 4, m_pItem12);
	}*/

	//pData = (CDvmData *)m_pRecloseResultAssessDataGroup->FindByID("Ttrip_ErrorLogic");
	//if (pData != NULL)
	//{
	//	nValue = CString_To_long(pData->m_strValue);
	//	m_pCmbActionTime->setCurrentIndex(nValue);
	//}

	pData = (CDvmData *)m_pRecloseResultAssessDataGroup->FindByID("TtripD_ErrorLogic");
	if (pData != NULL)
	{
        CDataType *pDataType = (CDataType*)g_theHtmlRptGenFactory->m_pDataTypes->FindByID(STT_MULTI_MACRO_RECLOSEACC_PARAS_DATATYPE_ID_ERRTYPE);
        CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex(CString_To_long(pData->m_strValue));
        if(pValue != NULL)
            m_pCmbTtripTime->SetCurrSelByName(pValue->m_strName);
	}

	//pData = (CDvmData *)m_pRecloseResultAssessDataGroup->FindByID("TtripAcc_ErrorLogic");
	//if (pData != NULL)
	//{
	//	nValue = CString_To_long(pData->m_strValue);
	//	m_pCmbAccTime->setCurrentIndex(nValue);
	//}
}

void QRecloseResultAssessDlg::slot_cellClicked(int row ,int col)
{
	if (col == 2 && row >= 0 && row <= 2) 
	{
		QTableWidgetItem *item = m_pResultTableWidget->item(row, col);
		if (item) 
		{
			float fv = item->text().toFloat();
			fv = setLimit(0,100.000,fv);
			item->setText(QString::number(fv, 'f', 3)); 
		}
	}
	if (col == 3 && row >= 0 && row <= 2) 
	{
		QTableWidgetItem *item2 = m_pResultTableWidget->item(row, col);
		if (item2) 
		{
			float fv = item2->text().toFloat();
			fv = setLimit(0,200.000,fv);
			item2->setText(QString::number(fv, 'f', 3)); 
		}
	}

	if (col == 4 && row >= 0 && row <= 2)
	{
		QTableWidgetItem *item3 = m_pResultTableWidget->item(row, col);
		if (item3)
		{
			float fv = item3->text().toFloat();
			fv = setLimit(0, 200.000, fv);
			item3->setText(QString::number(fv, 'f', 3));
		}
	}
}

void QRecloseResultAssessDlg::slot_CmbTtripTimeCurrentIndex(int nIndex)
{
	if (nIndex == 0)
	{
		m_pItem4->setFlags(m_pItem4->flags() & ~Qt::ItemIsEnabled);
		m_pItem5->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
		m_pItem11->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
	}
	else if (nIndex == 1)
	{
		m_pItem4->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
		m_pItem5->setFlags(m_pItem4->flags() & ~Qt::ItemIsEnabled);
		m_pItem11->setFlags(m_pItem4->flags() & ~Qt::ItemIsEnabled);
	}
	else if (nIndex == 4)
	{
		m_pItem4->setFlags(m_pItem4->flags() & ~Qt::ItemIsEnabled); 
		m_pItem5->setFlags(m_pItem4->flags() & ~Qt::ItemIsEnabled);
		m_pItem11->setFlags(m_pItem4->flags() & ~Qt::ItemIsEnabled);
	}
	else
	{
		m_pItem4->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
		m_pItem5->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
		m_pItem11->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
	}
}

bool QRecloseResultAssessDlg::eventFilter(QObject *obj, QEvent *event)
{
	if (obj == m_pResultTableWidget->viewport() && event->type() == QEvent::MouseButtonPress) 
	{
		QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
		if (mouseEvent->button() == Qt::LeftButton) 
		{
			QPoint point = mouseEvent->pos();
			QModelIndex index = m_pResultTableWidget->indexAt(point);
			m_pResultTableWidget->edit(index);
			return true;
		}
	}
	return QObject::eventFilter(obj, event);
}

