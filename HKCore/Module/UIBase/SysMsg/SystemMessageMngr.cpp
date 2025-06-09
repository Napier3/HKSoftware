// SystemMessageMngr.cpp: implementation of the CSystemMessageMngr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SystemMessageMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const char* CSystemMessageMngr::g_pszKeySystemMessageDefine = "system-message-define";
const char* CSystemMessageMngr::g_pszKeySystemMessageFile   = "system-messages.xml";

CSystemMessageMngr* CSystemMessageMngr::g_pSystemMessageMngr = NULL;
long CSystemMessageMngr::g_nSysMsgMngrRefCount = 0;

CSystemMessageMngr* CSystemMessageMngr::CreateSystemMessageMngr()
{
	if (g_nSysMsgMngrRefCount == 0)
	{
		g_pSystemMessageMngr = new CSystemMessageMngr();
	}
	
	g_nSysMsgMngrRefCount++;
	
	return g_pSystemMessageMngr;
}

long CSystemMessageMngr::Release()
{
	if (g_nSysMsgMngrRefCount > 0)
	{
		g_nSysMsgMngrRefCount--;
		
		if (g_nSysMsgMngrRefCount == 0)
		{
			delete g_pSystemMessageMngr;
			g_pSystemMessageMngr = NULL;
		}
	}
	
	return g_nSysMsgMngrRefCount;
}

CSystemMessageMngr::CSystemMessageMngr()
{
	m_pSystemKeys    = NULL;
	m_pSingleSysMsgs = NULL;
	m_pMultiSysMsgs  = NULL;
	m_pAppSysKeyMaps = NULL;
	m_bHasInited     = FALSE;

	m_dwKeyDownTime      = 50;//2000
	m_dwKeyDownTimeAccel = 20;	//200
	m_dwKeyDownTimeDoubleClick = 150;	//800

#ifdef _SysMsg_WriteToFile
	m_bSysMsgFile = FALSE;
#endif	
}

CSystemMessageMngr::~CSystemMessageMngr()
{
#ifdef _SysMsg_WriteToFile
	if (m_bSysMsgFile)
	{
		m_oSysMsgFile.Close();
	}
#endif
}

#ifdef _SysMsg_WriteToFile
void CSystemMessageMngr::WriteSystemMessageFile()
{
	if (! m_bSysMsgFile)
	{
		return;
	}

	void *pos = m_oSysMsgs.GetHeadPosition();
	CSystemMessage *pMsg = NULL;
	CString strTemp;

	strTemp.Format("\n\n\n################################################################\n\n");
	m_oSysMsgFile.Write(strTemp, strTemp.GetLength());
	
	while (pos != NULL)
	{
		pMsg = (CSystemMessage*)m_oSysMsgs.GetNext(pos);
		if (pMsg->GetClassID() == CLASSID_SYSTEMMESSAGE_SINGLE)
		{
			CSystemMessageSingle *pSingleMsg = (CSystemMessageSingle*)pMsg;
			strTemp.Format("SysMsg: name(%s) index(%d)  id(%d)  time(%d)  keystate(%d)\n", 
				pSingleMsg->m_strName, pSingleMsg->m_nIndex, pSingleMsg->m_nID, pSingleMsg->m_dwTickCount, pSingleMsg->m_nKeyState);
			m_oSysMsgFile.Write(strTemp, strTemp.GetLength());
		}
	}
}
#endif

//XML��д
BOOL CSystemMessageMngr::ReadSystemMessageXmlFile()
{
	CString strFile;
	strFile.Format("%s%s", _P_GetConfigPath(), g_pszKeySystemMessageFile);
	return OpenXmlFile(strFile);
}

