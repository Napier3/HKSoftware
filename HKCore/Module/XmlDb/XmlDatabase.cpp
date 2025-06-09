#include "StdAfx.h"
#include "XmlDatabase.h"
#include "XmlDbData.h"

CXmlDatabase::CXmlDatabase(void)
{
}

CXmlDatabase::~CXmlDatabase(void)
{
}

void CXmlDatabase::Init()
{
	//
}

long CXmlDatabase::InitAfterSerialize()
{
	//
	return 0;
}

//串行化
long CXmlDatabase::SerializeOwn(SystemTool::IBinarySerialBufferPtr &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer->IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strUserName);
		BinarySerializeCalLen(oBinaryBuffer, m_strUserID);
	}
	else if (oBinaryBuffer->IsReadMode())
	{	
		BinarySerializeRead(oBinaryBuffer, m_strUserName);
		BinarySerializeRead(oBinaryBuffer, m_strUserID);
	}
	else if (oBinaryBuffer->IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strUserName);
		BinarySerializeWrite(oBinaryBuffer, m_strUserID);
	}

	return 0;
}

long CXmlDatabase::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);

	CXmlDbKeys *pXmlDbKeys = (CXmlDbKeys *)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlDbKeys->m_strUserIDKey, oNode, m_strUserID);
	xml_GetAttibuteValue(pXmlDbKeys->m_strUserNameKey, oNode, m_strUserName);

	return 0;
}

long CXmlDatabase::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElemen, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElemen, pXmlRWKeys);

	CXmlDbKeys *pXmlDbKeys = (CXmlDbKeys *)pXmlRWKeys;

	if (m_strUserID.GetLength() > 0)
	{
		oElemen->setAttribute(_bstr_t(pXmlDbKeys->m_strUserIDKey), _bstr_t(m_strUserID));
	}

	if (m_strUserName.GetLength() > 0)
	{
		oElemen->setAttribute(_bstr_t(pXmlDbKeys->m_strUserNameKey), _bstr_t(m_strUserName));
	}

	return 0;
}

//创建子对象
CExBaseObject* CXmlDatabase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail)
{
	if (strClassID == CXmlDbKeys::g_pXmlDbKeys->m_strDataKey)
	{
		CXmlDbData* pChild = new CXmlDbData();
		return pChild;
	}

	return NULL;
}

CExBaseObject* CXmlDatabase::CreateNewChild(long nClassID)
{
	if (nClassID == CLASSID_XMLDBDATA)
	{
		CXmlDbData* pChild = new CXmlDbData();
		return pChild;
	}

	return NULL;
}

//编辑
BOOL CXmlDatabase::IsEqualOwn(CBaseObject* pObj)
{
	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	ASSERT(pObj->GetClassID() == CLASSID_XMLDBDATA);
	if (m_strUserName != ((CXmlDatabase*)pObj)->m_strUserName)
	{
		return FALSE;
	}

	if (m_strUserID != ((CXmlDatabase*)pObj)->m_strUserID)
	{
		return FALSE;
	}

	if (!IsEqualChildren(pObj))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXmlDatabase::CopyOwn(CBaseObject* pDest)
{
	ASSERT(pDest != NULL);
	ASSERT(pDest->GetClassID() == CLASSID_TXMLDATABASE);

	if(!CExBaseObject::CopyOwn(pDest))
	{
		return FALSE;
	}

	CXmlDatabase *pDb = (CXmlDatabase *)pDest;
	pDb->m_strUserName = m_strUserName;
	pDb->m_strUserID   = m_strUserID;

	if (!CopyChildren(pDest))
	{
		return FALSE;
	}

	return TRUE;
}

CBaseObject* CXmlDatabase::Clone()
{
	CXmlDatabase* pNew = new CXmlDatabase();

	if (Copy(pNew))
	{
		return pNew;
	}

	return NULL;
}

//树形控件相关的操作
void CXmlDatabase::InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent)
{
	m_dwItemData = (DWORD)pTreeCtrl->InsertItem(m_strUserName, 0, 0, htiParent);
	pTreeCtrl->SetItemData((HTREEITEM)m_dwItemData,(DWORD)this);

	InsertChildrenTreeCtrl(pTreeCtrl, (HTREEITEM)m_dwItemData);
}

//文件打开/保存
BOOL CXmlDatabase::OpenXmlDbFile(const CString& strFile)
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

BOOL CXmlDatabase::SaveXmlDbFile(const CString& strFile)
{
	MSXML2::IXMLDOMDocumentPtr docPtr = NULL;
	docPtr.CreateInstance(__uuidof(MSXML2::DOMDocument));

	XmlWrite(docPtr,NULL,CXmlDbKeys::g_pXmlDbKeys);
	docPtr->save((_bstr_t)strFile);

	return TRUE;
}
