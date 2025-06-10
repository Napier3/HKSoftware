//SttAssistGlobalApi.h
#ifndef _SttAssistGlobalApi_H__
#define _SttAssistGlobalApi_H__

#include "SttAppWndAssistInterface.h"
#include <QWidget>

#define STT_AssistID_MUTEST                       "mutest"
#define STT_AssistID_ADMUTEST                     "admutest"

//总的接口函数
//调用全局对象CSttAssistEngine进行初始化和释放
bool assist_create(const CString &strAssistID);
bool assist_release();

//智能助手
//显示测试助手的菜单
void assist_show_menu();

//设置测试助手图标按钮窗口对象，可以不用，通过assist_find_widget函数传入“Assist”找到助手按钮
void assist_set_entry_wnd(void *pEntryWnd);

//设置主窗口对象，暂时不用，使用全局框架指针对象g_theTestCntrFrame
void assist_set_main_wnd(CSttWndAssistInterface *pSttMainWnd);

//暂时不用
void assist_set_app(CSttAppAssistInterface *pApp);

//执行助手脚本，后续扩展用。在助手做成平台的情况下，此函数才起作用
bool assist_run_script(const CString &strScriptFile);
bool assist_close_script(const CString &strScriptFile);

//事件相关函数
//窗口显示：一个窗口显示在界面，助手针对此窗口进行操作，例如闪屏或者在控件附近显示提示信息
//助手只会在当前显示的窗口中去查找相关的窗口ID。
//QT中，如果控件不是从ui文件中创建的，是动态创建的，需要指定控件的ObjectName，例如：
/*
第一步：设置控件的ObjectName
QSttAssistIecCbSelWidget::QSttAssistIecCbSelWidget(QWidget *parent)
	m_pGridIecCb->setObjectName("AstSttIecCbGrid");
第二步：使用控件
void CSttAssistWzd_MuTest::assist_init()
	g_theAssistWndDynEffExecTool->ShowMsgEx("AstSttIecCbGrid", "在控制块表格中选择关联的控制块", 0);
*/
void assist_wnd_show(const CString &strWndID, CSttWndAssistInterface *pWnd, bool bShow);
void assist_widget_show(const CString &strWndID, QWidget *pWidget, bool bShow);

//界面消息处理：交于助手进行界面消息的处理，暂时不用
void assist_ui_msg(const CString &strUiMsgID, CDataGroup *pDatas);

//数据发生改变，出发助手进行相关的行为，暂时不用，平台化后使用
void assist_data_change(const CString &strWndID, const CString &strDataID, const CString &strValue);

//应用程序事件，交于助手进行处理
bool assist_event(const CString &strEventID, CExBaseObject *pSttParas);

//消息显示相关
//如果定义了strWndID，并且控件存在，在控件周边显示提示信息，如果不存在，则在系统右下角显示提示信息
void assist_show_msg(const CString &strMsg, long nShowTimeLong);
void assist_show_msg_ex(const CString &strWndID, const CString &strMsg, long nShowTimeLong);
void assist_show_result(CDataGroup *pDatas); //保留

#endif//_SttAssistGlobalApi_H__
