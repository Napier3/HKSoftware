//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_TextDef.cpp  CRptTemp_TextDef


#include "stdafx.h"
#include "RptTemp_TextDef.h"
#include "RptTemp_TestMacroUiRptDef.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_TextDef::CRptTemp_TextDef()
{
	//初始化属性
	m_pEnable = NULL;
	m_fSize = 10.5;  //10.5磅。五号字体
	m_nBold = 0;
	//初始化成员变量
}

CRptTemp_TextDef::~CRptTemp_TextDef()
{
}

long CRptTemp_TextDef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTextKey, oNode, m_strText);
	xml_GetAttibuteValue(pXmlKeys->m_strData1_IdKey, oNode, m_strData1_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strData2_IdKey, oNode, m_strData2_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strData3_IdKey, oNode, m_strData3_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strData4_IdKey, oNode, m_strData4_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strData5_IdKey, oNode, m_strData5_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strData6_IdKey, oNode, m_strData6_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strFontKey, oNode, m_strFont);
	xml_GetAttibuteValue(pXmlKeys->m_strSizeKey, oNode, m_fSize);
	xml_GetAttibuteValue(pXmlKeys->m_strBoldKey, oNode, m_nBold);	
	return 0;
}

long CRptTemp_TextDef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTextKey, oElement, m_strText);
	xml_SetAttributeValue(pXmlKeys->m_strData1_IdKey, oElement, m_strData1_Id);
	xml_SetAttributeValue(pXmlKeys->m_strData2_IdKey, oElement, m_strData2_Id);
	xml_SetAttributeValue(pXmlKeys->m_strData3_IdKey, oElement, m_strData3_Id);
	xml_SetAttributeValue(pXmlKeys->m_strData4_IdKey, oElement, m_strData4_Id);
	xml_SetAttributeValue(pXmlKeys->m_strData5_IdKey, oElement, m_strData5_Id);
	xml_SetAttributeValue(pXmlKeys->m_strData6_IdKey, oElement, m_strData6_Id);
	xml_SetAttributeValue(pXmlKeys->m_strFontKey, oElement, m_strFont);
	xml_SetAttributeValue(pXmlKeys->m_strSizeKey, oElement, m_fSize);
	xml_SetAttributeValue(pXmlKeys->m_strBoldKey, oElement, m_nBold);	
	return 0;
}

long CRptTemp_TextDef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strText);
		BinarySerializeCalLen(oBinaryBuffer, m_strData1_Id);
		BinarySerializeCalLen(oBinaryBuffer, m_strData2_Id);
		BinarySerializeCalLen(oBinaryBuffer, m_strData3_Id);
		BinarySerializeCalLen(oBinaryBuffer, m_strData4_Id);
		BinarySerializeCalLen(oBinaryBuffer, m_strData5_Id);
		BinarySerializeCalLen(oBinaryBuffer, m_strData6_Id);
		BinarySerializeCalLen(oBinaryBuffer, m_strFont);
		BinarySerializeCalLen(oBinaryBuffer, m_fSize);
		BinarySerializeCalLen(oBinaryBuffer, m_nBold);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strText);
		BinarySerializeRead(oBinaryBuffer, m_strData1_Id);
		BinarySerializeRead(oBinaryBuffer, m_strData2_Id);
		BinarySerializeRead(oBinaryBuffer, m_strData3_Id);
		BinarySerializeRead(oBinaryBuffer, m_strData4_Id);
		BinarySerializeRead(oBinaryBuffer, m_strData5_Id);
		BinarySerializeRead(oBinaryBuffer, m_strData6_Id);
		BinarySerializeRead(oBinaryBuffer, m_strFont);
		BinarySerializeRead(oBinaryBuffer, m_fSize);
		BinarySerializeRead(oBinaryBuffer, m_nBold);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strText);
		BinarySerializeWrite(oBinaryBuffer, m_strData1_Id);
		BinarySerializeWrite(oBinaryBuffer, m_strData2_Id);
		BinarySerializeWrite(oBinaryBuffer, m_strData3_Id);
		BinarySerializeWrite(oBinaryBuffer, m_strData4_Id);
		BinarySerializeWrite(oBinaryBuffer, m_strData5_Id);
		BinarySerializeWrite(oBinaryBuffer, m_strData6_Id);
		BinarySerializeWrite(oBinaryBuffer, m_strFont);
		BinarySerializeWrite(oBinaryBuffer, m_fSize);
		BinarySerializeWrite(oBinaryBuffer, m_nBold);
	}
	return 0;
}

void CRptTemp_TextDef::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == MNGRCLASSID_CRPTTEMP_ENABLE)
		{
			m_pEnable = (CRptTemp_Enable*)p;
		}
	}
}

BOOL CRptTemp_TextDef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRptTemp_TextDef *p = (CRptTemp_TextDef*)pObj;

	if(m_strText != p->m_strText)
	{
		return FALSE;
	}

	if(m_strData1_Id != p->m_strData1_Id)
	{
		return FALSE;
	}

	if(m_strData2_Id != p->m_strData2_Id)
	{
		return FALSE;
	}

	if(m_strData3_Id != p->m_strData3_Id)
	{
		return FALSE;
	}

	if(m_strData4_Id != p->m_strData4_Id)
	{
		return FALSE;
	}

	if(m_strData5_Id != p->m_strData5_Id)
	{
		return FALSE;
	}

	if(m_strData6_Id != p->m_strData6_Id)
	{
		return FALSE;
	}

	if(m_strFont != p->m_strFont)
	{
		return FALSE;
	}

	if(m_fSize != p->m_fSize)
	{
		return FALSE;
	}

	if(m_nBold != p->m_nBold)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRptTemp_TextDef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRptTemp_TextDef *p = (CRptTemp_TextDef*)pDest;

	p->m_strText = m_strText;
	p->m_strData1_Id = m_strData1_Id;
	p->m_strData2_Id = m_strData2_Id;
	p->m_strData3_Id = m_strData3_Id;
	p->m_strData4_Id = m_strData4_Id;
	p->m_strData5_Id = m_strData5_Id;
	p->m_strData6_Id = m_strData6_Id;
	p->m_strFont = m_strFont;
	p->m_fSize = m_fSize;
	p->m_nBold = m_nBold;	
	return TRUE;
}

CBaseObject* CRptTemp_TextDef::Clone()
{
	CRptTemp_TextDef *p = new CRptTemp_TextDef();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_TextDef::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_TextDef *p = new CRptTemp_TextDef();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}


BOOL CRptTemp_TextDef::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CRPTTEMP_ENABLE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CRptTemp_TextDef::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCRptTemp_EnableKey)
	{
		pNew = new CRptTemp_Enable();
	}

	return pNew;
}

CExBaseObject* CRptTemp_TextDef::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == MNGRCLASSID_CRPTTEMP_ENABLE)
	{
		pNew = new CRptTemp_Enable();
	}

	return pNew;
}

BOOL CRptTemp_TextDef::IsEnable(CExBaseList *pParas)
{
	if (m_pEnable == NULL)
	{
		//默认使能为1
		return TRUE;
	}

	return m_pEnable->IsEnable(pParas);
}

CDataGroup* CRptTemp_TextDef::GetItemsTec()
{
	CRptTemp_TestMacroUiRptDef* pTestMacroUiDef = (CRptTemp_TestMacroUiRptDef *)GetAncestor(MNGRCLASSID_CRPTTEMP_TESTMACROUIRPTDEF);

	if (pTestMacroUiDef == NULL)
	{
		return NULL;
	}

	return pTestMacroUiDef->GetItemsTec();
}