#include "stdafx.h"
#include "XYunFileApi.h"
#include "YunConfig.h"
#include "YunInterface.h"

class CXYunFileMngr : public CExBaseList, public CYunFileInterface
{
private:
	CXYunFileMngr();
	virtual ~CXYunFileMngr();

	CYunConfig m_oYunConfig;
	Yun::IYunApp m_oYunApp;
	
	Yun::IYunOper m_oYunOper;
	Yun::IXDbTasks m_oXDbTasks;

// 	BOOL m_bBatchMode;
// 	HWND m_hMgRcvWnd;
// 	UINT  m_nYunOperMsg;
	BOOL m_bLoginState;

public:
	static CXYunFileMngr* g_pXYunFileMngr;
	static long g_nXYunFileMngrRef;

	static CXYunFileMngr* Create()
	{
		if (g_nXYunFileMngrRef == 0)
		{
			g_nXYunFileMngrRef = 1;
			g_pXYunFileMngr = new CXYunFileMngr();
			CString strFile;
			strFile = _P_GetCommonConfigPath();
			strFile += _T("YunConfig.xml");
			g_pXYunFileMngr->m_oYunConfig.OpenXmlFile(strFile, CYunConfigXmlRWKeys::g_pXmlKeys);
			g_pXYunFileMngr->m_oYunApp.CreateDispatch(g_pXYunFileMngr->m_oYunConfig.m_strProgID);
		}

		return g_pXYunFileMngr;
	}

	static void Release()
	{
		if (g_nXYunFileMngrRef > 0)
		{
			delete g_pXYunFileMngr;
			g_pXYunFileMngr = NULL;
			g_nXYunFileMngrRef = 0;
		}
	}

public:
	static void Yun_Login()
	{
		ASSERT(g_pXYunFileMngr != NULL);

		return g_pXYunFileMngr->In_Yun_Login();
	}

	static void Yun_Logout()
	{
		ASSERT(g_pXYunFileMngr != NULL);

		return g_pXYunFileMngr->In_Yun_Logout();
	}

	static BOOL Yun_IsLoginSucc()
	{
		return g_pXYunFileMngr->m_bLoginState;
	}

	static long YunSearch(CXFolder *pParentFolder, CExBaseList *pListPostfix, BOOL bTraveSubFolder)
	{
		ASSERT(g_pXYunFileMngr != NULL);

		return g_pXYunFileMngr->In_YunSearch(pParentFolder, pListPostfix, bTraveSubFolder);
	}

	static void SetAllSameNameFiles(BOOL bAllSameNameFiles)
	{
		ASSERT(g_pXYunFileMngr != NULL);
		g_pXYunFileMngr->m_bAllSameNameFiles = bAllSameNameFiles;
	}

	static long Yun_SetBatchOperMode(BOOL bBatchMode, HWND hWnd, UINT nMsg=YUN_OPER_RSLT_MSG)
	{
		ASSERT(g_pXYunFileMngr != NULL);
		g_pXYunFileMngr->m_bBatchMode = bBatchMode;
		g_pXYunFileMngr->m_hMgRcvWnd = hWnd;
		g_pXYunFileMngr->m_nYunOperMsg = nMsg;

		return 0;
	}

	static long Yun_BatchOper()
	{
		ASSERT(g_pXYunFileMngr != NULL);
		
		if (g_pXYunFileMngr == NULL)
		{
			return 0;
		}

		if (g_pXYunFileMngr->m_oYunOper == NULL)
		{
			return 0;
		}

		return g_pXYunFileMngr->m_oYunOper.BatchOper(g_pXYunFileMngr->m_bBatchMode);;
	}

