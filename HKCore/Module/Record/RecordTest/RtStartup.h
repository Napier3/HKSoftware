// RtStartup.h: interface for the CRtStartup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTSTARTUP_H__392981BB_B764_4C4D_8067_BF65F62962B1__INCLUDED_)
#define AFX_RTSTARTUP_H__392981BB_B764_4C4D_8067_BF65F62962B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RecordTestClassDef.h"

#define RECORDDATASAVEMODE_SINGLE   0
#define RECORDDATASAVEMODE_CYCLE    1
#define RECORDDATASAVEMODE_AUTO		2
#define RECORDDATASAVEMODE_HAND     3

extern long g_nRecordStartup;

class CRtStartup : public CExBaseList  
{
public:
	CRtStartup();
	virtual ~CRtStartup();

//属性
public:
	//自身属性
	long m_bUseSetStartup;
	long m_bHandStartup;
	long m_bUseTimeStartup;
	long m_nStartupTime;//定时启动的时间距离,以设置定时启动为开始时间
	double m_dTimeLookBack;//追忆时间
	CString m_strRefBufferID;
	CTime m_timeStartupStartTime;//定时时间
	double m_dTotalRecordTimeLen;
	long  m_nRecordDataSaveMode;		//录波数据的存储模式，长时间连续记录， lijq 2010-8-18
	CString m_strTotalRecordTimeLen;

	//关键字属性
	static const char* g_pszKeyStartup;
	static const char* g_pszKeySetsStartup;
	static const char* g_pszKeyTimeStartup;
	static const char* g_pszKeyTimeStartupTime;
	static const char* g_pszKeyHandStartup;
	static const char* g_pszKeyTimeLookBack;
	static const char* g_pszKeyRefBufferID;
	static const char* g_pszKeyTotalRocordTime;
	static const char* g_pszKeyTimeStartupStartTime;//定时时间
	static const char* g_pszKeyTimeStartupStartTimeYear;//定时时间年
	static const char* g_pszKeyTimeStartupStartTimeMonth;//定时时间月
	static const char* g_pszKeyTimeStartupStartTimeDay;//定时时间日
	static const char* g_pszKeyTimeStartupStartTimeHour;//定时时间时
	static const char* g_pszKeyTimeStartupStartTimeMinute;//定时时间分
	static const char* g_pszKeyTimeStartupStartTimeSecond;//定时时间秒

	static const char* g_pszKeyRecordDataSaveMode;//录波数据的存储模式，长时间连续记录， lijq 2010-8-18
	static const char* g_pszKeyRecordDataSaveModeSingle;//录波数据的存储模式-单次，长时间连续记录， lijq 2010-8-18
	static const char* g_pszKeyRecordDataSaveModeCycle;//录波数据的存储模式-循环，长时间连续记录， lijq 2010-8-18
	static const char* g_pszKeyAutoSave;//录波数据的存储模式,自动
	static const char* g_pszKeyNotAutoSave;//录波数据的存储模式,不自动
//方法
public:
	//重载的方法
	virtual UINT GetClassID();
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);
// 	virtual const char* GetXmlElementKey()        {     return g_pszKeyStartup;        };

	//定值文件相关
// 	BOOL ReadSetsValueXml(MSXML::IXMLDOMNodePtr &oNode);
// 	BOOL WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent);

	BOOL IsRecordFinished();
	void InitRefBuffer(CRtMemBufferMngr *pRtMemBufferMngr);
	void InitStartUp(BOOL bStartup, DWORD dwSampleRate);
	void InitWhenBeginRecord();
	BOOL IsStartup()     {     return g_nRecordStartup;   }
	void ResetStartUp()  {     g_nRecordStartup = FALSE;  }
	CString GetRecordDataSaveMode();
	CString GetRecordDataSaveModeString();
	BOOL IsRecordDataSaveModeSingle()		{	return (m_nRecordDataSaveMode == RECORDDATASAVEMODE_SINGLE);		}	
	BOOL IsRecordDataSaveModeCycle()		{	return (m_nRecordDataSaveMode == RECORDDATASAVEMODE_CYCLE);		}	
	
	CString GetStringTotalRecordTimeLen();
private:
	CMemBufferInterface *m_pRefBuffer;
	long m_nRecordBeginPos;    //录波开始的位置，等于启动位置-追忆时间

	void CalRecordBeginPos_Attr();
	void CalRecordBeginPos_Record(DWORD dwSampleRate);
	void CalRecordBeginPos(long nPointsLookBack);

	BOOL CalRecordFinished_Attr();
	BOOL CalRecordFinished_Record();
	BOOL CalRecordFinished(long nMaxLenOneFifo);
	void InitRecordDataSaveMode(const CString &strMode);
};


#endif // !defined(AFX_RTSTARTUP_H__392981BB_B764_4C4D_8067_BF65F62962B1__INCLUDED_)
