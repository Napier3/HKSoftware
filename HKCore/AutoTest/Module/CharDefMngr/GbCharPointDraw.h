//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//GbCharPointDraw.h  CGbCharPointDraw

#pragma once

#include "GbCharDefMngrGlobal.h"



class CGbCharPointDraw : public CExBaseObject
{
public:
	CGbCharPointDraw();
	virtual ~CGbCharPointDraw();


	CString  m_strXid;
	CString  m_strYid;
//���غ���
public:
	virtual UINT GetClassID() {    return CHRCLASSID_CGBCHARPOINTDRAW;   }
	virtual BSTR GetXmlElementKey()  {      return CGbCharDefMngrXmlRWKeys::CGbCharPointDrawKey();     }
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

