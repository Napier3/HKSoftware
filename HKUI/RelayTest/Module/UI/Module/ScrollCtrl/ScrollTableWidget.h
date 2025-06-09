#ifndef ScrollTableWidget_H
#define ScrollTableWidget_H

#include "ScrollDef.h"
#include <QTableWidget>
#include <QItemDelegate>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class QCheckBoxDelegateBase : public QItemDelegate
{
public:
	QCheckBoxDelegateBase(QObject *parent=NULL);
	~QCheckBoxDelegateBase();


private:
	virtual void paint(QPainter * painter, const QStyleOptionViewItem & option,
		const QModelIndex & index) const;
	virtual bool editorEvent(QEvent * event, QAbstractItemModel * model,
		const QStyleOptionViewItem & option, const QModelIndex & index);

	QRect CheckBoxRect(const QStyleOptionViewItem &viewItemStyleOptions) const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class QScrollTableWidget : public QTableWidget
{
	Q_OBJECT

public:
	explicit QScrollTableWidget(QWidget* pParent = NULL);
	virtual ~QScrollTableWidget();
protected:
	void mousePressEvent(QMouseEvent *ev);
	void mouseMoveEvent(QMouseEvent *ev);
	void mouseReleaseEvent(QMouseEvent *ev);

public:
	// 设置在QTableWidget中拖动时允许左右拖动还是上下拖动
	void SetSliderDir(tagSliderDir tagDir);
	bool IsScrollMoving();
	void SetVertScrollWidth(long nVertScrollWidth);
	void SetHorizontalScrollHeight(long nLevelScrollHeight);
private:
	tagSliderAttri m_oAttri;

signals:
	void sig_ScrollFinished();
};

#endif//!ScrollTableWidget_H
