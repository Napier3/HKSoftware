//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttItemBase.cpp  CSttItemBase


#include "stdafx.h"
#include "SttItemBase.h"
#include "SttItems.h"
#include "SttContents.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttItemBase::CSttItemBase()
{
	//��ʼ������
	m_nTkID = 65535;
	m_nShow = 1;
	m_nEnable = 1;
	m_nExecType = 0;
	m_nBatchItem = 0;
	m_nMdvTestEach = 0;
	m_nState = 0;
	m_nSelect = 1;

	//��ʼ����Ա����
	m_pSttReports = NULL;
	m_pSttReportMap = NULL;
	m_pRsltExpr = NULL;
}

CSttItemBase::~CSttItemBase()
{
}

BSTR CSttItemBase::GetXmlElementKey()
{
	return CSttCmdDefineXmlRWKeys::CSttItemBaseKey();
}

long CSttItemBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTkidKey, oNode, m_nTkID);
	xml_GetAttibuteValue(pXmlKeys->m_strShowKey, oNode, m_nShow);
	xml_GetAttibuteValue(pXmlKeys->m_strEnableKey, oNode, m_nEnable);
	xml_GetAttibuteValue(pXmlKeys->m_strExectypeKey, oNode, m_nExecType);
	xml_GetAttibuteValue(pXmlKeys->m_strBatchItemKey, oNode, m_nBatchItem);
	xml_GetAttibuteValue(pXmlKeys->m_strMdvTestEachKey, oNode, m_nMdvTestEach);
	xml_GetAttibuteValue(pXmlKeys->m_strStateKey, oNode, m_nState);
	xml_GetAttibuteValue(pXmlKeys->m_strSelectKey, oNode, m_nSelect);
	return 0;
}

long CSttItemBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;


	if (CSttCmdDefineXmlRWKeys::IsOnlyGetItem())
	{
		xml_SetAttributeValue(pXmlRWKeys->m_strNameKey, oElement, m_strName);
		xml_SetAttributeValue(pXmlRWKeys->m_strIDKey, oElement, m_strID);

		CString strText;
		strText.Format(_T("%d"), m_nTkID);
		xml_SetAttributeValue(pXmlKeys->m_strTkidKey, oElement, strText);

		strText.Format(_T("%d"), m_nSelect);
		xml_SetAttributeValue(pXmlKeys->m_strSelectKey, oElement, strText);
		return 0;
	}

	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	xml_SetAttributeValue(pXmlKeys->m_strTkidKey, oElement, m_nTkID);
	xml_SetAttributeValue(pXmlKeys->m_strSelectKey, oElement, m_nSelect);
	xml_SetAttributeValue(pXmlKeys->m_strShowKey, oElement, m_nShow);
	xml_SetAttributeValue(pXmlKeys->m_strEnableKey, oElement, m_nEnable);
	xml_SetAttributeValue(pXmlKeys->m_strExectypeKey, oElement, m_nExecType);
	xml_SetAttributeValue(pXmlKeys->m_strBatchItemKey, oElement, m_nBatchItem);
	xml_SetAttributeValue(pXmlKeys->m_strMdvTestEachKey, oElement, m_nMdvTestEach);
	xml_SetAttributeValue(pXmlKeys->m_strStateKey, oElement, m_nState);
	return 0;
}

long CSttItemBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nTkID);
		BinarySerializeCalLen(oBinaryBuffer, m_nShow);
		BinarySerializeCalLen(oBinaryBuffer, m_nEnable);
		BinarySerializeCalLen(oBinaryBuffer, m_nExecType);
		BinarySerializeCalLen(oBinaryBuffer, m_nBatchItem);
		BinarySerializeCalLen(oBinaryBuffer, m_nMdvTestEach);
		BinarySerializeCalLen(oBinaryBuffer, m_nState);
		BinarySerializeCalLen(oBinaryBuffer, m_nSelect);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nTkID);
		BinarySerializeRead(oBinaryBuffer, m_nShow);
		BinarySerializeRead(oBinaryBuffer, m_nEnable);
		BinarySerializeRead(oBinaryBuffer, m_nExecType);
		BinarySerializeRead(oBinaryBuffer, m_nBatchItem);
		BinarySerializeRead(oBinaryBuffer, m_nMdvTestEach);
		BinarySerializeRead(oBinaryBuffer, m_nState);
		BinarySerializeRead(oBinaryBuffer, m_nSelect);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nTkID);
		BinarySerializeWrite(oBinaryBuffer, m_nShow);
		BinarySerializeWrite(oBinaryBuffer, m_nEnable);
		BinarySerializeWrite(oBinaryBuffer, m_nExecType);
		BinarySerializeWrite(oBinaryBuffer, m_nBatchItem);
		BinarySerializeWrite(oBinaryBuffer, m_nMdvTestEach);
		BinarySerializeWrite(oBinaryBuffer, m_nState);
		BinarySerializeWrite(oBinaryBuffer, m_nSelect);
	}
	return 0;
}

