//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DsvElement.cpp  CDsvElement


#include "stdafx.h"
#include "DsvElement.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CDsvElement::CDsvElement()
{
	//初始化属性

	//初始化成员变量
}

CDsvElement::~CDsvElement()
{
}

long CDsvElement::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDsvBase::XmlReadOwn(oNode, pXmlRWKeys);
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strModeKey, oNode, m_strMode);
	return 0;
}

long CDsvElement::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDsvBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strModeKey, oElement, m_strMode);
	return 0;
}

long CDsvElement::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CDsvBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMode);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMode);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMode);
	}
	return 0;
}

void CDsvElement::InitAfterRead()
{
}

BOOL CDsvElement::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CDsvBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDsvElement *p = (CDsvElement*)pObj;

	if(m_strMode != p->m_strMode)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDsvElement::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDsvBase::CopyOwn(pDest);

	CDsvElement *p = (CDsvElement*)pDest;

	p->m_strMode = m_strMode;
	return TRUE;
}

CBaseObject* CDsvElement::Clone()
{
	CDsvElement *p = new CDsvElement();
	Copy(p);
	return p;
}


BOOL CDsvElement::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CDsvElement::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDsvElemAttrKey)
	{
		pNew = new CDsvElemAttr();
	}

	return pNew;
}

CExBaseObject* CDsvElement::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == DVMCLASSID_CDSVELEMATTR)
	{
		pNew = new CDsvElemAttr();
	}

	return pNew;
}


//////////////////////////////////////////////////////////////////////////
BOOL CDsvElement::IsAnyDsvObjectEx()
{
	if (GetCount() > 0)
	{
		return FALSE;
	}

	if (m_strMode.GetLength() > 0)
	{
		return FALSE;
	}

	if (m_strID.GetLength() > 0)
	{
		return FALSE;
	}

	m_bDsvSucc = TRUE;

	return TRUE;
}

BOOL CDsvElement::IsAnyDsvObject()
{
	return FALSE;
}

BOOL CDsvElement::DsValidate(CDvmDataset *pDataset, POS &posDataset, CValues *pRptValues, CDsvBase *pPrevAnlyDsvObj)
{
	m_listDsvMatch.RemoveAll();

	if (posDataset == NULL)
	{
		if (m_nMinOcc == 0)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	CDvmData *pData = NULL;
	long nCount = 0;

	while (posDataset != NULL)
	{
		pData = (CDvmData *)pDataset->GetAt(posDataset);

		//对当前element进行匹配
		if (ValidateData(pData, pRptValues))
		{
			m_listDsvMatch.AddTail(pData);
			nCount++;
			pDataset->GetNext(posDataset);
		}
		else
		{
			if (pPrevAnlyDsvObj == NULL)
			{
				//如果element之前的对象不是anly对象
				//则结束element的匹配
				break;
			}
			else
			{
				if (nCount > 0)
				{
					//element之前的对象是anly对象，当前element有匹配成功对象
					//则结束element的匹配
					break;
				}
				else
				{
					//element之前的对象是anly对象，并且当前element还没有任何匹配对象
					//则跳过当前的data对象
					//pPrevAnlyDsvObj->m_listDsvMatch.AddTail(pData);
					pDataset->GetNext(posDataset);
				}
			}
		}
	}

	if (m_nMinOcc <= nCount && nCount <= m_nMaxOcc)
	{
		m_bDsvSucc = TRUE;
	}
	else
	{
		m_bDsvSucc = FALSE;
	}

	return m_bDsvSucc;
}


BOOL CDsvElement::DsvQuery(CDvmDataset *pDataset, CValues *pRptValues)
{
	m_listDsvMatch.RemoveAll();
	POS posDataset = pDataset->GetHeadPosition();

	if (posDataset == NULL)
	{
		if (m_nMinOcc == 0)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	CDvmData *pData = NULL;
	long nCount = 0;

	while (posDataset != NULL)
	{
		pData = (CDvmData *)pDataset->GetNext(posDataset);

#ifndef exbase_not_use_m_dwReserved
		if (pDataset->m_dwReserved == 1)
#else
		if (pDataset->m_dwItemData == 1)
#endif
		{
			continue;
		}

		//对当前element进行匹配
		if (ValidateData(pData, pRptValues))
		{
			m_listDsvMatch.AddTail(pData);
			nCount++;
		}
	}

	if (m_nMinOcc <= nCount && nCount <= m_nMaxOcc)
	{
		m_bDsvSucc = TRUE;
	}
	else
	{
		m_bDsvSucc = FALSE;
	}

	return m_bDsvSucc;
}

BOOL CDsvElement::IsValidateSucc()
{
	BOOL bSucc = TRUE;

	if (!IsAnyDsvObject())
	{
		if (!m_bDsvSucc)
		{
			bSucc = FALSE;
		}
	}

	return bSucc;
}


BOOL CDsvElement::ValidateData(CDvmData *pDvmData, CValues *pRptValues)
{
	if (GetCount() == 0)
	{
		return (pDvmData->m_strName == m_strMode);
	}

	POS pos = GetHeadPosition();
	CDsvElemAttr *pAttr = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pAttr = (CDsvElemAttr *)GetNext(pos);

		if (!pAttr->ValidateData(pDvmData))
		{
			bTrue = FALSE;
			break;
		}
	}

	if (bTrue)
	{
		pos = GetHeadPosition();

		while (pos != NULL)
		{
			pAttr = (CDsvElemAttr *)GetNext(pos);
			pAttr->SetValuesByData(pDvmData, pRptValues);
		}
	}

	return bTrue;
}

CDsvElemAttr* CDsvElement::AddAttr(const CString &strName, const CString &strID, const CString &strDataType, const CString &strOptr, const CString &strValue, const CString &strValue2)
{
	CDsvElemAttr *pNew = new CDsvElemAttr();
	AddNewChild(pNew);

	pNew->m_strName = strName;
	pNew->m_strID = strID;
	pNew->SetOptr(strOptr);
	pNew->SetDataType(strDataType);
	pNew->m_strValue = strValue;
	pNew->m_strValue2 = strValue2;

	return pNew;
}

CDsvElemAttr* CDsvElement::AddAttr()
{
	CDsvElemAttr *pNew = new CDsvElemAttr();
	AddNewChild(pNew);

	return pNew;
}

CString CDsvElement::GetValueAttr()
{
	CDsvElemAttr *pFind = (CDsvElemAttr*)FindByID(g_strDataAttrID_Value);

	if (pFind != NULL)
	{
		return pFind->m_strValue;
	}
	else
	{
		return _T("");
	}
}

void CDsvElement::GetNameAndValueText(CString &strText, BOOL bAddValue)
{
	if (bAddValue)
	{
		CString strValue = GetValueAttr();

		if (strValue.GetLength() == 0)
		{
            strText.AppendFormat(_T("%s\r\n"), m_strName.GetString());
		}
		else
		{
            strText.AppendFormat(_T("%s(%s)\r\n"), m_strName.GetString(), strValue.GetString());
		}
	}
	else
	{
        strText.AppendFormat(_T("%s\r\n"), m_strName.GetString());
	}
}


//////////////////////////////////////////////////////////////////////////
//
CDsvAnyElement::CDsvAnyElement()
{

}

CDsvAnyElement::~CDsvAnyElement()
{

}

long CDsvAnyElement::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDsvElement::XmlReadOwn(oNode, pXmlRWKeys);
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	//xml_GetAttibuteValue(pXmlKeys->m_strTextKey, oNode, m_strMode);
	return 0;
}

