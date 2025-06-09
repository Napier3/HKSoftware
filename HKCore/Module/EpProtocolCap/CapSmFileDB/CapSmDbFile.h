//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapSmDbFile.h  CCapSmDbFile

#pragma once

#include "..\ShareMem\ShareMemServerEx.h"
#include "..\ShareMem\ShareMemClientEx.h"
#include "SmFileDBQueryDef.h"

class CCapSmDbFileArea : public CExBaseObject
{
public:
	CCapSmDbFileArea();
	virtual ~CCapSmDbFileArea();

	//重载函数
public:
	void UnMap()	{	if (m_pSmFile)	{	m_pSmFile->UnMapView();	}	}
	virtual volatile __int64 SmWrite(LPVOID pData, long nLength);

	void CreateArea(const CString &strID, volatile __int64 n64BeginPos, volatile __int64 n64Length, DWORD dwOnceMapSize);
	BOOL IsAreaOpenSucc();
	void MapArea(volatile __int64 n64BeginPos);
	volatile __int64 GetCurrPos();
	volatile __int64 GetBeginPos()	{	return m_n64AreaBeginPos;	}
	volatile __int64 GetLength()		{	return m_n64Length;		}
	void LocateAreaPos(volatile __int64 n64BeginPos, volatile __int64 n64CurrPos);
	BOOL IsMapCycle()	{	return m_bMapCycle;	}
	LPVOID Read(__int64 n64BeginPos, DWORD dwLength);

	//私有成员变量
protected:
	volatile __int64 m_n64Length;    //文件的大小
	volatile __int64 m_n64AreaBeginPos;  //数据起始位置
	DWORD m_dwOnceMapSize;
	volatile __int64 m_n64AreaEndPos;
	BOOL m_bMapCycle;

	CShareMemClientEx * m_pSmFile;

	virtual BYTE* MapView(volatile __int64 &n64BeginPos, DWORD dwLen = 33554432, DWORD dwMinLen=1024);//32M

	void FreeArea();
};


class CCapSmDbFile : public CExBaseList
{
public:
	CCapSmDbFile();
	virtual ~CCapSmDbFile();

//重载函数
public:
	virtual long CreateCapSmDbFile(const CString &strFile, const CString &strCapSmDbName, volatile __int64 n64FileSize);
	virtual CCapSmDbFileArea* CreateArea( volatile __int64 n64BeginPos, volatile __int64 n64Length, DWORD dwOnceMapSize);
	BOOL IsMapCycle();

//私有成员变量
private:
	CString m_strFile;
	volatile __int64 m_n64FileSize;    //文件的大小

	CShareMemServerEx * m_pSmFileServer;

//私有成员变量访问方法
protected:
	void FreeDbFile();
};

void EpCap_CalSmDbSize(long nDataSize, long nDataView, volatile __int64 &n64DataSize, volatile __int64 &n64DataView);
void EpCap_CalSmDbSize(double nDataSize, double nDataView, volatile __int64 &n64DataSize, volatile __int64 &n64DataView);