void CSttItemBase::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == STTCMDCLASSID_REPORTS)
		{
			m_pSttReports = (CSttReports *)p;
		}
		else if (nClassID == STTGBXMLCLASSID_CSTTREPORTMAP)
		{
			m_pSttReportMap = (CSttReportMap *)p;
		}
		else if (nClassID == STTGBXMLCLASSID_CSTTITEMRSLTEXPR)
		{
			m_pRsltExpr = (CSttItemRsltExpr *)p;
		}
	}
}

BOOL CSttItemBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttItemBase *p = (CSttItemBase*)pObj;

	if(m_nTkID != p->m_nTkID)
	{
		return FALSE;
	}

	if(m_nShow != p->m_nShow)
	{
		return FALSE;
	}

	if(m_nEnable != p->m_nEnable)
	{
		return FALSE;
	}

	if(m_nExecType != p->m_nExecType)
	{
		return FALSE;
	}

	if(m_nBatchItem != p->m_nBatchItem)
	{
		return FALSE;
	}

	if(m_nMdvTestEach != p->m_nMdvTestEach)
	{
		return FALSE;
	}

	if(m_nState != p->m_nState)
	{
		return FALSE;
	}

	if(m_nSelect != p->m_nSelect)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttItemBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttItemBase *p = (CSttItemBase*)pDest;

	p->m_nTkID = m_nTkID;
	p->m_nShow = m_nShow;
	p->m_nEnable = m_nEnable;
	p->m_nExecType = m_nExecType;
	p->m_nBatchItem = m_nBatchItem;
	p->m_nMdvTestEach = m_nMdvTestEach;
	p->m_nState = m_nState;
	p->m_nSelect = m_nSelect;
	return TRUE;
}

CBaseObject* CSttItemBase::Clone()
{
	CSttItemBase *p = new CSttItemBase();
	Copy(p);
	return p;
}

CBaseObject* CSttItemBase::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttItemBase *p = new CSttItemBase();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttItemBase::CanPaste(UINT nClassID)
{
	if (nClassID == STTGBXMLCLASSID_CSTTREPORTMAP)
	{
		return TRUE;
	}

	if (nClassID == STTCMDCLASSID_REPORTS)
	{
		return TRUE;
	}

	if (nClassID == STTGBXMLCLASSID_CSTTITEMRSLTEXPR)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttItemBase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttReportMapKey)
	{
		pNew = new CSttReportMap();
	}
	else if(strClassID == pXmlKeys->m_strCSttReportsKey)
	{
		pNew = new CSttReports();
	}
	else if (strClassID == pXmlKeys->m_strContentsKey)
	{	//2022-9-3  lijunqing  ��Ϊdevice��macro-char-items�����������ߣ�
		//�Լ�������Ե�ʱ��Ҳ���������ߣ����Խ�contents��չ�ŵ��˴˴�
		return new CSttContents();
	}
	//shaolei 2023-3-1 
	else if (strClassID == pXmlKeys->m_strCSttItemRsltExprKey)
	{
		return new CSttItemRsltExpr();
	}

	return pNew;
}

CExBaseObject* CSttItemBase::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == STTGBXMLCLASSID_CSTTREPORTMAP)
	{
		pNew = new CSttReportMap();
	}
	else if (nClassID == STTCMDCLASSID_REPORTS)
	{
		pNew = new CSttReports();
	}
	//shaolei 2023-3-1 
	else if (nClassID == STTGBXMLCLASSID_CSTTITEMRSLTEXPR)
	{
		pNew = new CSttItemRsltExpr();
	}

	return pNew;
}

CSttReports* CSttItemBase::SetReports(CSttReports *pSttReports)
{
	if (m_pSttReports == NULL)
	{
		m_pSttReports = new CSttReports();
		AddNewChild(m_pSttReports);
	}

	//��ʱ�����Ǳ���֮ǰ�ı�������
	m_pSttReports->DeleteAll();
	pSttReports->Copy(m_pSttReports);

	return m_pSttReports;
}

