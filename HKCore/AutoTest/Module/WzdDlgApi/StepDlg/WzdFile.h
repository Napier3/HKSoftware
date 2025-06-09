#pragma once

#include "../../../Module/XfileMngrBase/XFile.h"


class CWzdFile :public CXFile
{
public:
	CWzdFile(void);
	~CWzdFile(void);

	CXFile* m_pFile;

public:
	virtual long ValCmp(CBaseObject* pRightObj);

	BOOL ProssData(CString sParentPath);

	BOOL CheckValue(CString sZZMS, CString sZZXH);
	BOOL CheckTime(COleDateTime sTime, COleDateTime eTime);

};
