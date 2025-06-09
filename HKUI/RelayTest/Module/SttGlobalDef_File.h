#pragma once

#include "../../Module/API/FileApi.h"
#include "../../Module/API/StringApi.h"

//////////////////////////////////////////////
//报文格式
#define STT_PKG_HEAD_LEN	14
#define STT_PKG_INDEX_TYPECMD	4
#define STT_PKG_INDEX_DATALEN	11
#define STT_PKG_INDEX_DATALEN_FILEMODE		11
#define STT_PKG_INDEX_DATALEN_FILEDATALEN	12
#define STT_PKG_INDEX_IDTESTER		5
// #define STT_PKG_INDEX_SRCID		5
// #define STT_PKG_INDEX_DSTID		7
#define STT_PKG_INDEX_SEQUENCE	9
//	#define STT_PKG_INDEX_COMPRESS	11


#define STT_PKG_INDEX_DATA		STT_PKG_HEAD_LEN

#define STT_PKG_FILEMODE_FILESIZE_LEN		4
#define STT_PKG_FILEMODE_FILETIME_LEN		9//年：2B,月日时分秒：5B，毫秒：2B
#define STT_PKG_INDEX_FILESIZE			STT_PKG_INDEX_DATA
#define STT_PKG_INDEX_FILETIME			(STT_PKG_INDEX_FILESIZE+STT_PKG_FILEMODE_FILESIZE_LEN)
#define STT_PKG_INDEX_FILENAME			(STT_PKG_INDEX_FILETIME+STT_PKG_FILEMODE_FILETIME_LEN)

#define STT_PKG_SEND_FILEDATA_MAXLEN		32768  //2048  //4096  //16384  //4096

#define STT_FILECMD_MAX_LEN	(STT_PKG_SEND_FILEDATA_MAXLEN+STT_PKG_HEAD_LEN)
#define STT_SOCKET_RECV_SIZE		STT_FILECMD_MAX_LEN

#define STT_FILEMODE_FILENAME		0x0
#define STT_FILEMODE_LASTFRAME		0xFF

//文件命令错误编码
#define STT_FILEMODE_ERRNO_TRANSMITERROR	0xF1
#define STT_FILEMODE_ERRNO_FILENOTEXIST				0xF2
#define STT_FILEMODE_ERRNO_OCCUPIED_OPENFAILED		0xF3
#define STT_FILEMODE_ERRNO_DELETEFILE_FAILED		0xF4
#define STT_FILEMODE_ERRNO_DELETEFOLDER_FAILED		0xF5
#define STT_FILEMODE_ERRNO_CREATERFOLDER_FAILED		0xF6
#define STT_FILEMODE_ERRNO_GETDIR_FAILED			0xF7
#define STT_FILEMODE_ERRNO_READFILE_FAILED			0xF8

/////////////////////////////////////
//文件命令类型
#define STT_CMD_TYPE_FILE_WRITE			0xF0
#define STT_CMD_TYPE_FILE_READ			0xF1
#define STT_CMD_TYPE_FILE_DELETE		0xF2
#define STT_CMD_TYPE_FILE_RENAME		0xF3
#define STT_CMD_TYPE_FILE_GETDIR		0xF4
#define STT_CMD_TYPE_FILE_MOVE			0xF5

//////////////////////////////////////////////////////////////////////////
inline bool stt_is_cmd_a_file_cmd(BYTE nCmdType)
{
	return ((nCmdType >= STT_CMD_TYPE_FILE_WRITE) && (nCmdType <= STT_CMD_TYPE_FILE_MOVE));
}

inline bool stt_pkg_match_head(BYTE *pPkg)
{
	return (*pPkg == 0xEB) && (*(pPkg+1) == 0x90) && (*(pPkg+2) == 0xEB) && (*(pPkg+3) == 0x90);
}

inline bool stt_pkg_type_is_file(BYTE *pPkg)
{
	return stt_is_cmd_a_file_cmd(pPkg[STT_PKG_INDEX_TYPECMD]);
}

