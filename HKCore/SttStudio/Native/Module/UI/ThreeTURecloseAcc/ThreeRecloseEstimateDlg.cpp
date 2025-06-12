#include "ThreeRecloseEstimateDlg.h"
#include "../SttTestCntrFrameBase.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif

QThreeRecloseEstimateDlg::QThreeRecloseEstimateDlg( CDataGroup* pParas,QWidget* parent ): QDialog(parent)
{
	m_pParas = pParas;
	InitUI();
}

QThreeRecloseEstimateDlg::~QThreeRecloseEstimateDlg()
{

}

void QThreeRecloseEstimateDlg::InitUI()
{
    setWindowTitle("g_sLangTxt_StateEstimate_ResultEstimate");
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
	QVBoxLayout* pVLayout = new QVBoxLayout(this);
	setLayout(pVLayout);

	QHBoxLayout* pHLayout = new QHBoxLayout(this);
	m_pGrid = new QThreeRecloseEstimateGrid(m_pParas,this);
	pHLayout->addWidget(m_pGrid);
	pVLayout->addLayout(pHLayout);

	CString strText;
	pHLayout = new QHBoxLayout(this);
	pHLayout->addStretch();
	QPushButton* pBtn = new QPushButton(this);
	pBtn->setFont(*g_pSttGlobalFont);
	xlang_GetLangStrByFile(strText, "sOK");
	pBtn->setText(strText);
	connect(pBtn, SIGNAL(clicked()), this, SLOT(slot_btnOK_Clicked()));
	pHLayout->addWidget(pBtn);
	pBtn = new QPushButton(this);
	xlang_GetLangStrByFile(strText, "sCancel");
	pBtn->setFont(*g_pSttGlobalFont);
	pBtn->setText(strText);
	connect(pBtn, SIGNAL(clicked()), this, SLOT(slot_btnCancel_Clicked()));
	pHLayout->addWidget(pBtn);
	pHLayout->addStretch();
	pVLayout->addLayout(pHLayout);

	resize(800, 400);
}

void QThreeRecloseEstimateDlg::slot_btnOK_Clicked()
{
	m_pParas->SetDataValue(_T("Ttrip_RelErr"),m_pGrid->item(0, 2)->text().toFloat());
	m_pParas->SetDataValue(_T("TtripD_RelErr"),m_pGrid->item(1, 2)->text().toFloat());
	m_pParas->SetDataValue(_T("TtripD2_RelErr"),m_pGrid->item(2, 2)->text().toFloat());
	m_pParas->SetDataValue(_T("TtripD3_RelErr"),m_pGrid->item(3, 2)->text().toFloat());
	m_pParas->SetDataValue(_T("TtripAcc_RelErr"),m_pGrid->item(4, 2)->text().toFloat());

	m_pParas->SetDataValue(_T("Ttrip_AbsErr"),m_pGrid->item(0, 3)->text().toFloat());
	m_pParas->SetDataValue(_T("TtripD_AbsErr"),m_pGrid->item(1, 3)->text().toFloat());
	m_pParas->SetDataValue(_T("TtripD2_AbsErr"),m_pGrid->item(2, 3)->text().toFloat());
	m_pParas->SetDataValue(_T("TtripD3_AbsErr"),m_pGrid->item(3, 3)->text().toFloat());
	m_pParas->SetDataValue(_T("TtripAcc_AbsErr"),m_pGrid->item(4, 3)->text().toFloat());
	

	long nIndex = 0;
	nIndex = ((QComboBox*)m_pGrid->cellWidget(0, 1))->currentIndex();
	m_pParas->SetDataValue(_T("Ttrip_ErrorLogic"),nIndex);
	nIndex = ((QComboBox*)m_pGrid->cellWidget(1, 1))->currentIndex();
	m_pParas->SetDataValue(_T("TtripD_ErrorLogic"),nIndex);
	nIndex = ((QComboBox*)m_pGrid->cellWidget(2, 1))->currentIndex();
	m_pParas->SetDataValue(_T("TtripD2_ErrorLogic"),nIndex);
	nIndex = ((QComboBox*)m_pGrid->cellWidget(3, 1))->currentIndex();
	m_pParas->SetDataValue(_T("TtripD3_ErrorLogic"),nIndex);
	nIndex = ((QComboBox*)m_pGrid->cellWidget(4, 1))->currentIndex();
	m_pParas->SetDataValue(_T("TtripAcc_ErrorLogic"),nIndex);
	
	accept();
}

