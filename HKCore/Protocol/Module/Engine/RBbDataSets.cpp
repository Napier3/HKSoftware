#include "StdAfx.h"
#include "RBbDataSets.h"
#include "RBbDataSet.h"
#include "RByteBlock.h"
#include "PpParsePackage.h"
#include "PpPackageDetail.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CRBbDataSets::CRBbDataSets(void)
{

}

CRBbDataSets::~CRBbDataSets(void)
{

}

long CRBbDataSets::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CBbDataSets::XmlReadOwn(oNode,pXmlRWKeys);

	return 0;
}

long CRBbDataSets::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CBbDataSets::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	return 0;
}

long CRBbDataSets::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{

	return 0;
}


CExBaseObject* CRBbDataSets::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataSetKey)
	{
		return new CRBbDataSet();
	}

	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strByteBlockKey)
	{
		return new CRByteBlock();
	}

	return NULL;
}

CExBaseObject* CRBbDataSets::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	
	return NULL;
}

DWORD CRBbDataSets::Parse(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)
{// 数据总集解析
	POS pos = GetHeadPosition();
	POS posBegin = NULL, posEnd = NULL;
	CByteBlock *pByteBlock = NULL;
	PACKAGEBUFFERPOS oPkgBufPosBk;

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
		else if (nClassID == PPCLASSID_RBBDATASET)
		{
			oPkgBufPosBk = oPkgBufPos;

// 			if (pDetail != NULL)
// 			{
// 				((CPpPackageDetail*)pDetail)->m_pPkgBufPos = &oPkgBufPos;
// 			}

			nResult = pByteBlock->Parse(oPkgBufPosBk, pDetail);
			if (!IsPpParseError(nResult))
			{
				oPkgBufPos = oPkgBufPosBk;
				//break;
			}
			else
			{
				oPkgBufPosBk = oPkgBufPos;
				break;
			}

			if (IsPpParseError(nResult))
			{
				return nResult;
			}
			//break;
		} 			
 	}

	return nResult;

// 	// 遍历数据集
// 	int iDataSetCount = 1;
// 	CBbVariable* pVar = NULL;
// 	CExBaseList* pList = NULL;
// 	pList = (CExBaseList*)GetAncestor(PPCLASSID_PPPARSEPACKGE);
// 	
// 	if(pList != NULL)
// 	{
// 		CPpParsePackage* pPkg = (CPpParsePackage*)pList;
// 		pVar = (CBbVariable*)pPkg->FindVariableByID(L"DataSetCount");
// 		if (pVar != NULL)
// 		{
// 			iDataSetCount = _wtoi(pVar->m_strValue);
// 		}
// 	}
// 
// 	posEnd = posBegin;
// 	while (pos != NULL)
// 	{
// 		posEnd = pos;
// 		pByteBlock = (CByteBlock*)GetNext(pos);
// 		nClassID = pByteBlock->GetClassID();
// 
// 		if (nClassID == PPCLASSID_RBYTEBLOCK)
// 		{
// 			break;
// 		}		
// 	}
// 
// 	oPkgBufPosBk = oPkgBufPos;
// 	for (int iIndex=0; iIndex<iDataSetCount; iIndex++)
// 	{
// 		pos = posBegin;
// 		
// 		while (pos != NULL)
// 		{
// 			pByteBlock = (CByteBlock*)GetNext(pos);
// 			nClassID = pByteBlock->GetClassID();
// 
// 			if (nClassID == PPCLASSID_RBBDATASET)
// 			{
// 				nResult = pByteBlock->Parse(oPkgBufPosBk, pDetail);
// 				if (!IsPpParseError(nResult))
// 				{
// 					oPkgBufPos = oPkgBufPosBk;
// 					break;
// 				}
// 				else
// 				{
// 					oPkgBufPosBk = oPkgBufPos;
// 				}
// 			}		
// 		}
// 		if (IsPpParseError(nResult))
// 		{
// 			return nResult;
// 		}
// 	}
// 
// 	// 遍历最后的字节块
// 	pos = posEnd;
// 	while (pos != NULL)
// 	{
// 		pByteBlock = (CByteBlock*)GetNext(pos);
// 		nClassID = pByteBlock->GetClassID();
// 
// 		if (nClassID == PPCLASSID_RBYTEBLOCK)
// 		{
// 			nResult = pByteBlock->Parse(oPkgBufPos, pDetail);
// 			if (IsPpParseError(nResult))
// 			{
// 				return nResult;
// 			}
// 		}		
// 	}
// 
// 	return nResult;
}
//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CRBbDataSets::IsEqualOwn(CBaseObject* pObj)
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

	return CBbDataSets::IsEqualOwn(pObj);
}

CBaseObject* CRBbDataSets::Clone()
{
	CRBbDataSets* pNew = new CRBbDataSets();
	Copy(pNew);
	return pNew;
}

BOOL CRBbDataSets::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	return CBbDataSets::CopyOwn(pDest);
}