//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeParas.cpp  CEdgeParas


#include "stdafx.h"
#include "EdgeParas.h"
#include "EdgeGlobalDef.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeParas::CEdgeParas()
{
	//初始化属性

	//初始化成员变量
	m_pEdgeBody = NULL;
	m_pEdgeDirResp = NULL;
	m_pDirRespJson = NULL;
}

CEdgeParas::~CEdgeParas()
{
}

long CEdgeParas::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//CEdgeParaDatas::XmlReadOwn(oNode, pXmlRWKeys);
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	if(oNode.GetXmlRWType() != _JSON_TYPE_)
		return 0;

	CJsonNode *pJsonNode = (CJsonNode *)(&oNode);
	CJSON *pNode = pJsonNode->m_pJsonNode;
	CJSON *pChild = pNode->child;
	CString strValue = _T(""),strID = _T("");

	while(pChild != NULL)
	{
		if (pChild->type == CJSON_Object)
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
		else if (pChild->type == CJSON_Array)
		{
			if(strcmp(pChild->string, "DirResp") == 0)
			{
				m_pDirRespJson = CopyJson(pChild);
			}
		}

		pChild = pChild->next;
	}

	return 0;
}

long CEdgeParas::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeParaDatas::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEdgeParas::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CEdgeParaDatas::SerializeOwn(oBinaryBuffer);
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

void CEdgeParas::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == EDGECMDCLASSID_CEDGEBODY)
		{
			m_pEdgeBody = (CEdgeBody*)p;
		}
		else if (nClassID == EDGECMDCLASSID_CEDGEDIRRESP)
		{
			m_pEdgeDirResp = (CEdgeDirResp*)p;
		}
	}
}

BOOL CEdgeParas::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CEdgeParaDatas::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEdgeParas *p = (CEdgeParas*)pObj;

	return TRUE;
}

BOOL CEdgeParas::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeParaDatas::CopyOwn(pDest);

	CEdgeParas *p = (CEdgeParas*)pDest;

	return TRUE;
}

CBaseObject* CEdgeParas::Clone()
{
	CEdgeParas *p = new CEdgeParas();
	Copy(p);
	return p;
}

CBaseObject* CEdgeParas::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeParas *p = new CEdgeParas();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeParas::CanPaste(UINT nClassID)
{
	if (nClassID == EDGECMDCLASSID_CEDGEBODY)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEdgeParas::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEdgeBodyKey)
	{
		pNew = new CEdgeBody();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeDirRespKey)
	{
		pNew = new CEdgeDirResp();
	}

	return pNew;
}

CExBaseObject* CEdgeParas::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EDGECMDCLASSID_CEDGEBODY)
	{
		pNew = new CEdgeBody();
	}
	else if (nClassID == EDGECMDCLASSID_CEDGEDIRRESP)
	{
		pNew = new CEdgeDirResp();
	}

	return pNew;
}
