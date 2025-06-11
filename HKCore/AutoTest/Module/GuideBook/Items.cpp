#include "stdafx.h"
#include "Items.h"
#include "Safety.h"
#include "MacroTest.h"
#include "SysParaEdit.h"
#include "CommCmd.h"
#include "GuideBook.h"
#include "MacroCharItems.h"
#include "../XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const CString CItems::g_strExportID = _T("_$items$_");

CItems::CItems(void)
{
	m_strType = GBITEMS_NODETYPE_NONE;
	m_pItemsRsltExprScript = NULL;
	m_pUiParas = NULL;
	m_pCharParas = NULL;
	m_nTestTimes = 1;  //测试次数，填多少就是多少次

	m_nRptTitle = 0;
	m_nTitleLevel = 1;
}

CItems::~CItems(void)
{

}

BOOL CItems::IsTypeRootNode()
{
	return (m_strType == GBITEMS_NODETYPE_ROOTNODE);
}

//2022-11-04  lijuniqng  增加配置：重测所有子项目模式，此模式下只要一个子项目不合格，就重测所有子项目
//否则，只挑选不合格子项目以及相关的前驱和后驱项目
BOOL CItems::IsReTestAllChildMode()
{
	return FALSE;
}

void CItems::SetTypeRootNode(BOOL bRoot)
{
	if (bRoot)
	{
		m_strType = GBITEMS_NODETYPE_ROOTNODE;
	}
	else
	{
		m_strType = GBITEMS_NODETYPE_NONE;
	}
}

CItems* CItems::FindFirstRootTypeItem()
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	CItems *pFind = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != GBCLASSID_ITEMS)
		{
			continue;
		}

		CItems *pItems = (CItems *)pObj;

		if (pItems->IsTypeRootNode())
		{
			return pItems;
		}

		pFind = pItems->FindFirstRootTypeItem();

		if (pFind != NULL)
		{
			return pFind;
		}
	}

	return pFind;
}

long CItems::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemBase::XmlReadOwn(oNode,CGbXMLKeys::g_pGbXMLKeys);
	
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strTypeKey,oNode,m_strType);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strCharacteristicIDKey,oNode,m_strCharacteristicID);

	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strStxmlFileKey,oNode,m_strStxmlFile);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strWzdMapFileKey,oNode,m_strWzdMapFile);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strActLogicKey,oNode,m_strActLogic);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strRepeatTimes,oNode,m_nTestTimes);

	//shaolei 2023-6-20
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strRptTitleKey, oNode, m_nRptTitle);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strTitleLevelKey, oNode, m_nTitleLevel);

	return 0;
}

long CItems::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbItemBase::XmlWriteOwn(oXMLDoc,oElement,CGbXMLKeys::g_pGbXMLKeys);
	
	if (g_bGbExportXmlReportFile)
	{
		if (CGuideBookExportConfig::g_pGuideBookExportConfig->m_nExportItemAttrSimplify)
		{
			return 0;
		}
	}
	//保存dscxml时，需要记录该属性，以便PNS330上位机打开模板时，能够知道是哪个功能模块
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strStxmlFileKey,oElement,m_strStxmlFile);
	//保存dscxml时，需要记录该属性，以便PNS330上位机软件打开模板时，能够找到rootnode
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strTypeKey,oElement,m_strType);
	//保存dscxml时，需要记录该属性，以便PNS330上位机软件打开模板时，能够找到重复次数
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strRepeatTimes,oElement,m_nTestTimes);

	//shaolei 2023-6-20
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strRptTitleKey, oElement, m_nRptTitle);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strTitleLevelKey, oElement, m_nTitleLevel);

	if (g_bGbSaveGbStruDscFile)
	{
		return 0;
	}

	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strCharacteristicIDKey,oElement,m_strCharacteristicID);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strWzdMapFileKey,oElement,m_strWzdMapFile);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strActLogicKey,oElement,m_strActLogic);

	return 0;
}


//WriteXml
long CItems::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	if (g_bGbExportXmlReportFile)
	{
		CGuideBook *pGuideBook = (CGuideBook*)GetAncestor(GBCLASSID_GUIDEBOOK);

		if (pGuideBook->IsSaveRptToDB())
		{
			return XmlWriteChildren_FinalReport(oXMLDoc, oElement, pXmlRWKeys);
		}
	}
	
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);

		//2022-10-4  lijunqing
		if (g_bGbSaveGbStruDscFile)
		{
			if (pObj->GetClassID() == GBCLASSID_TESTMACROUIPARAS)
			{
				continue;
			}
		}

		pObj->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
	}

	return 0;
}


long CItems::XmlWriteChildren_FinalReport(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	CGbItemBase *pRefItem = NULL;
	CGbItemBase *pTempItemForDB = NULL;
	CString strTempFileName;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == GBCLASSID_MACROTEST || nClassID == GBCLASSID_COMMCMD)
		{//电气量测试功能和通讯命令
			pRefItem = (CGbItemBase*)pObj;
			strTempFileName = ats_GetBinaryTempFile(pRefItem);
			pTempItemForDB = pRefItem->OpenBinaryTempFileForRpt(strTempFileName);

			if (pTempItemForDB != NULL)
			{//创建成功的情况下
				pTempItemForDB->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
				delete pTempItemForDB;
			}
			else
			{
				pObj->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
			}
		}
		else if (Gb_IsItemNeedExportRpt(nClassID))
		{
			pObj->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
		}
	}

	return 0;
}


long CItems::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CGbItemBase::SerializeOwn(oBinaryBuffer);
	
	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strCharacteristicID);
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
		BinarySerializeCalLen(oBinaryBuffer, m_strStxmlFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strWzdMapFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strActLogic);
		BinarySerializeCalLen(oBinaryBuffer, m_nTestTimes);

		BinarySerializeCalLen(oBinaryBuffer, m_nRptTitle);
		BinarySerializeCalLen(oBinaryBuffer, m_nTitleLevel);
	}
	else if (oBinaryBuffer.IsReadMode())
	{
		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_6)
		{
			BinarySerializeRead(oBinaryBuffer, m_strCharacteristicID);
		}

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_14)
		{
			BinarySerializeRead(oBinaryBuffer, m_strType);
		}

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_16)
		{
			BinarySerializeRead(oBinaryBuffer, m_strStxmlFile);
			BinarySerializeRead(oBinaryBuffer, m_strWzdMapFile);
		}

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_41)
		{
			BinarySerializeRead(oBinaryBuffer, m_strActLogic);
		}

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_44)
		{
			BinarySerializeRead(oBinaryBuffer, m_nTestTimes);
		}

		if (oBinaryBuffer.m_dwVersion >= GBVERSION_1_45)
		{
			BinarySerializeRead(oBinaryBuffer, m_nRptTitle);
			BinarySerializeRead(oBinaryBuffer, m_nTitleLevel);
		}
	}
	else
	{
		BinarySerializeWrite(oBinaryBuffer, m_strCharacteristicID);
		BinarySerializeWrite(oBinaryBuffer, m_strType);
		BinarySerializeWrite(oBinaryBuffer, m_strStxmlFile);
		BinarySerializeWrite(oBinaryBuffer, m_strWzdMapFile);
		BinarySerializeWrite(oBinaryBuffer, m_strActLogic);
		BinarySerializeWrite(oBinaryBuffer, m_nTestTimes);

		BinarySerializeWrite(oBinaryBuffer, m_nRptTitle);
		BinarySerializeWrite(oBinaryBuffer, m_nTitleLevel);
	}

	return 0;
}

CExBaseObject* CItems::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *p = GbItems_CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);

	if (p != NULL)
	{
		return p;
	}

	return CGbItemBase::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
	//return GbItems_CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
