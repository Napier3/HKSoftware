//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SetsFileXml_Remark.cpp  CSetsFileXml_Remark


#include "stdafx.h"
#include "SetsFileXml_Remark.h"
#include "..\..\..\..\..\Module\API\Xmd5.h"
#include "..\..\..\..\..\Module\API\StringConvert\String_Gbk_To_Utf8.h"
#include "..\..\..\..\..\Module\xml\XmlRW_Pugi.h"
#include "..\..\..\..\..\Module\xml\PugiXML\pugixml.hpp"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSetsFileXml_Remark::CSetsFileXml_Remark()
{
	//初始化属性
	m_nItemNum = 0;
	m_nUpdate = -1;
	m_strMd5_Cal = "";

	m_pNode = NULL;
	//初始化成员变量
}

CSetsFileXml_Remark::~CSetsFileXml_Remark()
{
}

long CSetsFileXml_Remark::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	CXmlRWNode_Pugi *pNode = (CXmlRWNode_Pugi *)&oNode;
	m_pNode = &(pNode->m_oPugiXmlNode);

	xml_GetAttibuteValue(pXmlKeys->m_strItemNumKey, oNode, m_nItemNum);
	xml_GetAttibuteValue(pXmlKeys->m_strMd5Key, oNode, m_strmd5);
	xml_GetAttibuteValue(pXmlKeys->m_strupDateKey, oNode, m_nUpdate);
	return 0;
}

long CSetsFileXml_Remark::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strItemNumKey, oElement, m_nItemNum);

	if (m_nUpdate > 0)
	{
		xml_SetAttributeValue(pXmlKeys->m_strupDateKey, oElement, m_nUpdate);
	}

	xml_SetAttributeValue(pXmlKeys->m_strMd5Key, oElement, m_strmd5);
	
	return 0;
}

long CSetsFileXml_Remark::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nItemNum);
		BinarySerializeCalLen(oBinaryBuffer, m_strmd5);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nItemNum);
		BinarySerializeRead(oBinaryBuffer, m_strmd5);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nItemNum);
		BinarySerializeWrite(oBinaryBuffer, m_strmd5);
	}
	return 0;
}

void CSetsFileXml_Remark::InitAfterRead()
{
}

BOOL CSetsFileXml_Remark::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSetsFileXml_Remark *p = (CSetsFileXml_Remark*)pObj;

	if(m_nItemNum != p->m_nItemNum)
	{
		return FALSE;
	}

	if(m_strmd5 != p->m_strmd5)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSetsFileXml_Remark::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSetsFileXml_Remark *p = (CSetsFileXml_Remark*)pDest;

	p->m_nItemNum = m_nItemNum;
	p->m_strmd5 = m_strmd5;
	return TRUE;
}

CBaseObject* CSetsFileXml_Remark::Clone()
{
	CSetsFileXml_Remark *p = new CSetsFileXml_Remark();
	Copy(p);
	return p;
}

CBaseObject* CSetsFileXml_Remark::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSetsFileXml_Remark *p = new CSetsFileXml_Remark();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSetsFileXml_Remark::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSETSFILEXML_RI)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSetsFileXml_Remark::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSetFileXmlParseXmlRWKeys *pXmlKeys = (CSetFileXmlParseXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSetsFileXml_RIKey)
	{
		pNew = new CSetsFileXml_RI();
	}

	return pNew;
}

CExBaseObject* CSetsFileXml_Remark::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSETSFILEXML_RI)
	{
		pNew = new CSetsFileXml_RI();
	}

	return pNew;
}


void CSetsFileXml_Remark::GetValStringTotal_V110_Remark(CString &strValTotal)
{
	strValTotal.Empty();
	CString strVal;

	POS pos = GetHeadPosition();
	CSetsFileXml_RI *pRI = NULL;

	while (pos != NULL)
	{
		pRI = (CSetsFileXml_RI *)GetNext(pos);
		strVal = pRI->m_strVal;
		strValTotal.AppendFormat(_T("%s"), strVal);
	}
	//去掉空格、制表符、回车符、换行符
	// 	strValTotal.Replace(_T(" "), _T(""));
	// 	strValTotal.Replace(_T("\t"), _T(""));
	// 	strValTotal.Replace(_T("\r"), _T(""));
	// 	strValTotal.Replace(_T("\n"), _T(""));
	strValTotal = RemoveOffsetChars(strValTotal);
}

void CSetsFileXml_Remark::GetMd5_ForCal(CString &strMd5, const CString &strValTotal, BOOL bReCalMd5,BOOL bIsUpdateMD5)
{
	if (!bReCalMd5)
	{
		//不需要重复计算时，判断已经计算过，则直接返回
		if (m_strMd5_Cal.GetLength() > 0)
		{
			strMd5 = m_strMd5_Cal;
			return;
		}
	}

	char *pchVal = NULL;
	char *pszUtf8 = NULL;
	int nSize = CString_to_char(strValTotal,&pchVal);
	int nDestLen = 0;
	gbk_to_utf8_r((unsigned char*)pchVal, nSize, (unsigned char**)&pszUtf8, &nDestLen, 0);

	CXMD5 oMD5;
	oMD5.update(pszUtf8, nDestLen);
	string str = oMD5.toString();
	strMd5 = str.c_str();
	m_strMd5_Cal = strMd5;
	if(bIsUpdateMD5)
	{
		m_strmd5 = strMd5;
	}

	delete []pchVal;
	delete []pszUtf8;
}
