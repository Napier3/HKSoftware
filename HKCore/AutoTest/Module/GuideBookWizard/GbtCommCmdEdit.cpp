#include "stdafx.h"
#include "GbtCommCmdEdit.h"
#include "GbInsertStxmlFileTool.h"

//////////////////////////////////////////////////////////////////////////
//CGbtCommCmdItemEditExpand
CGbtCommCmdItemEditExpand::CGbtCommCmdItemEditExpand()
{
	m_bSelect = FALSE;
}

CGbtCommCmdItemEditExpand::~CGbtCommCmdItemEditExpand()
{

}

CBaseObject* CGbtCommCmdItemEditExpand::Clone()
{
	CGbtCommCmdItemEditExpand *pNew = new CGbtCommCmdItemEditExpand();
	Copy(pNew);

	return pNew;
}

void CGbtCommCmdItemEditExpand::InitByCopy(CGbtCommCmdItemEditExpand *pSrc)
{
	pSrc->Copy(this);
}


//////////////////////////////////////////////////////////////////////////
//CGbtCommCmdItemEdit
CGbtCommCmdItemEdit::CGbtCommCmdItemEdit()
{
	
}

CGbtCommCmdItemEdit::~CGbtCommCmdItemEdit()
{

}

CBaseObject* CGbtCommCmdItemEdit::Clone()
{
	CGbtCommCmdItemEdit *pNew = new CGbtCommCmdItemEdit();
	Copy(pNew);
	return pNew;
}

BOOL CGbtCommCmdItemEdit::CopyOwn(CBaseObject* pDest)
{
	((CGbtCommCmdItemEdit*)pDest)->m_strCommCmdItemPath = m_strCommCmdItemPath;
	((CGbtCommCmdItemEdit*)pDest)->m_strDatasetPath = m_strDatasetPath;

	return CExBaseObject::CopyOwn(pDest);
}

long CGbtCommCmdItemEdit::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strItemPathKey, oNode, m_strCommCmdItemPath);
	xml_GetAttibuteValue(pXmlKeys->m_strDatasetPathKey, oNode, m_strDatasetPath);

	return 0;
}

long CGbtCommCmdItemEdit::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strItemPathKey, oElement, m_strCommCmdItemPath);
	xml_SetAttributeValue(pXmlKeys->m_strDatasetPathKey, oElement, m_strDatasetPath);

	return 0;
}


CExBaseObject* CGbtCommCmdItemEdit::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbWzdToolXmlRWKeys::CGbtCommCmdItemEditExpandKey())
	{
		return new CGbtCommCmdItemEditExpand();
	}

	return NULL;
}

void CGbtCommCmdItemEdit::InitByCopy(CGbtCommCmdItemEdit *pSrc)
{
	m_strDatasetPath = pSrc->m_strDatasetPath;
}

CGbtCommCmdItemEditExpand* CGbtCommCmdItemEdit::AddNewEdit(const CString &strDatasetPath)
{
	CGbtCommCmdItemEditExpand *pNew = new CGbtCommCmdItemEditExpand();
	pNew->m_strName = strDatasetPath;
	pNew->m_strID   = strDatasetPath;
	AddNewChild(pNew);

	return pNew;
}

void CGbtCommCmdItemEdit::EditCommCmdItem()
{
	CCommCmd *pCommCmd = (CCommCmd*)m_pCommCmdRef;
	pCommCmd->GetCmd()->m_strDatasetPath = m_strDatasetPath;
	
	POS pos = GetTailPosition();
	CGbtCommCmdItemEditExpand *pExpand = NULL;
	CExBaseList *pParent = (CExBaseList*)pCommCmd->GetParent();
	POS posCmd = pParent->Find(pCommCmd);
	CCommCmd *pNewCommCmd = NULL;

	while (pos != NULL)
	{
		pExpand = (CGbtCommCmdItemEditExpand *)GetPrev(pos);

		if (pExpand->m_bSelect)
		{
			pNewCommCmd = (CCommCmd*)pCommCmd->Clone();
			pNewCommCmd->GetCmd()->m_strDatasetPath = pExpand->m_strID;
			pParent->InitNameAndIDForPaste(pNewCommCmd);
			pParent->InsertAfter(posCmd, pNewCommCmd);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//CGbtCommCmdItemEditMngr
CGbtCommCmdItemEditMngr::CGbtCommCmdItemEditMngr()
{
	m_pGuideBookDest = NULL;
}

CGbtCommCmdItemEditMngr::~CGbtCommCmdItemEditMngr()
{
	m_listDataset.RemoveAll();
}

CBaseObject* CGbtCommCmdItemEditMngr::Clone()
{
	CGbtCommCmdItemEditMngr *pNew = new CGbtCommCmdItemEditMngr();
	Copy(pNew);
	return pNew;
}

BOOL CGbtCommCmdItemEditMngr::CopyOwn(CBaseObject* pDest)
{
	return CExBaseList::CopyOwn(pDest);
}

long CGbtCommCmdItemEditMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;


	return 0;
}

long CGbtCommCmdItemEditMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	return 0;
}

CExBaseObject* CGbtCommCmdItemEditMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbWzdToolXmlRWKeys::CGbtCommCmdItemEditKey())
	{
		return new CGbtCommCmdItemEdit();
	}

	return NULL;
}

