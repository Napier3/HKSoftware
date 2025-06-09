#include "StdAfx.h"
#include "PpProcedure.h"
#include "PpDataInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPpProcedure::CPpProcedure(void)
{
	m_pPackageRef = NULL;
	m_pDataInterface = NULL;
	m_pVariables = NULL;
	m_pInitScript = NULL;
	m_pEndScript = NULL;

	m_nPriority = 0;
	m_nExclusive = 0;         //独占状态属性
	m_nReleaseT = 5000;          //多长时间取消独占一次,暂时不用
	m_dwRunState = PP_PROCEDURE_RUN_STATE_NOMAL;
	m_bValid = TRUE;
}

CPpProcedure::~CPpProcedure(void)
{
	m_oAllVariables.RemoveAll();
	//m_listPackageRefs.RemoveAll();
}


long CPpProcedure::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CProtocolXmlRWKeys *pKey = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pKey->m_strUseCmmChannelKey, oNode, m_strChannelID);
	xml_GetAttibuteValue(pKey->m_strPriorityKey, oNode, m_nPriority);
	xml_GetAttibuteValue(pKey->m_strChCmmModeKey, oNode, m_strChCmmMode);
	xml_GetAttibuteValue(pKey->m_strExclusiveKey, oNode, m_nExclusive);
	xml_GetAttibuteValue(pKey->m_strReleaseTKey, oNode, m_nReleaseT);

	return 0;
}

long CPpProcedure::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CProtocolXmlRWKeys *pKey = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pKey->m_strUseCmmChannelKey, oElement, m_strChannelID);
	xml_SetAttributeValue(pKey->m_strPriorityKey, oElement, m_nPriority);
	xml_SetAttributeValue(pKey->m_strChCmmModeKey, oElement, m_strChCmmMode);

	xml_SetAttributeValue(pKey->m_strExclusiveKey, oElement, m_nExclusive);
	xml_SetAttributeValue(pKey->m_strReleaseTKey, oElement, m_nReleaseT);
	return 0;
}

long CPpProcedure::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}


CExBaseObject* CPpProcedure::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPpNodeKey)
	{
		return new CPpNode(PPNODE_TYPE_PRODUCE);
	}

	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strVariablesKey)
	{
#ifdef UNICODE
		return new CBbVariables(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strVariablesKey);
#else
		return new CBbVariables(CString(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strVariablesKey));
#endif
	}

	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataInterfaceKey)
	{
#ifdef UNICODE
		return new CBbVariables(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataInterfaceKey);
#else
		return new CBbVariables(CString(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataInterfaceKey));
#endif
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

CExBaseObject* CPpProcedure::CreateNewChild(long nClassID)
{
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CPpProcedure::IsEqualOwn(CBaseObject* pObj)
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

	return CExBaseList::IsEqualOwn(pObj);
}

CBaseObject* CPpProcedure::Clone()
{
	CPpProcedure* pNew = new CPpProcedure();
	Copy(pNew);
	return pNew;
}

BOOL CPpProcedure::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CPpProcedure*)pDest)->m_strChannelID = m_strChannelID;       //过程使用的通讯通道ID
	((CPpProcedure*)pDest)->m_strChCmmMode = m_strChCmmMode;
	((CPpProcedure*)pDest)->m_nPriority = m_nPriority;          //优先级
	((CPpProcedure*)pDest)->m_nReleaseT = m_nReleaseT;
	((CPpProcedure*)pDest)->m_nExclusive = m_nExclusive;          //优先级

	return CExBaseList::CopyOwn(pDest);
}

void CPpProcedure::InitAfterRead()
{
	//初始化m_pDataInterface等子对象指针
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject*)GetNext(pos);

		UINT nClassID = p->GetClassID();

		switch (nClassID)
		{
		case PPCLASSID_BBVARIABLES:
			{
				CBbVariables *pVariables = (CBbVariables*)p;

				if (pVariables->m_strXmlKey == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strVariablesKey)
				{
					m_pVariables = pVariables;
				}
				else if (pVariables->m_strXmlKey == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataInterfaceKey)
				{
					m_pDataInterface = pVariables;
				}
				else
				{

				}
			}
 
			break;
		case PPCLASSID_PPSCRIPT:
			{
				CPpScript *pScript = (CPpScript*)p;

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
	/*	case PPCLASSID_PPNODE:
			{
				m_p
			}
			break;*/

		default:
			break;
		}
	}

	//InitPackageRefs();
}

