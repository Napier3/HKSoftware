#include "StdAfx.h"
#include "ByteBlocks.h"
#include "ByteBlock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CByteBlocks::CByteBlocks(void)
{
}

CByteBlocks::~CByteBlocks(void)
{
}

CExBaseObject* CByteBlocks::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strByteBlockKey)
	{
		return new CByteBlock();
	}

	return NULL;
}

CExBaseObject* CByteBlocks::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{

	return NULL;
}

//�ֽڿ�Ľ���		����Ľ�������������ִ�н���
DWORD CByteBlocks::Parse(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)
{
	POS pos = GetHeadPosition();
	CByteBlock *p = NULL;
	DWORD nResult = 0;

	while (pos != NULL)
	{
		p = (CByteBlock*)GetNext(pos);
		nResult = p->Parse(oPkgBufPos, pDetail);

		if (IsPpParseError(nResult))
		{
			break;
		}
	}

	return nResult;
}

//�ֽڿ��ƥ��		��Ҫ���ڽ���
DWORD CByteBlocks::Match(PACKAGEBUFFERPOS &oPkgBufPos)
{
	POS pos = GetHeadPosition();
	CByteBlock *p = NULL;
	DWORD nResult = 0;

	while (pos != NULL)
	{
		p = (CByteBlock*)GetNext(pos);
		nResult = p->Match(oPkgBufPos);

		if (!IsPpParseMatch(nResult))
		{
			break;
		}
	}

	return nResult;
}


DWORD CByteBlocks::Produce(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)	
{
	POS pos = GetHeadPosition();
	CByteBlock *p = NULL;
	DWORD nResult = 0;

	while (pos != NULL)
	{
		p = (CByteBlock*)GetNext(pos);
		nResult = p->Produce(oPkgBufPos, pDetail);

		if (!IsPpParseMatch(nResult))
		{
			break;
		}
	}

	return nResult;
}

//////////////////////////////////////////////////////////////////////////
//���� ��¡ �Ա�
BOOL CByteBlocks::IsEqualOwn(CBaseObject* pObj)
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

	if (m_strXmlKey != ((CByteBlocks*)pObj)->m_strXmlKey)
	{
		return FALSE;
	}

	return CExBaseList::IsEqualOwn(pObj);
}

CBaseObject* CByteBlocks::Clone()
{
	CByteBlocks* pNew = new CByteBlocks();
	Copy(pNew);
	return pNew;
}

BOOL CByteBlocks::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CByteBlocks*)pDest)->m_strXmlKey = m_strXmlKey;

	return CExBaseList::CopyOwn(pDest);
}

void CByteBlocks::GetAllVariables(CExBaseList &oDestList)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if ((p->GetClassID() & PPCLASSID_BYTEBLOCK) == PPCLASSID_BYTEBLOCK)
		{
			((CByteBlock*)p)->GetAllVariables(oDestList);
		}
	}
}

void CByteBlocks::GetBufferPos(long &nBegin, long &nEnd)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseObject *pFirst = NULL;
	CExBaseObject *pLast = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if ( PpIsByteBlock(p->GetClassID()))
		{
			if (pFirst == NULL)
			{
				pFirst = p;
			}
			else
			{
				pLast = p;
			}
		}
	}

	if (pLast == NULL)
	{
		pLast = pFirst;
	}

	if (pFirst == NULL)
	{
		nBegin = -1;
		nEnd = -1;
		return;
	}

	long nTemp = 0;
	((CByteBlock*)pFirst)->GetBufferPos(nBegin, nTemp);
	((CByteBlock*)pLast)->GetBufferPos(nTemp, nEnd);
}

void CByteBlocks::GetFirstAndLastByteBlock(CByteBlock **ppFirst, CByteBlock **ppLast)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseObject *pFirst = NULL;
	CExBaseObject *pLast = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if ( PpIsByteBlock(p->GetClassID()))
		{
			if (pFirst == NULL)
			{
				pFirst = p;
			}
			else
			{
				pLast = p;
			}
		}
	}

	if (pLast == NULL)
	{
		pLast = pFirst;
	}

	*ppFirst = (CByteBlock*)pFirst;
	*ppLast = (CByteBlock*)pLast;
}

