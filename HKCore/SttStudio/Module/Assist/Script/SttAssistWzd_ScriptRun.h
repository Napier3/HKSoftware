//SttAssistWzd_ScriptRun.h
#ifndef _SttAssistWzd_ScriptRun_H__
#define _SttAssistWzd_ScriptRun_H__

#include "../SttAssistInterface.h"


class CSttAssistWzd_ScriptRun : public CSttAssistInterface
{
public:
	CSttAssistWzd_ScriptRun();
	virtual ~CSttAssistWzd_ScriptRun();
	
public:
	virtual void assist_init();
	virtual void assist_wnd_show(const CString &strWndID, CSttAssistWzd_ScriptRun *pWnd, bool bShow);
	virtual void assist_ui_msg(const CString &strUiMsgID, CDataGroup *pDatas);
	virtual void assist_data_change(const CString &strWndID, const CString &strDataID, const CString &strValue);
	virtual bool assist_event(const CString &strEventID, CExBaseObject *pSttParas);
protected:
	bool Event_StartTest(CExBaseObject *pSttParas);
	bool Event_OnTestStarted(CExBaseObject *pSttParas);
	bool Event_OnTestFinished(CExBaseObject *pSttParas);
};


#endif//_SttAssistWzd_ScriptRun_H__
