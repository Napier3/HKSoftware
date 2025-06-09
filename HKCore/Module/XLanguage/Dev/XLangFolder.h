//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XLangFolder.h  CXLangFolder

#pragma once


#include "XLangFile.h"

class CXLangFolder : public CExBaseList
{
public:
	CXLangFolder();
	virtual ~CXLangFolder();


//重载函数
public:

//私有成员变量
private:

//私有成员变量访问方法
public:

//其他方法
public:
	void AppendLangFile(CXLangFolder *pSrcFolder);
	void AppendLangFile(CXLangFile *pFile);
	CXLangFile* FindLangFile(const CString &strFile);
	long FindLangFileIndex(const CString &strFile);
};

