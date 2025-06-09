#pragma once

#include "..\XFile.h"
#include <afxsock.h>

#define  XFCENTER_BUF_LEN          4108
#define  XFCENTER_FILE_BUF_LEN   4096

#define  XFCENTER_CMD_DOWNLOADFILE         _T("download file")
#define  XFCENTER_CMD_UPLOADFILE              _T("upload file")
#define  XFCENTER_CMD_DELETEFILE               _T("delete file")
#define  XFCENTER_CMD_RENAMEFILE              _T("rename file")
#define  XFCENTER_CMD_CREATEFOLDER          _T("create folder")
#define  XFCENTER_CMD_DOWNLOADFOLDER    _T("download folder")
#define  XFCENTER_CMD_UPLOADFOLDER         _T("upload folder")
#define  XFCENTER_CMD_DELETEFOLDER          _T("delete folder")
#define  XFCENTER_CMD_RENAMEFOLDER         _T("rename folder")
#define  XFCENTER_CMD_QUERY                     _T("query")

#define  XFCENTER_CMD_PARA_BUCKET            _T("bucket")
#define  XFCENTER_CMD_PARA_FILE                  _T("file-path")
#define  XFCENTER_CMD_PARA_DESTFILE           _T("dest file-path")
#define  XFCENTER_CMD_PARA_FOLDER             _T("folder-path")
#define  XFCENTER_CMD_PARA_DESTFOLDER      _T("dest folder-path")
#define  XFCENTER_CMD_PARA_KEYS                 _T("keys")
#define  XFCENTER_CMD_PARA_ROOTPATH            _T("root-path")

#define  WM_XFCENTERTCPCLIENT_CMD   (WM_USER+2150)


#define XFCENTER_BASECLASS          (CLASSID_BASECLASS   + 0X000F0000)
#define XFCENTER_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X000F0000)

#define XFCENTER_FILE            (XFCENTER_BASECLASS   + 0X00000001)
#define XFCENTER_FOLDER       (XFCENTER_EXLISTCLASS + 0X00000002)

class CXFcenterFile : public CExBaseObject
{
public:
	CXFcenterFile();
	virtual ~CXFcenterFile();

	SYSTEMTIME m_dtTime;
	DWORD   m_nFileSize;

	//重载函数
public:
	virtual UINT GetClassID() {    return XFCENTER_FILE;   }
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	//私有成员变量
private:

	//私有成员变量访问方法
public:


};


class CXFcenterFolder : public CExBaseList
{
public:
	CXFcenterFolder();
	virtual ~CXFcenterFolder();

	DWORD   m_nFileSize;
	SYSTEMTIME m_dtTime;

	//重载函数
public:
	virtual UINT GetClassID() {    return XFCENTER_FOLDER;   }
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	//私有成员变量
private:

	//私有成员变量访问方法
public:


};

// void xfile_QueryAllFiles(CXFolder *pFolder, CXFcenterFolder *pDest);



//////////////////////////////////////////////////////////////////////////
//
typedef struct xfcenter_cmd_ret
{
	DWORD dwCmdID;    //
	DWORD dwRcvIndex; //
	DWORD dwRcvLen;    //
}XFCENTER_CMD_RET;

typedef struct xfcenter_cmd_file
{
	DWORD dwCmdID;    //
}XFCENTER_CMD_FILE;

typedef struct xfcenter_cmd_file_buf
{
	DWORD dwCmdID;
	DWORD dwIndex; //
	DWORD dwLen; //
	CHAR    pBuffer[XFCENTER_FILE_BUF_LEN];
}XFCENTER_CMD_FILE_BUF;

typedef struct xfcenter_cmd_file_info
{
	DWORD dwCmdID;
	DWORD dwSize; //
	SYSTEMTIME    dtTime;
	char      pszPath[MAX_PATH];
}XFCENTER_CMD_FILE_INFO;

//
#define XFCENTER_OPTR_SVR_TO_CLIENT       0X01
#define XFCENTER_OPTR_CLIENT_TO_SVR       0X02
#define XFCENTER_OPTR_QUERY            0X03

#define XFCENTER_CMDID_ERROR               0X00
#define XFCENTER_CMDID_FILE_INFO          0X01
#define XFCENTER_CMDID_FILE_BUFF          0X02
#define XFCENTER_CMDID_FILE_FINISH       0X03

#define XFCENTER_CMDID_QUERY_FILES_BUF         0X04
#define XFCENTER_CMDID_QUERY_FILES_FINISH     0X05

#define XFCENTER_RECV_BUF_LEN              65536
#define XFCENTER_RECV_MAX_LEN             XFCENTER_BUF_LEN

#define XFCENTER_QUERY_MODE_AND           0X01
#define XFCENTER_QUERY_MODE_OR             0X00
#define XFCENTER_QUERY_MODEKEY_AND           _T("and")
#define XFCENTER_QUERY_MODEKEY_OR             _T("or")

typedef struct xfcenter_thread_param
{
	DWORD  nCmdID;
	USHORT nServerPort;
	char       pszServerIP[20];
	CWnd    *pWndMsgRcv;
	UINT      nMsgRcv;

	CWinThread    *pThread;
	UINT      nCmdFinishMsg;
	BOOL     *pbXFcenterFinish;
	CEvent   *pEvent;

	CString         strCmdID;
	CString         strRootPath;
	//CXFileMngr    *pXFileMngr;
	CString         strBucket;
	CStringArray  astrPath;
	CStringArray  astrKeys;
	DWORD       dwKeysMode;

	//2022-2-15  lijunqing
	SOCKET sktClient;
	CSocket *sktClientRef;
}XFCENTER_THREAD_PARAM;

static long xfcenter_get_file_buf_send_len(XFCENTER_CMD_FILE_BUF &cmd_file_buf)
{
	return 3*sizeof(DWORD) + cmd_file_buf.dwLen;
}

void xfcenter_set_thread_finish(XFCENTER_THREAD_PARAM *pParam);
void xfcenter_log_thread_param(XFCENTER_THREAD_PARAM *pParam);

// CXFolder* xfcenter_add_folder(CXFileMngr *pXFileMngr, const CString &strFolder);
// CXFile* xfcenter_add_file(CXFileMngr *pXFileMngr, const CString &strPath);

#define  XFCENTER_TIME_OUT     -1

extern BOOL g_bLogXFcenterTransInfo;