#ifndef QSTTIECCONFIGDIALOGLINUX_H
#define QSTTIECCONFIGDIALOGLINUX_H

#include "SttIecConfigDialogBase.h"

class QSttIecConfigDialogLinux : public QSttIecConfigDialogBase
{
	Q_OBJECT

public:
	QSttIecConfigDialogLinux(CIecCfgDatasMngr *pIecCfgDatasMngr, QWidget *parent = NULL);
 	virtual ~QSttIecConfigDialogLinux();

	virtual void InitUI();//初始化创建整个界面

protected:
	virtual void CreateNavigationTree(long nTotalFiberNum_LC , long nTotalFiberNum_STSend);

protected slots:
	virtual void slot_TreeItemClicked(QTreeWidgetItem * item, int column );

};

#endif // QSTTIECCONFIGDIALOGWIN_H
