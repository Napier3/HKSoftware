//SttAssistWndDynEffExecTool.h
#ifndef _SttAssistWndDynEffExecTool_H__
#define _SttAssistWndDynEffExecTool_H__

#include "SttAssistWndDynEffectBase.h"
#define MAX_COUNT_WndDynEffect  1000

#include <QWidget>
#include <QTimer>

typedef struct _SttAssistWndDynEffect_Obj
{
	int nUse;
	CSttAssistWndDynEffectBase *pWndDynEffect;
}STTASSITWNDEFFECT_OBJ;

class CSttAssistWndDynEffExecTool : public QWidget
{
	Q_OBJECT

public:
	CSttAssistWndDynEffExecTool();
	virtual ~CSttAssistWndDynEffExecTool();

public:
	QTimer m_oTimerDynEffct;

	//动态执行效果对象数组
	//	每次遍历所有的元素进行执行
	//	执行完一次动态处理，清除停止鲜果的对象
	STTASSITWNDEFFECT_OBJ m_arrAstWndDynEff[MAX_COUNT_WndDynEffect];

public:
	void Add(CSttAssistWndDynEffectBase *pWndDynEffect);		//添加动态对象
	void Stop(const CString  &strWndID);		//停止动态对象，从工具中清除对象
	void Flash(const CString  &strWndIDPath, const CString  &strStyle1="", const CString  &strStyle2="", long nTimeLong=-1);  //闪烁子窗口

	void ShowMsg(const CString &strMsg, long nShowTimeLong);
	void ShowMsgEx(const CString &strWndID, const CString &strMsg, long nShowTimeLong);

protected:
	
signals:
	void sig_ShowMsgEx(QString strWndID, QString strMsg, long nShowTimeLong);

private slots:
	void slot_Timer_DynEffect();
	void slot_ShowMsgEx(QString strWndID, QString strMsg, long nShowTimeLong);

};

QWidget* assist_find_widget(const CString  &strWndIDPath);
bool assist_get_widget_msg_pos(const CString &strWndIdPath, QRect &rcWnd);
extern CSttAssistWndDynEffExecTool *g_theAssistWndDynEffExecTool;


#endif//_SttAssistWndDynEffExecTool_H__
