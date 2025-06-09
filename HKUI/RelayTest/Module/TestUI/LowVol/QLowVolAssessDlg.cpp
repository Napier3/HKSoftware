
#include "QLowVolAssessDlg.h"
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
#include <QDesktopWidget>
#include <QRect>

QLowVolAssessDlg::QLowVolAssessDlg(CDataGroup *m_oLowVolDataGroup,QWidget *parent) : QDialog(parent)
{

	m_pLowVolAssessDataGroup = m_oLowVolDataGroup;

	// 在2k分辨率150%缩放下显示不全
#ifdef _PSX_QT_WINDOWS_
	QDesktopWidget* desktopWidget = QApplication::desktop();
	QRect rect = desktopWidget->screenGeometry();
	float fWidth = rect.width() * g_dUIShowCoef;

	if (fWidth >= 2280)
	{
		resize(900, 300);
	}
	else
	{
		resize(900, 250);
	}
#else
	resize(700, 170);
#endif // _PSX_QT_WINDOWS_
	InitUI();
	InitFont();
	InitConnections();
}

QLowVolAssessDlg::~QLowVolAssessDlg()
{

}

void QLowVolAssessDlg::InitUI()
{
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
	m_pResultTableWidget = new QTableWidget(4, 5, this);
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
//Sections
    m_pResultTableWidget->horizontalHeader()->setSectionsClickable(false);
    m_pResultTableWidget->horizontalHeader()->setSectionsMovable(false);
#else
    m_pResultTableWidget->horizontalHeader()->setClickable(false);
    m_pResultTableWidget->horizontalHeader()->setMovable(false);
#endif

	QStringList headers;
    headers << /*"名称"*/ g_sLangTxt_Name
            << /*误差类型*/g_sLangTxt_StateEstimate_ErrorType
            << /*"相对误差(%)"*/g_sLangTxt_StateEstimate_RelError + "(%)"
            << /*"绝对误差"*/g_sLangTxt_StateEstimate_AbsError
			<< /*"绝对误差(-)"*/g_sLangTxt_StateEstimate_AbsError + "(-)";
	m_pResultTableWidget->setHorizontalHeaderLabels(headers);
	m_pResultTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background: skyblue;}"); // 设置表头背景色
	m_pResultTableWidget->setStyleSheet("selection-background-color: grey;selection-color: black");
	m_pResultTableWidget->verticalHeader()->setVisible(false);

//	m_pResultTableWidget->resizeColumnsToContents(); // 根据内容调整列宽
//	m_pResultTableWidget->setColumnWidth(0, 200);
//	for (int col = 1; col < 4; ++col)
//	{
//        m_pResultTableWidget->setColumnWidth(col, 200);
//	}

    //m_pResultTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	m_pResultTableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); 
   // m_pResultTableWidget->setFixedSize(800, 150); // 设置固定大小

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
//Sections
    m_pResultTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 设置固定列宽
    m_pResultTableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 设置固定行高
#else
    m_pResultTableWidget->horizontalHeader()->setResizeMode(QHeaderView::Fixed); // 设置固定列宽
    m_pResultTableWidget->verticalHeader()->setResizeMode(QHeaderView::Fixed); // 设置固定行高
