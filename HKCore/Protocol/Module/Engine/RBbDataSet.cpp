#include "StdAfx.h"
#include "RBbDataSet.h"
#include"RByteBlock.h"
#include "RBbdata.h"
#include "PpParsePackage.h"
#include "PpPackageDetail.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CRBbDataSet::CRBbDataSet(void)
{
}

CRBbDataSet::~CRBbDataSet(void)
{

}

long CRBbDataSet::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CBbDataSet::XmlReadOwn(oNode,pXmlRWKeys);

	return 0;
}

long CRBbDataSet::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CBbDataSet::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	return 0;
}

long CRBbDataSet::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{

	return 0;
}


CExBaseObject* CRBbDataSet::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strByteBlockKey)
	{
		return new CRByteBlock();
	}

	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataKey)
	{
		return new CRBbData();
	}

	return NULL;
}

CExBaseObject* CRBbDataSet::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	
	return NULL;
}

DWORD CRBbDataSet::Parse(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)
{// 数据集解析
	POS pos = GetHeadPosition();
	POS posBegin, posEnd;
	CByteBlock *pByteBlock = NULL;
	PACKAGEBUFFERPOS oPkgBufPosBk;

	if (pos == NULL)
	{
		return 0;
	}

// 	if (pDetail != NULL)
// 	{
// 		((CPpPackageDetail*)pDetail)->m_pPkgBufPos = &oPkgBufPos;
// 	}

	DWORD nResult = 0;
	UINT nClassID = 0;

	// 遍历字节块
	while (pos != NULL)
	{
		posBegin = pos;
		pByteBlock = (CByteBlock*)GetNext(pos);
		nClassID = pByteBlock->GetClassID();

		if (nClassID == PPCLASSID_RBYTEBLOCK)
		{
			nResult = pByteBlock->Parse(oPkgBufPos, pDetail);

			if (IsPpParseError(nResult))
			{
				return nResult;
			}
		}
		else if (nClassID == PPCLASSID_RBBDATA)
		{
			break;
		} 			
	}

	// 遍历数据
	long nDataCount = 0;
	CBbVariable* pVar = NULL;
	CExBaseList* pList = NULL;
	pList = (CExBaseList*)GetAncestor(PPCLASSID_PPPARSEPACKGE);

	if(pList != NULL)
	{
		CPpParsePackage* pPkg = (CPpParsePackage*)pList;
		pPkg->GetVariableValue(m_strDataCountMax, nDataCount);
// 		pVar = (CBbVariable*)pPkg->FindVariableByID(L"DataCount");
// 		if (pVar != NULL)
// 		{
// 			nDataCount = _wtoi(pVar->m_strValue);
// 		}
	}

	posEnd = posBegin;
	while (pos != NULL)
	{
		posEnd = pos;
		pByteBlock = (CByteBlock*)GetNext(pos);
		nClassID = pByteBlock->GetClassID();

		if (nClassID == PPCLASSID_RBYTEBLOCK)
		{
			break;
		}		
	}

	oPkgBufPosBk = oPkgBufPos;
	BOOL bParseDataFinish = FALSE;

	for (int iIndex=0; iIndex<nDataCount; iIndex++)
	{
		if (bParseDataFinish)
		{
			break;
		}

		pos = posBegin;

		while (pos != NULL)
		{
			pByteBlock = (CByteBlock*)GetNext(pos);
			nClassID = pByteBlock->GetClassID();

			if (nClassID == PPCLASSID_RBBDATA)
			{
				CRBbData *pDataDetail = new CRBbData();
                pDataDetail->m_strName.Format(_T("%s-%d"), pByteBlock->m_strName.GetString(), iIndex+1);
				pDataDetail->m_strID = pByteBlock->m_strID;
				nResult = pByteBlock->Parse(oPkgBufPosBk, pDataDetail);

				if ((nResult & PPS_LOOP_BREAK) == PPS_LOOP_BREAK)
				{
					delete pDataDetail;
					bParseDataFinish = TRUE;
				}
				else
				{
					pDetail->AddNewChild(pDataDetail);
				}

				if (!IsPpParseError(nResult))
				{
					oPkgBufPos = oPkgBufPosBk;
					break;
				}
				else
				{
					oPkgBufPosBk = oPkgBufPos;
				}
			}		
		}

		if (IsPpParseError(nResult))
		{
			return nResult;
		}
	}

	// 遍历最后的字节块
	pos = posEnd;
	while (pos != NULL)
	{
		pByteBlock = (CByteBlock*)GetNext(pos);
		nClassID = pByteBlock->GetClassID();

		if (nClassID == PPCLASSID_RBYTEBLOCK)
		{
			nResult = pByteBlock->Parse(oPkgBufPos, pDetail);
			if (IsPpParseError(nResult))
			{
				return nResult;
			}
		}		
	}

	return nResult;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CRBbDataSet::IsEqualOwn(CBaseObject* pObj)
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

	return CBbDataSet::IsEqualOwn(pObj);
}

CBaseObject* CRBbDataSet::Clone()
{
	CRBbDataSet* pNew = new CRBbDataSet();
	Copy(pNew);
	return pNew;
}

BOOL CRBbDataSet::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	return CBbDataSet::CopyOwn(pDest);
}
