//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeCmd.cpp  CEdgeCmd


#include "stdafx.h"
#include "EdgeCmd.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CEdgeCmd::CEdgeCmd()
{
	//初始化属性
	m_nCode = 0;
	m_nMid = 0;
	m_nExpire = 0;

	//初始化成员变量
	m_pEdgeParam = NULL;
}

CEdgeCmd::~CEdgeCmd()
{
}

long CEdgeCmd::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strCodeKey, oNode, m_nCode);
	xml_GetAttibuteValue(pXmlKeys->m_strMsgKey, oNode, m_strMsg);
	xml_GetAttibuteValue(pXmlKeys->m_strAppKey, oNode, m_strApp);
	xml_GetAttibuteValue(pXmlKeys->m_strSignKey, oNode, m_strSign);
	xml_GetAttibuteValue(pXmlKeys->m_strMidKey, oNode, m_nMid);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	xml_GetAttibuteValue(pXmlKeys->m_strTimestampKey, oNode, m_strTimestamp);
	xml_GetAttibuteValue(pXmlKeys->m_strDeviceIdKey, oNode, m_strDeviceId);
	xml_GetAttibuteValue(pXmlKeys->m_strExpireKey, oNode, m_nExpire);

	CEdgeCmdErrorMngr::AddErrorInfo(pXmlKeys->m_strCodeKey, oNode, CJSON_Int, m_strErrorInfo);
 	CEdgeCmdErrorMngr::AddErrorInfo(pXmlKeys->m_strMsgKey, oNode, CJSON_String, m_strErrorInfo);
 	CEdgeCmdErrorMngr::AddErrorInfo(pXmlKeys->m_strAppKey, oNode, CJSON_String, m_strErrorInfo);
 	CEdgeCmdErrorMngr::AddErrorInfo(pXmlKeys->m_strSignKey, oNode, CJSON_String, m_strErrorInfo);
 	CEdgeCmdErrorMngr::AddErrorInfo(pXmlKeys->m_strMidKey, oNode, CJSON_Int, m_strErrorInfo);
 	CEdgeCmdErrorMngr::AddErrorInfo(pXmlKeys->m_strTypeKey, oNode, CJSON_String, m_strErrorInfo);
 	CEdgeCmdErrorMngr::AddErrorInfo(pXmlKeys->m_strTimestampKey, oNode, CJSON_String, m_strErrorInfo);
 	CEdgeCmdErrorMngr::AddErrorInfo(pXmlKeys->m_strDeviceIdKey, oNode, CJSON_String, m_strErrorInfo);
 	CEdgeCmdErrorMngr::AddErrorInfo(pXmlKeys->m_strExpireKey, oNode, CJSON_Int, m_strErrorInfo);

	return 0;
}

long CEdgeCmd::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;

	if(m_nCode)
		xml_SetAttributeValue(pXmlKeys->m_strCodeKey, oElement, m_nCode);
	if(m_strMsg.GetLength())
		xml_SetAttributeValue(pXmlKeys->m_strMsgKey, oElement, m_strMsg);
	if(m_strApp.GetLength())
		xml_SetAttributeValue(pXmlKeys->m_strAppKey, oElement, m_strApp);
	if(m_strSign.GetLength())
		xml_SetAttributeValue(pXmlKeys->m_strSignKey, oElement, m_strSign);
	xml_SetAttributeValue(pXmlKeys->m_strMidKey, oElement, m_nMid);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	xml_SetAttributeValue(pXmlKeys->m_strTimestampKey, oElement, m_strTimestamp);
	xml_SetAttributeValue(pXmlKeys->m_strDeviceIdKey, oElement, m_strDeviceId);
	xml_SetAttributeValue(pXmlKeys->m_strExpireKey, oElement, m_nExpire);
	return 0;
}

