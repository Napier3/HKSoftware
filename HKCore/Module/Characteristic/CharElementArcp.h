//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CharElementArcp.h  CCharElementArcp

#pragma once

#include "CharacteristicGlobal.h"



class CCharElementArcp : public CCharElement
{
public:
	CCharElementArcp();
	virtual ~CCharElementArcp();


	CString  m_strZ;
	CString  m_strPh;
	CString  m_strRadius;
	CString  m_strStartAngle;
	CString  m_strEndAngle;
	CString  m_strDir;
//���غ���
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTARCP;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementArcpKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	virtual CString ReturnXml();
//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

