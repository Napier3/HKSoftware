#include "stdafx.h"
#include "XYunFileApi.h"
#include "YunConfig.h"
#include "YunInterface.h"


CXYunFile_XmlRpc* CXYunFile_XmlRpc::g_pXYunFileMngr = NULL;
long CXYunFile_XmlRpc::g_nXYunFileMngrRef = 0;

void Yun_Init()
{
	CYunConfigXmlRWKeys::Create();
	CXYunFile_XmlRpc::Create();
}

void Yun_Free()
{
	CXYunFile_XmlRpc::Release();
	CYunConfigXmlRWKeys::Release();
}


void Yun_Login()
{
	CXYunFile_XmlRpc::Yun_Login();
}

void Yun_Logout()
{
	CXYunFile_XmlRpc::Yun_Logout();
}

BOOL Yun_IsLoginSucc()
{
	return CXYunFile_XmlRpc::g_pXYunFileMngr->Yun_IsLoginSucc();
}

long Yun_Search(CXFolder *pParentFolder, CExBaseList &listPostfix, BOOL bTraveSubFolder)
{
	long nRet = CXYunFile_XmlRpc::YunSearch(pParentFolder, &listPostfix, bTraveSubFolder);
	listPostfix.RemoveAll();

	return nRet;
}

long Yun_SetBatchOperMode(BOOL bBatchMode, HWND hWnd, UINT nMsg)
{
	return CXYunFile_XmlRpc::Yun_SetBatchOperMode(bBatchMode, hWnd, nMsg);
}

long Yun_BatchOper()
{
	return CXYunFile_XmlRpc::Yun_BatchOper();
}

long Yun_DownLoad(CExBaseObject *pXfxObj, BOOL bAllSameNameFiles)
{
	CXYunFile_XmlRpc::SetAllSameNameFiles(bAllSameNameFiles);
	return CXYunFile_XmlRpc::YunDownLoad(pXfxObj);
}

long Yun_UpLoad(CExBaseObject *pXfxObj, BOOL bAllSameNameFiles)
{
	CXYunFile_XmlRpc::SetAllSameNameFiles(bAllSameNameFiles);
	return CXYunFile_XmlRpc::YunUpLoad(pXfxObj);
}

long Yun_Delete(CExBaseObject *pXfxObj, BOOL bAllSameNameFiles)
{
	CXYunFile_XmlRpc::SetAllSameNameFiles(bAllSameNameFiles);
	return CXYunFile_XmlRpc::YunDelete(pXfxObj);
}


long Yun_DownLoadFile(const CString &strFile)
{
	return CXYunFile_XmlRpc::Yun_DownLoadFile(strFile);
}

long Yun_UpLoadFile(const CString &strFile)
{
	return CXYunFile_XmlRpc::Yun_UpLoadFile(strFile);
}

long Yun_DeleteFile(const CString &strFile)
{
	return CXYunFile_XmlRpc::Yun_DeleteFile(strFile);
}

long Yun_DownLoadFolder(const CString &strFolder)
{
	return CXYunFile_XmlRpc::Yun_DownLoadFolder(strFolder);
}

long Yun_UpLoadFolder(const CString &strFolder)
{
	return CXYunFile_XmlRpc::Yun_UpLoadFolder(strFolder);
}

long Yun_DeleteFolder(const CString &strFolder)
{
	return CXYunFile_XmlRpc::Yun_DeleteFolder(strFolder);
}

//XTestDB
void Yun_AttachMsgRcvWnd(HWND hWnd, UINT nMsg)
{
	return CXYunFile_XmlRpc::Yun_AttachMsgRcvWnd(hWnd, nMsg);
}

CString Yun_GetTasksXml(const CString &strPara)
{
	return CXYunFile_XmlRpc::Yun_GetTasksXml(strPara);
}

void Yun_SetTasksXml(CString &strXml)
{
	CXYunFile_XmlRpc::Yun_SetTasksXml(strXml);
}

void Yun_PopTasksSelWnd(const CString &strPara, long nPara)
{
	CXYunFile_XmlRpc::Yun_PopTasksSelWnd(strPara, nPara);
}

//////////////////////////////////////////////////////////////////////////
//
CXYunFile_XmlRpc::CXYunFile_XmlRpc()
{
	m_oYunApp = NULL;

	m_oYunOper = NULL;
// 	m_bBatchMode = FALSE;
// 	m_hMgRcvWnd = NULL;
// 	m_nYunOperMsg = 0;
	m_bLoginState = FALSE;
	m_oXDbTasks = NULL;
}

