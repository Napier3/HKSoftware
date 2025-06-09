
#ifndef _XYun_File_COM_h__
#define _XYun_File_COM_h__

#include "XYunFileApi_Global.h"


class CXYunFile_COM : public CExBaseList, public CYunFileInterface
{
public:
	CXYunFile_COM();
	virtual ~CXYunFile_COM();

	Yun::IYunApp m_oYunApp;	
	Yun::IYunOper m_oYunOper;
	Yun::IXDbTasks m_oXDbTasks;

	BOOL m_bLoginState;

public:
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



