#pragma once

#include "XFile.h"
#include "../BaseClass/ExBaseList.h"
#include "../API/FileApi.h"

#include "../../Module/DataMngr/DataGroup.h"

#define FIND_MODE_ALL    0
#define FIND_MODE_FOLDER 1
#define FIND_MODE_FILE   2

class CXFileMngr;

class CXFolder : public CExBaseList
{
public:
	CXFolder();
	virtual ~CXFolder();

//����
protected:
	CString m_strPath;
	BOOL m_bIsYun;
	BOOL m_bHasSearched;//20220702 zhouhj �Ƿ�������ļ����ļ���
	CDataGroup *m_pYunFolder;
	
public:
	virtual UINT GetClassID()										{		return CLASSID_XFOLDER;		}
	BOOL CheckFileExist();
	BOOL IsFolderExist();
	BOOL HasSearched(){return m_bHasSearched;}

	virtual BOOL IsFileExist(const CString& strFilePath);
	virtual CXFile* AddFile(const CString& strFilePath);
	virtual CXFile* AddFile2(const CString& strFile);
	virtual CXFile* OverWriteFile(const CString& strFilePath);

	virtual CXFile* AddFile(const CString& strFileName,BOOL bOverWrite);
	virtual CXFile* AddFile(CXFile *pSrcFile);
	virtual CXFile* AddFile(CXFile *pSrcFile, const CString &strFileName);
	virtual CXFolder* AddFolder(const CString &strFolderName, BOOL bCreateFolder=TRUE);
	
	BOOL GetFolderModifyTime(CString& strModifyTime);
	CExBaseObject* FindByLowerName(const CString &strFolderName);

	virtual BOOL DeleteAllInFolder();
	virtual BOOL RenameFolder(const CString &strNewName);
	virtual CXFolder* AddFolderByPath(const CString &strRelPath);

	BOOL CheckFileOpen();
	BOOL CheckFileOpenChildren(CXFolder* pFolder);

	CXFile* SelectFile(const CString &strFile, BOOL bUseFullPath=FALSE);
	CXFile* SelectFileInCurrFolder(const CString &strFile, BOOL bUseFullPath=FALSE);
	CXFile* SelectFileInSubFolder(const CString &strFile, BOOL bUseFullPath=FALSE);

	CXFolder* FindFolder(const CString &strFolder);
	CXFolder* SelectFolder(const CString &strFolder, BOOL bUseFullPath=FALSE);
	CXFolder* SelectFolderInCurrFolder(const CString &strFolder, BOOL bUseFullPath=FALSE);
	CXFolder* SelectFolderInSubFolder(const CString &strFolder, BOOL bUseFullPath=FALSE);

	CXFolder* SelectFolder(CStringArray &strIdArray, long nPos);
	CXFolder* SelectFolderInCurrFolder(CStringArray &strIdArray, long nPos);
// 	CXFolder* SelectFolderInSubFolder(CStringArray &strIdArray, long nPos);
	
	CXFile* SelectFile(CStringArray &strIdArray);
	long SelectAllFiles(CExBaseList &listFiles);

	virtual BOOL DeleteFolder();
	virtual BOOL DeleteFolderEx();
	long DeleteFile(const CString &strFile);
	long DeleteFile(CXFile *pFile);
#ifndef _PSX_IDE_QT_
	long DeleteFile_byTime(long nSpanDays);   //shaolei 20211517  //��ʱ�䳬������������ļ�ɾ��
#endif
	BOOL CopyTo(const CString &strPath, BOOL bCopySubFolder=FALSE);
	CString GetFolderPath(BOOL bValidateLastChar=FALSE);
	CString GetRelativePath();

	//ƴ���·����ʱ�򣬲���Name    Add By ShaoL   2019.05.24
	CString GetFolderPathByName(BOOL bValidateLastChar=FALSE);
	CString GetRelativePathByName();

	CXFolder* AddPath(const CString &strPath);

	virtual CExBaseObject* Paste(CExBaseObject *pObj);
	virtual CExBaseObject* Paste(CExBaseList *pList);

	void SetPath(const CString &strPath);
	BOOL IsYunFolder()	{	return m_bIsYun;	}
	void SetYunFolder(BOOL b=TRUE)	{	m_bIsYun = b;	}
	CDataGroup* GetYunFolder()	{	return m_pYunFolder;	}

	//xxy 20181107
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void XFolderToDataGroup(CDataGroup *pDestGroup);
	virtual void DataGroupToXFolder(CDataGroup *pDestGroup);

	CDataGroup* ParentToDataGroup(CDataGroup* pGroup, CXFolder* pRootFolder);
	long Search(CExBaseList *pListPostfix, BOOL bAddSubFiles, BOOL bAddSubFolders,BOOL bSearchSubFolders);	//20220702 zhouhj �Ƿ�������ļ����Ƿ�������ļ��С��Ƿ�������ļ���

protected:
	//����Դ����������		���������ļ����ļ���  //2022-3-23  lijunqing add bAddFiles
	long Search(CExBaseList *pListPostfix, BOOL bTraveSubFolder, BOOL bAddFiles=TRUE);	
	long SearchChildren(CExBaseList *pListPostfix, BOOL bTraveSubFolder, BOOL bAddFiles=TRUE);		//�������ļ���		�������ļ��е��ļ����ļ���
	long SearchChildren(CExBaseList *pListPostfix, BOOL bAddSubFiles, BOOL bAddSubFolders,BOOL bSearchSubFolders);	//20220702 zhouhj �Ƿ�������ļ����Ƿ�������ļ��С��Ƿ�������ļ���
};

void XFile_BringFileHead(CXFolder *pFolder, const CString &strFilePostfix);
BOOL XFile_IsFilePostFixExist(CExBaseList *pListFilePostFix, const CString &strPostfix);
