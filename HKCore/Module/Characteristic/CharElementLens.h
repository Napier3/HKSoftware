//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CharElementLens.h  CCharElementLens

#pragma once

#include "CharacteristicGlobal.h"



class CCharElementLens : public CCharElement
{
public:
	CCharElementLens();
	virtual ~CCharElementLens();


	CString  m_strForwardReach;
	CString  m_strAngle;
	CString  m_strOffset;
	CString  m_strWidth;
//���غ���
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTLENS;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementLensKey();     }
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