#endif

	m_pLabActionTime = new QLabel(/*"动作时间(s)"*/g_sLangTxt_Native_ActionTime);
	m_pResultTableWidget->setCellWidget(0, 0, m_pLabActionTime);

	m_pLabUAct = new QLabel(/*"低压减载动作值(V)"*/g_sLangTxt_Native_LowVoltUnderloadTripSet + "(V)");
	m_pResultTableWidget->setCellWidget(1, 0, m_pLabUAct);

	m_pLabDvdtClose = new QLabel(/*"电压滑差动作值(V/s)"*/g_sLangTxt_Native_VoltSlipAct + "(V/s)");
	m_pResultTableWidget->setCellWidget(2, 0, m_pLabDvdtClose);

	m_pLabTripILock = new QLabel(/*"低电流闭锁值(A)"*/g_sLangTxt_LowFreq_ILock + "(A)");
	m_pResultTableWidget->setCellWidget(3, 0, m_pLabTripILock);

	m_pLabActionTime->setAlignment(Qt::AlignCenter);
	m_pLabUAct->setAlignment(Qt::AlignCenter);
	m_pLabDvdtClose->setAlignment(Qt::AlignCenter);
	m_pLabTripILock->setAlignment(Qt::AlignCenter);

	m_pLabUActNeg = new QLabel("--");
	m_pLabDvdtCloseNeg = new QLabel("--");
	m_pLabTripILockNeg = new QLabel("--");

	m_pResultTableWidget->setCellWidget(1, 4, m_pLabUActNeg);
	m_pResultTableWidget->setCellWidget(2, 4, m_pLabDvdtCloseNeg);
	m_pResultTableWidget->setCellWidget(3, 4, m_pLabTripILockNeg);

	m_pLabUActNeg->setAlignment(Qt::AlignCenter);
	m_pLabDvdtCloseNeg->setAlignment(Qt::AlignCenter);
	m_pLabTripILockNeg->setAlignment(Qt::AlignCenter);

	m_pCmbActionTime = new QComboBox(m_pResultTableWidget);
	m_pCmbUAct = new QComboBox(m_pResultTableWidget);
	m_pCmbDvdtClose = new QComboBox(m_pResultTableWidget);
	m_pCmbTripILock = new QComboBox(m_pResultTableWidget);

	m_pCmbActionTime->setObjectName("0");
	m_pCmbUAct->setObjectName("1");
	m_pCmbDvdtClose->setObjectName("2");
	m_pCmbTripILock->setObjectName("3");

	QStringList headers1;
    headers1 << /*"绝对误差"*/g_sLangTxt_StateEstimate_AbsError
             << /*"相对误差"*/g_sLangTxt_StateEstimate_RelError
             << /*"绝对or相对"*/ g_sLangTxt_CBOperate_AbsOrRelative
             << /*"绝对&相对"*/g_sLangTxt_CBOperate_AbsRelative
             << /*"组合误差"*/g_sLangTxt_CBOperate_CombError
			 <<	/*"不评估"*/g_sLangTxt_Distance_ErrorNot;
	m_pCmbActionTime->addItems(headers1);
	m_pCmbUAct->addItems(headers1);
	m_pCmbDvdtClose->addItems(headers1);
	m_pCmbTripILock->addItems(headers1);


	m_pResultTableWidget->setCellWidget(0, 1, m_pCmbActionTime);
	m_pResultTableWidget->setCellWidget(1, 1, m_pCmbUAct);
	m_pResultTableWidget->setCellWidget(2, 1, m_pCmbDvdtClose);
	m_pResultTableWidget->setCellWidget(3, 1, m_pCmbTripILock);

	ComboxModelStyle(m_pCmbActionTime);
	ComboxModelStyle(m_pCmbUAct);
	ComboxModelStyle(m_pCmbDvdtClose);
	ComboxModelStyle(m_pCmbTripILock);

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
    //setLayout(m_pMainLayout);
	UpdataResultAssess();

	CbbErrorType(0, m_pCmbActionTime->currentText());
	CbbErrorType(1, m_pCmbUAct->currentText());
	CbbErrorType(2, m_pCmbDvdtClose->currentText());
	CbbErrorType(3, m_pCmbTripILock->currentText());
}
void QLowVolAssessDlg::slot_cmbErrorChanged(const QString& strText)
{
	QObject *senderObj = sender();
	CString strName;
	if (senderObj) {
		strName = senderObj->objectName();
	}
	CbbErrorType(strName.toInt(), strText);
}
void QLowVolAssessDlg::CbbErrorType(int nIndex, CString strText)
{
	if (strText == g_sLangTxt_Distance_ErrorNot)//不评估
	{
		SetItemEnable(nIndex, 2, FALSE);
		SetItemEnable(nIndex, 3, FALSE);
		if (nIndex == 0)
		{
			SetItemEnable(nIndex, 4, FALSE);
		}
	}
	else if (strText == g_sLangTxt_StateEstimate_AbsError)//绝对误差
	{
		SetItemEnable(nIndex, 2, FALSE);
		SetItemEnable(nIndex, 3, TRUE);
		if (nIndex == 0)
		{
			SetItemEnable(nIndex, 4, TRUE);
		}
	}
	else if (strText == g_sLangTxt_StateEstimate_RelError)//相对误差
	{
		SetItemEnable(nIndex, 2, TRUE);
		SetItemEnable(nIndex, 3, FALSE);
		if (nIndex == 0)
		{
			SetItemEnable(nIndex, 4, FALSE);
		}
	}
	else
	{
		SetItemEnable(nIndex, 2, TRUE);
		SetItemEnable(nIndex, 3, TRUE);
		if (nIndex == 0)
		{
			SetItemEnable(nIndex, 4, TRUE);
		}
	}
	if (nIndex != 0)
	{
		SetItemEnable(nIndex, 4, FALSE);
	}
}

