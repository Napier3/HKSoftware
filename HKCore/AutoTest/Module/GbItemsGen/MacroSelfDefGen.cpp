//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MacroSelfDefGen.cpp  CMacroSelfDefGen


#include "stdafx.h"
#include "MacroSelfDefGen.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMacroSelfDefGen::CMacroSelfDefGen()
{
	//初始化属性

	//初始化成员变量
	m_pItemsGenParasMap = NULL;
	m_pItemGenRsltExpr = NULL;
}

CMacroSelfDefGen::~CMacroSelfDefGen()
{
}

long CMacroSelfDefGen::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);  //2022-3-11  lijunqing

	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CMacroSelfDefGen::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys); //2022-3-11  lijunqing

	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;


	return 0;
}

long CMacroSelfDefGen::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CMacroSelfDefGen::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENPARASMAP)
		{
			m_pItemsGenParasMap = (CItemsGenParasMap*)p;
		}
		else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMGENRSLTEXPR)
		{
			m_pItemGenRsltExpr = (CItemGenRsltExpr*)p;
		}
	}
}

BOOL CMacroSelfDefGen::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}


	CMacroSelfDefGen *p = (CMacroSelfDefGen*)pObj;

	return TRUE;
}

BOOL CMacroSelfDefGen::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);
	CMacroSelfDefGen *p = (CMacroSelfDefGen*)pDest;

	return TRUE;
}

CBaseObject* CMacroSelfDefGen::Clone()
{
	CMacroSelfDefGen *p = new CMacroSelfDefGen();
	Copy(p);
	return p;
}

CBaseObject* CMacroSelfDefGen::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CMacroSelfDefGen *p = new CMacroSelfDefGen();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CMacroSelfDefGen::CanPaste(UINT nClassID)
{
	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMGENRSLTEXPR)
	{
		return TRUE;
	}

	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENPARASMAP)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CMacroSelfDefGen::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCItemsGenParasMapKey)
	{
		pNew = new CItemsGenParasMap();
	}
	else if (strClassID == pXmlKeys->m_strCItemRsltExprKey)
	{
		pNew = new CItemGenRsltExpr();
	}

	return pNew;
}

CExBaseObject* CMacroSelfDefGen::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENPARASMAP)
	{
		pNew = new CItemsGenParasMap();
	}
	else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMGENRSLTEXPR)
	{
		pNew = new CItemGenRsltExpr();
	}

	return pNew;
}

void CMacroSelfDefGen::InitParasMapByUIParas(CDataGroup *pUIParas)
{
	if (m_pItemsGenParasMap == NULL)
	{
		return;
	}

	m_pItemsGenParasMap->InitParaValueByUIParas(pUIParas);
	//m_pItemsGenParasMap->LogParasMapError();
}

