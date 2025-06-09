//Õâ¶ÎÔ´´úÂëÓÉClassGenerator´´½¨
//°æÈ¨ËùÓÐ LiJunqing  lijunqing1224@126.com
//±£ÁôËùÓÐÈ¨À?

//SttLicenseMngr.cpp  CSttLicenseMngr


#include "stdafx.h"
#include "SttLicenseMngr.h"

CSttLicenseMngr::CSttLicenseMngr()
{
	//³õÊ¼»¯ÊôÐÔ

	//³õÊ¼»¯³ÉÔ±±äÁ¿
}

CSttLicenseMngr::~CSttLicenseMngr()
{
}

long CSttLicenseMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttLicenseMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttLicenseMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSttLicenseMngr::InitAfterRead()
{
}

BOOL CSttLicenseMngr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttLicenseMngr *p = (CSttLicenseMngr*)pObj;

	return TRUE;
}

BOOL CSttLicenseMngr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttLicenseMngr *p = (CSttLicenseMngr*)pDest;

	return TRUE;
}

CBaseObject* CSttLicenseMngr::Clone()
{
	CSttLicenseMngr *p = new CSttLicenseMngr();
	Copy(p);
	return p;
}

CExBaseObject* CSttLicenseMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttLicenseKey)
	{
		pNew = new CSttLicense();
	}

	return pNew;
}

CExBaseObject* CSttLicenseMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == STTCMDCLASSID_CSTTLICENSE)
	{
		pNew = new CSttLicense();
	}

	return pNew;
}
