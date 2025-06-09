//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MacroItemsGen.cpp  CMacroItemsGen


#include "stdafx.h"
#include "MacroItemsGen.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMacroItemsGen::CMacroItemsGen()
{
	//初始化属性

	//初始化成员变量
	m_pItemsGenParasMap = NULL;
	m_pItemsGenClass = NULL;
	m_pItemsGenDefine = NULL;
	m_nNewItems = 0;
}

CMacroItemsGen::~CMacroItemsGen()
{
}

long CMacroItemsGen::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);  //2022-3-11  lijunqing

	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strMacro_IdKey, oNode, m_strMacroID);
	xml_GetAttibuteValue(pXmlKeys->m_strNew_ItemsKey, oNode, m_nNewItems);
	return 0;
}

long CMacroItemsGen::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys); //2022-3-11  lijunqing

	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strMacro_IdKey, oElement, m_strMacroID);
	xml_SetAttributeValue(pXmlKeys->m_strNew_ItemsKey, oElement, m_nNewItems);

	return 0;
}

long CMacroItemsGen::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMacroID);
		BinarySerializeCalLen(oBinaryBuffer, m_nNewItems);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMacroID);
		BinarySerializeRead(oBinaryBuffer, m_nNewItems);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMacroID);
		BinarySerializeWrite(oBinaryBuffer, m_nNewItems);
	}
	return 0;
}

void CMacroItemsGen::InitAfterRead()
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
		else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENCLASS)
		{
			m_pItemsGenClass = (CItemsGenClass*)p;
		}
		else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENDEFINE)
		{
			m_pItemsGenDefine = (CItemsGenDefine*)p;
		}
	}

	if (m_pItemsGenParasMap == NULL)
	{
		m_pItemsGenParasMap = (CItemsGenParasMap*)AddNewChild(new CItemsGenParasMap());
	}

	if (m_pItemsGenClass == NULL)
	{
		m_pItemsGenClass = (CItemsGenClass*)AddNewChild(new CItemsGenClass());
	}

	if (m_pItemsGenDefine == NULL)
	{
		m_pItemsGenDefine = (CItemsGenDefine*)AddNewChild(new CItemsGenDefine());
	}

}

BOOL CMacroItemsGen::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseList::IsEqualOwn(pObj))
	{
		return FALSE;
	}


	CMacroItemsGen *p = (CMacroItemsGen*)pObj;

	if(m_strMacroID != p->m_strMacroID)
	{
		return FALSE;
	}

	if(m_nNewItems != p->m_nNewItems)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CMacroItemsGen::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseList::CopyOwn(pDest);
	CMacroItemsGen *p = (CMacroItemsGen*)pDest;

	p->m_strMacroID = m_strMacroID;
	p->m_nNewItems = m_nNewItems;
	return TRUE;
}

CBaseObject* CMacroItemsGen::Clone()
{
	CMacroItemsGen *p = new CMacroItemsGen();
	Copy(p);
	return p;
}

CBaseObject* CMacroItemsGen::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CMacroItemsGen *p = new CMacroItemsGen();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CMacroItemsGen::CanPaste(UINT nClassID)
{
	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENCLASS)
	{
		return TRUE;
	}

	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENINST)
	{
		return TRUE;
	}

	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENPARASMAP)
	{
		return TRUE;
	}

	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENDEFINE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CMacroItemsGen::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCItemsGenClassKey)
	{
		pNew = new CItemsGenClass();
	}
	else if (strClassID == pXmlKeys->m_strCItemsGenInstKey)
	{
		pNew = new CItemsGenInst();
	}
	else if (strClassID == pXmlKeys->m_strCItemsGenParasMapKey)
	{
		pNew = new CItemsGenParasMap();
	}
	else if (strClassID == pXmlKeys->m_strCItemsGenDefineKey)
	{
		pNew = new CItemsGenDefine();
	}

	return pNew;
}

CExBaseObject* CMacroItemsGen::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENCLASS)
	{
		pNew = new CItemsGenClass();
	}
	else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENINST)
	{
		pNew = new CItemsGenInst();
	}
	else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENPARASMAP)
	{
		pNew = new CItemsGenParasMap();
	}
	else if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENDEFINE)
	{
		pNew = new CItemsGenDefine();
	}

	return pNew;
}

void CMacroItemsGen::InitParasMapByUIParas(CDataGroup *pUIParas)
{
	if (m_pItemsGenParasMap != NULL)
	{
		m_pItemsGenParasMap->InitParaValueByUIParas(pUIParas);
		m_pItemsGenParasMap->LogParasMapError();
	}	

	if (m_pItemsGenDefine != NULL)
	{
		m_pItemsGenDefine->InitParasMapByUIParas(pUIParas);
	}

	if (m_pItemsGenClass != NULL)
	{
		m_pItemsGenClass->InitParasMapByUIParas(pUIParas);
	}
}

