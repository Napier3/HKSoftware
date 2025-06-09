#include <QHeaderView>
#include "SettingValueDialog.h"
#include "../../../../Module/SttTest/Common/tmt_test_mngr.h"
#include "../Module/SttXTestMngrBaseApp.h"

#include"../ReportView/XLangResource_PowerTestWin.h"

SettingValueDialog::SettingValueDialog(QWidget *parent)
	: QDialog(parent)
{
	this->setWindowTitle(/*QObject::tr("整定值")*/g_sLangTxt_State_SettingValue);
	this->setWindowIcon (QPixmap( "./images/setSetting.png"));
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint|Qt::WindowCloseButtonHint);

	InitTable();
	if (g_theSttXTestMngrBaseApp->GetTplID() != STT_MACRO_ID_DCOverCurrentTest)
	{
	initUI();
	}
	connect(m_table, SIGNAL(cellClicked ( int , int  )), this, SLOT(slot_Table_cellClicked ( int , int  )));
	connect(m_table, SIGNAL(cellChanged ( int , int  )), this, SLOT(slot_Table_cellChanged ( int , int  )));

	int nRowHeight = m_table->rowHeight(0);//窗口太大，缩小到一半 chenling20240204
	int nHeiget = 6 * nRowHeight * g_pTmt_SetsRef->GetCount(); 
	if (nHeiget > 500)
	{
		nHeiget = 500;
	}
	resize(700,  nHeiget);
	this->setFixedSize(700,nHeiget);
}

SettingValueDialog::~SettingValueDialog()
{

}


void SettingValueDialog::InitTable()
{
	m_table = new QTableWidget(this);
	
	QHeaderView* pTop = m_table->horizontalHeader();
	pTop->setClickable(false);
	pTop->setMovable(false);
	QHeaderView* pLeft = m_table->verticalHeader();
	pLeft->setDefaultSectionSize(25);
	pLeft->setVisible(false);

	m_table->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
	m_table->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
	m_table->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	m_table->setColumnCount(4);

	QFontMetrics fontMetrics = QFontMetrics(font());

	QStringList headers;

	headers<</*tr("序号")*/g_sLangTxt_SerNumber<</*tr("名称")*/g_sLangTxt_Name<</*tr("值")*/g_sLangTxt_Values<</*tr("标识")*/g_sLangTxt_Native_Identifier;
	m_table->setHorizontalHeaderLabels(headers);

	//2023-10-08 suyang 2880X1800分辨率处理
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();
	if (rect.height() == 1800)
	{
		m_table->setColumnWidth(0,80);
		m_table->setColumnWidth(1,200);
		m_table->setColumnWidth(2,180);
		m_table->setColumnWidth(3,80);
	}
	else
	{
	m_table->setColumnWidth(0,50);
	m_table->setColumnWidth(1,200);
	m_table->setColumnWidth(2,150);
	m_table->setColumnWidth(3,80);
	}
	
	m_Cmb = new CCmbSettingDelegate(this);
	m_table->setItemDelegateForColumn(2,m_Cmb);
}

