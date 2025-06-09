//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeConStatus.cpp  CEdgeContStatus


#include "stdafx.h"
#include "EdgeContStatus.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeContStatus::CEdgeContStatus()
{
	//初始化属性
	m_nCpuRate = 0;
	m_nMemUsed = 0;
	m_nDiskUsed = 0;
	::GetLocalTime(&m_tmCreated);
	::GetLocalTime(&m_tmStarted);
	m_nLifeTime = 0;

	//初始化成员变量
}

CEdgeContStatus::~CEdgeContStatus()
{
}

long CEdgeContStatus::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strContainerKey, oNode, m_strContainer);
	xml_GetAttibuteValue(pXmlKeys->m_strVersionKey, oNode, m_strVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strRunKey, oNode, m_strRun);
	xml_GetAttibuteValue(pXmlKeys->m_strCpuRateKey, oNode, m_nCpuRate);
	xml_GetAttibuteValue(pXmlKeys->m_strMemUsedKey, oNode, m_nMemUsed);
	xml_GetAttibuteValue(pXmlKeys->m_strDiskUsedKey, oNode, m_nDiskUsed);
	xml_GetAttibuteValue(pXmlKeys->m_strIpKey, oNode, m_strIp);
	xml_GetAttibuteValue(pXmlKeys->m_strCreatedKey, oNode, m_tmCreated);
	xml_GetAttibuteValue(pXmlKeys->m_strStartedKey, oNode, m_tmStarted);
	xml_GetAttibuteValue(pXmlKeys->m_strLifeTimeKey, oNode, m_nLifeTime);
	xml_GetAttibuteValue(pXmlKeys->m_strImageKey, oNode, m_strImage);
	return 0;
}

long CEdgeContStatus::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strContainerKey, oElement, m_strContainer);
	xml_SetAttributeValue(pXmlKeys->m_strVersionKey, oElement, m_strVersion);
	xml_SetAttributeValue(pXmlKeys->m_strRunKey, oElement, m_strRun);
	xml_SetAttributeValue(pXmlKeys->m_strCpuRateKey, oElement, m_nCpuRate);
	xml_SetAttributeValue(pXmlKeys->m_strMemUsedKey, oElement, m_nMemUsed);
	xml_SetAttributeValue(pXmlKeys->m_strDiskUsedKey, oElement, m_nDiskUsed);
	xml_SetAttributeValue(pXmlKeys->m_strIpKey, oElement, m_strIp);
	xml_SetAttributeValue(pXmlKeys->m_strCreatedKey, oElement, m_tmCreated);
	xml_SetAttributeValue(pXmlKeys->m_strStartedKey, oElement, m_tmStarted);
	xml_SetAttributeValue(pXmlKeys->m_strLifeTimeKey, oElement, m_nLifeTime);
	xml_SetAttributeValue(pXmlKeys->m_strImageKey, oElement, m_strImage);
	return 0;
}

long CEdgeContStatus::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strContainer);
		BinarySerializeCalLen(oBinaryBuffer, m_strVersion);
		BinarySerializeCalLen(oBinaryBuffer, m_strRun);
		BinarySerializeCalLen(oBinaryBuffer, m_nCpuRate);
		BinarySerializeCalLen(oBinaryBuffer, m_nMemUsed);
		BinarySerializeCalLen(oBinaryBuffer, m_nDiskUsed);
		BinarySerializeCalLen(oBinaryBuffer, m_strIp);
		BinarySerializeCalLen(oBinaryBuffer, m_tmCreated);
		BinarySerializeCalLen(oBinaryBuffer, m_tmStarted);
		BinarySerializeCalLen(oBinaryBuffer, m_nLifeTime);
		BinarySerializeCalLen(oBinaryBuffer, m_strImage);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strContainer);
		BinarySerializeRead(oBinaryBuffer, m_strVersion);
		BinarySerializeRead(oBinaryBuffer, m_strRun);
		BinarySerializeRead(oBinaryBuffer, m_nCpuRate);
		BinarySerializeRead(oBinaryBuffer, m_nMemUsed);
		BinarySerializeRead(oBinaryBuffer, m_nDiskUsed);
		BinarySerializeRead(oBinaryBuffer, m_strIp);
		BinarySerializeRead(oBinaryBuffer, m_tmCreated);
		BinarySerializeRead(oBinaryBuffer, m_tmStarted);
		BinarySerializeRead(oBinaryBuffer, m_nLifeTime);
		BinarySerializeRead(oBinaryBuffer, m_strImage);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strContainer);
		BinarySerializeWrite(oBinaryBuffer, m_strVersion);
		BinarySerializeWrite(oBinaryBuffer, m_strRun);
		BinarySerializeWrite(oBinaryBuffer, m_nCpuRate);
		BinarySerializeWrite(oBinaryBuffer, m_nMemUsed);
		BinarySerializeWrite(oBinaryBuffer, m_nDiskUsed);
		BinarySerializeWrite(oBinaryBuffer, m_strIp);
		BinarySerializeWrite(oBinaryBuffer, m_tmCreated);
		BinarySerializeWrite(oBinaryBuffer, m_tmStarted);
		BinarySerializeWrite(oBinaryBuffer, m_nLifeTime);
		BinarySerializeWrite(oBinaryBuffer, m_strImage);
	}
	return 0;
}

