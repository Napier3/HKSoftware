//SttAssistGlobalApi.h
#ifndef _SttAssistWndFlash_H__
#define _SttAssistWndFlash_H__

#include "SttAssistWndDynEffectBase.h"


//窗口动态闪烁，两个样式切换，结束时回复之前的样式

class CSttAssistWndFlash : public CSttAssistWndDynEffectBase
{
public:
	CSttAssistWndFlash();
	virtual ~CSttAssistWndFlash();

	static long g_nCurrStyle;   //避免多个相同样式的闪烁，样式不一致，不好看，所以采用静态

	static void AfterExec();
public:
	CString m_strStyleBack;
	CString m_strStyle1;
	CString m_strStyle2;
	long m_nFlashTimeLong;  //  单位为毫秒  闪烁的时间间隔	

public:
  //动态效果执行函数
	virtual void ast_Exec(long nTimeGap);
	
  //停止动态效果执行
	virtual void ast_Stop();
	
	//定时器函数  暂时补重载实现
	//virtual void ast_on_timer(const CString &strTimerID);
	//virtual void ast_on_timer(long nTimerID);

protected:
	
};




#endif//_SttAssistGlobalApi_H__
