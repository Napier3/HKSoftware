//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TcpEdgePkgData_AppInstallResult.cpp  CTcpEdgePkgData_AppInstallResult


#include "stdafx.h"
#include "TcpEdgePkgData_AppInstallResult.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_AppInstallResult::CTcpEdgePkgData_AppInstallResult()
{
	//��ʼ������

	//��ʼ����Ա����
	m_arrayNotMust[0] = PkgData_Node_Note;
	m_arrayNotMust[1] = PkgData_Node_ErrorCode;
}

CTcpEdgePkgData_AppInstallResult::~CTcpEdgePkgData_AppInstallResult()
{
}

BOOL CTcpEdgePkgData_AppInstallResult::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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

		strTemp = QString("�����󡿡�������ȱʧ��AppInstallResult��[%1]=>[%2]�����ֶ�ȱʧ;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//ֵ����ʱ��������Ƿ���ȷ
		strTemp = QString("�����󡿡����������AppInstallResult��[%1]=>[%2]�ֶ����ʹ���;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

// 	if(strAttrName == L"Status")
// 	{
// 		if(strAttrVal == "0")
// 		{
// 			m_arrayNotMust[1] = PkgData_Node_ErrorCode;
// 		}
// 	}

	return bRet;
}

long CTcpEdgePkgData_AppInstallResult::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strJobIdKey, oNode, m_strJobId);
	xml_GetAttibuteValue(pXmlKeys->m_strStatusKey, oNode, m_strStatus);
	xml_GetAttibuteValue(pXmlKeys->m_strErrorCodeKey, oNode, m_strErrorCode);
	xml_GetAttibuteValue(pXmlKeys->m_strNoteKey, oNode, m_strNote);
	return 0;
}

long CTcpEdgePkgData_AppInstallResult::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strJobIdKey, oElement, m_strJobId);
	xml_SetAttributeValue(pXmlKeys->m_strStatusKey, oElement, m_strStatus);
	xml_SetAttributeValue(pXmlKeys->m_strErrorCodeKey, oElement, m_strErrorCode);
	xml_SetAttributeValue(pXmlKeys->m_strNoteKey, oElement, m_strNote);
	return 0;
}

long CTcpEdgePkgData_AppInstallResult::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strJobId);
		BinarySerializeCalLen(oBinaryBuffer, m_strStatus);
		BinarySerializeCalLen(oBinaryBuffer, m_strErrorCode);
		BinarySerializeCalLen(oBinaryBuffer, m_strNote);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strJobId);
		BinarySerializeRead(oBinaryBuffer, m_strStatus);
		BinarySerializeRead(oBinaryBuffer, m_strErrorCode);
		BinarySerializeRead(oBinaryBuffer, m_strNote);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strJobId);
		BinarySerializeWrite(oBinaryBuffer, m_strStatus);
		BinarySerializeWrite(oBinaryBuffer, m_strErrorCode);
		BinarySerializeWrite(oBinaryBuffer, m_strNote);
	}
	return 0;
}

void CTcpEdgePkgData_AppInstallResult::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_AppInstallResult::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_AppInstallResult *p = (CTcpEdgePkgData_AppInstallResult*)pObj;

	if(m_strJobId != p->m_strJobId)
	{
		return FALSE;
	}

	if(m_strStatus != p->m_strStatus)
	{
		return FALSE;
	}

	if(m_strErrorCode != p->m_strErrorCode)
	{
		return FALSE;
	}

	if(m_strNote != p->m_strNote)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTcpEdgePkgData_AppInstallResult::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_AppInstallResult *p = (CTcpEdgePkgData_AppInstallResult*)pDest;

	p->m_strJobId = m_strJobId;
	p->m_strStatus = m_strStatus;
	p->m_strErrorCode = m_strErrorCode;
	p->m_strNote = m_strNote;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_AppInstallResult::Clone()
{
	CTcpEdgePkgData_AppInstallResult *p = new CTcpEdgePkgData_AppInstallResult();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_AppInstallResult::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_AppInstallResult *p = new CTcpEdgePkgData_AppInstallResult();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_AppInstallResult::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_AppInstallResult::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_AppInstallResult::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_AppInstallResult::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strJobIdKey, m_strJobId);
	pRecordset->GetFieldValue(pXmlKeys->m_strStatusKey, m_strStatus);
	pRecordset->GetFieldValue(pXmlKeys->m_strErrorCodeKey, m_strErrorCode);
	pRecordset->GetFieldValue(pXmlKeys->m_strNoteKey, m_strNote);
	return 0;
}

long CTcpEdgePkgData_AppInstallResult::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strJobIdKey, m_strJobId);
	pRecordset->SetFieldValue(pXmlKeys->m_strStatusKey, m_strStatus);
	pRecordset->SetFieldValue(pXmlKeys->m_strErrorCodeKey, m_strErrorCode);
	pRecordset->SetFieldValue(pXmlKeys->m_strNoteKey, m_strNote);
	return 0;
}

