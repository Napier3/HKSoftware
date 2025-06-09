//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DocTable.cpp  CDocTable


#include "stdafx.h"
#include "DocTable.h"

CDocTable::CDocTable()
{
	//��ʼ������

	//��ʼ����Ա����
}

CDocTable::~CDocTable()
{
}

long CDocTable::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDocCmpXmlRWKeys *pXmlKeys = (CDocCmpXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strCmp_IdKey, oNode, m_strCmp_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strTxt_Cmp_IdKey, oNode, m_strTxt_Cmp_Id);
	return 0;
}

long CDocTable::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDocCmpXmlRWKeys *pXmlKeys = (CDocCmpXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strCmp_IdKey, oElement, m_strCmp_Id);
	xml_SetAttributeValue(pXmlKeys->m_strTxt_Cmp_IdKey, oElement, m_strTxt_Cmp_Id);
	return 0;
}

void CDocTable::InitAfterRead()
{
}

BOOL CDocTable::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CDocTable *p = (CDocTable*)pObj;

	if(m_strCmp_Id != p->m_strCmp_Id)
	{
		return FALSE;
	}

	if(m_strTxt_Cmp_Id != p->m_strTxt_Cmp_Id)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDocTable::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDocTable *p = (CDocTable*)pDest;

	p->m_strCmp_Id = m_strCmp_Id;
	p->m_strTxt_Cmp_Id = m_strTxt_Cmp_Id;
	return TRUE;
}

CBaseObject* CDocTable::Clone()
{
	CDocTable *p = new CDocTable();
	Copy(p);
	return p;
}

BOOL CDocTable::CanPaste(UINT nClassID)
{
	if (nClassID == DOCMPCLASSID_CDOCROW)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CDocTable::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDocCmpXmlRWKeys *pXmlKeys = (CDocCmpXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDocRowKey)
	{
		pNew = new CDocRow();
	}

	return pNew;
}

CExBaseObject* CDocTable::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DOCMPCLASSID_CDOCROW)
	{
		pNew = new CDocRow();
	}

	return pNew;
}

void CDocTable::SetCmpError()
{
	if (m_strCmp_Id.GetLength() > 0)
	{//�Ѿ��Ƚϣ����ٴ���
		return;
	}

	POS pos = GetHeadPosition();
	CDocRow *pRow = NULL;

	while (pos != NULL)
	{
		pRow = (CDocRow *)GetNext(pos);
		pRow->SetCmpError();
	}
}

void CDocTable::Cmp(CDocTable *pRef)
{	
	if (pRef == NULL)
	{
		return;
	}

	POS pos = GetHeadPosition();
	CDocRow *pRow = NULL;
	long nIndex = 0;

	while (pos != NULL)
	{
		pRow = (CDocRow *)GetNext(pos);
		pRow->Cmp((CDocRow*)pRef->GetAtIndex(nIndex));
		nIndex++;
	}

	//����û�бȽϵı����
	pRef->SetCmpError();
	m_strCmp_Id = docmp_GenDocCmpID();
	pRef->m_strCmp_Id = m_strCmp_Id;
}

