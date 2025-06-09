//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TtmgReport.cpp  CTtmgReport


#include "stdafx.h"
#include "TtmgReport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CTtmgReport::CTtmgReport()
{
	//初始化属性

	//初始化成员变量
}

CTtmgReport::~CTtmgReport()
{
	
}

long CTtmgReport::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CTtmgReport::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CTtmgReport::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

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

void CTtmgReport::InitAfterRead()
{
}

BOOL CTtmgReport::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTtmgReport *p = (CTtmgReport*)pObj;

	return TRUE;
}

BOOL CTtmgReport::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CTtmgReport *p = (CTtmgReport*)pDest;

	return TRUE;
}

CBaseObject* CTtmgReport::Clone()
{
	CTtmgReport *p = new CTtmgReport();
	Copy(p);
	return p;
}

void CTtmgReport::InitReport(CXFile *pXFile)
{
	m_pXFile = pXFile;
	m_strReportType = pXFile->GetFolderPath();

	long nPos = m_strReportType.Find('\\');

	if (m_strReportType.Right(1) == _T("\\"))
	{
		m_strReportType = m_strReportType.Left(m_strReportType.GetLength() - 1);
	}

	nPos = m_strReportType.ReverseFind('\\');

	if (nPos > 0)
	{
		m_strReportType = m_strReportType.Left(nPos);
	}
	else
	{
		m_strReportType.Empty();
	}
}

