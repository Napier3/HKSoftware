/************************************************************************/
/* QTableView中使用到的widget代理                                                                     */
/************************************************************************/
#ifndef WIDGETELEGATE_H
#define WIDGETELEGATE_H

#include <QItemDelegate>
#include "../../../61850/Module/CfgDataMngr/IecCfgDataMngrGlobal.h"

enum PAGE_TYPE{GOSUB_BLOCK, GOSUB_CHAN, GOPUB_BLOCK, GOPUB_CHAN, SMV92_BLOCK, SMV92_CHAN,SMV91_BLOCK, SMV91_CHAN, SMV78_BLOCK, 
			   SMV78_CHAN, COLLECTOR_BLOCK, COLLECTOR_CHAN, LOOPNET_BLOCK, LOOPNET_CHAN, LOOPNET_BITCHAN, LOOPNET_VALUE};

class CCheckBoxDelegate : public QItemDelegate
{
public:
	CCheckBoxDelegate(QObject *parent=NULL);
	~CCheckBoxDelegate();


private:
	virtual void paint(QPainter * painter, const QStyleOptionViewItem & option,
		const QModelIndex & index) const;
	virtual bool editorEvent(QEvent * event, QAbstractItemModel * model,
		const QStyleOptionViewItem & option, const QModelIndex & index);

	QRect CheckBoxRect(const QStyleOptionViewItem &viewItemStyleOptions) const;

private:
	QPixmap favouritePixmap;
	QPixmap notFavouritePixmap;
};


//////////////////////////////////////////////////////////////////////////
class CSpinBoxDelegate: public QItemDelegate
{
public:
	CSpinBoxDelegate(int _iMin, int _iMax, QObject *parent=NULL);
	~CSpinBoxDelegate();

	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, 
		const QModelIndex &index ) const;

	virtual void setEditorData(QWidget * ditor, const QModelIndex &index) const;

	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

	virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, 
		const QModelIndex &index) const;

private:
	int m_iMin;
	int m_iMax;
};


//////////////////////////////////////////////////////////////////////////
class CComboBoxDelegate : public QItemDelegate
{
public:
	//设置Data节点，代理会自动获取当前行和列，并设置值
	CComboBoxDelegate(PAGE_TYPE _type = GOPUB_BLOCK, QObject *parent=NULL);
	~CComboBoxDelegate();

	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, 
		const QModelIndex &index ) const;

	virtual void setEditorData(QWidget * ditor, const QModelIndex &index) const;

	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

	virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, 
		const QModelIndex &index) const;

private:
	PAGE_TYPE m_type;
};


//////////////////////////////////////////////////////////////////////////
#include "LineEdit.h"
class CNumberEditDelegate : public QItemDelegate
{
public:
	CNumberEditDelegate(CLineEdit::TEXT_TYPE _type = CLineEdit::STRING_TEXT, QObject *parent = NULL);
	~CNumberEditDelegate();

	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, 
		const QModelIndex &index ) const;

	virtual void setEditorData(QWidget * ditor, const QModelIndex &index) const;

	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

	virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, 
		const QModelIndex &index) const;

private:
	CLineEdit::TEXT_TYPE m_textType;
};

//////////////////////////////////////////////////////////////////////////
class CComplexDelegate : public QItemDelegate
{
public:
	CComplexDelegate(PAGE_TYPE _type, QObject *parent = NULL);
	~CComplexDelegate();

	void InitLanguage();

	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;

	virtual void setEditorData(QWidget * ditor, const QModelIndex &index) const;

	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

	virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;

private:
	PAGE_TYPE m_type;

	CString m_strString;
	CString m_strSingle;
	CString m_strDouble;
	CString m_strFloat;
	CString m_strQuality;
};

#endif // CHECKBOXDELEGATE_H