CXYunFile_XmlRpc::~CXYunFile_XmlRpc()
{
	try
	{
		m_oYunOper = NULL;
	}
	catch (...)
	{
		
	}

	try
	{
		m_oXDbTasks = NULL;
	}
	catch (...)
	{

	}

	try
	{
		m_oYunApp = NULL;
	}
	catch (...)
	{

	}
}

//////////////////////////////////////////////////////////////////////////
//接口实现
long CXYunFile_XmlRpc::xyun_DownLoadFile(const CString &strFile)
{
	return In_Yun_DownLoadFile(strFile);
}

long CXYunFile_XmlRpc::xyun_UpLoadFile(const CString &strFile) 
{
	return In_Yun_UpLoadFile(strFile);
}

long CXYunFile_XmlRpc::xyun_DeleteFile(const CString &strFile)
{
	return In_Yun_DeleteFile(strFile);
}


long CXYunFile_XmlRpc::xyun_DownLoadFolder(const CString &strFolder)
{
	return In_Yun_DownLoadFolder(strFolder);
}

long CXYunFile_XmlRpc::xyun_UpLoadFolder(const CString &strFolder)
{
	return In_Yun_UpLoadFolder(strFolder);
}

long CXYunFile_XmlRpc::xyun_DeleteFolder(const CString &strFolder)
{
	return In_Yun_DeleteFolder(strFolder);
}


BOOL CXYunFile_XmlRpc::xyun_IsLoginSucc()
{
	return Yun_IsLoginSucc();
}


//////////////////////////////////////////////////////////////////////////
void CXYunFile_XmlRpc::In_Yun_Login()
{
	if (m_oYunApp == NULL)
	{
		return;
	}

	CString strConfig;
	m_bLoginState = m_oYunApp.Login(strConfig);
}

void CXYunFile_XmlRpc::In_Yun_Logout()
{
	if (m_oYunApp == NULL)
	{
		return;
	}

	m_oYunApp.Logout();
	m_bLoginState = FALSE;
}

long CXYunFile_XmlRpc::In_YunSearch(CXFolder *pParentFolder, CExBaseList *pListPostfix, BOOL bTraveSubFolder)
{
	if (m_oYunApp == NULL)
	{
		return 0;
	}

	Yun::IYunFileFind oYunFileFind = m_oYunApp.CreateYunFileFind();

	if (oYunFileFind == NULL)
	{
		return 0;
	}

	CString strPath, strName;
	strPath = pParentFolder->GetFolderPath();

	if (oYunFileFind.FindFile(strPath) == 0)
	{
		return 0;
	}

	while (TRUE)
	{
		if (oYunFileFind.GetNextFile() == 0)
		{
			break;
		}

		if (oYunFileFind.IsDirectory())
		{
			strName = oYunFileFind.GetFileName();
			CXFolder* pChildFolder = (CXFolder*)pParentFolder->FindByLowerName(strName);

			if (pChildFolder == NULL)
			{
				pChildFolder = pParentFolder->AddFolder(strName, FALSE);
			}

			pChildFolder->SetYunFolder(TRUE);
		}
		else if (oYunFileFind.IsArchived())
		{
			//获取后缀
			strName = oYunFileFind.GetFileName();
			int npos = strName.ReverseFind('.'); 

			if(npos != -1)
			{
				npos++;
				//CString strFilePostFix = strFileWithExtension.Right(strFileWithExtension.GetLength() - npos); 

				//if(pListPostfix->FindByID(strName.Mid(npos)) != NULL)
				if (XFile_IsFilePostFixExist(pListPostfix, strName.Mid(npos)))
				{
					//CString strFileName = finder.GetFileName();//finder.GetFileTitle()+_T(".") + strFilePostFix;
					CXFile *pFile = (CXFile*)pParentFolder->FindByLowerName(strName);
					
					if (pFile == NULL)
					{
						pFile = pParentFolder->AddFile(strName,FALSE);
					}

					pFile->SetYunFile();
					DATE date = oYunFileFind.GetLastWriteTime();
					COleDateTime tmOle(date);
					tmOle.GetAsSystemTime(pFile->m_tmYun);
					pFile->m_nYunSize = oYunFileFind.GetFileSize();
				}
			}
		}
	}

	oYunFileFind.Close();
	oYunFileFind = NULL;

	if (bTraveSubFolder)
	{
		In_YunSearchChildren(pParentFolder, pListPostfix, bTraveSubFolder);
	}

	return 0;
}

