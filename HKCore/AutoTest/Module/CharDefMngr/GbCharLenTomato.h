//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//GbCharLenTomato.h  CGbCharLenTomato

#pragma once

#include "GbCharDefMngrGlobal.h"



class CGbCharLenTomato : public CExBaseObject
{
public:
	CGbCharLenTomato();
	virtual ~CGbCharLenTomato();


	CString  m_strAngle;
	CString  m_strReach;
	CString  m_strOffset;
	CString  m_strWidth;
	CString  m_strAB;
//���غ���
public:
	virtual UINT GetClassID() {    return CHRCLASSID_CGBCHARLENTOMATO;   }
	virtual BSTR GetXmlElementKey()  {      return CGbCharDefMngrXmlRWKeys::CGbCharLenTomatoKey();     }
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

