#include "StdAfx.h"
#include "PpNode.h"
#include "PpProcedure.h"
#include "PpPackageSend.h"
#include "../XLanguageResourcePp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPpNode::CPpNode(long nType)
{
	m_pResponseNodes = NULL;
	m_pJumps = NULL;
	m_pProcessNodes = NULL;
	m_pTimers = NULL;
	m_pInitScript = NULL;
	m_pEndScript = NULL;
	m_pPackageRef = NULL;
	m_nTypeID = nType;
	m_pPackageSend = NULL;
	m_pPackageRefs = NULL;
}

CPpNode::~CPpNode(void)
{
}

long CPpNode::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CProtocolXmlRWKeys *pKey = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pKey->m_strUseCmmChannelKey, oNode, m_strChannelID);

	return 0;
}

long CPpNode::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CProtocolXmlRWKeys *pKey = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pKey->m_strUseCmmChannelKey, oElement, m_strChannelID);

	return 0;
}

long CPpNode::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

CExBaseObject* CPpNode::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPackageRefKey)
	{
		return new CPpPackageRef();
	}
	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPackageRefsKey)
	{
		return new CPpPackageRefs();
	}
	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPpJumpsKey)
	{
		return new CPpJumps();
	}
	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPpTimersKey)
	{
		return new CPpTimers();
	}
	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strResponseKey)
	{
		CPpNodes* pNodes = new CPpNodes(PPNODE_TYPE_RESPONSE);
		return pNodes;
	}
	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strProcessKey)
	{
		CPpNodes* pNodes = new CPpNodes(PPNODE_TYPE_PROCESS);
		return pNodes;
	}

	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strInitScriptKey)
	{
#ifdef UNICODE
		return new CPpScript(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strInitScriptKey);
#else
		return new CPpScript(CString(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strInitScriptKey));
#endif
	}

	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strEndScriptKey)
	{
#ifdef UNICODE
		return new CPpScript(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strEndScriptKey);
#else
		return new CPpScript(CString(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strEndScriptKey));
#endif
	}

	return NULL;
}

CExBaseObject* CPpNode::CreateNewChild(long nClassID)
{
	return NULL;
}

void CPpNode::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject* pObj = NULL;
	LONG nClassID;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();
		switch (nClassID)
		{
		case PPCLASSID_PPPACKAGEREF:
			m_pPackageRef = (CPpPackageRef *)pObj;
			break;
		case PPCLASSID_PPPACKAGEREFS:
			m_pPackageRefs = (CPpPackageRefs*)pObj;
			break;
		case PPCLASSID_PPJUMPS:
			m_pJumps = (CPpJumps*)pObj;
			break;
		case PPCLASSID_PPTIMERS:
			m_pTimers = (CPpTimers*)pObj;
			break;
		case  PPCLASSID_PPNODES:
			{
				CPpNodes* pNodes = (CPpNodes*)pObj;
				if (pNodes->IsPpResponseNodes())
				{
					m_pResponseNodes = (CPpNodes*)pObj;
				}
				else if (pNodes->IsPpProcessNodes())
				{
					m_pProcessNodes = (CPpNodes*)pObj;
				}	
				else
				{
					ASSERT (FALSE);
				}
			}
			
			break;

		case PPCLASSID_PPSCRIPT:
			{
				CPpScript *pScript = (CPpScript*)pObj;

				if (pScript->m_strXmlKey == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strEndScriptKey)
				{
					m_pEndScript = pScript;
				}
				else if(pScript->m_strXmlKey == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strInitScriptKey)
				{
					m_pInitScript = pScript;
				}
			}
			break;
		default:
			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CPpNode::IsEqualOwn(CBaseObject* pObj)
{
	ASSERT (pObj == NULL);

	if (pObj == NULL)
	{
		return FALSE;
	}

	if (this == pObj)
	{
		return TRUE;
	}

	if (m_nTypeID != ((CPpNode*)pObj)->m_nTypeID)
	{
		return FALSE;
	}

	return CExBaseList::IsEqualOwn(pObj);
}

CBaseObject* CPpNode::Clone()
{
	CPpNode* pNew = new CPpNode(m_nTypeID);
	Copy(pNew);
	return pNew;
}

BOOL CPpNode::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CPpNode*)pDest)->m_nTypeID = m_nTypeID;
	((CPpNode*)pDest)->m_strChannelID = m_strChannelID;

	return CExBaseList::CopyOwn(pDest);
}

void CPpNode::SetNodePackageID(const CString &strPakageID)
{
	InitPackageRef();
	m_pPackageRef->SetPackageID(strPakageID);
}