CSttReport* CSttItemBase::GetReport(long nIndex)
{
	if (m_pSttReports == NULL)
	{
		return NULL;
	}

	long nCount = m_pSttReports->GetCount();

	if (nIndex == -1)
	{
		nIndex = nCount-1;
	}

	if (nCount > nIndex )
	{
		CSttReport *pReport = (CSttReport*)m_pSttReports->GetAtIndex(nIndex);
		return pReport;
	}
	else
	{
		return NULL;
	}
}

long CSttItemBase::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	if (! CSttCmdDefineXmlRWKeys::IsOnlyGetItem())
	{
		return CExBaseList::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
	}

// 	POS pos = GetHeadPosition();
// 	CExBaseObject *pObj = NULL;
// 	UINT nClassID = 0;
// 
// 	while (pos != NULL)
// 	{
// 		pObj = GetNext(pos);
// 		nClassID = pObj->GetClassID();
// 
// 		if ((nClassID == STTGBXMLCLASSID_CSTTREPORTMAP)
// 			|| (nClassID == STTCMDCLASSID_REPORTS) )
// 		{
// 			continue;
// 		}
// 
// 		pObj->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
// 	}

	return 0;
}

long CSttItemBase::GetGbItemCount()
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);

		if (stt_gb_is_a_itembase(pObj))
		{
			nCount++;

			CSttItemBase *pItemBase = (CSttItemBase *)pObj;
			nCount += pItemBase->GetGbItemCount();
		}
	}

	return nCount;
}

void CSttItemBase::GetItemsCountByItemsType(long &nTotalCount, long &nEligibleCount, long &nInlegibleCount)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	nTotalCount = nEligibleCount = nInlegibleCount = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != STTGBXMLCLASSID_CSTTITEMS)
		{
			continue;
		}

		CSttItems *pItems = (CSttItems *)pObj;

		if (pItems->m_nSelect != 1)
		{
			continue;
		}

		if (pItems->IsTypeRootNode())
		{
			nTotalCount++;  //����ǹ�����ڵ㣬������CItems������һ��������Ŀ������������Ŀ��ͳ�ƣ�

			if (pItems->m_nState == TEST_STATE_ELIGIBLE || pItems->m_nState == TEST_STATE_ELIGIBLEEX)
			{
				nEligibleCount++;
			}
			else if (pItems->m_nState == TEST_STATE_INLEGIBLE)
			{
				nInlegibleCount++;
			}

			continue;
		}

		long nTotal = 0, nEligible = 0, nInegible = 0;
		pItems->GetItemsCountByItemsType(nTotal, nEligible, nInegible);
		nTotalCount += nTotal;
		nEligibleCount += nEligible;
		nInlegibleCount += nInegible;
	}
}

void CSttItemBase::GetFirstTwoItemsByItemsType(CString &strFirst, CString &strSecond)
{
	CExBaseList oList;
	GetAllItemsByItemsType(oList);

	if (oList.GetCount() == 0)
	{
		return;
	}
	
	CExBaseObject *pFirst = oList.GetHead();
	strFirst = pFirst->m_strName;

	oList.RemoveHead();
	if (oList.GetCount() == 0)
	{
		strSecond = _T("����Ŀ");
		return;
	}

	CExBaseObject *pSecond = oList.GetHead();
	strSecond = pSecond->m_strName;

	oList.RemoveAll();
}

void CSttItemBase::GetAllItemsByItemsType(CExBaseList &oList)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != STTGBXMLCLASSID_CSTTITEMS)
		{
			continue;
		}

		CSttItems *pItems = (CSttItems *)pObj;

		if (pItems->m_nSelect != 1)
		{
			continue;
		}

		if (pItems->IsTypeRootNode())
		{
			oList.AddTail(pItems);
			continue;
		}

		pItems->GetAllItemsByItemsType(oList);
	}
}

BOOL CSttItemBase::IsChildItemExist(CSttItemBase *pChildItem)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	BOOL bRet = FALSE;

	while (pos != NULL)
	{
		pObj = GetNext(pos);

		if (! stt_gb_is_a_itembase(pObj))
		{
			continue;
		}

		CSttItemBase *pItem = (CSttItemBase *)pObj;

		if (pItem == pChildItem)
		{
			bRet = TRUE;
			break;
		}

		bRet = pItem->IsChildItemExist(pChildItem);

		if (bRet)
		{
			break;
		}
	}

	return bRet;
}

