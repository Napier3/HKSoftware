#include "StdAfx.h"
#include "PpParsePackage.h"
#include "ProtocolXmlRWKeys.h"
#include "PpScript.h"
#include "BbVariables.h"
#include "RBbDataSets.h"
#include "RByteBlock.h"
#include "PpTtPackage.h"
#include "PpPackageDetail.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPpParsePackage::CPpParsePackage(void)
{
	m_pPackageDetailRef = NULL;
	m_pBufferPos = NULL;
	m_nRequiredLen = -1;
}

CPpParsePackage::~CPpParsePackage(void)
{
	
}

long CPpParsePackage::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPpPackage::XmlReadOwn(oNode, pXmlRWKeys);

	CProtocolXmlRWKeys *pKeys = (CProtocolXmlRWKeys*)pXmlRWKeys;
	//xml_GetAttibuteValue(pKeys->m_stT_IDKey, oNode, m_strTID);

	return 0;

}
long CPpParsePackage::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPpPackage::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	return 0;
}

CExBaseObject* CPpParsePackage::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataSetsKey)
	{
		return new CRBbDataSets();
	}

	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strByteBlockKey)
	{
		return new CRByteBlock();
	}

	return CPpPackage::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
}

CExBaseObject* CPpParsePackage::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{

	return NULL;
}

//字节块的解析		具体的解析在派生类中执行解析
DWORD CPpParsePackage::Parse(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)
{
	RunInitScript();

	m_pPackageDetailRef = pDetail;
	m_pBufferPos = &oPkgBufPos;

	//ASSERT (m_pTtPackage != NULL);
	DWORD nResult = 0;

	//报文头解析
	if (m_pTtPackage != NULL && m_pTtPackage->m_pTtHead != NULL)
	{
		nResult = m_pTtPackage->m_pTtHead->Parse(oPkgBufPos, pDetail);
		if (IsPpParseError(nResult))
		{
			m_pPackageDetailRef = NULL;
			return nResult;
		}
	}

	//报文体解析
	POS pos = GetHeadPosition();
	CByteBlock *pByteBlock = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pByteBlock = (CByteBlock*)GetNext(pos);
		nClassID = pByteBlock->GetClassID();

		if (nClassID == PPCLASSID_RBYTEBLOCK || nClassID == PPCLASSID_RBBDATASETS)
		{
			nResult = pByteBlock->Parse(oPkgBufPos, pDetail);

			if (IsPpParseError(nResult))
			{
				break;
			}
		}
	}

	//报文尾解析
	if (m_pTtPackage != NULL && m_pTtPackage->m_pTtTail != NULL)
	{
		nResult = m_pTtPackage->m_pTtTail->Parse(oPkgBufPos, pDetail);
		if (IsPpParseError(nResult))
		{
			m_pPackageDetailRef = NULL;
			return nResult;
		}
	}

	pDetail->m_strID = m_strID;
	pDetail->m_strName = m_strName;

	//拷贝帧的变量、数据接口
	CPpPackageDetail *pPkgDetail = (CPpPackageDetail*)pDetail;
	CExBaseList *pList = pPkgDetail->m_pVariables;
	CloneAppendInterfaceVariable(*pList);
	pPkgDetail->InitOwnAllVariables(TRUE);
	m_pPackageDetailRef = NULL;

	RunEndScript();

	return nResult;
}

void CPpParsePackage::CloneAppendInterfaceVariable(CExBaseList &oDestList)
{
	if (m_pVariables != NULL)
	{
		m_pVariables->CloneAppend(oDestList);
	}

	if (m_pDataInterface != NULL)
	{
		m_pDataInterface->CloneAppend(oDestList);
	}

	if (m_pTtPackage != NULL)
	{
		if (m_pTtPackage->m_pTtVariables != NULL)
		{
			m_pTtPackage->m_pTtVariables->CloneAppend(oDestList);
		}

		if (m_pTtPackage->m_pDataInterface != NULL)
		{
			m_pTtPackage->m_pDataInterface->CloneAppend(oDestList);
		}
	}
}

//字节块的匹配		主要用于解析
DWORD CPpParsePackage::Match(PACKAGEBUFFERPOS &oPkgBufPos)
{
	POS pos = GetHeadPosition();
	CByteBlock *pByteBlock = NULL;
	PACKAGEBUFFERPOS oPkgBufPosBk = oPkgBufPos;  //匹配时，先备份位置
	DWORD nResult = 0;
	UINT nClassID = 0;

	//处理空报文异常
	long nBbCount = 0;

	while (pos != NULL)
	{
		pByteBlock = (CByteBlock*)GetNext(pos);
		nClassID = pByteBlock->GetClassID();

		if (nClassID == PPCLASSID_RBYTEBLOCK)
		{// ASDU帧匹配的时候，仅仅匹配字节块数据，数据总集不参与匹配
			nResult = pByteBlock->Match(oPkgBufPos);
			nBbCount++;

			if (!IsPpParseMatch(nResult))
			{
				//nResult = pByteBlock->Match(oPkgBufPos);
				break;
			}
		}		
	}

	oPkgBufPos = oPkgBufPosBk;

	if (nBbCount == 0)
	{
		nResult = PpParseNotWholeMatch();
	}

	return nResult;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CPpParsePackage::IsEqualOwn(CBaseObject* pObj)
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

	return CPpPackage::IsEqualOwn(pObj);
}

CBaseObject* CPpParsePackage::Clone()
{
	CPpParsePackage* pNew = new CPpParsePackage();
	Copy(pNew);

	return pNew;
}

BOOL CPpParsePackage::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	return CPpPackage::CopyOwn(pDest);
}

