//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SmDbTable.h  CSmDbTable

#pragma once

#include "SmFileDBGlobal.h"
#include "SmDbData.h"
#include "SmDbBaseList.h"



class CSmDbTable : public CSmDbBaseList
{
public:
	CSmDbTable();
	virtual ~CSmDbTable();


//���غ���
public:
	virtual UINT GetClassID() {    return SMDBCLASSID_CSMDBTABLE;   }
	virtual BSTR GetXmlElementKey()  {      return CSmFileDBXmlRWKeys::CSmDbTableKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

