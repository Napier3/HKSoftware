#include "stdafx.h"
#include "GbWzdCmdInitGbByStxmlFile.h"

#include "InitGbByStxml\GbWzdCmdEditGbItem.h"
#include "InitGbByStxml\GbWzdCmdEditGbtDataMap.h"
#include "InitGbByStxml\GbWzdCmdSelectRootItems.h"
#include "GuideBookWizard.h"

#define GBWZDSTXML_STATE_SELECT_ITEMS    0
#define GBWZDSTXML_STATE_EDIT_DATAMAP    1
#define GBWZDSTXML_STATE_EDIT_COMMCMD    2

CGbWzdCmdInitGbByStxmlFile::CGbWzdCmdInitGbByStxmlFile()
{
	m_pRootItems = NULL;
	m_pReadStxmlTool = NULL;//new CGbInsertStxmlFileTool();
	//AddNewChild(m_pReadStxmlTool);
	m_pGbInsertStxmlTool = NULL;
	m_pWzdAutoTemplateRef = NULL;
}


CGbWzdCmdInitGbByStxmlFile::~CGbWzdCmdInitGbByStxmlFile()
{
	m_pReadStxmlTool = NULL;
	DeleteAll();

	if (m_pGbInsertStxmlTool != NULL)
	{
		delete m_pGbInsertStxmlTool;
		m_pGbInsertStxmlTool = NULL;
	}
}



long CGbWzdCmdInitGbByStxmlFile::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

long CGbWzdCmdInitGbByStxmlFile::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbWzdCmdList::XmlReadOwn(oNode,pXmlRWKeys);
	CGbWzdToolXmlRWKeys *pGbXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pGbXmlKeys->m_strRootItemsNameKey,oNode,m_strRootItemsNamePath);
	xml_GetAttibuteValue(pGbXmlKeys->m_strRootItemsIDKey,oNode,m_strRootItemsIDPath);

	return 0;
}

long CGbWzdCmdInitGbByStxmlFile::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbWzdCmd::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	CGbWzdToolXmlRWKeys *pGbXmlKeys = (CGbWzdToolXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pGbXmlKeys->m_strRootItemsNameKey,oElement,m_strRootItemsNamePath);
	xml_SetAttributeValue(pGbXmlKeys->m_strRootItemsIDKey,oElement,m_strRootItemsIDPath);

	return 0;
}

BSTR CGbWzdCmdInitGbByStxmlFile::GetXmlElementKey()
{
	return CGbWzdToolXmlRWKeys::CGbWzdCmdInitGbByStxmlFileKey();
}


BOOL CGbWzdCmdInitGbByStxmlFile::IsEqual(CBaseObject* pObj)
{
	return TRUE;
}

BOOL CGbWzdCmdInitGbByStxmlFile::CopyOwn(CBaseObject* pDesObj)
{
	return TRUE;
}

CBaseObject* CGbWzdCmdInitGbByStxmlFile::Clone()
{
	CGbWzdCmdInitGbByStxmlFile *pNew = new CGbWzdCmdInitGbByStxmlFile();
	Copy(pNew);
	return pNew;
}

CExBaseObject* CGbWzdCmdInitGbByStxmlFile::CreateNewChild(long nClassID)
{
	return NULL;
}

CExBaseObject* CGbWzdCmdInitGbByStxmlFile::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbWzdToolXmlRWKeys::CGbInsertStxmlFileToolKey())
	{
		m_pReadStxmlTool = new CGbInsertStxmlFileTool();
		return m_pReadStxmlTool;
	}

	return NULL;
}

long CGbWzdCmdInitGbByStxmlFile::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
// 	POS pos = GetHeadPosition();
// 	CExBaseObject *pObj = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pObj = GetNext(pos);
// 		pObj->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
// 	}

	GetGbInsertStxmlFileTool();

	if (m_pGbInsertStxmlTool != NULL)
	{
		m_pGbInsertStxmlTool->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
	}

	return 0;
}

void CGbWzdCmdInitGbByStxmlFile::InitAfterRead()
{
	if (m_pReadStxmlTool != NULL)
	{

	}
}

