//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TcpEdgePkgData_DeviceGetLogResp.cpp  CTcpEdgePkgData_DeviceGetLogResp


#include "stdafx.h"
#include "TcpEdgePkgData_DeviceGetLogResp.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkgData_DeviceGetLogResp::CTcpEdgePkgData_DeviceGetLogResp()
{
	//��ʼ������

	//��ʼ����Ա����
	m_pTcpEdgePkgFile = NULL;
	m_arrayNotMust[0] = PkgData_Node_Note;
	m_arrayNotMust[1] = PkgData_Node_ErrorCode;

}

CTcpEdgePkgData_DeviceGetLogResp::~CTcpEdgePkgData_DeviceGetLogResp()
{
}

BOOL CTcpEdgePkgData_DeviceGetLogResp::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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

		strTemp = QString("�����󡿡�������ȱʧ��DeviceGetLogResp��[%1]=>[%2]�����ֶ�ȱʧ;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//ֵ����ʱ��������Ƿ���ȷ
		strTemp = QString("�����󡿡����������DeviceGetLogResp��[%1]=>[%2]�ֶ����ʹ���;\n").arg(strID).arg(strAttr);
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

long CTcpEdgePkgData_DeviceGetLogResp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strStatusKey, oNode, m_strStatus);
	xml_GetAttibuteValue(pXmlKeys->m_strErrorCodeKey, oNode, m_strErrorCode);
	xml_GetAttibuteValue(pXmlKeys->m_strNoteKey, oNode, m_strNote);
	return 0;
}

long CTcpEdgePkgData_DeviceGetLogResp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strStatusKey, oElement, m_strStatus);
	xml_SetAttributeValue(pXmlKeys->m_strErrorCodeKey, oElement, m_strErrorCode);
	xml_SetAttributeValue(pXmlKeys->m_strNoteKey, oElement, m_strNote);
	return 0;
}

long CTcpEdgePkgData_DeviceGetLogResp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strStatus);
		BinarySerializeCalLen(oBinaryBuffer, m_strErrorCode);
		BinarySerializeCalLen(oBinaryBuffer, m_strNote);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strStatus);
		BinarySerializeRead(oBinaryBuffer, m_strErrorCode);
		BinarySerializeRead(oBinaryBuffer, m_strNote);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strStatus);
		BinarySerializeWrite(oBinaryBuffer, m_strErrorCode);
		BinarySerializeWrite(oBinaryBuffer, m_strNote);
	}
	return 0;
}

void CTcpEdgePkgData_DeviceGetLogResp::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == MNGRCLASSID_CTCPEDGEPKGFILE)
		{
			m_pTcpEdgePkgFile = (CTcpEdgePkgFile*)p;
			m_strErrorInfo += m_pTcpEdgePkgFile->m_strErrorInfo;
			m_strNecessityErr += m_pTcpEdgePkgFile->m_strNecessityErr;
			m_strNecessityLack += m_pTcpEdgePkgFile->m_strNecessityLack;
		}
	}

	if (m_pTcpEdgePkgFile == NULL)
	{
		m_pTcpEdgePkgFile = (CTcpEdgePkgFile*)AddNewChild(new CTcpEdgePkgFile());
	}

}

BOOL CTcpEdgePkgData_DeviceGetLogResp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_DeviceGetLogResp *p = (CTcpEdgePkgData_DeviceGetLogResp*)pObj;

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

BOOL CTcpEdgePkgData_DeviceGetLogResp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_DeviceGetLogResp *p = (CTcpEdgePkgData_DeviceGetLogResp*)pDest;

	p->m_strStatus = m_strStatus;
	p->m_strErrorCode = m_strErrorCode;
	p->m_strNote = m_strNote;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_DeviceGetLogResp::Clone()
{
	CTcpEdgePkgData_DeviceGetLogResp *p = new CTcpEdgePkgData_DeviceGetLogResp();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkgData_DeviceGetLogResp::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkgData_DeviceGetLogResp *p = new CTcpEdgePkgData_DeviceGetLogResp();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkgData_DeviceGetLogResp::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CTCPEDGEPKGFILE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_DeviceGetLogResp::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCTcpEdgePkgFileKey)
	{
		pNew = new CTcpEdgePkgFile();
		pNew->m_strID = _T("DeviceGetLogResp");
	}

	return pNew;
}

CExBaseObject* CTcpEdgePkgData_DeviceGetLogResp::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CTCPEDGEPKGFILE)
	{
		pNew = new CTcpEdgePkgFile();
	}

	return pNew;
}
long CTcpEdgePkgData_DeviceGetLogResp::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strStatusKey, m_strStatus);
	pRecordset->GetFieldValue(pXmlKeys->m_strErrorCodeKey, m_strErrorCode);
	pRecordset->GetFieldValue(pXmlKeys->m_strNoteKey, m_strNote);
	return 0;
}

long CTcpEdgePkgData_DeviceGetLogResp::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strStatusKey, m_strStatus);
	pRecordset->SetFieldValue(pXmlKeys->m_strErrorCodeKey, m_strErrorCode);
	pRecordset->SetFieldValue(pXmlKeys->m_strNoteKey, m_strNote);
	return 0;
}

