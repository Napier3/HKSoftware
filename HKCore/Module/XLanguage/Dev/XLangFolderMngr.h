//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XLangFolderMngr.h  CXLangFolderMngr

#pragma once


#include "XLangFolder.h"

class CXLangFolderMngr : public CExBaseList
{
public:
	CXLangFolderMngr();
	virtual ~CXLangFolderMngr();

	//������Դ�ļ����󣬻������������Ե���Դ�ļ�
	CXLangFolder m_oAllFile;
//���غ���
public:
	

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//��������
public:
	void InitXLangFolderMngr();
	BOOL CanOpenXLangFile(CXLangFile *pFile);
	BOOL OpenXLangFiles(CXLangFile *pFile, CXLangFileRsItemMngr *pCXLangFileRsItemMngr);

protected:
	void AddXLangFolder(CExBaseList *pFolder);
	void InitAllFiles();
	void AppendXLanguage(CXLanguage *pRef, CXLanguage *pXLanguage);
};

