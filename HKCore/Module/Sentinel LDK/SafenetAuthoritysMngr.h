#pragma once

#include "../MemBuffer/BufferBase.h"
#include "SafenetAuthorityGlobal.h"

class CSafenetAuthority : public CExBaseObject
{
public:
	CSafenetAuthority();
	virtual ~CSafenetAuthority();

	long m_nEnable;
	CString m_strAuthorityType;

	//重载函数
public:
	virtual BSTR GetXmlElementKey()  {      return CSafenetAuthorityXmlRWKeys::CSafenetAuthorityKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	//私有成员变量
private:

	//私有成员变量访问方法
public:
};

/*
2020-03-09  lijq
Authoritys:如果单从单词的含义来说，应该为Authorities
从设计层面上看，Authoritys作为Authority的集合对象，就在后面+“s”
*/

//////////////////////////////////////////////////////////////////////////
//CSafenetAuthoritys
class CSafenetAuthoritys : public CExBaseList
{
public:
	CSafenetAuthoritys();
	virtual ~CSafenetAuthoritys();

public:
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CSafenetAuthorityXmlRWKeys::CSafenetAuthoritysKey();     }

	void ClearAuthority();

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	void InitByAuthoritys(CSafenetAuthoritys *pSrcAuthoritys);
	void InitByAuthoritys(const CString &strAuthoritys);
	void GetAuthoritys(CString &strAuthoritys);
};


//////////////////////////////////////////////////////////////////////////
//
class CSafenetAuthoritysMngr : public CExBaseList
{
private:
	CSafenetAuthoritysMngr();
	virtual ~CSafenetAuthoritysMngr();

	static long g_nSafenetAuthoritysMngr;
	static CSafenetAuthoritysMngr *g_pSafenetAuthoritysMngr;

public:
	static CSafenetAuthoritysMngr* Create();
	static void Release();
	static CSafenetAuthoritysMngr* GetSafenetAuthoritysMngr();

	static CSafenetAuthoritys* GetAuthoritys_Test();
	static CSafenetAuthoritys* GetAuthoritys_TestApp();
	static CSafenetAuthoritys* GetAuthoritys_HaspInfo();
	static CSafenetAuthoritys* GetAuthoritys_TestMacros();
	static void ClearAuthoritys_Test();
	static void ClearAuthoritys_TestApp();
	static void ClearAuthoritys_HaspInfo();
	static void ClearAuthoritys_TestMacro();

public:
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()  {      return CSafenetAuthorityXmlRWKeys::CSafenetAuthoritysMngrKey();     }
	virtual void InitAfterRead();

	void OpenAuthorityConfigFile();

private:
	CSafenetAuthoritys *m_pTest;
	CSafenetAuthoritys *m_pTestApp;
	CSafenetAuthoritys *m_pHaspInfo;
	CSafenetAuthoritys *m_pTestMacro;

};

inline 	BOOL safenet_has_authority(const CString &strAuthoritys, const CString &strAuthority)
{
	return strAuthoritys.Find(strAuthority) >= 0;
}
