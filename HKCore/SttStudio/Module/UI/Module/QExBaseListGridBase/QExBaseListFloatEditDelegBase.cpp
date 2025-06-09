#include "QExBaseListFloatEditDelegBase.h"

//////////////////////////////////////////////////////////////////////////

QExBaseListFloatEditDelegBase::QExBaseListFloatEditDelegBase(QObject *parent)
: QItemDelegate(parent)
{
	m_bEditable= TRUE;
	m_fMinValue = 0.0f;
	m_fMaxValue = 100.0f;
	m_nDecimals = 3;
}

QExBaseListFloatEditDelegBase::~QExBaseListFloatEditDelegBase()
{

}

QWidget *QExBaseListFloatEditDelegBase::createEditor(QWidget *parent, const QStyleOptionViewItem &, 
										 const QModelIndex &index) const
{
	if (!m_bEditable)
	{
		return NULL;
	}

	QVariant variant = index.data();

	QFloatLineEdit *pFloatLineEdit = new QFloatLineEdit(parent);
	pFloatLineEdit->InitCoverage(m_fMinValue,m_fMaxValue,m_nDecimals);
	return pFloatLineEdit;
}

void QExBaseListFloatEditDelegBase::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	if (!m_bEditable)
	{
		return;
	}

	QObject *pParent = parent();

	if (pParent == NULL)
	{
		return;
	}

	QExBaseListGridBase *pExBaseListGridBase = qobject_cast<QExBaseListGridBase *>(pParent);

	if (pExBaseListGridBase == NULL)
	{
		return;
	}

	float fValue = index.model()->data(index, Qt::EditRole).toDouble();  
	QLineEdit *lineEdit =  static_cast <QLineEdit*>(editor);
	QString strValue;
	strValue = QString::number(fValue,'f',3);
	lineEdit->setText(strValue); 
}

void QExBaseListFloatEditDelegBase::setModelData(QWidget *editor, QAbstractItemModel *model, 
									 const QModelIndex &index) const
{
	if (!m_bEditable)
	{
		return;
	}

	//将代理控件的文本写入单元格
	QLineEdit *lineEdit =  static_cast <QLineEdit*>(editor);  
	QString text = lineEdit->text();  
	model->setData(index, text, Qt::EditRole); 

}

void QExBaseListFloatEditDelegBase::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, 
											 const QModelIndex &/*index*/) const
{
	editor->setGeometry(option.rect);
}

//////////////////////////////////////////////////////////////////////////
