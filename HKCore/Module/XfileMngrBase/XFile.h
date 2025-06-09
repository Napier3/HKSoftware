#pragma once

#include "../BaseClass/ExBaseObject.h"

#define CLASSID_XFILE                      (CLASSID_BASECLASS + 0x00051000)
#define CLASSID_XFOLDER                  (CLASSID_LISTCLASS + 0x00052000)
#define CLASSID_XFILEMNGR               (CLASSID_LISTCLASS + 0x00054000)

#define CLASSID_XFILE_POSTFIX                      (CLASSID_BASECLASS + 0x0007A000)
#define CLASSID_XFILE_TYPE                  (CLASSID_LISTCLASS + 0x0007B000)
#define CLASSID_XFILE_TYPES               (CLASSID_LISTCLASS + 0x0007C000)
//yyj 
#ifndef _PSX_IDE_QT_
#include "XFileDlgDefine.h"
#include "../MfcCtrlEx/BmpImageList.h"
#endif

#include "../DataMngr/DvmData.h"
#include "../../Module/DataMngr/DataGroup.h"

class CXFileMngr;
class CXFolder;



class CXFile : public CExBaseObject
{
public:
	CXFile();
	virtual ~CXFile();

public:
	long m_nSelected;
	CString m_strFileType;
	CString m_strFileName;
	BOOL m_bIsOpen;
	BOOL m_bIsYun;
	long   m_nYunSize;          //2016-12-3  lijq
	SYSTEMTIME m_tmYun;  //2016-12-3  lijq
	CDvmData *m_pYunFile;

public:
	//获取包含完整路径和后缀的文件名称
	CString GetRelativePath(BOOL bAddRoot=FALSE);
	CString GetFolderPath(BOOL bAddRoot=FALSE);
	CString GetTotalFileName();
	BOOL IsFileExist();
	
	virtual UINT GetClassID()							{		return CLASSID_XFILE;		}
	BOOL GetFilePostfix(CString &strPostfix, BOOL bHasDot=TRUE);

	virtual BOOL CopyTo(const CString &strPath);
	virtual BOOL DeleteFile();
	virtual BOOL RenameFile(const CString& strName);
	
	//获得文件属性
	virtual BOOL GetModifyTime(CString& strCreateTime);
	virtual BOOL GetModifyTime(SYSTEMTIME &tm);
	virtual BOOL GetFileSize(CString& strFileSize);
	virtual long GetFileSize();

// #ifdef _PSX_QT_LINUX_
// 	virtual long GetFileSize(BOOL bUseUtf8Code);//linux下传递使用的编码方式
// #endif
	virtual BOOL GetModifyTime_Yun(CString& strCreateTime);//2016-12-3 lijq
	virtual BOOL GetFileSize_Yun(CString& strFileSize);//2016-12-3 lijq
	CString GetFileType()													{		return m_strFileType;					}
	void SetFileType(const CString strFileType)		{		m_strFileType = strFileType;	}

	//xxy 20181107
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CXFileMngr* GetXFileMngr();

	CDataGroup* XFolderToDataGroup(); //相对路径转换成CDataGroup,暂时默认模板不能直接放在根目录下
	CDataGroup* ParentToDataGroup(CDataGroup* pGroup, CXFolder* pFolder, CXFolder* pRootFolder);
	CDataGroup* GetLeafDataGroup(CDataGroup *pPathGroup);

	BOOL IsYunFile()	{	return m_bIsYun;	}
	void SetYunFile(BOOL b=TRUE)	{	m_bIsYun = b;	}

};

inline BOOL xfile_IsFile(UINT nClassID)
{
	return ( (nClassID & CLASSID_XFILE) == CLASSID_XFILE);
}

inline BOOL xfile_IsFolder(UINT nClassID)
{
	return ( (nClassID & CLASSID_XFOLDER) == CLASSID_XFOLDER);
}

class CXFileOptr
{
public:
	CXFileOptr()			{	}
	virtual ~CXFileOptr()	{	}

	virtual BOOL XCopyFile(const CString &strSrcFile, const CString &strDestFile, BOOL bFailIfExists) = 0;
	virtual DWORD XOpenXFile(CXFile *pFile) = 0;
	virtual DWORD XDeleteXFile(CXFile *pFile) = 0;
	virtual DWORD XDeleteXFolder(CXFolder *pFolder) = 0;
	virtual DWORD XEditXFile(CXFile *pFile, const CString &strDestName) = 0;
	virtual DWORD XCanEditXFile(CXFile *pFile)	{	return TRUE;	}
	virtual DWORD XCanEditXFolder(CXFolder *pFolder)	{	return TRUE;	}

	virtual UINT GetImgIndex(CExBaseObject *pObj) = 0;

	virtual DWORD XDownLoad(CExBaseObject *pXFileObj) = 0;
	virtual DWORD XUpload(CExBaseObject *pXFileObj) = 0;
};


extern CXFileOptr *g_pXFileOptr;
BOOL XCopyFile(const CString &strSrcFile, const CString &strDestFile, BOOL bFailIfExists);

BOOL xfile_XCopyFile(const CString &strFile, const CString &strFolder, BOOL bFailIfExists);

class CXFileOptrMsgRcvWnd : public CXFileOptr
{
public:
	CXFileOptrMsgRcvWnd()	{	m_pMsgRcvWnd = NULL;	}
	virtual ~CXFileOptrMsgRcvWnd()	{	}
	CWnd *m_pMsgRcvWnd;

public:
	
};

BOOL xfile_CheckFileName(const CString &strFileName, CWnd *pWnd=NULL);
BOOL xfile_GetModifyTime(const CString &strFile, CString& strModifyTime);
BOOL xfile_GetModifyTime(const CString &strFile, SYSTEMTIME &tmModifyTime);
BOOL xfile_GetFileSize(const CString &strFile, CString& strFileSize);
DWORD xfile_GetFileSize(const CString &strFile);
BOOL xfile_GetFileInfo(const CString &strFile, DWORD &dwSize, SYSTEMTIME &dtTime);
UINT xfile_GetImageIndex(CExBaseObject* pObj);
BOOL xfile_IsYunFile(CExBaseObject *pObj);
//yyj
#ifndef _PSX_IDE_QT_
BOOL xfile_LoadFileMngrBmp(CBmpImageList *pBmpImageList, const CString &strBmpFile=_T(""), long nCount=12, COLORREF crMask=RGB(255, 0, 0));
#endif

CString xfile_GetYunFileVersion(CXFile *pXFile);
