//SttAssistGlobalApi.h
#ifndef _SttAssistWndFlash_H__
#define _SttAssistWndFlash_H__

#include "SttAssistWndDynEffectBase.h"


//���ڶ�̬��˸��������ʽ�л�������ʱ�ظ�֮ǰ����ʽ

class CSttAssistWndFlash : public CSttAssistWndDynEffectBase
{
public:
	CSttAssistWndFlash();
	virtual ~CSttAssistWndFlash();

	static long g_nCurrStyle;   //��������ͬ��ʽ����˸����ʽ��һ�£����ÿ������Բ��þ�̬

	static void AfterExec();
public:
	CString m_strStyleBack;
	CString m_strStyle1;
	CString m_strStyle2;
	long m_nFlashTimeLong;  //  ��λΪ����  ��˸��ʱ����	

public:
  //��̬Ч��ִ�к���
	virtual void ast_Exec(long nTimeGap);
	
  //ֹͣ��̬Ч��ִ��
	virtual void ast_Stop();
	
	//��ʱ������  ��ʱ������ʵ��
	//virtual void ast_on_timer(const CString &strTimerID);
	//virtual void ast_on_timer(long nTimerID);

protected:
	
};




#endif//_SttAssistGlobalApi_H__