BOOL CSystemMessageMngr::OpenXmlFile(const CString &strFile)
{
	MSXML::IXMLDOMDocumentPtr oDoc = NULL;
	HRESULT hr = oDoc.CreateInstance(__uuidof(MSXML::DOMDocument));
	
	if(!SUCCEEDED(hr)) 
	{ 
		return FALSE;
	} 
	
	MSXML::IXMLDOMNodePtr oSysMsgDef = NULL;
	BSTR bstrFile = strFile.AllocSysString();
	BOOL bTrue = oDoc->load(bstrFile);
	::SysFreeString(bstrFile);
	
	if (!bTrue)
	{
		TRACE("\nRead language file failed......\n");
	}
	
	oSysMsgDef = oDoc->selectSingleNode(_bstr_t(g_pszKeySystemMessageDefine));
	
	if (oSysMsgDef == NULL)
	{
		return FALSE;
	}
	
	ReadXml(oSysMsgDef);
	m_bHasInited = TRUE;

	if (m_pSingleSysMsgs != NULL)
	{
		m_pSingleSysMsgs->InitSingleSystemMessages(m_pSystemKeys);
	}
	
	if (m_pMultiSysMsgs != NULL)
	{
		m_pMultiSysMsgs->InitMultiSystemMessages(m_pSingleSysMsgs);
	}

#ifdef _SysMsg_WriteToFile
	CString strSysMsgFileTemp;
	strSysMsgFileTemp.Format("%s\\SysMsgFile.txt", _P_GetConfigPath());
	m_bSysMsgFile = m_oSysMsgFile.Open(strSysMsgFileTemp, CFile::modeCreate | CFile::modeWrite);
#endif
	
	return m_bHasInited;
}

CExBaseObject* CSystemMessageMngr::CreateNewChild(LPCTSTR pszClassID)
{
	CExBaseObject *pNew = NULL;

	if (stricmp(pszClassID, CAppSysKeyMaps::g_pszKeyKeyMaps) == 0)
	{
		if (m_pAppSysKeyMaps == NULL)
		{
			m_pAppSysKeyMaps  = new CAppSysKeyMaps();
			pNew = m_pAppSysKeyMaps;
		}
	}
	else if (stricmp(pszClassID, CSystemKeys::g_pszKeySysKeys) == 0)
	{
		if (m_pSystemKeys == NULL)
		{
			m_pSystemKeys  = new CSystemKeys();
			pNew = m_pSystemKeys;
		}
	}
	else if (stricmp(pszClassID, CSystemMessages::g_pszKeyMultiSysMsgs) == 0)
	{
		if (m_pMultiSysMsgs == NULL)
		{
			m_pMultiSysMsgs  = new CSystemMessages();
			pNew = m_pMultiSysMsgs;
		}
	}
	else if (stricmp(pszClassID, CSystemMessages::g_pszKeySingleSysMsgs) == 0)
	{
		if (m_pSingleSysMsgs == NULL)
		{
			m_pSingleSysMsgs  = new CSystemMessages();
			pNew = m_pSingleSysMsgs;
		}
	}
	else
	{
	}

	return pNew;
}

CExBaseObject* CSystemMessageMngr::CreateNewChild(long nClassID)
{
	return NULL;
}

long CSystemMessageMngr::GetSystemMessageID(const CString &strSysMsg)
{
	CSystemMessage *pSysMsg = NULL;

	if (m_pSingleSysMsgs != NULL)
	{
		pSysMsg = (CSystemMessage*)m_pSingleSysMsgs->FindByName(strSysMsg);
		
		if (pSysMsg != NULL)
		{
			return pSysMsg->m_nID;
		}
	}

	if (m_pMultiSysMsgs != NULL)
	{
		pSysMsg = (CSystemMessage*)m_pMultiSysMsgs->FindByName(strSysMsg);
		
		if (pSysMsg != NULL)
		{
			return pSysMsg->m_nID;
		}
	}

	return -1;
}

BOOL CSystemMessageMngr::HasSysMsgNeedPost()
{
	BOOL bNeed = FALSE;
	CSystemMessage *pTail = (CSystemMessage*)m_oSysMsgs.GetTail();

	if(pTail != NULL)
	{
		if (!pTail->m_bMsgHasPosted)
		{
			bNeed = TRUE;
		}
	}

	return bNeed;
}

