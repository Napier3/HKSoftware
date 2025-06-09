//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmLog.cpp  CDvmLog


#include "stdafx.h"
#include "DvmLog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CDvmLog
CDvmLog::CDvmLog()
{
	//初始化属性
	m_dCurrTime = 0;
}

CDvmLog::~CDvmLog()
{
}

long CDvmLog::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTimeKey, oNode, m_dCurrTime);
	xml_GetAttibuteValue(pXmlKeys->m_strCLogCtrlKey, oNode, m_strLogCtrl);
	xml_GetAttibuteValue(pXmlKeys->m_strCDvmDatasetKey, oNode, m_strDataset);


	return 0;
}

long CDvmLog::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTimeKey, oElement, m_dCurrTime);
	xml_SetAttributeValue(pXmlKeys->m_strCLogCtrlKey, oElement, m_strLogCtrl);
	xml_SetAttributeValue(pXmlKeys->m_strCDvmDatasetKey, oElement, m_strDataset);

	return 0;
}

long CDvmLog::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_dCurrTime);
		BinarySerializeCalLen(oBinaryBuffer, m_strLogCtrl);
		BinarySerializeCalLen(oBinaryBuffer, m_strDataset);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_dCurrTime);
		BinarySerializeRead(oBinaryBuffer, m_strLogCtrl);
		BinarySerializeRead(oBinaryBuffer, m_strDataset);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_dCurrTime);
		BinarySerializeWrite(oBinaryBuffer, m_strLogCtrl);
		BinarySerializeWrite(oBinaryBuffer, m_strDataset);
	}

	return 0;
}

BOOL CDvmLog::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDvmLog *p = (CDvmLog*)pObj;

	if(m_dCurrTime != p->m_dCurrTime)
	{
		return FALSE;
	}

	if(m_strLogCtrl != p->m_strLogCtrl)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDvmLog::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDvmLog *p = (CDvmLog*)pDest;

	p->m_dCurrTime = m_dCurrTime;
	p->m_strLogCtrl = m_strLogCtrl;
	p->m_strDataset = m_strDataset;
	
	return TRUE;
}

CBaseObject* CDvmLog::Clone()
{
	CDvmLog *p = new CDvmLog();
	Copy(p);
	return p;
}
// 
// CExBaseObject* CDvmLog::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
// {
// 	CExBaseObject *pNew  = NULL;
// 	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;
// 
// 
// 	if (strClassID == pXmlKeys->m_strCDvmDataKey)
// 	{
// 		pNew = new CDvmData();
// 	}
// 
// 	return pNew;
// }
// 
// CExBaseObject* CDvmLog::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
// {
// 	CExBaseObject *pNew  = NULL;
// 
// 
// 	if (nClassID == DVMCLASSID_CDVMDATA)
// 	{
// 		pNew = new CDvmData();
// 	}
// 
// 	return pNew;
// }
// 
BOOL CDvmLog::CanPaste(UINT nClassID)
{
	if (nClassID == DVMCLASSID_CDVMDATA)
	{
		return TRUE;
	}

	return FALSE;
}


long CDvmLog::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strID);

	strTemp = dvm_GetTimeString(m_dCurrTime);
	pListCtrl->SetItemText(lItemIndex, 2, strTemp);

	pListCtrl->SetItemText(lItemIndex, 3, m_strDataset);
	//pListCtrl->SetItemText(lItemIndex, 3, m_strLogCtrl);

	pListCtrl->SetItemData(lItemIndex, (DWORD)this);

	return 1;
}


BOOL CDvmLog::GetValueByID(const CString &strValueID, CString &strValue)
{
	if (strValueID == CDataMngrXmlRWKeys::g_pXmlKeys->m_strNameKey)
	{
		strValue = m_strName;
		return TRUE;
	}

	if (strValueID == CDataMngrXmlRWKeys::g_pXmlKeys->m_strIDKey)
	{
		strValue = m_strID;
		return TRUE;
	}

	if (strValueID == CDataMngrXmlRWKeys::TimeKey())
	{
		strValue = dvm_GetTimeString(m_dCurrTime);
		return TRUE;
	}

	if (strValueID == CDataMngrXmlRWKeys::CLogCtrlKey())
	{
		strValue = m_strLogCtrl;
		return TRUE;
	}

	if (strValueID == CDataMngrXmlRWKeys::CDvmDatasetKey())
	{
		strValue = m_strLogCtrl;
		return TRUE;
	}

	strValue.Empty();

	return FALSE;
}