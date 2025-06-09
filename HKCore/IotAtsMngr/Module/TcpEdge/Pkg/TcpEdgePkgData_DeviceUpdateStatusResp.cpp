//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TcpEdgePkgData_DeviceUpdateStatusResp.cpp  CTcpEdgePkgData_DeviceUpdateStatusResp


#include "stdafx.h"
#include "TcpEdgePkgData_DeviceUpdateStatusResp.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_DeviceUpdateStatusResp::CTcpEdgePkgData_DeviceUpdateStatusResp()
{
	//��ʼ������

	//��ʼ����Ա����
}

CTcpEdgePkgData_DeviceUpdateStatusResp::~CTcpEdgePkgData_DeviceUpdateStatusResp()
{
}

BOOL CTcpEdgePkgData_DeviceUpdateStatusResp::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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

		strTemp = QString("�����󡿡�������ȱʧ��DeviceUpdateStatusResp��[%1]=>[%2]�����ֶ�ȱʧ;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//ֵ����ʱ��������Ƿ���ȷ
		strTemp = QString("�����󡿡����������DeviceUpdateStatusResp��[%1]=>[%2]�ֶ����ʹ���;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CTcpEdgePkgData_DeviceUpdateStatusResp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strJobIdKey, oNode, m_strJobId);
	xml_GetAttibuteValue(pXmlKeys->m_strProgressKey, oNode, m_strProgress);
	xml_GetAttibuteValue(pXmlKeys->m_strStateKey, oNode, m_strState);

	m_strErrorInfo += CheckRangePer(_T("DeviceUpdateStatusResp"), PkgData_Node_Progress, m_strProgress);
	m_strRangeOut += CheckRangePer(_T("DeviceUpdateStatusResp"), PkgData_Node_Progress, m_strProgress);

	//lmy,20230918�޸�
	//if(m_strState != _T("0") || m_strState != _T("1")|| m_strState != _T("2") || m_strState != _T("3")
	//	|| m_strState != _T("4") || m_strState != _T("5"))
	if(m_strState != _T("0") && m_strState != _T("1") && m_strState != _T("2") && m_strState != _T("3")
		&& m_strState != _T("4") && m_strState != _T("5"))
	{
		QString strTemp;
		strTemp = QString(_T("�����󡿡�������Χ��DeviceUpdateStatusResp: [Data]=>[State]�ֶγ�����Χ, �޷��жϵ�ǰ��������ִ��״̬;\n"));
		m_strErrorInfo += strTemp;
		m_strRangeOut += strTemp;
	}


	return 0;
}

long CTcpEdgePkgData_DeviceUpdateStatusResp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strJobIdKey, oElement, m_strJobId);
	xml_SetAttributeValue(pXmlKeys->m_strProgressKey, oElement, m_strProgress);
	xml_SetAttributeValue(pXmlKeys->m_strStateKey, oElement, m_strState);
	return 0;
}

long CTcpEdgePkgData_DeviceUpdateStatusResp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strJobId);
		BinarySerializeCalLen(oBinaryBuffer, m_strProgress);
		BinarySerializeCalLen(oBinaryBuffer, m_strState);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strJobId);
		BinarySerializeRead(oBinaryBuffer, m_strProgress);
		BinarySerializeRead(oBinaryBuffer, m_strState);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strJobId);
		BinarySerializeWrite(oBinaryBuffer, m_strProgress);
		BinarySerializeWrite(oBinaryBuffer, m_strState);
	}
	return 0;
}

void CTcpEdgePkgData_DeviceUpdateStatusResp::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_DeviceUpdateStatusResp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_DeviceUpdateStatusResp *p = (CTcpEdgePkgData_DeviceUpdateStatusResp*)pObj;

	if(m_strJobId != p->m_strJobId)
	{
		return FALSE;
	}

	if(m_strProgress != p->m_strProgress)
	{
		return FALSE;
	}

	if(m_strState != p->m_strState)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgData_DeviceUpdateStatusResp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_DeviceUpdateStatusResp *p = (CTcpEdgePkgData_DeviceUpdateStatusResp*)pDest;

	p->m_strJobId = m_strJobId;
	p->m_strProgress = m_strProgress;
	p->m_strState = m_strState;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_DeviceUpdateStatusResp::Clone()
{
	CTcpEdgePkgData_DeviceUpdateStatusResp *p = new CTcpEdgePkgData_DeviceUpdateStatusResp();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_DeviceUpdateStatusResp::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_DeviceUpdateStatusResp *p = new CTcpEdgePkgData_DeviceUpdateStatusResp();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_DeviceUpdateStatusResp::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_DeviceUpdateStatusResp::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_DeviceUpdateStatusResp::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_DeviceUpdateStatusResp::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strJobIdKey, m_strJobId);
	pRecordset->GetFieldValue(pXmlKeys->m_strProgressKey, m_strProgress);
	pRecordset->GetFieldValue(pXmlKeys->m_strStateKey, m_strState);
	return 0;
}

long CTcpEdgePkgData_DeviceUpdateStatusResp::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strJobIdKey, m_strJobId);
	pRecordset->SetFieldValue(pXmlKeys->m_strProgressKey, m_strProgress);
	pRecordset->SetFieldValue(pXmlKeys->m_strStateKey, m_strState);
	return 0;
}

