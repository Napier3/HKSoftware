#include "StdAfx.h"
#include "byteblock.h"
#include "RByteBlock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CRByteBlock::CRByteBlock(void)
{
}

CRByteBlock::~CRByteBlock(void)
{
}

long CRByteBlock::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CByteBlock::XmlReadOwn(oNode, pXmlRWKeys);
	return 0;
}

long CRByteBlock::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CByteBlock::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	return 0;
}

long CRByteBlock::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

CExBaseObject* CRByteBlock::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	return CByteBlock::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
}

CExBaseObject*  CRByteBlock::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{	
	return 0;
}

//字节块的解析		具体的解析在派生类中执行解析
DWORD CRByteBlock::Parse(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)
{
	return CByteBlock::Parse(oPkgBufPos, pDetail);
}

//字节块的匹配		主要用于解析
DWORD CRByteBlock::Match(PACKAGEBUFFERPOS &oPkgBufPos)
{
	return CByteBlock::Match(oPkgBufPos);
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CRByteBlock::IsEqualOwn(CBaseObject* pObj)
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

	return CByteBlock::IsEqualOwn(pObj);
}

CBaseObject* CRByteBlock::Clone()
{
	CRByteBlock* pNew = new CRByteBlock();
	Copy(pNew);
	return pNew;
}

BOOL CRByteBlock::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	return CByteBlock::CopyOwn(pDest);
}
