#include "SynResultEstimateDlg.h"
#include "ui_SynResultEstimateDlg.h"
#include "../../UI/Module/CommonMethod/commonMethod.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

#ifdef _PSX_QT_WINDOWS_	
#include <QApplication>
#include <QDesktopWidget>
#include <QRect>
#include "../../UI/SttTestCntrFrameBase.h"
#endif

extern CFont *g_pSttGlobalFont;

QSynResultEstimateDlg::QSynResultEstimateDlg(/*CDataGroup *pPara,*/QWidget *parent) :
    QDialog(parent), 
	ui(new Ui::QSynResultEstimateDlg)
{
    ui->setupUi(this);

	//m_pCurrDataGroup = pPara;
    InitUI();
	InitLanuage();
}

QSynResultEstimateDlg::~QSynResultEstimateDlg()
{
    delete ui;
}

void QSynResultEstimateDlg::InitUI()
{

    this->setFont(*g_pSttGlobalFont);
    this->setWindowTitle(/*"结果评估"*/g_sLangTxt_StateEstimate_ResultEstimate);
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::Dialog);

	ui->tableWidget->setRowCount(6);
	ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); 
	ui->tableWidget->setStyleSheet("selection-background-color: grey;selection-color: black");

	ui->tableWidget->horizontalHeader()->setMinimumHeight(30);

	ui->tableWidget->verticalHeader()->setVisible(true);
	ui->tableWidget->setShowGrid(true);

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
	ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#else
	ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
#endif
	//ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	QTableWidgetItem *pAllowPressureItem = new QTableWidgetItem(g_sLangTxt_VolDif + "(V)");
	QTableWidgetItem *pAllowFreItem = new QTableWidgetItem(g_sLangTxt_FreqDif + "(Hz)");
	QTableWidgetItem *pLeadAngleItem = new QTableWidgetItem(g_sLangTxt_LeadingAngle);
	QTableWidgetItem *pLeadTimeItem = new QTableWidgetItem(g_sLangTxt_LeadingTime + "(s)");
	QTableWidgetItem *pPressureItem = new QTableWidgetItem(g_sLangTxt_Vol_ReguPeriod + "(s)");
	QTableWidgetItem *pFreItem = new QTableWidgetItem(g_sLangTxt_Freq_ReguPeriod + "(s)");
	SetTableWidgetItem(pAllowPressureItem, 0, 0);
	SetTableWidgetItem(pAllowFreItem, 1, 0);
	SetTableWidgetItem(pLeadAngleItem, 2, 0);
	SetTableWidgetItem(pLeadTimeItem, 3, 0);
	SetTableWidgetItem(pPressureItem, 4, 0);
	SetTableWidgetItem(pFreItem, 5, 0);

	m_pCmb_AllowPressure = new QComboBox(this);
	ComboxModelStyle(m_pCmb_AllowPressure, 0, 1);
	m_pCmb_AllowFre = new QComboBox(this);
	ComboxModelStyle(m_pCmb_AllowFre, 1, 1);
	m_pCmb_LeadAngle = new QComboBox(this);
	ComboxModelStyle(m_pCmb_LeadAngle, 2, 1);
	m_pCmb_LeadTime = new QComboBox(this);
	ComboxModelStyle(m_pCmb_LeadTime, 3, 1);
	m_pCmb_Pressure = new QComboBox(this);
	ComboxModelStyle(m_pCmb_Pressure, 4, 1);
	m_pCmb_Fre = new QComboBox(this);
	ComboxModelStyle(m_pCmb_Fre, 5, 1);
    

	m_pRelativeErrorEdit1 = new QTableWidgetItem();
	SetTableWidgetItem(m_pRelativeErrorEdit1, 0, 2);
	m_pRelativeErrorLabel2 = new QLabel(this);
	SetLabel(m_pRelativeErrorLabel2, 1, 2);
	m_pRelativeErrorLabel3 = new QLabel(this);
	SetLabel(m_pRelativeErrorLabel3, 2, 2);
	m_pRelativeErrorLabel4 = new QLabel(this);
	SetLabel(m_pRelativeErrorLabel4, 3, 2);
	m_pRelativeErrorEdit5 = new QTableWidgetItem();
	SetTableWidgetItem(m_pRelativeErrorEdit5, 4, 2);
	m_pRelativeErrorEdit6 = new QTableWidgetItem();
	SetTableWidgetItem(m_pRelativeErrorEdit6, 5, 2);

	m_pAbsoluteErrorEdit1 = new QTableWidgetItem();
	SetTableWidgetItem(m_pAbsoluteErrorEdit1, 0, 3);
	m_pAbsoluteErrorEdit2 = new QTableWidgetItem();
	SetTableWidgetItem(m_pAbsoluteErrorEdit2, 1, 3);
	m_pAbsoluteErrorEdit3 = new QTableWidgetItem();
	SetTableWidgetItem(m_pAbsoluteErrorEdit3, 2, 3);
	m_pAbsoluteErrorEdit4 = new QTableWidgetItem();;
	SetTableWidgetItem(m_pAbsoluteErrorEdit4, 3, 3);
	m_pAbsoluteErrorEdit5 = new QTableWidgetItem();
	SetTableWidgetItem(m_pAbsoluteErrorEdit5, 4, 3);
	m_pAbsoluteErrorEdit6 = new QTableWidgetItem();
	SetTableWidgetItem(m_pAbsoluteErrorEdit6, 5, 3);

	m_pAbsoluteNegErrorLabel1 = new QLabel();
	SetLabel(m_pAbsoluteNegErrorLabel1, 0, 4);
	m_pAbsoluteNegErrorLabel2 = new QLabel();
	SetLabel(m_pAbsoluteNegErrorLabel2, 1, 4);
	m_pAbsoluteNegErrorLabel3 = new QLabel();
	SetLabel(m_pAbsoluteNegErrorLabel3, 2, 4);
	m_pAbsoluteNegErrorLabel4 = new QLabel();;
	SetLabel(m_pAbsoluteNegErrorLabel4, 3, 4);
	m_pAbsoluteNegErrorEdit5 = new QTableWidgetItem();
	SetTableWidgetItem(m_pAbsoluteNegErrorEdit5, 4, 4);
	m_pAbsoluteNegErrorEdit6 = new QTableWidgetItem();
	SetTableWidgetItem(m_pAbsoluteNegErrorEdit6, 5, 4);
	

    ui->tableWidget->horizontalHeaderItem(0)->setFont(*g_pSttGlobalFont);
    ui->tableWidget->horizontalHeaderItem(1)->setFont(*g_pSttGlobalFont);
    ui->tableWidget->horizontalHeaderItem(2)->setFont(*g_pSttGlobalFont);
    ui->tableWidget->horizontalHeaderItem(3)->setFont(*g_pSttGlobalFont);


    initBaseData();

