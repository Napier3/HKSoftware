#include "stdafx.h"
#include "SttAssistWndFlash.h"

long CSttAssistWndFlash::g_nCurrStyle = 0;   //避免多个相同样式的闪烁，样式不一致，不好看，所以采用静态

CSttAssistWndFlash::CSttAssistWndFlash()
{
	m_pCurrWnd = NULL;
	m_bIsStoped = false;
	m_nFlashTimeLong = 0;
}


CSttAssistWndFlash::~CSttAssistWndFlash()
{
	
}

void CSttAssistWndFlash::AfterExec()
{
	if (g_nCurrStyle == 0)
	{
		g_nCurrStyle = 1;
	}
	else
	{
		g_nCurrStyle = 0;
	}
}

//动态效果执行函数
void CSttAssistWndFlash::ast_Exec(long nTimeGap)
{
	CSttAssistWndDynEffectBase::ast_Exec(nTimeGap);

	if (m_bIsStoped)
	{
		if (m_pCurrWnd->inherits("QToolButton"))//如果是继承自QToolButton,设置为该控件的通用样式
		{
			m_pCurrWnd->setStyleSheet(g_strQToolButtonStyleSheet);
		} 
		else
		{
			m_pCurrWnd->setStyleSheet(m_strStyle1);//否则设置为样式1,即灰色
		}
		
		return;
	}

	if (g_nCurrStyle == 0)
	{
		m_pCurrWnd->setStyleSheet(m_strStyle1);
	}
	else
	{
		m_pCurrWnd->setStyleSheet(m_strStyle2);
	}
}

//停止动态效果执行
void CSttAssistWndFlash::ast_Stop()
{
	m_bIsStoped = true;
}