void CEdgeContStatus::InitAfterRead()
{
	m_strID = GetXmlElementKey();

	CExBaseList* pVersion = new CExBaseList;
	pVersion->m_strID = CEdgeCmdMngrXmlRWKeys::VersionKey();
	pVersion->m_strName = m_strVersion;
	AddNewChild(pVersion);

	CExBaseList* pRun = new CExBaseList;
	pRun->m_strID = CEdgeCmdMngrXmlRWKeys::RunKey();
	pRun->m_strName = m_strRun;
	AddNewChild(pRun);

	CExBaseList* pCpuRate = new CExBaseList;
	pCpuRate->m_strID = CEdgeCmdMngrXmlRWKeys::CpuRateKey();
	pCpuRate->m_strName.Format("%d", m_nCpuRate);
	AddNewChild(pCpuRate);

	CExBaseList* pMemUsed = new CExBaseList;
	pMemUsed->m_strID = CEdgeCmdMngrXmlRWKeys::MemUsedKey();
	pMemUsed->m_strName.Format("%d", m_nMemUsed);
	AddNewChild(pMemUsed);

	CExBaseList* pDiskUsed = new CExBaseList;
	pDiskUsed->m_strID = CEdgeCmdMngrXmlRWKeys::DiskUsedKey();
	pDiskUsed->m_strName.Format("%d", m_nDiskUsed);
	AddNewChild(pDiskUsed);

	CExBaseList* pIp = new CExBaseList;
	pIp->m_strID = CEdgeCmdMngrXmlRWKeys::IpKey();
	pIp->m_strName = m_strIp;
	AddNewChild(pIp);

	CExBaseList* pCreated = new CExBaseList;
	pCreated->m_strID = CEdgeCmdMngrXmlRWKeys::CreatedKey();
	SystemTime_To_String(m_tmCreated, pCreated->m_strName);
	AddNewChild(pCreated);

	CExBaseList* pStarted = new CExBaseList;
	pStarted->m_strID = CEdgeCmdMngrXmlRWKeys::StartedKey();
	SystemTime_To_String(m_tmStarted, pStarted->m_strName);
	AddNewChild(pStarted);

	CExBaseList* pLifeTime = new CExBaseList;
	pLifeTime->m_strID = CEdgeCmdMngrXmlRWKeys::LifeTimeKey();
	pLifeTime->m_strName.Format("%d", m_nLifeTime);
	AddNewChild(pLifeTime);

	CExBaseList* pImage = new CExBaseList;
	pImage->m_strID = CEdgeCmdMngrXmlRWKeys::ImageKey();
	pImage->m_strName = m_strImage;
	AddNewChild(pImage);

	CExBaseList* pContainer = new CExBaseList;
	pContainer->m_strID = CEdgeCmdMngrXmlRWKeys::ContainerKey();
	pContainer->m_strName = m_strContainer;
	AddNewChild(pContainer);
}

BOOL CEdgeContStatus::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeContStatus *p = (CEdgeContStatus*)pObj;

	if(m_strContainer != p->m_strContainer)
	{
		return FALSE;
	}

	if(m_strVersion != p->m_strVersion)
	{
		return FALSE;
	}

	if(m_strRun != p->m_strRun)
	{
		return FALSE;
	}

	if(m_nCpuRate != p->m_nCpuRate)
	{
		return FALSE;
	}

	if(m_nMemUsed != p->m_nMemUsed)
	{
		return FALSE;
	}

	if(m_nDiskUsed != p->m_nDiskUsed)
	{
		return FALSE;
	}

	if(m_strIp != p->m_strIp)
	{
		return FALSE;
	}

	if(m_nLifeTime != p->m_nLifeTime)
	{
		return FALSE;
	}

	if(m_strImage != p->m_strImage)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEdgeContStatus::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeContStatus *p = (CEdgeContStatus*)pDest;

	p->m_strContainer = m_strContainer;
	p->m_strVersion = m_strVersion;
	p->m_strRun = m_strRun;
	p->m_nCpuRate = m_nCpuRate;
	p->m_nMemUsed = m_nMemUsed;
	p->m_nDiskUsed = m_nDiskUsed;
	p->m_strIp = m_strIp;
	p->m_tmCreated = m_tmCreated;
	p->m_tmStarted = m_tmStarted;
	p->m_nLifeTime = m_nLifeTime;
	p->m_strImage = m_strImage;
	return TRUE;
}

CBaseObject* CEdgeContStatus::Clone()
{
	CEdgeContStatus *p = new CEdgeContStatus();
	Copy(p);
	return p;
}

CBaseObject* CEdgeContStatus::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeContStatus *p = new CEdgeContStatus();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeContStatus::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeContStatus::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeContStatus::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
