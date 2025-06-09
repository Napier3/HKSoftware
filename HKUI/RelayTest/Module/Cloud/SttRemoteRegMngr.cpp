#include "stdafx.h"
#include "SttRemoteRegMngr.h"
#include "DB/SttRemoteCtrlDbRWTool.h"
#include "../SttGlobalDef.h"
#include "SttCloudSvrBaseApp.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttRemoteRegMngr g_oSttRemoteRegMngr;

CSttRemoteRegMngr::CSttRemoteRegMngr()
{
	//初始化属性
	m_strName = _T("远程控制服务");

	m_pMsgWnd = NULL;
	//初始化成员变量
}

CSttRemoteRegMngr::~CSttRemoteRegMngr()
{

}

CStt_RemoteRegRT *CSttRemoteRegMngr::FindByRefSocket(CSttCloudServerClientSocketBase *pRef_Socket)
{
	POS pos = GetHeadPosition();
	CStt_RemoteRegRT *pFind = NULL;

	while(pos != NULL)
	{
		pFind = (CStt_RemoteRegRT *)GetNext(pos);

		if (pFind->GetRefSocket() == pRef_Socket)
		{
			return pFind;
		}
	}

	return NULL;
}

CStt_RemoteRegRT *CSttRemoteRegMngr::FindByCode_Register(const CString &strCode_Register)
{
	ASSERT(!strCode_Register.IsEmpty());

	POS pos = GetHeadPosition();
	CStt_RemoteRegRT *pFind = NULL;

	while(pos != NULL)
	{
		pFind = (CStt_RemoteRegRT *)GetNext(pos);

		if (pFind->m_strCode_Register == strCode_Register)
		{
			return pFind;
		}
	}

	return NULL;
}

void CSttRemoteRegMngr::AddRegisterChild(CSttRemoteCmd &oRemoteCmd,CSttCloudServerClientSocketBase *pRef_Socket)
{
	ASSERT(pRef_Socket != NULL);

	CStt_RemoteRegHis oRemoteRegHis;

	oRemoteRegHis.AnalysisRegisterAttr(oRemoteCmd,pRef_Socket,CSttCloudServerConfig::GetRemoteCtrlHisRoot());

	CStt_RemoteRegRT *pNewRT = Stt_InitRegisterDB(g_pTheMySqlApp,CRemoteCtrlMngrXmlRWKeys::g_pXmlKeys,oRemoteRegHis);

	AddNewChild(pNewRT);

	//发消息给窗口更新
	if (m_pMsgWnd != NULL)
	{
		m_pMsgWnd->PostMessage(WM_UPDATE_REGMNGR,(WPARAM)pNewRT,WM_UPDATE_REG_ADD);
	}
}

void CSttRemoteRegMngr::DeleteRegisterChild(CSttCloudServerClientSocketBase *pRef_Socket)
{
	ASSERT(pRef_Socket != NULL);

	CStt_RemoteRegRT *pFind = FindByRefSocket(pRef_Socket);

	if (pFind == NULL)
	{
		return;
	}

	Stt_InitUnRegisterDB(g_pTheMySqlApp,CRemoteCtrlMngrXmlRWKeys::g_pXmlKeys,*pFind);

	Delete(pFind);

	//发消息给窗口更新
	if (m_pMsgWnd != NULL)
	{
		m_pMsgWnd->PostMessage(WM_UPDATE_REGMNGR,(WPARAM)pFind,WM_UPDATE_REG_DELETE);
	}
}

void CSttRemoteRegMngr::AnalysisUserList(CSttSysState *pSysState,CStt_RemoteRegRT &oUserList)
{
	ASSERT(pSysState != NULL);

	CSttParas *pSttParas = pSysState->GetSttParas();

	POS pos = pSttParas->GetHeadPosition();
	CExBaseObject *p = NULL;

	while(pos != NULL)
	{
		p = pSttParas->GetNext(pos);

		if (p->GetClassID() != DVMCLASSID_CDVMDATA)
		{
			continue;
		}
		if (p->m_strID != STT_CMD_TESTOR)
		{
			continue;
		}

		CStt_RemoteUserRT *pNewUser = new CStt_RemoteUserRT;

		pNewUser->AnalysisData((CDvmData *)p);

		oUserList.AddNewChild(pNewUser);
	}
}

void CSttRemoteRegMngr::Update_UserList(CSttSysState *pSysState,CSttCloudServerClientSocketBase *pRef_Socket)
{
	ASSERT(pRef_Socket != NULL);

	CStt_RemoteRegRT *pFind = FindByRefSocket(pRef_Socket);

	if (pFind == NULL)
	{
		return;
	}

	//远程控制测试仪、远程协助
	UpdateAssist_UserList(pSysState,pFind);

	//发消息给窗口更新
	if (m_pMsgWnd != NULL)
	{
		m_pMsgWnd->PostMessage(WM_UPDATE_REGMNGR,(WPARAM)pFind,WM_UPDATE_REG_UPDATE);
	}
}

// void CSttRemoteRegMngr::Update_UserList_Request(CSttSysState *pSysState,CSttCloudServerClientSocketBase *pRef_Socket)
// {
// 	ASSERT(pRef_Socket != NULL);
// 
// 	CStt_RemoteRegRT *pFind = FindByRefSocket(pRef_Socket);
// 
// 	if (pFind == NULL)
// 	{
// 		return;
// 	}
// 
// 	CExBaseList *pParas = pSysState->GetSttParas();
// 	CStt_RemoteUserRT *pUser = pFind->FindByIDTest(pSysState->m_nDestID);
// 
// 	g_pTheMySqlApp->StartTransaction();
// 
// 	if (pUser != NULL)
// 	{
// 		pUser->SetAuthoritys(pParas);
// 		pUser->UpdateDB_Authority(g_pTheMySqlApp,CRemoteCtrlMngrXmlRWKeys::g_pXmlKeys);
// 	}
// 
// 	pFind->ClearOtherAuthoritys(pParas, pUser,g_pTheMySqlApp,CRemoteCtrlMngrXmlRWKeys::g_pXmlKeys);
// 
// 	g_pTheMySqlApp->Commit();
// 
// 	//发消息给窗口更新
// 	if (m_pMsgWnd != NULL)
// 	{
// 		m_pMsgWnd->PostMessage(WM_UPDATE_REGMNGR,(WPARAM)pFind,WM_UPDATE_REG_UPDATE);
// 	}
// }

void CSttRemoteRegMngr::UpdateAssist_UserList(CSttSysState *pSysState,CStt_RemoteRegRT *pFind)
{
	CStt_RemoteRegRT oUserList;
	AnalysisUserList(pSysState,oUserList);

	Stt_UpdateUserDB(g_pTheMySqlApp,CRemoteCtrlMngrXmlRWKeys::g_pXmlKeys,pFind,oUserList);
}

void CSttRemoteRegMngr::UpdateTest_UserList(CSttSysState *pSysState)
{

}

BOOL CSttRemoteRegMngr::QueryRegisterList(const CString &strCode_Register,CStt_RemoteRegRTs &oRemoteRegRTs)
{
	if (!strCode_Register.IsEmpty())
	{
		CStt_RemoteRegRT *pFind = FindByCode_Register(strCode_Register);

		if (pFind == NULL)
		{
			return FALSE;
		}

		oRemoteRegRTs.AddTail(pFind);
	}
	else
	{
		oRemoteRegRTs.Append(*this);
	}

	return TRUE;
}