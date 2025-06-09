//StudioCommShareMemDefine.h

#pragma once

#ifndef _StudioCommShareMemDefine_h__
#define _StudioCommShareMemDefine_h__
#endif

#define	STUDIO_CMM_MEMFILENAME	      _T("_studio_msg_buffer.nysm")
#define	STUDIO_CMM_MAPNAME		      _T("_studio_comm_share_mem_buffer_")
#define	STUDIO_CMM_MAPSIZE			  524288


#define STUDIO_CMM_BUF_EXE_BUFFERLEN             65536
#define STUDIO_CMM_BUF_EXE_MAIN                  0
#define STUDIO_CMM_BUF_EXE_AUTOTEST              1
#define STUDIO_CMM_BUF_EXE_GBDEV                 2
#define STUDIO_CMM_BUF_EXE_PPDEV                 4

//用户信息
#define STUDIO_CMM_BUF_USER_NAME                 0
#define STUDIO_CMM_BUF_USER_PSW                  1024

//程序标记
#define STUDIO_CMM_BUF_EXE_ID                    0
#define STUDIO_CMM_BUF_EXE_MSG                   4
#define STUDIO_CMM_BUF_EXE_MSGRCVWND             8
#define STUDIO_CMM_BUF_EXE_MSGRCVTHREAD          12
#define STUDIO_CMM_BUF_EXE_COMMAND               16
#define STUDIO_CMM_BUF_EXE_FILECOUNT_MAX         20
#define STUDIO_CMM_BUF_EXE_FILECOUNT             24
#define STUDIO_CMM_BUF_EXE_FILEBEGIN             256
#define STUDIO_CMM_BUF_EXE_FILELEN               256

#define STUDIO_EXE_ID_LOGIN                   0
#define STUDIO_EXE_ID_MAIN                    1
#define STUDIO_EXE_ID_AUTOTEST                2
#define STUDIO_EXE_ID_GBDEV                   3
#define STUDIO_EXE_ID_RPTDEV                  4
#define STUDIO_EXE_ID_PPDEV                   5
#define STUDIO_EXE_ID_PPENGINE                6


//自动测试 - 主程序
#define STUDIO_CMD_AUTOTEST_TO_MAIN_TESTBEGIN    0X1001
#define STUDIO_CMD_AUTOTEST_TO_MAIN_TESTSTOP     0X1002
#define STUDIO_CMD_AUTOTEST_TO_MAIN_TESTCLOSE    0X1003
#define STUDIO_CMD_AUTOTEST_TO_MAIN_TASKSAVE     0X1004
#define STUDIO_CMD_AUTOTEST_TO_MAIN_CREATETASK   0X1005
#define STUDIO_CMD_AUTOTEST_TO_MAIN_CREATETEST   0X1006
//主程序 - 自动测试
#define STUDIO_CMD_MAIN_TO_AUTOTEST_OPENTEST     0X1007

//测试模板编辑 - 主程序
#define STUDIO_CMD_GBDEV_TO_MAIN_SAVE            0X2001
#define STUDIO_CMD_GBDEV_TO_MAIN_CLOSE           0X2002
//主程序 - 测试模板编辑
#define STUDIO_CMD_MAIN_TO_GBDEV_OPEN            0X2003

//规约模板编辑 - 主程序
#define STUDIO_CMD_PPDEV_TO_MAIN_SAVE            0X3001
#define STUDIO_CMD_PPDEV_TO_MAIN_CLOSE           0X3002
//主程序 - 规约模板编辑
#define STUDIO_CMD_MAIN_TO_PPDEV_OPEN            0X3003

#define STUDIO_CMD_FILE_INDEX_TASK               0
#define STUDIO_CMD_FILE_INDEX_PROJECT            1


#include "..\..\..\MODULE\SHAREMEM\ShareMemServerEx.h"
#include "..\..\..\MODULE\SHAREMEM\ShareMemClientEx.h"


class CStudioCommShareMemServer : public CExBaseObject
{
public:
	CStudioCommShareMemServer();
	virtual ~CStudioCommShareMemServer();

	CShareMemServerEx *m_pMemServer;

public:
	virtual BOOL CreateServer();
};

