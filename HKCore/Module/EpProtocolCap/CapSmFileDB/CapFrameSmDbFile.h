//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapFrameSmDbFile.h  CCapFrameSmDbFile

#pragma once

#include "CapSmDbFile.h"


class CCapFrameSmDbArea : public CCapSmDbFileArea
{
public:
	CCapFrameSmDbArea();
	virtual ~CCapFrameSmDbArea();

	//���غ���
public:
	void Write(CCapCycleMemBufferMngr *pBufferMngr, POS posBegin, POS posEnd, EPSMDBFILEPOS &oSmDbFilePos);

	//˽�г�Ա����
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

//���غ���
public:
	void Write(CCapCycleMemBufferMngr *pBufferMngr, POS posBegin, POS posEnd, EPSMDBFILEPOS &oSmDbFilePos)
	{
		m_pFrameSmDbArea->Write(pBufferMngr, posBegin, posEnd, oSmDbFilePos);
	}

	void LocatePos(__int64 n64BeginPos, __int64 n64CurrPos);
	void CreateCapFrameSmDbServer(__int64 nDataSize, __int64 nDataView, const CString &strPath);
	void CreateCapFrameSmDbClient(__int64 nDataSize, __int64 nDataView, const CString &strPath);
	__int64 GetCurrPos()	{		return m_pFrameSmDbArea->GetCurrPos();	}
//˽�г�Ա����
private:
};

