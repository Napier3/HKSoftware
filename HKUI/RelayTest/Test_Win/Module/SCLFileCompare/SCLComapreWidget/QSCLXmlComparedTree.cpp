#include "QSCLXmlComparedTree.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include <sstream>

QSCLXmlComparedTree::QSCLXmlComparedTree(QWidget *parent)
:QTreeWidget(parent)
{
	_P_InitSystemPath();
	setStyle(QStyleFactory::create("windows"));
	setStyleSheet("QTreeWidget::item{height:30px}");
	setHeaderHidden(true);

	connect(this, SIGNAL(itemClicked(QTreeWidgetItem*, int)), SLOT(slot_TreeItemClicked(QTreeWidgetItem*, int)));
}

QSCLXmlComparedTree::~QSCLXmlComparedTree()
{

}


QExBaseTreeWidgetItem* QSCLXmlComparedTree::NewItem(QExBaseTreeWidgetItem *parent, CExBaseObject *pObj)
{
	if (parent == NULL)
	{
		return new QExBaseTreeWidgetItem(this, pObj);
	}
	else
	{
		return new QExBaseTreeWidgetItem(parent, pObj);
	}
}


void QSCLXmlComparedTree::UpdateTreeView(QDeliverPugiNode* pDelivNode)
{
	m_bCanPostSel = FALSE;
	DeleteAll();
	clear();

	ASSERT(pDelivNode != NULL);
	m_nDifNums = 0;

	pugi::xml_node oSourNode(pDelivNode->m_pSourNode);
	pugi::xml_node oCompNode(pDelivNode->m_pCompNode);


	pugi::xml_node oPugiNode;
	pugi::xml_node oPugiCompNode;
	CString strText;
	strText = oSourNode.name();
	
	CString strNodeName;
	QDeliverPugiNode *pDeliverNodeNew = NULL;
	CExBaseObject *pCurObj = NULL;
	QExBaseTreeWidgetItem *pItem = NULL;

	if (pDelivNode->m_nType == 2)
	{
		strNodeName = oCompNode.parent().name();
		oPugiNode = oCompNode;
	} 
	else
	{
		strNodeName = oSourNode.parent().name();
		oPugiNode = oSourNode;
	}

	if (strNodeName == _T("DataTypeTemplates"))
	{
		pItem = NewItem(NULL,pCurObj);
		pItem->setText(0,_T("DataTypeTemplates"));
		pItem->setExpanded(TRUE);

		while(oPugiNode != NULL)
		{
			pDeliverNodeNew = new QDeliverPugiNode();
			AddNewChild(pDeliverNodeNew);

			if (pDelivNode->m_nType == 6)
			{
				oPugiCompNode = oCompNode.next_sibling(strText.AllocSysString() , L"id" ,oPugiNode.attribute(L"id").value());

				if (oPugiCompNode != NULL)
					pDeliverNodeNew->m_nType = pDelivNode->m_nType;
				else
					pDeliverNodeNew->m_nType = 4;

				pDeliverNodeNew->m_pSourNode = oPugiNode.internal_object();
				pDeliverNodeNew->m_pCompNode = oPugiCompNode.internal_object();
			} 
			else
			{
				pDeliverNodeNew->m_pSourNode = oPugiNode.internal_object();
				pDeliverNodeNew->m_pCompNode = oPugiNode.internal_object();
				pDeliverNodeNew->m_nType = pDelivNode->m_nType;
			}


			PopulateTreeCtrl(pDeliverNodeNew, pItem);

			oPugiNode = oPugiNode.next_sibling(strText.AllocSysString());
		}

		if (pDelivNode->m_nType == 6)
		{
			oPugiCompNode = oCompNode;
			while(oPugiCompNode != NULL)
			{
				oPugiNode = oSourNode.next_sibling(strText.AllocSysString() , L"id" ,oPugiCompNode.attribute(L"id").value());

				if (oPugiNode == NULL)
				{
					pDeliverNodeNew = new QDeliverPugiNode();
					AddNewChild(pDeliverNodeNew);
					pDeliverNodeNew->m_pSourNode = NULL;
					pDeliverNodeNew->m_pCompNode = oPugiCompNode.internal_object();
					pDeliverNodeNew->m_nType = 2;

					InsertImage(pItem,pDelivNode->m_nType);

					PopulateTreeCtrl(pDeliverNodeNew, pItem);
				}

				oPugiCompNode = oPugiCompNode.next_sibling(strText.AllocSysString());
			}
		}
	}
	else
	{
//      CExBaseObject *pCurObj = NULL;
// 	    m_pRootItem = NewItem(NULL,pCurObj);//根节点
// 		m_pRootItem->setText(0,strNodeName);
// 	    m_pRootItem->setExpanded(TRUE);
		PopulateTreeCtrl(pDelivNode,NULL);
	}
	
	InitComparedTextView(pDelivNode);
	m_bCanPostSel = TRUE;
} 

