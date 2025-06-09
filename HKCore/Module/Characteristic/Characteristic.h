//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Characteristic.h  CCharacteristic

#pragma once

#include "CharacteristicGlobal.h"


#include "CharacterArea.h"
#include "CharMacroDraws.h"

class CCharacteristic : public CExBaseList
{
public:
	CCharacteristic();
	virtual ~CCharacteristic();


	long  m_nAutoClose;
	CString  m_strAxis;
	CString  m_strXMin;
	CString  m_strXMax;
	CString  m_strYMin;
	CString  m_strYMax;
//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARACTERISTIC;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharacteristicKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:
	CCharacterArea *m_pArea;
	CCharMacroDraws *m_pDraws;

//私有成员变量访问方法
public:
};

