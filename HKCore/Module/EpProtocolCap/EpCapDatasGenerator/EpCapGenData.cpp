//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapGenData.cpp  CEpCapGenData


#include "stdafx.h"
#include "EpCapGenData.h"
#include "..\..\Module\MemBuffer\BinaryTextConvert.h"

CEpCapGenData::CEpCapGenData()
{
	//初始化属性

	//初始化成员变量
}

CEpCapGenData::~CEpCapGenData()
{
}

char g_pszEpCapGenDataBuffer[4096];
BYTE g_byteEpCapGenDataBuffer[4096];
long CEpCapGenData::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapDatasGeneratorXmlRWKeys *pXmlKeys = (CEpCapDatasGeneratorXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strCapIDKey, oNode, m_dwCapID);
	xml_GetAttibuteValue(pXmlKeys->m_strCapTimeKey, oNode, m_dwCapTime);
	xml_GetAttibuteValue(pXmlKeys->m_strCapMsKey, oNode, m_dwCapMs);
	xml_GetAttibuteValue(pXmlKeys->m_strAddrSrcKey, oNode, m_dwAddrSrc);
	xml_GetAttibuteValue(pXmlKeys->m_strAddrDstKey, oNode, m_dwAddrDst);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_dwType);
	xml_GetAttibuteValue(pXmlKeys->m_strDataKey, oNode, m_strFrameData);

	BYTE *pBuffer = NULL;
	long nDataLength = 0;
	GetFrameDataBuffer(&pBuffer, &nDataLength);

	return 0;
}

void CEpCapGenData::GetFrameDataBuffer(BYTE **ppBufer, long *pnLength)
{
	*ppBufer = m_oBuffer.GetBuffer();

	if (*ppBufer == NULL)
	{
		CBinaryTextConvert oConvert;
		oConvert.SetText(m_strFrameData);
		oConvert.ConvertTextToBinary(FALSE);
		long nLen = 0;
		BYTE *pHex = NULL;
		oConvert.GetBinaryRef(&pHex, nLen);

		m_oBuffer.SetBufferLength(nLen);
		BYTE *p = m_oBuffer.GetBuffer();
		memcpy(p, pHex, nLen);
		m_oBuffer.SetDataLength(nLen);
		m_strFrameData.Empty();
	}

	*ppBufer = m_oBuffer.GetBuffer();
	*pnLength = m_oBuffer.GetBufferLength();
}

long CEpCapGenData::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpCapDatasGeneratorXmlRWKeys *pXmlKeys = (CEpCapDatasGeneratorXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strCapIDKey, oElement, m_dwCapID);
	xml_SetAttributeValue(pXmlKeys->m_strCapTimeKey, oElement, m_dwCapTime);
	xml_SetAttributeValue(pXmlKeys->m_strCapMsKey, oElement, m_dwCapMs);
	xml_SetAttributeValue(pXmlKeys->m_strAddrSrcKey, oElement, m_dwAddrSrc);
	xml_SetAttributeValue(pXmlKeys->m_strAddrDstKey, oElement, m_dwAddrDst);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_dwType);
//	xml_SetAttributeValue(pXmlKeys->m_strDataKey, oElement, m_strData);
	return 0;
}

long CEpCapGenData::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_dwCapID);
		BinarySerializeCalLen(oBinaryBuffer, m_dwCapTime);
		BinarySerializeCalLen(oBinaryBuffer, m_dwCapMs);
		BinarySerializeCalLen(oBinaryBuffer, m_dwAddrSrc);
		BinarySerializeCalLen(oBinaryBuffer, m_dwAddrDst);
		BinarySerializeCalLen(oBinaryBuffer, m_dwType);
//		BinarySerializeCalLen(oBinaryBuffer, m_strData);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_dwCapID);
		BinarySerializeRead(oBinaryBuffer, m_dwCapTime);
		BinarySerializeRead(oBinaryBuffer, m_dwCapMs);
		BinarySerializeRead(oBinaryBuffer, m_dwAddrSrc);
		BinarySerializeRead(oBinaryBuffer, m_dwAddrDst);
		BinarySerializeRead(oBinaryBuffer, m_dwType);
//		BinarySerializeRead(oBinaryBuffer, m_strData);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_dwCapID);
		BinarySerializeWrite(oBinaryBuffer, m_dwCapTime);
		BinarySerializeWrite(oBinaryBuffer, m_dwCapMs);
		BinarySerializeWrite(oBinaryBuffer, m_dwAddrSrc);
		BinarySerializeWrite(oBinaryBuffer, m_dwAddrDst);
		BinarySerializeWrite(oBinaryBuffer, m_dwType);
//		BinarySerializeWrite(oBinaryBuffer, m_strData);
	}
	return 0;
}

void CEpCapGenData::InitAfterRead()
{
}

BOOL CEpCapGenData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEpCapGenData *p = (CEpCapGenData*)pObj;

	if(m_dwCapID != p->m_dwCapID)
	{
		return FALSE;
	}

	if(m_dwCapTime != p->m_dwCapTime)
	{
		return FALSE;
	}

	if(m_dwCapMs != p->m_dwCapMs)
	{
		return FALSE;
	}

	if(m_dwAddrSrc != p->m_dwAddrSrc)
	{
		return FALSE;
	}

	if(m_dwAddrDst != p->m_dwAddrDst)
	{
		return FALSE;
	}

	if(m_dwType != p->m_dwType)
	{
		return FALSE;
	}

// 	if(m_strData != p->m_strData)
// 	{
// 		return FALSE;
// 	}
// 
	return TRUE;
}

BOOL CEpCapGenData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpCapGenData *p = (CEpCapGenData*)pDest;

	p->m_dwCapID = m_dwCapID;
	p->m_dwCapTime = m_dwCapTime;
	p->m_dwCapMs = m_dwCapMs;
	p->m_dwAddrSrc = m_dwAddrSrc;
	p->m_dwAddrDst = m_dwAddrDst;
	p->m_dwType = m_dwType;
//	p->m_strData = m_strData;
	return TRUE;
}

CBaseObject* CEpCapGenData::Clone()
{
	CEpCapGenData *p = new CEpCapGenData();
	Copy(p);
	return p;
}