long CXYunFile_XmlRpc::In_YunSearchChildren(CXFolder *pFolder, CExBaseList *pListPostfix, BOOL bTraveSubFolder)
{
	POS pos =  pFolder->GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseList oListFolder;
	CExBaseList oListFile;

	while (pos != NULL)
	{
		p = pFolder->GetNext(pos);

		if (p->GetClassID() == CLASSID_XFOLDER)
		{
			oListFolder.AddTail(p);
		}
		else
		{
			oListFile.AddTail(p);
		}
	}

	pFolder->RemoveAll();
	pFolder->Append(oListFolder);
	pFolder->Append(oListFile);
	oListFolder.RemoveAll();
	oListFile.RemoveAll();

	pos =  pFolder->GetHeadPosition();

	while (pos != NULL)
	{
		p =pFolder-> GetNext(pos);

		if (p->GetClassID() == CLASSID_XFOLDER)
		{
			In_YunSearch((CXFolder*)p, pListPostfix, bTraveSubFolder);
		}
	}

	return 0;
}

long CXYunFile_XmlRpc::In_Yun_GetAllFiles(CXFile *pXFile, CStringArray &astrFiles)
{
	return xfile_GetAllFiles(pXFile, astrFiles);
}

long CXYunFile_XmlRpc::In_YunDownLoad(CExBaseObject *pXfxObj)
{
// 	UINT nClassID = pXfxObj->GetClassID();
// 
// 	if (xfile_IsFile(nClassID) )
// 	{
// 		In_YunDownLoad((CXFile*)pXfxObj);
// 	}
// 	else if (xfile_IsFolder(nClassID))
// 	{
// 		In_YunDownLoad((CXFolder*)pXfxObj);
// 	}

	return xyun_DownLoad(pXfxObj);
}

long CXYunFile_XmlRpc::In_YunUpLoad(CExBaseObject *pXfxObj)
{
// 	UINT nClassID = pXfxObj->GetClassID();
// 
// 	if (xfile_IsFile(nClassID) )
// 	{
// 		In_YunUpLoad((CXFile*)pXfxObj);
// 	}
// 	else if (xfile_IsFolder(nClassID))
// 	{
// 		In_YunUpLoad((CXFolder*)pXfxObj);
// 	}

	return xyun_UpLoad(pXfxObj);
}

long CXYunFile_XmlRpc::In_YunDelete(CExBaseObject *pXfxObj)
{
// 	UINT nClassID = pXfxObj->GetClassID();
// 
// 	if (xfile_IsFile(nClassID) )
// 	{
// 		In_YunDelete((CXFile*)pXfxObj);
// 	}
// 	else if (xfile_IsFolder(nClassID))
// 	{
// 		In_YunDelete((CXFolder*)pXfxObj);
// 	}

	return xyun_Delete(pXfxObj);
}

long CXYunFile_XmlRpc::In_YunDownLoad(CXFile *pXFile)
{
// 	CStringArray astrFiles;
// 	In_Yun_GetAllFiles(pXFile, astrFiles);
// 
// 	long nCount = astrFiles.GetCount();
// 	long nIndex = 0;
// 	CString strFile;
// 
// 	for (nIndex=0; nIndex<nCount; nIndex++)
// 	{
// 		strFile = astrFiles.GetAt(nIndex);
// 		In_Yun_DownLoadFile(strFile);
// 	}

	return xyun_DownLoad(pXFile);
}

long CXYunFile_XmlRpc::In_YunUpLoad(CXFile *pXFile)
{
// 	CStringArray astrFiles;
// 	In_Yun_GetAllFiles(pXFile, astrFiles);
// 
// 	long nCount = astrFiles.GetCount();
// 	long nIndex = 0;
// 	CString strFile;
// 
// 	for (nIndex=0; nIndex<nCount; nIndex++)
// 	{
// 		strFile = astrFiles.GetAt(nIndex);
// 		In_Yun_UpLoadFile(strFile);
// 	}

	return xyun_UpLoad(pXFile);
}

long CXYunFile_XmlRpc::In_YunDelete(CXFile *pXFile)
{
// 	CStringArray astrFiles;
// 	In_Yun_GetAllFiles(pXFile, astrFiles);
// 
// 	long nCount = astrFiles.GetCount();
// 	long nIndex = 0;
// 	CString strFile;
// 
// 	for (nIndex=0; nIndex<nCount; nIndex++)
// 	{
// 		strFile = astrFiles.GetAt(nIndex);
// 		In_Yun_DeleteFile(strFile);
// 	}

	return xyun_UpLoad(pXFile);
}

long CXYunFile_XmlRpc::In_YunDownLoad(CXFolder *pXFolder)
{
// 	CString strPath;
// 	strPath = pXFolder->GetPath();
// 
// 	return In_Yun_DownLoadFolder(strPath);
	return xyun_DownLoad(pXFolder);
}

