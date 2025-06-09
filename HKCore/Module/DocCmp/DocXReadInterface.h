//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DocXReadInterface.h  CDocXReadInterface

#pragma once

#include "DocCmp.h"
#include "../../Module/System/TickCount32.h"
#include "../../Module/BaseClass/ThreadProgressInterface.h"

#define XDOC_PROG_ID_WORD   _T("WORD")
#define XDOC_PROG_ID_WPS    _T("WPS")
#define XDOC_PROG_ID_XML    _T("XML")
#define XDOC_PROG_ID_JSON   _T("JSON")

class CDocXReadInterface
{
public:
	CDocXReadInterface();
	virtual ~CDocXReadInterface();

	void SetProgressInterface(CThreadProgressInterface *p)	{	m_pProgress = p;	}
//˽�г�Ա����
protected:
	CTickCount32 m_oTickCount;
	CThreadProgressInterface *m_pProgress;

	void TickEnter()	{	m_oTickCount.Enter();	}
	void MessageTickCount(const CString &strTitle);

//˽�г�Ա�������ʷ���
public:
	virtual BOOL GetWordApp(BOOL bShow=FALSE) = 0;
	virtual void QuitApp() = 0;
	virtual void ShowApp(long nShow) = 0;

	virtual BOOL ReadDocFile(CDocCmp *pDocCmp, const CString &strFile1, const CString strFile2) = 0;
	virtual BOOL DocToXml(const CString &strFile) = 0;
};