void SettingValueDialog::initUI()
{
	CTestDataTypeMngrConstGlobal::Create();

	QFont ft("Microsoft YaHei", 10);
	int nHeight = 25;

	int nRow;
	CDvmData *pData;

	m_MainLayout = new QVBoxLayout;

	m_buttonLayout = new QHBoxLayout;

	POS pos = g_pTmt_SetsRef->GetHeadPosition();
	
	QLabel *TempLabel;
	QDvmDataLineEdit *TempEdit;
	nRow = 0;
	CString strValue, strK0A, strK0B;
	m_combIndexList.clear();

	while(pos)
	{
		pData = (CDvmData *)g_pTmt_SetsRef->GetNext(pos);

		m_table->insertRow(nRow);
		QTableWidgetItem* pitem = new QTableWidgetItem(QString::number(nRow+1));
		pitem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
		pitem->setFlags(pitem->flags() & (~Qt::ItemIsEditable));
		m_table->setItem(nRow,0,pitem);

		pitem = new QTableWidgetItem(pData->m_strName + pData->m_strUnit);
		pitem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
		pitem->setFlags(pitem->flags() & (~Qt::ItemIsEditable));
		m_table->setItem(nRow,1,pitem);

		strValue.Format(_T("%.3f"),CString_To_double(pData->m_strValue));//2023-12-06  suyang 保留三位小数

		if (pData->m_strDataType == _T("COMBO"))
		{
			m_combIndexList.push_back(nRow);
			pitem = new QTableWidgetItem(GetTextByIndex(pData->m_strID,/*pData->m_strValue*/strValue));
		}
		else
		{
			pitem = new QTableWidgetItem(/*pData->m_strValue*/strValue);
		}	

		//距离保护模块调用
		if(g_theSttXTestMngrBaseApp->GetTplID() == _T("DistanceTest") && pData->m_strDataType == _T("COMBO"))
		{
			CString strText = pitem->text();
			long nIndex = strText.Find(_T(","));
			if (nIndex>0)
			{
				strK0A = strText.left(nIndex);
				strK0B = strText.mid(nIndex + 1);
			}
		}
		pitem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
		m_table->setItem(nRow, 2, pitem);

		pitem = new QTableWidgetItem(pData->m_strID);
		pitem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter );
		pitem->setBackground(QColor(Qt::lightGray));
		pitem->setFlags(pitem->flags() & (~Qt::ItemIsEditable));
		m_table->setItem(nRow,3,pitem);
		
		m_table->setRowHeight(nRow,50);
		nRow ++;
	}

	if(g_theSttXTestMngrBaseApp->GetTplID() == _T("DistanceTest"))
	{
		ChangeTableItemTextByID(CString(_T("K0A")),strK0A,1);
		ChangeTableItemTextByID(CString(_T("K0B")),strK0B,1);
	}

	m_BtnOk = new QPushButton(this);
	m_BtnOk->setText(/*QObject::tr("确认")*/g_sLangTxt_OK);
	m_BtnOk->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_BtnOk->setFont(ft);
	m_BtnOk->setFixedSize(100,35);
	m_BtnOk->setIcon (QPixmap( "./images/Check.png"));
	m_buttonLayout->addWidget(m_BtnOk);

	m_BtnCancel = new QPushButton(this);
	m_BtnCancel->setText(/*QObject::tr("取消")*/g_sLangTxt_Cancel);
	m_BtnCancel->setFont(ft);
	m_BtnCancel->setFixedSize(100,35);
	m_BtnCancel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	m_BtnCancel->setIcon (QPixmap( "./images/Cancel.png"));
	m_buttonLayout->addWidget(m_BtnCancel);

	m_MainLayout->addWidget(m_table);
	m_MainLayout->addLayout(m_buttonLayout);

	setLayout(m_MainLayout);


	//this->setFixedSize(700,600);//窗口太大，缩小到一半

	connect(m_BtnOk,SIGNAL(clicked()),this,SLOT(slot_ClickOk()));
	connect(m_BtnCancel,SIGNAL(clicked()),this,SLOT(slot_ClickCancel()));
}

void SettingValueDialog::slot_Table_cellClicked( int nRow, int nCol)
{
	if (nCol == 2)
	{
		CDvmData *pData;
		pData = (CDvmData *)g_pTmt_SetsRef->GetAtIndex(nRow);
		if (pData->m_strDataType == _T("COMBO"))
		{
			m_Cmb->SetUseEditCtrl(TRUE);
			m_Cmb->SetListValue(CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(pData->m_strID));
		}
		else
		{
			m_Cmb->SetUseEditCtrl(FALSE);
		}
	}
}


