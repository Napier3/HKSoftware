//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementArcd.h  CCharElementArcd

#pragma once

#include "CharElementArcBase.h"

//2020-03-08  暂时不使用
class CCharElementArcd : public CCharElementArcBase
{
public:
	CCharElementArcd();
	virtual ~CCharElementArcd();


	CString  m_strXc;
	CString  m_strYc;
	CString  m_strAngleB;
	CString  m_strAngleE;
	CString  m_strRadius;
//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTARCD;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementArcdKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CString ReturnXml();
	virtual void Draw(CDC *pDC);

//私有成员变量
private:

//私有成员变量访问方法
public:
	virtual CXDrawDataBase* GetCXDrawDataBase();
	virtual CXDrawBase* CreateDrawElement()	;

};