//��Ϣ����
CSystemMessage* CSystemMessageMngr::TranslateMessage(MSG *pMsg)
{
	//�ж��Ƿ��Ѿ���XML�����ļ��ж�ȥ����������
	if (!m_bHasInited)
	{
		return NULL;
	}
	
	//ֻ��������Ϣ
	if (pMsg->wParam > 255)
	{
		return NULL;
	}

	//�Ƿ������Ϣ�������¡�����
	if ( (pMsg->message == WM_KEYDOWN) || (pMsg->message == WM_KEYUP) 
		|| (pMsg->message == WM_SYSKEYDOWN) || (pMsg->message == WM_SYSKEYUP))
	{
	}
	else
	{
		return NULL;
	}
	
#ifdef _SysMsg_WriteToFile
	if (m_bSysMsgFile)
	{
		CString strSysMsgFileTemp;
		strSysMsgFileTemp.Format("msg=%04x(%c,%x)  tm=%d\n", pMsg->message, pMsg->wParam, pMsg->lParam, pMsg->time);
		m_oSysMsgFile.Write(strSysMsgFileTemp, strSysMsgFileTemp.GetLength());
	}

	DWORD dwTickCountBegin = ::GetTickCount();
#endif

	CSystemMessage *pSysMsg = NULL;
	
	//��ǰ����û�ж��壬�򲻴���ͬʱ�����Ϣ�б�
	//��Ҫ�ǿ��Ǹ��ϰ�����˳����̣��������һ��û�ж���ļ�
	//�򸴺ϰ����п��ܱ�������ж�
	//���磬ϵͳ���塰A��S��D��F��4��ϵͳ���������ϰ�������Ϊ���ΰ���
	//��A��S��D�������ʵ�ʰ�����A��H��S��D����������������ж�Ϊ���ϰ���
	CSystemKey *pKey = m_pSystemKeys->FindByKeyID(pMsg->wParam);
	
	if (pKey == NULL)
	{
		m_oSysMsgs.DeleteAll();
		return NULL;
	}

	CSystemMessage *pTail = (CSystemMessage*)m_oSysMsgs.GetTail();

	if (pTail == NULL)
	{
		pSysMsg = AddMessage(pMsg);
	}
	else
	{
		if (pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYDOWN)
		{
			pSysMsg = AddKeyDownMessage(pMsg);
		}
		else if (pMsg->message == WM_KEYUP || pMsg->message == WM_SYSKEYUP)
		{
			pSysMsg = AddKeyUpMessage(pMsg);
		}
		else
		{
		}
	}

#ifdef _SysMsg_WriteToFile
	DWORD dwTickCountEnd = ::GetTickCount();
	if (m_bSysMsgFile)
	{
		CString strSysMsgFileTemp;
		strSysMsgFileTemp.Format("     time_long=%d \n", dwTickCountEnd-dwTickCountBegin);
		m_oSysMsgFile.Write(strSysMsgFileTemp, strSysMsgFileTemp.GetLength());
	}
	
#endif
	
	//ɾ�������ײ�û����ʹ�õ�ϵͳ��Ϣ
	DeleteTopMessages();

	return pSysMsg;
}

CSystemMessage* CSystemMessageMngr::AddMessage(MSG *pMsg)
{
	CSystemMessage *pNew = NULL;
	CSystemMessage *pFind = NULL;
	long nKeyState = 0;
		
	//����ϵͳ������Ϣ,��ȡ�����ж�Ӧ�İ���״̬
	nKeyState = CSystemMessageSingle::GetSysKeyState(pMsg->message, nKeyState);
	pFind = m_pSingleSysMsgs->FindSingleSysMsg(pMsg->wParam, nKeyState);
	
	if (pFind != NULL)
	{
		CSystemMessageSingle *pNewTemp = (CSystemMessageSingle*)pFind->Clone();
		pNewTemp->m_nKeyState = nKeyState;
		
		pNew = pNewTemp;
		pNew->m_nIndex = 0;
		pNew->m_dwTickCount = pMsg->time;
		
		m_oSysMsgs.AddTail(pNew);

#ifdef _SysMsg_WriteToFile
		if (m_bSysMsgFile)
		{
			CString strSysMsgFileTemp;
			strSysMsgFileTemp.Format("          SysMsg: name(%s)  id(%d)  time(%d)  keystate(%d)\n", pNewTemp->m_strName, pNewTemp->m_nID, pNewTemp->m_dwTickCount, nKeyState);
			m_oSysMsgFile.Write(strSysMsgFileTemp, strSysMsgFileTemp.GetLength());
		}
#endif
				
	}
	else
	{
		int i = 0;
	}

	return pNew;
}

