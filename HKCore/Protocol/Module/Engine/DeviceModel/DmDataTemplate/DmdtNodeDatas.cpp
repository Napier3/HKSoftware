//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DmdtNodeDatas.cpp  CDmdtNodeDatas


#include "stdafx.h"
#include "DmdtNodeDatas.h"

CDmdtNodeDatas::CDmdtNodeDatas()
{
	//初始化属性

	//初始化成员变量
}

CDmdtNodeDatas::~CDmdtNodeDatas()
{
}

long CDmdtNodeDatas::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDmDataTemplateXmlRWKeys *pXmlKeys = (CDmDataTemplateXmlRWKeys*)pXmlRWKeys;

	if (m_strName.GetLength() <= 1)
	{
		m_strName = m_strID;
	}

	return 0;
}

long CDmdtNodeDatas::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDmDataTemplateXmlRWKeys *pXmlKeys = (CDmDataTemplateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDmdtNodeDatas::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CDmdtNodeDatas::InitAfterRead()
{
}

BOOL CDmdtNodeDatas::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDmdtNodeDatas *p = (CDmdtNodeDatas*)pObj;

	return TRUE;
}

BOOL CDmdtNodeDatas::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDmdtNodeDatas *p = (CDmdtNodeDatas*)pDest;

	return TRUE;
}

CBaseObject* CDmdtNodeDatas::Clone()
{
	CDmdtNodeDatas *p = new CDmdtNodeDatas();
	Copy(p);
	return p;
}

BOOL CDmdtNodeDatas::CanPaste(UINT nClassID)
{
	if (nClassID == DMDTCLASSID_CDMDTNODEDATA)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CDmdtNodeDatas::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDmDataTemplateXmlRWKeys *pXmlKeys = (CDmDataTemplateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDmdtNodeDataKey)
	{
		pNew = new CDmdtNodeData();
	}

	return pNew;
}

CExBaseObject* CDmdtNodeDatas::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DMDTCLASSID_CDMDTNODEDATA)
	{
		pNew = new CDmdtNodeData();
	}

	return pNew;
}
