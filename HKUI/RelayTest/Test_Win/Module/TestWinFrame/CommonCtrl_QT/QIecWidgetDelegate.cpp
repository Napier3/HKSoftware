#include "QIecWidgetDelegate.h"
#include "../QExBaseListGridBase/QExBaseListGridBase.h"
#include <QSpinBox>

//////////////////////////////////////////////////////////////////////////
QIecNumberEditDelegate::QIecNumberEditDelegate(QIecLineEdit::TEXT_TYPE _type, QObject *parent)
: QExBaseListItemDelegateBase(parent),m_textType(_type)
{
//	m_nHexLenth = 4;
}

QIecNumberEditDelegate::~QIecNumberEditDelegate()
{

}

QWidget *QIecNumberEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, 
										   const QModelIndex &index) const
{
	QString str = index.model()->data(index,Qt::EditRole).toString();
	QIecLineEdit *lineEdit = new QIecLineEdit(m_textType, str, parent);

	if (m_textType == QIecLineEdit::MAC_TEXT)
	{
		lineEdit->setInputMask("HH-HH-HH-HH-HH-HH;_");
	}
	else if (m_textType == QIecLineEdit::HEX_TEXT)
	{
		QGV_ITEM* pCurItem = GetCurrItem(index);

		if (pCurItem != NULL)
		{
			lineEdit->InitHexFormat(pCurItem->iMaxLen);
		}
	}

	return lineEdit;
}

void QIecNumberEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QString str = index.model()->data(index,Qt::EditRole).toString();

	QIecLineEdit *lineEdit = dynamic_cast<QIecLineEdit *>(editor);
	if(lineEdit != NULL)
		lineEdit->setText(str);

	QGV_ITEM* pCurItem = GetCurrItem(index);
	long nLenth = 2;

	if (pCurItem != NULL)
	{
		nLenth = pCurItem->iMaxLen;
	}

	lineEdit->setCursorPosition(nLenth);
}

void QIecNumberEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, 
									   const QModelIndex &index) const
{
	QIecLineEdit *lineEdit = dynamic_cast<QIecLineEdit *>(editor);
	QString str = lineEdit->text();
	model->setData(index,str,Qt::EditRole);

	QGV_ITEM* pCurItem = GetCurrItem(index);

	if (pCurItem == NULL)
	{
		return;
	}

	if (pCurItem->m_pEditFunc != NULL)
	{
		QExBaseListGridBase *pExBaseListGridBase = qobject_cast<QExBaseListGridBase *>(parent());
		pCurItem->m_pEditFunc(index.row(),index.column(),pCurItem,pExBaseListGridBase);
	}
}

void QIecNumberEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, 
											   const QModelIndex &/*index*/) const
{
	editor->setGeometry(option.rect);
}

//////////////////////////////////////////////////////////////////////////
CIecSpinBoxDelegate::CIecSpinBoxDelegate(int _iMin, int _iMax, QObject *parent)
:QExBaseListItemDelegateBase(parent),m_nMinValue(_iMin),m_nMaxValue(_iMax)
{

}

CIecSpinBoxDelegate::~CIecSpinBoxDelegate()
{

}

QWidget *CIecSpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, 
										const QModelIndex &/*index*/) const
{
	QSpinBox *spinBox = new QSpinBox(parent);
	spinBox->setMinimum(m_nMinValue);
	spinBox->setMaximum(0x7FFFFFFF);//m_nMaxValue
	return spinBox;
}

void CIecSpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	int iValue = index.model()->data(index,Qt::EditRole).toInt();
	QSpinBox *spinBox = qobject_cast<QSpinBox *>(editor);
	spinBox->setValue(iValue);
}

void CIecSpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, 
									const QModelIndex &index) const
{
	QSpinBox *spinBox = qobject_cast<QSpinBox *>(editor);
	if(spinBox->value()>m_nMaxValue){
		spinBox->setValue(m_nMaxValue);
	}
	model->setData(index,spinBox->value(),Qt::EditRole);
}

void CIecSpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, 
											const QModelIndex &/*index*/) const
{
	editor->setGeometry(option.rect);
}

//////////////////////////////////////////////////////////////////////////

