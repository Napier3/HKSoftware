//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_ConStatusResp_ContStatu.cpp  CPkg_ConStatusResp_ContStatu


#include "stdafx.h"
#include "Pkg_ConStatusResp_ContStatu.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CPkg_ConStatusResp_ContStatu::CPkg_ConStatusResp_ContStatu()
{
	//初始化属性

	//初始化成员变量
	m_arrayNotMust[0] = PkgData_Node_Version;
	m_arrayNotMust[1] = PkgData_Node_CpuRate;
	m_arrayNotMust[2] = PkgData_Node_MemUsed;
	m_arrayNotMust[3] = PkgData_Node_DiskUsed;
	m_arrayNotMust[4] = PkgData_Node_Ip;
	m_arrayNotMust[5] = PkgData_Node_LifeTime;
	m_arrayNotMust[6] = PkgData_Node_Image;
}

CPkg_ConStatusResp_ContStatu::~CPkg_ConStatusResp_ContStatu()
{
}

BOOL CPkg_ConStatusResp_ContStatu::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
{
	//在这里判断报文中的String字段是否有误
	QString strTemp;
	CString strAttr(strAttrName);
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

		strTemp = QString("【错误】【必需项缺失】ConStatusResp：[%1]=>[%2$%3]必需字段缺失;\n").arg(PkgData_Node_Data).arg(PkgData_Node_ContStatus).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString("【错误】【必需项错误】ConStatusResp：[%s]=>[%s$%s]字段类型错误;\n").arg(PkgData_Node_Data).arg(PkgData_Node_ContStatus).arg(strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CPkg_ConStatusResp_ContStatu::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strContainerKey, oNode, m_strContainer);
	xml_GetAttibuteValue(pXmlKeys->m_strVersionKey, oNode, m_strVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strStateKey, oNode, m_strState);
	xml_GetAttibuteValue(pXmlKeys->m_strCpuRateKey, oNode, m_strCpuRate);
	xml_GetAttibuteValue(pXmlKeys->m_strMemUsedKey, oNode, m_strMemUsed);
	xml_GetAttibuteValue(pXmlKeys->m_strDiskUsedKey, oNode, m_strDiskUsed);
	xml_GetAttibuteValue(pXmlKeys->m_strIpKey, oNode, m_strIp);
	xml_GetAttibuteValue(pXmlKeys->m_strCreatedKey, oNode, m_strCreated);
	xml_GetAttibuteValue(pXmlKeys->m_strStartedKey, oNode, m_strStarted);
	xml_GetAttibuteValue(pXmlKeys->m_strLifeTimeKey, oNode, m_strLifeTime);
	xml_GetAttibuteValue(pXmlKeys->m_strImageKey, oNode, m_strImage);

	m_strErrorInfo += CheckRangePer(_T("ConStatusResp"), PkgData_Node_ContStatus, _T("CpuRate"), m_strCpuRate);
	m_strErrorInfo += CheckRangePer(_T("ConStatusResp"), PkgData_Node_ContStatus, _T("MemUsed"), m_strMemUsed);
	m_strErrorInfo += CheckRangePer(_T("ConStatusResp"), PkgData_Node_ContStatus, _T("DiskUsed"), m_strDiskUsed);
	m_strErrorInfo += CheckTimeFormat(_T("ConStatusResp"), PkgData_Node_ContStatus, _T("Created"), _T(""), _T(""), m_strCreated);
	m_strErrorInfo += CheckTimeFormat(_T("ConStatusResp"), PkgData_Node_ContStatus, _T("Started"), _T(""), _T(""), m_strStarted);

	m_strRangeOut += CheckRangePer(_T("ConStatusResp"), PkgData_Node_ContStatus, _T("CpuRate"), m_strCpuRate);
	m_strRangeOut += CheckRangePer(_T("ConStatusResp"), PkgData_Node_ContStatus, _T("MemUsed"), m_strMemUsed);
	m_strRangeOut += CheckRangePer(_T("ConStatusResp"), PkgData_Node_ContStatus, _T("DiskUsed"), m_strDiskUsed);
	m_strRangeOut += CheckTimeFormat(_T("ConStatusResp"), PkgData_Node_ContStatus, _T("Created"), _T(""), _T(""), m_strCreated);
	m_strRangeOut += CheckTimeFormat(_T("ConStatusResp"), PkgData_Node_ContStatus, _T("Started"), _T(""), _T(""), m_strStarted);

	return 0;  
}

