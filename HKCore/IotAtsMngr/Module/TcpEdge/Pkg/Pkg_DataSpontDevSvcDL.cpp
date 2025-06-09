//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_DataSpontDevSvcDL.cpp  CPkg_DataSpontDevSvcDL


#include "stdafx.h"
#include "Pkg_DataSpontDevSvcDL.h"

CPkg_DataSpontDevSvcDL::CPkg_DataSpontDevSvcDL()
{
	m_arrayNotMust[0] = PkgData_Node_Angle;
}

CPkg_DataSpontDevSvcDL::~CPkg_DataSpontDevSvcDL()
{
}

BOOL CPkg_DataSpontDevSvcDL::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
{
	//在这里判断报文中的String字段是否有误
	QString strTemp;
	CString strAttr(strAttrName);
	CString strID(GetXmlElementKey());
	BOOL bRet = oNode.xml_GetAttibuteValue(strAttrName,strAttrVal);
	if(!strAttrVal.GetLength())
	{
		//值不存在时检查是否必需
		for(int i = 0; i < 64; i++)
		{
			if(m_arrayNotMust[i] == strAttr)
			{
				return bRet;
			}
		}

		strTemp = QString("【错误】【必需项缺失】DataSpont：[%1]=>[%2$%3$%4$%5]必需字段缺失;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Devices).arg(PkgData_Node_Services).arg(PkgData_Node_DataList).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】DataSpont：[%1]=>[%2$%3$%4$%5]字段类型错误;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Devices).arg(PkgData_Node_Services).arg(PkgData_Node_DataList).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CPkg_DataSpontDevSvcDL::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDataReferKey, oNode, m_strDataRefer);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetAttibuteValue(pXmlKeys->m_strAngleKey, oNode, m_strAngle);
	xml_GetAttibuteValue(pXmlKeys->m_strTimeStampKey, oNode, m_strTimeStamp);
	xml_GetAttibuteValue(pXmlKeys->m_strQualityKey, oNode, m_strQuality);

	m_strErrorInfo += CheckTimeFormat(_T("DataSpont"), PkgData_Node_Devices, PkgData_Node_Services, 
		_T("$DataList"), _T("$TimeStamp"), m_strTimeStamp);
	m_strRangeOut += CheckTimeFormat(_T("DataSpont"), PkgData_Node_Devices, PkgData_Node_Services, 
		_T("$DataList"), _T("$TimeStamp"), m_strTimeStamp);


	char* pTemp = const_cast<char*>(m_strQuality.GetString());
	//lmy,20230915修改
	//if((pTemp[0] != '0' || pTemp[0] != '1') && (pTemp[1] != '0' || pTemp[1] != '1'))
	if((pTemp[0] != '0' && pTemp[0] != '1') || (pTemp[1] != '0' && pTemp[1] != '1'))
	{
		QString strTemp;
		strTemp = QString(_T("【错误】【超过范围】DataSpont：[%1]=>[%2$%3$%4$%5]字段超出范围;\n")).arg(PkgData_Node_Data).arg(
			PkgData_Node_Devices).arg(PkgData_Node_Services).arg(PkgData_Node_DataList).arg(PkgData_Node_Quality);
		m_strErrorInfo += strTemp;
		m_strRangeOut += strTemp;
	}

	return 0;
}

long CPkg_DataSpontDevSvcDL::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDataReferKey, oElement, m_strDataRefer);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	xml_SetAttributeValue(pXmlKeys->m_strAngleKey, oElement, m_strAngle);
	xml_SetAttributeValue(pXmlKeys->m_strTimeStampKey, oElement, m_strTimeStamp);
	xml_SetAttributeValue(pXmlKeys->m_strQualityKey, oElement, m_strQuality);
	return 0;
}

long CPkg_DataSpontDevSvcDL::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDataRefer);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
		BinarySerializeCalLen(oBinaryBuffer, m_strAngle);
		BinarySerializeCalLen(oBinaryBuffer, m_strTimeStamp);
		BinarySerializeCalLen(oBinaryBuffer, m_strQuality);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDataRefer);
		BinarySerializeRead(oBinaryBuffer, m_strValue);
		BinarySerializeRead(oBinaryBuffer, m_strAngle);
		BinarySerializeRead(oBinaryBuffer, m_strTimeStamp);
		BinarySerializeRead(oBinaryBuffer, m_strQuality);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDataRefer);
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
		BinarySerializeWrite(oBinaryBuffer, m_strAngle);
		BinarySerializeWrite(oBinaryBuffer, m_strTimeStamp);
		BinarySerializeWrite(oBinaryBuffer, m_strQuality);
	}
	return 0;
}