// 	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strSafetyKey)
// 	{
// 		CSafety* pObject = new CSafety;
// 		return pObject;
// 	}
// 	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strMacroTestKey)
// 	{
// 		CMacroTest* pObject = new CMacroTest;
// 		return pObject;
// 	}
// 	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strCommCmdKey)
// 	{
// 		CCommCmd* pObject = new CCommCmd;
// 		return pObject;
// 	}
// 	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strSysParaEditKey)
// 	{
// 		CSysParaEdit* pObject = new CSysParaEdit;
// 		return pObject;
// 	}
// 	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strItemsKey)
// 	{
// 		CItems* pObject = new CItems;
// 		return pObject;
// 	}
// 
// 	return NULL;
}

CExBaseObject* CItems::CreateNewChild(long nClassID)
{
	CExBaseObject *p = GbItems_CreateNewChild(nClassID);

	if (p != NULL)
	{
		return p;
	}

	return CGbItemBase::CreateNewChild(nClassID);
	//return GbItems_CreateNewChild(nClassID);
// 	if (nClassID == GBCLASSID_SAFETY)
// 	{
// 		CSafety* pObject = new CSafety;
// 		return pObject;
// 	}
// 	else if (nClassID == GBCLASSID_MACROTEST)
// 	{
// 		CMacroTest* pObject = new CMacroTest;
// 		return pObject;
// 	}
// 	else if (nClassID == GBCLASSID_COMMCMD)
// 	{
// 		CCommCmd* pObject = new CCommCmd;
// 		return pObject;
// 	}
// 	else if (nClassID == GBCLASSID_SYSPARAEDIT)
// 	{
// 		CSysParaEdit* pObject = new CSysParaEdit;
// 		return pObject;
// 	}
// 	else if (nClassID == GBCLASSID_ITEMS)
// 	{
// 		CItems* pObject = new CItems;
// 		return pObject;
// 	}
// 	return NULL;
}

CBaseObject* CItems::Clone()
{
	CItems* pItems = new CItems();
	Copy(pItems);

	return pItems;
}

CBaseObject* CItems::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CItems *p = new CItems();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CItems::CanPaste(CExBaseObject *pObj)
{
	CExBaseObject *pJobGuide = (CExBaseObject*)GetAncestor(GBCLASSID_JOBGUIDE);
	UINT nClassID = pObj->GetClassID();

	if (pJobGuide != NULL)
	{
		if (nClassID == GBCLASSID_ITEMS)
		{
			if (GbItems_HasItem((CExBaseList*)pObj, GBCLASSID_MACROTEST))
			{
				return FALSE;
			}

			if (GbItems_HasItem((CExBaseList*)pObj, GBCLASSID_MACROCHARITEMS))
			{
				return FALSE;
			}

			if (GbItems_HasItem((CExBaseList*)pObj, GBCLASSID_COMMCMD))
			{
				return FALSE;
			}

			if (GbItems_HasItem((CExBaseList*)pObj, GBCLASSID_SYSPARAEDIT))
			{
				return FALSE;
			}

			return TRUE;
		}

		if (nClassID == GBCLASSID_SAFETY)
		{
			return TRUE;
		}

		return FALSE;
	}

	//2020-07-03  lijunqing  避免拷贝父对象到子对象中
	if (HasParent(pObj) || pObj == this)
	{
		return FALSE;
	}

	if (nClassID == GBCLASSID_SAFETY || nClassID == GBCLASSID_MACROTEST || nClassID == GBCLASSID_SYSPARAEDIT
		|| nClassID == GBCLASSID_COMMCMD || nClassID == GBCLASSID_ITEMS || nClassID == GBCLASSID_MACROCHARITEMS)
	{
		return TRUE;
	}

	return FALSE;
}


BOOL CItems::CopyOwn(CBaseObject* pDest)
{
	ASSERT(pDest != NULL);

	if (this == pDest)
	{
		return TRUE;
	}

	CGbItemBase::CopyOwn(pDest);
	CItems *pItem = (CItems*)pDest;

	pItem->m_strCharacteristicID = m_strCharacteristicID;
	pItem->m_strType = m_strType;
	pItem->m_strStxmlFile = m_strStxmlFile;
	pItem->m_strWzdMapFile = m_strWzdMapFile;
	pItem->m_strActLogic = m_strActLogic;
	pItem->m_nTestTimes = m_nTestTimes;

	pItem->m_nRptTitle = m_nRptTitle;
	pItem->m_nTitleLevel = m_nTitleLevel;
	return TRUE;
}


void CItems::InitAfterRead()
{
	CGbItemBase::InitAfterRead();

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == GBCLASSID_ITEMSRSLTEXPRSCRIPT)
		{
			m_pItemsRsltExprScript = (CItemsRsltExprScript *)p;
			break;
		}
		else if (p->GetClassID() == GBCLASSID_TESTMACROUIPARAS)
		{
			m_pUiParas = (CTestMacroUiParas*)p;
			break;
		}
		else if (p->GetClassID() == GBCLASSID_TESTMACROCHARPARAS)
		{
			m_pCharParas = (CTestMacroCharParas*)p;
			break;
		}
	}

	if (m_pItemsRsltExprScript != NULL)
	{
		BringToHead(m_pItemsRsltExprScript);
	}

	//GetItemsRsltExprScript();
}

CItemsRsltExprScript* CItems::GetItemsRsltExprScript(BOOL bCreate)
{
	if (m_pItemsRsltExprScript == NULL)
	{
		if (bCreate)
		{
			m_pItemsRsltExprScript = new CItemsRsltExprScript();
			AddNewChild(m_pItemsRsltExprScript);
		}
	}

	return m_pItemsRsltExprScript;
}

BOOL CItems::HasItemsRsltExprScript()
{
	if (m_pItemsRsltExprScript == NULL)
	{
		return FALSE;
	}


	if ((m_pItemsRsltExprScript->m_strID.GetLength() > 0) && (m_pItemsRsltExprScript->m_nIsRef == 1))
	{
		return TRUE;
	}

	if (m_pItemsRsltExprScript->m_strTestMacroID.GetLength() < 2)
	{
		return FALSE;
	}

	return TRUE;

	//无判断公式
	if (m_pItemsRsltExprScript->GetCount() == 0)
	{
		//数据集为空，表示是使用报文验证功能
		if (m_pItemsRsltExprScript->m_strDatasetID.GetLength() == 0)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return TRUE;
	}
}

long CItems::SelectChildrenItems(const CString &strPath, CGbItemBaseList &oListDest)
{
	CExBaseObject *p = NULL;
	CGbItemBase *pItem = NULL;
	POS pos = GetHeadPosition();

	if (strPath.GetLength() == 0)
	{
		while (pos != NULL)			//BaseList 遍历所有子节点 在所有子节点中查找
		{
			p = GetNext(pos);

			if (Gb_IsItemBaseClassID(p->GetClassID()))
			{
				oListDest.AddTail(pItem);
			}
		}
	}
	else
	{
		while (pos != NULL)			//BaseList 遍历所有子节点 在所有子节点中查找
		{
			pItem = (CGbItemBase*)GetNext(pos);
			ASSERT(pItem != NULL);

			if (Gb_IsItemBaseClassID(p->GetClassID()))
			{
				pItem->SelectItems(strPath, oListDest);
			}
		}
	}

	return 0;
}


//2020-02-03  lijq update items paras
// BOOL CItems::Update(CBaseObject* pDest)
// {
// 	
// 
// 	return TRUE;
// }
// 
// BOOL CItems::UpdateOwn(CBaseObject* pDest)
// {
// 	return TRUE;
// }


