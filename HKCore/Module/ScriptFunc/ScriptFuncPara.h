//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ScriptFuncPara.h  CScriptFuncPara

#pragma once

#include "ScriptFuncGlobal.h"



class CScriptFuncPara : public CExBaseObject
{
public:
	CScriptFuncPara();
	virtual ~CScriptFuncPara();


	CString  m_strType;
//重载函数
public:
	virtual UINT GetClassID() {    return SFNCLASSID_CSCRIPTFUNCPARA;   }
	virtual BSTR GetXmlElementKey()  {      return CScriptFuncXmlRWKeys::CScriptFuncParaKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

//私有成员变量
private:

//私有成员变量访问方法
public:
};

