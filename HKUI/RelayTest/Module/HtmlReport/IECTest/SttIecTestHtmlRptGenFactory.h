#ifndef _CSttIecTestHtmlRptGenFactory_H
#define _CSttIecTestHtmlRptGenFactory_H

#include "../SttXHtmlRptGenFactoryBase.h"

class CSttIecTestHtmlRptGenFactory : public CSttXHtmlRptGenFactoryBase
{
public:
    CSttIecTestHtmlRptGenFactory();
    virtual ~CSttIecTestHtmlRptGenFactory();

public:
	void OpenDataTypesFile(CString strFilePath = _T(""));
	void OpenDataTypesByMacroFileID(const CString &strMacroFileID);

protected:
	void FreeDataTypes();
};


#endif // _CSttIecTestHtmlRptGenFactory_H
