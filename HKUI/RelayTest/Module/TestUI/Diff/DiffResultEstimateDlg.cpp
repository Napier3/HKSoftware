#include "DiffResultEstimateDlg.h"
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

extern void  Stt_Global_SettingParent(QWidget *parent);		//20240802 huangliang 

QDiffResultEstimateDlg::QDiffResultEstimateDlg(CDataGroup *m_oDiffDataGroup, QWidget *parent) : QDialog(parent)
{
	m_pParas = m_oDiffDataGroup;
		// 在2k分辨率150%缩放下显示不全
#ifdef _PSX_QT_WINDOWS_
		QDesktopWidget* desktopWidget = QApplication::desktop();
		QRect rect = desktopWidget->screenGeometry();
		float fWidth = rect.width() * g_dUIShowCoef;

		if (fWidth >= 2280)
		{
			resize(950, 300);
		}
		else
		{
			resize(950, 225);
		}
#else
		resize(950, 225);
#endif // _PSX_QT_WINDOWS_
		InitUI();
		InitFont();
		InitConnections();
}

QDiffResultEstimateDlg::~QDiffResultEstimateDlg()
{
}
void QDiffResultEstimateDlg::InitUI()
{
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::Dialog);
	m_pResultTableWidget = new QTableWidget(3, 5, this);

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
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
	//m_pResultTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	m_pResultTableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
	//Sections
	m_pResultTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 设置固定列宽
	m_pResultTableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch); // 设置固定行高
#else
	m_pResultTableWidget->horizontalHeader()->setResizeMode(QHeaderView::Fixed); // 设置固定列宽
	m_pResultTableWidget->verticalHeader()->setResizeMode(QHeaderView::Fixed); // 设置固定行高
#endif

	long nMinAxis = 0;
	m_pParas->GetDataValue(STT_MULTI_MACRO_DIFF_PARAS_ID_CHAR_MINAXIS, nMinAxis);
	CString strLabRateName, strLabHarmName;
	if (nMinAxis)
	{
		strLabRateName = g_sLangTxt_Native_TestPrecision + "(Ie):";
		strLabHarmName = g_sLangTxt_State_Harmonicbraking + "(Ie):";
	}
	else
	{
		strLabRateName = g_sLangTxt_Native_TestPrecision + "(A):";
		strLabHarmName = g_sLangTxt_State_Harmonicbraking + "(A):";
	}

	m_pLabRateName = new QLabel(strLabRateName);
	m_pResultTableWidget->setCellWidget(0, 0, m_pLabRateName);

	m_pLabTimeName = new QLabel(g_sLangTxt_Native_ActionTime);
	m_pResultTableWidget->setCellWidget(1, 0, m_pLabTimeName);

	m_pLabHarmName = new QLabel(strLabHarmName);
	m_pResultTableWidget->setCellWidget(2, 0, m_pLabHarmName);

	m_pLabRateNeg = new QLabel("--");
	m_pResultTableWidget->setCellWidget(0, 4, m_pLabRateNeg);

	m_pLabRateName->setAlignment(Qt::AlignCenter);
	m_pLabTimeName->setAlignment(Qt::AlignCenter);
	m_pLabHarmName->setAlignment(Qt::AlignCenter);
	m_pLabRateNeg->setAlignment(Qt::AlignCenter);

	m_pCmbRate = new QComboBox(m_pResultTableWidget);
	m_pCmbTime = new QComboBox(m_pResultTableWidget);
	m_pCmbHarm = new QComboBox(m_pResultTableWidget);

	m_pCmbRate->setObjectName("0");
	m_pCmbTime->setObjectName("1");
	m_pCmbHarm->setObjectName("2");

	QStringList headers1;
	headers1 << /*"绝对误差"*/g_sLangTxt_StateEstimate_AbsError
		<< /*"相对误差"*/g_sLangTxt_StateEstimate_RelError
		<< /*"绝对or相对"*/ g_sLangTxt_CBOperate_AbsOrRelative
		<< /*"绝对&相对"*/g_sLangTxt_CBOperate_AbsRelative
		//<< /*"组合误差"*/g_sLangTxt_CBOperate_CombError
		<<	/*"不评估"*/g_sLangTxt_Distance_ErrorNot;
	m_pCmbRate->addItems(headers1);
	m_pCmbTime->addItems(headers1);
	m_pCmbHarm->addItems(headers1);

	m_pResultTableWidget->setCellWidget(0, 1, m_pCmbRate);
	m_pResultTableWidget->setCellWidget(1, 1, m_pCmbTime);
	m_pResultTableWidget->setCellWidget(2, 1, m_pCmbHarm);

	ComboxModelStyle(m_pCmbRate);
	ComboxModelStyle(m_pCmbTime);
	ComboxModelStyle(m_pCmbHarm);

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

	CbbErrorType(0, m_pCmbRate->currentText());
	CbbErrorType(1, m_pCmbTime->currentText());
	CbbErrorType(2, m_pCmbHarm->currentText());
}
void QDiffResultEstimateDlg::slot_cmbErrorChanged(const QString& strText)
{
	QObject *senderObj = sender();
	CString strName;
	if (senderObj) {
		strName = senderObj->objectName();
	}
	CbbErrorType(strName.toInt(), strText);
}
void QDiffResultEstimateDlg::CbbErrorType(int nIndex, CString strText)
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