void CItems::UpdateItems(CItems *pDestItems, CGbItemBase *pNewItem)
{
	CGbItemBase *pDestItemsFind = (CGbItemBase*)pDestItems->FindByID(pNewItem->m_strID);

	if (pDestItemsFind == NULL)
	{
		pDestItemsFind = (CGbItemBase*)pDestItems->FindByName(pNewItem->m_strName);
	}

	if (pDestItemsFind == NULL)
	{
		return;
	}

	pNewItem->Update(pDestItemsFind);
}

void CItems::GetItemsCountByType(long &nTotalCount, long &nEligibleCount, long &nInlegibleCount)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	nTotalCount = nEligibleCount = nInlegibleCount = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != GBCLASSID_ITEMS)
		{
			continue;
		}

		CItems *pItems = (CItems *)pObj;

		if (!pItems->GetSelect())
		{
			continue;
		}

		if (pItems->IsTypeRootNode())
		{
			nTotalCount++;  //如果是功能类节点，则将整个CItems看作是一个测试项目，不进行子项目的统计；

			if (pItems->GetState() == TEST_STATE_ELIGIBLE || pItems->GetState() == TEST_STATE_ELIGIBLEEX)
			{
				nEligibleCount++;
			}
			else if (pItems->GetState() == TEST_STATE_INLEGIBLE)
			{
				nInlegibleCount++;
			}

			continue;
		}

		long nTotal = 0, nEligible = 0, nInegible = 0;
		pItems->GetItemsCountByType(nTotal, nEligible, nInegible);
		nTotalCount += nTotal;
		nEligibleCount += nEligible;
		nInlegibleCount += nInegible;
	}
}

//shaolei 2022-01-05
CTestMacroUiParas* CItems::CreateTestMacroUiParas()
{	
	if (m_pUiParas == NULL)
	{
		m_pUiParas = new CTestMacroUiParas;
		AddNewChild(m_pUiParas);
	}
	
	return m_pUiParas;
}

void CItems::SetTestMacroUiParas(CTestMacroUiParas *pUiParas)
{
	m_pUiParas = pUiParas;
}

//shaolei 2023-3-22
CTestMacroCharParas* CItems::CreateTestMacroCharParas()
{	
	if (m_pCharParas == NULL)
	{
		m_pCharParas = new CTestMacroCharParas;
		AddNewChild(m_pCharParas);
	}
	
	return m_pCharParas;
}

void CItems::SetTestMacroCharParas(CTestMacroCharParas *pCharParas)
{
	m_pCharParas = pCharParas;
}

BOOL CItems::UpdateChildren(CBaseObject* pDest)
{
	CItems *pDestItems = (CItems*)pDest;

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (Gb_IsGbItemClassID(nClassID))
		{
			UpdateItem(pDestItems, (CGbItemBase*)p);
		}
		else if (nClassID == GBCLASSID_ITEMS)
		{
			UpdateItems(pDestItems, (CGbItemBase*)p);
		}
// 		else if (nClassID == GBCLASSID_REPORTS)
// 		{
// 			((CExBaseList*)p)->AppendCloneEx(pDestItems->GetReports());
// 		}
		else
		{
		}
	}

	return TRUE;
}

//shaolei 20220607
void CItems::SetItemState(long nShow, long nEnable, long nSelect, BOOL bSetShow, BOOL bSetEnable, BOOL bSetSelect)
{
	CGbItemBase::SetItemState(nShow, nEnable, nSelect, bSetShow, bSetEnable, bSetSelect);

	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == GBCLASSID_COMMCMD)
		{
			CCommCmd* pCmd = (CCommCmd *)pObj;
			//此处是否应当考虑，如果设置成1，子项目是不是不需要设置？
			pCmd->SetItemState(nShow, nEnable, nSelect, bSetShow, bSetEnable, bSetSelect);
			continue;
		}

		if (nClassID == GBCLASSID_ITEMS)
		{
			CItems* pItems = (CItems *)pObj;
			//此处是否应当考虑，如果设置成1，子项目是不是不需要设置？
			pItems->SetItemState(nShow, nEnable, nSelect, bSetShow, bSetEnable, bSetSelect);
			continue;
		}

		if (nClassID == GBCLASSID_MACROTEST)
		{
			CMacroTest* pMacroTest = (CMacroTest *)pObj;
			//此处是否应当考虑，如果设置成1，子项目是不是不需要设置？
			pMacroTest->SetItemState(nShow, nEnable, nSelect, bSetShow, bSetEnable, bSetSelect);
			continue;
		}

		if (nClassID == GBCLASSID_SYSPARAEDIT)
		{
			CSysParaEdit* pSysParaEdit = (CSysParaEdit *)pObj;
			//此处是否应当考虑，如果设置成1，子项目是不是不需要设置？
			pSysParaEdit->SetItemState(nShow, nEnable, nSelect, bSetShow, bSetEnable, bSetSelect);
			continue;
		}

		if (nClassID == GBCLASSID_SAFETY)
		{
			CSafety* pSafety = (CSafety *)pObj;
			//此处是否应当考虑，如果设置成1，子项目是不是不需要设置？
			pSafety->SetItemState(nShow, nEnable, nSelect, bSetShow, bSetEnable, bSetSelect);
			continue;
		}

		if (nClassID == GBCLASSID_MACROCHARITEMS)
		{
			CMacroCharItems *pCharItems = (CMacroCharItems *)pObj;
			//此处是否应当考虑，如果设置成1，子项目是不是不需要设置？
			pCharItems->SetItemState(nShow, nEnable, nSelect, bSetShow, bSetEnable, bSetSelect);
			continue;
		}
	}
}

long CItems::GetItemTestCount()
{
	long nTestTimes = m_nTestTimes;
	CExBaseObject *pParent = (CExBaseObject *)GetParent();
	UINT nClassID = pParent->GetClassID();

	if (nClassID == GBCLASSID_ITEMS)
	{
		CItems *pItems = (CItems *)pParent;
		nTestTimes = nTestTimes * pItems->GetItemTestCount();
	}

	return nTestTimes;
}

CMacroTest* CItems::GetFirstMacroTest()
{
	CMacroTest *pFind = NULL;
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = (CExBaseObject *)GetNext(pos);

		if (pObj->GetClassID() == GBCLASSID_MACROTEST)
		{
			pFind = (CMacroTest *)pObj;
			break;
		}
	}

	return pFind;
}

//////////////////////////////////////////////////////////////////////////
CExBaseObject* GbItems_CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strSafetyKey)
	{
		CSafety* pObject = new CSafety;
		return pObject;
	}
	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strMacroTestKey)
	{
		CMacroTest* pObject = new CMacroTest;
		return pObject;
	}
	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strCommCmdKey)
	{
		CCommCmd* pObject = new CCommCmd;
		return pObject;
	}
	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strSysParaEditKey)
	{
		CSysParaEdit* pObject = new CSysParaEdit;
		return pObject;
	}
	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strItemsKey)
	{
		CItems* pObject = new CItems;
		return pObject;
	}
	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strCMacroCharItemsKey)
	{
		CMacroCharItems* pObject = new CMacroCharItems;
		return pObject;
	}
	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strRsltExprScriptKey)
	{
		CItemsRsltExprScript* pObject = new CItemsRsltExprScript;
		return pObject;
	}
	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strTestMacroUiParasKey)
	{
		CTestMacroUiParas* pObject = new CTestMacroUiParas;
		return pObject;
	}
	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strTestMacroCharParasKey)
	{
		CTestMacroCharParas* pObject = new CTestMacroCharParas;
		return pObject;
	}
	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strHdResReqestKey)
	{
		CHdResReqest* pObject = new CHdResReqest;
		return pObject;
	}

	return NULL;
}

