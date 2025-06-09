//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DocRow.h  CDocRow

#pragma once

#include "DocCmpGlobal.h"


#include "DocCel.h"

class CDocRow : public CExBaseList
{
public:
	CDocRow();
	virtual ~CDocRow();


	float  m_fWidth;
	float  m_fHeigh;
//重载函数
public:
	virtual UINT GetClassID() {    return DOCMPCLASSID_CDOCROW;   }
	virtual BSTR GetXmlElementKey()  {      return CDocCmpXmlRWKeys::CDocRowKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:
	void SetCmpError();
	void Cmp(CDocRow *pRef);
	
};

