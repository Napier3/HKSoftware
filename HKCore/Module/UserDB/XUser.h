//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XUser.h  CXUser

#pragma once

#include "UserDBGlobal.h"



class CXUser : public CExBaseList
{
public:
	CXUser();
	virtual ~CXUser();


	CString  m_strPSW;
	CString  m_strCurrTool;

	static CString g_strAdminID;
	static CString g_strAdminPSW;

	static void InitAdminUserAndPSW();

//���غ���
public:
	virtual UINT GetClassID() {    return USRDCLASSID_CXUSER;   }
	virtual BSTR GetXmlElementKey()  {      return CUserDBXmlRWKeys::CXUserKey();     }
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

	long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
	virtual long InsertComboBox(CComboBox *pComboBox);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	CString GetName();
	void SetName(const CString &strName);
	CString GetID();
	void SetID(const CString &strID);
	CString GetPSW();
	void SetPSW(const CString &strPsw);

	BOOL IsAdmin()	{	return g_strAdminID == m_strID;	}
};

