// RtAllocBuffer.cpp: implementation of the CRtAllocBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtAllocBuffer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//关键字属性
const char* CRtAttrBuffer::g_pszKeyAttrBuffer   = "attr";
const char* CRtAttrBuffer::g_pszKeyBufferID     = "buf-id";
const char* CRtAttrBuffer::g_pszKeyAttrID       = "attr-id";

CRtAttrBuffer::CRtAttrBuffer()
{

}

CRtAttrBuffer::~CRtAttrBuffer()
{

}
// 
// long CRtAttrBuffer::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)	
// {
// 	xml_GetAttibuteValue(g_pszKeyBufferID,  oNode, m_strBufferID);
// 	xml_GetAttibuteValue(g_pszKeyAttrID,  oNode, m_strAttrID);
// 
// 	m_strName = m_strID = m_strBufferID;
// 	return 0;
// }
// 
// long CRtAttrBuffer::WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement)
// {
// 	return 0;
// }
// 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// const char *CRtAllocBuffer::g_pszKeyAllocBuffer     = "alloc-buffer";
// const char *CRtAllocBuffer::g_pszKeyRecordBufferID  = "record-buf-id";
// const char *CRtAllocBuffer::g_pszKeyRecordBufferUse = "record-buf-use";
// const char *CRtAllocBuffer::g_pszKeySpyBufferID     = "spy-buf-id";
// const char *CRtAllocBuffer::g_pszKeySpyBufferUse    = "spy-buf-use";

CRtAllocBuffer::CRtAllocBuffer()
{
	m_nRecordBufferUse = 0;
	m_nSpyBufferUse    = 0;

	m_strName = "RtAllocBuffer";
	m_strID = m_strName;
}

CRtAllocBuffer::~CRtAllocBuffer()
{

}
// 
// //重载的方法
// long CRtAllocBuffer::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
// {
// 	xml_GetAttibuteValue(g_pszKeyRecordBufferID,  oNode, m_strRecordBufferID);
// 	xml_GetAttibuteValue(g_pszKeyRecordBufferUse, oNode, m_nRecordBufferUse);
// 	xml_GetAttibuteValue(g_pszKeySpyBufferID,  oNode, m_strSpyBufferID);
// 	xml_GetAttibuteValue(g_pszKeySpyBufferUse, oNode, m_nSpyBufferUse);
// 	
// 	return 0;
// }
// 
// CExBaseObject* CRtAllocBuffer::CreateNewChild(LPCTSTR pszClassID)
// {
// 	CRtAttrBuffer *pNew = NULL;
// 	
// 	if (strcmp(CRtAttrBuffer::g_pszKeyAttrBuffer, pszClassID) ==0) 
// 	{
// 		pNew  = new CRtAttrBuffer();
// 	}
// 
// 	return pNew;
// }
// 
// const char* CRtAllocBuffer::GetXmlElementKey()
// {
// 	return g_pszKeyAllocBuffer;
// }
// 
// long CRtAllocBuffer::WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement)
// {
// 	
// 	return 0;
// }
// 
// //树形控件相关的操作
// void CRtAllocBuffer::InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, BOOL bParentExpand, HTREEITEM hAfter)
// {
// 	CString strTemp;
// 	m_hTreeItem = pTreeCtrl->InsertItem(m_strName, 0, 0, htiParent, hAfter);
// 	pTreeCtrl->SetItemData(m_hTreeItem,(DWORD)this);
// 
// 	if (m_nRecordBufferUse)
// 	{
// 		strTemp.Format("RecordBuffer:  %s", m_strRecordBufferID);
// 		pTreeCtrl->InsertItem(strTemp, 0, 0, m_hTreeItem);
// 	}
// 	
// 	if (m_nSpyBufferUse)
// 	{
// 		strTemp.Format("SpyBuffer:  %s", m_strSpyBufferID);
// 		pTreeCtrl->InsertItem(strTemp, 0, 0, m_hTreeItem);
// 	}
// 	
// 	if (GetCount() > 0)
// 	{
// 		HTREEITEM hItem = pTreeCtrl->InsertItem("Attr Buffers", 0, 0, m_hTreeItem);
// 		InsertChildrenTreeCtrl(pTreeCtrl, hItem, bParentExpand);
// 	}
// }


