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

//����
public:
	//��������
	long m_bUseSetStartup;
	long m_bHandStartup;
	long m_bUseTimeStartup;
	long m_nStartupTime;//��ʱ������ʱ�����,�����ö�ʱ����Ϊ��ʼʱ��
	double m_dTimeLookBack;//׷��ʱ��
	CString m_strRefBufferID;
	CTime m_timeStartupStartTime;//��ʱʱ��
	double m_dTotalRecordTimeLen;
	long  m_nRecordDataSaveMode;		//¼�����ݵĴ洢ģʽ����ʱ��������¼�� lijq 2010-8-18
	CString m_strTotalRecordTimeLen;

	//�ؼ�������
	static const char* g_pszKeyStartup;
	static const char* g_pszKeySetsStartup;
	static const char* g_pszKeyTimeStartup;
	static const char* g_pszKeyTimeStartupTime;
	static const char* g_pszKeyHandStartup;
	static const char* g_pszKeyTimeLookBack;
	static const char* g_pszKeyRefBufferID;
	static const char* g_pszKeyTotalRocordTime;
	static const char* g_pszKeyTimeStartupStartTime;//��ʱʱ��
	static const char* g_pszKeyTimeStartupStartTimeYear;//��ʱʱ����
	static const char* g_pszKeyTimeStartupStartTimeMonth;//��ʱʱ����
	static const char* g_pszKeyTimeStartupStartTimeDay;//��ʱʱ����
	static const char* g_pszKeyTimeStartupStartTimeHour;//��ʱʱ��ʱ
	static const char* g_pszKeyTimeStartupStartTimeMinute;//��ʱʱ���
	static const char* g_pszKeyTimeStartupStartTimeSecond;//��ʱʱ����

	static const char* g_pszKeyRecordDataSaveMode;//¼�����ݵĴ洢ģʽ����ʱ��������¼�� lijq 2010-8-18
	static const char* g_pszKeyRecordDataSaveModeSingle;//¼�����ݵĴ洢ģʽ-���Σ���ʱ��������¼�� lijq 2010-8-18
	static const char* g_pszKeyRecordDataSaveModeCycle;//¼�����ݵĴ洢ģʽ-ѭ������ʱ��������¼�� lijq 2010-8-18
	static const char* g_pszKeyAutoSave;//¼�����ݵĴ洢ģʽ,�Զ�
	static const char* g_pszKeyNotAutoSave;//¼�����ݵĴ洢ģʽ,���Զ�
//����
public:
	//���صķ���
	virtual UINT GetClassID();
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);
// 	virtual const char* GetXmlElementKey()        {     return g_pszKeyStartup;        };

	//��ֵ�ļ����
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
	long m_nRecordBeginPos;    //¼����ʼ��λ�ã���������λ��-׷��ʱ��

	void CalRecordBeginPos_Attr();
	void CalRecordBeginPos_Record(DWORD dwSampleRate);
	void CalRecordBeginPos(long nPointsLookBack);

	BOOL CalRecordFinished_Attr();
	BOOL CalRecordFinished_Record();
	BOOL CalRecordFinished(long nMaxLenOneFifo);
	void InitRecordDataSaveMode(const CString &strMode);
};


#endif // !defined(AFX_RTSTARTUP_H__392981BB_B764_4C4D_8067_BF65F62962B1__INCLUDED_)
