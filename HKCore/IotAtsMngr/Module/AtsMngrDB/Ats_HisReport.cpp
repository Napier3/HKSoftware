//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_HisReport.cpp  CAts_HisReport


#include "stdafx.h"
#include "Ats_HisReport.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_HisReport::CAts_HisReport()
{
	//初始化属性

	//初始化成员变量
}

CAts_HisReport::~CAts_HisReport()
{
}

long CAts_HisReport::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAts_RTReport::XmlReadOwn(oNode, pXmlRWKeys);
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_HisReport::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAts_RTReport::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_HisReport::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CAts_RTReport::SerializeOwn(oBinaryBuffer);
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

void CAts_HisReport::InitAfterRead()
{
}

BOOL CAts_HisReport::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CAts_RTReport::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CAts_HisReport *p = (CAts_HisReport*)pObj;

	return TRUE;
}

BOOL CAts_HisReport::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_RTReport::CopyOwn(pDest);

	CAts_HisReport *p = (CAts_HisReport*)pDest;

	return TRUE;
}

CBaseObject* CAts_HisReport::Clone()
{
	CAts_HisReport *p = new CAts_HisReport();
	Copy(p);
	return p;
}

CBaseObject* CAts_HisReport::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_HisReport *p = new CAts_HisReport();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CAts_HisReport::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CAts_HisReport::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CATSMNGRXmlRWKeys *pXmlKeys = (CATSMNGRXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CAts_HisReport::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

BOOL CAts_HisReport::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
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