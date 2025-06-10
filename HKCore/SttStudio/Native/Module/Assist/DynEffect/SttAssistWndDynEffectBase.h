//SttAssistWndDynEffectBase.h
#ifndef _SttAssistWndDynEffectBase_H__
#define _SttAssistWndDynEffectBase_H__

#include "../SttAssistInterface.h"
#include "../SttAppWndAssistInterface.h"
#include "../../UI/SttStyleSheetGlobalDefine.h"
#include <QWidget>

#define ASSIST_MSG_WND_GAP   20

//助手动态效果执行工具基类
//所有动态效果执行对象从此类派生
class CSttAssistWndDynEffectBase : public CExBaseList
{
public:
	CSttAssistWndDynEffectBase();
	virtual ~CSttAssistWndDynEffectBase();
	
public:
	QWidget *m_pCurrWnd;
	CString m_strWndID;
	bool m_bIsStoped;
	long m_nTimeLong;  //持续时间, <=0表示不限时长  单位为毫秒 
	long m_nTimeExec;   //已用时长  单位为毫秒 

  //动态效果执行函数
	virtual void ast_Exec(long nTimeGap);
	
  //停止动态效果执行
	virtual void ast_Stop();
	
	//定时器函数
	virtual void ast_on_timer(const CString &strTimerID);
	virtual void ast_on_timer(long nTimerID);

};

#endif//_SttAssistWndDynEffectBase_H__
