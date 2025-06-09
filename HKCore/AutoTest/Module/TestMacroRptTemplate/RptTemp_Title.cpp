//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//RptTemp_Title.cpp  CRptTemp_Title


#include "stdafx.h"
#include "RptTemp_Title.h"
#include "RptTemp_Items.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_Title::CRptTemp_Title()
{
	//��ʼ������
	m_nLevel = 0;

	//��ʼ����Ա����
}

CRptTemp_Title::~CRptTemp_Title()
{
}

long CRptTemp_Title::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strLevelKey, oNode, m_nLevel);
	xml_GetAttibuteValue(pXmlKeys->m_strTextKey, oNode, m_strText);
	return 0;
}

long CRptTemp_Title::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strLevelKey, oElement, m_nLevel);
	xml_SetAttributeValue(pXmlKeys->m_strTextKey, oElement, m_strText);
	return 0;
}

long CRptTemp_Title::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nLevel);
		BinarySerializeCalLen(oBinaryBuffer, m_strText);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nLevel);
		BinarySerializeRead(oBinaryBuffer, m_strText);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nLevel);
		BinarySerializeWrite(oBinaryBuffer, m_strText);
	}
	return 0;
}

void CRptTemp_Title::InitAfterRead()
{
}

BOOL CRptTemp_Title::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRptTemp_Title *p = (CRptTemp_Title*)pObj;

	if(m_nLevel != p->m_nLevel)
	{
		return FALSE;
	}

	if(m_strText != p->m_strText)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRptTemp_Title::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRptTemp_Title *p = (CRptTemp_Title*)pDest;

	p->m_nLevel = m_nLevel;
	p->m_strText = m_strText;
	return TRUE;
}

CBaseObject* CRptTemp_Title::Clone()
{
	CRptTemp_Title *p = new CRptTemp_Title();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_Title::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_Title *p = new CRptTemp_Title();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

//��ȡ�������Եȼ����������items�ڵ�ĵȼ�
long CRptTemp_Title::GetRelTitleLevel()
{
	long nTitleLevel = 0;
	CRptTemp_Items* pFind = GetFirstItems_UseRptTitle();

	if (pFind != NULL)
	{
		nTitleLevel += pFind->m_ntitle_level; 
	}

	return nTitleLevel;
}

//�ҵ������ rpt-title��������Ϊ1��Items�ڵ�
CRptTemp_Items* CRptTemp_Title::GetFirstItems_UseRptTitle()
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

		if (nClassID == MNGRCLASSID_CRPTTEMP_TESTMACROUIRPT)
		{
			break;
		}

		pParent = (CExBaseObject *)pParent->GetParent();
	}

	return pFind;
}