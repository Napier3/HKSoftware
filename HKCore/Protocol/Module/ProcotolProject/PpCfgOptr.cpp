//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PpCfgOptr.cpp  CPpCfgOptr


#include "stdafx.h"
#include "PpCfgOptr.h"
#include "../Engine/ProtocolXmlRWKeys.h"

CPpCfgOptr::CPpCfgOptr()
{
	//初始化属性
	m_nTDelay = 0;
	m_pPpCfgOptrBatch = NULL;
	m_pPpScript = NULL;

	//初始化成员变量
	m_nIsRunning = 0;
}

CPpCfgOptr::~CPpCfgOptr()
{
}

long CPpCfgOptr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CClassProcotolProjectXmlRWKeys *pXmlKeys = (CClassProcotolProjectXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTDelayKey, oNode, m_nTDelay);
	xml_GetAttibuteValue(pXmlKeys->m_strRunProcedureKey, oNode, m_strRunProcedure);
	xml_GetAttibuteValue(pXmlKeys->m_strPachageIDKey, oNode, m_strPachageID);
	xml_GetAttibuteValue(pXmlKeys->m_strIsRunningKey, oNode, m_nIsRunning);
	
	return 0;
}

long CPpCfgOptr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CClassProcotolProjectXmlRWKeys *pXmlKeys = (CClassProcotolProjectXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTDelayKey, oElement, m_nTDelay);
	xml_SetAttributeValue(pXmlKeys->m_strRunProcedureKey, oElement, m_strRunProcedure);
	xml_SetAttributeValue(pXmlKeys->m_strPachageIDKey, oElement, m_strPachageID);
	xml_SetAttributeValue(pXmlKeys->m_strIsRunningKey, oElement, m_nIsRunning);
	return 0;
}

long CPpCfgOptr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nTDelay);
		BinarySerializeCalLen(oBinaryBuffer, m_strRunProcedure);
		BinarySerializeCalLen(oBinaryBuffer, m_strPachageID);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nTDelay);
		BinarySerializeRead(oBinaryBuffer, m_strRunProcedure);
		BinarySerializeRead(oBinaryBuffer, m_strPachageID);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nTDelay);
		BinarySerializeWrite(oBinaryBuffer, m_strRunProcedure);
		BinarySerializeWrite(oBinaryBuffer, m_strPachageID);
	}
	return 0;
}

void CPpCfgOptr::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == POCLASSID_CPPCFGOPTRBATCH)
		{
			m_pPpCfgOptrBatch = (CPpCfgOptrBatch*)p;
		}
		else if (nClassID == PPCLASSID_PPSCRIPT)
		{
			m_pPpScript = (CPpScript*)p;
		}
	
	}

	if (m_pPpCfgOptrBatch == NULL)
	{
		m_pPpCfgOptrBatch = (CPpCfgOptrBatch*)AddNewChild(new CPpCfgOptrBatch());
	}

	if (m_pPpScript == NULL)
	{
#ifdef UNICODE
		m_pPpScript = (CPpScript*)AddNewChild(new CPpScript(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strScriptKey));
#else
		m_pPpScript = (CPpScript*)AddNewChild(new CPpScript(CString(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strScriptKey)));
#endif
	}

}

BOOL CPpCfgOptr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPpCfgOptr *p = (CPpCfgOptr*)pObj;

	if(m_nTDelay != p->m_nTDelay)
	{
		return FALSE;
	}

	if(m_strRunProcedure != p->m_strRunProcedure)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPpCfgOptr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CPpCfgOptr *p = (CPpCfgOptr*)pDest;

	p->m_nTDelay = m_nTDelay;
	p->m_strRunProcedure = m_strRunProcedure;
	p->m_strPachageID = m_strPachageID;
	p->m_nIsRunning = m_nIsRunning;

	return TRUE;
}

CBaseObject* CPpCfgOptr::Clone()
{
	CPpCfgOptr *p = new CPpCfgOptr();
	Copy(p);
	return p;
}

long CPpCfgOptr::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("ID"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("TDelay"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->InsertColumn(4, _T("RunProcedure"));
	pListCtrl->SetColumnWidth(4, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPpCfgOptr::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
	strTemp.Format(_T("%d"), m_nTDelay);
	pListCtrl->SetItemText(lItemIndex, 3, strTemp);
	pListCtrl->SetItemText(lItemIndex, 4, m_strRunProcedure);
    pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

BOOL CPpCfgOptr::CanPaste(UINT nClassID)
{
	if (nClassID == POCLASSID_CPPCFGOPTRBATCH)
	{
		return TRUE;
	}

	if (nClassID == POCLASSID_CPPCFGOPTRDEVICE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CPpCfgOptr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CClassProcotolProjectXmlRWKeys *pXmlKeys = (CClassProcotolProjectXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCPpCfgOptrBatchKey)
	{
		pNew = new CPpCfgOptrBatch();
	}
	else if (strClassID == pXmlKeys->m_strCPpCfgOptrDeviceKey)
	{
		pNew = new CPpCfgOptrDevice();
	}
	else if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strScriptKey)
	{
#ifdef UNICODE
		pNew = new CPpScript(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strScriptKey);
#else
		pNew = new CPpScript(CString(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strScriptKey));
#endif
	}

	return pNew;
}

CExBaseObject* CPpCfgOptr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == POCLASSID_CPPCFGOPTRBATCH)
	{
		pNew = new CPpCfgOptrBatch();
	}
	else if (nClassID == POCLASSID_CPPCFGOPTRDEVICE)
	{
		pNew = new CPpCfgOptrDevice();
	}

	return pNew;
}

CPpScript* CPpCfgOptr::GetPpScript()
{
	if (m_pPpScript == NULL)
	{
#ifdef UNICODE
		m_pPpScript = new CPpScript(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strScriptKey);
#else
		m_pPpScript = new CPpScript(CString(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strScriptKey) );
#endif
		AddNewChild(m_pPpScript);
	}

	return m_pPpScript;
}

void CPpCfgOptr::SerializeTrigerScript(long &nScriptIndex, CExBaseList &listTrigerScript, const CString &strID)
{
	CExBaseObject *pFind = FindByID(strID);

	if (pFind != NULL)
	{
		if (m_pPpScript->m_strScript.GetLength() > 6)
		{
			g_oPpXvmScriptBuilder.xvm_script_SerializeScript(m_pPpScript, nScriptIndex);
			listTrigerScript.AddTail(this);
		}
	}
}

BOOL CPpCfgOptr::CanRun()
{
	if (m_nIsRunning == 0)
	{
		return FALSE;
	}

	if (m_oTickCount32.GetTickCountLong(FALSE) >= m_nTDelay)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CPpCfgOptr::EnterRun()
{
	m_oTickCount32.Enter();
}