CString CPpNode::GetNodePackageID()
{
	if (m_pPackageRef == NULL)
	{
		return _T("");
	}
	else
	{
		return m_pPackageRef->GetPackageID();
	}
}

void CPpNode::InitPackageRef()
{
	if (m_pPackageRef == NULL)
	{
		m_pPackageRef = new CPpPackageRef();
		AddTail(m_pPackageRef);
		m_pPackageRef->SetParent(this);
	}
}

BOOL CPpNode::IsPackageResponse(CPpPackageDetail *pPkgDetail)
{
	if (m_pPackageRef == NULL)
	{
		return FALSE;
	}
	
	return (m_pPackageRef->m_strPkgID == pPkgDetail->m_strID);
}


BOOL CPpNode::IsPackageResponses(CPpPackageDetail *pPkgDetail)
{
	POS pos = m_pResponseNodes->GetHeadPosition();
	CPpNode *pNode = NULL;
	BOOL bTrue = FALSE;

	while (pos != NULL)
	{
		pNode = (CPpNode*)m_pResponseNodes->GetNext(pos);

		if (pNode->IsPackageResponse(pPkgDetail))
		{
			bTrue = TRUE;
			break;
		}
	}
	
	return bTrue;
}

void CPpNode::BeginTimer()
{
	if (m_strID == _T("return_head"))
	{
		int i = 0;
	}

	if (m_pTimers != NULL)
	{
		m_pTimers->BeginTimer();
	}
}
void CPpNode::ResetTimer()
{
	if (m_strID == _T("return_head"))
	{
		int i = 0;
	}

	if (m_pTimers != NULL)
	{
		m_pTimers->ResetTimer();
	}
}

void CPpNode::KillTimer()
{
	if (m_pTimers != NULL)
	{
		m_pTimers->KillTimer();
	}
}

CPpNode* CPpNode::RunJumps(CPpPackageDetail *pPkgDetail)
{
	//执行初始化脚本
	RunInitScript(pPkgDetail);

	if (m_pJumps == NULL)
	{
		return NULL;
	}

	CPpNode *pNode = m_pJumps->RunJumps(pPkgDetail);

	//执行结束脚本
	//RunEndScript(pPkgDetail);

	return pNode;
}

CPpNode*  CPpNode::RunTimers(DWORD dwTickCount)
{
	return m_pTimers->RunTimer(dwTickCount);
}

BOOL CPpNode::IsEndNode()
{
	return (g_pPpEndNode == this);
}


CPpNode* PpGetJumpToNode(const CString &strJumpTo, CPpNode *pJumpTo, CExBaseObject *pJumpDef)
{
	CPpNode *pNode = NULL;

	if (strJumpTo == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strProcedureEndNodeID)
	{
		pNode = g_pPpEndNode;
	}
	else if (strJumpTo.GetLength() == 0)
	{
		pNode = pJumpTo;
	}
	else
	{
		CPpProcedure *pProcedure = (CPpProcedure*)pJumpDef->GetAncestor(PPCLASSID_PPPROCEDURE);
		ASSERT (pProcedure != NULL);

		if (pProcedure != NULL)
		{
			pNode = pProcedure->FindNodeByID(strJumpTo);
		}
	}

	return pNode;
}

CPpTimers* CPpNode::GetTimers()
{
	if (m_pTimers == NULL)
	{
		m_pTimers = new CPpTimers();
		AddTail(m_pTimers);
		m_pTimers->SetParent(this);
	}

	return m_pTimers;
}
CPpJumps* CPpNode::GetJumps()
{
	if (m_pJumps == NULL)
	{
		m_pJumps = new CPpJumps();
		AddTail(m_pJumps);
		m_pJumps->SetParent(this);
	}

	return m_pJumps;
}

CPpNodes* CPpNode::GetReponseNodes()
{
	if (m_pResponseNodes == NULL)
	{
		m_pResponseNodes = new CPpNodes(PPNODE_TYPE_RESPONSE);
		AddTail(m_pResponseNodes);
		m_pResponseNodes->SetParent(this);
	}

	return m_pResponseNodes;
}
CPpNodes* CPpNode::GetProcessNodes()
{
	if (m_pProcessNodes == NULL)
	{
		m_pProcessNodes = new CPpNodes(PPNODE_TYPE_PROCESS);
		AddTail(m_pProcessNodes);
		m_pProcessNodes->SetParent(this);
	}

	return m_pProcessNodes;
}

CPpScript*  CPpNode::GetInitScript()
{
	if (m_pInitScript == NULL)
	{
#ifdef UNICODE
		m_pInitScript = new CPpScript(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strInitScriptKey);
#else
		m_pInitScript = new CPpScript(CString(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strInitScriptKey));
#endif
		AddTail(m_pInitScript);
		m_pInitScript->SetParent(this);
	}

	return m_pInitScript;
}

