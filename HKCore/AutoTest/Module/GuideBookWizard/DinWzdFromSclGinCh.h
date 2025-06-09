//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DinWzdFromSclGinCh.h  CDinWzdFromSclGinCh

#pragma once

#include "GuideBookWizardDefine.h"



class CDinWzdFromSclGinCh : public CExBaseObject
{
public:
	CDinWzdFromSclGinCh();
	virtual ~CDinWzdFromSclGinCh();


	CString  m_strAppID;
	CString  m_strGsChIndex;
	CString  m_strDataType;
//重载函数
public:
	virtual UINT GetClassID() {    return GBWZDCLASSID_CDINWZDFROMSCLGINCH;   }
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CDinWzdFromSclGinChKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
};

