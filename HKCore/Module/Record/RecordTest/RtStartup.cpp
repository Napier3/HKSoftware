// RtStartup.cpp: implementation of the CRtStartup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtStartup.h"
#include "../RtMemBuffer/RtMemBufferMngr.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
long g_nRecordStartup = 0;

const char* CRtStartup::g_pszKeyStartup         = "startup";
const char* CRtStartup::g_pszKeySetsStartup     = "use-sets-startup";
const char* CRtStartup::g_pszKeyTimeStartup     = "use-time-startup";
const char* CRtStartup::g_pszKeyTimeStartupStartTime= "time-startup-time";//定时时间
const char* CRtStartup::g_pszKeyTimeStartupTime = "time-startup";
const char* CRtStartup::g_pszKeyHandStartup     = "use-hand-starup";
const char* CRtStartup::g_pszKeyTimeLookBack    = "time-look-back";
const char* CRtStartup::g_pszKeyRefBufferID     = "ref-buffer-id";
const char* CRtStartup::g_pszKeyTimeStartupStartTimeYear		= "year";//定时时间年
const char* CRtStartup::g_pszKeyTimeStartupStartTimeMonth	= "month";//定时时间月
const char* CRtStartup::g_pszKeyTimeStartupStartTimeDay		= "day";//定时时间日
const char* CRtStartup::g_pszKeyTimeStartupStartTimeHour		="hour";//定时时间时
const char* CRtStartup::g_pszKeyTimeStartupStartTimeMinute	="minute";//定时时间分
const char* CRtStartup::g_pszKeyTimeStartupStartTimeSecond	="second";//定时时间秒
const char* CRtStartup::g_pszKeyTotalRocordTime				= "total-record-time";//总的录波时间

//录波数据的存储模式，长时间连续记录， lijq 2010-8-18
const char* CRtStartup::g_pszKeyRecordDataSaveMode = "record-save-mode";
const char* CRtStartup::g_pszKeyRecordDataSaveModeSingle = "single";//录波数据的存储模式-单次
const char* CRtStartup::g_pszKeyRecordDataSaveModeCycle = "cycle";//录波数据的存储模式-循环

const char* CRtStartup::g_pszKeyAutoSave = "yes";//录波数据的存储模式,自动
const char* CRtStartup::g_pszKeyNotAutoSave = "no";//录波数据的存储模式,不自动
CRtStartup::CRtStartup()
{
	m_strName = "RtStartup";
	m_strID = m_strName;	
	m_pRefBuffer = NULL;
	g_nRecordStartup = FALSE;
	m_nRecordBeginPos = 0;
#ifndef _PSX_QT_LINUX_
	m_timeStartupStartTime = CTime::GetCurrentTime();
#endif
	m_dTotalRecordTimeLen = 100;
	m_dTimeLookBack = 0;
	m_strTotalRecordTimeLen = "";

	m_nRecordDataSaveMode = 0;
}

CRtStartup::~CRtStartup()
{
}

