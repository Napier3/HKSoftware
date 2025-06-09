#include "QSCLComparedTreeCtrl.h"
#include "../../../../Module/API/GlobalConfigApi.h"


QSCLComparedTreeCtrl::QSCLComparedTreeCtrl(QWidget *parent,CString strSCLFilePath, CString strCompareFilePath):QTreeWidget(parent)
{
	_P_InitSystemPath();
	setStyle(QStyleFactory::create("windows"));
	setHeaderHidden(true);
	setStyleSheet("QTreeWidget::item{height:30px}");
	m_bIsReading = FALSE;

	m_pPugixmlSoureDoc = NULL;
	m_pPugixmlCompareDoc = NULL;
	m_nIEDNumber = 0;
	m_nDifNums = 0;

	m_strSCLFilePath = strSCLFilePath;
	m_strCompareFilePath = strCompareFilePath;

// 	m_strSCLFilePath = _T("D:\\Program Files\\EPOTO\\Stt\\Library\\沈南500kV变电站.scd");
// 	m_strCompareFilePath = _T("D:\\Program Files\\EPOTO\\Stt\\Library\\龙山变130823.scd");

	m_pLoadFileThread = CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)ShowModelTreeThread,(LPVOID)this,0,NULL);
	connect(this, SIGNAL(itemClicked(QTreeWidgetItem*, int)), SLOT(slot_TreeItemClicked(QTreeWidgetItem*, int)));
}

QSCLComparedTreeCtrl::~QSCLComparedTreeCtrl()
{

}

pugi::xml_node QSCLComparedTreeCtrl::GetPugixmlSourceRoot()
{
	const QByteArray baTmp = m_strSCLFilePath.toLocal8Bit();
	const char *pzfFilePath = baTmp.data();

	if (m_pPugixmlSoureDoc == NULL)
	{
		m_bIsReading = TRUE;
		m_pPugixmlSoureDoc = new pugi::xml_document();

		if (!m_pPugixmlSoureDoc->load_file(pzfFilePath,pugi::parse_default,pugi::encoding_utf8))
		{
			m_bIsReading = FALSE;
			delete m_pPugixmlSoureDoc;
			m_pPugixmlSoureDoc = NULL;
			return (pugi::xml_node)NULL;
		}

		m_bIsReading = FALSE;
	}

	return m_pPugixmlSoureDoc->document_element();
}

pugi::xml_node QSCLComparedTreeCtrl::GetPugixmlCompareRoot()
{
	const QByteArray baTmp = m_strCompareFilePath.toLocal8Bit();
	const char *pCompareFilePath = baTmp.data();

	if (m_pPugixmlCompareDoc == NULL)
	{
		m_bIsReading = TRUE;
		m_pPugixmlCompareDoc = new pugi::xml_document();

		if (!m_pPugixmlCompareDoc->load_file(pCompareFilePath,pugi::parse_default,pugi::encoding_utf8))
		{
			m_bIsReading = FALSE;
			delete m_pPugixmlCompareDoc;
			m_pPugixmlCompareDoc = NULL;
			return (pugi::xml_node)NULL;
		}

		m_bIsReading = FALSE;
	}

	return m_pPugixmlCompareDoc->document_element();
}

UINT QSCLComparedTreeCtrl::ShowModelTreeThread(LPVOID pParam)
{
	QSCLComparedTreeCtrl *pSclCompareTreeCtrl = (QSCLComparedTreeCtrl *)pParam;
	pSclCompareTreeCtrl->ShowModelTree();
	pSclCompareTreeCtrl->m_pLoadFileThread = NULL;
	return 1;
}

void QSCLComparedTreeCtrl::ShowModelTree()
{
	DeleteAll();
	//clear();
	ShowMainTreeCtrl();
	return;
}

void QSCLComparedTreeCtrl::ShowMainTreeCtrl()
{
	while (m_bIsReading)
	{
		Sleep(500);
	}

	pugi::xml_node oPugixmlSourceRoot = GetPugixmlSourceRoot();
	pugi::xml_node oPugixmlCompareRoot = GetPugixmlCompareRoot();

	CString nodeName = m_strSCLFilePath;
	long nIndex = nodeName.ReverseFind('\\');
	nodeName = nodeName.Mid(nIndex+1);

	//HTREEITEM hItem = InsertItem(nodeName ,10 ,11 ,TVI_ROOT);
	CExBaseObject *pCurObj = NULL;
	m_pRootItem = NewItem(NULL,pCurObj);//根节点
	m_pRootItem->setText(0,nodeName);
	m_pRootItem->setExpanded(TRUE);

	pugi::xml_node oPugiSourceChild = oPugixmlSourceRoot.first_child();
	CString strName;

	while(oPugiSourceChild != NULL)
	{
		strName = oPugiSourceChild.name();
		if (strName != _T("Private") )
		{
			PopulateMainTreeCtrl(oPugiSourceChild, oPugixmlCompareRoot, /*hItem*/m_pRootItem);
		}

		oPugiSourceChild = oPugiSourceChild.next_sibling();
	}

	pugi::xml_node oPugiCompChild = oPugixmlCompareRoot.child(L"IED");
	QDeliverPugiNode *pDeliverNode = NULL;
	//HTREEITEM hSecondItem = NULL;
	QExBaseTreeWidgetItem *hSecondItem = NULL;
	while(oPugiCompChild != NULL)
	{
		if (oPugixmlSourceRoot.find_child_by_attribute(L"IED" ,L"name" ,oPugiCompChild.attribute(L"name").value()) == NULL)
		{
			GetAttrNameAndDescValue(oPugiCompChild, &strName);

			pDeliverNode = new QDeliverPugiNode();
			AddNewChild(pDeliverNode);
			pDeliverNode->m_pSourNode = NULL;
			pDeliverNode->m_pCompNode = oPugiCompChild.internal_object();
			pDeliverNode->m_nType = 2;
// 			hSecondItem = InsertItem(strName , 2 ,3 ,m_hIedItem);
// 			SetItemData(hSecondItem ,(DWORD)(pDeliverNode));
			hSecondItem = NewItem(m_pIedItem,pCurObj);
			hSecondItem->setText(0,strName);
			hSecondItem->m_pItemData = pDeliverNode;
			
			InsertImage(hSecondItem,pDeliverNode->m_nType);
			hSecondItem->setExpanded(TRUE);
		}

		oPugiCompChild = oPugiCompChild.next_sibling(L"IED");
	}
}

