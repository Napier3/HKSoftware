//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CharElementLined.h  CCharElementLined

#pragma once

#include "CharacteristicGlobal.h"



class CCharElementLined : public CCharElement
{
public:
	CCharElementLined();
	virtual ~CCharElementLined();


	CString  m_strXb;
	CString  m_strYb;
	CString  m_strXe;
	CString  m_strYe;
//���غ���
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTLINED;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementLinedKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual CString ReturnXml();
//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

