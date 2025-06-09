#ifndef QSCLXMLCOMPAREDTREE_H
#define QSCLXMLCOMPAREDTREE_H

#include <QTreeWidget>
#include "../../../../Module/BaseClass/ExBaseList.h"
#include "../../../../Module/BaseClass/QT/ExBaseListTreeCtrl.h"
#include "../../../../Module/xml/PugiXML/pugixml.hpp"
#include "QSCLComparedTreeCtrl.h"

class QSCLXmlComparedTree : public QTreeWidget,public CExBaseList
{
	Q_OBJECT

public:
	QSCLXmlComparedTree (QWidget *parent = 0);
	~QSCLXmlComparedTree ();

public slots:
	void UpdateTreeView(QDeliverPugiNode* pDelivNode);
	void slot_TreeItemClicked(QTreeWidgetItem*, int);

signals:
	void sig_UpdateComparedTextView(CString &,CString &);
	void sig_InitComparedTextView(CString &,CString &);

public:	
	void PopulateTreeCtrl(pugi::xml_node &oPugiNode, QExBaseTreeWidgetItem *pItem);
	void PopulateTreeCtrl(QDeliverPugiNode *pDeliverNode, QExBaseTreeWidgetItem *pItem);
	void GetPugixmlAttrDesc(pugi::xml_node &oPugiNode, CString &strNodeAllDesc);
	QExBaseTreeWidgetItem* NewItem(QExBaseTreeWidgetItem *parent, CExBaseObject* pObj);
	void InitComparedTextView(QDeliverPugiNode* pDelivNode);
	void InsertImage(QExBaseTreeWidgetItem *pItem,long nCtrlID);


	BOOL m_bCanPostSel;
	long m_nDifNums;
};

#endif