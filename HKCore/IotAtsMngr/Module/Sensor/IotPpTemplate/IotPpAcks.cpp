//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IotPpAcks.cpp  CIotPpAcks


#include "stdafx.h"
#include "IotPpAcks.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIotPpAcks::CIotPpAcks()
{
	//初始化属性

	//初始化成员变量
}

CIotPpAcks::~CIotPpAcks()
{
}

long CIotPpAcks::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIotPpAcks::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIotPpAcks::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
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

void CIotPpAcks::InitAfterRead()
{
}

BOOL CIotPpAcks::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIotPpAcks *p = (CIotPpAcks*)pObj;

	return TRUE;
}

BOOL CIotPpAcks::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIotPpAcks *p = (CIotPpAcks*)pDest;

	return TRUE;
}

CBaseObject* CIotPpAcks::Clone()
{
	CIotPpAcks *p = new CIotPpAcks();
	Copy(p);
	return p;
}

CBaseObject* CIotPpAcks::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIotPpAcks *p = new CIotPpAcks();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIotPpAcks::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOTPPACK)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIotPpAcks::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIotPpAckKey)
	{
		pNew = new CIotPpAck();
	}

	return pNew;
}

CExBaseObject* CIotPpAcks::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOTPPACK)
	{
		pNew = new CIotPpAck();
	}

	return pNew;
}

void CIotPpAcks::UpdateTimers(CDvmDataset *pAttrDataset,CExBaseList *pInterface)
{
	POS pos = GetHeadPosition();
	CIotPpAck *pAck = NULL;

	while(pos != NULL)
	{
		pAck = (CIotPpAck *)GetNext(pos);

		pAck->UpdateTimers(pAttrDataset,pInterface);
	}
}