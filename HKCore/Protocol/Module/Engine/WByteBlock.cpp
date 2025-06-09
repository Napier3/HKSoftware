#include "StdAfx.h"
#include "WByteBlock.h"
#include "ByteBlock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CWByteBlock::CWByteBlock(void)
{
	 m_nPackOrder=0;
	 m_nLength = 1;
}

CWByteBlock::~CWByteBlock(void)
{
}

long CWByteBlock::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CByteBlock::XmlReadOwn(oNode, pXmlRWKeys);
	CProtocolXmlRWKeys *pKeys = (CProtocolXmlRWKeys*)pXmlRWKeys;


	return 0;
}

long CWByteBlock::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CByteBlock::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	CProtocolXmlRWKeys *pKeys = (CProtocolXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CWByteBlock::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{

	return 0;
}


CExBaseObject* CWByteBlock::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	return CByteBlock::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
}

CExBaseObject* CWByteBlock::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	
	return NULL;
}

DWORD CWByteBlock::Produce(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)
{
	return CByteBlock::Produce(oPkgBufPos, pDetail);
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CWByteBlock::IsEqualOwn(CBaseObject* pObj)
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

	if (m_nPackOrder != ((CWByteBlock*)pObj)->m_nPackOrder)
	{
		return FALSE;
	}

	return CByteBlock::IsEqualOwn(pObj);
}

CBaseObject* CWByteBlock::Clone()
{
	CWByteBlock* pNew = new CWByteBlock();
	Copy(pNew);
	return pNew;
}

BOOL CWByteBlock::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	return CByteBlock::CopyOwn(pDest);
}