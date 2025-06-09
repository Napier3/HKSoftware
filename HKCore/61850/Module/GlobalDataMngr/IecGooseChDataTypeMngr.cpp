//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecGooseChDataTypeMngr.cpp  CIecGooseChDataTypeMngr


#include "stdafx.h"
#include "IecGooseChDataTypeMngr.h"

CIecGooseChDataTypeMngr::CIecGooseChDataTypeMngr()
{
	//初始化属性
	m_pGooseChType = NULL;
	m_pGooseInCh = NULL;
	m_pGooseOutChSingle = NULL;
	m_pGooseOutChDouble = NULL;

	//初始化成员变量
}

CIecGooseChDataTypeMngr::~CIecGooseChDataTypeMngr()
{
}

long CIecGooseChDataTypeMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDataTypes::XmlReadOwn(oNode, pXmlRWKeys);
	CIecGlobalDataMngrXmlRWKeys *pXmlKeys = (CIecGlobalDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecGooseChDataTypeMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataTypes::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CIecGlobalDataMngrXmlRWKeys *pXmlKeys = (CIecGlobalDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

void CIecGooseChDataTypeMngr::InitAfterRead()
{
// 	m_pGooseChType      = (CDataType*)FindByID(g_strGsChDtID_goose_ch_type);
// 	m_pGooseInCh        = (CDataType*)FindByID(g_strGsChDtID_goose_in_ch);
// 	m_pGooseOutChSingle = (CDataType*)FindByID(g_strGsChDtID_goose_out_ch_single);
// 	m_pGooseOutChDouble = (CDataType*)FindByID(g_strGsChDtID_goose_out_ch_double);

	ASSERT (m_pGooseChType != NULL);
	ASSERT (m_pGooseInCh != NULL);
	ASSERT (m_pGooseOutChSingle != NULL);
	ASSERT (m_pGooseOutChDouble != NULL);
}

BOOL CIecGooseChDataTypeMngr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CDataTypes::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecGooseChDataTypeMngr *p = (CIecGooseChDataTypeMngr*)pObj;

	return TRUE;
}

BOOL CIecGooseChDataTypeMngr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDataTypes::CopyOwn(pDest);

	CIecGooseChDataTypeMngr *p = (CIecGooseChDataTypeMngr*)pDest;

	return TRUE;
}

CBaseObject* CIecGooseChDataTypeMngr::Clone()
{
	CIecGooseChDataTypeMngr *p = new CIecGooseChDataTypeMngr();
	Copy(p);
	return p;
}