long CPkg_ConStatusResp_ContStatu::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strContainerKey, oElement, m_strContainer);
	xml_SetAttributeValue(pXmlKeys->m_strVersionKey, oElement, m_strVersion);
	xml_SetAttributeValue(pXmlKeys->m_strStateKey, oElement, m_strState);
	xml_SetAttributeValue(pXmlKeys->m_strCpuRateKey, oElement, m_strCpuRate);
	xml_SetAttributeValue(pXmlKeys->m_strMemUsedKey, oElement, m_strMemUsed);
	xml_SetAttributeValue(pXmlKeys->m_strDiskUsedKey, oElement, m_strDiskUsed);
	xml_SetAttributeValue(pXmlKeys->m_strIpKey, oElement, m_strIp);
	xml_SetAttributeValue(pXmlKeys->m_strCreatedKey, oElement, m_strCreated);
	xml_SetAttributeValue(pXmlKeys->m_strStartedKey, oElement, m_strStarted);
	xml_SetAttributeValue(pXmlKeys->m_strLifeTimeKey, oElement, m_strLifeTime);
	xml_SetAttributeValue(pXmlKeys->m_strImageKey, oElement, m_strImage);
	return 0;
}

long CPkg_ConStatusResp_ContStatu::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strContainer);
		BinarySerializeCalLen(oBinaryBuffer, m_strVersion);
		BinarySerializeCalLen(oBinaryBuffer, m_strState);
		BinarySerializeCalLen(oBinaryBuffer, m_strCpuRate);
		BinarySerializeCalLen(oBinaryBuffer, m_strMemUsed);
		BinarySerializeCalLen(oBinaryBuffer, m_strDiskUsed);
		BinarySerializeCalLen(oBinaryBuffer, m_strIp);
		BinarySerializeCalLen(oBinaryBuffer, m_strCreated);
		BinarySerializeCalLen(oBinaryBuffer, m_strStarted);
		BinarySerializeCalLen(oBinaryBuffer, m_strLifeTime);
		BinarySerializeCalLen(oBinaryBuffer, m_strImage);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strContainer);
		BinarySerializeRead(oBinaryBuffer, m_strVersion);
		BinarySerializeRead(oBinaryBuffer, m_strState);
		BinarySerializeRead(oBinaryBuffer, m_strCpuRate);
		BinarySerializeRead(oBinaryBuffer, m_strMemUsed);
		BinarySerializeRead(oBinaryBuffer, m_strDiskUsed);
		BinarySerializeRead(oBinaryBuffer, m_strIp);
		BinarySerializeRead(oBinaryBuffer, m_strCreated);
		BinarySerializeRead(oBinaryBuffer, m_strStarted);
		BinarySerializeRead(oBinaryBuffer, m_strLifeTime);
		BinarySerializeRead(oBinaryBuffer, m_strImage);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strContainer);
		BinarySerializeWrite(oBinaryBuffer, m_strVersion);
		BinarySerializeWrite(oBinaryBuffer, m_strState);
		BinarySerializeWrite(oBinaryBuffer, m_strCpuRate);
		BinarySerializeWrite(oBinaryBuffer, m_strMemUsed);
		BinarySerializeWrite(oBinaryBuffer, m_strDiskUsed);
		BinarySerializeWrite(oBinaryBuffer, m_strIp);
		BinarySerializeWrite(oBinaryBuffer, m_strCreated);
		BinarySerializeWrite(oBinaryBuffer, m_strStarted);
		BinarySerializeWrite(oBinaryBuffer, m_strLifeTime);
		BinarySerializeWrite(oBinaryBuffer, m_strImage);
	}
	return 0;
}

void CPkg_ConStatusResp_ContStatu::InitAfterRead()
{
}