	static long YunDownLoad(CExBaseObject *pXfxObj)
	{
		ASSERT(g_pXYunFileMngr != NULL);

		return g_pXYunFileMngr->In_YunDownLoad(pXfxObj);
	}
	static long YunUpLoad(CExBaseObject *pXfxObj)
	{
		ASSERT(g_pXYunFileMngr != NULL);

		return g_pXYunFileMngr->In_YunUpLoad(pXfxObj);
	}
	static long YunDelete(CExBaseObject *pXfxObj)
	{
		ASSERT(g_pXYunFileMngr != NULL);

		return g_pXYunFileMngr->In_YunDelete(pXfxObj);
	}

	static long Yun_DownLoadFile(const CString &strFile)
	{
		ASSERT(g_pXYunFileMngr != NULL);

		return g_pXYunFileMngr->In_Yun_DownLoadFile(strFile);
	}
	static long Yun_UpLoadFile(const CString &strFile)
	{
		ASSERT(g_pXYunFileMngr != NULL);

		return g_pXYunFileMngr->In_Yun_UpLoadFile(strFile);
	}
	static long Yun_DeleteFile(const CString &strFile)
	{
		ASSERT(g_pXYunFileMngr != NULL);

		return g_pXYunFileMngr->In_Yun_DeleteFile(strFile);
	}

	static long Yun_DownLoadFolder(const CString &strFolder)
	{
		ASSERT(g_pXYunFileMngr != NULL);

		return g_pXYunFileMngr->In_Yun_DownLoadFolder(strFolder);
	}

	static long Yun_UpLoadFolder(const CString &strFolder)
	{
		ASSERT(g_pXYunFileMngr != NULL);

		return g_pXYunFileMngr->In_Yun_UpLoadFolder(strFolder);
	}

	static long Yun_DeleteFolder(const CString &strFolder)
	{
		ASSERT(g_pXYunFileMngr != NULL);

		return g_pXYunFileMngr->In_Yun_DeleteFolder(strFolder);
	}

	//XTestDB
	static void Yun_AttachMsgRcvWnd(HWND hWnd, UINT nMsg)
	{
		ASSERT(g_pXYunFileMngr != NULL);

		return g_pXYunFileMngr->In_Yun_AttachMsgRcvWnd(hWnd, nMsg);
	}

	static CString Yun_GetTasksXml(const CString &strPara)
	{
		ASSERT(g_pXYunFileMngr != NULL);

		return g_pXYunFileMngr->In_Yun_GetTasksXml(strPara);
	}

	static void Yun_SetTasksXml(CString &strXml)
	{
		ASSERT(g_pXYunFileMngr != NULL);

		return g_pXYunFileMngr->In_Yun_SetTasksXml(strXml);
	}

	static void Yun_PopTasksSelWnd(const CString &strPara, long nPara)
	{
		ASSERT(g_pXYunFileMngr != NULL);

		return g_pXYunFileMngr->In_Yun_PopTasksSelWnd(strPara, nPara);
	}

//////////////////////////////////////////////////////////////////////////
//接口实现
public:
	virtual long xyun_DownLoadFile(const CString &strFile);
	virtual long xyun_UpLoadFile(const CString &strFile);
	virtual long xyun_DeleteFile(const CString &strFile);

	virtual long xyun_DownLoadFolder(const CString &strFolder);
	virtual long xyun_UpLoadFolder(const CString &strFolder);
	virtual long xyun_DeleteFolder(const CString &strFolder);

	virtual BOOL xyun_IsLoginSucc();


private:
	void In_Yun_Login();
	void In_Yun_Logout();

	long In_YunSearch(CXFolder *pParentFolder, CExBaseList *pListPostfix, BOOL bTraveSubFolder);
	long In_YunSearchChildren(CXFolder *pFolder, CExBaseList *pListPostfix, BOOL bTraveSubFolder);

