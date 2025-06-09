//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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


//重载函数
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

//私有成员变量
private:
	CCharacteristic *m_pCharacteristic;
	CCharInterface *m_pCharacteristicInterface;

//私有成员变量访问方法
public:
};

