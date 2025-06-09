//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PpCfgOptrs.cpp  CPpCfgOptrs


#include "stdafx.h"
#include "PpCfgOptrs.h"

CPpCfgOptrs::CPpCfgOptrs()
{
	//初始化属性

	//初始化成员变量
}

CPpCfgOptrs::~CPpCfgOptrs()
{
}

long CPpCfgOptrs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CClassProcotolProjectXmlRWKeys *pXmlKeys = (CClassProcotolProjectXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strProcedureKey, oNode, m_strProcedure);

	return 0;
}

long CPpCfgOptrs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CClassProcotolProjectXmlRWKeys *pXmlKeys = (CClassProcotolProjectXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strProcedureKey, oElement, m_strProcedure);

	return 0;
}

long CPpCfgOptrs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strProcedure);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strProcedure);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strProcedure);
	}
	return 0;
}

void CPpCfgOptrs::InitAfterRead()
{
}

BOOL CPpCfgOptrs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPpCfgOptrs *p = (CPpCfgOptrs*)pObj;

	if(m_strProcedure != p->m_strProcedure)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPpCfgOptrs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CPpCfgOptrs *p = (CPpCfgOptrs*)pDest;

	p->m_strProcedure = m_strProcedure;

	return TRUE;
}

CBaseObject* CPpCfgOptrs::Clone()
{
	CPpCfgOptrs *p = new CPpCfgOptrs();
	Copy(p);
	return p;
}

long CPpCfgOptrs::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("ID"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPpCfgOptrs::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
	pListCtrl->SetItemText(lItemIndex, 3, m_strProcedure);
    pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

BOOL CPpCfgOptrs::CanPaste(UINT nClassID)
{
	if (nClassID == POCLASSID_CPPCFGOPTR)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CPpCfgOptrs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CClassProcotolProjectXmlRWKeys *pXmlKeys = (CClassProcotolProjectXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCPpCfgOptrKey)
	{
		pNew = new CPpCfgOptr();
	}

	return pNew;
}

CExBaseObject* CPpCfgOptrs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == POCLASSID_CPPCFGOPTR)
	{
		pNew = new CPpCfgOptr();
	}

	return pNew;
}

void CPpCfgOptrs::SerializeTrigerScript(long &nScriptIndex, CExBaseList &listTrigerScript, const CString &strID)
{
	CPpCfgOptr *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CPpCfgOptr *)GetNext(pos);
		p->SerializeTrigerScript(nScriptIndex, listTrigerScript, strID);
	}
}