long CEdgeCmd::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nCode);
		BinarySerializeCalLen(oBinaryBuffer, m_strMsg);
		BinarySerializeCalLen(oBinaryBuffer, m_strApp);
		BinarySerializeCalLen(oBinaryBuffer, m_strSign);
		BinarySerializeCalLen(oBinaryBuffer, m_nMid);
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
		BinarySerializeCalLen(oBinaryBuffer, m_strTimestamp);
		BinarySerializeCalLen(oBinaryBuffer, m_strDeviceId);
		BinarySerializeCalLen(oBinaryBuffer, m_nExpire);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nCode);
		BinarySerializeRead(oBinaryBuffer, m_strMsg);
		BinarySerializeRead(oBinaryBuffer, m_strApp);
		BinarySerializeRead(oBinaryBuffer, m_strSign);
		BinarySerializeRead(oBinaryBuffer, m_nMid);
		BinarySerializeRead(oBinaryBuffer, m_strType);
		BinarySerializeRead(oBinaryBuffer, m_strTimestamp);
		BinarySerializeRead(oBinaryBuffer, m_strDeviceId);
		BinarySerializeRead(oBinaryBuffer, m_nExpire);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nCode);
		BinarySerializeWrite(oBinaryBuffer, m_strMsg);
		BinarySerializeWrite(oBinaryBuffer, m_strApp);
		BinarySerializeWrite(oBinaryBuffer, m_strSign);
		BinarySerializeWrite(oBinaryBuffer, m_nMid);
		BinarySerializeWrite(oBinaryBuffer, m_strType);
		BinarySerializeWrite(oBinaryBuffer, m_strTimestamp);
		BinarySerializeWrite(oBinaryBuffer, m_strDeviceId);
		BinarySerializeWrite(oBinaryBuffer, m_nExpire);
	}
	return 0;
}

void CEdgeCmd::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == EDGECMDCLASSID_CEDGEPARAM)
		{
			m_pEdgeParam = (CEdgeParam*)p;
		}
	}
}

BOOL CEdgeCmd::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CEdgeCmd *p = (CEdgeCmd*)pObj;

	if(m_nCode != p->m_nCode)
	{
		return FALSE;
	}

	if(m_strMsg != p->m_strMsg)
	{
		return FALSE;
	}

	if(m_strApp != p->m_strApp)
	{
		return FALSE;
	}

	if(m_strSign != p->m_strSign)
	{
		return FALSE;
	}

	if(m_nMid != p->m_nMid)
	{
		return FALSE;
	}

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	if(m_strTimestamp != p->m_strTimestamp)
	{
		return FALSE;
	}

	if(m_strDeviceId != p->m_strDeviceId)
	{
		return FALSE;
	}

	if(m_nExpire != p->m_nExpire)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CEdgeCmd::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEdgeCmd *p = (CEdgeCmd*)pDest;

	p->m_nCode = m_nCode;
	p->m_strMsg = m_strMsg;
	p->m_strApp = m_strApp;
	p->m_strSign = m_strSign;
	p->m_nMid = m_nMid;
	p->m_strType = m_strType;
	p->m_strTimestamp = m_strTimestamp;
	p->m_strDeviceId = m_strDeviceId;
	p->m_nExpire = m_nExpire;
	return TRUE;
}

CBaseObject* CEdgeCmd::Clone()
{
	CEdgeCmd *p = new CEdgeCmd();
	Copy(p);
	return p;
}

CBaseObject* CEdgeCmd::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CEdgeCmd *p = new CEdgeCmd();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CEdgeCmd::CanPaste(UINT nClassID)
{
	if (nClassID == EDGECMDCLASSID_CEDGEPARAM)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEdgeCmd::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEdgeCmdMngrXmlRWKeys *pXmlKeys = (CEdgeCmdMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEdgeParamKey)
	{
		pNew = new CEdgeParam();
	}

	return pNew;
}

CExBaseObject* CEdgeCmd::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EDGECMDCLASSID_CEDGEPARAM)
	{
		pNew = new CEdgeParam();
	}

	return pNew;
}

void CEdgeCmd::SetEdgeParam(CEdgeParam* pEdgeParam)
{	
	m_pEdgeParam = pEdgeParam;
	AddTail(pEdgeParam);
}

void CEdgeCmd::PraseCmdBuf(char *pBuf,long nLen, char *pszDestBuffer,const CString &strFormat)
{
	if (strFormat == EDGE_DATA_FORMAT_JSON)
	{
		SetXml_UTF8(pBuf,nLen, CEdgeCmdMngrXmlRWKeys::g_pXmlKeys,_JSON_TYPE_);
	}
	else
	{//XML
		ASSERT(pszDestBuffer != NULL);
		memcpy(pszDestBuffer, pBuf, nLen);
		pszDestBuffer[nLen] = 0;
		pszDestBuffer[nLen+1] = 0;

		SetXml_UTF8(pszDestBuffer, nLen, CEdgeCmdMngrXmlRWKeys::g_pXmlKeys);
	}
}