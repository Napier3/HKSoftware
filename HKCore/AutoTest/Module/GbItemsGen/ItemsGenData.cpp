//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ItemsGenData.cpp  CItemsGenData


#include "stdafx.h"
#include "ItemsGenData.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CItemsGenData::CItemsGenData()
{
	//��ʼ������
	//��ʼ����Ա����
}

CItemsGenData::~CItemsGenData()
{
}

long CItemsGenData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strData_TypeKey, oNode, m_strDataType);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	return 0;
}

long CItemsGenData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strData_TypeKey, oElement, m_strDataType);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	return 0;
}

long CItemsGenData::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDataType);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDataType);
		BinarySerializeRead(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDataType);
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
	}
	return 0;
}

void CItemsGenData::InitAfterRead()
{
}

BOOL CItemsGenData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CItemsGenData *p = (CItemsGenData*)pObj;

	if(m_strDataType != p->m_strDataType)
	{
		return FALSE;
	}

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CItemsGenData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CItemsGenData *p = (CItemsGenData*)pDest;

	p->m_strDataType = m_strDataType;
	p->m_strValue = m_strValue;
	return TRUE;
}

CBaseObject* CItemsGenData::Clone()
{
	CItemsGenData *p = new CItemsGenData();
	Copy(p);
	return p;
}

CBaseObject* CItemsGenData::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CItemsGenData *p = new CItemsGenData();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

//Enable�µ����ݣ������ݽӿ��е��������Ƚϣ��ж��Ƿ�ʹ��
BOOL CItemsGenData::IsEnable(CItemsGenInterface *pInterface)
{
	CItemsGenData *pInterfaceData = (CItemsGenData *)pInterface->FindByID(m_strID);

	if (pInterfaceData == NULL)
	{
		return FALSE;
	}

	//Ҫ���������ͱ���һ��
	if (pInterfaceData->m_strDataType != m_strDataType)
	{
		return FALSE;
	}

	if (m_strDataType == _T("long"))
	{
		if (CString_To_long(pInterfaceData->m_strValue)
			!= CString_To_long(m_strValue))
		{
			return FALSE;
		}
		
	}
	else if(pInterfaceData->m_strValue != m_strValue)
	{
		return FALSE;
	}

	return TRUE;
}