//shaolei 20221020
CSttItemBase* CSttItemBase::GetPrevItem(CSttItemBase *pCurrItem)
{
	POS pos = Find(pCurrItem);
	GetPrev(pos);
	CSttItemBase *pFind = NULL;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetPrev(pos);

		if (stt_gb_is_a_itembase(pObj))
		{
			pFind = (CSttItemBase *)pObj;
			break;
		}
	}

	return pFind;
}

CSttItemBase* CSttItemBase::GetNextItem(CSttItemBase *pCurrItem)
{
	POS pos = Find(pCurrItem);
	GetNext(pos);
	CSttItemBase *pFind = NULL;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);

		if (stt_gb_is_a_itembase(pObj))
		{
			pFind = (CSttItemBase *)pObj;
			break;
		}
	}

	return pFind;
}

void CSttItemBase::UpdateParentState()
{
	CBaseObject *pParent = GetParent();
	while (pParent != NULL)
	{
		CSttItemBase *pItems = (CSttItemBase *)pParent;
		switch(m_nState)
		{
		case TEST_STATE_INLEGIBLE:
			pItems->m_nState = TEST_STATE_INLEGIBLE;
			break;
		case TEST_STATE_STOPED:
			pItems->m_nState = TEST_STATE_STOPED;
			break;
		case TEST_STATE_TESTING:
			if (pItems->m_nState != TEST_STATE_INLEGIBLE)
			{
				pItems->m_nState = TEST_STATE_TESTING;
			}
			break;
		case TEST_STATE_ELIGIBLE:
			if (pItems->m_nState == TEST_STATE_INLEGIBLE)
			{
				//break;
				//��ǰ��Ŀ�Ǻϸ񣬸���Ŀ״̬ˢ��ǰ���ǲ��ϸ����жϸø���Ŀ�£��Ƿ���������Ŀ���Ǻϸ�̬��
				//���ǣ�����Ŀˢ��Ϊ�ϸ�̬��������Ŀ��ˢ��
				if (Stt_Stt_IsAllChildItemTestELIGIBLE(pItems))
				{
					pItems->m_nState = TEST_STATE_ELIGIBLE;
				}
				else
				{
					break;
				}
			}

			long nState = Stt_IsItemsTestFinished(pItems);
			if (nState == 1)
			{
				pItems->m_nState = TEST_STATE_ELIGIBLE;
			}
			else if(nState == 2)
			{
				pItems->m_nState = TEST_STATE_TESTING;
			}
			else
			{
				pItems->m_nState = TEST_STATE_NORMAL;
			}
			break;
		}
		pParent = pParent->GetParent();
	}
}

void CSttItemBase::GetAllItemsByID(const CString &strItemID, CExBaseList &oItemList)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if ( nClassID == STTGBXMLCLASSID_CSTTSAFETY || nClassID == STTGBXMLCLASSID_CSTTMACROTEST
			|| nClassID == STTGBXMLCLASSID_CSTTCOMMCMD || nClassID == STTGBXMLCLASSID_CSTTSYSPARAEDIT )
		{
			if (p->m_strID == strItemID)
			{
				oItemList.AddTail(p);
			}	
		}

		if (nClassID == STTGBXMLCLASSID_CSTTITEMS)
		{
			CSttItems *pItems = (CSttItems *)p;

			pItems->GetAllItemsByID(strItemID, oItemList);
		}
	}
}

//���Խ���������1�����ڲ��Է���2��δ��ʼ������0������ֹͣ������3
long CSttItemBase::IsTestFinish()
{
	//���û��ѡ������Ϊ�����״̬
	if (m_nSelect == 0)
	{
		return 1;
	}

	if (m_nEnable == 0 || m_nShow == 0)
	{
		return 1;
	}

	//���Ժϸ񡢲��ϸ񡢲��Ժϸ���չ������Ϊ�����״̬
	if ((m_nState == TEST_STATE_INLEGIBLE) || (m_nState == TEST_STATE_ELIGIBLEEX)
		|| (m_nState == TEST_STATE_ELIGIBLE))
	{
		return 1;
	}
	else if(m_nState == TEST_STATE_TESTING)
	{
		return 2;
	}
	else if (m_nState == TEST_STATE_NORMAL)
	{
		return 0;
	}
	else if (m_nState == TEST_STATE_STOPED)
	{
		return 3;
	}

	return 0;
}