void QSCLComparedTreeCtrl::PopulateMainTreeCtrl(pugi::xml_node oPugiSourceNode, pugi::xml_node oPugixmlCompareRoot, /* HTREEITEM hParent*/QExBaseTreeWidgetItem * pItem)
{
	CString strSourNodeVal,strCompareNodeVal;
	strSourNodeVal = oPugiSourceNode.name();

	long nCtrlID = 0;
	CExBaseObject *pCurObj = NULL;
	CString strName;
	pugi::xml_node oPugiCompareNode = oPugixmlCompareRoot.child(strSourNodeVal.AllocSysString());

	//HTREEITEM hSecondItem = NULL;
	QExBaseTreeWidgetItem *SecondItem = NULL;
	QDeliverPugiNode *pDeliverNode = NULL;

	if (strSourNodeVal == "Header")
	{
		if (oPugiCompareNode == NULL)
			nCtrlID = 4;
		else
			nCtrlID = CompareHearderPort(oPugiSourceNode ,oPugiCompareNode );

		pDeliverNode = new QDeliverPugiNode();
		AddNewChild(pDeliverNode);
		pDeliverNode->m_pSourNode = oPugiSourceNode.internal_object();
		pDeliverNode->m_pCompNode = oPugiCompareNode.internal_object();
		pDeliverNode->m_nType = nCtrlID;
		//hSecondItem = InsertItem(_T("头文件") ,nCtrlID ,nCtrlID + 1 ,hParent);
		//SetItemData(hSecondItem ,(DWORD)(pDeliverNode));
		SecondItem = NewItem(pItem,pCurObj);
		strName = _T("头文件");
		SecondItem->setText(0,strName);
		SecondItem->m_pItemData = pDeliverNode;
		
		InsertImage(SecondItem,pDeliverNode->m_nType);
		slot_TreeItemClicked(SecondItem,0);

		if ((nCtrlID == 4)&&(oPugiCompareNode != NULL))
		{
			pDeliverNode = new QDeliverPugiNode();
			AddNewChild(pDeliverNode);
			pDeliverNode->m_pSourNode = oPugiSourceNode.internal_object();
			pDeliverNode->m_pCompNode = oPugiCompareNode.internal_object();
			pDeliverNode->m_nType = 2;
// 			hSecondItem = InsertItem(_T("头文件") ,2 ,3 ,hParent);
// 			SetItemData(hSecondItem ,(DWORD)(pDeliverNode));
			SecondItem = NewItem(pItem,pCurObj);
			strName = _T("头文件");
			SecondItem->setText(0,strName);
			SecondItem->setExpanded(TRUE);

			SecondItem->m_pItemData = pDeliverNode;
		}
		InsertImage(SecondItem,pDeliverNode->m_nType);
	}
	else if (strSourNodeVal == "Substation")
	{
		if (oPugiCompareNode == NULL)
			nCtrlID = 4;
		else
			nCtrlID = CompareSubstationPort(oPugiSourceNode ,oPugiCompareNode );

		pDeliverNode = new QDeliverPugiNode();
		AddNewChild(pDeliverNode);
		pDeliverNode->m_pSourNode = oPugiSourceNode.internal_object();
		pDeliverNode->m_pCompNode = oPugiCompareNode.internal_object();
 		pDeliverNode->m_nType = nCtrlID;
// 		hSecondItem = InsertItem(_T("变电站") ,nCtrlID ,nCtrlID + 1 ,hParent);
// 		SetItemData(hSecondItem ,(DWORD)(pDeliverNode));
		SecondItem = NewItem(pItem,pCurObj);
		strName = _T("变电站");
		SecondItem->setText(0,strName);
		SecondItem->m_pItemData = pDeliverNode;
		InsertImage(SecondItem,pDeliverNode->m_nType);

		if ((nCtrlID == 4)&&(oPugiCompareNode != NULL))
		{
			pDeliverNode = new QDeliverPugiNode();
			AddNewChild(pDeliverNode);
			pDeliverNode->m_pSourNode = oPugiSourceNode.internal_object();
			pDeliverNode->m_pCompNode = oPugiCompareNode.internal_object();
			pDeliverNode->m_nType = 2;
			//hSecondItem = InsertItem(_T("变电站") ,2 ,3 ,hParent);
			//SetItemData(hSecondItem ,(DWORD)(pDeliverNode));
			SecondItem = NewItem(pItem,pCurObj);
			strName = _T("变电站");
			SecondItem->setText(0,strName);
			SecondItem->setExpanded(TRUE);

			SecondItem->m_pItemData = pDeliverNode;
		}

		InsertImage(SecondItem,pDeliverNode->m_nType);
	}
	else if (strSourNodeVal == "Communication")
	{
		CString nodeValue;

		//hSecondItem = InsertItem(_T("通讯网络") , 0 ,1,hParent);
		SecondItem = NewItem(pItem,pCurObj);
		strName = _T("通讯网络");
		SecondItem->setText(0,strName);
		SecondItem->setExpanded(TRUE);

		nodeValue = "SubNetwork-";

		QExBaseTreeWidgetItem *hThirdItem = NULL;
		pugi::xml_node oPugiSourChild = oPugiSourceNode.first_child();
		pugi::xml_node oPugiCompChild;
		CString strNode;

		while(oPugiSourChild != NULL)
		{
			strNode = oPugiSourChild.name();

			if( strNode != _T("SubNetwork"))//排除节点名称不是SubNetwork的节点
			{
				oPugiSourChild = oPugiSourChild.next_sibling();
				continue;
			}

			GetAttrNameAndDescValue(oPugiSourChild, &strSourNodeVal);
			strSourNodeVal = nodeValue + strSourNodeVal;

			oPugiCompChild = oPugiCompareNode.find_child_by_attribute(strNode.AllocSysString() ,oPugiSourChild.attribute(L"name").name() , oPugiSourChild.attribute(L"name").value());

			if (oPugiCompChild == NULL)
				nCtrlID = 4;
			else
				nCtrlID = CompareCommonPort(oPugiSourChild ,oPugiCompChild );

			pDeliverNode = new QDeliverPugiNode();
			AddNewChild(pDeliverNode);
			pDeliverNode->m_pSourNode = oPugiSourChild.internal_object();
			pDeliverNode->m_pCompNode = oPugiCompChild.internal_object();
			pDeliverNode->m_nType = nCtrlID;
// 			hThirdItem = InsertItem(strSourNodeVal , nCtrlID ,nCtrlID + 1 ,hSecondItem);
// 			SetItemData(hThirdItem ,(DWORD)(pDeliverNode));
			hThirdItem = NewItem(SecondItem,pCurObj);
			hThirdItem->setText(0,strSourNodeVal);
			hThirdItem->m_pItemData = pDeliverNode;
			hThirdItem->setExpanded(TRUE);

			InsertImage(hThirdItem,pDeliverNode->m_nType);

			oPugiSourChild = oPugiSourChild.next_sibling();
		}

		oPugiCompChild = oPugiCompareNode.first_child();

		while(oPugiCompChild != NULL)
		{
			strNode = oPugiCompChild.name();

			if( strNode != _T("SubNetwork"))//排除节点名称不是SubNetwork的节点
			{
				oPugiCompChild = oPugiCompChild.next_sibling();
				continue;
			}

			GetAttrNameAndDescValue(oPugiCompChild, &strSourNodeVal);
			strSourNodeVal = nodeValue + strSourNodeVal;

			oPugiSourChild = oPugiSourceNode.find_child_by_attribute(strNode.AllocSysString() ,oPugiCompChild.attribute(L"name").name() , oPugiCompChild.attribute(L"name").value());

			if (oPugiSourChild == NULL)
			{
				nCtrlID = 2;
				pDeliverNode = new QDeliverPugiNode();
				AddNewChild(pDeliverNode);
				pDeliverNode->m_pSourNode = oPugiSourChild.internal_object();
				pDeliverNode->m_pCompNode = oPugiCompChild.internal_object();
				pDeliverNode->m_nType = nCtrlID;
// 				hThirdItem = InsertItem(strSourNodeVal , nCtrlID ,nCtrlID + 1 ,hSecondItem);
// 				SetItemData(hThirdItem ,(DWORD)(pDeliverNode));
				hThirdItem = NewItem(SecondItem,pCurObj);
				hThirdItem->setText(0,strSourNodeVal);
				hThirdItem->m_pItemData = pDeliverNode;
				hThirdItem->setExpanded(TRUE);

				InsertImage(hThirdItem,pDeliverNode->m_nType);
			}

			oPugiCompChild = oPugiCompChild.next_sibling();
		}
	}
	else if (strSourNodeVal == "IED")
	{
		if (m_nIEDNumber == 0)
		{
			//m_hIedItem = InsertItem(_T("IED列表") , 0 ,1 ,hParent);
			m_pIedItem = NewItem(pItem,pCurObj);
		    strName = _T("IED列表");
		    m_pIedItem->setText(0,strName);
			m_pIedItem->setExpanded(TRUE);
		}

		oPugiCompareNode = oPugixmlCompareRoot.find_child_by_attribute(strSourNodeVal.AllocSysString() ,oPugiSourceNode.attribute(L"name").name() , oPugiSourceNode.attribute(L"name").value());
		if (oPugiCompareNode == NULL)
		{
			nCtrlID = 4;
		}
		else
		{
			nCtrlID = CompareCommonPort(oPugiSourceNode ,oPugiCompareNode);
		}

		GetAttrNameAndDescValue(oPugiSourceNode, &strSourNodeVal);

		pDeliverNode = new QDeliverPugiNode();
		AddNewChild(pDeliverNode);
		pDeliverNode->m_pSourNode = oPugiSourceNode.internal_object();
		pDeliverNode->m_pCompNode = oPugiCompareNode.internal_object();
		pDeliverNode->m_nType = nCtrlID;
// 		hSecondItem = InsertItem(strSourNodeVal , nCtrlID ,nCtrlID + 1 ,m_hIedItem);
// 		SetItemData(hSecondItem ,(DWORD)(pDeliverNode));
		SecondItem = NewItem(m_pIedItem,pCurObj);
		SecondItem->setText(0,strSourNodeVal); 
		SecondItem->m_pItemData = pDeliverNode;
		SecondItem->setExpanded(TRUE);
		InsertImage(SecondItem,pDeliverNode->m_nType);
		m_nIEDNumber++;

	}
	else if (strSourNodeVal == "DataTypeTemplates")
	{
		//hSecondItem = InsertItem(_T("数据类型模板库") , 0 ,1 ,hParent);
		SecondItem = NewItem(pItem,pCurObj);
		strName = _T("数据类型模板库");
		SecondItem->setText(0,strName); 
		SecondItem->setExpanded(TRUE);

		pugi::xml_node oPugiSourChild = oPugiSourceNode.child(L"LNodeType");
		pugi::xml_node oPugiCompChild = oPugiCompareNode.child(L"LNodeType");

		nCtrlID = CompareDataTypeTempPort(_T("LNodeType") ,oPugiSourChild ,oPugiCompChild);

		pDeliverNode = new QDeliverPugiNode();
		AddNewChild(pDeliverNode);
		pDeliverNode->m_pSourNode = oPugiSourChild.internal_object();
		pDeliverNode->m_pCompNode = oPugiCompChild.internal_object();
		pDeliverNode->m_nType = nCtrlID;
		//HTREEITEM hThirdItem = InsertItem(_T("LNodeType") , nCtrlID ,nCtrlID + 1 ,hSecondItem);
		//SetItemData(hThirdItem ,(DWORD)(pDeliverNode));
		QExBaseTreeWidgetItem *hThirdItem = NewItem(SecondItem,pCurObj);
		hThirdItem->setText(0,_T("LNodeType")); 
		hThirdItem->m_pItemData = pDeliverNode;
		hThirdItem->setExpanded(TRUE);
		InsertImage(hThirdItem,pDeliverNode->m_nType);


		oPugiSourChild = oPugiSourceNode.child(L"DOType");
		oPugiCompChild = oPugiCompareNode.child(L"DOType");
		nCtrlID = CompareDataTypeTempPort(_T("DOType") ,oPugiSourChild ,oPugiCompChild);

		pDeliverNode = new QDeliverPugiNode();
		AddNewChild(pDeliverNode);
		pDeliverNode->m_pSourNode = oPugiSourChild.internal_object();
		pDeliverNode->m_pCompNode = oPugiCompChild.internal_object();
		pDeliverNode->m_nType = nCtrlID;
// 		hThirdItem = InsertItem( _T("DOType") , nCtrlID ,nCtrlID + 1 ,hSecondItem);
// 		SetItemData(hThirdItem ,(DWORD)(pDeliverNode));
		hThirdItem = NewItem(SecondItem,pCurObj);
		hThirdItem->setText(0,_T("DOType"));
		hThirdItem->m_pItemData = pDeliverNode;
		hThirdItem->setExpanded(TRUE);
		InsertImage(hThirdItem,pDeliverNode->m_nType);

		oPugiSourChild = oPugiSourceNode.child(L"DAType");
		oPugiCompChild = oPugiCompareNode.child(L"DAType");
		nCtrlID = CompareDataTypeTempPort(_T("DAType") ,oPugiSourChild ,oPugiCompChild);

		pDeliverNode = new QDeliverPugiNode();
		AddNewChild(pDeliverNode);
		pDeliverNode->m_pSourNode = oPugiSourChild.internal_object();
		pDeliverNode->m_pCompNode = oPugiCompChild.internal_object();
		pDeliverNode->m_nType = nCtrlID;
// 		hThirdItem = InsertItem(_T("DAType") , nCtrlID ,nCtrlID + 1 , hSecondItem);
// 		SetItemData(hThirdItem ,(DWORD)(pDeliverNode));
		hThirdItem = NewItem(SecondItem,pCurObj);
		hThirdItem->setText(0,_T("DAType")); 
		hThirdItem->m_pItemData = pDeliverNode;
		hThirdItem->setExpanded(TRUE);
		
		InsertImage(hThirdItem,pDeliverNode->m_nType);

		oPugiSourChild = oPugiSourceNode.child(L"EnumType");
		oPugiCompChild = oPugiCompareNode.child(L"EnumType");
		nCtrlID = CompareDataTypeTempPort(_T("EnumType") ,oPugiSourChild ,oPugiCompChild);
		pDeliverNode = new QDeliverPugiNode();
		AddNewChild(pDeliverNode);
		pDeliverNode->m_pSourNode = oPugiSourChild.internal_object();
		pDeliverNode->m_pCompNode = oPugiCompChild.internal_object();
		pDeliverNode->m_nType = nCtrlID;
// 		hThirdItem = InsertItem(_T("EnumType") , nCtrlID ,nCtrlID + 1 , hSecondItem);
// 		SetItemData(hThirdItem ,(DWORD)(pDeliverNode));
		hThirdItem = NewItem(SecondItem,pCurObj);
		hThirdItem->setText(0,_T("EnumType")); 
		hThirdItem->m_pItemData = pDeliverNode;
		hThirdItem->setExpanded(TRUE);
		
		InsertImage(hThirdItem,pDeliverNode->m_nType);
	}
	else
	{
		pDeliverNode = new QDeliverPugiNode();
		AddNewChild(pDeliverNode);
		pDeliverNode->m_pSourNode = oPugiSourceNode.internal_object();
		pDeliverNode->m_pCompNode = oPugiCompareNode.internal_object();
		pDeliverNode->m_nType = 0;
// 		hSecondItem = InsertItem(strSourNodeVal , 0 ,1, hParent);
// 		SetItemData(hSecondItem ,(DWORD)(pDeliverNode));
		SecondItem = NewItem(pItem,pCurObj);
		SecondItem->setText(0,strSourNodeVal); 
		SecondItem->m_pItemData = pDeliverNode;
		SecondItem->setExpanded(TRUE);

		InsertImage(SecondItem,pDeliverNode->m_nType);
	}
}