#ifdef _PSX_QT_WINDOWS_	
	//2024-8-1 wuxinyi 在2880*1800分辨率显示不全
	QDesktopWidget* desktopWidget = QApplication::desktop();
	QRect rect = desktopWidget->screenGeometry();
	float fWidth = rect.width() * g_dUIShowCoef;

	if (fWidth >= 2880)
	{
		resize(1000, 750);
	}
	else if (fWidth >= 2280)
	{
		resize(800, 450);
	}
	else
	{
		resize(800, 400);
	}
#else
	resize(800, 400);
#endif // _PSX_QT_WINDOWS_


    return;

}
void QSynResultEstimateDlg::InitLanuage()
{
	CString strtemp;
	xlang_GetLangStrByFile(strtemp, g_sLangID_Name);//名称
	ui->tableWidget->horizontalHeaderItem(0)->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_ErrorType);//误差类型
	ui->tableWidget->horizontalHeaderItem(1)->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_RelError_Percent);//相对误差(％)
	ui->tableWidget->horizontalHeaderItem(2)->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_AbsError);//绝对误差
	ui->tableWidget->horizontalHeaderItem(3)->setText(strtemp);
	xlang_GetLangStrByFile(strtemp, g_sLangID_StateEstimate_AbsError_Neg);//绝对误差(-)
	ui->tableWidget->horizontalHeaderItem(4)->setText(strtemp);

	xlang_SetLangStrToWidget(ui->pushButton, g_sLangID_OK, XLang_Ctrls_QPushButton);//确定
	xlang_SetLangStrToWidget(ui->pushButton_2, g_sLangID_Cancel, XLang_Ctrls_QPushButton);//取消

}
void QSynResultEstimateDlg::SetTableWidgetItem(QTableWidgetItem *pItem, int nRow, int nCol)
{
	if (nCol==0)
	{
		pItem->setFlags(pItem->flags() & ~Qt::ItemIsEditable);
		pItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	}
	else
	{
		pItem->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
	}

	ui->tableWidget->setItem(nRow, nCol, pItem);
}