void QLowVolAssessDlg::SetItemEnable(int nRow, int nCol, BOOL bEnable)
{
	QTableWidgetItem *pItem = m_pResultTableWidget->item(nRow, nCol);
	if (!pItem)
	{
		return;
	}

	pItem->setFlags(bEnable ? pItem->flags() | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable
		: pItem->flags() & ~Qt::ItemIsEditable &~Qt::ItemIsEnabled &~Qt::ItemIsSelectable);

	bool bCbbState = true;
	if (nCol == 2 || nCol == 3 || nCol == 4)
	{
		QComboBox* pCbb = (QComboBox*)m_pResultTableWidget->cellWidget(nRow, 1);
		if (pCbb)
		{
			bCbbState = pCbb->isEnabled();
		}
	}

	if (bCbbState && bEnable)
	{
		pItem->setForeground(Qt::black);  // 黑色背景
	}
	else
	{
		pItem->setForeground(Qt::gray);  // 灰色背景 
	}
}
void QLowVolAssessDlg::ComboxModelStyle(QComboBox *pCombox)
{
	pCombox->setEditable(true);
	pCombox->lineEdit()->setAlignment(Qt::AlignCenter);
	pCombox->lineEdit()->setReadOnly(true);
	pCombox->lineEdit()->setMouseTracking(true);
	pCombox->lineEdit()->setStyleSheet("background:transparent;border-width:0;border-style:outset");
	pCombox->lineEdit()->setAttribute(Qt::WA_TransparentForMouseEvents);
	pCombox->setEnabled(true);
}

void QLowVolAssessDlg::InitFont()
{
	m_pCmbActionTime->setFont(*g_pSttGlobalFont);
	m_pCmbUAct->setFont(*g_pSttGlobalFont);
	m_pCmbDvdtClose->setFont(*g_pSttGlobalFont);
	m_pCmbTripILock->setFont(*g_pSttGlobalFont);

	m_pResultTableWidget->setFont(*g_pSttGlobalFont);
	m_pResultTableWidget->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pBtnOK->setFont(*g_pSttGlobalFont);
	m_pBtnCancel->setFont(*g_pSttGlobalFont);

	m_pLabActionTime->setFont(*g_pSttGlobalFont);
	m_pLabUAct->setFont(*g_pSttGlobalFont);
	m_pLabDvdtClose->setFont(*g_pSttGlobalFont);
	m_pLabTripILock->setFont(*g_pSttGlobalFont);

}