long QSCLComparedTreeCtrl::CompareHearderPort(pugi::xml_node oPugiSourceNode ,pugi::xml_node oPugiCompareNode )
{
	pugi::xml_attribute oPugiSourAttr = oPugiSourceNode.attribute(L"id");
	pugi::xml_attribute oPugiCompareAttr = oPugiCompareNode.attribute(L"id");

	CString strSourValue , strCompValue;
	strSourValue = oPugiSourAttr.value();
	strCompValue = oPugiCompareAttr.value();

	if (strSourValue != strCompValue)
	{
		return 4;
	}
	else if (oPugiSourceNode.attribute_number() != oPugiCompareNode.attribute_number())
	{
		return 6;
	}

	oPugiSourAttr = oPugiSourceNode.first_attribute();

	while(oPugiSourAttr != NULL)
	{
		oPugiCompareAttr = oPugiCompareNode.attribute(oPugiSourAttr.name());

		if (oPugiCompareAttr == NULL)
			return 6;

		strSourValue = oPugiSourAttr.value();
		strCompValue = oPugiCompareAttr.value();

		if (strSourValue != strCompValue)
			return 6;

		oPugiSourAttr = oPugiSourAttr.next_attribute();
	}

	return 0;
}

long QSCLComparedTreeCtrl::CompareSubstationPort(pugi::xml_node oPugiSourceNode ,pugi::xml_node oPugiCompareNode )
{
	pugi::xml_attribute oPugiSourAttr = oPugiSourceNode.attribute(L"name");
	pugi::xml_attribute oPugiCompareAttr = oPugiCompareNode.attribute(L"name");

	if (!pugi::strequal(oPugiSourAttr.value() ,oPugiCompareAttr.value()))
	{
		return 4;
	}
	else if (oPugiSourceNode.attribute_number() != oPugiCompareNode.attribute_number())
	{
		return 6;
	}

	oPugiSourAttr = oPugiSourceNode.first_attribute();

	while(oPugiSourAttr != NULL)
	{
		oPugiCompareAttr = oPugiCompareNode.attribute(oPugiSourAttr.name());

		if (oPugiCompareAttr == NULL)
			return 6;

		if (!pugi::strequal(oPugiSourAttr.value() ,oPugiCompareAttr.value()))
			return 6;

		oPugiSourAttr = oPugiSourAttr.next_attribute();
	}

	return CompareChildAndAttr(oPugiSourceNode , oPugiCompareNode);
}


