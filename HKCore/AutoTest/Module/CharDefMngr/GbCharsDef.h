//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//GbCharsDef.h  CGbCharsDef

#pragma once

#include "GbCharDefMngrGlobal.h"


#include "GbCharAxises.h"
#include "GbCharDef.h"

class CGbCharsDef : public CExBaseList
{
public:
	CGbCharsDef();
	virtual ~CGbCharsDef();


//���غ���
public:
	virtual UINT GetClassID() {    return CHRCLASSID_CGBCHARSDEF;   }
	virtual BSTR GetXmlElementKey()  {      return CGbCharDefMngrXmlRWKeys::CGbCharsDefKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
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

