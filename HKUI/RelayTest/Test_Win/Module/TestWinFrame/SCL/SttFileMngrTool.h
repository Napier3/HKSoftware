#ifndef STTFILEMNGRTOOL_H
#define STTFILEMNGRTOOL_H


#include "../../../../../Module/DataMngr/DataGroup.h"


class CSttFileMngrTool
{
	

public:
	CSttFileMngrTool();
	~CSttFileMngrTool();	
	
public:
	
	BOOL OpenConfigFile(CString strFilePath = _T(""));
	CString GetFolderPath(const CString &strTypeId);
	BOOL IsFolderPath(const CString &strPath,CString &strFilePath);

	CDataGroup m_oFileMngr;

};

extern CSttFileMngrTool g_oFileMngrTool;


#endif // STTFILEMNGRTOOL_H
