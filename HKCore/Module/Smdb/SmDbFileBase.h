//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SmDbFileBase.h  CSmDbFileBase

#pragma once

#include "../BaseClass/ExBaseObject.h"
#include "../ShareMem/ShareMemClientEx.h"
#include "../ShareMem/ShareMemServerEx.h"

#include "SmDbConfig.h"
#include "XSmMemBufferMngr.h"

//�����ļ��ڴ��������һ���ļ����Էֳɺܶ������������
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

//˽�г�Ա����
protected:
	volatile __int64 m_n64Length;				//����Ĵ�С
	volatile __int64 m_n64AreaBeginPos;  //������ʼλ��
	DWORD m_dwOnceMapSize;              //ÿ��ӳ��Ĵ�С
	volatile __int64 m_n64AreaEndPos;    //����Ľ���λ��
	BOOL m_bMapCycle;                         //����д��ʱ���Ƿ��Ѿ�ѭ������

	CShareMemClientEx * m_pSmFileClient;   //�����ڴ�ͻ��˶���

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

//�����ڴ�������ļ�����
class CSmDbFileBase : public CExBaseList
{
public:
	CSmDbFileBase();
	virtual ~CSmDbFileBase();

	__int64 GetFileSize();

//���غ���
public:
	//����˴���
	virtual long CreateSmDb(CSmDbFileCfg *pCfg);
	virtual long CreateSmDb(const CString &strFile, const CString &strSmDbName, __int64 n64FileSize);
	virtual void CreateSmDb(volatile __int64 nDbSize, volatile __int64 nViewSize, const CString &strID, const CString &strPath);

	//�ͻ���
	virtual long OpenSmDb(CSmDbFileCfg *pCfg);
	virtual void OpenSmDb(volatile __int64 nDbSize, const CString &strID, const CString &strPath);
	virtual CSmDbAreaBase* CreateArea( __int64 n64BeginPos, __int64 n64Length, DWORD dwOnceMapSize, BOOL bAddTail=FALSE);
	virtual CSmDbAreaBase* CreateNewArea(CEpCapDbFileArea *pCfgArea = NULL);
	virtual LPVOID LocatePos(volatile __int64 n64CurrPos)	{		return m_pSmDbArea->LocateAreaPos(n64CurrPos);	}

//˽�г�Ա����
protected:
	CString m_strFile;            //�ڴ湲���ļ��ľ���·��
	CShareMemServerEx * m_pSmFileServer;  //�ڴ湲���ļ������
	__int64 m_n64SmDbSize;   //DB�Ĵ�С
	CSmDbAreaBase *m_pSmDbArea;  //����˵�ȱʡд����
	__int64 m_n64BeginPos;

//˽�г�Ա�������ʷ���
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

//SmDB�ļ����������ݿ�
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
