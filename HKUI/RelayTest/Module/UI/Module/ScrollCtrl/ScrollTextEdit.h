#ifndef ScrollTextEdit_H
#define ScrollTextEdit_H

#include "ScrollDef.h"
#include <QTextEdit>
#include <QMenu>

class QScrollTextEdit : public QTextEdit
{
	Q_OBJECT
public:
	explicit QScrollTextEdit(QWidget* pParent = NULL);
	virtual ~QScrollTextEdit();

#ifdef _PSX_QT_LINUX_
protected:
	void mousePressEvent(QMouseEvent *ev);
	void mouseMoveEvent(QMouseEvent *ev);
	void mouseReleaseEvent(QMouseEvent *ev);

public:
	void SetSliderDir(tagSliderDir tagDir);

private:
	tagSliderAttri m_oAttri;
#endif

	//windows下，创建右键菜单
#ifndef _PSX_QT_LINUX_
	QMenu *m_MenuLogOptr;
	QAction *m_ActCopyLog;      //拷贝
	QAction *m_ActClearLog;  //清楚

	void CreateLogOptrMenu();
#endif

public slots:
#ifndef _PSX_QT_LINUX_
	void slot_OnCopyLog();
	void slot_OnClearLog();
	void slot_LogShowMenu(QPoint pos);
#endif
};

#endif//!ScrollTextEdit_H
