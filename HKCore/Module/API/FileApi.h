#ifndef _FILE_API_H__
#define _FILE_API_H__

#include "../OSInterface/OSInterface.h"

//���ļ���ȫ����·���л�ȡ�ļ���·����Ϣ
CString GetPathFromFilePathName(const CString &strFilePath, char ch='\\');
CString GetPathFromFilePathName(const char *pszFilePath, char ch='\\');
CString GetLastFolderNameFromPathName(const CString &strFilePath);
CString GetPathFileNameFromFilePathName(const CString &strFilePath, char ch='\\');
CString ChangeFilePostfix(const CString &strFile, const CString &strPostfix);
CString ChangeFileName(const CString &strFile, const CString &strFileName);

CString GetFileNameFromFilePath(const CString &strFilePath, char ch='\\');
//�Ӿ���·���л�ȡ�ļ�������������׺   shaolei  20210928
CString GetFileTitleFromFilePath(const CString &strFilePath, char ch='\\');

//���ļ���·��д��ע�������Ĳ���Ϊ�ļ��ľ���·��
void WriteFilePathToRegByFilePathName(const CString &strRoot,const CString &strRegKey,const CString &strPathName);


//�ļ����桢�򿪶Ի���
BOOL PopupSaveAsFileDialog(CWnd *pParent,CString &strFilePath,const CString &strRoot,const CString &strRegKey,const CString &strFilter,const CString &strPostFix);
BOOL PopupSaveAsFileDialog(CWnd *pParent,CString &strFilePath,const CString &strFilter,const CString &strPostFix);
BOOL PopupSaveAsFileDialogEx(CWnd *pParent,CString &strFilePath,const CString &strRoot,const CString &strRegKey,const CString &strFilter,const CString &strPostFix,const CString &strDefaultFile);

BOOL PopupOpenFileDialog(CWnd *pParent,CString &strFilePath,const CString &strRoot,const CString &strRegKey,const CString &strFilter,const CString &strPostFix, const CString &strCaption=_T(""));
BOOL PopupOpenFileDialog(CWnd *pParent,CString &strFilePath,const CString &strFilter,const CString &strPostFix, const CString &strCaption=_T(""));

BOOL PopupOpenFileDialog(CStringArray &vecFiles,const CString &strFilter
						 ,const CString &strPostfix,const CString &strCaption=_T(""),int nMaxFiles=20);

//����ѡ���ļ���·���Ի���
BOOL FGetDirectory(HWND hParent, CString &strPath, const CString &strTitle);
//xxy 20210604 strPathΪĬ�ϴ�Ŀ¼
BOOL FGetDirectoryA(HWND hParent, CString &strPath, const CString &strTitle);
BOOL FGetDirectory(HWND hParent, wchar_t *szDir, wchar_t *strTitle);
BOOL FGetDirectory(HWND hParent, char *szDir, char *strTitle);

//�����ļ������ֺͺ�׺����
void ParseFileNameAndPostfix(const CString &strFileName, CString &strName, CString &strPostfix);
CString ParseFilePostfix(const CString &strFileName);
CString ParseFileName(const CString &strFileName);

//�����ļ���
void CreateAllDirectories(CString strDir);

//ɾ���ļ��м����µ�ȫ���ļ��м��ļ�
BOOL DeleteAllDirectorys(const CString &strDirName, BOOL bDelOwn=TRUE); 
BOOL DeleteAllFiles(const CString &strDirName, const CString &strFileType); 

BOOL CheckFileName(const CString &strFileName, CString &strInfor);

BOOL IsFileExist(const CString &strFile);
BOOL IsFileExist2(const CString &strFile);

void ClearFileReadOnlyAttr(const CString &strFile);
long file_GetFileSize(const CString &strFile);
void file_get_time(const CString &strFile, CString &strTime);
CString file_get_time(const CString &strFile);
CString file_get_time(const char* pstrFile);

void file_set_time(HANDLE hFile,SYSTEMTIME &tm);
void file_set_time(const CString& strFile,SYSTEMTIME &tm);
void file_set_time(const CString& strFile,unsigned long uTime); //add by yyj at 20200416

void GetRelativePathTo(const CString &strFrom, const CString &strTo, CString &strOut);
void GetPathFromRelative(const CString &strFrom, const CString &strFile, CString &strOut);
BOOL ValidateFileName(CString &strFileName);
void MakeFileNameValidate(CString &strFileName);
void ValidatePath(CString &strPath);

BOOL X_CopyFile(const CString &strSrcFile, const CString &strDestFile, BOOL bFailIfExists=FALSE);
BOOL X_DeleteFile(const CString &strFile);

BOOL GetFileVersion(const CString &filePath,unsigned int &nFileVersionMS, unsigned int &nFileVersionLS)  ;
BOOL GetFileVersion(const CString& strFile,CString &strVersion);	//ȡ���ļ��汾

//2021-1-2  lijunqing
void path_CheckSeparater(CString &strPath);

#endif//_FILE_API_H__