long QSCLComparedTreeCtrl::CompareDataTypeTempPort(CString strNodeType, pugi::xml_node oPugiSourceNode ,pugi::xml_node oPugiCompareNode )
{
	if ((oPugiSourceNode == NULL)&&(oPugiCompareNode == NULL))
		return 0;
	else if (oPugiSourceNode == NULL)
		return 2;
	else if (oPugiCompareNode == NULL)
		return 4;

	pugi::xml_node oPugiSourNew = oPugiSourceNode;
	pugi::xml_node oPugiCompNew;

	long nCtrlID;

	while(oPugiSourNew != NULL)
	{
		oPugiCompNew = oPugiCompareNode.find_nextnode_by_attribute(strNodeType.AllocSysString() ,L"id" ,oPugiSourNew.attribute(L"id").value());

		if (oPugiCompNew == NULL)
			return 6;
		else if ((nCtrlID = CompareCommonPort(oPugiSourNew ,oPugiCompNew)) != 0)
			return nCtrlID;

		oPugiSourNew = oPugiSourNew.next_sibling(strNodeType.AllocSysString());
	}

	oPugiCompNew = oPugiCompareNode;

	while(oPugiCompNew != NULL)
	{
		oPugiSourNew = oPugiSourceNode.find_nextnode_by_attribute(strNodeType.AllocSysString() ,L"id" ,oPugiCompNew.attribute(L"id").value());

		if (oPugiSourNew == NULL)
			return 6;

		oPugiCompNew = oPugiCompNew.next_sibling(strNodeType.AllocSysString());
	}

	return 0;
}

