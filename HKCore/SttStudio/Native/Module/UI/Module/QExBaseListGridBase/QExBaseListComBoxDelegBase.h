#ifndef QExBaseList_ComboBoxDelegate_H
#define QExBaseList_ComboBoxDelegate_H

#include "QExBaseListGridBase.h"
#include <QItemDelegate>
#include <QComboBox>
#include <QProxyStyle>
//#include <QStyledItemDelegate>

//////////////////////////////////////////////////////////////////////////

class QExBaseListItemDelegateBase : public QItemDelegate
{
public:
	QExBaseListItemDelegateBase(QObject *parent=NULL);
	virtual ~QExBaseListItemDelegateBase();

protected:
	QGV_ITEM* GetCurrItem(const QModelIndex &oQModelIndex) const;

};

class QExBaseListCheckBoxDelegate : public QExBaseListItemDelegateBase
{
public:
	QExBaseListCheckBoxDelegate(QObject *parent=NULL);
	virtual ~QExBaseListCheckBoxDelegate();

	void InitStyleSheet();

private:
	virtual void paint(QPainter * painter, const QStyleOptionViewItem & option,
		const QModelIndex & index) const;
	virtual bool editorEvent(QEvent * event, QAbstractItemModel * model,
		const QStyleOptionViewItem & option, const QModelIndex & index);

	QRect CheckBoxRect(const QStyleOptionViewItem &viewItemStyleOptions) const;

	
 protected:
 	QPixmap m_oSelectedPixmap;
 	QPixmap m_oUnselectedPixmap;
};

//////////////////////////////////////////////////////////////////////////
class QExBaseListComBoxDelegBase : public QExBaseListItemDelegateBase
{
public:
	//����Data�ڵ㣬������Զ���ȡ��ǰ�к��У�������ֵ
	QExBaseListComBoxDelegBase(QObject *parent=NULL);
	virtual ~QExBaseListComBoxDelegBase();

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


	BOOL m_bEditable;//�ܷ��޸�
	BOOL m_bUseEditCtrl;//��Ҫ��̬�л���ǰʹ��Combox����Edit,ͨ���˱������ʹ��Edit
	BOOL m_bFirstClicked;
};


//////////////////////////////////////////////////////////////////////////

#endif // CHMAPSGRID_H
