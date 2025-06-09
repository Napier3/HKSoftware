//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CharacteristicTmplate.h  CCharacteristicTmplate

#pragma once

#include "CharacteristicGlobal.h"


#include "CharInterface.h"
#include "Characteristic.h"

class CCharacteristicTmplate : public CExBaseList
{
public:
	CCharacteristicTmplate();
	virtual ~CCharacteristicTmplate();


//���غ���
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARACTERISTICTMPLATE;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharacteristicTmplateKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:
	CCharacteristic *m_pCharacteristic;
	CCharInterface *m_pCharacteristicInterface;

//˽�г�Ա�������ʷ���
public:
};

