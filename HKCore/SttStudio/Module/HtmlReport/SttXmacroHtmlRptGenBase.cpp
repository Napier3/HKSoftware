#include "SttXmacroHtmlRptGenBase.h"
#include "../UI/Webkit/SttReportViewHtml.h"


CSttXmacroHtmlRptGenBase::CSttXmacroHtmlRptGenBase()
{

}

CSttXmacroHtmlRptGenBase::~CSttXmacroHtmlRptGenBase()
{
 
}

void CSttXmacroHtmlRptGenBase::GetHtml(CString &strHtmlData)
{
	strHtmlData = (char*)m_pHtmlBuffer->GetBuffer();
}

