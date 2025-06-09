//SttAssistGlobalApi.h
#ifndef _SttAssistEngine_H__
#define _SttAssistEngine_H__

#include "SttAssistInterface.h"
#include "SttAppWndAssistInterface.h"
#include "../UI/SttTestCntrFrameBase.h"

//不考虑QT和MFC兼容，后面如果需要再改进
#define STT_ASSISTWIGETSHOW_OBJ_COUNT   100

class CSttAssistEngine : public CExBaseList
{
private:
	CSttAssistEngine();
	virtual ~CSttAssistEngine();
	
	static CSttAssistEngine* g_pSttAssistEngine;
	static long g_nSttAssistEngine;

public:
	static void Create();
	static void Release();

public:
	//智能助手
	void assist_show_menu();
	void assist_set_entry_wnd(void *pEntryWnd);
	void assist_set_main_wnd(CSttWndAssistInterface *pSttMainWnd);
	void assist_set_app(CSttAppAssistInterface *pApp);
	bool assist_run_script(const CString &strScriptFile);
	bool assist_close_script(const CString &strScriptFile);

	//事件相关函数
	void assist_wnd_show(const CString &strWndID, CSttWndAssistInterface *pWnd, bool bShow);
	void assist_widget_show(const CString &strWndID, QWidget *pWidget, bool bShow);
	void assist_ui_msg(const CString &strUiMsgID, CDataGroup *pDatas);
	void assist_data_change(const CString &strWndID, const CString &strDataID, const CString &strValue);
	bool assist_event(const CString &strEventID, CExBaseObject *pSttParas);

	//消息显示相关
	void assist_show_msg(const CString &strMsg, long nShowTimeLong);
	void assist_show_msg_ex(const CString &strWndID, const CString &strMsg, long nShowTimeLong);
	void assist_show_result(CDataGroup *pDatas); //保留

private:
	CSttAssistInterface *m_pCurrAssist;
	QWidget *m_pEntryWnd;

protected:
	void show_start_tip();

protected:
	typedef struct _SttAssistWidgetShow_Obj
	{
		int nUse;
		char pszWndID[64];
		QWidget *pWidget;
	}STT_ASSISTWIGETSHOW_OBJ;

	STT_ASSISTWIGETSHOW_OBJ m_arrWidgetShow[STT_ASSISTWIGETSHOW_OBJ_COUNT];
	
	void WidgetAdd(const CString &strWndID, QWidget *pWidget);
	void WidgetRemove(const CString &strWndID);
	void WidgetRemove(QWidget *pWidget);
	void WidgetRemove();

public:
	QWidget* assist_find_widget(const CString  &strWndIDPath);

};

extern CSttAssistEngine *g_theAssistEngine;

#endif//_SttAssistEngine_H__
