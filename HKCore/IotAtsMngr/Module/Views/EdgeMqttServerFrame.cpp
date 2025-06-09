
// iSmartTestNewTestFrame.cpp : CiSmartTestNewTestFrame 类的实现
//

#include "stdafx.h"

#include "EdgeMqttServerFrame.h"
#include "EdgeMqttServerView.h"
#include "../../EdgeEngineProtocolServer/MainFrm.h"
#include "../../EdgeEngineProtocolServer/EdgeSmartTestCtrlCntr.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

// CiSmartTestNewTestFrame

IMPLEMENT_DYNCREATE(CEdgeMqttServerFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CEdgeMqttServerFrame, CMDIChildWndEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CiSmartTestNewTestFrame 构造/析构

CEdgeMqttServerFrame::CEdgeMqttServerFrame()
{
	// TODO: 在此添加成员初始化代码
}

CEdgeMqttServerFrame::~CEdgeMqttServerFrame()
{
}


BOOL CEdgeMqttServerFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CiSmartTestNewTestFrame 诊断

#ifdef _DEBUG
void CEdgeMqttServerFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CEdgeMqttServerFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CiSmartTestNewTestFrame 消息处理程序
void CEdgeMqttServerFrame::OnClose()
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("MQTT客户端列表禁止关闭..."));
	return;
}

