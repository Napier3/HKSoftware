//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TtmgStation.cpp  CTtmgStation


#include "stdafx.h"
#include "TtmgStation.h"

#include "TestTasksMngrGenerate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CTtmgStation::CTtmgStation()
{
	//初始化属性

	//初始化成员变量
}

CTtmgStation::~CTtmgStation()
{
}

long CTtmgStation::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CTtmgStation::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CTtmgStation::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CTtmgStation::InitAfterRead()
{
}

BOOL CTtmgStation::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTtmgStation *p = (CTtmgStation*)pObj;

	return TRUE;
}

BOOL CTtmgStation::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CTtmgStation *p = (CTtmgStation*)pDest;

	return TRUE;
}

CBaseObject* CTtmgStation::Clone()
{
	CTtmgStation *p = new CTtmgStation();
	Copy(p);
	return p;
}

CTtmgStation* TTMG_FindStation(const CString &strStation)
{
	CTestTasksMngrGenerate *pGenerate = CTestTasksMngrGenerate::GetTestTasksMngrGenerate();
	return (CTtmgStation*)pGenerate->m_pStations->FindByName(strStation);
}

