//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGdGridInst.cpp  CSttGdGridInst


#include "stdafx.h"
#include "SttGdGridInst.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttGdGridInst::CSttGdGridInst()
{
	//初始化属性
	m_pSttGdInst_Cols = NULL;

	//初始化成员变量
}

CSttGdGridInst::~CSttGdGridInst()
{
}

long CSttGdGridInst::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttGdGridInst::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttGdGridInst::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

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

void CSttGdGridInst::InitAfterRead()
{
}

BOOL CSttGdGridInst::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttGdGridInst *p = (CSttGdGridInst*)pObj;

	return TRUE;
}

BOOL CSttGdGridInst::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttGdGridInst *p = (CSttGdGridInst*)pDest;

	return TRUE;
}

CBaseObject* CSttGdGridInst::Clone()
{
	CSttGdGridInst *p = new CSttGdGridInst();
	Copy(p);
	return p;
}

CBaseObject* CSttGdGridInst::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttGdGridInst *p = new CSttGdGridInst();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttGdGridInst::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTGDINST_COLS)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTGDCONDITION)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttGdGridInst::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttGdInst_ColsKey)
	{
		pNew = new CSttGdInst_Cols();
	}
	else if (strClassID == pXmlKeys->m_strCSttGdConditionKey)
	{
		pNew = new CSttGdCondition();
	}

	return pNew;
}

CExBaseObject* CSttGdGridInst::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTGDINST_COLS)
	{
		pNew = new CSttGdInst_Cols();
	}
	else if (nClassID == MNGRCLASSID_CSTTGDCONDITION)
	{
		pNew = new CSttGdCondition();
	}

	return pNew;
}

CSttGdInst_Cols* CSttGdGridInst::GetInst_Cols()
{
	if (m_pSttGdInst_Cols != NULL)
	{
		return m_pSttGdInst_Cols;
	}

	m_pSttGdInst_Cols = (CSttGdInst_Cols*)FindByClassID(MNGRCLASSID_CSTTGDINST_COLS);
	return m_pSttGdInst_Cols;
}

long CSttGdGridInst::GetColCount()
{
	GetInst_Cols();

	if (m_pSttGdInst_Cols == NULL)
	{
		return 0;
	}

	return m_pSttGdInst_Cols->GetCount();
}

BOOL CSttGdGridInst::GetGridColsTitleWidth(CString *pstrTitle,int *pnWidth,int nCols)
{
	CSttGdInst_Cols *pSttGdInst_Cols = GetInst_Cols();

	if (pSttGdInst_Cols == NULL)
	{
		return FALSE;
	}

	return pSttGdInst_Cols->GetGridColsTitleWidth(pstrTitle,pnWidth,nCols);
}

void CSttGdGridInst::InitGridInst(CSttGdGridDefine *pSttGdGridDefine)
{
	GetInst_Cols();

	if (m_pSttGdInst_Cols == NULL)
	{
		return;
	}

	m_pSttGdInst_Cols->InitGridCols(pSttGdGridDefine);
// 	POS pos = GetHeadPosition();
// 	CExBaseObject *pCurrObj = NULL;
// 	CSttGdGridInst *pSttGdGridInst = NULL;
// 
// 	while(pos)
// 	{
// 		pCurrObj = GetNext(pos);
// 
// 		if (pCurrObj->GetClassID() != MNGRCLASSID_CSTTGDGRIDINST)
// 		{
// 			continue;
// 		}
// 
// 		pSttGdGridInst = (CSttGdGridInst *)pCurrObj;
// 		pSttGdGridInst->InitGridInst(pSttGdGridDefine);
// 	}
}