long QSCLComparedTreeCtrl::CompareCommonPort(pugi::xml_node oPugiSourceNode ,pugi::xml_node oPugiCompareNode )
{
	pugi::xml_attribute oPugiSourAttr;
	pugi::xml_attribute oPugiCompareAttr;

	if (oPugiSourceNode.attribute_number() != oPugiCompareNode.attribute_number())
	{
		return 6;
	}

	oPugiSourAttr = oPugiSourceNode.first_attribute();

	while(oPugiSourAttr != NULL)
	{
		oPugiCompareAttr = oPugiCompareNode.attribute(oPugiSourAttr.name());

		if (oPugiCompareAttr == NULL)
			return 6;

		if (!pugi::strequal(oPugiSourAttr.value() ,oPugiCompareAttr.value()))
			return 6;

		oPugiSourAttr = oPugiSourAttr.next_attribute();
	}

	return CompareChildAndAttr(oPugiSourceNode , oPugiCompareNode);
}

long QSCLComparedTreeCtrl::CompareChildAndAttr(pugi::xml_node oPugiSourceNode ,pugi::xml_node oPugiCompareNode)
{
	if (oPugiSourceNode.child_number() != oPugiCompareNode.child_number())
		return 6;

	pugi::xml_node oPugiSourChild = oPugiSourceNode.first_child();
	pugi::xml_node oPugiCompChild;
	long nCtrlID = 0;
	CString strSourNodeVal;

	while(oPugiSourChild != NULL)
	{
		strSourNodeVal = oPugiSourChild.name();

		if (strSourNodeVal != _T("Private"))
		{
			oPugiCompChild = oPugiCompareNode.find_child_by_attribute(oPugiSourChild.name() ,oPugiSourChild.special_attribute() ,oPugiSourChild.first_attribute() ,oPugiSourChild.first_attribute().next_attribute()
				,oPugiSourChild.first_attribute().next_attribute().next_attribute(),oPugiSourChild.first_attribute().next_attribute().next_attribute().next_attribute()
				,oPugiSourChild.first_attribute().next_attribute().next_attribute().next_attribute().next_attribute(),oPugiSourChild.first_attribute().next_attribute().next_attribute().next_attribute().next_attribute().next_attribute()
				,oPugiSourChild.first_attribute().next_attribute().next_attribute().next_attribute().next_attribute().next_attribute().next_attribute() ,oPugiSourChild.attribute_number());

			if (CompPugiNodeAttr(oPugiSourChild , oPugiCompChild))
			{
				nCtrlID = CompareChildAndAttr(oPugiSourChild ,oPugiCompChild );

				if (nCtrlID != 0)
					return nCtrlID;
			} 
			else
				return 6;
		}
		oPugiSourChild = oPugiSourChild.next_sibling();
	}

	return 0;
}

bool QSCLComparedTreeCtrl::CompPugiNodeAttr(pugi::xml_node oPugiSourChild ,pugi::xml_node oPugiCompChild)
{
	if (oPugiSourChild.attribute_number() != oPugiCompChild.attribute_number())
		return false;

	pugi::xml_attribute oPugiSourAttr ,oPugiCompareAttr;
	oPugiSourAttr = oPugiSourChild.first_attribute();
	CString strSourValue , strCompValue;

	while(oPugiSourAttr != NULL)
	{
		oPugiCompareAttr = oPugiCompChild.attribute(oPugiSourAttr.name());

		if (oPugiCompareAttr == NULL)
			return false;

		if (!pugi::strequal(oPugiSourAttr.value() ,oPugiCompareAttr.value()))
			return false;

		oPugiSourAttr = oPugiSourAttr.next_attribute();
	}

	return true;
}


void QSCLComparedTreeCtrl::GetAttrNameAndDescValue(pugi::xml_node oPugiNode,CString *strAttrVal)
{
	CString strName , strDesc;
	strName = oPugiNode.attribute(L"name").value();
	strDesc = oPugiNode.attribute(L"desc").value();

	if (strDesc.IsEmpty())
	{
		*strAttrVal = strName;
	} 
	else
	{
		*strAttrVal = strDesc;
		*strAttrVal += "-";
		*strAttrVal += strName;
	}
}


QExBaseTreeWidgetItem* QSCLComparedTreeCtrl::NewItem(QExBaseTreeWidgetItem *parent, CExBaseObject *pObj)
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


void QSCLComparedTreeCtrl::slot_TreeItemClicked(QTreeWidgetItem *pTreeWidgetItem, int column)
{
	QExBaseTreeWidgetItem *pItem = (QExBaseTreeWidgetItem*)pTreeWidgetItem;

	if (pItem->m_pItemData == NULL)
	{
		return;
	}

	QDeliverPugiNode* pDelivNode =(QDeliverPugiNode*)pItem->m_pItemData;


	emit sig_UpdateXmlComparedTree(pDelivNode);
}

void QSCLComparedTreeCtrl::InsertImage(QExBaseTreeWidgetItem *pItem,long nCtrlID)
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

void QSCLComparedTreeCtrl::GetPugixmlAttrDesc(pugi::xml_node &oPugiNode, CString &strNodeAllDesc)
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
			strNodeAllDesc += strText;
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

