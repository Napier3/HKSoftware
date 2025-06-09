#include "StdAfx.h"
#include "BbDataRange.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CBbDataRange::CBbDataRange(void)
{
	m_strID="";
	m_strValue="";
	m_pValueBuffer = NULL;
	m_nValueBufferLength = -1;
}

CBbDataRange::~CBbDataRange(void)
{
	FreeValBuffer();
}


long CBbDataRange::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CProtocolXmlRWKeys *pKeys = (CProtocolXmlRWKeys*)pXmlRWKeys;

	m_strValue = oNode.Gettext();

	xml_GetAttibuteValue(pKeys->m_strTypeKey,oNode,m_strType);

	return 0;
}



long CBbDataRange::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	CProtocolXmlRWKeys *pKeys=(CProtocolXmlRWKeys*)pXmlRWKeys;

	oElement.Puttext(m_strValue);

	xml_SetAttributeValue(pKeys->m_strTypeKey,oElement,m_strType);

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CBbDataRange::IsEqualOwn(CBaseObject* pObj)
{
	ASSERT (pObj == NULL);

	if (pObj == NULL)
	{
		return FALSE;
	}

	if (this == pObj)
	{
		return TRUE;
	}

	if (m_strValue != ((CBbDataRange*)pObj)->m_strValue)
	{
		return FALSE;
	}

	if (m_strID != ((CBbDataRange*)pObj)->m_strID)
	{
		return FALSE;
	}

	return CExBaseObject::IsEqualOwn(pObj);
}

CBaseObject* CBbDataRange::Clone()
{
	CBbDataRange* pNew = new CBbDataRange();
	Copy(pNew);
	return pNew;
}

BOOL CBbDataRange::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CBbDataRange*)pDest)->m_strType = m_strType;
	((CBbDataRange*)pDest)->m_strValue = m_strValue;

	return CExBaseObject::CopyOwn(pDest);
}

void CBbDataRange::InitAfterRead()
{
	InitValueBuffer();
}

void CBbDataRange::InitValueBuffer()
{
	if (m_nValueBufferLength != -1)
	{
		return;
	}

	if (m_strType != PPRANGE_CONST_HEX)
	{
		return;
	}

	m_nValueBufferLength = m_strValue.GetLength();
	FreeValBuffer();

	if (m_nValueBufferLength > 0)
	{
		m_pValueBuffer = new BYTE[m_nValueBufferLength*2+2];
		CString_to_char(m_strValue, (char*)m_pValueBuffer);
		BYTE *p = m_pValueBuffer;
		BYTE *pEnd = p + m_nValueBufferLength;
		BYTE *pDest = p;

		while (p < pEnd)
		{
			HexToByte(p, pDest);
			pDest++;
			p+=2;
		}

		*pDest = 0;
		m_nValueBufferLength /= 2;
	}
	else
	{
		m_nValueBufferLength = 0;
	}
}

BYTE* CBbDataRange::GetValueBuffer(long &nLen)
{
	nLen = m_nValueBufferLength;

	return m_pValueBuffer;
}
