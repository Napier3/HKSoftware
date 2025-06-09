//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeCfgCpu.cpp  CEdgeCfgCpu


#include "stdafx.h"
#include "EdgeCfgCpu.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeCfgCpu::CEdgeCfgCpu()
{
	//初始化属性
	m_nCpus = 0;
	m_nCpuLmt = 0;

	//初始化成员变量
}

CEdgeCfgCpu::~CEdgeCfgCpu()
{
}

long CEdgeCfgCpu::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strCpusKey, oNode, m_nCpus);
	xml_GetAttibuteValue(pXmlKeys->m_strCpuLmtKey, oNode, m_nCpuLmt);

	AddErrorInfo(pXmlKeys->m_strCpusKey, oNode, CJSON_Int);
	AddErrorInfo(pXmlKeys->m_strCpuLmtKey, oNode, CJSON_Int);

	return 0;
}

long CEdgeCfgCpu::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strCpusKey, oElement, m_nCpus);
	xml_SetAttributeValue(pXmlKeys->m_strCpuLmtKey, oElement, m_nCpuLmt);
	return 0;
}

long CEdgeCfgCpu::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nCpus);
		BinarySerializeCalLen(oBinaryBuffer, m_nCpuLmt);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nCpus);
		BinarySerializeRead(oBinaryBuffer, m_nCpuLmt);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nCpus);
		BinarySerializeWrite(oBinaryBuffer, m_nCpuLmt);
	}
	return 0;
}

void CEdgeCfgCpu::InitAfterRead()
{
	m_strID = GetXmlElementKey();

	CExBaseList* pCpus = new CExBaseList;
	pCpus->m_strID = CEdgeCmdMngrXmlRWKeys::CpusKey();
	pCpus->m_strName.Format("%d", m_nCpus);
	AddNewChild(pCpus);

	CExBaseList* pLmt = new CExBaseList;
	pLmt->m_strID = CEdgeCmdMngrXmlRWKeys::CpuLmtKey();
	pLmt->m_strName.Format("%d", m_nCpuLmt);
	AddNewChild(pLmt);
}

BOOL CEdgeCfgCpu::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeCfgCpu *p = (CEdgeCfgCpu*)pObj;

	if(m_nCpus != p->m_nCpus)
	{
		return FALSE;
	}

	if(m_nCpuLmt != p->m_nCpuLmt)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEdgeCfgCpu::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeCfgCpu *p = (CEdgeCfgCpu*)pDest;

	p->m_nCpus = m_nCpus;
	p->m_nCpuLmt = m_nCpuLmt;
	return TRUE;
}

CBaseObject* CEdgeCfgCpu::Clone()
{
	CEdgeCfgCpu *p = new CEdgeCfgCpu();
	Copy(p);
	return p;
}

CBaseObject* CEdgeCfgCpu::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeCfgCpu *p = new CEdgeCfgCpu();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeCfgCpu::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CEdgeCfgCpu::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CEdgeCfgCpu::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}
