//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ValueMap.h  CValueMap

#pragma once

#include "MacroMapMngrGlobal.h"



class CValueMap : public CExBaseObject
{
public:
	CValueMap();
	virtual ~CValueMap();

	//CString  m_strSrcName; //PowerTest参数值的释义 name
	CString  m_strMapName; //Ats参数值的释义
	//CString  m_strSrcValue; //PowerTest参数值 id
	CString  m_strMapID; //Ats参数值
//重载函数
public:
	virtual UINT GetClassID() {    return MPCLASSID_CVALUEMAP;   }
	virtual BSTR GetXmlElementKey()  {      return CMacroMapMngrXmlRWKeys::CValueMapKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
};

