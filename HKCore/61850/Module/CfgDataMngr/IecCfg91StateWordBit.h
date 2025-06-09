//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfg91StateWordBit.h  CIecCfg91StateWordBit

#pragma once

#include "IecCfgDataMngrGlobal.h"



class CIecCfg91StateWordBit : public CExBaseObject
{
public:
	CIecCfg91StateWordBit();
	virtual ~CIecCfg91StateWordBit();


	CString  m_strDataType;
	CString  m_strValue;
	long  m_nIndex;

	CString m_strText;
//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG91STATEWORDBIT;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfg91StateWordBitKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
};

