
// iSmartTestNewTestFrame.cpp : CiSmartTestNewTestFrame ���ʵ��
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

// CiSmartTestNewTestFrame ����/����

CEdgeMqttServerFrame::CEdgeMqttServerFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CEdgeMqttServerFrame::~CEdgeMqttServerFrame()
{
}


BOOL CEdgeMqttServerFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CiSmartTestNewTestFrame ���

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

// CiSmartTestNewTestFrame ��Ϣ�������
void CEdgeMqttServerFrame::OnClose()
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("MQTT�ͻ����б��ֹ�ر�..."));
	return;
}

