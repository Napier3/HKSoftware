//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

#pragma once

/*******************************
通用类消息窗口和消息接口实现：
1、解决类对象的独立定时器和消息处理【统一发送 XCOMM_WND_MSG 消息】；
2、使用时要求该类继承CXCommSvrWndInterface接口，
3、添加成员变量CXCommSvrWnd，
4、在构造或初始化函数中调用CreateXCommSvrWnd接口
5、重写定时器和消息处理接口OnXTimer和OnXCommMsg

具体实例参考：CIotEngineMqttServer
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

