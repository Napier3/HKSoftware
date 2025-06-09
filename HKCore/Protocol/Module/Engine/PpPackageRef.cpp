#include "StdAfx.h"
#include "PpPackageRef.h"
#include "PpDataInterface.h"
#include "PpTemplate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CPpPackageRef
CPpPackageRef::CPpPackageRef(void)
{
}

CPpPackageRef::~CPpPackageRef(void)
{
}

long CPpPackageRef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CProtocolXmlRWKeys *pKey = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pKey->m_strPackageIDKey, oNode, m_strPkgID);

	return 0;
}

long CPpPackageRef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CProtocolXmlRWKeys *pKey = (CProtocolXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pKey->m_strPackageIDKey, oElement, m_strPkgID);

	return 0;
}

long CPpPackageRef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

CExBaseObject* CPpPackageRef::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataMapKey)
	{
		return new CPpDataInterface();
	}

	return NULL;
}

CExBaseObject* CPpPackageRef::CreateNewChild(long nClassID)
{
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CPpPackageRef::IsEqualOwn(CBaseObject* pObj)
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

	if (m_strPkgID != ((CPpPackageRef*)pObj)->m_strPkgID)
	{
		return FALSE;
	}

	return CExBaseObject::IsEqualOwn(pObj);
}

CBaseObject* CPpPackageRef::Clone()
{
	CPpPackageRef* pNew = new CPpPackageRef();
	Copy(pNew);
	return pNew;
}

BOOL CPpPackageRef::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CPpPackageRef*)pDest)->m_strPkgID = m_strPkgID;

	return CExBaseObject::CopyOwn(pDest);
}

void CPpPackageRef::SetPackageID(const CString &strPakageID)
{
	if (strPakageID == m_strPkgID)
	{
		return;
	}

	DeleteAll();
	m_strPkgID = strPakageID;

	CPpPackage *pPackage = PpFindPackageByID(strPakageID, this);

	if (pPackage == NULL)
	{
		return;
	}

	CExBaseList oList;
	CBbVariable *pVariable = NULL;
	POS pos = NULL;
	CPpDataInterface *pDataInterface = NULL;
	
	pPackage->GetDataInterface(oList);
	pos = oList.GetHeadPosition();

	while (pos != NULL)
	{
		pVariable = (CBbVariable*)oList.GetNext(pos);
		pDataInterface = new CPpDataInterface(pVariable->m_strID, _T(""));
		AddTail(pDataInterface);
	}

	oList.RemoveAll();
}

CString CPpPackageRef::GetPackageID()
{
	return m_strPkgID;
}

//////////////////////////////////////////////////////////////////////////
//CPpPackageRefs

CPpPackageRefs::CPpPackageRefs(void)
{
}

CPpPackageRefs::~CPpPackageRefs(void)
{
}

long CPpPackageRefs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	//CProtocolXmlRWKeys *pKey = (CProtocolXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPpPackageRefs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	//CProtocolXmlRWKeys *pKey = (CProtocolXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CPpPackageRefs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

CExBaseObject* CPpPackageRefs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPackageRefKey)
	{
		return new CPpPackageRef();
	}

	return NULL;
}

CExBaseObject* CPpPackageRefs::CreateNewChild(long nClassID)
{
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CPpPackageRefs::IsEqualOwn(CBaseObject* pObj)
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

	return CExBaseObject::IsEqualOwn(pObj);
}

CBaseObject* CPpPackageRefs::Clone()
{
	CPpPackageRefs* pNew = new CPpPackageRefs();
	Copy(pNew);
	return pNew;
}

BOOL CPpPackageRefs::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	return CExBaseObject::CopyOwn(pDest);
}