void CGbWzdCmdInitGbByStxmlFile::SelectRootItems()
{
	CGuideBook *pGuideBook = GetGuideBook();
	ASSERT (pGuideBook != NULL);
	CDevice *pDevice = pGuideBook->GetDevice();
	ASSERT (pDevice != NULL);

	m_pRootItems = pDevice->CreateItemsDirectories(m_strRootItemsNamePath, m_strRootItemsIDPath);

	if (m_pRootItems->m_dwItemData == 0)
	{
		CTreeCtrl *pTree = GetGuideBookEditTreeCtrl();
		pTree->PostMessage(WM_USER+1057, (WPARAM)m_pRootItems, (LPARAM)m_pRootItems);
	}
}

BOOL CGbWzdCmdInitGbByStxmlFile::OnGbNodeSelChange(CExBaseObject *pGbNode)
{
	 CGbWzdCmd *pCurr = GetCurrGbWzdCmd();

	 if (pCurr == NULL)
	 {
		 return FALSE;
	 }

	 if (pCurr->GetClassID() == GBWZDCLASSID_STXML_SELROOT)
	 {
		 SetRootItems((CExBaseList*)pGbNode);
		 return TRUE;
	 }
	 else
	 {
		 return FALSE;
	 }
}

BOOL CGbWzdCmdInitGbByStxmlFile::SetRootItems(CExBaseList *pRootItems)
{
	ASSERT (pRootItems != NULL);
	m_pRootItems = NULL;

	if (pRootItems == NULL)
	{
		return FALSE;
	}

	UINT nClassID = pRootItems->GetClassID();

	if ( nClassID == GBCLASSID_DEVICE)
	{
		m_strRootItemsNamePath = _T("");
		m_strRootItemsIDPath = _T("");
		m_pRootItems = pRootItems;
		return TRUE;
	}

	if (nClassID == GBCLASSID_ITEMS)
	{
		if (pRootItems->GetAncestor(GBCLASSID_DEVICE) == NULL)
		{
			return FALSE;
		}
		else
		{
			m_pRootItems = pRootItems;

			//此处的路径只考虑一个设备，不考虑多个设备
			m_strRootItemsNamePath = m_pRootItems->GetNamePathEx(GBCLASSID_DEVICE, FALSE);
			m_strRootItemsIDPath = m_pRootItems->GetIDPathEx(GBCLASSID_DEVICE, FALSE);

			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
}

void CGbWzdCmdInitGbByStxmlFile::InitCmd()
{
	CGuideBookWizard *pWzd = (CGuideBookWizard*)GetAncestor(GBWZDCLASSID_GBWIZARD);
// 	m_oGbInsertStxmlTool.Init(GetGuideBook(), GbWzd_GetXKeyDB(), pWzd->GetCWordRptEdit());
// 	m_oGbInsertStxmlTool.Init(m_strID);
	//m_pReadStxmlTool->Init(GetGuideBook(), GbWzd_GetXKeyDB(), pWzd->GetCWordRptEdit());
	//m_pReadStxmlTool->Init(m_strID);
	GetGbInsertStxmlFileTool();

	//选择根节点
	CGbWzdCmdSelectRootItems *pSelRoot = new CGbWzdCmdSelectRootItems();
	m_listCmd.AddNewChild(pSelRoot);

	//编辑映射关系
	CGbWzdCmdEditGbtDataMap *pEditMap = new CGbWzdCmdEditGbtDataMap();
	m_listCmd.AddNewChild(pEditMap);

	//编辑测试项目
// 	ASSERT (m_pRootItems != NULL);
// 
// 	if (m_pRootItems != NULL)
// 	{
// 		InsertEditItemsGbCmd(m_pRootItems);
// 	}
//
// 	CGuideBook *pGbStxml = m_oGbInsertStxmlTool.m_pGbStxml;
// 	ASSERT (pGbStxml != NULL);
// 	CDevice *pGbDevice = pGbStxml->GetDevice();
// 	ASSERT (pGbDevice != NULL);
// 
// 	if (pGbDevice == NULL)
// 	{
// 		return;
// 	}
// 
// 	POS pos = pGbDevice->GetHeadPosition();
// 	CExBaseObject *pGbObj = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pGbObj = pGbDevice->GetNext(pos);
// 		
// 		if (IsNeedEditItems(pGbObj))
// 		{
// 			InsertEditItemsGbCmd((CExBaseList*)pGbObj);
// 		}
// 		
// 		if (pGbObj->GetClassID() != GBCLASSID_ITEMS)
// 		{
// 			
// 		}
// 	}
}

BOOL CGbWzdCmdInitGbByStxmlFile::IsNeedEditItems(CExBaseObject *pItem)
{
	if (pItem->GetClassID() != GBCLASSID_ITEMS)
	{
		return FALSE;
	}

	if (pItem->m_strID == GBID_BeforeTest_ || pItem->m_strID == GBID_AfterTest_)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CGbWzdCmdInitGbByStxmlFile::IsNeedEditItem(CExBaseObject *pItem)
{
	if (pItem->GetClassID() == GBCLASSID_COMMCMD)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CGbWzdCmdInitGbByStxmlFile::InsertEditItemsGbCmd(CExBaseList *pList)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	CGbWzdCmdEditGbItem *pNew = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pList->GetNext(pos);
		nClassID = p->GetClassID();

		if (p->GetClassID() == GBCLASSID_ITEMS)
		{
			InsertEditItemsGbCmd((CExBaseList*)p);
		}

		if (IsNeedEditItem(p) && IsNeedEditItems(pList))
		{
			if (nClassID == GBCLASSID_COMMCMD)
			{
				if (((CCommCmd*)p)->m_bWzdHasInitDataset)
				{
					continue;
				}
			}

			pNew = new CGbWzdCmdEditGbItem();
			pNew->m_strName = p->GetNamePathEx(GBCLASSID_DEVICE, FALSE);
			pNew->m_strID = p->GetIDPathEx(GBCLASSID_DEVICE);
			pNew->m_pGbItem = p;
			m_listCmd.AddNewChild(pNew);
		}
	}
}

void CGbWzdCmdInitGbByStxmlFile::InitGbItemEditCmds()
{
// 	if (m_pRootItems == NULL)
// 	{
// 		CGuideBook *pGbStxml = m_oGbInsertStxmlTool.m_pGbStxml;
// 		ASSERT (pGbStxml != NULL);
// 		CDevice *pGbDevice = pGbStxml->GetDevice();
// 		ASSERT (pGbDevice != NULL);
// 
// 		if (pGbDevice == NULL)
// 		{
// 			return;
// 		}
// 
// 		m_pRootItems = pGbDevice;
// 	}

	//InsertEditItemsGbCmd(&m_oGbInsertStxmlTool.m_oListNewItems);
	InsertEditItemsGbCmd(m_pGbInsertStxmlTool);

	//报告模板映射关系插入

}

BOOL CGbWzdCmdInitGbByStxmlFile::Execute(DWORD dwExecMode)
{
	if (m_nCmdExecState == GBWZDCMD_STATE_NORMAL)
	{
		InitCmd();
		ResetCmdList();
		CGbWzdCmd::Execute(dwExecMode);
		return CGbWzdCmdList::ExecCurrGbWzdCmd(dwExecMode);
	}

	return CGbWzdCmdList::Execute(dwExecMode);
}


void CGbWzdCmdInitGbByStxmlFile::GetCmdInfor(CString &strText)
{
	CGbWzdCmd::GetCmdInfor(strText);
}

CGbInsertStxmlFileTool* CGbWzdCmdInitGbByStxmlFile::GetGbInsertStxmlFileTool()	
{	
	if (m_pGbInsertStxmlTool == NULL)
	{
		CGuideBookWizard *pWzd = (CGuideBookWizard*)GetAncestor(GBWZDCLASSID_GBWIZARD);
		m_pGbInsertStxmlTool = new CGbInsertStxmlFileTool();
		m_pGbInsertStxmlTool->SetParent(this);
		m_pGbInsertStxmlTool->Init(GetGuideBook(), GbWzd_GetXKeyDB(), pWzd->GetCWordRptEdit());
		m_pGbInsertStxmlTool->Init(m_strID);
		SelectRootItems();
		m_pGbInsertStxmlTool->SetParentItems(m_pRootItems);

		if (m_pReadStxmlTool != NULL)
		{
			m_pGbInsertStxmlTool->InitTool(m_pReadStxmlTool);
		}
	}

	return m_pGbInsertStxmlTool;
}


void CGbWzdCmdInitGbByStxmlFile::InitGbInsertStxmlFileToolOwn()
{
	
}