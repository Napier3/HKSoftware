#include "stdafx.h"
#include "PpDeviceNodeDataDefine.h"
#include "PpTagDefineMngr.h"
#include "DeviceModelXmlKeys.h"
#include "PpDeviceNodeDefine.h"

CPpDeviceNodeDefine::CPpDeviceNodeDefine()
{
	m_pTags=NULL;
	m_strMaxOccurs = L"";
	m_strNodeType = L"";
	m_strTemplateFile = L"";
}

CPpDeviceNodeDefine::~CPpDeviceNodeDefine()
{

}

void CPpDeviceNodeDefine::Init()
{
	
}

void CPpDeviceNodeDefine::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		switch (nClassID)
		{
		case DMCLASSID_TAGDEFINEMNGR:
			m_pTags = (CPpTagDefineMngr*)p;
			break;
		default:
			break;
		}
	}

	if (m_pTags == NULL)
	{
		m_pTags = new CPpTagDefineMngr();
		AddNewChild(m_pTags);
	}
}

long CPpDeviceNodeDefine::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(((CDeviceModelXmlKeys*)pXmlRWKeys)->m_strNodeTypeKey,oNode,m_strNodeType);
	xml_GetAttibuteValue(((CDeviceModelXmlKeys*)pXmlRWKeys)->m_strMaxOccursKey,oNode,m_strMaxOccurs);
	xml_GetAttibuteValue(((CDeviceModelXmlKeys*)pXmlRWKeys)->m_strTemplateFileKey,oNode,m_strTemplateFile);

	return 0;
}

long CPpDeviceNodeDefine::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElemen, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElemen,pXmlRWKeys);

	//xml_SetAttributeValue(((CDeviceModelXmlKeys*)pXmlRWKeys)->m_strNodeTypeKey,oXMLDoc,m_strNodeType);
	xml_SetAttributeValue(((CDeviceModelXmlKeys*)pXmlRWKeys)->m_strNodeTypeKey,oElemen,m_strNodeType);
	//xml_SetAttributeValue(((CDeviceModelXmlKeys*)pXmlRWKeys)->m_strMaxOccursKey,oXMLDoc,m_strMaxOccurs);
	xml_SetAttributeValue(((CDeviceModelXmlKeys*)pXmlRWKeys)->m_strMaxOccursKey,oElemen,m_strMaxOccurs);
	xml_SetAttributeValue(((CDeviceModelXmlKeys*)pXmlRWKeys)->m_strTemplateFileKey,oElemen,m_strTemplateFile);

	return 0;

}

CExBaseObject* CPpDeviceNodeDefine::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	if(nClassID==DMCLASSID_DEVICENODEDATADEFINE)
	{
		return new CPpDeviceNodeDataDefine();
	}

	if(nClassID==DMCLASSID_TAGDEFINEMNGR)
	{
		m_pTags = new CPpTagDefineMngr();
		return m_pTags;
	}

	if(nClassID==DMCLASSID_DEVICENODEDEFINE)
	{
		return new CPpDeviceNodeDefine();
	}

	return NULL;
}

CExBaseObject* CPpDeviceNodeDefine::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{

	if(strClassID==CDeviceModelXmlKeys::g_pXmlRWKeys->m_strTagsKey)
	{
		m_pTags = new CPpTagDefineMngr();
		return m_pTags;
	}
	else if(strClassID==CDeviceModelXmlKeys::g_pXmlRWKeys->m_strDeviceNodeDefineKey) 	
	{
		return new CPpDeviceNodeDefine();
	}
	else if(strClassID==CDeviceModelXmlKeys::g_pXmlRWKeys->m_strDeviceNodeDataDefineKey)
	{
		return new CPpDeviceNodeDataDefine();
	}

	return NULL;
}
 
BOOL CPpDeviceNodeDefine::IsEqualOwn(CBaseObject* pObj)
{
	if(!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}
		
	return TRUE;

}

BOOL CPpDeviceNodeDefine::CopyOwn(CBaseObject* pDest)
{
	if (pDest == this)
	{
		return FALSE;
	}


	if(!CExBaseObject::CopyOwn(pDest))
	{
		return FALSE;
	}

	((CPpDeviceNodeDefine*)pDest)->m_strNodeType = m_strNodeType;
	((CPpDeviceNodeDefine*)pDest)->m_strMaxOccurs = m_strMaxOccurs;
	((CPpDeviceNodeDefine*)pDest)->m_strTemplateFile = m_strTemplateFile;


	return TRUE;	
}

CExBaseObject* CPpDeviceNodeDefine::Clone()
{
	CPpDeviceNodeDefine *pDmdvNode= new CPpDeviceNodeDefine;

	if (Copy(pDmdvNode))
	{
		return pDmdvNode;
	}

	return NULL;
}

CPpDeviceNodeDataDefine* CPpDeviceNodeDefine::GetDeviceNodeDataDefine()
{
	CPpDeviceNodeDataDefine *pDataDefine = NULL;
	CExBaseObject *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == DMCLASSID_DEVICENODEDATADEFINE)
		{
			pDataDefine = (CPpDeviceNodeDataDefine*)p;
			break;
		}
	}

	return pDataDefine;
}

CPpDeviceNode *CPpDeviceNodeDefine::CreateDeviceNode()
{
	//创建DeviceNode节点
	CPpDeviceNode *pNewDeviceNode = NULL;
	CExBaseObject *pNewChild = NULL;
	pNewDeviceNode = new CPpDeviceNode();
 	pNewDeviceNode->m_strID = m_strID;
 	pNewDeviceNode->m_strName = m_strID;
	ASSERT(pNewDeviceNode != NULL);

	//遍历PpDeviceNodeDefine子节点，创建PpDeviceNode子节点
	CExBaseObject* pNode = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pNode = GetNext(pos);
		ASSERT(pNode != NULL);
		UINT nClassID = pNode->GetClassID();

		if (DMCLASSID_TAGDEFINEMNGR == nClassID)
		{
			pNewChild = ((CPpTagDefineMngr *)pNode)->CreateTags();
			pNewDeviceNode->m_pTags = (CPpTags*)pNewChild;
			pNewDeviceNode->AddTail(pNewChild);
			pNewChild->SetParent(pNewDeviceNode);
		}
		else if (DMCLASSID_DEVICENODEDEFINE == nClassID)
		{
			pNewChild = ((CPpDeviceNodeDefine *)pNode)->CreateDeviceNode();
			pNewDeviceNode->AddNewChild(pNewChild);
		}
		else if (DMCLASSID_DEVICENODEDATADEFINE == nClassID)
		{
			pNewChild = ((CPpDeviceNodeDataDefine *)pNode)->CreateDeviceNodeData();
			pNewDeviceNode->AddNewChild(pNewChild);
		}
		else
		{

		}
	}

	return pNewDeviceNode;
}