void QLowVolAssessDlg::slot_btnOK_Clicked()
{
	long nActionTime = m_pCmbActionTime->currentIndex();
	long nUAct = m_pCmbUAct->currentIndex();
	long nDvdtClose = m_pCmbDvdtClose->currentIndex();
	long nTripILock = m_pCmbTripILock->currentIndex();

	float fTtripRelErr = m_pResultTableWidget->item(0, 2)->text().toFloat();
	float fTtripAbsErrPos = m_pResultTableWidget->item(0, 3)->text().toFloat();
	float fTtripAbsErrNeg = m_pResultTableWidget->item(0, 4)->text().toFloat();

	float fTripVolRelErr = m_pResultTableWidget->item(1, 2)->text().toFloat();
	float fTripVolAbsErr = m_pResultTableWidget->item(1, 3)->text().toFloat();

	float fTripDvdtRelErr = m_pResultTableWidget->item(2, 2)->text().toFloat();
	float fTripDvdtAbsErr = m_pResultTableWidget->item(2, 3)->text().toFloat();

	float fIlowRelErr = m_pResultTableWidget->item(3, 2)->text().toFloat();
	float fIlowAbsErr = m_pResultTableWidget->item(3, 3)->text().toFloat();

	CDvmData *pData = NULL;
	if (m_pLowVolAssessDataGroup == NULL)
	{
		return;
	}

	pData = (CDvmData *)m_pLowVolAssessDataGroup->FindByID(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_RELERR);
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(fTtripRelErr, 'f', 3);
	}

	pData = (CDvmData *)m_pLowVolAssessDataGroup->FindByID(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_ABSERRPOS);
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(fTtripAbsErrPos, 'f', 3);
	}

	pData = (CDvmData *)m_pLowVolAssessDataGroup->FindByID(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_ABSERRNEG);
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(fTtripAbsErrNeg, 'f', 3);
	}
	
	pData = (CDvmData *)m_pLowVolAssessDataGroup->FindByID(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_RELERR);
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(fTripVolRelErr, 'f', 3);
	}


	pData = (CDvmData *)m_pLowVolAssessDataGroup->FindByID(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_ABSERR);
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(fTripVolAbsErr, 'f', 3);
	}

	pData = (CDvmData *)m_pLowVolAssessDataGroup->FindByID(STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_RELERR);
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(fTripDvdtRelErr, 'f', 3);
	}

	pData = (CDvmData *)m_pLowVolAssessDataGroup->FindByID(STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_ABSERR);
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(fTripDvdtAbsErr, 'f', 3);
	}

	pData = (CDvmData *)m_pLowVolAssessDataGroup->FindByID(STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_RELERR);
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(fIlowRelErr, 'f', 3);
	}

	pData = (CDvmData *)m_pLowVolAssessDataGroup->FindByID(STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_ABSERR);
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(fIlowAbsErr, 'f', 3);
	}

	pData = (CDvmData *)m_pLowVolAssessDataGroup->FindByID(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_RSLTEVAL);
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nActionTime);
	}

	pData = (CDvmData *)m_pLowVolAssessDataGroup->FindByID(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_RSLTEVAL);
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nUAct);
	}

	pData = (CDvmData *)m_pLowVolAssessDataGroup->FindByID(STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_RSLTEVAL);
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nDvdtClose);
	}

	pData = (CDvmData *)m_pLowVolAssessDataGroup->FindByID(STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_RSLTEVAL);
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(nTripILock);
	}

	accept();
}