long CDsvAnyElement::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDsvElement::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	//xml_SetAttributeValue(pXmlKeys->m_strTextKey, oElement, m_strMode);
	return 0;
}

long CDsvAnyElement::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CDsvElement::SerializeOwn(oBinaryBuffer);
	
	if(oBinaryBuffer.IsCalSizeMode())
	{
		//BinarySerializeCalLen(oBinaryBuffer, m_strMode);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		//BinarySerializeRead(oBinaryBuffer, m_strMode);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		//BinarySerializeWrite(oBinaryBuffer, m_strMode);
	}

	return 0;
}

BOOL CDsvAnyElement::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDsvElement::CopyOwn(pDest);

	CDsvAnyElement *p = (CDsvAnyElement*)pDest;

	p->m_strMode = m_strMode;
	return TRUE;
}

CBaseObject* CDsvAnyElement::Clone()
{
	CDsvAnyElement *p = new CDsvAnyElement();
	Copy(p);
	return p;
}

BOOL CDsvAnyElement::IsAnyDsvObject()
{
	m_bDsvSucc = TRUE;

	return TRUE;
}

BOOL CDsvAnyElement::IsMode_any()
{
	return (m_strMode == DSV_ANYELEMENT_MODE_ANY);
}

BOOL CDsvAnyElement::IsMode_define()
{
	return (m_strMode == DSV_ANYELEMENT_MODE_DEFINE);
}

BOOL CDsvAnyElement::IsMode_in_sequence()
{
	return (m_strMode == DSV_ANYELEMENT_MODE_IN_SEQUENCE);
}

BOOL CDsvAnyElement::IsMode_out_sequance()
{
	return (m_strMode == DSV_ANYELEMENT_MODE_OUT_SEQUENCE);
}

BOOL CDsvAnyElement::IsMode_reference()
{
	return (m_strMode == DSV_ANYELEMENT_MODE_REFERENCE);
}


void CDsvAnyElement::DsValidate(CExBaseList &listElments)
{
	if (m_strMode == DSV_ANYELEMENT_MODE_ANY)
	{
		DsValidate_any(listElments);
	}
	else if (m_strMode == DSV_ANYELEMENT_MODE_DEFINE)
	{
		DsValidate_define(listElments);
	}
	else if (m_strMode == DSV_ANYELEMENT_MODE_IN_SEQUENCE)
	{
		DsValidate_in_sequence(listElments);
	}
	else if (m_strMode == DSV_ANYELEMENT_MODE_OUT_SEQUENCE)
	{
		DsValidate_out_sequance(listElments);
	}
	else if (m_strMode == DSV_ANYELEMENT_MODE_REFERENCE)
	{
		DsValidate_reference(listElments);
	}
	else
	{
		DsValidate_any(listElments);
	}
}

