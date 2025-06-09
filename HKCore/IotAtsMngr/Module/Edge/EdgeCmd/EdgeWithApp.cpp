//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeWithApp.cpp  CEdgeWithApp


#include "stdafx.h"
#include "EdgeWithApp.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeWithApp::CEdgeWithApp()
{
	//初始化属性

	//初始化成员变量
	m_pEdgeFile = NULL;
	m_pEdgeCfgMem = NULL;
	m_pEdgeCfgCpu = NULL;
}

CEdgeWithApp::~CEdgeWithApp()
{
}

long CEdgeWithApp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strVersionKey, oNode, m_strVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strEnableKey, oNode, m_strEnable);

	AddErrorInfo(pXmlKeys->m_strVersionKey, oNode, CJSON_String);
	AddErrorInfo(pXmlKeys->m_strEnableKey, oNode, CJSON_String);
	return 0;
}

long CEdgeWithApp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strVersionKey, oElement, m_strVersion);
	xml_SetAttributeValue(pXmlKeys->m_strEnableKey, oElement, m_strEnable);
	return 0;
}

long CEdgeWithApp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strVersion);
		BinarySerializeCalLen(oBinaryBuffer, m_strEnable);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strVersion);
		BinarySerializeRead(oBinaryBuffer, m_strEnable);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strVersion);
		BinarySerializeWrite(oBinaryBuffer, m_strEnable);
	}
	return 0;
}

void CEdgeWithApp::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == EDGECMDCLASSID_CEDGEFILE)
		{
			m_pEdgeFile = (CEdgeFile*)p;
		}
		else if (nClassID == EDGECMDCLASSID_CEDGECFGMEM)
		{
			m_pEdgeCfgMem = (CEdgeCfgMem*)p;
		}
		else if (nClassID == EDGECMDCLASSID_CEDGECFGCPU)
		{
			m_pEdgeCfgCpu = (CEdgeCfgCpu*)p;
		}
	}

	m_strID = GetXmlElementKey();

	CExBaseList* pVersion = new CExBaseList;
	pVersion->m_strID = CEdgeCmdMngrXmlRWKeys::VersionKey();
	pVersion->m_strName = m_strVersion;
	AddNewChild(pVersion);

	CExBaseList* pEnable = new CExBaseList;
	pEnable->m_strID = CEdgeCmdMngrXmlRWKeys::EnableKey();
	pEnable->m_strName = m_strEnable;
	AddNewChild(pEnable);
}

BOOL CEdgeWithApp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeWithApp *p = (CEdgeWithApp*)pObj;

	if(m_strVersion != p->m_strVersion)
	{
		return FALSE;
	}

	if(m_strEnable != p->m_strEnable)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEdgeWithApp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeWithApp *p = (CEdgeWithApp*)pDest;

	p->m_strVersion = m_strVersion;
	p->m_strEnable = m_strEnable;
	return TRUE;
}

CBaseObject* CEdgeWithApp::Clone()
{
	CEdgeWithApp *p = new CEdgeWithApp();
	Copy(p);
	return p;
}

CBaseObject* CEdgeWithApp::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeWithApp *p = new CEdgeWithApp();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeWithApp::CanPaste(UINT nClassID)
{
	if (nClassID == EDGECMDCLASSID_CEDGEFILE)
	{
		return TRUE;
	}

	if (nClassID == EDGECMDCLASSID_CEDGECFGCPU)
	{
		return TRUE;
	}

	if (nClassID == EDGECMDCLASSID_CEDGECFGMEM)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEdgeWithApp::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEdgeFileKey)
	{
		pNew = new CEdgeFile();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeCfgCpuKey)
	{
		pNew = new CEdgeCfgCpu();
	}
	else if (strClassID == pXmlKeys->m_strCEdgeCfgMemKey)
	{
		pNew = new CEdgeCfgMem();
	}

	return pNew;
}

CExBaseObject* CEdgeWithApp::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EDGECMDCLASSID_CEDGEFILE)
	{
		pNew = new CEdgeFile();
	}
	else if (nClassID == EDGECMDCLASSID_CEDGECFGCPU)
	{
		pNew = new CEdgeCfgCpu();
	}
	else if (nClassID == EDGECMDCLASSID_CEDGECFGMEM)
	{
		pNew = new CEdgeCfgMem();
	}

	return pNew;
}