	//对象操作
	BOOL m_bAllSameNameFiles;
	long In_Yun_GetAllFiles(CXFile *pXFile, CStringArray &astrFiles);
	long In_YunDownLoad(CExBaseObject *pXfxObj);
	long In_YunUpLoad(CExBaseObject *pXfxObj);
	long In_YunDelete(CExBaseObject *pXfxObj);
	long In_YunDownLoad(CXFile *pXFile);
	long In_YunUpLoad(CXFile *pXFile);
	long In_YunDelete(CXFile *pXFile);
	long In_YunDownLoad(CXFolder *pXFolder);
	long In_YunUpLoad(CXFolder *pXFolder);
	long In_YunDelete(CXFolder *pXFolder);

	//文件操作
	long In_Yun_DownLoadFile(const CString &strFile);
	long In_Yun_UpLoadFile(const CString &strFile);
	long In_Yun_DeleteFile(const CString &strFile);

	//文件夹操作
	long In_Yun_DownLoadFolder(const CString &strFolder);
	long In_Yun_UpLoadFolder(const CString &strFolder);
	long In_Yun_DeleteFolder(const CString &strFolder);

	BOOL In_CreateYunOper();

	//XTestDB
	void In_Yun_AttachMsgRcvWnd(HWND hWnd, UINT nMsg);
	CString In_Yun_GetTasksXml(const CString &strPara);
	void In_Yun_SetTasksXml(CString &strXml);
	void In_Yun_PopTasksSelWnd(const CString &strPara, long nPara);
	BOOL In_CreateXTaskDB();

};


CXYunFileMngr* CXYunFileMngr::g_pXYunFileMngr = NULL;
long CXYunFileMngr::g_nXYunFileMngrRef = 0;

void Yun_Init()
{
	CYunConfigXmlRWKeys::Create();
	CXYunFileMngr::Create();
}

void Yun_Free()
{
	CXYunFileMngr::Release();
	CYunConfigXmlRWKeys::Release();
}


void Yun_Login()
{
	CXYunFileMngr::Yun_Login();
}

void Yun_Logout()
{
	CXYunFileMngr::Yun_Logout();
}

BOOL Yun_IsLoginSucc()
{
	return CXYunFileMngr::g_pXYunFileMngr->Yun_IsLoginSucc();
}

long Yun_Search(CXFolder *pParentFolder, CExBaseList &listPostfix, BOOL bTraveSubFolder)
{
	long nRet = CXYunFileMngr::YunSearch(pParentFolder, &listPostfix, bTraveSubFolder);
	listPostfix.RemoveAll();

	return nRet;
}

long Yun_SetBatchOperMode(BOOL bBatchMode, HWND hWnd, UINT nMsg)
{
	return CXYunFileMngr::Yun_SetBatchOperMode(bBatchMode, hWnd, nMsg);
}

long Yun_BatchOper()
{
	return CXYunFileMngr::Yun_BatchOper();
}

long Yun_DownLoad(CExBaseObject *pXfxObj, BOOL bAllSameNameFiles)
{
	CXYunFileMngr::SetAllSameNameFiles(bAllSameNameFiles);
	return CXYunFileMngr::YunDownLoad(pXfxObj);
}

long Yun_UpLoad(CExBaseObject *pXfxObj, BOOL bAllSameNameFiles)
{
	CXYunFileMngr::SetAllSameNameFiles(bAllSameNameFiles);
	return CXYunFileMngr::YunUpLoad(pXfxObj);
}

long Yun_Delete(CExBaseObject *pXfxObj, BOOL bAllSameNameFiles)
{
	CXYunFileMngr::SetAllSameNameFiles(bAllSameNameFiles);
	return CXYunFileMngr::YunDelete(pXfxObj);
}


long Yun_DownLoadFile(const CString &strFile)
{
	return CXYunFileMngr::Yun_DownLoadFile(strFile);
}

long Yun_UpLoadFile(const CString &strFile)
{
	return CXYunFileMngr::Yun_UpLoadFile(strFile);
}

long Yun_DeleteFile(const CString &strFile)
{
	return CXYunFileMngr::Yun_DeleteFile(strFile);
}

