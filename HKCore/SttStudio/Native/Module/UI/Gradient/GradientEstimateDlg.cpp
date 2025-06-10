#include "GradientEstimateDlg.h"
#include "../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include <QBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QHeaderView>
#include "../../XLangResource_Native.h"
#include "../Module/CommonMethod/commonMethod.h"
GradientEstimateGrid::GradientEstimateGrid(int rows, int columns, QWidget* parent) : QTableWidget(rows, columns, parent)
{
	m_bRunning = FALSE;
	installEventFilter(this);
}

GradientEstimateGrid::~GradientEstimateGrid()
{

}

void GradientEstimateGrid::InitGrid()
{
	CString strName, strErrorType, strRelError, strAbsError, strSettingValue;
	xlang_GetLangStrByFile(strName, "sName");
	xlang_GetLangStrByFile(strErrorType, "StateEstimate_ErrorType");
	//strErrorType = "误差类型";
	strRelError = g_sLangTxt_StateEstimate_RelError;
	strRelError += "(%)";
	//strRelError = "相对误差(%)";
	//strAbsError = "绝对误差";
	//strSettingValue = "整定值";
	xlang_GetLangStrByFile(strAbsError, "StateEstimate_AbsError");
	xlang_GetLangStrByFile(strSettingValue, "State_SettingValue");

	setHorizontalHeaderLabels(QStringList() << strName << strErrorType << strRelError << strAbsError << strSettingValue);
	setColumnWidth(0, 120);
	setColumnWidth(1, 150);
	setColumnWidth(4, 80);
	this->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
	this->setStyleSheet("selection-background-color: grey;selection-color: black");
}

void GradientEstimateGrid::EnableRow(long nIndex, BOOL bEnabled)
{
	if(nIndex >= rowCount())
	{
		return;
	}

	QComboBox* pCbb = (QComboBox*)cellWidget(nIndex, 1);
	pCbb->setEnabled(bEnabled);
	if(bEnabled)
	{
		QTableWidgetItem* pItem = pItem = item(nIndex, 2);
		pItem->setFlags(pItem->flags() | Qt::ItemIsEnabled);
		pItem = item(nIndex, 3);
		pItem->setFlags(pItem->flags() | Qt::ItemIsEnabled);
	}
	else
	{
		QTableWidgetItem* pItem = pItem = item(nIndex, 2);
		pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled);
		pItem = item(nIndex, 3);
		pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled);
	}
}

QComboBox* GradientEstimateGrid::NewErrorType()
{
	CString strText;

	QComboBox *pCbbError = new QComboBox(this);
	pCbbError->addItem(/*"绝对误差"*/g_sLangTxt_StateEstimate_AbsError);
	pCbbError->addItem(/*"相对误差"*/g_sLangTxt_StateEstimate_RelError);

	strText = g_sLangTxt_StateEstimate_AbsError +"or"+g_sLangTxt_StateEstimate_RelError;
	pCbbError->addItem(/*"相对误差or绝对误差"*/strText);

	strText = g_sLangTxt_StateEstimate_AbsError +"&"+g_sLangTxt_StateEstimate_RelError;
	pCbbError->addItem(/*"相对误差&绝对误差"*/strText);
	//pCbbError->addItem("组合误差");
	return pCbbError;
}

QComboBox* GradientEstimateGrid::AbsErrorType()
{
	QComboBox *pCbbError = new QComboBox(this);
	pCbbError->addItem(/*"绝对误差"*/g_sLangTxt_StateEstimate_AbsError);
	return pCbbError;
}