void QLowVolAssessDlg::InitConnections()
{
	connect(m_pBtnOK,SIGNAL(clicked()),this,SLOT(slot_btnOK_Clicked()));
	connect(m_pBtnCancel,SIGNAL(clicked()),this,SLOT(slot_btnCancel_Clicked()));
	connect(m_pResultTableWidget,SIGNAL(cellChanged(int, int)),this,SLOT(slot_cellClicked(int, int)));

	connect(m_pCmbActionTime, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(m_pCmbUAct, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(m_pCmbDvdtClose, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(m_pCmbTripILock, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
}
void QLowVolAssessDlg::slot_btnCancel_Clicked()
{
	reject();
}

void QLowVolAssessDlg::UpdataResultAssess()
{
	CDvmData *pData = NULL;
	long nValue;
	float fValue;

	pData = (CDvmData *)m_pLowVolAssessDataGroup->FindByID(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_RELERR);
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pItem1 = new QTableWidgetItem(QString::number(nValue, 'f', 3));
		m_pItem1->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(0, 2, m_pItem1);
	}

	pData = (CDvmData *)m_pLowVolAssessDataGroup->FindByID(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_ABSERRPOS);
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		m_pItem2 = new QTableWidgetItem(QString::number(fValue, 'f', 3));
		m_pItem2->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(0, 3, m_pItem2);
	}

	pData = (CDvmData *)m_pLowVolAssessDataGroup->FindByID(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_ABSERRNEG);
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		m_pItem3 = new QTableWidgetItem(QString::number(fValue, 'f', 3));
		m_pItem3->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(0, 4, m_pItem3);
	}

	pData = (CDvmData *)m_pLowVolAssessDataGroup->FindByID(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_RELERR);
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pItem4 = new QTableWidgetItem(QString::number(nValue, 'f', 3));
		m_pItem4->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(1, 2, m_pItem4);
	}

	pData = (CDvmData *)m_pLowVolAssessDataGroup->FindByID(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_ABSERR);
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		m_pItem5 = new QTableWidgetItem(QString::number(fValue, 'f', 3));
		m_pItem5->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(1, 3, m_pItem5);
	}

	pData = (CDvmData *)m_pLowVolAssessDataGroup->FindByID(STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_RELERR);
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pItem6 = new QTableWidgetItem(QString::number(nValue, 'f', 3));
		m_pItem6->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(2, 2, m_pItem6);
	}

	pData = (CDvmData *)m_pLowVolAssessDataGroup->FindByID(STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_ABSERR);
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		m_pItem7 = new QTableWidgetItem(QString::number(fValue, 'f', 3));
		m_pItem7->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(2, 3, m_pItem7);
	}

	pData = (CDvmData *)m_pLowVolAssessDataGroup->FindByID(STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_RELERR);
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		m_pItem8 = new QTableWidgetItem(QString::number(fValue, 'f', 3));
		m_pItem8->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(3, 2, m_pItem8);
	}

	pData = (CDvmData *)m_pLowVolAssessDataGroup->FindByID(STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_ABSERR);
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		m_pItem9 = new QTableWidgetItem(QString::number(fValue, 'f', 3));
		m_pItem9->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(3, 3, m_pItem9);
	}

	pData = (CDvmData *)m_pLowVolAssessDataGroup->FindByID(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTTIME_RSLTEVAL);
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pCmbActionTime->setCurrentIndex(nValue);
	}

	pData = (CDvmData *)m_pLowVolAssessDataGroup->FindByID(STT_MULTI_MACRO_LOWVOL_PARAS_ID_ACTVALUE_RSLTEVAL);
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pCmbUAct->setCurrentIndex(nValue);
	}

	pData = (CDvmData *)m_pLowVolAssessDataGroup->FindByID(STT_MULTI_MACRO_LOWVOL_PARAS_ID_SLIPTRIP_RSLTEVAL);
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pCmbDvdtClose->setCurrentIndex(nValue);
	}

	pData = (CDvmData *)m_pLowVolAssessDataGroup->FindByID(STT_MULTI_MACRO_LOWVOL_PARAS_ID_IBLOCK_RSLTEVAL);
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		m_pCmbTripILock->setCurrentIndex(nValue);
	}
}

void QLowVolAssessDlg::slot_cellClicked(int row ,int col)
{
	if (col == 2 && row >= 0 && row <= 3) 
	{
		QTableWidgetItem *item = m_pResultTableWidget->item(row, col);
		if (item) 
		{
			float fv = item->text().toFloat();
			fv = setLimit(0,100.000,fv);
			item->setText(QString::number(fv, 'f', 3)); 
		}
	}
	if (col == 3 && row >= 0 && row <= 3) 
	{
		QTableWidgetItem *item2 = m_pResultTableWidget->item(row, col);
		if (item2) 
		{
			float fv = item2->text().toFloat();
			fv = setLimit(0,200.000,fv);
			item2->setText(QString::number(fv, 'f', 3)); 
		}
	}
	if (col == 4 && row == 0 )
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