void QSCLXmlComparedTree::InitComparedTextView(QDeliverPugiNode* pDelivNode)
{
	pugi::xml_node oPugiSurHeadNode(pDelivNode->m_pSourNode);
	pugi::xml_node oPugiCmpHeadNode(pDelivNode->m_pCompNode);
	pugi::xml_string_writer writerSur,writerCmp;
	CString strSourText ,strCompText;

	oPugiSurHeadNode.print(writerSur,L"\t", 1U, pugi::encoding_utf8);
	oPugiCmpHeadNode.print(writerCmp,L"\t", 1U, pugi::encoding_utf8);

	strSourText = QString::fromUtf8(writerSur.result);
	strCompText = QString::fromUtf8(writerCmp.result);

	emit sig_InitComparedTextView(strSourText,strCompText);
}

void QSCLXmlComparedTree::slot_TreeItemClicked(QTreeWidgetItem *pTreeWidgetItem, int column)
{
	QExBaseTreeWidgetItem *pItem = (QExBaseTreeWidgetItem*)pTreeWidgetItem;

	if (pItem->m_pItemData == NULL)
	{
		return;
	}

	QDeliverPugiNode* pDelivNode =(QDeliverPugiNode*)pItem->m_pItemData;

	if (!m_bCanPostSel)
	{
		return;
	}

	pugi::xml_node oPugiSourNode(pDelivNode->m_pSourNode);
	pugi::xml_node oPugiCompNode(pDelivNode->m_pCompNode);
	CString strSourText ,strCompText;
	pugi::xml_string_writer wrtSour ,wrtComp;

	if (pDelivNode->m_nType == 0)
	{
		oPugiSourNode.print(wrtSour,L"\t", 1U, pugi::encoding_utf8);
		strSourText = QString::fromUtf8(wrtSour.result);
		strCompText = QString::fromUtf8(wrtSour.result);
	} 
	else if (pDelivNode->m_nType == 2)
	{
		oPugiCompNode.print(wrtComp,L"\t", 1U, pugi::encoding_utf8);
		//strSourText = "";
		strCompText = QString::fromUtf8(wrtComp.result);
	} 
	else if (pDelivNode->m_nType == 4)
	{
		oPugiSourNode.print(wrtSour,L"\t", 1U, pugi::encoding_utf8);
		strSourText = QString::fromUtf8(wrtSour.result);
		//strCompText = "";
	}
	else if (pDelivNode->m_nType == 6)
	{
		oPugiSourNode.print(wrtSour,L"\t", 1U, pugi::encoding_utf8);
		oPugiCompNode.print(wrtComp,L"\t", 1U, pugi::encoding_utf8);
 		strSourText = QString::fromUtf8(wrtSour.result);
 		strCompText = QString::fromUtf8(wrtComp.result);
	}

	emit sig_UpdateComparedTextView(strSourText,strCompText);
}