// //////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////
// //CStudioCommShareMemClient
class CStudioCommShareMemClient : public CExBaseObject
{
public:
	CStudioCommShareMemClient();
	virtual ~CStudioCommShareMemClient();
	
public:
	UINT  m_nExeID;
	DWORD *m_pdwExeMsg;
	DWORD *m_pdwExeMsgRevWnd;
	DWORD *m_pdwExeMsgRevThread;
	DWORD *m_pdwExeCommand;
	DWORD *m_pdwExeFileMaxCount;
	DWORD *m_pdwExeFileCount;
	DWORD *m_pdwExeFileBegin;
	DWORD *m_pdwExeFileLen;

public:
	CShareMemClientEx *m_pClient;

	BOOL IsValidate();
	void FreeClient();
	BOOL CreateClient(UINT nExeID);
	void WriteFile(long nIndex, const CString &strFile);
	CString ReadFile(long nIndex);
	void PostCommand(UINT nCmd, UINT nCmdParam);
	
	void InitExeDatas();
	CString GetString(long nPos, long nLen);
	void SetString(long nPos, const CString &strText);
	void UpdateMemClient();

private:
	long GetFilePos(long nIndex);
	BYTE* MapView(volatile __int64 &n64BeginPos, DWORD dwLen);

	volatile __int64 m_n64Length;    //文件的大小
	volatile __int64 m_n64AreaBeginPos;  //数据起始位置
	DWORD m_dwOnceMapSize;
	volatile __int64 m_n64AreaEndPos;

};

class CStudioCommShareMemMngr : CExBaseList
{
private:
	CStudioCommShareMemMngr();
	virtual ~CStudioCommShareMemMngr();

public:
	static CStudioCommShareMemMngr* g_pStudioCommShareMemMngr;
	static long g_nStudioCommShareMemMngr;
	static CStudioCommShareMemMngr* Create();
	static void Release();

	static CString GetUserName();
	static void    SetUserName(const CString &strUserName);
	
	static CStudioCommShareMemClient* GetLogin();
	static CStudioCommShareMemClient* GetMainExe();
	static CStudioCommShareMemClient* GetAutoTestExe();
	static CStudioCommShareMemClient* GetGbDevExe();
	static CStudioCommShareMemClient* GetRptDevExe();
	static CStudioCommShareMemClient* GetPpDevExe();
	static CStudioCommShareMemClient* GetPpEngineExe();
	

private:
	static CStudioCommShareMemClient* GetExeShareMem(UINT nExeID);

	CStudioCommShareMemServer *m_pStudioCommShareMemServer;
	CStudioCommShareMemClient *m_pStudioCommShareMemClient;
	
	static CString m_strUserName;
	
	CStudioCommShareMemClient* CreeateShareMem(UINT nExeID);
	CStudioCommShareMemClient* FindByExeID(UINT nExeID);
};


BOOL studio_cmd_autotest_to_main_testbegin(const CString &strProjectFile);
BOOL studio_cmd_autotest_to_main_teststop(const CString &strProjectFile);
BOOL studio_cmd_autotest_to_main_testclose(const CString &strProjectFile);
BOOL studio_cmd_autotest_to_main_tasksave(const CString &strTaskFile);
BOOL studio_cmd_autotest_to_main_createtask(const CString &strTaskFile);
BOOL studio_cmd_autotest_to_main_createtest(const CString &strProjectFile);
//主程序 - 自动测试
BOOL studio_cmd_main_to_autotest_opentest(const CString &strTaskFile, const CString &strProjectFile);

//测试模板编辑 - 主程序
BOOL studio_cmd_gbdev_to_main_save(const CString &strGbFile);
BOOL studio_cmd_gbdev_to_main_close(const CString &strGbFile);
//主程序 - 测试模板编辑
BOOL studio_cmd_main_to_gbdev_open(const CString &strGbFile);

//规约模板编辑 - 主程序
BOOL studio_cmd_ppdev_to_main_save(const CString &strPpFile);
BOOL studio_cmd_ppdev_to_main_close(const CString &strPpFile);
//主程序 - 规约模板编辑
BOOL studio_cmd_main_to_ppdev_open(const CString &strPpFile);

