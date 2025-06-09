
#ifndef _XYun_File_XmlRpc_h__
#define _XYun_File_XmlRpc_h__

#include "XYunFileApi_Global.h"


class CXYunFile_XmlRpc : public CExBaseList, public CYunFileInterface
{
private:
	CXYunFile_XmlRpc();
	virtual ~CXYunFile_XmlRpc();

	CYunConfig m_oYunConfig;
	Yun::IYunApp m_oYunApp;
	
	Yun::IYunOper m_oYunOper;
	Yun::IXDbTasks m_oXDbTasks;

// 	BOOL m_bBatchMode;
// 	HWND m_hMgRcvWnd;
// 	UINT  m_nYunOperMsg;
	BOOL m_bLoginState;

public:
	static CXYunFile_XmlRpc* g_pXYunFileMngr;
	static long g_nXYunFileMngrRef;

	static CXYunFile_XmlRpc* Create()
	{
		if (g_nXYunFileMngrRef == 0)
		{
			g_nXYunFileMngrRef = 1;
			g_pXYunFileMngr = new CXYunFile_XmlRpc();
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


#endif