void QSCLXmlComparedTree::PopulateTreeCtrl(pugi::xml_node &oPugiNode, QExBaseTreeWidgetItem *pItem)
{
	if (oPugiNode.type() == 3)
	{
		return;
	}

	CExBaseObject *pObj = NULL;
	CString strNodeAllDesc;
	GetPugixmlAttrDesc(oPugiNode ,strNodeAllDesc);
	pugi::xml_node oPugiChild = oPugiNode.first_child();

	//HTREEITEM hItem = GetTreeCtrl().InsertItem(strNodeAllDesc ,0 ,1 ,hParent);
	QExBaseTreeWidgetItem *pSecondItem = NewItem(pItem,pObj);
	pSecondItem->setText(0,strNodeAllDesc);
	pSecondItem->setExpanded(TRUE);

	CString strChild;
	while(oPugiChild != NULL)
	{
		strChild = oPugiChild.name();
		if ((strChild != _T("Private"))&&(oPugiChild.type() != 5))
		{
			PopulateTreeCtrl(oPugiChild, pItem);
		}

		oPugiChild = oPugiChild.next_sibling();
	}
}

void QSCLXmlComparedTree::PopulateTreeCtrl(QDeliverPugiNode *pDeliverNode, QExBaseTreeWidgetItem *pItem)
{
	ASSERT(pDeliverNode != NULL);
	pugi::xml_node oPugiSourNode(pDeliverNode->m_pSourNode);
	pugi::xml_node oPugiCompNode(pDeliverNode->m_pCompNode);
	pugi::xml_node oPugiNode;
	pugi::xml_node oPugiChild;
	pugi::xml_node oPugiCompChild;
	QExBaseTreeWidgetItem *pSecondItem = NULL;
	long nCtrlID = pDeliverNode->m_nType;
	CExBaseObject *pCurObj = NULL;

	if (nCtrlID == 2)
	{
		oPugiNode = oPugiCompNode;
	} 
	else
	{
		oPugiNode = oPugiSourNode;
	}

	if (oPugiNode.type() == 3)//node_pcdata   text文本的
	{
		return;
	}

	CString strNodeAllDesc;

	if (nCtrlID == 6)
	{
		if (oPugiSourNode.compare_all_attribue(oPugiCompNode))
		{
			GetPugixmlAttrDesc(oPugiSourNode ,strNodeAllDesc);
// 			hItem = m_treeCtrl.InsertItem(strNodeAllDesc ,0 , 1 ,hParent);
// 			m_treeCtrl.SetItemData(hItem ,(DWORD)(pDeliverNode));
			pSecondItem = NewItem(pItem,pCurObj);
			pSecondItem->setText(0,strNodeAllDesc);
			pSecondItem->setExpanded(TRUE);
			pSecondItem->m_pItemData = pDeliverNode;
		} 
		else
		{
			CString strModifyDesc;
			GetPugixmlAttrDesc(oPugiSourNode ,strModifyDesc);
			strModifyDesc += _T("  <----->  ");
			GetPugixmlAttrDesc(oPugiCompNode ,strNodeAllDesc);
			strModifyDesc += strNodeAllDesc;
			//hItem = m_treeCtrl.InsertItem(strModifyDesc ,nCtrlID ,nCtrlID + 1 ,hParent);
			pSecondItem = NewItem(pItem,pCurObj);
			pSecondItem->setText(0,strModifyDesc);
			pSecondItem->setExpanded(TRUE);

			if (m_nDifNums == 999)
			{
				m_nDifNums++;
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("比对差异超过1000,忽略显示;"));
			}

			if (m_nDifNums<1000)
			{
				CString strMSG;
				m_nDifNums++;
				//strMSG.Format(_T("比对差异%d(修改):%s;"),m_nDifNums,strModifyDesc);
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("比对差异%d(修改):%s;"),m_nDifNums,strModifyDesc.GetString());
			}

			//m_treeCtrl.SetItemData(hItem ,(DWORD)(pDeliverNode));
			pSecondItem->m_pItemData = pDeliverNode;
		}
	} 
	else
	{
		GetPugixmlAttrDesc(oPugiNode ,strNodeAllDesc);
		//hItem = m_treeCtrl.InsertItem(strNodeAllDesc ,nCtrlID ,nCtrlID + 1 ,hParent);
		pSecondItem = NewItem(pItem,pCurObj);
		pSecondItem->setText(0,strNodeAllDesc);
		pSecondItem->setExpanded(TRUE);

		if (m_nDifNums == 999)
		{
			m_nDifNums++;
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("比对差异超过1000,忽略显示;"));
		}

		int nTmp1 = -1,nTmp2 = -1;
		//m_treeCtrl.GetItemImage(hParent,nTmp1,nTmp2);

		if ((nTmp1 != 2)&&(nTmp1 != 4))
		{
			if ((nCtrlID == 2)&&(m_nDifNums<1000))
			{
				CString strMSG;
				m_nDifNums++;
				//strMSG.Format(_T("比对差异%d(删除):%s;"),m_nDifNums,strNodeAllDesc);
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("比对差异%d(删除):%s;"),m_nDifNums,strNodeAllDesc.GetString());
			} 
			else if ((nCtrlID == 4)&&(m_nDifNums<1000))
			{
				CString strMSG;
				m_nDifNums++;
				//strMSG.Format(_T("比对差异%d(新增):%s;"),m_nDifNums,strNodeAllDesc);
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("比对差异%d(新增):%s;"),m_nDifNums,strNodeAllDesc.GetString());
			}
		}

		//m_treeCtrl.SetItemData(hItem ,(DWORD)(pDeliverNode));
		pSecondItem->m_pItemData = pDeliverNode;
	}

	CString strChild;
	QDeliverPugiNode *pDeliverNodeNew = NULL;
	oPugiChild = oPugiNode.first_child();

	while(oPugiChild != NULL)
	{
		strChild = oPugiChild.name();
		if ((strChild != _T("Private"))&&(oPugiChild.type() != 5))//node_comment
		{
			pDeliverNodeNew = new QDeliverPugiNode();
			AddNewChild(pDeliverNodeNew);

			if (nCtrlID == 6)
			{
				oPugiCompChild = oPugiCompNode.find_child_by_attribute(oPugiChild.name() ,oPugiChild.first_attribute() ,oPugiChild.first_attribute().next_attribute(),oPugiChild.first_attribute().next_attribute().next_attribute(),
					oPugiChild.first_attribute().next_attribute().next_attribute().next_attribute() ,oPugiChild.first_attribute().next_attribute().next_attribute().next_attribute().next_attribute() ,
					oPugiChild.first_attribute().next_attribute().next_attribute().next_attribute().next_attribute().next_attribute(),oPugiChild.first_attribute().next_attribute().next_attribute().next_attribute().next_attribute().next_attribute().next_attribute(),
					oPugiChild.first_attribute().next_attribute().next_attribute().next_attribute().next_attribute().next_attribute().next_attribute().next_attribute() ,oPugiChild.attribute_number());

				if (oPugiCompChild != NULL)
				{
					pDeliverNodeNew->m_nType = nCtrlID;
				} 
				else if ((oPugiCompChild = oPugiCompNode.find_child_by_attribute(oPugiChild.name() ,oPugiChild.special_attribute())) != NULL )
				{
					pDeliverNodeNew->m_nType = nCtrlID;
				} 
				else
				{
					pDeliverNodeNew->m_nType = 4;
				}

				pDeliverNodeNew->m_pSourNode = oPugiChild.internal_object();
				pDeliverNodeNew->m_pCompNode = oPugiCompChild.internal_object();
			} 
			else if (nCtrlID == 2)
			{
				pDeliverNodeNew->m_pSourNode = NULL;
				pDeliverNodeNew->m_pCompNode = oPugiChild.internal_object();
				pDeliverNodeNew->m_nType = nCtrlID;
			} 
			else
			{
				pDeliverNodeNew->m_pSourNode = oPugiChild.internal_object();
				pDeliverNodeNew->m_pCompNode = NULL;
				pDeliverNodeNew->m_nType = nCtrlID;
			}

			PopulateTreeCtrl(pDeliverNodeNew, pSecondItem);
		}

		oPugiChild = oPugiChild.next_sibling();
	}

	if (nCtrlID == 6)
	{
		oPugiCompChild = oPugiCompNode.first_child();

		while(oPugiCompChild != NULL)
		{
			strChild = oPugiCompChild.name();
			if ((strChild != _T("Private"))&&(oPugiCompChild.type() != 5))//node_comment
			{
				if ((oPugiSourNode.find_child_by_attribute(oPugiCompChild.name() ,oPugiCompChild.first_attribute() ,oPugiCompChild.first_attribute().next_attribute(),oPugiCompChild.first_attribute().next_attribute().next_attribute(),
					oPugiCompChild.first_attribute().next_attribute().next_attribute().next_attribute() ,oPugiCompChild.first_attribute().next_attribute().next_attribute().next_attribute().next_attribute() ,
					oPugiCompChild.first_attribute().next_attribute().next_attribute().next_attribute().next_attribute().next_attribute(),oPugiCompChild.first_attribute().next_attribute().next_attribute().next_attribute().next_attribute().next_attribute().next_attribute(),
					oPugiCompChild.first_attribute().next_attribute().next_attribute().next_attribute().next_attribute().next_attribute().next_attribute().next_attribute() ,oPugiCompChild.attribute_number()) == NULL))
				{
					pDeliverNodeNew = new QDeliverPugiNode();
					AddNewChild(pDeliverNodeNew);
					pDeliverNodeNew->m_pSourNode = NULL;
					pDeliverNodeNew->m_pCompNode = oPugiCompChild.internal_object();
					pDeliverNodeNew->m_nType = 2;
					PopulateTreeCtrl(pDeliverNodeNew, /*hItem*/pSecondItem);
				}
			}
			oPugiCompChild = oPugiCompChild.next_sibling();
		}
	}

	InsertImage(pSecondItem,nCtrlID);
}


