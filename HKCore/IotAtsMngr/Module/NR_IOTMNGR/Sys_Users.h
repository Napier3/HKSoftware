//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Sys_Users.h  CSys_Users

#pragma once

#include "NR_IOTMNGRGlobal.h"


#include "Sys_User.h"

class CSys_Users : public CExBaseList
{
public:
	CSys_Users();
	virtual ~CSys_Users();


//���غ���
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CSYS_USERS;   }
	virtual BSTR GetXmlElementKey()  {      return CNR_IOTMNGRXmlRWKeys::CSys_UsersKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CNR_IOTMNGRXmlRWKeys::CSys_UserKey();     }
	virtual BSTR DB_GetChildTableName(CXmlRWKeys *pXmlRWKeys)  {      return CNR_IOTMNGRXmlRWKeys::CSys_UserKey();     }
	virtual CExBaseObject* DB_CreateNewChild();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

