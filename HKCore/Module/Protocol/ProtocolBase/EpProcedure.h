// EpProcedure.h: interface for the CEpProcedure class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EPPROCEDURE_H__)
#define _EPPROCEDURE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EpFrameBase.h"
#include "EpNodes.h"
#include "..\EpFrameSendMngr.h"
#include "..\CmmChannel\EpDeviceCmmChannel.h"

class CEpProcedure : public CExBaseObject  
{
public:
	CEpProcedure();
	virtual ~CEpProcedure();

	void InitDeviceCmmChannel(CEpDeviceCmmChannel *pDeviceChannel);

public:
	CString m_strChannelID;
	CString m_strChCmmMode;

private:
	CEpNode *m_pCurrNode;
	CEpFrameSendMngr *m_pPkgSendMngr;  //报文帧发送管理对象
	CExBaseList *m_pListReceiveFrame;             //解析出来的帧对象
	CWinThread *m_pEngineThread;
	BOOL m_bProcedureExit;

public:
	//基本方法
	virtual void Init()	{}
	virtual UINT GetClassID()		{ return EPCLASSID_PROCEDURE; }

	//编辑
	virtual long IsEqual(CExBaseObject* pObj) {	return 0;}
	virtual long Copy(CExBaseObject* pDesObj) {	return 0;}
	virtual CExBaseObject* Clone()			  {	return NULL;  }

	//执行
	virtual void RunInitScript() {}
	virtual void RunEndScript() {}
	virtual DWORD Run() = 0;
	virtual DWORD Process(CEpFrameBase *pFrame) = 0;
	virtual BOOL IsProcedureExit()	{	return TRUE;	}
	virtual void CopyDataInterfaceToFrame();
	CEpNode* GetCurrNode()	{	return m_pCurrNode;		}

private:
	void RunNode();
	void ProcessNode();
	CEpNode* ProcessNodeProcess();
	CEpNode* ProcessNodeJumps();
	CEpNode* ProcessNodeTimers();

	void RunWFrame(CEpFrameBase *pFrame);
	void SetCurrNode(CEpNode *pNode)
	{
		if (m_pCurrNode != NULL)
		{
			m_pCurrNode->SetFrameSend(NULL);
		}

		m_pCurrNode = pNode;
	}

};

#endif // !defined(_EPPROCEDURE_H__)
