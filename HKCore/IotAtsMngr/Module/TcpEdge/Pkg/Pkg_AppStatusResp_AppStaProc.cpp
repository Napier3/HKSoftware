//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Pkg_AppStatusResp_AppStaProc.cpp  CPkg_AppStatusResp_AppStaProc


#include "stdafx.h"
#include "Pkg_AppStatusResp_AppStaProc.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CPkg_AppStatusResp_AppStaProc::CPkg_AppStatusResp_AppStaProc()
{
	//初始化属性

	//初始化成员变量
	m_arrayNotMust[0] = PkgData_Node_CpuRate;
	m_arrayNotMust[1] = PkgData_Node_MemUsed;
	m_arrayNotMust[2] = PkgData_Node_StartTime;
}

CPkg_AppStatusResp_AppStaProc::~CPkg_AppStatusResp_AppStaProc()
{
}

BOOL CPkg_AppStatusResp_AppStaProc::xml_GetAttibuteValue(const BSTR strAttrName, CXmlRWNodeBase &oNode, CString &strAttrVal)
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
		strTemp = QString(_T("【错误】【必需项缺失】AppStatusResp：[%1]=>[%2$%3$%4]必需字段缺失;\n")).arg(PkgData_Node_Data).arg(PkgData_Node_AppStatus).arg(PkgData_Node_Process, strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityLack += strTemp;
	}
	else if(oNode.xml_GetAttibuteType(strAttrName) != CJSON_String)
	{
		//值存在时检查类型是否正确
		strTemp = QString(_T("【错误】【必需项错误】AppStatusResp：[%1]=>[%2$%3$%4]字段类型错误;\n")).arg(PkgData_Node_Data).arg(PkgData_Node_AppStatus).arg(PkgData_Node_Process, strAttr);
		m_strErrorInfo += strTemp;
		m_strNecessityErr += strTemp;
	}

	return bRet;
}

long CPkg_AppStatusResp_AppStaProc::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strSrvIndexKey, oNode, m_strSrvIndex);
	xml_GetAttibuteValue(pXmlKeys->m_strSrvNameKey, oNode, m_strSrvName);
	xml_GetAttibuteValue(pXmlKeys->m_strSrvEnableKey, oNode, m_strSrvEnable);
	xml_GetAttibuteValue(pXmlKeys->m_strSrvStatusKey, oNode, m_strSrvStatus);
	xml_GetAttibuteValue(pXmlKeys->m_strCpuRateKey, oNode, m_strCpuRate);
	xml_GetAttibuteValue(pXmlKeys->m_strMemUsedKey, oNode, m_strMemUsed);
	xml_GetAttibuteValue(pXmlKeys->m_strStartTimeKey, oNode, m_strStartTime);
