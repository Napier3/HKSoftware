#include "StdAfx.h"
#include "PpTtPackage.h"
#include "BbDataRange.h"
#include "PpPackage.h"
#include "ByteBlocks.h"
#include "PpTemplate.h"
#include "../XLanguageResourcePp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPpTtPackage::CPpTtPackage(void)
{
	m_pTtVariables = NULL;
	m_pTtHead = NULL;
	m_pTtTail = NULL;
	m_bIsWholeMatch = FALSE;
	m_pDataInterface = NULL;
	m_nPkgLen = 0;
	m_nPkgNum = 0;
	m_nParseRef = 0;
}

CPpTtPackage::~CPpTtPackage(void)
{
	EmptyParsePackages();
	m_oAllVariables.RemoveAll();
}

CExBaseObject* CPpTtPackage::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CByteBlocks *pBbs = NULL;

	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPackageHeadKey)
	{
		ASSERT (m_pTtHead == NULL);
		pBbs = new CByteBlocks();
		pBbs->m_strXmlKey = CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPackageHeadKey;
		m_pTtHead = pBbs;
	}

	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPackageTailKey)
	{
		ASSERT (m_pTtTail == NULL);
		pBbs = new CByteBlocks();
		pBbs->m_strXmlKey = CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPackageTailKey;
		m_pTtTail = pBbs;
	}
	
	if(strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strVariablesKey)
	{
#ifdef UNICODE
		m_pTtVariables = new CBbVariables(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strVariablesKey);
#else
		m_pTtVariables = new CBbVariables(CString(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strVariablesKey));
#endif
		return m_pTtVariables;
	}
	
	if(strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataInterfaceKey)
	{
#ifdef UNICODE
		m_pDataInterface = new CBbVariables(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataInterfaceKey);
#else
		m_pDataInterface = new CBbVariables(CString(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataInterfaceKey));
#endif
		return m_pDataInterface;
	}

	return pBbs;
}

CExBaseObject* CPpTtPackage::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	return NULL;
}

//字节块的解析		具体的解析在派生类中执行解析
long CPpTtPackage::Parse(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)
{
	return 0;
}

//字节块的匹配		主要用于解析
DWORD CPpTtPackage::MatchHeadAndTail(PACKAGEBUFFERPOS &oPkgBufPos)
{
	//考虑m_pTtHead、m_pTtTail都等于NULL的情况，返回匹配成功
	if (m_pTtHead == NULL && m_pTtTail == NULL)
	{
		return PpParseMatch();
	}

	//匹配头
	DWORD nResult = 0;

	if (m_pTtHead != NULL)
	{
		nResult = m_pTtHead->Match(oPkgBufPos);
	}

	if (!IsPpParseMatch(nResult))
	{
		return nResult;
	}

	//匹配尾
// 	if (m_pTtTail != NULL)
// 	{
// 		nResult = m_pTtTail->Match(oPkgBufPos);
// 	}
// 
// 	if (!IsPpParseMatch(nResult))
// 	{
// 		return nResult;
// 	}

	m_bIsWholeMatch = TRUE;

	return nResult;
}

//匹配报文		遍历解析帧进行匹配
CExBaseObject* CPpTtPackage::MatchPackge(PACKAGEBUFFERPOS &oPkgBufPos)
{
	POS pos = m_listPackages.GetHeadPosition();
	CPpPackage *p = NULL;
	CPpPackage *pMatch = NULL;
	long nResult = 0;

	PACKAGEBUFFERPOS oPkgBufPosBk = oPkgBufPos;
	while (pos != NULL)
	{
		p = (CPpPackage*)m_listPackages.GetNext(pos);
		if (p->GetClassID() == PPCLASSID_PPPARSEPACKGE)
		{
			if (p->m_strName == g_sLangTxt_SureValueASDU/*_T("响应带确认写定值ASDU10")*/)
			{
				nResult = p->Match(oPkgBufPos);
			}
			else
			{
				nResult = p->Match(oPkgBufPos);
			}

			if (IsPpParseWholeMatch(nResult))
			{
				pMatch = p;
				break;
			}
			oPkgBufPos = oPkgBufPosBk;
		}		
	}

	return pMatch;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CPpTtPackage::IsEqualOwn(CBaseObject* pObj)
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

	if (m_bIsWholeMatch != ((CPpTtPackage*)pObj)->m_bIsWholeMatch)
	{
		return FALSE;
	}

	return CExBaseList::IsEqualOwn(pObj);
}

CBaseObject* CPpTtPackage::Clone()
{
	CPpTtPackage* pNew = new CPpTtPackage();
	Copy(pNew);
	return pNew;
}

BOOL CPpTtPackage::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CPpTtPackage*)pDest)->m_bIsWholeMatch = m_bIsWholeMatch;

	return CExBaseList::CopyOwn(pDest);
}

void CPpTtPackage::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject* pObj = NULL;

	UINT nClassID;

	while(pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		switch(nClassID)
		{
		case PPCLASSID_BYTEBLOCKS:
			{
				CByteBlocks* pByteBlocks = (CByteBlocks*)pObj;
				if(pByteBlocks->m_strXmlKey == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPackageHeadKey)
				{
					m_pTtHead = pByteBlocks;
				}
				else if(pByteBlocks->m_strXmlKey == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPackageTailKey)
				{
					m_pTtTail = pByteBlocks;
				}
			}
			break;
		case PPCLASSID_BBVARIABLES:
			{
				CBbVariables *pVariables = (CBbVariables*)pObj;

				if (pVariables->m_strXmlKey == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataInterfaceKey)
				{
					m_pDataInterface = pVariables;
				}
				else if (pVariables->m_strXmlKey == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strVariablesKey)
				{
					m_pTtVariables = pVariables;
				}
				else
				{

				}
			}

			break;
		}
	}

	InitOwnAllVariables();
}

void CPpTtPackage::GetDataInterface(CExBaseList &oDestList)
{
	if (m_pDataInterface != NULL)
	{
		m_pDataInterface->Append(oDestList);
	}
}

void CPpTtPackage::GetAllVariables(CExBaseList &oDestList)
{
	if (m_pDataInterface != NULL)
	{
		oDestList.Append(*m_pDataInterface);
	}

	if (m_pTtVariables != NULL)
	{
		oDestList.Append(*m_pTtVariables);
	}

	if (m_pTtHead != NULL)
	{
		m_pTtHead->GetAllVariables(oDestList);
	}

	if (m_pTtTail != NULL)
	{
		m_pTtTail->GetAllVariables(oDestList);
	}
}

long CPpTtPackage::InitOwnAllVariables()
{
	m_oAllVariables.RemoveAll();
	GetAllVariables(m_oAllVariables);
	return m_oAllVariables.GetCount();
}


CBbVariable* CPpTtPackage::FindVariableByName(const CString &strName)
{
	CBbVariable *p = (CBbVariable*)m_oAllVariables.FindByName(strName);
	return p;
}

CBbVariable* CPpTtPackage::FindVariableByID(const CString &strID)
{
	CBbVariable *p = (CBbVariable*)m_oAllVariables.FindByID(strID);
	return p;
}

/*
2010-12-06 添加
*/
BOOL CPpTtPackage::AddSystemVariables()
{
	
	return TRUE;
}
