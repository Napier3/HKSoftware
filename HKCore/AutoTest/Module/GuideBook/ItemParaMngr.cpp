#include "stdafx.h"
#include "ItemParaMngr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGbWzdAutoItemPara::CGbWzdAutoItemPara()
{
	
}

CGbWzdAutoItemPara::~CGbWzdAutoItemPara()
{

}

long CGbWzdAutoItemPara::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if (oBinaryBuffer.IsCalSizeMode())
	{
		
	}
	else if (oBinaryBuffer.IsReadMode())
	{	
		
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		
	}

	return 0;
}

long CGbWzdAutoItemPara::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;
}

long CGbWzdAutoItemPara::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	return 0;
}

BOOL CGbWzdAutoItemPara::IsEqual(CBaseObject* pObj)
{
	if(pObj != NULL)
	{
		CGbWzdAutoItemPara* pSingleItemPara = (CGbWzdAutoItemPara*)pObj;

		if(CExBaseObject::IsEqual(pObj))
		{
			return TRUE;
		}
	}
	
	return FALSE;
}	

BOOL CGbWzdAutoItemPara::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
		return TRUE;

	CExBaseObject::CopyOwn(pDesObj);

	return TRUE;
}

CBaseObject* CGbWzdAutoItemPara::Clone()
{
	CGbWzdAutoItemPara* pItemPara = new CGbWzdAutoItemPara();
	Copy(pItemPara);

	return pItemPara;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CTestItemParaMngr::CTestItemParaMngr()
{

}

CTestItemParaMngr::~CTestItemParaMngr()
{

}

long CTestItemParaMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);
	return 0;
}

long CTestItemParaMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;
}

long CTestItemParaMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	return 0;
}

BOOL CTestItemParaMngr::IsEqual(CBaseObject* pObj)
{
	return CExBaseObject::IsEqual(pObj);
}

BOOL CTestItemParaMngr::CopyOwn(CBaseObject* pDesObj)
{
	CExBaseObject::CopyOwn(pDesObj);
	return TRUE;
}

CBaseObject* CTestItemParaMngr::Clone()
{
	CTestItemParaMngr* pObj = new CTestItemParaMngr();
	Copy(pObj);

	return pObj;
}


CExBaseObject* CTestItemParaMngr::CreateNewChild(long nClassID)
{
	return new CGbWzdAutoItemPara();
}

CExBaseObject* CTestItemParaMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	return new CGbWzdAutoItemPara();
}