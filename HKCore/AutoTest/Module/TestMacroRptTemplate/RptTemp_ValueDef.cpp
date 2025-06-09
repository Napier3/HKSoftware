//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_ValueDef.cpp  CRptTemp_ValueDef


#include "stdafx.h"
#include "RptTemp_ValueDef.h"
#include "RptTemp_TestMacroUiRptDef.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_ValueDef::CRptTemp_ValueDef()
{
	//初始化属性
	m_nPrecision = -1;  //默认-1，表示不需要修约。
	//初始化成员变量
}

CRptTemp_ValueDef::~CRptTemp_ValueDef()
{
}

long CRptTemp_ValueDef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strValKey, oNode, m_strVal);
	xml_GetAttibuteValue(pXmlKeys->m_strPrecisionKey, oNode, m_strPrecision);
	xml_GetAttibuteValue(pXmlKeys->m_strProcessKey, oNode, m_strProcess);
	return 0;
}

long CRptTemp_ValueDef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strValKey, oElement, m_strVal);
	xml_SetAttributeValue(pXmlKeys->m_strPrecisionKey, oElement, m_strPrecision);
	xml_SetAttributeValue(pXmlKeys->m_strProcessKey, oElement, m_strProcess);
	return 0;
}

long CRptTemp_ValueDef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strVal);
		BinarySerializeCalLen(oBinaryBuffer, m_strPrecision);
		BinarySerializeCalLen(oBinaryBuffer, m_strProcess);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strVal);
		BinarySerializeRead(oBinaryBuffer, m_strPrecision);
		BinarySerializeRead(oBinaryBuffer, m_strProcess);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strVal);
		BinarySerializeWrite(oBinaryBuffer, m_strPrecision);
		BinarySerializeWrite(oBinaryBuffer, m_strProcess);
	}
	return 0;
}

void CRptTemp_ValueDef::InitAfterRead()
{
	if (m_strPrecision.IsEmpty())
	{
		return;
	}

	//处理保留精度：m_strPrecision转换到m_nPrecision
	CDataGroup* pItemsTec = GetItemsTec();

	if (pItemsTec == NULL)
	{
		m_nPrecision = CString_To_long(m_strPrecision);
		return;
	}

	CDvmData* pData = (CDvmData *)pItemsTec->FindByID(m_strPrecision);

	if (pData == NULL)
	{
		m_nPrecision = CString_To_long(m_strPrecision);
	}
	else
	{
		m_nPrecision = CString_To_long(pData->m_strValue);
	}
}

BOOL CRptTemp_ValueDef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CRptTemp_ValueDef *p = (CRptTemp_ValueDef*)pObj;

	if(m_strVal != p->m_strVal)
	{
		return FALSE;
	}

	if(m_strProcess != p->m_strProcess)
	{
		return FALSE;
	}

	if(m_strPrecision != p->m_strPrecision)
	{
		return FALSE;
	}

	if(m_nPrecision != p->m_nPrecision)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRptTemp_ValueDef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CRptTemp_ValueDef *p = (CRptTemp_ValueDef*)pDest;

	p->m_strVal = m_strVal;
	p->m_strProcess = m_strProcess;
	p->m_strPrecision = m_strPrecision;
	p->m_nPrecision = m_nPrecision;
	return TRUE;
}

CBaseObject* CRptTemp_ValueDef::Clone()
{
	CRptTemp_ValueDef *p = new CRptTemp_ValueDef();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_ValueDef::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_ValueDef *p = new CRptTemp_ValueDef();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

CDataGroup* CRptTemp_ValueDef::GetItemsTec()
{
	CRptTemp_TestMacroUiRptDef* pTestMacroUiDef = (CRptTemp_TestMacroUiRptDef *)GetAncestor(MNGRCLASSID_CRPTTEMP_TESTMACROUIRPTDEF);

	if (pTestMacroUiDef == NULL)
	{
		return NULL;
	}

	return pTestMacroUiDef->GetItemsTec();
}

BOOL CRptTemp_ValueDef::UpdatePrecision()
{
	CDataGroup *pItemsTec = GetItemsTec();

	if (pItemsTec == NULL)
	{
		return FALSE;
	}

	CDvmData* pData = (CDvmData *)pItemsTec->FindByID(m_strPrecision);

	if (pData != NULL)
	{
		m_nPrecision = CString_To_long(pData->m_strValue);
		return TRUE;
	}
	
	return FALSE;
}