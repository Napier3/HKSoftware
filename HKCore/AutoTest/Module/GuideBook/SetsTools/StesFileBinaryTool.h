#pragma once

#include "SetsFileToolInterface.h"

class CStesFileBinaryTool :public CFileToolInterface
{
public:
	CStesFileBinaryTool(void);
	~CStesFileBinaryTool(void);

	static CFileToolInterface* Create()
	{
		return new CStesFileBinaryTool();
	}

	virtual BOOL ExportFile(const CString &strFile, LPDISPATCH lpDispatch=NULL);
	virtual BOOL ImportFile(const CString &strFile, LPDISPATCH lpDispatch=NULL);
};

