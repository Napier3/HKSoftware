#ifndef QSTTWGTSCROLLBUTTONGROUP_H
#define	QSTTWGTSCROLLBUTTONGROUP_H

#include "../../UI/Module/ScrollCtrl/ScrollWidget.h"
#include "../Module/SttWgtBaseList.h"
#include "SttWgtButtonGroup.h"

class QSttWgtScrollButtonGroup : public QSttWgtBaseList, public QScrollWidget
{
public:
	QSttWgtButtonGroup* m_pBtnGroup;

public:
	QSttWgtScrollButtonGroup(QWidget* pParent = NULL);
	virtual ~QSttWgtScrollButtonGroup();

protected:
	void mousePressEvent(QMouseEvent *ev, long nX);
	void mouseMoveEvent(QMouseEvent *ev, long nX);

private slots:
	bool eventFilter(QObject *target, QEvent *event);

public:
	virtual void InitUIOwn(CExBaseObject *pSttXuiData);
	virtual void InitUIChildren(CExBaseObject *pSttXuiData);
};

#endif//!QSTTWGTSCROLLBUTTONGROUP_H