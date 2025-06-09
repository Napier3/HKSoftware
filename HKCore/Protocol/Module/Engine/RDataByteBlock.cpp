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

	// ��ȡ�ֽڿ��ֽڳ���
	m_nLength = GetByteBlockLength();
	AllocBuffer(m_nLength);

	if (m_pBuffer == NULL)
	{
		return PpParseError();
	}

	// �ӻ�������ȡ����
	nResult = GetByteBlockData(oPkgBufPos, m_pBuffer);

	if (!IsPpParseMatch(nResult) || IsPpParseError(nResult))
	{
		FreeBuffer();
		return nResult;
	}

	// �������ֽڿ�����
	if (m_pScript != NULL && m_nLength > 0)
	{
		m_pScript->Run();

		if (m_pScript->m_dwReturn == 0)
		{// ����ű���������
			FreeBuffer();
			return PpParseError();
		}
	}

	// ��¡������
	CByteBlock *pByteBlock = NULL;
	pByteBlock = (CByteBlock*)Clone();
	pByteBlock->SetBuffer(DetachBuffer());

	// ����������ӵ�pDetail��
	pByteBlock->SetParent(pDetail);
	pDetail->AddTail(pByteBlock);

	return nResult;
}

//////////////////////////////////////////////////////////////////////////
//���� ��¡ �Ա�
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