void QSCLComparedTreeCtrl::ExportReport()
{
	m_DiffListMap.clear();
	pugi::xml_node oPugixmlSourceRoot = GetPugixmlSourceRoot();
	pugi::xml_node oPugixmlCompareRoot = GetPugixmlCompareRoot();
	pugi::xml_node oPugiSourceChild = oPugixmlSourceRoot.first_child();
	CString strName;
	CString strSourNodeVal,strCompareNodeVal;
	long nCtrlID = 0;
	long nItemIndex= 0;
	CString strIndex,strMSG;

	while(oPugiSourceChild != NULL)
	{
		strName = oPugiSourceChild.name();
		if (strName != _T("Private") )
		{
			strSourNodeVal = oPugiSourceChild.name();
			pugi::xml_node oPugiCompareNode = oPugixmlCompareRoot.child(strSourNodeVal.AllocSysString());
			QDeliverPugiNode *pDeliverNode = NULL;

			if (strSourNodeVal == "Header")
			{
				if (oPugiCompareNode == NULL)
				{
					nCtrlID = 4;
				}
				else
				{
					nCtrlID = CompareHearderPort(oPugiSourceChild ,oPugiCompareNode);
				}

				pDeliverNode = new QDeliverPugiNode();
				AddNewChild(pDeliverNode);
				pDeliverNode->m_pSourNode = oPugiSourceChild.internal_object();
				pDeliverNode->m_pCompNode = oPugiCompareNode.internal_object();
				pDeliverNode->m_nType = nCtrlID;
				CompareNodeContents(pDeliverNode);
				strIndex.Format(_T("%06ld"), nItemIndex +1);
				strMSG = strIndex + _T(".") + _T("头文件");
				m_DiffListMap.insert(strMSG, m_DiffList);
				nItemIndex ++ ;

				if ((nCtrlID == 4)&&(oPugiCompareNode != NULL))
				{
					pDeliverNode = new QDeliverPugiNode();
					AddNewChild(pDeliverNode);
					pDeliverNode->m_pSourNode = oPugiSourceChild.internal_object();
					pDeliverNode->m_pCompNode = oPugiCompareNode.internal_object();
					pDeliverNode->m_nType = 2;
				}
				CompareNodeContents(pDeliverNode);
				strIndex.Format(_T("%06ld"), nItemIndex +1);
				strMSG = strIndex + _T(".") + _T("头文件");
				m_DiffListMap.insert(strMSG, m_DiffList);
				nItemIndex ++ ;
			}
			else if (strSourNodeVal == "Substation")
			{
				if (oPugiCompareNode == NULL)
				{
					nCtrlID = 4;
				}
				else
				{
					nCtrlID = CompareSubstationPort(oPugiSourceChild ,oPugiCompareNode );
				}
				pDeliverNode = new QDeliverPugiNode();
				AddNewChild(pDeliverNode);
				pDeliverNode->m_pSourNode = oPugiSourceChild.internal_object();
				pDeliverNode->m_pCompNode = oPugiCompareNode.internal_object();
				pDeliverNode->m_nType = nCtrlID;
				CompareNodeContents(pDeliverNode);
				strIndex.Format(_T("%06ld"), nItemIndex +1);
				strMSG = strIndex + _T(".") + _T("变电站");
				m_DiffListMap.insert(strMSG, m_DiffList);
				nItemIndex ++ ;

				if ((nCtrlID == 4)&&(oPugiCompareNode != NULL))
				{
					pDeliverNode = new QDeliverPugiNode();
					AddNewChild(pDeliverNode);
					pDeliverNode->m_pSourNode = oPugiSourceChild.internal_object();
					pDeliverNode->m_pCompNode = oPugiCompareNode.internal_object();
					pDeliverNode->m_nType = 2;
					CompareNodeContents(pDeliverNode);
					strIndex.Format(_T("%06ld"), nItemIndex +1);
					strMSG = strIndex + _T(".") + _T("变电站");
					m_DiffListMap.insert(strMSG, m_DiffList);
					nItemIndex ++ ;
				}
			}
			else if (strSourNodeVal == "Communication")
			{
				CString nodeValue;
				nodeValue = "SubNetwork-";
				pugi::xml_node oPugiSourChild = oPugiSourceChild.first_child();
				pugi::xml_node oPugiCompChild;
				CString strNode;
				while(oPugiSourChild != NULL)
				{
					strNode = oPugiSourChild.name();

					if( strNode != _T("SubNetwork"))
					{
						oPugiSourChild = oPugiSourChild.next_sibling();
						continue;
					}
					GetAttrNameAndDescValue(oPugiSourChild, &strSourNodeVal);
					strSourNodeVal = nodeValue + strSourNodeVal;
					oPugiCompChild = oPugiCompareNode.find_child_by_attribute(strNode.AllocSysString() ,oPugiSourChild.attribute(L"name").name() , oPugiSourChild.attribute(L"name").value());
					if (oPugiCompChild == NULL)
						nCtrlID = 4;
					else
						nCtrlID = CompareCommonPort(oPugiSourChild ,oPugiCompChild );
					pDeliverNode = new QDeliverPugiNode();
					AddNewChild(pDeliverNode);
					pDeliverNode->m_pSourNode = oPugiSourChild.internal_object();
					pDeliverNode->m_pCompNode = oPugiCompChild.internal_object();
					pDeliverNode->m_nType = nCtrlID;
					CompareNodeContents(pDeliverNode);
					strIndex.Format(_T("%06ld"), nItemIndex +1);
					strSourNodeVal = _T("通讯网络-") + strSourNodeVal;
					strMSG = strIndex + _T(".") + strSourNodeVal;
					m_DiffListMap.insert(strMSG, m_DiffList);
					nItemIndex ++ ;
					oPugiSourChild = oPugiSourChild.next_sibling();
				}

				oPugiCompChild = oPugiCompareNode.first_child();

				while(oPugiCompChild != NULL)
				{
					strNode = oPugiCompChild.name();
					if( strNode != _T("SubNetwork"))
					{
						oPugiCompChild = oPugiCompChild.next_sibling();
						continue;
					}
					GetAttrNameAndDescValue(oPugiCompChild, &strSourNodeVal);
					strSourNodeVal = nodeValue + strSourNodeVal;
					oPugiSourChild = oPugiSourChild.find_child_by_attribute(strNode.AllocSysString() ,oPugiCompChild.attribute(L"name").name() , oPugiCompChild.attribute(L"name").value());

					if (oPugiSourChild == NULL)
					{
						nCtrlID = 2;
						pDeliverNode = new QDeliverPugiNode();
						AddNewChild(pDeliverNode);
						pDeliverNode->m_pSourNode = oPugiSourChild.internal_object();
						pDeliverNode->m_pCompNode = oPugiCompChild.internal_object();
						pDeliverNode->m_nType = nCtrlID;
						CompareNodeContents(pDeliverNode);
						strIndex.Format(_T("%06ld"), nItemIndex +1);
						strSourNodeVal = _T("通讯网络-") + strSourNodeVal;
						strMSG = strIndex + _T(".") + strSourNodeVal;
						m_DiffListMap.insert(strMSG, m_DiffList);
						nItemIndex ++ ;
					}
					oPugiCompChild = oPugiCompChild.next_sibling();
				}
			}
			else if (strSourNodeVal == "IED")
			{
				oPugiCompareNode = oPugixmlCompareRoot.find_child_by_attribute(strSourNodeVal.AllocSysString() ,oPugiSourceChild.attribute(L"name").name() , oPugiSourceChild.attribute(L"name").value());
				if (oPugiCompareNode == NULL)
				{
					nCtrlID = 4;
				}
				else
				{
					nCtrlID = CompareCommonPort(oPugiSourceChild ,oPugiCompareNode);
				}

				GetAttrNameAndDescValue(oPugiSourceChild, &strSourNodeVal);
				pDeliverNode = new QDeliverPugiNode();
				AddNewChild(pDeliverNode);
				pDeliverNode->m_pSourNode = oPugiSourceChild.internal_object();
				pDeliverNode->m_pCompNode = oPugiCompareNode.internal_object();
				pDeliverNode->m_nType = nCtrlID;
				CompareNodeContents(pDeliverNode);
				strIndex.Format(_T("%06ld"), nItemIndex +1);
				strSourNodeVal = _T("IED列表-") + strSourNodeVal;
				strMSG = strIndex + _T(".") + strSourNodeVal;
				m_DiffListMap.insert(strMSG, m_DiffList);
				nItemIndex ++ ;
			}
			else if (strSourNodeVal == "DataTypeTemplates")
			{
				pugi::xml_node oPugiSourChild = oPugiSourceChild.child(L"LNodeType");
				pugi::xml_node oPugiCompChild = oPugiCompareNode.child(L"LNodeType");
				nCtrlID = CompareDataTypeTempPort(_T("LNodeType") ,oPugiSourChild ,oPugiCompChild);
				pDeliverNode = new QDeliverPugiNode();
				AddNewChild(pDeliverNode);
				pDeliverNode->m_pSourNode = oPugiSourChild.internal_object();
				pDeliverNode->m_pCompNode = oPugiCompChild.internal_object();
				pDeliverNode->m_nType = nCtrlID;
				CompareNodeContents(pDeliverNode);
				strIndex.Format(_T("%06ld"), nItemIndex +1);
				strSourNodeVal += _T("-LNodeType");
				strMSG = strIndex + _T(".") + _T("数据类型模板库-LNodeType");
				m_DiffListMap.insert(strMSG, m_DiffList);
				nItemIndex ++ ;

				oPugiSourChild = oPugiSourceChild.child(L"DOType");
				oPugiCompChild = oPugiCompareNode.child(L"DOType");
				nCtrlID = CompareDataTypeTempPort(_T("DOType") ,oPugiSourChild ,oPugiCompChild);
				pDeliverNode = new QDeliverPugiNode();
				AddNewChild(pDeliverNode);
				pDeliverNode->m_pSourNode = oPugiSourChild.internal_object();
				pDeliverNode->m_pCompNode = oPugiCompChild.internal_object();
				pDeliverNode->m_nType = nCtrlID;
				CompareNodeContents(pDeliverNode);
				strIndex.Format(_T("%06ld"), nItemIndex +1);
				strSourNodeVal += _T("-DOType");
				strMSG = strIndex + _T(".") + _T("数据类型模板库-DOType");
				m_DiffListMap.insert(strMSG, m_DiffList);
				nItemIndex ++ ;

				oPugiSourChild = oPugiSourceChild.child(L"DAType");
				oPugiCompChild = oPugiCompareNode.child(L"DAType");
				nCtrlID = CompareDataTypeTempPort(_T("-DAType") ,oPugiSourChild ,oPugiCompChild);
				pDeliverNode = new QDeliverPugiNode();
				AddNewChild(pDeliverNode);
				pDeliverNode->m_pSourNode = oPugiSourChild.internal_object();
				pDeliverNode->m_pCompNode = oPugiCompChild.internal_object();
				pDeliverNode->m_nType = nCtrlID;
				CompareNodeContents(pDeliverNode);
				strIndex.Format(_T("%06ld"), nItemIndex +1);
				strSourNodeVal += _T("-DAType");
				strMSG = strIndex + _T(".") + _T("数据类型模板库-DAType");
				m_DiffListMap.insert(strMSG, m_DiffList);
				nItemIndex ++ ;

				oPugiSourChild = oPugiSourceChild.child(L"EnumType");
				oPugiCompChild = oPugiCompareNode.child(L"EnumType");
				nCtrlID = CompareDataTypeTempPort(_T("EnumType") ,oPugiSourChild ,oPugiCompChild);
				pDeliverNode = new QDeliverPugiNode();
				AddNewChild(pDeliverNode);
				pDeliverNode->m_pSourNode = oPugiSourChild.internal_object();
				pDeliverNode->m_pCompNode = oPugiCompChild.internal_object();
				pDeliverNode->m_nType = nCtrlID;
				CompareNodeContents(pDeliverNode);
				strIndex.Format(_T("%06ld"), nItemIndex +1);
				strSourNodeVal += _T("-EnumType");
				strMSG = strIndex + _T(".") + _T("数据类型模板库-EnumType");
				m_DiffListMap.insert(strMSG, m_DiffList);
				nItemIndex ++ ;
			}
			else
			{
				pDeliverNode = new QDeliverPugiNode();
				AddNewChild(pDeliverNode);
				pDeliverNode->m_pSourNode = oPugiSourceChild.internal_object();
				pDeliverNode->m_pCompNode = oPugiCompareNode.internal_object();
				pDeliverNode->m_nType = 0;
				CompareNodeContents(pDeliverNode);
				strIndex.Format(_T("%06ld"), nItemIndex +1);
				strMSG = strIndex + _T(".") + strSourNodeVal;
				m_DiffListMap.insert(strMSG, m_DiffList);
				nItemIndex ++ ;
			}
		}
		oPugiSourceChild = oPugiSourceChild.next_sibling();		
	}

	pugi::xml_node oPugiCompChild = oPugixmlCompareRoot.child(L"IED");
	QDeliverPugiNode *pDeliverNode = NULL;
	while(oPugiCompChild != NULL)
	{
		if (oPugixmlSourceRoot.find_child_by_attribute(L"IED" ,L"name" ,oPugiCompChild.attribute(L"name").value()) == NULL)
		{
			GetAttrNameAndDescValue(oPugiCompChild, &strName);

			pDeliverNode = new QDeliverPugiNode();
			AddNewChild(pDeliverNode);
			pDeliverNode->m_pSourNode = NULL;
			pDeliverNode->m_pCompNode = oPugiCompChild.internal_object();
			pDeliverNode->m_nType = 2;
			CompareNodeContents(pDeliverNode);
			strIndex.Format(_T("%06ld"), nItemIndex +1);
			strName = _T("IED列表-")+strName;
			strMSG = strIndex + _T(".") + strName;
			m_DiffListMap.insert(strMSG, m_DiffList);
			nItemIndex ++ ;
		}
		oPugiCompChild = oPugiCompChild.next_sibling(L"IED");
	}
}


