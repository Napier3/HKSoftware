//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IotPpJump.cpp  CIotPpJump


#include "stdafx.h"
#include "IotPpJump.h"
#include "IotPpNode.h"
#include "../../../../Module/DataMngr/DvmDataset.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIotPpJump::CIotPpJump()
{
	//初始化属性

	//初始化成员变量
	m_pIotPpNode = NULL;
}

CIotPpJump::~CIotPpJump()
{
}

long CIotPpJump::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strJump_ToKey, oNode, m_strJump_To);
	return 0;
}

long CIotPpJump::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strJump_ToKey, oElement, m_strJump_To);
	return 0;
}

long CIotPpJump::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strJump_To);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strJump_To);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strJump_To);
	}
	return 0;
}

void CIotPpJump::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == IOTCLASSID_CIOTPPNODE)
		{
			m_pIotPpNode = (CIotPpNode*)p;
		}
	}
}

BOOL CIotPpJump::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIotPpJump *p = (CIotPpJump*)pObj;

	if(m_strJump_To != p->m_strJump_To)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIotPpJump::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIotPpJump *p = (CIotPpJump*)pDest;

	p->m_strJump_To = m_strJump_To;
	return TRUE;
}

CBaseObject* CIotPpJump::Clone()
{
	CIotPpJump *p = new CIotPpJump();
	Copy(p);
	return p;
}

CBaseObject* CIotPpJump::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIotPpJump *p = new CIotPpJump();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIotPpJump::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOTPPNODE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIotPpJump::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIotPpNodeKey)
	{
		pNew = new CIotPpNode();
	}

	return pNew;
}

CExBaseObject* CIotPpJump::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOTPPNODE)
	{
		pNew = new CIotPpNode();
	}

	return pNew;
}

void CIotPpJump::UpdateTimers(CDvmDataset *pAttrDataset,CExBaseList *pInterface)
{
	POS pos = GetHeadPosition();
	CIotPpNode *pNode = NULL;

	while(pos != NULL)
	{
		pNode = (CIotPpNode *)GetNext(pos);

		pNode->UpdateTimers(pAttrDataset,pInterface);
	}
}