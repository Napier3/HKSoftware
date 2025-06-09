#include "StdAfx.h"
#include "TXmlDatabase.h"
#include "TXmlDbTable.h"

CTXmlDatabase::CTXmlDatabase(void)
{
}

CTXmlDatabase::~CTXmlDatabase(void)
{
}


void CTXmlDatabase::Init()
{
	//
}

long CTXmlDatabase::InitAfterSerialize()
{
	//
	return 0;
}

//串行化
long CTXmlDatabase::SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer->IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDbName);
		BinarySerializeCalLen(oBinaryBuffer, m_strDbID);
	}
	else if (oBinaryBuffer->IsReadMode())
	{	
		BinarySerializeRead(oBinaryBuffer, m_strDbName);
		BinarySerializeRead(oBinaryBuffer, m_strDbID);
	}
	else if (oBinaryBuffer->IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDbName);
		BinarySerializeWrite(oBinaryBuffer, m_strDbID);
	}
	
	return 0;
}

long CTXmlDatabase::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);

	CXmlDbKeys *pXmlDbKeys = (CXmlDbKeys *)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlDbKeys->m_strDbIDKey, oNode, m_strDbID);
	xml_GetAttibuteValue(pXmlDbKeys->m_strDbNameKey, oNode, m_strDbName);

	return 0;
}

long CTXmlDatabase::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElemen, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElemen, pXmlRWKeys);
	
	CXmlDbKeys *pXmlDbKeys = (CXmlDbKeys *)pXmlRWKeys;

	if (m_strDbID.GetLength() > 0)
	{
		oElemen->setAttribute(_bstr_t(pXmlDbKeys->m_strDbIDKey), _bstr_t(m_strDbID));
	}

	if (m_strDbName.GetLength() > 0)
	{
		oElemen->setAttribute(_bstr_t(pXmlDbKeys->m_strDbNameKey), _bstr_t(m_strDbName));
	}

	return 0;
}

//创建子对象
CExBaseObject* CTXmlDatabase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail)
{												
	if (strClassID == CXmlDbKeys::g_pXmlDbKeys->m_strDbTableKey)
	{
		CTXmlDbTable* pDbTable = new CTXmlDbTable();
		return pDbTable;
	}

	return NULL;
}

CExBaseObject* CTXmlDatabase::CreateNewChild(long nClassID)
{
	if (nClassID == CLASSID_TXMLDBTABLE)
	{
		CTXmlDbTable* pDbTable = new CTXmlDbTable();
		return pDbTable;
	}

	return NULL;
}

//编辑
BOOL CTXmlDatabase::IsEqualOwn(CBaseObject* pObj)
{	
	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	ASSERT(pObj->GetClassID() == CLASSID_TXMLDATABASE);
	if (m_strDbName != ((CTXmlDatabase*)pObj)->m_strDbName)
	{
		return FALSE;
	}

	if (m_strDbID != ((CTXmlDatabase*)pObj)->m_strDbID)
	{
		return FALSE;
	}

	if (!IsEqualChildren(pObj))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTXmlDatabase::CopyOwn(CBaseObject* pDest)
{
	ASSERT(pDest != NULL);
	ASSERT(pDest->GetClassID() == CLASSID_TXMLDATABASE);

	if(!CExBaseObject::CopyOwn(pDest))
	{
		return FALSE;
	}
	
	CTXmlDatabase *pDb = (CTXmlDatabase *)pDest;
	pDb->m_strDbName = m_strDbName;
	pDb->m_strDbID   = m_strDbID;

	if (!CopyChildren(pDest))
	{
		return FALSE;
	}

	return TRUE;
}

CBaseObject* CTXmlDatabase::Clone()
{
	CTXmlDatabase* pNew = new CTXmlDatabase();

	if (Copy(pNew))
	{
		return pNew;
	}

	return NULL;
}

void CTXmlDatabase::InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent)
{
	m_dwItemData = (DWORD)pTreeCtrl->InsertItem(m_strDbName, 0, 0, htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);

	InsertChildrenTreeCtrl(pTreeCtrl, (HTREEITEM)m_dwItemData);
}

BOOL CTXmlDatabase::OpenXmlFile(const CString& strFile)
{
	MSXML2::IXMLDOMDocumentPtr docPtr = NULL;
	docPtr.CreateInstance(__uuidof(MSXML2::DOMDocument));

	_variant_t varXml(strFile);
	_variant_t varOut((bool)TRUE);

	varOut = docPtr->load(varXml);

	if((BOOL)varOut == FALSE)
	{
		AfxMessageBox(L"打开XML文件失败或与XSD文件匹配失败！");		
		return FALSE;
	}

	ASSERT((BOOL)varOut != FALSE);
	MSXML2::IXMLDOMNodePtr oDocRoot = docPtr->GetdocumentElement();
	_bstr_t bstr = L"//";
	bstr += CXmlDbKeys::g_pXmlDbKeys->m_strDbKey;

	MSXML2::IXMLDOMNodePtr oRoot = oDocRoot->selectSingleNode(bstr);
	ASSERT(oRoot != NULL);

	if(oRoot == NULL)
	{
		AfxMessageBox(L"打开XML文件失败！");
		return FALSE;
	}

	XmlRead(oRoot, CXmlDbKeys::g_pXmlDbKeys);

	return TRUE;
}

BOOL CTXmlDatabase::SaveXmlFile(const CString& strFile)
{
	MSXML2::IXMLDOMDocumentPtr docPtr = NULL;
	docPtr.CreateInstance(__uuidof(MSXML2::DOMDocument));

	XmlWrite(docPtr,NULL,CXmlDbKeys::g_pXmlDbKeys);
	docPtr->save((_bstr_t)strFile);

	return TRUE;
}

CTXmlDbTable *CTXmlDatabase::GetTDbTable(const CString &strID)
{
	CTXmlDbTable *pTable = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pTable = (CTXmlDbTable *)GetNext(pos);
		if (pTable != NULL &&  pTable->GetClassID() == CLASSID_TXMLDBTABLE)
		{
			return pTable->GetTDbTable(strID);
		}	
	}

	return NULL;
}