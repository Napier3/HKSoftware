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

//�ֽڿ�Ľ���		����Ľ�������������ִ�н���
DWORD CRByteBlock::Parse(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)
{
	return CByteBlock::Parse(oPkgBufPos, pDetail);
}

//�ֽڿ��ƥ��		��Ҫ���ڽ���
DWORD CRByteBlock::Match(PACKAGEBUFFERPOS &oPkgBufPos)
{
	return CByteBlock::Match(oPkgBufPos);
}

//////////////////////////////////////////////////////////////////////////
//���� ��¡ �Ա�
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
