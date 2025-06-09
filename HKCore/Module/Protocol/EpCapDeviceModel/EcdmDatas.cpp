//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EcdmDatas.cpp  CEcdmDatas


#include "stdafx.h"
#include "EcdmDatas.h"

CEcdmDatas::CEcdmDatas()
{
	//初始化属性
	m_nDataType = 0;

	//初始化成员变量
}

CEcdmDatas::~CEcdmDatas()
{
}

long CEcdmDatas::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapDeviceModelXmlRWKeys *pXmlKeys = (CEpCapDeviceModelXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEcdmDatas::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapDeviceModelXmlRWKeys *pXmlKeys = (CEpCapDeviceModelXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BOOL CEcdmDatas::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEcdmDatas *p = (CEcdmDatas*)pObj;

	return TRUE;
}

BOOL CEcdmDatas::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEcdmDatas *p = (CEcdmDatas*)pDest;

	return TRUE;
}

CBaseObject* CEcdmDatas::Clone()
{
	CEcdmDatas *p = new CEcdmDatas();
	Copy(p);
	return p;
}

BOOL CEcdmDatas::CanPaste(UINT nClassID)
{
	if (nClassID == ECDMCLASSID_CECDMDATA)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEcdmDatas::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpCapDeviceModelXmlRWKeys *pXmlKeys = (CEpCapDeviceModelXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEcdmDataKey)
	{
		pNew = new CEcdmData();
	}

	return pNew;
}

CExBaseObject* CEcdmDatas::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ECDMCLASSID_CECDMDATA)
	{
		pNew = new CEcdmData();
	}

	return pNew;
}

CEcdmData* CEcdmDatas::FindData(long nDataType,long nItemIndex)
{
	POS pos = GetHeadPosition();
	CEcdmData *pData = NULL;
	CEcdmData *pFind = NULL;

	while (pos != NULL)
	{
		pData = (CEcdmData *)GetNext(pos);

		if (pData->FindData(nDataType, nItemIndex))
		{
			pFind = pData;
			break;
		}
	}

	return pFind;
}

void CEcdmDatas::InitOffset(long nYxAddr, long nYcAddr, long nYtAddr)
{
	POS pos = GetHeadPosition();
	CEcdmData *pData = NULL;
	CEcdmData *pFind = NULL;

	while (pos != NULL)
	{
		pData = (CEcdmData *)GetNext(pos);

		pData->InitOffset(nYxAddr, nYcAddr, nYtAddr);
	}
}

CEcdmData* CEcdmDatas::AddNewData(CEcdmData *pSrc, long nInsertAfter)
{
	CEcdmData *pNew = NULL;

	if (pSrc == NULL)
	{
		pNew = new CEcdmData();
	}
	else
	{
		pNew = (CEcdmData*)pSrc->Clone();
	}

	pNew->m_nDataType = m_nDataType;

	if (nInsertAfter < 0 || nInsertAfter >= GetCount())
	{
		AddNewChild(pNew);
	}
	else
	{
		POS pos = FindIndex(nInsertAfter);
		InsertAfter(pos, pNew);
		pNew->SetParent(this);
	}

	return pNew;
}

void CEcdmDatas::GetDatas(CEcdmDatas &oDatas, long nType)
{
	POS pos = GetHeadPosition();
	CEcdmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CEcdmData *)GetNext(pos);

		if (pData->m_nDataType == nType)
		{
			oDatas.AddTail(pData);
		}
	}
}

