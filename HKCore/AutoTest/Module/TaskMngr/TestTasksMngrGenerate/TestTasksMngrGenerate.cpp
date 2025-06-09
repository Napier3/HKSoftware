//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TestTasksMngrGenerate.cpp  CTestTasksMngrGenerate


#include "stdafx.h"
#include "TestTasksMngrGenerate.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTestTasksMngrGenerate* CTestTasksMngrGenerate::g_pTestTasksMngrGenerate = NULL;
long CTestTasksMngrGenerate::g_nTestTasksMngrGenerateRef = 0;

CString CTestTasksMngrGenerate::GetGbxml1()
{
	ASSERT (g_pTestTasksMngrGenerate != NULL);
	return g_pTestTasksMngrGenerate->m_strGbxml1;
}

CString CTestTasksMngrGenerate::GetGbxml2()
{
	ASSERT (g_pTestTasksMngrGenerate != NULL);
	return g_pTestTasksMngrGenerate->m_strGbxml2;
}

CString CTestTasksMngrGenerate::GetGbxml3()
{
	ASSERT (g_pTestTasksMngrGenerate != NULL);
	return g_pTestTasksMngrGenerate->m_strGbxml3;
}

CTestProject* CTestTasksMngrGenerate::GetTestProject()
{
	ASSERT (g_pTestTasksMngrGenerate != NULL);
	return &g_pTestTasksMngrGenerate->m_oTestProject;
}

CDvmDataset* CTestTasksMngrGenerate::GetReportSNGen()
{
	ASSERT (g_pTestTasksMngrGenerate != NULL);
	return g_pTestTasksMngrGenerate->m_pReportSNGen;
}

CDvmDataset* CTestTasksMngrGenerate::GetTaskReportSNGen()
{
	ASSERT (g_pTestTasksMngrGenerate != NULL);
	return g_pTestTasksMngrGenerate->m_pTaskReportSNGen;
}

CExcelReadWrite* CTestTasksMngrGenerate::GetExcelReadWrite()
{
	ASSERT (g_pTestTasksMngrGenerate != NULL);
	return &g_pTestTasksMngrGenerate->m_oExcelWrite;
}

CTestTasksMngrGenerate* CTestTasksMngrGenerate::GetTestTasksMngrGenerate()
{
	ASSERT (g_pTestTasksMngrGenerate != NULL);
	return g_pTestTasksMngrGenerate;
}

CTestTasksMngrGenerate* CTestTasksMngrGenerate::Create()
{
	g_nTestTasksMngrGenerateRef++;

	if (g_nTestTasksMngrGenerateRef == 1)
	{
		CTestTasksMngrGenerateXmlRWKeys::Create();
		CGbXMLKeys::CreatetGbXMLkeys();

		g_pTestTasksMngrGenerate = new CTestTasksMngrGenerate;
	}

	return g_pTestTasksMngrGenerate;
}

void CTestTasksMngrGenerate::Release()
{
	g_nTestTasksMngrGenerateRef--;

	if (g_nTestTasksMngrGenerateRef == 0)
	{
		delete g_pTestTasksMngrGenerate;
		g_pTestTasksMngrGenerate = NULL;
		CTestTasksMngrGenerateXmlRWKeys::Release();
		CGbXMLKeys::Release();

	}
}

CTestTasksMngrGenerate::CTestTasksMngrGenerate()
{
	//初始化属性

	//初始化成员变量
	m_pBatchs = NULL;
	m_pFactorys = NULL;
	m_pReportsMngr = NULL;
	m_pStations = NULL;

	m_pReportSNGen = NULL;
	m_pTaskReportSNGen = NULL;

	CString strFile = TTMG_GetConfigRootPath();
	strFile += _T("nari-rpt-generator.xml");
	OpenXmlFile(strFile, CTestTasksMngrGenerateXmlRWKeys::g_pXmlKeys);

	strFile = _P_GetConfigFilePath(_T("GZExpandData.xml"));
	m_oTestDefine.OpenTestDefineFile(strFile, CGbXMLKeys::TestDefineKey(), CGbXMLKeys::g_pGbXMLKeys);

	m_pReportSNGen = m_oTestDefine.m_pReportSNGen;
	m_pTaskReportSNGen = m_oTestDefine.m_pTaskReportSNGen;
}

CTestTasksMngrGenerate::~CTestTasksMngrGenerate()
{
}

long CTestTasksMngrGenerate::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strGbxml1Key, oNode, m_strGbxml1);
	xml_GetAttibuteValue(pXmlKeys->m_strGbxml2Key, oNode, m_strGbxml2);
	xml_GetAttibuteValue(pXmlKeys->m_strGbxml3Key, oNode, m_strGbxml3);
	return 0;
}