CSttReportMap* CSttItemBase::GetReportMap(BOOL bCreate)
{
	if (m_pSttReportMap != NULL)
	{
		return m_pSttReportMap;
	}

	if (bCreate)
	{
		m_pSttReportMap = new CSttReportMap();
		AddNewChild(m_pSttReportMap);
	}

	return m_pSttReportMap;
}

long CSttItemBase::GetReportsCount()
{
	if (m_pSttReports == NULL)
	{
		return 0;
	}

	return m_pSttReports->GetCount();
}

CSttItemRsltExpr* CSttItemBase::GetRsltExpr()
{
	if (m_pRsltExpr == NULL)
	{
		m_pRsltExpr = new CSttItemRsltExpr();
		AddNewChild(m_pRsltExpr);
	}

	return m_pRsltExpr;
}

#include "SttDevice.h"
void CSttItemBase::GetRsltExprValues(CExBaseList *pRlstExprValues, CExBaseList *pReportValues, CExBaseList *pListXExprValues)
{
	if (m_pRsltExpr == NULL)
	{
		return;
	}

	CSttDevice *pDevice = (CSttDevice*)GetAncestor(STTGBXMLCLASSID_CSTTDEVICE);

	m_pRsltExpr->GetRsltExprValues(this, pReportValues, pDevice, pRlstExprValues, pListXExprValues);
}

//������Ŀ�����·�������Ҷ�Ӧ����Ŀ
long CSttItemBase::SelectItems(const CString &strPath, CExBaseList &oListDest)
{
	//2020-12-21 shaolei
	if (strPath.GetLength() == 0)
	{//·��Ϊ�� ��ǰ�ڵ��������
		oListDest.AddTail(this);
		return 0;
	}

	UINT nClassID = GetClassID();
	BOOL bIsItems = (nClassID == STTGBXMLCLASSID_CSTTITEMBASE);
	CString strPathLeft, strPathRight;
	CSttItemBase* pTemp;

	//��ת�����ڵ� �ų�·���еľ���·��
	int nSepPos = strPath.ReverseFind('/');

	if (nSepPos != -1)
	{
		pTemp = (CSttItemBase*)GetRoot();
		return pTemp == NULL ? -1 : pTemp->SelectItems(strPath.Mid(nSepPos+1), oListDest);
	}

	if (strPath[0] == '\\')
	{	//·����ʼ����'\'����Ϊ�ָ����� �ڴ˴�������Щ����
		int i = 1;
		for (i = 1;strPath[i] == '\\'; i++);
		return SelectItems(strPath.Mid(i), oListDest);
	}

	nSepPos = strPath.Find('\\');		//Ѱ�ҵ�һ��'\'���ţ���·����Ϊ������ ��ΪҪ��ת���Ľڵ� �Ҳ�Ϊ���ݸ���һ�ڵ�Ĳ���

	if (nSepPos == -1)
	{
		strPathLeft = strPath;
		strPathRight = "";
	}
	else
	{
		strPathLeft = strPath.Left(nSepPos);
		strPathRight = strPath.Mid(nSepPos+1);
	}

	if (strPathLeft == ".")			//ѡ��ǰ�ڵ� ��������
	{
		SelectItems(strPathRight, oListDest);
	} 
	else if (strPathLeft == "..")	//ѡ�и��ڵ� ��������
	{
		pTemp = (CSttItemBase*)GetParent();//parentһ����CExBaseList����
		pTemp == NULL ? -1 : pTemp->SelectItems(strPathRight, oListDest);
	}
	else if (strPathLeft == "?")	//ƥ��һ������·��
	{
		if (bIsItems)	
		{//BaseObject �������ӽڵ�
			SelectChildrenItems(strPathRight, oListDest);
		}
	}
	else if (strPathLeft == "*")	//ƥ�����⼶��������·��
	{
		SelectItems(strPathRight, oListDest);//��"*"ƥ��Ϊ��(�㼶)

		if ( bIsItems)	//BaseObject �������ӽڵ�
		{
			//SelectChildrenItems(strPathRight, oListDest);
			SelectChildrenItems(strPath, oListDest);
		}
	}
	else
	{
		SelectItemsLeft_Var(strPath, strPathLeft, strPathRight, oListDest);
	}

	return 0;
}

