//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XMultiKeyBase.h  CXMultiKeyBase

#pragma once

#include "KeyDbGlobal.h"


#include "XKeyBase.h"

class CXMultiSubKey : public CExBaseObject
{
public:
	CXMultiSubKey();
	virtual ~CXMultiSubKey();

	CXKeyBase *m_pXKeyRef;
	long  m_nArrayIndex;

public:
	virtual UINT GetClassID() {    return KDBCLASSID_CXMULTISUBKEY;   }
	virtual BSTR GetXmlElementKey()  {      return CKeyDbXmlRWKeys::CXKeyBaseKey();     }
	
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

};

class CXMultiKeyBase : public CExBaseList
{
public:
	CXMultiKeyBase();
	virtual ~CXMultiKeyBase();

//���غ���
public:
	virtual UINT GetClassID() {    return KDBCLASSID_CXMULTIKEYBASE;   }
	virtual BSTR GetXmlElementKey()  {      return CKeyDbXmlRWKeys::CXMultiKeyBaseKey();     }
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

	virtual BOOL Query(const CString &strText, CExBaseList *pListKeys);
	virtual BOOL Match(CXKeyBase *pKey);
	virtual BOOL IsSubKey(CXKeyBase *pXKeyRef);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	BOOL HasXKey(long nArrayIndex, CXKeyBase *pKey);
};

//////////////////////////////////////////////////////////////////////////
//
class CXKeyMaps : public CExBaseList
{
public:
	CXKeyMaps();
	virtual ~CXKeyMaps();


	//���غ���
public:
	virtual UINT GetClassID() {    return KDBCLASSID_CXKEYMAPS;   }
	virtual BSTR GetXmlElementKey()  {      return CKeyDbXmlRWKeys::CXKeyMapsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
// 	virtual void InitAfterRead();
// 	virtual BOOL IsEqualOwn(CBaseObject* pObj);
// 	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
// 	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
};