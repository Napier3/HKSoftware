//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MmsEngineDsCfg.h  CMmsEngineDsCfg

#pragma once

#include "MmsEngineConfigGlobal.h"



class CMmsEngineDsCfg : public CExBaseObject
{
public:
	CMmsEngineDsCfg();
	virtual ~CMmsEngineDsCfg();


	CString  m_strKey;
	long  m_nRead;
//重载函数
public:
	virtual UINT GetClassID() {    return MSCFGCLASSID_CMMSENGINEDSCFG;   }
	virtual BSTR GetXmlElementKey()  {      return CMmsEngineConfigXmlRWKeys::CMmsEngineDsCfgKey();     }
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

