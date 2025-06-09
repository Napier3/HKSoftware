/************************************************************************/
/* QTableView中使用到的widget代理                                                                     */
/************************************************************************/
#ifndef QIECWIDGETELEGATE_H
#define QIECWIDGETELEGATE_H

#include "../QExBaseListGridBase/QExBaseListComBoxDelegBase.h"

//////////////////////////////////////////////////////////////////////////
#include "QIecLineEdit.h"
class QIecNumberEditDelegate : public QExBaseListItemDelegateBase
{
public:
	QIecNumberEditDelegate(QIecLineEdit::TEXT_TYPE _type = QIecLineEdit::STRING_TEXT, QObject *parent = NULL);
	~QIecNumberEditDelegate();

//	void InitHexLenth(long nHexLenth){m_nHexLenth = nHexLenth;}

	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, 
		const QModelIndex &index ) const;

	virtual void setEditorData(QWidget * ditor, const QModelIndex &index) const;

	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

	virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, 
		const QModelIndex &index) const;

private:
	QIecLineEdit::TEXT_TYPE m_textType;
//	long m_nHexLenth;//16进制数的长度如0x4003 对应长度为4
};


//////////////////////////////////////////////////////////////////////////
class CIecSpinBoxDelegate: public QExBaseListItemDelegateBase
{
public:
	CIecSpinBoxDelegate(int _iMin, int _iMax, QObject *parent=NULL);
	~CIecSpinBoxDelegate();

	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, 
		const QModelIndex &index ) const;

	virtual void setEditorData(QWidget * ditor, const QModelIndex &index) const;

	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

	virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, 
		const QModelIndex &index) const;

private:
	int m_nMinValue;
	int m_nMaxValue;
};


#endif // QIECWIDGETELEGATE_H
