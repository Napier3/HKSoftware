//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbItemsGen.cpp  CGbItemsGen


#include "stdafx.h"
#include "GbItemsGen.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CGbItemsGen::CGbItemsGen()
{
	//初始化属性

	//初始化成员变量
}

CGbItemsGen::~CGbItemsGen()
{
}

long CGbItemsGen::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNew_ItemsKey, oNode, m_nNewItems);
	xml_GetAttibuteValue(pXmlKeys->m_strEngineProgIDKey, oNode, m_strEngineProgID);

	return 0;
}

long CGbItemsGen::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strNew_ItemsKey, oElement, m_nNewItems);
	xml_SetAttributeValue(pXmlKeys->m_strEngineProgIDKey, oElement, m_strEngineProgID);

	return 0;
}

long CGbItemsGen::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nNewItems);
		BinarySerializeCalLen(oBinaryBuffer, m_strEngineProgID);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nNewItems);
		BinarySerializeRead(oBinaryBuffer, m_strEngineProgID);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nNewItems);
		BinarySerializeWrite(oBinaryBuffer, m_strEngineProgID);
	}
	return 0;
}

void CGbItemsGen::InitAfterRead()
{

}

BOOL CGbItemsGen::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CGbItemsGen *p = (CGbItemsGen*)pObj;
	if(m_nNewItems != p->m_nNewItems)
	{
		return FALSE;
	}

	if(m_strEngineProgID != p->m_strEngineProgID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CGbItemsGen::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CGbItemsGen *p = (CGbItemsGen*)pDest;
	p->m_nNewItems = m_nNewItems;
	p->m_strEngineProgID = m_strEngineProgID;

	return TRUE;
}

CBaseObject* CGbItemsGen::Clone()
{
	CGbItemsGen *p = new CGbItemsGen();
	Copy(p);
	return p;
}

CBaseObject* CGbItemsGen::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CGbItemsGen *p = new CGbItemsGen();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CGbItemsGen::CanPaste(UINT nClassID)
{
	if (nClassID == GBITEMSGENMNGRCLASSID_CMACROITEMSGEN)
	{
		return TRUE;
	}

	if (nClassID == GBITEMSGENMNGRCLASSID_CMACROSELFDEFGEN)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CGbItemsGen::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCMacroItemsGenKey)
	{
		pNew = new CMacroItemsGen();
	}

	if (strClassID == pXmlKeys->m_strCMacroSelfDefGenKey)
	{
		pNew = new CMacroSelfDefGen();
	}

	return pNew;
}

CExBaseObject* CGbItemsGen::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == GBITEMSGENMNGRCLASSID_CMACROITEMSGEN)
	{
		pNew = new CMacroItemsGen();
	}

	if (nClassID == GBITEMSGENMNGRCLASSID_CMACROSELFDEFGEN)
	{
		pNew = new CMacroSelfDefGen();
	}

	return pNew;
}

void CGbItemsGen::InitParasMapByUIParas(CDataGroup *pUIParas)
{
	if (pUIParas == NULL)
	{
		return;
	}

	POS pos = GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;
	
	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if(nClassID == GBITEMSGENMNGRCLASSID_CMACROITEMSGEN)
		{
			CMacroItemsGen *pMacroItemsGen = (CMacroItemsGen *)pObj;
			pMacroItemsGen->InitParasMapByUIParas(pUIParas);
		}

		if (nClassID == GBITEMSGENMNGRCLASSID_CMACROSELFDEFGEN)
		{
			CMacroSelfDefGen *pMacroSelfDefGen = (CMacroSelfDefGen *)pObj;
			pMacroSelfDefGen->InitParasMapByUIParas(pUIParas);
		}
	}
}

CString CGbItemsGen::GetGbxmlName()
{
	CString strName;
// 	POS pos = GetHeadPosition();
// 	UINT nClassID = 0;
// 	CExBaseObject *pObj = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pObj = GetNext(pos);
// 		nClassID = pObj->GetClassID();
// 
// 		if(nClassID != GBITEMSGENMNGRCLASSID_CMACROITEMSGEN)
// 		{
// 			continue;
// 		}
// 
// 		CMacroItemsGen *pMacroItemsGen = (CMacroItemsGen *)pObj;
// 		strName.AppendFormat(_T("_"));
// 		strName.AppendFormat(pMacroItemsGen->m_strMacroID);
// 	}

	strName.AppendFormat(_T("%s_%s.gbxml"), m_strName.GetString(), m_strID.GetString());
	return strName;
}