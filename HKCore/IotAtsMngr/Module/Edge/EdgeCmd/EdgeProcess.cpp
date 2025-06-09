//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeProcess.cpp  CEdgeProcess


#include "stdafx.h"
#include "EdgeProcess.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeProcess::CEdgeProcess()
{
	//初始化属性
	m_nSrvIndex = 0;
	m_nCpuLmt = 0;
	m_nCpuRate = 0;
	m_nMemLmt = 0;
	m_nMemUsed = 0;

	//初始化成员变量
}

CEdgeProcess::~CEdgeProcess()
{
}

long CEdgeProcess::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strSrvIndexKey, oNode, m_nSrvIndex);
	xml_GetAttibuteValue(pXmlKeys->m_strSrvNameKey, oNode, m_strSrvName);
	xml_GetAttibuteValue(pXmlKeys->m_strSrvEnableKey, oNode, m_strSrvEnable);
	xml_GetAttibuteValue(pXmlKeys->m_strSrvStatusKey, oNode, m_strSrvStatus);
	xml_GetAttibuteValue(pXmlKeys->m_strCpuLmtKey, oNode, m_nCpuLmt);
	xml_GetAttibuteValue(pXmlKeys->m_strCpuRateKey, oNode, m_nCpuRate);
	xml_GetAttibuteValue(pXmlKeys->m_strSrvNameKey, oNode, m_nMemLmt);
	xml_GetAttibuteValue(pXmlKeys->m_strMemUsedKey, oNode, m_nMemUsed);
	xml_GetAttibuteValue(pXmlKeys->m_strStartTimeKey, oNode, m_strStartTime);
	return 0;
}

long CEdgeProcess::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strSrvIndexKey, oElement, m_nSrvIndex);
	xml_SetAttributeValue(pXmlKeys->m_strSrvNameKey, oElement, m_strSrvName);
	xml_SetAttributeValue(pXmlKeys->m_strSrvEnableKey, oElement, m_strSrvEnable);
	xml_SetAttributeValue(pXmlKeys->m_strSrvStatusKey, oElement, m_strSrvStatus);
	xml_SetAttributeValue(pXmlKeys->m_strCpuLmtKey, oElement, m_nCpuLmt);
	xml_SetAttributeValue(pXmlKeys->m_strCpuRateKey, oElement, m_nCpuRate);
	xml_SetAttributeValue(pXmlKeys->m_strSrvNameKey, oElement, m_nMemLmt);
	xml_SetAttributeValue(pXmlKeys->m_strMemUsedKey, oElement, m_nMemUsed);
	xml_SetAttributeValue(pXmlKeys->m_strStartTimeKey, oElement, m_strStartTime);
	return 0;
}

long CEdgeProcess::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nSrvIndex);
		BinarySerializeCalLen(oBinaryBuffer, m_strSrvName);
		BinarySerializeCalLen(oBinaryBuffer, m_strSrvEnable);
		BinarySerializeCalLen(oBinaryBuffer, m_strSrvStatus);
		BinarySerializeCalLen(oBinaryBuffer, m_nCpuLmt);
		BinarySerializeCalLen(oBinaryBuffer, m_nCpuRate);
		BinarySerializeCalLen(oBinaryBuffer, m_nMemLmt);
		BinarySerializeCalLen(oBinaryBuffer, m_nMemUsed);
		BinarySerializeCalLen(oBinaryBuffer, m_strStartTime);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nSrvIndex);
		BinarySerializeRead(oBinaryBuffer, m_strSrvName);
		BinarySerializeRead(oBinaryBuffer, m_strSrvEnable);
		BinarySerializeRead(oBinaryBuffer, m_strSrvStatus);
		BinarySerializeRead(oBinaryBuffer, m_nCpuLmt);
		BinarySerializeRead(oBinaryBuffer, m_nCpuRate);
		BinarySerializeRead(oBinaryBuffer, m_nMemLmt);
		BinarySerializeRead(oBinaryBuffer, m_nMemUsed);
		BinarySerializeRead(oBinaryBuffer, m_strStartTime);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nSrvIndex);
		BinarySerializeWrite(oBinaryBuffer, m_strSrvName);
		BinarySerializeWrite(oBinaryBuffer, m_strSrvEnable);
		BinarySerializeWrite(oBinaryBuffer, m_strSrvStatus);
		BinarySerializeWrite(oBinaryBuffer, m_nCpuLmt);
		BinarySerializeWrite(oBinaryBuffer, m_nCpuRate);
		BinarySerializeWrite(oBinaryBuffer, m_nMemLmt);
		BinarySerializeWrite(oBinaryBuffer, m_nMemUsed);
		BinarySerializeWrite(oBinaryBuffer, m_strStartTime);
	}
	return 0;
}

