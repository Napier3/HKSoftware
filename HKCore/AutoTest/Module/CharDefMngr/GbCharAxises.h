//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//GbCharAxises.h  CGbCharAxises

#pragma once

#include "GbCharDefMngrGlobal.h"


#include "GbCharAxis.h"

class CGbCharAxises : public CExBaseList
{
public:
	CGbCharAxises();
	virtual ~CGbCharAxises();


//���غ���
public:
	virtual UINT GetClassID() {    return CHRCLASSID_CGBCHARAXISES;   }
	virtual BSTR GetXmlElementKey()  {      return CGbCharDefMngrXmlRWKeys::CGbCharAxisesKey();     }
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