void QSynResultEstimateDlg::CbbErrorType(int nIndex, CString strText)
{
	if (strText == g_sLangTxt_StateEstimate_AbsError)//绝对误差
	{
		SetItemEnable(nIndex, 2, FALSE);
		SetItemEnable(nIndex, 3, TRUE);
		SetItemEnable(nIndex, 4, TRUE);
	}
	else if (strText == g_sLangTxt_StateEstimate_RelError)//相对误差
	{
		SetItemEnable(nIndex, 2, TRUE);
		SetItemEnable(nIndex, 3, FALSE);
		SetItemEnable(nIndex, 4, FALSE);
	}
	else if (strText == g_sLangTxt_Distance_ErrorNot)//不评估
	{
		SetItemEnable(nIndex, 2, FALSE);
		SetItemEnable(nIndex, 3, FALSE);
		SetItemEnable(nIndex, 4, FALSE);
	}
	else
	{
		SetItemEnable(nIndex, 2, TRUE);
		SetItemEnable(nIndex, 3, TRUE);
		SetItemEnable(nIndex, 4, TRUE);
	}


}

void QSynResultEstimateDlg::ComboxModelStyle(QComboBox *pCombox, int nRow, int nCol)
{
	pCombox->setEditable(true);
	pCombox->lineEdit()->setAlignment(Qt::AlignCenter);
	pCombox->lineEdit()->setReadOnly(true);
	pCombox->lineEdit()->setMouseTracking(true);
	pCombox->lineEdit()->setStyleSheet("background:transparent;border-width:0;border-style:outset");
	pCombox->lineEdit()->setAttribute(Qt::WA_TransparentForMouseEvents);
	ui->tableWidget->setCellWidget(nRow, nCol, pCombox);
}

void QSynResultEstimateDlg::slot_cmbAllowPressureErrorChanged(const QString& strText)
{

	CbbErrorType(0, strText);
}

void QSynResultEstimateDlg::slot_cmbPressureErrorChanged(const QString& strText)
{
	CbbErrorType(4, strText);
}

void QSynResultEstimateDlg::slot_cmbFreErrorChanged(const QString& strText)
{
	CbbErrorType(5, strText);
}

void QSynResultEstimateDlg::SetLineEdit(QLineEdit *pLineEdit,int nRow,int nCol)
{
	pLineEdit->setAlignment(Qt::AlignCenter);
	ui->tableWidget->setCellWidget(nRow, nCol, pLineEdit);
}

void QSynResultEstimateDlg::SetLabel(QLabel *pLabel, int nRow, int nCol)
{
	pLabel->setAlignment(Qt::AlignCenter);
	ui->tableWidget->setCellWidget(nRow, nCol, pLabel); 
	//QTableWidgetItem *item = new QTableWidgetItem;
	
}