void QThreeRecloseEstimateDlg::slot_btnCancel_Clicked()
{
	close();
}

QThreeRecloseEstimateGrid::QThreeRecloseEstimateGrid( CDataGroup* pParas,QWidget* parent ): QTableWidget(parent)
{
	m_bRunning = FALSE;
	installEventFilter(this);
	m_pParas = pParas;
	InitUI();
}

QThreeRecloseEstimateGrid::~QThreeRecloseEstimateGrid()
{

}

void QThreeRecloseEstimateGrid::InitUI()
{
	QHeaderView* pLeft = verticalHeader();
	pLeft->setDefaultSectionSize(36);
	pLeft->setVisible(false);
	QHeaderView* pHeadTop = horizontalHeader();
    pHeadTop->setSectionsClickable(false);
    pHeadTop->setSectionsMovable(false);
 	QFont font1 = this->horizontalHeader()->font();
 	font1.setBold(true);
 	this->horizontalHeader()->setFont(font1);
	horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	setEditTriggers(QAbstractItemView::DoubleClicked);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
 	setFont(*g_pSttGlobalFont);
 	horizontalHeader()->setFont(*g_pSttGlobalFont);
	this->setStyleSheet("selection-background-color: grey;selection-color: black");
	InitTable();
}

void QThreeRecloseEstimateGrid::InitTable()
{
	QStringList  HStrList;
	HStrList << _T("名称") << _T("误差类型") <<  _T("相对误差(%)")<< _T("绝对误差");
	setColumnCount(4);
	setRowCount(5);
	setHorizontalHeaderLabels(HStrList);

	QTableWidgetItem *pItem = NULL;
	CString strText; 
	strText = _T("动作时间(s)");
	pItem = new QTableWidgetItem();
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	pItem->setText(strText);
	setItem(0, 0, pItem); 

	strText = _T("一次重合闸动作时间(s)");
	pItem = new QTableWidgetItem();
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	pItem->setText(strText);
	setItem(1, 0, pItem); 

	strText = _T("二次重合闸动作时间(s)");
	pItem = new QTableWidgetItem();
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	pItem->setText(strText);
	setItem(2, 0, pItem); 
	strText = _T("三次重合闸动作时间(s)");
	pItem = new QTableWidgetItem();
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	pItem->setText(strText);
	setItem(3, 0, pItem); 
	strText = _T("后加速动作时间(s)");
	pItem = new QTableWidgetItem();
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	pItem->setText(strText);
	setItem(4, 0, pItem); 


// 	QCenterComboBox *pCbbError1 = NewErrorType();
// 	GetComboxValue(_T("Ttrip_ErrorLogic"),pCbbError1);
// 	QCenterComboBox *pCbbError2 = NewErrorType();
// 	GetComboxValue(_T("TtripD_ErrorLogic"),pCbbError2);
// 	QCenterComboBox *pCbbError3 = NewErrorType();
// 	GetComboxValue(_T("TtripD2_ErrorLogic"),pCbbError3);
// 	QCenterComboBox *pCbbError4 = NewErrorType();
// 	GetComboxValue(_T("TtripD3_ErrorLogic"),pCbbError4);
// 	QCenterComboBox *pCbbError5 = NewErrorType();
// 	GetComboxValue(_T("TtripAcc_ErrorLogic"),pCbbError5);
	QComboBox *pCbbError1 = NewErrorType();
	GetComboxValue(_T("Ttrip_ErrorLogic"),pCbbError1);
	QComboBox *pCbbError2 = NewErrorType();
	GetComboxValue(_T("TtripD_ErrorLogic"),pCbbError2);
	QComboBox *pCbbError3 = NewErrorType();
	GetComboxValue(_T("TtripD2_ErrorLogic"),pCbbError3);
	QComboBox *pCbbError4 = NewErrorType();
	GetComboxValue(_T("TtripD3_ErrorLogic"),pCbbError4);
	QComboBox *pCbbError5 = NewErrorType();
	GetComboxValue(_T("TtripAcc_ErrorLogic"),pCbbError5);

	setCellWidget(0, 1, pCbbError1);
	setCellWidget(1, 1, pCbbError2);
	setCellWidget(2, 1, pCbbError3);
	setCellWidget(3, 1, pCbbError4);
	setCellWidget(4, 1, pCbbError5);

   	ComboxModelStyle(pCbbError1);
   	ComboxModelStyle(pCbbError2);
   	ComboxModelStyle(pCbbError3);
   	ComboxModelStyle(pCbbError4);
   	ComboxModelStyle(pCbbError5);


	pItem = new QTableWidgetItem();
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	GetTableWidgetItemValue(pItem,_T("Ttrip_RelErr"),false);
	setItem(0, 2, pItem); 
	pItem = new QTableWidgetItem();
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	GetTableWidgetItemValue(pItem,_T("TtripD_RelErr"),false);
	setItem(1, 2, pItem); 
	pItem = new QTableWidgetItem();
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	GetTableWidgetItemValue(pItem,_T("TtripD2_RelErr"),false);
	setItem(2, 2, pItem); 
	pItem = new QTableWidgetItem();
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	GetTableWidgetItemValue(pItem,_T("TtripD3_RelErr"),false);
	setItem(3, 2, pItem); 
	pItem = new QTableWidgetItem();
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	GetTableWidgetItemValue(pItem,_T("TtripAcc_RelErr"),false);
	setItem(4, 2, pItem); 


	pItem = new QTableWidgetItem();
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	GetTableWidgetItemValue(pItem,_T("Ttrip_AbsErr"),true);
	setItem(0, 3, pItem); 
	pItem = new QTableWidgetItem();
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	GetTableWidgetItemValue(pItem,_T("TtripD_AbsErr"),true);
	setItem(1, 3, pItem); 
	pItem = new QTableWidgetItem();
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	GetTableWidgetItemValue(pItem,_T("TtripD2_AbsErr"),true);
	setItem(2, 3, pItem); 
	pItem = new QTableWidgetItem();
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	GetTableWidgetItemValue(pItem,_T("TtripD3_AbsErr"),true);
	setItem(3, 3, pItem); 
	pItem = new QTableWidgetItem();
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	GetTableWidgetItemValue(pItem,_T("TtripAcc_AbsErr"),true);
	setItem(4, 3, pItem); 

// 	m_pCbbErrorDelegate = new QExBaseListComBoxDelegBase(this);
// 	setItemDelegateForColumn(1,m_pCbbErrorDelegate);
	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}

