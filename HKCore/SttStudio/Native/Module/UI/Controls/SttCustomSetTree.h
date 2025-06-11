#ifndef STTOTHER_SET_TREE_H
#define STTOTHER_SET_TREE_H

#include <QTreeWidget>
#include <QObject>
#include <QTreeWidgetItem>

#include "../../../Module/BaseClass/QT/ExBaseListTreeCtrl.h"


class QSttCustomSetTree : public CExBaseListTreeCtrl
{
	Q_OBJECT

public:
	QSttCustomSetTree(QWidget *parent);
	virtual ~QSttCustomSetTree();

    virtual void ShowMenuBaseList(CExBaseList *pList, bool bAddRoot=TRUE);
	virtual BOOL CanAdd(UINT nClassID);

	void ShowFloatBarTree(CExBaseList *pList,BOOL bClear = true);
	void ShowCustomSetBarTree_ToolBar(CExBaseList *pList);
	void SetCustomSetScrollWidth(long nCustomVertWidth,long nCustomLevelWidth); //�Զ������ý��滬��������
	
private:

	CExBaseList *m_pSet;

};

#endif // STTOTHER_SET_TREE_H
