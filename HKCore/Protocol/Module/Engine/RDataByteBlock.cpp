#include "StdAfx.h"
#include "RDataByteBlock.h"
#include "BbVariable.h"
#include "PpDataBinds.h"
#include "PpScript.h"
#include "PpEngineBaseApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CRDataByteBlock::CRDataByteBlock(void)
{
	
}

CRDataByteBlock::~CRDataByteBlock(void)
{
}

long CRDataByteBlock::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDataByteBlock::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;
}

long CRDataByteBlock::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataByteBlock::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	return 0;
}

long CRDataByteBlock::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{

	return 0;
}


CExBaseObject* CRDataByteBlock::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	return CDataByteBlock::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
	
	return NULL;
}

CExBaseObject* CRDataByteBlock::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	
	return NULL;
}

DWORD CRDataByteBlock::Parse(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)
{
	DWORD nResult = 0;

	// 获取字节块字节长度
	m_nLength = GetByteBlockLength();
	AllocBuffer(m_nLength);

	if (m_pBuffer == NULL)
	{
		return PpParseError();
	}

	// 从缓存区获取数据
	nResult = GetByteBlockData(oPkgBufPos, m_pBuffer);

	if (!IsPpParseMatch(nResult) || IsPpParseError(nResult))
	{
		FreeBuffer();
		return nResult;
	}

	// 解析该字节块数据
	if (m_pScript != NULL && m_nLength > 0)
	{
		m_pScript->Run();

		if (m_pScript->m_dwReturn == 0)
		{// 如果脚本解析错误
			FreeBuffer();
			return PpParseError();
		}
	}

	// 克隆该数据
	CByteBlock *pByteBlock = NULL;
	pByteBlock = (CByteBlock*)Clone();
	pByteBlock->SetBuffer(DetachBuffer());

	// 将该数据添加到pDetail中
	pByteBlock->SetParent(pDetail);
	pDetail->AddTail(pByteBlock);

	return nResult;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CRDataByteBlock::IsEqualOwn(CBaseObject* pObj)
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

	if (m_strValue != ((CRDataByteBlock*)pObj)->m_strValue)
	{
		return FALSE;
	}

	return CDataByteBlock::IsEqualOwn(pObj);
}

CBaseObject* CRDataByteBlock::Clone()
{
	CRDataByteBlock* pNew = new CRDataByteBlock();
	Copy(pNew);
	return pNew;
}

BOOL CRDataByteBlock::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CRDataByteBlock*)pDest)->m_strValue = m_strValue;

	return CDataByteBlock::CopyOwn(pDest);
}