//�������ͣ����ҵ�һ��CSttItems��Ŀ
CSttItemBase* CSttItemBase::FindFirstItems(const CString &strType, BOOL bCheckType)
{
	CSttItems* pFind = NULL;
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID != STTGBXMLCLASSID_CSTTITEMS)
		{
			continue;
		}

		CSttItems* pSttItems = (CSttItems *)p;

		if (pSttItems->m_nSelect == 0)
		{
			continue;
		}

		if (!bCheckType)
		{
			pFind = pSttItems;
			break;
		}

		if (pSttItems->m_strType == strType)
		{
			pFind = pSttItems;
			break;
		}

		pFind = (CSttItems*)pSttItems->FindFirstItems(strType, bCheckType);

		if (pFind != NULL)
		{
			return pFind;
		}
	}

	return pFind;
}

void CSttItemBase::SetState(long nState)
{
	m_nState = nState;
}

void CSttItemBase::ClearReport()
{
	if (m_pSttReports == NULL)
	{
		return;
	}

	CSttReport *pInitReport = (CSttReport *)m_pSttReports->FindByID(_T("_Init_"));

	if (pInitReport != NULL)
	{
		m_pSttReports->Remove(pInitReport);
	}

	m_pSttReports->DeleteAll();

	if (pInitReport != NULL)
	{
		m_pSttReports->AddNewChild(pInitReport);
	}
}

void CSttItemBase::DeleteChildItem_Commcmd(BOOL bRecursion)
{
	POS pos = GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == STTGBXMLCLASSID_CSTTCOMMCMD)
		{
			Delete(pObj);
		}
		else if (nClassID == STTGBXMLCLASSID_CSTTITEMS)
		{
			if (! bRecursion)
			{
				continue;
			}

			CSttItems* pItems = (CSttItems *)pObj;
			pItems->DeleteChildItem_Commcmd();
		}
		else if (nClassID == STTGBXMLCLASSID_CSTTMACROTEST)
		{
			if (! bRecursion)
			{
				continue;
			}

			CSttMacroTest *pMacroTest = (CSttMacroTest *)pObj;
			pMacroTest->DeleteChildItem_Commcmd();
		}
		else if (nClassID == STTGBXMLCLASSID_CSTTSAFETY)
		{
			if (! bRecursion)
			{
				continue;
			}

			CSttSafety *pSafety = (CSttSafety *)pObj;
			pSafety->DeleteChildItem_Commcmd();
		}
		else if (nClassID == STTGBXMLCLASSID_CSTTSYSPARAEDIT)
		{
			if (! bRecursion)
			{
				continue;
			}

			CSttSysParaEdit *pSysParaEdit = (CSttSysParaEdit *)pObj;
			pSysParaEdit->DeleteChildItem_Commcmd();
		}
	}
}

long CSttItemBase::SelectItemsLeft_Var(const CString &strPath, const CString &strPathLeft, const CString &strPathRight, CExBaseList &oListDest)
{
	BOOL bIsBaseObject = IsBaseObject();

	if (bIsBaseObject)	//BaseObject �������ӽڵ�
	{
		if (strPathRight == "")
		{
			if (strPath == m_strID)
			{
				oListDest.AddTail(this);
			}
		}

		return 0;
	}
	else
	{
		CSttItemBase *pObj = NULL;

		if (strPathRight == "")
		{
			// 			if (strPath == m_strID)
			// 			{
			// 				oListDest.AddTail(this);
			// 			}

			pObj =(CSttItemBase*) ( ((CSttItems*)this)->FindByID(strPathLeft) );

			if (pObj != NULL)
			{
				oListDest.AddTail(pObj);
			}
		}
		else
		{
			pObj = (CSttItemBase*) ( ((CSttItems*)this)->FindByID(strPathLeft) );

			if (pObj == NULL)
			{
				return -1;
			}
			else
			{
				pObj->SelectItems(strPathRight, oListDest);
			}
		}
	}

	return 0;
}