CExBaseObject* GbItems_CreateNewChild(long nClassID)
{
	if (nClassID == GBCLASSID_SAFETY)
	{
		CSafety* pObject = new CSafety;
		return pObject;
	}
	else if (nClassID == GBCLASSID_MACROTEST)
	{
		CMacroTest* pObject = new CMacroTest;
		return pObject;
	}
	else if (nClassID == GBCLASSID_COMMCMD)
	{
		CCommCmd* pObject = new CCommCmd;
		return pObject;
	}
	else if (nClassID == GBCLASSID_SYSPARAEDIT)
	{
		CSysParaEdit* pObject = new CSysParaEdit;
		return pObject;
	}
	else if (nClassID == GBCLASSID_ITEMS)
	{
		CItems* pObject = new CItems;
		return pObject;
	}
	else if (nClassID == GBCLASSID_MACROCHARITEMS)
	{
		CMacroCharItems* pObject = new CMacroCharItems;
		return pObject;
	}

	else if (nClassID == GBCLASSID_SCRIPTTEXT)
	{
		return new CScriptText();
	}
	else if (nClassID == GBCLASSID_SCRIPTTEXT_INIT)
	{
		return new CScriptTextInit();
	}
	else if (nClassID == GBCLASSID_SCRIPTTEXT_NAME)
	{
		return new CScriptTextName();
	}
	else if (nClassID == GBCLASSID_SCRIPTTEXT_RESULT)
	{
		return new CScriptTextResult();
	}
	else if(nClassID == GBCLASSID_REPORTS)
	{
		return new CReports();
	}
	else if(nClassID == RPTCLASSID_RPTREPORTMAP)
	{
		return new CReportMap();
	}
	else if (nClassID == GBCLASSID_ITEMSRSLTEXPRSCRIPT)
	{
		return new CItemsRsltExprScript();
	}
	else if (nClassID == 0x00030060)
	{//GBCLASSID_ITEMSRSLTEXPRSCRIPT有BaseObject变为List    2017-7-14，兼容老版本的错误
		return new CItemsRsltExprScript();
	}
	else if (nClassID == GBCLASSID_TESTMACROUIPARAS)
	{
		CTestMacroUiParas* pObject = new CTestMacroUiParas;
		return pObject;
	}
	else if (nClassID == GBCLASSID_TESTMACROCHARPARAS)
	{
		CTestMacroCharParas* pObject = new CTestMacroCharParas;
		return pObject;
	}
	else if (nClassID == GBCLASSID_HDRESREQUEST)
	{
		CHdResReqest* pObject = new CHdResReqest;
		return pObject;
	}

	return NULL;
}


void Gb_UpdateMacroTestParaData(CExBaseList *pList, const CShortData  *pData, const CString &strMacroID, BOOL bOnlySubItem, BOOL bShowLog)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *pItem = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pItem = (CExBaseObject*)pList->GetNext(pos);
		nClassID = pItem->GetClassID() ;

		if (nClassID ==GBCLASSID_MACROTEST)
		{
			( (CMacroTest*)pItem )->UpdateMacroTestParaData(pData, strMacroID, bShowLog);
		}
		else if (nClassID ==GBCLASSID_ITEMS)
		{
			if (!bOnlySubItem)
			{
				Gb_UpdateMacroTestParaData((CExBaseList*)pItem, pData, strMacroID, bOnlySubItem, bShowLog);
			}
		}
	}
}

void Gb_UpdateCmmCmdParaData(CExBaseList *pList, CCmd *pCmd,UINT nParaID,BOOL bOnlySubItem, BOOL bShowLog)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *pItem = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pItem = (CExBaseObject*)pList->GetNext(pos);
		nClassID = pItem->GetClassID() ;

		if (nClassID ==GBCLASSID_COMMCMD)
		{
			( (CCommCmd*)pItem )->UpdateCmdData(pCmd, nParaID, bShowLog);
		}
		else if (nClassID ==GBCLASSID_ITEMS)
		{
			if (!bOnlySubItem)
			{
				Gb_UpdateCmmCmdParaData((CExBaseList*)pItem, pCmd, nParaID, bOnlySubItem, bShowLog);
			}
		}
	}
}

BOOL GbItems_HasItem(CExBaseList *pItems, UINT nClassID)
{
	POS pos = pItems->GetHeadPosition();
	CExBaseObject *p = NULL;
	BOOL bTrue = FALSE;
	UINT n = 0;

	while (pos != NULL)
	{
		p = pItems->GetNext(pos);
		n = p->GetClassID();

		if (n == nClassID)
		{
			bTrue = TRUE;
			break;
		}

		if (n == GBCLASSID_ITEMS)
		{
			bTrue = GbItems_HasItem((CExBaseList*)p, nClassID);

			if (bTrue)
			{
				break;
			}
		}
	}

	return bTrue;
}

void Gb_SetTestItemSelectedState(CGbItemBase *pItem,long nSelect, BOOL bUpdateParent)
{
	pItem->SetSelect(nSelect);
// 	if(nSelect == 1)
// 		pItem->SetSelect(0);
// 	else 
// 		pItem->SetSelect(1);

	CGbItemBase* pParent = (CGbItemBase*)pItem->GetParent();

	if((pParent != NULL) && bUpdateParent)
	{
		Gb_UpdateItemSelectedState(pParent);
	}

	POS pos = pItem->GetHeadPosition();
	CExBaseObject *pChildItem = NULL;

	while(pos != NULL)
	{
		pChildItem = pItem->GetNext(pos);

		if(Gb_IsItemBaseClassID(pChildItem->GetClassID()))
		{
			Gb_SetTestItemSelectedState((CGbItemBase*)pChildItem,nSelect, bUpdateParent);
		}
	}

	if (bUpdateParent)
	{
		Gb_UpdateGbItemParentTestState(pItem);  //更新测试状态
	}
}


void Gb_UpdateItemSelectedState(CGbItemBase* pItem)
{
	if (pItem->GetClassID() == GBCLASSID_GUIDEBOOK)
	{
		return;
	}

	ASSERT(pItem != NULL);
	long nVal[3] = {0,0,0};

	POS pos = pItem->GetHeadPosition();
	CGbItemBase* pChildItem = NULL;
	long nSelect = 0;

	while(pos != NULL)
	{
		pChildItem = (CGbItemBase*)pItem->GetNext(pos);

		if(Gb_IsItemBaseClassID(pChildItem->GetClassID()))
		{
			nSelect = pChildItem->GetSelect();

			if( 0 <= nSelect && nSelect <= 2)
				nVal[nSelect] = 1;
			else
				nVal[2] = 1;
		}
	}

	nSelect = 0;

	if (nVal[0] == 1 && nVal[1]==0 && nVal[2] == 0)
		nSelect = 0;
	else if (nVal[0] == 0 && nVal[1]==1 && nVal[2] == 0)
		nSelect = 1;
	else if (nVal[0] == 0 && nVal[1]==0 && nVal[2] == 0)
		nSelect = 0;
	else
		nSelect = 2;

	long n1 = pItem->GetSelect();

	if (nSelect == 0 || nSelect == 1)
	{
		if (nSelect != pItem->GetSelect())
		{
			pItem->SetSelect(nSelect);
			CGbItemBase* pParent = (CGbItemBase*)pItem->GetParent();

			if (pParent != NULL)
			{
				Gb_UpdateItemSelectedState(pParent);
			}
		}
	}
	else
	{
		pItem->SetSelect(nSelect);
		CGbItemBase* pParent = (CGbItemBase*)pItem->GetParent();

		if (pParent  != NULL)
		{
			Gb_UpdateItemSelectedState(pParent);
		}
	}

	Gb_UpdateGbItemParentTestState(pItem);  //更新测试状态
}