long Yun_DownLoadFolder(const CString &strFolder)
{
	return CXYunFileMngr::Yun_DownLoadFolder(strFolder);
}

long Yun_UpLoadFolder(const CString &strFolder)
{
	return CXYunFileMngr::Yun_UpLoadFolder(strFolder);
}

long Yun_DeleteFolder(const CString &strFolder)
{
	return CXYunFileMngr::Yun_DeleteFolder(strFolder);
}

//XTestDB
void Yun_AttachMsgRcvWnd(HWND hWnd, UINT nMsg)
{
	return CXYunFileMngr::Yun_AttachMsgRcvWnd(hWnd, nMsg);
}

CString Yun_GetTasksXml(const CString &strPara)
{
	return CXYunFileMngr::Yun_GetTasksXml(strPara);
}

void Yun_SetTasksXml(CString &strXml)
{
	CXYunFileMngr::Yun_SetTasksXml(strXml);
}

void Yun_PopTasksSelWnd(const CString &strPara, long nPara)
{
	CXYunFileMngr::Yun_PopTasksSelWnd(strPara, nPara);
}

//////////////////////////////////////////////////////////////////////////
//
CXYunFileMngr::CXYunFileMngr()
{
	m_oYunApp = NULL;

	m_oYunOper = NULL;
// 	m_bBatchMode = FALSE;
// 	m_hMgRcvWnd = NULL;
// 	m_nYunOperMsg = 0;
	m_bLoginState = FALSE;
	m_oXDbTasks = NULL;
}

CXYunFileMngr::~CXYunFileMngr()
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
long CXYunFileMngr::xyun_DownLoadFile(const CString &strFile)
{
	return In_Yun_DownLoadFile(strFile);
}

long CXYunFileMngr::xyun_UpLoadFile(const CString &strFile) 
{
	return In_Yun_UpLoadFile(strFile);
}

long CXYunFileMngr::xyun_DeleteFile(const CString &strFile)
{
	return In_Yun_DeleteFile(strFile);
}


long CXYunFileMngr::xyun_DownLoadFolder(const CString &strFolder)
{
	return In_Yun_DownLoadFolder(strFolder);
}

long CXYunFileMngr::xyun_UpLoadFolder(const CString &strFolder)
{
	return In_Yun_UpLoadFolder(strFolder);
}

long CXYunFileMngr::xyun_DeleteFolder(const CString &strFolder)
{
	return In_Yun_DeleteFolder(strFolder);
}


BOOL CXYunFileMngr::xyun_IsLoginSucc()
{
	return Yun_IsLoginSucc();
}


//////////////////////////////////////////////////////////////////////////
void CXYunFileMngr::In_Yun_Login()
{
	if (m_oYunApp == NULL)
	{
		return;
	}

	CString strConfig;
	m_bLoginState = m_oYunApp.Login(strConfig);
}

void CXYunFileMngr::In_Yun_Logout()
{
	if (m_oYunApp == NULL)
	{
		return;
	}

	m_oYunApp.Logout();
	m_bLoginState = FALSE;
}

long CXYunFileMngr::In_YunSearch(CXFolder *pParentFolder, CExBaseList *pListPostfix, BOOL bTraveSubFolder)
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

long CXYunFileMngr::In_YunSearchChildren(CXFolder *pFolder, CExBaseList *pListPostfix, BOOL bTraveSubFolder)
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

long CXYunFileMngr::In_Yun_GetAllFiles(CXFile *pXFile, CStringArray &astrFiles)
{
	return xfile_GetAllFiles(pXFile, astrFiles);
}

long CXYunFileMngr::In_YunDownLoad(CExBaseObject *pXfxObj)
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

long CXYunFileMngr::In_YunUpLoad(CExBaseObject *pXfxObj)
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

long CXYunFileMngr::In_YunDelete(CExBaseObject *pXfxObj)
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

long CXYunFileMngr::In_YunDownLoad(CXFile *pXFile)
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

