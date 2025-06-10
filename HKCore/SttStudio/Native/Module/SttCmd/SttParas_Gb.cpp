//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttParas.cpp  CSttParas


#include "stdafx.h"
#include "SttParas_Gb.h"
#include "../../../AutoTest/Module/GuideBook/GuideBook.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttParas_Gb::CSttParas_Gb()
{
	m_pItems = NULL;
	m_pDataTypes = NULL;
	m_pTestTemplate = NULL;
	m_bItemsAttach = FALSE;
}

CSttParas_Gb::~CSttParas_Gb()
{
	FreeItems();
}

void CSttParas_Gb::FreeItems()
{
	if (m_bItemsAttach)
	{
		Remove(m_pItems);
		Remove(m_pDataTypes);
		m_bItemsAttach = FALSE;
		m_pItems = NULL;
		m_pDataTypes = NULL;
	}
	else
	{
		m_pItems = NULL;
		m_pDataTypes = NULL;
	}
}

void CSttParas_Gb::AttachItems(CItems *pItems, CDataTypes *pDataTypes)
{
	FreeItems();
	m_pDataTypes = pDataTypes;
	m_pItems = pItems;
	m_bItemsAttach = TRUE;
	AddNewChild(pItems);
	AddNewChild(pDataTypes);
}

CBaseObject* CSttParas_Gb::Clone()
{
	CSttParas_Gb *p = new CSttParas_Gb();
	Copy(p);
	return p;
}

CBaseObject* CSttParas_Gb::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttParas_Gb *p = new CSttParas_Gb();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

CExBaseObject* CSttParas_Gb::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
     CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

    if (strClassID ==  CSttCmdDefineXmlRWKeys::CSttGuideBookKey())
    {
        m_pTestTemplate = new CGuideBook();
        return m_pTestTemplate;
    }
	else if (strClassID ==  CSttCmdDefineXmlRWKeys::CSttItemsKey())
	{
		m_pItems = new CItems();
		return m_pItems;
	}
	else if (strClassID == pXmlKeys->m_strCDataTypesKey)
	{
		m_pDataTypes = new CDataTypes();
		return m_pDataTypes;
	}
	else
    {
        return CSttParas::CreateNewChild(strClassID, bAddToTail, pXmlKeys);
    }
}


long CSttParas_Gb::XmlReadChildren(CXmlRWNodeListBase &oNodes, CXmlRWKeys *pXmlRWKeys)
{
	long nCount = oNodes.GetNodeNum();
	long nIndex = 0;
	CBaseObject *pNew = NULL;
	CXmlRWNodeBase *pNode = NULL;
	CString strNodeName;
	BOOL bAddToTail = TRUE;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pNode = oNodes.GetChild(nIndex);

		if (pNode == NULL)
		{
			continue;
		}

		pNew = CExBaseList::CreateNewChild(*pNode, bAddToTail, pXmlRWKeys);

		if (pNew != NULL && bAddToTail)
		{
			pNew->SetParent(this);
			AddTail((CExBaseObject*)pNew);
		}

		if (pNew)
		{
			if (pNew->GetClassID() == GBCLASSID_ITEMS
				|| pNew->GetClassID() == GBCLASSID_GUIDEBOOK)
			{
				pNew->XmlRead(*pNode, CGbXMLKeys::g_pGbXMLKeys);
			}
			else
			{
				pNew->XmlRead(*pNode, pXmlRWKeys);
			}
		}

		bAddToTail = TRUE;
	}

	return 0;
}

//WriteXml
long CSttParas_Gb::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	POS pos = GetHeadPosition();
	CBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);

		if (pObj->GetClassID() == GBCLASSID_ITEMS)
		{
			pObj->XmlWrite(oXMLDoc, oElement, CGbXMLKeys::g_pGbXMLKeys);
		}
		else
		{
			pObj->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
		}
	}

	return 0;
}
