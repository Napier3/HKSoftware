#ifndef STTXFILE_MNGR_TREE_H
#define STTXFILE_MNGR_TREE_H

#include <QTreeWidget>
#include <QObject>
#include <QMouseEvent>
#include <QTreeWidgetItem>
#include "../../../../../Module/DataMngr/DvmData.h"
#include "../../../../../Module/XfileMngrBase/XFileMngr.h"
#include "../../../../../Module/BaseClass/QT/ExBaseListTreeCtrl.h"
#include "../ScrollCtrl/ScrollTreeWidget.h"

class QSttFileMngrTree : public QScrollTreeWidget
{
	Q_OBJECT

public:
	QSttFileMngrTree(QWidget *parent = 0);
	virtual ~QSttFileMngrTree();

	void InitUI();
	void InitShowFolderViewTree(const CString &strRootFolderPath);
	virtual  QExBaseTreeWidgetItem* InsertItem(QExBaseTreeWidgetItem *parent, CExBaseObject* pObj);
	virtual QExBaseTreeWidgetItem* NewItem(QExBaseTreeWidgetItem *parent, CExBaseObject *pData);
	BOOL IsUsbFolder(const CString &strPath);

// 	bool eventFilter(QObject *obj, QEvent *event);
// 	virtual void mouseReleaseEvent(QMouseEvent *);
// 	BOOL m_bRunning;

	CXFileMngr m_oFileMngr;
//	BOOL m_bUseCodeConversion;

protected://�༭������
	virtual void InsertItemToTreeCtrl(CExBaseObject* pObj,QExBaseTreeWidgetItem *pItemParent);
	virtual void InsertItemChildrenToTreeCtrl(CExBaseObject* pObj,QExBaseTreeWidgetItem *pItemParent);

	public slots:
		void slot_TreeItemClicked(QTreeWidgetItem*, int);
		void slot_OnFileTreeViewDoubleClick(QTreeWidgetItem*, int);
};

//void utf8_to_gbk(const CString &strUtf8, CString &strGbk);
BOOL GetUsbRootFolderPath(CString &strUsbRootFolderPath);//��ȡUSB�ӿڸ�Ŀ¼·��
extern QFont *g_pSttGlobalFont;


#endif // STTXFILE_MNGR_TREE_H
