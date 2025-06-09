#include <string>
#include "libxml/parser.h"
#include "libxml/xmlschemas.h"
#include "../ResultsRec.h"
#include "../ResultRec.h"

#define XML_CHECK_TYPE_DOM               _T("DOM")

class Cxml2SchemaCheckTool
{
public:
	Cxml2SchemaCheckTool();
	virtual ~Cxml2SchemaCheckTool();

	static void my_structured_error_handler(void *userData, const xmlError *error);
	void error_handle(const xmlError *error);
	BOOL validateXML(CString strxsdFilePath, CString strxmlFilePath);
	BOOL StartCheckXml2ValidNormal();
	int StartCheckXml2ValidFromThread(CString strXsdPath, CString strXmlPath);
	void InitCheck(CString strCheckType,CResultsRec *pResultsRec);
	BOOL m_nSchemaCheckFinished;

protected:
	void FreeSchemaCheckThread();
	static UINT SchemaCheckThread(LPVOID pParam);
	void FormatString(CString &strText, const char *strFormat, ...);

	CWinThread *m_pXml2CheckThread;
	CString m_strXsdPath;
	CString m_strXmlPath;

	CResultsRec *m_pResultsRec;
	long m_nErrorIndex;
	long m_nWarningIndex;
	long m_nFatalErrorIndex;
	CString m_strDomType;


};