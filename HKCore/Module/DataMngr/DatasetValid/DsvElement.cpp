//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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
	//��ʼ������

	//��ʼ����Ա����
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

		//�Ե�ǰelement����ƥ��
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
				//���element֮ǰ�Ķ�����anly����
				//�����element��ƥ��
				break;
			}
			else
			{
				if (nCount > 0)
				{
					//element֮ǰ�Ķ�����anly���󣬵�ǰelement��ƥ��ɹ�����
					//�����element��ƥ��
					break;
				}
				else
				{
					//element֮ǰ�Ķ�����anly���󣬲��ҵ�ǰelement��û���κ�ƥ�����
					//��������ǰ��data����
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

		//�Ե�ǰelement����ƥ��
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

//����Ԫ��Ϊ����ı���
void CDsvAnyElement::DsValidate_define(CExBaseList &listElments)
{
	POS pos = m_listDsvMatch.GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData*)m_listDsvMatch.GetNext(pos);

		//�Ӷ���������У����ҵ�ǰƥ�䵽�ı��ģ����û���ҵ������ʾ���ϸ�
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

//����Ԫ��Ϊ���ж����е�Ԫ��
void CDsvAnyElement::DsValidate_in_sequence(CExBaseList &listElments)
{
	//���û��ƥ��ı��ģ��򷵻�
	if (m_listDsvMatch.GetCount() == 0)
	{
		m_bDsvSucc = TRUE;
		return;
	}

	POS pos = listElments.GetHeadPosition();
	CDsvElement *pElement = NULL;
	POS posData = m_listDsvMatch.GetHeadPosition();
	CDvmData *pData = NULL;

	//�������е�����element
	while (pos != NULL)
	{
		pElement = (CDsvElement *)listElments.GetNext(pos);

		if (pElement->IsAnyDsvObject())
		{//AnyElement�������ж�
			continue;
		}

		//����ƥ�������
		posData = m_listDsvMatch.GetHeadPosition();

		while (posData != NULL)
		{
			pData = (CDvmData*)m_listDsvMatch.GetNext(posData);

			//�������ID����Ԫ��ID����ʾdata�ڶ����������
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

	//����ƥ������ݼ���
	posData = m_listDsvMatch.GetHeadPosition();
	long nCount = 0;

	while (posData != NULL)
	{
		pData = (CDvmData*)m_listDsvMatch.GetNext(posData);

		//ͳ�����ж���֮���Ԫ��
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

	//����������ж���֮���Ԫ�أ�����ȷ
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
	//���û��ƥ��ı��ģ��򷵻�
	if (m_listDsvMatch.GetCount() == 0)
	{
		m_bDsvSucc = TRUE;
		return;
	}

	POS pos = listElments.GetHeadPosition();
	CDsvElement *pElement = NULL;
	POS posData = m_listDsvMatch.GetHeadPosition();
	CDvmData *pData = NULL;

	//�������е�����element
	while (pos != NULL)
	{
		pElement = (CDsvElement *)listElments.GetNext(pos);

		if (pElement->IsAnyDsvObject())
		{//AnyElement�������ж�
			continue;
		}

		//����ƥ�������
		posData = m_listDsvMatch.GetHeadPosition();

		while (posData != NULL)
		{
			pData = (CDvmData*)m_listDsvMatch.GetNext(posData);

			//�������ID����Ԫ��ID����ʾdata�ڶ���������У��ж�Ϊ���ϸ�
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

	//����ƥ������ݼ���
	posData = m_listDsvMatch.GetHeadPosition();
	long nCount = 0;

	while (posData != NULL)
	{
		pData = (CDvmData*)m_listDsvMatch.GetNext(posData);

		//ͳ�����ж����е�Ԫ��
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

	//����������ж����е�Ԫ�أ�����ȷ
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

