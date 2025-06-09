//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeAppCfgs.cpp  CEdgeAppCfgs


#include "stdafx.h"
#include "EdgeAppCfgs.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeAppCfgs::CEdgeAppCfgs()
{
	//初始化属性

	//初始化成员变量
	m_pEdgeCfgCpu = NULL;
	m_pEdgeCfgMem = NULL;
}

CEdgeAppCfgs::~CEdgeAppCfgs()
{
}

long CEdgeAppCfgs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strAppKey, oNode, m_strApp);
	return 0;
}

long CEdgeAppCfgs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strAppKey, oElement, m_strApp);
	return 0;
}

long CEdgeAppCfgs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strApp);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strApp);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strApp);
	}
	return 0;
}

void CEdgeAppCfgs::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == EDGECMDCLASSID_CEDGECFGCPU)
		{
			m_pEdgeCfgCpu = (CEdgeCfgCpu*)p;
		}
		else if (nClassID == EDGECMDCLASSID_CEDGECFGMEM)
		{
			m_pEdgeCfgMem = (CEdgeCfgMem*)p;
		}
	}

	m_strID = GetXmlElementKey();

	CExBaseList* pApp = new CExBaseList;
	pApp->m_strID = CEdgeCmdMngrXmlRWKeys::AppKey();
	pApp->m_strName = m_strApp;
	AddNewChild(pApp);
}

BOOL CEdgeAppCfgs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeAppCfgs *p = (CEdgeAppCfgs*)pObj;

	if(m_strApp != p->m_strApp)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEdgeAppCfgs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeAppCfgs *p = (CEdgeAppCfgs*)pDest;

	p->m_strApp = m_strApp;
	return TRUE;
}

CBaseObject* CEdgeAppCfgs::Clone()
{
	CEdgeAppCfgs *p = new CEdgeAppCfgs();
	Copy(p);
	return p;
}

CBaseObject* CEdgeAppCfgs::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeAppCfgs *p = new CEdgeAppCfgs();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeAppCfgs::CanPaste(UINT nClassID)
{
	if (nClassID == EDGECMDCLASSID_CEDGECFGMEM)
	{
		return TRUE;
	}

	if (nClassID == EDGECMDCLASSID_CEDGECFGCPU)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEdgeAppCfgs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEdgeCfgMemKey)
	{
		pNew = new CEdgeCfgMem();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeCfgCpuKey)
	{
		pNew = new CEdgeCfgCpu();
	}

	return pNew;
}

CExBaseObject* CEdgeAppCfgs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EDGECMDCLASSID_CEDGECFGMEM)
	{
		pNew = new CEdgeCfgMem();
	}
	else if (nClassID == EDGECMDCLASSID_CEDGECFGCPU)
	{
		pNew = new CEdgeCfgCpu();
	}

	return pNew;
}