//////////////////////////////////////////////////////////////////////////
//
extern CExBaseList *g_pOptrAddToAllCmdRootItems;// = NULL;

BOOL Gb_IsRootItemsAncestor(CExBaseObject *pObj)
{
	if (g_pOptrAddToAllCmdRootItems == NULL || pObj == NULL)
	{
		return FALSE;
	}

	CExBaseObject *pParent = NULL;
	pParent = (CExBaseObject*)pObj->GetParent();

	while (pParent != NULL)
	{
		if (pParent == g_pOptrAddToAllCmdRootItems)
		{
			return TRUE;
		}

		pParent = (CExBaseObject*)pParent->GetParent();
	}

	return FALSE;
}

BOOL Gb_IsItems_BeforeTest(CItems *pItems)
{
	return (pItems->m_strID == GBID_BeforeTest_);
}

BOOL Gb_IsItems_AfterTest(CItems *pItems)
{
	return (pItems->m_strID == GBID_AfterTest_);
}

CItems* Gb_GetParentItems_BeforeOrAterTest(CExBaseObject *pObj)
{
	CItems *pItems = (CItems*)pObj->GetAncestor(GBCLASSID_ITEMS);

	if (Gb_IsItems_BeforeTest(pItems))
	{
		return pItems;
	}

	if (Gb_IsItems_AfterTest(pItems))
	{
		return pItems;
	}

	return NULL;
}


BOOL Gb_IsParentItems_BeforeTest(CExBaseObject *pObj)
{
	CItems *pItems = (CItems*)pObj->GetAncestor(GBCLASSID_ITEMS);

	if (pItems == NULL)
	{
		return FALSE;
	}

	return Gb_IsItems_BeforeTest(pItems);
}

BOOL Gb_IsParentItems_AfterTest(CExBaseObject *pObj)
{
	CItems *pItems = (CItems*)pObj->GetAncestor(GBCLASSID_ITEMS);

	if (pItems == NULL)
	{
		return FALSE;
	}

	return Gb_IsItems_AfterTest(pItems);
}

BOOL Gb_IsParentItems_BeforeOrAfterTest(CCommCmd *pCommCmd)
{
	CItems *pItems = (CItems*)pCommCmd->GetParent();

	if (pItems->GetClassID() != GBCLASSID_ITEMS)
	{
		return FALSE;
	}

	if (Gb_IsItems_BeforeTest(pItems))
	{
		return TRUE;
	}

	if (Gb_IsItems_AfterTest(pItems))
	{
		return TRUE;
	}

	return FALSE;
}

CCommCmd* Gb_GetTheOtherCommCmd(CCommCmd *pCommCmd)
{
	CItems *pItems = (CItems*)pCommCmd->GetParent();

	if (pItems->GetClassID() != GBCLASSID_ITEMS)
	{
		return NULL;
	}

	if ( !(Gb_IsParentItems_BeforeOrAfterTest(pCommCmd) || Gb_IsParentItems_BeforeOrAfterTest(pCommCmd)) )
	{
		return NULL;
	}

	CItems *pItemsParent = (CItems *)pItems->GetParent();

	if (pItemsParent->GetClassID() != GBCLASSID_ITEMS)
	{
		return NULL;
	}

	CItems *pFindItems = NULL;
	
	if (Gb_IsItems_BeforeTest(pItems))
	{
		pFindItems = (CItems*)pItemsParent->FindByID(GBID_AfterTest_);
	}
	else if (Gb_IsItems_AfterTest(pItems))
	{
		pFindItems = (CItems*)pItemsParent->FindByID(GBID_BeforeTest_);
	}

	if (pFindItems == NULL)
	{
		return NULL;
	}

	CCommCmd *pCommCmdFind = (CCommCmd*)pFindItems->FindByID(pCommCmd->m_strID);

	if (!Gb_IsCommCmdTheSameType(pCommCmd, pCommCmdFind))
	{
		pCommCmdFind = NULL;
	}

	if (pCommCmdFind == NULL)
	{
		POS pos = pFindItems->GetHeadPosition();
		CExBaseObject *p = NULL;

		while (pos != NULL)
		{
			p = pFindItems->GetNext(pos);

			if (p->GetClassID() == GBCLASSID_COMMCMD)
			{
				if (Gb_IsCommCmdTheSameType(pCommCmd, (CCommCmd*)p))
				{
					pCommCmdFind = (CCommCmd *)p;
					break;
				}
			}
		}
	}

	return pCommCmdFind;
}

BOOL Gb_IsCommCmdTheSameType(CCommCmd *pSrc, CCommCmd *pDest, BOOL bUseID)
{
	if (pSrc == NULL || pDest == NULL)
	{
		return FALSE;
	}

	if (pSrc->m_strCommCmdID != pDest->m_strCommCmdID)
	{
		return FALSE;
	}

	if (bUseID)
	{
		if (pSrc->m_strID != pDest->m_strID)
		{
			return FALSE;
		}
	}

	if (pSrc->GetCmd()->m_strDatasetPath != pDest->GetCmd()->m_strDatasetPath)
	{
		return FALSE;
	}

	if (Gb_IsParentItems_BeforeOrAfterTest(pDest) && Gb_IsParentItems_BeforeOrAfterTest(pDest))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


//Gb_Delete
void Gb_DeleteAllItem_Command(CCommCmd *pCommCmd, CExBaseList *pList, CTreeCtrl *pTreeCtrl, CExBaseList *pListDelete);

void Gb_DeleteAllItem(CExBaseObject* pItem, CTreeCtrl *pTreeCtrl, CExBaseList *pListDelete)
{
	if (g_pOptrAddToAllCmdRootItems == NULL)
	{
		return;
	}

	ASSERT (pItem != NULL);

	if (pItem == NULL)
	{
		return;
	}

	if (pItem->GetClassID() == GBCLASSID_COMMCMD)
	{
		Gb_DeleteAllItem_Command((CCommCmd*)pItem, g_pOptrAddToAllCmdRootItems, pTreeCtrl, pListDelete);
	}
}

void Gb_DeleteAllItem_Command(CCommCmd *pCommCmd, CExBaseList *pList, CTreeCtrl *pTreeCtrl, CExBaseList *pListDelete)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	CCmd *pCmd = pCommCmd->GetCmd();
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pList->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == GBCLASSID_ITEMS)
		{
			Gb_DeleteAllItem_Command(pCommCmd, (CExBaseList*)p, pTreeCtrl, pListDelete);
			continue;
		}

		if ((nClassID != GBCLASSID_COMMCMD) || (p == pCommCmd) )
		{
			continue;
		}

		if ((p->m_strID != pCommCmd->m_strID) || ( ((CCommCmd*)p)->m_strCommCmdID != pCommCmd->m_strCommCmdID) )
		{
			continue;
		}

#ifndef _PSX_QT_LINUX_
        pTreeCtrl->DeleteItem((HTREEITEM)p->m_dwItemData);
#endif
        //CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_Delete2.GetString()/*_T("删除：%s")*/, p->GetNamePathEx(GBCLASSID_DEVICE));
		pList->Delete(p);
		pListDelete->AddTail(p);
	}
}

