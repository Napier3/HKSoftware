#pragma once
#include "ExBaseList.h"
#include "ProtocolXmlRWKeys.h"
#include "BbVariable.h"

//////////////////////////////////////////////////////////////////////////
//CPpPackageRef
class CPpPackageRef :	public CExBaseList
{
public:
	CPpPackageRef(void);
	virtual ~CPpPackageRef(void);

//ÊôÐÔ
public:
	CString m_strPkgID;

public:
	virtual UINT GetClassID(){ return PPCLASSID_PPPACKAGEREF; };
	virtual BSTR GetXmlElementKey()  {      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPackageRefKey;     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

public:
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);

public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

public:
	void SetPackageID(const CString &strPakageID);
	CString GetPackageID();
};

//////////////////////////////////////////////////////////////////////////
//CPpPackageRefs
class CPpPackageRefs :	public CExBaseList
{
public:
	CPpPackageRefs(void);
	virtual ~CPpPackageRefs(void);

	//ÊôÐÔ
public:

public:
	virtual UINT GetClassID(){ return PPCLASSID_PPPACKAGEREFS; };
	virtual BSTR GetXmlElementKey()  {      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPackageRefsKey;     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

public:
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);

public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

};