void QDiffResultEstimateDlg::SetItemEnable(int nRow, int nCol, BOOL bEnable)
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
void QDiffResultEstimateDlg::ComboxModelStyle(QComboBox *pCombox)
{
	pCombox->setEditable(true);
	pCombox->lineEdit()->setAlignment(Qt::AlignCenter);
	pCombox->lineEdit()->setReadOnly(true);
	pCombox->lineEdit()->setMouseTracking(true);
	pCombox->lineEdit()->setStyleSheet("background:transparent;border-width:0;border-style:outset");
	pCombox->lineEdit()->setAttribute(Qt::WA_TransparentForMouseEvents);
	pCombox->setEnabled(true);
}
void QDiffResultEstimateDlg::InitFont()
{
	m_pCmbRate->setFont(*g_pSttGlobalFont);
	m_pCmbTime->setFont(*g_pSttGlobalFont);
	m_pCmbHarm->setFont(*g_pSttGlobalFont);

	m_pResultTableWidget->setFont(*g_pSttGlobalFont);
	m_pResultTableWidget->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pBtnOK->setFont(*g_pSttGlobalFont);
	m_pBtnCancel->setFont(*g_pSttGlobalFont);

	m_pLabRateName->setFont(*g_pSttGlobalFont);
	m_pLabTimeName->setFont(*g_pSttGlobalFont);
	m_pLabHarmName->setFont(*g_pSttGlobalFont);
	m_pLabRateNeg->setFont(*g_pSttGlobalFont);

}
void QDiffResultEstimateDlg::slot_btnOK_Clicked()
{
	long nRate = m_pCmbRate->currentIndex();
	long nTime = m_pCmbTime->currentIndex();
	long nHarm = m_pCmbHarm->currentIndex();


	float fRateRelErr = m_pResultTableWidget->item(0, 2)->text().toFloat();
	float fRateAbsErr = m_pResultTableWidget->item(0, 3)->text().toFloat();

	float fTimeRelErr = m_pResultTableWidget->item(1, 2)->text().toFloat();
	float fTimeAbsErrPos = m_pResultTableWidget->item(1, 3)->text().toFloat();
	float fTimeAbsErrNeg = m_pResultTableWidget->item(1, 4)->text().toFloat();

	float fHarmRelErr = m_pResultTableWidget->item(2, 2)->text().toFloat();
	float fHarmAbsErrPos = m_pResultTableWidget->item(2, 3)->text().toFloat();
	float fHarmAbsErrNeg = m_pResultTableWidget->item(2, 4)->text().toFloat();

	CDvmData *pData = NULL;

	if (m_pParas == NULL)
	{
		return;
	}

	pData = (CDvmData *)m_pParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_RATE_RSLTEVAL);
	if (pData != NULL)
	{
		if (nRate == 4)//不评估
		{
			pData->m_strValue = QString::number(5);
		}
		else
		{
			pData->m_strValue = QString::number(nRate);
		}
	}

	pData = (CDvmData *)m_pParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_TIME_RSLTEVAL);
	if (pData != NULL)
	{
		if (nTime == 4)//不评估
		{
			pData->m_strValue = QString::number(5);
		}
		else
		{
			pData->m_strValue = QString::number(nTime);
		}
	}

	pData = (CDvmData *)m_pParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_HARM_RSLTEVAL);
	if (pData != NULL)
	{
		if (nHarm == 4)//不评估
		{
			pData->m_strValue = QString::number(5);
		}
		else
		{
			pData->m_strValue = QString::number(nHarm);
		}
	}

	pData = (CDvmData *)m_pParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_RATE_ABSERR);
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(fRateRelErr, 'f', 3);
	}

	pData = (CDvmData *)m_pParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_RATE_RELERR);
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(fRateAbsErr, 'f', 3);
	}

	pData = (CDvmData *)m_pParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_TIME_RELERR);
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(fHarmRelErr, 'f', 3);
	}

	pData = (CDvmData *)m_pParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_TIME_ABSERRPOS);
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(fHarmAbsErrPos, 'f', 3);
	}

	pData = (CDvmData *)m_pParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_TIME_ABSERRNEG);
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(fHarmAbsErrNeg, 'f', 3);
	}

	pData = (CDvmData *)m_pParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_HARM_RELERR);
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(fTimeRelErr, 'f', 3);
	}

	pData = (CDvmData *)m_pParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_HARM_ABSERRPOS);
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(fTimeAbsErrPos, 'f', 3);
	}

	pData = (CDvmData *)m_pParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_HARM_ABSERRNEG);
	if (pData != NULL)
	{
		pData->m_strValue = QString::number(fTimeAbsErrNeg, 'f', 3);
	}

	accept();
}

