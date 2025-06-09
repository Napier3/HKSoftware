//SttAssistWndDynEffectBase.h
#ifndef _SttAssistWndDynEffectBase_H__
#define _SttAssistWndDynEffectBase_H__

#include "../SttAssistInterface.h"
#include "../SttAppWndAssistInterface.h"
#include "../../UI/SttStyleSheetGlobalDefine.h"
#include <QWidget>

#define ASSIST_MSG_WND_GAP   20

//���ֶ�̬Ч��ִ�й��߻���
//���ж�̬Ч��ִ�ж���Ӵ�������
class CSttAssistWndDynEffectBase : public CExBaseList
{
public:
	CSttAssistWndDynEffectBase();
	virtual ~CSttAssistWndDynEffectBase();
	
public:
	QWidget *m_pCurrWnd;
	CString m_strWndID;
	bool m_bIsStoped;
	long m_nTimeLong;  //����ʱ��, <=0��ʾ����ʱ��  ��λΪ���� 
	long m_nTimeExec;   //����ʱ��  ��λΪ���� 

  //��̬Ч��ִ�к���
	virtual void ast_Exec(long nTimeGap);
	
  //ֹͣ��̬Ч��ִ��
	virtual void ast_Stop();
	
	//��ʱ������
	virtual void ast_on_timer(const CString &strTimerID);
	virtual void ast_on_timer(long nTimerID);

};

#endif//_SttAssistWndDynEffectBase_H__
