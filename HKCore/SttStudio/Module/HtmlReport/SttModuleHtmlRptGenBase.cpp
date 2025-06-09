#include "SttModuleHtmlRptGenBase.h"
#include "../UI/Webkit/SttReportViewHtml.h"


CSttModuleHtmlRptGenBase::CSttModuleHtmlRptGenBase()
{
	m_pHtmlBuffer = &m_oHtmlBuffer;
	m_oHtmlBuffer.Init();
	m_oHtmlBuffer.AllocBuffer(HTML_BUFFER_SIZE_INIT);//1024*1024
	memset(m_oHtmlBuffer.GetDataBuffer(), 0, HTML_BUFFER_SIZE_INIT);

	m_bHtmlGened = false;
}

CSttModuleHtmlRptGenBase::~CSttModuleHtmlRptGenBase()
{
 
}

void CSttModuleHtmlRptGenBase::OpenDataTypesFile(const CString &strFile)
{
	if (strFile.GetLength() <= 7)
	{
		return;
	}

	FreeDataTypes();
	m_pDataTypes = new CDataTypes();
	m_pDataTypes->Open(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void CSttModuleHtmlRptGenBase::FreeDataTypes()
{
	if (m_bDataTypesCreate)
	{
		if (m_pDataTypes != NULL)
		{
			delete m_pDataTypes;
		}
	}

	m_pDataTypes = NULL;
}
