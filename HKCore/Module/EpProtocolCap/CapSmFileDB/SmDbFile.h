//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SmDbFile.h  CSmDbFile

#pragma once

#include "SmFileDBGlobal.h"
#include "SmDbTable.h"

class CSmDbFileArea : public CExBaseObject
{
public:
	CSmDbFileArea();
	virtual ~CSmDbFileArea();

	//���غ���
public:
	virtual long SmWrite(CSmDbData *pData);
	virtual long SmWrite(CSmDbBaseList *pList);
	virtual long SmWrite(CSmDbTable *pTable);

	void CreateArea(const CString &strID, __int64 n64BeginPos, __int64 n64Length, DWORD dwOnceMapSize);

	//˽�г�Ա����
private:
	__int64 m_n64Length;    //�ļ��Ĵ�С
	__int64 m_n64BeginPos;  //������ʼλ��
	__int64 m_n64CurrPos; //��ǰλ��
	DWORD m_dwCurrWriteLen;   //һ��д��ĳ���
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

//���غ���
public:
	virtual long CreateSmDbFile(const CString &strFile, const CString &strSmDbName, __int64 n64FileSize);
	virtual CSmDbFileArea* CreateArea( __int64 n64BeginPos, __int64 n64Length, DWORD dwOnceMapSize);

//˽�г�Ա����
private:
	CString m_strFile;
	__int64 m_n64FileSize;    //�ļ��Ĵ�С

	CShareMemServerEx * m_pSmFileServer;

//˽�г�Ա�������ʷ���
protected:
	void FreeDbFile();
};

