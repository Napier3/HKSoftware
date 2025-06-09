//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ServerUser.cpp  CServerUserListCtrl


#include "stdafx.h"
#include "ServerUserListCtrl.h"
#include "XUserTcpServer.h"

#include "..\XLanguage\XLanguageResource.h"

CServerUserListCtrl::CServerUserListCtrl()
{
	//��ʼ������

	//��ʼ����Ա����
}

CServerUserListCtrl::~CServerUserListCtrl()
{

}

#define SAFEUSER_COL_INDEX      0
#define SAFEUSER_COL_USERNAME   1
#define SAFEUSER_COL_MODULE     2
#define SAFEUSER_COL_IP         3
#define SAFEUSER_COL_STATE      4
#define SAFEUSER_COL_REMOTEPORT 5
#define SAFEUSER_COL_LOCALPORT  6
#define SAFEUSER_COL_WORKPATH   7

void CServerUserListCtrl::InitCollumns()
{
	InsertColumn(SAFEUSER_COL_INDEX,     CXLanguageResourceBase::g_sLangTxt_Index,    LVCFMT_CENTER,40);
	InsertColumn(SAFEUSER_COL_USERNAME,  CXLanguageResourceBase::g_sLangTxt_User,LVCFMT_LEFT,160);/*_T("�û�")*/
	InsertColumn(SAFEUSER_COL_IP,        _T("IP"),  LVCFMT_LEFT,120);
	InsertColumn(SAFEUSER_COL_MODULE,    CXLanguageResourceBase::g_sLangTxt_Module,  LVCFMT_LEFT,120);/*_T("ģ��")*/
	InsertColumn(SAFEUSER_COL_REMOTEPORT,CXLanguageResourceBase::g_sLangTxt_RemotePort ,LVCFMT_CENTER,100);/*_T("Զ�̶˿�")*/
	InsertColumn(SAFEUSER_COL_LOCALPORT, CXLanguageResourceBase::g_sLangTxt_LocalPort,LVCFMT_CENTER,100);/* _T("���ض˿�")*/
	InsertColumn(SAFEUSER_COL_STATE,     CXLanguageResourceBase::g_sLangTxt_State,LVCFMT_CENTER,120);/*_T("״̬")*/
	InsertColumn(SAFEUSER_COL_WORKPATH,  CXLanguageResourceBase::g_sLangTxt_ServerWorkPath,  LVCFMT_CENTER,280);/*_T("����������·��")*/
}

void CServerUserListCtrl::UpdateListCtrl(CExBaseObject *pObj, long nIndex)
{
	CXUserTcpServerClientObject *pClientObject = (CXUserTcpServerClientObject*)pObj;

	CString strText;
	strText.Format(_T("%d"), nIndex+1);
	SetItemText(nIndex, SAFEUSER_COL_INDEX, strText);

	if (pClientObject->m_pCurrUser != NULL)
	{
		SetItemText(nIndex, SAFEUSER_COL_USERNAME, pClientObject->m_pCurrUser->m_strName);
	}

	SetItemText(nIndex, SAFEUSER_COL_IP, pClientObject->m_strRemoteIp);
	SetItemText(nIndex, SAFEUSER_COL_MODULE, pClientObject->m_strModule);

	strText.Format(_T("%d"), pClientObject->m_nReotePort);
	SetItemText(nIndex, SAFEUSER_COL_REMOTEPORT, strText);

	strText.Format(_T("%d"), pClientObject->m_nLocalPort);
	SetItemText(nIndex, SAFEUSER_COL_LOCALPORT, strText);

	SetItemData(nIndex, (DWORD)pObj);
}

void CServerUserListCtrl::UpdateListCtrl(CExBaseObject *pObj)
{
	long nCount = GetItemCount();
	long nIndex = 0;
	CExBaseObject *pObjFind = NULL;
	BOOL bFind  = FALSE;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pObjFind = (CExBaseObject *)GetItemData(nIndex);

		if (pObjFind == pObj)
		{
			bFind = TRUE;
			break;
		}
	}

	if (bFind)
	{
		UpdateListCtrl(pObj, nIndex);
	}
	else
	{
		AddObj(pObj);
	}
}
