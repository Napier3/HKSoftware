//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XLangFolder.h  CXLangFolder

#pragma once


#include "XLangFile.h"

class CXLangFolder : public CExBaseList
{
public:
	CXLangFolder();
	virtual ~CXLangFolder();


//���غ���
public:

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//��������
public:
	void AppendLangFile(CXLangFolder *pSrcFolder);
	void AppendLangFile(CXLangFile *pFile);
	CXLangFile* FindLangFile(const CString &strFile);
	long FindLangFileIndex(const CString &strFile);
};

