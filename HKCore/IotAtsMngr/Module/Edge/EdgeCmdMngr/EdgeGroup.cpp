//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeGroup.cpp  CEdgeGroup


#include "stdafx.h"
#include "EdgeGroup.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeGroup::CEdgeGroup()
{
	//初始化属性

	//初始化成员变量
}

CEdgeGroup::~CEdgeGroup()
{
}

long CEdgeGroup::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	if(oNode.GetXmlRWType() != _JSON_TYPE_)
		return 0;

	CJsonNode *pJsonNode = (CJsonNode *)(&oNode);
	CJSON *pNode = pJsonNode->m_pJsonNode;
	CJSON *pChild = pNode->child;
	CString strValue = _T(""),strID = _T("");
	
	while(pChild != NULL)
	{
		if ((pChild->type == CJSON_Object) || (pChild->type == CJSON_Array))
		{
			pChild = pChild->next;
			continue;
		}

		strID = pChild->string;

		if (pChild->type == CJSON_False || pChild->type == CJSON_True)
		{
			strValue.Format(_T("%d"),pChild->valueint);
			AddNewData(strID,strID,EDGE_DATATYPE_LONG,strValue);
		}
		else if (pChild->type == CJSON_Number)
		{
			if (pChild->valuedouble - pChild->valueint >= 0.01)
			{
				strValue.Format(_T("%.3f"),pChild->valuedouble);
				AddNewData(strID,strID,EDGE_DATATYPE_DOUBLE,strValue);
			}
			else
			{
				strValue.Format(_T("%d"),pChild->valueint);
				AddNewData(strID,strID,EDGE_DATATYPE_LONG,strValue);
			}
		}
		else if (pChild->type == CJSON_String)
		{
			strValue = pChild->valuestring;
			AddNewData(strID,strID,EDGE_DATATYPE_STRING,strValue);
		}

		pChild = pChild->next;
	}

	return 0;
}

long CEdgeGroup::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	if(oElement.GetXmlRWType() != _JSON_TYPE_)
		return 0;

	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CEdgeData *pData = NULL;

	CXmlRWElement_Json *pElementJson = (CXmlRWElement_Json *)(&oElement);
	CJSON *pNode = pElementJson->m_pJsonNode;

	while(pos != NULL)
	{
		p = GetNext(pos);
		if (p->GetClassID() != MNGRCLASSID_CEDGEDATA)
		{
			continue;
		}

		pData = (CEdgeData *)p;

		if (pData->m_strDataType == EDGE_DATATYPE_STRING)
		{
			CJSON_AddStringToObject(pNode,pData->m_strID,pData->m_strValue);
		}
		else if (pData->m_strDataType == EDGE_DATATYPE_LONG)
		{
			long nValue = CString_To_long(pData->m_strValue);
			CJSON_AddNumberToObject(pNode,pData->m_strID,nValue);
		}
		else if (pData->m_strDataType == EDGE_DATATYPE_DOUBLE)
		{
			double fValue = CString_To_double(pData->m_strValue);
			CJSON_AddNumberToObject(pNode,pData->m_strID,fValue);
		}
	}

	return 0;
}

long CEdgeGroup::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CEdgeGroup::InitAfterRead()
{
}

BOOL CEdgeGroup::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeGroup *p = (CEdgeGroup*)pObj;

	return TRUE;
}

BOOL CEdgeGroup::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeGroup *p = (CEdgeGroup*)pDest;

	return TRUE;
}

CBaseObject* CEdgeGroup::Clone()
{
	CEdgeGroup *p = new CEdgeGroup();
	Copy(p);
	return p;
}

CBaseObject* CEdgeGroup::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeGroup *p = new CEdgeGroup();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeGroup::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CEDGEGROUP)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CEDGEDATA)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEdgeGroup::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEdgeGroupKey)
	{
		pNew = new CEdgeGroup();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeDataKey)
	{
		pNew = new CEdgeData();
	}

	return pNew;
}

CExBaseObject* CEdgeGroup::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CEDGEGROUP)
	{
		pNew = new CEdgeGroup();
	}
	else if (nClassID == MNGRCLASSID_CEDGEDATA)
	{
		pNew = new CEdgeData();
	}

	return pNew;
}

CEdgeData *CEdgeGroup::AddNewData(const CString &strName,const CString &strID
					  ,const CString &strDataType,const CString &strValue)
{
	CEdgeData *pData = new CEdgeData;
	pData->m_strName = strName;
	pData->m_strID = strID;
	pData->m_strDataType = strDataType;
	pData->m_strValue = strValue;
	AddNewChild(pData);
	return pData;
}