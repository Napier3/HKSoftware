//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_BenchTestApp.cpp  CIot_BenchTestApp


#include "stdafx.h"
#include "Iot_BenchTestApp.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_BenchTestApp::CIot_BenchTestApp()
{
	//初始化属性
	m_nIndex_Bench_Testapp = 0;
	m_nIndex_Testapp = 0;
	m_nIndex_Bench = 0;

	//初始化成员变量
}

CIot_BenchTestApp::~CIot_BenchTestApp()
{
}

long CIot_BenchTestApp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Bench_TestappKey, oNode, m_nIndex_Bench_Testapp);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TestappKey, oNode, m_nIndex_Testapp);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_BenchKey, oNode, m_nIndex_Bench);
	return 0;
}

long CIot_BenchTestApp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_Bench_TestappKey, oElement, m_nIndex_Bench_Testapp);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TestappKey, oElement, m_nIndex_Testapp);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_BenchKey, oElement, m_nIndex_Bench);
	return 0;
}

long CIot_BenchTestApp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Bench_Testapp);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Testapp);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Bench);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Bench_Testapp);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Testapp);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Bench);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Bench_Testapp);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Testapp);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Bench);
	}
	return 0;
}

void CIot_BenchTestApp::InitAfterRead()
{
}

BOOL CIot_BenchTestApp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIot_BenchTestApp *p = (CIot_BenchTestApp*)pObj;

	if(m_nIndex_Bench_Testapp != p->m_nIndex_Bench_Testapp)
	{
		return FALSE;
	}

	if(m_nIndex_Testapp != p->m_nIndex_Testapp)
	{
		return FALSE;
	}

	if(m_nIndex_Bench != p->m_nIndex_Bench)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_BenchTestApp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIot_BenchTestApp *p = (CIot_BenchTestApp*)pDest;

	p->m_nIndex_Bench_Testapp = m_nIndex_Bench_Testapp;
	p->m_nIndex_Testapp = m_nIndex_Testapp;
	p->m_nIndex_Bench = m_nIndex_Bench;
	return TRUE;
}

CBaseObject* CIot_BenchTestApp::Clone()
{
	CIot_BenchTestApp *p = new CIot_BenchTestApp();
	Copy(p);
	return p;
}

CBaseObject* CIot_BenchTestApp::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_BenchTestApp *p = new CIot_BenchTestApp();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_BenchTestApp::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Bench_TestappKey, m_nIndex_Bench_Testapp);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TestappKey, m_nIndex_Testapp);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_BenchKey, m_nIndex_Bench);
	pRecordset->GetFieldValue(pXmlKeys->m_strModel_TestappKey, m_strName);
	pRecordset->GetFieldValue(pXmlKeys->m_strSn_TestappKey, m_strID);
	return 0;
}

long CIot_BenchTestApp::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Bench_TestappKey, m_nIndex_Bench_Testapp);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TestappKey, m_nIndex_Testapp);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_BenchKey, m_nIndex_Bench);
	pRecordset->SetFieldValue(pXmlKeys->m_strModel_TestappKey, m_strName);
	pRecordset->SetFieldValue(pXmlKeys->m_strSn_TestappKey, m_strID);
	return 0;
}

BOOL CIot_BenchTestApp::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CNR_IOTMNGRXmlRWKeys *pXmlKeys = (CNR_IOTMNGRXmlRWKeys*)pXmlRWKeys;

	if (oPKeyValue.nClassID == IOTCLASSID_CIOT_TESTAPP)
	{
		m_nIndex_Testapp = *oPKeyValue.oKeyValRef.pnValue;
	}
	else if (oPKeyValue.nClassID == IOTCLASSID_CIOT_BENCH)
	{
		m_nIndex_Bench = *oPKeyValue.oKeyValRef.pnValue;
	}

	return TRUE;
}