CSystemMessage* CSystemMessageMngr::AddMessage(CSystemMessageSingle *pSysMsg, MSG *pMsg, long nKeyState)
{
	CSystemMessage *pFind = NULL;
	pFind = m_pSingleSysMsgs->FindSingleSysMsg(pMsg->wParam, nKeyState);
	CSystemMessageSingle *pNew = NULL;
	
	if (pFind != NULL)
	{		
		pNew = (CSystemMessageSingle*)pFind->Clone();
		pNew->m_dwTickCount = pMsg->time;

		if (KEYSTATE_DOWN == nKeyState)
		{
			pNew->m_nIndex = pSysMsg->m_nIndex+1;
		}
		else
		{
			pNew->m_nIndex = 0;
		}
		
		pNew->m_nKeyState = nKeyState;
		m_oSysMsgs.AddTail(pNew);

#ifdef _SysMsg_WriteToFile
		if (m_bSysMsgFile)
		{
			CString strSysMsgFileTemp;
			strSysMsgFileTemp.Format("          SysMsg: name(%s) index(%d)  id(%d)  time(%d)  keystate(%d)\n", pNew->m_strName, pNew->m_nIndex, pNew->m_nID, pNew->m_dwTickCount, nKeyState);
			m_oSysMsgFile.Write(strSysMsgFileTemp, strSysMsgFileTemp.GetLength());
		}
#endif
		
	}

	return pNew;
}

CSystemMessage* CSystemMessageMngr::AddKeyDownMessage(MSG *pMsg)
{
	CSystemMessage *pTail = (CSystemMessage*)m_oSysMsgs.GetTail();
	CSystemMessage *pNew = NULL;
	CSystemMessageSingle *pSysMsgSingle = NULL;

	long nClassID = pTail->GetClassID();

	if (nClassID == CLASSID_SYSTEMMESSAGE_SINGLE)
	{
		pSysMsgSingle = (CSystemMessageSingle*)pTail;

		//�ж�ǰһ��Ϣ�Ƿ�Ϊ��ͬ������KeyDown��Ϣ
		//������������������̶���ʱ�������Ϣ�Լ����ٵ���Ϣ
		if (pSysMsgSingle->IsKeyDown(pMsg->wParam))
		{
			//ǰһ��ϢΪ��һ����Ϣ
			if (pSysMsgSingle->m_nIndex == 0)
			{
				//Windowsϵͳ�ڼ��������µ�ʱ�򣬲��ϵط���MSG������ֻ��ӳ�����ʱʱ���MSG
				//���ﶨʱʱ��1
				if (pMsg->time - pSysMsgSingle->m_dwTickCount >= m_dwKeyDownTime)
				{
					pNew = AddMessage(pSysMsgSingle, pMsg, KEYSTATE_DOWN);
				}
				else
				{
				}
			}
			else
			{
				//���ﶨʱʱ��2
				if (pMsg->time - pSysMsgSingle->m_dwTickCount >= m_dwKeyDownTimeAccel)
				{
					pNew = AddMessage(pSysMsgSingle, pMsg, KEYSTATE_DOWN);
				}
				else
				{
				}
			}
		}
		else
		{
			pNew = AddMessage(pMsg);
		}
	}
	else
	{
		pNew = AddMessage(pMsg);
	}
	
	return pNew;	
}

CSystemMessage* CSystemMessageMngr::AddKeyUpMessage(MSG *pMsg)
{
	CSystemMessage *pNew = NULL;

	//���ͼ�upϵͳ��Ϣ��ӵ���Ϣ�����б�
	pNew = AddMessage(pMsg);

	//��Ӽ���KeyClickϵͳ��Ϣ��ӵ���Ϣ�����б�
	pNew = AddClickMessage(pMsg);

	return pNew;	
}

