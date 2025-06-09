//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecGenRule_CtrlCh.cpp  CIecGenRule_CtrlCh


#include "stdafx.h"
#include "IecGenRule_CtrlCh.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIecGenRule_CtrlCh::CIecGenRule_CtrlCh()
{
	//初始化属性
	m_nMatchRatio = 70;

	//初始化成员变量
}

CIecGenRule_CtrlCh::~CIecGenRule_CtrlCh()
{
}

long CIecGenRule_CtrlCh::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strApp_ChKey, oNode, m_strAppCh);
	xml_GetAttibuteValue(pXmlKeys->m_strCh_TypeKey, oNode, m_strChType);
	xml_GetAttibuteValue(pXmlKeys->m_strMatch_RatioKey, oNode, m_nMatchRatio);
	xml_GetAttibuteValue(pXmlKeys->m_strPhsIDKey, oNode, m_strPhsID);
	return 0;
}

long CIecGenRule_CtrlCh::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strApp_ChKey, oElement, m_strAppCh);
	xml_SetAttributeValue(pXmlKeys->m_strCh_TypeKey, oElement, m_strChType);
	xml_SetAttributeValue(pXmlKeys->m_strMatch_RatioKey, oElement, m_nMatchRatio);
	xml_SetAttributeValue(pXmlKeys->m_strPhsIDKey, oElement, m_strPhsID);
	return 0;
}

long CIecGenRule_CtrlCh::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strAppCh);
		BinarySerializeCalLen(oBinaryBuffer, m_strChType);
		BinarySerializeCalLen(oBinaryBuffer, m_nMatchRatio);
		BinarySerializeCalLen(oBinaryBuffer, m_strPhsID);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strAppCh);
		BinarySerializeRead(oBinaryBuffer, m_strChType);
		BinarySerializeRead(oBinaryBuffer, m_nMatchRatio);
		BinarySerializeRead(oBinaryBuffer, m_strPhsID);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strAppCh);
		BinarySerializeWrite(oBinaryBuffer, m_strChType);
		BinarySerializeWrite(oBinaryBuffer, m_nMatchRatio);
		BinarySerializeWrite(oBinaryBuffer, m_strPhsID);
	}
	return 0;
}

void CIecGenRule_CtrlCh::InitAfterRead()
{
}

BOOL CIecGenRule_CtrlCh::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecGenRule_CtrlCh *p = (CIecGenRule_CtrlCh*)pObj;

	if(m_strAppCh != p->m_strAppCh)
	{
		return FALSE;
	}

	if(m_strChType != p->m_strChType)
	{
		return FALSE;
	}

	if(m_nMatchRatio != p->m_nMatchRatio)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecGenRule_CtrlCh::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIecGenRule_CtrlCh *p = (CIecGenRule_CtrlCh*)pDest;

	p->m_strAppCh = m_strAppCh;
	p->m_strChType = m_strChType;
	p->m_nMatchRatio = m_nMatchRatio;
	p->m_strPhsID = m_strPhsID;
	return TRUE;
}

CBaseObject* CIecGenRule_CtrlCh::Clone()
{
	CIecGenRule_CtrlCh *p = new CIecGenRule_CtrlCh();
	Copy(p);
	return p;
}

CBaseObject* CIecGenRule_CtrlCh::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIecGenRule_CtrlCh *p = new CIecGenRule_CtrlCh();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIecGenRule_CtrlCh::CanPaste(UINT nClassID)
{
	if (nClassID == GENRATECLASSID_CIECGENCFGKEYS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIecGenRule_CtrlCh::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIecfgGenMngrXmlRWKeys *pXmlKeys = (CIecfgGenMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecGenCfgKeysKey)
	{
		pNew = new CIecGenCfgKeys();
	}

	return pNew;
}

CExBaseObject* CIecGenRule_CtrlCh::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == GENRATECLASSID_CIECGENCFGKEYS)
	{
		pNew = new CIecGenCfgKeys();
	}

	return pNew;
}