void SettingValueDialog::slot_Table_cellChanged( int nRow, int nCol)
{
	if (nCol == 2)
	{
		CDvmData *pData;
		pData = (CDvmData *)g_pTmt_SetsRef->GetAtIndex(nRow);
		if (pData->m_strDataType != _T("COMBO"))
		{
			disconnect(m_table, SIGNAL(cellChanged ( int , int  )), this, SLOT(slot_Table_cellChanged ( int , int  )));

			QTableWidgetItem* pitem = m_table->item(nRow,2);
			float fv = pitem->text().toFloat();
			CString strUnit = _T("°");
			if (pData->m_strUnit.Find(strUnit) != -1)
			{
				fv = setAngleLimitEx(fv);
			}
			else
			{
				fv = setLimit(pData->m_strMin.toFloat(), pData->m_strMax.toFloat(), fv);
			}
			pitem->setText(QString::number(fv,'f',3));

			connect(m_table, SIGNAL(cellChanged ( int , int  )), this, SLOT(slot_Table_cellChanged ( int , int  )));

		}
		else//2024-5-27 wuxinyi 距离保护修改下拉框的值修改名称
		{
			if(g_theSttXTestMngrBaseApp->GetTplID() == _T("DistanceTest"))
			{
				disconnect(m_table, SIGNAL(cellChanged ( int , int  )), this, SLOT(slot_Table_cellChanged ( int , int  )));
				CString strID,strText, strK0A, strK0B;

				QTableWidgetItem* pTableWidgetItem = m_table->item(nRow,nCol);
				strID = pData->m_strID;
				strText = pTableWidgetItem->text();

				if(strID == _T("K0Mode"))
				{			
					long nIndex = strText.Find(_T(","));
					if (nIndex>0)
					{
						strK0A = strText.left(nIndex);
						strK0B = strText.mid(nIndex + 1);
					}
					//找到对应结构体改名称
	// 				g_pTmt_SetsRef->InitNameByID(strK0A,_T("K0A"));
					ChangeTableItemTextByID(CString(_T("K0A")),strK0A,1);
					ChangeTableItemTextByID(CString(_T("K0B")),strK0B,1);
				}	

				connect(m_table, SIGNAL(cellChanged ( int , int  )), this, SLOT(slot_Table_cellChanged ( int , int  )));
			}

		}
	}
}

void SettingValueDialog::slot_ClickOk()
{
	int nCount = m_table->rowCount();
	int i = 0;
	CDvmData *pData;
	POS pos = g_pTmt_SetsRef->GetHeadPosition();

 	while(pos && i <= nCount)
 	{
 		pData = (CDvmData *)g_pTmt_SetsRef->GetNext(pos);
		
		QTableWidgetItem* pitem = m_table->item(i,2);

		CString strCurText = pitem->text();

 		if (pData->m_strDataType == _T("COMBO"))
 		{
 			if (pData->m_strValue != GetIndexByText(pData->m_strID, strCurText))		//sf 20210915
 			{
 				g_theSttXTestMngrBaseApp->SetModifyPara();
 			}
 			pData->m_strValue = GetIndexByText(pData->m_strID, strCurText);
 		}
 		else
 		{
 			if (pData->m_strValue != strCurText) //sf 20210915
 			{
 				g_theSttXTestMngrBaseApp->SetModifyPara();
 			}
 			pData->m_strValue = strCurText;
 		}
		i++;
 	}

	emit sig_ClickOk();
	close();

}
void SettingValueDialog::slot_ClickCancel()
{
	close();
}

CString SettingValueDialog::GetTextByIndex( CString strID, CString nIndex )
{
	CDataType *pList = CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(strID);
	return pList->GetAtIndex(CString_To_long(nIndex))->m_strName; //chenling20240122
}

CString SettingValueDialog::GetIndexByText( CString strID, CString nText )
{
	CDataType *pList = CTestDataTypeMngrConstGlobal::g_pDataTypeGlobal->FindTestDataType(strID);

	POS pos = pList->GetHeadPosition();
	int i = 0;
	while (pos != NULL)
	{
		CDataTypeValue *pObj = (CDataTypeValue*)pList->GetNext(pos);

		if (pObj->m_strName == nText)
		{
			break;
		}
		else
		{
			i++;
			continue;
		}
	}
	
	return QString::number(i);
}

void SettingValueDialog::ChangeTableItemTextByID( const CString &strID, const CString &strText,int nCol )
{
	int nIndex = g_pTmt_SetsRef->FindIndexByID(strID);
	if (nIndex < 0)
	{
		return;
	}

	QTableWidgetItem *pItem = m_table->item(nIndex, nCol);
	if(pItem)
	{
		pItem->setText(strText);
	}
}

