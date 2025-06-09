// MR1200BaseApp.h: interface for the CMR1200BaseApp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MR1200BaseApp_H__C8A73265_F86A_47C5_970E_13CB1131337F__INCLUDED_)
#define AFX_MR1200BaseApp_H__C8A73265_F86A_47C5_970E_13CB1131337F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RecordGlobalDefine.h"
#include "RecordTest/RecordTest.h"
#include "Comtrade/ComtradeMngr.h"
#include "../DataMngr/DvmDataset.h"

class CMR1200BaseApp : public CExBaseList
{
public:
	CMR1200BaseApp();
	virtual ~CMR1200BaseApp();

	double m_dRecordDataReadBeginTime;

private:
	long m_nRecordDataMode;
	BOOL m_bADStart;
	BOOL m_bCanJudgeStartup;
	BOOL m_bCanFireSysMessage;
	BOOL m_bRecordCmpDrawAllMatchCh;

	enum eRunHoldState{RHS_HOLD=0, RHS_RUN=1}m_eRecordHoldState;

public:
	void SetRecordDataModeOscillograph()		{		m_nRecordDataMode = MRONLINE_RECORDEX_MODE_OSCILLOGRAPH;	}
	void SetRecordDataModeComtrade()			{		m_nRecordDataMode = MRONLINE_RECORDEX_MODE_COMTRADE;		}
	void SetRecordDataModeOnlineRecord()		{		m_nRecordDataMode = MRONLINE_RECORDEX_MODE_ONLINERECORD;	}
	BOOL IsRecordDataModeOscillograph()			{	return (m_nRecordDataMode == MRONLINE_RECORDEX_MODE_OSCILLOGRAPH);	}
	BOOL IsRecordDataModeComtrade()				{	return (m_nRecordDataMode == MRONLINE_RECORDEX_MODE_COMTRADE);		}
	BOOL IsRecordDataModeOnlineRecord()			{	return (m_nRecordDataMode == MRONLINE_RECORDEX_MODE_ONLINERECORD);	}

	BOOL IsAdStart()	{	return m_bADStart;	}

	void SetInRecordHoldState(BOOL bInRecordHoldState=TRUE)
	{
		if (bInRecordHoldState)
		{
			m_eRecordHoldState = RHS_HOLD;
		}
		else
		{
			m_eRecordHoldState = RHS_RUN;
		}
	}

	BOOL IsInRecordHoldState()
	{
		return (m_eRecordHoldState == RHS_HOLD);
	}
	BOOL IsInRecordRunState()
	{
		return (m_eRecordHoldState == RHS_RUN);
	}
	
	BOOL CanJudgeStartup() {   return m_bCanJudgeStartup;    }
	void SetCanJudgeStartup(BOOL b = TRUE) {   m_bCanJudgeStartup = b;    }
	BOOL IsRecordStartup();
	
	
	//设置从录波缓冲区开始读的位置，从此位置开始写入共享文件
	void SetOnlineExWriteBeginPos(long nWriteRecordBeginPos);

	void SetCanFireSysMessage(BOOL bCanFireSysMessage=TRUE)	{	m_bCanFireSysMessage = bCanFireSysMessage;		}
	BOOL CanFireSysMessage()								{	return m_bCanFireSysMessage;					}

public:
	CString m_strComtradeFilePath;
	void ReadComtradeFile();
	void ReadComtradeFile(const CString& strPath);
	CRecordTest* ReadComtradeFile(CRcdComtradeFile *pComtradeFile);

	long  UnloadRecordTest();
	void AttachOnlineRecordExBuffer(CRcdComtradeFile *pComtradeFile, CRecordTest *pRecordTest);

	CRecordTest* InitRecordTestByComtradeEx(CRcdComtradeFile *pComtradeFile);
	CRtSingleVariable* InitAnalogVariableByComtrade(CRecordTest *pRecordTest, CComtradeAnalogData* pAnalog,CRtMemBufferChannel* pChannel,long& nIndex);
	CRtBinaryVariable* InitBinaryVariableByComtrade(CComtradeBinaryData* pBinary,CRtMemBufferChannel* pChannel,long& nIndex);
	//CRtDataAttribute* CreateAttrByID(const CString& strID,const CString& strVarName);

public:
	void InitDrawControlByRecordTest(CRecordTest* pRecordTest);

	void InitRtFilterData();

protected:
	CExBaseList *m_pRecordCompare;

	void WaveAnalyseAll();

public:
#ifndef _no_use_RecordCompare_
	void RecordCompare();
	void RecordAnalyse();
	BOOL IsRcdCmpSucc()	;

	CRecordTest* InitRecordTestByCompare(CExBaseList *pRecordCompare);
	void FreeRecordCompare();
	CExBaseList* GetRecordCompare()	{	return m_pRecordCompare;	}
	CExBaseObject* FindCmpVariable1(CExBaseObject *pVar2);
	CDvmDataset* GetRcdCmpResult();
#endif
	long GetTotalPoints(CRecordTest *pRecordTest);

// public:
// 	CString m_strRcdCmpStdFile;
// 	CString m_strRcdCmpTestFile;
// 
// 	BOOL RcdCmp(const CString &strStdFile, const CString &strTestFie);
// 	void RcdCmpClear();

//lijq 2020-4-15  创建CRecordTest
public:
	CRecordTest* CreateNewCrecordTest();
};

extern CMR1200BaseApp g_theRecordApp;
extern CRecordTest* g_pCurrRecordTest;
extern 	BOOL g_bInWriteBmpFileState;


// extern long USE_RT_FILTER_BUFFER_LEN;//   81
// extern long RT_FILTER_DATA_LEN_PREV;// 40
// extern long RT_FILTER_DATA_LEN_NEXT;// 40
// extern long RTATTRIBUTECAL_MIN_BUFFER_LEN;
// extern long Analyse_Cal_Length;// 2000


#endif // !defined(AFX_MR1200BaseApp_H__C8A73265_F86A_47C5_970E_13CB1131337F__INCLUDED_)
