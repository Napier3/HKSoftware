#pragma once

#include "SetsFileToolInterface.h"

class CStesFileExcelTool :public CFileToolInterface
{
public:
	CStesFileExcelTool(void);
	~CStesFileExcelTool(void);

	static CFileToolInterface* Create()
	{
		return new CStesFileExcelTool();
	}


	virtual BOOL ExportFile(const CString &strFile, LPDISPATCH lpDispatch=NULL);
	virtual BOOL ImportFile(const CString &strFile, LPDISPATCH lpDispatch=NULL);

};

