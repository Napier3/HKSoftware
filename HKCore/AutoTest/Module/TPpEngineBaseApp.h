#pragma once

/*
	�����������Զ����ԵĹ������
	�Զ����������򡢵����������Ӧ�ó���App�඼�Ӵ�������
	ʵ�֣���������Ĺ������Թ���
*/

#include "TestMsgWnd.h"
#include "..\..\Module\Interface\ProtocolEngineInterface.h"

class CTPpEngineBaseApp : public CWinAppEx
{
public:
	CTPpEngineBaseApp();
	virtual ~CTPpEngineBaseApp();


protected:
	CString m_strPpEngineProgID;
	PpEngine::IPpEnginePtr m_pPpEngine;

protected:
	//��ʼ������
	long InitPpEngineBaseApp();
	long ExitTPpEngineBaseApp();

public:
	PpEngine::IPpEnginePtr GetPpEngine(const CString &strProgID);
	void ReleasePpEngine();
	virtual void CreatePpEngine();


};
