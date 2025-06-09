#include "stdafx.h"
#include"PpDeviceNodeDataDefine.h"

CPpDeviceNodeDataDefine::CPpDeviceNodeDataDefine()
{

	m_strName = _T("tdata");
	m_strID = m_strName;

}

CPpDeviceNodeDataDefine::~CPpDeviceNodeDataDefine()
{

}

//基本方法
void CPpDeviceNodeDataDefine::Init()
{

}

void CPpDeviceNodeDataDefine::InitAfterRead()
{
	
}


//串行化
//long CPpDmDvNdData::BinarySerializeOwn(SysTool::IBinarySerialBufferPtr &oBinaryBuff)
//{
//	return 0
//}
long CPpDeviceNodeDataDefine::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNod,CXmlRWKeys *pXmlRWKeys)
{
	CPpTagDefineMngr::XmlReadOwn(oNod,pXmlRWKeys);

	return 0;
}

long CPpDeviceNodeDataDefine::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPpTagDefineMngr::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	return 0;
}
//编辑
BOOL CPpDeviceNodeDataDefine::IsEqualOwn(CBaseObject* pObj)
{
	if(!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	return TRUE;

}

BOOL CPpDeviceNodeDataDefine::CopyOwn(CBaseObject* pDest)
{
	if(!CExBaseObject::CopyOwn(pDest))
	{
		return FALSE;
	}

	return TRUE;

}

CExBaseObject* CPpDeviceNodeDataDefine::Clone()
{
	CPpDeviceNodeDataDefine *pDmDVNData= new CPpDeviceNodeDataDefine;

	if (Copy(pDmDVNData))
	{
		return pDmDVNData;
	}

	return NULL;

}


CExBaseObject* CPpDeviceNodeDataDefine::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CPpTagDefine *pTtag=NULL;

	if(nClassID==DMCLASSID_TAGDEFINE)
	{
		pTtag=new CPpTagDefine();

		return pTtag;
	}

	return pTtag;
}

CExBaseObject* CPpDeviceNodeDataDefine::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CPpTagDefine *pTtag=NULL;

	if(strClassID==CDeviceModelXmlKeys::g_pXmlRWKeys->m_strTagKey)
	{
		pTtag=new CPpTagDefine();
		return pTtag;
	}
	
	return pTtag;
}

CPpDeviceNodeData *CPpDeviceNodeDataDefine::CreateDeviceNodeData()
{
	//创建DeviceNodeData节点
	CPpDeviceNodeData *pNodeData = NULL;
	pNodeData = new CPpDeviceNodeData();
 	pNodeData->m_strID = CDeviceModelXmlKeys::g_pXmlRWKeys->m_strDeviceNodeDataKey;
 	pNodeData->m_strName = pNodeData->m_strID;
	ASSERT(pNodeData != NULL);
	BOOL bAddToTail = TRUE;

	//遍历CPpDeviceNodeDataDefine的子节点，并依次创建CPpDeviceNodeData的子节点
	CPpTagDefine *pTagDefine = NULL;
	CExBaseObject  *pNew = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pTagDefine = (CPpTagDefine *)GetNext(pos);
		ASSERT(pTagDefine != NULL);

		if((pTagDefine != NULL) && (!pTagDefine->m_strID.IsEmpty()))
		{	
			pNew = pNodeData->CreateNewChild(pTagDefine->m_strID, bAddToTail,  CDeviceModelXmlKeys::g_pXmlRWKeys);
			ASSERT(pNew != NULL);
			pNodeData->AddTail(pNew);
			pNew->SetParent(pNodeData);
		}
	}

	CExBaseObject *pParent = (CExBaseObject*)GetAncestor(DMCLASSID_DEVICENODEDEFINE);

	if (pParent != NULL)
	{
		pNodeData->SetAttribute(CDeviceModelXmlKeys::DmDataTag_Name(), pParent->m_strName);
		pNodeData->SetAttribute(CDeviceModelXmlKeys::DmDataTag_ID(), pParent->m_strID);
	}

	return pNodeData;
}