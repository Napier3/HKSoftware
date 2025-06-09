#include "stdafx.h"
#include "SttAssistWndFlash.h"

long CSttAssistWndFlash::g_nCurrStyle = 0;   //��������ͬ��ʽ����˸����ʽ��һ�£����ÿ������Բ��þ�̬

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

//��̬Ч��ִ�к���
void CSttAssistWndFlash::ast_Exec(long nTimeGap)
{
	CSttAssistWndDynEffectBase::ast_Exec(nTimeGap);

	if (m_bIsStoped)
	{
		if (m_pCurrWnd->inherits("QToolButton"))//����Ǽ̳���QToolButton,����Ϊ�ÿؼ���ͨ����ʽ
		{
			m_pCurrWnd->setStyleSheet(g_strQToolButtonStyleSheet);
		} 
		else
		{
			m_pCurrWnd->setStyleSheet(m_strStyle1);//��������Ϊ��ʽ1,����ɫ
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

//ֹͣ��̬Ч��ִ��
void CSttAssistWndFlash::ast_Stop()
{
	m_bIsStoped = true;
}