//重载的方法
UINT CRtStartup::GetClassID()
{
	return RTCLASSID_STARTUP;
}
// 
// long CRtStartup::ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode)
// {
// 	xml_GetAttibuteValue(g_pszKeySetsStartup, oNode, m_bUseSetStartup);
// 	xml_GetAttibuteValue(g_pszKeyTimeStartup, oNode, m_bUseTimeStartup);
// 	xml_GetAttibuteValue(g_pszKeyTimeStartupTime, oNode, m_nStartupTime);
// 	xml_GetAttibuteValue(g_pszKeyHandStartup, oNode, m_bHandStartup);
// 	xml_GetAttibuteValue(g_pszKeyTimeLookBack, oNode, m_dTimeLookBack);
// 	xml_GetAttibuteValue(g_pszKeyRefBufferID, oNode, m_strRefBufferID);
// 	xml_GetAttibuteValue(g_pszKeyTotalRocordTime, oNode, m_dTotalRecordTimeLen);
// 
// 	CString strMode;
// 	xml_GetAttibuteValue(g_pszKeyRecordDataSaveMode, oNode, strMode);
// 	InitRecordDataSaveMode(strMode);
// 
// 	return 0;
// }
// 
// BOOL CRtStartup::ReadSetsValueXml(MSXML::IXMLDOMNodePtr &oNode)
// {
// 	xml_GetAttibuteValue(g_pszKeySetsStartup, oNode, m_bUseSetStartup);
// 	xml_GetAttibuteValue(g_pszKeyTimeStartup, oNode, m_bUseTimeStartup);
// 	xml_GetAttibuteValue(g_pszKeyTimeStartupTime, oNode, m_nStartupTime);
// 	xml_GetAttibuteValue(g_pszKeyHandStartup, oNode, m_bHandStartup);
// 	xml_GetAttibuteValue(g_pszKeyTimeLookBack, oNode, m_dTimeLookBack);
// 	xml_GetAttibuteValue(g_pszKeyTotalRocordTime, oNode, m_dTotalRecordTimeLen);
// 
// 	CString strMode;
// 	xml_GetAttibuteValue(g_pszKeyRecordDataSaveMode, oNode, strMode);
// 	InitRecordDataSaveMode(strMode);
// 
// 	SYSTEMTIME tm;
// 	::GetLocalTime(&tm);
// 	long lYear = tm.wYear, lMonth=tm.wMonth, lDay=tm.wDay, lHour=tm.wHour, lMinute=tm.wMinute, lSecond=tm.wSecond;
// 	MSXML::IXMLDOMNodePtr oTimeStartupStartTimeNode = oNode->selectSingleNode(_bstr_t(g_pszKeyTimeStartupStartTime));
// 	
// 	if (oTimeStartupStartTimeNode != NULL)
// 	{
//  		xml_GetAttibuteValue(g_pszKeyTimeStartupStartTimeYear, oTimeStartupStartTimeNode, lYear);
// 		xml_GetAttibuteValue(g_pszKeyTimeStartupStartTimeMonth, oTimeStartupStartTimeNode, lMonth);
//  		xml_GetAttibuteValue(g_pszKeyTimeStartupStartTimeDay, oTimeStartupStartTimeNode, lDay);
// 		xml_GetAttibuteValue(g_pszKeyTimeStartupStartTimeHour, oTimeStartupStartTimeNode, lHour);
// 		xml_GetAttibuteValue(g_pszKeyTimeStartupStartTimeMinute, oTimeStartupStartTimeNode, lMinute);
// 		xml_GetAttibuteValue(g_pszKeyTimeStartupStartTimeSecond, oTimeStartupStartTimeNode, lSecond);
// 	}
// 	m_timeStartupStartTime = CTime(lYear, lMonth, lDay, lHour, lMinute, lSecond);
// 
// 	return TRUE;
// }
// 
// BOOL CRtStartup::WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent)
// {
// 	MSXML::IXMLDOMElementPtr oStartup;
// 	
// 	oStartup = oXMLDoc->createElement(_bstr_t(g_pszKeyStartup));
// 	oStartup->setAttribute(_bstr_t(g_pszKeySetsStartup), m_bUseSetStartup);
// 	oStartup->setAttribute(_bstr_t(g_pszKeyTimeStartup), m_bUseTimeStartup);
// 	oStartup->setAttribute(_bstr_t(g_pszKeyTimeStartupTime), m_nStartupTime);
// 	oStartup->setAttribute(_bstr_t(g_pszKeyHandStartup), m_bHandStartup);
// 	oStartup->setAttribute(_bstr_t(g_pszKeyTimeLookBack), m_dTimeLookBack);
// 	oStartup->setAttribute(_bstr_t(g_pszKeyTotalRocordTime), m_dTotalRecordTimeLen);
// 
// 	CString strMode;
// 	strMode = GetRecordDataSaveMode();
// 	oStartup->setAttribute(_bstr_t(g_pszKeyRecordDataSaveMode), _bstr_t(strMode));
// 
// 	if(m_bUseSetStartup)
// 	{
// 		MSXML::IXMLDOMElementPtr oTimeStartupTime;
// 		oTimeStartupTime = oXMLDoc->createElement(_bstr_t(g_pszKeyTimeStartupStartTime));
// 		oTimeStartupTime->setAttribute(_bstr_t(g_pszKeyTimeStartupStartTimeYear), (long)m_timeStartupStartTime.GetYear());
// 		oTimeStartupTime->setAttribute(_bstr_t(g_pszKeyTimeStartupStartTimeMonth), (long)m_timeStartupStartTime.GetMonth());
// 		oTimeStartupTime->setAttribute(_bstr_t(g_pszKeyTimeStartupStartTimeDay), (long)m_timeStartupStartTime.GetDay());
// 		oTimeStartupTime->setAttribute(_bstr_t(g_pszKeyTimeStartupStartTimeHour), (long)m_timeStartupStartTime.GetHour());
// 		oTimeStartupTime->setAttribute(_bstr_t(g_pszKeyTimeStartupStartTimeMinute), (long)m_timeStartupStartTime.GetMinute());
// 		oTimeStartupTime->setAttribute(_bstr_t(g_pszKeyTimeStartupStartTimeSecond), (long)m_timeStartupStartTime.GetSecond());
// 		oStartup->appendChild(oTimeStartupTime);
// 	}
// 
// 	oParent->appendChild(oStartup);
// 	
// 	return TRUE;
// }

