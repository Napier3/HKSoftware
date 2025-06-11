#ifndef QSttPxEngineDvmTREECTRL_H
#define QSttPxEngineDvmTREECTRL_H

#include <QTreeWidget>
#include <QStyleFactory>
#include "../../../Module/DataMngr/DvmDevices.h"

#include "../../../../Module/BaseClass/QT/ExBaseListTreeCtrl.h"
#include "../../UI/Module/ScrollCtrl/ScrollCtrlInterface.h"

class QSttPxEngineDvmTreeItem : public QExBaseTreeWidgetItem
{
public:
	QSttPxEngineDvmTreeItem(QTreeWidgetItem *parent, CExBaseObject *pData);
	QSttPxEngineDvmTreeItem(QTreeWidget *parent, CExBaseObject *pData);
	virtual ~QSttPxEngineDvmTreeItem();

	void UpdateItemColor();
};

class QSttPxEngineDvmTreeCtrl : public CExBaseListTreeCtrl  ,public CScrollCtrlInterface
{
    Q_OBJECT
    
public:
    QSttPxEngineDvmTreeCtrl(QFont *font,QWidget *parent);
	virtual ~QSttPxEngineDvmTreeCtrl();
    
	virtual QExBaseTreeWidgetItem* NewItem(QTreeWidgetItem *parent, CExBaseObject *pData);
	void UpdateItemColour();
	void OnItemSelChanged(CExBaseObject *pSel);
	virtual void ShowBaseList(CExBaseList *pList, BOOL bAddRoot=TRUE);

private:
	virtual BOOL CanAdd(CExBaseObject *pObj);

signals:
	void sig_MouseMoveGbTree(QMouseEvent *);
	void sig_focusOutEventGbTree(QFocusEvent *);

protected:
	void mouseMoveEvent(QMouseEvent *e);
	void mousePressEvent(QMouseEvent *ev);
	void mouseReleaseEvent(QMouseEvent *ev);
	virtual void focusOutEvent(QFocusEvent *e);

private:

};

#endif // QSttPxEngineDvmTREECTRL_H
