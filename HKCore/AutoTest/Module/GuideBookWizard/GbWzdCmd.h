#pragma once

//#include "..\..\Module\BaseClass\ExBaseList.h"
#include "GuideBookWizardDefine.h"
#include "..\GuideBook\GuideBook.h"
#include "..\GbDev\GuideBookDevGlobalDefine.h"
#include "..\GuideBook\ReportMap\WordRptEdit.h"

#define WM_EXEC_GBWZD_CMD    (WM_USER+1330)
#define WM_EXEC_GBWZD_MSG    (WM_USER+1331)
#define WM_EXEC_GBWZD_STATE  (WM_USER+1332)
#define WM_EXEC_GBWZD_FINISH (WM_USER+1333)
#define WM_GBWZD_GBNODE_SEICHANGE (WM_USER+1334)
#define WM_GBWZD_GET_FROM_FRAME   (WM_USER+1335)
#define WM_EXEC_GBWZD_NEXT_ENABLE (WM_USER+1336)
#define WM_EXEC_GBWZD_EXEC_NEXT   (WM_USER+1337)

#define GBWZDCMD_STATE_NORMAL   0
#define GBWZDCMD_STATE_EXEC     1
#define GBWZDCMD_STATE_FINISH   2

#define WZDEXEC_NONE    -1
#define WZDEXEC_STEP    0
#define WZDEXEC_AUTO    1


class CGbWzdCmd : public CExBaseList
{
public:
	CGbWzdCmd();
	virtual ~CGbWzdCmd();

	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);

public:
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey() ;

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();

public:
	virtual BOOL Execute(DWORD dwExecMode);
	virtual BOOL IsCmdFinish()	{	return (m_nCmdExecState == GBWZDCMD_STATE_FINISH);	}
	virtual BOOL IsCmdStateFinish()	{	return (m_nCmdExecState == GBWZDCMD_STATE_FINISH);	}
	virtual void GetStateInfor(CString &strText);
	virtual void GetCmdInfor(CString &strText);


public:
	CGuideBook* GetGuideBook();
	CTreeCtrl* GetGuideBookEditTreeCtrl();
	CFrameWnd* GetMaiFrame();
	CWnd* GetGbWzdWnd();
	CDevice* GetDevice();
	void ShowGbWzdMsg(const CString &strWzdMsg);
	void UpdateWzdState();
	void SetFinishState()	{	m_nCmdExecState = GBWZDCMD_STATE_FINISH;	}
	void PostExecCmdMsg();
	void ResetState()		{	m_nCmdExecState = GBWZDCMD_STATE_NORMAL;	}

protected:
	long m_nCmdExecState;
};


class CGbWzdCmdList : public CGbWzdCmd
{
public:
	CGbWzdCmdList();
	virtual ~CGbWzdCmdList();

public:
	long m_nWzdCmdIndex;
	CExBaseList m_listCmd;

public:
	virtual BOOL Execute(DWORD dwExecMode);
	virtual BOOL IsCmdFinish();
	BOOL ResetCmdList();

protected:
	CGbWzdCmd* GetCurrGbWzdCmd();
	CGbWzdCmd* GetNextGbWzdCmd();
	BOOL ExecCurrGbWzdCmd(DWORD dwExecMode);
	BOOL ExecNextGbWzdCmd(DWORD dwExecMode);
	BOOL IsCurrCmdFinish();
};