BOOL CRtStartup::IsRecordFinished()
{
	//如果没有启动，则不结束
	if (!g_nRecordStartup)
	{
		return FALSE;
	}

	if (m_pRefBuffer == NULL)
	{
		return FALSE;
	}

	if (IsMemBufferTypeAttr( m_pRefBuffer->m_nMemBufferTypeID))
	{
		return CalRecordFinished_Attr();
	}
	else
	{
		return CalRecordFinished_Record();
	}
	
	return FALSE;
}

BOOL CRtStartup::CalRecordFinished_Attr()
{
	//23毫秒，如果按照最高25次谐波来计算的话，一次FIFO需要存储25个数据
	long nMaxLenOneFifo = 25;
	return CalRecordFinished(nMaxLenOneFifo);
}

BOOL CRtStartup::CalRecordFinished_Record()
{
	//23毫秒，大致估算为3000点,1.5个周波
	long nMaxLenOneFifo = 3000;
	return CalRecordFinished(nMaxLenOneFifo);
}

BOOL CRtStartup::CalRecordFinished(long nMaxLenOneFifo)
{
	long nBufLen = m_pRefBuffer->GetBufferLength();
	long nDataLen = m_pRefBuffer->GetDataLength();
	long nFillBeginPos = m_pRefBuffer->GetDataFillBeginPosition();

	//计算方法，m_nRecordBeginPos起始位置与当前位置的长度，加上nMaxLenOneFifo
	//要小于长个缓冲区的长度
	//即nFillBeginPos+nMaxLenOneFifo要小于m_nRecordBeginPos
	BOOL bFinished = FALSE;
	long nNextPos = nMaxLenOneFifo + nFillBeginPos;

	if (nFillBeginPos < m_nRecordBeginPos)
	{
		if (nNextPos > m_nRecordBeginPos)
		{
			bFinished = TRUE;
		}
	}
	else
	{
		nNextPos -= nBufLen;

		if (nNextPos >= m_nRecordBeginPos)
		{
			bFinished = TRUE;
		}
	}

	return bFinished;
}


void CRtStartup::InitRefBuffer(CRtMemBufferMngr *pRtMemBufferMngr)
{
	m_pRefBuffer = (CMemBufferInterface*)pRtMemBufferMngr->FindBufferByBufferID(m_strRefBufferID.GetString());

	if (m_pRefBuffer == NULL)
	{
		return;
	}	
}

