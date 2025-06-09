//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_DataReadRespDevSvcDL.cpp  CPkg_DataReadRespDevSvcDL


#include "stdafx.h"
#include "Pkg_DataReadRespDevSvcDL.h"

CPkg_DataReadRespDevSvcDL::CPkg_DataReadRespDevSvcDL()
{
	//初始化属性

	//初始化成员变量
	m_arrayNotMust[0] = PkgData_Node_Angle;
}

CPkg_DataReadRespDevSvcDL::~CPkg_DataReadRespDevSvcDL()
{
}

BOOL CPkg_DataReadRespDevSvcDL::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
{
	//在这里判断报文中的String字段是否有误
	QString strTemp;
	CString strAttr(strAttrName);
	//CString strID(GetXmlElementKey());
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
		strTemp = QString("【错误】【必需项缺失】DataReadResp：[%1]=>[%2$%3$%4$%5]必需字段缺失;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Devices).arg(PkgData_Node_Services).arg(PkgData_Node_DataList).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】DataReadResp：[%1]=>[%2$%3$%4$%5]字段类型错误;\n").arg(PkgData_Node_Data).arg(PkgData_Node_Devices).arg(PkgData_Node_Services).arg(PkgData_Node_DataList).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CPkg_DataReadRespDevSvcDL::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDataReferKey, oNode, m_strDataRefer);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);
	xml_GetAttibuteValue(pXmlKeys->m_strAngleKey, oNode, m_strAngle);
	xml_GetAttibuteValue(pXmlKeys->m_strTimeStampKey, oNode, m_strTimeStamp);
	xml_GetAttibuteValue(pXmlKeys->m_strQualityKey, oNode, m_strQuality);

	m_strErrorInfo += CheckTimeFormat(_T("DataReadResp"), PkgData_Node_Devices, PkgData_Node_Services, 
		_T("$DataList"), _T("$TimeStamp"), m_strTimeStamp);
	m_strRangeOut += CheckTimeFormat(_T("DataReadResp"), PkgData_Node_Devices, PkgData_Node_Services, 
		_T("$DataList"), _T("$TimeStamp"), m_strTimeStamp);

	char* pTemp = const_cast<char*>(m_strQuality.GetString());
	//lmy,20230915修改
	//if((pTemp[0] != '0' || pTemp[0] != '1') && (pTemp[1] != '0' || pTemp[1] != '1'))
	if((pTemp[0] != '0' && pTemp[0] != '1') || (pTemp[1] != '0' && pTemp[1] != '1'))
	{
		QString strTemp;
		strTemp = QString(_T("【错误】【超过范围】DataReadResp：[%1]=>[%2$%3$%4$%5]字段超出范围;\n")).arg(PkgData_Node_Data) 
			.arg(PkgData_Node_Devices).arg(PkgData_Node_Services).arg(PkgData_Node_DataList).arg(PkgData_Node_Quality);
		m_strErrorInfo += strTemp;
		m_strRangeOut += strTemp;
	}

	return 0;
}

long CPkg_DataReadRespDevSvcDL::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
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

long CPkg_DataReadRespDevSvcDL::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPkg_DataReadRespDevSvcDL::InitAfterRead()
{
}

BOOL CPkg_DataReadRespDevSvcDL::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_DataReadRespDevSvcDL *p = (CPkg_DataReadRespDevSvcDL*)pObj;

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

BOOL CPkg_DataReadRespDevSvcDL::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_DataReadRespDevSvcDL *p = (CPkg_DataReadRespDevSvcDL*)pDest;

	p->m_strDataRefer = m_strDataRefer;
	p->m_strValue = m_strValue;
	p->m_strAngle = m_strAngle;
	p->m_strTimeStamp = m_strTimeStamp;
	p->m_strQuality = m_strQuality;
	return TRUE;
}

CBaseObject* CPkg_DataReadRespDevSvcDL::Clone()
{
	CPkg_DataReadRespDevSvcDL *p = new CPkg_DataReadRespDevSvcDL();
	Copy(p);
	return p;
}

long CPkg_DataReadRespDevSvcDL::InitListCtrlColumns(CListCtrl *pListCtrl)
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

long CPkg_DataReadRespDevSvcDL::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
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

BOOL CPkg_DataReadRespDevSvcDL::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_DataReadRespDevSvcDL::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_DataReadRespDevSvcDL::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
