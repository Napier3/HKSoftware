//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmDbFileBase.h  CSmDbFileBase

#pragma once

#include "../BaseClass/ExBaseObject.h"
#include "../ShareMem/ShareMemClientEx.h"
#include "../ShareMem/ShareMemServerEx.h"

#include "SmDbConfig.h"
#include "XSmMemBufferMngr.h"

//共享文件内存区域对象，一个文件可以分成很多个独立的区域
class CSmDbAreaBase : public CExBaseObject
{
public:
	CSmDbAreaBase();
	virtual ~CSmDbAreaBase();

public:
	virtual BOOL CreateArea(CEpCapDbFileArea *pCfgArea);
	virtual void CreateArea(const CString &strID, volatile __int64 n64BeginPos, volatile __int64 n64Length, DWORD dwOnceMapSize);
	BOOL IsAreaOpenSucc();
	void MapArea(volatile __int64 n64BeginPos);
	void UnMap()	{	if (m_pSmFileClient)	{	m_pSmFileClient->UnMapView();	}	}
	
	volatile __int64 GetCurrPos();
	volatile __int64 GetBeginPos()	{	return m_n64AreaBeginPos;	}
	volatile __int64 GetLength()		{	return m_n64Length;		}
	
	BOOL IsMapCycle()	{	return m_bMapCycle;	}

//私有成员变量
protected:
	volatile __int64 m_n64Length;				//区域的大小
	volatile __int64 m_n64AreaBeginPos;  //区域起始位置
	DWORD m_dwOnceMapSize;              //每次映射的大小
	volatile __int64 m_n64AreaEndPos;    //区域的结束位置
	BOOL m_bMapCycle;                         //区域写的时候，是否已经循环覆盖

	CShareMemClientEx * m_pSmFileClient;   //共享内存客户端对象

	virtual BYTE* MapView(volatile __int64 n64BeginPos, DWORD dwLen = 33554432, DWORD dwMinLen=1024);//32M
	void FreeArea();

public:
	virtual LPVOID LocateAreaPos(volatile __int64 n64CurrPos);
	virtual void Reset()	{			}

	virtual volatile __int64 SmWrite(LPVOID pData, long nLength);
	virtual long GetWriteCount(CXSmMemBufferMngr *pBufferMngr);
	virtual long Write(CXSmMemBufferMngr *pBufferMngr);
	virtual void Write(CXSmMemBufferMngr *pBufferMngr,long nBeginIndex, long nEndIndex);

	LPVOID Read(__int64 n64BeginPos, DWORD dwLength);
	BOOL Read(LPVOID pBuffer, __int64 n64BeginPos, DWORD dwLength);  //2020-06-12   lijunqing
	virtual void ReadBuffer(__int64 n64Pos, long nLen, CXMemBufferBse *pDestBuffer);
	virtual void ReadBuffer(CXSmMemBuffer *pBuffer, CXMemBufferBse *pDestBuffer);
	void   FlushView()    {     m_pSmFileClient->FlushView();                }
	void   FlushView(LPVOID pBuffer, DWORD dwSize)    {     m_pSmFileClient->FlushView(pBuffer, dwSize);                }

	DWORD GetOnceMapSize() { return m_dwOnceMapSize; }

};

//共享内存服务器文件对象
class CSmDbFileBase : public CExBaseList
{
public:
	CSmDbFileBase();
	virtual ~CSmDbFileBase();

	__int64 GetFileSize();

//重载函数
public:
	//服务端创建
	virtual long CreateSmDb(CSmDbFileCfg *pCfg);
	virtual long CreateSmDb(const CString &strFile, const CString &strSmDbName, __int64 n64FileSize);
	virtual void CreateSmDb(volatile __int64 nDbSize, volatile __int64 nViewSize, const CString &strID, const CString &strPath);

	//客户端
	virtual long OpenSmDb(CSmDbFileCfg *pCfg);
	virtual void OpenSmDb(volatile __int64 nDbSize, const CString &strID, const CString &strPath);
	virtual CSmDbAreaBase* CreateArea( __int64 n64BeginPos, __int64 n64Length, DWORD dwOnceMapSize, BOOL bAddTail=FALSE);
	virtual CSmDbAreaBase* CreateNewArea(CEpCapDbFileArea *pCfgArea = NULL);
	virtual LPVOID LocatePos(volatile __int64 n64CurrPos)	{		return m_pSmDbArea->LocateAreaPos(n64CurrPos);	}

//私有成员变量
protected:
	CString m_strFile;            //内存共享文件的绝对路径
	CShareMemServerEx * m_pSmFileServer;  //内存共享文件服务端
	__int64 m_n64SmDbSize;   //DB的大小
	CSmDbAreaBase *m_pSmDbArea;  //服务端的缺省写对象
	__int64 m_n64BeginPos;

//私有成员变量访问方法
protected:
	void FreeDbFile();
	void CreateArea(CSmDbFileCfg *pCfg);

public:
	virtual BOOL IsAreaOpenSucc();
	virtual long Write(CXSmMemBufferMngr *pBufferMngr);
// 	virtual void Free(CXSmMemBufferMngr *pBufferMngr);
	virtual void ReadBuffer(__int64 n64Pos, long nLen, CXMemBufferBse *pDestBuffer);

	CShareMemServerEx *GetSmFileServer() { return m_pSmFileServer; }
	CSmDbAreaBase* GetSmDbArea()	{	return m_pSmDbArea;	}
};

//SmDB文件管理，即数据库
class CSmDbFileMngrBase : public CExBaseList
{
public:
	CSmDbFileMngrBase();
	virtual ~CSmDbFileMngrBase();

protected:
	CSmDbConfig m_oSmDbConfig;

public:
	virtual BOOL OpenCapDbConfigFile();
	virtual CString GetCapDbConfigFile();
	virtual BOOL CreateServerByDbConfigFile();
	virtual BOOL OpenByDbConfigFile();

	virtual CSmDbFileBase* CreateNewSmDB(CSmDbFileCfg *pCfg);
	virtual CSmDbFileBase* OpenSmDB(CSmDbFileCfg *pCfg);
	
public:

};

CString EpCap_GetCapDbConfigFile();

void EpCap_CalSmDbSize(long nDataSize, long nDataView, volatile __int64 &n64DataSize, volatile __int64 &n64DataView);
void EpCap_CalSmDbSize(double nDataSize, double nDataView, volatile __int64 &n64DataSize, volatile __int64 &n64DataView);
