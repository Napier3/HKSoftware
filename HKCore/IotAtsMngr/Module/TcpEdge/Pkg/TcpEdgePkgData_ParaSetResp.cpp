//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TcpEdgePkgData_ParaSetResp.cpp  CTcpEdgePkgData_ParaSetResp


#include "stdafx.h"
#include "TcpEdgePkgData_ParaSetResp.h"

CTcpEdgePkgData_ParaSetResp::CTcpEdgePkgData_ParaSetResp()
{
	//��ʼ������

	//��ʼ����Ա����
	m_arrayNotMust[0] = PkgData_Node_Note;
	m_arrayNotMust[1] = PkgData_Node_ErrorCode;
}

CTcpEdgePkgData_ParaSetResp::~CTcpEdgePkgData_ParaSetResp()
{
}

BOOL CTcpEdgePkgData_ParaSetResp::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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
		strTemp = QString("�����󡿡�������ȱʧ��ParaSetResp��[%1]=>[%2]�����ֶ�ȱʧ;\n").arg(strID).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//ֵ����ʱ��������Ƿ���ȷ
		strTemp = QString("�����󡿡����������ParaSetResp��[%1]=>[%2]�ֶ����ʹ���;\n").arg(strID).arg(strAttr);
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
long CTcpEdgePkgData_ParaSetResp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDeviceIdKey, oNode, m_strDeviceId);
	xml_GetAttibuteValue(pXmlKeys->m_strStatusKey, oNode, m_strStatus);
	xml_GetAttibuteValue(pXmlKeys->m_strErrorCodeKey, oNode, m_strErrorCode);
	xml_GetAttibuteValue(pXmlKeys->m_strNoteKey, oNode, m_strNote);
	return 0;
}

long CTcpEdgePkgData_ParaSetResp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDeviceIdKey, oElement, m_strDeviceId);
	xml_SetAttributeValue(pXmlKeys->m_strStatusKey, oElement, m_strStatus);
	xml_SetAttributeValue(pXmlKeys->m_strErrorCodeKey, oElement, m_strErrorCode);
	xml_SetAttributeValue(pXmlKeys->m_strNoteKey, oElement, m_strNote);
	return 0;
}

long CTcpEdgePkgData_ParaSetResp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceId);
		BinarySerializeCalLen(oBinaryBuffer, m_strStatus);
		BinarySerializeCalLen(oBinaryBuffer, m_strErrorCode);
		BinarySerializeCalLen(oBinaryBuffer, m_strNote);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDeviceId);
		BinarySerializeRead(oBinaryBuffer, m_strStatus);
		BinarySerializeRead(oBinaryBuffer, m_strErrorCode);
		BinarySerializeRead(oBinaryBuffer, m_strNote);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceId);
		BinarySerializeWrite(oBinaryBuffer, m_strStatus);
		BinarySerializeWrite(oBinaryBuffer, m_strErrorCode);
		BinarySerializeWrite(oBinaryBuffer, m_strNote);
	}
	return 0;
}

void CTcpEdgePkgData_ParaSetResp::InitAfterRead()
{
}

BOOL CTcpEdgePkgData_ParaSetResp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkgData_ParaSetResp *p = (CTcpEdgePkgData_ParaSetResp*)pObj;

	if(m_strDeviceId != p->m_strDeviceId)
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

BOOL CTcpEdgePkgData_ParaSetResp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgData::CopyOwn(pDest);

	CTcpEdgePkgData_ParaSetResp *p = (CTcpEdgePkgData_ParaSetResp*)pDest;

	p->m_strDeviceId = m_strDeviceId;
	p->m_strStatus = m_strStatus;
	p->m_strErrorCode = m_strErrorCode;
	p->m_strNote = m_strNote;
	return TRUE;
}

CBaseObject* CTcpEdgePkgData_ParaSetResp::Clone()
{
	CTcpEdgePkgData_ParaSetResp *p = new CTcpEdgePkgData_ParaSetResp();
	Copy(p);
	return p;
}

long CTcpEdgePkgData_ParaSetResp::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("���"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("DeviceId"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("Status"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("ErrorCode"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->InsertColumn(4, _T("Note"));
	pListCtrl->SetColumnWidth(4, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CTcpEdgePkgData_ParaSetResp::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strDeviceId);
	pListCtrl->SetItemText(lItemIndex, 2, m_strStatus);
	pListCtrl->SetItemText(lItemIndex, 3, m_strErrorCode);
	pListCtrl->SetItemText(lItemIndex, 4, m_strNote);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CTcpEdgePkgData_ParaSetResp::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkgData_ParaSetResp::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkgData_ParaSetResp::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CTcpEdgePkgData_ParaSetResp::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strDeviceIdKey, m_strDeviceId);
	pRecordset->GetFieldValue(pXmlKeys->m_strStatusKey, m_strStatus);
	pRecordset->GetFieldValue(pXmlKeys->m_strErrorCodeKey, m_strErrorCode);
	pRecordset->GetFieldValue(pXmlKeys->m_strNoteKey, m_strNote);
	return 0;
}

long CTcpEdgePkgData_ParaSetResp::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgData::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strDeviceIdKey, m_strDeviceId);
	pRecordset->SetFieldValue(pXmlKeys->m_strStatusKey, m_strStatus);
	pRecordset->SetFieldValue(pXmlKeys->m_strErrorCodeKey, m_strErrorCode);
	pRecordset->SetFieldValue(pXmlKeys->m_strNoteKey, m_strNote);
	return 0;
}