//Gb_Delete
void Gb_DeleteCommCmdValue(CCommCmd *pSrcCommCmd, CCommCmd *pDestCommCmd, CExBaseList *pListValue)
{
	if ( !(Gb_IsParentItems_BeforeTest(pDestCommCmd) || Gb_IsParentItems_AfterTest(pDestCommCmd)) )
	{
		return;
	}

// 	if (/*(pSrcCommCmd->m_strID != pDestCommCmd->m_strID) || */
// 		( pSrcCommCmd->m_strCommCmdID != pDestCommCmd->m_strCommCmdID) )
// 	{
// 		return;
// 	}

	if (pSrcCommCmd == pDestCommCmd)
	{
		return;
	}

	if (!Gb_IsCommCmdTheSameType(pDestCommCmd, pSrcCommCmd))
	{
		return;
	}

    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_DelCommunPara.GetString()/*_T("删除通讯命令的参数：%s")*/, pDestCommCmd->GetNamePathEx(GBCLASSID_DEVICE).GetString());

	CCmd *pCmd = ((CCommCmd*)pDestCommCmd)->GetCmd();
	POS posValue = NULL;
	CValue *pVal = NULL;
	CValue *pFind = NULL;
	posValue = pListValue->GetHeadPosition();

	while (posValue != NULL)
	{
		pVal = (CValue *)pListValue->GetNext(posValue);
		pFind = (CValue *)pCmd->FindByID(pVal->m_strID);

		if (pFind != NULL)
		{
			pCmd->Delete(pFind);
		}
	}
}

void Gb_DeleteValueFromAllCommCmd(CCommCmd *pCommCmd, CExBaseList *pListValue, CExBaseList *pList)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	CCmd *pCmd = pCommCmd->GetCmd();
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pList->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == GBCLASSID_ITEMS)
		{
			Gb_DeleteValueFromAllCommCmd(pCommCmd, pListValue, (CExBaseList*)p);
			continue;
		}

		if ((nClassID == GBCLASSID_COMMCMD) && (p != pCommCmd) )
		{
			Gb_DeleteCommCmdValue(pCommCmd, (CCommCmd*)p, pListValue);
		}

// 		if ((p->m_strID != pCommCmd->m_strID) || ( ((CCommCmd*)p)->m_strCommCmdID != pCommCmd->m_strCommCmdID) )
// 		{
// 			continue;
// 		}
// 
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("删除通讯命令的参数：%s"), p->GetNamePathEx(GBCLASSID_DEVICE));
// 		
// 		CCmd *pCmd = ((CCommCmd*)p)->GetCmd();
// 		POS posValue = NULL;
// 		CValue *pVal = NULL;
// 		CValue *pFind = NULL;
// 		posValue = pListValue->GetHeadPosition();
// 
// 		while (posValue != NULL)
// 		{
// 			pVal = (CValue *)pListValue->GetNext(posValue);
// 			pFind = (CValue *)pCmd->FindByID(pVal->m_strID);
// 
// 			if (pFind != NULL)
// 			{
// 				pCmd->Delete(pFind);
// 			}
// 		}
	}
}

void Gb_DeleteValueFromAllCommCmd(CCommCmd *pCommCmd, CExBaseList *pListValue)
{
	if (Gb_IsRootItemsAncestor(pCommCmd))
	{
		ASSERT (g_pOptrAddToAllCmdRootItems != NULL);
		Gb_DeleteValueFromAllCommCmd(pCommCmd, pListValue, g_pOptrAddToAllCmdRootItems);
	}
	else
	{
		CCommCmd *pOther = Gb_GetTheOtherCommCmd(pCommCmd);

		if (pOther != NULL)
		{
			Gb_DeleteCommCmdValue(pCommCmd, pOther, pListValue);
		}
	}
}

//Gb_AddValue
CValue* Gb_FindValueByIDPath(const CString &strID, CValues *pValues)
{
	POS pos = pValues->GetHeadPosition();
	CValue *pValue = NULL;
	CValue *pFind = NULL;
	long nIDLen = strID.GetLength();
	long nLenTemp = 0;

	while (pos != NULL)
	{
		pValue = (CValue *)pValues->GetNext(pos);
		nLenTemp = pValue->m_strID.GetLength();

		if (nIDLen == nLenTemp)
		{
			if (strID == pValue->m_strID)
			{
				pFind = pValue;
				break;
			}
		}
		else if (nIDLen > nLenTemp)
		{
			if (strID.Right(pValue->m_strID.GetLength()) == pValue->m_strID)
			{
				CHAR xch = strID.GetAt(nIDLen - nLenTemp - 1);

				if (xch == '$')
				{
					pFind = pValue;
					break;
				}
			}
		}
		else
		{
			if (pValue->m_strID.Right(strID.GetLength()) == strID)
			{
				CHAR xch = strID.GetAt(nLenTemp - nIDLen - 1);

				if (xch == '$')
				{
					pFind = pValue;
					break;
				}
			}
		}
	}

	return pFind;
}

BOOL Gb_IsDataObj_BOOL(CDataObj *pDataObj)
{
	CString strTemp = pDataObj->m_strDataType;
	strTemp.MakeUpper();

	if (strTemp == _T("BOOL"))
	{
		return TRUE;
	}

	POS pos = pDataObj->GetHeadPosition();
	CDataObjValue *pValue = NULL;

	while (pos != NULL)
	{
		pValue = (CDataObjValue *)pDataObj->GetNext(pos);
		strTemp = pValue->m_strDataTypeID;
		strTemp.MakeUpper();

		if (strTemp == _T("BOOL"))
		{
			return TRUE;
		}
	}

	return FALSE;
}

CValue* Gb_AddValuesToCmd(CCommCmd *pCommCmd, CExBaseObject *pObj)
{
	CString strID = pObj->m_strID;
	CString strName = pObj->m_strName;
	CString strValue;
	UINT nClassID = pObj->GetClassID();
	ASSERT (nClassID == GBCLASSID_DATAOBJ || nClassID == GBCLASSID_GBTDATA);

	CDataObj* pSet = (CDataObj*)pObj;
	strValue = pSet->m_strValue;

	if (Gb_IsDataObj_BOOL(pSet))
	{
		CExBaseList *pParent = (CExBaseList*)pCommCmd->GetParent();

		if (pParent->m_strID == GBID_BeforeTest_)
		{
			if (g_nOptrAddToAllCmdBeforeIs1 == 1)
			{
				strValue = _T("1");
			}
			else
			{
				strValue = _T("0");
			}
		}
		else if (pParent->m_strID == GBID_AfterTest_)
		{
			if (g_nOptrAddToAllCmdBeforeIs1 == 1)
			{
				strValue = _T("0");
			}
			else
			{
				strValue = _T("1");
			}
		}

	}

	CValues *pValues = pCommCmd->GetCmd();
	CValue *pValue = Gb_FindValueByIDPath(strID, pValues);//(CValue*)pValues->FindByID(strID);

	if (pValue == NULL)
	{
		pValue = pValues->AddNew(strID, strName, strValue);
	}

	return pValue;
}

void Gb_AddValuesToAllCommCmd(CExBaseList *pItems, CExBaseObject *pObj, CCommCmd *pCommCmd)
{
	POS pos = pItems->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pItems->GetNext(pos);

		switch (p->GetClassID())
		{
		case GBCLASSID_ITEMS:
			Gb_AddValuesToAllCommCmd((CExBaseList*)p, pObj, pCommCmd);
			break;
		case GBCLASSID_COMMCMD:
			if (p != pCommCmd)
			{
				if (Gb_IsCommCmdTheSameType((CCommCmd*)p, pCommCmd))
				{
					Gb_AddValuesToCmd((CCommCmd*)p, pObj);;
				}
			}

			break;
		default:
			break;
		}
	}
}


