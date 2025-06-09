//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XLangFolder.cpp  CXLangFolder


#include "stdafx.h"
#include "XLangFolder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXLangFolder::CXLangFolder()
{
	//初始化属性

	//初始化成员变量
}

CXLangFolder::~CXLangFolder()
{
}

//添加语言资源文件夹中的所有文件对象，此函数用于总的文件管理对象列表
void CXLangFolder::AppendLangFile(CXLangFolder *pSrcFolder)
{
	CXLangFile *p = NULL;
	POS pos = pSrcFolder->GetHeadPosition();
	CXLangFile *pNew = NULL;

	while (pos != NULL)
	{
		p = (CXLangFile *)pSrcFolder->GetNext(pos);
		
		if (FindLangFile(p->m_strID) == NULL)
		{
			pNew = (CXLangFile *)(CExBaseObject*)p->Clone();
			pNew->SetRefXLanguage(TRUE);
			AddNewChild(pNew);
		}
	}
}

void CXLangFolder::AppendLangFile(CXLangFile *pFile)
{
	if (FindLangFile(pFile->m_strID) == NULL)
	{
		CXLangFile *pNew = (CXLangFile*)pFile->Clone();
		pNew->SetRefXLanguage(TRUE);
		AddNewChild(pNew);
	}
}

CXLangFile* CXLangFolder::FindLangFile(const CString &strFile)
{
	CXLangFile *p = NULL, *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CXLangFile *)GetNext(pos);

#ifdef _UNICODE
	if (wcsicmp(p->m_strID, strFile) == 0)
#else
	if (stricmp(p->m_strID, strFile) == 0)
#endif
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}


long CXLangFolder::FindLangFileIndex(const CString &strFile)
{
	long nIndexFind = -1;
	long nIndex = 0;
	CXLangFile *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CXLangFile *)GetNext(pos);

#ifdef _UNICODE
		if (wcsicmp(p->m_strID, strFile) == 0)
#else
		if (stricmp(p->m_strID, strFile) == 0)
#endif
		{
			nIndexFind = nIndex;
			break;
		}

		nIndex++;
	}

	return nIndexFind;
}

