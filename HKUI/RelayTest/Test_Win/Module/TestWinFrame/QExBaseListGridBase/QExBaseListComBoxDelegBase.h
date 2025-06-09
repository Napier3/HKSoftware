#ifndef QExBaseList_ComboBoxDelegate_H
#define QExBaseList_ComboBoxDelegate_H

#include "QExBaseListGridBase.h"
#include <QItemDelegate>
#include <QComboBox>
#include <QProxyStyle>
//#include <QStyledItemDelegate>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class QCheckBoxDelegateBase : public QItemDelegate
{
public:
	QCheckBoxDelegateBase(QObject *parent=NULL);
	virtual ~QCheckBoxDelegateBase();

	void SetEditable(BOOL bEditable = TRUE)       { m_bEditable = bEditable;         }

private:
	virtual void paint(QPainter * painter, const QStyleOptionViewItem & option,
		const QModelIndex & index) const;
 	virtual bool editorEvent(QEvent * event, QAbstractItemModel * model,
 		const QStyleOptionViewItem & option, const QModelIndex & index);

	QRect CheckBoxRect(const QStyleOptionViewItem &viewItemStyleOptions) const;

public:
	BOOL m_bEditable;//能否被修改
	// private:
	// 	QPixmap m_oSelectedPixmap;
	// 	QPixmap m_oUnselectedPixmap;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class QExBaseListItemDelegateBase : public QItemDelegate
{
public:
	QExBaseListItemDelegateBase(QObject *parent=NULL);
	~QExBaseListItemDelegateBase();

protected:
	QGV_ITEM* GetCurrItem(const QModelIndex &oQModelIndex) const;

};

class QExBaseListCheckBoxDelegate : public QExBaseListItemDelegateBase
{
public:
	QExBaseListCheckBoxDelegate(QObject *parent=NULL);
	~QExBaseListCheckBoxDelegate();


private:
	virtual void paint(QPainter * painter, const QStyleOptionViewItem & option,
		const QModelIndex & index) const;
	virtual bool editorEvent(QEvent * event, QAbstractItemModel * model,
		const QStyleOptionViewItem & option, const QModelIndex & index);

protected:
	QRect CheckBoxRect(const QStyleOptionViewItem &viewItemStyleOptions) const;

// private:
// 	QPixmap m_oSelectedPixmap;
// 	QPixmap m_oUnselectedPixmap;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class QExBaseListComBoxDelegBase : public QExBaseListItemDelegateBase
{
public:
	//设置Data节点，代理会自动获取当前行和列，并设置值
	QExBaseListComBoxDelegBase(QObject *parent=NULL);
	~QExBaseListComBoxDelegBase();

	void SetEditable(BOOL bEditable = TRUE)       { m_bEditable = bEditable;          }
	void SetUseEditCtrl(BOOL bUseEditCtrl = TRUE)       { m_bUseEditCtrl = bUseEditCtrl;          }

	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, 
		const QModelIndex &index ) const;

 	virtual void paint(QPainter * painter, const QStyleOptionViewItem & option,
 		const QModelIndex & index) const;
  	virtual bool editorEvent(QEvent * event, QAbstractItemModel * model,
  		const QStyleOptionViewItem & option, const QModelIndex & index);

	virtual void setEditorData(QWidget * ditor, const QModelIndex &index) const;

	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

	virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, 
		const QModelIndex &index) const;


	BOOL m_bEditable;//能否被修改
	BOOL m_bUseEditCtrl;//需要动态切换当前使用Combox还是Edit,通过此标记设置使用Edit
	BOOL m_bFirstClicked;
};


//////////////////////////////////////////////////////////////////////////

#endif // QExBaseList_ComboBoxDelegate_H
