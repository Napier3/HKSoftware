#pragma once

/*
	�������������Կ�����Ϣ���ܽӿڣ����Թ����У�ͨ���˽ӿ�֪ͨ���������ص���ʾ
*/
#include "GuideBook/GuideBook.h"

//////////////////////////////////////////////////////////////////////////
//CTCtrlMsgRcvInterface
class CTCtrlMsgRcvInterface
{
public:
	CTCtrlMsgRcvInterface();
	virtual ~CTCtrlMsgRcvInterface();

	CWnd *m_pTCtrlMsgRcvWnd;

public:
	virtual long OnException(long nError, const CString &strError, CExBaseObject *pTestControl) = 0;
	virtual long OnConnectSuccess(CExBaseObject *pTestControl) = 0;
	virtual long OnConnectFailed(CExBaseObject *pTestControl) = 0;
	virtual long OnEngineEvent(CExBaseObject *pTestControl, const CString &strEventID) = 0;
	virtual long OnCurrItemStateChanged(CGbItemBase* pItem, BOOL bBringToTop=TRUE) = 0;
	virtual long OnCurrCharItemStateChanged(CGbItemBase* pItem, CExBaseObject *pObj) = 0;
	virtual long OnStopTest(long nType, CExBaseObject *pTestControl) = 0;

	virtual long OnUpdateMeasure(long nData, CExBaseObject *pTestControl) = 0;   //ֱ������
	virtual BOOL IsRunning(long nType, CExBaseObject *pTestControl) = 0;         //�ֶ������Ƿ��������
	virtual long HideAllTestItemUI(long nData, CExBaseObject *pTestControl) = 0; //�ر��ֶ�����
	virtual HWND GetFrameHwnd()=0;
	virtual void ShowItemReport(CExBaseObject *pGbItem, BOOL bCreate=TRUE, BOOL bShow=TRUE) = 0;
	virtual void ShowCharDraw(CExBaseObject *pGbItem, BOOL bShow=TRUE) = 0;
	virtual void EditItemPara(CExBaseObject *pGbItem) = 0;
	virtual void LocateItemReport(CExBaseObject *pGbItem) = 0;
	virtual long OnTestBegin(CExBaseObject *pTestControl);
    virtual void OnTestItemCount(long nCount, CExBaseObject *pTestControl)  {}
	virtual void OnExportRptEvent(CExBaseObject *pTestControl, const CString &strEventID)	{}

	//shaolei 20220622 SV����ѹ��һ���Բ��ԣ���Ҫ��̬������Ŀ����Ҫɾ�������
	virtual void InsertItem(CGbItemBase *pParentItem, CGbItemBase *pSubItem) {}
	virtual void DeleteItem(CGbItemBase *pParentItem, CGbItemBase *pSubItem) {}
	//shaolei 2023-6-14��������Ŀʱ���ݹ��������Ŀ
	virtual void InsertItemEx(CGbItemBase *pParentItem, CGbItemBase *pSubItem){}
// 	virtual void LogString(long nLevel, const CString &strMsg);
// 
// public:
// 	void LogFormatString(long nLevel, const wchar_t *strFormat, ...);
};

typedef CTLinkList<CTCtrlMsgRcvInterface> CTCtrlMsgRcvInterfaceList;

class CTCtrlMsgRcvInterfaceMngr : public CTCtrlMsgRcvInterface, public CTCtrlMsgRcvInterfaceList
{
public:
	CTCtrlMsgRcvInterfaceMngr();
	virtual ~CTCtrlMsgRcvInterfaceMngr();

	void AddTCtrlMsgRcvInterface(CTCtrlMsgRcvInterface *p);

public://CEatsMsgRcvInterface
	virtual long OnException(long nError, const CString &strError, CExBaseObject *pTestControl);
	virtual long OnConnectSuccess(CExBaseObject *pTestControl);
	virtual long OnConnectFailed(CExBaseObject *pTestControl);
	virtual long OnEngineEvent(CExBaseObject *pTestControl, const CString &strEventID);
	virtual long OnCurrItemStateChanged(CGbItemBase* pItem, BOOL bBringToTop=TRUE);
	virtual long OnCurrCharItemStateChanged(CGbItemBase* pItem, CExBaseObject *pObj);
	virtual long OnStopTest(long nType, CExBaseObject *pTestControl);

	virtual long OnUpdateMeasure(long nData, CExBaseObject *pTestControl);   //ֱ������
	virtual BOOL IsRunning(long nType, CExBaseObject *pTestControl);         //�ֶ������Ƿ��������
	virtual long HideAllTestItemUI(long nData, CExBaseObject *pTestControl); //�ر��ֶ�����
	virtual HWND GetFrameHwnd();
	virtual void ShowItemReport(CExBaseObject *pGbItem, BOOL bCreate=TRUE, BOOL bShow=TRUE);
	virtual void ShowCharDraw(CExBaseObject *pGbItem, BOOL bShow=TRUE);
	virtual void EditItemPara(CExBaseObject *pGbItem);
	virtual void LocateItemReport(CExBaseObject *pGbItem);
	virtual long OnTestBegin(CExBaseObject *pTestControl);
	virtual void OnTestItemCount(long nCount, CExBaseObject *pTestControl);
	virtual void OnExportRptEvent(CExBaseObject *pTestControl, const CString &strEventID);

	//shaolei 20220622 SV����ѹ��һ���Բ��ԣ���Ҫ��̬������Ŀ����Ҫɾ�������
	virtual void InsertItem(CGbItemBase *pParentItem, CGbItemBase *pSubItem);
	virtual void DeleteItem(CGbItemBase *pParentItem, CGbItemBase *pSubItem);
	virtual void InsertItemEx(CGbItemBase *pParentItem, CGbItemBase *pSubItem);
};


//////////////////////////////////////////////////////////////////////////
//CMacroCharTestInterface
class CMacroCharTestInterface
{
public:
	CMacroCharTestInterface(){};
	virtual ~CMacroCharTestInterface(){};

public:
	virtual void ShowMacroCharTest(BOOL bShow) = 0;
	//��ʾ������������
	virtual void ShowMacroCharTest(CMacroCharItems *pMacroCharItems) = 0;

	//������������
	virtual void UpdateMacroCharTest(CMacroTest *pMacroTest) = 0;
	virtual CMacroCharItemLineDef* UpdateMacroTest(CMacroTest *pMacroTest, CValues *pSearchReport) = 0;
	virtual CCharElementTestLine* UpdateMacroTest(CMacroTest *pMacroTest, CReport *pReport) = 0;
};

