//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TcpEdgePkgTemperature.cpp  CTcpEdgePkgTemperature


#include "stdafx.h"
#include "TcpEdgePkgTemperature.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgTemperature::CTcpEdgePkgTemperature()
{
	//��ʼ������

	//��ʼ����Ա����
}

CTcpEdgePkgTemperature::~CTcpEdgePkgTemperature()
{
}

BOOL CTcpEdgePkgTemperature::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
{
	//�������жϱ����е�String�ֶ��Ƿ�����
	QString strTemp;
	CString strAttr(strAttrName);
	CString strID(GetXmlElementKey());
	BOOL bRet = oNode.xml_GetAttibuteValue(strAttrName,strAttrVal);
	if(!strAttrVal.GetLength())
	{
		//ֵ������ʱ����Ƿ����
		for(int i = 0; i < 64; i++)
		{
			if(m_arrayNotMust[i] == strAttr)
			{
				return bRet;
			}
		}

		strTemp = QString("�����󡿡�������ȱʧ��%1��[%2]=>[%3$%4]�����ֶ�ȱʧ;\n").arg(m_strID).arg(PkgData_Node_Data).arg(
			PkgData_Node_Temperature).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//ֵ����ʱ��������Ƿ���ȷ
		strTemp = QString("�����󡿡����������%1��[%2]=>[%3$%4]�ֶ����ʹ���;\n").arg(m_strID).arg(PkgData_Node_Data).arg(
			PkgData_Node_Temperature).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CTcpEdgePkgTemperature::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTemLowKey, oNode, m_strTemLow);
	xml_GetAttibuteValue(pXmlKeys->m_strTemHighKey, oNode, m_strTemHigh);
	return 0;
}

long CTcpEdgePkgTemperature::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTemLowKey, oElement, m_strTemLow);
	xml_SetAttributeValue(pXmlKeys->m_strTemHighKey, oElement, m_strTemHigh);
	return 0;
}

long CTcpEdgePkgTemperature::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strTemLow);
		BinarySerializeCalLen(oBinaryBuffer, m_strTemHigh);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strTemLow);
		BinarySerializeRead(oBinaryBuffer, m_strTemHigh);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strTemLow);
		BinarySerializeWrite(oBinaryBuffer, m_strTemHigh);
	}
	return 0;
}

void CTcpEdgePkgTemperature::InitAfterRead()
{
}

BOOL CTcpEdgePkgTemperature::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgTemperature *p = (CTcpEdgePkgTemperature*)pObj;

	if(m_strTemLow != p->m_strTemLow)
	{
		return FALSE;
	}

	if(m_strTemHigh != p->m_strTemHigh)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgTemperature::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CTcpEdgePkgTemperature *p = (CTcpEdgePkgTemperature*)pDest;

	p->m_strTemLow = m_strTemLow;
	p->m_strTemHigh = m_strTemHigh;
	return TRUE;
}

CBaseObject* CTcpEdgePkgTemperature::Clone()
{
	CTcpEdgePkgTemperature *p = new CTcpEdgePkgTemperature();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgTemperature::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgTemperature *p = new CTcpEdgePkgTemperature();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgTemperature::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgTemperature::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgTemperature::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgTemperature::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strTemLowKey, m_strTemLow);
	pRecordset->GetFieldValue(pXmlKeys->m_strTemHighKey, m_strTemHigh);
	return 0;
}

long CTcpEdgePkgTemperature::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strTemLowKey, m_strTemLow);
	pRecordset->SetFieldValue(pXmlKeys->m_strTemHighKey, m_strTemHigh);
	return 0;
}

CDvmDataset* CTcpEdgePkgTemperature::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_Temperature;
	pDataset->m_strDataType = PkgData_Type_Object;

	CDvmData* pData = pDataset->AddNewData(PkgData_Node_TemLow, PkgData_Node_TemLow, PkgData_Type_String, "");
	pData->m_dwItemData = 1;
	pData = pDataset->AddNewData(PkgData_Node_TemHigh, PkgData_Node_TemHigh, PkgData_Type_String, "");
	pData->m_dwItemData = 1;

	return pDataset;
}