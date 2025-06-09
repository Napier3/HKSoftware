#include "stdafx.h"
#include "PpDeviceDefine.h"
#include "DeviceModelXmlKeys.h"

CPpDeviceDefine::CPpDeviceDefine()
{
	m_pTags=NULL;


	m_strName = "DeviceDefine";
	m_strID = m_strName;

}

CPpDeviceDefine::~CPpDeviceDefine()
{

}

void CPpDeviceDefine::Init()
{

}

void CPpDeviceDefine::InitAfterRead()
{
	
}

long CPpDeviceDefine::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);

	return 0;
}

long CPpDeviceDefine::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	return 0;
}

BOOL CPpDeviceDefine::IsEqualOwn(CBaseObject* pObj)
{
	if(!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}
	else if (!IsEqualChildren(pObj))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPpDeviceDefine::CopyOwn(CBaseObject* pDest)
{
	return TRUE;
}
CExBaseObject* CPpDeviceDefine::Clone()
{
	return NULL;
}


CExBaseObject* CPpDeviceDefine::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	if(nClassID==DMCLASSID_TAGDEFINEMNGR)
	{
		m_pTags = new CPpTagDefineMngr();
		return m_pTags;
	}

	if(nClassID==DMCLASSID_DEVICENODEDATADEFINE)
	{
		return new CPpDeviceNodeDataDefine();
	}

	return NULL;
}

CExBaseObject* CPpDeviceDefine::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
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

	return NULL;
}

CPpDevice *CPpDeviceDefine::CreateDevice(const CString &strTemplateFile)
{
	ASSERT(!strTemplateFile.IsEmpty());
	//创建CPpDevice
	CExBaseObject* pNew = NULL;
	CPpDevice *pDevice = NULL;
	pDevice = new CPpDevice();
 	pDevice->m_strName = CDeviceModelXmlKeys::g_pXmlRWKeys->m_strDeviceKey;
 	pDevice->m_strID = CDeviceModelXmlKeys::g_pXmlRWKeys->m_strDeviceKey;
	pDevice->m_strTemplateFile = strTemplateFile;
	ASSERT(pDevice != NULL);

	//遍历DeviceDefine子节点，依次创建PpDevice子节点
	CExBaseObject* pDvNode = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pDvNode = GetNext(pos);
		ASSERT(pDvNode != NULL);
		UINT nClassID = pDvNode->GetClassID();

		if (DMCLASSID_TAGDEFINEMNGR == nClassID)
		{
			pNew = ((CPpTagDefineMngr *)pDvNode)->CreateTags();
			pDevice->m_pTags = (CPpTags*)pNew;
			pDevice->AddTail(pNew);
			pNew->SetParent(pDevice);
		}
		else if (DMCLASSID_DEVICENODEDEFINE == nClassID)
		{
			pNew = ((CPpDeviceNodeDefine *)pDvNode)->CreateDeviceNode();
			pDevice->AddNewChild(pNew);
		}
		else
		{

		}
	}

	return pDevice;
}

CPpDeviceNodeDefine* CPpDeviceDefine::FindNodeDefine(const CString &strNodeDefID)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CPpDeviceNodeDefine *pNodeDefine = NULL;
	CPpDeviceNodeDefine *pFind = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == DMCLASSID_DEVICENODEDEFINE)
		{
			pNodeDefine = (CPpDeviceNodeDefine*)p;

			if (pNodeDefine->m_strID == strNodeDefID)
			{
				pFind = pNodeDefine;
				break;
			}
		}
	}

	return pFind;
}

