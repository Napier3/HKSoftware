//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapSmDb.h  CCapSmDb

#pragma once

#include "..\..\..\Module\BaseClass\ExBaseObject.h"
#include "..\..\..\Module\ShareMem\ShareMemClientEx.h"
#include "..\..\..\Module\ShareMem\ShareMemServerEx.h"

#include "SmDbConfig.h"

//�����ļ��ڴ��������һ���ļ����Էֳɺܶ������������
class CSmDbAreaBase : public CExBaseObject
{
public:
	CSmDbAreaBase();
	virtual ~CSmDbAreaBase();

public:
	virtual BOOL CreateArea(CEpCapDbFileArea *pCfgArea);

//���غ���
public:
	void UnMap()	{	if (m_pSmFileClient)	{	m_pSmFileClient->UnMapView();	}	}
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
	CString GetSmDbID();

//˽�г�Ա����
protected:
	volatile __int64 m_n64Length;				//����Ĵ�С
	volatile __int64 m_n64AreaBeginPos;  //������ʼλ��
	DWORD m_dwOnceMapSize;              //ÿ��ӳ��Ĵ�С
	volatile __int64 m_n64AreaEndPos;    //����Ľ���Ϊֹ
	BOOL m_bMapCycle;                         //����д��ʱ���Ƿ��Ѿ�ѭ������

	CShareMemClientEx * m_pSmFileClient;   //�����ڴ�ͻ��˶���

	virtual BYTE* MapView(volatile __int64 n64BeginPos, DWORD dwLen = 33554432, DWORD dwMinLen=1024);//32M

	void FreeArea();

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

//˽�г�Ա����
protected:
	CString m_strFile;            //�ڴ湲���ļ��ľ���·��
	CShareMemServerEx * m_pSmFileServer;  //�ڴ湲���ļ������
	__int64 m_n64SmDbSize;   //DB�Ĵ�С
	CSmDbAreaBase *m_pSmDbArea;

//˽�г�Ա�������ʷ���
protected:
	void FreeDbFile();
	void CreateArea(CSmDbFileCfg *pCfg);
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

void EpCap_CalSmDbSize(long nDataSize, long nDataView, volatile __int64 &n64DataSize, volatile __int64 &n64DataView);
void EpCap_CalSmDbSize(double nDataSize, double nDataView, volatile __int64 &n64DataSize, volatile __int64 &n64DataView);