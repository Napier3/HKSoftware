#include "StdAfx.h"
#include "DvDataTypes.h"
#include "DvDataType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CDvDataTypes::CDvDataTypes(void)
{
}

CDvDataTypes::~CDvDataTypes(void)
{
}

long CDvDataTypes::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;
}

long CDvDataTypes::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	return 0;
}

long CDvDataTypes::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}



CExBaseObject* CDvDataTypes::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDvDataTypeKey)
	{
		return new CDvDataType();
	}

	return NULL;
}

CExBaseObject* CDvDataTypes::CreateNewChild(long nClassID)
{
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CDvDataTypes::IsEqualOwn(CBaseObject* pObj)
{
	ASSERT (pObj == NULL);

	if (pObj == NULL)
	{
		return FALSE;
	}

	if (this == pObj)
	{
		return TRUE;
	}

	return CExBaseList::IsEqualOwn(pObj);
}

CBaseObject* CDvDataTypes::Clone()
{
	CDvDataTypes* pNew = new CDvDataTypes();
	Copy(pNew);
	return pNew;
}

BOOL CDvDataTypes::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	return CExBaseList::CopyOwn(pDest);
}