long CXYunFileMngr::In_YunUpLoad(CXFile *pXFile)
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

long CXYunFileMngr::In_YunDelete(CXFile *pXFile)
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

long CXYunFileMngr::In_YunDownLoad(CXFolder *pXFolder)
{
// 	CString strPath;
// 	strPath = pXFolder->GetPath();
// 
// 	return In_Yun_DownLoadFolder(strPath);
	return xyun_DownLoad(pXFolder);
}

long CXYunFileMngr::In_YunUpLoad(CXFolder *pXFolder)
{
// 	CString strPath;
// 	strPath = pXFolder->GetPath();
// 
// 	return In_Yun_UpLoadFolder(strPath);
	return xyun_UpLoad(pXFolder);
}

long CXYunFileMngr::In_YunDelete(CXFolder *pXFolder)
{
// 	CString strPath;
// 	strPath = pXFolder->GetPath();
// 
// 	return In_Yun_DeleteFolder(strPath);
	return xyun_Delete(pXFolder);
}


long CXYunFileMngr::In_Yun_DownLoadFile(const CString &strFile)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Yun Download File [%s]"), strFile);

	if (! In_CreateYunOper())
	{
		return 0;
	}

	return m_oYunOper.DownloadFile(strFile, _T(""));
}

long CXYunFileMngr::In_Yun_UpLoadFile(const CString &strFile)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Yun Upload File [%s]"), strFile);

	if (! In_CreateYunOper())
	{
		return 0;
	}

	return m_oYunOper.UploadFile(strFile, _T(""));
}

long CXYunFileMngr::In_Yun_DeleteFile(const CString &strFile)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Yun Delete File [%s]"), strFile);

	if (! In_CreateYunOper())
	{
		return 0;
	}

	return m_oYunOper.DelFile(strFile);
}


long CXYunFileMngr::In_Yun_DownLoadFolder(const CString &strFolder)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Yun Download Folder [%s]"), strFolder);

	if (! In_CreateYunOper())
	{
		return 0;
	}

	return m_oYunOper.DownloadFolder(strFolder, strFolder, 1);
}

long CXYunFileMngr::In_Yun_UpLoadFolder(const CString &strFolder)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Yun Upload Folder [%s]"), strFolder);

	if (! In_CreateYunOper())
	{
		return 0;
	}

	return m_oYunOper.UploadFolder(strFolder, strFolder, 1);
}

long CXYunFileMngr::In_Yun_DeleteFolder(const CString &strFolder)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Yun Delete Folder [%s]"), strFolder);

	if (! In_CreateYunOper())
	{
		return 0;
	}

	return m_oYunOper.DelFolder(strFolder);
}

BOOL CXYunFileMngr::In_CreateYunOper()
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

void CXYunFileMngr::In_Yun_AttachMsgRcvWnd(HWND hWnd, UINT nMsg)
{
	if (m_oYunApp == NULL)
	{
		return ;
	}

	m_oYunApp.AttachMsgRcv((LONG)hWnd, nMsg);
}

CString CXYunFileMngr::In_Yun_GetTasksXml(const CString &strPara)
{
	In_CreateXTaskDB();

	if (m_oXDbTasks == NULL)
	{
		return _T("");
	}

	return m_oXDbTasks.GetTasksXml(strPara);
}

void CXYunFileMngr::In_Yun_SetTasksXml(CString &strXml)
{
	In_CreateXTaskDB();

	if (m_oXDbTasks == NULL)
	{
		return;
	}

	m_oXDbTasks.SetTasksXml(strXml);
}

void CXYunFileMngr::In_Yun_PopTasksSelWnd(const CString &strPara, long nPara)
{
	In_CreateXTaskDB();

	if (m_oXDbTasks == NULL)
	{
		return;
	}

	m_oXDbTasks.PopTasksSelWnd(strPara, nPara);
}


BOOL CXYunFileMngr::In_CreateXTaskDB()
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
