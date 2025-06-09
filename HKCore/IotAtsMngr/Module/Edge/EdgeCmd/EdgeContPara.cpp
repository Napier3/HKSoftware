//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeContPara.cpp  CEdgeContPara


#include "stdafx.h"
#include "EdgeContPara.h"
#include "EdgeGlobalDef.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeContPara::CEdgeContPara()
{
	//初始化属性

	//初始化成员变量
	m_pEdgeCpuLmt = NULL;
	m_pEdgeDiskLmt = NULL;
	m_pEdgeMemLmt = NULL;

	m_pMountJson = NULL;
	m_pDevJson = NULL;
}

CEdgeContPara::~CEdgeContPara()
{
}

long CEdgeContPara::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strPortKey, oNode, m_strPort);
	xml_GetAttibuteValue(pXmlKeys->m_strContainerKey, oNode, m_strContainer);

	if(oNode.GetXmlRWType() != _JSON_TYPE_)
		return 0;

	CJsonNode *pJsonNode = (CJsonNode *)(&oNode);
	CJSON *pNode = pJsonNode->m_pJsonNode;
	CJSON *pChild = pNode->child;
	while(pChild != NULL)
	{
		if (pChild->type == CJSON_Array)
		{
			if(strcmp(pChild->string, EDGE_PROCEDURE_VAR_dev) == 0)
			{
				m_pDevJson = CopyJson(pChild);
			}
			else if(strcmp(pChild->string, EDGE_PROCEDURE_VAR_mount) == 0)
			{
				m_pMountJson = CopyJson(pChild);
			}
		}

		pChild = pChild->next;
	}

	return 0;
}

long CEdgeContPara::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strPortKey, oElement, m_strPort);
	xml_SetAttributeValue(pXmlKeys->m_strContainerKey, oElement, m_strContainer);

	return 0;
}

long CEdgeContPara::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strContainer);
		BinarySerializeCalLen(oBinaryBuffer, m_strPort);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strContainer);
		BinarySerializeRead(oBinaryBuffer, m_strPort);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strContainer);
		BinarySerializeWrite(oBinaryBuffer, m_strPort);
	}
	return 0;
}

void CEdgeContPara::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == EDGECMDCLASSID_CEDGECPULMT)
		{
			m_pEdgeCpuLmt = (CEdgeCpuLmt*)p;
		}
		else if (nClassID == EDGECMDCLASSID_CEDGEDISKLMT)
		{
			m_pEdgeDiskLmt = (CEdgeDiskLmt*)p;
		}
		else if (nClassID == EDGECMDCLASSID_CEDGEMEMLMT)
		{
			m_pEdgeMemLmt = (CEdgeMemLmt*)p;
		}
	}

	m_strID = GetXmlElementKey();

	CExBaseList* pPort = new CExBaseList;
	pPort->m_strID = CEdgeCmdMngrXmlRWKeys::PortKey();
	pPort->m_strName = m_strPort;
	AddNewChild(pPort);

	CExBaseList* pContainer = new CExBaseList;
	pContainer->m_strID = CEdgeCmdMngrXmlRWKeys::ContainerKey();
	pContainer->m_strName = m_strContainer;
	AddNewChild(pContainer);
}

BOOL CEdgeContPara::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeContPara *p = (CEdgeContPara*)pObj;

	if(m_strContainer != p->m_strContainer)
	{
		return FALSE;
	}

	if(m_strPort != p->m_strPort)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEdgeContPara::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeContPara *p = (CEdgeContPara*)pDest;

	p->m_strContainer = m_strContainer;
	p->m_strPort = m_strPort;
	return TRUE;
}

CBaseObject* CEdgeContPara::Clone()
{
	CEdgeContPara *p = new CEdgeContPara();
	Copy(p);
	return p;
}

CBaseObject* CEdgeContPara::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeContPara *p = new CEdgeContPara();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeContPara::CanPaste(UINT nClassID)
{
	if (nClassID == EDGECMDCLASSID_CEDGEMEMLMT)
	{
		return TRUE;
	}

	if (nClassID == EDGECMDCLASSID_CEDGEDISKLMT)
	{
		return TRUE;
	}

	if (nClassID == EDGECMDCLASSID_CEDGECPULMT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEdgeContPara::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEdgeMemLmtKey)
	{
		pNew = new CEdgeMemLmt();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeDiskLmtKey)
	{
		pNew = new CEdgeDiskLmt();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeCpuLmtKey)
	{
		pNew = new CEdgeCpuLmt();
	}

	return pNew;
}

CExBaseObject* CEdgeContPara::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EDGECMDCLASSID_CEDGEMEMLMT)
	{
		pNew = new CEdgeMemLmt();
	}
	else if (nClassID == EDGECMDCLASSID_CEDGEDISKLMT)
	{
		pNew = new CEdgeDiskLmt();
	}
	else if (nClassID == EDGECMDCLASSID_CEDGECPULMT)
	{
		pNew = new CEdgeCpuLmt();
	}

	return pNew;
}
