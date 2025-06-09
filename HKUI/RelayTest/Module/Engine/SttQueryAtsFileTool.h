#pragma once

#include "../SttCmd/SttSysState.h"
#include "../SttCmd/SttAtsCmd.h"

class CSttQueryAtsFileTool
{
public:
	CSttQueryAtsFileTool();
	virtual ~CSttQueryAtsFileTool();

public:
    void QueryAtsFile(CSttAtsCmd &oAtsCmd, CSttSysState &oSysState);

protected:
    void QueryFiles(const CString &strPath, const CString &strFilesID, const CString &strFilter, CSttParas *pSttParas, CSttParas *pRetParas, const CString &strNotHas);
};
