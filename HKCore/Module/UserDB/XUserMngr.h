//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XUserMngr.h  CXUserMngr

#pragma once

#include "UserDBGlobal.h"


#include "XUser.h"

#define XUSER_ERRORID_NOUSER      1
#define XUSER_ERRORID_PSWERROR    2

class CXUserMngr : public CExBaseList
{
public:
	CXUserMngr();
	virtual ~CXUserMngr();

	DWORD  m_dwErrorMsg;

//���غ���
public:
	virtual UINT GetClassID() {    return USRDCLASSID_CXUSERMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CUserDBXmlRWKeys::CXUserMngrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:
	CString GetUserDBFile();

	CXUser* Login_Admin(const CString &strPSW);
	CXUser  *m_pXUserAdmin;

//˽�г�Ա�������ʷ���
public:
	void OpenUserDB();
	void SaveUserDB();

	CXUser* Login(const CString &strUser, const CString &strPSW);
	CXUser* FindUserByName(const CString &strUserName);
	CXUser* FindUserByID(const CString &strUserID);
	void AddUser(CXUser *pUser);
	void DeleteUser(CXUser *pUser);
};

