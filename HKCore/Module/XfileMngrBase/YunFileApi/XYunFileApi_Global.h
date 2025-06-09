
#ifndef _XYun_File_Api_Interface_h__
#define _XYun_File_Api_Interface_h__

#include "..\XFileMngr.h"

#define  YUN_OPER_RSLT_MSG   (WM_USER + 930)

class CYunFileInterface
{
public:
	CYunFileInterface();
	virtual ~CYunFileInterface();

public:
	virtual BOOL xyun_IsLogin()		{ return FALSE;	};
	virtual BOOL xyun_IsLogout()		{	return FALSE;	}
	virtual BOOL xyun_IsLoginSucc() = 0;

	virtual long xyun_DownLoadFile(const CString &strFile) = 0;
	virtual long xyun_UpLoadFile(const CString &strFile) = 0;
	virtual long xyun_DeleteFile(const CString &strFile) = 0;

	virtual long xyun_DownLoadFolder(const CString &strFolder) = 0;
	virtual long xyun_UpLoadFolder(const CString &strFolder) = 0;
	virtual long xyun_DeleteFolder(const CString &strFolder) = 0;

	//XTestDB
	virtual void xyun_AttachMsgRcvWnd(HWND hWnd, UINT nMsg)	{};
	virtual CString xyun_GetTasksXml(const CString &strPara)			{	return _T("");	}
	virtual void xyun_SetTasksXml(CString &strXml)						{}
	virtual void xyun_PopTasksSelWnd(const CString &strPara, long nPara)	{};
	virtual BOOL xyun_CreateXTaskDB()				{	return FALSE;	}

public:
	//2016-12-27  批量下载增加
	virtual long xyun_DownLoadFiles(const CStringArray &astrFiles);
	virtual long xyun_UpLoadFiles(const CStringArray &astrFiles);
	virtual long xyun_DeleteFiles(const CStringArray &astrFiles);


public:
	virtual long xyun_DownLoad(CExBaseObject *pXfxObj, BOOL bAllSameNameFiles);
	virtual long xyun_UpLoad(CExBaseObject *pXfxObj, BOOL bAllSameNameFiles);
	virtual long xyun_Delete(CExBaseObject *pXfxObj, BOOL bAllSameNameFiles);
	
	virtual long xyun_DownLoad(CExBaseObject *pXfxObj);
	virtual long xyun_UpLoad(CExBaseObject *pXfxObj);
	virtual long xyun_Delete(CExBaseObject *pXfxObj);

	virtual long xyun_DownLoad(CXFile *pXFile);
	virtual long xyun_UpLoad(CXFile *pXFile);
	virtual long xyun_Delete(CXFile *pXFile);

	virtual long xyun_DownLoad(CXFolder *pXFolder);
	virtual long xyun_UpLoad(CXFolder *pXFolder);
	virtual long xyun_Delete(CXFolder *pXFolder);

public:
	virtual long xyun_SetBatchOperMode(BOOL bBatchMode, HWND hWnd, UINT nMsg);
	virtual long xyun_BatchOper();
	
protected:
	BOOL m_bAllSameNameFiles;
	BOOL m_bBatchMode;
	HWND m_hMgRcvWnd;
	UINT  m_nYunOperMsg;

};


#endif



