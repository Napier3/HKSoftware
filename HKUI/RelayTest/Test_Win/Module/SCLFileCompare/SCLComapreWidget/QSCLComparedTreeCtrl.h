#ifndef QSCLCOMPAREDTREECTRL_H
#define QSCLCOMPAREDTREECTRL_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "../../../../Module/BaseClass/ExBaseList.h"
#include "../../../../Module/xml/PugiXML/pugixml.hpp"
#include "../../../../Module/BaseClass/QT/ExBaseListTreeCtrl.h"
#include "QDeliverPugiNode.h"


class QSCLComparedTreeCtrl: public QTreeWidget,public CExBaseList
{
	Q_OBJECT

public:
	QSCLComparedTreeCtrl(QWidget *parent = 0,CString strSCLFilePath = "", CString strCompareFilePath = "");
	~QSCLComparedTreeCtrl();
 
public:
	pugi::xml_node GetPugixmlSourceRoot(); //解析源文件
	pugi::xml_node GetPugixmlCompareRoot();//解析比对文件	
	
	void ShowMainTreeCtrl();
	void PopulateMainTreeCtrl(pugi::xml_node oPugiSourceNode, pugi::xml_node oPugixmlCompareRoot,QExBaseTreeWidgetItem * pItem);
	long CompareHearderPort(pugi::xml_node oPugiSourceNode ,pugi::xml_node oPugiCompareNode );
	long CompareSubstationPort(pugi::xml_node oPugiSourceNode ,pugi::xml_node oPugiCompareNode );
	long CompareDataTypeTempPort(CString strNodeType, pugi::xml_node oPugiSourceNode ,pugi::xml_node oPugiCompareNode );
	long CompareCommonPort(pugi::xml_node oPugiSourceNode ,pugi::xml_node oPugiCompareNode );
	long CompareChildAndAttr(pugi::xml_node oPugiSourceNode ,pugi::xml_node oPugiCompareNode);
	bool CompPugiNodeAttr(pugi::xml_node oPugiSourChild ,pugi::xml_node oPugiCompChild);
	void GetAttrNameAndDescValue(pugi::xml_node oPugiNode,CString *strAttrVal);

	QExBaseTreeWidgetItem* NewItem(QExBaseTreeWidgetItem *parent, CExBaseObject* pObj);
	static UINT ShowModelTreeThread(LPVOID pParam);

	void ShowModelTree();
	void InsertImage(QExBaseTreeWidgetItem *pItem,long nCtrlID);

	void ExportReport();
	void GetPugixmlAttrDesc(pugi::xml_node &oPugiNode, CString &strNodeAllDesc);
	void CompareNodeContents(QDeliverPugiNode* pDelivNode);
	void CompareNode(QDeliverPugiNode *pDeliverNode);

signals:
	void sig_UpdateXmlComparedTree(QDeliverPugiNode*);

public slots:
	void slot_TreeItemClicked(QTreeWidgetItem*, int);

public:
	HANDLE m_pLoadFileThread;
	CString m_strSCLFilePath;//导入源文件路径
	CString m_strCompareFilePath;//导入比对文件路径

	BOOL m_bIsReading;
	long m_nIEDNumber;

	pugi::xml_document* m_pPugixmlSoureDoc;
	pugi::xml_document* m_pPugixmlCompareDoc;
	QExBaseTreeWidgetItem *m_pRootItem;//根节点
	QExBaseTreeWidgetItem *m_pIedItem;
	QExBaseTreeWidgetItem *m_pCurrItem;//当前节点

	long m_nDifNums ;
	QMap<QString, QVector<QString>> m_DiffListMap;
	QVector<QString> m_DiffList;
};

#endif