#pragma once

#include "ScriptFunc_Engine.h"


/////////////////////////////////////////////////////////////////////////////

// CFileTrans
#define MAX_SECTION_NUM       6144

class CFileTrans
{
public:
	CFileTrans();
	~CFileTrans();

public:
	int GetCurSection() { return m_nCurSection; }
	int AddNewSection() { m_nCurSection++; return m_nCurSection; }
	int GetSectionLength(int nSection) { return m_uSectionLen[nSection]; }
	BYTE* GetSectionData(int nSection) { return m_pSectionData[nSection]; }
	void AddSectionData(int nSection, BYTE* pData, int nLength);

protected:
	unsigned int m_uSectionLen[MAX_SECTION_NUM];  // 节长度
	BYTE* m_pSectionData[MAX_SECTION_NUM];        // 节数据指针
	int m_nCurSection;                            // 当前节
};

//=========================================================================

void script_AddSectionData(CTScriptSingleVM *pXvm,long nIndex, long nBytes);
void script_Fis103SaveRCDFile(CTScriptSingleVM *pXvm,const char* strPath, long nFileNameLen);			//保存录波文件
void script_Fis103SaveCommonFile(CTScriptSingleVM *pXvm,const char* strPath, long nFileNameLen);			//保存普通文件



long script_CreateFile(CTScriptSingleVM *pXvm, const char *pszPath, const char* pszFileName);
long script_WriteFile(CTScriptSingleVM *pXvm, long nIndex, long nBytes);
long script_CloseFile(CTScriptSingleVM *pXvm);

long script_OpenRcdFile(CTScriptSingleVM *pXvm, const char *pszPathPath, const char *pszFileName);
long script_ReadRcdFile(CTScriptSingleVM *pXvm, long nIndex, long nBytes);
long script_GetFileLength(CTScriptSingleVM *pXvm);
long script_GetFileLeftLength(CTScriptSingleVM *pXvm);