// 	xml_GetAttibuteValue(pXmlKeys->m_strSrvNumberKey, oNode, m_strSrvNumber);
// 	xml_GetAttibuteValue(pXmlKeys->m_strCpuLmtKey, oNode, m_strCpuLmt);
// 	xml_GetAttibuteValue(pXmlKeys->m_strMemLmtKey, oNode, m_strMemLmt);

	//lmy,20230915修改
	//if(m_strSrvEnable != _T("yes") || m_strSrvEnable != _T("no"))
	if(m_strSrvEnable != _T("yes") && m_strSrvEnable != _T("no"))
	{
		QString strTemp;
		//strTemp = QString(_T("【错误】【超过范围】GetHisEventResp：[%1]=>[%2$%3$%4]字段超出范围;\n")).arg(PkgData_Node_Data).arg(PkgData_Node_AppStatus).arg(PkgData_Node_Process).arg(PkgData_Node_SrvEnable);
		strTemp = QString(_T("【错误】【超过范围】AppStatusResp：[%1]=>[%2$%3$%4]字段超出范围;\n")).arg(PkgData_Node_Data).arg(PkgData_Node_AppStatus).arg(PkgData_Node_Process).arg(PkgData_Node_SrvEnable);
		m_strErrorInfo += strTemp;
		m_strRangeOut += strTemp;
	}

	//if(m_strSrvStatus != _T("running ") || m_strSrvStatus != _T("stopped"))
	if((m_strSrvStatus != _T("running")) && (m_strSrvStatus != _T("stopped")))
	{
		CString strTemp;
		//strTemp = QString(_T("【错误】【超过范围】GetHisEventResp：[%1]=>[%2$%3$%4]字段超出范围;\n")).arg(PkgData_Node_Data) 
		//	.arg(PkgData_Node_AppStatus).arg(PkgData_Node_Process).arg(PkgData_Node_SrvStatus);
		strTemp = QString(_T("【错误】【超过范围】AppStatusResp：[%1]=>[%2$%3$%4]字段超出范围;\n")).arg(PkgData_Node_Data) 
				.arg(PkgData_Node_AppStatus).arg(PkgData_Node_Process).arg(PkgData_Node_SrvStatus);
		m_strErrorInfo += strTemp;
		m_strRangeOut += strTemp;
	}

	//m_strErrorInfo += CheckRangePer(_T("GetHisEventResp"), PkgData_Node_AppStatus, _T("Process$CpuRate"), m_strCpuRate);
	//m_strRangeOut += CheckRangePer(_T("GetHisEventResp"), PkgData_Node_AppStatus, _T("Process$CpuRate"), m_strCpuRate);
	m_strErrorInfo += CheckRangePer(_T("AppStatusResp"), PkgData_Node_AppStatus, _T("Process$CpuRate"), m_strCpuRate);
	m_strRangeOut += CheckRangePer(_T("AppStatusResp"), PkgData_Node_AppStatus, _T("Process$CpuRate"), m_strCpuRate);

	return 0;
}

long CPkg_AppStatusResp_AppStaProc::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPxPkgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strSrvIndexKey, oElement, m_strSrvIndex);
	xml_SetAttributeValue(pXmlKeys->m_strSrvNameKey, oElement, m_strSrvName);
	xml_SetAttributeValue(pXmlKeys->m_strSrvEnableKey, oElement, m_strSrvEnable);
	xml_SetAttributeValue(pXmlKeys->m_strSrvStatusKey, oElement, m_strSrvStatus);
	xml_SetAttributeValue(pXmlKeys->m_strCpuRateKey, oElement, m_strCpuRate);
	xml_SetAttributeValue(pXmlKeys->m_strMemUsedKey, oElement, m_strMemUsed);
	xml_SetAttributeValue(pXmlKeys->m_strStartTimeKey, oElement, m_strStartTime);
//	xml_SetAttributeValue(pXmlKeys->m_strSrvNumberKey, oElement, m_strSrvNumber);
//	xml_SetAttributeValue(pXmlKeys->m_strCpuLmtKey, oElement, m_strCpuLmt);
//	xml_SetAttributeValue(pXmlKeys->m_strMemLmtKey, oElement, m_strMemLmt);

	return 0;
}

long CPkg_AppStatusResp_AppStaProc::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CPxPkgDataBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strSrvIndex);
		BinarySerializeCalLen(oBinaryBuffer, m_strSrvName);
		BinarySerializeCalLen(oBinaryBuffer, m_strSrvEnable);
		BinarySerializeCalLen(oBinaryBuffer, m_strSrvStatus);
		BinarySerializeCalLen(oBinaryBuffer, m_strCpuRate);
		BinarySerializeCalLen(oBinaryBuffer, m_strMemUsed);
		BinarySerializeCalLen(oBinaryBuffer, m_strStartTime);
// 		BinarySerializeCalLen(oBinaryBuffer, m_strSrvNumber);
// 		BinarySerializeCalLen(oBinaryBuffer, m_strCpuLmt);
// 		BinarySerializeCalLen(oBinaryBuffer, m_strMemLmt);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strSrvIndex);
		BinarySerializeRead(oBinaryBuffer, m_strSrvName);
		BinarySerializeRead(oBinaryBuffer, m_strSrvEnable);
		BinarySerializeRead(oBinaryBuffer, m_strSrvStatus);
		BinarySerializeRead(oBinaryBuffer, m_strCpuRate);
		BinarySerializeRead(oBinaryBuffer, m_strMemUsed);
		BinarySerializeRead(oBinaryBuffer, m_strStartTime);
