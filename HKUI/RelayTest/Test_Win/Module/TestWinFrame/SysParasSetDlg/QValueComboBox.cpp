#include "QValueComboBox.h"

QValueComboBox::QValueComboBox(QWidget *parent)
	: QComboBox(parent)
{
	m_pList = NULL;
	m_pIndex = NULL;

	//this->setEditable(true);
	SetEditingFinished();
}

QValueComboBox::~QValueComboBox()
{

}

void QValueComboBox::SetValue( CDataType *pList)
{
	ASSERT(pList);
	m_pList = pList;

	clear();

	POS pos = m_pList->GetHeadPosition();
	int i = 0;
	while (pos != NULL)
	{
		CDataTypeValue *pObj = (CDataTypeValue*)m_pList->GetNext(pos);

		if (pObj != NULL)
		{
			insertItem(i++,pObj->m_strName);
		}
	}
}
void QValueComboBox::SetIndex( int *pIndex )
{
	disconnect(this,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_currentIndexChanged(int)));

	ASSERT(pIndex);
	m_pIndex = pIndex;

	setCurrentIndex(*m_pIndex);

	connect(this,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_currentIndexChanged(int)));
}

void QValueComboBox::slot_currentIndexChanged( int nIndex)
{
	if (nIndex >= 0 && nIndex < count())
	{
		*m_pIndex = nIndex;
	}
}

//mym 2021-7-22 增加了可以编辑combox 属性，把编辑框么有的内容添加到list中；
void QValueComboBox::SetEditingFinished()
{
	QLineEdit * pLineEdit = this->lineEdit();
	QObject::connect(pLineEdit,	 SIGNAL(returnPressed()),  this ,SLOT(slot_EditingFinished()));//editingFinished
}

void QValueComboBox::slot_EditingFinished()
{
	QLineEdit * pLineEdit = this->lineEdit();
	QString strValue  = pLineEdit->text();

	//
	bool bFind = false;
	POS pos = m_pList->GetHeadPosition();
	int i = 0;
	while (pos != NULL)
	{
		CDataTypeValue *pObj = (CDataTypeValue*)m_pList->GetNext(pos);

		if (pObj != NULL)
		{
			if (strValue == pObj->m_strName)
			{
				bFind = true;
				break;
			}
		}	
	}

	//假如没有这个项，则往链表中添加一项；
	if (!bFind)
	{
		CString strNO;
		strNO.Format(_T("%d"),  m_pList->GetCount());
		m_pList->AddNewValue( strValue,  _T(""), strNO);
		
		SetValue(m_pList);
	}	
	int adf = 0;
}