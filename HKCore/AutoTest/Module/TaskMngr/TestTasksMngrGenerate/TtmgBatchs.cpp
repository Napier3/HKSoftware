//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TtmgBatchs.cpp  CTtmgBatchs


#include "stdafx.h"
#include "TtmgBatchs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CTtmgBatchs::CTtmgBatchs()
{
	//初始化属性
	m_nTotalReports = 0;

	//初始化成员变量
	m_nCurrBatchGenIndex = -1;
	m_pCurrBatch = NULL;
	m_nCurrBatchRptGenIndex = -1;
}

CTtmgBatchs::~CTtmgBatchs()
{
}

long CTtmgBatchs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CTtmgBatchs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CTtmgBatchs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CTtmgBatchs::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CTtmgBatch *p = NULL;
	m_nTotalReports = 0;
	long nIndex = 0;

	while (pos != NULL)
	{
		p = (CTtmgBatch *)GetNext(pos);
		m_nTotalReports += p->m_nNum;

		POS posRpt = p->GetHeadPosition();
		CTtmgBatchReport *pRpt = NULL;

		while (posRpt != NULL)
		{
			pRpt = (CTtmgBatchReport *)p->GetNext(posRpt);
			pRpt->m_nRptIndex = nIndex;
			nIndex++;
		}
	}
}

BOOL CTtmgBatchs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CTtmgBatchs *p = (CTtmgBatchs*)pObj;

	return TRUE;
}

BOOL CTtmgBatchs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTtmgBatchs *p = (CTtmgBatchs*)pDest;

	return TRUE;
}

CBaseObject* CTtmgBatchs::Clone()
{
	CTtmgBatchs *p = new CTtmgBatchs();
	Copy(p);
	return p;
}

BOOL CTtmgBatchs::CanPaste(UINT nClassID)
{
	if (nClassID == TTMGCLASSID_CTTMGBATCH)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CTtmgBatchs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCTtmgBatchKey)
	{
		pNew = new CTtmgBatch();
	}

	return pNew;
}

CExBaseObject* CTtmgBatchs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == TTMGCLASSID_CTTMGBATCH)
	{
		pNew = new CTtmgBatch();
	}

	return pNew;
}

void CTtmgBatchs::Generate(CThreadProgressInterface *pGenThread)
{
	
}

CTtmgBatch* CTtmgBatchs::GetFirstBatch()
{
	m_nCurrBatchRptGenIndex = -1;
	m_nCurrBatchGenIndex = 0;
	m_pCurrBatch = (CTtmgBatch*)GetAtIndex(m_nCurrBatchGenIndex);
	return m_pCurrBatch;
}

CTtmgBatch* CTtmgBatchs::GetNextBatch()
{
	if (m_nCurrBatchGenIndex == -1)
	{
		m_nCurrBatchGenIndex = 0;
	}
	else
	{
		m_nCurrBatchGenIndex++;
	}

	m_nCurrBatchRptGenIndex = -1;
	m_pCurrBatch = (CTtmgBatch*)GetAtIndex(m_nCurrBatchGenIndex);
	return m_pCurrBatch;
}

CTtmgBatchReport* CTtmgBatchs::GetFirstBatchReport()
{
	m_nCurrBatchRptGenIndex = 0;
	m_pCurrBatchReport = (CTtmgBatchReport*)m_pCurrBatch->GetAtIndex(m_nCurrBatchRptGenIndex);
	return m_pCurrBatchReport;
}

CTtmgBatchReport* CTtmgBatchs::GetNextBatchReport()
{
	if (m_nCurrBatchRptGenIndex == -1)
	{
		m_nCurrBatchRptGenIndex = 0;
	}
	else
	{
		m_nCurrBatchRptGenIndex++;
	}

	while (TRUE)
	{
		m_pCurrBatchReport = (CTtmgBatchReport*)m_pCurrBatch->GetAtIndex(m_nCurrBatchRptGenIndex);

		if (m_pCurrBatchReport == NULL)
		{
			break;
		}

		if (m_pCurrBatchReport->m_nHasGenerated == 0)
		{
			break;
		}

		m_nCurrBatchRptGenIndex++;
	}

	return m_pCurrBatchReport;
}