// 		BinarySerializeRead(oBinaryBuffer, m_strSrvNumber);
// 		BinarySerializeRead(oBinaryBuffer, m_strCpuLmt);
// 		BinarySerializeRead(oBinaryBuffer, m_strMemLmt);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strSrvIndex);
		BinarySerializeWrite(oBinaryBuffer, m_strSrvName);
		BinarySerializeWrite(oBinaryBuffer, m_strSrvEnable);
		BinarySerializeWrite(oBinaryBuffer, m_strSrvStatus);
		BinarySerializeWrite(oBinaryBuffer, m_strCpuRate);
		BinarySerializeWrite(oBinaryBuffer, m_strMemUsed);
		BinarySerializeWrite(oBinaryBuffer, m_strStartTime);
// 		BinarySerializeWrite(oBinaryBuffer, m_strSrvNumber);
// 		BinarySerializeWrite(oBinaryBuffer, m_strCpuLmt);
// 		BinarySerializeWrite(oBinaryBuffer, m_strMemLmt);
	}
	return 0;
}

void CPkg_AppStatusResp_AppStaProc::InitAfterRead()
{
}

BOOL CPkg_AppStatusResp_AppStaProc::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CPxPkgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CPkg_AppStatusResp_AppStaProc *p = (CPkg_AppStatusResp_AppStaProc*)pObj;

	if(m_strSrvIndex != p->m_strSrvIndex)
	{
		return FALSE;
	}

	if(m_strSrvName != p->m_strSrvName)
	{
		return FALSE;
	}

	if(m_strSrvEnable != p->m_strSrvEnable)
	{
		return FALSE;
	}

	if(m_strSrvStatus != p->m_strSrvStatus)
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

	if(m_strStartTime != p->m_strStartTime)
	{
		return FALSE;
	}

// 	if(m_strSrvNumber != p->m_strSrvNumber)
// 	{
// 		return FALSE;
// 	}
// 
// 	if(m_strCpuLmt != p->m_strCpuLmt)
// 	{
// 		return FALSE;
// 	}
// 
// 	if(m_strMemLmt != p->m_strMemLmt)
// 	{
// 		return FALSE;
// 	}

	return TRUE;
}

BOOL CPkg_AppStatusResp_AppStaProc::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPxPkgDataBase::CopyOwn(pDest);

	CPkg_AppStatusResp_AppStaProc *p = (CPkg_AppStatusResp_AppStaProc*)pDest;

	p->m_strSrvIndex = m_strSrvIndex;
	p->m_strSrvName = m_strSrvName;
	p->m_strSrvEnable = m_strSrvEnable;
	p->m_strSrvStatus = m_strSrvStatus;
	p->m_strCpuRate = m_strCpuRate;
	p->m_strMemUsed = m_strMemUsed;
	p->m_strStartTime = m_strStartTime;
// 	p->m_strSrvNumber = m_strSrvNumber;
// 	p->m_strCpuLmt = m_strCpuLmt;
// 	p->m_strMemLmt = m_strMemLmt;
	return TRUE;
}

CBaseObject* CPkg_AppStatusResp_AppStaProc::Clone()
{
	CPkg_AppStatusResp_AppStaProc *p = new CPkg_AppStatusResp_AppStaProc();
	Copy(p);
	return p;
}

CBaseObject* CPkg_AppStatusResp_AppStaProc::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CPkg_AppStatusResp_AppStaProc *p = new CPkg_AppStatusResp_AppStaProc();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CPkg_AppStatusResp_AppStaProc::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CPkg_AppStatusResp_AppStaProc::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CPkg_AppStatusResp_AppStaProc::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
