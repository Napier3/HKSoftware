//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DmDataTemplate.cpp  CDmDataTemplate


#include "stdafx.h"
#include "DmDataTemplate.h"

CDmDataTemplate::CDmDataTemplate()
{
	//初始化属性

	//初始化成员变量
}

CDmDataTemplate::~CDmDataTemplate()
{
}

long CDmDataTemplate::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDmDataTemplateXmlRWKeys *pXmlKeys = (CDmDataTemplateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDmDataTemplate::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	if (m_strName.GetLength() <= 1)
	{
		m_strName = m_strID;
	}

	CDmDataTemplateXmlRWKeys *pXmlKeys = (CDmDataTemplateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDmDataTemplate::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CDmDataTemplate::InitAfterRead()
{
}

BOOL CDmDataTemplate::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDmDataTemplate *p = (CDmDataTemplate*)pObj;

	return TRUE;
}

BOOL CDmDataTemplate::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDmDataTemplate *p = (CDmDataTemplate*)pDest;

	return TRUE;
}

CBaseObject* CDmDataTemplate::Clone()
{
	CDmDataTemplate *p = new CDmDataTemplate();
	Copy(p);
	return p;
}

BOOL CDmDataTemplate::CanPaste(UINT nClassID)
{
	if (nClassID == DMDTCLASSID_CDMDTNODEDATAS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CDmDataTemplate::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDmDataTemplateXmlRWKeys *pXmlKeys = (CDmDataTemplateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDmdtNodeDatasKey)
	{
		pNew = new CDmdtNodeDatas();
	}

	return pNew;
}

CExBaseObject* CDmDataTemplate::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DMDTCLASSID_CDMDTNODEDATAS)
	{
		pNew = new CDmdtNodeDatas();
	}

	return pNew;
}

void CDmDataTemplate::OpenDmDataTemplateFile()
{
	CString strPath;
	
	GetDmDataTemplateFile(strPath);
	DeleteAll();
	OpenXmlFile(strPath, CDmDataTemplateXmlRWKeys::CDmDataTemplateKey(), CDmDataTemplateXmlRWKeys::g_pXmlKeys);
}

void CDmDataTemplate::GetDmDataTemplateFile(CString &strFile)
{
	strFile = _P_GetConfigPath();
	strFile += _T("DmNodeDataTemplate.xml");
}