//读取结束后保存临时的所有PackageRef变量
void CPpProcedure::InitPackageRefs()
{
// 	POS pos = GetHeadPosition();
// 	CExBaseObject* pObj = NULL;
// 	CExBaseObject* pSrcObj = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pObj = GetNext(pos);
// 		if (pObj->GetClassID() == PPCLASSID_PPNODE)
// 		{
// 			if (((CPpNode*)pObj)->m_pPackageRef != NULL)
// 			{
// 				if (FindPackageRefByPkID(((CPpNode*)pObj)->m_pPackageRef->m_strPkgID) == NULL)
// 				{
// 					CPpPackageRef* pRef = new CPpPackageRef;
// 					pRef->m_strPkgID = ((CPpNode*)pObj)->m_pPackageRef->m_strPkgID;
// 					POS SrPos = ((CPpNode*)pObj)->m_pPackageRef->GetHeadPosition();
// 
// 					while(SrPos != NULL)
// 					{
// 						pSrcObj = ((CPpNode*)pObj)->m_pPackageRef->GetNext(SrPos);
// 						CPpDataInterface* pDestData = new CPpDataInterface;
// 						pDestData->m_strID = ((CPpDataInterface*)pSrcObj)->m_strID;
// 						pDestData->m_strPackageDataID = ((CPpDataInterface*)pSrcObj)->m_strPackageDataID;
// 						pDestData->m_strProcedureDataID = ((CPpDataInterface*)pSrcObj)->m_strProcedureDataID;
// 						pRef->AddTail(pDestData);
// 						pDestData->SetParent(pRef);
// 					}
// 					m_listPackageRefs.AddTail(pRef);
// 				}
// 			}
// 		}
// 	}
}

CExBaseObject* CPpProcedure::FindPackageRefByPkID(CString strPkgID)
{
	POS pos = m_listPackageRefs.GetHeadPosition();
	CExBaseObject* pObj = NULL;
	BOOL bFind = FALSE;

	while (pos != NULL&&!bFind)
	{
		pObj = m_listPackageRefs.GetNext(pos);
		if (((CPpPackageRef*)pObj)->m_strPkgID == strPkgID)
		{
			bFind = TRUE;
		}
	}

	if (bFind)
	{
		return pObj;
	}
	else
	{
		return NULL;
	}
}

CPpNode* CPpProcedure::FindNodeByID(CString strID)
{
	CExBaseObject* pFind = NULL;
	CExBaseList oList;
	InsertNodesIntoList(&oList);
	pFind = oList.FindByID(strID);
	oList.RemoveAll();

	return (CPpNode*)pFind;
}

CPpNode* CPpProcedure::FindNodeByName(CString strName)
{
	CExBaseObject* pFind = NULL;
	CExBaseList oList;
	InsertNodesIntoList(&oList);
	pFind = oList.FindByName(strName);
	oList.RemoveAll();

	return (CPpNode*)pFind;
}


void CPpProcedure::InsertNodesIntoList(CExBaseList* pList)
{
	InsertNodesIntoList(this,pList);
}
void CPpProcedure::InsertNodesIntoList(CExBaseList* pRcList,CExBaseList* pList)
{
	CExBaseObject* pObj = NULL;
	POS pos = pRcList->GetHeadPosition();

	while (pos != NULL)
	{
		pObj = pRcList->GetNext(pos);
		if (pObj->GetClassID() == PPCLASSID_PPNODE)
		{
			pList->AddTail(pObj);
			
		}
		if (pObj->IsBaseList())
		{
			InsertNodesIntoList((CExBaseList*)pObj,pList);
		}
	}
}

