//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IotPpProcedure.cpp  CIotPpProcedure


#include "stdafx.h"
#include "IotPpProcedure.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIotPpProcedure::CIotPpProcedure()
{
	//初始化属性

	//初始化成员变量
	m_pIotPpInterface = NULL;
	m_pIotPpNode = NULL;
}

CIotPpProcedure::~CIotPpProcedure()
{
}

long CIotPpProcedure::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIotPpProcedure::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIotPpProcedure::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CIotPpProcedure::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == IOTCLASSID_CIOTPPINTERFACE)
		{
			m_pIotPpInterface = (CIotPpInterface*)p;
		}
		else if (nClassID == IOTCLASSID_CIOTPPNODE)
		{
			m_pIotPpNode = (CIotPpNode*)p;
		}
	}

	if (m_pIotPpInterface == NULL)
	{
		m_pIotPpInterface = (CIotPpInterface*)AddNewChild(new CIotPpInterface());
	}

	if (m_pIotPpNode == NULL)
	{
		m_pIotPpNode = (CIotPpNode*)AddNewChild(new CIotPpNode());
	}

}

BOOL CIotPpProcedure::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIotPpProcedure *p = (CIotPpProcedure*)pObj;

	return TRUE;
}

BOOL CIotPpProcedure::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIotPpProcedure *p = (CIotPpProcedure*)pDest;

	return TRUE;
}

CBaseObject* CIotPpProcedure::Clone()
{
	CIotPpProcedure *p = new CIotPpProcedure();
	Copy(p);
	return p;
}

CBaseObject* CIotPpProcedure::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIotPpProcedure *p = new CIotPpProcedure();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIotPpProcedure::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOTPPINTERFACE)
	{
		return TRUE;
	}

	if (nClassID == IOTCLASSID_CIOTPPNODE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIotPpProcedure::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIotPpInterfaceKey)
	{
		pNew = new CIotPpInterface();
	}
	else if (strClassID == pXmlKeys->m_strCIotPpNodeKey)
	{
		pNew = new CIotPpNode();
	}

	return pNew;
}

CExBaseObject* CIotPpProcedure::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOTPPINTERFACE)
	{
		pNew = new CIotPpInterface();
	}
	else if (nClassID == IOTCLASSID_CIOTPPNODE)
	{
		pNew = new CIotPpNode();
	}

	return pNew;
}

CIotPpNode* CIotPpProcedure::GetRootNode()
{
	return GetIotPpNode();
}

void CIotPpProcedure::UpdateNodeTimers(CDvmDataset *pAttrDataset)
{
	if (m_pIotPpNode == NULL)
	{
		return;
	}

	CIotPpTimers *pTimers = m_pIotPpNode->GetIotPpTimers();
	if (pTimers != NULL)
	{
		pTimers->UpdateTimers(pAttrDataset,m_pIotPpInterface);
	}
}