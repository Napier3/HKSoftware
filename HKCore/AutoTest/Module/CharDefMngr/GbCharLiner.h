//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//GbCharLiner.h  CGbCharLiner

#pragma once

#include "GbCharDefMngrGlobal.h"



class CGbCharLiner : public CExBaseObject
{
public:
	CGbCharLiner();
	virtual ~CGbCharLiner();


	CString  m_strXb;
	CString  m_strYb;
	CString  m_strAngle;
	CString  m_strDir;
//���غ���
public:
	virtual UINT GetClassID() {    return CHRCLASSID_CGBCHARLINER;   }
	virtual BSTR GetXmlElementKey()  {      return CGbCharDefMngrXmlRWKeys::CGbCharLinerKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

