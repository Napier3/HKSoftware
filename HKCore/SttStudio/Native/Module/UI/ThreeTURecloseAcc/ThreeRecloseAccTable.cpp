#include "ThreeRecloseAccTable.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QApplication>
#include <QHeaderView>
#include <QLabel>
#include "../Module/CommonMethod/commonMethod.h"

QThreeRecloseAccTable::QThreeRecloseAccTable(CDataGroup* pParas, QWidget *parent )
: QScrollTableWidget(parent)
{
	m_pCurrKeyboardItem = NULL;
	m_bRunning = FALSE;
	m_pParas = pParas;
	InitUI();
}

QThreeRecloseAccTable::~QThreeRecloseAccTable()
{
	for (int i = 0; i < m_pAllCheckBoxList.size(); ++i) 
	{
		delete m_pAllCheckBoxList.at(i); 
	}
	m_pAllCheckBoxList.clear();

	for (int i = 0; i < m_pAllLineEditList.size(); ++i) 
	{
		delete m_pAllLineEditList.at(i); 
	}
	m_pAllLineEditList.clear();
}

void QThreeRecloseAccTable::InitUI()
{
	QHeaderView* pLeft = verticalHeader();
	pLeft->setDefaultSectionSize(36);
	pLeft->setVisible(false);
	QHeaderView* pHeadTop = horizontalHeader();
	pHeadTop->setClickable(false);
	pHeadTop->setMovable(false);
	QFont font1 = this->horizontalHeader()->font();
	font1.setBold(true);
	this->horizontalHeader()->setFont(font1);
	horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
	setEditTriggers(QAbstractItemView::DoubleClicked);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色

	QFontMetrics fontHeaderViewMe = QFontMetrics(font1);
	m_nHeaderViewHeight = fontHeaderViewMe.height() + 20;
	QFont font2 = this->font();
	font2.setPointSize(20);
	this->setFont(font2);
	QFontMetrics fontRowMe = QFontMetrics(font2);
	m_nRowHeight = fontRowMe.height() + 15;

	this->setStyleSheet(
		"QTableWidget::item:selected {"
		"background-color: transparent;" 
		"}"
		);
	//this->setStyleSheet("selection-background-color: grey;selection-color: black");
	this->setFocusPolicy(Qt::NoFocus);


	InitTable();
}