void Gb_AddValuesToAllCmd(CExBaseObject *pObj, CCommCmd *pCommCmd)
{
	if (Gb_IsRootItemsAncestor(pCommCmd))
	{
		Gb_AddValuesToAllCommCmd(g_pOptrAddToAllCmdRootItems, pObj, pCommCmd);
	}
	else
	{
		CCommCmd *pOther = Gb_GetTheOtherCommCmd(pCommCmd);

		if (pOther != NULL)
		{
			Gb_AddValuesToCmd(pOther, pObj);
		}
	}
}

//Gb_Edit
void Gb_EditCmdValue(CValue *pValue, CCommCmd *pDestCommCmd, CCommCmd *pSrcCommCmd)
{
	CItems *pDestItems = Gb_GetParentItems_BeforeOrAterTest(pDestCommCmd);
	CItems *pSrcItems  = Gb_GetParentItems_BeforeOrAterTest(pSrcCommCmd);
	
	if (pDestItems == NULL || pSrcItems == NULL)
	{
		return;
	}

	CCmd *pCmd = pDestCommCmd->GetCmd();
	CValue *pFind = Gb_FindValueByIDPath(pValue->m_strID, pCmd);

	if (pFind == NULL)
	{
		return;
	}

	CDevice *pDevice = (CDevice*)pDestCommCmd->GetAncestor(GBCLASSID_DEVICE);
	CDataObj *pDataObj = pDevice->FindDataObjByID(pValue->m_strID, -1);

	if (pDataObj == NULL)
	{
		return;
	}

	//编辑数据联动，只针对BOOL性数据类型，即压板和控制字
	if (!Gb_IsDataObj_BOOL(pDataObj))
	{
		return;
	}

	if (pDestItems->m_strID == pSrcItems->m_strID)
	{
		pFind->m_strValue = pValue->m_strValue;
	}
	else
	{
		if (pValue->m_strValue == _T("0"))
		{
			pFind->m_strValue = _T("1");
		}
		else if (pValue->m_strValue == _T("1"))
		{
			pFind->m_strValue = _T("0");
		}
		else
		{
			pFind->m_strValue = pValue->m_strValue;
		}
	}
	

	return;

// 	if (pDestItems->m_strID == pSrcItems->m_strID)
// 	{
// 		pFind->m_strValue = pValue->m_strValue;
// 	}
// 	else
// 	{
// 		CDevice *pDevice = (CDevice*)pDestCommCmd->GetAncestor(GBCLASSID_DEVICE);
// 		CDataObj *pDataObj = pDevice->FindDataObjByID(pValue->m_strID, -1);
// 
// 		if (pDataObj == NULL)
// 		{
// 			pFind->m_strValue = pValue->m_strValue;
// 		}
// 		else if (Gb_IsDataObj_BOOL(pDataObj))
// 		{
// 			if (pValue->m_strValue == _T("0"))
// 			{
// 				pFind->m_strValue = _T("1");
// 			}
// 			else if (pValue->m_strValue == _T("1"))
// 			{
// 				pFind->m_strValue = _T("0");
// 			}
// 			else
// 			{
// 				pFind->m_strValue = pValue->m_strValue;
// 			}
// 		}
// 		else
// 		{
// 			pFind->m_strValue = pValue->m_strValue;
// 		}
// 	}
}

void Gb_EditAllCmdValue(CExBaseList *pItems, CValue *pValue, CCommCmd *pCommCmd)
{
	POS pos = pItems->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pItems->GetNext(pos);

		switch (p->GetClassID())
		{
		case GBCLASSID_ITEMS:
			Gb_EditAllCmdValue((CExBaseList*)p, pValue, pCommCmd);
			break;

		case GBCLASSID_COMMCMD:
			if (p != pCommCmd)
			{
				if (Gb_IsCommCmdTheSameType((CCommCmd*)p, pCommCmd))
				{
					Gb_EditCmdValue(pValue, (CCommCmd*)p, pCommCmd);
				}
			}

			break;

		default:
			break;
		}
	}
}

void Gb_EditAllCmdValue(CValue *pValue, CCommCmd *pCommCmd)
{
	if (Gb_IsRootItemsAncestor(pCommCmd))
	{
		Gb_EditAllCmdValue(g_pOptrAddToAllCmdRootItems, pValue, pCommCmd);
	}
	else
	{
		CCommCmd *pOther = Gb_GetTheOtherCommCmd(pCommCmd);

		if (pOther != NULL)
		{
			Gb_EditCmdValue(pValue, pOther, pCommCmd);
		}
	}
}

//粘贴
void Gb_PasteCommCmd(CCommCmd *pSrcCommCmd, CCommCmd *pDestCommCmd)
{
	CCmd *pCmdSrc  = pSrcCommCmd->GetCmd();
	CCmd *pCmdDest = pDestCommCmd->GetCmd();

	pCmdDest->DeleteAll();
	pCmdDest->AppendClone(pCmdSrc);
}

void Gb_PasteAllCommCmd(CExBaseList *pItems, CCommCmd *pSrcCommCmd, CCommCmd *pCurrCommCmd)
{
	POS pos = pItems->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pItems->GetNext(pos);

		switch (p->GetClassID())
		{
		case GBCLASSID_ITEMS:
			Gb_PasteAllCommCmd((CExBaseList*)p, pSrcCommCmd, pCurrCommCmd);
			break;

		case GBCLASSID_COMMCMD:
			{
				if (p == pCurrCommCmd)
				{
					continue;
				}

				if (Gb_IsCommCmdTheSameType(pSrcCommCmd, (CCommCmd*)p))
				{
					Gb_PasteCommCmd(pSrcCommCmd, (CCommCmd*)p);
				}
			}

			break;
		default:
			break;
		}
	}
}