inline long stt_pkg_get_cmd_type(BYTE *pPkg)
{
	return pPkg[STT_PKG_INDEX_TYPECMD];
}

inline bool stt_is_ret_file_cmd_fail(long nMode)
{
	return ((nMode < STT_FILEMODE_LASTFRAME) && (nMode >= STT_FILEMODE_ERRNO_TRANSMITERROR));
}

inline long stt_pkg_get_idtester(BYTE *pPkg)
{
	return pPkg[STT_PKG_INDEX_IDTESTER] + (pPkg[STT_PKG_INDEX_IDTESTER+1]<<8)
		+ (pPkg[STT_PKG_INDEX_IDTESTER+2]<<16) + (pPkg[STT_PKG_INDEX_IDTESTER+3]<<24);
}

inline long stt_pkg_get_send_index(BYTE *pPkg)
{
	return pPkg[STT_PKG_INDEX_SEQUENCE] + (pPkg[STT_PKG_INDEX_SEQUENCE+1]<<8);
}

inline long stt_pkg_get_data_len_cmd_file(BYTE *pPkg)
{
	return pPkg[STT_PKG_INDEX_DATALEN_FILEDATALEN] + (pPkg[STT_PKG_INDEX_DATALEN_FILEDATALEN+1]<<8);
}

//文件名命令数据格式：4字节：文件大小，9字节：文件时间，文件名
inline char* stt_pkg_get_cmd_file_name(BYTE *pPkg, char **ppszFileName)
{
	long nLenFileName = stt_pkg_get_data_len_cmd_file(pPkg) - STT_PKG_FILEMODE_FILESIZE_LEN - STT_PKG_FILEMODE_FILETIME_LEN;
	
	if (nLenFileName <= 0)
	{
		return NULL;
	}

	char *pszFileName = new char[nLenFileName+5];
	memcpy(pszFileName, (char*)pPkg + STT_PKG_INDEX_FILENAME, nLenFileName);
	pszFileName[nLenFileName] = 0;
	*ppszFileName = pszFileName;

	return pszFileName;
}

inline long stt_pkg_get_cmd_file_size(BYTE *pPkg)
{
	long nFileSize = 0;
	memcpy(&nFileSize, (char*)pPkg + STT_PKG_INDEX_FILESIZE, STT_PKG_FILEMODE_FILESIZE_LEN);

	return nFileSize;
}

inline SYSTEMTIME stt_pkg_get_cmd_file_time(BYTE *pPkg)
{
	SYSTEMTIME tmFile;
	BYTE *pTemp = pPkg + STT_PKG_INDEX_FILETIME;

	tmFile.wYear = (DWORD)pTemp[0] + (pTemp[1]<<8) ;
	tmFile.wMonth = pTemp[2];
	tmFile.wDay = pTemp[3];
	tmFile.wHour = pTemp[4];
	tmFile.wMinute = pTemp[5];
	tmFile.wSecond = pTemp[6];
	tmFile.wMilliseconds = (DWORD)pTemp[7] + (pTemp[8]<<8) ;

	return tmFile;
}

inline void stt_pkg_set_cmd_file_time(BYTE *pPkg,const char* pszFileName)
{
	SYSTEMTIME tmFile;
	CString strFileTime = file_get_time(pszFileName);
	CString_To_SystemTime(strFileTime, tmFile);

	BYTE *pTemp = pPkg + STT_PKG_INDEX_FILETIME;
	pTemp[0] = tmFile.wYear & 0xff;
	pTemp[1] = tmFile.wYear >> 8;
	pTemp[2] = tmFile.wMonth & 0xff;
	pTemp[3] = tmFile.wDay & 0xff;
	pTemp[4] = tmFile.wHour & 0xff;
	pTemp[5] = tmFile.wMinute & 0xff;
	pTemp[6] = tmFile.wSecond & 0xff;
	pTemp[7] = tmFile.wMilliseconds & 0xff;
	pTemp[8] = tmFile.wMilliseconds >> 8;
}

