//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

#pragma once

/*******************************
ͨ������Ϣ���ں���Ϣ�ӿ�ʵ�֣�
1����������Ķ�����ʱ������Ϣ����ͳһ���� XCOMM_WND_MSG ��Ϣ����
2��ʹ��ʱҪ�����̳�CXCommSvrWndInterface�ӿڣ�
3����ӳ�Ա����CXCommSvrWnd��
4���ڹ�����ʼ�������е���CreateXCommSvrWnd�ӿ�
5����д��ʱ������Ϣ����ӿ�OnXTimer��OnXCommMsg

����ʵ���ο���CIotEngineMqttServer
*******************************/

#define XCOMM_WND_MSG (WM_USER + 2222)

class CXCommSvrWndInterface
{
public:
	virtual void OnXTimer(UINT nIDEvent){};
	virtual void OnXCommMsg(WPARAM wParam, LPARAM lParam){};
};

class CXCommSvrWnd : public CWnd
{
public:
	CXCommSvrWnd();
	virtual ~CXCommSvrWnd();

	void CreateXCommSvrWnd(CXCommSvrWndInterface *pInterface);

protected:
	CXCommSvrWndInterface *m_pInterfaceRef;

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg LRESULT OnXCommMsg(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT nIDEvent);
};

