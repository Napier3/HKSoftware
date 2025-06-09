//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_DeviceItemRslt.cpp  CIot_DeviceItemRslt


#include "stdafx.h"
#include "Iot_DeviceItemRslt.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_DeviceItemRslt::CIot_DeviceItemRslt()
{
	//初始化属性
	m_nIndex_Item_Rslt = 0;
	m_nIndex_Test = 0;
	m_nIndex_Device = 0;
	m_nIndex_Item = 0;
	m_nState = 0;
	m_nRsltjdg = 0;
	m_nSelect_State = 0;
	m_nIndex_Bench = 0;

	//初始化成员变量
}

CIot_DeviceItemRslt::~CIot_DeviceItemRslt()
{
}

long CIot_DeviceItemRslt::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Item_RsltKey, oNode, m_nIndex_Item_Rslt);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TestKey, oNode, m_nIndex_Test);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_DeviceKey, oNode, m_nIndex_Device);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_ItemKey, oNode, m_nIndex_Item);
	xml_GetAttibuteValue(pXmlKeys->m_strStateKey, oNode, m_nState);
	xml_GetAttibuteValue(pXmlKeys->m_strRsltjdgKey, oNode, m_nRsltjdg);
	xml_GetAttibuteValue(pXmlKeys->m_strRsltdscKey, oNode, m_strRsltdsc);
	xml_GetAttibuteValue(pXmlKeys->m_strFile_ReportKey, oNode, m_strFile_Report);
	xml_GetAttibuteValue(pXmlKeys->m_strFile_PkgsKey, oNode, m_strFile_Pkgs);
	xml_GetAttibuteValue(pXmlKeys->m_strSelect_StateKey, oNode, m_nSelect_State);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_BenchKey, oNode, m_nIndex_Bench);
	xml_GetAttibuteValue(pXmlKeys->m_strFile_Report_SKey, oNode, m_strFile_Report_S);
	xml_GetAttibuteValue(pXmlKeys->m_strFile_Pkgs_SKey, oNode, m_strFile_Pkgs_S);
	return 0;
}

long CIot_DeviceItemRslt::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_Item_RsltKey, oElement, m_nIndex_Item_Rslt);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TestKey, oElement, m_nIndex_Test);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_DeviceKey, oElement, m_nIndex_Device);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_ItemKey, oElement, m_nIndex_Item);
	xml_SetAttributeValue(pXmlKeys->m_strStateKey, oElement, m_nState);
	xml_SetAttributeValue(pXmlKeys->m_strRsltjdgKey, oElement, m_nRsltjdg);
	xml_SetAttributeValue(pXmlKeys->m_strRsltdscKey, oElement, m_strRsltdsc);
	xml_SetAttributeValue(pXmlKeys->m_strFile_ReportKey, oElement, m_strFile_Report);
	xml_SetAttributeValue(pXmlKeys->m_strFile_PkgsKey, oElement, m_strFile_Pkgs);
	xml_SetAttributeValue(pXmlKeys->m_strSelect_StateKey, oElement, m_nSelect_State);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_BenchKey, oElement, m_nIndex_Bench);
	xml_SetAttributeValue(pXmlKeys->m_strFile_Report_SKey, oElement, m_strFile_Report_S);
	xml_SetAttributeValue(pXmlKeys->m_strFile_Pkgs_SKey, oElement, m_strFile_Pkgs_S);
	return 0;
}

long CIot_DeviceItemRslt::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Item_Rslt);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Test);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Item);
		BinarySerializeCalLen(oBinaryBuffer, m_nState);
		BinarySerializeCalLen(oBinaryBuffer, m_nRsltjdg);
		BinarySerializeCalLen(oBinaryBuffer, m_strRsltdsc);
		BinarySerializeCalLen(oBinaryBuffer, m_strFile_Report);
		BinarySerializeCalLen(oBinaryBuffer, m_strFile_Pkgs);
		BinarySerializeCalLen(oBinaryBuffer, m_nSelect_State);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Bench);
		BinarySerializeCalLen(oBinaryBuffer, m_strFile_Report_S);
		BinarySerializeCalLen(oBinaryBuffer, m_strFile_Pkgs_S);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Item_Rslt);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Test);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Item);
		BinarySerializeRead(oBinaryBuffer, m_nState);
		BinarySerializeRead(oBinaryBuffer, m_nRsltjdg);
		BinarySerializeRead(oBinaryBuffer, m_strRsltdsc);
		BinarySerializeRead(oBinaryBuffer, m_strFile_Report);
		BinarySerializeRead(oBinaryBuffer, m_strFile_Pkgs);
		BinarySerializeRead(oBinaryBuffer, m_nSelect_State);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Bench);
		BinarySerializeRead(oBinaryBuffer, m_strFile_Report_S);
		BinarySerializeRead(oBinaryBuffer, m_strFile_Pkgs_S);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Item_Rslt);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Test);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Device);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Item);
		BinarySerializeWrite(oBinaryBuffer, m_nState);
		BinarySerializeWrite(oBinaryBuffer, m_nRsltjdg);
		BinarySerializeWrite(oBinaryBuffer, m_strRsltdsc);
		BinarySerializeWrite(oBinaryBuffer, m_strFile_Report);
		BinarySerializeWrite(oBinaryBuffer, m_strFile_Pkgs);
		BinarySerializeWrite(oBinaryBuffer, m_nSelect_State);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Bench);
		BinarySerializeWrite(oBinaryBuffer, m_strFile_Report_S);
		BinarySerializeWrite(oBinaryBuffer, m_strFile_Pkgs_S);
	}
	return 0;
}

