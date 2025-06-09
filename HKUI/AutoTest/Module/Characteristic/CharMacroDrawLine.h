﻿//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharMacroDrawLine.h  CCharMacroDrawLine

#pragma once

#include "CharacteristicGlobal.h"
#include "CharMacroDraw.h"


class CCharMacroDrawLine : public CCharMacroDraw
{
public:
	CCharMacroDrawLine();
	virtual ~CCharMacroDrawLine();


	CString  m_strXb;
	CString  m_strXe;
	CString  m_strYe;
	CString  m_strYb;
	CString  m_strType;
	CString  m_strColor;
//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARMACRODRAWLINE;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharMacroDrawLineKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

//私有成员变量
private:

//私有成员变量访问方法
public:
};