void QDiffResultEstimateDlg::UpdataResultAssess()
{
	CDvmData *pData = NULL;
	long nValue;
	float fValue;


	if (m_pParas == NULL)
	{
		return;
	}

	pData = (CDvmData *)m_pParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_RATE_RSLTEVAL);
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		if (nValue == 5)
		{
			m_pCmbRate->setCurrentIndex(4);
		}
		else
		{
			m_pCmbRate->setCurrentIndex(nValue);
		}
	}

	pData = (CDvmData *)m_pParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_TIME_RSLTEVAL);
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		if (nValue == 5)
		{
			m_pCmbTime->setCurrentIndex(4);
		}
		else
		{
			m_pCmbTime->setCurrentIndex(nValue);
		}
	}

	pData = (CDvmData *)m_pParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_HARM_RSLTEVAL);
	if (pData != NULL)
	{
		nValue = CString_To_long(pData->m_strValue);
		if (nValue == 5)
		{
			m_pCmbHarm->setCurrentIndex(4);
		}
		else
		{
			m_pCmbHarm->setCurrentIndex(nValue);
		}
	}

	pData = (CDvmData *)m_pParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_RATE_ABSERR);
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		m_pItem1 = new QTableWidgetItem(QString::number(fValue, 'f', 3));
		m_pItem1->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(0, 2, m_pItem1);
	}

	pData = (CDvmData *)m_pParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_RATE_RELERR);
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		m_pItem2 = new QTableWidgetItem(QString::number(fValue, 'f', 3));
		m_pItem2->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(0, 3, m_pItem2);
	}

	pData = (CDvmData *)m_pParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_TIME_RELERR);
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		m_pItem3 = new QTableWidgetItem(QString::number(fValue, 'f', 3));
		m_pItem3->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(1, 2, m_pItem3);
	}

	pData = (CDvmData *)m_pParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_TIME_ABSERRPOS);
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		m_pItem4 = new QTableWidgetItem(QString::number(fValue, 'f', 3));
		m_pItem4->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(1, 3, m_pItem4);
	}

	pData = (CDvmData *)m_pParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_TIME_ABSERRNEG);
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		m_pItem5 = new QTableWidgetItem(QString::number(fValue, 'f', 3));
		m_pItem5->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(1, 4, m_pItem5);
	}

	pData = (CDvmData *)m_pParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_HARM_RELERR);
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		m_pItem6 = new QTableWidgetItem(QString::number(fValue, 'f', 3));
		m_pItem6->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(2, 2, m_pItem6);
	}

	pData = (CDvmData *)m_pParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_HARM_ABSERRPOS);
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		m_pItem7 = new QTableWidgetItem(QString::number(fValue, 'f', 3));
		m_pItem7->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(2, 3, m_pItem7);
	}

	pData = (CDvmData *)m_pParas->FindByID(STT_MULTI_MACRO_DIFF_PARAS_ID_R_HARM_ABSERRNEG);
	if (pData != NULL)
	{
		fValue = CString_To_double(pData->m_strValue);
		m_pItem8 = new QTableWidgetItem(QString::number(fValue, 'f', 3));
		m_pItem8->setTextAlignment(Qt::AlignCenter);
		m_pResultTableWidget->setItem(2, 4, m_pItem8);
	}
}

void QDiffResultEstimateDlg::InitConnections()
{
	connect(m_pBtnOK, SIGNAL(clicked()), this, SLOT(slot_btnOK_Clicked()));
	connect(m_pBtnCancel, SIGNAL(clicked()), this, SLOT(slot_btnCancel_Clicked()));

	connect(m_pResultTableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(slot_cellClicked(int, int)));
	connect(m_pCmbRate, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(m_pCmbTime, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(m_pCmbHarm, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
}

void QDiffResultEstimateDlg::slot_btnCancel_Clicked()
{
	reject();
}

void QDiffResultEstimateDlg::slot_cellClicked(int row, int col)
{
	if (col == 2 && row >= 0 && row <= 4)
	{
		QTableWidgetItem *item = m_pResultTableWidget->item(row, col);
		if (item)
		{
			float fv = item->text().toFloat();
			fv = setLimit(0, 100.000, fv);
			item->setText(QString::number(fv, 'f', 3));
		}
	}
	if (col == 3 && row >= 0 && row <= 4)
	{
		QTableWidgetItem *item2 = m_pResultTableWidget->item(row, col);
		if (item2)
		{
			float fv = item2->text().toFloat();
			fv = setLimit(0, 200.000, fv);
			item2->setText(QString::number(fv, 'f', 3));
		}
	}

	if (col == 4 && row != 0)
	{
		QTableWidgetItem *item3 = m_pResultTableWidget->item(row, col);
		if (item3)
		{
			float fv = item3->text().toFloat();
			fv = setLimit(0, 200.000, fv);
			item3->setText(QString::number(fv, 'f', 3));
		}
	}
	else
	{
		return;
	}
}
