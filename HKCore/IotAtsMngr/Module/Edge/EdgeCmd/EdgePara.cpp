//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgePara.cpp  CEdgePara


#include "stdafx.h"
#include "EdgePara.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgePara::CEdgePara()
{
	//初始化属性

	//初始化成员变量
	m_pEdgeCpuLmt = NULL;
	m_pEdgeMemLmt = NULL;
	m_pEdgeDiskLmt = NULL;
}

CEdgePara::~CEdgePara()
{
}

long CEdgePara::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strContainerKey, oNode, m_strContainer);
	xml_GetAttibuteValue(pXmlKeys->m_strPortKey, oNode, m_strPort);
	return 0;
}

long CEdgePara::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strContainerKey, oElement, m_strContainer);
	xml_SetAttributeValue(pXmlKeys->m_strPortKey, oElement, m_strPort);
	return 0;
}

long CEdgePara::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CEdgePara::InitAfterRead()
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
		else if (nClassID == EDGECMDCLASSID_CEDGEMEMLMT)
		{
			m_pEdgeMemLmt = (CEdgeMemLmt*)p;
		}
		else if (nClassID == EDGECMDCLASSID_CEDGEDISKLMT)
		{
			m_pEdgeDiskLmt = (CEdgeDiskLmt*)p;
		}
	}
}

BOOL CEdgePara::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgePara *p = (CEdgePara*)pObj;

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

BOOL CEdgePara::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgePara *p = (CEdgePara*)pDest;

	p->m_strContainer = m_strContainer;
	p->m_strPort = m_strPort;
	return TRUE;
}

CBaseObject* CEdgePara::Clone()
{
	CEdgePara *p = new CEdgePara();
	Copy(p);
	return p;
}

CBaseObject* CEdgePara::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgePara *p = new CEdgePara();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgePara::CanPaste(UINT nClassID)
{
	if (nClassID == EDGECMDCLASSID_CEDGEMEMLMT)
	{
		return TRUE;
	}

	if (nClassID == EDGECMDCLASSID_CEDGECPULMT)
	{
		return TRUE;
	}

	if (nClassID == EDGECMDCLASSID_CEDGEDISKLMT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEdgePara::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEdgeMemLmtKey)
	{
		pNew = new CEdgeMemLmt();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeCpuLmtKey)
	{
		pNew = new CEdgeCpuLmt();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeDiskLmtKey)
	{
		pNew = new CEdgeDiskLmt();
	}

	return pNew;
}

CExBaseObject* CEdgePara::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EDGECMDCLASSID_CEDGEMEMLMT)
	{
		pNew = new CEdgeMemLmt();
	}
	else if (nClassID == EDGECMDCLASSID_CEDGECPULMT)
	{
		pNew = new CEdgeCpuLmt();
	}
	else if (nClassID == EDGECMDCLASSID_CEDGEDISKLMT)
	{
		pNew = new CEdgeDiskLmt();
	}

	return pNew;
}