void CPpProcedure::LogProcedureRunInfor()
{
	CString strLog;
	CString strTemp;

	POS pos = m_pDataInterface->GetHeadPosition();
    strLog.Format(_T("RunProcedure(%s):"), m_strID.GetString());

	while (pos != NULL)
	{
		CBbVariable *pVariable = (CBbVariable*)m_pDataInterface->GetNext(pos);
        strTemp.Format(_T(" [%s=%s]"), pVariable->m_strID.GetString(), pVariable->m_strValue.GetString());
		strLog += strTemp;
	}

	CLogPrint::LogString(XLOGLEVEL_TRACE, strLog);
}

CPpNode* CPpProcedure::GetRootNode()
{
	CExBaseObject* p = NULL;
	POS pos = GetHeadPosition();
	CPpNode *pNode = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
	
		if (p->GetClassID() == PPCLASSID_PPNODE)
		{
			pNode = (CPpNode*)p;
			break;
		}
	}

	return pNode;
}

void CPpProcedure::RunInitScript()
{
#ifdef _LUA_IN_DEVBASEAPP_
	CBbVariables oWVariables(_T("variables"));  //过程的变量，能够保存数据的变量
	if (m_pVariables != NULL)
	{
		m_pVariables->Append(oWVariables);
	}

	if (m_pDataInterface != NULL)
	{
		m_pDataInterface->Append(oWVariables);
	}

	RunScript(m_pInitScript, &oWVariables);
	oWVariables.RemoveAll();
#else
	RunScript(m_pInitScript, NULL);
#endif
}

CBbVariable* CPpProcedure::FindVariableByID(const CString &strID)
{
	CBbVariable *pFind = NULL;//(CBbVariable*)m_oAllVariables.FindByID(strID);

	if (m_pVariables != NULL)
	{
		pFind = (CBbVariable*)m_pVariables->FindByID(strID);
	}

	if (pFind == NULL)
	{
		if (m_pDataInterface != NULL)
		{
			pFind = (CBbVariable*)m_pDataInterface->FindByID(strID);
		}
	}

	if (pFind == NULL)
	{
		if (m_pPackageRef != NULL)
		{
			CPpPackage *pPackage = (CPpPackage*)m_pPackageRef;
			pFind = pPackage->FindVariableByID(strID);
		}
	}

	return pFind;
}

void CPpProcedure::RunEndScript()
{
#ifdef _LUA_IN_DEVBASEAPP_
	CBbVariables oWVariables(_T("variables"));  //过程的变量，能够保存数据的变量
	if (m_pVariables != NULL)
	{
		m_pVariables->Append(oWVariables);
	}

	if (m_pDataInterface != NULL)
	{
		m_pDataInterface->Append(oWVariables);
	}

	RunScript(m_pEndScript, &oWVariables);

	oWVariables.RemoveAll();
#else
	RunScript(m_pEndScript, NULL);
#endif
}

void CPpProcedure::RunScript(CPpScript *pScript, CBbVariables *pVariables)
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
	CBbVariables oAllVariables(_T("variables"));  //能够使用的全部变量
	//CBbVariables oWVariables(_T("variables"));  //过程的变量，能够保存数据的变量

	if (m_pVariables != NULL)
	{
		m_pVariables->Append(oAllVariables);
		//m_pVariables->Append(oWVariables);
	}

	if (m_pDataInterface != NULL)
	{
		m_pDataInterface->Append(oAllVariables);
	}

	oAllVariables.GetVariablesString(strVariables);
	pScript->Run(/*strVariables, pVariables*/);//&oWVariables);
	oAllVariables.RemoveAll();
	//oWVariables.RemoveAll();
#else
	pScript->Run(/*_T(""), NULL*/);//&oWVariables);
#endif
}

void CPpProcedure::SetDataInterface(long nIndex,long nValue)
{
	CBbVariables *pVariables = m_pDataInterface;
	CBbVariable *pVariable = NULL;

	POS pos = pVariables->GetHeadPosition();
	if (pos == NULL)
	{
		return;
	}
	pVariable = (CBbVariable *)pVariables->GetNext(pos);
	CString strValue;
	strValue.Format(_T("%d"),nIndex);
	pVariable->m_strValue = strValue;

	pVariable = (CBbVariable *)pVariables->GetAt(pos);
	strValue.Format(_T("%d"),nValue);
	pVariable->m_strValue = strValue;
}