void CGbtCommCmdItemEditMngr::InitGuideBookDest(CGuideBook *pGuideBook)
{
	m_pGuideBookDest = pGuideBook;
	CDevice *pDevice = pGuideBook->GetDevice();
	m_listDataset.RemoveAll();
	pDevice->GetDataSetList(_T(""), m_listDataset, DSID_ALL_DVM);
}

void CGbtCommCmdItemEditMngr::InitGbtCommCmdItemEdit(CGuideBook *pGuideBook)
{
	CDevice *pDevice = pGuideBook->GetDevice();
	CExBaseList oListItems;
	pDevice->SelectAllRootItem(oListItems);
	InitGbtCommCmdItemEdit(&oListItems);
	oListItems.RemoveAll();
}

void CGbtCommCmdItemEditMngr::InitGbtCommCmdItemEdit(CExBaseList *pList)
{
	UINT nClassID = 0;
	POS pos = pList->GetHeadPosition();
	CExBaseObject *pItem = NULL;

	while (pos != NULL)
	{
		pItem = (CExBaseObject *)pList->GetNext(pos);
		nClassID = pItem->GetClassID();

		if (nClassID == GBCLASSID_ITEMS)
		{
			InitGbtCommCmdItemEdit((CExBaseList*)pItem);
		}
		else if ( nClassID == GBCLASSID_COMMCMD )
		{
			CCommCmd *pCommCmd = (CCommCmd*)pItem;
			GbtCommCmdItemEdit(pCommCmd);
		}
	}
}

CGbtCommCmdItemEdit* CGbtCommCmdItemEditMngr::GbtCommCmdItemEdit(CCommCmd *pCommCmd)
{
	CGbCommCmdMms *pCmdMms = pCommCmd->GetGbCommCmd();

	if (!pCmdMms->IsWzdEditMode_Edit())
	{
		return NULL;
	}
// 	if (pCmdMms->m_strGbDataID == g_strDataSetIDKey[DSID_dsNone])
// 	{
// 		return NULL;
// 	}
// 
// 	if (pCmdMms->m_strGbDataID == g_strDataSetIDKey[DSID_dsReport])
// 	{
// 		return NULL;
// 	}
// 
// 	if (pCmdMms->m_strGbDataID != g_strDataSetIDKey[DSID_dsAll])
// 	{
// 		return NULL;
// 	}
	
	CGbtCommCmdItemEdit *pNew = new CGbtCommCmdItemEdit();
	pNew->m_strCommCmdItemPath = pCommCmd->GetIDPathEx(GBCLASSID_DEVICE, FALSE);
	pNew->m_pCommCmdRef = pCommCmd;
	pNew->m_strName = pCommCmd->GetNamePathEx(GBCLASSID_DEVICE, FALSE);
	pNew->m_strID = pCommCmd->m_strID;
	AddNewChild(pNew);

	CExBaseList listDataset;
	CDataSet *pFind = FindDatasetByDsID(pCmdMms->m_strGbDataID, listDataset);

	if (pFind != NULL)
	{
		pNew->m_strDatasetPath = pFind->GetIDPathEx(GBCLASSID_CPUS, FALSE);
	}

	if (listDataset.GetCount() > 1)
	{
		POS pos = listDataset.GetHeadPosition();
		CGbtCommCmdItemEdit *pExpand = NULL;
		pFind = (CDataSet *)listDataset.GetNext(pos);
		
		while (pos != NULL)
		{
			pFind = (CDataSet *)listDataset.GetNext(pos);
			pNew->AddNewEdit(pFind->GetIDPathEx(GBCLASSID_CPUS, FALSE));
		}
	}

	listDataset.RemoveAll();

	return pNew;
}

void CGbtCommCmdItemEditMngr::InitByCopy(CGbtCommCmdItemEditMngr *pSrc)
{
	POS pos = pSrc->GetHeadPosition();
	CGbtCommCmdItemEdit *pFindDest = NULL;
	CGbtCommCmdItemEdit *p = NULL;

	while (pos != NULL)
	{
		p = (CGbtCommCmdItemEdit*)pSrc->GetNext(pos);
		pFindDest = FindGbtCommCmdItemEdit(p->m_strCommCmdItemPath);

		if (pFindDest != NULL)
		{
			pFindDest->InitByCopy(p);
		}
	}
}

CGbtCommCmdItemEdit* CGbtCommCmdItemEditMngr::FindGbtCommCmdItemEdit(const CString &strPath)
{
	CGbtCommCmdItemEdit *p = NULL, *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CGbtCommCmdItemEdit *)GetNext(pos);

		if (p->m_strCommCmdItemPath == strPath)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CDataSet* CGbtCommCmdItemEditMngr::FindDatasetByDsID(const CString &strDsID, CExBaseList &listDataset)
{
	POS pos = m_listDataset.GetHeadPosition();
	CDataSet *p = NULL, *pFind = NULL;
	CString strKey = Gb_GetDataSetKey(strDsID);

	if (strKey.GetLength() <= 1)
	{
		return NULL;
	}

	while (pos != NULL)
	{
		p = (CDataSet *)m_listDataset.GetNext(pos);

		if (p->m_strID.Find(strKey) >= 0)
		{
			listDataset.AddTail(p);
		}
	}

	pFind = (CDataSet *)listDataset.GetHead();

	return pFind;
}


void CGbtCommCmdItemEditMngr::EditCommCmdItems()
{
	CGbtCommCmdItemEdit *p = NULL, *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CGbtCommCmdItemEdit *)GetNext(pos);
		p->EditCommCmdItem();
	}
}