void CDsvAnyElement::DsValidate_any(CExBaseList &listElments)
{
	m_bDsvSucc = TRUE;
}

//任意元素为定义的报文
void CDsvAnyElement::DsValidate_define(CExBaseList &listElments)
{
	POS pos = m_listDsvMatch.GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData*)m_listDsvMatch.GetNext(pos);

		//从定义的属性中，查找当前匹配到的报文，如果没有找到，则表示不合格
		if (FindByID(pData->m_strID) == NULL)
		{
			m_bDsvSucc = FALSE;
#ifndef exbase_not_use_m_dwReserved
			pData->m_dwReserved = 0;
#else
			pData->m_dwItemData = 0;
#endif
		}
		else
		{
#ifndef exbase_not_use_m_dwReserved
			pData->m_dwReserved = 1;
#else
			pData->m_dwItemData = 1;
#endif
		}
	}
}

//任意元素为序列定义中的元素
void CDsvAnyElement::DsValidate_in_sequence(CExBaseList &listElments)
{
	//如果没有匹配的报文，则返回
	if (m_listDsvMatch.GetCount() == 0)
	{
		m_bDsvSucc = TRUE;
		return;
	}

	POS pos = listElments.GetHeadPosition();
	CDsvElement *pElement = NULL;
	POS posData = m_listDsvMatch.GetHeadPosition();
	CDvmData *pData = NULL;

	//遍历所有的序列element
	while (pos != NULL)
	{
		pElement = (CDsvElement *)listElments.GetNext(pos);

		if (pElement->IsAnyDsvObject())
		{//AnyElement不参与判断
			continue;
		}

		//遍历匹配的数据
		posData = m_listDsvMatch.GetHeadPosition();

		while (posData != NULL)
		{
			pData = (CDvmData*)m_listDsvMatch.GetNext(posData);

			//如果数据ID等于元素ID，表示data在定义的序列中
			if (pData->m_strID == pElement->m_strID)
			{
#ifndef exbase_not_use_m_dwReserved
				pData->m_dwReserved = 1;
#else
				pData->m_dwItemData = 1;
#endif
			}
		}
	}

	//遍历匹配的数据集合
	posData = m_listDsvMatch.GetHeadPosition();
	long nCount = 0;

	while (posData != NULL)
	{
		pData = (CDvmData*)m_listDsvMatch.GetNext(posData);

		//统计序列定义之外的元素
#ifndef exbase_not_use_m_dwReserved
		if (pData->m_dwReserved != 1)
		{
			pData->m_dwReserved = 0;
			nCount++;
		}
#else
		if (pData->m_dwItemData != 1)
		{
			pData->m_dwItemData = 0;
			nCount++;
		}
#endif
	}

	//如果出现序列定义之外的元素，则不正确
	if (nCount > 0)
	{
		m_bDsvSucc = FALSE;
	}
	else
	{
		m_bDsvSucc = TRUE;
	}
}

void CDsvAnyElement::DsValidate_out_sequance(CExBaseList &listElments)
{
	//如果没有匹配的报文，则返回
	if (m_listDsvMatch.GetCount() == 0)
	{
		m_bDsvSucc = TRUE;
		return;
	}

	POS pos = listElments.GetHeadPosition();
	CDsvElement *pElement = NULL;
	POS posData = m_listDsvMatch.GetHeadPosition();
	CDvmData *pData = NULL;

	//遍历所有的序列element
	while (pos != NULL)
	{
		pElement = (CDsvElement *)listElments.GetNext(pos);

		if (pElement->IsAnyDsvObject())
		{//AnyElement不参与判断
			continue;
		}

		//遍历匹配的数据
		posData = m_listDsvMatch.GetHeadPosition();

		while (posData != NULL)
		{
			pData = (CDvmData*)m_listDsvMatch.GetNext(posData);

			//如果数据ID等于元素ID，表示data在定义的序列中，判断为不合格
			if (pData->m_strID == pElement->m_strID)
			{
#ifndef exbase_not_use_m_dwReserved
				pData->m_dwReserved = 0;
#else
				pData->m_dwItemData = 0;
#endif
			}
		}
	}

	//遍历匹配的数据集合
	posData = m_listDsvMatch.GetHeadPosition();
	long nCount = 0;

	while (posData != NULL)
	{
		pData = (CDvmData*)m_listDsvMatch.GetNext(posData);

		//统计序列定义中的元素
#ifndef exbase_not_use_m_dwReserved
		if (pData->m_dwReserved != 0)
		{
			pData->m_dwReserved = 1;
			nCount++;
		}
#else
		if (pData->m_dwItemData != 0)
		{
			pData->m_dwItemData = 1;
			nCount++;
		}
#endif
	}

	//如果出现序列定义中的元素，则不正确
	if (nCount > 0)
	{
		m_bDsvSucc = FALSE;
	}
	else
	{
		m_bDsvSucc = TRUE;
	}
}

void CDsvAnyElement::DsValidate_reference(CExBaseList &listElments)
{

}

