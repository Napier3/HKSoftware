//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeParam.cpp  CEdgeParam


#include "stdafx.h"
#include "EdgeParam.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeParam::CEdgeParam()
{
	//初始化属性

	//初始化成员变量
	m_pEdgeParas = NULL;
}

CEdgeParam::~CEdgeParam()
{
}

long CEdgeParam::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	return CEdgeGroup::XmlReadOwn(oNode,pXmlRWKeys);
}

long CEdgeParam::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	return CEdgeGroup::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
}

long CEdgeParam::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CEdgeParam::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == MNGRCLASSID_CEDGEPARAS)
		{
			m_pEdgeParas = (CEdgeParas*)p;
		}
	}

	if (m_pEdgeParas == NULL)
	{
		m_pEdgeParas = (CEdgeParas*)AddNewChild(new CEdgeParas());
	}

}

BOOL CEdgeParam::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeParam *p = (CEdgeParam*)pObj;

	return TRUE;
}

BOOL CEdgeParam::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeParam *p = (CEdgeParam*)pDest;

	return TRUE;
}

CBaseObject* CEdgeParam::Clone()
{
	CEdgeParam *p = new CEdgeParam();
	Copy(p);
	return p;
}

CBaseObject* CEdgeParam::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeParam *p = new CEdgeParam();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeParam::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CEDGEDATA)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CEDGEPARAS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEdgeParam::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEdgeDataKey)
	{
		pNew = new CEdgeData();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeParasKey)
	{
		pNew = new CEdgeParas();
	}

	return pNew;
}

CExBaseObject* CEdgeParam::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CEDGEDATA)
	{
		pNew = new CEdgeData();
	}
	else if (nClassID == MNGRCLASSID_CEDGEPARAS)
	{
		pNew = new CEdgeParas();
	}

	return pNew;
}
