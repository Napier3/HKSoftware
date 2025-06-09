//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfg2MInData.cpp  IecCfg2MInData


#include "stdafx.h"
#include "IecCfg2MInData.h"

CIecCfg2MInData::CIecCfg2MInData()
{
	//初始化属性
}

CIecCfg2MInData::~CIecCfg2MInData()
{
}

long CIecCfg2MInData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfg2MData::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;
	return 0;
}

long CIecCfg2MInData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfg2MData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BOOL CIecCfg2MInData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfg2MData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfg2MInData *p = (CIecCfg2MInData*)pObj;

	return TRUE;
}

BOOL CIecCfg2MInData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfg2MData::CopyOwn(pDest);
	return TRUE;
}

CBaseObject* CIecCfg2MInData::Clone()
{
	CIecCfg2MInData *p = new CIecCfg2MInData();
	Copy(p);
	return p;
}

CExBaseObject* CIecCfg2MInData::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	return CIecCfg2MData::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
}


void CIecCfg2MInData::InitAfterRead()
{
	CIecCfg2MData::InitAfterRead();
}

void CIecCfg2MInData::GetCommData(CIecCfgDataSmvCommon *pCommon)
{
	CIecCfg2MData::GetCommData(pCommon);
}

void CIecCfg2MInData::InitByCommData(CIecCfgDataSmvCommon *pCommon)
{
	CIecCfg2MData::InitByCommData(pCommon);
}