inline long stt_pkg_get_data_len_cmd_other(BYTE *pPkg)
{
	return pPkg[STT_PKG_INDEX_DATALEN] + (pPkg[STT_PKG_INDEX_DATALEN+1]<<8)
		+ (pPkg[STT_PKG_INDEX_DATALEN+2]<<16);
}

inline long stt_pkg_get_data_len(BYTE *pPkg)
{
	if (stt_pkg_type_is_file(pPkg))
	{
		return stt_pkg_get_data_len_cmd_file(pPkg);
	}
	else
	{
		return stt_pkg_get_data_len_cmd_other(pPkg);
	}
}

inline long stt_pkg_get_cmd_file_mode(BYTE *pPkg)
{
	return pPkg[STT_PKG_INDEX_DATALEN_FILEMODE];
}

inline void stt_pkg_set_head(BYTE *pPkg)
{		
	pPkg[0] = 0xEB;
	pPkg[1] = 0x90;
	pPkg[2] = 0xEB;
	pPkg[3] = 0x90;
}

inline void stt_pkg_set_cmd_type(BYTE *pPkg, BYTE nCmdType)
{
	pPkg[STT_PKG_INDEX_TYPECMD] = nCmdType;
}

inline void stt_pkg_set_idtester(BYTE *pPkg, DWORD nIDTester)
{
	pPkg[STT_PKG_INDEX_IDTESTER] = nIDTester & 0xFF;
	pPkg[STT_PKG_INDEX_IDTESTER+1] = (nIDTester >> 8)  & 0xFF;
	pPkg[STT_PKG_INDEX_IDTESTER+2] = (nIDTester >> 16)  & 0xFF;
	pPkg[STT_PKG_INDEX_IDTESTER+3] = (nIDTester >> 24)  & 0xFF;
}

inline void stt_pkg_set_send_index(BYTE *pPkg, long nSendIndex)
{
	pPkg[STT_PKG_INDEX_SEQUENCE] = nSendIndex & 0xFF;
	pPkg[STT_PKG_INDEX_SEQUENCE+1] = (nSendIndex >> 8)  & 0xFF;
}

inline void stt_pkg_set_data_len_cmd_file(BYTE *pPkg, long nMode,  long nLen)
{
	pPkg[STT_PKG_INDEX_DATALEN_FILEMODE] = nMode & 0xFF;
	pPkg[STT_PKG_INDEX_DATALEN_FILEDATALEN] = nLen & 0xFF;
	pPkg[STT_PKG_INDEX_DATALEN_FILEDATALEN+1] = (nLen >> 8)  & 0xFF;
}

inline void stt_pkg_set_data_len_cmd_other(BYTE *pPkg, long nLen)
{
	pPkg[STT_PKG_INDEX_DATALEN] = nLen & 0xFF;
	pPkg[STT_PKG_INDEX_DATALEN+1] = (nLen >> 8)  & 0xFF;
	pPkg[STT_PKG_INDEX_DATALEN+2] = (nLen >> 16)  & 0xFF;
}

//2019-12-28   lijq
inline void stt_InitPktBuffer_Head_File(BYTE *pPkgBuffer,long nTypeCmd, long nMode
							, long nDataLen, DWORD nIDTester, long nSendIndex, BYTE bCompress)
{
#ifdef _PSX_IDE_QT_
        (void)bCompress;
#endif
    stt_pkg_set_head(pPkgBuffer);
	stt_pkg_set_cmd_type(pPkgBuffer, (BYTE)nTypeCmd);
	stt_pkg_set_idtester(pPkgBuffer, nIDTester);
	stt_pkg_set_send_index(pPkgBuffer, nSendIndex);
	//	stt_pkg_set_compress(pPkgBuffer, bCompress);

	stt_pkg_set_data_len_cmd_file(pPkgBuffer, nMode, nDataLen);
}
