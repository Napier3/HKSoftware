//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//GbChar_y_f_x.h  CGbChar_y_f_x

#pragma once

#include "GbCharDefMngrGlobal.h"



class CGbChar_y_f_x : public CExBaseObject
{
public:
	CGbChar_y_f_x();
	virtual ~CGbChar_y_f_x();


	CString  m_strMin;
	CString  m_strMax;
	CString  m_strExpression;
//���غ���
public:
	virtual UINT GetClassID() {    return CHRCLASSID_CGBCHAR_Y_F_X;   }
	virtual BSTR GetXmlElementKey()  {      return CGbCharDefMngrXmlRWKeys::CGbChar_y_f_xKey();     }
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

