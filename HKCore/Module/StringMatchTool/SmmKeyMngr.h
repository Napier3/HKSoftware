//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SmmKeyMngr.h  CSmmKeyMngr

#pragma once

#include "StringMatchMapGlobal.h"


#include "SmmGroupKey.h"
#include "SmmGroupKeys.h"
#include "SmmMultiKey.h"
#include "SmmKey.h"

class CSmmKeyMngr : public CExBaseList
{
public:
	CSmmKeyMngr();
	virtual ~CSmmKeyMngr();


//���غ���
public:
	virtual UINT GetClassID() {    return SMMCLASSID_CSMMKEYMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CStringMatchMapXmlRWKeys::CSmmKeyMngrKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
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

//˽�г�Ա�������ʷ���
public:
};