void Gb_PasteAllCommCmd(CCommCmd *pSrcCommCmd, CCommCmd *pCurrCommCmd)
{
	if (Gb_IsRootItemsAncestor(pCurrCommCmd))
	{
		Gb_PasteAllCommCmd(g_pOptrAddToAllCmdRootItems, pSrcCommCmd, pCurrCommCmd);
	}
	else
	{
		CCommCmd *pOther = Gb_GetTheOtherCommCmd(pCurrCommCmd);

		if (pOther != NULL)
		{
			Gb_PasteCommCmd(pSrcCommCmd, pOther);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
#define GBCLASSID_ITEMBASE			(GBCLASSID_EXLISTCLASS	+  0x00001000)
#define GBCLASSID_ITEMSBASE			(GBCLASSID_EXLISTCLASS	+  0x00003000)

//清空报告数据
void Gb_EmptyReportDatas(CExBaseList *pList, BOOL bOnlySelect)
{
	if (pList == NULL)
	{
		return;
	}
	
	CGbItemBase *pItemList = (CGbItemBase *)pList;
	pItemList->CGbItemBase::ClearReport(FALSE);
	pItemList->CGbItemBase::SetState(TEST_STATE_NORMAL);

	POS pos = pList->GetHeadPosition();
	CExBaseObject *pItem = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pItem = pList->GetNext(pos);
		nClassID = pItem->GetClassID();

		if (nClassID == GBCLASSID_ITEMS)
		{
			CItems *pItems = (CItems*)pItem;

			if (bOnlySelect)
			{
				if (pItems->m_nSelect == 0)
				{
					continue;
				}
			}

			pItems->ClearReport(FALSE);
			pItems->SetState(TEST_STATE_NORMAL);
			Gb_EmptyReportDatas(pItems, bOnlySelect);
		}
		else if (nClassID == GBCLASSID_MACROTEST)
		{
			CMacroTest *pMacroTest = (CMacroTest *)pItem;

			if (bOnlySelect)
			{
				if (pMacroTest->m_nSelect == 0)
				{
					continue;
				}
			}

			pMacroTest->ClearReport(FALSE);
			pMacroTest->SetState(TEST_STATE_NORMAL);
			Gb_EmptyReportDatas(pMacroTest, bOnlySelect);
		}
		else if (nClassID == GBCLASSID_MACROCHARITEMS)
		{
			CMacroCharItems *pMacroCharItems = (CMacroCharItems *)pItem;

			if (bOnlySelect)
			{
				if (pMacroCharItems->m_nSelect == 0)
				{
					continue;
				}
			}

			pMacroCharItems->ClearReport(FALSE);
			pMacroCharItems->SetState(TEST_STATE_NORMAL);
			Gb_EmptyReportDatas(pMacroCharItems, bOnlySelect);
		}
		else if (nClassID == GBCLASSID_SAFETY)
		{
			CSafety *pSafety = (CSafety *)pItem;

			if (bOnlySelect)
			{
				if (pSafety->m_nSelect == 0)
				{
					continue;
				}
			}

			pSafety->ClearReport(FALSE);
			pSafety->SetState(TEST_STATE_NORMAL);
			Gb_EmptyReportDatas(pSafety, bOnlySelect);
		}
		else if (nClassID == GBCLASSID_SYSPARAEDIT)
		{
			CSysParaEdit *pSysParaEdit = (CSysParaEdit *)pItem;

			if (bOnlySelect)
			{
				if (pSysParaEdit->m_nSelect == 0)
				{
					continue;
				}
			}

			pSysParaEdit->ClearReport(FALSE);
			pSysParaEdit->SetState(TEST_STATE_NORMAL);
			Gb_EmptyReportDatas(pSysParaEdit, bOnlySelect);
		}
		else if ((nClassID & GBCLASSID_ITEMBASE) == GBCLASSID_ITEMBASE)
		{
			CGbItemBase *pItemBase = (CGbItemBase*)pItem;

			if (bOnlySelect)
			{
				if (pItemBase->m_nSelect == 0)
				{
					continue;
				}
			}

			pItemBase->ClearReport(FALSE);
			pItemBase->SetState(TEST_STATE_NORMAL);
		}
	}
}

long Gb_QueryBftAftItem(CExBaseList *pGuideBook, CExBaseObject *pCurrItem, CExBaseList &listQuery)
{
	CGuideBook *p = (CGuideBook*)pGuideBook;
	CItemContainer *pContainer = (CItemContainer*)p->GetItemContainer();
	CExBaseList *pListAll = pContainer->GetGuideBookAllItems();
	CGbItemBase *pItem = (CGbItemBase*)pCurrItem;
	long nIndex = pItem->m_nIndex;

	POS pos = pListAll->GetHeadPosition();
	CString strTemp;

	while (pos != NULL)
	{
		pItem = (CGbItemBase *)pListAll->GetNext(pos);

		if (pItem->m_nIndex > nIndex)
		{
			break;
		}

		strTemp = pItem->m_strID.Left(5);

		if (strTemp == GBID_ItemPrefix_BeforeTest
			|| strTemp == GBID_ItemPrefix_AfterTest)
		{
			listQuery.AddTail(pItem);
		}
	}

	return listQuery.GetCount();
}

long Gb_QueryBftItem(CExBaseList &listQuery, CExBaseList &listDest)
{
	POS pos = listQuery.GetHeadPosition();
	CString strTemp;
	CGbItemBase *pItem = NULL;
	CGbItemBase *pItemFind = NULL;
	BOOL bFind = FALSE;

	while (pos != NULL)
	{
		pItem = (CGbItemBase *)listQuery.GetNext(pos);

		if (pItem->m_strID.Left(5) == GBID_ItemPrefix_BeforeTest)
		{
			strTemp = GBID_ItemPrefix_AfterTest + pItem->m_strID.Mid(5);

			POS posFind = pos;
			bFind = FALSE;

			while (posFind != NULL)
			{
				pItemFind = (CGbItemBase *)listQuery.GetNext(posFind);

				if (pItemFind->m_strID == strTemp)
				{
					bFind = TRUE;
					break;
				}
			}

			if ( !bFind )
			{
				listDest.AddTail(pItem);
			}
		}
	}

	return listDest.GetCount();
}


CItemsRsltExprScriptMngr* Gb_GetExprScriptMngr(CExBaseObject *pGbObj)
{
	CGuideBook *pGuideBook = (CGuideBook *)pGbObj->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);

	CItemsRsltExprScriptMngr *pMngr = pGuideBook->GetItemsRsltExprScriptMngr();
	ASSERT (pMngr != NULL);

	return pMngr;
}




//2021-8-9  lijunqing  
void Gb_QuerySafetyDataTypes(CSafety *pSafety, CDataTypes *pDataTypes)
{
	CShortDatas *pDatas = pSafety->m_pDatas;
	POS pos = pDatas->GetHeadPosition();
	CShortData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CShortData *)pDatas->GetNext(pos);

		if(pData->m_strDataTypeID == g_strGbDataTypeCombobox)
		{
			if (pDataTypes->FindByID(pData->m_strFormat) == NULL)
			{
				CDataType* pDataType = (CDataType*)CGbDataTypeMngr::GetSafetyComboDataTypes()->FindByID(pData->m_strFormat);
				pDataTypes->AddTail(pDataType);
			}
		}
	}
}

void Gb_QueryItems_SafetyDataTypes(CGbItemBase *pItemRoot, CDataTypes *pDataTypes)
{
	if (pItemRoot->GetClassID() == GBCLASSID_SAFETY)
	{
		Gb_QuerySafetyDataTypes((CSafety*)pItemRoot, pDataTypes);
	}
	else
	{
		POS pos = pItemRoot->GetHeadPosition();
		CExBaseObject *p = NULL;

		while (pos != NULL)
		{
			p = pItemRoot->GetNext(pos);

			if (p->GetClassID() == GBCLASSID_SAFETY)
			{
				Gb_QuerySafetyDataTypes((CSafety*)p, pDataTypes);
			}
			else if (p->GetClassID() == GBCLASSID_ITEMS)
			{
				Gb_QueryItems_SafetyDataTypes((CGbItemBase*)p, pDataTypes);
			}
		}
	}
}
//2023-9-18 lijunqing 设置测试项目分类的报告数据
void Gb_SetItemsReport(CItems *pDestItems, CItems *pSrcItems)
{
	POS pos = pSrcItems->GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseObject *pFind = NULL;

	while (pos != NULL)
	{
		p = pSrcItems->GetNext(pos);
		pFind = pDestItems->FindByID(p->m_strID);

		if (pFind == NULL)
		{
			continue;
		}

		Gb_SetItemReport((CGbItemBase*)pFind, (CGbItemBase*)p);
	}
}

void Gb_SetItemReport_Safety(CSafety *pDest, CSafety *pSrc)
{
	pDest->m_pDatas->InitDatasValue(pSrc->m_pDatas);
	CReports *pReports_Dest = pDest->GetReports();
	CReports *pReports_Src = pSrc->GetReports();

	pReports_Dest->AppendCloneEx(*pReports_Src);
}


void Gb_SetItemReport(CGbItemBase *pDest, CGbItemBase *pSrc)
{
	if (pDest->GetClassID() != pSrc->GetClassID())
	{
		return;
	}

	UINT nClassID = pDest->GetClassID();

	switch (nClassID)
	{
	case GBCLASSID_SAFETY:
		Gb_SetItemReport_Safety((CSafety*)pDest, (CSafety*)pSrc);
		break;
	}
}

