//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XLangFolderMngr.h  CXLangFolderMngr

#pragma once


#include "XLangFolder.h"

class CXLangFolderMngr : public CExBaseList
{
public:
	CXLangFolderMngr();
	virtual ~CXLangFolderMngr();

	//所有资源文件对象，汇总了所有语言的资源文件
	CXLangFolder m_oAllFile;
//重载函数
public:
	

//私有成员变量
private:

//私有成员变量访问方法
public:

//其他方法
public:
	void InitXLangFolderMngr();
	BOOL CanOpenXLangFile(CXLangFile *pFile);
	BOOL OpenXLangFiles(CXLangFile *pFile, CXLangFileRsItemMngr *pCXLangFileRsItemMngr);

protected:
	void AddXLangFolder(CExBaseList *pFolder);
	void InitAllFiles();
	void AppendXLanguage(CXLanguage *pRef, CXLanguage *pXLanguage);
};