BOOL CPkg_ConStatusResp_ContStatu::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_ConStatusResp_ContStatu *p = (CPkg_ConStatusResp_ContStatu*)pObj;

	if(m_strContainer != p->m_strContainer)
	{
		return FALSE;
	}

	if(m_strVersion != p->m_strVersion)
	{
		return FALSE;
	}

	if(m_strState != p->m_strState)
	{
		return FALSE;
	}

	if(m_strCpuRate != p->m_strCpuRate)
	{
		return FALSE;
	}

	if(m_strMemUsed != p->m_strMemUsed)
	{
		return FALSE;
	}

	if(m_strDiskUsed != p->m_strDiskUsed)
	{
		return FALSE;
	}

	if(m_strIp != p->m_strIp)
	{
		return FALSE;
	}

	if(m_strCreated != p->m_strCreated)
	{
		return FALSE;
	}

	if(m_strStarted != p->m_strStarted)
	{
		return FALSE;
	}

	if(m_strLifeTime != p->m_strLifeTime)
	{
		return FALSE;
	}

	if(m_strImage != p->m_strImage)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CPkg_ConStatusResp_ContStatu::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_ConStatusResp_ContStatu *p = (CPkg_ConStatusResp_ContStatu*)pDest;

	p->m_strContainer = m_strContainer;
	p->m_strVersion = m_strVersion;
	p->m_strState = m_strState;
	p->m_strCpuRate = m_strCpuRate;
	p->m_strMemUsed = m_strMemUsed;
	p->m_strDiskUsed = m_strDiskUsed;
	p->m_strIp = m_strIp;
	p->m_strCreated = m_strCreated;
	p->m_strStarted = m_strStarted;
	p->m_strLifeTime = m_strLifeTime;
	p->m_strImage = m_strImage;
	return TRUE;
}

CBaseObject* CPkg_ConStatusResp_ContStatu::Clone()
{
	CPkg_ConStatusResp_ContStatu *p = new CPkg_ConStatusResp_ContStatu();
	Copy(p);
	return p;
}

CBaseObject* CPkg_ConStatusResp_ContStatu::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CPkg_ConStatusResp_ContStatu *p = new CPkg_ConStatusResp_ContStatu();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CPkg_ConStatusResp_ContStatu::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_ConStatusResp_ContStatu::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_ConStatusResp_ContStatu::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
long CPkg_ConStatusResp_ContStatu::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_ReadFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strContainerKey, m_strContainer);
	pRecordset->GetFieldValue(pXmlKeys->m_strVersionKey, m_strVersion);
	pRecordset->GetFieldValue(pXmlKeys->m_strStateKey, m_strState);
	pRecordset->GetFieldValue(pXmlKeys->m_strCpuRateKey, m_strCpuRate);
	pRecordset->GetFieldValue(pXmlKeys->m_strMemUsedKey, m_strMemUsed);
	pRecordset->GetFieldValue(pXmlKeys->m_strDiskUsedKey, m_strDiskUsed);
	pRecordset->GetFieldValue(pXmlKeys->m_strIpKey, m_strIp);
	pRecordset->GetFieldValue(pXmlKeys->m_strCreatedKey, m_strCreated);
	pRecordset->GetFieldValue(pXmlKeys->m_strStartedKey, m_strStarted);
	pRecordset->GetFieldValue(pXmlKeys->m_strLifeTimeKey, m_strLifeTime);
	pRecordset->GetFieldValue(pXmlKeys->m_strImageKey, m_strImage);
	return 0;
}

long CPkg_ConStatusResp_ContStatu::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::DB_WriteFields(pRecordset, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strContainerKey, m_strContainer);
	pRecordset->SetFieldValue(pXmlKeys->m_strVersionKey, m_strVersion);
	pRecordset->SetFieldValue(pXmlKeys->m_strStateKey, m_strState);
	pRecordset->SetFieldValue(pXmlKeys->m_strCpuRateKey, m_strCpuRate);
	pRecordset->SetFieldValue(pXmlKeys->m_strMemUsedKey, m_strMemUsed);
	pRecordset->SetFieldValue(pXmlKeys->m_strDiskUsedKey, m_strDiskUsed);
	pRecordset->SetFieldValue(pXmlKeys->m_strIpKey, m_strIp);
	pRecordset->SetFieldValue(pXmlKeys->m_strCreatedKey, m_strCreated);
	pRecordset->SetFieldValue(pXmlKeys->m_strStartedKey, m_strStarted);
	pRecordset->SetFieldValue(pXmlKeys->m_strLifeTimeKey, m_strLifeTime);
	pRecordset->SetFieldValue(pXmlKeys->m_strImageKey, m_strImage);
	return 0;
}

