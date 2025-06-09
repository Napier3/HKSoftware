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
	unsigned int m_uSectionLen[MAX_SECTION_NUM];  // �ڳ���
	BYTE* m_pSectionData[MAX_SECTION_NUM];        // ������ָ��
	int m_nCurSection;                            // ��ǰ��
};

//=========================================================================

void script_AddSectionData(CTScriptSingleVM *pXvm,long nIndex, long nBytes);
void script_Fis103SaveRCDFile(CTScriptSingleVM *pXvm,const char* strPath, long nFileNameLen);			//����¼���ļ�
void script_Fis103SaveCommonFile(CTScriptSingleVM *pXvm,const char* strPath, long nFileNameLen);			//������ͨ�ļ�



long script_CreateFile(CTScriptSingleVM *pXvm, const char *pszPath, const char* pszFileName);
long script_WriteFile(CTScriptSingleVM *pXvm, long nIndex, long nBytes);
long script_CloseFile(CTScriptSingleVM *pXvm);

long script_OpenRcdFile(CTScriptSingleVM *pXvm, const char *pszPathPath, const char *pszFileName);
long script_ReadRcdFile(CTScriptSingleVM *pXvm, long nIndex, long nBytes);
long script_GetFileLength(CTScriptSingleVM *pXvm);
long script_GetFileLeftLength(CTScriptSingleVM *pXvm);