void QSynResultEstimateDlg::initBaseData()
{
	m_SynEstimateList.clear();
	//m_SynEstimateList <<QString::fromUtf8("绝对误差")<< QString::fromUtf8("相对误差")<< QString::fromUtf8("绝对or相对")\
	//	<<QString::fromUtf8("绝对&相对")<<QString::fromUtf8("组合误差")<< QString::fromUtf8("不评估");
	m_SynEstimateList << g_sLangTxt_StateEstimate_AbsError << g_sLangTxt_StateEstimate_RelError << g_sLangTxt_StateEstimate_AbsError + "or" + g_sLangTxt_StateEstimate_RelError << \
		g_sLangTxt_StateEstimate_AbsError + "&" + g_sLangTxt_StateEstimate_RelError << g_sLangTxt_StateEstimate_CombinationError << g_sLangTxt_Distance_ErrorNot;
	m_pCmb_AllowPressure->clear();
	m_pCmb_AllowPressure->addItems(m_SynEstimateList);
	m_pCmb_AllowPressure->setCurrentIndex(0);

	m_pCmb_AllowFre->clear();
	m_pCmb_AllowFre->addItems(QStringList() << g_sLangTxt_StateEstimate_AbsError);
	m_pCmb_AllowFre->setCurrentIndex(0);

	m_pCmb_LeadAngle->clear();
	m_pCmb_LeadAngle->addItems(QStringList() << g_sLangTxt_StateEstimate_AbsError);
	m_pCmb_LeadAngle->setCurrentIndex(0);

	m_pCmb_LeadTime->clear();
	m_pCmb_LeadTime->addItems(QStringList() << g_sLangTxt_StateEstimate_AbsError);
	m_pCmb_LeadTime->setCurrentIndex(0);

	m_pRelativeErrorLabel2->setText("---");
	//m_pRelativeErrorLabel2->setDisabled(true);
	m_pRelativeErrorLabel3->setText("---");
	//m_pRelativeErrorLabel3->setDisabled(true);
	m_pRelativeErrorLabel4->setText("---");
	//m_pRelativeErrorLabel4->setDisabled(true);

	m_pAbsoluteNegErrorLabel1->setText("---");
	//m_pAbsoluteNegErrorLabel1->setDisabled(true);
	m_pAbsoluteNegErrorLabel2->setText("---");
	//m_pAbsoluteNegErrorLabel2->setDisabled(true);
	m_pAbsoluteNegErrorLabel3->setText("---");
	//m_pAbsoluteNegErrorLabel3->setDisabled(true);
	m_pAbsoluteNegErrorLabel4->setText("---");
	//m_pAbsoluteNegErrorLabel4->setDisabled(true);

	for (int i = 0; i < 6; i++)
	{
		ui->tableWidget->item(i, 0)->setFlags(ui->tableWidget->item(i, 0)->flags() & ~Qt::ItemIsEditable);
		EnableRow(i, FALSE);
	}

	m_pCmb_Pressure->clear();
	m_pCmb_Pressure->addItems(m_SynEstimateList);
	m_pCmb_Pressure->setCurrentIndex(0);

	m_pCmb_Fre->clear();
	m_pCmb_Fre->addItems(m_SynEstimateList);
	m_pCmb_Fre->setCurrentIndex(0);

	
	
	connect(ui->tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(slot_OnCellChanged(int, int)), Qt::UniqueConnection);
	connect(m_pCmb_AllowPressure, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbAllowPressureErrorChanged(const QString &)));
	connect(m_pCmb_Pressure, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbPressureErrorChanged(const QString &)));
	connect(m_pCmb_Fre, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbFreErrorChanged(const QString &)));
	
}

void QSynResultEstimateDlg::slot_OnCellChanged(int row, int col)
{
	if (row  <  0)
	{
		return;
	}

	disconnect(ui->tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(slot_OnCellChanged(int, int)));

	QTableWidgetItem  *pItem = ui->tableWidget->item(row, col);

	if (pItem == NULL)
	{
		return;
	}

	QString str = pItem->text();
	float fv = str.toFloat();

	if (col == 2)//相对误差
	{
		fv = setLimit(0, 100, fv);
		pItem->setText(QString::number(fv, 'f', 3));
	}

	if (col == 3)//绝对误差
	{
		fv = setLimit(0, 200, fv);
		pItem->setText(QString::number(fv, 'f', 3));
	}

	if (col == 4)//绝对误差负
	{
		fv = setLimit(0, 200, fv);
		pItem->setText(QString::number(fv, 'f', 3));
	}

	connect(ui->tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(slot_OnCellChanged(int, int)), Qt::UniqueConnection);
}

void QSynResultEstimateDlg::SetDatas(CDataGroup *pParas)
{

	if (pParas == NULL)
	{
		return;
	}
	m_pCurrDataGroup = pParas;
	CheckAllPresence();

	POS pos = pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CDvmData *pData = (CDvmData*)m_pCurrDataGroup->GetNext(pos);
		SetValueToPage(pData);
	}

	GetValueFromSelect(STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_VolBordValue_CHECK, 0);
	GetValueFromSelect(STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_FreqBordValue_CHECK, 1);
	GetValueFromSelect(STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_LeaderAngleLeaderTime_CHECK, STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_SelfAdjusting_CHECK);
	GetValueFromSelect(STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_Ut_CHECK, 4);
	GetValueFromSelect(STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_Ft_CHECK, 5);

	CbbErrorType(0, m_pCmb_AllowPressure->currentText());
	CbbErrorType(4, m_pCmb_Pressure->currentText());
	CbbErrorType(5, m_pCmb_Fre->currentText());
}

