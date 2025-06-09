#ifndef QSttCommCfgPointTblFileImportTreeCtrl_H
#define QSttCommCfgPointTblFileImportTreeCtrl_H

#include <QTreeWidget>
#include <QStyleFactory>
#include "../../../Module/DataMngr/DvmDevices.h"

#include "../../../../../../Module/BaseClass/QT/QExBaseListTreeCtrl.h"
#include "../../ScrollCtrl/ScrollCtrlInterface.h"

class QSttCommCfgPointTblFileImportTreeItem : public QExBaseTreeWidgetItem
{
public:
	QSttCommCfgPointTblFileImportTreeItem(QTreeWidgetItem *parent, CExBaseObject *pData);
	QSttCommCfgPointTblFileImportTreeItem(QTreeWidget *parent, CExBaseObject *pData);
	virtual ~QSttCommCfgPointTblFileImportTreeItem();

	void UpdateItemColor();
};

class QSttCommCfgPointTblFileImportTreeCtrl : public CExBaseListTreeCtrl  ,public CScrollCtrlInterface
{
    Q_OBJECT
    
public:
    QSttCommCfgPointTblFileImportTreeCtrl(QFont *font,QWidget *parent);
	virtual ~QSttCommCfgPointTblFileImportTreeCtrl();
    
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

#endif // QSttCommCfgDeviceTreeCtrl_H
