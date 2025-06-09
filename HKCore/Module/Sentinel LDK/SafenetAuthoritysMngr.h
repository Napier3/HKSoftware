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

	//���غ���
public:
	virtual BSTR GetXmlElementKey()  {      return CSafenetAuthorityXmlRWKeys::CSafenetAuthorityKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:
};

/*
2020-03-09  lijq
Authoritys:������ӵ��ʵĺ�����˵��Ӧ��ΪAuthorities
����Ʋ����Ͽ���Authoritys��ΪAuthority�ļ��϶��󣬾��ں���+��s��
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
