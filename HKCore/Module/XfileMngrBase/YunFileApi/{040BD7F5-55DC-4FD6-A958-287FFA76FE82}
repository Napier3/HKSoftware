#include "stdafx.h"
#include "XYunFileApi_Global.h"


CYunFileInterface::CYunFileInterface()
{
	m_bBatchMode = FALSE;
	m_hMgRcvWnd = NULL;
	m_nYunOperMsg = 0;
}

CYunFileInterface::~CYunFileInterface()
{

}

long CYunFileInterface::xyun_DownLoadFiles(const CStringArray &astrFiles)
{
	return 0;
}

long CYunFileInterface::xyun_UpLoadFiles(const CStringArray &astrFiles)
{
	return 0;
}

long CYunFileInterface::xyun_DeleteFiles(const CStringArray &astrFiles)
{
	return 0;
}




long CYunFileInterface::xyun_SetBatchOperMode(BOOL bBatchMode, HWND hWnd, UINT nMsg)
{
	return 0;
}

long CYunFileInterface::xyun_BatchOper()
{
	return 0;
}

long CYunFileInterface::xyun_DownLoad(CExBaseObject *pXfxObj, BOOL bAllSameNameFiles)
{
	m_bAllSameNameFiles = bAllSameNameFiles;
	return xyun_DownLoad(pXfxObj);
}

long CYunFileInterface::xyun_UpLoad(CExBaseObject *pXfxObj, BOOL bAllSameNameFiles)
{
	m_bAllSameNameFiles = bAllSameNameFiles;
	return xyun_UpLoad(pXfxObj);
}

long CYunFileInterface::xyun_Delete(CExBaseObject *pXfxObj, BOOL bAllSameNameFiles)
{
	m_bAllSameNameFiles = bAllSameNameFiles;
	return xyun_Delete(pXfxObj);
}

long CYunFileInterface::xyun_DownLoad(CExBaseObject *pXfxObj)
{
	UINT nClassID = pXfxObj->GetClassID();

	if (xfile_IsFile(nClassID) )
	{
		return xyun_DownLoad((CXFile*)pXfxObj);
	}
	else if (xfile_IsFolder(nClassID))
	{
		return xyun_DownLoad((CXFolder*)pXfxObj);
	}

	return 0;
}

long CYunFileInterface::xyun_UpLoad(CExBaseObject *pXfxObj)
{
	UINT nClassID = pXfxObj->GetClassID();

	if (xfile_IsFile(nClassID) )
	{
		return xyun_UpLoad((CXFile*)pXfxObj);
	}
	else if (xfile_IsFolder(nClassID))
	{
		return xyun_UpLoad((CXFolder*)pXfxObj);
	}

	return 0;
}

long CYunFileInterface::xyun_Delete(CExBaseObject *pXfxObj)
{
	UINT nClassID = pXfxObj->GetClassID();

	if (xfile_IsFile(nClassID) )
	{
		return xyun_Delete((CXFile*)pXfxObj);
	}
	else if (xfile_IsFolder(nClassID))
	{
		return xyun_Delete((CXFolder*)pXfxObj);
	}

	return 0;
}

long CYunFileInterface::xyun_DownLoad(CXFile *pXFile)
{
	CStringArray astrFiles;
	xfile_GetAllFiles(pXFile, astrFiles);

	if (xyun_DownLoadFiles(astrFiles))
	{
		return 0;
	}

	long nCount = astrFiles.GetCount();
	long nIndex = 0;
	CString strFile;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		strFile = astrFiles.GetAt(nIndex);
		xyun_DownLoadFile(strFile);
	}

	return 0;
}

long CYunFileInterface::xyun_UpLoad(CXFile *pXFile)
{
	CStringArray astrFiles;
	xfile_GetAllFiles(pXFile, astrFiles);

	if (xyun_UpLoadFiles(astrFiles))
	{
		return 0;
	}

	long nCount = astrFiles.GetCount();
	long nIndex = 0;
	CString strFile;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		strFile = astrFiles.GetAt(nIndex);
		xyun_UpLoadFile(strFile);
	}

	return 0;
}

long CYunFileInterface::xyun_Delete(CXFile *pXFile)
{
	CStringArray astrFiles;
	xfile_GetAllFiles(pXFile, astrFiles);

	long nCount = astrFiles.GetCount();
	long nIndex = 0;
	CString strFile;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		strFile = astrFiles.GetAt(nIndex);
		xyun_DeleteFile(strFile);
	}

	return 0;
}

long CYunFileInterface::xyun_DownLoad(CXFolder *pXFolder)
{
// 	CStringArray astrFiles;
// 	xfile_GetAllFiles(pXFolder, astrFiles);
// 
// 	if (xyun_DownLoadFiles(astrFiles))
// 	{
// 		return 0;
// 	}

	CString strPath;
	strPath = pXFolder->GetFolderPath();

	return xyun_DownLoadFolder(strPath);
}

long CYunFileInterface::xyun_UpLoad(CXFolder *pXFolder)
{
// 	CStringArray astrFiles;
// 	xfile_GetAllFiles(pXFolder, astrFiles);
// 
// 	if (xyun_UpLoadFiles(astrFiles))
// 	{
// 		return 0;
// 	}

	CString strPath;
	strPath = pXFolder->GetFolderPath();

	return xyun_UpLoadFolder(strPath);
}

long CYunFileInterface::xyun_Delete(CXFolder *pXFolder)
{
	CString strPath;
	strPath = pXFolder->GetFolderPath();

	return xyun_DeleteFolder(strPath);
}

