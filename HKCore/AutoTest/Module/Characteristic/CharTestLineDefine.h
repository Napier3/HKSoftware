//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharTestLineDefine.h  CCharTestLineDefine

#pragma once

#include "CharacteristicGlobal.h"



class CCharTestLineDefine : public CExBaseObject
{
public:
	CCharTestLineDefine();
	virtual ~CCharTestLineDefine();


	CString  m_strExprAngle;
	CString  m_strExprX;
	CString  m_strExprY;
	CString  m_strExprR;
//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARTESTLINEDEFINE;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharTestLineDefineKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

//私有成员变量
private:

//私有成员变量访问方法
public:
};

