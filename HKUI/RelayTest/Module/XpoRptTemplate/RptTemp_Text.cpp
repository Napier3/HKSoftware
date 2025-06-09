//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_Text.cpp  CRptTemp_Text


#include "stdafx.h"
#include "RptTemp_Text.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_Text::CRptTemp_Text()
{
	//初始化属性
	m_fSize = 10.5;  //10.5磅。五号字体
	m_nBold = 0;
	m_pGbItemBase = NULL;
	//初始化成员变量
}

CRptTemp_Text::~CRptTemp_Text()
{
}

long CRptTemp_Text::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTextKey, oNode, m_strText);
	xml_GetAttibuteValue(pXmlKeys->m_strFontKey, oNode, m_strFont);
	xml_GetAttibuteValue(pXmlKeys->m_strSizeKey, oNode, m_fSize);
	xml_GetAttibuteValue(pXmlKeys->m_strBoldKey, oNode, m_nBold);	

	xml_GetAttibuteValue(pXmlKeys->m_strData1_IdKey, oNode, m_strData1_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strData2_IdKey, oNode, m_strData2_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strData3_IdKey, oNode, m_strData3_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strData4_IdKey, oNode, m_strData4_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strData5_IdKey, oNode, m_strData5_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strData6_IdKey, oNode, m_strData6_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strTextFormatKey, oNode, m_strTextFormat);

	return 0;
}

long CRptTemp_Text::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTextKey, oElement, m_strText);
	xml_SetAttributeValue(pXmlKeys->m_strFontKey, oElement, m_strFont);
	xml_SetAttributeValue(pXmlKeys->m_strSizeKey, oElement, m_fSize);
	xml_SetAttributeValue(pXmlKeys->m_strBoldKey, oElement, m_nBold);	

	xml_SetAttributeValue(pXmlKeys->m_strData1_IdKey, oElement, m_strData1_Id);
	xml_SetAttributeValue(pXmlKeys->m_strData2_IdKey, oElement, m_strData2_Id);
	xml_SetAttributeValue(pXmlKeys->m_strData3_IdKey, oElement, m_strData3_Id);
	xml_SetAttributeValue(pXmlKeys->m_strData4_IdKey, oElement, m_strData4_Id);
	xml_SetAttributeValue(pXmlKeys->m_strData5_IdKey, oElement, m_strData5_Id);
	xml_SetAttributeValue(pXmlKeys->m_strData6_IdKey, oElement, m_strData6_Id);
	xml_SetAttributeValue(pXmlKeys->m_strTextFormatKey, oElement, m_strTextFormat);

	return 0;
}

long CRptTemp_Text::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strText);
		BinarySerializeCalLen(oBinaryBuffer, m_strFont);
		BinarySerializeCalLen(oBinaryBuffer, m_fSize);
		BinarySerializeCalLen(oBinaryBuffer, m_nBold);

		BinarySerializeCalLen(oBinaryBuffer, m_strData1_Id);
		BinarySerializeCalLen(oBinaryBuffer, m_strData2_Id);
		BinarySerializeCalLen(oBinaryBuffer, m_strData3_Id);
		BinarySerializeCalLen(oBinaryBuffer, m_strData4_Id);
		BinarySerializeCalLen(oBinaryBuffer, m_strData5_Id);
		BinarySerializeCalLen(oBinaryBuffer, m_strData6_Id);
		BinarySerializeCalLen(oBinaryBuffer, m_strTextFormat);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strText);
		BinarySerializeRead(oBinaryBuffer, m_strFont);
		BinarySerializeRead(oBinaryBuffer, m_fSize);
		BinarySerializeRead(oBinaryBuffer, m_nBold);

		BinarySerializeRead(oBinaryBuffer, m_strData1_Id);
		BinarySerializeRead(oBinaryBuffer, m_strData2_Id);
		BinarySerializeRead(oBinaryBuffer, m_strData3_Id);
		BinarySerializeRead(oBinaryBuffer, m_strData4_Id);
		BinarySerializeRead(oBinaryBuffer, m_strData5_Id);
		BinarySerializeRead(oBinaryBuffer, m_strData6_Id);
		BinarySerializeRead(oBinaryBuffer, m_strTextFormat);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strText);
		BinarySerializeWrite(oBinaryBuffer, m_strFont);
		BinarySerializeWrite(oBinaryBuffer, m_fSize);
		BinarySerializeWrite(oBinaryBuffer, m_nBold);

		BinarySerializeWrite(oBinaryBuffer, m_strData1_Id);
		BinarySerializeWrite(oBinaryBuffer, m_strData2_Id);
		BinarySerializeWrite(oBinaryBuffer, m_strData3_Id);
		BinarySerializeWrite(oBinaryBuffer, m_strData4_Id);
		BinarySerializeWrite(oBinaryBuffer, m_strData5_Id);
		BinarySerializeWrite(oBinaryBuffer, m_strData6_Id);
		BinarySerializeWrite(oBinaryBuffer, m_strTextFormat);
	}
	return 0;
}

void CRptTemp_Text::InitAfterRead()
{
}

BOOL CRptTemp_Text::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRptTemp_Text *p = (CRptTemp_Text*)pObj;

	if(m_strText != p->m_strText)
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

	if(m_strTextFormat != p->m_strTextFormat)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRptTemp_Text::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRptTemp_Text *p = (CRptTemp_Text*)pDest;

	p->m_strText = m_strText;
	p->m_strFont = m_strFont;
	p->m_fSize = m_fSize;
	p->m_nBold = m_nBold;

	p->m_strData1_Id = m_strData1_Id;
	p->m_strData2_Id = m_strData2_Id;
	p->m_strData3_Id = m_strData3_Id;
	p->m_strData4_Id = m_strData4_Id;
	p->m_strData5_Id = m_strData5_Id;
	p->m_strData6_Id = m_strData6_Id;
	p->m_strTextFormat = m_strTextFormat;
	return TRUE;
}

CBaseObject* CRptTemp_Text::Clone()
{
	CRptTemp_Text *p = new CRptTemp_Text();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_Text::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_Text *p = new CRptTemp_Text();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