void CEdgeProcess::InitAfterRead()
{
	m_strID = GetXmlElementKey();

	CExBaseList* pSrvIndex = new CExBaseList;
	pSrvIndex->m_strID = CEdgeCmdMngrXmlRWKeys::SrvIndexKey();
	pSrvIndex->m_strName.Format("%d", m_nSrvIndex);
	AddNewChild(pSrvIndex);

	CExBaseList* pSrvEnable = new CExBaseList;
	pSrvEnable->m_strID = CEdgeCmdMngrXmlRWKeys::SrvEnableKey();
	pSrvEnable->m_strName = m_strSrvEnable;
	AddNewChild(pSrvEnable);

	CExBaseList* pSrvStatus = new CExBaseList;
	pSrvStatus->m_strID = CEdgeCmdMngrXmlRWKeys::SrvStatusKey();
	pSrvStatus->m_strName = m_strSrvStatus;
	AddNewChild(pSrvStatus);

	CExBaseList* pCpuLmt = new CExBaseList;
	pCpuLmt->m_strID = CEdgeCmdMngrXmlRWKeys::CpuLmtKey();
	pCpuLmt->m_strName.Format("%d", m_nCpuLmt);
	AddNewChild(pCpuLmt);

	CExBaseList* pCpuRate = new CExBaseList;
	pCpuRate->m_strID = CEdgeCmdMngrXmlRWKeys::CpuRateKey();
	pCpuRate->m_strName.Format("%d", m_nCpuRate);
	AddNewChild(pCpuRate);

	CExBaseList* pMemLmt = new CExBaseList;
	pMemLmt->m_strID = CEdgeCmdMngrXmlRWKeys::MemLmtKey();
	pMemLmt->m_strName.Format("%d", m_nMemLmt);
	AddNewChild(pMemLmt);

	CExBaseList* pMemUsed = new CExBaseList;
	pMemUsed->m_strID = CEdgeCmdMngrXmlRWKeys::MemUsedKey();
	pMemUsed->m_strName.Format("%d", m_nMemUsed);
	AddNewChild(pMemUsed);

	CExBaseList* pStartTime = new CExBaseList;
	pStartTime->m_strID = CEdgeCmdMngrXmlRWKeys::StartTimeKey();
	pStartTime->m_strName = m_strStartTime;
	AddNewChild(pStartTime);

	CExBaseList* pSrvName = new CExBaseList;
	pSrvName->m_strID = CEdgeCmdMngrXmlRWKeys::SrvNameKey();
	pSrvName->m_strName = m_strSrvName;
	AddNewChild(pSrvName);
}

BOOL CEdgeProcess::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeProcess *p = (CEdgeProcess*)pObj;

	if(m_nSrvIndex != p->m_nSrvIndex)
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

	if(m_nCpuLmt != p->m_nCpuLmt)
	{
		return FALSE;
	}

	if(m_nCpuRate != p->m_nCpuRate)
	{
		return FALSE;
	}

	if(m_nMemLmt != p->m_nMemLmt)
	{
		return FALSE;
	}

	if(m_nMemUsed != p->m_nMemUsed)
	{
		return FALSE;
	}

	if(m_strStartTime != p->m_strStartTime)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEdgeProcess::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeProcess *p = (CEdgeProcess*)pDest;

	p->m_nSrvIndex = m_nSrvIndex;
	p->m_strSrvName = m_strSrvName;
	p->m_strSrvEnable = m_strSrvEnable;
	p->m_strSrvStatus = m_strSrvStatus;
	p->m_nCpuLmt = m_nCpuLmt;
	p->m_nCpuRate = m_nCpuRate;
	p->m_nMemLmt = m_nMemLmt;
	p->m_nMemUsed = m_nMemUsed;
	p->m_strStartTime = m_strStartTime;
	return TRUE;
}

CBaseObject* CEdgeProcess::Clone()
{
	CEdgeProcess *p = new CEdgeProcess();
	Copy(p);
	return p;
}

CBaseObject* CEdgeProcess::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeProcess *p = new CEdgeProcess();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeProcess::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeProcess::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeProcess::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
