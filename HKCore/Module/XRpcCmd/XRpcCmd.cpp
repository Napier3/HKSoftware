//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XRpcCmd.cpp  CXRpcCmd


#include "stdafx.h"
#include "XRpcCmd.h"

#ifdef DVM_USE_MAP
#include "DvmCmp\DvmMapObject.h"
#endif	

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CXRpcCmd
CXRpcCmd::CXRpcCmd()
{
	//初始化属性
#ifdef DVM_USE_MAP
	m_pDvmMapObj = NULL;
#endif
	//初始化成员变量

#ifdef _DVM_VALUE_USE_CHAR_
	ZeroMemory(m_strValue , _DVM_VALUE_LENGTH_*sizeof(wchar_t));
#endif
}

CXRpcCmd::~CXRpcCmd()
{
}

long CXRpcCmd::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDataTypeKey, oNode, m_strDataType);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);

	return 0;
}

long CXRpcCmd::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDataTypeKey, oElement, m_strDataType);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
	return 0;
}

long CXRpcCmd::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDataType);
#ifdef UNICODE
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
#else
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
#endif
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDataType);
#ifdef _DVM_VALUE_USE_CHAR_
#else
		BinarySerializeRead(oBinaryBuffer, m_strValue);
#endif
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDataType);
#ifdef _DVM_VALUE_USE_CHAR_
#else
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
#endif
	}
	return 0;
}


long CXRpcCmd::SerializeChildren(CBinarySerialBuffer &oBinaryBuffer)
{
	if (oBinaryBuffer.m_dwVersionFind != 0)
	{
		CExBaseList::SerializeChildren(oBinaryBuffer);
	}
	else
	{
	}

	return 0;
}


BOOL CXRpcCmd::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CXRpcCmd *p = (CXRpcCmd*)pObj;

	if(m_strDataType != p->m_strDataType)
	{
		return FALSE;
	}

	if(m_strValue != p->m_strValue)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CXRpcCmd::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CXRpcCmd *p = (CXRpcCmd*)pDest;

	p->m_strDataType = m_strDataType;
#ifdef _DVM_VALUE_USE_CHAR_
	wcscpy(p->m_strValue, m_strValue);
#else
	p->m_strValue = m_strValue;
#endif
	return TRUE;
}

CBaseObject* CXRpcCmd::Clone()
{
	CXRpcCmd *p = new CXRpcCmd();
	Copy(p);
	return p;
}


CExBaseObject* CXRpcCmd::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCXRpcCmdKey)
	{
		pNew = new CXRpcCmd();
	}

	return pNew;
}

CExBaseObject* CXRpcCmd::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DVMCLASSID_CDVMVALUE)
	{
		pNew = new CXRpcCmd();
	}

	return pNew;
}

#ifdef DVM_USE_MAP

BOOL CXRpcCmd::IsAllMap()
{
	if (m_pDvmMapObj == NULL)
	{
		return FALSE;
	}

	BOOL bAllMap = TRUE;
	POS pos = GetHeadPosition();
	CXRpcCmd *p = NULL;

	while (pos != NULL)
	{
		p = (CXRpcCmd *)GetNext(pos);

		if (!p->IsAllMap())
		{
			bAllMap = FALSE;
			break;
		}
	}

	if (bAllMap)
	{
		if ( ((CDvmMapObject*)m_pDvmMapObj)->m_pMap == NULL)
		{
			bAllMap = FALSE;
		}
	}

	return bAllMap;
}

#endif
CXRpcCmd* CXRpcCmd::FindValueByID(const CString &strValueID)
{
	CXRpcCmd *pValue;
	CXRpcCmd *pFind = (CXRpcCmd*)FindByID(strValueID);

	if (pFind != NULL)
	{
		return pFind;
	}

	POS pos = GetHeadPosition();
	long nLen = strValueID.GetLength();

	while (pos != NULL)
	{
		pValue = (CXRpcCmd *)GetNext(pos);

		if (pValue->m_strID.Right(nLen) == strValueID)
		{
			pFind = pValue;
			break;
		}

		if (pValue->GetCount() > 0)
		{
			pFind = pValue->FindValueByID(strValueID);

			if (pFind != NULL)
			{
				break;
			}
		}
	}

	return pFind;
}

//////////////////////////////////////////////////////////////////////////
//CDvmBrcbValue
CDvmBrcbValue::CDvmBrcbValue()
{

}

CDvmBrcbValue::~CDvmBrcbValue()
{

}


CBaseObject* CDvmBrcbValue::Clone()
{
	CDvmBrcbValue *p = new CDvmBrcbValue();
	Copy(p);
	return p;
}


