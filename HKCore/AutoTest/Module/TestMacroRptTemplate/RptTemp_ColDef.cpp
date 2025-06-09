//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_ColDef.cpp  CRptTemp_ColDef


#include "stdafx.h"
#include "RptTemp_ColDef.h"
#include "RptTemp_TestMacroUiRptDef.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_ColDef::CRptTemp_ColDef()
{
	//初始化属性
	m_nPrecision = -1;  //默认-1，表示不需要修约。
	//初始化成员变量
}

CRptTemp_ColDef::~CRptTemp_ColDef()
{
}

long CRptTemp_ColDef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	xml_GetAttibuteValue(pXmlKeys->m_strPrecisionKey, oNode, m_strPrecision);
	xml_GetAttibuteValue(pXmlKeys->m_strProcessKey, oNode, m_strProcess);
	return 0;
}

long CRptTemp_ColDef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	xml_SetAttributeValue(pXmlKeys->m_strPrecisionKey, oElement, m_strPrecision);
	xml_SetAttributeValue(pXmlKeys->m_strProcessKey, oElement, m_strProcess);
	return 0;
}

long CRptTemp_ColDef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
		BinarySerializeCalLen(oBinaryBuffer, m_strPrecision);
		BinarySerializeCalLen(oBinaryBuffer, m_strProcess);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strID);
		BinarySerializeRead(oBinaryBuffer, m_strType);
		BinarySerializeRead(oBinaryBuffer, m_strPrecision);
		BinarySerializeRead(oBinaryBuffer, m_strProcess);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strID);
		BinarySerializeWrite(oBinaryBuffer, m_strType);
		BinarySerializeWrite(oBinaryBuffer, m_strPrecision);
		BinarySerializeWrite(oBinaryBuffer, m_strProcess);
	}
	return 0;
}

void CRptTemp_ColDef::InitAfterRead()
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

BOOL CRptTemp_ColDef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRptTemp_ColDef *p = (CRptTemp_ColDef*)pObj;

	if(m_strID != p->m_strID)
	{
		return FALSE;
	}

	if(m_strType != p->m_strType)
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

BOOL CRptTemp_ColDef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRptTemp_ColDef *p = (CRptTemp_ColDef*)pDest;

	p->m_strID = m_strID;
	p->m_strType = m_strType;
	p->m_strProcess = m_strProcess;
	p->m_strPrecision = m_strPrecision;
	p->m_nPrecision = m_nPrecision;
	return TRUE;
}

CBaseObject* CRptTemp_ColDef::Clone()
{
	CRptTemp_ColDef *p = new CRptTemp_ColDef();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_ColDef::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_ColDef *p = new CRptTemp_ColDef();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

CDataGroup* CRptTemp_ColDef::GetItemsTec()
{
	CRptTemp_TestMacroUiRptDef* pTestMacroUiDef = (CRptTemp_TestMacroUiRptDef *)GetAncestor(MNGRCLASSID_CRPTTEMP_TESTMACROUIRPTDEF);

	if (pTestMacroUiDef == NULL)
	{
		return NULL;
	}

	return pTestMacroUiDef->GetItemsTec();
}

BOOL CRptTemp_ColDef::UpdatePrecision()
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