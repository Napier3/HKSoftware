//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IotPpParse.cpp  CIotPpParse


#include "stdafx.h"
#include "IotPpParse.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIotPpParse::CIotPpParse()
{
	//初始化属性

	//初始化成员变量
	m_pIotPpPkgHead = NULL;
	m_pIotPpDataList = NULL;
}

CIotPpParse::~CIotPpParse()
{
}

long CIotPpParse::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDs_OptrKey, oNode, m_strDs_Optr);
	return 0;
}

long CIotPpParse::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDs_OptrKey, oElement, m_strDs_Optr);
	return 0;
}

long CIotPpParse::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDs_Optr);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDs_Optr);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDs_Optr);
	}
	return 0;
}

void CIotPpParse::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == IOTCLASSID_CIOTPPPKGHEAD)
		{
			m_pIotPpPkgHead = (CIotPpPkgHead*)p;
		}
		else if (nClassID == IOTCLASSID_CIOTPPDATALIST)
		{
			m_pIotPpDataList = (CIotPpDataList*)p;
		}
	}

	if (m_pIotPpPkgHead == NULL)
	{
		m_pIotPpPkgHead = (CIotPpPkgHead*)AddNewChild(new CIotPpPkgHead());
	}

	if (m_pIotPpDataList == NULL)
	{
		m_pIotPpDataList = (CIotPpDataList*)AddNewChild(new CIotPpDataList());
	}

}

BOOL CIotPpParse::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIotPpParse *p = (CIotPpParse*)pObj;

	if(m_strDs_Optr != p->m_strDs_Optr)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIotPpParse::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIotPpParse *p = (CIotPpParse*)pDest;

	p->m_strDs_Optr = m_strDs_Optr;
	return TRUE;
}

CBaseObject* CIotPpParse::Clone()
{
	CIotPpParse *p = new CIotPpParse();
	Copy(p);
	return p;
}

CBaseObject* CIotPpParse::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIotPpParse *p = new CIotPpParse();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIotPpParse::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOTPPPKGHEAD)
	{
		return TRUE;
	}

	if (nClassID == IOTCLASSID_CIOTPPDATALIST)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIotPpParse::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIotPpPkgHeadKey)
	{
		pNew = new CIotPpPkgHead();
	}
	else if (strClassID == pXmlKeys->m_strCIotPpDataListKey)
	{
		pNew = new CIotPpDataList();
	}

	return pNew;
}

CExBaseObject* CIotPpParse::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOTPPPKGHEAD)
	{
		pNew = new CIotPpPkgHead();
	}
	else if (nClassID == IOTCLASSID_CIOTPPDATALIST)
	{
		pNew = new CIotPpDataList();
	}

	return pNew;
}

CString CIotPpParse::GetDatasetID()
{
	if (m_pIotPpPkgHead == NULL)
	{
		return _T("");
	}

	return m_pIotPpPkgHead->m_strDs;
}