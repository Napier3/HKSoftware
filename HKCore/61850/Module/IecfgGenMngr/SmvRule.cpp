//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmvRule.cpp  CSmvRule


#include "stdafx.h"
#include "SmvRule.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSmvRule::CSmvRule()
{
	//初始化属性

	//初始化成员变量
}

CSmvRule::~CSmvRule()
{
}

long CSmvRule::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSmvRule::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSmvRule::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSmvRule::InitAfterRead()
{
}

BOOL CSmvRule::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSmvRule *p = (CSmvRule*)pObj;

	return TRUE;
}

BOOL CSmvRule::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSmvRule *p = (CSmvRule*)pDest;

	return TRUE;
}

CBaseObject* CSmvRule::Clone()
{
	CSmvRule *p = new CSmvRule();
	Copy(p);
	return p;
}

CBaseObject* CSmvRule::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSmvRule *p = new CSmvRule();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSmvRule::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CCTRLBLOCK)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSmvRule::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCCtrlBlockKey)
	{
		pNew = new CCtrlBlock();
	}

	return pNew;
}

CExBaseObject* CSmvRule::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CCTRLBLOCK)
	{
		pNew = new CCtrlBlock();
	}

	return pNew;
}
CExBaseObject* CSmvRule::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

		pNew = new CCtrlBlock();

	return pNew;
}

BOOL CSmvRule::GenarateIecCfgDatasSMV(CIecCfgDatasSMV *pSmvMngr)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pCurObj = NULL;
	CCtrlBlock *pCurCtrlBlock = NULL;

	while(pos)
	{
		pCurObj = GetNext(pos);

		if (pCurObj->GetClassID() == MNGRCLASSID_CCTRLBLOCK)
		{
			pCurCtrlBlock = (CCtrlBlock *)pCurObj;
			pCurCtrlBlock->GenerateIecCfgDatas(pSmvMngr);
		}
	}

	return TRUE;
}
