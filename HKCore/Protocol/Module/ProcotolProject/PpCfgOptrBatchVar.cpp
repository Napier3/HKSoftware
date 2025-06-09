//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PpCfgOptrBatchVar.cpp  CPpCfgOptrBatchVar


#include "stdafx.h"
#include "PpCfgOptrBatchVar.h"

CPpCfgOptrBatchVar::CPpCfgOptrBatchVar()
{
	//初始化属性
	m_fStepVal = 0;
	m_nStepCount = 0;

	//初始化成员变量
}

CPpCfgOptrBatchVar::~CPpCfgOptrBatchVar()
{
}

long CPpCfgOptrBatchVar::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CClassProcotolProjectXmlRWKeys *pXmlKeys = (CClassProcotolProjectXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strStepValKey, oNode, m_fStepVal);
	xml_GetAttibuteValue(pXmlKeys->m_strStepCountKey, oNode, m_nStepCount);
	return 0;
}

long CPpCfgOptrBatchVar::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CClassProcotolProjectXmlRWKeys *pXmlKeys = (CClassProcotolProjectXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strStepValKey, oElement, m_fStepVal);
	xml_SetAttributeValue(pXmlKeys->m_strStepCountKey, oElement, m_nStepCount);
	return 0;
}

long CPpCfgOptrBatchVar::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_fStepVal);
		BinarySerializeCalLen(oBinaryBuffer, m_nStepCount);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_fStepVal);
		BinarySerializeRead(oBinaryBuffer, m_nStepCount);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_fStepVal);
		BinarySerializeWrite(oBinaryBuffer, m_nStepCount);
	}
	return 0;
}

void CPpCfgOptrBatchVar::InitAfterRead()
{
}

BOOL CPpCfgOptrBatchVar::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPpCfgOptrBatchVar *p = (CPpCfgOptrBatchVar*)pObj;

	if(m_fStepVal != p->m_fStepVal)
	{
		return FALSE;
	}

	if(m_nStepCount != p->m_nStepCount)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPpCfgOptrBatchVar::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CPpCfgOptrBatchVar *p = (CPpCfgOptrBatchVar*)pDest;

	p->m_fStepVal = m_fStepVal;
	p->m_nStepCount = m_nStepCount;
	return TRUE;
}

CBaseObject* CPpCfgOptrBatchVar::Clone()
{
	CPpCfgOptrBatchVar *p = new CPpCfgOptrBatchVar();
	Copy(p);
	return p;
}

long CPpCfgOptrBatchVar::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("ID"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("StepVal"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->InsertColumn(4, _T("StepCount"));
	pListCtrl->SetColumnWidth(4, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPpCfgOptrBatchVar::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
	strTemp.Format(_T("%f"), m_fStepVal);
	pListCtrl->SetItemText(lItemIndex, 3, strTemp);
	strTemp.Format(_T("%d"), m_nStepCount);
	pListCtrl->SetItemText(lItemIndex, 4, strTemp);
    pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

