#include "stdafx.h"
#include "SttVmMacroTest.h"
#include "../SttAuthority/SttTestRemoteRegister.h"
#include "../SttCmd/SttTestCmd.h"

#include "../SttSocket/TestTerminal/VC/SttClientSocket.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CSttVmMacroTest::CSttVmMacroTest()
{
	g_pSttTestEngine = this;
	m_pSttClientSocket = new CSttClientSocket();
}

CSttVmMacroTest::~CSttVmMacroTest()
{

}

BOOL CSttVmMacroTest::ConnectServer(const CString &strIPServer, long nPort)
{
	ASSERT (m_pSttClientSocket != NULL);
	return m_pSttClientSocket->ConnectServer(strIPServer, nPort);
}

long CSttVmMacroTest::Process_Cmd_Test(CSttSocketDataBase *pClientSocket, CSttTestCmd &oTestCmd)
{
	
	return 0;
}

long CSttVmMacroTest::Process_Cmd_Ats(CSttSocketDataBase *pClientSocket, CSttAtsCmd &oAtsCmd)
{
	return 0;
}

long CSttVmMacroTest::Process_SysState(CSttSocketDataBase *pClientSocket, CSttSysState &oSysState)
{
	long nValue = 0;
	BOOL bPreLogin = FALSE;

	if (oSysState.m_strID == STT_CMD_TYPE_SYSTEM_Login)
	{//����ǵ�¼Ӧ�𡾱��ء�Զ�̡�
		return Process_SysState_Login(oSysState);
	}
	else if (oSysState.m_strID == STT_CMD_TYPE_SYSTEM_Logout)
	{//������˳���¼Ӧ�𡾱��ء�Զ�̡�
		return Process_SysState_Logout(oSysState);
	}
	else if (oSysState.m_strID == STT_CMD_TYPE_SYSTEM_Request)
	{//�����Ȩ������Ӧ�𡾱��ء�Զ�̡�
		return Process_SysState_Request(oSysState);
	}
	else if (oSysState.m_strID == STT_CMD_TYPE_REMOTE_Query)
	{//����ǲ�ѯ��Զ�̡�
		return Process_SysState_Query(oSysState);
	}
	else if (oSysState.m_strID == STT_CMD_TYPE_REMOTE_Bind)
	{//����ǰ�Ӧ��Զ�̡�
		return Process_SysState_Bind(oSysState);
	}
	else if (oSysState.m_strID == STT_CMD_TYPE_REMOTE_UnRegister)
	{//�����UnRegisterӦ��Զ�̡�
		return Process_SysState_UnRegister(oSysState);
	}
	else if (oSysState.m_strID == STT_CMD_TYPE_SYSTEM_Authority)
	{//�����AuthorityӦ��Զ�̡�
		return Process_SysState_Authority(oSysState);
	}
	else
	{//������������

	}
	
	return 0;
}

long CSttVmMacroTest::Process_SysState_Login(CSttSysState &oSysState)
{
	BOOL bPreLogin = HasLogin();

	if (m_oClientUserMngr.UpdateUserList(oSysState))
	{	
		if (UpdateLoginUser(&m_oCurrUser))
		{
			if (!bPreLogin)
			{
				CLogPrint::LogString(XLOGLEVEL_INFOR,_T("��¼�ɹ�"));
			}
		}
	}

	return 1;
}

long CSttVmMacroTest::Process_SysState_Logout(CSttSysState &oSysState)
{
	if (m_oClientUserMngr.UpdateUserList(oSysState))
	{	
		if (!UpdateLoginUser(&m_oCurrUser))
		{
			OnLogout();
			CLogPrint::LogString(XLOGLEVEL_INFOR,_T("�˳���¼�ɹ�"));
		}
	}

	return 1;
}

long CSttVmMacroTest::Process_SysState_Request(CSttSysState &oSysState)
{
	BOOL bMatch = FALSE;

	if (OnUpdate_Users(oSysState,bMatch))
	{	
		if (bMatch)
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR,_T("����Ȩ�޳ɹ�"));
		}
	}
	else if(bMatch)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("����Ȩ�ޱ��ܾ�"));
	}

	return 1;
}

long CSttVmMacroTest::Process_SysState_Query(CSttSysState &oSysState)
{
	UpdateRegisterList(oSysState);
	return 1;
}

long CSttVmMacroTest::Process_SysState_Bind(CSttSysState &oSysState)
{
	long nID_Remote = 0;
	
	if (!oSysState.Get_IsSuccess())
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("Bind����ܾ�"));
		return 0;
	}

	oSysState.GetParasDataValueByID(ID_STT_USER_ATTR_ID_Remote, nID_Remote);
	m_oCurrUser.ID_Remote(nID_Remote);
	m_oCurrUser.ID_Terminal(STT_TERMINAL_TYPE_REMOTE);

	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("Bind����ɹ�"));

	return 1;
}

long CSttVmMacroTest::Process_SysState_UnRegister(CSttSysState &oSysState)
{
	OnLogout();
	CLogPrint::LogString(XLOGLEVEL_INFOR,_T("���ض��˳�Զ�̿���"));
	return 1;
}

long CSttVmMacroTest::Process_SysState_Authority(CSttSysState &oSysState)
{
	BOOL bMatch = FALSE;

	if (OnUpdate_Users(oSysState,bMatch))
	{	
		if (bMatch)
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR,_T("��Ȩ�ɹ�"));
		}
	}
	else if(bMatch)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("��Ȩʧ��"));
	}

	return 1;
}

BOOL CSttVmMacroTest::OnUpdate_Users(CSttSysState &oSysState,BOOL &bMatch)
{
	bMatch = IsMatchIDTest(oSysState.m_nDestID);

	if (m_oClientUserMngr.UpdateUserList(oSysState))
	{	
		if (UpdateLoginUser(&m_oCurrUser))
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CSttVmMacroTest::UpdateRegisterList(CSttSysState &oSysState)
{//Query����Ӧ�𣬸���ע������
	m_oSttRemoteRegList.DeleteAll();

	POS pos = oSysState.GetHeadPosition();
	CExBaseObject *p = NULL;

	while(pos != NULL)
	{
		p = oSysState.GetNext(pos);

		if (p->GetClassID() != DVMCLASSID_CDVMDATA)
		{
			continue;
		}
		if (p->m_strID != _T("remote"))
		{
			continue;
		}
		CDvmData *pData = (CDvmData *)p;

		CSttTestRemoteRegister *pNew = new CSttTestRemoteRegister;
		pNew->AppendEx(*pData);
		m_oSttRemoteRegList.AddNewChild(pNew);

		pData->RemoveAll();
	}

	return TRUE;
}

void CSttVmMacroTest::OnLogout()
{
	m_oCurrUser.OnLogout();
	m_oClientUserMngr.DeleteAll();

	//�Ͽ�����
	CloseSocket(m_pSocketDataBase);
}