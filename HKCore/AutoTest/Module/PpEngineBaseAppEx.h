#pragma once

/*
	������������Լ������ù������App����
	�Զ����������򡢵����������Ӧ�ó���App�඼�Ӵ�������
*/

#include "PpEngineCreateMngr.h"

//////////////////////////////////////////////////////////////////////////
//CPpEngineBaseAppEx
class CPpEngineBaseAppEx : public CWinAppEx
{
public:
	CPpEngineBaseAppEx();
	virtual ~CPpEngineBaseAppEx();

protected:
	//֧�ֶ��Լ���ܣ�����ͳ��Լ��61850MMS��Լ����  2016-8-15
	CPpEngineCreateMngr m_oPpEngineCreateMngr;

	CWnd *m_pXTestMsgWnd;

protected:
	//��ʼ������
	long InitTCtrlBaseApp();
	long ExitPpEngineBaseAppEx();

public:
	//PpEngine
	PpEngine::IPpEnginePtr GetPpEngine(const CString &strProgID);
	BOOL HasPpEngine();

	//MacroTest
	virtual void CreatePpEngine();
	virtual void CreateAllEngine();
	virtual void InitPpEngineShowSpyWnd();
	virtual void StopProtocolParseForReadSoe(BOOL bStop);

public:
	virtual void ReleasePpEngine(const CString &strProgID);
	virtual void ReleasePpEngine();
};

extern CPpEngineBaseAppEx *g_thePpEngineApp;
