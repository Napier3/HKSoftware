
#include "stdafx.h"
#include "SetsFileXml_Update.h"
#include "..\..\..\..\..\Module\xml\XmlRW_Pugi.h"
#include "..\..\..\..\..\Module\xml\PugiXML\pugixml.hpp"

#include "SetFilesXml_DSC.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSetsFileXml_Update::CSetsFileXml_Update()
{
	//初始化属性
	m_nItemNum = 0;
	m_pNode = NULL;

	//初始化成员变量
}

CSetsFileXml_Update::~CSetsFileXml_Update()
{
}

long CSetsFileXml_Update::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	CXmlRWNode_Pugi *pNode = (CXmlRWNode_Pugi *)&oNode;
	m_pNode = &(pNode->m_oPugiXmlNode);

	xml_GetAttibuteValue(pXmlKeys->m_strItemNumKey, oNode, m_nItemNum);
	return 0;
}

long CSetsFileXml_Update::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strItemNumKey, oElement, m_nItemNum);
	return 0;
}

long CSetsFileXml_Update::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nItemNum);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nItemNum);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nItemNum);
	}
	return 0;
}

void CSetsFileXml_Update::InitAfterRead()
{
}

BOOL CSetsFileXml_Update::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSetsFileXml_Update *p = (CSetsFileXml_Update*)pObj;

	if(m_nItemNum != p->m_nItemNum)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSetsFileXml_Update::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSetsFileXml_Update *p = (CSetsFileXml_Update*)pDest;

	p->m_nItemNum = m_nItemNum;
	return TRUE;
}

CBaseObject* CSetsFileXml_Update::Clone()
{
	CSetsFileXml_Update *p = new CSetsFileXml_Update();
	Copy(p);
	return p;
}

CBaseObject* CSetsFileXml_Update::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSetsFileXml_Update *p = new CSetsFileXml_Update();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSetsFileXml_Update::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSETSFILEXML_HI)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSetsFileXml_Update::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSetsFileXml_HIKey)
	{
		pNew = new CSetsFileXml_UI();
	}

	return pNew;
}

CExBaseObject* CSetsFileXml_Update::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSETSFILEXML_HI)
	{
		pNew = new CSetsFileXml_UI();
	}

	return pNew;
}

void CSetsFileXml_Update::SetItemNum(long nNum)
{
	m_nItemNum = nNum;

	m_pNode = &(((CSetFilesXml_DSC*)GetParent())->m_pNode->child(CSetFileXmlParseXmlRWKeys::CSetsFileXml_UpdateKey()));
	if (m_pNode != NULL)
	{
		pugi::xml_attribute attr = m_pNode->attribute(CSetFileXmlParseXmlRWKeys::g_pXmlKeys->m_strItemNumKey);
		attr.set_value(nNum);
	}
}

void CSetsFileXml_Update::ClearAllXmlNode()
{
	m_pNode = &(((CSetFilesXml_DSC*)GetParent())->m_pNode->child(CSetFileXmlParseXmlRWKeys::CSetsFileXml_UpdateKey()));
	if (m_pNode == NULL)
	{
		return;
	}

	pugi::xml_node nd = m_pNode->last_child();

	while (! nd.empty())
	{
		m_pNode->remove_child(nd);
		nd = m_pNode->last_child();
	}
}

void CSetsFileXml_Update::GetMd5_FromFile(const CString &strClass, CString &strMd5)
{
	CSetsFileXml_UI *pFind = FindUIByClass(strClass);

	if (pFind != NULL)
	{
		strMd5 = pFind->m_strmd5;
	}
}

CSetsFileXml_UI* CSetsFileXml_Update::FindUIByClass(const CString &strClass)
{
	POS pos = GetHeadPosition();
	CSetsFileXml_UI *pFind = NULL;

	while (pos != NULL)
	{
		CSetsFileXml_UI *pUI = (CSetsFileXml_UI *)GetNext(pos);

		if (pUI->m_strClass == strClass)
		{
			pFind = pUI;
			break;
		}
	}

	return pFind;
}

CSetsFileXml_UI* CSetsFileXml_Update::FindUIByClass_Grp(const CString &strClass, long nGrp)
{
	POS pos = GetHeadPosition();
	CSetsFileXml_UI *pFind = NULL;

	while (pos != NULL)
	{
		CSetsFileXml_UI *pUI = (CSetsFileXml_UI *)GetNext(pos);

		if (pUI->m_strClass == strClass
			&& pUI->m_nGrp == nGrp)
		{
			pFind = pUI;
			break;
		}
	}

	return pFind;
}

CSetsFileXml_UI* CSetsFileXml_Update::AddNewUI(const CString &strLd, const CString &strClass, long nGrp, const CString &strMd5)
{
	CSetsFileXml_UI* pNew = FindUIByClass_Grp(strClass, nGrp);

	//找到了，刷新md5。多次编辑同一个定值分组时，只需要刷新md5即可
	if (pNew != NULL)
	{
		//pNew->m_strmd5 = strMd5;
		pNew->SetMd5(strMd5);
		return pNew;
	}

	pNew = new CSetsFileXml_UI();
	AddNewChild(pNew);
	pNew->m_strLd = strLd;
	pNew->m_strClass = strClass;
	pNew->m_nGrp = nGrp;
	pNew->m_strmd5 = strMd5;
	m_nItemNum++;
	ASSERT(m_nItemNum == GetCount());

	m_pNode = &(((CSetFilesXml_DSC*)GetParent())->m_pNode->child(CSetFileXmlParseXmlRWKeys::CSetsFileXml_UpdateKey()));
	if (m_pNode != NULL)
	{
		pugi::xml_attribute attr = m_pNode->attribute(CSetFileXmlParseXmlRWKeys::g_pXmlKeys->m_strItemNumKey);
		attr.set_value(m_nItemNum);

		pugi::xml_node nUI = m_pNode->append_child(CSetFileXmlParseXmlRWKeys::g_pXmlKeys->m_strCSetsFileXml_UIKey);
		pugi::xml_attribute attr1 = nUI.append_attribute(CSetFileXmlParseXmlRWKeys::g_pXmlKeys->m_strLdKey);
		pugi::xml_attribute attr2 = nUI.append_attribute(CSetFileXmlParseXmlRWKeys::g_pXmlKeys->m_strClassKey);

		if (nGrp > 0)
		{
			pugi::xml_attribute attr3 = nUI.append_attribute(CSetFileXmlParseXmlRWKeys::g_pXmlKeys->m_strGrpKey);
			attr3.set_value(nGrp);
		}
		
		pugi::xml_attribute attr4 = nUI.append_attribute(CSetFileXmlParseXmlRWKeys::g_pXmlKeys->m_strMd5Key);

		char* psz = NULL;
		CString_to_char(strLd, &psz);
		wchar_t *pW = NULL;
		Char_to_WChart(psz, &pW);
		attr1.set_value(pW);
		delete []psz;
		delete []pW;

		psz = NULL;
		pW = NULL;
		CString_to_char(strClass, &psz);
		Char_to_WChart(psz, &pW);
		attr2.set_value(pW);
		delete []psz;
		delete []pW;

		psz = NULL;
		pW = NULL;
		CString_to_char(strMd5, &psz);
		Char_to_WChart(psz, &pW);
		attr4.set_value(pW);
		delete []psz;
		delete []pW;
	}
	return pNew;
}