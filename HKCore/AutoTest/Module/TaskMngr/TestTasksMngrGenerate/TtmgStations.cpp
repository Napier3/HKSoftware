//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TtmgStations.cpp  CTtmgStations


#include "stdafx.h"
#include "TtmgStations.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CTtmgStations::CTtmgStations()
{
	//初始化属性

	//初始化成员变量
}

CTtmgStations::~CTtmgStations()
{
}

long CTtmgStations::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CTtmgStations::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CTtmgStations::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CTtmgStations::InitAfterRead()
{
}

BOOL CTtmgStations::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CTtmgStations *p = (CTtmgStations*)pObj;

	return TRUE;
}

BOOL CTtmgStations::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTtmgStations *p = (CTtmgStations*)pDest;

	return TRUE;
}

CBaseObject* CTtmgStations::Clone()
{
	CTtmgStations *p = new CTtmgStations();
	Copy(p);
	return p;
}

BOOL CTtmgStations::CanPaste(UINT nClassID)
{
	if (nClassID == TTMGCLASSID_CTTMGSTATION)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CTtmgStations::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCTtmgStationKey)
	{
		pNew = new CTtmgStation();
	}

	return pNew;
}

CExBaseObject* CTtmgStations::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == TTMGCLASSID_CTTMGSTATION)
	{
		pNew = new CTtmgStation();
	}

	return pNew;
}
