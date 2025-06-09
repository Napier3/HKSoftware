#include "StdAfx.h"
#include "PpJumps.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPpJumps::CPpJumps(void)
{
}

CPpJumps::~CPpJumps(void)
{
}

long CPpJumps::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CProtocolXmlRWKeys *pKey = (CProtocolXmlRWKeys*)pXmlRWKeys;


	return 0;
}

long CPpJumps::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CProtocolXmlRWKeys *pKey = (CProtocolXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPpJumps::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}


CExBaseObject* CPpJumps::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPpJumpKey)
	{
		return new CPpJump();
	}

	return NULL;
}

CExBaseObject* CPpJumps::CreateNewChild(long nClassID)
{
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CPpJumps::IsEqualOwn(CBaseObject* pObj)
{
	ASSERT (pObj == NULL);

	if (pObj == NULL)
	{
		return FALSE;
	}

	if (this == pObj)
	{
		return TRUE;
	}

	return CExBaseList::IsEqualOwn(pObj);
}

CBaseObject* CPpJumps::Clone()
{
	CPpJumps* pNew = new CPpJumps();
	Copy(pNew);
	return pNew;
}

BOOL CPpJumps::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	return CExBaseList::CopyOwn(pDest);
}

CPpNode* CPpJumps::RunJumps(CPpPackageDetail *pPkgDetail)
{
	CPpNode *pNode = NULL;
	POS pos = GetHeadPosition();
	CPpJump *pJump = NULL;

	while (pos != NULL)
	{
		pJump = (CPpJump*)GetNext(pos);
		pNode = pJump->RunJump(pPkgDetail);

		if (pNode != NULL)
		{
			break;
		}
	}

	return pNode;
}