long CTestTasksMngrGenerate::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strGbxml1Key, oElement, m_strGbxml1);
	xml_SetAttributeValue(pXmlKeys->m_strGbxml2Key, oElement, m_strGbxml2);
	xml_SetAttributeValue(pXmlKeys->m_strGbxml3Key, oElement, m_strGbxml3);
	return 0;
}

long CTestTasksMngrGenerate::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strGbxml1);
		BinarySerializeCalLen(oBinaryBuffer, m_strGbxml2);
		BinarySerializeCalLen(oBinaryBuffer, m_strGbxml3);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strGbxml1);
		BinarySerializeRead(oBinaryBuffer, m_strGbxml2);
		BinarySerializeRead(oBinaryBuffer, m_strGbxml3);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strGbxml1);
		BinarySerializeWrite(oBinaryBuffer, m_strGbxml2);
		BinarySerializeWrite(oBinaryBuffer, m_strGbxml3);
	}
	return 0;
}

void CTestTasksMngrGenerate::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == TTMGCLASSID_CTTMGBATCHS)
		{
			m_pBatchs = (CTtmgBatchs*)p;
		}
		else if (nClassID == TTMGCLASSID_CTTMGFACTORYS)
		{
			m_pFactorys = (CTtmgFactorys*)p;
		}
		else if (nClassID == TTMGCLASSID_CTTMGREPORTSMNGR)
		{
			m_pReportsMngr = (CTtmgReportsMngr*)p;
		}
		else if (nClassID == TTMGCLASSID_CTTMGSTATIONS)
		{
			m_pStations = (CTtmgStations*)p;
		}
	}

	if (m_pBatchs == NULL)
	{
		m_pBatchs = (CTtmgBatchs*)AddNewChild(new CTtmgBatchs());
	}

	if (m_pFactorys == NULL)
	{
		m_pFactorys = (CTtmgFactorys*)AddNewChild(new CTtmgFactorys());
	}

	if (m_pReportsMngr == NULL)
	{
		m_pReportsMngr = (CTtmgReportsMngr*)AddNewChild(new CTtmgReportsMngr());
	}

	if (m_pStations == NULL)
	{
		m_pStations = (CTtmgStations*)AddNewChild(new CTtmgStations());
	}

}

BOOL CTestTasksMngrGenerate::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CTestTasksMngrGenerate *p = (CTestTasksMngrGenerate*)pObj;

	if(m_strGbxml1 != p->m_strGbxml1)
	{
		return FALSE;
	}

	if(m_strGbxml2 != p->m_strGbxml2)
	{
		return FALSE;
	}

	if(m_strGbxml3 != p->m_strGbxml3)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTestTasksMngrGenerate::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTestTasksMngrGenerate *p = (CTestTasksMngrGenerate*)pDest;

	p->m_strGbxml1 = m_strGbxml1;
	p->m_strGbxml2 = m_strGbxml2;
	p->m_strGbxml3 = m_strGbxml3;
	return TRUE;
}

CBaseObject* CTestTasksMngrGenerate::Clone()
{
	CTestTasksMngrGenerate *p = new CTestTasksMngrGenerate();
	Copy(p);
	return p;
}

BOOL CTestTasksMngrGenerate::CanPaste(UINT nClassID)
{
	if (nClassID == TTMGCLASSID_CTTMGREPORTSMNGR)
	{
		return TRUE;
	}

	if (nClassID == TTMGCLASSID_CTTMGFACTORYS)
	{
		return TRUE;
	}

	if (nClassID == TTMGCLASSID_CTTMGSTATIONS)
	{
		return TRUE;
	}

	if (nClassID == TTMGCLASSID_CTTMGBATCHS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CTestTasksMngrGenerate::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCTtmgReportsMngrKey)
	{
		pNew = new CTtmgReportsMngr();
	}
	else if (strClassID == pXmlKeys->m_strCTtmgFactorysKey)
	{
		pNew = new CTtmgFactorys();
	}
	else if (strClassID == pXmlKeys->m_strCTtmgStationsKey)
	{
		pNew = new CTtmgStations();
	}
	else if (strClassID == pXmlKeys->m_strCTtmgBatchsKey)
	{
		pNew = new CTtmgBatchs();
	}

	return pNew;
}

CExBaseObject* CTestTasksMngrGenerate::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == TTMGCLASSID_CTTMGREPORTSMNGR)
	{
		pNew = new CTtmgReportsMngr();
	}
	else if (nClassID == TTMGCLASSID_CTTMGFACTORYS)
	{
		pNew = new CTtmgFactorys();
	}
	else if (nClassID == TTMGCLASSID_CTTMGSTATIONS)
	{
		pNew = new CTtmgStations();
	}
	else if (nClassID == TTMGCLASSID_CTTMGBATCHS)
	{
		pNew = new CTtmgBatchs();
	}

	return pNew;
}


void CTestTasksMngrGenerate::Generate()
{
	
}

