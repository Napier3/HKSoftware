//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgFiberPara.h  CIecCfgFiberPara

#pragma once

#include "IecCfgDataMngrGlobal.h"



class CIecCfgFiberPara : public CExBaseObject
{
public:
	CIecCfgFiberPara();
	virtual ~CIecCfgFiberPara();


	long  m_ntype;//LC 光口 0对应百兆口,1对应千兆口;   ST光口  0对应B码   1对应FT3  2对应PPS
//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFGFIBERPARA;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfgFiberParaKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
};

