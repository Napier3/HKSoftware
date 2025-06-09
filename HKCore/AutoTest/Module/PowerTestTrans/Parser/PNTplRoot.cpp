//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PNTplRoot.cpp  CPNTplRoot


#include "stdafx.h"
#include "PNTplRoot.h"

CPNTplRoot::CPNTplRoot()
{
	//初始化属性
	
	//初始化成员变量
}

CPNTplRoot::~CPNTplRoot()
{
}

long CPNTplRoot::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPNTplMngrXmlRWKeys *pXmlKeys = (CPNTplMngrXmlRWKeys*)pXmlRWKeys;
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);

	return 0;
}

long CPNTplRoot::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPNTplMngrXmlRWKeys *pXmlKeys = (CPNTplMngrXmlRWKeys*)pXmlRWKeys;
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);

	return 0;
}

long CPNTplRoot::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
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

void CPNTplRoot::InitAfterRead()
{
}

BOOL CPNTplRoot::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CPNTplRoot *p = (CPNTplRoot*)pObj;

	return TRUE;
}

BOOL CPNTplRoot::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPNTplRoot *p = (CPNTplRoot*)pDest;

	return TRUE;
}

CBaseObject* CPNTplRoot::Clone()
{
	CPNTplRoot *p = new CPNTplRoot();
	Copy(p);
	return p;
}

BOOL CPNTplRoot::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CPNTPLELEMENT)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CPNTPLEQUATION)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CPNTPLGROUP)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CPNTPLTEXT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CPNTplRoot::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CPNTplMngrXmlRWKeys *pXmlKeys = (CPNTplMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCPNTplElementKey)
	{
		pNew = new CPNTplElement();
	}
	else if (strClassID == pXmlKeys->m_strCPNTplEquationKey)
	{
		pNew = new CPNTplEquation();
	}
	else if (strClassID == pXmlKeys->m_strCPNTplGroupKey)
	{
		pNew = new CPNTplGroup();
	}
	else if (strClassID == pXmlKeys->m_strCPNTplTextKey)
	{
		pNew = new CPNTplText();
	}

	return pNew;
}

CExBaseObject* CPNTplRoot::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CPNTPLELEMENT)
	{
		pNew = new CPNTplElement();
	}
	else if (nClassID == MNGRCLASSID_CPNTPLEQUATION)
	{
		pNew = new CPNTplEquation();
	}
	else if (nClassID == MNGRCLASSID_CPNTPLGROUP)
	{
		pNew = new CPNTplGroup();
	}
	else if (nClassID == MNGRCLASSID_CPNTPLTEXT)
	{
		pNew = new CPNTplText();
	}

	return pNew;
}