void QSynResultEstimateDlg::CheckAllPresence()
{
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_ERRORLOGIC);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_ERRORLOGIC);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_ERRORLOGIC);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_ERRORLOGIC);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_ERRORLOGIC);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_ERRORLOGIC);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_ABSERR);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_RELERR);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_ABSERR);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_RELERR);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_ABSERR);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_RELERR);//STT_MULTI_MACRO_SYN_PARAS_ID_RESULT_LEADANG_RELERR
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_ABSERR);//STT_MULTI_MACRO_SYN_PARAS_ID_RESULT_LEADTIME_ABSERR
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_RELERR);//STT_MULTI_MACRO_SYN_PARAS_ID_RESULT_LEADTIME_RELERR
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_PLUS);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_RELERR);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_MINUS);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_RELERR);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_PLUS);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_MINUS);
	
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_VolBordValue_CHECK);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_FreqBordValue_CHECK);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_LeaderAngleLeaderTime_CHECK);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_SelfAdjusting_CHECK);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_Ut_CHECK);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_Ft_CHECK);
}

void QSynResultEstimateDlg::CheckForPresence(CString strID)
{
	//20240624 luozibing检查ID对应数据是否存在、不存在则添加
	if (m_pCurrDataGroup == NULL)
		return;
	CDvmData *pData = (CDvmData *)m_pCurrDataGroup->FindByID(strID);
	if (pData == NULL)
	{
		CDvmData *pNew = new CDvmData();
		pNew->m_strName = strID;
		pNew->m_strID = strID;
		pNew->m_strValue = STT_MULTI_MACRO_SYN_PARAS_ID_DEFAULT;
		m_pCurrDataGroup->AddNewChild(pNew);
	}
}
void QSynResultEstimateDlg::SetValueToPage(CDvmData *pData)
{
	if(pData == NULL)
		return;

	if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_ERRORLOGIC)
	{
		m_pCmb_AllowPressure->setCurrentIndex(pData->m_strValue.toInt());
	}
	//else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_ERRORLOGIC)
	//{
	//	m_pAllowFreLabel->setText(QString::fromUtf8("绝对误差"));
	//	m_pAllowFreLabel->setEnabled(false);
	//}
	//else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_ERRORLOGIC)
	//{
	//	m_pLeadAngleLabel->setText(QString::fromUtf8("绝对误差"));
	//	m_pLeadAngleLabel->setEnabled(false);
	//}
	//else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_ERRORLOGIC)
	//{
	//	m_pLeadTimeLabel->setText(QString::fromUtf8("绝对误差"));
	//	m_pLeadTimeLabel->setEnabled(false);
	//}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_ERRORLOGIC)
	{
		m_pCmb_Pressure->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_ERRORLOGIC)
	{
		m_pCmb_Fre->setCurrentIndex(pData->m_strValue.toInt());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_ABSERR)
	{
		m_pAbsoluteErrorEdit1->setText(CheckDataMinMax(pData->m_strValue,200,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_RELERR)
	{
		m_pRelativeErrorEdit1->setText(CheckDataMinMax(pData->m_strValue,100,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_ABSERR)
	{
		m_pAbsoluteErrorEdit2->setText(CheckDataMinMax(pData->m_strValue,200,0,3));
	}
	/*else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_RESULT_FREQTEST_RELERR)
	{
		m_pRelativeErrorLabel2->setText("---");
	}*/
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_ABSERR)
	{
		m_pAbsoluteErrorEdit3->setText(CheckDataMinMax(pData->m_strValue,200,0,3));
	}
	/*else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_RESULT_LEADANG_RELERR)
	{
		m_pRelativeErrorLabel3->setText("---");
	}*/
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_ABSERR)
	{
		m_pAbsoluteErrorEdit4->setText(CheckDataMinMax(pData->m_strValue,200,0,3));
	}
	/*else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_RESULT_LEADTIME_RELERR)
	{
		m_pRelativeErrorLabel4->setText("---");
	}*/
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_PLUS)
	{
		m_pAbsoluteErrorEdit5->setText(CheckDataMinMax(pData->m_strValue,200,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_RELERR)
	{
		m_pRelativeErrorEdit5->setText(CheckDataMinMax(pData->m_strValue,100,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_PLUS)
	{
		m_pAbsoluteErrorEdit6->setText(CheckDataMinMax(pData->m_strValue,200,0,3));
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_RELERR)
	{
		m_pRelativeErrorEdit6->setText(CheckDataMinMax(pData->m_strValue,100,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_MINUS)
	{
		m_pAbsoluteNegErrorEdit5->setText(CheckDataMinMax(pData->m_strValue, 200, 0, 3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_MINUS)
	{
		m_pAbsoluteNegErrorEdit6->setText(CheckDataMinMax(pData->m_strValue, 200, 0, 3));
	}
}

void QSynResultEstimateDlg::GetDatas(CDataGroup *pParas)
{
	if(pParas == NULL)
		return;
	m_pCurrDataGroup = pParas;
	CheckAllPresence();
	//20240614 luozibing 将界面中的参数保存到链表中
	POS pos = pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CDvmData *pData = (CDvmData*)pParas->GetNext(pos);
		GetPageToValue(pData);
	}

	return;
}
void QSynResultEstimateDlg::GetPageToValue(CDvmData *pData)
{
	if(pData == NULL)
		return;
	if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_ERRORLOGIC)
	{
		 pData->m_strValue.setNum(m_pCmb_AllowPressure->currentIndex());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_ERRORLOGIC)
	{
		pData->m_strValue.setNum(m_pCmb_Pressure->currentIndex());
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_ERRORLOGIC)
	{
		pData->m_strValue.setNum(m_pCmb_Fre->currentIndex());
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_ABSERR)
	{
		pData->m_strValue = m_pAbsoluteErrorEdit1->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_VOLTTEST_RELERR)
	{
		pData->m_strValue = m_pRelativeErrorEdit1->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_FREQTEST_ABSERR)
	{
		pData->m_strValue = m_pAbsoluteErrorEdit2->text();
	}
	//else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_RESULT_FREQTEST_RELERR)
	//{
	//	pData->m_strValue = m_pRelativeErrorLabel2->text();
	//}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_ABSERR)
	{
		pData->m_strValue = m_pAbsoluteErrorEdit3->text();
	}	
	/*else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_RESULT_LEADANG_RELERR)
	{
		pData->m_strValue = m_pRelativeErrorLabel3->text();
	}*/
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_ABSERR)
	{
		pData->m_strValue = m_pAbsoluteErrorEdit4->text();
	}
	//else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_RESULT_LEADTIME_RELERR)
	//{
	//	pData->m_strValue = m_pRelativeErrorLabel4->text();
	//}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_PLUS)
	{
		pData->m_strValue = m_pAbsoluteErrorEdit5->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_RELERR)
	{
		pData->m_strValue = m_pRelativeErrorEdit5->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_PLUS)
	{
		pData->m_strValue = m_pAbsoluteErrorEdit6->text();
	}
	else if(pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_RELERR)
	{
		pData->m_strValue = m_pRelativeErrorEdit6->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJVOL_MINUS)
	{
		pData->m_strValue = m_pAbsoluteNegErrorEdit5->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_ADJFREQ_MINUS)
	{
		pData->m_strValue = m_pAbsoluteNegErrorEdit6->text();
	}
}

void QSynResultEstimateDlg::GetValueFromSelect(CString strID,int nindex)
{
	if (m_pCurrDataGroup == NULL)
		return;

	CDvmData *pData = NULL;

	CheckForPresence(strID);
	pData = (CDvmData *)m_pCurrDataGroup->FindByID(strID);

	CDvmData *pLeaderAngData = (CDvmData *)m_pCurrDataGroup->FindByID(STT_MULTI_MACRO_SYN_PARAS_ID_LEADANG_LeaderAngleLeaderTime_CHECK);
	CDvmData *pSelfAdjustData = (CDvmData *)m_pCurrDataGroup->FindByID(STT_MULTI_MACRO_SYN_PARAS_ID_AUTOADJ_SelfAdjusting_CHECK);
	if (pLeaderAngData != NULL || pSelfAdjustData != NULL)
	{
		int nLeaderAngValue = pLeaderAngData->m_strValue.toInt();
		int nSelfAdjustValue = pSelfAdjustData->m_strValue.toInt();
		if (nLeaderAngValue == 1 || nSelfAdjustValue == 1)
		{
			EnableRow(2);
			EnableRow(3);
		}
		else
		{
			EnableRow(2, false);
			EnableRow(3, false);
			
		}
	}

	if (pData != NULL)
	{
		int nValue = pData->m_strValue.toInt();
		if (nValue)
		{
			EnableRow(nindex);
			
		}
		else
		{
			EnableRow(nindex, false);
			
		}
	}
}

//导前角及导前时间试验和自调整试验的结果评估需要同时显示导前角和导前时间
void QSynResultEstimateDlg::GetValueFromSelect(CString strID, CString strID2)
{
	if (m_pCurrDataGroup == NULL)
		return;

	CDvmData *pLeaderAngData = NULL;
	CDvmData *pSelfAdjustData = NULL;

	CheckForPresence(strID);

	pLeaderAngData = (CDvmData *)m_pCurrDataGroup->FindByID(strID);
	pSelfAdjustData = (CDvmData *)m_pCurrDataGroup->FindByID(strID2);
	if (pLeaderAngData != NULL || pSelfAdjustData != NULL)
	{
		int nLeaderAngValue = pLeaderAngData->m_strValue.toInt();
		int nSelfAdjustValue = pSelfAdjustData->m_strValue.toInt();
		if (nLeaderAngValue == 1 || nSelfAdjustValue == 1)
		{
			EnableRow(2);
			EnableRow(3);
		}
		else
		{
			EnableRow(2, false);
			EnableRow(3, false);
		}
	}
}

void QSynResultEstimateDlg::EnableRow(long nIndex, BOOL bEnabled)
{
	if (nIndex >= 6)
	{
		return;
	}

	QComboBox* pCbb = (QComboBox*)ui->tableWidget->cellWidget(nIndex, 1);
	pCbb->setEnabled(bEnabled);
	if (bEnabled)
	{
		SetItemEnable(nIndex, 2, TRUE);
		SetItemEnable(nIndex, 3, TRUE);
		SetItemEnable(nIndex, 4, TRUE);
	}
	else
	{
		SetItemEnable(nIndex, 2, FALSE);
		SetItemEnable(nIndex, 3, FALSE);
		SetItemEnable(nIndex, 4, FALSE);
	}
}

void QSynResultEstimateDlg::SetItemEnable(int nRow, int nCol, BOOL bEnable)
{
	QTableWidgetItem *pItem = ui->tableWidget->item(nRow, nCol);
	if (!pItem)
	{
		return;
	}

	pItem->setFlags(bEnable ? pItem->flags() | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable
		: pItem->flags() & ~Qt::ItemIsEditable &~Qt::ItemIsEnabled &~Qt::ItemIsSelectable);
	bool bCbbState = true;
	if (nCol == 2 || nCol == 3 || nCol == 4)
	{
		QComboBox* pCbb = (QComboBox*)ui->tableWidget->cellWidget(nRow, 1);
		if (pCbb)
		{
			bCbbState = pCbb->isEnabled();
		}
	}

	QLabel* pRelErrorLabel = (QLabel*)ui->tableWidget->cellWidget(nRow, 2);
	QLabel* pNegErrorLabel = (QLabel*)ui->tableWidget->cellWidget(nRow, 4);
	
	if (bCbbState && bEnable)
	{
		pItem->setForeground(Qt::black);  // 黑色背景
		if (pRelErrorLabel)
		{
			pRelErrorLabel->setDisabled(false);
		}
		if (pNegErrorLabel)
		{
			pNegErrorLabel->setDisabled(false);
		}
	}
	else
	{
		pItem->setForeground(Qt::gray);  // 灰色背景
		if (pRelErrorLabel)
		{
			pRelErrorLabel->setDisabled(true);
		}
		if (pNegErrorLabel)
		{
			pNegErrorLabel->setDisabled(true);
		}
	}
}

//确认
void QSynResultEstimateDlg::on_pushButton_clicked()
{
	this->done(Accepted);
}

//取消
void QSynResultEstimateDlg::on_pushButton_2_clicked()
{
	this->close();
}
