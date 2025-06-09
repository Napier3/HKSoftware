#include "stdafx.h"
#include "EdgeMqttServerView.h"
#include "EdgeMqttServerDoc.h"
#include "../MosquittoClient.h"
#include "../Edge/EdgeEngineProtoSvrBaseApp.h"
#include "../../EdgeEngineProtocolServer/MainFrm.h"
#include "../../EdgeEngineProtocolServer/EdgeSmartTestCtrlCntr.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

IMPLEMENT_DYNCREATE(CEdgeMqttServerView, CFormView)

CEdgeMqttServerView::CEdgeMqttServerView()
	: CFormView(CEdgeMqttServerView::IDD)
{
	g_pEdgeEngineProtoSvrBaseApp->m_pMqttServerView = this;
}

CEdgeMqttServerView::~CEdgeMqttServerView()
{
	
}

void CEdgeMqttServerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_MQTTCLIENT_GRID,m_oMqttClientList);
}

BEGIN_MESSAGE_MAP(CEdgeMqttServerView, CFormView)
	ON_WM_SIZE()
END_MESSAGE_MAP()

void CEdgeMqttServerView::InitUI()
{
	((CEdgeMqttServerDoc*)m_pDocument)->SetTitle("MQTT客户端列表");
}

void CEdgeMqttServerView::XUI_InitAdjust()
{
	CXUIAdjItem_Area::XUI_SetParentWnd(this);
	XUI_AddWnd(&m_oMqttClientList, 0, 0, 1, 1);
	CXUIAdjItem_Area::XUI_OnSize();
}

void CEdgeMqttServerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	XUI_InitAdjust();

	m_oMqttClientList.InitGrid();
	InitUI();
}

BOOL CEdgeMqttServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CFormView::PreCreateWindow(cs);
}

void CEdgeMqttServerView::OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol)
{

}

void CEdgeMqttServerView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	XUI_OnSize(cx, cy);
}

LRESULT CEdgeMqttServerView::Process_Connect(WPARAM wParam, LPARAM lParam)
{
	CString strIP = (char*)wParam;
	CString strID = (char*)lParam;

	CExBaseObject* pClient = m_oClientList.FindChildByID(strID);
	if(pClient)
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("【MQTT错误】: 存在一个相同ID的客户端!"));
	else
	{
		CMosquittoClient* pClient = new CMosquittoClient();
		pClient->m_strName = strIP;
		pClient->m_strID = strID;
		m_oClientList.AddNewChild(pClient);
	}

	m_oMqttClientList.ShowDatas(&m_oClientList);

	free((void*)wParam);
	free((void*)lParam);

	return 0;
}

LRESULT CEdgeMqttServerView::Process_Disconnect(WPARAM wParam, LPARAM lParam)
{
	CString strID = (char*)lParam;
	CExBaseObject* pClient = m_oClientList.FindChildByID(strID);
	if(pClient)
	{
		//测试台断开连接时,断开测试台与数据库的连接
		m_oClientList.DeleteByID(strID);
	}
	else
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("【MQTT错误】: 尝试断开一个ID不存在的客户端!"));

	m_oMqttClientList.ShowDatas(&m_oClientList);

	free((void*)lParam);

	return 0;
}

LRESULT CEdgeMqttServerView::Process_Subscribe(WPARAM wParam, LPARAM lParam)
{
	CString strTopic = (char*)wParam;
	CString strID = (char*)lParam;

	CMosquittoClient* pClient = (CMosquittoClient*)m_oClientList.FindChildByID(strID);
	if(pClient)
	{
		CExBaseObject* pTopic = pClient->m_oTopics.FindChildByID(strTopic);
		if(pTopic)
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("【MQTT错误】: 客户端已经订阅了一个相同的主题!"));
		else
		{
			CString strText = strTopic;
			char* strUtf8 = NULL;
			long nUtf8Len = 0;
			charUtf8_to_charGBK(const_cast<char*>(strText.GetString()), strText.GetLength(), &strUtf8, nUtf8Len);
			strText = strUtf8;
			delete strUtf8;
			pClient->m_oTopics.AddNew(strID, strText);
		}
	}
	else
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("【MQTT错误】: 客户端不存在!"));

	free((void*)wParam);
	free((void*)lParam);

	return 0;
}

LRESULT CEdgeMqttServerView::Process_Unsubscribe(WPARAM wParam, LPARAM lParam)
{
	CString strTopic = (char*)wParam;
	CString strID = (char*)lParam;

	CMosquittoClient* pClient = (CMosquittoClient*)m_oClientList.FindChildByID(strID);
	if(pClient)
	{
		CExBaseObject* pTopic = pClient->m_oTopics.FindChildByID(strTopic);
		if(pTopic)
			pClient->m_oTopics.DeleteByID(strTopic);
		else
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("【MQTT错误】: 客户端不存在需要取消订阅的主题!"));
	}
	else
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("【MQTT错误】: 客户端不存在!"));

	free((void*)wParam);
	free((void*)lParam);

	return 0;
}