void GradientEstimateGrid::InitData(tmt_GradientParasEx* pParas)
{
	m_pParas=pParas;
	QComboBox *pCbbError1 = NewErrorType();
	pCbbError1->setCurrentIndex(pParas->m_nUActVal_ErrorLogic);
	QComboBox *pCbbError2 = NewErrorType();
	pCbbError2->setCurrentIndex(pParas->m_nIActVal_ErrorLogic);
	QComboBox *pCbbError3 = AbsErrorType();
	pCbbError3->setCurrentIndex(pParas->m_nAngleActVal_ErrorLogic);
	QComboBox *pCbbError4 = AbsErrorType();
	pCbbError4->setCurrentIndex(pParas->m_nHzActVal_ErrorLogic);
	QComboBox *pCbbError5 = AbsErrorType();
	pCbbError5->setCurrentIndex(pParas->m_nRetCoef_ErrorLogic);
	QComboBox *pCbbError6 = AbsErrorType();
	pCbbError6->setCurrentIndex(pParas->m_nMaxAngle_ErrorLogic);
	QComboBox *pCbbError7 = AbsErrorType();
	pCbbError7->setCurrentIndex(pParas->m_nAngleF_ErrorLogic);
	QComboBox *pCbbError8 = AbsErrorType();
	pCbbError8->setCurrentIndex(pParas->m_nAngleS_ErrorLogic);

	CString strText; 
	//strText = "电压动作值(V)";
	strText = g_sLangTxt_Gradient_VActionValue;//lcq
	setItem(0, 0, new QTableWidgetItem(strText));
	//strText = "电流动作值(A)";
	strText = g_sLangTxt_Gradient_CActionValue;
	setItem(1, 0, new QTableWidgetItem(strText));
	//strText = "返回系数";
	strText = g_sLangTxt_Gradient_ReCoefficient;
	setItem(2, 0, new QTableWidgetItem(strText));
	//strText = "边界角1(°)";
	strText = g_sLangTxt_Gradient_FirBoundAngle;
	setItem(3, 0, new QTableWidgetItem(strText));
	//strText = "边界角2(°)";
	strText = g_sLangTxt_Gradient_SecBoundAngle;
	setItem(4, 0, new QTableWidgetItem(strText));
	//strText = "最大灵敏角(°)";
	strText = g_sLangTxt_Gradient_MaxSenAngle;
	setItem(5, 0, new QTableWidgetItem(strText));
	//strText = "动作频率(Hz)";
	strText = g_sLangTxt_Gradient_FreAction;
	setItem(6, 0, new QTableWidgetItem(strText));
	//strText = "相位动作值(°)";
	strText = g_sLangTxt_Gradient_PhaseAValue;
	setItem(7, 0, new QTableWidgetItem(strText));

	setCellWidget(0, 1, pCbbError1);
	setCellWidget(1, 1, pCbbError2);
	setCellWidget(2, 1, pCbbError3);
	setCellWidget(3, 1, pCbbError4);
	setCellWidget(4, 1, pCbbError5);
	setCellWidget(5, 1, pCbbError6);
	setCellWidget(6, 1, pCbbError7);
	setCellWidget(7, 1, pCbbError8);

	ComboxModelStyle(pCbbError1);
	ComboxModelStyle(pCbbError2);
	ComboxModelStyle(pCbbError3);
	ComboxModelStyle(pCbbError4);
	ComboxModelStyle(pCbbError5);
	ComboxModelStyle(pCbbError6);
	ComboxModelStyle(pCbbError7);
	ComboxModelStyle(pCbbError8);

	setItem(0, 2, new QTableWidgetItem(QString::number(pParas->m_fUActVal_RelErr)));
	setItem(1, 2, new QTableWidgetItem(QString::number(pParas->m_fIActVal_RelErr)));
	setItem(2, 2, new QTableWidgetItem(QString::number(pParas->m_fRetCoef_RelErr)));
	setItem(3, 2, new QTableWidgetItem(QString::number(pParas->m_fAngleF_RelErr)));
	setItem(4, 2, new QTableWidgetItem(QString::number(pParas->m_fAngleS_RelErr)));
	setItem(5, 2, new QTableWidgetItem(QString::number(pParas->m_fMaxAngle_RelErr)));
	setItem(6, 2, new QTableWidgetItem(QString::number(pParas->m_fHzActVal_RelErr)));
	setItem(7, 2, new QTableWidgetItem(QString::number(pParas->m_fAngleActVal_RelErr)));
	setItem(0, 3, new QTableWidgetItem(QString::number(pParas->m_fUActVal_AbsErr)));
	setItem(1, 3, new QTableWidgetItem(QString::number(pParas->m_fIActVal_AbsErr)));
	setItem(2, 3, new QTableWidgetItem(QString::number(pParas->m_fRetCoef_AbsErr)));
	setItem(3, 3, new QTableWidgetItem(QString::number(pParas->m_fAngleF_AbsErr)));
	setItem(4, 3, new QTableWidgetItem(QString::number(pParas->m_fAngleS_AbsErr)));
	setItem(5, 3, new QTableWidgetItem(QString::number(pParas->m_fMaxAngle_AbsErr)));
	setItem(6, 3, new QTableWidgetItem(QString::number(pParas->m_fHzActVal_AbsErr)));
	setItem(7, 3, new QTableWidgetItem(QString::number(pParas->m_fAngleActVal_AbsErr)));
	setItem(0, 4, new QTableWidgetItem(QString::number(pParas->m_fUSet)));
	setItem(1, 4, new QTableWidgetItem(QString::number(pParas->m_fISet)));
	setItem(2, 4, new QTableWidgetItem(QString::number(pParas->m_fRetCoefSet)));
	setItem(3, 4, new QTableWidgetItem(QString::number(pParas->m_fAngleFSet)));
	setItem(4, 4, new QTableWidgetItem(QString::number(pParas->m_fAngleSSet)));
	setItem(5, 4, new QTableWidgetItem(QString::number(pParas->m_fMaxAngleSet)));
	setItem(6, 4, new QTableWidgetItem(QString::number(pParas->m_fHzSet)));
	setItem(7, 4, new QTableWidgetItem(QString::number(pParas->m_fAngleSet)));


	for (int i = 0 ;i < 5 ;i++)
	{
		if (i != 1)
		{
			item(0,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			item(1,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			item(2,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			item(3,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			item(4,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			item(5,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			item(6,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
			item(7,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
		}
		
	}

	for (int i = 0; i < 8; i++)
	{
		item(i, 0)->setFlags(item(i, 0)->flags() & ~Qt::ItemIsEditable);
		EnableRow(i, FALSE);
	}

	if(pParas->m_nType == 0)
	{
		//幅值
		if(pParas->m_nTestMode == 0)
		{
			//动作值
			if(pParas->m_nVarIndexType == 0)
			{
				//电流
				EnableRow(1);
			}
			else if(pParas->m_nVarIndexType == 1)
			{
				//电压
				EnableRow(0);
			}
		}
		else if(pParas->m_nTestMode == 1)
		{
			//返回系数
			EnableRow(2);
		}
	}
	else if (pParas->m_nType == 1)
	{
		//相位
		if(pParas->m_nTestMode == 0)
		{
			//动作值
			EnableRow(7);
		}
		else if(pParas->m_nTestMode == 1)
		{
			//返回系数
			EnableRow(2);
		}
		else if(pParas->m_nTestMode == 2)
		{
			//最大灵敏角
			EnableRow(3);
			EnableRow(4);
			EnableRow(5);
		}
	}
	else if (pParas->m_nType == 2)
	{
		//频率
		EnableRow(6);
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
	connect(pCbbError1, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError2, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError3, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError4, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError5, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError6, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError7, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));
	connect(pCbbError8, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(slot_cmbErrorChanged(const QString &)));


	CbbErrorType(0,pCbbError1->currentText());
	CbbErrorType(1,pCbbError2->currentText());
	CbbErrorType(2,pCbbError3->currentText());
	CbbErrorType(3,pCbbError4->currentText());
	CbbErrorType(4,pCbbError5->currentText());
	CbbErrorType(5,pCbbError6->currentText());
	CbbErrorType(6,pCbbError7->currentText());
	CbbErrorType(7,pCbbError8->currentText());
}

void GradientEstimateGrid::ComboxModelStyle(QComboBox *pCombox)
{
	pCombox->setEditable(true);
	pCombox->lineEdit()->setAlignment(Qt::AlignCenter);
	pCombox->lineEdit()->setReadOnly(true);
	pCombox->lineEdit()->setMouseTracking(true);
	pCombox->lineEdit()->setStyleSheet("background:transparent;border-width:0;border-style:outset");
	pCombox->lineEdit()->setAttribute(Qt::WA_TransparentForMouseEvents);
}



void GradientEstimateGrid::CbbErrorType(int nIndex, CString strText)
{
	if (strText==g_sLangTxt_StateEstimate_AbsError)//绝对误差
	{
		item(nIndex, 2)->setFlags(item(nIndex, 2)->flags() & ~Qt::ItemIsEditable);
		item(nIndex, 3)->setFlags(item(nIndex, 3)->flags() &  Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
	}
	else if (strText==g_sLangTxt_StateEstimate_RelError)//相对误差
	{
		item(nIndex, 2)->setFlags(item(nIndex, 2)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		item(nIndex, 3)->setFlags(item(nIndex, 3)->flags() & ~Qt::ItemIsEditable);
	}
	else
	{
		item(nIndex, 2)->setFlags(item(nIndex, 2)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		item(nIndex, 3)->setFlags(item(nIndex, 3)->flags() & Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
	}
}

void GradientEstimateGrid::slot_cmbErrorChanged(const QString& strText)
{
	int nRow = currentRow();
	CbbErrorType(nRow,strText);
}

void GradientEstimateGrid::slot_OnCellChanged(int row,int col)
{
	if (row  <  0)
	{
		return;
	}

	disconnect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)));

	QTableWidgetItem  *pItem  = this->item(row,col);

	if (pItem == NULL)
	{
		return;
	} 

	QString str = pItem->text();
	float fv =str.toFloat();

	if (col==1)
	{
		pItem->setText(str);
	}

	if(col==2)//相对误差
	{
		fv=setLimit(0,100,fv);
		pItem->setText(QString::number(fv));
	}

	if(col==3)//绝对误差
	{
		fv=setLimit(0,200,fv);
		pItem->setText(QString::number(fv));
	}

	if(col==4)//整定值
	{
		if (row==0)
		{
			fv=setLimit(0,120,fv);
			pItem->setText(QString::number(fv));
		}
		if (row==1)
		{
			fv=setLimit(0,10,fv);
			pItem->setText(QString::number(fv));
		}
		if (row==2)
		{
			fv=setLimit(0,999,fv);
			pItem->setText(QString::number(fv));
		}
		if (row==3)
		{
			fv=setLimit(0,360,fv);
			pItem->setText(QString::number(fv));
		}
		if (row==4)
		{
			fv=setLimit(0,360,fv);
			pItem->setText(QString::number(fv));
		}
		if (row==5)
		{
			fv=setLimit(0,360,fv);
			pItem->setText(QString::number(fv));
		}
		if (row==6)
		{
			fv=setLimit(0,1550,fv);
			pItem->setText(QString::number(fv));
		}
		if (row==7)
		{
			fv=setLimit(0,360,fv);
			pItem->setText(QString::number(fv));
		}
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}

bool GradientEstimateGrid::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent *pMouseEvent = (QMouseEvent *)event;
		m_bRunning = TRUE;
		mouseDoubleClickEvent((QMouseEvent *)pMouseEvent);
		m_bRunning = FALSE;
		return true;
	}

	return QTableWidget::eventFilter(obj,event);
}

void GradientEstimateGrid::mousePressEvent(QMouseEvent * event)
{
	if (m_bRunning)
	{
		QTableWidget::mousePressEvent(event);
		return;
	}

	QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick,event->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
	QApplication::postEvent(this,pEvent);
	QTableWidget::mousePressEvent(event);
}

GradientEstimateDlg::GradientEstimateDlg(tmt_GradientParasEx* pParas, QWidget* parent) : QDialog(parent)
{
	m_pGrid = NULL;
	m_pParas = pParas;
	InitUI();
}

GradientEstimateDlg::~GradientEstimateDlg()
{

}

void GradientEstimateDlg::InitUI()
{
	//CString strTitle = "结果评估";
	CString strTitle = g_sLangTxt_StateEstimate_ResultEstimate; //lcq
	setWindowTitle(strTitle);
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);

	QVBoxLayout* pVLayout = new QVBoxLayout(this);
	setLayout(pVLayout);

	QHBoxLayout* pHLayout = new QHBoxLayout(this);
	m_pGrid = new GradientEstimateGrid(8, 5, this);
	m_pGrid->InitGrid();
	m_pGrid->InitData(m_pParas);
	pHLayout->addWidget(m_pGrid);
	pVLayout->addLayout(pHLayout);
	
	CString strText;
	pHLayout = new QHBoxLayout(this);
	pHLayout->addStretch();
	QPushButton* pBtn = new QPushButton(this);
	xlang_GetLangStrByFile(strText, "sOK");
	pBtn->setText(strText);
	connect(pBtn, SIGNAL(clicked()), this, SLOT(slot_btnOK_Clicked()));
	pHLayout->addWidget(pBtn);
	pBtn = new QPushButton(this);
	xlang_GetLangStrByFile(strText, "sCancel");
	pBtn->setText(strText);
	connect(pBtn, SIGNAL(clicked()), this, SLOT(slot_btnCancel_Clicked()));
	pHLayout->addWidget(pBtn);
	pHLayout->addStretch();
	pVLayout->addLayout(pHLayout);

	resize(600, 400);
}

void GradientEstimateDlg::slot_btnOK_Clicked()
{
 	m_pParas->m_fUActVal_RelErr = m_pGrid->item(0, 2)->text().toFloat();
	m_pParas->m_fIActVal_RelErr = m_pGrid->item(1, 2)->text().toFloat();
	m_pParas->m_fRetCoef_RelErr = m_pGrid->item(2, 2)->text().toFloat();
	m_pParas->m_fAngleF_RelErr = m_pGrid->item(3, 2)->text().toFloat();
	m_pParas->m_fAngleS_RelErr = m_pGrid->item(4, 2)->text().toFloat();
	m_pParas->m_fMaxAngle_RelErr = m_pGrid->item(5, 2)->text().toFloat();
	m_pParas->m_fHzActVal_RelErr = m_pGrid->item(6, 2)->text().toFloat();
	m_pParas->m_fAngleActVal_RelErr = m_pGrid->item(7, 2)->text().toFloat();
	m_pParas->m_fUActVal_AbsErr = m_pGrid->item(0, 3)->text().toFloat();
	m_pParas->m_fIActVal_AbsErr = m_pGrid->item(1, 3)->text().toFloat();
	m_pParas->m_fRetCoef_AbsErr = m_pGrid->item(2, 3)->text().toFloat();
	m_pParas->m_fAngleF_AbsErr = m_pGrid->item(3, 3)->text().toFloat();
	m_pParas->m_fAngleS_AbsErr = m_pGrid->item(4, 3)->text().toFloat();
	m_pParas->m_fMaxAngle_AbsErr = m_pGrid->item(5, 3)->text().toFloat();
	m_pParas->m_fHzActVal_AbsErr = m_pGrid->item(6, 3)->text().toFloat();
	m_pParas->m_fAngleActVal_AbsErr = m_pGrid->item(7, 3)->text().toFloat();
	m_pParas->m_nUActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(0, 1))->currentIndex();
	m_pParas->m_nIActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(1, 1))->currentIndex();
	m_pParas->m_nAngleActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(2, 1))->currentIndex();
	m_pParas->m_nHzActVal_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(3, 1))->currentIndex();
	m_pParas->m_nRetCoef_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(4, 1))->currentIndex();
	m_pParas->m_nMaxAngle_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(5, 1))->currentIndex();
	m_pParas->m_nAngleF_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(6, 1))->currentIndex();
	m_pParas->m_nAngleS_ErrorLogic = ((QComboBox*)m_pGrid->cellWidget(7, 1))->currentIndex();
	m_pParas->m_fUSet = m_pGrid->item(0, 4)->text().toFloat();
	m_pParas->m_fISet = m_pGrid->item(1, 4)->text().toFloat();
	m_pParas->m_fRetCoefSet = m_pGrid->item(2, 4)->text().toFloat();
	m_pParas->m_fAngleFSet = m_pGrid->item(3, 4)->text().toFloat();
	m_pParas->m_fAngleSSet = m_pGrid->item(4, 4)->text().toFloat();
	m_pParas->m_fMaxAngleSet = m_pGrid->item(5, 4)->text().toFloat();
	m_pParas->m_fHzSet = m_pGrid->item(6, 4)->text().toFloat();
	m_pParas->m_fAngleSet =	m_pGrid->item(7, 4)->text().toFloat();
	accept();
}

void GradientEstimateDlg::slot_btnCancel_Clicked()
{
	reject();
}



