//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TtmgReports.cpp  CTtmgReports


#include "stdafx.h"
#include "TtmgReports.h"
#include "..\..\TCtrlCntrDefine.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CTtmgReports::CTtmgReports()
{
	//初始化属性

	//初始化成员变量
	m_pXFileMngr = NULL;
}

CTtmgReports::~CTtmgReports()
{
	if (m_pXFileMngr != NULL)
	{
		delete m_pXFileMngr;
		m_pXFileMngr = NULL;
	}
}

long CTtmgReports::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strPathKey, oNode, m_strPath);
	return 0;
}

long CTtmgReports::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strPathKey, oElement, m_strPath);
	return 0;
}

long CTtmgReports::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strPath);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strPath);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strPath);
	}
	return 0;
}

void CTtmgReports::InitAfterRead()
{
}

BOOL CTtmgReports::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTtmgReports *p = (CTtmgReports*)pObj;

	if(m_strPath != p->m_strPath)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTtmgReports::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CTtmgReports *p = (CTtmgReports*)pDest;

	p->m_strPath = m_strPath;
	return TRUE;
}

CBaseObject* CTtmgReports::Clone()
{
	CTtmgReports *p = new CTtmgReports();
	Copy(p);
	return p;
}

BOOL CTtmgReports::CanPaste(UINT nClassID)
{
	if (nClassID == TTMGCLASSID_CTTMGREPORT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CTtmgReports::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCTtmgReportKey)
	{
		pNew = new CTtmgReport();
	}

	return pNew;
}

CExBaseObject* CTtmgReports::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == TTMGCLASSID_CTTMGREPORT)
	{
		pNew = new CTtmgReport();
	}

	return pNew;
}

void CTtmgReports::InitAllReports()
{
	if (m_pXFileMngr != NULL)
	{
		return;
	}
	
	m_pXFileMngr = new CXFileMngr();
	CString strPath = TTMG_GetConfigRootPath();
	strPath += m_strPath;

	CXFileType *pXFileType = m_pXFileMngr->AddFileType(g_strGuideBookBinaryPostfix, g_strGuideBookBinaryPostfix, _T(""), _T(""));
	pXFileType->AddNewPostfix(g_strGuideBookBinaryPostfix, g_strGuideBookBinaryPostfix);

	m_pXFileMngr->SetOnllySearchMainTypeFile(TRUE);
	m_pXFileMngr->InitByXFileTypes();
	m_pXFileMngr->SetLibraryPath(strPath);

	InitAllReports(m_pXFileMngr);
}

void CTtmgReports::InitAllReports(CXFolder *pXFolder)
{
	POS pos = pXFolder->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (xfile_IsFolder(p->GetClassID()))
		{
			InitAllReports((CXFolder*)p);
		}
		else
		{
			CTtmgReport *pReport  = new CTtmgReport();
			AddNewChild(pReport);
			pReport->InitReport((CXFile*)p);
		}
	}
}

CTtmgReport* CTtmgReports::GetReport()
{
	long nIndex = rand();
	nIndex = nIndex % m_nCount;

	CTtmgReport *pReport = NULL;

	pReport = (CTtmgReport *)GetAtIndex(nIndex);

	return pReport;
}

CTtmgReport* CTtmgReports::FindReportByID(const CString &strID)
{
	POS pos = GetHeadPosition();
	CTtmgReport *p = NULL, *pFind = NULL;
	long nLen = strID.GetLength();

	while (pos != NULL)
	{
		p = (CTtmgReport *)GetNext(pos);

		if (p->m_pXFile->m_strID.Left(nLen) == strID)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