void QThreeRecloseEstimateGrid::GetComboxValue( const CString &strID ,QComboBox *pCombox )
{
	CDvmData* pCurData = (CDvmData*)m_pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	long nIndex = CString_To_long(pCurData->m_strValue);
	if (nIndex < 0)
	{
		return;
	}
	pCombox->setCurrentIndex(nIndex);
}

void QThreeRecloseEstimateGrid::GetTableWidgetItemValue(QTableWidgetItem * pItem , const CString &strID ,bool bAbs)
{
	CDvmData* pCurData = (CDvmData*)m_pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	
	float fValue = pCurData->m_strValue.toFloat();
	if (bAbs)
	{
		pItem->setText(QString::number(fValue,'f',2));
	}
	else
	{
		pItem->setText(QString::number(fValue,'f',0));
	}
}



void QThreeRecloseEstimateGrid::ComboxModelStyle(QComboBox *pCombox)
{
//  	QLineEdit *pLineEdit = new QLineEdit();
//  	pLineEdit->setReadOnly(true); 
//  	pLineEdit->setAlignment(Qt::AlignCenter);
//  	pLineEdit->installEventFilter(pCombox);
//  	pCombox->setLineEdit(pLineEdit);
// 	pCombox->setFont(*g_pSttGlobalFont);

  	pCombox->setEditable(true);
	pCombox->setFont(*g_pSttGlobalFont);
	pCombox->lineEdit()->setFont(*g_pSttGlobalFont);
  	pCombox->lineEdit()->setAlignment(Qt::AlignCenter);
  	pCombox->lineEdit()->setReadOnly(true);
  	pCombox->lineEdit()->setMouseTracking(true);
  	pCombox->lineEdit()->setStyleSheet("background:transparent;border-width:0;border-style:outset");
  	pCombox->lineEdit()->setAttribute(Qt::WA_TransparentForMouseEvents);
}

