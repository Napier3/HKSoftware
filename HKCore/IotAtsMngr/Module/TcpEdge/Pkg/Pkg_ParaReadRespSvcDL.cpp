//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Pkg_ParaReadRespSvcDL.cpp  CPkg_ParaReadRespSvcDL


#include "stdafx.h"
#include "Pkg_ParaReadRespSvcDL.h"

CPkg_ParaReadRespSvcDL::CPkg_ParaReadRespSvcDL()
{
	//��ʼ������

	//��ʼ����Ա����
}

CPkg_ParaReadRespSvcDL::~CPkg_ParaReadRespSvcDL()
{
}

BOOL CPkg_ParaReadRespSvcDL::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
{
	//�������жϱ����е�String�ֶ��Ƿ�����
	QString strTemp;
	CString strAttr(strAttrName);
	//CString strID(GetXmlElementKey());
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
		strTemp = QString("�����󡿡�������ȱʧ��ParaReadResp��[%1]=>[%2$%3$%4]�����ֶ�ȱʧ;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Services).arg(PkgData_Node_DataList).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//ֵ����ʱ��������Ƿ���ȷ
		strTemp = QString("�����󡿡����������ParaReadResp��[%1]=>[%2$%3$%4]�ֶ����ʹ���;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Services).arg(PkgData_Node_DataList).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CPkg_ParaReadRespSvcDL::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDataReferKey, oNode, m_strDataRefer);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	return 0;
}

long CPkg_ParaReadRespSvcDL::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDataReferKey, oElement, m_strDataRefer);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	return 0;
}

long CPkg_ParaReadRespSvcDL::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDataRefer);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDataRefer);
		BinarySerializeRead(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDataRefer);
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
	}
	return 0;
}

void CPkg_ParaReadRespSvcDL::InitAfterRead()
{
}

BOOL CPkg_ParaReadRespSvcDL::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_ParaReadRespSvcDL *p = (CPkg_ParaReadRespSvcDL*)pObj;

	if(m_strDataRefer != p->m_strDataRefer)
	{
		return FALSE;
	}

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPkg_ParaReadRespSvcDL::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_ParaReadRespSvcDL *p = (CPkg_ParaReadRespSvcDL*)pDest;

	p->m_strDataRefer = m_strDataRefer;
	p->m_strValue = m_strValue;
	return TRUE;
}

CBaseObject* CPkg_ParaReadRespSvcDL::Clone()
{
	CPkg_ParaReadRespSvcDL *p = new CPkg_ParaReadRespSvcDL();
	Copy(p);
	return p;
}

long CPkg_ParaReadRespSvcDL::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("���"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("DataRefer"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("Value"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_ParaReadRespSvcDL::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strDataRefer);
	pListCtrl->SetItemText(lItemIndex, 2, m_strValue);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_ParaReadRespSvcDL::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_ParaReadRespSvcDL::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_ParaReadRespSvcDL::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CPkg_ParaReadRespSvcDL::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strDataReferKey, m_strDataRefer);
	pRecordset->GetFieldValue(pXmlKeys->m_strValueKey, m_strValue);
	return 0;
}

long CPkg_ParaReadRespSvcDL::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strDataReferKey, m_strDataRefer);
	pRecordset->SetFieldValue(pXmlKeys->m_strValueKey, m_strValue);
	return 0;
}