void CPkg_DataSpontDevSvcDL::InitAfterRead()
{
}

BOOL CPkg_DataSpontDevSvcDL::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_DataSpontDevSvcDL *p = (CPkg_DataSpontDevSvcDL*)pObj;

	if(m_strDataRefer != p->m_strDataRefer)
	{
		return FALSE;
	}

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	if(m_strAngle != p->m_strAngle)
	{
		return FALSE;
	}

	if(m_strTimeStamp != p->m_strTimeStamp)
	{
		return FALSE;
	}

	if(m_strQuality != p->m_strQuality)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPkg_DataSpontDevSvcDL::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_DataSpontDevSvcDL *p = (CPkg_DataSpontDevSvcDL*)pDest;

	p->m_strDataRefer = m_strDataRefer;
	p->m_strValue = m_strValue;
	p->m_strAngle = m_strAngle;
	p->m_strTimeStamp = m_strTimeStamp;
	p->m_strQuality = m_strQuality;
	return TRUE;
}

CBaseObject* CPkg_DataSpontDevSvcDL::Clone()
{
	CPkg_DataSpontDevSvcDL *p = new CPkg_DataSpontDevSvcDL();
	Copy(p);
	return p;
}

long CPkg_DataSpontDevSvcDL::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, _T("编号"));
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("DataRefer"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("Value"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("Angle"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->InsertColumn(4, _T("TimeStamp"));
	pListCtrl->SetColumnWidth(4, 80);
	pListCtrl->InsertColumn(5, _T("Quality"));
	pListCtrl->SetColumnWidth(5, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CPkg_DataSpontDevSvcDL::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strDataRefer);
	pListCtrl->SetItemText(lItemIndex, 2, m_strValue);
	pListCtrl->SetItemText(lItemIndex, 3, m_strAngle);
	pListCtrl->SetItemText(lItemIndex, 4, m_strTimeStamp);
	pListCtrl->SetItemText(lItemIndex, 5, m_strQuality);
	pListCtrl->SetItemData(lItemIndex, (WORD)this);
	return 0;
}

BOOL CPkg_DataSpontDevSvcDL::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_DataSpontDevSvcDL::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_DataSpontDevSvcDL::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CPkg_DataSpontDevSvcDL::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strDataReferKey, m_strDataRefer);
	pRecordset->GetFieldValue(pXmlKeys->m_strValueKey, m_strValue);
	pRecordset->GetFieldValue(pXmlKeys->m_strAngleKey, m_strAngle);
	pRecordset->GetFieldValue(pXmlKeys->m_strTimeStampKey, m_strTimeStamp);
	pRecordset->GetFieldValue(pXmlKeys->m_strQualityKey, m_strQuality);
	return 0;
}

long CPkg_DataSpontDevSvcDL::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strDataReferKey, m_strDataRefer);
	pRecordset->SetFieldValue(pXmlKeys->m_strValueKey, m_strValue);
	pRecordset->SetFieldValue(pXmlKeys->m_strAngleKey, m_strAngle);
	pRecordset->SetFieldValue(pXmlKeys->m_strTimeStampKey, m_strTimeStamp);
	pRecordset->SetFieldValue(pXmlKeys->m_strQualityKey, m_strQuality);
	return 0;
}

CDvmDataset* CPkg_DataSpontDevSvcDL::ToDataset()
{
	CDvmDataset* pDataset = new CDvmDataset;
	pDataset->m_strID = PkgData_Node_DataList;
	pDataset->m_strDataType = PkgData_Type_Array;
	pDataset->m_dwItemData = 1;

	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_DataRefer);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Value);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Angle, 0);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_TimeStamp);
	CTcpEdgePkgData::AddNewData(pDataset, PkgData_Node_Quality);

	return pDataset;
}