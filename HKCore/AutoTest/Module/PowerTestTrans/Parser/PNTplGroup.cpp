//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PNTplGroup.cpp  CPNTplGroup


#include "stdafx.h"
#include "PNTplGroup.h"
#include "..\PttGlobalDefine.h"

CPNTplGroup::CPNTplGroup()
{
	//初始化属性

	//初始化成员变量
}

CPNTplGroup::~CPNTplGroup()
{
}

long CPNTplGroup::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CPNTplMngrXmlRWKeys *pXmlKeys = (CPNTplMngrXmlRWKeys*)pXmlRWKeys;
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);
	return 0;
}

long CPNTplGroup::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CPNTplMngrXmlRWKeys *pXmlKeys = (CPNTplMngrXmlRWKeys*)pXmlRWKeys;
	CExBaseObject::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	return 0;
}

long CPNTplGroup::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CPNTplGroup::InitAfterRead()
{
}

BOOL CPNTplGroup::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CPNTplGroup *p = (CPNTplGroup*)pObj;

	return TRUE;
}

BOOL CPNTplGroup::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CPNTplGroup *p = (CPNTplGroup*)pDest;

	return TRUE;
}

CBaseObject* CPNTplGroup::Clone()
{
	CPNTplGroup *p = new CPNTplGroup();
	Copy(p);
	return p;
}

BOOL CPNTplGroup::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CPNTPLEQUATION)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CPNTplGroup::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CPNTplMngrXmlRWKeys *pXmlKeys = (CPNTplMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCPNTplEquationKey)
	{
		pNew = new CPNTplEquation();
	}

	return pNew;
}

CExBaseObject* CPNTplGroup::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CPNTPLEQUATION)
	{
		pNew = new CPNTplEquation();
	}

	return pNew;
}

CPNTplEquation* CPNTplGroup::FindValueByID(const CString &strVarID)
{
	CPNTplEquation *p = NULL;
	CPNTplEquation *pFind = NULL;

	p = (CPNTplEquation *)FindByName(PTT_KEY_DATA_ATTR_ID);

	if (p == NULL)
	{
		return NULL;
	}

	if (p->m_strValue != strVarID)
	{
		return NULL;
	}

	pFind = (CPNTplEquation*)FindByName(PTT_KEY_DATA_ATTR_V);

	return pFind;
}

