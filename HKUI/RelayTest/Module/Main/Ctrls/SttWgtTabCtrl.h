#ifndef QSTTWGTTABCTRL_H
#define	QSTTWGTTABCTRL_H

#include <QTabWidget>
#include "../Module/SttWgtBaseList.h"

class QSttWgtTabCtrl : public QSttWgtBaseList, public QTabWidget
{
public:
	QSttWgtTabCtrl(QWidget* pParent = NULL);
	virtual ~QSttWgtTabCtrl();

public:
	virtual void InitUIOwn(CExBaseObject *pSttXuiData);
	virtual void InitUIChildren(CExBaseObject *pSttXuiData);
};

class QSttWgtTab : public QSttWgtBase, public QWidget
{
public:
	QSttWgtTab(QWidget* pParent = NULL);
	virtual ~QSttWgtTab();

public:
	virtual void InitUIOwn(CExBaseObject *pSttXuiData);
	virtual void InitUIChildren(CExBaseObject *pSttXuiData);
	void AddWidgetChild(QWidget *pChildWidget);
};

#endif//!QSTTWGTTABCTRL_H