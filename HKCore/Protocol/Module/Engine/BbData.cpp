#include "StdAfx.h"
#include "BbData.h"
#include "PpPackage.h"
#include "PpTemplate.h"
#include "../XLanguageResourcePp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CBbData::CBbData(void)
{
	m_pVariables = new CBbVariables(_T(""));
	this->AddTail(m_pVariables);
	m_pVariables->SetParent(this);

	m_pDataByteBlock = NULL;
	m_pDataBinds = NULL;
	//m_strMaxCount = 0;
}

CBbData::~CBbData(void)
{
	//delete m_pVariables;
}

long CBbData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CProtocolXmlRWKeys *pKeys = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pKeys->m_strMaxKey, oNode,m_strMaxCount);

	return 0;
}

long CBbData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	CProtocolXmlRWKeys *pKeys = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pKeys->m_strMaxKey, oElement,m_strMaxCount);

	return 0;
}

long CBbData::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{

	return 0;
}


CExBaseObject* CBbData::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataBindsKey)
	{//数据绑定
		//ASSERT (m_pDataBinds != NULL);
		m_pDataBinds = new CPpDataBinds();
		return m_pDataBinds;
	}

	return CByteBlocks::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
}

CExBaseObject* CBbData::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	
	return NULL;
}

void CBbData::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == PPCLASSID_BBVARIABLES)
		{
			m_pVariables = (CBbVariables *)p;
		}

		if (p->GetClassID() == PPCLASSID_PPDATABINDS)
		{
			m_pDataBinds = (CPpDataBinds*)p;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CBbData::IsEqualOwn(CBaseObject* pObj)
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

	return CByteBlocks::IsEqualOwn(pObj);
}

CBaseObject* CBbData::Clone()
{
	CBbData* pNew = new CBbData();
	Copy(pNew);
	return pNew;
}

BOOL CBbData::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CBbData*)pDest)->m_strMaxCount = m_strMaxCount;

	return CByteBlocks::CopyOwn(pDest);
}

long CBbData::GetBindItemIndex()
{
	CPpPackage *pPkg = (CPpPackage*)PpFindPackage(this);
	ASSERT (pPkg != NULL);

	CPpTemplate *pTemplate = (CPpTemplate*)GetAncestor(PPCLASSID_PPTEMPLATE);
	ASSERT (pTemplate != NULL);

	CExBaseList *pDevice = pTemplate->GetDevice();

	if (pDevice == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Init Query Bind Stack Error..."));
		return -1;
	}

	CPpDataBind *pBind = (CPpDataBind*)m_pDataBinds->GetTail();
	long nIndex = -1;

	if (pBind != NULL)
	{
		//$$  2-160414
		if (pBind->m_strDataType == g_strVariableDataTypeItemIndexID || pBind->m_strDataType == g_strVariableDataTypeGROUPID || pBind->m_strDataType == g_strVariableDataTypeCPUID)
		{
			CString strValue;
			pPkg->GetVariableValue(pBind->m_strDataAttrID, strValue);
			nIndex = CString_To_long(strValue);
		}
	}

	return nIndex;
}

void CBbData::InitQueryBindStack(void **ppDataQueryBindStatck)
{
	CPpPackage *pPkg = (CPpPackage*)PpFindPackage(this);
	ASSERT (pPkg != NULL);

	CPpTemplate *pTemplate = (CPpTemplate*)GetAncestor(PPCLASSID_PPTEMPLATE);
	ASSERT (pTemplate != NULL);

	CExBaseList *pDevice = pTemplate->GetDevice();

	if (pDevice == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Init Query Bind Stack Error..."));
		return;
	}

	CExBaseObject *pQueryData = NULL;
	CDataQueryBindStatck *pDataQueryBindStatck = pPkg->GetDataQueryBindStatck();
	*ppDataQueryBindStatck = pDataQueryBindStatck;
	pDataQueryBindStatck->m_pDevice = pDevice;
	pDataQueryBindStatck->SetBindCount(m_pDataBinds->GetDataBindCount());

	POS pos = m_pDataBinds->GetFirstDataBindPos();
	long nIndex = 0;
	CPpDataBind *pBind = NULL;
	CString strValue;

	pos = m_pDataBinds->GetFirstDataBindPos();

	while (pos != NULL)
	{
		pBind = m_pDataBinds->GetNextDataBind(pos);
		//pBind = m_pDataBinds->GetAtDataBind(pos);

		if (pBind == NULL)
		{
			break;
		}

		pPkg->GetVariableValue(pBind->m_strDataAttrID, strValue);
		pDataQueryBindStatck->SetBind(nIndex, pBind->m_strDataType, strValue);
		nIndex++;
	}

}

CExBaseObject* CBbData::QueryByBindStack(void **ppDataQueryBindStatck, BOOL bQueryDataNode)
{
	InitQueryBindStack(ppDataQueryBindStatck);
	CDataQueryBindStatck *pDataQueryBindStatck = (CDataQueryBindStatck*)(*ppDataQueryBindStatck);

	if (pDataQueryBindStatck == NULL)
	{
		return NULL;
	}

	CExBaseObject *pQueryData = (CDvmData*)pDataQueryBindStatck->Query(bQueryDataNode);
	*ppDataQueryBindStatck = pDataQueryBindStatck;

// 	if (g_bLogBindQueryErrorInfor)
// 	{
// 		if (pQueryData == NULL)
// 		{
// 			CString strLog;
// 			strLog.Format(L"Data[%s]绑定:", m_strName);
// 			pDataQueryBindStatck->LogString(strLog);
// 		}
// 	}

	return pQueryData;
}


CDvmData* CBbData::GetDeviceNodeDataByBind()
{
	CDvmData *pNodeData = NULL;
	CDataQueryBindStatck *pDataQueryBindStatck = NULL;

	pNodeData = (CDvmData*)QueryByBindStack((void**)(&pDataQueryBindStatck), FALSE);

	if (pNodeData == NULL)
	{
		pDataQueryBindStatck->LogString(g_sLangTxt_DataRltnshipError/*L"数据绑定关系错误："*/);
	}

	return pNodeData;
}

CExBaseObject* CBbData::QueryByBind(BOOL bQueryDataNode)
{
	CDataQueryBindStatck *pDataQueryBindStatck = NULL;
	CExBaseObject *pQueryData = NULL;
	
	pQueryData = QueryByBindStack((void**)(&pDataQueryBindStatck), bQueryDataNode);

	if (pDataQueryBindStatck != NULL)
	{
		pQueryData = pDataQueryBindStatck->GetDataQuery();
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("BbData::QueryByBind Error..."));
	}

	return pQueryData;
}

CExBaseObject* CBbData::BindItemIndex(long nItemIndex)
{
	CDataQueryBindStatck *pDataQueryBindStatck = NULL;
	CExBaseObject *pQueryData = NULL;

	pQueryData = QueryByBindStack((void**)(&pDataQueryBindStatck), FALSE);
	CDataQueryBind *pDataQueryBind = (CDataQueryBind*)pDataQueryBindStatck->GetTail();
	pDataQueryBind->m_strValue.Format(_T("%d"), nItemIndex);

	pQueryData = pDataQueryBindStatck->GetDataQuery();

	return pQueryData;
}