CSystemMessage* CSystemMessageMngr::AddClickMessage(MSG *pMsg)
{
	CSystemMessageSingle *pNew = NULL;
	long nCount = m_oSysMsgs.GetCount();
	
	if (nCount < 2)
	{
		return pNew;
	}

	CExBaseObject *pObj = m_oSysMsgs.GetAt(nCount-2);
	
	if (pObj->GetClassID() == CLASSID_SYSTEMMESSAGE_SINGLE)
	{
		CSystemMessageSingle *pSysMsg = (CSystemMessageSingle*)pObj;
		
		//ǰһ��ϢΪ��ͬ����down
		if (pSysMsg->IsKeyDown(pMsg->wParam))
		{
			//���ͼ���KeyClickϵͳ��Ϣ��ӵ���Ϣ�����б�
			pNew = (CSystemMessageSingle*)AddMessage(pSysMsg, pMsg, KEYSTATE_CLICK);
			pNew = (CSystemMessageSingle*)AddDbClickMessage(pNew, pMsg);
		}
		else
		{
		}
	}

	return pNew;
}

/*
 ֮ǰû���κΰ���û�е���İ���
 ��Key n Downϵͳ��Ϣ
 Key n Down
 Key n Up
 Key n Click
 Key n Down
 Key n Up
 Key n Click
*/
CSystemMessage* CSystemMessageMngr::AddDbClickMessage(CSystemMessageSingle *pSysMsg, MSG *pMsg)
{
	if (pSysMsg == NULL)
	{
		return NULL;
	}
	
	long nCount = m_oSysMsgs.GetCount();

	if (nCount < 6)
	{
		return NULL;
	}

	CSystemMessageSingle *pNew = NULL;
	void *pos = m_oSysMsgs.FindByIndex(nCount - 6);
	CSystemMessage *pSysMsg1 = (CSystemMessage*)m_oSysMsgs.GetNext(pos);
	CSystemMessage *pSysMsg2 = (CSystemMessage*)m_oSysMsgs.GetNext(pos);
	CSystemMessage *pSysMsg3 = (CSystemMessage*)m_oSysMsgs.GetNext(pos);
	CSystemMessage *pSysMsg4 = (CSystemMessage*)m_oSysMsgs.GetNext(pos);
	CSystemMessage *pSysMsg5 = (CSystemMessage*)m_oSysMsgs.GetNext(pos);
	CSystemMessage *pSysMsg6 = (CSystemMessage*)m_oSysMsgs.GetAt(pos);

	UINT nKeyID = pSysMsg->m_nSysKeyID;

	if (   SysMsg_IsKeyDown(pSysMsg1, nKeyID) && pSysMsg1->m_nIndex == 0
		&& SysMsg_IsKeyUp(pSysMsg2, nKeyID)
		&& SysMsg_IsKeyClick(pSysMsg3, nKeyID)
		&& SysMsg_IsKeyDown(pSysMsg4, nKeyID)
		&& SysMsg_IsKeyUp(pSysMsg5, nKeyID)
		&& SysMsg_IsKeyClick(pSysMsg6, nKeyID) )
	{
		//����DbClickʱ��Ҫ��
		if (pMsg->time - pSysMsg3->m_dwTickCount <= m_dwKeyDownTimeDoubleClick)
		{
			pNew = (CSystemMessageSingle*)AddMessage(pSysMsg, pMsg, KEYSTATE_DBCLICK);
		}
	}
	else
	{
	}

	return pNew;
}

void CSystemMessageMngr::DeleteTopMessages()
{
	while (m_oSysMsgs.GetCount() > 50)
	{
		m_oSysMsgs.DeleteHead();
	}
}

long  SysMsg_GetSystemMessageID(const CString &strSysMsg)
{
	if (strSysMsg == NONE_SYSTEMMESSAGEID)
	{
		return -1;
	}
	
	ASSERT (CSystemMessageMngr::g_pSystemMessageMngr != NULL);

	return CSystemMessageMngr::g_pSystemMessageMngr->GetSystemMessageID(strSysMsg);
}