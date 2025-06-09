//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmDbFile.h  CSmDbFile

#pragma once

#include "SmFileDBGlobal.h"
#include "SmDbTable.h"

class CSmDbFileArea : public CExBaseObject
{
public:
	CSmDbFileArea();
	virtual ~CSmDbFileArea();

	//重载函数
public:
	virtual long SmWrite(CSmDbData *pData);
	virtual long SmWrite(CSmDbBaseList *pList);
	virtual long SmWrite(CSmDbTable *pTable);

	void CreateArea(const CString &strID, __int64 n64BeginPos, __int64 n64Length, DWORD dwOnceMapSize);

	//私有成员变量
private:
	__int64 m_n64Length;    //文件的大小
	__int64 m_n64BeginPos;  //数据起始位置
	__int64 m_n64CurrPos; //当前位置
	DWORD m_dwCurrWriteLen;   //一次写入的长度
	DWORD m_dwOnceMapSize;
	__int64 m_n64EndPos;

	CShareMemClientEx * m_pSmFile;

	BYTE* MapView(__int64 n64BeginPos, DWORD dwLen = 33554432, DWORD dwMinLen=1024);//32M

	void CalCurrPos()
	{
		m_n64CurrPos = m_n64CurrPos +  m_dwCurrWriteLen;
		m_dwCurrWriteLen = 0;
	}

	void FreeArea();

};


class CSmDbFile : public CExBaseList
{
public:
	CSmDbFile();
	virtual ~CSmDbFile();

//重载函数
public:
	virtual long CreateSmDbFile(const CString &strFile, const CString &strSmDbName, __int64 n64FileSize);
	virtual CSmDbFileArea* CreateArea( __int64 n64BeginPos, __int64 n64Length, DWORD dwOnceMapSize);

//私有成员变量
private:
	CString m_strFile;
	__int64 m_n64FileSize;    //文件的大小

	CShareMemServerEx * m_pSmFileServer;

//私有成员变量访问方法
protected:
	void FreeDbFile();
};