void CIot_DeviceItemRslt::InitAfterRead()
{
}

BOOL CIot_DeviceItemRslt::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIot_DeviceItemRslt *p = (CIot_DeviceItemRslt*)pObj;

	if(m_nIndex_Item_Rslt != p->m_nIndex_Item_Rslt)
	{
		return FALSE;
	}

	if(m_nIndex_Test != p->m_nIndex_Test)
	{
		return FALSE;
	}

	if(m_nIndex_Device != p->m_nIndex_Device)
	{
		return FALSE;
	}

	if(m_nIndex_Item != p->m_nIndex_Item)
	{
		return FALSE;
	}

	if(m_nState != p->m_nState)
	{
		return FALSE;
	}

	if(m_nRsltjdg != p->m_nRsltjdg)
	{
		return FALSE;
	}

	if(m_strRsltdsc != p->m_strRsltdsc)
	{
		return FALSE;
	}

	if(m_strFile_Report != p->m_strFile_Report)
	{
		return FALSE;
	}

	if(m_strFile_Pkgs != p->m_strFile_Pkgs)
	{
		return FALSE;
	}

	if(m_nSelect_State != p->m_nSelect_State)
	{
		return FALSE;
	}

	if(m_nIndex_Bench != p->m_nIndex_Bench)
	{
		return FALSE;
	}

	if(m_strFile_Report_S != p->m_strFile_Report_S)
	{
		return FALSE;
	}

	if(m_strFile_Pkgs_S != p->m_strFile_Pkgs_S)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_DeviceItemRslt::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIot_DeviceItemRslt *p = (CIot_DeviceItemRslt*)pDest;

	p->m_nIndex_Item_Rslt = m_nIndex_Item_Rslt;
	p->m_nIndex_Test = m_nIndex_Test;
	p->m_nIndex_Device = m_nIndex_Device;
	p->m_nIndex_Item = m_nIndex_Item;
	p->m_nState = m_nState;
	p->m_nRsltjdg = m_nRsltjdg;
	p->m_strRsltdsc = m_strRsltdsc;
	p->m_strFile_Report = m_strFile_Report;
	p->m_strFile_Pkgs = m_strFile_Pkgs;
	p->m_nSelect_State = m_nSelect_State;
	p->m_nIndex_Bench = m_nIndex_Bench;
	p->m_strFile_Report_S = m_strFile_Report_S;
	p->m_strFile_Pkgs_S = m_strFile_Pkgs_S;
	return TRUE;
}

CBaseObject* CIot_DeviceItemRslt::Clone()
{
	CIot_DeviceItemRslt *p = new CIot_DeviceItemRslt();
	Copy(p);
	return p;
}

CBaseObject* CIot_DeviceItemRslt::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_DeviceItemRslt *p = new CIot_DeviceItemRslt();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_DeviceItemRslt::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Item_RsltKey, m_nIndex_Item_Rslt);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TestKey, m_nIndex_Test);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_DeviceKey, m_nIndex_Device);
	pRecordset->GetFieldValue(pXmlKeys->m_strName_Item_PathKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strId_Item_PathKey, m_strID);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_ItemKey, m_nIndex_Item);
	pRecordset->GetFieldValue(pXmlKeys->m_strStateKey, m_nState);
	pRecordset->GetFieldValue(pXmlKeys->m_strRsltjdgKey, m_nRsltjdg);
	pRecordset->GetFieldValue(pXmlKeys->m_strRsltdscKey, m_strRsltdsc);
	pRecordset->GetFieldValue(pXmlKeys->m_strFile_ReportKey, m_strFile_Report);
	pRecordset->GetFieldValue(pXmlKeys->m_strFile_PkgsKey, m_strFile_Pkgs);
	pRecordset->GetFieldValue(pXmlKeys->m_strSelect_StateKey, m_nSelect_State);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_BenchKey, m_nIndex_Bench);
	pRecordset->GetFieldValue(pXmlKeys->m_strFile_Report_SKey, m_strFile_Report_S);
	pRecordset->GetFieldValue(pXmlKeys->m_strFile_Pkgs_SKey, m_strFile_Pkgs_S);
	return 0;
}

long CIot_DeviceItemRslt::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Item_RsltKey, m_nIndex_Item_Rslt);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TestKey, m_nIndex_Test);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_DeviceKey, m_nIndex_Device);
	pRecordset->SetFieldValue(pXmlKeys->m_strName_Item_PathKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strId_Item_PathKey, m_strID);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_ItemKey, m_nIndex_Item);
	pRecordset->SetFieldValue(pXmlKeys->m_strStateKey, m_nState);
	pRecordset->SetFieldValue(pXmlKeys->m_strRsltjdgKey, m_nRsltjdg);
	pRecordset->SetFieldValue(pXmlKeys->m_strRsltdscKey, m_strRsltdsc);
	pRecordset->SetFieldValue(pXmlKeys->m_strFile_ReportKey, m_strFile_Report);
	pRecordset->SetFieldValue(pXmlKeys->m_strFile_PkgsKey, m_strFile_Pkgs);
	pRecordset->SetFieldValue(pXmlKeys->m_strSelect_StateKey, m_nSelect_State);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_BenchKey, m_nIndex_Bench);
	pRecordset->SetFieldValue(pXmlKeys->m_strFile_Report_SKey, m_strFile_Report_S);
	pRecordset->SetFieldValue(pXmlKeys->m_strFile_Pkgs_SKey, m_strFile_Pkgs_S);
	return 0;
}

BOOL CIot_DeviceItemRslt::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == IOTCLASSID_CIOT_DEVICE)
	{
		m_nIndex_Device = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