void CRtStartup::InitStartUp(BOOL bStartup, DWORD dwSampleRate)
{
	//如果已经启动，则返回
	if (g_nRecordStartup)
	{
		return;
	}

	//如果没有启动，则返回
	if (!bStartup)
	{
		return;
	}

	//启动
	g_nRecordStartup = TRUE;

	//根据追忆时间计算录波计算起始位置
	if (IsMemBufferTypeAttr(m_pRefBuffer->m_nMemBufferTypeID))
	{
		//是属性数据
		CalRecordBeginPos_Attr();
	}
	else
	{
		CalRecordBeginPos_Record(dwSampleRate);
	}

	//启动录波，发送开始录波的消息
	

#ifdef _USE_PAGES
	g_theRecordApp.m_pUIWndThread->PostThreadMessage(WM_RECORD, 0, 0);
#endif
	
}

//判断有问题，少了录波启动点的位置，所以第一个点的计算不对
void CRtStartup::CalRecordBeginPos(long nPointsLookBack)
{
	UINT nBufTypeID = m_pRefBuffer->m_nMemBufferTypeID;
	long nBufLen = m_pRefBuffer->GetBufferLength();
	long nDataLen = m_pRefBuffer->GetDataLength();
	long nFillBeginPos = m_pRefBuffer->GetDataFillBeginPosition();
	
	//nPointsLookBack有效性检查，此种判断可能有问题
	//追忆时间最大为录波总时间的1/2
	if (nPointsLookBack >= nBufLen /* / 2*/)
	{
		nPointsLookBack = nBufLen;
	}
	
	if (nDataLen == nBufLen)
	{//如果缓冲区填满，追忆时间小于当前的填充位置，则从当前填充位置减去追忆的长度
		if (nFillBeginPos > nPointsLookBack)
		{
			m_nRecordBeginPos = nFillBeginPos - nPointsLookBack;
		}
		else
		{
			m_nRecordBeginPos = nBufLen + nFillBeginPos - nPointsLookBack;
		}
	}
	else
	{
		if (nFillBeginPos > nPointsLookBack)
		{//如果缓冲区没有填满，追忆时间小于现在的录波长度，则从从当前位置减去追忆的长度
			m_nRecordBeginPos = nFillBeginPos - nPointsLookBack;
		}
		else
		{//如果缓冲区没有填满，追忆时间超过现在的录波长度，则从开始位置
			m_nRecordBeginPos = 0;
		}
	}
}

//根据属性数据进行的录波，计算起始位置
void CRtStartup::CalRecordBeginPos_Attr()
{
	//m_nTimeLookBack * 50是初步的估算。
	//严格来说，应该使用m_pAttrTimeBuffer来向前计算开始录波的位置
	//因为m_pAttrTimeBuffer记录了每一个属性数据的点数
	long nPointsLookBack = (long)(m_dTimeLookBack * 50); 

	CalRecordBeginPos(nPointsLookBack);
}

void CRtStartup::CalRecordBeginPos_Record(DWORD dwSampleRate)
{
	long nPointsLookBack = (long)(m_dTimeLookBack * dwSampleRate); 
	
	CalRecordBeginPos(nPointsLookBack);
}

//开始录波是的初始化
void CRtStartup::InitWhenBeginRecord()
{
	g_nRecordStartup = FALSE;
}
// 
// CString CRtStartup::GetRecordDataSaveModeString()
// {
// 	if (IsRecordDataSaveModeCycle())
// 	{
// 		return GetLanguageStringByID(gs_strLanguage_msRecordDataSaveModeCycle);
// 	}
// 	else
// 	{
// 		return GetLanguageStringByID(gs_strLanguage_msRecordDataSaveModeSingle);
// 	}
// }

