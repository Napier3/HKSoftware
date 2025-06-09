/*
	用于解析pqdif文件
	yp.w wangyp@youdiantech.com
*/

#ifndef _PQDIF_TOOL_H_
#define _PQDIF_TOOL_H_

#include <stdio.h>
#include "pqdexamp.h"
#include <float.h>

#include "..\DataMngr\DvmDataset.h"
#include "..\MemBuffer\EquationBuffer.h"

class stPqdifTotalData
{
public:
	stPqdifTotalData(){};
	virtual ~stPqdifTotalData(){}

public:
	container_example container; // 用于存储pqdif文件中container的信息
	datasource_example datasource; // 用于存储pqdif文件中datasource的信息
	monitorsettings_example monitorsetting; // 用于存储pqdif文件中monitorsetting的信息
	observation_example observation; // 用于存储pqdif文件中observation的信息
}; // 用于存储所有数据的结构体定义

class STRUCT_QueryNodeData : public CExBaseObject
{
public:
	STRUCT_QueryNodeData()
	{
		freqVal = DBL_MIN;
		maxVal  = DBL_MIN;
		minVal  = DBL_MIN;
		avgVal  = DBL_MIN;
		cp95Val = DBL_MIN;
		idQuantityMeasured = -1;
	};
	~STRUCT_QueryNodeData(){};

public:
	UINT4 stdDataSrcIndex;
	CString channelName;
	UINT4       idQuantityMeasured; // 

public:
	double freqVal; 
	double maxVal; 
	double minVal; 
	double avgVal; 
	double cp95Val; 
} ;

class STRUCT_QueryTotalData : public CBaseList
{
public:
	STRUCT_QueryTotalData()
	{
	};
	~STRUCT_QueryTotalData(){}

public:
	time_t queryTime; 

public:
	STRUCT_QueryNodeData* AddNode()
	{
		STRUCT_QueryNodeData *p = new STRUCT_QueryNodeData();
		AddTail(p);
		return p;
	}

	STRUCT_QueryNodeData* GetNode(long nIndex)
	{
		return (STRUCT_QueryNodeData*)GetAtIndex(nIndex);
	}

	void AddArray(long nCount)
	{
		long nIndex = 0;

		for (nIndex=0; nIndex<nCount; nIndex++)
		{
			AddTail(new STRUCT_QueryNodeData());
		}
	}
} ;

extern stPqdifTotalData g_stdFormat; // 用于存储标准格式xml
extern stPqdifTotalData g_pqTotalData; // 用于存储所有的数据
extern STRUCT_QueryTotalData g_queryTotalData; // 用于存储查询的数据

enum tagRecordState
{
	rcdStateConnectFailed = 0,
	rcdStateConnectSuccess = 1,
	rcdStateRecordFailed = 2,
	rcdStateRecordSuccess = 3
};

class CPqdifTool
{
public:
	CPqdifTool();
	~CPqdifTool();

	CDvmDataset   m_oPqdifSelectConfig;
	CEquationBuffer m_oPqdifSelectPara;
	CDvmDataset m_oPqdifError;

	void OpenPqdifSelectConfig();


public:
	int setStdXml( const CString &xml );
	int openPqdifFile( const char *file );
	void queryData( time_t time );
	void InitQueryData();

	void GetQueryDatas(CDvmDataset *pDataset, float fCT, float fPT);
	void AddPqdifErrorString(const CString &strError);
	void AddPqdifErrorString(const char *strError);

	CString GetPqdifErrorString();
protected:
	CDvmData* FindPqdifSelectConfig(const CString &strName);
	CDvmData* AddPqdifError();
};

class CPqdifConfig : CBaseObject
{
public:
	CPqdifConfig();
	virtual ~CPqdifConfig();

	BOOL IsFtpServer()	{	return (m_nFtpType == 0);	}
	BOOL IsFtpClient()	{	return (m_nFtpType == 1);	}
	CString GetFtpServerRootPath();

public:
	CString m_strLocalFtpServerIP;
	CString m_strUser;
	CString m_strPSW;
	CString m_strServerPath;

	CString m_strRemoteFtpServerIP;
	long    m_nFtpType;   //0 = Server;  1=Client
	
	CString m_strStdFile;
	CString m_strFtpServerRootPath;
	long    m_nPqdifTimeLocal;
	float    m_fPT, m_fCT;

public:
	//缓冲区串行化
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	
	BOOL OpenConfigFile();
	void SaveConfigFile();
	void Init();
	BOOL IsPqdifTimeLocal()	{	return m_nPqdifTimeLocal == 1;	}
	BOOL IsPqdifTimeUTC()	{	return m_nPqdifTimeLocal == 0;	}

protected:
	CString GetConfigFile();
};


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//版本管理
#define PQDIFTOOL_VERSION_1_0         0X00010000

static const DWORD g_dwPqdifToolCurrVersion = PQDIFTOOL_VERSION_1_0;


inline void Gb_InitPqdifFileVersion(char *pszPrefix, DWORD &dwVersion)
{
	pszPrefix[0]='E';
	pszPrefix[1]='P';
	pszPrefix[2]='O';
	pszPrefix[3]='T';
	pszPrefix[4]='O';
	pszPrefix[5]='.';
	pszPrefix[6]='P';
	pszPrefix[7]='Q';
	pszPrefix[8]='D';
	pszPrefix[9]='I';
	pszPrefix[10]='F';
	pszPrefix[11]=0;
	dwVersion = g_dwPqdifToolCurrVersion;
}


#endif  // _PQDIF_TOOL_H_