QComboBox* QThreeRecloseEstimateGrid::NewErrorType()
{
	CString strText;
	QComboBox *pCbbError = new QComboBox(this);
   //pCbbError->addItem("g_sLangTxt_StateEstimate_AbsError");
   //pCbbError->addItem("g_sLangTxt_StateEstimate_RelError");
   //strText = "g_sLangTxt_StateEstimate_AbsError" +"or"+"g_sLangTxt_StateEstimate_RelError";
   //pCbbError->addItem(strText);
   //strText = "g_sLangTxt_StateEstimate_AbsError" +"&"+"g_sLangTxt_StateEstimate_RelError";
   //pCbbError->addItem(strText);
   //pCbbError->addItem("g_sLangTxt_StateEstimate_CombinationError");
	return pCbbError;
}

bool QThreeRecloseEstimateGrid::eventFilter(QObject *obj, QEvent *event)
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

void QThreeRecloseEstimateGrid::mousePressEvent(QMouseEvent * event)
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

void QThreeRecloseEstimateGrid::slot_OnCellChanged( int row,int col )
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

	if(col == 2)//相对误差
	{
		fv = setLimit(0,100,fv);
		pItem->setText(QString::number(fv));
	}

	if(col == 3)//绝对误差
	{
		fv = setLimit(0,200,fv);
		pItem->setText(QString::number(fv,'f',2));
	}

	connect(this,SIGNAL(cellChanged (int,int)),this,SLOT(slot_OnCellChanged(int ,int)),Qt::UniqueConnection);
}


QCenterComboBox::QCenterComboBox(QWidget *parent) : QComboBox(parent)
{
	m_bPopupVisible = false;
}

QCenterComboBox::~QCenterComboBox()
{

}

bool QCenterComboBox::eventFilter(QObject *watched, QEvent *event)
{
	QString str = watched->metaObject()->className();
	if(QString(watched->metaObject()->className()) == "QLineEdit")
	{
		QLineEdit* lineEdit = static_cast<QLineEdit*>(watched);
		if (event->type() == QEvent::MouseButtonPress
			|| event->type() == QEvent::MouseButtonDblClick)
		{

			QCenterComboBox*  box = qobject_cast<QCenterComboBox*>(watched->parent());
			if(box && box == this && box->isEnabled())
			{
				if (m_bPopupVisible) // 如果下拉框已显示，则隐藏
				{
					box->hidePopup();
					m_bPopupVisible = false;
				}
				else // 如果下拉框未显示，则显示
				{
					box->showPopup();
					m_bPopupVisible = true;
				}
			}
			return true;
		}
		
	}
	else
	{
		QComboBox::eventFilter(watched, event);
		return true;
	}
	return false;
}
