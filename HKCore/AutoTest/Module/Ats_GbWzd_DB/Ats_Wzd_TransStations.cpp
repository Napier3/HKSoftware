//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_TransStations.cpp  CAts_Wzd_TransStations


#include "stdafx.h"
#include "Ats_Wzd_TransStations.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_TransStations::CAts_Wzd_TransStations()
{
	//初始化属性

	//初始化成员变量
}

CAts_Wzd_TransStations::~CAts_Wzd_TransStations()
{
}

long CAts_Wzd_TransStations::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_TransStations::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_TransStations::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CAts_Wzd_TransStations::InitAfterRead()
{
}

BOOL CAts_Wzd_TransStations::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAts_Wzd_TransStations *p = (CAts_Wzd_TransStations*)pObj;

	return TRUE;
}

BOOL CAts_Wzd_TransStations::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_Wzd_TransStations *p = (CAts_Wzd_TransStations*)pDest;

	return TRUE;
}

CBaseObject* CAts_Wzd_TransStations::Clone()
{
	CAts_Wzd_TransStations *p = new CAts_Wzd_TransStations();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_TransStations::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_TransStations *p = new CAts_Wzd_TransStations();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CAts_Wzd_TransStations::CanPaste(UINT nClassID)
{
	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_TRANSSTATION)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAts_Wzd_TransStations::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAts_Wzd_TransStationKey)
	{
		pNew = new CAts_Wzd_TransStation();
	}

	return pNew;
}

CExBaseObject* CAts_Wzd_TransStations::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_TRANSSTATION)
	{
		pNew = new CAts_Wzd_TransStation();
	}

	return pNew;
}
CExBaseObject* CAts_Wzd_TransStations::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CAts_Wzd_TransStation();

	return pNew;
}
