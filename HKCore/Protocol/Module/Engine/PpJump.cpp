#include "StdAfx.h"
#include "PpJump.h"
#include "PpProcedure.h"
#include "../XLanguageResourcePp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPpJump::CPpJump(const CString &strJumpType)
{
	m_pJumpScript = NULL;
	m_pJumpToNode = NULL;
	m_strJumpTo = CProtocolXmlRWKeys::g_pXmlRWKeys->m_strProcedureEndNodeID;
}

CPpJump::CPpJump(void)
{
	m_pJumpScript = NULL;
	m_pJumpToNode = NULL;
	m_strJumpTo = CProtocolXmlRWKeys::g_pXmlRWKeys->m_strProcedureEndNodeID;
}

CPpJump::~CPpJump(void)
{
}

long CPpJump::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CProtocolXmlRWKeys *pKey = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pKey->m_strJumpToKey, oNode, m_strJumpTo);

	return 0;
}

long CPpJump::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CProtocolXmlRWKeys *pKey = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pKey->m_strJumpToKey, oElement, m_strJumpTo);

	return 0;
}

long CPpJump::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CPpJump::IsEqualOwn(CBaseObject* pObj)
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

	if (m_strJumpTo != ((CPpJump*)pObj)->m_strJumpTo)
	{
		return FALSE;
	}

	return CExBaseObject::IsEqualOwn(pObj);
}

CBaseObject* CPpJump::Clone()
{
	CPpJump* pNew = new CPpJump();
	Copy(pNew);
	return pNew;
}

BOOL CPpJump::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CPpJump*)pDest)->m_strJumpTo = m_strJumpTo;

	return CExBaseObject::CopyOwn(pDest);
}

CExBaseObject* CPpJump::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPpNodeKey)
	{
		return new CPpNode(PPNODE_TYPE_PRODUCE);
	}

	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strScriptKey)
	{
#ifdef UNICODE
		return new CPpScript(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strScriptKey);
#else
		return new CPpScript(CString(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strScriptKey));
#endif
	}

	return NULL;
}

CExBaseObject* CPpJump::CreateNewChild(long nClassID)
{
	if (nClassID == PPCLASSID_PPNODE)
	{
		return new CPpNode(PPNODE_TYPE_PRODUCE);
	}

	if (nClassID == PPCLASSID_PPSCRIPT)
	{
#ifdef UNICODE
		return new CPpScript(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strScriptKey);
#else
		return new CPpScript(CString(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strScriptKey));
#endif
	}

	return NULL;
}
void CPpJump::InitAfterRead()
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
		case PPCLASSID_PPNODE:
			{
				m_pJumpToNode = (CPpNode*)p;
			}
			break;
		case PPCLASSID_PPSCRIPT:
			{
				m_pJumpScript = (CPpScript*)p;
			}
			break;

		default:
			break;
		}
	}
}

CPpNode* CPpJump::RunJump(CPpPackageDetail *pPkgDetail)
{
	ASSERT (m_pJumpScript != NULL);

	//如果没有定义脚本，有两种处理方式
	//第一种：处理为跳转；第二种，不做任何处理
	//暂时不做任何处理
	if (m_pJumpScript == NULL)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                                   , g_sLangTxt_UnDefinScript.GetString()/*L"跳转节点\"%s\"没有定义脚本"*/
                                   , m_strName.GetString());
		return NULL;
	}
	
	CPpNode *pJumpTo = NULL;
	CString strVariables;
	CPpProcedure *pProcedure = (CPpProcedure*)GetAncestor(PPCLASSID_PPPROCEDURE);
	CBbVariables *pVariables = NULL;

#ifdef _LUA_IN_DEVBASEAPP_
	//获取关联的Packagedetail的变量
	if (pPkgDetail != NULL)
	{
		pPkgDetail->GetVariablesString(strVariables);
	}

	//获取过程的变量
	if (pProcedure != NULL)
	{
		pVariables = pProcedure->m_pVariables;
	}

	if (pVariables != NULL)
	{
		pVariables->GetVariablesString(strVariables);
	}

	//执行脚本：传入桢变量数据和过程变量数据，返回并记录过程用到的变量
	m_pJumpScript->Run(/*strVariables, pVariables*/);
#else
	m_pJumpScript->Run(/*_T(""), NULL*/);
#endif

	if (m_pJumpScript->HasReturn())
	{
		if (m_pJumpScript->IsReturnValueTrue())
		{//返回TRUE，执行节点跳转
			pJumpTo = PpGetJumpToNode(m_strJumpTo, m_pJumpToNode, this);

			if (pJumpTo != NULL)
			{
				//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"[%s]跳转到节点\"%s\"", m_strID, pJumpTo->m_strID);
			}
			else
			{
                CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                                           , g_sLangTxt_NoJumpNode.GetString()/*L"[%s]无跳转节点"*/
                                           , m_strID.GetString());
			}
		}
		else
		{
		}
	}
	else
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                                   , g_sLangTxt_JumpNodeNoValue.GetString()/*L"跳转节点\"%s\"脚本【%s】没有返回值，使用\"return\"返回"*/
                                   , m_strName.GetString(), m_pJumpScript->m_pszFuncName);
	}

	return pJumpTo;
}

