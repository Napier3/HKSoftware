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
const char* CRtStartup::g_pszKeyTimeStartupStartTime= "time-startup-time";//��ʱʱ��
const char* CRtStartup::g_pszKeyTimeStartupTime = "time-startup";
const char* CRtStartup::g_pszKeyHandStartup     = "use-hand-starup";
const char* CRtStartup::g_pszKeyTimeLookBack    = "time-look-back";
const char* CRtStartup::g_pszKeyRefBufferID     = "ref-buffer-id";
const char* CRtStartup::g_pszKeyTimeStartupStartTimeYear		= "year";//��ʱʱ����
const char* CRtStartup::g_pszKeyTimeStartupStartTimeMonth	= "month";//��ʱʱ����
const char* CRtStartup::g_pszKeyTimeStartupStartTimeDay		= "day";//��ʱʱ����
const char* CRtStartup::g_pszKeyTimeStartupStartTimeHour		="hour";//��ʱʱ��ʱ
const char* CRtStartup::g_pszKeyTimeStartupStartTimeMinute	="minute";//��ʱʱ���
const char* CRtStartup::g_pszKeyTimeStartupStartTimeSecond	="second";//��ʱʱ����
const char* CRtStartup::g_pszKeyTotalRocordTime				= "total-record-time";//�ܵ�¼��ʱ��

//¼�����ݵĴ洢ģʽ����ʱ��������¼�� lijq 2010-8-18
const char* CRtStartup::g_pszKeyRecordDataSaveMode = "record-save-mode";
const char* CRtStartup::g_pszKeyRecordDataSaveModeSingle = "single";//¼�����ݵĴ洢ģʽ-����
const char* CRtStartup::g_pszKeyRecordDataSaveModeCycle = "cycle";//¼�����ݵĴ洢ģʽ-ѭ��

const char* CRtStartup::g_pszKeyAutoSave = "yes";//¼�����ݵĴ洢ģʽ,�Զ�
const char* CRtStartup::g_pszKeyNotAutoSave = "no";//¼�����ݵĴ洢ģʽ,���Զ�
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

//���صķ���
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
	//���û���������򲻽���
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
	//23���룬����������25��г��������Ļ���һ��FIFO��Ҫ�洢25������
	long nMaxLenOneFifo = 25;
	return CalRecordFinished(nMaxLenOneFifo);
}

BOOL CRtStartup::CalRecordFinished_Record()
{
	//23���룬���¹���Ϊ3000��,1.5���ܲ�
	long nMaxLenOneFifo = 3000;
	return CalRecordFinished(nMaxLenOneFifo);
}

BOOL CRtStartup::CalRecordFinished(long nMaxLenOneFifo)
{
	long nBufLen = m_pRefBuffer->GetBufferLength();
	long nDataLen = m_pRefBuffer->GetDataLength();
	long nFillBeginPos = m_pRefBuffer->GetDataFillBeginPosition();

	//���㷽����m_nRecordBeginPos��ʼλ���뵱ǰλ�õĳ��ȣ�����nMaxLenOneFifo
	//ҪС�ڳ����������ĳ���
	//��nFillBeginPos+nMaxLenOneFifoҪС��m_nRecordBeginPos
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
	//����Ѿ��������򷵻�
	if (g_nRecordStartup)
	{
		return;
	}

	//���û���������򷵻�
	if (!bStartup)
	{
		return;
	}

	//����
	g_nRecordStartup = TRUE;

	//����׷��ʱ�����¼��������ʼλ��
	if (IsMemBufferTypeAttr(m_pRefBuffer->m_nMemBufferTypeID))
	{
		//����������
		CalRecordBeginPos_Attr();
	}
	else
	{
		CalRecordBeginPos_Record(dwSampleRate);
	}

	//����¼�������Ϳ�ʼ¼������Ϣ
	

#ifdef _USE_PAGES
	g_theRecordApp.m_pUIWndThread->PostThreadMessage(WM_RECORD, 0, 0);
#endif
	
}

//�ж������⣬����¼���������λ�ã����Ե�һ����ļ��㲻��
void CRtStartup::CalRecordBeginPos(long nPointsLookBack)
{
	UINT nBufTypeID = m_pRefBuffer->m_nMemBufferTypeID;
	long nBufLen = m_pRefBuffer->GetBufferLength();
	long nDataLen = m_pRefBuffer->GetDataLength();
	long nFillBeginPos = m_pRefBuffer->GetDataFillBeginPosition();
	
	//nPointsLookBack��Ч�Լ�飬�����жϿ���������
	//׷��ʱ�����Ϊ¼����ʱ���1/2
	if (nPointsLookBack >= nBufLen /* / 2*/)
	{
		nPointsLookBack = nBufLen;
	}
	
	if (nDataLen == nBufLen)
	{//���������������׷��ʱ��С�ڵ�ǰ�����λ�ã���ӵ�ǰ���λ�ü�ȥ׷��ĳ���
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
		{//���������û��������׷��ʱ��С�����ڵ�¼�����ȣ���Ӵӵ�ǰλ�ü�ȥ׷��ĳ���
			m_nRecordBeginPos = nFillBeginPos - nPointsLookBack;
		}
		else
		{//���������û��������׷��ʱ�䳬�����ڵ�¼�����ȣ���ӿ�ʼλ��
			m_nRecordBeginPos = 0;
		}
	}
}

//�����������ݽ��е�¼����������ʼλ��
void CRtStartup::CalRecordBeginPos_Attr()
{
	//m_nTimeLookBack * 50�ǳ����Ĺ��㡣
	//�ϸ���˵��Ӧ��ʹ��m_pAttrTimeBuffer����ǰ���㿪ʼ¼����λ��
	//��Ϊm_pAttrTimeBuffer��¼��ÿһ���������ݵĵ���
	long nPointsLookBack = (long)(m_dTimeLookBack * 50); 

	CalRecordBeginPos(nPointsLookBack);
}

void CRtStartup::CalRecordBeginPos_Record(DWORD dwSampleRate)
{
	long nPointsLookBack = (long)(m_dTimeLookBack * dwSampleRate); 
	
	CalRecordBeginPos(nPointsLookBack);
}

//��ʼ¼���ǵĳ�ʼ��
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
