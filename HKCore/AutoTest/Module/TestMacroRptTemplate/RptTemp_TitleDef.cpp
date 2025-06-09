//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_TitleDef.cpp  CRptTemp_TitleDef


#include "stdafx.h"
#include "RptTemp_TitleDef.h"
#include "RptTemp_Items.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_TitleDef::CRptTemp_TitleDef()
{
	//初始化属性
	m_nLevel = 0;
	m_nItem_Level = 0;
	m_nItem_Level_2 = 0;
	m_nItem_Level_3 = 0;

	//初始化成员变量
}

CRptTemp_TitleDef::~CRptTemp_TitleDef()
{
}

long CRptTemp_TitleDef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strLevelKey, oNode, m_nLevel);
	xml_GetAttibuteValue(pXmlKeys->m_strTextKey, oNode, m_strText);
	xml_GetAttibuteValue(pXmlKeys->m_strItem_IdKey, oNode, m_strItem_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strItem_LevelKey, oNode, m_nItem_Level);
	xml_GetAttibuteValue(pXmlKeys->m_strItem_Level_2Key, oNode, m_nItem_Level_2);
	xml_GetAttibuteValue(pXmlKeys->m_strItem_Level_3Key, oNode, m_nItem_Level_3);
	return 0;
}

long CRptTemp_TitleDef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strLevelKey, oElement, m_nLevel);
	xml_SetAttributeValue(pXmlKeys->m_strTextKey, oElement, m_strText);
	xml_SetAttributeValue(pXmlKeys->m_strItem_IdKey, oElement, m_strItem_Id);
	xml_SetAttributeValue(pXmlKeys->m_strItem_LevelKey, oElement, m_nItem_Level);
	xml_SetAttributeValue(pXmlKeys->m_strItem_Level_2Key, oElement, m_nItem_Level_2);
	xml_SetAttributeValue(pXmlKeys->m_strItem_Level_3Key, oElement, m_nItem_Level_3);
	return 0;
}

long CRptTemp_TitleDef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nLevel);
		BinarySerializeCalLen(oBinaryBuffer, m_strText);
		BinarySerializeCalLen(oBinaryBuffer, m_strItem_Id);
		BinarySerializeCalLen(oBinaryBuffer, m_nItem_Level);
		BinarySerializeCalLen(oBinaryBuffer, m_nItem_Level_2);
		BinarySerializeCalLen(oBinaryBuffer, m_nItem_Level_3);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nLevel);
		BinarySerializeRead(oBinaryBuffer, m_strText);
		BinarySerializeRead(oBinaryBuffer, m_strItem_Id);
		BinarySerializeRead(oBinaryBuffer, m_nItem_Level);
		BinarySerializeRead(oBinaryBuffer, m_nItem_Level_2);
		BinarySerializeRead(oBinaryBuffer, m_nItem_Level_3);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nLevel);
		BinarySerializeWrite(oBinaryBuffer, m_strText);
		BinarySerializeWrite(oBinaryBuffer, m_strItem_Id);
		BinarySerializeWrite(oBinaryBuffer, m_nItem_Level);
		BinarySerializeWrite(oBinaryBuffer, m_nItem_Level_2);
		BinarySerializeWrite(oBinaryBuffer, m_nItem_Level_3);
	}
	return 0;
}

void CRptTemp_TitleDef::InitAfterRead()
{
}

BOOL CRptTemp_TitleDef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRptTemp_TitleDef *p = (CRptTemp_TitleDef*)pObj;

	if(m_nLevel != p->m_nLevel)
	{
		return FALSE;
	}

	if(m_strText != p->m_strText)
	{
		return FALSE;
	}

	if(m_strItem_Id != p->m_strItem_Id)
	{
		return FALSE;
	}

	if(m_nItem_Level != p->m_nItem_Level)
	{
		return FALSE;
	}

	if(m_nItem_Level_2 != p->m_nItem_Level_2)
	{
		return FALSE;
	}

	if(m_nItem_Level_3 != p->m_nItem_Level_3)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRptTemp_TitleDef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRptTemp_TitleDef *p = (CRptTemp_TitleDef*)pDest;

	p->m_nLevel = m_nLevel;
	p->m_strText = m_strText;
	p->m_strItem_Id = m_strItem_Id;
	p->m_nItem_Level = m_nItem_Level;
	p->m_nItem_Level_2 = m_nItem_Level_2;
	p->m_nItem_Level_3 = m_nItem_Level_3;
	return TRUE;
}

CBaseObject* CRptTemp_TitleDef::Clone()
{
	CRptTemp_TitleDef *p = new CRptTemp_TitleDef();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_TitleDef::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_TitleDef *p = new CRptTemp_TitleDef();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CRptTemp_TitleDef::GetTitleLevel()
{
	long nTitleLevel = m_nLevel;
	CRptTemp_Items* pFind = GetFirstItems_UseRptTitle();

	if (pFind != NULL)
	{
		nTitleLevel += pFind->m_ntitle_level; 
	}

	return nTitleLevel;
}

//找到最近的 rpt-title属性设置为1的Items节点
CRptTemp_Items* CRptTemp_TitleDef::GetFirstItems_UseRptTitle()
{
	CRptTemp_Items* pFind = NULL;
	UINT nClassID = 0;
	CExBaseObject *pParent = this;

	while (pParent != NULL)
	{
		nClassID = pParent->GetClassID();

		if (nClassID == MNGRCLASSID_CRPTTEMP_ITEMS)
		{
			CRptTemp_Items* pItems = (CRptTemp_Items*)pParent;

			if (pItems->m_nRpt_Title == 1)
			{
				pFind = pItems;
				break;
			}
		}

		if (nClassID == MNGRCLASSID_CRPTTEMP_GUIDEBOOK)
		{
			break;
		}

		pParent = (CExBaseObject *)pParent->GetParent();
	}

	return pFind;
}