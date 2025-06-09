#include "SttXHtmlRptGenFactoryBase.h"
#include "../UI/Webkit/SttReportViewHtml.h"

CSttXHtmlRptGenFactoryBase *g_theHtmlRptGenFactory = NULL;

CSttXHtmlRptGenFactoryBase::CSttXHtmlRptGenFactoryBase()
{
	g_theHtmlRptGenFactory = this;
	m_pDvmDevice = NULL;
	m_pDataTypes = NULL;
	m_pGuideBook = NULL;
	m_pCurrHtmRptGen = NULL;

	m_oHtmlBuffer.Init();
	m_oHtmlBuffer.AllocBuffer(HTML_BUFFER_SIZE_INIT);//1024*1024
	memset(m_oHtmlBuffer.GetDataBuffer(), 0, HTML_BUFFER_SIZE_INIT);
}

CSttXHtmlRptGenFactoryBase::~CSttXHtmlRptGenFactoryBase()
{
	if (m_pCurrHtmRptGen != NULL)
	{
		delete m_pCurrHtmRptGen;
	}
}

CSttXmacroHtmlRptGenBase* CSttXHtmlRptGenFactoryBase::CreateHtmlRptGen(const CString &strMacroID, 	CSttItems* pSttItems)
{
	if (m_strMacroID == strMacroID)
	{
		return m_pCurrHtmRptGen;
	}

	if (m_pCurrHtmRptGen != NULL)
	{
		delete m_pCurrHtmRptGen;
	}

	m_strMacroID = strMacroID;
	m_pCurrHtmRptGen = Create(strMacroID);

	if (m_pCurrHtmRptGen == NULL)
	{
		return m_pCurrHtmRptGen;
	}

	m_oHtmlBuffer.ZeroBuffer();
	m_pCurrHtmRptGen->m_pDvmDevice = m_pDvmDevice;
	m_pCurrHtmRptGen->SetDataTypes(m_pDataTypes);
	m_pCurrHtmRptGen->m_pSttItems = pSttItems;
	m_pCurrHtmRptGen->SetHtmlBuffer(&m_oHtmlBuffer);

	return m_pCurrHtmRptGen;
}


CSttXmacroHtmlRptGenBase* CSttXHtmlRptGenFactoryBase::CreateHtmlRptGen(const CString &strMacroID)
{
	return CreateHtmlRptGen(strMacroID, NULL);
}

