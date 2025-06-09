#pragma once

#include "../BaseClass/ExBaseObject.h"
#include "FileMngrXMLKeys.h"

#define CLASSID_FILE_BASE										(CLASSID_BASECLASS     + 0x00050000)
#define CLASSID_FOLDER_BASE								(CLASSID_EXLISTCLASS + 0x00400000)
#define CLASSID_FILE_MNGR_BASE							(CLASSID_EXLISTCLASS + 0x00500000)

class CFileMngrBase;
class CFolderBase;

const BSTR g_strFileKey = L"file";
const BSTR g_strFolderKey = L"folder";


//�����ļ����������ļ������ļ���,strFilePostFixΪ�ļ���׺
BOOL TraverseFolder(CFolderBase* pFolder,const CString& strPath,const CString& strFilePostFix/*,const CString& strFileType=_T("")*/, BOOL bTraveSubFolder=TRUE);

//�鿴һ���ļ��Ƿ����
//BOOL IsFileExist(const CString& strFile);

class CFileBase : public CExBaseObject
{
public:
	CFileBase();
	virtual ~CFileBase();

public:
	long m_nSelected;
	//CString m_strFileType;
	CString m_strFileName;
	BOOL m_bIsOpen;

public:
	//��ȡ��������·���ͺ�׺���ļ�����
	CString GetRelativePath(BOOL bAddRoot=FALSE);
	CString GetTotalFileName();
	BOOL IsFileExist();
	virtual CString GetPath();
	
	virtual UINT GetClassID()							{		return CLASSID_FILE_BASE;		}
	virtual BSTR GetXmlElementKey()		{		return g_strFileKey;						}
	BOOL GetFilePostfix(CString &strPostfix);

	virtual BOOL DeleteFile();
	virtual BOOL RenameFile(const CString& strName);
	
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys);

	//����ļ�����
	virtual BOOL GetModifyTime(CString& strCreateTime);
	virtual BOOL GetFileSize(CString& strFileSize);
// 	CString GetFileType()													{		return m_strFileType;					}
// 	void SetFileType(const CString strFileType)		{		m_strFileType = strFileType;	}

};

inline BOOL IsFile(UINT nClassID)
{
	return ( (nClassID & CLASSID_FILE_BASE) == CLASSID_FILE_BASE);
}

inline BOOL IsFolder(UINT nClassID)
{
	return ( (nClassID & CLASSID_FOLDER_BASE) == CLASSID_FOLDER_BASE);
}