void QThreeRecloseAccTable::InitTable()
{
	QStringList  HStrList;
	//HStrList << _T("测试项") << _T("整定值") <<  _T("故障相别")<< _T("倍数") ;//解决乱码
	HStrList << CString("测试项") << CString("整定值") <<  CString("故障相别")<< CString("倍数") ;
	setColumnCount(4);
	setRowCount(5);
	setHorizontalHeaderLabels(HStrList);
	QFontMetrics fontMetrics = QFontMetrics(this->font());
	this->setColumnWidth(0,160);
	this->setColumnWidth(1,200);
	this->setColumnWidth(2,420);
	this->setColumnWidth(3,140);


	HStrList.clear();
	//HStrList << _T("检有压测试") << _T("一次重合闸") << _T("二次重合闸")<< _T("三次重合闸")<<  _T("后加速测试");
	HStrList << CString("检有压测试") << CString("一次重合闸") << CString("二次重合闸")<< CString("三次重合闸")<<  CString("后加速测试");
	QStringList  HStrIDList;
	HStrIDList << _T("NoPre_Check") << _T("Rec_Check") << _T("Rec2_Check")<< _T("Rec3_Check")<<  _T("AftAcc_Check");

	for (int row = 0; row < this->rowCount(); row++) 
	{
		this->setRowHeight(row, 50); 
		QStringList pFaultPhases,pFaultPhasesID;
		if (row == 0)
		{
			pFaultPhases <<_T("AB") << _T("BC")<< _T("CA")<< _T("ABC") ;
			pFaultPhasesID <<_T("NoPreFaultTypeAB_Check") << _T("NoPreFaultTypeBC_Check")<< _T("NoPreFaultTypeCA_Check")<< _T("NoPreFaultTypeABC_Check") ;
		}
		else if (row == 3)
		{
			pFaultPhases.clear();
			pFaultPhases <<_T("AN") << _T("BN")<< _T("CN");
			pFaultPhasesID.clear();
			pFaultPhasesID <<_T("Rec3FaultTypeA_Check") << _T("Rec3FaultTypeB_Check")<< _T("Rec3FaultTypeC_Check");
		}
		else
		{
			pFaultPhases.clear();
			pFaultPhases <<_T("AN") << _T("BN")<< _T("CN")<< g_sLangTxt_Native_ZeroSeq;
			if (row == 1)
			{
				pFaultPhasesID.clear();
				pFaultPhasesID <<_T("RecFaultTypeA_Check") << _T("RecFaultTypeB_Check")<< _T("RecFaultTypeC_Check")<< _T("RecFaultTypeI0_Check");
			}
			else if(row == 4)
			{
				pFaultPhasesID.clear();
				pFaultPhasesID <<_T("AftAccFaultTypeA_Check") << _T("AftAccFaultTypeB_Check")<< _T("AftAccFaultTypeC_Check")<< _T("AftAccFaultTypeI0_Check");
			}
			else
			{
				pFaultPhases.clear();
				pFaultPhasesID.clear();
			}
		}

		for (int col = 0; col < this->columnCount(); col++) 
		{	
			if (col == 0)
			{	
				QSttCheckBox *pTestCheckBox = new QSttCheckBox();
				pTestCheckBox->setFont(*g_pSttGlobalFont);
				pTestCheckBox->setText(HStrList.at(row));
				pTestCheckBox->setObjectName(HStrIDList.at(row));
				m_pAllCheckBoxList.append(pTestCheckBox);
				QWidget *pTestItemWidget = new QWidget();
				QHBoxLayout *pTestLayout = new QHBoxLayout(pTestItemWidget);
				pTestLayout->addWidget(pTestCheckBox);
				pTestLayout->setAlignment(Qt::AlignCenter);
				setCellWidget(row, col, pTestItemWidget); 

				if (row == 1 || row == 2 || row == 3)
				{
					m_pRecCheckBoxList.append(pTestCheckBox);
				}
				m_pPreAccRecCheckBoxList.append(pTestCheckBox);
			}
			else if (col == 1)
			{
				if (row == 0)
				{
					QLabel *pSetLabel = new QLabel;
					//pSetLabel->setText(_T("有压定值(V)"));
					pSetLabel->setText(CString("有压定值(V)"));
					pSetLabel->setFont(*g_pSttGlobalFont);
					QSttLineEdit *pSetValueEdit = new QSttLineEdit();
					pSetValueEdit->setFont(*g_pSttGlobalFont);
					CString strID = _T("NoPreSet");
					CDvmData *pCurData = (CDvmData*)m_pParas->FindByID(strID);
					float fValue = pCurData->m_strValue.toFloat();
					pSetValueEdit->setText(QString::number(fValue,'f',1));
					pSetValueEdit->setObjectName(strID);
					QWidget *pSetWidget = new QWidget();
					QHBoxLayout *pSetLayout = new QHBoxLayout(pSetWidget);
					pSetLayout->addWidget(pSetLabel);
					pSetLayout->addWidget(pSetValueEdit);
					pSetLayout->setAlignment(Qt::AlignCenter);
					setCellWidget(row, col, pSetWidget); 
					m_pAllLineEditList.append(pSetValueEdit);
				}
				else if (row == 1  || row == 2 || row == 3)
				{
					CString strID;
					QLabel *pTimeLabel = new QLabel;
					//pTimeLabel->setText(_T("时间定值(s)"));
					pTimeLabel->setText(CString("时间定值(s)"));
					pTimeLabel->setFont(*g_pSttGlobalFont);
					QSttLineEdit *pTimeLineEdit = new QSttLineEdit();
					pTimeLineEdit->setFont(*g_pSttGlobalFont);
					if (row == 1)
					{
						strID = _T("RecloseTime");
					}
					else if (row == 2)
					{
						strID = _T("RecloseTime2");
					}
					else
					{
						strID = _T("RecloseTime3");
					}

					pTimeLineEdit->setObjectName(strID);
					CDvmData *pCurData = (CDvmData*)m_pParas->FindByID(strID);
					float fValue = pCurData->m_strValue.toFloat();
					pTimeLineEdit->setText(QString::number(fValue,'f',1));
					QWidget *pTimeWidget = new QWidget();
					QHBoxLayout *pTimeLayout = new QHBoxLayout(pTimeWidget);
					pTimeLayout->addWidget(pTimeLabel);
					pTimeLayout->addWidget(pTimeLineEdit);
					pTimeLayout->setAlignment(Qt::AlignCenter);
					setCellWidget(row, col, pTimeWidget); 
					m_pAllLineEditList.append(pTimeLineEdit);
				}
				else 
				{
					QTableWidgetItem *item = new QTableWidgetItem();
					item->setFlags(item->flags() & ~Qt::ItemIsSelectable & ~Qt::ItemIsEditable);
					item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
					item->setText(_T("---"));
					setItem(row, col, item);
				}
			}
			else if (col == 2)
			{
				if(row == 0 || row == 1 || row == 3 || row == 4)
				{
					QWidget *pFaultWidget = new QWidget();
					QHBoxLayout *pFaultLayout = new QHBoxLayout(pFaultWidget);
					for (int i = 0; i < pFaultPhases.size(); ++i) 
					{
						QSttCheckBox *pPhaseCheckBox = new QSttCheckBox(pFaultPhases[i]);
						pPhaseCheckBox->setObjectName(pFaultPhasesID.at(i));
						m_pAllCheckBoxList.append(pPhaseCheckBox);
						pPhaseCheckBox->setFont(*g_pSttGlobalFont);
						pFaultLayout->addWidget(pPhaseCheckBox);
					}					
					pFaultLayout->setAlignment(Qt::AlignCenter);
					setCellWidget(row, col,pFaultWidget);  
				}
			}
			else 
			{
				if(row == 0)
				{
					QWidget *pMultipleWidget = new QWidget();
					QHBoxLayout *pMultipleLayout = new QHBoxLayout(pMultipleWidget);
					QSttCheckBox *pMultCheckBox1 = new QSttCheckBox();
					QSttCheckBox *pMultCheckBox2 = new QSttCheckBox();
					m_pAllCheckBoxList.append(pMultCheckBox1);
					m_pAllCheckBoxList.append(pMultCheckBox2);
					pMultCheckBox1->setFont(*g_pSttGlobalFont);
					pMultCheckBox2->setFont(*g_pSttGlobalFont);
					pMultCheckBox1->setObjectName(_T("NoPreRate095_Check"));
					pMultCheckBox2->setObjectName(_T("NoPreRate105_Check"));
					pMultCheckBox1->setText(_T("0.95"));
					pMultCheckBox2->setText(_T("1.05"));
					pMultipleLayout->addWidget(pMultCheckBox1);
					pMultipleLayout->addWidget(pMultCheckBox2); 
					pMultipleLayout->setAlignment(Qt::AlignCenter);
					setCellWidget(row, col, pMultipleWidget); 
				}
				else if (row == 1 || row == 4)
				{
					QTableWidgetItem *item = new QTableWidgetItem();
					item->setFlags(item->flags() & ~Qt::ItemIsSelectable & ~Qt::ItemIsEditable);
					item->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
					item->setText(_T("---"));
					setItem(row, col, item);
				}
			}
		}
	}

	setSpan(1, 2, 2, 1);
	setSpan(1, 3, 3, 1);

	UpdateTestItemState();

	for (int i = 0; i < m_pAllCheckBoxList.size(); ++i) 
	{
		QSttCheckBox *pCheckBox = m_pAllCheckBoxList.at(i);
		//pCheckBox->setFocusPolicy(Qt::NoFocus);    // 禁用焦点
		connect(pCheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
	}

	for (int i = 0; i < m_pAllLineEditList.size(); ++i) 
	{
		QSttLineEdit *pLineEdit = m_pAllLineEditList.at(i);
		connect(pLineEdit, SIGNAL(editingFinished ()), this, SLOT(slot_EditingFinished()));
	}
}

void QThreeRecloseAccTable::GetCheckBoxValue( CDataGroup *pParas,QSttCheckBox * pCheckBox,const CString strID )
{
	CDvmData* pCurData = (CDvmData*)pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
	if(nIsSelected)
	{
		pCheckBox->setChecked(true);;
	}
	else
	{
		pCheckBox->setChecked(false);;
	}
}


void QThreeRecloseAccTable::UpdateText( const QString &strText )
{

}

void QThreeRecloseAccTable::slot_CheckBoxStateChanged( int nState)
{
	QSttCheckBox* pCheckBox = qobject_cast<QSttCheckBox*>(sender()); 
	if (!pCheckBox)
	{
		return;
	}

	CString strID = pCheckBox->objectName();
	if (pCheckBox->isChecked()) 
	{
		m_pParas->SetDataValue(strID,(long)1);
	}
	else
	{
		m_pParas->SetDataValue(strID,(long)0);
	}
	
	int nRow = -1;
	if (strID == _T("NoPre_Check"))
	{
		nRow = 0;
		m_pAllLineEditList[0]->setEnabled(nState);
	}
	else if (strID == _T("AftAcc_Check"))
	{
		nRow = 4;
		emit sig_AftAccCheckStateChanged(pCheckBox->isChecked());
	}
	else if (strID == _T("Rec_Check") || strID == _T("Rec2_Check") || strID == _T("Rec3_Check"))
	{
		nRow = -1;
		UpdateRecState();
	}
	
	if (nRow != -1)
	{
		UpdateCheckbox(nRow,nState);
 		if (nRow != 1)
 		{
 			UpdateRecSetValue();
 		}
	}


	QWidget* widget = NULL; //dingxy 20241116 勾选框至少勾选一个
	if (strID.Find("NoPreFaultType") >= 0)
	{
		widget = this->cellWidget(0, 2);
	}
	else if (strID.Find("RecFaultType") >= 0)
	{
		widget = this->cellWidget(1, 2);
	}
	else if (strID.Find("Rec3FaultType") >= 0)
	{
		widget = this->cellWidget(3, 2);
	}
	else if (strID.Find("AftAccFaultType") >= 0)
	{
		widget = this->cellWidget(4, 2);
	}
	else if ((strID.Find("NoPreRate095_Check") >= 0) || (strID.Find("NoPreRate105_Check") >= 0))
	{
		widget = this->cellWidget(0, 3);
	}
	
	int nItemSelectCount = 0;
	if (widget)
	{
		QList<QSttCheckBox *> pCheckBoxList = widget->findChildren<QSttCheckBox *>();
		foreach (QSttCheckBox* pCheckBox, pCheckBoxList)
		{			   
			if (pCheckBox->isChecked())
			{
				nItemSelectCount++;
			}  
		}
		
		if (pCheckBoxList.count() > 1)
		{
			if (nItemSelectCount == 0)
			{
				pCheckBox->setCheckState(Qt::Checked);
				m_pParas->SetDataValue(strID,(long)1);
				
			}
		}
	}
}


void QThreeRecloseAccTable::slot_EditingFinished()
{
	QSttLineEdit* pLineEdit = qobject_cast<QSttLineEdit*>(sender()); 
	if (!pLineEdit)
	{
		return;
	}

	CString strID = pLineEdit->objectName();
	float fValue = pLineEdit->text().toFloat();
	fValue = setLimit(0,99999,fValue);
	pLineEdit->setText(QString::number(fValue,'f',1));
	m_pParas->SetDataValue(strID,fValue);
}

void QThreeRecloseAccTable::UpdateCheckbox(int row,bool bChecked )
{
	for (int col = 1; col < this->columnCount(); ++col) 
	{
		QWidget *pCellWidget = this->cellWidget(row, col);
		if (pCellWidget) 
		{
		   QList<QSttCheckBox *> pCheckBoxList = pCellWidget->findChildren<QSttCheckBox *>();
		   foreach (QSttCheckBox* pCheckBox, pCheckBoxList)
		   {			   
			   pCheckBox->setEnabled(bChecked);  
		   }
		}
	}
}


void QThreeRecloseAccTable::UpdateTableData(CDataGroup *pParas)
{
	for (int i = 0; i < m_pAllCheckBoxList.size(); ++i) 
	{
		QSttCheckBox *pCheckBox = m_pAllCheckBoxList.at(i);
		if (pCheckBox)
		{
			GetCheckBoxValue(pParas,pCheckBox,pCheckBox->objectName());
		}
	}
}

void QThreeRecloseAccTable::UpdateRecState(bool bUpdateRec1State, bool bCheck)
{
	QWidget *pFaultWidget = this->cellWidget(1, 2);
	if (pFaultWidget) 
	{
		QList<QSttCheckBox *> pCheckBoxList = pFaultWidget->findChildren<QSttCheckBox *>();
		foreach (QSttCheckBox* pCheckBox, pCheckBoxList)
		{	
			bool bChecked = m_pRecCheckBoxList[0]->isChecked() || m_pRecCheckBoxList[1]->isChecked();
			pCheckBox->setEnabled(bChecked);  
		}
	}
	QWidget *pTripWidget = this->cellWidget(3, 2);
	if (pTripWidget) 
	{
		QList<QSttCheckBox *> pCheckBoxList = pTripWidget->findChildren<QSttCheckBox *>();
		foreach (QSttCheckBox* pCheckBox, pCheckBoxList)
		{	
			bool bChecked = m_pRecCheckBoxList[2]->isChecked();
			pCheckBox->setEnabled(bChecked);  
		}
	}
	if (bUpdateRec1State == true)//dingxy 20241114 按测试要求5个测试项任意一项勾选，开放一次重合闸时间定值设置
	{
		if (bCheck == true)
		{
			m_pAllLineEditList[1]->setEnabled(true);
		}
		else
		{
			m_pAllLineEditList[1]->setEnabled(false);
		}
	}
	else
	{
		m_pAllLineEditList[1]->setEnabled(m_pRecCheckBoxList[0]->isChecked() || m_pRecCheckBoxList[1]->isChecked() || m_pRecCheckBoxList[2]->isChecked() || m_pPreAccRecCheckBoxList[0]->isChecked() || m_pPreAccRecCheckBoxList[4]->isChecked());
	}
	m_pAllLineEditList[2]->setEnabled(m_pRecCheckBoxList[1]->isChecked() || m_pRecCheckBoxList[2]->isChecked());
	m_pAllLineEditList[3]->setEnabled(m_pRecCheckBoxList[2]->isChecked());
}

void QThreeRecloseAccTable::UpdateTestItemState()
{
	//UpdateRecState();
	UpdateRecSetValue();

	for (int row = 0; row < this->rowCount(); ++row) 
	{
		QWidget *pWidget = this->cellWidget(row, 0);
		if (pWidget)
		{
			QSttCheckBox *pCheckBox = pWidget->findChild<QSttCheckBox *>();
			if (pCheckBox)
			{	
				bool isChecked = pCheckBox->isChecked();

				if (pCheckBox->objectName() == _T("NoPre_Check") || pCheckBox->objectName() == _T("AftAcc_Check"))
				{
					UpdateCheckbox(row,isChecked);
					if (pCheckBox->objectName() == _T("NoPre_Check"))
					{
						m_pAllLineEditList[row]->setEnabled(isChecked);
					}
				}
			}
		}
	}
}

void QThreeRecloseAccTable::UpdateRecSetValue()
{
	int nAllCheckBoxCheckedCount = 0;
	foreach (QSttCheckBox* pPreAccRecCheckBox, m_pPreAccRecCheckBoxList)
	{			   
		if (pPreAccRecCheckBox->isChecked())
		{
			nAllCheckBoxCheckedCount++;
		}
	}

	if (nAllCheckBoxCheckedCount >= 1)
	{
		UpdateRecState(true, true);
	}
	else
	{
		UpdateRecState(true, false);
	}
}
