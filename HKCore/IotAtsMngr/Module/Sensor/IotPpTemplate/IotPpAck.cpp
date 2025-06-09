//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IotPpAck.cpp  CIotPpAck


#include "stdafx.h"
#include "IotPpAck.h"
#include "../../../../Module/DataMngr/DvmDataset.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIotPpAck::CIotPpAck()
{
	//初始化属性

	//初始化成员变量
	m_pIotPpJumps = NULL;
}

CIotPpAck::~CIotPpAck()
{
}

long CIotPpAck::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strPkg_IdKey, oNode, m_strPkg_Id);
	return 0;
}

long CIotPpAck::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strPkg_IdKey, oElement, m_strPkg_Id);
	return 0;
}

long CIotPpAck::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strPkg_Id);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strPkg_Id);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strPkg_Id);
	}
	return 0;
}

void CIotPpAck::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == IOTCLASSID_CIOTPPJUMPS)
		{
			m_pIotPpJumps = (CIotPpJumps*)p;
		}
	}

	if (m_pIotPpJumps == NULL)
	{
		m_pIotPpJumps = (CIotPpJumps*)AddNewChild(new CIotPpJumps());
	}

}

BOOL CIotPpAck::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIotPpAck *p = (CIotPpAck*)pObj;

	if(m_strPkg_Id != p->m_strPkg_Id)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIotPpAck::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIotPpAck *p = (CIotPpAck*)pDest;

	p->m_strPkg_Id = m_strPkg_Id;
	return TRUE;
}

CBaseObject* CIotPpAck::Clone()
{
	CIotPpAck *p = new CIotPpAck();
	Copy(p);
	return p;
}

CBaseObject* CIotPpAck::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIotPpAck *p = new CIotPpAck();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIotPpAck::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOTPPJUMPS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIotPpAck::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIotPpJumpsKey)
	{
		pNew = new CIotPpJumps();
	}

	return pNew;
}

CExBaseObject* CIotPpAck::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOTPPJUMPS)
	{
		pNew = new CIotPpJumps();
	}

	return pNew;
}

void CIotPpAck::UpdateTimers(CDvmDataset *pAttrDataset,CExBaseList *pInterface)
{
	if (m_pIotPpJumps == NULL)
	{
		return;
	}

	POS pos = m_pIotPpJumps->GetHeadPosition();
	CIotPpJump *pJump = NULL;

	while(pos != NULL)
	{
		pJump = (CIotPpJump *)m_pIotPpJumps->GetNext(pos);

		pJump->UpdateTimers(pAttrDataset,pInterface);
	}
}