void QSCLComparedTreeCtrl::CompareNodeContents(QDeliverPugiNode* pDelivNode)
{
	ASSERT(pDelivNode != NULL);
	m_nDifNums = 0;
	m_DiffList.clear();
	pugi::xml_node oSourNode(pDelivNode->m_pSourNode);
	pugi::xml_node oCompNode(pDelivNode->m_pCompNode);
	pugi::xml_node oPugiNode;
	pugi::xml_node oPugiCompNode;
	CString strText;
	strText = oSourNode.name();
	CString strNodeName;
	QDeliverPugiNode *pDeliverNodeNew = NULL;
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

			CompareNode(pDeliverNodeNew);
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
					CompareNode(pDeliverNodeNew);
				}
				oPugiCompNode = oPugiCompNode.next_sibling(strText.AllocSysString());
			}
		}
	}
	else
	{
		CompareNode(pDelivNode);
	}
}

void QSCLComparedTreeCtrl::CompareNode(QDeliverPugiNode *pDeliverNode)
{
	ASSERT(pDeliverNode != NULL);
	pugi::xml_node oPugiSourNode(pDeliverNode->m_pSourNode);
	pugi::xml_node oPugiCompNode(pDeliverNode->m_pCompNode);
	pugi::xml_node oPugiNode;
	pugi::xml_node oPugiChild;
	pugi::xml_node oPugiCompChild;
	long nCtrlID = pDeliverNode->m_nType;

	if (nCtrlID == 2)
	{
		oPugiNode = oPugiCompNode;
	} 
	else
	{
		oPugiNode = oPugiSourNode;
	}

	if (oPugiNode.type() == 3)
	{
		return;
	}

	CString strNodeAllDesc;
	CString strMSG ,strDifNums;

	if (nCtrlID == 6)
	{
		if (oPugiSourNode.compare_all_attribue(oPugiCompNode))
		{
			GetPugixmlAttrDesc(oPugiSourNode ,strNodeAllDesc);
		} 
		else
		{
			CString strModifyDesc;
			GetPugixmlAttrDesc(oPugiSourNode ,strModifyDesc);
			strModifyDesc += _T("  <----->  ");
			GetPugixmlAttrDesc(oPugiCompNode ,strNodeAllDesc);
			strModifyDesc += strNodeAllDesc;

			if (m_nDifNums == 999)
			{
				m_nDifNums++;
				strMSG  = _T("比对差异超过1000,忽略显示");
				m_DiffList.append(strMSG);
			}

			if (m_nDifNums<1000)
			{
				m_nDifNums++;
				strDifNums.Format(_T("%ld"),m_nDifNums);
				strMSG  = _T("比对差异")+ strDifNums +_T("(修改):") + strModifyDesc;
				m_DiffList.append(strMSG);
			}
		}
	} 
	else
	{
		GetPugixmlAttrDesc(oPugiNode ,strNodeAllDesc);

		if (m_nDifNums == 999)
		{
			m_nDifNums++;
			strMSG  = _T("比对差异超过1000,忽略显示");
			m_DiffList.append(strMSG);
		}

		int nTmp1 = -1,nTmp2 = -1;

		if ((nTmp1 != 2)&&(nTmp1 != 4))
		{
			if ((nCtrlID == 2)&&(m_nDifNums<1000))
			{
				m_nDifNums++;
				strDifNums.Format(_T("%ld"),m_nDifNums);
				strMSG  = _T("比对差异")+ strDifNums +_T("(删除):")+strNodeAllDesc;
				m_DiffList.append(strMSG);
			} 
			else if ((nCtrlID == 4)&&(m_nDifNums<1000))
			{
				m_nDifNums++;	
				strDifNums.Format(_T("%ld"),m_nDifNums);
				strMSG  = _T("比对差异")+ strDifNums +_T("(新增):")+strNodeAllDesc;
				m_DiffList.append(strMSG);
			}
		}
	}

	CString strChild;
	QDeliverPugiNode *pDeliverNodeNew = NULL;
	oPugiChild = oPugiNode.first_child();

	while(oPugiChild != NULL)
	{
		strChild = oPugiChild.name();
		if ((strChild != _T("Private"))&&(oPugiChild.type() != 5))
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

			CompareNode(pDeliverNodeNew);
		}
		oPugiChild = oPugiChild.next_sibling();
	}

	if (nCtrlID == 6)
	{
		oPugiCompChild = oPugiCompNode.first_child();

		while(oPugiCompChild != NULL)
		{
			strChild = oPugiCompChild.name();
			if ((strChild != _T("Private"))&&(oPugiCompChild.type() != 5))
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
					CompareNode(pDeliverNodeNew);
				}
			}
			oPugiCompChild = oPugiCompChild.next_sibling();
		}
	}
}
