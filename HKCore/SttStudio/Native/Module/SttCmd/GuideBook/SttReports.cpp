#include "stdafx.h"
#include "SttReports.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CSttReports::CSttReports()
{

}

CSttReports::~CSttReports()
{
}

long CSttReports::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

long CSttReports::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

long CSttReports::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

BOOL CSttReports::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);

	if(pDesObj == this)
	{
		return TRUE;
	}

	CExBaseList::CopyOwn(pDesObj);

	return 0;
}

CBaseObject* CSttReports::Clone()
{
	CSttReports* pSttReports = new CSttReports();
	Copy(pSttReports);
	return pSttReports;
}

CBaseObject* CSttReports::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttReports *p = new CSttReports();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

CExBaseObject* CSttReports::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID == CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strCSttReportKey)
	{
		return new CSttReport();
	}

	return NULL;
}

CExBaseObject* CSttReports::CreateNewChild(long nClassID)
{
	if(nClassID == STTCMDCLASSID_REPORT)
	{
		return new CSttReport();
	}

	return NULL;
}

void CSttReports::AddReport(CDataGroup *pDataGroup)
{
	CSttReport *p = (CSttReport*)GetHead();

	if (p == NULL)
	{
		p = new CSttReport();
		AddNewChild(p);
	}

	p->InitReport(pDataGroup);
}

