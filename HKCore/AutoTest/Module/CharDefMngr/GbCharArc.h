//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//GbCharArc.h  CGbCharArc

#pragma once

#include "GbCharDefMngrGlobal.h"



class CGbCharArc : public CExBaseObject
{
public:
	CGbCharArc();
	virtual ~CGbCharArc();


	CString  m_strXc;
	CString  m_strYc;
	CString  m_strR;
	CString  m_strAngleB;
	CString  m_strAngleE;
	CString  m_strDir;
//���غ���
public:
	virtual UINT GetClassID() {    return CHRCLASSID_CGBCHARARC;   }
	virtual BSTR GetXmlElementKey()  {      return CGbCharDefMngrXmlRWKeys::CGbCharArcKey();     }
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