///////////////////////////////////////////////////////////////////////

CCmbSettingDelegate::CCmbSettingDelegate(QObject *parent /*= NULL*/ ):QItemDelegate (parent)
{

}

CCmbSettingDelegate::~CCmbSettingDelegate()
{

}

QWidget * CCmbSettingDelegate::createEditor( QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	QVariant variant = index.data();
	if (m_bUseEditCtrl)
	{
		QComboBox *comboBox = new QComboBox(parent);
		return comboBox;
	}
	else
	{
		return new QLineEdit(parent);
	}
}

void CCmbSettingDelegate::setEditorData( QWidget * editor, const QModelIndex &index ) const
{
	if (m_bUseEditCtrl)
	{
		QString strItem = index.model()->data(index,Qt::EditRole).toString();

		QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
		comboBox->clear();
		int id = 0;
		for (int i = 0; i < m_strList.size(); i++)
		{
			QString strValue = m_strList.at(i);
			if (strValue == strItem)
			{
				id = i;
			}
			comboBox->addItem(strValue);
		}
		comboBox->setCurrentIndex(id);
	}
	else
	{
		QLineEdit *lineEdit =  static_cast <QLineEdit*>(editor);
		lineEdit->setText(index.model()->data(index, Qt::EditRole).toString()); 
	}
	
}

void CCmbSettingDelegate::setModelData( QWidget *editor, QAbstractItemModel *model, const QModelIndex &index ) const
{
	if (m_bUseEditCtrl)
	{
		QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
		model->setData(index,comboBox->currentText(),Qt::EditRole);
	}
	else
	{
		QLineEdit *pLineEdit = qobject_cast<QLineEdit *>(editor);
		model->setData(index, pLineEdit->text(), Qt::EditRole);
	}
}

void CCmbSettingDelegate::updateEditorGeometry( QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	editor->setGeometry(option.rect);
}

void CCmbSettingDelegate::SetListValue( CDataType *pList )
{
	ASSERT(pList);

	m_strList.clear();

	POS pos = pList->GetHeadPosition();
	int i = 0;
	while (pos != NULL)
	{
		CDataTypeValue *pObj = (CDataTypeValue*)pList->GetNext(pos);

		if (pObj != NULL)
		{
			m_strList.insert(i++,pObj->m_strName);
		}
	}
}

//鼠标单击单元格的时候，重绘事件触发
void CCmbSettingDelegate::paint(QPainter * painter,
								  const QStyleOptionViewItem & option,
								  const QModelIndex & index) const
{  
	QProxyStyle oProxyStyle;
	QStyleOptionComboBox oStyleOptionComboBox;
	oStyleOptionComboBox.state = QStyle::State_On;
	oStyleOptionComboBox.rect = option.rect;
	QPalette oPalette;
	SettingValueDialog* pParent = (SettingValueDialog*)parent();

	if (pParent != NULL)
	{
		QTableWidgetItem *pTableWidgetItem = pParent->m_table->item(index.row(),index.column());
		oStyleOptionComboBox.editable = true;
		oStyleOptionComboBox.frame = false;
		oStyleOptionComboBox.currentText = pTableWidgetItem->text();
		if (index.column() == 2 && (pParent->m_combIndexList.size() != 0))
		{
			for (int nIndex = 0; nIndex < pParent->m_combIndexList.size(); nIndex++)
			{
				if (index.row() == pParent->m_combIndexList[nIndex])
				{
					if (pTableWidgetItem != NULL)
					{
						//只对第2列的下拉框做特殊处理
						oProxyStyle.drawComplexControl(QStyle::CC_ComboBox,&oStyleOptionComboBox, painter);
						oProxyStyle.drawItemText(painter,option.rect,Qt::AlignCenter,oPalette,true,oStyleOptionComboBox.currentText);
					}
				}
				else
				{
					QItemDelegate::paint(painter, option, index);
				}
			}
		}
		else
		{
			QItemDelegate::paint(painter, option, index);
		}
	}
	else
	{
		QItemDelegate::paint(painter, option, index);
	}

 }