void QSCLXmlComparedTree::GetPugixmlAttrDesc(pugi::xml_node &oPugiNode, CString &strNodeAllDesc)
{
	strNodeAllDesc = oPugiNode.name();	
	pugi::xml_node oPugiChild = oPugiNode.first_child();
	CString strText;

	if (oPugiChild != NULL)
	{
		if (oPugiChild.type() == 3)
		{
			strNodeAllDesc += "=";
			strText = oPugiChild.text().as_string();
			strNodeAllDesc += /*oPugiChild.text().as_string()*/strText;
		}
	} 	

	pugi::xml_attribute oAttr = oPugiNode.first_attribute();

	while(oAttr != NULL)
	{
		strNodeAllDesc += " ";
		strText = oAttr.name();
		strNodeAllDesc += strText;
		strNodeAllDesc += _T("=");
		strNodeAllDesc += "\"";
		strText = oAttr.value();
		strNodeAllDesc += strText;
		strNodeAllDesc += "\"";

		oAttr = oAttr.next_attribute();
	}
}


void QSCLXmlComparedTree::InsertImage(QExBaseTreeWidgetItem *pItem,long nCtrlID)
{
	CString strPicPath;
	strPicPath = _P_GetResourcePath();

	if (nCtrlID == 2)
	{
		strPicPath += _T("delete.png");
		//strPicPath = ":/resource/images/delete.png";
	}
	else if (nCtrlID == 4)
	{
		strPicPath += _T("add.png");
		//strPicPath = ":/resource/images/add.png";
	}
	else if (nCtrlID == 6)
	{
		strPicPath += _T("modify.png");
		//strPicPath = ":/resource/images/modify.png";
	}
	pItem->setIcon(0,QIcon(strPicPath));
}