//���Խ���������1�����ڲ��Է���2��δ��ʼ������0
long Stt_IsItemsTestFinished(CExBaseList *pList)
{
	UINT nClassID = 0;
	nClassID = pList->GetClassID();
	long nState = 1;

	if (nClassID == STTGBXMLCLASSID_CSTTITEMS)
	{
		CSttItems *pItems = (CSttItems*)pList;

		if (pItems->m_nEnable == 0 || pItems->m_nSelect == 0)
		{
			return 1;
		}
	}

	if(Stt_IsGbItemClassID(nClassID))
	{
		return ((CSttItemBase*)pList)->IsTestFinish();
	}

	if (Stt_IsItemsBaseClassID(nClassID))
	{
		POS pos = pList->GetHeadPosition();
		CExBaseObject *p = NULL;

		while (pos != NULL)
		{
			p = pList->GetNext(pos);
			nState = Stt_IsItemsTestFinished((CExBaseList*)p);

			if (nState == 2 || nState == 0 || nState == 3)
			{
				break;
			}
		}
	}

	return nState;
}

//�жϸ���Ŀ�£��Ƿ���������Ŀ�����Ժϸ�
BOOL Stt_Stt_IsAllChildItemTestELIGIBLE(CExBaseList *pList)
{
	UINT nClassID = 0;
	nClassID = pList->GetClassID();

	if (nClassID == STTGBXMLCLASSID_CSTTITEMS)
	{
		CSttItems *pItems = (CSttItems*)pList;

		if (pItems->m_nEnable == 0 || pItems->m_nSelect == 0)
		{
			return TRUE;
		}
	}

	if(Stt_IsGbItemClassID(nClassID))
	{
		CSttItemBase *pItemBase = (CSttItemBase *)pList;
		
		if (pItemBase->m_nState == TEST_STATE_ELIGIBLE
			|| pItemBase->m_nState == TEST_STATE_ELIGIBLEEX)
		{
			return TRUE;
		}
		else if (pItemBase->m_nState == TEST_STATE_NORMAL)
		{
			//δ���Եģ���ʱ��Ϊ�Ǻϸ��
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	BOOL bRet = TRUE;

	if (Stt_IsItemsBaseClassID(nClassID))
	{
		POS pos = pList->GetHeadPosition();
		CExBaseObject *p = NULL;

		while (pos != NULL)
		{
			p = pList->GetNext(pos);
			bRet = Stt_Stt_IsAllChildItemTestELIGIBLE((CExBaseList*)p);

			if (!bRet)
			{
				break;
			}
		}
	}

	return bRet;
}

BOOL Stt_IsGbItemClassID(UINT nClassID)
{
	if (nClassID == STTGBXMLCLASSID_CSTTSAFETY || nClassID == STTGBXMLCLASSID_CSTTMACROTEST
		|| nClassID == STTGBXMLCLASSID_CSTTCOMMCMD || nClassID == STTGBXMLCLASSID_CSTTSYSPARAEDIT
		|| nClassID == STTGBXMLCLASSID_CSTTMACROCHARITEMS)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//���п��Բ��Ե�����Ŀ��  ����TRUE
BOOL Stt_IsItemsBaseClassID(UINT nClassID)
{
	if (nClassID == STTGBXMLCLASSID_CSTTSAFETY || nClassID == STTGBXMLCLASSID_CSTTMACROTEST
		|| nClassID == STTGBXMLCLASSID_CSTTITEMS || nClassID == STTGBXMLCLASSID_CSTTSYSPARAEDIT
		|| nClassID == STTGBXMLCLASSID_CSTTDEVICE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

CSttItems* Stt_GetFirstParentItems(CExBaseObject *pObj, const CString &strType, BOOL bType)
{
	UINT nClassID = 0;
	CBaseObject *pParent = NULL;
	CSttItems *pItem = NULL;

	if (pObj == NULL)
	{
		return NULL;
	}

	pParent = pObj;

	while (pParent != NULL)
	{
		nClassID = pParent->GetClassID();

		if (nClassID == STTGBXMLCLASSID_CSTTDEVICE)
		{
			break;
		}

		if (STTGBXMLCLASSID_CSTTITEMS == nClassID)
		{
			pItem = (CSttItems*)pParent;

			if (bType)
			{
				if (pItem->m_strType != strType)
				{
					pParent = pParent->GetParent();
					pItem = NULL;
					continue;
				}
			}

			break;
		}
		else
		{
			pParent = pParent->GetParent();
		}
	}

	return pItem;
}

//��ձ�������
void Stt_EmptyReportDatas(CExBaseList *pList, BOOL bOnlySelect)
{
	CSttItemBase *pItemList = (CSttItemBase *)pList;
	pItemList->CSttItemBase::ClearReport();
	pItemList->CSttItemBase::SetState(TEST_STATE_NORMAL);

	POS pos = pList->GetHeadPosition();
	CExBaseObject *pItem = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pItem = pList->GetNext(pos);
		nClassID = pItem->GetClassID();

		if (nClassID == STTGBXMLCLASSID_CSTTITEMS)
		{
			CSttItems *pItems = (CSttItems*)pItem;

			if (bOnlySelect)
			{
				if (pItems->m_nSelect == 0)
				{
					continue;
				}
			}

			pItems->ClearReport();
			pItems->SetState(TEST_STATE_NORMAL);
			Stt_EmptyReportDatas(pItems, bOnlySelect);
		}
		else if (nClassID == STTGBXMLCLASSID_CSTTMACROTEST)
		{
			CSttMacroTest *pMacroTest = (CSttMacroTest *)pItem;

			if (bOnlySelect)
			{
				if (pMacroTest->m_nSelect == 0)
				{
					continue;
				}
			}

			pMacroTest->ClearReport();
			pMacroTest->SetState(TEST_STATE_NORMAL);
			Stt_EmptyReportDatas(pMacroTest, bOnlySelect);
		}
		else if (nClassID == STTGBXMLCLASSID_CSTTMACROCHARITEMS)
		{
			CSttMacroCharItems *pMacroCharItems = (CSttMacroCharItems *)pItem;

			if (bOnlySelect)
			{
				if (pMacroCharItems->m_nSelect == 0)
				{
					continue;
				}
			}

			pMacroCharItems->ClearReport();
			pMacroCharItems->SetState(TEST_STATE_NORMAL);
			Stt_EmptyReportDatas(pMacroCharItems, bOnlySelect);
		}
		else if (nClassID == STTGBXMLCLASSID_CSTTSAFETY)
		{
			CSttSafety *pSafety = (CSttSafety *)pItem;

			if (bOnlySelect)
			{
				if (pSafety->m_nSelect == 0)
				{
					continue;
				}
			}

			pSafety->ClearReport();
			pSafety->SetState(TEST_STATE_NORMAL);
			Stt_EmptyReportDatas(pSafety, bOnlySelect);
		}
		else if (nClassID == STTGBXMLCLASSID_CSTTSYSPARAEDIT)
		{
			CSttSysParaEdit *pSysParaEdit = (CSttSysParaEdit *)pItem;

			if (bOnlySelect)
			{
				if (pSysParaEdit->m_nSelect == 0)
				{
					continue;
				}
			}

			pSysParaEdit->ClearReport();
			pSysParaEdit->SetState(TEST_STATE_NORMAL);
			Stt_EmptyReportDatas(pSysParaEdit, bOnlySelect);
		}
		else if ((nClassID & STTGBXMLCLASSID_CSTTITEMBASE) == STTGBXMLCLASSID_CSTTITEMBASE)
		{
			CSttItemBase *pItemBase = (CSttItemBase*)pItem;

			if (bOnlySelect)
			{
				if (pItemBase->m_nSelect == 0)
				{
					continue;
				}
			}

			pItemBase->ClearReport();
			pItemBase->SetState(TEST_STATE_NORMAL);
		}
	}
}

BOOL stt_IsItemsAin(const CString &strItemsID)
{
	if (strItemsID == _T("AccuracyTest")
		|| strItemsID == _T("PowerAccuracyTest")
		|| strItemsID == _T("FreqPFTest")
		|| strItemsID == _T("FreqCurrTest")
		|| strItemsID == _T("SupplyVolHeatTest")
		|| strItemsID == _T("HarmChangeTest")
		|| strItemsID == _T("PFOverTest")
		|| strItemsID == _T("PowerVolCurrTest"))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL stt_IsItemAin(CExBaseObject *pItemBase)
{
	UINT nClassID = pItemBase->GetClassID();

	if (nClassID != STTGBXMLCLASSID_CSTTITEMS)
	{
		return FALSE;
	}

	CSttItems *pItems = (CSttItems *)pItemBase;

	return stt_IsItemsAin(pItems->m_strstxmlFile);
}

BOOL stt_IsItemHasAin(CSttItemBase *pItemBase)
{
	if (stt_IsItemAin(pItemBase))
	{
		return TRUE;
	}

	POS pos = pItemBase->GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = pItemBase->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (!Stt_IsItemsBaseClassID(nClassID))
		{
			continue;
		}

		CSttItemBase *pItemBase = (CSttItemBase *)pObj;

		if (stt_IsItemHasAin(pItemBase))
		{
			return TRUE;
		}
	}

	return FALSE;
}