//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGdTestMacro.cpp  CSttGdTestMacro


#include "stdafx.h"
#include "SttGdTestMacro.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttGdTestMacro::CSttGdTestMacro()
{
	//初始化属性
	m_pSttGdGridDefine = NULL;
	m_pSttGdGridInsts = NULL;

	//初始化成员变量
}

CSttGdTestMacro::~CSttGdTestMacro()
{
}

long CSttGdTestMacro::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strMacro_IdKey, oNode, m_strMacroID);
	return 0;
}

long CSttGdTestMacro::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strMacro_IdKey, oElement, m_strMacroID);
	return 0;
}

long CSttGdTestMacro::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMacroID);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMacroID);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMacroID);
	}
	return 0;
}

void CSttGdTestMacro::InitAfterRead()
{
}

BOOL CSttGdTestMacro::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttGdTestMacro *p = (CSttGdTestMacro*)pObj;

	if(m_strMacroID != p->m_strMacroID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttGdTestMacro::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttGdTestMacro *p = (CSttGdTestMacro*)pDest;

	p->m_strMacroID = m_strMacroID;
	return TRUE;
}

CBaseObject* CSttGdTestMacro::Clone()
{
	CSttGdTestMacro *p = new CSttGdTestMacro();
	Copy(p);
	return p;
}

CBaseObject* CSttGdTestMacro::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttGdTestMacro *p = new CSttGdTestMacro();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttGdTestMacro::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTGDDATAPROCESS)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTGDGRIDDEFINE)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTGDGRIDINSTS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttGdTestMacro::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttGdDataProcessKey)
	{
		pNew = new CSttGdDataProcess();
	}
	else if (strClassID == pXmlKeys->m_strCSttGdGridDefineKey)
	{
		pNew = new CSttGdGridDefine();
	}
	else if (strClassID == pXmlKeys->m_strCSttGdGridInstsKey)
	{
		pNew = new CSttGdGridInsts();
	}

	return pNew;
}

CExBaseObject* CSttGdTestMacro::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTGDDATAPROCESS)
	{
		pNew = new CSttGdDataProcess();
	}
	else if (nClassID == MNGRCLASSID_CSTTGDGRIDDEFINE)
	{
		pNew = new CSttGdGridDefine();
	}
	else if (nClassID == MNGRCLASSID_CSTTGDGRIDINSTS)
	{
		pNew = new CSttGdGridInsts();
	}

	return pNew;
}

CSttGdGridDefine* CSttGdTestMacro::GetSttGdGridDefine()
{
	if (m_pSttGdGridDefine != NULL)
	{
		return m_pSttGdGridDefine;
	}

	m_pSttGdGridDefine = (CSttGdGridDefine*)FindByClassID(MNGRCLASSID_CSTTGDGRIDDEFINE);
	return m_pSttGdGridDefine;
}

CSttGdGridInsts* CSttGdTestMacro::GetSttGdGridInsts()
{
	if (m_pSttGdGridInsts != NULL)
	{
		return m_pSttGdGridInsts;
	}

	m_pSttGdGridInsts = (CSttGdGridInsts*)FindByClassID(MNGRCLASSID_CSTTGDGRIDINSTS);
	return m_pSttGdGridInsts;
}

void CSttGdTestMacro::InitGridInsts()
{
	GetSttGdGridDefine();
	GetSttGdGridInsts();

	if((m_pSttGdGridDefine == NULL)||(m_pSttGdGridInsts == NULL))
	{
		return;
	}

	m_pSttGdGridInsts->InitGridInsts(m_pSttGdGridDefine);
}

