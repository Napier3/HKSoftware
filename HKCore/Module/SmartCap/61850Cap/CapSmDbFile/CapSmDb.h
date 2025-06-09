//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapSmDb.h  CCapSmDb

#pragma once

#include "CapFrameDbFile.h"
// #include "CapDeviceDataSmDbFile.h"
#include "CapDbIndexSmDbFile.h"
#include "CapDbIndex0SmDbFile.h"
// #include "CapFrmDvSmDbFile.h"
//#include "CapDataSmDbFile.h"

class CCapSmDb : public CExBaseObject
{
public:
	CCapSmDb();
	virtual ~CCapSmDb();

public:
	volatile __int64 m_nIndex0DbHeadSize;
	volatile __int64 m_nIndex0DbHeadView;

	volatile __int64 m_nIndexDbSize;
	volatile __int64 m_nIndexDbView;

// 	volatile __int64 m_nDeviceDataDbSize;
// 	volatile __int64 m_nDeviceDataDbView;

	volatile __int64 m_nCapFrameAndDeviceDbSize;
	volatile __int64 m_nCapFrameAndDeviceDbView;

	volatile __int64 m_nCapDataDbSize;
	volatile __int64 m_nCapDataDbView;

	CString m_strDbFilePath;

	CCapFrameDbFile *m_pCapFrameSmDbFile;
// 	CCapDeviceDataSmDbFile *m_pCapDeviceDataSmDbFile;
// 	CCapFrmDvSmDbFile   *m_pCapFrmDvSmDbFile;
// 	CCapDataSmDbFile   *m_pCapDataSmDbFile;
	CCapDbIndexSmDbFile *m_pCapDbIndexSmDbFile;
	CCapDbIndex0SmDbFile *m_pCapDbIndex0SmDbFile;

	CString m_strCapDvFilePath;
	CString m_strCapIndexFilePath;
	CString m_strCapDataFilePath;

public:
	void CreateSmDbServer();
	void CreateSmDbClient();
	void Write(CFrameMemBufferMngr *pBufferMngr);
	void UpdateIndex0File()	{	m_pCapDbIndex0SmDbFile->UpdateIndex0File();	}

	void ReadConfig();
	BOOL IsSmDbTrue();

	long Query(EPCAPSEARCHCONFIG &oSearchConfig, CEpQueryEpCapDbBufferIndex &oQuery);//, CEpDeviceDatasMngr &oDataMngr);
	void ReadCapBuffer(EPCAPDBBUFFERINDEX *pIndex, CCycleMemBuffer *pBuffer);

	void ValidSmDb();
private:
	void InitDbFiles();
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	void SetWriteFlag(CFrameMemBufferMngr *pBufferMngr);

	EPSMDBFILEPOS m_oSmDbFilePos;
	long m_nCurrWriteIndex;    //上次写数据的位置
	long m_nCurrIndex_MemBufMngr;  //本次写数据时，缓冲区当前的位置
};