long CXYunFile_XmlRpc::In_YunUpLoad(CXFolder *pXFolder)
{
// 	CString strPath;
// 	strPath = pXFolder->GetPath();
// 
// 	return In_Yun_UpLoadFolder(strPath);
	return xyun_UpLoad(pXFolder);
}

long CXYunFile_XmlRpc::In_YunDelete(CXFolder *pXFolder)
{
// 	CString strPath;
// 	strPath = pXFolder->GetPath();
// 
// 	return In_Yun_DeleteFolder(strPath);
	return xyun_Delete(pXFolder);
}


long CXYunFile_XmlRpc::In_Yun_DownLoadFile(const CString &strFile)
{
	CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("Yun Download File [%s]"), strFile);

	if (! In_CreateYunOper())
	{
		return 0;
	}

	return m_oYunOper.DownloadFile(strFile, _T(""));
}

long CXYunFile_XmlRpc::In_Yun_UpLoadFile(const CString &strFile)
{
	CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("Yun Upload File [%s]"), strFile);

	if (! In_CreateYunOper())
	{
		return 0;
	}

	return m_oYunOper.UploadFile(strFile, _T(""));
}

long CXYunFile_XmlRpc::In_Yun_DeleteFile(const CString &strFile)
{
	CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("Yun Delete File [%s]"), strFile);

	if (! In_CreateYunOper())
	{
		return 0;
	}

	return m_oYunOper.DelFile(strFile);
}


long CXYunFile_XmlRpc::In_Yun_DownLoadFolder(const CString &strFolder)
{
	CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("Yun Download Folder [%s]"), strFolder);

	if (! In_CreateYunOper())
	{
		return 0;
	}

	return m_oYunOper.DownloadFolder(strFolder, strFolder, 1);
}

long CXYunFile_XmlRpc::In_Yun_UpLoadFolder(const CString &strFolder)
{
	CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("Yun Upload Folder [%s]"), strFolder);

	if (! In_CreateYunOper())
	{
		return 0;
	}

	return m_oYunOper.UploadFolder(strFolder, strFolder, 1);
}

long CXYunFile_XmlRpc::In_Yun_DeleteFolder(const CString &strFolder)
{
	CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("Yun Delete Folder [%s]"), strFolder);

	if (! In_CreateYunOper())
	{
		return 0;
	}

	return m_oYunOper.DelFolder(strFolder);
}

BOOL CXYunFile_XmlRpc::In_CreateYunOper()
{
	if (m_oYunOper != NULL)
	{
		m_oYunOper.SetBatchMode(m_bBatchMode, (UINT)m_hMgRcvWnd, m_nYunOperMsg);
		return TRUE;
	}

	m_oYunOper = m_oYunApp.CreateYunOper();

	if (m_oYunOper != NULL)
	{
		m_oYunOper.SetBatchMode(m_bBatchMode, (UINT)m_hMgRcvWnd, m_nYunOperMsg);
	}

	return (m_oYunOper != NULL);
}

void CXYunFile_XmlRpc::In_Yun_AttachMsgRcvWnd(HWND hWnd, UINT nMsg)
{
	if (m_oYunApp == NULL)
	{
		return ;
	}

	m_oYunApp.AttachMsgRcv((LONG)hWnd, nMsg);
}

CString CXYunFile_XmlRpc::In_Yun_GetTasksXml(const CString &strPara)
{
	In_CreateXTaskDB();

	if (m_oXDbTasks == NULL)
	{
		return _T("");
	}

	return m_oXDbTasks.GetTasksXml(strPara);
}

void CXYunFile_XmlRpc::In_Yun_SetTasksXml(CString &strXml)
{
	In_CreateXTaskDB();

	if (m_oXDbTasks == NULL)
	{
		return;
	}

	m_oXDbTasks.SetTasksXml(strXml);
}

void CXYunFile_XmlRpc::In_Yun_PopTasksSelWnd(const CString &strPara, long nPara)
{
	In_CreateXTaskDB();

	if (m_oXDbTasks == NULL)
	{
		return;
	}

	m_oXDbTasks.PopTasksSelWnd(strPara, nPara);
}


BOOL CXYunFile_XmlRpc::In_CreateXTaskDB()
{
	if (m_oYunApp == NULL)
	{
		return FALSE;
	}

	if (m_oXDbTasks != NULL)
	{
		return TRUE;
	}

	m_oXDbTasks = m_oYunApp.CreateTasks();

	return (m_oXDbTasks != NULL);
}
