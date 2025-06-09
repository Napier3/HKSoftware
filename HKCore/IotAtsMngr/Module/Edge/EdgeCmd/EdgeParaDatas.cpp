//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeParaDatas.cpp  CEdgeParaDatas


#include "stdafx.h"
#include "EdgeParaDatas.h"
#include "EdgeGlobalDef.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeParaDatas::CEdgeParaDatas()
{
	//初始化属性

	//初始化成员变量
}

CEdgeParaDatas::~CEdgeParaDatas()
{
}

long CEdgeParaDatas::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEdgeParaDatas::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;
	
	POS pos = GetHeadPosition();
	while (pos)
	{
		CExBaseObject* pChild = GetNext(pos);
		if(pChild && pChild->GetClassID() == EDGECMDCLASSID_CEDGEPARADATA)
		{
			CEdgeParaData* pData = (CEdgeParaData*)pChild;
			BSTR bstrID = pChild->m_strID.AllocSysString();

			if(pData->m_strDataType == EDGE_DATATYPE_LONG)
			{
				long nTemp =  CString_To_long(((CEdgeParaData*)pChild)->m_strValue);
				xml_SetAttributeValue(bstrID, oElement, nTemp);
			}
			else if (pData->m_strDataType == EDGE_DATATYPE_DOUBLE)
			{
				double dTemp = CString_To_double(((CEdgeParaData*)pChild)->m_strValue);
				xml_SetAttributeValue(bstrID, oElement, dTemp);
			}
			else if (pData->m_strDataType == EDGE_DATATYPE_STRING)
			{
				xml_SetAttributeValue(bstrID, oElement, ((CEdgeParaData*)pChild)->m_strValue);
			}
			else
			{
				xml_SetAttributeValue(bstrID, oElement, ((CEdgeParaData*)pChild)->m_strValue);
			}

			SysFreeString(bstrID);	
		}
	}

	return 0;
}


long CEdgeParaDatas::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		if(pObj && pObj->GetClassID() != EDGECMDCLASSID_CEDGEPARADATA)
		{
			pObj->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
		}
	}

	return 0;
}

long CEdgeParaDatas::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CEdgeParaDatas::InitAfterRead()
{
}

BOOL CEdgeParaDatas::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeParaDatas *p = (CEdgeParaDatas*)pObj;

	return TRUE;
}

BOOL CEdgeParaDatas::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeParaDatas *p = (CEdgeParaDatas*)pDest;

	return TRUE;
}

CBaseObject* CEdgeParaDatas::Clone()
{
	CEdgeParaDatas *p = new CEdgeParaDatas();
	Copy(p);
	return p;
}

CBaseObject* CEdgeParaDatas::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeParaDatas *p = new CEdgeParaDatas();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeParaDatas::CanPaste(UINT nClassID)
{
	if (nClassID == EDGECMDCLASSID_CEDGEPARADATA)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEdgeParaDatas::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEdgeParaDataKey)
	{
		pNew = new CEdgeParaData();
	}

	return pNew;
}

CExBaseObject* CEdgeParaDatas::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EDGECMDCLASSID_CEDGEPARADATA)
	{
		pNew = new CEdgeParaData();
	}

	return pNew;
}

CEdgeParaData* CEdgeParaDatas::AddNewData(const CString &strName,const CString &strID
								  ,const CString &strDataType,const CString &strValue)
{
	CEdgeParaData *pData = new CEdgeParaData;
	pData->m_strName = strName;
	pData->m_strID = strID;
	pData->m_strDataType = strDataType;
	pData->m_strValue = strValue;
	AddNewChild(pData);
	return pData;
}

//该函数仅用于无法解析的array of string类型json对象复制
CJSON* CEdgeParaDatas::CopyJson(CJSON* pSrc)
{
	CJSON* pDst = new CJSON;
	CJSON_CreateObject();
	pDst->child = NULL;
	pDst->next = NULL;
	pDst->prev = NULL;

	CJSON* pChild = pSrc->child;
	while (pChild)
	{
		CJSON* pJson = CJSON_CreateString(pChild->valuestring);
		pJson->type = pChild->type;

		if(!pDst->child)
			pDst->child = pJson;
		else
		{
			CJSON* pTemp = pDst->child;
			while (pTemp->next)
			{
				pTemp = pTemp->next;
			}
			pTemp->next = pJson;
			pJson->prev = pTemp;
		}	
		pChild = pChild->next;
	}

	return pDst;
}