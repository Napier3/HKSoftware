//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_HisDevice.cpp  CAts_HisDevice


#include "stdafx.h"
#include "Ats_HisDevice.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_HisDevice::CAts_HisDevice()
{
	//初始化属性

	//初始化成员变量
}

CAts_HisDevice::~CAts_HisDevice()
{
}

long CAts_HisDevice::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAts_RTDevice::XmlReadOwn(oNode, pXmlRWKeys);
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_HisDevice::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAts_RTDevice::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_HisDevice::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CAts_RTDevice::SerializeOwn(oBinaryBuffer);
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

void CAts_HisDevice::InitAfterRead()
{
}

BOOL CAts_HisDevice::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CAts_RTDevice::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAts_HisDevice *p = (CAts_HisDevice*)pObj;

	return TRUE;
}

BOOL CAts_HisDevice::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_RTDevice::CopyOwn(pDest);

	CAts_HisDevice *p = (CAts_HisDevice*)pDest;

	return TRUE;
}

CBaseObject* CAts_HisDevice::Clone()
{
	CAts_HisDevice *p = new CAts_HisDevice();
	Copy(p);
	return p;
}

CBaseObject* CAts_HisDevice::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_HisDevice *p = new CAts_HisDevice();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CAts_HisDevice::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CAts_HisDevice::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CAts_HisDevice::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

BOOL CAts_HisDevice::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == ATSCLASSID_CATS_HISTASKBATCH)
	{
		m_nIndex_TaskBatch = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == ATSCLASSID_CATS_HISTASK)
	{
		m_nIndex_Task = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

void CAts_HisDevice::ClearPKValue()
{
	m_nIndex_Task = 0;
	m_nIndex_TaskBatch = 0;
	m_nIndex_Device = 0;
}