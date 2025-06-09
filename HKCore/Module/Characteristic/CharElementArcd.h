//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CharElementArcd.h  CCharElementArcd

#pragma once

#include "CharacteristicGlobal.h"



class CCharElementArcd : public CCharElement
{
public:
	CCharElementArcd();
	virtual ~CCharElementArcd();


	CString  m_strXc;
	CString  m_strYc;
	CString  m_strAngleB;
	CString  m_strAngleE;
	CString  m_strRadius;
//���غ���
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTARCD;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementArcdKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);

	virtual CString ReturnXml();
//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