CString CRtStartup::GetRecordDataSaveMode()
{
	CString strMode;

	if (m_nRecordDataSaveMode == RECORDDATASAVEMODE_SINGLE)
	{
		strMode = g_pszKeyRecordDataSaveModeSingle;
	}
	else if (m_nRecordDataSaveMode = RECORDDATASAVEMODE_CYCLE)
	{
		strMode = g_pszKeyRecordDataSaveModeCycle;
	}
	else if (m_nRecordDataSaveMode == RECORDDATASAVEMODE_AUTO)
	{
		strMode = g_pszKeyAutoSave;
	}
	else if (m_nRecordDataSaveMode == RECORDDATASAVEMODE_HAND)
	{
		strMode = g_pszKeyNotAutoSave;
	}
	else
	{
		m_nRecordDataSaveMode = RECORDDATASAVEMODE_SINGLE;
	}

	return strMode;
}

void CRtStartup::InitRecordDataSaveMode(const CString &strMode)
{
	if (strMode == g_pszKeyRecordDataSaveModeSingle)
	{
		m_nRecordDataSaveMode = RECORDDATASAVEMODE_SINGLE;
	}
	else if (strMode == g_pszKeyRecordDataSaveModeCycle)
	{
		m_nRecordDataSaveMode = RECORDDATASAVEMODE_CYCLE;
	}
	else if (strMode == g_pszKeyAutoSave)
	{
		m_nRecordDataSaveMode = RECORDDATASAVEMODE_AUTO;
	}
	else if (strMode == g_pszKeyNotAutoSave)
	{
		m_nRecordDataSaveMode = RECORDDATASAVEMODE_HAND;
	}
	else
	{
		m_nRecordDataSaveMode = RECORDDATASAVEMODE_SINGLE;
	}

}
// 
// CString CRtStartup::GetStringTotalRecordTimeLen()
// {
// 	long nDay = 0, nHour = 0, nMin = 0, nSec = 0;
// 	long nTotalRecordTimeLen = (long)m_dTotalRecordTimeLen;
// 	m_strTotalRecordTimeLen = "";
// 	nDay = nTotalRecordTimeLen / (3600 * 24);
// 	nSec = nTotalRecordTimeLen % (3600 * 24);
// 	nHour = nSec / 3600;
// 	nSec = nSec % 3600;
// 	nMin = nSec / 60;
// 	nSec = nSec % 60;
// 
// 	if (nDay > 0)
// 	{
// 		m_strTotalRecordTimeLen.Format("%d%s%d%s%d%s%d%s", nDay, GetLanguageStringByID(gs_strLanguage_msDay),
// 											nHour, GetLanguageStringByID(gs_strLanguage_msHour),
// 											nMin, GetLanguageStringByID(gs_strLanguage_msMinute),
// 											nSec, GetLanguageStringByID(gs_strLanguage_msSecond));
// 	}
// 	else
// 	{
// 		if (nHour > 0)
// 		{
// 			m_strTotalRecordTimeLen.Format("%d%s%d%s%d%s", nHour, GetLanguageStringByID(gs_strLanguage_msHour),
// 											nMin, GetLanguageStringByID(gs_strLanguage_msMinute),
// 											nSec, GetLanguageStringByID(gs_strLanguage_msSecond));
// 		}
// 		else
// 		{
// 			if (nMin > 0)
// 			{
// 				m_strTotalRecordTimeLen.Format("%d%s%d%s", nMin, GetLanguageStringByID(gs_strLanguage_msMinute),
// 											nSec, GetLanguageStringByID(gs_strLanguage_msSecond));
// 			}
// 			else
// 			{
// 				if (nSec > 0)
// 				{
// 					m_strTotalRecordTimeLen.Format("%d%s", nSec, GetLanguageStringByID(gs_strLanguage_msSecond));
// 				}
// 				else
// 				{}
// 			}
// 		}
// 	}
// 
// 	return m_strTotalRecordTimeLen;
// }
