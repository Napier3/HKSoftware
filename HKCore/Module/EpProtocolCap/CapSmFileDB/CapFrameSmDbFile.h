//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapFrameSmDbFile.h  CCapFrameSmDbFile

#pragma once

#include "CapSmDbFile.h"


class CCapFrameSmDbArea : public CCapSmDbFileArea
{
public:
	CCapFrameSmDbArea();
	virtual ~CCapFrameSmDbArea();

	//重载函数
public:
	void Write(CCapCycleMemBufferMngr *pBufferMngr, POS posBegin, POS posEnd, EPSMDBFILEPOS &oSmDbFilePos);

	//私有成员变量
private:
	

};

class CCapFrameSmDbFile : public CCapSmDbFile
{
public:
	CCapFrameSmDbFile();
	virtual ~CCapFrameSmDbFile();

	static const CString g_strCapFrameSmDbFile;
	static const CString g_strCapFrameSmDbID;

	CCapFrameSmDbArea *m_pFrameSmDbArea;

//重载函数
public:
	void Write(CCapCycleMemBufferMngr *pBufferMngr, POS posBegin, POS posEnd, EPSMDBFILEPOS &oSmDbFilePos)
	{
		m_pFrameSmDbArea->Write(pBufferMngr, posBegin, posEnd, oSmDbFilePos);
	}

	void LocatePos(__int64 n64BeginPos, __int64 n64CurrPos);
	void CreateCapFrameSmDbServer(__int64 nDataSize, __int64 nDataView, const CString &strPath);
	void CreateCapFrameSmDbClient(__int64 nDataSize, __int64 nDataView, const CString &strPath);
	__int64 GetCurrPos()	{		return m_pFrameSmDbArea->GetCurrPos();	}
//私有成员变量
private:
};

