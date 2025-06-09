//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EdgeDatas.cpp  CEdgeDatas


#include "stdafx.h"
#include "EdgeDatas.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeDatas::CEdgeDatas()
{
	//��ʼ������

	//��ʼ����Ա����
}

CEdgeDatas::~CEdgeDatas()
{
}

long CEdgeDatas::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
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

long CEdgeDatas::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
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

long CEdgeDatas::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CEdgeDatas::InitAfterRead()
{
}

BOOL CEdgeDatas::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeDatas *p = (CEdgeDatas*)pObj;

	return TRUE;
}

BOOL CEdgeDatas::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeDatas *p = (CEdgeDatas*)pDest;

	return TRUE;
}

CBaseObject* CEdgeDatas::Clone()
{
	CEdgeDatas *p = new CEdgeDatas();
	Copy(p);
	return p;
}

CBaseObject* CEdgeDatas::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeDatas *p = new CEdgeDatas();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeDatas::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CEDGEDATA)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEdgeDatas::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEdgeDataKey)
	{
		pNew = new CEdgeData();
	}

	return pNew;
}

CExBaseObject* CEdgeDatas::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CEDGEDATA)
	{
		pNew = new CEdgeData();
	}

	return pNew;
}

CEdgeData *CEdgeDatas::AddNewData(const CString &strName,const CString &strID
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