#ifndef QDEVMODTREE
#define QDEVMODTREE
#include <QTreeWidget>
#include "ExBaseList.h"
#include "..\DataMngr\DvmDevice.h"


class QDevModTree:public QTreeWidget,public CExBaseList
{
	Q_OBJECT

public:
	QDevModTree(QWidget *parent = NULL, CDvmDevice* pDvmDev = NULL);
	~QDevModTree();

public:
	CDvmDevice* m_pDvmDev;
	void InitDeviceTree();


};
#endif