CPpScript*  CPpNode::GetEndScript()
{
	if (m_pEndScript == NULL)
	{
#ifdef UNICODE
		m_pEndScript = new CPpScript(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strEndScriptKey);
#else
		m_pEndScript = new CPpScript(CString(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strEndScriptKey));
#endif
		AddTail(m_pEndScript);
		m_pEndScript->SetParent(this);
	}

	return m_pEndScript;
}

CPpPackageRef*  CPpNode::GetPackageRef()
{
	if (m_pPackageRef == NULL)
	{
		m_pPackageRef = new CPpPackageRef();
		AddTail(m_pPackageRef);
		m_pPackageRef->SetParent(this);
	}

	return m_pPackageRef;
}

CPpPackageRefs*  CPpNode::GetPackageRefs()
{
	if (m_pPackageRefs == NULL)
	{
		m_pPackageRefs = new CPpPackageRefs();
		AddTail(m_pPackageRefs);
		m_pPackageRefs->SetParent(this);
	}

	return m_pPackageRefs;
}

//设置当前节点的发送帧
void CPpNode::SetPackageSend(CExBaseObject *pPkgSend)
{
	CPpPackageSend *pCurr = (CPpPackageSend*)m_pPackageSend;
	
	if (pCurr != NULL)
	{
		pCurr->Lock(FALSE);
	}

	m_pPackageSend = pPkgSend;

	if (m_pPackageSend != NULL)
	{
		pCurr = (CPpPackageSend*)m_pPackageSend;
		pCurr->Lock();
	}
}

void CPpNode::GetPackageVariables(CExBaseList &oVariables)
{
	if (m_pPackageRef == NULL)
	{
		return;
	}

	CPpPackage *pPackage =  PpFindPackageByID(m_pPackageRef->m_strPkgID, this);

	if (pPackage == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
               , g_sLangTxt_PrcsFrameUnExist.GetString()/*L"过程节点[%s]关联的帧[%s]不存在"*/
               , m_strID.GetString(), m_pPackageRef->m_strPkgID.GetString());
		return;
	}

	pPackage->GetPackageVaraibles(oVariables, FALSE);
}


void CPpNode::RunInitScript(CExBaseObject *pPkg)
{
	if (m_pPackageRef != NULL)
	{
		CPpPackage *pPackage =  PpFindPackageByID(m_pPackageRef->m_strPkgID, this);
		
		if (pPackage != NULL)
		{
			pPackage->RunInitScript();
		}
	}

	RunNodeScript(m_pInitScript, pPkg);
}

void CPpNode::RunEndScript(CExBaseObject *pPkg)
{
	if (m_pPackageRef != NULL)
	{
		CPpPackage *pPackage =  PpFindPackageByID(m_pPackageRef->m_strPkgID, this);

		if (pPkg != NULL)
		{
			pPackage->RunEndScript();
		}
	}

	RunNodeScript(m_pEndScript, pPkg);
}

void CPpNode::RunNodeScript(CPpScript *pScript, CExBaseObject *pPkg)
{
	if (pScript == NULL)
	{
		return;
	}

	if (pScript->m_strScript.GetLength() == 0)
	{
		return;
	}

#ifdef _LUA_IN_DEVBASEAPP_
	CString strVariables;
	CPpProcedure *pProcedure = (CPpProcedure*)GetAncestor(PPCLASSID_PPPROCEDURE);
	CBbVariables oAllVariables(_T("variables"));  //能够使用的全部变量
	CBbVariables oWVariables(_T("variables"));  //过程的变量，能够保存数据的变量
	CPpPackage *pPackage = (CPpPackage*)pPkg;

	//获取过程的变量
	if (pProcedure == NULL)
	{
		return;
	}

	if (pProcedure->m_pVariables != NULL)
	{
		pProcedure->m_pVariables->Append(oAllVariables);
		pProcedure->m_pVariables->Append(oWVariables);
	}

	if (pProcedure->m_pDataInterface != NULL)
	{
		pProcedure->m_pDataInterface->Append(oAllVariables);
	}

	if (pPackage != NULL)
	{
		pPackage->GetPackageVaraibles(oAllVariables, FALSE);
	}

	oAllVariables.GetVariablesString(strVariables);
	pScript->Run(/*strVariables, &oWVariables*/);
	oAllVariables.RemoveAll();
	oWVariables.RemoveAll();
#else
	pScript->Run(/*_T(""), NULL*/);
#endif
}

