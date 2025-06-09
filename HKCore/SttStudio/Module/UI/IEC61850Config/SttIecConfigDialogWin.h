#ifndef QSTTIECCONFIGDIALOGWIN_H
#define QSTTIECCONFIGDIALOGWIN_H

#include "SttIecConfigDialogBase.h"

class QSttIecConfigDialogWin : public QSttIecConfigDialogBase
{
	Q_OBJECT

public:
	QSttIecConfigDialogWin(CIecCfgDatasMngr *pIecCfgDatasMngr, QWidget *parent = NULL);
	~QSttIecConfigDialogWin();

	virtual void InitUI();//初始化创建整个界面

protected:
	virtual void CreateNavigationTree(long nTotalFiberNum_LC , long nTotalFiberNum_STSend);

protected slots:
	virtual void slot_TreeItemClicked(QTreeWidgetItem * item, int column );

};

#endif // QSTTIECCONFIGDIALOGWIN_H
