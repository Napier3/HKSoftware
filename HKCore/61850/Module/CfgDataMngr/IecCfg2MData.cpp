//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfg2MData.cpp  CIecCfg2MData


#include "stdafx.h"
#include "IecCfg2MData.h"

CIecCfg2MData::CIecCfg2MData()
{
	//��ʼ������
}

CIecCfg2MData::~CIecCfg2MData()
{
}

long CIecCfg2MData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfg6044CommonData::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;
	return 0;
}

long CIecCfg2MData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfg6044CommonData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BOOL CIecCfg2MData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfg6044CommonData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfg2MData *p = (CIecCfg2MData*)pObj;

	return TRUE;
}

BOOL CIecCfg2MData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfg6044CommonData::CopyOwn(pDest);
	return TRUE;
}

CBaseObject* CIecCfg2MData::Clone()
{
	CIecCfg2MData *p = new CIecCfg2MData();
	Copy(p);
	return p;
}

CExBaseObject* CIecCfg2MData::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	return CIecCfg6044CommonData::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
}


void CIecCfg2MData::InitAfterRead()
{
	CIecCfg6044CommonData::InitAfterRead();
}

void CIecCfg2MData::GetCommData(CIecCfgDataSmvCommon *pCommon)
{
	CIecCfg6044CommonData::GetCommData(pCommon);
}

void CIecCfg2MData::InitByCommData(CIecCfgDataSmvCommon *pCommon)
{
	CIecCfg6044CommonData::InitByCommData(pCommon);
}
