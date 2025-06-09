//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeDirResp.cpp  CEdgeDirResp


#include "stdafx.h"
#include "EdgeDirResp.h"
#include "EdgeGlobalDef.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeDirResp::CEdgeDirResp()
{
	//初始化属性

	//初始化成员变量
}

CEdgeDirResp::~CEdgeDirResp()
{
}

long CEdgeDirResp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
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
		strID = pChild->string;

		if (pChild->type == CJSON_String)
		{
			strValue = pChild->valuestring;
			AddNewData(strID,strID,EDGE_DATATYPE_STRING,strValue);
		}

		pChild = pChild->next;
	}

	return 0;
}

long CEdgeDirResp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEdgeDirResp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CEdgeDirResp::InitAfterRead()
{
	m_strID = GetXmlElementKey();
}

BOOL CEdgeDirResp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeDirResp *p = (CEdgeDirResp*)pObj;

	return TRUE;
}

BOOL CEdgeDirResp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeDirResp *p = (CEdgeDirResp*)pDest;

	return TRUE;
}

CBaseObject* CEdgeDirResp::Clone()
{
	CEdgeDirResp *p = new CEdgeDirResp();
	Copy(p);
	return p;
}

CBaseObject* CEdgeDirResp::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeDirResp *p = new CEdgeDirResp();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeDirResp::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeDirResp::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeDirResp::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
